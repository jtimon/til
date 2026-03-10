#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scavenger.h"

// Name-to-Expr map (for top-level decls and namespace methods)
static Expr *map_get_expr(Map *m, Str *key) {
    if (!*Map_has(m, key)) return NULL;
    return *(Expr **)Map_get(m, key);
}

// Garbage collector for Str* allocated during scavenging
static Vec gc_strs;

static Str *gc_str(Str *s) {
    cvec_push(&gc_strs, &s);
    return s;
}

static void gc_free_all(void) {
    for (U32 i = 0; i < gc_strs.count; i++)
        Str_delete(*(Str **)Vec_get(&gc_strs, &(U64){(U64)(i)}), &(Bool){1});
    Vec_delete(&gc_strs, &(Bool){0});
}

// Build a qualified name "Type.method"
static Str *qualified_name(Str *type_name, Str *method_name) {
    U64 len = type_name->count + 1 + method_name->count;
    char *buf = malloc(len + 1);
    snprintf(buf, len + 1, "%s.%s", type_name->c_str, method_name->c_str);
    Str *s = Str_new(buf);
    free(buf);
    return gc_str(s);
}

// Collect all name references from an AST subtree into refs
static void vec_push_str(Vec *v, Str *s) {
    cvec_push(v, &s);
}

static void collect_refs(Expr *e, Vec *refs) {
    if (!e) return;

    switch (e->type.tag) {
    case NODE_IDENT:
        vec_push_str(refs, e->type.str_val);
        break;

    case NODE_FCALL:
        // Check for namespace method call: Type.method(args...)
        if (e->children.count > 0 && expr_child(e, 0)->type.tag == NODE_FIELD_ACCESS &&
            expr_child(e, 0)->is_ns_field) {
            Expr *fa = expr_child(e, 0);
            Str *type_name = expr_child(fa, 0)->type.str_val;
            Str *method = fa->type.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, method));
            // Recurse into args (skip callee — already handled)
            for (U32 i = 1; i < e->children.count; i++)
                collect_refs(expr_child(e, i), refs);
            return;
        }
        // array()/vec() builtins need Array/Vec constructor methods
        if (e->children.count >= 2 && expr_child(e, 0)->type.tag == NODE_IDENT) {
            Str *cn = expr_child(e, 0)->type.str_val;
            // array()/vec() builtins: their namespace methods are called from
            // C code (ext.c/dispatch.c) which the scavenger can't see
            if (strcmp(cn->c_str, "array") == 0) {
                Str *arr = gc_str(Str_new("Array"));
                vec_push_str(refs, qualified_name(arr, gc_str(Str_new("new"))));
                vec_push_str(refs, qualified_name(arr, gc_str(Str_new("set"))));
                vec_push_str(refs, qualified_name(arr, gc_str(Str_new("delete"))));
            } else if (strcmp(cn->c_str, "vec") == 0) {
                Str *vec = gc_str(Str_new("Vec"));
                vec_push_str(refs, qualified_name(vec, gc_str(Str_new("new"))));
                vec_push_str(refs, qualified_name(vec, gc_str(Str_new("push"))));
                vec_push_str(refs, qualified_name(vec, gc_str(Str_new("delete"))));
            }
        }
        break;

    case NODE_FUNC_DEF: {
        U32 np = e->type.func_def.nparam;
        I32 fvi = e->type.func_def.variadic_index;
        for (U32 i = 0; i < np; i++) {
            if (e->type.func_def.param_types[i])
                vec_push_str(refs, e->type.func_def.param_types[i]);
        }
        if (fvi >= 0) {
            // Variadic param uses Array internally
            Str *arr = gc_str(Str_new("Array"));
            vec_push_str(refs, arr);
            vec_push_str(refs, qualified_name(arr, gc_str(Str_new("new"))));
            vec_push_str(refs, qualified_name(arr, gc_str(Str_new("set"))));
            vec_push_str(refs, qualified_name(arr, gc_str(Str_new("delete"))));
        }
        if (e->type.func_def.return_type)
            vec_push_str(refs, e->type.func_def.return_type);
        break;
    }

    case NODE_FIELD_ACCESS:
        // Namespace field access: Type.field
        if (e->is_ns_field && expr_child(e, 0)->type.tag == NODE_IDENT) {
            Str *type_name = expr_child(e, 0)->type.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, e->type.str_val));
        }
        break;

    case NODE_FIELD_ASSIGN:
        // Namespace field assignment: Type.field = value
        if (e->is_ns_field && expr_child(e, 0)->type.tag == NODE_IDENT) {
            Str *type_name = expr_child(e, 0)->type.str_val;
            vec_push_str(refs, type_name);
            vec_push_str(refs, qualified_name(type_name, e->type.str_val));
        }
        break;

    case NODE_DECL:
        if (e->type.decl.explicit_type)
            vec_push_str(refs, e->type.decl.explicit_type);
        break;

    default:
        break;
    }

    // Recurse into children
    for (U32 i = 0; i < e->children.count; i++)
        collect_refs(expr_child(e, i), refs);
}

