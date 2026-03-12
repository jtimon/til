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
    TokenType_TAG_DotDotDot,
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
Bool * TokenType_is_DotDotDot(TokenType * self);
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
TokenType *TokenType_DotDotDot();
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

static I64 *_t2031;
static I64 *_t2032;
static I64 *_t2033;
static U64 *CAP_LIT;
static I64 *_t2034;
static I64 *_t2035;
static I64 *_t2036;
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
        I32 _t132 = 0;
        (void)_t132;
        U64 _t133 = 1;
        (void)_t133;
        memset(_t131, _t132, _t133);
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
    I32 _t171 = 0;
    (void)_t171;
    U64 _t172 = 1;
    (void)_t172;
    memset(_t170, _t171, _t172);
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
    I32 _t261 = 0;
    (void)_t261;
    memset(src, _t261, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t262 = 0;
        (void)_t262;
        I64 _t263 = 1;
        (void)_t263;
        I64 _t264 = I64_sub(_t262, _t263);
        (void)_t264;
        ;
        ;
        Bool _t265; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t264}); _t265 = *_hp; free(_hp); }
        (void)_t265;
        ;
        if (_t265) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t266 = 50;
        (void)_t266;
        sleep_ms(_t266);
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
        U64 _t272; { U64 *_hp = (U64 *)Array_len(args); _t272 = *_hp; free(_hp); }
        (void)_t272;
        Bool _wcond267; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t272}); _wcond267 = *_hp; free(_hp); }
        (void)_wcond267;
        ;
        if (_wcond267) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t273 = 0;
        (void)_t273;
        Bool _t274; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t273}); _t274 = *_hp; free(_hp); }
        (void)_t274;
        ;
        if (_t274) {
            Str *_t268 = Str_lit(" '", 2ULL);
            (void)_t268;
            Str *_t269 = Str_concat(cmd, _t268);
            (void)_t269;
            Str_delete(_t268, &(Bool){1});
            Str *_t270 = Str_concat(_t269, arg);
            (void)_t270;
            Str_delete(_t269, &(Bool){1});
            Str *_t271 = Str_lit("'", 1ULL);
            (void)_t271;
            cmd = Str_concat(_t270, _t271);
            Str_delete(_t270, &(Bool){1});
            Str_delete(_t271, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t275 = 1;
        (void)_t275;
        U64 _t276 = U64_add(DEREF(i), _t275);
        (void)_t276;
        ;
        *i = _t276;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t277 = Str_lit(" > ", 3ULL);
    (void)_t277;
    Str *_t278 = Str_concat(cmd, _t277);
    (void)_t278;
    Str_delete(_t277, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t279 = Str_concat(_t278, tmpf);
    (void)_t279;
    Str_delete(_t278, &(Bool){1});
    Str *_t280 = Str_lit(" 2>&1", 5ULL);
    (void)_t280;
    Str *_t281 = Str_concat(_t279, _t280);
    (void)_t281;
    Str_delete(_t279, &(Bool){1});
    Str_delete(_t280, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t281); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t281, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t282; { U64 *_hp = (U64 *)Str_size(); _t282 = *_hp; free(_hp); }
    (void)_t282;
    memcpy(output, content, _t282);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t283 = Str_lit("Str", 3ULL);
    (void)_t283;
    U64 _t284; { U64 *_hp = (U64 *)Str_size(); _t284 = *_hp; free(_hp); }
    (void)_t284;
    U64 _t285 = 3;
    (void)_t285;
    Array *_va0 = Array_new(_t283, &(U64){_t284}, &(U64){_t285});
    (void)_va0;
    Str_delete(_t283, &(Bool){1});
    ;
    ;
    U64 _t286 = 0;
    (void)_t286;
    Str *_t287 = Str_clone(loc_str);
    (void)_t287;
    Array_set(_va0, &(U64){_t286}, _t287);
    ;
    U64 _t288 = 1;
    (void)_t288;
    Str *_t289 = Str_lit(": panic: ", 9ULL);
    (void)_t289;
    Array_set(_va0, &(U64){_t288}, _t289);
    ;
    U64 _t290 = 2;
    (void)_t290;
    Str *_t291 = format(parts);
    (void)_t291;
    Array_set(_va0, &(U64){_t290}, _t291);
    ;
    println(_va0);
    I64 _t292 = 1;
    (void)_t292;
    exit(_t292);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t293 = Str_lit("Str", 3ULL);
    (void)_t293;
    U64 _t294; { U64 *_hp = (U64 *)Str_size(); _t294 = *_hp; free(_hp); }
    (void)_t294;
    U64 _t295 = 2;
    (void)_t295;
    Array *_va1 = Array_new(_t293, &(U64){_t294}, &(U64){_t295});
    (void)_va1;
    Str_delete(_t293, &(Bool){1});
    ;
    ;
    U64 _t296 = 0;
    (void)_t296;
    Str *_t297 = Str_lit("TODO: ", 6ULL);
    (void)_t297;
    Array_set(_va1, &(U64){_t296}, _t297);
    ;
    U64 _t298 = 1;
    (void)_t298;
    Str *_t299 = format(parts);
    (void)_t299;
    Array_set(_va1, &(U64){_t298}, _t299);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t300 = Str_lit("Str", 3ULL);
    (void)_t300;
    U64 _t301; { U64 *_hp = (U64 *)Str_size(); _t301 = *_hp; free(_hp); }
    (void)_t301;
    U64 _t302 = 1;
    (void)_t302;
    Array *_va2 = Array_new(_t300, &(U64){_t301}, &(U64){_t302});
    (void)_va2;
    Str_delete(_t300, &(Bool){1});
    ;
    ;
    U64 _t303 = 0;
    (void)_t303;
    Str *_t304 = Str_lit("unreachable", 11ULL);
    (void)_t304;
    Array_set(_va2, &(U64){_t303}, _t304);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t312 = Bool_not(DEREF(cond));
    (void)_t312;
    if (_t312) {
        Str *_t305 = Str_lit("Str", 3ULL);
        (void)_t305;
        U64 _t306; { U64 *_hp = (U64 *)Str_size(); _t306 = *_hp; free(_hp); }
        (void)_t306;
        U64 _t307 = 2;
        (void)_t307;
        Array *_va3 = Array_new(_t305, &(U64){_t306}, &(U64){_t307});
        (void)_va3;
        Str_delete(_t305, &(Bool){1});
        ;
        ;
        U64 _t308 = 0;
        (void)_t308;
        Str *_t309 = Str_lit("assert failed: ", 15ULL);
        (void)_t309;
        Array_set(_va3, &(U64){_t308}, _t309);
        ;
        U64 _t310 = 1;
        (void)_t310;
        Str *_t311 = format(parts);
        (void)_t311;
        Array_set(_va3, &(U64){_t310}, _t311);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t313 = 1;
    (void)_t313;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t313; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Str *_t314 = Str_lit("Str", 3ULL);
    (void)_t314;
    U64 _t315; { U64 *_hp = (U64 *)Str_size(); _t315 = *_hp; free(_hp); }
    (void)_t315;
    U64 _t316 = 0;
    (void)_t316;
    Array *_va4 = Array_new(_t314, &(U64){_t315}, &(U64){_t316});
    (void)_va4;
    Str_delete(_t314, &(Bool){1});
    ;
    ;
    Bool _t317; { Bool *_hp = (Bool *)assertm(loc_str, cond, _va4); _t317 = *_hp; free(_hp); }
    (void)_t317;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t317; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Array *_t318 = Array_clone(parts);
    (void)_t318;
    Array_delete(parts, &(Bool){1});
    Bool _t319; { Bool *_hp = (Bool *)assertm(loc_str, cond, _t318); _t319 = *_hp; free(_hp); }
    (void)_t319;
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t333; { Bool *_hp = (Bool *)I64_neq(a, b); _t333 = *_hp; free(_hp); }
    (void)_t333;
    if (_t333) {
        Str *_t320 = Str_lit("Str", 3ULL);
        (void)_t320;
        U64 _t321; { U64 *_hp = (U64 *)Str_size(); _t321 = *_hp; free(_hp); }
        (void)_t321;
        U64 _t322 = 5;
        (void)_t322;
        Array *_va5 = Array_new(_t320, &(U64){_t321}, &(U64){_t322});
        (void)_va5;
        Str_delete(_t320, &(Bool){1});
        ;
        ;
        U64 _t323 = 0;
        (void)_t323;
        Str *_t324 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t324;
        Array_set(_va5, &(U64){_t323}, _t324);
        ;
        U64 _t325 = 1;
        (void)_t325;
        Str *_t326 = I64_to_str(a);
        (void)_t326;
        Array_set(_va5, &(U64){_t325}, _t326);
        ;
        U64 _t327 = 2;
        (void)_t327;
        Str *_t328 = Str_lit("', found '", 10ULL);
        (void)_t328;
        Array_set(_va5, &(U64){_t327}, _t328);
        ;
        U64 _t329 = 3;
        (void)_t329;
        Str *_t330 = I64_to_str(b);
        (void)_t330;
        Array_set(_va5, &(U64){_t329}, _t330);
        ;
        U64 _t331 = 4;
        (void)_t331;
        Str *_t332 = Str_lit("'", 1ULL);
        (void)_t332;
        Array_set(_va5, &(U64){_t331}, _t332);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t347; { Bool *_hp = (Bool *)Str_eq(a, b); _t347 = *_hp; free(_hp); }
    (void)_t347;
    Bool _t348 = Bool_not(_t347);
    (void)_t348;
    ;
    if (_t348) {
        Str *_t334 = Str_lit("Str", 3ULL);
        (void)_t334;
        U64 _t335; { U64 *_hp = (U64 *)Str_size(); _t335 = *_hp; free(_hp); }
        (void)_t335;
        U64 _t336 = 5;
        (void)_t336;
        Array *_va6 = Array_new(_t334, &(U64){_t335}, &(U64){_t336});
        (void)_va6;
        Str_delete(_t334, &(Bool){1});
        ;
        ;
        U64 _t337 = 0;
        (void)_t337;
        Str *_t338 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t338;
        Array_set(_va6, &(U64){_t337}, _t338);
        ;
        U64 _t339 = 1;
        (void)_t339;
        Str *_t340 = Str_clone(a);
        (void)_t340;
        Array_set(_va6, &(U64){_t339}, _t340);
        ;
        U64 _t341 = 2;
        (void)_t341;
        Str *_t342 = Str_lit("', found '", 10ULL);
        (void)_t342;
        Array_set(_va6, &(U64){_t341}, _t342);
        ;
        U64 _t343 = 3;
        (void)_t343;
        Str *_t344 = Str_clone(b);
        (void)_t344;
        Array_set(_va6, &(U64){_t343}, _t344);
        ;
        U64 _t345 = 4;
        (void)_t345;
        Str *_t346 = Str_lit("'", 1ULL);
        (void)_t346;
        Array_set(_va6, &(U64){_t345}, _t346);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t349 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t349;
    U64 _t350 = U64_clone(cap);
    (void)_t350;
    U64 _t351 = U64_clone(elem_size);
    (void)_t351;
    Array *_t352 = malloc(sizeof(Array));
    _t352->data = _t349;
    _t352->cap = _t350;
    _t352->elem_size = _t351;
    { Str *_ca = Str_clone(elem_type); _t352->elem_type = *_ca; free(_ca); }
    (void)_t352;
    ;
    ;
    return _t352;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t367; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t367 = *_hp; free(_hp); }
    (void)_t367;
    if (_t367) {
        Str *_t353 = Str_lit("Str", 3ULL);
        (void)_t353;
        U64 _t354; { U64 *_hp = (U64 *)Str_size(); _t354 = *_hp; free(_hp); }
        (void)_t354;
        U64 _t355 = 5;
        (void)_t355;
        Array *_va7 = Array_new(_t353, &(U64){_t354}, &(U64){_t355});
        (void)_va7;
        Str_delete(_t353, &(Bool){1});
        ;
        ;
        U64 _t356 = 0;
        (void)_t356;
        Str *_t357 = Str_lit("Array.get: index ", 17ULL);
        (void)_t357;
        Array_set(_va7, &(U64){_t356}, _t357);
        ;
        U64 _t358 = 1;
        (void)_t358;
        Str *_t359 = U64_to_str(DEREF(i));
        (void)_t359;
        Array_set(_va7, &(U64){_t358}, _t359);
        ;
        U64 _t360 = 2;
        (void)_t360;
        Str *_t361 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t361;
        Array_set(_va7, &(U64){_t360}, _t361);
        ;
        U64 _t362 = 3;
        (void)_t362;
        Str *_t363 = U64_to_str(self->cap);
        (void)_t363;
        Array_set(_va7, &(U64){_t362}, _t363);
        ;
        U64 _t364 = 4;
        (void)_t364;
        Str *_t365 = Str_lit(")", 1ULL);
        (void)_t365;
        Array_set(_va7, &(U64){_t364}, _t365);
        ;
        Str *_t366 = Str_lit("/home/user/til/src/core/array.til:19:19", 39ULL);
        (void)_t366;
        panic(_t366, _va7);
        Str_delete(_t366, &(Bool){1});
    }
    ;
    U64 *_t368 = malloc(sizeof(U64)); *_t368 = U64_mul(DEREF(i), self->elem_size);
    (void)_t368;
    void *_t369 = ptr_add(self->data, DEREF(_t368));
    (void)_t369;
    U64_delete(_t368, &(Bool){1});
    return _t369;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t384; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t384 = *_hp; free(_hp); }
    (void)_t384;
    if (_t384) {
        Str *_t370 = Str_lit("Str", 3ULL);
        (void)_t370;
        U64 _t371; { U64 *_hp = (U64 *)Str_size(); _t371 = *_hp; free(_hp); }
        (void)_t371;
        U64 _t372 = 5;
        (void)_t372;
        Array *_va8 = Array_new(_t370, &(U64){_t371}, &(U64){_t372});
        (void)_va8;
        Str_delete(_t370, &(Bool){1});
        ;
        ;
        U64 _t373 = 0;
        (void)_t373;
        Str *_t374 = Str_lit("Array.set: index ", 17ULL);
        (void)_t374;
        Array_set(_va8, &(U64){_t373}, _t374);
        ;
        U64 _t375 = 1;
        (void)_t375;
        Str *_t376 = U64_to_str(DEREF(i));
        (void)_t376;
        Array_set(_va8, &(U64){_t375}, _t376);
        ;
        U64 _t377 = 2;
        (void)_t377;
        Str *_t378 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t378;
        Array_set(_va8, &(U64){_t377}, _t378);
        ;
        U64 _t379 = 3;
        (void)_t379;
        Str *_t380 = U64_to_str(self->cap);
        (void)_t380;
        Array_set(_va8, &(U64){_t379}, _t380);
        ;
        U64 _t381 = 4;
        (void)_t381;
        Str *_t382 = Str_lit(")", 1ULL);
        (void)_t382;
        Array_set(_va8, &(U64){_t381}, _t382);
        ;
        Str *_t383 = Str_lit("/home/user/til/src/core/array.til:27:19", 39ULL);
        (void)_t383;
        panic(_t383, _va8);
        Str_delete(_t383, &(Bool){1});
    }
    ;
    U64 *_t385 = malloc(sizeof(U64)); *_t385 = U64_mul(DEREF(i), self->elem_size);
    (void)_t385;
    void *_t386 = ptr_add(self->data, DEREF(_t385));
    (void)_t386;
    Bool _t387 = 0;
    (void)_t387;
    dyn_call_delete(&self->elem_type, _t386, &(Bool){_t387});
    U64_delete(_t385, &(Bool){1});
    ;
    U64 *_t388 = malloc(sizeof(U64)); *_t388 = U64_mul(DEREF(i), self->elem_size);
    (void)_t388;
    void *_t389 = ptr_add(self->data, DEREF(_t388));
    (void)_t389;
    memcpy(_t389, val, self->elem_size);
    U64_delete(_t388, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi390 = 0;
        (void)_fi390;
        while (1) {
            U64 _t392 = 0;
            (void)_t392;
            Range *_t393 = Range_new(_t392, self->cap);
            (void)_t393;
            ;
            U64 _t394; { U64 *_hp = (U64 *)Range_len(_t393); _t394 = *_hp; free(_hp); }
            (void)_t394;
            Range_delete(_t393, &(Bool){1});
            Bool _wcond391; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi390}, &(U64){_t394}); _wcond391 = *_hp; free(_hp); }
            (void)_wcond391;
            ;
            if (_wcond391) {
            } else {
                ;
                break;
            }
            ;
            U64 _t395 = 0;
            (void)_t395;
            Range *_t396 = Range_new(_t395, self->cap);
            (void)_t396;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t396, _fi390); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t396, &(Bool){1});
            U64 _t397 = 1;
            (void)_t397;
            U64 _t398 = U64_add(_fi390, _t397);
            (void)_t398;
            ;
            _fi390 = _t398;
            ;
            U64 *_t399 = malloc(sizeof(U64)); *_t399 = U64_mul(i, self->elem_size);
            (void)_t399;
            ;
            void *_t400 = ptr_add(self->data, DEREF(_t399));
            (void)_t400;
            Bool _t401 = 0;
            (void)_t401;
            dyn_call_delete(&self->elem_type, _t400, &(Bool){_t401});
            U64_delete(_t399, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t402 = 0;
    (void)_t402;
    Str_delete(&self->elem_type, &(Bool){_t402});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t416 = U64_mul(self->cap, self->elem_size);
    (void)_t416;
    U8 *new_data = malloc(_t416);
    (void)new_data;
    ;
    {
        U64 _fi403 = 0;
        (void)_fi403;
        while (1) {
            U64 _t405 = 0;
            (void)_t405;
            Range *_t406 = Range_new(_t405, self->cap);
            (void)_t406;
            ;
            U64 _t407; { U64 *_hp = (U64 *)Range_len(_t406); _t407 = *_hp; free(_hp); }
            (void)_t407;
            Range_delete(_t406, &(Bool){1});
            Bool _wcond404; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi403}, &(U64){_t407}); _wcond404 = *_hp; free(_hp); }
            (void)_wcond404;
            ;
            if (_wcond404) {
            } else {
                ;
                break;
            }
            ;
            U64 _t408 = 0;
            (void)_t408;
            Range *_t409 = Range_new(_t408, self->cap);
            (void)_t409;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t409, _fi403); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t409, &(Bool){1});
            U64 _t410 = 1;
            (void)_t410;
            U64 _t411 = U64_add(_fi403, _t410);
            (void)_t411;
            ;
            _fi403 = _t411;
            ;
            U64 *_t412 = malloc(sizeof(U64)); *_t412 = U64_mul(i, self->elem_size);
            (void)_t412;
            void *_t413 = ptr_add(self->data, DEREF(_t412));
            (void)_t413;
            void *cloned = dyn_call_clone(&self->elem_type, _t413);
            (void)cloned;
            U64_delete(_t412, &(Bool){1});
            U64 *_t414 = malloc(sizeof(U64)); *_t414 = U64_mul(i, self->elem_size);
            (void)_t414;
            ;
            void *_t415 = ptr_add(new_data, DEREF(_t414));
            (void)_t415;
            memcpy(_t415, cloned, self->elem_size);
            U64_delete(_t414, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t417 = malloc(sizeof(Array));
    _t417->data = new_data;
    _t417->cap = self->cap;
    _t417->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t417->elem_type = *_ca; free(_ca); }
    (void)_t417;
    return _t417;
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
    Bool _t431; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t431 = *_hp; free(_hp); }
    (void)_t431;
    Bool _t432 = Bool_not(_t431);
    (void)_t432;
    ;
    if (_t432) {
        Bool _t429 = dyn_has_cmp(key_type);
        (void)_t429;
        Bool _t430 = Bool_not(_t429);
        (void)_t430;
        ;
        if (_t430) {
            Str *_t419 = Str_lit("Str", 3ULL);
            (void)_t419;
            U64 _t420; { U64 *_hp = (U64 *)Str_size(); _t420 = *_hp; free(_hp); }
            (void)_t420;
            U64 _t421 = 3;
            (void)_t421;
            Array *_va9 = Array_new(_t419, &(U64){_t420}, &(U64){_t421});
            (void)_va9;
            Str_delete(_t419, &(Bool){1});
            ;
            ;
            U64 _t422 = 0;
            (void)_t422;
            Str *_t423 = Str_lit("Map.new: type ", 14ULL);
            (void)_t423;
            Array_set(_va9, &(U64){_t422}, _t423);
            ;
            U64 _t424 = 1;
            (void)_t424;
            Str *_t425 = Str_clone(key_type);
            (void)_t425;
            Array_set(_va9, &(U64){_t424}, _t425);
            ;
            U64 _t426 = 2;
            (void)_t426;
            Str *_t427 = Str_lit(" must implement cmp", 19ULL);
            (void)_t427;
            Array_set(_va9, &(U64){_t426}, _t427);
            ;
            Str *_t428 = Str_lit("/home/user/til/src/core/map.til:17:23", 37ULL);
            (void)_t428;
            panic(_t428, _va9);
            Str_delete(_t428, &(Bool){1});
        }
        ;
    }
    ;
    void *_t433 = malloc(DEREF(key_size));
    (void)_t433;
    void *_t434 = malloc(DEREF(val_size));
    (void)_t434;
    U64 _t435 = 0;
    (void)_t435;
    I64 _t436 = 1;
    (void)_t436;
    U64 _t437 = U64_clone(key_size);
    (void)_t437;
    U64 _t438 = U64_clone(val_size);
    (void)_t438;
    Map *_t439 = malloc(sizeof(Map));
    _t439->key_data = _t433;
    _t439->val_data = _t434;
    _t439->count = _t435;
    _t439->cap = _t436;
    _t439->key_size = _t437;
    { Str *_ca = Str_clone(key_type); _t439->key_type = *_ca; free(_ca); }
    _t439->val_size = _t438;
    { Str *_ca = Str_clone(val_type); _t439->val_type = *_ca; free(_ca); }
    (void)_t439;
    ;
    ;
    ;
    ;
    return _t439;
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
        Bool _wcond440; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond440 = *_hp; free(_hp); }
        (void)_wcond440;
        if (_wcond440) {
        } else {
            ;
            break;
        }
        ;
        U64 _t447 = U64_sub(hi, lo);
        (void)_t447;
        U64 _t448 = 2;
        (void)_t448;
        U64 _t449 = U64_div(_t447, _t448);
        (void)_t449;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t449);
        (void)mid;
        ;
        U64 *_t450 = malloc(sizeof(U64)); *_t450 = U64_mul(DEREF(mid), self->key_size);
        (void)_t450;
        void *_t451 = ptr_add(self->key_data, DEREF(_t450));
        (void)_t451;
        I64 *c = dyn_call_cmp(&self->key_type, _t451, key);
        (void)c;
        U64_delete(_t450, &(Bool){1});
        I64 _t452 = 0;
        (void)_t452;
        Bool _t453; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t452}); _t453 = *_hp; free(_hp); }
        (void)_t453;
        ;
        if (_t453) {
            U64 _t441 = 1;
            (void)_t441;
            U64 _t442 = U64_add(DEREF(mid), _t441);
            (void)_t442;
            ;
            lo = _t442;
            ;
        } else {
            I64 _t445 = 0;
            (void)_t445;
            Bool _t446; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t445}); _t446 = *_hp; free(_hp); }
            (void)_t446;
            ;
            if (_t446) {
                U64 _t443 = U64_clone(mid);
                (void)_t443;
                hi = _t443;
                ;
            } else {
                Bool _t444 = 1;
                (void)_t444;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t444; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t454 = 0;
    (void)_t454;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t454; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond455; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond455 = *_hp; free(_hp); }
        (void)_wcond455;
        if (_wcond455) {
        } else {
            ;
            break;
        }
        ;
        U64 _t463 = U64_sub(hi, lo);
        (void)_t463;
        U64 _t464 = 2;
        (void)_t464;
        U64 _t465 = U64_div(_t463, _t464);
        (void)_t465;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t465);
        (void)mid;
        ;
        U64 *_t466 = malloc(sizeof(U64)); *_t466 = U64_mul(DEREF(mid), self->key_size);
        (void)_t466;
        void *_t467 = ptr_add(self->key_data, DEREF(_t466));
        (void)_t467;
        I64 *c = dyn_call_cmp(&self->key_type, _t467, key);
        (void)c;
        U64_delete(_t466, &(Bool){1});
        I64 _t468 = 0;
        (void)_t468;
        Bool _t469; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t468}); _t469 = *_hp; free(_hp); }
        (void)_t469;
        ;
        if (_t469) {
            U64 _t456 = 1;
            (void)_t456;
            U64 _t457 = U64_add(DEREF(mid), _t456);
            (void)_t457;
            ;
            lo = _t457;
            ;
        } else {
            I64 _t461 = 0;
            (void)_t461;
            Bool _t462; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t461}); _t462 = *_hp; free(_hp); }
            (void)_t462;
            ;
            if (_t462) {
                U64 _t458 = U64_clone(mid);
                (void)_t458;
                hi = _t458;
                ;
            } else {
                U64 *_t459 = malloc(sizeof(U64)); *_t459 = U64_mul(DEREF(mid), self->val_size);
                (void)_t459;
                void *_t460 = ptr_add(self->val_data, DEREF(_t459));
                (void)_t460;
                U64_delete(_t459, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t460;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t470 = Str_lit("Str", 3ULL);
    (void)_t470;
    U64 _t471; { U64 *_hp = (U64 *)Str_size(); _t471 = *_hp; free(_hp); }
    (void)_t471;
    U64 _t472 = 1;
    (void)_t472;
    Array *_va10 = Array_new(_t470, &(U64){_t471}, &(U64){_t472});
    (void)_va10;
    Str_delete(_t470, &(Bool){1});
    ;
    ;
    U64 _t473 = 0;
    (void)_t473;
    Str *_t474 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t474;
    Array_set(_va10, &(U64){_t473}, _t474);
    ;
    Str *_t475 = Str_lit("/home/user/til/src/core/map.til:56:15", 37ULL);
    (void)_t475;
    panic(_t475, _va10);
    Str_delete(_t475, &(Bool){1});
    U64 *_t476 = malloc(sizeof(U64));
    *_t476 = 0;
    (void)_t476;
    void *_t477 = ptr_add(self->val_data, DEREF(_t476));
    (void)_t477;
    U64_delete(_t476, &(Bool){1});
    return _t477;
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
        Bool _wcond478; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond478 = *_hp; free(_hp); }
        (void)_wcond478;
        if (_wcond478) {
        } else {
            ;
            break;
        }
        ;
        U64 _t487 = U64_sub(hi, lo);
        (void)_t487;
        U64 _t488 = 2;
        (void)_t488;
        U64 _t489 = U64_div(_t487, _t488);
        (void)_t489;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t489);
        (void)mid;
        ;
        U64 *_t490 = malloc(sizeof(U64)); *_t490 = U64_mul(DEREF(mid), self->key_size);
        (void)_t490;
        void *_t491 = ptr_add(self->key_data, DEREF(_t490));
        (void)_t491;
        I64 *c = dyn_call_cmp(&self->key_type, _t491, key);
        (void)c;
        U64_delete(_t490, &(Bool){1});
        I64 _t492 = 0;
        (void)_t492;
        Bool _t493; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t492}); _t493 = *_hp; free(_hp); }
        (void)_t493;
        ;
        if (_t493) {
            U64 _t479 = 1;
            (void)_t479;
            U64 _t480 = U64_add(DEREF(mid), _t479);
            (void)_t480;
            ;
            lo = _t480;
            ;
        } else {
            I64 _t485 = 0;
            (void)_t485;
            Bool _t486; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t485}); _t486 = *_hp; free(_hp); }
            (void)_t486;
            ;
            if (_t486) {
                U64 _t481 = U64_clone(mid);
                (void)_t481;
                hi = _t481;
                ;
            } else {
                Bool _t482 = 1;
                (void)_t482;
                found = _t482;
                ;
                U64 _t483 = U64_clone(mid);
                (void)_t483;
                lo = _t483;
                ;
                U64 _t484 = U64_clone(mid);
                (void)_t484;
                hi = _t484;
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
        Bool _t498; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t498 = *_hp; free(_hp); }
        (void)_t498;
        Bool _t499 = Bool_not(_t498);
        (void)_t499;
        ;
        if (_t499) {
            Bool _t494 = 0;
            (void)_t494;
            dyn_call_delete(&self->key_type, key, &(Bool){_t494});
            ;
        }
        ;
        free(key);
        Bool _t500; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t500 = *_hp; free(_hp); }
        (void)_t500;
        Bool _t501 = Bool_not(_t500);
        (void)_t501;
        ;
        if (_t501) {
            U64 *_t495 = malloc(sizeof(U64)); *_t495 = U64_mul(lo, self->val_size);
            (void)_t495;
            void *_t496 = ptr_add(self->val_data, DEREF(_t495));
            (void)_t496;
            Bool _t497 = 0;
            (void)_t497;
            dyn_call_delete(&self->val_type, _t496, &(Bool){_t497});
            U64_delete(_t495, &(Bool){1});
            ;
        }
        ;
        U64 *_t502 = malloc(sizeof(U64)); *_t502 = U64_mul(lo, self->val_size);
        (void)_t502;
        void *_t503 = ptr_add(self->val_data, DEREF(_t502));
        (void)_t503;
        memcpy(_t503, val, self->val_size);
        U64_delete(_t502, &(Bool){1});
        free(val);
    } else {
        Bool _t510 = U64_eq(self->count, self->cap);
        (void)_t510;
        if (_t510) {
            U64 _t504 = 2;
            (void)_t504;
            U64 new_cap = U64_mul(self->cap, _t504);
            (void)new_cap;
            ;
            U64 _t505 = U64_mul(new_cap, self->key_size);
            (void)_t505;
            void *_t506 = realloc(self->key_data, _t505);
            (void)_t506;
            ;
            self->key_data = _t506;
            U64 _t507 = U64_mul(new_cap, self->val_size);
            (void)_t507;
            void *_t508 = realloc(self->val_data, _t507);
            (void)_t508;
            ;
            self->val_data = _t508;
            U64 _t509 = U64_clone(&(U64){new_cap});
            (void)_t509;
            ;
            self->cap = _t509;
            ;
        }
        ;
        U64 _t511 = 1;
        (void)_t511;
        U64 _t512 = U64_add(lo, _t511);
        (void)_t512;
        ;
        U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(_t512, self->key_size);
        (void)_t513;
        ;
        U64 *_t514 = malloc(sizeof(U64)); *_t514 = U64_mul(lo, self->key_size);
        (void)_t514;
        U64 _t515 = U64_sub(self->count, lo);
        (void)_t515;
        void *_t516 = ptr_add(self->key_data, DEREF(_t513));
        (void)_t516;
        void *_t517 = ptr_add(self->key_data, DEREF(_t514));
        (void)_t517;
        U64 _t518 = U64_mul(_t515, self->key_size);
        (void)_t518;
        ;
        memmove(_t516, _t517, _t518);
        U64_delete(_t513, &(Bool){1});
        U64_delete(_t514, &(Bool){1});
        ;
        U64 _t519 = 1;
        (void)_t519;
        U64 _t520 = U64_add(lo, _t519);
        (void)_t520;
        ;
        U64 *_t521 = malloc(sizeof(U64)); *_t521 = U64_mul(_t520, self->val_size);
        (void)_t521;
        ;
        U64 *_t522 = malloc(sizeof(U64)); *_t522 = U64_mul(lo, self->val_size);
        (void)_t522;
        U64 _t523 = U64_sub(self->count, lo);
        (void)_t523;
        void *_t524 = ptr_add(self->val_data, DEREF(_t521));
        (void)_t524;
        void *_t525 = ptr_add(self->val_data, DEREF(_t522));
        (void)_t525;
        U64 _t526 = U64_mul(_t523, self->val_size);
        (void)_t526;
        ;
        memmove(_t524, _t525, _t526);
        U64_delete(_t521, &(Bool){1});
        U64_delete(_t522, &(Bool){1});
        ;
        U64 *_t527 = malloc(sizeof(U64)); *_t527 = U64_mul(lo, self->key_size);
        (void)_t527;
        void *_t528 = ptr_add(self->key_data, DEREF(_t527));
        (void)_t528;
        memcpy(_t528, key, self->key_size);
        U64_delete(_t527, &(Bool){1});
        U64 *_t529 = malloc(sizeof(U64)); *_t529 = U64_mul(lo, self->val_size);
        (void)_t529;
        void *_t530 = ptr_add(self->val_data, DEREF(_t529));
        (void)_t530;
        memcpy(_t530, val, self->val_size);
        U64_delete(_t529, &(Bool){1});
        free(key);
        free(val);
        U64 _t531 = 1;
        (void)_t531;
        U64 _t532 = U64_add(self->count, _t531);
        (void)_t532;
        ;
        self->count = _t532;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t559; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t559 = *_hp; free(_hp); }
    (void)_t559;
    Bool _t560 = Bool_not(_t559);
    (void)_t560;
    ;
    if (_t560) {
        {
            U64 _fi533 = 0;
            (void)_fi533;
            while (1) {
                U64 _t535 = 0;
                (void)_t535;
                Range *_t536 = Range_new(_t535, self->count);
                (void)_t536;
                ;
                U64 _t537; { U64 *_hp = (U64 *)Range_len(_t536); _t537 = *_hp; free(_hp); }
                (void)_t537;
                Range_delete(_t536, &(Bool){1});
                Bool _wcond534; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi533}, &(U64){_t537}); _wcond534 = *_hp; free(_hp); }
                (void)_wcond534;
                ;
                if (_wcond534) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t538 = 0;
                (void)_t538;
                Range *_t539 = Range_new(_t538, self->count);
                (void)_t539;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t539, _fi533); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t539, &(Bool){1});
                U64 _t540 = 1;
                (void)_t540;
                U64 _t541 = U64_add(_fi533, _t540);
                (void)_t541;
                ;
                _fi533 = _t541;
                ;
                U64 *_t542 = malloc(sizeof(U64)); *_t542 = U64_mul(i, self->key_size);
                (void)_t542;
                ;
                void *_t543 = ptr_add(self->key_data, DEREF(_t542));
                (void)_t543;
                Bool _t544 = 0;
                (void)_t544;
                dyn_call_delete(&self->key_type, _t543, &(Bool){_t544});
                U64_delete(_t542, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t561; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t561 = *_hp; free(_hp); }
    (void)_t561;
    Bool _t562 = Bool_not(_t561);
    (void)_t562;
    ;
    if (_t562) {
        {
            U64 _fi545 = 0;
            (void)_fi545;
            while (1) {
                U64 _t547 = 0;
                (void)_t547;
                Range *_t548 = Range_new(_t547, self->count);
                (void)_t548;
                ;
                U64 _t549; { U64 *_hp = (U64 *)Range_len(_t548); _t549 = *_hp; free(_hp); }
                (void)_t549;
                Range_delete(_t548, &(Bool){1});
                Bool _wcond546; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi545}, &(U64){_t549}); _wcond546 = *_hp; free(_hp); }
                (void)_wcond546;
                ;
                if (_wcond546) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t550 = 0;
                (void)_t550;
                Range *_t551 = Range_new(_t550, self->count);
                (void)_t551;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t551, _fi545); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t551, &(Bool){1});
                U64 _t552 = 1;
                (void)_t552;
                U64 _t553 = U64_add(_fi545, _t552);
                (void)_t553;
                ;
                _fi545 = _t553;
                ;
                U64 *_t554 = malloc(sizeof(U64)); *_t554 = U64_mul(i, self->val_size);
                (void)_t554;
                ;
                void *_t555 = ptr_add(self->val_data, DEREF(_t554));
                (void)_t555;
                Bool _t556 = 0;
                (void)_t556;
                dyn_call_delete(&self->val_type, _t555, &(Bool){_t556});
                U64_delete(_t554, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t563; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t563 = *_hp; free(_hp); }
    (void)_t563;
    Bool _t564 = Bool_not(_t563);
    (void)_t564;
    ;
    if (_t564) {
        Bool _t557 = 0;
        (void)_t557;
        Str_delete(&self->key_type, &(Bool){_t557});
        ;
    }
    ;
    Bool _t565; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t565 = *_hp; free(_hp); }
    (void)_t565;
    Bool _t566 = Bool_not(_t565);
    (void)_t566;
    ;
    if (_t566) {
        Bool _t558 = 0;
        (void)_t558;
        Str_delete(&self->val_type, &(Bool){_t558});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t584 = U64_mul(self->cap, self->key_size);
    (void)_t584;
    U8 *new_keys = malloc(_t584);
    (void)new_keys;
    ;
    U64 _t585 = U64_mul(self->cap, self->val_size);
    (void)_t585;
    U8 *new_vals = malloc(_t585);
    (void)new_vals;
    ;
    {
        U64 _fi567 = 0;
        (void)_fi567;
        while (1) {
            U64 _t569 = 0;
            (void)_t569;
            Range *_t570 = Range_new(_t569, self->count);
            (void)_t570;
            ;
            U64 _t571; { U64 *_hp = (U64 *)Range_len(_t570); _t571 = *_hp; free(_hp); }
            (void)_t571;
            Range_delete(_t570, &(Bool){1});
            Bool _wcond568; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi567}, &(U64){_t571}); _wcond568 = *_hp; free(_hp); }
            (void)_wcond568;
            ;
            if (_wcond568) {
            } else {
                ;
                break;
            }
            ;
            U64 _t572 = 0;
            (void)_t572;
            Range *_t573 = Range_new(_t572, self->count);
            (void)_t573;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t573, _fi567); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t573, &(Bool){1});
            U64 _t574 = 1;
            (void)_t574;
            U64 _t575 = U64_add(_fi567, _t574);
            (void)_t575;
            ;
            _fi567 = _t575;
            ;
            U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_mul(i, self->key_size);
            (void)_t576;
            void *_t577 = ptr_add(self->key_data, DEREF(_t576));
            (void)_t577;
            void *ck = dyn_call_clone(&self->key_type, _t577);
            (void)ck;
            U64_delete(_t576, &(Bool){1});
            U64 *_t578 = malloc(sizeof(U64)); *_t578 = U64_mul(i, self->key_size);
            (void)_t578;
            void *_t579 = ptr_add(new_keys, DEREF(_t578));
            (void)_t579;
            memcpy(_t579, ck, self->key_size);
            U64_delete(_t578, &(Bool){1});
            free(ck);
            U64 *_t580 = malloc(sizeof(U64)); *_t580 = U64_mul(i, self->val_size);
            (void)_t580;
            void *_t581 = ptr_add(self->val_data, DEREF(_t580));
            (void)_t581;
            void *cv = dyn_call_clone(&self->val_type, _t581);
            (void)cv;
            U64_delete(_t580, &(Bool){1});
            U64 *_t582 = malloc(sizeof(U64)); *_t582 = U64_mul(i, self->val_size);
            (void)_t582;
            ;
            void *_t583 = ptr_add(new_vals, DEREF(_t582));
            (void)_t583;
            memcpy(_t583, cv, self->val_size);
            U64_delete(_t582, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t586 = malloc(sizeof(Map));
    _t586->key_data = new_keys;
    _t586->val_data = new_vals;
    _t586->count = self->count;
    _t586->cap = self->cap;
    _t586->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t586->key_type = *_ca; free(_ca); }
    _t586->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t586->val_type = *_ca; free(_ca); }
    (void)_t586;
    return _t586;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t600; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t600 = *_hp; free(_hp); }
    (void)_t600;
    Bool _t601 = Bool_not(_t600);
    (void)_t601;
    ;
    if (_t601) {
        Bool _t598 = dyn_has_cmp(elem_type);
        (void)_t598;
        Bool _t599 = Bool_not(_t598);
        (void)_t599;
        ;
        if (_t599) {
            Str *_t588 = Str_lit("Str", 3ULL);
            (void)_t588;
            U64 _t589; { U64 *_hp = (U64 *)Str_size(); _t589 = *_hp; free(_hp); }
            (void)_t589;
            U64 _t590 = 3;
            (void)_t590;
            Array *_va11 = Array_new(_t588, &(U64){_t589}, &(U64){_t590});
            (void)_va11;
            Str_delete(_t588, &(Bool){1});
            ;
            ;
            U64 _t591 = 0;
            (void)_t591;
            Str *_t592 = Str_lit("Set.new: type ", 14ULL);
            (void)_t592;
            Array_set(_va11, &(U64){_t591}, _t592);
            ;
            U64 _t593 = 1;
            (void)_t593;
            Str *_t594 = Str_clone(elem_type);
            (void)_t594;
            Array_set(_va11, &(U64){_t593}, _t594);
            ;
            U64 _t595 = 2;
            (void)_t595;
            Str *_t596 = Str_lit(" must implement cmp", 19ULL);
            (void)_t596;
            Array_set(_va11, &(U64){_t595}, _t596);
            ;
            Str *_t597 = Str_lit("/home/user/til/src/core/set.til:14:23", 37ULL);
            (void)_t597;
            panic(_t597, _va11);
            Str_delete(_t597, &(Bool){1});
        }
        ;
    }
    ;
    void *_t602 = malloc(DEREF(elem_size));
    (void)_t602;
    U64 _t603 = 0;
    (void)_t603;
    I64 _t604 = 1;
    (void)_t604;
    U64 _t605 = U64_clone(elem_size);
    (void)_t605;
    Set *_t606 = malloc(sizeof(Set));
    _t606->data = _t602;
    _t606->count = _t603;
    _t606->cap = _t604;
    _t606->elem_size = _t605;
    { Str *_ca = Str_clone(elem_type); _t606->elem_type = *_ca; free(_ca); }
    (void)_t606;
    ;
    ;
    ;
    return _t606;
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
        Bool _wcond607; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond607 = *_hp; free(_hp); }
        (void)_wcond607;
        if (_wcond607) {
        } else {
            ;
            break;
        }
        ;
        U64 _t614 = U64_sub(hi, lo);
        (void)_t614;
        U64 _t615 = 2;
        (void)_t615;
        U64 _t616 = U64_div(_t614, _t615);
        (void)_t616;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t616);
        (void)mid;
        ;
        U64 *_t617 = malloc(sizeof(U64)); *_t617 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t617;
        void *_t618 = ptr_add(self->data, DEREF(_t617));
        (void)_t618;
        I64 *c = dyn_call_cmp(&self->elem_type, _t618, val);
        (void)c;
        U64_delete(_t617, &(Bool){1});
        I64 _t619 = 0;
        (void)_t619;
        Bool _t620; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t619}); _t620 = *_hp; free(_hp); }
        (void)_t620;
        ;
        if (_t620) {
            U64 _t608 = 1;
            (void)_t608;
            U64 _t609 = U64_add(DEREF(mid), _t608);
            (void)_t609;
            ;
            lo = _t609;
            ;
        } else {
            I64 _t612 = 0;
            (void)_t612;
            Bool _t613; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t612}); _t613 = *_hp; free(_hp); }
            (void)_t613;
            ;
            if (_t613) {
                U64 _t610 = U64_clone(mid);
                (void)_t610;
                hi = _t610;
                ;
            } else {
                Bool _t611 = 1;
                (void)_t611;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t611; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t621 = 0;
    (void)_t621;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t621; return _r; }
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
        Bool _wcond622; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond622 = *_hp; free(_hp); }
        (void)_wcond622;
        if (_wcond622) {
        } else {
            ;
            break;
        }
        ;
        U64 _t631 = U64_sub(hi, lo);
        (void)_t631;
        U64 _t632 = 2;
        (void)_t632;
        U64 _t633 = U64_div(_t631, _t632);
        (void)_t633;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t633);
        (void)mid;
        ;
        U64 *_t634 = malloc(sizeof(U64)); *_t634 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t634;
        void *_t635 = ptr_add(self->data, DEREF(_t634));
        (void)_t635;
        I64 *c = dyn_call_cmp(&self->elem_type, _t635, val);
        (void)c;
        U64_delete(_t634, &(Bool){1});
        I64 _t636 = 0;
        (void)_t636;
        Bool _t637; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t636}); _t637 = *_hp; free(_hp); }
        (void)_t637;
        ;
        if (_t637) {
            U64 _t623 = 1;
            (void)_t623;
            U64 _t624 = U64_add(DEREF(mid), _t623);
            (void)_t624;
            ;
            lo = _t624;
            ;
        } else {
            I64 _t629 = 0;
            (void)_t629;
            Bool _t630; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t629}); _t630 = *_hp; free(_hp); }
            (void)_t630;
            ;
            if (_t630) {
                U64 _t625 = U64_clone(mid);
                (void)_t625;
                hi = _t625;
                ;
            } else {
                Bool _t626 = 1;
                (void)_t626;
                found = _t626;
                ;
                U64 _t627 = U64_clone(mid);
                (void)_t627;
                lo = _t627;
                ;
                U64 _t628 = U64_clone(mid);
                (void)_t628;
                hi = _t628;
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
        Bool _t639; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t639 = *_hp; free(_hp); }
        (void)_t639;
        Bool _t640 = Bool_not(_t639);
        (void)_t640;
        ;
        if (_t640) {
            Bool _t638 = 0;
            (void)_t638;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t638});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t645 = U64_eq(self->count, self->cap);
        (void)_t645;
        if (_t645) {
            U64 _t641 = 2;
            (void)_t641;
            U64 new_cap = U64_mul(self->cap, _t641);
            (void)new_cap;
            ;
            U64 _t642 = U64_mul(new_cap, self->elem_size);
            (void)_t642;
            void *_t643 = realloc(self->data, _t642);
            (void)_t643;
            ;
            self->data = _t643;
            U64 _t644 = U64_clone(&(U64){new_cap});
            (void)_t644;
            ;
            self->cap = _t644;
            ;
        }
        ;
        U64 _t646 = 1;
        (void)_t646;
        U64 _t647 = U64_add(lo, _t646);
        (void)_t647;
        ;
        U64 *_t648 = malloc(sizeof(U64)); *_t648 = U64_mul(_t647, self->elem_size);
        (void)_t648;
        ;
        U64 *_t649 = malloc(sizeof(U64)); *_t649 = U64_mul(lo, self->elem_size);
        (void)_t649;
        U64 _t650 = U64_sub(self->count, lo);
        (void)_t650;
        void *_t651 = ptr_add(self->data, DEREF(_t648));
        (void)_t651;
        void *_t652 = ptr_add(self->data, DEREF(_t649));
        (void)_t652;
        U64 _t653 = U64_mul(_t650, self->elem_size);
        (void)_t653;
        ;
        memmove(_t651, _t652, _t653);
        U64_delete(_t648, &(Bool){1});
        U64_delete(_t649, &(Bool){1});
        ;
        U64 *_t654 = malloc(sizeof(U64)); *_t654 = U64_mul(lo, self->elem_size);
        (void)_t654;
        void *_t655 = ptr_add(self->data, DEREF(_t654));
        (void)_t655;
        memcpy(_t655, val, self->elem_size);
        U64_delete(_t654, &(Bool){1});
        free(val);
        U64 _t656 = 1;
        (void)_t656;
        U64 _t657 = U64_add(self->count, _t656);
        (void)_t657;
        ;
        self->count = _t657;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t671; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t671 = *_hp; free(_hp); }
    (void)_t671;
    Bool _t672 = Bool_not(_t671);
    (void)_t672;
    ;
    if (_t672) {
        {
            U64 _fi658 = 0;
            (void)_fi658;
            while (1) {
                U64 _t660 = 0;
                (void)_t660;
                Range *_t661 = Range_new(_t660, self->count);
                (void)_t661;
                ;
                U64 _t662; { U64 *_hp = (U64 *)Range_len(_t661); _t662 = *_hp; free(_hp); }
                (void)_t662;
                Range_delete(_t661, &(Bool){1});
                Bool _wcond659; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi658}, &(U64){_t662}); _wcond659 = *_hp; free(_hp); }
                (void)_wcond659;
                ;
                if (_wcond659) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t663 = 0;
                (void)_t663;
                Range *_t664 = Range_new(_t663, self->count);
                (void)_t664;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t664, _fi658); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t664, &(Bool){1});
                U64 _t665 = 1;
                (void)_t665;
                U64 _t666 = U64_add(_fi658, _t665);
                (void)_t666;
                ;
                _fi658 = _t666;
                ;
                U64 *_t667 = malloc(sizeof(U64)); *_t667 = U64_mul(i, self->elem_size);
                (void)_t667;
                ;
                void *_t668 = ptr_add(self->data, DEREF(_t667));
                (void)_t668;
                Bool _t669 = 0;
                (void)_t669;
                dyn_call_delete(&self->elem_type, _t668, &(Bool){_t669});
                U64_delete(_t667, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t673; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t673 = *_hp; free(_hp); }
    (void)_t673;
    Bool _t674 = Bool_not(_t673);
    (void)_t674;
    ;
    if (_t674) {
        Bool _t670 = 0;
        (void)_t670;
        Str_delete(&self->elem_type, &(Bool){_t670});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t688 = U64_mul(self->cap, self->elem_size);
    (void)_t688;
    U8 *new_data = malloc(_t688);
    (void)new_data;
    ;
    {
        U64 _fi675 = 0;
        (void)_fi675;
        while (1) {
            U64 _t677 = 0;
            (void)_t677;
            Range *_t678 = Range_new(_t677, self->count);
            (void)_t678;
            ;
            U64 _t679; { U64 *_hp = (U64 *)Range_len(_t678); _t679 = *_hp; free(_hp); }
            (void)_t679;
            Range_delete(_t678, &(Bool){1});
            Bool _wcond676; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi675}, &(U64){_t679}); _wcond676 = *_hp; free(_hp); }
            (void)_wcond676;
            ;
            if (_wcond676) {
            } else {
                ;
                break;
            }
            ;
            U64 _t680 = 0;
            (void)_t680;
            Range *_t681 = Range_new(_t680, self->count);
            (void)_t681;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t681, _fi675); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t681, &(Bool){1});
            U64 _t682 = 1;
            (void)_t682;
            U64 _t683 = U64_add(_fi675, _t682);
            (void)_t683;
            ;
            _fi675 = _t683;
            ;
            U64 *_t684 = malloc(sizeof(U64)); *_t684 = U64_mul(i, self->elem_size);
            (void)_t684;
            void *_t685 = ptr_add(self->data, DEREF(_t684));
            (void)_t685;
            void *cloned = dyn_call_clone(&self->elem_type, _t685);
            (void)cloned;
            U64_delete(_t684, &(Bool){1});
            U64 *_t686 = malloc(sizeof(U64)); *_t686 = U64_mul(i, self->elem_size);
            (void)_t686;
            ;
            void *_t687 = ptr_add(new_data, DEREF(_t686));
            (void)_t687;
            memcpy(_t687, cloned, self->elem_size);
            U64_delete(_t686, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t689 = malloc(sizeof(Set));
    _t689->data = new_data;
    _t689->count = self->count;
    _t689->cap = self->cap;
    _t689->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t689->elem_type = *_ca; free(_ca); }
    (void)_t689;
    return _t689;
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
    Bool _t697; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t697 = *_hp; free(_hp); }
    (void)_t697;
    if (_t697) {
        Str *_t691 = Str_lit("Str", 3ULL);
        (void)_t691;
        U64 _t692; { U64 *_hp = (U64 *)Str_size(); _t692 = *_hp; free(_hp); }
        (void)_t692;
        U64 _t693 = 1;
        (void)_t693;
        Array *_va12 = Array_new(_t691, &(U64){_t692}, &(U64){_t693});
        (void)_va12;
        Str_delete(_t691, &(Bool){1});
        ;
        ;
        U64 _t694 = 0;
        (void)_t694;
        Str *_t695 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t695;
        Array_set(_va12, &(U64){_t694}, _t695);
        ;
        Str *_t696 = Str_lit("/home/user/til/src/core/str.til:16:19", 37ULL);
        (void)_t696;
        panic(_t696, _va12);
        Str_delete(_t696, &(Bool){1});
    }
    ;
    void *_t698 = ptr_add(self->c_str, DEREF(i));
    (void)_t698;
    return _t698;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t699 = ptr_add(self->c_str, DEREF(i));
    (void)_t699;
    return _t699;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t705; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t705 = *_hp; free(_hp); }
    (void)_t705;
    if (_t705) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond700; { Bool *_hp = (Bool *)U64_lt(i, &(U64){min_len}); _wcond700 = *_hp; free(_hp); }
        (void)_wcond700;
        if (_wcond700) {
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
        I64 _t701 = 0;
        (void)_t701;
        Bool _t702; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t701}); _t702 = *_hp; free(_hp); }
        (void)_t702;
        ;
        if (_t702) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t703 = 1;
        (void)_t703;
        U64 _t704 = U64_add(DEREF(i), _t703);
        (void)_t704;
        ;
        *i = _t704;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t706 = U64_cmp(a->count, b->count);
    (void)_t706;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t706; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t707 = 1;
    (void)_t707;
    U64 _t708 = U64_add(DEREF(new_len), _t707);
    (void)_t708;
    ;
    U8 *new_data = malloc(_t708);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t709 = ptr_add(new_data, a->count);
    (void)_t709;
    memcpy(_t709, b->c_str, b->count);
    void *_t710 = ptr_add(new_data, DEREF(new_len));
    (void)_t710;
    I32 _t711 = 0;
    (void)_t711;
    U64 _t712 = 1;
    (void)_t712;
    memset(_t710, _t711, _t712);
    ;
    ;
    U64 _t713 = U64_clone(new_len);
    (void)_t713;
    U64 _t714 = U64_clone(new_len);
    (void)_t714;
    U64_delete(new_len, &(Bool){1});
    Str *_t715 = malloc(sizeof(Str));
    _t715->c_str = new_data;
    _t715->count = _t713;
    _t715->cap = _t714;
    (void)_t715;
    ;
    ;
    return _t715;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t716 = 1;
    (void)_t716;
    U64 _t717 = U64_add(DEREF(n), _t716);
    (void)_t717;
    ;
    U8 *buf = malloc(_t717);
    (void)buf;
    ;
    I32 _t718 = 0;
    (void)_t718;
    U64 _t719 = 1;
    (void)_t719;
    memset(buf, _t718, _t719);
    ;
    ;
    I64 _t720 = 0;
    (void)_t720;
    U64 _t721 = U64_clone(n);
    (void)_t721;
    Str *_t722 = malloc(sizeof(Str));
    _t722->c_str = buf;
    _t722->count = _t720;
    _t722->cap = _t721;
    (void)_t722;
    ;
    ;
    return _t722;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t735; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t735 = *_hp; free(_hp); }
    (void)_t735;
    if (_t735) {
        Str *_t723 = Str_lit("Str", 3ULL);
        (void)_t723;
        U64 _t724; { U64 *_hp = (U64 *)Str_size(); _t724 = *_hp; free(_hp); }
        (void)_t724;
        U64 _t725 = 1;
        (void)_t725;
        Array *_va13 = Array_new(_t723, &(U64){_t724}, &(U64){_t725});
        (void)_va13;
        Str_delete(_t723, &(Bool){1});
        ;
        ;
        U64 _t726 = 0;
        (void)_t726;
        Str *_t727 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t727;
        Array_set(_va13, &(U64){_t726}, _t727);
        ;
        Str *_t728 = Str_lit("/home/user/til/src/core/str.til:57:19", 37ULL);
        (void)_t728;
        panic(_t728, _va13);
        Str_delete(_t728, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t736; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t736 = *_hp; free(_hp); }
    (void)_t736;
    if (_t736) {
        Str *_t729 = Str_lit("Str", 3ULL);
        (void)_t729;
        U64 _t730; { U64 *_hp = (U64 *)Str_size(); _t730 = *_hp; free(_hp); }
        (void)_t730;
        U64 _t731 = 1;
        (void)_t731;
        Array *_va14 = Array_new(_t729, &(U64){_t730}, &(U64){_t731});
        (void)_va14;
        Str_delete(_t729, &(Bool){1});
        ;
        ;
        U64 _t732 = 0;
        (void)_t732;
        Str *_t733 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t733;
        Array_set(_va14, &(U64){_t732}, _t733);
        ;
        Str *_t734 = Str_lit("/home/user/til/src/core/str.til:61:19", 37ULL);
        (void)_t734;
        panic(_t734, _va14);
        Str_delete(_t734, &(Bool){1});
    }
    ;
    void *_t737 = ptr_add(self->c_str, self->count);
    (void)_t737;
    memcpy(_t737, s->c_str, s->count);
    U64 _t738 = U64_clone(new_len);
    (void)_t738;
    self->count = _t738;
    ;
    void *_t739 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t739;
    I32 _t740 = 0;
    (void)_t740;
    U64 _t741 = 1;
    (void)_t741;
    memset(_t739, _t740, _t741);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t742 = 1;
    (void)_t742;
    U64 _t743 = U64_add(val->count, _t742);
    (void)_t743;
    ;
    U8 *new_data = malloc(_t743);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t744 = ptr_add(new_data, val->count);
    (void)_t744;
    I32 _t745 = 0;
    (void)_t745;
    U64 _t746 = 1;
    (void)_t746;
    memset(_t744, _t745, _t746);
    ;
    ;
    Str *_t747 = malloc(sizeof(Str));
    _t747->c_str = new_data;
    _t747->count = val->count;
    _t747->cap = val->count;
    (void)_t747;
    return _t747;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t748; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t748 = *_hp; free(_hp); }
    (void)_t748;
    if (_t748) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t749 = Str_clone(val);
    (void)_t749;
    return _t749;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t751; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t751 = *_hp; free(_hp); }
    (void)_t751;
    if (_t751) {
        *st = s->count;
    }
    ;
    U64 _t752 = U64_add(DEREF(st), ln);
    (void)_t752;
    Bool _t753; { Bool *_hp = (Bool *)U64_gt(&(U64){_t752}, &s->count); _t753 = *_hp; free(_hp); }
    (void)_t753;
    ;
    if (_t753) {
        U64 _t750 = U64_sub(s->count, DEREF(st));
        (void)_t750;
        ln = _t750;
        ;
    }
    ;
    void *_t754 = ptr_add(s->c_str, DEREF(st));
    (void)_t754;
    U64 _t755 = U64_clone(&(U64){ln});
    (void)_t755;
    ;
    U64 _t756 = U64_clone(CAP_VIEW);
    (void)_t756;
    Str *_t757 = malloc(sizeof(Str));
    _t757->c_str = _t754;
    _t757->count = _t755;
    _t757->cap = _t756;
    (void)_t757;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t757;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t771 = 0;
    (void)_t771;
    Bool _t772 = U64_eq(b->count, _t771);
    (void)_t772;
    ;
    if (_t772) {
        Bool _t758 = 1;
        (void)_t758;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t758; return _r; }
    }
    ;
    Bool _t773; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t773 = *_hp; free(_hp); }
    (void)_t773;
    if (_t773) {
        Bool _t759 = 0;
        (void)_t759;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t759; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t768 = U64_sub(a->count, b->count);
        (void)_t768;
        Bool _wcond760; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t768}); _wcond760 = *_hp; free(_hp); }
        (void)_wcond760;
        ;
        if (_wcond760) {
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
            Bool _wcond761; { Bool *_hp = (Bool *)U64_lt(j, &b->count); _wcond761 = *_hp; free(_hp); }
            (void)_wcond761;
            if (_wcond761) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t763 = malloc(sizeof(U64)); *_t763 = U64_add(i, DEREF(j));
            (void)_t763;
            U8 *ac = Str_get(a, _t763);
            (void)ac;
            U8 *bc = Str_get(b, j);
            (void)bc;
            Bool _t764; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t764 = *_hp; free(_hp); }
            (void)_t764;
            U64_delete(_t763, &(Bool){1});
            if (_t764) {
                Bool _t762 = 0;
                (void)_t762;
                found = _t762;
                ;
            }
            ;
            U64 _t765 = 1;
            (void)_t765;
            U64 _t766 = U64_add(DEREF(j), _t765);
            (void)_t766;
            ;
            *j = _t766;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t767 = 1;
            (void)_t767;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t767; return _r; }
        }
        ;
        U64 _t769 = 1;
        (void)_t769;
        U64 _t770 = U64_add(i, _t769);
        (void)_t770;
        ;
        i = _t770;
        ;
    }
    ;
    Bool _t774 = 0;
    (void)_t774;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t774; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t781; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t781 = *_hp; free(_hp); }
    (void)_t781;
    if (_t781) {
        Bool _t775 = 0;
        (void)_t775;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t775; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond776; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond776 = *_hp; free(_hp); }
        (void)_wcond776;
        if (_wcond776) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t778; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t778 = *_hp; free(_hp); }
        (void)_t778;
        if (_t778) {
            Bool _t777 = 0;
            (void)_t777;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t777; return _r; }
        }
        ;
        U64 _t779 = 1;
        (void)_t779;
        U64 _t780 = U64_add(DEREF(i), _t779);
        (void)_t780;
        ;
        *i = _t780;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t782 = 1;
    (void)_t782;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t782; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t790; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t790 = *_hp; free(_hp); }
    (void)_t790;
    if (_t790) {
        Bool _t783 = 0;
        (void)_t783;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t783; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond784; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond784 = *_hp; free(_hp); }
        (void)_wcond784;
        if (_wcond784) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t786 = malloc(sizeof(U64)); *_t786 = U64_add(offset, DEREF(i));
        (void)_t786;
        U8 *ac = Str_get(a, _t786);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t787; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t787 = *_hp; free(_hp); }
        (void)_t787;
        U64_delete(_t786, &(Bool){1});
        if (_t787) {
            Bool _t785 = 0;
            (void)_t785;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t785; return _r; }
        }
        ;
        U64 _t788 = 1;
        (void)_t788;
        U64 _t789 = U64_add(DEREF(i), _t788);
        (void)_t789;
        ;
        *i = _t789;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t791 = 1;
    (void)_t791;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t791; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t792 = 0;
    (void)_t792;
    Bool _t793 = U64_eq(self->count, _t792);
    (void)_t793;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t793; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t811 = 0;
    (void)_t811;
    Bool _t812 = U64_eq(needle->count, _t811);
    (void)_t812;
    ;
    if (_t812) {
        I64 _t794 = 0;
        (void)_t794;
        I64 _t795 = 1;
        (void)_t795;
        I64 _t796 = I64_sub(_t794, _t795);
        (void)_t796;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t796; return _r; }
    }
    ;
    Bool _t813; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t813 = *_hp; free(_hp); }
    (void)_t813;
    if (_t813) {
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
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t808 = U64_sub(self->count, needle->count);
        (void)_t808;
        Bool _wcond800; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t808}); _wcond800 = *_hp; free(_hp); }
        (void)_wcond800;
        ;
        if (_wcond800) {
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
            Bool _wcond801; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond801 = *_hp; free(_hp); }
            (void)_wcond801;
            if (_wcond801) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t803 = malloc(sizeof(U64)); *_t803 = U64_add(i, DEREF(j));
            (void)_t803;
            U8 *ac = Str_get(self, _t803);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t804; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t804 = *_hp; free(_hp); }
            (void)_t804;
            U64_delete(_t803, &(Bool){1});
            if (_t804) {
                Bool _t802 = 0;
                (void)_t802;
                found = _t802;
                ;
            }
            ;
            U64 _t805 = 1;
            (void)_t805;
            U64 _t806 = U64_add(DEREF(j), _t805);
            (void)_t806;
            ;
            *j = _t806;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t807 = U64_to_i64(i);
            (void)_t807;
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t807; return _r; }
        }
        ;
        U64 _t809 = 1;
        (void)_t809;
        U64 _t810 = U64_add(i, _t809);
        (void)_t810;
        ;
        i = _t810;
        ;
    }
    ;
    I64 _t814 = 0;
    (void)_t814;
    I64 _t815 = 1;
    (void)_t815;
    I64 _t816 = I64_sub(_t814, _t815);
    (void)_t816;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t816; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t834 = 0;
    (void)_t834;
    Bool _t835 = U64_eq(needle->count, _t834);
    (void)_t835;
    ;
    if (_t835) {
        I64 _t817 = 0;
        (void)_t817;
        I64 _t818 = 1;
        (void)_t818;
        I64 _t819 = I64_sub(_t817, _t818);
        (void)_t819;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t819; return _r; }
    }
    ;
    Bool _t836; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t836 = *_hp; free(_hp); }
    (void)_t836;
    if (_t836) {
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
    I64 _t837 = 0;
    (void)_t837;
    I64 _t838 = 1;
    (void)_t838;
    I64 last = I64_sub(_t837, _t838);
    (void)last;
    ;
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t831 = U64_sub(self->count, needle->count);
        (void)_t831;
        Bool _wcond823; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t831}); _wcond823 = *_hp; free(_hp); }
        (void)_wcond823;
        ;
        if (_wcond823) {
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
            Bool _wcond824; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond824 = *_hp; free(_hp); }
            (void)_wcond824;
            if (_wcond824) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t826 = malloc(sizeof(U64)); *_t826 = U64_add(i, DEREF(j));
            (void)_t826;
            U8 *ac = Str_get(self, _t826);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t827; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t827 = *_hp; free(_hp); }
            (void)_t827;
            U64_delete(_t826, &(Bool){1});
            if (_t827) {
                Bool _t825 = 0;
                (void)_t825;
                found = _t825;
                ;
            }
            ;
            U64 _t828 = 1;
            (void)_t828;
            U64 _t829 = U64_add(DEREF(j), _t828);
            (void)_t829;
            ;
            *j = _t829;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t830 = U64_to_i64(i);
            (void)_t830;
            last = _t830;
            ;
        }
        ;
        U64 _t832 = 1;
        (void)_t832;
        U64 _t833 = U64_add(i, _t832);
        (void)_t833;
        ;
        i = _t833;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t854 = 0;
    (void)_t854;
    Bool _t855 = U64_eq(from->count, _t854);
    (void)_t855;
    ;
    if (_t855) {
        Str *_t839 = Str_clone(self);
        (void)_t839;
        ;
        return _t839;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t841 = U64_sub(self->count, from->count);
        (void)_t841;
        Bool _wcond840; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t841}); _wcond840 = *_hp; free(_hp); }
        (void)_wcond840;
        ;
        if (_wcond840) {
        } else {
            ;
            break;
        }
        ;
        U64 _t842 = U64_sub(self->count, start);
        (void)_t842;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t842});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t843 = 0;
        (void)_t843;
        I64 _t844 = 1;
        (void)_t844;
        I64 _t845 = I64_sub(_t843, _t844);
        (void)_t845;
        ;
        ;
        Bool _t846 = I64_eq(pos, _t845);
        (void)_t846;
        ;
        if (_t846) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t847 = I64_to_u64(pos);
        (void)_t847;
        Str *_t848 = Str_substr(self, &(U64){start}, &(U64){_t847});
        (void)_t848;
        ;
        result = Str_concat(result, _t848);
        Str_delete(_t848, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t849 = I64_to_u64(pos);
        (void)_t849;
        ;
        U64 _t850 = U64_add(start, _t849);
        (void)_t850;
        ;
        U64 _t851 = U64_add(_t850, from->count);
        (void)_t851;
        ;
        start = _t851;
        ;
    }
    Bool _t856; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t856 = *_hp; free(_hp); }
    (void)_t856;
    if (_t856) {
        U64 _t852 = U64_sub(self->count, start);
        (void)_t852;
        Str *_t853 = Str_substr(self, &(U64){start}, &(U64){_t852});
        (void)_t853;
        ;
        result = Str_concat(result, _t853);
        Str_delete(_t853, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t857 = 1;
    (void)_t857;
    Str *_t858 = Str_substr(self, i, &(U64){_t857});
    (void)_t858;
    ;
    return _t858;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t861; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t861 = *_hp; free(_hp); }
    (void)_t861;
    if (_t861) {
        U64 _t859 = U64_sub(self->count, prefix->count);
        (void)_t859;
        Str *_t860 = Str_substr(self, &prefix->count, &(U64){_t859});
        (void)_t860;
        ;
        ;
        return _t860;
    }
    ;
    Str *_t862 = Str_clone(self);
    (void)_t862;
    return _t862;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t866; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t866 = *_hp; free(_hp); }
    (void)_t866;
    if (_t866) {
        U64 _t863 = 0;
        (void)_t863;
        U64 _t864 = U64_sub(self->count, suffix->count);
        (void)_t864;
        Str *_t865 = Str_substr(self, &(U64){_t863}, &(U64){_t864});
        (void)_t865;
        ;
        ;
        ;
        return _t865;
    }
    ;
    Str *_t867 = Str_clone(self);
    (void)_t867;
    return _t867;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t868 = 2;
    (void)_t868;
    U8 *buf = malloc(_t868);
    (void)buf;
    ;
    U64 _t869 = 1;
    (void)_t869;
    memcpy(buf, byte, _t869);
    ;
    U64 *_t870 = malloc(sizeof(U64));
    *_t870 = 1;
    (void)_t870;
    void *_t871 = ptr_add(buf, DEREF(_t870));
    (void)_t871;
    I32 _t872 = 0;
    (void)_t872;
    U64 _t873 = 1;
    (void)_t873;
    memset(_t871, _t872, _t873);
    U64_delete(_t870, &(Bool){1});
    ;
    ;
    I64 _t874 = 1;
    (void)_t874;
    I64 _t875 = 1;
    (void)_t875;
    Str *_t876 = malloc(sizeof(Str));
    _t876->c_str = buf;
    _t876->count = _t874;
    _t876->cap = _t875;
    (void)_t876;
    ;
    ;
    return _t876;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t916 = 0;
    (void)_t916;
    Bool _t917 = U64_eq(self->count, _t916);
    (void)_t917;
    ;
    if (_t917) {
        Str *_t877 = Str_lit("Str", 3ULL);
        (void)_t877;
        U64 _t878; { U64 *_hp = (U64 *)Str_size(); _t878 = *_hp; free(_hp); }
        (void)_t878;
        U64 _t879 = 1;
        (void)_t879;
        Array *_va15 = Array_new(_t877, &(U64){_t878}, &(U64){_t879});
        (void)_va15;
        Str_delete(_t877, &(Bool){1});
        ;
        ;
        U64 _t880 = 0;
        (void)_t880;
        Str *_t881 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t881;
        Array_set(_va15, &(U64){_t880}, _t881);
        ;
        Str *_t882 = Str_lit("/home/user/til/src/core/str.til:224:37", 38ULL);
        (void)_t882;
        panic(_t882, _va15);
        Str_delete(_t882, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    Bool neg = 0;
    (void)neg;
    U64 *_t918 = malloc(sizeof(U64));
    *_t918 = 0;
    (void)_t918;
    U8 *first = Str_get(self, _t918);
    (void)first;
    U8 _t919 = 45;
    (void)_t919;
    Bool _t920 = U8_eq(DEREF(first), _t919);
    (void)_t920;
    U64_delete(_t918, &(Bool){1});
    ;
    if (_t920) {
        Bool _t883 = 1;
        (void)_t883;
        neg = _t883;
        ;
        U64 _t884 = 1;
        (void)_t884;
        *i = _t884;
        ;
    }
    ;
    Bool _t921 = U64_eq(DEREF(i), self->count);
    (void)_t921;
    if (_t921) {
        Str *_t885 = Str_lit("Str", 3ULL);
        (void)_t885;
        U64 _t886; { U64 *_hp = (U64 *)Str_size(); _t886 = *_hp; free(_hp); }
        (void)_t886;
        U64 _t887 = 1;
        (void)_t887;
        Array *_va16 = Array_new(_t885, &(U64){_t886}, &(U64){_t887});
        (void)_va16;
        Str_delete(_t885, &(Bool){1});
        ;
        ;
        U64 _t888 = 0;
        (void)_t888;
        Str *_t889 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t889;
        Array_set(_va16, &(U64){_t888}, _t889);
        ;
        Str *_t890 = Str_lit("/home/user/til/src/core/str.til:233:37", 38ULL);
        (void)_t890;
        panic(_t890, _va16);
        Str_delete(_t890, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond891; { Bool *_hp = (Bool *)U64_lt(i, &self->count); _wcond891 = *_hp; free(_hp); }
        (void)_wcond891;
        if (_wcond891) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        (void)ch;
        I64 _t902 = U8_to_i64(DEREF(ch));
        (void)_t902;
        I64 _t903 = 48;
        (void)_t903;
        I64 d = I64_sub(_t902, _t903);
        (void)d;
        ;
        ;
        I64 _t904 = 0;
        (void)_t904;
        I64 _t905 = 9;
        (void)_t905;
        Bool _t906; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t904}); _t906 = *_hp; free(_hp); }
        (void)_t906;
        ;
        Bool _t907; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t905}); _t907 = *_hp; free(_hp); }
        (void)_t907;
        ;
        Bool _t908 = Bool_or(_t906, _t907);
        (void)_t908;
        ;
        ;
        if (_t908) {
            Str *_t892 = Str_lit("Str", 3ULL);
            (void)_t892;
            U64 _t893; { U64 *_hp = (U64 *)Str_size(); _t893 = *_hp; free(_hp); }
            (void)_t893;
            U64 _t894 = 3;
            (void)_t894;
            Array *_va17 = Array_new(_t892, &(U64){_t893}, &(U64){_t894});
            (void)_va17;
            Str_delete(_t892, &(Bool){1});
            ;
            ;
            U64 _t895 = 0;
            (void)_t895;
            Str *_t896 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
            (void)_t896;
            Array_set(_va17, &(U64){_t895}, _t896);
            ;
            U64 _t897 = 1;
            (void)_t897;
            Str *_t898 = Str_clone(self);
            (void)_t898;
            Array_set(_va17, &(U64){_t897}, _t898);
            ;
            U64 _t899 = 2;
            (void)_t899;
            Str *_t900 = Str_lit("'", 1ULL);
            (void)_t900;
            Array_set(_va17, &(U64){_t899}, _t900);
            ;
            Str *_t901 = Str_lit("/home/user/til/src/core/str.til:238:23", 38ULL);
            (void)_t901;
            panic(_t901, _va17);
            Str_delete(_t901, &(Bool){1});
        }
        ;
        I64 _t909 = 10;
        (void)_t909;
        I64 _t910 = I64_mul(result, _t909);
        (void)_t910;
        ;
        I64 _t911 = I64_add(_t910, d);
        (void)_t911;
        ;
        ;
        result = _t911;
        ;
        U64 _t912 = 1;
        (void)_t912;
        U64 _t913 = U64_add(DEREF(i), _t912);
        (void)_t913;
        ;
        *i = _t913;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t914 = 0;
        (void)_t914;
        I64 _t915 = I64_sub(_t914, result);
        (void)_t915;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t915; return _r; }
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
    I64 _t923; { I64 *_hp = (I64 *)Str_cmp(a, b); _t923 = *_hp; free(_hp); }
    (void)_t923;
    I64 _t924 = 0;
    (void)_t924;
    Bool _t925 = I64_eq(_t923, _t924);
    (void)_t925;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t925; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t926 = 0;
    (void)_t926;
    I64 _t927 = 1;
    (void)_t927;
    I64 _t928; { I64 *_hp = (I64 *)Str_cmp(a, b); _t928 = *_hp; free(_hp); }
    (void)_t928;
    I64 _t929 = I64_sub(_t926, _t927);
    (void)_t929;
    ;
    ;
    Bool _t930 = I64_eq(_t928, _t929);
    (void)_t930;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t930; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t931; { I64 *_hp = (I64 *)Str_cmp(a, b); _t931 = *_hp; free(_hp); }
    (void)_t931;
    I64 _t932 = 1;
    (void)_t932;
    Bool _t933 = I64_eq(_t931, _t932);
    (void)_t933;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t933; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t934; { Bool *_hp = (Bool *)Str_eq(a, b); _t934 = *_hp; free(_hp); }
    (void)_t934;
    Bool _t935 = Bool_not(_t934);
    (void)_t935;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t935; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t936; { Bool *_hp = (Bool *)Str_gt(a, b); _t936 = *_hp; free(_hp); }
    (void)_t936;
    Bool _t937 = Bool_not(_t936);
    (void)_t937;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t937; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t938; { Bool *_hp = (Bool *)Str_lt(a, b); _t938 = *_hp; free(_hp); }
    (void)_t938;
    Bool _t939 = Bool_not(_t938);
    (void)_t939;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t939; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t940 = malloc(DEREF(elem_size));
    (void)_t940;
    U64 _t941 = 0;
    (void)_t941;
    I64 _t942 = 1;
    (void)_t942;
    U64 _t943 = U64_clone(elem_size);
    (void)_t943;
    Vec *_t944 = malloc(sizeof(Vec));
    _t944->data = _t940;
    _t944->count = _t941;
    _t944->cap = _t942;
    _t944->elem_size = _t943;
    { Str *_ca = Str_clone(elem_type); _t944->elem_type = *_ca; free(_ca); }
    (void)_t944;
    ;
    ;
    ;
    return _t944;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t949 = U64_eq(self->count, self->cap);
    (void)_t949;
    if (_t949) {
        U64 _t945 = 2;
        (void)_t945;
        U64 new_cap = U64_mul(self->cap, _t945);
        (void)new_cap;
        ;
        U64 _t946 = U64_mul(new_cap, self->elem_size);
        (void)_t946;
        void *_t947 = realloc(self->data, _t946);
        (void)_t947;
        ;
        self->data = _t947;
        U64 _t948 = U64_clone(&(U64){new_cap});
        (void)_t948;
        ;
        self->cap = _t948;
        ;
    }
    ;
    U64 *_t950 = malloc(sizeof(U64)); *_t950 = U64_mul(self->count, self->elem_size);
    (void)_t950;
    void *_t951 = ptr_add(self->data, DEREF(_t950));
    (void)_t951;
    memcpy(_t951, val, self->elem_size);
    U64_delete(_t950, &(Bool){1});
    free(val);
    U64 _t952 = 1;
    (void)_t952;
    U64 _t953 = U64_add(self->count, _t952);
    (void)_t953;
    ;
    self->count = _t953;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t968; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t968 = *_hp; free(_hp); }
    (void)_t968;
    if (_t968) {
        Str *_t954 = Str_lit("Str", 3ULL);
        (void)_t954;
        U64 _t955; { U64 *_hp = (U64 *)Str_size(); _t955 = *_hp; free(_hp); }
        (void)_t955;
        U64 _t956 = 5;
        (void)_t956;
        Array *_va18 = Array_new(_t954, &(U64){_t955}, &(U64){_t956});
        (void)_va18;
        Str_delete(_t954, &(Bool){1});
        ;
        ;
        U64 _t957 = 0;
        (void)_t957;
        Str *_t958 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t958;
        Array_set(_va18, &(U64){_t957}, _t958);
        ;
        U64 _t959 = 1;
        (void)_t959;
        Str *_t960 = U64_to_str(DEREF(i));
        (void)_t960;
        Array_set(_va18, &(U64){_t959}, _t960);
        ;
        U64 _t961 = 2;
        (void)_t961;
        Str *_t962 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t962;
        Array_set(_va18, &(U64){_t961}, _t962);
        ;
        U64 _t963 = 3;
        (void)_t963;
        Str *_t964 = U64_to_str(self->count);
        (void)_t964;
        Array_set(_va18, &(U64){_t963}, _t964);
        ;
        U64 _t965 = 4;
        (void)_t965;
        Str *_t966 = Str_lit(")", 1ULL);
        (void)_t966;
        Array_set(_va18, &(U64){_t965}, _t966);
        ;
        Str *_t967 = Str_lit("/home/user/til/src/core/vec.til:31:19", 37ULL);
        (void)_t967;
        panic(_t967, _va18);
        Str_delete(_t967, &(Bool){1});
    }
    ;
    U64 *_t969 = malloc(sizeof(U64)); *_t969 = U64_mul(DEREF(i), self->elem_size);
    (void)_t969;
    void *_t970 = ptr_add(self->data, DEREF(_t969));
    (void)_t970;
    U64_delete(_t969, &(Bool){1});
    return _t970;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t984; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t984 = *_hp; free(_hp); }
    (void)_t984;
    Bool _t985 = Bool_not(_t984);
    (void)_t985;
    ;
    if (_t985) {
        {
            U64 _fi971 = 0;
            (void)_fi971;
            while (1) {
                U64 _t973 = 0;
                (void)_t973;
                Range *_t974 = Range_new(_t973, self->count);
                (void)_t974;
                ;
                U64 _t975; { U64 *_hp = (U64 *)Range_len(_t974); _t975 = *_hp; free(_hp); }
                (void)_t975;
                Range_delete(_t974, &(Bool){1});
                Bool _wcond972; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi971}, &(U64){_t975}); _wcond972 = *_hp; free(_hp); }
                (void)_wcond972;
                ;
                if (_wcond972) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t976 = 0;
                (void)_t976;
                Range *_t977 = Range_new(_t976, self->count);
                (void)_t977;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t977, _fi971); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t977, &(Bool){1});
                U64 _t978 = 1;
                (void)_t978;
                U64 _t979 = U64_add(_fi971, _t978);
                (void)_t979;
                ;
                _fi971 = _t979;
                ;
                U64 *_t980 = malloc(sizeof(U64)); *_t980 = U64_mul(i, self->elem_size);
                (void)_t980;
                ;
                void *_t981 = ptr_add(self->data, DEREF(_t980));
                (void)_t981;
                Bool _t982 = 0;
                (void)_t982;
                dyn_call_delete(&self->elem_type, _t981, &(Bool){_t982});
                U64_delete(_t980, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t986; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t986 = *_hp; free(_hp); }
    (void)_t986;
    Bool _t987 = Bool_not(_t986);
    (void)_t987;
    ;
    if (_t987) {
        Bool _t983 = 0;
        (void)_t983;
        Str_delete(&self->elem_type, &(Bool){_t983});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1001 = U64_mul(self->cap, self->elem_size);
    (void)_t1001;
    U8 *new_data = malloc(_t1001);
    (void)new_data;
    ;
    {
        U64 _fi988 = 0;
        (void)_fi988;
        while (1) {
            U64 _t990 = 0;
            (void)_t990;
            Range *_t991 = Range_new(_t990, self->count);
            (void)_t991;
            ;
            U64 _t992; { U64 *_hp = (U64 *)Range_len(_t991); _t992 = *_hp; free(_hp); }
            (void)_t992;
            Range_delete(_t991, &(Bool){1});
            Bool _wcond989; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi988}, &(U64){_t992}); _wcond989 = *_hp; free(_hp); }
            (void)_wcond989;
            ;
            if (_wcond989) {
            } else {
                ;
                break;
            }
            ;
            U64 _t993 = 0;
            (void)_t993;
            Range *_t994 = Range_new(_t993, self->count);
            (void)_t994;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t994, _fi988); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t994, &(Bool){1});
            U64 _t995 = 1;
            (void)_t995;
            U64 _t996 = U64_add(_fi988, _t995);
            (void)_t996;
            ;
            _fi988 = _t996;
            ;
            U64 *_t997 = malloc(sizeof(U64)); *_t997 = U64_mul(i, self->elem_size);
            (void)_t997;
            void *_t998 = ptr_add(self->data, DEREF(_t997));
            (void)_t998;
            void *cloned = dyn_call_clone(&self->elem_type, _t998);
            (void)cloned;
            U64_delete(_t997, &(Bool){1});
            U64 *_t999 = malloc(sizeof(U64)); *_t999 = U64_mul(i, self->elem_size);
            (void)_t999;
            ;
            void *_t1000 = ptr_add(new_data, DEREF(_t999));
            (void)_t1000;
            memcpy(_t1000, cloned, self->elem_size);
            U64_delete(_t999, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1002 = malloc(sizeof(Vec));
    _t1002->data = new_data;
    _t1002->count = self->count;
    _t1002->cap = self->cap;
    _t1002->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1002->elem_type = *_ca; free(_ca); }
    (void)_t1002;
    return _t1002;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1020 = Str_lit("Str", 3ULL);
    (void)_t1020;
    U64 _t1021; { U64 *_hp = (U64 *)Str_size(); _t1021 = *_hp; free(_hp); }
    (void)_t1021;
    Vec *parts = Vec_new(_t1020, &(U64){_t1021});
    (void)parts;
    Str_delete(_t1020, &(Bool){1});
    ;
    U64 _t1022; { U64 *_hp = (U64 *)Str_len(delim); _t1022 = *_hp; free(_hp); }
    (void)_t1022;
    U64 _t1023 = 0;
    (void)_t1023;
    Bool _t1024 = U64_eq(_t1022, _t1023);
    (void)_t1024;
    ;
    ;
    if (_t1024) {
        Str *_t1004 = Str_clone(s);
        (void)_t1004;
        Vec_push(parts, _t1004);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1014; { U64 *_hp = (U64 *)Str_len(s); _t1014 = *_hp; free(_hp); }
        (void)_t1014;
        U64 _t1015; { U64 *_hp = (U64 *)Str_len(delim); _t1015 = *_hp; free(_hp); }
        (void)_t1015;
        U64 _t1016 = U64_sub(_t1014, _t1015);
        (void)_t1016;
        ;
        ;
        Bool _wcond1005; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1016}); _wcond1005 = *_hp; free(_hp); }
        (void)_wcond1005;
        ;
        if (_wcond1005) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1017; { U64 *_hp = (U64 *)Str_len(delim); _t1017 = *_hp; free(_hp); }
        (void)_t1017;
        Str *_t1018 = Str_substr(s, &(U64){pos}, &(U64){_t1017});
        (void)_t1018;
        ;
        Bool _t1019; { Bool *_hp = (Bool *)Str_eq(_t1018, delim); _t1019 = *_hp; free(_hp); }
        (void)_t1019;
        Str_delete(_t1018, &(Bool){1});
        if (_t1019) {
            U64 _t1006 = U64_sub(pos, start);
            (void)_t1006;
            Str *_t1007 = Str_substr(s, &(U64){start}, &(U64){_t1006});
            (void)_t1007;
            ;
            Str *_t1008 = Str_clone(_t1007);
            (void)_t1008;
            Str_delete(_t1007, &(Bool){1});
            Vec_push(parts, _t1008);
            U64 _t1009; { U64 *_hp = (U64 *)Str_len(delim); _t1009 = *_hp; free(_hp); }
            (void)_t1009;
            U64 _t1010 = U64_add(pos, _t1009);
            (void)_t1010;
            ;
            start = _t1010;
            ;
            U64 _t1011 = U64_clone(&(U64){start});
            (void)_t1011;
            pos = _t1011;
            ;
        } else {
            U64 _t1012 = 1;
            (void)_t1012;
            U64 _t1013 = U64_add(pos, _t1012);
            (void)_t1013;
            ;
            pos = _t1013;
            ;
        }
        ;
    }
    ;
    U64 _t1025; { U64 *_hp = (U64 *)Str_len(s); _t1025 = *_hp; free(_hp); }
    (void)_t1025;
    U64 _t1026 = U64_sub(_t1025, start);
    (void)_t1026;
    ;
    Str *_t1027 = Str_substr(s, &(U64){start}, &(U64){_t1026});
    (void)_t1027;
    ;
    ;
    Str *_t1028 = Str_clone(_t1027);
    (void)_t1028;
    Str_delete(_t1027, &(Bool){1});
    Vec_push(parts, _t1028);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1036; { U64 *_hp = (U64 *)Vec_len(parts); _t1036 = *_hp; free(_hp); }
    (void)_t1036;
    U64 _t1037 = 0;
    (void)_t1037;
    Bool _t1038 = U64_eq(_t1036, _t1037);
    (void)_t1038;
    ;
    ;
    if (_t1038) {
        Str *_t1029 = Str_lit("", 0ULL);
        (void)_t1029;
        ;
        return _t1029;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1031; { U64 *_hp = (U64 *)Vec_len(parts); _t1031 = *_hp; free(_hp); }
        (void)_t1031;
        Bool _wcond1030; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1031}); _wcond1030 = *_hp; free(_hp); }
        (void)_wcond1030;
        ;
        if (_wcond1030) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1032 = 0;
        (void)_t1032;
        Bool _t1033; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1032}); _t1033 = *_hp; free(_hp); }
        (void)_t1033;
        ;
        if (_t1033) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        (void)p;
        result = Str_concat(result, p);
        U64 _t1034 = 1;
        (void)_t1034;
        U64 _t1035 = U64_add(DEREF(i), _t1034);
        (void)_t1035;
        ;
        *i = _t1035;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

