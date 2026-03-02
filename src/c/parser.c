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

    // Parse parameters: name: Type, name: Type, ...
    int param_cap = 4;
    const char **param_names = malloc(param_cap * sizeof(char *));
    const char **param_types = malloc(param_cap * sizeof(char *));
    Expr **param_defaults = malloc(param_cap * sizeof(Expr *));
    int nparam = 0;
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        Token *pname = expect(p, TOK_IDENT);
        expect(p, TOK_COLON);
        Token *ptype = expect(p, TOK_IDENT);
        if (nparam >= param_cap) {
            param_cap *= 2;
            param_names = realloc(param_names, param_cap * sizeof(char *));
            param_types = realloc(param_types, param_cap * sizeof(char *));
            param_defaults = realloc(param_defaults, param_cap * sizeof(Expr *));
        }
        param_names[nparam] = tok_str(pname);
        param_types[nparam] = tok_str(ptype);
        // Optional default value: name: Type = expr
        if (check(p, TOK_EQ)) {
            advance(p); // consume '='
            param_defaults[nparam] = parse_expression(p);
        } else {
            param_defaults[nparam] = NULL;
        }
        nparam++;
        if (check(p, TOK_COMMA)) advance(p);
    }
    expect(p, TOK_RPAREN);

    // Parse optional 'returns Type'
    const char *return_type = NULL;
    if (check(p, TOK_RETURNS)) {
        advance(p);
        Token *rt = expect(p, TOK_IDENT);
        return_type = tok_str(rt);
    }

    Expr *def = expr_new(NODE_FUNC_DEF, kw->line, kw->col);
    def->data.func_def.func_type = ft;
    def->data.func_def.param_names = param_names;
    def->data.func_def.param_types = param_types;
    def->data.func_def.param_defaults = param_defaults;
    def->data.func_def.nparam = nparam;
    def->data.func_def.return_type = return_type;

    expect(p, TOK_LBRACE);
    expr_add_child(def, parse_block(p));

    return def;
}

// parse_struct_def: current token is 'struct'
static Expr *parse_struct_def(Parser *p) {
    Token *kw = advance(p); // consume 'struct'
    Expr *def = expr_new(NODE_STRUCT_DEF, kw->line, kw->col);
    expect(p, TOK_LBRACE);
    expr_add_child(def, parse_block(p)); // body of declarations
    return def;
}

// parse_call: identifier already consumed, current token is '('
static Expr *parse_call(Parser *p, const char *name, int line, int col) {
    advance(p); // consume '('

    // loc() — replaced with "path:line:col" string literal
    if (strcmp(name, "loc") == 0) {
        expect(p, TOK_RPAREN);
        char buf[256];
        snprintf(buf, sizeof(buf), "%s:%d:%d", p->path, line, col);
        Expr *e = expr_new(NODE_LITERAL_STR, line, col);
        char *s = malloc(strlen(buf) + 1);
        strcpy(s, buf);
        e->data.str_val = s;
        return e;
    }

    Expr *call = expr_new(NODE_FCALL, line, col);

    // first child is the callee identifier
    Expr *callee = expr_new(NODE_IDENT, line, col);
    callee->data.str_val = name;
    expr_add_child(call, callee);

    // parse arguments (positional or named: name=expr)
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        // Check for named arg: IDENT '=' expr (peek ahead)
        if (check(p, TOK_IDENT) && p->pos + 1 < p->count &&
            p->tokens[p->pos + 1].type == TOK_EQ) {
            Token *aname = advance(p); // consume ident
            advance(p); // consume '='
            Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col);
            na->data.str_val = tok_str(aname);
            expr_add_child(na, parse_expression(p));
            expr_add_child(call, na);
        } else {
            expr_add_child(call, parse_expression(p));
        }
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

        Expr *e;
        // function call?
        if (check(p, TOK_LPAREN)) {
            e = parse_call(p, name, t->line, t->col);
        } else {
            e = expr_new(NODE_IDENT, t->line, t->col);
            e->data.str_val = name;
        }

        // field access chain: expr.field.field...
        while (check(p, TOK_DOT)) {
            advance(p); // consume '.'
            Token *field = expect(p, TOK_IDENT);
            Expr *access = expr_new(NODE_FIELD_ACCESS, field->line, field->col);
            access->data.str_val = tok_str(field);
            expr_add_child(access, e);
            e = access;
        }
        return e;
    }

    // func/proc literal (e.g. as RHS of :=)
    if (t->type == TOK_FUNC || t->type == TOK_PROC || t->type == TOK_MACRO ||
        t->type == TOK_EXT_FUNC || t->type == TOK_EXT_PROC) {
        return parse_func_def(p);
    }

    // struct literal (e.g. as RHS of :=)
    if (t->type == TOK_STRUCT) {
        return parse_struct_def(p);
    }

    fprintf(stderr, "%s:%d:%d: parse error: unexpected token '%.*s'\n",
            p->path, t->line, t->col, t->len, t->start);
    exit(1);
}

