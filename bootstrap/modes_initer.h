#pragma once
#include "modes_decls.h"

#include "modes_ast.h"

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
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Bool is_ext;
    Str *struct_name;
} TypeBinding;


TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U64 * TypeBinding_size(void);
