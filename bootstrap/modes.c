#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "modes_core.h"
#include "modes_array.h"
#include "modes_map.h"
#include "modes_set.h"
#include "modes_str.h"
#include "modes_vec.h"
#include "modes_tuple.h"
#include "modes_ast.h"
#include "modes_lexer.h"
#include "modes_parser.h"
#include "modes_initer.h"
#include "modes_modes.h"

#include "ext.h"


Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U64 * EnumDef_size(void);
Str * U8_to_str(U8 * val);
U64 * U8_size(void);
Bool * U8_lt(U8 * a, U8 * b);
Bool * U8_gt(U8 * a, U8 * b);
Bool * U8_neq(U8 * a, U8 * b);
Bool * U8_lte(U8 * a, U8 * b);
Bool * U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
U64 * I16_size(void);
Bool * I16_lt(I16 * a, I16 * b);
Bool * I16_gt(I16 * a, I16 * b);
Bool * I16_neq(I16 * a, I16 * b);
Bool * I16_lte(I16 * a, I16 * b);
Bool * I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
U64 * I32_size(void);
Bool * I32_lt(I32 * a, I32 * b);
Bool * I32_gt(I32 * a, I32 * b);
Bool * I32_neq(I32 * a, I32 * b);
Bool * I32_lte(I32 * a, I32 * b);
Bool * I32_gte(I32 * a, I32 * b);
F32 * F32_from_i64(I64 * val);
U64 * F32_size(void);
Bool * F32_lt(F32 * a, F32 * b);
Bool * F32_gt(F32 * a, F32 * b);
Bool * F32_neq(F32 * a, F32 * b);
Bool * F32_lte(F32 * a, F32 * b);
Bool * F32_gte(F32 * a, F32 * b);
Str * U32_to_str(U32 * val);
U64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Bool * U32_gt(U32 * a, U32 * b);
Bool * U32_neq(U32 * a, U32 * b);
Bool * U32_lte(U32 * a, U32 * b);
Bool * U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
U64 * U64_size(void);
Bool * U64_lt(U64 * a, U64 * b);
Bool * U64_gt(U64 * a, U64 * b);
Bool * U64_neq(U64 * a, U64 * b);
Bool * U64_lte(U64 * a, U64 * b);
Bool * U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
U64 * I64_size(void);
Bool * I64_lt(I64 * a, I64 * b);
Bool * I64_gt(I64 * a, I64 * b);
Bool * I64_neq(I64 * a, I64 * b);
Bool * I64_lte(I64 * a, I64 * b);
Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
Str * Bool_to_str(Bool * b);
I64 * Bool_cmp(Bool * a, Bool * b);
U64 * Bool_size(void);
Bool * Bool_lt(Bool * a, Bool * b);
Bool * Bool_gt(Bool * a, Bool * b);
Bool * Bool_neq(Bool * a, Bool * b);
Bool * Bool_lte(Bool * a, Bool * b);
Bool * Bool_gte(Bool * a, Bool * b);
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
Bool * assert(Str * loc_str, Bool * cond);
void expect(Str * loc_str, Bool * cond, Array * parts);
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
Vec * Str_split(Str * self, Str * delim);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Bool * Str_lt(Str * a, Str * b);
Bool * Str_gt(Str * a, Str * b);
Bool * Str_neq(Str * a, Str * b);
Bool * Str_lte(Str * a, Str * b);
Bool * Str_gte(Str * a, Str * b);
Str * join(Vec * parts, Str * sep);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Tuple * Tuple_new(void);
U64 * Tuple_len(Tuple * self);
void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val);
void * Tuple_get(Tuple * self, U64 * i);
Str * Tuple_type_at(Tuple * self, U64 * i);
U64 * Tuple_size_at(Tuple * self, U64 * i);
void Tuple_delete(Tuple * self, Bool * call_free);
Tuple * Tuple_clone(Tuple * self);
U64 * Tuple_size(void);
Bool * TilType_eq(TilType * self, TilType * other);
TilType * TilType_clone(TilType * self);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
U64 * TilType_size(void);
Str * til_type_name_c(TilType * t);
Bool * Declaration_eq(Declaration * a, Declaration * b);
Str * Declaration_to_str(Declaration * self);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool * call_free);
U64 * Declaration_size(void);
Bool * FuncType_eq(FuncType * self, FuncType * other);
FuncType * FuncType_clone(FuncType * self);
void FuncType_delete(FuncType * self, Bool * call_free);
Str * FuncType_to_str(FuncType * self);
U64 * FuncType_size(void);
Param * Param_clone(Param * self);
void Param_delete(Param * self, Bool * call_free);
U64 * Param_size(void);
Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b);
Str * FunctionDef_to_str(FunctionDef * self);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U64 * FunctionDef_size(void);
Bool * ExprData_eq(ExprData * self, ExprData * other);
ExprData * ExprData_clone(ExprData * self);
void ExprData_delete(ExprData * self, Bool * call_free);
Str * ExprData_to_str(ExprData * self);
U64 * ExprData_size(void);
void Expr_error(Expr * self, Str * msg);
void Expr_todo_error(Expr * self, Str * msg);
void Expr_lang_error(Expr * self, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
Expr * Expr_child(Expr * parent, I64 * i);
I64 * Expr_child_count(Expr * parent);
Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U64 * Expr_size(void);
Str * node_name(ExprData * data);
Str * func_type_name(FuncType * ft);
void ast_print(Expr * e, U32 indent);
Bool * enum_has_payloads(Expr * enum_def);
I32 * enum_variant_tag(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 tag);
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
Parser * Parser_clone(Parser * self);
void Parser_delete(Parser * self, Bool * call_free);
U64 * Parser_size(void);
Token * peek(Parser * p);
Token * advance(Parser * p);
Bool check(Parser * p, TokenType * type);
Token * expect_token(Parser * p, TokenType * type);
Str * expect_text(Parser * p, TokenType * type);
U32 peek_line(Parser * p);
U32 peek_col(Parser * p);
Str * parse_fn_signature(Parser * p, U32 line, U32 col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool is_mut, Bool is_own);
Expr * parse_statement(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U64 * TypeBinding_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
Bool * Mode_eq(Mode * a, Mode * b);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
Mode * mode_resolve(Str * name);
Bool * mode_is_lib(Mode * m);
Bool * mode_is_lib_output(Mode * m);
Bool * TilType_eq(TilType *, TilType *);
TilType *TilType_Unknown();
TilType *TilType_None();
TilType *TilType_I64();
TilType *TilType_U8();
TilType *TilType_I16();
TilType *TilType_I32();
TilType *TilType_U32();
TilType *TilType_U64();
TilType *TilType_F32();
TilType *TilType_Bool();
TilType *TilType_Struct();
TilType *TilType_StructDef();
TilType *TilType_Enum();
TilType *TilType_EnumDef();
TilType *TilType_FuncDef();
TilType *TilType_FuncPtr();
TilType *TilType_Dynamic();
Bool * FuncType_eq(FuncType *, FuncType *);
FuncType *FuncType_Func();
FuncType *FuncType_Proc();
FuncType *FuncType_Test();
FuncType *FuncType_Macro();
FuncType *FuncType_ExtFunc();
FuncType *FuncType_ExtProc();
Bool * ExprData_eq(ExprData *, ExprData *);
Bool * ExprData_is_Body(ExprData *);
ExprData *ExprData_Body();
Bool * ExprData_is_LiteralStr(ExprData *);
ExprData *ExprData_LiteralStr(Str *);
Str * ExprData_get_LiteralStr(ExprData *);
Bool * ExprData_is_LiteralNum(ExprData *);
ExprData *ExprData_LiteralNum(Str *);
Str * ExprData_get_LiteralNum(ExprData *);
Bool * ExprData_is_LiteralBool(ExprData *);
ExprData *ExprData_LiteralBool(Str *);
Str * ExprData_get_LiteralBool(ExprData *);
Bool * ExprData_is_LiteralNull(ExprData *);
ExprData *ExprData_LiteralNull();
Bool * ExprData_is_Ident(ExprData *);
ExprData *ExprData_Ident(Str *);
Str * ExprData_get_Ident(ExprData *);
Bool * ExprData_is_Decl(ExprData *);
ExprData *ExprData_Decl(Declaration *);
Declaration * ExprData_get_Decl(ExprData *);
Bool * ExprData_is_Assign(ExprData *);
ExprData *ExprData_Assign(Str *);
Str * ExprData_get_Assign(ExprData *);
Bool * ExprData_is_FCall(ExprData *);
ExprData *ExprData_FCall();
Bool * ExprData_is_FuncDef(ExprData *);
ExprData *ExprData_FuncDef(FunctionDef *);
FunctionDef * ExprData_get_FuncDef(ExprData *);
Bool * ExprData_is_StructDef(ExprData *);
ExprData *ExprData_StructDef();
Bool * ExprData_is_EnumDef(ExprData *);
ExprData *ExprData_EnumDef();
Bool * ExprData_is_FieldAccess(ExprData *);
ExprData *ExprData_FieldAccess(Str *);
Str * ExprData_get_FieldAccess(ExprData *);
Bool * ExprData_is_FieldAssign(ExprData *);
ExprData *ExprData_FieldAssign(Str *);
Str * ExprData_get_FieldAssign(ExprData *);
Bool * ExprData_is_Return(ExprData *);
ExprData *ExprData_Return();
Bool * ExprData_is_If(ExprData *);
ExprData *ExprData_If();
Bool * ExprData_is_While(ExprData *);
ExprData *ExprData_While();
Bool * ExprData_is_ForIn(ExprData *);
ExprData *ExprData_ForIn(Str *);
Str * ExprData_get_ForIn(ExprData *);
Bool * ExprData_is_NamedArg(ExprData *);
ExprData *ExprData_NamedArg(Str *);
Str * ExprData_get_NamedArg(ExprData *);
Bool * ExprData_is_Break(ExprData *);
ExprData *ExprData_Break();
Bool * ExprData_is_Continue(ExprData *);
ExprData *ExprData_Continue();
Bool * ExprData_is_MapLit(ExprData *);
ExprData *ExprData_MapLit();
Bool * ExprData_is_SetLit(ExprData *);
ExprData *ExprData_SetLit();
Bool * ExprData_is_Switch(ExprData *);
ExprData *ExprData_Switch();
Bool * ExprData_is_Case(ExprData *);
ExprData *ExprData_Case();
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

#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ULLONG_MAX
Str *Str_lit(const char *s, unsigned long long len) {
    Str *r = malloc(sizeof(Str));
    r->c_str = (U8 *)s;
    r->count = len;
    r->cap = TIL_CAP_LIT;
    return r;
}
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

static I64 *_t4251;
static I64 *_t4252;
static I64 *_t4253;
static U64 *CAP_LIT;
static I64 *_t4254;
static I64 *_t4255;
static I64 *_t4256;
static U64 *CAP_VIEW;
static Str *_t4257;
static U64 *_t4258;
static Str *_t4259;
static U64 *_t4260;
static Map *core_modes;
static Bool *_t4261;
static Bool *_t4262;
static Bool *_t4263;
static Bool *_t4264;
static Str *_t4265;
static Mode *_t4266;
static Bool *_t4267;
static Bool *_t4268;
static Bool *_t4269;
static Bool *_t4270;
static Str *_t4271;
static Mode *_t4272;
static Bool *_t4273;
static Bool *_t4274;
static Bool *_t4275;
static Bool *_t4276;
static Str *_t4277;
static Mode *_t4278;
static Bool *_t4279;
static Bool *_t4280;
static Bool *_t4281;
static Bool *_t4282;
static Str *_t4283;
static Mode *_t4284;
static Bool *_t4285;
static Bool *_t4286;
static Bool *_t4287;
static Bool *_t4288;
static Str *_t4289;
static Mode *_t4290;
static Bool *_t4291;
static Bool *_t4292;
static Bool *_t4293;
static Bool *_t4294;
static Str *_t4295;
static Mode *_t4296;
static Bool *_t4297;
static Bool *_t4298;
static Bool *_t4299;
static Bool *_t4300;
static Str *_t4301;
static Mode *_t4302;
static Bool *_t4303;
static Bool *_t4304;
static Bool *_t4305;
static Bool *_t4306;
static Str *_t4307;
static Mode *_t4308;

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t2 = U8_to_i64(DEREF(val));
    (void)_t2;
    Str *_t3 = I64_to_str(&(I64){_t2});
    (void)_t3;
    ;
    return _t3;
}

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t19 = I16_to_i64(DEREF(val));
    (void)_t19;
    Str *_t20 = I64_to_str(&(I64){_t19});
    (void)_t20;
    ;
    return _t20;
}

I16 * I16_neg(I16 * a) {
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

I16 * I16_abs(I16 * a) {
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

U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t48 = I32_to_i64(DEREF(val));
    (void)_t48;
    Str *_t49 = I64_to_str(&(I64){_t48});
    (void)_t49;
    ;
    return _t49;
}

I32 * I32_neg(I32 * a) {
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

I32 * I32_abs(I32 * a) {
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

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t77 = F32_from_i64_ext(val);
    (void)_t77;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t77; return _r; }
}

U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t93 = U32_to_i64(DEREF(val));
    (void)_t93;
    Str *_t94 = I64_to_str(&(I64){_t93});
    (void)_t94;
    ;
    return _t94;
}

U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t110 = U64_to_str_ext(val);
    (void)_t110;
    return _t110;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t111 = U64_from_i64_ext(val);
    (void)_t111;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t111; return _r; }
}

U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

Str * I64_to_str(I64 * val) {
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

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t176 = 0;
    (void)_t176;
    I64 _t177 = I64_sub(_t176, DEREF(a));
    (void)_t177;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t177; return _r; }
}