// parse_statement_ident: identifier is current token
static Expr *parse_statement_ident(Parser *p, int is_mut) {
    Token *t = advance(p); // consume identifier
    const char *name = tok_str(t);

    // Declaration: name := value (inferred type)
    if (check(p, TOK_COLONEQ)) {
        advance(p); // consume :=
        Expr *decl = expr_new(NODE_DECL, t->line, t->col);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = NULL;
        decl->data.decl.is_mut = is_mut;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Declaration with explicit type: name : Type = value
    if (check(p, TOK_COLON)) {
        advance(p); // consume :
        Token *type_tok = peek(p);
        const char *type_name = tok_str(type_tok);
        advance(p); // consume type name
        expect(p, TOK_EQ); // consume =
        Expr *decl = expr_new(NODE_DECL, t->line, t->col);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = type_name;
        decl->data.decl.is_mut = is_mut;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Field assignment: name.field = value  or  name.a.b.c = value
    if (check(p, TOK_DOT)) {
        // Build the field access chain
        Expr *obj = expr_new(NODE_IDENT, t->line, t->col);
        obj->data.str_val = name;
        Token *last_field = NULL;
        while (check(p, TOK_DOT)) {
            advance(p); // consume '.'
            last_field = expect(p, TOK_IDENT);
            if (check(p, TOK_DOT)) {
                // More dots coming — this is an intermediate access
                Expr *access = expr_new(NODE_FIELD_ACCESS, last_field->line, last_field->col);
                access->data.str_val = tok_str(last_field);
                expr_add_child(access, obj);
                obj = access;
            }
        }
        expect(p, TOK_EQ);
        Expr *fa = expr_new(NODE_FIELD_ASSIGN, t->line, t->col);
        fa->data.str_val = tok_str(last_field);
        expr_add_child(fa, obj);
        expr_add_child(fa, parse_expression(p));
        return fa;
    }

    // Assignment: name = value
    if (check(p, TOK_EQ)) {
        advance(p); // consume =
        Expr *assign = expr_new(NODE_ASSIGN, t->line, t->col);
        assign->data.str_val = name;
        expr_add_child(assign, parse_expression(p));
        return assign;
    }

    // Function call: name(...)
    if (check(p, TOK_LPAREN)) {
        return parse_call(p, name, t->line, t->col);
    }

    fprintf(stderr, "%s:%d:%d: parse error: expected ':=', ':', '=' or '(' after identifier '%s'\n",
            p->path, t->line, t->col, name);
    exit(1);
}

static Expr *parse_statement(Parser *p) {
    Token *t = peek(p);

    switch (t->type) {
    case TOK_IDENT:
        return parse_statement_ident(p, 0);
    case TOK_MUT: {
        advance(p); // consume 'mut'
        return parse_statement_ident(p, 1);
    }
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
    case TOK_LBRACE: {
        advance(p); // consume '{'
        return parse_block(p);
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
