#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scavenger.h"

// Simple string set (dynamic array with linear lookup)
typedef struct {
    Str **items;
    int len, cap;
} StrSet;

static StrSet strset_new(void) {
    return (StrSet){NULL, 0, 0};
}

static int strset_has(StrSet *s, Str *name) {
    for (int i = 0; i < s->len; i++)
        if (Str_eq(s->items[i], name)) return 1;
    return 0;
}

static void strset_add(StrSet *s, Str *name) {
    if (strset_has(s, name)) return;
    if (s->len == s->cap) {
        s->cap = s->cap ? s->cap * 2 : 16;
        s->items = realloc(s->items, s->cap * sizeof(Str *));
    }
    s->items[s->len++] = name;
}

static void strset_free(StrSet *s) {
    free(s->items);
}

// Name-to-Expr map (for top-level decls and namespace methods)
typedef struct {
    Str **keys;
    Expr **vals;
    int len, cap;
} DeclMap;

static DeclMap declmap_new(void) {
    return (DeclMap){NULL, NULL, 0, 0};
}

static void declmap_put(DeclMap *m, Str *key, Expr *val) {
    if (m->len == m->cap) {
        m->cap = m->cap ? m->cap * 2 : 16;
        m->keys = realloc(m->keys, m->cap * sizeof(Str *));
        m->vals = realloc(m->vals, m->cap * sizeof(Expr *));
    }
    m->keys[m->len] = key;
    m->vals[m->len] = val;
    m->len++;
}

static Expr *declmap_get(DeclMap *m, Str *key) {
    for (int i = 0; i < m->len; i++)
        if (Str_eq(m->keys[i], key)) return m->vals[i];
    return NULL;
}

static void declmap_free(DeclMap *m) {
    free(m->keys);
    free(m->vals);
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
static void collect_refs(Expr *e, StrSet *refs) {
    if (!e) return;

    switch (e->type) {
    case NODE_IDENT:
        strset_add(refs, e->data.str_val);
        break;

    case NODE_FCALL:
        // Check for namespace method call: Type.method(args...)
        if (e->nchildren > 0 && e->children[0]->type == NODE_FIELD_ACCESS &&
            e->children[0]->is_ns_field) {
            Expr *fa = e->children[0];
            Str *type_name = fa->children[0]->data.str_val;
            Str *method = fa->data.str_val;
            strset_add(refs, type_name);
            strset_add(refs, qualified_name(type_name, method));
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
                strset_add(refs, e->data.func_def.param_types[i]);
        }
        if (e->data.func_def.return_type)
            strset_add(refs, e->data.func_def.return_type);
        break;
    }

    case NODE_FIELD_ACCESS:
        // Namespace field access: Type.field
        if (e->is_ns_field && e->children[0]->type == NODE_IDENT) {
            Str *type_name = e->children[0]->data.str_val;
            strset_add(refs, type_name);
            strset_add(refs, qualified_name(type_name, e->data.str_val));
        }
        break;

    case NODE_FIELD_ASSIGN:
        // Namespace field assignment: Type.field = value
        if (e->is_ns_field && e->children[0]->type == NODE_IDENT) {
            Str *type_name = e->children[0]->data.str_val;
            strset_add(refs, type_name);
            strset_add(refs, qualified_name(type_name, e->data.str_val));
        }
        break;

    case NODE_DECL:
        if (e->data.decl.explicit_type)
            strset_add(refs, e->data.decl.explicit_type);
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
    DeclMap top = declmap_new();
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL)
            declmap_put(&top, stmt->data.decl.name, stmt);
    }

    // 2. Build namespace method map: "Type.method" → method decl node
    DeclMap methods = declmap_new();
    for (int i = 0; i < top.len; i++) {
        Expr *decl = top.vals[i];
        if (decl->children[0]->type != NODE_STRUCT_DEF &&
            decl->children[0]->type != NODE_ENUM_DEF) continue;
        Str *sname = top.keys[i];
        Expr *body = decl->children[0]->children[0];
        for (int j = 0; j < body->nchildren; j++) {
            Expr *field = body->children[j];
            if (!field->data.decl.is_namespace) continue;
            declmap_put(&methods, qualified_name(sname, field->data.decl.name), field);
        }
    }

    // 3. Seed worklist
    StrSet worklist = strset_new();
    if (is_cli) {
        strset_add(&worklist, gc_str(Str_new("main")));
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
    StrSet visited = strset_new();
    int cursor = 0;
    while (cursor < worklist.len) {
        Str *name = worklist.items[cursor++];
        if (strset_has(&visited, name)) continue;
        strset_add(&visited, name);

        // Top-level declaration?
        Expr *decl = declmap_get(&top, name);
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
        Expr *method = declmap_get(&methods, name);
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
            if (!strset_has(&visited, stmt->data.decl.name)) continue;
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
                if (!strset_has(&visited, qn)) continue;
            }
            body->children[bw++] = field;
        }
        body->nchildren = bw;
    }

    // Cleanup
    strset_free(&worklist);
    strset_free(&visited);
    declmap_free(&top);
    declmap_free(&methods);
    gc_free_all();
}
