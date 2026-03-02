#include "typer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type scope (tracks variable types) ---

typedef struct {
    const char *name;
    TilType type;
} TypeBinding;

typedef struct TypeScope TypeScope;
struct TypeScope {
    TypeBinding *bindings;
    int len;
    int cap;
    TypeScope *parent;
};

static TypeScope *tscope_new(TypeScope *parent) {
    TypeScope *s = calloc(1, sizeof(TypeScope));
    s->parent = parent;
    return s;
}

static void tscope_free(TypeScope *s) {
    free(s->bindings);
    free(s);
}

static void tscope_set(TypeScope *s, const char *name, TilType type) {
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].type = type;
            return;
        }
    }
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(TypeBinding));
    }
    s->bindings[s->len++] = (TypeBinding){name, type};
}

static TilType tscope_get(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].type;
            }
        }
    }
    return TIL_TYPE_UNKNOWN;
}

// --- Built-in function return types ---

static TilType builtin_return_type(const char *name) {
    if (strcmp(name, "add") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "sub") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "mul") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "div") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "to_str") == 0) return TIL_TYPE_STR;
    if (strcmp(name, "println") == 0) return TIL_TYPE_NONE;
    if (strcmp(name, "print") == 0)   return TIL_TYPE_NONE;
    if (strcmp(name, "and") == 0)  return TIL_TYPE_BOOL;
    if (strcmp(name, "or") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "eq") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "lt") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "gt") == 0)   return TIL_TYPE_BOOL;
    return TIL_TYPE_UNKNOWN;
}

// --- Type inference/checking pass ---

static int errors;

static void type_error(const char *path, Expr *e, const char *msg) {
    fprintf(stderr, "%s:%d:%d: type error: %s\n", path, e->line, e->col, msg);
    errors++;
}

// Parse a type name string to TilType
static TilType type_from_name(const char *name) {
    if (strcmp(name, "I64") == 0)  return TIL_TYPE_I64;
    if (strcmp(name, "Str") == 0)  return TIL_TYPE_STR;
    if (strcmp(name, "Bool") == 0) return TIL_TYPE_BOOL;
    return TIL_TYPE_UNKNOWN;
}

static void infer_expr(TypeScope *scope, Expr *e, const char *path);
static void infer_body(TypeScope *scope, Expr *body, const char *path);

static void infer_expr(TypeScope *scope, Expr *e, const char *path) {
    switch (e->type) {
    case NODE_LITERAL_STR:
        e->til_type = TIL_TYPE_STR;
        break;
    case NODE_LITERAL_NUM:
        e->til_type = TIL_TYPE_I64;
        break;
    case NODE_LITERAL_BOOL:
        e->til_type = TIL_TYPE_BOOL;
        break;
    case NODE_IDENT: {
        TilType t = tscope_get(scope, e->data.str_val);
        if (t == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.str_val);
            type_error(path, e, buf);
        }
        e->til_type = t;
        break;
    }
    case NODE_FUNC_DEF:
        e->til_type = TIL_TYPE_NONE;
        // Type the body
        {
            TypeScope *func_scope = tscope_new(scope);
            // TODO: bind parameter types when we support func args
            infer_body(func_scope, e->children[0], path);
            tscope_free(func_scope);
        }
        break;
    case NODE_FCALL: {
        // Infer types of all arguments first
        for (int i = 1; i < e->nchildren; i++) {
            infer_expr(scope, e->children[i], path);
        }
        // Resolve callee
        const char *name = e->children[0]->data.str_val;
        TilType ret = builtin_return_type(name);
        if (ret != TIL_TYPE_UNKNOWN) {
            e->til_type = ret;
        } else {
            // User-defined function — look up in scope
            TilType fn_type = tscope_get(scope, name);
            if (fn_type == TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined function '%s'", name);
                type_error(path, e, buf);
            }
            // TODO: track return types of user-defined functions
            e->til_type = TIL_TYPE_NONE;
        }
        break;
    }
    default:
        e->til_type = TIL_TYPE_UNKNOWN;
        break;
    }
}

static void infer_body(TypeScope *scope, Expr *body, const char *path) {
    body->til_type = TIL_TYPE_NONE;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];
        switch (stmt->type) {
        case NODE_DECL:
            infer_expr(scope, stmt->children[0], path);
            if (stmt->data.decl.explicit_type) {
                TilType declared = type_from_name(stmt->data.decl.explicit_type);
                if (declared == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", stmt->data.decl.explicit_type);
                    type_error(path, stmt, buf);
                } else if (stmt->children[0]->til_type != declared) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name, til_type_name(declared),
                             til_type_name(stmt->children[0]->til_type));
                    type_error(path, stmt, buf);
                }
                stmt->til_type = declared;
            } else {
                stmt->til_type = stmt->children[0]->til_type;
            }
            tscope_set(scope, stmt->data.decl.name, stmt->til_type);
            break;
        case NODE_FCALL:
            infer_expr(scope, stmt, path);
            break;
        case NODE_RETURN:
            if (stmt->nchildren > 0) {
                infer_expr(scope, stmt->children[0], path);
                stmt->til_type = stmt->children[0]->til_type;
            } else {
                stmt->til_type = TIL_TYPE_NONE;
            }
            break;
        case NODE_IF:
            infer_expr(scope, stmt->children[0], path); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            infer_body(scope, stmt->children[1], path); // then
            if (stmt->nchildren > 2) {
                infer_body(scope, stmt->children[2], path); // else
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_BODY: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, path);
            tscope_free(block_scope);
            break;
        }
        case NODE_WHILE:
            infer_expr(scope, stmt->children[0], path); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            infer_body(scope, stmt->children[1], path); // body
            stmt->til_type = TIL_TYPE_NONE;
            break;
        default:
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
    }
}

int type_check(Expr *program, const char *path) {
    errors = 0;
    TypeScope *global = tscope_new(NULL);
    infer_body(global, program, path);
    tscope_free(global);
    return errors;
}
