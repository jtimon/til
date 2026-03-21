// FFI bridge for til.til — thin wrappers around C module APIs.
// Converts Str* ↔ const char*, handles output params, provides Expr field accessors.

#include "../../bootstrap/modes.h"
#include "pre70.h"
#include "interpreter.h"
#include "builder.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

// Replace children: old children are freed, new_children is moved in
void expr_swap_children(Expr *e, Vec *new_children) {
    Vec_delete(&e->children, &(Bool){0});
    e->children = *new_children;
    memset(new_children, 0, sizeof(Vec));
}

// --- Pipeline wrappers ---

I32 til_interpret_v(Expr *ast, Mode *mode, Bool run_tests,
                    Str *path, Str *user_c, Str *ext_c, Str *link_flags,
                    Vec *user_argv) {
    if (user_c && user_c->count == 0) user_c = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    return interpret(ast, mode, run_tests, path, user_c, ext_c, link_flags, user_argv);
}

I32 til_compile_c(Str *c_path, Str *bin_path, Str *ext_c, Str *user_c, Str *lflags) {
    if (user_c && user_c->count == 0) user_c = NULL;
    if (lflags && lflags->count == 0) lflags = NULL;
    return compile_c(c_path, bin_path, ext_c, user_c, lflags);
}

I32 til_compile_lib(Str *c_path, Str *lib_name, Str *ext_c, Str *user_c, Str *lflags) {
    if (user_c && user_c->count == 0) user_c = NULL;
    if (lflags && lflags->count == 0) lflags = NULL;
    return compile_lib(c_path, lib_name, ext_c, user_c, lflags);
}

// --- Utility wrappers ---

Str *til_realpath(Str *path) {
    char *abs = realpath((const char *)path->c_str, NULL);
    if (!abs) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    Str *s = Str_clone(&(Str){.c_str = (U8*)(abs), .count = (USize)strlen((const char*)(abs)), .cap = CAP_VIEW});
    free(abs);
    return s;
}

I32 til_system(Str *cmd) {
    int status = system((const char *)cmd->c_str);
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return 1;
}


// Derive project root by searching upward from binary location for src/core/core.til
Str *til_bin_dir(void) {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
    buf[len] = '\0';
    // Strip binary name
    char *slash = strrchr(buf, '/');
    if (slash) *slash = '\0';
    // Search upward for src/core/core.til
    for (int i = 0; i < 5; i++) {
        char test[PATH_MAX + 32];
        snprintf(test, sizeof(test), "%s/src/core/core.til", buf);
        if (access(test, F_OK) == 0) return Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
        slash = strrchr(buf, '/');
        if (!slash) break;
        *slash = '\0';
    }
    return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
}
