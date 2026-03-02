#ifndef TIL_CCODEGEN_H
#define TIL_CCODEGEN_H

#include "ast.h"

// Generate C source code from a parsed program.
// Writes the generated C to `c_output_path`.
// Returns 0 on success, non-zero on error.
int codegen_c(Expr *program, const char *mode, const char *path, const char *c_output_path);

// Compile a generated C file to a binary using cc.
// Returns 0 on success, non-zero on error.
int compile_c(const char *c_path, const char *bin_path);

#endif
