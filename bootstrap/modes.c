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
void U8_inc(U8 * self);
void U8_dec(U8 * self);
U8 * U8_unity(U8 * self);
U64 * U8_size(void);
Bool * U8_lt(U8 * a, U8 * b);
Bool * U8_gt(U8 * a, U8 * b);
Bool * U8_neq(U8 * a, U8 * b);
Bool * U8_lte(U8 * a, U8 * b);
Bool * U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
void I16_inc(I16 * self);
void I16_dec(I16 * self);
I16 * I16_unity(I16 * self);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
U64 * I16_size(void);
Bool * I16_lt(I16 * a, I16 * b);
Bool * I16_gt(I16 * a, I16 * b);
Bool * I16_neq(I16 * a, I16 * b);
Bool * I16_lte(I16 * a, I16 * b);
Bool * I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
I32 * I32_unity(I32 * self);
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
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U32 * U32_unity(U32 * self);
U64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Bool * U32_gt(U32 * a, U32 * b);
Bool * U32_neq(U32 * a, U32 * b);
Bool * U32_lte(U32 * a, U32 * b);
Bool * U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
U64 * U64_unity(U64 * self);
U64 * U64_size(void);
Bool * U64_lt(U64 * a, U64 * b);
Bool * U64_gt(U64 * a, U64 * b);
Bool * U64_neq(U64 * a, U64 * b);
Bool * U64_lte(U64 * a, U64 * b);
Bool * U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
I64 * I64_unity(I64 * self);
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
void *dyn_fn(Str *type_name, Str *method);

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

static I64 *_t4152;
static I64 *_t4153;
static I64 *_t4154;
static U64 *CAP_LIT;
static I64 *_t4155;
static I64 *_t4156;
static I64 *_t4157;
static U64 *CAP_VIEW;
static Str *_t4158;
static U64 *_t4159;
static Str *_t4160;
static U64 *_t4161;
static Map *core_modes;
static Bool *_t4162;
static Bool *_t4163;
static Bool *_t4164;
static Bool *_t4165;
static Str *_t4166;
static Mode *_t4167;
static Bool *_t4168;
static Bool *_t4169;
static Bool *_t4170;
static Bool *_t4171;
static Str *_t4172;
static Mode *_t4173;
static Bool *_t4174;
static Bool *_t4175;
static Bool *_t4176;
static Bool *_t4177;
static Str *_t4178;
static Mode *_t4179;
static Bool *_t4180;
static Bool *_t4181;
static Bool *_t4182;
static Bool *_t4183;
static Str *_t4184;
static Mode *_t4185;
static Bool *_t4186;
static Bool *_t4187;
static Bool *_t4188;
static Bool *_t4189;
static Str *_t4190;
static Mode *_t4191;
static Bool *_t4192;
static Bool *_t4193;
static Bool *_t4194;
static Bool *_t4195;
static Str *_t4196;
static Mode *_t4197;
static Bool *_t4198;
static Bool *_t4199;
static Bool *_t4200;
static Bool *_t4201;
static Str *_t4202;
static Mode *_t4203;
static Bool *_t4204;
static Bool *_t4205;
static Bool *_t4206;
static Bool *_t4207;
static Str *_t4208;
static Mode *_t4209;

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t2 = U8_to_i64(DEREF(val));
    (void)_t2;
    Str *_t3 = I64_to_str(&(I64){_t2});
    (void)_t3;
    ;
    return _t3;
}

void U8_inc(U8 * self) {
    (void)self;
    U8 _t4 = 1;
    (void)_t4;
    U8 _t5 = U8_add(DEREF(self), _t4);
    (void)_t5;
    ;
    *self = _t5;
    ;
}

void U8_dec(U8 * self) {
    (void)self;
    U8 _t6 = 1;
    (void)_t6;
    U8 _t7 = U8_sub(DEREF(self), _t6);
    (void)_t7;
    ;
    *self = _t7;
    ;
}

U8 * U8_unity(U8 * self) {
    (void)self;
    I64 _t8 = 1;
    (void)_t8;
    U8 _t9 = I64_to_u8(_t8);
    (void)_t9;
    ;
    { U8 *_r = malloc(sizeof(U8)); *_r = _t9; return _r; }
}

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t25 = I16_to_i64(DEREF(val));
    (void)_t25;
    Str *_t26 = I64_to_str(&(I64){_t25});
    (void)_t26;
    ;
    return _t26;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t27 = 1;
    (void)_t27;
    I16 _t28 = I16_add(DEREF(self), _t27);
    (void)_t28;
    ;
    *self = _t28;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t29 = 1;
    (void)_t29;
    I16 _t30 = I16_sub(DEREF(self), _t29);
    (void)_t30;
    ;
    *self = _t30;
    ;
}

I16 * I16_unity(I16 * self) {
    (void)self;
    I64 _t31 = 1;
    (void)_t31;
    I16 _t32 = I64_to_i16(_t31);
    (void)_t32;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t32; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t33 = 0;
    (void)_t33;
    I64 _t34 = I16_to_i64(DEREF(a));
    (void)_t34;
    I64 _t35 = I64_sub(_t33, _t34);
    (void)_t35;
    ;
    ;
    I16 _t36 = I64_to_i16(_t35);
    (void)_t36;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t36; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t41 = I16_to_i64(DEREF(a));
    (void)_t41;
    I64 _t42 = 0;
    (void)_t42;
    Bool _t43; { Bool *_hp = (Bool *)I64_lt(&(I64){_t41}, &(I64){_t42}); _t43 = *_hp; free(_hp); }
    (void)_t43;
    ;
    ;
    if (_t43) {
        I64 _t37 = 0;
        (void)_t37;
        I64 _t38 = I16_to_i64(DEREF(a));
        (void)_t38;
        I64 _t39 = I64_sub(_t37, _t38);
        (void)_t39;
        ;
        ;
        I16 _t40 = I64_to_i16(_t39);
        (void)_t40;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t40; return _r; }
    }
    ;
    I16 _t44 = I16_clone(a);
    (void)_t44;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t44; return _r; }
}

U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t60 = I32_to_i64(DEREF(val));
    (void)_t60;
    Str *_t61 = I64_to_str(&(I64){_t60});
    (void)_t61;
    ;
    return _t61;
}

void I32_inc(I32 * self) {
    (void)self;
    I32 _t62 = 1;
    (void)_t62;
    I32 _t63 = I32_add(DEREF(self), _t62);
    (void)_t63;
    ;
    *self = _t63;
    ;
}

void I32_dec(I32 * self) {
    (void)self;
    I32 _t64 = 1;
    (void)_t64;
    I32 _t65 = I32_sub(DEREF(self), _t64);
    (void)_t65;
    ;
    *self = _t65;
    ;
}

I32 * I32_unity(I32 * self) {
    (void)self;
    I64 _t66 = 1;
    (void)_t66;
    I32 _t67 = I64_to_i32(_t66);
    (void)_t67;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t67; return _r; }
}

I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t68 = 0;
    (void)_t68;
    I64 _t69 = I32_to_i64(DEREF(a));
    (void)_t69;
    I64 _t70 = I64_sub(_t68, _t69);
    (void)_t70;
    ;
    ;
    I32 _t71 = I64_to_i32(_t70);
    (void)_t71;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t71; return _r; }
}

I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t76 = I32_to_i64(DEREF(a));
    (void)_t76;
    I64 _t77 = 0;
    (void)_t77;
    Bool _t78; { Bool *_hp = (Bool *)I64_lt(&(I64){_t76}, &(I64){_t77}); _t78 = *_hp; free(_hp); }
    (void)_t78;
    ;
    ;
    if (_t78) {
        I64 _t72 = 0;
        (void)_t72;
        I64 _t73 = I32_to_i64(DEREF(a));
        (void)_t73;
        I64 _t74 = I64_sub(_t72, _t73);
        (void)_t74;
        ;
        ;
        I32 _t75 = I64_to_i32(_t74);
        (void)_t75;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t75; return _r; }
    }
    ;
    I32 _t79 = I32_clone(a);
    (void)_t79;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t79; return _r; }
}

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t95 = F32_from_i64_ext(val);
    (void)_t95;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t95; return _r; }
}

U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t111 = U32_to_i64(DEREF(val));
    (void)_t111;
    Str *_t112 = I64_to_str(&(I64){_t111});
    (void)_t112;
    ;
    return _t112;
}

void U32_inc(U32 * self) {
    (void)self;
    U32 _t113 = 1;
    (void)_t113;
    U32 _t114 = U32_add(DEREF(self), _t113);
    (void)_t114;
    ;
    *self = _t114;
    ;
}

void U32_dec(U32 * self) {
    (void)self;
    U32 _t115 = 1;
    (void)_t115;
    U32 _t116 = U32_sub(DEREF(self), _t115);
    (void)_t116;
    ;
    *self = _t116;
    ;
}

U32 * U32_unity(U32 * self) {
    (void)self;
    I64 _t117 = 1;
    (void)_t117;
    U32 _t118 = I64_to_u32(_t117);
    (void)_t118;
    ;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t118; return _r; }
}

U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t134 = U64_to_str_ext(val);
    (void)_t134;
    return _t134;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t135 = U64_from_i64_ext(val);
    (void)_t135;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t135; return _r; }
}

void U64_inc(U64 * self) {
    (void)self;
    U64 _t136 = 1;
    (void)_t136;
    U64 _t137 = U64_add(DEREF(self), _t136);
    (void)_t137;
    ;
    *self = _t137;
    ;
}

void U64_dec(U64 * self) {
    (void)self;
    U64 _t138 = 1;
    (void)_t138;
    U64 _t139 = U64_sub(DEREF(self), _t138);
    (void)_t139;
    ;
    *self = _t139;
    ;
}

U64 * U64_unity(U64 * self) {
    (void)self;
    I64 _t140 = 1;
    (void)_t140;
    U64 _t141 = I64_to_u64(_t140);
    (void)_t141;
    ;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t141; return _r; }
}

U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t193 = 0;
    (void)_t193;
    Bool _t194 = I64_eq(DEREF(val), _t193);
    (void)_t194;
    ;
    if (_t194) {
        U64 _t157 = 2;
        (void)_t157;
        U8 *buf = malloc(_t157);
        (void)buf;
        ;
        I64 _t158 = 48;
        (void)_t158;
        U64 _t159 = 1;
        (void)_t159;
        memcpy(buf, &(I64){_t158}, _t159);
        ;
        ;
        U64 *_t160 = malloc(sizeof(U64));
        *_t160 = 1;
        (void)_t160;
        void *_t161 = ptr_add(buf, DEREF(_t160));
        (void)_t161;
        I32 _t162 = 0;
        (void)_t162;
        U64 _t163 = 1;
        (void)_t163;
        memset(_t161, _t162, _t163);
        U64_delete(_t160, &(Bool){1});
        ;
        ;
        I64 _t164 = 1;
        (void)_t164;
        I64 _t165 = 1;
        (void)_t165;
        Str *_t166 = malloc(sizeof(Str));
        _t166->c_str = buf;
        _t166->count = _t164;
        _t166->cap = _t165;
        (void)_t166;
        ;
        ;
        ;
        return _t166;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t195 = 0;
    (void)_t195;
    Bool _t196; { Bool *_hp = (Bool *)I64_lt(val, &(I64){_t195}); _t196 = *_hp; free(_hp); }
    (void)_t196;
    ;
    if (_t196) {
        Bool _t167 = 1;
        (void)_t167;
        is_neg = _t167;
        ;
        I64 _t168 = 0;
        (void)_t168;
        I64 _t169 = I64_sub(_t168, DEREF(val));
        (void)_t169;
        ;
        v = _t169;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&(I64){v});
    (void)tmp;
    while (1) {
        I64 _t171 = 0;
        (void)_t171;
        Bool _wcond170; { Bool *_hp = (Bool *)I64_gt(&(I64){tmp}, &(I64){_t171}); _wcond170 = *_hp; free(_hp); }
        (void)_wcond170;
        ;
        if (_wcond170) {
        } else {
            ;
            break;
        }
        ;
        U64 _t172 = 1;
        (void)_t172;
        U64 _t173 = U64_add(ndigits, _t172);
        (void)_t173;
        ;
        ndigits = _t173;
        ;
        I64 _t174 = 10;
        (void)_t174;
        I64 _t175 = I64_div(tmp, _t174);
        (void)_t175;
        ;
        tmp = _t175;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    (void)total;
    ;
    if (is_neg) {
        U64 _t176 = 1;
        (void)_t176;
        U64 _t177 = U64_add(DEREF(total), _t176);
        (void)_t177;
        ;
        *total = _t177;
        ;
    }
    U64 _t197 = 1;
    (void)_t197;
    U64 _t198 = U64_add(DEREF(total), _t197);
    (void)_t198;
    ;
    U8 *buf = malloc(_t198);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t178 = 45;
        (void)_t178;
        U64 _t179 = 1;
        (void)_t179;
        memcpy(buf, &(I64){_t178}, _t179);
        ;
        ;
    }
    ;
    U64 _t199 = 1;
    (void)_t199;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t199);
    (void)i;
    ;
    while (1) {
        I64 _t181 = 0;
        (void)_t181;
        Bool _wcond180; { Bool *_hp = (Bool *)I64_gt(&(I64){v}, &(I64){_t181}); _wcond180 = *_hp; free(_hp); }
        (void)_wcond180;
        ;
        if (_wcond180) {
        } else {
            ;
            break;
        }
        ;
        I64 _t182 = 10;
        (void)_t182;
        I64 _t183 = I64_mod(v, _t182);
        (void)_t183;
        ;
        I64 _t184 = 48;
        (void)_t184;
        I64 _t185 = I64_add(_t183, _t184);
        (void)_t185;
        ;
        ;
        void *_t186 = ptr_add(buf, DEREF(i));
        (void)_t186;
        U8 _t187 = I64_to_u8(_t185);
        (void)_t187;
        ;
        U64 _t188 = 1;
        (void)_t188;
        memcpy(_t186, &(U8){_t187}, _t188);
        ;
        ;
        I64 _t189 = 10;
        (void)_t189;
        I64 _t190 = I64_div(v, _t189);
        (void)_t190;
        ;
        v = _t190;
        ;
        U64 _t191 = 1;
        (void)_t191;
        U64 _t192 = U64_sub(DEREF(i), _t191);
        (void)_t192;
        ;
        *i = _t192;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t200 = ptr_add(buf, DEREF(total));
    (void)_t200;
    I32 _t201 = 0;
    (void)_t201;
    U64 _t202 = 1;
    (void)_t202;
    memset(_t200, _t201, _t202);
    ;
    ;
    U64 _t203 = U64_clone(total);
    (void)_t203;
    U64 _t204 = U64_clone(total);
    (void)_t204;
    U64_delete(total, &(Bool){1});
    Str *_t205 = malloc(sizeof(Str));
    _t205->c_str = buf;
    _t205->count = _t203;
    _t205->cap = _t204;
    (void)_t205;
    ;
    ;
    return _t205;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t206 = 1;
    (void)_t206;
    I64 _t207 = I64_add(DEREF(self), _t206);
    (void)_t207;
    ;
    *self = _t207;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t208 = 1;
    (void)_t208;
    I64 _t209 = I64_sub(DEREF(self), _t208);
    (void)_t209;
    ;
    *self = _t209;
    ;
}

I64 * I64_unity(I64 * self) {
    (void)self;
    I64 _t210 = 1;
    (void)_t210;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t210; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t211 = 0;
    (void)_t211;
    I64 _t212 = I64_sub(_t211, DEREF(a));
    (void)_t212;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t212; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t215 = 0;
    (void)_t215;
    Bool _t216; { Bool *_hp = (Bool *)I64_lt(a, &(I64){_t215}); _t216 = *_hp; free(_hp); }
    (void)_t216;
    ;
    if (_t216) {
        I64 _t213 = 0;
        (void)_t213;
        I64 _t214 = I64_sub(_t213, DEREF(a));
        (void)_t214;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t214; return _r; }
    }
    ;
    I64 _t217 = I64_clone(a);
    (void)_t217;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t217; return _r; }
}

U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

Range * Range_new(U64 start, U64 end) {
    (void)start;
    (void)end;
    U64 _t233 = U64_clone(&(U64){start});
    (void)_t233;
    U64 _t234 = U64_clone(&(U64){end});
    (void)_t234;
    Range *_t235 = malloc(sizeof(Range));
    _t235->start = _t233;
    _t235->end = _t234;
    (void)_t235;
    ;
    ;
    return _t235;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t237; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t237 = *_hp; free(_hp); }
    (void)_t237;
    if (_t237) {
        U64 _t236 = U64_sub(self->end, self->start);
        (void)_t236;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t236; return _r; }
    }
    ;
    U64 _t238 = U64_sub(self->start, self->end);
    (void)_t238;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t238; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    (void)i;
    Bool _t240; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t240 = *_hp; free(_hp); }
    (void)_t240;
    if (_t240) {
        U64 _t239 = U64_add(self->start, i);
        (void)_t239;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t239; return _r; }
    }
    ;
    U64 _t241 = U64_sub(self->start, i);
    (void)_t241;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t241; return _r; }
}

