#ifndef TIL_PRECOMP_H
#define TIL_PRECOMP_H

#include "../../bootstrap/ast.h"

// Evaluate macro calls at compile time and replace them with literals.
// Runs after type_check, before scavenge.
void precomp(Expr *program);

#endif
