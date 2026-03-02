#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Parser state ---

typedef struct {
    Token *tokens;
    int count;
    int pos;
    const char *path;
} Parser;

static Token *peek(Parser *p) {
    return &p->tokens[p->pos];
}

static Token *advance(Parser *p) {
    Token *t = &p->tokens[p->pos];
    if (t->type != TOK_EOF) p->pos++;
    return t;
}

static int check(Parser *p, TokenType type) {
    return peek(p)->type == type;
}

static Token *expect(Parser *p, TokenType type) {
    Token *t = peek(p);
    if (t->type != type) {
        fprintf(stderr, "%s:%d:%d: parse error: expected '%s', found '%.*s'\n",
                p->path, t->line, t->col, tok_name(type), t->len, t->start);
        exit(1);
    }
    return advance(p);
}

// Extract a null-terminated string from a token. Uses malloc.
static const char *tok_str(Token *t) {
    char *s = malloc(t->len + 1);
    memcpy(s, t->start, t->len);
    s[t->len] = '\0';
    return s;
}

// --- Forward declarations ---

static Expr *parse_statement(Parser *p);
static Expr *parse_expression(Parser *p);

// --- Parsing functions ---

// parse_block: expects '{' already consumed, reads statements until '}'
static Expr *parse_block(Parser *p) {
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col);
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        expr_add_child(body, parse_statement(p));
    }
    expect(p, TOK_RBRACE);
    return body;
}

// parse_func_def: current token is func/proc/etc
static Expr *parse_func_def(Parser *p) {
    Token *kw = advance(p); // consume func/proc/etc
    FuncType ft;
    switch (kw->type) {
    case TOK_FUNC:     ft = FUNC_FUNC;     break;
    case TOK_PROC:     ft = FUNC_PROC;     break;
    case TOK_MACRO:    ft = FUNC_MACRO;    break;
    case TOK_EXT_FUNC: ft = FUNC_EXT_FUNC; break;
    case TOK_EXT_PROC: ft = FUNC_EXT_PROC; break;
    default:
        fprintf(stderr, "%s:%d:%d: parse error: expected function keyword\n",
                p->path, kw->line, kw->col);
        exit(1);
    }

    expect(p, TOK_LPAREN);
    // TODO: parse arguments
    expect(p, TOK_RPAREN);

    // TODO: parse 'returns' and 'throws' clauses

    Expr *def = expr_new(NODE_FUNC_DEF, kw->line, kw->col);
    def->data.func_def.func_type = ft;

    expect(p, TOK_LBRACE);
    expr_add_child(def, parse_block(p));

    return def;
}

// parse_call: identifier already consumed, current token is '('
static Expr *parse_call(Parser *p, const char *name, int line, int col) {
    advance(p); // consume '('

    Expr *call = expr_new(NODE_FCALL, line, col);

    // first child is the callee identifier
    Expr *callee = expr_new(NODE_IDENT, line, col);
    callee->data.str_val = name;
    expr_add_child(call, callee);

    // parse arguments
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        expr_add_child(call, parse_expression(p));
        if (check(p, TOK_COMMA)) advance(p); // skip comma between args
    }
    expect(p, TOK_RPAREN);

    return call;
}

// parse_expression: for now handles literals, identifiers, and calls
static Expr *parse_expression(Parser *p) {
    Token *t = peek(p);

    if (t->type == TOK_STRING) {
        advance(p);
        Expr *e = expr_new(NODE_LITERAL_STR, t->line, t->col);
        e->data.str_val = tok_str(t);
        return e;
    }

    if (t->type == TOK_NUMBER) {
        advance(p);
        Expr *e = expr_new(NODE_LITERAL_NUM, t->line, t->col);
        e->data.str_val = tok_str(t);
        return e;
    }

    if (t->type == TOK_TRUE || t->type == TOK_FALSE) {
        advance(p);
        Expr *e = expr_new(NODE_LITERAL_BOOL, t->line, t->col);
        e->data.str_val = tok_str(t);
        return e;
    }

    if (t->type == TOK_IDENT) {
        advance(p);
        const char *name = tok_str(t);

        // function call?
        if (check(p, TOK_LPAREN)) {
            return parse_call(p, name, t->line, t->col);
        }

        Expr *e = expr_new(NODE_IDENT, t->line, t->col);
        e->data.str_val = name;
        return e;
    }

    // func/proc literal (e.g. as RHS of :=)
    if (t->type == TOK_FUNC || t->type == TOK_PROC || t->type == TOK_MACRO ||
        t->type == TOK_EXT_FUNC || t->type == TOK_EXT_PROC) {
        return parse_func_def(p);
    }

    fprintf(stderr, "%s:%d:%d: parse error: unexpected token '%.*s'\n",
            p->path, t->line, t->col, t->len, t->start);
    exit(1);
}

