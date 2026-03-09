// FFI bridge for til.til — thin wrappers around C module APIs.
// Converts Str* ↔ const char*, handles output params, provides Expr field accessors.

#include "ast.h"
#include "lexer.h"
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

// --- Tokenize/Parse wrappers (avoid output params) ---

static U32 _tok_count;
static Str *_parse_mode;

Token *til_tokenize(Str *source, Str *path) {
    return tokenize(source->c_str, path, &_tok_count);
}
U32 til_tok_count(void) { return _tok_count; }

Expr *til_parse(Token *tokens, U32 count, Str *path) {
    _parse_mode = NULL;
    return parse(tokens, count, path, &_parse_mode);
}
Str *til_parse_mode(void) { return _parse_mode; }

// --- Expr field accessors ---

Expr *expr_null(void) { return NULL; }
Bool expr_is_null(Expr *e) { return e == NULL; }
Bool Expr_eq(Expr *a, Expr *b) { return a == b; }
I32 expr_get_tag(Expr *e) { return (I32)e->type.tag; }
Str *expr_get_str_val(Expr *e) { return e->type.str_val; }
Expr *expr_get_child(Expr *e, U32 i) { return expr_child(e, i); }
U32 expr_nchildren(Expr *e) { return e->children.count; }
void expr_set_core(Expr *e) { e->is_core = true; }
void expr_push_child(Expr *e, Expr *child) { expr_add_child(e, child); }

// Replace children: old children are freed, new_children is moved in
void expr_swap_children(Expr *e, Vec *new_children) {
    Vec_delete(&e->children);
    e->children = *new_children;
    new_children->data = NULL;
    new_children->count = 0;
    new_children->cap = 0;
}

// Create new Vec for collecting Expr* (elem_size = sizeof(Expr*))
Vec *expr_vec_new(void) {
    Vec *v = malloc(sizeof(Vec));
    *v = Vec_new(sizeof(Expr *));
    return v;
}

// Push an Expr* into a Vec
void expr_vec_push(Vec *v, Expr *e) {
    Vec_push(v, &e);
}

// Get Expr* from Vec at index i
Expr *expr_vec_get(Vec *v, U32 i) {
    return *(Expr **)Vec_get(v, i);
}

U32 expr_vec_count(Vec *v) { return v->count; }

void expr_vec_pop(Vec *v) { v->count--; }

void expr_vec_free(Vec *v) {
    Vec_delete(v);
    free(v);
}

// --- Mode helpers ---

const Mode *til_mode_resolve(Str *name) {
    if (!name) return NULL;
    if (Str_eq_c(name, "script")) return &MODE_SCRIPT;
    if (Str_eq_c(name, "cli"))    return &MODE_CLI;
    if (Str_eq_c(name, "gui"))    return &MODE_GUI;
    if (Str_eq_c(name, "test"))   return &MODE_TEST;
    if (Str_eq_c(name, "pure"))   return &MODE_PURE;
    if (Str_eq_c(name, "pura"))   return &MODE_PURA;
    if (Str_eq_c(name, "lib"))    return &MODE_LIB;
    if (Str_eq_c(name, "liba"))   return &MODE_LIBA;
    return NULL;
}

Bool til_mode_eq(const Mode *a, const Mode *b) { return a == b; }
Bool Mode_eq(const Mode *a, const Mode *b) { return a == b; }

const Mode *til_mode_none(void)   { return NULL; }
const Mode *til_mode_script(void) { return &MODE_SCRIPT; }
const Mode *til_mode_cli(void)    { return &MODE_CLI; }
const Mode *til_mode_gui(void)    { return &MODE_GUI; }
const Mode *til_mode_test(void)   { return &MODE_TEST; }
const Mode *til_mode_pure(void)   { return &MODE_PURE; }
const Mode *til_mode_pura(void)   { return &MODE_PURA; }
const Mode *til_mode_lib(void)    { return &MODE_LIB; }
const Mode *til_mode_liba(void)   { return &MODE_LIBA; }

Str *til_mode_name(const Mode *m) { return m ? Str_new(m->name) : NULL; }
Str *til_mode_auto_import(const Mode *m) {
    return m && m->auto_import ? Str_new(m->auto_import) : NULL;
}

Bool til_mode_is_lib(const Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA);
}
Bool til_mode_is_lib_output(const Mode *m) {
    return m && (m == &MODE_LIB || m == &MODE_LIBA ||
                 m == &MODE_PURE || m == &MODE_PURA);
}

// --- Pipeline wrappers ---

I32 til_init_declarations(Expr *program, TypeScope *scope) {
    return init_declarations(program, scope);
}

I32 til_type_check(Expr *program, TypeScope *scope, const Mode *mode) {
    return type_check(program, scope, mode);
}

void til_precomp(Expr *program) { precomp(program); }

void til_scavenge(Expr *program, const Mode *mode, Bool run_tests) {
    scavenge(program, mode, run_tests);
}

I32 til_interpret(Expr *ast, const Mode *mode, Bool run_tests,
                  Str *path, Str *user_c, Str *ext_c, Str *link_flags,
                  U32 user_argc, Str **user_argv) {
    // Convert Str** to char**
    char **argv = NULL;
    if (user_argc > 0 && user_argv) {
        argv = malloc(user_argc * sizeof(char *));
        for (U32 i = 0; i < user_argc; i++)
            argv[i] = (char *)user_argv[i]->c_str;
    }
    I32 r = interpret(ast, mode, run_tests, path, user_c, ext_c, link_flags,
                      user_argc, argv);
    free(argv);
    return r;
}

I32 til_build(Expr *ast, const Mode *mode, Bool run_tests,
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
    return compile_c(c_path, bin_path, ext_c, user_c, lflags);
}

I32 til_compile_lib(Str *c_path, Str *lib_name, Str *ext_c, Str *user_c, Str *lflags) {
    return compile_lib(c_path, lib_name, ext_c, user_c, lflags);
}

void til_ast_print(Expr *ast, U32 indent) { ast_print(ast, indent); }
void til_expr_free(Expr *ast) { expr_free(ast); }

// --- Utility wrappers ---

Str *til_realpath(Str *path) {
    char *abs = realpath(path->c_str, NULL);
    if (!abs) return NULL;
    Str *s = Str_new(abs);
    free(abs);
    return s;
}

I32 til_system(Str *cmd) {
    return system(cmd->c_str);
}

// Set operations (bridge for Str* set, using str_ptr_cmp from ccore)
extern I32 str_ptr_cmp(const void *a, const void *b);

Set *til_set_new(void) {
    Set *s = malloc(sizeof(Set));
    *s = Set_new(sizeof(Str *), str_ptr_cmp);
    return s;
}

Bool til_set_has(Set *s, Str *str) {
    return Set_has(s, &str);
}

void til_set_add(Set *s, Str *str) {
    Set_add(s, &str);
}

void til_set_free(Set *s) {
    Set_delete(s);
    free(s);
}

// til_prepare: exposed for self-hosting (til.til can call the C version)
// When compiled as part of ctil, til_prepare is defined in ctil.c.
// When compiled standalone (e.g. til.til compiled binary), it may not exist.
extern Expr *til_prepare(Str *path, Str *bin_dir) __attribute__((weak));
Expr *til_prepare_s(Str *path, Str *bin_dir) {
    if (til_prepare) return til_prepare(path, bin_dir);
    return NULL;
}
