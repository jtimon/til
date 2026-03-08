#ifndef TIL_DISPATCH_H
#define TIL_DISPATCH_H

#include "interpreter.h"

// Returns 1 if name matched an ext function, 0 if not.
// If matched, *result is set to the return value.
Bool ext_function_dispatch(Str *name, Scope *scope, Expr *e, Value *result);

// Dispatch enum method calls (both simple and payload enums).
// Returns 1 if handled, 0 if not an enum method.
Bool enum_method_dispatch(Str *method, Scope *scope, Expr *enum_def,
                         Str *enum_name, Expr *e,
                         Value *result);

// FFI: auto-discover C functions via dlsym, optionally compile user .c library
I32 ffi_init(Expr *program, const char *user_c_path, const char *ext_c_path, const char *link_flags);
void ffi_cleanup(void);

#endif
