#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Parser state ---

typedef struct {
    Token *tokens;
    U32 count;
    U32 pos;
    Str *path;
} Parser;

static Token *peek(Parser *p) {
    return &p->tokens[p->pos];
}

static Token *advance(Parser *p) {
    Token *t = &p->tokens[p->pos];
    if (t->type.tag != TokenType_TAG_Eof) p->pos++;
    return t;
}

static I32 check(Parser *p, TokenType_tag type) {
    return peek(p)->type.tag == type;
}

static Token *expect(Parser *p, TokenType_tag type) {
    Token *t = peek(p);
    if (t->type.tag != type) {
        TokenType tt = {type};
        fprintf(stderr, "%s:%lld:%lld: parse error: expected '%s', found '%.*s'\n",
                p->path->c_str, t->line, t->col,
                tok_name(&tt)->c_str,
                (int)t->text.count, (const char *)t->text.c_str);
        exit(1);
    }
    return advance(p);
}

// Extract a Str from a token.
static Str *tok_str(Token *t) {
    return Str_clone(&t->text);
}

// --- Forward declarations ---

static Expr *parse_statement(Parser *p);
static Expr *parse_expression(Parser *p);
static Expr *parse_primary(Parser *p);

// --- Parsing functions ---

// parse_block: expects '{' already consumed, reads statements until '}'
static Expr *parse_block(Parser *p) {
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->path);
    while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
        expr_add_child(body, parse_statement(p));
    }
    expect(p, TokenType_TAG_RBrace);
    return body;
}

