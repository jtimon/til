#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scavenger.h"
#include "map.h"
#include "vec.h"

// Name-to-Expr map (for top-level decls and namespace methods)
static Expr *map_get_expr(Map *m, Str *key) {
    Expr **p = Map_get(m, &key);
    return p ? *p : NULL;
}

// Garbage collector for Str* allocated during scavenging
static Str **gc_strs = NULL;
static int gc_len = 0, gc_cap = 0;

static Str *gc_str(Str *s) {
    if (gc_len == gc_cap) {
        gc_cap = gc_cap ? gc_cap * 2 : 32;
        gc_strs = realloc(gc_strs, gc_cap * sizeof(Str *));
    }
    gc_strs[gc_len++] = s;
    return s;
}

static void gc_free_all(void) {
    for (int i = 0; i < gc_len; i++) Str_delete(gc_strs[i]);
    free(gc_strs);
    gc_strs = NULL;
    gc_len = gc_cap = 0;
}

// Build a qualified name "Type.method"
static Str *qualified_name(Str *type_name, Str *method_name) {
    int len = type_name->len + 1 + method_name->len;
    char *buf = malloc(len + 1);
    snprintf(buf, len + 1, "%s.%s", type_name->c_str, method_name->c_str);
    Str *s = Str_new(buf);
    free(buf);
    return gc_str(s);
}

// Collect all name references from an AST subtree into refs
static void vec_push_str(Vec *v, Str *s) {
    Vec_push(v, &s);
}

static void collect_refs(Expr *e, Vec *refs) {
    if (!e) return;

    switch (e->type) {
    case NODE_IDENT:
        vec_push_str(refs, e->data.str_val);
        break;

    case NODE_FCALL:
        // Check for namespace method call: Type.method(args...)
        if (e->nchildren > 0 && e->children[0]->type == NODE_FIELD_ACCESS &&
            e->children[0]->is_ns_field) {
            Expr *fa = e->children[0];
            Str *type_name = fa->children[0]->data.str_val;
            Str *method = fa->data.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, method));
            // Recurse into args (skip callee — already handled)
            for (int i = 1; i < e->nchildren; i++)
                collect_refs(e->children[i], refs);
            return;
        }
        break;

    case NODE_FUNC_DEF: {
        int np = e->data.func_def.nparam;
        for (int i = 0; i < np; i++) {
            if (e->data.func_def.param_types[i])
                vec_push_str(refs, e->data.func_def.param_types[i]);
        }
        if (e->data.func_def.return_type)
            vec_push_str(refs, e->data.func_def.return_type);
        break;
    }

    case NODE_FIELD_ACCESS:
        // Namespace field access: Type.field
        if (e->is_ns_field && e->children[0]->type == NODE_IDENT) {
            Str *type_name = e->children[0]->data.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, e->data.str_val));
        }
        break;

    case NODE_FIELD_ASSIGN:
        // Namespace field assignment: Type.field = value
        if (e->is_ns_field && e->children[0]->type == NODE_IDENT) {
            Str *type_name = e->children[0]->data.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, e->data.str_val));
        }
        break;

    case NODE_DECL:
        if (e->data.decl.explicit_type)
            vec_push_str(refs, e->data.decl.explicit_type);
        break;

    default:
        break;
    }

    // Recurse into children
    for (int i = 0; i < e->nchildren; i++)
        collect_refs(e->children[i], refs);
}

void scavenge(Expr *program, Str *mode) {
    int is_cli = mode && strcmp(mode->c_str, "cli") == 0;

    // 1. Build top-level declaration map
    Map top = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL) {
            Str *name = stmt->data.decl.name;
            Map_set(&top, &name, &stmt);
        }
    }

    // 2. Build namespace method map: "Type.method" → method decl node
    Map methods = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (int i = 0; i < Map_len(&top); i++) {
        Expr *decl = ((Expr **)top.vals.data)[i];
        if (decl->children[0]->type != NODE_STRUCT_DEF &&
            decl->children[0]->type != NODE_ENUM_DEF) continue;
        Str *sname = ((Str **)top.keys.data)[i];
        Expr *body = decl->children[0]->children[0];
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (!field->data.decl.is_namespace) continue;
            Str *qn = qualified_name(sname, field->data.decl.name);
            Map_set(&methods, &qn, &field);
        }
    }

    // 3. Seed worklist
    Vec worklist = Vec_new(sizeof(Str *));
    if (is_cli) {
        vec_push_str(&worklist, gc_str(Str_new("main")));
    } else {
        // Script mode: collect refs from all top-level executable statements
        for (int i = 0; i < program->nchildren; i++) {
            Expr *stmt = program->children[i];
            if (stmt->type == NODE_DECL &&
                (stmt->children[0]->type == NODE_FUNC_DEF ||
                 stmt->children[0]->type == NODE_STRUCT_DEF ||
                 stmt->children[0]->type == NODE_ENUM_DEF))
                continue;
            collect_refs(stmt, &worklist);
        }
    }

    // 4. BFS
    Set visited = Set_new(sizeof(Str *), str_ptr_cmp);
    int cursor = 0;
    while (cursor < worklist.len) {
        Str *name = ((Str **)worklist.data)[cursor++];
        if (Set_has(&visited, &name)) continue;
        Set_add(&visited, &name);

        // Top-level declaration?
        Expr *decl = map_get_expr(&top, name);
        if (decl) {
            if (decl->children[0]->type == NODE_STRUCT_DEF ||
                decl->children[0]->type == NODE_ENUM_DEF) {
                // For structs/enums: only walk instance fields, not namespace methods.
                // Namespace methods are walked individually via qualified names.
                Expr *body = decl->children[0]->children[0];
                for (int i = 0; i < body->nchildren; i++) {
                    if (!body->children[i]->data.decl.is_namespace)
                        collect_refs(body->children[i], &worklist);
                }
            } else {
                collect_refs(decl->children[0], &worklist);
            }
        }

        // Namespace method?
        Expr *method = map_get_expr(&methods, name);
        if (method && method->children[0]->type == NODE_FUNC_DEF) {
            collect_refs(method->children[0], &worklist);
        }
    }

    // 5. Filter top-level declarations
    int w = 0;
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL &&
            (stmt->children[0]->type == NODE_FUNC_DEF ||
             stmt->children[0]->type == NODE_STRUCT_DEF ||
             stmt->children[0]->type == NODE_ENUM_DEF)) {
            Str *dname = stmt->data.decl.name;
            if (!Set_has(&visited, &dname)) continue;
        }
        program->children[w++] = stmt;
    }
    program->nchildren = w;

    // 6. Filter namespace methods in kept structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type != NODE_DECL || (stmt->children[0]->type != NODE_STRUCT_DEF &&
                                        stmt->children[0]->type != NODE_ENUM_DEF))
            continue;
        Str *sname = stmt->data.decl.name;
        Expr *body = stmt->children[0]->children[0];
        int bw = 0;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (field->data.decl.is_namespace) {
                Str *qn = qualified_name(sname, field->data.decl.name);
                if (!Set_has(&visited, &qn)) continue;
            }
            body->children[bw++] = field;
        }
        body->nchildren = bw;
    }

    // Cleanup
    Vec_delete(&worklist);
    Set_delete(&visited);
    Map_delete(&top);
    Map_delete(&methods);
    gc_free_all();
}