I64 * I64_abs(I64 * a) {
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

U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
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
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Bool_to_str(Bool * b) {
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

I64 * Bool_cmp(Bool * a, Bool * b) {
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

U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
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
    if (!self) return;
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
    if (!self) return;
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
    if (!self) return;
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
    if (!self) return;
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

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t1011 = Str_lit("Str", 3ULL);
    (void)_t1011;
    U64 _t1012; { U64 *_hp = (U64 *)Str_size(); _t1012 = *_hp; free(_hp); }
    (void)_t1012;
    Vec *parts = Vec_new(_t1011, &(U64){_t1012});
    (void)parts;
    Str_delete(_t1011, &(Bool){1});
    ;
    U64 _t1013; { U64 *_hp = (U64 *)Str_len(delim); _t1013 = *_hp; free(_hp); }
    (void)_t1013;
    U64 _t1014 = 0;
    (void)_t1014;
    Bool _t1015 = U64_eq(_t1013, _t1014);
    (void)_t1015;
    ;
    ;
    if (_t1015) {
        Str *_t995 = Str_clone(self);
        (void)_t995;
        Vec_push(parts, _t995);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1005; { U64 *_hp = (U64 *)Str_len(self); _t1005 = *_hp; free(_hp); }
        (void)_t1005;
        U64 _t1006; { U64 *_hp = (U64 *)Str_len(delim); _t1006 = *_hp; free(_hp); }
        (void)_t1006;
        U64 _t1007 = U64_sub(_t1005, _t1006);
        (void)_t1007;
        ;
        ;
        Bool _wcond996; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1007}); _wcond996 = *_hp; free(_hp); }
        (void)_wcond996;
        ;
        if (_wcond996) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1008; { U64 *_hp = (U64 *)Str_len(delim); _t1008 = *_hp; free(_hp); }
        (void)_t1008;
        Str *_t1009 = Str_substr(self, &(U64){pos}, &(U64){_t1008});
        (void)_t1009;
        ;
        Bool _t1010; { Bool *_hp = (Bool *)Str_eq(_t1009, delim); _t1010 = *_hp; free(_hp); }
        (void)_t1010;
        Str_delete(_t1009, &(Bool){1});
        if (_t1010) {
            U64 _t997 = U64_sub(pos, start);
            (void)_t997;
            Str *_t998 = Str_substr(self, &(U64){start}, &(U64){_t997});
            (void)_t998;
            ;
            Str *_t999 = Str_clone(_t998);
            (void)_t999;
            Str_delete(_t998, &(Bool){1});
            Vec_push(parts, _t999);
            U64 _t1000; { U64 *_hp = (U64 *)Str_len(delim); _t1000 = *_hp; free(_hp); }
            (void)_t1000;
            U64 _t1001 = U64_add(pos, _t1000);
            (void)_t1001;
            ;
            start = _t1001;
            ;
            U64 _t1002 = U64_clone(&(U64){start});
            (void)_t1002;
            pos = _t1002;
            ;
        } else {
            U64 _t1003 = 1;
            (void)_t1003;
            U64 _t1004 = U64_add(pos, _t1003);
            (void)_t1004;
            ;
            pos = _t1004;
            ;
        }
        ;
    }
    ;
    U64 _t1016; { U64 *_hp = (U64 *)Str_len(self); _t1016 = *_hp; free(_hp); }
    (void)_t1016;
    U64 _t1017 = U64_sub(_t1016, start);
    (void)_t1017;
    ;
    Str *_t1018 = Str_substr(self, &(U64){start}, &(U64){_t1017});
    (void)_t1018;
    ;
    ;
    Str *_t1019 = Str_clone(_t1018);
    (void)_t1019;
    Str_delete(_t1018, &(Bool){1});
    Vec_push(parts, _t1019);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1055 = malloc(DEREF(elem_size));
    (void)_t1055;
    U64 _t1056 = 0;
    (void)_t1056;
    I64 _t1057 = 1;
    (void)_t1057;
    U64 _t1058 = U64_clone(elem_size);
    (void)_t1058;
    Vec *_t1059 = malloc(sizeof(Vec));
    _t1059->data = _t1055;
    _t1059->count = _t1056;
    _t1059->cap = _t1057;
    _t1059->elem_size = _t1058;
    { Str *_ca = Str_clone(elem_type); _t1059->elem_type = *_ca; free(_ca); }
    (void)_t1059;
    ;
    ;
    ;
    return _t1059;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1064 = U64_eq(self->count, self->cap);
    (void)_t1064;
    if (_t1064) {
        U64 _t1060 = 2;
        (void)_t1060;
        U64 new_cap = U64_mul(self->cap, _t1060);
        (void)new_cap;
        ;
        U64 _t1061 = U64_mul(new_cap, self->elem_size);
        (void)_t1061;
        void *_t1062 = realloc(self->data, _t1061);
        (void)_t1062;
        ;
        self->data = _t1062;
        U64 _t1063 = U64_clone(&(U64){new_cap});
        (void)_t1063;
        ;
        self->cap = _t1063;
        ;
    }
    ;
    U64 *_t1065 = malloc(sizeof(U64)); *_t1065 = U64_mul(self->count, self->elem_size);
    (void)_t1065;
    void *_t1066 = ptr_add(self->data, DEREF(_t1065));
    (void)_t1066;
    memcpy(_t1066, val, self->elem_size);
    U64_delete(_t1065, &(Bool){1});
    free(val);
    U64 _t1067 = 1;
    (void)_t1067;
    U64 _t1068 = U64_add(self->count, _t1067);
    (void)_t1068;
    ;
    self->count = _t1068;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1083; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1083 = *_hp; free(_hp); }
    (void)_t1083;
    if (_t1083) {
        Str *_t1069 = Str_lit("Str", 3ULL);
        (void)_t1069;
        U64 _t1070; { U64 *_hp = (U64 *)Str_size(); _t1070 = *_hp; free(_hp); }
        (void)_t1070;
        U64 _t1071 = 5;
        (void)_t1071;
        Array *_va18 = Array_new(_t1069, &(U64){_t1070}, &(U64){_t1071});
        (void)_va18;
        Str_delete(_t1069, &(Bool){1});
        ;
        ;
        U64 _t1072 = 0;
        (void)_t1072;
        Str *_t1073 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1073;
        Array_set(_va18, &(U64){_t1072}, _t1073);
        ;
        U64 _t1074 = 1;
        (void)_t1074;
        Str *_t1075 = U64_to_str(DEREF(i));
        (void)_t1075;
        Array_set(_va18, &(U64){_t1074}, _t1075);
        ;
        U64 _t1076 = 2;
        (void)_t1076;
        Str *_t1077 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1077;
        Array_set(_va18, &(U64){_t1076}, _t1077);
        ;
        U64 _t1078 = 3;
        (void)_t1078;
        Str *_t1079 = U64_to_str(self->count);
        (void)_t1079;
        Array_set(_va18, &(U64){_t1078}, _t1079);
        ;
        U64 _t1080 = 4;
        (void)_t1080;
        Str *_t1081 = Str_lit(")", 1ULL);
        (void)_t1081;
        Array_set(_va18, &(U64){_t1080}, _t1081);
        ;
        Str *_t1082 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1082;
        panic(_t1082, _va18);
        Str_delete(_t1082, &(Bool){1});
    }
    ;
    U64 *_t1084 = malloc(sizeof(U64)); *_t1084 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1084;
    void *_t1085 = ptr_add(self->data, DEREF(_t1084));
    (void)_t1085;
    U64_delete(_t1084, &(Bool){1});
    return _t1085;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1099; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1099 = *_hp; free(_hp); }
    (void)_t1099;
    Bool _t1100 = Bool_not(_t1099);
    (void)_t1100;
    ;
    if (_t1100) {
        {
            U64 _fi1086 = 0;
            (void)_fi1086;
            while (1) {
                U64 _t1088 = 0;
                (void)_t1088;
                Range *_t1089 = Range_new(_t1088, self->count);
                (void)_t1089;
                ;
                U64 _t1090; { U64 *_hp = (U64 *)Range_len(_t1089); _t1090 = *_hp; free(_hp); }
                (void)_t1090;
                Range_delete(_t1089, &(Bool){1});
                Bool _wcond1087; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1086}, &(U64){_t1090}); _wcond1087 = *_hp; free(_hp); }
                (void)_wcond1087;
                ;
                if (_wcond1087) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1091 = 0;
                (void)_t1091;
                Range *_t1092 = Range_new(_t1091, self->count);
                (void)_t1092;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1092, _fi1086); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1092, &(Bool){1});
                U64 _t1093 = 1;
                (void)_t1093;
                U64 _t1094 = U64_add(_fi1086, _t1093);
                (void)_t1094;
                ;
                _fi1086 = _t1094;
                ;
                U64 *_t1095 = malloc(sizeof(U64)); *_t1095 = U64_mul(i, self->elem_size);
                (void)_t1095;
                ;
                void *_t1096 = ptr_add(self->data, DEREF(_t1095));
                (void)_t1096;
                Bool _t1097 = 0;
                (void)_t1097;
                dyn_call_delete(&self->elem_type, _t1096, &(Bool){_t1097});
                U64_delete(_t1095, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1101; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1101 = *_hp; free(_hp); }
    (void)_t1101;
    Bool _t1102 = Bool_not(_t1101);
    (void)_t1102;
    ;
    if (_t1102) {
        Bool _t1098 = 0;
        (void)_t1098;
        Str_delete(&self->elem_type, &(Bool){_t1098});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1117 = U64_mul(self->cap, self->elem_size);
    (void)_t1117;
    U8 *new_data = malloc(_t1117);
    (void)new_data;
    ;
    Bool _t1118; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1118 = *_hp; free(_hp); }
    (void)_t1118;
    Bool _t1119 = Bool_not(_t1118);
    (void)_t1119;
    ;
    if (_t1119) {
        {
            U64 _fi1103 = 0;
            (void)_fi1103;
            while (1) {
                U64 _t1105 = 0;
                (void)_t1105;
                Range *_t1106 = Range_new(_t1105, self->count);
                (void)_t1106;
                ;
                U64 _t1107; { U64 *_hp = (U64 *)Range_len(_t1106); _t1107 = *_hp; free(_hp); }
                (void)_t1107;
                Range_delete(_t1106, &(Bool){1});
                Bool _wcond1104; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1103}, &(U64){_t1107}); _wcond1104 = *_hp; free(_hp); }
                (void)_wcond1104;
                ;
                if (_wcond1104) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1108 = 0;
                (void)_t1108;
                Range *_t1109 = Range_new(_t1108, self->count);
                (void)_t1109;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1109, _fi1103); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1109, &(Bool){1});
                U64 _t1110 = 1;
                (void)_t1110;
                U64 _t1111 = U64_add(_fi1103, _t1110);
                (void)_t1111;
                ;
                _fi1103 = _t1111;
                ;
                U64 *_t1112 = malloc(sizeof(U64)); *_t1112 = U64_mul(i, self->elem_size);
                (void)_t1112;
                void *_t1113 = ptr_add(self->data, DEREF(_t1112));
                (void)_t1113;
                void *cloned = dyn_call_clone(&self->elem_type, _t1113);
                (void)cloned;
                U64_delete(_t1112, &(Bool){1});
                U64 *_t1114 = malloc(sizeof(U64)); *_t1114 = U64_mul(i, self->elem_size);
                (void)_t1114;
                ;
                void *_t1115 = ptr_add(new_data, DEREF(_t1114));
                (void)_t1115;
                memcpy(_t1115, cloned, self->elem_size);
                U64_delete(_t1114, &(Bool){1});
                free(cloned);
            }
            ;
        }
    } else {
        U64 _t1116 = U64_mul(self->count, self->elem_size);
        (void)_t1116;
        memcpy(new_data, self->data, _t1116);
        ;
    }
    ;
    Vec *_t1120 = malloc(sizeof(Vec));
    _t1120->data = new_data;
    _t1120->count = self->count;
    _t1120->cap = self->cap;
    _t1120->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1120->elem_type = *_ca; free(_ca); }
    (void)_t1120;
    return _t1120;
}

Tuple * Tuple_new(void) {
    U64 _t1122 = 8;
    (void)_t1122;
    Str *_t1123 = Str_lit("Str", 3ULL);
    (void)_t1123;
    U64 _t1124; { U64 *_hp = (U64 *)Str_size(); _t1124 = *_hp; free(_hp); }
    (void)_t1124;
    Str *_t1125 = Str_lit("U64", 3ULL);
    (void)_t1125;
    U64 _t1126; { U64 *_hp = (U64 *)U64_size(); _t1126 = *_hp; free(_hp); }
    (void)_t1126;
    void *_t1127 = malloc(_t1122);
    (void)_t1127;
    ;
    U64 _t1128 = 0;
    (void)_t1128;
    I64 _t1129 = 8;
    (void)_t1129;
    Tuple *_t1130 = malloc(sizeof(Tuple));
    _t1130->data = _t1127;
    _t1130->total_size = _t1128;
    _t1130->cap = _t1129;
    { Vec *_ca = Vec_new(_t1123, &(U64){_t1124}); _t1130->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1125, &(U64){_t1126}); _t1130->type_sizes = *_ca; free(_ca); }
    (void)_t1130;
    Str_delete(_t1123, &(Bool){1});
    ;
    Str_delete(_t1125, &(Bool){1});
    ;
    ;
    ;
    return _t1130;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1131; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1131 = *_hp; free(_hp); }
    (void)_t1131;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1131; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1138; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1138 = *_hp; free(_hp); }
    (void)_t1138;
    if (_t1138) {
        U64 _t1135 = 2;
        (void)_t1135;
        U64 new_cap = U64_mul(self->cap, _t1135);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1132; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1132 = *_hp; free(_hp); }
            (void)_wcond1132;
            if (_wcond1132) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1133 = 2;
            (void)_t1133;
            U64 _t1134 = U64_mul(new_cap, _t1133);
            (void)_t1134;
            ;
            new_cap = _t1134;
            ;
        }
        void *_t1136 = realloc(self->data, new_cap);
        (void)_t1136;
        self->data = _t1136;
        U64 _t1137 = U64_clone(&(U64){new_cap});
        (void)_t1137;
        ;
        self->cap = _t1137;
        ;
    }
    ;
    void *_t1139 = ptr_add(self->data, self->total_size);
    (void)_t1139;
    memcpy(_t1139, val, DEREF(elem_size));
    free(val);
    Str *_t1140 = Str_clone(elem_type);
    (void)_t1140;
    Vec_push(&self->type_names, _t1140);
    U64 _t1141 = U64_clone(elem_size);
    (void)_t1141;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1141; _oa; }));
    U64 _t1142 = U64_clone(&(U64){new_total});
    (void)_t1142;
    ;
    self->total_size = _t1142;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1168; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1168 = *_hp; free(_hp); }
    (void)_t1168;
    Bool _t1169; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1168}); _t1169 = *_hp; free(_hp); }
    (void)_t1169;
    ;
    if (_t1169) {
        Str *_t1143 = Str_lit("Str", 3ULL);
        (void)_t1143;
        U64 _t1144; { U64 *_hp = (U64 *)Str_size(); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        U64 _t1145 = 5;
        (void)_t1145;
        Array *_va19 = Array_new(_t1143, &(U64){_t1144}, &(U64){_t1145});
        (void)_va19;
        Str_delete(_t1143, &(Bool){1});
        ;
        ;
        U64 _t1146 = 0;
        (void)_t1146;
        Str *_t1147 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1147;
        Array_set(_va19, &(U64){_t1146}, _t1147);
        ;
        U64 _t1148 = 1;
        (void)_t1148;
        Str *_t1149 = U64_to_str(DEREF(i));
        (void)_t1149;
        Array_set(_va19, &(U64){_t1148}, _t1149);
        ;
        U64 _t1150 = 2;
        (void)_t1150;
        Str *_t1151 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1151;
        Array_set(_va19, &(U64){_t1150}, _t1151);
        ;
        U64 _t1152; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1152 = *_hp; free(_hp); }
        (void)_t1152;
        U64 _t1153 = 3;
        (void)_t1153;
        Str *_t1154 = U64_to_str(_t1152);
        (void)_t1154;
        ;
        Array_set(_va19, &(U64){_t1153}, _t1154);
        ;
        U64 _t1155 = 4;
        (void)_t1155;
        Str *_t1156 = Str_lit(")", 1ULL);
        (void)_t1156;
        Array_set(_va19, &(U64){_t1155}, _t1156);
        ;
        Str *_t1157 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1157;
        panic(_t1157, _va19);
        Str_delete(_t1157, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1158 = 0;
        (void)_fi1158;
        while (1) {
            U64 _t1160 = 0;
            (void)_t1160;
            Range *_t1161 = Range_new(_t1160, DEREF(i));
            (void)_t1161;
            ;
            U64 _t1162; { U64 *_hp = (U64 *)Range_len(_t1161); _t1162 = *_hp; free(_hp); }
            (void)_t1162;
            Range_delete(_t1161, &(Bool){1});
            Bool _wcond1159; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1158}, &(U64){_t1162}); _wcond1159 = *_hp; free(_hp); }
            (void)_wcond1159;
            ;
            if (_wcond1159) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1163 = 0;
            (void)_t1163;
            Range *_t1164 = Range_new(_t1163, DEREF(i));
            (void)_t1164;
            ;
            U64 *j = Range_get(_t1164, _fi1158);
            (void)j;
            Range_delete(_t1164, &(Bool){1});
            U64 _t1165 = 1;
            (void)_t1165;
            U64 _t1166 = U64_add(_fi1158, _t1165);
            (void)_t1166;
            ;
            _fi1158 = _t1166;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1167 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1167;
            U64_delete(j, &(Bool){1});
            *offset = _t1167;
            ;
        }
        ;
    }
    void *_t1170 = ptr_add(self->data, DEREF(offset));
    (void)_t1170;
    U64_delete(offset, &(Bool){1});
    return _t1170;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1171 = Vec_get(&self->type_names, i);
    (void)_t1171;
    return _t1171;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1172 = Vec_get(&self->type_sizes, i);
    (void)_t1172;
    return _t1172;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1173 = 0;
        (void)_fi1173;
        while (1) {
            U64 _t1175 = 0;
            (void)_t1175;
            U64 _t1176; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1176 = *_hp; free(_hp); }
            (void)_t1176;
            Range *_t1177 = Range_new(_t1175, _t1176);
            (void)_t1177;
            ;
            ;
            U64 _t1178; { U64 *_hp = (U64 *)Range_len(_t1177); _t1178 = *_hp; free(_hp); }
            (void)_t1178;
            Range_delete(_t1177, &(Bool){1});
            Bool _wcond1174; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1173}, &(U64){_t1178}); _wcond1174 = *_hp; free(_hp); }
            (void)_wcond1174;
            ;
            if (_wcond1174) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1179 = 0;
            (void)_t1179;
            U64 _t1180; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1180 = *_hp; free(_hp); }
            (void)_t1180;
            Range *_t1181 = Range_new(_t1179, _t1180);
            (void)_t1181;
            ;
            ;
            U64 *i = Range_get(_t1181, _fi1173);
            (void)i;
            Range_delete(_t1181, &(Bool){1});
            U64 _t1182 = 1;
            (void)_t1182;
            U64 _t1183 = U64_add(_fi1173, _t1182);
            (void)_t1183;
            ;
            _fi1173 = _t1183;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1184 = ptr_add(self->data, DEREF(offset));
            (void)_t1184;
            Bool _t1185 = 0;
            (void)_t1185;
            dyn_call_delete(tn, _t1184, &(Bool){_t1185});
            ;
            U64 _t1186 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1186;
            U64_delete(i, &(Bool){1});
            *offset = _t1186;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1187 = 0;
    (void)_t1187;
    Vec_delete(&self->type_names, &(Bool){_t1187});
    ;
    Bool _t1188 = 0;
    (void)_t1188;
    Vec_delete(&self->type_sizes, &(Bool){_t1188});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1205 = 0;
    (void)_t1205;
    Bool _t1206 = U64_eq(new_cap, _t1205);
    (void)_t1206;
    ;
    if (_t1206) {
        I64 _t1189 = 8;
        (void)_t1189;
        U64 _t1190; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1189}); _t1190 = *_hp; free(_hp); }
        (void)_t1190;
        ;
        new_cap = _t1190;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1191 = 0;
        (void)_fi1191;
        while (1) {
            U64 _t1193 = 0;
            (void)_t1193;
            U64 _t1194; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1194 = *_hp; free(_hp); }
            (void)_t1194;
            Range *_t1195 = Range_new(_t1193, _t1194);
            (void)_t1195;
            ;
            ;
            U64 _t1196; { U64 *_hp = (U64 *)Range_len(_t1195); _t1196 = *_hp; free(_hp); }
            (void)_t1196;
            Range_delete(_t1195, &(Bool){1});
            Bool _wcond1192; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1191}, &(U64){_t1196}); _wcond1192 = *_hp; free(_hp); }
            (void)_wcond1192;
            ;
            if (_wcond1192) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1197 = 0;
            (void)_t1197;
            U64 _t1198; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1198 = *_hp; free(_hp); }
            (void)_t1198;
            Range *_t1199 = Range_new(_t1197, _t1198);
            (void)_t1199;
            ;
            ;
            U64 *i = Range_get(_t1199, _fi1191);
            (void)i;
            Range_delete(_t1199, &(Bool){1});
            U64 _t1200 = 1;
            (void)_t1200;
            U64 _t1201 = U64_add(_fi1191, _t1200);
            (void)_t1201;
            ;
            _fi1191 = _t1201;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1202 = ptr_add(self->data, DEREF(offset));
            (void)_t1202;
            void *cloned = dyn_call_clone(tn, _t1202);
            (void)cloned;
            void *_t1203 = ptr_add(new_data, DEREF(offset));
            (void)_t1203;
            memcpy(_t1203, cloned, DEREF(ts));
            free(cloned);
            U64 _t1204 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1204;
            U64_delete(i, &(Bool){1});
            *offset = _t1204;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1207 = U64_clone(&(U64){new_cap});
    (void)_t1207;
    ;
    Vec *_t1208 = Vec_clone(&self->type_names);
    (void)_t1208;
    Vec *_t1209 = Vec_clone(&self->type_sizes);
    (void)_t1209;
    Tuple *_t1210 = malloc(sizeof(Tuple));
    _t1210->data = new_data;
    _t1210->total_size = self->total_size;
    _t1210->cap = _t1207;
    { Vec *_ca = Vec_clone(_t1208); _t1210->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1209); _t1210->type_sizes = *_ca; free(_ca); }
    (void)_t1210;
    ;
    Vec_delete(_t1208, &(Bool){1});
    Vec_delete(_t1209, &(Bool){1});
    return _t1210;
}