// parse_func_def: current token is func/proc/etc
static Expr *parse_func_def(Parser *p) {
    Token *kw = advance(p); // consume func/proc/etc
    FuncType ft;
    switch (kw->type.tag) {
    case TokenType_TAG_KwFunc:     ft = FUNC_FUNC;     break;
    case TokenType_TAG_KwProc:     ft = FUNC_PROC;     break;
    case TokenType_TAG_KwTest:     ft = FUNC_TEST;     break;
    case TokenType_TAG_KwMacro:    ft = FUNC_MACRO;    break;
    case TokenType_TAG_KwExtFunc:  ft = FUNC_EXT_FUNC; break;
    case TokenType_TAG_KwExtProc:  ft = FUNC_EXT_PROC; break;
    default:
        fprintf(stderr, "%s:%lld:%lld: parse error: expected function keyword\n",
                p->path->c_str, kw->line, kw->col);
        exit(1);
    }

    expect(p, TokenType_TAG_LParen);

    // Parse parameters: name: Type, name: Type, ...
    Vec pnames; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); pnames = *_vp; free(_vp); }
    Vec ptypes; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); ptypes = *_vp; free(_vp); }
    Vec pmuts; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(bool)}); pmuts = *_vp; free(_vp); }
    Vec powns; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(bool)}); powns = *_vp; free(_vp); }
    Vec pdefs; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); pdefs = *_vp; free(_vp); }
    Vec pshallows; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(bool)}); pshallows = *_vp; free(_vp); }
    I32 variadic_index = -1;
    while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
        bool is_shallow = false;
        if (check(p, TokenType_TAG_KwShallow)) {
            advance(p);
            is_shallow = true;
        }
        bool is_own = false;
        if (check(p, TokenType_TAG_KwOwn)) {
            advance(p);
            is_own = true;
        }
        bool is_mut = false;
        if (check(p, TokenType_TAG_KwMut)) {
            advance(p);
            is_mut = true;
        }
        Token *pname = expect(p, TokenType_TAG_Ident);
        expect(p, TokenType_TAG_Colon);
        bool is_this_variadic = false;
        if (check(p, TokenType_TAG_DotDot)) {
            advance(p); // consume '..'
            if (is_own) {
                fprintf(stderr, "%s:%lld:%lld: parse error: variadic parameter '%.*s' cannot be 'own' (implicit)\n",
                        p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                exit(1);
            }
            if (is_mut) {
                fprintf(stderr, "%s:%lld:%lld: parse error: variadic parameter '%.*s' cannot be 'mut'\n",
                        p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                exit(1);
            }
            if (is_shallow) {
                fprintf(stderr, "%s:%lld:%lld: parse error: variadic parameter '%.*s' cannot be 'shallow'\n",
                        p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                exit(1);
            }
            if (variadic_index >= 0) {
                fprintf(stderr, "%s:%lld:%lld: parse error: only one variadic parameter is allowed\n",
                        p->path->c_str, pname->line, pname->col);
                exit(1);
            }
            variadic_index = pnames.count; // index of this param (before push)
            is_this_variadic = true;
        }
        Token *ptype = expect(p, TokenType_TAG_Ident);
        Str *nm = tok_str(pname);
        Str *tp = tok_str(ptype);
        { Str **_p = malloc(sizeof(Str *)); *_p = nm; Vec_push(&pnames, _p); }
        { Str **_p = malloc(sizeof(Str *)); *_p = tp; Vec_push(&ptypes, _p); }
        { bool *_p = malloc(sizeof(bool)); *_p = is_mut; Vec_push(&pmuts, _p); }
        { bool *_p = malloc(sizeof(bool)); *_p = is_own; Vec_push(&powns, _p); }
        { bool *_p = malloc(sizeof(bool)); *_p = is_shallow; Vec_push(&pshallows, _p); }
        // Optional default value: name: Type = expr
        Expr *def_val = NULL;
        if (check(p, TokenType_TAG_Eq)) {
            advance(p); // consume '='
            def_val = parse_expression(p);
        }
        if (variadic_index >= 0 && !is_this_variadic && !def_val) {
            fprintf(stderr, "%s:%lld:%lld: parse error: positional parameter '%.*s' not allowed after variadic\n",
                    p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
            exit(1);
        }
        { Expr **_p = malloc(sizeof(Expr *)); *_p = def_val; Vec_push(&pdefs, _p); }
        if (check(p, TokenType_TAG_Comma)) advance(p);
    }
    expect(p, TokenType_TAG_RParen);

    // Parse optional 'returns [ref|shallow] Type'
    Str *return_type = NULL;
    bool return_is_ref = false;
    bool return_is_shallow = false;
    if (check(p, TokenType_TAG_KwReturns)) {
        advance(p);
        if (check(p, TokenType_TAG_KwRef)) {
            advance(p);
            return_is_ref = true;
        } else if (check(p, TokenType_TAG_KwShallow)) {
            advance(p);
            return_is_shallow = true;
        }
        Token *rt = expect(p, TokenType_TAG_Ident);
        return_type = tok_str(rt);
    }

    Expr *def = expr_new(NODE_FUNC_DEF, kw->line, kw->col, p->path);
    def->type.func_def.func_type = ft;
    def->type.func_def.nparam = pnames.count;
    def->type.func_def.param_names = Vec_take(&pnames);
    def->type.func_def.param_types = Vec_take(&ptypes);
    def->type.func_def.param_muts = Vec_take(&pmuts);
    def->type.func_def.param_owns = Vec_take(&powns);
    def->type.func_def.param_shallows = Vec_take(&pshallows);
    def->type.func_def.param_defaults = Vec_take(&pdefs);
    def->type.func_def.return_type = return_type;
    def->type.func_def.return_is_ref = return_is_ref;
    def->type.func_def.return_is_shallow = return_is_shallow;
    def->type.func_def.variadic_index = variadic_index;

    expect(p, TokenType_TAG_LBrace);
    expr_add_child(def, parse_block(p));

    return def;
}

// parse_struct_def: current token is 'struct' or 'ext_struct'
static Expr *parse_struct_def(Parser *p) {
    Token *kw = advance(p); // consume 'struct' or 'ext_struct'
    bool is_ext = (kw->type.tag == TokenType_TAG_KwExtStruct);
    Expr *def = expr_new(NODE_STRUCT_DEF, kw->line, kw->col, p->path);
    def->is_ext = is_ext;
    expect(p, TokenType_TAG_LBrace);
    // Parse struct body with namespace: support
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->path);
    I32 in_namespace = 0;
    while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
        if (check(p, TokenType_TAG_KwNamespace)) {
            advance(p); // consume 'namespace'
            expect(p, TokenType_TAG_Colon);
            in_namespace = 1;
            continue;
        }
        Expr *stmt = parse_statement(p);
        if (in_namespace && stmt->type.tag == NODE_DECL) {
            stmt->type.decl.is_namespace = true;
        }
        expr_add_child(body, stmt);
    }
    expect(p, TokenType_TAG_RBrace);
    expr_add_child(def, body);

    return def;
}

