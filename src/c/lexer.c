#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

const char *tok_name(TokenType type) {
    switch (type) {
    case TOK_EOF:       return "eof";
    case TOK_LPAREN:    return "(";
    case TOK_RPAREN:    return ")";
    case TOK_LBRACE:    return "{";
    case TOK_RBRACE:    return "}";
    case TOK_LBRACKET:  return "[";
    case TOK_RBRACKET:  return "]";
    case TOK_COMMA:     return ",";
    case TOK_COLON:     return ":";
    case TOK_QUESTION:  return "?";
    case TOK_BANG:      return "!";
    case TOK_MINUS:     return "-";
    case TOK_PLUS:      return "+";
    case TOK_STAR:      return "*";
    case TOK_SLASH:     return "/";
    case TOK_DOT:       return ".";
    case TOK_DOTDOT:    return "..";
    case TOK_EQ:        return "=";
    case TOK_EQEQ:     return "==";
    case TOK_NEQ:       return "!=";
    case TOK_LT:        return "<";
    case TOK_LTEQ:      return "<=";
    case TOK_GT:        return ">";
    case TOK_GTEQ:      return ">=";
    case TOK_COLONEQ:   return ":=";
    case TOK_IDENT:     return "identifier";
    case TOK_STRING:    return "string";
    case TOK_NUMBER:    return "number";
    case TOK_CHAR:      return "char";
    case TOK_MODE:      return "mode";
    case TOK_MUT:       return "mut";
    case TOK_OWN:       return "own";
    case TOK_REF:       return "ref";
    case TOK_SHALLOW:   return "shallow";
    case TOK_STRUCT:     return "struct";
    case TOK_EXT_STRUCT: return "ext_struct";
    case TOK_ENUM:      return "enum";
    case TOK_NAMESPACE: return "namespace";
    case TOK_FUNC:      return "func";
    case TOK_PROC:      return "proc";
    case TOK_TEST:      return "test";
    case TOK_MACRO:     return "macro";
    case TOK_EXT_FUNC:  return "ext_func";
    case TOK_EXT_PROC:  return "ext_proc";
    case TOK_RETURNS:   return "returns";
    case TOK_THROWS:    return "throws";
    case TOK_IF:        return "if";
    case TOK_ELSE:      return "else";
    case TOK_WHILE:     return "while";
    case TOK_FOR:       return "for";
    case TOK_IN:        return "in";
    case TOK_SWITCH:    return "switch";
    case TOK_MATCH:     return "match";
    case TOK_CASE:      return "case";
    case TOK_DEFAULT:   return "default";
    case TOK_RETURN:    return "return";
    case TOK_THROW:     return "throw";
    case TOK_CATCH:     return "catch";
    case TOK_BREAK:     return "break";
    case TOK_CONTINUE:  return "continue";
    case TOK_DEFER:     return "defer";
    case TOK_TRUE:      return "true";
    case TOK_FALSE:     return "false";
    case TOK_NULL:      return "NULL";
    case TOK_ERROR:     return "error";
    }
    return "?";
}

// --- Keyword lookup ---

typedef struct {
    const char *word;
    TokenType type;
} Keyword;

static const Keyword keywords[] = {
    {"mode",      TOK_MODE},
    {"mut",       TOK_MUT},
    {"own",       TOK_OWN},
    {"ref",       TOK_REF},
    {"shallow",   TOK_SHALLOW},
    {"struct",     TOK_STRUCT},
    {"ext_struct", TOK_EXT_STRUCT},
    {"enum",      TOK_ENUM},
    {"namespace", TOK_NAMESPACE},
    {"func",      TOK_FUNC},
    {"proc",      TOK_PROC},
    {"test",      TOK_TEST},
    {"macro",     TOK_MACRO},
    {"ext_func",  TOK_EXT_FUNC},
    {"ext_proc",  TOK_EXT_PROC},
    {"returns",   TOK_RETURNS},
    {"throws",    TOK_THROWS},
    {"if",        TOK_IF},
    {"else",      TOK_ELSE},
    {"while",     TOK_WHILE},
    {"for",       TOK_FOR},
    {"in",        TOK_IN},
    {"switch",    TOK_SWITCH},
    {"match",     TOK_MATCH},
    {"case",      TOK_CASE},
    {"default",   TOK_DEFAULT},
    {"return",    TOK_RETURN},
    {"throw",     TOK_THROW},
    {"catch",     TOK_CATCH},
    {"break",     TOK_BREAK},
    {"continue",  TOK_CONTINUE},
    {"defer",     TOK_DEFER},
    {"true",      TOK_TRUE},
    {"false",     TOK_FALSE},
    {"NULL",      TOK_NULL},
    {NULL, TOK_EOF},
};

static TokenType lookup_keyword(const char *start, I32 len) {
    for (const Keyword *kw = keywords; kw->word; kw++) {
        if ((I32)strlen(kw->word) == len && memcmp(kw->word, start, len) == 0) {
            return kw->type;
        }
    }
    return TOK_IDENT;
}

// --- Tokenizer ---

