#include "ccodegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Expr *codegen_program; // set during codegen for struct lookups

// Find a struct definition by name in the program
static Expr *find_struct_def(const char *name) {
    for (int i = 0; i < codegen_program->nchildren; i++) {
        Expr *stmt = codegen_program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF &&
            strcmp(stmt->data.decl.name, name) == 0) {
            return stmt->children[0];
        }
    }
    return NULL;
}

// --- Emitter helpers ---

static void emit_indent(FILE *f, int depth) {
    for (int i = 0; i < depth; i++) fprintf(f, "    ");
}

// Check if a field is a namespace field in a struct
static int is_ns_field(const char *struct_name, const char *field_name) {
    Expr *sdef = find_struct_def(struct_name);
    if (!sdef) return 0;
    Expr *body = sdef->children[0];
    for (int i = 0; i < body->nchildren; i++) {
        Expr *f = body->children[i];
        if (strcmp(f->data.decl.name, field_name) == 0)
            return f->data.decl.is_namespace;
    }
    return 0;
}

// Check if an expr is a to_str call (builtin or namespace method), return the inner expr if so
static Expr *unwrap_to_str(Expr *e) {
    if (e->type == NODE_FCALL && e->nchildren >= 2) {
        if (e->children[0]->type == NODE_IDENT) {
            const char *name = e->children[0]->data.str_val;
            if (strcmp(name, "i64_to_str") == 0 || strcmp(name, "bool_to_str") == 0)
                return e->children[1];
        }
        // I64.to_str(x) or Bool.to_str(x)
        if (e->children[0]->type == NODE_FIELD_ACCESS &&
            strcmp(e->children[0]->data.str_val, "to_str") == 0) {
            Expr *obj = e->children[0]->children[0];
            if (obj->struct_name &&
                (strcmp(obj->struct_name, "I64") == 0 || strcmp(obj->struct_name, "Bool") == 0))
                return e->children[1];
        }
    }
    return NULL;
}

// --- Forward declarations ---

static void emit_expr(FILE *f, Expr *e, int depth);
static void emit_stmt(FILE *f, Expr *e, int depth);
static void emit_body(FILE *f, Expr *body, int depth);

// --- Expression emission ---