// parse_enum_def: current token is 'enum'
static Expr *parse_enum_def(Parser *p) {
    Token *kw = advance(p); // consume 'enum'
    Expr *def = expr_new(NODE_ENUM_DEF, kw->line, kw->col, p->path);
    expect(p, TokenType_TAG_LBrace);
    Expr *body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->path);
    I32 in_namespace = 0;
    while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
        if (check(p, TokenType_TAG_KwNamespace)) {
            advance(p);
            expect(p, TokenType_TAG_Colon);
            in_namespace = 1;
            continue;
        }
        if (in_namespace) {
            Expr *stmt = parse_statement(p);
            if (stmt->type.tag == NODE_DECL) {
                stmt->type.decl.is_namespace = true;
            }
            expr_add_child(body, stmt);
        } else {
            // Variant: bare identifier or Variant: Type, comma-separated
            Token *name = expect(p, TokenType_TAG_Ident);
            Expr *variant = expr_new(NODE_DECL, name->line, name->col, p->path);
            variant->type.decl.name = tok_str(name);
            if (check(p, TokenType_TAG_Colon)) {
                advance(p);
                Token *ptype = expect(p, TokenType_TAG_Ident);
                variant->type.decl.explicit_type = tok_str(ptype);
            }
            expr_add_child(body, variant);
            if (check(p, TokenType_TAG_Comma)) advance(p);
        }
    }
    expect(p, TokenType_TAG_RBrace);
    expr_add_child(def, body);
    return def;
}

// parse_call: identifier already consumed, current token is '('
static Expr *parse_call(Parser *p, Str *name, I64 line, I64 col) {
    advance(p); // consume '('

    Expr *call = expr_new(NODE_FCALL, line, col, p->path);

    // first child is the callee identifier
    Expr *callee = expr_new(NODE_IDENT, line, col, p->path);
    callee->type.str_val = name;
    expr_add_child(call, callee);

    // parse arguments (positional or named: name=expr)
    while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
        // Check for named arg: IDENT '=' expr (peek ahead)
        if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
            p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
            Token *aname = advance(p); // consume ident
            advance(p); // consume '='
            Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->path);
            na->type.str_val = tok_str(aname);
            expr_add_child(na, parse_expression(p));
            expr_add_child(call, na);
        } else {
            bool is_splat = false;
            if (check(p, TokenType_TAG_DotDot)) {
                advance(p);
                is_splat = true;
            }
            bool is_own_arg = false;
            if (check(p, TokenType_TAG_KwOwn)) {
                advance(p);
                is_own_arg = true;
            }
            Expr *arg = parse_expression(p);
            arg->is_own_arg = is_own_arg;
            arg->is_splat = is_splat;
            expr_add_child(call, arg);
        }
        if (check(p, TokenType_TAG_Comma)) advance(p); // skip comma between args
    }
    expect(p, TokenType_TAG_RParen);

    return call;
}

