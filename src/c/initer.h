#ifndef TIL_INITER_H
#define TIL_INITER_H

#include "ast.h"

// --- Type scope (tracks variable types across phases) ---

typedef struct {
    Str *name;
    TilType type;
    I32 is_proc; // -1 = not a function, 0 = func, 1 = proc
    Bool is_mut;
    U32 line;
    U32 col;
    Bool is_param; // 1 if this is a function parameter
    Bool is_own;   // 1 if this is an 'own' parameter
    Bool is_ref;   // 1 if this is a 'ref' declaration (borrowed, no delete)
    Expr *struct_def; // non-NULL if this is a struct type definition
    Expr *func_def;   // non-NULL if this is a func/proc definition
    Bool is_builtin;   // 1 if this is a builtin type (I64, Str, Bool, etc.)
    Bool is_ext;       // 1 if this is an ext_struct
    Str *struct_name; // for variables of struct type: which struct
} TypeBinding;

typedef struct TypeScope TypeScope;
struct TypeScope {
    Map bindings; // Str* name → TypeBinding
    TypeScope *parent;
};

// Scope operations
TypeScope *tscope_new(TypeScope *parent);
void tscope_free(TypeScope *s);
void tscope_set(TypeScope *s, Str *name, TilType type, I32 is_proc, Bool is_mut, U32 line, U32 col, Bool is_param, Bool is_own);
TilType tscope_get(TypeScope *s, Str *name);
I32 tscope_is_proc(TypeScope *s, Str *name);
TypeBinding *tscope_find(TypeScope *s, Str *name);
Expr *tscope_get_struct(TypeScope *s, Str *name);
Bool tscope_is_mut(TypeScope *s, Str *name);

// Pre-scan top-level declarations (structs and functions) into scope.
// Returns number of errors.
I32 init_declarations(Expr *program, TypeScope *scope);

#endif
