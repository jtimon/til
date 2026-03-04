#include "ccodegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Expr *codegen_program; // set during codegen for struct lookups


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
            fprintf(f, "%s%s", obj->type == NODE_FIELD_ACCESS ? "." : "->", fname->c_str);
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
    if (t == TIL_TYPE_STRUCT && struct_name) {
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
        // Struct/Str field: take address directly (fields are embedded values)
        fprintf(f, "&");
        emit_expr(f, e, depth);
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
        } else if (e->children[0]->type == NODE_STRUCT_DEF) {
            fprintf(f, "/* struct %s defined above */\n", e->data.decl.name->c_str);
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
                    for (int i = 1; i < rhs->nchildren; i++) {
                        if (i > 1) fprintf(f, ", ");
                        emit_deref(f, rhs->children[i], depth);
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
    case NODE_ASSIGN:
        if (e->children[0]->type == NODE_LITERAL_STR) {
            // Str_new returns Str * — assign pointer directly
            fprintf(f, "%s = ", e->data.str_val->c_str);
            emit_expr(f, e->children[0], depth);
        } else {
            fprintf(f, "*%s = ", e->data.str_val->c_str);
            emit_deref(f, e->children[0], depth);
        }
        fprintf(f, ";\n");
        break;
    case NODE_FIELD_ASSIGN: {
        Expr *obj = e->children[0];
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "til_%s_%s = ", obj->struct_name->c_str, fname->c_str);
        } else {
            emit_expr(f, obj, depth);
            fprintf(f, "%s%s = ", obj->type == NODE_FIELD_ACCESS ? "." : "->", fname->c_str);
        }
        emit_deref(f, e->children[1], depth);
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
                    for (int i = 1; i < rv->nchildren; i++) {
                        if (i > 1) fprintf(f, ", ");
                        emit_deref(f, rv->children[i], depth);
                    }
                    fprintf(f, "};");
                }
                fprintf(f, " return _r; }\n");
            } else if (rv->type == NODE_LITERAL_NUM || rv->type == NODE_LITERAL_BOOL) {
                const char *ctype = c_type_name(rv->til_type, rv->struct_name);
                fprintf(f, "{ %s *_r = malloc(sizeof(%s)); *_r = ", ctype, ctype);
                emit_expr(f, rv, depth);
                fprintf(f, "; return _r; }\n");
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
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            Str *sname = stmt->data.decl.name;
            Expr *body = stmt->children[0]->children[0];
            for (int j = 0; j < body->nchildren; j++) {
                Expr *field = body->children[j];
                if (!field->data.decl.is_namespace) continue;
                if (field->children[0]->type == NODE_FUNC_DEF) continue;
                emit_indent(f, depth);
                fprintf(f, "til_%s_%s = ", sname->c_str, field->data.decl.name->c_str);
                emit_deref(f, field->children[0], depth);
                fprintf(f, ";\n");
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
            if (field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
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

int codegen_c(Expr *program, Str *mode, const char *path, const char *c_output_path) {
    (void)path;
    codegen_program = program;
    FILE *f = fopen(c_output_path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", c_output_path);
        return 1;
    }

    fprintf(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include \"str.h\"\n#include \"ext.h\"\n\n");

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
    }
    fprintf(f, "\n");

    // Forward-declare all functions (namespace methods + top-level)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
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
    fprintf(f, "\n");

    // First pass: emit struct definitions (primitives skip body/constructor, keep namespace methods)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            emit_struct_def(f, stmt->data.decl.name, stmt->children[0]);
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
                 stmt->children[0]->type == NODE_STRUCT_DEF))
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

    // Build the cc command — also compile str.c
    char str_c_path[256];
    snprintf(str_c_path, sizeof(str_c_path), "%s/str.c", ext_dir);
    int len = snprintf(NULL, 0, "cc -Wall -Wextra -I%s -o %s %s %s %s",
                       ext_dir, bin_path, c_path, ext_c_path, str_c_path);
    char *cmd = malloc(len + 1);
    snprintf(cmd, len + 1, "cc -Wall -Wextra -I%s -o %s %s %s %s",
             ext_dir, bin_path, c_path, ext_c_path, str_c_path);

    int result = system(cmd);
    free(cmd);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
