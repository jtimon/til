#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "til_core.h"
#include "til_array.h"
#include "til_map.h"
#include "til_set.h"
#include "til_str.h"
#include "til_vec.h"
#include "til_tuple.h"
#include "til_ast.h"
#include "til_lexer.h"
#include "til_parser.h"
#include "til_initer.h"
#include "til_typer.h"
#include "til_dispatch.h"
#include "til_modes.h"
#include "til_til.h"

#include "ext.h"

Vec * tokenize(Str *, Str *);
Expr * til_parse(Vec *, Str *);
Str * til_parse_mode(void);
Expr * expr_null(void);
I32 expr_get_tag(Expr *);
Str * expr_get_str_val(Expr *);
Expr * expr_get_child(Expr *, U32);
U32 expr_nchildren(Expr *);
void expr_swap_children(Expr *, Vec *);
Vec * expr_vec_new(void);
void expr_vec_push(Vec *, Expr *);
Expr * expr_vec_get(Vec *, U32);
U32 expr_vec_count(Vec *);
Mode * mode_resolve(Str *);
Bool * mode_is_lib(Mode *);
Bool * mode_is_lib_output(Mode *);
TypeScope * tscope_new(TypeScope *);
void tscope_free(TypeScope *);
I32 init_declarations(Expr *, TypeScope *);
I32 type_check(Expr *, TypeScope *, Mode *);
void precomp(Expr *);
void scavenge(Expr *, Mode *, Bool);
I32 til_interpret_v(Expr *, Mode *, Bool, Str *, Str *, Str *, Str *, Vec *);
I32 build(Expr *, Mode *, Bool, Str *, Str *);
I32 build_header(Expr *, Str *);
I32 build_til_binding(Expr *, Str *, Str *);
I32 til_compile_c(Str *, Str *, Str *, Str *, Str *);
I32 til_compile_lib(Str *, Str *, Str *, Str *, Str *);
void ast_print(Expr *, U32);
Str * til_bin_dir(void);
Str * til_realpath(Str *);
Str * til_str_left(Str *, U64);
I32 til_system(Str *);

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
void * CloneFn(void * );
void DeleteFn(void * , Bool * );
I64 * CmpFn(void * , void * );
void * default_clone(void * v);
void default_delete(void * v, Bool * cf);
I64 * default_cmp(void * a, void * b);
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
LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U64 * LocalInfo_size(void);
ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U64 * ExtStr_size(void);
Bool * Mode_eq(Mode * a, Mode * b);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
Mode * mode_resolve(Str * name);
Bool * mode_is_lib(Mode * m);
Bool * mode_is_lib_output(Mode * m);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(Expr * e);
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

static I64 *_t4762;
static I64 *_t4763;
static I64 *_t4764;
static U64 *CAP_LIT;
static I64 *_t4765;
static I64 *_t4766;
static I64 *_t4767;
static U64 *CAP_VIEW;
static Str *_t4768;
static U64 *_t4769;
static Str *_t4770;
static U64 *_t4771;
static Map *core_modes;
static Bool *_t4772;
static Bool *_t4773;
static Bool *_t4774;
static Bool *_t4775;
static Str *_t4776;
static Mode *_t4777;
static Bool *_t4778;
static Bool *_t4779;
static Bool *_t4780;
static Bool *_t4781;
static Str *_t4782;
static Mode *_t4783;
static Bool *_t4784;
static Bool *_t4785;
static Bool *_t4786;
static Bool *_t4787;
static Str *_t4788;
static Mode *_t4789;
static Bool *_t4790;
static Bool *_t4791;
static Bool *_t4792;
static Bool *_t4793;
static Str *_t4794;
static Mode *_t4795;
static Bool *_t4796;
static Bool *_t4797;
static Bool *_t4798;
static Bool *_t4799;
static Str *_t4800;
static Mode *_t4801;
static Bool *_t4802;
static Bool *_t4803;
static Bool *_t4804;
static Bool *_t4805;
static Str *_t4806;
static Mode *_t4807;
static Bool *_t4808;
static Bool *_t4809;
static Bool *_t4810;
static Bool *_t4811;
static Str *_t4812;
static Mode *_t4813;
static Bool *_t4814;
static Bool *_t4815;
static Bool *_t4816;
static Bool *_t4817;
static Str *_t4818;
static Mode *_t4819;
static I32 *NODE_BODY;
static I32 *NODE_LITERAL_STR;
static I32 *NODE_LITERAL_NUM;
static I32 *NODE_LITERAL_BOOL;
static I32 *NODE_LITERAL_NULL;
static I32 *NODE_IDENT;
static I32 *NODE_DECL;
static I32 *NODE_ASSIGN;
static I32 *NODE_FCALL;
static I32 *NODE_FUNC_DEF;
static I32 *NODE_STRUCT_DEF;
static I32 *NODE_ENUM_DEF;
static I32 *NODE_FIELD_ACCESS;
static I32 *NODE_FIELD_ASSIGN;
static I32 *NODE_RETURN;
static I32 *NODE_IF;
static I32 *NODE_WHILE;
static I32 *NODE_FOR_IN;
static I32 *NODE_NAMED_ARG;
static I32 *NODE_BREAK;
static I32 *NODE_CONTINUE;
static I32 *NODE_MAP_LIT;
static I32 *NODE_SET_LIT;
static I32 *NODE_SWITCH;
static I32 *NODE_CASE;

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
    Bool _t391; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t391 = *_hp; free(_hp); }
    (void)_t391;
    if (_t391) {
        Str *_t385 = Str_lit("Str", 3ULL);
        (void)_t385;
        U64 _t386; { U64 *_hp = (U64 *)Str_size(); _t386 = *_hp; free(_hp); }
        (void)_t386;
        U64 _t387 = 1;
        (void)_t387;
        Array *_va7 = Array_new(_t385, &(U64){_t386}, &(U64){_t387});
        (void)_va7;
        Str_delete(_t385, &(Bool){1});
        ;
        ;
        U64 _t388 = 0;
        (void)_t388;
        Str *_t389 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t389;
        Array_set(_va7, &(U64){_t388}, _t389);
        ;
        Str *_t390 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:11:41", 62ULL);
        (void)_t390;
        panic(_t390, _va7);
        Str_delete(_t390, &(Bool){1});
    }
    ;
    void *_t392 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t392;
    U64 _t393 = U64_clone(cap);
    (void)_t393;
    U64 _t394 = U64_clone(elem_size);
    (void)_t394;
    Array *_t395 = malloc(sizeof(Array));
    _t395->data = _t392;
    _t395->cap = _t393;
    _t395->elem_size = _t394;
    { Str *_ca = Str_clone(elem_type); _t395->elem_type = *_ca; free(_ca); }
    (void)_t395;
    ;
    ;
    return _t395;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t410; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t410 = *_hp; free(_hp); }
    (void)_t410;
    if (_t410) {
        Str *_t396 = Str_lit("Str", 3ULL);
        (void)_t396;
        U64 _t397; { U64 *_hp = (U64 *)Str_size(); _t397 = *_hp; free(_hp); }
        (void)_t397;
        U64 _t398 = 5;
        (void)_t398;
        Array *_va8 = Array_new(_t396, &(U64){_t397}, &(U64){_t398});
        (void)_va8;
        Str_delete(_t396, &(Bool){1});
        ;
        ;
        U64 _t399 = 0;
        (void)_t399;
        Str *_t400 = Str_lit("Array.get: index ", 17ULL);
        (void)_t400;
        Array_set(_va8, &(U64){_t399}, _t400);
        ;
        U64 _t401 = 1;
        (void)_t401;
        Str *_t402 = U64_to_str(DEREF(i));
        (void)_t402;
        Array_set(_va8, &(U64){_t401}, _t402);
        ;
        U64 _t403 = 2;
        (void)_t403;
        Str *_t404 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t404;
        Array_set(_va8, &(U64){_t403}, _t404);
        ;
        U64 _t405 = 3;
        (void)_t405;
        Str *_t406 = U64_to_str(self->cap);
        (void)_t406;
        Array_set(_va8, &(U64){_t405}, _t406);
        ;
        U64 _t407 = 4;
        (void)_t407;
        Str *_t408 = Str_lit(")", 1ULL);
        (void)_t408;
        Array_set(_va8, &(U64){_t407}, _t408);
        ;
        Str *_t409 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:20:19", 62ULL);
        (void)_t409;
        panic(_t409, _va8);
        Str_delete(_t409, &(Bool){1});
    }
    ;
    U64 *_t411 = malloc(sizeof(U64)); *_t411 = U64_mul(DEREF(i), self->elem_size);
    (void)_t411;
    void *_t412 = ptr_add(self->data, DEREF(_t411));
    (void)_t412;
    U64_delete(_t411, &(Bool){1});
    return _t412;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t427; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t427 = *_hp; free(_hp); }
    (void)_t427;
    if (_t427) {
        Str *_t413 = Str_lit("Str", 3ULL);
        (void)_t413;
        U64 _t414; { U64 *_hp = (U64 *)Str_size(); _t414 = *_hp; free(_hp); }
        (void)_t414;
        U64 _t415 = 5;
        (void)_t415;
        Array *_va9 = Array_new(_t413, &(U64){_t414}, &(U64){_t415});
        (void)_va9;
        Str_delete(_t413, &(Bool){1});
        ;
        ;
        U64 _t416 = 0;
        (void)_t416;
        Str *_t417 = Str_lit("Array.set: index ", 17ULL);
        (void)_t417;
        Array_set(_va9, &(U64){_t416}, _t417);
        ;
        U64 _t418 = 1;
        (void)_t418;
        Str *_t419 = U64_to_str(DEREF(i));
        (void)_t419;
        Array_set(_va9, &(U64){_t418}, _t419);
        ;
        U64 _t420 = 2;
        (void)_t420;
        Str *_t421 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t421;
        Array_set(_va9, &(U64){_t420}, _t421);
        ;
        U64 _t422 = 3;
        (void)_t422;
        Str *_t423 = U64_to_str(self->cap);
        (void)_t423;
        Array_set(_va9, &(U64){_t422}, _t423);
        ;
        U64 _t424 = 4;
        (void)_t424;
        Str *_t425 = Str_lit(")", 1ULL);
        (void)_t425;
        Array_set(_va9, &(U64){_t424}, _t425);
        ;
        Str *_t426 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:28:19", 62ULL);
        (void)_t426;
        panic(_t426, _va9);
        Str_delete(_t426, &(Bool){1});
    }
    ;
    U64 *_t428 = malloc(sizeof(U64)); *_t428 = U64_mul(DEREF(i), self->elem_size);
    (void)_t428;
    void *_t429 = ptr_add(self->data, DEREF(_t428));
    (void)_t429;
    Bool _t430 = 0;
    (void)_t430;
    dyn_call_delete(&self->elem_type, _t429, &(Bool){_t430});
    U64_delete(_t428, &(Bool){1});
    ;
    U64 *_t431 = malloc(sizeof(U64)); *_t431 = U64_mul(DEREF(i), self->elem_size);
    (void)_t431;
    void *_t432 = ptr_add(self->data, DEREF(_t431));
    (void)_t432;
    memcpy(_t432, val, self->elem_size);
    U64_delete(_t431, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    {
        U64 _t441 = 0;
        (void)_t441;
        Range *_fc433 = Range_new(_t441, self->cap);
        (void)_fc433;
        ;
        U64 _fi433 = 0;
        (void)_fi433;
        while (1) {
            U64 _t435; { U64 *_hp = (U64 *)Range_len(_fc433); _t435 = *_hp; free(_hp); }
            (void)_t435;
            Bool _wcond434; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi433}, &(U64){_t435}); _wcond434 = *_hp; free(_hp); }
            (void)_wcond434;
            ;
            if (_wcond434) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc433, _fi433); i = *_hp; free(_hp); }
            (void)i;
            U64 _t436 = 1;
            (void)_t436;
            U64 _t437 = U64_add(_fi433, _t436);
            (void)_t437;
            ;
            _fi433 = _t437;
            ;
            U64 *_t438 = malloc(sizeof(U64)); *_t438 = U64_mul(i, self->elem_size);
            (void)_t438;
            ;
            void *_t439 = ptr_add(self->data, DEREF(_t438));
            (void)_t439;
            Bool _t440 = 0;
            (void)_t440;
            dyn_call_delete(&self->elem_type, _t439, &(Bool){_t440});
            U64_delete(_t438, &(Bool){1});
            ;
        }
        Range_delete(_fc433, &(Bool){1});
        ;
    }
    free(self->data);
    Bool _t442 = 0;
    (void)_t442;
    Str_delete(&self->elem_type, &(Bool){_t442});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t453 = U64_mul(self->cap, self->elem_size);
    (void)_t453;
    U8 *new_data = malloc(_t453);
    (void)new_data;
    ;
    {
        U64 _t452 = 0;
        (void)_t452;
        Range *_fc443 = Range_new(_t452, self->cap);
        (void)_fc443;
        ;
        U64 _fi443 = 0;
        (void)_fi443;
        while (1) {
            U64 _t445; { U64 *_hp = (U64 *)Range_len(_fc443); _t445 = *_hp; free(_hp); }
            (void)_t445;
            Bool _wcond444; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi443}, &(U64){_t445}); _wcond444 = *_hp; free(_hp); }
            (void)_wcond444;
            ;
            if (_wcond444) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc443, _fi443); i = *_hp; free(_hp); }
            (void)i;
            U64 _t446 = 1;
            (void)_t446;
            U64 _t447 = U64_add(_fi443, _t446);
            (void)_t447;
            ;
            _fi443 = _t447;
            ;
            U64 *_t448 = malloc(sizeof(U64)); *_t448 = U64_mul(i, self->elem_size);
            (void)_t448;
            void *_t449 = ptr_add(self->data, DEREF(_t448));
            (void)_t449;
            void *cloned = dyn_call_clone(&self->elem_type, _t449);
            (void)cloned;
            U64_delete(_t448, &(Bool){1});
            U64 *_t450 = malloc(sizeof(U64)); *_t450 = U64_mul(i, self->elem_size);
            (void)_t450;
            ;
            void *_t451 = ptr_add(new_data, DEREF(_t450));
            (void)_t451;
            memcpy(_t451, cloned, self->elem_size);
            U64_delete(_t450, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc443, &(Bool){1});
        ;
    }
    Array *_t454 = malloc(sizeof(Array));
    _t454->data = new_data;
    _t454->cap = self->cap;
    _t454->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t454->elem_type = *_ca; free(_ca); }
    (void)_t454;
    return _t454;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t472; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t472 = *_hp; free(_hp); }
    (void)_t472;
    if (_t472) {
        Str *_t456 = Str_lit("Str", 3ULL);
        (void)_t456;
        U64 _t457; { U64 *_hp = (U64 *)Str_size(); _t457 = *_hp; free(_hp); }
        (void)_t457;
        U64 _t458 = 1;
        (void)_t458;
        Array *_va10 = Array_new(_t456, &(U64){_t457}, &(U64){_t458});
        (void)_va10;
        Str_delete(_t456, &(Bool){1});
        ;
        ;
        U64 _t459 = 0;
        (void)_t459;
        Str *_t460 = Str_lit("Map.new: key_type required", 26ULL);
        (void)_t460;
        Array_set(_va10, &(U64){_t459}, _t460);
        ;
        Str *_t461 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:15:40", 60ULL);
        (void)_t461;
        panic(_t461, _va10);
        Str_delete(_t461, &(Bool){1});
    }
    ;
    Bool _t473 = dyn_has_cmp(key_type);
    (void)_t473;
    Bool _t474 = Bool_not(_t473);
    (void)_t474;
    ;
    if (_t474) {
        Str *_t462 = Str_lit("Str", 3ULL);
        (void)_t462;
        U64 _t463; { U64 *_hp = (U64 *)Str_size(); _t463 = *_hp; free(_hp); }
        (void)_t463;
        U64 _t464 = 3;
        (void)_t464;
        Array *_va11 = Array_new(_t462, &(U64){_t463}, &(U64){_t464});
        (void)_va11;
        Str_delete(_t462, &(Bool){1});
        ;
        ;
        U64 _t465 = 0;
        (void)_t465;
        Str *_t466 = Str_lit("Map.new: type ", 14ULL);
        (void)_t466;
        Array_set(_va11, &(U64){_t465}, _t466);
        ;
        U64 _t467 = 1;
        (void)_t467;
        Str *_t468 = Str_clone(key_type);
        (void)_t468;
        Array_set(_va11, &(U64){_t467}, _t468);
        ;
        U64 _t469 = 2;
        (void)_t469;
        Str *_t470 = Str_lit(" must implement cmp", 19ULL);
        (void)_t470;
        Array_set(_va11, &(U64){_t469}, _t470);
        ;
        Str *_t471 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:19", 60ULL);
        (void)_t471;
        panic(_t471, _va11);
        Str_delete(_t471, &(Bool){1});
    }
    ;
    void *_t475 = malloc(DEREF(key_size));
    (void)_t475;
    void *_t476 = malloc(DEREF(val_size));
    (void)_t476;
    U64 _t477 = 0;
    (void)_t477;
    I64 _t478 = 1;
    (void)_t478;
    U64 _t479 = U64_clone(key_size);
    (void)_t479;
    U64 _t480 = U64_clone(val_size);
    (void)_t480;
    Map *_t481 = malloc(sizeof(Map));
    _t481->key_data = _t475;
    _t481->val_data = _t476;
    _t481->count = _t477;
    _t481->cap = _t478;
    _t481->key_size = _t479;
    { Str *_ca = Str_clone(key_type); _t481->key_type = *_ca; free(_ca); }
    _t481->val_size = _t480;
    { Str *_ca = Str_clone(val_type); _t481->val_type = *_ca; free(_ca); }
    (void)_t481;
    ;
    ;
    ;
    ;
    return _t481;
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
        Bool _wcond482; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond482 = *_hp; free(_hp); }
        (void)_wcond482;
        if (_wcond482) {
        } else {
            ;
            break;
        }
        ;
        U64 _t489 = U64_sub(hi, lo);
        (void)_t489;
        U64 _t490 = 2;
        (void)_t490;
        U64 _t491 = U64_div(_t489, _t490);
        (void)_t491;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t491);
        (void)mid;
        ;
        U64 *_t492 = malloc(sizeof(U64)); *_t492 = U64_mul(DEREF(mid), self->key_size);
        (void)_t492;
        void *_t493 = ptr_add(self->key_data, DEREF(_t492));
        (void)_t493;
        I64 *c = dyn_call_cmp(&self->key_type, _t493, key);
        (void)c;
        U64_delete(_t492, &(Bool){1});
        I64 _t494 = 0;
        (void)_t494;
        Bool _t495; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t494}); _t495 = *_hp; free(_hp); }
        (void)_t495;
        ;
        if (_t495) {
            U64 _t483 = 1;
            (void)_t483;
            U64 _t484 = U64_add(DEREF(mid), _t483);
            (void)_t484;
            ;
            lo = _t484;
            ;
        } else {
            I64 _t487 = 0;
            (void)_t487;
            Bool _t488; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t487}); _t488 = *_hp; free(_hp); }
            (void)_t488;
            ;
            if (_t488) {
                U64 _t485 = U64_clone(mid);
                (void)_t485;
                hi = _t485;
                ;
            } else {
                Bool _t486 = 1;
                (void)_t486;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t486; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t496 = 0;
    (void)_t496;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t496; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond497; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond497 = *_hp; free(_hp); }
        (void)_wcond497;
        if (_wcond497) {
        } else {
            ;
            break;
        }
        ;
        U64 _t505 = U64_sub(hi, lo);
        (void)_t505;
        U64 _t506 = 2;
        (void)_t506;
        U64 _t507 = U64_div(_t505, _t506);
        (void)_t507;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t507);
        (void)mid;
        ;
        U64 *_t508 = malloc(sizeof(U64)); *_t508 = U64_mul(DEREF(mid), self->key_size);
        (void)_t508;
        void *_t509 = ptr_add(self->key_data, DEREF(_t508));
        (void)_t509;
        I64 *c = dyn_call_cmp(&self->key_type, _t509, key);
        (void)c;
        U64_delete(_t508, &(Bool){1});
        I64 _t510 = 0;
        (void)_t510;
        Bool _t511; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t510}); _t511 = *_hp; free(_hp); }
        (void)_t511;
        ;
        if (_t511) {
            U64 _t498 = 1;
            (void)_t498;
            U64 _t499 = U64_add(DEREF(mid), _t498);
            (void)_t499;
            ;
            lo = _t499;
            ;
        } else {
            I64 _t503 = 0;
            (void)_t503;
            Bool _t504; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t503}); _t504 = *_hp; free(_hp); }
            (void)_t504;
            ;
            if (_t504) {
                U64 _t500 = U64_clone(mid);
                (void)_t500;
                hi = _t500;
                ;
            } else {
                U64 *_t501 = malloc(sizeof(U64)); *_t501 = U64_mul(DEREF(mid), self->val_size);
                (void)_t501;
                void *_t502 = ptr_add(self->val_data, DEREF(_t501));
                (void)_t502;
                U64_delete(_t501, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t502;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t512 = Str_lit("Str", 3ULL);
    (void)_t512;
    U64 _t513; { U64 *_hp = (U64 *)Str_size(); _t513 = *_hp; free(_hp); }
    (void)_t513;
    U64 _t514 = 1;
    (void)_t514;
    Array *_va12 = Array_new(_t512, &(U64){_t513}, &(U64){_t514});
    (void)_va12;
    Str_delete(_t512, &(Bool){1});
    ;
    ;
    U64 _t515 = 0;
    (void)_t515;
    Str *_t516 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t516;
    Array_set(_va12, &(U64){_t515}, _t516);
    ;
    Str *_t517 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:55:15", 60ULL);
    (void)_t517;
    panic(_t517, _va12);
    Str_delete(_t517, &(Bool){1});
    U64 *_t518 = malloc(sizeof(U64));
    *_t518 = 0;
    (void)_t518;
    void *_t519 = ptr_add(self->val_data, DEREF(_t518));
    (void)_t519;
    U64_delete(_t518, &(Bool){1});
    return _t519;
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
        Bool _wcond520; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond520 = *_hp; free(_hp); }
        (void)_wcond520;
        if (_wcond520) {
        } else {
            ;
            break;
        }
        ;
        U64 _t529 = U64_sub(hi, lo);
        (void)_t529;
        U64 _t530 = 2;
        (void)_t530;
        U64 _t531 = U64_div(_t529, _t530);
        (void)_t531;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t531);
        (void)mid;
        ;
        U64 *_t532 = malloc(sizeof(U64)); *_t532 = U64_mul(DEREF(mid), self->key_size);
        (void)_t532;
        void *_t533 = ptr_add(self->key_data, DEREF(_t532));
        (void)_t533;
        I64 *c = dyn_call_cmp(&self->key_type, _t533, key);
        (void)c;
        U64_delete(_t532, &(Bool){1});
        I64 _t534 = 0;
        (void)_t534;
        Bool _t535; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t534}); _t535 = *_hp; free(_hp); }
        (void)_t535;
        ;
        if (_t535) {
            U64 _t521 = 1;
            (void)_t521;
            U64 _t522 = U64_add(DEREF(mid), _t521);
            (void)_t522;
            ;
            lo = _t522;
            ;
        } else {
            I64 _t527 = 0;
            (void)_t527;
            Bool _t528; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t527}); _t528 = *_hp; free(_hp); }
            (void)_t528;
            ;
            if (_t528) {
                U64 _t523 = U64_clone(mid);
                (void)_t523;
                hi = _t523;
                ;
            } else {
                Bool _t524 = 1;
                (void)_t524;
                found = _t524;
                ;
                U64 _t525 = U64_clone(mid);
                (void)_t525;
                lo = _t525;
                ;
                U64 _t526 = U64_clone(mid);
                (void)_t526;
                hi = _t526;
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
        Bool _t540; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t540 = *_hp; free(_hp); }
        (void)_t540;
        Bool _t541 = Bool_not(_t540);
        (void)_t541;
        ;
        if (_t541) {
            Bool _t536 = 0;
            (void)_t536;
            dyn_call_delete(&self->key_type, key, &(Bool){_t536});
            ;
        }
        ;
        free(key);
        Bool _t542; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t542 = *_hp; free(_hp); }
        (void)_t542;
        Bool _t543 = Bool_not(_t542);
        (void)_t543;
        ;
        if (_t543) {
            U64 *_t537 = malloc(sizeof(U64)); *_t537 = U64_mul(lo, self->val_size);
            (void)_t537;
            void *_t538 = ptr_add(self->val_data, DEREF(_t537));
            (void)_t538;
            Bool _t539 = 0;
            (void)_t539;
            dyn_call_delete(&self->val_type, _t538, &(Bool){_t539});
            U64_delete(_t537, &(Bool){1});
            ;
        }
        ;
        U64 *_t544 = malloc(sizeof(U64)); *_t544 = U64_mul(lo, self->val_size);
        (void)_t544;
        void *_t545 = ptr_add(self->val_data, DEREF(_t544));
        (void)_t545;
        memcpy(_t545, val, self->val_size);
        U64_delete(_t544, &(Bool){1});
        free(val);
    } else {
        Bool _t552 = U64_eq(self->count, self->cap);
        (void)_t552;
        if (_t552) {
            U64 _t546 = 2;
            (void)_t546;
            U64 new_cap = U64_mul(self->cap, _t546);
            (void)new_cap;
            ;
            U64 _t547 = U64_mul(new_cap, self->key_size);
            (void)_t547;
            void *_t548 = realloc(self->key_data, _t547);
            (void)_t548;
            ;
            self->key_data = _t548;
            U64 _t549 = U64_mul(new_cap, self->val_size);
            (void)_t549;
            void *_t550 = realloc(self->val_data, _t549);
            (void)_t550;
            ;
            self->val_data = _t550;
            U64 _t551 = U64_clone(&(U64){new_cap});
            (void)_t551;
            ;
            self->cap = _t551;
            ;
        }
        ;
        U64 _t553 = 1;
        (void)_t553;
        U64 _t554 = U64_add(lo, _t553);
        (void)_t554;
        ;
        U64 *_t555 = malloc(sizeof(U64)); *_t555 = U64_mul(_t554, self->key_size);
        (void)_t555;
        ;
        U64 *_t556 = malloc(sizeof(U64)); *_t556 = U64_mul(lo, self->key_size);
        (void)_t556;
        U64 _t557 = U64_sub(self->count, lo);
        (void)_t557;
        void *_t558 = ptr_add(self->key_data, DEREF(_t555));
        (void)_t558;
        void *_t559 = ptr_add(self->key_data, DEREF(_t556));
        (void)_t559;
        U64 _t560 = U64_mul(_t557, self->key_size);
        (void)_t560;
        ;
        memmove(_t558, _t559, _t560);
        U64_delete(_t555, &(Bool){1});
        U64_delete(_t556, &(Bool){1});
        ;
        U64 _t561 = 1;
        (void)_t561;
        U64 _t562 = U64_add(lo, _t561);
        (void)_t562;
        ;
        U64 *_t563 = malloc(sizeof(U64)); *_t563 = U64_mul(_t562, self->val_size);
        (void)_t563;
        ;
        U64 *_t564 = malloc(sizeof(U64)); *_t564 = U64_mul(lo, self->val_size);
        (void)_t564;
        U64 _t565 = U64_sub(self->count, lo);
        (void)_t565;
        void *_t566 = ptr_add(self->val_data, DEREF(_t563));
        (void)_t566;
        void *_t567 = ptr_add(self->val_data, DEREF(_t564));
        (void)_t567;
        U64 _t568 = U64_mul(_t565, self->val_size);
        (void)_t568;
        ;
        memmove(_t566, _t567, _t568);
        U64_delete(_t563, &(Bool){1});
        U64_delete(_t564, &(Bool){1});
        ;
        U64 *_t569 = malloc(sizeof(U64)); *_t569 = U64_mul(lo, self->key_size);
        (void)_t569;
        void *_t570 = ptr_add(self->key_data, DEREF(_t569));
        (void)_t570;
        memcpy(_t570, key, self->key_size);
        U64_delete(_t569, &(Bool){1});
        U64 *_t571 = malloc(sizeof(U64)); *_t571 = U64_mul(lo, self->val_size);
        (void)_t571;
        void *_t572 = ptr_add(self->val_data, DEREF(_t571));
        (void)_t572;
        memcpy(_t572, val, self->val_size);
        U64_delete(_t571, &(Bool){1});
        free(key);
        free(val);
        U64 _t573 = 1;
        (void)_t573;
        U64 _t574 = U64_add(self->count, _t573);
        (void)_t574;
        ;
        self->count = _t574;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t595; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t595 = *_hp; free(_hp); }
    (void)_t595;
    Bool _t596 = Bool_not(_t595);
    (void)_t596;
    ;
    if (_t596) {
        {
            U64 _t583 = 0;
            (void)_t583;
            Range *_fc575 = Range_new(_t583, self->count);
            (void)_fc575;
            ;
            U64 _fi575 = 0;
            (void)_fi575;
            while (1) {
                U64 _t577; { U64 *_hp = (U64 *)Range_len(_fc575); _t577 = *_hp; free(_hp); }
                (void)_t577;
                Bool _wcond576; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi575}, &(U64){_t577}); _wcond576 = *_hp; free(_hp); }
                (void)_wcond576;
                ;
                if (_wcond576) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc575, _fi575); i = *_hp; free(_hp); }
                (void)i;
                U64 _t578 = 1;
                (void)_t578;
                U64 _t579 = U64_add(_fi575, _t578);
                (void)_t579;
                ;
                _fi575 = _t579;
                ;
                U64 *_t580 = malloc(sizeof(U64)); *_t580 = U64_mul(i, self->key_size);
                (void)_t580;
                ;
                void *_t581 = ptr_add(self->key_data, DEREF(_t580));
                (void)_t581;
                Bool _t582 = 0;
                (void)_t582;
                dyn_call_delete(&self->key_type, _t581, &(Bool){_t582});
                U64_delete(_t580, &(Bool){1});
                ;
            }
            Range_delete(_fc575, &(Bool){1});
            ;
        }
    }
    ;
    Bool _t597; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t597 = *_hp; free(_hp); }
    (void)_t597;
    Bool _t598 = Bool_not(_t597);
    (void)_t598;
    ;
    if (_t598) {
        {
            U64 _t592 = 0;
            (void)_t592;
            Range *_fc584 = Range_new(_t592, self->count);
            (void)_fc584;
            ;
            U64 _fi584 = 0;
            (void)_fi584;
            while (1) {
                U64 _t586; { U64 *_hp = (U64 *)Range_len(_fc584); _t586 = *_hp; free(_hp); }
                (void)_t586;
                Bool _wcond585; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi584}, &(U64){_t586}); _wcond585 = *_hp; free(_hp); }
                (void)_wcond585;
                ;
                if (_wcond585) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc584, _fi584); i = *_hp; free(_hp); }
                (void)i;
                U64 _t587 = 1;
                (void)_t587;
                U64 _t588 = U64_add(_fi584, _t587);
                (void)_t588;
                ;
                _fi584 = _t588;
                ;
                U64 *_t589 = malloc(sizeof(U64)); *_t589 = U64_mul(i, self->val_size);
                (void)_t589;
                ;
                void *_t590 = ptr_add(self->val_data, DEREF(_t589));
                (void)_t590;
                Bool _t591 = 0;
                (void)_t591;
                dyn_call_delete(&self->val_type, _t590, &(Bool){_t591});
                U64_delete(_t589, &(Bool){1});
                ;
            }
            Range_delete(_fc584, &(Bool){1});
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t599; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t599 = *_hp; free(_hp); }
    (void)_t599;
    Bool _t600 = Bool_not(_t599);
    (void)_t600;
    ;
    if (_t600) {
        Bool _t593 = 0;
        (void)_t593;
        Str_delete(&self->key_type, &(Bool){_t593});
        ;
    }
    ;
    Bool _t601; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t601 = *_hp; free(_hp); }
    (void)_t601;
    Bool _t602 = Bool_not(_t601);
    (void)_t602;
    ;
    if (_t602) {
        Bool _t594 = 0;
        (void)_t594;
        Str_delete(&self->val_type, &(Bool){_t594});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t617 = U64_mul(self->cap, self->key_size);
    (void)_t617;
    U8 *new_keys = malloc(_t617);
    (void)new_keys;
    ;
    U64 _t618 = U64_mul(self->cap, self->val_size);
    (void)_t618;
    U8 *new_vals = malloc(_t618);
    (void)new_vals;
    ;
    {
        U64 _t616 = 0;
        (void)_t616;
        Range *_fc603 = Range_new(_t616, self->count);
        (void)_fc603;
        ;
        U64 _fi603 = 0;
        (void)_fi603;
        while (1) {
            U64 _t605; { U64 *_hp = (U64 *)Range_len(_fc603); _t605 = *_hp; free(_hp); }
            (void)_t605;
            Bool _wcond604; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi603}, &(U64){_t605}); _wcond604 = *_hp; free(_hp); }
            (void)_wcond604;
            ;
            if (_wcond604) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc603, _fi603); i = *_hp; free(_hp); }
            (void)i;
            U64 _t606 = 1;
            (void)_t606;
            U64 _t607 = U64_add(_fi603, _t606);
            (void)_t607;
            ;
            _fi603 = _t607;
            ;
            U64 *_t608 = malloc(sizeof(U64)); *_t608 = U64_mul(i, self->key_size);
            (void)_t608;
            void *_t609 = ptr_add(self->key_data, DEREF(_t608));
            (void)_t609;
            void *ck = dyn_call_clone(&self->key_type, _t609);
            (void)ck;
            U64_delete(_t608, &(Bool){1});
            U64 *_t610 = malloc(sizeof(U64)); *_t610 = U64_mul(i, self->key_size);
            (void)_t610;
            void *_t611 = ptr_add(new_keys, DEREF(_t610));
            (void)_t611;
            memcpy(_t611, ck, self->key_size);
            U64_delete(_t610, &(Bool){1});
            free(ck);
            U64 *_t612 = malloc(sizeof(U64)); *_t612 = U64_mul(i, self->val_size);
            (void)_t612;
            void *_t613 = ptr_add(self->val_data, DEREF(_t612));
            (void)_t613;
            void *cv = dyn_call_clone(&self->val_type, _t613);
            (void)cv;
            U64_delete(_t612, &(Bool){1});
            U64 *_t614 = malloc(sizeof(U64)); *_t614 = U64_mul(i, self->val_size);
            (void)_t614;
            ;
            void *_t615 = ptr_add(new_vals, DEREF(_t614));
            (void)_t615;
            memcpy(_t615, cv, self->val_size);
            U64_delete(_t614, &(Bool){1});
            free(cv);
        }
        Range_delete(_fc603, &(Bool){1});
        ;
    }
    Map *_t619 = malloc(sizeof(Map));
    _t619->key_data = new_keys;
    _t619->val_data = new_vals;
    _t619->count = self->count;
    _t619->cap = self->cap;
    _t619->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t619->key_type = *_ca; free(_ca); }
    _t619->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t619->val_type = *_ca; free(_ca); }
    (void)_t619;
    return _t619;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t637; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t637 = *_hp; free(_hp); }
    (void)_t637;
    if (_t637) {
        Str *_t621 = Str_lit("Str", 3ULL);
        (void)_t621;
        U64 _t622; { U64 *_hp = (U64 *)Str_size(); _t622 = *_hp; free(_hp); }
        (void)_t622;
        U64 _t623 = 1;
        (void)_t623;
        Array *_va13 = Array_new(_t621, &(U64){_t622}, &(U64){_t623});
        (void)_va13;
        Str_delete(_t621, &(Bool){1});
        ;
        ;
        U64 _t624 = 0;
        (void)_t624;
        Str *_t625 = Str_lit("Set.new: elem_type required", 27ULL);
        (void)_t625;
        Array_set(_va13, &(U64){_t624}, _t625);
        ;
        Str *_t626 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:12:41", 60ULL);
        (void)_t626;
        panic(_t626, _va13);
        Str_delete(_t626, &(Bool){1});
    }
    ;
    Bool _t638 = dyn_has_cmp(elem_type);
    (void)_t638;
    Bool _t639 = Bool_not(_t638);
    (void)_t639;
    ;
    if (_t639) {
        Str *_t627 = Str_lit("Str", 3ULL);
        (void)_t627;
        U64 _t628; { U64 *_hp = (U64 *)Str_size(); _t628 = *_hp; free(_hp); }
        (void)_t628;
        U64 _t629 = 3;
        (void)_t629;
        Array *_va14 = Array_new(_t627, &(U64){_t628}, &(U64){_t629});
        (void)_va14;
        Str_delete(_t627, &(Bool){1});
        ;
        ;
        U64 _t630 = 0;
        (void)_t630;
        Str *_t631 = Str_lit("Set.new: type ", 14ULL);
        (void)_t631;
        Array_set(_va14, &(U64){_t630}, _t631);
        ;
        U64 _t632 = 1;
        (void)_t632;
        Str *_t633 = Str_clone(elem_type);
        (void)_t633;
        Array_set(_va14, &(U64){_t632}, _t633);
        ;
        U64 _t634 = 2;
        (void)_t634;
        Str *_t635 = Str_lit(" must implement cmp", 19ULL);
        (void)_t635;
        Array_set(_va14, &(U64){_t634}, _t635);
        ;
        Str *_t636 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:19", 60ULL);
        (void)_t636;
        panic(_t636, _va14);
        Str_delete(_t636, &(Bool){1});
    }
    ;
    void *_t640 = malloc(DEREF(elem_size));
    (void)_t640;
    U64 _t641 = 0;
    (void)_t641;
    I64 _t642 = 1;
    (void)_t642;
    U64 _t643 = U64_clone(elem_size);
    (void)_t643;
    Set *_t644 = malloc(sizeof(Set));
    _t644->data = _t640;
    _t644->count = _t641;
    _t644->cap = _t642;
    _t644->elem_size = _t643;
    { Str *_ca = Str_clone(elem_type); _t644->elem_type = *_ca; free(_ca); }
    (void)_t644;
    ;
    ;
    ;
    return _t644;
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
        Bool _wcond645; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond645 = *_hp; free(_hp); }
        (void)_wcond645;
        if (_wcond645) {
        } else {
            ;
            break;
        }
        ;
        U64 _t652 = U64_sub(hi, lo);
        (void)_t652;
        U64 _t653 = 2;
        (void)_t653;
        U64 _t654 = U64_div(_t652, _t653);
        (void)_t654;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t654);
        (void)mid;
        ;
        U64 *_t655 = malloc(sizeof(U64)); *_t655 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t655;
        void *_t656 = ptr_add(self->data, DEREF(_t655));
        (void)_t656;
        I64 *c = dyn_call_cmp(&self->elem_type, _t656, val);
        (void)c;
        U64_delete(_t655, &(Bool){1});
        I64 _t657 = 0;
        (void)_t657;
        Bool _t658; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t657}); _t658 = *_hp; free(_hp); }
        (void)_t658;
        ;
        if (_t658) {
            U64 _t646 = 1;
            (void)_t646;
            U64 _t647 = U64_add(DEREF(mid), _t646);
            (void)_t647;
            ;
            lo = _t647;
            ;
        } else {
            I64 _t650 = 0;
            (void)_t650;
            Bool _t651; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t650}); _t651 = *_hp; free(_hp); }
            (void)_t651;
            ;
            if (_t651) {
                U64 _t648 = U64_clone(mid);
                (void)_t648;
                hi = _t648;
                ;
            } else {
                Bool _t649 = 1;
                (void)_t649;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t649; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t659 = 0;
    (void)_t659;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t659; return _r; }
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
        Bool _wcond660; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond660 = *_hp; free(_hp); }
        (void)_wcond660;
        if (_wcond660) {
        } else {
            ;
            break;
        }
        ;
        U64 _t669 = U64_sub(hi, lo);
        (void)_t669;
        U64 _t670 = 2;
        (void)_t670;
        U64 _t671 = U64_div(_t669, _t670);
        (void)_t671;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t671);
        (void)mid;
        ;
        U64 *_t672 = malloc(sizeof(U64)); *_t672 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t672;
        void *_t673 = ptr_add(self->data, DEREF(_t672));
        (void)_t673;
        I64 *c = dyn_call_cmp(&self->elem_type, _t673, val);
        (void)c;
        U64_delete(_t672, &(Bool){1});
        I64 _t674 = 0;
        (void)_t674;
        Bool _t675; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t674}); _t675 = *_hp; free(_hp); }
        (void)_t675;
        ;
        if (_t675) {
            U64 _t661 = 1;
            (void)_t661;
            U64 _t662 = U64_add(DEREF(mid), _t661);
            (void)_t662;
            ;
            lo = _t662;
            ;
        } else {
            I64 _t667 = 0;
            (void)_t667;
            Bool _t668; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t667}); _t668 = *_hp; free(_hp); }
            (void)_t668;
            ;
            if (_t668) {
                U64 _t663 = U64_clone(mid);
                (void)_t663;
                hi = _t663;
                ;
            } else {
                Bool _t664 = 1;
                (void)_t664;
                found = _t664;
                ;
                U64 _t665 = U64_clone(mid);
                (void)_t665;
                lo = _t665;
                ;
                U64 _t666 = U64_clone(mid);
                (void)_t666;
                hi = _t666;
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
        Bool _t677; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t677 = *_hp; free(_hp); }
        (void)_t677;
        Bool _t678 = Bool_not(_t677);
        (void)_t678;
        ;
        if (_t678) {
            Bool _t676 = 0;
            (void)_t676;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t676});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t683 = U64_eq(self->count, self->cap);
        (void)_t683;
        if (_t683) {
            U64 _t679 = 2;
            (void)_t679;
            U64 new_cap = U64_mul(self->cap, _t679);
            (void)new_cap;
            ;
            U64 _t680 = U64_mul(new_cap, self->elem_size);
            (void)_t680;
            void *_t681 = realloc(self->data, _t680);
            (void)_t681;
            ;
            self->data = _t681;
            U64 _t682 = U64_clone(&(U64){new_cap});
            (void)_t682;
            ;
            self->cap = _t682;
            ;
        }
        ;
        U64 _t684 = 1;
        (void)_t684;
        U64 _t685 = U64_add(lo, _t684);
        (void)_t685;
        ;
        U64 *_t686 = malloc(sizeof(U64)); *_t686 = U64_mul(_t685, self->elem_size);
        (void)_t686;
        ;
        U64 *_t687 = malloc(sizeof(U64)); *_t687 = U64_mul(lo, self->elem_size);
        (void)_t687;
        U64 _t688 = U64_sub(self->count, lo);
        (void)_t688;
        void *_t689 = ptr_add(self->data, DEREF(_t686));
        (void)_t689;
        void *_t690 = ptr_add(self->data, DEREF(_t687));
        (void)_t690;
        U64 _t691 = U64_mul(_t688, self->elem_size);
        (void)_t691;
        ;
        memmove(_t689, _t690, _t691);
        U64_delete(_t686, &(Bool){1});
        U64_delete(_t687, &(Bool){1});
        ;
        U64 *_t692 = malloc(sizeof(U64)); *_t692 = U64_mul(lo, self->elem_size);
        (void)_t692;
        void *_t693 = ptr_add(self->data, DEREF(_t692));
        (void)_t693;
        memcpy(_t693, val, self->elem_size);
        U64_delete(_t692, &(Bool){1});
        free(val);
        U64 _t694 = 1;
        (void)_t694;
        U64 _t695 = U64_add(self->count, _t694);
        (void)_t695;
        ;
        self->count = _t695;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t706; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t706 = *_hp; free(_hp); }
    (void)_t706;
    Bool _t707 = Bool_not(_t706);
    (void)_t707;
    ;
    if (_t707) {
        {
            U64 _t704 = 0;
            (void)_t704;
            Range *_fc696 = Range_new(_t704, self->count);
            (void)_fc696;
            ;
            U64 _fi696 = 0;
            (void)_fi696;
            while (1) {
                U64 _t698; { U64 *_hp = (U64 *)Range_len(_fc696); _t698 = *_hp; free(_hp); }
                (void)_t698;
                Bool _wcond697; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi696}, &(U64){_t698}); _wcond697 = *_hp; free(_hp); }
                (void)_wcond697;
                ;
                if (_wcond697) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc696, _fi696); i = *_hp; free(_hp); }
                (void)i;
                U64 _t699 = 1;
                (void)_t699;
                U64 _t700 = U64_add(_fi696, _t699);
                (void)_t700;
                ;
                _fi696 = _t700;
                ;
                U64 *_t701 = malloc(sizeof(U64)); *_t701 = U64_mul(i, self->elem_size);
                (void)_t701;
                ;
                void *_t702 = ptr_add(self->data, DEREF(_t701));
                (void)_t702;
                Bool _t703 = 0;
                (void)_t703;
                dyn_call_delete(&self->elem_type, _t702, &(Bool){_t703});
                U64_delete(_t701, &(Bool){1});
                ;
            }
            Range_delete(_fc696, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t708; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t708 = *_hp; free(_hp); }
    (void)_t708;
    Bool _t709 = Bool_not(_t708);
    (void)_t709;
    ;
    if (_t709) {
        Bool _t705 = 0;
        (void)_t705;
        Str_delete(&self->elem_type, &(Bool){_t705});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t720 = U64_mul(self->cap, self->elem_size);
    (void)_t720;
    U8 *new_data = malloc(_t720);
    (void)new_data;
    ;
    {
        U64 _t719 = 0;
        (void)_t719;
        Range *_fc710 = Range_new(_t719, self->count);
        (void)_fc710;
        ;
        U64 _fi710 = 0;
        (void)_fi710;
        while (1) {
            U64 _t712; { U64 *_hp = (U64 *)Range_len(_fc710); _t712 = *_hp; free(_hp); }
            (void)_t712;
            Bool _wcond711; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi710}, &(U64){_t712}); _wcond711 = *_hp; free(_hp); }
            (void)_wcond711;
            ;
            if (_wcond711) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc710, _fi710); i = *_hp; free(_hp); }
            (void)i;
            U64 _t713 = 1;
            (void)_t713;
            U64 _t714 = U64_add(_fi710, _t713);
            (void)_t714;
            ;
            _fi710 = _t714;
            ;
            U64 *_t715 = malloc(sizeof(U64)); *_t715 = U64_mul(i, self->elem_size);
            (void)_t715;
            void *_t716 = ptr_add(self->data, DEREF(_t715));
            (void)_t716;
            void *cloned = dyn_call_clone(&self->elem_type, _t716);
            (void)cloned;
            U64_delete(_t715, &(Bool){1});
            U64 *_t717 = malloc(sizeof(U64)); *_t717 = U64_mul(i, self->elem_size);
            (void)_t717;
            ;
            void *_t718 = ptr_add(new_data, DEREF(_t717));
            (void)_t718;
            memcpy(_t718, cloned, self->elem_size);
            U64_delete(_t717, &(Bool){1});
            free(cloned);
        }
        Range_delete(_fc710, &(Bool){1});
        ;
    }
    Set *_t721 = malloc(sizeof(Set));
    _t721->data = new_data;
    _t721->count = self->count;
    _t721->cap = self->cap;
    _t721->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t721->elem_type = *_ca; free(_ca); }
    (void)_t721;
    return _t721;
}