Range * Range_clone(Range * val) {
    (void)val;
    Range *_t242 = malloc(sizeof(Range));
    _t242->start = val->start;
    _t242->end = val->end;
    (void)_t242;
    return _t242;
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
        Str *_t244 = Str_lit("true", 4ULL);
        (void)_t244;
        return _t244;
    } else {
        Str *_t245 = Str_lit("false", 5ULL);
        (void)_t245;
        return _t245;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t250 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t250;
    if (_t250) {
        I64 _t246 = 0;
        (void)_t246;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t246; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t247 = 0;
        (void)_t247;
        I64 _t248 = 1;
        (void)_t248;
        I64 _t249 = I64_sub(_t247, _t248);
        (void)_t249;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t249; return _r; }
    }
    I64 _t251 = 1;
    (void)_t251;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t251; return _r; }
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
    Bool _t390; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t390 = *_hp; free(_hp); }
    (void)_t390;
    if (_t390) {
        Str *_t384 = Str_lit("Str", 3ULL);
        (void)_t384;
        U64 _t385; { U64 *_hp = (U64 *)Str_size(); _t385 = *_hp; free(_hp); }
        (void)_t385;
        U64 _t386 = 1;
        (void)_t386;
        Array *_va7 = Array_new(_t384, &(U64){_t385}, &(U64){_t386});
        (void)_va7;
        Str_delete(_t384, &(Bool){1});
        ;
        ;
        U64 _t387 = 0;
        (void)_t387;
        Str *_t388 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t388;
        Array_set(_va7, &(U64){_t387}, _t388);
        ;
        Str *_t389 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:11:41", 62ULL);
        (void)_t389;
        panic(_t389, _va7);
        Str_delete(_t389, &(Bool){1});
    }
    ;
    void *_t391 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t391;
    U64 _t392 = U64_clone(cap);
    (void)_t392;
    U64 _t393 = U64_clone(elem_size);
    (void)_t393;
    Array *_t394 = malloc(sizeof(Array));
    _t394->data = _t391;
    _t394->cap = _t392;
    _t394->elem_size = _t393;
    { Str *_ca = Str_clone(elem_type); _t394->elem_type = *_ca; free(_ca); }
    (void)_t394;
    ;
    ;
    return _t394;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t409; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t409 = *_hp; free(_hp); }
    (void)_t409;
    if (_t409) {
        Str *_t395 = Str_lit("Str", 3ULL);
        (void)_t395;
        U64 _t396; { U64 *_hp = (U64 *)Str_size(); _t396 = *_hp; free(_hp); }
        (void)_t396;
        U64 _t397 = 5;
        (void)_t397;
        Array *_va8 = Array_new(_t395, &(U64){_t396}, &(U64){_t397});
        (void)_va8;
        Str_delete(_t395, &(Bool){1});
        ;
        ;
        U64 _t398 = 0;
        (void)_t398;
        Str *_t399 = Str_lit("Array.get: index ", 17ULL);
        (void)_t399;
        Array_set(_va8, &(U64){_t398}, _t399);
        ;
        U64 _t400 = 1;
        (void)_t400;
        Str *_t401 = U64_to_str(DEREF(i));
        (void)_t401;
        Array_set(_va8, &(U64){_t400}, _t401);
        ;
        U64 _t402 = 2;
        (void)_t402;
        Str *_t403 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t403;
        Array_set(_va8, &(U64){_t402}, _t403);
        ;
        U64 _t404 = 3;
        (void)_t404;
        Str *_t405 = U64_to_str(self->cap);
        (void)_t405;
        Array_set(_va8, &(U64){_t404}, _t405);
        ;
        U64 _t406 = 4;
        (void)_t406;
        Str *_t407 = Str_lit(")", 1ULL);
        (void)_t407;
        Array_set(_va8, &(U64){_t406}, _t407);
        ;
        Str *_t408 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:20:19", 62ULL);
        (void)_t408;
        panic(_t408, _va8);
        Str_delete(_t408, &(Bool){1});
    }
    ;
    U64 *_t410 = malloc(sizeof(U64)); *_t410 = U64_mul(DEREF(i), self->elem_size);
    (void)_t410;
    void *_t411 = ptr_add(self->data, DEREF(_t410));
    (void)_t411;
    U64_delete(_t410, &(Bool){1});
    return _t411;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t426; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t426 = *_hp; free(_hp); }
    (void)_t426;
    if (_t426) {
        Str *_t412 = Str_lit("Str", 3ULL);
        (void)_t412;
        U64 _t413; { U64 *_hp = (U64 *)Str_size(); _t413 = *_hp; free(_hp); }
        (void)_t413;
        U64 _t414 = 5;
        (void)_t414;
        Array *_va9 = Array_new(_t412, &(U64){_t413}, &(U64){_t414});
        (void)_va9;
        Str_delete(_t412, &(Bool){1});
        ;
        ;
        U64 _t415 = 0;
        (void)_t415;
        Str *_t416 = Str_lit("Array.set: index ", 17ULL);
        (void)_t416;
        Array_set(_va9, &(U64){_t415}, _t416);
        ;
        U64 _t417 = 1;
        (void)_t417;
        Str *_t418 = U64_to_str(DEREF(i));
        (void)_t418;
        Array_set(_va9, &(U64){_t417}, _t418);
        ;
        U64 _t419 = 2;
        (void)_t419;
        Str *_t420 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t420;
        Array_set(_va9, &(U64){_t419}, _t420);
        ;
        U64 _t421 = 3;
        (void)_t421;
        Str *_t422 = U64_to_str(self->cap);
        (void)_t422;
        Array_set(_va9, &(U64){_t421}, _t422);
        ;
        U64 _t423 = 4;
        (void)_t423;
        Str *_t424 = Str_lit(")", 1ULL);
        (void)_t424;
        Array_set(_va9, &(U64){_t423}, _t424);
        ;
        Str *_t425 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:28:19", 62ULL);
        (void)_t425;
        panic(_t425, _va9);
        Str_delete(_t425, &(Bool){1});
    }
    ;
    U64 *_t427 = malloc(sizeof(U64)); *_t427 = U64_mul(DEREF(i), self->elem_size);
    (void)_t427;
    void *_t428 = ptr_add(self->data, DEREF(_t427));
    (void)_t428;
    Bool _t429 = 0;
    (void)_t429;
    dyn_call_delete(&self->elem_type, _t428, &(Bool){_t429});
    U64_delete(_t427, &(Bool){1});
    ;
    U64 *_t430 = malloc(sizeof(U64)); *_t430 = U64_mul(DEREF(i), self->elem_size);
    (void)_t430;
    void *_t431 = ptr_add(self->data, DEREF(_t430));
    (void)_t431;
    memcpy(_t431, val, self->elem_size);
    U64_delete(_t430, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    {
        U64 _t440 = 0;
        (void)_t440;
        Range *_fc432 = Range_new(_t440, self->cap);
        (void)_fc432;
        ;
        U64 _fi432 = 0;
        (void)_fi432;
        while (1) {
            U64 _t434; { U64 *_hp = (U64 *)Range_len(_fc432); _t434 = *_hp; free(_hp); }
            (void)_t434;
            Bool _wcond433; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi432}, &(U64){_t434}); _wcond433 = *_hp; free(_hp); }
            (void)_wcond433;
            ;
            if (_wcond433) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc432, _fi432); i = *_hp; free(_hp); }
            (void)i;
            U64 _t435 = 1;
            (void)_t435;
            U64 _t436 = U64_add(_fi432, _t435);
            (void)_t436;
            ;
            _fi432 = _t436;
            ;
            U64 *_t437 = malloc(sizeof(U64)); *_t437 = U64_mul(i, self->elem_size);
            (void)_t437;
            ;
            void *_t438 = ptr_add(self->data, DEREF(_t437));
            (void)_t438;
            Bool _t439 = 0;
            (void)_t439;
            dyn_call_delete(&self->elem_type, _t438, &(Bool){_t439});
            U64_delete(_t437, &(Bool){1});
            ;
        }
        Range_delete(_fc432, &(Bool){1});
        ;
    }
    free(self->data);
    Bool _t441 = 0;
    (void)_t441;
    Str_delete(&self->elem_type, &(Bool){_t441});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t452 = U64_mul(self->cap, self->elem_size);
    (void)_t452;
    U8 *new_data = malloc(_t452);
    (void)new_data;
    ;
    {
        U64 _t451 = 0;
        (void)_t451;
        Range *_fc442 = Range_new(_t451, self->cap);
        (void)_fc442;
        ;
        U64 _fi442 = 0;
        (void)_fi442;
        while (1) {
            U64 _t444; { U64 *_hp = (U64 *)Range_len(_fc442); _t444 = *_hp; free(_hp); }
            (void)_t444;
            Bool _wcond443; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi442}, &(U64){_t444}); _wcond443 = *_hp; free(_hp); }
            (void)_wcond443;
            ;
            if (_wcond443) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc442, _fi442); i = *_hp; free(_hp); }
            (void)i;
            U64 _t445 = 1;
            (void)_t445;
            U64 _t446 = U64_add(_fi442, _t445);
            (void)_t446;
            ;
            _fi442 = _t446;
            ;
            U64 *_t447 = malloc(sizeof(U64)); *_t447 = U64_mul(i, self->elem_size);
            (void)_t447;
            void *_t448 = ptr_add(self->data, DEREF(_t447));
            (void)_t448;
            void *cloned = dyn_call_clone(&self->elem_type, _t448);
            (void)cloned;
            U64_delete(_t447, &(Bool){1});
            U64 *_t449 = malloc(sizeof(U64)); *_t449 = U64_mul(i, self->elem_size);
            (void)_t449;
            ;
            void *_t450 = ptr_add(new_data, DEREF(_t449));
            (void)_t450;
            memcpy(_t450, cloned, self->elem_size);
            U64_delete(_t449, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc442, &(Bool){1});
        ;
    }
    Array *_t453 = malloc(sizeof(Array));
    _t453->data = new_data;
    _t453->cap = self->cap;
    _t453->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t453->elem_type = *_ca; free(_ca); }
    (void)_t453;
    return _t453;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t471; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t471 = *_hp; free(_hp); }
    (void)_t471;
    if (_t471) {
        Str *_t455 = Str_lit("Str", 3ULL);
        (void)_t455;
        U64 _t456; { U64 *_hp = (U64 *)Str_size(); _t456 = *_hp; free(_hp); }
        (void)_t456;
        U64 _t457 = 1;
        (void)_t457;
        Array *_va10 = Array_new(_t455, &(U64){_t456}, &(U64){_t457});
        (void)_va10;
        Str_delete(_t455, &(Bool){1});
        ;
        ;
        U64 _t458 = 0;
        (void)_t458;
        Str *_t459 = Str_lit("Map.new: key_type required", 26ULL);
        (void)_t459;
        Array_set(_va10, &(U64){_t458}, _t459);
        ;
        Str *_t460 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:15:40", 60ULL);
        (void)_t460;
        panic(_t460, _va10);
        Str_delete(_t460, &(Bool){1});
    }
    ;
    Bool _t472 = dyn_has_cmp(key_type);
    (void)_t472;
    Bool _t473 = Bool_not(_t472);
    (void)_t473;
    ;
    if (_t473) {
        Str *_t461 = Str_lit("Str", 3ULL);
        (void)_t461;
        U64 _t462; { U64 *_hp = (U64 *)Str_size(); _t462 = *_hp; free(_hp); }
        (void)_t462;
        U64 _t463 = 3;
        (void)_t463;
        Array *_va11 = Array_new(_t461, &(U64){_t462}, &(U64){_t463});
        (void)_va11;
        Str_delete(_t461, &(Bool){1});
        ;
        ;
        U64 _t464 = 0;
        (void)_t464;
        Str *_t465 = Str_lit("Map.new: type ", 14ULL);
        (void)_t465;
        Array_set(_va11, &(U64){_t464}, _t465);
        ;
        U64 _t466 = 1;
        (void)_t466;
        Str *_t467 = Str_clone(key_type);
        (void)_t467;
        Array_set(_va11, &(U64){_t466}, _t467);
        ;
        U64 _t468 = 2;
        (void)_t468;
        Str *_t469 = Str_lit(" must implement cmp", 19ULL);
        (void)_t469;
        Array_set(_va11, &(U64){_t468}, _t469);
        ;
        Str *_t470 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:19", 60ULL);
        (void)_t470;
        panic(_t470, _va11);
        Str_delete(_t470, &(Bool){1});
    }
    ;
    void *_t474 = malloc(DEREF(key_size));
    (void)_t474;
    void *_t475 = malloc(DEREF(val_size));
    (void)_t475;
    U64 _t476 = 0;
    (void)_t476;
    I64 _t477 = 1;
    (void)_t477;
    U64 _t478 = U64_clone(key_size);
    (void)_t478;
    U64 _t479 = U64_clone(val_size);
    (void)_t479;
    Map *_t480 = malloc(sizeof(Map));
    _t480->key_data = _t474;
    _t480->val_data = _t475;
    _t480->count = _t476;
    _t480->cap = _t477;
    _t480->key_size = _t478;
    { Str *_ca = Str_clone(key_type); _t480->key_type = *_ca; free(_ca); }
    _t480->val_size = _t479;
    { Str *_ca = Str_clone(val_type); _t480->val_type = *_ca; free(_ca); }
    (void)_t480;
    ;
    ;
    ;
    ;
    return _t480;
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
        Bool _wcond481; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond481 = *_hp; free(_hp); }
        (void)_wcond481;
        if (_wcond481) {
        } else {
            ;
            break;
        }
        ;
        U64 _t488 = U64_sub(hi, lo);
        (void)_t488;
        U64 _t489 = 2;
        (void)_t489;
        U64 _t490 = U64_div(_t488, _t489);
        (void)_t490;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t490);
        (void)mid;
        ;
        U64 *_t491 = malloc(sizeof(U64)); *_t491 = U64_mul(DEREF(mid), self->key_size);
        (void)_t491;
        void *_t492 = ptr_add(self->key_data, DEREF(_t491));
        (void)_t492;
        I64 *c = dyn_call_cmp(&self->key_type, _t492, key);
        (void)c;
        U64_delete(_t491, &(Bool){1});
        I64 _t493 = 0;
        (void)_t493;
        Bool _t494; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t493}); _t494 = *_hp; free(_hp); }
        (void)_t494;
        ;
        if (_t494) {
            U64 _t482 = 1;
            (void)_t482;
            U64 _t483 = U64_add(DEREF(mid), _t482);
            (void)_t483;
            ;
            lo = _t483;
            ;
        } else {
            I64 _t486 = 0;
            (void)_t486;
            Bool _t487; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t486}); _t487 = *_hp; free(_hp); }
            (void)_t487;
            ;
            if (_t487) {
                U64 _t484 = U64_clone(mid);
                (void)_t484;
                hi = _t484;
                ;
            } else {
                Bool _t485 = 1;
                (void)_t485;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t485; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t495 = 0;
    (void)_t495;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t495; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond496; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond496 = *_hp; free(_hp); }
        (void)_wcond496;
        if (_wcond496) {
        } else {
            ;
            break;
        }
        ;
        U64 _t504 = U64_sub(hi, lo);
        (void)_t504;
        U64 _t505 = 2;
        (void)_t505;
        U64 _t506 = U64_div(_t504, _t505);
        (void)_t506;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t506);
        (void)mid;
        ;
        U64 *_t507 = malloc(sizeof(U64)); *_t507 = U64_mul(DEREF(mid), self->key_size);
        (void)_t507;
        void *_t508 = ptr_add(self->key_data, DEREF(_t507));
        (void)_t508;
        I64 *c = dyn_call_cmp(&self->key_type, _t508, key);
        (void)c;
        U64_delete(_t507, &(Bool){1});
        I64 _t509 = 0;
        (void)_t509;
        Bool _t510; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t509}); _t510 = *_hp; free(_hp); }
        (void)_t510;
        ;
        if (_t510) {
            U64 _t497 = 1;
            (void)_t497;
            U64 _t498 = U64_add(DEREF(mid), _t497);
            (void)_t498;
            ;
            lo = _t498;
            ;
        } else {
            I64 _t502 = 0;
            (void)_t502;
            Bool _t503; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t502}); _t503 = *_hp; free(_hp); }
            (void)_t503;
            ;
            if (_t503) {
                U64 _t499 = U64_clone(mid);
                (void)_t499;
                hi = _t499;
                ;
            } else {
                U64 *_t500 = malloc(sizeof(U64)); *_t500 = U64_mul(DEREF(mid), self->val_size);
                (void)_t500;
                void *_t501 = ptr_add(self->val_data, DEREF(_t500));
                (void)_t501;
                U64_delete(_t500, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t501;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t511 = Str_lit("Str", 3ULL);
    (void)_t511;
    U64 _t512; { U64 *_hp = (U64 *)Str_size(); _t512 = *_hp; free(_hp); }
    (void)_t512;
    U64 _t513 = 1;
    (void)_t513;
    Array *_va12 = Array_new(_t511, &(U64){_t512}, &(U64){_t513});
    (void)_va12;
    Str_delete(_t511, &(Bool){1});
    ;
    ;
    U64 _t514 = 0;
    (void)_t514;
    Str *_t515 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t515;
    Array_set(_va12, &(U64){_t514}, _t515);
    ;
    Str *_t516 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:55:15", 60ULL);
    (void)_t516;
    panic(_t516, _va12);
    Str_delete(_t516, &(Bool){1});
    U64 *_t517 = malloc(sizeof(U64));
    *_t517 = 0;
    (void)_t517;
    void *_t518 = ptr_add(self->val_data, DEREF(_t517));
    (void)_t518;
    U64_delete(_t517, &(Bool){1});
    return _t518;
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
        Bool _wcond519; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond519 = *_hp; free(_hp); }
        (void)_wcond519;
        if (_wcond519) {
        } else {
            ;
            break;
        }
        ;
        U64 _t528 = U64_sub(hi, lo);
        (void)_t528;
        U64 _t529 = 2;
        (void)_t529;
        U64 _t530 = U64_div(_t528, _t529);
        (void)_t530;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t530);
        (void)mid;
        ;
        U64 *_t531 = malloc(sizeof(U64)); *_t531 = U64_mul(DEREF(mid), self->key_size);
        (void)_t531;
        void *_t532 = ptr_add(self->key_data, DEREF(_t531));
        (void)_t532;
        I64 *c = dyn_call_cmp(&self->key_type, _t532, key);
        (void)c;
        U64_delete(_t531, &(Bool){1});
        I64 _t533 = 0;
        (void)_t533;
        Bool _t534; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t533}); _t534 = *_hp; free(_hp); }
        (void)_t534;
        ;
        if (_t534) {
            U64 _t520 = 1;
            (void)_t520;
            U64 _t521 = U64_add(DEREF(mid), _t520);
            (void)_t521;
            ;
            lo = _t521;
            ;
        } else {
            I64 _t526 = 0;
            (void)_t526;
            Bool _t527; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t526}); _t527 = *_hp; free(_hp); }
            (void)_t527;
            ;
            if (_t527) {
                U64 _t522 = U64_clone(mid);
                (void)_t522;
                hi = _t522;
                ;
            } else {
                Bool _t523 = 1;
                (void)_t523;
                found = _t523;
                ;
                U64 _t524 = U64_clone(mid);
                (void)_t524;
                lo = _t524;
                ;
                U64 _t525 = U64_clone(mid);
                (void)_t525;
                hi = _t525;
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
        Bool _t539; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t539 = *_hp; free(_hp); }
        (void)_t539;
        Bool _t540 = Bool_not(_t539);
        (void)_t540;
        ;
        if (_t540) {
            Bool _t535 = 0;
            (void)_t535;
            dyn_call_delete(&self->key_type, key, &(Bool){_t535});
            ;
        }
        ;
        free(key);
        Bool _t541; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t541 = *_hp; free(_hp); }
        (void)_t541;
        Bool _t542 = Bool_not(_t541);
        (void)_t542;
        ;
        if (_t542) {
            U64 *_t536 = malloc(sizeof(U64)); *_t536 = U64_mul(lo, self->val_size);
            (void)_t536;
            void *_t537 = ptr_add(self->val_data, DEREF(_t536));
            (void)_t537;
            Bool _t538 = 0;
            (void)_t538;
            dyn_call_delete(&self->val_type, _t537, &(Bool){_t538});
            U64_delete(_t536, &(Bool){1});
            ;
        }
        ;
        U64 *_t543 = malloc(sizeof(U64)); *_t543 = U64_mul(lo, self->val_size);
        (void)_t543;
        void *_t544 = ptr_add(self->val_data, DEREF(_t543));
        (void)_t544;
        memcpy(_t544, val, self->val_size);
        U64_delete(_t543, &(Bool){1});
        free(val);
    } else {
        Bool _t551 = U64_eq(self->count, self->cap);
        (void)_t551;
        if (_t551) {
            U64 _t545 = 2;
            (void)_t545;
            U64 new_cap = U64_mul(self->cap, _t545);
            (void)new_cap;
            ;
            U64 _t546 = U64_mul(new_cap, self->key_size);
            (void)_t546;
            void *_t547 = realloc(self->key_data, _t546);
            (void)_t547;
            ;
            self->key_data = _t547;
            U64 _t548 = U64_mul(new_cap, self->val_size);
            (void)_t548;
            void *_t549 = realloc(self->val_data, _t548);
            (void)_t549;
            ;
            self->val_data = _t549;
            U64 _t550 = U64_clone(&(U64){new_cap});
            (void)_t550;
            ;
            self->cap = _t550;
            ;
        }
        ;
        U64 _t552 = 1;
        (void)_t552;
        U64 _t553 = U64_add(lo, _t552);
        (void)_t553;
        ;
        U64 *_t554 = malloc(sizeof(U64)); *_t554 = U64_mul(_t553, self->key_size);
        (void)_t554;
        ;
        U64 *_t555 = malloc(sizeof(U64)); *_t555 = U64_mul(lo, self->key_size);
        (void)_t555;
        U64 _t556 = U64_sub(self->count, lo);
        (void)_t556;
        void *_t557 = ptr_add(self->key_data, DEREF(_t554));
        (void)_t557;
        void *_t558 = ptr_add(self->key_data, DEREF(_t555));
        (void)_t558;
        U64 _t559 = U64_mul(_t556, self->key_size);
        (void)_t559;
        ;
        memmove(_t557, _t558, _t559);
        U64_delete(_t554, &(Bool){1});
        U64_delete(_t555, &(Bool){1});
        ;
        U64 _t560 = 1;
        (void)_t560;
        U64 _t561 = U64_add(lo, _t560);
        (void)_t561;
        ;
        U64 *_t562 = malloc(sizeof(U64)); *_t562 = U64_mul(_t561, self->val_size);
        (void)_t562;
        ;
        U64 *_t563 = malloc(sizeof(U64)); *_t563 = U64_mul(lo, self->val_size);
        (void)_t563;
        U64 _t564 = U64_sub(self->count, lo);
        (void)_t564;
        void *_t565 = ptr_add(self->val_data, DEREF(_t562));
        (void)_t565;
        void *_t566 = ptr_add(self->val_data, DEREF(_t563));
        (void)_t566;
        U64 _t567 = U64_mul(_t564, self->val_size);
        (void)_t567;
        ;
        memmove(_t565, _t566, _t567);
        U64_delete(_t562, &(Bool){1});
        U64_delete(_t563, &(Bool){1});
        ;
        U64 *_t568 = malloc(sizeof(U64)); *_t568 = U64_mul(lo, self->key_size);
        (void)_t568;
        void *_t569 = ptr_add(self->key_data, DEREF(_t568));
        (void)_t569;
        memcpy(_t569, key, self->key_size);
        U64_delete(_t568, &(Bool){1});
        U64 *_t570 = malloc(sizeof(U64)); *_t570 = U64_mul(lo, self->val_size);
        (void)_t570;
        void *_t571 = ptr_add(self->val_data, DEREF(_t570));
        (void)_t571;
        memcpy(_t571, val, self->val_size);
        U64_delete(_t570, &(Bool){1});
        free(key);
        free(val);
        U64 _t572 = 1;
        (void)_t572;
        U64 _t573 = U64_add(self->count, _t572);
        (void)_t573;
        ;
        self->count = _t573;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t594; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t594 = *_hp; free(_hp); }
    (void)_t594;
    Bool _t595 = Bool_not(_t594);
    (void)_t595;
    ;
    if (_t595) {
        {
            U64 _t582 = 0;
            (void)_t582;
            Range *_fc574 = Range_new(_t582, self->count);
            (void)_fc574;
            ;
            U64 _fi574 = 0;
            (void)_fi574;
            while (1) {
                U64 _t576; { U64 *_hp = (U64 *)Range_len(_fc574); _t576 = *_hp; free(_hp); }
                (void)_t576;
                Bool _wcond575; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi574}, &(U64){_t576}); _wcond575 = *_hp; free(_hp); }
                (void)_wcond575;
                ;
                if (_wcond575) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc574, _fi574); i = *_hp; free(_hp); }
                (void)i;
                U64 _t577 = 1;
                (void)_t577;
                U64 _t578 = U64_add(_fi574, _t577);
                (void)_t578;
                ;
                _fi574 = _t578;
                ;
                U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(i, self->key_size);
                (void)_t579;
                ;
                void *_t580 = ptr_add(self->key_data, DEREF(_t579));
                (void)_t580;
                Bool _t581 = 0;
                (void)_t581;
                dyn_call_delete(&self->key_type, _t580, &(Bool){_t581});
                U64_delete(_t579, &(Bool){1});
                ;
            }
            Range_delete(_fc574, &(Bool){1});
            ;
        }
    }
    ;
    Bool _t596; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t596 = *_hp; free(_hp); }
    (void)_t596;
    Bool _t597 = Bool_not(_t596);
    (void)_t597;
    ;
    if (_t597) {
        {
            U64 _t591 = 0;
            (void)_t591;
            Range *_fc583 = Range_new(_t591, self->count);
            (void)_fc583;
            ;
            U64 _fi583 = 0;
            (void)_fi583;
            while (1) {
                U64 _t585; { U64 *_hp = (U64 *)Range_len(_fc583); _t585 = *_hp; free(_hp); }
                (void)_t585;
                Bool _wcond584; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi583}, &(U64){_t585}); _wcond584 = *_hp; free(_hp); }
                (void)_wcond584;
                ;
                if (_wcond584) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc583, _fi583); i = *_hp; free(_hp); }
                (void)i;
                U64 _t586 = 1;
                (void)_t586;
                U64 _t587 = U64_add(_fi583, _t586);
                (void)_t587;
                ;
                _fi583 = _t587;
                ;
                U64 *_t588 = malloc(sizeof(U64)); *_t588 = U64_mul(i, self->val_size);
                (void)_t588;
                ;
                void *_t589 = ptr_add(self->val_data, DEREF(_t588));
                (void)_t589;
                Bool _t590 = 0;
                (void)_t590;
                dyn_call_delete(&self->val_type, _t589, &(Bool){_t590});
                U64_delete(_t588, &(Bool){1});
                ;
            }
            Range_delete(_fc583, &(Bool){1});
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t598; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t598 = *_hp; free(_hp); }
    (void)_t598;
    Bool _t599 = Bool_not(_t598);
    (void)_t599;
    ;
    if (_t599) {
        Bool _t592 = 0;
        (void)_t592;
        Str_delete(&self->key_type, &(Bool){_t592});
        ;
    }
    ;
    Bool _t600; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t600 = *_hp; free(_hp); }
    (void)_t600;
    Bool _t601 = Bool_not(_t600);
    (void)_t601;
    ;
    if (_t601) {
        Bool _t593 = 0;
        (void)_t593;
        Str_delete(&self->val_type, &(Bool){_t593});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t616 = U64_mul(self->cap, self->key_size);
    (void)_t616;
    U8 *new_keys = malloc(_t616);
    (void)new_keys;
    ;
    U64 _t617 = U64_mul(self->cap, self->val_size);
    (void)_t617;
    U8 *new_vals = malloc(_t617);
    (void)new_vals;
    ;
    {
        U64 _t615 = 0;
        (void)_t615;
        Range *_fc602 = Range_new(_t615, self->count);
        (void)_fc602;
        ;
        U64 _fi602 = 0;
        (void)_fi602;
        while (1) {
            U64 _t604; { U64 *_hp = (U64 *)Range_len(_fc602); _t604 = *_hp; free(_hp); }
            (void)_t604;
            Bool _wcond603; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi602}, &(U64){_t604}); _wcond603 = *_hp; free(_hp); }
            (void)_wcond603;
            ;
            if (_wcond603) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc602, _fi602); i = *_hp; free(_hp); }
            (void)i;
            U64 _t605 = 1;
            (void)_t605;
            U64 _t606 = U64_add(_fi602, _t605);
            (void)_t606;
            ;
            _fi602 = _t606;
            ;
            U64 *_t607 = malloc(sizeof(U64)); *_t607 = U64_mul(i, self->key_size);
            (void)_t607;
            void *_t608 = ptr_add(self->key_data, DEREF(_t607));
            (void)_t608;
            void *ck = dyn_call_clone(&self->key_type, _t608);
            (void)ck;
            U64_delete(_t607, &(Bool){1});
            U64 *_t609 = malloc(sizeof(U64)); *_t609 = U64_mul(i, self->key_size);
            (void)_t609;
            void *_t610 = ptr_add(new_keys, DEREF(_t609));
            (void)_t610;
            memcpy(_t610, ck, self->key_size);
            U64_delete(_t609, &(Bool){1});
            free(ck);
            U64 *_t611 = malloc(sizeof(U64)); *_t611 = U64_mul(i, self->val_size);
            (void)_t611;
            void *_t612 = ptr_add(self->val_data, DEREF(_t611));
            (void)_t612;
            void *cv = dyn_call_clone(&self->val_type, _t612);
            (void)cv;
            U64_delete(_t611, &(Bool){1});
            U64 *_t613 = malloc(sizeof(U64)); *_t613 = U64_mul(i, self->val_size);
            (void)_t613;
            ;
            void *_t614 = ptr_add(new_vals, DEREF(_t613));
            (void)_t614;
            memcpy(_t614, cv, self->val_size);
            U64_delete(_t613, &(Bool){1});
            free(cv);
        }
        Range_delete(_fc602, &(Bool){1});
        ;
    }
    Map *_t618 = malloc(sizeof(Map));
    _t618->key_data = new_keys;
    _t618->val_data = new_vals;
    _t618->count = self->count;
    _t618->cap = self->cap;
    _t618->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t618->key_type = *_ca; free(_ca); }
    _t618->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t618->val_type = *_ca; free(_ca); }
    (void)_t618;
    return _t618;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t636; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t636 = *_hp; free(_hp); }
    (void)_t636;
    if (_t636) {
        Str *_t620 = Str_lit("Str", 3ULL);
        (void)_t620;
        U64 _t621; { U64 *_hp = (U64 *)Str_size(); _t621 = *_hp; free(_hp); }
        (void)_t621;
        U64 _t622 = 1;
        (void)_t622;
        Array *_va13 = Array_new(_t620, &(U64){_t621}, &(U64){_t622});
        (void)_va13;
        Str_delete(_t620, &(Bool){1});
        ;
        ;
        U64 _t623 = 0;
        (void)_t623;
        Str *_t624 = Str_lit("Set.new: elem_type required", 27ULL);
        (void)_t624;
        Array_set(_va13, &(U64){_t623}, _t624);
        ;
        Str *_t625 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:12:41", 60ULL);
        (void)_t625;
        panic(_t625, _va13);
        Str_delete(_t625, &(Bool){1});
    }
    ;
    Bool _t637 = dyn_has_cmp(elem_type);
    (void)_t637;
    Bool _t638 = Bool_not(_t637);
    (void)_t638;
    ;
    if (_t638) {
        Str *_t626 = Str_lit("Str", 3ULL);
        (void)_t626;
        U64 _t627; { U64 *_hp = (U64 *)Str_size(); _t627 = *_hp; free(_hp); }
        (void)_t627;
        U64 _t628 = 3;
        (void)_t628;
        Array *_va14 = Array_new(_t626, &(U64){_t627}, &(U64){_t628});
        (void)_va14;
        Str_delete(_t626, &(Bool){1});
        ;
        ;
        U64 _t629 = 0;
        (void)_t629;
        Str *_t630 = Str_lit("Set.new: type ", 14ULL);
        (void)_t630;
        Array_set(_va14, &(U64){_t629}, _t630);
        ;
        U64 _t631 = 1;
        (void)_t631;
        Str *_t632 = Str_clone(elem_type);
        (void)_t632;
        Array_set(_va14, &(U64){_t631}, _t632);
        ;
        U64 _t633 = 2;
        (void)_t633;
        Str *_t634 = Str_lit(" must implement cmp", 19ULL);
        (void)_t634;
        Array_set(_va14, &(U64){_t633}, _t634);
        ;
        Str *_t635 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:19", 60ULL);
        (void)_t635;
        panic(_t635, _va14);
        Str_delete(_t635, &(Bool){1});
    }
    ;
    void *_t639 = malloc(DEREF(elem_size));
    (void)_t639;
    U64 _t640 = 0;
    (void)_t640;
    I64 _t641 = 1;
    (void)_t641;
    U64 _t642 = U64_clone(elem_size);
    (void)_t642;
    Set *_t643 = malloc(sizeof(Set));
    _t643->data = _t639;
    _t643->count = _t640;
    _t643->cap = _t641;
    _t643->elem_size = _t642;
    { Str *_ca = Str_clone(elem_type); _t643->elem_type = *_ca; free(_ca); }
    (void)_t643;
    ;
    ;
    ;
    return _t643;
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
        Bool _wcond644; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond644 = *_hp; free(_hp); }
        (void)_wcond644;
        if (_wcond644) {
        } else {
            ;
            break;
        }
        ;
        U64 _t651 = U64_sub(hi, lo);
        (void)_t651;
        U64 _t652 = 2;
        (void)_t652;
        U64 _t653 = U64_div(_t651, _t652);
        (void)_t653;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t653);
        (void)mid;
        ;
        U64 *_t654 = malloc(sizeof(U64)); *_t654 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t654;
        void *_t655 = ptr_add(self->data, DEREF(_t654));
        (void)_t655;
        I64 *c = dyn_call_cmp(&self->elem_type, _t655, val);
        (void)c;
        U64_delete(_t654, &(Bool){1});
        I64 _t656 = 0;
        (void)_t656;
        Bool _t657; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t656}); _t657 = *_hp; free(_hp); }
        (void)_t657;
        ;
        if (_t657) {
            U64 _t645 = 1;
            (void)_t645;
            U64 _t646 = U64_add(DEREF(mid), _t645);
            (void)_t646;
            ;
            lo = _t646;
            ;
        } else {
            I64 _t649 = 0;
            (void)_t649;
            Bool _t650; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t649}); _t650 = *_hp; free(_hp); }
            (void)_t650;
            ;
            if (_t650) {
                U64 _t647 = U64_clone(mid);
                (void)_t647;
                hi = _t647;
                ;
            } else {
                Bool _t648 = 1;
                (void)_t648;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t648; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t658 = 0;
    (void)_t658;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t658; return _r; }
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
        Bool _wcond659; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond659 = *_hp; free(_hp); }
        (void)_wcond659;
        if (_wcond659) {
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
            U64 _t660 = 1;
            (void)_t660;
            U64 _t661 = U64_add(DEREF(mid), _t660);
            (void)_t661;
            ;
            lo = _t661;
            ;
        } else {
            I64 _t666 = 0;
            (void)_t666;
            Bool _t667; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t666}); _t667 = *_hp; free(_hp); }
            (void)_t667;
            ;
            if (_t667) {
                U64 _t662 = U64_clone(mid);
                (void)_t662;
                hi = _t662;
                ;
            } else {
                Bool _t663 = 1;
                (void)_t663;
                found = _t663;
                ;
                U64 _t664 = U64_clone(mid);
                (void)_t664;
                lo = _t664;
                ;
                U64 _t665 = U64_clone(mid);
                (void)_t665;
                hi = _t665;
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
        Bool _t676; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t676 = *_hp; free(_hp); }
        (void)_t676;
        Bool _t677 = Bool_not(_t676);
        (void)_t677;
        ;
        if (_t677) {
            Bool _t675 = 0;
            (void)_t675;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t675});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t682 = U64_eq(self->count, self->cap);
        (void)_t682;
        if (_t682) {
            U64 _t678 = 2;
            (void)_t678;
            U64 new_cap = U64_mul(self->cap, _t678);
            (void)new_cap;
            ;
            U64 _t679 = U64_mul(new_cap, self->elem_size);
            (void)_t679;
            void *_t680 = realloc(self->data, _t679);
            (void)_t680;
            ;
            self->data = _t680;
            U64 _t681 = U64_clone(&(U64){new_cap});
            (void)_t681;
            ;
            self->cap = _t681;
            ;
        }
        ;
        U64 _t683 = 1;
        (void)_t683;
        U64 _t684 = U64_add(lo, _t683);
        (void)_t684;
        ;
        U64 *_t685 = malloc(sizeof(U64)); *_t685 = U64_mul(_t684, self->elem_size);
        (void)_t685;
        ;
        U64 *_t686 = malloc(sizeof(U64)); *_t686 = U64_mul(lo, self->elem_size);
        (void)_t686;
        U64 _t687 = U64_sub(self->count, lo);
        (void)_t687;
        void *_t688 = ptr_add(self->data, DEREF(_t685));
        (void)_t688;
        void *_t689 = ptr_add(self->data, DEREF(_t686));
        (void)_t689;
        U64 _t690 = U64_mul(_t687, self->elem_size);
        (void)_t690;
        ;
        memmove(_t688, _t689, _t690);
        U64_delete(_t685, &(Bool){1});
        U64_delete(_t686, &(Bool){1});
        ;
        U64 *_t691 = malloc(sizeof(U64)); *_t691 = U64_mul(lo, self->elem_size);
        (void)_t691;
        void *_t692 = ptr_add(self->data, DEREF(_t691));
        (void)_t692;
        memcpy(_t692, val, self->elem_size);
        U64_delete(_t691, &(Bool){1});
        free(val);
        U64 _t693 = 1;
        (void)_t693;
        U64 _t694 = U64_add(self->count, _t693);
        (void)_t694;
        ;
        self->count = _t694;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t705; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t705 = *_hp; free(_hp); }
    (void)_t705;
    Bool _t706 = Bool_not(_t705);
    (void)_t706;
    ;
    if (_t706) {
        {
            U64 _t703 = 0;
            (void)_t703;
            Range *_fc695 = Range_new(_t703, self->count);
            (void)_fc695;
            ;
            U64 _fi695 = 0;
            (void)_fi695;
            while (1) {
                U64 _t697; { U64 *_hp = (U64 *)Range_len(_fc695); _t697 = *_hp; free(_hp); }
                (void)_t697;
                Bool _wcond696; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi695}, &(U64){_t697}); _wcond696 = *_hp; free(_hp); }
                (void)_wcond696;
                ;
                if (_wcond696) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc695, _fi695); i = *_hp; free(_hp); }
                (void)i;
                U64 _t698 = 1;
                (void)_t698;
                U64 _t699 = U64_add(_fi695, _t698);
                (void)_t699;
                ;
                _fi695 = _t699;
                ;
                U64 *_t700 = malloc(sizeof(U64)); *_t700 = U64_mul(i, self->elem_size);
                (void)_t700;
                ;
                void *_t701 = ptr_add(self->data, DEREF(_t700));
                (void)_t701;
                Bool _t702 = 0;
                (void)_t702;
                dyn_call_delete(&self->elem_type, _t701, &(Bool){_t702});
                U64_delete(_t700, &(Bool){1});
                ;
            }
            Range_delete(_fc695, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t707; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t707 = *_hp; free(_hp); }
    (void)_t707;
    Bool _t708 = Bool_not(_t707);
    (void)_t708;
    ;
    if (_t708) {
        Bool _t704 = 0;
        (void)_t704;
        Str_delete(&self->elem_type, &(Bool){_t704});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t719 = U64_mul(self->cap, self->elem_size);
    (void)_t719;
    U8 *new_data = malloc(_t719);
    (void)new_data;
    ;
    {
        U64 _t718 = 0;
        (void)_t718;
        Range *_fc709 = Range_new(_t718, self->count);
        (void)_fc709;
        ;
        U64 _fi709 = 0;
        (void)_fi709;
        while (1) {
            U64 _t711; { U64 *_hp = (U64 *)Range_len(_fc709); _t711 = *_hp; free(_hp); }
            (void)_t711;
            Bool _wcond710; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi709}, &(U64){_t711}); _wcond710 = *_hp; free(_hp); }
            (void)_wcond710;
            ;
            if (_wcond710) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc709, _fi709); i = *_hp; free(_hp); }
            (void)i;
            U64 _t712 = 1;
            (void)_t712;
            U64 _t713 = U64_add(_fi709, _t712);
            (void)_t713;
            ;
            _fi709 = _t713;
            ;
            U64 *_t714 = malloc(sizeof(U64)); *_t714 = U64_mul(i, self->elem_size);
            (void)_t714;
            void *_t715 = ptr_add(self->data, DEREF(_t714));
            (void)_t715;
            void *cloned = dyn_call_clone(&self->elem_type, _t715);
            (void)cloned;
            U64_delete(_t714, &(Bool){1});
            U64 *_t716 = malloc(sizeof(U64)); *_t716 = U64_mul(i, self->elem_size);
            (void)_t716;
            ;
            void *_t717 = ptr_add(new_data, DEREF(_t716));
            (void)_t717;
            memcpy(_t717, cloned, self->elem_size);
            U64_delete(_t716, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc709, &(Bool){1});
        ;
    }
    Set *_t720 = malloc(sizeof(Set));
    _t720->data = new_data;
    _t720->count = self->count;
    _t720->cap = self->cap;
    _t720->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t720->elem_type = *_ca; free(_ca); }
    (void)_t720;
    return _t720;
}

