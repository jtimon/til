#include "parser.h"
#include "../../bootstrap/ast.h"
#include "pre70.h"
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

Token *peek(Parser *p) {
    return &p->tokens[p->pos];
}

Token *advance(Parser *p) {
    Token *t = &p->tokens[p->pos];
    if (t->type.tag != TokenType_TAG_Eof) p->pos++;
    return t;
}

I32 check(Parser *p, TokenType_tag type) {
    return peek(p)->type.tag == type;
}

Token *expect(Parser *p, TokenType_tag type) {
    Token *t = peek(p);
    if (t->type.tag != type) {
        TokenType tt = {type};
        fprintf(stderr, "%s:%u:%u: parse error: expected '%s', found '%.*s'\n",
                p->path->c_str, t->line, t->col,
                tok_name(&tt)->c_str,
                (int)t->text.count, (const char *)t->text.c_str);
        exit(1);
    }
    return advance(p);
}

// Extract a Str from a token.
Str *tok_str(Token *t) {
    return Str_clone(&t->text);
}

// --- Forward declarations ---

Expr *parse_statement(Parser *p);
Expr *parse_expression(Parser *p);

// --- Parsing functions ---

// parse_block: expects '{' already consumed, reads statements until '}'
Expr *parse_block(Parser *p) {
    Expr *body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, peek(p)->line, peek(p)->col, p->path);
    while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
        Expr_add_child(body, parse_statement(p));
    }
    expect(p, TokenType_TAG_RBrace);
    return body;
}

