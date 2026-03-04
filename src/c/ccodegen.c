#include "ccodegen.h"
#include "map.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Expr *codegen_program; // set during codegen for ns_init lookups
static Map struct_bodies; // Str* name → Expr* body (NODE_BODY)

static Expr *find_struct_body(Str *name) {
    Expr **p = Map_get(&struct_bodies, &name);
    return p ? *p : NULL;
}

// --- Emitter helpers ---

static void emit_indent(FILE *f, int depth) {
    for (int i = 0; i < depth; i++) fprintf(f, "    ");
}

// Emit expression dereferenced to a value: (*x) for IDENT, plain for literals/builtins
static void emit_deref(FILE *f, Expr *e, int depth);
// Emit expression as a pointer: wraps values in &(type){val}
static void emit_as_ptr(FILE *f, Expr *e, int depth);

// --- Forward declarations ---

static void emit_expr(FILE *f, Expr *e, int depth);
static void emit_stmt(FILE *f, Expr *e, int depth);
static void emit_body(FILE *f, Expr *body, int depth);

// --- Expression emission ---

static void emit_expr(FILE *f, Expr *e, int depth) {
    (void)depth;
    switch (e->type) {
    case NODE_LITERAL_STR:
        fprintf(f, "Str_new(\"%s\")", e->data.str_val->c_str);
        break;
    case NODE_LITERAL_NUM:
        fprintf(f, "%s", e->data.str_val->c_str);
        break;
    case NODE_LITERAL_BOOL:
        fprintf(f, "%d", Str_eq_c(e->data.str_val, "true") ? 1 : 0);
        break;
    case NODE_IDENT:
        fprintf(f, "%s", e->data.str_val->c_str);
        break;
    case NODE_FCALL: {
        // Namespace method call: Struct.method(args)
        if (expr_child(e, 0)->type == NODE_FIELD_ACCESS) {
            Str *sname = expr_child(expr_child(e, 0), 0)->struct_name;
            Str *mname = expr_child(e, 0)->data.str_val;
            fprintf(f, "til_%s_%s(", sname->c_str, mname->c_str);
            for (int i = 1; i < e->children.len; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
            break;
        }
        Str *name = expr_child(e, 0)->data.str_val;
        if (Str_eq_c(name, "println")) {
            fprintf(f, "til_println(%d", e->children.len - 1);
            for (int i = 1; i < e->children.len; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "print")) {
            fprintf(f, "til_print(%d", e->children.len - 1);
            for (int i = 1; i < e->children.len; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "format")) {
            fprintf(f, "til_format(%d", e->children.len - 1);
            for (int i = 1; i < e->children.len; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        } else if (e->struct_name && Str_eq(name, e->struct_name)) {
            // Struct constructor — compound literal (handled in emit_stmt)
            fprintf(f, "/* BUG: struct constructor in expr context */");
        } else {
            // User-defined function call
            fprintf(f, "til_%s(", name->c_str);
            for (int i = 1; i < e->children.len; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        Expr *obj = expr_child(e, 0);
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "til_%s_%s", obj->struct_name->c_str, fname->c_str);
            // Auto-call enum variant constructors (Color.Red → til_Color_Red())
            if (e->til_type == TIL_TYPE_ENUM) fprintf(f, "()");
        } else {
            emit_expr(f, obj, depth);
            int use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s", use_dot ? "." : "->", fname->c_str);
        }
        break;
    }
    default:
        fprintf(f, "/* TODO: expr type %d */", e->type);
        break;
    }
}

// --- Type to C type string ---

static const char *til_type_to_c(TilType t) {
    switch (t) {
    case TIL_TYPE_I64:  return "til_I64";
    case TIL_TYPE_U8:   return "til_U8";
    case TIL_TYPE_STR:  return "Str";
    case TIL_TYPE_BOOL: return "til_Bool";
    case TIL_TYPE_NONE: return "void";
    default:            return "til_I64"; // fallback
    }
}

// C type name without pointer — "til_Point" for structs, "til_I64" for I64, etc.
static const char *c_type_name(TilType t, Str *struct_name) {
    if ((t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM) && struct_name) {
        static char buf[128];
        snprintf(buf, sizeof(buf), "til_%s", struct_name->c_str);
        return buf;
    }
    return til_type_to_c(t);
}

// Convert a type name string to C type string (handles struct types)
static const char *type_name_to_c(Str *name) {
    if (Str_eq_c(name, "I64"))  return "til_I64 *";
    if (Str_eq_c(name, "U8"))   return "til_U8 *";
    if (Str_eq_c(name, "Str"))  return "Str *";
    if (Str_eq_c(name, "Bool")) return "til_Bool *";
    // User-defined struct type — pointer
    static char buf[128];
    snprintf(buf, sizeof(buf), "til_%s *", name->c_str);
    return buf;
}

static void emit_deref(FILE *f, Expr *e, int depth) {
    if (e->type == NODE_IDENT) {
        fprintf(f, "(*");
        emit_expr(f, e, depth);
        fprintf(f, ")");
    } else if (e->type == NODE_LITERAL_STR) {
        // Str_new returns Str *, but we need a Str value here; use Str_val
        fprintf(f, "Str_val(\"%s\")", e->data.str_val->c_str);
    } else if (e->type == NODE_FIELD_ACCESS && e->is_ns_field && e->til_type == TIL_TYPE_ENUM) {
        // Auto-called constructor returns pointer; dereference it
        fprintf(f, "(*");
        emit_expr(f, e, depth);
        fprintf(f, ")");
    } else {
        emit_expr(f, e, depth);
    }
}

// Emit expression as a pointer — after hoisting, args are NODE_IDENT (already pointer)
// or NODE_FIELD_ACCESS (value needing compound literal wrapping).
static void emit_as_ptr(FILE *f, Expr *e, int depth) {
    if (e->type == NODE_IDENT || e->type == NODE_FCALL || e->type == NODE_LITERAL_STR) {
        emit_expr(f, e, depth);
    } else if (e->type == NODE_FIELD_ACCESS) {
        // Own field is already a pointer; enum ns_field constructor returns pointer; inline field needs address-of
        if (e->is_own_field || (e->is_ns_field && e->til_type == TIL_TYPE_ENUM)) {
            emit_expr(f, e, depth);
        } else {
            fprintf(f, "&");
            emit_expr(f, e, depth);
        }
    } else {
        const char *ctype = c_type_name(e->til_type, e->struct_name);
        fprintf(f, "&(%s){", ctype);
        emit_expr(f, e, depth);
        fprintf(f, "}");
    }
}

// Emit struct constructor field assignments into 'var' (already malloc'd).
static int _ctor_seq = 0;
static void emit_ctor_fields(FILE *f, const char *var, Expr *ctor, int depth) {
    Expr *sbody = find_struct_body(ctor->struct_name);
    int fi = 0;
    for (int i = 1; i < ctor->children.len; i++) {
        int is_own = 0;
        const char *fname = NULL;
        if (sbody) {
            for (; fi < sbody->children.len; fi++) {
                if (!expr_child(sbody, fi)->data.decl.is_namespace) {
                    is_own = expr_child(sbody, fi)->data.decl.is_own;
                    fname = expr_child(sbody, fi)->data.decl.name->c_str;
                    fi++;
                    break;
                }
            }
        }
        Expr *arg = expr_child(ctor, i);
        emit_indent(f, depth);
        if (is_own && arg->type == NODE_FCALL && arg->struct_name &&
            Str_eq(expr_child(arg, 0)->data.str_val, arg->struct_name)) {
            // Nested struct constructor for own field: emit as temp, assign pointer
            const char *ct = c_type_name(arg->til_type, arg->struct_name);
            int id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ct, tmp, ct);
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            fprintf(f, "%s->%s = %s;\n", var, fname, tmp);
        } else if (is_own) {
            fprintf(f, "%s->%s = ", var, fname);
            emit_expr(f, arg, depth);
            fprintf(f, ";\n");
        } else if (arg->type == NODE_FCALL && arg->struct_name &&
                   Str_eq(expr_child(arg, 0)->data.str_val, arg->struct_name)) {
            // Inline struct field: nested constructor — build in-place
            const char *ct = c_type_name(arg->til_type, arg->struct_name);
            int id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ct, tmp, ct);
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            fprintf(f, "%s->%s = *%s; free(%s);\n", var, fname, tmp, tmp);
        } else if (arg->type == NODE_FCALL) {
            // Unhoisted fcall for inline compound field: deref + free wrapper
            const char *ftype = c_type_name(arg->til_type, arg->struct_name);
            fprintf(f, "{ %s *_ca = ", ftype);
            emit_expr(f, arg, depth);
            fprintf(f, "; %s->%s = *_ca; free(_ca); }\n", var, fname);
        } else {
            fprintf(f, "%s->%s = ", var, fname);
            emit_deref(f, arg, depth);
            fprintf(f, ";\n");
        }
    }
}