TilType *TilType_Unknown() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Unknown };
    return r;
}
TilType *TilType_None() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_None };
    return r;
}
TilType *TilType_I64() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I64 };
    return r;
}
TilType *TilType_U8() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U8 };
    return r;
}
TilType *TilType_I16() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I16 };
    return r;
}
TilType *TilType_I32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I32 };
    return r;
}
TilType *TilType_U32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U32 };
    return r;
}
TilType *TilType_U64() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U64 };
    return r;
}
TilType *TilType_F32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_F32 };
    return r;
}
TilType *TilType_Bool() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Bool };
    return r;
}
TilType *TilType_Struct() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Struct };
    return r;
}
TilType *TilType_StructDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_StructDef };
    return r;
}
TilType *TilType_Enum() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Enum };
    return r;
}
TilType *TilType_EnumDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_EnumDef };
    return r;
}
TilType *TilType_FuncDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_FuncDef };
    return r;
}
TilType *TilType_FuncPtr() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_FuncPtr };
    return r;
}
TilType *TilType_Dynamic() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Dynamic };
    return r;
}
Bool *TilType_is_Unknown(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Unknown);
    return r;
}
Bool *TilType_is_None(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_None);
    return r;
}
Bool *TilType_is_I64(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I64);
    return r;
}
Bool *TilType_is_U8(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U8);
    return r;
}
Bool *TilType_is_I16(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I16);
    return r;
}
Bool *TilType_is_I32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I32);
    return r;
}
Bool *TilType_is_U32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U32);
    return r;
}
Bool *TilType_is_U64(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U64);
    return r;
}
Bool *TilType_is_F32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_F32);
    return r;
}
Bool *TilType_is_Bool(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Bool);
    return r;
}
Bool *TilType_is_Struct(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Struct);
    return r;
}
Bool *TilType_is_StructDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_StructDef);
    return r;
}
Bool *TilType_is_Enum(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Enum);
    return r;
}
Bool *TilType_is_EnumDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_EnumDef);
    return r;
}
Bool *TilType_is_FuncDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_FuncDef);
    return r;
}
Bool *TilType_is_FuncPtr(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_FuncPtr);
    return r;
}
Bool *TilType_is_Dynamic(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Dynamic);
    return r;
}
Bool * TilType_eq(TilType * self, TilType * other) {
    (void)self;
    (void)other;
    Bool _t1229; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        Bool _t1212; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t1212 = *_hp; free(_hp); }
        (void)_t1212;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1212; return _r; }
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TilType_is_None(self); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        Bool _t1213; { Bool *_hp = (Bool *)TilType_is_None(other); _t1213 = *_hp; free(_hp); }
        (void)_t1213;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1213; return _r; }
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TilType_is_I64(self); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        Bool _t1214; { Bool *_hp = (Bool *)TilType_is_I64(other); _t1214 = *_hp; free(_hp); }
        (void)_t1214;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1214; return _r; }
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TilType_is_U8(self); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        Bool _t1215; { Bool *_hp = (Bool *)TilType_is_U8(other); _t1215 = *_hp; free(_hp); }
        (void)_t1215;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1215; return _r; }
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TilType_is_I16(self); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        Bool _t1216; { Bool *_hp = (Bool *)TilType_is_I16(other); _t1216 = *_hp; free(_hp); }
        (void)_t1216;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1216; return _r; }
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TilType_is_I32(self); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        Bool _t1217; { Bool *_hp = (Bool *)TilType_is_I32(other); _t1217 = *_hp; free(_hp); }
        (void)_t1217;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1217; return _r; }
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TilType_is_U32(self); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Bool _t1218; { Bool *_hp = (Bool *)TilType_is_U32(other); _t1218 = *_hp; free(_hp); }
        (void)_t1218;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1218; return _r; }
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TilType_is_U64(self); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Bool _t1219; { Bool *_hp = (Bool *)TilType_is_U64(other); _t1219 = *_hp; free(_hp); }
        (void)_t1219;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1219; return _r; }
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TilType_is_F32(self); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Bool _t1220; { Bool *_hp = (Bool *)TilType_is_F32(other); _t1220 = *_hp; free(_hp); }
        (void)_t1220;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1220; return _r; }
    }
    ;
    Bool _t1238; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t1238 = *_hp; free(_hp); }
    (void)_t1238;
    if (_t1238) {
        Bool _t1221; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t1221 = *_hp; free(_hp); }
        (void)_t1221;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1221; return _r; }
    }
    ;
    Bool _t1239; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        Bool _t1222; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t1222 = *_hp; free(_hp); }
        (void)_t1222;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1222; return _r; }
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        Bool _t1223; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t1223 = *_hp; free(_hp); }
        (void)_t1223;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1223; return _r; }
    }
    ;
    Bool _t1241; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t1241 = *_hp; free(_hp); }
    (void)_t1241;
    if (_t1241) {
        Bool _t1224; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t1224 = *_hp; free(_hp); }
        (void)_t1224;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1224; return _r; }
    }
    ;
    Bool _t1242; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t1242 = *_hp; free(_hp); }
    (void)_t1242;
    if (_t1242) {
        Bool _t1225; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t1225 = *_hp; free(_hp); }
        (void)_t1225;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1225; return _r; }
    }
    ;
    Bool _t1243; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t1243 = *_hp; free(_hp); }
    (void)_t1243;
    if (_t1243) {
        Bool _t1226; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t1226 = *_hp; free(_hp); }
        (void)_t1226;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1226; return _r; }
    }
    ;
    Bool _t1244; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        Bool _t1227; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t1227 = *_hp; free(_hp); }
        (void)_t1227;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1227; return _r; }
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        Bool _t1228; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t1228 = *_hp; free(_hp); }
        (void)_t1228;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1228; return _r; }
    }
    ;
    Bool _t1246 = 0;
    (void)_t1246;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1246; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t1247; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        ;
        return TilType_None();
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t1252; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        ;
        return TilType_FuncPtr();
    }
    ;
    return TilType_Dynamic();
}

void TilType_delete(TilType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TilType_to_str(TilType * self) {
    (void)self;
    Bool _t1280; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        Str *_t1263 = Str_lit("Unknown", 7ULL);
        (void)_t1263;
        ;
        return _t1263;
    }
    ;
    Bool _t1281; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1281 = *_hp; free(_hp); }
    (void)_t1281;
    if (_t1281) {
        Str *_t1264 = Str_lit("None", 4ULL);
        (void)_t1264;
        ;
        return _t1264;
    }
    ;
    Bool _t1282; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        Str *_t1265 = Str_lit("I64", 3ULL);
        (void)_t1265;
        ;
        return _t1265;
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        Str *_t1266 = Str_lit("U8", 2ULL);
        (void)_t1266;
        ;
        return _t1266;
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        Str *_t1267 = Str_lit("I16", 3ULL);
        (void)_t1267;
        ;
        return _t1267;
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        Str *_t1268 = Str_lit("I32", 3ULL);
        (void)_t1268;
        ;
        return _t1268;
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        Str *_t1269 = Str_lit("U32", 3ULL);
        (void)_t1269;
        ;
        return _t1269;
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        Str *_t1270 = Str_lit("U64", 3ULL);
        (void)_t1270;
        ;
        return _t1270;
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        Str *_t1271 = Str_lit("F32", 3ULL);
        (void)_t1271;
        ;
        return _t1271;
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        Str *_t1272 = Str_lit("Bool", 4ULL);
        (void)_t1272;
        ;
        return _t1272;
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        Str *_t1273 = Str_lit("Struct", 6ULL);
        (void)_t1273;
        ;
        return _t1273;
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        Str *_t1274 = Str_lit("StructDef", 9ULL);
        (void)_t1274;
        ;
        return _t1274;
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        Str *_t1275 = Str_lit("Enum", 4ULL);
        (void)_t1275;
        ;
        return _t1275;
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        Str *_t1276 = Str_lit("EnumDef", 7ULL);
        (void)_t1276;
        ;
        return _t1276;
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        Str *_t1277 = Str_lit("FuncDef", 7ULL);
        (void)_t1277;
        ;
        return _t1277;
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        Str *_t1278 = Str_lit("FuncPtr", 7ULL);
        (void)_t1278;
        ;
        return _t1278;
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        Str *_t1279 = Str_lit("Dynamic", 7ULL);
        (void)_t1279;
        ;
        return _t1279;
    }
    ;
    Str *_t1297 = Str_lit("unknown", 7ULL);
    (void)_t1297;
    return _t1297;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t1335; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1335; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
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
    Bool _t1358; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t1358 = *_hp; free(_hp); }
    (void)_t1358;
    if (_t1358) {
        Bool _t1352; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t1352 = *_hp; free(_hp); }
        (void)_t1352;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1352; return _r; }
    }
    ;
    Bool _t1359; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t1359 = *_hp; free(_hp); }
    (void)_t1359;
    if (_t1359) {
        Bool _t1353; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t1353 = *_hp; free(_hp); }
        (void)_t1353;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1353; return _r; }
    }
    ;
    Bool _t1360; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t1360 = *_hp; free(_hp); }
    (void)_t1360;
    if (_t1360) {
        Bool _t1354; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t1354 = *_hp; free(_hp); }
        (void)_t1354;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1354; return _r; }
    }
    ;
    Bool _t1361; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t1361 = *_hp; free(_hp); }
    (void)_t1361;
    if (_t1361) {
        Bool _t1355; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t1355 = *_hp; free(_hp); }
        (void)_t1355;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1355; return _r; }
    }
    ;
    Bool _t1362; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    if (_t1362) {
        Bool _t1356; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t1356 = *_hp; free(_hp); }
        (void)_t1356;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1356; return _r; }
    }
    ;
    Bool _t1363; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t1363 = *_hp; free(_hp); }
    (void)_t1363;
    if (_t1363) {
        Bool _t1357; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t1357 = *_hp; free(_hp); }
        (void)_t1357;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1357; return _r; }
    }
    ;
    Bool _t1364 = 0;
    (void)_t1364;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1364; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t1365; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1365 = *_hp; free(_hp); }
    (void)_t1365;
    if (_t1365) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t1366; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    if (_t1366) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t1367; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    if (_t1367) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t1368; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        ;
        return FuncType_ExtFunc();
    }
    ;
    return FuncType_ExtProc();
}

void FuncType_delete(FuncType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * FuncType_to_str(FuncType * self) {
    (void)self;
    Bool _t1376; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Str *_t1370 = Str_lit("Func", 4ULL);
        (void)_t1370;
        ;
        return _t1370;
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Str *_t1371 = Str_lit("Proc", 4ULL);
        (void)_t1371;
        ;
        return _t1371;
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Str *_t1372 = Str_lit("Test", 4ULL);
        (void)_t1372;
        ;
        return _t1372;
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Str *_t1373 = Str_lit("Macro", 5ULL);
        (void)_t1373;
        ;
        return _t1373;
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Str *_t1374 = Str_lit("ExtFunc", 7ULL);
        (void)_t1374;
        ;
        return _t1374;
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Str *_t1375 = Str_lit("ExtProc", 7ULL);
        (void)_t1375;
        ;
        return _t1375;
    }
    ;
    Str *_t1382 = Str_lit("unknown", 7ULL);
    (void)_t1382;
    return _t1382;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t1394; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1394; return _r; }
}

Str * FunctionDef_to_str(FunctionDef * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->return_type; return _r; }
}

