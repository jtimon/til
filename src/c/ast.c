#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

const char *til_type_name_c(TilType t) {
    switch (t) {
    case TIL_TYPE_UNKNOWN: return "unknown";
    case TIL_TYPE_NONE:    return "None";
    case TIL_TYPE_I64:     return "I64";
    case TIL_TYPE_U8:      return "U8";
    case TIL_TYPE_I16:     return "I16";
    case TIL_TYPE_I32:     return "I32";
    case TIL_TYPE_U32:     return "U32";
    case TIL_TYPE_F32:     return "F32";
    case TIL_TYPE_BOOL:    return "Bool";
    case TIL_TYPE_STRUCT:      return "Struct";
    case TIL_TYPE_STRUCT_DEF:  return "StructDef";
    case TIL_TYPE_ENUM:        return "Enum";
    case TIL_TYPE_ENUM_DEF:    return "EnumDef";
    case TIL_TYPE_FUNC_DEF:    return "FunctionDef";
    case TIL_TYPE_DYNAMIC:     return "Dynamic";
    }
    return "?";
}

Expr *expr_new(NodeTypeTag tag, U32 line, U32 col, Str *path) {
    Expr *e = calloc(1, sizeof(Expr));
    e->type.tag = tag;
    e->children = Vec_new(sizeof(Expr *));
    e->line = line;
    e->col = col;
    e->path = path;
    e->variadic_index = -1;
    return e;
}

void expr_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: error: %s\n", e->path->c_str, e->line, e->col, msg);
}

void expr_todo_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: error: %s\n", e->path->c_str, e->line, e->col, msg);
    fprintf(stderr, "  note: this language feature is not implemented yet\n");
}

void expr_lang_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: error: %s\n", e->path->c_str, e->line, e->col, msg);
    fprintf(stderr, "  note: this is a bug in the language, please report it\n");
}

void expr_add_child(Expr *parent, Expr *child) {
    Vec_push(&parent->children, &child);
}

Expr *expr_clone(Expr *e) {
    if (!e) return NULL;
    Expr *c = calloc(1, sizeof(Expr));
    *c = *e;
    c->children = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < e->children.count; i++) {
        Expr *cloned = expr_clone(expr_child(e, i));
        Vec_push(&c->children, &cloned);
    }
    return c;
}

void expr_free(Expr *e) {
    if (!e) return;
    for (U32 i = 0; i < e->children.count; i++) {
        expr_free(expr_child(e, i));
    }
    Vec_delete(&e->children);
    free(e);
}

static const char *node_name(NodeTypeTag type) {
    switch (type) {
    case NODE_BODY:        return "body";
    case NODE_LITERAL_STR: return "str";
    case NODE_LITERAL_NUM: return "num";
    case NODE_LITERAL_BOOL: return "bool";
    case NODE_LITERAL_NULL: return "null";
    case NODE_IDENT:       return "ident";
    case NODE_DECL:        return "decl";
    case NODE_ASSIGN:      return "assign";
    case NODE_FCALL:       return "fcall";
    case NODE_FUNC_DEF:    return "func_def";
    case NODE_STRUCT_DEF:  return "struct_def";
    case NODE_ENUM_DEF:    return "enum_def";
    case NODE_FIELD_ACCESS: return "field_access";
    case NODE_FIELD_ASSIGN: return "field_assign";
    case NODE_RETURN:      return "return";
    case NODE_IF:          return "if";
    case NODE_WHILE:       return "while";
    case NODE_FOR_IN:      return "for_in";
    case NODE_NAMED_ARG:   return "named_arg";
    case NODE_BREAK:       return "break";
    case NODE_CONTINUE:    return "continue";
    case NODE_MAP_LIT:     return "map_lit";
    case NODE_SET_LIT:     return "set_lit";
    case NODE_SWITCH:      return "switch";
    case NODE_CASE:        return "case";
    }
    return "?";
}

static const char *func_type_name(FuncType ft) {
    switch (ft) {
    case FUNC_FUNC:     return "func";
    case FUNC_PROC:     return "proc";
    case FUNC_TEST:     return "test";
    case FUNC_MACRO:    return "macro";
    case FUNC_EXT_FUNC: return "ext_func";
    case FUNC_EXT_PROC: return "ext_proc";
    }
    return "?";
}

void ast_print(Expr *e, U32 indent) {
    if (!e) return;
    for (U32 i = 0; i < indent; i++) printf("  ");
    printf("(%s", node_name(e->type.tag));
    if (e->til_type != TIL_TYPE_UNKNOWN) {
        printf(":%s", til_type_name_c(e->til_type));
    }
    switch (e->type.tag) {
    case NODE_IDENT:
    case NODE_LITERAL_STR:
    case NODE_LITERAL_NUM:
    case NODE_LITERAL_BOOL:
    case NODE_FOR_IN:
        printf(" \"%s\"", e->type.str_val->c_str);
        break;
    case NODE_LITERAL_NULL:
        break;
    case NODE_DECL:
        printf(" %s%s", e->type.decl.is_mut ? "mut " : "", e->type.decl.name->c_str);
        break;
    case NODE_ASSIGN:
    case NODE_NAMED_ARG:
        printf(" %s", e->type.str_val->c_str);
        break;
    case NODE_FUNC_DEF:
        printf(" %s", func_type_name(e->type.func_def.func_type));
        break;
    default:
        break;
    }
    if (e->children.count > 0) {
        printf("\n");
        for (U32 i = 0; i < e->children.count; i++) {
            ast_print(expr_child(e, i), indent + 1);
        }
        for (U32 i = 0; i < indent; i++) printf("  ");
    }
    printf(")\n");
}
