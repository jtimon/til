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
static Vec gc_strs;

static Str *gc_str(Str *s) {
    Vec_push(&gc_strs, &s);
    return s;
}

static void gc_free_all(void) {
    for (int i = 0; i < gc_strs.len; i++)
        Str_delete(((Str **)gc_strs.data)[i]);
    Vec_delete(&gc_strs);
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
        if (e->children.len > 0 && expr_child(e, 0)->type == NODE_FIELD_ACCESS &&
            expr_child(e, 0)->is_ns_field) {
            Expr *fa = expr_child(e, 0);
            Str *type_name = expr_child(fa, 0)->data.str_val;
            Str *method = fa->data.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, method));
            // Recurse into args (skip callee — already handled)
            for (int i = 1; i < e->children.len; i++)
                collect_refs(expr_child(e, i), refs);
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
        if (e->is_ns_field && expr_child(e, 0)->type == NODE_IDENT) {
            Str *type_name = expr_child(e, 0)->data.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, e->data.str_val));
        }
        break;

    case NODE_FIELD_ASSIGN:
        // Namespace field assignment: Type.field = value
        if (e->is_ns_field && expr_child(e, 0)->type == NODE_IDENT) {
            Str *type_name = expr_child(e, 0)->data.str_val;
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
    for (int i = 0; i < e->children.len; i++)
        collect_refs(expr_child(e, i), refs);
}

void scavenge(Expr *program, Str *mode) {
    int is_cli = mode && strcmp(mode->c_str, "cli") == 0;

    gc_strs = Vec_new(sizeof(Str *));

    // 1. Build top-level declaration map
    Map top = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL) {
            Str *name = stmt->data.decl.name;
            Map_set(&top, &name, &stmt);
        }
    }

    // 2. Build namespace method map: "Type.method" → method decl node
    Map methods = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (int i = 0; i < Map_len(&top); i++) {
        Expr *decl = ((Expr **)top.vals.data)[i];
        if (expr_child(decl, 0)->type != NODE_STRUCT_DEF &&
            expr_child(decl, 0)->type != NODE_ENUM_DEF) continue;
        Str *sname = ((Str **)top.keys.data)[i];
        Expr *body = expr_child(expr_child(decl, 0), 0);
        for (int j = 0; j < body->children.len; j++) {
            Expr *field = expr_child(body, j);
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
        for (int i = 0; i < program->children.len; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type == NODE_DECL &&
                (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
                 expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                 expr_child(stmt, 0)->type == NODE_ENUM_DEF))
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
            if (expr_child(decl, 0)->type == NODE_STRUCT_DEF ||
                expr_child(decl, 0)->type == NODE_ENUM_DEF) {
                // For structs/enums: only walk instance fields, not namespace methods.
                // Namespace methods are walked individually via qualified names.
                Expr *body = expr_child(expr_child(decl, 0), 0);
                for (int i = 0; i < body->children.len; i++) {
                    if (!expr_child(body, i)->data.decl.is_namespace)
                        collect_refs(expr_child(body, i), &worklist);
                }
            } else {
                collect_refs(expr_child(decl, 0), &worklist);
            }
        }

        // Namespace method?
        Expr *method = map_get_expr(&methods, name);
        if (method && expr_child(method, 0)->type == NODE_FUNC_DEF) {
            collect_refs(expr_child(method, 0), &worklist);
        }
    }

    // 5. Filter top-level declarations
    int w = 0;
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL &&
            (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *dname = stmt->data.decl.name;
            if (!Set_has(&visited, &dname)) continue;
        }
        expr_child(program, w++) = stmt;
    }
    program->children.len = w;

    // 6. Filter namespace methods in kept structs
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type != NODE_DECL || (expr_child(stmt, 0)->type != NODE_STRUCT_DEF &&
                                        expr_child(stmt, 0)->type != NODE_ENUM_DEF))
            continue;
        Str *sname = stmt->data.decl.name;
        Expr *body = expr_child(expr_child(stmt, 0), 0);
        int bw = 0;
        for (int j = 0; j < body->children.len; j++) {
            Expr *field = expr_child(body, j);
            if (field->data.decl.is_namespace) {
                Str *qn = qualified_name(sname, field->data.decl.name);
                if (!Set_has(&visited, &qn)) continue;
            }
            expr_child(body, bw++) = field;
        }
        body->children.len = bw;
    }

    // Cleanup
    Vec_delete(&worklist);
    Set_delete(&visited);
    Map_delete(&top);
    Map_delete(&methods);
    gc_free_all();
}
