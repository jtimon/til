#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "til_core.h"
#include "til_array.h"
#include "til_set.h"
#include "til_str.h"
#include "til_vec.h"
#include "til_lexer.h"
#include "til_ast.h"
#include "til_til.h"

#include "ext.h"

Token * til_tokenize(Str *, Str *);
U32 til_tok_count(void);
Expr * til_parse(Token *, U32, Str *);
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
Mode * til_mode_test(void);
Mode * til_mode_pure(void);
Mode * til_mode_pura(void);
Str * til_mode_name(Mode *);
Str * til_mode_auto_import(Mode *);
Bool til_mode_is_lib(Mode *);
Bool til_mode_is_lib_output(Mode *);
TypeScope * tscope_new(TypeScope *);
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

Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

Bool * FuncType_eq(FuncType * self, FuncType * other);
FuncType * FuncType_clone(FuncType * self);
void FuncType_delete(FuncType * self, Bool * call_free);
U64 * FuncType_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U64 * FunctionDef_size(void);
U64 * U8_size(void);
Bool * U8_neq(U8 * a, U8 * b);
Str * I32_to_str(I32 * val);
U64 * I32_size(void);
Bool * I32_gt(I32 * a, I32 * b);
U64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_size(void);
Bool * U64_lt(U64 * a, U64 * b);
Bool * U64_gt(U64 * a, U64 * b);
Bool * U64_lte(U64 * a, U64 * b);
Bool * U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
U64 * I64_size(void);
Bool * I64_lt(I64 * a, I64 * b);
Bool * I64_gt(I64 * a, I64 * b);
Bool * I64_neq(I64 * a, I64 * b);
Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
I64 * Bool_cmp(Bool * a, Bool * b);
U64 * Bool_size(void);
void println(Array * parts);
Str * format(Array * parts);
void panic(Str * loc_str, Array * parts);
Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_rfind(Str * self, Str * needle);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
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
U64 * TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U64 * Token_size(void);
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
U64 * TilType_size(void);
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
ExprData * ExprData_clone(ExprData * self);
void ExprData_delete(ExprData * self, Bool * call_free);
U64 * ExprData_size(void);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U64 * Expr_size(void);
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

static I64 *_t3634;
static I64 *_t3635;
static I64 *_t3636;
static U64 *CAP_LIT;
static I64 *_t3637;
static I64 *_t3638;
static I64 *_t3639;
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

