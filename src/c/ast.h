#ifndef TIL_AST_H
#define TIL_AST_H

#include "../../bootstrap/lexer.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// --- TilType (struct wrapping tag, matches til codegen) ---

typedef enum {
    TilType_TAG_Unknown,
    TilType_TAG_None,
    TilType_TAG_I64,
    TilType_TAG_U8,
    TilType_TAG_I16,
    TilType_TAG_I32,
    TilType_TAG_U32,
    TilType_TAG_U64,
    TilType_TAG_F32,
    TilType_TAG_Bool,
    TilType_TAG_Struct,
    TilType_TAG_StructDef,
    TilType_TAG_Enum,
    TilType_TAG_EnumDef,
    TilType_TAG_FuncDef,
    TilType_TAG_FuncPtr,
    TilType_TAG_Dynamic,
} TilType_tag;

typedef struct {
    TilType_tag tag;
} TilType;

// --- ExprData tag enum ---

typedef enum {
    ExprData_TAG_Body,
    ExprData_TAG_LiteralStr,
    ExprData_TAG_LiteralNum,
    ExprData_TAG_LiteralBool,
    ExprData_TAG_LiteralNull,
    ExprData_TAG_Ident,
    ExprData_TAG_Decl,
    ExprData_TAG_Assign,
    ExprData_TAG_FCall,
    ExprData_TAG_FuncDef,
    ExprData_TAG_StructDef,
    ExprData_TAG_EnumDef,
    ExprData_TAG_FieldAccess,
    ExprData_TAG_FieldAssign,
    ExprData_TAG_Return,
    ExprData_TAG_If,
    ExprData_TAG_While,
    ExprData_TAG_ForIn,
    ExprData_TAG_NamedArg,
    ExprData_TAG_Break,
    ExprData_TAG_Continue,
    ExprData_TAG_MapLit,
    ExprData_TAG_SetLit,
    ExprData_TAG_Switch,
    ExprData_TAG_Case,
} ExprData_tag;

// --- Declaration ---

typedef struct Expr Expr;

