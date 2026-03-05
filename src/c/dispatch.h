#ifndef TIL_DISPATCH_H
#define TIL_DISPATCH_H

#include "interpreter.h"

// Returns 1 if name matched an ext function, 0 if not.
// If matched, *result is set to the return value.
int ext_function_dispatch(Str *name, Scope *scope, Expr *e, const char *path, Value *result);

// Dispatch enum method calls (both simple and payload enums).
// Returns 1 if handled, 0 if not an enum method.
int enum_method_dispatch(Str *method, Scope *scope, Expr *enum_def,
                         Str *enum_name, Expr *e, const char *path,
                         Value *result);

// FFI: load user .c as shared library, register function pointers
int ffi_init(Expr *program, const char *user_c_path, const char *ext_c_path);
void ffi_cleanup(void);

#endif
