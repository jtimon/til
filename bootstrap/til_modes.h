#pragma once
#include "til_decls.h"

#include "til_str.h"

typedef struct Mode {
    Str name;
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_pure;
    Bool debug_prints;
} Mode;


Bool * Mode_eq(Mode * a, Mode * b);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
Mode * mode_resolve(Str * name);
Bool * mode_is_lib(Mode * m);
Bool * mode_is_lib_output(Mode * m);