// --- Statement emission ---

static void emit_stmt(FILE *f, Expr *e, int depth) {
    emit_indent(f, depth);
    switch (e->type) {
    case NODE_DECL:
        if (expr_child(e, 0)->type == NODE_FUNC_DEF) {
            fprintf(f, "/* TODO: nested func %s */\n", e->data.decl.name->c_str);
        } else if (expr_child(e, 0)->type == NODE_STRUCT_DEF ||
                   expr_child(e, 0)->type == NODE_ENUM_DEF) {
            fprintf(f, "/* %s %s defined above */\n",
                    expr_child(e, 0)->type == NODE_ENUM_DEF ? "enum" : "struct",
                    e->data.decl.name->c_str);
        } else if (e->data.decl.is_ref) {
            const char *ctype = c_type_name(e->til_type, expr_child(e, 0)->struct_name);
            Expr *rhs = expr_child(e, 0);
            fprintf(f, "%s *%s = ", ctype, e->data.decl.name->c_str);
            emit_expr(f, rhs, depth);
            fprintf(f, ";\n");
        } else {
            const char *ctype = c_type_name(e->til_type, expr_child(e, 0)->struct_name);
            Expr *rhs = expr_child(e, 0);
            if (rhs->type == NODE_FCALL && rhs->struct_name &&
                Str_eq(expr_child(rhs, 0)->data.str_val, rhs->struct_name)) {
                // Struct constructor — malloc + field-by-field assignment
                const char *var = e->data.decl.name->c_str;
                fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ctype, var, ctype);
                emit_ctor_fields(f, var, rhs, depth);
            } else if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR ||
                       (rhs->type == NODE_FIELD_ACCESS && rhs->is_ns_field && rhs->til_type == TIL_TYPE_ENUM)) {
                // Function calls / enum constructors already return a fresh heap pointer
                fprintf(f, "%s *%s = ", ctype, e->data.decl.name->c_str);
                emit_expr(f, rhs, depth);
                fprintf(f, ";\n");
            } else {
                // Literals and idents: allocate new memory and copy the value
                fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ctype, e->data.decl.name->c_str, ctype);
                emit_indent(f, depth);
                fprintf(f, "*%s = ", e->data.decl.name->c_str);
                emit_deref(f, rhs, depth);
                fprintf(f, ";\n");
            }
        }
        break;
    case NODE_ASSIGN: {
        Expr *rhs = expr_child(e, 0);
        if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR ||
            (rhs->type == NODE_FIELD_ACCESS && rhs->is_ns_field && rhs->til_type == TIL_TYPE_ENUM)) {
            fprintf(f, "%s = ", e->data.str_val->c_str);
            emit_expr(f, rhs, depth);
        } else {
            fprintf(f, "*%s = ", e->data.str_val->c_str);
            emit_deref(f, rhs, depth);
        }
        fprintf(f, ";\n");
        break;
    }
    case NODE_FIELD_ASSIGN: {
        Expr *obj = expr_child(e, 0);
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "til_%s_%s = ", obj->struct_name->c_str, fname->c_str);
        } else {
            emit_expr(f, obj, depth);
            int use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s = ", use_dot ? "." : "->", fname->c_str);
        }
        if (e->is_own_field) {
            emit_expr(f, expr_child(e, 1), depth);
            fprintf(f, ";\n");
        } else if (expr_child(e, 1)->type == NODE_FCALL) {
            // Unhoisted fcall for inline compound field: deref + free wrapper
            const char *ftype = c_type_name(expr_child(e, 1)->til_type, expr_child(e, 1)->struct_name);
            fprintf(f, "{ %s *_fa = ", ftype);
            emit_expr(f, expr_child(e, 1), depth);
            fprintf(f, "; ");
            emit_expr(f, obj, depth);
            int use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s = *_fa; free(_fa); }\n", use_dot ? "." : "->", fname->c_str);
        } else {
            emit_deref(f, expr_child(e, 1), depth);
            fprintf(f, ";\n");
        }
        break;
    }
    case NODE_FCALL:
        if (e->struct_name && Str_eq(expr_child(e, 0)->data.str_val, e->struct_name)) {
            // Bare struct constructor statement — discard result
            fprintf(f, "/* discarded struct constructor */;\n");
        } else {
            emit_expr(f, e, depth);
            fprintf(f, ";\n");
        }
        break;
    case NODE_RETURN:
        if (e->children.len == 0) {
            fprintf(f, "return;\n");
        } else {
            Expr *rv = expr_child(e, 0);
            if (rv->type == NODE_FCALL && rv->struct_name &&
                Str_eq(expr_child(rv, 0)->data.str_val, rv->struct_name)) {
                // Struct constructor return — malloc + field-by-field
                const char *ctype = c_type_name(rv->til_type, rv->struct_name);
                fprintf(f, "{ %s *_r = malloc(sizeof(%s));\n", ctype, ctype);
                emit_ctor_fields(f, "_r", rv, depth);
                emit_indent(f, depth);
                fprintf(f, "return _r; }\n");
            } else {
                fprintf(f, "return ");
                emit_expr(f, rv, depth);
                fprintf(f, ";\n");
            }
        }
        break;
    case NODE_BODY:
        fprintf(f, "{\n");
        emit_body(f, e, depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
        break;
    case NODE_IF:
        fprintf(f, "if (");
        emit_deref(f, expr_child(e, 0), depth);
        fprintf(f, ") {\n");
        emit_body(f, expr_child(e, 1), depth + 1);
        emit_indent(f, depth);
        if (e->children.len > 2) {
            fprintf(f, "} else {\n");
            emit_body(f, expr_child(e, 2), depth + 1);
            emit_indent(f, depth);
        }
        fprintf(f, "}\n");
        break;
    case NODE_WHILE:
        fprintf(f, "while (");
        emit_deref(f, expr_child(e, 0), depth);
        fprintf(f, ") {\n");
        emit_body(f, expr_child(e, 1), depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
        break;
    case NODE_BREAK:
        fprintf(f, "break;\n");
        break;
    case NODE_CONTINUE:
        fprintf(f, "continue;\n");
        break;
    default:
        fprintf(f, "/* TODO: stmt type %d */\n", e->type);
        break;
    }
}