Token *tokenize(const char *source, Str *path, U32 *count_out) {
    Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Token)}); Vec tokens = *_vp; free(_vp);
    const char *pos = source;
    U32 line = 1;
    const char *line_start = source;

    while (*pos) {
        // Skip whitespace (spaces, tabs, \r, semicolons)
        if (*pos == ' ' || *pos == '\t' || *pos == '\r' || *pos == ';') {
            pos++;
            continue;
        }
        if (*pos == '\n') {
            pos++;
            line++;
            line_start = pos;
            continue;
        }

        U32 col = (U32)(pos - line_start) + 1;
        const char *start = pos;

        // Line comments: // or #
        if ((*pos == '/' && pos[1] == '/') || *pos == '#') {
            while (*pos && *pos != '\n') pos++;
            continue;
        }

        // Block comments: /* ... */ (nestable)
        if (*pos == '/' && pos[1] == '*') {
            pos += 2;
            I32 depth = 1;
            while (*pos && depth > 0) {
                if (pos[0] == '/' && pos[1] == '*') { depth++; pos += 2; }
                else if (pos[0] == '*' && pos[1] == '/') { depth--; pos += 2; }
                else { if (*pos == '\n') { line++; line_start = pos + 1; } pos++; }
            }
            if (depth > 0) {
                fprintf(stderr, "%s:%u:%u: error: unterminated comment\n", path->c_str, line, col);
            }
            continue;
        }

        // Numbers
        if (isdigit(*pos)) {
            while (isdigit(*pos)) pos++;
            if (*pos == '.' && isdigit(pos[1])) {
                pos++;
                while (isdigit(*pos)) pos++;
            }
            { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_NUMBER, start, (I32)(pos - start), line, col}; Vec_push(&tokens, _p); }
            continue;
        }

        // Identifiers and keywords
        if (isalpha(*pos) || *pos == '_') {
            while (isalpha(*pos) || isdigit(*pos) || *pos == '_') pos++;
            I32 len = (I32)(pos - start);
            TokenType type = lookup_keyword(start, len);
            { Token *_p = malloc(sizeof(Token)); *_p = (Token){type, start, len, line, col}; Vec_push(&tokens, _p); }
            continue;
        }

        // Strings
        if (*pos == '"') {
            pos++; // skip opening quote
            while (*pos && *pos != '"') {
                if (*pos == '\\' && pos[1]) pos++; // skip escaped char
                if (*pos == '\n') { line++; line_start = pos + 1; }
                pos++;
            }
            if (*pos == '"') {
                pos++; // skip closing quote
                // start+1 to skip opening quote, len excludes both quotes
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_STRING, start + 1, (I32)(pos - start - 2), line, col}; Vec_push(&tokens, _p); }
            } else {
                fprintf(stderr, "%s:%u:%u: error: unterminated string\n", path->c_str, line, col);
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_ERROR, start, (I32)(pos - start), line, col}; Vec_push(&tokens, _p); }
            }
            continue;
        }

        // Character literals: 'x' or '\n'
        if (*pos == '\'') {
            pos++; // skip opening quote
            const char *ch_start = pos;
            if (*pos == '\\' && pos[1]) pos++; // skip escaped char
            pos++; // skip the character
            if (*pos == '\'') {
                I32 ch_len = (I32)(pos - ch_start);
                pos++; // skip closing quote
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_CHAR, ch_start, ch_len, line, col}; Vec_push(&tokens, _p); }
            } else {
                fprintf(stderr, "%s:%u:%u: error: unterminated character literal\n", path->c_str, line, col);
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_ERROR, start, (I32)(pos - start), line, col}; Vec_push(&tokens, _p); }
            }
            continue;
        }

        // Two-character tokens
        if (pos[1]) {
            TokenType two = TOK_EOF;
            if      (pos[0] == ':' && pos[1] == '=') two = TOK_COLONEQ;
            else if (pos[0] == '=' && pos[1] == '=') two = TOK_EQEQ;
            else if (pos[0] == '!' && pos[1] == '=') two = TOK_NEQ;
            else if (pos[0] == '<' && pos[1] == '=') two = TOK_LTEQ;
            else if (pos[0] == '>' && pos[1] == '=') two = TOK_GTEQ;
            else if (pos[0] == '.' && pos[1] == '.') two = TOK_DOTDOT;
            if (two != TOK_EOF) {
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){two, start, 2, line, col}; Vec_push(&tokens, _p); }
                pos += 2;
                continue;
            }
        }

        // Single-character tokens
        {
            TokenType single = TOK_EOF;
            switch (*pos) {
            case '(': single = TOK_LPAREN;   break;
            case ')': single = TOK_RPAREN;   break;
            case '{': single = TOK_LBRACE;   break;
            case '}': single = TOK_RBRACE;   break;
            case '[': single = TOK_LBRACKET; break;
            case ']': single = TOK_RBRACKET; break;
            case ',': single = TOK_COMMA;    break;
            case ':': single = TOK_COLON;    break;
            case '.': single = TOK_DOT;      break;
            case '?': single = TOK_QUESTION; break;
            case '!': single = TOK_BANG;     break;
            case '+': single = TOK_PLUS;     break;
            case '-': single = TOK_MINUS;    break;
            case '*': single = TOK_STAR;     break;
            case '/': single = TOK_SLASH;    break;
            case '=': single = TOK_EQ;       break;
            case '<': single = TOK_LT;       break;
            case '>': single = TOK_GT;       break;
            default: break;
            }
            if (single != TOK_EOF) {
                { Token *_p = malloc(sizeof(Token)); *_p = (Token){single, start, 1, line, col}; Vec_push(&tokens, _p); }
                pos++;
                continue;
            }
        }

        // Unknown character
        fprintf(stderr, "%s:%u:%u: error: unexpected character '%c'\n", path->c_str, line, col, *pos);
        { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_ERROR, start, 1, line, col}; Vec_push(&tokens, _p); }
        pos++;
    }

    // EOF
    U32 col = (U32)(pos - line_start) + 1;
    { Token *_p = malloc(sizeof(Token)); *_p = (Token){TOK_EOF, pos, 0, line, col}; Vec_push(&tokens, _p); }

    if (count_out) *count_out = tokens.count;
    return Vec_take(&tokens);
}
