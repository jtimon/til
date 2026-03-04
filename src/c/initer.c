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

void tscope_set(TypeScope *s, Str *name, TilType type, int is_proc, int is_mut, int line, int col, int is_param, int is_own) {
    for (int i = 0; i < s->len; i++) {
        if (Str_eq(s->bindings[i].name, name)) {
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
    s->bindings[s->len++] = (TypeBinding){name, type, is_proc, is_mut, line, col, is_param, is_own, NULL, NULL, 0, 0, NULL};
}

TilType tscope_get(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (Str_eq(cur->bindings[i].name, name)) {
                return cur->bindings[i].type;
            }
        }
    }
    return TIL_TYPE_UNKNOWN;
}

int tscope_is_proc(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (Str_eq(cur->bindings[i].name, name)) {
                return cur->bindings[i].is_proc;
            }
        }
    }
    return -1;
}

TypeBinding *tscope_find(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (Str_eq(cur->bindings[i].name, name)) {
                return &cur->bindings[i];
            }
        }
    }
    return NULL;
}

Expr *tscope_get_struct(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (Str_eq(cur->bindings[i].name, name)) {
                return cur->bindings[i].struct_def;
            }
        }
    }
    return NULL;
}

int tscope_is_mut(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (Str_eq(cur->bindings[i].name, name)) {
                return cur->bindings[i].is_mut;
            }
        }
    }
    return 0;
}

// --- Resolve type name (simplified, for init phase) ---