U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t729; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t729 = *_hp; free(_hp); }
    (void)_t729;
    if (_t729) {
        Str *_t723 = Str_lit("Str", 3ULL);
        (void)_t723;
        U64 _t724; { U64 *_hp = (U64 *)Str_size(); _t724 = *_hp; free(_hp); }
        (void)_t724;
        U64 _t725 = 1;
        (void)_t725;
        Array *_va15 = Array_new(_t723, &(U64){_t724}, &(U64){_t725});
        (void)_va15;
        Str_delete(_t723, &(Bool){1});
        ;
        ;
        U64 _t726 = 0;
        (void)_t726;
        Str *_t727 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t727;
        Array_set(_va15, &(U64){_t726}, _t727);
        ;
        Str *_t728 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t728;
        panic(_t728, _va15);
        Str_delete(_t728, &(Bool){1});
    }
    ;
    void *_t730 = ptr_add(self->c_str, DEREF(i));
    (void)_t730;
    return _t730;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t731 = ptr_add(self->c_str, DEREF(i));
    (void)_t731;
    return _t731;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t740; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t740 = *_hp; free(_hp); }
    (void)_t740;
    if (_t740) {
        min_len = b->count;
    }
    ;
    {
        U64 _t739 = 0;
        (void)_t739;
        Range *_fc732 = Range_new(_t739, min_len);
        (void)_fc732;
        ;
        U64 _fi732 = 0;
        (void)_fi732;
        while (1) {
            U64 _t734; { U64 *_hp = (U64 *)Range_len(_fc732); _t734 = *_hp; free(_hp); }
            (void)_t734;
            Bool _wcond733; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi732}, &(U64){_t734}); _wcond733 = *_hp; free(_hp); }
            (void)_wcond733;
            ;
            if (_wcond733) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc732, _fi732);
            (void)i;
            U64 _t735 = 1;
            (void)_t735;
            U64 _t736 = U64_add(_fi732, _t735);
            (void)_t736;
            ;
            _fi732 = _t736;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t737 = 0;
            (void)_t737;
            Bool _t738; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t737}); _t738 = *_hp; free(_hp); }
            (void)_t738;
            ;
            if (_t738) {
                ;
                Range_delete(_fc732, &(Bool){1});
                ;
                return c;
            }
            ;
            I64_delete(c, &(Bool){1});
        }
        Range_delete(_fc732, &(Bool){1});
        ;
    }
    ;
    I64 _t741 = U64_cmp(a->count, b->count);
    (void)_t741;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t741; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t742 = 1;
    (void)_t742;
    U64 _t743 = U64_add(DEREF(new_len), _t742);
    (void)_t743;
    ;
    U8 *new_data = malloc(_t743);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t744 = ptr_add(new_data, a->count);
    (void)_t744;
    memcpy(_t744, b->c_str, b->count);
    void *_t745 = ptr_add(new_data, DEREF(new_len));
    (void)_t745;
    I32 _t746 = 0;
    (void)_t746;
    U64 _t747 = 1;
    (void)_t747;
    memset(_t745, _t746, _t747);
    ;
    ;
    U64 _t748 = U64_clone(new_len);
    (void)_t748;
    U64 _t749 = U64_clone(new_len);
    (void)_t749;
    U64_delete(new_len, &(Bool){1});
    Str *_t750 = malloc(sizeof(Str));
    _t750->c_str = new_data;
    _t750->count = _t748;
    _t750->cap = _t749;
    (void)_t750;
    ;
    ;
    return _t750;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t751 = 1;
    (void)_t751;
    U64 _t752 = U64_add(DEREF(n), _t751);
    (void)_t752;
    ;
    U8 *buf = malloc(_t752);
    (void)buf;
    ;
    I32 _t753 = 0;
    (void)_t753;
    U64 _t754 = 1;
    (void)_t754;
    memset(buf, _t753, _t754);
    ;
    ;
    I64 _t755 = 0;
    (void)_t755;
    U64 _t756 = U64_clone(n);
    (void)_t756;
    Str *_t757 = malloc(sizeof(Str));
    _t757->c_str = buf;
    _t757->count = _t755;
    _t757->cap = _t756;
    (void)_t757;
    ;
    ;
    return _t757;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t770; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t770 = *_hp; free(_hp); }
    (void)_t770;
    if (_t770) {
        Str *_t758 = Str_lit("Str", 3ULL);
        (void)_t758;
        U64 _t759; { U64 *_hp = (U64 *)Str_size(); _t759 = *_hp; free(_hp); }
        (void)_t759;
        U64 _t760 = 1;
        (void)_t760;
        Array *_va16 = Array_new(_t758, &(U64){_t759}, &(U64){_t760});
        (void)_va16;
        Str_delete(_t758, &(Bool){1});
        ;
        ;
        U64 _t761 = 0;
        (void)_t761;
        Str *_t762 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t762;
        Array_set(_va16, &(U64){_t761}, _t762);
        ;
        Str *_t763 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t763;
        panic(_t763, _va16);
        Str_delete(_t763, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t771; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t771 = *_hp; free(_hp); }
    (void)_t771;
    if (_t771) {
        Str *_t764 = Str_lit("Str", 3ULL);
        (void)_t764;
        U64 _t765; { U64 *_hp = (U64 *)Str_size(); _t765 = *_hp; free(_hp); }
        (void)_t765;
        U64 _t766 = 1;
        (void)_t766;
        Array *_va17 = Array_new(_t764, &(U64){_t765}, &(U64){_t766});
        (void)_va17;
        Str_delete(_t764, &(Bool){1});
        ;
        ;
        U64 _t767 = 0;
        (void)_t767;
        Str *_t768 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t768;
        Array_set(_va17, &(U64){_t767}, _t768);
        ;
        Str *_t769 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t769;
        panic(_t769, _va17);
        Str_delete(_t769, &(Bool){1});
    }
    ;
    void *_t772 = ptr_add(self->c_str, self->count);
    (void)_t772;
    memcpy(_t772, s->c_str, s->count);
    U64 _t773 = U64_clone(new_len);
    (void)_t773;
    self->count = _t773;
    ;
    void *_t774 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t774;
    I32 _t775 = 0;
    (void)_t775;
    U64 _t776 = 1;
    (void)_t776;
    memset(_t774, _t775, _t776);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t777 = 1;
    (void)_t777;
    U64 _t778 = U64_add(val->count, _t777);
    (void)_t778;
    ;
    U8 *new_data = malloc(_t778);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t779 = ptr_add(new_data, val->count);
    (void)_t779;
    I32 _t780 = 0;
    (void)_t780;
    U64 _t781 = 1;
    (void)_t781;
    memset(_t779, _t780, _t781);
    ;
    ;
    Str *_t782 = malloc(sizeof(Str));
    _t782->c_str = new_data;
    _t782->count = val->count;
    _t782->cap = val->count;
    (void)_t782;
    return _t782;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t783; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t783 = *_hp; free(_hp); }
    (void)_t783;
    if (_t783) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t784 = Str_clone(val);
    (void)_t784;
    return _t784;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t786; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t786 = *_hp; free(_hp); }
    (void)_t786;
    if (_t786) {
        *st = s->count;
    }
    ;
    U64 _t787 = U64_add(DEREF(st), ln);
    (void)_t787;
    Bool _t788; { Bool *_hp = (Bool *)U64_gt(&(U64){_t787}, &s->count); _t788 = *_hp; free(_hp); }
    (void)_t788;
    ;
    if (_t788) {
        U64 _t785 = U64_sub(s->count, DEREF(st));
        (void)_t785;
        ln = _t785;
        ;
    }
    ;
    void *_t789 = ptr_add(s->c_str, DEREF(st));
    (void)_t789;
    U64 _t790 = U64_clone(&(U64){ln});
    (void)_t790;
    ;
    U64 _t791 = U64_clone(CAP_VIEW);
    (void)_t791;
    Str *_t792 = malloc(sizeof(Str));
    _t792->c_str = _t789;
    _t792->count = _t790;
    _t792->cap = _t791;
    (void)_t792;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t792;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t814 = 0;
    (void)_t814;
    Bool _t815 = U64_eq(b->count, _t814);
    (void)_t815;
    ;
    if (_t815) {
        Bool _t793 = 1;
        (void)_t793;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t793; return _r; }
    }
    ;
    Bool _t816; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t816 = *_hp; free(_hp); }
    (void)_t816;
    if (_t816) {
        Bool _t794 = 0;
        (void)_t794;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t794; return _r; }
    }
    ;
    {
        U64 _t810 = U64_sub(a->count, b->count);
        (void)_t810;
        U64 _t811 = 1;
        (void)_t811;
        U64 _t812 = 0;
        (void)_t812;
        U64 _t813 = U64_add(_t810, _t811);
        (void)_t813;
        ;
        ;
        Range *_fc795 = Range_new(_t812, _t813);
        (void)_fc795;
        ;
        ;
        U64 _fi795 = 0;
        (void)_fi795;
        while (1) {
            U64 _t807; { U64 *_hp = (U64 *)Range_len(_fc795); _t807 = *_hp; free(_hp); }
            (void)_t807;
            Bool _wcond796; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi795}, &(U64){_t807}); _wcond796 = *_hp; free(_hp); }
            (void)_wcond796;
            ;
            if (_wcond796) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc795, _fi795); i = *_hp; free(_hp); }
            (void)i;
            U64 _t808 = 1;
            (void)_t808;
            U64 _t809 = U64_add(_fi795, _t808);
            (void)_t809;
            ;
            _fi795 = _t809;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t805 = 0;
                (void)_t805;
                Range *_fc797 = Range_new(_t805, b->count);
                (void)_fc797;
                ;
                U64 _fi797 = 0;
                (void)_fi797;
                while (1) {
                    U64 _t800; { U64 *_hp = (U64 *)Range_len(_fc797); _t800 = *_hp; free(_hp); }
                    (void)_t800;
                    Bool _wcond798; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi797}, &(U64){_t800}); _wcond798 = *_hp; free(_hp); }
                    (void)_wcond798;
                    ;
                    if (_wcond798) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc797, _fi797);
                    (void)j;
                    U64 _t801 = 1;
                    (void)_t801;
                    U64 _t802 = U64_add(_fi797, _t801);
                    (void)_t802;
                    ;
                    _fi797 = _t802;
                    ;
                    U64 *_t803 = malloc(sizeof(U64)); *_t803 = U64_add(i, DEREF(j));
                    (void)_t803;
                    U8 *ac = Str_get(a, _t803);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t804; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t804 = *_hp; free(_hp); }
                    (void)_t804;
                    U64_delete(_t803, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t804) {
                        Bool _t799 = 0;
                        (void)_t799;
                        found = _t799;
                        ;
                    }
                    ;
                }
                Range_delete(_fc797, &(Bool){1});
                ;
            }
            ;
            if (found) {
                Bool _t806 = 1;
                (void)_t806;
                ;
                Range_delete(_fc795, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t806; return _r; }
            }
            ;
        }
        Range_delete(_fc795, &(Bool){1});
        ;
    }
    Bool _t817 = 0;
    (void)_t817;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t817; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t827; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t827 = *_hp; free(_hp); }
    (void)_t827;
    if (_t827) {
        Bool _t818 = 0;
        (void)_t818;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t818; return _r; }
    }
    ;
    {
        U64 _t826 = 0;
        (void)_t826;
        Range *_fc819 = Range_new(_t826, b->count);
        (void)_fc819;
        ;
        U64 _fi819 = 0;
        (void)_fi819;
        while (1) {
            U64 _t822; { U64 *_hp = (U64 *)Range_len(_fc819); _t822 = *_hp; free(_hp); }
            (void)_t822;
            Bool _wcond820; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi819}, &(U64){_t822}); _wcond820 = *_hp; free(_hp); }
            (void)_wcond820;
            ;
            if (_wcond820) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc819, _fi819);
            (void)i;
            U64 _t823 = 1;
            (void)_t823;
            U64 _t824 = U64_add(_fi819, _t823);
            (void)_t824;
            ;
            _fi819 = _t824;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t825; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t825 = *_hp; free(_hp); }
            (void)_t825;
            U64_delete(i, &(Bool){1});
            if (_t825) {
                Bool _t821 = 0;
                (void)_t821;
                ;
                Range_delete(_fc819, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t821; return _r; }
            }
            ;
        }
        Range_delete(_fc819, &(Bool){1});
        ;
    }
    Bool _t828 = 1;
    (void)_t828;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t828; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t839; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t839 = *_hp; free(_hp); }
    (void)_t839;
    if (_t839) {
        Bool _t829 = 0;
        (void)_t829;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t829; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _t838 = 0;
        (void)_t838;
        Range *_fc830 = Range_new(_t838, b->count);
        (void)_fc830;
        ;
        U64 _fi830 = 0;
        (void)_fi830;
        while (1) {
            U64 _t833; { U64 *_hp = (U64 *)Range_len(_fc830); _t833 = *_hp; free(_hp); }
            (void)_t833;
            Bool _wcond831; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi830}, &(U64){_t833}); _wcond831 = *_hp; free(_hp); }
            (void)_wcond831;
            ;
            if (_wcond831) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc830, _fi830);
            (void)i;
            U64 _t834 = 1;
            (void)_t834;
            U64 _t835 = U64_add(_fi830, _t834);
            (void)_t835;
            ;
            _fi830 = _t835;
            ;
            U64 *_t836 = malloc(sizeof(U64)); *_t836 = U64_add(offset, DEREF(i));
            (void)_t836;
            U8 *ac = Str_get(a, _t836);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t837; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t837 = *_hp; free(_hp); }
            (void)_t837;
            U64_delete(_t836, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t837) {
                Bool _t832 = 0;
                (void)_t832;
                ;
                Range_delete(_fc830, &(Bool){1});
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t832; return _r; }
            }
            ;
        }
        Range_delete(_fc830, &(Bool){1});
        ;
    }
    ;
    Bool _t840 = 1;
    (void)_t840;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t840; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t841 = 0;
    (void)_t841;
    Bool _t842 = U64_eq(self->count, _t841);
    (void)_t842;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t842; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t868 = 0;
    (void)_t868;
    Bool _t869 = U64_eq(needle->count, _t868);
    (void)_t869;
    ;
    if (_t869) {
        I64 _t843 = 0;
        (void)_t843;
        I64 _t844 = 1;
        (void)_t844;
        I64 _t845 = I64_sub(_t843, _t844);
        (void)_t845;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t845; return _r; }
    }
    ;
    Bool _t870; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t870 = *_hp; free(_hp); }
    (void)_t870;
    if (_t870) {
        I64 _t846 = 0;
        (void)_t846;
        I64 _t847 = 1;
        (void)_t847;
        I64 _t848 = I64_sub(_t846, _t847);
        (void)_t848;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t848; return _r; }
    }
    ;
    {
        U64 _t864 = U64_sub(self->count, needle->count);
        (void)_t864;
        U64 _t865 = 1;
        (void)_t865;
        U64 _t866 = 0;
        (void)_t866;
        U64 _t867 = U64_add(_t864, _t865);
        (void)_t867;
        ;
        ;
        Range *_fc849 = Range_new(_t866, _t867);
        (void)_fc849;
        ;
        ;
        U64 _fi849 = 0;
        (void)_fi849;
        while (1) {
            U64 _t861; { U64 *_hp = (U64 *)Range_len(_fc849); _t861 = *_hp; free(_hp); }
            (void)_t861;
            Bool _wcond850; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi849}, &(U64){_t861}); _wcond850 = *_hp; free(_hp); }
            (void)_wcond850;
            ;
            if (_wcond850) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc849, _fi849); i = *_hp; free(_hp); }
            (void)i;
            U64 _t862 = 1;
            (void)_t862;
            U64 _t863 = U64_add(_fi849, _t862);
            (void)_t863;
            ;
            _fi849 = _t863;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t859 = 0;
                (void)_t859;
                Range *_fc851 = Range_new(_t859, needle->count);
                (void)_fc851;
                ;
                U64 _fi851 = 0;
                (void)_fi851;
                while (1) {
                    U64 _t854; { U64 *_hp = (U64 *)Range_len(_fc851); _t854 = *_hp; free(_hp); }
                    (void)_t854;
                    Bool _wcond852; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi851}, &(U64){_t854}); _wcond852 = *_hp; free(_hp); }
                    (void)_wcond852;
                    ;
                    if (_wcond852) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc851, _fi851);
                    (void)j;
                    U64 _t855 = 1;
                    (void)_t855;
                    U64 _t856 = U64_add(_fi851, _t855);
                    (void)_t856;
                    ;
                    _fi851 = _t856;
                    ;
                    U64 *_t857 = malloc(sizeof(U64)); *_t857 = U64_add(i, DEREF(j));
                    (void)_t857;
                    U8 *ac = Str_get(self, _t857);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t858; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t858 = *_hp; free(_hp); }
                    (void)_t858;
                    U64_delete(_t857, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t858) {
                        Bool _t853 = 0;
                        (void)_t853;
                        found = _t853;
                        ;
                    }
                    ;
                }
                Range_delete(_fc851, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t860 = U64_to_i64(i);
                (void)_t860;
                ;
                ;
                Range_delete(_fc849, &(Bool){1});
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t860; return _r; }
            }
            ;
            ;
        }
        Range_delete(_fc849, &(Bool){1});
        ;
    }
    I64 _t871 = 0;
    (void)_t871;
    I64 _t872 = 1;
    (void)_t872;
    I64 _t873 = I64_sub(_t871, _t872);
    (void)_t873;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t873; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t899 = 0;
    (void)_t899;
    Bool _t900 = U64_eq(needle->count, _t899);
    (void)_t900;
    ;
    if (_t900) {
        I64 _t874 = 0;
        (void)_t874;
        I64 _t875 = 1;
        (void)_t875;
        I64 _t876 = I64_sub(_t874, _t875);
        (void)_t876;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t876; return _r; }
    }
    ;
    Bool _t901; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t901 = *_hp; free(_hp); }
    (void)_t901;
    if (_t901) {
        I64 _t877 = 0;
        (void)_t877;
        I64 _t878 = 1;
        (void)_t878;
        I64 _t879 = I64_sub(_t877, _t878);
        (void)_t879;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t879; return _r; }
    }
    ;
    I64 _t902 = 0;
    (void)_t902;
    I64 _t903 = 1;
    (void)_t903;
    I64 last = I64_sub(_t902, _t903);
    (void)last;
    ;
    ;
    {
        U64 _t895 = U64_sub(self->count, needle->count);
        (void)_t895;
        U64 _t896 = 1;
        (void)_t896;
        U64 _t897 = 0;
        (void)_t897;
        U64 _t898 = U64_add(_t895, _t896);
        (void)_t898;
        ;
        ;
        Range *_fc880 = Range_new(_t897, _t898);
        (void)_fc880;
        ;
        ;
        U64 _fi880 = 0;
        (void)_fi880;
        while (1) {
            U64 _t892; { U64 *_hp = (U64 *)Range_len(_fc880); _t892 = *_hp; free(_hp); }
            (void)_t892;
            Bool _wcond881; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi880}, &(U64){_t892}); _wcond881 = *_hp; free(_hp); }
            (void)_wcond881;
            ;
            if (_wcond881) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc880, _fi880); i = *_hp; free(_hp); }
            (void)i;
            U64 _t893 = 1;
            (void)_t893;
            U64 _t894 = U64_add(_fi880, _t893);
            (void)_t894;
            ;
            _fi880 = _t894;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _t890 = 0;
                (void)_t890;
                Range *_fc882 = Range_new(_t890, needle->count);
                (void)_fc882;
                ;
                U64 _fi882 = 0;
                (void)_fi882;
                while (1) {
                    U64 _t885; { U64 *_hp = (U64 *)Range_len(_fc882); _t885 = *_hp; free(_hp); }
                    (void)_t885;
                    Bool _wcond883; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi882}, &(U64){_t885}); _wcond883 = *_hp; free(_hp); }
                    (void)_wcond883;
                    ;
                    if (_wcond883) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 *j = Range_get(_fc882, _fi882);
                    (void)j;
                    U64 _t886 = 1;
                    (void)_t886;
                    U64 _t887 = U64_add(_fi882, _t886);
                    (void)_t887;
                    ;
                    _fi882 = _t887;
                    ;
                    U64 *_t888 = malloc(sizeof(U64)); *_t888 = U64_add(i, DEREF(j));
                    (void)_t888;
                    U8 *ac = Str_get(self, _t888);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t889; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t889 = *_hp; free(_hp); }
                    (void)_t889;
                    U64_delete(_t888, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t889) {
                        Bool _t884 = 0;
                        (void)_t884;
                        found = _t884;
                        ;
                    }
                    ;
                }
                Range_delete(_fc882, &(Bool){1});
                ;
            }
            if (found) {
                I64 _t891 = U64_to_i64(i);
                (void)_t891;
                last = _t891;
                ;
            }
            ;
            ;
        }
        Range_delete(_fc880, &(Bool){1});
        ;
    }
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t919 = 0;
    (void)_t919;
    Bool _t920 = U64_eq(from->count, _t919);
    (void)_t920;
    ;
    if (_t920) {
        Str *_t904 = Str_clone(self);
        (void)_t904;
        ;
        return _t904;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t906 = U64_sub(self->count, from->count);
        (void)_t906;
        Bool _wcond905; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t906}); _wcond905 = *_hp; free(_hp); }
        (void)_wcond905;
        ;
        if (_wcond905) {
        } else {
            ;
            break;
        }
        ;
        U64 _t907 = U64_sub(self->count, start);
        (void)_t907;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t907});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t908 = 0;
        (void)_t908;
        I64 _t909 = 1;
        (void)_t909;
        I64 _t910 = I64_sub(_t908, _t909);
        (void)_t910;
        ;
        ;
        Bool _t911 = I64_eq(pos, _t910);
        (void)_t911;
        ;
        if (_t911) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t912 = I64_to_u64(pos);
        (void)_t912;
        Str *_t913 = Str_substr(self, &(U64){start}, &(U64){_t912});
        (void)_t913;
        ;
        result = Str_concat(result, _t913);
        Str_delete(_t913, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t914 = I64_to_u64(pos);
        (void)_t914;
        ;
        U64 _t915 = U64_add(start, _t914);
        (void)_t915;
        ;
        U64 _t916 = U64_add(_t915, from->count);
        (void)_t916;
        ;
        start = _t916;
        ;
    }
    Bool _t921; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t921 = *_hp; free(_hp); }
    (void)_t921;
    if (_t921) {
        U64 _t917 = U64_sub(self->count, start);
        (void)_t917;
        Str *_t918 = Str_substr(self, &(U64){start}, &(U64){_t917});
        (void)_t918;
        ;
        result = Str_concat(result, _t918);
        Str_delete(_t918, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t922 = 1;
    (void)_t922;
    Str *_t923 = Str_substr(self, i, &(U64){_t922});
    (void)_t923;
    ;
    return _t923;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t926; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t926 = *_hp; free(_hp); }
    (void)_t926;
    if (_t926) {
        U64 _t924 = U64_sub(self->count, prefix->count);
        (void)_t924;
        Str *_t925 = Str_substr(self, &prefix->count, &(U64){_t924});
        (void)_t925;
        ;
        ;
        return _t925;
    }
    ;
    Str *_t927 = Str_clone(self);
    (void)_t927;
    return _t927;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t931; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t931 = *_hp; free(_hp); }
    (void)_t931;
    if (_t931) {
        U64 _t928 = 0;
        (void)_t928;
        U64 _t929 = U64_sub(self->count, suffix->count);
        (void)_t929;
        Str *_t930 = Str_substr(self, &(U64){_t928}, &(U64){_t929});
        (void)_t930;
        ;
        ;
        ;
        return _t930;
    }
    ;
    Str *_t932 = Str_clone(self);
    (void)_t932;
    return _t932;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t933 = 2;
    (void)_t933;
    U8 *buf = malloc(_t933);
    (void)buf;
    ;
    U64 _t934 = 1;
    (void)_t934;
    memcpy(buf, byte, _t934);
    ;
    U64 *_t935 = malloc(sizeof(U64));
    *_t935 = 1;
    (void)_t935;
    void *_t936 = ptr_add(buf, DEREF(_t935));
    (void)_t936;
    I32 _t937 = 0;
    (void)_t937;
    U64 _t938 = 1;
    (void)_t938;
    memset(_t936, _t937, _t938);
    U64_delete(_t935, &(Bool){1});
    ;
    ;
    I64 _t939 = 1;
    (void)_t939;
    I64 _t940 = 1;
    (void)_t940;
    Str *_t941 = malloc(sizeof(Str));
    _t941->c_str = buf;
    _t941->count = _t939;
    _t941->cap = _t940;
    (void)_t941;
    ;
    ;
    return _t941;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t983 = 0;
    (void)_t983;
    Bool _t984 = U64_eq(self->count, _t983);
    (void)_t984;
    ;
    if (_t984) {
        Str *_t942 = Str_lit("Str", 3ULL);
        (void)_t942;
        U64 _t943; { U64 *_hp = (U64 *)Str_size(); _t943 = *_hp; free(_hp); }
        (void)_t943;
        U64 _t944 = 1;
        (void)_t944;
        Array *_va18 = Array_new(_t942, &(U64){_t943}, &(U64){_t944});
        (void)_va18;
        Str_delete(_t942, &(Bool){1});
        ;
        ;
        U64 _t945 = 0;
        (void)_t945;
        Str *_t946 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t946;
        Array_set(_va18, &(U64){_t945}, _t946);
        ;
        Str *_t947 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t947;
        panic(_t947, _va18);
        Str_delete(_t947, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t985 = malloc(sizeof(U64));
    *_t985 = 0;
    (void)_t985;
    U8 *first = Str_get(self, _t985);
    (void)first;
    U8 _t986 = 45;
    (void)_t986;
    Bool _t987 = U8_eq(DEREF(first), _t986);
    (void)_t987;
    U64_delete(_t985, &(Bool){1});
    ;
    if (_t987) {
        Bool _t948 = 1;
        (void)_t948;
        neg = _t948;
        ;
        U64 _t949 = 1;
        (void)_t949;
        start = _t949;
        ;
    }
    ;
    Bool _t988 = U64_eq(start, self->count);
    (void)_t988;
    if (_t988) {
        Str *_t950 = Str_lit("Str", 3ULL);
        (void)_t950;
        U64 _t951; { U64 *_hp = (U64 *)Str_size(); _t951 = *_hp; free(_hp); }
        (void)_t951;
        U64 _t952 = 1;
        (void)_t952;
        Array *_va19 = Array_new(_t950, &(U64){_t951}, &(U64){_t952});
        (void)_va19;
        Str_delete(_t950, &(Bool){1});
        ;
        ;
        U64 _t953 = 0;
        (void)_t953;
        Str *_t954 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t954;
        Array_set(_va19, &(U64){_t953}, _t954);
        ;
        Str *_t955 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t955;
        panic(_t955, _va19);
        Str_delete(_t955, &(Bool){1});
    }
    ;
    {
        Range *_fc956 = Range_new(start, self->count);
        (void)_fc956;
        U64 _fi956 = 0;
        (void)_fi956;
        while (1) {
            U64 _t968; { U64 *_hp = (U64 *)Range_len(_fc956); _t968 = *_hp; free(_hp); }
            (void)_t968;
            Bool _wcond957; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi956}, &(U64){_t968}); _wcond957 = *_hp; free(_hp); }
            (void)_wcond957;
            ;
            if (_wcond957) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc956, _fi956);
            (void)i;
            U64 _t969 = 1;
            (void)_t969;
            U64 _t970 = U64_add(_fi956, _t969);
            (void)_t970;
            ;
            _fi956 = _t970;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t971 = U8_to_i64(DEREF(ch));
            (void)_t971;
            U64_delete(i, &(Bool){1});
            I64 _t972 = 48;
            (void)_t972;
            I64 d = I64_sub(_t971, _t972);
            (void)d;
            ;
            ;
            I64 _t973 = 0;
            (void)_t973;
            I64 _t974 = 9;
            (void)_t974;
            Bool _t975; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t973}); _t975 = *_hp; free(_hp); }
            (void)_t975;
            ;
            Bool _t976; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t974}); _t976 = *_hp; free(_hp); }
            (void)_t976;
            ;
            Bool _t977 = Bool_or(_t975, _t976);
            (void)_t977;
            ;
            ;
            if (_t977) {
                Str *_t958 = Str_lit("Str", 3ULL);
                (void)_t958;
                U64 _t959; { U64 *_hp = (U64 *)Str_size(); _t959 = *_hp; free(_hp); }
                (void)_t959;
                U64 _t960 = 3;
                (void)_t960;
                Array *_va20 = Array_new(_t958, &(U64){_t959}, &(U64){_t960});
                (void)_va20;
                Str_delete(_t958, &(Bool){1});
                ;
                ;
                U64 _t961 = 0;
                (void)_t961;
                Str *_t962 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t962;
                Array_set(_va20, &(U64){_t961}, _t962);
                ;
                U64 _t963 = 1;
                (void)_t963;
                Str *_t964 = Str_clone(self);
                (void)_t964;
                Array_set(_va20, &(U64){_t963}, _t964);
                ;
                U64 _t965 = 2;
                (void)_t965;
                Str *_t966 = Str_lit("'", 1ULL);
                (void)_t966;
                Array_set(_va20, &(U64){_t965}, _t966);
                ;
                Str *_t967 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t967;
                panic(_t967, _va20);
                Str_delete(_t967, &(Bool){1});
            }
            ;
            I64 _t978 = 10;
            (void)_t978;
            I64 _t979 = I64_mul(result, _t978);
            (void)_t979;
            ;
            I64 _t980 = I64_add(_t979, d);
            (void)_t980;
            ;
            ;
            result = _t980;
            ;
        }
        Range_delete(_fc956, &(Bool){1});
        ;
    }
    ;
    if (neg) {
        I64 _t981 = 0;
        (void)_t981;
        I64 _t982 = I64_sub(_t981, result);
        (void)_t982;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t982; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t1005 = Str_lit("Str", 3ULL);
    (void)_t1005;
    U64 _t1006; { U64 *_hp = (U64 *)Str_size(); _t1006 = *_hp; free(_hp); }
    (void)_t1006;
    Vec *parts = Vec_new(_t1005, &(U64){_t1006});
    (void)parts;
    Str_delete(_t1005, &(Bool){1});
    ;
    U64 _t1007; { U64 *_hp = (U64 *)Str_len(delim); _t1007 = *_hp; free(_hp); }
    (void)_t1007;
    U64 _t1008 = 0;
    (void)_t1008;
    Bool _t1009 = U64_eq(_t1007, _t1008);
    (void)_t1009;
    ;
    ;
    if (_t1009) {
        Str *_t989 = Str_clone(self);
        (void)_t989;
        Vec_push(parts, _t989);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t999; { U64 *_hp = (U64 *)Str_len(self); _t999 = *_hp; free(_hp); }
        (void)_t999;
        U64 _t1000; { U64 *_hp = (U64 *)Str_len(delim); _t1000 = *_hp; free(_hp); }
        (void)_t1000;
        U64 _t1001 = U64_sub(_t999, _t1000);
        (void)_t1001;
        ;
        ;
        Bool _wcond990; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1001}); _wcond990 = *_hp; free(_hp); }
        (void)_wcond990;
        ;
        if (_wcond990) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1002; { U64 *_hp = (U64 *)Str_len(delim); _t1002 = *_hp; free(_hp); }
        (void)_t1002;
        Str *_t1003 = Str_substr(self, &(U64){pos}, &(U64){_t1002});
        (void)_t1003;
        ;
        Bool _t1004; { Bool *_hp = (Bool *)Str_eq(_t1003, delim); _t1004 = *_hp; free(_hp); }
        (void)_t1004;
        Str_delete(_t1003, &(Bool){1});
        if (_t1004) {
            U64 _t991 = U64_sub(pos, start);
            (void)_t991;
            Str *_t992 = Str_substr(self, &(U64){start}, &(U64){_t991});
            (void)_t992;
            ;
            Str *_t993 = Str_clone(_t992);
            (void)_t993;
            Str_delete(_t992, &(Bool){1});
            Vec_push(parts, _t993);
            U64 _t994; { U64 *_hp = (U64 *)Str_len(delim); _t994 = *_hp; free(_hp); }
            (void)_t994;
            U64 _t995 = U64_add(pos, _t994);
            (void)_t995;
            ;
            start = _t995;
            ;
            U64 _t996 = U64_clone(&(U64){start});
            (void)_t996;
            pos = _t996;
            ;
        } else {
            U64 _t997 = 1;
            (void)_t997;
            U64 _t998 = U64_add(pos, _t997);
            (void)_t998;
            ;
            pos = _t998;
            ;
        }
        ;
    }
    ;
    U64 _t1010; { U64 *_hp = (U64 *)Str_len(self); _t1010 = *_hp; free(_hp); }
    (void)_t1010;
    U64 _t1011 = U64_sub(_t1010, start);
    (void)_t1011;
    ;
    Str *_t1012 = Str_substr(self, &(U64){start}, &(U64){_t1011});
    (void)_t1012;
    ;
    ;
    Str *_t1013 = Str_clone(_t1012);
    (void)_t1013;
    Str_delete(_t1012, &(Bool){1});
    Vec_push(parts, _t1013);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1045 = malloc(DEREF(elem_size));
    (void)_t1045;
    U64 _t1046 = 0;
    (void)_t1046;
    I64 _t1047 = 1;
    (void)_t1047;
    U64 _t1048 = U64_clone(elem_size);
    (void)_t1048;
    Vec *_t1049 = malloc(sizeof(Vec));
    _t1049->data = _t1045;
    _t1049->count = _t1046;
    _t1049->cap = _t1047;
    _t1049->elem_size = _t1048;
    { Str *_ca = Str_clone(elem_type); _t1049->elem_type = *_ca; free(_ca); }
    (void)_t1049;
    ;
    ;
    ;
    return _t1049;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1054 = U64_eq(self->count, self->cap);
    (void)_t1054;
    if (_t1054) {
        U64 _t1050 = 2;
        (void)_t1050;
        U64 new_cap = U64_mul(self->cap, _t1050);
        (void)new_cap;
        ;
        U64 _t1051 = U64_mul(new_cap, self->elem_size);
        (void)_t1051;
        void *_t1052 = realloc(self->data, _t1051);
        (void)_t1052;
        ;
        self->data = _t1052;
        U64 _t1053 = U64_clone(&(U64){new_cap});
        (void)_t1053;
        ;
        self->cap = _t1053;
        ;
    }
    ;
    U64 *_t1055 = malloc(sizeof(U64)); *_t1055 = U64_mul(self->count, self->elem_size);
    (void)_t1055;
    void *_t1056 = ptr_add(self->data, DEREF(_t1055));
    (void)_t1056;
    memcpy(_t1056, val, self->elem_size);
    U64_delete(_t1055, &(Bool){1});
    free(val);
    U64 _t1057 = 1;
    (void)_t1057;
    U64 _t1058 = U64_add(self->count, _t1057);
    (void)_t1058;
    ;
    self->count = _t1058;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1073; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1073 = *_hp; free(_hp); }
    (void)_t1073;
    if (_t1073) {
        Str *_t1059 = Str_lit("Str", 3ULL);
        (void)_t1059;
        U64 _t1060; { U64 *_hp = (U64 *)Str_size(); _t1060 = *_hp; free(_hp); }
        (void)_t1060;
        U64 _t1061 = 5;
        (void)_t1061;
        Array *_va21 = Array_new(_t1059, &(U64){_t1060}, &(U64){_t1061});
        (void)_va21;
        Str_delete(_t1059, &(Bool){1});
        ;
        ;
        U64 _t1062 = 0;
        (void)_t1062;
        Str *_t1063 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1063;
        Array_set(_va21, &(U64){_t1062}, _t1063);
        ;
        U64 _t1064 = 1;
        (void)_t1064;
        Str *_t1065 = U64_to_str(DEREF(i));
        (void)_t1065;
        Array_set(_va21, &(U64){_t1064}, _t1065);
        ;
        U64 _t1066 = 2;
        (void)_t1066;
        Str *_t1067 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1067;
        Array_set(_va21, &(U64){_t1066}, _t1067);
        ;
        U64 _t1068 = 3;
        (void)_t1068;
        Str *_t1069 = U64_to_str(self->count);
        (void)_t1069;
        Array_set(_va21, &(U64){_t1068}, _t1069);
        ;
        U64 _t1070 = 4;
        (void)_t1070;
        Str *_t1071 = Str_lit(")", 1ULL);
        (void)_t1071;
        Array_set(_va21, &(U64){_t1070}, _t1071);
        ;
        Str *_t1072 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1072;
        panic(_t1072, _va21);
        Str_delete(_t1072, &(Bool){1});
    }
    ;
    U64 *_t1074 = malloc(sizeof(U64)); *_t1074 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1074;
    void *_t1075 = ptr_add(self->data, DEREF(_t1074));
    (void)_t1075;
    U64_delete(_t1074, &(Bool){1});
    return _t1075;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1086; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1086 = *_hp; free(_hp); }
    (void)_t1086;
    Bool _t1087 = Bool_not(_t1086);
    (void)_t1087;
    ;
    if (_t1087) {
        {
            U64 _t1084 = 0;
            (void)_t1084;
            Range *_fc1076 = Range_new(_t1084, self->count);
            (void)_fc1076;
            ;
            U64 _fi1076 = 0;
            (void)_fi1076;
            while (1) {
                U64 _t1078; { U64 *_hp = (U64 *)Range_len(_fc1076); _t1078 = *_hp; free(_hp); }
                (void)_t1078;
                Bool _wcond1077; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1076}, &(U64){_t1078}); _wcond1077 = *_hp; free(_hp); }
                (void)_wcond1077;
                ;
                if (_wcond1077) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1076, _fi1076); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1079 = 1;
                (void)_t1079;
                U64 _t1080 = U64_add(_fi1076, _t1079);
                (void)_t1080;
                ;
                _fi1076 = _t1080;
                ;
                U64 *_t1081 = malloc(sizeof(U64)); *_t1081 = U64_mul(i, self->elem_size);
                (void)_t1081;
                ;
                void *_t1082 = ptr_add(self->data, DEREF(_t1081));
                (void)_t1082;
                Bool _t1083 = 0;
                (void)_t1083;
                dyn_call_delete(&self->elem_type, _t1082, &(Bool){_t1083});
                U64_delete(_t1081, &(Bool){1});
                ;
            }
            Range_delete(_fc1076, &(Bool){1});
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1088; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1088 = *_hp; free(_hp); }
    (void)_t1088;
    Bool _t1089 = Bool_not(_t1088);
    (void)_t1089;
    ;
    if (_t1089) {
        Bool _t1085 = 0;
        (void)_t1085;
        Str_delete(&self->elem_type, &(Bool){_t1085});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1101 = U64_mul(self->cap, self->elem_size);
    (void)_t1101;
    U8 *new_data = malloc(_t1101);
    (void)new_data;
    ;
    Bool _t1102; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1102 = *_hp; free(_hp); }
    (void)_t1102;
    Bool _t1103 = Bool_not(_t1102);
    (void)_t1103;
    ;
    if (_t1103) {
        {
            U64 _t1099 = 0;
            (void)_t1099;
            Range *_fc1090 = Range_new(_t1099, self->count);
            (void)_fc1090;
            ;
            U64 _fi1090 = 0;
            (void)_fi1090;
            while (1) {
                U64 _t1092; { U64 *_hp = (U64 *)Range_len(_fc1090); _t1092 = *_hp; free(_hp); }
                (void)_t1092;
                Bool _wcond1091; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1090}, &(U64){_t1092}); _wcond1091 = *_hp; free(_hp); }
                (void)_wcond1091;
                ;
                if (_wcond1091) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1090, _fi1090); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1093 = 1;
                (void)_t1093;
                U64 _t1094 = U64_add(_fi1090, _t1093);
                (void)_t1094;
                ;
                _fi1090 = _t1094;
                ;
                U64 *_t1095 = malloc(sizeof(U64)); *_t1095 = U64_mul(i, self->elem_size);
                (void)_t1095;
                void *_t1096 = ptr_add(self->data, DEREF(_t1095));
                (void)_t1096;
                void *cloned = dyn_call_clone(&self->elem_type, _t1096);
                (void)cloned;
                U64_delete(_t1095, &(Bool){1});
                U64 *_t1097 = malloc(sizeof(U64)); *_t1097 = U64_mul(i, self->elem_size);
                (void)_t1097;
                ;
                void *_t1098 = ptr_add(new_data, DEREF(_t1097));
                (void)_t1098;
                memcpy(_t1098, cloned, self->elem_size);
                U64_delete(_t1097, &(Bool){1});
                free(cloned);
            }
            Range_delete(_fc1090, &(Bool){1});
            ;
        }
    } else {
        U64 _t1100 = U64_mul(self->count, self->elem_size);
        (void)_t1100;
        memcpy(new_data, self->data, _t1100);
        ;
    }
    ;
    Vec *_t1104 = malloc(sizeof(Vec));
    _t1104->data = new_data;
    _t1104->count = self->count;
    _t1104->cap = self->cap;
    _t1104->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1104->elem_type = *_ca; free(_ca); }
    (void)_t1104;
    return _t1104;
}

