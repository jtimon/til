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

static char *read_file(Str *path) {
    FILE *f = fopen((const char *)path->c_str, "rb");
    if (!f) {
        fprintf(stderr, "error: could not open '%s'\n", path->c_str);
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
    Vec paths; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); paths = *_vp; free(_vp); }
    Vec kept; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); kept = *_vp; free(_vp); }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type.tag == NODE_FCALL && stmt->children.count == 2 &&
            expr_child(stmt, 0)->type.tag == NODE_IDENT &&
            Str_eq_c(expr_child(stmt, 0)->type.str_val, "import") &&
            expr_child(stmt, 1)->type.tag == NODE_LITERAL_STR) {
            Str *path = expr_child(stmt, 1)->type.str_val;
            { Str **_p = malloc(sizeof(Str *)); *_p = path; Vec_push(&paths, _p); }
        } else {
            { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&kept, _p); }
        }
    }
    Vec_delete(&body->children, &(Bool){0});
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
static int resolve_imports(Vec *import_paths, Str *base_dir,
                           Set *resolved, Vec *stack,
                           Vec *merged,
                           Str *lib_dir) {
    Str *slash = Str_new("/");
    for (U32 i = 0; i < import_paths->count; i++) {
        Str *import_path = *(Str **)Vec_get(import_paths, &(U64){(U64)(i)});

        // Try relative to importing file's directory, then lib_dir
        Str *try_path = Str_concat(Str_concat(base_dir, slash), import_path);
        char *abs = realpath((const char *)try_path->c_str, NULL);
        if (!abs && lib_dir) {
            try_path = Str_concat(Str_concat(lib_dir, slash), import_path);
            abs = realpath((const char *)try_path->c_str, NULL);
        }
        if (!abs) {
            fprintf(stderr, "error: could not find import '%s' (from %s/)\n",
                    import_path->c_str, base_dir->c_str);
            return 1;
        }

        Str *abs_str = Str_new(abs);

        // Dedup: skip if already resolved (also handles circular imports —
        // files are added to resolved when they start processing, so a
        // circular import is silently skipped here)
        if (*Set_has(resolved, abs_str)) {
            free(abs);
            continue;
        }
        { Str *_p = malloc(sizeof(Str)); *_p = (Str){abs_str->c_str, abs_str->count, CAP_VIEW}; Set_add(resolved, _p); }
        { Str **_p = malloc(sizeof(Str *)); *_p = abs_str; Vec_push(stack, _p); }

        // Load, lex, parse the imported file
        char *source = read_file(abs_str);
        if (!source) { free(abs); return 1; }

        U32 tok_count;
        Token *toks = tokenize(source, abs_str, &tok_count);

        Str *sub_mode = NULL;
        Expr *sub_ast = parse(toks, tok_count, abs_str, &sub_mode);
        Vec sub_imports = extract_imports(sub_ast);

        if (!sub_mode) {
            fprintf(stderr, "error: imported file '%s' has no mode declaration (must be lib/liba/pure/pura)\n", abs);
            free(abs);
            return 1;
        } else {
            const Mode *sm = mode_resolve((const char *)sub_mode->c_str);
            if (!sm || !(sm == &MODE_LIB || sm == &MODE_LIBA || sm == &MODE_PURE || sm == &MODE_PURA)) {
                fprintf(stderr, "error: imported file '%s' cannot use mode '%s'\n", abs, sub_mode->c_str);
                free(abs);
                return 1;
            }
        }

        // Get imported file's directory for recursive resolution
        Str *sub_dir;
        {
            const char *last_slash = strrchr(abs, '/');
            if (last_slash)
                sub_dir = Str_new_len(abs, last_slash - abs);
            else
                sub_dir = Str_new(".");
        }

        // Recurse for sub-imports
        if (sub_imports.count > 0) {
            int err = resolve_imports(&sub_imports, sub_dir, resolved, stack,
                                      merged, lib_dir);
            if (err) { free(abs); return err; }
        }
        Vec_delete(&sub_imports, &(Bool){0});

        // Append imported file's declarations
        for (U32 j = 0; j < sub_ast->children.count; j++) {
            Expr *ch = expr_child(sub_ast, j);
            { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(merged, _p); }
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
Expr *til_prepare(Str *path, Str *bin_dir) {
    // Single resolved set for all imports
    Set resolved; { Set *_sp = Set_new(Str_new("Str"), &(U64){sizeof(Str)}); resolved = *_sp; free(_sp); }
    Vec resolve_stack; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); resolve_stack = *_vp; free(_vp); }

    // Add user file to resolved set early
    char *user_abs = realpath((const char *)path->c_str, NULL);
    if (user_abs) {
        Str *user_abs_str = Str_new(user_abs);
        { Str *_p = malloc(sizeof(Str)); *_p = (Str){user_abs_str->c_str, user_abs_str->count, CAP_VIEW}; Set_add(&resolved, _p); }
        free(user_abs);
    }

    // Load core.til
    Str *core_path = Str_concat(bin_dir, Str_new("/src/core/core.til"));
    char *core_source = read_file(core_path);
    if (!core_source) return NULL;
    U32 core_count;
    Token *core_tokens = tokenize(core_source, core_path, &core_count);
    Str *core_mode = NULL;
    Expr *core_ast = parse(core_tokens, core_count, core_path, &core_mode);

    // Add core.til to resolved set
    char *core_abs = realpath((const char *)core_path->c_str, NULL);
    if (core_abs) {
        Str *core_abs_str = Str_new(core_abs);
        { Str *_p = malloc(sizeof(Str)); *_p = (Str){core_abs_str->c_str, core_abs_str->count, CAP_VIEW}; Set_add(&resolved, _p); }
        free(core_abs);
    }

    // Resolve core imports
    Vec core_import_decls; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); core_import_decls = *_vp; free(_vp); }
    Vec core_imports = extract_imports(core_ast);
    if (core_imports.count > 0) {
        Str *core_dir = Str_concat(bin_dir, Str_new("/src/core"));
        int err = resolve_imports(&core_imports, core_dir, &resolved, &resolve_stack,
                                  &core_import_decls, NULL);
        if (err) return NULL;
    }
    Vec_delete(&core_imports, &(Bool){0});

    Set_delete(&resolved, &(Bool){0});
    Vec_delete(&resolve_stack, &(Bool){0});

    // Load user file
    char *source = read_file(path);
    if (!source) return NULL;
    U32 count;
    Token *tokens = tokenize(source, path, &count);
    Expr *ast = parse(tokens, count, path, NULL);

    // Merge: core + core imports + user
    Vec merged; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); merged = *_vp; free(_vp); }
    for (U32 i = 0; i < core_ast->children.count; i++) {
        Expr *ch = expr_child(core_ast, i);
        mark_core(ch);
        { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
    }
    for (U32 i = 0; i < core_import_decls.count; i++) {
        Expr *ch = *(Expr **)Vec_get(&core_import_decls, &(U64){(U64)(i)});
        mark_core(ch);
        { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
    }
    for (U32 i = 0; i < ast->children.count; i++) {
        Expr *ch = expr_child(ast, i);
        { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
    }
    Vec_delete(&ast->children, &(Bool){0});
    ast->children = merged;

    // Strip link() and link_c() directives
    Vec kept; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); kept = *_vp; free(_vp); }
    for (U32 i = 0; i < ast->children.count; i++) {
        Expr *stmt = expr_child(ast, i);
        if (stmt->type.tag == NODE_FCALL && stmt->children.count == 2 &&
            expr_child(stmt, 0)->type.tag == NODE_IDENT &&
            expr_child(stmt, 1)->type.tag == NODE_LITERAL_STR) {
            Str *fn = expr_child(stmt, 0)->type.str_val;
            if (Str_eq_c(fn, "link") || Str_eq_c(fn, "link_c")) continue;
        }
        { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&kept, _p); }
    }
    Vec_delete(&ast->children, &(Bool){0});
    ast->children = kept;

    return ast;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage();
        return 1;
    }

    const char *command = argv[1];
    Str *path = NULL;

    if (argc == 2) {
        // Single arg: if it's a known command without a path, handle it
        if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
            usage();
            return 0;
        }
        // Otherwise treat as a path (like til does)
        path = Str_new(command);
        command = "interpret";
    } else {
        path = Str_new(argv[2]);
    }

    if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
        usage();
        return 0;
    }

    // Resolve paths relative to binary location
    Str *bin_dir;
    {
        const char *slash = strrchr(argv[0], '/');
        if (slash) {
            Str *bin_parent = Str_new_len(argv[0], slash - argv[0]);
            bin_dir = Str_concat(bin_parent, Str_new("/.."));
        } else {
            bin_dir = Str_new("..");
        }
    }
    Str *core_path = Str_concat(bin_dir, Str_new("/src/core/core.til"));
    Str *ext_c_path = Str_concat(bin_dir, Str_new("/src/c/ext.c"));
    // Single resolved set for all imports (core + user), so no file is loaded twice
    Set resolved; { Set *_sp = Set_new(Str_new("Str"), &(U64){sizeof(Str)}); resolved = *_sp; free(_sp); }
    Vec resolve_stack; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); resolve_stack = *_vp; free(_vp); }

    // Add user file to resolved set early (so core imports skip it if it overlaps)
    Str *user_dir;
    {
        char *user_abs_path = realpath((const char *)path->c_str, NULL);
        if (user_abs_path) {
            const char *slash = strrchr(user_abs_path, '/');
            if (slash)
                user_dir = Str_new_len(user_abs_path, slash - user_abs_path);
            else
                user_dir = Str_new(".");
            Str *user_abs_str = Str_new(user_abs_path);
            { Str *_p = malloc(sizeof(Str)); *_p = (Str){user_abs_str->c_str, user_abs_str->count, CAP_VIEW}; Set_add(&resolved, _p); }
            free(user_abs_path);
        } else {
            user_dir = Str_new(".");
        }
    }

    char *core_source = read_file(core_path);
    U32 core_count;
    Token *core_tokens = core_source ? tokenize(core_source, core_path, &core_count) : NULL;
    Str *core_mode = NULL;
    Expr *core_ast = core_tokens ? parse(core_tokens, core_count, core_path, &core_mode) : NULL;

    // Add core.til to resolved set; skip prepending if user file IS core.til
    if (core_ast) {
        char *core_abs = realpath((const char *)core_path->c_str, NULL);
        if (core_abs) {
            Str *core_abs_str = Str_new(core_abs);
            if (*Set_has(&resolved, core_abs_str)) {
                // User file is core.til itself — don't prepend core to itself
                core_ast = NULL;
            }
            { Str *_p = malloc(sizeof(Str)); *_p = (Str){core_abs_str->c_str, core_abs_str->count, CAP_VIEW}; Set_add(&resolved, _p); }
            free(core_abs);
        }
    }

    // Resolve imports from core.til (relative to src/core/)
    Vec core_import_decls; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); core_import_decls = *_vp; free(_vp); }
    if (core_ast) {
        Vec core_imports = extract_imports(core_ast);
        if (core_imports.count > 0) {
            Str *core_dir = Str_concat(bin_dir, Str_new("/src/core"));
            int err = resolve_imports(&core_imports, core_dir, &resolved, &resolve_stack,
                                      &core_import_decls, NULL);
            if (err) return 1;
        }
        Vec_delete(&core_imports, &(Bool){0});
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
        mode = mode_resolve((const char *)mode_str->c_str);
        if (!mode) {
            fprintf(stderr, "error: unknown mode '%s'\n", mode_str->c_str);
            return 1;
        }
    }

    // If mode has auto_import, load its .til declarations
    Expr *mode_ast = NULL;
    Str *mode_til_path = NULL;
    if (mode && mode->auto_import) {
        mode_til_path = Str_concat(Str_concat(bin_dir, Str_new("/src/modes/")),
                                   Str_concat(Str_new(mode->auto_import), Str_new(".til")));
        char *mode_source = read_file(mode_til_path);
        if (!mode_source) {
            fprintf(stderr, "error: mode '%s' requires %s.til (not found at '%s')\n",
                    mode->name, mode->auto_import, mode_til_path->c_str);
            return 1;
        }
        U32 mode_count;
        Token *mode_tokens = tokenize(mode_source, mode_til_path, &mode_count);
        mode_ast = parse(mode_tokens, mode_count, mode_til_path, NULL);
    }

    // Resolve user imports (using same resolved set — skips files already loaded by core)
    Vec import_decls; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); import_decls = *_vp; free(_vp); }
    if (imports.count > 0) {
        Str *lib_dir = Str_concat(bin_dir, Str_new("/src/lib"));

        int err = resolve_imports(&imports, user_dir, &resolved, &resolve_stack,
                                  &import_decls, lib_dir);
        Vec_delete(&imports, &(Bool){0});
        if (err) return 1;
    }

    Set_delete(&resolved, &(Bool){0});
    Vec_delete(&resolve_stack, &(Bool){0});

    // Prepend core declarations (and mode .til + imports) to program AST
    {
        Bool need_merge = (core_ast && core_ast->children.count > 0) ||
                          import_decls.count > 0 || mode_ast;
        if (need_merge) {
            Vec merged; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); merged = *_vp; free(_vp); }
            if (core_ast) {
                for (U32 i = 0; i < core_ast->children.count; i++) {
                    Expr *ch = expr_child(core_ast, i);
                    mark_core(ch);
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
                }
            }
            for (U32 i = 0; i < core_import_decls.count; i++) {
                Expr *ch = *(Expr **)Vec_get(&core_import_decls, &(U64){(U64)(i)});
                mark_core(ch);
                { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
            }
            if (mode_ast) {
                for (U32 i = 0; i < mode_ast->children.count; i++) {
                    Expr *ch = expr_child(mode_ast, i);
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
                }
            }
            for (U32 i = 0; i < import_decls.count; i++) {
                Expr *ch = *(Expr **)Vec_get(&import_decls, &(U64){(U64)(i)});
                { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
            }
            for (U32 i = 0; i < ast->children.count; i++) {
                Expr *ch = expr_child(ast, i);
                { Expr **_p = malloc(sizeof(Expr *)); *_p = ch; Vec_push(&merged, _p); }
            }
            Vec_delete(&ast->children, &(Bool){0});
            ast->children = merged;
        }
    }

    // Extract link("lib") and link_c("file.c") directives from AST
    Str *link_flags = Str_new("");
    Str *link_c_paths = Str_new("");
    {
        Vec kept; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); kept = *_vp; free(_vp); }
        for (U32 i = 0; i < ast->children.count; i++) {
            Expr *stmt = expr_child(ast, i);
            if (stmt->type.tag == NODE_FCALL && stmt->children.count == 2 &&
                expr_child(stmt, 0)->type.tag == NODE_IDENT &&
                expr_child(stmt, 1)->type.tag == NODE_LITERAL_STR) {
                Str *fname = expr_child(stmt, 0)->type.str_val;
                Str *arg = expr_child(stmt, 1)->type.str_val;
                if (Str_eq_c(fname, "link")) {
                    link_flags = Str_concat(Str_concat(link_flags, Str_new(" -l")), arg);
                } else if (Str_eq_c(fname, "link_c")) {
                    if (link_c_paths->count > 0)
                        link_c_paths = Str_concat(link_c_paths, Str_new(" "));
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&kept, _p); }
                }
            } else {
                { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&kept, _p); }
            }
        }
        Vec_delete(&ast->children, &(Bool){0});
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
    Str *user_c = link_c_paths->count > 0 ? link_c_paths : NULL;

    // Append -l flags from CLI args (argv[3..])
    char *filtered_argv[argc];
    U32 user_argc = 0;
    for (I32 i = 3; i < argc; i++) {
        if (strncmp(argv[i], "-l", 2) == 0) {
            const char *lib = argv[i] + 2;
            if (*lib == '\0' && i + 1 < argc) { lib = argv[++i]; }
            link_flags = Str_concat(Str_concat(link_flags, Str_new(" -l")), Str_new(lib));
        } else {
            filtered_argv[user_argc++] = argv[i];
        }
    }
    char **user_argv = user_argc > 0 ? filtered_argv : NULL;
    Str *lflags = link_flags->count > 0 ? link_flags : NULL;

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
        I64 last_slash = *Str_rfind(path, Str_new("/"));
        Str *basename = last_slash >= 0 ? Str_substr(path, &(U64){(U64)(last_slash + 1)}, &(U64){(U64)(path->count - last_slash - 1)}) : path;
        // Strip .til extension
        Str *name = *Str_ends_with(basename, Str_new(".til"))
            ? Str_substr(basename, &(U64){(U64)(0)}, &(U64){(U64)(basename->count - 4)}) : basename;

        Str *c_path = Str_concat(Str_concat(Str_new("gen/c/"), name), Str_new(".c"));
        Str *bin_path = Str_concat(Str_new("bin/c/"), name);

        Bool do_lib = is_lib_output && strcmp(command, "run") != 0;

        if (do_lib)
            system("mkdir -p gen/c gen/til gen/lib");
        else
            system("mkdir -p gen/c bin/c");

        result = build(ast, mode, run_tests, path, c_path);

        // For lib/pure translate/build: generate .h header and .til binding
        if (result == 0 && do_lib) {
            Str *h_path = Str_concat(Str_concat(Str_new("gen/c/"), name), Str_new(".h"));
            Str *til_path = Str_concat(Str_concat(Str_new("gen/til/"), name), Str_new(".til"));
            result = build_header(ast, h_path);
            if (result == 0)
                result = build_til_binding(ast, til_path, name);
            if (result == 0 && strcmp(command, "translate") == 0) {
                printf("Generated: %s\n", c_path->c_str);
                printf("Generated: %s\n", h_path->c_str);
                printf("Generated: %s\n", til_path->c_str);
            }
            if (result == 0 && strcmp(command, "build") == 0) {
                result = compile_lib(c_path, name, ext_c_path, user_c, lflags);
                if (result == 0) {
                    printf("Generated: %s\n", c_path->c_str);
                    printf("Generated: %s\n", h_path->c_str);
                    printf("Generated: %s\n", til_path->c_str);
                    printf("Generated: gen/lib/lib%s.so\n", name->c_str);
                    printf("Generated: gen/lib/lib%s.a\n", name->c_str);
                }
            }
        }

        if (result == 0 && !do_lib && strcmp(command, "translate") == 0) {
            printf("Generated: %s\n", c_path->c_str);
        }
        if (result == 0 && !do_lib && strcmp(command, "translate") != 0) {
            result = compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
        }
        if (result == 0 && !do_lib && strcmp(command, "run") == 0) {
            // Build command with user args appended
            Str *cmd = Str_clone(bin_path);
            for (U32 i = 0; i < user_argc; i++) {
                cmd = Str_concat(Str_concat(Str_concat(cmd, Str_new(" '")),
                                            Str_new(user_argv[i])), Str_new("'"));
            }
            int status = system((const char *)cmd->c_str);
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