// parse_fn_signature: parse Fn(T1, T2, ...) returns T after "Fn" has been consumed.
// Returns a synthetic ExprData_TAG_FuncDef Expr with param_types and return_type,
// or NULL if not followed by '(' (bare "Fn" type).
Expr *parse_fn_signature(Parser *p, I64 line, I64 col) {
    if (!check(p, TokenType_TAG_LParen)) return NULL;
    advance(p); // consume '('

    // Parse parameter types: [mut] Type, [mut] Type, ...
    Vec ptypes; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); ptypes = *_vp; free(_vp); }
    Vec pmuts; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); pmuts = *_vp; free(_vp); }
    while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
        bool is_mut = false;
        if (check(p, TokenType_TAG_KwMut)) {
            advance(p);
            is_mut = true;
        }
        Token *ptype = expect(p, TokenType_TAG_Ident);
        Str *tp = tok_str(ptype);
        { Str *_p = malloc(sizeof(Str)); *_p = *tp; Vec_push(&ptypes, _p); }
        { Bool *_p = malloc(sizeof(Bool)); *_p = is_mut; Vec_push(&pmuts, _p); }
        if (check(p, TokenType_TAG_Comma)) advance(p);
    }
    expect(p, TokenType_TAG_RParen);

    // Parse optional 'returns Type'
    Str *return_type = NULL;
    if (check(p, TokenType_TAG_KwReturns)) {
        advance(p);
        Token *rt = expect(p, TokenType_TAG_Ident);
        return_type = tok_str(rt);
    }

    // Build synthetic func_def
    Expr *sig = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, p->path);
    sig->data.data.FuncDef.func_type = return_type ? (FuncType){FuncType_TAG_Func} : (FuncType){FuncType_TAG_Proc};
    U32 np_sig = ptypes.count;
    sig->data.data.FuncDef.nparam = np_sig;
    sig->data.data.FuncDef.param_types = ptypes; ptypes = (Vec){0};
    sig->data.data.FuncDef.param_muts = pmuts; pmuts = (Vec){0};
    // Allocate empty arrays for required fields
    sig->data.data.FuncDef.param_names = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); for (U32 _i = 0; _i < (U32)(np_sig); _i++) { Str *_z = calloc(1, sizeof(Str)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
    sig->data.data.FuncDef.param_owns = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); for (U32 _i = 0; _i < (U32)(np_sig); _i++) { Bool *_z = calloc(1, sizeof(Bool)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
    sig->data.data.FuncDef.param_shallows = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); for (U32 _i = 0; _i < (U32)(np_sig); _i++) { Bool *_z = calloc(1, sizeof(Bool)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
    sig->data.data.FuncDef.param_defaults = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(void*)}); for (U32 _i = 0; _i < (U32)(np_sig); _i++) { void* *_z = calloc(1, sizeof(void*)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
    sig->data.data.FuncDef.param_fn_sigs = (Vec){0};
    sig->data.data.FuncDef.return_type = return_type ? *return_type : (Str){0};
    sig->data.data.FuncDef.variadic_index = -1;
    sig->data.data.FuncDef.kwargs_index = -1;
    sig->data.data.FuncDef.return_is_ref = false;
    sig->data.data.FuncDef.return_is_shallow = false;
    // No body — this is just a type signature
    return sig;
}

// parse_func_def: current token is func/proc/etc
Expr *parse_func_def(Parser *p) {
    Token *kw = advance(p); // consume func/proc/etc
    FuncType ft;
    switch (kw->type.tag) {
    case TokenType_TAG_KwFunc:     ft = (FuncType){FuncType_TAG_Func};     break;
    case TokenType_TAG_KwProc:     ft = (FuncType){FuncType_TAG_Proc};     break;
    case TokenType_TAG_KwTest:     ft = (FuncType){FuncType_TAG_Test};     break;
    case TokenType_TAG_KwMacro:    ft = (FuncType){FuncType_TAG_Macro};    break;
    case TokenType_TAG_KwExtFunc:  ft = (FuncType){FuncType_TAG_ExtFunc}; break;
    case TokenType_TAG_KwExtProc:  ft = (FuncType){FuncType_TAG_ExtProc}; break;
    default:
        fprintf(stderr, "%s:%u:%u: parse error: expected function keyword\n",
                p->path->c_str, kw->line, kw->col);
        exit(1);
    }

    expect(p, TokenType_TAG_LParen);

    // Parse parameters: name: Type, name: Type, ...
    Vec pnames; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); pnames = *_vp; free(_vp); }
    Vec ptypes; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); ptypes = *_vp; free(_vp); }
    Vec pmuts; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); pmuts = *_vp; free(_vp); }
    Vec powns; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); powns = *_vp; free(_vp); }
    Vec pdefs; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); pdefs = *_vp; free(_vp); }
    Vec pshallows; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); pshallows = *_vp; free(_vp); }
    Vec pfnsigs; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); pfnsigs = *_vp; free(_vp); }
    I32 variadic_index = -1;
    I32 kwargs_index = -1;
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
        // Bare type (FuncSig style): no colon after identifier
        Str *nm = NULL;
        Str *tp = NULL;
        bool is_this_variadic = false;
        if (!check(p, TokenType_TAG_Colon)) {
            // No colon — this is a bare type, not name: Type
            tp = tok_str(pname);
            nm = &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};  // no param name
        } else {
            expect(p, TokenType_TAG_Colon);
            if (check(p, TokenType_TAG_DotDotDot)) {
                advance(p); // consume '...'
                if (is_own || is_mut || is_shallow) {
                    fprintf(stderr, "%s:%u:%u: parse error: kwargs parameter '%.*s' cannot be own/mut/shallow\n",
                            p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                    exit(1);
                }
                if (kwargs_index >= 0) {
                    fprintf(stderr, "%s:%u:%u: parse error: only one kwargs parameter is allowed\n",
                            p->path->c_str, pname->line, pname->col);
                    exit(1);
                }
                if (variadic_index >= 0) {
                    fprintf(stderr, "%s:%u:%u: parse error: cannot combine variadic and kwargs in the same function\n",
                            p->path->c_str, pname->line, pname->col);
                    exit(1);
                }
                kwargs_index = pnames.count;
                is_own = true; // kwargs Map is owned by callee
                nm = tok_str(pname);
                tp = &(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT}; // implicit type
            } else if (check(p, TokenType_TAG_DotDot)) {
                advance(p); // consume '..'
                if (is_own) {
                    fprintf(stderr, "%s:%u:%u: parse error: variadic parameter '%.*s' cannot be 'own' (implicit)\n",
                            p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                    exit(1);
                }
                if (is_mut) {
                    fprintf(stderr, "%s:%u:%u: parse error: variadic parameter '%.*s' cannot be 'mut'\n",
                            p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                    exit(1);
                }
                if (is_shallow) {
                    fprintf(stderr, "%s:%u:%u: parse error: variadic parameter '%.*s' cannot be 'shallow'\n",
                            p->path->c_str, pname->line, pname->col, (int)pname->text.count, (const char *)pname->text.c_str);
                    exit(1);
                }
                if (variadic_index >= 0) {
                    fprintf(stderr, "%s:%u:%u: parse error: only one variadic parameter is allowed\n",
                            p->path->c_str, pname->line, pname->col);
                    exit(1);
                }
                if (kwargs_index >= 0) {
                    fprintf(stderr, "%s:%u:%u: parse error: cannot combine variadic and kwargs in the same function\n",
                            p->path->c_str, pname->line, pname->col);
                    exit(1);
                }
                variadic_index = pnames.count;
                is_this_variadic = true;
                Token *ptype = expect(p, TokenType_TAG_Ident);
                nm = tok_str(pname);
                tp = tok_str(ptype);
            } else {
                Token *ptype = expect(p, TokenType_TAG_Ident);
                nm = tok_str(pname);
                tp = tok_str(ptype);
            }
        }
        // If type is Fn, try to parse Fn(T1, T2) returns T signature
        Expr *fn_sig = NULL;
        if ((tp->count == 2 && memcmp(tp->c_str, "Fn", 2) == 0)) {
            fn_sig = parse_fn_signature(p, pname->line, pname->col);
        }
        { Str *_p = malloc(sizeof(Str)); *_p = *nm; Vec_push(&pnames, _p); }
        { Str *_p = malloc(sizeof(Str)); *_p = *tp; Vec_push(&ptypes, _p); }
        { Bool *_p = malloc(sizeof(Bool)); *_p = is_mut; Vec_push(&pmuts, _p); }
        { Bool *_p = malloc(sizeof(Bool)); *_p = is_own; Vec_push(&powns, _p); }
        { Bool *_p = malloc(sizeof(Bool)); *_p = is_shallow; Vec_push(&pshallows, _p); }
        { Expr **_p = malloc(sizeof(Expr *)); *_p = fn_sig; Vec_push(&pfnsigs, _p); }
        // Optional default value: name: Type = expr
        Expr *def_val = NULL;
        if (check(p, TokenType_TAG_Eq)) {
            advance(p); // consume '='
            def_val = parse_expression(p);
        }
        if (variadic_index >= 0 && !is_this_variadic && !def_val) {
            fprintf(stderr, "%s:%u:%u: parse error: positional parameter '%.*s' not allowed after variadic\n",
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

    Expr *def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, kw->line, kw->col, p->path);
    def->data.data.FuncDef.func_type = ft;
    def->data.data.FuncDef.nparam = pnames.count;
    def->data.data.FuncDef.param_names = pnames; pnames = (Vec){0};
    def->data.data.FuncDef.param_types = ptypes; ptypes = (Vec){0};
    def->data.data.FuncDef.param_muts = pmuts; pmuts = (Vec){0};
    def->data.data.FuncDef.param_owns = powns; powns = (Vec){0};
    def->data.data.FuncDef.param_shallows = pshallows; pshallows = (Vec){0};
    def->data.data.FuncDef.param_fn_sigs = pfnsigs; pfnsigs = (Vec){0};
    def->data.data.FuncDef.param_defaults = pdefs; pdefs = (Vec){0};
    def->data.data.FuncDef.return_type = return_type ? *return_type : (Str){0};
    def->data.data.FuncDef.return_is_ref = return_is_ref;
    def->data.data.FuncDef.return_is_shallow = return_is_shallow;
    def->data.data.FuncDef.variadic_index = variadic_index;
    def->data.data.FuncDef.kwargs_index = kwargs_index;

    if (check(p, TokenType_TAG_LBrace)) {
        expect(p, TokenType_TAG_LBrace);
        Expr_add_child(def, parse_block(p));
    } else {
        // Bodyless = FuncSig type definition (only for func/proc)
        if (ft.tag != FuncType_TAG_Func && ft.tag != FuncType_TAG_Proc) {
            fprintf(stderr, "%s:%u:%u: parse error: %s requires a body\n",
                    p->path->c_str, kw->line, kw->col,
                    ft.tag == FuncType_TAG_Test ? "test" : "ext_func/ext_proc");
            exit(1);
        }
    }

    return def;
}

// parse_struct_def: current token is 'struct' or 'ext_struct'
Expr *parse_struct_def(Parser *p) {
    Token *kw = advance(p); // consume 'struct' or 'ext_struct'
    bool is_ext = (kw->type.tag == TokenType_TAG_KwExtStruct);
    Expr *def = Expr_new(&(ExprData){.tag = ExprData_TAG_StructDef}, kw->line, kw->col, p->path);
    def->is_ext = is_ext;
    expect(p, TokenType_TAG_LBrace);
    // Parse struct body with namespace: support
    Expr *body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, peek(p)->line, peek(p)->col, p->path);
    I32 in_namespace = 0;
    while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
        if (check(p, TokenType_TAG_KwNamespace)) {
            advance(p); // consume 'namespace'
            expect(p, TokenType_TAG_Colon);
            in_namespace = 1;
            continue;
        }
        Expr *stmt = parse_statement(p);
        if (in_namespace && stmt->data.tag == ExprData_TAG_Decl) {
            stmt->data.data.Decl.is_namespace = true;
        }
        Expr_add_child(body, stmt);
    }
    expect(p, TokenType_TAG_RBrace);
    Expr_add_child(def, body);

    return def;
}

// parse_enum_def: current token is 'enum'
Expr *parse_enum_def(Parser *p) {
    Token *kw = advance(p); // consume 'enum'
    Expr *def = Expr_new(&(ExprData){.tag = ExprData_TAG_EnumDef}, kw->line, kw->col, p->path);
    expect(p, TokenType_TAG_LBrace);
    Expr *body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, peek(p)->line, peek(p)->col, p->path);
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
            if (stmt->data.tag == ExprData_TAG_Decl) {
                stmt->data.data.Decl.is_namespace = true;
            }
            Expr_add_child(body, stmt);
        } else {
            // Variant: bare identifier or Variant: Type, comma-separated
            Token *name = expect(p, TokenType_TAG_Ident);
            Expr *variant = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, name->line, name->col, p->path);
            variant->data.data.Decl.name = *tok_str(name);
            if (check(p, TokenType_TAG_Colon)) {
                advance(p);
                Token *ptype = expect(p, TokenType_TAG_Ident);
                variant->data.data.Decl.explicit_type = *tok_str(ptype);
            }
            Expr_add_child(body, variant);
            if (check(p, TokenType_TAG_Comma)) advance(p);
        }
    }
    expect(p, TokenType_TAG_RBrace);
    Expr_add_child(def, body);
    return def;
}

