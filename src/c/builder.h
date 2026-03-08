#ifndef TIL_BUILDER_H
#define TIL_BUILDER_H

#include "ast.h"
#include "modes.h"

// Generate C source code from a parsed program.
// Writes the generated C to `c_output_path`.
// Returns 0 on success, non-zero on error.
I32 build(Expr *program, const Mode *mode, Bool run_tests, const char *path, const char *c_output_path);

// Generate a C header file declaring the library's public interface.
I32 build_header(Expr *program, const char *h_path);

// Generate a .til FFI binding file for the library.
I32 build_til_binding(Expr *program, const char *til_path, const char *lib_name);

// Compile a generated C file to a binary using cc.
I32 compile_c(const char *c_path, const char *bin_path, const char *ext_c_path, const char *user_c_path, const char *link_flags);

// Compile a generated C file to shared (.so) and static (.a) libraries.
I32 compile_lib(const char *c_path, const char *lib_name, const char *ext_c_path, const char *user_c_path, const char *link_flags);

#endif