// parse_primary: handles literals, identifiers, calls, field access, grouping parens
static Expr *parse_primary(Parser *p) {
    Token *t = peek(p);
    Expr *e = NULL;

    if (t->type.tag == TokenType_TAG_StringTok) {
        advance(p);
        e = expr_new(NODE_LITERAL_STR, t->line, t->col, p->path);
        e->type.str_val = tok_str(t);
    } else if (t->type.tag == TokenType_TAG_Number) {
        advance(p);
        e = expr_new(NODE_LITERAL_NUM, t->line, t->col, p->path);
        e->type.str_val = tok_str(t);
    } else if (t->type.tag == TokenType_TAG_Char) {
        advance(p);
        const char *ch = (const char *)t->text.c_str;
        U8 byte_val;
        if (ch[0] == '\\') {
            switch (ch[1]) {
            case 'n':  byte_val = 10; break;
            case 't':  byte_val = 9;  break;
            case 'r':  byte_val = 13; break;
            case '\\': byte_val = 92; break;
            case '\'': byte_val = 39; break;
            case '0':  byte_val = 0;  break;
            default:   byte_val = (U8)ch[1]; break;
            }
        } else {
            byte_val = (U8)ch[0];
        }
        e = expr_new(NODE_LITERAL_NUM, t->line, t->col, p->path);
        char buf[4];
        snprintf(buf, sizeof(buf), "%u", byte_val);
        e->type.str_val = Str_new(buf);
        e->til_type = TIL_TYPE_U8;
    } else if (t->type.tag == TokenType_TAG_KwTrue || t->type.tag == TokenType_TAG_KwFalse) {
        advance(p);
        e = expr_new(NODE_LITERAL_BOOL, t->line, t->col, p->path);
        e->type.str_val = tok_str(t);
    } else if (t->type.tag == TokenType_TAG_KwNull) {
        advance(p);
        e = expr_new(NODE_LITERAL_NULL, t->line, t->col, p->path);
    } else if (t->type.tag == TokenType_TAG_Ident) {
        advance(p);
        Str *name = tok_str(t);
        // compile-time directives
        if (Str_eq_c(name, "__LOC__")) {
            char loc[32];
            snprintf(loc, sizeof(loc), ":%lld:%lld", t->line, t->col);
            e = expr_new(NODE_LITERAL_STR, t->line, t->col, p->path);
            e->type.str_val = Str_concat(p->path, Str_new(loc));
        } else if (Str_eq_c(name, "__FILE__")) {
            e = expr_new(NODE_LITERAL_STR, t->line, t->col, p->path);
            e->type.str_val = Str_clone(p->path);
        } else if (Str_eq_c(name, "__LINE__")) {
            char buf[24];
            snprintf(buf, sizeof(buf), "%lld", t->line);
            e = expr_new(NODE_LITERAL_NUM, t->line, t->col, p->path);
            e->type.str_val = Str_new(buf);
        } else if (Str_eq_c(name, "__COL__")) {
            char buf[24];
            snprintf(buf, sizeof(buf), "%lld", t->col);
            e = expr_new(NODE_LITERAL_NUM, t->line, t->col, p->path);
            e->type.str_val = Str_new(buf);
        } else if (check(p, TokenType_TAG_LParen)) {
            e = parse_call(p, name, t->line, t->col);
        } else {
            e = expr_new(NODE_IDENT, t->line, t->col, p->path);
            e->type.str_val = name;
        }
    } else if (t->type.tag == TokenType_TAG_KwFunc || t->type.tag == TokenType_TAG_KwProc || t->type.tag == TokenType_TAG_KwTest ||
               t->type.tag == TokenType_TAG_KwMacro || t->type.tag == TokenType_TAG_KwExtFunc || t->type.tag == TokenType_TAG_KwExtProc) {
        return parse_func_def(p);
    } else if (t->type.tag == TokenType_TAG_KwStruct || t->type.tag == TokenType_TAG_KwExtStruct) {
        return parse_struct_def(p);
    } else if (t->type.tag == TokenType_TAG_KwEnum) {
        return parse_enum_def(p);
    } else if (t->type.tag == TokenType_TAG_LBrace) {
        advance(p); // consume '{'
        Expr *first = parse_expression(p);
        if (check(p, TokenType_TAG_Colon)) {
            // Map literal: {key: val, ...}
            e = expr_new(NODE_MAP_LIT, t->line, t->col, p->path);
            expr_add_child(e, first);
            advance(p); // consume ':'
            expr_add_child(e, parse_expression(p));
            if (check(p, TokenType_TAG_Comma)) advance(p);
            while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                expr_add_child(e, parse_expression(p));
                expect(p, TokenType_TAG_Colon);
                expr_add_child(e, parse_expression(p));
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
        } else {
            // Set literal: {val, val, ...}
            e = expr_new(NODE_SET_LIT, t->line, t->col, p->path);
            expr_add_child(e, first);
            if (check(p, TokenType_TAG_Comma)) advance(p);
            while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                expr_add_child(e, parse_expression(p));
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
        }
        expect(p, TokenType_TAG_RBrace);
    } else if (t->type.tag == TokenType_TAG_LParen) {
        // Grouping parentheses: (expr)
        advance(p); // consume '('
        e = parse_expression(p);
        expect(p, TokenType_TAG_RParen);
    } else {
        fprintf(stderr, "%s:%lld:%lld: parse error: unexpected token '%.*s'\n",
                p->path->c_str, t->line, t->col, (int)t->text.count, (const char *)t->text.c_str);
        exit(1);
    }

    // field access chain: expr.field.field... or expr.method(args)
    while (check(p, TokenType_TAG_Dot)) {
        advance(p); // consume '.'
        Token *field = expect(p, TokenType_TAG_Ident);
        if (check(p, TokenType_TAG_LParen)) {
            // Method call: expr.method(args)
            advance(p); // consume '('
            Expr *callee = expr_new(NODE_FIELD_ACCESS, field->line, field->col, p->path);
            callee->type.str_val = tok_str(field);
            expr_add_child(callee, e);
            Expr *call = expr_new(NODE_FCALL, field->line, field->col, p->path);
            expr_add_child(call, callee);
            while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
                if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->path);
                    na->type.str_val = tok_str(aname);
                    expr_add_child(na, parse_expression(p));
                    expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TokenType_TAG_KwOwn)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    expr_add_child(call, arg);
                }
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
            expect(p, TokenType_TAG_RParen);
            e = call;
        } else {
            Expr *access = expr_new(NODE_FIELD_ACCESS, field->line, field->col, p->path);
            access->type.str_val = tok_str(field);
            expr_add_child(access, e);
            e = access;
        }
    }
    return e;
}