// parse_call: identifier already consumed, current token is '('
Expr *parse_call(Parser *p, Str *name, I64 line, I64 col) {
    advance(p); // consume '('

    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, p->path);

    // first child is the callee identifier
    Expr *callee = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, p->path);
    callee->data.data.Ident = *name;
    Expr_add_child(call, callee);

    // parse arguments (positional or named: name=expr)
    while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
        // Check for named arg: IDENT '=' expr (peek ahead)
        if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
            p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
            Token *aname = advance(p); // consume ident
            advance(p); // consume '='
            Expr *na = Expr_new(&(ExprData){.tag = ExprData_TAG_NamedArg}, aname->line, aname->col, p->path);
            na->data.data.NamedArg = *tok_str(aname);
            Expr_add_child(na, parse_expression(p));
            Expr_add_child(call, na);
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
            Expr_add_child(call, arg);
        }
        if (check(p, TokenType_TAG_Comma)) advance(p); // skip comma between args
    }
    expect(p, TokenType_TAG_RParen);

    return call;
}

// parse_expression: for now handles literals, identifiers, and calls
Expr *parse_expression(Parser *p) {
    Token *t = peek(p);
    Expr *e = NULL;

    if (t->type.tag == TokenType_TAG_StringTok) {
        advance(p);
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, t->line, t->col, p->path);
        e->data.data.LiteralStr = *tok_str(t);
    } else if (t->type.tag == TokenType_TAG_Number) {
        advance(p);
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, t->line, t->col, p->path);
        e->data.data.LiteralNum = *tok_str(t);
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
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, t->line, t->col, p->path);
        char buf[4];
        snprintf(buf, sizeof(buf), "%u", byte_val);
        e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
        e->til_type = (TilType){TilType_TAG_U8};
    } else if (t->type.tag == TokenType_TAG_KwTrue || t->type.tag == TokenType_TAG_KwFalse) {
        advance(p);
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, t->line, t->col, p->path);
        e->data.data.LiteralBool = *tok_str(t);
    } else if (t->type.tag == TokenType_TAG_KwNull) {
        advance(p);
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNull}, t->line, t->col, p->path);
    } else if (t->type.tag == TokenType_TAG_Ident) {
        advance(p);
        Str *name = tok_str(t);
        // compile-time directives
        if ((name->count == 7 && memcmp(name->c_str, "__LOC__", 7) == 0)) {
            char loc[32];
            snprintf(loc, sizeof(loc), ":%u:%u", t->line, t->col);
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, t->line, t->col, p->path);
            e->data.data.LiteralStr = *Str_concat(p->path, Str_clone(&(Str){.c_str = (U8*)(loc), .count = (U64)strlen((const char*)(loc)), .cap = CAP_VIEW}));
        } else if ((name->count == 8 && memcmp(name->c_str, "__FILE__", 8) == 0)) {
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, t->line, t->col, p->path);
            e->data.data.LiteralStr = *Str_clone(p->path);
        } else if ((name->count == 8 && memcmp(name->c_str, "__LINE__", 8) == 0)) {
            char buf[24];
            snprintf(buf, sizeof(buf), "%u", t->line);
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, t->line, t->col, p->path);
            e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
        } else if ((name->count == 7 && memcmp(name->c_str, "__COL__", 7) == 0)) {
            char buf[24];
            snprintf(buf, sizeof(buf), "%u", t->col);
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, t->line, t->col, p->path);
            e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
        } else if (check(p, TokenType_TAG_LParen)) {
            e = parse_call(p, name, t->line, t->col);
        } else {
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, t->line, t->col, p->path);
            e->data.data.Ident = *name;
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
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_MapLit}, t->line, t->col, p->path);
            Expr_add_child(e, first);
            advance(p); // consume ':'
            Expr_add_child(e, parse_expression(p));
            if (check(p, TokenType_TAG_Comma)) advance(p);
            while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                Expr_add_child(e, parse_expression(p));
                expect(p, TokenType_TAG_Colon);
                Expr_add_child(e, parse_expression(p));
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
        } else {
            // Set literal: {val, val, ...}
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_SetLit}, t->line, t->col, p->path);
            Expr_add_child(e, first);
            if (check(p, TokenType_TAG_Comma)) advance(p);
            while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                Expr_add_child(e, parse_expression(p));
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
        }
        expect(p, TokenType_TAG_RBrace);
    } else {
        fprintf(stderr, "%s:%u:%u: parse error: unexpected token '%.*s'\n",
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
            Expr *callee = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, field->line, field->col, p->path);
            callee->data.data.FieldAccess = *tok_str(field);
            Expr_add_child(callee, e);
            Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, field->line, field->col, p->path);
            Expr_add_child(call, callee);
            while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
                if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = Expr_new(&(ExprData){.tag = ExprData_TAG_NamedArg}, aname->line, aname->col, p->path);
                    na->data.data.NamedArg = *tok_str(aname);
                    Expr_add_child(na, parse_expression(p));
                    Expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TokenType_TAG_KwOwn)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    Expr_add_child(call, arg);
                }
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
            expect(p, TokenType_TAG_RParen);
            e = call;
        } else {
            Expr *access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, field->line, field->col, p->path);
            access->data.data.FieldAccess = *tok_str(field);
            Expr_add_child(access, e);
            e = access;
        }
    }
    // Range expression: expr..expr → Range.new(expr, expr)
    if (check(p, TokenType_TAG_DotDot)) {
        Token *dt = &p->tokens[p->pos];
        advance(p); // consume '..'
        Expr *rhs = parse_expression(p);
        Expr *range_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, dt->line, dt->col, p->path);
        range_ident->data.data.Ident = (Str){.c_str = (U8*)"Range", .count = 5, .cap = CAP_LIT};
        Expr *new_access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, dt->line, dt->col, p->path);
        new_access->data.data.FieldAccess = (Str){.c_str = (U8*)"new", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_access, range_ident);
        Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, dt->line, dt->col, p->path);
        Expr_add_child(call, new_access);
        Expr_add_child(call, e);
        Expr_add_child(call, rhs);
        e = call;
    }
    return e;
}