ExprData *ExprData_Body() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Body;
    return r;
}
ExprData *ExprData_LiteralStr(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralStr;
    { Str * _tmp = Str_clone(val); r->data.LiteralStr = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralNum(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralNum;
    { Str * _tmp = Str_clone(val); r->data.LiteralNum = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralBool(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralBool;
    { Str * _tmp = Str_clone(val); r->data.LiteralBool = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralNull() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralNull;
    return r;
}
ExprData *ExprData_Ident(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Ident;
    { Str * _tmp = Str_clone(val); r->data.Ident = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Decl(Declaration * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Decl;
    { Declaration * _tmp = Declaration_clone(val); r->data.Decl = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Assign(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Assign;
    { Str * _tmp = Str_clone(val); r->data.Assign = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_FCall() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FCall;
    return r;
}
ExprData *ExprData_FuncDef(FunctionDef * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FuncDef;
    { FunctionDef * _tmp = FunctionDef_clone(val); r->data.FuncDef = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_StructDef() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_StructDef;
    return r;
}
ExprData *ExprData_EnumDef() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_EnumDef;
    return r;
}
ExprData *ExprData_FieldAccess(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FieldAccess;
    { Str * _tmp = Str_clone(val); r->data.FieldAccess = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_FieldAssign(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FieldAssign;
    { Str * _tmp = Str_clone(val); r->data.FieldAssign = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Return() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Return;
    return r;
}
ExprData *ExprData_If() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_If;
    return r;
}
ExprData *ExprData_While() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_While;
    return r;
}
ExprData *ExprData_ForIn(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_ForIn;
    { Str * _tmp = Str_clone(val); r->data.ForIn = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_NamedArg(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_NamedArg;
    { Str * _tmp = Str_clone(val); r->data.NamedArg = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Break() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Break;
    return r;
}
ExprData *ExprData_Continue() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Continue;
    return r;
}
ExprData *ExprData_MapLit() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_MapLit;
    return r;
}
ExprData *ExprData_SetLit() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_SetLit;
    return r;
}
ExprData *ExprData_Switch() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Switch;
    return r;
}
ExprData *ExprData_Case() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Case;
    return r;
}
Bool *ExprData_is_Body(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Body);
    return r;
}
Bool *ExprData_is_LiteralStr(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralStr);
    return r;
}
Bool *ExprData_is_LiteralNum(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralNum);
    return r;
}
Bool *ExprData_is_LiteralBool(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralBool);
    return r;
}
Bool *ExprData_is_LiteralNull(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralNull);
    return r;
}
Bool *ExprData_is_Ident(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Ident);
    return r;
}
Bool *ExprData_is_Decl(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Decl);
    return r;
}
Bool *ExprData_is_Assign(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Assign);
    return r;
}
Bool *ExprData_is_FCall(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FCall);
    return r;
}
Bool *ExprData_is_FuncDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FuncDef);
    return r;
}
Bool *ExprData_is_StructDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_StructDef);
    return r;
}
Bool *ExprData_is_EnumDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_EnumDef);
    return r;
}
Bool *ExprData_is_FieldAccess(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FieldAccess);
    return r;
}
Bool *ExprData_is_FieldAssign(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FieldAssign);
    return r;
}
Bool *ExprData_is_Return(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Return);
    return r;
}
Bool *ExprData_is_If(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_If);
    return r;
}
Bool *ExprData_is_While(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_While);
    return r;
}
Bool *ExprData_is_ForIn(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_ForIn);
    return r;
}
Bool *ExprData_is_NamedArg(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_NamedArg);
    return r;
}
Bool *ExprData_is_Break(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Break);
    return r;
}
Bool *ExprData_is_Continue(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Continue);
    return r;
}
Bool *ExprData_is_MapLit(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_MapLit);
    return r;
}
Bool *ExprData_is_SetLit(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_SetLit);
    return r;
}
Bool *ExprData_is_Switch(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Switch);
    return r;
}
Bool *ExprData_is_Case(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Case);
    return r;
}
Str * ExprData_get_LiteralStr(ExprData *self) {
    return Str_clone(&self->data.LiteralStr);
}
Str * ExprData_get_LiteralNum(ExprData *self) {
    return Str_clone(&self->data.LiteralNum);
}
Str * ExprData_get_LiteralBool(ExprData *self) {
    return Str_clone(&self->data.LiteralBool);
}
Str * ExprData_get_Ident(ExprData *self) {
    return Str_clone(&self->data.Ident);
}
Declaration * ExprData_get_Decl(ExprData *self) {
    return Declaration_clone(&self->data.Decl);
}
Str * ExprData_get_Assign(ExprData *self) {
    return Str_clone(&self->data.Assign);
}
FunctionDef * ExprData_get_FuncDef(ExprData *self) {
    return FunctionDef_clone(&self->data.FuncDef);
}
Str * ExprData_get_FieldAccess(ExprData *self) {
    return Str_clone(&self->data.FieldAccess);
}
Str * ExprData_get_FieldAssign(ExprData *self) {
    return Str_clone(&self->data.FieldAssign);
}
Str * ExprData_get_ForIn(ExprData *self) {
    return Str_clone(&self->data.ForIn);
}
Str * ExprData_get_NamedArg(ExprData *self) {
    return Str_clone(&self->data.NamedArg);
}
Bool * ExprData_eq(ExprData * self, ExprData * other) {
    (void)self;
    (void)other;
    Bool _t1491; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1491 = *_hp; free(_hp); }
    (void)_t1491;
    if (_t1491) {
        Bool _t1411; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t1411 = *_hp; free(_hp); }
        (void)_t1411;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1411; return _r; }
    }
    ;
    Bool _t1492; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1492 = *_hp; free(_hp); }
    (void)_t1492;
    if (_t1492) {
        Bool _t1413; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t1413 = *_hp; free(_hp); }
        (void)_t1413;
        Bool _t1414 = Bool_not(_t1413);
        (void)_t1414;
        ;
        if (_t1414) {
            Bool _t1412 = 0;
            (void)_t1412;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1412; return _r; }
        }
        ;
        Str *_t1415 = ExprData_get_LiteralStr(self);
        (void)_t1415;
        Str *_t1416 = ExprData_get_LiteralStr(other);
        (void)_t1416;
        Bool _t1417; { Bool *_hp = (Bool *)Str_eq(_t1415, _t1416); _t1417 = *_hp; free(_hp); }
        (void)_t1417;
        Str_delete(_t1415, &(Bool){1});
        Str_delete(_t1416, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1417; return _r; }
    }
    ;
    Bool _t1493; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1493 = *_hp; free(_hp); }
    (void)_t1493;
    if (_t1493) {
        Bool _t1419; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t1419 = *_hp; free(_hp); }
        (void)_t1419;
        Bool _t1420 = Bool_not(_t1419);
        (void)_t1420;
        ;
        if (_t1420) {
            Bool _t1418 = 0;
            (void)_t1418;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1418; return _r; }
        }
        ;
        Str *_t1421 = ExprData_get_LiteralNum(self);
        (void)_t1421;
        Str *_t1422 = ExprData_get_LiteralNum(other);
        (void)_t1422;
        Bool _t1423; { Bool *_hp = (Bool *)Str_eq(_t1421, _t1422); _t1423 = *_hp; free(_hp); }
        (void)_t1423;
        Str_delete(_t1421, &(Bool){1});
        Str_delete(_t1422, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1423; return _r; }
    }
    ;
    Bool _t1494; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1494 = *_hp; free(_hp); }
    (void)_t1494;
    if (_t1494) {
        Bool _t1425; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t1425 = *_hp; free(_hp); }
        (void)_t1425;
        Bool _t1426 = Bool_not(_t1425);
        (void)_t1426;
        ;
        if (_t1426) {
            Bool _t1424 = 0;
            (void)_t1424;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1424; return _r; }
        }
        ;
        Str *_t1427 = ExprData_get_LiteralBool(self);
        (void)_t1427;
        Str *_t1428 = ExprData_get_LiteralBool(other);
        (void)_t1428;
        Bool _t1429; { Bool *_hp = (Bool *)Str_eq(_t1427, _t1428); _t1429 = *_hp; free(_hp); }
        (void)_t1429;
        Str_delete(_t1427, &(Bool){1});
        Str_delete(_t1428, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1429; return _r; }
    }
    ;
    Bool _t1495; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1495 = *_hp; free(_hp); }
    (void)_t1495;
    if (_t1495) {
        Bool _t1430; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t1430 = *_hp; free(_hp); }
        (void)_t1430;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1430; return _r; }
    }
    ;
    Bool _t1496; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1496 = *_hp; free(_hp); }
    (void)_t1496;
    if (_t1496) {
        Bool _t1432; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t1432 = *_hp; free(_hp); }
        (void)_t1432;
        Bool _t1433 = Bool_not(_t1432);
        (void)_t1433;
        ;
        if (_t1433) {
            Bool _t1431 = 0;
            (void)_t1431;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1431; return _r; }
        }
        ;
        Str *_t1434 = ExprData_get_Ident(self);
        (void)_t1434;
        Str *_t1435 = ExprData_get_Ident(other);
        (void)_t1435;
        Bool _t1436; { Bool *_hp = (Bool *)Str_eq(_t1434, _t1435); _t1436 = *_hp; free(_hp); }
        (void)_t1436;
        Str_delete(_t1434, &(Bool){1});
        Str_delete(_t1435, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1436; return _r; }
    }
    ;
    Bool _t1497; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1497 = *_hp; free(_hp); }
    (void)_t1497;
    if (_t1497) {
        Bool _t1438; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t1438 = *_hp; free(_hp); }
        (void)_t1438;
        Bool _t1439 = Bool_not(_t1438);
        (void)_t1439;
        ;
        if (_t1439) {
            Bool _t1437 = 0;
            (void)_t1437;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1437; return _r; }
        }
        ;
        Declaration *_t1440 = ExprData_get_Decl(self);
        (void)_t1440;
        Declaration *_t1441 = ExprData_get_Decl(other);
        (void)_t1441;
        Bool _t1442; { Bool *_hp = (Bool *)Declaration_eq(_t1440, _t1441); _t1442 = *_hp; free(_hp); }
        (void)_t1442;
        Declaration_delete(_t1440, &(Bool){1});
        Declaration_delete(_t1441, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1442; return _r; }
    }
    ;
    Bool _t1498; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1498 = *_hp; free(_hp); }
    (void)_t1498;
    if (_t1498) {
        Bool _t1444; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t1444 = *_hp; free(_hp); }
        (void)_t1444;
        Bool _t1445 = Bool_not(_t1444);
        (void)_t1445;
        ;
        if (_t1445) {
            Bool _t1443 = 0;
            (void)_t1443;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1443; return _r; }
        }
        ;
        Str *_t1446 = ExprData_get_Assign(self);
        (void)_t1446;
        Str *_t1447 = ExprData_get_Assign(other);
        (void)_t1447;
        Bool _t1448; { Bool *_hp = (Bool *)Str_eq(_t1446, _t1447); _t1448 = *_hp; free(_hp); }
        (void)_t1448;
        Str_delete(_t1446, &(Bool){1});
        Str_delete(_t1447, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1448; return _r; }
    }
    ;
    Bool _t1499; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1499 = *_hp; free(_hp); }
    (void)_t1499;
    if (_t1499) {
        Bool _t1449; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t1449 = *_hp; free(_hp); }
        (void)_t1449;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1449; return _r; }
    }
    ;
    Bool _t1500; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1500 = *_hp; free(_hp); }
    (void)_t1500;
    if (_t1500) {
        Bool _t1451; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t1451 = *_hp; free(_hp); }
        (void)_t1451;
        Bool _t1452 = Bool_not(_t1451);
        (void)_t1452;
        ;
        if (_t1452) {
            Bool _t1450 = 0;
            (void)_t1450;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1450; return _r; }
        }
        ;
        FunctionDef *_t1453 = ExprData_get_FuncDef(self);
        (void)_t1453;
        FunctionDef *_t1454 = ExprData_get_FuncDef(other);
        (void)_t1454;
        Bool _t1455; { Bool *_hp = (Bool *)FunctionDef_eq(_t1453, _t1454); _t1455 = *_hp; free(_hp); }
        (void)_t1455;
        FunctionDef_delete(_t1453, &(Bool){1});
        FunctionDef_delete(_t1454, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1455; return _r; }
    }
    ;
    Bool _t1501; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1501 = *_hp; free(_hp); }
    (void)_t1501;
    if (_t1501) {
        Bool _t1456; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t1456 = *_hp; free(_hp); }
        (void)_t1456;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1456; return _r; }
    }
    ;
    Bool _t1502; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1502 = *_hp; free(_hp); }
    (void)_t1502;
    if (_t1502) {
        Bool _t1457; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t1457 = *_hp; free(_hp); }
        (void)_t1457;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1457; return _r; }
    }
    ;
    Bool _t1503; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1503 = *_hp; free(_hp); }
    (void)_t1503;
    if (_t1503) {
        Bool _t1459; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t1459 = *_hp; free(_hp); }
        (void)_t1459;
        Bool _t1460 = Bool_not(_t1459);
        (void)_t1460;
        ;
        if (_t1460) {
            Bool _t1458 = 0;
            (void)_t1458;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1458; return _r; }
        }
        ;
        Str *_t1461 = ExprData_get_FieldAccess(self);
        (void)_t1461;
        Str *_t1462 = ExprData_get_FieldAccess(other);
        (void)_t1462;
        Bool _t1463; { Bool *_hp = (Bool *)Str_eq(_t1461, _t1462); _t1463 = *_hp; free(_hp); }
        (void)_t1463;
        Str_delete(_t1461, &(Bool){1});
        Str_delete(_t1462, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1463; return _r; }
    }
    ;
    Bool _t1504; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1504 = *_hp; free(_hp); }
    (void)_t1504;
    if (_t1504) {
        Bool _t1465; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t1465 = *_hp; free(_hp); }
        (void)_t1465;
        Bool _t1466 = Bool_not(_t1465);
        (void)_t1466;
        ;
        if (_t1466) {
            Bool _t1464 = 0;
            (void)_t1464;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1464; return _r; }
        }
        ;
        Str *_t1467 = ExprData_get_FieldAssign(self);
        (void)_t1467;
        Str *_t1468 = ExprData_get_FieldAssign(other);
        (void)_t1468;
        Bool _t1469; { Bool *_hp = (Bool *)Str_eq(_t1467, _t1468); _t1469 = *_hp; free(_hp); }
        (void)_t1469;
        Str_delete(_t1467, &(Bool){1});
        Str_delete(_t1468, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1469; return _r; }
    }
    ;
    Bool _t1505; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1505 = *_hp; free(_hp); }
    (void)_t1505;
    if (_t1505) {
        Bool _t1470; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t1470 = *_hp; free(_hp); }
        (void)_t1470;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1470; return _r; }
    }
    ;
    Bool _t1506; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1506 = *_hp; free(_hp); }
    (void)_t1506;
    if (_t1506) {
        Bool _t1471; { Bool *_hp = (Bool *)ExprData_is_If(other); _t1471 = *_hp; free(_hp); }
        (void)_t1471;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1471; return _r; }
    }
    ;
    Bool _t1507; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1507 = *_hp; free(_hp); }
    (void)_t1507;
    if (_t1507) {
        Bool _t1472; { Bool *_hp = (Bool *)ExprData_is_While(other); _t1472 = *_hp; free(_hp); }
        (void)_t1472;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1472; return _r; }
    }
    ;
    Bool _t1508; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1508 = *_hp; free(_hp); }
    (void)_t1508;
    if (_t1508) {
        Bool _t1474; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t1474 = *_hp; free(_hp); }
        (void)_t1474;
        Bool _t1475 = Bool_not(_t1474);
        (void)_t1475;
        ;
        if (_t1475) {
            Bool _t1473 = 0;
            (void)_t1473;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1473; return _r; }
        }
        ;
        Str *_t1476 = ExprData_get_ForIn(self);
        (void)_t1476;
        Str *_t1477 = ExprData_get_ForIn(other);
        (void)_t1477;
        Bool _t1478; { Bool *_hp = (Bool *)Str_eq(_t1476, _t1477); _t1478 = *_hp; free(_hp); }
        (void)_t1478;
        Str_delete(_t1476, &(Bool){1});
        Str_delete(_t1477, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1478; return _r; }
    }
    ;
    Bool _t1509; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1509 = *_hp; free(_hp); }
    (void)_t1509;
    if (_t1509) {
        Bool _t1480; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t1480 = *_hp; free(_hp); }
        (void)_t1480;
        Bool _t1481 = Bool_not(_t1480);
        (void)_t1481;
        ;
        if (_t1481) {
            Bool _t1479 = 0;
            (void)_t1479;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1479; return _r; }
        }
        ;
        Str *_t1482 = ExprData_get_NamedArg(self);
        (void)_t1482;
        Str *_t1483 = ExprData_get_NamedArg(other);
        (void)_t1483;
        Bool _t1484; { Bool *_hp = (Bool *)Str_eq(_t1482, _t1483); _t1484 = *_hp; free(_hp); }
        (void)_t1484;
        Str_delete(_t1482, &(Bool){1});
        Str_delete(_t1483, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1484; return _r; }
    }
    ;
    Bool _t1510; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1510 = *_hp; free(_hp); }
    (void)_t1510;
    if (_t1510) {
        Bool _t1485; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t1485 = *_hp; free(_hp); }
        (void)_t1485;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1485; return _r; }
    }
    ;
    Bool _t1511; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1511 = *_hp; free(_hp); }
    (void)_t1511;
    if (_t1511) {
        Bool _t1486; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t1486 = *_hp; free(_hp); }
        (void)_t1486;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1486; return _r; }
    }
    ;
    Bool _t1512; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1512 = *_hp; free(_hp); }
    (void)_t1512;
    if (_t1512) {
        Bool _t1487; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t1487 = *_hp; free(_hp); }
        (void)_t1487;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1487; return _r; }
    }
    ;
    Bool _t1513; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1513 = *_hp; free(_hp); }
    (void)_t1513;
    if (_t1513) {
        Bool _t1488; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t1488 = *_hp; free(_hp); }
        (void)_t1488;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1488; return _r; }
    }
    ;
    Bool _t1514; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1514 = *_hp; free(_hp); }
    (void)_t1514;
    if (_t1514) {
        Bool _t1489; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t1489 = *_hp; free(_hp); }
        (void)_t1489;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1489; return _r; }
    }
    ;
    Bool _t1515; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1515 = *_hp; free(_hp); }
    (void)_t1515;
    if (_t1515) {
        Bool _t1490; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t1490 = *_hp; free(_hp); }
        (void)_t1490;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1490; return _r; }
    }
    ;
    Bool _t1516 = 0;
    (void)_t1516;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1516; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t1539; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1539 = *_hp; free(_hp); }
    (void)_t1539;
    if (_t1539) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t1540; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1540 = *_hp; free(_hp); }
    (void)_t1540;
    if (_t1540) {
        Str *_t1517 = ExprData_get_LiteralStr(self);
        (void)_t1517;
        ExprData *_t1518 = ExprData_LiteralStr(_t1517);
        (void)_t1518;
        Str_delete(_t1517, &(Bool){1});
        ;
        return _t1518;
    }
    ;
    Bool _t1541; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1541 = *_hp; free(_hp); }
    (void)_t1541;
    if (_t1541) {
        Str *_t1519 = ExprData_get_LiteralNum(self);
        (void)_t1519;
        ExprData *_t1520 = ExprData_LiteralNum(_t1519);
        (void)_t1520;
        Str_delete(_t1519, &(Bool){1});
        ;
        return _t1520;
    }
    ;
    Bool _t1542; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1542 = *_hp; free(_hp); }
    (void)_t1542;
    if (_t1542) {
        Str *_t1521 = ExprData_get_LiteralBool(self);
        (void)_t1521;
        ExprData *_t1522 = ExprData_LiteralBool(_t1521);
        (void)_t1522;
        Str_delete(_t1521, &(Bool){1});
        ;
        return _t1522;
    }
    ;
    Bool _t1543; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1543 = *_hp; free(_hp); }
    (void)_t1543;
    if (_t1543) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t1544; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1544 = *_hp; free(_hp); }
    (void)_t1544;
    if (_t1544) {
        Str *_t1523 = ExprData_get_Ident(self);
        (void)_t1523;
        ExprData *_t1524 = ExprData_Ident(_t1523);
        (void)_t1524;
        Str_delete(_t1523, &(Bool){1});
        ;
        return _t1524;
    }
    ;
    Bool _t1545; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1545 = *_hp; free(_hp); }
    (void)_t1545;
    if (_t1545) {
        Declaration *_t1525 = ExprData_get_Decl(self);
        (void)_t1525;
        ExprData *_t1526 = ExprData_Decl(_t1525);
        (void)_t1526;
        Declaration_delete(_t1525, &(Bool){1});
        ;
        return _t1526;
    }
    ;
    Bool _t1546; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1546 = *_hp; free(_hp); }
    (void)_t1546;
    if (_t1546) {
        Str *_t1527 = ExprData_get_Assign(self);
        (void)_t1527;
        ExprData *_t1528 = ExprData_Assign(_t1527);
        (void)_t1528;
        Str_delete(_t1527, &(Bool){1});
        ;
        return _t1528;
    }
    ;
    Bool _t1547; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1547 = *_hp; free(_hp); }
    (void)_t1547;
    if (_t1547) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t1548; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1548 = *_hp; free(_hp); }
    (void)_t1548;
    if (_t1548) {
        FunctionDef *_t1529 = ExprData_get_FuncDef(self);
        (void)_t1529;
        ExprData *_t1530 = ExprData_FuncDef(_t1529);
        (void)_t1530;
        FunctionDef_delete(_t1529, &(Bool){1});
        ;
        return _t1530;
    }
    ;
    Bool _t1549; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1549 = *_hp; free(_hp); }
    (void)_t1549;
    if (_t1549) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t1550; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1550 = *_hp; free(_hp); }
    (void)_t1550;
    if (_t1550) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t1551; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1551 = *_hp; free(_hp); }
    (void)_t1551;
    if (_t1551) {
        Str *_t1531 = ExprData_get_FieldAccess(self);
        (void)_t1531;
        ExprData *_t1532 = ExprData_FieldAccess(_t1531);
        (void)_t1532;
        Str_delete(_t1531, &(Bool){1});
        ;
        return _t1532;
    }
    ;
    Bool _t1552; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1552 = *_hp; free(_hp); }
    (void)_t1552;
    if (_t1552) {
        Str *_t1533 = ExprData_get_FieldAssign(self);
        (void)_t1533;
        ExprData *_t1534 = ExprData_FieldAssign(_t1533);
        (void)_t1534;
        Str_delete(_t1533, &(Bool){1});
        ;
        return _t1534;
    }
    ;
    Bool _t1553; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1553 = *_hp; free(_hp); }
    (void)_t1553;
    if (_t1553) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t1554; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1554 = *_hp; free(_hp); }
    (void)_t1554;
    if (_t1554) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t1555; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1555 = *_hp; free(_hp); }
    (void)_t1555;
    if (_t1555) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t1556; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1556 = *_hp; free(_hp); }
    (void)_t1556;
    if (_t1556) {
        Str *_t1535 = ExprData_get_ForIn(self);
        (void)_t1535;
        ExprData *_t1536 = ExprData_ForIn(_t1535);
        (void)_t1536;
        Str_delete(_t1535, &(Bool){1});
        ;
        return _t1536;
    }
    ;
    Bool _t1557; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1557 = *_hp; free(_hp); }
    (void)_t1557;
    if (_t1557) {
        Str *_t1537 = ExprData_get_NamedArg(self);
        (void)_t1537;
        ExprData *_t1538 = ExprData_NamedArg(_t1537);
        (void)_t1538;
        Str_delete(_t1537, &(Bool){1});
        ;
        return _t1538;
    }
    ;
    Bool _t1558; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1558 = *_hp; free(_hp); }
    (void)_t1558;
    if (_t1558) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t1559; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1559 = *_hp; free(_hp); }
    (void)_t1559;
    if (_t1559) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t1560; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1560 = *_hp; free(_hp); }
    (void)_t1560;
    if (_t1560) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t1561; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1561 = *_hp; free(_hp); }
    (void)_t1561;
    if (_t1561) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t1562; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1562 = *_hp; free(_hp); }
    (void)_t1562;
    if (_t1562) {
        ;
        return ExprData_Switch();
    }
    ;
    return ExprData_Case();
}