// parse_statement_ident: identifier is current token
static Expr *parse_statement_ident(Parser *p) {
    Token *t = advance(p); // consume identifier
    const char *name = tok_str(t);

    // Declaration: name := value (inferred type)
    if (check(p, TOK_COLONEQ)) {
        advance(p); // consume :=
        Expr *decl = expr_new(NODE_DECL, t->line, t->col);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = NULL;
        decl->data.decl.is_mut = false;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Declaration with explicit type: name : Type = value
    // Or func/proc def: name : proc(...) { ... }
    if (check(p, TOK_COLON)) {
        advance(p); // consume :
        // name : Type = value
        Token *type_tok = peek(p);
        const char *type_name = tok_str(type_tok);
        advance(p); // consume type name
        expect(p, TOK_EQ); // consume =
        Expr *decl = expr_new(NODE_DECL, t->line, t->col);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = type_name;
        decl->data.decl.is_mut = false;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Function call: name(...)
    if (check(p, TOK_LPAREN)) {
        return parse_call(p, name, t->line, t->col);
    }

    fprintf(stderr, "%s:%d:%d: parse error: expected ':=', ':' or '(' after identifier '%s'\n",
            p->path, t->line, t->col, name);
    exit(1);
}

static Expr *parse_statement(Parser *p) {
    Token *t = peek(p);

    switch (t->type) {
    case TOK_IDENT:
        return parse_statement_ident(p);
    case TOK_RETURN: {
        advance(p);
        Expr *ret = expr_new(NODE_RETURN, t->line, t->col);
        // If next token looks like a value, parse it
        if (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
            expr_add_child(ret, parse_expression(p));
        }
        return ret;
    }
    case TOK_IF: {
        advance(p); // consume 'if'
        Expr *node = expr_new(NODE_IF, t->line, t->col);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TOK_LBRACE);
        expr_add_child(node, parse_block(p));       // then body
        if (check(p, TOK_ELSE)) {
            advance(p); // consume 'else'
            expect(p, TOK_LBRACE);
            expr_add_child(node, parse_block(p));   // else body
        }
        return node;
    }
    case TOK_WHILE: {
        advance(p); // consume 'while'
        Expr *node = expr_new(NODE_WHILE, t->line, t->col);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TOK_LBRACE);
        expr_add_child(node, parse_block(p));       // body
        return node;
    }
    default:
        fprintf(stderr, "%s:%d:%d: parse error: expected statement, found '%.*s'\n",
                p->path, t->line, t->col, t->len, t->start);
        exit(1);
    }
}

Expr *parse(Token *tokens, int count, const char *path, const char **mode_out) {
    Parser p = {tokens, count, 0, path};

    // Parse optional mode declaration
    if (mode_out) *mode_out = NULL;
    if (check(&p, TOK_MODE)) {
        advance(&p); // consume 'mode'
        Token *mode_name = expect(&p, TOK_IDENT);
        if (mode_out) *mode_out = tok_str(mode_name);
    }

    // Parse body (top-level statements until EOF)
    Expr *root = expr_new(NODE_BODY, 1, 1);
    while (!check(&p, TOK_EOF)) {
        expr_add_child(root, parse_statement(&p));
    }

    return root;
}