// Helper: create a method call AST node from a binary operator
// a OP b → a.method(b)
static Expr *make_binop_call(Expr *lhs, const char *method, Token *op, Str *path, Expr *rhs) {
    Expr *callee = expr_new(NODE_FIELD_ACCESS, op->line, op->col, path);
    callee->type.str_val = Str_new(method);
    expr_add_child(callee, lhs);
    Expr *call = expr_new(NODE_FCALL, op->line, op->col, path);
    expr_add_child(call, callee);
    expr_add_child(call, rhs);
    return call;
}

// parse_multiplicative: * / %  (highest precedence binary operators)
static Expr *parse_multiplicative(Parser *p) {
    Expr *e = parse_primary(p);
    while (check(p, TokenType_TAG_Star) || check(p, TokenType_TAG_Slash) || check(p, TokenType_TAG_Percent)) {
        Token *op = advance(p);
        const char *method;
        if (op->type.tag == TokenType_TAG_Star) method = "mul";
        else if (op->type.tag == TokenType_TAG_Slash) method = "div";
        else method = "mod";
        Expr *rhs = parse_primary(p);
        e = make_binop_call(e, method, op, p->path, rhs);
    }
    return e;
}

// parse_additive: + -  (medium precedence)
static Expr *parse_additive(Parser *p) {
    Expr *e = parse_multiplicative(p);
    while (check(p, TokenType_TAG_Plus) || check(p, TokenType_TAG_Minus)) {
        Token *op = advance(p);
        const char *method = (op->type.tag == TokenType_TAG_Plus) ? "add" : "sub";
        Expr *rhs = parse_multiplicative(p);
        e = make_binop_call(e, method, op, p->path, rhs);
    }
    return e;
}

// parse_comparison: == != < <= > >=  (lowest precedence binary operators)
static Expr *parse_comparison(Parser *p) {
    Expr *e = parse_additive(p);
    while (check(p, TokenType_TAG_EqEq) || check(p, TokenType_TAG_Neq) ||
           check(p, TokenType_TAG_Lt) || check(p, TokenType_TAG_LtEq) ||
           check(p, TokenType_TAG_Gt) || check(p, TokenType_TAG_GtEq)) {
        Token *op = advance(p);
        const char *method;
        switch (op->type.tag) {
        case TokenType_TAG_EqEq: method = "eq"; break;
        case TokenType_TAG_Neq:  method = "neq"; break;
        case TokenType_TAG_Lt:   method = "lt"; break;
        case TokenType_TAG_LtEq: method = "lte"; break;
        case TokenType_TAG_Gt:   method = "gt"; break;
        case TokenType_TAG_GtEq: method = "gte"; break;
        default: method = "eq"; break; // unreachable
        }
        Expr *rhs = parse_additive(p);
        e = make_binop_call(e, method, op, p->path, rhs);
    }
    return e;
}