void ExprData_delete(ExprData * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * ExprData_to_str(ExprData * self) {
    (void)self;
    Bool _t1698; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1698 = *_hp; free(_hp); }
    (void)_t1698;
    if (_t1698) {
        Str *_t1563 = Str_lit("Body", 4ULL);
        (void)_t1563;
        ;
        return _t1563;
    }
    ;
    Bool _t1699; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1699 = *_hp; free(_hp); }
    (void)_t1699;
    if (_t1699) {
        Str *_t1564 = Str_lit("Str", 3ULL);
        (void)_t1564;
        U64 _t1565; { U64 *_hp = (U64 *)Str_size(); _t1565 = *_hp; free(_hp); }
        (void)_t1565;
        U64 _t1566 = 3;
        (void)_t1566;
        Array *_va20 = Array_new(_t1564, &(U64){_t1565}, &(U64){_t1566});
        (void)_va20;
        Str_delete(_t1564, &(Bool){1});
        ;
        ;
        U64 _t1567 = 0;
        (void)_t1567;
        Str *_t1568 = Str_lit("LiteralStr(", 11ULL);
        (void)_t1568;
        Array_set(_va20, &(U64){_t1567}, _t1568);
        ;
        Str *_t1569 = ExprData_get_LiteralStr(self);
        (void)_t1569;
        U64 _t1570 = 1;
        (void)_t1570;
        Str *_t1571 = Str_to_str(_t1569);
        (void)_t1571;
        Str_delete(_t1569, &(Bool){1});
        Array_set(_va20, &(U64){_t1570}, _t1571);
        ;
        U64 _t1572 = 2;
        (void)_t1572;
        Str *_t1573 = Str_lit(")", 1ULL);
        (void)_t1573;
        Array_set(_va20, &(U64){_t1572}, _t1573);
        ;
        Str *_t1574 = format(_va20);
        (void)_t1574;
        ;
        return _t1574;
    }
    ;
    Bool _t1700; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1700 = *_hp; free(_hp); }
    (void)_t1700;
    if (_t1700) {
        Str *_t1575 = Str_lit("Str", 3ULL);
        (void)_t1575;
        U64 _t1576; { U64 *_hp = (U64 *)Str_size(); _t1576 = *_hp; free(_hp); }
        (void)_t1576;
        U64 _t1577 = 3;
        (void)_t1577;
        Array *_va21 = Array_new(_t1575, &(U64){_t1576}, &(U64){_t1577});
        (void)_va21;
        Str_delete(_t1575, &(Bool){1});
        ;
        ;
        U64 _t1578 = 0;
        (void)_t1578;
        Str *_t1579 = Str_lit("LiteralNum(", 11ULL);
        (void)_t1579;
        Array_set(_va21, &(U64){_t1578}, _t1579);
        ;
        Str *_t1580 = ExprData_get_LiteralNum(self);
        (void)_t1580;
        U64 _t1581 = 1;
        (void)_t1581;
        Str *_t1582 = Str_to_str(_t1580);
        (void)_t1582;
        Str_delete(_t1580, &(Bool){1});
        Array_set(_va21, &(U64){_t1581}, _t1582);
        ;
        U64 _t1583 = 2;
        (void)_t1583;
        Str *_t1584 = Str_lit(")", 1ULL);
        (void)_t1584;
        Array_set(_va21, &(U64){_t1583}, _t1584);
        ;
        Str *_t1585 = format(_va21);
        (void)_t1585;
        ;
        return _t1585;
    }
    ;
    Bool _t1701; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1701 = *_hp; free(_hp); }
    (void)_t1701;
    if (_t1701) {
        Str *_t1586 = Str_lit("Str", 3ULL);
        (void)_t1586;
        U64 _t1587; { U64 *_hp = (U64 *)Str_size(); _t1587 = *_hp; free(_hp); }
        (void)_t1587;
        U64 _t1588 = 3;
        (void)_t1588;
        Array *_va22 = Array_new(_t1586, &(U64){_t1587}, &(U64){_t1588});
        (void)_va22;
        Str_delete(_t1586, &(Bool){1});
        ;
        ;
        U64 _t1589 = 0;
        (void)_t1589;
        Str *_t1590 = Str_lit("LiteralBool(", 12ULL);
        (void)_t1590;
        Array_set(_va22, &(U64){_t1589}, _t1590);
        ;
        Str *_t1591 = ExprData_get_LiteralBool(self);
        (void)_t1591;
        U64 _t1592 = 1;
        (void)_t1592;
        Str *_t1593 = Str_to_str(_t1591);
        (void)_t1593;
        Str_delete(_t1591, &(Bool){1});
        Array_set(_va22, &(U64){_t1592}, _t1593);
        ;
        U64 _t1594 = 2;
        (void)_t1594;
        Str *_t1595 = Str_lit(")", 1ULL);
        (void)_t1595;
        Array_set(_va22, &(U64){_t1594}, _t1595);
        ;
        Str *_t1596 = format(_va22);
        (void)_t1596;
        ;
        return _t1596;
    }
    ;
    Bool _t1702; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1702 = *_hp; free(_hp); }
    (void)_t1702;
    if (_t1702) {
        Str *_t1597 = Str_lit("LiteralNull", 11ULL);
        (void)_t1597;
        ;
        return _t1597;
    }
    ;
    Bool _t1703; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1703 = *_hp; free(_hp); }
    (void)_t1703;
    if (_t1703) {
        Str *_t1598 = Str_lit("Str", 3ULL);
        (void)_t1598;
        U64 _t1599; { U64 *_hp = (U64 *)Str_size(); _t1599 = *_hp; free(_hp); }
        (void)_t1599;
        U64 _t1600 = 3;
        (void)_t1600;
        Array *_va23 = Array_new(_t1598, &(U64){_t1599}, &(U64){_t1600});
        (void)_va23;
        Str_delete(_t1598, &(Bool){1});
        ;
        ;
        U64 _t1601 = 0;
        (void)_t1601;
        Str *_t1602 = Str_lit("Ident(", 6ULL);
        (void)_t1602;
        Array_set(_va23, &(U64){_t1601}, _t1602);
        ;
        Str *_t1603 = ExprData_get_Ident(self);
        (void)_t1603;
        U64 _t1604 = 1;
        (void)_t1604;
        Str *_t1605 = Str_to_str(_t1603);
        (void)_t1605;
        Str_delete(_t1603, &(Bool){1});
        Array_set(_va23, &(U64){_t1604}, _t1605);
        ;
        U64 _t1606 = 2;
        (void)_t1606;
        Str *_t1607 = Str_lit(")", 1ULL);
        (void)_t1607;
        Array_set(_va23, &(U64){_t1606}, _t1607);
        ;
        Str *_t1608 = format(_va23);
        (void)_t1608;
        ;
        return _t1608;
    }
    ;
    Bool _t1704; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1704 = *_hp; free(_hp); }
    (void)_t1704;
    if (_t1704) {
        Str *_t1609 = Str_lit("Str", 3ULL);
        (void)_t1609;
        U64 _t1610; { U64 *_hp = (U64 *)Str_size(); _t1610 = *_hp; free(_hp); }
        (void)_t1610;
        U64 _t1611 = 3;
        (void)_t1611;
        Array *_va24 = Array_new(_t1609, &(U64){_t1610}, &(U64){_t1611});
        (void)_va24;
        Str_delete(_t1609, &(Bool){1});
        ;
        ;
        U64 _t1612 = 0;
        (void)_t1612;
        Str *_t1613 = Str_lit("Decl(", 5ULL);
        (void)_t1613;
        Array_set(_va24, &(U64){_t1612}, _t1613);
        ;
        Declaration *_t1614 = ExprData_get_Decl(self);
        (void)_t1614;
        U64 _t1615 = 1;
        (void)_t1615;
        Str *_t1616 = Declaration_to_str(_t1614);
        (void)_t1616;
        Declaration_delete(_t1614, &(Bool){1});
        Array_set(_va24, &(U64){_t1615}, _t1616);
        ;
        U64 _t1617 = 2;
        (void)_t1617;
        Str *_t1618 = Str_lit(")", 1ULL);
        (void)_t1618;
        Array_set(_va24, &(U64){_t1617}, _t1618);
        ;
        Str *_t1619 = format(_va24);
        (void)_t1619;
        ;
        return _t1619;
    }
    ;
    Bool _t1705; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1705 = *_hp; free(_hp); }
    (void)_t1705;
    if (_t1705) {
        Str *_t1620 = Str_lit("Str", 3ULL);
        (void)_t1620;
        U64 _t1621; { U64 *_hp = (U64 *)Str_size(); _t1621 = *_hp; free(_hp); }
        (void)_t1621;
        U64 _t1622 = 3;
        (void)_t1622;
        Array *_va25 = Array_new(_t1620, &(U64){_t1621}, &(U64){_t1622});
        (void)_va25;
        Str_delete(_t1620, &(Bool){1});
        ;
        ;
        U64 _t1623 = 0;
        (void)_t1623;
        Str *_t1624 = Str_lit("Assign(", 7ULL);
        (void)_t1624;
        Array_set(_va25, &(U64){_t1623}, _t1624);
        ;
        Str *_t1625 = ExprData_get_Assign(self);
        (void)_t1625;
        U64 _t1626 = 1;
        (void)_t1626;
        Str *_t1627 = Str_to_str(_t1625);
        (void)_t1627;
        Str_delete(_t1625, &(Bool){1});
        Array_set(_va25, &(U64){_t1626}, _t1627);
        ;
        U64 _t1628 = 2;
        (void)_t1628;
        Str *_t1629 = Str_lit(")", 1ULL);
        (void)_t1629;
        Array_set(_va25, &(U64){_t1628}, _t1629);
        ;
        Str *_t1630 = format(_va25);
        (void)_t1630;
        ;
        return _t1630;
    }
    ;
    Bool _t1706; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1706 = *_hp; free(_hp); }
    (void)_t1706;
    if (_t1706) {
        Str *_t1631 = Str_lit("FCall", 5ULL);
        (void)_t1631;
        ;
        return _t1631;
    }
    ;
    Bool _t1707; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1707 = *_hp; free(_hp); }
    (void)_t1707;
    if (_t1707) {
        Str *_t1632 = Str_lit("Str", 3ULL);
        (void)_t1632;
        U64 _t1633; { U64 *_hp = (U64 *)Str_size(); _t1633 = *_hp; free(_hp); }
        (void)_t1633;
        U64 _t1634 = 3;
        (void)_t1634;
        Array *_va26 = Array_new(_t1632, &(U64){_t1633}, &(U64){_t1634});
        (void)_va26;
        Str_delete(_t1632, &(Bool){1});
        ;
        ;
        U64 _t1635 = 0;
        (void)_t1635;
        Str *_t1636 = Str_lit("FuncDef(", 8ULL);
        (void)_t1636;
        Array_set(_va26, &(U64){_t1635}, _t1636);
        ;
        FunctionDef *_t1637 = ExprData_get_FuncDef(self);
        (void)_t1637;
        U64 _t1638 = 1;
        (void)_t1638;
        Str *_t1639 = FunctionDef_to_str(_t1637);
        (void)_t1639;
        FunctionDef_delete(_t1637, &(Bool){1});
        Array_set(_va26, &(U64){_t1638}, _t1639);
        ;
        U64 _t1640 = 2;
        (void)_t1640;
        Str *_t1641 = Str_lit(")", 1ULL);
        (void)_t1641;
        Array_set(_va26, &(U64){_t1640}, _t1641);
        ;
        Str *_t1642 = format(_va26);
        (void)_t1642;
        ;
        return _t1642;
    }
    ;
    Bool _t1708; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1708 = *_hp; free(_hp); }
    (void)_t1708;
    if (_t1708) {
        Str *_t1643 = Str_lit("StructDef", 9ULL);
        (void)_t1643;
        ;
        return _t1643;
    }
    ;
    Bool _t1709; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1709 = *_hp; free(_hp); }
    (void)_t1709;
    if (_t1709) {
        Str *_t1644 = Str_lit("EnumDef", 7ULL);
        (void)_t1644;
        ;
        return _t1644;
    }
    ;
    Bool _t1710; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1710 = *_hp; free(_hp); }
    (void)_t1710;
    if (_t1710) {
        Str *_t1645 = Str_lit("Str", 3ULL);
        (void)_t1645;
        U64 _t1646; { U64 *_hp = (U64 *)Str_size(); _t1646 = *_hp; free(_hp); }
        (void)_t1646;
        U64 _t1647 = 3;
        (void)_t1647;
        Array *_va27 = Array_new(_t1645, &(U64){_t1646}, &(U64){_t1647});
        (void)_va27;
        Str_delete(_t1645, &(Bool){1});
        ;
        ;
        U64 _t1648 = 0;
        (void)_t1648;
        Str *_t1649 = Str_lit("FieldAccess(", 12ULL);
        (void)_t1649;
        Array_set(_va27, &(U64){_t1648}, _t1649);
        ;
        Str *_t1650 = ExprData_get_FieldAccess(self);
        (void)_t1650;
        U64 _t1651 = 1;
        (void)_t1651;
        Str *_t1652 = Str_to_str(_t1650);
        (void)_t1652;
        Str_delete(_t1650, &(Bool){1});
        Array_set(_va27, &(U64){_t1651}, _t1652);
        ;
        U64 _t1653 = 2;
        (void)_t1653;
        Str *_t1654 = Str_lit(")", 1ULL);
        (void)_t1654;
        Array_set(_va27, &(U64){_t1653}, _t1654);
        ;
        Str *_t1655 = format(_va27);
        (void)_t1655;
        ;
        return _t1655;
    }
    ;
    Bool _t1711; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1711 = *_hp; free(_hp); }
    (void)_t1711;
    if (_t1711) {
        Str *_t1656 = Str_lit("Str", 3ULL);
        (void)_t1656;
        U64 _t1657; { U64 *_hp = (U64 *)Str_size(); _t1657 = *_hp; free(_hp); }
        (void)_t1657;
        U64 _t1658 = 3;
        (void)_t1658;
        Array *_va28 = Array_new(_t1656, &(U64){_t1657}, &(U64){_t1658});
        (void)_va28;
        Str_delete(_t1656, &(Bool){1});
        ;
        ;
        U64 _t1659 = 0;
        (void)_t1659;
        Str *_t1660 = Str_lit("FieldAssign(", 12ULL);
        (void)_t1660;
        Array_set(_va28, &(U64){_t1659}, _t1660);
        ;
        Str *_t1661 = ExprData_get_FieldAssign(self);
        (void)_t1661;
        U64 _t1662 = 1;
        (void)_t1662;
        Str *_t1663 = Str_to_str(_t1661);
        (void)_t1663;
        Str_delete(_t1661, &(Bool){1});
        Array_set(_va28, &(U64){_t1662}, _t1663);
        ;
        U64 _t1664 = 2;
        (void)_t1664;
        Str *_t1665 = Str_lit(")", 1ULL);
        (void)_t1665;
        Array_set(_va28, &(U64){_t1664}, _t1665);
        ;
        Str *_t1666 = format(_va28);
        (void)_t1666;
        ;
        return _t1666;
    }
    ;
    Bool _t1712; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1712 = *_hp; free(_hp); }
    (void)_t1712;
    if (_t1712) {
        Str *_t1667 = Str_lit("Return", 6ULL);
        (void)_t1667;
        ;
        return _t1667;
    }
    ;
    Bool _t1713; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1713 = *_hp; free(_hp); }
    (void)_t1713;
    if (_t1713) {
        Str *_t1668 = Str_lit("If", 2ULL);
        (void)_t1668;
        ;
        return _t1668;
    }
    ;
    Bool _t1714; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1714 = *_hp; free(_hp); }
    (void)_t1714;
    if (_t1714) {
        Str *_t1669 = Str_lit("While", 5ULL);
        (void)_t1669;
        ;
        return _t1669;
    }
    ;
    Bool _t1715; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1715 = *_hp; free(_hp); }
    (void)_t1715;
    if (_t1715) {
        Str *_t1670 = Str_lit("Str", 3ULL);
        (void)_t1670;
        U64 _t1671; { U64 *_hp = (U64 *)Str_size(); _t1671 = *_hp; free(_hp); }
        (void)_t1671;
        U64 _t1672 = 3;
        (void)_t1672;
        Array *_va29 = Array_new(_t1670, &(U64){_t1671}, &(U64){_t1672});
        (void)_va29;
        Str_delete(_t1670, &(Bool){1});
        ;
        ;
        U64 _t1673 = 0;
        (void)_t1673;
        Str *_t1674 = Str_lit("ForIn(", 6ULL);
        (void)_t1674;
        Array_set(_va29, &(U64){_t1673}, _t1674);
        ;
        Str *_t1675 = ExprData_get_ForIn(self);
        (void)_t1675;
        U64 _t1676 = 1;
        (void)_t1676;
        Str *_t1677 = Str_to_str(_t1675);
        (void)_t1677;
        Str_delete(_t1675, &(Bool){1});
        Array_set(_va29, &(U64){_t1676}, _t1677);
        ;
        U64 _t1678 = 2;
        (void)_t1678;
        Str *_t1679 = Str_lit(")", 1ULL);
        (void)_t1679;
        Array_set(_va29, &(U64){_t1678}, _t1679);
        ;
        Str *_t1680 = format(_va29);
        (void)_t1680;
        ;
        return _t1680;
    }
    ;
    Bool _t1716; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1716 = *_hp; free(_hp); }
    (void)_t1716;
    if (_t1716) {
        Str *_t1681 = Str_lit("Str", 3ULL);
        (void)_t1681;
        U64 _t1682; { U64 *_hp = (U64 *)Str_size(); _t1682 = *_hp; free(_hp); }
        (void)_t1682;
        U64 _t1683 = 3;
        (void)_t1683;
        Array *_va30 = Array_new(_t1681, &(U64){_t1682}, &(U64){_t1683});
        (void)_va30;
        Str_delete(_t1681, &(Bool){1});
        ;
        ;
        U64 _t1684 = 0;
        (void)_t1684;
        Str *_t1685 = Str_lit("NamedArg(", 9ULL);
        (void)_t1685;
        Array_set(_va30, &(U64){_t1684}, _t1685);
        ;
        Str *_t1686 = ExprData_get_NamedArg(self);
        (void)_t1686;
        U64 _t1687 = 1;
        (void)_t1687;
        Str *_t1688 = Str_to_str(_t1686);
        (void)_t1688;
        Str_delete(_t1686, &(Bool){1});
        Array_set(_va30, &(U64){_t1687}, _t1688);
        ;
        U64 _t1689 = 2;
        (void)_t1689;
        Str *_t1690 = Str_lit(")", 1ULL);
        (void)_t1690;
        Array_set(_va30, &(U64){_t1689}, _t1690);
        ;
        Str *_t1691 = format(_va30);
        (void)_t1691;
        ;
        return _t1691;
    }
    ;
    Bool _t1717; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1717 = *_hp; free(_hp); }
    (void)_t1717;
    if (_t1717) {
        Str *_t1692 = Str_lit("Break", 5ULL);
        (void)_t1692;
        ;
        return _t1692;
    }
    ;
    Bool _t1718; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1718 = *_hp; free(_hp); }
    (void)_t1718;
    if (_t1718) {
        Str *_t1693 = Str_lit("Continue", 8ULL);
        (void)_t1693;
        ;
        return _t1693;
    }
    ;
    Bool _t1719; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1719 = *_hp; free(_hp); }
    (void)_t1719;
    if (_t1719) {
        Str *_t1694 = Str_lit("MapLit", 6ULL);
        (void)_t1694;
        ;
        return _t1694;
    }
    ;
    Bool _t1720; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1720 = *_hp; free(_hp); }
    (void)_t1720;
    if (_t1720) {
        Str *_t1695 = Str_lit("SetLit", 6ULL);
        (void)_t1695;
        ;
        return _t1695;
    }
    ;
    Bool _t1721; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1721 = *_hp; free(_hp); }
    (void)_t1721;
    if (_t1721) {
        Str *_t1696 = Str_lit("Switch", 6ULL);
        (void)_t1696;
        ;
        return _t1696;
    }
    ;
    Bool _t1722; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1722 = *_hp; free(_hp); }
    (void)_t1722;
    if (_t1722) {
        Str *_t1697 = Str_lit("Case", 4ULL);
        (void)_t1697;
        ;
        return _t1697;
    }
    ;
    Str *_t1723 = Str_lit("unknown", 7ULL);
    (void)_t1723;
    return _t1723;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t1725 = Str_lit("Str", 3ULL);
    (void)_t1725;
    U64 _t1726; { U64 *_hp = (U64 *)Str_size(); _t1726 = *_hp; free(_hp); }
    (void)_t1726;
    U64 _t1727 = 7;
    (void)_t1727;
    Array *_va31 = Array_new(_t1725, &(U64){_t1726}, &(U64){_t1727});
    (void)_va31;
    Str_delete(_t1725, &(Bool){1});
    ;
    ;
    U64 _t1728 = 0;
    (void)_t1728;
    Str *_t1729 = Str_clone(&self->path);
    (void)_t1729;
    Array_set(_va31, &(U64){_t1728}, _t1729);
    ;
    U64 _t1730 = 1;
    (void)_t1730;
    Str *_t1731 = Str_lit(":", 1ULL);
    (void)_t1731;
    Array_set(_va31, &(U64){_t1730}, _t1731);
    ;
    U64 _t1732 = 2;
    (void)_t1732;
    Str *_t1733 = U32_to_str(&self->line);
    (void)_t1733;
    Array_set(_va31, &(U64){_t1732}, _t1733);
    ;
    U64 _t1734 = 3;
    (void)_t1734;
    Str *_t1735 = Str_lit(":", 1ULL);
    (void)_t1735;
    Array_set(_va31, &(U64){_t1734}, _t1735);
    ;
    U64 _t1736 = 4;
    (void)_t1736;
    Str *_t1737 = U32_to_str(&self->col);
    (void)_t1737;
    Array_set(_va31, &(U64){_t1736}, _t1737);
    ;
    U64 _t1738 = 5;
    (void)_t1738;
    Str *_t1739 = Str_lit(": error: ", 9ULL);
    (void)_t1739;
    Array_set(_va31, &(U64){_t1738}, _t1739);
    ;
    U64 _t1740 = 6;
    (void)_t1740;
    Str *_t1741 = Str_clone(msg);
    (void)_t1741;
    Array_set(_va31, &(U64){_t1740}, _t1741);
    ;
    println(_va31);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1742 = Str_lit("Str", 3ULL);
    (void)_t1742;
    U64 _t1743; { U64 *_hp = (U64 *)Str_size(); _t1743 = *_hp; free(_hp); }
    (void)_t1743;
    U64 _t1744 = 1;
    (void)_t1744;
    Array *_va32 = Array_new(_t1742, &(U64){_t1743}, &(U64){_t1744});
    (void)_va32;
    Str_delete(_t1742, &(Bool){1});
    ;
    ;
    U64 _t1745 = 0;
    (void)_t1745;
    Str *_t1746 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t1746;
    Array_set(_va32, &(U64){_t1745}, _t1746);
    ;
    println(_va32);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1747 = Str_lit("Str", 3ULL);
    (void)_t1747;
    U64 _t1748; { U64 *_hp = (U64 *)Str_size(); _t1748 = *_hp; free(_hp); }
    (void)_t1748;
    U64 _t1749 = 1;
    (void)_t1749;
    Array *_va33 = Array_new(_t1747, &(U64){_t1748}, &(U64){_t1749});
    (void)_va33;
    Str_delete(_t1747, &(Bool){1});
    ;
    ;
    U64 _t1750 = 0;
    (void)_t1750;
    Str *_t1751 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t1751;
    Array_set(_va33, &(U64){_t1750}, _t1751);
    ;
    println(_va33);
}

