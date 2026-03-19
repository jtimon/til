#pragma once

#include "../../bootstrap/modes.h"

// TypeBinding and TypeScope are defined in initer.til (generated into bootstrap headers)

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

// Move Vec buffer out (returns data pointer, zeroes Vec)
void *Vec_take(Vec *v);