Tuple * Tuple_new(void) {
    U64 _t1039 = 8;
    (void)_t1039;
    Str *_t1040 = Str_lit("Str", 3ULL);
    (void)_t1040;
    U64 _t1041; { U64 *_hp = (U64 *)Str_size(); _t1041 = *_hp; free(_hp); }
    (void)_t1041;
    Str *_t1042 = Str_lit("U64", 3ULL);
    (void)_t1042;
    U64 _t1043; { U64 *_hp = (U64 *)U64_size(); _t1043 = *_hp; free(_hp); }
    (void)_t1043;
    void *_t1044 = malloc(_t1039);
    (void)_t1044;
    ;
    U64 _t1045 = 0;
    (void)_t1045;
    I64 _t1046 = 8;
    (void)_t1046;
    Tuple *_t1047 = malloc(sizeof(Tuple));
    _t1047->data = _t1044;
    _t1047->total_size = _t1045;
    _t1047->cap = _t1046;
    { Vec *_ca = Vec_new(_t1040, &(U64){_t1041}); _t1047->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1042, &(U64){_t1043}); _t1047->type_sizes = *_ca; free(_ca); }
    (void)_t1047;
    Str_delete(_t1040, &(Bool){1});
    ;
    Str_delete(_t1042, &(Bool){1});
    ;
    ;
    ;
    return _t1047;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1048; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1048 = *_hp; free(_hp); }
    (void)_t1048;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1048; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1055; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1055 = *_hp; free(_hp); }
    (void)_t1055;
    if (_t1055) {
        U64 _t1052 = 2;
        (void)_t1052;
        U64 new_cap = U64_mul(self->cap, _t1052);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1049; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1049 = *_hp; free(_hp); }
            (void)_wcond1049;
            if (_wcond1049) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1050 = 2;
            (void)_t1050;
            U64 _t1051 = U64_mul(new_cap, _t1050);
            (void)_t1051;
            ;
            new_cap = _t1051;
            ;
        }
        void *_t1053 = realloc(self->data, new_cap);
        (void)_t1053;
        self->data = _t1053;
        U64 _t1054 = U64_clone(&(U64){new_cap});
        (void)_t1054;
        ;
        self->cap = _t1054;
        ;
    }
    ;
    void *_t1056 = ptr_add(self->data, self->total_size);
    (void)_t1056;
    memcpy(_t1056, val, DEREF(elem_size));
    free(val);
    Str *_t1057 = Str_clone(elem_type);
    (void)_t1057;
    Vec_push(&self->type_names, _t1057);
    U64 _t1058 = U64_clone(elem_size);
    (void)_t1058;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1058; _oa; }));
    U64 _t1059 = U64_clone(&(U64){new_total});
    (void)_t1059;
    ;
    self->total_size = _t1059;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1079; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1079 = *_hp; free(_hp); }
    (void)_t1079;
    Bool _t1080; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1079}); _t1080 = *_hp; free(_hp); }
    (void)_t1080;
    ;
    if (_t1080) {
        Str *_t1060 = Str_lit("Str", 3ULL);
        (void)_t1060;
        U64 _t1061; { U64 *_hp = (U64 *)Str_size(); _t1061 = *_hp; free(_hp); }
        (void)_t1061;
        U64 _t1062 = 5;
        (void)_t1062;
        Array *_va19 = Array_new(_t1060, &(U64){_t1061}, &(U64){_t1062});
        (void)_va19;
        Str_delete(_t1060, &(Bool){1});
        ;
        ;
        U64 _t1063 = 0;
        (void)_t1063;
        Str *_t1064 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1064;
        Array_set(_va19, &(U64){_t1063}, _t1064);
        ;
        U64 _t1065 = 1;
        (void)_t1065;
        Str *_t1066 = U64_to_str(DEREF(i));
        (void)_t1066;
        Array_set(_va19, &(U64){_t1065}, _t1066);
        ;
        U64 _t1067 = 2;
        (void)_t1067;
        Str *_t1068 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1068;
        Array_set(_va19, &(U64){_t1067}, _t1068);
        ;
        U64 _t1069; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1069 = *_hp; free(_hp); }
        (void)_t1069;
        U64 _t1070 = 3;
        (void)_t1070;
        Str *_t1071 = U64_to_str(_t1069);
        (void)_t1071;
        ;
        Array_set(_va19, &(U64){_t1070}, _t1071);
        ;
        U64 _t1072 = 4;
        (void)_t1072;
        Str *_t1073 = Str_lit(")", 1ULL);
        (void)_t1073;
        Array_set(_va19, &(U64){_t1072}, _t1073);
        ;
        Str *_t1074 = Str_lit("/home/user/til/src/core/tuple.til:36:19", 39ULL);
        (void)_t1074;
        panic(_t1074, _va19);
        Str_delete(_t1074, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *j = malloc(sizeof(U64));
    *j = 0;
    (void)j;
    while (1) {
        Bool _wcond1075; { Bool *_hp = (Bool *)U64_lt(j, i); _wcond1075 = *_hp; free(_hp); }
        (void)_wcond1075;
        if (_wcond1075) {
        } else {
            ;
            break;
        }
        ;
        U64 *sz = Vec_get(&self->type_sizes, j);
        (void)sz;
        U64 _t1076 = U64_add(DEREF(offset), DEREF(sz));
        (void)_t1076;
        *offset = _t1076;
        ;
        U64 _t1077 = 1;
        (void)_t1077;
        U64 _t1078 = U64_add(DEREF(j), _t1077);
        (void)_t1078;
        ;
        *j = _t1078;
        ;
    }
    U64_delete(j, &(Bool){1});
    void *_t1081 = ptr_add(self->data, DEREF(offset));
    (void)_t1081;
    U64_delete(offset, &(Bool){1});
    return _t1081;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1082 = Vec_get(&self->type_names, i);
    (void)_t1082;
    return _t1082;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1083 = Vec_get(&self->type_sizes, i);
    (void)_t1083;
    return _t1083;
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
        U64 _t1085; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1085 = *_hp; free(_hp); }
        (void)_t1085;
        Bool _wcond1084; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1085}); _wcond1084 = *_hp; free(_hp); }
        (void)_wcond1084;
        ;
        if (_wcond1084) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1086 = ptr_add(self->data, DEREF(offset));
        (void)_t1086;
        Bool _t1087 = 0;
        (void)_t1087;
        dyn_call_delete(tn, _t1086, &(Bool){_t1087});
        ;
        U64 _t1088 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1088;
        *offset = _t1088;
        ;
        U64 _t1089 = 1;
        (void)_t1089;
        U64 _t1090 = U64_add(DEREF(i), _t1089);
        (void)_t1090;
        ;
        *i = _t1090;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1091 = 0;
    (void)_t1091;
    Vec_delete(&self->type_names, &(Bool){_t1091});
    ;
    Bool _t1092 = 0;
    (void)_t1092;
    Vec_delete(&self->type_sizes, &(Bool){_t1092});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1102 = 0;
    (void)_t1102;
    Bool _t1103 = U64_eq(new_cap, _t1102);
    (void)_t1103;
    ;
    if (_t1103) {
        I64 _t1093 = 8;
        (void)_t1093;
        U64 _t1094; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1093}); _t1094 = *_hp; free(_hp); }
        (void)_t1094;
        ;
        new_cap = _t1094;
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
        U64 _t1096; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1096 = *_hp; free(_hp); }
        (void)_t1096;
        Bool _wcond1095; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1096}); _wcond1095 = *_hp; free(_hp); }
        (void)_wcond1095;
        ;
        if (_wcond1095) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1097 = ptr_add(self->data, DEREF(offset));
        (void)_t1097;
        void *cloned = dyn_call_clone(tn, _t1097);
        (void)cloned;
        void *_t1098 = ptr_add(new_data, DEREF(offset));
        (void)_t1098;
        memcpy(_t1098, cloned, DEREF(ts));
        free(cloned);
        U64 _t1099 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1099;
        *offset = _t1099;
        ;
        U64 _t1100 = 1;
        (void)_t1100;
        U64 _t1101 = U64_add(DEREF(i), _t1100);
        (void)_t1101;
        ;
        *i = _t1101;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    U64 _t1104 = U64_clone(&(U64){new_cap});
    (void)_t1104;
    ;
    Vec *_t1105 = Vec_clone(&self->type_names);
    (void)_t1105;
    Vec *_t1106 = Vec_clone(&self->type_sizes);
    (void)_t1106;
    Tuple *_t1107 = malloc(sizeof(Tuple));
    _t1107->data = new_data;
    _t1107->total_size = self->total_size;
    _t1107->cap = _t1104;
    { Vec *_ca = Vec_clone(_t1105); _t1107->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1106); _t1107->type_sizes = *_ca; free(_ca); }
    (void)_t1107;
    ;
    Vec_delete(_t1105, &(Bool){1});
    Vec_delete(_t1106, &(Bool){1});
    return _t1107;
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
TokenType *TokenType_DotDotDot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_DotDotDot };
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
Bool *TokenType_is_DotDotDot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_DotDotDot);
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
    Bool _t1175; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1175 = *_hp; free(_hp); }
    (void)_t1175;
    if (_t1175) {
        Bool _t1109; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1109 = *_hp; free(_hp); }
        (void)_t1109;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1176; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1176 = *_hp; free(_hp); }
    (void)_t1176;
    if (_t1176) {
        Bool _t1110; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1110 = *_hp; free(_hp); }
        (void)_t1110;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1177; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1177 = *_hp; free(_hp); }
    (void)_t1177;
    if (_t1177) {
        Bool _t1111; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1111 = *_hp; free(_hp); }
        (void)_t1111;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1178 = *_hp; free(_hp); }
    (void)_t1178;
    if (_t1178) {
        Bool _t1112; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1112 = *_hp; free(_hp); }
        (void)_t1112;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1179 = *_hp; free(_hp); }
    (void)_t1179;
    if (_t1179) {
        Bool _t1113; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1113 = *_hp; free(_hp); }
        (void)_t1113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1180 = *_hp; free(_hp); }
    (void)_t1180;
    if (_t1180) {
        Bool _t1114; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1114 = *_hp; free(_hp); }
        (void)_t1114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1181 = *_hp; free(_hp); }
    (void)_t1181;
    if (_t1181) {
        Bool _t1115; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1115 = *_hp; free(_hp); }
        (void)_t1115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    if (_t1182) {
        Bool _t1116; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1116 = *_hp; free(_hp); }
        (void)_t1116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1183 = *_hp; free(_hp); }
    (void)_t1183;
    if (_t1183) {
        Bool _t1117; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1117 = *_hp; free(_hp); }
        (void)_t1117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1184 = *_hp; free(_hp); }
    (void)_t1184;
    if (_t1184) {
        Bool _t1118; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1118 = *_hp; free(_hp); }
        (void)_t1118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    if (_t1185) {
        Bool _t1119; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1119 = *_hp; free(_hp); }
        (void)_t1119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1186 = *_hp; free(_hp); }
    (void)_t1186;
    if (_t1186) {
        Bool _t1120; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1120 = *_hp; free(_hp); }
        (void)_t1120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1187 = *_hp; free(_hp); }
    (void)_t1187;
    if (_t1187) {
        Bool _t1121; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1121 = *_hp; free(_hp); }
        (void)_t1121;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1188 = *_hp; free(_hp); }
    (void)_t1188;
    if (_t1188) {
        Bool _t1122; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1122 = *_hp; free(_hp); }
        (void)_t1122;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        Bool _t1123; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1123 = *_hp; free(_hp); }
        (void)_t1123;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1190 = *_hp; free(_hp); }
    (void)_t1190;
    if (_t1190) {
        Bool _t1124; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1124 = *_hp; free(_hp); }
        (void)_t1124;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1191 = *_hp; free(_hp); }
    (void)_t1191;
    if (_t1191) {
        Bool _t1125; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1125 = *_hp; free(_hp); }
        (void)_t1125;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        Bool _t1126; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t1126 = *_hp; free(_hp); }
        (void)_t1126;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1193 = *_hp; free(_hp); }
    (void)_t1193;
    if (_t1193) {
        Bool _t1127; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1127 = *_hp; free(_hp); }
        (void)_t1127;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1194 = *_hp; free(_hp); }
    (void)_t1194;
    if (_t1194) {
        Bool _t1128; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1128 = *_hp; free(_hp); }
        (void)_t1128;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1195 = *_hp; free(_hp); }
    (void)_t1195;
    if (_t1195) {
        Bool _t1129; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1129 = *_hp; free(_hp); }
        (void)_t1129;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1196 = *_hp; free(_hp); }
    (void)_t1196;
    if (_t1196) {
        Bool _t1130; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1130 = *_hp; free(_hp); }
        (void)_t1130;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1197 = *_hp; free(_hp); }
    (void)_t1197;
    if (_t1197) {
        Bool _t1131; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1131 = *_hp; free(_hp); }
        (void)_t1131;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1198 = *_hp; free(_hp); }
    (void)_t1198;
    if (_t1198) {
        Bool _t1132; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1132 = *_hp; free(_hp); }
        (void)_t1132;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1199 = *_hp; free(_hp); }
    (void)_t1199;
    if (_t1199) {
        Bool _t1133; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1133 = *_hp; free(_hp); }
        (void)_t1133;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1200 = *_hp; free(_hp); }
    (void)_t1200;
    if (_t1200) {
        Bool _t1134; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1134 = *_hp; free(_hp); }
        (void)_t1134;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1201 = *_hp; free(_hp); }
    (void)_t1201;
    if (_t1201) {
        Bool _t1135; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1135 = *_hp; free(_hp); }
        (void)_t1135;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1136; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1136 = *_hp; free(_hp); }
        (void)_t1136;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1137; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1137 = *_hp; free(_hp); }
        (void)_t1137;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1138; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1138 = *_hp; free(_hp); }
        (void)_t1138;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1139; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1139 = *_hp; free(_hp); }
        (void)_t1139;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1139; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1140; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1140 = *_hp; free(_hp); }
        (void)_t1140;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1140; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1141; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1141; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1142; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1142; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1143; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1143 = *_hp; free(_hp); }
        (void)_t1143;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1143; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1144; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1144; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1145; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1145; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1146; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1146; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1147; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1147 = *_hp; free(_hp); }
        (void)_t1147;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1147; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1148; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1148 = *_hp; free(_hp); }
        (void)_t1148;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1148; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1149; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1149; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1150; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1150 = *_hp; free(_hp); }
        (void)_t1150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1150; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1151; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1151 = *_hp; free(_hp); }
        (void)_t1151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1151; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1218 = *_hp; free(_hp); }
    (void)_t1218;
    if (_t1218) {
        Bool _t1152; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1152 = *_hp; free(_hp); }
        (void)_t1152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1152; return _r; }
    }
    ;
    Bool _t1219; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    if (_t1219) {
        Bool _t1153; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1153 = *_hp; free(_hp); }
        (void)_t1153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1153; return _r; }
    }
    ;
    Bool _t1220; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        Bool _t1154; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1154 = *_hp; free(_hp); }
        (void)_t1154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1154; return _r; }
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        Bool _t1155; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1155 = *_hp; free(_hp); }
        (void)_t1155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1155; return _r; }
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        Bool _t1156; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1156 = *_hp; free(_hp); }
        (void)_t1156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1156; return _r; }
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        Bool _t1157; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1157 = *_hp; free(_hp); }
        (void)_t1157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1157; return _r; }
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        Bool _t1158; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1158 = *_hp; free(_hp); }
        (void)_t1158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1158; return _r; }
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        Bool _t1159; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1159 = *_hp; free(_hp); }
        (void)_t1159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1159; return _r; }
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        Bool _t1160; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1160 = *_hp; free(_hp); }
        (void)_t1160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1160; return _r; }
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        Bool _t1161; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1161 = *_hp; free(_hp); }
        (void)_t1161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1161; return _r; }
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        Bool _t1162; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1162 = *_hp; free(_hp); }
        (void)_t1162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1162; return _r; }
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        Bool _t1163; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1163 = *_hp; free(_hp); }
        (void)_t1163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1163; return _r; }
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        Bool _t1164; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1164 = *_hp; free(_hp); }
        (void)_t1164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1164; return _r; }
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        Bool _t1165; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1165 = *_hp; free(_hp); }
        (void)_t1165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1165; return _r; }
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        Bool _t1166; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1166 = *_hp; free(_hp); }
        (void)_t1166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1166; return _r; }
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        Bool _t1167; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        Bool _t1168; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1168 = *_hp; free(_hp); }
        (void)_t1168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1168; return _r; }
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Bool _t1169; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1169 = *_hp; free(_hp); }
        (void)_t1169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1169; return _r; }
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Bool _t1170; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1170 = *_hp; free(_hp); }
        (void)_t1170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1170; return _r; }
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Bool _t1171; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1171 = *_hp; free(_hp); }
        (void)_t1171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1171; return _r; }
    }
    ;
    Bool _t1238; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1238 = *_hp; free(_hp); }
    (void)_t1238;
    if (_t1238) {
        Bool _t1172; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1172 = *_hp; free(_hp); }
        (void)_t1172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1172; return _r; }
    }
    ;
    Bool _t1239; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        Bool _t1173; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1173 = *_hp; free(_hp); }
        (void)_t1173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1173; return _r; }
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        Bool _t1174; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1174 = *_hp; free(_hp); }
        (void)_t1174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1174; return _r; }
    }
    ;
    Bool _t1241 = 0;
    (void)_t1241;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1241; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1242; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1242 = *_hp; free(_hp); }
    (void)_t1242;
    if (_t1242) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1243; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1243 = *_hp; free(_hp); }
    (void)_t1243;
    if (_t1243) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1246 = *_hp; free(_hp); }
    (void)_t1246;
    if (_t1246) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        ;
        return TokenType_DotDotDot();
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
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Str *_t1307 = Str_lit("Eof", 3ULL);
        (void)_t1307;
        ;
        return _t1307;
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Str *_t1308 = Str_lit("LParen", 6ULL);
        (void)_t1308;
        ;
        return _t1308;
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Str *_t1309 = Str_lit("RParen", 6ULL);
        (void)_t1309;
        ;
        return _t1309;
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Str *_t1310 = Str_lit("LBrace", 6ULL);
        (void)_t1310;
        ;
        return _t1310;
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Str *_t1311 = Str_lit("RBrace", 6ULL);
        (void)_t1311;
        ;
        return _t1311;
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Str *_t1312 = Str_lit("LBracket", 8ULL);
        (void)_t1312;
        ;
        return _t1312;
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Str *_t1313 = Str_lit("RBracket", 8ULL);
        (void)_t1313;
        ;
        return _t1313;
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Str *_t1314 = Str_lit("Comma", 5ULL);
        (void)_t1314;
        ;
        return _t1314;
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Str *_t1315 = Str_lit("Colon", 5ULL);
        (void)_t1315;
        ;
        return _t1315;
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Str *_t1316 = Str_lit("Question", 8ULL);
        (void)_t1316;
        ;
        return _t1316;
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Str *_t1317 = Str_lit("Bang", 4ULL);
        (void)_t1317;
        ;
        return _t1317;
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Str *_t1318 = Str_lit("Minus", 5ULL);
        (void)_t1318;
        ;
        return _t1318;
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Str *_t1319 = Str_lit("Plus", 4ULL);
        (void)_t1319;
        ;
        return _t1319;
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Str *_t1320 = Str_lit("Star", 4ULL);
        (void)_t1320;
        ;
        return _t1320;
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Str *_t1321 = Str_lit("Slash", 5ULL);
        (void)_t1321;
        ;
        return _t1321;
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Str *_t1322 = Str_lit("Dot", 3ULL);
        (void)_t1322;
        ;
        return _t1322;
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Str *_t1323 = Str_lit("DotDot", 6ULL);
        (void)_t1323;
        ;
        return _t1323;
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Str *_t1324 = Str_lit("DotDotDot", 9ULL);
        (void)_t1324;
        ;
        return _t1324;
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Str *_t1325 = Str_lit("Eq", 2ULL);
        (void)_t1325;
        ;
        return _t1325;
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Str *_t1326 = Str_lit("EqEq", 4ULL);
        (void)_t1326;
        ;
        return _t1326;
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Str *_t1327 = Str_lit("Neq", 3ULL);
        (void)_t1327;
        ;
        return _t1327;
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Str *_t1328 = Str_lit("Lt", 2ULL);
        (void)_t1328;
        ;
        return _t1328;
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Str *_t1329 = Str_lit("LtEq", 4ULL);
        (void)_t1329;
        ;
        return _t1329;
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Str *_t1330 = Str_lit("Gt", 2ULL);
        (void)_t1330;
        ;
        return _t1330;
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Str *_t1331 = Str_lit("GtEq", 4ULL);
        (void)_t1331;
        ;
        return _t1331;
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        Str *_t1332 = Str_lit("ColonEq", 7ULL);
        (void)_t1332;
        ;
        return _t1332;
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        Str *_t1333 = Str_lit("Ident", 5ULL);
        (void)_t1333;
        ;
        return _t1333;
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        Str *_t1334 = Str_lit("StringTok", 9ULL);
        (void)_t1334;
        ;
        return _t1334;
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        Str *_t1335 = Str_lit("Number", 6ULL);
        (void)_t1335;
        ;
        return _t1335;
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        Str *_t1336 = Str_lit("Char", 4ULL);
        (void)_t1336;
        ;
        return _t1336;
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        Str *_t1337 = Str_lit("KwMode", 6ULL);
        (void)_t1337;
        ;
        return _t1337;
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        Str *_t1338 = Str_lit("KwMut", 5ULL);
        (void)_t1338;
        ;
        return _t1338;
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        Str *_t1339 = Str_lit("KwOwn", 5ULL);
        (void)_t1339;
        ;
        return _t1339;
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        Str *_t1340 = Str_lit("KwRef", 5ULL);
        (void)_t1340;
        ;
        return _t1340;
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        Str *_t1341 = Str_lit("KwShallow", 9ULL);
        (void)_t1341;
        ;
        return _t1341;
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        Str *_t1342 = Str_lit("KwStruct", 8ULL);
        (void)_t1342;
        ;
        return _t1342;
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        Str *_t1343 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        Str *_t1344 = Str_lit("KwEnum", 6ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        Str *_t1345 = Str_lit("KwNamespace", 11ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        Str *_t1346 = Str_lit("KwFunc", 6ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        Str *_t1347 = Str_lit("KwProc", 6ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        Str *_t1348 = Str_lit("KwTest", 6ULL);
        (void)_t1348;
        ;
        return _t1348;
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        Str *_t1349 = Str_lit("KwMacro", 7ULL);
        (void)_t1349;
        ;
        return _t1349;
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        Str *_t1350 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1350;
        ;
        return _t1350;
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        Str *_t1351 = Str_lit("KwExtProc", 9ULL);
        (void)_t1351;
        ;
        return _t1351;
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        Str *_t1352 = Str_lit("KwReturns", 9ULL);
        (void)_t1352;
        ;
        return _t1352;
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        Str *_t1353 = Str_lit("KwThrows", 8ULL);
        (void)_t1353;
        ;
        return _t1353;
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        Str *_t1354 = Str_lit("KwIf", 4ULL);
        (void)_t1354;
        ;
        return _t1354;
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        Str *_t1355 = Str_lit("KwElse", 6ULL);
        (void)_t1355;
        ;
        return _t1355;
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        Str *_t1356 = Str_lit("KwWhile", 7ULL);
        (void)_t1356;
        ;
        return _t1356;
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        Str *_t1357 = Str_lit("KwFor", 5ULL);
        (void)_t1357;
        ;
        return _t1357;
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        Str *_t1358 = Str_lit("KwIn", 4ULL);
        (void)_t1358;
        ;
        return _t1358;
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        Str *_t1359 = Str_lit("KwSwitch", 8ULL);
        (void)_t1359;
        ;
        return _t1359;
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        Str *_t1360 = Str_lit("KwMatch", 7ULL);
        (void)_t1360;
        ;
        return _t1360;
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        Str *_t1361 = Str_lit("KwCase", 6ULL);
        (void)_t1361;
        ;
        return _t1361;
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        Str *_t1362 = Str_lit("KwDefault", 9ULL);
        (void)_t1362;
        ;
        return _t1362;
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        Str *_t1363 = Str_lit("KwReturn", 8ULL);
        (void)_t1363;
        ;
        return _t1363;
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        Str *_t1364 = Str_lit("KwThrow", 7ULL);
        (void)_t1364;
        ;
        return _t1364;
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        Str *_t1365 = Str_lit("KwCatch", 7ULL);
        (void)_t1365;
        ;
        return _t1365;
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        Str *_t1366 = Str_lit("KwBreak", 7ULL);
        (void)_t1366;
        ;
        return _t1366;
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        Str *_t1367 = Str_lit("KwContinue", 10ULL);
        (void)_t1367;
        ;
        return _t1367;
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        Str *_t1368 = Str_lit("KwDefer", 7ULL);
        (void)_t1368;
        ;
        return _t1368;
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        Str *_t1369 = Str_lit("KwTrue", 6ULL);
        (void)_t1369;
        ;
        return _t1369;
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        Str *_t1370 = Str_lit("KwFalse", 7ULL);
        (void)_t1370;
        ;
        return _t1370;
    }
    ;
    Bool _t1437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1437 = *_hp; free(_hp); }
    (void)_t1437;
    if (_t1437) {
        Str *_t1371 = Str_lit("KwNull", 6ULL);
        (void)_t1371;
        ;
        return _t1371;
    }
    ;
    Bool _t1438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1438 = *_hp; free(_hp); }
    (void)_t1438;
    if (_t1438) {
        Str *_t1372 = Str_lit("Error", 5ULL);
        (void)_t1372;
        ;
        return _t1372;
    }
    ;
    Str *_t1439 = Str_lit("unknown", 7ULL);
    (void)_t1439;
    return _t1439;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1441 = I64_clone(&self->line);
    (void)_t1441;
    I64 _t1442 = I64_clone(&self->col);
    (void)_t1442;
    Token *_t1443 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1443->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1443->text = *_ca; free(_ca); }
    _t1443->line = _t1441;
    _t1443->col = _t1442;
    (void)_t1443;
    ;
    ;
    return _t1443;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1444 = 0;
    (void)_t1444;
    TokenType_delete(&self->type, &(Bool){_t1444});
    ;
    Bool _t1445 = 0;
    (void)_t1445;
    Str_delete(&self->text, &(Bool){_t1445});
    ;
    Bool _t1446 = 0;
    (void)_t1446;
    I64_delete(&self->line, &(Bool){_t1446});
    ;
    Bool _t1447 = 0;
    (void)_t1447;
    I64_delete(&self->col, &(Bool){_t1447});
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
    U8 _t1449 = 48;
    (void)_t1449;
    U8 _t1450 = 57;
    (void)_t1450;
    Bool _t1451; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1449}); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    ;
    Bool _t1452; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1450}); _t1452 = *_hp; free(_hp); }
    (void)_t1452;
    ;
    Bool _t1453 = Bool_and(_t1451, _t1452);
    (void)_t1453;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1453; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1454 = 97;
    (void)_t1454;
    U8 _t1455 = 122;
    (void)_t1455;
    Bool _t1456; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1454}); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    ;
    Bool _t1457; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1455}); _t1457 = *_hp; free(_hp); }
    (void)_t1457;
    ;
    U8 _t1458 = 65;
    (void)_t1458;
    U8 _t1459 = 90;
    (void)_t1459;
    Bool _t1460; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1458}); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    ;
    Bool _t1461; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1459}); _t1461 = *_hp; free(_hp); }
    (void)_t1461;
    ;
    Bool _t1462 = Bool_and(_t1456, _t1457);
    (void)_t1462;
    ;
    ;
    Bool _t1463 = Bool_and(_t1460, _t1461);
    (void)_t1463;
    ;
    ;
    U8 _t1464 = 95;
    (void)_t1464;
    Bool _t1465 = Bool_or(_t1462, _t1463);
    (void)_t1465;
    ;
    ;
    Bool _t1466 = U8_eq(DEREF(c), _t1464);
    (void)_t1466;
    ;
    Bool _t1467 = Bool_or(_t1465, _t1466);
    (void)_t1467;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1467; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1468; { Bool *_hp = (Bool *)is_alpha(c); _t1468 = *_hp; free(_hp); }
    (void)_t1468;
    Bool _t1469; { Bool *_hp = (Bool *)is_digit(c); _t1469 = *_hp; free(_hp); }
    (void)_t1469;
    Bool _t1470 = Bool_or(_t1468, _t1469);
    (void)_t1470;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1470; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1471 = TokenType_clone(type);
        (void)_sw1471;
        Bool _t1604; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Eof()); _t1604 = *_hp; free(_hp); }
        (void)_t1604;
        if (_t1604) {
            Str *_t1472 = Str_lit("eof", 3ULL);
            (void)_t1472;
            TokenType_delete(_sw1471, &(Bool){1});
            ;
            return _t1472;
        } else {
            Bool _t1603; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_LParen()); _t1603 = *_hp; free(_hp); }
            (void)_t1603;
            if (_t1603) {
                Str *_t1473 = Str_lit("(", 1ULL);
                (void)_t1473;
                ;
                TokenType_delete(_sw1471, &(Bool){1});
                ;
                return _t1473;
            } else {
                Bool _t1602; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_RParen()); _t1602 = *_hp; free(_hp); }
                (void)_t1602;
                if (_t1602) {
                    Str *_t1474 = Str_lit(")", 1ULL);
                    (void)_t1474;
                    ;
                    ;
                    TokenType_delete(_sw1471, &(Bool){1});
                    ;
                    return _t1474;
                } else {
                    Bool _t1601; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_LBrace()); _t1601 = *_hp; free(_hp); }
                    (void)_t1601;
                    if (_t1601) {
                        Str *_t1475 = Str_lit("{", 1ULL);
                        (void)_t1475;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1471, &(Bool){1});
                        ;
                        return _t1475;
                    } else {
                        Bool _t1600; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_RBrace()); _t1600 = *_hp; free(_hp); }
                        (void)_t1600;
                        if (_t1600) {
                            Str *_t1476 = Str_lit("}", 1ULL);
                            (void)_t1476;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1471, &(Bool){1});
                            ;
                            return _t1476;
                        } else {
                            Bool _t1599; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_LBracket()); _t1599 = *_hp; free(_hp); }
                            (void)_t1599;
                            if (_t1599) {
                                Str *_t1477 = Str_lit("[", 1ULL);
                                (void)_t1477;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1471, &(Bool){1});
                                ;
                                return _t1477;
                            } else {
                                Bool _t1598; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_RBracket()); _t1598 = *_hp; free(_hp); }
                                (void)_t1598;
                                if (_t1598) {
                                    Str *_t1478 = Str_lit("]", 1ULL);
                                    (void)_t1478;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1471, &(Bool){1});
                                    ;
                                    return _t1478;
                                } else {
                                    Bool _t1597; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Comma()); _t1597 = *_hp; free(_hp); }
                                    (void)_t1597;
                                    if (_t1597) {
                                        Str *_t1479 = Str_lit(",", 1ULL);
                                        (void)_t1479;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1471, &(Bool){1});
                                        ;
                                        return _t1479;
                                    } else {
                                        Bool _t1596; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Colon()); _t1596 = *_hp; free(_hp); }
                                        (void)_t1596;
                                        if (_t1596) {
                                            Str *_t1480 = Str_lit(":", 1ULL);
                                            (void)_t1480;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1471, &(Bool){1});
                                            ;
                                            return _t1480;
                                        } else {
                                            Bool _t1595; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Question()); _t1595 = *_hp; free(_hp); }
                                            (void)_t1595;
                                            if (_t1595) {
                                                Str *_t1481 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw1471, &(Bool){1});
                                                ;
                                                return _t1481;
                                            } else {
                                                Bool _t1594; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Bang()); _t1594 = *_hp; free(_hp); }
                                                (void)_t1594;
                                                if (_t1594) {
                                                    Str *_t1482 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                    ;
                                                    return _t1482;
                                                } else {
                                                    Bool _t1593; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Minus()); _t1593 = *_hp; free(_hp); }
                                                    (void)_t1593;
                                                    if (_t1593) {
                                                        Str *_t1483 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                        ;
                                                        return _t1483;
                                                    } else {
                                                        Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Plus()); _t1592 = *_hp; free(_hp); }
                                                        (void)_t1592;
                                                        if (_t1592) {
                                                            Str *_t1484 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                            ;
                                                            return _t1484;
                                                        } else {
                                                            Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Star()); _t1591 = *_hp; free(_hp); }
                                                            (void)_t1591;
                                                            if (_t1591) {
                                                                Str *_t1485 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                ;
                                                                return _t1485;
                                                            } else {
                                                                Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Slash()); _t1590 = *_hp; free(_hp); }
                                                                (void)_t1590;
                                                                if (_t1590) {
                                                                    Str *_t1486 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                    ;
                                                                    return _t1486;
                                                                } else {
                                                                    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Dot()); _t1589 = *_hp; free(_hp); }
                                                                    (void)_t1589;
                                                                    if (_t1589) {
                                                                        Str *_t1487 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                        ;
                                                                        return _t1487;
                                                                    } else {
                                                                        Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_DotDot()); _t1588 = *_hp; free(_hp); }
                                                                        (void)_t1588;
                                                                        if (_t1588) {
                                                                            Str *_t1488 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                            ;
                                                                            return _t1488;
                                                                        } else {
                                                                            Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_DotDotDot()); _t1587 = *_hp; free(_hp); }
                                                                            (void)_t1587;
                                                                            if (_t1587) {
                                                                                Str *_t1489 = Str_lit("...", 3ULL);
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
                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                ;
                                                                                return _t1489;
                                                                            } else {
                                                                                Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Eq()); _t1586 = *_hp; free(_hp); }
                                                                                (void)_t1586;
                                                                                if (_t1586) {
                                                                                    Str *_t1490 = Str_lit("=", 1ULL);
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
                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                    ;
                                                                                    return _t1490;
                                                                                } else {
                                                                                    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_EqEq()); _t1585 = *_hp; free(_hp); }
                                                                                    (void)_t1585;
                                                                                    if (_t1585) {
                                                                                        Str *_t1491 = Str_lit("==", 2ULL);
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
                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                        ;
                                                                                        return _t1491;
                                                                                    } else {
                                                                                        Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Neq()); _t1584 = *_hp; free(_hp); }
                                                                                        (void)_t1584;
                                                                                        if (_t1584) {
                                                                                            Str *_t1492 = Str_lit("!=", 2ULL);
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
                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                            ;
                                                                                            return _t1492;
                                                                                        } else {
                                                                                            Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Lt()); _t1583 = *_hp; free(_hp); }
                                                                                            (void)_t1583;
                                                                                            if (_t1583) {
                                                                                                Str *_t1493 = Str_lit("<", 1ULL);
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
                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                ;
                                                                                                return _t1493;
                                                                                            } else {
                                                                                                Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_LtEq()); _t1582 = *_hp; free(_hp); }
                                                                                                (void)_t1582;
                                                                                                if (_t1582) {
                                                                                                    Str *_t1494 = Str_lit("<=", 2ULL);
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
                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1494;
                                                                                                } else {
                                                                                                    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Gt()); _t1581 = *_hp; free(_hp); }
                                                                                                    (void)_t1581;
                                                                                                    if (_t1581) {
                                                                                                        Str *_t1495 = Str_lit(">", 1ULL);
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
                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1495;
                                                                                                    } else {
                                                                                                        Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_GtEq()); _t1580 = *_hp; free(_hp); }
                                                                                                        (void)_t1580;
                                                                                                        if (_t1580) {
                                                                                                            Str *_t1496 = Str_lit(">=", 2ULL);
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
                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1496;
                                                                                                        } else {
                                                                                                            Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_ColonEq()); _t1579 = *_hp; free(_hp); }
                                                                                                            (void)_t1579;
                                                                                                            if (_t1579) {
                                                                                                                Str *_t1497 = Str_lit(":=", 2ULL);
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
                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1497;
                                                                                                            } else {
                                                                                                                Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Ident()); _t1578 = *_hp; free(_hp); }
                                                                                                                (void)_t1578;
                                                                                                                if (_t1578) {
                                                                                                                    Str *_t1498 = Str_lit("identifier", 10ULL);
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
                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1498;
                                                                                                                } else {
                                                                                                                    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_StringTok()); _t1577 = *_hp; free(_hp); }
                                                                                                                    (void)_t1577;
                                                                                                                    if (_t1577) {
                                                                                                                        Str *_t1499 = Str_lit("string", 6ULL);
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
                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1499;
                                                                                                                    } else {
                                                                                                                        Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Number()); _t1576 = *_hp; free(_hp); }
                                                                                                                        (void)_t1576;
                                                                                                                        if (_t1576) {
                                                                                                                            Str *_t1500 = Str_lit("number", 6ULL);
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
                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1500;
                                                                                                                        } else {
                                                                                                                            Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Char()); _t1575 = *_hp; free(_hp); }
                                                                                                                            (void)_t1575;
                                                                                                                            if (_t1575) {
                                                                                                                                Str *_t1501 = Str_lit("char", 4ULL);
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
                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1501;
                                                                                                                            } else {
                                                                                                                                Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwMode()); _t1574 = *_hp; free(_hp); }
                                                                                                                                (void)_t1574;
                                                                                                                                if (_t1574) {
                                                                                                                                    Str *_t1502 = Str_lit("mode", 4ULL);
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
                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1502;
                                                                                                                                } else {
                                                                                                                                    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwMut()); _t1573 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1573;
                                                                                                                                    if (_t1573) {
                                                                                                                                        Str *_t1503 = Str_lit("mut", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1503;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwOwn()); _t1572 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1572;
                                                                                                                                        if (_t1572) {
                                                                                                                                            Str *_t1504 = Str_lit("own", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1504;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwRef()); _t1571 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1571;
                                                                                                                                            if (_t1571) {
                                                                                                                                                Str *_t1505 = Str_lit("ref", 3ULL);
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
                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1505;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwShallow()); _t1570 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1570;
                                                                                                                                                if (_t1570) {
                                                                                                                                                    Str *_t1506 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1506;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwStruct()); _t1569 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1569;
                                                                                                                                                    if (_t1569) {
                                                                                                                                                        Str *_t1507 = Str_lit("struct", 6ULL);
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
                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1507;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwExtStruct()); _t1568 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1568;
                                                                                                                                                        if (_t1568) {
                                                                                                                                                            Str *_t1508 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1508;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwEnum()); _t1567 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1567;
                                                                                                                                                            if (_t1567) {
                                                                                                                                                                Str *_t1509 = Str_lit("enum", 4ULL);
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
                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1509;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwNamespace()); _t1566 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1566;
                                                                                                                                                                if (_t1566) {
                                                                                                                                                                    Str *_t1510 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1510;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwFunc()); _t1565 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1565;
                                                                                                                                                                    if (_t1565) {
                                                                                                                                                                        Str *_t1511 = Str_lit("func", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1511;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwProc()); _t1564 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1564;
                                                                                                                                                                        if (_t1564) {
                                                                                                                                                                            Str *_t1512 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1512;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwTest()); _t1563 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1563;
                                                                                                                                                                            if (_t1563) {
                                                                                                                                                                                Str *_t1513 = Str_lit("test", 4ULL);
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
                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1513;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwMacro()); _t1562 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1562;
                                                                                                                                                                                if (_t1562) {
                                                                                                                                                                                    Str *_t1514 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1514;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwExtFunc()); _t1561 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1561;
                                                                                                                                                                                    if (_t1561) {
                                                                                                                                                                                        Str *_t1515 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1515;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwExtProc()); _t1560 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1560;
                                                                                                                                                                                        if (_t1560) {
                                                                                                                                                                                            Str *_t1516 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1516;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwReturns()); _t1559 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1559;
                                                                                                                                                                                            if (_t1559) {
                                                                                                                                                                                                Str *_t1517 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1517;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwThrows()); _t1558 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1558;
                                                                                                                                                                                                if (_t1558) {
                                                                                                                                                                                                    Str *_t1518 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1518;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwIf()); _t1557 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1557;
                                                                                                                                                                                                    if (_t1557) {
                                                                                                                                                                                                        Str *_t1519 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1519;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwElse()); _t1556 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1556;
                                                                                                                                                                                                        if (_t1556) {
                                                                                                                                                                                                            Str *_t1520 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1520;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwWhile()); _t1555 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1555;
                                                                                                                                                                                                            if (_t1555) {
                                                                                                                                                                                                                Str *_t1521 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1521;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwFor()); _t1554 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1554;
                                                                                                                                                                                                                if (_t1554) {
                                                                                                                                                                                                                    Str *_t1522 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1522;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwIn()); _t1553 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1553;
                                                                                                                                                                                                                    if (_t1553) {
                                                                                                                                                                                                                        Str *_t1523 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1523;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwSwitch()); _t1552 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1552;
                                                                                                                                                                                                                        if (_t1552) {
                                                                                                                                                                                                                            Str *_t1524 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1524;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwMatch()); _t1551 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1551;
                                                                                                                                                                                                                            if (_t1551) {
                                                                                                                                                                                                                                Str *_t1525 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1525;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwCase()); _t1550 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1550;
                                                                                                                                                                                                                                if (_t1550) {
                                                                                                                                                                                                                                    Str *_t1526 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1526;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwDefault()); _t1549 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1549;
                                                                                                                                                                                                                                    if (_t1549) {
                                                                                                                                                                                                                                        Str *_t1527 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1527;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwReturn()); _t1548 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1548;
                                                                                                                                                                                                                                        if (_t1548) {
                                                                                                                                                                                                                                            Str *_t1528 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1528;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwThrow()); _t1547 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1547;
                                                                                                                                                                                                                                            if (_t1547) {
                                                                                                                                                                                                                                                Str *_t1529 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1529;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwCatch()); _t1546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1546;
                                                                                                                                                                                                                                                if (_t1546) {
                                                                                                                                                                                                                                                    Str *_t1530 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1530;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwBreak()); _t1545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1545;
                                                                                                                                                                                                                                                    if (_t1545) {
                                                                                                                                                                                                                                                        Str *_t1531 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1531;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwContinue()); _t1544 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1544;
                                                                                                                                                                                                                                                        if (_t1544) {
                                                                                                                                                                                                                                                            Str *_t1532 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1532;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwDefer()); _t1543 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1543;
                                                                                                                                                                                                                                                            if (_t1543) {
                                                                                                                                                                                                                                                                Str *_t1533 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1533;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwTrue()); _t1542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1542;
                                                                                                                                                                                                                                                                if (_t1542) {
                                                                                                                                                                                                                                                                    Str *_t1534 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1534;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwFalse()); _t1541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1541;
                                                                                                                                                                                                                                                                    if (_t1541) {
                                                                                                                                                                                                                                                                        Str *_t1535 = Str_lit("false", 5ULL);
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
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1535;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_KwNull()); _t1540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1540;
                                                                                                                                                                                                                                                                        if (_t1540) {
                                                                                                                                                                                                                                                                            Str *_t1536 = Str_lit("NULL", 4ULL);
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
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1536;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(_sw1471, TokenType_Error()); _t1539 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t1539;
                                                                                                                                                                                                                                                                            if (_t1539) {
                                                                                                                                                                                                                                                                                Str *_t1537 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t1537;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1537;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t1538 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t1538;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1471, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1538;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1471, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1605 = Str_clone(word);
        (void)_sw1605;
        Str *_t1674 = Str_lit("mode", 4ULL);
        (void)_t1674;
        Bool _t1675; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1674); _t1675 = *_hp; free(_hp); }
        (void)_t1675;
        Str_delete(_t1674, &(Bool){1});
        if (_t1675) {
            Str_delete(_sw1605, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1672 = Str_lit("mut", 3ULL);
            (void)_t1672;
            Bool _t1673; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1672); _t1673 = *_hp; free(_hp); }
            (void)_t1673;
            Str_delete(_t1672, &(Bool){1});
            if (_t1673) {
                ;
                Str_delete(_sw1605, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1670 = Str_lit("own", 3ULL);
                (void)_t1670;
                Bool _t1671; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1670); _t1671 = *_hp; free(_hp); }
                (void)_t1671;
                Str_delete(_t1670, &(Bool){1});
                if (_t1671) {
                    ;
                    ;
                    Str_delete(_sw1605, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1668 = Str_lit("ref", 3ULL);
                    (void)_t1668;
                    Bool _t1669; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1668); _t1669 = *_hp; free(_hp); }
                    (void)_t1669;
                    Str_delete(_t1668, &(Bool){1});
                    if (_t1669) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1605, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1666 = Str_lit("shallow", 7ULL);
                        (void)_t1666;
                        Bool _t1667; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1666); _t1667 = *_hp; free(_hp); }
                        (void)_t1667;
                        Str_delete(_t1666, &(Bool){1});
                        if (_t1667) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1605, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1664 = Str_lit("struct", 6ULL);
                            (void)_t1664;
                            Bool _t1665; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1664); _t1665 = *_hp; free(_hp); }
                            (void)_t1665;
                            Str_delete(_t1664, &(Bool){1});
                            if (_t1665) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1605, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1662 = Str_lit("ext_struct", 10ULL);
                                (void)_t1662;
                                Bool _t1663; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1662); _t1663 = *_hp; free(_hp); }
                                (void)_t1663;
                                Str_delete(_t1662, &(Bool){1});
                                if (_t1663) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1605, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1660 = Str_lit("enum", 4ULL);
                                    (void)_t1660;
                                    Bool _t1661; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1660); _t1661 = *_hp; free(_hp); }
                                    (void)_t1661;
                                    Str_delete(_t1660, &(Bool){1});
                                    if (_t1661) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1605, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1658 = Str_lit("namespace", 9ULL);
                                        (void)_t1658;
                                        Bool _t1659; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1658); _t1659 = *_hp; free(_hp); }
                                        (void)_t1659;
                                        Str_delete(_t1658, &(Bool){1});
                                        if (_t1659) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1605, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1656 = Str_lit("func", 4ULL);
                                            (void)_t1656;
                                            Bool _t1657; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1656); _t1657 = *_hp; free(_hp); }
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
                                                ;
                                                ;
                                                Str_delete(_sw1605, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1654 = Str_lit("proc", 4ULL);
                                                (void)_t1654;
                                                Bool _t1655; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1654); _t1655 = *_hp; free(_hp); }
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
                                                    ;
                                                    ;
                                                    Str_delete(_sw1605, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1652 = Str_lit("test", 4ULL);
                                                    (void)_t1652;
                                                    Bool _t1653; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1652); _t1653 = *_hp; free(_hp); }
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
                                                        ;
                                                        ;
                                                        Str_delete(_sw1605, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1650 = Str_lit("macro", 5ULL);
                                                        (void)_t1650;
                                                        Bool _t1651; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1650); _t1651 = *_hp; free(_hp); }
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
                                                            ;
                                                            ;
                                                            Str_delete(_sw1605, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1648 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1648;
                                                            Bool _t1649; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1648); _t1649 = *_hp; free(_hp); }
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
                                                                ;
                                                                ;
                                                                Str_delete(_sw1605, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1646 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1646;
                                                                Bool _t1647; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1646); _t1647 = *_hp; free(_hp); }
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
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1605, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1644 = Str_lit("returns", 7ULL);
                                                                    (void)_t1644;
                                                                    Bool _t1645; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1644); _t1645 = *_hp; free(_hp); }
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
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1605, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1642 = Str_lit("throws", 6ULL);
                                                                        (void)_t1642;
                                                                        Bool _t1643; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1642); _t1643 = *_hp; free(_hp); }
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
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1605, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1640 = Str_lit("if", 2ULL);
                                                                            (void)_t1640;
                                                                            Bool _t1641; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1640); _t1641 = *_hp; free(_hp); }
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
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1605, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1638 = Str_lit("else", 4ULL);
                                                                                (void)_t1638;
                                                                                Bool _t1639; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1638); _t1639 = *_hp; free(_hp); }
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
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1605, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1636 = Str_lit("while", 5ULL);
                                                                                    (void)_t1636;
                                                                                    Bool _t1637; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1636); _t1637 = *_hp; free(_hp); }
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
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1605, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1634 = Str_lit("for", 3ULL);
                                                                                        (void)_t1634;
                                                                                        Bool _t1635; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1634); _t1635 = *_hp; free(_hp); }
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
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1605, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1632 = Str_lit("in", 2ULL);
                                                                                            (void)_t1632;
                                                                                            Bool _t1633; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1632); _t1633 = *_hp; free(_hp); }
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
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1605, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1630 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1630;
                                                                                                Bool _t1631; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1630); _t1631 = *_hp; free(_hp); }
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1605, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1628 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1628;
                                                                                                    Bool _t1629; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1628); _t1629 = *_hp; free(_hp); }
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1605, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1626 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1626;
                                                                                                        Bool _t1627; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1626); _t1627 = *_hp; free(_hp); }
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1605, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1624 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1624;
                                                                                                            Bool _t1625; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1624); _t1625 = *_hp; free(_hp); }
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1605, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1622 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1622;
                                                                                                                Bool _t1623; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1622); _t1623 = *_hp; free(_hp); }
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1605, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1620 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1620;
                                                                                                                    Bool _t1621; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1620); _t1621 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1605, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1618 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1618;
                                                                                                                        Bool _t1619; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1618); _t1619 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1605, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1616 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1616;
                                                                                                                            Bool _t1617; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1616); _t1617 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1605, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1614 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1614;
                                                                                                                                Bool _t1615; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1614); _t1615 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1605, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1612 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1612;
                                                                                                                                    Bool _t1613; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1612); _t1613 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1605, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1610 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1610;
                                                                                                                                        Bool _t1611; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1610); _t1611 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1605, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1608 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1608;
                                                                                                                                            Bool _t1609; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1608); _t1609 = *_hp; free(_hp); }
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1605, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1606 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1606;
                                                                                                                                                Bool _t1607; { Bool *_hp = (Bool *)Str_eq(_sw1605, _t1606); _t1607 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1605, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1605, &(Bool){1});
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
        Str_delete(_sw1605, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2024 = Str_lit("Token", 5ULL);
    (void)_t2024;
    U64 _t2025; { U64 *_hp = (U64 *)Token_size(); _t2025 = *_hp; free(_hp); }
    (void)_t2025;
    Vec *tokens = Vec_new(_t2024, &(U64){_t2025});
    (void)tokens;
    Str_delete(_t2024, &(Bool){1});
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
        Bool _wcond1676; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1676 = *_hp; free(_hp); }
        (void)_wcond1676;
        if (_wcond1676) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t1970 = 32;
        (void)_t1970;
        U8 _t1971 = 9;
        (void)_t1971;
        Bool _t1972 = U8_eq(DEREF(c), _t1970);
        (void)_t1972;
        ;
        Bool _t1973 = U8_eq(DEREF(c), _t1971);
        (void)_t1973;
        ;
        U8 _t1974 = 13;
        (void)_t1974;
        Bool _t1975 = Bool_or(_t1972, _t1973);
        (void)_t1975;
        ;
        ;
        Bool _t1976 = U8_eq(DEREF(c), _t1974);
        (void)_t1976;
        ;
        U8 _t1977 = 59;
        (void)_t1977;
        Bool _t1978 = Bool_or(_t1975, _t1976);
        (void)_t1978;
        ;
        ;
        Bool _t1979 = U8_eq(DEREF(c), _t1977);
        (void)_t1979;
        ;
        Bool _t1980 = Bool_or(_t1978, _t1979);
        (void)_t1980;
        ;
        ;
        if (_t1980) {
            U64 _t1677 = U64_inc(DEREF(pos));
            (void)_t1677;
            *pos = _t1677;
            ;
            ;
            continue;
        }
        ;
        U8 _t1981 = 10;
        (void)_t1981;
        Bool _t1982 = U8_eq(DEREF(c), _t1981);
        (void)_t1982;
        ;
        if (_t1982) {
            U64 _t1678 = U64_inc(DEREF(pos));
            (void)_t1678;
            *pos = _t1678;
            ;
            I64 _t1679 = 1;
            (void)_t1679;
            I64 _t1680 = I64_add(line, _t1679);
            (void)_t1680;
            ;
            line = _t1680;
            ;
            U64 _t1681 = U64_clone(pos);
            (void)_t1681;
            line_start = _t1681;
            ;
            ;
            continue;
        }
        ;
        U64 _t1983 = U64_sub(DEREF(pos), line_start);
        (void)_t1983;
        U64 _t1984 = 1;
        (void)_t1984;
        U64 _t1985 = U64_add(_t1983, _t1984);
        (void)_t1985;
        ;
        ;
        I64 col = U64_to_i64(_t1985);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t1986 = 35;
        (void)_t1986;
        Bool _t1987 = U8_eq(DEREF(c), _t1986);
        (void)_t1987;
        ;
        if (_t1987) {
            while (1) {
                Bool _wcond1682; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1682 = *_hp; free(_hp); }
                (void)_wcond1682;
                if (_wcond1682) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1683 = Str_byte_at(src, pos);
                (void)_t1683;
                U8 _t1684 = 10;
                (void)_t1684;
                Bool _t1685 = U8_eq(DEREF(_t1683), _t1684);
                (void)_t1685;
                ;
                if (_t1685) {
                    ;
                    break;
                }
                ;
                U64 _t1686 = U64_inc(DEREF(pos));
                (void)_t1686;
                *pos = _t1686;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1988 = 47;
        (void)_t1988;
        U64 _t1989 = 1;
        (void)_t1989;
        U64 _t1990 = U64_add(DEREF(pos), _t1989);
        (void)_t1990;
        ;
        Bool _t1991 = U8_eq(DEREF(c), _t1988);
        (void)_t1991;
        ;
        Bool _t1992; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1990}, &(U64){src_len}); _t1992 = *_hp; free(_hp); }
        (void)_t1992;
        ;
        Bool _t1993 = Bool_and(_t1991, _t1992);
        (void)_t1993;
        ;
        ;
        if (_t1993) {
            U64 _t1745 = 1;
            (void)_t1745;
            U64 *_t1746 = malloc(sizeof(U64)); *_t1746 = U64_add(DEREF(pos), _t1745);
            (void)_t1746;
            ;
            U8 *c2 = Str_byte_at(src, _t1746);
            (void)c2;
            U8 _t1747 = 47;
            (void)_t1747;
            Bool _t1748 = U8_eq(DEREF(c2), _t1747);
            (void)_t1748;
            ;
            if (_t1748) {
                while (1) {
                    Bool _wcond1687; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1687 = *_hp; free(_hp); }
                    (void)_wcond1687;
                    if (_wcond1687) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1688 = Str_byte_at(src, pos);
                    (void)_t1688;
                    U8 _t1689 = 10;
                    (void)_t1689;
                    Bool _t1690 = U8_eq(DEREF(_t1688), _t1689);
                    (void)_t1690;
                    ;
                    if (_t1690) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1691 = U64_inc(DEREF(pos));
                    (void)_t1691;
                    *pos = _t1691;
                    ;
                }
                U64_delete(_t1746, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1749 = 42;
            (void)_t1749;
            Bool _t1750 = U8_eq(DEREF(c2), _t1749);
            (void)_t1750;
            U64_delete(_t1746, &(Bool){1});
            ;
            if (_t1750) {
                U64 _t1741 = 2;
                (void)_t1741;
                U64 _t1742 = U64_add(DEREF(pos), _t1741);
                (void)_t1742;
                ;
                *pos = _t1742;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1692; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1692 = *_hp; free(_hp); }
                    (void)_wcond1692;
                    if (_wcond1692) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1717 = 0;
                    (void)_t1717;
                    Bool _t1718; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1717}); _t1718 = *_hp; free(_hp); }
                    (void)_t1718;
                    ;
                    if (_t1718) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1719 = 1;
                    (void)_t1719;
                    U64 _t1720 = U64_add(DEREF(pos), _t1719);
                    (void)_t1720;
                    ;
                    Bool _t1721; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1720}, &(U64){src_len}); _t1721 = *_hp; free(_hp); }
                    (void)_t1721;
                    ;
                    if (_t1721) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1701 = 1;
                        (void)_t1701;
                        U64 *_t1702 = malloc(sizeof(U64)); *_t1702 = U64_add(DEREF(pos), _t1701);
                        (void)_t1702;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1702);
                        (void)b2;
                        U8 _t1703 = 47;
                        (void)_t1703;
                        U8 _t1704 = 42;
                        (void)_t1704;
                        Bool _t1705 = U8_eq(DEREF(b1), _t1703);
                        (void)_t1705;
                        ;
                        Bool _t1706 = U8_eq(DEREF(b2), _t1704);
                        (void)_t1706;
                        ;
                        Bool _t1707 = Bool_and(_t1705, _t1706);
                        (void)_t1707;
                        ;
                        ;
                        if (_t1707) {
                            I64 _t1693 = 1;
                            (void)_t1693;
                            I64 _t1694 = I64_add(depth, _t1693);
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
                            U64_delete(_t1702, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1708 = 42;
                        (void)_t1708;
                        U8 _t1709 = 47;
                        (void)_t1709;
                        Bool _t1710 = U8_eq(DEREF(b1), _t1708);
                        (void)_t1710;
                        ;
                        Bool _t1711 = U8_eq(DEREF(b2), _t1709);
                        (void)_t1711;
                        U64_delete(_t1702, &(Bool){1});
                        ;
                        Bool _t1712 = Bool_and(_t1710, _t1711);
                        (void)_t1712;
                        ;
                        ;
                        if (_t1712) {
                            I64 _t1697 = 1;
                            (void)_t1697;
                            I64 _t1698 = I64_sub(depth, _t1697);
                            (void)_t1698;
                            ;
                            depth = _t1698;
                            ;
                            U64 _t1699 = 2;
                            (void)_t1699;
                            U64 _t1700 = U64_add(DEREF(pos), _t1699);
                            (void)_t1700;
                            ;
                            *pos = _t1700;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1722 = Str_byte_at(src, pos);
                    (void)_t1722;
                    U8 _t1723 = 10;
                    (void)_t1723;
                    Bool _t1724 = U8_eq(DEREF(_t1722), _t1723);
                    (void)_t1724;
                    ;
                    if (_t1724) {
                        I64 _t1713 = 1;
                        (void)_t1713;
                        I64 _t1714 = I64_add(line, _t1713);
                        (void)_t1714;
                        ;
                        line = _t1714;
                        ;
                        U64 _t1715 = 1;
                        (void)_t1715;
                        U64 _t1716 = U64_add(DEREF(pos), _t1715);
                        (void)_t1716;
                        ;
                        line_start = _t1716;
                        ;
                    }
                    ;
                    U64 _t1725 = U64_inc(DEREF(pos));
                    (void)_t1725;
                    *pos = _t1725;
                    ;
                }
                I64 _t1743 = 0;
                (void)_t1743;
                Bool _t1744; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1743}); _t1744 = *_hp; free(_hp); }
                (void)_t1744;
                ;
                ;
                if (_t1744) {
                    Str *_t1726 = Str_lit("Str", 3ULL);
                    (void)_t1726;
                    U64 _t1727; { U64 *_hp = (U64 *)Str_size(); _t1727 = *_hp; free(_hp); }
                    (void)_t1727;
                    U64 _t1728 = 6;
                    (void)_t1728;
                    Array *_va20 = Array_new(_t1726, &(U64){_t1727}, &(U64){_t1728});
                    (void)_va20;
                    Str_delete(_t1726, &(Bool){1});
                    ;
                    ;
                    U64 _t1729 = 0;
                    (void)_t1729;
                    Str *_t1730 = Str_clone(path);
                    (void)_t1730;
                    Array_set(_va20, &(U64){_t1729}, _t1730);
                    ;
                    U64 _t1731 = 1;
                    (void)_t1731;
                    Str *_t1732 = Str_lit(":", 1ULL);
                    (void)_t1732;
                    Array_set(_va20, &(U64){_t1731}, _t1732);
                    ;
                    U64 _t1733 = 2;
                    (void)_t1733;
                    Str *_t1734 = I64_to_str(&(I64){line});
                    (void)_t1734;
                    Array_set(_va20, &(U64){_t1733}, _t1734);
                    ;
                    U64 _t1735 = 3;
                    (void)_t1735;
                    Str *_t1736 = Str_lit(":", 1ULL);
                    (void)_t1736;
                    Array_set(_va20, &(U64){_t1735}, _t1736);
                    ;
                    U64 _t1737 = 4;
                    (void)_t1737;
                    Str *_t1738 = I64_to_str(&(I64){col});
                    (void)_t1738;
                    Array_set(_va20, &(U64){_t1737}, _t1738);
                    ;
                    U64 _t1739 = 5;
                    (void)_t1739;
                    Str *_t1740 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1740;
                    Array_set(_va20, &(U64){_t1739}, _t1740);
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
        Bool _t1994; { Bool *_hp = (Bool *)is_digit(c); _t1994 = *_hp; free(_hp); }
        (void)_t1994;
        if (_t1994) {
            while (1) {
                Bool _wcond1751; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1751 = *_hp; free(_hp); }
                (void)_wcond1751;
                if (_wcond1751) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1752 = Str_byte_at(src, pos);
                (void)_t1752;
                Bool _t1753; { Bool *_hp = (Bool *)is_digit(_t1752); _t1753 = *_hp; free(_hp); }
                (void)_t1753;
                Bool _t1754 = Bool_not(_t1753);
                (void)_t1754;
                ;
                if (_t1754) {
                    ;
                    break;
                }
                ;
                U64 _t1755 = U64_inc(DEREF(pos));
                (void)_t1755;
                *pos = _t1755;
                ;
            }
            U64 _t1770 = 1;
            (void)_t1770;
            U64 _t1771 = U64_add(DEREF(pos), _t1770);
            (void)_t1771;
            ;
            Bool _t1772; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1771}, &(U64){src_len}); _t1772 = *_hp; free(_hp); }
            (void)_t1772;
            ;
            if (_t1772) {
                U8 *_t1762 = Str_byte_at(src, pos);
                (void)_t1762;
                U8 _t1763 = 46;
                (void)_t1763;
                U64 _t1764 = 1;
                (void)_t1764;
                U64 *_t1765 = malloc(sizeof(U64)); *_t1765 = U64_add(DEREF(pos), _t1764);
                (void)_t1765;
                ;
                U8 *_t1766 = Str_byte_at(src, _t1765);
                (void)_t1766;
                Bool _t1767 = U8_eq(DEREF(_t1762), _t1763);
                (void)_t1767;
                ;
                Bool _t1768; { Bool *_hp = (Bool *)is_digit(_t1766); _t1768 = *_hp; free(_hp); }
                (void)_t1768;
                U64_delete(_t1765, &(Bool){1});
                Bool _t1769 = Bool_and(_t1767, _t1768);
                (void)_t1769;
                ;
                ;
                if (_t1769) {
                    U64 _t1761 = U64_inc(DEREF(pos));
                    (void)_t1761;
                    *pos = _t1761;
                    ;
                    while (1) {
                        Bool _wcond1756; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1756 = *_hp; free(_hp); }
                        (void)_wcond1756;
                        if (_wcond1756) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1757 = Str_byte_at(src, pos);
                        (void)_t1757;
                        Bool _t1758; { Bool *_hp = (Bool *)is_digit(_t1757); _t1758 = *_hp; free(_hp); }
                        (void)_t1758;
                        Bool _t1759 = Bool_not(_t1758);
                        (void)_t1759;
                        ;
                        if (_t1759) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1760 = U64_inc(DEREF(pos));
                        (void)_t1760;
                        *pos = _t1760;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1773 = U64_sub(DEREF(pos), start);
            (void)_t1773;
            I64 _t1774 = I64_clone(&(I64){col});
            (void)_t1774;
            Token *_t1775 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1775->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1773}); _t1775->text = *_ca; free(_ca); }
            _t1775->line = I64_clone(&(I64){line});
            _t1775->col = _t1774;
            (void)_t1775;
            ;
            ;
            Vec_push(tokens, _t1775);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1995; { Bool *_hp = (Bool *)is_alpha(c); _t1995 = *_hp; free(_hp); }
        (void)_t1995;
        if (_t1995) {
            while (1) {
                Bool _wcond1776; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1776 = *_hp; free(_hp); }
                (void)_wcond1776;
                if (_wcond1776) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1777 = Str_byte_at(src, pos);
                (void)_t1777;
                Bool _t1778; { Bool *_hp = (Bool *)is_alnum(_t1777); _t1778 = *_hp; free(_hp); }
                (void)_t1778;
                Bool _t1779 = Bool_not(_t1778);
                (void)_t1779;
                ;
                if (_t1779) {
                    ;
                    break;
                }
                ;
                U64 _t1780 = U64_inc(DEREF(pos));
                (void)_t1780;
                *pos = _t1780;
                ;
            }
            U64 _t1781 = U64_sub(DEREF(pos), start);
            (void)_t1781;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1781});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1782 = I64_clone(&(I64){line});
            (void)_t1782;
            I64 _t1783 = I64_clone(&(I64){col});
            (void)_t1783;
            Token *_t1784 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1784->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1784->text = *_ca; free(_ca); }
            _t1784->line = _t1782;
            _t1784->col = _t1783;
            (void)_t1784;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1784);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1996 = 34;
        (void)_t1996;
        Bool _t1997 = U8_eq(DEREF(c), _t1996);
        (void)_t1997;
        ;
        if (_t1997) {
            U64 _t1831 = U64_inc(DEREF(pos));
            (void)_t1831;
            *pos = _t1831;
            ;
            while (1) {
                Bool _wcond1785; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1785 = *_hp; free(_hp); }
                (void)_wcond1785;
                if (_wcond1785) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1791 = Str_byte_at(src, pos);
                (void)_t1791;
                U8 _t1792 = 34;
                (void)_t1792;
                Bool _t1793 = U8_eq(DEREF(_t1791), _t1792);
                (void)_t1793;
                ;
                if (_t1793) {
                    ;
                    break;
                }
                ;
                U8 *_t1794 = Str_byte_at(src, pos);
                (void)_t1794;
                U8 _t1795 = 92;
                (void)_t1795;
                U64 _t1796 = 1;
                (void)_t1796;
                U64 _t1797 = U64_add(DEREF(pos), _t1796);
                (void)_t1797;
                ;
                Bool _t1798 = U8_eq(DEREF(_t1794), _t1795);
                (void)_t1798;
                ;
                Bool _t1799; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1797}, &(U64){src_len}); _t1799 = *_hp; free(_hp); }
                (void)_t1799;
                ;
                Bool _t1800 = Bool_and(_t1798, _t1799);
                (void)_t1800;
                ;
                ;
                if (_t1800) {
                    U64 _t1786 = U64_inc(DEREF(pos));
                    (void)_t1786;
                    *pos = _t1786;
                    ;
                }
                ;
                U8 *_t1801 = Str_byte_at(src, pos);
                (void)_t1801;
                U8 _t1802 = 10;
                (void)_t1802;
                Bool _t1803 = U8_eq(DEREF(_t1801), _t1802);
                (void)_t1803;
                ;
                if (_t1803) {
                    I64 _t1787 = 1;
                    (void)_t1787;
                    I64 _t1788 = I64_add(line, _t1787);
                    (void)_t1788;
                    ;
                    line = _t1788;
                    ;
                    U64 _t1789 = 1;
                    (void)_t1789;
                    U64 _t1790 = U64_add(DEREF(pos), _t1789);
                    (void)_t1790;
                    ;
                    line_start = _t1790;
                    ;
                }
                ;
                U64 _t1804 = U64_inc(DEREF(pos));
                (void)_t1804;
                *pos = _t1804;
                ;
            }
            U8 *_t1832 = Str_byte_at(src, pos);
            (void)_t1832;
            U8 _t1833 = 34;
            (void)_t1833;
            Bool _t1834; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1834 = *_hp; free(_hp); }
            (void)_t1834;
            Bool _t1835 = U8_eq(DEREF(_t1832), _t1833);
            (void)_t1835;
            ;
            Bool _t1836 = Bool_and(_t1834, _t1835);
            (void)_t1836;
            ;
            ;
            if (_t1836) {
                U64 _t1805 = U64_inc(DEREF(pos));
                (void)_t1805;
                *pos = _t1805;
                ;
                U64 _t1806 = 1;
                (void)_t1806;
                U64 _t1807 = U64_sub(DEREF(pos), start);
                (void)_t1807;
                U64 _t1808 = 2;
                (void)_t1808;
                U64 _t1809 = U64_add(start, _t1806);
                (void)_t1809;
                ;
                U64 _t1810 = U64_sub(_t1807, _t1808);
                (void)_t1810;
                ;
                ;
                I64 _t1811 = I64_clone(&(I64){col});
                (void)_t1811;
                Token *_t1812 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1812->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1809}, &(U64){_t1810}); _t1812->text = *_ca; free(_ca); }
                _t1812->line = I64_clone(&(I64){line});
                _t1812->col = _t1811;
                (void)_t1812;
                ;
                ;
                ;
                Vec_push(tokens, _t1812);
            } else {
                Str *_t1813 = Str_lit("Str", 3ULL);
                (void)_t1813;
                U64 _t1814; { U64 *_hp = (U64 *)Str_size(); _t1814 = *_hp; free(_hp); }
                (void)_t1814;
                U64 _t1815 = 6;
                (void)_t1815;
                Array *_va21 = Array_new(_t1813, &(U64){_t1814}, &(U64){_t1815});
                (void)_va21;
                Str_delete(_t1813, &(Bool){1});
                ;
                ;
                U64 _t1816 = 0;
                (void)_t1816;
                Str *_t1817 = Str_clone(path);
                (void)_t1817;
                Array_set(_va21, &(U64){_t1816}, _t1817);
                ;
                U64 _t1818 = 1;
                (void)_t1818;
                Str *_t1819 = Str_lit(":", 1ULL);
                (void)_t1819;
                Array_set(_va21, &(U64){_t1818}, _t1819);
                ;
                U64 _t1820 = 2;
                (void)_t1820;
                Str *_t1821 = I64_to_str(&(I64){line});
                (void)_t1821;
                Array_set(_va21, &(U64){_t1820}, _t1821);
                ;
                U64 _t1822 = 3;
                (void)_t1822;
                Str *_t1823 = Str_lit(":", 1ULL);
                (void)_t1823;
                Array_set(_va21, &(U64){_t1822}, _t1823);
                ;
                U64 _t1824 = 4;
                (void)_t1824;
                Str *_t1825 = I64_to_str(&(I64){col});
                (void)_t1825;
                Array_set(_va21, &(U64){_t1824}, _t1825);
                ;
                U64 _t1826 = 5;
                (void)_t1826;
                Str *_t1827 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1827;
                Array_set(_va21, &(U64){_t1826}, _t1827);
                ;
                println(_va21);
                U64 _t1828 = U64_sub(DEREF(pos), start);
                (void)_t1828;
                I64 _t1829 = I64_clone(&(I64){col});
                (void)_t1829;
                Token *_t1830 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1830->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1828}); _t1830->text = *_ca; free(_ca); }
                _t1830->line = I64_clone(&(I64){line});
                _t1830->col = _t1829;
                (void)_t1830;
                ;
                ;
                Vec_push(tokens, _t1830);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1998 = 39;
        (void)_t1998;
        Bool _t1999 = U8_eq(DEREF(c), _t1998);
        (void)_t1999;
        ;
        if (_t1999) {
            U64 _t1860 = U64_inc(DEREF(pos));
            (void)_t1860;
            *pos = _t1860;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t1861 = Str_byte_at(src, pos);
            (void)_t1861;
            U8 _t1862 = 92;
            (void)_t1862;
            U64 _t1863 = 1;
            (void)_t1863;
            U64 _t1864 = U64_add(DEREF(pos), _t1863);
            (void)_t1864;
            ;
            Bool _t1865 = U8_eq(DEREF(_t1861), _t1862);
            (void)_t1865;
            ;
            Bool _t1866; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1864}, &(U64){src_len}); _t1866 = *_hp; free(_hp); }
            (void)_t1866;
            ;
            Bool _t1867; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1867 = *_hp; free(_hp); }
            (void)_t1867;
            Bool _t1868 = Bool_and(_t1865, _t1866);
            (void)_t1868;
            ;
            ;
            Bool _t1869 = Bool_and(_t1867, _t1868);
            (void)_t1869;
            ;
            ;
            if (_t1869) {
                U64 _t1837 = U64_inc(DEREF(pos));
                (void)_t1837;
                *pos = _t1837;
                ;
            }
            ;
            U64 _t1870 = U64_inc(DEREF(pos));
            (void)_t1870;
            *pos = _t1870;
            ;
            U8 *_t1871 = Str_byte_at(src, pos);
            (void)_t1871;
            U8 _t1872 = 39;
            (void)_t1872;
            Bool _t1873; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1873 = *_hp; free(_hp); }
            (void)_t1873;
            Bool _t1874 = U8_eq(DEREF(_t1871), _t1872);
            (void)_t1874;
            ;
            Bool _t1875 = Bool_and(_t1873, _t1874);
            (void)_t1875;
            ;
            ;
            if (_t1875) {
                U64 _t1838 = U64_sub(DEREF(pos), ch_start);
                (void)_t1838;
                I64 _t1839 = I64_clone(&(I64){col});
                (void)_t1839;
                Token *_t1840 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1840->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1838}); _t1840->text = *_ca; free(_ca); }
                _t1840->line = I64_clone(&(I64){line});
                _t1840->col = _t1839;
                (void)_t1840;
                ;
                ;
                Vec_push(tokens, _t1840);
                U64 _t1841 = U64_inc(DEREF(pos));
                (void)_t1841;
                *pos = _t1841;
                ;
            } else {
                Str *_t1842 = Str_lit("Str", 3ULL);
                (void)_t1842;
                U64 _t1843; { U64 *_hp = (U64 *)Str_size(); _t1843 = *_hp; free(_hp); }
                (void)_t1843;
                U64 _t1844 = 6;
                (void)_t1844;
                Array *_va22 = Array_new(_t1842, &(U64){_t1843}, &(U64){_t1844});
                (void)_va22;
                Str_delete(_t1842, &(Bool){1});
                ;
                ;
                U64 _t1845 = 0;
                (void)_t1845;
                Str *_t1846 = Str_clone(path);
                (void)_t1846;
                Array_set(_va22, &(U64){_t1845}, _t1846);
                ;
                U64 _t1847 = 1;
                (void)_t1847;
                Str *_t1848 = Str_lit(":", 1ULL);
                (void)_t1848;
                Array_set(_va22, &(U64){_t1847}, _t1848);
                ;
                U64 _t1849 = 2;
                (void)_t1849;
                Str *_t1850 = I64_to_str(&(I64){line});
                (void)_t1850;
                Array_set(_va22, &(U64){_t1849}, _t1850);
                ;
                U64 _t1851 = 3;
                (void)_t1851;
                Str *_t1852 = Str_lit(":", 1ULL);
                (void)_t1852;
                Array_set(_va22, &(U64){_t1851}, _t1852);
                ;
                U64 _t1853 = 4;
                (void)_t1853;
                Str *_t1854 = I64_to_str(&(I64){col});
                (void)_t1854;
                Array_set(_va22, &(U64){_t1853}, _t1854);
                ;
                U64 _t1855 = 5;
                (void)_t1855;
                Str *_t1856 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t1856;
                Array_set(_va22, &(U64){_t1855}, _t1856);
                ;
                println(_va22);
                U64 _t1857 = U64_sub(DEREF(pos), start);
                (void)_t1857;
                I64 _t1858 = I64_clone(&(I64){col});
                (void)_t1858;
                Token *_t1859 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1859->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1857}); _t1859->text = *_ca; free(_ca); }
                _t1859->line = I64_clone(&(I64){line});
                _t1859->col = _t1858;
                (void)_t1859;
                ;
                ;
                Vec_push(tokens, _t1859);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2000 = 1;
        (void)_t2000;
        U64 _t2001 = U64_add(DEREF(pos), _t2000);
        (void)_t2001;
        ;
        Bool _t2002; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2001}, &(U64){src_len}); _t2002 = *_hp; free(_hp); }
        (void)_t2002;
        ;
        if (_t2002) {
            U64 _t1919 = 1;
            (void)_t1919;
            U64 *_t1920 = malloc(sizeof(U64)); *_t1920 = U64_add(DEREF(pos), _t1919);
            (void)_t1920;
            ;
            U8 *c2 = Str_byte_at(src, _t1920);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t1921 = 58;
            (void)_t1921;
            U8 _t1922 = 61;
            (void)_t1922;
            Bool _t1923 = U8_eq(DEREF(c), _t1921);
            (void)_t1923;
            ;
            Bool _t1924 = U8_eq(DEREF(c2), _t1922);
            (void)_t1924;
            ;
            Bool _t1925 = Bool_and(_t1923, _t1924);
            (void)_t1925;
            ;
            ;
            if (_t1925) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t1908 = 61;
                (void)_t1908;
                U8 _t1909 = 61;
                (void)_t1909;
                Bool _t1910 = U8_eq(DEREF(c), _t1908);
                (void)_t1910;
                ;
                Bool _t1911 = U8_eq(DEREF(c2), _t1909);
                (void)_t1911;
                ;
                Bool _t1912 = Bool_and(_t1910, _t1911);
                (void)_t1912;
                ;
                ;
                if (_t1912) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t1903 = 33;
                    (void)_t1903;
                    U8 _t1904 = 61;
                    (void)_t1904;
                    Bool _t1905 = U8_eq(DEREF(c), _t1903);
                    (void)_t1905;
                    ;
                    Bool _t1906 = U8_eq(DEREF(c2), _t1904);
                    (void)_t1906;
                    ;
                    Bool _t1907 = Bool_and(_t1905, _t1906);
                    (void)_t1907;
                    ;
                    ;
                    if (_t1907) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1898 = 60;
                        (void)_t1898;
                        U8 _t1899 = 61;
                        (void)_t1899;
                        Bool _t1900 = U8_eq(DEREF(c), _t1898);
                        (void)_t1900;
                        ;
                        Bool _t1901 = U8_eq(DEREF(c2), _t1899);
                        (void)_t1901;
                        ;
                        Bool _t1902 = Bool_and(_t1900, _t1901);
                        (void)_t1902;
                        ;
                        ;
                        if (_t1902) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1893 = 62;
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
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1888 = 46;
                                (void)_t1888;
                                U8 _t1889 = 46;
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
                                    U64 _t1885 = 2;
                                    (void)_t1885;
                                    U64 _t1886 = U64_add(DEREF(pos), _t1885);
                                    (void)_t1886;
                                    ;
                                    Bool _t1887; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1886}, &(U64){src_len}); _t1887 = *_hp; free(_hp); }
                                    (void)_t1887;
                                    ;
                                    if (_t1887) {
                                        U64 _t1881 = 2;
                                        (void)_t1881;
                                        U64 *_t1882 = malloc(sizeof(U64)); *_t1882 = U64_add(DEREF(pos), _t1881);
                                        (void)_t1882;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t1882);
                                        (void)c3;
                                        U8 _t1883 = 46;
                                        (void)_t1883;
                                        Bool _t1884 = U8_eq(DEREF(c3), _t1883);
                                        (void)_t1884;
                                        U64_delete(_t1882, &(Bool){1});
                                        ;
                                        if (_t1884) {
                                            U64 _t1876 = 3;
                                            (void)_t1876;
                                            I64 _t1877 = I64_clone(&(I64){col});
                                            (void)_t1877;
                                            Token *_t1878 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t1878->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1876}); _t1878->text = *_ca; free(_ca); }
                                            _t1878->line = I64_clone(&(I64){line});
                                            _t1878->col = _t1877;
                                            (void)_t1878;
                                            ;
                                            ;
                                            Vec_push(tokens, _t1878);
                                            U64 _t1879 = 3;
                                            (void)_t1879;
                                            U64 _t1880 = U64_add(DEREF(pos), _t1879);
                                            (void)_t1880;
                                            ;
                                            *pos = _t1880;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t1920, &(Bool){1});
                                            ;
                                            TokenType_delete(two, &(Bool){1});
                                            ;
                                            ;
                                            ;
                                            continue;
                                        }
                                        ;
                                    }
                                    ;
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
            U64_delete(_t1920, &(Bool){1});
            ;
            Bool _t1926; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t1926 = *_hp; free(_hp); }
            (void)_t1926;
            Bool _t1927 = Bool_not(_t1926);
            (void)_t1927;
            ;
            if (_t1927) {
                U64 _t1913 = 2;
                (void)_t1913;
                I64 _t1914 = I64_clone(&(I64){line});
                (void)_t1914;
                I64 _t1915 = I64_clone(&(I64){col});
                (void)_t1915;
                Token *_t1916 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1916->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1913}); _t1916->text = *_ca; free(_ca); }
                _t1916->line = _t1914;
                _t1916->col = _t1915;
                (void)_t1916;
                ;
                ;
                ;
                Vec_push(tokens, _t1916);
                U64 _t1917 = 2;
                (void)_t1917;
                U64 _t1918 = U64_add(DEREF(pos), _t1917);
                (void)_t1918;
                ;
                *pos = _t1918;
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
            U8 _sw1928 = U8_clone(c);
            (void)_sw1928;
            U8 _t1963 = 40;
            (void)_t1963;
            Bool _t1964 = U8_eq(_sw1928, _t1963);
            (void)_t1964;
            ;
            if (_t1964) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1961 = 41;
                (void)_t1961;
                Bool _t1962 = U8_eq(_sw1928, _t1961);
                (void)_t1962;
                ;
                if (_t1962) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1959 = 123;
                    (void)_t1959;
                    Bool _t1960 = U8_eq(_sw1928, _t1959);
                    (void)_t1960;
                    ;
                    if (_t1960) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1957 = 125;
                        (void)_t1957;
                        Bool _t1958 = U8_eq(_sw1928, _t1957);
                        (void)_t1958;
                        ;
                        if (_t1958) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1955 = 91;
                            (void)_t1955;
                            Bool _t1956 = U8_eq(_sw1928, _t1955);
                            (void)_t1956;
                            ;
                            if (_t1956) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1953 = 93;
                                (void)_t1953;
                                Bool _t1954 = U8_eq(_sw1928, _t1953);
                                (void)_t1954;
                                ;
                                if (_t1954) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1951 = 44;
                                    (void)_t1951;
                                    Bool _t1952 = U8_eq(_sw1928, _t1951);
                                    (void)_t1952;
                                    ;
                                    if (_t1952) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1949 = 58;
                                        (void)_t1949;
                                        Bool _t1950 = U8_eq(_sw1928, _t1949);
                                        (void)_t1950;
                                        ;
                                        if (_t1950) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1947 = 46;
                                            (void)_t1947;
                                            Bool _t1948 = U8_eq(_sw1928, _t1947);
                                            (void)_t1948;
                                            ;
                                            if (_t1948) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1945 = 63;
                                                (void)_t1945;
                                                Bool _t1946 = U8_eq(_sw1928, _t1945);
                                                (void)_t1946;
                                                ;
                                                if (_t1946) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1943 = 33;
                                                    (void)_t1943;
                                                    Bool _t1944 = U8_eq(_sw1928, _t1943);
                                                    (void)_t1944;
                                                    ;
                                                    if (_t1944) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1941 = 43;
                                                        (void)_t1941;
                                                        Bool _t1942 = U8_eq(_sw1928, _t1941);
                                                        (void)_t1942;
                                                        ;
                                                        if (_t1942) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1939 = 45;
                                                            (void)_t1939;
                                                            Bool _t1940 = U8_eq(_sw1928, _t1939);
                                                            (void)_t1940;
                                                            ;
                                                            if (_t1940) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1937 = 42;
                                                                (void)_t1937;
                                                                Bool _t1938 = U8_eq(_sw1928, _t1937);
                                                                (void)_t1938;
                                                                ;
                                                                if (_t1938) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1935 = 47;
                                                                    (void)_t1935;
                                                                    Bool _t1936 = U8_eq(_sw1928, _t1935);
                                                                    (void)_t1936;
                                                                    ;
                                                                    if (_t1936) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1933 = 61;
                                                                        (void)_t1933;
                                                                        Bool _t1934 = U8_eq(_sw1928, _t1933);
                                                                        (void)_t1934;
                                                                        ;
                                                                        if (_t1934) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1931 = 60;
                                                                            (void)_t1931;
                                                                            Bool _t1932 = U8_eq(_sw1928, _t1931);
                                                                            (void)_t1932;
                                                                            ;
                                                                            if (_t1932) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1929 = 62;
                                                                                (void)_t1929;
                                                                                Bool _t1930 = U8_eq(_sw1928, _t1929);
                                                                                (void)_t1930;
                                                                                ;
                                                                                if (_t1930) {
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
        Bool _t2003; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2003 = *_hp; free(_hp); }
        (void)_t2003;
        Bool _t2004 = Bool_not(_t2003);
        (void)_t2004;
        ;
        if (_t2004) {
            U64 _t1965 = 1;
            (void)_t1965;
            I64 _t1966 = I64_clone(&(I64){line});
            (void)_t1966;
            I64 _t1967 = I64_clone(&(I64){col});
            (void)_t1967;
            Token *_t1968 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1968->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1965}); _t1968->text = *_ca; free(_ca); }
            _t1968->line = _t1966;
            _t1968->col = _t1967;
            (void)_t1968;
            ;
            ;
            ;
            Vec_push(tokens, _t1968);
            U64 _t1969 = U64_inc(DEREF(pos));
            (void)_t1969;
            *pos = _t1969;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2005 = Str_lit("Str", 3ULL);
        (void)_t2005;
        U64 _t2006; { U64 *_hp = (U64 *)Str_size(); _t2006 = *_hp; free(_hp); }
        (void)_t2006;
        U64 _t2007 = 6;
        (void)_t2007;
        Array *_va23 = Array_new(_t2005, &(U64){_t2006}, &(U64){_t2007});
        (void)_va23;
        Str_delete(_t2005, &(Bool){1});
        ;
        ;
        U64 _t2008 = 0;
        (void)_t2008;
        Str *_t2009 = Str_clone(path);
        (void)_t2009;
        Array_set(_va23, &(U64){_t2008}, _t2009);
        ;
        U64 _t2010 = 1;
        (void)_t2010;
        Str *_t2011 = Str_lit(":", 1ULL);
        (void)_t2011;
        Array_set(_va23, &(U64){_t2010}, _t2011);
        ;
        U64 _t2012 = 2;
        (void)_t2012;
        Str *_t2013 = I64_to_str(&(I64){line});
        (void)_t2013;
        Array_set(_va23, &(U64){_t2012}, _t2013);
        ;
        U64 _t2014 = 3;
        (void)_t2014;
        Str *_t2015 = Str_lit(":", 1ULL);
        (void)_t2015;
        Array_set(_va23, &(U64){_t2014}, _t2015);
        ;
        U64 _t2016 = 4;
        (void)_t2016;
        Str *_t2017 = I64_to_str(&(I64){col});
        (void)_t2017;
        Array_set(_va23, &(U64){_t2016}, _t2017);
        ;
        U64 _t2018 = 5;
        (void)_t2018;
        Str *_t2019 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2019;
        Array_set(_va23, &(U64){_t2018}, _t2019);
        ;
        println(_va23);
        U64 _t2020 = 1;
        (void)_t2020;
        I64 _t2021 = I64_clone(&(I64){col});
        (void)_t2021;
        ;
        Token *_t2022 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2022->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2020}); _t2022->text = *_ca; free(_ca); }
        _t2022->line = I64_clone(&(I64){line});
        _t2022->col = _t2021;
        (void)_t2022;
        ;
        ;
        ;
        Vec_push(tokens, _t2022);
        U64 _t2023 = U64_inc(DEREF(pos));
        (void)_t2023;
        *pos = _t2023;
        ;
    }
    ;
    U64 _t2026 = U64_sub(DEREF(pos), line_start);
    (void)_t2026;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2027 = 1;
    (void)_t2027;
    U64 _t2028 = U64_add(_t2026, _t2027);
    (void)_t2028;
    ;
    ;
    I64 col = U64_to_i64(_t2028);
    (void)col;
    ;
    I64 _t2029 = I64_clone(&(I64){col});
    (void)_t2029;
    ;
    Token *_t2030 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2030->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2030->text = *_ca; free(_ca); }
    _t2030->line = I64_clone(&(I64){line});
    _t2030->col = _t2029;
    (void)_t2030;
    ;
    ;
    Vec_push(tokens, _t2030);
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
    _t2031 = malloc(sizeof(I64));
    *_t2031 = 0;
    (void)_t2031;
    _t2032 = malloc(sizeof(I64));
    *_t2032 = 1;
    (void)_t2032;
    _t2033 = malloc(sizeof(I64)); *_t2033 = I64_sub(DEREF(_t2031), DEREF(_t2032));
    (void)_t2033;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2033));
    (void)CAP_LIT;
    _t2034 = malloc(sizeof(I64));
    *_t2034 = 0;
    (void)_t2034;
    _t2035 = malloc(sizeof(I64));
    *_t2035 = 2;
    (void)_t2035;
    _t2036 = malloc(sizeof(I64)); *_t2036 = I64_sub(DEREF(_t2034), DEREF(_t2035));
    (void)_t2036;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2036));
    (void)CAP_VIEW;
}