void Expr_add_child(Expr * self, Expr * child) {
    (void)self;
    (void)child;
    Vec_push(&self->children, child);
}

Expr * Expr_child(Expr * parent, I64 * i) {
    (void)parent;
    (void)i;
    U64 *_t1752 = malloc(sizeof(U64)); *_t1752 = I64_to_u64(DEREF(i));
    (void)_t1752;
    Expr *c = Vec_get(&parent->children, _t1752);
    (void)c;
    U64_delete(_t1752, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t1753; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t1753 = *_hp; free(_hp); }
    (void)_t1753;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t1753; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t1754 = 0;
    (void)_t1754;
    I64 _t1755 = 1;
    (void)_t1755;
    I64 _t1756 = I64_sub(_t1754, _t1755);
    (void)_t1756;
    ;
    ;
    I64 _t1757 = 0;
    (void)_t1757;
    I64 _t1758 = 1;
    (void)_t1758;
    I64 _t1759 = I64_sub(_t1757, _t1758);
    (void)_t1759;
    ;
    ;
    Str *_t1760 = Str_lit("", 0ULL);
    (void)_t1760;
    U64 _t1761; { U64 *_hp = (U64 *)Expr_size(); _t1761 = *_hp; free(_hp); }
    (void)_t1761;
    Bool _t1762 = 0;
    (void)_t1762;
    Bool _t1763 = 0;
    (void)_t1763;
    Bool _t1764 = 0;
    (void)_t1764;
    Bool _t1765 = 0;
    (void)_t1765;
    Bool _t1766 = 0;
    (void)_t1766;
    Bool _t1767 = 0;
    (void)_t1767;
    Bool _t1768 = 0;
    (void)_t1768;
    Bool _t1769 = 0;
    (void)_t1769;
    I32 _t1770 = 0;
    (void)_t1770;
    I32 _t1771 = I64_to_i32(_t1756);
    (void)_t1771;
    ;
    U32 _t1772 = 0;
    (void)_t1772;
    I32 _t1773 = I64_to_i32(_t1759);
    (void)_t1773;
    ;
    U32 _t1774 = 0;
    (void)_t1774;
    U32 _t1775 = U32_clone(&(U32){col});
    (void)_t1775;
    Str *_t1776 = Str_clone(path);
    (void)_t1776;
    Expr *_t1777 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t1777->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t1777->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1777->struct_name = *_ca; free(_ca); }
    _t1777->is_own_arg = _t1762;
    _t1777->is_splat = _t1763;
    _t1777->is_own_field = _t1764;
    _t1777->is_ref_field = _t1765;
    _t1777->is_ns_field = _t1766;
    _t1777->is_ext = _t1767;
    _t1777->is_core = _t1768;
    _t1777->save_old_delete = _t1769;
    _t1777->total_struct_size = _t1770;
    _t1777->variadic_index = _t1771;
    _t1777->variadic_count = _t1772;
    _t1777->kwargs_index = _t1773;
    _t1777->kwargs_count = _t1774;
    _t1777->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t1760, &(U64){_t1761}); _t1777->children = *_ca; free(_ca); }
    _t1777->line = U32_clone(&(U32){line});
    _t1777->col = _t1775;
    { Str *_ca = Str_clone(_t1776); _t1777->path = *_ca; free(_ca); }
    (void)_t1777;
    Str_delete(_t1760, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t1776, &(Bool){1});
    return _t1777;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t1789 = Str_lit("", 0ULL);
    (void)_t1789;
    U64 _t1790; { U64 *_hp = (U64 *)Expr_size(); _t1790 = *_hp; free(_hp); }
    (void)_t1790;
    Vec *new_children = Vec_new(_t1789, &(U64){_t1790});
    (void)new_children;
    Str_delete(_t1789, &(Bool){1});
    ;
    {
        U64 _fi1778 = 0;
        (void)_fi1778;
        while (1) {
            U64 _t1780 = 0;
            (void)_t1780;
            U64 _t1781; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1781 = *_hp; free(_hp); }
            (void)_t1781;
            Range *_t1782 = Range_new(_t1780, _t1781);
            (void)_t1782;
            ;
            ;
            U64 _t1783; { U64 *_hp = (U64 *)Range_len(_t1782); _t1783 = *_hp; free(_hp); }
            (void)_t1783;
            Range_delete(_t1782, &(Bool){1});
            Bool _wcond1779; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1778}, &(U64){_t1783}); _wcond1779 = *_hp; free(_hp); }
            (void)_wcond1779;
            ;
            if (_wcond1779) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1784 = 0;
            (void)_t1784;
            U64 _t1785; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1785 = *_hp; free(_hp); }
            (void)_t1785;
            Range *_t1786 = Range_new(_t1784, _t1785);
            (void)_t1786;
            ;
            ;
            U64 *i = Range_get(_t1786, _fi1778);
            (void)i;
            Range_delete(_t1786, &(Bool){1});
            U64 _t1787 = 1;
            (void)_t1787;
            U64 _t1788 = U64_add(_fi1778, _t1787);
            (void)_t1788;
            ;
            _fi1778 = _t1788;
            ;
            Expr *c = Vec_get(&self->children, i);
            (void)c;
            Expr *cloned = Expr_clone(c);
            (void)cloned;
            U64_delete(i, &(Bool){1});
            Vec_push(new_children, cloned);
        }
        ;
    }
    Expr *_t1791 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t1791->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t1791->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t1791->struct_name = *_ca; free(_ca); }
    _t1791->is_own_arg = self->is_own_arg;
    _t1791->is_splat = self->is_splat;
    _t1791->is_own_field = self->is_own_field;
    _t1791->is_ref_field = self->is_ref_field;
    _t1791->is_ns_field = self->is_ns_field;
    _t1791->is_ext = self->is_ext;
    _t1791->is_core = self->is_core;
    _t1791->save_old_delete = self->save_old_delete;
    _t1791->total_struct_size = self->total_struct_size;
    _t1791->variadic_index = self->variadic_index;
    _t1791->variadic_count = self->variadic_count;
    _t1791->kwargs_index = self->kwargs_index;
    _t1791->kwargs_count = self->kwargs_count;
    _t1791->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t1791->children = *_ca; free(_ca); }
    _t1791->line = self->line;
    _t1791->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t1791->path = *_ca; free(_ca); }
    (void)_t1791;
    Vec_delete(new_children, &(Bool){1});
    return _t1791;
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
    Bool _t2181; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t2181 = *_hp; free(_hp); }
    (void)_t2181;
    if (_t2181) {
        Bool _t2115; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t2115 = *_hp; free(_hp); }
        (void)_t2115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2115; return _r; }
    }
    ;
    Bool _t2182; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t2182 = *_hp; free(_hp); }
    (void)_t2182;
    if (_t2182) {
        Bool _t2116; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t2116 = *_hp; free(_hp); }
        (void)_t2116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2116; return _r; }
    }
    ;
    Bool _t2183; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t2183 = *_hp; free(_hp); }
    (void)_t2183;
    if (_t2183) {
        Bool _t2117; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t2117 = *_hp; free(_hp); }
        (void)_t2117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2117; return _r; }
    }
    ;
    Bool _t2184; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t2184 = *_hp; free(_hp); }
    (void)_t2184;
    if (_t2184) {
        Bool _t2118; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t2118 = *_hp; free(_hp); }
        (void)_t2118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2118; return _r; }
    }
    ;
    Bool _t2185; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t2185 = *_hp; free(_hp); }
    (void)_t2185;
    if (_t2185) {
        Bool _t2119; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t2119 = *_hp; free(_hp); }
        (void)_t2119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2119; return _r; }
    }
    ;
    Bool _t2186; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t2186 = *_hp; free(_hp); }
    (void)_t2186;
    if (_t2186) {
        Bool _t2120; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t2120 = *_hp; free(_hp); }
        (void)_t2120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2120; return _r; }
    }
    ;
    Bool _t2187; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t2187 = *_hp; free(_hp); }
    (void)_t2187;
    if (_t2187) {
        Bool _t2121; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t2121 = *_hp; free(_hp); }
        (void)_t2121;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2121; return _r; }
    }
    ;
    Bool _t2188; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t2188 = *_hp; free(_hp); }
    (void)_t2188;
    if (_t2188) {
        Bool _t2122; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t2122 = *_hp; free(_hp); }
        (void)_t2122;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2122; return _r; }
    }
    ;
    Bool _t2189; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t2189 = *_hp; free(_hp); }
    (void)_t2189;
    if (_t2189) {
        Bool _t2123; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t2123 = *_hp; free(_hp); }
        (void)_t2123;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2123; return _r; }
    }
    ;
    Bool _t2190; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t2190 = *_hp; free(_hp); }
    (void)_t2190;
    if (_t2190) {
        Bool _t2124; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t2124 = *_hp; free(_hp); }
        (void)_t2124;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2124; return _r; }
    }
    ;
    Bool _t2191; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t2191 = *_hp; free(_hp); }
    (void)_t2191;
    if (_t2191) {
        Bool _t2125; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t2125 = *_hp; free(_hp); }
        (void)_t2125;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2125; return _r; }
    }
    ;
    Bool _t2192; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t2192 = *_hp; free(_hp); }
    (void)_t2192;
    if (_t2192) {
        Bool _t2126; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t2126 = *_hp; free(_hp); }
        (void)_t2126;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2126; return _r; }
    }
    ;
    Bool _t2193; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t2193 = *_hp; free(_hp); }
    (void)_t2193;
    if (_t2193) {
        Bool _t2127; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t2127 = *_hp; free(_hp); }
        (void)_t2127;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2127; return _r; }
    }
    ;
    Bool _t2194; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t2194 = *_hp; free(_hp); }
    (void)_t2194;
    if (_t2194) {
        Bool _t2128; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t2128 = *_hp; free(_hp); }
        (void)_t2128;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2128; return _r; }
    }
    ;
    Bool _t2195; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t2195 = *_hp; free(_hp); }
    (void)_t2195;
    if (_t2195) {
        Bool _t2129; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t2129 = *_hp; free(_hp); }
        (void)_t2129;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2129; return _r; }
    }
    ;
    Bool _t2196; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t2196 = *_hp; free(_hp); }
    (void)_t2196;
    if (_t2196) {
        Bool _t2130; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t2130 = *_hp; free(_hp); }
        (void)_t2130;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2130; return _r; }
    }
    ;
    Bool _t2197; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t2197 = *_hp; free(_hp); }
    (void)_t2197;
    if (_t2197) {
        Bool _t2131; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t2131 = *_hp; free(_hp); }
        (void)_t2131;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2131; return _r; }
    }
    ;
    Bool _t2198; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t2198 = *_hp; free(_hp); }
    (void)_t2198;
    if (_t2198) {
        Bool _t2132; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t2132 = *_hp; free(_hp); }
        (void)_t2132;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2132; return _r; }
    }
    ;
    Bool _t2199; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t2199 = *_hp; free(_hp); }
    (void)_t2199;
    if (_t2199) {
        Bool _t2133; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t2133 = *_hp; free(_hp); }
        (void)_t2133;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2133; return _r; }
    }
    ;
    Bool _t2200; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t2200 = *_hp; free(_hp); }
    (void)_t2200;
    if (_t2200) {
        Bool _t2134; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t2134 = *_hp; free(_hp); }
        (void)_t2134;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2134; return _r; }
    }
    ;
    Bool _t2201; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t2201 = *_hp; free(_hp); }
    (void)_t2201;
    if (_t2201) {
        Bool _t2135; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t2135 = *_hp; free(_hp); }
        (void)_t2135;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2135; return _r; }
    }
    ;
    Bool _t2202; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t2202 = *_hp; free(_hp); }
    (void)_t2202;
    if (_t2202) {
        Bool _t2136; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t2136 = *_hp; free(_hp); }
        (void)_t2136;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2136; return _r; }
    }
    ;
    Bool _t2203; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t2203 = *_hp; free(_hp); }
    (void)_t2203;
    if (_t2203) {
        Bool _t2137; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t2137 = *_hp; free(_hp); }
        (void)_t2137;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2137; return _r; }
    }
    ;
    Bool _t2204; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t2204 = *_hp; free(_hp); }
    (void)_t2204;
    if (_t2204) {
        Bool _t2138; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t2138 = *_hp; free(_hp); }
        (void)_t2138;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2138; return _r; }
    }
    ;
    Bool _t2205; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t2205 = *_hp; free(_hp); }
    (void)_t2205;
    if (_t2205) {
        Bool _t2139; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t2139 = *_hp; free(_hp); }
        (void)_t2139;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2139; return _r; }
    }
    ;
    Bool _t2206; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        Bool _t2140; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t2140 = *_hp; free(_hp); }
        (void)_t2140;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2140; return _r; }
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        Bool _t2141; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t2141 = *_hp; free(_hp); }
        (void)_t2141;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2141; return _r; }
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        Bool _t2142; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t2142 = *_hp; free(_hp); }
        (void)_t2142;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2142; return _r; }
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        Bool _t2143; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t2143 = *_hp; free(_hp); }
        (void)_t2143;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2143; return _r; }
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        Bool _t2144; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t2144 = *_hp; free(_hp); }
        (void)_t2144;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2144; return _r; }
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        Bool _t2145; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t2145 = *_hp; free(_hp); }
        (void)_t2145;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2145; return _r; }
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        Bool _t2146; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t2146 = *_hp; free(_hp); }
        (void)_t2146;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2146; return _r; }
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        Bool _t2147; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t2147 = *_hp; free(_hp); }
        (void)_t2147;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2147; return _r; }
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        Bool _t2148; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t2148 = *_hp; free(_hp); }
        (void)_t2148;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2148; return _r; }
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        Bool _t2149; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t2149 = *_hp; free(_hp); }
        (void)_t2149;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2149; return _r; }
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        Bool _t2150; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t2150 = *_hp; free(_hp); }
        (void)_t2150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2150; return _r; }
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        Bool _t2151; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t2151 = *_hp; free(_hp); }
        (void)_t2151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2151; return _r; }
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        Bool _t2152; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t2152 = *_hp; free(_hp); }
        (void)_t2152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2152; return _r; }
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        Bool _t2153; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t2153 = *_hp; free(_hp); }
        (void)_t2153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2153; return _r; }
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        Bool _t2154; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t2154 = *_hp; free(_hp); }
        (void)_t2154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2154; return _r; }
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        Bool _t2155; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t2155 = *_hp; free(_hp); }
        (void)_t2155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2155; return _r; }
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        Bool _t2156; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t2156 = *_hp; free(_hp); }
        (void)_t2156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2156; return _r; }
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        Bool _t2157; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t2157 = *_hp; free(_hp); }
        (void)_t2157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2157; return _r; }
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        Bool _t2158; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t2158 = *_hp; free(_hp); }
        (void)_t2158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2158; return _r; }
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        Bool _t2159; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t2159 = *_hp; free(_hp); }
        (void)_t2159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2159; return _r; }
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        Bool _t2160; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2160; return _r; }
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        Bool _t2161; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t2161 = *_hp; free(_hp); }
        (void)_t2161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2161; return _r; }
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        Bool _t2162; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t2162 = *_hp; free(_hp); }
        (void)_t2162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2162; return _r; }
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        Bool _t2163; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t2163 = *_hp; free(_hp); }
        (void)_t2163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2163; return _r; }
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        Bool _t2164; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t2164 = *_hp; free(_hp); }
        (void)_t2164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2164; return _r; }
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        Bool _t2165; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t2165 = *_hp; free(_hp); }
        (void)_t2165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2165; return _r; }
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        Bool _t2166; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t2166 = *_hp; free(_hp); }
        (void)_t2166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2166; return _r; }
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        Bool _t2167; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t2167 = *_hp; free(_hp); }
        (void)_t2167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2167; return _r; }
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        Bool _t2168; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t2168 = *_hp; free(_hp); }
        (void)_t2168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2168; return _r; }
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        Bool _t2169; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t2169 = *_hp; free(_hp); }
        (void)_t2169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2169; return _r; }
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        Bool _t2170; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t2170 = *_hp; free(_hp); }
        (void)_t2170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2170; return _r; }
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        Bool _t2171; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t2171 = *_hp; free(_hp); }
        (void)_t2171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2171; return _r; }
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        Bool _t2172; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t2172 = *_hp; free(_hp); }
        (void)_t2172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2172; return _r; }
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
        Bool _t2173; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t2173 = *_hp; free(_hp); }
        (void)_t2173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2173; return _r; }
    }
    ;
    Bool _t2240; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t2240 = *_hp; free(_hp); }
    (void)_t2240;
    if (_t2240) {
        Bool _t2174; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t2174 = *_hp; free(_hp); }
        (void)_t2174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2174; return _r; }
    }
    ;
    Bool _t2241; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    if (_t2241) {
        Bool _t2175; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t2175 = *_hp; free(_hp); }
        (void)_t2175;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2175; return _r; }
    }
    ;
    Bool _t2242; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    if (_t2242) {
        Bool _t2176; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t2176 = *_hp; free(_hp); }
        (void)_t2176;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2176; return _r; }
    }
    ;
    Bool _t2243; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t2243 = *_hp; free(_hp); }
    (void)_t2243;
    if (_t2243) {
        Bool _t2177; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t2177 = *_hp; free(_hp); }
        (void)_t2177;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2177; return _r; }
    }
    ;
    Bool _t2244; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t2244 = *_hp; free(_hp); }
    (void)_t2244;
    if (_t2244) {
        Bool _t2178; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t2178 = *_hp; free(_hp); }
        (void)_t2178;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2178; return _r; }
    }
    ;
    Bool _t2245; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t2245 = *_hp; free(_hp); }
    (void)_t2245;
    if (_t2245) {
        Bool _t2179; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t2179 = *_hp; free(_hp); }
        (void)_t2179;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2179; return _r; }
    }
    ;
    Bool _t2246; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    if (_t2246) {
        Bool _t2180; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t2180 = *_hp; free(_hp); }
        (void)_t2180;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2180; return _r; }
    }
    ;
    Bool _t2247 = 0;
    (void)_t2247;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2247; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t2248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2248 = *_hp; free(_hp); }
    (void)_t2248;
    if (_t2248) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t2249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2249 = *_hp; free(_hp); }
    (void)_t2249;
    if (_t2249) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t2250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2250 = *_hp; free(_hp); }
    (void)_t2250;
    if (_t2250) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t2251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2251 = *_hp; free(_hp); }
    (void)_t2251;
    if (_t2251) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t2252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2252 = *_hp; free(_hp); }
    (void)_t2252;
    if (_t2252) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t2253; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2253 = *_hp; free(_hp); }
    (void)_t2253;
    if (_t2253) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t2254; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2254 = *_hp; free(_hp); }
    (void)_t2254;
    if (_t2254) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t2255; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2255 = *_hp; free(_hp); }
    (void)_t2255;
    if (_t2255) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t2256; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2256 = *_hp; free(_hp); }
    (void)_t2256;
    if (_t2256) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t2257; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2257 = *_hp; free(_hp); }
    (void)_t2257;
    if (_t2257) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t2258; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2258 = *_hp; free(_hp); }
    (void)_t2258;
    if (_t2258) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t2259; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2259 = *_hp; free(_hp); }
    (void)_t2259;
    if (_t2259) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t2260; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2260 = *_hp; free(_hp); }
    (void)_t2260;
    if (_t2260) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t2261; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2261 = *_hp; free(_hp); }
    (void)_t2261;
    if (_t2261) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t2262; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2262 = *_hp; free(_hp); }
    (void)_t2262;
    if (_t2262) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t2263; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2263 = *_hp; free(_hp); }
    (void)_t2263;
    if (_t2263) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t2264; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2264 = *_hp; free(_hp); }
    (void)_t2264;
    if (_t2264) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t2265; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2265 = *_hp; free(_hp); }
    (void)_t2265;
    if (_t2265) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t2266; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2266 = *_hp; free(_hp); }
    (void)_t2266;
    if (_t2266) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t2267; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2267 = *_hp; free(_hp); }
    (void)_t2267;
    if (_t2267) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t2268; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2268 = *_hp; free(_hp); }
    (void)_t2268;
    if (_t2268) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t2269; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2269 = *_hp; free(_hp); }
    (void)_t2269;
    if (_t2269) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t2270; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2270 = *_hp; free(_hp); }
    (void)_t2270;
    if (_t2270) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t2271; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2271 = *_hp; free(_hp); }
    (void)_t2271;
    if (_t2271) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t2272; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2272 = *_hp; free(_hp); }
    (void)_t2272;
    if (_t2272) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t2273; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2273 = *_hp; free(_hp); }
    (void)_t2273;
    if (_t2273) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t2274; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2274 = *_hp; free(_hp); }
    (void)_t2274;
    if (_t2274) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t2275; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2275 = *_hp; free(_hp); }
    (void)_t2275;
    if (_t2275) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t2276; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2276 = *_hp; free(_hp); }
    (void)_t2276;
    if (_t2276) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t2277; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2277 = *_hp; free(_hp); }
    (void)_t2277;
    if (_t2277) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t2278; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2278 = *_hp; free(_hp); }
    (void)_t2278;
    if (_t2278) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t2279; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2279 = *_hp; free(_hp); }
    (void)_t2279;
    if (_t2279) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t2280; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2280 = *_hp; free(_hp); }
    (void)_t2280;
    if (_t2280) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t2281; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2281 = *_hp; free(_hp); }
    (void)_t2281;
    if (_t2281) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t2282; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2282 = *_hp; free(_hp); }
    (void)_t2282;
    if (_t2282) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t2283; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2283 = *_hp; free(_hp); }
    (void)_t2283;
    if (_t2283) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t2284; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2284 = *_hp; free(_hp); }
    (void)_t2284;
    if (_t2284) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t2285; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2285 = *_hp; free(_hp); }
    (void)_t2285;
    if (_t2285) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t2286; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2286 = *_hp; free(_hp); }
    (void)_t2286;
    if (_t2286) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t2287; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2287 = *_hp; free(_hp); }
    (void)_t2287;
    if (_t2287) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t2288; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2288 = *_hp; free(_hp); }
    (void)_t2288;
    if (_t2288) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t2289; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2289 = *_hp; free(_hp); }
    (void)_t2289;
    if (_t2289) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t2290; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2290 = *_hp; free(_hp); }
    (void)_t2290;
    if (_t2290) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t2291; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2291 = *_hp; free(_hp); }
    (void)_t2291;
    if (_t2291) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t2292; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2292 = *_hp; free(_hp); }
    (void)_t2292;
    if (_t2292) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t2293; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2293 = *_hp; free(_hp); }
    (void)_t2293;
    if (_t2293) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t2294; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2294 = *_hp; free(_hp); }
    (void)_t2294;
    if (_t2294) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t2295; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2295 = *_hp; free(_hp); }
    (void)_t2295;
    if (_t2295) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t2296; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2296 = *_hp; free(_hp); }
    (void)_t2296;
    if (_t2296) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t2297; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2297 = *_hp; free(_hp); }
    (void)_t2297;
    if (_t2297) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t2298; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2298 = *_hp; free(_hp); }
    (void)_t2298;
    if (_t2298) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t2299; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2299 = *_hp; free(_hp); }
    (void)_t2299;
    if (_t2299) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t2300; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2300 = *_hp; free(_hp); }
    (void)_t2300;
    if (_t2300) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t2301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2301 = *_hp; free(_hp); }
    (void)_t2301;
    if (_t2301) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t2302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2302 = *_hp; free(_hp); }
    (void)_t2302;
    if (_t2302) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t2303; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2303 = *_hp; free(_hp); }
    (void)_t2303;
    if (_t2303) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t2304; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2304 = *_hp; free(_hp); }
    (void)_t2304;
    if (_t2304) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t2305; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2305 = *_hp; free(_hp); }
    (void)_t2305;
    if (_t2305) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t2306; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2306 = *_hp; free(_hp); }
    (void)_t2306;
    if (_t2306) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t2307; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2307 = *_hp; free(_hp); }
    (void)_t2307;
    if (_t2307) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t2308; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2308 = *_hp; free(_hp); }
    (void)_t2308;
    if (_t2308) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t2309; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2309 = *_hp; free(_hp); }
    (void)_t2309;
    if (_t2309) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t2310; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2310 = *_hp; free(_hp); }
    (void)_t2310;
    if (_t2310) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t2311; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2311 = *_hp; free(_hp); }
    (void)_t2311;
    if (_t2311) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t2312; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2312 = *_hp; free(_hp); }
    (void)_t2312;
    if (_t2312) {
        ;
        return TokenType_KwNull();
    }
    ;
    return TokenType_Error();
}

