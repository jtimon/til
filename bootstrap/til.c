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
#include "til_lexer.h"
#include "til_ast.h"
#include "til_til.h"

#include "ext.h"

Vec * tokenize(Str *, Str *);
Expr * til_parse(Vec *, Str *);
Str * til_parse_mode(void);
Expr * expr_null(void);
Bool expr_is_null(Expr *);
I32 expr_get_tag(Expr *);
Str * expr_get_str_val(Expr *);
Expr * expr_get_child(Expr *, U32);
U32 expr_nchildren(Expr *);
void expr_set_core(Expr *);
void expr_swap_children(Expr *, Vec *);
Vec * expr_vec_new(void);
void expr_vec_push(Vec *, Expr *);
Expr * expr_vec_get(Vec *, U32);
U32 expr_vec_count(Vec *);
Mode * til_mode_none(void);
Mode * til_mode_resolve(Str *);
Bool til_mode_eq(Mode *, Mode *);
Mode * til_mode_script(void);
Mode * til_mode_cli(void);
Mode * til_mode_gui(void);
Mode * til_mode_test(void);
Mode * til_mode_pure(void);
Mode * til_mode_pura(void);
Mode * til_mode_lib(void);
Mode * til_mode_liba(void);
Str * til_mode_name(Mode *);
Str * til_mode_auto_import(Mode *);
Bool til_mode_is_lib(Mode *);
Bool til_mode_is_lib_output(Mode *);
TypeScope * tscope_new(TypeScope *);
void tscope_free(TypeScope *);
I32 til_init_declarations(Expr *, TypeScope *);
I32 til_type_check(Expr *, TypeScope *, Mode *);
void til_precomp(Expr *);
void til_scavenge(Expr *, Mode *, Bool);
I32 til_interpret_v(Expr *, Mode *, Bool, Str *, Str *, Str *, Str *, Vec *);
I32 til_build(Expr *, Mode *, Bool, Str *, Str *);
I32 til_build_header(Expr *, Str *);
I32 til_build_til_binding(Expr *, Str *, Str *);
I32 til_compile_c(Str *, Str *, Str *, Str *, Str *);
I32 til_compile_lib(Str *, Str *, Str *, Str *, Str *);
void til_ast_print(Expr *, U32);
Str * til_bin_dir(void);
Str * til_realpath(Str *);
Str * til_str_left(Str *, U64);
I32 til_system(Str *);
Set * til_set_new(void);
Bool til_set_has(Set *, Str *);
void til_set_add(Set *, Str *);
void til_set_free(Set *);

Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

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
Bool * TilType_is_Unknown(TilType * self);
Bool * TilType_is_None(TilType * self);
Bool * TilType_is_I64(TilType * self);
Bool * TilType_is_U8(TilType * self);
Bool * TilType_is_I16(TilType * self);
Bool * TilType_is_I32(TilType * self);
Bool * TilType_is_U32(TilType * self);
Bool * TilType_is_U64(TilType * self);
Bool * TilType_is_F32(TilType * self);
Bool * TilType_is_Bool(TilType * self);
Bool * TilType_is_Struct(TilType * self);
Bool * TilType_is_StructDef(TilType * self);
Bool * TilType_is_Enum(TilType * self);
Bool * TilType_is_EnumDef(TilType * self);
Bool * TilType_is_FuncDef(TilType * self);
Bool * TilType_is_FuncPtr(TilType * self);
Bool * TilType_is_Dynamic(TilType * self);
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
ExprData * ExprData_Body(void);
ExprData * ExprData_LiteralStr(Str * val);
ExprData * ExprData_LiteralNum(Str * val);
ExprData * ExprData_LiteralBool(Str * val);
ExprData * ExprData_LiteralNull(void);
ExprData * ExprData_Ident(Str * val);
ExprData * ExprData_Decl(Declaration * val);
ExprData * ExprData_Assign(Str * val);
ExprData * ExprData_FCall(void);
ExprData * ExprData_FuncDef(FunctionDef * val);
ExprData * ExprData_StructDef(void);
ExprData * ExprData_EnumDef(void);
ExprData * ExprData_FieldAccess(Str * val);
ExprData * ExprData_FieldAssign(Str * val);
ExprData * ExprData_Return(void);
ExprData * ExprData_If(void);
ExprData * ExprData_While(void);
ExprData * ExprData_ForIn(Str * val);
ExprData * ExprData_NamedArg(Str * val);
ExprData * ExprData_Break(void);
ExprData * ExprData_Continue(void);
ExprData * ExprData_MapLit(void);
ExprData * ExprData_SetLit(void);
ExprData * ExprData_Switch(void);
ExprData * ExprData_Case(void);
Str * ExprData_get_LiteralStr(ExprData * self);
Str * ExprData_get_LiteralNum(ExprData * self);
Str * ExprData_get_LiteralBool(ExprData * self);
Str * ExprData_get_Ident(ExprData * self);
Declaration * ExprData_get_Decl(ExprData * self);
Str * ExprData_get_Assign(ExprData * self);
FunctionDef * ExprData_get_FuncDef(ExprData * self);
Str * ExprData_get_FieldAccess(ExprData * self);
Str * ExprData_get_FieldAssign(ExprData * self);
Str * ExprData_get_ForIn(ExprData * self);
Str * ExprData_get_NamedArg(ExprData * self);
Bool * ExprData_is_Body(ExprData * self);
Bool * ExprData_is_LiteralStr(ExprData * self);
Bool * ExprData_is_LiteralNum(ExprData * self);
Bool * ExprData_is_LiteralBool(ExprData * self);
Bool * ExprData_is_LiteralNull(ExprData * self);
Bool * ExprData_is_Ident(ExprData * self);
Bool * ExprData_is_Decl(ExprData * self);
Bool * ExprData_is_Assign(ExprData * self);
Bool * ExprData_is_FCall(ExprData * self);
Bool * ExprData_is_FuncDef(ExprData * self);
Bool * ExprData_is_StructDef(ExprData * self);
Bool * ExprData_is_EnumDef(ExprData * self);
Bool * ExprData_is_FieldAccess(ExprData * self);
Bool * ExprData_is_FieldAssign(ExprData * self);
Bool * ExprData_is_Return(ExprData * self);
Bool * ExprData_is_If(ExprData * self);
Bool * ExprData_is_While(ExprData * self);
Bool * ExprData_is_ForIn(ExprData * self);
Bool * ExprData_is_NamedArg(ExprData * self);
Bool * ExprData_is_Break(ExprData * self);
Bool * ExprData_is_Continue(ExprData * self);
Bool * ExprData_is_MapLit(ExprData * self);
Bool * ExprData_is_SetLit(ExprData * self);
Bool * ExprData_is_Switch(ExprData * self);
Bool * ExprData_is_Case(ExprData * self);
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
Bool * Mode_eq(Mode * self, Mode * other);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(void * e);
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

static I64 *_t3647;
static I64 *_t3648;
static I64 *_t3649;
static U64 *CAP_LIT;
static I64 *_t3650;
static I64 *_t3651;
static I64 *_t3652;
static U64 *CAP_VIEW;
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

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
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
    if (!self) return;
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

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
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

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t56 = U8_to_i64(DEREF(val));
    (void)_t56;
    Str *_t57 = I64_to_str(&(I64){_t56});
    (void)_t57;
    ;
    return _t57;
}

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t73 = I16_to_i64(DEREF(val));
    (void)_t73;
    Str *_t74 = I64_to_str(&(I64){_t73});
    (void)_t74;
    ;
    return _t74;
}

I16 * I16_neg(I16 * a) {
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

I16 * I16_abs(I16 * a) {
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

U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t102 = I32_to_i64(DEREF(val));
    (void)_t102;
    Str *_t103 = I64_to_str(&(I64){_t102});
    (void)_t103;
    ;
    return _t103;
}

I32 * I32_neg(I32 * a) {
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

I32 * I32_abs(I32 * a) {
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

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t131 = F32_from_i64_ext(val);
    (void)_t131;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t131; return _r; }
}

U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t147 = U32_to_i64(DEREF(val));
    (void)_t147;
    Str *_t148 = I64_to_str(&(I64){_t147});
    (void)_t148;
    ;
    return _t148;
}

U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t164 = U64_to_str_ext(val);
    (void)_t164;
    return _t164;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t165 = U64_from_i64_ext(val);
    (void)_t165;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t165; return _r; }
}

U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

Str * I64_to_str(I64 * val) {
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

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t230 = 0;
    (void)_t230;
    I64 _t231 = I64_sub(_t230, DEREF(a));
    (void)_t231;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t231; return _r; }
}