void scavenge(Expr *program, const Mode *mode, Bool run_tests) {
    Bool is_cli = mode && mode->needs_main && !run_tests;

    gc_strs = cvec_new(sizeof(Str *));

    // 1. Build top-level declaration map
    Map top = cmap_new(sizeof(Str), sizeof(Expr *));
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL) {
            Str *name = stmt->type.decl.name;
            cmap_set(&top, name, &stmt);
        }
    }

    // 2. Build namespace method map: "Type.method" → method decl node
    Map methods = cmap_new(sizeof(Str), sizeof(Expr *));
    for (U32 i = 0; i < top.count; i++) {
        Expr *decl = *(Expr **)(top.val_data + i * top.val_size);
        if (expr_child(decl, 0)->type.tag != NODE_STRUCT_DEF &&
            expr_child(decl, 0)->type.tag != NODE_ENUM_DEF) continue;
        Str *sname = (Str *)(top.key_data + i * top.key_size);
        Expr *body = expr_child(expr_child(decl, 0), 0);
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (!field->type.decl.is_namespace) continue;
            Str *qn = qualified_name(sname, field->type.decl.name);
            cmap_set(&methods, qn, &field);
        }
    }

    // 3. Seed worklist
    Vec worklist = cvec_new(sizeof(Str *));
    if (is_cli) {
        vec_push_str(&worklist, gc_str(Str_new("main")));
        // Also seed from top-level variable declarations (e.g. mode auto-imports)
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type.tag == NODE_DECL &&
                (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
                 expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
                 expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF))
                continue;
            collect_refs(stmt, &worklist);
        }
    } else if (run_tests) {
        // Test execution: seed with all test function names
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type.tag == NODE_DECL && expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF &&
                expr_child(stmt, 0)->type.func_def.func_type == FUNC_TEST) {
                vec_push_str(&worklist, stmt->type.decl.name);
            }
        }
    } else {
        // Script mode: collect refs from all top-level executable statements
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type.tag == NODE_DECL &&
                (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
                 expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
                 expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF))
                continue;
            collect_refs(stmt, &worklist);
        }
    }

    // 4. BFS
    Set visited = cset_new(sizeof(Str));
    U32 cursor = 0;
    while (cursor < worklist.count) {
        Str *name = *(Str **)Vec_get(&worklist, &(U64){(U64)(cursor++)});
        if (*Set_has(&visited, name)) continue;
        cset_add(&visited, name);

        // Top-level declaration?
        Expr *decl = map_get_expr(&top, name);
        if (decl) {
            if (expr_child(decl, 0)->type.tag == NODE_STRUCT_DEF ||
                expr_child(decl, 0)->type.tag == NODE_ENUM_DEF) {
                // For structs/enums: only walk instance fields, not namespace methods.
                // Namespace methods are walked individually via qualified names.
                Expr *body = expr_child(expr_child(decl, 0), 0);
                for (U32 i = 0; i < body->children.count; i++) {
                    if (!expr_child(body, i)->type.decl.is_namespace)
                        collect_refs(expr_child(body, i), &worklist);
                }
                // Always keep infrastructure methods — collections use dyn_call
                // which scavenger can't trace (delete, clone, size, cmp)
                vec_push_str(&worklist, qualified_name(name, gc_str(Str_new("delete"))));
                vec_push_str(&worklist, qualified_name(name, gc_str(Str_new("clone"))));
                vec_push_str(&worklist, qualified_name(name, gc_str(Str_new("size"))));
                vec_push_str(&worklist, qualified_name(name, gc_str(Str_new("cmp"))));
            } else {
                collect_refs(expr_child(decl, 0), &worklist);
            }
        }

        // Namespace method?
        Expr *method = map_get_expr(&methods, name);
        if (method && expr_child(method, 0)->type.tag == NODE_FUNC_DEF) {
            collect_refs(expr_child(method, 0), &worklist);
        }
    }

    // 5. Filter top-level declarations
    I32 w = 0;
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL &&
            (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF)) {
            Str *dname = stmt->type.decl.name;
            if (!*Set_has(&visited, dname)) continue;
        }
        expr_child(program, w++) = stmt;
    }
    program->children.count = w;

    // 6. Filter namespace methods in kept structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL || (expr_child(stmt, 0)->type.tag != NODE_STRUCT_DEF &&
                                        expr_child(stmt, 0)->type.tag != NODE_ENUM_DEF))
            continue;
        Str *sname = stmt->type.decl.name;
        Expr *body = expr_child(expr_child(stmt, 0), 0);
        I32 bw = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.decl.is_namespace) {
                Str *qn = qualified_name(sname, field->type.decl.name);
                if (!*Set_has(&visited, qn)) continue;
            }
            expr_child(body, bw++) = field;
        }
        body->children.count = bw;
    }

    // Cleanup
    Vec_delete(&worklist, &(Bool){0});
    Set_delete(&visited, &(Bool){0});
    Map_delete(&top, &(Bool){0});
    Map_delete(&methods, &(Bool){0});
    gc_free_all();
}
