#ifndef TIL_INTERPRETER_H
#define TIL_INTERPRETER_H

#include "ast.h"

// Interpret a parsed program. `mode` is the mode string (e.g. "cli").
// Returns 0 on success, non-zero on error.
int interpret(Expr *program, Str *mode, const char *path);

#endif
