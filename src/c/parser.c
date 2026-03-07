#include "parser.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Parser state ---

typedef struct {
    Token *tokens;
    I32 count;
    I32 pos;
    const char *path;
    Str *spath;  // path as Str* (for Expr nodes)
} Parser;

static Token *peek(Parser *p) {
    return &p->tokens[p->pos];
}

static Token *advance(Parser *p) {
    Token *t = &p->tokens[p->pos];
    if (t->type != TOK_EOF) p->pos++;
    return t;
}

static I32 check(Parser *p, TokenType type) {
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

// Extract a Str from a token.
static Str *tok_str(Token *t) {
    return Str_new_len(t->start, t->len);
}

// --- Forward declarations ---

static Expr *parse_statement(Parser *p);
static Expr *parse_expression(Parser *p);

// --- Parsing functions ---

// parse_block: expects '{' already consumed, reads statements until '}'
static Expr *parse_block(Parser *p) {
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->spath);
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
    case TOK_TEST:     ft = FUNC_TEST;     break;
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
    Vec pnames = Vec_new(sizeof(Str *));
    Vec ptypes = Vec_new(sizeof(Str *));
    Vec pmuts = Vec_new(sizeof(bool));
    Vec powns = Vec_new(sizeof(bool));
    Vec pdefs = Vec_new(sizeof(Expr *));
    I32 variadic_index = -1;
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        bool is_own = false;
        if (check(p, TOK_OWN)) {
            advance(p);
            is_own = true;
        }
        bool is_mut = false;
        if (check(p, TOK_MUT)) {
            advance(p);
            is_mut = true;
        }
        Token *pname = expect(p, TOK_IDENT);
        expect(p, TOK_COLON);
        bool is_this_variadic = false;
        if (check(p, TOK_DOTDOT)) {
            advance(p); // consume '..'
            if (is_own) {
                fprintf(stderr, "%s:%d:%d: parse error: variadic parameter '%.*s' cannot be 'own' (implicit)\n",
                        p->path, pname->line, pname->col, pname->len, pname->start);
                exit(1);
            }
            if (is_mut) {
                fprintf(stderr, "%s:%d:%d: parse error: variadic parameter '%.*s' cannot be 'mut'\n",
                        p->path, pname->line, pname->col, pname->len, pname->start);
                exit(1);
            }
            if (variadic_index >= 0) {
                fprintf(stderr, "%s:%d:%d: parse error: only one variadic parameter is allowed\n",
                        p->path, pname->line, pname->col);
                exit(1);
            }
            variadic_index = pnames.count; // index of this param (before push)
            is_this_variadic = true;
        }
        Token *ptype = expect(p, TOK_IDENT);
        Str *nm = tok_str(pname);
        Str *tp = tok_str(ptype);
        Vec_push(&pnames, &nm);
        Vec_push(&ptypes, &tp);
        Vec_push(&pmuts, &is_mut);
        Vec_push(&powns, &is_own);
        // Optional default value: name: Type = expr
        Expr *def_val = NULL;
        if (check(p, TOK_EQ)) {
            advance(p); // consume '='
            def_val = parse_expression(p);
        }
        if (variadic_index >= 0 && !is_this_variadic && !def_val) {
            fprintf(stderr, "%s:%d:%d: parse error: positional parameter '%.*s' not allowed after variadic\n",
                    p->path, pname->line, pname->col, pname->len, pname->start);
            exit(1);
        }
        Vec_push(&pdefs, &def_val);
        if (check(p, TOK_COMMA)) advance(p);
    }
    expect(p, TOK_RPAREN);

    // Parse optional 'returns [ref] Type'
    Str *return_type = NULL;
    bool return_is_ref = false;
    if (check(p, TOK_RETURNS)) {
        advance(p);
        if (check(p, TOK_REF)) {
            advance(p);
            return_is_ref = true;
        }
        Token *rt = expect(p, TOK_IDENT);
        return_type = tok_str(rt);
    }

    Expr *def = expr_new(NODE_FUNC_DEF, kw->line, kw->col, p->spath);
    def->data.func_def.func_type = ft;
    def->data.func_def.nparam = pnames.count;
    def->data.func_def.param_names = Vec_take(&pnames);
    def->data.func_def.param_types = Vec_take(&ptypes);
    def->data.func_def.param_muts = Vec_take(&pmuts);
    def->data.func_def.param_owns = Vec_take(&powns);
    def->data.func_def.param_defaults = Vec_take(&pdefs);
    def->data.func_def.return_type = return_type;
    def->data.func_def.return_is_ref = return_is_ref;
    def->data.func_def.variadic_index = variadic_index;

    expect(p, TOK_LBRACE);
    expr_add_child(def, parse_block(p));

    return def;
}