I64 * I64_abs(I64 * a) {
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

U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
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
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Bool_to_str(Bool * b) {
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

I64 * Bool_cmp(Bool * a, Bool * b) {
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

U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
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
    if (!self) return;
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
    if (!self) return;
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
    if (!self) return;
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
    if (!self) return;
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

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t1065 = Str_lit("Str", 3ULL);
    (void)_t1065;
    U64 _t1066; { U64 *_hp = (U64 *)Str_size(); _t1066 = *_hp; free(_hp); }
    (void)_t1066;
    Vec *parts = Vec_new(_t1065, &(U64){_t1066});
    (void)parts;
    Str_delete(_t1065, &(Bool){1});
    ;
    U64 _t1067; { U64 *_hp = (U64 *)Str_len(delim); _t1067 = *_hp; free(_hp); }
    (void)_t1067;
    U64 _t1068 = 0;
    (void)_t1068;
    Bool _t1069 = U64_eq(_t1067, _t1068);
    (void)_t1069;
    ;
    ;
    if (_t1069) {
        Str *_t1049 = Str_clone(self);
        (void)_t1049;
        Vec_push(parts, _t1049);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1059; { U64 *_hp = (U64 *)Str_len(self); _t1059 = *_hp; free(_hp); }
        (void)_t1059;
        U64 _t1060; { U64 *_hp = (U64 *)Str_len(delim); _t1060 = *_hp; free(_hp); }
        (void)_t1060;
        U64 _t1061 = U64_sub(_t1059, _t1060);
        (void)_t1061;
        ;
        ;
        Bool _wcond1050; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1061}); _wcond1050 = *_hp; free(_hp); }
        (void)_wcond1050;
        ;
        if (_wcond1050) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1062; { U64 *_hp = (U64 *)Str_len(delim); _t1062 = *_hp; free(_hp); }
        (void)_t1062;
        Str *_t1063 = Str_substr(self, &(U64){pos}, &(U64){_t1062});
        (void)_t1063;
        ;
        Bool _t1064; { Bool *_hp = (Bool *)Str_eq(_t1063, delim); _t1064 = *_hp; free(_hp); }
        (void)_t1064;
        Str_delete(_t1063, &(Bool){1});
        if (_t1064) {
            U64 _t1051 = U64_sub(pos, start);
            (void)_t1051;
            Str *_t1052 = Str_substr(self, &(U64){start}, &(U64){_t1051});
            (void)_t1052;
            ;
            Str *_t1053 = Str_clone(_t1052);
            (void)_t1053;
            Str_delete(_t1052, &(Bool){1});
            Vec_push(parts, _t1053);
            U64 _t1054; { U64 *_hp = (U64 *)Str_len(delim); _t1054 = *_hp; free(_hp); }
            (void)_t1054;
            U64 _t1055 = U64_add(pos, _t1054);
            (void)_t1055;
            ;
            start = _t1055;
            ;
            U64 _t1056 = U64_clone(&(U64){start});
            (void)_t1056;
            pos = _t1056;
            ;
        } else {
            U64 _t1057 = 1;
            (void)_t1057;
            U64 _t1058 = U64_add(pos, _t1057);
            (void)_t1058;
            ;
            pos = _t1058;
            ;
        }
        ;
    }
    ;
    U64 _t1070; { U64 *_hp = (U64 *)Str_len(self); _t1070 = *_hp; free(_hp); }
    (void)_t1070;
    U64 _t1071 = U64_sub(_t1070, start);
    (void)_t1071;
    ;
    Str *_t1072 = Str_substr(self, &(U64){start}, &(U64){_t1071});
    (void)_t1072;
    ;
    ;
    Str *_t1073 = Str_clone(_t1072);
    (void)_t1073;
    Str_delete(_t1072, &(Bool){1});
    Vec_push(parts, _t1073);
    return parts;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1109 = malloc(DEREF(elem_size));
    (void)_t1109;
    U64 _t1110 = 0;
    (void)_t1110;
    I64 _t1111 = 1;
    (void)_t1111;
    U64 _t1112 = U64_clone(elem_size);
    (void)_t1112;
    Vec *_t1113 = malloc(sizeof(Vec));
    _t1113->data = _t1109;
    _t1113->count = _t1110;
    _t1113->cap = _t1111;
    _t1113->elem_size = _t1112;
    { Str *_ca = Str_clone(elem_type); _t1113->elem_type = *_ca; free(_ca); }
    (void)_t1113;
    ;
    ;
    ;
    return _t1113;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1118 = U64_eq(self->count, self->cap);
    (void)_t1118;
    if (_t1118) {
        U64 _t1114 = 2;
        (void)_t1114;
        U64 new_cap = U64_mul(self->cap, _t1114);
        (void)new_cap;
        ;
        U64 _t1115 = U64_mul(new_cap, self->elem_size);
        (void)_t1115;
        void *_t1116 = realloc(self->data, _t1115);
        (void)_t1116;
        ;
        self->data = _t1116;
        U64 _t1117 = U64_clone(&(U64){new_cap});
        (void)_t1117;
        ;
        self->cap = _t1117;
        ;
    }
    ;
    U64 *_t1119 = malloc(sizeof(U64)); *_t1119 = U64_mul(self->count, self->elem_size);
    (void)_t1119;
    void *_t1120 = ptr_add(self->data, DEREF(_t1119));
    (void)_t1120;
    memcpy(_t1120, val, self->elem_size);
    U64_delete(_t1119, &(Bool){1});
    free(val);
    U64 _t1121 = 1;
    (void)_t1121;
    U64 _t1122 = U64_add(self->count, _t1121);
    (void)_t1122;
    ;
    self->count = _t1122;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1137; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1137 = *_hp; free(_hp); }
    (void)_t1137;
    if (_t1137) {
        Str *_t1123 = Str_lit("Str", 3ULL);
        (void)_t1123;
        U64 _t1124; { U64 *_hp = (U64 *)Str_size(); _t1124 = *_hp; free(_hp); }
        (void)_t1124;
        U64 _t1125 = 5;
        (void)_t1125;
        Array *_va18 = Array_new(_t1123, &(U64){_t1124}, &(U64){_t1125});
        (void)_va18;
        Str_delete(_t1123, &(Bool){1});
        ;
        ;
        U64 _t1126 = 0;
        (void)_t1126;
        Str *_t1127 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1127;
        Array_set(_va18, &(U64){_t1126}, _t1127);
        ;
        U64 _t1128 = 1;
        (void)_t1128;
        Str *_t1129 = U64_to_str(DEREF(i));
        (void)_t1129;
        Array_set(_va18, &(U64){_t1128}, _t1129);
        ;
        U64 _t1130 = 2;
        (void)_t1130;
        Str *_t1131 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1131;
        Array_set(_va18, &(U64){_t1130}, _t1131);
        ;
        U64 _t1132 = 3;
        (void)_t1132;
        Str *_t1133 = U64_to_str(self->count);
        (void)_t1133;
        Array_set(_va18, &(U64){_t1132}, _t1133);
        ;
        U64 _t1134 = 4;
        (void)_t1134;
        Str *_t1135 = Str_lit(")", 1ULL);
        (void)_t1135;
        Array_set(_va18, &(U64){_t1134}, _t1135);
        ;
        Str *_t1136 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1136;
        panic(_t1136, _va18);
        Str_delete(_t1136, &(Bool){1});
    }
    ;
    U64 *_t1138 = malloc(sizeof(U64)); *_t1138 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1138;
    void *_t1139 = ptr_add(self->data, DEREF(_t1138));
    (void)_t1139;
    U64_delete(_t1138, &(Bool){1});
    return _t1139;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1153; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1153 = *_hp; free(_hp); }
    (void)_t1153;
    Bool _t1154 = Bool_not(_t1153);
    (void)_t1154;
    ;
    if (_t1154) {
        {
            U64 _fi1140 = 0;
            (void)_fi1140;
            while (1) {
                U64 _t1142 = 0;
                (void)_t1142;
                Range *_t1143 = Range_new(_t1142, self->count);
                (void)_t1143;
                ;
                U64 _t1144; { U64 *_hp = (U64 *)Range_len(_t1143); _t1144 = *_hp; free(_hp); }
                (void)_t1144;
                Range_delete(_t1143, &(Bool){1});
                Bool _wcond1141; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1140}, &(U64){_t1144}); _wcond1141 = *_hp; free(_hp); }
                (void)_wcond1141;
                ;
                if (_wcond1141) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1145 = 0;
                (void)_t1145;
                Range *_t1146 = Range_new(_t1145, self->count);
                (void)_t1146;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1146, _fi1140); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1146, &(Bool){1});
                U64 _t1147 = 1;
                (void)_t1147;
                U64 _t1148 = U64_add(_fi1140, _t1147);
                (void)_t1148;
                ;
                _fi1140 = _t1148;
                ;
                U64 *_t1149 = malloc(sizeof(U64)); *_t1149 = U64_mul(i, self->elem_size);
                (void)_t1149;
                ;
                void *_t1150 = ptr_add(self->data, DEREF(_t1149));
                (void)_t1150;
                Bool _t1151 = 0;
                (void)_t1151;
                dyn_call_delete(&self->elem_type, _t1150, &(Bool){_t1151});
                U64_delete(_t1149, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1155; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1155 = *_hp; free(_hp); }
    (void)_t1155;
    Bool _t1156 = Bool_not(_t1155);
    (void)_t1156;
    ;
    if (_t1156) {
        Bool _t1152 = 0;
        (void)_t1152;
        Str_delete(&self->elem_type, &(Bool){_t1152});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1171 = U64_mul(self->cap, self->elem_size);
    (void)_t1171;
    U8 *new_data = malloc(_t1171);
    (void)new_data;
    ;
    Bool _t1172; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1172 = *_hp; free(_hp); }
    (void)_t1172;
    Bool _t1173 = Bool_not(_t1172);
    (void)_t1173;
    ;
    if (_t1173) {
        {
            U64 _fi1157 = 0;
            (void)_fi1157;
            while (1) {
                U64 _t1159 = 0;
                (void)_t1159;
                Range *_t1160 = Range_new(_t1159, self->count);
                (void)_t1160;
                ;
                U64 _t1161; { U64 *_hp = (U64 *)Range_len(_t1160); _t1161 = *_hp; free(_hp); }
                (void)_t1161;
                Range_delete(_t1160, &(Bool){1});
                Bool _wcond1158; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1157}, &(U64){_t1161}); _wcond1158 = *_hp; free(_hp); }
                (void)_wcond1158;
                ;
                if (_wcond1158) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1162 = 0;
                (void)_t1162;
                Range *_t1163 = Range_new(_t1162, self->count);
                (void)_t1163;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1163, _fi1157); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1163, &(Bool){1});
                U64 _t1164 = 1;
                (void)_t1164;
                U64 _t1165 = U64_add(_fi1157, _t1164);
                (void)_t1165;
                ;
                _fi1157 = _t1165;
                ;
                U64 *_t1166 = malloc(sizeof(U64)); *_t1166 = U64_mul(i, self->elem_size);
                (void)_t1166;
                void *_t1167 = ptr_add(self->data, DEREF(_t1166));
                (void)_t1167;
                void *cloned = dyn_call_clone(&self->elem_type, _t1167);
                (void)cloned;
                U64_delete(_t1166, &(Bool){1});
                U64 *_t1168 = malloc(sizeof(U64)); *_t1168 = U64_mul(i, self->elem_size);
                (void)_t1168;
                ;
                void *_t1169 = ptr_add(new_data, DEREF(_t1168));
                (void)_t1169;
                memcpy(_t1169, cloned, self->elem_size);
                U64_delete(_t1168, &(Bool){1});
                free(cloned);
            }
            ;
        }
    } else {
        U64 _t1170 = U64_mul(self->count, self->elem_size);
        (void)_t1170;
        memcpy(new_data, self->data, _t1170);
        ;
    }
    ;
    Vec *_t1174 = malloc(sizeof(Vec));
    _t1174->data = new_data;
    _t1174->count = self->count;
    _t1174->cap = self->cap;
    _t1174->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1174->elem_type = *_ca; free(_ca); }
    (void)_t1174;
    return _t1174;
}

