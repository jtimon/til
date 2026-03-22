#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../boot/modes.h"
#include "pre70.h"

// Forward declaration for til-generated function (scavenger.til)
Str *qualified_name(Str *type_name, Str *method_name);

// Name-to-Expr map (for top-level decls and namespace methods)
static Expr *map_get_expr(Map *m, Str *key) {
    if (!*Map_has(m, key)) return NULL;
    return *(Expr **)Map_get(m, key);
}

// Garbage collector for Str* allocated during scavenging
static Vec gc_strs;

static Str *gc_str(Str *s) {
    { Str **_p = malloc(sizeof(Str *)); *_p = s; Vec_push(&gc_strs, _p); }
    return s;
}

static void gc_free_all(void) {
    for (U32 i = 0; i < gc_strs.count; i++)
        Str_delete(*(Str **)Vec_get(&gc_strs, &(USize){(USize)(i)}), &(Bool){1});
    Vec_delete(&gc_strs, &(Bool){0});
}

// Collect all name references from an AST subtree into refs
static void vec_push_str(Vec *v, Str *s) {
    { Str **_p = malloc(sizeof(Str *)); *_p = s; Vec_push(v, _p); }
}

static void collect_refs(Expr *e, Vec *refs) {
    if (!e) return;

    switch (e->data.tag) {
    case ExprData_TAG_Ident:
        vec_push_str(refs, &e->data.data.Ident);
        break;

    case ExprData_TAG_FCall:
        // Check for namespace method call: Type.method(args...)
        if (e->children.count > 0 && Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
            Expr_child(e, &(USize){(USize)(0)})->is_ns_field) {
            Expr *fa = Expr_child(e, &(USize){(USize)(0)});
            Str *type_name = &Expr_child(fa, &(USize){(USize)(0)})->data.data.Ident;
            Str *method = &fa->data.data.FieldAccess;
            vec_push_str(refs, type_name);
            vec_push_str(refs, gc_str(qualified_name(type_name, method)));
            // Recurse into args (skip callee — already handled)
            for (U32 i = 1; i < e->children.count; i++)
                collect_refs(Expr_child(e, &(USize){(USize)(i)}), refs);
            return;
        }
        // array()/vec() builtins need Array/Vec constructor methods
        if (e->children.count >= 2 && Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
            Str *cn = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
            // array()/vec() builtins: their namespace methods are called from
            // C code (ext.c/dispatch.c) which the scavenger can't see
            if (strcmp((const char *)cn->c_str, "array") == 0) {
                Str *arr = gc_str(Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT}));
                vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"new", .count = 3, .cap = CAP_LIT})))));
                vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"set", .count = 3, .cap = CAP_LIT})))));
                vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT})))));
            } else if (strcmp((const char *)cn->c_str, "vec") == 0) {
                Str *vec = gc_str(Str_clone(&(Str){.c_str = (U8*)"Vec", .count = 3, .cap = CAP_LIT}));
                vec_push_str(refs, gc_str(qualified_name(vec, gc_str(Str_clone(&(Str){.c_str = (U8*)"new", .count = 3, .cap = CAP_LIT})))));
                vec_push_str(refs, gc_str(qualified_name(vec, gc_str(Str_clone(&(Str){.c_str = (U8*)"push", .count = 4, .cap = CAP_LIT})))));
                vec_push_str(refs, gc_str(qualified_name(vec, gc_str(Str_clone(&(Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT})))));
            }
        }
        break;

    case ExprData_TAG_FuncDef: {
        U32 np = e->data.data.FuncDef.nparam;
        I32 fvi = e->data.data.FuncDef.variadic_index;
        for (U32 i = 0; i < np; i++) {
            Param *_sp = (Param*)Vec_get(&e->data.data.FuncDef.params, &(USize){(USize)(i)});
            if (_sp->ptype.count > 0)
                vec_push_str(refs, &_sp->ptype);
        }
        if (fvi >= 0) {
            // Variadic param uses Array internally
            Str *arr = gc_str(Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT}));
            vec_push_str(refs, arr);
            vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"new", .count = 3, .cap = CAP_LIT})))));
            vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"set", .count = 3, .cap = CAP_LIT})))));
            vec_push_str(refs, gc_str(qualified_name(arr, gc_str(Str_clone(&(Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT})))));
        }
        if (e->data.data.FuncDef.return_type.count > 0)
            vec_push_str(refs, &e->data.data.FuncDef.return_type);
        break;
    }

    case ExprData_TAG_FieldAccess:
        // Namespace field access: Type.field
        if (e->is_ns_field && Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
            Str *type_name = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
            vec_push_str(refs, type_name);
            vec_push_str(refs, gc_str(qualified_name(type_name, &e->data.data.FieldAccess)));
        }
        break;

    case ExprData_TAG_FieldAssign:
        // Namespace field assignment: Type.field = value
        if (e->is_ns_field && Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
            Str *type_name = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
            vec_push_str(refs, type_name);
            vec_push_str(refs, gc_str(qualified_name(type_name, &e->data.data.FieldAssign)));
        }
        break;

    case ExprData_TAG_Decl:
        if (e->data.data.Decl.explicit_type.count > 0)
            vec_push_str(refs, &e->data.data.Decl.explicit_type);
        break;

    default:
        break;
    }

    // Recurse into children
    for (U32 i = 0; i < e->children.count; i++)
        collect_refs(Expr_child(e, &(USize){(USize)(i)}), refs);
}

