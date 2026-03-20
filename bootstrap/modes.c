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

static I64 *_t4135;
static I64 *_t4136;
static I64 *_t4137;
static U64 *CAP_LIT;
static I64 *_t4138;
static I64 *_t4139;
static I64 *_t4140;
static U64 *CAP_VIEW;
static Str *_t4141;
static U64 *_t4142;
static Str *_t4143;
static U64 *_t4144;
static Map *core_modes;
static Bool *_t4145;
static Bool *_t4146;
static Bool *_t4147;
static Bool *_t4148;
static Str *_t4149;
static Mode *_t4150;
static Bool *_t4151;
static Bool *_t4152;
static Bool *_t4153;
static Bool *_t4154;
static Str *_t4155;
static Mode *_t4156;
static Bool *_t4157;
static Bool *_t4158;
static Bool *_t4159;
static Bool *_t4160;
static Str *_t4161;
static Mode *_t4162;
static Bool *_t4163;
static Bool *_t4164;
static Bool *_t4165;
static Bool *_t4166;
static Str *_t4167;
static Mode *_t4168;
static Bool *_t4169;
static Bool *_t4170;
static Bool *_t4171;
static Bool *_t4172;
static Str *_t4173;
static Mode *_t4174;
static Bool *_t4175;
static Bool *_t4176;
static Bool *_t4177;
static Bool *_t4178;
static Str *_t4179;
static Mode *_t4180;
static Bool *_t4181;
static Bool *_t4182;
static Bool *_t4183;
static Bool *_t4184;
static Str *_t4185;
static Mode *_t4186;
static Bool *_t4187;
static Bool *_t4188;
static Bool *_t4189;
static Bool *_t4190;
static Str *_t4191;
static Mode *_t4192;

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
    void *_t384 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t384;
    U64 _t385 = U64_clone(cap);
    (void)_t385;
    U64 _t386 = U64_clone(elem_size);
    (void)_t386;
    Array *_t387 = malloc(sizeof(Array));
    _t387->data = _t384;
    _t387->cap = _t385;
    _t387->elem_size = _t386;
    { Str *_ca = Str_clone(elem_type); _t387->elem_type = *_ca; free(_ca); }
    (void)_t387;
    ;
    ;
    return _t387;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t402; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t402 = *_hp; free(_hp); }
    (void)_t402;
    if (_t402) {
        Str *_t388 = Str_lit("Str", 3ULL);
        (void)_t388;
        U64 _t389; { U64 *_hp = (U64 *)Str_size(); _t389 = *_hp; free(_hp); }
        (void)_t389;
        U64 _t390 = 5;
        (void)_t390;
        Array *_va7 = Array_new(_t388, &(U64){_t389}, &(U64){_t390});
        (void)_va7;
        Str_delete(_t388, &(Bool){1});
        ;
        ;
        U64 _t391 = 0;
        (void)_t391;
        Str *_t392 = Str_lit("Array.get: index ", 17ULL);
        (void)_t392;
        Array_set(_va7, &(U64){_t391}, _t392);
        ;
        U64 _t393 = 1;
        (void)_t393;
        Str *_t394 = U64_to_str(DEREF(i));
        (void)_t394;
        Array_set(_va7, &(U64){_t393}, _t394);
        ;
        U64 _t395 = 2;
        (void)_t395;
        Str *_t396 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t396;
        Array_set(_va7, &(U64){_t395}, _t396);
        ;
        U64 _t397 = 3;
        (void)_t397;
        Str *_t398 = U64_to_str(self->cap);
        (void)_t398;
        Array_set(_va7, &(U64){_t397}, _t398);
        ;
        U64 _t399 = 4;
        (void)_t399;
        Str *_t400 = Str_lit(")", 1ULL);
        (void)_t400;
        Array_set(_va7, &(U64){_t399}, _t400);
        ;
        Str *_t401 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t401;
        panic(_t401, _va7);
        Str_delete(_t401, &(Bool){1});
    }
    ;
    U64 *_t403 = malloc(sizeof(U64)); *_t403 = U64_mul(DEREF(i), self->elem_size);
    (void)_t403;
    void *_t404 = ptr_add(self->data, DEREF(_t403));
    (void)_t404;
    U64_delete(_t403, &(Bool){1});
    return _t404;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t419; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t419 = *_hp; free(_hp); }
    (void)_t419;
    if (_t419) {
        Str *_t405 = Str_lit("Str", 3ULL);
        (void)_t405;
        U64 _t406; { U64 *_hp = (U64 *)Str_size(); _t406 = *_hp; free(_hp); }
        (void)_t406;
        U64 _t407 = 5;
        (void)_t407;
        Array *_va8 = Array_new(_t405, &(U64){_t406}, &(U64){_t407});
        (void)_va8;
        Str_delete(_t405, &(Bool){1});
        ;
        ;
        U64 _t408 = 0;
        (void)_t408;
        Str *_t409 = Str_lit("Array.set: index ", 17ULL);
        (void)_t409;
        Array_set(_va8, &(U64){_t408}, _t409);
        ;
        U64 _t410 = 1;
        (void)_t410;
        Str *_t411 = U64_to_str(DEREF(i));
        (void)_t411;
        Array_set(_va8, &(U64){_t410}, _t411);
        ;
        U64 _t412 = 2;
        (void)_t412;
        Str *_t413 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t413;
        Array_set(_va8, &(U64){_t412}, _t413);
        ;
        U64 _t414 = 3;
        (void)_t414;
        Str *_t415 = U64_to_str(self->cap);
        (void)_t415;
        Array_set(_va8, &(U64){_t414}, _t415);
        ;
        U64 _t416 = 4;
        (void)_t416;
        Str *_t417 = Str_lit(")", 1ULL);
        (void)_t417;
        Array_set(_va8, &(U64){_t416}, _t417);
        ;
        Str *_t418 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t418;
        panic(_t418, _va8);
        Str_delete(_t418, &(Bool){1});
    }
    ;
    U64 *_t420 = malloc(sizeof(U64)); *_t420 = U64_mul(DEREF(i), self->elem_size);
    (void)_t420;
    void *_t421 = ptr_add(self->data, DEREF(_t420));
    (void)_t421;
    Bool _t422 = 0;
    (void)_t422;
    dyn_call_delete(&self->elem_type, _t421, &(Bool){_t422});
    U64_delete(_t420, &(Bool){1});
    ;
    U64 *_t423 = malloc(sizeof(U64)); *_t423 = U64_mul(DEREF(i), self->elem_size);
    (void)_t423;
    void *_t424 = ptr_add(self->data, DEREF(_t423));
    (void)_t424;
    memcpy(_t424, val, self->elem_size);
    U64_delete(_t423, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    {
        U64 _t433 = 0;
        (void)_t433;
        Range *_fc425 = Range_new(_t433, self->cap);
        (void)_fc425;
        ;
        U64 _fi425 = 0;
        (void)_fi425;
        while (1) {
            U64 _t427; { U64 *_hp = (U64 *)Range_len(_fc425); _t427 = *_hp; free(_hp); }
            (void)_t427;
            Bool _wcond426; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi425}, &(U64){_t427}); _wcond426 = *_hp; free(_hp); }
            (void)_wcond426;
            ;
            if (_wcond426) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc425, _fi425); i = *_hp; free(_hp); }
            (void)i;
            U64 _t428 = 1;
            (void)_t428;
            U64 _t429 = U64_add(_fi425, _t428);
            (void)_t429;
            ;
            _fi425 = _t429;
            ;
            U64 *_t430 = malloc(sizeof(U64)); *_t430 = U64_mul(i, self->elem_size);
            (void)_t430;
            ;
            void *_t431 = ptr_add(self->data, DEREF(_t430));
            (void)_t431;
            Bool _t432 = 0;
            (void)_t432;
            dyn_call_delete(&self->elem_type, _t431, &(Bool){_t432});
            U64_delete(_t430, &(Bool){1});
            ;
        }
        Range_delete(_fc425, &(Bool){1});
        ;
    }
    free(self->data);
    Bool _t434 = 0;
    (void)_t434;
    Str_delete(&self->elem_type, &(Bool){_t434});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t445 = U64_mul(self->cap, self->elem_size);
    (void)_t445;
    U8 *new_data = malloc(_t445);
    (void)new_data;
    ;
    {
        U64 _t444 = 0;
        (void)_t444;
        Range *_fc435 = Range_new(_t444, self->cap);
        (void)_fc435;
        ;
        U64 _fi435 = 0;
        (void)_fi435;
        while (1) {
            U64 _t437; { U64 *_hp = (U64 *)Range_len(_fc435); _t437 = *_hp; free(_hp); }
            (void)_t437;
            Bool _wcond436; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi435}, &(U64){_t437}); _wcond436 = *_hp; free(_hp); }
            (void)_wcond436;
            ;
            if (_wcond436) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc435, _fi435); i = *_hp; free(_hp); }
            (void)i;
            U64 _t438 = 1;
            (void)_t438;
            U64 _t439 = U64_add(_fi435, _t438);
            (void)_t439;
            ;
            _fi435 = _t439;
            ;
            U64 *_t440 = malloc(sizeof(U64)); *_t440 = U64_mul(i, self->elem_size);
            (void)_t440;
            void *_t441 = ptr_add(self->data, DEREF(_t440));
            (void)_t441;
            void *cloned = dyn_call_clone(&self->elem_type, _t441);
            (void)cloned;
            U64_delete(_t440, &(Bool){1});
            U64 *_t442 = malloc(sizeof(U64)); *_t442 = U64_mul(i, self->elem_size);
            (void)_t442;
            ;
            void *_t443 = ptr_add(new_data, DEREF(_t442));
            (void)_t443;
            memcpy(_t443, cloned, self->elem_size);
            U64_delete(_t442, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc435, &(Bool){1});
        ;
    }
    Array *_t446 = malloc(sizeof(Array));
    _t446->data = new_data;
    _t446->cap = self->cap;
    _t446->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t446->elem_type = *_ca; free(_ca); }
    (void)_t446;
    return _t446;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t460; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t460 = *_hp; free(_hp); }
    (void)_t460;
    Bool _t461 = Bool_not(_t460);
    (void)_t461;
    ;
    if (_t461) {
        Bool _t458 = dyn_has_cmp(key_type);
        (void)_t458;
        Bool _t459 = Bool_not(_t458);
        (void)_t459;
        ;
        if (_t459) {
            Str *_t448 = Str_lit("Str", 3ULL);
            (void)_t448;
            U64 _t449; { U64 *_hp = (U64 *)Str_size(); _t449 = *_hp; free(_hp); }
            (void)_t449;
            U64 _t450 = 3;
            (void)_t450;
            Array *_va9 = Array_new(_t448, &(U64){_t449}, &(U64){_t450});
            (void)_va9;
            Str_delete(_t448, &(Bool){1});
            ;
            ;
            U64 _t451 = 0;
            (void)_t451;
            Str *_t452 = Str_lit("Map.new: type ", 14ULL);
            (void)_t452;
            Array_set(_va9, &(U64){_t451}, _t452);
            ;
            U64 _t453 = 1;
            (void)_t453;
            Str *_t454 = Str_clone(key_type);
            (void)_t454;
            Array_set(_va9, &(U64){_t453}, _t454);
            ;
            U64 _t455 = 2;
            (void)_t455;
            Str *_t456 = Str_lit(" must implement cmp", 19ULL);
            (void)_t456;
            Array_set(_va9, &(U64){_t455}, _t456);
            ;
            Str *_t457 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t457;
            panic(_t457, _va9);
            Str_delete(_t457, &(Bool){1});
        }
        ;
    }
    ;
    void *_t462 = malloc(DEREF(key_size));
    (void)_t462;
    void *_t463 = malloc(DEREF(val_size));
    (void)_t463;
    U64 _t464 = 0;
    (void)_t464;
    I64 _t465 = 1;
    (void)_t465;
    U64 _t466 = U64_clone(key_size);
    (void)_t466;
    U64 _t467 = U64_clone(val_size);
    (void)_t467;
    Map *_t468 = malloc(sizeof(Map));
    _t468->key_data = _t462;
    _t468->val_data = _t463;
    _t468->count = _t464;
    _t468->cap = _t465;
    _t468->key_size = _t466;
    { Str *_ca = Str_clone(key_type); _t468->key_type = *_ca; free(_ca); }
    _t468->val_size = _t467;
    { Str *_ca = Str_clone(val_type); _t468->val_type = *_ca; free(_ca); }
    (void)_t468;
    ;
    ;
    ;
    ;
    return _t468;
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
        Bool _wcond469; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond469 = *_hp; free(_hp); }
        (void)_wcond469;
        if (_wcond469) {
        } else {
            ;
            break;
        }
        ;
        U64 _t476 = U64_sub(hi, lo);
        (void)_t476;
        U64 _t477 = 2;
        (void)_t477;
        U64 _t478 = U64_div(_t476, _t477);
        (void)_t478;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t478);
        (void)mid;
        ;
        U64 *_t479 = malloc(sizeof(U64)); *_t479 = U64_mul(DEREF(mid), self->key_size);
        (void)_t479;
        void *_t480 = ptr_add(self->key_data, DEREF(_t479));
        (void)_t480;
        I64 *c = dyn_call_cmp(&self->key_type, _t480, key);
        (void)c;
        U64_delete(_t479, &(Bool){1});
        I64 _t481 = 0;
        (void)_t481;
        Bool _t482; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t481}); _t482 = *_hp; free(_hp); }
        (void)_t482;
        ;
        if (_t482) {
            U64 _t470 = 1;
            (void)_t470;
            U64 _t471 = U64_add(DEREF(mid), _t470);
            (void)_t471;
            ;
            lo = _t471;
            ;
        } else {
            I64 _t474 = 0;
            (void)_t474;
            Bool _t475; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t474}); _t475 = *_hp; free(_hp); }
            (void)_t475;
            ;
            if (_t475) {
                U64 _t472 = U64_clone(mid);
                (void)_t472;
                hi = _t472;
                ;
            } else {
                Bool _t473 = 1;
                (void)_t473;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t473; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t483 = 0;
    (void)_t483;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t483; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond484; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond484 = *_hp; free(_hp); }
        (void)_wcond484;
        if (_wcond484) {
        } else {
            ;
            break;
        }
        ;
        U64 _t492 = U64_sub(hi, lo);
        (void)_t492;
        U64 _t493 = 2;
        (void)_t493;
        U64 _t494 = U64_div(_t492, _t493);
        (void)_t494;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t494);
        (void)mid;
        ;
        U64 *_t495 = malloc(sizeof(U64)); *_t495 = U64_mul(DEREF(mid), self->key_size);
        (void)_t495;
        void *_t496 = ptr_add(self->key_data, DEREF(_t495));
        (void)_t496;
        I64 *c = dyn_call_cmp(&self->key_type, _t496, key);
        (void)c;
        U64_delete(_t495, &(Bool){1});
        I64 _t497 = 0;
        (void)_t497;
        Bool _t498; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t497}); _t498 = *_hp; free(_hp); }
        (void)_t498;
        ;
        if (_t498) {
            U64 _t485 = 1;
            (void)_t485;
            U64 _t486 = U64_add(DEREF(mid), _t485);
            (void)_t486;
            ;
            lo = _t486;
            ;
        } else {
            I64 _t490 = 0;
            (void)_t490;
            Bool _t491; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t490}); _t491 = *_hp; free(_hp); }
            (void)_t491;
            ;
            if (_t491) {
                U64 _t487 = U64_clone(mid);
                (void)_t487;
                hi = _t487;
                ;
            } else {
                U64 *_t488 = malloc(sizeof(U64)); *_t488 = U64_mul(DEREF(mid), self->val_size);
                (void)_t488;
                void *_t489 = ptr_add(self->val_data, DEREF(_t488));
                (void)_t489;
                U64_delete(_t488, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t489;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t499 = Str_lit("Str", 3ULL);
    (void)_t499;
    U64 _t500; { U64 *_hp = (U64 *)Str_size(); _t500 = *_hp; free(_hp); }
    (void)_t500;
    U64 _t501 = 1;
    (void)_t501;
    Array *_va10 = Array_new(_t499, &(U64){_t500}, &(U64){_t501});
    (void)_va10;
    Str_delete(_t499, &(Bool){1});
    ;
    ;
    U64 _t502 = 0;
    (void)_t502;
    Str *_t503 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t503;
    Array_set(_va10, &(U64){_t502}, _t503);
    ;
    Str *_t504 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t504;
    panic(_t504, _va10);
    Str_delete(_t504, &(Bool){1});
    U64 *_t505 = malloc(sizeof(U64));
    *_t505 = 0;
    (void)_t505;
    void *_t506 = ptr_add(self->val_data, DEREF(_t505));
    (void)_t506;
    U64_delete(_t505, &(Bool){1});
    return _t506;
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
        Bool _wcond507; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond507 = *_hp; free(_hp); }
        (void)_wcond507;
        if (_wcond507) {
        } else {
            ;
            break;
        }
        ;
        U64 _t516 = U64_sub(hi, lo);
        (void)_t516;
        U64 _t517 = 2;
        (void)_t517;
        U64 _t518 = U64_div(_t516, _t517);
        (void)_t518;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t518);
        (void)mid;
        ;
        U64 *_t519 = malloc(sizeof(U64)); *_t519 = U64_mul(DEREF(mid), self->key_size);
        (void)_t519;
        void *_t520 = ptr_add(self->key_data, DEREF(_t519));
        (void)_t520;
        I64 *c = dyn_call_cmp(&self->key_type, _t520, key);
        (void)c;
        U64_delete(_t519, &(Bool){1});
        I64 _t521 = 0;
        (void)_t521;
        Bool _t522; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t521}); _t522 = *_hp; free(_hp); }
        (void)_t522;
        ;
        if (_t522) {
            U64 _t508 = 1;
            (void)_t508;
            U64 _t509 = U64_add(DEREF(mid), _t508);
            (void)_t509;
            ;
            lo = _t509;
            ;
        } else {
            I64 _t514 = 0;
            (void)_t514;
            Bool _t515; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t514}); _t515 = *_hp; free(_hp); }
            (void)_t515;
            ;
            if (_t515) {
                U64 _t510 = U64_clone(mid);
                (void)_t510;
                hi = _t510;
                ;
            } else {
                Bool _t511 = 1;
                (void)_t511;
                found = _t511;
                ;
                U64 _t512 = U64_clone(mid);
                (void)_t512;
                lo = _t512;
                ;
                U64 _t513 = U64_clone(mid);
                (void)_t513;
                hi = _t513;
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
        Bool _t527; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t527 = *_hp; free(_hp); }
        (void)_t527;
        Bool _t528 = Bool_not(_t527);
        (void)_t528;
        ;
        if (_t528) {
            Bool _t523 = 0;
            (void)_t523;
            dyn_call_delete(&self->key_type, key, &(Bool){_t523});
            ;
        }
        ;
        free(key);
        Bool _t529; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t529 = *_hp; free(_hp); }
        (void)_t529;
        Bool _t530 = Bool_not(_t529);
        (void)_t530;
        ;
        if (_t530) {
            U64 *_t524 = malloc(sizeof(U64)); *_t524 = U64_mul(lo, self->val_size);
            (void)_t524;
            void *_t525 = ptr_add(self->val_data, DEREF(_t524));
            (void)_t525;
            Bool _t526 = 0;
            (void)_t526;
            dyn_call_delete(&self->val_type, _t525, &(Bool){_t526});
            U64_delete(_t524, &(Bool){1});
            ;
        }
        ;
        U64 *_t531 = malloc(sizeof(U64)); *_t531 = U64_mul(lo, self->val_size);
        (void)_t531;
        void *_t532 = ptr_add(self->val_data, DEREF(_t531));
        (void)_t532;
        memcpy(_t532, val, self->val_size);
        U64_delete(_t531, &(Bool){1});
        free(val);
    } else {
        Bool _t539 = U64_eq(self->count, self->cap);
        (void)_t539;
        if (_t539) {
            U64 _t533 = 2;
            (void)_t533;
            U64 new_cap = U64_mul(self->cap, _t533);
            (void)new_cap;
            ;
            U64 _t534 = U64_mul(new_cap, self->key_size);
            (void)_t534;
            void *_t535 = realloc(self->key_data, _t534);
            (void)_t535;
            ;
            self->key_data = _t535;
            U64 _t536 = U64_mul(new_cap, self->val_size);
            (void)_t536;
            void *_t537 = realloc(self->val_data, _t536);
            (void)_t537;
            ;
            self->val_data = _t537;
            U64 _t538 = U64_clone(&(U64){new_cap});
            (void)_t538;
            ;
            self->cap = _t538;
            ;
        }
        ;
        U64 _t540 = 1;
        (void)_t540;
        U64 _t541 = U64_add(lo, _t540);
        (void)_t541;
        ;
        U64 *_t542 = malloc(sizeof(U64)); *_t542 = U64_mul(_t541, self->key_size);
        (void)_t542;
        ;
        U64 *_t543 = malloc(sizeof(U64)); *_t543 = U64_mul(lo, self->key_size);
        (void)_t543;
        U64 _t544 = U64_sub(self->count, lo);
        (void)_t544;
        void *_t545 = ptr_add(self->key_data, DEREF(_t542));
        (void)_t545;
        void *_t546 = ptr_add(self->key_data, DEREF(_t543));
        (void)_t546;
        U64 _t547 = U64_mul(_t544, self->key_size);
        (void)_t547;
        ;
        memmove(_t545, _t546, _t547);
        U64_delete(_t542, &(Bool){1});
        U64_delete(_t543, &(Bool){1});
        ;
        U64 _t548 = 1;
        (void)_t548;
        U64 _t549 = U64_add(lo, _t548);
        (void)_t549;
        ;
        U64 *_t550 = malloc(sizeof(U64)); *_t550 = U64_mul(_t549, self->val_size);
        (void)_t550;
        ;
        U64 *_t551 = malloc(sizeof(U64)); *_t551 = U64_mul(lo, self->val_size);
        (void)_t551;
        U64 _t552 = U64_sub(self->count, lo);
        (void)_t552;
        void *_t553 = ptr_add(self->val_data, DEREF(_t550));
        (void)_t553;
        void *_t554 = ptr_add(self->val_data, DEREF(_t551));
        (void)_t554;
        U64 _t555 = U64_mul(_t552, self->val_size);
        (void)_t555;
        ;
        memmove(_t553, _t554, _t555);
        U64_delete(_t550, &(Bool){1});
        U64_delete(_t551, &(Bool){1});
        ;
        U64 *_t556 = malloc(sizeof(U64)); *_t556 = U64_mul(lo, self->key_size);
        (void)_t556;
        void *_t557 = ptr_add(self->key_data, DEREF(_t556));
        (void)_t557;
        memcpy(_t557, key, self->key_size);
        U64_delete(_t556, &(Bool){1});
        U64 *_t558 = malloc(sizeof(U64)); *_t558 = U64_mul(lo, self->val_size);
        (void)_t558;
        void *_t559 = ptr_add(self->val_data, DEREF(_t558));
        (void)_t559;
        memcpy(_t559, val, self->val_size);
        U64_delete(_t558, &(Bool){1});
        free(key);
        free(val);
        U64 _t560 = 1;
        (void)_t560;
        U64 _t561 = U64_add(self->count, _t560);
        (void)_t561;
        ;
        self->count = _t561;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t582; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t582 = *_hp; free(_hp); }
    (void)_t582;
    Bool _t583 = Bool_not(_t582);
    (void)_t583;
    ;
    if (_t583) {
        {
            U64 _t570 = 0;
            (void)_t570;
            Range *_fc562 = Range_new(_t570, self->count);
            (void)_fc562;
            ;
            U64 _fi562 = 0;
            (void)_fi562;
            while (1) {
                U64 _t564; { U64 *_hp = (U64 *)Range_len(_fc562); _t564 = *_hp; free(_hp); }
                (void)_t564;
                Bool _wcond563; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi562}, &(U64){_t564}); _wcond563 = *_hp; free(_hp); }
                (void)_wcond563;
                ;
                if (_wcond563) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc562, _fi562); i = *_hp; free(_hp); }
                (void)i;
                U64 _t565 = 1;
                (void)_t565;
                U64 _t566 = U64_add(_fi562, _t565);
                (void)_t566;
                ;
                _fi562 = _t566;
                ;
                U64 *_t567 = malloc(sizeof(U64)); *_t567 = U64_mul(i, self->key_size);
                (void)_t567;
                ;
                void *_t568 = ptr_add(self->key_data, DEREF(_t567));
                (void)_t568;
                Bool _t569 = 0;
                (void)_t569;
                dyn_call_delete(&self->key_type, _t568, &(Bool){_t569});
                U64_delete(_t567, &(Bool){1});
                ;
            }
            Range_delete(_fc562, &(Bool){1});
            ;
        }
    }
    ;
    Bool _t584; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t584 = *_hp; free(_hp); }
    (void)_t584;
    Bool _t585 = Bool_not(_t584);
    (void)_t585;
    ;
    if (_t585) {
        {
            U64 _t579 = 0;
            (void)_t579;
            Range *_fc571 = Range_new(_t579, self->count);
            (void)_fc571;
            ;
            U64 _fi571 = 0;
            (void)_fi571;
            while (1) {
                U64 _t573; { U64 *_hp = (U64 *)Range_len(_fc571); _t573 = *_hp; free(_hp); }
                (void)_t573;
                Bool _wcond572; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi571}, &(U64){_t573}); _wcond572 = *_hp; free(_hp); }
                (void)_wcond572;
                ;
                if (_wcond572) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc571, _fi571); i = *_hp; free(_hp); }
                (void)i;
                U64 _t574 = 1;
                (void)_t574;
                U64 _t575 = U64_add(_fi571, _t574);
                (void)_t575;
                ;
                _fi571 = _t575;
                ;
                U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_mul(i, self->val_size);
                (void)_t576;
                ;
                void *_t577 = ptr_add(self->val_data, DEREF(_t576));
                (void)_t577;
                Bool _t578 = 0;
                (void)_t578;
                dyn_call_delete(&self->val_type, _t577, &(Bool){_t578});
                U64_delete(_t576, &(Bool){1});
                ;
            }
            Range_delete(_fc571, &(Bool){1});
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t586; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t586 = *_hp; free(_hp); }
    (void)_t586;
    Bool _t587 = Bool_not(_t586);
    (void)_t587;
    ;
    if (_t587) {
        Bool _t580 = 0;
        (void)_t580;
        Str_delete(&self->key_type, &(Bool){_t580});
        ;
    }
    ;
    Bool _t588; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t588 = *_hp; free(_hp); }
    (void)_t588;
    Bool _t589 = Bool_not(_t588);
    (void)_t589;
    ;
    if (_t589) {
        Bool _t581 = 0;
        (void)_t581;
        Str_delete(&self->val_type, &(Bool){_t581});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t604 = U64_mul(self->cap, self->key_size);
    (void)_t604;
    U8 *new_keys = malloc(_t604);
    (void)new_keys;
    ;
    U64 _t605 = U64_mul(self->cap, self->val_size);
    (void)_t605;
    U8 *new_vals = malloc(_t605);
    (void)new_vals;
    ;
    {
        U64 _t603 = 0;
        (void)_t603;
        Range *_fc590 = Range_new(_t603, self->count);
        (void)_fc590;
        ;
        U64 _fi590 = 0;
        (void)_fi590;
        while (1) {
            U64 _t592; { U64 *_hp = (U64 *)Range_len(_fc590); _t592 = *_hp; free(_hp); }
            (void)_t592;
            Bool _wcond591; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi590}, &(U64){_t592}); _wcond591 = *_hp; free(_hp); }
            (void)_wcond591;
            ;
            if (_wcond591) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc590, _fi590); i = *_hp; free(_hp); }
            (void)i;
            U64 _t593 = 1;
            (void)_t593;
            U64 _t594 = U64_add(_fi590, _t593);
            (void)_t594;
            ;
            _fi590 = _t594;
            ;
            U64 *_t595 = malloc(sizeof(U64)); *_t595 = U64_mul(i, self->key_size);
            (void)_t595;
            void *_t596 = ptr_add(self->key_data, DEREF(_t595));
            (void)_t596;
            void *ck = dyn_call_clone(&self->key_type, _t596);
            (void)ck;
            U64_delete(_t595, &(Bool){1});
            U64 *_t597 = malloc(sizeof(U64)); *_t597 = U64_mul(i, self->key_size);
            (void)_t597;
            void *_t598 = ptr_add(new_keys, DEREF(_t597));
            (void)_t598;
            memcpy(_t598, ck, self->key_size);
            U64_delete(_t597, &(Bool){1});
            free(ck);
            U64 *_t599 = malloc(sizeof(U64)); *_t599 = U64_mul(i, self->val_size);
            (void)_t599;
            void *_t600 = ptr_add(self->val_data, DEREF(_t599));
            (void)_t600;
            void *cv = dyn_call_clone(&self->val_type, _t600);
            (void)cv;
            U64_delete(_t599, &(Bool){1});
            U64 *_t601 = malloc(sizeof(U64)); *_t601 = U64_mul(i, self->val_size);
            (void)_t601;
            ;
            void *_t602 = ptr_add(new_vals, DEREF(_t601));
            (void)_t602;
            memcpy(_t602, cv, self->val_size);
            U64_delete(_t601, &(Bool){1});
            free(cv);
        }
        Range_delete(_fc590, &(Bool){1});
        ;
    }
    Map *_t606 = malloc(sizeof(Map));
    _t606->key_data = new_keys;
    _t606->val_data = new_vals;
    _t606->count = self->count;
    _t606->cap = self->cap;
    _t606->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t606->key_type = *_ca; free(_ca); }
    _t606->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t606->val_type = *_ca; free(_ca); }
    (void)_t606;
    return _t606;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t620; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t620 = *_hp; free(_hp); }
    (void)_t620;
    Bool _t621 = Bool_not(_t620);
    (void)_t621;
    ;
    if (_t621) {
        Bool _t618 = dyn_has_cmp(elem_type);
        (void)_t618;
        Bool _t619 = Bool_not(_t618);
        (void)_t619;
        ;
        if (_t619) {
            Str *_t608 = Str_lit("Str", 3ULL);
            (void)_t608;
            U64 _t609; { U64 *_hp = (U64 *)Str_size(); _t609 = *_hp; free(_hp); }
            (void)_t609;
            U64 _t610 = 3;
            (void)_t610;
            Array *_va11 = Array_new(_t608, &(U64){_t609}, &(U64){_t610});
            (void)_va11;
            Str_delete(_t608, &(Bool){1});
            ;
            ;
            U64 _t611 = 0;
            (void)_t611;
            Str *_t612 = Str_lit("Set.new: type ", 14ULL);
            (void)_t612;
            Array_set(_va11, &(U64){_t611}, _t612);
            ;
            U64 _t613 = 1;
            (void)_t613;
            Str *_t614 = Str_clone(elem_type);
            (void)_t614;
            Array_set(_va11, &(U64){_t613}, _t614);
            ;
            U64 _t615 = 2;
            (void)_t615;
            Str *_t616 = Str_lit(" must implement cmp", 19ULL);
            (void)_t616;
            Array_set(_va11, &(U64){_t615}, _t616);
            ;
            Str *_t617 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t617;
            panic(_t617, _va11);
            Str_delete(_t617, &(Bool){1});
        }
        ;
    }
    ;
    void *_t622 = malloc(DEREF(elem_size));
    (void)_t622;
    U64 _t623 = 0;
    (void)_t623;
    I64 _t624 = 1;
    (void)_t624;
    U64 _t625 = U64_clone(elem_size);
    (void)_t625;
    Set *_t626 = malloc(sizeof(Set));
    _t626->data = _t622;
    _t626->count = _t623;
    _t626->cap = _t624;
    _t626->elem_size = _t625;
    { Str *_ca = Str_clone(elem_type); _t626->elem_type = *_ca; free(_ca); }
    (void)_t626;
    ;
    ;
    ;
    return _t626;
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
        Bool _wcond627; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond627 = *_hp; free(_hp); }
        (void)_wcond627;
        if (_wcond627) {
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
            U64 _t628 = 1;
            (void)_t628;
            U64 _t629 = U64_add(DEREF(mid), _t628);
            (void)_t629;
            ;
            lo = _t629;
            ;
        } else {
            I64 _t632 = 0;
            (void)_t632;
            Bool _t633; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t632}); _t633 = *_hp; free(_hp); }
            (void)_t633;
            ;
            if (_t633) {
                U64 _t630 = U64_clone(mid);
                (void)_t630;
                hi = _t630;
                ;
            } else {
                Bool _t631 = 1;
                (void)_t631;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t631; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t641 = 0;
    (void)_t641;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t641; return _r; }
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
        Bool _wcond642; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond642 = *_hp; free(_hp); }
        (void)_wcond642;
        if (_wcond642) {
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
            U64 _t643 = 1;
            (void)_t643;
            U64 _t644 = U64_add(DEREF(mid), _t643);
            (void)_t644;
            ;
            lo = _t644;
            ;
        } else {
            I64 _t649 = 0;
            (void)_t649;
            Bool _t650; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t649}); _t650 = *_hp; free(_hp); }
            (void)_t650;
            ;
            if (_t650) {
                U64 _t645 = U64_clone(mid);
                (void)_t645;
                hi = _t645;
                ;
            } else {
                Bool _t646 = 1;
                (void)_t646;
                found = _t646;
                ;
                U64 _t647 = U64_clone(mid);
                (void)_t647;
                lo = _t647;
                ;
                U64 _t648 = U64_clone(mid);
                (void)_t648;
                hi = _t648;
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
        Bool _t659; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t659 = *_hp; free(_hp); }
        (void)_t659;
        Bool _t660 = Bool_not(_t659);
        (void)_t660;
        ;
        if (_t660) {
            Bool _t658 = 0;
            (void)_t658;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t658});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t665 = U64_eq(self->count, self->cap);
        (void)_t665;
        if (_t665) {
            U64 _t661 = 2;
            (void)_t661;
            U64 new_cap = U64_mul(self->cap, _t661);
            (void)new_cap;
            ;
            U64 _t662 = U64_mul(new_cap, self->elem_size);
            (void)_t662;
            void *_t663 = realloc(self->data, _t662);
            (void)_t663;
            ;
            self->data = _t663;
            U64 _t664 = U64_clone(&(U64){new_cap});
            (void)_t664;
            ;
            self->cap = _t664;
            ;
        }
        ;
        U64 _t666 = 1;
        (void)_t666;
        U64 _t667 = U64_add(lo, _t666);
        (void)_t667;
        ;
        U64 *_t668 = malloc(sizeof(U64)); *_t668 = U64_mul(_t667, self->elem_size);
        (void)_t668;
        ;
        U64 *_t669 = malloc(sizeof(U64)); *_t669 = U64_mul(lo, self->elem_size);
        (void)_t669;
        U64 _t670 = U64_sub(self->count, lo);
        (void)_t670;
        void *_t671 = ptr_add(self->data, DEREF(_t668));
        (void)_t671;
        void *_t672 = ptr_add(self->data, DEREF(_t669));
        (void)_t672;
        U64 _t673 = U64_mul(_t670, self->elem_size);
        (void)_t673;
        ;
        memmove(_t671, _t672, _t673);
        U64_delete(_t668, &(Bool){1});
        U64_delete(_t669, &(Bool){1});
        ;
        U64 *_t674 = malloc(sizeof(U64)); *_t674 = U64_mul(lo, self->elem_size);
        (void)_t674;
        void *_t675 = ptr_add(self->data, DEREF(_t674));
        (void)_t675;
        memcpy(_t675, val, self->elem_size);
        U64_delete(_t674, &(Bool){1});
        free(val);
        U64 _t676 = 1;
        (void)_t676;
        U64 _t677 = U64_add(self->count, _t676);
        (void)_t677;
        ;
        self->count = _t677;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t688; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t688 = *_hp; free(_hp); }
    (void)_t688;
    Bool _t689 = Bool_not(_t688);
    (void)_t689;
    ;
    if (_t689) {
        {
            U64 _t686 = 0;
            (void)_t686;
            Range *_fc678 = Range_new(_t686, self->count);
            (void)_fc678;
            ;
            U64 _fi678 = 0;
            (void)_fi678;
            while (1) {
                U64 _t680; { U64 *_hp = (U64 *)Range_len(_fc678); _t680 = *_hp; free(_hp); }
                (void)_t680;
                Bool _wcond679; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi678}, &(U64){_t680}); _wcond679 = *_hp; free(_hp); }
                (void)_wcond679;
                ;
                if (_wcond679) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc678, _fi678); i = *_hp; free(_hp); }
                (void)i;
                U64 _t681 = 1;
                (void)_t681;
                U64 _t682 = U64_add(_fi678, _t681);
                (void)_t682;
                ;
                _fi678 = _t682;
                ;
                U64 *_t683 = malloc(sizeof(U64)); *_t683 = U64_mul(i, self->elem_size);
                (void)_t683;
                ;
                void *_t684 = ptr_add(self->data, DEREF(_t683));
                (void)_t684;
                Bool _t685 = 0;
                (void)_t685;
                dyn_call_delete(&self->elem_type, _t684, &(Bool){_t685});
                U64_delete(_t683, &(Bool){1});
                ;
            }
            Range_delete(_fc678, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t690; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t690 = *_hp; free(_hp); }
    (void)_t690;
    Bool _t691 = Bool_not(_t690);
    (void)_t691;
    ;
    if (_t691) {
        Bool _t687 = 0;
        (void)_t687;
        Str_delete(&self->elem_type, &(Bool){_t687});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t702 = U64_mul(self->cap, self->elem_size);
    (void)_t702;
    U8 *new_data = malloc(_t702);
    (void)new_data;
    ;
    {
        U64 _t701 = 0;
        (void)_t701;
        Range *_fc692 = Range_new(_t701, self->count);
        (void)_fc692;
        ;
        U64 _fi692 = 0;
        (void)_fi692;
        while (1) {
            U64 _t694; { U64 *_hp = (U64 *)Range_len(_fc692); _t694 = *_hp; free(_hp); }
            (void)_t694;
            Bool _wcond693; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi692}, &(U64){_t694}); _wcond693 = *_hp; free(_hp); }
            (void)_wcond693;
            ;
            if (_wcond693) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc692, _fi692); i = *_hp; free(_hp); }
            (void)i;
            U64 _t695 = 1;
            (void)_t695;
            U64 _t696 = U64_add(_fi692, _t695);
            (void)_t696;
            ;
            _fi692 = _t696;
            ;
            U64 *_t697 = malloc(sizeof(U64)); *_t697 = U64_mul(i, self->elem_size);
            (void)_t697;
            void *_t698 = ptr_add(self->data, DEREF(_t697));
            (void)_t698;
            void *cloned = dyn_call_clone(&self->elem_type, _t698);
            (void)cloned;
            U64_delete(_t697, &(Bool){1});
            U64 *_t699 = malloc(sizeof(U64)); *_t699 = U64_mul(i, self->elem_size);
            (void)_t699;
            ;
            void *_t700 = ptr_add(new_data, DEREF(_t699));
            (void)_t700;
            memcpy(_t700, cloned, self->elem_size);
            U64_delete(_t699, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc692, &(Bool){1});
        ;
    }
    Set *_t703 = malloc(sizeof(Set));
    _t703->data = new_data;
    _t703->count = self->count;
    _t703->cap = self->cap;
    _t703->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t703->elem_type = *_ca; free(_ca); }
    (void)_t703;
    return _t703;
}