Tuple * Tuple_new(void) {
    U64 _t1106 = 8;
    (void)_t1106;
    Str *_t1107 = Str_lit("Str", 3ULL);
    (void)_t1107;
    U64 _t1108; { U64 *_hp = (U64 *)Str_size(); _t1108 = *_hp; free(_hp); }
    (void)_t1108;
    Str *_t1109 = Str_lit("U64", 3ULL);
    (void)_t1109;
    U64 _t1110; { U64 *_hp = (U64 *)U64_size(); _t1110 = *_hp; free(_hp); }
    (void)_t1110;
    void *_t1111 = malloc(_t1106);
    (void)_t1111;
    ;
    U64 _t1112 = 0;
    (void)_t1112;
    I64 _t1113 = 8;
    (void)_t1113;
    Tuple *_t1114 = malloc(sizeof(Tuple));
    _t1114->data = _t1111;
    _t1114->total_size = _t1112;
    _t1114->cap = _t1113;
    { Vec *_ca = Vec_new(_t1107, &(U64){_t1108}); _t1114->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1109, &(U64){_t1110}); _t1114->type_sizes = *_ca; free(_ca); }
    (void)_t1114;
    Str_delete(_t1107, &(Bool){1});
    ;
    Str_delete(_t1109, &(Bool){1});
    ;
    ;
    ;
    return _t1114;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1115; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1115 = *_hp; free(_hp); }
    (void)_t1115;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1115; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1122; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1122 = *_hp; free(_hp); }
    (void)_t1122;
    if (_t1122) {
        U64 _t1119 = 2;
        (void)_t1119;
        U64 new_cap = U64_mul(self->cap, _t1119);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1116; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1116 = *_hp; free(_hp); }
            (void)_wcond1116;
            if (_wcond1116) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1117 = 2;
            (void)_t1117;
            U64 _t1118 = U64_mul(new_cap, _t1117);
            (void)_t1118;
            ;
            new_cap = _t1118;
            ;
        }
        void *_t1120 = realloc(self->data, new_cap);
        (void)_t1120;
        self->data = _t1120;
        U64 _t1121 = U64_clone(&(U64){new_cap});
        (void)_t1121;
        ;
        self->cap = _t1121;
        ;
    }
    ;
    void *_t1123 = ptr_add(self->data, self->total_size);
    (void)_t1123;
    memcpy(_t1123, val, DEREF(elem_size));
    free(val);
    Str *_t1124 = Str_clone(elem_type);
    (void)_t1124;
    Vec_push(&self->type_names, _t1124);
    U64 _t1125 = U64_clone(elem_size);
    (void)_t1125;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1125; _oa; }));
    U64 _t1126 = U64_clone(&(U64){new_total});
    (void)_t1126;
    ;
    self->total_size = _t1126;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1149; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1149 = *_hp; free(_hp); }
    (void)_t1149;
    Bool _t1150; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1149}); _t1150 = *_hp; free(_hp); }
    (void)_t1150;
    ;
    if (_t1150) {
        Str *_t1127 = Str_lit("Str", 3ULL);
        (void)_t1127;
        U64 _t1128; { U64 *_hp = (U64 *)Str_size(); _t1128 = *_hp; free(_hp); }
        (void)_t1128;
        U64 _t1129 = 5;
        (void)_t1129;
        Array *_va22 = Array_new(_t1127, &(U64){_t1128}, &(U64){_t1129});
        (void)_va22;
        Str_delete(_t1127, &(Bool){1});
        ;
        ;
        U64 _t1130 = 0;
        (void)_t1130;
        Str *_t1131 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1131;
        Array_set(_va22, &(U64){_t1130}, _t1131);
        ;
        U64 _t1132 = 1;
        (void)_t1132;
        Str *_t1133 = U64_to_str(DEREF(i));
        (void)_t1133;
        Array_set(_va22, &(U64){_t1132}, _t1133);
        ;
        U64 _t1134 = 2;
        (void)_t1134;
        Str *_t1135 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1135;
        Array_set(_va22, &(U64){_t1134}, _t1135);
        ;
        U64 _t1136; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1136 = *_hp; free(_hp); }
        (void)_t1136;
        U64 _t1137 = 3;
        (void)_t1137;
        Str *_t1138 = U64_to_str(_t1136);
        (void)_t1138;
        ;
        Array_set(_va22, &(U64){_t1137}, _t1138);
        ;
        U64 _t1139 = 4;
        (void)_t1139;
        Str *_t1140 = Str_lit(")", 1ULL);
        (void)_t1140;
        Array_set(_va22, &(U64){_t1139}, _t1140);
        ;
        Str *_t1141 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1141;
        panic(_t1141, _va22);
        Str_delete(_t1141, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1148 = 0;
        (void)_t1148;
        Range *_fc1142 = Range_new(_t1148, DEREF(i));
        (void)_fc1142;
        ;
        U64 _fi1142 = 0;
        (void)_fi1142;
        while (1) {
            U64 _t1144; { U64 *_hp = (U64 *)Range_len(_fc1142); _t1144 = *_hp; free(_hp); }
            (void)_t1144;
            Bool _wcond1143; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1142}, &(U64){_t1144}); _wcond1143 = *_hp; free(_hp); }
            (void)_wcond1143;
            ;
            if (_wcond1143) {
            } else {
                ;
                break;
            }
            ;
            U64 *j = Range_get(_fc1142, _fi1142);
            (void)j;
            U64 _t1145 = 1;
            (void)_t1145;
            U64 _t1146 = U64_add(_fi1142, _t1145);
            (void)_t1146;
            ;
            _fi1142 = _t1146;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1147 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1147;
            U64_delete(j, &(Bool){1});
            *offset = _t1147;
            ;
        }
        Range_delete(_fc1142, &(Bool){1});
        ;
    }
    void *_t1151 = ptr_add(self->data, DEREF(offset));
    (void)_t1151;
    U64_delete(offset, &(Bool){1});
    return _t1151;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1152 = Vec_get(&self->type_names, i);
    (void)_t1152;
    return _t1152;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1153 = Vec_get(&self->type_sizes, i);
    (void)_t1153;
    return _t1153;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1162 = 0;
        (void)_t1162;
        U64 _t1163; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1163 = *_hp; free(_hp); }
        (void)_t1163;
        Range *_fc1154 = Range_new(_t1162, _t1163);
        (void)_fc1154;
        ;
        ;
        U64 _fi1154 = 0;
        (void)_fi1154;
        while (1) {
            U64 _t1156; { U64 *_hp = (U64 *)Range_len(_fc1154); _t1156 = *_hp; free(_hp); }
            (void)_t1156;
            Bool _wcond1155; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1154}, &(U64){_t1156}); _wcond1155 = *_hp; free(_hp); }
            (void)_wcond1155;
            ;
            if (_wcond1155) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1154, _fi1154);
            (void)i;
            U64 _t1157 = 1;
            (void)_t1157;
            U64 _t1158 = U64_add(_fi1154, _t1157);
            (void)_t1158;
            ;
            _fi1154 = _t1158;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1159 = ptr_add(self->data, DEREF(offset));
            (void)_t1159;
            Bool _t1160 = 0;
            (void)_t1160;
            dyn_call_delete(tn, _t1159, &(Bool){_t1160});
            ;
            U64 _t1161 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1161;
            U64_delete(i, &(Bool){1});
            *offset = _t1161;
            ;
        }
        Range_delete(_fc1154, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1164 = 0;
    (void)_t1164;
    Vec_delete(&self->type_names, &(Bool){_t1164});
    ;
    Bool _t1165 = 0;
    (void)_t1165;
    Vec_delete(&self->type_sizes, &(Bool){_t1165});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1178 = 0;
    (void)_t1178;
    Bool _t1179 = U64_eq(new_cap, _t1178);
    (void)_t1179;
    ;
    if (_t1179) {
        I64 _t1166 = 8;
        (void)_t1166;
        U64 _t1167; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1166}); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        new_cap = _t1167;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _t1176 = 0;
        (void)_t1176;
        U64 _t1177; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1177 = *_hp; free(_hp); }
        (void)_t1177;
        Range *_fc1168 = Range_new(_t1176, _t1177);
        (void)_fc1168;
        ;
        ;
        U64 _fi1168 = 0;
        (void)_fi1168;
        while (1) {
            U64 _t1170; { U64 *_hp = (U64 *)Range_len(_fc1168); _t1170 = *_hp; free(_hp); }
            (void)_t1170;
            Bool _wcond1169; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1168}, &(U64){_t1170}); _wcond1169 = *_hp; free(_hp); }
            (void)_wcond1169;
            ;
            if (_wcond1169) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1168, _fi1168);
            (void)i;
            U64 _t1171 = 1;
            (void)_t1171;
            U64 _t1172 = U64_add(_fi1168, _t1171);
            (void)_t1172;
            ;
            _fi1168 = _t1172;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1173 = ptr_add(self->data, DEREF(offset));
            (void)_t1173;
            void *cloned = dyn_call_clone(tn, _t1173);
            (void)cloned;
            void *_t1174 = ptr_add(new_data, DEREF(offset));
            (void)_t1174;
            memcpy(_t1174, cloned, DEREF(ts));
            free(cloned);
            U64 _t1175 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1175;
            U64_delete(i, &(Bool){1});
            *offset = _t1175;
            ;
        }
        Range_delete(_fc1168, &(Bool){1});
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1180 = U64_clone(&(U64){new_cap});
    (void)_t1180;
    ;
    Vec *_t1181 = Vec_clone(&self->type_names);
    (void)_t1181;
    Vec *_t1182 = Vec_clone(&self->type_sizes);
    (void)_t1182;
    Tuple *_t1183 = malloc(sizeof(Tuple));
    _t1183->data = new_data;
    _t1183->total_size = self->total_size;
    _t1183->cap = _t1180;
    { Vec *_ca = Vec_clone(_t1181); _t1183->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1182); _t1183->type_sizes = *_ca; free(_ca); }
    (void)_t1183;
    ;
    Vec_delete(_t1181, &(Bool){1});
    Vec_delete(_t1182, &(Bool){1});
    return _t1183;
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
    Bool _t1202; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1185; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t1185 = *_hp; free(_hp); }
        (void)_t1185;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1185; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TilType_is_None(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1186; { Bool *_hp = (Bool *)TilType_is_None(other); _t1186 = *_hp; free(_hp); }
        (void)_t1186;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1186; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TilType_is_I64(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1187; { Bool *_hp = (Bool *)TilType_is_I64(other); _t1187 = *_hp; free(_hp); }
        (void)_t1187;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1187; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TilType_is_U8(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1188; { Bool *_hp = (Bool *)TilType_is_U8(other); _t1188 = *_hp; free(_hp); }
        (void)_t1188;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1188; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TilType_is_I16(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1189; { Bool *_hp = (Bool *)TilType_is_I16(other); _t1189 = *_hp; free(_hp); }
        (void)_t1189;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1189; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TilType_is_I32(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1190; { Bool *_hp = (Bool *)TilType_is_I32(other); _t1190 = *_hp; free(_hp); }
        (void)_t1190;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1190; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TilType_is_U32(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1191; { Bool *_hp = (Bool *)TilType_is_U32(other); _t1191 = *_hp; free(_hp); }
        (void)_t1191;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1191; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TilType_is_U64(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1192; { Bool *_hp = (Bool *)TilType_is_U64(other); _t1192 = *_hp; free(_hp); }
        (void)_t1192;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1192; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TilType_is_F32(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1193; { Bool *_hp = (Bool *)TilType_is_F32(other); _t1193 = *_hp; free(_hp); }
        (void)_t1193;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1193; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1194; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t1194 = *_hp; free(_hp); }
        (void)_t1194;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1194; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1195; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t1195 = *_hp; free(_hp); }
        (void)_t1195;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1195; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1196; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t1196 = *_hp; free(_hp); }
        (void)_t1196;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1196; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1197; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t1197 = *_hp; free(_hp); }
        (void)_t1197;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1197; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1198; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t1198 = *_hp; free(_hp); }
        (void)_t1198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1198; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1199; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t1199 = *_hp; free(_hp); }
        (void)_t1199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1199; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1200; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t1200 = *_hp; free(_hp); }
        (void)_t1200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1200; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t1218 = *_hp; free(_hp); }
    (void)_t1218;
    if (_t1218) {
        Bool _t1201; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t1201 = *_hp; free(_hp); }
        (void)_t1201;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1201; return _r; }
    }
    ;
    Bool _t1219 = 0;
    (void)_t1219;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1219; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t1220; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        ;
        return TilType_None();
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
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
    Bool _t1253; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        Str *_t1236 = Str_lit("Unknown", 7ULL);
        (void)_t1236;
        ;
        return _t1236;
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        Str *_t1237 = Str_lit("None", 4ULL);
        (void)_t1237;
        ;
        return _t1237;
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        Str *_t1238 = Str_lit("I64", 3ULL);
        (void)_t1238;
        ;
        return _t1238;
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        Str *_t1239 = Str_lit("U8", 2ULL);
        (void)_t1239;
        ;
        return _t1239;
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        Str *_t1240 = Str_lit("I16", 3ULL);
        (void)_t1240;
        ;
        return _t1240;
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        Str *_t1241 = Str_lit("I32", 3ULL);
        (void)_t1241;
        ;
        return _t1241;
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        Str *_t1242 = Str_lit("U32", 3ULL);
        (void)_t1242;
        ;
        return _t1242;
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        Str *_t1243 = Str_lit("U64", 3ULL);
        (void)_t1243;
        ;
        return _t1243;
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        Str *_t1244 = Str_lit("F32", 3ULL);
        (void)_t1244;
        ;
        return _t1244;
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        Str *_t1245 = Str_lit("Bool", 4ULL);
        (void)_t1245;
        ;
        return _t1245;
    }
    ;
    Bool _t1263; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1263 = *_hp; free(_hp); }
    (void)_t1263;
    if (_t1263) {
        Str *_t1246 = Str_lit("Struct", 6ULL);
        (void)_t1246;
        ;
        return _t1246;
    }
    ;
    Bool _t1264; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        Str *_t1247 = Str_lit("StructDef", 9ULL);
        (void)_t1247;
        ;
        return _t1247;
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        Str *_t1248 = Str_lit("Enum", 4ULL);
        (void)_t1248;
        ;
        return _t1248;
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        Str *_t1249 = Str_lit("EnumDef", 7ULL);
        (void)_t1249;
        ;
        return _t1249;
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        Str *_t1250 = Str_lit("FuncDef", 7ULL);
        (void)_t1250;
        ;
        return _t1250;
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        Str *_t1251 = Str_lit("FuncPtr", 7ULL);
        (void)_t1251;
        ;
        return _t1251;
    }
    ;
    Bool _t1269; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t1269 = *_hp; free(_hp); }
    (void)_t1269;
    if (_t1269) {
        Str *_t1252 = Str_lit("Dynamic", 7ULL);
        (void)_t1252;
        ;
        return _t1252;
    }
    ;
    Str *_t1270 = Str_lit("unknown", 7ULL);
    (void)_t1270;
    return _t1270;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t1308; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t1308 = *_hp; free(_hp); }
    (void)_t1308;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1308; return _r; }
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
    Bool _t1331; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Bool _t1325; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t1325 = *_hp; free(_hp); }
        (void)_t1325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1325; return _r; }
    }
    ;
    Bool _t1332; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1326; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t1326 = *_hp; free(_hp); }
        (void)_t1326;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1326; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1327; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t1327 = *_hp; free(_hp); }
        (void)_t1327;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1327; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1328; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t1328 = *_hp; free(_hp); }
        (void)_t1328;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1328; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1329; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t1329 = *_hp; free(_hp); }
        (void)_t1329;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1329; return _r; }
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Bool _t1330; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t1330 = *_hp; free(_hp); }
        (void)_t1330;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1330; return _r; }
    }
    ;
    Bool _t1337 = 0;
    (void)_t1337;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1337; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t1338; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t1341; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1341 = *_hp; free(_hp); }
    (void)_t1341;
    if (_t1341) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t1342; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1342 = *_hp; free(_hp); }
    (void)_t1342;
    if (_t1342) {
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
    Bool _t1349; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        Str *_t1343 = Str_lit("Func", 4ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        Str *_t1344 = Str_lit("Proc", 4ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        Str *_t1345 = Str_lit("Test", 4ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        Str *_t1346 = Str_lit("Macro", 5ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        Str *_t1347 = Str_lit("ExtFunc", 7ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Bool _t1354; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t1354 = *_hp; free(_hp); }
    (void)_t1354;
    if (_t1354) {
        Str *_t1348 = Str_lit("ExtProc", 7ULL);
        (void)_t1348;
        ;
        return _t1348;
    }
    ;
    Str *_t1355 = Str_lit("unknown", 7ULL);
    (void)_t1355;
    return _t1355;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t1367; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1367; return _r; }
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
    Bool _t1464; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1464 = *_hp; free(_hp); }
    (void)_t1464;
    if (_t1464) {
        Bool _t1384; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t1384 = *_hp; free(_hp); }
        (void)_t1384;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1384; return _r; }
    }
    ;
    Bool _t1465; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1465 = *_hp; free(_hp); }
    (void)_t1465;
    if (_t1465) {
        Bool _t1386; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t1386 = *_hp; free(_hp); }
        (void)_t1386;
        Bool _t1387 = Bool_not(_t1386);
        (void)_t1387;
        ;
        if (_t1387) {
            Bool _t1385 = 0;
            (void)_t1385;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1385; return _r; }
        }
        ;
        Str *_t1388 = ExprData_get_LiteralStr(self);
        (void)_t1388;
        Str *_t1389 = ExprData_get_LiteralStr(other);
        (void)_t1389;
        Bool _t1390; { Bool *_hp = (Bool *)Str_eq(_t1388, _t1389); _t1390 = *_hp; free(_hp); }
        (void)_t1390;
        Str_delete(_t1388, &(Bool){1});
        Str_delete(_t1389, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1390; return _r; }
    }
    ;
    Bool _t1466; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1466 = *_hp; free(_hp); }
    (void)_t1466;
    if (_t1466) {
        Bool _t1392; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t1392 = *_hp; free(_hp); }
        (void)_t1392;
        Bool _t1393 = Bool_not(_t1392);
        (void)_t1393;
        ;
        if (_t1393) {
            Bool _t1391 = 0;
            (void)_t1391;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1391; return _r; }
        }
        ;
        Str *_t1394 = ExprData_get_LiteralNum(self);
        (void)_t1394;
        Str *_t1395 = ExprData_get_LiteralNum(other);
        (void)_t1395;
        Bool _t1396; { Bool *_hp = (Bool *)Str_eq(_t1394, _t1395); _t1396 = *_hp; free(_hp); }
        (void)_t1396;
        Str_delete(_t1394, &(Bool){1});
        Str_delete(_t1395, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1396; return _r; }
    }
    ;
    Bool _t1467; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1467 = *_hp; free(_hp); }
    (void)_t1467;
    if (_t1467) {
        Bool _t1398; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t1398 = *_hp; free(_hp); }
        (void)_t1398;
        Bool _t1399 = Bool_not(_t1398);
        (void)_t1399;
        ;
        if (_t1399) {
            Bool _t1397 = 0;
            (void)_t1397;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1397; return _r; }
        }
        ;
        Str *_t1400 = ExprData_get_LiteralBool(self);
        (void)_t1400;
        Str *_t1401 = ExprData_get_LiteralBool(other);
        (void)_t1401;
        Bool _t1402; { Bool *_hp = (Bool *)Str_eq(_t1400, _t1401); _t1402 = *_hp; free(_hp); }
        (void)_t1402;
        Str_delete(_t1400, &(Bool){1});
        Str_delete(_t1401, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1402; return _r; }
    }
    ;
    Bool _t1468; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1468 = *_hp; free(_hp); }
    (void)_t1468;
    if (_t1468) {
        Bool _t1403; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t1403 = *_hp; free(_hp); }
        (void)_t1403;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1403; return _r; }
    }
    ;
    Bool _t1469; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1469 = *_hp; free(_hp); }
    (void)_t1469;
    if (_t1469) {
        Bool _t1405; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t1405 = *_hp; free(_hp); }
        (void)_t1405;
        Bool _t1406 = Bool_not(_t1405);
        (void)_t1406;
        ;
        if (_t1406) {
            Bool _t1404 = 0;
            (void)_t1404;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1404; return _r; }
        }
        ;
        Str *_t1407 = ExprData_get_Ident(self);
        (void)_t1407;
        Str *_t1408 = ExprData_get_Ident(other);
        (void)_t1408;
        Bool _t1409; { Bool *_hp = (Bool *)Str_eq(_t1407, _t1408); _t1409 = *_hp; free(_hp); }
        (void)_t1409;
        Str_delete(_t1407, &(Bool){1});
        Str_delete(_t1408, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1409; return _r; }
    }
    ;
    Bool _t1470; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1470 = *_hp; free(_hp); }
    (void)_t1470;
    if (_t1470) {
        Bool _t1411; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t1411 = *_hp; free(_hp); }
        (void)_t1411;
        Bool _t1412 = Bool_not(_t1411);
        (void)_t1412;
        ;
        if (_t1412) {
            Bool _t1410 = 0;
            (void)_t1410;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1410; return _r; }
        }
        ;
        Declaration *_t1413 = ExprData_get_Decl(self);
        (void)_t1413;
        Declaration *_t1414 = ExprData_get_Decl(other);
        (void)_t1414;
        Bool _t1415; { Bool *_hp = (Bool *)Declaration_eq(_t1413, _t1414); _t1415 = *_hp; free(_hp); }
        (void)_t1415;
        Declaration_delete(_t1413, &(Bool){1});
        Declaration_delete(_t1414, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1415; return _r; }
    }
    ;
    Bool _t1471; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1471 = *_hp; free(_hp); }
    (void)_t1471;
    if (_t1471) {
        Bool _t1417; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t1417 = *_hp; free(_hp); }
        (void)_t1417;
        Bool _t1418 = Bool_not(_t1417);
        (void)_t1418;
        ;
        if (_t1418) {
            Bool _t1416 = 0;
            (void)_t1416;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1416; return _r; }
        }
        ;
        Str *_t1419 = ExprData_get_Assign(self);
        (void)_t1419;
        Str *_t1420 = ExprData_get_Assign(other);
        (void)_t1420;
        Bool _t1421; { Bool *_hp = (Bool *)Str_eq(_t1419, _t1420); _t1421 = *_hp; free(_hp); }
        (void)_t1421;
        Str_delete(_t1419, &(Bool){1});
        Str_delete(_t1420, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1421; return _r; }
    }
    ;
    Bool _t1472; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1472 = *_hp; free(_hp); }
    (void)_t1472;
    if (_t1472) {
        Bool _t1422; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t1422 = *_hp; free(_hp); }
        (void)_t1422;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1422; return _r; }
    }
    ;
    Bool _t1473; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1473 = *_hp; free(_hp); }
    (void)_t1473;
    if (_t1473) {
        Bool _t1424; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t1424 = *_hp; free(_hp); }
        (void)_t1424;
        Bool _t1425 = Bool_not(_t1424);
        (void)_t1425;
        ;
        if (_t1425) {
            Bool _t1423 = 0;
            (void)_t1423;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1423; return _r; }
        }
        ;
        FunctionDef *_t1426 = ExprData_get_FuncDef(self);
        (void)_t1426;
        FunctionDef *_t1427 = ExprData_get_FuncDef(other);
        (void)_t1427;
        Bool _t1428; { Bool *_hp = (Bool *)FunctionDef_eq(_t1426, _t1427); _t1428 = *_hp; free(_hp); }
        (void)_t1428;
        FunctionDef_delete(_t1426, &(Bool){1});
        FunctionDef_delete(_t1427, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1428; return _r; }
    }
    ;
    Bool _t1474; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1474 = *_hp; free(_hp); }
    (void)_t1474;
    if (_t1474) {
        Bool _t1429; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t1429 = *_hp; free(_hp); }
        (void)_t1429;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1429; return _r; }
    }
    ;
    Bool _t1475; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1475 = *_hp; free(_hp); }
    (void)_t1475;
    if (_t1475) {
        Bool _t1430; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t1430 = *_hp; free(_hp); }
        (void)_t1430;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1430; return _r; }
    }
    ;
    Bool _t1476; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1476 = *_hp; free(_hp); }
    (void)_t1476;
    if (_t1476) {
        Bool _t1432; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t1432 = *_hp; free(_hp); }
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
        Str *_t1434 = ExprData_get_FieldAccess(self);
        (void)_t1434;
        Str *_t1435 = ExprData_get_FieldAccess(other);
        (void)_t1435;
        Bool _t1436; { Bool *_hp = (Bool *)Str_eq(_t1434, _t1435); _t1436 = *_hp; free(_hp); }
        (void)_t1436;
        Str_delete(_t1434, &(Bool){1});
        Str_delete(_t1435, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1436; return _r; }
    }
    ;
    Bool _t1477; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1477 = *_hp; free(_hp); }
    (void)_t1477;
    if (_t1477) {
        Bool _t1438; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t1438 = *_hp; free(_hp); }
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
        Str *_t1440 = ExprData_get_FieldAssign(self);
        (void)_t1440;
        Str *_t1441 = ExprData_get_FieldAssign(other);
        (void)_t1441;
        Bool _t1442; { Bool *_hp = (Bool *)Str_eq(_t1440, _t1441); _t1442 = *_hp; free(_hp); }
        (void)_t1442;
        Str_delete(_t1440, &(Bool){1});
        Str_delete(_t1441, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1442; return _r; }
    }
    ;
    Bool _t1478; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1478 = *_hp; free(_hp); }
    (void)_t1478;
    if (_t1478) {
        Bool _t1443; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t1443 = *_hp; free(_hp); }
        (void)_t1443;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1443; return _r; }
    }
    ;
    Bool _t1479; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1479 = *_hp; free(_hp); }
    (void)_t1479;
    if (_t1479) {
        Bool _t1444; { Bool *_hp = (Bool *)ExprData_is_If(other); _t1444 = *_hp; free(_hp); }
        (void)_t1444;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1444; return _r; }
    }
    ;
    Bool _t1480; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1480 = *_hp; free(_hp); }
    (void)_t1480;
    if (_t1480) {
        Bool _t1445; { Bool *_hp = (Bool *)ExprData_is_While(other); _t1445 = *_hp; free(_hp); }
        (void)_t1445;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1445; return _r; }
    }
    ;
    Bool _t1481; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1481 = *_hp; free(_hp); }
    (void)_t1481;
    if (_t1481) {
        Bool _t1447; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t1447 = *_hp; free(_hp); }
        (void)_t1447;
        Bool _t1448 = Bool_not(_t1447);
        (void)_t1448;
        ;
        if (_t1448) {
            Bool _t1446 = 0;
            (void)_t1446;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1446; return _r; }
        }
        ;
        Str *_t1449 = ExprData_get_ForIn(self);
        (void)_t1449;
        Str *_t1450 = ExprData_get_ForIn(other);
        (void)_t1450;
        Bool _t1451; { Bool *_hp = (Bool *)Str_eq(_t1449, _t1450); _t1451 = *_hp; free(_hp); }
        (void)_t1451;
        Str_delete(_t1449, &(Bool){1});
        Str_delete(_t1450, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1451; return _r; }
    }
    ;
    Bool _t1482; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1482 = *_hp; free(_hp); }
    (void)_t1482;
    if (_t1482) {
        Bool _t1453; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t1453 = *_hp; free(_hp); }
        (void)_t1453;
        Bool _t1454 = Bool_not(_t1453);
        (void)_t1454;
        ;
        if (_t1454) {
            Bool _t1452 = 0;
            (void)_t1452;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1452; return _r; }
        }
        ;
        Str *_t1455 = ExprData_get_NamedArg(self);
        (void)_t1455;
        Str *_t1456 = ExprData_get_NamedArg(other);
        (void)_t1456;
        Bool _t1457; { Bool *_hp = (Bool *)Str_eq(_t1455, _t1456); _t1457 = *_hp; free(_hp); }
        (void)_t1457;
        Str_delete(_t1455, &(Bool){1});
        Str_delete(_t1456, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1457; return _r; }
    }
    ;
    Bool _t1483; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1483 = *_hp; free(_hp); }
    (void)_t1483;
    if (_t1483) {
        Bool _t1458; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t1458 = *_hp; free(_hp); }
        (void)_t1458;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1458; return _r; }
    }
    ;
    Bool _t1484; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1484 = *_hp; free(_hp); }
    (void)_t1484;
    if (_t1484) {
        Bool _t1459; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t1459 = *_hp; free(_hp); }
        (void)_t1459;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1459; return _r; }
    }
    ;
    Bool _t1485; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1485 = *_hp; free(_hp); }
    (void)_t1485;
    if (_t1485) {
        Bool _t1460; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t1460 = *_hp; free(_hp); }
        (void)_t1460;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1460; return _r; }
    }
    ;
    Bool _t1486; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1486 = *_hp; free(_hp); }
    (void)_t1486;
    if (_t1486) {
        Bool _t1461; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t1461 = *_hp; free(_hp); }
        (void)_t1461;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1461; return _r; }
    }
    ;
    Bool _t1487; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1487 = *_hp; free(_hp); }
    (void)_t1487;
    if (_t1487) {
        Bool _t1462; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t1462 = *_hp; free(_hp); }
        (void)_t1462;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1462; return _r; }
    }
    ;
    Bool _t1488; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1488 = *_hp; free(_hp); }
    (void)_t1488;
    if (_t1488) {
        Bool _t1463; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t1463 = *_hp; free(_hp); }
        (void)_t1463;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1463; return _r; }
    }
    ;
    Bool _t1489 = 0;
    (void)_t1489;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1489; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t1512; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1512 = *_hp; free(_hp); }
    (void)_t1512;
    if (_t1512) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t1513; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1513 = *_hp; free(_hp); }
    (void)_t1513;
    if (_t1513) {
        Str *_t1490 = ExprData_get_LiteralStr(self);
        (void)_t1490;
        ExprData *_t1491 = ExprData_LiteralStr(_t1490);
        (void)_t1491;
        Str_delete(_t1490, &(Bool){1});
        ;
        return _t1491;
    }
    ;
    Bool _t1514; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1514 = *_hp; free(_hp); }
    (void)_t1514;
    if (_t1514) {
        Str *_t1492 = ExprData_get_LiteralNum(self);
        (void)_t1492;
        ExprData *_t1493 = ExprData_LiteralNum(_t1492);
        (void)_t1493;
        Str_delete(_t1492, &(Bool){1});
        ;
        return _t1493;
    }
    ;
    Bool _t1515; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1515 = *_hp; free(_hp); }
    (void)_t1515;
    if (_t1515) {
        Str *_t1494 = ExprData_get_LiteralBool(self);
        (void)_t1494;
        ExprData *_t1495 = ExprData_LiteralBool(_t1494);
        (void)_t1495;
        Str_delete(_t1494, &(Bool){1});
        ;
        return _t1495;
    }
    ;
    Bool _t1516; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1516 = *_hp; free(_hp); }
    (void)_t1516;
    if (_t1516) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t1517; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1517 = *_hp; free(_hp); }
    (void)_t1517;
    if (_t1517) {
        Str *_t1496 = ExprData_get_Ident(self);
        (void)_t1496;
        ExprData *_t1497 = ExprData_Ident(_t1496);
        (void)_t1497;
        Str_delete(_t1496, &(Bool){1});
        ;
        return _t1497;
    }
    ;
    Bool _t1518; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1518 = *_hp; free(_hp); }
    (void)_t1518;
    if (_t1518) {
        Declaration *_t1498 = ExprData_get_Decl(self);
        (void)_t1498;
        ExprData *_t1499 = ExprData_Decl(_t1498);
        (void)_t1499;
        Declaration_delete(_t1498, &(Bool){1});
        ;
        return _t1499;
    }
    ;
    Bool _t1519; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1519 = *_hp; free(_hp); }
    (void)_t1519;
    if (_t1519) {
        Str *_t1500 = ExprData_get_Assign(self);
        (void)_t1500;
        ExprData *_t1501 = ExprData_Assign(_t1500);
        (void)_t1501;
        Str_delete(_t1500, &(Bool){1});
        ;
        return _t1501;
    }
    ;
    Bool _t1520; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1520 = *_hp; free(_hp); }
    (void)_t1520;
    if (_t1520) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t1521; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1521 = *_hp; free(_hp); }
    (void)_t1521;
    if (_t1521) {
        FunctionDef *_t1502 = ExprData_get_FuncDef(self);
        (void)_t1502;
        ExprData *_t1503 = ExprData_FuncDef(_t1502);
        (void)_t1503;
        FunctionDef_delete(_t1502, &(Bool){1});
        ;
        return _t1503;
    }
    ;
    Bool _t1522; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1522 = *_hp; free(_hp); }
    (void)_t1522;
    if (_t1522) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t1523; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1523 = *_hp; free(_hp); }
    (void)_t1523;
    if (_t1523) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t1524; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1524 = *_hp; free(_hp); }
    (void)_t1524;
    if (_t1524) {
        Str *_t1504 = ExprData_get_FieldAccess(self);
        (void)_t1504;
        ExprData *_t1505 = ExprData_FieldAccess(_t1504);
        (void)_t1505;
        Str_delete(_t1504, &(Bool){1});
        ;
        return _t1505;
    }
    ;
    Bool _t1525; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1525 = *_hp; free(_hp); }
    (void)_t1525;
    if (_t1525) {
        Str *_t1506 = ExprData_get_FieldAssign(self);
        (void)_t1506;
        ExprData *_t1507 = ExprData_FieldAssign(_t1506);
        (void)_t1507;
        Str_delete(_t1506, &(Bool){1});
        ;
        return _t1507;
    }
    ;
    Bool _t1526; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1526 = *_hp; free(_hp); }
    (void)_t1526;
    if (_t1526) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t1527; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Str *_t1508 = ExprData_get_ForIn(self);
        (void)_t1508;
        ExprData *_t1509 = ExprData_ForIn(_t1508);
        (void)_t1509;
        Str_delete(_t1508, &(Bool){1});
        ;
        return _t1509;
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Str *_t1510 = ExprData_get_NamedArg(self);
        (void)_t1510;
        ExprData *_t1511 = ExprData_NamedArg(_t1510);
        (void)_t1511;
        Str_delete(_t1510, &(Bool){1});
        ;
        return _t1511;
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
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
    Bool _t1671; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1671 = *_hp; free(_hp); }
    (void)_t1671;
    if (_t1671) {
        Str *_t1536 = Str_lit("Body", 4ULL);
        (void)_t1536;
        ;
        return _t1536;
    }
    ;
    Bool _t1672; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1672 = *_hp; free(_hp); }
    (void)_t1672;
    if (_t1672) {
        Str *_t1537 = Str_lit("Str", 3ULL);
        (void)_t1537;
        U64 _t1538; { U64 *_hp = (U64 *)Str_size(); _t1538 = *_hp; free(_hp); }
        (void)_t1538;
        U64 _t1539 = 3;
        (void)_t1539;
        Array *_va23 = Array_new(_t1537, &(U64){_t1538}, &(U64){_t1539});
        (void)_va23;
        Str_delete(_t1537, &(Bool){1});
        ;
        ;
        U64 _t1540 = 0;
        (void)_t1540;
        Str *_t1541 = Str_lit("LiteralStr(", 11ULL);
        (void)_t1541;
        Array_set(_va23, &(U64){_t1540}, _t1541);
        ;
        Str *_t1542 = ExprData_get_LiteralStr(self);
        (void)_t1542;
        U64 _t1543 = 1;
        (void)_t1543;
        Str *_t1544 = Str_to_str(_t1542);
        (void)_t1544;
        Str_delete(_t1542, &(Bool){1});
        Array_set(_va23, &(U64){_t1543}, _t1544);
        ;
        U64 _t1545 = 2;
        (void)_t1545;
        Str *_t1546 = Str_lit(")", 1ULL);
        (void)_t1546;
        Array_set(_va23, &(U64){_t1545}, _t1546);
        ;
        Str *_t1547 = format(_va23);
        (void)_t1547;
        ;
        return _t1547;
    }
    ;
    Bool _t1673; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1673 = *_hp; free(_hp); }
    (void)_t1673;
    if (_t1673) {
        Str *_t1548 = Str_lit("Str", 3ULL);
        (void)_t1548;
        U64 _t1549; { U64 *_hp = (U64 *)Str_size(); _t1549 = *_hp; free(_hp); }
        (void)_t1549;
        U64 _t1550 = 3;
        (void)_t1550;
        Array *_va24 = Array_new(_t1548, &(U64){_t1549}, &(U64){_t1550});
        (void)_va24;
        Str_delete(_t1548, &(Bool){1});
        ;
        ;
        U64 _t1551 = 0;
        (void)_t1551;
        Str *_t1552 = Str_lit("LiteralNum(", 11ULL);
        (void)_t1552;
        Array_set(_va24, &(U64){_t1551}, _t1552);
        ;
        Str *_t1553 = ExprData_get_LiteralNum(self);
        (void)_t1553;
        U64 _t1554 = 1;
        (void)_t1554;
        Str *_t1555 = Str_to_str(_t1553);
        (void)_t1555;
        Str_delete(_t1553, &(Bool){1});
        Array_set(_va24, &(U64){_t1554}, _t1555);
        ;
        U64 _t1556 = 2;
        (void)_t1556;
        Str *_t1557 = Str_lit(")", 1ULL);
        (void)_t1557;
        Array_set(_va24, &(U64){_t1556}, _t1557);
        ;
        Str *_t1558 = format(_va24);
        (void)_t1558;
        ;
        return _t1558;
    }
    ;
    Bool _t1674; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1674 = *_hp; free(_hp); }
    (void)_t1674;
    if (_t1674) {
        Str *_t1559 = Str_lit("Str", 3ULL);
        (void)_t1559;
        U64 _t1560; { U64 *_hp = (U64 *)Str_size(); _t1560 = *_hp; free(_hp); }
        (void)_t1560;
        U64 _t1561 = 3;
        (void)_t1561;
        Array *_va25 = Array_new(_t1559, &(U64){_t1560}, &(U64){_t1561});
        (void)_va25;
        Str_delete(_t1559, &(Bool){1});
        ;
        ;
        U64 _t1562 = 0;
        (void)_t1562;
        Str *_t1563 = Str_lit("LiteralBool(", 12ULL);
        (void)_t1563;
        Array_set(_va25, &(U64){_t1562}, _t1563);
        ;
        Str *_t1564 = ExprData_get_LiteralBool(self);
        (void)_t1564;
        U64 _t1565 = 1;
        (void)_t1565;
        Str *_t1566 = Str_to_str(_t1564);
        (void)_t1566;
        Str_delete(_t1564, &(Bool){1});
        Array_set(_va25, &(U64){_t1565}, _t1566);
        ;
        U64 _t1567 = 2;
        (void)_t1567;
        Str *_t1568 = Str_lit(")", 1ULL);
        (void)_t1568;
        Array_set(_va25, &(U64){_t1567}, _t1568);
        ;
        Str *_t1569 = format(_va25);
        (void)_t1569;
        ;
        return _t1569;
    }
    ;
    Bool _t1675; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1675 = *_hp; free(_hp); }
    (void)_t1675;
    if (_t1675) {
        Str *_t1570 = Str_lit("LiteralNull", 11ULL);
        (void)_t1570;
        ;
        return _t1570;
    }
    ;
    Bool _t1676; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1676 = *_hp; free(_hp); }
    (void)_t1676;
    if (_t1676) {
        Str *_t1571 = Str_lit("Str", 3ULL);
        (void)_t1571;
        U64 _t1572; { U64 *_hp = (U64 *)Str_size(); _t1572 = *_hp; free(_hp); }
        (void)_t1572;
        U64 _t1573 = 3;
        (void)_t1573;
        Array *_va26 = Array_new(_t1571, &(U64){_t1572}, &(U64){_t1573});
        (void)_va26;
        Str_delete(_t1571, &(Bool){1});
        ;
        ;
        U64 _t1574 = 0;
        (void)_t1574;
        Str *_t1575 = Str_lit("Ident(", 6ULL);
        (void)_t1575;
        Array_set(_va26, &(U64){_t1574}, _t1575);
        ;
        Str *_t1576 = ExprData_get_Ident(self);
        (void)_t1576;
        U64 _t1577 = 1;
        (void)_t1577;
        Str *_t1578 = Str_to_str(_t1576);
        (void)_t1578;
        Str_delete(_t1576, &(Bool){1});
        Array_set(_va26, &(U64){_t1577}, _t1578);
        ;
        U64 _t1579 = 2;
        (void)_t1579;
        Str *_t1580 = Str_lit(")", 1ULL);
        (void)_t1580;
        Array_set(_va26, &(U64){_t1579}, _t1580);
        ;
        Str *_t1581 = format(_va26);
        (void)_t1581;
        ;
        return _t1581;
    }
    ;
    Bool _t1677; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1677 = *_hp; free(_hp); }
    (void)_t1677;
    if (_t1677) {
        Str *_t1582 = Str_lit("Str", 3ULL);
        (void)_t1582;
        U64 _t1583; { U64 *_hp = (U64 *)Str_size(); _t1583 = *_hp; free(_hp); }
        (void)_t1583;
        U64 _t1584 = 3;
        (void)_t1584;
        Array *_va27 = Array_new(_t1582, &(U64){_t1583}, &(U64){_t1584});
        (void)_va27;
        Str_delete(_t1582, &(Bool){1});
        ;
        ;
        U64 _t1585 = 0;
        (void)_t1585;
        Str *_t1586 = Str_lit("Decl(", 5ULL);
        (void)_t1586;
        Array_set(_va27, &(U64){_t1585}, _t1586);
        ;
        Declaration *_t1587 = ExprData_get_Decl(self);
        (void)_t1587;
        U64 _t1588 = 1;
        (void)_t1588;
        Str *_t1589 = Declaration_to_str(_t1587);
        (void)_t1589;
        Declaration_delete(_t1587, &(Bool){1});
        Array_set(_va27, &(U64){_t1588}, _t1589);
        ;
        U64 _t1590 = 2;
        (void)_t1590;
        Str *_t1591 = Str_lit(")", 1ULL);
        (void)_t1591;
        Array_set(_va27, &(U64){_t1590}, _t1591);
        ;
        Str *_t1592 = format(_va27);
        (void)_t1592;
        ;
        return _t1592;
    }
    ;
    Bool _t1678; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1678 = *_hp; free(_hp); }
    (void)_t1678;
    if (_t1678) {
        Str *_t1593 = Str_lit("Str", 3ULL);
        (void)_t1593;
        U64 _t1594; { U64 *_hp = (U64 *)Str_size(); _t1594 = *_hp; free(_hp); }
        (void)_t1594;
        U64 _t1595 = 3;
        (void)_t1595;
        Array *_va28 = Array_new(_t1593, &(U64){_t1594}, &(U64){_t1595});
        (void)_va28;
        Str_delete(_t1593, &(Bool){1});
        ;
        ;
        U64 _t1596 = 0;
        (void)_t1596;
        Str *_t1597 = Str_lit("Assign(", 7ULL);
        (void)_t1597;
        Array_set(_va28, &(U64){_t1596}, _t1597);
        ;
        Str *_t1598 = ExprData_get_Assign(self);
        (void)_t1598;
        U64 _t1599 = 1;
        (void)_t1599;
        Str *_t1600 = Str_to_str(_t1598);
        (void)_t1600;
        Str_delete(_t1598, &(Bool){1});
        Array_set(_va28, &(U64){_t1599}, _t1600);
        ;
        U64 _t1601 = 2;
        (void)_t1601;
        Str *_t1602 = Str_lit(")", 1ULL);
        (void)_t1602;
        Array_set(_va28, &(U64){_t1601}, _t1602);
        ;
        Str *_t1603 = format(_va28);
        (void)_t1603;
        ;
        return _t1603;
    }
    ;
    Bool _t1679; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1679 = *_hp; free(_hp); }
    (void)_t1679;
    if (_t1679) {
        Str *_t1604 = Str_lit("FCall", 5ULL);
        (void)_t1604;
        ;
        return _t1604;
    }
    ;
    Bool _t1680; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1680 = *_hp; free(_hp); }
    (void)_t1680;
    if (_t1680) {
        Str *_t1605 = Str_lit("Str", 3ULL);
        (void)_t1605;
        U64 _t1606; { U64 *_hp = (U64 *)Str_size(); _t1606 = *_hp; free(_hp); }
        (void)_t1606;
        U64 _t1607 = 3;
        (void)_t1607;
        Array *_va29 = Array_new(_t1605, &(U64){_t1606}, &(U64){_t1607});
        (void)_va29;
        Str_delete(_t1605, &(Bool){1});
        ;
        ;
        U64 _t1608 = 0;
        (void)_t1608;
        Str *_t1609 = Str_lit("FuncDef(", 8ULL);
        (void)_t1609;
        Array_set(_va29, &(U64){_t1608}, _t1609);
        ;
        FunctionDef *_t1610 = ExprData_get_FuncDef(self);
        (void)_t1610;
        U64 _t1611 = 1;
        (void)_t1611;
        Str *_t1612 = FunctionDef_to_str(_t1610);
        (void)_t1612;
        FunctionDef_delete(_t1610, &(Bool){1});
        Array_set(_va29, &(U64){_t1611}, _t1612);
        ;
        U64 _t1613 = 2;
        (void)_t1613;
        Str *_t1614 = Str_lit(")", 1ULL);
        (void)_t1614;
        Array_set(_va29, &(U64){_t1613}, _t1614);
        ;
        Str *_t1615 = format(_va29);
        (void)_t1615;
        ;
        return _t1615;
    }
    ;
    Bool _t1681; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1681 = *_hp; free(_hp); }
    (void)_t1681;
    if (_t1681) {
        Str *_t1616 = Str_lit("StructDef", 9ULL);
        (void)_t1616;
        ;
        return _t1616;
    }
    ;
    Bool _t1682; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1682 = *_hp; free(_hp); }
    (void)_t1682;
    if (_t1682) {
        Str *_t1617 = Str_lit("EnumDef", 7ULL);
        (void)_t1617;
        ;
        return _t1617;
    }
    ;
    Bool _t1683; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1683 = *_hp; free(_hp); }
    (void)_t1683;
    if (_t1683) {
        Str *_t1618 = Str_lit("Str", 3ULL);
        (void)_t1618;
        U64 _t1619; { U64 *_hp = (U64 *)Str_size(); _t1619 = *_hp; free(_hp); }
        (void)_t1619;
        U64 _t1620 = 3;
        (void)_t1620;
        Array *_va30 = Array_new(_t1618, &(U64){_t1619}, &(U64){_t1620});
        (void)_va30;
        Str_delete(_t1618, &(Bool){1});
        ;
        ;
        U64 _t1621 = 0;
        (void)_t1621;
        Str *_t1622 = Str_lit("FieldAccess(", 12ULL);
        (void)_t1622;
        Array_set(_va30, &(U64){_t1621}, _t1622);
        ;
        Str *_t1623 = ExprData_get_FieldAccess(self);
        (void)_t1623;
        U64 _t1624 = 1;
        (void)_t1624;
        Str *_t1625 = Str_to_str(_t1623);
        (void)_t1625;
        Str_delete(_t1623, &(Bool){1});
        Array_set(_va30, &(U64){_t1624}, _t1625);
        ;
        U64 _t1626 = 2;
        (void)_t1626;
        Str *_t1627 = Str_lit(")", 1ULL);
        (void)_t1627;
        Array_set(_va30, &(U64){_t1626}, _t1627);
        ;
        Str *_t1628 = format(_va30);
        (void)_t1628;
        ;
        return _t1628;
    }
    ;
    Bool _t1684; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1684 = *_hp; free(_hp); }
    (void)_t1684;
    if (_t1684) {
        Str *_t1629 = Str_lit("Str", 3ULL);
        (void)_t1629;
        U64 _t1630; { U64 *_hp = (U64 *)Str_size(); _t1630 = *_hp; free(_hp); }
        (void)_t1630;
        U64 _t1631 = 3;
        (void)_t1631;
        Array *_va31 = Array_new(_t1629, &(U64){_t1630}, &(U64){_t1631});
        (void)_va31;
        Str_delete(_t1629, &(Bool){1});
        ;
        ;
        U64 _t1632 = 0;
        (void)_t1632;
        Str *_t1633 = Str_lit("FieldAssign(", 12ULL);
        (void)_t1633;
        Array_set(_va31, &(U64){_t1632}, _t1633);
        ;
        Str *_t1634 = ExprData_get_FieldAssign(self);
        (void)_t1634;
        U64 _t1635 = 1;
        (void)_t1635;
        Str *_t1636 = Str_to_str(_t1634);
        (void)_t1636;
        Str_delete(_t1634, &(Bool){1});
        Array_set(_va31, &(U64){_t1635}, _t1636);
        ;
        U64 _t1637 = 2;
        (void)_t1637;
        Str *_t1638 = Str_lit(")", 1ULL);
        (void)_t1638;
        Array_set(_va31, &(U64){_t1637}, _t1638);
        ;
        Str *_t1639 = format(_va31);
        (void)_t1639;
        ;
        return _t1639;
    }
    ;
    Bool _t1685; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1685 = *_hp; free(_hp); }
    (void)_t1685;
    if (_t1685) {
        Str *_t1640 = Str_lit("Return", 6ULL);
        (void)_t1640;
        ;
        return _t1640;
    }
    ;
    Bool _t1686; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1686 = *_hp; free(_hp); }
    (void)_t1686;
    if (_t1686) {
        Str *_t1641 = Str_lit("If", 2ULL);
        (void)_t1641;
        ;
        return _t1641;
    }
    ;
    Bool _t1687; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1687 = *_hp; free(_hp); }
    (void)_t1687;
    if (_t1687) {
        Str *_t1642 = Str_lit("While", 5ULL);
        (void)_t1642;
        ;
        return _t1642;
    }
    ;
    Bool _t1688; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1688 = *_hp; free(_hp); }
    (void)_t1688;
    if (_t1688) {
        Str *_t1643 = Str_lit("Str", 3ULL);
        (void)_t1643;
        U64 _t1644; { U64 *_hp = (U64 *)Str_size(); _t1644 = *_hp; free(_hp); }
        (void)_t1644;
        U64 _t1645 = 3;
        (void)_t1645;
        Array *_va32 = Array_new(_t1643, &(U64){_t1644}, &(U64){_t1645});
        (void)_va32;
        Str_delete(_t1643, &(Bool){1});
        ;
        ;
        U64 _t1646 = 0;
        (void)_t1646;
        Str *_t1647 = Str_lit("ForIn(", 6ULL);
        (void)_t1647;
        Array_set(_va32, &(U64){_t1646}, _t1647);
        ;
        Str *_t1648 = ExprData_get_ForIn(self);
        (void)_t1648;
        U64 _t1649 = 1;
        (void)_t1649;
        Str *_t1650 = Str_to_str(_t1648);
        (void)_t1650;
        Str_delete(_t1648, &(Bool){1});
        Array_set(_va32, &(U64){_t1649}, _t1650);
        ;
        U64 _t1651 = 2;
        (void)_t1651;
        Str *_t1652 = Str_lit(")", 1ULL);
        (void)_t1652;
        Array_set(_va32, &(U64){_t1651}, _t1652);
        ;
        Str *_t1653 = format(_va32);
        (void)_t1653;
        ;
        return _t1653;
    }
    ;
    Bool _t1689; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1689 = *_hp; free(_hp); }
    (void)_t1689;
    if (_t1689) {
        Str *_t1654 = Str_lit("Str", 3ULL);
        (void)_t1654;
        U64 _t1655; { U64 *_hp = (U64 *)Str_size(); _t1655 = *_hp; free(_hp); }
        (void)_t1655;
        U64 _t1656 = 3;
        (void)_t1656;
        Array *_va33 = Array_new(_t1654, &(U64){_t1655}, &(U64){_t1656});
        (void)_va33;
        Str_delete(_t1654, &(Bool){1});
        ;
        ;
        U64 _t1657 = 0;
        (void)_t1657;
        Str *_t1658 = Str_lit("NamedArg(", 9ULL);
        (void)_t1658;
        Array_set(_va33, &(U64){_t1657}, _t1658);
        ;
        Str *_t1659 = ExprData_get_NamedArg(self);
        (void)_t1659;
        U64 _t1660 = 1;
        (void)_t1660;
        Str *_t1661 = Str_to_str(_t1659);
        (void)_t1661;
        Str_delete(_t1659, &(Bool){1});
        Array_set(_va33, &(U64){_t1660}, _t1661);
        ;
        U64 _t1662 = 2;
        (void)_t1662;
        Str *_t1663 = Str_lit(")", 1ULL);
        (void)_t1663;
        Array_set(_va33, &(U64){_t1662}, _t1663);
        ;
        Str *_t1664 = format(_va33);
        (void)_t1664;
        ;
        return _t1664;
    }
    ;
    Bool _t1690; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1690 = *_hp; free(_hp); }
    (void)_t1690;
    if (_t1690) {
        Str *_t1665 = Str_lit("Break", 5ULL);
        (void)_t1665;
        ;
        return _t1665;
    }
    ;
    Bool _t1691; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1691 = *_hp; free(_hp); }
    (void)_t1691;
    if (_t1691) {
        Str *_t1666 = Str_lit("Continue", 8ULL);
        (void)_t1666;
        ;
        return _t1666;
    }
    ;
    Bool _t1692; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1692 = *_hp; free(_hp); }
    (void)_t1692;
    if (_t1692) {
        Str *_t1667 = Str_lit("MapLit", 6ULL);
        (void)_t1667;
        ;
        return _t1667;
    }
    ;
    Bool _t1693; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1693 = *_hp; free(_hp); }
    (void)_t1693;
    if (_t1693) {
        Str *_t1668 = Str_lit("SetLit", 6ULL);
        (void)_t1668;
        ;
        return _t1668;
    }
    ;
    Bool _t1694; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1694 = *_hp; free(_hp); }
    (void)_t1694;
    if (_t1694) {
        Str *_t1669 = Str_lit("Switch", 6ULL);
        (void)_t1669;
        ;
        return _t1669;
    }
    ;
    Bool _t1695; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1695 = *_hp; free(_hp); }
    (void)_t1695;
    if (_t1695) {
        Str *_t1670 = Str_lit("Case", 4ULL);
        (void)_t1670;
        ;
        return _t1670;
    }
    ;
    Str *_t1696 = Str_lit("unknown", 7ULL);
    (void)_t1696;
    return _t1696;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t1698 = Str_lit("Str", 3ULL);
    (void)_t1698;
    U64 _t1699; { U64 *_hp = (U64 *)Str_size(); _t1699 = *_hp; free(_hp); }
    (void)_t1699;
    U64 _t1700 = 7;
    (void)_t1700;
    Array *_va34 = Array_new(_t1698, &(U64){_t1699}, &(U64){_t1700});
    (void)_va34;
    Str_delete(_t1698, &(Bool){1});
    ;
    ;
    U64 _t1701 = 0;
    (void)_t1701;
    Str *_t1702 = Str_clone(&self->path);
    (void)_t1702;
    Array_set(_va34, &(U64){_t1701}, _t1702);
    ;
    U64 _t1703 = 1;
    (void)_t1703;
    Str *_t1704 = Str_lit(":", 1ULL);
    (void)_t1704;
    Array_set(_va34, &(U64){_t1703}, _t1704);
    ;
    U64 _t1705 = 2;
    (void)_t1705;
    Str *_t1706 = U32_to_str(&self->line);
    (void)_t1706;
    Array_set(_va34, &(U64){_t1705}, _t1706);
    ;
    U64 _t1707 = 3;
    (void)_t1707;
    Str *_t1708 = Str_lit(":", 1ULL);
    (void)_t1708;
    Array_set(_va34, &(U64){_t1707}, _t1708);
    ;
    U64 _t1709 = 4;
    (void)_t1709;
    Str *_t1710 = U32_to_str(&self->col);
    (void)_t1710;
    Array_set(_va34, &(U64){_t1709}, _t1710);
    ;
    U64 _t1711 = 5;
    (void)_t1711;
    Str *_t1712 = Str_lit(": error: ", 9ULL);
    (void)_t1712;
    Array_set(_va34, &(U64){_t1711}, _t1712);
    ;
    U64 _t1713 = 6;
    (void)_t1713;
    Str *_t1714 = Str_clone(msg);
    (void)_t1714;
    Array_set(_va34, &(U64){_t1713}, _t1714);
    ;
    println(_va34);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1715 = Str_lit("Str", 3ULL);
    (void)_t1715;
    U64 _t1716; { U64 *_hp = (U64 *)Str_size(); _t1716 = *_hp; free(_hp); }
    (void)_t1716;
    U64 _t1717 = 1;
    (void)_t1717;
    Array *_va35 = Array_new(_t1715, &(U64){_t1716}, &(U64){_t1717});
    (void)_va35;
    Str_delete(_t1715, &(Bool){1});
    ;
    ;
    U64 _t1718 = 0;
    (void)_t1718;
    Str *_t1719 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t1719;
    Array_set(_va35, &(U64){_t1718}, _t1719);
    ;
    println(_va35);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1720 = Str_lit("Str", 3ULL);
    (void)_t1720;
    U64 _t1721; { U64 *_hp = (U64 *)Str_size(); _t1721 = *_hp; free(_hp); }
    (void)_t1721;
    U64 _t1722 = 1;
    (void)_t1722;
    Array *_va36 = Array_new(_t1720, &(U64){_t1721}, &(U64){_t1722});
    (void)_va36;
    Str_delete(_t1720, &(Bool){1});
    ;
    ;
    U64 _t1723 = 0;
    (void)_t1723;
    Str *_t1724 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t1724;
    Array_set(_va36, &(U64){_t1723}, _t1724);
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
    U64 *_t1725 = malloc(sizeof(U64)); *_t1725 = I64_to_u64(DEREF(i));
    (void)_t1725;
    Expr *c = Vec_get(&parent->children, _t1725);
    (void)c;
    U64_delete(_t1725, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t1726; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t1726 = *_hp; free(_hp); }
    (void)_t1726;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t1726; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t1727 = 0;
    (void)_t1727;
    I64 _t1728 = 1;
    (void)_t1728;
    I64 _t1729 = I64_sub(_t1727, _t1728);
    (void)_t1729;
    ;
    ;
    I64 _t1730 = 0;
    (void)_t1730;
    I64 _t1731 = 1;
    (void)_t1731;
    I64 _t1732 = I64_sub(_t1730, _t1731);
    (void)_t1732;
    ;
    ;
    Str *_t1733 = Str_lit("", 0ULL);
    (void)_t1733;
    U64 _t1734; { U64 *_hp = (U64 *)Expr_size(); _t1734 = *_hp; free(_hp); }
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
    Bool _t1742 = 0;
    (void)_t1742;
    I32 _t1743 = 0;
    (void)_t1743;
    I32 _t1744 = I64_to_i32(_t1729);
    (void)_t1744;
    ;
    U32 _t1745 = 0;
    (void)_t1745;
    I32 _t1746 = I64_to_i32(_t1732);
    (void)_t1746;
    ;
    U32 _t1747 = 0;
    (void)_t1747;
    U32 _t1748 = U32_clone(&(U32){col});
    (void)_t1748;
    Str *_t1749 = Str_clone(path);
    (void)_t1749;
    Expr *_t1750 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t1750->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t1750->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1750->struct_name = *_ca; free(_ca); }
    _t1750->is_own_arg = _t1735;
    _t1750->is_splat = _t1736;
    _t1750->is_own_field = _t1737;
    _t1750->is_ref_field = _t1738;
    _t1750->is_ns_field = _t1739;
    _t1750->is_ext = _t1740;
    _t1750->is_core = _t1741;
    _t1750->save_old_delete = _t1742;
    _t1750->total_struct_size = _t1743;
    _t1750->variadic_index = _t1744;
    _t1750->variadic_count = _t1745;
    _t1750->kwargs_index = _t1746;
    _t1750->kwargs_count = _t1747;
    _t1750->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t1733, &(U64){_t1734}); _t1750->children = *_ca; free(_ca); }
    _t1750->line = U32_clone(&(U32){line});
    _t1750->col = _t1748;
    { Str *_ca = Str_clone(_t1749); _t1750->path = *_ca; free(_ca); }
    (void)_t1750;
    Str_delete(_t1733, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t1749, &(Bool){1});
    return _t1750;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t1758 = Str_lit("", 0ULL);
    (void)_t1758;
    U64 _t1759; { U64 *_hp = (U64 *)Expr_size(); _t1759 = *_hp; free(_hp); }
    (void)_t1759;
    Vec *new_children = Vec_new(_t1758, &(U64){_t1759});
    (void)new_children;
    Str_delete(_t1758, &(Bool){1});
    ;
    {
        U64 _t1756 = 0;
        (void)_t1756;
        U64 _t1757; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1757 = *_hp; free(_hp); }
        (void)_t1757;
        Range *_fc1751 = Range_new(_t1756, _t1757);
        (void)_fc1751;
        ;
        ;
        U64 _fi1751 = 0;
        (void)_fi1751;
        while (1) {
            U64 _t1753; { U64 *_hp = (U64 *)Range_len(_fc1751); _t1753 = *_hp; free(_hp); }
            (void)_t1753;
            Bool _wcond1752; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1751}, &(U64){_t1753}); _wcond1752 = *_hp; free(_hp); }
            (void)_wcond1752;
            ;
            if (_wcond1752) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1751, _fi1751);
            (void)i;
            U64 _t1754 = 1;
            (void)_t1754;
            U64 _t1755 = U64_add(_fi1751, _t1754);
            (void)_t1755;
            ;
            _fi1751 = _t1755;
            ;
            Expr *c = Vec_get(&self->children, i);
            (void)c;
            Expr *cloned = Expr_clone(c);
            (void)cloned;
            U64_delete(i, &(Bool){1});
            Vec_push(new_children, cloned);
        }
        Range_delete(_fc1751, &(Bool){1});
        ;
    }
    Expr *_t1760 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t1760->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t1760->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t1760->struct_name = *_ca; free(_ca); }
    _t1760->is_own_arg = self->is_own_arg;
    _t1760->is_splat = self->is_splat;
    _t1760->is_own_field = self->is_own_field;
    _t1760->is_ref_field = self->is_ref_field;
    _t1760->is_ns_field = self->is_ns_field;
    _t1760->is_ext = self->is_ext;
    _t1760->is_core = self->is_core;
    _t1760->save_old_delete = self->save_old_delete;
    _t1760->total_struct_size = self->total_struct_size;
    _t1760->variadic_index = self->variadic_index;
    _t1760->variadic_count = self->variadic_count;
    _t1760->kwargs_index = self->kwargs_index;
    _t1760->kwargs_count = self->kwargs_count;
    _t1760->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t1760->children = *_ca; free(_ca); }
    _t1760->line = self->line;
    _t1760->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t1760->path = *_ca; free(_ca); }
    (void)_t1760;
    Vec_delete(new_children, &(Bool){1});
    return _t1760;
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
    Bool _t2121; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t2121 = *_hp; free(_hp); }
    (void)_t2121;
    if (_t2121) {
        Bool _t2055; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t2055 = *_hp; free(_hp); }
        (void)_t2055;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2055; return _r; }
    }
    ;
    Bool _t2122; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t2122 = *_hp; free(_hp); }
    (void)_t2122;
    if (_t2122) {
        Bool _t2056; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t2056 = *_hp; free(_hp); }
        (void)_t2056;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2056; return _r; }
    }
    ;
    Bool _t2123; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t2123 = *_hp; free(_hp); }
    (void)_t2123;
    if (_t2123) {
        Bool _t2057; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t2057 = *_hp; free(_hp); }
        (void)_t2057;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2057; return _r; }
    }
    ;
    Bool _t2124; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t2124 = *_hp; free(_hp); }
    (void)_t2124;
    if (_t2124) {
        Bool _t2058; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t2058 = *_hp; free(_hp); }
        (void)_t2058;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2058; return _r; }
    }
    ;
    Bool _t2125; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t2125 = *_hp; free(_hp); }
    (void)_t2125;
    if (_t2125) {
        Bool _t2059; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t2059 = *_hp; free(_hp); }
        (void)_t2059;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2059; return _r; }
    }
    ;
    Bool _t2126; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t2126 = *_hp; free(_hp); }
    (void)_t2126;
    if (_t2126) {
        Bool _t2060; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t2060 = *_hp; free(_hp); }
        (void)_t2060;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2060; return _r; }
    }
    ;
    Bool _t2127; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t2127 = *_hp; free(_hp); }
    (void)_t2127;
    if (_t2127) {
        Bool _t2061; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t2061 = *_hp; free(_hp); }
        (void)_t2061;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2061; return _r; }
    }
    ;
    Bool _t2128; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t2128 = *_hp; free(_hp); }
    (void)_t2128;
    if (_t2128) {
        Bool _t2062; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t2062 = *_hp; free(_hp); }
        (void)_t2062;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2062; return _r; }
    }
    ;
    Bool _t2129; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t2129 = *_hp; free(_hp); }
    (void)_t2129;
    if (_t2129) {
        Bool _t2063; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t2063 = *_hp; free(_hp); }
        (void)_t2063;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2063; return _r; }
    }
    ;
    Bool _t2130; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t2130 = *_hp; free(_hp); }
    (void)_t2130;
    if (_t2130) {
        Bool _t2064; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t2064 = *_hp; free(_hp); }
        (void)_t2064;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2064; return _r; }
    }
    ;
    Bool _t2131; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t2131 = *_hp; free(_hp); }
    (void)_t2131;
    if (_t2131) {
        Bool _t2065; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t2065 = *_hp; free(_hp); }
        (void)_t2065;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2065; return _r; }
    }
    ;
    Bool _t2132; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t2132 = *_hp; free(_hp); }
    (void)_t2132;
    if (_t2132) {
        Bool _t2066; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t2066 = *_hp; free(_hp); }
        (void)_t2066;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2066; return _r; }
    }
    ;
    Bool _t2133; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t2133 = *_hp; free(_hp); }
    (void)_t2133;
    if (_t2133) {
        Bool _t2067; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t2067 = *_hp; free(_hp); }
        (void)_t2067;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2067; return _r; }
    }
    ;
    Bool _t2134; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t2134 = *_hp; free(_hp); }
    (void)_t2134;
    if (_t2134) {
        Bool _t2068; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t2068 = *_hp; free(_hp); }
        (void)_t2068;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2068; return _r; }
    }
    ;
    Bool _t2135; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t2135 = *_hp; free(_hp); }
    (void)_t2135;
    if (_t2135) {
        Bool _t2069; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t2069 = *_hp; free(_hp); }
        (void)_t2069;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2069; return _r; }
    }
    ;
    Bool _t2136; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t2136 = *_hp; free(_hp); }
    (void)_t2136;
    if (_t2136) {
        Bool _t2070; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t2070 = *_hp; free(_hp); }
        (void)_t2070;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2070; return _r; }
    }
    ;
    Bool _t2137; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t2137 = *_hp; free(_hp); }
    (void)_t2137;
    if (_t2137) {
        Bool _t2071; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t2071 = *_hp; free(_hp); }
        (void)_t2071;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2071; return _r; }
    }
    ;
    Bool _t2138; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t2138 = *_hp; free(_hp); }
    (void)_t2138;
    if (_t2138) {
        Bool _t2072; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t2072 = *_hp; free(_hp); }
        (void)_t2072;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2072; return _r; }
    }
    ;
    Bool _t2139; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t2139 = *_hp; free(_hp); }
    (void)_t2139;
    if (_t2139) {
        Bool _t2073; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t2073 = *_hp; free(_hp); }
        (void)_t2073;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2073; return _r; }
    }
    ;
    Bool _t2140; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t2140 = *_hp; free(_hp); }
    (void)_t2140;
    if (_t2140) {
        Bool _t2074; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t2074 = *_hp; free(_hp); }
        (void)_t2074;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2074; return _r; }
    }
    ;
    Bool _t2141; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t2141 = *_hp; free(_hp); }
    (void)_t2141;
    if (_t2141) {
        Bool _t2075; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t2075 = *_hp; free(_hp); }
        (void)_t2075;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2075; return _r; }
    }
    ;
    Bool _t2142; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t2142 = *_hp; free(_hp); }
    (void)_t2142;
    if (_t2142) {
        Bool _t2076; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t2076 = *_hp; free(_hp); }
        (void)_t2076;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2076; return _r; }
    }
    ;
    Bool _t2143; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t2143 = *_hp; free(_hp); }
    (void)_t2143;
    if (_t2143) {
        Bool _t2077; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t2077 = *_hp; free(_hp); }
        (void)_t2077;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2077; return _r; }
    }
    ;
    Bool _t2144; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t2144 = *_hp; free(_hp); }
    (void)_t2144;
    if (_t2144) {
        Bool _t2078; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t2078 = *_hp; free(_hp); }
        (void)_t2078;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2078; return _r; }
    }
    ;
    Bool _t2145; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t2145 = *_hp; free(_hp); }
    (void)_t2145;
    if (_t2145) {
        Bool _t2079; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t2079 = *_hp; free(_hp); }
        (void)_t2079;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2079; return _r; }
    }
    ;
    Bool _t2146; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t2146 = *_hp; free(_hp); }
    (void)_t2146;
    if (_t2146) {
        Bool _t2080; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t2080 = *_hp; free(_hp); }
        (void)_t2080;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2080; return _r; }
    }
    ;
    Bool _t2147; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t2147 = *_hp; free(_hp); }
    (void)_t2147;
    if (_t2147) {
        Bool _t2081; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t2081 = *_hp; free(_hp); }
        (void)_t2081;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2081; return _r; }
    }
    ;
    Bool _t2148; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t2148 = *_hp; free(_hp); }
    (void)_t2148;
    if (_t2148) {
        Bool _t2082; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t2082 = *_hp; free(_hp); }
        (void)_t2082;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2082; return _r; }
    }
    ;
    Bool _t2149; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t2149 = *_hp; free(_hp); }
    (void)_t2149;
    if (_t2149) {
        Bool _t2083; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t2083 = *_hp; free(_hp); }
        (void)_t2083;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2083; return _r; }
    }
    ;
    Bool _t2150; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t2150 = *_hp; free(_hp); }
    (void)_t2150;
    if (_t2150) {
        Bool _t2084; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t2084 = *_hp; free(_hp); }
        (void)_t2084;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2084; return _r; }
    }
    ;
    Bool _t2151; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t2151 = *_hp; free(_hp); }
    (void)_t2151;
    if (_t2151) {
        Bool _t2085; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t2085 = *_hp; free(_hp); }
        (void)_t2085;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2085; return _r; }
    }
    ;
    Bool _t2152; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t2152 = *_hp; free(_hp); }
    (void)_t2152;
    if (_t2152) {
        Bool _t2086; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t2086 = *_hp; free(_hp); }
        (void)_t2086;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2086; return _r; }
    }
    ;
    Bool _t2153; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t2153 = *_hp; free(_hp); }
    (void)_t2153;
    if (_t2153) {
        Bool _t2087; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t2087 = *_hp; free(_hp); }
        (void)_t2087;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2087; return _r; }
    }
    ;
    Bool _t2154; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t2154 = *_hp; free(_hp); }
    (void)_t2154;
    if (_t2154) {
        Bool _t2088; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t2088 = *_hp; free(_hp); }
        (void)_t2088;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2088; return _r; }
    }
    ;
    Bool _t2155; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t2155 = *_hp; free(_hp); }
    (void)_t2155;
    if (_t2155) {
        Bool _t2089; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t2089 = *_hp; free(_hp); }
        (void)_t2089;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2089; return _r; }
    }
    ;
    Bool _t2156; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t2156 = *_hp; free(_hp); }
    (void)_t2156;
    if (_t2156) {
        Bool _t2090; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t2090 = *_hp; free(_hp); }
        (void)_t2090;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2090; return _r; }
    }
    ;
    Bool _t2157; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t2157 = *_hp; free(_hp); }
    (void)_t2157;
    if (_t2157) {
        Bool _t2091; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t2091 = *_hp; free(_hp); }
        (void)_t2091;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2091; return _r; }
    }
    ;
    Bool _t2158; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t2158 = *_hp; free(_hp); }
    (void)_t2158;
    if (_t2158) {
        Bool _t2092; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t2092 = *_hp; free(_hp); }
        (void)_t2092;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2092; return _r; }
    }
    ;
    Bool _t2159; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t2159 = *_hp; free(_hp); }
    (void)_t2159;
    if (_t2159) {
        Bool _t2093; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t2093 = *_hp; free(_hp); }
        (void)_t2093;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2093; return _r; }
    }
    ;
    Bool _t2160; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t2160 = *_hp; free(_hp); }
    (void)_t2160;
    if (_t2160) {
        Bool _t2094; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t2094 = *_hp; free(_hp); }
        (void)_t2094;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2094; return _r; }
    }
    ;
    Bool _t2161; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t2161 = *_hp; free(_hp); }
    (void)_t2161;
    if (_t2161) {
        Bool _t2095; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t2095 = *_hp; free(_hp); }
        (void)_t2095;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2095; return _r; }
    }
    ;
    Bool _t2162; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t2162 = *_hp; free(_hp); }
    (void)_t2162;
    if (_t2162) {
        Bool _t2096; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t2096 = *_hp; free(_hp); }
        (void)_t2096;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2096; return _r; }
    }
    ;
    Bool _t2163; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t2163 = *_hp; free(_hp); }
    (void)_t2163;
    if (_t2163) {
        Bool _t2097; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t2097 = *_hp; free(_hp); }
        (void)_t2097;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2097; return _r; }
    }
    ;
    Bool _t2164; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t2164 = *_hp; free(_hp); }
    (void)_t2164;
    if (_t2164) {
        Bool _t2098; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t2098 = *_hp; free(_hp); }
        (void)_t2098;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2098; return _r; }
    }
    ;
    Bool _t2165; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t2165 = *_hp; free(_hp); }
    (void)_t2165;
    if (_t2165) {
        Bool _t2099; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t2099 = *_hp; free(_hp); }
        (void)_t2099;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2099; return _r; }
    }
    ;
    Bool _t2166; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t2166 = *_hp; free(_hp); }
    (void)_t2166;
    if (_t2166) {
        Bool _t2100; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t2100 = *_hp; free(_hp); }
        (void)_t2100;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2100; return _r; }
    }
    ;
    Bool _t2167; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t2167 = *_hp; free(_hp); }
    (void)_t2167;
    if (_t2167) {
        Bool _t2101; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t2101 = *_hp; free(_hp); }
        (void)_t2101;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2101; return _r; }
    }
    ;
    Bool _t2168; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t2168 = *_hp; free(_hp); }
    (void)_t2168;
    if (_t2168) {
        Bool _t2102; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t2102 = *_hp; free(_hp); }
        (void)_t2102;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2102; return _r; }
    }
    ;
    Bool _t2169; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t2169 = *_hp; free(_hp); }
    (void)_t2169;
    if (_t2169) {
        Bool _t2103; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t2103 = *_hp; free(_hp); }
        (void)_t2103;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2103; return _r; }
    }
    ;
    Bool _t2170; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t2170 = *_hp; free(_hp); }
    (void)_t2170;
    if (_t2170) {
        Bool _t2104; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t2104 = *_hp; free(_hp); }
        (void)_t2104;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2104; return _r; }
    }
    ;
    Bool _t2171; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t2171 = *_hp; free(_hp); }
    (void)_t2171;
    if (_t2171) {
        Bool _t2105; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t2105 = *_hp; free(_hp); }
        (void)_t2105;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2105; return _r; }
    }
    ;
    Bool _t2172; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t2172 = *_hp; free(_hp); }
    (void)_t2172;
    if (_t2172) {
        Bool _t2106; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t2106 = *_hp; free(_hp); }
        (void)_t2106;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2106; return _r; }
    }
    ;
    Bool _t2173; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t2173 = *_hp; free(_hp); }
    (void)_t2173;
    if (_t2173) {
        Bool _t2107; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t2107 = *_hp; free(_hp); }
        (void)_t2107;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2107; return _r; }
    }
    ;
    Bool _t2174; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t2174 = *_hp; free(_hp); }
    (void)_t2174;
    if (_t2174) {
        Bool _t2108; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t2108 = *_hp; free(_hp); }
        (void)_t2108;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2108; return _r; }
    }
    ;
    Bool _t2175; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t2175 = *_hp; free(_hp); }
    (void)_t2175;
    if (_t2175) {
        Bool _t2109; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t2109 = *_hp; free(_hp); }
        (void)_t2109;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2109; return _r; }
    }
    ;
    Bool _t2176; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t2176 = *_hp; free(_hp); }
    (void)_t2176;
    if (_t2176) {
        Bool _t2110; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t2110 = *_hp; free(_hp); }
        (void)_t2110;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2110; return _r; }
    }
    ;
    Bool _t2177; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t2177 = *_hp; free(_hp); }
    (void)_t2177;
    if (_t2177) {
        Bool _t2111; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t2111 = *_hp; free(_hp); }
        (void)_t2111;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2111; return _r; }
    }
    ;
    Bool _t2178; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t2178 = *_hp; free(_hp); }
    (void)_t2178;
    if (_t2178) {
        Bool _t2112; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t2112 = *_hp; free(_hp); }
        (void)_t2112;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2112; return _r; }
    }
    ;
    Bool _t2179; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t2179 = *_hp; free(_hp); }
    (void)_t2179;
    if (_t2179) {
        Bool _t2113; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t2113 = *_hp; free(_hp); }
        (void)_t2113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2113; return _r; }
    }
    ;
    Bool _t2180; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t2180 = *_hp; free(_hp); }
    (void)_t2180;
    if (_t2180) {
        Bool _t2114; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t2114 = *_hp; free(_hp); }
        (void)_t2114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2114; return _r; }
    }
    ;
    Bool _t2181; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t2181 = *_hp; free(_hp); }
    (void)_t2181;
    if (_t2181) {
        Bool _t2115; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t2115 = *_hp; free(_hp); }
        (void)_t2115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2115; return _r; }
    }
    ;
    Bool _t2182; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t2182 = *_hp; free(_hp); }
    (void)_t2182;
    if (_t2182) {
        Bool _t2116; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t2116 = *_hp; free(_hp); }
        (void)_t2116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2116; return _r; }
    }
    ;
    Bool _t2183; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t2183 = *_hp; free(_hp); }
    (void)_t2183;
    if (_t2183) {
        Bool _t2117; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t2117 = *_hp; free(_hp); }
        (void)_t2117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2117; return _r; }
    }
    ;
    Bool _t2184; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t2184 = *_hp; free(_hp); }
    (void)_t2184;
    if (_t2184) {
        Bool _t2118; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t2118 = *_hp; free(_hp); }
        (void)_t2118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2118; return _r; }
    }
    ;
    Bool _t2185; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t2185 = *_hp; free(_hp); }
    (void)_t2185;
    if (_t2185) {
        Bool _t2119; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t2119 = *_hp; free(_hp); }
        (void)_t2119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2119; return _r; }
    }
    ;
    Bool _t2186; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t2186 = *_hp; free(_hp); }
    (void)_t2186;
    if (_t2186) {
        Bool _t2120; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t2120 = *_hp; free(_hp); }
        (void)_t2120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2120; return _r; }
    }
    ;
    Bool _t2187 = 0;
    (void)_t2187;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2187; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t2188; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2188 = *_hp; free(_hp); }
    (void)_t2188;
    if (_t2188) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t2189; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2189 = *_hp; free(_hp); }
    (void)_t2189;
    if (_t2189) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t2190; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2190 = *_hp; free(_hp); }
    (void)_t2190;
    if (_t2190) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t2191; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2191 = *_hp; free(_hp); }
    (void)_t2191;
    if (_t2191) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t2192; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2192 = *_hp; free(_hp); }
    (void)_t2192;
    if (_t2192) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t2193; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2193 = *_hp; free(_hp); }
    (void)_t2193;
    if (_t2193) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t2194; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2194 = *_hp; free(_hp); }
    (void)_t2194;
    if (_t2194) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t2195; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2195 = *_hp; free(_hp); }
    (void)_t2195;
    if (_t2195) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t2196; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2196 = *_hp; free(_hp); }
    (void)_t2196;
    if (_t2196) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t2197; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2197 = *_hp; free(_hp); }
    (void)_t2197;
    if (_t2197) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t2198; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2198 = *_hp; free(_hp); }
    (void)_t2198;
    if (_t2198) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t2199; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2199 = *_hp; free(_hp); }
    (void)_t2199;
    if (_t2199) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t2200; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2200 = *_hp; free(_hp); }
    (void)_t2200;
    if (_t2200) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t2201; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2201 = *_hp; free(_hp); }
    (void)_t2201;
    if (_t2201) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t2202; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2202 = *_hp; free(_hp); }
    (void)_t2202;
    if (_t2202) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t2203; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2203 = *_hp; free(_hp); }
    (void)_t2203;
    if (_t2203) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t2204; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2204 = *_hp; free(_hp); }
    (void)_t2204;
    if (_t2204) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t2205; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2205 = *_hp; free(_hp); }
    (void)_t2205;
    if (_t2205) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t2206; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t2240; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2240 = *_hp; free(_hp); }
    (void)_t2240;
    if (_t2240) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t2241; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    if (_t2241) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t2242; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    if (_t2242) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t2243; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2243 = *_hp; free(_hp); }
    (void)_t2243;
    if (_t2243) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t2244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2244 = *_hp; free(_hp); }
    (void)_t2244;
    if (_t2244) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t2245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2245 = *_hp; free(_hp); }
    (void)_t2245;
    if (_t2245) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t2246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    if (_t2246) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t2247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    if (_t2247) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t2248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2248 = *_hp; free(_hp); }
    (void)_t2248;
    if (_t2248) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t2249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2249 = *_hp; free(_hp); }
    (void)_t2249;
    if (_t2249) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t2250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2250 = *_hp; free(_hp); }
    (void)_t2250;
    if (_t2250) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t2251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2251 = *_hp; free(_hp); }
    (void)_t2251;
    if (_t2251) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t2252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2252 = *_hp; free(_hp); }
    (void)_t2252;
    if (_t2252) {
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
    Bool _t2319; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2319 = *_hp; free(_hp); }
    (void)_t2319;
    if (_t2319) {
        Str *_t2253 = Str_lit("Eof", 3ULL);
        (void)_t2253;
        ;
        return _t2253;
    }
    ;
    Bool _t2320; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2320 = *_hp; free(_hp); }
    (void)_t2320;
    if (_t2320) {
        Str *_t2254 = Str_lit("LParen", 6ULL);
        (void)_t2254;
        ;
        return _t2254;
    }
    ;
    Bool _t2321; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2321 = *_hp; free(_hp); }
    (void)_t2321;
    if (_t2321) {
        Str *_t2255 = Str_lit("RParen", 6ULL);
        (void)_t2255;
        ;
        return _t2255;
    }
    ;
    Bool _t2322; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2322 = *_hp; free(_hp); }
    (void)_t2322;
    if (_t2322) {
        Str *_t2256 = Str_lit("LBrace", 6ULL);
        (void)_t2256;
        ;
        return _t2256;
    }
    ;
    Bool _t2323; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2323 = *_hp; free(_hp); }
    (void)_t2323;
    if (_t2323) {
        Str *_t2257 = Str_lit("RBrace", 6ULL);
        (void)_t2257;
        ;
        return _t2257;
    }
    ;
    Bool _t2324; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2324 = *_hp; free(_hp); }
    (void)_t2324;
    if (_t2324) {
        Str *_t2258 = Str_lit("LBracket", 8ULL);
        (void)_t2258;
        ;
        return _t2258;
    }
    ;
    Bool _t2325; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2325 = *_hp; free(_hp); }
    (void)_t2325;
    if (_t2325) {
        Str *_t2259 = Str_lit("RBracket", 8ULL);
        (void)_t2259;
        ;
        return _t2259;
    }
    ;
    Bool _t2326; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2326 = *_hp; free(_hp); }
    (void)_t2326;
    if (_t2326) {
        Str *_t2260 = Str_lit("Comma", 5ULL);
        (void)_t2260;
        ;
        return _t2260;
    }
    ;
    Bool _t2327; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2327 = *_hp; free(_hp); }
    (void)_t2327;
    if (_t2327) {
        Str *_t2261 = Str_lit("Colon", 5ULL);
        (void)_t2261;
        ;
        return _t2261;
    }
    ;
    Bool _t2328; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2328 = *_hp; free(_hp); }
    (void)_t2328;
    if (_t2328) {
        Str *_t2262 = Str_lit("Question", 8ULL);
        (void)_t2262;
        ;
        return _t2262;
    }
    ;
    Bool _t2329; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2329 = *_hp; free(_hp); }
    (void)_t2329;
    if (_t2329) {
        Str *_t2263 = Str_lit("Bang", 4ULL);
        (void)_t2263;
        ;
        return _t2263;
    }
    ;
    Bool _t2330; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2330 = *_hp; free(_hp); }
    (void)_t2330;
    if (_t2330) {
        Str *_t2264 = Str_lit("Minus", 5ULL);
        (void)_t2264;
        ;
        return _t2264;
    }
    ;
    Bool _t2331; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2331 = *_hp; free(_hp); }
    (void)_t2331;
    if (_t2331) {
        Str *_t2265 = Str_lit("Plus", 4ULL);
        (void)_t2265;
        ;
        return _t2265;
    }
    ;
    Bool _t2332; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2332 = *_hp; free(_hp); }
    (void)_t2332;
    if (_t2332) {
        Str *_t2266 = Str_lit("Star", 4ULL);
        (void)_t2266;
        ;
        return _t2266;
    }
    ;
    Bool _t2333; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2333 = *_hp; free(_hp); }
    (void)_t2333;
    if (_t2333) {
        Str *_t2267 = Str_lit("Slash", 5ULL);
        (void)_t2267;
        ;
        return _t2267;
    }
    ;
    Bool _t2334; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2334 = *_hp; free(_hp); }
    (void)_t2334;
    if (_t2334) {
        Str *_t2268 = Str_lit("Dot", 3ULL);
        (void)_t2268;
        ;
        return _t2268;
    }
    ;
    Bool _t2335; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2335 = *_hp; free(_hp); }
    (void)_t2335;
    if (_t2335) {
        Str *_t2269 = Str_lit("DotDot", 6ULL);
        (void)_t2269;
        ;
        return _t2269;
    }
    ;
    Bool _t2336; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2336 = *_hp; free(_hp); }
    (void)_t2336;
    if (_t2336) {
        Str *_t2270 = Str_lit("DotDotDot", 9ULL);
        (void)_t2270;
        ;
        return _t2270;
    }
    ;
    Bool _t2337; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2337 = *_hp; free(_hp); }
    (void)_t2337;
    if (_t2337) {
        Str *_t2271 = Str_lit("Eq", 2ULL);
        (void)_t2271;
        ;
        return _t2271;
    }
    ;
    Bool _t2338; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2338 = *_hp; free(_hp); }
    (void)_t2338;
    if (_t2338) {
        Str *_t2272 = Str_lit("EqEq", 4ULL);
        (void)_t2272;
        ;
        return _t2272;
    }
    ;
    Bool _t2339; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2339 = *_hp; free(_hp); }
    (void)_t2339;
    if (_t2339) {
        Str *_t2273 = Str_lit("Neq", 3ULL);
        (void)_t2273;
        ;
        return _t2273;
    }
    ;
    Bool _t2340; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2340 = *_hp; free(_hp); }
    (void)_t2340;
    if (_t2340) {
        Str *_t2274 = Str_lit("Lt", 2ULL);
        (void)_t2274;
        ;
        return _t2274;
    }
    ;
    Bool _t2341; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2341 = *_hp; free(_hp); }
    (void)_t2341;
    if (_t2341) {
        Str *_t2275 = Str_lit("LtEq", 4ULL);
        (void)_t2275;
        ;
        return _t2275;
    }
    ;
    Bool _t2342; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2342 = *_hp; free(_hp); }
    (void)_t2342;
    if (_t2342) {
        Str *_t2276 = Str_lit("Gt", 2ULL);
        (void)_t2276;
        ;
        return _t2276;
    }
    ;
    Bool _t2343; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2343 = *_hp; free(_hp); }
    (void)_t2343;
    if (_t2343) {
        Str *_t2277 = Str_lit("GtEq", 4ULL);
        (void)_t2277;
        ;
        return _t2277;
    }
    ;
    Bool _t2344; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2344 = *_hp; free(_hp); }
    (void)_t2344;
    if (_t2344) {
        Str *_t2278 = Str_lit("ColonEq", 7ULL);
        (void)_t2278;
        ;
        return _t2278;
    }
    ;
    Bool _t2345; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2345 = *_hp; free(_hp); }
    (void)_t2345;
    if (_t2345) {
        Str *_t2279 = Str_lit("Ident", 5ULL);
        (void)_t2279;
        ;
        return _t2279;
    }
    ;
    Bool _t2346; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2346 = *_hp; free(_hp); }
    (void)_t2346;
    if (_t2346) {
        Str *_t2280 = Str_lit("StringTok", 9ULL);
        (void)_t2280;
        ;
        return _t2280;
    }
    ;
    Bool _t2347; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2347 = *_hp; free(_hp); }
    (void)_t2347;
    if (_t2347) {
        Str *_t2281 = Str_lit("Number", 6ULL);
        (void)_t2281;
        ;
        return _t2281;
    }
    ;
    Bool _t2348; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2348 = *_hp; free(_hp); }
    (void)_t2348;
    if (_t2348) {
        Str *_t2282 = Str_lit("Char", 4ULL);
        (void)_t2282;
        ;
        return _t2282;
    }
    ;
    Bool _t2349; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2349 = *_hp; free(_hp); }
    (void)_t2349;
    if (_t2349) {
        Str *_t2283 = Str_lit("KwMode", 6ULL);
        (void)_t2283;
        ;
        return _t2283;
    }
    ;
    Bool _t2350; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2350 = *_hp; free(_hp); }
    (void)_t2350;
    if (_t2350) {
        Str *_t2284 = Str_lit("KwMut", 5ULL);
        (void)_t2284;
        ;
        return _t2284;
    }
    ;
    Bool _t2351; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2351 = *_hp; free(_hp); }
    (void)_t2351;
    if (_t2351) {
        Str *_t2285 = Str_lit("KwOwn", 5ULL);
        (void)_t2285;
        ;
        return _t2285;
    }
    ;
    Bool _t2352; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2352 = *_hp; free(_hp); }
    (void)_t2352;
    if (_t2352) {
        Str *_t2286 = Str_lit("KwRef", 5ULL);
        (void)_t2286;
        ;
        return _t2286;
    }
    ;
    Bool _t2353; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2353 = *_hp; free(_hp); }
    (void)_t2353;
    if (_t2353) {
        Str *_t2287 = Str_lit("KwShallow", 9ULL);
        (void)_t2287;
        ;
        return _t2287;
    }
    ;
    Bool _t2354; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2354 = *_hp; free(_hp); }
    (void)_t2354;
    if (_t2354) {
        Str *_t2288 = Str_lit("KwStruct", 8ULL);
        (void)_t2288;
        ;
        return _t2288;
    }
    ;
    Bool _t2355; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2355 = *_hp; free(_hp); }
    (void)_t2355;
    if (_t2355) {
        Str *_t2289 = Str_lit("KwExtStruct", 11ULL);
        (void)_t2289;
        ;
        return _t2289;
    }
    ;
    Bool _t2356; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2356 = *_hp; free(_hp); }
    (void)_t2356;
    if (_t2356) {
        Str *_t2290 = Str_lit("KwEnum", 6ULL);
        (void)_t2290;
        ;
        return _t2290;
    }
    ;
    Bool _t2357; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2357 = *_hp; free(_hp); }
    (void)_t2357;
    if (_t2357) {
        Str *_t2291 = Str_lit("KwNamespace", 11ULL);
        (void)_t2291;
        ;
        return _t2291;
    }
    ;
    Bool _t2358; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2358 = *_hp; free(_hp); }
    (void)_t2358;
    if (_t2358) {
        Str *_t2292 = Str_lit("KwFunc", 6ULL);
        (void)_t2292;
        ;
        return _t2292;
    }
    ;
    Bool _t2359; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2359 = *_hp; free(_hp); }
    (void)_t2359;
    if (_t2359) {
        Str *_t2293 = Str_lit("KwProc", 6ULL);
        (void)_t2293;
        ;
        return _t2293;
    }
    ;
    Bool _t2360; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2360 = *_hp; free(_hp); }
    (void)_t2360;
    if (_t2360) {
        Str *_t2294 = Str_lit("KwTest", 6ULL);
        (void)_t2294;
        ;
        return _t2294;
    }
    ;
    Bool _t2361; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2361 = *_hp; free(_hp); }
    (void)_t2361;
    if (_t2361) {
        Str *_t2295 = Str_lit("KwMacro", 7ULL);
        (void)_t2295;
        ;
        return _t2295;
    }
    ;
    Bool _t2362; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2362 = *_hp; free(_hp); }
    (void)_t2362;
    if (_t2362) {
        Str *_t2296 = Str_lit("KwExtFunc", 9ULL);
        (void)_t2296;
        ;
        return _t2296;
    }
    ;
    Bool _t2363; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2363 = *_hp; free(_hp); }
    (void)_t2363;
    if (_t2363) {
        Str *_t2297 = Str_lit("KwExtProc", 9ULL);
        (void)_t2297;
        ;
        return _t2297;
    }
    ;
    Bool _t2364; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2364 = *_hp; free(_hp); }
    (void)_t2364;
    if (_t2364) {
        Str *_t2298 = Str_lit("KwReturns", 9ULL);
        (void)_t2298;
        ;
        return _t2298;
    }
    ;
    Bool _t2365; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2365 = *_hp; free(_hp); }
    (void)_t2365;
    if (_t2365) {
        Str *_t2299 = Str_lit("KwThrows", 8ULL);
        (void)_t2299;
        ;
        return _t2299;
    }
    ;
    Bool _t2366; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2366 = *_hp; free(_hp); }
    (void)_t2366;
    if (_t2366) {
        Str *_t2300 = Str_lit("KwIf", 4ULL);
        (void)_t2300;
        ;
        return _t2300;
    }
    ;
    Bool _t2367; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2367 = *_hp; free(_hp); }
    (void)_t2367;
    if (_t2367) {
        Str *_t2301 = Str_lit("KwElse", 6ULL);
        (void)_t2301;
        ;
        return _t2301;
    }
    ;
    Bool _t2368; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2368 = *_hp; free(_hp); }
    (void)_t2368;
    if (_t2368) {
        Str *_t2302 = Str_lit("KwWhile", 7ULL);
        (void)_t2302;
        ;
        return _t2302;
    }
    ;
    Bool _t2369; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2369 = *_hp; free(_hp); }
    (void)_t2369;
    if (_t2369) {
        Str *_t2303 = Str_lit("KwFor", 5ULL);
        (void)_t2303;
        ;
        return _t2303;
    }
    ;
    Bool _t2370; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2370 = *_hp; free(_hp); }
    (void)_t2370;
    if (_t2370) {
        Str *_t2304 = Str_lit("KwIn", 4ULL);
        (void)_t2304;
        ;
        return _t2304;
    }
    ;
    Bool _t2371; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2371 = *_hp; free(_hp); }
    (void)_t2371;
    if (_t2371) {
        Str *_t2305 = Str_lit("KwSwitch", 8ULL);
        (void)_t2305;
        ;
        return _t2305;
    }
    ;
    Bool _t2372; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2372 = *_hp; free(_hp); }
    (void)_t2372;
    if (_t2372) {
        Str *_t2306 = Str_lit("KwMatch", 7ULL);
        (void)_t2306;
        ;
        return _t2306;
    }
    ;
    Bool _t2373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2373 = *_hp; free(_hp); }
    (void)_t2373;
    if (_t2373) {
        Str *_t2307 = Str_lit("KwCase", 6ULL);
        (void)_t2307;
        ;
        return _t2307;
    }
    ;
    Bool _t2374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2374 = *_hp; free(_hp); }
    (void)_t2374;
    if (_t2374) {
        Str *_t2308 = Str_lit("KwDefault", 9ULL);
        (void)_t2308;
        ;
        return _t2308;
    }
    ;
    Bool _t2375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2375 = *_hp; free(_hp); }
    (void)_t2375;
    if (_t2375) {
        Str *_t2309 = Str_lit("KwReturn", 8ULL);
        (void)_t2309;
        ;
        return _t2309;
    }
    ;
    Bool _t2376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2376 = *_hp; free(_hp); }
    (void)_t2376;
    if (_t2376) {
        Str *_t2310 = Str_lit("KwThrow", 7ULL);
        (void)_t2310;
        ;
        return _t2310;
    }
    ;
    Bool _t2377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2377 = *_hp; free(_hp); }
    (void)_t2377;
    if (_t2377) {
        Str *_t2311 = Str_lit("KwCatch", 7ULL);
        (void)_t2311;
        ;
        return _t2311;
    }
    ;
    Bool _t2378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2378 = *_hp; free(_hp); }
    (void)_t2378;
    if (_t2378) {
        Str *_t2312 = Str_lit("KwBreak", 7ULL);
        (void)_t2312;
        ;
        return _t2312;
    }
    ;
    Bool _t2379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2379 = *_hp; free(_hp); }
    (void)_t2379;
    if (_t2379) {
        Str *_t2313 = Str_lit("KwContinue", 10ULL);
        (void)_t2313;
        ;
        return _t2313;
    }
    ;
    Bool _t2380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2380 = *_hp; free(_hp); }
    (void)_t2380;
    if (_t2380) {
        Str *_t2314 = Str_lit("KwDefer", 7ULL);
        (void)_t2314;
        ;
        return _t2314;
    }
    ;
    Bool _t2381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2381 = *_hp; free(_hp); }
    (void)_t2381;
    if (_t2381) {
        Str *_t2315 = Str_lit("KwTrue", 6ULL);
        (void)_t2315;
        ;
        return _t2315;
    }
    ;
    Bool _t2382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2382 = *_hp; free(_hp); }
    (void)_t2382;
    if (_t2382) {
        Str *_t2316 = Str_lit("KwFalse", 7ULL);
        (void)_t2316;
        ;
        return _t2316;
    }
    ;
    Bool _t2383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2383 = *_hp; free(_hp); }
    (void)_t2383;
    if (_t2383) {
        Str *_t2317 = Str_lit("KwNull", 6ULL);
        (void)_t2317;
        ;
        return _t2317;
    }
    ;
    Bool _t2384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t2384 = *_hp; free(_hp); }
    (void)_t2384;
    if (_t2384) {
        Str *_t2318 = Str_lit("Error", 5ULL);
        (void)_t2318;
        ;
        return _t2318;
    }
    ;
    Str *_t2385 = Str_lit("unknown", 7ULL);
    (void)_t2385;
    return _t2385;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


