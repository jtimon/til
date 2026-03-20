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

static I64 *_t4865;
static I64 *_t4866;
static I64 *_t4867;
static U64 *CAP_LIT;
static I64 *_t4868;
static I64 *_t4869;
static I64 *_t4870;
static U64 *CAP_VIEW;
static Str *_t4871;
static U64 *_t4872;
static Str *_t4873;
static U64 *_t4874;
static Map *core_modes;
static Bool *_t4875;
static Bool *_t4876;
static Bool *_t4877;
static Bool *_t4878;
static Str *_t4879;
static Mode *_t4880;
static Bool *_t4881;
static Bool *_t4882;
static Bool *_t4883;
static Bool *_t4884;
static Str *_t4885;
static Mode *_t4886;
static Bool *_t4887;
static Bool *_t4888;
static Bool *_t4889;
static Bool *_t4890;
static Str *_t4891;
static Mode *_t4892;
static Bool *_t4893;
static Bool *_t4894;
static Bool *_t4895;
static Bool *_t4896;
static Str *_t4897;
static Mode *_t4898;
static Bool *_t4899;
static Bool *_t4900;
static Bool *_t4901;
static Bool *_t4902;
static Str *_t4903;
static Mode *_t4904;
static Bool *_t4905;
static Bool *_t4906;
static Bool *_t4907;
static Bool *_t4908;
static Str *_t4909;
static Mode *_t4910;
static Bool *_t4911;
static Bool *_t4912;
static Bool *_t4913;
static Bool *_t4914;
static Str *_t4915;
static Mode *_t4916;
static Bool *_t4917;
static Bool *_t4918;
static Bool *_t4919;
static Bool *_t4920;
static Str *_t4921;
static Mode *_t4922;
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
        U64 _fi425 = 0;
        (void)_fi425;
        while (1) {
            U64 _t427 = 0;
            (void)_t427;
            Range *_t428 = Range_new(_t427, self->cap);
            (void)_t428;
            ;
            U64 _t429; { U64 *_hp = (U64 *)Range_len(_t428); _t429 = *_hp; free(_hp); }
            (void)_t429;
            Range_delete(_t428, &(Bool){1});
            Bool _wcond426; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi425}, &(U64){_t429}); _wcond426 = *_hp; free(_hp); }
            (void)_wcond426;
            ;
            if (_wcond426) {
            } else {
                ;
                break;
            }
            ;
            U64 _t430 = 0;
            (void)_t430;
            Range *_t431 = Range_new(_t430, self->cap);
            (void)_t431;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t431, _fi425); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t431, &(Bool){1});
            U64 _t432 = 1;
            (void)_t432;
            U64 _t433 = U64_add(_fi425, _t432);
            (void)_t433;
            ;
            _fi425 = _t433;
            ;
            U64 *_t434 = malloc(sizeof(U64)); *_t434 = U64_mul(i, self->elem_size);
            (void)_t434;
            ;
            void *_t435 = ptr_add(self->data, DEREF(_t434));
            (void)_t435;
            Bool _t436 = 0;
            (void)_t436;
            dyn_call_delete(&self->elem_type, _t435, &(Bool){_t436});
            U64_delete(_t434, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t437 = 0;
    (void)_t437;
    Str_delete(&self->elem_type, &(Bool){_t437});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t451 = U64_mul(self->cap, self->elem_size);
    (void)_t451;
    U8 *new_data = malloc(_t451);
    (void)new_data;
    ;
    {
        U64 _fi438 = 0;
        (void)_fi438;
        while (1) {
            U64 _t440 = 0;
            (void)_t440;
            Range *_t441 = Range_new(_t440, self->cap);
            (void)_t441;
            ;
            U64 _t442; { U64 *_hp = (U64 *)Range_len(_t441); _t442 = *_hp; free(_hp); }
            (void)_t442;
            Range_delete(_t441, &(Bool){1});
            Bool _wcond439; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi438}, &(U64){_t442}); _wcond439 = *_hp; free(_hp); }
            (void)_wcond439;
            ;
            if (_wcond439) {
            } else {
                ;
                break;
            }
            ;
            U64 _t443 = 0;
            (void)_t443;
            Range *_t444 = Range_new(_t443, self->cap);
            (void)_t444;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t444, _fi438); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t444, &(Bool){1});
            U64 _t445 = 1;
            (void)_t445;
            U64 _t446 = U64_add(_fi438, _t445);
            (void)_t446;
            ;
            _fi438 = _t446;
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
        ;
    }
    Array *_t452 = malloc(sizeof(Array));
    _t452->data = new_data;
    _t452->cap = self->cap;
    _t452->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t452->elem_type = *_ca; free(_ca); }
    (void)_t452;
    return _t452;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t466; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t466 = *_hp; free(_hp); }
    (void)_t466;
    Bool _t467 = Bool_not(_t466);
    (void)_t467;
    ;
    if (_t467) {
        Bool _t464 = dyn_has_cmp(key_type);
        (void)_t464;
        Bool _t465 = Bool_not(_t464);
        (void)_t465;
        ;
        if (_t465) {
            Str *_t454 = Str_lit("Str", 3ULL);
            (void)_t454;
            U64 _t455; { U64 *_hp = (U64 *)Str_size(); _t455 = *_hp; free(_hp); }
            (void)_t455;
            U64 _t456 = 3;
            (void)_t456;
            Array *_va9 = Array_new(_t454, &(U64){_t455}, &(U64){_t456});
            (void)_va9;
            Str_delete(_t454, &(Bool){1});
            ;
            ;
            U64 _t457 = 0;
            (void)_t457;
            Str *_t458 = Str_lit("Map.new: type ", 14ULL);
            (void)_t458;
            Array_set(_va9, &(U64){_t457}, _t458);
            ;
            U64 _t459 = 1;
            (void)_t459;
            Str *_t460 = Str_clone(key_type);
            (void)_t460;
            Array_set(_va9, &(U64){_t459}, _t460);
            ;
            U64 _t461 = 2;
            (void)_t461;
            Str *_t462 = Str_lit(" must implement cmp", 19ULL);
            (void)_t462;
            Array_set(_va9, &(U64){_t461}, _t462);
            ;
            Str *_t463 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t463;
            panic(_t463, _va9);
            Str_delete(_t463, &(Bool){1});
        }
        ;
    }
    ;
    void *_t468 = malloc(DEREF(key_size));
    (void)_t468;
    void *_t469 = malloc(DEREF(val_size));
    (void)_t469;
    U64 _t470 = 0;
    (void)_t470;
    I64 _t471 = 1;
    (void)_t471;
    U64 _t472 = U64_clone(key_size);
    (void)_t472;
    U64 _t473 = U64_clone(val_size);
    (void)_t473;
    Map *_t474 = malloc(sizeof(Map));
    _t474->key_data = _t468;
    _t474->val_data = _t469;
    _t474->count = _t470;
    _t474->cap = _t471;
    _t474->key_size = _t472;
    { Str *_ca = Str_clone(key_type); _t474->key_type = *_ca; free(_ca); }
    _t474->val_size = _t473;
    { Str *_ca = Str_clone(val_type); _t474->val_type = *_ca; free(_ca); }
    (void)_t474;
    ;
    ;
    ;
    ;
    return _t474;
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
        Bool _wcond475; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond475 = *_hp; free(_hp); }
        (void)_wcond475;
        if (_wcond475) {
        } else {
            ;
            break;
        }
        ;
        U64 _t482 = U64_sub(hi, lo);
        (void)_t482;
        U64 _t483 = 2;
        (void)_t483;
        U64 _t484 = U64_div(_t482, _t483);
        (void)_t484;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t484);
        (void)mid;
        ;
        U64 *_t485 = malloc(sizeof(U64)); *_t485 = U64_mul(DEREF(mid), self->key_size);
        (void)_t485;
        void *_t486 = ptr_add(self->key_data, DEREF(_t485));
        (void)_t486;
        I64 *c = dyn_call_cmp(&self->key_type, _t486, key);
        (void)c;
        U64_delete(_t485, &(Bool){1});
        I64 _t487 = 0;
        (void)_t487;
        Bool _t488; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t487}); _t488 = *_hp; free(_hp); }
        (void)_t488;
        ;
        if (_t488) {
            U64 _t476 = 1;
            (void)_t476;
            U64 _t477 = U64_add(DEREF(mid), _t476);
            (void)_t477;
            ;
            lo = _t477;
            ;
        } else {
            I64 _t480 = 0;
            (void)_t480;
            Bool _t481; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t480}); _t481 = *_hp; free(_hp); }
            (void)_t481;
            ;
            if (_t481) {
                U64 _t478 = U64_clone(mid);
                (void)_t478;
                hi = _t478;
                ;
            } else {
                Bool _t479 = 1;
                (void)_t479;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t479; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t489 = 0;
    (void)_t489;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t489; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond490; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond490 = *_hp; free(_hp); }
        (void)_wcond490;
        if (_wcond490) {
        } else {
            ;
            break;
        }
        ;
        U64 _t498 = U64_sub(hi, lo);
        (void)_t498;
        U64 _t499 = 2;
        (void)_t499;
        U64 _t500 = U64_div(_t498, _t499);
        (void)_t500;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t500);
        (void)mid;
        ;
        U64 *_t501 = malloc(sizeof(U64)); *_t501 = U64_mul(DEREF(mid), self->key_size);
        (void)_t501;
        void *_t502 = ptr_add(self->key_data, DEREF(_t501));
        (void)_t502;
        I64 *c = dyn_call_cmp(&self->key_type, _t502, key);
        (void)c;
        U64_delete(_t501, &(Bool){1});
        I64 _t503 = 0;
        (void)_t503;
        Bool _t504; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t503}); _t504 = *_hp; free(_hp); }
        (void)_t504;
        ;
        if (_t504) {
            U64 _t491 = 1;
            (void)_t491;
            U64 _t492 = U64_add(DEREF(mid), _t491);
            (void)_t492;
            ;
            lo = _t492;
            ;
        } else {
            I64 _t496 = 0;
            (void)_t496;
            Bool _t497; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t496}); _t497 = *_hp; free(_hp); }
            (void)_t497;
            ;
            if (_t497) {
                U64 _t493 = U64_clone(mid);
                (void)_t493;
                hi = _t493;
                ;
            } else {
                U64 *_t494 = malloc(sizeof(U64)); *_t494 = U64_mul(DEREF(mid), self->val_size);
                (void)_t494;
                void *_t495 = ptr_add(self->val_data, DEREF(_t494));
                (void)_t495;
                U64_delete(_t494, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t495;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t505 = Str_lit("Str", 3ULL);
    (void)_t505;
    U64 _t506; { U64 *_hp = (U64 *)Str_size(); _t506 = *_hp; free(_hp); }
    (void)_t506;
    U64 _t507 = 1;
    (void)_t507;
    Array *_va10 = Array_new(_t505, &(U64){_t506}, &(U64){_t507});
    (void)_va10;
    Str_delete(_t505, &(Bool){1});
    ;
    ;
    U64 _t508 = 0;
    (void)_t508;
    Str *_t509 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t509;
    Array_set(_va10, &(U64){_t508}, _t509);
    ;
    Str *_t510 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t510;
    panic(_t510, _va10);
    Str_delete(_t510, &(Bool){1});
    U64 *_t511 = malloc(sizeof(U64));
    *_t511 = 0;
    (void)_t511;
    void *_t512 = ptr_add(self->val_data, DEREF(_t511));
    (void)_t512;
    U64_delete(_t511, &(Bool){1});
    return _t512;
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
        Bool _wcond513; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond513 = *_hp; free(_hp); }
        (void)_wcond513;
        if (_wcond513) {
        } else {
            ;
            break;
        }
        ;
        U64 _t522 = U64_sub(hi, lo);
        (void)_t522;
        U64 _t523 = 2;
        (void)_t523;
        U64 _t524 = U64_div(_t522, _t523);
        (void)_t524;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t524);
        (void)mid;
        ;
        U64 *_t525 = malloc(sizeof(U64)); *_t525 = U64_mul(DEREF(mid), self->key_size);
        (void)_t525;
        void *_t526 = ptr_add(self->key_data, DEREF(_t525));
        (void)_t526;
        I64 *c = dyn_call_cmp(&self->key_type, _t526, key);
        (void)c;
        U64_delete(_t525, &(Bool){1});
        I64 _t527 = 0;
        (void)_t527;
        Bool _t528; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t527}); _t528 = *_hp; free(_hp); }
        (void)_t528;
        ;
        if (_t528) {
            U64 _t514 = 1;
            (void)_t514;
            U64 _t515 = U64_add(DEREF(mid), _t514);
            (void)_t515;
            ;
            lo = _t515;
            ;
        } else {
            I64 _t520 = 0;
            (void)_t520;
            Bool _t521; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t520}); _t521 = *_hp; free(_hp); }
            (void)_t521;
            ;
            if (_t521) {
                U64 _t516 = U64_clone(mid);
                (void)_t516;
                hi = _t516;
                ;
            } else {
                Bool _t517 = 1;
                (void)_t517;
                found = _t517;
                ;
                U64 _t518 = U64_clone(mid);
                (void)_t518;
                lo = _t518;
                ;
                U64 _t519 = U64_clone(mid);
                (void)_t519;
                hi = _t519;
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
        Bool _t533; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t533 = *_hp; free(_hp); }
        (void)_t533;
        Bool _t534 = Bool_not(_t533);
        (void)_t534;
        ;
        if (_t534) {
            Bool _t529 = 0;
            (void)_t529;
            dyn_call_delete(&self->key_type, key, &(Bool){_t529});
            ;
        }
        ;
        free(key);
        Bool _t535; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t535 = *_hp; free(_hp); }
        (void)_t535;
        Bool _t536 = Bool_not(_t535);
        (void)_t536;
        ;
        if (_t536) {
            U64 *_t530 = malloc(sizeof(U64)); *_t530 = U64_mul(lo, self->val_size);
            (void)_t530;
            void *_t531 = ptr_add(self->val_data, DEREF(_t530));
            (void)_t531;
            Bool _t532 = 0;
            (void)_t532;
            dyn_call_delete(&self->val_type, _t531, &(Bool){_t532});
            U64_delete(_t530, &(Bool){1});
            ;
        }
        ;
        U64 *_t537 = malloc(sizeof(U64)); *_t537 = U64_mul(lo, self->val_size);
        (void)_t537;
        void *_t538 = ptr_add(self->val_data, DEREF(_t537));
        (void)_t538;
        memcpy(_t538, val, self->val_size);
        U64_delete(_t537, &(Bool){1});
        free(val);
    } else {
        Bool _t545 = U64_eq(self->count, self->cap);
        (void)_t545;
        if (_t545) {
            U64 _t539 = 2;
            (void)_t539;
            U64 new_cap = U64_mul(self->cap, _t539);
            (void)new_cap;
            ;
            U64 _t540 = U64_mul(new_cap, self->key_size);
            (void)_t540;
            void *_t541 = realloc(self->key_data, _t540);
            (void)_t541;
            ;
            self->key_data = _t541;
            U64 _t542 = U64_mul(new_cap, self->val_size);
            (void)_t542;
            void *_t543 = realloc(self->val_data, _t542);
            (void)_t543;
            ;
            self->val_data = _t543;
            U64 _t544 = U64_clone(&(U64){new_cap});
            (void)_t544;
            ;
            self->cap = _t544;
            ;
        }
        ;
        U64 _t546 = 1;
        (void)_t546;
        U64 _t547 = U64_add(lo, _t546);
        (void)_t547;
        ;
        U64 *_t548 = malloc(sizeof(U64)); *_t548 = U64_mul(_t547, self->key_size);
        (void)_t548;
        ;
        U64 *_t549 = malloc(sizeof(U64)); *_t549 = U64_mul(lo, self->key_size);
        (void)_t549;
        U64 _t550 = U64_sub(self->count, lo);
        (void)_t550;
        void *_t551 = ptr_add(self->key_data, DEREF(_t548));
        (void)_t551;
        void *_t552 = ptr_add(self->key_data, DEREF(_t549));
        (void)_t552;
        U64 _t553 = U64_mul(_t550, self->key_size);
        (void)_t553;
        ;
        memmove(_t551, _t552, _t553);
        U64_delete(_t548, &(Bool){1});
        U64_delete(_t549, &(Bool){1});
        ;
        U64 _t554 = 1;
        (void)_t554;
        U64 _t555 = U64_add(lo, _t554);
        (void)_t555;
        ;
        U64 *_t556 = malloc(sizeof(U64)); *_t556 = U64_mul(_t555, self->val_size);
        (void)_t556;
        ;
        U64 *_t557 = malloc(sizeof(U64)); *_t557 = U64_mul(lo, self->val_size);
        (void)_t557;
        U64 _t558 = U64_sub(self->count, lo);
        (void)_t558;
        void *_t559 = ptr_add(self->val_data, DEREF(_t556));
        (void)_t559;
        void *_t560 = ptr_add(self->val_data, DEREF(_t557));
        (void)_t560;
        U64 _t561 = U64_mul(_t558, self->val_size);
        (void)_t561;
        ;
        memmove(_t559, _t560, _t561);
        U64_delete(_t556, &(Bool){1});
        U64_delete(_t557, &(Bool){1});
        ;
        U64 *_t562 = malloc(sizeof(U64)); *_t562 = U64_mul(lo, self->key_size);
        (void)_t562;
        void *_t563 = ptr_add(self->key_data, DEREF(_t562));
        (void)_t563;
        memcpy(_t563, key, self->key_size);
        U64_delete(_t562, &(Bool){1});
        U64 *_t564 = malloc(sizeof(U64)); *_t564 = U64_mul(lo, self->val_size);
        (void)_t564;
        void *_t565 = ptr_add(self->val_data, DEREF(_t564));
        (void)_t565;
        memcpy(_t565, val, self->val_size);
        U64_delete(_t564, &(Bool){1});
        free(key);
        free(val);
        U64 _t566 = 1;
        (void)_t566;
        U64 _t567 = U64_add(self->count, _t566);
        (void)_t567;
        ;
        self->count = _t567;
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
            U64 _fi568 = 0;
            (void)_fi568;
            while (1) {
                U64 _t570 = 0;
                (void)_t570;
                Range *_t571 = Range_new(_t570, self->count);
                (void)_t571;
                ;
                U64 _t572; { U64 *_hp = (U64 *)Range_len(_t571); _t572 = *_hp; free(_hp); }
                (void)_t572;
                Range_delete(_t571, &(Bool){1});
                Bool _wcond569; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi568}, &(U64){_t572}); _wcond569 = *_hp; free(_hp); }
                (void)_wcond569;
                ;
                if (_wcond569) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t573 = 0;
                (void)_t573;
                Range *_t574 = Range_new(_t573, self->count);
                (void)_t574;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t574, _fi568); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t574, &(Bool){1});
                U64 _t575 = 1;
                (void)_t575;
                U64 _t576 = U64_add(_fi568, _t575);
                (void)_t576;
                ;
                _fi568 = _t576;
                ;
                U64 *_t577 = malloc(sizeof(U64)); *_t577 = U64_mul(i, self->key_size);
                (void)_t577;
                ;
                void *_t578 = ptr_add(self->key_data, DEREF(_t577));
                (void)_t578;
                Bool _t579 = 0;
                (void)_t579;
                dyn_call_delete(&self->key_type, _t578, &(Bool){_t579});
                U64_delete(_t577, &(Bool){1});
                ;
            }
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
            U64 _fi580 = 0;
            (void)_fi580;
            while (1) {
                U64 _t582 = 0;
                (void)_t582;
                Range *_t583 = Range_new(_t582, self->count);
                (void)_t583;
                ;
                U64 _t584; { U64 *_hp = (U64 *)Range_len(_t583); _t584 = *_hp; free(_hp); }
                (void)_t584;
                Range_delete(_t583, &(Bool){1});
                Bool _wcond581; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi580}, &(U64){_t584}); _wcond581 = *_hp; free(_hp); }
                (void)_wcond581;
                ;
                if (_wcond581) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t585 = 0;
                (void)_t585;
                Range *_t586 = Range_new(_t585, self->count);
                (void)_t586;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t586, _fi580); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t586, &(Bool){1});
                U64 _t587 = 1;
                (void)_t587;
                U64 _t588 = U64_add(_fi580, _t587);
                (void)_t588;
                ;
                _fi580 = _t588;
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
    U64 _t619 = U64_mul(self->cap, self->key_size);
    (void)_t619;
    U8 *new_keys = malloc(_t619);
    (void)new_keys;
    ;
    U64 _t620 = U64_mul(self->cap, self->val_size);
    (void)_t620;
    U8 *new_vals = malloc(_t620);
    (void)new_vals;
    ;
    {
        U64 _fi602 = 0;
        (void)_fi602;
        while (1) {
            U64 _t604 = 0;
            (void)_t604;
            Range *_t605 = Range_new(_t604, self->count);
            (void)_t605;
            ;
            U64 _t606; { U64 *_hp = (U64 *)Range_len(_t605); _t606 = *_hp; free(_hp); }
            (void)_t606;
            Range_delete(_t605, &(Bool){1});
            Bool _wcond603; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi602}, &(U64){_t606}); _wcond603 = *_hp; free(_hp); }
            (void)_wcond603;
            ;
            if (_wcond603) {
            } else {
                ;
                break;
            }
            ;
            U64 _t607 = 0;
            (void)_t607;
            Range *_t608 = Range_new(_t607, self->count);
            (void)_t608;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t608, _fi602); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t608, &(Bool){1});
            U64 _t609 = 1;
            (void)_t609;
            U64 _t610 = U64_add(_fi602, _t609);
            (void)_t610;
            ;
            _fi602 = _t610;
            ;
            U64 *_t611 = malloc(sizeof(U64)); *_t611 = U64_mul(i, self->key_size);
            (void)_t611;
            void *_t612 = ptr_add(self->key_data, DEREF(_t611));
            (void)_t612;
            void *ck = dyn_call_clone(&self->key_type, _t612);
            (void)ck;
            U64_delete(_t611, &(Bool){1});
            U64 *_t613 = malloc(sizeof(U64)); *_t613 = U64_mul(i, self->key_size);
            (void)_t613;
            void *_t614 = ptr_add(new_keys, DEREF(_t613));
            (void)_t614;
            memcpy(_t614, ck, self->key_size);
            U64_delete(_t613, &(Bool){1});
            free(ck);
            U64 *_t615 = malloc(sizeof(U64)); *_t615 = U64_mul(i, self->val_size);
            (void)_t615;
            void *_t616 = ptr_add(self->val_data, DEREF(_t615));
            (void)_t616;
            void *cv = dyn_call_clone(&self->val_type, _t616);
            (void)cv;
            U64_delete(_t615, &(Bool){1});
            U64 *_t617 = malloc(sizeof(U64)); *_t617 = U64_mul(i, self->val_size);
            (void)_t617;
            ;
            void *_t618 = ptr_add(new_vals, DEREF(_t617));
            (void)_t618;
            memcpy(_t618, cv, self->val_size);
            U64_delete(_t617, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t621 = malloc(sizeof(Map));
    _t621->key_data = new_keys;
    _t621->val_data = new_vals;
    _t621->count = self->count;
    _t621->cap = self->cap;
    _t621->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t621->key_type = *_ca; free(_ca); }
    _t621->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t621->val_type = *_ca; free(_ca); }
    (void)_t621;
    return _t621;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t635; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t635 = *_hp; free(_hp); }
    (void)_t635;
    Bool _t636 = Bool_not(_t635);
    (void)_t636;
    ;
    if (_t636) {
        Bool _t633 = dyn_has_cmp(elem_type);
        (void)_t633;
        Bool _t634 = Bool_not(_t633);
        (void)_t634;
        ;
        if (_t634) {
            Str *_t623 = Str_lit("Str", 3ULL);
            (void)_t623;
            U64 _t624; { U64 *_hp = (U64 *)Str_size(); _t624 = *_hp; free(_hp); }
            (void)_t624;
            U64 _t625 = 3;
            (void)_t625;
            Array *_va11 = Array_new(_t623, &(U64){_t624}, &(U64){_t625});
            (void)_va11;
            Str_delete(_t623, &(Bool){1});
            ;
            ;
            U64 _t626 = 0;
            (void)_t626;
            Str *_t627 = Str_lit("Set.new: type ", 14ULL);
            (void)_t627;
            Array_set(_va11, &(U64){_t626}, _t627);
            ;
            U64 _t628 = 1;
            (void)_t628;
            Str *_t629 = Str_clone(elem_type);
            (void)_t629;
            Array_set(_va11, &(U64){_t628}, _t629);
            ;
            U64 _t630 = 2;
            (void)_t630;
            Str *_t631 = Str_lit(" must implement cmp", 19ULL);
            (void)_t631;
            Array_set(_va11, &(U64){_t630}, _t631);
            ;
            Str *_t632 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t632;
            panic(_t632, _va11);
            Str_delete(_t632, &(Bool){1});
        }
        ;
    }
    ;
    void *_t637 = malloc(DEREF(elem_size));
    (void)_t637;
    U64 _t638 = 0;
    (void)_t638;
    I64 _t639 = 1;
    (void)_t639;
    U64 _t640 = U64_clone(elem_size);
    (void)_t640;
    Set *_t641 = malloc(sizeof(Set));
    _t641->data = _t637;
    _t641->count = _t638;
    _t641->cap = _t639;
    _t641->elem_size = _t640;
    { Str *_ca = Str_clone(elem_type); _t641->elem_type = *_ca; free(_ca); }
    (void)_t641;
    ;
    ;
    ;
    return _t641;
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
        Bool _wcond642; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond642 = *_hp; free(_hp); }
        (void)_wcond642;
        if (_wcond642) {
        } else {
            ;
            break;
        }
        ;
        U64 _t649 = U64_sub(hi, lo);
        (void)_t649;
        U64 _t650 = 2;
        (void)_t650;
        U64 _t651 = U64_div(_t649, _t650);
        (void)_t651;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t651);
        (void)mid;
        ;
        U64 *_t652 = malloc(sizeof(U64)); *_t652 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t652;
        void *_t653 = ptr_add(self->data, DEREF(_t652));
        (void)_t653;
        I64 *c = dyn_call_cmp(&self->elem_type, _t653, val);
        (void)c;
        U64_delete(_t652, &(Bool){1});
        I64 _t654 = 0;
        (void)_t654;
        Bool _t655; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t654}); _t655 = *_hp; free(_hp); }
        (void)_t655;
        ;
        if (_t655) {
            U64 _t643 = 1;
            (void)_t643;
            U64 _t644 = U64_add(DEREF(mid), _t643);
            (void)_t644;
            ;
            lo = _t644;
            ;
        } else {
            I64 _t647 = 0;
            (void)_t647;
            Bool _t648; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t647}); _t648 = *_hp; free(_hp); }
            (void)_t648;
            ;
            if (_t648) {
                U64 _t645 = U64_clone(mid);
                (void)_t645;
                hi = _t645;
                ;
            } else {
                Bool _t646 = 1;
                (void)_t646;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t646; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t656 = 0;
    (void)_t656;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t656; return _r; }
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
        Bool _wcond657; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond657 = *_hp; free(_hp); }
        (void)_wcond657;
        if (_wcond657) {
        } else {
            ;
            break;
        }
        ;
        U64 _t666 = U64_sub(hi, lo);
        (void)_t666;
        U64 _t667 = 2;
        (void)_t667;
        U64 _t668 = U64_div(_t666, _t667);
        (void)_t668;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t668);
        (void)mid;
        ;
        U64 *_t669 = malloc(sizeof(U64)); *_t669 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t669;
        void *_t670 = ptr_add(self->data, DEREF(_t669));
        (void)_t670;
        I64 *c = dyn_call_cmp(&self->elem_type, _t670, val);
        (void)c;
        U64_delete(_t669, &(Bool){1});
        I64 _t671 = 0;
        (void)_t671;
        Bool _t672; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t671}); _t672 = *_hp; free(_hp); }
        (void)_t672;
        ;
        if (_t672) {
            U64 _t658 = 1;
            (void)_t658;
            U64 _t659 = U64_add(DEREF(mid), _t658);
            (void)_t659;
            ;
            lo = _t659;
            ;
        } else {
            I64 _t664 = 0;
            (void)_t664;
            Bool _t665; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t664}); _t665 = *_hp; free(_hp); }
            (void)_t665;
            ;
            if (_t665) {
                U64 _t660 = U64_clone(mid);
                (void)_t660;
                hi = _t660;
                ;
            } else {
                Bool _t661 = 1;
                (void)_t661;
                found = _t661;
                ;
                U64 _t662 = U64_clone(mid);
                (void)_t662;
                lo = _t662;
                ;
                U64 _t663 = U64_clone(mid);
                (void)_t663;
                hi = _t663;
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
        Bool _t674; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t674 = *_hp; free(_hp); }
        (void)_t674;
        Bool _t675 = Bool_not(_t674);
        (void)_t675;
        ;
        if (_t675) {
            Bool _t673 = 0;
            (void)_t673;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t673});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t680 = U64_eq(self->count, self->cap);
        (void)_t680;
        if (_t680) {
            U64 _t676 = 2;
            (void)_t676;
            U64 new_cap = U64_mul(self->cap, _t676);
            (void)new_cap;
            ;
            U64 _t677 = U64_mul(new_cap, self->elem_size);
            (void)_t677;
            void *_t678 = realloc(self->data, _t677);
            (void)_t678;
            ;
            self->data = _t678;
            U64 _t679 = U64_clone(&(U64){new_cap});
            (void)_t679;
            ;
            self->cap = _t679;
            ;
        }
        ;
        U64 _t681 = 1;
        (void)_t681;
        U64 _t682 = U64_add(lo, _t681);
        (void)_t682;
        ;
        U64 *_t683 = malloc(sizeof(U64)); *_t683 = U64_mul(_t682, self->elem_size);
        (void)_t683;
        ;
        U64 *_t684 = malloc(sizeof(U64)); *_t684 = U64_mul(lo, self->elem_size);
        (void)_t684;
        U64 _t685 = U64_sub(self->count, lo);
        (void)_t685;
        void *_t686 = ptr_add(self->data, DEREF(_t683));
        (void)_t686;
        void *_t687 = ptr_add(self->data, DEREF(_t684));
        (void)_t687;
        U64 _t688 = U64_mul(_t685, self->elem_size);
        (void)_t688;
        ;
        memmove(_t686, _t687, _t688);
        U64_delete(_t683, &(Bool){1});
        U64_delete(_t684, &(Bool){1});
        ;
        U64 *_t689 = malloc(sizeof(U64)); *_t689 = U64_mul(lo, self->elem_size);
        (void)_t689;
        void *_t690 = ptr_add(self->data, DEREF(_t689));
        (void)_t690;
        memcpy(_t690, val, self->elem_size);
        U64_delete(_t689, &(Bool){1});
        free(val);
        U64 _t691 = 1;
        (void)_t691;
        U64 _t692 = U64_add(self->count, _t691);
        (void)_t692;
        ;
        self->count = _t692;
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
            U64 _fi693 = 0;
            (void)_fi693;
            while (1) {
                U64 _t695 = 0;
                (void)_t695;
                Range *_t696 = Range_new(_t695, self->count);
                (void)_t696;
                ;
                U64 _t697; { U64 *_hp = (U64 *)Range_len(_t696); _t697 = *_hp; free(_hp); }
                (void)_t697;
                Range_delete(_t696, &(Bool){1});
                Bool _wcond694; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi693}, &(U64){_t697}); _wcond694 = *_hp; free(_hp); }
                (void)_wcond694;
                ;
                if (_wcond694) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t698 = 0;
                (void)_t698;
                Range *_t699 = Range_new(_t698, self->count);
                (void)_t699;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t699, _fi693); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t699, &(Bool){1});
                U64 _t700 = 1;
                (void)_t700;
                U64 _t701 = U64_add(_fi693, _t700);
                (void)_t701;
                ;
                _fi693 = _t701;
                ;
                U64 *_t702 = malloc(sizeof(U64)); *_t702 = U64_mul(i, self->elem_size);
                (void)_t702;
                ;
                void *_t703 = ptr_add(self->data, DEREF(_t702));
                (void)_t703;
                Bool _t704 = 0;
                (void)_t704;
                dyn_call_delete(&self->elem_type, _t703, &(Bool){_t704});
                U64_delete(_t702, &(Bool){1});
                ;
            }
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
    U64 _t723 = U64_mul(self->cap, self->elem_size);
    (void)_t723;
    U8 *new_data = malloc(_t723);
    (void)new_data;
    ;
    {
        U64 _fi710 = 0;
        (void)_fi710;
        while (1) {
            U64 _t712 = 0;
            (void)_t712;
            Range *_t713 = Range_new(_t712, self->count);
            (void)_t713;
            ;
            U64 _t714; { U64 *_hp = (U64 *)Range_len(_t713); _t714 = *_hp; free(_hp); }
            (void)_t714;
            Range_delete(_t713, &(Bool){1});
            Bool _wcond711; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi710}, &(U64){_t714}); _wcond711 = *_hp; free(_hp); }
            (void)_wcond711;
            ;
            if (_wcond711) {
            } else {
                ;
                break;
            }
            ;
            U64 _t715 = 0;
            (void)_t715;
            Range *_t716 = Range_new(_t715, self->count);
            (void)_t716;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t716, _fi710); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t716, &(Bool){1});
            U64 _t717 = 1;
            (void)_t717;
            U64 _t718 = U64_add(_fi710, _t717);
            (void)_t718;
            ;
            _fi710 = _t718;
            ;
            U64 *_t719 = malloc(sizeof(U64)); *_t719 = U64_mul(i, self->elem_size);
            (void)_t719;
            void *_t720 = ptr_add(self->data, DEREF(_t719));
            (void)_t720;
            void *cloned = dyn_call_clone(&self->elem_type, _t720);
            (void)cloned;
            U64_delete(_t719, &(Bool){1});
            U64 *_t721 = malloc(sizeof(U64)); *_t721 = U64_mul(i, self->elem_size);
            (void)_t721;
            ;
            void *_t722 = ptr_add(new_data, DEREF(_t721));
            (void)_t722;
            memcpy(_t722, cloned, self->elem_size);
            U64_delete(_t721, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t724 = malloc(sizeof(Set));
    _t724->data = new_data;
    _t724->count = self->count;
    _t724->cap = self->cap;
    _t724->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t724->elem_type = *_ca; free(_ca); }
    (void)_t724;
    return _t724;
}

