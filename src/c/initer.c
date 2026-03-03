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

void tscope_set(TypeScope *s, const char *name, TilType type, int is_proc, int is_mut, int line, int col, int is_param, int is_own) {
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].type = type;
            s->bindings[i].is_proc = is_proc;
            s->bindings[i].is_mut = is_mut;
            s->bindings[i].line = line;
            s->bindings[i].col = col;
            s->bindings[i].is_param = is_param;
            s->bindings[i].is_own = is_own;
            return;
        }
    }
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(TypeBinding));
    }
    s->bindings[s->len++] = (TypeBinding){name, type, is_proc, is_mut, line, col, is_param, is_own, NULL, NULL, 0, NULL};
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
    if (strcmp(name, "U8") == 0)   return TIL_TYPE_U8;
    if (strcmp(name, "Str") == 0)  return TIL_TYPE_STR;
    if (strcmp(name, "Bool") == 0) return TIL_TYPE_BOOL;
    if (strcmp(name, "StructDef") == 0)    return TIL_TYPE_STRUCT_DEF;
    if (strcmp(name, "FunctionDef") == 0)  return TIL_TYPE_FUNC_DEF;
    if (strcmp(name, "Dynamic") == 0)     return TIL_TYPE_DYNAMIC;
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
        else if (strcmp(sname, "U8") == 0)         { builtin_type = TIL_TYPE_U8;         is_builtin = 1; }
        else if (strcmp(sname, "Str") == 0)        { builtin_type = TIL_TYPE_STR;        is_builtin = 1; }
        else if (strcmp(sname, "Bool") == 0)       { builtin_type = TIL_TYPE_BOOL;       is_builtin = 1; }
        else if (strcmp(sname, "StructDef") == 0)  { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
        else if (strcmp(sname, "FunctionDef") == 0){ builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
        else if (strcmp(sname, "Dynamic") == 0)   { builtin_type = TIL_TYPE_DYNAMIC;    is_builtin = 1; }

        tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *b = tscope_find(scope, sname);
        b->struct_def = stmt->children[0];
        b->is_builtin = is_builtin;
    }

    // Pass 1.5: auto-generate clone methods for all structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL) continue;
        if (stmt->children[0]->type != NODE_STRUCT_DEF) continue;

        const char *sname = stmt->data.decl.name;

        // Skip meta-types (not actual data types)
        if (strcmp(sname, "StructDef") == 0 ||
            strcmp(sname, "FunctionDef") == 0 ||
            strcmp(sname, "Dynamic") == 0) continue;

        Expr *sdef = stmt->children[0];
        Expr *body = sdef->children[0]; // NODE_BODY

        // Check if clone already exists in namespace
        int has_clone = 0;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && field->data.decl.is_namespace &&
                strcmp(field->data.decl.name, "clone") == 0) {
                has_clone = 1;
                break;
            }
        }
        if (has_clone) continue;

        // Collect instance field names
        int nfields = 0;
        const char **field_names = NULL;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && !field->data.decl.is_namespace) {
                nfields++;
                field_names = realloc(field_names, nfields * sizeof(const char *));
                field_names[nfields - 1] = field->data.decl.name;
            }
        }

        int line = stmt->line;
        int col = stmt->col;
        Expr *func_body = expr_new(NODE_BODY, line, col);

        if (nfields == 0) {
            // No instance fields: other := self; return other
            Expr *self_ref = expr_new(NODE_IDENT, line, col);
            self_ref->data.str_val = "self";
            Expr *other_decl = expr_new(NODE_DECL, line, col);
            other_decl->data.decl.name = "other";
            other_decl->data.decl.is_mut = false;
            other_decl->data.decl.is_namespace = false;
            other_decl->data.decl.explicit_type = NULL;
            expr_add_child(other_decl, self_ref);
            expr_add_child(func_body, other_decl);

            Expr *other_ref = expr_new(NODE_IDENT, line, col);
            other_ref->data.str_val = "other";
            Expr *ret = expr_new(NODE_RETURN, line, col);
            expr_add_child(ret, other_ref);
            expr_add_child(func_body, ret);
        } else {
            // With fields: return StructName(f1=self.f1.clone(), ...)
            Expr *ctor = expr_new(NODE_FCALL, line, col);
            Expr *ctor_name = expr_new(NODE_IDENT, line, col);
            ctor_name->data.str_val = sname;
            expr_add_child(ctor, ctor_name);

            for (int j = 0; j < nfields; j++) {
                // self.field_name
                Expr *self_id = expr_new(NODE_IDENT, line, col);
                self_id->data.str_val = "self";
                Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col);
                field_acc->data.str_val = field_names[j];
                expr_add_child(field_acc, self_id);

                // self.field_name.clone()
                Expr *clone_acc = expr_new(NODE_FIELD_ACCESS, line, col);
                clone_acc->data.str_val = "clone";
                expr_add_child(clone_acc, field_acc);
                Expr *clone_call = expr_new(NODE_FCALL, line, col);
                expr_add_child(clone_call, clone_acc);

                // Named arg: field_name=self.field_name.clone()
                Expr *named = expr_new(NODE_NAMED_ARG, line, col);
                named->data.str_val = field_names[j];
                expr_add_child(named, clone_call);
                expr_add_child(ctor, named);
            }

            Expr *ret = expr_new(NODE_RETURN, line, col);
            expr_add_child(ret, ctor);
            expr_add_child(func_body, ret);
        }

        // func def
        Expr *func_def = expr_new(NODE_FUNC_DEF, line, col);
        func_def->data.func_def.func_type = FUNC_FUNC;
        func_def->data.func_def.nparam = 1;
        func_def->data.func_def.param_names = malloc(sizeof(const char *));
        func_def->data.func_def.param_names[0] = "self";
        func_def->data.func_def.param_types = malloc(sizeof(const char *));
        func_def->data.func_def.param_types[0] = sname;
        func_def->data.func_def.param_muts = calloc(1, sizeof(bool));
        func_def->data.func_def.param_owns = calloc(1, sizeof(bool));
        func_def->data.func_def.param_defaults = calloc(1, sizeof(Expr *));
        func_def->data.func_def.return_type = sname;
        func_def->data.func_def.is_variadic = false;
        expr_add_child(func_def, func_body);

        // clone := func(...)  (namespace decl)
        Expr *decl = expr_new(NODE_DECL, line, col);
        decl->data.decl.name = "clone";
        decl->data.decl.is_namespace = true;
        decl->data.decl.is_mut = false;
        decl->data.decl.explicit_type = NULL;
        expr_add_child(decl, func_def);

        // Add to struct body
        expr_add_child(body, decl);
        free(field_names);
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
        tscope_set(scope, stmt->data.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *fb = tscope_find(scope, stmt->data.decl.name);
        if (fb) {
            fb->func_def = stmt->children[0];
            if (ft == FUNC_EXT_FUNC || ft == FUNC_EXT_PROC)
                fb->is_builtin = 1;
        }
    }

    return 0;
}
