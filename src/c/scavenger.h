#pragma once

#include "../../bootstrap/modes.h"

// Remove top-level declarations and namespace methods not reachable
// from the program's entry points. needs_main: main. Otherwise: all
// top-level executable statements.
void scavenge(Expr *program, Mode *mode, Bool run_tests);