void scavenge(Expr *program, Mode *mode, Bool run_tests) {
    Bool is_cli = mode && mode->needs_main && !run_tests;

    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); gc_strs = *_vp; free(_vp); }

    // 1. Build top-level declaration map
    Map top; { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); top = *_mp; free(_mp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl) {
            Str *name = &stmt->data.data.Decl.name;
            { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(stmt)); memcpy(_v, &stmt, sizeof(stmt)); Map_set(&top, _k, _v); }
        }
    }

    // 2. Build namespace method map: "Type.method" → method decl node
    Map methods; { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); methods = *_mp; free(_mp); }
    for (U32 i = 0; i < top.count; i++) {
        Expr *decl = *(Expr **)(top.val_data + i * top.val_size);
        if (Expr_child(decl, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef &&
            Expr_child(decl, &(USize){(USize)(0)})->data.tag != ExprData_TAG_EnumDef) continue;
        Str *sname = (Str *)(top.key_data + i * top.key_size);
        Expr *body = Expr_child(Expr_child(decl, &(USize){(USize)(0)}), &(USize){(USize)(0)});
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (!field->data.data.Decl.is_namespace) continue;
            Str *qn = gc_str(qualified_name(sname, &field->data.data.Decl.name));
            { Str *_k = malloc(sizeof(Str)); *_k = (Str){qn->c_str, qn->count, CAP_VIEW}; void *_v = malloc(sizeof(field)); memcpy(_v, &field, sizeof(field)); Map_set(&methods, _k, _v); }
        }
    }

    // 3. Seed worklist
    Vec worklist; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); worklist = *_vp; free(_vp); }
    if (is_cli) {
        vec_push_str(&worklist, gc_str(Str_clone(&(Str){.c_str = (U8*)"main", .count = 4, .cap = CAP_LIT})));
        // Also seed from top-level variable declarations (e.g. mode auto-imports)
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == ExprData_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef))
                continue;
            collect_refs(stmt, &worklist);
        }
    } else if (run_tests) {
        // Test execution: seed with all test function names
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == ExprData_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef &&
                Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type.tag == FuncType_TAG_Test) {
                vec_push_str(&worklist, &stmt->data.data.Decl.name);
            }
        }
    } else {
        // Script mode: collect refs from all top-level executable statements
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == ExprData_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef))
                continue;
            collect_refs(stmt, &worklist);
        }
    }

    // 4. BFS
    Set visited; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); visited = *_sp; free(_sp); }
    U32 cursor = 0;
    while (cursor < worklist.count) {
        Str *name = *(Str **)Vec_get(&worklist, &(USize){(USize)(cursor++)});
        if (*Set_has(&visited, name)) continue;
        { Str *_p = malloc(sizeof(Str)); *_p = (Str){name->c_str, name->count, CAP_VIEW}; Set_add(&visited, _p); }

        // Top-level declaration?
        Expr *decl = map_get_expr(&top, name);
        if (decl) {
            if (Expr_child(decl, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
                Expr_child(decl, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef) {
                // For structs/enums: only walk instance fields, not namespace methods.
                // Namespace methods are walked individually via qualified names.
                Expr *body = Expr_child(Expr_child(decl, &(USize){(USize)(0)}), &(USize){0});
                for (U32 i = 0; i < body->children.count; i++) {
                    if (!Expr_child(body, &(USize){(USize)(i)})->data.data.Decl.is_namespace)
                        collect_refs(Expr_child(body, &(USize){(USize)(i)}), &worklist);
                }
                // Always keep infrastructure methods — collections use dyn_call
                // which scavenger can't trace (delete, clone, size, cmp)
                vec_push_str(&worklist, gc_str(qualified_name(name, gc_str(Str_clone(&(Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT})))));
                vec_push_str(&worklist, gc_str(qualified_name(name, gc_str(Str_clone(&(Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT})))));
                vec_push_str(&worklist, gc_str(qualified_name(name, gc_str(Str_clone(&(Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT})))));
                vec_push_str(&worklist, gc_str(qualified_name(name, gc_str(Str_clone(&(Str){.c_str = (U8*)"cmp", .count = 3, .cap = CAP_LIT})))));
            } else {
                collect_refs(Expr_child(decl, &(USize){(USize)(0)}), &worklist);
            }
        }

        // Namespace method?
        Expr *method = map_get_expr(&methods, name);
        if (method && Expr_child(method, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
            collect_refs(Expr_child(method, &(USize){(USize)(0)}), &worklist);
        }
    }

    // 5. Filter top-level declarations
    I32 w = 0;
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl &&
            (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef)) {
            Str *dname = &stmt->data.data.Decl.name;
            if (!*Set_has(&visited, dname)) continue;
        }
        *(Expr*)Vec_get(&program->children, &(USize){(USize)(w++)}) = *stmt;
    }
    program->children.count = w;

    // 6. Filter namespace methods in kept structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl || (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef &&
                                        Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_EnumDef))
            continue;
        Str *sname = &stmt->data.data.Decl.name;
        Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)});
        I32 bw = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.data.Decl.is_namespace) {
                Str *qn = gc_str(qualified_name(sname, &field->data.data.Decl.name));
                if (!*Set_has(&visited, qn)) continue;
            }
            *(Expr*)Vec_get(&body->children, &(USize){(USize)(bw++)}) = *field;
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