U64 *FuncType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FuncType);
    return r;
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

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
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

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
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
    Bool _t2206; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        Bool _t2189; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t2189 = *_hp; free(_hp); }
        (void)_t2189;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2189; return _r; }
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TilType_is_None(self); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        Bool _t2190; { Bool *_hp = (Bool *)TilType_is_None(other); _t2190 = *_hp; free(_hp); }
        (void)_t2190;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2190; return _r; }
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TilType_is_I64(self); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        Bool _t2191; { Bool *_hp = (Bool *)TilType_is_I64(other); _t2191 = *_hp; free(_hp); }
        (void)_t2191;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2191; return _r; }
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TilType_is_U8(self); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        Bool _t2192; { Bool *_hp = (Bool *)TilType_is_U8(other); _t2192 = *_hp; free(_hp); }
        (void)_t2192;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2192; return _r; }
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TilType_is_I16(self); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        Bool _t2193; { Bool *_hp = (Bool *)TilType_is_I16(other); _t2193 = *_hp; free(_hp); }
        (void)_t2193;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2193; return _r; }
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TilType_is_I32(self); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        Bool _t2194; { Bool *_hp = (Bool *)TilType_is_I32(other); _t2194 = *_hp; free(_hp); }
        (void)_t2194;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2194; return _r; }
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TilType_is_U32(self); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        Bool _t2195; { Bool *_hp = (Bool *)TilType_is_U32(other); _t2195 = *_hp; free(_hp); }
        (void)_t2195;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2195; return _r; }
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TilType_is_U64(self); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        Bool _t2196; { Bool *_hp = (Bool *)TilType_is_U64(other); _t2196 = *_hp; free(_hp); }
        (void)_t2196;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2196; return _r; }
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TilType_is_F32(self); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        Bool _t2197; { Bool *_hp = (Bool *)TilType_is_F32(other); _t2197 = *_hp; free(_hp); }
        (void)_t2197;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2197; return _r; }
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        Bool _t2198; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t2198 = *_hp; free(_hp); }
        (void)_t2198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2198; return _r; }
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        Bool _t2199; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t2199 = *_hp; free(_hp); }
        (void)_t2199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2199; return _r; }
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        Bool _t2200; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t2200 = *_hp; free(_hp); }
        (void)_t2200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2200; return _r; }
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        Bool _t2201; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t2201 = *_hp; free(_hp); }
        (void)_t2201;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2201; return _r; }
    }
    ;
    Bool _t2219; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t2219 = *_hp; free(_hp); }
    (void)_t2219;
    if (_t2219) {
        Bool _t2202; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t2202 = *_hp; free(_hp); }
        (void)_t2202;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2202; return _r; }
    }
    ;
    Bool _t2220; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        Bool _t2203; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t2203 = *_hp; free(_hp); }
        (void)_t2203;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2203; return _r; }
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        Bool _t2204; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t2204 = *_hp; free(_hp); }
        (void)_t2204;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2204; return _r; }
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        Bool _t2205; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t2205 = *_hp; free(_hp); }
        (void)_t2205;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2205; return _r; }
    }
    ;
    Bool _t2223 = 0;
    (void)_t2223;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2223; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t2224; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        ;
        return TilType_None();
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t2236; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    if (_t2236) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t2237; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    if (_t2237) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t2238; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t2238 = *_hp; free(_hp); }
    (void)_t2238;
    if (_t2238) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t2239; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t2239 = *_hp; free(_hp); }
    (void)_t2239;
    if (_t2239) {
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

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2320 = 0;
    (void)_t2320;
    Str_delete(&self->name, &(Bool){_t2320});
    ;
    Bool _t2321 = 0;
    (void)_t2321;
    Str_delete(&self->explicit_type, &(Bool){_t2321});
    ;
    Bool _t2322 = 0;
    (void)_t2322;
    Bool_delete(&self->is_mut, &(Bool){_t2322});
    ;
    Bool _t2323 = 0;
    (void)_t2323;
    Bool_delete(&self->is_namespace, &(Bool){_t2323});
    ;
    Bool _t2324 = 0;
    (void)_t2324;
    Bool_delete(&self->is_ref, &(Bool){_t2324});
    ;
    Bool _t2325 = 0;
    (void)_t2325;
    Bool_delete(&self->is_own, &(Bool){_t2325});
    ;
    Bool _t2326 = 0;
    (void)_t2326;
    I32_delete(&self->field_offset, &(Bool){_t2326});
    ;
    Bool _t2327 = 0;
    (void)_t2327;
    I32_delete(&self->field_size, &(Bool){_t2327});
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
ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t2457; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    if (_t2457) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t2458; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2458 = *_hp; free(_hp); }
    (void)_t2458;
    if (_t2458) {
        Str *_t2435 = ExprData_get_LiteralStr(self);
        (void)_t2435;
        ExprData *_t2436 = ExprData_LiteralStr(_t2435);
        (void)_t2436;
        Str_delete(_t2435, &(Bool){1});
        ;
        return _t2436;
    }
    ;
    Bool _t2459; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2459 = *_hp; free(_hp); }
    (void)_t2459;
    if (_t2459) {
        Str *_t2437 = ExprData_get_LiteralNum(self);
        (void)_t2437;
        ExprData *_t2438 = ExprData_LiteralNum(_t2437);
        (void)_t2438;
        Str_delete(_t2437, &(Bool){1});
        ;
        return _t2438;
    }
    ;
    Bool _t2460; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2460 = *_hp; free(_hp); }
    (void)_t2460;
    if (_t2460) {
        Str *_t2439 = ExprData_get_LiteralBool(self);
        (void)_t2439;
        ExprData *_t2440 = ExprData_LiteralBool(_t2439);
        (void)_t2440;
        Str_delete(_t2439, &(Bool){1});
        ;
        return _t2440;
    }
    ;
    Bool _t2461; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2461 = *_hp; free(_hp); }
    (void)_t2461;
    if (_t2461) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t2462; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2462 = *_hp; free(_hp); }
    (void)_t2462;
    if (_t2462) {
        Str *_t2441 = ExprData_get_Ident(self);
        (void)_t2441;
        ExprData *_t2442 = ExprData_Ident(_t2441);
        (void)_t2442;
        Str_delete(_t2441, &(Bool){1});
        ;
        return _t2442;
    }
    ;
    Bool _t2463; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2463 = *_hp; free(_hp); }
    (void)_t2463;
    if (_t2463) {
        Declaration *_t2443 = ExprData_get_Decl(self);
        (void)_t2443;
        ExprData *_t2444 = ExprData_Decl(_t2443);
        (void)_t2444;
        Declaration_delete(_t2443, &(Bool){1});
        ;
        return _t2444;
    }
    ;
    Bool _t2464; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2464 = *_hp; free(_hp); }
    (void)_t2464;
    if (_t2464) {
        Str *_t2445 = ExprData_get_Assign(self);
        (void)_t2445;
        ExprData *_t2446 = ExprData_Assign(_t2445);
        (void)_t2446;
        Str_delete(_t2445, &(Bool){1});
        ;
        return _t2446;
    }
    ;
    Bool _t2465; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2465 = *_hp; free(_hp); }
    (void)_t2465;
    if (_t2465) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t2466; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2466 = *_hp; free(_hp); }
    (void)_t2466;
    if (_t2466) {
        FunctionDef *_t2447 = ExprData_get_FuncDef(self);
        (void)_t2447;
        ExprData *_t2448 = ExprData_FuncDef(_t2447);
        (void)_t2448;
        FunctionDef_delete(_t2447, &(Bool){1});
        ;
        return _t2448;
    }
    ;
    Bool _t2467; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2467 = *_hp; free(_hp); }
    (void)_t2467;
    if (_t2467) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t2468; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2468 = *_hp; free(_hp); }
    (void)_t2468;
    if (_t2468) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t2469; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    if (_t2469) {
        Str *_t2449 = ExprData_get_FieldAccess(self);
        (void)_t2449;
        ExprData *_t2450 = ExprData_FieldAccess(_t2449);
        (void)_t2450;
        Str_delete(_t2449, &(Bool){1});
        ;
        return _t2450;
    }
    ;
    Bool _t2470; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2470 = *_hp; free(_hp); }
    (void)_t2470;
    if (_t2470) {
        Str *_t2451 = ExprData_get_FieldAssign(self);
        (void)_t2451;
        ExprData *_t2452 = ExprData_FieldAssign(_t2451);
        (void)_t2452;
        Str_delete(_t2451, &(Bool){1});
        ;
        return _t2452;
    }
    ;
    Bool _t2471; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2471 = *_hp; free(_hp); }
    (void)_t2471;
    if (_t2471) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t2472; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2472 = *_hp; free(_hp); }
    (void)_t2472;
    if (_t2472) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t2473; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2473 = *_hp; free(_hp); }
    (void)_t2473;
    if (_t2473) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t2474; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2474 = *_hp; free(_hp); }
    (void)_t2474;
    if (_t2474) {
        Str *_t2453 = ExprData_get_ForIn(self);
        (void)_t2453;
        ExprData *_t2454 = ExprData_ForIn(_t2453);
        (void)_t2454;
        Str_delete(_t2453, &(Bool){1});
        ;
        return _t2454;
    }
    ;
    Bool _t2475; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2475 = *_hp; free(_hp); }
    (void)_t2475;
    if (_t2475) {
        Str *_t2455 = ExprData_get_NamedArg(self);
        (void)_t2455;
        ExprData *_t2456 = ExprData_NamedArg(_t2455);
        (void)_t2456;
        Str_delete(_t2455, &(Bool){1});
        ;
        return _t2456;
    }
    ;
    Bool _t2476; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2476 = *_hp; free(_hp); }
    (void)_t2476;
    if (_t2476) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t2477; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2477 = *_hp; free(_hp); }
    (void)_t2477;
    if (_t2477) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t2478; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2478 = *_hp; free(_hp); }
    (void)_t2478;
    if (_t2478) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t2479; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2479 = *_hp; free(_hp); }
    (void)_t2479;
    if (_t2479) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t2480; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2480 = *_hp; free(_hp); }
    (void)_t2480;
    if (_t2480) {
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

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_delete(Expr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2710 = 0;
    (void)_t2710;
    ExprData_delete(&self->data, &(Bool){_t2710});
    ;
    Bool _t2711 = 0;
    (void)_t2711;
    TilType_delete(&self->til_type, &(Bool){_t2711});
    ;
    Bool _t2712 = 0;
    (void)_t2712;
    Str_delete(&self->struct_name, &(Bool){_t2712});
    ;
    Bool _t2713 = 0;
    (void)_t2713;
    Bool_delete(&self->is_own_arg, &(Bool){_t2713});
    ;
    Bool _t2714 = 0;
    (void)_t2714;
    Bool_delete(&self->is_splat, &(Bool){_t2714});
    ;
    Bool _t2715 = 0;
    (void)_t2715;
    Bool_delete(&self->is_own_field, &(Bool){_t2715});
    ;
    Bool _t2716 = 0;
    (void)_t2716;
    Bool_delete(&self->is_ref_field, &(Bool){_t2716});
    ;
    Bool _t2717 = 0;
    (void)_t2717;
    Bool_delete(&self->is_ns_field, &(Bool){_t2717});
    ;
    Bool _t2718 = 0;
    (void)_t2718;
    Bool_delete(&self->is_ext, &(Bool){_t2718});
    ;
    Bool _t2719 = 0;
    (void)_t2719;
    Bool_delete(&self->is_core, &(Bool){_t2719});
    ;
    Bool _t2720 = 0;
    (void)_t2720;
    Bool_delete(&self->save_old_delete, &(Bool){_t2720});
    ;
    Bool _t2721 = 0;
    (void)_t2721;
    I32_delete(&self->total_struct_size, &(Bool){_t2721});
    ;
    Bool _t2722 = 0;
    (void)_t2722;
    I32_delete(&self->variadic_index, &(Bool){_t2722});
    ;
    Bool _t2723 = 0;
    (void)_t2723;
    U32_delete(&self->variadic_count, &(Bool){_t2723});
    ;
    Bool _t2724 = 0;
    (void)_t2724;
    I32_delete(&self->kwargs_index, &(Bool){_t2724});
    ;
    Bool _t2725 = 0;
    (void)_t2725;
    U32_delete(&self->kwargs_count, &(Bool){_t2725});
    ;
    Bool _t2726 = 0;
    (void)_t2726;
    Vec_delete(&self->children, &(Bool){_t2726});
    ;
    Bool _t2727 = 0;
    (void)_t2727;
    U32_delete(&self->line, &(Bool){_t2727});
    ;
    Bool _t2728 = 0;
    (void)_t2728;
    U32_delete(&self->col, &(Bool){_t2728});
    ;
    Bool _t2729 = 0;
    (void)_t2729;
    Str_delete(&self->path, &(Bool){_t2729});
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
#include "til_set.c"
#include "til_str.c"
#include "til_vec.c"
#include "til_lexer.c"
#include "til_ast.c"
#include "til_til.c"

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) { FuncType_delete(val, arg2); return; }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) { FunctionDef_delete(val, arg2); return; }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) { Range_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) { Array_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) { Set_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Str_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) { Vec_delete(val, arg2); return; }
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) return (void *)FuncType_clone(val);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) return (void *)FunctionDef_clone(val);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void *)Array_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void *)Set_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void *)Vec_clone(val);
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