static void emit_body(FILE *f, Expr *body, int depth) {
    for (int i = 0; i < body->children.len; i++) {
        emit_stmt(f, expr_child(body, i), depth);
    }
}

// --- Top-level emission ---

// Emit namespace field initializations for all structs in the program
static void emit_ns_inits(FILE *f, int depth) {
    for (int i = 0; i < codegen_program->children.len; i++) {
        Expr *stmt = expr_child(codegen_program, i);
        if (stmt->type == NODE_DECL && (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                                        expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *edef = expr_child(stmt, 0);
            Expr *body = expr_child(edef, 0);
            for (int j = 0; j < body->children.len; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (expr_child(field, 0)->type == NODE_FUNC_DEF) continue;
                // Skip enum variant literals — handled by constructor functions
                if (edef->type == NODE_ENUM_DEF) continue;
                emit_indent(f, depth);
                fprintf(f, "til_%s_%s = ", sname->c_str, field->data.decl.name->c_str);
                emit_deref(f, expr_child(field, 0), depth);
                fprintf(f, ";\n");
            }
        }
    }
}

static void emit_func_def(FILE *f, Str *name, Expr *func_def, Str *mode) {
    (void)func_def->data.func_def.func_type;
    Expr *body = expr_child(func_def, 0);

    // In cli mode, main proc becomes C main()
    int is_main = mode && Str_eq_c(mode, "cli") && Str_eq_c(name, "main");

    if (is_main) {
        fprintf(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        emit_body(f, body, 1);
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    } else {
        // Return type
        const char *ret = "void";
        if (func_def->data.func_def.return_type) {
            ret = type_name_to_c(func_def->data.func_def.return_type);
        }
        // Signature
        fprintf(f, "%s til_%s(", ret, name->c_str);
        int np = func_def->data.func_def.nparam;
        if (np == 0) {
            fprintf(f, "void");
        } else {
            for (int i = 0; i < np; i++) {
                if (i > 0) fprintf(f, ", ");
                fprintf(f, "%s %s", type_name_to_c(func_def->data.func_def.param_types[i]),
                        func_def->data.func_def.param_names[i]->c_str);
            }
        }
        fprintf(f, ") {\n");
        emit_body(f, body, 1);
        fprintf(f, "}\n");
    }
}

static void emit_struct_def(FILE *f, Str *name, Expr *struct_def) {
    Expr *body = expr_child(struct_def, 0);
    int skip_typedef = struct_def->is_ext;
    // Emit typedef struct (skip for primitives and ext_structs — C side provides)
    if (!skip_typedef) {
        int has_instance_fields = 0;
        for (int i = 0; i < body->children.len; i++)
            if (!expr_child(body, i)->data.decl.is_namespace) { has_instance_fields = 1; break; }
        fprintf(f, "typedef struct til_%s {\n", name->c_str);
        if (!has_instance_fields) {
            fprintf(f, "    char _;\n"); // padding for empty structs
        }
        for (int i = 0; i < body->children.len; i++) {
            Expr *field = expr_child(body, i);
            if (field->data.decl.is_namespace) continue;
            if (field->data.decl.is_own && field->til_type == TIL_TYPE_STRUCT && expr_child(field, 0)->struct_name) {
                fprintf(f, "    til_%s *%s;\n", expr_child(field, 0)->struct_name->c_str, field->data.decl.name->c_str);
            } else if (field->til_type == TIL_TYPE_STRUCT && expr_child(field, 0)->struct_name) {
                fprintf(f, "    til_%s %s;\n", expr_child(field, 0)->struct_name->c_str, field->data.decl.name->c_str);
            } else {
                fprintf(f, "    %s %s;\n", til_type_to_c(field->til_type), field->data.decl.name->c_str);
            }
        }
        fprintf(f, "} til_%s;\n\n", name->c_str);
        // Emit namespace fields as globals (skip func defs — emitted separately)
        for (int i = 0; i < body->children.len; i++) {
            Expr *field = expr_child(body, i);
            if (!field->data.decl.is_namespace) continue;
            if (expr_child(field, 0)->type == NODE_FUNC_DEF) continue;
            if (field->til_type == TIL_TYPE_STRUCT && expr_child(field, 0)->struct_name) {
                fprintf(f, "til_%s til_%s_%s;\n", expr_child(field, 0)->struct_name->c_str, name->c_str, field->data.decl.name->c_str);
            } else {
                fprintf(f, "%s til_%s_%s;\n", til_type_to_c(field->til_type), name->c_str, field->data.decl.name->c_str);
            }
        }
    }
    // Emit namespace functions as C functions (skip ext_funcs — handled by ext.c)
    for (int i = 0; i < body->children.len; i++) {
        Expr *field = expr_child(body, i);
        if (!field->data.decl.is_namespace) continue;
        if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(field, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.decl.name->c_str);
        Str *full_name = Str_new(full_name_buf);
        emit_func_def(f, full_name, fdef, NULL);
        Str_delete(full_name);
        fprintf(f, "\n");
    }
}

static void emit_enum_def(FILE *f, Str *name, Expr *enum_def) {
    Expr *body = expr_child(enum_def, 0);
    int hp = enum_has_payloads(enum_def);

    if (!hp) {
        // === SIMPLE ENUM ===

        // Collect variant names from non-namespace entries
        Vec vnames = Vec_new(sizeof(Str *));
        for (int i = 0; i < body->children.len; i++) {
            Expr *v = expr_child(body, i);
            if (v->data.decl.is_namespace) continue;
            Vec_push(&vnames, &v->data.decl.name);
        }

        // Zero-arg constructors
        for (int i = 0; i < vnames.len; i++) {
            Str *vn = ((Str **)vnames.data)[i];
            fprintf(f, "til_%s *til_%s_%s() {\n", name->c_str, name->c_str, vn->c_str);
            fprintf(f, "    til_%s *r = malloc(sizeof(til_%s));\n", name->c_str, name->c_str);
            fprintf(f, "    *r = (til_%s){ .tag = til_%s_TAG_%s };\n", name->c_str, name->c_str, vn->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // eq
        fprintf(f, "til_Bool *til_%s_eq(til_%s *a, til_%s *b) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool)); *r = (a->tag == b->tag); return r;\n");
        fprintf(f, "}\n");

        Vec_delete(&vnames);
    } else {
        // === PAYLOAD ENUM ===

        // Collect variant info from non-namespace entries
        Vec vnames = Vec_new(sizeof(Str *));
        Vec vtypes = Vec_new(sizeof(Str *));
        for (int i = 0; i < body->children.len; i++) {
            Expr *v = expr_child(body, i);
            if (v->data.decl.is_namespace) continue;
            Vec_push(&vnames, &v->data.decl.name);
            Vec_push(&vtypes, &v->data.decl.explicit_type);
        }

        // Constructor functions for all variants
        for (int i = 0; i < vnames.len; i++) {
            Str *vn = ((Str **)vnames.data)[i];
            Str *vt = ((Str **)vtypes.data)[i];
            if (!vt) {
                // Zero-arg constructor for no-payload variant
                fprintf(f, "til_%s *til_%s_%s() {\n", name->c_str, name->c_str, vn->c_str);
                fprintf(f, "    til_%s *r = malloc(sizeof(til_%s));\n", name->c_str, name->c_str);
                fprintf(f, "    r->tag = til_%s_TAG_%s;\n", name->c_str, vn->c_str);
                fprintf(f, "    return r;\n");
                fprintf(f, "}\n");
                continue;
            }
            const char *ptype = type_name_to_c(vt);
            fprintf(f, "til_%s *til_%s_%s(%s val) {\n", name->c_str, name->c_str, vn->c_str, ptype);
            fprintf(f, "    til_%s *r = malloc(sizeof(til_%s));\n", name->c_str, name->c_str);
            fprintf(f, "    r->tag = til_%s_TAG_%s;\n", name->c_str, vn->c_str);
            // Clone the payload to take ownership
            if (Str_eq_c(vt, "I64")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_I64)); *r->data.%s = *val;\n", vn->c_str, vn->c_str);
            } else if (Str_eq_c(vt, "U8")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_U8)); *r->data.%s = *val;\n", vn->c_str, vn->c_str);
            } else if (Str_eq_c(vt, "Bool")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_Bool)); *r->data.%s = *val;\n", vn->c_str, vn->c_str);
            } else if (Str_eq_c(vt, "Str")) {
                fprintf(f, "    r->data.%s = Str_clone(val);\n", vn->c_str);
            } else {
                fprintf(f, "    r->data.%s = til_%s_clone(val);\n", vn->c_str, vt->c_str);
            }
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // is_Variant functions
        for (int i = 0; i < vnames.len; i++) {
            Str *vn = ((Str **)vnames.data)[i];
            fprintf(f, "til_Bool *til_%s_is_%s(til_%s *self) {\n", name->c_str, vn->c_str, name->c_str);
            fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool));\n");
            fprintf(f, "    *r = (self->tag == til_%s_TAG_%s);\n", name->c_str, vn->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // get_Variant functions (payload variants only)
        for (int i = 0; i < vnames.len; i++) {
            Str *vn = ((Str **)vnames.data)[i];
            Str *vt = ((Str **)vtypes.data)[i];
            if (!vt) continue;
            const char *ptype = type_name_to_c(vt);
            fprintf(f, "%s til_%s_get_%s(til_%s *self) {\n", ptype, name->c_str, vn->c_str, name->c_str);
            // Clone the payload
            if (Str_eq_c(vt, "I64")) {
                fprintf(f, "    til_I64 *r = malloc(sizeof(til_I64)); *r = *self->data.%s; return r;\n", vn->c_str);
            } else if (Str_eq_c(vt, "U8")) {
                fprintf(f, "    til_U8 *r = malloc(sizeof(til_U8)); *r = *self->data.%s; return r;\n", vn->c_str);
            } else if (Str_eq_c(vt, "Bool")) {
                fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool)); *r = *self->data.%s; return r;\n", vn->c_str);
            } else if (Str_eq_c(vt, "Str")) {
                fprintf(f, "    return Str_clone(self->data.%s);\n", vn->c_str);
            } else {
                // Struct/enum type — call clone
                fprintf(f, "    return til_%s_clone(self->data.%s);\n", vt->c_str, vn->c_str);
            }
            fprintf(f, "}\n");
        }

        // eq: compare tags, then payloads
        fprintf(f, "til_Bool *til_%s_eq(til_%s *a, til_%s *b) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool));\n");
        fprintf(f, "    if (a->tag != b->tag) { *r = 0; return r; }\n");
        fprintf(f, "    switch (a->tag) {\n");
        for (int i = 0; i < vnames.len; i++) {
            Str *vn = ((Str **)vnames.data)[i];
            Str *vt = ((Str **)vtypes.data)[i];
            fprintf(f, "    case til_%s_TAG_%s:\n", name->c_str, vn->c_str);
            if (vt) {
                if (Str_eq_c(vt, "I64") || Str_eq_c(vt, "U8") || Str_eq_c(vt, "Bool")) {
                    fprintf(f, "        *r = (*a->data.%s == *b->data.%s); break;\n", vn->c_str, vn->c_str);
                } else if (Str_eq_c(vt, "Str")) {
                    fprintf(f, "        { til_Bool *t = til_Str_eq(a->data.%s, b->data.%s); *r = *t; free(t); break; }\n", vn->c_str, vn->c_str);
                } else {
                    fprintf(f, "        { til_Bool *t = til_%s_eq(a->data.%s, b->data.%s); *r = *t; free(t); break; }\n", vt->c_str, vn->c_str, vn->c_str);
                }
            } else {
                fprintf(f, "        *r = 1; break;\n");
            }
        }
        fprintf(f, "    }\n");
        fprintf(f, "    return r;\n");
        fprintf(f, "}\n");

        Vec_delete(&vnames);
        Vec_delete(&vtypes);
    }

    // Emit namespace func/proc methods (to_str, user methods)
    for (int i = 0; i < body->children.len; i++) {
        Expr *field = expr_child(body, i);
        if (!field->data.decl.is_namespace) continue;
        if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(field, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.decl.name->c_str);
        Str *full_name = Str_new(full_name_buf);
        emit_func_def(f, full_name, fdef, NULL);
        Str_delete(full_name);
        fprintf(f, "\n");
    }
}