U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t728; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t728 = *_hp; free(_hp); }
    (void)_t728;
    if (_t728) {
        Str *_t722 = Str_lit("Str", 3ULL);
        (void)_t722;
        U64 _t723; { U64 *_hp = (U64 *)Str_size(); _t723 = *_hp; free(_hp); }
        (void)_t723;
        U64 _t724 = 1;
        (void)_t724;
        Array *_va15 = Array_new(_t722, &(U64){_t723}, &(U64){_t724});
        (void)_va15;
        Str_delete(_t722, &(Bool){1});
        ;
        ;
        U64 _t725 = 0;
        (void)_t725;
        Str *_t726 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t726;
        Array_set(_va15, &(U64){_t725}, _t726);
        ;
        Str *_t727 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t727;
        panic(_t727, _va15);
        Str_delete(_t727, &(Bool){1});
    }
    ;
    void *_t729 = ptr_add(self->c_str, DEREF(i));
    (void)_t729;
    return _t729;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t730 = ptr_add(self->c_str, DEREF(i));
    (void)_t730;
    return _t730;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t739; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t739 = *_hp; free(_hp); }
    (void)_t739;
    if (_t739) {
        min_len = b->count;
    }
    ;
    {
        U64 _t738 = 0;
        (void)_t738;
        Range *_fc731 = Range_new(_t738, min_len);
        (void)_fc731;
        ;
        U64 _fi731 = 0;
        (void)_fi731;
        while (1) {
            U64 _t733; { U64 *_hp = (U64 *)Range_len(_fc731); _t733 = *_hp; free(_hp); }
            (void)_t733;
            Bool _wcond732; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi731}, &(U64){_t733}); _wcond732 = *_hp; free(_hp); }
            (void)_wcond732;
            ;
            if (_wcond732) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc731, _fi731);
            (void)i;
            U64 _t734 = 1;
            (void)_t734;
            U64 _t735 = U64_add(_fi731, _t734);
            (void)_t735;
            ;
            _fi731 = _t735;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t736 = 0;
            (void)_t736;
            Bool _t737; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t736}); _t737 = *_hp; free(_hp); }
            (void)_t737;
            ;
            if (_t737) {
                ;
                Range_delete(_fc731, &(Bool){1});
                ;
                return c;
            }
            ;
            I64_delete(c, &(Bool){1});
        }
        Range_delete(_fc731, &(Bool){1});
        ;
    }
    ;
    I64 _t740 = U64_cmp(a->count, b->count);
    (void)_t740;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t740; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t741 = 1;
    (void)_t741;
    U64 _t742 = U64_add(DEREF(new_len), _t741);
    (void)_t742;
    ;
    U8 *new_data = malloc(_t742);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t743 = ptr_add(new_data, a->count);
    (void)_t743;
    memcpy(_t743, b->c_str, b->count);
    void *_t744 = ptr_add(new_data, DEREF(new_len));
    (void)_t744;
    I32 _t745 = 0;
    (void)_t745;
    U64 _t746 = 1;
    (void)_t746;
    memset(_t744, _t745, _t746);
    ;
    ;
    U64 _t747 = U64_clone(new_len);
    (void)_t747;
    U64 _t748 = U64_clone(new_len);
    (void)_t748;
    U64_delete(new_len, &(Bool){1});
    Str *_t749 = malloc(sizeof(Str));
    _t749->c_str = new_data;
    _t749->count = _t747;
    _t749->cap = _t748;
    (void)_t749;
    ;
    ;
    return _t749;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t750 = 1;
    (void)_t750;
    U64 _t751 = U64_add(DEREF(n), _t750);
    (void)_t751;
    ;
    U8 *buf = malloc(_t751);
    (void)buf;
    ;
    I32 _t752 = 0;
    (void)_t752;
    U64 _t753 = 1;
    (void)_t753;
    memset(buf, _t752, _t753);
    ;
    ;
    I64 _t754 = 0;
    (void)_t754;
    U64 _t755 = U64_clone(n);
    (void)_t755;
    Str *_t756 = malloc(sizeof(Str));
    _t756->c_str = buf;
    _t756->count = _t754;
    _t756->cap = _t755;
    (void)_t756;
    ;
    ;
    return _t756;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t769; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t769 = *_hp; free(_hp); }
    (void)_t769;
    if (_t769) {
        Str *_t757 = Str_lit("Str", 3ULL);
        (void)_t757;
        U64 _t758; { U64 *_hp = (U64 *)Str_size(); _t758 = *_hp; free(_hp); }
        (void)_t758;
        U64 _t759 = 1;
        (void)_t759;
        Array *_va16 = Array_new(_t757, &(U64){_t758}, &(U64){_t759});
        (void)_va16;
        Str_delete(_t757, &(Bool){1});
        ;
        ;
        U64 _t760 = 0;
        (void)_t760;
        Str *_t761 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t761;
        Array_set(_va16, &(U64){_t760}, _t761);
        ;
        Str *_t762 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t762;
        panic(_t762, _va16);
        Str_delete(_t762, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t770; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t770 = *_hp; free(_hp); }
    (void)_t770;
    if (_t770) {
        Str *_t763 = Str_lit("Str", 3ULL);
        (void)_t763;
        U64 _t764; { U64 *_hp = (U64 *)Str_size(); _t764 = *_hp; free(_hp); }
        (void)_t764;
        U64 _t765 = 1;
        (void)_t765;
        Array *_va17 = Array_new(_t763, &(U64){_t764}, &(U64){_t765});
        (void)_va17;
        Str_delete(_t763, &(Bool){1});
        ;
        ;
        U64 _t766 = 0;
        (void)_t766;
        Str *_t767 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t767;
        Array_set(_va17, &(U64){_t766}, _t767);
        ;
        Str *_t768 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t768;
        panic(_t768, _va17);
        Str_delete(_t768, &(Bool){1});
    }
    ;
    void *_t771 = ptr_add(self->c_str, self->count);
    (void)_t771;
    memcpy(_t771, s->c_str, s->count);
    U64 _t772 = U64_clone(new_len);
    (void)_t772;
    self->count = _t772;
    ;
    void *_t773 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t773;
    I32 _t774 = 0;
    (void)_t774;
    U64 _t775 = 1;
    (void)_t775;
    memset(_t773, _t774, _t775);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t776 = 1;
    (void)_t776;
    U64 _t777 = U64_add(val->count, _t776);
    (void)_t777;
    ;
    U8 *new_data = malloc(_t777);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t778 = ptr_add(new_data, val->count);
    (void)_t778;
    I32 _t779 = 0;
    (void)_t779;
    U64 _t780 = 1;
    (void)_t780;
    memset(_t778, _t779, _t780);
    ;
    ;
    Str *_t781 = malloc(sizeof(Str));
    _t781->c_str = new_data;
    _t781->count = val->count;
    _t781->cap = val->count;
    (void)_t781;
    return _t781;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t782; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t782 = *_hp; free(_hp); }
    (void)_t782;
    if (_t782) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t783 = Str_clone(val);
    (void)_t783;
    return _t783;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t785; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t785 = *_hp; free(_hp); }
    (void)_t785;
    if (_t785) {
        *st = s->count;
    }
    ;
    U64 _t786 = U64_add(DEREF(st), ln);
    (void)_t786;
    Bool _t787; { Bool *_hp = (Bool *)U64_gt(&(U64){_t786}, &s->count); _t787 = *_hp; free(_hp); }
    (void)_t787;
    ;
    if (_t787) {
        U64 _t784 = U64_sub(s->count, DEREF(st));
        (void)_t784;
        ln = _t784;
        ;
    }
    ;
    void *_t788 = ptr_add(s->c_str, DEREF(st));
    (void)_t788;
    U64 _t789 = U64_clone(&(U64){ln});
    (void)_t789;
    ;
    U64 _t790 = U64_clone(CAP_VIEW);
    (void)_t790;
    Str *_t791 = malloc(sizeof(Str));
    _t791->c_str = _t788;
    _t791->count = _t789;
    _t791->cap = _t790;
    (void)_t791;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t791;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t813 = 0;
    (void)_t813;
    Bool _t814 = U64_eq(b->count, _t813);
    (void)_t814;
    ;
    if (_t814) {
        Bool _t792 = 1;
        (void)_t792;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t792; return _r; }
    }
    ;
    Bool _t815; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t815 = *_hp; free(_hp); }
    (void)_t815;
    if (_t815) {
        Bool _t793 = 0;
        (void)_t793;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t793; return _r; }
    }
    ;
    {
        U64 _t809 = U64_sub(a->count, b->count);
        (void)_t809;
        U64 _t810 = 1;
        (void)_t810;
        U64 _t811 = 0;
        (void)_t811;
        U64 _t812 = U64_add(_t809, _t810);
        (void)_t812;
        ;
        ;
        Range *_fc794 = Range_new(_t811, _t812);
        (void)_fc794;
        ;
        ;
        U64 _fi794 = 0;
        (void)_fi794;
        while (1) {
            U64 _t806; { U64 *_hp = (U64 *)Range_len(_fc794); _t806 = *_hp; free(_hp); }
            (void)_t806;
            Bool _wcond795; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi794}, &(U64){_t806}); _wcond795 = *_hp; free(_hp); }
            (void)_wcond795;
            ;
            if (_wcond795) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc794, _fi794); i = *_hp; free(_hp); }
            (void)i;
            U64 _t807 = 1;
            (void)_t807;
            U64 _t808 = U64_add(_fi794, _t807);
            (void)_t808;
            ;
            _fi794 = _t808;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t804 = 0;
                (void)_t804;
                Range *_fc796 = Range_new(_t804, b->count);
                (void)_fc796;
                ;
                U64 _fi796 = 0;
                (void)_fi796;
                while (1) {
                    U64 _t799; { U64 *_hp = (U64 *)Range_len(_fc796); _t799 = *_hp; free(_hp); }
                    (void)_t799;
                    Bool _wcond797; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi796}, &(U64){_t799}); _wcond797 = *_hp; free(_hp); }
                    (void)_wcond797;
                    ;
                    if (_wcond797) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc796, _fi796);
                    (void)j;
                    U64 _t800 = 1;
                    (void)_t800;
                    U64 _t801 = U64_add(_fi796, _t800);
                    (void)_t801;
                    ;
                    _fi796 = _t801;
                    ;
                    U64 *_t802 = malloc(sizeof(U64)); *_t802 = U64_add(i, DEREF(j));
                    (void)_t802;
                    U8 *ac = Str_get(a, _t802);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t803; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t803 = *_hp; free(_hp); }
                    (void)_t803;
                    U64_delete(_t802, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t803) {
                        Bool _t798 = 0;
                        (void)_t798;
                        found = _t798;
                        ;
                    }
                    ;
                }
                Range_delete(_fc796, &(Bool){1});
                ;
            }
            ;
            if (found) {
                Bool _t805 = 1;
                (void)_t805;
                ;
                Range_delete(_fc794, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t805; return _r; }
            }
            ;
        }
        Range_delete(_fc794, &(Bool){1});
        ;
    }
    Bool _t816 = 0;
    (void)_t816;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t816; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t826; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t826 = *_hp; free(_hp); }
    (void)_t826;
    if (_t826) {
        Bool _t817 = 0;
        (void)_t817;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t817; return _r; }
    }
    ;
    {
        U64 _t825 = 0;
        (void)_t825;
        Range *_fc818 = Range_new(_t825, b->count);
        (void)_fc818;
        ;
        U64 _fi818 = 0;
        (void)_fi818;
        while (1) {
            U64 _t821; { U64 *_hp = (U64 *)Range_len(_fc818); _t821 = *_hp; free(_hp); }
            (void)_t821;
            Bool _wcond819; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi818}, &(U64){_t821}); _wcond819 = *_hp; free(_hp); }
            (void)_wcond819;
            ;
            if (_wcond819) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc818, _fi818);
            (void)i;
            U64 _t822 = 1;
            (void)_t822;
            U64 _t823 = U64_add(_fi818, _t822);
            (void)_t823;
            ;
            _fi818 = _t823;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t824; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t824 = *_hp; free(_hp); }
            (void)_t824;
            U64_delete(i, &(Bool){1});
            if (_t824) {
                Bool _t820 = 0;
                (void)_t820;
                ;
                Range_delete(_fc818, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t820; return _r; }
            }
            ;
        }
        Range_delete(_fc818, &(Bool){1});
        ;
    }
    Bool _t827 = 1;
    (void)_t827;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t827; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t838; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t838 = *_hp; free(_hp); }
    (void)_t838;
    if (_t838) {
        Bool _t828 = 0;
        (void)_t828;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t828; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _t837 = 0;
        (void)_t837;
        Range *_fc829 = Range_new(_t837, b->count);
        (void)_fc829;
        ;
        U64 _fi829 = 0;
        (void)_fi829;
        while (1) {
            U64 _t832; { U64 *_hp = (U64 *)Range_len(_fc829); _t832 = *_hp; free(_hp); }
            (void)_t832;
            Bool _wcond830; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi829}, &(U64){_t832}); _wcond830 = *_hp; free(_hp); }
            (void)_wcond830;
            ;
            if (_wcond830) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc829, _fi829);
            (void)i;
            U64 _t833 = 1;
            (void)_t833;
            U64 _t834 = U64_add(_fi829, _t833);
            (void)_t834;
            ;
            _fi829 = _t834;
            ;
            U64 *_t835 = malloc(sizeof(U64)); *_t835 = U64_add(offset, DEREF(i));
            (void)_t835;
            U8 *ac = Str_get(a, _t835);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t836; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t836 = *_hp; free(_hp); }
            (void)_t836;
            U64_delete(_t835, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t836) {
                Bool _t831 = 0;
                (void)_t831;
                ;
                Range_delete(_fc829, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t831; return _r; }
            }
            ;
        }
        Range_delete(_fc829, &(Bool){1});
        ;
    }
    ;
    Bool _t839 = 1;
    (void)_t839;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t839; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t840 = 0;
    (void)_t840;
    Bool _t841 = U64_eq(self->count, _t840);
    (void)_t841;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t841; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t867 = 0;
    (void)_t867;
    Bool _t868 = U64_eq(needle->count, _t867);
    (void)_t868;
    ;
    if (_t868) {
        I64 _t842 = 0;
        (void)_t842;
        I64 _t843 = 1;
        (void)_t843;
        I64 _t844 = I64_sub(_t842, _t843);
        (void)_t844;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t844; return _r; }
    }
    ;
    Bool _t869; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t869 = *_hp; free(_hp); }
    (void)_t869;
    if (_t869) {
        I64 _t845 = 0;
        (void)_t845;
        I64 _t846 = 1;
        (void)_t846;
        I64 _t847 = I64_sub(_t845, _t846);
        (void)_t847;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t847; return _r; }
    }
    ;
    {
        U64 _t863 = U64_sub(self->count, needle->count);
        (void)_t863;
        U64 _t864 = 1;
        (void)_t864;
        U64 _t865 = 0;
        (void)_t865;
        U64 _t866 = U64_add(_t863, _t864);
        (void)_t866;
        ;
        ;
        Range *_fc848 = Range_new(_t865, _t866);
        (void)_fc848;
        ;
        ;
        U64 _fi848 = 0;
        (void)_fi848;
        while (1) {
            U64 _t860; { U64 *_hp = (U64 *)Range_len(_fc848); _t860 = *_hp; free(_hp); }
            (void)_t860;
            Bool _wcond849; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi848}, &(U64){_t860}); _wcond849 = *_hp; free(_hp); }
            (void)_wcond849;
            ;
            if (_wcond849) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc848, _fi848); i = *_hp; free(_hp); }
            (void)i;
            U64 _t861 = 1;
            (void)_t861;
            U64 _t862 = U64_add(_fi848, _t861);
            (void)_t862;
            ;
            _fi848 = _t862;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t858 = 0;
                (void)_t858;
                Range *_fc850 = Range_new(_t858, needle->count);
                (void)_fc850;
                ;
                U64 _fi850 = 0;
                (void)_fi850;
                while (1) {
                    U64 _t853; { U64 *_hp = (U64 *)Range_len(_fc850); _t853 = *_hp; free(_hp); }
                    (void)_t853;
                    Bool _wcond851; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi850}, &(U64){_t853}); _wcond851 = *_hp; free(_hp); }
                    (void)_wcond851;
                    ;
                    if (_wcond851) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc850, _fi850);
                    (void)j;
                    U64 _t854 = 1;
                    (void)_t854;
                    U64 _t855 = U64_add(_fi850, _t854);
                    (void)_t855;
                    ;
                    _fi850 = _t855;
                    ;
                    U64 *_t856 = malloc(sizeof(U64)); *_t856 = U64_add(i, DEREF(j));
                    (void)_t856;
                    U8 *ac = Str_get(self, _t856);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t857; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t857 = *_hp; free(_hp); }
                    (void)_t857;
                    U64_delete(_t856, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t857) {
                        Bool _t852 = 0;
                        (void)_t852;
                        found = _t852;
                        ;
                    }
                    ;
                }
                Range_delete(_fc850, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t859 = U64_to_i64(i);
                (void)_t859;
                ;
                ;
                Range_delete(_fc848, &(Bool){1});
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t859; return _r; }
            }
            ;
            ;
        }
        Range_delete(_fc848, &(Bool){1});
        ;
    }
    I64 _t870 = 0;
    (void)_t870;
    I64 _t871 = 1;
    (void)_t871;
    I64 _t872 = I64_sub(_t870, _t871);
    (void)_t872;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t872; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t898 = 0;
    (void)_t898;
    Bool _t899 = U64_eq(needle->count, _t898);
    (void)_t899;
    ;
    if (_t899) {
        I64 _t873 = 0;
        (void)_t873;
        I64 _t874 = 1;
        (void)_t874;
        I64 _t875 = I64_sub(_t873, _t874);
        (void)_t875;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t875; return _r; }
    }
    ;
    Bool _t900; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t900 = *_hp; free(_hp); }
    (void)_t900;
    if (_t900) {
        I64 _t876 = 0;
        (void)_t876;
        I64 _t877 = 1;
        (void)_t877;
        I64 _t878 = I64_sub(_t876, _t877);
        (void)_t878;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t878; return _r; }
    }
    ;
    I64 _t901 = 0;
    (void)_t901;
    I64 _t902 = 1;
    (void)_t902;
    I64 last = I64_sub(_t901, _t902);
    (void)last;
    ;
    ;
    {
        U64 _t894 = U64_sub(self->count, needle->count);
        (void)_t894;
        U64 _t895 = 1;
        (void)_t895;
        U64 _t896 = 0;
        (void)_t896;
        U64 _t897 = U64_add(_t894, _t895);
        (void)_t897;
        ;
        ;
        Range *_fc879 = Range_new(_t896, _t897);
        (void)_fc879;
        ;
        ;
        U64 _fi879 = 0;
        (void)_fi879;
        while (1) {
            U64 _t891; { U64 *_hp = (U64 *)Range_len(_fc879); _t891 = *_hp; free(_hp); }
            (void)_t891;
            Bool _wcond880; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi879}, &(U64){_t891}); _wcond880 = *_hp; free(_hp); }
            (void)_wcond880;
            ;
            if (_wcond880) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc879, _fi879); i = *_hp; free(_hp); }
            (void)i;
            U64 _t892 = 1;
            (void)_t892;
            U64 _t893 = U64_add(_fi879, _t892);
            (void)_t893;
            ;
            _fi879 = _t893;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t889 = 0;
                (void)_t889;
                Range *_fc881 = Range_new(_t889, needle->count);
                (void)_fc881;
                ;
                U64 _fi881 = 0;
                (void)_fi881;
                while (1) {
                    U64 _t884; { U64 *_hp = (U64 *)Range_len(_fc881); _t884 = *_hp; free(_hp); }
                    (void)_t884;
                    Bool _wcond882; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi881}, &(U64){_t884}); _wcond882 = *_hp; free(_hp); }
                    (void)_wcond882;
                    ;
                    if (_wcond882) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc881, _fi881);
                    (void)j;
                    U64 _t885 = 1;
                    (void)_t885;
                    U64 _t886 = U64_add(_fi881, _t885);
                    (void)_t886;
                    ;
                    _fi881 = _t886;
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
                        Bool _t883 = 0;
                        (void)_t883;
                        found = _t883;
                        ;
                    }
                    ;
                }
                Range_delete(_fc881, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t890 = U64_to_i64(i);
                (void)_t890;
                last = _t890;
                ;
            }
            ;
            ;
        }
        Range_delete(_fc879, &(Bool){1});
        ;
    }
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t918 = 0;
    (void)_t918;
    Bool _t919 = U64_eq(from->count, _t918);
    (void)_t919;
    ;
    if (_t919) {
        Str *_t903 = Str_clone(self);
        (void)_t903;
        ;
        return _t903;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t905 = U64_sub(self->count, from->count);
        (void)_t905;
        Bool _wcond904; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t905}); _wcond904 = *_hp; free(_hp); }
        (void)_wcond904;
        ;
        if (_wcond904) {
        } else {
            ;
            break;
        }
        ;
        U64 _t906 = U64_sub(self->count, start);
        (void)_t906;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t906});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t907 = 0;
        (void)_t907;
        I64 _t908 = 1;
        (void)_t908;
        I64 _t909 = I64_sub(_t907, _t908);
        (void)_t909;
        ;
        ;
        Bool _t910 = I64_eq(pos, _t909);
        (void)_t910;
        ;
        if (_t910) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t911 = I64_to_u64(pos);
        (void)_t911;
        Str *_t912 = Str_substr(self, &(U64){start}, &(U64){_t911});
        (void)_t912;
        ;
        result = Str_concat(result, _t912);
        Str_delete(_t912, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t913 = I64_to_u64(pos);
        (void)_t913;
        ;
        U64 _t914 = U64_add(start, _t913);
        (void)_t914;
        ;
        U64 _t915 = U64_add(_t914, from->count);
        (void)_t915;
        ;
        start = _t915;
        ;
    }
    Bool _t920; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t920 = *_hp; free(_hp); }
    (void)_t920;
    if (_t920) {
        U64 _t916 = U64_sub(self->count, start);
        (void)_t916;
        Str *_t917 = Str_substr(self, &(U64){start}, &(U64){_t916});
        (void)_t917;
        ;
        result = Str_concat(result, _t917);
        Str_delete(_t917, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t921 = 1;
    (void)_t921;
    Str *_t922 = Str_substr(self, i, &(U64){_t921});
    (void)_t922;
    ;
    return _t922;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t925; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t925 = *_hp; free(_hp); }
    (void)_t925;
    if (_t925) {
        U64 _t923 = U64_sub(self->count, prefix->count);
        (void)_t923;
        Str *_t924 = Str_substr(self, &prefix->count, &(U64){_t923});
        (void)_t924;
        ;
        ;
        return _t924;
    }
    ;
    Str *_t926 = Str_clone(self);
    (void)_t926;
    return _t926;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t930; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t930 = *_hp; free(_hp); }
    (void)_t930;
    if (_t930) {
        U64 _t927 = 0;
        (void)_t927;
        U64 _t928 = U64_sub(self->count, suffix->count);
        (void)_t928;
        Str *_t929 = Str_substr(self, &(U64){_t927}, &(U64){_t928});
        (void)_t929;
        ;
        ;
        ;
        return _t929;
    }
    ;
    Str *_t931 = Str_clone(self);
    (void)_t931;
    return _t931;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t932 = 2;
    (void)_t932;
    U8 *buf = malloc(_t932);
    (void)buf;
    ;
    U64 _t933 = 1;
    (void)_t933;
    memcpy(buf, byte, _t933);
    ;
    U64 *_t934 = malloc(sizeof(U64));
    *_t934 = 1;
    (void)_t934;
    void *_t935 = ptr_add(buf, DEREF(_t934));
    (void)_t935;
    I32 _t936 = 0;
    (void)_t936;
    U64 _t937 = 1;
    (void)_t937;
    memset(_t935, _t936, _t937);
    U64_delete(_t934, &(Bool){1});
    ;
    ;
    I64 _t938 = 1;
    (void)_t938;
    I64 _t939 = 1;
    (void)_t939;
    Str *_t940 = malloc(sizeof(Str));
    _t940->c_str = buf;
    _t940->count = _t938;
    _t940->cap = _t939;
    (void)_t940;
    ;
    ;
    return _t940;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t982 = 0;
    (void)_t982;
    Bool _t983 = U64_eq(self->count, _t982);
    (void)_t983;
    ;
    if (_t983) {
        Str *_t941 = Str_lit("Str", 3ULL);
        (void)_t941;
        U64 _t942; { U64 *_hp = (U64 *)Str_size(); _t942 = *_hp; free(_hp); }
        (void)_t942;
        U64 _t943 = 1;
        (void)_t943;
        Array *_va18 = Array_new(_t941, &(U64){_t942}, &(U64){_t943});
        (void)_va18;
        Str_delete(_t941, &(Bool){1});
        ;
        ;
        U64 _t944 = 0;
        (void)_t944;
        Str *_t945 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t945;
        Array_set(_va18, &(U64){_t944}, _t945);
        ;
        Str *_t946 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t946;
        panic(_t946, _va18);
        Str_delete(_t946, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t984 = malloc(sizeof(U64));
    *_t984 = 0;
    (void)_t984;
    U8 *first = Str_get(self, _t984);
    (void)first;
    U8 _t985 = 45;
    (void)_t985;
    Bool _t986 = U8_eq(DEREF(first), _t985);
    (void)_t986;
    U64_delete(_t984, &(Bool){1});
    ;
    if (_t986) {
        Bool _t947 = 1;
        (void)_t947;
        neg = _t947;
        ;
        U64 _t948 = 1;
        (void)_t948;
        start = _t948;
        ;
    }
    ;
    Bool _t987 = U64_eq(start, self->count);
    (void)_t987;
    if (_t987) {
        Str *_t949 = Str_lit("Str", 3ULL);
        (void)_t949;
        U64 _t950; { U64 *_hp = (U64 *)Str_size(); _t950 = *_hp; free(_hp); }
        (void)_t950;
        U64 _t951 = 1;
        (void)_t951;
        Array *_va19 = Array_new(_t949, &(U64){_t950}, &(U64){_t951});
        (void)_va19;
        Str_delete(_t949, &(Bool){1});
        ;
        ;
        U64 _t952 = 0;
        (void)_t952;
        Str *_t953 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t953;
        Array_set(_va19, &(U64){_t952}, _t953);
        ;
        Str *_t954 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t954;
        panic(_t954, _va19);
        Str_delete(_t954, &(Bool){1});
    }
    ;
    {
        Range *_fc955 = Range_new(start, self->count);
        (void)_fc955;
        U64 _fi955 = 0;
        (void)_fi955;
        while (1) {
            U64 _t967; { U64 *_hp = (U64 *)Range_len(_fc955); _t967 = *_hp; free(_hp); }
            (void)_t967;
            Bool _wcond956; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi955}, &(U64){_t967}); _wcond956 = *_hp; free(_hp); }
            (void)_wcond956;
            ;
            if (_wcond956) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc955, _fi955);
            (void)i;
            U64 _t968 = 1;
            (void)_t968;
            U64 _t969 = U64_add(_fi955, _t968);
            (void)_t969;
            ;
            _fi955 = _t969;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t970 = U8_to_i64(DEREF(ch));
            (void)_t970;
            U64_delete(i, &(Bool){1});
            I64 _t971 = 48;
            (void)_t971;
            I64 d = I64_sub(_t970, _t971);
            (void)d;
            ;
            ;
            I64 _t972 = 0;
            (void)_t972;
            I64 _t973 = 9;
            (void)_t973;
            Bool _t974; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t972}); _t974 = *_hp; free(_hp); }
            (void)_t974;
            ;
            Bool _t975; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t973}); _t975 = *_hp; free(_hp); }
            (void)_t975;
            ;
            Bool _t976 = Bool_or(_t974, _t975);
            (void)_t976;
            ;
            ;
            if (_t976) {
                Str *_t957 = Str_lit("Str", 3ULL);
                (void)_t957;
                U64 _t958; { U64 *_hp = (U64 *)Str_size(); _t958 = *_hp; free(_hp); }
                (void)_t958;
                U64 _t959 = 3;
                (void)_t959;
                Array *_va20 = Array_new(_t957, &(U64){_t958}, &(U64){_t959});
                (void)_va20;
                Str_delete(_t957, &(Bool){1});
                ;
                ;
                U64 _t960 = 0;
                (void)_t960;
                Str *_t961 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t961;
                Array_set(_va20, &(U64){_t960}, _t961);
                ;
                U64 _t962 = 1;
                (void)_t962;
                Str *_t963 = Str_clone(self);
                (void)_t963;
                Array_set(_va20, &(U64){_t962}, _t963);
                ;
                U64 _t964 = 2;
                (void)_t964;
                Str *_t965 = Str_lit("'", 1ULL);
                (void)_t965;
                Array_set(_va20, &(U64){_t964}, _t965);
                ;
                Str *_t966 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t966;
                panic(_t966, _va20);
                Str_delete(_t966, &(Bool){1});
            }
            ;
            I64 _t977 = 10;
            (void)_t977;
            I64 _t978 = I64_mul(result, _t977);
            (void)_t978;
            ;
            I64 _t979 = I64_add(_t978, d);
            (void)_t979;
            ;
            ;
            result = _t979;
            ;
        }
        Range_delete(_fc955, &(Bool){1});
        ;
    }
    ;
    if (neg) {
        I64 _t980 = 0;
        (void)_t980;
        I64 _t981 = I64_sub(_t980, result);
        (void)_t981;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t981; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t1004 = Str_lit("Str", 3ULL);
    (void)_t1004;
    U64 _t1005; { U64 *_hp = (U64 *)Str_size(); _t1005 = *_hp; free(_hp); }
    (void)_t1005;
    Vec *parts = Vec_new(_t1004, &(U64){_t1005});
    (void)parts;
    Str_delete(_t1004, &(Bool){1});
    ;
    U64 _t1006; { U64 *_hp = (U64 *)Str_len(delim); _t1006 = *_hp; free(_hp); }
    (void)_t1006;
    U64 _t1007 = 0;
    (void)_t1007;
    Bool _t1008 = U64_eq(_t1006, _t1007);
    (void)_t1008;
    ;
    ;
    if (_t1008) {
        Str *_t988 = Str_clone(self);
        (void)_t988;
        Vec_push(parts, _t988);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t998; { U64 *_hp = (U64 *)Str_len(self); _t998 = *_hp; free(_hp); }
        (void)_t998;
        U64 _t999; { U64 *_hp = (U64 *)Str_len(delim); _t999 = *_hp; free(_hp); }
        (void)_t999;
        U64 _t1000 = U64_sub(_t998, _t999);
        (void)_t1000;
        ;
        ;
        Bool _wcond989; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1000}); _wcond989 = *_hp; free(_hp); }
        (void)_wcond989;
        ;
        if (_wcond989) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1001; { U64 *_hp = (U64 *)Str_len(delim); _t1001 = *_hp; free(_hp); }
        (void)_t1001;
        Str *_t1002 = Str_substr(self, &(U64){pos}, &(U64){_t1001});
        (void)_t1002;
        ;
        Bool _t1003; { Bool *_hp = (Bool *)Str_eq(_t1002, delim); _t1003 = *_hp; free(_hp); }
        (void)_t1003;
        Str_delete(_t1002, &(Bool){1});
        if (_t1003) {
            U64 _t990 = U64_sub(pos, start);
            (void)_t990;
            Str *_t991 = Str_substr(self, &(U64){start}, &(U64){_t990});
            (void)_t991;
            ;
            Str *_t992 = Str_clone(_t991);
            (void)_t992;
            Str_delete(_t991, &(Bool){1});
            Vec_push(parts, _t992);
            U64 _t993; { U64 *_hp = (U64 *)Str_len(delim); _t993 = *_hp; free(_hp); }
            (void)_t993;
            U64 _t994 = U64_add(pos, _t993);
            (void)_t994;
            ;
            start = _t994;
            ;
            U64 _t995 = U64_clone(&(U64){start});
            (void)_t995;
            pos = _t995;
            ;
        } else {
            U64 _t996 = 1;
            (void)_t996;
            U64 _t997 = U64_add(pos, _t996);
            (void)_t997;
            ;
            pos = _t997;
            ;
        }
        ;
    }
    ;
    U64 _t1009; { U64 *_hp = (U64 *)Str_len(self); _t1009 = *_hp; free(_hp); }
    (void)_t1009;
    U64 _t1010 = U64_sub(_t1009, start);
    (void)_t1010;
    ;
    Str *_t1011 = Str_substr(self, &(U64){start}, &(U64){_t1010});
    (void)_t1011;
    ;
    ;
    Str *_t1012 = Str_clone(_t1011);
    (void)_t1012;
    Str_delete(_t1011, &(Bool){1});
    Vec_push(parts, _t1012);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1044 = malloc(DEREF(elem_size));
    (void)_t1044;
    U64 _t1045 = 0;
    (void)_t1045;
    I64 _t1046 = 1;
    (void)_t1046;
    U64 _t1047 = U64_clone(elem_size);
    (void)_t1047;
    Vec *_t1048 = malloc(sizeof(Vec));
    _t1048->data = _t1044;
    _t1048->count = _t1045;
    _t1048->cap = _t1046;
    _t1048->elem_size = _t1047;
    { Str *_ca = Str_clone(elem_type); _t1048->elem_type = *_ca; free(_ca); }
    (void)_t1048;
    ;
    ;
    ;
    return _t1048;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1053 = U64_eq(self->count, self->cap);
    (void)_t1053;
    if (_t1053) {
        U64 _t1049 = 2;
        (void)_t1049;
        U64 new_cap = U64_mul(self->cap, _t1049);
        (void)new_cap;
        ;
        U64 _t1050 = U64_mul(new_cap, self->elem_size);
        (void)_t1050;
        void *_t1051 = realloc(self->data, _t1050);
        (void)_t1051;
        ;
        self->data = _t1051;
        U64 _t1052 = U64_clone(&(U64){new_cap});
        (void)_t1052;
        ;
        self->cap = _t1052;
        ;
    }
    ;
    U64 *_t1054 = malloc(sizeof(U64)); *_t1054 = U64_mul(self->count, self->elem_size);
    (void)_t1054;
    void *_t1055 = ptr_add(self->data, DEREF(_t1054));
    (void)_t1055;
    memcpy(_t1055, val, self->elem_size);
    U64_delete(_t1054, &(Bool){1});
    free(val);
    U64 _t1056 = 1;
    (void)_t1056;
    U64 _t1057 = U64_add(self->count, _t1056);
    (void)_t1057;
    ;
    self->count = _t1057;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1072; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1072 = *_hp; free(_hp); }
    (void)_t1072;
    if (_t1072) {
        Str *_t1058 = Str_lit("Str", 3ULL);
        (void)_t1058;
        U64 _t1059; { U64 *_hp = (U64 *)Str_size(); _t1059 = *_hp; free(_hp); }
        (void)_t1059;
        U64 _t1060 = 5;
        (void)_t1060;
        Array *_va21 = Array_new(_t1058, &(U64){_t1059}, &(U64){_t1060});
        (void)_va21;
        Str_delete(_t1058, &(Bool){1});
        ;
        ;
        U64 _t1061 = 0;
        (void)_t1061;
        Str *_t1062 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1062;
        Array_set(_va21, &(U64){_t1061}, _t1062);
        ;
        U64 _t1063 = 1;
        (void)_t1063;
        Str *_t1064 = U64_to_str(DEREF(i));
        (void)_t1064;
        Array_set(_va21, &(U64){_t1063}, _t1064);
        ;
        U64 _t1065 = 2;
        (void)_t1065;
        Str *_t1066 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1066;
        Array_set(_va21, &(U64){_t1065}, _t1066);
        ;
        U64 _t1067 = 3;
        (void)_t1067;
        Str *_t1068 = U64_to_str(self->count);
        (void)_t1068;
        Array_set(_va21, &(U64){_t1067}, _t1068);
        ;
        U64 _t1069 = 4;
        (void)_t1069;
        Str *_t1070 = Str_lit(")", 1ULL);
        (void)_t1070;
        Array_set(_va21, &(U64){_t1069}, _t1070);
        ;
        Str *_t1071 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1071;
        panic(_t1071, _va21);
        Str_delete(_t1071, &(Bool){1});
    }
    ;
    U64 *_t1073 = malloc(sizeof(U64)); *_t1073 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1073;
    void *_t1074 = ptr_add(self->data, DEREF(_t1073));
    (void)_t1074;
    U64_delete(_t1073, &(Bool){1});
    return _t1074;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1085; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1085 = *_hp; free(_hp); }
    (void)_t1085;
    Bool _t1086 = Bool_not(_t1085);
    (void)_t1086;
    ;
    if (_t1086) {
        {
            U64 _t1083 = 0;
            (void)_t1083;
            Range *_fc1075 = Range_new(_t1083, self->count);
            (void)_fc1075;
            ;
            U64 _fi1075 = 0;
            (void)_fi1075;
            while (1) {
                U64 _t1077; { U64 *_hp = (U64 *)Range_len(_fc1075); _t1077 = *_hp; free(_hp); }
                (void)_t1077;
                Bool _wcond1076; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1075}, &(U64){_t1077}); _wcond1076 = *_hp; free(_hp); }
                (void)_wcond1076;
                ;
                if (_wcond1076) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1075, _fi1075); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1078 = 1;
                (void)_t1078;
                U64 _t1079 = U64_add(_fi1075, _t1078);
                (void)_t1079;
                ;
                _fi1075 = _t1079;
                ;
                U64 *_t1080 = malloc(sizeof(U64)); *_t1080 = U64_mul(i, self->elem_size);
                (void)_t1080;
                ;
                void *_t1081 = ptr_add(self->data, DEREF(_t1080));
                (void)_t1081;
                Bool _t1082 = 0;
                (void)_t1082;
                dyn_call_delete(&self->elem_type, _t1081, &(Bool){_t1082});
                U64_delete(_t1080, &(Bool){1});
                ;
            }
            Range_delete(_fc1075, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1087; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1087 = *_hp; free(_hp); }
    (void)_t1087;
    Bool _t1088 = Bool_not(_t1087);
    (void)_t1088;
    ;
    if (_t1088) {
        Bool _t1084 = 0;
        (void)_t1084;
        Str_delete(&self->elem_type, &(Bool){_t1084});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1100 = U64_mul(self->cap, self->elem_size);
    (void)_t1100;
    U8 *new_data = malloc(_t1100);
    (void)new_data;
    ;
    Bool _t1101; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1101 = *_hp; free(_hp); }
    (void)_t1101;
    Bool _t1102 = Bool_not(_t1101);
    (void)_t1102;
    ;
    if (_t1102) {
        {
            U64 _t1098 = 0;
            (void)_t1098;
            Range *_fc1089 = Range_new(_t1098, self->count);
            (void)_fc1089;
            ;
            U64 _fi1089 = 0;
            (void)_fi1089;
            while (1) {
                U64 _t1091; { U64 *_hp = (U64 *)Range_len(_fc1089); _t1091 = *_hp; free(_hp); }
                (void)_t1091;
                Bool _wcond1090; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1089}, &(U64){_t1091}); _wcond1090 = *_hp; free(_hp); }
                (void)_wcond1090;
                ;
                if (_wcond1090) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1089, _fi1089); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1092 = 1;
                (void)_t1092;
                U64 _t1093 = U64_add(_fi1089, _t1092);
                (void)_t1093;
                ;
                _fi1089 = _t1093;
                ;
                U64 *_t1094 = malloc(sizeof(U64)); *_t1094 = U64_mul(i, self->elem_size);
                (void)_t1094;
                void *_t1095 = ptr_add(self->data, DEREF(_t1094));
                (void)_t1095;
                void *cloned = dyn_call_clone(&self->elem_type, _t1095);
                (void)cloned;
                U64_delete(_t1094, &(Bool){1});
                U64 *_t1096 = malloc(sizeof(U64)); *_t1096 = U64_mul(i, self->elem_size);
                (void)_t1096;
                ;
                void *_t1097 = ptr_add(new_data, DEREF(_t1096));
                (void)_t1097;
                memcpy(_t1097, cloned, self->elem_size);
                U64_delete(_t1096, &(Bool){1});
                free(cloned);
            }
            Range_delete(_fc1089, &(Bool){1});
            ;
        }
    } else {
        U64 _t1099 = U64_mul(self->count, self->elem_size);
        (void)_t1099;
        memcpy(new_data, self->data, _t1099);
        ;
    }
    ;
    Vec *_t1103 = malloc(sizeof(Vec));
    _t1103->data = new_data;
    _t1103->count = self->count;
    _t1103->cap = self->cap;
    _t1103->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1103->elem_type = *_ca; free(_ca); }
    (void)_t1103;
    return _t1103;
}

