#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include "ext.h"

typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct Dynamic Dynamic;
typedef enum {
    FuncType_TAG_Func,
    FuncType_TAG_Proc,
    FuncType_TAG_Test,
    FuncType_TAG_Macro,
    FuncType_TAG_ExtFunc,
    FuncType_TAG_ExtProc
} FuncType_tag;
typedef struct FuncType FuncType;
typedef struct FunctionDef FunctionDef;
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
Bool * FuncType_eq(FuncType * self, FuncType * other);
FuncType * FuncType_clone(FuncType * self);
void FuncType_delete(FuncType * self, Bool * call_free);
Str * FuncType_to_str(FuncType * self);
U64 * FuncType_size(void);
Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b);
Str * FunctionDef_to_str(FunctionDef * self);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U64 * FunctionDef_size(void);
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
Bool * FuncType_eq(FuncType *, FuncType *);
FuncType *FuncType_Func();
FuncType *FuncType_Proc();
FuncType *FuncType_Test();
FuncType *FuncType_Macro();
FuncType *FuncType_ExtFunc();
FuncType *FuncType_ExtProc();
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


typedef struct Dynamic {
    char _;
} Dynamic;


struct FuncType {
    FuncType_tag tag;
};








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


typedef struct FunctionDef {
    FuncType func_type;
    Vec param_names;
    Vec param_types;
    Vec param_muts;
    Vec param_owns;
    Vec param_shallows;
    Vec param_fn_sigs;
    U32 nparam;
    Vec param_defaults;
    Str return_type;
    I32 variadic_index;
    I32 kwargs_index;
    Bool return_is_ref;
    Bool return_is_shallow;
} FunctionDef;


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ULLONG_MAX
__attribute__((unused))
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

static I64 *_t2185;
static I64 *_t2186;
static I64 *_t2187;
static U64 *CAP_LIT;
static I64 *_t2188;
static I64 *_t2189;
static I64 *_t2190;
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

FuncType *FuncType_Func() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Func };
    return r;
}
FuncType *FuncType_Proc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Proc };
    return r;
}
FuncType *FuncType_Test() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Test };
    return r;
}
FuncType *FuncType_Macro() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_Macro };
    return r;
}
FuncType *FuncType_ExtFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_ExtFunc };
    return r;
}
FuncType *FuncType_ExtProc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_ExtProc };
    return r;
}
Bool *FuncType_is_Func(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_Func);
    return r;
}
Bool *FuncType_is_Proc(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_Proc);
    return r;
}
Bool *FuncType_is_Test(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_Test);
    return r;
}
Bool *FuncType_is_Macro(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_Macro);
    return r;
}
Bool *FuncType_is_ExtFunc(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_ExtFunc);
    return r;
}
Bool *FuncType_is_ExtProc(FuncType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == FuncType_TAG_ExtProc);
    return r;
}
Bool * FuncType_eq(FuncType * self, FuncType * other) {
    (void)self;
    (void)other;
    Bool _t8; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t8 = *_hp; free(_hp); }
    (void)_t8;
    if (_t8) {
        Bool _t2; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t2 = *_hp; free(_hp); }
        (void)_t2;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2; return _r; }
    }
    ;
    Bool _t9; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t9 = *_hp; free(_hp); }
    (void)_t9;
    if (_t9) {
        Bool _t3; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t3 = *_hp; free(_hp); }
        (void)_t3;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t3; return _r; }
    }
    ;
    Bool _t10; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t10 = *_hp; free(_hp); }
    (void)_t10;
    if (_t10) {
        Bool _t4; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t4 = *_hp; free(_hp); }
        (void)_t4;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t4; return _r; }
    }
    ;
    Bool _t11; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t11 = *_hp; free(_hp); }
    (void)_t11;
    if (_t11) {
        Bool _t5; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t5 = *_hp; free(_hp); }
        (void)_t5;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t5; return _r; }
    }
    ;
    Bool _t12; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t12 = *_hp; free(_hp); }
    (void)_t12;
    if (_t12) {
        Bool _t6; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t6 = *_hp; free(_hp); }
        (void)_t6;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t6; return _r; }
    }
    ;
    Bool _t13; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t13 = *_hp; free(_hp); }
    (void)_t13;
    if (_t13) {
        Bool _t7; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t7 = *_hp; free(_hp); }
        (void)_t7;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t7; return _r; }
    }
    ;
    Bool _t14 = 0;
    (void)_t14;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t14; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t15; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t15 = *_hp; free(_hp); }
    (void)_t15;
    if (_t15) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t16; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t16 = *_hp; free(_hp); }
    (void)_t16;
    if (_t16) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t17; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t17 = *_hp; free(_hp); }
    (void)_t17;
    if (_t17) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t18; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t18 = *_hp; free(_hp); }
    (void)_t18;
    if (_t18) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t19; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t19 = *_hp; free(_hp); }
    (void)_t19;
    if (_t19) {
        ;
        return FuncType_ExtFunc();
    }
    ;
    return FuncType_ExtProc();
}

void FuncType_delete(FuncType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * FuncType_to_str(FuncType * self) {
    (void)self;
    Bool _t26; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t26 = *_hp; free(_hp); }
    (void)_t26;
    if (_t26) {
        Str *_t20 = Str_lit("Func", 4ULL);
        (void)_t20;
        ;
        return _t20;
    }
    ;
    Bool _t27; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t27 = *_hp; free(_hp); }
    (void)_t27;
    if (_t27) {
        Str *_t21 = Str_lit("Proc", 4ULL);
        (void)_t21;
        ;
        return _t21;
    }
    ;
    Bool _t28; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t28 = *_hp; free(_hp); }
    (void)_t28;
    if (_t28) {
        Str *_t22 = Str_lit("Test", 4ULL);
        (void)_t22;
        ;
        return _t22;
    }
    ;
    Bool _t29; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t29 = *_hp; free(_hp); }
    (void)_t29;
    if (_t29) {
        Str *_t23 = Str_lit("Macro", 5ULL);
        (void)_t23;
        ;
        return _t23;
    }
    ;
    Bool _t30; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t30 = *_hp; free(_hp); }
    (void)_t30;
    if (_t30) {
        Str *_t24 = Str_lit("ExtFunc", 7ULL);
        (void)_t24;
        ;
        return _t24;
    }
    ;
    Bool _t31; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t31 = *_hp; free(_hp); }
    (void)_t31;
    if (_t31) {
        Str *_t25 = Str_lit("ExtProc", 7ULL);
        (void)_t25;
        ;
        return _t25;
    }
    ;
    Str *_t32 = Str_lit("unknown", 7ULL);
    (void)_t32;
    return _t32;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t34; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t34 = *_hp; free(_hp); }
    (void)_t34;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t34; return _r; }
}

Str * FunctionDef_to_str(FunctionDef * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->return_type; return _r; }
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    (void)self;
    U32 _t35 = U32_clone(&self->nparam);
    (void)_t35;
    I32 _t36 = I32_clone(&self->variadic_index);
    (void)_t36;
    I32 _t37 = I32_clone(&self->kwargs_index);
    (void)_t37;
    Bool _t38 = Bool_clone(&self->return_is_ref);
    (void)_t38;
    Bool _t39 = Bool_clone(&self->return_is_shallow);
    (void)_t39;
    FunctionDef *_t40 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t40->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_names); _t40->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_types); _t40->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_muts); _t40->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_owns); _t40->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_shallows); _t40->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_fn_sigs); _t40->param_fn_sigs = *_ca; free(_ca); }
    _t40->nparam = _t35;
    { Vec *_ca = Vec_clone(&self->param_defaults); _t40->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t40->return_type = *_ca; free(_ca); }
    _t40->variadic_index = _t36;
    _t40->kwargs_index = _t37;
    _t40->return_is_ref = _t38;
    _t40->return_is_shallow = _t39;
    (void)_t40;
    ;
    ;
    ;
    ;
    ;
    return _t40;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t41 = 0;
    (void)_t41;
    FuncType_delete(&self->func_type, &(Bool){_t41});
    ;
    Bool _t42 = 0;
    (void)_t42;
    Vec_delete(&self->param_names, &(Bool){_t42});
    ;
    Bool _t43 = 0;
    (void)_t43;
    Vec_delete(&self->param_types, &(Bool){_t43});
    ;
    Bool _t44 = 0;
    (void)_t44;
    Vec_delete(&self->param_muts, &(Bool){_t44});
    ;
    Bool _t45 = 0;
    (void)_t45;
    Vec_delete(&self->param_owns, &(Bool){_t45});
    ;
    Bool _t46 = 0;
    (void)_t46;
    Vec_delete(&self->param_shallows, &(Bool){_t46});
    ;
    Bool _t47 = 0;
    (void)_t47;
    Vec_delete(&self->param_fn_sigs, &(Bool){_t47});
    ;
    Bool _t48 = 0;
    (void)_t48;
    U32_delete(&self->nparam, &(Bool){_t48});
    ;
    Bool _t49 = 0;
    (void)_t49;
    Vec_delete(&self->param_defaults, &(Bool){_t49});
    ;
    Bool _t50 = 0;
    (void)_t50;
    Str_delete(&self->return_type, &(Bool){_t50});
    ;
    Bool _t51 = 0;
    (void)_t51;
    I32_delete(&self->variadic_index, &(Bool){_t51});
    ;
    Bool _t52 = 0;
    (void)_t52;
    I32_delete(&self->kwargs_index, &(Bool){_t52});
    ;
    Bool _t53 = 0;
    (void)_t53;
    Bool_delete(&self->return_is_ref, &(Bool){_t53});
    ;
    Bool _t54 = 0;
    (void)_t54;
    Bool_delete(&self->return_is_shallow, &(Bool){_t54});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *FunctionDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FunctionDef);
    return r;
}

static __attribute__((unused)) Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t56 = U8_to_i64(DEREF(val));
    (void)_t56;
    Str *_t57 = I64_to_str(&(I64){_t56});
    (void)_t57;
    ;
    return _t57;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t59 = 0;
    (void)_t59;
    I64 _t60 = 1;
    (void)_t60;
    I64 _t61 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t61;
    I64 _t62 = I64_sub(_t59, _t60);
    (void)_t62;
    ;
    ;
    Bool _t63 = I64_eq(_t61, _t62);
    (void)_t63;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t63; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t64 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t64;
    I64 _t65 = 1;
    (void)_t65;
    Bool _t66 = I64_eq(_t64, _t65);
    (void)_t66;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t66; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t67 = U8_eq(DEREF(a), DEREF(b));
    (void)_t67;
    Bool _t68 = Bool_not(_t67);
    (void)_t68;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t68; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t69; { Bool *_hp = (Bool *)U8_gt(a, b); _t69 = *_hp; free(_hp); }
    (void)_t69;
    Bool _t70 = Bool_not(_t69);
    (void)_t70;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t71; { Bool *_hp = (Bool *)U8_lt(a, b); _t71 = *_hp; free(_hp); }
    (void)_t71;
    Bool _t72 = Bool_not(_t71);
    (void)_t72;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t73 = I16_to_i64(DEREF(val));
    (void)_t73;
    Str *_t74 = I64_to_str(&(I64){_t73});
    (void)_t74;
    ;
    return _t74;
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t75 = 0;
    (void)_t75;
    I64 _t76 = I16_to_i64(DEREF(a));
    (void)_t76;
    I64 _t77 = I64_sub(_t75, _t76);
    (void)_t77;
    ;
    ;
    I16 _t78 = I64_to_i16(_t77);
    (void)_t78;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t78; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t83 = I16_to_i64(DEREF(a));
    (void)_t83;
    I64 _t84 = 0;
    (void)_t84;
    Bool _t85; { Bool *_hp = (Bool *)I64_lt(&(I64){_t83}, &(I64){_t84}); _t85 = *_hp; free(_hp); }
    (void)_t85;
    ;
    ;
    if (_t85) {
        I64 _t79 = 0;
        (void)_t79;
        I64 _t80 = I16_to_i64(DEREF(a));
        (void)_t80;
        I64 _t81 = I64_sub(_t79, _t80);
        (void)_t81;
        ;
        ;
        I16 _t82 = I64_to_i16(_t81);
        (void)_t82;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t82; return _r; }
    }
    ;
    I16 _t86 = I16_clone(a);
    (void)_t86;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t86; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t88 = 0;
    (void)_t88;
    I64 _t89 = 1;
    (void)_t89;
    I64 _t90 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t90;
    I64 _t91 = I64_sub(_t88, _t89);
    (void)_t91;
    ;
    ;
    Bool _t92 = I64_eq(_t90, _t91);
    (void)_t92;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t93 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t93;
    I64 _t94 = 1;
    (void)_t94;
    Bool _t95 = I64_eq(_t93, _t94);
    (void)_t95;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t95; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t96 = I16_eq(DEREF(a), DEREF(b));
    (void)_t96;
    Bool _t97 = Bool_not(_t96);
    (void)_t97;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t97; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t98; { Bool *_hp = (Bool *)I16_gt(a, b); _t98 = *_hp; free(_hp); }
    (void)_t98;
    Bool _t99 = Bool_not(_t98);
    (void)_t99;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t99; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t100; { Bool *_hp = (Bool *)I16_lt(a, b); _t100 = *_hp; free(_hp); }
    (void)_t100;
    Bool _t101 = Bool_not(_t100);
    (void)_t101;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t101; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t102 = I32_to_i64(DEREF(val));
    (void)_t102;
    Str *_t103 = I64_to_str(&(I64){_t102});
    (void)_t103;
    ;
    return _t103;
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t104 = 0;
    (void)_t104;
    I64 _t105 = I32_to_i64(DEREF(a));
    (void)_t105;
    I64 _t106 = I64_sub(_t104, _t105);
    (void)_t106;
    ;
    ;
    I32 _t107 = I64_to_i32(_t106);
    (void)_t107;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t107; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t112 = I32_to_i64(DEREF(a));
    (void)_t112;
    I64 _t113 = 0;
    (void)_t113;
    Bool _t114; { Bool *_hp = (Bool *)I64_lt(&(I64){_t112}, &(I64){_t113}); _t114 = *_hp; free(_hp); }
    (void)_t114;
    ;
    ;
    if (_t114) {
        I64 _t108 = 0;
        (void)_t108;
        I64 _t109 = I32_to_i64(DEREF(a));
        (void)_t109;
        I64 _t110 = I64_sub(_t108, _t109);
        (void)_t110;
        ;
        ;
        I32 _t111 = I64_to_i32(_t110);
        (void)_t111;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t111; return _r; }
    }
    ;
    I32 _t115 = I32_clone(a);
    (void)_t115;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t115; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t117 = 0;
    (void)_t117;
    I64 _t118 = 1;
    (void)_t118;
    I64 _t119 = I32_cmp(DEREF(a), DEREF(b));
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

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t122 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t122;
    I64 _t123 = 1;
    (void)_t123;
    Bool _t124 = I64_eq(_t122, _t123);
    (void)_t124;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t125 = I32_eq(DEREF(a), DEREF(b));
    (void)_t125;
    Bool _t126 = Bool_not(_t125);
    (void)_t126;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t127; { Bool *_hp = (Bool *)I32_gt(a, b); _t127 = *_hp; free(_hp); }
    (void)_t127;
    Bool _t128 = Bool_not(_t127);
    (void)_t128;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t128; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t129; { Bool *_hp = (Bool *)I32_lt(a, b); _t129 = *_hp; free(_hp); }
    (void)_t129;
    Bool _t130 = Bool_not(_t129);
    (void)_t130;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t130; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t131 = F32_from_i64_ext(val);
    (void)_t131;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t131; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t133 = 0;
    (void)_t133;
    I64 _t134 = 1;
    (void)_t134;
    I64 _t135 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t135;
    I64 _t136 = I64_sub(_t133, _t134);
    (void)_t136;
    ;
    ;
    Bool _t137 = I64_eq(_t135, _t136);
    (void)_t137;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t137; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t138 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t138;
    I64 _t139 = 1;
    (void)_t139;
    Bool _t140 = I64_eq(_t138, _t139);
    (void)_t140;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t140; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t141 = F32_eq(DEREF(a), DEREF(b));
    (void)_t141;
    Bool _t142 = Bool_not(_t141);
    (void)_t142;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t142; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t143; { Bool *_hp = (Bool *)F32_gt(a, b); _t143 = *_hp; free(_hp); }
    (void)_t143;
    Bool _t144 = Bool_not(_t143);
    (void)_t144;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t144; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t145; { Bool *_hp = (Bool *)F32_lt(a, b); _t145 = *_hp; free(_hp); }
    (void)_t145;
    Bool _t146 = Bool_not(_t145);
    (void)_t146;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t146; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t147 = U32_to_i64(DEREF(val));
    (void)_t147;
    Str *_t148 = I64_to_str(&(I64){_t147});
    (void)_t148;
    ;
    return _t148;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t150 = 0;
    (void)_t150;
    I64 _t151 = 1;
    (void)_t151;
    I64 _t152 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t152;
    I64 _t153 = I64_sub(_t150, _t151);
    (void)_t153;
    ;
    ;
    Bool _t154 = I64_eq(_t152, _t153);
    (void)_t154;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t154; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t155 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t155;
    I64 _t156 = 1;
    (void)_t156;
    Bool _t157 = I64_eq(_t155, _t156);
    (void)_t157;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t157; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t158 = U32_eq(DEREF(a), DEREF(b));
    (void)_t158;
    Bool _t159 = Bool_not(_t158);
    (void)_t159;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t159; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t160; { Bool *_hp = (Bool *)U32_gt(a, b); _t160 = *_hp; free(_hp); }
    (void)_t160;
    Bool _t161 = Bool_not(_t160);
    (void)_t161;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t161; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t162; { Bool *_hp = (Bool *)U32_lt(a, b); _t162 = *_hp; free(_hp); }
    (void)_t162;
    Bool _t163 = Bool_not(_t162);
    (void)_t163;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t163; return _r; }
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t164 = U64_to_str_ext(val);
    (void)_t164;
    return _t164;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t165 = U64_from_i64_ext(val);
    (void)_t165;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t165; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t167 = 0;
    (void)_t167;
    I64 _t168 = 1;
    (void)_t168;
    I64 _t169 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t169;
    I64 _t170 = I64_sub(_t167, _t168);
    (void)_t170;
    ;
    ;
    Bool _t171 = I64_eq(_t169, _t170);
    (void)_t171;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t171; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t172 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t172;
    I64 _t173 = 1;
    (void)_t173;
    Bool _t174 = I64_eq(_t172, _t173);
    (void)_t174;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t174; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t175 = U64_eq(DEREF(a), DEREF(b));
    (void)_t175;
    Bool _t176 = Bool_not(_t175);
    (void)_t176;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t176; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t177; { Bool *_hp = (Bool *)U64_gt(a, b); _t177 = *_hp; free(_hp); }
    (void)_t177;
    Bool _t178 = Bool_not(_t177);
    (void)_t178;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t178; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t179; { Bool *_hp = (Bool *)U64_lt(a, b); _t179 = *_hp; free(_hp); }
    (void)_t179;
    Bool _t180 = Bool_not(_t179);
    (void)_t180;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t180; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t217 = 0;
    (void)_t217;
    Bool _t218 = I64_eq(DEREF(val), _t217);
    (void)_t218;
    ;
    if (_t218) {
        U64 _t181 = 2;
        (void)_t181;
        U8 *buf = malloc(_t181);
        (void)buf;
        ;
        I64 _t182 = 48;
        (void)_t182;
        U64 _t183 = 1;
        (void)_t183;
        memcpy(buf, &(I64){_t182}, _t183);
        ;
        ;
        U64 *_t184 = malloc(sizeof(U64));
        *_t184 = 1;
        (void)_t184;
        void *_t185 = ptr_add(buf, DEREF(_t184));
        (void)_t185;
        I32 _t186 = 0;
        (void)_t186;
        U64 _t187 = 1;
        (void)_t187;
        memset(_t185, _t186, _t187);
        U64_delete(_t184, &(Bool){1});
        ;
        ;
        I64 _t188 = 1;
        (void)_t188;
        I64 _t189 = 1;
        (void)_t189;
        Str *_t190 = malloc(sizeof(Str));
        _t190->c_str = buf;
        _t190->count = _t188;
        _t190->cap = _t189;
        (void)_t190;
        ;
        ;
        ;
        return _t190;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t219 = 0;
    (void)_t219;
    Bool _t220; { Bool *_hp = (Bool *)I64_lt(val, &(I64){_t219}); _t220 = *_hp; free(_hp); }
    (void)_t220;
    ;
    if (_t220) {
        Bool _t191 = 1;
        (void)_t191;
        is_neg = _t191;
        ;
        I64 _t192 = 0;
        (void)_t192;
        I64 _t193 = I64_sub(_t192, DEREF(val));
        (void)_t193;
        ;
        v = _t193;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&(I64){v});
    (void)tmp;
    while (1) {
        I64 _t195 = 0;
        (void)_t195;
        Bool _wcond194; { Bool *_hp = (Bool *)I64_gt(&(I64){tmp}, &(I64){_t195}); _wcond194 = *_hp; free(_hp); }
        (void)_wcond194;
        ;
        if (_wcond194) {
        } else {
            ;
            break;
        }
        ;
        U64 _t196 = 1;
        (void)_t196;
        U64 _t197 = U64_add(ndigits, _t196);
        (void)_t197;
        ;
        ndigits = _t197;
        ;
        I64 _t198 = 10;
        (void)_t198;
        I64 _t199 = I64_div(tmp, _t198);
        (void)_t199;
        ;
        tmp = _t199;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    (void)total;
    ;
    if (is_neg) {
        U64 _t200 = 1;
        (void)_t200;
        U64 _t201 = U64_add(DEREF(total), _t200);
        (void)_t201;
        ;
        *total = _t201;
        ;
    }
    U64 _t221 = 1;
    (void)_t221;
    U64 _t222 = U64_add(DEREF(total), _t221);
    (void)_t222;
    ;
    U8 *buf = malloc(_t222);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t202 = 45;
        (void)_t202;
        U64 _t203 = 1;
        (void)_t203;
        memcpy(buf, &(I64){_t202}, _t203);
        ;
        ;
    }
    ;
    U64 _t223 = 1;
    (void)_t223;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t223);
    (void)i;
    ;
    while (1) {
        I64 _t205 = 0;
        (void)_t205;
        Bool _wcond204; { Bool *_hp = (Bool *)I64_gt(&(I64){v}, &(I64){_t205}); _wcond204 = *_hp; free(_hp); }
        (void)_wcond204;
        ;
        if (_wcond204) {
        } else {
            ;
            break;
        }
        ;
        I64 _t206 = 10;
        (void)_t206;
        I64 _t207 = I64_mod(v, _t206);
        (void)_t207;
        ;
        I64 _t208 = 48;
        (void)_t208;
        I64 _t209 = I64_add(_t207, _t208);
        (void)_t209;
        ;
        ;
        void *_t210 = ptr_add(buf, DEREF(i));
        (void)_t210;
        U8 _t211 = I64_to_u8(_t209);
        (void)_t211;
        ;
        U64 _t212 = 1;
        (void)_t212;
        memcpy(_t210, &(U8){_t211}, _t212);
        ;
        ;
        I64 _t213 = 10;
        (void)_t213;
        I64 _t214 = I64_div(v, _t213);
        (void)_t214;
        ;
        v = _t214;
        ;
        U64 _t215 = 1;
        (void)_t215;
        U64 _t216 = U64_sub(DEREF(i), _t215);
        (void)_t216;
        ;
        *i = _t216;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t224 = ptr_add(buf, DEREF(total));
    (void)_t224;
    I32 _t225 = 0;
    (void)_t225;
    U64 _t226 = 1;
    (void)_t226;
    memset(_t224, _t225, _t226);
    ;
    ;
    U64 _t227 = U64_clone(total);
    (void)_t227;
    U64 _t228 = U64_clone(total);
    (void)_t228;
    U64_delete(total, &(Bool){1});
    Str *_t229 = malloc(sizeof(Str));
    _t229->c_str = buf;
    _t229->count = _t227;
    _t229->cap = _t228;
    (void)_t229;
    ;
    ;
    return _t229;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t230 = 0;
    (void)_t230;
    I64 _t231 = I64_sub(_t230, DEREF(a));
    (void)_t231;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t231; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t234 = 0;
    (void)_t234;
    Bool _t235; { Bool *_hp = (Bool *)I64_lt(a, &(I64){_t234}); _t235 = *_hp; free(_hp); }
    (void)_t235;
    ;
    if (_t235) {
        I64 _t232 = 0;
        (void)_t232;
        I64 _t233 = I64_sub(_t232, DEREF(a));
        (void)_t233;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t233; return _r; }
    }
    ;
    I64 _t236 = I64_clone(a);
    (void)_t236;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t236; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t238 = 0;
    (void)_t238;
    I64 _t239 = 1;
    (void)_t239;
    I64 _t240 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t240;
    I64 _t241 = I64_sub(_t238, _t239);
    (void)_t241;
    ;
    ;
    Bool _t242 = I64_eq(_t240, _t241);
    (void)_t242;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t242; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t243 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t243;
    I64 _t244 = 1;
    (void)_t244;
    Bool _t245 = I64_eq(_t243, _t244);
    (void)_t245;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t245; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t246 = I64_eq(DEREF(a), DEREF(b));
    (void)_t246;
    Bool _t247 = Bool_not(_t246);
    (void)_t247;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t247; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t248; { Bool *_hp = (Bool *)I64_gt(a, b); _t248 = *_hp; free(_hp); }
    (void)_t248;
    Bool _t249 = Bool_not(_t248);
    (void)_t249;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t249; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t250; { Bool *_hp = (Bool *)I64_lt(a, b); _t250 = *_hp; free(_hp); }
    (void)_t250;
    Bool _t251 = Bool_not(_t250);
    (void)_t251;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t251; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    (void)start;
    (void)end;
    U64 _t252 = U64_clone(&(U64){start});
    (void)_t252;
    U64 _t253 = U64_clone(&(U64){end});
    (void)_t253;
    Range *_t254 = malloc(sizeof(Range));
    _t254->start = _t252;
    _t254->end = _t253;
    (void)_t254;
    ;
    ;
    return _t254;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t256; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t256 = *_hp; free(_hp); }
    (void)_t256;
    if (_t256) {
        U64 _t255 = U64_sub(self->end, self->start);
        (void)_t255;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t255; return _r; }
    }
    ;
    U64 _t257 = U64_sub(self->start, self->end);
    (void)_t257;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t257; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    (void)i;
    Bool _t259; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t259 = *_hp; free(_hp); }
    (void)_t259;
    if (_t259) {
        U64 _t258 = U64_add(self->start, i);
        (void)_t258;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t258; return _r; }
    }
    ;
    U64 _t260 = U64_sub(self->start, i);
    (void)_t260;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t260; return _r; }
}

Range * Range_clone(Range * val) {
    (void)val;
    Range *_t261 = malloc(sizeof(Range));
    _t261->start = val->start;
    _t261->end = val->end;
    (void)_t261;
    return _t261;
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
        Str *_t263 = Str_lit("true", 4ULL);
        (void)_t263;
        return _t263;
    } else {
        Str *_t264 = Str_lit("false", 5ULL);
        (void)_t264;
        return _t264;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t269 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t269;
    if (_t269) {
        I64 _t265 = 0;
        (void)_t265;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t265; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t266 = 0;
        (void)_t266;
        I64 _t267 = 1;
        (void)_t267;
        I64 _t268 = I64_sub(_t266, _t267);
        (void)_t268;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t268; return _r; }
    }
    I64 _t270 = 1;
    (void)_t270;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t270; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t272 = 0;
    (void)_t272;
    I64 _t273 = 1;
    (void)_t273;
    I64 _t274; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t274 = *_hp; free(_hp); }
    (void)_t274;
    I64 _t275 = I64_sub(_t272, _t273);
    (void)_t275;
    ;
    ;
    Bool _t276 = I64_eq(_t274, _t275);
    (void)_t276;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t276; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t277; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t277 = *_hp; free(_hp); }
    (void)_t277;
    I64 _t278 = 1;
    (void)_t278;
    Bool _t279 = I64_eq(_t277, _t278);
    (void)_t279;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t279; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t280 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t280;
    Bool _t281 = Bool_not(_t280);
    (void)_t281;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t281; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t282; { Bool *_hp = (Bool *)Bool_gt(a, b); _t282 = *_hp; free(_hp); }
    (void)_t282;
    Bool _t283 = Bool_not(_t282);
    (void)_t283;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t283; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t284; { Bool *_hp = (Bool *)Bool_lt(a, b); _t284 = *_hp; free(_hp); }
    (void)_t284;
    Bool _t285 = Bool_not(_t284);
    (void)_t285;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t285; return _r; }
}