void TokenType_delete(TokenType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TokenType_to_str(TokenType * self) {
    (void)self;
    Bool _t2379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2379 = *_hp; free(_hp); }
    (void)_t2379;
    if (_t2379) {
        Str *_t2313 = Str_lit("Eof", 3ULL);
        (void)_t2313;
        ;
        return _t2313;
    }
    ;
    Bool _t2380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2380 = *_hp; free(_hp); }
    (void)_t2380;
    if (_t2380) {
        Str *_t2314 = Str_lit("LParen", 6ULL);
        (void)_t2314;
        ;
        return _t2314;
    }
    ;
    Bool _t2381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2381 = *_hp; free(_hp); }
    (void)_t2381;
    if (_t2381) {
        Str *_t2315 = Str_lit("RParen", 6ULL);
        (void)_t2315;
        ;
        return _t2315;
    }
    ;
    Bool _t2382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2382 = *_hp; free(_hp); }
    (void)_t2382;
    if (_t2382) {
        Str *_t2316 = Str_lit("LBrace", 6ULL);
        (void)_t2316;
        ;
        return _t2316;
    }
    ;
    Bool _t2383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2383 = *_hp; free(_hp); }
    (void)_t2383;
    if (_t2383) {
        Str *_t2317 = Str_lit("RBrace", 6ULL);
        (void)_t2317;
        ;
        return _t2317;
    }
    ;
    Bool _t2384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2384 = *_hp; free(_hp); }
    (void)_t2384;
    if (_t2384) {
        Str *_t2318 = Str_lit("LBracket", 8ULL);
        (void)_t2318;
        ;
        return _t2318;
    }
    ;
    Bool _t2385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2385 = *_hp; free(_hp); }
    (void)_t2385;
    if (_t2385) {
        Str *_t2319 = Str_lit("RBracket", 8ULL);
        (void)_t2319;
        ;
        return _t2319;
    }
    ;
    Bool _t2386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2386 = *_hp; free(_hp); }
    (void)_t2386;
    if (_t2386) {
        Str *_t2320 = Str_lit("Comma", 5ULL);
        (void)_t2320;
        ;
        return _t2320;
    }
    ;
    Bool _t2387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2387 = *_hp; free(_hp); }
    (void)_t2387;
    if (_t2387) {
        Str *_t2321 = Str_lit("Colon", 5ULL);
        (void)_t2321;
        ;
        return _t2321;
    }
    ;
    Bool _t2388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2388 = *_hp; free(_hp); }
    (void)_t2388;
    if (_t2388) {
        Str *_t2322 = Str_lit("Question", 8ULL);
        (void)_t2322;
        ;
        return _t2322;
    }
    ;
    Bool _t2389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2389 = *_hp; free(_hp); }
    (void)_t2389;
    if (_t2389) {
        Str *_t2323 = Str_lit("Bang", 4ULL);
        (void)_t2323;
        ;
        return _t2323;
    }
    ;
    Bool _t2390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2390 = *_hp; free(_hp); }
    (void)_t2390;
    if (_t2390) {
        Str *_t2324 = Str_lit("Minus", 5ULL);
        (void)_t2324;
        ;
        return _t2324;
    }
    ;
    Bool _t2391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2391 = *_hp; free(_hp); }
    (void)_t2391;
    if (_t2391) {
        Str *_t2325 = Str_lit("Plus", 4ULL);
        (void)_t2325;
        ;
        return _t2325;
    }
    ;
    Bool _t2392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2392 = *_hp; free(_hp); }
    (void)_t2392;
    if (_t2392) {
        Str *_t2326 = Str_lit("Star", 4ULL);
        (void)_t2326;
        ;
        return _t2326;
    }
    ;
    Bool _t2393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2393 = *_hp; free(_hp); }
    (void)_t2393;
    if (_t2393) {
        Str *_t2327 = Str_lit("Slash", 5ULL);
        (void)_t2327;
        ;
        return _t2327;
    }
    ;
    Bool _t2394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2394 = *_hp; free(_hp); }
    (void)_t2394;
    if (_t2394) {
        Str *_t2328 = Str_lit("Dot", 3ULL);
        (void)_t2328;
        ;
        return _t2328;
    }
    ;
    Bool _t2395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2395 = *_hp; free(_hp); }
    (void)_t2395;
    if (_t2395) {
        Str *_t2329 = Str_lit("DotDot", 6ULL);
        (void)_t2329;
        ;
        return _t2329;
    }
    ;
    Bool _t2396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2396 = *_hp; free(_hp); }
    (void)_t2396;
    if (_t2396) {
        Str *_t2330 = Str_lit("DotDotDot", 9ULL);
        (void)_t2330;
        ;
        return _t2330;
    }
    ;
    Bool _t2397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2397 = *_hp; free(_hp); }
    (void)_t2397;
    if (_t2397) {
        Str *_t2331 = Str_lit("Eq", 2ULL);
        (void)_t2331;
        ;
        return _t2331;
    }
    ;
    Bool _t2398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2398 = *_hp; free(_hp); }
    (void)_t2398;
    if (_t2398) {
        Str *_t2332 = Str_lit("EqEq", 4ULL);
        (void)_t2332;
        ;
        return _t2332;
    }
    ;
    Bool _t2399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2399 = *_hp; free(_hp); }
    (void)_t2399;
    if (_t2399) {
        Str *_t2333 = Str_lit("Neq", 3ULL);
        (void)_t2333;
        ;
        return _t2333;
    }
    ;
    Bool _t2400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2400 = *_hp; free(_hp); }
    (void)_t2400;
    if (_t2400) {
        Str *_t2334 = Str_lit("Lt", 2ULL);
        (void)_t2334;
        ;
        return _t2334;
    }
    ;
    Bool _t2401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2401 = *_hp; free(_hp); }
    (void)_t2401;
    if (_t2401) {
        Str *_t2335 = Str_lit("LtEq", 4ULL);
        (void)_t2335;
        ;
        return _t2335;
    }
    ;
    Bool _t2402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2402 = *_hp; free(_hp); }
    (void)_t2402;
    if (_t2402) {
        Str *_t2336 = Str_lit("Gt", 2ULL);
        (void)_t2336;
        ;
        return _t2336;
    }
    ;
    Bool _t2403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2403 = *_hp; free(_hp); }
    (void)_t2403;
    if (_t2403) {
        Str *_t2337 = Str_lit("GtEq", 4ULL);
        (void)_t2337;
        ;
        return _t2337;
    }
    ;
    Bool _t2404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2404 = *_hp; free(_hp); }
    (void)_t2404;
    if (_t2404) {
        Str *_t2338 = Str_lit("ColonEq", 7ULL);
        (void)_t2338;
        ;
        return _t2338;
    }
    ;
    Bool _t2405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2405 = *_hp; free(_hp); }
    (void)_t2405;
    if (_t2405) {
        Str *_t2339 = Str_lit("Ident", 5ULL);
        (void)_t2339;
        ;
        return _t2339;
    }
    ;
    Bool _t2406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2406 = *_hp; free(_hp); }
    (void)_t2406;
    if (_t2406) {
        Str *_t2340 = Str_lit("StringTok", 9ULL);
        (void)_t2340;
        ;
        return _t2340;
    }
    ;
    Bool _t2407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2407 = *_hp; free(_hp); }
    (void)_t2407;
    if (_t2407) {
        Str *_t2341 = Str_lit("Number", 6ULL);
        (void)_t2341;
        ;
        return _t2341;
    }
    ;
    Bool _t2408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2408 = *_hp; free(_hp); }
    (void)_t2408;
    if (_t2408) {
        Str *_t2342 = Str_lit("Char", 4ULL);
        (void)_t2342;
        ;
        return _t2342;
    }
    ;
    Bool _t2409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2409 = *_hp; free(_hp); }
    (void)_t2409;
    if (_t2409) {
        Str *_t2343 = Str_lit("KwMode", 6ULL);
        (void)_t2343;
        ;
        return _t2343;
    }
    ;
    Bool _t2410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2410 = *_hp; free(_hp); }
    (void)_t2410;
    if (_t2410) {
        Str *_t2344 = Str_lit("KwMut", 5ULL);
        (void)_t2344;
        ;
        return _t2344;
    }
    ;
    Bool _t2411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2411 = *_hp; free(_hp); }
    (void)_t2411;
    if (_t2411) {
        Str *_t2345 = Str_lit("KwOwn", 5ULL);
        (void)_t2345;
        ;
        return _t2345;
    }
    ;
    Bool _t2412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2412 = *_hp; free(_hp); }
    (void)_t2412;
    if (_t2412) {
        Str *_t2346 = Str_lit("KwRef", 5ULL);
        (void)_t2346;
        ;
        return _t2346;
    }
    ;
    Bool _t2413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2413 = *_hp; free(_hp); }
    (void)_t2413;
    if (_t2413) {
        Str *_t2347 = Str_lit("KwShallow", 9ULL);
        (void)_t2347;
        ;
        return _t2347;
    }
    ;
    Bool _t2414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2414 = *_hp; free(_hp); }
    (void)_t2414;
    if (_t2414) {
        Str *_t2348 = Str_lit("KwStruct", 8ULL);
        (void)_t2348;
        ;
        return _t2348;
    }
    ;
    Bool _t2415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2415 = *_hp; free(_hp); }
    (void)_t2415;
    if (_t2415) {
        Str *_t2349 = Str_lit("KwExtStruct", 11ULL);
        (void)_t2349;
        ;
        return _t2349;
    }
    ;
    Bool _t2416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2416 = *_hp; free(_hp); }
    (void)_t2416;
    if (_t2416) {
        Str *_t2350 = Str_lit("KwEnum", 6ULL);
        (void)_t2350;
        ;
        return _t2350;
    }
    ;
    Bool _t2417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2417 = *_hp; free(_hp); }
    (void)_t2417;
    if (_t2417) {
        Str *_t2351 = Str_lit("KwNamespace", 11ULL);
        (void)_t2351;
        ;
        return _t2351;
    }
    ;
    Bool _t2418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2418 = *_hp; free(_hp); }
    (void)_t2418;
    if (_t2418) {
        Str *_t2352 = Str_lit("KwFunc", 6ULL);
        (void)_t2352;
        ;
        return _t2352;
    }
    ;
    Bool _t2419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2419 = *_hp; free(_hp); }
    (void)_t2419;
    if (_t2419) {
        Str *_t2353 = Str_lit("KwProc", 6ULL);
        (void)_t2353;
        ;
        return _t2353;
    }
    ;
    Bool _t2420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2420 = *_hp; free(_hp); }
    (void)_t2420;
    if (_t2420) {
        Str *_t2354 = Str_lit("KwTest", 6ULL);
        (void)_t2354;
        ;
        return _t2354;
    }
    ;
    Bool _t2421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2421 = *_hp; free(_hp); }
    (void)_t2421;
    if (_t2421) {
        Str *_t2355 = Str_lit("KwMacro", 7ULL);
        (void)_t2355;
        ;
        return _t2355;
    }
    ;
    Bool _t2422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2422 = *_hp; free(_hp); }
    (void)_t2422;
    if (_t2422) {
        Str *_t2356 = Str_lit("KwExtFunc", 9ULL);
        (void)_t2356;
        ;
        return _t2356;
    }
    ;
    Bool _t2423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2423 = *_hp; free(_hp); }
    (void)_t2423;
    if (_t2423) {
        Str *_t2357 = Str_lit("KwExtProc", 9ULL);
        (void)_t2357;
        ;
        return _t2357;
    }
    ;
    Bool _t2424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2424 = *_hp; free(_hp); }
    (void)_t2424;
    if (_t2424) {
        Str *_t2358 = Str_lit("KwReturns", 9ULL);
        (void)_t2358;
        ;
        return _t2358;
    }
    ;
    Bool _t2425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2425 = *_hp; free(_hp); }
    (void)_t2425;
    if (_t2425) {
        Str *_t2359 = Str_lit("KwThrows", 8ULL);
        (void)_t2359;
        ;
        return _t2359;
    }
    ;
    Bool _t2426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2426 = *_hp; free(_hp); }
    (void)_t2426;
    if (_t2426) {
        Str *_t2360 = Str_lit("KwIf", 4ULL);
        (void)_t2360;
        ;
        return _t2360;
    }
    ;
    Bool _t2427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2427 = *_hp; free(_hp); }
    (void)_t2427;
    if (_t2427) {
        Str *_t2361 = Str_lit("KwElse", 6ULL);
        (void)_t2361;
        ;
        return _t2361;
    }
    ;
    Bool _t2428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2428 = *_hp; free(_hp); }
    (void)_t2428;
    if (_t2428) {
        Str *_t2362 = Str_lit("KwWhile", 7ULL);
        (void)_t2362;
        ;
        return _t2362;
    }
    ;
    Bool _t2429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2429 = *_hp; free(_hp); }
    (void)_t2429;
    if (_t2429) {
        Str *_t2363 = Str_lit("KwFor", 5ULL);
        (void)_t2363;
        ;
        return _t2363;
    }
    ;
    Bool _t2430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2430 = *_hp; free(_hp); }
    (void)_t2430;
    if (_t2430) {
        Str *_t2364 = Str_lit("KwIn", 4ULL);
        (void)_t2364;
        ;
        return _t2364;
    }
    ;
    Bool _t2431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2431 = *_hp; free(_hp); }
    (void)_t2431;
    if (_t2431) {
        Str *_t2365 = Str_lit("KwSwitch", 8ULL);
        (void)_t2365;
        ;
        return _t2365;
    }
    ;
    Bool _t2432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2432 = *_hp; free(_hp); }
    (void)_t2432;
    if (_t2432) {
        Str *_t2366 = Str_lit("KwMatch", 7ULL);
        (void)_t2366;
        ;
        return _t2366;
    }
    ;
    Bool _t2433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2433 = *_hp; free(_hp); }
    (void)_t2433;
    if (_t2433) {
        Str *_t2367 = Str_lit("KwCase", 6ULL);
        (void)_t2367;
        ;
        return _t2367;
    }
    ;
    Bool _t2434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2434 = *_hp; free(_hp); }
    (void)_t2434;
    if (_t2434) {
        Str *_t2368 = Str_lit("KwDefault", 9ULL);
        (void)_t2368;
        ;
        return _t2368;
    }
    ;
    Bool _t2435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2435 = *_hp; free(_hp); }
    (void)_t2435;
    if (_t2435) {
        Str *_t2369 = Str_lit("KwReturn", 8ULL);
        (void)_t2369;
        ;
        return _t2369;
    }
    ;
    Bool _t2436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2436 = *_hp; free(_hp); }
    (void)_t2436;
    if (_t2436) {
        Str *_t2370 = Str_lit("KwThrow", 7ULL);
        (void)_t2370;
        ;
        return _t2370;
    }
    ;
    Bool _t2437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2437 = *_hp; free(_hp); }
    (void)_t2437;
    if (_t2437) {
        Str *_t2371 = Str_lit("KwCatch", 7ULL);
        (void)_t2371;
        ;
        return _t2371;
    }
    ;
    Bool _t2438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2438 = *_hp; free(_hp); }
    (void)_t2438;
    if (_t2438) {
        Str *_t2372 = Str_lit("KwBreak", 7ULL);
        (void)_t2372;
        ;
        return _t2372;
    }
    ;
    Bool _t2439; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2439 = *_hp; free(_hp); }
    (void)_t2439;
    if (_t2439) {
        Str *_t2373 = Str_lit("KwContinue", 10ULL);
        (void)_t2373;
        ;
        return _t2373;
    }
    ;
    Bool _t2440; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2440 = *_hp; free(_hp); }
    (void)_t2440;
    if (_t2440) {
        Str *_t2374 = Str_lit("KwDefer", 7ULL);
        (void)_t2374;
        ;
        return _t2374;
    }
    ;
    Bool _t2441; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2441 = *_hp; free(_hp); }
    (void)_t2441;
    if (_t2441) {
        Str *_t2375 = Str_lit("KwTrue", 6ULL);
        (void)_t2375;
        ;
        return _t2375;
    }
    ;
    Bool _t2442; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2442 = *_hp; free(_hp); }
    (void)_t2442;
    if (_t2442) {
        Str *_t2376 = Str_lit("KwFalse", 7ULL);
        (void)_t2376;
        ;
        return _t2376;
    }
    ;
    Bool _t2443; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2443 = *_hp; free(_hp); }
    (void)_t2443;
    if (_t2443) {
        Str *_t2377 = Str_lit("KwNull", 6ULL);
        (void)_t2377;
        ;
        return _t2377;
    }
    ;
    Bool _t2444; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t2444 = *_hp; free(_hp); }
    (void)_t2444;
    if (_t2444) {
        Str *_t2378 = Str_lit("Error", 5ULL);
        (void)_t2378;
        ;
        return _t2378;
    }
    ;
    Str *_t2445 = Str_lit("unknown", 7ULL);
    (void)_t2445;
    return _t2445;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


