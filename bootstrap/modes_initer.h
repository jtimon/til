#pragma once
#include "modes_decls.h"

#include "modes_ast.h"
#include "modes_map.h"

typedef struct TypeBinding {
    Str *name;
    TilType type;
    I32 is_proc;
    Bool is_mut;
    U32 line;
    U32 col;
    Bool is_param;
    Bool is_own;
    Bool is_ref;
    Bool is_alias;
    Bool is_type_alias;
    Str *alias_target;
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Bool is_ext;
    Str *struct_name;
} TypeBinding;


typedef struct TypeScope {
    Map bindings;
    TypeScope *parent;
} TypeScope;


TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U64 * TypeBinding_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
