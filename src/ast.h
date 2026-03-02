#ifndef TIL_AST_H
#define TIL_AST_H

#include <stdbool.h>

typedef enum {
    NODE_BODY,          // list of statements (children = statements)
    NODE_LITERAL_STR,   // string literal (data.str_val)
    NODE_LITERAL_NUM,   // number literal (data.str_val)
    NODE_IDENT,         // identifier (data.str_val)
    NODE_DECL,          // declaration :=  (data.decl, children[0] = value)
    NODE_ASSIGN,        // assignment =    (data.str_val = name, children[0] = value)
    NODE_FCALL,         // function call   (children[0] = callee ident, children[1..] = args)
    NODE_FUNC_DEF,      // func/proc def   (data.func_def, children[0] = body)
    NODE_RETURN,        // return           (children[0] = value, if any)
    NODE_IF,            // if               (children[0] = cond, [1] = then body, [2] = else body)
    NODE_WHILE,         // while            (children[0] = cond, [1] = body)
    NODE_FOR_IN,        // for x in ...     (data.str_val = var name, children[0] = iter, [1] = body)
    NODE_BREAK,
    NODE_CONTINUE,
} NodeType;

typedef enum {
    FUNC_FUNC,
    FUNC_PROC,
    FUNC_MACRO,
    FUNC_EXT_FUNC,
    FUNC_EXT_PROC,
} FuncType;

typedef struct Expr Expr;

struct Expr {
    NodeType type;
    union {
        const char *str_val;        // for IDENT, LITERAL_STR, LITERAL_NUM, ASSIGN, FOR_IN
        struct {                    // for DECL
            const char *name;
            bool is_mut;
        } decl;
        struct {                    // for FUNC_DEF
            FuncType func_type;
        } func_def;
    } data;
    Expr **children;                // malloc'd array of child pointers
    int nchildren;
    int line;
    int col;
};

// Allocate a new Expr node
Expr *expr_new(NodeType type, int line, int col);

// Add a child to an Expr
void expr_add_child(Expr *parent, Expr *child);

// Free an Expr tree recursively
void expr_free(Expr *e);

// Print an AST tree (for debugging)
void ast_print(Expr *e, int indent);

#endif
