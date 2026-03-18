#pragma once
#include "modes_decls.h"

#include "modes_str.h"
#include "modes_vec.h"
#include "modes_map.h"

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


struct FuncType {
    FuncType_tag tag;
};

typedef struct FunctionDef {
    FuncType func_type;
    Vec param_names;
    Vec param_types;
    Vec param_muts;
    Vec param_owns;
    Vec param_shallows;
    Vec param_fn_sigs;
    U32 nparam;
    Map param_defaults;
    Str return_type;
    I32 variadic_index;
    I32 kwargs_index;
    Bool return_is_ref;
    Bool return_is_shallow;
} FunctionDef;


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