int codegen_c(Expr *program, Str *mode, const char *path, const char *c_output_path) {
    (void)path;

    codegen_program = program;

    // Build struct body lookup map
    struct_bodies = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            Map_set(&struct_bodies, &sname, &body);
        }
    }
    FILE *f = fopen(c_output_path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", c_output_path);
        return 1;
    }

    fprintf(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include \"ccore.h\"\n#include \"ext.h\"\n\n");

    // All ext_func implementations are in ext.c, declared via ext.h
    fprintf(f, "\n");

    int is_script = mode && Str_eq_c(mode, "script");

    // Forward-declare all structs (skip primitives and ext_structs — C side provides)
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            if (expr_child(stmt, 0)->is_ext) continue;
            fprintf(f, "typedef struct til_%s til_%s;\n", stmt->data.decl.name->c_str, stmt->data.decl.name->c_str);
        }
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            Str *ename = stmt->data.decl.name;
            {
                // All enums: tag enum + struct
                Expr *ebody = expr_child(expr_child(stmt, 0), 0);
                int hp = enum_has_payloads(expr_child(stmt, 0));
                fprintf(f, "typedef enum {\n");
                int tag = 0;
                for (int j = 0; j < ebody->children.len; j++) {
                    Expr *v = expr_child(ebody, j);
                    if (v->data.decl.is_namespace) continue;
                    if (tag > 0) fprintf(f, ",\n");
                    fprintf(f, "    til_%s_TAG_%s", ename->c_str, v->data.decl.name->c_str);
                    tag++;
                }
                fprintf(f, "\n} til_%s_tag;\n", ename->c_str);
                fprintf(f, "typedef struct til_%s {\n", ename->c_str);
                fprintf(f, "    til_%s_tag tag;\n", ename->c_str);
                if (hp) {
                    fprintf(f, "    union {\n");
                    for (int j = 0; j < ebody->children.len; j++) {
                        Expr *v = expr_child(ebody, j);
                        if (v->data.decl.is_namespace) continue;
                        if (v->data.decl.explicit_type) {
                            fprintf(f, "        %s %s;\n",
                                    type_name_to_c(v->data.decl.explicit_type),
                                    v->data.decl.name->c_str);
                        }
                    }
                    fprintf(f, "    } data;\n");
                }
                fprintf(f, "} til_%s;\n", ename->c_str);
            }
        }
    }
    fprintf(f, "\n");

    // Forward-declare all functions (namespace methods + top-level)
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                                         expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            for (int j = 0; j < body->children.len; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
                Expr *fdef = expr_child(field, 0);
                FuncType fft = fdef->data.func_def.func_type;
                if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
                const char *ret = "void";
                if (fdef->data.func_def.return_type)
                    ret = type_name_to_c(fdef->data.func_def.return_type);
                fprintf(f, "%s til_%s_%s(", ret, sname->c_str, field->data.decl.name->c_str);
                int np = fdef->data.func_def.nparam;
                if (np == 0) {
                    fprintf(f, "void");
                } else {
                    for (int k = 0; k < np; k++) {
                        if (k > 0) fprintf(f, ", ");
                        fprintf(f, "%s %s", type_name_to_c(fdef->data.func_def.param_types[k]),
                                fdef->data.func_def.param_names[k]->c_str);
                    }
                }
                fprintf(f, ");\n");
            }
        } else if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            Expr *func_def = expr_child(stmt, 0);
            FuncType fft = func_def->data.func_def.func_type;
            if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
            Str *name = stmt->data.decl.name;
            int is_main = mode && Str_eq_c(mode, "cli") && Str_eq_c(name, "main");
            if (is_main) continue;
            const char *ret = "void";
            if (func_def->data.func_def.return_type)
                ret = type_name_to_c(func_def->data.func_def.return_type);
            fprintf(f, "%s til_%s(", ret, name->c_str);
            int np = func_def->data.func_def.nparam;
            if (np == 0) {
                fprintf(f, "void");
            } else {
                for (int j = 0; j < np; j++) {
                    if (j > 0) fprintf(f, ", ");
                    fprintf(f, "%s %s", type_name_to_c(func_def->data.func_def.param_types[j]),
                            func_def->data.func_def.param_names[j]->c_str);
                }
            }
            fprintf(f, ");\n");
        }
    }
    // Forward-declare enum ext methods (eq, constructors + payload methods)
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            Str *sname = stmt->data.decl.name;
            int hp = enum_has_payloads(expr_child(stmt, 0));
            fprintf(f, "til_Bool *til_%s_eq(til_%s *, til_%s *);\n", sname->c_str, sname->c_str, sname->c_str);
            Expr *ebody = expr_child(expr_child(stmt, 0), 0);
            for (int j = 0; j < ebody->children.len; j++) {
                Expr *v = expr_child(ebody, j);
                if (v->data.decl.is_namespace) continue;
                if (hp) {
                    // is_Variant
                    fprintf(f, "til_Bool *til_%s_is_%s(til_%s *);\n", sname->c_str, v->data.decl.name->c_str, sname->c_str);
                }
                if (v->data.decl.explicit_type) {
                    // Payload constructor
                    fprintf(f, "til_%s *til_%s_%s(%s);\n", sname->c_str, sname->c_str,
                            v->data.decl.name->c_str, type_name_to_c(v->data.decl.explicit_type));
                    // get_Variant
                    fprintf(f, "%s til_%s_get_%s(til_%s *);\n",
                            type_name_to_c(v->data.decl.explicit_type),
                            sname->c_str, v->data.decl.name->c_str, sname->c_str);
                } else {
                    // Zero-arg constructor
                    fprintf(f, "til_%s *til_%s_%s();\n", sname->c_str, sname->c_str,
                            v->data.decl.name->c_str);
                }
            }
        }
    }
    fprintf(f, "\n");

    // First pass: emit struct/enum definitions
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            emit_struct_def(f, stmt->data.decl.name, expr_child(stmt, 0));
            fprintf(f, "\n");
        }
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            emit_enum_def(f, stmt->data.decl.name, expr_child(stmt, 0));
            fprintf(f, "\n");
        }
    }

    fprintf(f, "\n");

    // Second pass: emit func/proc definitions (skip ext_func/ext_proc builtins)
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            FuncType fft2 = expr_child(stmt, 0)->data.func_def.func_type;
            if (fft2 == FUNC_EXT_FUNC || fft2 == FUNC_EXT_PROC) continue;
            emit_func_def(f, stmt->data.decl.name, expr_child(stmt, 0), mode);
            fprintf(f, "\n");
        }
    }

    // Script mode: wrap top-level statements in main()
    if (is_script) {
        fprintf(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        for (int i = 0; i < program->children.len; i++) {
            Expr *stmt = expr_child(program, i);
            // Skip func/proc/struct defs (already emitted above)
            if (stmt->type == NODE_DECL &&
                (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
                 expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                 expr_child(stmt, 0)->type == NODE_ENUM_DEF))
                continue;
            emit_stmt(f, stmt, 1);
        }
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    }

    fclose(f);
    Map_delete(&struct_bodies);
    return 0;
}