U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t732; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t732 = *_hp; free(_hp); }
    (void)_t732;
    if (_t732) {
        Str *_t726 = Str_lit("Str", 3ULL);
        (void)_t726;
        U64 _t727; { U64 *_hp = (U64 *)Str_size(); _t727 = *_hp; free(_hp); }
        (void)_t727;
        U64 _t728 = 1;
        (void)_t728;
        Array *_va12 = Array_new(_t726, &(U64){_t727}, &(U64){_t728});
        (void)_va12;
        Str_delete(_t726, &(Bool){1});
        ;
        ;
        U64 _t729 = 0;
        (void)_t729;
        Str *_t730 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t730;
        Array_set(_va12, &(U64){_t729}, _t730);
        ;
        Str *_t731 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t731;
        panic(_t731, _va12);
        Str_delete(_t731, &(Bool){1});
    }
    ;
    void *_t733 = ptr_add(self->c_str, DEREF(i));
    (void)_t733;
    return _t733;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t734 = ptr_add(self->c_str, DEREF(i));
    (void)_t734;
    return _t734;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t746; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t746 = *_hp; free(_hp); }
    (void)_t746;
    if (_t746) {
        min_len = b->count;
    }
    ;
    {
        U64 _fi735 = 0;
        (void)_fi735;
        while (1) {
            U64 _t737 = 0;
            (void)_t737;
            Range *_t738 = Range_new(_t737, min_len);
            (void)_t738;
            ;
            U64 _t739; { U64 *_hp = (U64 *)Range_len(_t738); _t739 = *_hp; free(_hp); }
            (void)_t739;
            Range_delete(_t738, &(Bool){1});
            Bool _wcond736; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi735}, &(U64){_t739}); _wcond736 = *_hp; free(_hp); }
            (void)_wcond736;
            ;
            if (_wcond736) {
            } else {
                ;
                break;
            }
            ;
            U64 _t740 = 0;
            (void)_t740;
            Range *_t741 = Range_new(_t740, min_len);
            (void)_t741;
            ;
            U64 *i = Range_get(_t741, _fi735);
            (void)i;
            Range_delete(_t741, &(Bool){1});
            U64 _t742 = 1;
            (void)_t742;
            U64 _t743 = U64_add(_fi735, _t742);
            (void)_t743;
            ;
            _fi735 = _t743;
            ;
            U8 *ab = Str_get(a, i);
            (void)ab;
            U8 *bb = Str_get(b, i);
            (void)bb;
            I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
            (void)c;
            U64_delete(i, &(Bool){1});
            I64 _t744 = 0;
            (void)_t744;
            Bool _t745; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t744}); _t745 = *_hp; free(_hp); }
            (void)_t745;
            ;
            if (_t745) {
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
    I64 _t747 = U64_cmp(a->count, b->count);
    (void)_t747;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t747; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t748 = 1;
    (void)_t748;
    U64 _t749 = U64_add(DEREF(new_len), _t748);
    (void)_t749;
    ;
    U8 *new_data = malloc(_t749);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t750 = ptr_add(new_data, a->count);
    (void)_t750;
    memcpy(_t750, b->c_str, b->count);
    void *_t751 = ptr_add(new_data, DEREF(new_len));
    (void)_t751;
    I32 _t752 = 0;
    (void)_t752;
    U64 _t753 = 1;
    (void)_t753;
    memset(_t751, _t752, _t753);
    ;
    ;
    U64 _t754 = U64_clone(new_len);
    (void)_t754;
    U64 _t755 = U64_clone(new_len);
    (void)_t755;
    U64_delete(new_len, &(Bool){1});
    Str *_t756 = malloc(sizeof(Str));
    _t756->c_str = new_data;
    _t756->count = _t754;
    _t756->cap = _t755;
    (void)_t756;
    ;
    ;
    return _t756;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t757 = 1;
    (void)_t757;
    U64 _t758 = U64_add(DEREF(n), _t757);
    (void)_t758;
    ;
    U8 *buf = malloc(_t758);
    (void)buf;
    ;
    I32 _t759 = 0;
    (void)_t759;
    U64 _t760 = 1;
    (void)_t760;
    memset(buf, _t759, _t760);
    ;
    ;
    I64 _t761 = 0;
    (void)_t761;
    U64 _t762 = U64_clone(n);
    (void)_t762;
    Str *_t763 = malloc(sizeof(Str));
    _t763->c_str = buf;
    _t763->count = _t761;
    _t763->cap = _t762;
    (void)_t763;
    ;
    ;
    return _t763;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t776; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t776 = *_hp; free(_hp); }
    (void)_t776;
    if (_t776) {
        Str *_t764 = Str_lit("Str", 3ULL);
        (void)_t764;
        U64 _t765; { U64 *_hp = (U64 *)Str_size(); _t765 = *_hp; free(_hp); }
        (void)_t765;
        U64 _t766 = 1;
        (void)_t766;
        Array *_va13 = Array_new(_t764, &(U64){_t765}, &(U64){_t766});
        (void)_va13;
        Str_delete(_t764, &(Bool){1});
        ;
        ;
        U64 _t767 = 0;
        (void)_t767;
        Str *_t768 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t768;
        Array_set(_va13, &(U64){_t767}, _t768);
        ;
        Str *_t769 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:55:19", 60ULL);
        (void)_t769;
        panic(_t769, _va13);
        Str_delete(_t769, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t777; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t777 = *_hp; free(_hp); }
    (void)_t777;
    if (_t777) {
        Str *_t770 = Str_lit("Str", 3ULL);
        (void)_t770;
        U64 _t771; { U64 *_hp = (U64 *)Str_size(); _t771 = *_hp; free(_hp); }
        (void)_t771;
        U64 _t772 = 1;
        (void)_t772;
        Array *_va14 = Array_new(_t770, &(U64){_t771}, &(U64){_t772});
        (void)_va14;
        Str_delete(_t770, &(Bool){1});
        ;
        ;
        U64 _t773 = 0;
        (void)_t773;
        Str *_t774 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t774;
        Array_set(_va14, &(U64){_t773}, _t774);
        ;
        Str *_t775 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:59:19", 60ULL);
        (void)_t775;
        panic(_t775, _va14);
        Str_delete(_t775, &(Bool){1});
    }
    ;
    void *_t778 = ptr_add(self->c_str, self->count);
    (void)_t778;
    memcpy(_t778, s->c_str, s->count);
    U64 _t779 = U64_clone(new_len);
    (void)_t779;
    self->count = _t779;
    ;
    void *_t780 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t780;
    I32 _t781 = 0;
    (void)_t781;
    U64 _t782 = 1;
    (void)_t782;
    memset(_t780, _t781, _t782);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t783 = 1;
    (void)_t783;
    U64 _t784 = U64_add(val->count, _t783);
    (void)_t784;
    ;
    U8 *new_data = malloc(_t784);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t785 = ptr_add(new_data, val->count);
    (void)_t785;
    I32 _t786 = 0;
    (void)_t786;
    U64 _t787 = 1;
    (void)_t787;
    memset(_t785, _t786, _t787);
    ;
    ;
    Str *_t788 = malloc(sizeof(Str));
    _t788->c_str = new_data;
    _t788->count = val->count;
    _t788->cap = val->count;
    (void)_t788;
    return _t788;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t789; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t789 = *_hp; free(_hp); }
    (void)_t789;
    if (_t789) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t790 = Str_clone(val);
    (void)_t790;
    return _t790;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t792; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t792 = *_hp; free(_hp); }
    (void)_t792;
    if (_t792) {
        *st = s->count;
    }
    ;
    U64 _t793 = U64_add(DEREF(st), ln);
    (void)_t793;
    Bool _t794; { Bool *_hp = (Bool *)U64_gt(&(U64){_t793}, &s->count); _t794 = *_hp; free(_hp); }
    (void)_t794;
    ;
    if (_t794) {
        U64 _t791 = U64_sub(s->count, DEREF(st));
        (void)_t791;
        ln = _t791;
        ;
    }
    ;
    void *_t795 = ptr_add(s->c_str, DEREF(st));
    (void)_t795;
    U64 _t796 = U64_clone(&(U64){ln});
    (void)_t796;
    ;
    U64 _t797 = U64_clone(CAP_VIEW);
    (void)_t797;
    Str *_t798 = malloc(sizeof(Str));
    _t798->c_str = _t795;
    _t798->count = _t796;
    _t798->cap = _t797;
    (void)_t798;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t798;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t829 = 0;
    (void)_t829;
    Bool _t830 = U64_eq(b->count, _t829);
    (void)_t830;
    ;
    if (_t830) {
        Bool _t799 = 1;
        (void)_t799;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t799; return _r; }
    }
    ;
    Bool _t831; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t831 = *_hp; free(_hp); }
    (void)_t831;
    if (_t831) {
        Bool _t800 = 0;
        (void)_t800;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t800; return _r; }
    }
    ;
    {
        U64 _fi801 = 0;
        (void)_fi801;
        while (1) {
            U64 _t816 = U64_sub(a->count, b->count);
            (void)_t816;
            U64 _t817 = 1;
            (void)_t817;
            U64 _t818 = 0;
            (void)_t818;
            U64 _t819 = U64_add(_t816, _t817);
            (void)_t819;
            ;
            ;
            Range *_t820 = Range_new(_t818, _t819);
            (void)_t820;
            ;
            ;
            U64 _t821; { U64 *_hp = (U64 *)Range_len(_t820); _t821 = *_hp; free(_hp); }
            (void)_t821;
            Range_delete(_t820, &(Bool){1});
            Bool _wcond802; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi801}, &(U64){_t821}); _wcond802 = *_hp; free(_hp); }
            (void)_wcond802;
            ;
            if (_wcond802) {
            } else {
                ;
                break;
            }
            ;
            U64 _t822 = U64_sub(a->count, b->count);
            (void)_t822;
            U64 _t823 = 1;
            (void)_t823;
            U64 _t824 = 0;
            (void)_t824;
            U64 _t825 = U64_add(_t822, _t823);
            (void)_t825;
            ;
            ;
            Range *_t826 = Range_new(_t824, _t825);
            (void)_t826;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t826, _fi801); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t826, &(Bool){1});
            U64 _t827 = 1;
            (void)_t827;
            U64 _t828 = U64_add(_fi801, _t827);
            (void)_t828;
            ;
            _fi801 = _t828;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi803 = 0;
                (void)_fi803;
                while (1) {
                    U64 _t806 = 0;
                    (void)_t806;
                    Range *_t807 = Range_new(_t806, b->count);
                    (void)_t807;
                    ;
                    U64 _t808; { U64 *_hp = (U64 *)Range_len(_t807); _t808 = *_hp; free(_hp); }
                    (void)_t808;
                    Range_delete(_t807, &(Bool){1});
                    Bool _wcond804; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi803}, &(U64){_t808}); _wcond804 = *_hp; free(_hp); }
                    (void)_wcond804;
                    ;
                    if (_wcond804) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t809 = 0;
                    (void)_t809;
                    Range *_t810 = Range_new(_t809, b->count);
                    (void)_t810;
                    ;
                    U64 *j = Range_get(_t810, _fi803);
                    (void)j;
                    Range_delete(_t810, &(Bool){1});
                    U64 _t811 = 1;
                    (void)_t811;
                    U64 _t812 = U64_add(_fi803, _t811);
                    (void)_t812;
                    ;
                    _fi803 = _t812;
                    ;
                    U64 *_t813 = malloc(sizeof(U64)); *_t813 = U64_add(i, DEREF(j));
                    (void)_t813;
                    U8 *ac = Str_get(a, _t813);
                    (void)ac;
                    U8 *bc = Str_get(b, j);
                    (void)bc;
                    Bool _t814; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t814 = *_hp; free(_hp); }
                    (void)_t814;
                    U64_delete(_t813, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t814) {
                        Bool _t805 = 0;
                        (void)_t805;
                        found = _t805;
                        ;
                    }
                    ;
                }
                ;
            }
            ;
            if (found) {
                Bool _t815 = 1;
                (void)_t815;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t815; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t832 = 0;
    (void)_t832;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t832; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t845; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t845 = *_hp; free(_hp); }
    (void)_t845;
    if (_t845) {
        Bool _t833 = 0;
        (void)_t833;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t833; return _r; }
    }
    ;
    {
        U64 _fi834 = 0;
        (void)_fi834;
        while (1) {
            U64 _t837 = 0;
            (void)_t837;
            Range *_t838 = Range_new(_t837, b->count);
            (void)_t838;
            ;
            U64 _t839; { U64 *_hp = (U64 *)Range_len(_t838); _t839 = *_hp; free(_hp); }
            (void)_t839;
            Range_delete(_t838, &(Bool){1});
            Bool _wcond835; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi834}, &(U64){_t839}); _wcond835 = *_hp; free(_hp); }
            (void)_wcond835;
            ;
            if (_wcond835) {
            } else {
                ;
                break;
            }
            ;
            U64 _t840 = 0;
            (void)_t840;
            Range *_t841 = Range_new(_t840, b->count);
            (void)_t841;
            ;
            U64 *i = Range_get(_t841, _fi834);
            (void)i;
            Range_delete(_t841, &(Bool){1});
            U64 _t842 = 1;
            (void)_t842;
            U64 _t843 = U64_add(_fi834, _t842);
            (void)_t843;
            ;
            _fi834 = _t843;
            ;
            U8 *ac = Str_get(a, i);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t844; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t844 = *_hp; free(_hp); }
            (void)_t844;
            U64_delete(i, &(Bool){1});
            if (_t844) {
                Bool _t836 = 0;
                (void)_t836;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t836; return _r; }
            }
            ;
        }
        ;
    }
    Bool _t846 = 1;
    (void)_t846;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t846; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t860; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t860 = *_hp; free(_hp); }
    (void)_t860;
    if (_t860) {
        Bool _t847 = 0;
        (void)_t847;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t847; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    {
        U64 _fi848 = 0;
        (void)_fi848;
        while (1) {
            U64 _t851 = 0;
            (void)_t851;
            Range *_t852 = Range_new(_t851, b->count);
            (void)_t852;
            ;
            U64 _t853; { U64 *_hp = (U64 *)Range_len(_t852); _t853 = *_hp; free(_hp); }
            (void)_t853;
            Range_delete(_t852, &(Bool){1});
            Bool _wcond849; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi848}, &(U64){_t853}); _wcond849 = *_hp; free(_hp); }
            (void)_wcond849;
            ;
            if (_wcond849) {
            } else {
                ;
                break;
            }
            ;
            U64 _t854 = 0;
            (void)_t854;
            Range *_t855 = Range_new(_t854, b->count);
            (void)_t855;
            ;
            U64 *i = Range_get(_t855, _fi848);
            (void)i;
            Range_delete(_t855, &(Bool){1});
            U64 _t856 = 1;
            (void)_t856;
            U64 _t857 = U64_add(_fi848, _t856);
            (void)_t857;
            ;
            _fi848 = _t857;
            ;
            U64 *_t858 = malloc(sizeof(U64)); *_t858 = U64_add(offset, DEREF(i));
            (void)_t858;
            U8 *ac = Str_get(a, _t858);
            (void)ac;
            U8 *bc = Str_get(b, i);
            (void)bc;
            Bool _t859; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t859 = *_hp; free(_hp); }
            (void)_t859;
            U64_delete(_t858, &(Bool){1});
            U64_delete(i, &(Bool){1});
            if (_t859) {
                Bool _t850 = 0;
                (void)_t850;
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t850; return _r; }
            }
            ;
        }
        ;
    }
    ;
    Bool _t861 = 1;
    (void)_t861;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t861; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t862 = 0;
    (void)_t862;
    Bool _t863 = U64_eq(self->count, _t862);
    (void)_t863;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t863; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t898 = 0;
    (void)_t898;
    Bool _t899 = U64_eq(needle->count, _t898);
    (void)_t899;
    ;
    if (_t899) {
        I64 _t864 = 0;
        (void)_t864;
        I64 _t865 = 1;
        (void)_t865;
        I64 _t866 = I64_sub(_t864, _t865);
        (void)_t866;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t866; return _r; }
    }
    ;
    Bool _t900; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t900 = *_hp; free(_hp); }
    (void)_t900;
    if (_t900) {
        I64 _t867 = 0;
        (void)_t867;
        I64 _t868 = 1;
        (void)_t868;
        I64 _t869 = I64_sub(_t867, _t868);
        (void)_t869;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t869; return _r; }
    }
    ;
    {
        U64 _fi870 = 0;
        (void)_fi870;
        while (1) {
            U64 _t885 = U64_sub(self->count, needle->count);
            (void)_t885;
            U64 _t886 = 1;
            (void)_t886;
            U64 _t887 = 0;
            (void)_t887;
            U64 _t888 = U64_add(_t885, _t886);
            (void)_t888;
            ;
            ;
            Range *_t889 = Range_new(_t887, _t888);
            (void)_t889;
            ;
            ;
            U64 _t890; { U64 *_hp = (U64 *)Range_len(_t889); _t890 = *_hp; free(_hp); }
            (void)_t890;
            Range_delete(_t889, &(Bool){1});
            Bool _wcond871; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi870}, &(U64){_t890}); _wcond871 = *_hp; free(_hp); }
            (void)_wcond871;
            ;
            if (_wcond871) {
            } else {
                ;
                break;
            }
            ;
            U64 _t891 = U64_sub(self->count, needle->count);
            (void)_t891;
            U64 _t892 = 1;
            (void)_t892;
            U64 _t893 = 0;
            (void)_t893;
            U64 _t894 = U64_add(_t891, _t892);
            (void)_t894;
            ;
            ;
            Range *_t895 = Range_new(_t893, _t894);
            (void)_t895;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t895, _fi870); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t895, &(Bool){1});
            U64 _t896 = 1;
            (void)_t896;
            U64 _t897 = U64_add(_fi870, _t896);
            (void)_t897;
            ;
            _fi870 = _t897;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi872 = 0;
                (void)_fi872;
                while (1) {
                    U64 _t875 = 0;
                    (void)_t875;
                    Range *_t876 = Range_new(_t875, needle->count);
                    (void)_t876;
                    ;
                    U64 _t877; { U64 *_hp = (U64 *)Range_len(_t876); _t877 = *_hp; free(_hp); }
                    (void)_t877;
                    Range_delete(_t876, &(Bool){1});
                    Bool _wcond873; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi872}, &(U64){_t877}); _wcond873 = *_hp; free(_hp); }
                    (void)_wcond873;
                    ;
                    if (_wcond873) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t878 = 0;
                    (void)_t878;
                    Range *_t879 = Range_new(_t878, needle->count);
                    (void)_t879;
                    ;
                    U64 *j = Range_get(_t879, _fi872);
                    (void)j;
                    Range_delete(_t879, &(Bool){1});
                    U64 _t880 = 1;
                    (void)_t880;
                    U64 _t881 = U64_add(_fi872, _t880);
                    (void)_t881;
                    ;
                    _fi872 = _t881;
                    ;
                    U64 *_t882 = malloc(sizeof(U64)); *_t882 = U64_add(i, DEREF(j));
                    (void)_t882;
                    U8 *ac = Str_get(self, _t882);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t883; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t883 = *_hp; free(_hp); }
                    (void)_t883;
                    U64_delete(_t882, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t883) {
                        Bool _t874 = 0;
                        (void)_t874;
                        found = _t874;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t884 = U64_to_i64(i);
                (void)_t884;
                ;
                ;
                ;
                { I64 *_r = malloc(sizeof(I64)); *_r = _t884; return _r; }
            }
            ;
            ;
        }
        ;
    }
    I64 _t901 = 0;
    (void)_t901;
    I64 _t902 = 1;
    (void)_t902;
    I64 _t903 = I64_sub(_t901, _t902);
    (void)_t903;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t903; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t938 = 0;
    (void)_t938;
    Bool _t939 = U64_eq(needle->count, _t938);
    (void)_t939;
    ;
    if (_t939) {
        I64 _t904 = 0;
        (void)_t904;
        I64 _t905 = 1;
        (void)_t905;
        I64 _t906 = I64_sub(_t904, _t905);
        (void)_t906;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t906; return _r; }
    }
    ;
    Bool _t940; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t940 = *_hp; free(_hp); }
    (void)_t940;
    if (_t940) {
        I64 _t907 = 0;
        (void)_t907;
        I64 _t908 = 1;
        (void)_t908;
        I64 _t909 = I64_sub(_t907, _t908);
        (void)_t909;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t909; return _r; }
    }
    ;
    I64 _t941 = 0;
    (void)_t941;
    I64 _t942 = 1;
    (void)_t942;
    I64 last = I64_sub(_t941, _t942);
    (void)last;
    ;
    ;
    {
        U64 _fi910 = 0;
        (void)_fi910;
        while (1) {
            U64 _t925 = U64_sub(self->count, needle->count);
            (void)_t925;
            U64 _t926 = 1;
            (void)_t926;
            U64 _t927 = 0;
            (void)_t927;
            U64 _t928 = U64_add(_t925, _t926);
            (void)_t928;
            ;
            ;
            Range *_t929 = Range_new(_t927, _t928);
            (void)_t929;
            ;
            ;
            U64 _t930; { U64 *_hp = (U64 *)Range_len(_t929); _t930 = *_hp; free(_hp); }
            (void)_t930;
            Range_delete(_t929, &(Bool){1});
            Bool _wcond911; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi910}, &(U64){_t930}); _wcond911 = *_hp; free(_hp); }
            (void)_wcond911;
            ;
            if (_wcond911) {
            } else {
                ;
                break;
            }
            ;
            U64 _t931 = U64_sub(self->count, needle->count);
            (void)_t931;
            U64 _t932 = 1;
            (void)_t932;
            U64 _t933 = 0;
            (void)_t933;
            U64 _t934 = U64_add(_t931, _t932);
            (void)_t934;
            ;
            ;
            Range *_t935 = Range_new(_t933, _t934);
            (void)_t935;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t935, _fi910); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t935, &(Bool){1});
            U64 _t936 = 1;
            (void)_t936;
            U64 _t937 = U64_add(_fi910, _t936);
            (void)_t937;
            ;
            _fi910 = _t937;
            ;
            Bool found = 1;
            (void)found;
            {
                U64 _fi912 = 0;
                (void)_fi912;
                while (1) {
                    U64 _t915 = 0;
                    (void)_t915;
                    Range *_t916 = Range_new(_t915, needle->count);
                    (void)_t916;
                    ;
                    U64 _t917; { U64 *_hp = (U64 *)Range_len(_t916); _t917 = *_hp; free(_hp); }
                    (void)_t917;
                    Range_delete(_t916, &(Bool){1});
                    Bool _wcond913; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi912}, &(U64){_t917}); _wcond913 = *_hp; free(_hp); }
                    (void)_wcond913;
                    ;
                    if (_wcond913) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U64 _t918 = 0;
                    (void)_t918;
                    Range *_t919 = Range_new(_t918, needle->count);
                    (void)_t919;
                    ;
                    U64 *j = Range_get(_t919, _fi912);
                    (void)j;
                    Range_delete(_t919, &(Bool){1});
                    U64 _t920 = 1;
                    (void)_t920;
                    U64 _t921 = U64_add(_fi912, _t920);
                    (void)_t921;
                    ;
                    _fi912 = _t921;
                    ;
                    U64 *_t922 = malloc(sizeof(U64)); *_t922 = U64_add(i, DEREF(j));
                    (void)_t922;
                    U8 *ac = Str_get(self, _t922);
                    (void)ac;
                    U8 *bc = Str_get(needle, j);
                    (void)bc;
                    Bool _t923; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t923 = *_hp; free(_hp); }
                    (void)_t923;
                    U64_delete(_t922, &(Bool){1});
                    U64_delete(j, &(Bool){1});
                    if (_t923) {
                        Bool _t914 = 0;
                        (void)_t914;
                        found = _t914;
                        ;
                    }
                    ;
                }
                ;
            }
            if (found) {
                I64 _t924 = U64_to_i64(i);
                (void)_t924;
                last = _t924;
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
    U64 _t958 = 0;
    (void)_t958;
    Bool _t959 = U64_eq(from->count, _t958);
    (void)_t959;
    ;
    if (_t959) {
        Str *_t943 = Str_clone(self);
        (void)_t943;
        ;
        return _t943;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t945 = U64_sub(self->count, from->count);
        (void)_t945;
        Bool _wcond944; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t945}); _wcond944 = *_hp; free(_hp); }
        (void)_wcond944;
        ;
        if (_wcond944) {
        } else {
            ;
            break;
        }
        ;
        U64 _t946 = U64_sub(self->count, start);
        (void)_t946;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t946});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t947 = 0;
        (void)_t947;
        I64 _t948 = 1;
        (void)_t948;
        I64 _t949 = I64_sub(_t947, _t948);
        (void)_t949;
        ;
        ;
        Bool _t950 = I64_eq(pos, _t949);
        (void)_t950;
        ;
        if (_t950) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t951 = I64_to_u64(pos);
        (void)_t951;
        Str *_t952 = Str_substr(self, &(U64){start}, &(U64){_t951});
        (void)_t952;
        ;
        result = Str_concat(result, _t952);
        Str_delete(_t952, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t953 = I64_to_u64(pos);
        (void)_t953;
        ;
        U64 _t954 = U64_add(start, _t953);
        (void)_t954;
        ;
        U64 _t955 = U64_add(_t954, from->count);
        (void)_t955;
        ;
        start = _t955;
        ;
    }
    Bool _t960; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t960 = *_hp; free(_hp); }
    (void)_t960;
    if (_t960) {
        U64 _t956 = U64_sub(self->count, start);
        (void)_t956;
        Str *_t957 = Str_substr(self, &(U64){start}, &(U64){_t956});
        (void)_t957;
        ;
        result = Str_concat(result, _t957);
        Str_delete(_t957, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t961 = 1;
    (void)_t961;
    Str *_t962 = Str_substr(self, i, &(U64){_t961});
    (void)_t962;
    ;
    return _t962;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t965; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t965 = *_hp; free(_hp); }
    (void)_t965;
    if (_t965) {
        U64 _t963 = U64_sub(self->count, prefix->count);
        (void)_t963;
        Str *_t964 = Str_substr(self, &prefix->count, &(U64){_t963});
        (void)_t964;
        ;
        ;
        return _t964;
    }
    ;
    Str *_t966 = Str_clone(self);
    (void)_t966;
    return _t966;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t970; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t970 = *_hp; free(_hp); }
    (void)_t970;
    if (_t970) {
        U64 _t967 = 0;
        (void)_t967;
        U64 _t968 = U64_sub(self->count, suffix->count);
        (void)_t968;
        Str *_t969 = Str_substr(self, &(U64){_t967}, &(U64){_t968});
        (void)_t969;
        ;
        ;
        ;
        return _t969;
    }
    ;
    Str *_t971 = Str_clone(self);
    (void)_t971;
    return _t971;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t972 = 2;
    (void)_t972;
    U8 *buf = malloc(_t972);
    (void)buf;
    ;
    U64 _t973 = 1;
    (void)_t973;
    memcpy(buf, byte, _t973);
    ;
    U64 *_t974 = malloc(sizeof(U64));
    *_t974 = 1;
    (void)_t974;
    void *_t975 = ptr_add(buf, DEREF(_t974));
    (void)_t975;
    I32 _t976 = 0;
    (void)_t976;
    U64 _t977 = 1;
    (void)_t977;
    memset(_t975, _t976, _t977);
    U64_delete(_t974, &(Bool){1});
    ;
    ;
    I64 _t978 = 1;
    (void)_t978;
    I64 _t979 = 1;
    (void)_t979;
    Str *_t980 = malloc(sizeof(Str));
    _t980->c_str = buf;
    _t980->count = _t978;
    _t980->cap = _t979;
    (void)_t980;
    ;
    ;
    return _t980;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t1024 = 0;
    (void)_t1024;
    Bool _t1025 = U64_eq(self->count, _t1024);
    (void)_t1025;
    ;
    if (_t1025) {
        Str *_t981 = Str_lit("Str", 3ULL);
        (void)_t981;
        U64 _t982; { U64 *_hp = (U64 *)Str_size(); _t982 = *_hp; free(_hp); }
        (void)_t982;
        U64 _t983 = 1;
        (void)_t983;
        Array *_va15 = Array_new(_t981, &(U64){_t982}, &(U64){_t983});
        (void)_va15;
        Str_delete(_t981, &(Bool){1});
        ;
        ;
        U64 _t984 = 0;
        (void)_t984;
        Str *_t985 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t985;
        Array_set(_va15, &(U64){_t984}, _t985);
        ;
        Str *_t986 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:206:37", 61ULL);
        (void)_t986;
        panic(_t986, _va15);
        Str_delete(_t986, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U64 *_t1026 = malloc(sizeof(U64));
    *_t1026 = 0;
    (void)_t1026;
    U8 *first = Str_get(self, _t1026);
    (void)first;
    U8 _t1027 = 45;
    (void)_t1027;
    Bool _t1028 = U8_eq(DEREF(first), _t1027);
    (void)_t1028;
    U64_delete(_t1026, &(Bool){1});
    ;
    if (_t1028) {
        Bool _t987 = 1;
        (void)_t987;
        neg = _t987;
        ;
        U64 _t988 = 1;
        (void)_t988;
        start = _t988;
        ;
    }
    ;
    Bool _t1029 = U64_eq(start, self->count);
    (void)_t1029;
    if (_t1029) {
        Str *_t989 = Str_lit("Str", 3ULL);
        (void)_t989;
        U64 _t990; { U64 *_hp = (U64 *)Str_size(); _t990 = *_hp; free(_hp); }
        (void)_t990;
        U64 _t991 = 1;
        (void)_t991;
        Array *_va16 = Array_new(_t989, &(U64){_t990}, &(U64){_t991});
        (void)_va16;
        Str_delete(_t989, &(Bool){1});
        ;
        ;
        U64 _t992 = 0;
        (void)_t992;
        Str *_t993 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t993;
        Array_set(_va16, &(U64){_t992}, _t993);
        ;
        Str *_t994 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:215:41", 61ULL);
        (void)_t994;
        panic(_t994, _va16);
        Str_delete(_t994, &(Bool){1});
    }
    ;
    {
        U64 _fi995 = 0;
        (void)_fi995;
        while (1) {
            Range *_t1007 = Range_new(start, self->count);
            (void)_t1007;
            U64 _t1008; { U64 *_hp = (U64 *)Range_len(_t1007); _t1008 = *_hp; free(_hp); }
            (void)_t1008;
            Range_delete(_t1007, &(Bool){1});
            Bool _wcond996; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi995}, &(U64){_t1008}); _wcond996 = *_hp; free(_hp); }
            (void)_wcond996;
            ;
            if (_wcond996) {
            } else {
                ;
                break;
            }
            ;
            Range *_t1009 = Range_new(start, self->count);
            (void)_t1009;
            U64 *i = Range_get(_t1009, _fi995);
            (void)i;
            Range_delete(_t1009, &(Bool){1});
            U64 _t1010 = 1;
            (void)_t1010;
            U64 _t1011 = U64_add(_fi995, _t1010);
            (void)_t1011;
            ;
            _fi995 = _t1011;
            ;
            U8 *ch = Str_get(self, i);
            (void)ch;
            I64 _t1012 = U8_to_i64(DEREF(ch));
            (void)_t1012;
            U64_delete(i, &(Bool){1});
            I64 _t1013 = 48;
            (void)_t1013;
            I64 d = I64_sub(_t1012, _t1013);
            (void)d;
            ;
            ;
            I64 _t1014 = 0;
            (void)_t1014;
            I64 _t1015 = 9;
            (void)_t1015;
            Bool _t1016; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t1014}); _t1016 = *_hp; free(_hp); }
            (void)_t1016;
            ;
            Bool _t1017; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t1015}); _t1017 = *_hp; free(_hp); }
            (void)_t1017;
            ;
            Bool _t1018 = Bool_or(_t1016, _t1017);
            (void)_t1018;
            ;
            ;
            if (_t1018) {
                Str *_t997 = Str_lit("Str", 3ULL);
                (void)_t997;
                U64 _t998; { U64 *_hp = (U64 *)Str_size(); _t998 = *_hp; free(_hp); }
                (void)_t998;
                U64 _t999 = 3;
                (void)_t999;
                Array *_va17 = Array_new(_t997, &(U64){_t998}, &(U64){_t999});
                (void)_va17;
                Str_delete(_t997, &(Bool){1});
                ;
                ;
                U64 _t1000 = 0;
                (void)_t1000;
                Str *_t1001 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                (void)_t1001;
                Array_set(_va17, &(U64){_t1000}, _t1001);
                ;
                U64 _t1002 = 1;
                (void)_t1002;
                Str *_t1003 = Str_clone(self);
                (void)_t1003;
                Array_set(_va17, &(U64){_t1002}, _t1003);
                ;
                U64 _t1004 = 2;
                (void)_t1004;
                Str *_t1005 = Str_lit("'", 1ULL);
                (void)_t1005;
                Array_set(_va17, &(U64){_t1004}, _t1005);
                ;
                Str *_t1006 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:220:23", 61ULL);
                (void)_t1006;
                panic(_t1006, _va17);
                Str_delete(_t1006, &(Bool){1});
            }
            ;
            I64 _t1019 = 10;
            (void)_t1019;
            I64 _t1020 = I64_mul(result, _t1019);
            (void)_t1020;
            ;
            I64 _t1021 = I64_add(_t1020, d);
            (void)_t1021;
            ;
            ;
            result = _t1021;
            ;
        }
        ;
    }
    ;
    if (neg) {
        I64 _t1022 = 0;
        (void)_t1022;
        I64 _t1023 = I64_sub(_t1022, result);
        (void)_t1023;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t1023; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t1046 = Str_lit("Str", 3ULL);
    (void)_t1046;
    U64 _t1047; { U64 *_hp = (U64 *)Str_size(); _t1047 = *_hp; free(_hp); }
    (void)_t1047;
    Vec *parts = Vec_new(_t1046, &(U64){_t1047});
    (void)parts;
    Str_delete(_t1046, &(Bool){1});
    ;
    U64 _t1048; { U64 *_hp = (U64 *)Str_len(delim); _t1048 = *_hp; free(_hp); }
    (void)_t1048;
    U64 _t1049 = 0;
    (void)_t1049;
    Bool _t1050 = U64_eq(_t1048, _t1049);
    (void)_t1050;
    ;
    ;
    if (_t1050) {
        Str *_t1030 = Str_clone(self);
        (void)_t1030;
        Vec_push(parts, _t1030);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1040; { U64 *_hp = (U64 *)Str_len(self); _t1040 = *_hp; free(_hp); }
        (void)_t1040;
        U64 _t1041; { U64 *_hp = (U64 *)Str_len(delim); _t1041 = *_hp; free(_hp); }
        (void)_t1041;
        U64 _t1042 = U64_sub(_t1040, _t1041);
        (void)_t1042;
        ;
        ;
        Bool _wcond1031; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1042}); _wcond1031 = *_hp; free(_hp); }
        (void)_wcond1031;
        ;
        if (_wcond1031) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1043; { U64 *_hp = (U64 *)Str_len(delim); _t1043 = *_hp; free(_hp); }
        (void)_t1043;
        Str *_t1044 = Str_substr(self, &(U64){pos}, &(U64){_t1043});
        (void)_t1044;
        ;
        Bool _t1045; { Bool *_hp = (Bool *)Str_eq(_t1044, delim); _t1045 = *_hp; free(_hp); }
        (void)_t1045;
        Str_delete(_t1044, &(Bool){1});
        if (_t1045) {
            U64 _t1032 = U64_sub(pos, start);
            (void)_t1032;
            Str *_t1033 = Str_substr(self, &(U64){start}, &(U64){_t1032});
            (void)_t1033;
            ;
            Str *_t1034 = Str_clone(_t1033);
            (void)_t1034;
            Str_delete(_t1033, &(Bool){1});
            Vec_push(parts, _t1034);
            U64 _t1035; { U64 *_hp = (U64 *)Str_len(delim); _t1035 = *_hp; free(_hp); }
            (void)_t1035;
            U64 _t1036 = U64_add(pos, _t1035);
            (void)_t1036;
            ;
            start = _t1036;
            ;
            U64 _t1037 = U64_clone(&(U64){start});
            (void)_t1037;
            pos = _t1037;
            ;
        } else {
            U64 _t1038 = 1;
            (void)_t1038;
            U64 _t1039 = U64_add(pos, _t1038);
            (void)_t1039;
            ;
            pos = _t1039;
            ;
        }
        ;
    }
    ;
    U64 _t1051; { U64 *_hp = (U64 *)Str_len(self); _t1051 = *_hp; free(_hp); }
    (void)_t1051;
    U64 _t1052 = U64_sub(_t1051, start);
    (void)_t1052;
    ;
    Str *_t1053 = Str_substr(self, &(U64){start}, &(U64){_t1052});
    (void)_t1053;
    ;
    ;
    Str *_t1054 = Str_clone(_t1053);
    (void)_t1054;
    Str_delete(_t1053, &(Bool){1});
    Vec_push(parts, _t1054);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1090 = malloc(DEREF(elem_size));
    (void)_t1090;
    U64 _t1091 = 0;
    (void)_t1091;
    I64 _t1092 = 1;
    (void)_t1092;
    U64 _t1093 = U64_clone(elem_size);
    (void)_t1093;
    Vec *_t1094 = malloc(sizeof(Vec));
    _t1094->data = _t1090;
    _t1094->count = _t1091;
    _t1094->cap = _t1092;
    _t1094->elem_size = _t1093;
    { Str *_ca = Str_clone(elem_type); _t1094->elem_type = *_ca; free(_ca); }
    (void)_t1094;
    ;
    ;
    ;
    return _t1094;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1099 = U64_eq(self->count, self->cap);
    (void)_t1099;
    if (_t1099) {
        U64 _t1095 = 2;
        (void)_t1095;
        U64 new_cap = U64_mul(self->cap, _t1095);
        (void)new_cap;
        ;
        U64 _t1096 = U64_mul(new_cap, self->elem_size);
        (void)_t1096;
        void *_t1097 = realloc(self->data, _t1096);
        (void)_t1097;
        ;
        self->data = _t1097;
        U64 _t1098 = U64_clone(&(U64){new_cap});
        (void)_t1098;
        ;
        self->cap = _t1098;
        ;
    }
    ;
    U64 *_t1100 = malloc(sizeof(U64)); *_t1100 = U64_mul(self->count, self->elem_size);
    (void)_t1100;
    void *_t1101 = ptr_add(self->data, DEREF(_t1100));
    (void)_t1101;
    memcpy(_t1101, val, self->elem_size);
    U64_delete(_t1100, &(Bool){1});
    free(val);
    U64 _t1102 = 1;
    (void)_t1102;
    U64 _t1103 = U64_add(self->count, _t1102);
    (void)_t1103;
    ;
    self->count = _t1103;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1118; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1118 = *_hp; free(_hp); }
    (void)_t1118;
    if (_t1118) {
        Str *_t1104 = Str_lit("Str", 3ULL);
        (void)_t1104;
        U64 _t1105; { U64 *_hp = (U64 *)Str_size(); _t1105 = *_hp; free(_hp); }
        (void)_t1105;
        U64 _t1106 = 5;
        (void)_t1106;
        Array *_va18 = Array_new(_t1104, &(U64){_t1105}, &(U64){_t1106});
        (void)_va18;
        Str_delete(_t1104, &(Bool){1});
        ;
        ;
        U64 _t1107 = 0;
        (void)_t1107;
        Str *_t1108 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1108;
        Array_set(_va18, &(U64){_t1107}, _t1108);
        ;
        U64 _t1109 = 1;
        (void)_t1109;
        Str *_t1110 = U64_to_str(DEREF(i));
        (void)_t1110;
        Array_set(_va18, &(U64){_t1109}, _t1110);
        ;
        U64 _t1111 = 2;
        (void)_t1111;
        Str *_t1112 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1112;
        Array_set(_va18, &(U64){_t1111}, _t1112);
        ;
        U64 _t1113 = 3;
        (void)_t1113;
        Str *_t1114 = U64_to_str(self->count);
        (void)_t1114;
        Array_set(_va18, &(U64){_t1113}, _t1114);
        ;
        U64 _t1115 = 4;
        (void)_t1115;
        Str *_t1116 = Str_lit(")", 1ULL);
        (void)_t1116;
        Array_set(_va18, &(U64){_t1115}, _t1116);
        ;
        Str *_t1117 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1117;
        panic(_t1117, _va18);
        Str_delete(_t1117, &(Bool){1});
    }
    ;
    U64 *_t1119 = malloc(sizeof(U64)); *_t1119 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1119;
    void *_t1120 = ptr_add(self->data, DEREF(_t1119));
    (void)_t1120;
    U64_delete(_t1119, &(Bool){1});
    return _t1120;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1134; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1134 = *_hp; free(_hp); }
    (void)_t1134;
    Bool _t1135 = Bool_not(_t1134);
    (void)_t1135;
    ;
    if (_t1135) {
        {
            U64 _fi1121 = 0;
            (void)_fi1121;
            while (1) {
                U64 _t1123 = 0;
                (void)_t1123;
                Range *_t1124 = Range_new(_t1123, self->count);
                (void)_t1124;
                ;
                U64 _t1125; { U64 *_hp = (U64 *)Range_len(_t1124); _t1125 = *_hp; free(_hp); }
                (void)_t1125;
                Range_delete(_t1124, &(Bool){1});
                Bool _wcond1122; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1121}, &(U64){_t1125}); _wcond1122 = *_hp; free(_hp); }
                (void)_wcond1122;
                ;
                if (_wcond1122) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1126 = 0;
                (void)_t1126;
                Range *_t1127 = Range_new(_t1126, self->count);
                (void)_t1127;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1127, _fi1121); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1127, &(Bool){1});
                U64 _t1128 = 1;
                (void)_t1128;
                U64 _t1129 = U64_add(_fi1121, _t1128);
                (void)_t1129;
                ;
                _fi1121 = _t1129;
                ;
                U64 *_t1130 = malloc(sizeof(U64)); *_t1130 = U64_mul(i, self->elem_size);
                (void)_t1130;
                ;
                void *_t1131 = ptr_add(self->data, DEREF(_t1130));
                (void)_t1131;
                Bool _t1132 = 0;
                (void)_t1132;
                dyn_call_delete(&self->elem_type, _t1131, &(Bool){_t1132});
                U64_delete(_t1130, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1136; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1136 = *_hp; free(_hp); }
    (void)_t1136;
    Bool _t1137 = Bool_not(_t1136);
    (void)_t1137;
    ;
    if (_t1137) {
        Bool _t1133 = 0;
        (void)_t1133;
        Str_delete(&self->elem_type, &(Bool){_t1133});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1152 = U64_mul(self->cap, self->elem_size);
    (void)_t1152;
    U8 *new_data = malloc(_t1152);
    (void)new_data;
    ;
    Bool _t1153; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1153 = *_hp; free(_hp); }
    (void)_t1153;
    Bool _t1154 = Bool_not(_t1153);
    (void)_t1154;
    ;
    if (_t1154) {
        {
            U64 _fi1138 = 0;
            (void)_fi1138;
            while (1) {
                U64 _t1140 = 0;
                (void)_t1140;
                Range *_t1141 = Range_new(_t1140, self->count);
                (void)_t1141;
                ;
                U64 _t1142; { U64 *_hp = (U64 *)Range_len(_t1141); _t1142 = *_hp; free(_hp); }
                (void)_t1142;
                Range_delete(_t1141, &(Bool){1});
                Bool _wcond1139; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1138}, &(U64){_t1142}); _wcond1139 = *_hp; free(_hp); }
                (void)_wcond1139;
                ;
                if (_wcond1139) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1143 = 0;
                (void)_t1143;
                Range *_t1144 = Range_new(_t1143, self->count);
                (void)_t1144;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1144, _fi1138); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1144, &(Bool){1});
                U64 _t1145 = 1;
                (void)_t1145;
                U64 _t1146 = U64_add(_fi1138, _t1145);
                (void)_t1146;
                ;
                _fi1138 = _t1146;
                ;
                U64 *_t1147 = malloc(sizeof(U64)); *_t1147 = U64_mul(i, self->elem_size);
                (void)_t1147;
                void *_t1148 = ptr_add(self->data, DEREF(_t1147));
                (void)_t1148;
                void *cloned = dyn_call_clone(&self->elem_type, _t1148);
                (void)cloned;
                U64_delete(_t1147, &(Bool){1});
                U64 *_t1149 = malloc(sizeof(U64)); *_t1149 = U64_mul(i, self->elem_size);
                (void)_t1149;
                ;
                void *_t1150 = ptr_add(new_data, DEREF(_t1149));
                (void)_t1150;
                memcpy(_t1150, cloned, self->elem_size);
                U64_delete(_t1149, &(Bool){1});
                free(cloned);
            }
            ;
        }
    } else {
        U64 _t1151 = U64_mul(self->count, self->elem_size);
        (void)_t1151;
        memcpy(new_data, self->data, _t1151);
        ;
    }
    ;
    Vec *_t1155 = malloc(sizeof(Vec));
    _t1155->data = new_data;
    _t1155->count = self->count;
    _t1155->cap = self->cap;
    _t1155->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1155->elem_type = *_ca; free(_ca); }
    (void)_t1155;
    return _t1155;
}