#include "til_core.c"
#include "til_array.c"
#include "til_map.c"
#include "til_set.c"
#include "til_str.c"
#include "til_vec.c"
#include "til_tuple.c"
#include "til_ast.c"
#include "til_lexer.c"
#include "til_parser.c"
#include "til_initer.c"
#include "til_typer.c"
#include "til_dispatch.c"
#include "til_modes.c"
#include "til_til.c"

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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "LocalInfo", 9ULL) == 0) { LocalInfo_delete(val, arg2); return; }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "ExtStr", 6ULL) == 0) { ExtStr_delete(val, arg2); return; }
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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "LocalInfo", 9ULL) == 0) return (void *)LocalInfo_clone(val);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "ExtStr", 6ULL) == 0) return (void *)ExtStr_clone(val);
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

void *U8_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_to_i64(*(U8 *)_a0); return _r;
}
void *U8_add_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_add(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_sub_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_sub(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_mul_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_mul(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_div_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_div(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_mod_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_mod(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_eq(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_and_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_and(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_or_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_or(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_xor_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_xor(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
void *I16_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I16_to_i64(*(I16 *)_a0); return _r;
}
void *I16_add_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_add(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_sub_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_sub(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_mul_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_mul(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_div_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_div(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_mod_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_mod(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_eq(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I16_cmp(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_and_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_and(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_or_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_or(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_xor_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_xor(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_clone_dyn(void *_a0) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_clone(_a0); return _r;
}
void *I32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_to_i64(*(I32 *)_a0); return _r;
}
void *I32_add_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_add(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_sub_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_sub(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_mul_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_mul(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_div_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_div(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_mod_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_mod(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_eq(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_and_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_and(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_or_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_or(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_xor_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_xor(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_clone_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
void *F32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_to_i64(*(F32 *)_a0); return _r;
}
void *F32_to_str_dyn(void *_a0) {
    return (void *)F32_to_str(*(F32 *)_a0);
}
void *F32_add_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_add(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_sub_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_sub(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_mul_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_mul(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_div_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_div(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_eq(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
void *U32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_to_i64(*(U32 *)_a0); return _r;
}
void *U32_add_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_add(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_sub_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_sub(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_mul_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_mul(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_div_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_div(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_mod_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_mod(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_eq(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_and_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_and(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_or_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_or(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_xor_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_xor(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_clone_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
void *U64_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_to_i64(*(U64 *)_a0); return _r;
}
void *U64_to_str_dyn(void *_a0) {
    return (void *)U64_to_str(*(U64 *)_a0);
}
void *U64_add_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_add(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_sub_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_sub(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_mul_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_mul(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_div_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_div(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_mod_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_mod(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_eq(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_and_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_and(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_or_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_or(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_xor_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_xor(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_clone_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
void *I64_to_u8_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = I64_to_u8(*(I64 *)_a0); return _r;
}
void *I64_to_i16_dyn(void *_a0) {
    I16 *_r = malloc(sizeof(I16)); *_r = I64_to_i16(*(I64 *)_a0); return _r;
}
void *I64_to_i32_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I64_to_i32(*(I64 *)_a0); return _r;
}
void *I64_to_u32_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = I64_to_u32(*(I64 *)_a0); return _r;
}
void *I64_to_u64_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = I64_to_u64(*(I64 *)_a0); return _r;
}
void *I64_to_f32_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = I64_to_f32(*(I64 *)_a0); return _r;
}
void *I64_add_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_add(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_sub_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_sub(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_mul_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_mul(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_div_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_div(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_mod_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_mod(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_eq(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_and_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_and(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_or_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_or(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_xor_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_xor(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_clone_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
void *Range_new_dyn(void *_a0, void *_a1) {
    return (void *)Range_new(*(U64 *)_a0, *(U64 *)_a1);
}
void *Range_get_dyn(void *_a0, void *_a1) {
    return (void *)Range_get(_a0, *(U64 *)_a1);
}
void *Bool_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_eq(*(Bool *)_a0, *(Bool *)_a1); return _r;
}
void *Bool_clone_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
void *Expr_new_dyn(void *_a0, void *_a1, void *_a2, void *_a3) {
    return (void *)Expr_new(_a0, *(U32 *)_a1, *(U32 *)_a2, _a3);
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)EnumDef_clone;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)EnumDef_delete;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)EnumDef_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U8_to_i64_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U8_to_str;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U8_add_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U8_sub_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U8_mul_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U8_div_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U8_mod_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U8_inc;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U8_dec;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U8_unity;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U8_eq_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U8_and_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U8_or_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U8_xor_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U8_lt;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U8_gt;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U8_neq;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U8_lte;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U8_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)I16_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I16_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I16_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I16_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I16_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I16_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I16_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I16_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I16_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I16_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I16_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I16_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I16_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I16_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I16_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I16_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I16_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I16_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I16_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I16_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I16_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I16_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I16_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I16_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I16_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)I32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I32_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I32_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I32_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I32_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I32_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I32_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I32_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I32_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I32_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I32_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I32_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I32_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)F32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)F32_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "from_i64", 8ULL) == 0) return (void*)F32_from_i64;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)F32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)F32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)F32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)F32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)F32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)F32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)F32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)F32_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)F32_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)F32_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)F32_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)F32_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U32_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U32_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U32_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U32_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U32_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U32_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U64_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U64_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "from_i64", 8ULL) == 0) return (void*)U64_from_i64;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U64_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U64_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U64_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U64_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U64_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U64_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U64_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U64_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U64_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U64_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U64_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U64_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I64_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)I64_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i16", 6ULL) == 0) return (void*)I64_to_i16_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i32", 6ULL) == 0) return (void*)I64_to_i32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u32", 6ULL) == 0) return (void*)I64_to_u32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u64", 6ULL) == 0) return (void*)I64_to_u64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_f32", 6ULL) == 0) return (void*)I64_to_f32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I64_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I64_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I64_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I64_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I64_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I64_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I64_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I64_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I64_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I64_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I64_gte;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Range_new_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Range_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Range_get_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Range_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Range_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Range_size;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Bool_to_str;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)Bool_lt;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)Bool_gt;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)Bool_neq;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)Bool_lte;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)Bool_gte;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Map_new;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Map_len;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "has", 3ULL) == 0) return (void*)Map_has;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Map_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Map_set;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Map_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Map_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Map_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Set_new;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Set_len;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "has", 3ULL) == 0) return (void*)Set_has;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)Set_add;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Set_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Set_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Set_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Str_len;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Str_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "byte_at", 7ULL) == 0) return (void*)Str_byte_at;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Str_cmp;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "concat", 6ULL) == 0) return (void*)Str_concat;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)Str_with_capacity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)Str_push_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Str_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Str_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Str_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "substr", 6ULL) == 0) return (void*)Str_substr;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "contains", 8ULL) == 0) return (void*)Str_contains;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "starts_with", 11ULL) == 0) return (void*)Str_starts_with;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "ends_with", 9ULL) == 0) return (void*)Str_ends_with;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)Str_is_empty;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "find", 4ULL) == 0) return (void*)Str_find;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "rfind", 5ULL) == 0) return (void*)Str_rfind;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "replace", 7ULL) == 0) return (void*)Str_replace;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "get_char", 8ULL) == 0) return (void*)Str_get_char;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "strip_prefix", 12ULL) == 0) return (void*)Str_strip_prefix;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "strip_suffix", 12ULL) == 0) return (void*)Str_strip_suffix;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "from_byte", 9ULL) == 0) return (void*)Str_from_byte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)Str_to_i64;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "split", 5ULL) == 0) return (void*)Str_split;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Str_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Str_eq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)Str_lt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)Str_gt;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)Str_neq;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)Str_lte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)Str_gte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Vec_new;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Vec_len;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "push", 4ULL) == 0) return (void*)Vec_push;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Vec_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Vec_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Vec_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Vec_size;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Tuple_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Tuple_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "push", 4ULL) == 0) return (void*)Tuple_push;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Tuple_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "type_at", 7ULL) == 0) return (void*)Tuple_type_at;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "size_at", 7ULL) == 0) return (void*)Tuple_size_at;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Tuple_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Tuple_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Tuple_size;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_Unknown", 10ULL) == 0) return (void*)TilType_is_Unknown;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_None", 7ULL) == 0) return (void*)TilType_is_None;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_I64", 6ULL) == 0) return (void*)TilType_is_I64;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "is_U8", 5ULL) == 0) return (void*)TilType_is_U8;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_I16", 6ULL) == 0) return (void*)TilType_is_I16;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_I32", 6ULL) == 0) return (void*)TilType_is_I32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_U32", 6ULL) == 0) return (void*)TilType_is_U32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_U64", 6ULL) == 0) return (void*)TilType_is_U64;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_F32", 6ULL) == 0) return (void*)TilType_is_F32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Bool", 7ULL) == 0) return (void*)TilType_is_Bool;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_Struct", 9ULL) == 0) return (void*)TilType_is_Struct;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_StructDef", 12ULL) == 0) return (void*)TilType_is_StructDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Enum", 7ULL) == 0) return (void*)TilType_is_Enum;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_EnumDef", 10ULL) == 0) return (void*)TilType_is_EnumDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_FuncDef", 10ULL) == 0) return (void*)TilType_is_FuncDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_FuncPtr", 10ULL) == 0) return (void*)TilType_is_FuncPtr;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_Dynamic", 10ULL) == 0) return (void*)TilType_is_Dynamic;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)TilType_eq;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)TilType_clone;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)TilType_delete;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)TilType_to_str;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)TilType_size;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Declaration_eq;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Declaration_to_str;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Declaration_clone;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Declaration_delete;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Declaration_size;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Func", 7ULL) == 0) return (void*)FuncType_is_Func;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Proc", 7ULL) == 0) return (void*)FuncType_is_Proc;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Test", 7ULL) == 0) return (void*)FuncType_is_Test;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Macro", 8ULL) == 0) return (void*)FuncType_is_Macro;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_ExtFunc", 10ULL) == 0) return (void*)FuncType_is_ExtFunc;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_ExtProc", 10ULL) == 0) return (void*)FuncType_is_ExtProc;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)FuncType_eq;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)FuncType_clone;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)FuncType_delete;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)FuncType_to_str;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)FuncType_size;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Param_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Param_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Param", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Param_size;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)FunctionDef_eq;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)FunctionDef_to_str;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)FunctionDef_clone;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)FunctionDef_delete;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)FunctionDef_size;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Body", 4ULL) == 0) return (void*)ExprData_Body;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "LiteralStr", 10ULL) == 0) return (void*)ExprData_LiteralStr;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "LiteralNum", 10ULL) == 0) return (void*)ExprData_LiteralNum;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "LiteralBool", 11ULL) == 0) return (void*)ExprData_LiteralBool;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "LiteralNull", 11ULL) == 0) return (void*)ExprData_LiteralNull;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Ident", 5ULL) == 0) return (void*)ExprData_Ident;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Decl", 4ULL) == 0) return (void*)ExprData_Decl;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Assign", 6ULL) == 0) return (void*)ExprData_Assign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "FCall", 5ULL) == 0) return (void*)ExprData_FCall;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)ExprData_FuncDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)ExprData_StructDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)ExprData_EnumDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "FieldAccess", 11ULL) == 0) return (void*)ExprData_FieldAccess;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "FieldAssign", 11ULL) == 0) return (void*)ExprData_FieldAssign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Return", 6ULL) == 0) return (void*)ExprData_Return;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "If", 2ULL) == 0) return (void*)ExprData_If;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "While", 5ULL) == 0) return (void*)ExprData_While;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "ForIn", 5ULL) == 0) return (void*)ExprData_ForIn;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "NamedArg", 8ULL) == 0) return (void*)ExprData_NamedArg;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "Break", 5ULL) == 0) return (void*)ExprData_Break;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "Continue", 8ULL) == 0) return (void*)ExprData_Continue;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "MapLit", 6ULL) == 0) return (void*)ExprData_MapLit;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "SetLit", 6ULL) == 0) return (void*)ExprData_SetLit;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Switch", 6ULL) == 0) return (void*)ExprData_Switch;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Case", 4ULL) == 0) return (void*)ExprData_Case;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "get_LiteralStr", 14ULL) == 0) return (void*)ExprData_get_LiteralStr;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "get_LiteralNum", 14ULL) == 0) return (void*)ExprData_get_LiteralNum;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 15ULL && memcmp(method->c_str, "get_LiteralBool", 15ULL) == 0) return (void*)ExprData_get_LiteralBool;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "get_Ident", 9ULL) == 0) return (void*)ExprData_get_Ident;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "get_Decl", 8ULL) == 0) return (void*)ExprData_get_Decl;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "get_Assign", 10ULL) == 0) return (void*)ExprData_get_Assign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "get_FuncDef", 11ULL) == 0) return (void*)ExprData_get_FuncDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 15ULL && memcmp(method->c_str, "get_FieldAccess", 15ULL) == 0) return (void*)ExprData_get_FieldAccess;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 15ULL && memcmp(method->c_str, "get_FieldAssign", 15ULL) == 0) return (void*)ExprData_get_FieldAssign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "get_ForIn", 9ULL) == 0) return (void*)ExprData_get_ForIn;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "get_NamedArg", 12ULL) == 0) return (void*)ExprData_get_NamedArg;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Body", 7ULL) == 0) return (void*)ExprData_is_Body;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "is_LiteralStr", 13ULL) == 0) return (void*)ExprData_is_LiteralStr;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "is_LiteralNum", 13ULL) == 0) return (void*)ExprData_is_LiteralNum;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_LiteralBool", 14ULL) == 0) return (void*)ExprData_is_LiteralBool;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_LiteralNull", 14ULL) == 0) return (void*)ExprData_is_LiteralNull;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Ident", 8ULL) == 0) return (void*)ExprData_is_Ident;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Decl", 7ULL) == 0) return (void*)ExprData_is_Decl;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_Assign", 9ULL) == 0) return (void*)ExprData_is_Assign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_FCall", 8ULL) == 0) return (void*)ExprData_is_FCall;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_FuncDef", 10ULL) == 0) return (void*)ExprData_is_FuncDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_StructDef", 12ULL) == 0) return (void*)ExprData_is_StructDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_EnumDef", 10ULL) == 0) return (void*)ExprData_is_EnumDef;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_FieldAccess", 14ULL) == 0) return (void*)ExprData_is_FieldAccess;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_FieldAssign", 14ULL) == 0) return (void*)ExprData_is_FieldAssign;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_Return", 9ULL) == 0) return (void*)ExprData_is_Return;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "is_If", 5ULL) == 0) return (void*)ExprData_is_If;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_While", 8ULL) == 0) return (void*)ExprData_is_While;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_ForIn", 8ULL) == 0) return (void*)ExprData_is_ForIn;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_NamedArg", 11ULL) == 0) return (void*)ExprData_is_NamedArg;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Break", 8ULL) == 0) return (void*)ExprData_is_Break;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_Continue", 11ULL) == 0) return (void*)ExprData_is_Continue;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_MapLit", 9ULL) == 0) return (void*)ExprData_is_MapLit;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_SetLit", 9ULL) == 0) return (void*)ExprData_is_SetLit;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_Switch", 9ULL) == 0) return (void*)ExprData_is_Switch;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Case", 7ULL) == 0) return (void*)ExprData_is_Case;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)ExprData_eq;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)ExprData_clone;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)ExprData_delete;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)ExprData_to_str;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)ExprData_size;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "error", 5ULL) == 0) return (void*)Expr_error;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "todo_error", 10ULL) == 0) return (void*)Expr_todo_error;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "lang_error", 10ULL) == 0) return (void*)Expr_lang_error;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "add_child", 9ULL) == 0) return (void*)Expr_add_child;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "child", 5ULL) == 0) return (void*)Expr_child;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "child_count", 11ULL) == 0) return (void*)Expr_child_count;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Expr_new_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Expr_clone;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Expr_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Expr_size;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_Eof", 6ULL) == 0) return (void*)TokenType_is_Eof;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_LParen", 9ULL) == 0) return (void*)TokenType_is_LParen;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_RParen", 9ULL) == 0) return (void*)TokenType_is_RParen;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_LBrace", 9ULL) == 0) return (void*)TokenType_is_LBrace;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_RBrace", 9ULL) == 0) return (void*)TokenType_is_RBrace;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_LBracket", 11ULL) == 0) return (void*)TokenType_is_LBracket;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_RBracket", 11ULL) == 0) return (void*)TokenType_is_RBracket;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Comma", 8ULL) == 0) return (void*)TokenType_is_Comma;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Colon", 8ULL) == 0) return (void*)TokenType_is_Colon;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_Question", 11ULL) == 0) return (void*)TokenType_is_Question;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Bang", 7ULL) == 0) return (void*)TokenType_is_Bang;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Minus", 8ULL) == 0) return (void*)TokenType_is_Minus;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Plus", 7ULL) == 0) return (void*)TokenType_is_Plus;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Star", 7ULL) == 0) return (void*)TokenType_is_Star;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Slash", 8ULL) == 0) return (void*)TokenType_is_Slash;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_Dot", 6ULL) == 0) return (void*)TokenType_is_Dot;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_DotDot", 9ULL) == 0) return (void*)TokenType_is_DotDot;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_DotDotDot", 12ULL) == 0) return (void*)TokenType_is_DotDotDot;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "is_Eq", 5ULL) == 0) return (void*)TokenType_is_Eq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_EqEq", 7ULL) == 0) return (void*)TokenType_is_EqEq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "is_Neq", 6ULL) == 0) return (void*)TokenType_is_Neq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "is_Lt", 5ULL) == 0) return (void*)TokenType_is_Lt;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_LtEq", 7ULL) == 0) return (void*)TokenType_is_LtEq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "is_Gt", 5ULL) == 0) return (void*)TokenType_is_Gt;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_GtEq", 7ULL) == 0) return (void*)TokenType_is_GtEq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_ColonEq", 10ULL) == 0) return (void*)TokenType_is_ColonEq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Ident", 8ULL) == 0) return (void*)TokenType_is_Ident;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_StringTok", 12ULL) == 0) return (void*)TokenType_is_StringTok;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_Number", 9ULL) == 0) return (void*)TokenType_is_Number;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_Char", 7ULL) == 0) return (void*)TokenType_is_Char;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwMode", 9ULL) == 0) return (void*)TokenType_is_KwMode;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_KwMut", 8ULL) == 0) return (void*)TokenType_is_KwMut;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_KwOwn", 8ULL) == 0) return (void*)TokenType_is_KwOwn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_KwRef", 8ULL) == 0) return (void*)TokenType_is_KwRef;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_KwShallow", 12ULL) == 0) return (void*)TokenType_is_KwShallow;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_KwStruct", 11ULL) == 0) return (void*)TokenType_is_KwStruct;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_KwExtStruct", 14ULL) == 0) return (void*)TokenType_is_KwExtStruct;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwEnum", 9ULL) == 0) return (void*)TokenType_is_KwEnum;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "is_KwNamespace", 14ULL) == 0) return (void*)TokenType_is_KwNamespace;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwFunc", 9ULL) == 0) return (void*)TokenType_is_KwFunc;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwProc", 9ULL) == 0) return (void*)TokenType_is_KwProc;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwTest", 9ULL) == 0) return (void*)TokenType_is_KwTest;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwMacro", 10ULL) == 0) return (void*)TokenType_is_KwMacro;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_KwExtFunc", 12ULL) == 0) return (void*)TokenType_is_KwExtFunc;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_KwExtProc", 12ULL) == 0) return (void*)TokenType_is_KwExtProc;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_KwReturns", 12ULL) == 0) return (void*)TokenType_is_KwReturns;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_KwThrows", 11ULL) == 0) return (void*)TokenType_is_KwThrows;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_KwIf", 7ULL) == 0) return (void*)TokenType_is_KwIf;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwElse", 9ULL) == 0) return (void*)TokenType_is_KwElse;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwWhile", 10ULL) == 0) return (void*)TokenType_is_KwWhile;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_KwFor", 8ULL) == 0) return (void*)TokenType_is_KwFor;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "is_KwIn", 7ULL) == 0) return (void*)TokenType_is_KwIn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_KwSwitch", 11ULL) == 0) return (void*)TokenType_is_KwSwitch;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwMatch", 10ULL) == 0) return (void*)TokenType_is_KwMatch;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwCase", 9ULL) == 0) return (void*)TokenType_is_KwCase;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "is_KwDefault", 12ULL) == 0) return (void*)TokenType_is_KwDefault;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "is_KwReturn", 11ULL) == 0) return (void*)TokenType_is_KwReturn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwThrow", 10ULL) == 0) return (void*)TokenType_is_KwThrow;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwCatch", 10ULL) == 0) return (void*)TokenType_is_KwCatch;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwBreak", 10ULL) == 0) return (void*)TokenType_is_KwBreak;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "is_KwContinue", 13ULL) == 0) return (void*)TokenType_is_KwContinue;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwDefer", 10ULL) == 0) return (void*)TokenType_is_KwDefer;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwTrue", 9ULL) == 0) return (void*)TokenType_is_KwTrue;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "is_KwFalse", 10ULL) == 0) return (void*)TokenType_is_KwFalse;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "is_KwNull", 9ULL) == 0) return (void*)TokenType_is_KwNull;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_Error", 8ULL) == 0) return (void*)TokenType_is_Error;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)TokenType_eq;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)TokenType_clone;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)TokenType_delete;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)TokenType_to_str;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)TokenType_size;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Token_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Token_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Token_size;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Parser_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Parser_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "Parser", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Parser_size;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)TypeBinding_clone;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)TypeBinding_delete;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "TypeBinding", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)TypeBinding_size;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)TypeScope_clone;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)TypeScope_delete;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)TypeScope_size;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "LocalInfo", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)LocalInfo_clone;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "LocalInfo", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)LocalInfo_delete;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "LocalInfo", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)LocalInfo_size;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "ExtStr", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)ExtStr_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "ExtStr", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)ExtStr_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "ExtStr", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)ExtStr_size;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Mode_eq;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Mode_clone;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Mode_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Mode_size;
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

