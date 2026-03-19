#ifndef TIL_PARSER_H
#define TIL_PARSER_H

#include "../../bootstrap/modes.h"

Expr * parse(Vec * tokens, Str * path, Str * mode_out);

#endif