// parse_expression: top-level expression parser (comparison + range)
static Expr *parse_expression(Parser *p) {
    Expr *e = parse_comparison(p);
    // Range expression: expr..expr → Range.new(expr, expr)
    if (check(p, TokenType_TAG_DotDot)) {
        Token *dt = &p->tokens[p->pos];
        advance(p); // consume '..'
        Expr *rhs = parse_expression(p);
        Expr *range_ident = expr_new(NODE_IDENT, dt->line, dt->col, p->path);
        range_ident->type.str_val = Str_new("Range");
        Expr *new_access = expr_new(NODE_FIELD_ACCESS, dt->line, dt->col, p->path);
        new_access->type.str_val = Str_new("new");
        expr_add_child(new_access, range_ident);
        Expr *call = expr_new(NODE_FCALL, dt->line, dt->col, p->path);
        expr_add_child(call, new_access);
        expr_add_child(call, e);
        expr_add_child(call, rhs);
        e = call;
    }
    return e;
}

// parse_statement_ident: identifier is current token
static Expr *parse_statement_ident(Parser *p, I32 is_mut, I32 is_own) {
    Token *t = advance(p); // consume identifier
    Str *name = tok_str(t);

    // Declaration: name := value (inferred type)
    if (check(p, TokenType_TAG_ColonEq)) {
        advance(p); // consume :=
        Expr *decl = expr_new(NODE_DECL, t->line, t->col, p->path);
        decl->type.decl.name = name;
        decl->type.decl.explicit_type = NULL;
        decl->type.decl.is_mut = is_mut;
        decl->type.decl.is_own = is_own;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Declaration with explicit type: name : Type = value
    if (check(p, TokenType_TAG_Colon)) {
        advance(p); // consume :
        Token *type_tok = peek(p);
        Str *type_name = tok_str(type_tok);
        advance(p); // consume type name
        expect(p, TokenType_TAG_Eq); // consume =
        Expr *decl = expr_new(NODE_DECL, t->line, t->col, p->path);
        decl->type.decl.name = name;
        decl->type.decl.explicit_type = type_name;
        decl->type.decl.is_mut = is_mut;
        decl->type.decl.is_own = is_own;
        expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Field assignment or method call: name.field = value  or  name.method(args)
    if (check(p, TokenType_TAG_Dot)) {
        // Build the field access chain
        Expr *obj = expr_new(NODE_IDENT, t->line, t->col, p->path);
        obj->type.str_val = name;
        Token *last_field = NULL;
        while (check(p, TokenType_TAG_Dot)) {
            advance(p); // consume '.'
            last_field = expect(p, TokenType_TAG_Ident);
            if (check(p, TokenType_TAG_Dot)) {
                // More dots coming — this is an intermediate access
                Expr *access = expr_new(NODE_FIELD_ACCESS, last_field->line, last_field->col, p->path);
                access->type.str_val = tok_str(last_field);
                expr_add_child(access, obj);
                obj = access;
            }
        }
        // Method call: name.method(args)
        if (check(p, TokenType_TAG_LParen)) {
            advance(p); // consume '('
            Expr *callee = expr_new(NODE_FIELD_ACCESS, last_field->line, last_field->col, p->path);
            callee->type.str_val = tok_str(last_field);
            expr_add_child(callee, obj);
            Expr *call = expr_new(NODE_FCALL, last_field->line, last_field->col, p->path);
            expr_add_child(call, callee);
            while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
                if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = expr_new(NODE_NAMED_ARG, aname->line, aname->col, p->path);
                    na->type.str_val = tok_str(aname);
                    expr_add_child(na, parse_expression(p));
                    expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TokenType_TAG_KwOwn)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    expr_add_child(call, arg);
                }
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
            expect(p, TokenType_TAG_RParen);
            return call;
        }
        // Field assignment
        expect(p, TokenType_TAG_Eq);
        Expr *fa = expr_new(NODE_FIELD_ASSIGN, t->line, t->col, p->path);
        fa->type.str_val = tok_str(last_field);
        expr_add_child(fa, obj);
        expr_add_child(fa, parse_expression(p));
        return fa;
    }

    // Assignment: name = value
    if (check(p, TokenType_TAG_Eq)) {
        advance(p); // consume =
        Expr *assign = expr_new(NODE_ASSIGN, t->line, t->col, p->path);
        assign->type.str_val = name;
        expr_add_child(assign, parse_expression(p));
        return assign;
    }

    // Function call: name(...)
    if (check(p, TokenType_TAG_LParen)) {
        return parse_call(p, name, t->line, t->col);
    }

    fprintf(stderr, "%s:%lld:%lld: parse error: expected ':=', ':', '=' or '(' after identifier '%s'\n",
            p->path->c_str, t->line, t->col, name->c_str);
    exit(1);
}

