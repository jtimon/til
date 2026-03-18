// FFI bridge for til.til — thin wrappers around C module APIs.
// Converts Str* ↔ const char*, handles output params, provides Expr field accessors.

#include "../../bootstrap/ast.h"
#include "pre70.h"
#include "parser.h"
#include "initer.h"
#include "typer.h"
#include "interpreter.h"
#include "builder.h"
#include "precomp.h"
#include "scavenger.h"
#include "modes.h"
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

Expr *expr_null(void) { return NULL; }
Bool expr_is_null(Expr *e) { return e == NULL; }
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
void expr_set_core(Expr *e) { e->is_core = true; }
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

// --- Mode helpers ---

Mode *til_mode_resolve(Str *name) {
    if (!name) return NULL;
    if ((name->count == 6 && memcmp(name->c_str, "script", 6) == 0)) return &MODE_SCRIPT;
    if ((name->count == 3 && memcmp(name->c_str, "cli", 3) == 0))    return &MODE_CLI;
    if ((name->count == 3 && memcmp(name->c_str, "gui", 3) == 0))    return &MODE_GUI;
    if ((name->count == 4 && memcmp(name->c_str, "test", 4) == 0))   return &MODE_TEST;
    if ((name->count == 4 && memcmp(name->c_str, "pure", 4) == 0))   return &MODE_PURE;
    if ((name->count == 4 && memcmp(name->c_str, "pura", 4) == 0))   return &MODE_PURA;
    if ((name->count == 3 && memcmp(name->c_str, "lib", 3) == 0))    return &MODE_LIB;
    if ((name->count == 4 && memcmp(name->c_str, "liba", 4) == 0))   return &MODE_LIBA;
    return NULL;
}

Bool til_mode_eq(Mode *a, Mode *b) { return a == b; }

Mode *til_mode_none(void)   { return NULL; }
Mode *til_mode_script(void) { return &MODE_SCRIPT; }
Mode *til_mode_cli(void)    { return &MODE_CLI; }
Mode *til_mode_gui(void)    { return &MODE_GUI; }
Mode *til_mode_test(void)   { return &MODE_TEST; }
Mode *til_mode_pure(void)   { return &MODE_PURE; }
Mode *til_mode_pura(void)   { return &MODE_PURA; }
Mode *til_mode_lib(void)    { return &MODE_LIB; }
Mode *til_mode_liba(void)   { return &MODE_LIBA; }

Str *til_mode_name(Mode *m) { return m ? Str_clone((Str *)&m->name) : Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}); }
Str *til_mode_auto_import(Mode *m) {
    return m ? Str_clone((Str *)&m->auto_import) : Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
}

Bool til_mode_is_lib(Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA);
}
Bool til_mode_is_lib_output(Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA ||
                 m == &MODE_PURE || m == &MODE_PURA);
}

// --- Pipeline wrappers ---

I32 til_init_declarations(Expr *program, TypeScope *scope) {
    return init_declarations(program, scope);
}

I32 til_type_check(Expr *program, TypeScope *scope, Mode *mode) {
    return type_check(program, scope, mode);
}

void til_precomp(Expr *program) { precomp(program); }

void til_scavenge(Expr *program, Mode *mode, Bool run_tests) {
    scavenge(program, mode, run_tests);
}

I32 til_interpret_v(Expr *ast, Mode *mode, Bool run_tests,
                    Str *path, Str *user_c, Str *ext_c, Str *link_flags,
                    Vec *user_argv) {
    if (user_c && user_c->count == 0) user_c = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    return interpret(ast, mode, run_tests, path, user_c, ext_c, link_flags, user_argv);
}

I32 til_build(Expr *ast, Mode *mode, Bool run_tests,
              Str *path, Str *c_path) {
    return build(ast, mode, run_tests, path, c_path);
}

I32 til_build_header(Expr *ast, Str *h_path) {
    return build_header(ast, h_path);
}

I32 til_build_til_binding(Expr *ast, Str *til_path, Str *lib_name) {
    return build_til_binding(ast, til_path, lib_name);
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

void til_ast_print(Expr *ast, U32 indent) { ast_print(ast, indent); }

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

// Set operations (bridge for Str set)

Set *til_set_new(void) {
    Set *s = malloc(sizeof(Set));
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}); *s = *_sp; free(_sp); }
    return s;
}

Bool til_set_has(Set *s, Str *str) {
    return *Set_has(s, str);
}

void til_set_add(Set *s, Str *str) {
    // Clone: scavenger may free the original Str while the set still references it
    { Str *_p = Str_clone(str); Set_add(s, _p); }
}

void til_set_free(Set *s) {
    Set_delete(s, &(Bool){0});
    free(s);
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