static TilType type_from_name_init(Str *name, TypeScope *scope) {
    if (Str_eq_c(name, "I64"))  return TIL_TYPE_I64;
    if (Str_eq_c(name, "U8"))   return TIL_TYPE_U8;
    if (Str_eq_c(name, "Str"))  return TIL_TYPE_STR;
    if (Str_eq_c(name, "Bool")) return TIL_TYPE_BOOL;
    if (Str_eq_c(name, "StructDef"))    return TIL_TYPE_STRUCT_DEF;
    if (Str_eq_c(name, "FunctionDef"))  return TIL_TYPE_FUNC_DEF;
    if (Str_eq_c(name, "Dynamic"))     return TIL_TYPE_DYNAMIC;
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

        Str *sname = stmt->data.decl.name;
        TilType builtin_type = TIL_TYPE_STRUCT;
        int is_builtin = 0;
        if (Str_eq_c(sname, "I64"))             { builtin_type = TIL_TYPE_I64;        is_builtin = 1; }
        else if (Str_eq_c(sname, "U8"))         { builtin_type = TIL_TYPE_U8;         is_builtin = 1; }
        else if (Str_eq_c(sname, "Str"))        { builtin_type = TIL_TYPE_STR;        is_builtin = 1; }
        else if (Str_eq_c(sname, "Bool"))       { builtin_type = TIL_TYPE_BOOL;       is_builtin = 1; }
        else if (Str_eq_c(sname, "StructDef"))  { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
        else if (Str_eq_c(sname, "FunctionDef")){ builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
        else if (Str_eq_c(sname, "Dynamic"))   { builtin_type = TIL_TYPE_DYNAMIC;    is_builtin = 1; }

        tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *b = tscope_find(scope, sname);
        b->struct_def = stmt->children[0];
        b->is_builtin = is_builtin;
        b->is_ext = stmt->children[0]->is_ext;
    }

    // Pass 1.5: auto-generate clone methods for all structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL) continue;
        if (stmt->children[0]->type != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->data.decl.name;

        // Skip meta-types and ext_structs (C side provides clone if needed)
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        Expr *sdef = stmt->children[0];
        if (sdef->is_ext) continue;

        Expr *body = sdef->children[0]; // NODE_BODY

        // Check if clone already exists in namespace
        int has_clone = 0;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && field->data.decl.is_namespace &&
                Str_eq_c(field->data.decl.name, "clone")) {
                has_clone = 1;
                break;
            }
        }
        if (has_clone) continue;

        // Collect instance field names
        int nfields = 0;
        Str **field_names = NULL;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && !field->data.decl.is_namespace) {
                nfields++;
                field_names = realloc(field_names, nfields * sizeof(Str *));
                field_names[nfields - 1] = field->data.decl.name;
            }
        }

        int line = stmt->line;
        int col = stmt->col;
        Expr *func_body = expr_new(NODE_BODY, line, col);

        if (nfields == 0) {
            // No instance fields: return Type()
            Expr *ctor = expr_new(NODE_FCALL, line, col);
            Expr *ctor_name = expr_new(NODE_IDENT, line, col);
            ctor_name->data.str_val = sname;
            expr_add_child(ctor, ctor_name);

            Expr *ret = expr_new(NODE_RETURN, line, col);
            expr_add_child(ret, ctor);
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
                self_id->data.str_val = Str_new("self");
                Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col);
                field_acc->data.str_val = field_names[j];
                expr_add_child(field_acc, self_id);

                // self.field_name.clone()
                Expr *clone_acc = expr_new(NODE_FIELD_ACCESS, line, col);
                clone_acc->data.str_val = Str_new("clone");
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
        func_def->data.func_def.param_names = malloc(sizeof(Str *));
        func_def->data.func_def.param_names[0] = Str_new("self");
        func_def->data.func_def.param_types = malloc(sizeof(Str *));
        func_def->data.func_def.param_types[0] = sname;
        func_def->data.func_def.param_muts = calloc(1, sizeof(bool));
        func_def->data.func_def.param_owns = calloc(1, sizeof(bool));
        func_def->data.func_def.param_defaults = calloc(1, sizeof(Expr *));
        func_def->data.func_def.return_type = sname;
        func_def->data.func_def.is_variadic = false;
        expr_add_child(func_def, func_body);

        // clone := func(...)  (namespace decl)
        Expr *decl = expr_new(NODE_DECL, line, col);
        decl->data.decl.name = Str_new("clone");
        decl->data.decl.is_namespace = true;
        decl->data.decl.is_mut = false;
        decl->data.decl.explicit_type = NULL;
        expr_add_child(decl, func_def);

        // Add to struct body
        expr_add_child(body, decl);
        free(field_names);
    }

    // Pass 1.7: auto-generate delete methods for all structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL) continue;
        if (stmt->children[0]->type != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->data.decl.name;

        // Skip meta-types and ext_structs (C side provides delete if needed)
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        Expr *sdef = stmt->children[0];
        if (sdef->is_ext) continue;

        Expr *body = sdef->children[0]; // NODE_BODY

        // Check if delete already exists in namespace
        int has_delete = 0;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && field->data.decl.is_namespace &&
                Str_eq_c(field->data.decl.name, "delete")) {
                has_delete = 1;
                break;
            }
        }
        if (has_delete) continue;

        // Collect instance field names
        int nfields = 0;
        Str **field_names = NULL;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->type == NODE_DECL && !field->data.decl.is_namespace) {
                nfields++;
                field_names = realloc(field_names, nfields * sizeof(Str *));
                field_names[nfields - 1] = field->data.decl.name;
            }
        }

        int line = stmt->line;
        int col = stmt->col;
        Expr *proc_body = expr_new(NODE_BODY, line, col);

        // For each field: self.field.delete(call_free=false)
        for (int j = 0; j < nfields; j++) {
            Expr *self_id = expr_new(NODE_IDENT, line, col);
            self_id->data.str_val = Str_new("self");
            Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col);
            field_acc->data.str_val = field_names[j];
            field_acc->is_own_arg = true; // delete takes own self
            expr_add_child(field_acc, self_id);

            Expr *del_acc = expr_new(NODE_FIELD_ACCESS, line, col);
            del_acc->data.str_val = Str_new("delete");
            expr_add_child(del_acc, field_acc);
            Expr *del_call = expr_new(NODE_FCALL, line, col);
            expr_add_child(del_call, del_acc);

            // call_free=false (inline field, don't free individually)
            Expr *false_lit = expr_new(NODE_LITERAL_BOOL, line, col);
            false_lit->data.str_val = Str_new("false");
            expr_add_child(del_call, false_lit);

            expr_add_child(proc_body, del_call);
        }

        // if call_free { free(own self) }
        Expr *cond = expr_new(NODE_IDENT, line, col);
        cond->data.str_val = Str_new("call_free");
        Expr *then_body = expr_new(NODE_BODY, line, col);
        Expr *free_call = expr_new(NODE_FCALL, line, col);
        Expr *free_id = expr_new(NODE_IDENT, line, col);
        free_id->data.str_val = Str_new("free");
        expr_add_child(free_call, free_id);
        Expr *self_arg = expr_new(NODE_IDENT, line, col);
        self_arg->data.str_val = Str_new("self");
        self_arg->is_own_arg = true;
        expr_add_child(free_call, self_arg);
        expr_add_child(then_body, free_call);
        Expr *if_node = expr_new(NODE_IF, line, col);
        expr_add_child(if_node, cond);
        expr_add_child(if_node, then_body);
        expr_add_child(proc_body, if_node);

        // proc def: delete(own self: Type, call_free: Bool = true)
        Expr *default_true = expr_new(NODE_LITERAL_BOOL, line, col);
        default_true->data.str_val = Str_new("true");

        Expr *proc_def = expr_new(NODE_FUNC_DEF, line, col);
        proc_def->data.func_def.func_type = FUNC_PROC;
        proc_def->data.func_def.nparam = 2;
        proc_def->data.func_def.param_names = malloc(2 * sizeof(Str *));
        proc_def->data.func_def.param_names[0] = Str_new("self");
        proc_def->data.func_def.param_names[1] = Str_new("call_free");
        proc_def->data.func_def.param_types = malloc(2 * sizeof(Str *));
        proc_def->data.func_def.param_types[0] = sname;
        proc_def->data.func_def.param_types[1] = Str_new("Bool");
        proc_def->data.func_def.param_muts = calloc(2, sizeof(bool));
        proc_def->data.func_def.param_owns = calloc(2, sizeof(bool));
        proc_def->data.func_def.param_owns[0] = true;
        proc_def->data.func_def.param_defaults = calloc(2, sizeof(Expr *));
        proc_def->data.func_def.param_defaults[1] = default_true;
        proc_def->data.func_def.return_type = NULL;
        proc_def->data.func_def.is_variadic = false;
        expr_add_child(proc_def, proc_body);

        // delete := proc(...)  (namespace decl)
        Expr *decl = expr_new(NODE_DECL, line, col);
        decl->data.decl.name = Str_new("delete");
        decl->data.decl.is_namespace = true;
        decl->data.decl.is_mut = false;
        decl->data.decl.explicit_type = NULL;
        expr_add_child(decl, proc_def);

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