Tuple * Tuple_new(void) {
    U64 _t1105 = 8;
    (void)_t1105;
    Str *_t1106 = Str_lit("Str", 3ULL);
    (void)_t1106;
    U64 _t1107; { U64 *_hp = (U64 *)Str_size(); _t1107 = *_hp; free(_hp); }
    (void)_t1107;
    Str *_t1108 = Str_lit("U64", 3ULL);
    (void)_t1108;
    U64 _t1109; { U64 *_hp = (U64 *)U64_size(); _t1109 = *_hp; free(_hp); }
    (void)_t1109;
    void *_t1110 = malloc(_t1105);
    (void)_t1110;
    ;
    U64 _t1111 = 0;
    (void)_t1111;
    I64 _t1112 = 8;
    (void)_t1112;
    Tuple *_t1113 = malloc(sizeof(Tuple));
    _t1113->data = _t1110;
    _t1113->total_size = _t1111;
    _t1113->cap = _t1112;
    { Vec *_ca = Vec_new(_t1106, &(U64){_t1107}); _t1113->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1108, &(U64){_t1109}); _t1113->type_sizes = *_ca; free(_ca); }
    (void)_t1113;
    Str_delete(_t1106, &(Bool){1});
    ;
    Str_delete(_t1108, &(Bool){1});
    ;
    ;
    ;
    return _t1113;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1114; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1114 = *_hp; free(_hp); }
    (void)_t1114;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1114; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1121; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1121 = *_hp; free(_hp); }
    (void)_t1121;
    if (_t1121) {
        U64 _t1118 = 2;
        (void)_t1118;
        U64 new_cap = U64_mul(self->cap, _t1118);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1115; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1115 = *_hp; free(_hp); }
            (void)_wcond1115;
            if (_wcond1115) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1116 = 2;
            (void)_t1116;
            U64 _t1117 = U64_mul(new_cap, _t1116);
            (void)_t1117;
            ;
            new_cap = _t1117;
            ;
        }
        void *_t1119 = realloc(self->data, new_cap);
        (void)_t1119;
        self->data = _t1119;
        U64 _t1120 = U64_clone(&(U64){new_cap});
        (void)_t1120;
        ;
        self->cap = _t1120;
        ;
    }
    ;
    void *_t1122 = ptr_add(self->data, self->total_size);
    (void)_t1122;
    memcpy(_t1122, val, DEREF(elem_size));
    free(val);
    Str *_t1123 = Str_clone(elem_type);
    (void)_t1123;
    Vec_push(&self->type_names, _t1123);
    U64 _t1124 = U64_clone(elem_size);
    (void)_t1124;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1124; _oa; }));
    U64 _t1125 = U64_clone(&(U64){new_total});
    (void)_t1125;
    ;
    self->total_size = _t1125;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1148; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1148 = *_hp; free(_hp); }
    (void)_t1148;
    Bool _t1149; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1148}); _t1149 = *_hp; free(_hp); }
    (void)_t1149;
    ;
    if (_t1149) {
        Str *_t1126 = Str_lit("Str", 3ULL);
        (void)_t1126;
        U64 _t1127; { U64 *_hp = (U64 *)Str_size(); _t1127 = *_hp; free(_hp); }
        (void)_t1127;
        U64 _t1128 = 5;
        (void)_t1128;
        Array *_va22 = Array_new(_t1126, &(U64){_t1127}, &(U64){_t1128});
        (void)_va22;
        Str_delete(_t1126, &(Bool){1});
        ;
        ;
        U64 _t1129 = 0;
        (void)_t1129;
        Str *_t1130 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1130;
        Array_set(_va22, &(U64){_t1129}, _t1130);
        ;
        U64 _t1131 = 1;
        (void)_t1131;
        Str *_t1132 = U64_to_str(DEREF(i));
        (void)_t1132;
        Array_set(_va22, &(U64){_t1131}, _t1132);
        ;
        U64 _t1133 = 2;
        (void)_t1133;
        Str *_t1134 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1134;
        Array_set(_va22, &(U64){_t1133}, _t1134);
        ;
        U64 _t1135; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1135 = *_hp; free(_hp); }
        (void)_t1135;
        U64 _t1136 = 3;
        (void)_t1136;
        Str *_t1137 = U64_to_str(_t1135);
        (void)_t1137;
        ;
        Array_set(_va22, &(U64){_t1136}, _t1137);
        ;
        U64 _t1138 = 4;
        (void)_t1138;
        Str *_t1139 = Str_lit(")", 1ULL);
        (void)_t1139;
        Array_set(_va22, &(U64){_t1138}, _t1139);
        ;
        Str *_t1140 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1140;
        panic(_t1140, _va22);
        Str_delete(_t1140, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1147 = 0;
        (void)_t1147;
        Range *_fc1141 = Range_new(_t1147, DEREF(i));
        (void)_fc1141;
        ;
        U64 _fi1141 = 0;
        (void)_fi1141;
        while (1) {
            U64 _t1143; { U64 *_hp = (U64 *)Range_len(_fc1141); _t1143 = *_hp; free(_hp); }
            (void)_t1143;
            Bool _wcond1142; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1141}, &(U64){_t1143}); _wcond1142 = *_hp; free(_hp); }
            (void)_wcond1142;
            ;
            if (_wcond1142) {
            } else {
                ;
                break;
            }
            ;
            U64 *j = Range_get(_fc1141, _fi1141);
            (void)j;
            U64 _t1144 = 1;
            (void)_t1144;
            U64 _t1145 = U64_add(_fi1141, _t1144);
            (void)_t1145;
            ;
            _fi1141 = _t1145;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1146 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1146;
            U64_delete(j, &(Bool){1});
            *offset = _t1146;
            ;
        }
        Range_delete(_fc1141, &(Bool){1});
        ;
    }
    void *_t1150 = ptr_add(self->data, DEREF(offset));
    (void)_t1150;
    U64_delete(offset, &(Bool){1});
    return _t1150;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1151 = Vec_get(&self->type_names, i);
    (void)_t1151;
    return _t1151;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1152 = Vec_get(&self->type_sizes, i);
    (void)_t1152;
    return _t1152;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1161 = 0;
        (void)_t1161;
        U64 _t1162; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1162 = *_hp; free(_hp); }
        (void)_t1162;
        Range *_fc1153 = Range_new(_t1161, _t1162);
        (void)_fc1153;
        ;
        ;
        U64 _fi1153 = 0;
        (void)_fi1153;
        while (1) {
            U64 _t1155; { U64 *_hp = (U64 *)Range_len(_fc1153); _t1155 = *_hp; free(_hp); }
            (void)_t1155;
            Bool _wcond1154; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1153}, &(U64){_t1155}); _wcond1154 = *_hp; free(_hp); }
            (void)_wcond1154;
            ;
            if (_wcond1154) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1153, _fi1153);
            (void)i;
            U64 _t1156 = 1;
            (void)_t1156;
            U64 _t1157 = U64_add(_fi1153, _t1156);
            (void)_t1157;
            ;
            _fi1153 = _t1157;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1158 = ptr_add(self->data, DEREF(offset));
            (void)_t1158;
            Bool _t1159 = 0;
            (void)_t1159;
            dyn_call_delete(tn, _t1158, &(Bool){_t1159});
            ;
            U64 _t1160 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1160;
            U64_delete(i, &(Bool){1});
            *offset = _t1160;
            ;
        }
        Range_delete(_fc1153, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1163 = 0;
    (void)_t1163;
    Vec_delete(&self->type_names, &(Bool){_t1163});
    ;
    Bool _t1164 = 0;
    (void)_t1164;
    Vec_delete(&self->type_sizes, &(Bool){_t1164});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1177 = 0;
    (void)_t1177;
    Bool _t1178 = U64_eq(new_cap, _t1177);
    (void)_t1178;
    ;
    if (_t1178) {
        I64 _t1165 = 8;
        (void)_t1165;
        U64 _t1166; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1165}); _t1166 = *_hp; free(_hp); }
        (void)_t1166;
        ;
        new_cap = _t1166;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1175 = 0;
        (void)_t1175;
        U64 _t1176; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1176 = *_hp; free(_hp); }
        (void)_t1176;
        Range *_fc1167 = Range_new(_t1175, _t1176);
        (void)_fc1167;
        ;
        ;
        U64 _fi1167 = 0;
        (void)_fi1167;
        while (1) {
            U64 _t1169; { U64 *_hp = (U64 *)Range_len(_fc1167); _t1169 = *_hp; free(_hp); }
            (void)_t1169;
            Bool _wcond1168; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1167}, &(U64){_t1169}); _wcond1168 = *_hp; free(_hp); }
            (void)_wcond1168;
            ;
            if (_wcond1168) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1167, _fi1167);
            (void)i;
            U64 _t1170 = 1;
            (void)_t1170;
            U64 _t1171 = U64_add(_fi1167, _t1170);
            (void)_t1171;
            ;
            _fi1167 = _t1171;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1172 = ptr_add(self->data, DEREF(offset));
            (void)_t1172;
            void *cloned = dyn_call_clone(tn, _t1172);
            (void)cloned;
            void *_t1173 = ptr_add(new_data, DEREF(offset));
            (void)_t1173;
            memcpy(_t1173, cloned, DEREF(ts));
            free(cloned);
            U64 _t1174 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1174;
            U64_delete(i, &(Bool){1});
            *offset = _t1174;
            ;
        }
        Range_delete(_fc1167, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1179 = U64_clone(&(U64){new_cap});
    (void)_t1179;
    ;
    Vec *_t1180 = Vec_clone(&self->type_names);
    (void)_t1180;
    Vec *_t1181 = Vec_clone(&self->type_sizes);
    (void)_t1181;
    Tuple *_t1182 = malloc(sizeof(Tuple));
    _t1182->data = new_data;
    _t1182->total_size = self->total_size;
    _t1182->cap = _t1179;
    { Vec *_ca = Vec_clone(_t1180); _t1182->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1181); _t1182->type_sizes = *_ca; free(_ca); }
    (void)_t1182;
    ;
    Vec_delete(_t1180, &(Bool){1});
    Vec_delete(_t1181, &(Bool){1});
    return _t1182;
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
    Bool _t1201; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t1201 = *_hp; free(_hp); }
    (void)_t1201;
    if (_t1201) {
        Bool _t1184; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t1184 = *_hp; free(_hp); }
        (void)_t1184;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1184; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = (Bool *)TilType_is_None(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1185; { Bool *_hp = (Bool *)TilType_is_None(other); _t1185 = *_hp; free(_hp); }
        (void)_t1185;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1185; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TilType_is_I64(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1186; { Bool *_hp = (Bool *)TilType_is_I64(other); _t1186 = *_hp; free(_hp); }
        (void)_t1186;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1186; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TilType_is_U8(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1187; { Bool *_hp = (Bool *)TilType_is_U8(other); _t1187 = *_hp; free(_hp); }
        (void)_t1187;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1187; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TilType_is_I16(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1188; { Bool *_hp = (Bool *)TilType_is_I16(other); _t1188 = *_hp; free(_hp); }
        (void)_t1188;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1188; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TilType_is_I32(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1189; { Bool *_hp = (Bool *)TilType_is_I32(other); _t1189 = *_hp; free(_hp); }
        (void)_t1189;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1189; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TilType_is_U32(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1190; { Bool *_hp = (Bool *)TilType_is_U32(other); _t1190 = *_hp; free(_hp); }
        (void)_t1190;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1190; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TilType_is_U64(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1191; { Bool *_hp = (Bool *)TilType_is_U64(other); _t1191 = *_hp; free(_hp); }
        (void)_t1191;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1191; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TilType_is_F32(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1192; { Bool *_hp = (Bool *)TilType_is_F32(other); _t1192 = *_hp; free(_hp); }
        (void)_t1192;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1192; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1193; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t1193 = *_hp; free(_hp); }
        (void)_t1193;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1193; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1194; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t1194 = *_hp; free(_hp); }
        (void)_t1194;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1194; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1195; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t1195 = *_hp; free(_hp); }
        (void)_t1195;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1195; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1196; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t1196 = *_hp; free(_hp); }
        (void)_t1196;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1196; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1197; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t1197 = *_hp; free(_hp); }
        (void)_t1197;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1197; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1198; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t1198 = *_hp; free(_hp); }
        (void)_t1198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1198; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1199; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t1199 = *_hp; free(_hp); }
        (void)_t1199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1199; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1200; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t1200 = *_hp; free(_hp); }
        (void)_t1200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1200; return _r; }
    }
    ;
    Bool _t1218 = 0;
    (void)_t1218;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1218; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t1219; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    if (_t1219) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t1220; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        ;
        return TilType_None();
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
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
    Bool _t1252; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        Str *_t1235 = Str_lit("Unknown", 7ULL);
        (void)_t1235;
        ;
        return _t1235;
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        Str *_t1236 = Str_lit("None", 4ULL);
        (void)_t1236;
        ;
        return _t1236;
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        Str *_t1237 = Str_lit("I64", 3ULL);
        (void)_t1237;
        ;
        return _t1237;
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        Str *_t1238 = Str_lit("U8", 2ULL);
        (void)_t1238;
        ;
        return _t1238;
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        Str *_t1239 = Str_lit("I16", 3ULL);
        (void)_t1239;
        ;
        return _t1239;
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        Str *_t1240 = Str_lit("I32", 3ULL);
        (void)_t1240;
        ;
        return _t1240;
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        Str *_t1241 = Str_lit("U32", 3ULL);
        (void)_t1241;
        ;
        return _t1241;
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        Str *_t1242 = Str_lit("U64", 3ULL);
        (void)_t1242;
        ;
        return _t1242;
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        Str *_t1243 = Str_lit("F32", 3ULL);
        (void)_t1243;
        ;
        return _t1243;
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        Str *_t1244 = Str_lit("Bool", 4ULL);
        (void)_t1244;
        ;
        return _t1244;
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        Str *_t1245 = Str_lit("Struct", 6ULL);
        (void)_t1245;
        ;
        return _t1245;
    }
    ;
    Bool _t1263; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1263 = *_hp; free(_hp); }
    (void)_t1263;
    if (_t1263) {
        Str *_t1246 = Str_lit("StructDef", 9ULL);
        (void)_t1246;
        ;
        return _t1246;
    }
    ;
    Bool _t1264; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        Str *_t1247 = Str_lit("Enum", 4ULL);
        (void)_t1247;
        ;
        return _t1247;
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        Str *_t1248 = Str_lit("EnumDef", 7ULL);
        (void)_t1248;
        ;
        return _t1248;
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        Str *_t1249 = Str_lit("FuncDef", 7ULL);
        (void)_t1249;
        ;
        return _t1249;
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        Str *_t1250 = Str_lit("FuncPtr", 7ULL);
        (void)_t1250;
        ;
        return _t1250;
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        Str *_t1251 = Str_lit("Dynamic", 7ULL);
        (void)_t1251;
        ;
        return _t1251;
    }
    ;
    Str *_t1269 = Str_lit("unknown", 7ULL);
    (void)_t1269;
    return _t1269;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t1307; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t1307 = *_hp; free(_hp); }
    (void)_t1307;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1307; return _r; }
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
    Bool _t1330; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t1330 = *_hp; free(_hp); }
    (void)_t1330;
    if (_t1330) {
        Bool _t1324; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t1324 = *_hp; free(_hp); }
        (void)_t1324;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1324; return _r; }
    }
    ;
    Bool _t1331; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Bool _t1325; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t1325 = *_hp; free(_hp); }
        (void)_t1325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1325; return _r; }
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1326; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t1326 = *_hp; free(_hp); }
        (void)_t1326;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1326; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1327; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t1327 = *_hp; free(_hp); }
        (void)_t1327;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1327; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1328; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t1328 = *_hp; free(_hp); }
        (void)_t1328;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1328; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1329; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t1329 = *_hp; free(_hp); }
        (void)_t1329;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1329; return _r; }
    }
    ;
    Bool _t1336 = 0;
    (void)_t1336;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1336; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t1337; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1337 = *_hp; free(_hp); }
    (void)_t1337;
    if (_t1337) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t1338; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t1341; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1341 = *_hp; free(_hp); }
    (void)_t1341;
    if (_t1341) {
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
    Bool _t1348; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1348 = *_hp; free(_hp); }
    (void)_t1348;
    if (_t1348) {
        Str *_t1342 = Str_lit("Func", 4ULL);
        (void)_t1342;
        ;
        return _t1342;
    }
    ;
    Bool _t1349; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        Str *_t1343 = Str_lit("Proc", 4ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        Str *_t1344 = Str_lit("Test", 4ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        Str *_t1345 = Str_lit("Macro", 5ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        Str *_t1346 = Str_lit("ExtFunc", 7ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        Str *_t1347 = Str_lit("ExtProc", 7ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Str *_t1354 = Str_lit("unknown", 7ULL);
    (void)_t1354;
    return _t1354;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t1366; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1366; return _r; }
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
    Bool _t1463; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1463 = *_hp; free(_hp); }
    (void)_t1463;
    if (_t1463) {
        Bool _t1383; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t1383 = *_hp; free(_hp); }
        (void)_t1383;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1383; return _r; }
    }
    ;
    Bool _t1464; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1464 = *_hp; free(_hp); }
    (void)_t1464;
    if (_t1464) {
        Bool _t1385; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t1385 = *_hp; free(_hp); }
        (void)_t1385;
        Bool _t1386 = Bool_not(_t1385);
        (void)_t1386;
        ;
        if (_t1386) {
            Bool _t1384 = 0;
            (void)_t1384;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1384; return _r; }
        }
        ;
        Str *_t1387 = ExprData_get_LiteralStr(self);
        (void)_t1387;
        Str *_t1388 = ExprData_get_LiteralStr(other);
        (void)_t1388;
        Bool _t1389; { Bool *_hp = (Bool *)Str_eq(_t1387, _t1388); _t1389 = *_hp; free(_hp); }
        (void)_t1389;
        Str_delete(_t1387, &(Bool){1});
        Str_delete(_t1388, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1389; return _r; }
    }
    ;
    Bool _t1465; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1465 = *_hp; free(_hp); }
    (void)_t1465;
    if (_t1465) {
        Bool _t1391; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t1391 = *_hp; free(_hp); }
        (void)_t1391;
        Bool _t1392 = Bool_not(_t1391);
        (void)_t1392;
        ;
        if (_t1392) {
            Bool _t1390 = 0;
            (void)_t1390;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1390; return _r; }
        }
        ;
        Str *_t1393 = ExprData_get_LiteralNum(self);
        (void)_t1393;
        Str *_t1394 = ExprData_get_LiteralNum(other);
        (void)_t1394;
        Bool _t1395; { Bool *_hp = (Bool *)Str_eq(_t1393, _t1394); _t1395 = *_hp; free(_hp); }
        (void)_t1395;
        Str_delete(_t1393, &(Bool){1});
        Str_delete(_t1394, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1395; return _r; }
    }
    ;
    Bool _t1466; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1466 = *_hp; free(_hp); }
    (void)_t1466;
    if (_t1466) {
        Bool _t1397; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t1397 = *_hp; free(_hp); }
        (void)_t1397;
        Bool _t1398 = Bool_not(_t1397);
        (void)_t1398;
        ;
        if (_t1398) {
            Bool _t1396 = 0;
            (void)_t1396;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1396; return _r; }
        }
        ;
        Str *_t1399 = ExprData_get_LiteralBool(self);
        (void)_t1399;
        Str *_t1400 = ExprData_get_LiteralBool(other);
        (void)_t1400;
        Bool _t1401; { Bool *_hp = (Bool *)Str_eq(_t1399, _t1400); _t1401 = *_hp; free(_hp); }
        (void)_t1401;
        Str_delete(_t1399, &(Bool){1});
        Str_delete(_t1400, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1401; return _r; }
    }
    ;
    Bool _t1467; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1467 = *_hp; free(_hp); }
    (void)_t1467;
    if (_t1467) {
        Bool _t1402; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t1402 = *_hp; free(_hp); }
        (void)_t1402;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1402; return _r; }
    }
    ;
    Bool _t1468; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1468 = *_hp; free(_hp); }
    (void)_t1468;
    if (_t1468) {
        Bool _t1404; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t1404 = *_hp; free(_hp); }
        (void)_t1404;
        Bool _t1405 = Bool_not(_t1404);
        (void)_t1405;
        ;
        if (_t1405) {
            Bool _t1403 = 0;
            (void)_t1403;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1403; return _r; }
        }
        ;
        Str *_t1406 = ExprData_get_Ident(self);
        (void)_t1406;
        Str *_t1407 = ExprData_get_Ident(other);
        (void)_t1407;
        Bool _t1408; { Bool *_hp = (Bool *)Str_eq(_t1406, _t1407); _t1408 = *_hp; free(_hp); }
        (void)_t1408;
        Str_delete(_t1406, &(Bool){1});
        Str_delete(_t1407, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1408; return _r; }
    }
    ;
    Bool _t1469; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1469 = *_hp; free(_hp); }
    (void)_t1469;
    if (_t1469) {
        Bool _t1410; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t1410 = *_hp; free(_hp); }
        (void)_t1410;
        Bool _t1411 = Bool_not(_t1410);
        (void)_t1411;
        ;
        if (_t1411) {
            Bool _t1409 = 0;
            (void)_t1409;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1409; return _r; }
        }
        ;
        Declaration *_t1412 = ExprData_get_Decl(self);
        (void)_t1412;
        Declaration *_t1413 = ExprData_get_Decl(other);
        (void)_t1413;
        Bool _t1414; { Bool *_hp = (Bool *)Declaration_eq(_t1412, _t1413); _t1414 = *_hp; free(_hp); }
        (void)_t1414;
        Declaration_delete(_t1412, &(Bool){1});
        Declaration_delete(_t1413, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1414; return _r; }
    }
    ;
    Bool _t1470; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1470 = *_hp; free(_hp); }
    (void)_t1470;
    if (_t1470) {
        Bool _t1416; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t1416 = *_hp; free(_hp); }
        (void)_t1416;
        Bool _t1417 = Bool_not(_t1416);
        (void)_t1417;
        ;
        if (_t1417) {
            Bool _t1415 = 0;
            (void)_t1415;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1415; return _r; }
        }
        ;
        Str *_t1418 = ExprData_get_Assign(self);
        (void)_t1418;
        Str *_t1419 = ExprData_get_Assign(other);
        (void)_t1419;
        Bool _t1420; { Bool *_hp = (Bool *)Str_eq(_t1418, _t1419); _t1420 = *_hp; free(_hp); }
        (void)_t1420;
        Str_delete(_t1418, &(Bool){1});
        Str_delete(_t1419, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1420; return _r; }
    }
    ;
    Bool _t1471; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1471 = *_hp; free(_hp); }
    (void)_t1471;
    if (_t1471) {
        Bool _t1421; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t1421 = *_hp; free(_hp); }
        (void)_t1421;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1421; return _r; }
    }
    ;
    Bool _t1472; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1472 = *_hp; free(_hp); }
    (void)_t1472;
    if (_t1472) {
        Bool _t1423; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t1423 = *_hp; free(_hp); }
        (void)_t1423;
        Bool _t1424 = Bool_not(_t1423);
        (void)_t1424;
        ;
        if (_t1424) {
            Bool _t1422 = 0;
            (void)_t1422;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1422; return _r; }
        }
        ;
        FunctionDef *_t1425 = ExprData_get_FuncDef(self);
        (void)_t1425;
        FunctionDef *_t1426 = ExprData_get_FuncDef(other);
        (void)_t1426;
        Bool _t1427; { Bool *_hp = (Bool *)FunctionDef_eq(_t1425, _t1426); _t1427 = *_hp; free(_hp); }
        (void)_t1427;
        FunctionDef_delete(_t1425, &(Bool){1});
        FunctionDef_delete(_t1426, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1427; return _r; }
    }
    ;
    Bool _t1473; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1473 = *_hp; free(_hp); }
    (void)_t1473;
    if (_t1473) {
        Bool _t1428; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t1428 = *_hp; free(_hp); }
        (void)_t1428;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1428; return _r; }
    }
    ;
    Bool _t1474; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1474 = *_hp; free(_hp); }
    (void)_t1474;
    if (_t1474) {
        Bool _t1429; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t1429 = *_hp; free(_hp); }
        (void)_t1429;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1429; return _r; }
    }
    ;
    Bool _t1475; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1475 = *_hp; free(_hp); }
    (void)_t1475;
    if (_t1475) {
        Bool _t1431; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t1431 = *_hp; free(_hp); }
        (void)_t1431;
        Bool _t1432 = Bool_not(_t1431);
        (void)_t1432;
        ;
        if (_t1432) {
            Bool _t1430 = 0;
            (void)_t1430;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1430; return _r; }
        }
        ;
        Str *_t1433 = ExprData_get_FieldAccess(self);
        (void)_t1433;
        Str *_t1434 = ExprData_get_FieldAccess(other);
        (void)_t1434;
        Bool _t1435; { Bool *_hp = (Bool *)Str_eq(_t1433, _t1434); _t1435 = *_hp; free(_hp); }
        (void)_t1435;
        Str_delete(_t1433, &(Bool){1});
        Str_delete(_t1434, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1435; return _r; }
    }
    ;
    Bool _t1476; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1476 = *_hp; free(_hp); }
    (void)_t1476;
    if (_t1476) {
        Bool _t1437; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t1437 = *_hp; free(_hp); }
        (void)_t1437;
        Bool _t1438 = Bool_not(_t1437);
        (void)_t1438;
        ;
        if (_t1438) {
            Bool _t1436 = 0;
            (void)_t1436;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1436; return _r; }
        }
        ;
        Str *_t1439 = ExprData_get_FieldAssign(self);
        (void)_t1439;
        Str *_t1440 = ExprData_get_FieldAssign(other);
        (void)_t1440;
        Bool _t1441; { Bool *_hp = (Bool *)Str_eq(_t1439, _t1440); _t1441 = *_hp; free(_hp); }
        (void)_t1441;
        Str_delete(_t1439, &(Bool){1});
        Str_delete(_t1440, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1441; return _r; }
    }
    ;
    Bool _t1477; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1477 = *_hp; free(_hp); }
    (void)_t1477;
    if (_t1477) {
        Bool _t1442; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t1442 = *_hp; free(_hp); }
        (void)_t1442;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1442; return _r; }
    }
    ;
    Bool _t1478; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1478 = *_hp; free(_hp); }
    (void)_t1478;
    if (_t1478) {
        Bool _t1443; { Bool *_hp = (Bool *)ExprData_is_If(other); _t1443 = *_hp; free(_hp); }
        (void)_t1443;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1443; return _r; }
    }
    ;
    Bool _t1479; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1479 = *_hp; free(_hp); }
    (void)_t1479;
    if (_t1479) {
        Bool _t1444; { Bool *_hp = (Bool *)ExprData_is_While(other); _t1444 = *_hp; free(_hp); }
        (void)_t1444;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1444; return _r; }
    }
    ;
    Bool _t1480; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1480 = *_hp; free(_hp); }
    (void)_t1480;
    if (_t1480) {
        Bool _t1446; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t1446 = *_hp; free(_hp); }
        (void)_t1446;
        Bool _t1447 = Bool_not(_t1446);
        (void)_t1447;
        ;
        if (_t1447) {
            Bool _t1445 = 0;
            (void)_t1445;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1445; return _r; }
        }
        ;
        Str *_t1448 = ExprData_get_ForIn(self);
        (void)_t1448;
        Str *_t1449 = ExprData_get_ForIn(other);
        (void)_t1449;
        Bool _t1450; { Bool *_hp = (Bool *)Str_eq(_t1448, _t1449); _t1450 = *_hp; free(_hp); }
        (void)_t1450;
        Str_delete(_t1448, &(Bool){1});
        Str_delete(_t1449, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1450; return _r; }
    }
    ;
    Bool _t1481; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1481 = *_hp; free(_hp); }
    (void)_t1481;
    if (_t1481) {
        Bool _t1452; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t1452 = *_hp; free(_hp); }
        (void)_t1452;
        Bool _t1453 = Bool_not(_t1452);
        (void)_t1453;
        ;
        if (_t1453) {
            Bool _t1451 = 0;
            (void)_t1451;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1451; return _r; }
        }
        ;
        Str *_t1454 = ExprData_get_NamedArg(self);
        (void)_t1454;
        Str *_t1455 = ExprData_get_NamedArg(other);
        (void)_t1455;
        Bool _t1456; { Bool *_hp = (Bool *)Str_eq(_t1454, _t1455); _t1456 = *_hp; free(_hp); }
        (void)_t1456;
        Str_delete(_t1454, &(Bool){1});
        Str_delete(_t1455, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1456; return _r; }
    }
    ;
    Bool _t1482; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1482 = *_hp; free(_hp); }
    (void)_t1482;
    if (_t1482) {
        Bool _t1457; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t1457 = *_hp; free(_hp); }
        (void)_t1457;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1457; return _r; }
    }
    ;
    Bool _t1483; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1483 = *_hp; free(_hp); }
    (void)_t1483;
    if (_t1483) {
        Bool _t1458; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t1458 = *_hp; free(_hp); }
        (void)_t1458;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1458; return _r; }
    }
    ;
    Bool _t1484; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1484 = *_hp; free(_hp); }
    (void)_t1484;
    if (_t1484) {
        Bool _t1459; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t1459 = *_hp; free(_hp); }
        (void)_t1459;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1459; return _r; }
    }
    ;
    Bool _t1485; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1485 = *_hp; free(_hp); }
    (void)_t1485;
    if (_t1485) {
        Bool _t1460; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t1460 = *_hp; free(_hp); }
        (void)_t1460;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1460; return _r; }
    }
    ;
    Bool _t1486; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1486 = *_hp; free(_hp); }
    (void)_t1486;
    if (_t1486) {
        Bool _t1461; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t1461 = *_hp; free(_hp); }
        (void)_t1461;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1461; return _r; }
    }
    ;
    Bool _t1487; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1487 = *_hp; free(_hp); }
    (void)_t1487;
    if (_t1487) {
        Bool _t1462; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t1462 = *_hp; free(_hp); }
        (void)_t1462;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1462; return _r; }
    }
    ;
    Bool _t1488 = 0;
    (void)_t1488;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1488; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t1511; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1511 = *_hp; free(_hp); }
    (void)_t1511;
    if (_t1511) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t1512; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1512 = *_hp; free(_hp); }
    (void)_t1512;
    if (_t1512) {
        Str *_t1489 = ExprData_get_LiteralStr(self);
        (void)_t1489;
        ExprData *_t1490 = ExprData_LiteralStr(_t1489);
        (void)_t1490;
        Str_delete(_t1489, &(Bool){1});
        ;
        return _t1490;
    }
    ;
    Bool _t1513; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1513 = *_hp; free(_hp); }
    (void)_t1513;
    if (_t1513) {
        Str *_t1491 = ExprData_get_LiteralNum(self);
        (void)_t1491;
        ExprData *_t1492 = ExprData_LiteralNum(_t1491);
        (void)_t1492;
        Str_delete(_t1491, &(Bool){1});
        ;
        return _t1492;
    }
    ;
    Bool _t1514; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1514 = *_hp; free(_hp); }
    (void)_t1514;
    if (_t1514) {
        Str *_t1493 = ExprData_get_LiteralBool(self);
        (void)_t1493;
        ExprData *_t1494 = ExprData_LiteralBool(_t1493);
        (void)_t1494;
        Str_delete(_t1493, &(Bool){1});
        ;
        return _t1494;
    }
    ;
    Bool _t1515; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1515 = *_hp; free(_hp); }
    (void)_t1515;
    if (_t1515) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t1516; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1516 = *_hp; free(_hp); }
    (void)_t1516;
    if (_t1516) {
        Str *_t1495 = ExprData_get_Ident(self);
        (void)_t1495;
        ExprData *_t1496 = ExprData_Ident(_t1495);
        (void)_t1496;
        Str_delete(_t1495, &(Bool){1});
        ;
        return _t1496;
    }
    ;
    Bool _t1517; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1517 = *_hp; free(_hp); }
    (void)_t1517;
    if (_t1517) {
        Declaration *_t1497 = ExprData_get_Decl(self);
        (void)_t1497;
        ExprData *_t1498 = ExprData_Decl(_t1497);
        (void)_t1498;
        Declaration_delete(_t1497, &(Bool){1});
        ;
        return _t1498;
    }
    ;
    Bool _t1518; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1518 = *_hp; free(_hp); }
    (void)_t1518;
    if (_t1518) {
        Str *_t1499 = ExprData_get_Assign(self);
        (void)_t1499;
        ExprData *_t1500 = ExprData_Assign(_t1499);
        (void)_t1500;
        Str_delete(_t1499, &(Bool){1});
        ;
        return _t1500;
    }
    ;
    Bool _t1519; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1519 = *_hp; free(_hp); }
    (void)_t1519;
    if (_t1519) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t1520; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1520 = *_hp; free(_hp); }
    (void)_t1520;
    if (_t1520) {
        FunctionDef *_t1501 = ExprData_get_FuncDef(self);
        (void)_t1501;
        ExprData *_t1502 = ExprData_FuncDef(_t1501);
        (void)_t1502;
        FunctionDef_delete(_t1501, &(Bool){1});
        ;
        return _t1502;
    }
    ;
    Bool _t1521; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1521 = *_hp; free(_hp); }
    (void)_t1521;
    if (_t1521) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t1522; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1522 = *_hp; free(_hp); }
    (void)_t1522;
    if (_t1522) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t1523; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1523 = *_hp; free(_hp); }
    (void)_t1523;
    if (_t1523) {
        Str *_t1503 = ExprData_get_FieldAccess(self);
        (void)_t1503;
        ExprData *_t1504 = ExprData_FieldAccess(_t1503);
        (void)_t1504;
        Str_delete(_t1503, &(Bool){1});
        ;
        return _t1504;
    }
    ;
    Bool _t1524; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1524 = *_hp; free(_hp); }
    (void)_t1524;
    if (_t1524) {
        Str *_t1505 = ExprData_get_FieldAssign(self);
        (void)_t1505;
        ExprData *_t1506 = ExprData_FieldAssign(_t1505);
        (void)_t1506;
        Str_delete(_t1505, &(Bool){1});
        ;
        return _t1506;
    }
    ;
    Bool _t1525; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1525 = *_hp; free(_hp); }
    (void)_t1525;
    if (_t1525) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t1526; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1526 = *_hp; free(_hp); }
    (void)_t1526;
    if (_t1526) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t1527; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        Str *_t1507 = ExprData_get_ForIn(self);
        (void)_t1507;
        ExprData *_t1508 = ExprData_ForIn(_t1507);
        (void)_t1508;
        Str_delete(_t1507, &(Bool){1});
        ;
        return _t1508;
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Str *_t1509 = ExprData_get_NamedArg(self);
        (void)_t1509;
        ExprData *_t1510 = ExprData_NamedArg(_t1509);
        (void)_t1510;
        Str_delete(_t1509, &(Bool){1});
        ;
        return _t1510;
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
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
    Bool _t1670; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1670 = *_hp; free(_hp); }
    (void)_t1670;
    if (_t1670) {
        Str *_t1535 = Str_lit("Body", 4ULL);
        (void)_t1535;
        ;
        return _t1535;
    }
    ;
    Bool _t1671; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1671 = *_hp; free(_hp); }
    (void)_t1671;
    if (_t1671) {
        Str *_t1536 = Str_lit("Str", 3ULL);
        (void)_t1536;
        U64 _t1537; { U64 *_hp = (U64 *)Str_size(); _t1537 = *_hp; free(_hp); }
        (void)_t1537;
        U64 _t1538 = 3;
        (void)_t1538;
        Array *_va23 = Array_new(_t1536, &(U64){_t1537}, &(U64){_t1538});
        (void)_va23;
        Str_delete(_t1536, &(Bool){1});
        ;
        ;
        U64 _t1539 = 0;
        (void)_t1539;
        Str *_t1540 = Str_lit("LiteralStr(", 11ULL);
        (void)_t1540;
        Array_set(_va23, &(U64){_t1539}, _t1540);
        ;
        Str *_t1541 = ExprData_get_LiteralStr(self);
        (void)_t1541;
        U64 _t1542 = 1;
        (void)_t1542;
        Str *_t1543 = Str_to_str(_t1541);
        (void)_t1543;
        Str_delete(_t1541, &(Bool){1});
        Array_set(_va23, &(U64){_t1542}, _t1543);
        ;
        U64 _t1544 = 2;
        (void)_t1544;
        Str *_t1545 = Str_lit(")", 1ULL);
        (void)_t1545;
        Array_set(_va23, &(U64){_t1544}, _t1545);
        ;
        Str *_t1546 = format(_va23);
        (void)_t1546;
        ;
        return _t1546;
    }
    ;
    Bool _t1672; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1672 = *_hp; free(_hp); }
    (void)_t1672;
    if (_t1672) {
        Str *_t1547 = Str_lit("Str", 3ULL);
        (void)_t1547;
        U64 _t1548; { U64 *_hp = (U64 *)Str_size(); _t1548 = *_hp; free(_hp); }
        (void)_t1548;
        U64 _t1549 = 3;
        (void)_t1549;
        Array *_va24 = Array_new(_t1547, &(U64){_t1548}, &(U64){_t1549});
        (void)_va24;
        Str_delete(_t1547, &(Bool){1});
        ;
        ;
        U64 _t1550 = 0;
        (void)_t1550;
        Str *_t1551 = Str_lit("LiteralNum(", 11ULL);
        (void)_t1551;
        Array_set(_va24, &(U64){_t1550}, _t1551);
        ;
        Str *_t1552 = ExprData_get_LiteralNum(self);
        (void)_t1552;
        U64 _t1553 = 1;
        (void)_t1553;
        Str *_t1554 = Str_to_str(_t1552);
        (void)_t1554;
        Str_delete(_t1552, &(Bool){1});
        Array_set(_va24, &(U64){_t1553}, _t1554);
        ;
        U64 _t1555 = 2;
        (void)_t1555;
        Str *_t1556 = Str_lit(")", 1ULL);
        (void)_t1556;
        Array_set(_va24, &(U64){_t1555}, _t1556);
        ;
        Str *_t1557 = format(_va24);
        (void)_t1557;
        ;
        return _t1557;
    }
    ;
    Bool _t1673; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1673 = *_hp; free(_hp); }
    (void)_t1673;
    if (_t1673) {
        Str *_t1558 = Str_lit("Str", 3ULL);
        (void)_t1558;
        U64 _t1559; { U64 *_hp = (U64 *)Str_size(); _t1559 = *_hp; free(_hp); }
        (void)_t1559;
        U64 _t1560 = 3;
        (void)_t1560;
        Array *_va25 = Array_new(_t1558, &(U64){_t1559}, &(U64){_t1560});
        (void)_va25;
        Str_delete(_t1558, &(Bool){1});
        ;
        ;
        U64 _t1561 = 0;
        (void)_t1561;
        Str *_t1562 = Str_lit("LiteralBool(", 12ULL);
        (void)_t1562;
        Array_set(_va25, &(U64){_t1561}, _t1562);
        ;
        Str *_t1563 = ExprData_get_LiteralBool(self);
        (void)_t1563;
        U64 _t1564 = 1;
        (void)_t1564;
        Str *_t1565 = Str_to_str(_t1563);
        (void)_t1565;
        Str_delete(_t1563, &(Bool){1});
        Array_set(_va25, &(U64){_t1564}, _t1565);
        ;
        U64 _t1566 = 2;
        (void)_t1566;
        Str *_t1567 = Str_lit(")", 1ULL);
        (void)_t1567;
        Array_set(_va25, &(U64){_t1566}, _t1567);
        ;
        Str *_t1568 = format(_va25);
        (void)_t1568;
        ;
        return _t1568;
    }
    ;
    Bool _t1674; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1674 = *_hp; free(_hp); }
    (void)_t1674;
    if (_t1674) {
        Str *_t1569 = Str_lit("LiteralNull", 11ULL);
        (void)_t1569;
        ;
        return _t1569;
    }
    ;
    Bool _t1675; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1675 = *_hp; free(_hp); }
    (void)_t1675;
    if (_t1675) {
        Str *_t1570 = Str_lit("Str", 3ULL);
        (void)_t1570;
        U64 _t1571; { U64 *_hp = (U64 *)Str_size(); _t1571 = *_hp; free(_hp); }
        (void)_t1571;
        U64 _t1572 = 3;
        (void)_t1572;
        Array *_va26 = Array_new(_t1570, &(U64){_t1571}, &(U64){_t1572});
        (void)_va26;
        Str_delete(_t1570, &(Bool){1});
        ;
        ;
        U64 _t1573 = 0;
        (void)_t1573;
        Str *_t1574 = Str_lit("Ident(", 6ULL);
        (void)_t1574;
        Array_set(_va26, &(U64){_t1573}, _t1574);
        ;
        Str *_t1575 = ExprData_get_Ident(self);
        (void)_t1575;
        U64 _t1576 = 1;
        (void)_t1576;
        Str *_t1577 = Str_to_str(_t1575);
        (void)_t1577;
        Str_delete(_t1575, &(Bool){1});
        Array_set(_va26, &(U64){_t1576}, _t1577);
        ;
        U64 _t1578 = 2;
        (void)_t1578;
        Str *_t1579 = Str_lit(")", 1ULL);
        (void)_t1579;
        Array_set(_va26, &(U64){_t1578}, _t1579);
        ;
        Str *_t1580 = format(_va26);
        (void)_t1580;
        ;
        return _t1580;
    }
    ;
    Bool _t1676; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1676 = *_hp; free(_hp); }
    (void)_t1676;
    if (_t1676) {
        Str *_t1581 = Str_lit("Str", 3ULL);
        (void)_t1581;
        U64 _t1582; { U64 *_hp = (U64 *)Str_size(); _t1582 = *_hp; free(_hp); }
        (void)_t1582;
        U64 _t1583 = 3;
        (void)_t1583;
        Array *_va27 = Array_new(_t1581, &(U64){_t1582}, &(U64){_t1583});
        (void)_va27;
        Str_delete(_t1581, &(Bool){1});
        ;
        ;
        U64 _t1584 = 0;
        (void)_t1584;
        Str *_t1585 = Str_lit("Decl(", 5ULL);
        (void)_t1585;
        Array_set(_va27, &(U64){_t1584}, _t1585);
        ;
        Declaration *_t1586 = ExprData_get_Decl(self);
        (void)_t1586;
        U64 _t1587 = 1;
        (void)_t1587;
        Str *_t1588 = Declaration_to_str(_t1586);
        (void)_t1588;
        Declaration_delete(_t1586, &(Bool){1});
        Array_set(_va27, &(U64){_t1587}, _t1588);
        ;
        U64 _t1589 = 2;
        (void)_t1589;
        Str *_t1590 = Str_lit(")", 1ULL);
        (void)_t1590;
        Array_set(_va27, &(U64){_t1589}, _t1590);
        ;
        Str *_t1591 = format(_va27);
        (void)_t1591;
        ;
        return _t1591;
    }
    ;
    Bool _t1677; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1677 = *_hp; free(_hp); }
    (void)_t1677;
    if (_t1677) {
        Str *_t1592 = Str_lit("Str", 3ULL);
        (void)_t1592;
        U64 _t1593; { U64 *_hp = (U64 *)Str_size(); _t1593 = *_hp; free(_hp); }
        (void)_t1593;
        U64 _t1594 = 3;
        (void)_t1594;
        Array *_va28 = Array_new(_t1592, &(U64){_t1593}, &(U64){_t1594});
        (void)_va28;
        Str_delete(_t1592, &(Bool){1});
        ;
        ;
        U64 _t1595 = 0;
        (void)_t1595;
        Str *_t1596 = Str_lit("Assign(", 7ULL);
        (void)_t1596;
        Array_set(_va28, &(U64){_t1595}, _t1596);
        ;
        Str *_t1597 = ExprData_get_Assign(self);
        (void)_t1597;
        U64 _t1598 = 1;
        (void)_t1598;
        Str *_t1599 = Str_to_str(_t1597);
        (void)_t1599;
        Str_delete(_t1597, &(Bool){1});
        Array_set(_va28, &(U64){_t1598}, _t1599);
        ;
        U64 _t1600 = 2;
        (void)_t1600;
        Str *_t1601 = Str_lit(")", 1ULL);
        (void)_t1601;
        Array_set(_va28, &(U64){_t1600}, _t1601);
        ;
        Str *_t1602 = format(_va28);
        (void)_t1602;
        ;
        return _t1602;
    }
    ;
    Bool _t1678; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1678 = *_hp; free(_hp); }
    (void)_t1678;
    if (_t1678) {
        Str *_t1603 = Str_lit("FCall", 5ULL);
        (void)_t1603;
        ;
        return _t1603;
    }
    ;
    Bool _t1679; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1679 = *_hp; free(_hp); }
    (void)_t1679;
    if (_t1679) {
        Str *_t1604 = Str_lit("Str", 3ULL);
        (void)_t1604;
        U64 _t1605; { U64 *_hp = (U64 *)Str_size(); _t1605 = *_hp; free(_hp); }
        (void)_t1605;
        U64 _t1606 = 3;
        (void)_t1606;
        Array *_va29 = Array_new(_t1604, &(U64){_t1605}, &(U64){_t1606});
        (void)_va29;
        Str_delete(_t1604, &(Bool){1});
        ;
        ;
        U64 _t1607 = 0;
        (void)_t1607;
        Str *_t1608 = Str_lit("FuncDef(", 8ULL);
        (void)_t1608;
        Array_set(_va29, &(U64){_t1607}, _t1608);
        ;
        FunctionDef *_t1609 = ExprData_get_FuncDef(self);
        (void)_t1609;
        U64 _t1610 = 1;
        (void)_t1610;
        Str *_t1611 = FunctionDef_to_str(_t1609);
        (void)_t1611;
        FunctionDef_delete(_t1609, &(Bool){1});
        Array_set(_va29, &(U64){_t1610}, _t1611);
        ;
        U64 _t1612 = 2;
        (void)_t1612;
        Str *_t1613 = Str_lit(")", 1ULL);
        (void)_t1613;
        Array_set(_va29, &(U64){_t1612}, _t1613);
        ;
        Str *_t1614 = format(_va29);
        (void)_t1614;
        ;
        return _t1614;
    }
    ;
    Bool _t1680; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1680 = *_hp; free(_hp); }
    (void)_t1680;
    if (_t1680) {
        Str *_t1615 = Str_lit("StructDef", 9ULL);
        (void)_t1615;
        ;
        return _t1615;
    }
    ;
    Bool _t1681; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1681 = *_hp; free(_hp); }
    (void)_t1681;
    if (_t1681) {
        Str *_t1616 = Str_lit("EnumDef", 7ULL);
        (void)_t1616;
        ;
        return _t1616;
    }
    ;
    Bool _t1682; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1682 = *_hp; free(_hp); }
    (void)_t1682;
    if (_t1682) {
        Str *_t1617 = Str_lit("Str", 3ULL);
        (void)_t1617;
        U64 _t1618; { U64 *_hp = (U64 *)Str_size(); _t1618 = *_hp; free(_hp); }
        (void)_t1618;
        U64 _t1619 = 3;
        (void)_t1619;
        Array *_va30 = Array_new(_t1617, &(U64){_t1618}, &(U64){_t1619});
        (void)_va30;
        Str_delete(_t1617, &(Bool){1});
        ;
        ;
        U64 _t1620 = 0;
        (void)_t1620;
        Str *_t1621 = Str_lit("FieldAccess(", 12ULL);
        (void)_t1621;
        Array_set(_va30, &(U64){_t1620}, _t1621);
        ;
        Str *_t1622 = ExprData_get_FieldAccess(self);
        (void)_t1622;
        U64 _t1623 = 1;
        (void)_t1623;
        Str *_t1624 = Str_to_str(_t1622);
        (void)_t1624;
        Str_delete(_t1622, &(Bool){1});
        Array_set(_va30, &(U64){_t1623}, _t1624);
        ;
        U64 _t1625 = 2;
        (void)_t1625;
        Str *_t1626 = Str_lit(")", 1ULL);
        (void)_t1626;
        Array_set(_va30, &(U64){_t1625}, _t1626);
        ;
        Str *_t1627 = format(_va30);
        (void)_t1627;
        ;
        return _t1627;
    }
    ;
    Bool _t1683; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1683 = *_hp; free(_hp); }
    (void)_t1683;
    if (_t1683) {
        Str *_t1628 = Str_lit("Str", 3ULL);
        (void)_t1628;
        U64 _t1629; { U64 *_hp = (U64 *)Str_size(); _t1629 = *_hp; free(_hp); }
        (void)_t1629;
        U64 _t1630 = 3;
        (void)_t1630;
        Array *_va31 = Array_new(_t1628, &(U64){_t1629}, &(U64){_t1630});
        (void)_va31;
        Str_delete(_t1628, &(Bool){1});
        ;
        ;
        U64 _t1631 = 0;
        (void)_t1631;
        Str *_t1632 = Str_lit("FieldAssign(", 12ULL);
        (void)_t1632;
        Array_set(_va31, &(U64){_t1631}, _t1632);
        ;
        Str *_t1633 = ExprData_get_FieldAssign(self);
        (void)_t1633;
        U64 _t1634 = 1;
        (void)_t1634;
        Str *_t1635 = Str_to_str(_t1633);
        (void)_t1635;
        Str_delete(_t1633, &(Bool){1});
        Array_set(_va31, &(U64){_t1634}, _t1635);
        ;
        U64 _t1636 = 2;
        (void)_t1636;
        Str *_t1637 = Str_lit(")", 1ULL);
        (void)_t1637;
        Array_set(_va31, &(U64){_t1636}, _t1637);
        ;
        Str *_t1638 = format(_va31);
        (void)_t1638;
        ;
        return _t1638;
    }
    ;
    Bool _t1684; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1684 = *_hp; free(_hp); }
    (void)_t1684;
    if (_t1684) {
        Str *_t1639 = Str_lit("Return", 6ULL);
        (void)_t1639;
        ;
        return _t1639;
    }
    ;
    Bool _t1685; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1685 = *_hp; free(_hp); }
    (void)_t1685;
    if (_t1685) {
        Str *_t1640 = Str_lit("If", 2ULL);
        (void)_t1640;
        ;
        return _t1640;
    }
    ;
    Bool _t1686; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1686 = *_hp; free(_hp); }
    (void)_t1686;
    if (_t1686) {
        Str *_t1641 = Str_lit("While", 5ULL);
        (void)_t1641;
        ;
        return _t1641;
    }
    ;
    Bool _t1687; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1687 = *_hp; free(_hp); }
    (void)_t1687;
    if (_t1687) {
        Str *_t1642 = Str_lit("Str", 3ULL);
        (void)_t1642;
        U64 _t1643; { U64 *_hp = (U64 *)Str_size(); _t1643 = *_hp; free(_hp); }
        (void)_t1643;
        U64 _t1644 = 3;
        (void)_t1644;
        Array *_va32 = Array_new(_t1642, &(U64){_t1643}, &(U64){_t1644});
        (void)_va32;
        Str_delete(_t1642, &(Bool){1});
        ;
        ;
        U64 _t1645 = 0;
        (void)_t1645;
        Str *_t1646 = Str_lit("ForIn(", 6ULL);
        (void)_t1646;
        Array_set(_va32, &(U64){_t1645}, _t1646);
        ;
        Str *_t1647 = ExprData_get_ForIn(self);
        (void)_t1647;
        U64 _t1648 = 1;
        (void)_t1648;
        Str *_t1649 = Str_to_str(_t1647);
        (void)_t1649;
        Str_delete(_t1647, &(Bool){1});
        Array_set(_va32, &(U64){_t1648}, _t1649);
        ;
        U64 _t1650 = 2;
        (void)_t1650;
        Str *_t1651 = Str_lit(")", 1ULL);
        (void)_t1651;
        Array_set(_va32, &(U64){_t1650}, _t1651);
        ;
        Str *_t1652 = format(_va32);
        (void)_t1652;
        ;
        return _t1652;
    }
    ;
    Bool _t1688; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1688 = *_hp; free(_hp); }
    (void)_t1688;
    if (_t1688) {
        Str *_t1653 = Str_lit("Str", 3ULL);
        (void)_t1653;
        U64 _t1654; { U64 *_hp = (U64 *)Str_size(); _t1654 = *_hp; free(_hp); }
        (void)_t1654;
        U64 _t1655 = 3;
        (void)_t1655;
        Array *_va33 = Array_new(_t1653, &(U64){_t1654}, &(U64){_t1655});
        (void)_va33;
        Str_delete(_t1653, &(Bool){1});
        ;
        ;
        U64 _t1656 = 0;
        (void)_t1656;
        Str *_t1657 = Str_lit("NamedArg(", 9ULL);
        (void)_t1657;
        Array_set(_va33, &(U64){_t1656}, _t1657);
        ;
        Str *_t1658 = ExprData_get_NamedArg(self);
        (void)_t1658;
        U64 _t1659 = 1;
        (void)_t1659;
        Str *_t1660 = Str_to_str(_t1658);
        (void)_t1660;
        Str_delete(_t1658, &(Bool){1});
        Array_set(_va33, &(U64){_t1659}, _t1660);
        ;
        U64 _t1661 = 2;
        (void)_t1661;
        Str *_t1662 = Str_lit(")", 1ULL);
        (void)_t1662;
        Array_set(_va33, &(U64){_t1661}, _t1662);
        ;
        Str *_t1663 = format(_va33);
        (void)_t1663;
        ;
        return _t1663;
    }
    ;
    Bool _t1689; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1689 = *_hp; free(_hp); }
    (void)_t1689;
    if (_t1689) {
        Str *_t1664 = Str_lit("Break", 5ULL);
        (void)_t1664;
        ;
        return _t1664;
    }
    ;
    Bool _t1690; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1690 = *_hp; free(_hp); }
    (void)_t1690;
    if (_t1690) {
        Str *_t1665 = Str_lit("Continue", 8ULL);
        (void)_t1665;
        ;
        return _t1665;
    }
    ;
    Bool _t1691; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1691 = *_hp; free(_hp); }
    (void)_t1691;
    if (_t1691) {
        Str *_t1666 = Str_lit("MapLit", 6ULL);
        (void)_t1666;
        ;
        return _t1666;
    }
    ;
    Bool _t1692; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1692 = *_hp; free(_hp); }
    (void)_t1692;
    if (_t1692) {
        Str *_t1667 = Str_lit("SetLit", 6ULL);
        (void)_t1667;
        ;
        return _t1667;
    }
    ;
    Bool _t1693; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1693 = *_hp; free(_hp); }
    (void)_t1693;
    if (_t1693) {
        Str *_t1668 = Str_lit("Switch", 6ULL);
        (void)_t1668;
        ;
        return _t1668;
    }
    ;
    Bool _t1694; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1694 = *_hp; free(_hp); }
    (void)_t1694;
    if (_t1694) {
        Str *_t1669 = Str_lit("Case", 4ULL);
        (void)_t1669;
        ;
        return _t1669;
    }
    ;
    Str *_t1695 = Str_lit("unknown", 7ULL);
    (void)_t1695;
    return _t1695;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t1697 = Str_lit("Str", 3ULL);
    (void)_t1697;
    U64 _t1698; { U64 *_hp = (U64 *)Str_size(); _t1698 = *_hp; free(_hp); }
    (void)_t1698;
    U64 _t1699 = 7;
    (void)_t1699;
    Array *_va34 = Array_new(_t1697, &(U64){_t1698}, &(U64){_t1699});
    (void)_va34;
    Str_delete(_t1697, &(Bool){1});
    ;
    ;
    U64 _t1700 = 0;
    (void)_t1700;
    Str *_t1701 = Str_clone(&self->path);
    (void)_t1701;
    Array_set(_va34, &(U64){_t1700}, _t1701);
    ;
    U64 _t1702 = 1;
    (void)_t1702;
    Str *_t1703 = Str_lit(":", 1ULL);
    (void)_t1703;
    Array_set(_va34, &(U64){_t1702}, _t1703);
    ;
    U64 _t1704 = 2;
    (void)_t1704;
    Str *_t1705 = U32_to_str(&self->line);
    (void)_t1705;
    Array_set(_va34, &(U64){_t1704}, _t1705);
    ;
    U64 _t1706 = 3;
    (void)_t1706;
    Str *_t1707 = Str_lit(":", 1ULL);
    (void)_t1707;
    Array_set(_va34, &(U64){_t1706}, _t1707);
    ;
    U64 _t1708 = 4;
    (void)_t1708;
    Str *_t1709 = U32_to_str(&self->col);
    (void)_t1709;
    Array_set(_va34, &(U64){_t1708}, _t1709);
    ;
    U64 _t1710 = 5;
    (void)_t1710;
    Str *_t1711 = Str_lit(": error: ", 9ULL);
    (void)_t1711;
    Array_set(_va34, &(U64){_t1710}, _t1711);
    ;
    U64 _t1712 = 6;
    (void)_t1712;
    Str *_t1713 = Str_clone(msg);
    (void)_t1713;
    Array_set(_va34, &(U64){_t1712}, _t1713);
    ;
    println(_va34);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1714 = Str_lit("Str", 3ULL);
    (void)_t1714;
    U64 _t1715; { U64 *_hp = (U64 *)Str_size(); _t1715 = *_hp; free(_hp); }
    (void)_t1715;
    U64 _t1716 = 1;
    (void)_t1716;
    Array *_va35 = Array_new(_t1714, &(U64){_t1715}, &(U64){_t1716});
    (void)_va35;
    Str_delete(_t1714, &(Bool){1});
    ;
    ;
    U64 _t1717 = 0;
    (void)_t1717;
    Str *_t1718 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t1718;
    Array_set(_va35, &(U64){_t1717}, _t1718);
    ;
    println(_va35);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1719 = Str_lit("Str", 3ULL);
    (void)_t1719;
    U64 _t1720; { U64 *_hp = (U64 *)Str_size(); _t1720 = *_hp; free(_hp); }
    (void)_t1720;
    U64 _t1721 = 1;
    (void)_t1721;
    Array *_va36 = Array_new(_t1719, &(U64){_t1720}, &(U64){_t1721});
    (void)_va36;
    Str_delete(_t1719, &(Bool){1});
    ;
    ;
    U64 _t1722 = 0;
    (void)_t1722;
    Str *_t1723 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t1723;
    Array_set(_va36, &(U64){_t1722}, _t1723);
    ;
    println(_va36);
}

