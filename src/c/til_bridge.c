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

// --- Utility wrappers ---

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
