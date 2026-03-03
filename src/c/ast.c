#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

const char *til_type_name(TilType t) {
    switch (t) {
    case TIL_TYPE_UNKNOWN: return "unknown";
    case TIL_TYPE_NONE:    return "None";
    case TIL_TYPE_I64:     return "I64";
    case TIL_TYPE_U8:      return "U8";
    case TIL_TYPE_STR:     return "Str";
    case TIL_TYPE_BOOL:    return "Bool";
    case TIL_TYPE_STRUCT:      return "Struct";
    case TIL_TYPE_STRUCT_DEF:  return "StructDef";
    case TIL_TYPE_FUNC_DEF:    return "FunctionDef";
    }
    return "?";
}

Expr *expr_new(NodeType type, int line, int col) {
    Expr *e = calloc(1, sizeof(Expr));
    e->type = type;
    e->line = line;
    e->col = col;
    return e;
}

void expr_add_child(Expr *parent, Expr *child) {
    parent->nchildren++;
    parent->children = realloc(parent->children, parent->nchildren * sizeof(Expr *));
    parent->children[parent->nchildren - 1] = child;
}

Expr *expr_clone(Expr *e) {
    if (!e) return NULL;
    Expr *c = calloc(1, sizeof(Expr));
    *c = *e;
    if (e->nchildren > 0) {
        c->children = malloc(e->nchildren * sizeof(Expr *));
        for (int i = 0; i < e->nchildren; i++) {
            c->children[i] = expr_clone(e->children[i]);
        }
    } else {
        c->children = NULL;
    }
    return c;
}

void expr_free(Expr *e) {
    if (!e) return;
    for (int i = 0; i < e->nchildren; i++) {
        expr_free(e->children[i]);
    }
    free(e->children);
    free(e);
}

static const char *node_name(NodeType type) {
    switch (type) {
    case NODE_BODY:        return "body";
    case NODE_LITERAL_STR: return "str";
    case NODE_LITERAL_NUM: return "num";
    case NODE_LITERAL_BOOL: return "bool";
    case NODE_IDENT:       return "ident";
    case NODE_DECL:        return "decl";
    case NODE_ASSIGN:      return "assign";
    case NODE_FCALL:       return "fcall";
    case NODE_FUNC_DEF:    return "func_def";
    case NODE_STRUCT_DEF:  return "struct_def";
    case NODE_FIELD_ACCESS: return "field_access";
    case NODE_FIELD_ASSIGN: return "field_assign";
    case NODE_RETURN:      return "return";
    case NODE_IF:          return "if";
    case NODE_WHILE:       return "while";
    case NODE_FOR_IN:      return "for_in";
    case NODE_NAMED_ARG:   return "named_arg";
    case NODE_BREAK:       return "break";
    case NODE_CONTINUE:    return "continue";
    }
    return "?";
}

static const char *func_type_name(FuncType ft) {
    switch (ft) {
    case FUNC_FUNC:     return "func";
    case FUNC_PROC:     return "proc";
    case FUNC_MACRO:    return "macro";
    case FUNC_EXT_FUNC: return "ext_func";
    case FUNC_EXT_PROC: return "ext_proc";
    }
    return "?";
}

void ast_print(Expr *e, int indent) {
    if (!e) return;
    for (int i = 0; i < indent; i++) printf("  ");
    printf("(%s", node_name(e->type));
    if (e->til_type != TIL_TYPE_UNKNOWN) {
        printf(":%s", til_type_name(e->til_type));
    }
    switch (e->type) {
    case NODE_IDENT:
    case NODE_LITERAL_STR:
    case NODE_LITERAL_NUM:
    case NODE_LITERAL_BOOL:
    case NODE_FOR_IN:
        printf(" \"%s\"", e->data.str_val);
        break;
    case NODE_DECL:
        printf(" %s%s", e->data.decl.is_mut ? "mut " : "", e->data.decl.name);
        break;
    case NODE_ASSIGN:
    case NODE_NAMED_ARG:
        printf(" %s", e->data.str_val);
        break;
    case NODE_FUNC_DEF:
        printf(" %s", func_type_name(e->data.func_def.func_type));
        break;
    default:
        break;
    }
    if (e->nchildren > 0) {
        printf("\n");
        for (int i = 0; i < e->nchildren; i++) {
            ast_print(e->children[i], indent + 1);
        }
        for (int i = 0; i < indent; i++) printf("  ");
    }
    printf(")\n");
}
