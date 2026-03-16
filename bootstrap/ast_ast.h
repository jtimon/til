#pragma once
#include "ast_decls.h"

#include "ast_str.h"
#include "ast_core.h"
#include "ast_vec.h"

struct TilType {
    TilType_tag tag;
};

typedef struct Declaration {
    Str name;
    Str explicit_type;
    Bool is_mut;
    Bool is_namespace;
    Bool is_ref;
    Bool is_own;
    I32 field_offset;
    I32 field_size;
    Expr *field_struct_def;
    Expr *fn_sig;
} Declaration;


struct ExprData {
    ExprData_tag tag;
    union {
        Str LiteralStr;
        Str LiteralNum;
        Str LiteralBool;
        Str Ident;
        Declaration Decl;
        Str Assign;
        FunctionDef FuncDef;
        Str FieldAccess;
        Str FieldAssign;
        Str ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    ExprData data;
    TilType til_type;
    Str struct_name;
    Bool is_own_arg;
    Bool is_splat;
    Bool is_own_field;
    Bool is_ref_field;
    Bool is_ns_field;
    Bool is_ext;
    Bool is_core;
    Bool save_old_delete;
    I32 total_struct_size;
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Expr *fn_sig;
    Vec children;
    U32 line;
    U32 col;
    Str path;
} Expr;


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