U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t711; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t711 = *_hp; free(_hp); }
    (void)_t711;
    if (_t711) {
        Str *_t705 = Str_lit("Str", 3ULL);
        (void)_t705;
        U64 _t706; { U64 *_hp = (U64 *)Str_size(); _t706 = *_hp; free(_hp); }
        (void)_t706;
        U64 _t707 = 1;
        (void)_t707;
        Array *_va12 = Array_new(_t705, &(U64){_t706}, &(U64){_t707});
        (void)_va12;
        Str_delete(_t705, &(Bool){1});
        ;
        ;
        U64 _t708 = 0;
        (void)_t708;
        Str *_t709 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t709;
        Array_set(_va12, &(U64){_t708}, _t709);
        ;
        Str *_t710 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t710;
        panic(_t710, _va12);
        Str_delete(_t710, &(Bool){1});
    }
    ;
    void *_t712 = ptr_add(self->c_str, DEREF(i));
    (void)_t712;
    return _t712;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t713 = ptr_add(self->c_str, DEREF(i));
    (void)_t713;
    return _t713;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t722; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t722 = *_hp; free(_hp); }
    (void)_t722;
    if (_t722) {
        min_len = b->count;
    }
    ;
    {
        U64 _t721 = 0;
        (void)_t721;
        Range *_fc714 = Range_new(_t721, min_len);
        (void)_fc714;
        ;
        U64 _fi714 = 0;
        (void)_fi714;
        while (1) {
            U64 _t716; { U64 *_hp = (U64 *)Range_len(_fc714); _t716 = *_hp; free(_hp); }
            (void)_t716;
            Bool _wcond715; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi714}, &(U64){_t716}); _wcond715 = *_hp; free(_hp); }
            (void)_wcond715;
            ;
            if (_wcond715) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc714, _fi714);
            (void)i;
            U64 _t717 = 1;
            (void)_t717;
            U64 _t718 = U64_add(_fi714, _t717);
            (void)_t718;
            ;
            _fi714 = _t718;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t719 = 0;
            (void)_t719;
            Bool _t720; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t719}); _t720 = *_hp; free(_hp); }
            (void)_t720;
            ;
            if (_t720) {
                ;
                Range_delete(_fc714, &(Bool){1});
                ;
                return c;
            }
            ;
            I64_delete(c, &(Bool){1});
        }
        Range_delete(_fc714, &(Bool){1});
        ;
    }
    ;
    I64 _t723 = U64_cmp(a->count, b->count);
    (void)_t723;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t723; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t724 = 1;
    (void)_t724;
    U64 _t725 = U64_add(DEREF(new_len), _t724);
    (void)_t725;
    ;
    U8 *new_data = malloc(_t725);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t726 = ptr_add(new_data, a->count);
    (void)_t726;
    memcpy(_t726, b->c_str, b->count);
    void *_t727 = ptr_add(new_data, DEREF(new_len));
    (void)_t727;
    I32 _t728 = 0;
    (void)_t728;
    U64 _t729 = 1;
    (void)_t729;
    memset(_t727, _t728, _t729);
    ;
    ;
    U64 _t730 = U64_clone(new_len);
    (void)_t730;
    U64 _t731 = U64_clone(new_len);
    (void)_t731;
    U64_delete(new_len, &(Bool){1});
    Str *_t732 = malloc(sizeof(Str));
    _t732->c_str = new_data;
    _t732->count = _t730;
    _t732->cap = _t731;
    (void)_t732;
    ;
    ;
    return _t732;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t733 = 1;
    (void)_t733;
    U64 _t734 = U64_add(DEREF(n), _t733);
    (void)_t734;
    ;
    U8 *buf = malloc(_t734);
    (void)buf;
    ;
    I32 _t735 = 0;
    (void)_t735;
    U64 _t736 = 1;
    (void)_t736;
    memset(buf, _t735, _t736);
    ;
    ;
    I64 _t737 = 0;
    (void)_t737;
    U64 _t738 = U64_clone(n);
    (void)_t738;
    Str *_t739 = malloc(sizeof(Str));
    _t739->c_str = buf;
    _t739->count = _t737;
    _t739->cap = _t738;
    (void)_t739;
    ;
    ;
    return _t739;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t752; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t752 = *_hp; free(_hp); }
    (void)_t752;
    if (_t752) {
        Str *_t740 = Str_lit("Str", 3ULL);
        (void)_t740;
        U64 _t741; { U64 *_hp = (U64 *)Str_size(); _t741 = *_hp; free(_hp); }
        (void)_t741;
        U64 _t742 = 1;
        (void)_t742;
        Array *_va13 = Array_new(_t740, &(U64){_t741}, &(U64){_t742});
        (void)_va13;
        Str_delete(_t740, &(Bool){1});
        ;
        ;
        U64 _t743 = 0;
        (void)_t743;
        Str *_t744 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t744;
        Array_set(_va13, &(U64){_t743}, _t744);
        ;
        Str *_t745 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t745;
        panic(_t745, _va13);
        Str_delete(_t745, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t753; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t753 = *_hp; free(_hp); }
    (void)_t753;
    if (_t753) {
        Str *_t746 = Str_lit("Str", 3ULL);
        (void)_t746;
        U64 _t747; { U64 *_hp = (U64 *)Str_size(); _t747 = *_hp; free(_hp); }
        (void)_t747;
        U64 _t748 = 1;
        (void)_t748;
        Array *_va14 = Array_new(_t746, &(U64){_t747}, &(U64){_t748});
        (void)_va14;
        Str_delete(_t746, &(Bool){1});
        ;
        ;
        U64 _t749 = 0;
        (void)_t749;
        Str *_t750 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t750;
        Array_set(_va14, &(U64){_t749}, _t750);
        ;
        Str *_t751 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t751;
        panic(_t751, _va14);
        Str_delete(_t751, &(Bool){1});
    }
    ;
    void *_t754 = ptr_add(self->c_str, self->count);
    (void)_t754;
    memcpy(_t754, s->c_str, s->count);
    U64 _t755 = U64_clone(new_len);
    (void)_t755;
    self->count = _t755;
    ;
    void *_t756 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t756;
    I32 _t757 = 0;
    (void)_t757;
    U64 _t758 = 1;
    (void)_t758;
    memset(_t756, _t757, _t758);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t759 = 1;
    (void)_t759;
    U64 _t760 = U64_add(val->count, _t759);
    (void)_t760;
    ;
    U8 *new_data = malloc(_t760);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t761 = ptr_add(new_data, val->count);
    (void)_t761;
    I32 _t762 = 0;
    (void)_t762;
    U64 _t763 = 1;
    (void)_t763;
    memset(_t761, _t762, _t763);
    ;
    ;
    Str *_t764 = malloc(sizeof(Str));
    _t764->c_str = new_data;
    _t764->count = val->count;
    _t764->cap = val->count;
    (void)_t764;
    return _t764;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t765; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t765 = *_hp; free(_hp); }
    (void)_t765;
    if (_t765) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t766 = Str_clone(val);
    (void)_t766;
    return _t766;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t768; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t768 = *_hp; free(_hp); }
    (void)_t768;
    if (_t768) {
        *st = s->count;
    }
    ;
    U64 _t769 = U64_add(DEREF(st), ln);
    (void)_t769;
    Bool _t770; { Bool *_hp = (Bool *)U64_gt(&(U64){_t769}, &s->count); _t770 = *_hp; free(_hp); }
    (void)_t770;
    ;
    if (_t770) {
        U64 _t767 = U64_sub(s->count, DEREF(st));
        (void)_t767;
        ln = _t767;
        ;
    }
    ;
    void *_t771 = ptr_add(s->c_str, DEREF(st));
    (void)_t771;
    U64 _t772 = U64_clone(&(U64){ln});
    (void)_t772;
    ;
    U64 _t773 = U64_clone(CAP_VIEW);
    (void)_t773;
    Str *_t774 = malloc(sizeof(Str));
    _t774->c_str = _t771;
    _t774->count = _t772;
    _t774->cap = _t773;
    (void)_t774;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t774;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t796 = 0;
    (void)_t796;
    Bool _t797 = U64_eq(b->count, _t796);
    (void)_t797;
    ;
    if (_t797) {
        Bool _t775 = 1;
        (void)_t775;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t775; return _r; }
    }
    ;
    Bool _t798; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t798 = *_hp; free(_hp); }
    (void)_t798;
    if (_t798) {
        Bool _t776 = 0;
        (void)_t776;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t776; return _r; }
    }
    ;
    {
        U64 _t792 = U64_sub(a->count, b->count);
        (void)_t792;
        U64 _t793 = 1;
        (void)_t793;
        U64 _t794 = 0;
        (void)_t794;
        U64 _t795 = U64_add(_t792, _t793);
        (void)_t795;
        ;
        ;
        Range *_fc777 = Range_new(_t794, _t795);
        (void)_fc777;
        ;
        ;
        U64 _fi777 = 0;
        (void)_fi777;
        while (1) {
            U64 _t789; { U64 *_hp = (U64 *)Range_len(_fc777); _t789 = *_hp; free(_hp); }
            (void)_t789;
            Bool _wcond778; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi777}, &(U64){_t789}); _wcond778 = *_hp; free(_hp); }
            (void)_wcond778;
            ;
            if (_wcond778) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc777, _fi777); i = *_hp; free(_hp); }
            (void)i;
            U64 _t790 = 1;
            (void)_t790;
            U64 _t791 = U64_add(_fi777, _t790);
            (void)_t791;
            ;
            _fi777 = _t791;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t787 = 0;
                (void)_t787;
                Range *_fc779 = Range_new(_t787, b->count);
                (void)_fc779;
                ;
                U64 _fi779 = 0;
                (void)_fi779;
                while (1) {
                    U64 _t782; { U64 *_hp = (U64 *)Range_len(_fc779); _t782 = *_hp; free(_hp); }
                    (void)_t782;
                    Bool _wcond780; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi779}, &(U64){_t782}); _wcond780 = *_hp; free(_hp); }
                    (void)_wcond780;
                    ;
                    if (_wcond780) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc779, _fi779);
                    (void)j;
                    U64 _t783 = 1;
                    (void)_t783;
                    U64 _t784 = U64_add(_fi779, _t783);
                    (void)_t784;
                    ;
                    _fi779 = _t784;
                    ;
                    U64 *_t785 = malloc(sizeof(U64)); *_t785 = U64_add(i, DEREF(j));
                    (void)_t785;
                    U8 *ac = Str_get(a, _t785);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t786; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t786 = *_hp; free(_hp); }
                    (void)_t786;
                    U64_delete(_t785, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t786) {
                        Bool _t781 = 0;
                        (void)_t781;
                        found = _t781;
                        ;
                    }
                    ;
                }
                Range_delete(_fc779, &(Bool){1});
                ;
            }
            ;
            if (found) {
                Bool _t788 = 1;
                (void)_t788;
                ;
                Range_delete(_fc777, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t788; return _r; }
            }
            ;
        }
        Range_delete(_fc777, &(Bool){1});
        ;
    }
    Bool _t799 = 0;
    (void)_t799;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t799; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t809; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t809 = *_hp; free(_hp); }
    (void)_t809;
    if (_t809) {
        Bool _t800 = 0;
        (void)_t800;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t800; return _r; }
    }
    ;
    {
        U64 _t808 = 0;
        (void)_t808;
        Range *_fc801 = Range_new(_t808, b->count);
        (void)_fc801;
        ;
        U64 _fi801 = 0;
        (void)_fi801;
        while (1) {
            U64 _t804; { U64 *_hp = (U64 *)Range_len(_fc801); _t804 = *_hp; free(_hp); }
            (void)_t804;
            Bool _wcond802; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi801}, &(U64){_t804}); _wcond802 = *_hp; free(_hp); }
            (void)_wcond802;
            ;
            if (_wcond802) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc801, _fi801);
            (void)i;
            U64 _t805 = 1;
            (void)_t805;
            U64 _t806 = U64_add(_fi801, _t805);
            (void)_t806;
            ;
            _fi801 = _t806;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t807; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t807 = *_hp; free(_hp); }
            (void)_t807;
            U64_delete(i, &(Bool){1});
            if (_t807) {
                Bool _t803 = 0;
                (void)_t803;
                ;
                Range_delete(_fc801, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t803; return _r; }
            }
            ;
        }
        Range_delete(_fc801, &(Bool){1});
        ;
    }
    Bool _t810 = 1;
    (void)_t810;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t810; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t821; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t821 = *_hp; free(_hp); }
    (void)_t821;
    if (_t821) {
        Bool _t811 = 0;
        (void)_t811;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t811; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _t820 = 0;
        (void)_t820;
        Range *_fc812 = Range_new(_t820, b->count);
        (void)_fc812;
        ;
        U64 _fi812 = 0;
        (void)_fi812;
        while (1) {
            U64 _t815; { U64 *_hp = (U64 *)Range_len(_fc812); _t815 = *_hp; free(_hp); }
            (void)_t815;
            Bool _wcond813; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi812}, &(U64){_t815}); _wcond813 = *_hp; free(_hp); }
            (void)_wcond813;
            ;
            if (_wcond813) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc812, _fi812);
            (void)i;
            U64 _t816 = 1;
            (void)_t816;
            U64 _t817 = U64_add(_fi812, _t816);
            (void)_t817;
            ;
            _fi812 = _t817;
            ;
            U64 *_t818 = malloc(sizeof(U64)); *_t818 = U64_add(offset, DEREF(i));
            (void)_t818;
            U8 *ac = Str_get(a, _t818);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t819; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t819 = *_hp; free(_hp); }
            (void)_t819;
            U64_delete(_t818, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t819) {
                Bool _t814 = 0;
                (void)_t814;
                ;
                Range_delete(_fc812, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t814; return _r; }
            }
            ;
        }
        Range_delete(_fc812, &(Bool){1});
        ;
    }
    ;
    Bool _t822 = 1;
    (void)_t822;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t822; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t823 = 0;
    (void)_t823;
    Bool _t824 = U64_eq(self->count, _t823);
    (void)_t824;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t824; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t850 = 0;
    (void)_t850;
    Bool _t851 = U64_eq(needle->count, _t850);
    (void)_t851;
    ;
    if (_t851) {
        I64 _t825 = 0;
        (void)_t825;
        I64 _t826 = 1;
        (void)_t826;
        I64 _t827 = I64_sub(_t825, _t826);
        (void)_t827;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t827; return _r; }
    }
    ;
    Bool _t852; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t852 = *_hp; free(_hp); }
    (void)_t852;
    if (_t852) {
        I64 _t828 = 0;
        (void)_t828;
        I64 _t829 = 1;
        (void)_t829;
        I64 _t830 = I64_sub(_t828, _t829);
        (void)_t830;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t830; return _r; }
    }
    ;
    {
        U64 _t846 = U64_sub(self->count, needle->count);
        (void)_t846;
        U64 _t847 = 1;
        (void)_t847;
        U64 _t848 = 0;
        (void)_t848;
        U64 _t849 = U64_add(_t846, _t847);
        (void)_t849;
        ;
        ;
        Range *_fc831 = Range_new(_t848, _t849);
        (void)_fc831;
        ;
        ;
        U64 _fi831 = 0;
        (void)_fi831;
        while (1) {
            U64 _t843; { U64 *_hp = (U64 *)Range_len(_fc831); _t843 = *_hp; free(_hp); }
            (void)_t843;
            Bool _wcond832; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi831}, &(U64){_t843}); _wcond832 = *_hp; free(_hp); }
            (void)_wcond832;
            ;
            if (_wcond832) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc831, _fi831); i = *_hp; free(_hp); }
            (void)i;
            U64 _t844 = 1;
            (void)_t844;
            U64 _t845 = U64_add(_fi831, _t844);
            (void)_t845;
            ;
            _fi831 = _t845;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t841 = 0;
                (void)_t841;
                Range *_fc833 = Range_new(_t841, needle->count);
                (void)_fc833;
                ;
                U64 _fi833 = 0;
                (void)_fi833;
                while (1) {
                    U64 _t836; { U64 *_hp = (U64 *)Range_len(_fc833); _t836 = *_hp; free(_hp); }
                    (void)_t836;
                    Bool _wcond834; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi833}, &(U64){_t836}); _wcond834 = *_hp; free(_hp); }
                    (void)_wcond834;
                    ;
                    if (_wcond834) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc833, _fi833);
                    (void)j;
                    U64 _t837 = 1;
                    (void)_t837;
                    U64 _t838 = U64_add(_fi833, _t837);
                    (void)_t838;
                    ;
                    _fi833 = _t838;
                    ;
                    U64 *_t839 = malloc(sizeof(U64)); *_t839 = U64_add(i, DEREF(j));
                    (void)_t839;
                    U8 *ac = Str_get(self, _t839);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t840; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t840 = *_hp; free(_hp); }
                    (void)_t840;
                    U64_delete(_t839, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t840) {
                        Bool _t835 = 0;
                        (void)_t835;
                        found = _t835;
                        ;
                    }
                    ;
                }
                Range_delete(_fc833, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t842 = U64_to_i64(i);
                (void)_t842;
                ;
                ;
                Range_delete(_fc831, &(Bool){1});
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t842; return _r; }
            }
            ;
            ;
        }
        Range_delete(_fc831, &(Bool){1});
        ;
    }
    I64 _t853 = 0;
    (void)_t853;
    I64 _t854 = 1;
    (void)_t854;
    I64 _t855 = I64_sub(_t853, _t854);
    (void)_t855;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t855; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t881 = 0;
    (void)_t881;
    Bool _t882 = U64_eq(needle->count, _t881);
    (void)_t882;
    ;
    if (_t882) {
        I64 _t856 = 0;
        (void)_t856;
        I64 _t857 = 1;
        (void)_t857;
        I64 _t858 = I64_sub(_t856, _t857);
        (void)_t858;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t858; return _r; }
    }
    ;
    Bool _t883; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t883 = *_hp; free(_hp); }
    (void)_t883;
    if (_t883) {
        I64 _t859 = 0;
        (void)_t859;
        I64 _t860 = 1;
        (void)_t860;
        I64 _t861 = I64_sub(_t859, _t860);
        (void)_t861;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t861; return _r; }
    }
    ;
    I64 _t884 = 0;
    (void)_t884;
    I64 _t885 = 1;
    (void)_t885;
    I64 last = I64_sub(_t884, _t885);
    (void)last;
    ;
    ;
    {
        U64 _t877 = U64_sub(self->count, needle->count);
        (void)_t877;
        U64 _t878 = 1;
        (void)_t878;
        U64 _t879 = 0;
        (void)_t879;
        U64 _t880 = U64_add(_t877, _t878);
        (void)_t880;
        ;
        ;
        Range *_fc862 = Range_new(_t879, _t880);
        (void)_fc862;
        ;
        ;
        U64 _fi862 = 0;
        (void)_fi862;
        while (1) {
            U64 _t874; { U64 *_hp = (U64 *)Range_len(_fc862); _t874 = *_hp; free(_hp); }
            (void)_t874;
            Bool _wcond863; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi862}, &(U64){_t874}); _wcond863 = *_hp; free(_hp); }
            (void)_wcond863;
            ;
            if (_wcond863) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc862, _fi862); i = *_hp; free(_hp); }
            (void)i;
            U64 _t875 = 1;
            (void)_t875;
            U64 _t876 = U64_add(_fi862, _t875);
            (void)_t876;
            ;
            _fi862 = _t876;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t872 = 0;
                (void)_t872;
                Range *_fc864 = Range_new(_t872, needle->count);
                (void)_fc864;
                ;
                U64 _fi864 = 0;
                (void)_fi864;
                while (1) {
                    U64 _t867; { U64 *_hp = (U64 *)Range_len(_fc864); _t867 = *_hp; free(_hp); }
                    (void)_t867;
                    Bool _wcond865; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi864}, &(U64){_t867}); _wcond865 = *_hp; free(_hp); }
                    (void)_wcond865;
                    ;
                    if (_wcond865) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc864, _fi864);
                    (void)j;
                    U64 _t868 = 1;
                    (void)_t868;
                    U64 _t869 = U64_add(_fi864, _t868);
                    (void)_t869;
                    ;
                    _fi864 = _t869;
                    ;
                    U64 *_t870 = malloc(sizeof(U64)); *_t870 = U64_add(i, DEREF(j));
                    (void)_t870;
                    U8 *ac = Str_get(self, _t870);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t871; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t871 = *_hp; free(_hp); }
                    (void)_t871;
                    U64_delete(_t870, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t871) {
                        Bool _t866 = 0;
                        (void)_t866;
                        found = _t866;
                        ;
                    }
                    ;
                }
                Range_delete(_fc864, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t873 = U64_to_i64(i);
                (void)_t873;
                last = _t873;
                ;
            }
            ;
            ;
        }
        Range_delete(_fc862, &(Bool){1});
        ;
    }
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t901 = 0;
    (void)_t901;
    Bool _t902 = U64_eq(from->count, _t901);
    (void)_t902;
    ;
    if (_t902) {
        Str *_t886 = Str_clone(self);
        (void)_t886;
        ;
        return _t886;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t888 = U64_sub(self->count, from->count);
        (void)_t888;
        Bool _wcond887; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t888}); _wcond887 = *_hp; free(_hp); }
        (void)_wcond887;
        ;
        if (_wcond887) {
        } else {
            ;
            break;
        }
        ;
        U64 _t889 = U64_sub(self->count, start);
        (void)_t889;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t889});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t890 = 0;
        (void)_t890;
        I64 _t891 = 1;
        (void)_t891;
        I64 _t892 = I64_sub(_t890, _t891);
        (void)_t892;
        ;
        ;
        Bool _t893 = I64_eq(pos, _t892);
        (void)_t893;
        ;
        if (_t893) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t894 = I64_to_u64(pos);
        (void)_t894;
        Str *_t895 = Str_substr(self, &(U64){start}, &(U64){_t894});
        (void)_t895;
        ;
        result = Str_concat(result, _t895);
        Str_delete(_t895, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t896 = I64_to_u64(pos);
        (void)_t896;
        ;
        U64 _t897 = U64_add(start, _t896);
        (void)_t897;
        ;
        U64 _t898 = U64_add(_t897, from->count);
        (void)_t898;
        ;
        start = _t898;
        ;
    }
    Bool _t903; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t903 = *_hp; free(_hp); }
    (void)_t903;
    if (_t903) {
        U64 _t899 = U64_sub(self->count, start);
        (void)_t899;
        Str *_t900 = Str_substr(self, &(U64){start}, &(U64){_t899});
        (void)_t900;
        ;
        result = Str_concat(result, _t900);
        Str_delete(_t900, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t904 = 1;
    (void)_t904;
    Str *_t905 = Str_substr(self, i, &(U64){_t904});
    (void)_t905;
    ;
    return _t905;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t908; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t908 = *_hp; free(_hp); }
    (void)_t908;
    if (_t908) {
        U64 _t906 = U64_sub(self->count, prefix->count);
        (void)_t906;
        Str *_t907 = Str_substr(self, &prefix->count, &(U64){_t906});
        (void)_t907;
        ;
        ;
        return _t907;
    }
    ;
    Str *_t909 = Str_clone(self);
    (void)_t909;
    return _t909;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t913; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t913 = *_hp; free(_hp); }
    (void)_t913;
    if (_t913) {
        U64 _t910 = 0;
        (void)_t910;
        U64 _t911 = U64_sub(self->count, suffix->count);
        (void)_t911;
        Str *_t912 = Str_substr(self, &(U64){_t910}, &(U64){_t911});
        (void)_t912;
        ;
        ;
        ;
        return _t912;
    }
    ;
    Str *_t914 = Str_clone(self);
    (void)_t914;
    return _t914;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t915 = 2;
    (void)_t915;
    U8 *buf = malloc(_t915);
    (void)buf;
    ;
    U64 _t916 = 1;
    (void)_t916;
    memcpy(buf, byte, _t916);
    ;
    U64 *_t917 = malloc(sizeof(U64));
    *_t917 = 1;
    (void)_t917;
    void *_t918 = ptr_add(buf, DEREF(_t917));
    (void)_t918;
    I32 _t919 = 0;
    (void)_t919;
    U64 _t920 = 1;
    (void)_t920;
    memset(_t918, _t919, _t920);
    U64_delete(_t917, &(Bool){1});
    ;
    ;
    I64 _t921 = 1;
    (void)_t921;
    I64 _t922 = 1;
    (void)_t922;
    Str *_t923 = malloc(sizeof(Str));
    _t923->c_str = buf;
    _t923->count = _t921;
    _t923->cap = _t922;
    (void)_t923;
    ;
    ;
    return _t923;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t965 = 0;
    (void)_t965;
    Bool _t966 = U64_eq(self->count, _t965);
    (void)_t966;
    ;
    if (_t966) {
        Str *_t924 = Str_lit("Str", 3ULL);
        (void)_t924;
        U64 _t925; { U64 *_hp = (U64 *)Str_size(); _t925 = *_hp; free(_hp); }
        (void)_t925;
        U64 _t926 = 1;
        (void)_t926;
        Array *_va15 = Array_new(_t924, &(U64){_t925}, &(U64){_t926});
        (void)_va15;
        Str_delete(_t924, &(Bool){1});
        ;
        ;
        U64 _t927 = 0;
        (void)_t927;
        Str *_t928 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t928;
        Array_set(_va15, &(U64){_t927}, _t928);
        ;
        Str *_t929 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t929;
        panic(_t929, _va15);
        Str_delete(_t929, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t967 = malloc(sizeof(U64));
    *_t967 = 0;
    (void)_t967;
    U8 *first = Str_get(self, _t967);
    (void)first;
    U8 _t968 = 45;
    (void)_t968;
    Bool _t969 = U8_eq(DEREF(first), _t968);
    (void)_t969;
    U64_delete(_t967, &(Bool){1});
    ;
    if (_t969) {
        Bool _t930 = 1;
        (void)_t930;
        neg = _t930;
        ;
        U64 _t931 = 1;
        (void)_t931;
        start = _t931;
        ;
    }
    ;
    Bool _t970 = U64_eq(start, self->count);
    (void)_t970;
    if (_t970) {
        Str *_t932 = Str_lit("Str", 3ULL);
        (void)_t932;
        U64 _t933; { U64 *_hp = (U64 *)Str_size(); _t933 = *_hp; free(_hp); }
        (void)_t933;
        U64 _t934 = 1;
        (void)_t934;
        Array *_va16 = Array_new(_t932, &(U64){_t933}, &(U64){_t934});
        (void)_va16;
        Str_delete(_t932, &(Bool){1});
        ;
        ;
        U64 _t935 = 0;
        (void)_t935;
        Str *_t936 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t936;
        Array_set(_va16, &(U64){_t935}, _t936);
        ;
        Str *_t937 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t937;
        panic(_t937, _va16);
        Str_delete(_t937, &(Bool){1});
    }
    ;
    {
        Range *_fc938 = Range_new(start, self->count);
        (void)_fc938;
        U64 _fi938 = 0;
        (void)_fi938;
        while (1) {
            U64 _t950; { U64 *_hp = (U64 *)Range_len(_fc938); _t950 = *_hp; free(_hp); }
            (void)_t950;
            Bool _wcond939; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi938}, &(U64){_t950}); _wcond939 = *_hp; free(_hp); }
            (void)_wcond939;
            ;
            if (_wcond939) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc938, _fi938);
            (void)i;
            U64 _t951 = 1;
            (void)_t951;
            U64 _t952 = U64_add(_fi938, _t951);
            (void)_t952;
            ;
            _fi938 = _t952;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t953 = U8_to_i64(DEREF(ch));
            (void)_t953;
            U64_delete(i, &(Bool){1});
            I64 _t954 = 48;
            (void)_t954;
            I64 d = I64_sub(_t953, _t954);
            (void)d;
            ;
            ;
            I64 _t955 = 0;
            (void)_t955;
            I64 _t956 = 9;
            (void)_t956;
            Bool _t957; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t955}); _t957 = *_hp; free(_hp); }
            (void)_t957;
            ;
            Bool _t958; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t956}); _t958 = *_hp; free(_hp); }
            (void)_t958;
            ;
            Bool _t959 = Bool_or(_t957, _t958);
            (void)_t959;
            ;
            ;
            if (_t959) {
                Str *_t940 = Str_lit("Str", 3ULL);
                (void)_t940;
                U64 _t941; { U64 *_hp = (U64 *)Str_size(); _t941 = *_hp; free(_hp); }
                (void)_t941;
                U64 _t942 = 3;
                (void)_t942;
                Array *_va17 = Array_new(_t940, &(U64){_t941}, &(U64){_t942});
                (void)_va17;
                Str_delete(_t940, &(Bool){1});
                ;
                ;
                U64 _t943 = 0;
                (void)_t943;
                Str *_t944 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t944;
                Array_set(_va17, &(U64){_t943}, _t944);
                ;
                U64 _t945 = 1;
                (void)_t945;
                Str *_t946 = Str_clone(self);
                (void)_t946;
                Array_set(_va17, &(U64){_t945}, _t946);
                ;
                U64 _t947 = 2;
                (void)_t947;
                Str *_t948 = Str_lit("'", 1ULL);
                (void)_t948;
                Array_set(_va17, &(U64){_t947}, _t948);
                ;
                Str *_t949 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t949;
                panic(_t949, _va17);
                Str_delete(_t949, &(Bool){1});
            }
            ;
            I64 _t960 = 10;
            (void)_t960;
            I64 _t961 = I64_mul(result, _t960);
            (void)_t961;
            ;
            I64 _t962 = I64_add(_t961, d);
            (void)_t962;
            ;
            ;
            result = _t962;
            ;
        }
        Range_delete(_fc938, &(Bool){1});
        ;
    }
    ;
    if (neg) {
        I64 _t963 = 0;
        (void)_t963;
        I64 _t964 = I64_sub(_t963, result);
        (void)_t964;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t964; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t987 = Str_lit("Str", 3ULL);
    (void)_t987;
    U64 _t988; { U64 *_hp = (U64 *)Str_size(); _t988 = *_hp; free(_hp); }
    (void)_t988;
    Vec *parts = Vec_new(_t987, &(U64){_t988});
    (void)parts;
    Str_delete(_t987, &(Bool){1});
    ;
    U64 _t989; { U64 *_hp = (U64 *)Str_len(delim); _t989 = *_hp; free(_hp); }
    (void)_t989;
    U64 _t990 = 0;
    (void)_t990;
    Bool _t991 = U64_eq(_t989, _t990);
    (void)_t991;
    ;
    ;
    if (_t991) {
        Str *_t971 = Str_clone(self);
        (void)_t971;
        Vec_push(parts, _t971);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t981; { U64 *_hp = (U64 *)Str_len(self); _t981 = *_hp; free(_hp); }
        (void)_t981;
        U64 _t982; { U64 *_hp = (U64 *)Str_len(delim); _t982 = *_hp; free(_hp); }
        (void)_t982;
        U64 _t983 = U64_sub(_t981, _t982);
        (void)_t983;
        ;
        ;
        Bool _wcond972; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t983}); _wcond972 = *_hp; free(_hp); }
        (void)_wcond972;
        ;
        if (_wcond972) {
        } else {
            ;
            break;
        }
        ;
        U64 _t984; { U64 *_hp = (U64 *)Str_len(delim); _t984 = *_hp; free(_hp); }
        (void)_t984;
        Str *_t985 = Str_substr(self, &(U64){pos}, &(U64){_t984});
        (void)_t985;
        ;
        Bool _t986; { Bool *_hp = (Bool *)Str_eq(_t985, delim); _t986 = *_hp; free(_hp); }
        (void)_t986;
        Str_delete(_t985, &(Bool){1});
        if (_t986) {
            U64 _t973 = U64_sub(pos, start);
            (void)_t973;
            Str *_t974 = Str_substr(self, &(U64){start}, &(U64){_t973});
            (void)_t974;
            ;
            Str *_t975 = Str_clone(_t974);
            (void)_t975;
            Str_delete(_t974, &(Bool){1});
            Vec_push(parts, _t975);
            U64 _t976; { U64 *_hp = (U64 *)Str_len(delim); _t976 = *_hp; free(_hp); }
            (void)_t976;
            U64 _t977 = U64_add(pos, _t976);
            (void)_t977;
            ;
            start = _t977;
            ;
            U64 _t978 = U64_clone(&(U64){start});
            (void)_t978;
            pos = _t978;
            ;
        } else {
            U64 _t979 = 1;
            (void)_t979;
            U64 _t980 = U64_add(pos, _t979);
            (void)_t980;
            ;
            pos = _t980;
            ;
        }
        ;
    }
    ;
    U64 _t992; { U64 *_hp = (U64 *)Str_len(self); _t992 = *_hp; free(_hp); }
    (void)_t992;
    U64 _t993 = U64_sub(_t992, start);
    (void)_t993;
    ;
    Str *_t994 = Str_substr(self, &(U64){start}, &(U64){_t993});
    (void)_t994;
    ;
    ;
    Str *_t995 = Str_clone(_t994);
    (void)_t995;
    Str_delete(_t994, &(Bool){1});
    Vec_push(parts, _t995);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1027 = malloc(DEREF(elem_size));
    (void)_t1027;
    U64 _t1028 = 0;
    (void)_t1028;
    I64 _t1029 = 1;
    (void)_t1029;
    U64 _t1030 = U64_clone(elem_size);
    (void)_t1030;
    Vec *_t1031 = malloc(sizeof(Vec));
    _t1031->data = _t1027;
    _t1031->count = _t1028;
    _t1031->cap = _t1029;
    _t1031->elem_size = _t1030;
    { Str *_ca = Str_clone(elem_type); _t1031->elem_type = *_ca; free(_ca); }
    (void)_t1031;
    ;
    ;
    ;
    return _t1031;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1036 = U64_eq(self->count, self->cap);
    (void)_t1036;
    if (_t1036) {
        U64 _t1032 = 2;
        (void)_t1032;
        U64 new_cap = U64_mul(self->cap, _t1032);
        (void)new_cap;
        ;
        U64 _t1033 = U64_mul(new_cap, self->elem_size);
        (void)_t1033;
        void *_t1034 = realloc(self->data, _t1033);
        (void)_t1034;
        ;
        self->data = _t1034;
        U64 _t1035 = U64_clone(&(U64){new_cap});
        (void)_t1035;
        ;
        self->cap = _t1035;
        ;
    }
    ;
    U64 *_t1037 = malloc(sizeof(U64)); *_t1037 = U64_mul(self->count, self->elem_size);
    (void)_t1037;
    void *_t1038 = ptr_add(self->data, DEREF(_t1037));
    (void)_t1038;
    memcpy(_t1038, val, self->elem_size);
    U64_delete(_t1037, &(Bool){1});
    free(val);
    U64 _t1039 = 1;
    (void)_t1039;
    U64 _t1040 = U64_add(self->count, _t1039);
    (void)_t1040;
    ;
    self->count = _t1040;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1055; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1055 = *_hp; free(_hp); }
    (void)_t1055;
    if (_t1055) {
        Str *_t1041 = Str_lit("Str", 3ULL);
        (void)_t1041;
        U64 _t1042; { U64 *_hp = (U64 *)Str_size(); _t1042 = *_hp; free(_hp); }
        (void)_t1042;
        U64 _t1043 = 5;
        (void)_t1043;
        Array *_va18 = Array_new(_t1041, &(U64){_t1042}, &(U64){_t1043});
        (void)_va18;
        Str_delete(_t1041, &(Bool){1});
        ;
        ;
        U64 _t1044 = 0;
        (void)_t1044;
        Str *_t1045 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1045;
        Array_set(_va18, &(U64){_t1044}, _t1045);
        ;
        U64 _t1046 = 1;
        (void)_t1046;
        Str *_t1047 = U64_to_str(DEREF(i));
        (void)_t1047;
        Array_set(_va18, &(U64){_t1046}, _t1047);
        ;
        U64 _t1048 = 2;
        (void)_t1048;
        Str *_t1049 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1049;
        Array_set(_va18, &(U64){_t1048}, _t1049);
        ;
        U64 _t1050 = 3;
        (void)_t1050;
        Str *_t1051 = U64_to_str(self->count);
        (void)_t1051;
        Array_set(_va18, &(U64){_t1050}, _t1051);
        ;
        U64 _t1052 = 4;
        (void)_t1052;
        Str *_t1053 = Str_lit(")", 1ULL);
        (void)_t1053;
        Array_set(_va18, &(U64){_t1052}, _t1053);
        ;
        Str *_t1054 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1054;
        panic(_t1054, _va18);
        Str_delete(_t1054, &(Bool){1});
    }
    ;
    U64 *_t1056 = malloc(sizeof(U64)); *_t1056 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1056;
    void *_t1057 = ptr_add(self->data, DEREF(_t1056));
    (void)_t1057;
    U64_delete(_t1056, &(Bool){1});
    return _t1057;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1068; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1068 = *_hp; free(_hp); }
    (void)_t1068;
    Bool _t1069 = Bool_not(_t1068);
    (void)_t1069;
    ;
    if (_t1069) {
        {
            U64 _t1066 = 0;
            (void)_t1066;
            Range *_fc1058 = Range_new(_t1066, self->count);
            (void)_fc1058;
            ;
            U64 _fi1058 = 0;
            (void)_fi1058;
            while (1) {
                U64 _t1060; { U64 *_hp = (U64 *)Range_len(_fc1058); _t1060 = *_hp; free(_hp); }
                (void)_t1060;
                Bool _wcond1059; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1058}, &(U64){_t1060}); _wcond1059 = *_hp; free(_hp); }
                (void)_wcond1059;
                ;
                if (_wcond1059) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1058, _fi1058); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1061 = 1;
                (void)_t1061;
                U64 _t1062 = U64_add(_fi1058, _t1061);
                (void)_t1062;
                ;
                _fi1058 = _t1062;
                ;
                U64 *_t1063 = malloc(sizeof(U64)); *_t1063 = U64_mul(i, self->elem_size);
                (void)_t1063;
                ;
                void *_t1064 = ptr_add(self->data, DEREF(_t1063));
                (void)_t1064;
                Bool _t1065 = 0;
                (void)_t1065;
                dyn_call_delete(&self->elem_type, _t1064, &(Bool){_t1065});
                U64_delete(_t1063, &(Bool){1});
                ;
            }
            Range_delete(_fc1058, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1070; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1070 = *_hp; free(_hp); }
    (void)_t1070;
    Bool _t1071 = Bool_not(_t1070);
    (void)_t1071;
    ;
    if (_t1071) {
        Bool _t1067 = 0;
        (void)_t1067;
        Str_delete(&self->elem_type, &(Bool){_t1067});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1083 = U64_mul(self->cap, self->elem_size);
    (void)_t1083;
    U8 *new_data = malloc(_t1083);
    (void)new_data;
    ;
    Bool _t1084; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1084 = *_hp; free(_hp); }
    (void)_t1084;
    Bool _t1085 = Bool_not(_t1084);
    (void)_t1085;
    ;
    if (_t1085) {
        {
            U64 _t1081 = 0;
            (void)_t1081;
            Range *_fc1072 = Range_new(_t1081, self->count);
            (void)_fc1072;
            ;
            U64 _fi1072 = 0;
            (void)_fi1072;
            while (1) {
                U64 _t1074; { U64 *_hp = (U64 *)Range_len(_fc1072); _t1074 = *_hp; free(_hp); }
                (void)_t1074;
                Bool _wcond1073; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1072}, &(U64){_t1074}); _wcond1073 = *_hp; free(_hp); }
                (void)_wcond1073;
                ;
                if (_wcond1073) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1072, _fi1072); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1075 = 1;
                (void)_t1075;
                U64 _t1076 = U64_add(_fi1072, _t1075);
                (void)_t1076;
                ;
                _fi1072 = _t1076;
                ;
                U64 *_t1077 = malloc(sizeof(U64)); *_t1077 = U64_mul(i, self->elem_size);
                (void)_t1077;
                void *_t1078 = ptr_add(self->data, DEREF(_t1077));
                (void)_t1078;
                void *cloned = dyn_call_clone(&self->elem_type, _t1078);
                (void)cloned;
                U64_delete(_t1077, &(Bool){1});
                U64 *_t1079 = malloc(sizeof(U64)); *_t1079 = U64_mul(i, self->elem_size);
                (void)_t1079;
                ;
                void *_t1080 = ptr_add(new_data, DEREF(_t1079));
                (void)_t1080;
                memcpy(_t1080, cloned, self->elem_size);
                U64_delete(_t1079, &(Bool){1});
                free(cloned);
            }
            Range_delete(_fc1072, &(Bool){1});
            ;
        }
    } else {
        U64 _t1082 = U64_mul(self->count, self->elem_size);
        (void)_t1082;
        memcpy(new_data, self->data, _t1082);
        ;
    }
    ;
    Vec *_t1086 = malloc(sizeof(Vec));
    _t1086->data = new_data;
    _t1086->count = self->count;
    _t1086->cap = self->cap;
    _t1086->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1086->elem_type = *_ca; free(_ca); }
    (void)_t1086;
    return _t1086;
}