Tuple * Tuple_new(void) {
    U64 _t1157 = 8;
    (void)_t1157;
    Str *_t1158 = Str_lit("Str", 3ULL);
    (void)_t1158;
    U64 _t1159; { U64 *_hp = (U64 *)Str_size(); _t1159 = *_hp; free(_hp); }
    (void)_t1159;
    Str *_t1160 = Str_lit("U64", 3ULL);
    (void)_t1160;
    U64 _t1161; { U64 *_hp = (U64 *)U64_size(); _t1161 = *_hp; free(_hp); }
    (void)_t1161;
    void *_t1162 = malloc(_t1157);
    (void)_t1162;
    ;
    U64 _t1163 = 0;
    (void)_t1163;
    I64 _t1164 = 8;
    (void)_t1164;
    Tuple *_t1165 = malloc(sizeof(Tuple));
    _t1165->data = _t1162;
    _t1165->total_size = _t1163;
    _t1165->cap = _t1164;
    { Vec *_ca = Vec_new(_t1158, &(U64){_t1159}); _t1165->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1160, &(U64){_t1161}); _t1165->type_sizes = *_ca; free(_ca); }
    (void)_t1165;
    Str_delete(_t1158, &(Bool){1});
    ;
    Str_delete(_t1160, &(Bool){1});
    ;
    ;
    ;
    return _t1165;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1166; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1166 = *_hp; free(_hp); }
    (void)_t1166;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1166; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1173; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1173 = *_hp; free(_hp); }
    (void)_t1173;
    if (_t1173) {
        U64 _t1170 = 2;
        (void)_t1170;
        U64 new_cap = U64_mul(self->cap, _t1170);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1167; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1167 = *_hp; free(_hp); }
            (void)_wcond1167;
            if (_wcond1167) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1168 = 2;
            (void)_t1168;
            U64 _t1169 = U64_mul(new_cap, _t1168);
            (void)_t1169;
            ;
            new_cap = _t1169;
            ;
        }
        void *_t1171 = realloc(self->data, new_cap);
        (void)_t1171;
        self->data = _t1171;
        U64 _t1172 = U64_clone(&(U64){new_cap});
        (void)_t1172;
        ;
        self->cap = _t1172;
        ;
    }
    ;
    void *_t1174 = ptr_add(self->data, self->total_size);
    (void)_t1174;
    memcpy(_t1174, val, DEREF(elem_size));
    free(val);
    Str *_t1175 = Str_clone(elem_type);
    (void)_t1175;
    Vec_push(&self->type_names, _t1175);
    U64 _t1176 = U64_clone(elem_size);
    (void)_t1176;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1176; _oa; }));
    U64 _t1177 = U64_clone(&(U64){new_total});
    (void)_t1177;
    ;
    self->total_size = _t1177;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1203; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    Bool _t1204; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1203}); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    ;
    if (_t1204) {
        Str *_t1178 = Str_lit("Str", 3ULL);
        (void)_t1178;
        U64 _t1179; { U64 *_hp = (U64 *)Str_size(); _t1179 = *_hp; free(_hp); }
        (void)_t1179;
        U64 _t1180 = 5;
        (void)_t1180;
        Array *_va19 = Array_new(_t1178, &(U64){_t1179}, &(U64){_t1180});
        (void)_va19;
        Str_delete(_t1178, &(Bool){1});
        ;
        ;
        U64 _t1181 = 0;
        (void)_t1181;
        Str *_t1182 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1182;
        Array_set(_va19, &(U64){_t1181}, _t1182);
        ;
        U64 _t1183 = 1;
        (void)_t1183;
        Str *_t1184 = U64_to_str(DEREF(i));
        (void)_t1184;
        Array_set(_va19, &(U64){_t1183}, _t1184);
        ;
        U64 _t1185 = 2;
        (void)_t1185;
        Str *_t1186 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1186;
        Array_set(_va19, &(U64){_t1185}, _t1186);
        ;
        U64 _t1187; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1187 = *_hp; free(_hp); }
        (void)_t1187;
        U64 _t1188 = 3;
        (void)_t1188;
        Str *_t1189 = U64_to_str(_t1187);
        (void)_t1189;
        ;
        Array_set(_va19, &(U64){_t1188}, _t1189);
        ;
        U64 _t1190 = 4;
        (void)_t1190;
        Str *_t1191 = Str_lit(")", 1ULL);
        (void)_t1191;
        Array_set(_va19, &(U64){_t1190}, _t1191);
        ;
        Str *_t1192 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1192;
        panic(_t1192, _va19);
        Str_delete(_t1192, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1193 = 0;
        (void)_fi1193;
        while (1) {
            U64 _t1195 = 0;
            (void)_t1195;
            Range *_t1196 = Range_new(_t1195, DEREF(i));
            (void)_t1196;
            ;
            U64 _t1197; { U64 *_hp = (U64 *)Range_len(_t1196); _t1197 = *_hp; free(_hp); }
            (void)_t1197;
            Range_delete(_t1196, &(Bool){1});
            Bool _wcond1194; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1193}, &(U64){_t1197}); _wcond1194 = *_hp; free(_hp); }
            (void)_wcond1194;
            ;
            if (_wcond1194) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1198 = 0;
            (void)_t1198;
            Range *_t1199 = Range_new(_t1198, DEREF(i));
            (void)_t1199;
            ;
            U64 *j = Range_get(_t1199, _fi1193);
            (void)j;
            Range_delete(_t1199, &(Bool){1});
            U64 _t1200 = 1;
            (void)_t1200;
            U64 _t1201 = U64_add(_fi1193, _t1200);
            (void)_t1201;
            ;
            _fi1193 = _t1201;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1202 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1202;
            U64_delete(j, &(Bool){1});
            *offset = _t1202;
            ;
        }
        ;
    }
    void *_t1205 = ptr_add(self->data, DEREF(offset));
    (void)_t1205;
    U64_delete(offset, &(Bool){1});
    return _t1205;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1206 = Vec_get(&self->type_names, i);
    (void)_t1206;
    return _t1206;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1207 = Vec_get(&self->type_sizes, i);
    (void)_t1207;
    return _t1207;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1208 = 0;
        (void)_fi1208;
        while (1) {
            U64 _t1210 = 0;
            (void)_t1210;
            U64 _t1211; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1211 = *_hp; free(_hp); }
            (void)_t1211;
            Range *_t1212 = Range_new(_t1210, _t1211);
            (void)_t1212;
            ;
            ;
            U64 _t1213; { U64 *_hp = (U64 *)Range_len(_t1212); _t1213 = *_hp; free(_hp); }
            (void)_t1213;
            Range_delete(_t1212, &(Bool){1});
            Bool _wcond1209; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1208}, &(U64){_t1213}); _wcond1209 = *_hp; free(_hp); }
            (void)_wcond1209;
            ;
            if (_wcond1209) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1214 = 0;
            (void)_t1214;
            U64 _t1215; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1215 = *_hp; free(_hp); }
            (void)_t1215;
            Range *_t1216 = Range_new(_t1214, _t1215);
            (void)_t1216;
            ;
            ;
            U64 *i = Range_get(_t1216, _fi1208);
            (void)i;
            Range_delete(_t1216, &(Bool){1});
            U64 _t1217 = 1;
            (void)_t1217;
            U64 _t1218 = U64_add(_fi1208, _t1217);
            (void)_t1218;
            ;
            _fi1208 = _t1218;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1219 = ptr_add(self->data, DEREF(offset));
            (void)_t1219;
            Bool _t1220 = 0;
            (void)_t1220;
            dyn_call_delete(tn, _t1219, &(Bool){_t1220});
            ;
            U64 _t1221 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1221;
            U64_delete(i, &(Bool){1});
            *offset = _t1221;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1222 = 0;
    (void)_t1222;
    Vec_delete(&self->type_names, &(Bool){_t1222});
    ;
    Bool _t1223 = 0;
    (void)_t1223;
    Vec_delete(&self->type_sizes, &(Bool){_t1223});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1240 = 0;
    (void)_t1240;
    Bool _t1241 = U64_eq(new_cap, _t1240);
    (void)_t1241;
    ;
    if (_t1241) {
        I64 _t1224 = 8;
        (void)_t1224;
        U64 _t1225; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1224}); _t1225 = *_hp; free(_hp); }
        (void)_t1225;
        ;
        new_cap = _t1225;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1226 = 0;
        (void)_fi1226;
        while (1) {
            U64 _t1228 = 0;
            (void)_t1228;
            U64 _t1229; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1229 = *_hp; free(_hp); }
            (void)_t1229;
            Range *_t1230 = Range_new(_t1228, _t1229);
            (void)_t1230;
            ;
            ;
            U64 _t1231; { U64 *_hp = (U64 *)Range_len(_t1230); _t1231 = *_hp; free(_hp); }
            (void)_t1231;
            Range_delete(_t1230, &(Bool){1});
            Bool _wcond1227; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1226}, &(U64){_t1231}); _wcond1227 = *_hp; free(_hp); }
            (void)_wcond1227;
            ;
            if (_wcond1227) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1232 = 0;
            (void)_t1232;
            U64 _t1233; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1233 = *_hp; free(_hp); }
            (void)_t1233;
            Range *_t1234 = Range_new(_t1232, _t1233);
            (void)_t1234;
            ;
            ;
            U64 *i = Range_get(_t1234, _fi1226);
            (void)i;
            Range_delete(_t1234, &(Bool){1});
            U64 _t1235 = 1;
            (void)_t1235;
            U64 _t1236 = U64_add(_fi1226, _t1235);
            (void)_t1236;
            ;
            _fi1226 = _t1236;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1237 = ptr_add(self->data, DEREF(offset));
            (void)_t1237;
            void *cloned = dyn_call_clone(tn, _t1237);
            (void)cloned;
            void *_t1238 = ptr_add(new_data, DEREF(offset));
            (void)_t1238;
            memcpy(_t1238, cloned, DEREF(ts));
            free(cloned);
            U64 _t1239 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1239;
            U64_delete(i, &(Bool){1});
            *offset = _t1239;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1242 = U64_clone(&(U64){new_cap});
    (void)_t1242;
    ;
    Vec *_t1243 = Vec_clone(&self->type_names);
    (void)_t1243;
    Vec *_t1244 = Vec_clone(&self->type_sizes);
    (void)_t1244;
    Tuple *_t1245 = malloc(sizeof(Tuple));
    _t1245->data = new_data;
    _t1245->total_size = self->total_size;
    _t1245->cap = _t1242;
    { Vec *_ca = Vec_clone(_t1243); _t1245->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1244); _t1245->type_sizes = *_ca; free(_ca); }
    (void)_t1245;
    ;
    Vec_delete(_t1243, &(Bool){1});
    Vec_delete(_t1244, &(Bool){1});
    return _t1245;
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
    Bool _t1264; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        Bool _t1247; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t1247 = *_hp; free(_hp); }
        (void)_t1247;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1247; return _r; }
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TilType_is_None(self); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        Bool _t1248; { Bool *_hp = (Bool *)TilType_is_None(other); _t1248 = *_hp; free(_hp); }
        (void)_t1248;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1248; return _r; }
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TilType_is_I64(self); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        Bool _t1249; { Bool *_hp = (Bool *)TilType_is_I64(other); _t1249 = *_hp; free(_hp); }
        (void)_t1249;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1249; return _r; }
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TilType_is_U8(self); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        Bool _t1250; { Bool *_hp = (Bool *)TilType_is_U8(other); _t1250 = *_hp; free(_hp); }
        (void)_t1250;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1250; return _r; }
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TilType_is_I16(self); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        Bool _t1251; { Bool *_hp = (Bool *)TilType_is_I16(other); _t1251 = *_hp; free(_hp); }
        (void)_t1251;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1251; return _r; }
    }
    ;
    Bool _t1269; { Bool *_hp = (Bool *)TilType_is_I32(self); _t1269 = *_hp; free(_hp); }
    (void)_t1269;
    if (_t1269) {
        Bool _t1252; { Bool *_hp = (Bool *)TilType_is_I32(other); _t1252 = *_hp; free(_hp); }
        (void)_t1252;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1252; return _r; }
    }
    ;
    Bool _t1270; { Bool *_hp = (Bool *)TilType_is_U32(self); _t1270 = *_hp; free(_hp); }
    (void)_t1270;
    if (_t1270) {
        Bool _t1253; { Bool *_hp = (Bool *)TilType_is_U32(other); _t1253 = *_hp; free(_hp); }
        (void)_t1253;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1253; return _r; }
    }
    ;
    Bool _t1271; { Bool *_hp = (Bool *)TilType_is_U64(self); _t1271 = *_hp; free(_hp); }
    (void)_t1271;
    if (_t1271) {
        Bool _t1254; { Bool *_hp = (Bool *)TilType_is_U64(other); _t1254 = *_hp; free(_hp); }
        (void)_t1254;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1254; return _r; }
    }
    ;
    Bool _t1272; { Bool *_hp = (Bool *)TilType_is_F32(self); _t1272 = *_hp; free(_hp); }
    (void)_t1272;
    if (_t1272) {
        Bool _t1255; { Bool *_hp = (Bool *)TilType_is_F32(other); _t1255 = *_hp; free(_hp); }
        (void)_t1255;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1255; return _r; }
    }
    ;
    Bool _t1273; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t1273 = *_hp; free(_hp); }
    (void)_t1273;
    if (_t1273) {
        Bool _t1256; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t1256 = *_hp; free(_hp); }
        (void)_t1256;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1256; return _r; }
    }
    ;
    Bool _t1274; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t1274 = *_hp; free(_hp); }
    (void)_t1274;
    if (_t1274) {
        Bool _t1257; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t1257 = *_hp; free(_hp); }
        (void)_t1257;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1257; return _r; }
    }
    ;
    Bool _t1275; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t1275 = *_hp; free(_hp); }
    (void)_t1275;
    if (_t1275) {
        Bool _t1258; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t1258 = *_hp; free(_hp); }
        (void)_t1258;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1258; return _r; }
    }
    ;
    Bool _t1276; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t1276 = *_hp; free(_hp); }
    (void)_t1276;
    if (_t1276) {
        Bool _t1259; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t1259 = *_hp; free(_hp); }
        (void)_t1259;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1259; return _r; }
    }
    ;
    Bool _t1277; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t1277 = *_hp; free(_hp); }
    (void)_t1277;
    if (_t1277) {
        Bool _t1260; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t1260 = *_hp; free(_hp); }
        (void)_t1260;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1260; return _r; }
    }
    ;
    Bool _t1278; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t1278 = *_hp; free(_hp); }
    (void)_t1278;
    if (_t1278) {
        Bool _t1261; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t1261 = *_hp; free(_hp); }
        (void)_t1261;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1261; return _r; }
    }
    ;
    Bool _t1279; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t1279 = *_hp; free(_hp); }
    (void)_t1279;
    if (_t1279) {
        Bool _t1262; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t1262 = *_hp; free(_hp); }
        (void)_t1262;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1262; return _r; }
    }
    ;
    Bool _t1280; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        Bool _t1263; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t1263 = *_hp; free(_hp); }
        (void)_t1263;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1263; return _r; }
    }
    ;
    Bool _t1281 = 0;
    (void)_t1281;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1281; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t1282; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        ;
        return TilType_None();
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t1297; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1297 = *_hp; free(_hp); }
    (void)_t1297;
    if (_t1297) {
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
    Bool _t1315; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t1315 = *_hp; free(_hp); }
    (void)_t1315;
    if (_t1315) {
        Str *_t1298 = Str_lit("Unknown", 7ULL);
        (void)_t1298;
        ;
        return _t1298;
    }
    ;
    Bool _t1316; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t1316 = *_hp; free(_hp); }
    (void)_t1316;
    if (_t1316) {
        Str *_t1299 = Str_lit("None", 4ULL);
        (void)_t1299;
        ;
        return _t1299;
    }
    ;
    Bool _t1317; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t1317 = *_hp; free(_hp); }
    (void)_t1317;
    if (_t1317) {
        Str *_t1300 = Str_lit("I64", 3ULL);
        (void)_t1300;
        ;
        return _t1300;
    }
    ;
    Bool _t1318; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t1318 = *_hp; free(_hp); }
    (void)_t1318;
    if (_t1318) {
        Str *_t1301 = Str_lit("U8", 2ULL);
        (void)_t1301;
        ;
        return _t1301;
    }
    ;
    Bool _t1319; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t1319 = *_hp; free(_hp); }
    (void)_t1319;
    if (_t1319) {
        Str *_t1302 = Str_lit("I16", 3ULL);
        (void)_t1302;
        ;
        return _t1302;
    }
    ;
    Bool _t1320; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t1320 = *_hp; free(_hp); }
    (void)_t1320;
    if (_t1320) {
        Str *_t1303 = Str_lit("I32", 3ULL);
        (void)_t1303;
        ;
        return _t1303;
    }
    ;
    Bool _t1321; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t1321 = *_hp; free(_hp); }
    (void)_t1321;
    if (_t1321) {
        Str *_t1304 = Str_lit("U32", 3ULL);
        (void)_t1304;
        ;
        return _t1304;
    }
    ;
    Bool _t1322; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t1322 = *_hp; free(_hp); }
    (void)_t1322;
    if (_t1322) {
        Str *_t1305 = Str_lit("U64", 3ULL);
        (void)_t1305;
        ;
        return _t1305;
    }
    ;
    Bool _t1323; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t1323 = *_hp; free(_hp); }
    (void)_t1323;
    if (_t1323) {
        Str *_t1306 = Str_lit("F32", 3ULL);
        (void)_t1306;
        ;
        return _t1306;
    }
    ;
    Bool _t1324; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t1324 = *_hp; free(_hp); }
    (void)_t1324;
    if (_t1324) {
        Str *_t1307 = Str_lit("Bool", 4ULL);
        (void)_t1307;
        ;
        return _t1307;
    }
    ;
    Bool _t1325; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t1325 = *_hp; free(_hp); }
    (void)_t1325;
    if (_t1325) {
        Str *_t1308 = Str_lit("Struct", 6ULL);
        (void)_t1308;
        ;
        return _t1308;
    }
    ;
    Bool _t1326; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t1326 = *_hp; free(_hp); }
    (void)_t1326;
    if (_t1326) {
        Str *_t1309 = Str_lit("StructDef", 9ULL);
        (void)_t1309;
        ;
        return _t1309;
    }
    ;
    Bool _t1327; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t1327 = *_hp; free(_hp); }
    (void)_t1327;
    if (_t1327) {
        Str *_t1310 = Str_lit("Enum", 4ULL);
        (void)_t1310;
        ;
        return _t1310;
    }
    ;
    Bool _t1328; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t1328 = *_hp; free(_hp); }
    (void)_t1328;
    if (_t1328) {
        Str *_t1311 = Str_lit("EnumDef", 7ULL);
        (void)_t1311;
        ;
        return _t1311;
    }
    ;
    Bool _t1329; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t1329 = *_hp; free(_hp); }
    (void)_t1329;
    if (_t1329) {
        Str *_t1312 = Str_lit("FuncDef", 7ULL);
        (void)_t1312;
        ;
        return _t1312;
    }
    ;
    Bool _t1330; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t1330 = *_hp; free(_hp); }
    (void)_t1330;
    if (_t1330) {
        Str *_t1313 = Str_lit("FuncPtr", 7ULL);
        (void)_t1313;
        ;
        return _t1313;
    }
    ;
    Bool _t1331; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t1331 = *_hp; free(_hp); }
    (void)_t1331;
    if (_t1331) {
        Str *_t1314 = Str_lit("Dynamic", 7ULL);
        (void)_t1314;
        ;
        return _t1314;
    }
    ;
    Str *_t1332 = Str_lit("unknown", 7ULL);
    (void)_t1332;
    return _t1332;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t1370; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1370; return _r; }
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
    Bool _t1393; { Bool *_hp = (Bool *)FuncType_is_Func(self); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Bool _t1387; { Bool *_hp = (Bool *)FuncType_is_Func(other); _t1387 = *_hp; free(_hp); }
        (void)_t1387;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1387; return _r; }
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)FuncType_is_Proc(self); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Bool _t1388; { Bool *_hp = (Bool *)FuncType_is_Proc(other); _t1388 = *_hp; free(_hp); }
        (void)_t1388;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1388; return _r; }
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)FuncType_is_Test(self); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Bool _t1389; { Bool *_hp = (Bool *)FuncType_is_Test(other); _t1389 = *_hp; free(_hp); }
        (void)_t1389;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1389; return _r; }
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)FuncType_is_Macro(self); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Bool _t1390; { Bool *_hp = (Bool *)FuncType_is_Macro(other); _t1390 = *_hp; free(_hp); }
        (void)_t1390;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1390; return _r; }
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(self); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Bool _t1391; { Bool *_hp = (Bool *)FuncType_is_ExtFunc(other); _t1391 = *_hp; free(_hp); }
        (void)_t1391;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1391; return _r; }
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)FuncType_is_ExtProc(self); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        Bool _t1392; { Bool *_hp = (Bool *)FuncType_is_ExtProc(other); _t1392 = *_hp; free(_hp); }
        (void)_t1392;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1392; return _r; }
    }
    ;
    Bool _t1399 = 0;
    (void)_t1399;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1399; return _r; }
}