static void emit_expr(FILE *f, Expr *e, int depth) {
    (void)depth;
    switch (e->type) {
    case NODE_LITERAL_STR:
        fprintf(f, "\"%s\"", e->data.str_val);
        break;
    case NODE_LITERAL_NUM:
        fprintf(f, "%s", e->data.str_val);
        break;
    case NODE_LITERAL_BOOL:
        fprintf(f, "%d", strcmp(e->data.str_val, "true") == 0 ? 1 : 0);
        break;
    case NODE_IDENT:
        fprintf(f, "%s", e->data.str_val);
        break;
    case NODE_FCALL: {
        // Namespace method call: Struct.method(args)
        if (e->children[0]->type == NODE_FIELD_ACCESS) {
            const char *sname = e->children[0]->children[0]->struct_name;
            const char *mname = e->children[0]->data.str_val;
            fprintf(f, "til_%s_%s(", sname, mname);
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_expr(f, e->children[i], depth);
            }
            fprintf(f, ")");
            break;
        }
        const char *name = e->children[0]->data.str_val;
        // Built-in: println → one printf per arg, then \n
        if (strcmp(name, "println") == 0 || strcmp(name, "print") == 0) {
            int is_println = strcmp(name, "println") == 0;
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) { fprintf(f, ";\n"); emit_indent(f, depth); }
                Expr *arg = e->children[i];
                int last = is_println && i == e->nchildren - 1;
                const char *nl = last ? "\\n" : "";

                // Unwrap to_str(x) — print x directly
                Expr *inner = unwrap_to_str(arg);
                if (inner && inner->til_type == TIL_TYPE_BOOL) {
                    fprintf(f, "printf(\"%%s%s\", ", nl);
                    emit_expr(f, inner, depth);
                    fprintf(f, " ? \"true\" : \"false\")");
                } else if (inner) {
                    fprintf(f, "printf(\"%%lld%s\", (long long)", nl);
                    emit_expr(f, inner, depth);
                    fprintf(f, ")");
                } else if (arg->type == NODE_LITERAL_STR) {
                    fprintf(f, "printf(\"%s%s\")", arg->data.str_val, nl);
                } else if (arg->til_type == TIL_TYPE_I64) {
                    fprintf(f, "printf(\"%%lld%s\", (long long)", nl);
                    emit_expr(f, arg, depth);
                    fprintf(f, ")");
                } else if (arg->til_type == TIL_TYPE_BOOL) {
                    fprintf(f, "printf(\"%%s%s\", ", nl);
                    emit_expr(f, arg, depth);
                    fprintf(f, " ? \"true\" : \"false\")");
                } else {
                    fprintf(f, "printf(\"%%s%s\", ", nl);
                    emit_expr(f, arg, depth);
                    fprintf(f, ")");
                }
            }
            // println() with no args: just a newline
            if (is_println && e->nchildren <= 1) {
                fprintf(f, "printf(\"\\n\")");
            }
        } else if (strcmp(name, "i64_add") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " + ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_sub") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " - ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_mul") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " * ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_div") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " / ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_mod") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " %% ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_eq") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " == ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_lt") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " < ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_gt") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " > ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_and") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " & ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_or") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " | ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_xor") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " ^ ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "bool_and") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " && ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "bool_or") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " || ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "str_eq") == 0) {
            fprintf(f, "(strcmp(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, ", ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ") == 0)");
        } else if (strcmp(name, "format") == 0) {
            fprintf(f, "til_format(%d", e->nchildren - 1);
            for (int i = 1; i < e->nchildren; i++) {
                fprintf(f, ", ");
                emit_expr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        } else if (strcmp(name, "exit") == 0) {
            fprintf(f, "exit(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "bool_not") == 0) {
            fprintf(f, "(!");
            emit_expr(f, e->children[1], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "i64_to_str") == 0) {
            fprintf(f, "til_i64_to_str(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "bool_to_str") == 0) {
            fprintf(f, "til_bool_to_str(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, ")");
        } else if (e->struct_name) {
            // Struct instantiation
            if (e->nchildren > 1) {
                // Desugared args: emit compound literal (instance fields only)
                Expr *sd = find_struct_def(e->struct_name);
                Expr *body = sd->children[0];
                fprintf(f, "(til_%s){", e->struct_name);
                int first = 1;
                int arg_idx = 1;
                for (int i = 0; i < body->nchildren; i++) {
                    if (body->children[i]->data.decl.is_namespace) continue;
                    if (!first) fprintf(f, ", ");
                    first = 0;
                    fprintf(f, ".%s = ", body->children[i]->data.decl.name);
                    emit_expr(f, e->children[arg_idx++], depth);
                }
                fprintf(f, "}");
            } else {
                fprintf(f, "til_%s_default()", name);
            }
        } else {
            // User-defined function call
            fprintf(f, "til_%s(", name);
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_expr(f, e->children[i], depth);
            }
            fprintf(f, ")");
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        // Check if this is a namespace field access
        Expr *obj = e->children[0];
        const char *fname = e->data.str_val;
        const char *sname = obj->struct_name;
        if (sname && is_ns_field(sname, fname)) {
            fprintf(f, "til_%s_%s", sname, fname);
        } else {
            emit_expr(f, obj, depth);
            fprintf(f, ".%s", fname);
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
    case TIL_TYPE_I64:  return "long long";
    case TIL_TYPE_STR:  return "const char *";
    case TIL_TYPE_BOOL: return "int";
    case TIL_TYPE_NONE: return "void";
    default:            return "long long"; // fallback
    }
}

// Convert a type name string to C type string (handles struct types)
static const char *type_name_to_c(const char *name) {
    if (strcmp(name, "I64") == 0)  return "long long";
    if (strcmp(name, "Str") == 0)  return "const char *";
    if (strcmp(name, "Bool") == 0) return "int";
    // User-defined struct type
    static char buf[128];
    snprintf(buf, sizeof(buf), "til_%s", name);
    return buf;
}

// --- Statement emission ---

static void emit_stmt(FILE *f, Expr *e, int depth) {
    emit_indent(f, depth);
    switch (e->type) {
    case NODE_DECL:
        if (e->children[0]->type == NODE_FUNC_DEF) {
            fprintf(f, "/* TODO: nested func %s */\n", e->data.decl.name);
        } else if (e->children[0]->type == NODE_STRUCT_DEF) {
            fprintf(f, "/* struct %s defined above */\n", e->data.decl.name);
        } else if (e->til_type == TIL_TYPE_STRUCT && e->children[0]->struct_name) {
            fprintf(f, "til_%s %s = ", e->children[0]->struct_name, e->data.decl.name);
            emit_expr(f, e->children[0], depth);
            fprintf(f, ";\n");
        } else {
            fprintf(f, "%s %s = ", til_type_to_c(e->til_type), e->data.decl.name);
            emit_expr(f, e->children[0], depth);
            fprintf(f, ";\n");
        }
        break;
    case NODE_ASSIGN:
        fprintf(f, "%s = ", e->data.str_val);
        emit_expr(f, e->children[0], depth);
        fprintf(f, ";\n");
        break;
    case NODE_FIELD_ASSIGN: {
        Expr *obj = e->children[0];
        const char *fname = e->data.str_val;
        const char *sname = obj->struct_name;
        if (sname && is_ns_field(sname, fname)) {
            fprintf(f, "til_%s_%s = ", sname, fname);
        } else {
            emit_expr(f, obj, depth);
            fprintf(f, ".%s = ", fname);
        }
        emit_expr(f, e->children[1], depth);
        fprintf(f, ";\n");
        break;
    }
    case NODE_FCALL:
        emit_expr(f, e, depth);
        fprintf(f, ";\n");
        break;
    case NODE_RETURN:
        fprintf(f, "return");
        if (e->nchildren > 0) {
            fprintf(f, " ");
            emit_expr(f, e->children[0], depth);
        }
        fprintf(f, ";\n");
        break;
    case NODE_BODY:
        fprintf(f, "{\n");
        emit_body(f, e, depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
        break;
    case NODE_IF:
        fprintf(f, "if (");
        emit_expr(f, e->children[0], depth);
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
        emit_expr(f, e->children[0], depth);
        fprintf(f, ") {\n");
        emit_body(f, e->children[1], depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
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
            const char *sname = stmt->data.decl.name;
            Expr *body = stmt->children[0]->children[0];
            for (int j = 0; j < body->nchildren; j++) {
                Expr *field = body->children[j];
                if (!field->data.decl.is_namespace) continue;
                if (field->children[0]->type == NODE_FUNC_DEF) continue;
                emit_indent(f, depth);
                fprintf(f, "til_%s_%s = ", sname, field->data.decl.name);
                emit_expr(f, field->children[0], depth);
                fprintf(f, ";\n");
            }
        }
    }
}

static void emit_func_def(FILE *f, const char *name, Expr *func_def, const char *mode) {
    (void)func_def->data.func_def.func_type;
    Expr *body = func_def->children[0];

    // In cli mode, main proc becomes C main()
    int is_main = mode && strcmp(mode, "cli") == 0 && strcmp(name, "main") == 0;

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
        fprintf(f, "%s til_%s(", ret, name);
        int np = func_def->data.func_def.nparam;
        if (np == 0) {
            fprintf(f, "void");
        } else {
            for (int i = 0; i < np; i++) {
                if (i > 0) fprintf(f, ", ");
                fprintf(f, "%s %s", type_name_to_c(func_def->data.func_def.param_types[i]),
                        func_def->data.func_def.param_names[i]);
            }
        }
        fprintf(f, ") {\n");
        emit_body(f, body, 1);
        fprintf(f, "}\n");
    }
}

static void emit_struct_def(FILE *f, const char *name, Expr *struct_def) {
    Expr *body = struct_def->children[0];
    // Emit typedef struct (skip namespace fields)
    fprintf(f, "typedef struct til_%s {\n", name);
    for (int i = 0; i < body->nchildren; i++) {
        Expr *field = body->children[i];
        if (field->data.decl.is_namespace) continue;
        if (field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
            fprintf(f, "    til_%s %s;\n", field->children[0]->struct_name, field->data.decl.name);
        } else {
            fprintf(f, "    %s %s;\n", til_type_to_c(field->til_type), field->data.decl.name);
        }
    }
    fprintf(f, "} til_%s;\n\n", name);
    // Emit namespace fields as globals (skip func defs — emitted separately)
    for (int i = 0; i < body->nchildren; i++) {
        Expr *field = body->children[i];
        if (!field->data.decl.is_namespace) continue;
        if (field->children[0]->type == NODE_FUNC_DEF) continue;
        if (field->til_type == TIL_TYPE_STRUCT && field->children[0]->struct_name) {
            fprintf(f, "til_%s til_%s_%s;\n", field->children[0]->struct_name, name, field->data.decl.name);
        } else {
            fprintf(f, "%s til_%s_%s;\n", til_type_to_c(field->til_type), name, field->data.decl.name);
        }
    }
    // Emit namespace functions as C functions
    for (int i = 0; i < body->nchildren; i++) {
        Expr *field = body->children[i];
        if (!field->data.decl.is_namespace) continue;
        if (field->children[0]->type != NODE_FUNC_DEF) continue;
        Expr *fdef = field->children[0];
        char full_name[256];
        snprintf(full_name, sizeof(full_name), "%s_%s", name, field->data.decl.name);
        emit_func_def(f, full_name, fdef, NULL);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    // Emit default constructor (instance fields only)
    fprintf(f, "til_%s til_%s_default(void) {\n", name, name);
    fprintf(f, "    return (til_%s){", name);
    int first = 1;
    for (int i = 0; i < body->nchildren; i++) {
        if (body->children[i]->data.decl.is_namespace) continue;
        if (!first) fprintf(f, ", ");
        first = 0;
        fprintf(f, ".%s = ", body->children[i]->data.decl.name);
        emit_expr(f, body->children[i]->children[0], 0);
    }
    fprintf(f, "};\n");
    fprintf(f, "}\n");
}

int codegen_c(Expr *program, const char *mode, const char *path, const char *c_output_path) {
    (void)path;
    codegen_program = program;
    FILE *f = fopen(c_output_path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", c_output_path);
        return 1;
    }

    fprintf(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdarg.h>\n\n");
    fprintf(f, "static const char *til_format(int n, ...) {\n");
    fprintf(f, "    va_list ap; va_start(ap, n);\n");
    fprintf(f, "    int total = 0;\n");
    fprintf(f, "    const char *strs[64];\n");
    fprintf(f, "    for (int i = 0; i < n; i++) { strs[i] = va_arg(ap, const char *); total += strlen(strs[i]); }\n");
    fprintf(f, "    va_end(ap);\n");
    fprintf(f, "    char *r = malloc(total + 1); int off = 0;\n");
    fprintf(f, "    for (int i = 0; i < n; i++) { int l = strlen(strs[i]); memcpy(r + off, strs[i], l); off += l; }\n");
    fprintf(f, "    r[off] = '\\0'; return r;\n");
    fprintf(f, "}\n\n");
    fprintf(f, "static const char *til_i64_to_str(long long v) {\n");
    fprintf(f, "    char *buf = malloc(32); snprintf(buf, 32, \"%%lld\", v); return buf;\n");
    fprintf(f, "}\n\n");
    fprintf(f, "static const char *til_bool_to_str(int v) {\n");
    fprintf(f, "    return v ? \"true\" : \"false\";\n");
    fprintf(f, "}\n\n");

    int is_script = mode && strcmp(mode, "script") == 0;

    // Forward-declare all structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            fprintf(f, "typedef struct til_%s til_%s;\n", stmt->data.decl.name, stmt->data.decl.name);
        }
    }
    fprintf(f, "\n");

    // First pass: emit struct definitions
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            emit_struct_def(f, stmt->data.decl.name, stmt->children[0]);
            fprintf(f, "\n");
        }
    }

    // Forward-declare all functions (skip ext_func/ext_proc builtins)
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF) {
            Expr *func_def = stmt->children[0];
            FuncType fft = func_def->data.func_def.func_type;
            if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
            const char *name = stmt->data.decl.name;
            int is_main = mode && strcmp(mode, "cli") == 0 && strcmp(name, "main") == 0;
            if (is_main) continue;
            const char *ret = "void";
            if (func_def->data.func_def.return_type) {
                ret = type_name_to_c(func_def->data.func_def.return_type);
            }
            fprintf(f, "%s til_%s(", ret, name);
            int np = func_def->data.func_def.nparam;
            if (np == 0) {
                fprintf(f, "void");
            } else {
                for (int j = 0; j < np; j++) {
                    if (j > 0) fprintf(f, ", ");
                    fprintf(f, "%s %s", type_name_to_c(func_def->data.func_def.param_types[j]),
                            func_def->data.func_def.param_names[j]);
                }
            }
            fprintf(f, ");\n");
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

int compile_c(const char *c_path, const char *bin_path) {
    // Build the cc command
    int len = snprintf(NULL, 0, "cc -Wall -Wextra -o %s %s", bin_path, c_path);
    char *cmd = malloc(len + 1);
    snprintf(cmd, len + 1, "cc -Wall -Wextra -o %s %s", bin_path, c_path);

    int result = system(cmd);
    free(cmd);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
