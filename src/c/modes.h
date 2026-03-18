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

Mode *mode_resolve(Str *name);
Bool mode_eq(Mode *a, Mode *b);
Mode *mode_none(void);
Mode *mode_script(void);
Mode *mode_cli(void);
Mode *mode_gui(void);
Mode *mode_test(void);
Mode *mode_pure(void);
Mode *mode_pura(void);
Mode *mode_lib(void);
Mode *mode_liba(void);
Str *mode_name(Mode *m);
Str *mode_auto_import(Mode *m);
Bool mode_is_lib(Mode *m);
Bool mode_is_lib_output(Mode *m);

#endif
