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

// --- Parse wrapper ---

static Str _parse_mode;

Expr *til_parse(Vec *tokens, Str *path) {
    _parse_mode = (Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    // Clone path: parser stores Str* in Parser struct and propagates to AST nodes.
    return parse(tokens, Str_clone(path), &_parse_mode);
}
Str *til_parse_mode(void) { return Str_clone(&_parse_mode); }

// --- Expr field accessors ---

// NULL-safe: .and() chains in compiled til evaluate all operands eagerly
// (unlike C's && which short-circuits), so these may be called on NULL exprs
// or out-of-bounds indices when a prior condition would have been false.
I32 expr_get_tag(Expr *e) { return e ? (I32)e->data.tag : (I32)-1; }
Str *expr_get_str_val(Expr *e) {
    if (!e) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    // str_val shares a union with decl/func_def — only valid for these node types
    switch (e->data.tag) {
    case ExprData_TAG_Ident: case ExprData_TAG_LiteralStr: case ExprData_TAG_LiteralNum:
    case ExprData_TAG_LiteralBool: case ExprData_TAG_Assign: case ExprData_TAG_ForIn:
    case ExprData_TAG_FieldAccess: case ExprData_TAG_FieldAssign: case ExprData_TAG_NamedArg:
        return e->data.data.Ident.count > 0 ? &e->data.data.Ident : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    default:
        return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    }
}
Expr *expr_get_child(Expr *e, U32 i) {
    if (!e || i >= e->children.count) return NULL;
    return Expr_child(e, &(I64){(I64)(i)});
}
U32 expr_nchildren(Expr *e) { return e ? e->children.count : 0; }
// Replace children: old children are freed, new_children is moved in
void expr_swap_children(Expr *e, Vec *new_children) {
    Vec_delete(&e->children, &(Bool){0});
    e->children = *new_children;
    new_children->data = NULL;
    new_children->count = 0;
    new_children->cap = 0;
}

// Create new Vec for collecting Expr values (elem_size = sizeof(Expr))
Vec *expr_vec_new(void) {
    Vec *v = malloc(sizeof(Vec));
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); *v = *_vp; free(_vp); }
    return v;
}

// Push an Expr into a Vec (clones e, takes ownership of clone)
void expr_vec_push(Vec *v, Expr *e) {
    Vec_push(v, Expr_clone(e));
}

// Get Expr* from Vec at index i
Expr *expr_vec_get(Vec *v, U32 i) {
    return (Expr *)Vec_get(v, &(U64){(U64)(i)});
}

U32 expr_vec_count(Vec *v) { return v->count; }

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

// Return owned copy of first n bytes of s (avoids CAP_VIEW + scavenger ordering issues)
Str *til_str_left(Str *s, U64 n) {
    if (!s || n == 0) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    U64 len = (U64)s->count;
    if (n > len) n = len;
    char *buf = malloc(n + 1);
    memcpy(buf, s->c_str, n);
    buf[n] = '\0';
    Str *result = Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
    free(buf);
    return result;
}

Str *til_realpath(Str *path) {
    char *abs = realpath((const char *)path->c_str, NULL);
    if (!abs) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    Str *s = Str_clone(&(Str){.c_str = (U8*)(abs), .count = (U64)strlen((const char*)(abs)), .cap = CAP_VIEW});
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

