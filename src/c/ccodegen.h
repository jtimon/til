#ifndef TIL_CCODEGEN_H
#define TIL_CCODEGEN_H

#include "ast.h"

// Generate C source code from a parsed program.
// Writes the generated C to `c_output_path`.
// Returns 0 on success, non-zero on error.
I32 codegen_c(Expr *program, Str *mode, const char *path, const char *c_output_path);

// Compile a generated C file to a binary using cc.
// Returns 0 on success, non-zero on error.
I32 compile_c(const char *c_path, const char *bin_path, const char *ext_c_path, const char *user_c_path);

#endif