// parse_struct_def: current token is 'struct' or 'ext_struct'
static Expr *parse_struct_def(Parser *p) {
    Token *kw = advance(p); // consume 'struct' or 'ext_struct'
    bool is_ext = (kw->type == TOK_EXT_STRUCT);
    Expr *def = expr_new(NODE_STRUCT_DEF, kw->line, kw->col, p->spath);
    def->is_ext = is_ext;
    expect(p, TOK_LBRACE);
    // Parse struct body with namespace: support
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->spath);
    I32 in_namespace = 0;
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        if (check(p, TOK_NAMESPACE)) {
            advance(p); // consume 'namespace'
            expect(p, TOK_COLON);
            in_namespace = 1;
            continue;
        }
        Expr *stmt = parse_statement(p);
        if (in_namespace && stmt->type == NODE_DECL) {
            stmt->data.decl.is_namespace = true;
        }
        expr_add_child(body, stmt);
    }
    expect(p, TOK_RBRACE);
    expr_add_child(def, body);

    return def;
}

// parse_enum_def: current token is 'enum'
static Expr *parse_enum_def(Parser *p) {
    Token *kw = advance(p); // consume 'enum'
    Expr *def = expr_new(NODE_ENUM_DEF, kw->line, kw->col, p->spath);
    expect(p, TOK_LBRACE);
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->spath);
    I32 in_namespace = 0;
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        if (check(p, TOK_NAMESPACE)) {
            advance(p);
            expect(p, TOK_COLON);
            in_namespace = 1;
            continue;
        }
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            if (stmt->type == NODE_DECL) {
                stmt->data.decl.is_namespace = true;
            }
            expr_add_child(body, stmt);
        } else {
            // Variant: bare identifier or Variant: Type, comma-separated
            Token *name = expect(p, TOK_IDENT);
            Expr *variant = expr_new(NODE_DECL, name->line, name->col, p->spath);
            variant->data.decl.name = tok_str(name);
            if (check(p, TOK_COLON)) {
                advance(p);
                Token *ptype = expect(p, TOK_IDENT);
                variant->data.decl.explicit_type = tok_str(ptype);
            }
            expr_add_child(body, variant);
            if (check(p, TOK_COMMA)) advance(p);
        }
    }
    expect(p, TOK_RBRACE);
    expr_add_child(def, body);
    return def;
}

// parse_call: identifier already consumed, current token is '('
static Expr *parse_call(Parser *p, Str *name, I32 line, I32 col) {
    advance(p); // consume '('

    // loc() — replaced with "path:line:col" string literal
    if (Str_eq_c(name, "loc")) {
        expect(p, TOK_RPAREN);
        char buf[256];
        snprintf(buf, sizeof(buf), "%s:%d:%d", p->path, line, col);
        Expr *e = expr_new(NODE_LITERAL_STR, line, col, p->spath);
        e->data.str_val = Str_new(buf);
        return e;
    }

    Expr *call = expr_new(NODE_FCALL, line, col, p->spath);

    // first child is the callee identifier
    Expr *callee = expr_new(NODE_IDENT, line, col, p->spath);
    callee->data.str_val = name;
    expr_add_child(call, callee);

    // parse arguments (positional or named: name=expr)
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        // Check for named arg: IDENT '=' expr (peek ahead)
        if (check(p, TOK_IDENT) && p->pos + 1 < p->count &&
            p->tokens[p->pos + 1].type == TOK_EQ) {
            Token *aname = advance(p); // consume ident
            advance(p); // consume '='
            Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->spath);
            na->data.str_val = tok_str(aname);
            expr_add_child(na, parse_expression(p));
            expr_add_child(call, na);
        } else {
            bool is_own_arg = false;
            if (check(p, TOK_OWN)) {
                advance(p);
                is_own_arg = true;
            }
            Expr *arg = parse_expression(p);
            arg->is_own_arg = is_own_arg;
            expr_add_child(call, arg);
        }
        if (check(p, TOK_COMMA)) advance(p); // skip comma between args
    }
    expect(p, TOK_RPAREN);

    return call;
}

