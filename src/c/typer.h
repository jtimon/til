#ifndef TIL_TYPER_H
#define TIL_TYPER_H

#include "ast.h"

// Run type inference and type checking on the AST (in-place).
// Returns 0 on success, non-zero if type errors were found.
int type_check(Expr *program, const char *path);

#endif