FuncType * FuncType_clone(FuncType * self) {
    (void)self;
    Bool _t1400; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        ;
        return FuncType_Func();
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        ;
        return FuncType_Proc();
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        ;
        return FuncType_Test();
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        ;
        return FuncType_Macro();
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
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
    Bool _t1411; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Func()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        Str *_t1405 = Str_lit("Func", 4ULL);
        (void)_t1405;
        ;
        return _t1405;
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Proc()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        Str *_t1406 = Str_lit("Proc", 4ULL);
        (void)_t1406;
        ;
        return _t1406;
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Test()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        Str *_t1407 = Str_lit("Test", 4ULL);
        (void)_t1407;
        ;
        return _t1407;
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_Macro()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        Str *_t1408 = Str_lit("Macro", 5ULL);
        (void)_t1408;
        ;
        return _t1408;
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtFunc()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        Str *_t1409 = Str_lit("ExtFunc", 7ULL);
        (void)_t1409;
        ;
        return _t1409;
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)FuncType_eq(self, FuncType_ExtProc()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        Str *_t1410 = Str_lit("ExtProc", 7ULL);
        (void)_t1410;
        ;
        return _t1410;
    }
    ;
    Str *_t1417 = Str_lit("unknown", 7ULL);
    (void)_t1417;
    return _t1417;
}

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
}


Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b) {
    (void)a;
    (void)b;
    Bool _t1429; { Bool *_hp = (Bool *)Str_eq(&a->return_type, &b->return_type); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1429; return _r; }
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
    Bool _t1526; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1526 = *_hp; free(_hp); }
    (void)_t1526;
    if (_t1526) {
        Bool _t1446; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t1446 = *_hp; free(_hp); }
        (void)_t1446;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1446; return _r; }
    }
    ;
    Bool _t1527; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1527 = *_hp; free(_hp); }
    (void)_t1527;
    if (_t1527) {
        Bool _t1448; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t1448 = *_hp; free(_hp); }
        (void)_t1448;
        Bool _t1449 = Bool_not(_t1448);
        (void)_t1449;
        ;
        if (_t1449) {
            Bool _t1447 = 0;
            (void)_t1447;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1447; return _r; }
        }
        ;
        Str *_t1450 = ExprData_get_LiteralStr(self);
        (void)_t1450;
        Str *_t1451 = ExprData_get_LiteralStr(other);
        (void)_t1451;
        Bool _t1452; { Bool *_hp = (Bool *)Str_eq(_t1450, _t1451); _t1452 = *_hp; free(_hp); }
        (void)_t1452;
        Str_delete(_t1450, &(Bool){1});
        Str_delete(_t1451, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1452; return _r; }
    }
    ;
    Bool _t1528; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1528 = *_hp; free(_hp); }
    (void)_t1528;
    if (_t1528) {
        Bool _t1454; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t1454 = *_hp; free(_hp); }
        (void)_t1454;
        Bool _t1455 = Bool_not(_t1454);
        (void)_t1455;
        ;
        if (_t1455) {
            Bool _t1453 = 0;
            (void)_t1453;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1453; return _r; }
        }
        ;
        Str *_t1456 = ExprData_get_LiteralNum(self);
        (void)_t1456;
        Str *_t1457 = ExprData_get_LiteralNum(other);
        (void)_t1457;
        Bool _t1458; { Bool *_hp = (Bool *)Str_eq(_t1456, _t1457); _t1458 = *_hp; free(_hp); }
        (void)_t1458;
        Str_delete(_t1456, &(Bool){1});
        Str_delete(_t1457, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1458; return _r; }
    }
    ;
    Bool _t1529; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1529 = *_hp; free(_hp); }
    (void)_t1529;
    if (_t1529) {
        Bool _t1460; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t1460 = *_hp; free(_hp); }
        (void)_t1460;
        Bool _t1461 = Bool_not(_t1460);
        (void)_t1461;
        ;
        if (_t1461) {
            Bool _t1459 = 0;
            (void)_t1459;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1459; return _r; }
        }
        ;
        Str *_t1462 = ExprData_get_LiteralBool(self);
        (void)_t1462;
        Str *_t1463 = ExprData_get_LiteralBool(other);
        (void)_t1463;
        Bool _t1464; { Bool *_hp = (Bool *)Str_eq(_t1462, _t1463); _t1464 = *_hp; free(_hp); }
        (void)_t1464;
        Str_delete(_t1462, &(Bool){1});
        Str_delete(_t1463, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1464; return _r; }
    }
    ;
    Bool _t1530; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Bool _t1465; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t1465 = *_hp; free(_hp); }
        (void)_t1465;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1465; return _r; }
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        Bool _t1467; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t1467 = *_hp; free(_hp); }
        (void)_t1467;
        Bool _t1468 = Bool_not(_t1467);
        (void)_t1468;
        ;
        if (_t1468) {
            Bool _t1466 = 0;
            (void)_t1466;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1466; return _r; }
        }
        ;
        Str *_t1469 = ExprData_get_Ident(self);
        (void)_t1469;
        Str *_t1470 = ExprData_get_Ident(other);
        (void)_t1470;
        Bool _t1471; { Bool *_hp = (Bool *)Str_eq(_t1469, _t1470); _t1471 = *_hp; free(_hp); }
        (void)_t1471;
        Str_delete(_t1469, &(Bool){1});
        Str_delete(_t1470, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1471; return _r; }
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        Bool _t1473; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t1473 = *_hp; free(_hp); }
        (void)_t1473;
        Bool _t1474 = Bool_not(_t1473);
        (void)_t1474;
        ;
        if (_t1474) {
            Bool _t1472 = 0;
            (void)_t1472;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1472; return _r; }
        }
        ;
        Declaration *_t1475 = ExprData_get_Decl(self);
        (void)_t1475;
        Declaration *_t1476 = ExprData_get_Decl(other);
        (void)_t1476;
        Bool _t1477; { Bool *_hp = (Bool *)Declaration_eq(_t1475, _t1476); _t1477 = *_hp; free(_hp); }
        (void)_t1477;
        Declaration_delete(_t1475, &(Bool){1});
        Declaration_delete(_t1476, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1477; return _r; }
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        Bool _t1479; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t1479 = *_hp; free(_hp); }
        (void)_t1479;
        Bool _t1480 = Bool_not(_t1479);
        (void)_t1480;
        ;
        if (_t1480) {
            Bool _t1478 = 0;
            (void)_t1478;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1478; return _r; }
        }
        ;
        Str *_t1481 = ExprData_get_Assign(self);
        (void)_t1481;
        Str *_t1482 = ExprData_get_Assign(other);
        (void)_t1482;
        Bool _t1483; { Bool *_hp = (Bool *)Str_eq(_t1481, _t1482); _t1483 = *_hp; free(_hp); }
        (void)_t1483;
        Str_delete(_t1481, &(Bool){1});
        Str_delete(_t1482, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1483; return _r; }
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        Bool _t1484; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t1484 = *_hp; free(_hp); }
        (void)_t1484;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1484; return _r; }
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
        Bool _t1486; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t1486 = *_hp; free(_hp); }
        (void)_t1486;
        Bool _t1487 = Bool_not(_t1486);
        (void)_t1487;
        ;
        if (_t1487) {
            Bool _t1485 = 0;
            (void)_t1485;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1485; return _r; }
        }
        ;
        FunctionDef *_t1488 = ExprData_get_FuncDef(self);
        (void)_t1488;
        FunctionDef *_t1489 = ExprData_get_FuncDef(other);
        (void)_t1489;
        Bool _t1490; { Bool *_hp = (Bool *)FunctionDef_eq(_t1488, _t1489); _t1490 = *_hp; free(_hp); }
        (void)_t1490;
        FunctionDef_delete(_t1488, &(Bool){1});
        FunctionDef_delete(_t1489, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1490; return _r; }
    }
    ;
    Bool _t1536; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1536 = *_hp; free(_hp); }
    (void)_t1536;
    if (_t1536) {
        Bool _t1491; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t1491 = *_hp; free(_hp); }
        (void)_t1491;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1491; return _r; }
    }
    ;
    Bool _t1537; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1537 = *_hp; free(_hp); }
    (void)_t1537;
    if (_t1537) {
        Bool _t1492; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t1492 = *_hp; free(_hp); }
        (void)_t1492;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1492; return _r; }
    }
    ;
    Bool _t1538; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1538 = *_hp; free(_hp); }
    (void)_t1538;
    if (_t1538) {
        Bool _t1494; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t1494 = *_hp; free(_hp); }
        (void)_t1494;
        Bool _t1495 = Bool_not(_t1494);
        (void)_t1495;
        ;
        if (_t1495) {
            Bool _t1493 = 0;
            (void)_t1493;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1493; return _r; }
        }
        ;
        Str *_t1496 = ExprData_get_FieldAccess(self);
        (void)_t1496;
        Str *_t1497 = ExprData_get_FieldAccess(other);
        (void)_t1497;
        Bool _t1498; { Bool *_hp = (Bool *)Str_eq(_t1496, _t1497); _t1498 = *_hp; free(_hp); }
        (void)_t1498;
        Str_delete(_t1496, &(Bool){1});
        Str_delete(_t1497, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1498; return _r; }
    }
    ;
    Bool _t1539; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1539 = *_hp; free(_hp); }
    (void)_t1539;
    if (_t1539) {
        Bool _t1500; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t1500 = *_hp; free(_hp); }
        (void)_t1500;
        Bool _t1501 = Bool_not(_t1500);
        (void)_t1501;
        ;
        if (_t1501) {
            Bool _t1499 = 0;
            (void)_t1499;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1499; return _r; }
        }
        ;
        Str *_t1502 = ExprData_get_FieldAssign(self);
        (void)_t1502;
        Str *_t1503 = ExprData_get_FieldAssign(other);
        (void)_t1503;
        Bool _t1504; { Bool *_hp = (Bool *)Str_eq(_t1502, _t1503); _t1504 = *_hp; free(_hp); }
        (void)_t1504;
        Str_delete(_t1502, &(Bool){1});
        Str_delete(_t1503, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1504; return _r; }
    }
    ;
    Bool _t1540; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1540 = *_hp; free(_hp); }
    (void)_t1540;
    if (_t1540) {
        Bool _t1505; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t1505 = *_hp; free(_hp); }
        (void)_t1505;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1505; return _r; }
    }
    ;
    Bool _t1541; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1541 = *_hp; free(_hp); }
    (void)_t1541;
    if (_t1541) {
        Bool _t1506; { Bool *_hp = (Bool *)ExprData_is_If(other); _t1506 = *_hp; free(_hp); }
        (void)_t1506;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1506; return _r; }
    }
    ;
    Bool _t1542; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1542 = *_hp; free(_hp); }
    (void)_t1542;
    if (_t1542) {
        Bool _t1507; { Bool *_hp = (Bool *)ExprData_is_While(other); _t1507 = *_hp; free(_hp); }
        (void)_t1507;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1507; return _r; }
    }
    ;
    Bool _t1543; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1543 = *_hp; free(_hp); }
    (void)_t1543;
    if (_t1543) {
        Bool _t1509; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t1509 = *_hp; free(_hp); }
        (void)_t1509;
        Bool _t1510 = Bool_not(_t1509);
        (void)_t1510;
        ;
        if (_t1510) {
            Bool _t1508 = 0;
            (void)_t1508;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1508; return _r; }
        }
        ;
        Str *_t1511 = ExprData_get_ForIn(self);
        (void)_t1511;
        Str *_t1512 = ExprData_get_ForIn(other);
        (void)_t1512;
        Bool _t1513; { Bool *_hp = (Bool *)Str_eq(_t1511, _t1512); _t1513 = *_hp; free(_hp); }
        (void)_t1513;
        Str_delete(_t1511, &(Bool){1});
        Str_delete(_t1512, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1513; return _r; }
    }
    ;
    Bool _t1544; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1544 = *_hp; free(_hp); }
    (void)_t1544;
    if (_t1544) {
        Bool _t1515; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t1515 = *_hp; free(_hp); }
        (void)_t1515;
        Bool _t1516 = Bool_not(_t1515);
        (void)_t1516;
        ;
        if (_t1516) {
            Bool _t1514 = 0;
            (void)_t1514;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t1514; return _r; }
        }
        ;
        Str *_t1517 = ExprData_get_NamedArg(self);
        (void)_t1517;
        Str *_t1518 = ExprData_get_NamedArg(other);
        (void)_t1518;
        Bool _t1519; { Bool *_hp = (Bool *)Str_eq(_t1517, _t1518); _t1519 = *_hp; free(_hp); }
        (void)_t1519;
        Str_delete(_t1517, &(Bool){1});
        Str_delete(_t1518, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1519; return _r; }
    }
    ;
    Bool _t1545; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1545 = *_hp; free(_hp); }
    (void)_t1545;
    if (_t1545) {
        Bool _t1520; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t1520 = *_hp; free(_hp); }
        (void)_t1520;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1520; return _r; }
    }
    ;
    Bool _t1546; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1546 = *_hp; free(_hp); }
    (void)_t1546;
    if (_t1546) {
        Bool _t1521; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t1521 = *_hp; free(_hp); }
        (void)_t1521;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1521; return _r; }
    }
    ;
    Bool _t1547; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1547 = *_hp; free(_hp); }
    (void)_t1547;
    if (_t1547) {
        Bool _t1522; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t1522 = *_hp; free(_hp); }
        (void)_t1522;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1522; return _r; }
    }
    ;
    Bool _t1548; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1548 = *_hp; free(_hp); }
    (void)_t1548;
    if (_t1548) {
        Bool _t1523; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t1523 = *_hp; free(_hp); }
        (void)_t1523;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1523; return _r; }
    }
    ;
    Bool _t1549; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1549 = *_hp; free(_hp); }
    (void)_t1549;
    if (_t1549) {
        Bool _t1524; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t1524 = *_hp; free(_hp); }
        (void)_t1524;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1524; return _r; }
    }
    ;
    Bool _t1550; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1550 = *_hp; free(_hp); }
    (void)_t1550;
    if (_t1550) {
        Bool _t1525; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t1525 = *_hp; free(_hp); }
        (void)_t1525;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1525; return _r; }
    }
    ;
    Bool _t1551 = 0;
    (void)_t1551;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1551; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t1574; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1574 = *_hp; free(_hp); }
    (void)_t1574;
    if (_t1574) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t1575; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1575 = *_hp; free(_hp); }
    (void)_t1575;
    if (_t1575) {
        Str *_t1552 = ExprData_get_LiteralStr(self);
        (void)_t1552;
        ExprData *_t1553 = ExprData_LiteralStr(_t1552);
        (void)_t1553;
        Str_delete(_t1552, &(Bool){1});
        ;
        return _t1553;
    }
    ;
    Bool _t1576; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1576 = *_hp; free(_hp); }
    (void)_t1576;
    if (_t1576) {
        Str *_t1554 = ExprData_get_LiteralNum(self);
        (void)_t1554;
        ExprData *_t1555 = ExprData_LiteralNum(_t1554);
        (void)_t1555;
        Str_delete(_t1554, &(Bool){1});
        ;
        return _t1555;
    }
    ;
    Bool _t1577; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1577 = *_hp; free(_hp); }
    (void)_t1577;
    if (_t1577) {
        Str *_t1556 = ExprData_get_LiteralBool(self);
        (void)_t1556;
        ExprData *_t1557 = ExprData_LiteralBool(_t1556);
        (void)_t1557;
        Str_delete(_t1556, &(Bool){1});
        ;
        return _t1557;
    }
    ;
    Bool _t1578; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1578 = *_hp; free(_hp); }
    (void)_t1578;
    if (_t1578) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t1579; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1579 = *_hp; free(_hp); }
    (void)_t1579;
    if (_t1579) {
        Str *_t1558 = ExprData_get_Ident(self);
        (void)_t1558;
        ExprData *_t1559 = ExprData_Ident(_t1558);
        (void)_t1559;
        Str_delete(_t1558, &(Bool){1});
        ;
        return _t1559;
    }
    ;
    Bool _t1580; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1580 = *_hp; free(_hp); }
    (void)_t1580;
    if (_t1580) {
        Declaration *_t1560 = ExprData_get_Decl(self);
        (void)_t1560;
        ExprData *_t1561 = ExprData_Decl(_t1560);
        (void)_t1561;
        Declaration_delete(_t1560, &(Bool){1});
        ;
        return _t1561;
    }
    ;
    Bool _t1581; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1581 = *_hp; free(_hp); }
    (void)_t1581;
    if (_t1581) {
        Str *_t1562 = ExprData_get_Assign(self);
        (void)_t1562;
        ExprData *_t1563 = ExprData_Assign(_t1562);
        (void)_t1563;
        Str_delete(_t1562, &(Bool){1});
        ;
        return _t1563;
    }
    ;
    Bool _t1582; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1582 = *_hp; free(_hp); }
    (void)_t1582;
    if (_t1582) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t1583; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1583 = *_hp; free(_hp); }
    (void)_t1583;
    if (_t1583) {
        FunctionDef *_t1564 = ExprData_get_FuncDef(self);
        (void)_t1564;
        ExprData *_t1565 = ExprData_FuncDef(_t1564);
        (void)_t1565;
        FunctionDef_delete(_t1564, &(Bool){1});
        ;
        return _t1565;
    }
    ;
    Bool _t1584; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1584 = *_hp; free(_hp); }
    (void)_t1584;
    if (_t1584) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t1585; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1585 = *_hp; free(_hp); }
    (void)_t1585;
    if (_t1585) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t1586; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1586 = *_hp; free(_hp); }
    (void)_t1586;
    if (_t1586) {
        Str *_t1566 = ExprData_get_FieldAccess(self);
        (void)_t1566;
        ExprData *_t1567 = ExprData_FieldAccess(_t1566);
        (void)_t1567;
        Str_delete(_t1566, &(Bool){1});
        ;
        return _t1567;
    }
    ;
    Bool _t1587; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1587 = *_hp; free(_hp); }
    (void)_t1587;
    if (_t1587) {
        Str *_t1568 = ExprData_get_FieldAssign(self);
        (void)_t1568;
        ExprData *_t1569 = ExprData_FieldAssign(_t1568);
        (void)_t1569;
        Str_delete(_t1568, &(Bool){1});
        ;
        return _t1569;
    }
    ;
    Bool _t1588; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1588 = *_hp; free(_hp); }
    (void)_t1588;
    if (_t1588) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t1589; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1589 = *_hp; free(_hp); }
    (void)_t1589;
    if (_t1589) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t1590; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1590 = *_hp; free(_hp); }
    (void)_t1590;
    if (_t1590) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t1591; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1591 = *_hp; free(_hp); }
    (void)_t1591;
    if (_t1591) {
        Str *_t1570 = ExprData_get_ForIn(self);
        (void)_t1570;
        ExprData *_t1571 = ExprData_ForIn(_t1570);
        (void)_t1571;
        Str_delete(_t1570, &(Bool){1});
        ;
        return _t1571;
    }
    ;
    Bool _t1592; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1592 = *_hp; free(_hp); }
    (void)_t1592;
    if (_t1592) {
        Str *_t1572 = ExprData_get_NamedArg(self);
        (void)_t1572;
        ExprData *_t1573 = ExprData_NamedArg(_t1572);
        (void)_t1573;
        Str_delete(_t1572, &(Bool){1});
        ;
        return _t1573;
    }
    ;
    Bool _t1593; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1593 = *_hp; free(_hp); }
    (void)_t1593;
    if (_t1593) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t1594; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1594 = *_hp; free(_hp); }
    (void)_t1594;
    if (_t1594) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t1595; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1595 = *_hp; free(_hp); }
    (void)_t1595;
    if (_t1595) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t1596; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1596 = *_hp; free(_hp); }
    (void)_t1596;
    if (_t1596) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t1597; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1597 = *_hp; free(_hp); }
    (void)_t1597;
    if (_t1597) {
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
    Bool _t1733; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t1733 = *_hp; free(_hp); }
    (void)_t1733;
    if (_t1733) {
        Str *_t1598 = Str_lit("Body", 4ULL);
        (void)_t1598;
        ;
        return _t1598;
    }
    ;
    Bool _t1734; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t1734 = *_hp; free(_hp); }
    (void)_t1734;
    if (_t1734) {
        Str *_t1599 = Str_lit("Str", 3ULL);
        (void)_t1599;
        U64 _t1600; { U64 *_hp = (U64 *)Str_size(); _t1600 = *_hp; free(_hp); }
        (void)_t1600;
        U64 _t1601 = 3;
        (void)_t1601;
        Array *_va20 = Array_new(_t1599, &(U64){_t1600}, &(U64){_t1601});
        (void)_va20;
        Str_delete(_t1599, &(Bool){1});
        ;
        ;
        U64 _t1602 = 0;
        (void)_t1602;
        Str *_t1603 = Str_lit("LiteralStr(", 11ULL);
        (void)_t1603;
        Array_set(_va20, &(U64){_t1602}, _t1603);
        ;
        Str *_t1604 = ExprData_get_LiteralStr(self);
        (void)_t1604;
        U64 _t1605 = 1;
        (void)_t1605;
        Str *_t1606 = Str_to_str(_t1604);
        (void)_t1606;
        Str_delete(_t1604, &(Bool){1});
        Array_set(_va20, &(U64){_t1605}, _t1606);
        ;
        U64 _t1607 = 2;
        (void)_t1607;
        Str *_t1608 = Str_lit(")", 1ULL);
        (void)_t1608;
        Array_set(_va20, &(U64){_t1607}, _t1608);
        ;
        Str *_t1609 = format(_va20);
        (void)_t1609;
        ;
        return _t1609;
    }
    ;
    Bool _t1735; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t1735 = *_hp; free(_hp); }
    (void)_t1735;
    if (_t1735) {
        Str *_t1610 = Str_lit("Str", 3ULL);
        (void)_t1610;
        U64 _t1611; { U64 *_hp = (U64 *)Str_size(); _t1611 = *_hp; free(_hp); }
        (void)_t1611;
        U64 _t1612 = 3;
        (void)_t1612;
        Array *_va21 = Array_new(_t1610, &(U64){_t1611}, &(U64){_t1612});
        (void)_va21;
        Str_delete(_t1610, &(Bool){1});
        ;
        ;
        U64 _t1613 = 0;
        (void)_t1613;
        Str *_t1614 = Str_lit("LiteralNum(", 11ULL);
        (void)_t1614;
        Array_set(_va21, &(U64){_t1613}, _t1614);
        ;
        Str *_t1615 = ExprData_get_LiteralNum(self);
        (void)_t1615;
        U64 _t1616 = 1;
        (void)_t1616;
        Str *_t1617 = Str_to_str(_t1615);
        (void)_t1617;
        Str_delete(_t1615, &(Bool){1});
        Array_set(_va21, &(U64){_t1616}, _t1617);
        ;
        U64 _t1618 = 2;
        (void)_t1618;
        Str *_t1619 = Str_lit(")", 1ULL);
        (void)_t1619;
        Array_set(_va21, &(U64){_t1618}, _t1619);
        ;
        Str *_t1620 = format(_va21);
        (void)_t1620;
        ;
        return _t1620;
    }
    ;
    Bool _t1736; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t1736 = *_hp; free(_hp); }
    (void)_t1736;
    if (_t1736) {
        Str *_t1621 = Str_lit("Str", 3ULL);
        (void)_t1621;
        U64 _t1622; { U64 *_hp = (U64 *)Str_size(); _t1622 = *_hp; free(_hp); }
        (void)_t1622;
        U64 _t1623 = 3;
        (void)_t1623;
        Array *_va22 = Array_new(_t1621, &(U64){_t1622}, &(U64){_t1623});
        (void)_va22;
        Str_delete(_t1621, &(Bool){1});
        ;
        ;
        U64 _t1624 = 0;
        (void)_t1624;
        Str *_t1625 = Str_lit("LiteralBool(", 12ULL);
        (void)_t1625;
        Array_set(_va22, &(U64){_t1624}, _t1625);
        ;
        Str *_t1626 = ExprData_get_LiteralBool(self);
        (void)_t1626;
        U64 _t1627 = 1;
        (void)_t1627;
        Str *_t1628 = Str_to_str(_t1626);
        (void)_t1628;
        Str_delete(_t1626, &(Bool){1});
        Array_set(_va22, &(U64){_t1627}, _t1628);
        ;
        U64 _t1629 = 2;
        (void)_t1629;
        Str *_t1630 = Str_lit(")", 1ULL);
        (void)_t1630;
        Array_set(_va22, &(U64){_t1629}, _t1630);
        ;
        Str *_t1631 = format(_va22);
        (void)_t1631;
        ;
        return _t1631;
    }
    ;
    Bool _t1737; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t1737 = *_hp; free(_hp); }
    (void)_t1737;
    if (_t1737) {
        Str *_t1632 = Str_lit("LiteralNull", 11ULL);
        (void)_t1632;
        ;
        return _t1632;
    }
    ;
    Bool _t1738; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t1738 = *_hp; free(_hp); }
    (void)_t1738;
    if (_t1738) {
        Str *_t1633 = Str_lit("Str", 3ULL);
        (void)_t1633;
        U64 _t1634; { U64 *_hp = (U64 *)Str_size(); _t1634 = *_hp; free(_hp); }
        (void)_t1634;
        U64 _t1635 = 3;
        (void)_t1635;
        Array *_va23 = Array_new(_t1633, &(U64){_t1634}, &(U64){_t1635});
        (void)_va23;
        Str_delete(_t1633, &(Bool){1});
        ;
        ;
        U64 _t1636 = 0;
        (void)_t1636;
        Str *_t1637 = Str_lit("Ident(", 6ULL);
        (void)_t1637;
        Array_set(_va23, &(U64){_t1636}, _t1637);
        ;
        Str *_t1638 = ExprData_get_Ident(self);
        (void)_t1638;
        U64 _t1639 = 1;
        (void)_t1639;
        Str *_t1640 = Str_to_str(_t1638);
        (void)_t1640;
        Str_delete(_t1638, &(Bool){1});
        Array_set(_va23, &(U64){_t1639}, _t1640);
        ;
        U64 _t1641 = 2;
        (void)_t1641;
        Str *_t1642 = Str_lit(")", 1ULL);
        (void)_t1642;
        Array_set(_va23, &(U64){_t1641}, _t1642);
        ;
        Str *_t1643 = format(_va23);
        (void)_t1643;
        ;
        return _t1643;
    }
    ;
    Bool _t1739; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t1739 = *_hp; free(_hp); }
    (void)_t1739;
    if (_t1739) {
        Str *_t1644 = Str_lit("Str", 3ULL);
        (void)_t1644;
        U64 _t1645; { U64 *_hp = (U64 *)Str_size(); _t1645 = *_hp; free(_hp); }
        (void)_t1645;
        U64 _t1646 = 3;
        (void)_t1646;
        Array *_va24 = Array_new(_t1644, &(U64){_t1645}, &(U64){_t1646});
        (void)_va24;
        Str_delete(_t1644, &(Bool){1});
        ;
        ;
        U64 _t1647 = 0;
        (void)_t1647;
        Str *_t1648 = Str_lit("Decl(", 5ULL);
        (void)_t1648;
        Array_set(_va24, &(U64){_t1647}, _t1648);
        ;
        Declaration *_t1649 = ExprData_get_Decl(self);
        (void)_t1649;
        U64 _t1650 = 1;
        (void)_t1650;
        Str *_t1651 = Declaration_to_str(_t1649);
        (void)_t1651;
        Declaration_delete(_t1649, &(Bool){1});
        Array_set(_va24, &(U64){_t1650}, _t1651);
        ;
        U64 _t1652 = 2;
        (void)_t1652;
        Str *_t1653 = Str_lit(")", 1ULL);
        (void)_t1653;
        Array_set(_va24, &(U64){_t1652}, _t1653);
        ;
        Str *_t1654 = format(_va24);
        (void)_t1654;
        ;
        return _t1654;
    }
    ;
    Bool _t1740; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t1740 = *_hp; free(_hp); }
    (void)_t1740;
    if (_t1740) {
        Str *_t1655 = Str_lit("Str", 3ULL);
        (void)_t1655;
        U64 _t1656; { U64 *_hp = (U64 *)Str_size(); _t1656 = *_hp; free(_hp); }
        (void)_t1656;
        U64 _t1657 = 3;
        (void)_t1657;
        Array *_va25 = Array_new(_t1655, &(U64){_t1656}, &(U64){_t1657});
        (void)_va25;
        Str_delete(_t1655, &(Bool){1});
        ;
        ;
        U64 _t1658 = 0;
        (void)_t1658;
        Str *_t1659 = Str_lit("Assign(", 7ULL);
        (void)_t1659;
        Array_set(_va25, &(U64){_t1658}, _t1659);
        ;
        Str *_t1660 = ExprData_get_Assign(self);
        (void)_t1660;
        U64 _t1661 = 1;
        (void)_t1661;
        Str *_t1662 = Str_to_str(_t1660);
        (void)_t1662;
        Str_delete(_t1660, &(Bool){1});
        Array_set(_va25, &(U64){_t1661}, _t1662);
        ;
        U64 _t1663 = 2;
        (void)_t1663;
        Str *_t1664 = Str_lit(")", 1ULL);
        (void)_t1664;
        Array_set(_va25, &(U64){_t1663}, _t1664);
        ;
        Str *_t1665 = format(_va25);
        (void)_t1665;
        ;
        return _t1665;
    }
    ;
    Bool _t1741; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t1741 = *_hp; free(_hp); }
    (void)_t1741;
    if (_t1741) {
        Str *_t1666 = Str_lit("FCall", 5ULL);
        (void)_t1666;
        ;
        return _t1666;
    }
    ;
    Bool _t1742; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t1742 = *_hp; free(_hp); }
    (void)_t1742;
    if (_t1742) {
        Str *_t1667 = Str_lit("Str", 3ULL);
        (void)_t1667;
        U64 _t1668; { U64 *_hp = (U64 *)Str_size(); _t1668 = *_hp; free(_hp); }
        (void)_t1668;
        U64 _t1669 = 3;
        (void)_t1669;
        Array *_va26 = Array_new(_t1667, &(U64){_t1668}, &(U64){_t1669});
        (void)_va26;
        Str_delete(_t1667, &(Bool){1});
        ;
        ;
        U64 _t1670 = 0;
        (void)_t1670;
        Str *_t1671 = Str_lit("FuncDef(", 8ULL);
        (void)_t1671;
        Array_set(_va26, &(U64){_t1670}, _t1671);
        ;
        FunctionDef *_t1672 = ExprData_get_FuncDef(self);
        (void)_t1672;
        U64 _t1673 = 1;
        (void)_t1673;
        Str *_t1674 = FunctionDef_to_str(_t1672);
        (void)_t1674;
        FunctionDef_delete(_t1672, &(Bool){1});
        Array_set(_va26, &(U64){_t1673}, _t1674);
        ;
        U64 _t1675 = 2;
        (void)_t1675;
        Str *_t1676 = Str_lit(")", 1ULL);
        (void)_t1676;
        Array_set(_va26, &(U64){_t1675}, _t1676);
        ;
        Str *_t1677 = format(_va26);
        (void)_t1677;
        ;
        return _t1677;
    }
    ;
    Bool _t1743; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t1743 = *_hp; free(_hp); }
    (void)_t1743;
    if (_t1743) {
        Str *_t1678 = Str_lit("StructDef", 9ULL);
        (void)_t1678;
        ;
        return _t1678;
    }
    ;
    Bool _t1744; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t1744 = *_hp; free(_hp); }
    (void)_t1744;
    if (_t1744) {
        Str *_t1679 = Str_lit("EnumDef", 7ULL);
        (void)_t1679;
        ;
        return _t1679;
    }
    ;
    Bool _t1745; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t1745 = *_hp; free(_hp); }
    (void)_t1745;
    if (_t1745) {
        Str *_t1680 = Str_lit("Str", 3ULL);
        (void)_t1680;
        U64 _t1681; { U64 *_hp = (U64 *)Str_size(); _t1681 = *_hp; free(_hp); }
        (void)_t1681;
        U64 _t1682 = 3;
        (void)_t1682;
        Array *_va27 = Array_new(_t1680, &(U64){_t1681}, &(U64){_t1682});
        (void)_va27;
        Str_delete(_t1680, &(Bool){1});
        ;
        ;
        U64 _t1683 = 0;
        (void)_t1683;
        Str *_t1684 = Str_lit("FieldAccess(", 12ULL);
        (void)_t1684;
        Array_set(_va27, &(U64){_t1683}, _t1684);
        ;
        Str *_t1685 = ExprData_get_FieldAccess(self);
        (void)_t1685;
        U64 _t1686 = 1;
        (void)_t1686;
        Str *_t1687 = Str_to_str(_t1685);
        (void)_t1687;
        Str_delete(_t1685, &(Bool){1});
        Array_set(_va27, &(U64){_t1686}, _t1687);
        ;
        U64 _t1688 = 2;
        (void)_t1688;
        Str *_t1689 = Str_lit(")", 1ULL);
        (void)_t1689;
        Array_set(_va27, &(U64){_t1688}, _t1689);
        ;
        Str *_t1690 = format(_va27);
        (void)_t1690;
        ;
        return _t1690;
    }
    ;
    Bool _t1746; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t1746 = *_hp; free(_hp); }
    (void)_t1746;
    if (_t1746) {
        Str *_t1691 = Str_lit("Str", 3ULL);
        (void)_t1691;
        U64 _t1692; { U64 *_hp = (U64 *)Str_size(); _t1692 = *_hp; free(_hp); }
        (void)_t1692;
        U64 _t1693 = 3;
        (void)_t1693;
        Array *_va28 = Array_new(_t1691, &(U64){_t1692}, &(U64){_t1693});
        (void)_va28;
        Str_delete(_t1691, &(Bool){1});
        ;
        ;
        U64 _t1694 = 0;
        (void)_t1694;
        Str *_t1695 = Str_lit("FieldAssign(", 12ULL);
        (void)_t1695;
        Array_set(_va28, &(U64){_t1694}, _t1695);
        ;
        Str *_t1696 = ExprData_get_FieldAssign(self);
        (void)_t1696;
        U64 _t1697 = 1;
        (void)_t1697;
        Str *_t1698 = Str_to_str(_t1696);
        (void)_t1698;
        Str_delete(_t1696, &(Bool){1});
        Array_set(_va28, &(U64){_t1697}, _t1698);
        ;
        U64 _t1699 = 2;
        (void)_t1699;
        Str *_t1700 = Str_lit(")", 1ULL);
        (void)_t1700;
        Array_set(_va28, &(U64){_t1699}, _t1700);
        ;
        Str *_t1701 = format(_va28);
        (void)_t1701;
        ;
        return _t1701;
    }
    ;
    Bool _t1747; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t1747 = *_hp; free(_hp); }
    (void)_t1747;
    if (_t1747) {
        Str *_t1702 = Str_lit("Return", 6ULL);
        (void)_t1702;
        ;
        return _t1702;
    }
    ;
    Bool _t1748; { Bool *_hp = (Bool *)ExprData_is_If(self); _t1748 = *_hp; free(_hp); }
    (void)_t1748;
    if (_t1748) {
        Str *_t1703 = Str_lit("If", 2ULL);
        (void)_t1703;
        ;
        return _t1703;
    }
    ;
    Bool _t1749; { Bool *_hp = (Bool *)ExprData_is_While(self); _t1749 = *_hp; free(_hp); }
    (void)_t1749;
    if (_t1749) {
        Str *_t1704 = Str_lit("While", 5ULL);
        (void)_t1704;
        ;
        return _t1704;
    }
    ;
    Bool _t1750; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t1750 = *_hp; free(_hp); }
    (void)_t1750;
    if (_t1750) {
        Str *_t1705 = Str_lit("Str", 3ULL);
        (void)_t1705;
        U64 _t1706; { U64 *_hp = (U64 *)Str_size(); _t1706 = *_hp; free(_hp); }
        (void)_t1706;
        U64 _t1707 = 3;
        (void)_t1707;
        Array *_va29 = Array_new(_t1705, &(U64){_t1706}, &(U64){_t1707});
        (void)_va29;
        Str_delete(_t1705, &(Bool){1});
        ;
        ;
        U64 _t1708 = 0;
        (void)_t1708;
        Str *_t1709 = Str_lit("ForIn(", 6ULL);
        (void)_t1709;
        Array_set(_va29, &(U64){_t1708}, _t1709);
        ;
        Str *_t1710 = ExprData_get_ForIn(self);
        (void)_t1710;
        U64 _t1711 = 1;
        (void)_t1711;
        Str *_t1712 = Str_to_str(_t1710);
        (void)_t1712;
        Str_delete(_t1710, &(Bool){1});
        Array_set(_va29, &(U64){_t1711}, _t1712);
        ;
        U64 _t1713 = 2;
        (void)_t1713;
        Str *_t1714 = Str_lit(")", 1ULL);
        (void)_t1714;
        Array_set(_va29, &(U64){_t1713}, _t1714);
        ;
        Str *_t1715 = format(_va29);
        (void)_t1715;
        ;
        return _t1715;
    }
    ;
    Bool _t1751; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t1751 = *_hp; free(_hp); }
    (void)_t1751;
    if (_t1751) {
        Str *_t1716 = Str_lit("Str", 3ULL);
        (void)_t1716;
        U64 _t1717; { U64 *_hp = (U64 *)Str_size(); _t1717 = *_hp; free(_hp); }
        (void)_t1717;
        U64 _t1718 = 3;
        (void)_t1718;
        Array *_va30 = Array_new(_t1716, &(U64){_t1717}, &(U64){_t1718});
        (void)_va30;
        Str_delete(_t1716, &(Bool){1});
        ;
        ;
        U64 _t1719 = 0;
        (void)_t1719;
        Str *_t1720 = Str_lit("NamedArg(", 9ULL);
        (void)_t1720;
        Array_set(_va30, &(U64){_t1719}, _t1720);
        ;
        Str *_t1721 = ExprData_get_NamedArg(self);
        (void)_t1721;
        U64 _t1722 = 1;
        (void)_t1722;
        Str *_t1723 = Str_to_str(_t1721);
        (void)_t1723;
        Str_delete(_t1721, &(Bool){1});
        Array_set(_va30, &(U64){_t1722}, _t1723);
        ;
        U64 _t1724 = 2;
        (void)_t1724;
        Str *_t1725 = Str_lit(")", 1ULL);
        (void)_t1725;
        Array_set(_va30, &(U64){_t1724}, _t1725);
        ;
        Str *_t1726 = format(_va30);
        (void)_t1726;
        ;
        return _t1726;
    }
    ;
    Bool _t1752; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t1752 = *_hp; free(_hp); }
    (void)_t1752;
    if (_t1752) {
        Str *_t1727 = Str_lit("Break", 5ULL);
        (void)_t1727;
        ;
        return _t1727;
    }
    ;
    Bool _t1753; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t1753 = *_hp; free(_hp); }
    (void)_t1753;
    if (_t1753) {
        Str *_t1728 = Str_lit("Continue", 8ULL);
        (void)_t1728;
        ;
        return _t1728;
    }
    ;
    Bool _t1754; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t1754 = *_hp; free(_hp); }
    (void)_t1754;
    if (_t1754) {
        Str *_t1729 = Str_lit("MapLit", 6ULL);
        (void)_t1729;
        ;
        return _t1729;
    }
    ;
    Bool _t1755; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t1755 = *_hp; free(_hp); }
    (void)_t1755;
    if (_t1755) {
        Str *_t1730 = Str_lit("SetLit", 6ULL);
        (void)_t1730;
        ;
        return _t1730;
    }
    ;
    Bool _t1756; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t1756 = *_hp; free(_hp); }
    (void)_t1756;
    if (_t1756) {
        Str *_t1731 = Str_lit("Switch", 6ULL);
        (void)_t1731;
        ;
        return _t1731;
    }
    ;
    Bool _t1757; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t1757 = *_hp; free(_hp); }
    (void)_t1757;
    if (_t1757) {
        Str *_t1732 = Str_lit("Case", 4ULL);
        (void)_t1732;
        ;
        return _t1732;
    }
    ;
    Str *_t1758 = Str_lit("unknown", 7ULL);
    (void)_t1758;
    return _t1758;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t1760 = Str_lit("Str", 3ULL);
    (void)_t1760;
    U64 _t1761; { U64 *_hp = (U64 *)Str_size(); _t1761 = *_hp; free(_hp); }
    (void)_t1761;
    U64 _t1762 = 7;
    (void)_t1762;
    Array *_va31 = Array_new(_t1760, &(U64){_t1761}, &(U64){_t1762});
    (void)_va31;
    Str_delete(_t1760, &(Bool){1});
    ;
    ;
    U64 _t1763 = 0;
    (void)_t1763;
    Str *_t1764 = Str_clone(&self->path);
    (void)_t1764;
    Array_set(_va31, &(U64){_t1763}, _t1764);
    ;
    U64 _t1765 = 1;
    (void)_t1765;
    Str *_t1766 = Str_lit(":", 1ULL);
    (void)_t1766;
    Array_set(_va31, &(U64){_t1765}, _t1766);
    ;
    U64 _t1767 = 2;
    (void)_t1767;
    Str *_t1768 = U32_to_str(&self->line);
    (void)_t1768;
    Array_set(_va31, &(U64){_t1767}, _t1768);
    ;
    U64 _t1769 = 3;
    (void)_t1769;
    Str *_t1770 = Str_lit(":", 1ULL);
    (void)_t1770;
    Array_set(_va31, &(U64){_t1769}, _t1770);
    ;
    U64 _t1771 = 4;
    (void)_t1771;
    Str *_t1772 = U32_to_str(&self->col);
    (void)_t1772;
    Array_set(_va31, &(U64){_t1771}, _t1772);
    ;
    U64 _t1773 = 5;
    (void)_t1773;
    Str *_t1774 = Str_lit(": error: ", 9ULL);
    (void)_t1774;
    Array_set(_va31, &(U64){_t1773}, _t1774);
    ;
    U64 _t1775 = 6;
    (void)_t1775;
    Str *_t1776 = Str_clone(msg);
    (void)_t1776;
    Array_set(_va31, &(U64){_t1775}, _t1776);
    ;
    println(_va31);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1777 = Str_lit("Str", 3ULL);
    (void)_t1777;
    U64 _t1778; { U64 *_hp = (U64 *)Str_size(); _t1778 = *_hp; free(_hp); }
    (void)_t1778;
    U64 _t1779 = 1;
    (void)_t1779;
    Array *_va32 = Array_new(_t1777, &(U64){_t1778}, &(U64){_t1779});
    (void)_va32;
    Str_delete(_t1777, &(Bool){1});
    ;
    ;
    U64 _t1780 = 0;
    (void)_t1780;
    Str *_t1781 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t1781;
    Array_set(_va32, &(U64){_t1780}, _t1781);
    ;
    println(_va32);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t1782 = Str_lit("Str", 3ULL);
    (void)_t1782;
    U64 _t1783; { U64 *_hp = (U64 *)Str_size(); _t1783 = *_hp; free(_hp); }
    (void)_t1783;
    U64 _t1784 = 1;
    (void)_t1784;
    Array *_va33 = Array_new(_t1782, &(U64){_t1783}, &(U64){_t1784});
    (void)_va33;
    Str_delete(_t1782, &(Bool){1});
    ;
    ;
    U64 _t1785 = 0;
    (void)_t1785;
    Str *_t1786 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t1786;
    Array_set(_va33, &(U64){_t1785}, _t1786);
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
    U64 *_t1787 = malloc(sizeof(U64)); *_t1787 = I64_to_u64(DEREF(i));
    (void)_t1787;
    Expr *c = Vec_get(&parent->children, _t1787);
    (void)c;
    U64_delete(_t1787, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t1788; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t1788 = *_hp; free(_hp); }
    (void)_t1788;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t1788; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t1789 = 0;
    (void)_t1789;
    I64 _t1790 = 1;
    (void)_t1790;
    I64 _t1791 = I64_sub(_t1789, _t1790);
    (void)_t1791;
    ;
    ;
    I64 _t1792 = 0;
    (void)_t1792;
    I64 _t1793 = 1;
    (void)_t1793;
    I64 _t1794 = I64_sub(_t1792, _t1793);
    (void)_t1794;
    ;
    ;
    Str *_t1795 = Str_lit("", 0ULL);
    (void)_t1795;
    U64 _t1796; { U64 *_hp = (U64 *)Expr_size(); _t1796 = *_hp; free(_hp); }
    (void)_t1796;
    Bool _t1797 = 0;
    (void)_t1797;
    Bool _t1798 = 0;
    (void)_t1798;
    Bool _t1799 = 0;
    (void)_t1799;
    Bool _t1800 = 0;
    (void)_t1800;
    Bool _t1801 = 0;
    (void)_t1801;
    Bool _t1802 = 0;
    (void)_t1802;
    Bool _t1803 = 0;
    (void)_t1803;
    Bool _t1804 = 0;
    (void)_t1804;
    I32 _t1805 = 0;
    (void)_t1805;
    I32 _t1806 = I64_to_i32(_t1791);
    (void)_t1806;
    ;
    U32 _t1807 = 0;
    (void)_t1807;
    I32 _t1808 = I64_to_i32(_t1794);
    (void)_t1808;
    ;
    U32 _t1809 = 0;
    (void)_t1809;
    U32 _t1810 = U32_clone(&(U32){col});
    (void)_t1810;
    Str *_t1811 = Str_clone(path);
    (void)_t1811;
    Expr *_t1812 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t1812->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t1812->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1812->struct_name = *_ca; free(_ca); }
    _t1812->is_own_arg = _t1797;
    _t1812->is_splat = _t1798;
    _t1812->is_own_field = _t1799;
    _t1812->is_ref_field = _t1800;
    _t1812->is_ns_field = _t1801;
    _t1812->is_ext = _t1802;
    _t1812->is_core = _t1803;
    _t1812->save_old_delete = _t1804;
    _t1812->total_struct_size = _t1805;
    _t1812->variadic_index = _t1806;
    _t1812->variadic_count = _t1807;
    _t1812->kwargs_index = _t1808;
    _t1812->kwargs_count = _t1809;
    _t1812->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t1795, &(U64){_t1796}); _t1812->children = *_ca; free(_ca); }
    _t1812->line = U32_clone(&(U32){line});
    _t1812->col = _t1810;
    { Str *_ca = Str_clone(_t1811); _t1812->path = *_ca; free(_ca); }
    (void)_t1812;
    Str_delete(_t1795, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t1811, &(Bool){1});
    return _t1812;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Str *_t1824 = Str_lit("", 0ULL);
    (void)_t1824;
    U64 _t1825; { U64 *_hp = (U64 *)Expr_size(); _t1825 = *_hp; free(_hp); }
    (void)_t1825;
    Vec *new_children = Vec_new(_t1824, &(U64){_t1825});
    (void)new_children;
    Str_delete(_t1824, &(Bool){1});
    ;
    {
        U64 _fi1813 = 0;
        (void)_fi1813;
        while (1) {
            U64 _t1815 = 0;
            (void)_t1815;
            U64 _t1816; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1816 = *_hp; free(_hp); }
            (void)_t1816;
            Range *_t1817 = Range_new(_t1815, _t1816);
            (void)_t1817;
            ;
            ;
            U64 _t1818; { U64 *_hp = (U64 *)Range_len(_t1817); _t1818 = *_hp; free(_hp); }
            (void)_t1818;
            Range_delete(_t1817, &(Bool){1});
            Bool _wcond1814; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1813}, &(U64){_t1818}); _wcond1814 = *_hp; free(_hp); }
            (void)_wcond1814;
            ;
            if (_wcond1814) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1819 = 0;
            (void)_t1819;
            U64 _t1820; { U64 *_hp = (U64 *)Vec_len(&self->children); _t1820 = *_hp; free(_hp); }
            (void)_t1820;
            Range *_t1821 = Range_new(_t1819, _t1820);
            (void)_t1821;
            ;
            ;
            U64 *i = Range_get(_t1821, _fi1813);
            (void)i;
            Range_delete(_t1821, &(Bool){1});
            U64 _t1822 = 1;
            (void)_t1822;
            U64 _t1823 = U64_add(_fi1813, _t1822);
            (void)_t1823;
            ;
            _fi1813 = _t1823;
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
    Expr *_t1826 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t1826->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t1826->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t1826->struct_name = *_ca; free(_ca); }
    _t1826->is_own_arg = self->is_own_arg;
    _t1826->is_splat = self->is_splat;
    _t1826->is_own_field = self->is_own_field;
    _t1826->is_ref_field = self->is_ref_field;
    _t1826->is_ns_field = self->is_ns_field;
    _t1826->is_ext = self->is_ext;
    _t1826->is_core = self->is_core;
    _t1826->save_old_delete = self->save_old_delete;
    _t1826->total_struct_size = self->total_struct_size;
    _t1826->variadic_index = self->variadic_index;
    _t1826->variadic_count = self->variadic_count;
    _t1826->kwargs_index = self->kwargs_index;
    _t1826->kwargs_count = self->kwargs_count;
    _t1826->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(new_children); _t1826->children = *_ca; free(_ca); }
    _t1826->line = self->line;
    _t1826->col = self->col;
    { Str *_ca = Str_clone(&self->path); _t1826->path = *_ca; free(_ca); }
    (void)_t1826;
    Vec_delete(new_children, &(Bool){1});
    return _t1826;
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
    Bool _t2216; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        Bool _t2150; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t2150 = *_hp; free(_hp); }
        (void)_t2150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2150; return _r; }
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        Bool _t2151; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t2151 = *_hp; free(_hp); }
        (void)_t2151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2151; return _r; }
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        Bool _t2152; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t2152 = *_hp; free(_hp); }
        (void)_t2152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2152; return _r; }
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        Bool _t2153; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t2153 = *_hp; free(_hp); }
        (void)_t2153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2153; return _r; }
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        Bool _t2154; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t2154 = *_hp; free(_hp); }
        (void)_t2154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2154; return _r; }
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        Bool _t2155; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t2155 = *_hp; free(_hp); }
        (void)_t2155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2155; return _r; }
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        Bool _t2156; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t2156 = *_hp; free(_hp); }
        (void)_t2156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2156; return _r; }
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        Bool _t2157; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t2157 = *_hp; free(_hp); }
        (void)_t2157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2157; return _r; }
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        Bool _t2158; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t2158 = *_hp; free(_hp); }
        (void)_t2158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2158; return _r; }
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        Bool _t2159; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t2159 = *_hp; free(_hp); }
        (void)_t2159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2159; return _r; }
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        Bool _t2160; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t2160 = *_hp; free(_hp); }
        (void)_t2160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2160; return _r; }
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        Bool _t2161; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t2161 = *_hp; free(_hp); }
        (void)_t2161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2161; return _r; }
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        Bool _t2162; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t2162 = *_hp; free(_hp); }
        (void)_t2162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2162; return _r; }
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        Bool _t2163; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t2163 = *_hp; free(_hp); }
        (void)_t2163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2163; return _r; }
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        Bool _t2164; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t2164 = *_hp; free(_hp); }
        (void)_t2164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2164; return _r; }
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        Bool _t2165; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t2165 = *_hp; free(_hp); }
        (void)_t2165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2165; return _r; }
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        Bool _t2166; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t2166 = *_hp; free(_hp); }
        (void)_t2166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2166; return _r; }
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        Bool _t2167; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t2167 = *_hp; free(_hp); }
        (void)_t2167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2167; return _r; }
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        Bool _t2168; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t2168 = *_hp; free(_hp); }
        (void)_t2168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2168; return _r; }
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        Bool _t2169; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t2169 = *_hp; free(_hp); }
        (void)_t2169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2169; return _r; }
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        Bool _t2170; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t2170 = *_hp; free(_hp); }
        (void)_t2170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2170; return _r; }
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        Bool _t2171; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t2171 = *_hp; free(_hp); }
        (void)_t2171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2171; return _r; }
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        Bool _t2172; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t2172 = *_hp; free(_hp); }
        (void)_t2172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2172; return _r; }
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
        Bool _t2173; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t2173 = *_hp; free(_hp); }
        (void)_t2173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2173; return _r; }
    }
    ;
    Bool _t2240; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t2240 = *_hp; free(_hp); }
    (void)_t2240;
    if (_t2240) {
        Bool _t2174; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t2174 = *_hp; free(_hp); }
        (void)_t2174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2174; return _r; }
    }
    ;
    Bool _t2241; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    if (_t2241) {
        Bool _t2175; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t2175 = *_hp; free(_hp); }
        (void)_t2175;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2175; return _r; }
    }
    ;
    Bool _t2242; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    if (_t2242) {
        Bool _t2176; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t2176 = *_hp; free(_hp); }
        (void)_t2176;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2176; return _r; }
    }
    ;
    Bool _t2243; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t2243 = *_hp; free(_hp); }
    (void)_t2243;
    if (_t2243) {
        Bool _t2177; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t2177 = *_hp; free(_hp); }
        (void)_t2177;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2177; return _r; }
    }
    ;
    Bool _t2244; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t2244 = *_hp; free(_hp); }
    (void)_t2244;
    if (_t2244) {
        Bool _t2178; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t2178 = *_hp; free(_hp); }
        (void)_t2178;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2178; return _r; }
    }
    ;
    Bool _t2245; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t2245 = *_hp; free(_hp); }
    (void)_t2245;
    if (_t2245) {
        Bool _t2179; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t2179 = *_hp; free(_hp); }
        (void)_t2179;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2179; return _r; }
    }
    ;
    Bool _t2246; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    if (_t2246) {
        Bool _t2180; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t2180 = *_hp; free(_hp); }
        (void)_t2180;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2180; return _r; }
    }
    ;
    Bool _t2247; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    if (_t2247) {
        Bool _t2181; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t2181 = *_hp; free(_hp); }
        (void)_t2181;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2181; return _r; }
    }
    ;
    Bool _t2248; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t2248 = *_hp; free(_hp); }
    (void)_t2248;
    if (_t2248) {
        Bool _t2182; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t2182 = *_hp; free(_hp); }
        (void)_t2182;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2182; return _r; }
    }
    ;
    Bool _t2249; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t2249 = *_hp; free(_hp); }
    (void)_t2249;
    if (_t2249) {
        Bool _t2183; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t2183 = *_hp; free(_hp); }
        (void)_t2183;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2183; return _r; }
    }
    ;
    Bool _t2250; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t2250 = *_hp; free(_hp); }
    (void)_t2250;
    if (_t2250) {
        Bool _t2184; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t2184 = *_hp; free(_hp); }
        (void)_t2184;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2184; return _r; }
    }
    ;
    Bool _t2251; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t2251 = *_hp; free(_hp); }
    (void)_t2251;
    if (_t2251) {
        Bool _t2185; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t2185 = *_hp; free(_hp); }
        (void)_t2185;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2185; return _r; }
    }
    ;
    Bool _t2252; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t2252 = *_hp; free(_hp); }
    (void)_t2252;
    if (_t2252) {
        Bool _t2186; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t2186 = *_hp; free(_hp); }
        (void)_t2186;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2186; return _r; }
    }
    ;
    Bool _t2253; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t2253 = *_hp; free(_hp); }
    (void)_t2253;
    if (_t2253) {
        Bool _t2187; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t2187 = *_hp; free(_hp); }
        (void)_t2187;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2187; return _r; }
    }
    ;
    Bool _t2254; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t2254 = *_hp; free(_hp); }
    (void)_t2254;
    if (_t2254) {
        Bool _t2188; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t2188 = *_hp; free(_hp); }
        (void)_t2188;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2188; return _r; }
    }
    ;
    Bool _t2255; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t2255 = *_hp; free(_hp); }
    (void)_t2255;
    if (_t2255) {
        Bool _t2189; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t2189 = *_hp; free(_hp); }
        (void)_t2189;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2189; return _r; }
    }
    ;
    Bool _t2256; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t2256 = *_hp; free(_hp); }
    (void)_t2256;
    if (_t2256) {
        Bool _t2190; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t2190 = *_hp; free(_hp); }
        (void)_t2190;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2190; return _r; }
    }
    ;
    Bool _t2257; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t2257 = *_hp; free(_hp); }
    (void)_t2257;
    if (_t2257) {
        Bool _t2191; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t2191 = *_hp; free(_hp); }
        (void)_t2191;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2191; return _r; }
    }
    ;
    Bool _t2258; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t2258 = *_hp; free(_hp); }
    (void)_t2258;
    if (_t2258) {
        Bool _t2192; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t2192 = *_hp; free(_hp); }
        (void)_t2192;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2192; return _r; }
    }
    ;
    Bool _t2259; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t2259 = *_hp; free(_hp); }
    (void)_t2259;
    if (_t2259) {
        Bool _t2193; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t2193 = *_hp; free(_hp); }
        (void)_t2193;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2193; return _r; }
    }
    ;
    Bool _t2260; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t2260 = *_hp; free(_hp); }
    (void)_t2260;
    if (_t2260) {
        Bool _t2194; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t2194 = *_hp; free(_hp); }
        (void)_t2194;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2194; return _r; }
    }
    ;
    Bool _t2261; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t2261 = *_hp; free(_hp); }
    (void)_t2261;
    if (_t2261) {
        Bool _t2195; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t2195 = *_hp; free(_hp); }
        (void)_t2195;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2195; return _r; }
    }
    ;
    Bool _t2262; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t2262 = *_hp; free(_hp); }
    (void)_t2262;
    if (_t2262) {
        Bool _t2196; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t2196 = *_hp; free(_hp); }
        (void)_t2196;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2196; return _r; }
    }
    ;
    Bool _t2263; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t2263 = *_hp; free(_hp); }
    (void)_t2263;
    if (_t2263) {
        Bool _t2197; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t2197 = *_hp; free(_hp); }
        (void)_t2197;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2197; return _r; }
    }
    ;
    Bool _t2264; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t2264 = *_hp; free(_hp); }
    (void)_t2264;
    if (_t2264) {
        Bool _t2198; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t2198 = *_hp; free(_hp); }
        (void)_t2198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2198; return _r; }
    }
    ;
    Bool _t2265; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t2265 = *_hp; free(_hp); }
    (void)_t2265;
    if (_t2265) {
        Bool _t2199; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t2199 = *_hp; free(_hp); }
        (void)_t2199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2199; return _r; }
    }
    ;
    Bool _t2266; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t2266 = *_hp; free(_hp); }
    (void)_t2266;
    if (_t2266) {
        Bool _t2200; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t2200 = *_hp; free(_hp); }
        (void)_t2200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2200; return _r; }
    }
    ;
    Bool _t2267; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t2267 = *_hp; free(_hp); }
    (void)_t2267;
    if (_t2267) {
        Bool _t2201; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t2201 = *_hp; free(_hp); }
        (void)_t2201;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2201; return _r; }
    }
    ;
    Bool _t2268; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t2268 = *_hp; free(_hp); }
    (void)_t2268;
    if (_t2268) {
        Bool _t2202; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t2202 = *_hp; free(_hp); }
        (void)_t2202;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2202; return _r; }
    }
    ;
    Bool _t2269; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t2269 = *_hp; free(_hp); }
    (void)_t2269;
    if (_t2269) {
        Bool _t2203; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t2203 = *_hp; free(_hp); }
        (void)_t2203;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2203; return _r; }
    }
    ;
    Bool _t2270; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t2270 = *_hp; free(_hp); }
    (void)_t2270;
    if (_t2270) {
        Bool _t2204; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t2204 = *_hp; free(_hp); }
        (void)_t2204;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2204; return _r; }
    }
    ;
    Bool _t2271; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t2271 = *_hp; free(_hp); }
    (void)_t2271;
    if (_t2271) {
        Bool _t2205; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t2205 = *_hp; free(_hp); }
        (void)_t2205;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2205; return _r; }
    }
    ;
    Bool _t2272; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t2272 = *_hp; free(_hp); }
    (void)_t2272;
    if (_t2272) {
        Bool _t2206; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t2206 = *_hp; free(_hp); }
        (void)_t2206;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2206; return _r; }
    }
    ;
    Bool _t2273; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t2273 = *_hp; free(_hp); }
    (void)_t2273;
    if (_t2273) {
        Bool _t2207; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t2207 = *_hp; free(_hp); }
        (void)_t2207;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2207; return _r; }
    }
    ;
    Bool _t2274; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t2274 = *_hp; free(_hp); }
    (void)_t2274;
    if (_t2274) {
        Bool _t2208; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t2208 = *_hp; free(_hp); }
        (void)_t2208;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2208; return _r; }
    }
    ;
    Bool _t2275; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t2275 = *_hp; free(_hp); }
    (void)_t2275;
    if (_t2275) {
        Bool _t2209; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t2209 = *_hp; free(_hp); }
        (void)_t2209;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2209; return _r; }
    }
    ;
    Bool _t2276; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t2276 = *_hp; free(_hp); }
    (void)_t2276;
    if (_t2276) {
        Bool _t2210; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t2210 = *_hp; free(_hp); }
        (void)_t2210;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2210; return _r; }
    }
    ;
    Bool _t2277; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t2277 = *_hp; free(_hp); }
    (void)_t2277;
    if (_t2277) {
        Bool _t2211; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t2211 = *_hp; free(_hp); }
        (void)_t2211;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2211; return _r; }
    }
    ;
    Bool _t2278; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t2278 = *_hp; free(_hp); }
    (void)_t2278;
    if (_t2278) {
        Bool _t2212; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t2212 = *_hp; free(_hp); }
        (void)_t2212;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2212; return _r; }
    }
    ;
    Bool _t2279; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t2279 = *_hp; free(_hp); }
    (void)_t2279;
    if (_t2279) {
        Bool _t2213; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t2213 = *_hp; free(_hp); }
        (void)_t2213;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2213; return _r; }
    }
    ;
    Bool _t2280; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t2280 = *_hp; free(_hp); }
    (void)_t2280;
    if (_t2280) {
        Bool _t2214; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t2214 = *_hp; free(_hp); }
        (void)_t2214;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2214; return _r; }
    }
    ;
    Bool _t2281; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t2281 = *_hp; free(_hp); }
    (void)_t2281;
    if (_t2281) {
        Bool _t2215; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t2215 = *_hp; free(_hp); }
        (void)_t2215;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2215; return _r; }
    }
    ;
    Bool _t2282 = 0;
    (void)_t2282;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2282; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t2283; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2283 = *_hp; free(_hp); }
    (void)_t2283;
    if (_t2283) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t2284; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2284 = *_hp; free(_hp); }
    (void)_t2284;
    if (_t2284) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t2285; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2285 = *_hp; free(_hp); }
    (void)_t2285;
    if (_t2285) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t2286; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2286 = *_hp; free(_hp); }
    (void)_t2286;
    if (_t2286) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t2287; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2287 = *_hp; free(_hp); }
    (void)_t2287;
    if (_t2287) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t2288; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2288 = *_hp; free(_hp); }
    (void)_t2288;
    if (_t2288) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t2289; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2289 = *_hp; free(_hp); }
    (void)_t2289;
    if (_t2289) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t2290; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2290 = *_hp; free(_hp); }
    (void)_t2290;
    if (_t2290) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t2291; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2291 = *_hp; free(_hp); }
    (void)_t2291;
    if (_t2291) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t2292; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2292 = *_hp; free(_hp); }
    (void)_t2292;
    if (_t2292) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t2293; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2293 = *_hp; free(_hp); }
    (void)_t2293;
    if (_t2293) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t2294; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2294 = *_hp; free(_hp); }
    (void)_t2294;
    if (_t2294) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t2295; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2295 = *_hp; free(_hp); }
    (void)_t2295;
    if (_t2295) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t2296; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2296 = *_hp; free(_hp); }
    (void)_t2296;
    if (_t2296) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t2297; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2297 = *_hp; free(_hp); }
    (void)_t2297;
    if (_t2297) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t2298; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2298 = *_hp; free(_hp); }
    (void)_t2298;
    if (_t2298) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t2299; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2299 = *_hp; free(_hp); }
    (void)_t2299;
    if (_t2299) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t2300; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2300 = *_hp; free(_hp); }
    (void)_t2300;
    if (_t2300) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t2301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2301 = *_hp; free(_hp); }
    (void)_t2301;
    if (_t2301) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t2302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2302 = *_hp; free(_hp); }
    (void)_t2302;
    if (_t2302) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t2303; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2303 = *_hp; free(_hp); }
    (void)_t2303;
    if (_t2303) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t2304; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2304 = *_hp; free(_hp); }
    (void)_t2304;
    if (_t2304) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t2305; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2305 = *_hp; free(_hp); }
    (void)_t2305;
    if (_t2305) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t2306; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2306 = *_hp; free(_hp); }
    (void)_t2306;
    if (_t2306) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t2307; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2307 = *_hp; free(_hp); }
    (void)_t2307;
    if (_t2307) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t2308; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2308 = *_hp; free(_hp); }
    (void)_t2308;
    if (_t2308) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t2309; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2309 = *_hp; free(_hp); }
    (void)_t2309;
    if (_t2309) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t2310; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2310 = *_hp; free(_hp); }
    (void)_t2310;
    if (_t2310) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t2311; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2311 = *_hp; free(_hp); }
    (void)_t2311;
    if (_t2311) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t2312; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2312 = *_hp; free(_hp); }
    (void)_t2312;
    if (_t2312) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t2313; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2313 = *_hp; free(_hp); }
    (void)_t2313;
    if (_t2313) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t2314; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2314 = *_hp; free(_hp); }
    (void)_t2314;
    if (_t2314) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t2315; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2315 = *_hp; free(_hp); }
    (void)_t2315;
    if (_t2315) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t2316; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2316 = *_hp; free(_hp); }
    (void)_t2316;
    if (_t2316) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t2317; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2317 = *_hp; free(_hp); }
    (void)_t2317;
    if (_t2317) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t2318; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2318 = *_hp; free(_hp); }
    (void)_t2318;
    if (_t2318) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t2319; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2319 = *_hp; free(_hp); }
    (void)_t2319;
    if (_t2319) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t2320; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2320 = *_hp; free(_hp); }
    (void)_t2320;
    if (_t2320) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t2321; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2321 = *_hp; free(_hp); }
    (void)_t2321;
    if (_t2321) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t2322; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2322 = *_hp; free(_hp); }
    (void)_t2322;
    if (_t2322) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t2323; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2323 = *_hp; free(_hp); }
    (void)_t2323;
    if (_t2323) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t2324; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2324 = *_hp; free(_hp); }
    (void)_t2324;
    if (_t2324) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t2325; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2325 = *_hp; free(_hp); }
    (void)_t2325;
    if (_t2325) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t2326; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2326 = *_hp; free(_hp); }
    (void)_t2326;
    if (_t2326) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t2327; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2327 = *_hp; free(_hp); }
    (void)_t2327;
    if (_t2327) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t2328; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2328 = *_hp; free(_hp); }
    (void)_t2328;
    if (_t2328) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t2329; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2329 = *_hp; free(_hp); }
    (void)_t2329;
    if (_t2329) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t2330; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2330 = *_hp; free(_hp); }
    (void)_t2330;
    if (_t2330) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t2331; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2331 = *_hp; free(_hp); }
    (void)_t2331;
    if (_t2331) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t2332; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2332 = *_hp; free(_hp); }
    (void)_t2332;
    if (_t2332) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t2333; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2333 = *_hp; free(_hp); }
    (void)_t2333;
    if (_t2333) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t2334; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2334 = *_hp; free(_hp); }
    (void)_t2334;
    if (_t2334) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t2335; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2335 = *_hp; free(_hp); }
    (void)_t2335;
    if (_t2335) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t2336; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2336 = *_hp; free(_hp); }
    (void)_t2336;
    if (_t2336) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t2337; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2337 = *_hp; free(_hp); }
    (void)_t2337;
    if (_t2337) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t2338; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2338 = *_hp; free(_hp); }
    (void)_t2338;
    if (_t2338) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t2339; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2339 = *_hp; free(_hp); }
    (void)_t2339;
    if (_t2339) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t2340; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2340 = *_hp; free(_hp); }
    (void)_t2340;
    if (_t2340) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t2341; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2341 = *_hp; free(_hp); }
    (void)_t2341;
    if (_t2341) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t2342; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2342 = *_hp; free(_hp); }
    (void)_t2342;
    if (_t2342) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t2343; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2343 = *_hp; free(_hp); }
    (void)_t2343;
    if (_t2343) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t2344; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2344 = *_hp; free(_hp); }
    (void)_t2344;
    if (_t2344) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t2345; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2345 = *_hp; free(_hp); }
    (void)_t2345;
    if (_t2345) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t2346; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2346 = *_hp; free(_hp); }
    (void)_t2346;
    if (_t2346) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t2347; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2347 = *_hp; free(_hp); }
    (void)_t2347;
    if (_t2347) {
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
    Bool _t2414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t2414 = *_hp; free(_hp); }
    (void)_t2414;
    if (_t2414) {
        Str *_t2348 = Str_lit("Eof", 3ULL);
        (void)_t2348;
        ;
        return _t2348;
    }
    ;
    Bool _t2415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t2415 = *_hp; free(_hp); }
    (void)_t2415;
    if (_t2415) {
        Str *_t2349 = Str_lit("LParen", 6ULL);
        (void)_t2349;
        ;
        return _t2349;
    }
    ;
    Bool _t2416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t2416 = *_hp; free(_hp); }
    (void)_t2416;
    if (_t2416) {
        Str *_t2350 = Str_lit("RParen", 6ULL);
        (void)_t2350;
        ;
        return _t2350;
    }
    ;
    Bool _t2417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t2417 = *_hp; free(_hp); }
    (void)_t2417;
    if (_t2417) {
        Str *_t2351 = Str_lit("LBrace", 6ULL);
        (void)_t2351;
        ;
        return _t2351;
    }
    ;
    Bool _t2418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t2418 = *_hp; free(_hp); }
    (void)_t2418;
    if (_t2418) {
        Str *_t2352 = Str_lit("RBrace", 6ULL);
        (void)_t2352;
        ;
        return _t2352;
    }
    ;
    Bool _t2419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t2419 = *_hp; free(_hp); }
    (void)_t2419;
    if (_t2419) {
        Str *_t2353 = Str_lit("LBracket", 8ULL);
        (void)_t2353;
        ;
        return _t2353;
    }
    ;
    Bool _t2420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t2420 = *_hp; free(_hp); }
    (void)_t2420;
    if (_t2420) {
        Str *_t2354 = Str_lit("RBracket", 8ULL);
        (void)_t2354;
        ;
        return _t2354;
    }
    ;
    Bool _t2421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t2421 = *_hp; free(_hp); }
    (void)_t2421;
    if (_t2421) {
        Str *_t2355 = Str_lit("Comma", 5ULL);
        (void)_t2355;
        ;
        return _t2355;
    }
    ;
    Bool _t2422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t2422 = *_hp; free(_hp); }
    (void)_t2422;
    if (_t2422) {
        Str *_t2356 = Str_lit("Colon", 5ULL);
        (void)_t2356;
        ;
        return _t2356;
    }
    ;
    Bool _t2423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t2423 = *_hp; free(_hp); }
    (void)_t2423;
    if (_t2423) {
        Str *_t2357 = Str_lit("Question", 8ULL);
        (void)_t2357;
        ;
        return _t2357;
    }
    ;
    Bool _t2424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t2424 = *_hp; free(_hp); }
    (void)_t2424;
    if (_t2424) {
        Str *_t2358 = Str_lit("Bang", 4ULL);
        (void)_t2358;
        ;
        return _t2358;
    }
    ;
    Bool _t2425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t2425 = *_hp; free(_hp); }
    (void)_t2425;
    if (_t2425) {
        Str *_t2359 = Str_lit("Minus", 5ULL);
        (void)_t2359;
        ;
        return _t2359;
    }
    ;
    Bool _t2426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t2426 = *_hp; free(_hp); }
    (void)_t2426;
    if (_t2426) {
        Str *_t2360 = Str_lit("Plus", 4ULL);
        (void)_t2360;
        ;
        return _t2360;
    }
    ;
    Bool _t2427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t2427 = *_hp; free(_hp); }
    (void)_t2427;
    if (_t2427) {
        Str *_t2361 = Str_lit("Star", 4ULL);
        (void)_t2361;
        ;
        return _t2361;
    }
    ;
    Bool _t2428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t2428 = *_hp; free(_hp); }
    (void)_t2428;
    if (_t2428) {
        Str *_t2362 = Str_lit("Slash", 5ULL);
        (void)_t2362;
        ;
        return _t2362;
    }
    ;
    Bool _t2429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t2429 = *_hp; free(_hp); }
    (void)_t2429;
    if (_t2429) {
        Str *_t2363 = Str_lit("Dot", 3ULL);
        (void)_t2363;
        ;
        return _t2363;
    }
    ;
    Bool _t2430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t2430 = *_hp; free(_hp); }
    (void)_t2430;
    if (_t2430) {
        Str *_t2364 = Str_lit("DotDot", 6ULL);
        (void)_t2364;
        ;
        return _t2364;
    }
    ;
    Bool _t2431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t2431 = *_hp; free(_hp); }
    (void)_t2431;
    if (_t2431) {
        Str *_t2365 = Str_lit("DotDotDot", 9ULL);
        (void)_t2365;
        ;
        return _t2365;
    }
    ;
    Bool _t2432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t2432 = *_hp; free(_hp); }
    (void)_t2432;
    if (_t2432) {
        Str *_t2366 = Str_lit("Eq", 2ULL);
        (void)_t2366;
        ;
        return _t2366;
    }
    ;
    Bool _t2433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t2433 = *_hp; free(_hp); }
    (void)_t2433;
    if (_t2433) {
        Str *_t2367 = Str_lit("EqEq", 4ULL);
        (void)_t2367;
        ;
        return _t2367;
    }
    ;
    Bool _t2434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t2434 = *_hp; free(_hp); }
    (void)_t2434;
    if (_t2434) {
        Str *_t2368 = Str_lit("Neq", 3ULL);
        (void)_t2368;
        ;
        return _t2368;
    }
    ;
    Bool _t2435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t2435 = *_hp; free(_hp); }
    (void)_t2435;
    if (_t2435) {
        Str *_t2369 = Str_lit("Lt", 2ULL);
        (void)_t2369;
        ;
        return _t2369;
    }
    ;
    Bool _t2436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t2436 = *_hp; free(_hp); }
    (void)_t2436;
    if (_t2436) {
        Str *_t2370 = Str_lit("LtEq", 4ULL);
        (void)_t2370;
        ;
        return _t2370;
    }
    ;
    Bool _t2437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t2437 = *_hp; free(_hp); }
    (void)_t2437;
    if (_t2437) {
        Str *_t2371 = Str_lit("Gt", 2ULL);
        (void)_t2371;
        ;
        return _t2371;
    }
    ;
    Bool _t2438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t2438 = *_hp; free(_hp); }
    (void)_t2438;
    if (_t2438) {
        Str *_t2372 = Str_lit("GtEq", 4ULL);
        (void)_t2372;
        ;
        return _t2372;
    }
    ;
    Bool _t2439; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t2439 = *_hp; free(_hp); }
    (void)_t2439;
    if (_t2439) {
        Str *_t2373 = Str_lit("ColonEq", 7ULL);
        (void)_t2373;
        ;
        return _t2373;
    }
    ;
    Bool _t2440; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t2440 = *_hp; free(_hp); }
    (void)_t2440;
    if (_t2440) {
        Str *_t2374 = Str_lit("Ident", 5ULL);
        (void)_t2374;
        ;
        return _t2374;
    }
    ;
    Bool _t2441; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t2441 = *_hp; free(_hp); }
    (void)_t2441;
    if (_t2441) {
        Str *_t2375 = Str_lit("StringTok", 9ULL);
        (void)_t2375;
        ;
        return _t2375;
    }
    ;
    Bool _t2442; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t2442 = *_hp; free(_hp); }
    (void)_t2442;
    if (_t2442) {
        Str *_t2376 = Str_lit("Number", 6ULL);
        (void)_t2376;
        ;
        return _t2376;
    }
    ;
    Bool _t2443; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t2443 = *_hp; free(_hp); }
    (void)_t2443;
    if (_t2443) {
        Str *_t2377 = Str_lit("Char", 4ULL);
        (void)_t2377;
        ;
        return _t2377;
    }
    ;
    Bool _t2444; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t2444 = *_hp; free(_hp); }
    (void)_t2444;
    if (_t2444) {
        Str *_t2378 = Str_lit("KwMode", 6ULL);
        (void)_t2378;
        ;
        return _t2378;
    }
    ;
    Bool _t2445; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t2445 = *_hp; free(_hp); }
    (void)_t2445;
    if (_t2445) {
        Str *_t2379 = Str_lit("KwMut", 5ULL);
        (void)_t2379;
        ;
        return _t2379;
    }
    ;
    Bool _t2446; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t2446 = *_hp; free(_hp); }
    (void)_t2446;
    if (_t2446) {
        Str *_t2380 = Str_lit("KwOwn", 5ULL);
        (void)_t2380;
        ;
        return _t2380;
    }
    ;
    Bool _t2447; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t2447 = *_hp; free(_hp); }
    (void)_t2447;
    if (_t2447) {
        Str *_t2381 = Str_lit("KwRef", 5ULL);
        (void)_t2381;
        ;
        return _t2381;
    }
    ;
    Bool _t2448; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t2448 = *_hp; free(_hp); }
    (void)_t2448;
    if (_t2448) {
        Str *_t2382 = Str_lit("KwShallow", 9ULL);
        (void)_t2382;
        ;
        return _t2382;
    }
    ;
    Bool _t2449; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t2449 = *_hp; free(_hp); }
    (void)_t2449;
    if (_t2449) {
        Str *_t2383 = Str_lit("KwStruct", 8ULL);
        (void)_t2383;
        ;
        return _t2383;
    }
    ;
    Bool _t2450; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t2450 = *_hp; free(_hp); }
    (void)_t2450;
    if (_t2450) {
        Str *_t2384 = Str_lit("KwExtStruct", 11ULL);
        (void)_t2384;
        ;
        return _t2384;
    }
    ;
    Bool _t2451; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t2451 = *_hp; free(_hp); }
    (void)_t2451;
    if (_t2451) {
        Str *_t2385 = Str_lit("KwEnum", 6ULL);
        (void)_t2385;
        ;
        return _t2385;
    }
    ;
    Bool _t2452; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t2452 = *_hp; free(_hp); }
    (void)_t2452;
    if (_t2452) {
        Str *_t2386 = Str_lit("KwNamespace", 11ULL);
        (void)_t2386;
        ;
        return _t2386;
    }
    ;
    Bool _t2453; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t2453 = *_hp; free(_hp); }
    (void)_t2453;
    if (_t2453) {
        Str *_t2387 = Str_lit("KwFunc", 6ULL);
        (void)_t2387;
        ;
        return _t2387;
    }
    ;
    Bool _t2454; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t2454 = *_hp; free(_hp); }
    (void)_t2454;
    if (_t2454) {
        Str *_t2388 = Str_lit("KwProc", 6ULL);
        (void)_t2388;
        ;
        return _t2388;
    }
    ;
    Bool _t2455; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t2455 = *_hp; free(_hp); }
    (void)_t2455;
    if (_t2455) {
        Str *_t2389 = Str_lit("KwTest", 6ULL);
        (void)_t2389;
        ;
        return _t2389;
    }
    ;
    Bool _t2456; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t2456 = *_hp; free(_hp); }
    (void)_t2456;
    if (_t2456) {
        Str *_t2390 = Str_lit("KwMacro", 7ULL);
        (void)_t2390;
        ;
        return _t2390;
    }
    ;
    Bool _t2457; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    if (_t2457) {
        Str *_t2391 = Str_lit("KwExtFunc", 9ULL);
        (void)_t2391;
        ;
        return _t2391;
    }
    ;
    Bool _t2458; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t2458 = *_hp; free(_hp); }
    (void)_t2458;
    if (_t2458) {
        Str *_t2392 = Str_lit("KwExtProc", 9ULL);
        (void)_t2392;
        ;
        return _t2392;
    }
    ;
    Bool _t2459; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t2459 = *_hp; free(_hp); }
    (void)_t2459;
    if (_t2459) {
        Str *_t2393 = Str_lit("KwReturns", 9ULL);
        (void)_t2393;
        ;
        return _t2393;
    }
    ;
    Bool _t2460; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t2460 = *_hp; free(_hp); }
    (void)_t2460;
    if (_t2460) {
        Str *_t2394 = Str_lit("KwThrows", 8ULL);
        (void)_t2394;
        ;
        return _t2394;
    }
    ;
    Bool _t2461; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t2461 = *_hp; free(_hp); }
    (void)_t2461;
    if (_t2461) {
        Str *_t2395 = Str_lit("KwIf", 4ULL);
        (void)_t2395;
        ;
        return _t2395;
    }
    ;
    Bool _t2462; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t2462 = *_hp; free(_hp); }
    (void)_t2462;
    if (_t2462) {
        Str *_t2396 = Str_lit("KwElse", 6ULL);
        (void)_t2396;
        ;
        return _t2396;
    }
    ;
    Bool _t2463; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t2463 = *_hp; free(_hp); }
    (void)_t2463;
    if (_t2463) {
        Str *_t2397 = Str_lit("KwWhile", 7ULL);
        (void)_t2397;
        ;
        return _t2397;
    }
    ;
    Bool _t2464; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t2464 = *_hp; free(_hp); }
    (void)_t2464;
    if (_t2464) {
        Str *_t2398 = Str_lit("KwFor", 5ULL);
        (void)_t2398;
        ;
        return _t2398;
    }
    ;
    Bool _t2465; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t2465 = *_hp; free(_hp); }
    (void)_t2465;
    if (_t2465) {
        Str *_t2399 = Str_lit("KwIn", 4ULL);
        (void)_t2399;
        ;
        return _t2399;
    }
    ;
    Bool _t2466; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t2466 = *_hp; free(_hp); }
    (void)_t2466;
    if (_t2466) {
        Str *_t2400 = Str_lit("KwSwitch", 8ULL);
        (void)_t2400;
        ;
        return _t2400;
    }
    ;
    Bool _t2467; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t2467 = *_hp; free(_hp); }
    (void)_t2467;
    if (_t2467) {
        Str *_t2401 = Str_lit("KwMatch", 7ULL);
        (void)_t2401;
        ;
        return _t2401;
    }
    ;
    Bool _t2468; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t2468 = *_hp; free(_hp); }
    (void)_t2468;
    if (_t2468) {
        Str *_t2402 = Str_lit("KwCase", 6ULL);
        (void)_t2402;
        ;
        return _t2402;
    }
    ;
    Bool _t2469; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    if (_t2469) {
        Str *_t2403 = Str_lit("KwDefault", 9ULL);
        (void)_t2403;
        ;
        return _t2403;
    }
    ;
    Bool _t2470; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t2470 = *_hp; free(_hp); }
    (void)_t2470;
    if (_t2470) {
        Str *_t2404 = Str_lit("KwReturn", 8ULL);
        (void)_t2404;
        ;
        return _t2404;
    }
    ;
    Bool _t2471; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t2471 = *_hp; free(_hp); }
    (void)_t2471;
    if (_t2471) {
        Str *_t2405 = Str_lit("KwThrow", 7ULL);
        (void)_t2405;
        ;
        return _t2405;
    }
    ;
    Bool _t2472; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t2472 = *_hp; free(_hp); }
    (void)_t2472;
    if (_t2472) {
        Str *_t2406 = Str_lit("KwCatch", 7ULL);
        (void)_t2406;
        ;
        return _t2406;
    }
    ;
    Bool _t2473; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t2473 = *_hp; free(_hp); }
    (void)_t2473;
    if (_t2473) {
        Str *_t2407 = Str_lit("KwBreak", 7ULL);
        (void)_t2407;
        ;
        return _t2407;
    }
    ;
    Bool _t2474; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t2474 = *_hp; free(_hp); }
    (void)_t2474;
    if (_t2474) {
        Str *_t2408 = Str_lit("KwContinue", 10ULL);
        (void)_t2408;
        ;
        return _t2408;
    }
    ;
    Bool _t2475; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t2475 = *_hp; free(_hp); }
    (void)_t2475;
    if (_t2475) {
        Str *_t2409 = Str_lit("KwDefer", 7ULL);
        (void)_t2409;
        ;
        return _t2409;
    }
    ;
    Bool _t2476; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t2476 = *_hp; free(_hp); }
    (void)_t2476;
    if (_t2476) {
        Str *_t2410 = Str_lit("KwTrue", 6ULL);
        (void)_t2410;
        ;
        return _t2410;
    }
    ;
    Bool _t2477; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t2477 = *_hp; free(_hp); }
    (void)_t2477;
    if (_t2477) {
        Str *_t2411 = Str_lit("KwFalse", 7ULL);
        (void)_t2411;
        ;
        return _t2411;
    }
    ;
    Bool _t2478; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t2478 = *_hp; free(_hp); }
    (void)_t2478;
    if (_t2478) {
        Str *_t2412 = Str_lit("KwNull", 6ULL);
        (void)_t2412;
        ;
        return _t2412;
    }
    ;
    Bool _t2479; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t2479 = *_hp; free(_hp); }
    (void)_t2479;
    if (_t2479) {
        Str *_t2413 = Str_lit("Error", 5ULL);
        (void)_t2413;
        ;
        return _t2413;
    }
    ;
    Str *_t2480 = Str_lit("unknown", 7ULL);
    (void)_t2480;
    return _t2480;
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