void println(Array * parts) {
    (void)parts;
    {
        U64 *_fi286 = malloc(sizeof(U64));
        *_fi286 = 0;
        (void)_fi286;
        while (1) {
            U64 _t288; { U64 *_hp = (U64 *)Array_len(parts); _t288 = *_hp; free(_hp); }
            (void)_t288;
            Bool _wcond287; { Bool *_hp = (Bool *)U64_lt(_fi286, &(U64){_t288}); _wcond287 = *_hp; free(_hp); }
            (void)_wcond287;
            ;
            if (_wcond287) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi286);
            (void)s;
            U64 _t289 = 1;
            (void)_t289;
            U64 _t290 = U64_add(DEREF(_fi286), _t289);
            (void)_t290;
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
    (void)parts;
    {
        U64 *_fi291 = malloc(sizeof(U64));
        *_fi291 = 0;
        (void)_fi291;
        while (1) {
            U64 _t293; { U64 *_hp = (U64 *)Array_len(parts); _t293 = *_hp; free(_hp); }
            (void)_t293;
            Bool _wcond292; { Bool *_hp = (Bool *)U64_lt(_fi291, &(U64){_t293}); _wcond292 = *_hp; free(_hp); }
            (void)_wcond292;
            ;
            if (_wcond292) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi291);
            (void)s;
            U64 _t294 = 1;
            (void)_t294;
            U64 _t295 = U64_add(DEREF(_fi291), _t294);
            (void)_t295;
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
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        U64 *_fi296 = malloc(sizeof(U64));
        *_fi296 = 0;
        (void)_fi296;
        while (1) {
            U64 _t298; { U64 *_hp = (U64 *)Array_len(parts); _t298 = *_hp; free(_hp); }
            (void)_t298;
            Bool _wcond297; { Bool *_hp = (Bool *)U64_lt(_fi296, &(U64){_t298}); _wcond297 = *_hp; free(_hp); }
            (void)_wcond297;
            ;
            if (_wcond297) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi296);
            (void)s;
            U64 _t299 = 1;
            (void)_t299;
            U64 _t300 = U64_add(DEREF(_fi296), _t299);
            (void)_t300;
            ;
            *_fi296 = _t300;
            ;
            U64 _t301; { U64 *_hp = (U64 *)Str_len(s); _t301 = *_hp; free(_hp); }
            (void)_t301;
            U64 _t302 = U64_add(total, _t301);
            (void)_t302;
            ;
            total = _t302;
            ;
        }
        U64_delete(_fi296, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 *_fi303 = malloc(sizeof(U64));
        *_fi303 = 0;
        (void)_fi303;
        while (1) {
            U64 _t305; { U64 *_hp = (U64 *)Array_len(parts); _t305 = *_hp; free(_hp); }
            (void)_t305;
            Bool _wcond304; { Bool *_hp = (Bool *)U64_lt(_fi303, &(U64){_t305}); _wcond304 = *_hp; free(_hp); }
            (void)_wcond304;
            ;
            if (_wcond304) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi303);
            (void)s;
            U64 _t306 = 1;
            (void)_t306;
            U64 _t307 = U64_add(DEREF(_fi303), _t306);
            (void)_t307;
            ;
            *_fi303 = _t307;
            ;
            void *_t308 = ptr_add(buf, DEREF(offset));
            (void)_t308;
            U64 _t309; { U64 *_hp = (U64 *)Str_len(s); _t309 = *_hp; free(_hp); }
            (void)_t309;
            memcpy(_t308, s->c_str, _t309);
            ;
            U64 _t310; { U64 *_hp = (U64 *)Str_len(s); _t310 = *_hp; free(_hp); }
            (void)_t310;
            U64 _t311 = U64_add(DEREF(offset), _t310);
            (void)_t311;
            ;
            *offset = _t311;
            ;
        }
        U64_delete(_fi303, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t312 = U64_clone(&(U64){total});
    (void)_t312;
    U64 _t313 = U64_clone(&(U64){total});
    (void)_t313;
    ;
    Str *_t314 = malloc(sizeof(Str));
    _t314->c_str = buf;
    _t314->count = _t312;
    _t314->cap = _t313;
    (void)_t314;
    ;
    ;
    return _t314;
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
    I32 _t315 = 0;
    (void)_t315;
    memset(src, _t315, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t316 = 0;
        (void)_t316;
        I64 _t317 = 1;
        (void)_t317;
        I64 _t318 = I64_sub(_t316, _t317);
        (void)_t318;
        ;
        ;
        Bool _t319; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t318}); _t319 = *_hp; free(_hp); }
        (void)_t319;
        ;
        if (_t319) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t320 = 50;
        (void)_t320;
        sleep_ms(_t320);
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
        U64 _t326; { U64 *_hp = (U64 *)Array_len(args); _t326 = *_hp; free(_hp); }
        (void)_t326;
        Bool _wcond321; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t326}); _wcond321 = *_hp; free(_hp); }
        (void)_wcond321;
        ;
        if (_wcond321) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t327 = 0;
        (void)_t327;
        Bool _t328; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t327}); _t328 = *_hp; free(_hp); }
        (void)_t328;
        ;
        if (_t328) {
            Str *_t322 = Str_lit(" '", 2ULL);
            (void)_t322;
            Str *_t323 = Str_concat(cmd, _t322);
            (void)_t323;
            Str_delete(_t322, &(Bool){1});
            Str *_t324 = Str_concat(_t323, arg);
            (void)_t324;
            Str_delete(_t323, &(Bool){1});
            Str *_t325 = Str_lit("'", 1ULL);
            (void)_t325;
            cmd = Str_concat(_t324, _t325);
            Str_delete(_t324, &(Bool){1});
            Str_delete(_t325, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t329 = 1;
        (void)_t329;
        U64 _t330 = U64_add(DEREF(i), _t329);
        (void)_t330;
        ;
        *i = _t330;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t331 = Str_lit(" > ", 3ULL);
    (void)_t331;
    Str *_t332 = Str_concat(cmd, _t331);
    (void)_t332;
    Str_delete(_t331, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t333 = Str_concat(_t332, tmpf);
    (void)_t333;
    Str_delete(_t332, &(Bool){1});
    Str *_t334 = Str_lit(" 2>&1", 5ULL);
    (void)_t334;
    Str *_t335 = Str_concat(_t333, _t334);
    (void)_t335;
    Str_delete(_t333, &(Bool){1});
    Str_delete(_t334, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t335); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t335, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t336; { U64 *_hp = (U64 *)Str_size(); _t336 = *_hp; free(_hp); }
    (void)_t336;
    memcpy(output, content, _t336);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t337 = Str_lit("Str", 3ULL);
    (void)_t337;
    U64 _t338; { U64 *_hp = (U64 *)Str_size(); _t338 = *_hp; free(_hp); }
    (void)_t338;
    U64 _t339 = 3;
    (void)_t339;
    Array *_va0 = Array_new(_t337, &(U64){_t338}, &(U64){_t339});
    (void)_va0;
    Str_delete(_t337, &(Bool){1});
    ;
    ;
    U64 _t340 = 0;
    (void)_t340;
    Str *_t341 = Str_clone(loc_str);
    (void)_t341;
    Array_set(_va0, &(U64){_t340}, _t341);
    ;
    U64 _t342 = 1;
    (void)_t342;
    Str *_t343 = Str_lit(": panic: ", 9ULL);
    (void)_t343;
    Array_set(_va0, &(U64){_t342}, _t343);
    ;
    U64 _t344 = 2;
    (void)_t344;
    Str *_t345 = format(parts);
    (void)_t345;
    Array_set(_va0, &(U64){_t344}, _t345);
    ;
    println(_va0);
    I64 _t346 = 1;
    (void)_t346;
    exit(_t346);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t347 = Str_lit("Str", 3ULL);
    (void)_t347;
    U64 _t348; { U64 *_hp = (U64 *)Str_size(); _t348 = *_hp; free(_hp); }
    (void)_t348;
    U64 _t349 = 2;
    (void)_t349;
    Array *_va1 = Array_new(_t347, &(U64){_t348}, &(U64){_t349});
    (void)_va1;
    Str_delete(_t347, &(Bool){1});
    ;
    ;
    U64 _t350 = 0;
    (void)_t350;
    Str *_t351 = Str_lit("TODO: ", 6ULL);
    (void)_t351;
    Array_set(_va1, &(U64){_t350}, _t351);
    ;
    U64 _t352 = 1;
    (void)_t352;
    Str *_t353 = format(parts);
    (void)_t353;
    Array_set(_va1, &(U64){_t352}, _t353);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t354 = Str_lit("Str", 3ULL);
    (void)_t354;
    U64 _t355; { U64 *_hp = (U64 *)Str_size(); _t355 = *_hp; free(_hp); }
    (void)_t355;
    U64 _t356 = 1;
    (void)_t356;
    Array *_va2 = Array_new(_t354, &(U64){_t355}, &(U64){_t356});
    (void)_va2;
    Str_delete(_t354, &(Bool){1});
    ;
    ;
    U64 _t357 = 0;
    (void)_t357;
    Str *_t358 = Str_lit("unreachable", 11ULL);
    (void)_t358;
    Array_set(_va2, &(U64){_t357}, _t358);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t366 = Bool_not(DEREF(cond));
    (void)_t366;
    if (_t366) {
        Str *_t359 = Str_lit("Str", 3ULL);
        (void)_t359;
        U64 _t360; { U64 *_hp = (U64 *)Str_size(); _t360 = *_hp; free(_hp); }
        (void)_t360;
        U64 _t361 = 2;
        (void)_t361;
        Array *_va3 = Array_new(_t359, &(U64){_t360}, &(U64){_t361});
        (void)_va3;
        Str_delete(_t359, &(Bool){1});
        ;
        ;
        U64 _t362 = 0;
        (void)_t362;
        Str *_t363 = Str_lit("assert failed: ", 15ULL);
        (void)_t363;
        Array_set(_va3, &(U64){_t362}, _t363);
        ;
        U64 _t364 = 1;
        (void)_t364;
        Str *_t365 = format(parts);
        (void)_t365;
        Array_set(_va3, &(U64){_t364}, _t365);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t367 = 1;
    (void)_t367;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t367; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Str *_t368 = Str_lit("Str", 3ULL);
    (void)_t368;
    U64 _t369; { U64 *_hp = (U64 *)Str_size(); _t369 = *_hp; free(_hp); }
    (void)_t369;
    U64 _t370 = 0;
    (void)_t370;
    Array *_va4 = Array_new(_t368, &(U64){_t369}, &(U64){_t370});
    (void)_va4;
    Str_delete(_t368, &(Bool){1});
    ;
    ;
    Bool _t371; { Bool *_hp = (Bool *)assertm(loc_str, cond, _va4); _t371 = *_hp; free(_hp); }
    (void)_t371;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t371; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Array *_t372 = Array_clone(parts);
    (void)_t372;
    Array_delete(parts, &(Bool){1});
    Bool _t373; { Bool *_hp = (Bool *)assertm(loc_str, cond, _t372); _t373 = *_hp; free(_hp); }
    (void)_t373;
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t387; { Bool *_hp = (Bool *)I64_neq(a, b); _t387 = *_hp; free(_hp); }
    (void)_t387;
    if (_t387) {
        Str *_t374 = Str_lit("Str", 3ULL);
        (void)_t374;
        U64 _t375; { U64 *_hp = (U64 *)Str_size(); _t375 = *_hp; free(_hp); }
        (void)_t375;
        U64 _t376 = 5;
        (void)_t376;
        Array *_va5 = Array_new(_t374, &(U64){_t375}, &(U64){_t376});
        (void)_va5;
        Str_delete(_t374, &(Bool){1});
        ;
        ;
        U64 _t377 = 0;
        (void)_t377;
        Str *_t378 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t378;
        Array_set(_va5, &(U64){_t377}, _t378);
        ;
        U64 _t379 = 1;
        (void)_t379;
        Str *_t380 = I64_to_str(a);
        (void)_t380;
        Array_set(_va5, &(U64){_t379}, _t380);
        ;
        U64 _t381 = 2;
        (void)_t381;
        Str *_t382 = Str_lit("', found '", 10ULL);
        (void)_t382;
        Array_set(_va5, &(U64){_t381}, _t382);
        ;
        U64 _t383 = 3;
        (void)_t383;
        Str *_t384 = I64_to_str(b);
        (void)_t384;
        Array_set(_va5, &(U64){_t383}, _t384);
        ;
        U64 _t385 = 4;
        (void)_t385;
        Str *_t386 = Str_lit("'", 1ULL);
        (void)_t386;
        Array_set(_va5, &(U64){_t385}, _t386);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t401; { Bool *_hp = (Bool *)Str_eq(a, b); _t401 = *_hp; free(_hp); }
    (void)_t401;
    Bool _t402 = Bool_not(_t401);
    (void)_t402;
    ;
    if (_t402) {
        Str *_t388 = Str_lit("Str", 3ULL);
        (void)_t388;
        U64 _t389; { U64 *_hp = (U64 *)Str_size(); _t389 = *_hp; free(_hp); }
        (void)_t389;
        U64 _t390 = 5;
        (void)_t390;
        Array *_va6 = Array_new(_t388, &(U64){_t389}, &(U64){_t390});
        (void)_va6;
        Str_delete(_t388, &(Bool){1});
        ;
        ;
        U64 _t391 = 0;
        (void)_t391;
        Str *_t392 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t392;
        Array_set(_va6, &(U64){_t391}, _t392);
        ;
        U64 _t393 = 1;
        (void)_t393;
        Str *_t394 = Str_clone(a);
        (void)_t394;
        Array_set(_va6, &(U64){_t393}, _t394);
        ;
        U64 _t395 = 2;
        (void)_t395;
        Str *_t396 = Str_lit("', found '", 10ULL);
        (void)_t396;
        Array_set(_va6, &(U64){_t395}, _t396);
        ;
        U64 _t397 = 3;
        (void)_t397;
        Str *_t398 = Str_clone(b);
        (void)_t398;
        Array_set(_va6, &(U64){_t397}, _t398);
        ;
        U64 _t399 = 4;
        (void)_t399;
        Str *_t400 = Str_lit("'", 1ULL);
        (void)_t400;
        Array_set(_va6, &(U64){_t399}, _t400);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t403 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t403;
    U64 _t404 = U64_clone(cap);
    (void)_t404;
    U64 _t405 = U64_clone(elem_size);
    (void)_t405;
    Array *_t406 = malloc(sizeof(Array));
    _t406->data = _t403;
    _t406->cap = _t404;
    _t406->elem_size = _t405;
    { Str *_ca = Str_clone(elem_type); _t406->elem_type = *_ca; free(_ca); }
    (void)_t406;
    ;
    ;
    return _t406;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t421; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t421 = *_hp; free(_hp); }
    (void)_t421;
    if (_t421) {
        Str *_t407 = Str_lit("Str", 3ULL);
        (void)_t407;
        U64 _t408; { U64 *_hp = (U64 *)Str_size(); _t408 = *_hp; free(_hp); }
        (void)_t408;
        U64 _t409 = 5;
        (void)_t409;
        Array *_va7 = Array_new(_t407, &(U64){_t408}, &(U64){_t409});
        (void)_va7;
        Str_delete(_t407, &(Bool){1});
        ;
        ;
        U64 _t410 = 0;
        (void)_t410;
        Str *_t411 = Str_lit("Array.get: index ", 17ULL);
        (void)_t411;
        Array_set(_va7, &(U64){_t410}, _t411);
        ;
        U64 _t412 = 1;
        (void)_t412;
        Str *_t413 = U64_to_str(DEREF(i));
        (void)_t413;
        Array_set(_va7, &(U64){_t412}, _t413);
        ;
        U64 _t414 = 2;
        (void)_t414;
        Str *_t415 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t415;
        Array_set(_va7, &(U64){_t414}, _t415);
        ;
        U64 _t416 = 3;
        (void)_t416;
        Str *_t417 = U64_to_str(self->cap);
        (void)_t417;
        Array_set(_va7, &(U64){_t416}, _t417);
        ;
        U64 _t418 = 4;
        (void)_t418;
        Str *_t419 = Str_lit(")", 1ULL);
        (void)_t419;
        Array_set(_va7, &(U64){_t418}, _t419);
        ;
        Str *_t420 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t420;
        panic(_t420, _va7);
        Str_delete(_t420, &(Bool){1});
    }
    ;
    U64 *_t422 = malloc(sizeof(U64)); *_t422 = U64_mul(DEREF(i), self->elem_size);
    (void)_t422;
    void *_t423 = ptr_add(self->data, DEREF(_t422));
    (void)_t423;
    U64_delete(_t422, &(Bool){1});
    return _t423;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t438; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t438 = *_hp; free(_hp); }
    (void)_t438;
    if (_t438) {
        Str *_t424 = Str_lit("Str", 3ULL);
        (void)_t424;
        U64 _t425; { U64 *_hp = (U64 *)Str_size(); _t425 = *_hp; free(_hp); }
        (void)_t425;
        U64 _t426 = 5;
        (void)_t426;
        Array *_va8 = Array_new(_t424, &(U64){_t425}, &(U64){_t426});
        (void)_va8;
        Str_delete(_t424, &(Bool){1});
        ;
        ;
        U64 _t427 = 0;
        (void)_t427;
        Str *_t428 = Str_lit("Array.set: index ", 17ULL);
        (void)_t428;
        Array_set(_va8, &(U64){_t427}, _t428);
        ;
        U64 _t429 = 1;
        (void)_t429;
        Str *_t430 = U64_to_str(DEREF(i));
        (void)_t430;
        Array_set(_va8, &(U64){_t429}, _t430);
        ;
        U64 _t431 = 2;
        (void)_t431;
        Str *_t432 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t432;
        Array_set(_va8, &(U64){_t431}, _t432);
        ;
        U64 _t433 = 3;
        (void)_t433;
        Str *_t434 = U64_to_str(self->cap);
        (void)_t434;
        Array_set(_va8, &(U64){_t433}, _t434);
        ;
        U64 _t435 = 4;
        (void)_t435;
        Str *_t436 = Str_lit(")", 1ULL);
        (void)_t436;
        Array_set(_va8, &(U64){_t435}, _t436);
        ;
        Str *_t437 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t437;
        panic(_t437, _va8);
        Str_delete(_t437, &(Bool){1});
    }
    ;
    U64 *_t439 = malloc(sizeof(U64)); *_t439 = U64_mul(DEREF(i), self->elem_size);
    (void)_t439;
    void *_t440 = ptr_add(self->data, DEREF(_t439));
    (void)_t440;
    Bool _t441 = 0;
    (void)_t441;
    dyn_call_delete(&self->elem_type, _t440, &(Bool){_t441});
    U64_delete(_t439, &(Bool){1});
    ;
    U64 *_t442 = malloc(sizeof(U64)); *_t442 = U64_mul(DEREF(i), self->elem_size);
    (void)_t442;
    void *_t443 = ptr_add(self->data, DEREF(_t442));
    (void)_t443;
    memcpy(_t443, val, self->elem_size);
    U64_delete(_t442, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi444 = 0;
        (void)_fi444;
        while (1) {
            U64 _t446 = 0;
            (void)_t446;
            Range *_t447 = Range_new(_t446, self->cap);
            (void)_t447;
            ;
            U64 _t448; { U64 *_hp = (U64 *)Range_len(_t447); _t448 = *_hp; free(_hp); }
            (void)_t448;
            Range_delete(_t447, &(Bool){1});
            Bool _wcond445; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi444}, &(U64){_t448}); _wcond445 = *_hp; free(_hp); }
            (void)_wcond445;
            ;
            if (_wcond445) {
            } else {
                ;
                break;
            }
            ;
            U64 _t449 = 0;
            (void)_t449;
            Range *_t450 = Range_new(_t449, self->cap);
            (void)_t450;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t450, _fi444); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t450, &(Bool){1});
            U64 _t451 = 1;
            (void)_t451;
            U64 _t452 = U64_add(_fi444, _t451);
            (void)_t452;
            ;
            _fi444 = _t452;
            ;
            U64 *_t453 = malloc(sizeof(U64)); *_t453 = U64_mul(i, self->elem_size);
            (void)_t453;
            ;
            void *_t454 = ptr_add(self->data, DEREF(_t453));
            (void)_t454;
            Bool _t455 = 0;
            (void)_t455;
            dyn_call_delete(&self->elem_type, _t454, &(Bool){_t455});
            U64_delete(_t453, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t456 = 0;
    (void)_t456;
    Str_delete(&self->elem_type, &(Bool){_t456});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t470 = U64_mul(self->cap, self->elem_size);
    (void)_t470;
    U8 *new_data = malloc(_t470);
    (void)new_data;
    ;
    {
        U64 _fi457 = 0;
        (void)_fi457;
        while (1) {
            U64 _t459 = 0;
            (void)_t459;
            Range *_t460 = Range_new(_t459, self->cap);
            (void)_t460;
            ;
            U64 _t461; { U64 *_hp = (U64 *)Range_len(_t460); _t461 = *_hp; free(_hp); }
            (void)_t461;
            Range_delete(_t460, &(Bool){1});
            Bool _wcond458; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi457}, &(U64){_t461}); _wcond458 = *_hp; free(_hp); }
            (void)_wcond458;
            ;
            if (_wcond458) {
            } else {
                ;
                break;
            }
            ;
            U64 _t462 = 0;
            (void)_t462;
            Range *_t463 = Range_new(_t462, self->cap);
            (void)_t463;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t463, _fi457); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t463, &(Bool){1});
            U64 _t464 = 1;
            (void)_t464;
            U64 _t465 = U64_add(_fi457, _t464);
            (void)_t465;
            ;
            _fi457 = _t465;
            ;
            U64 *_t466 = malloc(sizeof(U64)); *_t466 = U64_mul(i, self->elem_size);
            (void)_t466;
            void *_t467 = ptr_add(self->data, DEREF(_t466));
            (void)_t467;
            void *cloned = dyn_call_clone(&self->elem_type, _t467);
            (void)cloned;
            U64_delete(_t466, &(Bool){1});
            U64 *_t468 = malloc(sizeof(U64)); *_t468 = U64_mul(i, self->elem_size);
            (void)_t468;
            ;
            void *_t469 = ptr_add(new_data, DEREF(_t468));
            (void)_t469;
            memcpy(_t469, cloned, self->elem_size);
            U64_delete(_t468, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t471 = malloc(sizeof(Array));
    _t471->data = new_data;
    _t471->cap = self->cap;
    _t471->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t471->elem_type = *_ca; free(_ca); }
    (void)_t471;
    return _t471;
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
    Bool _t485; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t485 = *_hp; free(_hp); }
    (void)_t485;
    Bool _t486 = Bool_not(_t485);
    (void)_t486;
    ;
    if (_t486) {
        Bool _t483 = dyn_has_cmp(key_type);
        (void)_t483;
        Bool _t484 = Bool_not(_t483);
        (void)_t484;
        ;
        if (_t484) {
            Str *_t473 = Str_lit("Str", 3ULL);
            (void)_t473;
            U64 _t474; { U64 *_hp = (U64 *)Str_size(); _t474 = *_hp; free(_hp); }
            (void)_t474;
            U64 _t475 = 3;
            (void)_t475;
            Array *_va9 = Array_new(_t473, &(U64){_t474}, &(U64){_t475});
            (void)_va9;
            Str_delete(_t473, &(Bool){1});
            ;
            ;
            U64 _t476 = 0;
            (void)_t476;
            Str *_t477 = Str_lit("Map.new: type ", 14ULL);
            (void)_t477;
            Array_set(_va9, &(U64){_t476}, _t477);
            ;
            U64 _t478 = 1;
            (void)_t478;
            Str *_t479 = Str_clone(key_type);
            (void)_t479;
            Array_set(_va9, &(U64){_t478}, _t479);
            ;
            U64 _t480 = 2;
            (void)_t480;
            Str *_t481 = Str_lit(" must implement cmp", 19ULL);
            (void)_t481;
            Array_set(_va9, &(U64){_t480}, _t481);
            ;
            Str *_t482 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t482;
            panic(_t482, _va9);
            Str_delete(_t482, &(Bool){1});
        }
        ;
    }
    ;
    void *_t487 = malloc(DEREF(key_size));
    (void)_t487;
    void *_t488 = malloc(DEREF(val_size));
    (void)_t488;
    U64 _t489 = 0;
    (void)_t489;
    I64 _t490 = 1;
    (void)_t490;
    U64 _t491 = U64_clone(key_size);
    (void)_t491;
    U64 _t492 = U64_clone(val_size);
    (void)_t492;
    Map *_t493 = malloc(sizeof(Map));
    _t493->key_data = _t487;
    _t493->val_data = _t488;
    _t493->count = _t489;
    _t493->cap = _t490;
    _t493->key_size = _t491;
    { Str *_ca = Str_clone(key_type); _t493->key_type = *_ca; free(_ca); }
    _t493->val_size = _t492;
    { Str *_ca = Str_clone(val_type); _t493->val_type = *_ca; free(_ca); }
    (void)_t493;
    ;
    ;
    ;
    ;
    return _t493;
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
        Bool _wcond494; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond494 = *_hp; free(_hp); }
        (void)_wcond494;
        if (_wcond494) {
        } else {
            ;
            break;
        }
        ;
        U64 _t501 = U64_sub(hi, lo);
        (void)_t501;
        U64 _t502 = 2;
        (void)_t502;
        U64 _t503 = U64_div(_t501, _t502);
        (void)_t503;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t503);
        (void)mid;
        ;
        U64 *_t504 = malloc(sizeof(U64)); *_t504 = U64_mul(DEREF(mid), self->key_size);
        (void)_t504;
        void *_t505 = ptr_add(self->key_data, DEREF(_t504));
        (void)_t505;
        I64 *c = dyn_call_cmp(&self->key_type, _t505, key);
        (void)c;
        U64_delete(_t504, &(Bool){1});
        I64 _t506 = 0;
        (void)_t506;
        Bool _t507; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t506}); _t507 = *_hp; free(_hp); }
        (void)_t507;
        ;
        if (_t507) {
            U64 _t495 = 1;
            (void)_t495;
            U64 _t496 = U64_add(DEREF(mid), _t495);
            (void)_t496;
            ;
            lo = _t496;
            ;
        } else {
            I64 _t499 = 0;
            (void)_t499;
            Bool _t500; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t499}); _t500 = *_hp; free(_hp); }
            (void)_t500;
            ;
            if (_t500) {
                U64 _t497 = U64_clone(mid);
                (void)_t497;
                hi = _t497;
                ;
            } else {
                Bool _t498 = 1;
                (void)_t498;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t498; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t508 = 0;
    (void)_t508;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t508; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond509; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond509 = *_hp; free(_hp); }
        (void)_wcond509;
        if (_wcond509) {
        } else {
            ;
            break;
        }
        ;
        U64 _t517 = U64_sub(hi, lo);
        (void)_t517;
        U64 _t518 = 2;
        (void)_t518;
        U64 _t519 = U64_div(_t517, _t518);
        (void)_t519;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t519);
        (void)mid;
        ;
        U64 *_t520 = malloc(sizeof(U64)); *_t520 = U64_mul(DEREF(mid), self->key_size);
        (void)_t520;
        void *_t521 = ptr_add(self->key_data, DEREF(_t520));
        (void)_t521;
        I64 *c = dyn_call_cmp(&self->key_type, _t521, key);
        (void)c;
        U64_delete(_t520, &(Bool){1});
        I64 _t522 = 0;
        (void)_t522;
        Bool _t523; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t522}); _t523 = *_hp; free(_hp); }
        (void)_t523;
        ;
        if (_t523) {
            U64 _t510 = 1;
            (void)_t510;
            U64 _t511 = U64_add(DEREF(mid), _t510);
            (void)_t511;
            ;
            lo = _t511;
            ;
        } else {
            I64 _t515 = 0;
            (void)_t515;
            Bool _t516; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t515}); _t516 = *_hp; free(_hp); }
            (void)_t516;
            ;
            if (_t516) {
                U64 _t512 = U64_clone(mid);
                (void)_t512;
                hi = _t512;
                ;
            } else {
                U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(DEREF(mid), self->val_size);
                (void)_t513;
                void *_t514 = ptr_add(self->val_data, DEREF(_t513));
                (void)_t514;
                U64_delete(_t513, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t514;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t524 = Str_lit("Str", 3ULL);
    (void)_t524;
    U64 _t525; { U64 *_hp = (U64 *)Str_size(); _t525 = *_hp; free(_hp); }
    (void)_t525;
    U64 _t526 = 1;
    (void)_t526;
    Array *_va10 = Array_new(_t524, &(U64){_t525}, &(U64){_t526});
    (void)_va10;
    Str_delete(_t524, &(Bool){1});
    ;
    ;
    U64 _t527 = 0;
    (void)_t527;
    Str *_t528 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t528;
    Array_set(_va10, &(U64){_t527}, _t528);
    ;
    Str *_t529 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t529;
    panic(_t529, _va10);
    Str_delete(_t529, &(Bool){1});
    U64 *_t530 = malloc(sizeof(U64));
    *_t530 = 0;
    (void)_t530;
    void *_t531 = ptr_add(self->val_data, DEREF(_t530));
    (void)_t531;
    U64_delete(_t530, &(Bool){1});
    return _t531;
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
        Bool _wcond532; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond532 = *_hp; free(_hp); }
        (void)_wcond532;
        if (_wcond532) {
        } else {
            ;
            break;
        }
        ;
        U64 _t541 = U64_sub(hi, lo);
        (void)_t541;
        U64 _t542 = 2;
        (void)_t542;
        U64 _t543 = U64_div(_t541, _t542);
        (void)_t543;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t543);
        (void)mid;
        ;
        U64 *_t544 = malloc(sizeof(U64)); *_t544 = U64_mul(DEREF(mid), self->key_size);
        (void)_t544;
        void *_t545 = ptr_add(self->key_data, DEREF(_t544));
        (void)_t545;
        I64 *c = dyn_call_cmp(&self->key_type, _t545, key);
        (void)c;
        U64_delete(_t544, &(Bool){1});
        I64 _t546 = 0;
        (void)_t546;
        Bool _t547; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t546}); _t547 = *_hp; free(_hp); }
        (void)_t547;
        ;
        if (_t547) {
            U64 _t533 = 1;
            (void)_t533;
            U64 _t534 = U64_add(DEREF(mid), _t533);
            (void)_t534;
            ;
            lo = _t534;
            ;
        } else {
            I64 _t539 = 0;
            (void)_t539;
            Bool _t540; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t539}); _t540 = *_hp; free(_hp); }
            (void)_t540;
            ;
            if (_t540) {
                U64 _t535 = U64_clone(mid);
                (void)_t535;
                hi = _t535;
                ;
            } else {
                Bool _t536 = 1;
                (void)_t536;
                found = _t536;
                ;
                U64 _t537 = U64_clone(mid);
                (void)_t537;
                lo = _t537;
                ;
                U64 _t538 = U64_clone(mid);
                (void)_t538;
                hi = _t538;
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
        Bool _t552; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t552 = *_hp; free(_hp); }
        (void)_t552;
        Bool _t553 = Bool_not(_t552);
        (void)_t553;
        ;
        if (_t553) {
            Bool _t548 = 0;
            (void)_t548;
            dyn_call_delete(&self->key_type, key, &(Bool){_t548});
            ;
        }
        ;
        free(key);
        Bool _t554; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t554 = *_hp; free(_hp); }
        (void)_t554;
        Bool _t555 = Bool_not(_t554);
        (void)_t555;
        ;
        if (_t555) {
            U64 *_t549 = malloc(sizeof(U64)); *_t549 = U64_mul(lo, self->val_size);
            (void)_t549;
            void *_t550 = ptr_add(self->val_data, DEREF(_t549));
            (void)_t550;
            Bool _t551 = 0;
            (void)_t551;
            dyn_call_delete(&self->val_type, _t550, &(Bool){_t551});
            U64_delete(_t549, &(Bool){1});
            ;
        }
        ;
        U64 *_t556 = malloc(sizeof(U64)); *_t556 = U64_mul(lo, self->val_size);
        (void)_t556;
        void *_t557 = ptr_add(self->val_data, DEREF(_t556));
        (void)_t557;
        memcpy(_t557, val, self->val_size);
        U64_delete(_t556, &(Bool){1});
        free(val);
    } else {
        Bool _t564 = U64_eq(self->count, self->cap);
        (void)_t564;
        if (_t564) {
            U64 _t558 = 2;
            (void)_t558;
            U64 new_cap = U64_mul(self->cap, _t558);
            (void)new_cap;
            ;
            U64 _t559 = U64_mul(new_cap, self->key_size);
            (void)_t559;
            void *_t560 = realloc(self->key_data, _t559);
            (void)_t560;
            ;
            self->key_data = _t560;
            U64 _t561 = U64_mul(new_cap, self->val_size);
            (void)_t561;
            void *_t562 = realloc(self->val_data, _t561);
            (void)_t562;
            ;
            self->val_data = _t562;
            U64 _t563 = U64_clone(&(U64){new_cap});
            (void)_t563;
            ;
            self->cap = _t563;
            ;
        }
        ;
        U64 _t565 = 1;
        (void)_t565;
        U64 _t566 = U64_add(lo, _t565);
        (void)_t566;
        ;
        U64 *_t567 = malloc(sizeof(U64)); *_t567 = U64_mul(_t566, self->key_size);
        (void)_t567;
        ;
        U64 *_t568 = malloc(sizeof(U64)); *_t568 = U64_mul(lo, self->key_size);
        (void)_t568;
        U64 _t569 = U64_sub(self->count, lo);
        (void)_t569;
        void *_t570 = ptr_add(self->key_data, DEREF(_t567));
        (void)_t570;
        void *_t571 = ptr_add(self->key_data, DEREF(_t568));
        (void)_t571;
        U64 _t572 = U64_mul(_t569, self->key_size);
        (void)_t572;
        ;
        memmove(_t570, _t571, _t572);
        U64_delete(_t567, &(Bool){1});
        U64_delete(_t568, &(Bool){1});
        ;
        U64 _t573 = 1;
        (void)_t573;
        U64 _t574 = U64_add(lo, _t573);
        (void)_t574;
        ;
        U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(_t574, self->val_size);
        (void)_t575;
        ;
        U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_mul(lo, self->val_size);
        (void)_t576;
        U64 _t577 = U64_sub(self->count, lo);
        (void)_t577;
        void *_t578 = ptr_add(self->val_data, DEREF(_t575));
        (void)_t578;
        void *_t579 = ptr_add(self->val_data, DEREF(_t576));
        (void)_t579;
        U64 _t580 = U64_mul(_t577, self->val_size);
        (void)_t580;
        ;
        memmove(_t578, _t579, _t580);
        U64_delete(_t575, &(Bool){1});
        U64_delete(_t576, &(Bool){1});
        ;
        U64 *_t581 = malloc(sizeof(U64)); *_t581 = U64_mul(lo, self->key_size);
        (void)_t581;
        void *_t582 = ptr_add(self->key_data, DEREF(_t581));
        (void)_t582;
        memcpy(_t582, key, self->key_size);
        U64_delete(_t581, &(Bool){1});
        U64 *_t583 = malloc(sizeof(U64)); *_t583 = U64_mul(lo, self->val_size);
        (void)_t583;
        void *_t584 = ptr_add(self->val_data, DEREF(_t583));
        (void)_t584;
        memcpy(_t584, val, self->val_size);
        U64_delete(_t583, &(Bool){1});
        free(key);
        free(val);
        U64 _t585 = 1;
        (void)_t585;
        U64 _t586 = U64_add(self->count, _t585);
        (void)_t586;
        ;
        self->count = _t586;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t613; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t613 = *_hp; free(_hp); }
    (void)_t613;
    Bool _t614 = Bool_not(_t613);
    (void)_t614;
    ;
    if (_t614) {
        {
            U64 _fi587 = 0;
            (void)_fi587;
            while (1) {
                U64 _t589 = 0;
                (void)_t589;
                Range *_t590 = Range_new(_t589, self->count);
                (void)_t590;
                ;
                U64 _t591; { U64 *_hp = (U64 *)Range_len(_t590); _t591 = *_hp; free(_hp); }
                (void)_t591;
                Range_delete(_t590, &(Bool){1});
                Bool _wcond588; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi587}, &(U64){_t591}); _wcond588 = *_hp; free(_hp); }
                (void)_wcond588;
                ;
                if (_wcond588) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t592 = 0;
                (void)_t592;
                Range *_t593 = Range_new(_t592, self->count);
                (void)_t593;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t593, _fi587); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t593, &(Bool){1});
                U64 _t594 = 1;
                (void)_t594;
                U64 _t595 = U64_add(_fi587, _t594);
                (void)_t595;
                ;
                _fi587 = _t595;
                ;
                U64 *_t596 = malloc(sizeof(U64)); *_t596 = U64_mul(i, self->key_size);
                (void)_t596;
                ;
                void *_t597 = ptr_add(self->key_data, DEREF(_t596));
                (void)_t597;
                Bool _t598 = 0;
                (void)_t598;
                dyn_call_delete(&self->key_type, _t597, &(Bool){_t598});
                U64_delete(_t596, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t615; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t615 = *_hp; free(_hp); }
    (void)_t615;
    Bool _t616 = Bool_not(_t615);
    (void)_t616;
    ;
    if (_t616) {
        {
            U64 _fi599 = 0;
            (void)_fi599;
            while (1) {
                U64 _t601 = 0;
                (void)_t601;
                Range *_t602 = Range_new(_t601, self->count);
                (void)_t602;
                ;
                U64 _t603; { U64 *_hp = (U64 *)Range_len(_t602); _t603 = *_hp; free(_hp); }
                (void)_t603;
                Range_delete(_t602, &(Bool){1});
                Bool _wcond600; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi599}, &(U64){_t603}); _wcond600 = *_hp; free(_hp); }
                (void)_wcond600;
                ;
                if (_wcond600) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t604 = 0;
                (void)_t604;
                Range *_t605 = Range_new(_t604, self->count);
                (void)_t605;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t605, _fi599); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t605, &(Bool){1});
                U64 _t606 = 1;
                (void)_t606;
                U64 _t607 = U64_add(_fi599, _t606);
                (void)_t607;
                ;
                _fi599 = _t607;
                ;
                U64 *_t608 = malloc(sizeof(U64)); *_t608 = U64_mul(i, self->val_size);
                (void)_t608;
                ;
                void *_t609 = ptr_add(self->val_data, DEREF(_t608));
                (void)_t609;
                Bool _t610 = 0;
                (void)_t610;
                dyn_call_delete(&self->val_type, _t609, &(Bool){_t610});
                U64_delete(_t608, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t617; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t617 = *_hp; free(_hp); }
    (void)_t617;
    Bool _t618 = Bool_not(_t617);
    (void)_t618;
    ;
    if (_t618) {
        Bool _t611 = 0;
        (void)_t611;
        Str_delete(&self->key_type, &(Bool){_t611});
        ;
    }
    ;
    Bool _t619; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t619 = *_hp; free(_hp); }
    (void)_t619;
    Bool _t620 = Bool_not(_t619);
    (void)_t620;
    ;
    if (_t620) {
        Bool _t612 = 0;
        (void)_t612;
        Str_delete(&self->val_type, &(Bool){_t612});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t638 = U64_mul(self->cap, self->key_size);
    (void)_t638;
    U8 *new_keys = malloc(_t638);
    (void)new_keys;
    ;
    U64 _t639 = U64_mul(self->cap, self->val_size);
    (void)_t639;
    U8 *new_vals = malloc(_t639);
    (void)new_vals;
    ;
    {
        U64 _fi621 = 0;
        (void)_fi621;
        while (1) {
            U64 _t623 = 0;
            (void)_t623;
            Range *_t624 = Range_new(_t623, self->count);
            (void)_t624;
            ;
            U64 _t625; { U64 *_hp = (U64 *)Range_len(_t624); _t625 = *_hp; free(_hp); }
            (void)_t625;
            Range_delete(_t624, &(Bool){1});
            Bool _wcond622; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi621}, &(U64){_t625}); _wcond622 = *_hp; free(_hp); }
            (void)_wcond622;
            ;
            if (_wcond622) {
            } else {
                ;
                break;
            }
            ;
            U64 _t626 = 0;
            (void)_t626;
            Range *_t627 = Range_new(_t626, self->count);
            (void)_t627;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t627, _fi621); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t627, &(Bool){1});
            U64 _t628 = 1;
            (void)_t628;
            U64 _t629 = U64_add(_fi621, _t628);
            (void)_t629;
            ;
            _fi621 = _t629;
            ;
            U64 *_t630 = malloc(sizeof(U64)); *_t630 = U64_mul(i, self->key_size);
            (void)_t630;
            void *_t631 = ptr_add(self->key_data, DEREF(_t630));
            (void)_t631;
            void *ck = dyn_call_clone(&self->key_type, _t631);
            (void)ck;
            U64_delete(_t630, &(Bool){1});
            U64 *_t632 = malloc(sizeof(U64)); *_t632 = U64_mul(i, self->key_size);
            (void)_t632;
            void *_t633 = ptr_add(new_keys, DEREF(_t632));
            (void)_t633;
            memcpy(_t633, ck, self->key_size);
            U64_delete(_t632, &(Bool){1});
            free(ck);
            U64 *_t634 = malloc(sizeof(U64)); *_t634 = U64_mul(i, self->val_size);
            (void)_t634;
            void *_t635 = ptr_add(self->val_data, DEREF(_t634));
            (void)_t635;
            void *cv = dyn_call_clone(&self->val_type, _t635);
            (void)cv;
            U64_delete(_t634, &(Bool){1});
            U64 *_t636 = malloc(sizeof(U64)); *_t636 = U64_mul(i, self->val_size);
            (void)_t636;
            ;
            void *_t637 = ptr_add(new_vals, DEREF(_t636));
            (void)_t637;
            memcpy(_t637, cv, self->val_size);
            U64_delete(_t636, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t640 = malloc(sizeof(Map));
    _t640->key_data = new_keys;
    _t640->val_data = new_vals;
    _t640->count = self->count;
    _t640->cap = self->cap;
    _t640->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t640->key_type = *_ca; free(_ca); }
    _t640->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t640->val_type = *_ca; free(_ca); }
    (void)_t640;
    return _t640;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t654; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t654 = *_hp; free(_hp); }
    (void)_t654;
    Bool _t655 = Bool_not(_t654);
    (void)_t655;
    ;
    if (_t655) {
        Bool _t652 = dyn_has_cmp(elem_type);
        (void)_t652;
        Bool _t653 = Bool_not(_t652);
        (void)_t653;
        ;
        if (_t653) {
            Str *_t642 = Str_lit("Str", 3ULL);
            (void)_t642;
            U64 _t643; { U64 *_hp = (U64 *)Str_size(); _t643 = *_hp; free(_hp); }
            (void)_t643;
            U64 _t644 = 3;
            (void)_t644;
            Array *_va11 = Array_new(_t642, &(U64){_t643}, &(U64){_t644});
            (void)_va11;
            Str_delete(_t642, &(Bool){1});
            ;
            ;
            U64 _t645 = 0;
            (void)_t645;
            Str *_t646 = Str_lit("Set.new: type ", 14ULL);
            (void)_t646;
            Array_set(_va11, &(U64){_t645}, _t646);
            ;
            U64 _t647 = 1;
            (void)_t647;
            Str *_t648 = Str_clone(elem_type);
            (void)_t648;
            Array_set(_va11, &(U64){_t647}, _t648);
            ;
            U64 _t649 = 2;
            (void)_t649;
            Str *_t650 = Str_lit(" must implement cmp", 19ULL);
            (void)_t650;
            Array_set(_va11, &(U64){_t649}, _t650);
            ;
            Str *_t651 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t651;
            panic(_t651, _va11);
            Str_delete(_t651, &(Bool){1});
        }
        ;
    }
    ;
    void *_t656 = malloc(DEREF(elem_size));
    (void)_t656;
    U64 _t657 = 0;
    (void)_t657;
    I64 _t658 = 1;
    (void)_t658;
    U64 _t659 = U64_clone(elem_size);
    (void)_t659;
    Set *_t660 = malloc(sizeof(Set));
    _t660->data = _t656;
    _t660->count = _t657;
    _t660->cap = _t658;
    _t660->elem_size = _t659;
    { Str *_ca = Str_clone(elem_type); _t660->elem_type = *_ca; free(_ca); }
    (void)_t660;
    ;
    ;
    ;
    return _t660;
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
        Bool _wcond661; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond661 = *_hp; free(_hp); }
        (void)_wcond661;
        if (_wcond661) {
        } else {
            ;
            break;
        }
        ;
        U64 _t668 = U64_sub(hi, lo);
        (void)_t668;
        U64 _t669 = 2;
        (void)_t669;
        U64 _t670 = U64_div(_t668, _t669);
        (void)_t670;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t670);
        (void)mid;
        ;
        U64 *_t671 = malloc(sizeof(U64)); *_t671 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t671;
        void *_t672 = ptr_add(self->data, DEREF(_t671));
        (void)_t672;
        I64 *c = dyn_call_cmp(&self->elem_type, _t672, val);
        (void)c;
        U64_delete(_t671, &(Bool){1});
        I64 _t673 = 0;
        (void)_t673;
        Bool _t674; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t673}); _t674 = *_hp; free(_hp); }
        (void)_t674;
        ;
        if (_t674) {
            U64 _t662 = 1;
            (void)_t662;
            U64 _t663 = U64_add(DEREF(mid), _t662);
            (void)_t663;
            ;
            lo = _t663;
            ;
        } else {
            I64 _t666 = 0;
            (void)_t666;
            Bool _t667; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t666}); _t667 = *_hp; free(_hp); }
            (void)_t667;
            ;
            if (_t667) {
                U64 _t664 = U64_clone(mid);
                (void)_t664;
                hi = _t664;
                ;
            } else {
                Bool _t665 = 1;
                (void)_t665;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t665; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t675 = 0;
    (void)_t675;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t675; return _r; }
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
        Bool _wcond676; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond676 = *_hp; free(_hp); }
        (void)_wcond676;
        if (_wcond676) {
        } else {
            ;
            break;
        }
        ;
        U64 _t685 = U64_sub(hi, lo);
        (void)_t685;
        U64 _t686 = 2;
        (void)_t686;
        U64 _t687 = U64_div(_t685, _t686);
        (void)_t687;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t687);
        (void)mid;
        ;
        U64 *_t688 = malloc(sizeof(U64)); *_t688 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t688;
        void *_t689 = ptr_add(self->data, DEREF(_t688));
        (void)_t689;
        I64 *c = dyn_call_cmp(&self->elem_type, _t689, val);
        (void)c;
        U64_delete(_t688, &(Bool){1});
        I64 _t690 = 0;
        (void)_t690;
        Bool _t691; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t690}); _t691 = *_hp; free(_hp); }
        (void)_t691;
        ;
        if (_t691) {
            U64 _t677 = 1;
            (void)_t677;
            U64 _t678 = U64_add(DEREF(mid), _t677);
            (void)_t678;
            ;
            lo = _t678;
            ;
        } else {
            I64 _t683 = 0;
            (void)_t683;
            Bool _t684; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t683}); _t684 = *_hp; free(_hp); }
            (void)_t684;
            ;
            if (_t684) {
                U64 _t679 = U64_clone(mid);
                (void)_t679;
                hi = _t679;
                ;
            } else {
                Bool _t680 = 1;
                (void)_t680;
                found = _t680;
                ;
                U64 _t681 = U64_clone(mid);
                (void)_t681;
                lo = _t681;
                ;
                U64 _t682 = U64_clone(mid);
                (void)_t682;
                hi = _t682;
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
        Bool _t693; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t693 = *_hp; free(_hp); }
        (void)_t693;
        Bool _t694 = Bool_not(_t693);
        (void)_t694;
        ;
        if (_t694) {
            Bool _t692 = 0;
            (void)_t692;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t692});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t699 = U64_eq(self->count, self->cap);
        (void)_t699;
        if (_t699) {
            U64 _t695 = 2;
            (void)_t695;
            U64 new_cap = U64_mul(self->cap, _t695);
            (void)new_cap;
            ;
            U64 _t696 = U64_mul(new_cap, self->elem_size);
            (void)_t696;
            void *_t697 = realloc(self->data, _t696);
            (void)_t697;
            ;
            self->data = _t697;
            U64 _t698 = U64_clone(&(U64){new_cap});
            (void)_t698;
            ;
            self->cap = _t698;
            ;
        }
        ;
        U64 _t700 = 1;
        (void)_t700;
        U64 _t701 = U64_add(lo, _t700);
        (void)_t701;
        ;
        U64 *_t702 = malloc(sizeof(U64)); *_t702 = U64_mul(_t701, self->elem_size);
        (void)_t702;
        ;
        U64 *_t703 = malloc(sizeof(U64)); *_t703 = U64_mul(lo, self->elem_size);
        (void)_t703;
        U64 _t704 = U64_sub(self->count, lo);
        (void)_t704;
        void *_t705 = ptr_add(self->data, DEREF(_t702));
        (void)_t705;
        void *_t706 = ptr_add(self->data, DEREF(_t703));
        (void)_t706;
        U64 _t707 = U64_mul(_t704, self->elem_size);
        (void)_t707;
        ;
        memmove(_t705, _t706, _t707);
        U64_delete(_t702, &(Bool){1});
        U64_delete(_t703, &(Bool){1});
        ;
        U64 *_t708 = malloc(sizeof(U64)); *_t708 = U64_mul(lo, self->elem_size);
        (void)_t708;
        void *_t709 = ptr_add(self->data, DEREF(_t708));
        (void)_t709;
        memcpy(_t709, val, self->elem_size);
        U64_delete(_t708, &(Bool){1});
        free(val);
        U64 _t710 = 1;
        (void)_t710;
        U64 _t711 = U64_add(self->count, _t710);
        (void)_t711;
        ;
        self->count = _t711;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t725; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t725 = *_hp; free(_hp); }
    (void)_t725;
    Bool _t726 = Bool_not(_t725);
    (void)_t726;
    ;
    if (_t726) {
        {
            U64 _fi712 = 0;
            (void)_fi712;
            while (1) {
                U64 _t714 = 0;
                (void)_t714;
                Range *_t715 = Range_new(_t714, self->count);
                (void)_t715;
                ;
                U64 _t716; { U64 *_hp = (U64 *)Range_len(_t715); _t716 = *_hp; free(_hp); }
                (void)_t716;
                Range_delete(_t715, &(Bool){1});
                Bool _wcond713; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi712}, &(U64){_t716}); _wcond713 = *_hp; free(_hp); }
                (void)_wcond713;
                ;
                if (_wcond713) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t717 = 0;
                (void)_t717;
                Range *_t718 = Range_new(_t717, self->count);
                (void)_t718;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t718, _fi712); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t718, &(Bool){1});
                U64 _t719 = 1;
                (void)_t719;
                U64 _t720 = U64_add(_fi712, _t719);
                (void)_t720;
                ;
                _fi712 = _t720;
                ;
                U64 *_t721 = malloc(sizeof(U64)); *_t721 = U64_mul(i, self->elem_size);
                (void)_t721;
                ;
                void *_t722 = ptr_add(self->data, DEREF(_t721));
                (void)_t722;
                Bool _t723 = 0;
                (void)_t723;
                dyn_call_delete(&self->elem_type, _t722, &(Bool){_t723});
                U64_delete(_t721, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t727; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t727 = *_hp; free(_hp); }
    (void)_t727;
    Bool _t728 = Bool_not(_t727);
    (void)_t728;
    ;
    if (_t728) {
        Bool _t724 = 0;
        (void)_t724;
        Str_delete(&self->elem_type, &(Bool){_t724});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t742 = U64_mul(self->cap, self->elem_size);
    (void)_t742;
    U8 *new_data = malloc(_t742);
    (void)new_data;
    ;
    {
        U64 _fi729 = 0;
        (void)_fi729;
        while (1) {
            U64 _t731 = 0;
            (void)_t731;
            Range *_t732 = Range_new(_t731, self->count);
            (void)_t732;
            ;
            U64 _t733; { U64 *_hp = (U64 *)Range_len(_t732); _t733 = *_hp; free(_hp); }
            (void)_t733;
            Range_delete(_t732, &(Bool){1});
            Bool _wcond730; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi729}, &(U64){_t733}); _wcond730 = *_hp; free(_hp); }
            (void)_wcond730;
            ;
            if (_wcond730) {
            } else {
                ;
                break;
            }
            ;
            U64 _t734 = 0;
            (void)_t734;
            Range *_t735 = Range_new(_t734, self->count);
            (void)_t735;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t735, _fi729); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t735, &(Bool){1});
            U64 _t736 = 1;
            (void)_t736;
            U64 _t737 = U64_add(_fi729, _t736);
            (void)_t737;
            ;
            _fi729 = _t737;
            ;
            U64 *_t738 = malloc(sizeof(U64)); *_t738 = U64_mul(i, self->elem_size);
            (void)_t738;
            void *_t739 = ptr_add(self->data, DEREF(_t738));
            (void)_t739;
            void *cloned = dyn_call_clone(&self->elem_type, _t739);
            (void)cloned;
            U64_delete(_t738, &(Bool){1});
            U64 *_t740 = malloc(sizeof(U64)); *_t740 = U64_mul(i, self->elem_size);
            (void)_t740;
            ;
            void *_t741 = ptr_add(new_data, DEREF(_t740));
            (void)_t741;
            memcpy(_t741, cloned, self->elem_size);
            U64_delete(_t740, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t743 = malloc(sizeof(Set));
    _t743->data = new_data;
    _t743->count = self->count;
    _t743->cap = self->cap;
    _t743->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t743->elem_type = *_ca; free(_ca); }
    (void)_t743;
    return _t743;
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
    Bool _t751; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t751 = *_hp; free(_hp); }
    (void)_t751;
    if (_t751) {
        Str *_t745 = Str_lit("Str", 3ULL);
        (void)_t745;
        U64 _t746; { U64 *_hp = (U64 *)Str_size(); _t746 = *_hp; free(_hp); }
        (void)_t746;
        U64 _t747 = 1;
        (void)_t747;
        Array *_va12 = Array_new(_t745, &(U64){_t746}, &(U64){_t747});
        (void)_va12;
        Str_delete(_t745, &(Bool){1});
        ;
        ;
        U64 _t748 = 0;
        (void)_t748;
        Str *_t749 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t749;
        Array_set(_va12, &(U64){_t748}, _t749);
        ;
        Str *_t750 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t750;
        panic(_t750, _va12);
        Str_delete(_t750, &(Bool){1});
    }
    ;
    void *_t752 = ptr_add(self->c_str, DEREF(i));
    (void)_t752;
    return _t752;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t753 = ptr_add(self->c_str, DEREF(i));
    (void)_t753;
    return _t753;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t765; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t765 = *_hp; free(_hp); }
    (void)_t765;
    if (_t765) {
        min_len = b->count;
    }
    ;
    {
        U64 _fi754 = 0;
        (void)_fi754;
        while (1) {
            U64 _t756 = 0;
            (void)_t756;
            Range *_t757 = Range_new(_t756, min_len);
            (void)_t757;
            ;
            U64 _t758; { U64 *_hp = (U64 *)Range_len(_t757); _t758 = *_hp; free(_hp); }
            (void)_t758;
            Range_delete(_t757, &(Bool){1});
            Bool _wcond755; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi754}, &(U64){_t758}); _wcond755 = *_hp; free(_hp); }
            (void)_wcond755;
            ;
            if (_wcond755) {
            } else {
                ;
                break;
            }
            ;
            U64 _t759 = 0;
            (void)_t759;
            Range *_t760 = Range_new(_t759, min_len);
            (void)_t760;
            ;
            U64 *i = Range_get(_t760, _fi754);
            (void)i;
            Range_delete(_t760, &(Bool){1});
            U64 _t761 = 1;
            (void)_t761;
            U64 _t762 = U64_add(_fi754, _t761);
            (void)_t762;
            ;
            _fi754 = _t762;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t763 = 0;
            (void)_t763;
            Bool _t764; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t763}); _t764 = *_hp; free(_hp); }
            (void)_t764;
            ;
            if (_t764) {
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
    I64 _t766 = U64_cmp(a->count, b->count);
    (void)_t766;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t766; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t767 = 1;
    (void)_t767;
    U64 _t768 = U64_add(DEREF(new_len), _t767);
    (void)_t768;
    ;
    U8 *new_data = malloc(_t768);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t769 = ptr_add(new_data, a->count);
    (void)_t769;
    memcpy(_t769, b->c_str, b->count);
    void *_t770 = ptr_add(new_data, DEREF(new_len));
    (void)_t770;
    I32 _t771 = 0;
    (void)_t771;
    U64 _t772 = 1;
    (void)_t772;
    memset(_t770, _t771, _t772);
    ;
    ;
    U64 _t773 = U64_clone(new_len);
    (void)_t773;
    U64 _t774 = U64_clone(new_len);
    (void)_t774;
    U64_delete(new_len, &(Bool){1});
    Str *_t775 = malloc(sizeof(Str));
    _t775->c_str = new_data;
    _t775->count = _t773;
    _t775->cap = _t774;
    (void)_t775;
    ;
    ;
    return _t775;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t776 = 1;
    (void)_t776;
    U64 _t777 = U64_add(DEREF(n), _t776);
    (void)_t777;
    ;
    U8 *buf = malloc(_t777);
    (void)buf;
    ;
    I32 _t778 = 0;
    (void)_t778;
    U64 _t779 = 1;
    (void)_t779;
    memset(buf, _t778, _t779);
    ;
    ;
    I64 _t780 = 0;
    (void)_t780;
    U64 _t781 = U64_clone(n);
    (void)_t781;
    Str *_t782 = malloc(sizeof(Str));
    _t782->c_str = buf;
    _t782->count = _t780;
    _t782->cap = _t781;
    (void)_t782;
    ;
    ;
    return _t782;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t795; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t795 = *_hp; free(_hp); }
    (void)_t795;
    if (_t795) {
        Str *_t783 = Str_lit("Str", 3ULL);
        (void)_t783;
        U64 _t784; { U64 *_hp = (U64 *)Str_size(); _t784 = *_hp; free(_hp); }
        (void)_t784;
        U64 _t785 = 1;
        (void)_t785;
        Array *_va13 = Array_new(_t783, &(U64){_t784}, &(U64){_t785});
        (void)_va13;
        Str_delete(_t783, &(Bool){1});
        ;
        ;
        U64 _t786 = 0;
        (void)_t786;
        Str *_t787 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t787;
        Array_set(_va13, &(U64){_t786}, _t787);
        ;
        Str *_t788 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t788;
        panic(_t788, _va13);
        Str_delete(_t788, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t796; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t796 = *_hp; free(_hp); }
    (void)_t796;
    if (_t796) {
        Str *_t789 = Str_lit("Str", 3ULL);
        (void)_t789;
        U64 _t790; { U64 *_hp = (U64 *)Str_size(); _t790 = *_hp; free(_hp); }
        (void)_t790;
        U64 _t791 = 1;
        (void)_t791;
        Array *_va14 = Array_new(_t789, &(U64){_t790}, &(U64){_t791});
        (void)_va14;
        Str_delete(_t789, &(Bool){1});
        ;
        ;
        U64 _t792 = 0;
        (void)_t792;
        Str *_t793 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t793;
        Array_set(_va14, &(U64){_t792}, _t793);
        ;
        Str *_t794 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t794;
        panic(_t794, _va14);
        Str_delete(_t794, &(Bool){1});
    }
    ;
    void *_t797 = ptr_add(self->c_str, self->count);
    (void)_t797;
    memcpy(_t797, s->c_str, s->count);
    U64 _t798 = U64_clone(new_len);
    (void)_t798;
    self->count = _t798;
    ;
    void *_t799 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t799;
    I32 _t800 = 0;
    (void)_t800;
    U64 _t801 = 1;
    (void)_t801;
    memset(_t799, _t800, _t801);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t802 = 1;
    (void)_t802;
    U64 _t803 = U64_add(val->count, _t802);
    (void)_t803;
    ;
    U8 *new_data = malloc(_t803);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t804 = ptr_add(new_data, val->count);
    (void)_t804;
    I32 _t805 = 0;
    (void)_t805;
    U64 _t806 = 1;
    (void)_t806;
    memset(_t804, _t805, _t806);
    ;
    ;
    Str *_t807 = malloc(sizeof(Str));
    _t807->c_str = new_data;
    _t807->count = val->count;
    _t807->cap = val->count;
    (void)_t807;
    return _t807;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t808; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t808 = *_hp; free(_hp); }
    (void)_t808;
    if (_t808) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t809 = Str_clone(val);
    (void)_t809;
    return _t809;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t811; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t811 = *_hp; free(_hp); }
    (void)_t811;
    if (_t811) {
        *st = s->count;
    }
    ;
    U64 _t812 = U64_add(DEREF(st), ln);
    (void)_t812;
    Bool _t813; { Bool *_hp = (Bool *)U64_gt(&(U64){_t812}, &s->count); _t813 = *_hp; free(_hp); }
    (void)_t813;
    ;
    if (_t813) {
        U64 _t810 = U64_sub(s->count, DEREF(st));
        (void)_t810;
        ln = _t810;
        ;
    }
    ;
    void *_t814 = ptr_add(s->c_str, DEREF(st));
    (void)_t814;
    U64 _t815 = U64_clone(&(U64){ln});
    (void)_t815;
    ;
    U64 _t816 = U64_clone(CAP_VIEW);
    (void)_t816;
    Str *_t817 = malloc(sizeof(Str));
    _t817->c_str = _t814;
    _t817->count = _t815;
    _t817->cap = _t816;
    (void)_t817;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t817;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t848 = 0;
    (void)_t848;
    Bool _t849 = U64_eq(b->count, _t848);
    (void)_t849;
    ;
    if (_t849) {
        Bool _t818 = 1;
        (void)_t818;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t818; return _r; }
    }
    ;
    Bool _t850; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t850 = *_hp; free(_hp); }
    (void)_t850;
    if (_t850) {
        Bool _t819 = 0;
        (void)_t819;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t819; return _r; }
    }
    ;
    {
        U64 _fi820 = 0;
        (void)_fi820;
        while (1) {
            U64 _t835 = U64_sub(a->count, b->count);
            (void)_t835;
            U64 _t836 = 1;
            (void)_t836;
            U64 _t837 = 0;
            (void)_t837;
            U64 _t838 = U64_add(_t835, _t836);
            (void)_t838;
            ;
            ;
            Range *_t839 = Range_new(_t837, _t838);
            (void)_t839;
            ;
            ;
            U64 _t840; { U64 *_hp = (U64 *)Range_len(_t839); _t840 = *_hp; free(_hp); }
            (void)_t840;
            Range_delete(_t839, &(Bool){1});
            Bool _wcond821; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi820}, &(U64){_t840}); _wcond821 = *_hp; free(_hp); }
            (void)_wcond821;
            ;
            if (_wcond821) {
            } else {
                ;
                break;
            }
            ;
            U64 _t841 = U64_sub(a->count, b->count);
            (void)_t841;
            U64 _t842 = 1;
            (void)_t842;
            U64 _t843 = 0;
            (void)_t843;
            U64 _t844 = U64_add(_t841, _t842);
            (void)_t844;
            ;
            ;
            Range *_t845 = Range_new(_t843, _t844);
            (void)_t845;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t845, _fi820); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t845, &(Bool){1});
            U64 _t846 = 1;
            (void)_t846;
            U64 _t847 = U64_add(_fi820, _t846);
            (void)_t847;
            ;
            _fi820 = _t847;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi822 = 0;
                (void)_fi822;
                while (1) {
                    U64 _t825 = 0;
                    (void)_t825;
                    Range *_t826 = Range_new(_t825, b->count);
                    (void)_t826;
                    ;
                    U64 _t827; { U64 *_hp = (U64 *)Range_len(_t826); _t827 = *_hp; free(_hp); }
                    (void)_t827;
                    Range_delete(_t826, &(Bool){1});
                    Bool _wcond823; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi822}, &(U64){_t827}); _wcond823 = *_hp; free(_hp); }
                    (void)_wcond823;
                    ;
                    if (_wcond823) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t828 = 0;
                    (void)_t828;
                    Range *_t829 = Range_new(_t828, b->count);
                    (void)_t829;
                    ;
                    U64 *j = Range_get(_t829, _fi822);
                    (void)j;
                    Range_delete(_t829, &(Bool){1});
                    U64 _t830 = 1;
                    (void)_t830;
                    U64 _t831 = U64_add(_fi822, _t830);
                    (void)_t831;
                    ;
                    _fi822 = _t831;
                    ;
                    U64 *_t832 = malloc(sizeof(U64)); *_t832 = U64_add(i, DEREF(j));
                    (void)_t832;
                    U8 *ac = Str_get(a, _t832);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t833; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t833 = *_hp; free(_hp); }
                    (void)_t833;
                    U64_delete(_t832, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t833) {
                        Bool _t824 = 0;
                        (void)_t824;
                        found = _t824;
                        ;
                    }
                    ;
                }
                ;
            }
            ;
            if (found) {
                Bool _t834 = 1;
                (void)_t834;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t834; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t851 = 0;
    (void)_t851;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t851; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t864; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t864 = *_hp; free(_hp); }
    (void)_t864;
    if (_t864) {
        Bool _t852 = 0;
        (void)_t852;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t852; return _r; }
    }
    ;
    {
        U64 _fi853 = 0;
        (void)_fi853;
        while (1) {
            U64 _t856 = 0;
            (void)_t856;
            Range *_t857 = Range_new(_t856, b->count);
            (void)_t857;
            ;
            U64 _t858; { U64 *_hp = (U64 *)Range_len(_t857); _t858 = *_hp; free(_hp); }
            (void)_t858;
            Range_delete(_t857, &(Bool){1});
            Bool _wcond854; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi853}, &(U64){_t858}); _wcond854 = *_hp; free(_hp); }
            (void)_wcond854;
            ;
            if (_wcond854) {
            } else {
                ;
                break;
            }
            ;
            U64 _t859 = 0;
            (void)_t859;
            Range *_t860 = Range_new(_t859, b->count);
            (void)_t860;
            ;
            U64 *i = Range_get(_t860, _fi853);
            (void)i;
            Range_delete(_t860, &(Bool){1});
            U64 _t861 = 1;
            (void)_t861;
            U64 _t862 = U64_add(_fi853, _t861);
            (void)_t862;
            ;
            _fi853 = _t862;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t863; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t863 = *_hp; free(_hp); }
            (void)_t863;
            U64_delete(i, &(Bool){1});
            if (_t863) {
                Bool _t855 = 0;
                (void)_t855;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t855; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t865 = 1;
    (void)_t865;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t865; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t879; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t879 = *_hp; free(_hp); }
    (void)_t879;
    if (_t879) {
        Bool _t866 = 0;
        (void)_t866;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t866; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _fi867 = 0;
        (void)_fi867;
        while (1) {
            U64 _t870 = 0;
            (void)_t870;
            Range *_t871 = Range_new(_t870, b->count);
            (void)_t871;
            ;
            U64 _t872; { U64 *_hp = (U64 *)Range_len(_t871); _t872 = *_hp; free(_hp); }
            (void)_t872;
            Range_delete(_t871, &(Bool){1});
            Bool _wcond868; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi867}, &(U64){_t872}); _wcond868 = *_hp; free(_hp); }
            (void)_wcond868;
            ;
            if (_wcond868) {
            } else {
                ;
                break;
            }
            ;
            U64 _t873 = 0;
            (void)_t873;
            Range *_t874 = Range_new(_t873, b->count);
            (void)_t874;
            ;
            U64 *i = Range_get(_t874, _fi867);
            (void)i;
            Range_delete(_t874, &(Bool){1});
            U64 _t875 = 1;
            (void)_t875;
            U64 _t876 = U64_add(_fi867, _t875);
            (void)_t876;
            ;
            _fi867 = _t876;
            ;
            U64 *_t877 = malloc(sizeof(U64)); *_t877 = U64_add(offset, DEREF(i));
            (void)_t877;
            U8 *ac = Str_get(a, _t877);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t878; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t878 = *_hp; free(_hp); }
            (void)_t878;
            U64_delete(_t877, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t878) {
                Bool _t869 = 0;
                (void)_t869;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t869; return _r; }
            }
            ;
        }
        ;
    }
    ;
    Bool _t880 = 1;
    (void)_t880;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t880; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t881 = 0;
    (void)_t881;
    Bool _t882 = U64_eq(self->count, _t881);
    (void)_t882;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t882; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t917 = 0;
    (void)_t917;
    Bool _t918 = U64_eq(needle->count, _t917);
    (void)_t918;
    ;
    if (_t918) {
        I64 _t883 = 0;
        (void)_t883;
        I64 _t884 = 1;
        (void)_t884;
        I64 _t885 = I64_sub(_t883, _t884);
        (void)_t885;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t885; return _r; }
    }
    ;
    Bool _t919; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t919 = *_hp; free(_hp); }
    (void)_t919;
    if (_t919) {
        I64 _t886 = 0;
        (void)_t886;
        I64 _t887 = 1;
        (void)_t887;
        I64 _t888 = I64_sub(_t886, _t887);
        (void)_t888;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t888; return _r; }
    }
    ;
    {
        U64 _fi889 = 0;
        (void)_fi889;
        while (1) {
            U64 _t904 = U64_sub(self->count, needle->count);
            (void)_t904;
            U64 _t905 = 1;
            (void)_t905;
            U64 _t906 = 0;
            (void)_t906;
            U64 _t907 = U64_add(_t904, _t905);
            (void)_t907;
            ;
            ;
            Range *_t908 = Range_new(_t906, _t907);
            (void)_t908;
            ;
            ;
            U64 _t909; { U64 *_hp = (U64 *)Range_len(_t908); _t909 = *_hp; free(_hp); }
            (void)_t909;
            Range_delete(_t908, &(Bool){1});
            Bool _wcond890; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi889}, &(U64){_t909}); _wcond890 = *_hp; free(_hp); }
            (void)_wcond890;
            ;
            if (_wcond890) {
            } else {
                ;
                break;
            }
            ;
            U64 _t910 = U64_sub(self->count, needle->count);
            (void)_t910;
            U64 _t911 = 1;
            (void)_t911;
            U64 _t912 = 0;
            (void)_t912;
            U64 _t913 = U64_add(_t910, _t911);
            (void)_t913;
            ;
            ;
            Range *_t914 = Range_new(_t912, _t913);
            (void)_t914;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t914, _fi889); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t914, &(Bool){1});
            U64 _t915 = 1;
            (void)_t915;
            U64 _t916 = U64_add(_fi889, _t915);
            (void)_t916;
            ;
            _fi889 = _t916;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi891 = 0;
                (void)_fi891;
                while (1) {
                    U64 _t894 = 0;
                    (void)_t894;
                    Range *_t895 = Range_new(_t894, needle->count);
                    (void)_t895;
                    ;
                    U64 _t896; { U64 *_hp = (U64 *)Range_len(_t895); _t896 = *_hp; free(_hp); }
                    (void)_t896;
                    Range_delete(_t895, &(Bool){1});
                    Bool _wcond892; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi891}, &(U64){_t896}); _wcond892 = *_hp; free(_hp); }
                    (void)_wcond892;
                    ;
                    if (_wcond892) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t897 = 0;
                    (void)_t897;
                    Range *_t898 = Range_new(_t897, needle->count);
                    (void)_t898;
                    ;
                    U64 *j = Range_get(_t898, _fi891);
                    (void)j;
                    Range_delete(_t898, &(Bool){1});
                    U64 _t899 = 1;
                    (void)_t899;
                    U64 _t900 = U64_add(_fi891, _t899);
                    (void)_t900;
                    ;
                    _fi891 = _t900;
                    ;
                    U64 *_t901 = malloc(sizeof(U64)); *_t901 = U64_add(i, DEREF(j));
                    (void)_t901;
                    U8 *ac = Str_get(self, _t901);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t902; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t902 = *_hp; free(_hp); }
                    (void)_t902;
                    U64_delete(_t901, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t902) {
                        Bool _t893 = 0;
                        (void)_t893;
                        found = _t893;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t903 = U64_to_i64(i);
                (void)_t903;
                ;
                ;
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t903; return _r; }
            }
            ;
            ;
        }
        ;
    }
    I64 _t920 = 0;
    (void)_t920;
    I64 _t921 = 1;
    (void)_t921;
    I64 _t922 = I64_sub(_t920, _t921);
    (void)_t922;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t922; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t957 = 0;
    (void)_t957;
    Bool _t958 = U64_eq(needle->count, _t957);
    (void)_t958;
    ;
    if (_t958) {
        I64 _t923 = 0;
        (void)_t923;
        I64 _t924 = 1;
        (void)_t924;
        I64 _t925 = I64_sub(_t923, _t924);
        (void)_t925;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t925; return _r; }
    }
    ;
    Bool _t959; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t959 = *_hp; free(_hp); }
    (void)_t959;
    if (_t959) {
        I64 _t926 = 0;
        (void)_t926;
        I64 _t927 = 1;
        (void)_t927;
        I64 _t928 = I64_sub(_t926, _t927);
        (void)_t928;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t928; return _r; }
    }
    ;
    I64 _t960 = 0;
    (void)_t960;
    I64 _t961 = 1;
    (void)_t961;
    I64 last = I64_sub(_t960, _t961);
    (void)last;
    ;
    ;
    {
        U64 _fi929 = 0;
        (void)_fi929;
        while (1) {
            U64 _t944 = U64_sub(self->count, needle->count);
            (void)_t944;
            U64 _t945 = 1;
            (void)_t945;
            U64 _t946 = 0;
            (void)_t946;
            U64 _t947 = U64_add(_t944, _t945);
            (void)_t947;
            ;
            ;
            Range *_t948 = Range_new(_t946, _t947);
            (void)_t948;
            ;
            ;
            U64 _t949; { U64 *_hp = (U64 *)Range_len(_t948); _t949 = *_hp; free(_hp); }
            (void)_t949;
            Range_delete(_t948, &(Bool){1});
            Bool _wcond930; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi929}, &(U64){_t949}); _wcond930 = *_hp; free(_hp); }
            (void)_wcond930;
            ;
            if (_wcond930) {
            } else {
                ;
                break;
            }
            ;
            U64 _t950 = U64_sub(self->count, needle->count);
            (void)_t950;
            U64 _t951 = 1;
            (void)_t951;
            U64 _t952 = 0;
            (void)_t952;
            U64 _t953 = U64_add(_t950, _t951);
            (void)_t953;
            ;
            ;
            Range *_t954 = Range_new(_t952, _t953);
            (void)_t954;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t954, _fi929); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t954, &(Bool){1});
            U64 _t955 = 1;
            (void)_t955;
            U64 _t956 = U64_add(_fi929, _t955);
            (void)_t956;
            ;
            _fi929 = _t956;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi931 = 0;
                (void)_fi931;
                while (1) {
                    U64 _t934 = 0;
                    (void)_t934;
                    Range *_t935 = Range_new(_t934, needle->count);
                    (void)_t935;
                    ;
                    U64 _t936; { U64 *_hp = (U64 *)Range_len(_t935); _t936 = *_hp; free(_hp); }
                    (void)_t936;
                    Range_delete(_t935, &(Bool){1});
                    Bool _wcond932; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi931}, &(U64){_t936}); _wcond932 = *_hp; free(_hp); }
                    (void)_wcond932;
                    ;
                    if (_wcond932) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t937 = 0;
                    (void)_t937;
                    Range *_t938 = Range_new(_t937, needle->count);
                    (void)_t938;
                    ;
                    U64 *j = Range_get(_t938, _fi931);
                    (void)j;
                    Range_delete(_t938, &(Bool){1});
                    U64 _t939 = 1;
                    (void)_t939;
                    U64 _t940 = U64_add(_fi931, _t939);
                    (void)_t940;
                    ;
                    _fi931 = _t940;
                    ;
                    U64 *_t941 = malloc(sizeof(U64)); *_t941 = U64_add(i, DEREF(j));
                    (void)_t941;
                    U8 *ac = Str_get(self, _t941);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t942; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t942 = *_hp; free(_hp); }
                    (void)_t942;
                    U64_delete(_t941, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t942) {
                        Bool _t933 = 0;
                        (void)_t933;
                        found = _t933;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t943 = U64_to_i64(i);
                (void)_t943;
                last = _t943;
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
    U64 _t977 = 0;
    (void)_t977;
    Bool _t978 = U64_eq(from->count, _t977);
    (void)_t978;
    ;
    if (_t978) {
        Str *_t962 = Str_clone(self);
        (void)_t962;
        ;
        return _t962;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t964 = U64_sub(self->count, from->count);
        (void)_t964;
        Bool _wcond963; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t964}); _wcond963 = *_hp; free(_hp); }
        (void)_wcond963;
        ;
        if (_wcond963) {
        } else {
            ;
            break;
        }
        ;
        U64 _t965 = U64_sub(self->count, start);
        (void)_t965;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t965});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t966 = 0;
        (void)_t966;
        I64 _t967 = 1;
        (void)_t967;
        I64 _t968 = I64_sub(_t966, _t967);
        (void)_t968;
        ;
        ;
        Bool _t969 = I64_eq(pos, _t968);
        (void)_t969;
        ;
        if (_t969) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t970 = I64_to_u64(pos);
        (void)_t970;
        Str *_t971 = Str_substr(self, &(U64){start}, &(U64){_t970});
        (void)_t971;
        ;
        result = Str_concat(result, _t971);
        Str_delete(_t971, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t972 = I64_to_u64(pos);
        (void)_t972;
        ;
        U64 _t973 = U64_add(start, _t972);
        (void)_t973;
        ;
        U64 _t974 = U64_add(_t973, from->count);
        (void)_t974;
        ;
        start = _t974;
        ;
    }
    Bool _t979; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t979 = *_hp; free(_hp); }
    (void)_t979;
    if (_t979) {
        U64 _t975 = U64_sub(self->count, start);
        (void)_t975;
        Str *_t976 = Str_substr(self, &(U64){start}, &(U64){_t975});
        (void)_t976;
        ;
        result = Str_concat(result, _t976);
        Str_delete(_t976, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t980 = 1;
    (void)_t980;
    Str *_t981 = Str_substr(self, i, &(U64){_t980});
    (void)_t981;
    ;
    return _t981;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t984; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t984 = *_hp; free(_hp); }
    (void)_t984;
    if (_t984) {
        U64 _t982 = U64_sub(self->count, prefix->count);
        (void)_t982;
        Str *_t983 = Str_substr(self, &prefix->count, &(U64){_t982});
        (void)_t983;
        ;
        ;
        return _t983;
    }
    ;
    Str *_t985 = Str_clone(self);
    (void)_t985;
    return _t985;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t989; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t989 = *_hp; free(_hp); }
    (void)_t989;
    if (_t989) {
        U64 _t986 = 0;
        (void)_t986;
        U64 _t987 = U64_sub(self->count, suffix->count);
        (void)_t987;
        Str *_t988 = Str_substr(self, &(U64){_t986}, &(U64){_t987});
        (void)_t988;
        ;
        ;
        ;
        return _t988;
    }
    ;
    Str *_t990 = Str_clone(self);
    (void)_t990;
    return _t990;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t991 = 2;
    (void)_t991;
    U8 *buf = malloc(_t991);
    (void)buf;
    ;
    U64 _t992 = 1;
    (void)_t992;
    memcpy(buf, byte, _t992);
    ;
    U64 *_t993 = malloc(sizeof(U64));
    *_t993 = 1;
    (void)_t993;
    void *_t994 = ptr_add(buf, DEREF(_t993));
    (void)_t994;
    I32 _t995 = 0;
    (void)_t995;
    U64 _t996 = 1;
    (void)_t996;
    memset(_t994, _t995, _t996);
    U64_delete(_t993, &(Bool){1});
    ;
    ;
    I64 _t997 = 1;
    (void)_t997;
    I64 _t998 = 1;
    (void)_t998;
    Str *_t999 = malloc(sizeof(Str));
    _t999->c_str = buf;
    _t999->count = _t997;
    _t999->cap = _t998;
    (void)_t999;
    ;
    ;
    return _t999;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t1043 = 0;
    (void)_t1043;
    Bool _t1044 = U64_eq(self->count, _t1043);
    (void)_t1044;
    ;
    if (_t1044) {
        Str *_t1000 = Str_lit("Str", 3ULL);
        (void)_t1000;
        U64 _t1001; { U64 *_hp = (U64 *)Str_size(); _t1001 = *_hp; free(_hp); }
        (void)_t1001;
        U64 _t1002 = 1;
        (void)_t1002;
        Array *_va15 = Array_new(_t1000, &(U64){_t1001}, &(U64){_t1002});
        (void)_va15;
        Str_delete(_t1000, &(Bool){1});
        ;
        ;
        U64 _t1003 = 0;
        (void)_t1003;
        Str *_t1004 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t1004;
        Array_set(_va15, &(U64){_t1003}, _t1004);
        ;
        Str *_t1005 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t1005;
        panic(_t1005, _va15);
        Str_delete(_t1005, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t1045 = malloc(sizeof(U64));
    *_t1045 = 0;
    (void)_t1045;
    U8 *first = Str_get(self, _t1045);
    (void)first;
    U8 _t1046 = 45;
    (void)_t1046;
    Bool _t1047 = U8_eq(DEREF(first), _t1046);
    (void)_t1047;
    U64_delete(_t1045, &(Bool){1});
    ;
    if (_t1047) {
        Bool _t1006 = 1;
        (void)_t1006;
        neg = _t1006;
        ;
        U64 _t1007 = 1;
        (void)_t1007;
        start = _t1007;
        ;
    }
    ;
    Bool _t1048 = U64_eq(start, self->count);
    (void)_t1048;
    if (_t1048) {
        Str *_t1008 = Str_lit("Str", 3ULL);
        (void)_t1008;
        U64 _t1009; { U64 *_hp = (U64 *)Str_size(); _t1009 = *_hp; free(_hp); }
        (void)_t1009;
        U64 _t1010 = 1;
        (void)_t1010;
        Array *_va16 = Array_new(_t1008, &(U64){_t1009}, &(U64){_t1010});
        (void)_va16;
        Str_delete(_t1008, &(Bool){1});
        ;
        ;
        U64 _t1011 = 0;
        (void)_t1011;
        Str *_t1012 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t1012;
        Array_set(_va16, &(U64){_t1011}, _t1012);
        ;
        Str *_t1013 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t1013;
        panic(_t1013, _va16);
        Str_delete(_t1013, &(Bool){1});
    }
    ;
    {
        U64 _fi1014 = 0;
        (void)_fi1014;
        while (1) {
            Range *_t1026 = Range_new(start, self->count);
            (void)_t1026;
            U64 _t1027; { U64 *_hp = (U64 *)Range_len(_t1026); _t1027 = *_hp; free(_hp); }
            (void)_t1027;
            Range_delete(_t1026, &(Bool){1});
            Bool _wcond1015; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1014}, &(U64){_t1027}); _wcond1015 = *_hp; free(_hp); }
            (void)_wcond1015;
            ;
            if (_wcond1015) {
            } else {
                ;
                break;
            }
            ;
            Range *_t1028 = Range_new(start, self->count);
            (void)_t1028;
            U64 *i = Range_get(_t1028, _fi1014);
            (void)i;
            Range_delete(_t1028, &(Bool){1});
            U64 _t1029 = 1;
            (void)_t1029;
            U64 _t1030 = U64_add(_fi1014, _t1029);
            (void)_t1030;
            ;
            _fi1014 = _t1030;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t1031 = U8_to_i64(DEREF(ch));
            (void)_t1031;
            U64_delete(i, &(Bool){1});
            I64 _t1032 = 48;
            (void)_t1032;
            I64 d = I64_sub(_t1031, _t1032);
            (void)d;
            ;
            ;
            I64 _t1033 = 0;
            (void)_t1033;
            I64 _t1034 = 9;
            (void)_t1034;
            Bool _t1035; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t1033}); _t1035 = *_hp; free(_hp); }
            (void)_t1035;
            ;
            Bool _t1036; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t1034}); _t1036 = *_hp; free(_hp); }
            (void)_t1036;
            ;
            Bool _t1037 = Bool_or(_t1035, _t1036);
            (void)_t1037;
            ;
            ;
            if (_t1037) {
                Str *_t1016 = Str_lit("Str", 3ULL);
                (void)_t1016;
                U64 _t1017; { U64 *_hp = (U64 *)Str_size(); _t1017 = *_hp; free(_hp); }
                (void)_t1017;
                U64 _t1018 = 3;
                (void)_t1018;
                Array *_va17 = Array_new(_t1016, &(U64){_t1017}, &(U64){_t1018});
                (void)_va17;
                Str_delete(_t1016, &(Bool){1});
                ;
                ;
                U64 _t1019 = 0;
                (void)_t1019;
                Str *_t1020 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t1020;
                Array_set(_va17, &(U64){_t1019}, _t1020);
                ;
                U64 _t1021 = 1;
                (void)_t1021;
                Str *_t1022 = Str_clone(self);
                (void)_t1022;
                Array_set(_va17, &(U64){_t1021}, _t1022);
                ;
                U64 _t1023 = 2;
                (void)_t1023;
                Str *_t1024 = Str_lit("'", 1ULL);
                (void)_t1024;
                Array_set(_va17, &(U64){_t1023}, _t1024);
                ;
                Str *_t1025 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t1025;
                panic(_t1025, _va17);
                Str_delete(_t1025, &(Bool){1});
            }
            ;
            I64 _t1038 = 10;
            (void)_t1038;
            I64 _t1039 = I64_mul(result, _t1038);
            (void)_t1039;
            ;
            I64 _t1040 = I64_add(_t1039, d);
            (void)_t1040;
            ;
            ;
            result = _t1040;
            ;
        }
        ;
    }
    ;
    if (neg) {
        I64 _t1041 = 0;
        (void)_t1041;
        I64 _t1042 = I64_sub(_t1041, result);
        (void)_t1042;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t1042; return _r; }
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
    I64 _t1050; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1050 = *_hp; free(_hp); }
    (void)_t1050;
    I64 _t1051 = 0;
    (void)_t1051;
    Bool _t1052 = I64_eq(_t1050, _t1051);
    (void)_t1052;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1052; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1053 = 0;
    (void)_t1053;
    I64 _t1054 = 1;
    (void)_t1054;
    I64 _t1055; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1055 = *_hp; free(_hp); }
    (void)_t1055;
    I64 _t1056 = I64_sub(_t1053, _t1054);
    (void)_t1056;
    ;
    ;
    Bool _t1057 = I64_eq(_t1055, _t1056);
    (void)_t1057;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1057; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1058; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1058 = *_hp; free(_hp); }
    (void)_t1058;
    I64 _t1059 = 1;
    (void)_t1059;
    Bool _t1060 = I64_eq(_t1058, _t1059);
    (void)_t1060;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1060; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1061; { Bool *_hp = (Bool *)Str_eq(a, b); _t1061 = *_hp; free(_hp); }
    (void)_t1061;
    Bool _t1062 = Bool_not(_t1061);
    (void)_t1062;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1063; { Bool *_hp = (Bool *)Str_gt(a, b); _t1063 = *_hp; free(_hp); }
    (void)_t1063;
    Bool _t1064 = Bool_not(_t1063);
    (void)_t1064;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1065; { Bool *_hp = (Bool *)Str_lt(a, b); _t1065 = *_hp; free(_hp); }
    (void)_t1065;
    Bool _t1066 = Bool_not(_t1065);
    (void)_t1066;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1067 = malloc(DEREF(elem_size));
    (void)_t1067;
    U64 _t1068 = 0;
    (void)_t1068;
    I64 _t1069 = 1;
    (void)_t1069;
    U64 _t1070 = U64_clone(elem_size);
    (void)_t1070;
    Vec *_t1071 = malloc(sizeof(Vec));
    _t1071->data = _t1067;
    _t1071->count = _t1068;
    _t1071->cap = _t1069;
    _t1071->elem_size = _t1070;
    { Str *_ca = Str_clone(elem_type); _t1071->elem_type = *_ca; free(_ca); }
    (void)_t1071;
    ;
    ;
    ;
    return _t1071;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1076 = U64_eq(self->count, self->cap);
    (void)_t1076;
    if (_t1076) {
        U64 _t1072 = 2;
        (void)_t1072;
        U64 new_cap = U64_mul(self->cap, _t1072);
        (void)new_cap;
        ;
        U64 _t1073 = U64_mul(new_cap, self->elem_size);
        (void)_t1073;
        void *_t1074 = realloc(self->data, _t1073);
        (void)_t1074;
        ;
        self->data = _t1074;
        U64 _t1075 = U64_clone(&(U64){new_cap});
        (void)_t1075;
        ;
        self->cap = _t1075;
        ;
    }
    ;
    U64 *_t1077 = malloc(sizeof(U64)); *_t1077 = U64_mul(self->count, self->elem_size);
    (void)_t1077;
    void *_t1078 = ptr_add(self->data, DEREF(_t1077));
    (void)_t1078;
    memcpy(_t1078, val, self->elem_size);
    U64_delete(_t1077, &(Bool){1});
    free(val);
    U64 _t1079 = 1;
    (void)_t1079;
    U64 _t1080 = U64_add(self->count, _t1079);
    (void)_t1080;
    ;
    self->count = _t1080;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1095; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1095 = *_hp; free(_hp); }
    (void)_t1095;
    if (_t1095) {
        Str *_t1081 = Str_lit("Str", 3ULL);
        (void)_t1081;
        U64 _t1082; { U64 *_hp = (U64 *)Str_size(); _t1082 = *_hp; free(_hp); }
        (void)_t1082;
        U64 _t1083 = 5;
        (void)_t1083;
        Array *_va18 = Array_new(_t1081, &(U64){_t1082}, &(U64){_t1083});
        (void)_va18;
        Str_delete(_t1081, &(Bool){1});
        ;
        ;
        U64 _t1084 = 0;
        (void)_t1084;
        Str *_t1085 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1085;
        Array_set(_va18, &(U64){_t1084}, _t1085);
        ;
        U64 _t1086 = 1;
        (void)_t1086;
        Str *_t1087 = U64_to_str(DEREF(i));
        (void)_t1087;
        Array_set(_va18, &(U64){_t1086}, _t1087);
        ;
        U64 _t1088 = 2;
        (void)_t1088;
        Str *_t1089 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1089;
        Array_set(_va18, &(U64){_t1088}, _t1089);
        ;
        U64 _t1090 = 3;
        (void)_t1090;
        Str *_t1091 = U64_to_str(self->count);
        (void)_t1091;
        Array_set(_va18, &(U64){_t1090}, _t1091);
        ;
        U64 _t1092 = 4;
        (void)_t1092;
        Str *_t1093 = Str_lit(")", 1ULL);
        (void)_t1093;
        Array_set(_va18, &(U64){_t1092}, _t1093);
        ;
        Str *_t1094 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1094;
        panic(_t1094, _va18);
        Str_delete(_t1094, &(Bool){1});
    }
    ;
    U64 *_t1096 = malloc(sizeof(U64)); *_t1096 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1096;
    void *_t1097 = ptr_add(self->data, DEREF(_t1096));
    (void)_t1097;
    U64_delete(_t1096, &(Bool){1});
    return _t1097;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1111; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1111 = *_hp; free(_hp); }
    (void)_t1111;
    Bool _t1112 = Bool_not(_t1111);
    (void)_t1112;
    ;
    if (_t1112) {
        {
            U64 _fi1098 = 0;
            (void)_fi1098;
            while (1) {
                U64 _t1100 = 0;
                (void)_t1100;
                Range *_t1101 = Range_new(_t1100, self->count);
                (void)_t1101;
                ;
                U64 _t1102; { U64 *_hp = (U64 *)Range_len(_t1101); _t1102 = *_hp; free(_hp); }
                (void)_t1102;
                Range_delete(_t1101, &(Bool){1});
                Bool _wcond1099; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1098}, &(U64){_t1102}); _wcond1099 = *_hp; free(_hp); }
                (void)_wcond1099;
                ;
                if (_wcond1099) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1103 = 0;
                (void)_t1103;
                Range *_t1104 = Range_new(_t1103, self->count);
                (void)_t1104;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1104, _fi1098); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1104, &(Bool){1});
                U64 _t1105 = 1;
                (void)_t1105;
                U64 _t1106 = U64_add(_fi1098, _t1105);
                (void)_t1106;
                ;
                _fi1098 = _t1106;
                ;
                U64 *_t1107 = malloc(sizeof(U64)); *_t1107 = U64_mul(i, self->elem_size);
                (void)_t1107;
                ;
                void *_t1108 = ptr_add(self->data, DEREF(_t1107));
                (void)_t1108;
                Bool _t1109 = 0;
                (void)_t1109;
                dyn_call_delete(&self->elem_type, _t1108, &(Bool){_t1109});
                U64_delete(_t1107, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1113; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1113 = *_hp; free(_hp); }
    (void)_t1113;
    Bool _t1114 = Bool_not(_t1113);
    (void)_t1114;
    ;
    if (_t1114) {
        Bool _t1110 = 0;
        (void)_t1110;
        Str_delete(&self->elem_type, &(Bool){_t1110});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1128 = U64_mul(self->cap, self->elem_size);
    (void)_t1128;
    U8 *new_data = malloc(_t1128);
    (void)new_data;
    ;
    {
        U64 _fi1115 = 0;
        (void)_fi1115;
        while (1) {
            U64 _t1117 = 0;
            (void)_t1117;
            Range *_t1118 = Range_new(_t1117, self->count);
            (void)_t1118;
            ;
            U64 _t1119; { U64 *_hp = (U64 *)Range_len(_t1118); _t1119 = *_hp; free(_hp); }
            (void)_t1119;
            Range_delete(_t1118, &(Bool){1});
            Bool _wcond1116; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1115}, &(U64){_t1119}); _wcond1116 = *_hp; free(_hp); }
            (void)_wcond1116;
            ;
            if (_wcond1116) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1120 = 0;
            (void)_t1120;
            Range *_t1121 = Range_new(_t1120, self->count);
            (void)_t1121;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1121, _fi1115); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1121, &(Bool){1});
            U64 _t1122 = 1;
            (void)_t1122;
            U64 _t1123 = U64_add(_fi1115, _t1122);
            (void)_t1123;
            ;
            _fi1115 = _t1123;
            ;
            U64 *_t1124 = malloc(sizeof(U64)); *_t1124 = U64_mul(i, self->elem_size);
            (void)_t1124;
            void *_t1125 = ptr_add(self->data, DEREF(_t1124));
            (void)_t1125;
            void *cloned = dyn_call_clone(&self->elem_type, _t1125);
            (void)cloned;
            U64_delete(_t1124, &(Bool){1});
            U64 *_t1126 = malloc(sizeof(U64)); *_t1126 = U64_mul(i, self->elem_size);
            (void)_t1126;
            ;
            void *_t1127 = ptr_add(new_data, DEREF(_t1126));
            (void)_t1127;
            memcpy(_t1127, cloned, self->elem_size);
            U64_delete(_t1126, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1129 = malloc(sizeof(Vec));
    _t1129->data = new_data;
    _t1129->count = self->count;
    _t1129->cap = self->cap;
    _t1129->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1129->elem_type = *_ca; free(_ca); }
    (void)_t1129;
    return _t1129;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1147 = Str_lit("Str", 3ULL);
    (void)_t1147;
    U64 _t1148; { U64 *_hp = (U64 *)Str_size(); _t1148 = *_hp; free(_hp); }
    (void)_t1148;
    Vec *parts = Vec_new(_t1147, &(U64){_t1148});
    (void)parts;
    Str_delete(_t1147, &(Bool){1});
    ;
    U64 _t1149; { U64 *_hp = (U64 *)Str_len(delim); _t1149 = *_hp; free(_hp); }
    (void)_t1149;
    U64 _t1150 = 0;
    (void)_t1150;
    Bool _t1151 = U64_eq(_t1149, _t1150);
    (void)_t1151;
    ;
    ;
    if (_t1151) {
        Str *_t1131 = Str_clone(s);
        (void)_t1131;
        Vec_push(parts, _t1131);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1141; { U64 *_hp = (U64 *)Str_len(s); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        U64 _t1142; { U64 *_hp = (U64 *)Str_len(delim); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        U64 _t1143 = U64_sub(_t1141, _t1142);
        (void)_t1143;
        ;
        ;
        Bool _wcond1132; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1143}); _wcond1132 = *_hp; free(_hp); }
        (void)_wcond1132;
        ;
        if (_wcond1132) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1144; { U64 *_hp = (U64 *)Str_len(delim); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        Str *_t1145 = Str_substr(s, &(U64){pos}, &(U64){_t1144});
        (void)_t1145;
        ;
        Bool _t1146; { Bool *_hp = (Bool *)Str_eq(_t1145, delim); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        Str_delete(_t1145, &(Bool){1});
        if (_t1146) {
            U64 _t1133 = U64_sub(pos, start);
            (void)_t1133;
            Str *_t1134 = Str_substr(s, &(U64){start}, &(U64){_t1133});
            (void)_t1134;
            ;
            Str *_t1135 = Str_clone(_t1134);
            (void)_t1135;
            Str_delete(_t1134, &(Bool){1});
            Vec_push(parts, _t1135);
            U64 _t1136; { U64 *_hp = (U64 *)Str_len(delim); _t1136 = *_hp; free(_hp); }
            (void)_t1136;
            U64 _t1137 = U64_add(pos, _t1136);
            (void)_t1137;
            ;
            start = _t1137;
            ;
            U64 _t1138 = U64_clone(&(U64){start});
            (void)_t1138;
            pos = _t1138;
            ;
        } else {
            U64 _t1139 = 1;
            (void)_t1139;
            U64 _t1140 = U64_add(pos, _t1139);
            (void)_t1140;
            ;
            pos = _t1140;
            ;
        }
        ;
    }
    ;
    U64 _t1152; { U64 *_hp = (U64 *)Str_len(s); _t1152 = *_hp; free(_hp); }
    (void)_t1152;
    U64 _t1153 = U64_sub(_t1152, start);
    (void)_t1153;
    ;
    Str *_t1154 = Str_substr(s, &(U64){start}, &(U64){_t1153});
    (void)_t1154;
    ;
    ;
    Str *_t1155 = Str_clone(_t1154);
    (void)_t1155;
    Str_delete(_t1154, &(Bool){1});
    Vec_push(parts, _t1155);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1170; { U64 *_hp = (U64 *)Vec_len(parts); _t1170 = *_hp; free(_hp); }
    (void)_t1170;
    U64 _t1171 = 0;
    (void)_t1171;
    Bool _t1172 = U64_eq(_t1170, _t1171);
    (void)_t1172;
    ;
    ;
    if (_t1172) {
        Str *_t1156 = Str_lit("", 0ULL);
        (void)_t1156;
        ;
        return _t1156;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1157 = 0;
        (void)_fi1157;
        while (1) {
            U64 _t1159 = 0;
            (void)_t1159;
            U64 _t1160; { U64 *_hp = (U64 *)Vec_len(parts); _t1160 = *_hp; free(_hp); }
            (void)_t1160;
            Range *_t1161 = Range_new(_t1159, _t1160);
            (void)_t1161;
            ;
            ;
            U64 _t1162; { U64 *_hp = (U64 *)Range_len(_t1161); _t1162 = *_hp; free(_hp); }
            (void)_t1162;
            Range_delete(_t1161, &(Bool){1});
            Bool _wcond1158; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1157}, &(U64){_t1162}); _wcond1158 = *_hp; free(_hp); }
            (void)_wcond1158;
            ;
            if (_wcond1158) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1163 = 0;
            (void)_t1163;
            U64 _t1164; { U64 *_hp = (U64 *)Vec_len(parts); _t1164 = *_hp; free(_hp); }
            (void)_t1164;
            Range *_t1165 = Range_new(_t1163, _t1164);
            (void)_t1165;
            ;
            ;
            U64 *i = Range_get(_t1165, _fi1157);
            (void)i;
            Range_delete(_t1165, &(Bool){1});
            U64 _t1166 = 1;
            (void)_t1166;
            U64 _t1167 = U64_add(_fi1157, _t1166);
            (void)_t1167;
            ;
            _fi1157 = _t1167;
            ;
            U64 _t1168 = 0;
            (void)_t1168;
            Bool _t1169; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1168}); _t1169 = *_hp; free(_hp); }
            (void)_t1169;
            ;
            if (_t1169) {
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
    U64 _t1173 = 8;
    (void)_t1173;
    Str *_t1174 = Str_lit("Str", 3ULL);
    (void)_t1174;
    U64 _t1175; { U64 *_hp = (U64 *)Str_size(); _t1175 = *_hp; free(_hp); }
    (void)_t1175;
    Str *_t1176 = Str_lit("U64", 3ULL);
    (void)_t1176;
    U64 _t1177; { U64 *_hp = (U64 *)U64_size(); _t1177 = *_hp; free(_hp); }
    (void)_t1177;
    void *_t1178 = malloc(_t1173);
    (void)_t1178;
    ;
    U64 _t1179 = 0;
    (void)_t1179;
    I64 _t1180 = 8;
    (void)_t1180;
    Tuple *_t1181 = malloc(sizeof(Tuple));
    _t1181->data = _t1178;
    _t1181->total_size = _t1179;
    _t1181->cap = _t1180;
    { Vec *_ca = Vec_new(_t1174, &(U64){_t1175}); _t1181->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1176, &(U64){_t1177}); _t1181->type_sizes = *_ca; free(_ca); }
    (void)_t1181;
    Str_delete(_t1174, &(Bool){1});
    ;
    Str_delete(_t1176, &(Bool){1});
    ;
    ;
    ;
    return _t1181;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1182; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1182; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1189; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        U64 _t1186 = 2;
        (void)_t1186;
        U64 new_cap = U64_mul(self->cap, _t1186);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1183; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1183 = *_hp; free(_hp); }
            (void)_wcond1183;
            if (_wcond1183) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1184 = 2;
            (void)_t1184;
            U64 _t1185 = U64_mul(new_cap, _t1184);
            (void)_t1185;
            ;
            new_cap = _t1185;
            ;
        }
        void *_t1187 = realloc(self->data, new_cap);
        (void)_t1187;
        self->data = _t1187;
        U64 _t1188 = U64_clone(&(U64){new_cap});
        (void)_t1188;
        ;
        self->cap = _t1188;
        ;
    }
    ;
    void *_t1190 = ptr_add(self->data, self->total_size);
    (void)_t1190;
    memcpy(_t1190, val, DEREF(elem_size));
    free(val);
    Str *_t1191 = Str_clone(elem_type);
    (void)_t1191;
    Vec_push(&self->type_names, _t1191);
    U64 _t1192 = U64_clone(elem_size);
    (void)_t1192;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1192; _oa; }));
    U64 _t1193 = U64_clone(&(U64){new_total});
    (void)_t1193;
    ;
    self->total_size = _t1193;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1219; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    Bool _t1220; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1219}); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    ;
    if (_t1220) {
        Str *_t1194 = Str_lit("Str", 3ULL);
        (void)_t1194;
        U64 _t1195; { U64 *_hp = (U64 *)Str_size(); _t1195 = *_hp; free(_hp); }
        (void)_t1195;
        U64 _t1196 = 5;
        (void)_t1196;
        Array *_va19 = Array_new(_t1194, &(U64){_t1195}, &(U64){_t1196});
        (void)_va19;
        Str_delete(_t1194, &(Bool){1});
        ;
        ;
        U64 _t1197 = 0;
        (void)_t1197;
        Str *_t1198 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1198;
        Array_set(_va19, &(U64){_t1197}, _t1198);
        ;
        U64 _t1199 = 1;
        (void)_t1199;
        Str *_t1200 = U64_to_str(DEREF(i));
        (void)_t1200;
        Array_set(_va19, &(U64){_t1199}, _t1200);
        ;
        U64 _t1201 = 2;
        (void)_t1201;
        Str *_t1202 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1202;
        Array_set(_va19, &(U64){_t1201}, _t1202);
        ;
        U64 _t1203; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1203 = *_hp; free(_hp); }
        (void)_t1203;
        U64 _t1204 = 3;
        (void)_t1204;
        Str *_t1205 = U64_to_str(_t1203);
        (void)_t1205;
        ;
        Array_set(_va19, &(U64){_t1204}, _t1205);
        ;
        U64 _t1206 = 4;
        (void)_t1206;
        Str *_t1207 = Str_lit(")", 1ULL);
        (void)_t1207;
        Array_set(_va19, &(U64){_t1206}, _t1207);
        ;
        Str *_t1208 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1208;
        panic(_t1208, _va19);
        Str_delete(_t1208, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1209 = 0;
        (void)_fi1209;
        while (1) {
            U64 _t1211 = 0;
            (void)_t1211;
            Range *_t1212 = Range_new(_t1211, DEREF(i));
            (void)_t1212;
            ;
            U64 _t1213; { U64 *_hp = (U64 *)Range_len(_t1212); _t1213 = *_hp; free(_hp); }
            (void)_t1213;
            Range_delete(_t1212, &(Bool){1});
            Bool _wcond1210; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1209}, &(U64){_t1213}); _wcond1210 = *_hp; free(_hp); }
            (void)_wcond1210;
            ;
            if (_wcond1210) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1214 = 0;
            (void)_t1214;
            Range *_t1215 = Range_new(_t1214, DEREF(i));
            (void)_t1215;
            ;
            U64 *j = Range_get(_t1215, _fi1209);
            (void)j;
            Range_delete(_t1215, &(Bool){1});
            U64 _t1216 = 1;
            (void)_t1216;
            U64 _t1217 = U64_add(_fi1209, _t1216);
            (void)_t1217;
            ;
            _fi1209 = _t1217;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1218 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1218;
            U64_delete(j, &(Bool){1});
            *offset = _t1218;
            ;
        }
        ;
    }
    void *_t1221 = ptr_add(self->data, DEREF(offset));
    (void)_t1221;
    U64_delete(offset, &(Bool){1});
    return _t1221;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1222 = Vec_get(&self->type_names, i);
    (void)_t1222;
    return _t1222;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1223 = Vec_get(&self->type_sizes, i);
    (void)_t1223;
    return _t1223;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1224 = 0;
        (void)_fi1224;
        while (1) {
            U64 _t1226 = 0;
            (void)_t1226;
            U64 _t1227; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1227 = *_hp; free(_hp); }
            (void)_t1227;
            Range *_t1228 = Range_new(_t1226, _t1227);
            (void)_t1228;
            ;
            ;
            U64 _t1229; { U64 *_hp = (U64 *)Range_len(_t1228); _t1229 = *_hp; free(_hp); }
            (void)_t1229;
            Range_delete(_t1228, &(Bool){1});
            Bool _wcond1225; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1224}, &(U64){_t1229}); _wcond1225 = *_hp; free(_hp); }
            (void)_wcond1225;
            ;
            if (_wcond1225) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1230 = 0;
            (void)_t1230;
            U64 _t1231; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1231 = *_hp; free(_hp); }
            (void)_t1231;
            Range *_t1232 = Range_new(_t1230, _t1231);
            (void)_t1232;
            ;
            ;
            U64 *i = Range_get(_t1232, _fi1224);
            (void)i;
            Range_delete(_t1232, &(Bool){1});
            U64 _t1233 = 1;
            (void)_t1233;
            U64 _t1234 = U64_add(_fi1224, _t1233);
            (void)_t1234;
            ;
            _fi1224 = _t1234;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1235 = ptr_add(self->data, DEREF(offset));
            (void)_t1235;
            Bool _t1236 = 0;
            (void)_t1236;
            dyn_call_delete(tn, _t1235, &(Bool){_t1236});
            ;
            U64 _t1237 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1237;
            U64_delete(i, &(Bool){1});
            *offset = _t1237;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1238 = 0;
    (void)_t1238;
    Vec_delete(&self->type_names, &(Bool){_t1238});
    ;
    Bool _t1239 = 0;
    (void)_t1239;
    Vec_delete(&self->type_sizes, &(Bool){_t1239});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1256 = 0;
    (void)_t1256;
    Bool _t1257 = U64_eq(new_cap, _t1256);
    (void)_t1257;
    ;
    if (_t1257) {
        I64 _t1240 = 8;
        (void)_t1240;
        U64 _t1241; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1240}); _t1241 = *_hp; free(_hp); }
        (void)_t1241;
        ;
        new_cap = _t1241;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1242 = 0;
        (void)_fi1242;
        while (1) {
            U64 _t1244 = 0;
            (void)_t1244;
            U64 _t1245; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1245 = *_hp; free(_hp); }
            (void)_t1245;
            Range *_t1246 = Range_new(_t1244, _t1245);
            (void)_t1246;
            ;
            ;
            U64 _t1247; { U64 *_hp = (U64 *)Range_len(_t1246); _t1247 = *_hp; free(_hp); }
            (void)_t1247;
            Range_delete(_t1246, &(Bool){1});
            Bool _wcond1243; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1242}, &(U64){_t1247}); _wcond1243 = *_hp; free(_hp); }
            (void)_wcond1243;
            ;
            if (_wcond1243) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1248 = 0;
            (void)_t1248;
            U64 _t1249; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1249 = *_hp; free(_hp); }
            (void)_t1249;
            Range *_t1250 = Range_new(_t1248, _t1249);
            (void)_t1250;
            ;
            ;
            U64 *i = Range_get(_t1250, _fi1242);
            (void)i;
            Range_delete(_t1250, &(Bool){1});
            U64 _t1251 = 1;
            (void)_t1251;
            U64 _t1252 = U64_add(_fi1242, _t1251);
            (void)_t1252;
            ;
            _fi1242 = _t1252;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1253 = ptr_add(self->data, DEREF(offset));
            (void)_t1253;
            void *cloned = dyn_call_clone(tn, _t1253);
            (void)cloned;
            void *_t1254 = ptr_add(new_data, DEREF(offset));
            (void)_t1254;
            memcpy(_t1254, cloned, DEREF(ts));
            free(cloned);
            U64 _t1255 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1255;
            U64_delete(i, &(Bool){1});
            *offset = _t1255;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1258 = U64_clone(&(U64){new_cap});
    (void)_t1258;
    ;
    Vec *_t1259 = Vec_clone(&self->type_names);
    (void)_t1259;
    Vec *_t1260 = Vec_clone(&self->type_sizes);
    (void)_t1260;
    Tuple *_t1261 = malloc(sizeof(Tuple));
    _t1261->data = new_data;
    _t1261->total_size = self->total_size;
    _t1261->cap = _t1258;
    { Vec *_ca = Vec_clone(_t1259); _t1261->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1260); _t1261->type_sizes = *_ca; free(_ca); }
    (void)_t1261;
    ;
    Vec_delete(_t1259, &(Bool){1});
    Vec_delete(_t1260, &(Bool){1});
    return _t1261;
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
    Bool _t1329; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1329 = *_hp; free(_hp); }
    (void)_t1329;
    if (_t1329) {
        Bool _t1263; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1263 = *_hp; free(_hp); }
        (void)_t1263;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1263; return _r; }
    }
    ;
    Bool _t1330; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1330 = *_hp; free(_hp); }
    (void)_t1330;
    if (_t1330) {
        Bool _t1264; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1264 = *_hp; free(_hp); }
        (void)_t1264;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1264; return _r; }
    }
    ;
    Bool _t1331; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Bool _t1265; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1265 = *_hp; free(_hp); }
        (void)_t1265;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1265; return _r; }
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1266; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1266 = *_hp; free(_hp); }
        (void)_t1266;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1266; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1267; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1267 = *_hp; free(_hp); }
        (void)_t1267;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1267; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1268; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1268 = *_hp; free(_hp); }
        (void)_t1268;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1268; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1269; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1269 = *_hp; free(_hp); }
        (void)_t1269;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1269; return _r; }
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Bool _t1270; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1270 = *_hp; free(_hp); }
        (void)_t1270;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1270; return _r; }
    }
    ;
    Bool _t1337; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1337 = *_hp; free(_hp); }
    (void)_t1337;
    if (_t1337) {
        Bool _t1271; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1271 = *_hp; free(_hp); }
        (void)_t1271;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1271; return _r; }
    }
    ;
    Bool _t1338; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        Bool _t1272; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1272 = *_hp; free(_hp); }
        (void)_t1272;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1272; return _r; }
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        Bool _t1273; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1273 = *_hp; free(_hp); }
        (void)_t1273;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1273; return _r; }
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        Bool _t1274; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1274 = *_hp; free(_hp); }
        (void)_t1274;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1274; return _r; }
    }
    ;
    Bool _t1341; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1341 = *_hp; free(_hp); }
    (void)_t1341;
    if (_t1341) {
        Bool _t1275; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1275 = *_hp; free(_hp); }
        (void)_t1275;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1275; return _r; }
    }
    ;
    Bool _t1342; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1342 = *_hp; free(_hp); }
    (void)_t1342;
    if (_t1342) {
        Bool _t1276; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1276 = *_hp; free(_hp); }
        (void)_t1276;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1276; return _r; }
    }
    ;
    Bool _t1343; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1343 = *_hp; free(_hp); }
    (void)_t1343;
    if (_t1343) {
        Bool _t1277; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1277 = *_hp; free(_hp); }
        (void)_t1277;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1277; return _r; }
    }
    ;
    Bool _t1344; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1344 = *_hp; free(_hp); }
    (void)_t1344;
    if (_t1344) {
        Bool _t1278; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1278 = *_hp; free(_hp); }
        (void)_t1278;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1278; return _r; }
    }
    ;
    Bool _t1345; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1345 = *_hp; free(_hp); }
    (void)_t1345;
    if (_t1345) {
        Bool _t1279; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1279 = *_hp; free(_hp); }
        (void)_t1279;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1279; return _r; }
    }
    ;
    Bool _t1346; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t1346 = *_hp; free(_hp); }
    (void)_t1346;
    if (_t1346) {
        Bool _t1280; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t1280 = *_hp; free(_hp); }
        (void)_t1280;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1280; return _r; }
    }
    ;
    Bool _t1347; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1347 = *_hp; free(_hp); }
    (void)_t1347;
    if (_t1347) {
        Bool _t1281; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1281 = *_hp; free(_hp); }
        (void)_t1281;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1281; return _r; }
    }
    ;
    Bool _t1348; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1348 = *_hp; free(_hp); }
    (void)_t1348;
    if (_t1348) {
        Bool _t1282; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1282 = *_hp; free(_hp); }
        (void)_t1282;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1282; return _r; }
    }
    ;
    Bool _t1349; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        Bool _t1283; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1283 = *_hp; free(_hp); }
        (void)_t1283;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1283; return _r; }
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        Bool _t1284; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1284 = *_hp; free(_hp); }
        (void)_t1284;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1284; return _r; }
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        Bool _t1285; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1285 = *_hp; free(_hp); }
        (void)_t1285;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1285; return _r; }
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        Bool _t1286; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1286 = *_hp; free(_hp); }
        (void)_t1286;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1286; return _r; }
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        Bool _t1287; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1287 = *_hp; free(_hp); }
        (void)_t1287;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1287; return _r; }
    }
    ;
    Bool _t1354; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1354 = *_hp; free(_hp); }
    (void)_t1354;
    if (_t1354) {
        Bool _t1288; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1288 = *_hp; free(_hp); }
        (void)_t1288;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1288; return _r; }
    }
    ;
    Bool _t1355; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1355 = *_hp; free(_hp); }
    (void)_t1355;
    if (_t1355) {
        Bool _t1289; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1289 = *_hp; free(_hp); }
        (void)_t1289;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1289; return _r; }
    }
    ;
    Bool _t1356; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1356 = *_hp; free(_hp); }
    (void)_t1356;
    if (_t1356) {
        Bool _t1290; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1290 = *_hp; free(_hp); }
        (void)_t1290;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1290; return _r; }
    }
    ;
    Bool _t1357; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1357 = *_hp; free(_hp); }
    (void)_t1357;
    if (_t1357) {
        Bool _t1291; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1291 = *_hp; free(_hp); }
        (void)_t1291;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1291; return _r; }
    }
    ;
    Bool _t1358; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1358 = *_hp; free(_hp); }
    (void)_t1358;
    if (_t1358) {
        Bool _t1292; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1292 = *_hp; free(_hp); }
        (void)_t1292;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1292; return _r; }
    }
    ;
    Bool _t1359; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1359 = *_hp; free(_hp); }
    (void)_t1359;
    if (_t1359) {
        Bool _t1293; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1293 = *_hp; free(_hp); }
        (void)_t1293;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1293; return _r; }
    }
    ;
    Bool _t1360; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1360 = *_hp; free(_hp); }
    (void)_t1360;
    if (_t1360) {
        Bool _t1294; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1294 = *_hp; free(_hp); }
        (void)_t1294;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1294; return _r; }
    }
    ;
    Bool _t1361; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1361 = *_hp; free(_hp); }
    (void)_t1361;
    if (_t1361) {
        Bool _t1295; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1295 = *_hp; free(_hp); }
        (void)_t1295;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1295; return _r; }
    }
    ;
    Bool _t1362; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    if (_t1362) {
        Bool _t1296; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1296 = *_hp; free(_hp); }
        (void)_t1296;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1296; return _r; }
    }
    ;
    Bool _t1363; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1363 = *_hp; free(_hp); }
    (void)_t1363;
    if (_t1363) {
        Bool _t1297; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1297 = *_hp; free(_hp); }
        (void)_t1297;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1297; return _r; }
    }
    ;
    Bool _t1364; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1364 = *_hp; free(_hp); }
    (void)_t1364;
    if (_t1364) {
        Bool _t1298; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1298 = *_hp; free(_hp); }
        (void)_t1298;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1298; return _r; }
    }
    ;
    Bool _t1365; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1365 = *_hp; free(_hp); }
    (void)_t1365;
    if (_t1365) {
        Bool _t1299; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1299 = *_hp; free(_hp); }
        (void)_t1299;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1299; return _r; }
    }
    ;
    Bool _t1366; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    if (_t1366) {
        Bool _t1300; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1300 = *_hp; free(_hp); }
        (void)_t1300;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1300; return _r; }
    }
    ;
    Bool _t1367; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    if (_t1367) {
        Bool _t1301; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1301 = *_hp; free(_hp); }
        (void)_t1301;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1301; return _r; }
    }
    ;
    Bool _t1368; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        Bool _t1302; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1302 = *_hp; free(_hp); }
        (void)_t1302;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1302; return _r; }
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        Bool _t1303; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1303 = *_hp; free(_hp); }
        (void)_t1303;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1303; return _r; }
    }
    ;
    Bool _t1370; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    if (_t1370) {
        Bool _t1304; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1304 = *_hp; free(_hp); }
        (void)_t1304;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1304; return _r; }
    }
    ;
    Bool _t1371; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1371 = *_hp; free(_hp); }
    (void)_t1371;
    if (_t1371) {
        Bool _t1305; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1305 = *_hp; free(_hp); }
        (void)_t1305;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1305; return _r; }
    }
    ;
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        Bool _t1306; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1306 = *_hp; free(_hp); }
        (void)_t1306;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1306; return _r; }
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Bool _t1307; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1307 = *_hp; free(_hp); }
        (void)_t1307;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1307; return _r; }
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Bool _t1308; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1308 = *_hp; free(_hp); }
        (void)_t1308;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1308; return _r; }
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Bool _t1309; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1309 = *_hp; free(_hp); }
        (void)_t1309;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1309; return _r; }
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Bool _t1310; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1310 = *_hp; free(_hp); }
        (void)_t1310;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1310; return _r; }
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Bool _t1311; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1311 = *_hp; free(_hp); }
        (void)_t1311;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1311; return _r; }
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Bool _t1312; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1312 = *_hp; free(_hp); }
        (void)_t1312;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1312; return _r; }
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Bool _t1313; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1313 = *_hp; free(_hp); }
        (void)_t1313;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1313; return _r; }
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Bool _t1314; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1314 = *_hp; free(_hp); }
        (void)_t1314;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1314; return _r; }
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Bool _t1315; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1315 = *_hp; free(_hp); }
        (void)_t1315;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1315; return _r; }
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Bool _t1316; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1316 = *_hp; free(_hp); }
        (void)_t1316;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1316; return _r; }
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Bool _t1317; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1317 = *_hp; free(_hp); }
        (void)_t1317;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1317; return _r; }
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Bool _t1318; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1318 = *_hp; free(_hp); }
        (void)_t1318;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1318; return _r; }
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Bool _t1319; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1319 = *_hp; free(_hp); }
        (void)_t1319;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1319; return _r; }
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Bool _t1320; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1320 = *_hp; free(_hp); }
        (void)_t1320;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1320; return _r; }
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Bool _t1321; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1321 = *_hp; free(_hp); }
        (void)_t1321;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1321; return _r; }
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Bool _t1322; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1322 = *_hp; free(_hp); }
        (void)_t1322;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1322; return _r; }
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Bool _t1323; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1323 = *_hp; free(_hp); }
        (void)_t1323;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1323; return _r; }
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Bool _t1324; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1324 = *_hp; free(_hp); }
        (void)_t1324;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1324; return _r; }
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Bool _t1325; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1325 = *_hp; free(_hp); }
        (void)_t1325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1325; return _r; }
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Bool _t1326; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1326 = *_hp; free(_hp); }
        (void)_t1326;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1326; return _r; }
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Bool _t1327; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1327 = *_hp; free(_hp); }
        (void)_t1327;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1327; return _r; }
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Bool _t1328; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1328 = *_hp; free(_hp); }
        (void)_t1328;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1328; return _r; }
    }
    ;
    Bool _t1395 = 0;
    (void)_t1395;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1395; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1437 = *_hp; free(_hp); }
    (void)_t1437;
    if (_t1437) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1438 = *_hp; free(_hp); }
    (void)_t1438;
    if (_t1438) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1439; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1439 = *_hp; free(_hp); }
    (void)_t1439;
    if (_t1439) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1440; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1440 = *_hp; free(_hp); }
    (void)_t1440;
    if (_t1440) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1441; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1441 = *_hp; free(_hp); }
    (void)_t1441;
    if (_t1441) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1442; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1442 = *_hp; free(_hp); }
    (void)_t1442;
    if (_t1442) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1443; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1443 = *_hp; free(_hp); }
    (void)_t1443;
    if (_t1443) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1444; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1444 = *_hp; free(_hp); }
    (void)_t1444;
    if (_t1444) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1445; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1445 = *_hp; free(_hp); }
    (void)_t1445;
    if (_t1445) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1446; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1446 = *_hp; free(_hp); }
    (void)_t1446;
    if (_t1446) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1447; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1447 = *_hp; free(_hp); }
    (void)_t1447;
    if (_t1447) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1448; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1448 = *_hp; free(_hp); }
    (void)_t1448;
    if (_t1448) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1449; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1449 = *_hp; free(_hp); }
    (void)_t1449;
    if (_t1449) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1450; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    if (_t1450) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1451; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    if (_t1451) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1452; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1452 = *_hp; free(_hp); }
    (void)_t1452;
    if (_t1452) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1453; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1453 = *_hp; free(_hp); }
    (void)_t1453;
    if (_t1453) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1454; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    if (_t1454) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1455; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    if (_t1455) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1456; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    if (_t1456) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1457; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1457 = *_hp; free(_hp); }
    (void)_t1457;
    if (_t1457) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1458; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1458 = *_hp; free(_hp); }
    (void)_t1458;
    if (_t1458) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1459; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    if (_t1459) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1460; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    if (_t1460) {
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
    Bool _t1527; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        Str *_t1461 = Str_lit("Eof", 3ULL);
        (void)_t1461;
        ;
        return _t1461;
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        Str *_t1462 = Str_lit("LParen", 6ULL);
        (void)_t1462;
        ;
        return _t1462;
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Str *_t1463 = Str_lit("RParen", 6ULL);
        (void)_t1463;
        ;
        return _t1463;
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Str *_t1464 = Str_lit("LBrace", 6ULL);
        (void)_t1464;
        ;
        return _t1464;
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        Str *_t1465 = Str_lit("RBrace", 6ULL);
        (void)_t1465;
        ;
        return _t1465;
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        Str *_t1466 = Str_lit("LBracket", 8ULL);
        (void)_t1466;
        ;
        return _t1466;
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        Str *_t1467 = Str_lit("RBracket", 8ULL);
        (void)_t1467;
        ;
        return _t1467;
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        Str *_t1468 = Str_lit("Comma", 5ULL);
        (void)_t1468;
        ;
        return _t1468;
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
        Str *_t1469 = Str_lit("Colon", 5ULL);
        (void)_t1469;
        ;
        return _t1469;
    }
    ;
    Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1536 = *_hp; free(_hp); }
    (void)_t1536;
    if (_t1536) {
        Str *_t1470 = Str_lit("Question", 8ULL);
        (void)_t1470;
        ;
        return _t1470;
    }
    ;
    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1537 = *_hp; free(_hp); }
    (void)_t1537;
    if (_t1537) {
        Str *_t1471 = Str_lit("Bang", 4ULL);
        (void)_t1471;
        ;
        return _t1471;
    }
    ;
    Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1538 = *_hp; free(_hp); }
    (void)_t1538;
    if (_t1538) {
        Str *_t1472 = Str_lit("Minus", 5ULL);
        (void)_t1472;
        ;
        return _t1472;
    }
    ;
    Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1539 = *_hp; free(_hp); }
    (void)_t1539;
    if (_t1539) {
        Str *_t1473 = Str_lit("Plus", 4ULL);
        (void)_t1473;
        ;
        return _t1473;
    }
    ;
    Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1540 = *_hp; free(_hp); }
    (void)_t1540;
    if (_t1540) {
        Str *_t1474 = Str_lit("Star", 4ULL);
        (void)_t1474;
        ;
        return _t1474;
    }
    ;
    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1541 = *_hp; free(_hp); }
    (void)_t1541;
    if (_t1541) {
        Str *_t1475 = Str_lit("Slash", 5ULL);
        (void)_t1475;
        ;
        return _t1475;
    }
    ;
    Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1542 = *_hp; free(_hp); }
    (void)_t1542;
    if (_t1542) {
        Str *_t1476 = Str_lit("Dot", 3ULL);
        (void)_t1476;
        ;
        return _t1476;
    }
    ;
    Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1543 = *_hp; free(_hp); }
    (void)_t1543;
    if (_t1543) {
        Str *_t1477 = Str_lit("DotDot", 6ULL);
        (void)_t1477;
        ;
        return _t1477;
    }
    ;
    Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1544 = *_hp; free(_hp); }
    (void)_t1544;
    if (_t1544) {
        Str *_t1478 = Str_lit("DotDotDot", 9ULL);
        (void)_t1478;
        ;
        return _t1478;
    }
    ;
    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1545 = *_hp; free(_hp); }
    (void)_t1545;
    if (_t1545) {
        Str *_t1479 = Str_lit("Eq", 2ULL);
        (void)_t1479;
        ;
        return _t1479;
    }
    ;
    Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1546 = *_hp; free(_hp); }
    (void)_t1546;
    if (_t1546) {
        Str *_t1480 = Str_lit("EqEq", 4ULL);
        (void)_t1480;
        ;
        return _t1480;
    }
    ;
    Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1547 = *_hp; free(_hp); }
    (void)_t1547;
    if (_t1547) {
        Str *_t1481 = Str_lit("Neq", 3ULL);
        (void)_t1481;
        ;
        return _t1481;
    }
    ;
    Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1548 = *_hp; free(_hp); }
    (void)_t1548;
    if (_t1548) {
        Str *_t1482 = Str_lit("Lt", 2ULL);
        (void)_t1482;
        ;
        return _t1482;
    }
    ;
    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1549 = *_hp; free(_hp); }
    (void)_t1549;
    if (_t1549) {
        Str *_t1483 = Str_lit("LtEq", 4ULL);
        (void)_t1483;
        ;
        return _t1483;
    }
    ;
    Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1550 = *_hp; free(_hp); }
    (void)_t1550;
    if (_t1550) {
        Str *_t1484 = Str_lit("Gt", 2ULL);
        (void)_t1484;
        ;
        return _t1484;
    }
    ;
    Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1551 = *_hp; free(_hp); }
    (void)_t1551;
    if (_t1551) {
        Str *_t1485 = Str_lit("GtEq", 4ULL);
        (void)_t1485;
        ;
        return _t1485;
    }
    ;
    Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1552 = *_hp; free(_hp); }
    (void)_t1552;
    if (_t1552) {
        Str *_t1486 = Str_lit("ColonEq", 7ULL);
        (void)_t1486;
        ;
        return _t1486;
    }
    ;
    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1553 = *_hp; free(_hp); }
    (void)_t1553;
    if (_t1553) {
        Str *_t1487 = Str_lit("Ident", 5ULL);
        (void)_t1487;
        ;
        return _t1487;
    }
    ;
    Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1554 = *_hp; free(_hp); }
    (void)_t1554;
    if (_t1554) {
        Str *_t1488 = Str_lit("StringTok", 9ULL);
        (void)_t1488;
        ;
        return _t1488;
    }
    ;
    Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1555 = *_hp; free(_hp); }
    (void)_t1555;
    if (_t1555) {
        Str *_t1489 = Str_lit("Number", 6ULL);
        (void)_t1489;
        ;
        return _t1489;
    }
    ;
    Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1556 = *_hp; free(_hp); }
    (void)_t1556;
    if (_t1556) {
        Str *_t1490 = Str_lit("Char", 4ULL);
        (void)_t1490;
        ;
        return _t1490;
    }
    ;
    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1557 = *_hp; free(_hp); }
    (void)_t1557;
    if (_t1557) {
        Str *_t1491 = Str_lit("KwMode", 6ULL);
        (void)_t1491;
        ;
        return _t1491;
    }
    ;
    Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1558 = *_hp; free(_hp); }
    (void)_t1558;
    if (_t1558) {
        Str *_t1492 = Str_lit("KwMut", 5ULL);
        (void)_t1492;
        ;
        return _t1492;
    }
    ;
    Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1559 = *_hp; free(_hp); }
    (void)_t1559;
    if (_t1559) {
        Str *_t1493 = Str_lit("KwOwn", 5ULL);
        (void)_t1493;
        ;
        return _t1493;
    }
    ;
    Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1560 = *_hp; free(_hp); }
    (void)_t1560;
    if (_t1560) {
        Str *_t1494 = Str_lit("KwRef", 5ULL);
        (void)_t1494;
        ;
        return _t1494;
    }
    ;
    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1561 = *_hp; free(_hp); }
    (void)_t1561;
    if (_t1561) {
        Str *_t1495 = Str_lit("KwShallow", 9ULL);
        (void)_t1495;
        ;
        return _t1495;
    }
    ;
    Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1562 = *_hp; free(_hp); }
    (void)_t1562;
    if (_t1562) {
        Str *_t1496 = Str_lit("KwStruct", 8ULL);
        (void)_t1496;
        ;
        return _t1496;
    }
    ;
    Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1563 = *_hp; free(_hp); }
    (void)_t1563;
    if (_t1563) {
        Str *_t1497 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1497;
        ;
        return _t1497;
    }
    ;
    Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1564 = *_hp; free(_hp); }
    (void)_t1564;
    if (_t1564) {
        Str *_t1498 = Str_lit("KwEnum", 6ULL);
        (void)_t1498;
        ;
        return _t1498;
    }
    ;
    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1565 = *_hp; free(_hp); }
    (void)_t1565;
    if (_t1565) {
        Str *_t1499 = Str_lit("KwNamespace", 11ULL);
        (void)_t1499;
        ;
        return _t1499;
    }
    ;
    Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1566 = *_hp; free(_hp); }
    (void)_t1566;
    if (_t1566) {
        Str *_t1500 = Str_lit("KwFunc", 6ULL);
        (void)_t1500;
        ;
        return _t1500;
    }
    ;
    Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1567 = *_hp; free(_hp); }
    (void)_t1567;
    if (_t1567) {
        Str *_t1501 = Str_lit("KwProc", 6ULL);
        (void)_t1501;
        ;
        return _t1501;
    }
    ;
    Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1568 = *_hp; free(_hp); }
    (void)_t1568;
    if (_t1568) {
        Str *_t1502 = Str_lit("KwTest", 6ULL);
        (void)_t1502;
        ;
        return _t1502;
    }
    ;
    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1569 = *_hp; free(_hp); }
    (void)_t1569;
    if (_t1569) {
        Str *_t1503 = Str_lit("KwMacro", 7ULL);
        (void)_t1503;
        ;
        return _t1503;
    }
    ;
    Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1570 = *_hp; free(_hp); }
    (void)_t1570;
    if (_t1570) {
        Str *_t1504 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1504;
        ;
        return _t1504;
    }
    ;
    Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1571 = *_hp; free(_hp); }
    (void)_t1571;
    if (_t1571) {
        Str *_t1505 = Str_lit("KwExtProc", 9ULL);
        (void)_t1505;
        ;
        return _t1505;
    }
    ;
    Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1572 = *_hp; free(_hp); }
    (void)_t1572;
    if (_t1572) {
        Str *_t1506 = Str_lit("KwReturns", 9ULL);
        (void)_t1506;
        ;
        return _t1506;
    }
    ;
    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1573 = *_hp; free(_hp); }
    (void)_t1573;
    if (_t1573) {
        Str *_t1507 = Str_lit("KwThrows", 8ULL);
        (void)_t1507;
        ;
        return _t1507;
    }
    ;
    Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1574 = *_hp; free(_hp); }
    (void)_t1574;
    if (_t1574) {
        Str *_t1508 = Str_lit("KwIf", 4ULL);
        (void)_t1508;
        ;
        return _t1508;
    }
    ;
    Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1575 = *_hp; free(_hp); }
    (void)_t1575;
    if (_t1575) {
        Str *_t1509 = Str_lit("KwElse", 6ULL);
        (void)_t1509;
        ;
        return _t1509;
    }
    ;
    Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1576 = *_hp; free(_hp); }
    (void)_t1576;
    if (_t1576) {
        Str *_t1510 = Str_lit("KwWhile", 7ULL);
        (void)_t1510;
        ;
        return _t1510;
    }
    ;
    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1577 = *_hp; free(_hp); }
    (void)_t1577;
    if (_t1577) {
        Str *_t1511 = Str_lit("KwFor", 5ULL);
        (void)_t1511;
        ;
        return _t1511;
    }
    ;
    Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1578 = *_hp; free(_hp); }
    (void)_t1578;
    if (_t1578) {
        Str *_t1512 = Str_lit("KwIn", 4ULL);
        (void)_t1512;
        ;
        return _t1512;
    }
    ;
    Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1579 = *_hp; free(_hp); }
    (void)_t1579;
    if (_t1579) {
        Str *_t1513 = Str_lit("KwSwitch", 8ULL);
        (void)_t1513;
        ;
        return _t1513;
    }
    ;
    Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1580 = *_hp; free(_hp); }
    (void)_t1580;
    if (_t1580) {
        Str *_t1514 = Str_lit("KwMatch", 7ULL);
        (void)_t1514;
        ;
        return _t1514;
    }
    ;
    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1581 = *_hp; free(_hp); }
    (void)_t1581;
    if (_t1581) {
        Str *_t1515 = Str_lit("KwCase", 6ULL);
        (void)_t1515;
        ;
        return _t1515;
    }
    ;
    Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1582 = *_hp; free(_hp); }
    (void)_t1582;
    if (_t1582) {
        Str *_t1516 = Str_lit("KwDefault", 9ULL);
        (void)_t1516;
        ;
        return _t1516;
    }
    ;
    Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1583 = *_hp; free(_hp); }
    (void)_t1583;
    if (_t1583) {
        Str *_t1517 = Str_lit("KwReturn", 8ULL);
        (void)_t1517;
        ;
        return _t1517;
    }
    ;
    Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1584 = *_hp; free(_hp); }
    (void)_t1584;
    if (_t1584) {
        Str *_t1518 = Str_lit("KwThrow", 7ULL);
        (void)_t1518;
        ;
        return _t1518;
    }
    ;
    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1585 = *_hp; free(_hp); }
    (void)_t1585;
    if (_t1585) {
        Str *_t1519 = Str_lit("KwCatch", 7ULL);
        (void)_t1519;
        ;
        return _t1519;
    }
    ;
    Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1586 = *_hp; free(_hp); }
    (void)_t1586;
    if (_t1586) {
        Str *_t1520 = Str_lit("KwBreak", 7ULL);
        (void)_t1520;
        ;
        return _t1520;
    }
    ;
    Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1587 = *_hp; free(_hp); }
    (void)_t1587;
    if (_t1587) {
        Str *_t1521 = Str_lit("KwContinue", 10ULL);
        (void)_t1521;
        ;
        return _t1521;
    }
    ;
    Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1588 = *_hp; free(_hp); }
    (void)_t1588;
    if (_t1588) {
        Str *_t1522 = Str_lit("KwDefer", 7ULL);
        (void)_t1522;
        ;
        return _t1522;
    }
    ;
    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1589 = *_hp; free(_hp); }
    (void)_t1589;
    if (_t1589) {
        Str *_t1523 = Str_lit("KwTrue", 6ULL);
        (void)_t1523;
        ;
        return _t1523;
    }
    ;
    Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1590 = *_hp; free(_hp); }
    (void)_t1590;
    if (_t1590) {
        Str *_t1524 = Str_lit("KwFalse", 7ULL);
        (void)_t1524;
        ;
        return _t1524;
    }
    ;
    Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1591 = *_hp; free(_hp); }
    (void)_t1591;
    if (_t1591) {
        Str *_t1525 = Str_lit("KwNull", 6ULL);
        (void)_t1525;
        ;
        return _t1525;
    }
    ;
    Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1592 = *_hp; free(_hp); }
    (void)_t1592;
    if (_t1592) {
        Str *_t1526 = Str_lit("Error", 5ULL);
        (void)_t1526;
        ;
        return _t1526;
    }
    ;
    Str *_t1593 = Str_lit("unknown", 7ULL);
    (void)_t1593;
    return _t1593;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1595 = I64_clone(&self->line);
    (void)_t1595;
    I64 _t1596 = I64_clone(&self->col);
    (void)_t1596;
    Token *_t1597 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1597->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1597->text = *_ca; free(_ca); }
    _t1597->line = _t1595;
    _t1597->col = _t1596;
    (void)_t1597;
    ;
    ;
    return _t1597;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1598 = 0;
    (void)_t1598;
    TokenType_delete(&self->type, &(Bool){_t1598});
    ;
    Bool _t1599 = 0;
    (void)_t1599;
    Str_delete(&self->text, &(Bool){_t1599});
    ;
    Bool _t1600 = 0;
    (void)_t1600;
    I64_delete(&self->line, &(Bool){_t1600});
    ;
    Bool _t1601 = 0;
    (void)_t1601;
    I64_delete(&self->col, &(Bool){_t1601});
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
    U8 _t1603 = 48;
    (void)_t1603;
    U8 _t1604 = 57;
    (void)_t1604;
    Bool _t1605; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1603}); _t1605 = *_hp; free(_hp); }
    (void)_t1605;
    ;
    Bool _t1606; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1604}); _t1606 = *_hp; free(_hp); }
    (void)_t1606;
    ;
    Bool _t1607 = Bool_and(_t1605, _t1606);
    (void)_t1607;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1607; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1608 = 97;
    (void)_t1608;
    U8 _t1609 = 122;
    (void)_t1609;
    Bool _t1610; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1608}); _t1610 = *_hp; free(_hp); }
    (void)_t1610;
    ;
    Bool _t1611; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1609}); _t1611 = *_hp; free(_hp); }
    (void)_t1611;
    ;
    U8 _t1612 = 65;
    (void)_t1612;
    U8 _t1613 = 90;
    (void)_t1613;
    Bool _t1614; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1612}); _t1614 = *_hp; free(_hp); }
    (void)_t1614;
    ;
    Bool _t1615; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1613}); _t1615 = *_hp; free(_hp); }
    (void)_t1615;
    ;
    Bool _t1616 = Bool_and(_t1610, _t1611);
    (void)_t1616;
    ;
    ;
    Bool _t1617 = Bool_and(_t1614, _t1615);
    (void)_t1617;
    ;
    ;
    U8 _t1618 = 95;
    (void)_t1618;
    Bool _t1619 = Bool_or(_t1616, _t1617);
    (void)_t1619;
    ;
    ;
    Bool _t1620 = U8_eq(DEREF(c), _t1618);
    (void)_t1620;
    ;
    Bool _t1621 = Bool_or(_t1619, _t1620);
    (void)_t1621;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1621; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1622; { Bool *_hp = (Bool *)is_alpha(c); _t1622 = *_hp; free(_hp); }
    (void)_t1622;
    Bool _t1623; { Bool *_hp = (Bool *)is_digit(c); _t1623 = *_hp; free(_hp); }
    (void)_t1623;
    Bool _t1624 = Bool_or(_t1622, _t1623);
    (void)_t1624;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1624; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1625 = TokenType_clone(type);
        (void)_sw1625;
        Bool _t1758; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Eof()); _t1758 = *_hp; free(_hp); }
        (void)_t1758;
        if (_t1758) {
            Str *_t1626 = Str_lit("eof", 3ULL);
            (void)_t1626;
            TokenType_delete(_sw1625, &(Bool){1});
            ;
            return _t1626;
        } else {
            Bool _t1757; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LParen()); _t1757 = *_hp; free(_hp); }
            (void)_t1757;
            if (_t1757) {
                Str *_t1627 = Str_lit("(", 1ULL);
                (void)_t1627;
                ;
                TokenType_delete(_sw1625, &(Bool){1});
                ;
                return _t1627;
            } else {
                Bool _t1756; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RParen()); _t1756 = *_hp; free(_hp); }
                (void)_t1756;
                if (_t1756) {
                    Str *_t1628 = Str_lit(")", 1ULL);
                    (void)_t1628;
                    ;
                    ;
                    TokenType_delete(_sw1625, &(Bool){1});
                    ;
                    return _t1628;
                } else {
                    Bool _t1755; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LBrace()); _t1755 = *_hp; free(_hp); }
                    (void)_t1755;
                    if (_t1755) {
                        Str *_t1629 = Str_lit("{", 1ULL);
                        (void)_t1629;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1625, &(Bool){1});
                        ;
                        return _t1629;
                    } else {
                        Bool _t1754; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RBrace()); _t1754 = *_hp; free(_hp); }
                        (void)_t1754;
                        if (_t1754) {
                            Str *_t1630 = Str_lit("}", 1ULL);
                            (void)_t1630;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1625, &(Bool){1});
                            ;
                            return _t1630;
                        } else {
                            Bool _t1753; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LBracket()); _t1753 = *_hp; free(_hp); }
                            (void)_t1753;
                            if (_t1753) {
                                Str *_t1631 = Str_lit("[", 1ULL);
                                (void)_t1631;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1625, &(Bool){1});
                                ;
                                return _t1631;
                            } else {
                                Bool _t1752; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_RBracket()); _t1752 = *_hp; free(_hp); }
                                (void)_t1752;
                                if (_t1752) {
                                    Str *_t1632 = Str_lit("]", 1ULL);
                                    (void)_t1632;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1625, &(Bool){1});
                                    ;
                                    return _t1632;
                                } else {
                                    Bool _t1751; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Comma()); _t1751 = *_hp; free(_hp); }
                                    (void)_t1751;
                                    if (_t1751) {
                                        Str *_t1633 = Str_lit(",", 1ULL);
                                        (void)_t1633;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1625, &(Bool){1});
                                        ;
                                        return _t1633;
                                    } else {
                                        Bool _t1750; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Colon()); _t1750 = *_hp; free(_hp); }
                                        (void)_t1750;
                                        if (_t1750) {
                                            Str *_t1634 = Str_lit(":", 1ULL);
                                            (void)_t1634;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1625, &(Bool){1});
                                            ;
                                            return _t1634;
                                        } else {
                                            Bool _t1749; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Question()); _t1749 = *_hp; free(_hp); }
                                            (void)_t1749;
                                            if (_t1749) {
                                                Str *_t1635 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw1625, &(Bool){1});
                                                ;
                                                return _t1635;
                                            } else {
                                                Bool _t1748; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Bang()); _t1748 = *_hp; free(_hp); }
                                                (void)_t1748;
                                                if (_t1748) {
                                                    Str *_t1636 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                    ;
                                                    return _t1636;
                                                } else {
                                                    Bool _t1747; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Minus()); _t1747 = *_hp; free(_hp); }
                                                    (void)_t1747;
                                                    if (_t1747) {
                                                        Str *_t1637 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                        ;
                                                        return _t1637;
                                                    } else {
                                                        Bool _t1746; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Plus()); _t1746 = *_hp; free(_hp); }
                                                        (void)_t1746;
                                                        if (_t1746) {
                                                            Str *_t1638 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                            ;
                                                            return _t1638;
                                                        } else {
                                                            Bool _t1745; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Star()); _t1745 = *_hp; free(_hp); }
                                                            (void)_t1745;
                                                            if (_t1745) {
                                                                Str *_t1639 = Str_lit("*", 1ULL);
                                                                (void)_t1639;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                ;
                                                                return _t1639;
                                                            } else {
                                                                Bool _t1744; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Slash()); _t1744 = *_hp; free(_hp); }
                                                                (void)_t1744;
                                                                if (_t1744) {
                                                                    Str *_t1640 = Str_lit("/", 1ULL);
                                                                    (void)_t1640;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                    ;
                                                                    return _t1640;
                                                                } else {
                                                                    Bool _t1743; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Dot()); _t1743 = *_hp; free(_hp); }
                                                                    (void)_t1743;
                                                                    if (_t1743) {
                                                                        Str *_t1641 = Str_lit(".", 1ULL);
                                                                        (void)_t1641;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                        ;
                                                                        return _t1641;
                                                                    } else {
                                                                        Bool _t1742; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_DotDot()); _t1742 = *_hp; free(_hp); }
                                                                        (void)_t1742;
                                                                        if (_t1742) {
                                                                            Str *_t1642 = Str_lit("..", 2ULL);
                                                                            (void)_t1642;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                            ;
                                                                            return _t1642;
                                                                        } else {
                                                                            Bool _t1741; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_DotDotDot()); _t1741 = *_hp; free(_hp); }
                                                                            (void)_t1741;
                                                                            if (_t1741) {
                                                                                Str *_t1643 = Str_lit("...", 3ULL);
                                                                                (void)_t1643;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                ;
                                                                                return _t1643;
                                                                            } else {
                                                                                Bool _t1740; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Eq()); _t1740 = *_hp; free(_hp); }
                                                                                (void)_t1740;
                                                                                if (_t1740) {
                                                                                    Str *_t1644 = Str_lit("=", 1ULL);
                                                                                    (void)_t1644;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                    ;
                                                                                    return _t1644;
                                                                                } else {
                                                                                    Bool _t1739; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_EqEq()); _t1739 = *_hp; free(_hp); }
                                                                                    (void)_t1739;
                                                                                    if (_t1739) {
                                                                                        Str *_t1645 = Str_lit("==", 2ULL);
                                                                                        (void)_t1645;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                        ;
                                                                                        return _t1645;
                                                                                    } else {
                                                                                        Bool _t1738; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Neq()); _t1738 = *_hp; free(_hp); }
                                                                                        (void)_t1738;
                                                                                        if (_t1738) {
                                                                                            Str *_t1646 = Str_lit("!=", 2ULL);
                                                                                            (void)_t1646;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                            ;
                                                                                            return _t1646;
                                                                                        } else {
                                                                                            Bool _t1737; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Lt()); _t1737 = *_hp; free(_hp); }
                                                                                            (void)_t1737;
                                                                                            if (_t1737) {
                                                                                                Str *_t1647 = Str_lit("<", 1ULL);
                                                                                                (void)_t1647;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                ;
                                                                                                return _t1647;
                                                                                            } else {
                                                                                                Bool _t1736; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_LtEq()); _t1736 = *_hp; free(_hp); }
                                                                                                (void)_t1736;
                                                                                                if (_t1736) {
                                                                                                    Str *_t1648 = Str_lit("<=", 2ULL);
                                                                                                    (void)_t1648;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1648;
                                                                                                } else {
                                                                                                    Bool _t1735; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Gt()); _t1735 = *_hp; free(_hp); }
                                                                                                    (void)_t1735;
                                                                                                    if (_t1735) {
                                                                                                        Str *_t1649 = Str_lit(">", 1ULL);
                                                                                                        (void)_t1649;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1649;
                                                                                                    } else {
                                                                                                        Bool _t1734; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_GtEq()); _t1734 = *_hp; free(_hp); }
                                                                                                        (void)_t1734;
                                                                                                        if (_t1734) {
                                                                                                            Str *_t1650 = Str_lit(">=", 2ULL);
                                                                                                            (void)_t1650;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1650;
                                                                                                        } else {
                                                                                                            Bool _t1733; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_ColonEq()); _t1733 = *_hp; free(_hp); }
                                                                                                            (void)_t1733;
                                                                                                            if (_t1733) {
                                                                                                                Str *_t1651 = Str_lit(":=", 2ULL);
                                                                                                                (void)_t1651;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1651;
                                                                                                            } else {
                                                                                                                Bool _t1732; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Ident()); _t1732 = *_hp; free(_hp); }
                                                                                                                (void)_t1732;
                                                                                                                if (_t1732) {
                                                                                                                    Str *_t1652 = Str_lit("identifier", 10ULL);
                                                                                                                    (void)_t1652;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1652;
                                                                                                                } else {
                                                                                                                    Bool _t1731; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_StringTok()); _t1731 = *_hp; free(_hp); }
                                                                                                                    (void)_t1731;
                                                                                                                    if (_t1731) {
                                                                                                                        Str *_t1653 = Str_lit("string", 6ULL);
                                                                                                                        (void)_t1653;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1653;
                                                                                                                    } else {
                                                                                                                        Bool _t1730; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Number()); _t1730 = *_hp; free(_hp); }
                                                                                                                        (void)_t1730;
                                                                                                                        if (_t1730) {
                                                                                                                            Str *_t1654 = Str_lit("number", 6ULL);
                                                                                                                            (void)_t1654;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1654;
                                                                                                                        } else {
                                                                                                                            Bool _t1729; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Char()); _t1729 = *_hp; free(_hp); }
                                                                                                                            (void)_t1729;
                                                                                                                            if (_t1729) {
                                                                                                                                Str *_t1655 = Str_lit("char", 4ULL);
                                                                                                                                (void)_t1655;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1655;
                                                                                                                            } else {
                                                                                                                                Bool _t1728; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMode()); _t1728 = *_hp; free(_hp); }
                                                                                                                                (void)_t1728;
                                                                                                                                if (_t1728) {
                                                                                                                                    Str *_t1656 = Str_lit("mode", 4ULL);
                                                                                                                                    (void)_t1656;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1656;
                                                                                                                                } else {
                                                                                                                                    Bool _t1727; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMut()); _t1727 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1727;
                                                                                                                                    if (_t1727) {
                                                                                                                                        Str *_t1657 = Str_lit("mut", 3ULL);
                                                                                                                                        (void)_t1657;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1657;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1726; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwOwn()); _t1726 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1726;
                                                                                                                                        if (_t1726) {
                                                                                                                                            Str *_t1658 = Str_lit("own", 3ULL);
                                                                                                                                            (void)_t1658;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1658;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1725; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwRef()); _t1725 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1725;
                                                                                                                                            if (_t1725) {
                                                                                                                                                Str *_t1659 = Str_lit("ref", 3ULL);
                                                                                                                                                (void)_t1659;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1659;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1724; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwShallow()); _t1724 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1724;
                                                                                                                                                if (_t1724) {
                                                                                                                                                    Str *_t1660 = Str_lit("shallow", 7ULL);
                                                                                                                                                    (void)_t1660;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1660;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1723; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwStruct()); _t1723 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1723;
                                                                                                                                                    if (_t1723) {
                                                                                                                                                        Str *_t1661 = Str_lit("struct", 6ULL);
                                                                                                                                                        (void)_t1661;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1661;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1722; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtStruct()); _t1722 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1722;
                                                                                                                                                        if (_t1722) {
                                                                                                                                                            Str *_t1662 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                            (void)_t1662;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1662;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1721; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwEnum()); _t1721 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1721;
                                                                                                                                                            if (_t1721) {
                                                                                                                                                                Str *_t1663 = Str_lit("enum", 4ULL);
                                                                                                                                                                (void)_t1663;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1663;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1720; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwNamespace()); _t1720 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1720;
                                                                                                                                                                if (_t1720) {
                                                                                                                                                                    Str *_t1664 = Str_lit("namespace", 9ULL);
                                                                                                                                                                    (void)_t1664;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1664;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1719; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFunc()); _t1719 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1719;
                                                                                                                                                                    if (_t1719) {
                                                                                                                                                                        Str *_t1665 = Str_lit("func", 4ULL);
                                                                                                                                                                        (void)_t1665;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1665;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1718; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwProc()); _t1718 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1718;
                                                                                                                                                                        if (_t1718) {
                                                                                                                                                                            Str *_t1666 = Str_lit("proc", 4ULL);
                                                                                                                                                                            (void)_t1666;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1666;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1717; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwTest()); _t1717 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1717;
                                                                                                                                                                            if (_t1717) {
                                                                                                                                                                                Str *_t1667 = Str_lit("test", 4ULL);
                                                                                                                                                                                (void)_t1667;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1667;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1716; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMacro()); _t1716 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1716;
                                                                                                                                                                                if (_t1716) {
                                                                                                                                                                                    Str *_t1668 = Str_lit("macro", 5ULL);
                                                                                                                                                                                    (void)_t1668;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1668;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1715; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtFunc()); _t1715 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1715;
                                                                                                                                                                                    if (_t1715) {
                                                                                                                                                                                        Str *_t1669 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                        (void)_t1669;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1669;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1714; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwExtProc()); _t1714 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1714;
                                                                                                                                                                                        if (_t1714) {
                                                                                                                                                                                            Str *_t1670 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                            (void)_t1670;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1670;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1713; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwReturns()); _t1713 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1713;
                                                                                                                                                                                            if (_t1713) {
                                                                                                                                                                                                Str *_t1671 = Str_lit("returns", 7ULL);
                                                                                                                                                                                                (void)_t1671;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1671;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1712; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwThrows()); _t1712 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1712;
                                                                                                                                                                                                if (_t1712) {
                                                                                                                                                                                                    Str *_t1672 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                    (void)_t1672;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1672;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1711; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwIf()); _t1711 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1711;
                                                                                                                                                                                                    if (_t1711) {
                                                                                                                                                                                                        Str *_t1673 = Str_lit("if", 2ULL);
                                                                                                                                                                                                        (void)_t1673;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1673;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1710; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwElse()); _t1710 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1710;
                                                                                                                                                                                                        if (_t1710) {
                                                                                                                                                                                                            Str *_t1674 = Str_lit("else", 4ULL);
                                                                                                                                                                                                            (void)_t1674;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1674;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1709; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwWhile()); _t1709 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1709;
                                                                                                                                                                                                            if (_t1709) {
                                                                                                                                                                                                                Str *_t1675 = Str_lit("while", 5ULL);
                                                                                                                                                                                                                (void)_t1675;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1675;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1708; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFor()); _t1708 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1708;
                                                                                                                                                                                                                if (_t1708) {
                                                                                                                                                                                                                    Str *_t1676 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                    (void)_t1676;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1676;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1707; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwIn()); _t1707 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1707;
                                                                                                                                                                                                                    if (_t1707) {
                                                                                                                                                                                                                        Str *_t1677 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                        (void)_t1677;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1677;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1706; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwSwitch()); _t1706 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1706;
                                                                                                                                                                                                                        if (_t1706) {
                                                                                                                                                                                                                            Str *_t1678 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                            (void)_t1678;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1678;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1705; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwMatch()); _t1705 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1705;
                                                                                                                                                                                                                            if (_t1705) {
                                                                                                                                                                                                                                Str *_t1679 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                                (void)_t1679;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1679;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1704; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwCase()); _t1704 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1704;
                                                                                                                                                                                                                                if (_t1704) {
                                                                                                                                                                                                                                    Str *_t1680 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                    (void)_t1680;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1680;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1703; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwDefault()); _t1703 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1703;
                                                                                                                                                                                                                                    if (_t1703) {
                                                                                                                                                                                                                                        Str *_t1681 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                        (void)_t1681;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1681;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1702; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwReturn()); _t1702 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1702;
                                                                                                                                                                                                                                        if (_t1702) {
                                                                                                                                                                                                                                            Str *_t1682 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                            (void)_t1682;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1682;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1701; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwThrow()); _t1701 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1701;
                                                                                                                                                                                                                                            if (_t1701) {
                                                                                                                                                                                                                                                Str *_t1683 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                                (void)_t1683;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1683;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1700; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwCatch()); _t1700 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1700;
                                                                                                                                                                                                                                                if (_t1700) {
                                                                                                                                                                                                                                                    Str *_t1684 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                    (void)_t1684;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1684;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1699; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwBreak()); _t1699 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1699;
                                                                                                                                                                                                                                                    if (_t1699) {
                                                                                                                                                                                                                                                        Str *_t1685 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                        (void)_t1685;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1685;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1698; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwContinue()); _t1698 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1698;
                                                                                                                                                                                                                                                        if (_t1698) {
                                                                                                                                                                                                                                                            Str *_t1686 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                            (void)_t1686;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1686;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1697; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwDefer()); _t1697 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1697;
                                                                                                                                                                                                                                                            if (_t1697) {
                                                                                                                                                                                                                                                                Str *_t1687 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                                (void)_t1687;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1687;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1696; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwTrue()); _t1696 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1696;
                                                                                                                                                                                                                                                                if (_t1696) {
                                                                                                                                                                                                                                                                    Str *_t1688 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                    (void)_t1688;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1688;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1695; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwFalse()); _t1695 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1695;
                                                                                                                                                                                                                                                                    if (_t1695) {
                                                                                                                                                                                                                                                                        Str *_t1689 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                        (void)_t1689;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1689;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1694; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_KwNull()); _t1694 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1694;
                                                                                                                                                                                                                                                                        if (_t1694) {
                                                                                                                                                                                                                                                                            Str *_t1690 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                            (void)_t1690;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1690;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Bool _t1693; { Bool *_hp = (Bool *)TokenType_eq(_sw1625, TokenType_Error()); _t1693 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                            (void)_t1693;
                                                                                                                                                                                                                                                                            if (_t1693) {
                                                                                                                                                                                                                                                                                Str *_t1691 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                                (void)_t1691;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1691;
                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                Str *_t1692 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                                (void)_t1692;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                TokenType_delete(_sw1625, &(Bool){1});
                                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                                return _t1692;
                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1625, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1759 = Str_clone(word);
        (void)_sw1759;
        Str *_t1828 = Str_lit("mode", 4ULL);
        (void)_t1828;
        Bool _t1829; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1828); _t1829 = *_hp; free(_hp); }
        (void)_t1829;
        Str_delete(_t1828, &(Bool){1});
        if (_t1829) {
            Str_delete(_sw1759, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1826 = Str_lit("mut", 3ULL);
            (void)_t1826;
            Bool _t1827; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1826); _t1827 = *_hp; free(_hp); }
            (void)_t1827;
            Str_delete(_t1826, &(Bool){1});
            if (_t1827) {
                ;
                Str_delete(_sw1759, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1824 = Str_lit("own", 3ULL);
                (void)_t1824;
                Bool _t1825; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1824); _t1825 = *_hp; free(_hp); }
                (void)_t1825;
                Str_delete(_t1824, &(Bool){1});
                if (_t1825) {
                    ;
                    ;
                    Str_delete(_sw1759, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1822 = Str_lit("ref", 3ULL);
                    (void)_t1822;
                    Bool _t1823; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1822); _t1823 = *_hp; free(_hp); }
                    (void)_t1823;
                    Str_delete(_t1822, &(Bool){1});
                    if (_t1823) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1759, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1820 = Str_lit("shallow", 7ULL);
                        (void)_t1820;
                        Bool _t1821; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1820); _t1821 = *_hp; free(_hp); }
                        (void)_t1821;
                        Str_delete(_t1820, &(Bool){1});
                        if (_t1821) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1759, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1818 = Str_lit("struct", 6ULL);
                            (void)_t1818;
                            Bool _t1819; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1818); _t1819 = *_hp; free(_hp); }
                            (void)_t1819;
                            Str_delete(_t1818, &(Bool){1});
                            if (_t1819) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1759, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1816 = Str_lit("ext_struct", 10ULL);
                                (void)_t1816;
                                Bool _t1817; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1816); _t1817 = *_hp; free(_hp); }
                                (void)_t1817;
                                Str_delete(_t1816, &(Bool){1});
                                if (_t1817) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1759, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1814 = Str_lit("enum", 4ULL);
                                    (void)_t1814;
                                    Bool _t1815; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1814); _t1815 = *_hp; free(_hp); }
                                    (void)_t1815;
                                    Str_delete(_t1814, &(Bool){1});
                                    if (_t1815) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1759, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1812 = Str_lit("namespace", 9ULL);
                                        (void)_t1812;
                                        Bool _t1813; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1812); _t1813 = *_hp; free(_hp); }
                                        (void)_t1813;
                                        Str_delete(_t1812, &(Bool){1});
                                        if (_t1813) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1759, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1810 = Str_lit("func", 4ULL);
                                            (void)_t1810;
                                            Bool _t1811; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1810); _t1811 = *_hp; free(_hp); }
                                            (void)_t1811;
                                            Str_delete(_t1810, &(Bool){1});
                                            if (_t1811) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1759, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1808 = Str_lit("proc", 4ULL);
                                                (void)_t1808;
                                                Bool _t1809; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1808); _t1809 = *_hp; free(_hp); }
                                                (void)_t1809;
                                                Str_delete(_t1808, &(Bool){1});
                                                if (_t1809) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1759, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1806 = Str_lit("test", 4ULL);
                                                    (void)_t1806;
                                                    Bool _t1807; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1806); _t1807 = *_hp; free(_hp); }
                                                    (void)_t1807;
                                                    Str_delete(_t1806, &(Bool){1});
                                                    if (_t1807) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1759, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1804 = Str_lit("macro", 5ULL);
                                                        (void)_t1804;
                                                        Bool _t1805; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1804); _t1805 = *_hp; free(_hp); }
                                                        (void)_t1805;
                                                        Str_delete(_t1804, &(Bool){1});
                                                        if (_t1805) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1759, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1802 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1802;
                                                            Bool _t1803; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1802); _t1803 = *_hp; free(_hp); }
                                                            (void)_t1803;
                                                            Str_delete(_t1802, &(Bool){1});
                                                            if (_t1803) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1759, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1800 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1800;
                                                                Bool _t1801; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1800); _t1801 = *_hp; free(_hp); }
                                                                (void)_t1801;
                                                                Str_delete(_t1800, &(Bool){1});
                                                                if (_t1801) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1798 = Str_lit("returns", 7ULL);
                                                                    (void)_t1798;
                                                                    Bool _t1799; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1798); _t1799 = *_hp; free(_hp); }
                                                                    (void)_t1799;
                                                                    Str_delete(_t1798, &(Bool){1});
                                                                    if (_t1799) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1796 = Str_lit("throws", 6ULL);
                                                                        (void)_t1796;
                                                                        Bool _t1797; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1796); _t1797 = *_hp; free(_hp); }
                                                                        (void)_t1797;
                                                                        Str_delete(_t1796, &(Bool){1});
                                                                        if (_t1797) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1794 = Str_lit("if", 2ULL);
                                                                            (void)_t1794;
                                                                            Bool _t1795; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1794); _t1795 = *_hp; free(_hp); }
                                                                            (void)_t1795;
                                                                            Str_delete(_t1794, &(Bool){1});
                                                                            if (_t1795) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1792 = Str_lit("else", 4ULL);
                                                                                (void)_t1792;
                                                                                Bool _t1793; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1792); _t1793 = *_hp; free(_hp); }
                                                                                (void)_t1793;
                                                                                Str_delete(_t1792, &(Bool){1});
                                                                                if (_t1793) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1790 = Str_lit("while", 5ULL);
                                                                                    (void)_t1790;
                                                                                    Bool _t1791; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1790); _t1791 = *_hp; free(_hp); }
                                                                                    (void)_t1791;
                                                                                    Str_delete(_t1790, &(Bool){1});
                                                                                    if (_t1791) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1788 = Str_lit("for", 3ULL);
                                                                                        (void)_t1788;
                                                                                        Bool _t1789; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1788); _t1789 = *_hp; free(_hp); }
                                                                                        (void)_t1789;
                                                                                        Str_delete(_t1788, &(Bool){1});
                                                                                        if (_t1789) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1786 = Str_lit("in", 2ULL);
                                                                                            (void)_t1786;
                                                                                            Bool _t1787; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1786); _t1787 = *_hp; free(_hp); }
                                                                                            (void)_t1787;
                                                                                            Str_delete(_t1786, &(Bool){1});
                                                                                            if (_t1787) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1784 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1784;
                                                                                                Bool _t1785; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1784); _t1785 = *_hp; free(_hp); }
                                                                                                (void)_t1785;
                                                                                                Str_delete(_t1784, &(Bool){1});
                                                                                                if (_t1785) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1782 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1782;
                                                                                                    Bool _t1783; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1782); _t1783 = *_hp; free(_hp); }
                                                                                                    (void)_t1783;
                                                                                                    Str_delete(_t1782, &(Bool){1});
                                                                                                    if (_t1783) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1780 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1780;
                                                                                                        Bool _t1781; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1780); _t1781 = *_hp; free(_hp); }
                                                                                                        (void)_t1781;
                                                                                                        Str_delete(_t1780, &(Bool){1});
                                                                                                        if (_t1781) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1778 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1778;
                                                                                                            Bool _t1779; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1778); _t1779 = *_hp; free(_hp); }
                                                                                                            (void)_t1779;
                                                                                                            Str_delete(_t1778, &(Bool){1});
                                                                                                            if (_t1779) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1776 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1776;
                                                                                                                Bool _t1777; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1776); _t1777 = *_hp; free(_hp); }
                                                                                                                (void)_t1777;
                                                                                                                Str_delete(_t1776, &(Bool){1});
                                                                                                                if (_t1777) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1774 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1774;
                                                                                                                    Bool _t1775; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1774); _t1775 = *_hp; free(_hp); }
                                                                                                                    (void)_t1775;
                                                                                                                    Str_delete(_t1774, &(Bool){1});
                                                                                                                    if (_t1775) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1772 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1772;
                                                                                                                        Bool _t1773; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1772); _t1773 = *_hp; free(_hp); }
                                                                                                                        (void)_t1773;
                                                                                                                        Str_delete(_t1772, &(Bool){1});
                                                                                                                        if (_t1773) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1770 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1770;
                                                                                                                            Bool _t1771; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1770); _t1771 = *_hp; free(_hp); }
                                                                                                                            (void)_t1771;
                                                                                                                            Str_delete(_t1770, &(Bool){1});
                                                                                                                            if (_t1771) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1768 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1768;
                                                                                                                                Bool _t1769; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1768); _t1769 = *_hp; free(_hp); }
                                                                                                                                (void)_t1769;
                                                                                                                                Str_delete(_t1768, &(Bool){1});
                                                                                                                                if (_t1769) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1766 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1766;
                                                                                                                                    Bool _t1767; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1766); _t1767 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1767;
                                                                                                                                    Str_delete(_t1766, &(Bool){1});
                                                                                                                                    if (_t1767) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1759, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1764 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1764;
                                                                                                                                        Bool _t1765; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1764); _t1765 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1765;
                                                                                                                                        Str_delete(_t1764, &(Bool){1});
                                                                                                                                        if (_t1765) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1759, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1762 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1762;
                                                                                                                                            Bool _t1763; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1762); _t1763 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1763;
                                                                                                                                            Str_delete(_t1762, &(Bool){1});
                                                                                                                                            if (_t1763) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1759, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1760 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1760;
                                                                                                                                                Bool _t1761; { Bool *_hp = (Bool *)Str_eq(_sw1759, _t1760); _t1761 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1759, &(Bool){1});
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
        Str_delete(_sw1759, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2178 = Str_lit("Token", 5ULL);
    (void)_t2178;
    U64 _t2179; { U64 *_hp = (U64 *)Token_size(); _t2179 = *_hp; free(_hp); }
    (void)_t2179;
    Vec *tokens = Vec_new(_t2178, &(U64){_t2179});
    (void)tokens;
    Str_delete(_t2178, &(Bool){1});
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
        Bool _wcond1830; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1830 = *_hp; free(_hp); }
        (void)_wcond1830;
        if (_wcond1830) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t2124 = 32;
        (void)_t2124;
        U8 _t2125 = 9;
        (void)_t2125;
        Bool _t2126 = U8_eq(DEREF(c), _t2124);
        (void)_t2126;
        ;
        Bool _t2127 = U8_eq(DEREF(c), _t2125);
        (void)_t2127;
        ;
        U8 _t2128 = 13;
        (void)_t2128;
        Bool _t2129 = Bool_or(_t2126, _t2127);
        (void)_t2129;
        ;
        ;
        Bool _t2130 = U8_eq(DEREF(c), _t2128);
        (void)_t2130;
        ;
        U8 _t2131 = 59;
        (void)_t2131;
        Bool _t2132 = Bool_or(_t2129, _t2130);
        (void)_t2132;
        ;
        ;
        Bool _t2133 = U8_eq(DEREF(c), _t2131);
        (void)_t2133;
        ;
        Bool _t2134 = Bool_or(_t2132, _t2133);
        (void)_t2134;
        ;
        ;
        if (_t2134) {
            U64 _t1831 = U64_inc(DEREF(pos));
            (void)_t1831;
            *pos = _t1831;
            ;
            ;
            continue;
        }
        ;
        U8 _t2135 = 10;
        (void)_t2135;
        Bool _t2136 = U8_eq(DEREF(c), _t2135);
        (void)_t2136;
        ;
        if (_t2136) {
            U64 _t1832 = U64_inc(DEREF(pos));
            (void)_t1832;
            *pos = _t1832;
            ;
            I64 _t1833 = 1;
            (void)_t1833;
            I64 _t1834 = I64_add(line, _t1833);
            (void)_t1834;
            ;
            line = _t1834;
            ;
            U64 _t1835 = U64_clone(pos);
            (void)_t1835;
            line_start = _t1835;
            ;
            ;
            continue;
        }
        ;
        U64 _t2137 = U64_sub(DEREF(pos), line_start);
        (void)_t2137;
        U64 _t2138 = 1;
        (void)_t2138;
        U64 _t2139 = U64_add(_t2137, _t2138);
        (void)_t2139;
        ;
        ;
        I64 col = U64_to_i64(_t2139);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t2140 = 35;
        (void)_t2140;
        Bool _t2141 = U8_eq(DEREF(c), _t2140);
        (void)_t2141;
        ;
        if (_t2141) {
            while (1) {
                Bool _wcond1836; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1836 = *_hp; free(_hp); }
                (void)_wcond1836;
                if (_wcond1836) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1837 = Str_byte_at(src, pos);
                (void)_t1837;
                U8 _t1838 = 10;
                (void)_t1838;
                Bool _t1839 = U8_eq(DEREF(_t1837), _t1838);
                (void)_t1839;
                ;
                if (_t1839) {
                    ;
                    break;
                }
                ;
                U64 _t1840 = U64_inc(DEREF(pos));
                (void)_t1840;
                *pos = _t1840;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2142 = 47;
        (void)_t2142;
        U64 _t2143 = 1;
        (void)_t2143;
        U64 _t2144 = U64_add(DEREF(pos), _t2143);
        (void)_t2144;
        ;
        Bool _t2145 = U8_eq(DEREF(c), _t2142);
        (void)_t2145;
        ;
        Bool _t2146; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2144}, &(U64){src_len}); _t2146 = *_hp; free(_hp); }
        (void)_t2146;
        ;
        Bool _t2147 = Bool_and(_t2145, _t2146);
        (void)_t2147;
        ;
        ;
        if (_t2147) {
            U64 _t1899 = 1;
            (void)_t1899;
            U64 *_t1900 = malloc(sizeof(U64)); *_t1900 = U64_add(DEREF(pos), _t1899);
            (void)_t1900;
            ;
            U8 *c2 = Str_byte_at(src, _t1900);
            (void)c2;
            U8 _t1901 = 47;
            (void)_t1901;
            Bool _t1902 = U8_eq(DEREF(c2), _t1901);
            (void)_t1902;
            ;
            if (_t1902) {
                while (1) {
                    Bool _wcond1841; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1841 = *_hp; free(_hp); }
                    (void)_wcond1841;
                    if (_wcond1841) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1842 = Str_byte_at(src, pos);
                    (void)_t1842;
                    U8 _t1843 = 10;
                    (void)_t1843;
                    Bool _t1844 = U8_eq(DEREF(_t1842), _t1843);
                    (void)_t1844;
                    ;
                    if (_t1844) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1845 = U64_inc(DEREF(pos));
                    (void)_t1845;
                    *pos = _t1845;
                    ;
                }
                U64_delete(_t1900, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1903 = 42;
            (void)_t1903;
            Bool _t1904 = U8_eq(DEREF(c2), _t1903);
            (void)_t1904;
            U64_delete(_t1900, &(Bool){1});
            ;
            if (_t1904) {
                U64 _t1895 = 2;
                (void)_t1895;
                U64 _t1896 = U64_add(DEREF(pos), _t1895);
                (void)_t1896;
                ;
                *pos = _t1896;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1846; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1846 = *_hp; free(_hp); }
                    (void)_wcond1846;
                    if (_wcond1846) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1871 = 0;
                    (void)_t1871;
                    Bool _t1872; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1871}); _t1872 = *_hp; free(_hp); }
                    (void)_t1872;
                    ;
                    if (_t1872) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1873 = 1;
                    (void)_t1873;
                    U64 _t1874 = U64_add(DEREF(pos), _t1873);
                    (void)_t1874;
                    ;
                    Bool _t1875; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1874}, &(U64){src_len}); _t1875 = *_hp; free(_hp); }
                    (void)_t1875;
                    ;
                    if (_t1875) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1855 = 1;
                        (void)_t1855;
                        U64 *_t1856 = malloc(sizeof(U64)); *_t1856 = U64_add(DEREF(pos), _t1855);
                        (void)_t1856;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1856);
                        (void)b2;
                        U8 _t1857 = 47;
                        (void)_t1857;
                        U8 _t1858 = 42;
                        (void)_t1858;
                        Bool _t1859 = U8_eq(DEREF(b1), _t1857);
                        (void)_t1859;
                        ;
                        Bool _t1860 = U8_eq(DEREF(b2), _t1858);
                        (void)_t1860;
                        ;
                        Bool _t1861 = Bool_and(_t1859, _t1860);
                        (void)_t1861;
                        ;
                        ;
                        if (_t1861) {
                            I64 _t1847 = 1;
                            (void)_t1847;
                            I64 _t1848 = I64_add(depth, _t1847);
                            (void)_t1848;
                            ;
                            depth = _t1848;
                            ;
                            U64 _t1849 = 2;
                            (void)_t1849;
                            U64 _t1850 = U64_add(DEREF(pos), _t1849);
                            (void)_t1850;
                            ;
                            *pos = _t1850;
                            ;
                            U64_delete(_t1856, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1862 = 42;
                        (void)_t1862;
                        U8 _t1863 = 47;
                        (void)_t1863;
                        Bool _t1864 = U8_eq(DEREF(b1), _t1862);
                        (void)_t1864;
                        ;
                        Bool _t1865 = U8_eq(DEREF(b2), _t1863);
                        (void)_t1865;
                        U64_delete(_t1856, &(Bool){1});
                        ;
                        Bool _t1866 = Bool_and(_t1864, _t1865);
                        (void)_t1866;
                        ;
                        ;
                        if (_t1866) {
                            I64 _t1851 = 1;
                            (void)_t1851;
                            I64 _t1852 = I64_sub(depth, _t1851);
                            (void)_t1852;
                            ;
                            depth = _t1852;
                            ;
                            U64 _t1853 = 2;
                            (void)_t1853;
                            U64 _t1854 = U64_add(DEREF(pos), _t1853);
                            (void)_t1854;
                            ;
                            *pos = _t1854;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1876 = Str_byte_at(src, pos);
                    (void)_t1876;
                    U8 _t1877 = 10;
                    (void)_t1877;
                    Bool _t1878 = U8_eq(DEREF(_t1876), _t1877);
                    (void)_t1878;
                    ;
                    if (_t1878) {
                        I64 _t1867 = 1;
                        (void)_t1867;
                        I64 _t1868 = I64_add(line, _t1867);
                        (void)_t1868;
                        ;
                        line = _t1868;
                        ;
                        U64 _t1869 = 1;
                        (void)_t1869;
                        U64 _t1870 = U64_add(DEREF(pos), _t1869);
                        (void)_t1870;
                        ;
                        line_start = _t1870;
                        ;
                    }
                    ;
                    U64 _t1879 = U64_inc(DEREF(pos));
                    (void)_t1879;
                    *pos = _t1879;
                    ;
                }
                I64 _t1897 = 0;
                (void)_t1897;
                Bool _t1898; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1897}); _t1898 = *_hp; free(_hp); }
                (void)_t1898;
                ;
                ;
                if (_t1898) {
                    Str *_t1880 = Str_lit("Str", 3ULL);
                    (void)_t1880;
                    U64 _t1881; { U64 *_hp = (U64 *)Str_size(); _t1881 = *_hp; free(_hp); }
                    (void)_t1881;
                    U64 _t1882 = 6;
                    (void)_t1882;
                    Array *_va20 = Array_new(_t1880, &(U64){_t1881}, &(U64){_t1882});
                    (void)_va20;
                    Str_delete(_t1880, &(Bool){1});
                    ;
                    ;
                    U64 _t1883 = 0;
                    (void)_t1883;
                    Str *_t1884 = Str_clone(path);
                    (void)_t1884;
                    Array_set(_va20, &(U64){_t1883}, _t1884);
                    ;
                    U64 _t1885 = 1;
                    (void)_t1885;
                    Str *_t1886 = Str_lit(":", 1ULL);
                    (void)_t1886;
                    Array_set(_va20, &(U64){_t1885}, _t1886);
                    ;
                    U64 _t1887 = 2;
                    (void)_t1887;
                    Str *_t1888 = I64_to_str(&(I64){line});
                    (void)_t1888;
                    Array_set(_va20, &(U64){_t1887}, _t1888);
                    ;
                    U64 _t1889 = 3;
                    (void)_t1889;
                    Str *_t1890 = Str_lit(":", 1ULL);
                    (void)_t1890;
                    Array_set(_va20, &(U64){_t1889}, _t1890);
                    ;
                    U64 _t1891 = 4;
                    (void)_t1891;
                    Str *_t1892 = I64_to_str(&(I64){col});
                    (void)_t1892;
                    Array_set(_va20, &(U64){_t1891}, _t1892);
                    ;
                    U64 _t1893 = 5;
                    (void)_t1893;
                    Str *_t1894 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1894;
                    Array_set(_va20, &(U64){_t1893}, _t1894);
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
        Bool _t2148; { Bool *_hp = (Bool *)is_digit(c); _t2148 = *_hp; free(_hp); }
        (void)_t2148;
        if (_t2148) {
            while (1) {
                Bool _wcond1905; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1905 = *_hp; free(_hp); }
                (void)_wcond1905;
                if (_wcond1905) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1906 = Str_byte_at(src, pos);
                (void)_t1906;
                Bool _t1907; { Bool *_hp = (Bool *)is_digit(_t1906); _t1907 = *_hp; free(_hp); }
                (void)_t1907;
                Bool _t1908 = Bool_not(_t1907);
                (void)_t1908;
                ;
                if (_t1908) {
                    ;
                    break;
                }
                ;
                U64 _t1909 = U64_inc(DEREF(pos));
                (void)_t1909;
                *pos = _t1909;
                ;
            }
            U64 _t1924 = 1;
            (void)_t1924;
            U64 _t1925 = U64_add(DEREF(pos), _t1924);
            (void)_t1925;
            ;
            Bool _t1926; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1925}, &(U64){src_len}); _t1926 = *_hp; free(_hp); }
            (void)_t1926;
            ;
            if (_t1926) {
                U8 *_t1916 = Str_byte_at(src, pos);
                (void)_t1916;
                U8 _t1917 = 46;
                (void)_t1917;
                U64 _t1918 = 1;
                (void)_t1918;
                U64 *_t1919 = malloc(sizeof(U64)); *_t1919 = U64_add(DEREF(pos), _t1918);
                (void)_t1919;
                ;
                U8 *_t1920 = Str_byte_at(src, _t1919);
                (void)_t1920;
                Bool _t1921 = U8_eq(DEREF(_t1916), _t1917);
                (void)_t1921;
                ;
                Bool _t1922; { Bool *_hp = (Bool *)is_digit(_t1920); _t1922 = *_hp; free(_hp); }
                (void)_t1922;
                U64_delete(_t1919, &(Bool){1});
                Bool _t1923 = Bool_and(_t1921, _t1922);
                (void)_t1923;
                ;
                ;
                if (_t1923) {
                    U64 _t1915 = U64_inc(DEREF(pos));
                    (void)_t1915;
                    *pos = _t1915;
                    ;
                    while (1) {
                        Bool _wcond1910; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1910 = *_hp; free(_hp); }
                        (void)_wcond1910;
                        if (_wcond1910) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1911 = Str_byte_at(src, pos);
                        (void)_t1911;
                        Bool _t1912; { Bool *_hp = (Bool *)is_digit(_t1911); _t1912 = *_hp; free(_hp); }
                        (void)_t1912;
                        Bool _t1913 = Bool_not(_t1912);
                        (void)_t1913;
                        ;
                        if (_t1913) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1914 = U64_inc(DEREF(pos));
                        (void)_t1914;
                        *pos = _t1914;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1927 = U64_sub(DEREF(pos), start);
            (void)_t1927;
            I64 _t1928 = I64_clone(&(I64){col});
            (void)_t1928;
            Token *_t1929 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1929->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1927}); _t1929->text = *_ca; free(_ca); }
            _t1929->line = I64_clone(&(I64){line});
            _t1929->col = _t1928;
            (void)_t1929;
            ;
            ;
            Vec_push(tokens, _t1929);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t2149; { Bool *_hp = (Bool *)is_alpha(c); _t2149 = *_hp; free(_hp); }
        (void)_t2149;
        if (_t2149) {
            while (1) {
                Bool _wcond1930; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1930 = *_hp; free(_hp); }
                (void)_wcond1930;
                if (_wcond1930) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1931 = Str_byte_at(src, pos);
                (void)_t1931;
                Bool _t1932; { Bool *_hp = (Bool *)is_alnum(_t1931); _t1932 = *_hp; free(_hp); }
                (void)_t1932;
                Bool _t1933 = Bool_not(_t1932);
                (void)_t1933;
                ;
                if (_t1933) {
                    ;
                    break;
                }
                ;
                U64 _t1934 = U64_inc(DEREF(pos));
                (void)_t1934;
                *pos = _t1934;
                ;
            }
            U64 _t1935 = U64_sub(DEREF(pos), start);
            (void)_t1935;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1935});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1936 = I64_clone(&(I64){line});
            (void)_t1936;
            I64 _t1937 = I64_clone(&(I64){col});
            (void)_t1937;
            Token *_t1938 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1938->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1938->text = *_ca; free(_ca); }
            _t1938->line = _t1936;
            _t1938->col = _t1937;
            (void)_t1938;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1938);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2150 = 34;
        (void)_t2150;
        Bool _t2151 = U8_eq(DEREF(c), _t2150);
        (void)_t2151;
        ;
        if (_t2151) {
            U64 _t1985 = U64_inc(DEREF(pos));
            (void)_t1985;
            *pos = _t1985;
            ;
            while (1) {
                Bool _wcond1939; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1939 = *_hp; free(_hp); }
                (void)_wcond1939;
                if (_wcond1939) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1945 = Str_byte_at(src, pos);
                (void)_t1945;
                U8 _t1946 = 34;
                (void)_t1946;
                Bool _t1947 = U8_eq(DEREF(_t1945), _t1946);
                (void)_t1947;
                ;
                if (_t1947) {
                    ;
                    break;
                }
                ;
                U8 *_t1948 = Str_byte_at(src, pos);
                (void)_t1948;
                U8 _t1949 = 92;
                (void)_t1949;
                U64 _t1950 = 1;
                (void)_t1950;
                U64 _t1951 = U64_add(DEREF(pos), _t1950);
                (void)_t1951;
                ;
                Bool _t1952 = U8_eq(DEREF(_t1948), _t1949);
                (void)_t1952;
                ;
                Bool _t1953; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1951}, &(U64){src_len}); _t1953 = *_hp; free(_hp); }
                (void)_t1953;
                ;
                Bool _t1954 = Bool_and(_t1952, _t1953);
                (void)_t1954;
                ;
                ;
                if (_t1954) {
                    U64 _t1940 = U64_inc(DEREF(pos));
                    (void)_t1940;
                    *pos = _t1940;
                    ;
                }
                ;
                U8 *_t1955 = Str_byte_at(src, pos);
                (void)_t1955;
                U8 _t1956 = 10;
                (void)_t1956;
                Bool _t1957 = U8_eq(DEREF(_t1955), _t1956);
                (void)_t1957;
                ;
                if (_t1957) {
                    I64 _t1941 = 1;
                    (void)_t1941;
                    I64 _t1942 = I64_add(line, _t1941);
                    (void)_t1942;
                    ;
                    line = _t1942;
                    ;
                    U64 _t1943 = 1;
                    (void)_t1943;
                    U64 _t1944 = U64_add(DEREF(pos), _t1943);
                    (void)_t1944;
                    ;
                    line_start = _t1944;
                    ;
                }
                ;
                U64 _t1958 = U64_inc(DEREF(pos));
                (void)_t1958;
                *pos = _t1958;
                ;
            }
            U8 *_t1986 = Str_byte_at(src, pos);
            (void)_t1986;
            U8 _t1987 = 34;
            (void)_t1987;
            Bool _t1988; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1988 = *_hp; free(_hp); }
            (void)_t1988;
            Bool _t1989 = U8_eq(DEREF(_t1986), _t1987);
            (void)_t1989;
            ;
            Bool _t1990 = Bool_and(_t1988, _t1989);
            (void)_t1990;
            ;
            ;
            if (_t1990) {
                U64 _t1959 = U64_inc(DEREF(pos));
                (void)_t1959;
                *pos = _t1959;
                ;
                U64 _t1960 = 1;
                (void)_t1960;
                U64 _t1961 = U64_sub(DEREF(pos), start);
                (void)_t1961;
                U64 _t1962 = 2;
                (void)_t1962;
                U64 _t1963 = U64_add(start, _t1960);
                (void)_t1963;
                ;
                U64 _t1964 = U64_sub(_t1961, _t1962);
                (void)_t1964;
                ;
                ;
                I64 _t1965 = I64_clone(&(I64){col});
                (void)_t1965;
                Token *_t1966 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1966->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1963}, &(U64){_t1964}); _t1966->text = *_ca; free(_ca); }
                _t1966->line = I64_clone(&(I64){line});
                _t1966->col = _t1965;
                (void)_t1966;
                ;
                ;
                ;
                Vec_push(tokens, _t1966);
            } else {
                Str *_t1967 = Str_lit("Str", 3ULL);
                (void)_t1967;
                U64 _t1968; { U64 *_hp = (U64 *)Str_size(); _t1968 = *_hp; free(_hp); }
                (void)_t1968;
                U64 _t1969 = 6;
                (void)_t1969;
                Array *_va21 = Array_new(_t1967, &(U64){_t1968}, &(U64){_t1969});
                (void)_va21;
                Str_delete(_t1967, &(Bool){1});
                ;
                ;
                U64 _t1970 = 0;
                (void)_t1970;
                Str *_t1971 = Str_clone(path);
                (void)_t1971;
                Array_set(_va21, &(U64){_t1970}, _t1971);
                ;
                U64 _t1972 = 1;
                (void)_t1972;
                Str *_t1973 = Str_lit(":", 1ULL);
                (void)_t1973;
                Array_set(_va21, &(U64){_t1972}, _t1973);
                ;
                U64 _t1974 = 2;
                (void)_t1974;
                Str *_t1975 = I64_to_str(&(I64){line});
                (void)_t1975;
                Array_set(_va21, &(U64){_t1974}, _t1975);
                ;
                U64 _t1976 = 3;
                (void)_t1976;
                Str *_t1977 = Str_lit(":", 1ULL);
                (void)_t1977;
                Array_set(_va21, &(U64){_t1976}, _t1977);
                ;
                U64 _t1978 = 4;
                (void)_t1978;
                Str *_t1979 = I64_to_str(&(I64){col});
                (void)_t1979;
                Array_set(_va21, &(U64){_t1978}, _t1979);
                ;
                U64 _t1980 = 5;
                (void)_t1980;
                Str *_t1981 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1981;
                Array_set(_va21, &(U64){_t1980}, _t1981);
                ;
                println(_va21);
                U64 _t1982 = U64_sub(DEREF(pos), start);
                (void)_t1982;
                I64 _t1983 = I64_clone(&(I64){col});
                (void)_t1983;
                Token *_t1984 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1984->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1982}); _t1984->text = *_ca; free(_ca); }
                _t1984->line = I64_clone(&(I64){line});
                _t1984->col = _t1983;
                (void)_t1984;
                ;
                ;
                Vec_push(tokens, _t1984);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t2152 = 39;
        (void)_t2152;
        Bool _t2153 = U8_eq(DEREF(c), _t2152);
        (void)_t2153;
        ;
        if (_t2153) {
            U64 _t2014 = U64_inc(DEREF(pos));
            (void)_t2014;
            *pos = _t2014;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t2015 = Str_byte_at(src, pos);
            (void)_t2015;
            U8 _t2016 = 92;
            (void)_t2016;
            U64 _t2017 = 1;
            (void)_t2017;
            U64 _t2018 = U64_add(DEREF(pos), _t2017);
            (void)_t2018;
            ;
            Bool _t2019 = U8_eq(DEREF(_t2015), _t2016);
            (void)_t2019;
            ;
            Bool _t2020; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2018}, &(U64){src_len}); _t2020 = *_hp; free(_hp); }
            (void)_t2020;
            ;
            Bool _t2021; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2021 = *_hp; free(_hp); }
            (void)_t2021;
            Bool _t2022 = Bool_and(_t2019, _t2020);
            (void)_t2022;
            ;
            ;
            Bool _t2023 = Bool_and(_t2021, _t2022);
            (void)_t2023;
            ;
            ;
            if (_t2023) {
                U64 _t1991 = U64_inc(DEREF(pos));
                (void)_t1991;
                *pos = _t1991;
                ;
            }
            ;
            U64 _t2024 = U64_inc(DEREF(pos));
            (void)_t2024;
            *pos = _t2024;
            ;
            U8 *_t2025 = Str_byte_at(src, pos);
            (void)_t2025;
            U8 _t2026 = 39;
            (void)_t2026;
            Bool _t2027; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t2027 = *_hp; free(_hp); }
            (void)_t2027;
            Bool _t2028 = U8_eq(DEREF(_t2025), _t2026);
            (void)_t2028;
            ;
            Bool _t2029 = Bool_and(_t2027, _t2028);
            (void)_t2029;
            ;
            ;
            if (_t2029) {
                U64 _t1992 = U64_sub(DEREF(pos), ch_start);
                (void)_t1992;
                I64 _t1993 = I64_clone(&(I64){col});
                (void)_t1993;
                Token *_t1994 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1994->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1992}); _t1994->text = *_ca; free(_ca); }
                _t1994->line = I64_clone(&(I64){line});
                _t1994->col = _t1993;
                (void)_t1994;
                ;
                ;
                Vec_push(tokens, _t1994);
                U64 _t1995 = U64_inc(DEREF(pos));
                (void)_t1995;
                *pos = _t1995;
                ;
            } else {
                Str *_t1996 = Str_lit("Str", 3ULL);
                (void)_t1996;
                U64 _t1997; { U64 *_hp = (U64 *)Str_size(); _t1997 = *_hp; free(_hp); }
                (void)_t1997;
                U64 _t1998 = 6;
                (void)_t1998;
                Array *_va22 = Array_new(_t1996, &(U64){_t1997}, &(U64){_t1998});
                (void)_va22;
                Str_delete(_t1996, &(Bool){1});
                ;
                ;
                U64 _t1999 = 0;
                (void)_t1999;
                Str *_t2000 = Str_clone(path);
                (void)_t2000;
                Array_set(_va22, &(U64){_t1999}, _t2000);
                ;
                U64 _t2001 = 1;
                (void)_t2001;
                Str *_t2002 = Str_lit(":", 1ULL);
                (void)_t2002;
                Array_set(_va22, &(U64){_t2001}, _t2002);
                ;
                U64 _t2003 = 2;
                (void)_t2003;
                Str *_t2004 = I64_to_str(&(I64){line});
                (void)_t2004;
                Array_set(_va22, &(U64){_t2003}, _t2004);
                ;
                U64 _t2005 = 3;
                (void)_t2005;
                Str *_t2006 = Str_lit(":", 1ULL);
                (void)_t2006;
                Array_set(_va22, &(U64){_t2005}, _t2006);
                ;
                U64 _t2007 = 4;
                (void)_t2007;
                Str *_t2008 = I64_to_str(&(I64){col});
                (void)_t2008;
                Array_set(_va22, &(U64){_t2007}, _t2008);
                ;
                U64 _t2009 = 5;
                (void)_t2009;
                Str *_t2010 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t2010;
                Array_set(_va22, &(U64){_t2009}, _t2010);
                ;
                println(_va22);
                U64 _t2011 = U64_sub(DEREF(pos), start);
                (void)_t2011;
                I64 _t2012 = I64_clone(&(I64){col});
                (void)_t2012;
                Token *_t2013 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2013->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2011}); _t2013->text = *_ca; free(_ca); }
                _t2013->line = I64_clone(&(I64){line});
                _t2013->col = _t2012;
                (void)_t2013;
                ;
                ;
                Vec_push(tokens, _t2013);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t2154 = 1;
        (void)_t2154;
        U64 _t2155 = U64_add(DEREF(pos), _t2154);
        (void)_t2155;
        ;
        Bool _t2156; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2155}, &(U64){src_len}); _t2156 = *_hp; free(_hp); }
        (void)_t2156;
        ;
        if (_t2156) {
            U64 _t2073 = 1;
            (void)_t2073;
            U64 *_t2074 = malloc(sizeof(U64)); *_t2074 = U64_add(DEREF(pos), _t2073);
            (void)_t2074;
            ;
            U8 *c2 = Str_byte_at(src, _t2074);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t2075 = 58;
            (void)_t2075;
            U8 _t2076 = 61;
            (void)_t2076;
            Bool _t2077 = U8_eq(DEREF(c), _t2075);
            (void)_t2077;
            ;
            Bool _t2078 = U8_eq(DEREF(c2), _t2076);
            (void)_t2078;
            ;
            Bool _t2079 = Bool_and(_t2077, _t2078);
            (void)_t2079;
            ;
            ;
            if (_t2079) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t2062 = 61;
                (void)_t2062;
                U8 _t2063 = 61;
                (void)_t2063;
                Bool _t2064 = U8_eq(DEREF(c), _t2062);
                (void)_t2064;
                ;
                Bool _t2065 = U8_eq(DEREF(c2), _t2063);
                (void)_t2065;
                ;
                Bool _t2066 = Bool_and(_t2064, _t2065);
                (void)_t2066;
                ;
                ;
                if (_t2066) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t2057 = 33;
                    (void)_t2057;
                    U8 _t2058 = 61;
                    (void)_t2058;
                    Bool _t2059 = U8_eq(DEREF(c), _t2057);
                    (void)_t2059;
                    ;
                    Bool _t2060 = U8_eq(DEREF(c2), _t2058);
                    (void)_t2060;
                    ;
                    Bool _t2061 = Bool_and(_t2059, _t2060);
                    (void)_t2061;
                    ;
                    ;
                    if (_t2061) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t2052 = 60;
                        (void)_t2052;
                        U8 _t2053 = 61;
                        (void)_t2053;
                        Bool _t2054 = U8_eq(DEREF(c), _t2052);
                        (void)_t2054;
                        ;
                        Bool _t2055 = U8_eq(DEREF(c2), _t2053);
                        (void)_t2055;
                        ;
                        Bool _t2056 = Bool_and(_t2054, _t2055);
                        (void)_t2056;
                        ;
                        ;
                        if (_t2056) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t2047 = 62;
                            (void)_t2047;
                            U8 _t2048 = 61;
                            (void)_t2048;
                            Bool _t2049 = U8_eq(DEREF(c), _t2047);
                            (void)_t2049;
                            ;
                            Bool _t2050 = U8_eq(DEREF(c2), _t2048);
                            (void)_t2050;
                            ;
                            Bool _t2051 = Bool_and(_t2049, _t2050);
                            (void)_t2051;
                            ;
                            ;
                            if (_t2051) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t2042 = 46;
                                (void)_t2042;
                                U8 _t2043 = 46;
                                (void)_t2043;
                                Bool _t2044 = U8_eq(DEREF(c), _t2042);
                                (void)_t2044;
                                ;
                                Bool _t2045 = U8_eq(DEREF(c2), _t2043);
                                (void)_t2045;
                                ;
                                Bool _t2046 = Bool_and(_t2044, _t2045);
                                (void)_t2046;
                                ;
                                ;
                                if (_t2046) {
                                    U64 _t2039 = 2;
                                    (void)_t2039;
                                    U64 _t2040 = U64_add(DEREF(pos), _t2039);
                                    (void)_t2040;
                                    ;
                                    Bool _t2041; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2040}, &(U64){src_len}); _t2041 = *_hp; free(_hp); }
                                    (void)_t2041;
                                    ;
                                    if (_t2041) {
                                        U64 _t2035 = 2;
                                        (void)_t2035;
                                        U64 *_t2036 = malloc(sizeof(U64)); *_t2036 = U64_add(DEREF(pos), _t2035);
                                        (void)_t2036;
                                        ;
                                        U8 *c3 = Str_byte_at(src, _t2036);
                                        (void)c3;
                                        U8 _t2037 = 46;
                                        (void)_t2037;
                                        Bool _t2038 = U8_eq(DEREF(c3), _t2037);
                                        (void)_t2038;
                                        U64_delete(_t2036, &(Bool){1});
                                        ;
                                        if (_t2038) {
                                            U64 _t2030 = 3;
                                            (void)_t2030;
                                            I64 _t2031 = I64_clone(&(I64){col});
                                            (void)_t2031;
                                            Token *_t2032 = malloc(sizeof(Token));
                                            { TokenType *_ca = TokenType_clone(TokenType_DotDotDot()); _t2032->type = *_ca; free(_ca); }
                                            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2030}); _t2032->text = *_ca; free(_ca); }
                                            _t2032->line = I64_clone(&(I64){line});
                                            _t2032->col = _t2031;
                                            (void)_t2032;
                                            ;
                                            ;
                                            Vec_push(tokens, _t2032);
                                            U64 _t2033 = 3;
                                            (void)_t2033;
                                            U64 _t2034 = U64_add(DEREF(pos), _t2033);
                                            (void)_t2034;
                                            ;
                                            *pos = _t2034;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            U64_delete(_t2074, &(Bool){1});
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
            U64_delete(_t2074, &(Bool){1});
            ;
            Bool _t2080; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t2080 = *_hp; free(_hp); }
            (void)_t2080;
            Bool _t2081 = Bool_not(_t2080);
            (void)_t2081;
            ;
            if (_t2081) {
                U64 _t2067 = 2;
                (void)_t2067;
                I64 _t2068 = I64_clone(&(I64){line});
                (void)_t2068;
                I64 _t2069 = I64_clone(&(I64){col});
                (void)_t2069;
                Token *_t2070 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t2070->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2067}); _t2070->text = *_ca; free(_ca); }
                _t2070->line = _t2068;
                _t2070->col = _t2069;
                (void)_t2070;
                ;
                ;
                ;
                Vec_push(tokens, _t2070);
                U64 _t2071 = 2;
                (void)_t2071;
                U64 _t2072 = U64_add(DEREF(pos), _t2071);
                (void)_t2072;
                ;
                *pos = _t2072;
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
            U8 _sw2082 = U8_clone(c);
            (void)_sw2082;
            U8 _t2117 = 40;
            (void)_t2117;
            Bool _t2118 = U8_eq(_sw2082, _t2117);
            (void)_t2118;
            ;
            if (_t2118) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t2115 = 41;
                (void)_t2115;
                Bool _t2116 = U8_eq(_sw2082, _t2115);
                (void)_t2116;
                ;
                if (_t2116) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t2113 = 123;
                    (void)_t2113;
                    Bool _t2114 = U8_eq(_sw2082, _t2113);
                    (void)_t2114;
                    ;
                    if (_t2114) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t2111 = 125;
                        (void)_t2111;
                        Bool _t2112 = U8_eq(_sw2082, _t2111);
                        (void)_t2112;
                        ;
                        if (_t2112) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t2109 = 91;
                            (void)_t2109;
                            Bool _t2110 = U8_eq(_sw2082, _t2109);
                            (void)_t2110;
                            ;
                            if (_t2110) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t2107 = 93;
                                (void)_t2107;
                                Bool _t2108 = U8_eq(_sw2082, _t2107);
                                (void)_t2108;
                                ;
                                if (_t2108) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t2105 = 44;
                                    (void)_t2105;
                                    Bool _t2106 = U8_eq(_sw2082, _t2105);
                                    (void)_t2106;
                                    ;
                                    if (_t2106) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t2103 = 58;
                                        (void)_t2103;
                                        Bool _t2104 = U8_eq(_sw2082, _t2103);
                                        (void)_t2104;
                                        ;
                                        if (_t2104) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t2101 = 46;
                                            (void)_t2101;
                                            Bool _t2102 = U8_eq(_sw2082, _t2101);
                                            (void)_t2102;
                                            ;
                                            if (_t2102) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t2099 = 63;
                                                (void)_t2099;
                                                Bool _t2100 = U8_eq(_sw2082, _t2099);
                                                (void)_t2100;
                                                ;
                                                if (_t2100) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t2097 = 33;
                                                    (void)_t2097;
                                                    Bool _t2098 = U8_eq(_sw2082, _t2097);
                                                    (void)_t2098;
                                                    ;
                                                    if (_t2098) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t2095 = 43;
                                                        (void)_t2095;
                                                        Bool _t2096 = U8_eq(_sw2082, _t2095);
                                                        (void)_t2096;
                                                        ;
                                                        if (_t2096) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t2093 = 45;
                                                            (void)_t2093;
                                                            Bool _t2094 = U8_eq(_sw2082, _t2093);
                                                            (void)_t2094;
                                                            ;
                                                            if (_t2094) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t2091 = 42;
                                                                (void)_t2091;
                                                                Bool _t2092 = U8_eq(_sw2082, _t2091);
                                                                (void)_t2092;
                                                                ;
                                                                if (_t2092) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t2089 = 47;
                                                                    (void)_t2089;
                                                                    Bool _t2090 = U8_eq(_sw2082, _t2089);
                                                                    (void)_t2090;
                                                                    ;
                                                                    if (_t2090) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t2087 = 61;
                                                                        (void)_t2087;
                                                                        Bool _t2088 = U8_eq(_sw2082, _t2087);
                                                                        (void)_t2088;
                                                                        ;
                                                                        if (_t2088) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t2085 = 60;
                                                                            (void)_t2085;
                                                                            Bool _t2086 = U8_eq(_sw2082, _t2085);
                                                                            (void)_t2086;
                                                                            ;
                                                                            if (_t2086) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t2083 = 62;
                                                                                (void)_t2083;
                                                                                Bool _t2084 = U8_eq(_sw2082, _t2083);
                                                                                (void)_t2084;
                                                                                ;
                                                                                if (_t2084) {
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
        Bool _t2157; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t2157 = *_hp; free(_hp); }
        (void)_t2157;
        Bool _t2158 = Bool_not(_t2157);
        (void)_t2158;
        ;
        if (_t2158) {
            U64 _t2119 = 1;
            (void)_t2119;
            I64 _t2120 = I64_clone(&(I64){line});
            (void)_t2120;
            I64 _t2121 = I64_clone(&(I64){col});
            (void)_t2121;
            Token *_t2122 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t2122->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2119}); _t2122->text = *_ca; free(_ca); }
            _t2122->line = _t2120;
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
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t2159 = Str_lit("Str", 3ULL);
        (void)_t2159;
        U64 _t2160; { U64 *_hp = (U64 *)Str_size(); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        U64 _t2161 = 6;
        (void)_t2161;
        Array *_va23 = Array_new(_t2159, &(U64){_t2160}, &(U64){_t2161});
        (void)_va23;
        Str_delete(_t2159, &(Bool){1});
        ;
        ;
        U64 _t2162 = 0;
        (void)_t2162;
        Str *_t2163 = Str_clone(path);
        (void)_t2163;
        Array_set(_va23, &(U64){_t2162}, _t2163);
        ;
        U64 _t2164 = 1;
        (void)_t2164;
        Str *_t2165 = Str_lit(":", 1ULL);
        (void)_t2165;
        Array_set(_va23, &(U64){_t2164}, _t2165);
        ;
        U64 _t2166 = 2;
        (void)_t2166;
        Str *_t2167 = I64_to_str(&(I64){line});
        (void)_t2167;
        Array_set(_va23, &(U64){_t2166}, _t2167);
        ;
        U64 _t2168 = 3;
        (void)_t2168;
        Str *_t2169 = Str_lit(":", 1ULL);
        (void)_t2169;
        Array_set(_va23, &(U64){_t2168}, _t2169);
        ;
        U64 _t2170 = 4;
        (void)_t2170;
        Str *_t2171 = I64_to_str(&(I64){col});
        (void)_t2171;
        Array_set(_va23, &(U64){_t2170}, _t2171);
        ;
        U64 _t2172 = 5;
        (void)_t2172;
        Str *_t2173 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2173;
        Array_set(_va23, &(U64){_t2172}, _t2173);
        ;
        println(_va23);
        U64 _t2174 = 1;
        (void)_t2174;
        I64 _t2175 = I64_clone(&(I64){col});
        (void)_t2175;
        ;
        Token *_t2176 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2176->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2174}); _t2176->text = *_ca; free(_ca); }
        _t2176->line = I64_clone(&(I64){line});
        _t2176->col = _t2175;
        (void)_t2176;
        ;
        ;
        ;
        Vec_push(tokens, _t2176);
        U64 _t2177 = U64_inc(DEREF(pos));
        (void)_t2177;
        *pos = _t2177;
        ;
    }
    ;
    U64 _t2180 = U64_sub(DEREF(pos), line_start);
    (void)_t2180;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2181 = 1;
    (void)_t2181;
    U64 _t2182 = U64_add(_t2180, _t2181);
    (void)_t2182;
    ;
    ;
    I64 col = U64_to_i64(_t2182);
    (void)col;
    ;
    I64 _t2183 = I64_clone(&(I64){col});
    (void)_t2183;
    ;
    Token *_t2184 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2184->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2184->text = *_ca; free(_ca); }
    _t2184->line = I64_clone(&(I64){line});
    _t2184->col = _t2183;
    (void)_t2184;
    ;
    ;
    Vec_push(tokens, _t2184);
    return tokens;
}

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) { EnumDef_delete(val, arg2); return; }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) { FuncType_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) { FunctionDef_delete(val, arg2); return; }
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return (void *)FuncType_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return (void *)FunctionDef_clone(val);
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
    _t2185 = malloc(sizeof(I64));
    *_t2185 = 0;
    (void)_t2185;
    _t2186 = malloc(sizeof(I64));
    *_t2186 = 1;
    (void)_t2186;
    _t2187 = malloc(sizeof(I64)); *_t2187 = I64_sub(DEREF(_t2185), DEREF(_t2186));
    (void)_t2187;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2187));
    (void)CAP_LIT;
    _t2188 = malloc(sizeof(I64));
    *_t2188 = 0;
    (void)_t2188;
    _t2189 = malloc(sizeof(I64));
    *_t2189 = 2;
    (void)_t2189;
    _t2190 = malloc(sizeof(I64)); *_t2190 = I64_sub(DEREF(_t2188), DEREF(_t2189));
    (void)_t2190;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2190));
    (void)CAP_VIEW;
}

