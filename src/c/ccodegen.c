#include "ccodegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Expr *codegen_program; // set during codegen for struct lookups

// Check if an enum def has payload variants
static int cg_enum_has_payloads(Expr *enum_def) {
    Expr *body = enum_def->children[0];
    for (int i = 0; i < body->nchildren; i++) {
        Expr *f = body->children[i];
        if (f->type == NODE_DECL && !f->data.decl.is_namespace && f->data.decl.explicit_type)
            return 1;
    }
    return 0;
}

// Find struct body (NODE_BODY) by struct name in the program
static Expr *find_struct_body(Str *name) {
    for (int i = 0; i < codegen_program->nchildren; i++) {
        Expr *stmt = codegen_program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF &&
            Str_eq(stmt->data.decl.name, name)) {
            return stmt->children[0]->children[0]; // NODE_BODY
        }
    }
    return NULL;
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
        if (e->children[0]->type == NODE_FIELD_ACCESS) {
            Str *sname = e->children[0]->children[0]->struct_name;
            Str *mname = e->children[0]->data.str_val;
            fprintf(f, "til_%s_%s(", sname->c_str, mname->c_str);
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, e->children[i], depth);
            }
            fprintf(f, ")");
            break;
        }
        Str *name = e->children[0]->data.str_val;
        if (Str_eq_c(name, "println")) {
            fprintf(f, "til_println(%d", e->nchildren - 1);
            for (int i = 1; i < e->nchildren; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "print")) {
            fprintf(f, "til_print(%d", e->nchildren - 1);
            for (int i = 1; i < e->nchildren; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "format")) {
            fprintf(f, "til_format(%d", e->nchildren - 1);
            for (int i = 1; i < e->nchildren; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        } else if (e->struct_name && Str_eq(name, e->struct_name)) {
            // Struct constructor — compound literal (handled in emit_stmt)
            fprintf(f, "/* BUG: struct constructor in expr context */");
        } else {
            // User-defined function call
            fprintf(f, "til_%s(", name->c_str);
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        Expr *obj = e->children[0];
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "til_%s_%s", obj->struct_name->c_str, fname->c_str);
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
        // Own field is already a pointer; inline field needs address-of
        if (e->is_own_field) {
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

// --- Statement emission ---

static void emit_stmt(FILE *f, Expr *e, int depth) {
    emit_indent(f, depth);
    switch (e->type) {
    case NODE_DECL:
        if (e->children[0]->type == NODE_FUNC_DEF) {
            fprintf(f, "/* TODO: nested func %s */\n", e->data.decl.name->c_str);
        } else if (e->children[0]->type == NODE_STRUCT_DEF ||
                   e->children[0]->type == NODE_ENUM_DEF) {
            fprintf(f, "/* %s %s defined above */\n",
                    e->children[0]->type == NODE_ENUM_DEF ? "enum" : "struct",
                    e->data.decl.name->c_str);
        } else if (e->data.decl.is_ref) {
            const char *ctype = c_type_name(e->til_type, e->children[0]->struct_name);
            Expr *rhs = e->children[0];
            fprintf(f, "%s *%s = ", ctype, e->data.decl.name->c_str);
            emit_expr(f, rhs, depth);
            fprintf(f, ";\n");
        } else {
            const char *ctype = c_type_name(e->til_type, e->children[0]->struct_name);
            Expr *rhs = e->children[0];
            if (rhs->type == NODE_FCALL && rhs->struct_name &&
                Str_eq(rhs->children[0]->data.str_val, rhs->struct_name)) {
                // Struct constructor — malloc + compound literal
                fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ctype, e->data.decl.name->c_str, ctype);
                if (rhs->nchildren > 1) {
                    emit_indent(f, depth);
                    fprintf(f, "*%s = (%s){", e->data.decl.name->c_str, ctype);
                    Expr *sbody = find_struct_body(rhs->struct_name);
                    int fi = 0;
                    for (int i = 1; i < rhs->nchildren; i++) {
                        if (i > 1) fprintf(f, ", ");
                        int is_own = 0;
                        if (sbody) {
                            // Find the fi-th instance field
                            for (; fi < sbody->nchildren; fi++) {
                                if (!sbody->children[fi]->data.decl.is_namespace) {
                                    is_own = sbody->children[fi]->data.decl.is_own;
                                    fi++;
                                    break;
                                }
                            }
                        }
                        if (is_own) {
                            emit_expr(f, rhs->children[i], depth);
                        } else {
                            emit_deref(f, rhs->children[i], depth);
                        }
                    }
                    fprintf(f, "};\n");
                }
            } else if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR) {
                // Function calls already return a fresh heap pointer
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
        Expr *rhs = e->children[0];
        if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR) {
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
        Expr *obj = e->children[0];
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "til_%s_%s = ", obj->struct_name->c_str, fname->c_str);
        } else {
            emit_expr(f, obj, depth);
            int use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s = ", use_dot ? "." : "->", fname->c_str);
        }
        if (e->is_own_field) {
            emit_expr(f, e->children[1], depth);
        } else {
            emit_deref(f, e->children[1], depth);
        }
        fprintf(f, ";\n");
        break;
    }
    case NODE_FCALL:
        if (e->struct_name && Str_eq(e->children[0]->data.str_val, e->struct_name)) {
            // Bare struct constructor statement — discard result
            fprintf(f, "/* discarded struct constructor */;\n");
        } else {
            emit_expr(f, e, depth);
            fprintf(f, ";\n");
        }
        break;
    case NODE_RETURN:
        if (e->nchildren == 0) {
            fprintf(f, "return;\n");
        } else {
            Expr *rv = e->children[0];
            if (rv->type == NODE_FCALL && rv->struct_name &&
                Str_eq(rv->children[0]->data.str_val, rv->struct_name)) {
                // Struct constructor return — malloc + compound literal
                const char *ctype = c_type_name(rv->til_type, rv->struct_name);
                fprintf(f, "{ %s *_r = malloc(sizeof(%s));", ctype, ctype);
                if (rv->nchildren > 1) {
                    fprintf(f, " *_r = (%s){", ctype);
                    Expr *sbody = find_struct_body(rv->struct_name);
                    int fi = 0;
                    for (int i = 1; i < rv->nchildren; i++) {
                        if (i > 1) fprintf(f, ", ");
                        int is_own = 0;
                        if (sbody) {
                            for (; fi < sbody->nchildren; fi++) {
                                if (!sbody->children[fi]->data.decl.is_namespace) {
                                    is_own = sbody->children[fi]->data.decl.is_own;
                                    fi++;
                                    break;
                                }
                            }
                        }
                        if (is_own) {
                            emit_expr(f, rv->children[i], depth);
                        } else {
                            emit_deref(f, rv->children[i], depth);
                        }
                    }
                    fprintf(f, "};");
                }
                fprintf(f, " return _r; }\n");
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
        emit_deref(f, e->children[0], depth);
        fprintf(f, ") {\n");
        emit_body(f, e->children[1], depth + 1);
        emit_indent(f, depth);
        if (e->nchildren > 2) {
            fprintf(f, "} else {\n");
            emit_body(f, e->children[2], depth + 1);
            emit_indent(f, depth);
        }
        fprintf(f, "}\n");
        break;
    case NODE_WHILE:
        fprintf(f, "while (");
        emit_deref(f, e->children[0], depth);
        fprintf(f, ") {\n");
        emit_body(f, e->children[1], depth + 1);
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
    for (int i = 0; i < body->nchildren; i++) {
        emit_stmt(f, body->children[i], depth);
    }
}

// --- Top-level emission ---

// Emit namespace field initializations for all structs in the program
static void emit_ns_inits(FILE *f, int depth) {
    for (int i = 0; i < codegen_program->nchildren; i++) {
        Expr *stmt = codegen_program->children[i];
        if (stmt->type == NODE_DECL && (stmt->children[0]->type == NODE_STRUCT_DEF ||
                                        stmt->children[0]->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *edef = stmt->children[0];
            int hp = (edef->type == NODE_ENUM_DEF) ? cg_enum_has_payloads(edef) : 0;
            Expr *body = edef->children[0];
            for (int j = 0; j < body->nchildren; j++) {
                Expr *field = body->children[j];
                if (!field->data.decl.is_namespace) continue;
                if (field->children[0]->type == NODE_FUNC_DEF) continue;
                emit_indent(f, depth);
                if (hp) {
                    // Payload enum no-payload variant: compound literal init
                    fprintf(f, "til_%s_%s = (til_%s){ .tag = til_%s_TAG_%s };\n",
                            sname->c_str, field->data.decl.name->c_str,
                            sname->c_str, sname->c_str, field->data.decl.name->c_str);
                } else {
                    fprintf(f, "til_%s_%s = ", sname->c_str, field->data.decl.name->c_str);
                    emit_deref(f, field->children[0], depth);
                    fprintf(f, ";\n");
                }
            }
        }
    }
}

static void emit_func_def(FILE *f, Str *name, Expr *func_def, Str *mode) {
    (void)func_def->data.func_def.func_type;
    Expr *body = func_def->children[0];

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
    Expr *body = struct_def->children[0];
    int skip_typedef = struct_def->is_ext;
    // Emit typedef struct (skip for primitives and ext_structs — C side provides)
    if (!skip_typedef) {
        int has_instance_fields = 0;
        for (int i = 0; i < body->nchildren; i++)
            if (!body->children[i]->data.decl.is_namespace) { has_instance_fields = 1; break; }
        fprintf(f, "typedef struct til_%s {\n", name->c_str);
        if (!has_instance_fields) {
            fprintf(f, "    char _;\n"); // padding for empty structs
        }
        for (int i = 0; i < body->nchildren; i++) {
            Expr *field = body->children[i];
            if (field->data.decl.is_namespace) continue;
            if (field->data.decl.is_own && field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
                fprintf(f, "    til_%s *%s;\n", field->children[0]->struct_name->c_str, field->data.decl.name->c_str);
            } else if (field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
                fprintf(f, "    til_%s %s;\n", field->children[0]->struct_name->c_str, field->data.decl.name->c_str);
            } else {
                fprintf(f, "    %s %s;\n", til_type_to_c(field->til_type), field->data.decl.name->c_str);
            }
        }
        fprintf(f, "} til_%s;\n\n", name->c_str);
        // Emit namespace fields as globals (skip func defs — emitted separately)
        for (int i = 0; i < body->nchildren; i++) {
            Expr *field = body->children[i];
            if (!field->data.decl.is_namespace) continue;
            if (field->children[0]->type == NODE_FUNC_DEF) continue;
            if (field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
                fprintf(f, "til_%s til_%s_%s;\n", field->children[0]->struct_name->c_str, name->c_str, field->data.decl.name->c_str);
            } else {
                fprintf(f, "%s til_%s_%s;\n", til_type_to_c(field->til_type), name->c_str, field->data.decl.name->c_str);
            }
        }
    }
    // Emit namespace functions as C functions (skip ext_funcs — handled by ext.c)
    for (int i = 0; i < body->nchildren; i++) {
        Expr *field = body->children[i];
        if (!field->data.decl.is_namespace) continue;
        if (field->children[0]->type != NODE_FUNC_DEF) continue;
        Expr *fdef = field->children[0];
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
    Expr *body = enum_def->children[0];
    int hp = cg_enum_has_payloads(enum_def);

    if (!hp) {
        // === SIMPLE ENUM ===

        // Variant constants as globals
        for (int i = 0; i < body->nchildren; i++) {
            Expr *field = body->children[i];
            if (!field->data.decl.is_namespace) continue;
            if (field->children[0]->type == NODE_FUNC_DEF) continue;
            fprintf(f, "til_%s til_%s_%s;\n", name->c_str, name->c_str, field->data.decl.name->c_str);
        }
        fprintf(f, "\n");

        // eq
        fprintf(f, "til_Bool *til_%s_eq(til_%s *a, til_%s *b) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool)); *r = (*a == *b); return r;\n");
        fprintf(f, "}\n");

        // clone
        fprintf(f, "til_%s *til_%s_clone(til_%s *a) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_%s *r = malloc(sizeof(til_%s)); *r = *a; return r;\n", name->c_str, name->c_str);
        fprintf(f, "}\n");

        // delete
        fprintf(f, "void til_%s_delete(til_%s *self, til_Bool *call_free) {\n", name->c_str, name->c_str);
        fprintf(f, "    if (*call_free) free(self);\n");
        fprintf(f, "}\n");
    } else {
        // === PAYLOAD ENUM ===

        // Collect variant info from non-namespace entries
        int nvariants = 0;
        Str **vnames = NULL;
        Str **vtypes = NULL;
        for (int i = 0; i < body->nchildren; i++) {
            Expr *v = body->children[i];
            if (v->data.decl.is_namespace) continue;
            nvariants++;
            vnames = realloc(vnames, nvariants * sizeof(Str *));
            vtypes = realloc(vtypes, nvariants * sizeof(Str *));
            vnames[nvariants - 1] = v->data.decl.name;
            vtypes[nvariants - 1] = v->data.decl.explicit_type;
        }

        // No-payload variant globals
        for (int i = 0; i < nvariants; i++) {
            if (!vtypes[i]) {
                fprintf(f, "til_%s til_%s_%s;\n", name->c_str, name->c_str, vnames[i]->c_str);
            }
        }
        fprintf(f, "\n");

        // Constructor functions for payload variants (clone the value)
        for (int i = 0; i < nvariants; i++) {
            if (!vtypes[i]) continue;
            const char *ptype = type_name_to_c(vtypes[i]);
            fprintf(f, "til_%s *til_%s_%s(%s val) {\n", name->c_str, name->c_str, vnames[i]->c_str, ptype);
            fprintf(f, "    til_%s *r = malloc(sizeof(til_%s));\n", name->c_str, name->c_str);
            fprintf(f, "    r->tag = til_%s_TAG_%s;\n", name->c_str, vnames[i]->c_str);
            // Clone the payload to take ownership
            if (Str_eq_c(vtypes[i], "I64")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_I64)); *r->data.%s = *val;\n", vnames[i]->c_str, vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "U8")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_U8)); *r->data.%s = *val;\n", vnames[i]->c_str, vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "Bool")) {
                fprintf(f, "    r->data.%s = malloc(sizeof(til_Bool)); *r->data.%s = *val;\n", vnames[i]->c_str, vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "Str")) {
                fprintf(f, "    r->data.%s = Str_clone(val);\n", vnames[i]->c_str);
            } else {
                fprintf(f, "    r->data.%s = til_%s_clone(val);\n", vnames[i]->c_str, vtypes[i]->c_str);
            }
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // is_Variant functions
        for (int i = 0; i < nvariants; i++) {
            fprintf(f, "til_Bool *til_%s_is_%s(til_%s *self) {\n", name->c_str, vnames[i]->c_str, name->c_str);
            fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool));\n");
            fprintf(f, "    *r = (self->tag == til_%s_TAG_%s);\n", name->c_str, vnames[i]->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // get_Variant functions (payload variants only)
        for (int i = 0; i < nvariants; i++) {
            if (!vtypes[i]) continue;
            const char *ptype = type_name_to_c(vtypes[i]);
            fprintf(f, "%s til_%s_get_%s(til_%s *self) {\n", ptype, name->c_str, vnames[i]->c_str, name->c_str);
            // Clone the payload
            if (Str_eq_c(vtypes[i], "I64")) {
                fprintf(f, "    til_I64 *r = malloc(sizeof(til_I64)); *r = *self->data.%s; return r;\n", vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "U8")) {
                fprintf(f, "    til_U8 *r = malloc(sizeof(til_U8)); *r = *self->data.%s; return r;\n", vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "Bool")) {
                fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool)); *r = *self->data.%s; return r;\n", vnames[i]->c_str);
            } else if (Str_eq_c(vtypes[i], "Str")) {
                fprintf(f, "    return Str_clone(self->data.%s);\n", vnames[i]->c_str);
            } else {
                // Struct/enum type — call clone
                fprintf(f, "    return til_%s_clone(self->data.%s);\n", vtypes[i]->c_str, vnames[i]->c_str);
            }
            fprintf(f, "}\n");
        }

        // eq: compare tags, then payloads
        fprintf(f, "til_Bool *til_%s_eq(til_%s *a, til_%s *b) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_Bool *r = malloc(sizeof(til_Bool));\n");
        fprintf(f, "    if (a->tag != b->tag) { *r = 0; return r; }\n");
        fprintf(f, "    switch (a->tag) {\n");
        for (int i = 0; i < nvariants; i++) {
            fprintf(f, "    case til_%s_TAG_%s:\n", name->c_str, vnames[i]->c_str);
            if (vtypes[i]) {
                if (Str_eq_c(vtypes[i], "I64") || Str_eq_c(vtypes[i], "U8") || Str_eq_c(vtypes[i], "Bool")) {
                    fprintf(f, "        *r = (*a->data.%s == *b->data.%s); break;\n", vnames[i]->c_str, vnames[i]->c_str);
                } else if (Str_eq_c(vtypes[i], "Str")) {
                    fprintf(f, "        { til_Bool *t = til_Str_eq(a->data.%s, b->data.%s); *r = *t; free(t); break; }\n", vnames[i]->c_str, vnames[i]->c_str);
                } else {
                    fprintf(f, "        { til_Bool *t = til_%s_eq(a->data.%s, b->data.%s); *r = *t; free(t); break; }\n", vtypes[i]->c_str, vnames[i]->c_str, vnames[i]->c_str);
                }
            } else {
                fprintf(f, "        *r = 1; break;\n");
            }
        }
        fprintf(f, "    }\n");
        fprintf(f, "    return r;\n");
        fprintf(f, "}\n");

        // clone: copy tag + clone payload
        fprintf(f, "til_%s *til_%s_clone(til_%s *a) {\n", name->c_str, name->c_str, name->c_str);
        fprintf(f, "    til_%s *r = malloc(sizeof(til_%s));\n", name->c_str, name->c_str);
        fprintf(f, "    r->tag = a->tag;\n");
        fprintf(f, "    switch (a->tag) {\n");
        for (int i = 0; i < nvariants; i++) {
            fprintf(f, "    case til_%s_TAG_%s:\n", name->c_str, vnames[i]->c_str);
            if (vtypes[i]) {
                if (Str_eq_c(vtypes[i], "I64")) {
                    fprintf(f, "        { til_I64 *p = malloc(sizeof(til_I64)); *p = *a->data.%s; r->data.%s = p; break; }\n", vnames[i]->c_str, vnames[i]->c_str);
                } else if (Str_eq_c(vtypes[i], "U8")) {
                    fprintf(f, "        { til_U8 *p = malloc(sizeof(til_U8)); *p = *a->data.%s; r->data.%s = p; break; }\n", vnames[i]->c_str, vnames[i]->c_str);
                } else if (Str_eq_c(vtypes[i], "Bool")) {
                    fprintf(f, "        { til_Bool *p = malloc(sizeof(til_Bool)); *p = *a->data.%s; r->data.%s = p; break; }\n", vnames[i]->c_str, vnames[i]->c_str);
                } else if (Str_eq_c(vtypes[i], "Str")) {
                    fprintf(f, "        r->data.%s = Str_clone(a->data.%s); break;\n", vnames[i]->c_str, vnames[i]->c_str);
                } else {
                    fprintf(f, "        r->data.%s = til_%s_clone(a->data.%s); break;\n", vnames[i]->c_str, vtypes[i]->c_str, vnames[i]->c_str);
                }
            } else {
                fprintf(f, "        break;\n");
            }
        }
        fprintf(f, "    }\n");
        fprintf(f, "    return r;\n");
        fprintf(f, "}\n");

        // delete: free payload + free self
        fprintf(f, "void til_%s_delete(til_%s *self, til_Bool *call_free) {\n", name->c_str, name->c_str);
        fprintf(f, "    switch (self->tag) {\n");
        for (int i = 0; i < nvariants; i++) {
            fprintf(f, "    case til_%s_TAG_%s:\n", name->c_str, vnames[i]->c_str);
            if (vtypes[i]) {
                if (Str_eq_c(vtypes[i], "I64") || Str_eq_c(vtypes[i], "U8") || Str_eq_c(vtypes[i], "Bool")) {
                    fprintf(f, "        free(self->data.%s); break;\n", vnames[i]->c_str);
                } else if (Str_eq_c(vtypes[i], "Str")) {
                    fprintf(f, "        til_Str_delete(self->data.%s, &(til_Bool){1}); break;\n", vnames[i]->c_str);
                } else {
                    fprintf(f, "        til_%s_delete(self->data.%s, &(til_Bool){1}); break;\n", vtypes[i]->c_str, vnames[i]->c_str);
                }
            } else {
                fprintf(f, "        break;\n");
            }
        }
        fprintf(f, "    }\n");
        fprintf(f, "    if (*call_free) free(self);\n");
        fprintf(f, "}\n");

        free(vnames);
        free(vtypes);
    }

    // Emit namespace func/proc methods (to_str, user methods)
    for (int i = 0; i < body->nchildren; i++) {
        Expr *field = body->children[i];
        if (!field->data.decl.is_namespace) continue;
        if (field->children[0]->type != NODE_FUNC_DEF) continue;
        Expr *fdef = field->children[0];
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
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            if (stmt->children[0]->is_ext) continue;
            fprintf(f, "typedef struct til_%s til_%s;\n", stmt->data.decl.name->c_str, stmt->data.decl.name->c_str);
        }
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_ENUM_DEF) {
            Str *ename = stmt->data.decl.name;
            if (cg_enum_has_payloads(stmt->children[0])) {
                // Payload enum: tag enum + struct with union
                Expr *ebody = stmt->children[0]->children[0];
                fprintf(f, "typedef enum {\n");
                int tag = 0;
                for (int j = 0; j < ebody->nchildren; j++) {
                    Expr *v = ebody->children[j];
                    if (v->data.decl.is_namespace) continue;
                    if (tag > 0) fprintf(f, ",\n");
                    fprintf(f, "    til_%s_TAG_%s", ename->c_str, v->data.decl.name->c_str);
                    tag++;
                }
                fprintf(f, "\n} til_%s_tag;\n", ename->c_str);
                fprintf(f, "typedef struct til_%s {\n", ename->c_str);
                fprintf(f, "    til_%s_tag tag;\n", ename->c_str);
                fprintf(f, "    union {\n");
                for (int j = 0; j < ebody->nchildren; j++) {
                    Expr *v = ebody->children[j];
                    if (v->data.decl.is_namespace) continue;
                    if (v->data.decl.explicit_type) {
                        fprintf(f, "        %s %s;\n",
                                type_name_to_c(v->data.decl.explicit_type),
                                v->data.decl.name->c_str);
                    }
                }
                fprintf(f, "    } data;\n");
                fprintf(f, "} til_%s;\n", ename->c_str);
            } else {
                fprintf(f, "typedef long long til_%s;\n", ename->c_str);
            }
        }
    }
    fprintf(f, "\n");

    // Forward-declare all functions (namespace methods + top-level)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && (stmt->children[0]->type == NODE_STRUCT_DEF ||
                                         stmt->children[0]->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *body = stmt->children[0]->children[0];
            for (int j = 0; j < body->nchildren; j++) {
                Expr *field = body->children[j];
                if (!field->data.decl.is_namespace) continue;
                if (field->children[0]->type != NODE_FUNC_DEF) continue;
                Expr *fdef = field->children[0];
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
        } else if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF) {
            Expr *func_def = stmt->children[0];
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
    // Forward-declare enum ext methods (eq, clone, delete + payload methods)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_ENUM_DEF) {
            Str *sname = stmt->data.decl.name;
            fprintf(f, "til_Bool *til_%s_eq(til_%s *, til_%s *);\n", sname->c_str, sname->c_str, sname->c_str);
            fprintf(f, "til_%s *til_%s_clone(til_%s *);\n", sname->c_str, sname->c_str, sname->c_str);
            fprintf(f, "void til_%s_delete(til_%s *, til_Bool *);\n", sname->c_str, sname->c_str);
            if (cg_enum_has_payloads(stmt->children[0])) {
                Expr *ebody = stmt->children[0]->children[0];
                for (int j = 0; j < ebody->nchildren; j++) {
                    Expr *v = ebody->children[j];
                    if (v->data.decl.is_namespace) continue;
                    // is_Variant
                    fprintf(f, "til_Bool *til_%s_is_%s(til_%s *);\n", sname->c_str, v->data.decl.name->c_str, sname->c_str);
                    if (v->data.decl.explicit_type) {
                        // Constructor
                        fprintf(f, "til_%s *til_%s_%s(%s);\n", sname->c_str, sname->c_str,
                                v->data.decl.name->c_str, type_name_to_c(v->data.decl.explicit_type));
                        // get_Variant
                        fprintf(f, "%s til_%s_get_%s(til_%s *);\n",
                                type_name_to_c(v->data.decl.explicit_type),
                                sname->c_str, v->data.decl.name->c_str, sname->c_str);
                    }
                }
            }
        }
    }
    fprintf(f, "\n");

    // First pass: emit struct/enum definitions
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            emit_struct_def(f, stmt->data.decl.name, stmt->children[0]);
            fprintf(f, "\n");
        }
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_ENUM_DEF) {
            emit_enum_def(f, stmt->data.decl.name, stmt->children[0]);
            fprintf(f, "\n");
        }
    }

    fprintf(f, "\n");

    // Second pass: emit func/proc definitions (skip ext_func/ext_proc builtins)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF) {
            FuncType fft2 = stmt->children[0]->data.func_def.func_type;
            if (fft2 == FUNC_EXT_FUNC || fft2 == FUNC_EXT_PROC) continue;
            emit_func_def(f, stmt->data.decl.name, stmt->children[0], mode);
            fprintf(f, "\n");
        }
    }

    // Script mode: wrap top-level statements in main()
    if (is_script) {
        fprintf(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        for (int i = 0; i < program->nchildren; i++) {
            Expr *stmt = program->children[i];
            // Skip func/proc/struct defs (already emitted above)
            if (stmt->type == NODE_DECL &&
                (stmt->children[0]->type == NODE_FUNC_DEF ||
                 stmt->children[0]->type == NODE_STRUCT_DEF ||
                 stmt->children[0]->type == NODE_ENUM_DEF))
                continue;
            emit_stmt(f, stmt, 1);
        }
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    }

    fclose(f);
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

    // Build the cc command — also compile ccore.c (str, i64, etc.)
    char ccore_c_path[256];
    snprintf(ccore_c_path, sizeof(ccore_c_path), "%s/ccore.c", ext_dir);
    int len = snprintf(NULL, 0, "cc -Wall -Wextra -I%s -o %s %s %s %s",
                       ext_dir, bin_path, c_path, ext_c_path, ccore_c_path);
    char *cmd = malloc(len + 1);
    snprintf(cmd, len + 1, "cc -Wall -Wextra -I%s -o %s %s %s %s",
             ext_dir, bin_path, c_path, ext_c_path, ccore_c_path);

    int result = system(cmd);
    free(cmd);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
