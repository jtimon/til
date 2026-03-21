#pragma once

#include "../../boot/modes.h"

// Evaluate macro calls at compile time and replace them with literals.
// Runs after type_check, before scavenge.
void precomp(Expr *program);