Tuple * Tuple_new(void) {
    U64 _t1176 = 8;
    (void)_t1176;
    Str *_t1177 = Str_lit("Str", 3ULL);
    (void)_t1177;
    U64 _t1178; { U64 *_hp = (U64 *)Str_size(); _t1178 = *_hp; free(_hp); }
    (void)_t1178;
    Str *_t1179 = Str_lit("U64", 3ULL);
    (void)_t1179;
    U64 _t1180; { U64 *_hp = (U64 *)U64_size(); _t1180 = *_hp; free(_hp); }
    (void)_t1180;
    void *_t1181 = malloc(_t1176);
    (void)_t1181;
    ;
    U64 _t1182 = 0;
    (void)_t1182;
    I64 _t1183 = 8;
    (void)_t1183;
    Tuple *_t1184 = malloc(sizeof(Tuple));
    _t1184->data = _t1181;
    _t1184->total_size = _t1182;
    _t1184->cap = _t1183;
    { Vec *_ca = Vec_new(_t1177, &(U64){_t1178}); _t1184->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1179, &(U64){_t1180}); _t1184->type_sizes = *_ca; free(_ca); }
    (void)_t1184;
    Str_delete(_t1177, &(Bool){1});
    ;
    Str_delete(_t1179, &(Bool){1});
    ;
    ;
    ;
    return _t1184;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1185; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1185; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1192; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        U64 _t1189 = 2;
        (void)_t1189;
        U64 new_cap = U64_mul(self->cap, _t1189);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1186; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1186 = *_hp; free(_hp); }
            (void)_wcond1186;
            if (_wcond1186) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1187 = 2;
            (void)_t1187;
            U64 _t1188 = U64_mul(new_cap, _t1187);
            (void)_t1188;
            ;
            new_cap = _t1188;
            ;
        }
        void *_t1190 = realloc(self->data, new_cap);
        (void)_t1190;
        self->data = _t1190;
        U64 _t1191 = U64_clone(&(U64){new_cap});
        (void)_t1191;
        ;
        self->cap = _t1191;
        ;
    }
    ;
    void *_t1193 = ptr_add(self->data, self->total_size);
    (void)_t1193;
    memcpy(_t1193, val, DEREF(elem_size));
    free(val);
    Str *_t1194 = Str_clone(elem_type);
    (void)_t1194;
    Vec_push(&self->type_names, _t1194);
    U64 _t1195 = U64_clone(elem_size);
    (void)_t1195;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1195; _oa; }));
    U64 _t1196 = U64_clone(&(U64){new_total});
    (void)_t1196;
    ;
    self->total_size = _t1196;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1222; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    Bool _t1223; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1222}); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    ;
    if (_t1223) {
        Str *_t1197 = Str_lit("Str", 3ULL);
        (void)_t1197;
        U64 _t1198; { U64 *_hp = (U64 *)Str_size(); _t1198 = *_hp; free(_hp); }
        (void)_t1198;
        U64 _t1199 = 5;
        (void)_t1199;
        Array *_va19 = Array_new(_t1197, &(U64){_t1198}, &(U64){_t1199});
        (void)_va19;
        Str_delete(_t1197, &(Bool){1});
        ;
        ;
        U64 _t1200 = 0;
        (void)_t1200;
        Str *_t1201 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1201;
        Array_set(_va19, &(U64){_t1200}, _t1201);
        ;
        U64 _t1202 = 1;
        (void)_t1202;
        Str *_t1203 = U64_to_str(DEREF(i));
        (void)_t1203;
        Array_set(_va19, &(U64){_t1202}, _t1203);
        ;
        U64 _t1204 = 2;
        (void)_t1204;
        Str *_t1205 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1205;
        Array_set(_va19, &(U64){_t1204}, _t1205);
        ;
        U64 _t1206; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1206 = *_hp; free(_hp); }
        (void)_t1206;
        U64 _t1207 = 3;
        (void)_t1207;
        Str *_t1208 = U64_to_str(_t1206);
        (void)_t1208;
        ;
        Array_set(_va19, &(U64){_t1207}, _t1208);
        ;
        U64 _t1209 = 4;
        (void)_t1209;
        Str *_t1210 = Str_lit(")", 1ULL);
        (void)_t1210;
        Array_set(_va19, &(U64){_t1209}, _t1210);
        ;
        Str *_t1211 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1211;
        panic(_t1211, _va19);
        Str_delete(_t1211, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1212 = 0;
        (void)_fi1212;
        while (1) {
            U64 _t1214 = 0;
            (void)_t1214;
            Range *_t1215 = Range_new(_t1214, DEREF(i));
            (void)_t1215;
            ;
            U64 _t1216; { U64 *_hp = (U64 *)Range_len(_t1215); _t1216 = *_hp; free(_hp); }
            (void)_t1216;
            Range_delete(_t1215, &(Bool){1});
            Bool _wcond1213; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1212}, &(U64){_t1216}); _wcond1213 = *_hp; free(_hp); }
            (void)_wcond1213;
            ;
            if (_wcond1213) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1217 = 0;
            (void)_t1217;
            Range *_t1218 = Range_new(_t1217, DEREF(i));
            (void)_t1218;
            ;
            U64 *j = Range_get(_t1218, _fi1212);
            (void)j;
            Range_delete(_t1218, &(Bool){1});
            U64 _t1219 = 1;
            (void)_t1219;
            U64 _t1220 = U64_add(_fi1212, _t1219);
            (void)_t1220;
            ;
            _fi1212 = _t1220;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1221 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1221;
            U64_delete(j, &(Bool){1});
            *offset = _t1221;
            ;
        }
        ;
    }
    void *_t1224 = ptr_add(self->data, DEREF(offset));
    (void)_t1224;
    U64_delete(offset, &(Bool){1});
    return _t1224;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1225 = Vec_get(&self->type_names, i);
    (void)_t1225;
    return _t1225;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1226 = Vec_get(&self->type_sizes, i);
    (void)_t1226;
    return _t1226;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1227 = 0;
        (void)_fi1227;
        while (1) {
            U64 _t1229 = 0;
            (void)_t1229;
            U64 _t1230; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1230 = *_hp; free(_hp); }
            (void)_t1230;
            Range *_t1231 = Range_new(_t1229, _t1230);
            (void)_t1231;
            ;
            ;
            U64 _t1232; { U64 *_hp = (U64 *)Range_len(_t1231); _t1232 = *_hp; free(_hp); }
            (void)_t1232;
            Range_delete(_t1231, &(Bool){1});
            Bool _wcond1228; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1227}, &(U64){_t1232}); _wcond1228 = *_hp; free(_hp); }
            (void)_wcond1228;
            ;
            if (_wcond1228) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1233 = 0;
            (void)_t1233;
            U64 _t1234; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1234 = *_hp; free(_hp); }
            (void)_t1234;
            Range *_t1235 = Range_new(_t1233, _t1234);
            (void)_t1235;
            ;
            ;
            U64 *i = Range_get(_t1235, _fi1227);
            (void)i;
            Range_delete(_t1235, &(Bool){1});
            U64 _t1236 = 1;
            (void)_t1236;
            U64 _t1237 = U64_add(_fi1227, _t1236);
            (void)_t1237;
            ;
            _fi1227 = _t1237;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1238 = ptr_add(self->data, DEREF(offset));
            (void)_t1238;
            Bool _t1239 = 0;
            (void)_t1239;
            dyn_call_delete(tn, _t1238, &(Bool){_t1239});
            ;
            U64 _t1240 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1240;
            U64_delete(i, &(Bool){1});
            *offset = _t1240;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1241 = 0;
    (void)_t1241;
    Vec_delete(&self->type_names, &(Bool){_t1241});
    ;
    Bool _t1242 = 0;
    (void)_t1242;
    Vec_delete(&self->type_sizes, &(Bool){_t1242});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1259 = 0;
    (void)_t1259;
    Bool _t1260 = U64_eq(new_cap, _t1259);
    (void)_t1260;
    ;
    if (_t1260) {
        I64 _t1243 = 8;
        (void)_t1243;
        U64 _t1244; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1243}); _t1244 = *_hp; free(_hp); }
        (void)_t1244;
        ;
        new_cap = _t1244;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1245 = 0;
        (void)_fi1245;
        while (1) {
            U64 _t1247 = 0;
            (void)_t1247;
            U64 _t1248; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1248 = *_hp; free(_hp); }
            (void)_t1248;
            Range *_t1249 = Range_new(_t1247, _t1248);
            (void)_t1249;
            ;
            ;
            U64 _t1250; { U64 *_hp = (U64 *)Range_len(_t1249); _t1250 = *_hp; free(_hp); }
            (void)_t1250;
            Range_delete(_t1249, &(Bool){1});
            Bool _wcond1246; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1245}, &(U64){_t1250}); _wcond1246 = *_hp; free(_hp); }
            (void)_wcond1246;
            ;
            if (_wcond1246) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1251 = 0;
            (void)_t1251;
            U64 _t1252; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1252 = *_hp; free(_hp); }
            (void)_t1252;
            Range *_t1253 = Range_new(_t1251, _t1252);
            (void)_t1253;
            ;
            ;
            U64 *i = Range_get(_t1253, _fi1245);
            (void)i;
            Range_delete(_t1253, &(Bool){1});
            U64 _t1254 = 1;
            (void)_t1254;
            U64 _t1255 = U64_add(_fi1245, _t1254);
            (void)_t1255;
            ;
            _fi1245 = _t1255;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1256 = ptr_add(self->data, DEREF(offset));
            (void)_t1256;
            void *cloned = dyn_call_clone(tn, _t1256);
            (void)cloned;
            void *_t1257 = ptr_add(new_data, DEREF(offset));
            (void)_t1257;
            memcpy(_t1257, cloned, DEREF(ts));
            free(cloned);
            U64 _t1258 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1258;
            U64_delete(i, &(Bool){1});
            *offset = _t1258;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1261 = U64_clone(&(U64){new_cap});
    (void)_t1261;
    ;
    Vec *_t1262 = Vec_clone(&self->type_names);
    (void)_t1262;
    Vec *_t1263 = Vec_clone(&self->type_sizes);
    (void)_t1263;
    Tuple *_t1264 = malloc(sizeof(Tuple));
    _t1264->data = new_data;
    _t1264->total_size = self->total_size;
    _t1264->cap = _t1261;
    { Vec *_ca = Vec_clone(_t1262); _t1264->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1263); _t1264->type_sizes = *_ca; free(_ca); }
    (void)_t1264;
    ;
    Vec_delete(_t1262, &(Bool){1});
    Vec_delete(_t1263, &(Bool){1});
    return _t1264;
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
    Bool _t1332; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1332 = *_hp; free(_hp); }
    (void)_t1332;
    if (_t1332) {
        Bool _t1266; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1266 = *_hp; free(_hp); }
        (void)_t1266;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1266; return _r; }
    }
    ;
    Bool _t1333; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1333 = *_hp; free(_hp); }
    (void)_t1333;
    if (_t1333) {
        Bool _t1267; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1267 = *_hp; free(_hp); }
        (void)_t1267;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1267; return _r; }
    }
    ;
    Bool _t1334; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1334 = *_hp; free(_hp); }
    (void)_t1334;
    if (_t1334) {
        Bool _t1268; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1268 = *_hp; free(_hp); }
        (void)_t1268;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1268; return _r; }
    }
    ;
    Bool _t1335; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1335 = *_hp; free(_hp); }
    (void)_t1335;
    if (_t1335) {
        Bool _t1269; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1269 = *_hp; free(_hp); }
        (void)_t1269;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1269; return _r; }
    }
    ;
    Bool _t1336; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1336 = *_hp; free(_hp); }
    (void)_t1336;
    if (_t1336) {
        Bool _t1270; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1270 = *_hp; free(_hp); }
        (void)_t1270;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1270; return _r; }
    }
    ;
    Bool _t1337; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1337 = *_hp; free(_hp); }
    (void)_t1337;
    if (_t1337) {
        Bool _t1271; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1271 = *_hp; free(_hp); }
        (void)_t1271;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1271; return _r; }
    }
    ;
    Bool _t1338; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1338 = *_hp; free(_hp); }
    (void)_t1338;
    if (_t1338) {
        Bool _t1272; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1272 = *_hp; free(_hp); }
        (void)_t1272;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1272; return _r; }
    }
    ;
    Bool _t1339; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1339 = *_hp; free(_hp); }
    (void)_t1339;
    if (_t1339) {
        Bool _t1273; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1273 = *_hp; free(_hp); }
        (void)_t1273;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1273; return _r; }
    }
    ;
    Bool _t1340; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1340 = *_hp; free(_hp); }
    (void)_t1340;
    if (_t1340) {
        Bool _t1274; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1274 = *_hp; free(_hp); }
        (void)_t1274;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1274; return _r; }
    }
    ;
    Bool _t1341; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1341 = *_hp; free(_hp); }
    (void)_t1341;
    if (_t1341) {
        Bool _t1275; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1275 = *_hp; free(_hp); }
        (void)_t1275;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1275; return _r; }
    }
    ;
    Bool _t1342; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1342 = *_hp; free(_hp); }
    (void)_t1342;
    if (_t1342) {
        Bool _t1276; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1276 = *_hp; free(_hp); }
        (void)_t1276;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1276; return _r; }
    }
    ;
    Bool _t1343; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1343 = *_hp; free(_hp); }
    (void)_t1343;
    if (_t1343) {
        Bool _t1277; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1277 = *_hp; free(_hp); }
        (void)_t1277;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1277; return _r; }
    }
    ;
    Bool _t1344; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1344 = *_hp; free(_hp); }
    (void)_t1344;
    if (_t1344) {
        Bool _t1278; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1278 = *_hp; free(_hp); }
        (void)_t1278;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1278; return _r; }
    }
    ;
    Bool _t1345; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1345 = *_hp; free(_hp); }
    (void)_t1345;
    if (_t1345) {
        Bool _t1279; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1279 = *_hp; free(_hp); }
        (void)_t1279;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1279; return _r; }
    }
    ;
    Bool _t1346; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1346 = *_hp; free(_hp); }
    (void)_t1346;
    if (_t1346) {
        Bool _t1280; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1280 = *_hp; free(_hp); }
        (void)_t1280;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1280; return _r; }
    }
    ;
    Bool _t1347; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1347 = *_hp; free(_hp); }
    (void)_t1347;
    if (_t1347) {
        Bool _t1281; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1281 = *_hp; free(_hp); }
        (void)_t1281;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1281; return _r; }
    }
    ;
    Bool _t1348; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1348 = *_hp; free(_hp); }
    (void)_t1348;
    if (_t1348) {
        Bool _t1282; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1282 = *_hp; free(_hp); }
        (void)_t1282;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1282; return _r; }
    }
    ;
    Bool _t1349; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(self); _t1349 = *_hp; free(_hp); }
    (void)_t1349;
    if (_t1349) {
        Bool _t1283; { Bool *_hp = (Bool *)TokenType_is_DotDotDot(other); _t1283 = *_hp; free(_hp); }
        (void)_t1283;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1283; return _r; }
    }
    ;
    Bool _t1350; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1350 = *_hp; free(_hp); }
    (void)_t1350;
    if (_t1350) {
        Bool _t1284; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1284 = *_hp; free(_hp); }
        (void)_t1284;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1284; return _r; }
    }
    ;
    Bool _t1351; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1351 = *_hp; free(_hp); }
    (void)_t1351;
    if (_t1351) {
        Bool _t1285; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1285 = *_hp; free(_hp); }
        (void)_t1285;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1285; return _r; }
    }
    ;
    Bool _t1352; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1352 = *_hp; free(_hp); }
    (void)_t1352;
    if (_t1352) {
        Bool _t1286; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1286 = *_hp; free(_hp); }
        (void)_t1286;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1286; return _r; }
    }
    ;
    Bool _t1353; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1353 = *_hp; free(_hp); }
    (void)_t1353;
    if (_t1353) {
        Bool _t1287; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1287 = *_hp; free(_hp); }
        (void)_t1287;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1287; return _r; }
    }
    ;
    Bool _t1354; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1354 = *_hp; free(_hp); }
    (void)_t1354;
    if (_t1354) {
        Bool _t1288; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1288 = *_hp; free(_hp); }
        (void)_t1288;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1288; return _r; }
    }
    ;
    Bool _t1355; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1355 = *_hp; free(_hp); }
    (void)_t1355;
    if (_t1355) {
        Bool _t1289; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1289 = *_hp; free(_hp); }
        (void)_t1289;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1289; return _r; }
    }
    ;
    Bool _t1356; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1356 = *_hp; free(_hp); }
    (void)_t1356;
    if (_t1356) {
        Bool _t1290; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1290 = *_hp; free(_hp); }
        (void)_t1290;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1290; return _r; }
    }
    ;
    Bool _t1357; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1357 = *_hp; free(_hp); }
    (void)_t1357;
    if (_t1357) {
        Bool _t1291; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1291 = *_hp; free(_hp); }
        (void)_t1291;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1291; return _r; }
    }
    ;
    Bool _t1358; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1358 = *_hp; free(_hp); }
    (void)_t1358;
    if (_t1358) {
        Bool _t1292; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1292 = *_hp; free(_hp); }
        (void)_t1292;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1292; return _r; }
    }
    ;
    Bool _t1359; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1359 = *_hp; free(_hp); }
    (void)_t1359;
    if (_t1359) {
        Bool _t1293; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1293 = *_hp; free(_hp); }
        (void)_t1293;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1293; return _r; }
    }
    ;
    Bool _t1360; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1360 = *_hp; free(_hp); }
    (void)_t1360;
    if (_t1360) {
        Bool _t1294; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1294 = *_hp; free(_hp); }
        (void)_t1294;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1294; return _r; }
    }
    ;
    Bool _t1361; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1361 = *_hp; free(_hp); }
    (void)_t1361;
    if (_t1361) {
        Bool _t1295; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1295 = *_hp; free(_hp); }
        (void)_t1295;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1295; return _r; }
    }
    ;
    Bool _t1362; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    if (_t1362) {
        Bool _t1296; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1296 = *_hp; free(_hp); }
        (void)_t1296;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1296; return _r; }
    }
    ;
    Bool _t1363; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1363 = *_hp; free(_hp); }
    (void)_t1363;
    if (_t1363) {
        Bool _t1297; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1297 = *_hp; free(_hp); }
        (void)_t1297;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1297; return _r; }
    }
    ;
    Bool _t1364; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1364 = *_hp; free(_hp); }
    (void)_t1364;
    if (_t1364) {
        Bool _t1298; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1298 = *_hp; free(_hp); }
        (void)_t1298;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1298; return _r; }
    }
    ;
    Bool _t1365; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1365 = *_hp; free(_hp); }
    (void)_t1365;
    if (_t1365) {
        Bool _t1299; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1299 = *_hp; free(_hp); }
        (void)_t1299;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1299; return _r; }
    }
    ;
    Bool _t1366; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1366 = *_hp; free(_hp); }
    (void)_t1366;
    if (_t1366) {
        Bool _t1300; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1300 = *_hp; free(_hp); }
        (void)_t1300;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1300; return _r; }
    }
    ;
    Bool _t1367; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    if (_t1367) {
        Bool _t1301; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1301 = *_hp; free(_hp); }
        (void)_t1301;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1301; return _r; }
    }
    ;
    Bool _t1368; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        Bool _t1302; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1302 = *_hp; free(_hp); }
        (void)_t1302;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1302; return _r; }
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        Bool _t1303; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1303 = *_hp; free(_hp); }
        (void)_t1303;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1303; return _r; }
    }
    ;
    Bool _t1370; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    if (_t1370) {
        Bool _t1304; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1304 = *_hp; free(_hp); }
        (void)_t1304;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1304; return _r; }
    }
    ;
    Bool _t1371; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1371 = *_hp; free(_hp); }
    (void)_t1371;
    if (_t1371) {
        Bool _t1305; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1305 = *_hp; free(_hp); }
        (void)_t1305;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1305; return _r; }
    }
    ;
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        Bool _t1306; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1306 = *_hp; free(_hp); }
        (void)_t1306;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1306; return _r; }
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Bool _t1307; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1307 = *_hp; free(_hp); }
        (void)_t1307;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1307; return _r; }
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Bool _t1308; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1308 = *_hp; free(_hp); }
        (void)_t1308;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1308; return _r; }
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Bool _t1309; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1309 = *_hp; free(_hp); }
        (void)_t1309;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1309; return _r; }
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Bool _t1310; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1310 = *_hp; free(_hp); }
        (void)_t1310;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1310; return _r; }
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Bool _t1311; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1311 = *_hp; free(_hp); }
        (void)_t1311;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1311; return _r; }
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Bool _t1312; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1312 = *_hp; free(_hp); }
        (void)_t1312;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1312; return _r; }
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Bool _t1313; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1313 = *_hp; free(_hp); }
        (void)_t1313;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1313; return _r; }
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Bool _t1314; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1314 = *_hp; free(_hp); }
        (void)_t1314;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1314; return _r; }
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Bool _t1315; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1315 = *_hp; free(_hp); }
        (void)_t1315;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1315; return _r; }
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Bool _t1316; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1316 = *_hp; free(_hp); }
        (void)_t1316;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1316; return _r; }
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Bool _t1317; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1317 = *_hp; free(_hp); }
        (void)_t1317;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1317; return _r; }
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Bool _t1318; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1318 = *_hp; free(_hp); }
        (void)_t1318;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1318; return _r; }
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Bool _t1319; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1319 = *_hp; free(_hp); }
        (void)_t1319;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1319; return _r; }
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Bool _t1320; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1320 = *_hp; free(_hp); }
        (void)_t1320;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1320; return _r; }
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Bool _t1321; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1321 = *_hp; free(_hp); }
        (void)_t1321;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1321; return _r; }
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Bool _t1322; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1322 = *_hp; free(_hp); }
        (void)_t1322;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1322; return _r; }
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Bool _t1323; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1323 = *_hp; free(_hp); }
        (void)_t1323;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1323; return _r; }
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Bool _t1324; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1324 = *_hp; free(_hp); }
        (void)_t1324;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1324; return _r; }
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Bool _t1325; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1325 = *_hp; free(_hp); }
        (void)_t1325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1325; return _r; }
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Bool _t1326; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1326 = *_hp; free(_hp); }
        (void)_t1326;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1326; return _r; }
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Bool _t1327; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1327 = *_hp; free(_hp); }
        (void)_t1327;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1327; return _r; }
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Bool _t1328; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1328 = *_hp; free(_hp); }
        (void)_t1328;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1328; return _r; }
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Bool _t1329; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1329 = *_hp; free(_hp); }
        (void)_t1329;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1329; return _r; }
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Bool _t1330; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1330 = *_hp; free(_hp); }
        (void)_t1330;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1330; return _r; }
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Bool _t1331; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1331 = *_hp; free(_hp); }
        (void)_t1331;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1331; return _r; }
    }
    ;
    Bool _t1398 = 0;
    (void)_t1398;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1398; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        ;
        return TokenType_DotDotDot();
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1437 = *_hp; free(_hp); }
    (void)_t1437;
    if (_t1437) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1438; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1438 = *_hp; free(_hp); }
    (void)_t1438;
    if (_t1438) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1439; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1439 = *_hp; free(_hp); }
    (void)_t1439;
    if (_t1439) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1440; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1440 = *_hp; free(_hp); }
    (void)_t1440;
    if (_t1440) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1441; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1441 = *_hp; free(_hp); }
    (void)_t1441;
    if (_t1441) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1442; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1442 = *_hp; free(_hp); }
    (void)_t1442;
    if (_t1442) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1443; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1443 = *_hp; free(_hp); }
    (void)_t1443;
    if (_t1443) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1444; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1444 = *_hp; free(_hp); }
    (void)_t1444;
    if (_t1444) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1445; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1445 = *_hp; free(_hp); }
    (void)_t1445;
    if (_t1445) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1446; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1446 = *_hp; free(_hp); }
    (void)_t1446;
    if (_t1446) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1447; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1447 = *_hp; free(_hp); }
    (void)_t1447;
    if (_t1447) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1448; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1448 = *_hp; free(_hp); }
    (void)_t1448;
    if (_t1448) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1449; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1449 = *_hp; free(_hp); }
    (void)_t1449;
    if (_t1449) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1450; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    if (_t1450) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1451; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    if (_t1451) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1452; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1452 = *_hp; free(_hp); }
    (void)_t1452;
    if (_t1452) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1453; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1453 = *_hp; free(_hp); }
    (void)_t1453;
    if (_t1453) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1454; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    if (_t1454) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1455; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    if (_t1455) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1456; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    if (_t1456) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1457; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1457 = *_hp; free(_hp); }
    (void)_t1457;
    if (_t1457) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1458; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1458 = *_hp; free(_hp); }
    (void)_t1458;
    if (_t1458) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1459; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    if (_t1459) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1460; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    if (_t1460) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1461; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1461 = *_hp; free(_hp); }
    (void)_t1461;
    if (_t1461) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1462; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1462 = *_hp; free(_hp); }
    (void)_t1462;
    if (_t1462) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1463; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1463 = *_hp; free(_hp); }
    (void)_t1463;
    if (_t1463) {
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
    Bool _t1530; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1530 = *_hp; free(_hp); }
    (void)_t1530;
    if (_t1530) {
        Str *_t1464 = Str_lit("Eof", 3ULL);
        (void)_t1464;
        ;
        return _t1464;
    }
    ;
    Bool _t1531; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1531 = *_hp; free(_hp); }
    (void)_t1531;
    if (_t1531) {
        Str *_t1465 = Str_lit("LParen", 6ULL);
        (void)_t1465;
        ;
        return _t1465;
    }
    ;
    Bool _t1532; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1532 = *_hp; free(_hp); }
    (void)_t1532;
    if (_t1532) {
        Str *_t1466 = Str_lit("RParen", 6ULL);
        (void)_t1466;
        ;
        return _t1466;
    }
    ;
    Bool _t1533; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1533 = *_hp; free(_hp); }
    (void)_t1533;
    if (_t1533) {
        Str *_t1467 = Str_lit("LBrace", 6ULL);
        (void)_t1467;
        ;
        return _t1467;
    }
    ;
    Bool _t1534; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1534 = *_hp; free(_hp); }
    (void)_t1534;
    if (_t1534) {
        Str *_t1468 = Str_lit("RBrace", 6ULL);
        (void)_t1468;
        ;
        return _t1468;
    }
    ;
    Bool _t1535; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1535 = *_hp; free(_hp); }
    (void)_t1535;
    if (_t1535) {
        Str *_t1469 = Str_lit("LBracket", 8ULL);
        (void)_t1469;
        ;
        return _t1469;
    }
    ;
    Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1536 = *_hp; free(_hp); }
    (void)_t1536;
    if (_t1536) {
        Str *_t1470 = Str_lit("RBracket", 8ULL);
        (void)_t1470;
        ;
        return _t1470;
    }
    ;
    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1537 = *_hp; free(_hp); }
    (void)_t1537;
    if (_t1537) {
        Str *_t1471 = Str_lit("Comma", 5ULL);
        (void)_t1471;
        ;
        return _t1471;
    }
    ;
    Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1538 = *_hp; free(_hp); }
    (void)_t1538;
    if (_t1538) {
        Str *_t1472 = Str_lit("Colon", 5ULL);
        (void)_t1472;
        ;
        return _t1472;
    }
    ;
    Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1539 = *_hp; free(_hp); }
    (void)_t1539;
    if (_t1539) {
        Str *_t1473 = Str_lit("Question", 8ULL);
        (void)_t1473;
        ;
        return _t1473;
    }
    ;
    Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1540 = *_hp; free(_hp); }
    (void)_t1540;
    if (_t1540) {
        Str *_t1474 = Str_lit("Bang", 4ULL);
        (void)_t1474;
        ;
        return _t1474;
    }
    ;
    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1541 = *_hp; free(_hp); }
    (void)_t1541;
    if (_t1541) {
        Str *_t1475 = Str_lit("Minus", 5ULL);
        (void)_t1475;
        ;
        return _t1475;
    }
    ;
    Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1542 = *_hp; free(_hp); }
    (void)_t1542;
    if (_t1542) {
        Str *_t1476 = Str_lit("Plus", 4ULL);
        (void)_t1476;
        ;
        return _t1476;
    }
    ;
    Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1543 = *_hp; free(_hp); }
    (void)_t1543;
    if (_t1543) {
        Str *_t1477 = Str_lit("Star", 4ULL);
        (void)_t1477;
        ;
        return _t1477;
    }
    ;
    Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1544 = *_hp; free(_hp); }
    (void)_t1544;
    if (_t1544) {
        Str *_t1478 = Str_lit("Slash", 5ULL);
        (void)_t1478;
        ;
        return _t1478;
    }
    ;
    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1545 = *_hp; free(_hp); }
    (void)_t1545;
    if (_t1545) {
        Str *_t1479 = Str_lit("Dot", 3ULL);
        (void)_t1479;
        ;
        return _t1479;
    }
    ;
    Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1546 = *_hp; free(_hp); }
    (void)_t1546;
    if (_t1546) {
        Str *_t1480 = Str_lit("DotDot", 6ULL);
        (void)_t1480;
        ;
        return _t1480;
    }
    ;
    Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDotDot()); _t1547 = *_hp; free(_hp); }
    (void)_t1547;
    if (_t1547) {
        Str *_t1481 = Str_lit("DotDotDot", 9ULL);
        (void)_t1481;
        ;
        return _t1481;
    }
    ;
    Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1548 = *_hp; free(_hp); }
    (void)_t1548;
    if (_t1548) {
        Str *_t1482 = Str_lit("Eq", 2ULL);
        (void)_t1482;
        ;
        return _t1482;
    }
    ;
    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1549 = *_hp; free(_hp); }
    (void)_t1549;
    if (_t1549) {
        Str *_t1483 = Str_lit("EqEq", 4ULL);
        (void)_t1483;
        ;
        return _t1483;
    }
    ;
    Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1550 = *_hp; free(_hp); }
    (void)_t1550;
    if (_t1550) {
        Str *_t1484 = Str_lit("Neq", 3ULL);
        (void)_t1484;
        ;
        return _t1484;
    }
    ;
    Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1551 = *_hp; free(_hp); }
    (void)_t1551;
    if (_t1551) {
        Str *_t1485 = Str_lit("Lt", 2ULL);
        (void)_t1485;
        ;
        return _t1485;
    }
    ;
    Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1552 = *_hp; free(_hp); }
    (void)_t1552;
    if (_t1552) {
        Str *_t1486 = Str_lit("LtEq", 4ULL);
        (void)_t1486;
        ;
        return _t1486;
    }
    ;
    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1553 = *_hp; free(_hp); }
    (void)_t1553;
    if (_t1553) {
        Str *_t1487 = Str_lit("Gt", 2ULL);
        (void)_t1487;
        ;
        return _t1487;
    }
    ;
    Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1554 = *_hp; free(_hp); }
    (void)_t1554;
    if (_t1554) {
        Str *_t1488 = Str_lit("GtEq", 4ULL);
        (void)_t1488;
        ;
        return _t1488;
    }
    ;
    Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1555 = *_hp; free(_hp); }
    (void)_t1555;
    if (_t1555) {
        Str *_t1489 = Str_lit("ColonEq", 7ULL);
        (void)_t1489;
        ;
        return _t1489;
    }
    ;
    Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1556 = *_hp; free(_hp); }
    (void)_t1556;
    if (_t1556) {
        Str *_t1490 = Str_lit("Ident", 5ULL);
        (void)_t1490;
        ;
        return _t1490;
    }
    ;
    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1557 = *_hp; free(_hp); }
    (void)_t1557;
    if (_t1557) {
        Str *_t1491 = Str_lit("StringTok", 9ULL);
        (void)_t1491;
        ;
        return _t1491;
    }
    ;
    Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1558 = *_hp; free(_hp); }
    (void)_t1558;
    if (_t1558) {
        Str *_t1492 = Str_lit("Number", 6ULL);
        (void)_t1492;
        ;
        return _t1492;
    }
    ;
    Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1559 = *_hp; free(_hp); }
    (void)_t1559;
    if (_t1559) {
        Str *_t1493 = Str_lit("Char", 4ULL);
        (void)_t1493;
        ;
        return _t1493;
    }
    ;
    Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1560 = *_hp; free(_hp); }
    (void)_t1560;
    if (_t1560) {
        Str *_t1494 = Str_lit("KwMode", 6ULL);
        (void)_t1494;
        ;
        return _t1494;
    }
    ;
    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1561 = *_hp; free(_hp); }
    (void)_t1561;
    if (_t1561) {
        Str *_t1495 = Str_lit("KwMut", 5ULL);
        (void)_t1495;
        ;
        return _t1495;
    }
    ;
    Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1562 = *_hp; free(_hp); }
    (void)_t1562;
    if (_t1562) {
        Str *_t1496 = Str_lit("KwOwn", 5ULL);
        (void)_t1496;
        ;
        return _t1496;
    }
    ;
    Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1563 = *_hp; free(_hp); }
    (void)_t1563;
    if (_t1563) {
        Str *_t1497 = Str_lit("KwRef", 5ULL);
        (void)_t1497;
        ;
        return _t1497;
    }
    ;
    Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1564 = *_hp; free(_hp); }
    (void)_t1564;
    if (_t1564) {
        Str *_t1498 = Str_lit("KwShallow", 9ULL);
        (void)_t1498;
        ;
        return _t1498;
    }
    ;
    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1565 = *_hp; free(_hp); }
    (void)_t1565;
    if (_t1565) {
        Str *_t1499 = Str_lit("KwStruct", 8ULL);
        (void)_t1499;
        ;
        return _t1499;
    }
    ;
    Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1566 = *_hp; free(_hp); }
    (void)_t1566;
    if (_t1566) {
        Str *_t1500 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1500;
        ;
        return _t1500;
    }
    ;
    Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1567 = *_hp; free(_hp); }
    (void)_t1567;
    if (_t1567) {
        Str *_t1501 = Str_lit("KwEnum", 6ULL);
        (void)_t1501;
        ;
        return _t1501;
    }
    ;
    Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1568 = *_hp; free(_hp); }
    (void)_t1568;
    if (_t1568) {
        Str *_t1502 = Str_lit("KwNamespace", 11ULL);
        (void)_t1502;
        ;
        return _t1502;
    }
    ;
    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1569 = *_hp; free(_hp); }
    (void)_t1569;
    if (_t1569) {
        Str *_t1503 = Str_lit("KwFunc", 6ULL);
        (void)_t1503;
        ;
        return _t1503;
    }
    ;
    Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1570 = *_hp; free(_hp); }
    (void)_t1570;
    if (_t1570) {
        Str *_t1504 = Str_lit("KwProc", 6ULL);
        (void)_t1504;
        ;
        return _t1504;
    }
    ;
    Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1571 = *_hp; free(_hp); }
    (void)_t1571;
    if (_t1571) {
        Str *_t1505 = Str_lit("KwTest", 6ULL);
        (void)_t1505;
        ;
        return _t1505;
    }
    ;
    Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1572 = *_hp; free(_hp); }
    (void)_t1572;
    if (_t1572) {
        Str *_t1506 = Str_lit("KwMacro", 7ULL);
        (void)_t1506;
        ;
        return _t1506;
    }
    ;
    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1573 = *_hp; free(_hp); }
    (void)_t1573;
    if (_t1573) {
        Str *_t1507 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1507;
        ;
        return _t1507;
    }
    ;
    Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1574 = *_hp; free(_hp); }
    (void)_t1574;
    if (_t1574) {
        Str *_t1508 = Str_lit("KwExtProc", 9ULL);
        (void)_t1508;
        ;
        return _t1508;
    }
    ;
    Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1575 = *_hp; free(_hp); }
    (void)_t1575;
    if (_t1575) {
        Str *_t1509 = Str_lit("KwReturns", 9ULL);
        (void)_t1509;
        ;
        return _t1509;
    }
    ;
    Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1576 = *_hp; free(_hp); }
    (void)_t1576;
    if (_t1576) {
        Str *_t1510 = Str_lit("KwThrows", 8ULL);
        (void)_t1510;
        ;
        return _t1510;
    }
    ;
    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1577 = *_hp; free(_hp); }
    (void)_t1577;
    if (_t1577) {
        Str *_t1511 = Str_lit("KwIf", 4ULL);
        (void)_t1511;
        ;
        return _t1511;
    }
    ;
    Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1578 = *_hp; free(_hp); }
    (void)_t1578;
    if (_t1578) {
        Str *_t1512 = Str_lit("KwElse", 6ULL);
        (void)_t1512;
        ;
        return _t1512;
    }
    ;
    Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1579 = *_hp; free(_hp); }
    (void)_t1579;
    if (_t1579) {
        Str *_t1513 = Str_lit("KwWhile", 7ULL);
        (void)_t1513;
        ;
        return _t1513;
    }
    ;
    Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1580 = *_hp; free(_hp); }
    (void)_t1580;
    if (_t1580) {
        Str *_t1514 = Str_lit("KwFor", 5ULL);
        (void)_t1514;
        ;
        return _t1514;
    }
    ;
    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1581 = *_hp; free(_hp); }
    (void)_t1581;
    if (_t1581) {
        Str *_t1515 = Str_lit("KwIn", 4ULL);
        (void)_t1515;
        ;
        return _t1515;
    }
    ;
    Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1582 = *_hp; free(_hp); }
    (void)_t1582;
    if (_t1582) {
        Str *_t1516 = Str_lit("KwSwitch", 8ULL);
        (void)_t1516;
        ;
        return _t1516;
    }
    ;
    Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1583 = *_hp; free(_hp); }
    (void)_t1583;
    if (_t1583) {
        Str *_t1517 = Str_lit("KwMatch", 7ULL);
        (void)_t1517;
        ;
        return _t1517;
    }
    ;
    Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1584 = *_hp; free(_hp); }
    (void)_t1584;
    if (_t1584) {
        Str *_t1518 = Str_lit("KwCase", 6ULL);
        (void)_t1518;
        ;
        return _t1518;
    }
    ;
    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1585 = *_hp; free(_hp); }
    (void)_t1585;
    if (_t1585) {
        Str *_t1519 = Str_lit("KwDefault", 9ULL);
        (void)_t1519;
        ;
        return _t1519;
    }
    ;
    Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1586 = *_hp; free(_hp); }
    (void)_t1586;
    if (_t1586) {
        Str *_t1520 = Str_lit("KwReturn", 8ULL);
        (void)_t1520;
        ;
        return _t1520;
    }
    ;
    Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1587 = *_hp; free(_hp); }
    (void)_t1587;
    if (_t1587) {
        Str *_t1521 = Str_lit("KwThrow", 7ULL);
        (void)_t1521;
        ;
        return _t1521;
    }
    ;
    Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1588 = *_hp; free(_hp); }
    (void)_t1588;
    if (_t1588) {
        Str *_t1522 = Str_lit("KwCatch", 7ULL);
        (void)_t1522;
        ;
        return _t1522;
    }
    ;
    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1589 = *_hp; free(_hp); }
    (void)_t1589;
    if (_t1589) {
        Str *_t1523 = Str_lit("KwBreak", 7ULL);
        (void)_t1523;
        ;
        return _t1523;
    }
    ;
    Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1590 = *_hp; free(_hp); }
    (void)_t1590;
    if (_t1590) {
        Str *_t1524 = Str_lit("KwContinue", 10ULL);
        (void)_t1524;
        ;
        return _t1524;
    }
    ;
    Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1591 = *_hp; free(_hp); }
    (void)_t1591;
    if (_t1591) {
        Str *_t1525 = Str_lit("KwDefer", 7ULL);
        (void)_t1525;
        ;
        return _t1525;
    }
    ;
    Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1592 = *_hp; free(_hp); }
    (void)_t1592;
    if (_t1592) {
        Str *_t1526 = Str_lit("KwTrue", 6ULL);
        (void)_t1526;
        ;
        return _t1526;
    }
    ;
    Bool _t1593; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1593 = *_hp; free(_hp); }
    (void)_t1593;
    if (_t1593) {
        Str *_t1527 = Str_lit("KwFalse", 7ULL);
        (void)_t1527;
        ;
        return _t1527;
    }
    ;
    Bool _t1594; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1594 = *_hp; free(_hp); }
    (void)_t1594;
    if (_t1594) {
        Str *_t1528 = Str_lit("KwNull", 6ULL);
        (void)_t1528;
        ;
        return _t1528;
    }
    ;
    Bool _t1595; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1595 = *_hp; free(_hp); }
    (void)_t1595;
    if (_t1595) {
        Str *_t1529 = Str_lit("Error", 5ULL);
        (void)_t1529;
        ;
        return _t1529;
    }
    ;
    Str *_t1596 = Str_lit("unknown", 7ULL);
    (void)_t1596;
    return _t1596;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1601 = 0;
    (void)_t1601;
    TokenType_delete(&self->type, &(Bool){_t1601});
    ;
    Bool _t1602 = 0;
    (void)_t1602;
    Str_delete(&self->text, &(Bool){_t1602});
    ;
    Bool _t1603 = 0;
    (void)_t1603;
    U32_delete(&self->line, &(Bool){_t1603});
    ;
    Bool _t1604 = 0;
    (void)_t1604;
    U32_delete(&self->col, &(Bool){_t1604});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
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
    Bool _t2215; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        Bool _t2198; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t2198 = *_hp; free(_hp); }
        (void)_t2198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2198; return _r; }
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TilType_is_None(self); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        Bool _t2199; { Bool *_hp = (Bool *)TilType_is_None(other); _t2199 = *_hp; free(_hp); }
        (void)_t2199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2199; return _r; }
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TilType_is_I64(self); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        Bool _t2200; { Bool *_hp = (Bool *)TilType_is_I64(other); _t2200 = *_hp; free(_hp); }
        (void)_t2200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2200; return _r; }
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TilType_is_U8(self); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        Bool _t2201; { Bool *_hp = (Bool *)TilType_is_U8(other); _t2201 = *_hp; free(_hp); }
        (void)_t2201;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2201; return _r; }
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TilType_is_I16(self); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        Bool _t2202; { Bool *_hp = (Bool *)TilType_is_I16(other); _t2202 = *_hp; free(_hp); }
        (void)_t2202;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2202; return _r; }
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TilType_is_I32(self); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        Bool _t2203; { Bool *_hp = (Bool *)TilType_is_I32(other); _t2203 = *_hp; free(_hp); }
        (void)_t2203;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2203; return _r; }
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TilType_is_U32(self); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        Bool _t2204; { Bool *_hp = (Bool *)TilType_is_U32(other); _t2204 = *_hp; free(_hp); }
        (void)_t2204;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2204; return _r; }
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TilType_is_U64(self); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        Bool _t2205; { Bool *_hp = (Bool *)TilType_is_U64(other); _t2205 = *_hp; free(_hp); }
        (void)_t2205;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2205; return _r; }
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TilType_is_F32(self); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        Bool _t2206; { Bool *_hp = (Bool *)TilType_is_F32(other); _t2206 = *_hp; free(_hp); }
        (void)_t2206;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2206; return _r; }
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        Bool _t2207; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t2207 = *_hp; free(_hp); }
        (void)_t2207;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2207; return _r; }
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        Bool _t2208; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t2208 = *_hp; free(_hp); }
        (void)_t2208;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2208; return _r; }
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        Bool _t2209; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t2209 = *_hp; free(_hp); }
        (void)_t2209;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2209; return _r; }
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        Bool _t2210; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t2210 = *_hp; free(_hp); }
        (void)_t2210;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2210; return _r; }
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        Bool _t2211; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t2211 = *_hp; free(_hp); }
        (void)_t2211;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2211; return _r; }
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        Bool _t2212; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t2212 = *_hp; free(_hp); }
        (void)_t2212;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2212; return _r; }
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        Bool _t2213; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t2213 = *_hp; free(_hp); }
        (void)_t2213;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2213; return _r; }
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        Bool _t2214; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t2214 = *_hp; free(_hp); }
        (void)_t2214;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2214; return _r; }
    }
    ;
    Bool _t2232 = 0;
    (void)_t2232;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2232; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t2233; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        ;
        return TilType_None();
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t2240; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t2240 = *_hp; free(_hp); }
    (void)_t2240;
    if (_t2240) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t2241; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    if (_t2241) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t2242; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    if (_t2242) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t2243; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t2243 = *_hp; free(_hp); }
    (void)_t2243;
    if (_t2243) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t2244; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t2244 = *_hp; free(_hp); }
    (void)_t2244;
    if (_t2244) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t2245; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t2245 = *_hp; free(_hp); }
    (void)_t2245;
    if (_t2245) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t2246; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    if (_t2246) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t2247; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    if (_t2247) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t2248; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t2248 = *_hp; free(_hp); }
    (void)_t2248;
    if (_t2248) {
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
    Bool _t2266; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t2266 = *_hp; free(_hp); }
    (void)_t2266;
    if (_t2266) {
        Str *_t2249 = Str_lit("Unknown", 7ULL);
        (void)_t2249;
        ;
        return _t2249;
    }
    ;
    Bool _t2267; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t2267 = *_hp; free(_hp); }
    (void)_t2267;
    if (_t2267) {
        Str *_t2250 = Str_lit("None", 4ULL);
        (void)_t2250;
        ;
        return _t2250;
    }
    ;
    Bool _t2268; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t2268 = *_hp; free(_hp); }
    (void)_t2268;
    if (_t2268) {
        Str *_t2251 = Str_lit("I64", 3ULL);
        (void)_t2251;
        ;
        return _t2251;
    }
    ;
    Bool _t2269; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t2269 = *_hp; free(_hp); }
    (void)_t2269;
    if (_t2269) {
        Str *_t2252 = Str_lit("U8", 2ULL);
        (void)_t2252;
        ;
        return _t2252;
    }
    ;
    Bool _t2270; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t2270 = *_hp; free(_hp); }
    (void)_t2270;
    if (_t2270) {
        Str *_t2253 = Str_lit("I16", 3ULL);
        (void)_t2253;
        ;
        return _t2253;
    }
    ;
    Bool _t2271; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t2271 = *_hp; free(_hp); }
    (void)_t2271;
    if (_t2271) {
        Str *_t2254 = Str_lit("I32", 3ULL);
        (void)_t2254;
        ;
        return _t2254;
    }
    ;
    Bool _t2272; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t2272 = *_hp; free(_hp); }
    (void)_t2272;
    if (_t2272) {
        Str *_t2255 = Str_lit("U32", 3ULL);
        (void)_t2255;
        ;
        return _t2255;
    }
    ;
    Bool _t2273; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t2273 = *_hp; free(_hp); }
    (void)_t2273;
    if (_t2273) {
        Str *_t2256 = Str_lit("U64", 3ULL);
        (void)_t2256;
        ;
        return _t2256;
    }
    ;
    Bool _t2274; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t2274 = *_hp; free(_hp); }
    (void)_t2274;
    if (_t2274) {
        Str *_t2257 = Str_lit("F32", 3ULL);
        (void)_t2257;
        ;
        return _t2257;
    }
    ;
    Bool _t2275; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t2275 = *_hp; free(_hp); }
    (void)_t2275;
    if (_t2275) {
        Str *_t2258 = Str_lit("Bool", 4ULL);
        (void)_t2258;
        ;
        return _t2258;
    }
    ;
    Bool _t2276; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t2276 = *_hp; free(_hp); }
    (void)_t2276;
    if (_t2276) {
        Str *_t2259 = Str_lit("Struct", 6ULL);
        (void)_t2259;
        ;
        return _t2259;
    }
    ;
    Bool _t2277; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t2277 = *_hp; free(_hp); }
    (void)_t2277;
    if (_t2277) {
        Str *_t2260 = Str_lit("StructDef", 9ULL);
        (void)_t2260;
        ;
        return _t2260;
    }
    ;
    Bool _t2278; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t2278 = *_hp; free(_hp); }
    (void)_t2278;
    if (_t2278) {
        Str *_t2261 = Str_lit("Enum", 4ULL);
        (void)_t2261;
        ;
        return _t2261;
    }
    ;
    Bool _t2279; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t2279 = *_hp; free(_hp); }
    (void)_t2279;
    if (_t2279) {
        Str *_t2262 = Str_lit("EnumDef", 7ULL);
        (void)_t2262;
        ;
        return _t2262;
    }
    ;
    Bool _t2280; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t2280 = *_hp; free(_hp); }
    (void)_t2280;
    if (_t2280) {
        Str *_t2263 = Str_lit("FuncDef", 7ULL);
        (void)_t2263;
        ;
        return _t2263;
    }
    ;
    Bool _t2281; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t2281 = *_hp; free(_hp); }
    (void)_t2281;
    if (_t2281) {
        Str *_t2264 = Str_lit("FuncPtr", 7ULL);
        (void)_t2264;
        ;
        return _t2264;
    }
    ;
    Bool _t2282; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t2282 = *_hp; free(_hp); }
    (void)_t2282;
    if (_t2282) {
        Str *_t2265 = Str_lit("Dynamic", 7ULL);
        (void)_t2265;
        ;
        return _t2265;
    }
    ;
    Str *_t2283 = Str_lit("unknown", 7ULL);
    (void)_t2283;
    return _t2283;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2329 = 0;
    (void)_t2329;
    Str_delete(&self->name, &(Bool){_t2329});
    ;
    Bool _t2330 = 0;
    (void)_t2330;
    Str_delete(&self->explicit_type, &(Bool){_t2330});
    ;
    Bool _t2331 = 0;
    (void)_t2331;
    Bool_delete(&self->is_mut, &(Bool){_t2331});
    ;
    Bool _t2332 = 0;
    (void)_t2332;
    Bool_delete(&self->is_namespace, &(Bool){_t2332});
    ;
    Bool _t2333 = 0;
    (void)_t2333;
    Bool_delete(&self->is_ref, &(Bool){_t2333});
    ;
    Bool _t2334 = 0;
    (void)_t2334;
    Bool_delete(&self->is_own, &(Bool){_t2334});
    ;
    Bool _t2335 = 0;
    (void)_t2335;
    I32_delete(&self->field_offset, &(Bool){_t2335});
    ;
    Bool _t2336 = 0;
    (void)_t2336;
    I32_delete(&self->field_size, &(Bool){_t2336});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
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
    Bool _t2418; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2418 = *_hp; free(_hp); }
    (void)_t2418;
    if (_t2418) {
        Bool _t2338; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t2338 = *_hp; free(_hp); }
        (void)_t2338;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2338; return _r; }
    }
    ;
    Bool _t2419; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2419 = *_hp; free(_hp); }
    (void)_t2419;
    if (_t2419) {
        Bool _t2340; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t2340 = *_hp; free(_hp); }
        (void)_t2340;
        Bool _t2341 = Bool_not(_t2340);
        (void)_t2341;
        ;
        if (_t2341) {
            Bool _t2339 = 0;
            (void)_t2339;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2339; return _r; }
        }
        ;
        Str *_t2342 = ExprData_get_LiteralStr(self);
        (void)_t2342;
        Str *_t2343 = ExprData_get_LiteralStr(other);
        (void)_t2343;
        Bool _t2344; { Bool *_hp = (Bool *)Str_eq(_t2342, _t2343); _t2344 = *_hp; free(_hp); }
        (void)_t2344;
        Str_delete(_t2342, &(Bool){1});
        Str_delete(_t2343, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2344; return _r; }
    }
    ;
    Bool _t2420; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2420 = *_hp; free(_hp); }
    (void)_t2420;
    if (_t2420) {
        Bool _t2346; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t2346 = *_hp; free(_hp); }
        (void)_t2346;
        Bool _t2347 = Bool_not(_t2346);
        (void)_t2347;
        ;
        if (_t2347) {
            Bool _t2345 = 0;
            (void)_t2345;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2345; return _r; }
        }
        ;
        Str *_t2348 = ExprData_get_LiteralNum(self);
        (void)_t2348;
        Str *_t2349 = ExprData_get_LiteralNum(other);
        (void)_t2349;
        Bool _t2350; { Bool *_hp = (Bool *)Str_eq(_t2348, _t2349); _t2350 = *_hp; free(_hp); }
        (void)_t2350;
        Str_delete(_t2348, &(Bool){1});
        Str_delete(_t2349, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2350; return _r; }
    }
    ;
    Bool _t2421; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2421 = *_hp; free(_hp); }
    (void)_t2421;
    if (_t2421) {
        Bool _t2352; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t2352 = *_hp; free(_hp); }
        (void)_t2352;
        Bool _t2353 = Bool_not(_t2352);
        (void)_t2353;
        ;
        if (_t2353) {
            Bool _t2351 = 0;
            (void)_t2351;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2351; return _r; }
        }
        ;
        Str *_t2354 = ExprData_get_LiteralBool(self);
        (void)_t2354;
        Str *_t2355 = ExprData_get_LiteralBool(other);
        (void)_t2355;
        Bool _t2356; { Bool *_hp = (Bool *)Str_eq(_t2354, _t2355); _t2356 = *_hp; free(_hp); }
        (void)_t2356;
        Str_delete(_t2354, &(Bool){1});
        Str_delete(_t2355, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2356; return _r; }
    }
    ;
    Bool _t2422; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2422 = *_hp; free(_hp); }
    (void)_t2422;
    if (_t2422) {
        Bool _t2357; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t2357 = *_hp; free(_hp); }
        (void)_t2357;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2357; return _r; }
    }
    ;
    Bool _t2423; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2423 = *_hp; free(_hp); }
    (void)_t2423;
    if (_t2423) {
        Bool _t2359; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t2359 = *_hp; free(_hp); }
        (void)_t2359;
        Bool _t2360 = Bool_not(_t2359);
        (void)_t2360;
        ;
        if (_t2360) {
            Bool _t2358 = 0;
            (void)_t2358;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2358; return _r; }
        }
        ;
        Str *_t2361 = ExprData_get_Ident(self);
        (void)_t2361;
        Str *_t2362 = ExprData_get_Ident(other);
        (void)_t2362;
        Bool _t2363; { Bool *_hp = (Bool *)Str_eq(_t2361, _t2362); _t2363 = *_hp; free(_hp); }
        (void)_t2363;
        Str_delete(_t2361, &(Bool){1});
        Str_delete(_t2362, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2363; return _r; }
    }
    ;
    Bool _t2424; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2424 = *_hp; free(_hp); }
    (void)_t2424;
    if (_t2424) {
        Bool _t2365; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t2365 = *_hp; free(_hp); }
        (void)_t2365;
        Bool _t2366 = Bool_not(_t2365);
        (void)_t2366;
        ;
        if (_t2366) {
            Bool _t2364 = 0;
            (void)_t2364;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2364; return _r; }
        }
        ;
        Declaration *_t2367 = ExprData_get_Decl(self);
        (void)_t2367;
        Declaration *_t2368 = ExprData_get_Decl(other);
        (void)_t2368;
        Bool _t2369; { Bool *_hp = (Bool *)Declaration_eq(_t2367, _t2368); _t2369 = *_hp; free(_hp); }
        (void)_t2369;
        Declaration_delete(_t2367, &(Bool){1});
        Declaration_delete(_t2368, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2369; return _r; }
    }
    ;
    Bool _t2425; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2425 = *_hp; free(_hp); }
    (void)_t2425;
    if (_t2425) {
        Bool _t2371; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t2371 = *_hp; free(_hp); }
        (void)_t2371;
        Bool _t2372 = Bool_not(_t2371);
        (void)_t2372;
        ;
        if (_t2372) {
            Bool _t2370 = 0;
            (void)_t2370;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2370; return _r; }
        }
        ;
        Str *_t2373 = ExprData_get_Assign(self);
        (void)_t2373;
        Str *_t2374 = ExprData_get_Assign(other);
        (void)_t2374;
        Bool _t2375; { Bool *_hp = (Bool *)Str_eq(_t2373, _t2374); _t2375 = *_hp; free(_hp); }
        (void)_t2375;
        Str_delete(_t2373, &(Bool){1});
        Str_delete(_t2374, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2375; return _r; }
    }
    ;
    Bool _t2426; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2426 = *_hp; free(_hp); }
    (void)_t2426;
    if (_t2426) {
        Bool _t2376; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t2376 = *_hp; free(_hp); }
        (void)_t2376;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2376; return _r; }
    }
    ;
    Bool _t2427; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2427 = *_hp; free(_hp); }
    (void)_t2427;
    if (_t2427) {
        Bool _t2378; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t2378 = *_hp; free(_hp); }
        (void)_t2378;
        Bool _t2379 = Bool_not(_t2378);
        (void)_t2379;
        ;
        if (_t2379) {
            Bool _t2377 = 0;
            (void)_t2377;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2377; return _r; }
        }
        ;
        FunctionDef *_t2380 = ExprData_get_FuncDef(self);
        (void)_t2380;
        FunctionDef *_t2381 = ExprData_get_FuncDef(other);
        (void)_t2381;
        Bool _t2382; { Bool *_hp = (Bool *)FunctionDef_eq(_t2380, _t2381); _t2382 = *_hp; free(_hp); }
        (void)_t2382;
        FunctionDef_delete(_t2380, &(Bool){1});
        FunctionDef_delete(_t2381, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2382; return _r; }
    }
    ;
    Bool _t2428; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2428 = *_hp; free(_hp); }
    (void)_t2428;
    if (_t2428) {
        Bool _t2383; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t2383 = *_hp; free(_hp); }
        (void)_t2383;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2383; return _r; }
    }
    ;
    Bool _t2429; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2429 = *_hp; free(_hp); }
    (void)_t2429;
    if (_t2429) {
        Bool _t2384; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t2384 = *_hp; free(_hp); }
        (void)_t2384;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2384; return _r; }
    }
    ;
    Bool _t2430; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2430 = *_hp; free(_hp); }
    (void)_t2430;
    if (_t2430) {
        Bool _t2386; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t2386 = *_hp; free(_hp); }
        (void)_t2386;
        Bool _t2387 = Bool_not(_t2386);
        (void)_t2387;
        ;
        if (_t2387) {
            Bool _t2385 = 0;
            (void)_t2385;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2385; return _r; }
        }
        ;
        Str *_t2388 = ExprData_get_FieldAccess(self);
        (void)_t2388;
        Str *_t2389 = ExprData_get_FieldAccess(other);
        (void)_t2389;
        Bool _t2390; { Bool *_hp = (Bool *)Str_eq(_t2388, _t2389); _t2390 = *_hp; free(_hp); }
        (void)_t2390;
        Str_delete(_t2388, &(Bool){1});
        Str_delete(_t2389, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2390; return _r; }
    }
    ;
    Bool _t2431; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2431 = *_hp; free(_hp); }
    (void)_t2431;
    if (_t2431) {
        Bool _t2392; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t2392 = *_hp; free(_hp); }
        (void)_t2392;
        Bool _t2393 = Bool_not(_t2392);
        (void)_t2393;
        ;
        if (_t2393) {
            Bool _t2391 = 0;
            (void)_t2391;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2391; return _r; }
        }
        ;
        Str *_t2394 = ExprData_get_FieldAssign(self);
        (void)_t2394;
        Str *_t2395 = ExprData_get_FieldAssign(other);
        (void)_t2395;
        Bool _t2396; { Bool *_hp = (Bool *)Str_eq(_t2394, _t2395); _t2396 = *_hp; free(_hp); }
        (void)_t2396;
        Str_delete(_t2394, &(Bool){1});
        Str_delete(_t2395, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2396; return _r; }
    }
    ;
    Bool _t2432; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2432 = *_hp; free(_hp); }
    (void)_t2432;
    if (_t2432) {
        Bool _t2397; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t2397 = *_hp; free(_hp); }
        (void)_t2397;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2397; return _r; }
    }
    ;
    Bool _t2433; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2433 = *_hp; free(_hp); }
    (void)_t2433;
    if (_t2433) {
        Bool _t2398; { Bool *_hp = (Bool *)ExprData_is_If(other); _t2398 = *_hp; free(_hp); }
        (void)_t2398;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2398; return _r; }
    }
    ;
    Bool _t2434; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2434 = *_hp; free(_hp); }
    (void)_t2434;
    if (_t2434) {
        Bool _t2399; { Bool *_hp = (Bool *)ExprData_is_While(other); _t2399 = *_hp; free(_hp); }
        (void)_t2399;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2399; return _r; }
    }
    ;
    Bool _t2435; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2435 = *_hp; free(_hp); }
    (void)_t2435;
    if (_t2435) {
        Bool _t2401; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t2401 = *_hp; free(_hp); }
        (void)_t2401;
        Bool _t2402 = Bool_not(_t2401);
        (void)_t2402;
        ;
        if (_t2402) {
            Bool _t2400 = 0;
            (void)_t2400;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2400; return _r; }
        }
        ;
        Str *_t2403 = ExprData_get_ForIn(self);
        (void)_t2403;
        Str *_t2404 = ExprData_get_ForIn(other);
        (void)_t2404;
        Bool _t2405; { Bool *_hp = (Bool *)Str_eq(_t2403, _t2404); _t2405 = *_hp; free(_hp); }
        (void)_t2405;
        Str_delete(_t2403, &(Bool){1});
        Str_delete(_t2404, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2405; return _r; }
    }
    ;
    Bool _t2436; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2436 = *_hp; free(_hp); }
    (void)_t2436;
    if (_t2436) {
        Bool _t2407; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t2407 = *_hp; free(_hp); }
        (void)_t2407;
        Bool _t2408 = Bool_not(_t2407);
        (void)_t2408;
        ;
        if (_t2408) {
            Bool _t2406 = 0;
            (void)_t2406;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2406; return _r; }
        }
        ;
        Str *_t2409 = ExprData_get_NamedArg(self);
        (void)_t2409;
        Str *_t2410 = ExprData_get_NamedArg(other);
        (void)_t2410;
        Bool _t2411; { Bool *_hp = (Bool *)Str_eq(_t2409, _t2410); _t2411 = *_hp; free(_hp); }
        (void)_t2411;
        Str_delete(_t2409, &(Bool){1});
        Str_delete(_t2410, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2411; return _r; }
    }
    ;
    Bool _t2437; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2437 = *_hp; free(_hp); }
    (void)_t2437;
    if (_t2437) {
        Bool _t2412; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t2412 = *_hp; free(_hp); }
        (void)_t2412;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2412; return _r; }
    }
    ;
    Bool _t2438; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2438 = *_hp; free(_hp); }
    (void)_t2438;
    if (_t2438) {
        Bool _t2413; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t2413 = *_hp; free(_hp); }
        (void)_t2413;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2413; return _r; }
    }
    ;
    Bool _t2439; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2439 = *_hp; free(_hp); }
    (void)_t2439;
    if (_t2439) {
        Bool _t2414; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t2414 = *_hp; free(_hp); }
        (void)_t2414;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2414; return _r; }
    }
    ;
    Bool _t2440; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2440 = *_hp; free(_hp); }
    (void)_t2440;
    if (_t2440) {
        Bool _t2415; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t2415 = *_hp; free(_hp); }
        (void)_t2415;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2415; return _r; }
    }
    ;
    Bool _t2441; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2441 = *_hp; free(_hp); }
    (void)_t2441;
    if (_t2441) {
        Bool _t2416; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t2416 = *_hp; free(_hp); }
        (void)_t2416;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2416; return _r; }
    }
    ;
    Bool _t2442; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t2442 = *_hp; free(_hp); }
    (void)_t2442;
    if (_t2442) {
        Bool _t2417; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t2417 = *_hp; free(_hp); }
        (void)_t2417;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2417; return _r; }
    }
    ;
    Bool _t2443 = 0;
    (void)_t2443;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2443; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t2466; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2466 = *_hp; free(_hp); }
    (void)_t2466;
    if (_t2466) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t2467; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2467 = *_hp; free(_hp); }
    (void)_t2467;
    if (_t2467) {
        Str *_t2444 = ExprData_get_LiteralStr(self);
        (void)_t2444;
        ExprData *_t2445 = ExprData_LiteralStr(_t2444);
        (void)_t2445;
        Str_delete(_t2444, &(Bool){1});
        ;
        return _t2445;
    }
    ;
    Bool _t2468; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2468 = *_hp; free(_hp); }
    (void)_t2468;
    if (_t2468) {
        Str *_t2446 = ExprData_get_LiteralNum(self);
        (void)_t2446;
        ExprData *_t2447 = ExprData_LiteralNum(_t2446);
        (void)_t2447;
        Str_delete(_t2446, &(Bool){1});
        ;
        return _t2447;
    }
    ;
    Bool _t2469; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    if (_t2469) {
        Str *_t2448 = ExprData_get_LiteralBool(self);
        (void)_t2448;
        ExprData *_t2449 = ExprData_LiteralBool(_t2448);
        (void)_t2449;
        Str_delete(_t2448, &(Bool){1});
        ;
        return _t2449;
    }
    ;
    Bool _t2470; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2470 = *_hp; free(_hp); }
    (void)_t2470;
    if (_t2470) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t2471; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2471 = *_hp; free(_hp); }
    (void)_t2471;
    if (_t2471) {
        Str *_t2450 = ExprData_get_Ident(self);
        (void)_t2450;
        ExprData *_t2451 = ExprData_Ident(_t2450);
        (void)_t2451;
        Str_delete(_t2450, &(Bool){1});
        ;
        return _t2451;
    }
    ;
    Bool _t2472; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2472 = *_hp; free(_hp); }
    (void)_t2472;
    if (_t2472) {
        Declaration *_t2452 = ExprData_get_Decl(self);
        (void)_t2452;
        ExprData *_t2453 = ExprData_Decl(_t2452);
        (void)_t2453;
        Declaration_delete(_t2452, &(Bool){1});
        ;
        return _t2453;
    }
    ;
    Bool _t2473; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2473 = *_hp; free(_hp); }
    (void)_t2473;
    if (_t2473) {
        Str *_t2454 = ExprData_get_Assign(self);
        (void)_t2454;
        ExprData *_t2455 = ExprData_Assign(_t2454);
        (void)_t2455;
        Str_delete(_t2454, &(Bool){1});
        ;
        return _t2455;
    }
    ;
    Bool _t2474; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2474 = *_hp; free(_hp); }
    (void)_t2474;
    if (_t2474) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t2475; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2475 = *_hp; free(_hp); }
    (void)_t2475;
    if (_t2475) {
        FunctionDef *_t2456 = ExprData_get_FuncDef(self);
        (void)_t2456;
        ExprData *_t2457 = ExprData_FuncDef(_t2456);
        (void)_t2457;
        FunctionDef_delete(_t2456, &(Bool){1});
        ;
        return _t2457;
    }
    ;
    Bool _t2476; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2476 = *_hp; free(_hp); }
    (void)_t2476;
    if (_t2476) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t2477; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2477 = *_hp; free(_hp); }
    (void)_t2477;
    if (_t2477) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t2478; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2478 = *_hp; free(_hp); }
    (void)_t2478;
    if (_t2478) {
        Str *_t2458 = ExprData_get_FieldAccess(self);
        (void)_t2458;
        ExprData *_t2459 = ExprData_FieldAccess(_t2458);
        (void)_t2459;
        Str_delete(_t2458, &(Bool){1});
        ;
        return _t2459;
    }
    ;
    Bool _t2479; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2479 = *_hp; free(_hp); }
    (void)_t2479;
    if (_t2479) {
        Str *_t2460 = ExprData_get_FieldAssign(self);
        (void)_t2460;
        ExprData *_t2461 = ExprData_FieldAssign(_t2460);
        (void)_t2461;
        Str_delete(_t2460, &(Bool){1});
        ;
        return _t2461;
    }
    ;
    Bool _t2480; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2480 = *_hp; free(_hp); }
    (void)_t2480;
    if (_t2480) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t2481; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2481 = *_hp; free(_hp); }
    (void)_t2481;
    if (_t2481) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t2482; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2482 = *_hp; free(_hp); }
    (void)_t2482;
    if (_t2482) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t2483; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2483 = *_hp; free(_hp); }
    (void)_t2483;
    if (_t2483) {
        Str *_t2462 = ExprData_get_ForIn(self);
        (void)_t2462;
        ExprData *_t2463 = ExprData_ForIn(_t2462);
        (void)_t2463;
        Str_delete(_t2462, &(Bool){1});
        ;
        return _t2463;
    }
    ;
    Bool _t2484; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2484 = *_hp; free(_hp); }
    (void)_t2484;
    if (_t2484) {
        Str *_t2464 = ExprData_get_NamedArg(self);
        (void)_t2464;
        ExprData *_t2465 = ExprData_NamedArg(_t2464);
        (void)_t2465;
        Str_delete(_t2464, &(Bool){1});
        ;
        return _t2465;
    }
    ;
    Bool _t2485; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2485 = *_hp; free(_hp); }
    (void)_t2485;
    if (_t2485) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t2486; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2486 = *_hp; free(_hp); }
    (void)_t2486;
    if (_t2486) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t2487; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2487 = *_hp; free(_hp); }
    (void)_t2487;
    if (_t2487) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t2488; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2488 = *_hp; free(_hp); }
    (void)_t2488;
    if (_t2488) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t2489; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2489 = *_hp; free(_hp); }
    (void)_t2489;
    if (_t2489) {
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
    Bool _t2625; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2625 = *_hp; free(_hp); }
    (void)_t2625;
    if (_t2625) {
        Str *_t2490 = Str_lit("Body", 4ULL);
        (void)_t2490;
        ;
        return _t2490;
    }
    ;
    Bool _t2626; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2626 = *_hp; free(_hp); }
    (void)_t2626;
    if (_t2626) {
        Str *_t2491 = Str_lit("Str", 3ULL);
        (void)_t2491;
        U64 _t2492; { U64 *_hp = (U64 *)Str_size(); _t2492 = *_hp; free(_hp); }
        (void)_t2492;
        U64 _t2493 = 3;
        (void)_t2493;
        Array *_va24 = Array_new(_t2491, &(U64){_t2492}, &(U64){_t2493});
        (void)_va24;
        Str_delete(_t2491, &(Bool){1});
        ;
        ;
        U64 _t2494 = 0;
        (void)_t2494;
        Str *_t2495 = Str_lit("LiteralStr(", 11ULL);
        (void)_t2495;
        Array_set(_va24, &(U64){_t2494}, _t2495);
        ;
        Str *_t2496 = ExprData_get_LiteralStr(self);
        (void)_t2496;
        U64 _t2497 = 1;
        (void)_t2497;
        Str *_t2498 = Str_to_str(_t2496);
        (void)_t2498;
        Str_delete(_t2496, &(Bool){1});
        Array_set(_va24, &(U64){_t2497}, _t2498);
        ;
        U64 _t2499 = 2;
        (void)_t2499;
        Str *_t2500 = Str_lit(")", 1ULL);
        (void)_t2500;
        Array_set(_va24, &(U64){_t2499}, _t2500);
        ;
        Str *_t2501 = format(_va24);
        (void)_t2501;
        ;
        return _t2501;
    }
    ;
    Bool _t2627; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2627 = *_hp; free(_hp); }
    (void)_t2627;
    if (_t2627) {
        Str *_t2502 = Str_lit("Str", 3ULL);
        (void)_t2502;
        U64 _t2503; { U64 *_hp = (U64 *)Str_size(); _t2503 = *_hp; free(_hp); }
        (void)_t2503;
        U64 _t2504 = 3;
        (void)_t2504;
        Array *_va25 = Array_new(_t2502, &(U64){_t2503}, &(U64){_t2504});
        (void)_va25;
        Str_delete(_t2502, &(Bool){1});
        ;
        ;
        U64 _t2505 = 0;
        (void)_t2505;
        Str *_t2506 = Str_lit("LiteralNum(", 11ULL);
        (void)_t2506;
        Array_set(_va25, &(U64){_t2505}, _t2506);
        ;
        Str *_t2507 = ExprData_get_LiteralNum(self);
        (void)_t2507;
        U64 _t2508 = 1;
        (void)_t2508;
        Str *_t2509 = Str_to_str(_t2507);
        (void)_t2509;
        Str_delete(_t2507, &(Bool){1});
        Array_set(_va25, &(U64){_t2508}, _t2509);
        ;
        U64 _t2510 = 2;
        (void)_t2510;
        Str *_t2511 = Str_lit(")", 1ULL);
        (void)_t2511;
        Array_set(_va25, &(U64){_t2510}, _t2511);
        ;
        Str *_t2512 = format(_va25);
        (void)_t2512;
        ;
        return _t2512;
    }
    ;
    Bool _t2628; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2628 = *_hp; free(_hp); }
    (void)_t2628;
    if (_t2628) {
        Str *_t2513 = Str_lit("Str", 3ULL);
        (void)_t2513;
        U64 _t2514; { U64 *_hp = (U64 *)Str_size(); _t2514 = *_hp; free(_hp); }
        (void)_t2514;
        U64 _t2515 = 3;
        (void)_t2515;
        Array *_va26 = Array_new(_t2513, &(U64){_t2514}, &(U64){_t2515});
        (void)_va26;
        Str_delete(_t2513, &(Bool){1});
        ;
        ;
        U64 _t2516 = 0;
        (void)_t2516;
        Str *_t2517 = Str_lit("LiteralBool(", 12ULL);
        (void)_t2517;
        Array_set(_va26, &(U64){_t2516}, _t2517);
        ;
        Str *_t2518 = ExprData_get_LiteralBool(self);
        (void)_t2518;
        U64 _t2519 = 1;
        (void)_t2519;
        Str *_t2520 = Str_to_str(_t2518);
        (void)_t2520;
        Str_delete(_t2518, &(Bool){1});
        Array_set(_va26, &(U64){_t2519}, _t2520);
        ;
        U64 _t2521 = 2;
        (void)_t2521;
        Str *_t2522 = Str_lit(")", 1ULL);
        (void)_t2522;
        Array_set(_va26, &(U64){_t2521}, _t2522);
        ;
        Str *_t2523 = format(_va26);
        (void)_t2523;
        ;
        return _t2523;
    }
    ;
    Bool _t2629; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2629 = *_hp; free(_hp); }
    (void)_t2629;
    if (_t2629) {
        Str *_t2524 = Str_lit("LiteralNull", 11ULL);
        (void)_t2524;
        ;
        return _t2524;
    }
    ;
    Bool _t2630; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2630 = *_hp; free(_hp); }
    (void)_t2630;
    if (_t2630) {
        Str *_t2525 = Str_lit("Str", 3ULL);
        (void)_t2525;
        U64 _t2526; { U64 *_hp = (U64 *)Str_size(); _t2526 = *_hp; free(_hp); }
        (void)_t2526;
        U64 _t2527 = 3;
        (void)_t2527;
        Array *_va27 = Array_new(_t2525, &(U64){_t2526}, &(U64){_t2527});
        (void)_va27;
        Str_delete(_t2525, &(Bool){1});
        ;
        ;
        U64 _t2528 = 0;
        (void)_t2528;
        Str *_t2529 = Str_lit("Ident(", 6ULL);
        (void)_t2529;
        Array_set(_va27, &(U64){_t2528}, _t2529);
        ;
        Str *_t2530 = ExprData_get_Ident(self);
        (void)_t2530;
        U64 _t2531 = 1;
        (void)_t2531;
        Str *_t2532 = Str_to_str(_t2530);
        (void)_t2532;
        Str_delete(_t2530, &(Bool){1});
        Array_set(_va27, &(U64){_t2531}, _t2532);
        ;
        U64 _t2533 = 2;
        (void)_t2533;
        Str *_t2534 = Str_lit(")", 1ULL);
        (void)_t2534;
        Array_set(_va27, &(U64){_t2533}, _t2534);
        ;
        Str *_t2535 = format(_va27);
        (void)_t2535;
        ;
        return _t2535;
    }
    ;
    Bool _t2631; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2631 = *_hp; free(_hp); }
    (void)_t2631;
    if (_t2631) {
        Str *_t2536 = Str_lit("Str", 3ULL);
        (void)_t2536;
        U64 _t2537; { U64 *_hp = (U64 *)Str_size(); _t2537 = *_hp; free(_hp); }
        (void)_t2537;
        U64 _t2538 = 3;
        (void)_t2538;
        Array *_va28 = Array_new(_t2536, &(U64){_t2537}, &(U64){_t2538});
        (void)_va28;
        Str_delete(_t2536, &(Bool){1});
        ;
        ;
        U64 _t2539 = 0;
        (void)_t2539;
        Str *_t2540 = Str_lit("Decl(", 5ULL);
        (void)_t2540;
        Array_set(_va28, &(U64){_t2539}, _t2540);
        ;
        Declaration *_t2541 = ExprData_get_Decl(self);
        (void)_t2541;
        U64 _t2542 = 1;
        (void)_t2542;
        Str *_t2543 = Declaration_to_str(_t2541);
        (void)_t2543;
        Declaration_delete(_t2541, &(Bool){1});
        Array_set(_va28, &(U64){_t2542}, _t2543);
        ;
        U64 _t2544 = 2;
        (void)_t2544;
        Str *_t2545 = Str_lit(")", 1ULL);
        (void)_t2545;
        Array_set(_va28, &(U64){_t2544}, _t2545);
        ;
        Str *_t2546 = format(_va28);
        (void)_t2546;
        ;
        return _t2546;
    }
    ;
    Bool _t2632; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2632 = *_hp; free(_hp); }
    (void)_t2632;
    if (_t2632) {
        Str *_t2547 = Str_lit("Str", 3ULL);
        (void)_t2547;
        U64 _t2548; { U64 *_hp = (U64 *)Str_size(); _t2548 = *_hp; free(_hp); }
        (void)_t2548;
        U64 _t2549 = 3;
        (void)_t2549;
        Array *_va29 = Array_new(_t2547, &(U64){_t2548}, &(U64){_t2549});
        (void)_va29;
        Str_delete(_t2547, &(Bool){1});
        ;
        ;
        U64 _t2550 = 0;
        (void)_t2550;
        Str *_t2551 = Str_lit("Assign(", 7ULL);
        (void)_t2551;
        Array_set(_va29, &(U64){_t2550}, _t2551);
        ;
        Str *_t2552 = ExprData_get_Assign(self);
        (void)_t2552;
        U64 _t2553 = 1;
        (void)_t2553;
        Str *_t2554 = Str_to_str(_t2552);
        (void)_t2554;
        Str_delete(_t2552, &(Bool){1});
        Array_set(_va29, &(U64){_t2553}, _t2554);
        ;
        U64 _t2555 = 2;
        (void)_t2555;
        Str *_t2556 = Str_lit(")", 1ULL);
        (void)_t2556;
        Array_set(_va29, &(U64){_t2555}, _t2556);
        ;
        Str *_t2557 = format(_va29);
        (void)_t2557;
        ;
        return _t2557;
    }
    ;
    Bool _t2633; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2633 = *_hp; free(_hp); }
    (void)_t2633;
    if (_t2633) {
        Str *_t2558 = Str_lit("FCall", 5ULL);
        (void)_t2558;
        ;
        return _t2558;
    }
    ;
    Bool _t2634; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2634 = *_hp; free(_hp); }
    (void)_t2634;
    if (_t2634) {
        Str *_t2559 = Str_lit("Str", 3ULL);
        (void)_t2559;
        U64 _t2560; { U64 *_hp = (U64 *)Str_size(); _t2560 = *_hp; free(_hp); }
        (void)_t2560;
        U64 _t2561 = 3;
        (void)_t2561;
        Array *_va30 = Array_new(_t2559, &(U64){_t2560}, &(U64){_t2561});
        (void)_va30;
        Str_delete(_t2559, &(Bool){1});
        ;
        ;
        U64 _t2562 = 0;
        (void)_t2562;
        Str *_t2563 = Str_lit("FuncDef(", 8ULL);
        (void)_t2563;
        Array_set(_va30, &(U64){_t2562}, _t2563);
        ;
        FunctionDef *_t2564 = ExprData_get_FuncDef(self);
        (void)_t2564;
        U64 _t2565 = 1;
        (void)_t2565;
        Str *_t2566 = FunctionDef_to_str(_t2564);
        (void)_t2566;
        FunctionDef_delete(_t2564, &(Bool){1});
        Array_set(_va30, &(U64){_t2565}, _t2566);
        ;
        U64 _t2567 = 2;
        (void)_t2567;
        Str *_t2568 = Str_lit(")", 1ULL);
        (void)_t2568;
        Array_set(_va30, &(U64){_t2567}, _t2568);
        ;
        Str *_t2569 = format(_va30);
        (void)_t2569;
        ;
        return _t2569;
    }
    ;
    Bool _t2635; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2635 = *_hp; free(_hp); }
    (void)_t2635;
    if (_t2635) {
        Str *_t2570 = Str_lit("StructDef", 9ULL);
        (void)_t2570;
        ;
        return _t2570;
    }
    ;
    Bool _t2636; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2636 = *_hp; free(_hp); }
    (void)_t2636;
    if (_t2636) {
        Str *_t2571 = Str_lit("EnumDef", 7ULL);
        (void)_t2571;
        ;
        return _t2571;
    }
    ;
    Bool _t2637; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2637 = *_hp; free(_hp); }
    (void)_t2637;
    if (_t2637) {
        Str *_t2572 = Str_lit("Str", 3ULL);
        (void)_t2572;
        U64 _t2573; { U64 *_hp = (U64 *)Str_size(); _t2573 = *_hp; free(_hp); }
        (void)_t2573;
        U64 _t2574 = 3;
        (void)_t2574;
        Array *_va31 = Array_new(_t2572, &(U64){_t2573}, &(U64){_t2574});
        (void)_va31;
        Str_delete(_t2572, &(Bool){1});
        ;
        ;
        U64 _t2575 = 0;
        (void)_t2575;
        Str *_t2576 = Str_lit("FieldAccess(", 12ULL);
        (void)_t2576;
        Array_set(_va31, &(U64){_t2575}, _t2576);
        ;
        Str *_t2577 = ExprData_get_FieldAccess(self);
        (void)_t2577;
        U64 _t2578 = 1;
        (void)_t2578;
        Str *_t2579 = Str_to_str(_t2577);
        (void)_t2579;
        Str_delete(_t2577, &(Bool){1});
        Array_set(_va31, &(U64){_t2578}, _t2579);
        ;
        U64 _t2580 = 2;
        (void)_t2580;
        Str *_t2581 = Str_lit(")", 1ULL);
        (void)_t2581;
        Array_set(_va31, &(U64){_t2580}, _t2581);
        ;
        Str *_t2582 = format(_va31);
        (void)_t2582;
        ;
        return _t2582;
    }
    ;
    Bool _t2638; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2638 = *_hp; free(_hp); }
    (void)_t2638;
    if (_t2638) {
        Str *_t2583 = Str_lit("Str", 3ULL);
        (void)_t2583;
        U64 _t2584; { U64 *_hp = (U64 *)Str_size(); _t2584 = *_hp; free(_hp); }
        (void)_t2584;
        U64 _t2585 = 3;
        (void)_t2585;
        Array *_va32 = Array_new(_t2583, &(U64){_t2584}, &(U64){_t2585});
        (void)_va32;
        Str_delete(_t2583, &(Bool){1});
        ;
        ;
        U64 _t2586 = 0;
        (void)_t2586;
        Str *_t2587 = Str_lit("FieldAssign(", 12ULL);
        (void)_t2587;
        Array_set(_va32, &(U64){_t2586}, _t2587);
        ;
        Str *_t2588 = ExprData_get_FieldAssign(self);
        (void)_t2588;
        U64 _t2589 = 1;
        (void)_t2589;
        Str *_t2590 = Str_to_str(_t2588);
        (void)_t2590;
        Str_delete(_t2588, &(Bool){1});
        Array_set(_va32, &(U64){_t2589}, _t2590);
        ;
        U64 _t2591 = 2;
        (void)_t2591;
        Str *_t2592 = Str_lit(")", 1ULL);
        (void)_t2592;
        Array_set(_va32, &(U64){_t2591}, _t2592);
        ;
        Str *_t2593 = format(_va32);
        (void)_t2593;
        ;
        return _t2593;
    }
    ;
    Bool _t2639; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2639 = *_hp; free(_hp); }
    (void)_t2639;
    if (_t2639) {
        Str *_t2594 = Str_lit("Return", 6ULL);
        (void)_t2594;
        ;
        return _t2594;
    }
    ;
    Bool _t2640; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2640 = *_hp; free(_hp); }
    (void)_t2640;
    if (_t2640) {
        Str *_t2595 = Str_lit("If", 2ULL);
        (void)_t2595;
        ;
        return _t2595;
    }
    ;
    Bool _t2641; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2641 = *_hp; free(_hp); }
    (void)_t2641;
    if (_t2641) {
        Str *_t2596 = Str_lit("While", 5ULL);
        (void)_t2596;
        ;
        return _t2596;
    }
    ;
    Bool _t2642; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2642 = *_hp; free(_hp); }
    (void)_t2642;
    if (_t2642) {
        Str *_t2597 = Str_lit("Str", 3ULL);
        (void)_t2597;
        U64 _t2598; { U64 *_hp = (U64 *)Str_size(); _t2598 = *_hp; free(_hp); }
        (void)_t2598;
        U64 _t2599 = 3;
        (void)_t2599;
        Array *_va33 = Array_new(_t2597, &(U64){_t2598}, &(U64){_t2599});
        (void)_va33;
        Str_delete(_t2597, &(Bool){1});
        ;
        ;
        U64 _t2600 = 0;
        (void)_t2600;
        Str *_t2601 = Str_lit("ForIn(", 6ULL);
        (void)_t2601;
        Array_set(_va33, &(U64){_t2600}, _t2601);
        ;
        Str *_t2602 = ExprData_get_ForIn(self);
        (void)_t2602;
        U64 _t2603 = 1;
        (void)_t2603;
        Str *_t2604 = Str_to_str(_t2602);
        (void)_t2604;
        Str_delete(_t2602, &(Bool){1});
        Array_set(_va33, &(U64){_t2603}, _t2604);
        ;
        U64 _t2605 = 2;
        (void)_t2605;
        Str *_t2606 = Str_lit(")", 1ULL);
        (void)_t2606;
        Array_set(_va33, &(U64){_t2605}, _t2606);
        ;
        Str *_t2607 = format(_va33);
        (void)_t2607;
        ;
        return _t2607;
    }
    ;
    Bool _t2643; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2643 = *_hp; free(_hp); }
    (void)_t2643;
    if (_t2643) {
        Str *_t2608 = Str_lit("Str", 3ULL);
        (void)_t2608;
        U64 _t2609; { U64 *_hp = (U64 *)Str_size(); _t2609 = *_hp; free(_hp); }
        (void)_t2609;
        U64 _t2610 = 3;
        (void)_t2610;
        Array *_va34 = Array_new(_t2608, &(U64){_t2609}, &(U64){_t2610});
        (void)_va34;
        Str_delete(_t2608, &(Bool){1});
        ;
        ;
        U64 _t2611 = 0;
        (void)_t2611;
        Str *_t2612 = Str_lit("NamedArg(", 9ULL);
        (void)_t2612;
        Array_set(_va34, &(U64){_t2611}, _t2612);
        ;
        Str *_t2613 = ExprData_get_NamedArg(self);
        (void)_t2613;
        U64 _t2614 = 1;
        (void)_t2614;
        Str *_t2615 = Str_to_str(_t2613);
        (void)_t2615;
        Str_delete(_t2613, &(Bool){1});
        Array_set(_va34, &(U64){_t2614}, _t2615);
        ;
        U64 _t2616 = 2;
        (void)_t2616;
        Str *_t2617 = Str_lit(")", 1ULL);
        (void)_t2617;
        Array_set(_va34, &(U64){_t2616}, _t2617);
        ;
        Str *_t2618 = format(_va34);
        (void)_t2618;
        ;
        return _t2618;
    }
    ;
    Bool _t2644; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2644 = *_hp; free(_hp); }
    (void)_t2644;
    if (_t2644) {
        Str *_t2619 = Str_lit("Break", 5ULL);
        (void)_t2619;
        ;
        return _t2619;
    }
    ;
    Bool _t2645; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2645 = *_hp; free(_hp); }
    (void)_t2645;
    if (_t2645) {
        Str *_t2620 = Str_lit("Continue", 8ULL);
        (void)_t2620;
        ;
        return _t2620;
    }
    ;
    Bool _t2646; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2646 = *_hp; free(_hp); }
    (void)_t2646;
    if (_t2646) {
        Str *_t2621 = Str_lit("MapLit", 6ULL);
        (void)_t2621;
        ;
        return _t2621;
    }
    ;
    Bool _t2647; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2647 = *_hp; free(_hp); }
    (void)_t2647;
    if (_t2647) {
        Str *_t2622 = Str_lit("SetLit", 6ULL);
        (void)_t2622;
        ;
        return _t2622;
    }
    ;
    Bool _t2648; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2648 = *_hp; free(_hp); }
    (void)_t2648;
    if (_t2648) {
        Str *_t2623 = Str_lit("Switch", 6ULL);
        (void)_t2623;
        ;
        return _t2623;
    }
    ;
    Bool _t2649; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t2649 = *_hp; free(_hp); }
    (void)_t2649;
    if (_t2649) {
        Str *_t2624 = Str_lit("Case", 4ULL);
        (void)_t2624;
        ;
        return _t2624;
    }
    ;
    Str *_t2650 = Str_lit("unknown", 7ULL);
    (void)_t2650;
    return _t2650;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_delete(Expr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2719 = 0;
    (void)_t2719;
    ExprData_delete(&self->data, &(Bool){_t2719});
    ;
    Bool _t2720 = 0;
    (void)_t2720;
    TilType_delete(&self->til_type, &(Bool){_t2720});
    ;
    Bool _t2721 = 0;
    (void)_t2721;
    Str_delete(&self->struct_name, &(Bool){_t2721});
    ;
    Bool _t2722 = 0;
    (void)_t2722;
    Bool_delete(&self->is_own_arg, &(Bool){_t2722});
    ;
    Bool _t2723 = 0;
    (void)_t2723;
    Bool_delete(&self->is_splat, &(Bool){_t2723});
    ;
    Bool _t2724 = 0;
    (void)_t2724;
    Bool_delete(&self->is_own_field, &(Bool){_t2724});
    ;
    Bool _t2725 = 0;
    (void)_t2725;
    Bool_delete(&self->is_ref_field, &(Bool){_t2725});
    ;
    Bool _t2726 = 0;
    (void)_t2726;
    Bool_delete(&self->is_ns_field, &(Bool){_t2726});
    ;
    Bool _t2727 = 0;
    (void)_t2727;
    Bool_delete(&self->is_ext, &(Bool){_t2727});
    ;
    Bool _t2728 = 0;
    (void)_t2728;
    Bool_delete(&self->is_core, &(Bool){_t2728});
    ;
    Bool _t2729 = 0;
    (void)_t2729;
    Bool_delete(&self->save_old_delete, &(Bool){_t2729});
    ;
    Bool _t2730 = 0;
    (void)_t2730;
    I32_delete(&self->total_struct_size, &(Bool){_t2730});
    ;
    Bool _t2731 = 0;
    (void)_t2731;
    I32_delete(&self->variadic_index, &(Bool){_t2731});
    ;
    Bool _t2732 = 0;
    (void)_t2732;
    U32_delete(&self->variadic_count, &(Bool){_t2732});
    ;
    Bool _t2733 = 0;
    (void)_t2733;
    I32_delete(&self->kwargs_index, &(Bool){_t2733});
    ;
    Bool _t2734 = 0;
    (void)_t2734;
    U32_delete(&self->kwargs_count, &(Bool){_t2734});
    ;
    Bool _t2735 = 0;
    (void)_t2735;
    Vec_delete(&self->children, &(Bool){_t2735});
    ;
    Bool _t2736 = 0;
    (void)_t2736;
    U32_delete(&self->line, &(Bool){_t2736});
    ;
    Bool _t2737 = 0;
    (void)_t2737;
    U32_delete(&self->col, &(Bool){_t2737});
    ;
    Bool _t2738 = 0;
    (void)_t2738;
    Str_delete(&self->path, &(Bool){_t2738});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

#include "til_core.c"
#include "til_array.c"
#include "til_map.c"
#include "til_set.c"
#include "til_str.c"
#include "til_vec.c"
#include "til_tuple.c"
#include "til_lexer.c"
#include "til_ast.c"
#include "til_til.c"

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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) { TilType_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) { Declaration_delete(val, arg2); return; }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) { ExprData_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) { Expr_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) { Mode_delete(val, arg2); return; }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) { TypeScope_delete(val, arg2); return; }
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) return (void *)TilType_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) return (void *)Declaration_clone(val);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "ExprData", 8ULL) == 0) return (void *)ExprData_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) return (void *)Expr_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Mode", 4ULL) == 0) return (void *)Mode_clone(val);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TypeScope", 9ULL) == 0) return (void *)TypeScope_clone(val);
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

