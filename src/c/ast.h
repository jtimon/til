#ifndef TIL_AST_H
#define TIL_AST_H

#include <stdbool.h>
#include <stddef.h>
#include "ccore.h"

typedef enum {
    NODE_BODY,          // list of statements (children = statements)
    NODE_LITERAL_STR,   // string literal (data.str_val)
    NODE_LITERAL_NUM,   // number literal (data.str_val)
    NODE_LITERAL_BOOL,  // bool literal (data.str_val = "true"/"false")
    NODE_IDENT,         // identifier (data.str_val)
    NODE_DECL,          // declaration :=  (data.decl, children[0] = value)
    NODE_ASSIGN,        // assignment =    (data.str_val = name, children[0] = value)
    NODE_FCALL,         // function call   (children[0] = callee ident, children[1..] = args)
    NODE_FUNC_DEF,      // func/proc def   (data.func_def, children[0] = body)
    NODE_STRUCT_DEF,    // struct def       (children[0] = body of NODE_DECL fields)
    NODE_ENUM_DEF,      // enum def        (children[0] = body of variant + namespace decls)
    NODE_FIELD_ACCESS,  // field access     (children[0] = object expr, data.str_val = field name)
    NODE_FIELD_ASSIGN,  // field assign     (children[0] = object expr, children[1] = value, data.str_val = field name)
    NODE_RETURN,        // return           (children[0] = value, if any)
    NODE_IF,            // if               (children[0] = cond, [1] = then body, [2] = else body)
    NODE_WHILE,         // while            (children[0] = cond, [1] = body)
    NODE_FOR_IN,        // for x in ...     (data.str_val = var name, children[0] = iter, [1] = body)
    NODE_NAMED_ARG,     // named argument   (data.str_val = param name, children[0] = value)
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

// Resolved type annotation (filled in by typer pass)
typedef enum {
    TIL_TYPE_UNKNOWN,   // not yet resolved
    TIL_TYPE_NONE,      // void / no value
    TIL_TYPE_I64,
    TIL_TYPE_U8,
    TIL_TYPE_STR,
    TIL_TYPE_BOOL,
    TIL_TYPE_STRUCT,
    TIL_TYPE_STRUCT_DEF,
    TIL_TYPE_ENUM,
    TIL_TYPE_ENUM_DEF,
    TIL_TYPE_FUNC_DEF,
    TIL_TYPE_DYNAMIC,
} TilType;

const char *til_type_name_c(TilType t);

typedef struct Expr Expr;

struct Expr {
    NodeType type;
    TilType til_type;               // resolved type (set by typer)
    union {
        Str *str_val;               // for IDENT, LITERAL_STR, LITERAL_NUM, ASSIGN, FOR_IN
        struct {                    // for DECL
            Str *name;
            Str *explicit_type;    // NULL if inferred (:=), e.g. "I64", "Str"
            bool is_mut;
            bool is_namespace;     // true for fields after namespace: in a struct
            bool is_ref;           // true for ref declarations (borrowed, no delete)
            bool is_own;           // true for own field declarations (heap pointer)
        } decl;
        struct {                    // for FUNC_DEF
            FuncType func_type;
            Str **param_names;
            Str **param_types;     // type name strings: "I64", "Str", etc.
            bool *param_muts;        // true for mut params
            bool *param_owns;        // true for own params
            int nparam;
            Expr **param_defaults;    // array[nparam], NULL entries for required params
            Str *return_type;      // NULL if none (proc)
            bool is_variadic;         // true if last param is variadic (..Type)
            bool return_is_ref;       // true for `returns ref Type`
        } func_def;
    } data;
    Str *struct_name;               // for TIL_TYPE_STRUCT: which struct type
    bool is_own_arg;                // true if this arg was marked 'own' at call site
    bool is_own_field;              // NODE_FIELD_ACCESS/ASSIGN: field is 'own' (pointer)
    bool is_ns_field;               // NODE_FIELD_ACCESS/ASSIGN: namespace field (not instance)
    bool is_ext;                    // NODE_STRUCT_DEF: externally-implemented struct
    Expr **children;                // malloc'd array of child pointers
    int nchildren;
    int line;
    int col;
};

// Allocate a new Expr node
Expr *expr_new(NodeType type, int line, int col);

// Add a child to an Expr
void expr_add_child(Expr *parent, Expr *child);

// Deep-clone an Expr tree
Expr *expr_clone(Expr *e);

// Free an Expr tree recursively
void expr_free(Expr *e);

// Print an AST tree (for debugging)
void ast_print(Expr *e, int indent);

// --- Enum helpers (shared by interpreter, ccodegen, precomp) ---

// Check if an enum def has payload variants (any non-namespace decl with explicit_type)
static inline int enum_has_payloads(Expr *enum_def) {
    Expr *body = enum_def->children[0];
    for (int i = 0; i < body->nchildren; i++) {
        Expr *f = body->children[i];
        if (f->type == NODE_DECL && !f->data.decl.is_namespace && f->data.decl.explicit_type)
            return 1;
    }
    return 0;
}

// Find tag index for a variant name in an enum def (scan non-namespace entries)
static inline int enum_variant_tag(Expr *enum_def, Str *variant_name) {
    Expr *body = enum_def->children[0];
    int tag = 0;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *f = body->children[i];
        if (f->type == NODE_DECL && !f->data.decl.is_namespace) {
            if (Str_eq(f->data.decl.name, variant_name)) return tag;
            tag++;
        }
    }
    return -1;
}

// Find payload type string for a variant (NULL if no payload)
static inline Str *enum_variant_type(Expr *enum_def, int tag) {
    Expr *body = enum_def->children[0];
    int idx = 0;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *f = body->children[i];
        if (f->type == NODE_DECL && !f->data.decl.is_namespace) {
            if (idx == tag) return f->data.decl.explicit_type;
            idx++;
        }
    }
    return NULL;
}

#endif
