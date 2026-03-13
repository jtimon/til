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

static I64 *_t2131;
static I64 *_t2132;
static I64 *_t2133;
static U64 *CAP_LIT;
static I64 *_t2134;
static I64 *_t2135;
static I64 *_t2136;
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
        Str *_t366 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
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
        Str *_t383 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
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
            Str *_t428 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
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
    Str *_t475 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
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
            Str *_t597 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
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
        Str *_t696 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
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
    U64 min_len = a->count;
    (void)min_len;
    Bool _t711; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t711 = *_hp; free(_hp); }
    (void)_t711;
    if (_t711) {
        min_len = b->count;
    }
    ;
    {
        U64 _fi700 = 0;
        (void)_fi700;
        while (1) {
            U64 _t702 = 0;
            (void)_t702;
            Range *_t703 = Range_new(_t702, min_len);
            (void)_t703;
            ;
            U64 _t704; { U64 *_hp = (U64 *)Range_len(_t703); _t704 = *_hp; free(_hp); }
            (void)_t704;
            Range_delete(_t703, &(Bool){1});
            Bool _wcond701; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi700}, &(U64){_t704}); _wcond701 = *_hp; free(_hp); }
            (void)_wcond701;
            ;
            if (_wcond701) {
            } else {
                ;
                break;
            }
            ;
            U64 _t705 = 0;
            (void)_t705;
            Range *_t706 = Range_new(_t705, min_len);
            (void)_t706;
            ;
            U64 *i = Range_get(_t706, _fi700);
            (void)i;
            Range_delete(_t706, &(Bool){1});
            U64 _t707 = 1;
            (void)_t707;
            U64 _t708 = U64_add(_fi700, _t707);
            (void)_t708;
            ;
            _fi700 = _t708;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t709 = 0;
            (void)_t709;
            Bool _t710; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t709}); _t710 = *_hp; free(_hp); }
            (void)_t710;
            ;
            if (_t710) {
                ;
                ;
                return c;
            }
            ;
            I64_delete(c, &(Bool){1});
        }
        ;
    }
    ;
    I64 _t712 = U64_cmp(a->count, b->count);
    (void)_t712;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t712; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t713 = 1;
    (void)_t713;
    U64 _t714 = U64_add(DEREF(new_len), _t713);
    (void)_t714;
    ;
    U8 *new_data = malloc(_t714);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t715 = ptr_add(new_data, a->count);
    (void)_t715;
    memcpy(_t715, b->c_str, b->count);
    void *_t716 = ptr_add(new_data, DEREF(new_len));
    (void)_t716;
    I32 _t717 = 0;
    (void)_t717;
    U64 _t718 = 1;
    (void)_t718;
    memset(_t716, _t717, _t718);
    ;
    ;
    U64 _t719 = U64_clone(new_len);
    (void)_t719;
    U64 _t720 = U64_clone(new_len);
    (void)_t720;
    U64_delete(new_len, &(Bool){1});
    Str *_t721 = malloc(sizeof(Str));
    _t721->c_str = new_data;
    _t721->count = _t719;
    _t721->cap = _t720;
    (void)_t721;
    ;
    ;
    return _t721;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t722 = 1;
    (void)_t722;
    U64 _t723 = U64_add(DEREF(n), _t722);
    (void)_t723;
    ;
    U8 *buf = malloc(_t723);
    (void)buf;
    ;
    I32 _t724 = 0;
    (void)_t724;
    U64 _t725 = 1;
    (void)_t725;
    memset(buf, _t724, _t725);
    ;
    ;
    I64 _t726 = 0;
    (void)_t726;
    U64 _t727 = U64_clone(n);
    (void)_t727;
    Str *_t728 = malloc(sizeof(Str));
    _t728->c_str = buf;
    _t728->count = _t726;
    _t728->cap = _t727;
    (void)_t728;
    ;
    ;
    return _t728;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t741; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t741 = *_hp; free(_hp); }
    (void)_t741;
    if (_t741) {
        Str *_t729 = Str_lit("Str", 3ULL);
        (void)_t729;
        U64 _t730; { U64 *_hp = (U64 *)Str_size(); _t730 = *_hp; free(_hp); }
        (void)_t730;
        U64 _t731 = 1;
        (void)_t731;
        Array *_va13 = Array_new(_t729, &(U64){_t730}, &(U64){_t731});
        (void)_va13;
        Str_delete(_t729, &(Bool){1});
        ;
        ;
        U64 _t732 = 0;
        (void)_t732;
        Str *_t733 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t733;
        Array_set(_va13, &(U64){_t732}, _t733);
        ;
        Str *_t734 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t734;
        panic(_t734, _va13);
        Str_delete(_t734, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t742; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t742 = *_hp; free(_hp); }
    (void)_t742;
    if (_t742) {
        Str *_t735 = Str_lit("Str", 3ULL);
        (void)_t735;
        U64 _t736; { U64 *_hp = (U64 *)Str_size(); _t736 = *_hp; free(_hp); }
        (void)_t736;
        U64 _t737 = 1;
        (void)_t737;
        Array *_va14 = Array_new(_t735, &(U64){_t736}, &(U64){_t737});
        (void)_va14;
        Str_delete(_t735, &(Bool){1});
        ;
        ;
        U64 _t738 = 0;
        (void)_t738;
        Str *_t739 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t739;
        Array_set(_va14, &(U64){_t738}, _t739);
        ;
        Str *_t740 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t740;
        panic(_t740, _va14);
        Str_delete(_t740, &(Bool){1});
    }
    ;
    void *_t743 = ptr_add(self->c_str, self->count);
    (void)_t743;
    memcpy(_t743, s->c_str, s->count);
    U64 _t744 = U64_clone(new_len);
    (void)_t744;
    self->count = _t744;
    ;
    void *_t745 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t745;
    I32 _t746 = 0;
    (void)_t746;
    U64 _t747 = 1;
    (void)_t747;
    memset(_t745, _t746, _t747);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t748 = 1;
    (void)_t748;
    U64 _t749 = U64_add(val->count, _t748);
    (void)_t749;
    ;
    U8 *new_data = malloc(_t749);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t750 = ptr_add(new_data, val->count);
    (void)_t750;
    I32 _t751 = 0;
    (void)_t751;
    U64 _t752 = 1;
    (void)_t752;
    memset(_t750, _t751, _t752);
    ;
    ;
    Str *_t753 = malloc(sizeof(Str));
    _t753->c_str = new_data;
    _t753->count = val->count;
    _t753->cap = val->count;
    (void)_t753;
    return _t753;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t754; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t754 = *_hp; free(_hp); }
    (void)_t754;
    if (_t754) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t755 = Str_clone(val);
    (void)_t755;
    return _t755;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t757; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t757 = *_hp; free(_hp); }
    (void)_t757;
    if (_t757) {
        *st = s->count;
    }
    ;
    U64 _t758 = U64_add(DEREF(st), ln);
    (void)_t758;
    Bool _t759; { Bool *_hp = (Bool *)U64_gt(&(U64){_t758}, &s->count); _t759 = *_hp; free(_hp); }
    (void)_t759;
    ;
    if (_t759) {
        U64 _t756 = U64_sub(s->count, DEREF(st));
        (void)_t756;
        ln = _t756;
        ;
    }
    ;
    void *_t760 = ptr_add(s->c_str, DEREF(st));
    (void)_t760;
    U64 _t761 = U64_clone(&(U64){ln});
    (void)_t761;
    ;
    U64 _t762 = U64_clone(CAP_VIEW);
    (void)_t762;
    Str *_t763 = malloc(sizeof(Str));
    _t763->c_str = _t760;
    _t763->count = _t761;
    _t763->cap = _t762;
    (void)_t763;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t763;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t794 = 0;
    (void)_t794;
    Bool _t795 = U64_eq(b->count, _t794);
    (void)_t795;
    ;
    if (_t795) {
        Bool _t764 = 1;
        (void)_t764;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t764; return _r; }
    }
    ;
    Bool _t796; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t796 = *_hp; free(_hp); }
    (void)_t796;
    if (_t796) {
        Bool _t765 = 0;
        (void)_t765;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t765; return _r; }
    }
    ;
    {
        U64 _fi766 = 0;
        (void)_fi766;
        while (1) {
            U64 _t781 = U64_sub(a->count, b->count);
            (void)_t781;
            U64 _t782 = 1;
            (void)_t782;
            U64 _t783 = 0;
            (void)_t783;
            U64 _t784 = U64_add(_t781, _t782);
            (void)_t784;
            ;
            ;
            Range *_t785 = Range_new(_t783, _t784);
            (void)_t785;
            ;
            ;
            U64 _t786; { U64 *_hp = (U64 *)Range_len(_t785); _t786 = *_hp; free(_hp); }
            (void)_t786;
            Range_delete(_t785, &(Bool){1});
            Bool _wcond767; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi766}, &(U64){_t786}); _wcond767 = *_hp; free(_hp); }
            (void)_wcond767;
            ;
            if (_wcond767) {
            } else {
                ;
                break;
            }
            ;
            U64 _t787 = U64_sub(a->count, b->count);
            (void)_t787;
            U64 _t788 = 1;
            (void)_t788;
            U64 _t789 = 0;
            (void)_t789;
            U64 _t790 = U64_add(_t787, _t788);
            (void)_t790;
            ;
            ;
            Range *_t791 = Range_new(_t789, _t790);
            (void)_t791;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t791, _fi766); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t791, &(Bool){1});
            U64 _t792 = 1;
            (void)_t792;
            U64 _t793 = U64_add(_fi766, _t792);
            (void)_t793;
            ;
            _fi766 = _t793;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi768 = 0;
                (void)_fi768;
                while (1) {
                    U64 _t771 = 0;
                    (void)_t771;
                    Range *_t772 = Range_new(_t771, b->count);
                    (void)_t772;
                    ;
                    U64 _t773; { U64 *_hp = (U64 *)Range_len(_t772); _t773 = *_hp; free(_hp); }
                    (void)_t773;
                    Range_delete(_t772, &(Bool){1});
                    Bool _wcond769; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi768}, &(U64){_t773}); _wcond769 = *_hp; free(_hp); }
                    (void)_wcond769;
                    ;
                    if (_wcond769) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t774 = 0;
                    (void)_t774;
                    Range *_t775 = Range_new(_t774, b->count);
                    (void)_t775;
                    ;
                    U64 *j = Range_get(_t775, _fi768);
                    (void)j;
                    Range_delete(_t775, &(Bool){1});
                    U64 _t776 = 1;
                    (void)_t776;
                    U64 _t777 = U64_add(_fi768, _t776);
                    (void)_t777;
                    ;
                    _fi768 = _t777;
                    ;
                    U64 *_t778 = malloc(sizeof(U64)); *_t778 = U64_add(i, DEREF(j));
                    (void)_t778;
                    U8 *ac = Str_get(a, _t778);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t779; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t779 = *_hp; free(_hp); }
                    (void)_t779;
                    U64_delete(_t778, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t779) {
                        Bool _t770 = 0;
                        (void)_t770;
                        found = _t770;
                        ;
                    }
                    ;
                }
                ;
            }
            ;
            if (found) {
                Bool _t780 = 1;
                (void)_t780;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t780; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t797 = 0;
    (void)_t797;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t797; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t810; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t810 = *_hp; free(_hp); }
    (void)_t810;
    if (_t810) {
        Bool _t798 = 0;
        (void)_t798;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t798; return _r; }
    }
    ;
    {
        U64 _fi799 = 0;
        (void)_fi799;
        while (1) {
            U64 _t802 = 0;
            (void)_t802;
            Range *_t803 = Range_new(_t802, b->count);
            (void)_t803;
            ;
            U64 _t804; { U64 *_hp = (U64 *)Range_len(_t803); _t804 = *_hp; free(_hp); }
            (void)_t804;
            Range_delete(_t803, &(Bool){1});
            Bool _wcond800; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi799}, &(U64){_t804}); _wcond800 = *_hp; free(_hp); }
            (void)_wcond800;
            ;
            if (_wcond800) {
            } else {
                ;
                break;
            }
            ;
            U64 _t805 = 0;
            (void)_t805;
            Range *_t806 = Range_new(_t805, b->count);
            (void)_t806;
            ;
            U64 *i = Range_get(_t806, _fi799);
            (void)i;
            Range_delete(_t806, &(Bool){1});
            U64 _t807 = 1;
            (void)_t807;
            U64 _t808 = U64_add(_fi799, _t807);
            (void)_t808;
            ;
            _fi799 = _t808;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t809; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t809 = *_hp; free(_hp); }
            (void)_t809;
            U64_delete(i, &(Bool){1});
            if (_t809) {
                Bool _t801 = 0;
                (void)_t801;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t801; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t811 = 1;
    (void)_t811;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t811; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t825; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t825 = *_hp; free(_hp); }
    (void)_t825;
    if (_t825) {
        Bool _t812 = 0;
        (void)_t812;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t812; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _fi813 = 0;
        (void)_fi813;
        while (1) {
            U64 _t816 = 0;
            (void)_t816;
            Range *_t817 = Range_new(_t816, b->count);
            (void)_t817;
            ;
            U64 _t818; { U64 *_hp = (U64 *)Range_len(_t817); _t818 = *_hp; free(_hp); }
            (void)_t818;
            Range_delete(_t817, &(Bool){1});
            Bool _wcond814; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi813}, &(U64){_t818}); _wcond814 = *_hp; free(_hp); }
            (void)_wcond814;
            ;
            if (_wcond814) {
            } else {
                ;
                break;
            }
            ;
            U64 _t819 = 0;
            (void)_t819;
            Range *_t820 = Range_new(_t819, b->count);
            (void)_t820;
            ;
            U64 *i = Range_get(_t820, _fi813);
            (void)i;
            Range_delete(_t820, &(Bool){1});
            U64 _t821 = 1;
            (void)_t821;
            U64 _t822 = U64_add(_fi813, _t821);
            (void)_t822;
            ;
            _fi813 = _t822;
            ;
            U64 *_t823 = malloc(sizeof(U64)); *_t823 = U64_add(offset, DEREF(i));
            (void)_t823;
            U8 *ac = Str_get(a, _t823);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t824; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t824 = *_hp; free(_hp); }
            (void)_t824;
            U64_delete(_t823, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t824) {
                Bool _t815 = 0;
                (void)_t815;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t815; return _r; }
            }
            ;
        }
        ;
    }
    ;
    Bool _t826 = 1;
    (void)_t826;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t826; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t827 = 0;
    (void)_t827;
    Bool _t828 = U64_eq(self->count, _t827);
    (void)_t828;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t828; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t863 = 0;
    (void)_t863;
    Bool _t864 = U64_eq(needle->count, _t863);
    (void)_t864;
    ;
    if (_t864) {
        I64 _t829 = 0;
        (void)_t829;
        I64 _t830 = 1;
        (void)_t830;
        I64 _t831 = I64_sub(_t829, _t830);
        (void)_t831;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t831; return _r; }
    }
    ;
    Bool _t865; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t865 = *_hp; free(_hp); }
    (void)_t865;
    if (_t865) {
        I64 _t832 = 0;
        (void)_t832;
        I64 _t833 = 1;
        (void)_t833;
        I64 _t834 = I64_sub(_t832, _t833);
        (void)_t834;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t834; return _r; }
    }
    ;
    {
        U64 _fi835 = 0;
        (void)_fi835;
        while (1) {
            U64 _t850 = U64_sub(self->count, needle->count);
            (void)_t850;
            U64 _t851 = 1;
            (void)_t851;
            U64 _t852 = 0;
            (void)_t852;
            U64 _t853 = U64_add(_t850, _t851);
            (void)_t853;
            ;
            ;
            Range *_t854 = Range_new(_t852, _t853);
            (void)_t854;
            ;
            ;
            U64 _t855; { U64 *_hp = (U64 *)Range_len(_t854); _t855 = *_hp; free(_hp); }
            (void)_t855;
            Range_delete(_t854, &(Bool){1});
            Bool _wcond836; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi835}, &(U64){_t855}); _wcond836 = *_hp; free(_hp); }
            (void)_wcond836;
            ;
            if (_wcond836) {
            } else {
                ;
                break;
            }
            ;
            U64 _t856 = U64_sub(self->count, needle->count);
            (void)_t856;
            U64 _t857 = 1;
            (void)_t857;
            U64 _t858 = 0;
            (void)_t858;
            U64 _t859 = U64_add(_t856, _t857);
            (void)_t859;
            ;
            ;
            Range *_t860 = Range_new(_t858, _t859);
            (void)_t860;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t860, _fi835); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t860, &(Bool){1});
            U64 _t861 = 1;
            (void)_t861;
            U64 _t862 = U64_add(_fi835, _t861);
            (void)_t862;
            ;
            _fi835 = _t862;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi837 = 0;
                (void)_fi837;
                while (1) {
                    U64 _t840 = 0;
                    (void)_t840;
                    Range *_t841 = Range_new(_t840, needle->count);
                    (void)_t841;
                    ;
                    U64 _t842; { U64 *_hp = (U64 *)Range_len(_t841); _t842 = *_hp; free(_hp); }
                    (void)_t842;
                    Range_delete(_t841, &(Bool){1});
                    Bool _wcond838; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi837}, &(U64){_t842}); _wcond838 = *_hp; free(_hp); }
                    (void)_wcond838;
                    ;
                    if (_wcond838) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t843 = 0;
                    (void)_t843;
                    Range *_t844 = Range_new(_t843, needle->count);
                    (void)_t844;
                    ;
                    U64 *j = Range_get(_t844, _fi837);
                    (void)j;
                    Range_delete(_t844, &(Bool){1});
                    U64 _t845 = 1;
                    (void)_t845;
                    U64 _t846 = U64_add(_fi837, _t845);
                    (void)_t846;
                    ;
                    _fi837 = _t846;
                    ;
                    U64 *_t847 = malloc(sizeof(U64)); *_t847 = U64_add(i, DEREF(j));
                    (void)_t847;
                    U8 *ac = Str_get(self, _t847);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t848; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t848 = *_hp; free(_hp); }
                    (void)_t848;
                    U64_delete(_t847, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t848) {
                        Bool _t839 = 0;
                        (void)_t839;
                        found = _t839;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t849 = U64_to_i64(i);
                (void)_t849;
                ;
                ;
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t849; return _r; }
            }
            ;
            ;
        }
        ;
    }
    I64 _t866 = 0;
    (void)_t866;
    I64 _t867 = 1;
    (void)_t867;
    I64 _t868 = I64_sub(_t866, _t867);
    (void)_t868;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t868; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t903 = 0;
    (void)_t903;
    Bool _t904 = U64_eq(needle->count, _t903);
    (void)_t904;
    ;
    if (_t904) {
        I64 _t869 = 0;
        (void)_t869;
        I64 _t870 = 1;
        (void)_t870;
        I64 _t871 = I64_sub(_t869, _t870);
        (void)_t871;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t871; return _r; }
    }
    ;
    Bool _t905; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t905 = *_hp; free(_hp); }
    (void)_t905;
    if (_t905) {
        I64 _t872 = 0;
        (void)_t872;
        I64 _t873 = 1;
        (void)_t873;
        I64 _t874 = I64_sub(_t872, _t873);
        (void)_t874;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t874; return _r; }
    }
    ;
    I64 _t906 = 0;
    (void)_t906;
    I64 _t907 = 1;
    (void)_t907;
    I64 last = I64_sub(_t906, _t907);
    (void)last;
    ;
    ;
    {
        U64 _fi875 = 0;
        (void)_fi875;
        while (1) {
            U64 _t890 = U64_sub(self->count, needle->count);
            (void)_t890;
            U64 _t891 = 1;
            (void)_t891;
            U64 _t892 = 0;
            (void)_t892;
            U64 _t893 = U64_add(_t890, _t891);
            (void)_t893;
            ;
            ;
            Range *_t894 = Range_new(_t892, _t893);
            (void)_t894;
            ;
            ;
            U64 _t895; { U64 *_hp = (U64 *)Range_len(_t894); _t895 = *_hp; free(_hp); }
            (void)_t895;
            Range_delete(_t894, &(Bool){1});
            Bool _wcond876; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi875}, &(U64){_t895}); _wcond876 = *_hp; free(_hp); }
            (void)_wcond876;
            ;
            if (_wcond876) {
            } else {
                ;
                break;
            }
            ;
            U64 _t896 = U64_sub(self->count, needle->count);
            (void)_t896;
            U64 _t897 = 1;
            (void)_t897;
            U64 _t898 = 0;
            (void)_t898;
            U64 _t899 = U64_add(_t896, _t897);
            (void)_t899;
            ;
            ;
            Range *_t900 = Range_new(_t898, _t899);
            (void)_t900;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t900, _fi875); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t900, &(Bool){1});
            U64 _t901 = 1;
            (void)_t901;
            U64 _t902 = U64_add(_fi875, _t901);
            (void)_t902;
            ;
            _fi875 = _t902;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi877 = 0;
                (void)_fi877;
                while (1) {
                    U64 _t880 = 0;
                    (void)_t880;
                    Range *_t881 = Range_new(_t880, needle->count);
                    (void)_t881;
                    ;
                    U64 _t882; { U64 *_hp = (U64 *)Range_len(_t881); _t882 = *_hp; free(_hp); }
                    (void)_t882;
                    Range_delete(_t881, &(Bool){1});
                    Bool _wcond878; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi877}, &(U64){_t882}); _wcond878 = *_hp; free(_hp); }
                    (void)_wcond878;
                    ;
                    if (_wcond878) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t883 = 0;
                    (void)_t883;
                    Range *_t884 = Range_new(_t883, needle->count);
                    (void)_t884;
                    ;
                    U64 *j = Range_get(_t884, _fi877);
                    (void)j;
                    Range_delete(_t884, &(Bool){1});
                    U64 _t885 = 1;
                    (void)_t885;
                    U64 _t886 = U64_add(_fi877, _t885);
                    (void)_t886;
                    ;
                    _fi877 = _t886;
                    ;
                    U64 *_t887 = malloc(sizeof(U64)); *_t887 = U64_add(i, DEREF(j));
                    (void)_t887;
                    U8 *ac = Str_get(self, _t887);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t888; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t888 = *_hp; free(_hp); }
                    (void)_t888;
                    U64_delete(_t887, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t888) {
                        Bool _t879 = 0;
                        (void)_t879;
                        found = _t879;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t889 = U64_to_i64(i);
                (void)_t889;
                last = _t889;
                ;
            }
            ;
            ;
        }
        ;
    }
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t923 = 0;
    (void)_t923;
    Bool _t924 = U64_eq(from->count, _t923);
    (void)_t924;
    ;
    if (_t924) {
        Str *_t908 = Str_clone(self);
        (void)_t908;
        ;
        return _t908;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t910 = U64_sub(self->count, from->count);
        (void)_t910;
        Bool _wcond909; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t910}); _wcond909 = *_hp; free(_hp); }
        (void)_wcond909;
        ;
        if (_wcond909) {
        } else {
            ;
            break;
        }
        ;
        U64 _t911 = U64_sub(self->count, start);
        (void)_t911;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t911});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t912 = 0;
        (void)_t912;
        I64 _t913 = 1;
        (void)_t913;
        I64 _t914 = I64_sub(_t912, _t913);
        (void)_t914;
        ;
        ;
        Bool _t915 = I64_eq(pos, _t914);
        (void)_t915;
        ;
        if (_t915) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t916 = I64_to_u64(pos);
        (void)_t916;
        Str *_t917 = Str_substr(self, &(U64){start}, &(U64){_t916});
        (void)_t917;
        ;
        result = Str_concat(result, _t917);
        Str_delete(_t917, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t918 = I64_to_u64(pos);
        (void)_t918;
        ;
        U64 _t919 = U64_add(start, _t918);
        (void)_t919;
        ;
        U64 _t920 = U64_add(_t919, from->count);
        (void)_t920;
        ;
        start = _t920;
        ;
    }
    Bool _t925; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t925 = *_hp; free(_hp); }
    (void)_t925;
    if (_t925) {
        U64 _t921 = U64_sub(self->count, start);
        (void)_t921;
        Str *_t922 = Str_substr(self, &(U64){start}, &(U64){_t921});
        (void)_t922;
        ;
        result = Str_concat(result, _t922);
        Str_delete(_t922, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t926 = 1;
    (void)_t926;
    Str *_t927 = Str_substr(self, i, &(U64){_t926});
    (void)_t927;
    ;
    return _t927;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t930; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t930 = *_hp; free(_hp); }
    (void)_t930;
    if (_t930) {
        U64 _t928 = U64_sub(self->count, prefix->count);
        (void)_t928;
        Str *_t929 = Str_substr(self, &prefix->count, &(U64){_t928});
        (void)_t929;
        ;
        ;
        return _t929;
    }
    ;
    Str *_t931 = Str_clone(self);
    (void)_t931;
    return _t931;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t935; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t935 = *_hp; free(_hp); }
    (void)_t935;
    if (_t935) {
        U64 _t932 = 0;
        (void)_t932;
        U64 _t933 = U64_sub(self->count, suffix->count);
        (void)_t933;
        Str *_t934 = Str_substr(self, &(U64){_t932}, &(U64){_t933});
        (void)_t934;
        ;
        ;
        ;
        return _t934;
    }
    ;
    Str *_t936 = Str_clone(self);
    (void)_t936;
    return _t936;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t937 = 2;
    (void)_t937;
    U8 *buf = malloc(_t937);
    (void)buf;
    ;
    U64 _t938 = 1;
    (void)_t938;
    memcpy(buf, byte, _t938);
    ;
    U64 *_t939 = malloc(sizeof(U64));
    *_t939 = 1;
    (void)_t939;
    void *_t940 = ptr_add(buf, DEREF(_t939));
    (void)_t940;
    I32 _t941 = 0;
    (void)_t941;
    U64 _t942 = 1;
    (void)_t942;
    memset(_t940, _t941, _t942);
    U64_delete(_t939, &(Bool){1});
    ;
    ;
    I64 _t943 = 1;
    (void)_t943;
    I64 _t944 = 1;
    (void)_t944;
    Str *_t945 = malloc(sizeof(Str));
    _t945->c_str = buf;
    _t945->count = _t943;
    _t945->cap = _t944;
    (void)_t945;
    ;
    ;
    return _t945;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t989 = 0;
    (void)_t989;
    Bool _t990 = U64_eq(self->count, _t989);
    (void)_t990;
    ;
    if (_t990) {
        Str *_t946 = Str_lit("Str", 3ULL);
        (void)_t946;
        U64 _t947; { U64 *_hp = (U64 *)Str_size(); _t947 = *_hp; free(_hp); }
        (void)_t947;
        U64 _t948 = 1;
        (void)_t948;
        Array *_va15 = Array_new(_t946, &(U64){_t947}, &(U64){_t948});
        (void)_va15;
        Str_delete(_t946, &(Bool){1});
        ;
        ;
        U64 _t949 = 0;
        (void)_t949;
        Str *_t950 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t950;
        Array_set(_va15, &(U64){_t949}, _t950);
        ;
        Str *_t951 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t951;
        panic(_t951, _va15);
        Str_delete(_t951, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t991 = malloc(sizeof(U64));
    *_t991 = 0;
    (void)_t991;
    U8 *first = Str_get(self, _t991);
    (void)first;
    U8 _t992 = 45;
    (void)_t992;
    Bool _t993 = U8_eq(DEREF(first), _t992);
    (void)_t993;
    U64_delete(_t991, &(Bool){1});
    ;
    if (_t993) {
        Bool _t952 = 1;
        (void)_t952;
        neg = _t952;
        ;
        U64 _t953 = 1;
        (void)_t953;
        start = _t953;
        ;
    }
    ;
    Bool _t994 = U64_eq(start, self->count);
    (void)_t994;
    if (_t994) {
        Str *_t954 = Str_lit("Str", 3ULL);
        (void)_t954;
        U64 _t955; { U64 *_hp = (U64 *)Str_size(); _t955 = *_hp; free(_hp); }
        (void)_t955;
        U64 _t956 = 1;
        (void)_t956;
        Array *_va16 = Array_new(_t954, &(U64){_t955}, &(U64){_t956});
        (void)_va16;
        Str_delete(_t954, &(Bool){1});
        ;
        ;
        U64 _t957 = 0;
        (void)_t957;
        Str *_t958 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t958;
        Array_set(_va16, &(U64){_t957}, _t958);
        ;
        Str *_t959 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t959;
        panic(_t959, _va16);
        Str_delete(_t959, &(Bool){1});
    }
    ;
    {
        U64 _fi960 = 0;
        (void)_fi960;
        while (1) {
            Range *_t972 = Range_new(start, self->count);
            (void)_t972;
            U64 _t973; { U64 *_hp = (U64 *)Range_len(_t972); _t973 = *_hp; free(_hp); }
            (void)_t973;
            Range_delete(_t972, &(Bool){1});
            Bool _wcond961; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi960}, &(U64){_t973}); _wcond961 = *_hp; free(_hp); }
            (void)_wcond961;
            ;
            if (_wcond961) {
            } else {
                ;
                break;
            }
            ;
            Range *_t974 = Range_new(start, self->count);
            (void)_t974;
            U64 *i = Range_get(_t974, _fi960);
            (void)i;
            Range_delete(_t974, &(Bool){1});
            U64 _t975 = 1;
            (void)_t975;
            U64 _t976 = U64_add(_fi960, _t975);
            (void)_t976;
            ;
            _fi960 = _t976;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t977 = U8_to_i64(DEREF(ch));
            (void)_t977;
            U64_delete(i, &(Bool){1});
            I64 _t978 = 48;
            (void)_t978;
            I64 d = I64_sub(_t977, _t978);
            (void)d;
            ;
            ;
            I64 _t979 = 0;
            (void)_t979;
            I64 _t980 = 9;
            (void)_t980;
            Bool _t981; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t979}); _t981 = *_hp; free(_hp); }
            (void)_t981;
            ;
            Bool _t982; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t980}); _t982 = *_hp; free(_hp); }
            (void)_t982;
            ;
            Bool _t983 = Bool_or(_t981, _t982);
            (void)_t983;
            ;
            ;
            if (_t983) {
                Str *_t962 = Str_lit("Str", 3ULL);
                (void)_t962;
                U64 _t963; { U64 *_hp = (U64 *)Str_size(); _t963 = *_hp; free(_hp); }
                (void)_t963;
                U64 _t964 = 3;
                (void)_t964;
                Array *_va17 = Array_new(_t962, &(U64){_t963}, &(U64){_t964});
                (void)_va17;
                Str_delete(_t962, &(Bool){1});
                ;
                ;
                U64 _t965 = 0;
                (void)_t965;
                Str *_t966 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t966;
                Array_set(_va17, &(U64){_t965}, _t966);
                ;
                U64 _t967 = 1;
                (void)_t967;
                Str *_t968 = Str_clone(self);
                (void)_t968;
                Array_set(_va17, &(U64){_t967}, _t968);
                ;
                U64 _t969 = 2;
                (void)_t969;
                Str *_t970 = Str_lit("'", 1ULL);
                (void)_t970;
                Array_set(_va17, &(U64){_t969}, _t970);
                ;
                Str *_t971 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t971;
                panic(_t971, _va17);
                Str_delete(_t971, &(Bool){1});
            }
            ;
            I64 _t984 = 10;
            (void)_t984;
            I64 _t985 = I64_mul(result, _t984);
            (void)_t985;
            ;
            I64 _t986 = I64_add(_t985, d);
            (void)_t986;
            ;
            ;
            result = _t986;
            ;
        }
        ;
    }
    ;
    if (neg) {
        I64 _t987 = 0;
        (void)_t987;
        I64 _t988 = I64_sub(_t987, result);
        (void)_t988;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t988; return _r; }
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
    I64 _t996; { I64 *_hp = (I64 *)Str_cmp(a, b); _t996 = *_hp; free(_hp); }
    (void)_t996;
    I64 _t997 = 0;
    (void)_t997;
    Bool _t998 = I64_eq(_t996, _t997);
    (void)_t998;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t998; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t999 = 0;
    (void)_t999;
    I64 _t1000 = 1;
    (void)_t1000;
    I64 _t1001; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1001 = *_hp; free(_hp); }
    (void)_t1001;
    I64 _t1002 = I64_sub(_t999, _t1000);
    (void)_t1002;
    ;
    ;
    Bool _t1003 = I64_eq(_t1001, _t1002);
    (void)_t1003;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1003; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1004; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1004 = *_hp; free(_hp); }
    (void)_t1004;
    I64 _t1005 = 1;
    (void)_t1005;
    Bool _t1006 = I64_eq(_t1004, _t1005);
    (void)_t1006;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1006; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1007; { Bool *_hp = (Bool *)Str_eq(a, b); _t1007 = *_hp; free(_hp); }
    (void)_t1007;
    Bool _t1008 = Bool_not(_t1007);
    (void)_t1008;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1008; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1009; { Bool *_hp = (Bool *)Str_gt(a, b); _t1009 = *_hp; free(_hp); }
    (void)_t1009;
    Bool _t1010 = Bool_not(_t1009);
    (void)_t1010;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1010; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1011; { Bool *_hp = (Bool *)Str_lt(a, b); _t1011 = *_hp; free(_hp); }
    (void)_t1011;
    Bool _t1012 = Bool_not(_t1011);
    (void)_t1012;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1012; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1013 = malloc(DEREF(elem_size));
    (void)_t1013;
    U64 _t1014 = 0;
    (void)_t1014;
    I64 _t1015 = 1;
    (void)_t1015;
    U64 _t1016 = U64_clone(elem_size);
    (void)_t1016;
    Vec *_t1017 = malloc(sizeof(Vec));
    _t1017->data = _t1013;
    _t1017->count = _t1014;
    _t1017->cap = _t1015;
    _t1017->elem_size = _t1016;
    { Str *_ca = Str_clone(elem_type); _t1017->elem_type = *_ca; free(_ca); }
    (void)_t1017;
    ;
    ;
    ;
    return _t1017;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1022 = U64_eq(self->count, self->cap);
    (void)_t1022;
    if (_t1022) {
        U64 _t1018 = 2;
        (void)_t1018;
        U64 new_cap = U64_mul(self->cap, _t1018);
        (void)new_cap;
        ;
        U64 _t1019 = U64_mul(new_cap, self->elem_size);
        (void)_t1019;
        void *_t1020 = realloc(self->data, _t1019);
        (void)_t1020;
        ;
        self->data = _t1020;
        U64 _t1021 = U64_clone(&(U64){new_cap});
        (void)_t1021;
        ;
        self->cap = _t1021;
        ;
    }
    ;
    U64 *_t1023 = malloc(sizeof(U64)); *_t1023 = U64_mul(self->count, self->elem_size);
    (void)_t1023;
    void *_t1024 = ptr_add(self->data, DEREF(_t1023));
    (void)_t1024;
    memcpy(_t1024, val, self->elem_size);
    U64_delete(_t1023, &(Bool){1});
    free(val);
    U64 _t1025 = 1;
    (void)_t1025;
    U64 _t1026 = U64_add(self->count, _t1025);
    (void)_t1026;
    ;
    self->count = _t1026;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1041; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1041 = *_hp; free(_hp); }
    (void)_t1041;
    if (_t1041) {
        Str *_t1027 = Str_lit("Str", 3ULL);
        (void)_t1027;
        U64 _t1028; { U64 *_hp = (U64 *)Str_size(); _t1028 = *_hp; free(_hp); }
        (void)_t1028;
        U64 _t1029 = 5;
        (void)_t1029;
        Array *_va18 = Array_new(_t1027, &(U64){_t1028}, &(U64){_t1029});
        (void)_va18;
        Str_delete(_t1027, &(Bool){1});
        ;
        ;
        U64 _t1030 = 0;
        (void)_t1030;
        Str *_t1031 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1031;
        Array_set(_va18, &(U64){_t1030}, _t1031);
        ;
        U64 _t1032 = 1;
        (void)_t1032;
        Str *_t1033 = U64_to_str(DEREF(i));
        (void)_t1033;
        Array_set(_va18, &(U64){_t1032}, _t1033);
        ;
        U64 _t1034 = 2;
        (void)_t1034;
        Str *_t1035 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1035;
        Array_set(_va18, &(U64){_t1034}, _t1035);
        ;
        U64 _t1036 = 3;
        (void)_t1036;
        Str *_t1037 = U64_to_str(self->count);
        (void)_t1037;
        Array_set(_va18, &(U64){_t1036}, _t1037);
        ;
        U64 _t1038 = 4;
        (void)_t1038;
        Str *_t1039 = Str_lit(")", 1ULL);
        (void)_t1039;
        Array_set(_va18, &(U64){_t1038}, _t1039);
        ;
        Str *_t1040 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1040;
        panic(_t1040, _va18);
        Str_delete(_t1040, &(Bool){1});
    }
    ;
    U64 *_t1042 = malloc(sizeof(U64)); *_t1042 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1042;
    void *_t1043 = ptr_add(self->data, DEREF(_t1042));
    (void)_t1043;
    U64_delete(_t1042, &(Bool){1});
    return _t1043;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1057; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1057 = *_hp; free(_hp); }
    (void)_t1057;
    Bool _t1058 = Bool_not(_t1057);
    (void)_t1058;
    ;
    if (_t1058) {
        {
            U64 _fi1044 = 0;
            (void)_fi1044;
            while (1) {
                U64 _t1046 = 0;
                (void)_t1046;
                Range *_t1047 = Range_new(_t1046, self->count);
                (void)_t1047;
                ;
                U64 _t1048; { U64 *_hp = (U64 *)Range_len(_t1047); _t1048 = *_hp; free(_hp); }
                (void)_t1048;
                Range_delete(_t1047, &(Bool){1});
                Bool _wcond1045; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1044}, &(U64){_t1048}); _wcond1045 = *_hp; free(_hp); }
                (void)_wcond1045;
                ;
                if (_wcond1045) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1049 = 0;
                (void)_t1049;
                Range *_t1050 = Range_new(_t1049, self->count);
                (void)_t1050;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1050, _fi1044); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1050, &(Bool){1});
                U64 _t1051 = 1;
                (void)_t1051;
                U64 _t1052 = U64_add(_fi1044, _t1051);
                (void)_t1052;
                ;
                _fi1044 = _t1052;
                ;
                U64 *_t1053 = malloc(sizeof(U64)); *_t1053 = U64_mul(i, self->elem_size);
                (void)_t1053;
                ;
                void *_t1054 = ptr_add(self->data, DEREF(_t1053));
                (void)_t1054;
                Bool _t1055 = 0;
                (void)_t1055;
                dyn_call_delete(&self->elem_type, _t1054, &(Bool){_t1055});
                U64_delete(_t1053, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1059; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1059 = *_hp; free(_hp); }
    (void)_t1059;
    Bool _t1060 = Bool_not(_t1059);
    (void)_t1060;
    ;
    if (_t1060) {
        Bool _t1056 = 0;
        (void)_t1056;
        Str_delete(&self->elem_type, &(Bool){_t1056});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1074 = U64_mul(self->cap, self->elem_size);
    (void)_t1074;
    U8 *new_data = malloc(_t1074);
    (void)new_data;
    ;
    {
        U64 _fi1061 = 0;
        (void)_fi1061;
        while (1) {
            U64 _t1063 = 0;
            (void)_t1063;
            Range *_t1064 = Range_new(_t1063, self->count);
            (void)_t1064;
            ;
            U64 _t1065; { U64 *_hp = (U64 *)Range_len(_t1064); _t1065 = *_hp; free(_hp); }
            (void)_t1065;
            Range_delete(_t1064, &(Bool){1});
            Bool _wcond1062; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1061}, &(U64){_t1065}); _wcond1062 = *_hp; free(_hp); }
            (void)_wcond1062;
            ;
            if (_wcond1062) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1066 = 0;
            (void)_t1066;
            Range *_t1067 = Range_new(_t1066, self->count);
            (void)_t1067;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1067, _fi1061); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1067, &(Bool){1});
            U64 _t1068 = 1;
            (void)_t1068;
            U64 _t1069 = U64_add(_fi1061, _t1068);
            (void)_t1069;
            ;
            _fi1061 = _t1069;
            ;
            U64 *_t1070 = malloc(sizeof(U64)); *_t1070 = U64_mul(i, self->elem_size);
            (void)_t1070;
            void *_t1071 = ptr_add(self->data, DEREF(_t1070));
            (void)_t1071;
            void *cloned = dyn_call_clone(&self->elem_type, _t1071);
            (void)cloned;
            U64_delete(_t1070, &(Bool){1});
            U64 *_t1072 = malloc(sizeof(U64)); *_t1072 = U64_mul(i, self->elem_size);
            (void)_t1072;
            ;
            void *_t1073 = ptr_add(new_data, DEREF(_t1072));
            (void)_t1073;
            memcpy(_t1073, cloned, self->elem_size);
            U64_delete(_t1072, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1075 = malloc(sizeof(Vec));
    _t1075->data = new_data;
    _t1075->count = self->count;
    _t1075->cap = self->cap;
    _t1075->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1075->elem_type = *_ca; free(_ca); }
    (void)_t1075;
    return _t1075;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1093 = Str_lit("Str", 3ULL);
    (void)_t1093;
    U64 _t1094; { U64 *_hp = (U64 *)Str_size(); _t1094 = *_hp; free(_hp); }
    (void)_t1094;
    Vec *parts = Vec_new(_t1093, &(U64){_t1094});
    (void)parts;
    Str_delete(_t1093, &(Bool){1});
    ;
    U64 _t1095; { U64 *_hp = (U64 *)Str_len(delim); _t1095 = *_hp; free(_hp); }
    (void)_t1095;
    U64 _t1096 = 0;
    (void)_t1096;
    Bool _t1097 = U64_eq(_t1095, _t1096);
    (void)_t1097;
    ;
    ;
    if (_t1097) {
        Str *_t1077 = Str_clone(s);
        (void)_t1077;
        Vec_push(parts, _t1077);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1087; { U64 *_hp = (U64 *)Str_len(s); _t1087 = *_hp; free(_hp); }
        (void)_t1087;
        U64 _t1088; { U64 *_hp = (U64 *)Str_len(delim); _t1088 = *_hp; free(_hp); }
        (void)_t1088;
        U64 _t1089 = U64_sub(_t1087, _t1088);
        (void)_t1089;
        ;
        ;
        Bool _wcond1078; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1089}); _wcond1078 = *_hp; free(_hp); }
        (void)_wcond1078;
        ;
        if (_wcond1078) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1090; { U64 *_hp = (U64 *)Str_len(delim); _t1090 = *_hp; free(_hp); }
        (void)_t1090;
        Str *_t1091 = Str_substr(s, &(U64){pos}, &(U64){_t1090});
        (void)_t1091;
        ;
        Bool _t1092; { Bool *_hp = (Bool *)Str_eq(_t1091, delim); _t1092 = *_hp; free(_hp); }
        (void)_t1092;
        Str_delete(_t1091, &(Bool){1});
        if (_t1092) {
            U64 _t1079 = U64_sub(pos, start);
            (void)_t1079;
            Str *_t1080 = Str_substr(s, &(U64){start}, &(U64){_t1079});
            (void)_t1080;
            ;
            Str *_t1081 = Str_clone(_t1080);
            (void)_t1081;
            Str_delete(_t1080, &(Bool){1});
            Vec_push(parts, _t1081);
            U64 _t1082; { U64 *_hp = (U64 *)Str_len(delim); _t1082 = *_hp; free(_hp); }
            (void)_t1082;
            U64 _t1083 = U64_add(pos, _t1082);
            (void)_t1083;
            ;
            start = _t1083;
            ;
            U64 _t1084 = U64_clone(&(U64){start});
            (void)_t1084;
            pos = _t1084;
            ;
        } else {
            U64 _t1085 = 1;
            (void)_t1085;
            U64 _t1086 = U64_add(pos, _t1085);
            (void)_t1086;
            ;
            pos = _t1086;
            ;
        }
        ;
    }
    ;
    U64 _t1098; { U64 *_hp = (U64 *)Str_len(s); _t1098 = *_hp; free(_hp); }
    (void)_t1098;
    U64 _t1099 = U64_sub(_t1098, start);
    (void)_t1099;
    ;
    Str *_t1100 = Str_substr(s, &(U64){start}, &(U64){_t1099});
    (void)_t1100;
    ;
    ;
    Str *_t1101 = Str_clone(_t1100);
    (void)_t1101;
    Str_delete(_t1100, &(Bool){1});
    Vec_push(parts, _t1101);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1116; { U64 *_hp = (U64 *)Vec_len(parts); _t1116 = *_hp; free(_hp); }
    (void)_t1116;
    U64 _t1117 = 0;
    (void)_t1117;
    Bool _t1118 = U64_eq(_t1116, _t1117);
    (void)_t1118;
    ;
    ;
    if (_t1118) {
        Str *_t1102 = Str_lit("", 0ULL);
        (void)_t1102;
        ;
        return _t1102;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1103 = 0;
        (void)_fi1103;
        while (1) {
            U64 _t1105 = 0;
            (void)_t1105;
            U64 _t1106; { U64 *_hp = (U64 *)Vec_len(parts); _t1106 = *_hp; free(_hp); }
            (void)_t1106;
            Range *_t1107 = Range_new(_t1105, _t1106);
            (void)_t1107;
            ;
            ;
            U64 _t1108; { U64 *_hp = (U64 *)Range_len(_t1107); _t1108 = *_hp; free(_hp); }
            (void)_t1108;
            Range_delete(_t1107, &(Bool){1});
            Bool _wcond1104; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1103}, &(U64){_t1108}); _wcond1104 = *_hp; free(_hp); }
            (void)_wcond1104;
            ;
            if (_wcond1104) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1109 = 0;
            (void)_t1109;
            U64 _t1110; { U64 *_hp = (U64 *)Vec_len(parts); _t1110 = *_hp; free(_hp); }
            (void)_t1110;
            Range *_t1111 = Range_new(_t1109, _t1110);
            (void)_t1111;
            ;
            ;
            U64 *i = Range_get(_t1111, _fi1103);
            (void)i;
            Range_delete(_t1111, &(Bool){1});
            U64 _t1112 = 1;
            (void)_t1112;
            U64 _t1113 = U64_add(_fi1103, _t1112);
            (void)_t1113;
            ;
            _fi1103 = _t1113;
            ;
            U64 _t1114 = 0;
            (void)_t1114;
            Bool _t1115; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1114}); _t1115 = *_hp; free(_hp); }
            (void)_t1115;
            ;
            if (_t1115) {
                result = Str_concat(result, sep);
            }
            ;
            Str *p = Vec_get(parts, i);
            (void)p;
            result = Str_concat(result, p);
            U64_delete(i, &(Bool){1});
        }
        ;
    }
    return result;
}