#include "modes_core.c"
#include "modes_array.c"
#include "modes_map.c"
#include "modes_set.c"
#include "modes_str.c"
#include "modes_vec.c"
#include "modes_tuple.c"
#include "modes_ast.c"
#include "modes_lexer.c"
#include "modes_parser.c"
#include "modes_initer.c"
#include "modes_modes.c"

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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) { TilType_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) { Declaration_delete(val, arg2); return; }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) { FuncType_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0) { Param_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) { FunctionDef_delete(val, arg2); return; }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) { ExprData_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) { Expr_delete(val, arg2); return; }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) { TokenType_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) { Token_delete(val, arg2); return; }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0) { Parser_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0) { TypeBinding_delete(val, arg2); return; }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) { TypeScope_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) { Mode_delete(val, arg2); return; }
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) return (void *)TilType_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) return (void *)Declaration_clone(val);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return (void *)FuncType_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0) return (void *)Param_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return (void *)FunctionDef_clone(val);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) return (void *)ExprData_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return (void *)Expr_clone(val);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) return (void *)TokenType_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return (void *)Token_clone(val);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0) return (void *)Parser_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0) return (void *)TypeBinding_clone(val);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) return (void *)TypeScope_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) return (void *)Mode_clone(val);
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
    _t4251 = malloc(sizeof(I64));
    *_t4251 = 0;
    (void)_t4251;
    _t4252 = malloc(sizeof(I64));
    *_t4252 = 1;
    (void)_t4252;
    _t4253 = malloc(sizeof(I64)); *_t4253 = I64_sub(DEREF(_t4251), DEREF(_t4252));
    (void)_t4253;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4253));
    (void)CAP_LIT;
    _t4254 = malloc(sizeof(I64));
    *_t4254 = 0;
    (void)_t4254;
    _t4255 = malloc(sizeof(I64));
    *_t4255 = 2;
    (void)_t4255;
    _t4256 = malloc(sizeof(I64)); *_t4256 = I64_sub(DEREF(_t4254), DEREF(_t4255));
    (void)_t4256;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4256));
    (void)CAP_VIEW;
    _t4257 = Str_lit("Str", 3ULL);
    (void)_t4257;
    _t4258 = Str_size();
    (void)_t4258;
    _t4259 = Str_lit("Mode", 4ULL);
    (void)_t4259;
    _t4260 = Mode_size();
    (void)_t4260;
    core_modes = Map_new(_t4257, _t4258, _t4259, _t4260);
    (void)core_modes;
    _t4261 = malloc(sizeof(Bool));
    *_t4261 = 0;
    (void)_t4261;
    _t4262 = malloc(sizeof(Bool));
    *_t4262 = 0;
    (void)_t4262;
    _t4263 = malloc(sizeof(Bool));
    *_t4263 = 0;
    (void)_t4263;
    _t4264 = malloc(sizeof(Bool));
    *_t4264 = 0;
    (void)_t4264;
    _t4265 = Str_lit("script", 6ULL);
    (void)_t4265;
    _t4266 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4266->name = *_ca; free(_ca); }
    _t4266->needs_main = DEREF(_t4261);
    _t4266->decls_only = DEREF(_t4262);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4266->auto_import = *_ca; free(_ca); }
    _t4266->is_pure = DEREF(_t4263);
    _t4266->debug_prints = DEREF(_t4264);
    (void)_t4266;
    Map_set(core_modes, _t4265, _t4266);
    _t4267 = malloc(sizeof(Bool));
    *_t4267 = 1;
    (void)_t4267;
    _t4268 = malloc(sizeof(Bool));
    *_t4268 = 1;
    (void)_t4268;
    _t4269 = malloc(sizeof(Bool));
    *_t4269 = 0;
    (void)_t4269;
    _t4270 = malloc(sizeof(Bool));
    *_t4270 = 0;
    (void)_t4270;
    _t4271 = Str_lit("cli", 3ULL);
    (void)_t4271;
    _t4272 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4272->name = *_ca; free(_ca); }
    _t4272->needs_main = DEREF(_t4267);
    _t4272->decls_only = DEREF(_t4268);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4272->auto_import = *_ca; free(_ca); }
    _t4272->is_pure = DEREF(_t4269);
    _t4272->debug_prints = DEREF(_t4270);
    (void)_t4272;
    Map_set(core_modes, _t4271, _t4272);
    _t4273 = malloc(sizeof(Bool));
    *_t4273 = 1;
    (void)_t4273;
    _t4274 = malloc(sizeof(Bool));
    *_t4274 = 1;
    (void)_t4274;
    _t4275 = malloc(sizeof(Bool));
    *_t4275 = 0;
    (void)_t4275;
    _t4276 = malloc(sizeof(Bool));
    *_t4276 = 0;
    (void)_t4276;
    _t4277 = Str_lit("gui", 3ULL);
    (void)_t4277;
    _t4278 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4278->name = *_ca; free(_ca); }
    _t4278->needs_main = DEREF(_t4273);
    _t4278->decls_only = DEREF(_t4274);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4278->auto_import = *_ca; free(_ca); }
    _t4278->is_pure = DEREF(_t4275);
    _t4278->debug_prints = DEREF(_t4276);
    (void)_t4278;
    Map_set(core_modes, _t4277, _t4278);
    _t4279 = malloc(sizeof(Bool));
    *_t4279 = 0;
    (void)_t4279;
    _t4280 = malloc(sizeof(Bool));
    *_t4280 = 1;
    (void)_t4280;
    _t4281 = malloc(sizeof(Bool));
    *_t4281 = 0;
    (void)_t4281;
    _t4282 = malloc(sizeof(Bool));
    *_t4282 = 0;
    (void)_t4282;
    _t4283 = Str_lit("test", 4ULL);
    (void)_t4283;
    _t4284 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4284->name = *_ca; free(_ca); }
    _t4284->needs_main = DEREF(_t4279);
    _t4284->decls_only = DEREF(_t4280);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4284->auto_import = *_ca; free(_ca); }
    _t4284->is_pure = DEREF(_t4281);
    _t4284->debug_prints = DEREF(_t4282);
    (void)_t4284;
    Map_set(core_modes, _t4283, _t4284);
    _t4285 = malloc(sizeof(Bool));
    *_t4285 = 0;
    (void)_t4285;
    _t4286 = malloc(sizeof(Bool));
    *_t4286 = 1;
    (void)_t4286;
    _t4287 = malloc(sizeof(Bool));
    *_t4287 = 1;
    (void)_t4287;
    _t4288 = malloc(sizeof(Bool));
    *_t4288 = 0;
    (void)_t4288;
    _t4289 = Str_lit("pure", 4ULL);
    (void)_t4289;
    _t4290 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4290->name = *_ca; free(_ca); }
    _t4290->needs_main = DEREF(_t4285);
    _t4290->decls_only = DEREF(_t4286);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4290->auto_import = *_ca; free(_ca); }
    _t4290->is_pure = DEREF(_t4287);
    _t4290->debug_prints = DEREF(_t4288);
    (void)_t4290;
    Map_set(core_modes, _t4289, _t4290);
    _t4291 = malloc(sizeof(Bool));
    *_t4291 = 0;
    (void)_t4291;
    _t4292 = malloc(sizeof(Bool));
    *_t4292 = 1;
    (void)_t4292;
    _t4293 = malloc(sizeof(Bool));
    *_t4293 = 1;
    (void)_t4293;
    _t4294 = malloc(sizeof(Bool));
    *_t4294 = 1;
    (void)_t4294;
    _t4295 = Str_lit("pura", 4ULL);
    (void)_t4295;
    _t4296 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4296->name = *_ca; free(_ca); }
    _t4296->needs_main = DEREF(_t4291);
    _t4296->decls_only = DEREF(_t4292);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4296->auto_import = *_ca; free(_ca); }
    _t4296->is_pure = DEREF(_t4293);
    _t4296->debug_prints = DEREF(_t4294);
    (void)_t4296;
    Map_set(core_modes, _t4295, _t4296);
    _t4297 = malloc(sizeof(Bool));
    *_t4297 = 0;
    (void)_t4297;
    _t4298 = malloc(sizeof(Bool));
    *_t4298 = 1;
    (void)_t4298;
    _t4299 = malloc(sizeof(Bool));
    *_t4299 = 0;
    (void)_t4299;
    _t4300 = malloc(sizeof(Bool));
    *_t4300 = 0;
    (void)_t4300;
    _t4301 = Str_lit("lib", 3ULL);
    (void)_t4301;
    _t4302 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4302->name = *_ca; free(_ca); }
    _t4302->needs_main = DEREF(_t4297);
    _t4302->decls_only = DEREF(_t4298);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4302->auto_import = *_ca; free(_ca); }
    _t4302->is_pure = DEREF(_t4299);
    _t4302->debug_prints = DEREF(_t4300);
    (void)_t4302;
    Map_set(core_modes, _t4301, _t4302);
    _t4303 = malloc(sizeof(Bool));
    *_t4303 = 0;
    (void)_t4303;
    _t4304 = malloc(sizeof(Bool));
    *_t4304 = 1;
    (void)_t4304;
    _t4305 = malloc(sizeof(Bool));
    *_t4305 = 0;
    (void)_t4305;
    _t4306 = malloc(sizeof(Bool));
    *_t4306 = 1;
    (void)_t4306;
    _t4307 = Str_lit("liba", 4ULL);
    (void)_t4307;
    _t4308 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4308->name = *_ca; free(_ca); }
    _t4308->needs_main = DEREF(_t4303);
    _t4308->decls_only = DEREF(_t4304);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4308->auto_import = *_ca; free(_ca); }
    _t4308->is_pure = DEREF(_t4305);
    _t4308->debug_prints = DEREF(_t4306);
    (void)_t4308;
    Map_set(core_modes, _t4307, _t4308);
}