// parse_expression: for now handles literals, identifiers, and calls
static Expr *parse_expression(Parser *p) {
    Token *t = peek(p);
    Expr *e = NULL;

    if (t->type == TOK_STRING) {
        advance(p);
        e = expr_new(NODE_LITERAL_STR, t->line, t->col, p->spath);
        e->data.str_val = tok_str(t);
    } else if (t->type == TOK_NUMBER) {
        advance(p);
        e = expr_new(NODE_LITERAL_NUM, t->line, t->col, p->spath);
        e->data.str_val = tok_str(t);
    } else if (t->type == TOK_TRUE || t->type == TOK_FALSE) {
        advance(p);
        e = expr_new(NODE_LITERAL_BOOL, t->line, t->col, p->spath);
        e->data.str_val = tok_str(t);
    } else if (t->type == TOK_IDENT) {
        advance(p);
        Str *name = tok_str(t);
        // function call?
        if (check(p, TOK_LPAREN)) {
            e = parse_call(p, name, t->line, t->col);
        } else {
            e = expr_new(NODE_IDENT, t->line, t->col, p->spath);
            e->data.str_val = name;
        }
    } else if (t->type == TOK_FUNC || t->type == TOK_PROC || t->type == TOK_TEST ||
               t->type == TOK_MACRO || t->type == TOK_EXT_FUNC || t->type == TOK_EXT_PROC) {
        return parse_func_def(p);
    } else if (t->type == TOK_STRUCT || t->type == TOK_EXT_STRUCT) {
        return parse_struct_def(p);
    } else if (t->type == TOK_ENUM) {
        return parse_enum_def(p);
    } else {
        fprintf(stderr, "%s:%d:%d: parse error: unexpected token '%.*s'\n",
                p->path, t->line, t->col, t->len, t->start);
        exit(1);
    }

    // field access chain: expr.field.field... or expr.method(args)
    while (check(p, TOK_DOT)) {
        advance(p); // consume '.'
        Token *field = expect(p, TOK_IDENT);
        if (check(p, TOK_LPAREN)) {
            // Method call: expr.method(args)
            advance(p); // consume '('
            Expr *callee = expr_new(NODE_FIELD_ACCESS, field->line, field->col, p->spath);
            callee->data.str_val = tok_str(field);
            expr_add_child(callee, e);
            Expr *call = expr_new(NODE_FCALL, field->line, field->col, p->spath);
            expr_add_child(call, callee);
            while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                if (check(p, TOK_IDENT) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type == TOK_EQ) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->spath);
                    na->data.str_val = tok_str(aname);
                    expr_add_child(na, parse_expression(p));
                    expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TOK_OWN)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    expr_add_child(call, arg);
                }
                if (check(p, TOK_COMMA)) advance(p);
            }
            expect(p, TOK_RPAREN);
            e = call;
        } else {
            Expr *access = expr_new(NODE_FIELD_ACCESS, field->line, field->col, p->spath);
            access->data.str_val = tok_str(field);
            expr_add_child(access, e);
            e = access;
        }
    }
    return e;
}

