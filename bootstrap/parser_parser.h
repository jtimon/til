#pragma once
#include "parser_decls.h"

#include "parser_vec.h"
#include "parser_str.h"

typedef struct Parser {
    Vec tokens;
    U32 count;
    U32 pos;
    Str path;
} Parser;


Parser * Parser_clone(Parser * self);
void Parser_delete(Parser * self, Bool * call_free);
U64 * Parser_size(void);
Token * peek(Parser * p);
Token * advance(Parser * p);
Bool check(Parser * p, TokenType * type);
Token * expect_token(Parser * p, TokenType * type);
Str * expect_text(Parser * p, TokenType * type);
U32 * peek_line(Parser * p);
U32 * peek_col(Parser * p);
Expr * parse_fn_signature(Parser * p, U32 * line, U32 * col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 * call_line, U32 * call_col);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool * is_mut, Bool * is_own);
Expr * parse_statement(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