int compile_c(const char *c_path, const char *bin_path, const char *ext_c_path) {
    // Extract directory from ext_c_path for -I flag
    char ext_dir[256];
    const char *last_slash = strrchr(ext_c_path, '/');
    if (last_slash) {
        int dlen = (int)(last_slash - ext_c_path);
        snprintf(ext_dir, sizeof(ext_dir), "%.*s", dlen, ext_c_path);
    } else {
        snprintf(ext_dir, sizeof(ext_dir), ".");
    }

    // Build the cc command — also compile str.c and ccore.c
    char str_c_path[256], ccore_c_path[256];
    snprintf(str_c_path, sizeof(str_c_path), "%s/str.c", ext_dir);
    snprintf(ccore_c_path, sizeof(ccore_c_path), "%s/ccore.c", ext_dir);
    int len = snprintf(NULL, 0, "cc -Wall -Wextra -I%s -o %s %s %s %s %s",
                       ext_dir, bin_path, c_path, ext_c_path, str_c_path, ccore_c_path);
    char *cmd = malloc(len + 1);
    snprintf(cmd, len + 1, "cc -Wall -Wextra -I%s -o %s %s %s %s %s",
             ext_dir, bin_path, c_path, ext_c_path, str_c_path, ccore_c_path);

    int result = system(cmd);
    free(cmd);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
