#ifndef MODES_H
#define MODES_H

#include "../../bootstrap/ast.h"
#include "pre70.h"

typedef struct {
    Str name;
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_pure;
    Bool debug_prints;
} Mode;

#define STR_LIT(s) ((Str){.c_str = (U8*)(s), .count = sizeof(s) - 1, .cap = CAP_LIT})
#define STR_EMPTY  ((Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT})

extern Mode MODE_SCRIPT, MODE_CLI, MODE_GUI, MODE_TEST;
extern Mode MODE_PURE, MODE_PURA, MODE_LIB, MODE_LIBA;

Bool mode_is_lib(const Mode *m);
Bool mode_is_lib_output(const Mode *m);

#endif