Tuple * Tuple_new(void) {
    U64 _t1088 = 8;
    (void)_t1088;
    Str *_t1089 = Str_lit("Str", 3ULL);
    (void)_t1089;
    U64 _t1090; { U64 *_hp = (U64 *)Str_size(); _t1090 = *_hp; free(_hp); }
    (void)_t1090;
    Str *_t1091 = Str_lit("U64", 3ULL);
    (void)_t1091;
    U64 _t1092; { U64 *_hp = (U64 *)U64_size(); _t1092 = *_hp; free(_hp); }
    (void)_t1092;
    void *_t1093 = malloc(_t1088);
    (void)_t1093;
    ;
    U64 _t1094 = 0;
    (void)_t1094;
    I64 _t1095 = 8;
    (void)_t1095;
    Tuple *_t1096 = malloc(sizeof(Tuple));
    _t1096->data = _t1093;
    _t1096->total_size = _t1094;
    _t1096->cap = _t1095;
    { Vec *_ca = Vec_new(_t1089, &(U64){_t1090}); _t1096->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1091, &(U64){_t1092}); _t1096->type_sizes = *_ca; free(_ca); }
    (void)_t1096;
    Str_delete(_t1089, &(Bool){1});
    ;
    Str_delete(_t1091, &(Bool){1});
    ;
    ;
    ;
    return _t1096;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1097; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1097 = *_hp; free(_hp); }
    (void)_t1097;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1097; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1104; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1104 = *_hp; free(_hp); }
    (void)_t1104;
    if (_t1104) {
        U64 _t1101 = 2;
        (void)_t1101;
        U64 new_cap = U64_mul(self->cap, _t1101);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1098; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1098 = *_hp; free(_hp); }
            (void)_wcond1098;
            if (_wcond1098) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1099 = 2;
            (void)_t1099;
            U64 _t1100 = U64_mul(new_cap, _t1099);
            (void)_t1100;
            ;
            new_cap = _t1100;
            ;
        }
        void *_t1102 = realloc(self->data, new_cap);
        (void)_t1102;
        self->data = _t1102;
        U64 _t1103 = U64_clone(&(U64){new_cap});
        (void)_t1103;
        ;
        self->cap = _t1103;
        ;
    }
    ;
    void *_t1105 = ptr_add(self->data, self->total_size);
    (void)_t1105;
    memcpy(_t1105, val, DEREF(elem_size));
    free(val);
    Str *_t1106 = Str_clone(elem_type);
    (void)_t1106;
    Vec_push(&self->type_names, _t1106);
    U64 _t1107 = U64_clone(elem_size);
    (void)_t1107;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1107; _oa; }));
    U64 _t1108 = U64_clone(&(U64){new_total});
    (void)_t1108;
    ;
    self->total_size = _t1108;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1131; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1131 = *_hp; free(_hp); }
    (void)_t1131;
    Bool _t1132; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1131}); _t1132 = *_hp; free(_hp); }
    (void)_t1132;
    ;
    if (_t1132) {
        Str *_t1109 = Str_lit("Str", 3ULL);
        (void)_t1109;
        U64 _t1110; { U64 *_hp = (U64 *)Str_size(); _t1110 = *_hp; free(_hp); }
        (void)_t1110;
        U64 _t1111 = 5;
        (void)_t1111;
        Array *_va19 = Array_new(_t1109, &(U64){_t1110}, &(U64){_t1111});
        (void)_va19;
        Str_delete(_t1109, &(Bool){1});
        ;
        ;
        U64 _t1112 = 0;
        (void)_t1112;
        Str *_t1113 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1113;
        Array_set(_va19, &(U64){_t1112}, _t1113);
        ;
        U64 _t1114 = 1;
        (void)_t1114;
        Str *_t1115 = U64_to_str(DEREF(i));
        (void)_t1115;
        Array_set(_va19, &(U64){_t1114}, _t1115);
        ;
        U64 _t1116 = 2;
        (void)_t1116;
        Str *_t1117 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1117;
        Array_set(_va19, &(U64){_t1116}, _t1117);
        ;
        U64 _t1118; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1118 = *_hp; free(_hp); }
        (void)_t1118;
        U64 _t1119 = 3;
        (void)_t1119;
        Str *_t1120 = U64_to_str(_t1118);
        (void)_t1120;
        ;
        Array_set(_va19, &(U64){_t1119}, _t1120);
        ;
        U64 _t1121 = 4;
        (void)_t1121;
        Str *_t1122 = Str_lit(")", 1ULL);
        (void)_t1122;
        Array_set(_va19, &(U64){_t1121}, _t1122);
        ;
        Str *_t1123 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1123;
        panic(_t1123, _va19);
        Str_delete(_t1123, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1130 = 0;
        (void)_t1130;
        Range *_fc1124 = Range_new(_t1130, DEREF(i));
        (void)_fc1124;
        ;
        U64 _fi1124 = 0;
        (void)_fi1124;
        while (1) {
            U64 _t1126; { U64 *_hp = (U64 *)Range_len(_fc1124); _t1126 = *_hp; free(_hp); }
            (void)_t1126;
            Bool _wcond1125; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1124}, &(U64){_t1126}); _wcond1125 = *_hp; free(_hp); }
            (void)_wcond1125;
            ;
            if (_wcond1125) {
            } else {
                ;
                break;
            }
            ;
            U64 *j = Range_get(_fc1124, _fi1124);
            (void)j;
            U64 _t1127 = 1;
            (void)_t1127;
            U64 _t1128 = U64_add(_fi1124, _t1127);
            (void)_t1128;
            ;
            _fi1124 = _t1128;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1129 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1129;
            U64_delete(j, &(Bool){1});
            *offset = _t1129;
            ;
        }
        Range_delete(_fc1124, &(Bool){1});
        ;
    }
    void *_t1133 = ptr_add(self->data, DEREF(offset));
    (void)_t1133;
    U64_delete(offset, &(Bool){1});
    return _t1133;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1134 = Vec_get(&self->type_names, i);
    (void)_t1134;
    return _t1134;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1135 = Vec_get(&self->type_sizes, i);
    (void)_t1135;
    return _t1135;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1144 = 0;
        (void)_t1144;
        U64 _t1145; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        Range *_fc1136 = Range_new(_t1144, _t1145);
        (void)_fc1136;
        ;
        ;
        U64 _fi1136 = 0;
        (void)_fi1136;
        while (1) {
            U64 _t1138; { U64 *_hp = (U64 *)Range_len(_fc1136); _t1138 = *_hp; free(_hp); }
            (void)_t1138;
            Bool _wcond1137; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1136}, &(U64){_t1138}); _wcond1137 = *_hp; free(_hp); }
            (void)_wcond1137;
            ;
            if (_wcond1137) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1136, _fi1136);
            (void)i;
            U64 _t1139 = 1;
            (void)_t1139;
            U64 _t1140 = U64_add(_fi1136, _t1139);
            (void)_t1140;
            ;
            _fi1136 = _t1140;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1141 = ptr_add(self->data, DEREF(offset));
            (void)_t1141;
            Bool _t1142 = 0;
            (void)_t1142;
            dyn_call_delete(tn, _t1141, &(Bool){_t1142});
            ;
            U64 _t1143 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1143;
            U64_delete(i, &(Bool){1});
            *offset = _t1143;
            ;
        }
        Range_delete(_fc1136, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1146 = 0;
    (void)_t1146;
    Vec_delete(&self->type_names, &(Bool){_t1146});
    ;
    Bool _t1147 = 0;
    (void)_t1147;
    Vec_delete(&self->type_sizes, &(Bool){_t1147});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1160 = 0;
    (void)_t1160;
    Bool _t1161 = U64_eq(new_cap, _t1160);
    (void)_t1161;
    ;
    if (_t1161) {
        I64 _t1148 = 8;
        (void)_t1148;
        U64 _t1149; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1148}); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        ;
        new_cap = _t1149;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1158 = 0;
        (void)_t1158;
        U64 _t1159; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1159 = *_hp; free(_hp); }
        (void)_t1159;
        Range *_fc1150 = Range_new(_t1158, _t1159);
        (void)_fc1150;
        ;
        ;
        U64 _fi1150 = 0;
        (void)_fi1150;
        while (1) {
            U64 _t1152; { U64 *_hp = (U64 *)Range_len(_fc1150); _t1152 = *_hp; free(_hp); }
            (void)_t1152;
            Bool _wcond1151; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1150}, &(U64){_t1152}); _wcond1151 = *_hp; free(_hp); }
            (void)_wcond1151;
            ;
            if (_wcond1151) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1150, _fi1150);
            (void)i;
            U64 _t1153 = 1;
            (void)_t1153;
            U64 _t1154 = U64_add(_fi1150, _t1153);
            (void)_t1154;
            ;
            _fi1150 = _t1154;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1155 = ptr_add(self->data, DEREF(offset));
            (void)_t1155;
            void *cloned = dyn_call_clone(tn, _t1155);
            (void)cloned;
            void *_t1156 = ptr_add(new_data, DEREF(offset));
            (void)_t1156;
            memcpy(_t1156, cloned, DEREF(ts));
            free(cloned);
            U64 _t1157 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1157;
            U64_delete(i, &(Bool){1});
            *offset = _t1157;
            ;
        }
        Range_delete(_fc1150, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1162 = U64_clone(&(U64){new_cap});
    (void)_t1162;
    ;
    Vec *_t1163 = Vec_clone(&self->type_names);
    (void)_t1163;
    Vec *_t1164 = Vec_clone(&self->type_sizes);
    (void)_t1164;
    Tuple *_t1165 = malloc(sizeof(Tuple));
    _t1165->data = new_data;
    _t1165->total_size = self->total_size;
    _t1165->cap = _t1162;
    { Vec *_ca = Vec_clone(_t1163); _t1165->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1164); _t1165->type_sizes = *_ca; free(_ca); }
    (void)_t1165;
    ;
    Vec_delete(_t1163, &(Bool){1});
    Vec_delete(_t1164, &(Bool){1});
    return _t1165;
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
    Bool _t1184; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t1184 = *_hp; free(_hp); }
    (void)_t1184;
    if (_t1184) {
        Bool _t1167; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = (Bool *)TilType_is_None(self); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    if (_t1185) {
        Bool _t1168; { Bool *_hp = (Bool *)TilType_is_None(other); _t1168 = *_hp; free(_hp); }
        (void)_t1168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1168; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = (Bool *)TilType_is_I64(self); _t1186 = *_hp; free(_hp); }
    (void)_t1186;
    if (_t1186) {
        Bool _t1169; { Bool *_hp = (Bool *)TilType_is_I64(other); _t1169 = *_hp; free(_hp); }
        (void)_t1169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1169; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = (Bool *)TilType_is_U8(self); _t1187 = *_hp; free(_hp); }
    (void)_t1187;
    if (_t1187) {
        Bool _t1170; { Bool *_hp = (Bool *)TilType_is_U8(other); _t1170 = *_hp; free(_hp); }
        (void)_t1170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1170; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = (Bool *)TilType_is_I16(self); _t1188 = *_hp; free(_hp); }
    (void)_t1188;
    if (_t1188) {
        Bool _t1171; { Bool *_hp = (Bool *)TilType_is_I16(other); _t1171 = *_hp; free(_hp); }
        (void)_t1171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1171; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = (Bool *)TilType_is_I32(self); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        Bool _t1172; { Bool *_hp = (Bool *)TilType_is_I32(other); _t1172 = *_hp; free(_hp); }
        (void)_t1172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1172; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = (Bool *)TilType_is_U32(self); _t1190 = *_hp; free(_hp); }
    (void)_t1190;
    if (_t1190) {
        Bool _t1173; { Bool *_hp = (Bool *)TilType_is_U32(other); _t1173 = *_hp; free(_hp); }
        (void)_t1173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1173; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = (Bool *)TilType_is_U64(self); _t1191 = *_hp; free(_hp); }
    (void)_t1191;
    if (_t1191) {
        Bool _t1174; { Bool *_hp = (Bool *)TilType_is_U64(other); _t1174 = *_hp; free(_hp); }
        (void)_t1174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1174; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = (Bool *)TilType_is_F32(self); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        Bool _t1175; { Bool *_hp = (Bool *)TilType_is_F32(other); _t1175 = *_hp; free(_hp); }
        (void)_t1175;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1175; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t1193 = *_hp; free(_hp); }
    (void)_t1193;
    if (_t1193) {
        Bool _t1176; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t1176 = *_hp; free(_hp); }
        (void)_t1176;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1176; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t1194 = *_hp; free(_hp); }
    (void)_t1194;
    if (_t1194) {
        Bool _t1177; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t1177 = *_hp; free(_hp); }
        (void)_t1177;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1177; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t1195 = *_hp; free(_hp); }
    (void)_t1195;
    if (_t1195) {
        Bool _t1178; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t1178 = *_hp; free(_hp); }
        (void)_t1178;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1178; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t1196 = *_hp; free(_hp); }
    (void)_t1196;
    if (_t1196) {
        Bool _t1179; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t1179 = *_hp; free(_hp); }
        (void)_t1179;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1179; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t1197 = *_hp; free(_hp); }
    (void)_t1197;
    if (_t1197) {
        Bool _t1180; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t1180 = *_hp; free(_hp); }
        (void)_t1180;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1180; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t1198 = *_hp; free(_hp); }
    (void)_t1198;
    if (_t1198) {
        Bool _t1181; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t1181 = *_hp; free(_hp); }
        (void)_t1181;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1181; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t1199 = *_hp; free(_hp); }
    (void)_t1199;
    if (_t1199) {
        Bool _t1182; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t1182 = *_hp; free(_hp); }
        (void)_t1182;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1182; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t1200 = *_hp; free(_hp); }
    (void)_t1200;
    if (_t1200) {
        Bool _t1183; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t1183 = *_hp; free(_hp); }
        (void)_t1183;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1183; return _r; }
    }
    ;
    Bool _t1201 = 0;
    (void)_t1201;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1201; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t1202; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        ;
        return TilType_None();
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
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
    Bool _t1235; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Str *_t1218 = Str_lit("Unknown", 7ULL);
        (void)_t1218;
        ;
        return _t1218;
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Str *_t1219 = Str_lit("None", 4ULL);
        (void)_t1219;
        ;
        return _t1219;
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Str *_t1220 = Str_lit("I64", 3ULL);
        (void)_t1220;
        ;
        return _t1220;
    }
    ;
    Bool _t1238; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1238 = *_hp; free(_hp); }
    (void)_t1238;
    if (_t1238) {
        Str *_t1221 = Str_lit("U8", 2ULL);
        (void)_t1221;
        ;
        return _t1221;
    }
    ;
    Bool _t1239; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        Str *_t1222 = Str_lit("I16", 3ULL);
        (void)_t1222;
        ;
        return _t1222;
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        Str *_t1223 = Str_lit("I32", 3ULL);
        (void)_t1223;
        ;
        return _t1223;
    }
    ;
    Bool _t1241; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1241 = *_hp; free(_hp); }
    (void)_t1241;
    if (_t1241) {
        Str *_t1224 = Str_lit("U32", 3ULL);
        (void)_t1224;
        ;
        return _t1224;
    }
    ;
    Bool _t1242; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1242 = *_hp; free(_hp); }
    (void)_t1242;
    if (_t1242) {
        Str *_t1225 = Str_lit("U64", 3ULL);
        (void)_t1225;
        ;
        return _t1225;
    }
    ;
    Bool _t1243; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1243 = *_hp; free(_hp); }
    (void)_t1243;
    if (_t1243) {
        Str *_t1226 = Str_lit("F32", 3ULL);
        (void)_t1226;
        ;
        return _t1226;
    }
    ;
    Bool _t1244; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        Str *_t1227 = Str_lit("Bool", 4ULL);
        (void)_t1227;
        ;
        return _t1227;
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        Str *_t1228 = Str_lit("Struct", 6ULL);
        (void)_t1228;
        ;
        return _t1228;
    }
    ;
    Bool _t1246; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1246 = *_hp; free(_hp); }
    (void)_t1246;
    if (_t1246) {
        Str *_t1229 = Str_lit("StructDef", 9ULL);
        (void)_t1229;
        ;
        return _t1229;
    }
    ;
    Bool _t1247; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        Str *_t1230 = Str_lit("Enum", 4ULL);
        (void)_t1230;
        ;
        return _t1230;
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        Str *_t1231 = Str_lit("EnumDef", 7ULL);
        (void)_t1231;
        ;
        return _t1231;
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        Str *_t1232 = Str_lit("FuncDef", 7ULL);
        (void)_t1232;
        ;
        return _t1232;
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        Str *_t1233 = Str_lit("FuncPtr", 7ULL);
        (void)_t1233;
        ;
        return _t1233;
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        Str *_t1234 = Str_lit("Dynamic", 7ULL);
        (void)_t1234;
        ;
        return _t1234;
    }
    ;
    Str *_t1252 = Str_lit("unknown", 7ULL);
    (void)_t1252;
    return _t1252;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t1290; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1290; return _r; }
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
    Bool _t1313; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t1313 = *_hp; free(_hp); }
    (void)_t1313;
    if (_t1313) {
        Bool _t1307; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t1307 = *_hp; free(_hp); }
        (void)_t1307;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1307; return _r; }
    }
    ;
    Bool _t1314; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t1314 = *_hp; free(_hp); }
    (void)_t1314;
    if (_t1314) {
        Bool _t1308; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t1308 = *_hp; free(_hp); }
        (void)_t1308;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1308; return _r; }
    }
    ;
    Bool _t1315; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t1315 = *_hp; free(_hp); }
    (void)_t1315;
    if (_t1315) {
        Bool _t1309; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t1309 = *_hp; free(_hp); }
        (void)_t1309;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1309; return _r; }
    }
    ;
    Bool _t1316; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t1316 = *_hp; free(_hp); }
    (void)_t1316;
    if (_t1316) {
        Bool _t1310; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t1310 = *_hp; free(_hp); }
        (void)_t1310;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1310; return _r; }
    }
    ;
    Bool _t1317; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t1317 = *_hp; free(_hp); }
    (void)_t1317;
    if (_t1317) {
        Bool _t1311; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t1311 = *_hp; free(_hp); }
        (void)_t1311;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1311; return _r; }
    }
    ;
    Bool _t1318; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t1318 = *_hp; free(_hp); }
    (void)_t1318;
    if (_t1318) {
        Bool _t1312; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t1312 = *_hp; free(_hp); }
        (void)_t1312;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1312; return _r; }
    }
    ;
    Bool _t1319 = 0;
    (void)_t1319;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1319; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t1320; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1320 = *_hp; free(_hp); }
    (void)_t1320;
    if (_t1320) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t1321; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1321 = *_hp; free(_hp); }
    (void)_t1321;
    if (_t1321) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t1322; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1322 = *_hp; free(_hp); }
    (void)_t1322;
    if (_t1322) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t1323; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1323 = *_hp; free(_hp); }
    (void)_t1323;
    if (_t1323) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t1324; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1324 = *_hp; free(_hp); }
    (void)_t1324;
    if (_t1324) {
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
    Bool _t1331; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Str *_t1325 = Str_lit("Func", 4ULL);
        (void)_t1325;
        ;
        return _t1325;
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Str *_t1326 = Str_lit("Proc", 4ULL);
        (void)_t1326;
        ;
        return _t1326;
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Str *_t1327 = Str_lit("Test", 4ULL);
        (void)_t1327;
        ;
        return _t1327;
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Str *_t1328 = Str_lit("Macro", 5ULL);
        (void)_t1328;
        ;
        return _t1328;
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Str *_t1329 = Str_lit("ExtFunc", 7ULL);
        (void)_t1329;
        ;
        return _t1329;
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Str *_t1330 = Str_lit("ExtProc", 7ULL);
        (void)_t1330;
        ;
        return _t1330;
    }
    ;
    Str *_t1337 = Str_lit("unknown", 7ULL);
    (void)_t1337;
    return _t1337;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t1349; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1349; return _r; }
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
    Bool _t1446; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1446 = *_hp; free(_hp); }
    (void)_t1446;
    if (_t1446) {
        Bool _t1366; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t1366 = *_hp; free(_hp); }
        (void)_t1366;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1366; return _r; }
    }
    ;
    Bool _t1447; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1447 = *_hp; free(_hp); }
    (void)_t1447;
    if (_t1447) {
        Bool _t1368; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t1368 = *_hp; free(_hp); }
        (void)_t1368;
        Bool _t1369 = Bool_not(_t1368);
        (void)_t1369;
        ;
        if (_t1369) {
            Bool _t1367 = 0;
            (void)_t1367;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1367; return _r; }
        }
        ;
        Str *_t1370 = ExprData_get_LiteralStr(self);
        (void)_t1370;
        Str *_t1371 = ExprData_get_LiteralStr(other);
        (void)_t1371;
        Bool _t1372; { Bool *_hp = (Bool *)Str_eq(_t1370, _t1371); _t1372 = *_hp; free(_hp); }
        (void)_t1372;
        Str_delete(_t1370, &(Bool){1});
        Str_delete(_t1371, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1372; return _r; }
    }
    ;
    Bool _t1448; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1448 = *_hp; free(_hp); }
    (void)_t1448;
    if (_t1448) {
        Bool _t1374; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t1374 = *_hp; free(_hp); }
        (void)_t1374;
        Bool _t1375 = Bool_not(_t1374);
        (void)_t1375;
        ;
        if (_t1375) {
            Bool _t1373 = 0;
            (void)_t1373;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1373; return _r; }
        }
        ;
        Str *_t1376 = ExprData_get_LiteralNum(self);
        (void)_t1376;
        Str *_t1377 = ExprData_get_LiteralNum(other);
        (void)_t1377;
        Bool _t1378; { Bool *_hp = (Bool *)Str_eq(_t1376, _t1377); _t1378 = *_hp; free(_hp); }
        (void)_t1378;
        Str_delete(_t1376, &(Bool){1});
        Str_delete(_t1377, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1378; return _r; }
    }
    ;
    Bool _t1449; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1449 = *_hp; free(_hp); }
    (void)_t1449;
    if (_t1449) {
        Bool _t1380; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t1380 = *_hp; free(_hp); }
        (void)_t1380;
        Bool _t1381 = Bool_not(_t1380);
        (void)_t1381;
        ;
        if (_t1381) {
            Bool _t1379 = 0;
            (void)_t1379;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1379; return _r; }
        }
        ;
        Str *_t1382 = ExprData_get_LiteralBool(self);
        (void)_t1382;
        Str *_t1383 = ExprData_get_LiteralBool(other);
        (void)_t1383;
        Bool _t1384; { Bool *_hp = (Bool *)Str_eq(_t1382, _t1383); _t1384 = *_hp; free(_hp); }
        (void)_t1384;
        Str_delete(_t1382, &(Bool){1});
        Str_delete(_t1383, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1384; return _r; }
    }
    ;
    Bool _t1450; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    if (_t1450) {
        Bool _t1385; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t1385 = *_hp; free(_hp); }
        (void)_t1385;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1385; return _r; }
    }
    ;
    Bool _t1451; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    if (_t1451) {
        Bool _t1387; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t1387 = *_hp; free(_hp); }
        (void)_t1387;
        Bool _t1388 = Bool_not(_t1387);
        (void)_t1388;
        ;
        if (_t1388) {
            Bool _t1386 = 0;
            (void)_t1386;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1386; return _r; }
        }
        ;
        Str *_t1389 = ExprData_get_Ident(self);
        (void)_t1389;
        Str *_t1390 = ExprData_get_Ident(other);
        (void)_t1390;
        Bool _t1391; { Bool *_hp = (Bool *)Str_eq(_t1389, _t1390); _t1391 = *_hp; free(_hp); }
        (void)_t1391;
        Str_delete(_t1389, &(Bool){1});
        Str_delete(_t1390, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1391; return _r; }
    }
    ;
    Bool _t1452; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1452 = *_hp; free(_hp); }
    (void)_t1452;
    if (_t1452) {
        Bool _t1393; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t1393 = *_hp; free(_hp); }
        (void)_t1393;
        Bool _t1394 = Bool_not(_t1393);
        (void)_t1394;
        ;
        if (_t1394) {
            Bool _t1392 = 0;
            (void)_t1392;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1392; return _r; }
        }
        ;
        Declaration *_t1395 = ExprData_get_Decl(self);
        (void)_t1395;
        Declaration *_t1396 = ExprData_get_Decl(other);
        (void)_t1396;
        Bool _t1397; { Bool *_hp = (Bool *)Declaration_eq(_t1395, _t1396); _t1397 = *_hp; free(_hp); }
        (void)_t1397;
        Declaration_delete(_t1395, &(Bool){1});
        Declaration_delete(_t1396, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1397; return _r; }
    }
    ;
    Bool _t1453; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1453 = *_hp; free(_hp); }
    (void)_t1453;
    if (_t1453) {
        Bool _t1399; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t1399 = *_hp; free(_hp); }
        (void)_t1399;
        Bool _t1400 = Bool_not(_t1399);
        (void)_t1400;
        ;
        if (_t1400) {
            Bool _t1398 = 0;
            (void)_t1398;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1398; return _r; }
        }
        ;
        Str *_t1401 = ExprData_get_Assign(self);
        (void)_t1401;
        Str *_t1402 = ExprData_get_Assign(other);
        (void)_t1402;
        Bool _t1403; { Bool *_hp = (Bool *)Str_eq(_t1401, _t1402); _t1403 = *_hp; free(_hp); }
        (void)_t1403;
        Str_delete(_t1401, &(Bool){1});
        Str_delete(_t1402, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1403; return _r; }
    }
    ;
    Bool _t1454; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    if (_t1454) {
        Bool _t1404; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t1404 = *_hp; free(_hp); }
        (void)_t1404;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1404; return _r; }
    }
    ;
    Bool _t1455; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    if (_t1455) {
        Bool _t1406; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t1406 = *_hp; free(_hp); }
        (void)_t1406;
        Bool _t1407 = Bool_not(_t1406);
        (void)_t1407;
        ;
        if (_t1407) {
            Bool _t1405 = 0;
            (void)_t1405;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1405; return _r; }
        }
        ;
        FunctionDef *_t1408 = ExprData_get_FuncDef(self);
        (void)_t1408;
        FunctionDef *_t1409 = ExprData_get_FuncDef(other);
        (void)_t1409;
        Bool _t1410; { Bool *_hp = (Bool *)FunctionDef_eq(_t1408, _t1409); _t1410 = *_hp; free(_hp); }
        (void)_t1410;
        FunctionDef_delete(_t1408, &(Bool){1});
        FunctionDef_delete(_t1409, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1410; return _r; }
    }
    ;
    Bool _t1456; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    if (_t1456) {
        Bool _t1411; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t1411 = *_hp; free(_hp); }
        (void)_t1411;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1411; return _r; }
    }
    ;
    Bool _t1457; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1457 = *_hp; free(_hp); }
    (void)_t1457;
    if (_t1457) {
        Bool _t1412; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t1412 = *_hp; free(_hp); }
        (void)_t1412;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1412; return _r; }
    }
    ;
    Bool _t1458; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1458 = *_hp; free(_hp); }
    (void)_t1458;
    if (_t1458) {
        Bool _t1414; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t1414 = *_hp; free(_hp); }
        (void)_t1414;
        Bool _t1415 = Bool_not(_t1414);
        (void)_t1415;
        ;
        if (_t1415) {
            Bool _t1413 = 0;
            (void)_t1413;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1413; return _r; }
        }
        ;
        Str *_t1416 = ExprData_get_FieldAccess(self);
        (void)_t1416;
        Str *_t1417 = ExprData_get_FieldAccess(other);
        (void)_t1417;
        Bool _t1418; { Bool *_hp = (Bool *)Str_eq(_t1416, _t1417); _t1418 = *_hp; free(_hp); }
        (void)_t1418;
        Str_delete(_t1416, &(Bool){1});
        Str_delete(_t1417, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1418; return _r; }
    }
    ;
    Bool _t1459; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    if (_t1459) {
        Bool _t1420; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t1420 = *_hp; free(_hp); }
        (void)_t1420;
        Bool _t1421 = Bool_not(_t1420);
        (void)_t1421;
        ;
        if (_t1421) {
            Bool _t1419 = 0;
            (void)_t1419;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1419; return _r; }
        }
        ;
        Str *_t1422 = ExprData_get_FieldAssign(self);
        (void)_t1422;
        Str *_t1423 = ExprData_get_FieldAssign(other);
        (void)_t1423;
        Bool _t1424; { Bool *_hp = (Bool *)Str_eq(_t1422, _t1423); _t1424 = *_hp; free(_hp); }
        (void)_t1424;
        Str_delete(_t1422, &(Bool){1});
        Str_delete(_t1423, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1424; return _r; }
    }
    ;
    Bool _t1460; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    if (_t1460) {
        Bool _t1425; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t1425 = *_hp; free(_hp); }
        (void)_t1425;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1425; return _r; }
    }
    ;
    Bool _t1461; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1461 = *_hp; free(_hp); }
    (void)_t1461;
    if (_t1461) {
        Bool _t1426; { Bool *_hp = (Bool *)ExprData_is_If(other); _t1426 = *_hp; free(_hp); }
        (void)_t1426;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1426; return _r; }
    }
    ;
    Bool _t1462; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1462 = *_hp; free(_hp); }
    (void)_t1462;
    if (_t1462) {
        Bool _t1427; { Bool *_hp = (Bool *)ExprData_is_While(other); _t1427 = *_hp; free(_hp); }
        (void)_t1427;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1427; return _r; }
    }
    ;
    Bool _t1463; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1463 = *_hp; free(_hp); }
    (void)_t1463;
    if (_t1463) {
        Bool _t1429; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t1429 = *_hp; free(_hp); }
        (void)_t1429;
        Bool _t1430 = Bool_not(_t1429);
        (void)_t1430;
        ;
        if (_t1430) {
            Bool _t1428 = 0;
            (void)_t1428;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1428; return _r; }
        }
        ;
        Str *_t1431 = ExprData_get_ForIn(self);
        (void)_t1431;
        Str *_t1432 = ExprData_get_ForIn(other);
        (void)_t1432;
        Bool _t1433; { Bool *_hp = (Bool *)Str_eq(_t1431, _t1432); _t1433 = *_hp; free(_hp); }
        (void)_t1433;
        Str_delete(_t1431, &(Bool){1});
        Str_delete(_t1432, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1433; return _r; }
    }
    ;
    Bool _t1464; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1464 = *_hp; free(_hp); }
    (void)_t1464;
    if (_t1464) {
        Bool _t1435; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t1435 = *_hp; free(_hp); }
        (void)_t1435;
        Bool _t1436 = Bool_not(_t1435);
        (void)_t1436;
        ;
        if (_t1436) {
            Bool _t1434 = 0;
            (void)_t1434;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1434; return _r; }
        }
        ;
        Str *_t1437 = ExprData_get_NamedArg(self);
        (void)_t1437;
        Str *_t1438 = ExprData_get_NamedArg(other);
        (void)_t1438;
        Bool _t1439; { Bool *_hp = (Bool *)Str_eq(_t1437, _t1438); _t1439 = *_hp; free(_hp); }
        (void)_t1439;
        Str_delete(_t1437, &(Bool){1});
        Str_delete(_t1438, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1439; return _r; }
    }
    ;
    Bool _t1465; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1465 = *_hp; free(_hp); }
    (void)_t1465;
    if (_t1465) {
        Bool _t1440; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t1440 = *_hp; free(_hp); }
        (void)_t1440;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1440; return _r; }
    }
    ;
    Bool _t1466; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1466 = *_hp; free(_hp); }
    (void)_t1466;
    if (_t1466) {
        Bool _t1441; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t1441 = *_hp; free(_hp); }
        (void)_t1441;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1441; return _r; }
    }
    ;
    Bool _t1467; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1467 = *_hp; free(_hp); }
    (void)_t1467;
    if (_t1467) {
        Bool _t1442; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t1442 = *_hp; free(_hp); }
        (void)_t1442;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1442; return _r; }
    }
    ;
    Bool _t1468; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1468 = *_hp; free(_hp); }
    (void)_t1468;
    if (_t1468) {
        Bool _t1443; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t1443 = *_hp; free(_hp); }
        (void)_t1443;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1443; return _r; }
    }
    ;
    Bool _t1469; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1469 = *_hp; free(_hp); }
    (void)_t1469;
    if (_t1469) {
        Bool _t1444; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t1444 = *_hp; free(_hp); }
        (void)_t1444;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1444; return _r; }
    }
    ;
    Bool _t1470; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1470 = *_hp; free(_hp); }
    (void)_t1470;
    if (_t1470) {
        Bool _t1445; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t1445 = *_hp; free(_hp); }
        (void)_t1445;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1445; return _r; }
    }
    ;
    Bool _t1471 = 0;
    (void)_t1471;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1471; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t1494; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1494 = *_hp; free(_hp); }
    (void)_t1494;
    if (_t1494) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t1495; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1495 = *_hp; free(_hp); }
    (void)_t1495;
    if (_t1495) {
        Str *_t1472 = ExprData_get_LiteralStr(self);
        (void)_t1472;
        ExprData *_t1473 = ExprData_LiteralStr(_t1472);
        (void)_t1473;
        Str_delete(_t1472, &(Bool){1});
        ;
        return _t1473;
    }
    ;
    Bool _t1496; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1496 = *_hp; free(_hp); }
    (void)_t1496;
    if (_t1496) {
        Str *_t1474 = ExprData_get_LiteralNum(self);
        (void)_t1474;
        ExprData *_t1475 = ExprData_LiteralNum(_t1474);
        (void)_t1475;
        Str_delete(_t1474, &(Bool){1});
        ;
        return _t1475;
    }
    ;
    Bool _t1497; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1497 = *_hp; free(_hp); }
    (void)_t1497;
    if (_t1497) {
        Str *_t1476 = ExprData_get_LiteralBool(self);
        (void)_t1476;
        ExprData *_t1477 = ExprData_LiteralBool(_t1476);
        (void)_t1477;
        Str_delete(_t1476, &(Bool){1});
        ;
        return _t1477;
    }
    ;
    Bool _t1498; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1498 = *_hp; free(_hp); }
    (void)_t1498;
    if (_t1498) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t1499; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1499 = *_hp; free(_hp); }
    (void)_t1499;
    if (_t1499) {
        Str *_t1478 = ExprData_get_Ident(self);
        (void)_t1478;
        ExprData *_t1479 = ExprData_Ident(_t1478);
        (void)_t1479;
        Str_delete(_t1478, &(Bool){1});
        ;
        return _t1479;
    }
    ;
    Bool _t1500; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1500 = *_hp; free(_hp); }
    (void)_t1500;
    if (_t1500) {
        Declaration *_t1480 = ExprData_get_Decl(self);
        (void)_t1480;
        ExprData *_t1481 = ExprData_Decl(_t1480);
        (void)_t1481;
        Declaration_delete(_t1480, &(Bool){1});
        ;
        return _t1481;
    }
    ;
    Bool _t1501; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1501 = *_hp; free(_hp); }
    (void)_t1501;
    if (_t1501) {
        Str *_t1482 = ExprData_get_Assign(self);
        (void)_t1482;
        ExprData *_t1483 = ExprData_Assign(_t1482);
        (void)_t1483;
        Str_delete(_t1482, &(Bool){1});
        ;
        return _t1483;
    }
    ;
    Bool _t1502; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1502 = *_hp; free(_hp); }
    (void)_t1502;
    if (_t1502) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t1503; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1503 = *_hp; free(_hp); }
    (void)_t1503;
    if (_t1503) {
        FunctionDef *_t1484 = ExprData_get_FuncDef(self);
        (void)_t1484;
        ExprData *_t1485 = ExprData_FuncDef(_t1484);
        (void)_t1485;
        FunctionDef_delete(_t1484, &(Bool){1});
        ;
        return _t1485;
    }
    ;
    Bool _t1504; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1504 = *_hp; free(_hp); }
    (void)_t1504;
    if (_t1504) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t1505; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1505 = *_hp; free(_hp); }
    (void)_t1505;
    if (_t1505) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t1506; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1506 = *_hp; free(_hp); }
    (void)_t1506;
    if (_t1506) {
        Str *_t1486 = ExprData_get_FieldAccess(self);
        (void)_t1486;
        ExprData *_t1487 = ExprData_FieldAccess(_t1486);
        (void)_t1487;
        Str_delete(_t1486, &(Bool){1});
        ;
        return _t1487;
    }
    ;
    Bool _t1507; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1507 = *_hp; free(_hp); }
    (void)_t1507;
    if (_t1507) {
        Str *_t1488 = ExprData_get_FieldAssign(self);
        (void)_t1488;
        ExprData *_t1489 = ExprData_FieldAssign(_t1488);
        (void)_t1489;
        Str_delete(_t1488, &(Bool){1});
        ;
        return _t1489;
    }
    ;
    Bool _t1508; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1508 = *_hp; free(_hp); }
    (void)_t1508;
    if (_t1508) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t1509; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1509 = *_hp; free(_hp); }
    (void)_t1509;
    if (_t1509) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t1510; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1510 = *_hp; free(_hp); }
    (void)_t1510;
    if (_t1510) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t1511; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1511 = *_hp; free(_hp); }
    (void)_t1511;
    if (_t1511) {
        Str *_t1490 = ExprData_get_ForIn(self);
        (void)_t1490;
        ExprData *_t1491 = ExprData_ForIn(_t1490);
        (void)_t1491;
        Str_delete(_t1490, &(Bool){1});
        ;
        return _t1491;
    }
    ;
    Bool _t1512; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1512 = *_hp; free(_hp); }
    (void)_t1512;
    if (_t1512) {
        Str *_t1492 = ExprData_get_NamedArg(self);
        (void)_t1492;
        ExprData *_t1493 = ExprData_NamedArg(_t1492);
        (void)_t1493;
        Str_delete(_t1492, &(Bool){1});
        ;
        return _t1493;
    }
    ;
    Bool _t1513; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1513 = *_hp; free(_hp); }
    (void)_t1513;
    if (_t1513) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t1514; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1514 = *_hp; free(_hp); }
    (void)_t1514;
    if (_t1514) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t1515; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1515 = *_hp; free(_hp); }
    (void)_t1515;
    if (_t1515) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t1516; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1516 = *_hp; free(_hp); }
    (void)_t1516;
    if (_t1516) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t1517; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1517 = *_hp; free(_hp); }
    (void)_t1517;
    if (_t1517) {
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
    Bool _t1653; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1653 = *_hp; free(_hp); }
    (void)_t1653;
    if (_t1653) {
        Str *_t1518 = Str_lit("Body", 4ULL);
        (void)_t1518;
        ;
        return _t1518;
    }
    ;
    Bool _t1654; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1654 = *_hp; free(_hp); }
    (void)_t1654;
    if (_t1654) {
        Str *_t1519 = Str_lit("Str", 3ULL);
        (void)_t1519;
        U64 _t1520; { U64 *_hp = (U64 *)Str_size(); _t1520 = *_hp; free(_hp); }
        (void)_t1520;
        U64 _t1521 = 3;
        (void)_t1521;
        Array *_va20 = Array_new(_t1519, &(U64){_t1520}, &(U64){_t1521});
        (void)_va20;
        Str_delete(_t1519, &(Bool){1});
        ;
        ;
        U64 _t1522 = 0;
        (void)_t1522;
        Str *_t1523 = Str_lit("LiteralStr(", 11ULL);
        (void)_t1523;
        Array_set(_va20, &(U64){_t1522}, _t1523);
        ;
        Str *_t1524 = ExprData_get_LiteralStr(self);
        (void)_t1524;
        U64 _t1525 = 1;
        (void)_t1525;
        Str *_t1526 = Str_to_str(_t1524);
        (void)_t1526;
        Str_delete(_t1524, &(Bool){1});
        Array_set(_va20, &(U64){_t1525}, _t1526);
        ;
        U64 _t1527 = 2;
        (void)_t1527;
        Str *_t1528 = Str_lit(")", 1ULL);
        (void)_t1528;
        Array_set(_va20, &(U64){_t1527}, _t1528);
        ;
        Str *_t1529 = format(_va20);
        (void)_t1529;
        ;
        return _t1529;
    }
    ;
    Bool _t1655; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1655 = *_hp; free(_hp); }
    (void)_t1655;
    if (_t1655) {
        Str *_t1530 = Str_lit("Str", 3ULL);
        (void)_t1530;
        U64 _t1531; { U64 *_hp = (U64 *)Str_size(); _t1531 = *_hp; free(_hp); }
        (void)_t1531;
        U64 _t1532 = 3;
        (void)_t1532;
        Array *_va21 = Array_new(_t1530, &(U64){_t1531}, &(U64){_t1532});
        (void)_va21;
        Str_delete(_t1530, &(Bool){1});
        ;
        ;
        U64 _t1533 = 0;
        (void)_t1533;
        Str *_t1534 = Str_lit("LiteralNum(", 11ULL);
        (void)_t1534;
        Array_set(_va21, &(U64){_t1533}, _t1534);
        ;
        Str *_t1535 = ExprData_get_LiteralNum(self);
        (void)_t1535;
        U64 _t1536 = 1;
        (void)_t1536;
        Str *_t1537 = Str_to_str(_t1535);
        (void)_t1537;
        Str_delete(_t1535, &(Bool){1});
        Array_set(_va21, &(U64){_t1536}, _t1537);
        ;
        U64 _t1538 = 2;
        (void)_t1538;
        Str *_t1539 = Str_lit(")", 1ULL);
        (void)_t1539;
        Array_set(_va21, &(U64){_t1538}, _t1539);
        ;
        Str *_t1540 = format(_va21);
        (void)_t1540;
        ;
        return _t1540;
    }
    ;
    Bool _t1656; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1656 = *_hp; free(_hp); }
    (void)_t1656;
    if (_t1656) {
        Str *_t1541 = Str_lit("Str", 3ULL);
        (void)_t1541;
        U64 _t1542; { U64 *_hp = (U64 *)Str_size(); _t1542 = *_hp; free(_hp); }
        (void)_t1542;
        U64 _t1543 = 3;
        (void)_t1543;
        Array *_va22 = Array_new(_t1541, &(U64){_t1542}, &(U64){_t1543});
        (void)_va22;
        Str_delete(_t1541, &(Bool){1});
        ;
        ;
        U64 _t1544 = 0;
        (void)_t1544;
        Str *_t1545 = Str_lit("LiteralBool(", 12ULL);
        (void)_t1545;
        Array_set(_va22, &(U64){_t1544}, _t1545);
        ;
        Str *_t1546 = ExprData_get_LiteralBool(self);
        (void)_t1546;
        U64 _t1547 = 1;
        (void)_t1547;
        Str *_t1548 = Str_to_str(_t1546);
        (void)_t1548;
        Str_delete(_t1546, &(Bool){1});
        Array_set(_va22, &(U64){_t1547}, _t1548);
        ;
        U64 _t1549 = 2;
        (void)_t1549;
        Str *_t1550 = Str_lit(")", 1ULL);
        (void)_t1550;
        Array_set(_va22, &(U64){_t1549}, _t1550);
        ;
        Str *_t1551 = format(_va22);
        (void)_t1551;
        ;
        return _t1551;
    }
    ;
    Bool _t1657; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1657 = *_hp; free(_hp); }
    (void)_t1657;
    if (_t1657) {
        Str *_t1552 = Str_lit("LiteralNull", 11ULL);
        (void)_t1552;
        ;
        return _t1552;
    }
    ;
    Bool _t1658; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1658 = *_hp; free(_hp); }
    (void)_t1658;
    if (_t1658) {
        Str *_t1553 = Str_lit("Str", 3ULL);
        (void)_t1553;
        U64 _t1554; { U64 *_hp = (U64 *)Str_size(); _t1554 = *_hp; free(_hp); }
        (void)_t1554;
        U64 _t1555 = 3;
        (void)_t1555;
        Array *_va23 = Array_new(_t1553, &(U64){_t1554}, &(U64){_t1555});
        (void)_va23;
        Str_delete(_t1553, &(Bool){1});
        ;
        ;
        U64 _t1556 = 0;
        (void)_t1556;
        Str *_t1557 = Str_lit("Ident(", 6ULL);
        (void)_t1557;
        Array_set(_va23, &(U64){_t1556}, _t1557);
        ;
        Str *_t1558 = ExprData_get_Ident(self);
        (void)_t1558;
        U64 _t1559 = 1;
        (void)_t1559;
        Str *_t1560 = Str_to_str(_t1558);
        (void)_t1560;
        Str_delete(_t1558, &(Bool){1});
        Array_set(_va23, &(U64){_t1559}, _t1560);
        ;
        U64 _t1561 = 2;
        (void)_t1561;
        Str *_t1562 = Str_lit(")", 1ULL);
        (void)_t1562;
        Array_set(_va23, &(U64){_t1561}, _t1562);
        ;
        Str *_t1563 = format(_va23);
        (void)_t1563;
        ;
        return _t1563;
    }
    ;
    Bool _t1659; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1659 = *_hp; free(_hp); }
    (void)_t1659;
    if (_t1659) {
        Str *_t1564 = Str_lit("Str", 3ULL);
        (void)_t1564;
        U64 _t1565; { U64 *_hp = (U64 *)Str_size(); _t1565 = *_hp; free(_hp); }
        (void)_t1565;
        U64 _t1566 = 3;
        (void)_t1566;
        Array *_va24 = Array_new(_t1564, &(U64){_t1565}, &(U64){_t1566});
        (void)_va24;
        Str_delete(_t1564, &(Bool){1});
        ;
        ;
        U64 _t1567 = 0;
        (void)_t1567;
        Str *_t1568 = Str_lit("Decl(", 5ULL);
        (void)_t1568;
        Array_set(_va24, &(U64){_t1567}, _t1568);
        ;
        Declaration *_t1569 = ExprData_get_Decl(self);
        (void)_t1569;
        U64 _t1570 = 1;
        (void)_t1570;
        Str *_t1571 = Declaration_to_str(_t1569);
        (void)_t1571;
        Declaration_delete(_t1569, &(Bool){1});
        Array_set(_va24, &(U64){_t1570}, _t1571);
        ;
        U64 _t1572 = 2;
        (void)_t1572;
        Str *_t1573 = Str_lit(")", 1ULL);
        (void)_t1573;
        Array_set(_va24, &(U64){_t1572}, _t1573);
        ;
        Str *_t1574 = format(_va24);
        (void)_t1574;
        ;
        return _t1574;
    }
    ;
    Bool _t1660; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1660 = *_hp; free(_hp); }
    (void)_t1660;
    if (_t1660) {
        Str *_t1575 = Str_lit("Str", 3ULL);
        (void)_t1575;
        U64 _t1576; { U64 *_hp = (U64 *)Str_size(); _t1576 = *_hp; free(_hp); }
        (void)_t1576;
        U64 _t1577 = 3;
        (void)_t1577;
        Array *_va25 = Array_new(_t1575, &(U64){_t1576}, &(U64){_t1577});
        (void)_va25;
        Str_delete(_t1575, &(Bool){1});
        ;
        ;
        U64 _t1578 = 0;
        (void)_t1578;
        Str *_t1579 = Str_lit("Assign(", 7ULL);
        (void)_t1579;
        Array_set(_va25, &(U64){_t1578}, _t1579);
        ;
        Str *_t1580 = ExprData_get_Assign(self);
        (void)_t1580;
        U64 _t1581 = 1;
        (void)_t1581;
        Str *_t1582 = Str_to_str(_t1580);
        (void)_t1582;
        Str_delete(_t1580, &(Bool){1});
        Array_set(_va25, &(U64){_t1581}, _t1582);
        ;
        U64 _t1583 = 2;
        (void)_t1583;
        Str *_t1584 = Str_lit(")", 1ULL);
        (void)_t1584;
        Array_set(_va25, &(U64){_t1583}, _t1584);
        ;
        Str *_t1585 = format(_va25);
        (void)_t1585;
        ;
        return _t1585;
    }
    ;
    Bool _t1661; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1661 = *_hp; free(_hp); }
    (void)_t1661;
    if (_t1661) {
        Str *_t1586 = Str_lit("FCall", 5ULL);
        (void)_t1586;
        ;
        return _t1586;
    }
    ;
    Bool _t1662; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1662 = *_hp; free(_hp); }
    (void)_t1662;
    if (_t1662) {
        Str *_t1587 = Str_lit("Str", 3ULL);
        (void)_t1587;
        U64 _t1588; { U64 *_hp = (U64 *)Str_size(); _t1588 = *_hp; free(_hp); }
        (void)_t1588;
        U64 _t1589 = 3;
        (void)_t1589;
        Array *_va26 = Array_new(_t1587, &(U64){_t1588}, &(U64){_t1589});
        (void)_va26;
        Str_delete(_t1587, &(Bool){1});
        ;
        ;
        U64 _t1590 = 0;
        (void)_t1590;
        Str *_t1591 = Str_lit("FuncDef(", 8ULL);
        (void)_t1591;
        Array_set(_va26, &(U64){_t1590}, _t1591);
        ;
        FunctionDef *_t1592 = ExprData_get_FuncDef(self);
        (void)_t1592;
        U64 _t1593 = 1;
        (void)_t1593;
        Str *_t1594 = FunctionDef_to_str(_t1592);
        (void)_t1594;
        FunctionDef_delete(_t1592, &(Bool){1});
        Array_set(_va26, &(U64){_t1593}, _t1594);
        ;
        U64 _t1595 = 2;
        (void)_t1595;
        Str *_t1596 = Str_lit(")", 1ULL);
        (void)_t1596;
        Array_set(_va26, &(U64){_t1595}, _t1596);
        ;
        Str *_t1597 = format(_va26);
        (void)_t1597;
        ;
        return _t1597;
    }
    ;
    Bool _t1663; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1663 = *_hp; free(_hp); }
    (void)_t1663;
    if (_t1663) {
        Str *_t1598 = Str_lit("StructDef", 9ULL);
        (void)_t1598;
        ;
        return _t1598;
    }
    ;
    Bool _t1664; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1664 = *_hp; free(_hp); }
    (void)_t1664;
    if (_t1664) {
        Str *_t1599 = Str_lit("EnumDef", 7ULL);
        (void)_t1599;
        ;
        return _t1599;
    }
    ;
    Bool _t1665; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1665 = *_hp; free(_hp); }
    (void)_t1665;
    if (_t1665) {
        Str *_t1600 = Str_lit("Str", 3ULL);
        (void)_t1600;
        U64 _t1601; { U64 *_hp = (U64 *)Str_size(); _t1601 = *_hp; free(_hp); }
        (void)_t1601;
        U64 _t1602 = 3;
        (void)_t1602;
        Array *_va27 = Array_new(_t1600, &(U64){_t1601}, &(U64){_t1602});
        (void)_va27;
        Str_delete(_t1600, &(Bool){1});
        ;
        ;
        U64 _t1603 = 0;
        (void)_t1603;
        Str *_t1604 = Str_lit("FieldAccess(", 12ULL);
        (void)_t1604;
        Array_set(_va27, &(U64){_t1603}, _t1604);
        ;
        Str *_t1605 = ExprData_get_FieldAccess(self);
        (void)_t1605;
        U64 _t1606 = 1;
        (void)_t1606;
        Str *_t1607 = Str_to_str(_t1605);
        (void)_t1607;
        Str_delete(_t1605, &(Bool){1});
        Array_set(_va27, &(U64){_t1606}, _t1607);
        ;
        U64 _t1608 = 2;
        (void)_t1608;
        Str *_t1609 = Str_lit(")", 1ULL);
        (void)_t1609;
        Array_set(_va27, &(U64){_t1608}, _t1609);
        ;
        Str *_t1610 = format(_va27);
        (void)_t1610;
        ;
        return _t1610;
    }
    ;
    Bool _t1666; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1666 = *_hp; free(_hp); }
    (void)_t1666;
    if (_t1666) {
        Str *_t1611 = Str_lit("Str", 3ULL);
        (void)_t1611;
        U64 _t1612; { U64 *_hp = (U64 *)Str_size(); _t1612 = *_hp; free(_hp); }
        (void)_t1612;
        U64 _t1613 = 3;
        (void)_t1613;
        Array *_va28 = Array_new(_t1611, &(U64){_t1612}, &(U64){_t1613});
        (void)_va28;
        Str_delete(_t1611, &(Bool){1});
        ;
        ;
        U64 _t1614 = 0;
        (void)_t1614;
        Str *_t1615 = Str_lit("FieldAssign(", 12ULL);
        (void)_t1615;
        Array_set(_va28, &(U64){_t1614}, _t1615);
        ;
        Str *_t1616 = ExprData_get_FieldAssign(self);
        (void)_t1616;
        U64 _t1617 = 1;
        (void)_t1617;
        Str *_t1618 = Str_to_str(_t1616);
        (void)_t1618;
        Str_delete(_t1616, &(Bool){1});
        Array_set(_va28, &(U64){_t1617}, _t1618);
        ;
        U64 _t1619 = 2;
        (void)_t1619;
        Str *_t1620 = Str_lit(")", 1ULL);
        (void)_t1620;
        Array_set(_va28, &(U64){_t1619}, _t1620);
        ;
        Str *_t1621 = format(_va28);
        (void)_t1621;
        ;
        return _t1621;
    }
    ;
    Bool _t1667; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1667 = *_hp; free(_hp); }
    (void)_t1667;
    if (_t1667) {
        Str *_t1622 = Str_lit("Return", 6ULL);
        (void)_t1622;
        ;
        return _t1622;
    }
    ;
    Bool _t1668; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1668 = *_hp; free(_hp); }
    (void)_t1668;
    if (_t1668) {
        Str *_t1623 = Str_lit("If", 2ULL);
        (void)_t1623;
        ;
        return _t1623;
    }
    ;
    Bool _t1669; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1669 = *_hp; free(_hp); }
    (void)_t1669;
    if (_t1669) {
        Str *_t1624 = Str_lit("While", 5ULL);
        (void)_t1624;
        ;
        return _t1624;
    }
    ;
    Bool _t1670; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1670 = *_hp; free(_hp); }
    (void)_t1670;
    if (_t1670) {
        Str *_t1625 = Str_lit("Str", 3ULL);
        (void)_t1625;
        U64 _t1626; { U64 *_hp = (U64 *)Str_size(); _t1626 = *_hp; free(_hp); }
        (void)_t1626;
        U64 _t1627 = 3;
        (void)_t1627;
        Array *_va29 = Array_new(_t1625, &(U64){_t1626}, &(U64){_t1627});
        (void)_va29;
        Str_delete(_t1625, &(Bool){1});
        ;
        ;
        U64 _t1628 = 0;
        (void)_t1628;
        Str *_t1629 = Str_lit("ForIn(", 6ULL);
        (void)_t1629;
        Array_set(_va29, &(U64){_t1628}, _t1629);
        ;
        Str *_t1630 = ExprData_get_ForIn(self);
        (void)_t1630;
        U64 _t1631 = 1;
        (void)_t1631;
        Str *_t1632 = Str_to_str(_t1630);
        (void)_t1632;
        Str_delete(_t1630, &(Bool){1});
        Array_set(_va29, &(U64){_t1631}, _t1632);
        ;
        U64 _t1633 = 2;
        (void)_t1633;
        Str *_t1634 = Str_lit(")", 1ULL);
        (void)_t1634;
        Array_set(_va29, &(U64){_t1633}, _t1634);
        ;
        Str *_t1635 = format(_va29);
        (void)_t1635;
        ;
        return _t1635;
    }
    ;
    Bool _t1671; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1671 = *_hp; free(_hp); }
    (void)_t1671;
    if (_t1671) {
        Str *_t1636 = Str_lit("Str", 3ULL);
        (void)_t1636;
        U64 _t1637; { U64 *_hp = (U64 *)Str_size(); _t1637 = *_hp; free(_hp); }
        (void)_t1637;
        U64 _t1638 = 3;
        (void)_t1638;
        Array *_va30 = Array_new(_t1636, &(U64){_t1637}, &(U64){_t1638});
        (void)_va30;
        Str_delete(_t1636, &(Bool){1});
        ;
        ;
        U64 _t1639 = 0;
        (void)_t1639;
        Str *_t1640 = Str_lit("NamedArg(", 9ULL);
        (void)_t1640;
        Array_set(_va30, &(U64){_t1639}, _t1640);
        ;
        Str *_t1641 = ExprData_get_NamedArg(self);
        (void)_t1641;
        U64 _t1642 = 1;
        (void)_t1642;
        Str *_t1643 = Str_to_str(_t1641);
        (void)_t1643;
        Str_delete(_t1641, &(Bool){1});
        Array_set(_va30, &(U64){_t1642}, _t1643);
        ;
        U64 _t1644 = 2;
        (void)_t1644;
        Str *_t1645 = Str_lit(")", 1ULL);
        (void)_t1645;
        Array_set(_va30, &(U64){_t1644}, _t1645);
        ;
        Str *_t1646 = format(_va30);
        (void)_t1646;
        ;
        return _t1646;
    }
    ;
    Bool _t1672; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1672 = *_hp; free(_hp); }
    (void)_t1672;
    if (_t1672) {
        Str *_t1647 = Str_lit("Break", 5ULL);
        (void)_t1647;
        ;
        return _t1647;
    }
    ;
    Bool _t1673; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1673 = *_hp; free(_hp); }
    (void)_t1673;
    if (_t1673) {
        Str *_t1648 = Str_lit("Continue", 8ULL);
        (void)_t1648;
        ;
        return _t1648;
    }
    ;
    Bool _t1674; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1674 = *_hp; free(_hp); }
    (void)_t1674;
    if (_t1674) {
        Str *_t1649 = Str_lit("MapLit", 6ULL);
        (void)_t1649;
        ;
        return _t1649;
    }
    ;
    Bool _t1675; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1675 = *_hp; free(_hp); }
    (void)_t1675;
    if (_t1675) {
        Str *_t1650 = Str_lit("SetLit", 6ULL);
        (void)_t1650;
        ;
        return _t1650;
    }
    ;
    Bool _t1676; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1676 = *_hp; free(_hp); }
    (void)_t1676;
    if (_t1676) {
        Str *_t1651 = Str_lit("Switch", 6ULL);
        (void)_t1651;
        ;
        return _t1651;
    }
    ;
    Bool _t1677; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1677 = *_hp; free(_hp); }
    (void)_t1677;
    if (_t1677) {
        Str *_t1652 = Str_lit("Case", 4ULL);
        (void)_t1652;
        ;
        return _t1652;
    }
    ;
    Str *_t1678 = Str_lit("unknown", 7ULL);
    (void)_t1678;
    return _t1678;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t1680 = Str_lit("Str", 3ULL);
    (void)_t1680;
    U64 _t1681; { U64 *_hp = (U64 *)Str_size(); _t1681 = *_hp; free(_hp); }
    (void)_t1681;
    U64 _t1682 = 7;
    (void)_t1682;
    Array *_va31 = Array_new(_t1680, &(U64){_t1681}, &(U64){_t1682});
    (void)_va31;
    Str_delete(_t1680, &(Bool){1});
    ;
    ;
    U64 _t1683 = 0;
    (void)_t1683;
    Str *_t1684 = Str_clone(&self->path);
    (void)_t1684;
    Array_set(_va31, &(U64){_t1683}, _t1684);
    ;
    U64 _t1685 = 1;
    (void)_t1685;
    Str *_t1686 = Str_lit(":", 1ULL);
    (void)_t1686;
    Array_set(_va31, &(U64){_t1685}, _t1686);
    ;
    U64 _t1687 = 2;
    (void)_t1687;
    Str *_t1688 = U32_to_str(&self->line);
    (void)_t1688;
    Array_set(_va31, &(U64){_t1687}, _t1688);
    ;
    U64 _t1689 = 3;
    (void)_t1689;
    Str *_t1690 = Str_lit(":", 1ULL);
    (void)_t1690;
    Array_set(_va31, &(U64){_t1689}, _t1690);
    ;
    U64 _t1691 = 4;
    (void)_t1691;
    Str *_t1692 = U32_to_str(&self->col);
    (void)_t1692;
    Array_set(_va31, &(U64){_t1691}, _t1692);
    ;
    U64 _t1693 = 5;
    (void)_t1693;
    Str *_t1694 = Str_lit(": error: ", 9ULL);
    (void)_t1694;
    Array_set(_va31, &(U64){_t1693}, _t1694);
    ;
    U64 _t1695 = 6;
    (void)_t1695;
    Str *_t1696 = Str_clone(msg);
    (void)_t1696;
    Array_set(_va31, &(U64){_t1695}, _t1696);
    ;
    println(_va31);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1697 = Str_lit("Str", 3ULL);
    (void)_t1697;
    U64 _t1698; { U64 *_hp = (U64 *)Str_size(); _t1698 = *_hp; free(_hp); }
    (void)_t1698;
    U64 _t1699 = 1;
    (void)_t1699;
    Array *_va32 = Array_new(_t1697, &(U64){_t1698}, &(U64){_t1699});
    (void)_va32;
    Str_delete(_t1697, &(Bool){1});
    ;
    ;
    U64 _t1700 = 0;
    (void)_t1700;
    Str *_t1701 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t1701;
    Array_set(_va32, &(U64){_t1700}, _t1701);
    ;
    println(_va32);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1702 = Str_lit("Str", 3ULL);
    (void)_t1702;
    U64 _t1703; { U64 *_hp = (U64 *)Str_size(); _t1703 = *_hp; free(_hp); }
    (void)_t1703;
    U64 _t1704 = 1;
    (void)_t1704;
    Array *_va33 = Array_new(_t1702, &(U64){_t1703}, &(U64){_t1704});
    (void)_va33;
    Str_delete(_t1702, &(Bool){1});
    ;
    ;
    U64 _t1705 = 0;
    (void)_t1705;
    Str *_t1706 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t1706;
    Array_set(_va33, &(U64){_t1705}, _t1706);
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
    U64 *_t1707 = malloc(sizeof(U64)); *_t1707 = I64_to_u64(DEREF(i));
    (void)_t1707;
    Expr *c = Vec_get(&parent->children, _t1707);
    (void)c;
    U64_delete(_t1707, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t1708; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t1708 = *_hp; free(_hp); }
    (void)_t1708;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t1708; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t1709 = 0;
    (void)_t1709;
    I64 _t1710 = 1;
    (void)_t1710;
    I64 _t1711 = I64_sub(_t1709, _t1710);
    (void)_t1711;
    ;
    ;
    I64 _t1712 = 0;
    (void)_t1712;
    I64 _t1713 = 1;
    (void)_t1713;
    I64 _t1714 = I64_sub(_t1712, _t1713);
    (void)_t1714;
    ;
    ;
    Str *_t1715 = Str_lit("", 0ULL);
    (void)_t1715;
    U64 _t1716; { U64 *_hp = (U64 *)Expr_size(); _t1716 = *_hp; free(_hp); }
    (void)_t1716;
    Bool _t1717 = 0;
    (void)_t1717;
    Bool _t1718 = 0;
    (void)_t1718;
    Bool _t1719 = 0;
    (void)_t1719;
    Bool _t1720 = 0;
    (void)_t1720;
    Bool _t1721 = 0;
    (void)_t1721;
    Bool _t1722 = 0;
    (void)_t1722;
    Bool _t1723 = 0;
    (void)_t1723;
    Bool _t1724 = 0;
    (void)_t1724;
    I32 _t1725 = 0;
    (void)_t1725;
    I32 _t1726 = I64_to_i32(_t1711);
    (void)_t1726;
    ;
    U32 _t1727 = 0;
    (void)_t1727;
    I32 _t1728 = I64_to_i32(_t1714);
    (void)_t1728;
    ;
    U32 _t1729 = 0;
    (void)_t1729;
    U32 _t1730 = U32_clone(&(U32){col});
    (void)_t1730;
    Str *_t1731 = Str_clone(path);
    (void)_t1731;
    Expr *_t1732 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t1732->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t1732->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1732->struct_name = *_ca; free(_ca); }
    _t1732->is_own_arg = _t1717;
    _t1732->is_splat = _t1718;
    _t1732->is_own_field = _t1719;
    _t1732->is_ref_field = _t1720;
    _t1732->is_ns_field = _t1721;
    _t1732->is_ext = _t1722;
    _t1732->is_core = _t1723;
    _t1732->save_old_delete = _t1724;
    _t1732->total_struct_size = _t1725;
    _t1732->variadic_index = _t1726;
    _t1732->variadic_count = _t1727;
    _t1732->kwargs_index = _t1728;
    _t1732->kwargs_count = _t1729;
    _t1732->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t1715, &(U64){_t1716}); _t1732->children = *_ca; free(_ca); }
    _t1732->line = U32_clone(&(U32){line});
    _t1732->col = _t1730;
    { Str *_ca = Str_clone(_t1731); _t1732->path = *_ca; free(_ca); }
    (void)_t1732;
    Str_delete(_t1715, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t1731, &(Bool){1});
    return _t1732;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t1740 = Str_lit("", 0ULL);
    (void)_t1740;
    U64 _t1741; { U64 *_hp = (U64 *)Expr_size(); _t1741 = *_hp; free(_hp); }
    (void)_t1741;
    Vec *new_children = Vec_new(_t1740, &(U64){_t1741});
    (void)new_children;
    Str_delete(_t1740, &(Bool){1});
    ;
    {
        U64 _t1738 = 0;
        (void)_t1738;
        U64 _t1739; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1739 = *_hp; free(_hp); }
        (void)_t1739;
        Range *_fc1733 = Range_new(_t1738, _t1739);
        (void)_fc1733;
        ;
        ;
        U64 _fi1733 = 0;
        (void)_fi1733;
        while (1) {
            U64 _t1735; { U64 *_hp = (U64 *)Range_len(_fc1733); _t1735 = *_hp; free(_hp); }
            (void)_t1735;
            Bool _wcond1734; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1733}, &(U64){_t1735}); _wcond1734 = *_hp; free(_hp); }
            (void)_wcond1734;
            ;
            if (_wcond1734) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1733, _fi1733);
            (void)i;
            U64 _t1736 = 1;
            (void)_t1736;
            U64 _t1737 = U64_add(_fi1733, _t1736);
            (void)_t1737;
            ;
            _fi1733 = _t1737;
            ;
            Expr *c = Vec_get(&self->children, i);
            (void)c;
            Expr *cloned = Expr_clone(c);
            (void)cloned;
            U64_delete(i, &(Bool){1});
            Vec_push(new_children, cloned);
        }
        Range_delete(_fc1733, &(Bool){1});
        ;
    }
    Expr *_t1742 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t1742->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t1742->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t1742->struct_name = *_ca; free(_ca); }
    _t1742->is_own_arg = self->is_own_arg;
    _t1742->is_splat = self->is_splat;
    _t1742->is_own_field = self->is_own_field;
    _t1742->is_ref_field = self->is_ref_field;
    _t1742->is_ns_field = self->is_ns_field;
    _t1742->is_ext = self->is_ext;
    _t1742->is_core = self->is_core;
    _t1742->save_old_delete = self->save_old_delete;
    _t1742->total_struct_size = self->total_struct_size;
    _t1742->variadic_index = self->variadic_index;
    _t1742->variadic_count = self->variadic_count;
    _t1742->kwargs_index = self->kwargs_index;
    _t1742->kwargs_count = self->kwargs_count;
    _t1742->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t1742->children = *_ca; free(_ca); }
    _t1742->line = self->line;
    _t1742->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t1742->path = *_ca; free(_ca); }
    (void)_t1742;
    Vec_delete(new_children, &(Bool){1});
    return _t1742;
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
    Bool _t2103; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t2103 = *_hp; free(_hp); }
    (void)_t2103;
    if (_t2103) {
        Bool _t2037; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t2037 = *_hp; free(_hp); }
        (void)_t2037;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2037; return _r; }
    }
    ;
    Bool _t2104; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t2104 = *_hp; free(_hp); }
    (void)_t2104;
    if (_t2104) {
        Bool _t2038; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t2038 = *_hp; free(_hp); }
        (void)_t2038;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2038; return _r; }
    }
    ;
    Bool _t2105; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t2105 = *_hp; free(_hp); }
    (void)_t2105;
    if (_t2105) {
        Bool _t2039; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t2039 = *_hp; free(_hp); }
        (void)_t2039;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2039; return _r; }
    }
    ;
    Bool _t2106; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t2106 = *_hp; free(_hp); }
    (void)_t2106;
    if (_t2106) {
        Bool _t2040; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t2040 = *_hp; free(_hp); }
        (void)_t2040;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2040; return _r; }
    }
    ;
    Bool _t2107; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t2107 = *_hp; free(_hp); }
    (void)_t2107;
    if (_t2107) {
        Bool _t2041; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t2041 = *_hp; free(_hp); }
        (void)_t2041;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2041; return _r; }
    }
    ;
    Bool _t2108; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t2108 = *_hp; free(_hp); }
    (void)_t2108;
    if (_t2108) {
        Bool _t2042; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t2042 = *_hp; free(_hp); }
        (void)_t2042;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2042; return _r; }
    }
    ;
    Bool _t2109; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t2109 = *_hp; free(_hp); }
    (void)_t2109;
    if (_t2109) {
        Bool _t2043; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t2043 = *_hp; free(_hp); }
        (void)_t2043;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2043; return _r; }
    }
    ;
    Bool _t2110; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t2110 = *_hp; free(_hp); }
    (void)_t2110;
    if (_t2110) {
        Bool _t2044; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t2044 = *_hp; free(_hp); }
        (void)_t2044;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2044; return _r; }
    }
    ;
    Bool _t2111; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t2111 = *_hp; free(_hp); }
    (void)_t2111;
    if (_t2111) {
        Bool _t2045; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t2045 = *_hp; free(_hp); }
        (void)_t2045;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2045; return _r; }
    }
    ;
    Bool _t2112; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t2112 = *_hp; free(_hp); }
    (void)_t2112;
    if (_t2112) {
        Bool _t2046; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t2046 = *_hp; free(_hp); }
        (void)_t2046;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2046; return _r; }
    }
    ;
    Bool _t2113; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t2113 = *_hp; free(_hp); }
    (void)_t2113;
    if (_t2113) {
        Bool _t2047; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t2047 = *_hp; free(_hp); }
        (void)_t2047;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2047; return _r; }
    }
    ;
    Bool _t2114; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t2114 = *_hp; free(_hp); }
    (void)_t2114;
    if (_t2114) {
        Bool _t2048; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t2048 = *_hp; free(_hp); }
        (void)_t2048;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2048; return _r; }
    }
    ;
    Bool _t2115; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t2115 = *_hp; free(_hp); }
    (void)_t2115;
    if (_t2115) {
        Bool _t2049; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t2049 = *_hp; free(_hp); }
        (void)_t2049;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2049; return _r; }
    }
    ;
    Bool _t2116; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t2116 = *_hp; free(_hp); }
    (void)_t2116;
    if (_t2116) {
        Bool _t2050; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t2050 = *_hp; free(_hp); }
        (void)_t2050;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2050; return _r; }
    }
    ;
    Bool _t2117; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t2117 = *_hp; free(_hp); }
    (void)_t2117;
    if (_t2117) {
        Bool _t2051; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t2051 = *_hp; free(_hp); }
        (void)_t2051;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2051; return _r; }
    }
    ;
    Bool _t2118; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t2118 = *_hp; free(_hp); }
    (void)_t2118;
    if (_t2118) {
        Bool _t2052; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t2052 = *_hp; free(_hp); }
        (void)_t2052;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2052; return _r; }
    }
    ;
    Bool _t2119; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t2119 = *_hp; free(_hp); }
    (void)_t2119;
    if (_t2119) {
        Bool _t2053; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t2053 = *_hp; free(_hp); }
        (void)_t2053;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2053; return _r; }
    }
    ;
    Bool _t2120; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t2120 = *_hp; free(_hp); }
    (void)_t2120;
    if (_t2120) {
        Bool _t2054; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t2054 = *_hp; free(_hp); }
        (void)_t2054;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2054; return _r; }
    }
    ;
    Bool _t2121; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t2121 = *_hp; free(_hp); }
    (void)_t2121;
    if (_t2121) {
        Bool _t2055; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t2055 = *_hp; free(_hp); }
        (void)_t2055;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2055; return _r; }
    }
    ;
    Bool _t2122; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t2122 = *_hp; free(_hp); }
    (void)_t2122;
    if (_t2122) {
        Bool _t2056; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t2056 = *_hp; free(_hp); }
        (void)_t2056;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2056; return _r; }
    }
    ;
    Bool _t2123; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t2123 = *_hp; free(_hp); }
    (void)_t2123;
    if (_t2123) {
        Bool _t2057; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t2057 = *_hp; free(_hp); }
        (void)_t2057;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2057; return _r; }
    }
    ;
    Bool _t2124; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t2124 = *_hp; free(_hp); }
    (void)_t2124;
    if (_t2124) {
        Bool _t2058; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t2058 = *_hp; free(_hp); }
        (void)_t2058;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2058; return _r; }
    }
    ;
    Bool _t2125; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t2125 = *_hp; free(_hp); }
    (void)_t2125;
    if (_t2125) {
        Bool _t2059; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t2059 = *_hp; free(_hp); }
        (void)_t2059;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2059; return _r; }
    }
    ;
    Bool _t2126; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t2126 = *_hp; free(_hp); }
    (void)_t2126;
    if (_t2126) {
        Bool _t2060; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t2060 = *_hp; free(_hp); }
        (void)_t2060;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2060; return _r; }
    }
    ;
    Bool _t2127; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t2127 = *_hp; free(_hp); }
    (void)_t2127;
    if (_t2127) {
        Bool _t2061; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t2061 = *_hp; free(_hp); }
        (void)_t2061;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2061; return _r; }
    }
    ;
    Bool _t2128; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t2128 = *_hp; free(_hp); }
    (void)_t2128;
    if (_t2128) {
        Bool _t2062; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t2062 = *_hp; free(_hp); }
        (void)_t2062;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2062; return _r; }
    }
    ;
    Bool _t2129; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t2129 = *_hp; free(_hp); }
    (void)_t2129;
    if (_t2129) {
        Bool _t2063; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t2063 = *_hp; free(_hp); }
        (void)_t2063;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2063; return _r; }
    }
    ;
    Bool _t2130; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t2130 = *_hp; free(_hp); }
    (void)_t2130;
    if (_t2130) {
        Bool _t2064; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t2064 = *_hp; free(_hp); }
        (void)_t2064;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2064; return _r; }
    }
    ;
    Bool _t2131; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t2131 = *_hp; free(_hp); }
    (void)_t2131;
    if (_t2131) {
        Bool _t2065; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t2065 = *_hp; free(_hp); }
        (void)_t2065;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2065; return _r; }
    }
    ;
    Bool _t2132; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t2132 = *_hp; free(_hp); }
    (void)_t2132;
    if (_t2132) {
        Bool _t2066; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t2066 = *_hp; free(_hp); }
        (void)_t2066;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2066; return _r; }
    }
    ;
    Bool _t2133; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t2133 = *_hp; free(_hp); }
    (void)_t2133;
    if (_t2133) {
        Bool _t2067; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t2067 = *_hp; free(_hp); }
        (void)_t2067;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2067; return _r; }
    }
    ;
    Bool _t2134; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t2134 = *_hp; free(_hp); }
    (void)_t2134;
    if (_t2134) {
        Bool _t2068; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t2068 = *_hp; free(_hp); }
        (void)_t2068;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2068; return _r; }
    }
    ;
    Bool _t2135; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t2135 = *_hp; free(_hp); }
    (void)_t2135;
    if (_t2135) {
        Bool _t2069; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t2069 = *_hp; free(_hp); }
        (void)_t2069;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2069; return _r; }
    }
    ;
    Bool _t2136; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t2136 = *_hp; free(_hp); }
    (void)_t2136;
    if (_t2136) {
        Bool _t2070; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t2070 = *_hp; free(_hp); }
        (void)_t2070;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2070; return _r; }
    }
    ;
    Bool _t2137; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t2137 = *_hp; free(_hp); }
    (void)_t2137;
    if (_t2137) {
        Bool _t2071; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t2071 = *_hp; free(_hp); }
        (void)_t2071;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2071; return _r; }
    }
    ;
    Bool _t2138; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t2138 = *_hp; free(_hp); }
    (void)_t2138;
    if (_t2138) {
        Bool _t2072; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t2072 = *_hp; free(_hp); }
        (void)_t2072;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2072; return _r; }
    }
    ;
    Bool _t2139; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t2139 = *_hp; free(_hp); }
    (void)_t2139;
    if (_t2139) {
        Bool _t2073; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t2073 = *_hp; free(_hp); }
        (void)_t2073;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2073; return _r; }
    }
    ;
    Bool _t2140; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t2140 = *_hp; free(_hp); }
    (void)_t2140;
    if (_t2140) {
        Bool _t2074; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t2074 = *_hp; free(_hp); }
        (void)_t2074;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2074; return _r; }
    }
    ;
    Bool _t2141; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t2141 = *_hp; free(_hp); }
    (void)_t2141;
    if (_t2141) {
        Bool _t2075; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t2075 = *_hp; free(_hp); }
        (void)_t2075;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2075; return _r; }
    }
    ;
    Bool _t2142; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t2142 = *_hp; free(_hp); }
    (void)_t2142;
    if (_t2142) {
        Bool _t2076; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t2076 = *_hp; free(_hp); }
        (void)_t2076;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2076; return _r; }
    }
    ;
    Bool _t2143; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t2143 = *_hp; free(_hp); }
    (void)_t2143;
    if (_t2143) {
        Bool _t2077; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t2077 = *_hp; free(_hp); }
        (void)_t2077;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2077; return _r; }
    }
    ;
    Bool _t2144; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t2144 = *_hp; free(_hp); }
    (void)_t2144;
    if (_t2144) {
        Bool _t2078; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t2078 = *_hp; free(_hp); }
        (void)_t2078;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2078; return _r; }
    }
    ;
    Bool _t2145; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t2145 = *_hp; free(_hp); }
    (void)_t2145;
    if (_t2145) {
        Bool _t2079; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t2079 = *_hp; free(_hp); }
        (void)_t2079;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2079; return _r; }
    }
    ;
    Bool _t2146; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t2146 = *_hp; free(_hp); }
    (void)_t2146;
    if (_t2146) {
        Bool _t2080; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t2080 = *_hp; free(_hp); }
        (void)_t2080;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2080; return _r; }
    }
    ;
    Bool _t2147; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t2147 = *_hp; free(_hp); }
    (void)_t2147;
    if (_t2147) {
        Bool _t2081; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t2081 = *_hp; free(_hp); }
        (void)_t2081;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2081; return _r; }
    }
    ;
    Bool _t2148; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t2148 = *_hp; free(_hp); }
    (void)_t2148;
    if (_t2148) {
        Bool _t2082; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t2082 = *_hp; free(_hp); }
        (void)_t2082;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2082; return _r; }
    }
    ;
    Bool _t2149; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t2149 = *_hp; free(_hp); }
    (void)_t2149;
    if (_t2149) {
        Bool _t2083; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t2083 = *_hp; free(_hp); }
        (void)_t2083;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2083; return _r; }
    }
    ;
    Bool _t2150; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t2150 = *_hp; free(_hp); }
    (void)_t2150;
    if (_t2150) {
        Bool _t2084; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t2084 = *_hp; free(_hp); }
        (void)_t2084;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2084; return _r; }
    }
    ;
    Bool _t2151; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t2151 = *_hp; free(_hp); }
    (void)_t2151;
    if (_t2151) {
        Bool _t2085; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t2085 = *_hp; free(_hp); }
        (void)_t2085;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2085; return _r; }
    }
    ;
    Bool _t2152; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t2152 = *_hp; free(_hp); }
    (void)_t2152;
    if (_t2152) {
        Bool _t2086; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t2086 = *_hp; free(_hp); }
        (void)_t2086;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2086; return _r; }
    }
    ;
    Bool _t2153; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t2153 = *_hp; free(_hp); }
    (void)_t2153;
    if (_t2153) {
        Bool _t2087; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t2087 = *_hp; free(_hp); }
        (void)_t2087;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2087; return _r; }
    }
    ;
    Bool _t2154; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t2154 = *_hp; free(_hp); }
    (void)_t2154;
    if (_t2154) {
        Bool _t2088; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t2088 = *_hp; free(_hp); }
        (void)_t2088;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2088; return _r; }
    }
    ;
    Bool _t2155; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t2155 = *_hp; free(_hp); }
    (void)_t2155;
    if (_t2155) {
        Bool _t2089; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t2089 = *_hp; free(_hp); }
        (void)_t2089;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2089; return _r; }
    }
    ;
    Bool _t2156; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t2156 = *_hp; free(_hp); }
    (void)_t2156;
    if (_t2156) {
        Bool _t2090; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t2090 = *_hp; free(_hp); }
        (void)_t2090;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2090; return _r; }
    }
    ;
    Bool _t2157; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t2157 = *_hp; free(_hp); }
    (void)_t2157;
    if (_t2157) {
        Bool _t2091; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t2091 = *_hp; free(_hp); }
        (void)_t2091;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2091; return _r; }
    }
    ;
    Bool _t2158; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t2158 = *_hp; free(_hp); }
    (void)_t2158;
    if (_t2158) {
        Bool _t2092; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t2092 = *_hp; free(_hp); }
        (void)_t2092;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2092; return _r; }
    }
    ;
    Bool _t2159; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t2159 = *_hp; free(_hp); }
    (void)_t2159;
    if (_t2159) {
        Bool _t2093; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t2093 = *_hp; free(_hp); }
        (void)_t2093;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2093; return _r; }
    }
    ;
    Bool _t2160; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t2160 = *_hp; free(_hp); }
    (void)_t2160;
    if (_t2160) {
        Bool _t2094; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t2094 = *_hp; free(_hp); }
        (void)_t2094;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2094; return _r; }
    }
    ;
    Bool _t2161; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t2161 = *_hp; free(_hp); }
    (void)_t2161;
    if (_t2161) {
        Bool _t2095; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t2095 = *_hp; free(_hp); }
        (void)_t2095;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2095; return _r; }
    }
    ;
    Bool _t2162; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t2162 = *_hp; free(_hp); }
    (void)_t2162;
    if (_t2162) {
        Bool _t2096; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t2096 = *_hp; free(_hp); }
        (void)_t2096;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2096; return _r; }
    }
    ;
    Bool _t2163; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t2163 = *_hp; free(_hp); }
    (void)_t2163;
    if (_t2163) {
        Bool _t2097; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t2097 = *_hp; free(_hp); }
        (void)_t2097;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2097; return _r; }
    }
    ;
    Bool _t2164; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t2164 = *_hp; free(_hp); }
    (void)_t2164;
    if (_t2164) {
        Bool _t2098; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t2098 = *_hp; free(_hp); }
        (void)_t2098;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2098; return _r; }
    }
    ;
    Bool _t2165; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t2165 = *_hp; free(_hp); }
    (void)_t2165;
    if (_t2165) {
        Bool _t2099; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t2099 = *_hp; free(_hp); }
        (void)_t2099;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2099; return _r; }
    }
    ;
    Bool _t2166; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t2166 = *_hp; free(_hp); }
    (void)_t2166;
    if (_t2166) {
        Bool _t2100; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t2100 = *_hp; free(_hp); }
        (void)_t2100;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2100; return _r; }
    }
    ;
    Bool _t2167; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t2167 = *_hp; free(_hp); }
    (void)_t2167;
    if (_t2167) {
        Bool _t2101; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t2101 = *_hp; free(_hp); }
        (void)_t2101;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2101; return _r; }
    }
    ;
    Bool _t2168; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t2168 = *_hp; free(_hp); }
    (void)_t2168;
    if (_t2168) {
        Bool _t2102; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t2102 = *_hp; free(_hp); }
        (void)_t2102;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2102; return _r; }
    }
    ;
    Bool _t2169 = 0;
    (void)_t2169;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2169; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t2170; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2170 = *_hp; free(_hp); }
    (void)_t2170;
    if (_t2170) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t2171; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2171 = *_hp; free(_hp); }
    (void)_t2171;
    if (_t2171) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t2172; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2172 = *_hp; free(_hp); }
    (void)_t2172;
    if (_t2172) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t2173; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2173 = *_hp; free(_hp); }
    (void)_t2173;
    if (_t2173) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t2174; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2174 = *_hp; free(_hp); }
    (void)_t2174;
    if (_t2174) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t2175; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2175 = *_hp; free(_hp); }
    (void)_t2175;
    if (_t2175) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t2176; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2176 = *_hp; free(_hp); }
    (void)_t2176;
    if (_t2176) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t2177; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2177 = *_hp; free(_hp); }
    (void)_t2177;
    if (_t2177) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t2178; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2178 = *_hp; free(_hp); }
    (void)_t2178;
    if (_t2178) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t2179; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2179 = *_hp; free(_hp); }
    (void)_t2179;
    if (_t2179) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t2180; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2180 = *_hp; free(_hp); }
    (void)_t2180;
    if (_t2180) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t2181; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2181 = *_hp; free(_hp); }
    (void)_t2181;
    if (_t2181) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t2182; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2182 = *_hp; free(_hp); }
    (void)_t2182;
    if (_t2182) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t2183; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2183 = *_hp; free(_hp); }
    (void)_t2183;
    if (_t2183) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t2184; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2184 = *_hp; free(_hp); }
    (void)_t2184;
    if (_t2184) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t2185; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2185 = *_hp; free(_hp); }
    (void)_t2185;
    if (_t2185) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t2186; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2186 = *_hp; free(_hp); }
    (void)_t2186;
    if (_t2186) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t2187; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2187 = *_hp; free(_hp); }
    (void)_t2187;
    if (_t2187) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t2188; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2188 = *_hp; free(_hp); }
    (void)_t2188;
    if (_t2188) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t2189; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2189 = *_hp; free(_hp); }
    (void)_t2189;
    if (_t2189) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t2190; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2190 = *_hp; free(_hp); }
    (void)_t2190;
    if (_t2190) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t2191; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2191 = *_hp; free(_hp); }
    (void)_t2191;
    if (_t2191) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t2192; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2192 = *_hp; free(_hp); }
    (void)_t2192;
    if (_t2192) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t2193; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2193 = *_hp; free(_hp); }
    (void)_t2193;
    if (_t2193) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t2194; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2194 = *_hp; free(_hp); }
    (void)_t2194;
    if (_t2194) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t2195; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2195 = *_hp; free(_hp); }
    (void)_t2195;
    if (_t2195) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t2196; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2196 = *_hp; free(_hp); }
    (void)_t2196;
    if (_t2196) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t2197; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2197 = *_hp; free(_hp); }
    (void)_t2197;
    if (_t2197) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t2198; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2198 = *_hp; free(_hp); }
    (void)_t2198;
    if (_t2198) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t2199; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2199 = *_hp; free(_hp); }
    (void)_t2199;
    if (_t2199) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t2200; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2200 = *_hp; free(_hp); }
    (void)_t2200;
    if (_t2200) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t2201; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2201 = *_hp; free(_hp); }
    (void)_t2201;
    if (_t2201) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t2202; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2202 = *_hp; free(_hp); }
    (void)_t2202;
    if (_t2202) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t2203; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2203 = *_hp; free(_hp); }
    (void)_t2203;
    if (_t2203) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t2204; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2204 = *_hp; free(_hp); }
    (void)_t2204;
    if (_t2204) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t2205; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2205 = *_hp; free(_hp); }
    (void)_t2205;
    if (_t2205) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t2206; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
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
    Bool _t2301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2301 = *_hp; free(_hp); }
    (void)_t2301;
    if (_t2301) {
        Str *_t2235 = Str_lit("Eof", 3ULL);
        (void)_t2235;
        ;
        return _t2235;
    }
    ;
    Bool _t2302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2302 = *_hp; free(_hp); }
    (void)_t2302;
    if (_t2302) {
        Str *_t2236 = Str_lit("LParen", 6ULL);
        (void)_t2236;
        ;
        return _t2236;
    }
    ;
    Bool _t2303; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2303 = *_hp; free(_hp); }
    (void)_t2303;
    if (_t2303) {
        Str *_t2237 = Str_lit("RParen", 6ULL);
        (void)_t2237;
        ;
        return _t2237;
    }
    ;
    Bool _t2304; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2304 = *_hp; free(_hp); }
    (void)_t2304;
    if (_t2304) {
        Str *_t2238 = Str_lit("LBrace", 6ULL);
        (void)_t2238;
        ;
        return _t2238;
    }
    ;
    Bool _t2305; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2305 = *_hp; free(_hp); }
    (void)_t2305;
    if (_t2305) {
        Str *_t2239 = Str_lit("RBrace", 6ULL);
        (void)_t2239;
        ;
        return _t2239;
    }
    ;
    Bool _t2306; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2306 = *_hp; free(_hp); }
    (void)_t2306;
    if (_t2306) {
        Str *_t2240 = Str_lit("LBracket", 8ULL);
        (void)_t2240;
        ;
        return _t2240;
    }
    ;
    Bool _t2307; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2307 = *_hp; free(_hp); }
    (void)_t2307;
    if (_t2307) {
        Str *_t2241 = Str_lit("RBracket", 8ULL);
        (void)_t2241;
        ;
        return _t2241;
    }
    ;
    Bool _t2308; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2308 = *_hp; free(_hp); }
    (void)_t2308;
    if (_t2308) {
        Str *_t2242 = Str_lit("Comma", 5ULL);
        (void)_t2242;
        ;
        return _t2242;
    }
    ;
    Bool _t2309; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2309 = *_hp; free(_hp); }
    (void)_t2309;
    if (_t2309) {
        Str *_t2243 = Str_lit("Colon", 5ULL);
        (void)_t2243;
        ;
        return _t2243;
    }
    ;
    Bool _t2310; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2310 = *_hp; free(_hp); }
    (void)_t2310;
    if (_t2310) {
        Str *_t2244 = Str_lit("Question", 8ULL);
        (void)_t2244;
        ;
        return _t2244;
    }
    ;
    Bool _t2311; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2311 = *_hp; free(_hp); }
    (void)_t2311;
    if (_t2311) {
        Str *_t2245 = Str_lit("Bang", 4ULL);
        (void)_t2245;
        ;
        return _t2245;
    }
    ;
    Bool _t2312; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2312 = *_hp; free(_hp); }
    (void)_t2312;
    if (_t2312) {
        Str *_t2246 = Str_lit("Minus", 5ULL);
        (void)_t2246;
        ;
        return _t2246;
    }
    ;
    Bool _t2313; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2313 = *_hp; free(_hp); }
    (void)_t2313;
    if (_t2313) {
        Str *_t2247 = Str_lit("Plus", 4ULL);
        (void)_t2247;
        ;
        return _t2247;
    }
    ;
    Bool _t2314; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2314 = *_hp; free(_hp); }
    (void)_t2314;
    if (_t2314) {
        Str *_t2248 = Str_lit("Star", 4ULL);
        (void)_t2248;
        ;
        return _t2248;
    }
    ;
    Bool _t2315; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2315 = *_hp; free(_hp); }
    (void)_t2315;
    if (_t2315) {
        Str *_t2249 = Str_lit("Slash", 5ULL);
        (void)_t2249;
        ;
        return _t2249;
    }
    ;
    Bool _t2316; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2316 = *_hp; free(_hp); }
    (void)_t2316;
    if (_t2316) {
        Str *_t2250 = Str_lit("Dot", 3ULL);
        (void)_t2250;
        ;
        return _t2250;
    }
    ;
    Bool _t2317; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2317 = *_hp; free(_hp); }
    (void)_t2317;
    if (_t2317) {
        Str *_t2251 = Str_lit("DotDot", 6ULL);
        (void)_t2251;
        ;
        return _t2251;
    }
    ;
    Bool _t2318; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2318 = *_hp; free(_hp); }
    (void)_t2318;
    if (_t2318) {
        Str *_t2252 = Str_lit("DotDotDot", 9ULL);
        (void)_t2252;
        ;
        return _t2252;
    }
    ;
    Bool _t2319; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2319 = *_hp; free(_hp); }
    (void)_t2319;
    if (_t2319) {
        Str *_t2253 = Str_lit("Eq", 2ULL);
        (void)_t2253;
        ;
        return _t2253;
    }
    ;
    Bool _t2320; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2320 = *_hp; free(_hp); }
    (void)_t2320;
    if (_t2320) {
        Str *_t2254 = Str_lit("EqEq", 4ULL);
        (void)_t2254;
        ;
        return _t2254;
    }
    ;
    Bool _t2321; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2321 = *_hp; free(_hp); }
    (void)_t2321;
    if (_t2321) {
        Str *_t2255 = Str_lit("Neq", 3ULL);
        (void)_t2255;
        ;
        return _t2255;
    }
    ;
    Bool _t2322; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2322 = *_hp; free(_hp); }
    (void)_t2322;
    if (_t2322) {
        Str *_t2256 = Str_lit("Lt", 2ULL);
        (void)_t2256;
        ;
        return _t2256;
    }
    ;
    Bool _t2323; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2323 = *_hp; free(_hp); }
    (void)_t2323;
    if (_t2323) {
        Str *_t2257 = Str_lit("LtEq", 4ULL);
        (void)_t2257;
        ;
        return _t2257;
    }
    ;
    Bool _t2324; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2324 = *_hp; free(_hp); }
    (void)_t2324;
    if (_t2324) {
        Str *_t2258 = Str_lit("Gt", 2ULL);
        (void)_t2258;
        ;
        return _t2258;
    }
    ;
    Bool _t2325; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2325 = *_hp; free(_hp); }
    (void)_t2325;
    if (_t2325) {
        Str *_t2259 = Str_lit("GtEq", 4ULL);
        (void)_t2259;
        ;
        return _t2259;
    }
    ;
    Bool _t2326; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2326 = *_hp; free(_hp); }
    (void)_t2326;
    if (_t2326) {
        Str *_t2260 = Str_lit("ColonEq", 7ULL);
        (void)_t2260;
        ;
        return _t2260;
    }
    ;
    Bool _t2327; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2327 = *_hp; free(_hp); }
    (void)_t2327;
    if (_t2327) {
        Str *_t2261 = Str_lit("Ident", 5ULL);
        (void)_t2261;
        ;
        return _t2261;
    }
    ;
    Bool _t2328; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2328 = *_hp; free(_hp); }
    (void)_t2328;
    if (_t2328) {
        Str *_t2262 = Str_lit("StringTok", 9ULL);
        (void)_t2262;
        ;
        return _t2262;
    }
    ;
    Bool _t2329; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2329 = *_hp; free(_hp); }
    (void)_t2329;
    if (_t2329) {
        Str *_t2263 = Str_lit("Number", 6ULL);
        (void)_t2263;
        ;
        return _t2263;
    }
    ;
    Bool _t2330; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2330 = *_hp; free(_hp); }
    (void)_t2330;
    if (_t2330) {
        Str *_t2264 = Str_lit("Char", 4ULL);
        (void)_t2264;
        ;
        return _t2264;
    }
    ;
    Bool _t2331; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2331 = *_hp; free(_hp); }
    (void)_t2331;
    if (_t2331) {
        Str *_t2265 = Str_lit("KwMode", 6ULL);
        (void)_t2265;
        ;
        return _t2265;
    }
    ;
    Bool _t2332; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2332 = *_hp; free(_hp); }
    (void)_t2332;
    if (_t2332) {
        Str *_t2266 = Str_lit("KwMut", 5ULL);
        (void)_t2266;
        ;
        return _t2266;
    }
    ;
    Bool _t2333; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2333 = *_hp; free(_hp); }
    (void)_t2333;
    if (_t2333) {
        Str *_t2267 = Str_lit("KwOwn", 5ULL);
        (void)_t2267;
        ;
        return _t2267;
    }
    ;
    Bool _t2334; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2334 = *_hp; free(_hp); }
    (void)_t2334;
    if (_t2334) {
        Str *_t2268 = Str_lit("KwRef", 5ULL);
        (void)_t2268;
        ;
        return _t2268;
    }
    ;
    Bool _t2335; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2335 = *_hp; free(_hp); }
    (void)_t2335;
    if (_t2335) {
        Str *_t2269 = Str_lit("KwShallow", 9ULL);
        (void)_t2269;
        ;
        return _t2269;
    }
    ;
    Bool _t2336; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2336 = *_hp; free(_hp); }
    (void)_t2336;
    if (_t2336) {
        Str *_t2270 = Str_lit("KwStruct", 8ULL);
        (void)_t2270;
        ;
        return _t2270;
    }
    ;
    Bool _t2337; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2337 = *_hp; free(_hp); }
    (void)_t2337;
    if (_t2337) {
        Str *_t2271 = Str_lit("KwExtStruct", 11ULL);
        (void)_t2271;
        ;
        return _t2271;
    }
    ;
    Bool _t2338; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2338 = *_hp; free(_hp); }
    (void)_t2338;
    if (_t2338) {
        Str *_t2272 = Str_lit("KwEnum", 6ULL);
        (void)_t2272;
        ;
        return _t2272;
    }
    ;
    Bool _t2339; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2339 = *_hp; free(_hp); }
    (void)_t2339;
    if (_t2339) {
        Str *_t2273 = Str_lit("KwNamespace", 11ULL);
        (void)_t2273;
        ;
        return _t2273;
    }
    ;
    Bool _t2340; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2340 = *_hp; free(_hp); }
    (void)_t2340;
    if (_t2340) {
        Str *_t2274 = Str_lit("KwFunc", 6ULL);
        (void)_t2274;
        ;
        return _t2274;
    }
    ;
    Bool _t2341; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2341 = *_hp; free(_hp); }
    (void)_t2341;
    if (_t2341) {
        Str *_t2275 = Str_lit("KwProc", 6ULL);
        (void)_t2275;
        ;
        return _t2275;
    }
    ;
    Bool _t2342; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2342 = *_hp; free(_hp); }
    (void)_t2342;
    if (_t2342) {
        Str *_t2276 = Str_lit("KwTest", 6ULL);
        (void)_t2276;
        ;
        return _t2276;
    }
    ;
    Bool _t2343; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2343 = *_hp; free(_hp); }
    (void)_t2343;
    if (_t2343) {
        Str *_t2277 = Str_lit("KwMacro", 7ULL);
        (void)_t2277;
        ;
        return _t2277;
    }
    ;
    Bool _t2344; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2344 = *_hp; free(_hp); }
    (void)_t2344;
    if (_t2344) {
        Str *_t2278 = Str_lit("KwExtFunc", 9ULL);
        (void)_t2278;
        ;
        return _t2278;
    }
    ;
    Bool _t2345; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2345 = *_hp; free(_hp); }
    (void)_t2345;
    if (_t2345) {
        Str *_t2279 = Str_lit("KwExtProc", 9ULL);
        (void)_t2279;
        ;
        return _t2279;
    }
    ;
    Bool _t2346; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2346 = *_hp; free(_hp); }
    (void)_t2346;
    if (_t2346) {
        Str *_t2280 = Str_lit("KwReturns", 9ULL);
        (void)_t2280;
        ;
        return _t2280;
    }
    ;
    Bool _t2347; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2347 = *_hp; free(_hp); }
    (void)_t2347;
    if (_t2347) {
        Str *_t2281 = Str_lit("KwThrows", 8ULL);
        (void)_t2281;
        ;
        return _t2281;
    }
    ;
    Bool _t2348; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2348 = *_hp; free(_hp); }
    (void)_t2348;
    if (_t2348) {
        Str *_t2282 = Str_lit("KwIf", 4ULL);
        (void)_t2282;
        ;
        return _t2282;
    }
    ;
    Bool _t2349; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2349 = *_hp; free(_hp); }
    (void)_t2349;
    if (_t2349) {
        Str *_t2283 = Str_lit("KwElse", 6ULL);
        (void)_t2283;
        ;
        return _t2283;
    }
    ;
    Bool _t2350; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2350 = *_hp; free(_hp); }
    (void)_t2350;
    if (_t2350) {
        Str *_t2284 = Str_lit("KwWhile", 7ULL);
        (void)_t2284;
        ;
        return _t2284;
    }
    ;
    Bool _t2351; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2351 = *_hp; free(_hp); }
    (void)_t2351;
    if (_t2351) {
        Str *_t2285 = Str_lit("KwFor", 5ULL);
        (void)_t2285;
        ;
        return _t2285;
    }
    ;
    Bool _t2352; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2352 = *_hp; free(_hp); }
    (void)_t2352;
    if (_t2352) {
        Str *_t2286 = Str_lit("KwIn", 4ULL);
        (void)_t2286;
        ;
        return _t2286;
    }
    ;
    Bool _t2353; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2353 = *_hp; free(_hp); }
    (void)_t2353;
    if (_t2353) {
        Str *_t2287 = Str_lit("KwSwitch", 8ULL);
        (void)_t2287;
        ;
        return _t2287;
    }
    ;
    Bool _t2354; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2354 = *_hp; free(_hp); }
    (void)_t2354;
    if (_t2354) {
        Str *_t2288 = Str_lit("KwMatch", 7ULL);
        (void)_t2288;
        ;
        return _t2288;
    }
    ;
    Bool _t2355; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2355 = *_hp; free(_hp); }
    (void)_t2355;
    if (_t2355) {
        Str *_t2289 = Str_lit("KwCase", 6ULL);
        (void)_t2289;
        ;
        return _t2289;
    }
    ;
    Bool _t2356; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2356 = *_hp; free(_hp); }
    (void)_t2356;
    if (_t2356) {
        Str *_t2290 = Str_lit("KwDefault", 9ULL);
        (void)_t2290;
        ;
        return _t2290;
    }
    ;
    Bool _t2357; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2357 = *_hp; free(_hp); }
    (void)_t2357;
    if (_t2357) {
        Str *_t2291 = Str_lit("KwReturn", 8ULL);
        (void)_t2291;
        ;
        return _t2291;
    }
    ;
    Bool _t2358; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2358 = *_hp; free(_hp); }
    (void)_t2358;
    if (_t2358) {
        Str *_t2292 = Str_lit("KwThrow", 7ULL);
        (void)_t2292;
        ;
        return _t2292;
    }
    ;
    Bool _t2359; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2359 = *_hp; free(_hp); }
    (void)_t2359;
    if (_t2359) {
        Str *_t2293 = Str_lit("KwCatch", 7ULL);
        (void)_t2293;
        ;
        return _t2293;
    }
    ;
    Bool _t2360; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2360 = *_hp; free(_hp); }
    (void)_t2360;
    if (_t2360) {
        Str *_t2294 = Str_lit("KwBreak", 7ULL);
        (void)_t2294;
        ;
        return _t2294;
    }
    ;
    Bool _t2361; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2361 = *_hp; free(_hp); }
    (void)_t2361;
    if (_t2361) {
        Str *_t2295 = Str_lit("KwContinue", 10ULL);
        (void)_t2295;
        ;
        return _t2295;
    }
    ;
    Bool _t2362; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2362 = *_hp; free(_hp); }
    (void)_t2362;
    if (_t2362) {
        Str *_t2296 = Str_lit("KwDefer", 7ULL);
        (void)_t2296;
        ;
        return _t2296;
    }
    ;
    Bool _t2363; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2363 = *_hp; free(_hp); }
    (void)_t2363;
    if (_t2363) {
        Str *_t2297 = Str_lit("KwTrue", 6ULL);
        (void)_t2297;
        ;
        return _t2297;
    }
    ;
    Bool _t2364; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2364 = *_hp; free(_hp); }
    (void)_t2364;
    if (_t2364) {
        Str *_t2298 = Str_lit("KwFalse", 7ULL);
        (void)_t2298;
        ;
        return _t2298;
    }
    ;
    Bool _t2365; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2365 = *_hp; free(_hp); }
    (void)_t2365;
    if (_t2365) {
        Str *_t2299 = Str_lit("KwNull", 6ULL);
        (void)_t2299;
        ;
        return _t2299;
    }
    ;
    Bool _t2366; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t2366 = *_hp; free(_hp); }
    (void)_t2366;
    if (_t2366) {
        Str *_t2300 = Str_lit("Error", 5ULL);
        (void)_t2300;
        ;
        return _t2300;
    }
    ;
    Str *_t2367 = Str_lit("unknown", 7ULL);
    (void)_t2367;
    return _t2367;
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
        _t4135 = malloc(sizeof(I64));
    *_t4135 = 0;
    (void)_t4135;
    _t4136 = malloc(sizeof(I64));
    *_t4136 = 1;
    (void)_t4136;
    _t4137 = malloc(sizeof(I64)); *_t4137 = I64_sub(DEREF(_t4135), DEREF(_t4136));
    (void)_t4137;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4137));
    (void)CAP_LIT;
    _t4138 = malloc(sizeof(I64));
    *_t4138 = 0;
    (void)_t4138;
    _t4139 = malloc(sizeof(I64));
    *_t4139 = 2;
    (void)_t4139;
    _t4140 = malloc(sizeof(I64)); *_t4140 = I64_sub(DEREF(_t4138), DEREF(_t4139));
    (void)_t4140;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4140));
    (void)CAP_VIEW;
    _t4141 = Str_lit("Str", 3ULL);
    (void)_t4141;
    _t4142 = Str_size();
    (void)_t4142;
    _t4143 = Str_lit("Mode", 4ULL);
    (void)_t4143;
    _t4144 = Mode_size();
    (void)_t4144;
    core_modes = Map_new(_t4141, _t4142, _t4143, _t4144);
    (void)core_modes;
    _t4145 = malloc(sizeof(Bool));
    *_t4145 = 0;
    (void)_t4145;
    _t4146 = malloc(sizeof(Bool));
    *_t4146 = 0;
    (void)_t4146;
    _t4147 = malloc(sizeof(Bool));
    *_t4147 = 0;
    (void)_t4147;
    _t4148 = malloc(sizeof(Bool));
    *_t4148 = 0;
    (void)_t4148;
    _t4149 = Str_lit("script", 6ULL);
    (void)_t4149;
    _t4150 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4150->name = *_ca; free(_ca); }
    _t4150->needs_main = DEREF(_t4145);
    _t4150->decls_only = DEREF(_t4146);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4150->auto_import = *_ca; free(_ca); }
    _t4150->is_pure = DEREF(_t4147);
    _t4150->debug_prints = DEREF(_t4148);
    (void)_t4150;
    Map_set(core_modes, _t4149, _t4150);
    _t4151 = malloc(sizeof(Bool));
    *_t4151 = 1;
    (void)_t4151;
    _t4152 = malloc(sizeof(Bool));
    *_t4152 = 1;
    (void)_t4152;
    _t4153 = malloc(sizeof(Bool));
    *_t4153 = 0;
    (void)_t4153;
    _t4154 = malloc(sizeof(Bool));
    *_t4154 = 0;
    (void)_t4154;
    _t4155 = Str_lit("cli", 3ULL);
    (void)_t4155;
    _t4156 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4156->name = *_ca; free(_ca); }
    _t4156->needs_main = DEREF(_t4151);
    _t4156->decls_only = DEREF(_t4152);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4156->auto_import = *_ca; free(_ca); }
    _t4156->is_pure = DEREF(_t4153);
    _t4156->debug_prints = DEREF(_t4154);
    (void)_t4156;
    Map_set(core_modes, _t4155, _t4156);
    _t4157 = malloc(sizeof(Bool));
    *_t4157 = 1;
    (void)_t4157;
    _t4158 = malloc(sizeof(Bool));
    *_t4158 = 1;
    (void)_t4158;
    _t4159 = malloc(sizeof(Bool));
    *_t4159 = 0;
    (void)_t4159;
    _t4160 = malloc(sizeof(Bool));
    *_t4160 = 0;
    (void)_t4160;
    _t4161 = Str_lit("gui", 3ULL);
    (void)_t4161;
    _t4162 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4162->name = *_ca; free(_ca); }
    _t4162->needs_main = DEREF(_t4157);
    _t4162->decls_only = DEREF(_t4158);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4162->auto_import = *_ca; free(_ca); }
    _t4162->is_pure = DEREF(_t4159);
    _t4162->debug_prints = DEREF(_t4160);
    (void)_t4162;
    Map_set(core_modes, _t4161, _t4162);
    _t4163 = malloc(sizeof(Bool));
    *_t4163 = 0;
    (void)_t4163;
    _t4164 = malloc(sizeof(Bool));
    *_t4164 = 1;
    (void)_t4164;
    _t4165 = malloc(sizeof(Bool));
    *_t4165 = 0;
    (void)_t4165;
    _t4166 = malloc(sizeof(Bool));
    *_t4166 = 0;
    (void)_t4166;
    _t4167 = Str_lit("test", 4ULL);
    (void)_t4167;
    _t4168 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4168->name = *_ca; free(_ca); }
    _t4168->needs_main = DEREF(_t4163);
    _t4168->decls_only = DEREF(_t4164);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4168->auto_import = *_ca; free(_ca); }
    _t4168->is_pure = DEREF(_t4165);
    _t4168->debug_prints = DEREF(_t4166);
    (void)_t4168;
    Map_set(core_modes, _t4167, _t4168);
    _t4169 = malloc(sizeof(Bool));
    *_t4169 = 0;
    (void)_t4169;
    _t4170 = malloc(sizeof(Bool));
    *_t4170 = 1;
    (void)_t4170;
    _t4171 = malloc(sizeof(Bool));
    *_t4171 = 1;
    (void)_t4171;
    _t4172 = malloc(sizeof(Bool));
    *_t4172 = 0;
    (void)_t4172;
    _t4173 = Str_lit("pure", 4ULL);
    (void)_t4173;
    _t4174 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4174->name = *_ca; free(_ca); }
    _t4174->needs_main = DEREF(_t4169);
    _t4174->decls_only = DEREF(_t4170);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4174->auto_import = *_ca; free(_ca); }
    _t4174->is_pure = DEREF(_t4171);
    _t4174->debug_prints = DEREF(_t4172);
    (void)_t4174;
    Map_set(core_modes, _t4173, _t4174);
    _t4175 = malloc(sizeof(Bool));
    *_t4175 = 0;
    (void)_t4175;
    _t4176 = malloc(sizeof(Bool));
    *_t4176 = 1;
    (void)_t4176;
    _t4177 = malloc(sizeof(Bool));
    *_t4177 = 1;
    (void)_t4177;
    _t4178 = malloc(sizeof(Bool));
    *_t4178 = 1;
    (void)_t4178;
    _t4179 = Str_lit("pura", 4ULL);
    (void)_t4179;
    _t4180 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4180->name = *_ca; free(_ca); }
    _t4180->needs_main = DEREF(_t4175);
    _t4180->decls_only = DEREF(_t4176);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4180->auto_import = *_ca; free(_ca); }
    _t4180->is_pure = DEREF(_t4177);
    _t4180->debug_prints = DEREF(_t4178);
    (void)_t4180;
    Map_set(core_modes, _t4179, _t4180);
    _t4181 = malloc(sizeof(Bool));
    *_t4181 = 0;
    (void)_t4181;
    _t4182 = malloc(sizeof(Bool));
    *_t4182 = 1;
    (void)_t4182;
    _t4183 = malloc(sizeof(Bool));
    *_t4183 = 0;
    (void)_t4183;
    _t4184 = malloc(sizeof(Bool));
    *_t4184 = 0;
    (void)_t4184;
    _t4185 = Str_lit("lib", 3ULL);
    (void)_t4185;
    _t4186 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4186->name = *_ca; free(_ca); }
    _t4186->needs_main = DEREF(_t4181);
    _t4186->decls_only = DEREF(_t4182);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4186->auto_import = *_ca; free(_ca); }
    _t4186->is_pure = DEREF(_t4183);
    _t4186->debug_prints = DEREF(_t4184);
    (void)_t4186;
    Map_set(core_modes, _t4185, _t4186);
    _t4187 = malloc(sizeof(Bool));
    *_t4187 = 0;
    (void)_t4187;
    _t4188 = malloc(sizeof(Bool));
    *_t4188 = 1;
    (void)_t4188;
    _t4189 = malloc(sizeof(Bool));
    *_t4189 = 0;
    (void)_t4189;
    _t4190 = malloc(sizeof(Bool));
    *_t4190 = 1;
    (void)_t4190;
    _t4191 = Str_lit("liba", 4ULL);
    (void)_t4191;
    _t4192 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4192->name = *_ca; free(_ca); }
    _t4192->needs_main = DEREF(_t4187);
    _t4192->decls_only = DEREF(_t4188);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4192->auto_import = *_ca; free(_ca); }
    _t4192->is_pure = DEREF(_t4189);
    _t4192->debug_prints = DEREF(_t4190);
    (void)_t4192;
    Map_set(core_modes, _t4191, _t4192);
}