// parse_statement_ident: identifier is current token
Expr *parse_statement_ident(Parser *p, I32 is_mut, I32 is_own) {
    Token *t = advance(p); // consume identifier
    Str *name = tok_str(t);

    // Declaration: name := value (inferred type)
    if (check(p, TokenType_TAG_ColonEq)) {
        advance(p); // consume :=
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, t->line, t->col, p->path);
        decl->data.data.Decl.name = *name;
        decl->data.data.Decl.explicit_type = (Str){0};
        decl->data.data.Decl.is_mut = is_mut;
        decl->data.data.Decl.is_own = is_own;
        Expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Declaration with explicit type: name : Type = value
    if (check(p, TokenType_TAG_Colon)) {
        advance(p); // consume :

        // FuncSig form: name : func(Types) returns T = (names) { body }
        if (check(p, TokenType_TAG_KwFunc) || check(p, TokenType_TAG_KwProc)) {
            Expr *sig = parse_func_def(p);  // parses bodyless func(I64, I64) returns I64
            expect(p, TokenType_TAG_Eq);    // consume =
            // Parse (name1, name2, ...) — just identifiers
            expect(p, TokenType_TAG_LParen);
            for (U32 i = 0; i < sig->data.data.FuncDef.nparam; i++) {
                if (i > 0) expect(p, TokenType_TAG_Comma);
                Token *pn = expect(p, TokenType_TAG_Ident);
                *((Str*)Vec_get(&sig->data.data.FuncDef.param_names, &(U64){(U64)(i)})) = *tok_str(pn);
            }
            if (check(p, TokenType_TAG_Comma)) advance(p); // trailing comma
            expect(p, TokenType_TAG_RParen);
            // Parse { body }
            expect(p, TokenType_TAG_LBrace);
            Expr_add_child(sig, parse_block(p));
            // Wrap in ExprData_TAG_Decl — same AST as FuncDef form
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, t->line, t->col, p->path);
            decl->data.data.Decl.name = *name;
            decl->data.data.Decl.explicit_type = (Str){0};
            decl->data.data.Decl.is_mut = is_mut;
            decl->data.data.Decl.is_own = is_own;
            Expr_add_child(decl, sig);
            return decl;
        }

        Token *type_tok = peek(p);
        Str *type_name = tok_str(type_tok);
        advance(p); // consume type name
        // If type is Fn, parse optional Fn(T1, T2) returns T signature
        Expr *fn_sig = NULL;
        if ((type_name->count == 2 && memcmp(type_name->c_str, "Fn", 2) == 0)) {
            fn_sig = parse_fn_signature(p, type_tok->line, type_tok->col);
        }
        expect(p, TokenType_TAG_Eq); // consume =

        // Named FuncSig form: name : Type = (names) { body }
        // Lookahead: check if pattern is (ident [, ident]* [,]) {
        if (check(p, TokenType_TAG_LParen)) {
            U32 saved = p->pos;
            advance(p); // skip (
            Bool is_fsf = 1;
            while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
                if (!check(p, TokenType_TAG_Ident)) { is_fsf = 0; break; }
                advance(p);
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
            if (is_fsf && check(p, TokenType_TAG_RParen)) {
                advance(p); // skip )
                if (!check(p, TokenType_TAG_LBrace)) is_fsf = 0;
            } else {
                is_fsf = 0;
            }
            p->pos = saved; // restore

            if (is_fsf) {
                // Parse (name1, name2, ...) as param names
                expect(p, TokenType_TAG_LParen);
                Vec pnames; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); pnames = *_vp; free(_vp); }
                while (!check(p, TokenType_TAG_RParen)) {
                    Token *pn = expect(p, TokenType_TAG_Ident);
                    { Str *_p = malloc(sizeof(Str)); *_p = *tok_str(pn); Vec_push(&pnames, _p); }
                    if (check(p, TokenType_TAG_Comma)) advance(p);
                }
                expect(p, TokenType_TAG_RParen);
                // Parse { body }
                expect(p, TokenType_TAG_LBrace);
                Expr *body = parse_block(p);
                // Build incomplete ExprData_TAG_FuncDef (types filled by initer)
                Expr *def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, t->line, t->col, p->path);
                U32 np = pnames.count;
                def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func}; // placeholder
                def->data.data.FuncDef.nparam = np;
                def->data.data.FuncDef.param_names = pnames; pnames = (Vec){0};
                def->data.data.FuncDef.param_types = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); for (U32 _i = 0; _i < (U32)(np); _i++) { Str *_z = calloc(1, sizeof(Str)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
                def->data.data.FuncDef.param_muts = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); for (U32 _i = 0; _i < (U32)(np); _i++) { Bool *_z = calloc(1, sizeof(Bool)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
                def->data.data.FuncDef.param_owns = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); for (U32 _i = 0; _i < (U32)(np); _i++) { Bool *_z = calloc(1, sizeof(Bool)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
                def->data.data.FuncDef.param_shallows = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}, &(U64){sizeof(Bool)}); for (U32 _i = 0; _i < (U32)(np); _i++) { Bool *_z = calloc(1, sizeof(Bool)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
                def->data.data.FuncDef.param_fn_sigs = (Vec){0};
                def->data.data.FuncDef.param_defaults = ({ Vec *_v = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(void*)}); for (U32 _i = 0; _i < (U32)(np); _i++) { void* *_z = calloc(1, sizeof(void*)); Vec_push(_v, _z); } Vec _r = *_v; free(_v); _r; });
                def->data.data.FuncDef.return_type = (Str){0};
                def->data.data.FuncDef.variadic_index = -1;
                def->data.data.FuncDef.kwargs_index = -1;
                Expr_add_child(def, body);
                // Wrap in ExprData_TAG_Decl with explicit_type (initer fills types)
                Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, t->line, t->col, p->path);
                decl->data.data.Decl.name = *name;
                decl->data.data.Decl.explicit_type = *type_name;
                decl->data.data.Decl.is_mut = is_mut;
                decl->data.data.Decl.is_own = is_own;
                Expr_add_child(decl, def);
                return decl;
            }
        }

        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, t->line, t->col, p->path);
        decl->data.data.Decl.name = *name;
        decl->data.data.Decl.explicit_type = *type_name;
        decl->data.data.Decl.fn_sig = fn_sig;
        decl->data.data.Decl.is_mut = is_mut;
        decl->data.data.Decl.is_own = is_own;
        Expr_add_child(decl, parse_expression(p));
        return decl;
    }

    // Field assignment or method call: name.field = value  or  name.method(args)
    if (check(p, TokenType_TAG_Dot)) {
        // Build the field access chain
        Expr *obj = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, t->line, t->col, p->path);
        obj->data.data.Ident = *name;
        Token *last_field = NULL;
        while (check(p, TokenType_TAG_Dot)) {
            advance(p); // consume '.'
            last_field = expect(p, TokenType_TAG_Ident);
            if (check(p, TokenType_TAG_Dot)) {
                // More dots coming — this is an intermediate access
                Expr *access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, last_field->line, last_field->col, p->path);
                access->data.data.FieldAccess = *tok_str(last_field);
                Expr_add_child(access, obj);
                obj = access;
            }
        }
        // Method call: name.method(args)
        if (check(p, TokenType_TAG_LParen)) {
            advance(p); // consume '('
            Expr *callee = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, last_field->line, last_field->col, p->path);
            callee->data.data.FieldAccess = *tok_str(last_field);
            Expr_add_child(callee, obj);
            Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, last_field->line, last_field->col, p->path);
            Expr_add_child(call, callee);
            while (!check(p, TokenType_TAG_RParen) && !check(p, TokenType_TAG_Eof)) {
                if (check(p, TokenType_TAG_Ident) && p->pos + 1 < p->count &&
                    p->tokens[p->pos + 1].type.tag == TokenType_TAG_Eq) {
                    Token *aname = advance(p);
                    advance(p);
                    Expr *na = Expr_new(&(ExprData){.tag = ExprData_TAG_NamedArg}, aname->line, aname->col, p->path);
                    na->data.data.NamedArg = *tok_str(aname);
                    Expr_add_child(na, parse_expression(p));
                    Expr_add_child(call, na);
                } else {
                    bool is_own_arg = false;
                    if (check(p, TokenType_TAG_KwOwn)) {
                        advance(p);
                        is_own_arg = true;
                    }
                    Expr *arg = parse_expression(p);
                    arg->is_own_arg = is_own_arg;
                    Expr_add_child(call, arg);
                }
                if (check(p, TokenType_TAG_Comma)) advance(p);
            }
            expect(p, TokenType_TAG_RParen);
            return call;
        }
        // Field assignment
        expect(p, TokenType_TAG_Eq);
        Expr *fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAssign}, t->line, t->col, p->path);
        fa->data.data.FieldAssign = *tok_str(last_field);
        Expr_add_child(fa, obj);
        Expr_add_child(fa, parse_expression(p));
        return fa;
    }

    // Assignment: name = value
    if (check(p, TokenType_TAG_Eq)) {
        advance(p); // consume =
        Expr *assign = Expr_new(&(ExprData){.tag = ExprData_TAG_Assign}, t->line, t->col, p->path);
        assign->data.data.Assign = *name;
        Expr_add_child(assign, parse_expression(p));
        return assign;
    }

    // Function call: name(...)
    if (check(p, TokenType_TAG_LParen)) {
        return parse_call(p, name, t->line, t->col);
    }

    fprintf(stderr, "%s:%u:%u: parse error: expected ':=', ':', '=' or '(' after identifier '%s'\n",
            p->path->c_str, t->line, t->col, name->c_str);
    exit(1);
}