// parse_statement_ident: identifier is current token
static Expr *parse_statement_ident(Parser *p, I32 is_mut, I32 is_own) {
    Token *t = advance(p); // consume identifier
    Str *name = tok_str(t);

    // Declaration: name := value (inferred type)
    if (check(p, TOK_COLONEQ)) {
        advance(p); // consume :=
        Expr *decl = expr_new(NODE_DECL, t->line, t->col, p->spath);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = NULL;
        decl->data.decl.is_mut = is_mut;
        decl->data.decl.is_own = is_own;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Declaration with explicit type: name : Type = value
    if (check(p, TOK_COLON)) {
        advance(p); // consume :
        Token *type_tok = peek(p);
        Str *type_name = tok_str(type_tok);
        advance(p); // consume type name
        expect(p, TOK_EQ); // consume =
        Expr *decl = expr_new(NODE_DECL, t->line, t->col, p->spath);
        decl->data.decl.name = name;
        decl->data.decl.explicit_type = type_name;
        decl->data.decl.is_mut = is_mut;
        decl->data.decl.is_own = is_own;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Field assignment or method call: name.field = value  or  name.method(args)
    if (check(p, TOK_DOT)) {
        // Build the field access chain
        Expr *obj = expr_new(NODE_IDENT, t->line, t->col, p->spath);
        obj->data.str_val = name;
        Token *last_field = NULL;
        while (check(p, TOK_DOT)) {
            advance(p); // consume '.'
            last_field = expect(p, TOK_IDENT);
            if (check(p, TOK_DOT)) {
                // More dots coming — this is an intermediate access
                Expr *access = expr_new(NODE_FIELD_ACCESS, last_field->line, last_field->col, p->spath);
                access->data.str_val = tok_str(last_field);
                expr_add_child(access, obj);
                obj = access;
            }
        }
        // Method call: name.method(args)
        if (check(p, TOK_LPAREN)) {
            advance(p); // consume '('
            Expr *callee = expr_new(NODE_FIELD_ACCESS, last_field->line, last_field->col, p->spath);
            callee->data.str_val = tok_str(last_field);
            expr_add_child(callee, obj);
            Expr *call = expr_new(NODE_FCALL, last_field->line, last_field->col, p->spath);
            expr_add_child(call, callee);
            while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                if (check(p, TOK_IDENT) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type == TOK_EQ) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->spath);
                    na->data.str_val = tok_str(aname);
                    expr_add_child(na, parse_expression(p));
                    expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TOK_OWN)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    expr_add_child(call, arg);
                }
                if (check(p, TOK_COMMA)) advance(p);
            }
            expect(p, TOK_RPAREN);
            return call;
        }
        // Field assignment
        expect(p, TOK_EQ);
        Expr *fa = expr_new(NODE_FIELD_ASSIGN, t->line, t->col, p->spath);
        fa->data.str_val = tok_str(last_field);
        expr_add_child(fa, obj);
        expr_add_child(fa, parse_expression(p));
        return fa;
    }

    // Assignment: name = value
    if (check(p, TOK_EQ)) {
        advance(p); // consume =
        Expr *assign = expr_new(NODE_ASSIGN, t->line, t->col, p->spath);
        assign->data.str_val = name;
        expr_add_child(assign, parse_expression(p));
        return assign;
    }

    // Function call: name(...)
    if (check(p, TOK_LPAREN)) {
        return parse_call(p, name, t->line, t->col);
    }

    fprintf(stderr, "%s:%d:%d: parse error: expected ':=', ':', '=' or '(' after identifier '%s'\n",
            p->path, t->line, t->col, name->c_str);
    exit(1);
}

