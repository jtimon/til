#ifndef TIL_BUILDER_H
#define TIL_BUILDER_H

#include "ast.h"
#include "modes.h"

// Generate C source code from a parsed program.
// Writes the generated C to `c_output_path`.
// Returns 0 on success, non-zero on error.
I32 build(Expr *program, const Mode *mode, Bool run_tests, Str *path, Str *c_output_path);

// Generate a C header file declaring the library's public interface.
I32 build_header(Expr *program, Str *h_path);

// Generate a .til FFI binding file for the library.
I32 build_til_binding(Expr *program, Str *til_path, Str *lib_name);

// Generate a Python ctypes binding file for the library.
I32 build_python_binding(Expr *program, Str *py_path, Str *lib_name);

// Compile a generated C file to a binary using cc.
I32 compile_c(Str *c_path, Str *bin_path, Str *ext_c_path, Str *user_c_path, Str *link_flags);

// Compile a generated C file to shared (.so) and static (.a) libraries.
I32 compile_lib(Str *c_path, Str *lib_name, Str *ext_c_path, Str *user_c_path, Str *link_flags);

#endif
