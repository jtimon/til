#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include "c/lexer.h"
#include "c/parser.h"
#include "c/initer.h"
#include "c/typer.h"
#include "c/interpreter.h"
#include "c/builder.h"
#include "c/precomp.h"
#include "c/scavenger.h"
#include "c/modes.h"
#include "c/map.h"

static const Mode *mode_resolve(const char *name) {
    if (strcmp(name, "script") == 0) return &MODE_SCRIPT;
    if (strcmp(name, "cli") == 0)    return &MODE_CLI;
    if (strcmp(name, "gui") == 0)    return &MODE_GUI;
    if (strcmp(name, "test") == 0)   return &MODE_TEST;
    if (strcmp(name, "pure") == 0)   return &MODE_PURE;
    if (strcmp(name, "pura") == 0)   return &MODE_PURA;
    if (strcmp(name, "lib") == 0)    return &MODE_LIB;
    if (strcmp(name, "liba") == 0)   return &MODE_LIBA;
    return NULL;
}

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

// Extract import("path") calls from AST body, returning paths as Vec of Str*.
// Matching nodes are removed from the body.
static Vec extract_imports(Expr *body) {
    Vec paths = Vec_new(sizeof(Str *));
    Vec kept = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type == NODE_FCALL && stmt->children.count == 2 &&
            expr_child(stmt, 0)->type == NODE_IDENT &&
            Str_eq_c(expr_child(stmt, 0)->data.str_val, "import") &&
            expr_child(stmt, 1)->type == NODE_LITERAL_STR) {
            Str *path = expr_child(stmt, 1)->data.str_val;
            Vec_push(&paths, &path);
        } else {
            Vec_push(&kept, &stmt);
        }
    }
    Vec_delete(&body->children);
    body->children = kept;
    return paths;
}

// Recursively resolve imports. Returns 0 on success, 1 on error.
// - import_paths: Vec of Str* (paths extracted from AST)
// - base_dir: directory of the importing file (for relative resolution)
// - resolved: Set of Str* (absolute paths already imported, for dedup)
// - stack: Vec of Str* (current import chain, for cycle detection)
// - merged: Vec of Expr* (accumulated declarations, output)
// - lib_dir: standard library directory (fallback search path)
static int resolve_imports(Vec *import_paths, const char *base_dir,
                           Set *resolved, Vec *stack,
                           Vec *merged,
                           const char *lib_dir) {
    for (U32 i = 0; i < import_paths->count; i++) {
        Str *import_path = *(Str **)Vec_get(import_paths, i);

        // Try relative to importing file's directory, then lib_dir
        char try_path[PATH_MAX];
        snprintf(try_path, sizeof(try_path), "%s/%s", base_dir, import_path->c_str);
        char *abs = realpath(try_path, NULL);
        if (!abs && lib_dir) {
            snprintf(try_path, sizeof(try_path), "%s/%s", lib_dir, import_path->c_str);
            abs = realpath(try_path, NULL);
        }
        if (!abs) {
            fprintf(stderr, "error: could not find import '%s' (from %s/)\n",
                    import_path->c_str, base_dir);
            return 1;
        }

        Str *abs_str = Str_new(abs);

        // Cycle detection: check if this file is on the current import stack
        for (U32 j = 0; j < stack->count; j++) {
            Str *s = *(Str **)Vec_get(stack, j);
            if (Str_eq(s, abs_str)) {
                fprintf(stderr, "error: circular import: ");
                for (U32 k = j; k < stack->count; k++) {
                    Str *sk = *(Str **)Vec_get(stack, k);
                    fprintf(stderr, "%s -> ", sk->c_str);
                }
                fprintf(stderr, "%s\n", abs_str->c_str);
                free(abs);
                return 1;
            }
        }

        // Dedup: skip if already resolved
        if (Set_has(resolved, &abs_str)) {
            free(abs);
            continue;
        }
        Set_add(resolved, &abs_str);
        Vec_push(stack, &abs_str);

        // Load, lex, parse the imported file
        char *source = read_file(abs);
        if (!source) { free(abs); return 1; }

        U32 tok_count;
        Token *toks = tokenize(source, abs, &tok_count);

        Str *sub_mode = NULL;
        Expr *sub_ast = parse(toks, tok_count, abs, &sub_mode);
        Vec sub_imports = extract_imports(sub_ast);

        if (sub_mode) {
            const Mode *sm = mode_resolve(sub_mode->c_str);
            if (!sm || !(sm == &MODE_LIB || sm == &MODE_LIBA || sm == &MODE_PURE || sm == &MODE_PURA)) {
                fprintf(stderr, "error: imported file '%s' cannot use mode '%s'\n", abs, sub_mode->c_str);
                free(abs);
                return 1;
            }
        }

        // Get imported file's directory for recursive resolution
        char sub_dir[PATH_MAX];
        strncpy(sub_dir, abs, sizeof(sub_dir));
        sub_dir[sizeof(sub_dir) - 1] = '\0';
        char *last_slash = strrchr(sub_dir, '/');
        if (last_slash) *last_slash = '\0';

        // Recurse for sub-imports
        if (sub_imports.count > 0) {
            int err = resolve_imports(&sub_imports, sub_dir, resolved, stack,
                                      merged, lib_dir);
            if (err) { free(abs); return err; }
        }
        Vec_delete(&sub_imports);

        // Append imported file's declarations
        for (U32 j = 0; j < sub_ast->children.count; j++) {
            Expr *ch = expr_child(sub_ast, j);
            Vec_push(merged, &ch);
        }

        // Pop from stack
        stack->count--;

        free(abs);
    }
    return 0;
}