void Expr_add_child(Expr * self, Expr * child) {
    (void)self;
    (void)child;
    Vec_push(&self->children, child);
}

Expr * Expr_child(Expr * parent, I64 * i) {
    (void)parent;
    (void)i;
    U64 *_t1724 = malloc(sizeof(U64)); *_t1724 = I64_to_u64(DEREF(i));
    (void)_t1724;
    Expr *c = Vec_get(&parent->children, _t1724);
    (void)c;
    U64_delete(_t1724, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t1725; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t1725 = *_hp; free(_hp); }
    (void)_t1725;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t1725; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t1726 = 0;
    (void)_t1726;
    I64 _t1727 = 1;
    (void)_t1727;
    I64 _t1728 = I64_sub(_t1726, _t1727);
    (void)_t1728;
    ;
    ;
    I64 _t1729 = 0;
    (void)_t1729;
    I64 _t1730 = 1;
    (void)_t1730;
    I64 _t1731 = I64_sub(_t1729, _t1730);
    (void)_t1731;
    ;
    ;
    Str *_t1732 = Str_lit("", 0ULL);
    (void)_t1732;
    U64 _t1733; { U64 *_hp = (U64 *)Expr_size(); _t1733 = *_hp; free(_hp); }
    (void)_t1733;
    Bool _t1734 = 0;
    (void)_t1734;
    Bool _t1735 = 0;
    (void)_t1735;
    Bool _t1736 = 0;
    (void)_t1736;
    Bool _t1737 = 0;
    (void)_t1737;
    Bool _t1738 = 0;
    (void)_t1738;
    Bool _t1739 = 0;
    (void)_t1739;
    Bool _t1740 = 0;
    (void)_t1740;
    Bool _t1741 = 0;
    (void)_t1741;
    I32 _t1742 = 0;
    (void)_t1742;
    I32 _t1743 = I64_to_i32(_t1728);
    (void)_t1743;
    ;
    U32 _t1744 = 0;
    (void)_t1744;
    I32 _t1745 = I64_to_i32(_t1731);
    (void)_t1745;
    ;
    U32 _t1746 = 0;
    (void)_t1746;
    U32 _t1747 = U32_clone(&(U32){col});
    (void)_t1747;
    Str *_t1748 = Str_clone(path);
    (void)_t1748;
    Expr *_t1749 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t1749->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t1749->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1749->struct_name = *_ca; free(_ca); }
    _t1749->is_own_arg = _t1734;
    _t1749->is_splat = _t1735;
    _t1749->is_own_field = _t1736;
    _t1749->is_ref_field = _t1737;
    _t1749->is_ns_field = _t1738;
    _t1749->is_ext = _t1739;
    _t1749->is_core = _t1740;
    _t1749->save_old_delete = _t1741;
    _t1749->total_struct_size = _t1742;
    _t1749->variadic_index = _t1743;
    _t1749->variadic_count = _t1744;
    _t1749->kwargs_index = _t1745;
    _t1749->kwargs_count = _t1746;
    _t1749->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t1732, &(U64){_t1733}); _t1749->children = *_ca; free(_ca); }
    _t1749->line = U32_clone(&(U32){line});
    _t1749->col = _t1747;
    { Str *_ca = Str_clone(_t1748); _t1749->path = *_ca; free(_ca); }
    (void)_t1749;
    Str_delete(_t1732, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t1748, &(Bool){1});
    return _t1749;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t1757 = Str_lit("", 0ULL);
    (void)_t1757;
    U64 _t1758; { U64 *_hp = (U64 *)Expr_size(); _t1758 = *_hp; free(_hp); }
    (void)_t1758;
    Vec *new_children = Vec_new(_t1757, &(U64){_t1758});
    (void)new_children;
    Str_delete(_t1757, &(Bool){1});
    ;
    {
        U64 _t1755 = 0;
        (void)_t1755;
        U64 _t1756; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1756 = *_hp; free(_hp); }
        (void)_t1756;
        Range *_fc1750 = Range_new(_t1755, _t1756);
        (void)_fc1750;
        ;
        ;
        U64 _fi1750 = 0;
        (void)_fi1750;
        while (1) {
            U64 _t1752; { U64 *_hp = (U64 *)Range_len(_fc1750); _t1752 = *_hp; free(_hp); }
            (void)_t1752;
            Bool _wcond1751; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1750}, &(U64){_t1752}); _wcond1751 = *_hp; free(_hp); }
            (void)_wcond1751;
            ;
            if (_wcond1751) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1750, _fi1750);
            (void)i;
            U64 _t1753 = 1;
            (void)_t1753;
            U64 _t1754 = U64_add(_fi1750, _t1753);
            (void)_t1754;
            ;
            _fi1750 = _t1754;
            ;
            Expr *c = Vec_get(&self->children, i);
            (void)c;
            Expr *cloned = Expr_clone(c);
            (void)cloned;
            U64_delete(i, &(Bool){1});
            Vec_push(new_children, cloned);
        }
        Range_delete(_fc1750, &(Bool){1});
        ;
    }
    Expr *_t1759 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t1759->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t1759->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t1759->struct_name = *_ca; free(_ca); }
    _t1759->is_own_arg = self->is_own_arg;
    _t1759->is_splat = self->is_splat;
    _t1759->is_own_field = self->is_own_field;
    _t1759->is_ref_field = self->is_ref_field;
    _t1759->is_ns_field = self->is_ns_field;
    _t1759->is_ext = self->is_ext;
    _t1759->is_core = self->is_core;
    _t1759->save_old_delete = self->save_old_delete;
    _t1759->total_struct_size = self->total_struct_size;
    _t1759->variadic_index = self->variadic_index;
    _t1759->variadic_count = self->variadic_count;
    _t1759->kwargs_index = self->kwargs_index;
    _t1759->kwargs_count = self->kwargs_count;
    _t1759->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t1759->children = *_ca; free(_ca); }
    _t1759->line = self->line;
    _t1759->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t1759->path = *_ca; free(_ca); }
    (void)_t1759;
    Vec_delete(new_children, &(Bool){1});
    return _t1759;
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
    Bool _t2120; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t2120 = *_hp; free(_hp); }
    (void)_t2120;
    if (_t2120) {
        Bool _t2054; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t2054 = *_hp; free(_hp); }
        (void)_t2054;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2054; return _r; }
    }
    ;
    Bool _t2121; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t2121 = *_hp; free(_hp); }
    (void)_t2121;
    if (_t2121) {
        Bool _t2055; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t2055 = *_hp; free(_hp); }
        (void)_t2055;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2055; return _r; }
    }
    ;
    Bool _t2122; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t2122 = *_hp; free(_hp); }
    (void)_t2122;
    if (_t2122) {
        Bool _t2056; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t2056 = *_hp; free(_hp); }
        (void)_t2056;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2056; return _r; }
    }
    ;
    Bool _t2123; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t2123 = *_hp; free(_hp); }
    (void)_t2123;
    if (_t2123) {
        Bool _t2057; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t2057 = *_hp; free(_hp); }
        (void)_t2057;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2057; return _r; }
    }
    ;
    Bool _t2124; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t2124 = *_hp; free(_hp); }
    (void)_t2124;
    if (_t2124) {
        Bool _t2058; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t2058 = *_hp; free(_hp); }
        (void)_t2058;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2058; return _r; }
    }
    ;
    Bool _t2125; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t2125 = *_hp; free(_hp); }
    (void)_t2125;
    if (_t2125) {
        Bool _t2059; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t2059 = *_hp; free(_hp); }
        (void)_t2059;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2059; return _r; }
    }
    ;
    Bool _t2126; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t2126 = *_hp; free(_hp); }
    (void)_t2126;
    if (_t2126) {
        Bool _t2060; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t2060 = *_hp; free(_hp); }
        (void)_t2060;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2060; return _r; }
    }
    ;
    Bool _t2127; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t2127 = *_hp; free(_hp); }
    (void)_t2127;
    if (_t2127) {
        Bool _t2061; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t2061 = *_hp; free(_hp); }
        (void)_t2061;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2061; return _r; }
    }
    ;
    Bool _t2128; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t2128 = *_hp; free(_hp); }
    (void)_t2128;
    if (_t2128) {
        Bool _t2062; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t2062 = *_hp; free(_hp); }
        (void)_t2062;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2062; return _r; }
    }
    ;
    Bool _t2129; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t2129 = *_hp; free(_hp); }
    (void)_t2129;
    if (_t2129) {
        Bool _t2063; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t2063 = *_hp; free(_hp); }
        (void)_t2063;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2063; return _r; }
    }
    ;
    Bool _t2130; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t2130 = *_hp; free(_hp); }
    (void)_t2130;
    if (_t2130) {
        Bool _t2064; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t2064 = *_hp; free(_hp); }
        (void)_t2064;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2064; return _r; }
    }
    ;
    Bool _t2131; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t2131 = *_hp; free(_hp); }
    (void)_t2131;
    if (_t2131) {
        Bool _t2065; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t2065 = *_hp; free(_hp); }
        (void)_t2065;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2065; return _r; }
    }
    ;
    Bool _t2132; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t2132 = *_hp; free(_hp); }
    (void)_t2132;
    if (_t2132) {
        Bool _t2066; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t2066 = *_hp; free(_hp); }
        (void)_t2066;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2066; return _r; }
    }
    ;
    Bool _t2133; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t2133 = *_hp; free(_hp); }
    (void)_t2133;
    if (_t2133) {
        Bool _t2067; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t2067 = *_hp; free(_hp); }
        (void)_t2067;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2067; return _r; }
    }
    ;
    Bool _t2134; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t2134 = *_hp; free(_hp); }
    (void)_t2134;
    if (_t2134) {
        Bool _t2068; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t2068 = *_hp; free(_hp); }
        (void)_t2068;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2068; return _r; }
    }
    ;
    Bool _t2135; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t2135 = *_hp; free(_hp); }
    (void)_t2135;
    if (_t2135) {
        Bool _t2069; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t2069 = *_hp; free(_hp); }
        (void)_t2069;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2069; return _r; }
    }
    ;
    Bool _t2136; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t2136 = *_hp; free(_hp); }
    (void)_t2136;
    if (_t2136) {
        Bool _t2070; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t2070 = *_hp; free(_hp); }
        (void)_t2070;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2070; return _r; }
    }
    ;
    Bool _t2137; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t2137 = *_hp; free(_hp); }
    (void)_t2137;
    if (_t2137) {
        Bool _t2071; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t2071 = *_hp; free(_hp); }
        (void)_t2071;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2071; return _r; }
    }
    ;
    Bool _t2138; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t2138 = *_hp; free(_hp); }
    (void)_t2138;
    if (_t2138) {
        Bool _t2072; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t2072 = *_hp; free(_hp); }
        (void)_t2072;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2072; return _r; }
    }
    ;
    Bool _t2139; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t2139 = *_hp; free(_hp); }
    (void)_t2139;
    if (_t2139) {
        Bool _t2073; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t2073 = *_hp; free(_hp); }
        (void)_t2073;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2073; return _r; }
    }
    ;
    Bool _t2140; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t2140 = *_hp; free(_hp); }
    (void)_t2140;
    if (_t2140) {
        Bool _t2074; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t2074 = *_hp; free(_hp); }
        (void)_t2074;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2074; return _r; }
    }
    ;
    Bool _t2141; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t2141 = *_hp; free(_hp); }
    (void)_t2141;
    if (_t2141) {
        Bool _t2075; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t2075 = *_hp; free(_hp); }
        (void)_t2075;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2075; return _r; }
    }
    ;
    Bool _t2142; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t2142 = *_hp; free(_hp); }
    (void)_t2142;
    if (_t2142) {
        Bool _t2076; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t2076 = *_hp; free(_hp); }
        (void)_t2076;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2076; return _r; }
    }
    ;
    Bool _t2143; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t2143 = *_hp; free(_hp); }
    (void)_t2143;
    if (_t2143) {
        Bool _t2077; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t2077 = *_hp; free(_hp); }
        (void)_t2077;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2077; return _r; }
    }
    ;
    Bool _t2144; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t2144 = *_hp; free(_hp); }
    (void)_t2144;
    if (_t2144) {
        Bool _t2078; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t2078 = *_hp; free(_hp); }
        (void)_t2078;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2078; return _r; }
    }
    ;
    Bool _t2145; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t2145 = *_hp; free(_hp); }
    (void)_t2145;
    if (_t2145) {
        Bool _t2079; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t2079 = *_hp; free(_hp); }
        (void)_t2079;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2079; return _r; }
    }
    ;
    Bool _t2146; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t2146 = *_hp; free(_hp); }
    (void)_t2146;
    if (_t2146) {
        Bool _t2080; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t2080 = *_hp; free(_hp); }
        (void)_t2080;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2080; return _r; }
    }
    ;
    Bool _t2147; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t2147 = *_hp; free(_hp); }
    (void)_t2147;
    if (_t2147) {
        Bool _t2081; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t2081 = *_hp; free(_hp); }
        (void)_t2081;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2081; return _r; }
    }
    ;
    Bool _t2148; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t2148 = *_hp; free(_hp); }
    (void)_t2148;
    if (_t2148) {
        Bool _t2082; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t2082 = *_hp; free(_hp); }
        (void)_t2082;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2082; return _r; }
    }
    ;
    Bool _t2149; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t2149 = *_hp; free(_hp); }
    (void)_t2149;
    if (_t2149) {
        Bool _t2083; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t2083 = *_hp; free(_hp); }
        (void)_t2083;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2083; return _r; }
    }
    ;
    Bool _t2150; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t2150 = *_hp; free(_hp); }
    (void)_t2150;
    if (_t2150) {
        Bool _t2084; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t2084 = *_hp; free(_hp); }
        (void)_t2084;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2084; return _r; }
    }
    ;
    Bool _t2151; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t2151 = *_hp; free(_hp); }
    (void)_t2151;
    if (_t2151) {
        Bool _t2085; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t2085 = *_hp; free(_hp); }
        (void)_t2085;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2085; return _r; }
    }
    ;
    Bool _t2152; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t2152 = *_hp; free(_hp); }
    (void)_t2152;
    if (_t2152) {
        Bool _t2086; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t2086 = *_hp; free(_hp); }
        (void)_t2086;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2086; return _r; }
    }
    ;
    Bool _t2153; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t2153 = *_hp; free(_hp); }
    (void)_t2153;
    if (_t2153) {
        Bool _t2087; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t2087 = *_hp; free(_hp); }
        (void)_t2087;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2087; return _r; }
    }
    ;
    Bool _t2154; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t2154 = *_hp; free(_hp); }
    (void)_t2154;
    if (_t2154) {
        Bool _t2088; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t2088 = *_hp; free(_hp); }
        (void)_t2088;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2088; return _r; }
    }
    ;
    Bool _t2155; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t2155 = *_hp; free(_hp); }
    (void)_t2155;
    if (_t2155) {
        Bool _t2089; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t2089 = *_hp; free(_hp); }
        (void)_t2089;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2089; return _r; }
    }
    ;
    Bool _t2156; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t2156 = *_hp; free(_hp); }
    (void)_t2156;
    if (_t2156) {
        Bool _t2090; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t2090 = *_hp; free(_hp); }
        (void)_t2090;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2090; return _r; }
    }
    ;
    Bool _t2157; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t2157 = *_hp; free(_hp); }
    (void)_t2157;
    if (_t2157) {
        Bool _t2091; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t2091 = *_hp; free(_hp); }
        (void)_t2091;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2091; return _r; }
    }
    ;
    Bool _t2158; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t2158 = *_hp; free(_hp); }
    (void)_t2158;
    if (_t2158) {
        Bool _t2092; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t2092 = *_hp; free(_hp); }
        (void)_t2092;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2092; return _r; }
    }
    ;
    Bool _t2159; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t2159 = *_hp; free(_hp); }
    (void)_t2159;
    if (_t2159) {
        Bool _t2093; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t2093 = *_hp; free(_hp); }
        (void)_t2093;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2093; return _r; }
    }
    ;
    Bool _t2160; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t2160 = *_hp; free(_hp); }
    (void)_t2160;
    if (_t2160) {
        Bool _t2094; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t2094 = *_hp; free(_hp); }
        (void)_t2094;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2094; return _r; }
    }
    ;
    Bool _t2161; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t2161 = *_hp; free(_hp); }
    (void)_t2161;
    if (_t2161) {
        Bool _t2095; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t2095 = *_hp; free(_hp); }
        (void)_t2095;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2095; return _r; }
    }
    ;
    Bool _t2162; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t2162 = *_hp; free(_hp); }
    (void)_t2162;
    if (_t2162) {
        Bool _t2096; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t2096 = *_hp; free(_hp); }
        (void)_t2096;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2096; return _r; }
    }
    ;
    Bool _t2163; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t2163 = *_hp; free(_hp); }
    (void)_t2163;
    if (_t2163) {
        Bool _t2097; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t2097 = *_hp; free(_hp); }
        (void)_t2097;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2097; return _r; }
    }
    ;
    Bool _t2164; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t2164 = *_hp; free(_hp); }
    (void)_t2164;
    if (_t2164) {
        Bool _t2098; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t2098 = *_hp; free(_hp); }
        (void)_t2098;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2098; return _r; }
    }
    ;
    Bool _t2165; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t2165 = *_hp; free(_hp); }
    (void)_t2165;
    if (_t2165) {
        Bool _t2099; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t2099 = *_hp; free(_hp); }
        (void)_t2099;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2099; return _r; }
    }
    ;
    Bool _t2166; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t2166 = *_hp; free(_hp); }
    (void)_t2166;
    if (_t2166) {
        Bool _t2100; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t2100 = *_hp; free(_hp); }
        (void)_t2100;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2100; return _r; }
    }
    ;
    Bool _t2167; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t2167 = *_hp; free(_hp); }
    (void)_t2167;
    if (_t2167) {
        Bool _t2101; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t2101 = *_hp; free(_hp); }
        (void)_t2101;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2101; return _r; }
    }
    ;
    Bool _t2168; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t2168 = *_hp; free(_hp); }
    (void)_t2168;
    if (_t2168) {
        Bool _t2102; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t2102 = *_hp; free(_hp); }
        (void)_t2102;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2102; return _r; }
    }
    ;
    Bool _t2169; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t2169 = *_hp; free(_hp); }
    (void)_t2169;
    if (_t2169) {
        Bool _t2103; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t2103 = *_hp; free(_hp); }
        (void)_t2103;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2103; return _r; }
    }
    ;
    Bool _t2170; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t2170 = *_hp; free(_hp); }
    (void)_t2170;
    if (_t2170) {
        Bool _t2104; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t2104 = *_hp; free(_hp); }
        (void)_t2104;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2104; return _r; }
    }
    ;
    Bool _t2171; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t2171 = *_hp; free(_hp); }
    (void)_t2171;
    if (_t2171) {
        Bool _t2105; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t2105 = *_hp; free(_hp); }
        (void)_t2105;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2105; return _r; }
    }
    ;
    Bool _t2172; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t2172 = *_hp; free(_hp); }
    (void)_t2172;
    if (_t2172) {
        Bool _t2106; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t2106 = *_hp; free(_hp); }
        (void)_t2106;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2106; return _r; }
    }
    ;
    Bool _t2173; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t2173 = *_hp; free(_hp); }
    (void)_t2173;
    if (_t2173) {
        Bool _t2107; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t2107 = *_hp; free(_hp); }
        (void)_t2107;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2107; return _r; }
    }
    ;
    Bool _t2174; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t2174 = *_hp; free(_hp); }
    (void)_t2174;
    if (_t2174) {
        Bool _t2108; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t2108 = *_hp; free(_hp); }
        (void)_t2108;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2108; return _r; }
    }
    ;
    Bool _t2175; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t2175 = *_hp; free(_hp); }
    (void)_t2175;
    if (_t2175) {
        Bool _t2109; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t2109 = *_hp; free(_hp); }
        (void)_t2109;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2109; return _r; }
    }
    ;
    Bool _t2176; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t2176 = *_hp; free(_hp); }
    (void)_t2176;
    if (_t2176) {
        Bool _t2110; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t2110 = *_hp; free(_hp); }
        (void)_t2110;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2110; return _r; }
    }
    ;
    Bool _t2177; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t2177 = *_hp; free(_hp); }
    (void)_t2177;
    if (_t2177) {
        Bool _t2111; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t2111 = *_hp; free(_hp); }
        (void)_t2111;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2111; return _r; }
    }
    ;
    Bool _t2178; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t2178 = *_hp; free(_hp); }
    (void)_t2178;
    if (_t2178) {
        Bool _t2112; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t2112 = *_hp; free(_hp); }
        (void)_t2112;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2112; return _r; }
    }
    ;
    Bool _t2179; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t2179 = *_hp; free(_hp); }
    (void)_t2179;
    if (_t2179) {
        Bool _t2113; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t2113 = *_hp; free(_hp); }
        (void)_t2113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2113; return _r; }
    }
    ;
    Bool _t2180; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t2180 = *_hp; free(_hp); }
    (void)_t2180;
    if (_t2180) {
        Bool _t2114; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t2114 = *_hp; free(_hp); }
        (void)_t2114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2114; return _r; }
    }
    ;
    Bool _t2181; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t2181 = *_hp; free(_hp); }
    (void)_t2181;
    if (_t2181) {
        Bool _t2115; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t2115 = *_hp; free(_hp); }
        (void)_t2115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2115; return _r; }
    }
    ;
    Bool _t2182; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t2182 = *_hp; free(_hp); }
    (void)_t2182;
    if (_t2182) {
        Bool _t2116; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t2116 = *_hp; free(_hp); }
        (void)_t2116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2116; return _r; }
    }
    ;
    Bool _t2183; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t2183 = *_hp; free(_hp); }
    (void)_t2183;
    if (_t2183) {
        Bool _t2117; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t2117 = *_hp; free(_hp); }
        (void)_t2117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2117; return _r; }
    }
    ;
    Bool _t2184; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t2184 = *_hp; free(_hp); }
    (void)_t2184;
    if (_t2184) {
        Bool _t2118; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t2118 = *_hp; free(_hp); }
        (void)_t2118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2118; return _r; }
    }
    ;
    Bool _t2185; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t2185 = *_hp; free(_hp); }
    (void)_t2185;
    if (_t2185) {
        Bool _t2119; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t2119 = *_hp; free(_hp); }
        (void)_t2119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2119; return _r; }
    }
    ;
    Bool _t2186 = 0;
    (void)_t2186;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2186; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t2187; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2187 = *_hp; free(_hp); }
    (void)_t2187;
    if (_t2187) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t2188; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2188 = *_hp; free(_hp); }
    (void)_t2188;
    if (_t2188) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t2189; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2189 = *_hp; free(_hp); }
    (void)_t2189;
    if (_t2189) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t2190; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2190 = *_hp; free(_hp); }
    (void)_t2190;
    if (_t2190) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t2191; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2191 = *_hp; free(_hp); }
    (void)_t2191;
    if (_t2191) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t2192; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2192 = *_hp; free(_hp); }
    (void)_t2192;
    if (_t2192) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t2193; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2193 = *_hp; free(_hp); }
    (void)_t2193;
    if (_t2193) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t2194; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2194 = *_hp; free(_hp); }
    (void)_t2194;
    if (_t2194) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t2195; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2195 = *_hp; free(_hp); }
    (void)_t2195;
    if (_t2195) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t2196; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2196 = *_hp; free(_hp); }
    (void)_t2196;
    if (_t2196) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t2197; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2197 = *_hp; free(_hp); }
    (void)_t2197;
    if (_t2197) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t2198; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2198 = *_hp; free(_hp); }
    (void)_t2198;
    if (_t2198) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t2199; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2199 = *_hp; free(_hp); }
    (void)_t2199;
    if (_t2199) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t2200; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2200 = *_hp; free(_hp); }
    (void)_t2200;
    if (_t2200) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t2201; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2201 = *_hp; free(_hp); }
    (void)_t2201;
    if (_t2201) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t2202; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2202 = *_hp; free(_hp); }
    (void)_t2202;
    if (_t2202) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t2203; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2203 = *_hp; free(_hp); }
    (void)_t2203;
    if (_t2203) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t2204; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2204 = *_hp; free(_hp); }
    (void)_t2204;
    if (_t2204) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t2205; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2205 = *_hp; free(_hp); }
    (void)_t2205;
    if (_t2205) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t2206; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t2240; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2240 = *_hp; free(_hp); }
    (void)_t2240;
    if (_t2240) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t2241; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    if (_t2241) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t2242; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    if (_t2242) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t2243; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2243 = *_hp; free(_hp); }
    (void)_t2243;
    if (_t2243) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t2244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2244 = *_hp; free(_hp); }
    (void)_t2244;
    if (_t2244) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t2245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2245 = *_hp; free(_hp); }
    (void)_t2245;
    if (_t2245) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t2246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    if (_t2246) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t2247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    if (_t2247) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t2248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2248 = *_hp; free(_hp); }
    (void)_t2248;
    if (_t2248) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t2249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2249 = *_hp; free(_hp); }
    (void)_t2249;
    if (_t2249) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t2250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2250 = *_hp; free(_hp); }
    (void)_t2250;
    if (_t2250) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t2251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2251 = *_hp; free(_hp); }
    (void)_t2251;
    if (_t2251) {
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
    Bool _t2318; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2318 = *_hp; free(_hp); }
    (void)_t2318;
    if (_t2318) {
        Str *_t2252 = Str_lit("Eof", 3ULL);
        (void)_t2252;
        ;
        return _t2252;
    }
    ;
    Bool _t2319; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2319 = *_hp; free(_hp); }
    (void)_t2319;
    if (_t2319) {
        Str *_t2253 = Str_lit("LParen", 6ULL);
        (void)_t2253;
        ;
        return _t2253;
    }
    ;
    Bool _t2320; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2320 = *_hp; free(_hp); }
    (void)_t2320;
    if (_t2320) {
        Str *_t2254 = Str_lit("RParen", 6ULL);
        (void)_t2254;
        ;
        return _t2254;
    }
    ;
    Bool _t2321; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2321 = *_hp; free(_hp); }
    (void)_t2321;
    if (_t2321) {
        Str *_t2255 = Str_lit("LBrace", 6ULL);
        (void)_t2255;
        ;
        return _t2255;
    }
    ;
    Bool _t2322; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2322 = *_hp; free(_hp); }
    (void)_t2322;
    if (_t2322) {
        Str *_t2256 = Str_lit("RBrace", 6ULL);
        (void)_t2256;
        ;
        return _t2256;
    }
    ;
    Bool _t2323; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2323 = *_hp; free(_hp); }
    (void)_t2323;
    if (_t2323) {
        Str *_t2257 = Str_lit("LBracket", 8ULL);
        (void)_t2257;
        ;
        return _t2257;
    }
    ;
    Bool _t2324; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2324 = *_hp; free(_hp); }
    (void)_t2324;
    if (_t2324) {
        Str *_t2258 = Str_lit("RBracket", 8ULL);
        (void)_t2258;
        ;
        return _t2258;
    }
    ;
    Bool _t2325; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2325 = *_hp; free(_hp); }
    (void)_t2325;
    if (_t2325) {
        Str *_t2259 = Str_lit("Comma", 5ULL);
        (void)_t2259;
        ;
        return _t2259;
    }
    ;
    Bool _t2326; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2326 = *_hp; free(_hp); }
    (void)_t2326;
    if (_t2326) {
        Str *_t2260 = Str_lit("Colon", 5ULL);
        (void)_t2260;
        ;
        return _t2260;
    }
    ;
    Bool _t2327; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2327 = *_hp; free(_hp); }
    (void)_t2327;
    if (_t2327) {
        Str *_t2261 = Str_lit("Question", 8ULL);
        (void)_t2261;
        ;
        return _t2261;
    }
    ;
    Bool _t2328; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2328 = *_hp; free(_hp); }
    (void)_t2328;
    if (_t2328) {
        Str *_t2262 = Str_lit("Bang", 4ULL);
        (void)_t2262;
        ;
        return _t2262;
    }
    ;
    Bool _t2329; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2329 = *_hp; free(_hp); }
    (void)_t2329;
    if (_t2329) {
        Str *_t2263 = Str_lit("Minus", 5ULL);
        (void)_t2263;
        ;
        return _t2263;
    }
    ;
    Bool _t2330; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2330 = *_hp; free(_hp); }
    (void)_t2330;
    if (_t2330) {
        Str *_t2264 = Str_lit("Plus", 4ULL);
        (void)_t2264;
        ;
        return _t2264;
    }
    ;
    Bool _t2331; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2331 = *_hp; free(_hp); }
    (void)_t2331;
    if (_t2331) {
        Str *_t2265 = Str_lit("Star", 4ULL);
        (void)_t2265;
        ;
        return _t2265;
    }
    ;
    Bool _t2332; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2332 = *_hp; free(_hp); }
    (void)_t2332;
    if (_t2332) {
        Str *_t2266 = Str_lit("Slash", 5ULL);
        (void)_t2266;
        ;
        return _t2266;
    }
    ;
    Bool _t2333; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2333 = *_hp; free(_hp); }
    (void)_t2333;
    if (_t2333) {
        Str *_t2267 = Str_lit("Dot", 3ULL);
        (void)_t2267;
        ;
        return _t2267;
    }
    ;
    Bool _t2334; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2334 = *_hp; free(_hp); }
    (void)_t2334;
    if (_t2334) {
        Str *_t2268 = Str_lit("DotDot", 6ULL);
        (void)_t2268;
        ;
        return _t2268;
    }
    ;
    Bool _t2335; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2335 = *_hp; free(_hp); }
    (void)_t2335;
    if (_t2335) {
        Str *_t2269 = Str_lit("DotDotDot", 9ULL);
        (void)_t2269;
        ;
        return _t2269;
    }
    ;
    Bool _t2336; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2336 = *_hp; free(_hp); }
    (void)_t2336;
    if (_t2336) {
        Str *_t2270 = Str_lit("Eq", 2ULL);
        (void)_t2270;
        ;
        return _t2270;
    }
    ;
    Bool _t2337; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2337 = *_hp; free(_hp); }
    (void)_t2337;
    if (_t2337) {
        Str *_t2271 = Str_lit("EqEq", 4ULL);
        (void)_t2271;
        ;
        return _t2271;
    }
    ;
    Bool _t2338; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2338 = *_hp; free(_hp); }
    (void)_t2338;
    if (_t2338) {
        Str *_t2272 = Str_lit("Neq", 3ULL);
        (void)_t2272;
        ;
        return _t2272;
    }
    ;
    Bool _t2339; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2339 = *_hp; free(_hp); }
    (void)_t2339;
    if (_t2339) {
        Str *_t2273 = Str_lit("Lt", 2ULL);
        (void)_t2273;
        ;
        return _t2273;
    }
    ;
    Bool _t2340; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2340 = *_hp; free(_hp); }
    (void)_t2340;
    if (_t2340) {
        Str *_t2274 = Str_lit("LtEq", 4ULL);
        (void)_t2274;
        ;
        return _t2274;
    }
    ;
    Bool _t2341; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2341 = *_hp; free(_hp); }
    (void)_t2341;
    if (_t2341) {
        Str *_t2275 = Str_lit("Gt", 2ULL);
        (void)_t2275;
        ;
        return _t2275;
    }
    ;
    Bool _t2342; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2342 = *_hp; free(_hp); }
    (void)_t2342;
    if (_t2342) {
        Str *_t2276 = Str_lit("GtEq", 4ULL);
        (void)_t2276;
        ;
        return _t2276;
    }
    ;
    Bool _t2343; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2343 = *_hp; free(_hp); }
    (void)_t2343;
    if (_t2343) {
        Str *_t2277 = Str_lit("ColonEq", 7ULL);
        (void)_t2277;
        ;
        return _t2277;
    }
    ;
    Bool _t2344; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2344 = *_hp; free(_hp); }
    (void)_t2344;
    if (_t2344) {
        Str *_t2278 = Str_lit("Ident", 5ULL);
        (void)_t2278;
        ;
        return _t2278;
    }
    ;
    Bool _t2345; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2345 = *_hp; free(_hp); }
    (void)_t2345;
    if (_t2345) {
        Str *_t2279 = Str_lit("StringTok", 9ULL);
        (void)_t2279;
        ;
        return _t2279;
    }
    ;
    Bool _t2346; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2346 = *_hp; free(_hp); }
    (void)_t2346;
    if (_t2346) {
        Str *_t2280 = Str_lit("Number", 6ULL);
        (void)_t2280;
        ;
        return _t2280;
    }
    ;
    Bool _t2347; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2347 = *_hp; free(_hp); }
    (void)_t2347;
    if (_t2347) {
        Str *_t2281 = Str_lit("Char", 4ULL);
        (void)_t2281;
        ;
        return _t2281;
    }
    ;
    Bool _t2348; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2348 = *_hp; free(_hp); }
    (void)_t2348;
    if (_t2348) {
        Str *_t2282 = Str_lit("KwMode", 6ULL);
        (void)_t2282;
        ;
        return _t2282;
    }
    ;
    Bool _t2349; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2349 = *_hp; free(_hp); }
    (void)_t2349;
    if (_t2349) {
        Str *_t2283 = Str_lit("KwMut", 5ULL);
        (void)_t2283;
        ;
        return _t2283;
    }
    ;
    Bool _t2350; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2350 = *_hp; free(_hp); }
    (void)_t2350;
    if (_t2350) {
        Str *_t2284 = Str_lit("KwOwn", 5ULL);
        (void)_t2284;
        ;
        return _t2284;
    }
    ;
    Bool _t2351; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2351 = *_hp; free(_hp); }
    (void)_t2351;
    if (_t2351) {
        Str *_t2285 = Str_lit("KwRef", 5ULL);
        (void)_t2285;
        ;
        return _t2285;
    }
    ;
    Bool _t2352; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2352 = *_hp; free(_hp); }
    (void)_t2352;
    if (_t2352) {
        Str *_t2286 = Str_lit("KwShallow", 9ULL);
        (void)_t2286;
        ;
        return _t2286;
    }
    ;
    Bool _t2353; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2353 = *_hp; free(_hp); }
    (void)_t2353;
    if (_t2353) {
        Str *_t2287 = Str_lit("KwStruct", 8ULL);
        (void)_t2287;
        ;
        return _t2287;
    }
    ;
    Bool _t2354; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2354 = *_hp; free(_hp); }
    (void)_t2354;
    if (_t2354) {
        Str *_t2288 = Str_lit("KwExtStruct", 11ULL);
        (void)_t2288;
        ;
        return _t2288;
    }
    ;
    Bool _t2355; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2355 = *_hp; free(_hp); }
    (void)_t2355;
    if (_t2355) {
        Str *_t2289 = Str_lit("KwEnum", 6ULL);
        (void)_t2289;
        ;
        return _t2289;
    }
    ;
    Bool _t2356; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2356 = *_hp; free(_hp); }
    (void)_t2356;
    if (_t2356) {
        Str *_t2290 = Str_lit("KwNamespace", 11ULL);
        (void)_t2290;
        ;
        return _t2290;
    }
    ;
    Bool _t2357; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2357 = *_hp; free(_hp); }
    (void)_t2357;
    if (_t2357) {
        Str *_t2291 = Str_lit("KwFunc", 6ULL);
        (void)_t2291;
        ;
        return _t2291;
    }
    ;
    Bool _t2358; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2358 = *_hp; free(_hp); }
    (void)_t2358;
    if (_t2358) {
        Str *_t2292 = Str_lit("KwProc", 6ULL);
        (void)_t2292;
        ;
        return _t2292;
    }
    ;
    Bool _t2359; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2359 = *_hp; free(_hp); }
    (void)_t2359;
    if (_t2359) {
        Str *_t2293 = Str_lit("KwTest", 6ULL);
        (void)_t2293;
        ;
        return _t2293;
    }
    ;
    Bool _t2360; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2360 = *_hp; free(_hp); }
    (void)_t2360;
    if (_t2360) {
        Str *_t2294 = Str_lit("KwMacro", 7ULL);
        (void)_t2294;
        ;
        return _t2294;
    }
    ;
    Bool _t2361; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2361 = *_hp; free(_hp); }
    (void)_t2361;
    if (_t2361) {
        Str *_t2295 = Str_lit("KwExtFunc", 9ULL);
        (void)_t2295;
        ;
        return _t2295;
    }
    ;
    Bool _t2362; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2362 = *_hp; free(_hp); }
    (void)_t2362;
    if (_t2362) {
        Str *_t2296 = Str_lit("KwExtProc", 9ULL);
        (void)_t2296;
        ;
        return _t2296;
    }
    ;
    Bool _t2363; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2363 = *_hp; free(_hp); }
    (void)_t2363;
    if (_t2363) {
        Str *_t2297 = Str_lit("KwReturns", 9ULL);
        (void)_t2297;
        ;
        return _t2297;
    }
    ;
    Bool _t2364; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2364 = *_hp; free(_hp); }
    (void)_t2364;
    if (_t2364) {
        Str *_t2298 = Str_lit("KwThrows", 8ULL);
        (void)_t2298;
        ;
        return _t2298;
    }
    ;
    Bool _t2365; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2365 = *_hp; free(_hp); }
    (void)_t2365;
    if (_t2365) {
        Str *_t2299 = Str_lit("KwIf", 4ULL);
        (void)_t2299;
        ;
        return _t2299;
    }
    ;
    Bool _t2366; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2366 = *_hp; free(_hp); }
    (void)_t2366;
    if (_t2366) {
        Str *_t2300 = Str_lit("KwElse", 6ULL);
        (void)_t2300;
        ;
        return _t2300;
    }
    ;
    Bool _t2367; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2367 = *_hp; free(_hp); }
    (void)_t2367;
    if (_t2367) {
        Str *_t2301 = Str_lit("KwWhile", 7ULL);
        (void)_t2301;
        ;
        return _t2301;
    }
    ;
    Bool _t2368; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2368 = *_hp; free(_hp); }
    (void)_t2368;
    if (_t2368) {
        Str *_t2302 = Str_lit("KwFor", 5ULL);
        (void)_t2302;
        ;
        return _t2302;
    }
    ;
    Bool _t2369; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2369 = *_hp; free(_hp); }
    (void)_t2369;
    if (_t2369) {
        Str *_t2303 = Str_lit("KwIn", 4ULL);
        (void)_t2303;
        ;
        return _t2303;
    }
    ;
    Bool _t2370; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2370 = *_hp; free(_hp); }
    (void)_t2370;
    if (_t2370) {
        Str *_t2304 = Str_lit("KwSwitch", 8ULL);
        (void)_t2304;
        ;
        return _t2304;
    }
    ;
    Bool _t2371; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2371 = *_hp; free(_hp); }
    (void)_t2371;
    if (_t2371) {
        Str *_t2305 = Str_lit("KwMatch", 7ULL);
        (void)_t2305;
        ;
        return _t2305;
    }
    ;
    Bool _t2372; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2372 = *_hp; free(_hp); }
    (void)_t2372;
    if (_t2372) {
        Str *_t2306 = Str_lit("KwCase", 6ULL);
        (void)_t2306;
        ;
        return _t2306;
    }
    ;
    Bool _t2373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2373 = *_hp; free(_hp); }
    (void)_t2373;
    if (_t2373) {
        Str *_t2307 = Str_lit("KwDefault", 9ULL);
        (void)_t2307;
        ;
        return _t2307;
    }
    ;
    Bool _t2374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2374 = *_hp; free(_hp); }
    (void)_t2374;
    if (_t2374) {
        Str *_t2308 = Str_lit("KwReturn", 8ULL);
        (void)_t2308;
        ;
        return _t2308;
    }
    ;
    Bool _t2375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2375 = *_hp; free(_hp); }
    (void)_t2375;
    if (_t2375) {
        Str *_t2309 = Str_lit("KwThrow", 7ULL);
        (void)_t2309;
        ;
        return _t2309;
    }
    ;
    Bool _t2376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2376 = *_hp; free(_hp); }
    (void)_t2376;
    if (_t2376) {
        Str *_t2310 = Str_lit("KwCatch", 7ULL);
        (void)_t2310;
        ;
        return _t2310;
    }
    ;
    Bool _t2377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2377 = *_hp; free(_hp); }
    (void)_t2377;
    if (_t2377) {
        Str *_t2311 = Str_lit("KwBreak", 7ULL);
        (void)_t2311;
        ;
        return _t2311;
    }
    ;
    Bool _t2378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2378 = *_hp; free(_hp); }
    (void)_t2378;
    if (_t2378) {
        Str *_t2312 = Str_lit("KwContinue", 10ULL);
        (void)_t2312;
        ;
        return _t2312;
    }
    ;
    Bool _t2379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2379 = *_hp; free(_hp); }
    (void)_t2379;
    if (_t2379) {
        Str *_t2313 = Str_lit("KwDefer", 7ULL);
        (void)_t2313;
        ;
        return _t2313;
    }
    ;
    Bool _t2380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2380 = *_hp; free(_hp); }
    (void)_t2380;
    if (_t2380) {
        Str *_t2314 = Str_lit("KwTrue", 6ULL);
        (void)_t2314;
        ;
        return _t2314;
    }
    ;
    Bool _t2381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2381 = *_hp; free(_hp); }
    (void)_t2381;
    if (_t2381) {
        Str *_t2315 = Str_lit("KwFalse", 7ULL);
        (void)_t2315;
        ;
        return _t2315;
    }
    ;
    Bool _t2382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2382 = *_hp; free(_hp); }
    (void)_t2382;
    if (_t2382) {
        Str *_t2316 = Str_lit("KwNull", 6ULL);
        (void)_t2316;
        ;
        return _t2316;
    }
    ;
    Bool _t2383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t2383 = *_hp; free(_hp); }
    (void)_t2383;
    if (_t2383) {
        Str *_t2317 = Str_lit("Error", 5ULL);
        (void)_t2317;
        ;
        return _t2317;
    }
    ;
    Str *_t2384 = Str_lit("unknown", 7ULL);
    (void)_t2384;
    return _t2384;
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

