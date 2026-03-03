#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c/lexer.h"
#include "c/parser.h"
#include "c/initer.h"
#include "c/typer.h"
#include "c/interpreter.h"
#include "c/ccodegen.h"

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "error: could not open '%s'\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);
    return buf;
}

static void usage(void) {
    printf("Usage: ctil <command> <path>\n\n");
    printf("Commands:\n");
    printf("  interpret  Read and interpret a .til file\n");
    printf("  translate  Generate C source (no compilation)\n");
    printf("  build      Compile a .til file to a binary\n");
    printf("  run        Compile and run a .til file\n");
    printf("  help       Print this message\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage();
        return 1;
    }

    const char *command = argv[1];
    const char *path = NULL;

    if (argc == 2) {
        // Single arg: if it's a known command without a path, handle it
        if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
            usage();
            return 0;
        }
        // Otherwise treat as a path (like til does)
        path = command;
        command = "interpret";
    } else {
        path = argv[2];
    }

    if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
        usage();
        return 0;
    }

    // Resolve paths relative to binary location
    char core_path[256], ext_c_path[256];
    {
        const char *slash = strrchr(argv[0], '/');
        if (slash) {
            int dir_len = (int)(slash - argv[0]);
            snprintf(core_path, sizeof(core_path), "%.*s/../src/core/core.til", dir_len, argv[0]);
            snprintf(ext_c_path, sizeof(ext_c_path), "%.*s/../src/c/ext.c", dir_len, argv[0]);
        } else {
            snprintf(core_path, sizeof(core_path), "../src/core/core.til");
            snprintf(ext_c_path, sizeof(ext_c_path), "../src/c/ext.c");
        }
    }
    char *core_source = read_file(core_path);
    int core_count;
    Token *core_tokens = core_source ? tokenize(core_source, core_path, &core_count) : NULL;
    Expr *core_ast = core_tokens ? parse(core_tokens, core_count, core_path, NULL) : NULL;

    char *source = read_file(path);
    if (!source) return 1;

    int count;
    Token *tokens = tokenize(source, path, &count);

    const char *mode = NULL;
    Expr *ast = parse(tokens, count, path, &mode);

    // Prepend core declarations to program AST
    if (core_ast && core_ast->nchildren > 0) {
        int total = core_ast->nchildren + ast->nchildren;
        Expr **merged = malloc(total * sizeof(Expr *));
        memcpy(merged, core_ast->children, core_ast->nchildren * sizeof(Expr *));
        memcpy(merged + core_ast->nchildren, ast->children, ast->nchildren * sizeof(Expr *));
        free(ast->children);
        ast->children = merged;
        ast->nchildren = total;
    }

    // Init phase: pre-scan declarations for forward references
    TypeScope *scope = tscope_new(NULL);
    init_declarations(ast, scope, path);

    // Type checking and inference
    int type_errors = type_check(ast, path, scope);
    tscope_free(scope);
    if (type_errors > 0) {
        fprintf(stderr, "%d type error(s) found\n", type_errors);
        expr_free(ast);
        free(tokens);
        free(source);
        return 1;
    }

    int result = 0;

    if (strcmp(command, "interpret") == 0) {
        result = interpret(ast, mode, path);
    } else if (strcmp(command, "translate") == 0 || strcmp(command, "build") == 0 || strcmp(command, "run") == 0) {
        // Derive output paths from input: examples/hello_cli.til -> gen/c/hello_cli.c, bin/c/hello_cli
        const char *basename = strrchr(path, '/');
        basename = basename ? basename + 1 : path;
        int name_len = (int)(strlen(basename) - 4); // strip .til
        if (name_len <= 0) name_len = (int)strlen(basename);

        char c_path[256], bin_path[256];
        snprintf(c_path, sizeof(c_path), "gen/c/%.*s.c", name_len, basename);
        snprintf(bin_path, sizeof(bin_path), "bin/c/%.*s", name_len, basename);

        system("mkdir -p gen/c bin/c");

        result = codegen_c(ast, mode, path, c_path);
        if (result == 0 && strcmp(command, "translate") == 0) {
            printf("Generated: %s\n", c_path);
        }
        if (result == 0 && strcmp(command, "translate") != 0) {
            result = compile_c(c_path, bin_path, ext_c_path);
        }
        if (result == 0 && strcmp(command, "run") == 0) {
            result = system(bin_path);
        }
    } else if (strcmp(command, "ast") == 0) {
        printf("mode: %s\n", mode ? mode : "(none)");
        ast_print(ast, 0);
    } else {
        fprintf(stderr, "error: unknown command '%s'\n", command);
        usage();
        result = 1;
    }

    expr_free(ast);
    free(tokens);
    free(source);
    return result;
}