static void usage(void) {
    printf("Usage: ctil <command> <path>\n\n");
    printf("Commands:\n");
    printf("  interpret  Read and interpret a .til file\n");
    printf("  translate  Generate C source (no compilation)\n");
    printf("  build      Compile a .til file to a binary\n");
    printf("  run        Compile and run a .til file\n");
    printf("  test       Run test functions in a .til file\n");
    printf("  help       Print this message\n");
}

static void mark_core(Expr *e) {
    e->is_core = true;
    for (U32 i = 0; i < e->children.count; i++)
        mark_core(expr_child(e, i));
}

// High-level prepare function for til.til self-hosting.
// Loads core.til, resolves imports, merges ASTs, strips link() directives.
// Returns merged AST ready for type checking, or NULL on error.
Expr *til_prepare(const char *path, const char *bin_dir) {
    // Load core.til
    char core_path[256];
    snprintf(core_path, sizeof(core_path), "%s/src/core/core.til", bin_dir);
    char *core_source = read_file(core_path);
    if (!core_source) return NULL;
    U32 core_count;
    Token *core_tokens = tokenize(core_source, core_path, &core_count);
    Expr *core_ast = parse(core_tokens, core_count, core_path, NULL);

    // Resolve core imports
    Vec core_import_decls = Vec_new(sizeof(Expr *));
    Vec core_imports = extract_imports(core_ast);
    if (core_imports.count > 0) {
        char core_dir[PATH_MAX];
        snprintf(core_dir, sizeof(core_dir), "%s/src/core", bin_dir);
        Set resolved = Set_new(sizeof(Str *), str_ptr_cmp);
        Vec resolve_stack = Vec_new(sizeof(Str *));
        int err = resolve_imports(&core_imports, core_dir, &resolved, &resolve_stack,
                                  &core_import_decls, NULL);
        Set_delete(&resolved);
        Vec_delete(&resolve_stack);
        if (err) return NULL;
    }
    Vec_delete(&core_imports);

    // Load user file
    char *source = read_file(path);
    if (!source) return NULL;
    U32 count;
    Token *tokens = tokenize(source, path, &count);
    Expr *ast = parse(tokens, count, path, NULL);

    // Merge: core + core imports + user
    Vec merged = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < core_ast->children.count; i++) {
        Expr *ch = expr_child(core_ast, i);
        mark_core(ch);
        Vec_push(&merged, &ch);
    }
    for (U32 i = 0; i < core_import_decls.count; i++) {
        Expr *ch = *(Expr **)Vec_get(&core_import_decls, i);
        mark_core(ch);
        Vec_push(&merged, &ch);
    }
    for (U32 i = 0; i < ast->children.count; i++) {
        Expr *ch = expr_child(ast, i);
        Vec_push(&merged, &ch);
    }
    Vec_delete(&ast->children);
    ast->children = merged;

    // Strip link() and link_c() directives
    Vec kept = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < ast->children.count; i++) {
        Expr *stmt = expr_child(ast, i);
        if (stmt->type == NODE_FCALL && stmt->children.count == 2 &&
            expr_child(stmt, 0)->type == NODE_IDENT &&
            expr_child(stmt, 1)->type == NODE_LITERAL_STR) {
            Str *fn = expr_child(stmt, 0)->data.str_val;
            if (Str_eq_c(fn, "link") || Str_eq_c(fn, "link_c")) continue;
        }
        Vec_push(&kept, &stmt);
    }
    Vec_delete(&ast->children);
    ast->children = kept;

    return ast;
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
    char core_path[256], ext_c_path[256], bin_dir[256];
    {
        const char *slash = strrchr(argv[0], '/');
        if (slash) {
            I32 dir_len = (int)(slash - argv[0]);
            snprintf(bin_dir, sizeof(bin_dir), "%.*s/..", dir_len, argv[0]);
            snprintf(core_path, sizeof(core_path), "%s/src/core/core.til", bin_dir);
            snprintf(ext_c_path, sizeof(ext_c_path), "%s/src/c/ext.c", bin_dir);
        } else {
            snprintf(bin_dir, sizeof(bin_dir), "..");
            snprintf(core_path, sizeof(core_path), "../src/core/core.til");
            snprintf(ext_c_path, sizeof(ext_c_path), "../src/c/ext.c");
        }
    }
    char *core_source = read_file(core_path);
    U32 core_count;
    Token *core_tokens = core_source ? tokenize(core_source, core_path, &core_count) : NULL;
    Expr *core_ast = core_tokens ? parse(core_tokens, core_count, core_path, NULL) : NULL;

    // Resolve imports from core.til (relative to src/core/)
    Vec core_import_decls = Vec_new(sizeof(Expr *));
    if (core_ast) {
        Vec core_imports = extract_imports(core_ast);
        if (core_imports.count > 0) {
            char core_dir[PATH_MAX];
            snprintf(core_dir, sizeof(core_dir), "%s/src/core", bin_dir);
            Set resolved = Set_new(sizeof(Str *), str_ptr_cmp);
            Vec resolve_stack = Vec_new(sizeof(Str *));
            int err = resolve_imports(&core_imports, core_dir, &resolved, &resolve_stack,
                                      &core_import_decls, NULL);
            Set_delete(&resolved);
            Vec_delete(&resolve_stack);
            if (err) return 1;
        }
        Vec_delete(&core_imports);
    }

    char *source = read_file(path);
    if (!source) return 1;

    U32 count;
    Token *tokens = tokenize(source, path, &count);

    Str *mode_str = NULL;
    Expr *ast = parse(tokens, count, path, &mode_str);
    Vec imports = extract_imports(ast);

    const Mode *mode = NULL;
    if (mode_str) {
        mode = mode_resolve(mode_str->c_str);
        if (!mode) {
            fprintf(stderr, "error: unknown mode '%s'\n", mode_str->c_str);
            return 1;
        }
    }

    // If mode has auto_import, load its .til declarations
    Expr *mode_ast = NULL;
    char mode_til_path[256] = "";
    if (mode && mode->auto_import) {
        snprintf(mode_til_path, sizeof(mode_til_path), "%s/src/modes/%s.til", bin_dir, mode->auto_import);
        char *mode_source = read_file(mode_til_path);
        if (!mode_source) {
            fprintf(stderr, "error: mode '%s' requires %s.til (not found at '%s')\n",
                    mode->name, mode->auto_import, mode_til_path);
            return 1;
        }
        U32 mode_count;
        Token *mode_tokens = tokenize(mode_source, mode_til_path, &mode_count);
        mode_ast = parse(mode_tokens, mode_count, mode_til_path, NULL);
    }

    // Resolve imports recursively
    Vec import_decls = Vec_new(sizeof(Expr *));
    if (imports.count > 0) {
        Set resolved = Set_new(sizeof(Str *), str_ptr_cmp);
        Vec resolve_stack = Vec_new(sizeof(Str *));

        // Compute base directory of user file
        char user_dir[PATH_MAX];
        char *abs_path = realpath(path, NULL);
        if (abs_path) {
            strncpy(user_dir, abs_path, sizeof(user_dir));
            user_dir[sizeof(user_dir) - 1] = '\0';
            char *slash = strrchr(user_dir, '/');
            if (slash) *slash = '\0';
            // Add user file itself to resolved set (so it can't import itself)
            Str *abs_str = Str_new(abs_path);
            Set_add(&resolved, &abs_str);
            Vec_push(&resolve_stack, &abs_str);
            free(abs_path);
        } else {
            snprintf(user_dir, sizeof(user_dir), ".");
        }

        // Standard library path
        char lib_dir[PATH_MAX];
        snprintf(lib_dir, sizeof(lib_dir), "%s/src/lib", bin_dir);

        int err = resolve_imports(&imports, user_dir, &resolved, &resolve_stack,
                                  &import_decls, lib_dir);
        Set_delete(&resolved);
        Vec_delete(&resolve_stack);
        Vec_delete(&imports);
        if (err) return 1;
    }

    // Prepend core declarations (and mode .til + imports) to program AST
    if (core_ast && core_ast->children.count > 0) {
        Vec merged = Vec_new(sizeof(Expr *));
        for (U32 i = 0; i < core_ast->children.count; i++) {
            Expr *ch = expr_child(core_ast, i);
            mark_core(ch);
            Vec_push(&merged, &ch);
        }
        for (U32 i = 0; i < core_import_decls.count; i++) {
            Expr *ch = *(Expr **)Vec_get(&core_import_decls, i);
            mark_core(ch);
            Vec_push(&merged, &ch);
        }
        if (mode_ast) {
            for (U32 i = 0; i < mode_ast->children.count; i++) {
                Expr *ch = expr_child(mode_ast, i);
                Vec_push(&merged, &ch);
            }
        }
        for (U32 i = 0; i < import_decls.count; i++) {
            Expr *ch = *(Expr **)Vec_get(&import_decls, i);
            Vec_push(&merged, &ch);
        }
        for (U32 i = 0; i < ast->children.count; i++) {
            Expr *ch = expr_child(ast, i);
            Vec_push(&merged, &ch);
        }
        Vec_delete(&ast->children);
        ast->children = merged;
    }

    // Extract link("lib") and link_c("file.c") directives from AST
    char link_flags[512] = "";
    I32 link_pos = 0;
    char link_c_paths[2048] = "";
    I32 link_c_pos = 0;
    {
        Vec kept = Vec_new(sizeof(Expr *));
        for (U32 i = 0; i < ast->children.count; i++) {
            Expr *stmt = expr_child(ast, i);
            if (stmt->type == NODE_FCALL && stmt->children.count == 2 &&
                expr_child(stmt, 0)->type == NODE_IDENT &&
                expr_child(stmt, 1)->type == NODE_LITERAL_STR) {
                Str *fname = expr_child(stmt, 0)->data.str_val;
                Str *arg = expr_child(stmt, 1)->data.str_val;
                if (Str_eq_c(fname, "link")) {
                    link_pos += snprintf(link_flags + link_pos, sizeof(link_flags) - link_pos,
                                         " -l%.*s", (int)arg->cap, arg->c_str);
                } else if (Str_eq_c(fname, "link_c")) {
                    link_c_pos += snprintf(link_c_paths + link_c_pos, sizeof(link_c_paths) - link_c_pos,
                                           "%s%.*s", link_c_pos > 0 ? " " : "", (int)arg->cap, arg->c_str);
                } else {
                    Vec_push(&kept, &stmt);
                }
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
    I32 type_errors = type_check(ast, scope, mode);
    tscope_free(scope);
    if (type_errors > 0) {
        fprintf(stderr, "%d type error(s) found\n", type_errors);
        expr_free(ast);
        free(tokens);
        free(source);
        return 1;
    }

    Bool run_tests = strcmp(command, "test") == 0 || (mode == &MODE_TEST) || (mode == &MODE_PURE) || (mode == &MODE_PURA);

    precomp(ast);
    // Skip scavenging for lib/pure translate/build — all declarations are public API
    Bool is_lib_target = mode && (strcmp(mode->name, "lib") == 0 || strcmp(mode->name, "liba") == 0 ||
                                  strcmp(mode->name, "pure") == 0 || strcmp(mode->name, "pura") == 0)
                              && (strcmp(command, "translate") == 0 || strcmp(command, "build") == 0);
    if (!is_lib_target)
        scavenge(ast, mode, run_tests);

    I32 result = 0;

    // Use link_c() paths as user .c files (replaces companion .c auto-detection)
    const char *user_c = link_c_pos > 0 ? link_c_paths : NULL;

    // Append -l flags from CLI args (argv[3..])
    char *filtered_argv[argc];
    U32 user_argc = 0;
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

    Bool is_lib_mode = mode && (strcmp(mode->name, "lib") == 0 || strcmp(mode->name, "liba") == 0);
    Bool is_lib_output = is_lib_mode || (mode && (strcmp(mode->name, "pure") == 0 || strcmp(mode->name, "pura") == 0));

    if (strcmp(command, "interpret") == 0 || strcmp(command, "test") == 0) {
        if (is_lib_mode && strcmp(command, "interpret") == 0) {
            fprintf(stderr, "error: cannot interpret a library — use translate or build\n");
            expr_free(ast); free(tokens); free(source);
            return 1;
        }
        result = interpret(ast, mode, run_tests, path, user_c, ext_c_path, lflags, user_argc, user_argv);
    } else if (strcmp(command, "translate") == 0 || strcmp(command, "build") == 0 || strcmp(command, "run") == 0) {
        if (is_lib_mode && strcmp(command, "run") == 0) {
            fprintf(stderr, "error: cannot run a library — use translate or build\n");
            expr_free(ast); free(tokens); free(source);
            return 1;
        }
        // Derive output paths from input: examples/hello_cli.til -> gen/c/hello_cli.c, bin/c/hello_cli
        const char *basename = strrchr(path, '/');
        basename = basename ? basename + 1 : path;
        I32 name_len = (int)(strlen(basename) - 4); // strip .til
        if (name_len <= 0) name_len = (int)strlen(basename);

        char c_path[256], bin_path[256];
        snprintf(c_path, sizeof(c_path), "gen/c/%.*s.c", name_len, basename);
        snprintf(bin_path, sizeof(bin_path), "bin/c/%.*s", name_len, basename);

        Bool do_lib = is_lib_output && strcmp(command, "run") != 0;

        if (do_lib)
            system("mkdir -p gen/c gen/til gen/lib");
        else
            system("mkdir -p gen/c bin/c");

        result = build(ast, mode, run_tests, path, c_path);

        // For lib/pure translate/build: generate .h header and .til binding
        if (result == 0 && do_lib) {
            char h_path[256], til_path[256], lib_name[256];
            snprintf(h_path, sizeof(h_path), "gen/c/%.*s.h", name_len, basename);
            snprintf(til_path, sizeof(til_path), "gen/til/%.*s.til", name_len, basename);
            snprintf(lib_name, sizeof(lib_name), "%.*s", name_len, basename);
            result = build_header(ast, h_path);
            if (result == 0)
                result = build_til_binding(ast, til_path, lib_name);
            if (result == 0 && strcmp(command, "translate") == 0) {
                printf("Generated: %s\n", c_path);
                printf("Generated: %s\n", h_path);
                printf("Generated: %s\n", til_path);
            }
            if (result == 0 && strcmp(command, "build") == 0) {
                result = compile_lib(c_path, lib_name, ext_c_path, user_c, lflags);
                if (result == 0) {
                    printf("Generated: %s\n", c_path);
                    printf("Generated: %s\n", h_path);
                    printf("Generated: %s\n", til_path);
                    printf("Generated: gen/lib/lib%s.so\n", lib_name);
                    printf("Generated: gen/lib/lib%s.a\n", lib_name);
                }
            }
        }

        if (result == 0 && !do_lib && strcmp(command, "translate") == 0) {
            printf("Generated: %s\n", c_path);
        }
        if (result == 0 && !do_lib && strcmp(command, "translate") != 0) {
            result = compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
        }
        if (result == 0 && !do_lib && strcmp(command, "run") == 0) {
            // Build command with user args appended
            I32 cmdlen = (int)strlen(bin_path);
            for (U32 i = 0; i < user_argc; i++)
                cmdlen += 1 + (I32)strlen(user_argv[i]) + 2; // space + quotes
            char *cmd = malloc(cmdlen + 1);
            I32 pos = snprintf(cmd, cmdlen + 1, "%s", bin_path);
            for (U32 i = 0; i < user_argc; i++)
                pos += snprintf(cmd + pos, cmdlen + 1 - pos, " '%s'", user_argv[i]);
            int status = system(cmd);
            free(cmd);
            if (WIFEXITED(status))
                result = WEXITSTATUS(status);
            else
                result = 1;
        }
    } else if (strcmp(command, "ast") == 0) {
        printf("mode: %s\n", mode ? mode->name : "(none)");
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
