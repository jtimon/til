#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "c/lexer.h"
#include "c/parser.h"
#include "c/initer.h"
#include "c/typer.h"
#include "c/interpreter.h"
#include "c/ccodegen.h"
#include "c/precomp.h"
#include "c/scavenger.h"

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
            I32 dir_len = (int)(slash - argv[0]);
            snprintf(core_path, sizeof(core_path), "%.*s/../src/core/core.til", dir_len, argv[0]);
            snprintf(ext_c_path, sizeof(ext_c_path), "%.*s/../src/c/ext.c", dir_len, argv[0]);
        } else {
            snprintf(core_path, sizeof(core_path), "../src/core/core.til");
            snprintf(ext_c_path, sizeof(ext_c_path), "../src/c/ext.c");
        }
    }
    char *core_source = read_file(core_path);
    I32 core_count;
    Token *core_tokens = core_source ? tokenize(core_source, core_path, &core_count) : NULL;
    Expr *core_ast = core_tokens ? parse(core_tokens, core_count, core_path, NULL) : NULL;

    char *source = read_file(path);
    if (!source) return 1;

    I32 count;
    Token *tokens = tokenize(source, path, &count);

    Str *mode = NULL;
    Expr *ast = parse(tokens, count, path, &mode);

    // Prepend core declarations to program AST
    if (core_ast && core_ast->children.count > 0) {
        Vec merged = Vec_new(sizeof(Expr *));
        for (I32 i = 0; i < core_ast->children.count; i++) {
            Expr *ch = expr_child(core_ast, i);
            ch->is_core = true;
            if (ch->children.count > 0) expr_child(ch, 0)->is_core = true;
            Vec_push(&merged, &ch);
        }
        for (I32 i = 0; i < ast->children.count; i++) {
            Expr *ch = expr_child(ast, i);
            Vec_push(&merged, &ch);
        }
        Vec_delete(&ast->children);
        ast->children = merged;
    }

    // Extract link("lib") directives from AST (before type checking)
    char link_flags[512] = "";
    I32 link_pos = 0;
    {
        Vec kept = Vec_new(sizeof(Expr *));
        for (I32 i = 0; i < ast->children.count; i++) {
            Expr *stmt = expr_child(ast, i);
            if (stmt->type == NODE_FCALL && stmt->children.count == 2 &&
                expr_child(stmt, 0)->type == NODE_IDENT &&
                Str_eq_c(expr_child(stmt, 0)->data.str_val, "link") &&
                expr_child(stmt, 1)->type == NODE_LITERAL_STR) {
                Str *lib = expr_child(stmt, 1)->data.str_val;
                link_pos += snprintf(link_flags + link_pos, sizeof(link_flags) - link_pos,
                                     " -l%.*s", (int)lib->cap, lib->c_str);
            } else {
                Vec_push(&kept, &stmt);
            }
        }
        Vec_delete(&ast->children);
        ast->children = kept;
    }

    // Init phase: pre-scan declarations for forward references
    TypeScope *scope = tscope_new(NULL);
    init_declarations(ast, scope);

    // Type checking and inference
    I32 type_errors = type_check(ast, scope);
    tscope_free(scope);
    if (type_errors > 0) {
        fprintf(stderr, "%d type error(s) found\n", type_errors);
        expr_free(ast);
        free(tokens);
        free(source);
        return 1;
    }

    precomp(ast);
    scavenge(ast, mode);

    I32 result = 0;

    // Check for user FFI .c file (same name as .til but with .c extension)
    char user_c_path[256];
    const char *user_c = NULL;
    {
        I32 plen = (int)strlen(path);
        if (plen > 4 && strcmp(path + plen - 4, ".til") == 0) {
            snprintf(user_c_path, sizeof(user_c_path), "%.*s.c", plen - 4, path);
            FILE *uf = fopen(user_c_path, "r");
            if (uf) { fclose(uf); user_c = user_c_path; }
        }
    }

    // Append -l flags from CLI args (argv[3..])
    char *filtered_argv[argc];
    I32 user_argc = 0;
    for (I32 i = 3; i < argc; i++) {
        if (strncmp(argv[i], "-l", 2) == 0) {
            const char *lib = argv[i] + 2;
            if (*lib == '\0' && i + 1 < argc) { lib = argv[++i]; }
            link_pos += snprintf(link_flags + link_pos, sizeof(link_flags) - link_pos,
                                 " -l%s", lib);
        } else {
            filtered_argv[user_argc++] = argv[i];
        }
    }
    char **user_argv = user_argc > 0 ? filtered_argv : NULL;
    const char *lflags = link_flags[0] ? link_flags : NULL;

    if (strcmp(command, "interpret") == 0) {
        result = interpret(ast, mode, path, user_c, ext_c_path, lflags, user_argc, user_argv);
    } else if (strcmp(command, "translate") == 0 || strcmp(command, "build") == 0 || strcmp(command, "run") == 0) {
        // Derive output paths from input: examples/hello_cli.til -> gen/c/hello_cli.c, bin/c/hello_cli
        const char *basename = strrchr(path, '/');
        basename = basename ? basename + 1 : path;
        I32 name_len = (int)(strlen(basename) - 4); // strip .til
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
            result = compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
        }
        if (result == 0 && strcmp(command, "run") == 0) {
            // Build command with user args appended
            I32 cmdlen = (int)strlen(bin_path);
            for (I32 i = 0; i < user_argc; i++)
                cmdlen += 1 + (I32)strlen(user_argv[i]) + 2; // space + quotes
            char *cmd = malloc(cmdlen + 1);
            I32 pos = snprintf(cmd, cmdlen + 1, "%s", bin_path);
            for (I32 i = 0; i < user_argc; i++)
                pos += snprintf(cmd + pos, cmdlen + 1 - pos, " '%s'", user_argv[i]);
            int status = system(cmd);
            free(cmd);
            if (WIFEXITED(status))
                result = WEXITSTATUS(status);
            else
                result = 1;
        }
    } else if (strcmp(command, "ast") == 0) {
        printf("mode: %s\n", mode ? mode->c_str : "(none)");
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