static Expr *parse_statement(Parser *p) {
    Token *t = peek(p);

    switch (t->type) {
    case TOK_IDENT:
        return parse_statement_ident(p, 0, 0);
    case TOK_REF: {
        advance(p); // consume 'ref'
        bool ref_mut = false;
        if (check(p, TOK_MUT)) {
            advance(p); // consume 'mut'
            ref_mut = true;
        }
        Token *ident = expect(p, TOK_IDENT);
        Str *name = tok_str(ident);
        Expr *decl = expr_new(NODE_DECL, ident->line, ident->col, p->spath);
        decl->data.decl.name = name;
        decl->data.decl.is_ref = true;
        if (ref_mut) decl->data.decl.is_mut = true;
        if (check(p, TOK_COLON)) {
            // ref name : Type = expr
            advance(p); // consume :
            Token *type_tok = peek(p);
            decl->data.decl.explicit_type = tok_str(type_tok);
            advance(p); // consume type name
            expect(p, TOK_EQ); // consume =
        } else {
            // ref name := expr
            expect(p, TOK_COLONEQ);
        }
        expr_add_child(decl, parse_expression(p));
        return decl;
    }
    case TOK_MUT: {
        advance(p); // consume 'mut'
        return parse_statement_ident(p, 1, 0);
    }
    case TOK_RETURN: {
        advance(p);
        Expr *ret = expr_new(NODE_RETURN, t->line, t->col, p->spath);
        // If next token looks like a value, parse it
        if (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
            expr_add_child(ret, parse_expression(p));
        }
        return ret;
    }
    case TOK_IF: {
        advance(p); // consume 'if'
        Expr *node = expr_new(NODE_IF, t->line, t->col, p->spath);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TOK_LBRACE);
        expr_add_child(node, parse_block(p));       // then body
        if (check(p, TOK_ELSE)) {
            advance(p); // consume 'else'
            if (check(p, TOK_IF)) {
                // else if → else { if ... }
                Expr *else_body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->spath);
                expr_add_child(else_body, parse_statement(p));
                expr_add_child(node, else_body);
            } else {
                expect(p, TOK_LBRACE);
                expr_add_child(node, parse_block(p));
            }
        }
        return node;
    }
    case TOK_STRING:
    case TOK_NUMBER:
    case TOK_TRUE:
    case TOK_FALSE:
        return parse_expression(p);
    case TOK_LBRACE: {
        advance(p); // consume '{'
        return parse_block(p);
    }
    case TOK_WHILE: {
        advance(p); // consume 'while'
        Expr *node = expr_new(NODE_WHILE, t->line, t->col, p->spath);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TOK_LBRACE);
        expr_add_child(node, parse_block(p));       // body
        return node;
    }
    case TOK_OWN: {
        advance(p); // consume 'own'
        // own field declaration: own name := value  or  own mut name := value
        if (check(p, TOK_IDENT) || check(p, TOK_MUT)) {
            I32 own_mut = 0;
            if (check(p, TOK_MUT)) { advance(p); own_mut = 1; }
            if (check(p, TOK_IDENT)) {
                Token *next = &p->tokens[p->pos + 1];
                if (next->type == TOK_COLONEQ || next->type == TOK_COLON) {
                    return parse_statement_ident(p, own_mut, 1);
                }
            }
            // Not a declaration — fall through to own expression
            if (own_mut) {
                // We consumed 'mut' but it's not a declaration — error
                fprintf(stderr, "%s:%d:%d: parse error: expected identifier after 'own mut'\n",
                        p->path, t->line, t->col);
                exit(1);
            }
        }
        // own expression (call-site ownership marker)
        Expr *expr = parse_expression(p);
        Expr *primary = expr;
        while (primary->children.count > 0 &&
               (primary->type == NODE_FCALL || primary->type == NODE_FIELD_ACCESS)) {
            primary = expr_child(primary, 0);
        }
        primary->is_own_arg = true;
        return expr;
    }
    case TOK_BREAK: {
        advance(p);
        return expr_new(NODE_BREAK, t->line, t->col, p->spath);
    }
    case TOK_CONTINUE: {
        advance(p);
        return expr_new(NODE_CONTINUE, t->line, t->col, p->spath);
    }
    default:
        fprintf(stderr, "%s:%d:%d: parse error: expected statement, found '%.*s'\n",
                p->path, t->line, t->col, t->len, t->start);
        exit(1);
    }
}

Expr *parse(Token *tokens, I32 count, const char *path, Str **mode_out) {
    Parser p = {tokens, count, 0, path, Str_new(path)};

    // Parse optional mode declaration
    if (mode_out) *mode_out = NULL;
    if (check(&p, TOK_MODE)) {
        advance(&p); // consume 'mode'
        // Accept TOK_IDENT or TOK_TEST (test is both a keyword and a mode name)
        Token *mode_name = (check(&p, TOK_IDENT) || check(&p, TOK_TEST))
            ? advance(&p) : expect(&p, TOK_IDENT);
        if (mode_out) *mode_out = tok_str(mode_name);
    }

    // Parse body (top-level statements until EOF)
    Expr *root = expr_new(NODE_BODY, 1, 1, p.spath);
    while (!check(&p, TOK_EOF)) {
        expr_add_child(root, parse_statement(&p));
    }

    return root;
}
