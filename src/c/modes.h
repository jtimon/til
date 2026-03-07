#ifndef MODES_H
#define MODES_H

#include "aliases.h"

typedef struct {
    const char *name;
    Bool needs_main;
    Bool decls_only;
    const char *auto_import; // e.g. "gui" → loads modes/gui.til + modes/gui.c
} Mode;

static const Mode MODE_SCRIPT = {"script", 0, 0, NULL};
static const Mode MODE_CLI    = {"cli",    1, 1, NULL};
static const Mode MODE_GUI    = {"gui",    1, 1, "gui"};
static const Mode MODE_TEST   = {"test",   0, 1, NULL};

#endif
