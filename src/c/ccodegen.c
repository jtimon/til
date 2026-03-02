#include "ccodegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Emitter helpers ---

static void emit_indent(FILE *f, int depth) {
    for (int i = 0; i < depth; i++) fprintf(f, "    ");
}

// Check if an expr is a to_str(x) call, return the inner expr if so
static Expr *unwrap_to_str(Expr *e) {
    if (e->type == NODE_FCALL && e->nchildren >= 2) {
        const char *name = e->children[0]->data.str_val;
        if (strcmp(name, "to_str") == 0) return e->children[1];
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
    case NODE_IDENT:
        fprintf(f, "%s", e->data.str_val);
        break;
    case NODE_FCALL: {
        const char *name = e->children[0]->data.str_val;
        // Built-in: println → one printf per arg, then \n
        if (strcmp(name, "println") == 0 || strcmp(name, "print") == 0) {
            int is_println = strcmp(name, "println") == 0;
            for (int i = 1; i < e->nchildren; i++) {
                if (i > 1) { fprintf(f, ";\n"); emit_indent(f, depth); }
                Expr *arg = e->children[i];
                int last = is_println && i == e->nchildren - 1;
                const char *nl = last ? "\\n" : "";

                // Unwrap to_str(x) — print x directly with %lld
                Expr *inner = unwrap_to_str(arg);
                if (inner) {
                    fprintf(f, "printf(\"%%lld%s\", (long long)", nl);
                    emit_expr(f, inner, depth);
                    fprintf(f, ")");
                } else if (arg->type == NODE_LITERAL_STR) {
                    fprintf(f, "printf(\"%s%s\")", arg->data.str_val, nl);
                } else if (arg->til_type == TIL_TYPE_I64) {
                    fprintf(f, "printf(\"%%lld%s\", (long long)", nl);
                    emit_expr(f, arg, depth);
                    fprintf(f, ")");
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
        } else if (strcmp(name, "add") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " + ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "sub") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " - ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "mul") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " * ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "div") == 0) {
            fprintf(f, "(");
            emit_expr(f, e->children[1], depth);
            fprintf(f, " / ");
            emit_expr(f, e->children[2], depth);
            fprintf(f, ")");
        } else if (strcmp(name, "to_str") == 0) {
            // For I64 args in printf context, just pass the integer
            // and let the printf format handle it. For a proper to_str
            // we'd need snprintf into a buffer, but this works for now.
            emit_expr(f, e->children[1], depth);
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

// --- Statement emission ---

static void emit_stmt(FILE *f, Expr *e, int depth) {
    emit_indent(f, depth);
    switch (e->type) {
    case NODE_DECL:
        if (e->children[0]->type == NODE_FUNC_DEF) {
            fprintf(f, "/* TODO: nested func %s */\n", e->data.decl.name);
        } else {
            fprintf(f, "%s %s = ", til_type_to_c(e->til_type), e->data.decl.name);
            emit_expr(f, e->children[0], depth);
            fprintf(f, ";\n");
        }
        break;
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

static void emit_func_def(FILE *f, const char *name, Expr *func_def, const char *mode) {
    FuncType ft = func_def->data.func_def.func_type;
    Expr *body = func_def->children[0];

    // In cli mode, main proc becomes C main()
    int is_main = mode && strcmp(mode, "cli") == 0 && strcmp(name, "main") == 0;

    if (is_main) {
        fprintf(f, "int main(void) {\n");
        emit_body(f, body, 1);
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    } else {
        // TODO: proper return type and args
        const char *ret = (ft == FUNC_FUNC) ? "/* TODO */ void" : "void";
        fprintf(f, "%s til_%s(void) {\n", ret, name);
        emit_body(f, body, 1);
        fprintf(f, "}\n");
    }
}

int codegen_c(Expr *program, const char *mode, const char *path, const char *c_output_path) {
    (void)path;
    FILE *f = fopen(c_output_path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", c_output_path);
        return 1;
    }

    fprintf(f, "#include <stdio.h>\n\n");

    int is_script = mode && strcmp(mode, "script") == 0;

    // First pass: emit func/proc definitions
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF) {
            emit_func_def(f, stmt->data.decl.name, stmt->children[0], mode);
            fprintf(f, "\n");
        }
    }

    // Script mode: wrap top-level statements in main()
    if (is_script) {
        fprintf(f, "int main(void) {\n");
        for (int i = 0; i < program->nchildren; i++) {
            Expr *stmt = program->children[i];
            // Skip func/proc defs (already emitted above)
            if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF)
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