void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) {
        if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return (void*)EnumDef_delete;
        if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return (void*)U8_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return (void*)I16_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return (void*)I32_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return (void*)F32_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return (void*)U32_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return (void*)U64_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return (void*)I64_delete;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void*)Range_delete;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void*)Bool_delete;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void*)Array_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) return (void*)Map_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void*)Set_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void*)Str_delete;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void*)Vec_delete;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0) return (void*)Tuple_delete;
        if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) return (void*)TilType_delete;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) return (void*)Declaration_delete;
        if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return (void*)FuncType_delete;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0) return (void*)Param_delete;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return (void*)FunctionDef_delete;
        if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) return (void*)ExprData_delete;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return (void*)Expr_delete;
        if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) return (void*)TokenType_delete;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return (void*)Token_delete;
        if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0) return (void*)Parser_delete;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0) return (void*)TypeBinding_delete;
        if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) return (void*)TypeScope_delete;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) return (void*)Mode_delete;
    }
    if (method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) {
        if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return (void*)EnumDef_clone;
        if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return (void*)U8_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return (void*)I16_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return (void*)I32_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return (void*)F32_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return (void*)U32_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return (void*)U64_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return (void*)I64_clone;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void*)Range_clone;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void*)Bool_clone;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void*)Array_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) return (void*)Map_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void*)Set_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void*)Str_clone;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void*)Vec_clone;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0) return (void*)Tuple_clone;
        if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) return (void*)TilType_clone;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) return (void*)Declaration_clone;
        if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return (void*)FuncType_clone;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0) return (void*)Param_clone;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return (void*)FunctionDef_clone;
        if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) return (void*)ExprData_clone;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return (void*)Expr_clone;
        if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) return (void*)TokenType_clone;
        if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return (void*)Token_clone;
        if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0) return (void*)Parser_clone;
        if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0) return (void*)TypeBinding_clone;
        if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) return (void*)TypeScope_clone;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) return (void*)Mode_clone;
    }
    if (method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) {
        if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return (void*)U8_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return (void*)I16_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return (void*)I32_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return (void*)F32_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return (void*)U32_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return (void*)U64_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return (void*)I64_cmp;
        if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void*)Bool_cmp;
        if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void*)Str_cmp;
    }
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
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
        _t4152 = malloc(sizeof(I64));
    *_t4152 = 0;
    (void)_t4152;
    _t4153 = malloc(sizeof(I64));
    *_t4153 = 1;
    (void)_t4153;
    _t4154 = malloc(sizeof(I64)); *_t4154 = I64_sub(DEREF(_t4152), DEREF(_t4153));
    (void)_t4154;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4154));
    (void)CAP_LIT;
    _t4155 = malloc(sizeof(I64));
    *_t4155 = 0;
    (void)_t4155;
    _t4156 = malloc(sizeof(I64));
    *_t4156 = 2;
    (void)_t4156;
    _t4157 = malloc(sizeof(I64)); *_t4157 = I64_sub(DEREF(_t4155), DEREF(_t4156));
    (void)_t4157;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4157));
    (void)CAP_VIEW;
    _t4158 = Str_lit("Str", 3ULL);
    (void)_t4158;
    _t4159 = Str_size();
    (void)_t4159;
    _t4160 = Str_lit("Mode", 4ULL);
    (void)_t4160;
    _t4161 = Mode_size();
    (void)_t4161;
    core_modes = Map_new(_t4158, _t4159, _t4160, _t4161);
    (void)core_modes;
    _t4162 = malloc(sizeof(Bool));
    *_t4162 = 0;
    (void)_t4162;
    _t4163 = malloc(sizeof(Bool));
    *_t4163 = 0;
    (void)_t4163;
    _t4164 = malloc(sizeof(Bool));
    *_t4164 = 0;
    (void)_t4164;
    _t4165 = malloc(sizeof(Bool));
    *_t4165 = 0;
    (void)_t4165;
    _t4166 = Str_lit("script", 6ULL);
    (void)_t4166;
    _t4167 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4167->name = *_ca; free(_ca); }
    _t4167->needs_main = DEREF(_t4162);
    _t4167->decls_only = DEREF(_t4163);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4167->auto_import = *_ca; free(_ca); }
    _t4167->is_pure = DEREF(_t4164);
    _t4167->debug_prints = DEREF(_t4165);
    (void)_t4167;
    Map_set(core_modes, _t4166, _t4167);
    _t4168 = malloc(sizeof(Bool));
    *_t4168 = 1;
    (void)_t4168;
    _t4169 = malloc(sizeof(Bool));
    *_t4169 = 1;
    (void)_t4169;
    _t4170 = malloc(sizeof(Bool));
    *_t4170 = 0;
    (void)_t4170;
    _t4171 = malloc(sizeof(Bool));
    *_t4171 = 0;
    (void)_t4171;
    _t4172 = Str_lit("cli", 3ULL);
    (void)_t4172;
    _t4173 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4173->name = *_ca; free(_ca); }
    _t4173->needs_main = DEREF(_t4168);
    _t4173->decls_only = DEREF(_t4169);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4173->auto_import = *_ca; free(_ca); }
    _t4173->is_pure = DEREF(_t4170);
    _t4173->debug_prints = DEREF(_t4171);
    (void)_t4173;
    Map_set(core_modes, _t4172, _t4173);
    _t4174 = malloc(sizeof(Bool));
    *_t4174 = 1;
    (void)_t4174;
    _t4175 = malloc(sizeof(Bool));
    *_t4175 = 1;
    (void)_t4175;
    _t4176 = malloc(sizeof(Bool));
    *_t4176 = 0;
    (void)_t4176;
    _t4177 = malloc(sizeof(Bool));
    *_t4177 = 0;
    (void)_t4177;
    _t4178 = Str_lit("gui", 3ULL);
    (void)_t4178;
    _t4179 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4179->name = *_ca; free(_ca); }
    _t4179->needs_main = DEREF(_t4174);
    _t4179->decls_only = DEREF(_t4175);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4179->auto_import = *_ca; free(_ca); }
    _t4179->is_pure = DEREF(_t4176);
    _t4179->debug_prints = DEREF(_t4177);
    (void)_t4179;
    Map_set(core_modes, _t4178, _t4179);
    _t4180 = malloc(sizeof(Bool));
    *_t4180 = 0;
    (void)_t4180;
    _t4181 = malloc(sizeof(Bool));
    *_t4181 = 1;
    (void)_t4181;
    _t4182 = malloc(sizeof(Bool));
    *_t4182 = 0;
    (void)_t4182;
    _t4183 = malloc(sizeof(Bool));
    *_t4183 = 0;
    (void)_t4183;
    _t4184 = Str_lit("test", 4ULL);
    (void)_t4184;
    _t4185 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4185->name = *_ca; free(_ca); }
    _t4185->needs_main = DEREF(_t4180);
    _t4185->decls_only = DEREF(_t4181);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4185->auto_import = *_ca; free(_ca); }
    _t4185->is_pure = DEREF(_t4182);
    _t4185->debug_prints = DEREF(_t4183);
    (void)_t4185;
    Map_set(core_modes, _t4184, _t4185);
    _t4186 = malloc(sizeof(Bool));
    *_t4186 = 0;
    (void)_t4186;
    _t4187 = malloc(sizeof(Bool));
    *_t4187 = 1;
    (void)_t4187;
    _t4188 = malloc(sizeof(Bool));
    *_t4188 = 1;
    (void)_t4188;
    _t4189 = malloc(sizeof(Bool));
    *_t4189 = 0;
    (void)_t4189;
    _t4190 = Str_lit("pure", 4ULL);
    (void)_t4190;
    _t4191 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4191->name = *_ca; free(_ca); }
    _t4191->needs_main = DEREF(_t4186);
    _t4191->decls_only = DEREF(_t4187);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4191->auto_import = *_ca; free(_ca); }
    _t4191->is_pure = DEREF(_t4188);
    _t4191->debug_prints = DEREF(_t4189);
    (void)_t4191;
    Map_set(core_modes, _t4190, _t4191);
    _t4192 = malloc(sizeof(Bool));
    *_t4192 = 0;
    (void)_t4192;
    _t4193 = malloc(sizeof(Bool));
    *_t4193 = 1;
    (void)_t4193;
    _t4194 = malloc(sizeof(Bool));
    *_t4194 = 1;
    (void)_t4194;
    _t4195 = malloc(sizeof(Bool));
    *_t4195 = 1;
    (void)_t4195;
    _t4196 = Str_lit("pura", 4ULL);
    (void)_t4196;
    _t4197 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4197->name = *_ca; free(_ca); }
    _t4197->needs_main = DEREF(_t4192);
    _t4197->decls_only = DEREF(_t4193);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4197->auto_import = *_ca; free(_ca); }
    _t4197->is_pure = DEREF(_t4194);
    _t4197->debug_prints = DEREF(_t4195);
    (void)_t4197;
    Map_set(core_modes, _t4196, _t4197);
    _t4198 = malloc(sizeof(Bool));
    *_t4198 = 0;
    (void)_t4198;
    _t4199 = malloc(sizeof(Bool));
    *_t4199 = 1;
    (void)_t4199;
    _t4200 = malloc(sizeof(Bool));
    *_t4200 = 0;
    (void)_t4200;
    _t4201 = malloc(sizeof(Bool));
    *_t4201 = 0;
    (void)_t4201;
    _t4202 = Str_lit("lib", 3ULL);
    (void)_t4202;
    _t4203 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4203->name = *_ca; free(_ca); }
    _t4203->needs_main = DEREF(_t4198);
    _t4203->decls_only = DEREF(_t4199);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4203->auto_import = *_ca; free(_ca); }
    _t4203->is_pure = DEREF(_t4200);
    _t4203->debug_prints = DEREF(_t4201);
    (void)_t4203;
    Map_set(core_modes, _t4202, _t4203);
    _t4204 = malloc(sizeof(Bool));
    *_t4204 = 0;
    (void)_t4204;
    _t4205 = malloc(sizeof(Bool));
    *_t4205 = 1;
    (void)_t4205;
    _t4206 = malloc(sizeof(Bool));
    *_t4206 = 0;
    (void)_t4206;
    _t4207 = malloc(sizeof(Bool));
    *_t4207 = 1;
    (void)_t4207;
    _t4208 = Str_lit("liba", 4ULL);
    (void)_t4208;
    _t4209 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4209->name = *_ca; free(_ca); }
    _t4209->needs_main = DEREF(_t4204);
    _t4209->decls_only = DEREF(_t4205);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4209->auto_import = *_ca; free(_ca); }
    _t4209->is_pure = DEREF(_t4206);
    _t4209->debug_prints = DEREF(_t4207);
    (void)_t4209;
    Map_set(core_modes, _t4208, _t4209);
}

