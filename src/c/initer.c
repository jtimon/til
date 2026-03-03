#include "initer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type scope implementation ---

TypeScope *tscope_new(TypeScope *parent) {
    TypeScope *s = calloc(1, sizeof(TypeScope));
    s->parent = parent;
    return s;
}

void tscope_free(TypeScope *s) {
    free(s->bindings);
    free(s);
}

void tscope_set(TypeScope *s, const char *name, TilType type, int is_proc, int is_mut, int line, int col, int is_param) {
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].type = type;
            s->bindings[i].is_proc = is_proc;
            s->bindings[i].is_mut = is_mut;
            s->bindings[i].line = line;
            s->bindings[i].col = col;
            s->bindings[i].is_param = is_param;
            return;
        }
    }
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(TypeBinding));
    }
    s->bindings[s->len++] = (TypeBinding){name, type, is_proc, is_mut, line, col, is_param, NULL, NULL, 0, NULL};
}

TilType tscope_get(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].type;
            }
        }
    }
    return TIL_TYPE_UNKNOWN;
}

int tscope_is_proc(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].is_proc;
            }
        }
    }
    return -1;
}

TypeBinding *tscope_find(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return &cur->bindings[i];
            }
        }
    }
    return NULL;
}

Expr *tscope_get_struct(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].struct_def;
            }
        }
    }
    return NULL;
}

int tscope_is_mut(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].is_mut;
            }
        }
    }
    return 0;
}

// --- Resolve type name (simplified, for init phase) ---

static TilType type_from_name_init(const char *name, TypeScope *scope) {
    if (strcmp(name, "I64") == 0)  return TIL_TYPE_I64;
    if (strcmp(name, "Str") == 0)  return TIL_TYPE_STR;
    if (strcmp(name, "Bool") == 0) return TIL_TYPE_BOOL;
    if (strcmp(name, "StructDef") == 0)    return TIL_TYPE_STRUCT_DEF;
    if (strcmp(name, "FunctionDef") == 0)  return TIL_TYPE_FUNC_DEF;
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return TIL_TYPE_STRUCT;
    }
    return TIL_TYPE_UNKNOWN;
}

// --- Init phase: pre-scan top-level declarations ---

int init_declarations(Expr *program, TypeScope *scope, const char *path) {
    (void)path;
    // Pass 1: register all struct definitions
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL) continue;
        if (stmt->children[0]->type != NODE_STRUCT_DEF) continue;

        const char *sname = stmt->data.decl.name;
        TilType builtin_type = TIL_TYPE_STRUCT;
        int is_builtin = 0;
        if (strcmp(sname, "I64") == 0)             { builtin_type = TIL_TYPE_I64;        is_builtin = 1; }
        else if (strcmp(sname, "Str") == 0)        { builtin_type = TIL_TYPE_STR;        is_builtin = 1; }
        else if (strcmp(sname, "Bool") == 0)       { builtin_type = TIL_TYPE_BOOL;       is_builtin = 1; }
        else if (strcmp(sname, "StructDef") == 0)  { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
        else if (strcmp(sname, "FunctionDef") == 0){ builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }

        tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0);
        TypeBinding *b = tscope_find(scope, sname);
        b->struct_def = stmt->children[0];
        b->is_builtin = is_builtin;
    }

    // Pass 2: register all func/proc definitions
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL) continue;
        if (stmt->children[0]->type != NODE_FUNC_DEF) continue;

        FuncType ft = stmt->children[0]->data.func_def.func_type;
        int callee_is_proc = (ft == FUNC_PROC || ft == FUNC_EXT_PROC);
        TilType rt = TIL_TYPE_NONE;
        if (stmt->children[0]->data.func_def.return_type) {
            rt = type_from_name_init(stmt->children[0]->data.func_def.return_type, scope);
        }
        tscope_set(scope, stmt->data.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0);
        TypeBinding *fb = tscope_find(scope, stmt->data.decl.name);
        if (fb) {
            fb->func_def = stmt->children[0];
            if (ft == FUNC_EXT_FUNC || ft == FUNC_EXT_PROC)
                fb->is_builtin = 1;
        }
    }

    return 0;
}
