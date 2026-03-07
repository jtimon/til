#ifndef TIL_PARSER_H
#define TIL_PARSER_H

#include "lexer.h"
#include "ast.h"
#include "vec.h"

// Parse a token array into an AST. Returns the root body node.
// `path` is used for error messages. `mode_out` receives the mode name
// (e.g. "cli", "lib") if a mode declaration is found, or NULL.
Expr *parse(Token *tokens, I32 count, const char *path, Str **mode_out);

#endif