Tuple * Tuple_new(void) {
    U64 _t1119 = 8;
    (void)_t1119;
    Str *_t1120 = Str_lit("Str", 3ULL);
    (void)_t1120;
    U64 _t1121; { U64 *_hp = (U64 *)Str_size(); _t1121 = *_hp; free(_hp); }
    (void)_t1121;
    Str *_t1122 = Str_lit("U64", 3ULL);
    (void)_t1122;
    U64 _t1123; { U64 *_hp = (U64 *)U64_size(); _t1123 = *_hp; free(_hp); }
    (void)_t1123;
    void *_t1124 = malloc(_t1119);
    (void)_t1124;
    ;
    U64 _t1125 = 0;
    (void)_t1125;
    I64 _t1126 = 8;
    (void)_t1126;
    Tuple *_t1127 = malloc(sizeof(Tuple));
    _t1127->data = _t1124;
    _t1127->total_size = _t1125;
    _t1127->cap = _t1126;
    { Vec *_ca = Vec_new(_t1120, &(U64){_t1121}); _t1127->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1122, &(U64){_t1123}); _t1127->type_sizes = *_ca; free(_ca); }
    (void)_t1127;
    Str_delete(_t1120, &(Bool){1});
    ;
    Str_delete(_t1122, &(Bool){1});
    ;
    ;
    ;
    return _t1127;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1128; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1128 = *_hp; free(_hp); }
    (void)_t1128;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1128; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1135; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1135 = *_hp; free(_hp); }
    (void)_t1135;
    if (_t1135) {
        U64 _t1132 = 2;
        (void)_t1132;
        U64 new_cap = U64_mul(self->cap, _t1132);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1129; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1129 = *_hp; free(_hp); }
            (void)_wcond1129;
            if (_wcond1129) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1130 = 2;
            (void)_t1130;
            U64 _t1131 = U64_mul(new_cap, _t1130);
            (void)_t1131;
            ;
            new_cap = _t1131;
            ;
        }
        void *_t1133 = realloc(self->data, new_cap);
        (void)_t1133;
        self->data = _t1133;
        U64 _t1134 = U64_clone(&(U64){new_cap});
        (void)_t1134;
        ;
        self->cap = _t1134;
        ;
    }
    ;
    void *_t1136 = ptr_add(self->data, self->total_size);
    (void)_t1136;
    memcpy(_t1136, val, DEREF(elem_size));
    free(val);
    Str *_t1137 = Str_clone(elem_type);
    (void)_t1137;
    Vec_push(&self->type_names, _t1137);
    U64 _t1138 = U64_clone(elem_size);
    (void)_t1138;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1138; _oa; }));
    U64 _t1139 = U64_clone(&(U64){new_total});
    (void)_t1139;
    ;
    self->total_size = _t1139;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1165; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1165 = *_hp; free(_hp); }
    (void)_t1165;
    Bool _t1166; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1165}); _t1166 = *_hp; free(_hp); }
    (void)_t1166;
    ;
    if (_t1166) {
        Str *_t1140 = Str_lit("Str", 3ULL);
        (void)_t1140;
        U64 _t1141; { U64 *_hp = (U64 *)Str_size(); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        U64 _t1142 = 5;
        (void)_t1142;
        Array *_va19 = Array_new(_t1140, &(U64){_t1141}, &(U64){_t1142});
        (void)_va19;
        Str_delete(_t1140, &(Bool){1});
        ;
        ;
        U64 _t1143 = 0;
        (void)_t1143;
        Str *_t1144 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1144;
        Array_set(_va19, &(U64){_t1143}, _t1144);
        ;
        U64 _t1145 = 1;
        (void)_t1145;
        Str *_t1146 = U64_to_str(DEREF(i));
        (void)_t1146;
        Array_set(_va19, &(U64){_t1145}, _t1146);
        ;
        U64 _t1147 = 2;
        (void)_t1147;
        Str *_t1148 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1148;
        Array_set(_va19, &(U64){_t1147}, _t1148);
        ;
        U64 _t1149; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        U64 _t1150 = 3;
        (void)_t1150;
        Str *_t1151 = U64_to_str(_t1149);
        (void)_t1151;
        ;
        Array_set(_va19, &(U64){_t1150}, _t1151);
        ;
        U64 _t1152 = 4;
        (void)_t1152;
        Str *_t1153 = Str_lit(")", 1ULL);
        (void)_t1153;
        Array_set(_va19, &(U64){_t1152}, _t1153);
        ;
        Str *_t1154 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1154;
        panic(_t1154, _va19);
        Str_delete(_t1154, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1155 = 0;
        (void)_fi1155;
        while (1) {
            U64 _t1157 = 0;
            (void)_t1157;
            Range *_t1158 = Range_new(_t1157, DEREF(i));
            (void)_t1158;
            ;
            U64 _t1159; { U64 *_hp = (U64 *)Range_len(_t1158); _t1159 = *_hp; free(_hp); }
            (void)_t1159;
            Range_delete(_t1158, &(Bool){1});
            Bool _wcond1156; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1155}, &(U64){_t1159}); _wcond1156 = *_hp; free(_hp); }
            (void)_wcond1156;
            ;
            if (_wcond1156) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1160 = 0;
            (void)_t1160;
            Range *_t1161 = Range_new(_t1160, DEREF(i));
            (void)_t1161;
            ;
            U64 *j = Range_get(_t1161, _fi1155);
            (void)j;
            Range_delete(_t1161, &(Bool){1});
            U64 _t1162 = 1;
            (void)_t1162;
            U64 _t1163 = U64_add(_fi1155, _t1162);
            (void)_t1163;
            ;
            _fi1155 = _t1163;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1164 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1164;
            U64_delete(j, &(Bool){1});
            *offset = _t1164;
            ;
        }
        ;
    }
    void *_t1167 = ptr_add(self->data, DEREF(offset));
    (void)_t1167;
    U64_delete(offset, &(Bool){1});
    return _t1167;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1168 = Vec_get(&self->type_names, i);
    (void)_t1168;
    return _t1168;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1169 = Vec_get(&self->type_sizes, i);
    (void)_t1169;
    return _t1169;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1170 = 0;
        (void)_fi1170;
        while (1) {
            U64 _t1172 = 0;
            (void)_t1172;
            U64 _t1173; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1173 = *_hp; free(_hp); }
            (void)_t1173;
            Range *_t1174 = Range_new(_t1172, _t1173);
            (void)_t1174;
            ;
            ;
            U64 _t1175; { U64 *_hp = (U64 *)Range_len(_t1174); _t1175 = *_hp; free(_hp); }
            (void)_t1175;
            Range_delete(_t1174, &(Bool){1});
            Bool _wcond1171; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1170}, &(U64){_t1175}); _wcond1171 = *_hp; free(_hp); }
            (void)_wcond1171;
            ;
            if (_wcond1171) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1176 = 0;
            (void)_t1176;
            U64 _t1177; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1177 = *_hp; free(_hp); }
            (void)_t1177;
            Range *_t1178 = Range_new(_t1176, _t1177);
            (void)_t1178;
            ;
            ;
            U64 *i = Range_get(_t1178, _fi1170);
            (void)i;
            Range_delete(_t1178, &(Bool){1});
            U64 _t1179 = 1;
            (void)_t1179;
            U64 _t1180 = U64_add(_fi1170, _t1179);
            (void)_t1180;
            ;
            _fi1170 = _t1180;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1181 = ptr_add(self->data, DEREF(offset));
            (void)_t1181;
            Bool _t1182 = 0;
            (void)_t1182;
            dyn_call_delete(tn, _t1181, &(Bool){_t1182});
            ;
            U64 _t1183 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1183;
            U64_delete(i, &(Bool){1});
            *offset = _t1183;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1184 = 0;
    (void)_t1184;
    Vec_delete(&self->type_names, &(Bool){_t1184});
    ;
    Bool _t1185 = 0;
    (void)_t1185;
    Vec_delete(&self->type_sizes, &(Bool){_t1185});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1202 = 0;
    (void)_t1202;
    Bool _t1203 = U64_eq(new_cap, _t1202);
    (void)_t1203;
    ;
    if (_t1203) {
        I64 _t1186 = 8;
        (void)_t1186;
        U64 _t1187; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1186}); _t1187 = *_hp; free(_hp); }
        (void)_t1187;
        ;
        new_cap = _t1187;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1188 = 0;
        (void)_fi1188;
        while (1) {
            U64 _t1190 = 0;
            (void)_t1190;
            U64 _t1191; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1191 = *_hp; free(_hp); }
            (void)_t1191;
            Range *_t1192 = Range_new(_t1190, _t1191);
            (void)_t1192;
            ;
            ;
            U64 _t1193; { U64 *_hp = (U64 *)Range_len(_t1192); _t1193 = *_hp; free(_hp); }
            (void)_t1193;
            Range_delete(_t1192, &(Bool){1});
            Bool _wcond1189; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1188}, &(U64){_t1193}); _wcond1189 = *_hp; free(_hp); }
            (void)_wcond1189;
            ;
            if (_wcond1189) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1194 = 0;
            (void)_t1194;
            U64 _t1195; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1195 = *_hp; free(_hp); }
            (void)_t1195;
            Range *_t1196 = Range_new(_t1194, _t1195);
            (void)_t1196;
            ;
            ;
            U64 *i = Range_get(_t1196, _fi1188);
            (void)i;
            Range_delete(_t1196, &(Bool){1});
            U64 _t1197 = 1;
            (void)_t1197;
            U64 _t1198 = U64_add(_fi1188, _t1197);
            (void)_t1198;
            ;
            _fi1188 = _t1198;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1199 = ptr_add(self->data, DEREF(offset));
            (void)_t1199;
            void *cloned = dyn_call_clone(tn, _t1199);
            (void)cloned;
            void *_t1200 = ptr_add(new_data, DEREF(offset));
            (void)_t1200;
            memcpy(_t1200, cloned, DEREF(ts));
            free(cloned);
            U64 _t1201 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1201;
            U64_delete(i, &(Bool){1});
            *offset = _t1201;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1204 = U64_clone(&(U64){new_cap});
    (void)_t1204;
    ;
    Vec *_t1205 = Vec_clone(&self->type_names);
    (void)_t1205;
    Vec *_t1206 = Vec_clone(&self->type_sizes);
    (void)_t1206;
    Tuple *_t1207 = malloc(sizeof(Tuple));
    _t1207->data = new_data;
    _t1207->total_size = self->total_size;
    _t1207->cap = _t1204;
    { Vec *_ca = Vec_clone(_t1205); _t1207->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1206); _t1207->type_sizes = *_ca; free(_ca); }
    (void)_t1207;
    ;
    Vec_delete(_t1205, &(Bool){1});
    Vec_delete(_t1206, &(Bool){1});
    return _t1207;
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
    Bool _t1275; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1275 = *_hp; free(_hp); }
    (void)_t1275;
    if (_t1275) {
        Bool _t1209; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1209 = *_hp; free(_hp); }
        (void)_t1209;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1209; return _r; }
    }
    ;
    Bool _t1276; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1276 = *_hp; free(_hp); }
    (void)_t1276;
    if (_t1276) {
        Bool _t1210; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1210 = *_hp; free(_hp); }
        (void)_t1210;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1210; return _r; }
    }
    ;
    Bool _t1277; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1277 = *_hp; free(_hp); }
    (void)_t1277;
    if (_t1277) {
        Bool _t1211; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1211 = *_hp; free(_hp); }
        (void)_t1211;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1211; return _r; }
    }
    ;
    Bool _t1278; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1278 = *_hp; free(_hp); }
    (void)_t1278;
    if (_t1278) {
        Bool _t1212; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1212 = *_hp; free(_hp); }
        (void)_t1212;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1212; return _r; }
    }
    ;
    Bool _t1279; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1279 = *_hp; free(_hp); }
    (void)_t1279;
    if (_t1279) {
        Bool _t1213; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1213 = *_hp; free(_hp); }
        (void)_t1213;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1213; return _r; }
    }
    ;
    Bool _t1280; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        Bool _t1214; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1214 = *_hp; free(_hp); }
        (void)_t1214;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1214; return _r; }
    }
    ;
    Bool _t1281; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1281 = *_hp; free(_hp); }
    (void)_t1281;
    if (_t1281) {
        Bool _t1215; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1215 = *_hp; free(_hp); }
        (void)_t1215;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1215; return _r; }
    }
    ;
    Bool _t1282; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        Bool _t1216; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1216 = *_hp; free(_hp); }
        (void)_t1216;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1216; return _r; }
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        Bool _t1217; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1217 = *_hp; free(_hp); }
        (void)_t1217;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1217; return _r; }
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        Bool _t1218; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1218 = *_hp; free(_hp); }
        (void)_t1218;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1218; return _r; }
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        Bool _t1219; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1219 = *_hp; free(_hp); }
        (void)_t1219;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1219; return _r; }
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        Bool _t1220; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1220 = *_hp; free(_hp); }
        (void)_t1220;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1220; return _r; }
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        Bool _t1221; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1221 = *_hp; free(_hp); }
        (void)_t1221;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1221; return _r; }
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        Bool _t1222; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1222 = *_hp; free(_hp); }
        (void)_t1222;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1222; return _r; }
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        Bool _t1223; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1223 = *_hp; free(_hp); }
        (void)_t1223;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1223; return _r; }
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        Bool _t1224; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1224 = *_hp; free(_hp); }
        (void)_t1224;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1224; return _r; }
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        Bool _t1225; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1225 = *_hp; free(_hp); }
        (void)_t1225;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1225; return _r; }
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        Bool _t1226; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t1226 = *_hp; free(_hp); }
        (void)_t1226;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1226; return _r; }
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        Bool _t1227; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1227 = *_hp; free(_hp); }
        (void)_t1227;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1227; return _r; }
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        Bool _t1228; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1228 = *_hp; free(_hp); }
        (void)_t1228;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1228; return _r; }
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        Bool _t1229; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1229 = *_hp; free(_hp); }
        (void)_t1229;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1229; return _r; }
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        Bool _t1230; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1230 = *_hp; free(_hp); }
        (void)_t1230;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1230; return _r; }
    }
    ;
    Bool _t1297; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1297 = *_hp; free(_hp); }
    (void)_t1297;
    if (_t1297) {
        Bool _t1231; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1231 = *_hp; free(_hp); }
        (void)_t1231;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1231; return _r; }
    }
    ;
    Bool _t1298; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1298 = *_hp; free(_hp); }
    (void)_t1298;
    if (_t1298) {
        Bool _t1232; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1232 = *_hp; free(_hp); }
        (void)_t1232;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1232; return _r; }
    }
    ;
    Bool _t1299; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1299 = *_hp; free(_hp); }
    (void)_t1299;
    if (_t1299) {
        Bool _t1233; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1233 = *_hp; free(_hp); }
        (void)_t1233;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1233; return _r; }
    }
    ;
    Bool _t1300; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1300 = *_hp; free(_hp); }
    (void)_t1300;
    if (_t1300) {
        Bool _t1234; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1234 = *_hp; free(_hp); }
        (void)_t1234;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1234; return _r; }
    }
    ;
    Bool _t1301; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1301 = *_hp; free(_hp); }
    (void)_t1301;
    if (_t1301) {
        Bool _t1235; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1235 = *_hp; free(_hp); }
        (void)_t1235;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1235; return _r; }
    }
    ;
    Bool _t1302; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1302 = *_hp; free(_hp); }
    (void)_t1302;
    if (_t1302) {
        Bool _t1236; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1236 = *_hp; free(_hp); }
        (void)_t1236;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1236; return _r; }
    }
    ;
    Bool _t1303; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1303 = *_hp; free(_hp); }
    (void)_t1303;
    if (_t1303) {
        Bool _t1237; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1237 = *_hp; free(_hp); }
        (void)_t1237;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1237; return _r; }
    }
    ;
    Bool _t1304; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1304 = *_hp; free(_hp); }
    (void)_t1304;
    if (_t1304) {
        Bool _t1238; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1238 = *_hp; free(_hp); }
        (void)_t1238;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1238; return _r; }
    }
    ;
    Bool _t1305; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1305 = *_hp; free(_hp); }
    (void)_t1305;
    if (_t1305) {
        Bool _t1239; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1239 = *_hp; free(_hp); }
        (void)_t1239;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1239; return _r; }
    }
    ;
    Bool _t1306; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1306 = *_hp; free(_hp); }
    (void)_t1306;
    if (_t1306) {
        Bool _t1240; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1240 = *_hp; free(_hp); }
        (void)_t1240;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1240; return _r; }
    }
    ;
    Bool _t1307; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1307 = *_hp; free(_hp); }
    (void)_t1307;
    if (_t1307) {
        Bool _t1241; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1241 = *_hp; free(_hp); }
        (void)_t1241;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1241; return _r; }
    }
    ;
    Bool _t1308; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1308 = *_hp; free(_hp); }
    (void)_t1308;
    if (_t1308) {
        Bool _t1242; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1242 = *_hp; free(_hp); }
        (void)_t1242;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1242; return _r; }
    }
    ;
    Bool _t1309; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1309 = *_hp; free(_hp); }
    (void)_t1309;
    if (_t1309) {
        Bool _t1243; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1243 = *_hp; free(_hp); }
        (void)_t1243;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1243; return _r; }
    }
    ;
    Bool _t1310; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1310 = *_hp; free(_hp); }
    (void)_t1310;
    if (_t1310) {
        Bool _t1244; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1244 = *_hp; free(_hp); }
        (void)_t1244;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1244; return _r; }
    }
    ;
    Bool _t1311; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1311 = *_hp; free(_hp); }
    (void)_t1311;
    if (_t1311) {
        Bool _t1245; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1245 = *_hp; free(_hp); }
        (void)_t1245;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1245; return _r; }
    }
    ;
    Bool _t1312; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1312 = *_hp; free(_hp); }
    (void)_t1312;
    if (_t1312) {
        Bool _t1246; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1246 = *_hp; free(_hp); }
        (void)_t1246;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1246; return _r; }
    }
    ;
    Bool _t1313; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1313 = *_hp; free(_hp); }
    (void)_t1313;
    if (_t1313) {
        Bool _t1247; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1247 = *_hp; free(_hp); }
        (void)_t1247;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1247; return _r; }
    }
    ;
    Bool _t1314; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1314 = *_hp; free(_hp); }
    (void)_t1314;
    if (_t1314) {
        Bool _t1248; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1248 = *_hp; free(_hp); }
        (void)_t1248;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1248; return _r; }
    }
    ;
    Bool _t1315; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1315 = *_hp; free(_hp); }
    (void)_t1315;
    if (_t1315) {
        Bool _t1249; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1249 = *_hp; free(_hp); }
        (void)_t1249;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1249; return _r; }
    }
    ;
    Bool _t1316; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1316 = *_hp; free(_hp); }
    (void)_t1316;
    if (_t1316) {
        Bool _t1250; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1250 = *_hp; free(_hp); }
        (void)_t1250;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1250; return _r; }
    }
    ;
    Bool _t1317; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1317 = *_hp; free(_hp); }
    (void)_t1317;
    if (_t1317) {
        Bool _t1251; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1251 = *_hp; free(_hp); }
        (void)_t1251;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1251; return _r; }
    }
    ;
    Bool _t1318; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1318 = *_hp; free(_hp); }
    (void)_t1318;
    if (_t1318) {
        Bool _t1252; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1252 = *_hp; free(_hp); }
        (void)_t1252;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1252; return _r; }
    }
    ;
    Bool _t1319; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1319 = *_hp; free(_hp); }
    (void)_t1319;
    if (_t1319) {
        Bool _t1253; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1253 = *_hp; free(_hp); }
        (void)_t1253;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1253; return _r; }
    }
    ;
    Bool _t1320; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1320 = *_hp; free(_hp); }
    (void)_t1320;
    if (_t1320) {
        Bool _t1254; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1254 = *_hp; free(_hp); }
        (void)_t1254;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1254; return _r; }
    }
    ;
    Bool _t1321; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1321 = *_hp; free(_hp); }
    (void)_t1321;
    if (_t1321) {
        Bool _t1255; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1255 = *_hp; free(_hp); }
        (void)_t1255;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1255; return _r; }
    }
    ;
    Bool _t1322; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1322 = *_hp; free(_hp); }
    (void)_t1322;
    if (_t1322) {
        Bool _t1256; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1256 = *_hp; free(_hp); }
        (void)_t1256;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1256; return _r; }
    }
    ;
    Bool _t1323; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1323 = *_hp; free(_hp); }
    (void)_t1323;
    if (_t1323) {
        Bool _t1257; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1257 = *_hp; free(_hp); }
        (void)_t1257;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1257; return _r; }
    }
    ;
    Bool _t1324; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1324 = *_hp; free(_hp); }
    (void)_t1324;
    if (_t1324) {
        Bool _t1258; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1258 = *_hp; free(_hp); }
        (void)_t1258;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1258; return _r; }
    }
    ;
    Bool _t1325; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1325 = *_hp; free(_hp); }
    (void)_t1325;
    if (_t1325) {
        Bool _t1259; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1259 = *_hp; free(_hp); }
        (void)_t1259;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1259; return _r; }
    }
    ;
    Bool _t1326; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1326 = *_hp; free(_hp); }
    (void)_t1326;
    if (_t1326) {
        Bool _t1260; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1260 = *_hp; free(_hp); }
        (void)_t1260;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1260; return _r; }
    }
    ;
    Bool _t1327; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1327 = *_hp; free(_hp); }
    (void)_t1327;
    if (_t1327) {
        Bool _t1261; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1261 = *_hp; free(_hp); }
        (void)_t1261;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1261; return _r; }
    }
    ;
    Bool _t1328; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1328 = *_hp; free(_hp); }
    (void)_t1328;
    if (_t1328) {
        Bool _t1262; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1262 = *_hp; free(_hp); }
        (void)_t1262;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1262; return _r; }
    }
    ;
    Bool _t1329; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1329 = *_hp; free(_hp); }
    (void)_t1329;
    if (_t1329) {
        Bool _t1263; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1263 = *_hp; free(_hp); }
        (void)_t1263;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1263; return _r; }
    }
    ;
    Bool _t1330; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1330 = *_hp; free(_hp); }
    (void)_t1330;
    if (_t1330) {
        Bool _t1264; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1264 = *_hp; free(_hp); }
        (void)_t1264;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1264; return _r; }
    }
    ;
    Bool _t1331; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Bool _t1265; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1265 = *_hp; free(_hp); }
        (void)_t1265;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1265; return _r; }
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1266; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1266 = *_hp; free(_hp); }
        (void)_t1266;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1266; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1267; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1267 = *_hp; free(_hp); }
        (void)_t1267;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1267; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1268; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1268 = *_hp; free(_hp); }
        (void)_t1268;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1268; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1269; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1269 = *_hp; free(_hp); }
        (void)_t1269;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1269; return _r; }
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Bool _t1270; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1270 = *_hp; free(_hp); }
        (void)_t1270;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1270; return _r; }
    }
    ;
    Bool _t1337; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1337 = *_hp; free(_hp); }
    (void)_t1337;
    if (_t1337) {
        Bool _t1271; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1271 = *_hp; free(_hp); }
        (void)_t1271;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1271; return _r; }
    }
    ;
    Bool _t1338; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        Bool _t1272; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1272 = *_hp; free(_hp); }
        (void)_t1272;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1272; return _r; }
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        Bool _t1273; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1273 = *_hp; free(_hp); }
        (void)_t1273;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1273; return _r; }
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        Bool _t1274; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1274 = *_hp; free(_hp); }
        (void)_t1274;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1274; return _r; }
    }
    ;
    Bool _t1341 = 0;
    (void)_t1341;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1341; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1342; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1342 = *_hp; free(_hp); }
    (void)_t1342;
    if (_t1342) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1343; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1343 = *_hp; free(_hp); }
    (void)_t1343;
    if (_t1343) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1344; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1344 = *_hp; free(_hp); }
    (void)_t1344;
    if (_t1344) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1345; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1345 = *_hp; free(_hp); }
    (void)_t1345;
    if (_t1345) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1346; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1346 = *_hp; free(_hp); }
    (void)_t1346;
    if (_t1346) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1347; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1347 = *_hp; free(_hp); }
    (void)_t1347;
    if (_t1347) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1348; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1348 = *_hp; free(_hp); }
    (void)_t1348;
    if (_t1348) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1349; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1354; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1354 = *_hp; free(_hp); }
    (void)_t1354;
    if (_t1354) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1355; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1355 = *_hp; free(_hp); }
    (void)_t1355;
    if (_t1355) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1356; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1356 = *_hp; free(_hp); }
    (void)_t1356;
    if (_t1356) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1357; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1357 = *_hp; free(_hp); }
    (void)_t1357;
    if (_t1357) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1358; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1358 = *_hp; free(_hp); }
    (void)_t1358;
    if (_t1358) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1359; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1359 = *_hp; free(_hp); }
    (void)_t1359;
    if (_t1359) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t1360; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1360 = *_hp; free(_hp); }
    (void)_t1360;
    if (_t1360) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1361; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1361 = *_hp; free(_hp); }
    (void)_t1361;
    if (_t1361) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1362; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    if (_t1362) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1363; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1363 = *_hp; free(_hp); }
    (void)_t1363;
    if (_t1363) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1364; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1364 = *_hp; free(_hp); }
    (void)_t1364;
    if (_t1364) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1365; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1365 = *_hp; free(_hp); }
    (void)_t1365;
    if (_t1365) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1366; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    if (_t1366) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1367; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    if (_t1367) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1368; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1370; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    if (_t1370) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1371; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1371 = *_hp; free(_hp); }
    (void)_t1371;
    if (_t1371) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
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
    Bool _t1473; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1473 = *_hp; free(_hp); }
    (void)_t1473;
    if (_t1473) {
        Str *_t1407 = Str_lit("Eof", 3ULL);
        (void)_t1407;
        ;
        return _t1407;
    }
    ;
    Bool _t1474; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1474 = *_hp; free(_hp); }
    (void)_t1474;
    if (_t1474) {
        Str *_t1408 = Str_lit("LParen", 6ULL);
        (void)_t1408;
        ;
        return _t1408;
    }
    ;
    Bool _t1475; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1475 = *_hp; free(_hp); }
    (void)_t1475;
    if (_t1475) {
        Str *_t1409 = Str_lit("RParen", 6ULL);
        (void)_t1409;
        ;
        return _t1409;
    }
    ;
    Bool _t1476; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1476 = *_hp; free(_hp); }
    (void)_t1476;
    if (_t1476) {
        Str *_t1410 = Str_lit("LBrace", 6ULL);
        (void)_t1410;
        ;
        return _t1410;
    }
    ;
    Bool _t1477; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1477 = *_hp; free(_hp); }
    (void)_t1477;
    if (_t1477) {
        Str *_t1411 = Str_lit("RBrace", 6ULL);
        (void)_t1411;
        ;
        return _t1411;
    }
    ;
    Bool _t1478; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1478 = *_hp; free(_hp); }
    (void)_t1478;
    if (_t1478) {
        Str *_t1412 = Str_lit("LBracket", 8ULL);
        (void)_t1412;
        ;
        return _t1412;
    }
    ;
    Bool _t1479; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1479 = *_hp; free(_hp); }
    (void)_t1479;
    if (_t1479) {
        Str *_t1413 = Str_lit("RBracket", 8ULL);
        (void)_t1413;
        ;
        return _t1413;
    }
    ;
    Bool _t1480; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1480 = *_hp; free(_hp); }
    (void)_t1480;
    if (_t1480) {
        Str *_t1414 = Str_lit("Comma", 5ULL);
        (void)_t1414;
        ;
        return _t1414;
    }
    ;
    Bool _t1481; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1481 = *_hp; free(_hp); }
    (void)_t1481;
    if (_t1481) {
        Str *_t1415 = Str_lit("Colon", 5ULL);
        (void)_t1415;
        ;
        return _t1415;
    }
    ;
    Bool _t1482; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1482 = *_hp; free(_hp); }
    (void)_t1482;
    if (_t1482) {
        Str *_t1416 = Str_lit("Question", 8ULL);
        (void)_t1416;
        ;
        return _t1416;
    }
    ;
    Bool _t1483; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1483 = *_hp; free(_hp); }
    (void)_t1483;
    if (_t1483) {
        Str *_t1417 = Str_lit("Bang", 4ULL);
        (void)_t1417;
        ;
        return _t1417;
    }
    ;
    Bool _t1484; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1484 = *_hp; free(_hp); }
    (void)_t1484;
    if (_t1484) {
        Str *_t1418 = Str_lit("Minus", 5ULL);
        (void)_t1418;
        ;
        return _t1418;
    }
    ;
    Bool _t1485; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1485 = *_hp; free(_hp); }
    (void)_t1485;
    if (_t1485) {
        Str *_t1419 = Str_lit("Plus", 4ULL);
        (void)_t1419;
        ;
        return _t1419;
    }
    ;
    Bool _t1486; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1486 = *_hp; free(_hp); }
    (void)_t1486;
    if (_t1486) {
        Str *_t1420 = Str_lit("Star", 4ULL);
        (void)_t1420;
        ;
        return _t1420;
    }
    ;
    Bool _t1487; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1487 = *_hp; free(_hp); }
    (void)_t1487;
    if (_t1487) {
        Str *_t1421 = Str_lit("Slash", 5ULL);
        (void)_t1421;
        ;
        return _t1421;
    }
    ;
    Bool _t1488; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1488 = *_hp; free(_hp); }
    (void)_t1488;
    if (_t1488) {
        Str *_t1422 = Str_lit("Dot", 3ULL);
        (void)_t1422;
        ;
        return _t1422;
    }
    ;
    Bool _t1489; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1489 = *_hp; free(_hp); }
    (void)_t1489;
    if (_t1489) {
        Str *_t1423 = Str_lit("DotDot", 6ULL);
        (void)_t1423;
        ;
        return _t1423;
    }
    ;
    Bool _t1490; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1490 = *_hp; free(_hp); }
    (void)_t1490;
    if (_t1490) {
        Str *_t1424 = Str_lit("DotDotDot", 9ULL);
        (void)_t1424;
        ;
        return _t1424;
    }
    ;
    Bool _t1491; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1491 = *_hp; free(_hp); }
    (void)_t1491;
    if (_t1491) {
        Str *_t1425 = Str_lit("Eq", 2ULL);
        (void)_t1425;
        ;
        return _t1425;
    }
    ;
    Bool _t1492; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1492 = *_hp; free(_hp); }
    (void)_t1492;
    if (_t1492) {
        Str *_t1426 = Str_lit("EqEq", 4ULL);
        (void)_t1426;
        ;
        return _t1426;
    }
    ;
    Bool _t1493; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1493 = *_hp; free(_hp); }
    (void)_t1493;
    if (_t1493) {
        Str *_t1427 = Str_lit("Neq", 3ULL);
        (void)_t1427;
        ;
        return _t1427;
    }
    ;
    Bool _t1494; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1494 = *_hp; free(_hp); }
    (void)_t1494;
    if (_t1494) {
        Str *_t1428 = Str_lit("Lt", 2ULL);
        (void)_t1428;
        ;
        return _t1428;
    }
    ;
    Bool _t1495; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1495 = *_hp; free(_hp); }
    (void)_t1495;
    if (_t1495) {
        Str *_t1429 = Str_lit("LtEq", 4ULL);
        (void)_t1429;
        ;
        return _t1429;
    }
    ;
    Bool _t1496; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1496 = *_hp; free(_hp); }
    (void)_t1496;
    if (_t1496) {
        Str *_t1430 = Str_lit("Gt", 2ULL);
        (void)_t1430;
        ;
        return _t1430;
    }
    ;
    Bool _t1497; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1497 = *_hp; free(_hp); }
    (void)_t1497;
    if (_t1497) {
        Str *_t1431 = Str_lit("GtEq", 4ULL);
        (void)_t1431;
        ;
        return _t1431;
    }
    ;
    Bool _t1498; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1498 = *_hp; free(_hp); }
    (void)_t1498;
    if (_t1498) {
        Str *_t1432 = Str_lit("ColonEq", 7ULL);
        (void)_t1432;
        ;
        return _t1432;
    }
    ;
    Bool _t1499; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1499 = *_hp; free(_hp); }
    (void)_t1499;
    if (_t1499) {
        Str *_t1433 = Str_lit("Ident", 5ULL);
        (void)_t1433;
        ;
        return _t1433;
    }
    ;
    Bool _t1500; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1500 = *_hp; free(_hp); }
    (void)_t1500;
    if (_t1500) {
        Str *_t1434 = Str_lit("StringTok", 9ULL);
        (void)_t1434;
        ;
        return _t1434;
    }
    ;
    Bool _t1501; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1501 = *_hp; free(_hp); }
    (void)_t1501;
    if (_t1501) {
        Str *_t1435 = Str_lit("Number", 6ULL);
        (void)_t1435;
        ;
        return _t1435;
    }
    ;
    Bool _t1502; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1502 = *_hp; free(_hp); }
    (void)_t1502;
    if (_t1502) {
        Str *_t1436 = Str_lit("Char", 4ULL);
        (void)_t1436;
        ;
        return _t1436;
    }
    ;
    Bool _t1503; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1503 = *_hp; free(_hp); }
    (void)_t1503;
    if (_t1503) {
        Str *_t1437 = Str_lit("KwMode", 6ULL);
        (void)_t1437;
        ;
        return _t1437;
    }
    ;
    Bool _t1504; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1504 = *_hp; free(_hp); }
    (void)_t1504;
    if (_t1504) {
        Str *_t1438 = Str_lit("KwMut", 5ULL);
        (void)_t1438;
        ;
        return _t1438;
    }
    ;
    Bool _t1505; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1505 = *_hp; free(_hp); }
    (void)_t1505;
    if (_t1505) {
        Str *_t1439 = Str_lit("KwOwn", 5ULL);
        (void)_t1439;
        ;
        return _t1439;
    }
    ;
    Bool _t1506; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1506 = *_hp; free(_hp); }
    (void)_t1506;
    if (_t1506) {
        Str *_t1440 = Str_lit("KwRef", 5ULL);
        (void)_t1440;
        ;
        return _t1440;
    }
    ;
    Bool _t1507; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1507 = *_hp; free(_hp); }
    (void)_t1507;
    if (_t1507) {
        Str *_t1441 = Str_lit("KwShallow", 9ULL);
        (void)_t1441;
        ;
        return _t1441;
    }
    ;
    Bool _t1508; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1508 = *_hp; free(_hp); }
    (void)_t1508;
    if (_t1508) {
        Str *_t1442 = Str_lit("KwStruct", 8ULL);
        (void)_t1442;
        ;
        return _t1442;
    }
    ;
    Bool _t1509; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1509 = *_hp; free(_hp); }
    (void)_t1509;
    if (_t1509) {
        Str *_t1443 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1443;
        ;
        return _t1443;
    }
    ;
    Bool _t1510; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1510 = *_hp; free(_hp); }
    (void)_t1510;
    if (_t1510) {
        Str *_t1444 = Str_lit("KwEnum", 6ULL);
        (void)_t1444;
        ;
        return _t1444;
    }
    ;
    Bool _t1511; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1511 = *_hp; free(_hp); }
    (void)_t1511;
    if (_t1511) {
        Str *_t1445 = Str_lit("KwNamespace", 11ULL);
        (void)_t1445;
        ;
        return _t1445;
    }
    ;
    Bool _t1512; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1512 = *_hp; free(_hp); }
    (void)_t1512;
    if (_t1512) {
        Str *_t1446 = Str_lit("KwFunc", 6ULL);
        (void)_t1446;
        ;
        return _t1446;
    }
    ;
    Bool _t1513; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1513 = *_hp; free(_hp); }
    (void)_t1513;
    if (_t1513) {
        Str *_t1447 = Str_lit("KwProc", 6ULL);
        (void)_t1447;
        ;
        return _t1447;
    }
    ;
    Bool _t1514; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1514 = *_hp; free(_hp); }
    (void)_t1514;
    if (_t1514) {
        Str *_t1448 = Str_lit("KwTest", 6ULL);
        (void)_t1448;
        ;
        return _t1448;
    }
    ;
    Bool _t1515; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1515 = *_hp; free(_hp); }
    (void)_t1515;
    if (_t1515) {
        Str *_t1449 = Str_lit("KwMacro", 7ULL);
        (void)_t1449;
        ;
        return _t1449;
    }
    ;
    Bool _t1516; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1516 = *_hp; free(_hp); }
    (void)_t1516;
    if (_t1516) {
        Str *_t1450 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1450;
        ;
        return _t1450;
    }
    ;
    Bool _t1517; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1517 = *_hp; free(_hp); }
    (void)_t1517;
    if (_t1517) {
        Str *_t1451 = Str_lit("KwExtProc", 9ULL);
        (void)_t1451;
        ;
        return _t1451;
    }
    ;
    Bool _t1518; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1518 = *_hp; free(_hp); }
    (void)_t1518;
    if (_t1518) {
        Str *_t1452 = Str_lit("KwReturns", 9ULL);
        (void)_t1452;
        ;
        return _t1452;
    }
    ;
    Bool _t1519; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1519 = *_hp; free(_hp); }
    (void)_t1519;
    if (_t1519) {
        Str *_t1453 = Str_lit("KwThrows", 8ULL);
        (void)_t1453;
        ;
        return _t1453;
    }
    ;
    Bool _t1520; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1520 = *_hp; free(_hp); }
    (void)_t1520;
    if (_t1520) {
        Str *_t1454 = Str_lit("KwIf", 4ULL);
        (void)_t1454;
        ;
        return _t1454;
    }
    ;
    Bool _t1521; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1521 = *_hp; free(_hp); }
    (void)_t1521;
    if (_t1521) {
        Str *_t1455 = Str_lit("KwElse", 6ULL);
        (void)_t1455;
        ;
        return _t1455;
    }
    ;
    Bool _t1522; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1522 = *_hp; free(_hp); }
    (void)_t1522;
    if (_t1522) {
        Str *_t1456 = Str_lit("KwWhile", 7ULL);
        (void)_t1456;
        ;
        return _t1456;
    }
    ;
    Bool _t1523; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1523 = *_hp; free(_hp); }
    (void)_t1523;
    if (_t1523) {
        Str *_t1457 = Str_lit("KwFor", 5ULL);
        (void)_t1457;
        ;
        return _t1457;
    }
    ;
    Bool _t1524; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1524 = *_hp; free(_hp); }
    (void)_t1524;
    if (_t1524) {
        Str *_t1458 = Str_lit("KwIn", 4ULL);
        (void)_t1458;
        ;
        return _t1458;
    }
    ;
    Bool _t1525; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1525 = *_hp; free(_hp); }
    (void)_t1525;
    if (_t1525) {
        Str *_t1459 = Str_lit("KwSwitch", 8ULL);
        (void)_t1459;
        ;
        return _t1459;
    }
    ;
    Bool _t1526; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1526 = *_hp; free(_hp); }
    (void)_t1526;
    if (_t1526) {
        Str *_t1460 = Str_lit("KwMatch", 7ULL);
        (void)_t1460;
        ;
        return _t1460;
    }
    ;
    Bool _t1527; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        Str *_t1461 = Str_lit("KwCase", 6ULL);
        (void)_t1461;
        ;
        return _t1461;
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        Str *_t1462 = Str_lit("KwDefault", 9ULL);
        (void)_t1462;
        ;
        return _t1462;
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Str *_t1463 = Str_lit("KwReturn", 8ULL);
        (void)_t1463;
        ;
        return _t1463;
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Str *_t1464 = Str_lit("KwThrow", 7ULL);
        (void)_t1464;
        ;
        return _t1464;
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        Str *_t1465 = Str_lit("KwCatch", 7ULL);
        (void)_t1465;
        ;
        return _t1465;
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        Str *_t1466 = Str_lit("KwBreak", 7ULL);
        (void)_t1466;
        ;
        return _t1466;
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        Str *_t1467 = Str_lit("KwContinue", 10ULL);
        (void)_t1467;
        ;
        return _t1467;
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        Str *_t1468 = Str_lit("KwDefer", 7ULL);
        (void)_t1468;
        ;
        return _t1468;
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
        Str *_t1469 = Str_lit("KwTrue", 6ULL);
        (void)_t1469;
        ;
        return _t1469;
    }
    ;
    Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1536 = *_hp; free(_hp); }
    (void)_t1536;
    if (_t1536) {
        Str *_t1470 = Str_lit("KwFalse", 7ULL);
        (void)_t1470;
        ;
        return _t1470;
    }
    ;
    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1537 = *_hp; free(_hp); }
    (void)_t1537;
    if (_t1537) {
        Str *_t1471 = Str_lit("KwNull", 6ULL);
        (void)_t1471;
        ;
        return _t1471;
    }
    ;
    Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1538 = *_hp; free(_hp); }
    (void)_t1538;
    if (_t1538) {
        Str *_t1472 = Str_lit("Error", 5ULL);
        (void)_t1472;
        ;
        return _t1472;
    }
    ;
    Str *_t1539 = Str_lit("unknown", 7ULL);
    (void)_t1539;
    return _t1539;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1541 = I64_clone(&self->line);
    (void)_t1541;
    I64 _t1542 = I64_clone(&self->col);
    (void)_t1542;
    Token *_t1543 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1543->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1543->text = *_ca; free(_ca); }
    _t1543->line = _t1541;
    _t1543->col = _t1542;
    (void)_t1543;
    ;
    ;
    return _t1543;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1544 = 0;
    (void)_t1544;
    TokenType_delete(&self->type, &(Bool){_t1544});
    ;
    Bool _t1545 = 0;
    (void)_t1545;
    Str_delete(&self->text, &(Bool){_t1545});
    ;
    Bool _t1546 = 0;
    (void)_t1546;
    I64_delete(&self->line, &(Bool){_t1546});
    ;
    Bool _t1547 = 0;
    (void)_t1547;
    I64_delete(&self->col, &(Bool){_t1547});
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
    U8 _t1549 = 48;
    (void)_t1549;
    U8 _t1550 = 57;
    (void)_t1550;
    Bool _t1551; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1549}); _t1551 = *_hp; free(_hp); }
    (void)_t1551;
    ;
    Bool _t1552; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1550}); _t1552 = *_hp; free(_hp); }
    (void)_t1552;
    ;
    Bool _t1553 = Bool_and(_t1551, _t1552);
    (void)_t1553;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1553; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1554 = 97;
    (void)_t1554;
    U8 _t1555 = 122;
    (void)_t1555;
    Bool _t1556; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1554}); _t1556 = *_hp; free(_hp); }
    (void)_t1556;
    ;
    Bool _t1557; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1555}); _t1557 = *_hp; free(_hp); }
    (void)_t1557;
    ;
    U8 _t1558 = 65;
    (void)_t1558;
    U8 _t1559 = 90;
    (void)_t1559;
    Bool _t1560; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1558}); _t1560 = *_hp; free(_hp); }
    (void)_t1560;
    ;
    Bool _t1561; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1559}); _t1561 = *_hp; free(_hp); }
    (void)_t1561;
    ;
    Bool _t1562 = Bool_and(_t1556, _t1557);
    (void)_t1562;
    ;
    ;
    Bool _t1563 = Bool_and(_t1560, _t1561);
    (void)_t1563;
    ;
    ;
    U8 _t1564 = 95;
    (void)_t1564;
    Bool _t1565 = Bool_or(_t1562, _t1563);
    (void)_t1565;
    ;
    ;
    Bool _t1566 = U8_eq(DEREF(c), _t1564);
    (void)_t1566;
    ;
    Bool _t1567 = Bool_or(_t1565, _t1566);
    (void)_t1567;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1567; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1568; { Bool *_hp = (Bool *)is_alpha(c); _t1568 = *_hp; free(_hp); }
    (void)_t1568;
    Bool _t1569; { Bool *_hp = (Bool *)is_digit(c); _t1569 = *_hp; free(_hp); }
    (void)_t1569;
    Bool _t1570 = Bool_or(_t1568, _t1569);
    (void)_t1570;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1570; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1571 = TokenType_clone(type);
        (void)_sw1571;
        Bool _t1704; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Eof()); _t1704 = *_hp; free(_hp); }
        (void)_t1704;
        if (_t1704) {
            Str *_t1572 = Str_lit("eof", 3ULL);
            (void)_t1572;
            TokenType_delete(_sw1571, &(Bool){1});
            ;
            return _t1572;
        } else {
            Bool _t1703; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_LParen()); _t1703 = *_hp; free(_hp); }
            (void)_t1703;
            if (_t1703) {
                Str *_t1573 = Str_lit("(", 1ULL);
                (void)_t1573;
                ;
                TokenType_delete(_sw1571, &(Bool){1});
                ;
                return _t1573;
            } else {
                Bool _t1702; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_RParen()); _t1702 = *_hp; free(_hp); }
                (void)_t1702;
                if (_t1702) {
                    Str *_t1574 = Str_lit(")", 1ULL);
                    (void)_t1574;
                    ;
                    ;
                    TokenType_delete(_sw1571, &(Bool){1});
                    ;
                    return _t1574;
                } else {
                    Bool _t1701; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_LBrace()); _t1701 = *_hp; free(_hp); }
                    (void)_t1701;
                    if (_t1701) {
                        Str *_t1575 = Str_lit("{", 1ULL);
                        (void)_t1575;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1571, &(Bool){1});
                        ;
                        return _t1575;
                    } else {
                        Bool _t1700; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_RBrace()); _t1700 = *_hp; free(_hp); }
                        (void)_t1700;
                        if (_t1700) {
                            Str *_t1576 = Str_lit("}", 1ULL);
                            (void)_t1576;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1571, &(Bool){1});
                            ;
                            return _t1576;
                        } else {
                            Bool _t1699; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_LBracket()); _t1699 = *_hp; free(_hp); }
                            (void)_t1699;
                            if (_t1699) {
                                Str *_t1577 = Str_lit("[", 1ULL);
                                (void)_t1577;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1571, &(Bool){1});
                                ;
                                return _t1577;
                            } else {
                                Bool _t1698; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_RBracket()); _t1698 = *_hp; free(_hp); }
                                (void)_t1698;
                                if (_t1698) {
                                    Str *_t1578 = Str_lit("]", 1ULL);
                                    (void)_t1578;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1571, &(Bool){1});
                                    ;
                                    return _t1578;
                                } else {
                                    Bool _t1697; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Comma()); _t1697 = *_hp; free(_hp); }
                                    (void)_t1697;
                                    if (_t1697) {
                                        Str *_t1579 = Str_lit(",", 1ULL);
                                        (void)_t1579;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1571, &(Bool){1});
                                        ;
                                        return _t1579;
                                    } else {
                                        Bool _t1696; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Colon()); _t1696 = *_hp; free(_hp); }
                                        (void)_t1696;
                                        if (_t1696) {
                                            Str *_t1580 = Str_lit(":", 1ULL);
                                            (void)_t1580;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1571, &(Bool){1});
                                            ;
                                            return _t1580;
                                        } else {
                                            Bool _t1695; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Question()); _t1695 = *_hp; free(_hp); }
                                            (void)_t1695;
                                            if (_t1695) {
                                                Str *_t1581 = Str_lit("?", 1ULL);
                                                (void)_t1581;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1571, &(Bool){1});
                                                ;
                                                return _t1581;
                                            } else {
                                                Bool _t1694; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Bang()); _t1694 = *_hp; free(_hp); }
                                                (void)_t1694;
                                                if (_t1694) {
                                                    Str *_t1582 = Str_lit("!", 1ULL);
                                                    (void)_t1582;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                    ;
                                                    return _t1582;
                                                } else {
                                                    Bool _t1693; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Minus()); _t1693 = *_hp; free(_hp); }
                                                    (void)_t1693;
                                                    if (_t1693) {
                                                        Str *_t1583 = Str_lit("-", 1ULL);
                                                        (void)_t1583;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                        ;
                                                        return _t1583;
                                                    } else {
                                                        Bool _t1692; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Plus()); _t1692 = *_hp; free(_hp); }
                                                        (void)_t1692;
                                                        if (_t1692) {
                                                            Str *_t1584 = Str_lit("+", 1ULL);
                                                            (void)_t1584;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                            ;
                                                            return _t1584;
                                                        } else {
                                                            Bool _t1691; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Star()); _t1691 = *_hp; free(_hp); }
                                                            (void)_t1691;
                                                            if (_t1691) {
                                                                Str *_t1585 = Str_lit("*", 1ULL);
                                                                (void)_t1585;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                ;
                                                                return _t1585;
                                                            } else {
                                                                Bool _t1690; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Slash()); _t1690 = *_hp; free(_hp); }
                                                                (void)_t1690;
                                                                if (_t1690) {
                                                                    Str *_t1586 = Str_lit("/", 1ULL);
                                                                    (void)_t1586;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                    ;
                                                                    return _t1586;
                                                                } else {
                                                                    Bool _t1689; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Dot()); _t1689 = *_hp; free(_hp); }
                                                                    (void)_t1689;
                                                                    if (_t1689) {
                                                                        Str *_t1587 = Str_lit(".", 1ULL);
                                                                        (void)_t1587;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                        ;
                                                                        return _t1587;
                                                                    } else {
                                                                        Bool _t1688; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_DotDot()); _t1688 = *_hp; free(_hp); }
                                                                        (void)_t1688;
                                                                        if (_t1688) {
                                                                            Str *_t1588 = Str_lit("..", 2ULL);
                                                                            (void)_t1588;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                            ;
                                                                            return _t1588;
                                                                        } else {
                                                                            Bool _t1687; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_DotDotDot()); _t1687 = *_hp; free(_hp); }
                                                                            (void)_t1687;
                                                                            if (_t1687) {
                                                                                Str *_t1589 = Str_lit("...", 3ULL);
                                                                                (void)_t1589;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                ;
                                                                                return _t1589;
                                                                            } else {
                                                                                Bool _t1686; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Eq()); _t1686 = *_hp; free(_hp); }
                                                                                (void)_t1686;
                                                                                if (_t1686) {
                                                                                    Str *_t1590 = Str_lit("=", 1ULL);
                                                                                    (void)_t1590;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                    ;
                                                                                    return _t1590;
                                                                                } else {
                                                                                    Bool _t1685; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_EqEq()); _t1685 = *_hp; free(_hp); }
                                                                                    (void)_t1685;
                                                                                    if (_t1685) {
                                                                                        Str *_t1591 = Str_lit("==", 2ULL);
                                                                                        (void)_t1591;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                        ;
                                                                                        return _t1591;
                                                                                    } else {
                                                                                        Bool _t1684; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Neq()); _t1684 = *_hp; free(_hp); }
                                                                                        (void)_t1684;
                                                                                        if (_t1684) {
                                                                                            Str *_t1592 = Str_lit("!=", 2ULL);
                                                                                            (void)_t1592;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                            ;
                                                                                            return _t1592;
                                                                                        } else {
                                                                                            Bool _t1683; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Lt()); _t1683 = *_hp; free(_hp); }
                                                                                            (void)_t1683;
                                                                                            if (_t1683) {
                                                                                                Str *_t1593 = Str_lit("<", 1ULL);
                                                                                                (void)_t1593;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                ;
                                                                                                return _t1593;
                                                                                            } else {
                                                                                                Bool _t1682; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_LtEq()); _t1682 = *_hp; free(_hp); }
                                                                                                (void)_t1682;
                                                                                                if (_t1682) {
                                                                                                    Str *_t1594 = Str_lit("<=", 2ULL);
                                                                                                    (void)_t1594;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1594;
                                                                                                } else {
                                                                                                    Bool _t1681; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Gt()); _t1681 = *_hp; free(_hp); }
                                                                                                    (void)_t1681;
                                                                                                    if (_t1681) {
                                                                                                        Str *_t1595 = Str_lit(">", 1ULL);
                                                                                                        (void)_t1595;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1595;
                                                                                                    } else {
                                                                                                        Bool _t1680; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_GtEq()); _t1680 = *_hp; free(_hp); }
                                                                                                        (void)_t1680;
                                                                                                        if (_t1680) {
                                                                                                            Str *_t1596 = Str_lit(">=", 2ULL);
                                                                                                            (void)_t1596;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1596;
                                                                                                        } else {
                                                                                                            Bool _t1679; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_ColonEq()); _t1679 = *_hp; free(_hp); }
                                                                                                            (void)_t1679;
                                                                                                            if (_t1679) {
                                                                                                                Str *_t1597 = Str_lit(":=", 2ULL);
                                                                                                                (void)_t1597;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1597;
                                                                                                            } else {
                                                                                                                Bool _t1678; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Ident()); _t1678 = *_hp; free(_hp); }
                                                                                                                (void)_t1678;
                                                                                                                if (_t1678) {
                                                                                                                    Str *_t1598 = Str_lit("identifier", 10ULL);
                                                                                                                    (void)_t1598;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1598;
                                                                                                                } else {
                                                                                                                    Bool _t1677; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_StringTok()); _t1677 = *_hp; free(_hp); }
                                                                                                                    (void)_t1677;
                                                                                                                    if (_t1677) {
                                                                                                                        Str *_t1599 = Str_lit("string", 6ULL);
                                                                                                                        (void)_t1599;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1599;
                                                                                                                    } else {
                                                                                                                        Bool _t1676; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Number()); _t1676 = *_hp; free(_hp); }
                                                                                                                        (void)_t1676;
                                                                                                                        if (_t1676) {
                                                                                                                            Str *_t1600 = Str_lit("number", 6ULL);
                                                                                                                            (void)_t1600;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1600;
                                                                                                                        } else {
                                                                                                                            Bool _t1675; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Char()); _t1675 = *_hp; free(_hp); }
                                                                                                                            (void)_t1675;
                                                                                                                            if (_t1675) {
                                                                                                                                Str *_t1601 = Str_lit("char", 4ULL);
                                                                                                                                (void)_t1601;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1601;
                                                                                                                            } else {
                                                                                                                                Bool _t1674; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwMode()); _t1674 = *_hp; free(_hp); }
                                                                                                                                (void)_t1674;
                                                                                                                                if (_t1674) {
                                                                                                                                    Str *_t1602 = Str_lit("mode", 4ULL);
                                                                                                                                    (void)_t1602;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1602;
                                                                                                                                } else {
                                                                                                                                    Bool _t1673; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwMut()); _t1673 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1673;
                                                                                                                                    if (_t1673) {
                                                                                                                                        Str *_t1603 = Str_lit("mut", 3ULL);
                                                                                                                                        (void)_t1603;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1603;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1672; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwOwn()); _t1672 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1672;
                                                                                                                                        if (_t1672) {
                                                                                                                                            Str *_t1604 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t1604;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1604;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1671; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwRef()); _t1671 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1671;
                                                                                                                                            if (_t1671) {
                                                                                                                                                Str *_t1605 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t1605;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1605;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1670; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwShallow()); _t1670 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1670;
                                                                                                                                                if (_t1670) {
                                                                                                                                                    Str *_t1606 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t1606;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1606;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1669; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwStruct()); _t1669 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1669;
                                                                                                                                                    if (_t1669) {
                                                                                                                                                        Str *_t1607 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t1607;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1607;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1668; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwExtStruct()); _t1668 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1668;
                                                                                                                                                        if (_t1668) {
                                                                                                                                                            Str *_t1608 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t1608;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1608;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1667; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwEnum()); _t1667 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1667;
                                                                                                                                                            if (_t1667) {
                                                                                                                                                                Str *_t1609 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t1609;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1609;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1666; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwNamespace()); _t1666 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1666;
                                                                                                                                                                if (_t1666) {
                                                                                                                                                                    Str *_t1610 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t1610;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1610;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1665; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwFunc()); _t1665 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1665;
                                                                                                                                                                    if (_t1665) {
                                                                                                                                                                        Str *_t1611 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t1611;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1611;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1664; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwProc()); _t1664 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1664;
                                                                                                                                                                        if (_t1664) {
                                                                                                                                                                            Str *_t1612 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t1612;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1612;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1663; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwTest()); _t1663 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1663;
                                                                                                                                                                            if (_t1663) {
                                                                                                                                                                                Str *_t1613 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t1613;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1613;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1662; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwMacro()); _t1662 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1662;
                                                                                                                                                                                if (_t1662) {
                                                                                                                                                                                    Str *_t1614 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t1614;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1614;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1661; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwExtFunc()); _t1661 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1661;
                                                                                                                                                                                    if (_t1661) {
                                                                                                                                                                                        Str *_t1615 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t1615;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1615;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1660; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwExtProc()); _t1660 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1660;
                                                                                                                                                                                        if (_t1660) {
                                                                                                                                                                                            Str *_t1616 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t1616;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1616;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1659; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwReturns()); _t1659 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1659;
                                                                                                                                                                                            if (_t1659) {
                                                                                                                                                                                                Str *_t1617 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t1617;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1617;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1658; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwThrows()); _t1658 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1658;
                                                                                                                                                                                                if (_t1658) {
                                                                                                                                                                                                    Str *_t1618 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t1618;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1618;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1657; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwIf()); _t1657 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1657;
                                                                                                                                                                                                    if (_t1657) {
                                                                                                                                                                                                        Str *_t1619 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t1619;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1619;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1656; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwElse()); _t1656 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1656;
                                                                                                                                                                                                        if (_t1656) {
                                                                                                                                                                                                            Str *_t1620 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t1620;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1620;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1655; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwWhile()); _t1655 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1655;
                                                                                                                                                                                                            if (_t1655) {
                                                                                                                                                                                                                Str *_t1621 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t1621;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1621;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1654; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwFor()); _t1654 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1654;
                                                                                                                                                                                                                if (_t1654) {
                                                                                                                                                                                                                    Str *_t1622 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t1622;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1622;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1653; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwIn()); _t1653 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1653;
                                                                                                                                                                                                                    if (_t1653) {
                                                                                                                                                                                                                        Str *_t1623 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t1623;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1623;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1652; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwSwitch()); _t1652 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1652;
                                                                                                                                                                                                                        if (_t1652) {
                                                                                                                                                                                                                            Str *_t1624 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t1624;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1624;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1651; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwMatch()); _t1651 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1651;
                                                                                                                                                                                                                            if (_t1651) {
                                                                                                                                                                                                                                Str *_t1625 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t1625;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1625;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1650; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwCase()); _t1650 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1650;
                                                                                                                                                                                                                                if (_t1650) {
                                                                                                                                                                                                                                    Str *_t1626 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t1626;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1626;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1649; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwDefault()); _t1649 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1649;
                                                                                                                                                                                                                                    if (_t1649) {
                                                                                                                                                                                                                                        Str *_t1627 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t1627;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1627;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1648; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwReturn()); _t1648 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1648;
                                                                                                                                                                                                                                        if (_t1648) {
                                                                                                                                                                                                                                            Str *_t1628 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t1628;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1628;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1647; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwThrow()); _t1647 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1647;
                                                                                                                                                                                                                                            if (_t1647) {
                                                                                                                                                                                                                                                Str *_t1629 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t1629;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1629;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1646; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwCatch()); _t1646 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1646;
                                                                                                                                                                                                                                                if (_t1646) {
                                                                                                                                                                                                                                                    Str *_t1630 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t1630;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1630;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1645; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwBreak()); _t1645 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1645;
                                                                                                                                                                                                                                                    if (_t1645) {
                                                                                                                                                                                                                                                        Str *_t1631 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t1631;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1631;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1644; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwContinue()); _t1644 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1644;
                                                                                                                                                                                                                                                        if (_t1644) {
                                                                                                                                                                                                                                                            Str *_t1632 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t1632;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1632;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1643; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwDefer()); _t1643 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1643;
                                                                                                                                                                                                                                                            if (_t1643) {
                                                                                                                                                                                                                                                                Str *_t1633 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t1633;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1633;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1642; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwTrue()); _t1642 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1642;
                                                                                                                                                                                                                                                                if (_t1642) {
                                                                                                                                                                                                                                                                    Str *_t1634 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t1634;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1634;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1641; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwFalse()); _t1641 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1641;
                                                                                                                                                                                                                                                                    if (_t1641) {
                                                                                                                                                                                                                                                                        Str *_t1635 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t1635;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1635;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1640; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_KwNull()); _t1640 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1640;
                                                                                                                                                                                                                                                                        if (_t1640) {
                                                                                                                                                                                                                                                                            Str *_t1636 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t1636;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1636;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t1639; { Bool *_hp = (Bool *)TokenType_eq(_sw1571, TokenType_Error()); _t1639 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t1639;
                                                                                                                                                                                                                                                                            if (_t1639) {
                                                                                                                                                                                                                                                                                Str *_t1637 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t1637;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1637;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t1638 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t1638;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1571, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1638;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1571, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1705 = Str_clone(word);
        (void)_sw1705;
        Str *_t1774 = Str_lit("mode", 4ULL);
        (void)_t1774;
        Bool _t1775; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1774); _t1775 = *_hp; free(_hp); }
        (void)_t1775;
        Str_delete(_t1774, &(Bool){1});
        if (_t1775) {
            Str_delete(_sw1705, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1772 = Str_lit("mut", 3ULL);
            (void)_t1772;
            Bool _t1773; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1772); _t1773 = *_hp; free(_hp); }
            (void)_t1773;
            Str_delete(_t1772, &(Bool){1});
            if (_t1773) {
                ;
                Str_delete(_sw1705, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1770 = Str_lit("own", 3ULL);
                (void)_t1770;
                Bool _t1771; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1770); _t1771 = *_hp; free(_hp); }
                (void)_t1771;
                Str_delete(_t1770, &(Bool){1});
                if (_t1771) {
                    ;
                    ;
                    Str_delete(_sw1705, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1768 = Str_lit("ref", 3ULL);
                    (void)_t1768;
                    Bool _t1769; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1768); _t1769 = *_hp; free(_hp); }
                    (void)_t1769;
                    Str_delete(_t1768, &(Bool){1});
                    if (_t1769) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1705, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1766 = Str_lit("shallow", 7ULL);
                        (void)_t1766;
                        Bool _t1767; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1766); _t1767 = *_hp; free(_hp); }
                        (void)_t1767;
                        Str_delete(_t1766, &(Bool){1});
                        if (_t1767) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1705, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1764 = Str_lit("struct", 6ULL);
                            (void)_t1764;
                            Bool _t1765; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1764); _t1765 = *_hp; free(_hp); }
                            (void)_t1765;
                            Str_delete(_t1764, &(Bool){1});
                            if (_t1765) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1705, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1762 = Str_lit("ext_struct", 10ULL);
                                (void)_t1762;
                                Bool _t1763; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1762); _t1763 = *_hp; free(_hp); }
                                (void)_t1763;
                                Str_delete(_t1762, &(Bool){1});
                                if (_t1763) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1705, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1760 = Str_lit("enum", 4ULL);
                                    (void)_t1760;
                                    Bool _t1761; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1760); _t1761 = *_hp; free(_hp); }
                                    (void)_t1761;
                                    Str_delete(_t1760, &(Bool){1});
                                    if (_t1761) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1705, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1758 = Str_lit("namespace", 9ULL);
                                        (void)_t1758;
                                        Bool _t1759; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1758); _t1759 = *_hp; free(_hp); }
                                        (void)_t1759;
                                        Str_delete(_t1758, &(Bool){1});
                                        if (_t1759) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1705, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1756 = Str_lit("func", 4ULL);
                                            (void)_t1756;
                                            Bool _t1757; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1756); _t1757 = *_hp; free(_hp); }
                                            (void)_t1757;
                                            Str_delete(_t1756, &(Bool){1});
                                            if (_t1757) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1705, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1754 = Str_lit("proc", 4ULL);
                                                (void)_t1754;
                                                Bool _t1755; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1754); _t1755 = *_hp; free(_hp); }
                                                (void)_t1755;
                                                Str_delete(_t1754, &(Bool){1});
                                                if (_t1755) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1705, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1752 = Str_lit("test", 4ULL);
                                                    (void)_t1752;
                                                    Bool _t1753; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1752); _t1753 = *_hp; free(_hp); }
                                                    (void)_t1753;
                                                    Str_delete(_t1752, &(Bool){1});
                                                    if (_t1753) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1705, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1750 = Str_lit("macro", 5ULL);
                                                        (void)_t1750;
                                                        Bool _t1751; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1750); _t1751 = *_hp; free(_hp); }
                                                        (void)_t1751;
                                                        Str_delete(_t1750, &(Bool){1});
                                                        if (_t1751) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1705, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1748 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1748;
                                                            Bool _t1749; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1748); _t1749 = *_hp; free(_hp); }
                                                            (void)_t1749;
                                                            Str_delete(_t1748, &(Bool){1});
                                                            if (_t1749) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1705, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1746 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1746;
                                                                Bool _t1747; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1746); _t1747 = *_hp; free(_hp); }
                                                                (void)_t1747;
                                                                Str_delete(_t1746, &(Bool){1});
                                                                if (_t1747) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1705, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1744 = Str_lit("returns", 7ULL);
                                                                    (void)_t1744;
                                                                    Bool _t1745; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1744); _t1745 = *_hp; free(_hp); }
                                                                    (void)_t1745;
                                                                    Str_delete(_t1744, &(Bool){1});
                                                                    if (_t1745) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1705, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1742 = Str_lit("throws", 6ULL);
                                                                        (void)_t1742;
                                                                        Bool _t1743; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1742); _t1743 = *_hp; free(_hp); }
                                                                        (void)_t1743;
                                                                        Str_delete(_t1742, &(Bool){1});
                                                                        if (_t1743) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1705, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1740 = Str_lit("if", 2ULL);
                                                                            (void)_t1740;
                                                                            Bool _t1741; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1740); _t1741 = *_hp; free(_hp); }
                                                                            (void)_t1741;
                                                                            Str_delete(_t1740, &(Bool){1});
                                                                            if (_t1741) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1705, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1738 = Str_lit("else", 4ULL);
                                                                                (void)_t1738;
                                                                                Bool _t1739; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1738); _t1739 = *_hp; free(_hp); }
                                                                                (void)_t1739;
                                                                                Str_delete(_t1738, &(Bool){1});
                                                                                if (_t1739) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1705, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1736 = Str_lit("while", 5ULL);
                                                                                    (void)_t1736;
                                                                                    Bool _t1737; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1736); _t1737 = *_hp; free(_hp); }
                                                                                    (void)_t1737;
                                                                                    Str_delete(_t1736, &(Bool){1});
                                                                                    if (_t1737) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1705, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1734 = Str_lit("for", 3ULL);
                                                                                        (void)_t1734;
                                                                                        Bool _t1735; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1734); _t1735 = *_hp; free(_hp); }
                                                                                        (void)_t1735;
                                                                                        Str_delete(_t1734, &(Bool){1});
                                                                                        if (_t1735) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1705, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1732 = Str_lit("in", 2ULL);
                                                                                            (void)_t1732;
                                                                                            Bool _t1733; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1732); _t1733 = *_hp; free(_hp); }
                                                                                            (void)_t1733;
                                                                                            Str_delete(_t1732, &(Bool){1});
                                                                                            if (_t1733) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1705, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1730 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1730;
                                                                                                Bool _t1731; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1730); _t1731 = *_hp; free(_hp); }
                                                                                                (void)_t1731;
                                                                                                Str_delete(_t1730, &(Bool){1});
                                                                                                if (_t1731) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1705, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1728 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1728;
                                                                                                    Bool _t1729; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1728); _t1729 = *_hp; free(_hp); }
                                                                                                    (void)_t1729;
                                                                                                    Str_delete(_t1728, &(Bool){1});
                                                                                                    if (_t1729) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1705, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1726 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1726;
                                                                                                        Bool _t1727; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1726); _t1727 = *_hp; free(_hp); }
                                                                                                        (void)_t1727;
                                                                                                        Str_delete(_t1726, &(Bool){1});
                                                                                                        if (_t1727) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1705, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1724 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1724;
                                                                                                            Bool _t1725; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1724); _t1725 = *_hp; free(_hp); }
                                                                                                            (void)_t1725;
                                                                                                            Str_delete(_t1724, &(Bool){1});
                                                                                                            if (_t1725) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1705, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1722 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1722;
                                                                                                                Bool _t1723; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1722); _t1723 = *_hp; free(_hp); }
                                                                                                                (void)_t1723;
                                                                                                                Str_delete(_t1722, &(Bool){1});
                                                                                                                if (_t1723) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1705, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1720 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1720;
                                                                                                                    Bool _t1721; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1720); _t1721 = *_hp; free(_hp); }
                                                                                                                    (void)_t1721;
                                                                                                                    Str_delete(_t1720, &(Bool){1});
                                                                                                                    if (_t1721) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1705, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1718 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1718;
                                                                                                                        Bool _t1719; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1718); _t1719 = *_hp; free(_hp); }
                                                                                                                        (void)_t1719;
                                                                                                                        Str_delete(_t1718, &(Bool){1});
                                                                                                                        if (_t1719) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1705, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1716 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1716;
                                                                                                                            Bool _t1717; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1716); _t1717 = *_hp; free(_hp); }
                                                                                                                            (void)_t1717;
                                                                                                                            Str_delete(_t1716, &(Bool){1});
                                                                                                                            if (_t1717) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1705, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1714 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1714;
                                                                                                                                Bool _t1715; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1714); _t1715 = *_hp; free(_hp); }
                                                                                                                                (void)_t1715;
                                                                                                                                Str_delete(_t1714, &(Bool){1});
                                                                                                                                if (_t1715) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1705, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1712 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1712;
                                                                                                                                    Bool _t1713; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1712); _t1713 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1713;
                                                                                                                                    Str_delete(_t1712, &(Bool){1});
                                                                                                                                    if (_t1713) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1705, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1710 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1710;
                                                                                                                                        Bool _t1711; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1710); _t1711 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1711;
                                                                                                                                        Str_delete(_t1710, &(Bool){1});
                                                                                                                                        if (_t1711) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1705, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1708 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1708;
                                                                                                                                            Bool _t1709; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1708); _t1709 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1709;
                                                                                                                                            Str_delete(_t1708, &(Bool){1});
                                                                                                                                            if (_t1709) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1705, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1706 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1706;
                                                                                                                                                Bool _t1707; { Bool *_hp = (Bool *)Str_eq(_sw1705, _t1706); _t1707 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1707;
                                                                                                                                                Str_delete(_t1706, &(Bool){1});
                                                                                                                                                if (_t1707) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1705, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1705, &(Bool){1});
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
        Str_delete(_sw1705, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2124 = Str_lit("Token", 5ULL);
    (void)_t2124;
    U64 _t2125; { U64 *_hp = (U64 *)Token_size(); _t2125 = *_hp; free(_hp); }
    (void)_t2125;
    Vec *tokens = Vec_new(_t2124, &(U64){_t2125});
    (void)tokens;
    Str_delete(_t2124, &(Bool){1});
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
        Bool _wcond1776; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1776 = *_hp; free(_hp); }
        (void)_wcond1776;
        if (_wcond1776) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2070 = 32;
        (void)_t2070;
        U8 _t2071 = 9;
        (void)_t2071;
        Bool _t2072 = U8_eq(DEREF(c), _t2070);
        (void)_t2072;
        ;
        Bool _t2073 = U8_eq(DEREF(c), _t2071);
        (void)_t2073;
        ;
        U8 _t2074 = 13;
        (void)_t2074;
        Bool _t2075 = Bool_or(_t2072, _t2073);
        (void)_t2075;
        ;
        ;
        Bool _t2076 = U8_eq(DEREF(c), _t2074);
        (void)_t2076;
        ;
        U8 _t2077 = 59;
        (void)_t2077;
        Bool _t2078 = Bool_or(_t2075, _t2076);
        (void)_t2078;
        ;
        ;
        Bool _t2079 = U8_eq(DEREF(c), _t2077);
        (void)_t2079;
        ;
        Bool _t2080 = Bool_or(_t2078, _t2079);
        (void)_t2080;
        ;
        ;
        if (_t2080) {
            U64 _t1777 = U64_inc(DEREF(pos));
            (void)_t1777;
            *pos = _t1777;
            ;
            ;
            continue;
        }
        ;
        U8 _t2081 = 10;
        (void)_t2081;
        Bool _t2082 = U8_eq(DEREF(c), _t2081);
        (void)_t2082;
        ;
        if (_t2082) {
            U64 _t1778 = U64_inc(DEREF(pos));
            (void)_t1778;
            *pos = _t1778;
            ;
            I64 _t1779 = 1;
            (void)_t1779;
            I64 _t1780 = I64_add(line, _t1779);
            (void)_t1780;
            ;
            line = _t1780;
            ;
            U64 _t1781 = U64_clone(pos);
            (void)_t1781;
            line_start = _t1781;
            ;
            ;
            continue;
        }
        ;
        U64 _t2083 = U64_sub(DEREF(pos), line_start);
        (void)_t2083;
        U64 _t2084 = 1;
        (void)_t2084;
        U64 _t2085 = U64_add(_t2083, _t2084);
        (void)_t2085;
        ;
        ;
        I64 col = U64_to_i64(_t2085);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2086 = 35;
        (void)_t2086;
        Bool _t2087 = U8_eq(DEREF(c), _t2086);
        (void)_t2087;
        ;
        if (_t2087) {
            while (1) {
                Bool _wcond1782; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1782 = *_hp; free(_hp); }
                (void)_wcond1782;
                if (_wcond1782) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1783 = Str_byte_at(src, pos);
                (void)_t1783;
                U8 _t1784 = 10;
                (void)_t1784;
                Bool _t1785 = U8_eq(DEREF(_t1783), _t1784);
                (void)_t1785;
                ;
                if (_t1785) {
                    ;
                    break;
                }
                ;
                U64 _t1786 = U64_inc(DEREF(pos));
                (void)_t1786;
                *pos = _t1786;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2088 = 47;
        (void)_t2088;
        U64 _t2089 = 1;
        (void)_t2089;
        U64 _t2090 = U64_add(DEREF(pos), _t2089);
        (void)_t2090;
        ;
        Bool _t2091 = U8_eq(DEREF(c), _t2088);
        (void)_t2091;
        ;
        Bool _t2092; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2090}, &(U64){src_len}); _t2092 = *_hp; free(_hp); }
        (void)_t2092;
        ;
        Bool _t2093 = Bool_and(_t2091, _t2092);
        (void)_t2093;
        ;
        ;
        if (_t2093) {
            U64 _t1845 = 1;
            (void)_t1845;
            U64 *_t1846 = malloc(sizeof(U64)); *_t1846 = U64_add(DEREF(pos), _t1845);
            (void)_t1846;
            ;
            U8 *c2 = Str_byte_at(src, _t1846);
            (void)c2;
            U8 _t1847 = 47;
            (void)_t1847;
            Bool _t1848 = U8_eq(DEREF(c2), _t1847);
            (void)_t1848;
            ;
            if (_t1848) {
                while (1) {
                    Bool _wcond1787; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1787 = *_hp; free(_hp); }
                    (void)_wcond1787;
                    if (_wcond1787) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1788 = Str_byte_at(src, pos);
                    (void)_t1788;
                    U8 _t1789 = 10;
                    (void)_t1789;
                    Bool _t1790 = U8_eq(DEREF(_t1788), _t1789);
                    (void)_t1790;
                    ;
                    if (_t1790) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1791 = U64_inc(DEREF(pos));
                    (void)_t1791;
                    *pos = _t1791;
                    ;
                }
                U64_delete(_t1846, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1849 = 42;
            (void)_t1849;
            Bool _t1850 = U8_eq(DEREF(c2), _t1849);
            (void)_t1850;
            U64_delete(_t1846, &(Bool){1});
            ;
            if (_t1850) {
                U64 _t1841 = 2;
                (void)_t1841;
                U64 _t1842 = U64_add(DEREF(pos), _t1841);
                (void)_t1842;
                ;
                *pos = _t1842;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1792; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1792 = *_hp; free(_hp); }
                    (void)_wcond1792;
                    if (_wcond1792) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1817 = 0;
                    (void)_t1817;
                    Bool _t1818; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1817}); _t1818 = *_hp; free(_hp); }
                    (void)_t1818;
                    ;
                    if (_t1818) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1819 = 1;
                    (void)_t1819;
                    U64 _t1820 = U64_add(DEREF(pos), _t1819);
                    (void)_t1820;
                    ;
                    Bool _t1821; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1820}, &(U64){src_len}); _t1821 = *_hp; free(_hp); }
                    (void)_t1821;
                    ;
                    if (_t1821) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1801 = 1;
                        (void)_t1801;
                        U64 *_t1802 = malloc(sizeof(U64)); *_t1802 = U64_add(DEREF(pos), _t1801);
                        (void)_t1802;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1802);
                        (void)b2;
                        U8 _t1803 = 47;
                        (void)_t1803;
                        U8 _t1804 = 42;
                        (void)_t1804;
                        Bool _t1805 = U8_eq(DEREF(b1), _t1803);
                        (void)_t1805;
                        ;
                        Bool _t1806 = U8_eq(DEREF(b2), _t1804);
                        (void)_t1806;
                        ;
                        Bool _t1807 = Bool_and(_t1805, _t1806);
                        (void)_t1807;
                        ;
                        ;
                        if (_t1807) {
                            I64 _t1793 = 1;
                            (void)_t1793;
                            I64 _t1794 = I64_add(depth, _t1793);
                            (void)_t1794;
                            ;
                            depth = _t1794;
                            ;
                            U64 _t1795 = 2;
                            (void)_t1795;
                            U64 _t1796 = U64_add(DEREF(pos), _t1795);
                            (void)_t1796;
                            ;
                            *pos = _t1796;
                            ;
                            U64_delete(_t1802, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1808 = 42;
                        (void)_t1808;
                        U8 _t1809 = 47;
                        (void)_t1809;
                        Bool _t1810 = U8_eq(DEREF(b1), _t1808);
                        (void)_t1810;
                        ;
                        Bool _t1811 = U8_eq(DEREF(b2), _t1809);
                        (void)_t1811;
                        U64_delete(_t1802, &(Bool){1});
                        ;
                        Bool _t1812 = Bool_and(_t1810, _t1811);
                        (void)_t1812;
                        ;
                        ;
                        if (_t1812) {
                            I64 _t1797 = 1;
                            (void)_t1797;
                            I64 _t1798 = I64_sub(depth, _t1797);
                            (void)_t1798;
                            ;
                            depth = _t1798;
                            ;
                            U64 _t1799 = 2;
                            (void)_t1799;
                            U64 _t1800 = U64_add(DEREF(pos), _t1799);
                            (void)_t1800;
                            ;
                            *pos = _t1800;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1822 = Str_byte_at(src, pos);
                    (void)_t1822;
                    U8 _t1823 = 10;
                    (void)_t1823;
                    Bool _t1824 = U8_eq(DEREF(_t1822), _t1823);
                    (void)_t1824;
                    ;
                    if (_t1824) {
                        I64 _t1813 = 1;
                        (void)_t1813;
                        I64 _t1814 = I64_add(line, _t1813);
                        (void)_t1814;
                        ;
                        line = _t1814;
                        ;
                        U64 _t1815 = 1;
                        (void)_t1815;
                        U64 _t1816 = U64_add(DEREF(pos), _t1815);
                        (void)_t1816;
                        ;
                        line_start = _t1816;
                        ;
                    }
                    ;
                    U64 _t1825 = U64_inc(DEREF(pos));
                    (void)_t1825;
                    *pos = _t1825;
                    ;
                }
                I64 _t1843 = 0;
                (void)_t1843;
                Bool _t1844; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1843}); _t1844 = *_hp; free(_hp); }
                (void)_t1844;
                ;
                ;
                if (_t1844) {
                    Str *_t1826 = Str_lit("Str", 3ULL);
                    (void)_t1826;
                    U64 _t1827; { U64 *_hp = (U64 *)Str_size(); _t1827 = *_hp; free(_hp); }
                    (void)_t1827;
                    U64 _t1828 = 6;
                    (void)_t1828;
                    Array *_va20 = Array_new(_t1826, &(U64){_t1827}, &(U64){_t1828});
                    (void)_va20;
                    Str_delete(_t1826, &(Bool){1});
                    ;
                    ;
                    U64 _t1829 = 0;
                    (void)_t1829;
                    Str *_t1830 = Str_clone(path);
                    (void)_t1830;
                    Array_set(_va20, &(U64){_t1829}, _t1830);
                    ;
                    U64 _t1831 = 1;
                    (void)_t1831;
                    Str *_t1832 = Str_lit(":", 1ULL);
                    (void)_t1832;
                    Array_set(_va20, &(U64){_t1831}, _t1832);
                    ;
                    U64 _t1833 = 2;
                    (void)_t1833;
                    Str *_t1834 = I64_to_str(&(I64){line});
                    (void)_t1834;
                    Array_set(_va20, &(U64){_t1833}, _t1834);
                    ;
                    U64 _t1835 = 3;
                    (void)_t1835;
                    Str *_t1836 = Str_lit(":", 1ULL);
                    (void)_t1836;
                    Array_set(_va20, &(U64){_t1835}, _t1836);
                    ;
                    U64 _t1837 = 4;
                    (void)_t1837;
                    Str *_t1838 = I64_to_str(&(I64){col});
                    (void)_t1838;
                    Array_set(_va20, &(U64){_t1837}, _t1838);
                    ;
                    U64 _t1839 = 5;
                    (void)_t1839;
                    Str *_t1840 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1840;
                    Array_set(_va20, &(U64){_t1839}, _t1840);
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
        Bool _t2094; { Bool *_hp = (Bool *)is_digit(c); _t2094 = *_hp; free(_hp); }
        (void)_t2094;
        if (_t2094) {
            while (1) {
                Bool _wcond1851; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1851 = *_hp; free(_hp); }
                (void)_wcond1851;
                if (_wcond1851) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1852 = Str_byte_at(src, pos);
                (void)_t1852;
                Bool _t1853; { Bool *_hp = (Bool *)is_digit(_t1852); _t1853 = *_hp; free(_hp); }
                (void)_t1853;
                Bool _t1854 = Bool_not(_t1853);
                (void)_t1854;
                ;
                if (_t1854) {
                    ;
                    break;
                }
                ;
                U64 _t1855 = U64_inc(DEREF(pos));
                (void)_t1855;
                *pos = _t1855;
                ;
            }
            U64 _t1870 = 1;
            (void)_t1870;
            U64 _t1871 = U64_add(DEREF(pos), _t1870);
            (void)_t1871;
            ;
            Bool _t1872; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1871}, &(U64){src_len}); _t1872 = *_hp; free(_hp); }
            (void)_t1872;
            ;
            if (_t1872) {
                U8 *_t1862 = Str_byte_at(src, pos);
                (void)_t1862;
                U8 _t1863 = 46;
                (void)_t1863;
                U64 _t1864 = 1;
                (void)_t1864;
                U64 *_t1865 = malloc(sizeof(U64)); *_t1865 = U64_add(DEREF(pos), _t1864);
                (void)_t1865;
                ;
                U8 *_t1866 = Str_byte_at(src, _t1865);
                (void)_t1866;
                Bool _t1867 = U8_eq(DEREF(_t1862), _t1863);
                (void)_t1867;
                ;
                Bool _t1868; { Bool *_hp = (Bool *)is_digit(_t1866); _t1868 = *_hp; free(_hp); }
                (void)_t1868;
                U64_delete(_t1865, &(Bool){1});
                Bool _t1869 = Bool_and(_t1867, _t1868);
                (void)_t1869;
                ;
                ;
                if (_t1869) {
                    U64 _t1861 = U64_inc(DEREF(pos));
                    (void)_t1861;
                    *pos = _t1861;
                    ;
                    while (1) {
                        Bool _wcond1856; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1856 = *_hp; free(_hp); }
                        (void)_wcond1856;
                        if (_wcond1856) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1857 = Str_byte_at(src, pos);
                        (void)_t1857;
                        Bool _t1858; { Bool *_hp = (Bool *)is_digit(_t1857); _t1858 = *_hp; free(_hp); }
                        (void)_t1858;
                        Bool _t1859 = Bool_not(_t1858);
                        (void)_t1859;
                        ;
                        if (_t1859) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1860 = U64_inc(DEREF(pos));
                        (void)_t1860;
                        *pos = _t1860;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1873 = U64_sub(DEREF(pos), start);
            (void)_t1873;
            I64 _t1874 = I64_clone(&(I64){col});
            (void)_t1874;
            Token *_t1875 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1875->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1873}); _t1875->text = *_ca; free(_ca); }
            _t1875->line = I64_clone(&(I64){line});
            _t1875->col = _t1874;
            (void)_t1875;
            ;
            ;
            Vec_push(tokens, _t1875);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2095; { Bool *_hp = (Bool *)is_alpha(c); _t2095 = *_hp; free(_hp); }
        (void)_t2095;
        if (_t2095) {
            while (1) {
                Bool _wcond1876; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1876 = *_hp; free(_hp); }
                (void)_wcond1876;
                if (_wcond1876) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1877 = Str_byte_at(src, pos);
                (void)_t1877;
                Bool _t1878; { Bool *_hp = (Bool *)is_alnum(_t1877); _t1878 = *_hp; free(_hp); }
                (void)_t1878;
                Bool _t1879 = Bool_not(_t1878);
                (void)_t1879;
                ;
                if (_t1879) {
                    ;
                    break;
                }
                ;
                U64 _t1880 = U64_inc(DEREF(pos));
                (void)_t1880;
                *pos = _t1880;
                ;
            }
            U64 _t1881 = U64_sub(DEREF(pos), start);
            (void)_t1881;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1881});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1882 = I64_clone(&(I64){line});
            (void)_t1882;
            I64 _t1883 = I64_clone(&(I64){col});
            (void)_t1883;
            Token *_t1884 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1884->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1884->text = *_ca; free(_ca); }
            _t1884->line = _t1882;
            _t1884->col = _t1883;
            (void)_t1884;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1884);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2096 = 34;
        (void)_t2096;
        Bool _t2097 = U8_eq(DEREF(c), _t2096);
        (void)_t2097;
        ;
        if (_t2097) {
            U64 _t1931 = U64_inc(DEREF(pos));
            (void)_t1931;
            *pos = _t1931;
            ;
            while (1) {
                Bool _wcond1885; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1885 = *_hp; free(_hp); }
                (void)_wcond1885;
                if (_wcond1885) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1891 = Str_byte_at(src, pos);
                (void)_t1891;
                U8 _t1892 = 34;
                (void)_t1892;
                Bool _t1893 = U8_eq(DEREF(_t1891), _t1892);
                (void)_t1893;
                ;
                if (_t1893) {
                    ;
                    break;
                }
                ;
                U8 *_t1894 = Str_byte_at(src, pos);
                (void)_t1894;
                U8 _t1895 = 92;
                (void)_t1895;
                U64 _t1896 = 1;
                (void)_t1896;
                U64 _t1897 = U64_add(DEREF(pos), _t1896);
                (void)_t1897;
                ;
                Bool _t1898 = U8_eq(DEREF(_t1894), _t1895);
                (void)_t1898;
                ;
                Bool _t1899; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1897}, &(U64){src_len}); _t1899 = *_hp; free(_hp); }
                (void)_t1899;
                ;
                Bool _t1900 = Bool_and(_t1898, _t1899);
                (void)_t1900;
                ;
                ;
                if (_t1900) {
                    U64 _t1886 = U64_inc(DEREF(pos));
                    (void)_t1886;
                    *pos = _t1886;
                    ;
                }
                ;
                U8 *_t1901 = Str_byte_at(src, pos);
                (void)_t1901;
                U8 _t1902 = 10;
                (void)_t1902;
                Bool _t1903 = U8_eq(DEREF(_t1901), _t1902);
                (void)_t1903;
                ;
                if (_t1903) {
                    I64 _t1887 = 1;
                    (void)_t1887;
                    I64 _t1888 = I64_add(line, _t1887);
                    (void)_t1888;
                    ;
                    line = _t1888;
                    ;
                    U64 _t1889 = 1;
                    (void)_t1889;
                    U64 _t1890 = U64_add(DEREF(pos), _t1889);
                    (void)_t1890;
                    ;
                    line_start = _t1890;
                    ;
                }
                ;
                U64 _t1904 = U64_inc(DEREF(pos));
                (void)_t1904;
                *pos = _t1904;
                ;
            }
            U8 *_t1932 = Str_byte_at(src, pos);
            (void)_t1932;
            U8 _t1933 = 34;
            (void)_t1933;
            Bool _t1934; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1934 = *_hp; free(_hp); }
            (void)_t1934;
            Bool _t1935 = U8_eq(DEREF(_t1932), _t1933);
            (void)_t1935;
            ;
            Bool _t1936 = Bool_and(_t1934, _t1935);
            (void)_t1936;
            ;
            ;
            if (_t1936) {
                U64 _t1905 = U64_inc(DEREF(pos));
                (void)_t1905;
                *pos = _t1905;
                ;
                U64 _t1906 = 1;
                (void)_t1906;
                U64 _t1907 = U64_sub(DEREF(pos), start);
                (void)_t1907;
                U64 _t1908 = 2;
                (void)_t1908;
                U64 _t1909 = U64_add(start, _t1906);
                (void)_t1909;
                ;
                U64 _t1910 = U64_sub(_t1907, _t1908);
                (void)_t1910;
                ;
                ;
                I64 _t1911 = I64_clone(&(I64){col});
                (void)_t1911;
                Token *_t1912 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1912->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1909}, &(U64){_t1910}); _t1912->text = *_ca; free(_ca); }
                _t1912->line = I64_clone(&(I64){line});
                _t1912->col = _t1911;
                (void)_t1912;
                ;
                ;
                ;
                Vec_push(tokens, _t1912);
            } else {
                Str *_t1913 = Str_lit("Str", 3ULL);
                (void)_t1913;
                U64 _t1914; { U64 *_hp = (U64 *)Str_size(); _t1914 = *_hp; free(_hp); }
                (void)_t1914;
                U64 _t1915 = 6;
                (void)_t1915;
                Array *_va21 = Array_new(_t1913, &(U64){_t1914}, &(U64){_t1915});
                (void)_va21;
                Str_delete(_t1913, &(Bool){1});
                ;
                ;
                U64 _t1916 = 0;
                (void)_t1916;
                Str *_t1917 = Str_clone(path);
                (void)_t1917;
                Array_set(_va21, &(U64){_t1916}, _t1917);
                ;
                U64 _t1918 = 1;
                (void)_t1918;
                Str *_t1919 = Str_lit(":", 1ULL);
                (void)_t1919;
                Array_set(_va21, &(U64){_t1918}, _t1919);
                ;
                U64 _t1920 = 2;
                (void)_t1920;
                Str *_t1921 = I64_to_str(&(I64){line});
                (void)_t1921;
                Array_set(_va21, &(U64){_t1920}, _t1921);
                ;
                U64 _t1922 = 3;
                (void)_t1922;
                Str *_t1923 = Str_lit(":", 1ULL);
                (void)_t1923;
                Array_set(_va21, &(U64){_t1922}, _t1923);
                ;
                U64 _t1924 = 4;
                (void)_t1924;
                Str *_t1925 = I64_to_str(&(I64){col});
                (void)_t1925;
                Array_set(_va21, &(U64){_t1924}, _t1925);
                ;
                U64 _t1926 = 5;
                (void)_t1926;
                Str *_t1927 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1927;
                Array_set(_va21, &(U64){_t1926}, _t1927);
                ;
                println(_va21);
                U64 _t1928 = U64_sub(DEREF(pos), start);
                (void)_t1928;
                I64 _t1929 = I64_clone(&(I64){col});
                (void)_t1929;
                Token *_t1930 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1930->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1928}); _t1930->text = *_ca; free(_ca); }
                _t1930->line = I64_clone(&(I64){line});
                _t1930->col = _t1929;
                (void)_t1930;
                ;
                ;
                Vec_push(tokens, _t1930);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2098 = 39;
        (void)_t2098;
        Bool _t2099 = U8_eq(DEREF(c), _t2098);
        (void)_t2099;
        ;
        if (_t2099) {
            U64 _t1960 = U64_inc(DEREF(pos));
            (void)_t1960;
            *pos = _t1960;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t1961 = Str_byte_at(src, pos);
            (void)_t1961;
            U8 _t1962 = 92;
            (void)_t1962;
            U64 _t1963 = 1;
            (void)_t1963;
            U64 _t1964 = U64_add(DEREF(pos), _t1963);
            (void)_t1964;
            ;
            Bool _t1965 = U8_eq(DEREF(_t1961), _t1962);
            (void)_t1965;
            ;
            Bool _t1966; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1964}, &(U64){src_len}); _t1966 = *_hp; free(_hp); }
            (void)_t1966;
            ;
            Bool _t1967; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1967 = *_hp; free(_hp); }
            (void)_t1967;
            Bool _t1968 = Bool_and(_t1965, _t1966);
            (void)_t1968;
            ;
            ;
            Bool _t1969 = Bool_and(_t1967, _t1968);
            (void)_t1969;
            ;
            ;
            if (_t1969) {
                U64 _t1937 = U64_inc(DEREF(pos));
                (void)_t1937;
                *pos = _t1937;
                ;
            }
            ;
            U64 _t1970 = U64_inc(DEREF(pos));
            (void)_t1970;
            *pos = _t1970;
            ;
            U8 *_t1971 = Str_byte_at(src, pos);
            (void)_t1971;
            U8 _t1972 = 39;
            (void)_t1972;
            Bool _t1973; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1973 = *_hp; free(_hp); }
            (void)_t1973;
            Bool _t1974 = U8_eq(DEREF(_t1971), _t1972);
            (void)_t1974;
            ;
            Bool _t1975 = Bool_and(_t1973, _t1974);
            (void)_t1975;
            ;
            ;
            if (_t1975) {
                U64 _t1938 = U64_sub(DEREF(pos), ch_start);
                (void)_t1938;
                I64 _t1939 = I64_clone(&(I64){col});
                (void)_t1939;
                Token *_t1940 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1940->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1938}); _t1940->text = *_ca; free(_ca); }
                _t1940->line = I64_clone(&(I64){line});
                _t1940->col = _t1939;
                (void)_t1940;
                ;
                ;
                Vec_push(tokens, _t1940);
                U64 _t1941 = U64_inc(DEREF(pos));
                (void)_t1941;
                *pos = _t1941;
                ;
            } else {
                Str *_t1942 = Str_lit("Str", 3ULL);
                (void)_t1942;
                U64 _t1943; { U64 *_hp = (U64 *)Str_size(); _t1943 = *_hp; free(_hp); }
                (void)_t1943;
                U64 _t1944 = 6;
                (void)_t1944;
                Array *_va22 = Array_new(_t1942, &(U64){_t1943}, &(U64){_t1944});
                (void)_va22;
                Str_delete(_t1942, &(Bool){1});
                ;
                ;
                U64 _t1945 = 0;
                (void)_t1945;
                Str *_t1946 = Str_clone(path);
                (void)_t1946;
                Array_set(_va22, &(U64){_t1945}, _t1946);
                ;
                U64 _t1947 = 1;
                (void)_t1947;
                Str *_t1948 = Str_lit(":", 1ULL);
                (void)_t1948;
                Array_set(_va22, &(U64){_t1947}, _t1948);
                ;
                U64 _t1949 = 2;
                (void)_t1949;
                Str *_t1950 = I64_to_str(&(I64){line});
                (void)_t1950;
                Array_set(_va22, &(U64){_t1949}, _t1950);
                ;
                U64 _t1951 = 3;
                (void)_t1951;
                Str *_t1952 = Str_lit(":", 1ULL);
                (void)_t1952;
                Array_set(_va22, &(U64){_t1951}, _t1952);
                ;
                U64 _t1953 = 4;
                (void)_t1953;
                Str *_t1954 = I64_to_str(&(I64){col});
                (void)_t1954;
                Array_set(_va22, &(U64){_t1953}, _t1954);
                ;
                U64 _t1955 = 5;
                (void)_t1955;
                Str *_t1956 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t1956;
                Array_set(_va22, &(U64){_t1955}, _t1956);
                ;
                println(_va22);
                U64 _t1957 = U64_sub(DEREF(pos), start);
                (void)_t1957;
                I64 _t1958 = I64_clone(&(I64){col});
                (void)_t1958;
                Token *_t1959 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1959->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1957}); _t1959->text = *_ca; free(_ca); }
                _t1959->line = I64_clone(&(I64){line});
                _t1959->col = _t1958;
                (void)_t1959;
                ;
                ;
                Vec_push(tokens, _t1959);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2100 = 1;
        (void)_t2100;
        U64 _t2101 = U64_add(DEREF(pos), _t2100);
        (void)_t2101;
        ;
        Bool _t2102; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2101}, &(U64){src_len}); _t2102 = *_hp; free(_hp); }
        (void)_t2102;
        ;
        if (_t2102) {
            U64 _t2019 = 1;
            (void)_t2019;
            U64 *_t2020 = malloc(sizeof(U64)); *_t2020 = U64_add(DEREF(pos), _t2019);
            (void)_t2020;
            ;
            U8 *c2 = Str_byte_at(src, _t2020);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2021 = 58;
            (void)_t2021;
            U8 _t2022 = 61;
            (void)_t2022;
            Bool _t2023 = U8_eq(DEREF(c), _t2021);
            (void)_t2023;
            ;
            Bool _t2024 = U8_eq(DEREF(c2), _t2022);
            (void)_t2024;
            ;
            Bool _t2025 = Bool_and(_t2023, _t2024);
            (void)_t2025;
            ;
            ;
            if (_t2025) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2008 = 61;
                (void)_t2008;
                U8 _t2009 = 61;
                (void)_t2009;
                Bool _t2010 = U8_eq(DEREF(c), _t2008);
                (void)_t2010;
                ;
                Bool _t2011 = U8_eq(DEREF(c2), _t2009);
                (void)_t2011;
                ;
                Bool _t2012 = Bool_and(_t2010, _t2011);
                (void)_t2012;
                ;
                ;
                if (_t2012) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2003 = 33;
                    (void)_t2003;
                    U8 _t2004 = 61;
                    (void)_t2004;
                    Bool _t2005 = U8_eq(DEREF(c), _t2003);
                    (void)_t2005;
                    ;
                    Bool _t2006 = U8_eq(DEREF(c2), _t2004);
                    (void)_t2006;
                    ;
                    Bool _t2007 = Bool_and(_t2005, _t2006);
                    (void)_t2007;
                    ;
                    ;
                    if (_t2007) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1998 = 60;
                        (void)_t1998;
                        U8 _t1999 = 61;
                        (void)_t1999;
                        Bool _t2000 = U8_eq(DEREF(c), _t1998);
                        (void)_t2000;
                        ;
                        Bool _t2001 = U8_eq(DEREF(c2), _t1999);
                        (void)_t2001;
                        ;
                        Bool _t2002 = Bool_and(_t2000, _t2001);
                        (void)_t2002;
                        ;
                        ;
                        if (_t2002) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1993 = 62;
                            (void)_t1993;
                            U8 _t1994 = 61;
                            (void)_t1994;
                            Bool _t1995 = U8_eq(DEREF(c), _t1993);
                            (void)_t1995;
                            ;
                            Bool _t1996 = U8_eq(DEREF(c2), _t1994);
                            (void)_t1996;
                            ;
                            Bool _t1997 = Bool_and(_t1995, _t1996);
                            (void)_t1997;
                            ;
                            ;
                            if (_t1997) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1988 = 46;
                                (void)_t1988;
                                U8 _t1989 = 46;
                                (void)_t1989;
                                Bool _t1990 = U8_eq(DEREF(c), _t1988);
                                (void)_t1990;
                                ;
                                Bool _t1991 = U8_eq(DEREF(c2), _t1989);
                                (void)_t1991;
                                ;
                                Bool _t1992 = Bool_and(_t1990, _t1991);
                                (void)_t1992;
                                ;
                                ;
                                if (_t1992) {
                                    U64 _t1985 = 2;
                                    (void)_t1985;
                                    U64 _t1986 = U64_add(DEREF(pos), _t1985);
                                    (void)_t1986;
                                    ;
                                    Bool _t1987; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1986}, &(U64){src_len}); _t1987 = *_hp; free(_hp); }
                                    (void)_t1987;
                                    ;
                                    if (_t1987) {
                                        U64 _t1981 = 2;
                                        (void)_t1981;
                                        U64 *_t1982 = malloc(sizeof(U64)); *_t1982 = U64_add(DEREF(pos), _t1981);
                                        (void)_t1982;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t1982);
                                        (void)c3;
                                        U8 _t1983 = 46;
                                        (void)_t1983;
                                        Bool _t1984 = U8_eq(DEREF(c3), _t1983);
                                        (void)_t1984;
                                        U64_delete(_t1982, &(Bool){1});
                                        ;
                                        if (_t1984) {
                                            U64 _t1976 = 3;
                                            (void)_t1976;
                                            I64 _t1977 = I64_clone(&(I64){col});
                                            (void)_t1977;
                                            Token *_t1978 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t1978->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1976}); _t1978->text = *_ca; free(_ca); }
                                            _t1978->line = I64_clone(&(I64){line});
                                            _t1978->col = _t1977;
                                            (void)_t1978;
                                            ;
                                            ;
                                            Vec_push(tokens, _t1978);
                                            U64 _t1979 = 3;
                                            (void)_t1979;
                                            U64 _t1980 = U64_add(DEREF(pos), _t1979);
                                            (void)_t1980;
                                            ;
                                            *pos = _t1980;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2020, &(Bool){1});
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
            U64_delete(_t2020, &(Bool){1});
            ;
            Bool _t2026; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2026 = *_hp; free(_hp); }
            (void)_t2026;
            Bool _t2027 = Bool_not(_t2026);
            (void)_t2027;
            ;
            if (_t2027) {
                U64 _t2013 = 2;
                (void)_t2013;
                I64 _t2014 = I64_clone(&(I64){line});
                (void)_t2014;
                I64 _t2015 = I64_clone(&(I64){col});
                (void)_t2015;
                Token *_t2016 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2016->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2013}); _t2016->text = *_ca; free(_ca); }
                _t2016->line = _t2014;
                _t2016->col = _t2015;
                (void)_t2016;
                ;
                ;
                ;
                Vec_push(tokens, _t2016);
                U64 _t2017 = 2;
                (void)_t2017;
                U64 _t2018 = U64_add(DEREF(pos), _t2017);
                (void)_t2018;
                ;
                *pos = _t2018;
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
            U8 _sw2028 = U8_clone(c);
            (void)_sw2028;
            U8 _t2063 = 40;
            (void)_t2063;
            Bool _t2064 = U8_eq(_sw2028, _t2063);
            (void)_t2064;
            ;
            if (_t2064) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2061 = 41;
                (void)_t2061;
                Bool _t2062 = U8_eq(_sw2028, _t2061);
                (void)_t2062;
                ;
                if (_t2062) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2059 = 123;
                    (void)_t2059;
                    Bool _t2060 = U8_eq(_sw2028, _t2059);
                    (void)_t2060;
                    ;
                    if (_t2060) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2057 = 125;
                        (void)_t2057;
                        Bool _t2058 = U8_eq(_sw2028, _t2057);
                        (void)_t2058;
                        ;
                        if (_t2058) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2055 = 91;
                            (void)_t2055;
                            Bool _t2056 = U8_eq(_sw2028, _t2055);
                            (void)_t2056;
                            ;
                            if (_t2056) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2053 = 93;
                                (void)_t2053;
                                Bool _t2054 = U8_eq(_sw2028, _t2053);
                                (void)_t2054;
                                ;
                                if (_t2054) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2051 = 44;
                                    (void)_t2051;
                                    Bool _t2052 = U8_eq(_sw2028, _t2051);
                                    (void)_t2052;
                                    ;
                                    if (_t2052) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2049 = 58;
                                        (void)_t2049;
                                        Bool _t2050 = U8_eq(_sw2028, _t2049);
                                        (void)_t2050;
                                        ;
                                        if (_t2050) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2047 = 46;
                                            (void)_t2047;
                                            Bool _t2048 = U8_eq(_sw2028, _t2047);
                                            (void)_t2048;
                                            ;
                                            if (_t2048) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2045 = 63;
                                                (void)_t2045;
                                                Bool _t2046 = U8_eq(_sw2028, _t2045);
                                                (void)_t2046;
                                                ;
                                                if (_t2046) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2043 = 33;
                                                    (void)_t2043;
                                                    Bool _t2044 = U8_eq(_sw2028, _t2043);
                                                    (void)_t2044;
                                                    ;
                                                    if (_t2044) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2041 = 43;
                                                        (void)_t2041;
                                                        Bool _t2042 = U8_eq(_sw2028, _t2041);
                                                        (void)_t2042;
                                                        ;
                                                        if (_t2042) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2039 = 45;
                                                            (void)_t2039;
                                                            Bool _t2040 = U8_eq(_sw2028, _t2039);
                                                            (void)_t2040;
                                                            ;
                                                            if (_t2040) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2037 = 42;
                                                                (void)_t2037;
                                                                Bool _t2038 = U8_eq(_sw2028, _t2037);
                                                                (void)_t2038;
                                                                ;
                                                                if (_t2038) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2035 = 47;
                                                                    (void)_t2035;
                                                                    Bool _t2036 = U8_eq(_sw2028, _t2035);
                                                                    (void)_t2036;
                                                                    ;
                                                                    if (_t2036) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2033 = 61;
                                                                        (void)_t2033;
                                                                        Bool _t2034 = U8_eq(_sw2028, _t2033);
                                                                        (void)_t2034;
                                                                        ;
                                                                        if (_t2034) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2031 = 60;
                                                                            (void)_t2031;
                                                                            Bool _t2032 = U8_eq(_sw2028, _t2031);
                                                                            (void)_t2032;
                                                                            ;
                                                                            if (_t2032) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2029 = 62;
                                                                                (void)_t2029;
                                                                                Bool _t2030 = U8_eq(_sw2028, _t2029);
                                                                                (void)_t2030;
                                                                                ;
                                                                                if (_t2030) {
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
        Bool _t2103; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2103 = *_hp; free(_hp); }
        (void)_t2103;
        Bool _t2104 = Bool_not(_t2103);
        (void)_t2104;
        ;
        if (_t2104) {
            U64 _t2065 = 1;
            (void)_t2065;
            I64 _t2066 = I64_clone(&(I64){line});
            (void)_t2066;
            I64 _t2067 = I64_clone(&(I64){col});
            (void)_t2067;
            Token *_t2068 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2068->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2065}); _t2068->text = *_ca; free(_ca); }
            _t2068->line = _t2066;
            _t2068->col = _t2067;
            (void)_t2068;
            ;
            ;
            ;
            Vec_push(tokens, _t2068);
            U64 _t2069 = U64_inc(DEREF(pos));
            (void)_t2069;
            *pos = _t2069;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2105 = Str_lit("Str", 3ULL);
        (void)_t2105;
        U64 _t2106; { U64 *_hp = (U64 *)Str_size(); _t2106 = *_hp; free(_hp); }
        (void)_t2106;
        U64 _t2107 = 6;
        (void)_t2107;
        Array *_va23 = Array_new(_t2105, &(U64){_t2106}, &(U64){_t2107});
        (void)_va23;
        Str_delete(_t2105, &(Bool){1});
        ;
        ;
        U64 _t2108 = 0;
        (void)_t2108;
        Str *_t2109 = Str_clone(path);
        (void)_t2109;
        Array_set(_va23, &(U64){_t2108}, _t2109);
        ;
        U64 _t2110 = 1;
        (void)_t2110;
        Str *_t2111 = Str_lit(":", 1ULL);
        (void)_t2111;
        Array_set(_va23, &(U64){_t2110}, _t2111);
        ;
        U64 _t2112 = 2;
        (void)_t2112;
        Str *_t2113 = I64_to_str(&(I64){line});
        (void)_t2113;
        Array_set(_va23, &(U64){_t2112}, _t2113);
        ;
        U64 _t2114 = 3;
        (void)_t2114;
        Str *_t2115 = Str_lit(":", 1ULL);
        (void)_t2115;
        Array_set(_va23, &(U64){_t2114}, _t2115);
        ;
        U64 _t2116 = 4;
        (void)_t2116;
        Str *_t2117 = I64_to_str(&(I64){col});
        (void)_t2117;
        Array_set(_va23, &(U64){_t2116}, _t2117);
        ;
        U64 _t2118 = 5;
        (void)_t2118;
        Str *_t2119 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2119;
        Array_set(_va23, &(U64){_t2118}, _t2119);
        ;
        println(_va23);
        U64 _t2120 = 1;
        (void)_t2120;
        I64 _t2121 = I64_clone(&(I64){col});
        (void)_t2121;
        ;
        Token *_t2122 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2122->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2120}); _t2122->text = *_ca; free(_ca); }
        _t2122->line = I64_clone(&(I64){line});
        _t2122->col = _t2121;
        (void)_t2122;
        ;
        ;
        ;
        Vec_push(tokens, _t2122);
        U64 _t2123 = U64_inc(DEREF(pos));
        (void)_t2123;
        *pos = _t2123;
        ;
    }
    ;
    U64 _t2126 = U64_sub(DEREF(pos), line_start);
    (void)_t2126;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2127 = 1;
    (void)_t2127;
    U64 _t2128 = U64_add(_t2126, _t2127);
    (void)_t2128;
    ;
    ;
    I64 col = U64_to_i64(_t2128);
    (void)col;
    ;
    I64 _t2129 = I64_clone(&(I64){col});
    (void)_t2129;
    ;
    Token *_t2130 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2130->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2130->text = *_ca; free(_ca); }
    _t2130->line = I64_clone(&(I64){line});
    _t2130->col = _t2129;
    (void)_t2130;
    ;
    ;
    Vec_push(tokens, _t2130);
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
    _t2131 = malloc(sizeof(I64));
    *_t2131 = 0;
    (void)_t2131;
    _t2132 = malloc(sizeof(I64));
    *_t2132 = 1;
    (void)_t2132;
    _t2133 = malloc(sizeof(I64)); *_t2133 = I64_sub(DEREF(_t2131), DEREF(_t2132));
    (void)_t2133;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2133));
    (void)CAP_LIT;
    _t2134 = malloc(sizeof(I64));
    *_t2134 = 0;
    (void)_t2134;
    _t2135 = malloc(sizeof(I64));
    *_t2135 = 2;
    (void)_t2135;
    _t2136 = malloc(sizeof(I64)); *_t2136 = I64_sub(DEREF(_t2134), DEREF(_t2135));
    (void)_t2136;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2136));
    (void)CAP_VIEW;
}