Expr *parse_statement(Parser *p) {
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
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, ident->line, ident->col, p->path);
        decl->data.data.Decl.name = *name;
        decl->data.data.Decl.is_ref = true;
        if (ref_mut) decl->data.data.Decl.is_mut = true;
        if (check(p, TokenType_TAG_Colon)) {
            // ref name : Type = expr
            advance(p); // consume :
            Token *type_tok = peek(p);
            decl->data.data.Decl.explicit_type = *tok_str(type_tok);
            advance(p); // consume type name
            expect(p, TokenType_TAG_Eq); // consume =
        } else {
            // ref name := expr
            expect(p, TokenType_TAG_ColonEq);
        }
        Expr_add_child(decl, parse_expression(p));
        return decl;
    }
    case TokenType_TAG_KwMut: {
        advance(p); // consume 'mut'
        return parse_statement_ident(p, 1, 0);
    }
    case TokenType_TAG_KwReturn: {
        advance(p);
        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, t->line, t->col, p->path);
        // If next token looks like a value, parse it
        if (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
            Expr_add_child(ret, parse_expression(p));
        }
        return ret;
    }
    case TokenType_TAG_KwIf: {
        advance(p); // consume 'if'
        Expr *node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, t->line, t->col, p->path);
        Expr_add_child(node, parse_expression(p)); // condition
        expect(p, TokenType_TAG_LBrace);
        Expr_add_child(node, parse_block(p));       // then body
        if (check(p, TokenType_TAG_KwElse)) {
            advance(p); // consume 'else'
            if (check(p, TokenType_TAG_KwIf)) {
                // else if → else { if ... }
                Expr *else_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, peek(p)->line, peek(p)->col, p->path);
                Expr_add_child(else_body, parse_statement(p));
                Expr_add_child(node, else_body);
            } else {
                expect(p, TokenType_TAG_LBrace);
                Expr_add_child(node, parse_block(p));
            }
        }
        return node;
    }
    case TokenType_TAG_StringTok:
    case TokenType_TAG_Number:
    case TokenType_TAG_KwTrue:
    case TokenType_TAG_KwFalse:
    case TokenType_TAG_KwNull:
        return parse_expression(p);
    case TokenType_TAG_LBrace: {
        advance(p); // consume '{'
        return parse_block(p);
    }
    case TokenType_TAG_KwWhile: {
        advance(p); // consume 'while'
        Expr *node = Expr_new(&(ExprData){.tag = ExprData_TAG_While}, t->line, t->col, p->path);
        Expr_add_child(node, parse_expression(p)); // condition
        expect(p, TokenType_TAG_LBrace);
        Expr_add_child(node, parse_block(p));       // body
        return node;
    }
    case TokenType_TAG_KwFor: {
        advance(p); // consume 'for'
        Token *ident = expect(p, TokenType_TAG_Ident);
        Expr *node = Expr_new(&(ExprData){.tag = ExprData_TAG_ForIn}, ident->line, ident->col, p->path);
        node->data.data.ForIn = *tok_str(ident);
        if (check(p, TokenType_TAG_Colon)) {
            advance(p); // consume ':'
            node->struct_name = *tok_str(peek(p)); // explicit element type
            advance(p); // consume type name
        }
        expect(p, TokenType_TAG_KwIn);
        Expr_add_child(node, parse_expression(p)); // iterable
        expect(p, TokenType_TAG_LBrace);
        Expr_add_child(node, parse_block(p));       // body
        return node;
    }
    case TokenType_TAG_KwSwitch: {
        advance(p); // consume 'switch'
        Expr *node = Expr_new(&(ExprData){.tag = ExprData_TAG_Switch}, t->line, t->col, p->path);
        Expr_add_child(node, parse_expression(p)); // switch expression
        expect(p, TokenType_TAG_LBrace);
        while (!check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
            expect(p, TokenType_TAG_KwCase);
            Expr *cn = Expr_new(&(ExprData){.tag = ExprData_TAG_Case}, peek(p)->line, peek(p)->col, p->path);
            if (!check(p, TokenType_TAG_Colon)) {
                Expr_add_child(cn, parse_expression(p)); // match value
            }
            expect(p, TokenType_TAG_Colon);
            Expr *cb = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, peek(p)->line, peek(p)->col, p->path);
            while (!check(p, TokenType_TAG_KwCase) && !check(p, TokenType_TAG_RBrace) && !check(p, TokenType_TAG_Eof)) {
                Expr_add_child(cb, parse_statement(p));
            }
            Expr_add_child(cn, cb);
            Expr_add_child(node, cn);
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
                fprintf(stderr, "%s:%u:%u: parse error: expected identifier after 'own mut'\n",
                        p->path->c_str, t->line, t->col);
                exit(1);
            }
        }
        // own expression (call-site ownership marker)
        Expr *expr = parse_expression(p);
        Expr *primary = expr;
        while (primary->children.count > 0 &&
               (primary->data.tag == ExprData_TAG_FCall || primary->data.tag == ExprData_TAG_FieldAccess)) {
            primary = Expr_child(primary, &(I64){(I64)(0)});
        }
        primary->is_own_arg = true;
        return expr;
    }
    case TokenType_TAG_KwBreak: {
        advance(p);
        return Expr_new(&(ExprData){.tag = ExprData_TAG_Break}, t->line, t->col, p->path);
    }
    case TokenType_TAG_KwContinue: {
        advance(p);
        return Expr_new(&(ExprData){.tag = ExprData_TAG_Continue}, t->line, t->col, p->path);
    }
    default:
        fprintf(stderr, "%s:%u:%u: parse error: expected statement, found '%.*s'\n",
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
    Expr *root = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, 1, 1, p.path);
    while (!check(&p, TokenType_TAG_Eof)) {
        Expr_add_child(root, parse_statement(&p));
    }

    return root;
}
