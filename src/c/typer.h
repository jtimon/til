#pragma once

#include "initer.h"

// Run type inference and type checking on the AST (in-place).
// Scope should be pre-populated by init_declarations.
// Returns 0 on success, non-zero if type errors were found.
I32 type_check(Expr *program, TypeScope *scope, Mode *mode);

