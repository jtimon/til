#ifndef TIL_PARSER_H
#define TIL_PARSER_H

#include "../../bootstrap/ast.h"

// Parse a token array into an AST. Returns the root body node.
// `path` is used for error messages. `mode_out` receives the mode name
// (e.g. "cli", "lib") if a mode declaration is found, or empty Str.
Expr *parse(Vec *tokens, Str *path, Str *mode_out);

// Returns the mode string from the last parse() call (or empty Str if none).
Str *parser_get_mode(void);

#endif