static Expr *parse_statement(Parser *p) {
    Token *t = peek(p);

    switch (t->type.tag) {
    case TokenType_TAG_Ident:
        return parse_statement_ident(p, 0, 0);
    case TokenType_TAG_KwRef: {
        advance(p); // consume 'ref'
        bool ref_mut = false;
        if (check(p, TokenType_TAG_KwMut)) {
            advance(p); // consume 'mut'
            ref_mut = true;
        }
        Token *ident = expect(p, TokenType_TAG_Ident);
        Str *name = tok_str(ident);
        Expr *decl = expr_new(NODE_DECL, ident->line, ident->col, p->path);
        decl->type.decl.name = name;
        decl->type.decl.is_ref = true;
        if (ref_mut) decl->type.decl.is_mut = true;
        if (check(p, TokenType_TAG_Colon)) {
            // ref name : Type = expr
            advance(p); // consume :
            Token *type_tok = peek(p);
            decl->type.decl.explicit_type = tok_str(type_tok);
            advance(p); // consume type name
            expect(p, TokenType_TAG_Eq); // consume =
        } else {
            // ref name := expr
            expect(p, TokenType_TAG_ColonEq);
        }
        expr_add_child(decl, parse_expression(p));
        return decl;
    }
    case TokenType_TAG_KwMut: {
        advance(p); // consume 'mut'
        return parse_statement_ident(p, 1, 0);
    }
    case TokenType_TAG_KwReturn: {
        advance(p);
        Expr *ret = expr_new(NODE_RETURN, t->line, t->col, p->path);
        // If next token looks like a value, parse it
        if (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
            expr_add_child(ret, parse_expression(p));
        }
        return ret;
    }
    case TokenType_TAG_KwIf: {
        advance(p); // consume 'if'
        Expr *node = expr_new(NODE_IF, t->line, t->col, p->path);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TokenType_TAG_LBrace);
        expr_add_child(node, parse_block(p));       // then body
        if (check(p, TokenType_TAG_KwElse)) {
            advance(p); // consume 'else'
            if (check(p, TokenType_TAG_KwIf)) {
                // else if → else { if ... }
                Expr *else_body = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->path);
                expr_add_child(else_body, parse_statement(p));
                expr_add_child(node, else_body);
            } else {
                expect(p, TokenType_TAG_LBrace);
                expr_add_child(node, parse_block(p));
            }
        }
        return node;
    }
    case TokenType_TAG_StringTok:
    case TokenType_TAG_Number:
    case TokenType_TAG_KwTrue:
    case TokenType_TAG_KwFalse:
    case TokenType_TAG_KwNull:
    case TokenType_TAG_LParen:
        return parse_expression(p);
    case TokenType_TAG_LBrace: {
        advance(p); // consume '{'
        return parse_block(p);
    }
    case TokenType_TAG_KwWhile: {
        advance(p); // consume 'while'
        Expr *node = expr_new(NODE_WHILE, t->line, t->col, p->path);
        expr_add_child(node, parse_expression(p)); // condition
        expect(p, TokenType_TAG_LBrace);
        expr_add_child(node, parse_block(p));       // body
        return node;
    }
    case TokenType_TAG_KwFor: {
        advance(p); // consume 'for'
        Token *ident = expect(p, TokenType_TAG_Ident);
        Expr *node = expr_new(NODE_FOR_IN, ident->line, ident->col, p->path);
        node->type.str_val = tok_str(ident);
        if (check(p, TokenType_TAG_Colon)) {
            advance(p); // consume ':'
            node->struct_name = tok_str(peek(p)); // explicit element type
            advance(p); // consume type name
        }
        expect(p, TokenType_TAG_KwIn);
        expr_add_child(node, parse_expression(p)); // iterable
        expect(p, TokenType_TAG_LBrace);
        expr_add_child(node, parse_block(p));       // body
        return node;
    }
    case TokenType_TAG_KwSwitch: {
        advance(p); // consume 'switch'
        Expr *node = expr_new(NODE_SWITCH, t->line, t->col, p->path);
        expr_add_child(node, parse_expression(p)); // switch expression
        expect(p, TokenType_TAG_LBrace);
        while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
            expect(p, TokenType_TAG_KwCase);
            Expr *cn = expr_new(NODE_CASE, peek(p)->line, peek(p)->col, p->path);
            if (!check(p, TokenType_TAG_Colon)) {
                expr_add_child(cn, parse_expression(p)); // match value
            }
            expect(p, TokenType_TAG_Colon);
            Expr *cb = expr_new(NODE_BODY, peek(p)->line, peek(p)->col, p->path);
            while (!check(p, TokenType_TAG_KwCase) && !check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                expr_add_child(cb, parse_statement(p));
            }
            expr_add_child(cn, cb);
            expr_add_child(node, cn);
        }
        expect(p, TokenType_TAG_RBrace);
        return node;
    }
    case TokenType_TAG_KwOwn: {
        advance(p); // consume 'own'
        // own field declaration: own name := value  or  own mut name := value
        if (check(p, TokenType_TAG_Ident) || check(p, TokenType_TAG_KwMut)) {
            I32 own_mut = 0;
            if (check(p, TokenType_TAG_KwMut)) { advance(p); own_mut = 1; }
            if (check(p, TokenType_TAG_Ident)) {
                Token *next = &p->tokens[p->pos + 1];
                if (next->type.tag == TokenType_TAG_ColonEq || next->type.tag == TokenType_TAG_Colon) {
                    return parse_statement_ident(p, own_mut, 1);
                }
            }
            // Not a declaration — fall through to own expression
            if (own_mut) {
                // We consumed 'mut' but it's not a declaration — error
                fprintf(stderr, "%s:%lld:%lld: parse error: expected identifier after 'own mut'\n",
                        p->path->c_str, t->line, t->col);
                exit(1);
            }
        }
        // own expression (call-site ownership marker)
        Expr *expr = parse_expression(p);
        Expr *primary = expr;
        while (primary->children.count > 0 &&
               (primary->type.tag == NODE_FCALL || primary->type.tag == NODE_FIELD_ACCESS)) {
            primary = expr_child(primary, 0);
        }
        primary->is_own_arg = true;
        return expr;
    }
    case TokenType_TAG_KwBreak: {
        advance(p);
        return expr_new(NODE_BREAK, t->line, t->col, p->path);
    }
    case TokenType_TAG_KwContinue: {
        advance(p);
        return expr_new(NODE_CONTINUE, t->line, t->col, p->path);
    }
    default:
        fprintf(stderr, "%s:%lld:%lld: parse error: expected statement, found '%.*s'\n",
                p->path->c_str, t->line, t->col, (int)t->text.count, (const char *)t->text.c_str);
        exit(1);
    }
}

Expr *parse(Token *tokens, U32 count, Str *path, Str **mode_out) {
    Parser p = {tokens, count, 0, path};

    // Parse optional mode declaration
    if (mode_out) *mode_out = NULL;
    if (check(&p, TokenType_TAG_KwMode)) {
        advance(&p); // consume 'mode'
        // Accept TOK_IDENT or TOK_TEST (test is both a keyword and a mode name)
        Token *mode_name = (check(&p, TokenType_TAG_Ident) || check(&p, TokenType_TAG_KwTest))
            ? advance(&p) : expect(&p, TokenType_TAG_Ident);
        if (mode_out) *mode_out = tok_str(mode_name);
    }

    // Parse body (top-level statements until EOF)
    Expr *root = expr_new(NODE_BODY, 1, 1, p.path);
    while (!check(&p, TokenType_TAG_Eof)) {
        expr_add_child(root, parse_statement(&p));
    }

    return root;
}
