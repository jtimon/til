#ifndef TIL_INITER_H
#define TIL_INITER_H

#include "ast.h"

// --- Type scope (tracks variable types across phases) ---

typedef struct {
    const char *name;
    TilType type;
    int is_proc; // -1 = not a function, 0 = func, 1 = proc
    int is_mut;
    int line;
    int col;
    int is_param; // 1 if this is a function parameter
    Expr *struct_def; // non-NULL if this is a struct type definition
    Expr *func_def;   // non-NULL if this is a func/proc definition
    int is_builtin;   // 1 if this is a builtin type (I64, Str, Bool, etc.)
    const char *struct_name; // for variables of struct type: which struct
} TypeBinding;

typedef struct TypeScope TypeScope;
struct TypeScope {
    TypeBinding *bindings;
    int len;
    int cap;
    TypeScope *parent;
};

// Scope operations
TypeScope *tscope_new(TypeScope *parent);
void tscope_free(TypeScope *s);
void tscope_set(TypeScope *s, const char *name, TilType type, int is_proc, int is_mut, int line, int col, int is_param);
TilType tscope_get(TypeScope *s, const char *name);
int tscope_is_proc(TypeScope *s, const char *name);
TypeBinding *tscope_find(TypeScope *s, const char *name);
Expr *tscope_get_struct(TypeScope *s, const char *name);
int tscope_is_mut(TypeScope *s, const char *name);

// Pre-scan top-level declarations (structs and functions) into scope.
// Returns number of errors.
int init_declarations(Expr *program, TypeScope *scope, const char *path);

#endif