typedef struct {
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

// --- ExprData (tagged union) ---

typedef struct {
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
} ExprData;

// --- Expr ---

struct Expr {
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
};

// --- Inline-Str convenience macros ---

#define STR_FIELD(expr, field) (&(expr)->data.data.field)
#define STR_SNAME(expr)       (&(expr)->struct_name)
#define STR_PATH(expr)        (&(expr)->path)
#define DECL_NAME(expr)       (&(expr)->data.data.Decl.name)
#define DECL_ETYPE(expr)      (&(expr)->data.data.Decl.explicit_type)
#define FDEF_RTYPE(expr)      (&(expr)->data.data.FuncDef.return_type)

#define VEC_SET(v)   ((v).count > 0)

// --- Functions matching ast.til generated signatures ---

Str *til_type_name_c(TilType *t);
Str *node_name(ExprData *data);
Str *func_type_name(FuncType *ft);
void ast_print(Expr *e, U32 indent);
Bool *enum_has_payloads(Expr *enum_def);
I32 *enum_variant_tag(Expr *enum_def, Str *variant_name);
Str *enum_variant_type(Expr *enum_def, I32 tag);

// --- Auto-generated clone/delete (matching what builder generates from initer) ---

TilType *TilType_clone(TilType *self);
void TilType_delete(TilType *self, Bool *call_free);
Declaration *Declaration_clone(Declaration *self);
void Declaration_delete(Declaration *self, Bool *call_free);
ExprData *ExprData_clone(ExprData *self);
void ExprData_delete(ExprData *self, Bool *call_free);
Expr *Expr_clone(Expr *self);
void Expr_delete(Expr *self, Bool *call_free);

// --- Expr namespace methods (matching ast.til) ---

Expr *Expr_new(ExprData *data, U32 line, U32 col, Str *path);
void Expr_add_child(Expr *self, Expr *child);
void Expr_error(Expr *self, Str *msg);
void Expr_todo_error(Expr *self, Str *msg);
void Expr_lang_error(Expr *self, Str *msg);

Expr *Expr_child(Expr *parent, I64 *i);
I64 *Expr_child_count(Expr *parent);
#define expr_child(e, i) ((Expr *)Vec_get(&(e)->children, &(U64){(U64)(i)}))

#ifndef TIL_CAP_LIT
#define TIL_CAP_LIT ULLONG_MAX
#endif
#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush(void);
Str *U32_to_str(U32 *val);
Bool *U64_lt(U64 *a, U64 *b);
Bool *U64_gt(U64 *a, U64 *b);
Bool *TilType_eq(TilType *, TilType *);
Str *TilType_to_str(TilType *self);
U64 *TilType_size(void);
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
Bool *Declaration_eq(Declaration *a, Declaration *b);
Str *Declaration_to_str(Declaration *self);
U64 *Declaration_size(void);
Bool *ExprData_eq(ExprData *, ExprData *);
Str *ExprData_to_str(ExprData *self);
U64 *ExprData_size(void);
Bool *ExprData_is_Body(ExprData *);
ExprData *ExprData_Body();
Bool *ExprData_is_LiteralStr(ExprData *);
ExprData *ExprData_LiteralStr(Str *);
Str *ExprData_get_LiteralStr(ExprData *);
Bool *ExprData_is_LiteralNum(ExprData *);
ExprData *ExprData_LiteralNum(Str *);
Str *ExprData_get_LiteralNum(ExprData *);
Bool *ExprData_is_LiteralBool(ExprData *);
ExprData *ExprData_LiteralBool(Str *);
Str *ExprData_get_LiteralBool(ExprData *);
Bool *ExprData_is_LiteralNull(ExprData *);
ExprData *ExprData_LiteralNull();
Bool *ExprData_is_Ident(ExprData *);
ExprData *ExprData_Ident(Str *);
Str *ExprData_get_Ident(ExprData *);
Bool *ExprData_is_Decl(ExprData *);
ExprData *ExprData_Decl(Declaration *);
Declaration *ExprData_get_Decl(ExprData *);
Bool *ExprData_is_Assign(ExprData *);
ExprData *ExprData_Assign(Str *);
Str *ExprData_get_Assign(ExprData *);
Bool *ExprData_is_FCall(ExprData *);
ExprData *ExprData_FCall();
Bool *ExprData_is_FuncDef(ExprData *);
ExprData *ExprData_FuncDef(FunctionDef *);
FunctionDef *ExprData_get_FuncDef(ExprData *);
Bool *ExprData_is_StructDef(ExprData *);
ExprData *ExprData_StructDef();
Bool *ExprData_is_EnumDef(ExprData *);
ExprData *ExprData_EnumDef();
Bool *ExprData_is_FieldAccess(ExprData *);
ExprData *ExprData_FieldAccess(Str *);
Str *ExprData_get_FieldAccess(ExprData *);
Bool *ExprData_is_FieldAssign(ExprData *);
ExprData *ExprData_FieldAssign(Str *);
Str *ExprData_get_FieldAssign(ExprData *);
Bool *ExprData_is_Return(ExprData *);
ExprData *ExprData_Return();
Bool *ExprData_is_If(ExprData *);
ExprData *ExprData_If();
Bool *ExprData_is_While(ExprData *);
ExprData *ExprData_While();
Bool *ExprData_is_ForIn(ExprData *);
ExprData *ExprData_ForIn(Str *);
Str *ExprData_get_ForIn(ExprData *);
Bool *ExprData_is_NamedArg(ExprData *);
ExprData *ExprData_NamedArg(Str *);
Str *ExprData_get_NamedArg(ExprData *);
Bool *ExprData_is_Break(ExprData *);
ExprData *ExprData_Break();
Bool *ExprData_is_Continue(ExprData *);
ExprData *ExprData_Continue();
Bool *ExprData_is_MapLit(ExprData *);
ExprData *ExprData_MapLit();
Bool *ExprData_is_SetLit(ExprData *);
ExprData *ExprData_SetLit();
Bool *ExprData_is_Switch(ExprData *);
ExprData *ExprData_Switch();
Bool *ExprData_is_Case(ExprData *);
ExprData *ExprData_Case();
U64 *Expr_size(void);
FuncType *FuncType_Func();
FuncType *FuncType_Proc();
FuncType *FuncType_Test();
FuncType *FuncType_Macro();
FuncType *FuncType_ExtFunc();
FuncType *FuncType_ExtProc();
void *Vec_take(Vec *v);

#endif
