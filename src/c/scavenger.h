#ifndef TIL_SCAVENGER_H
#define TIL_SCAVENGER_H

#include "ast.h"

// Remove top-level declarations and namespace methods not reachable
// from the program's entry points. CLI mode: main. Script mode: all
// top-level executable statements.
void scavenge(Expr *program, Str *mode);

#endif
