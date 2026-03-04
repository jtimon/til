#ifndef TIL_LEXER_H
#define TIL_LEXER_H

typedef enum {
    TOK_EOF,

    // Single-character
    TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACE, TOK_RBRACE,
    TOK_LBRACKET, TOK_RBRACKET,
    TOK_COMMA, TOK_COLON,
    TOK_QUESTION, TOK_BANG,
    TOK_MINUS, TOK_PLUS, TOK_STAR, TOK_SLASH,

    // One or two character
    TOK_DOT, TOK_DOTDOT,
    TOK_EQ, TOK_EQEQ,
    TOK_NEQ,
    TOK_LT, TOK_LTEQ,
    TOK_GT, TOK_GTEQ,

    // Assignment
    TOK_COLONEQ,   // :=

    // Literals
    TOK_IDENT, TOK_STRING, TOK_NUMBER,

    // Keywords
    TOK_MODE,
    TOK_MUT, TOK_OWN,
    TOK_STRUCT, TOK_EXT_STRUCT, TOK_ENUM, TOK_NAMESPACE,
    TOK_FUNC, TOK_PROC, TOK_MACRO, TOK_EXT_FUNC, TOK_EXT_PROC,
    TOK_RETURNS, TOK_THROWS,
    TOK_IF, TOK_ELSE,
    TOK_WHILE, TOK_FOR, TOK_IN,
    TOK_SWITCH, TOK_MATCH, TOK_CASE, TOK_DEFAULT,
    TOK_RETURN, TOK_THROW, TOK_CATCH,
    TOK_BREAK, TOK_CONTINUE, TOK_DEFER,
    TOK_TRUE, TOK_FALSE,

    // Error tokens (forbidden keywords, invalid chars, etc.)
    TOK_ERROR,
} TokenType;

typedef struct {
    TokenType type;
    const char *start;  // pointer into source buffer
    int len;            // length of lexeme
    int line;
    int col;
} Token;

// Returns a null-terminated name for a token type (for debug printing)
const char *tok_name(TokenType type);

// Tokenize a source string. Returns a malloc'd array of tokens ending with TOK_EOF.
// The caller owns the returned array. `path` is used for error messages.
// `count_out` receives the number of tokens (including TOK_EOF).
Token *tokenize(const char *source, const char *path, int *count_out);

#endif
