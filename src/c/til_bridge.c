// FFI bridge for til.til — thin wrappers around C module APIs.
// Converts Str* ↔ const char*, handles output params, provides Expr field accessors.

#include "ast.h"
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

// --- Tokenize/Parse wrappers (avoid output params) ---

static Vec *_tok_vec;
static Str *_parse_mode;

Token *til_tokenize(Str *source, Str *path) {
    // Clone inputs: tokenizer creates Str views (CAP_VIEW) into source buffer,
    // and parser stores path in AST nodes. The generated caller may free its
    // copies (scavenger inserts Str_delete), so the bridge must own persistent copies.
    _tok_vec = tokenize(Str_clone(source), Str_clone(path));
    return (Token *)_tok_vec->data;
}
U32 til_tok_count(void) { return _tok_vec ? _tok_vec->count : 0; }

Expr *til_parse(Token *tokens, U32 count, Str *path) {
    _parse_mode = NULL;
    // Clone path: parser stores Str* in Parser struct and propagates to AST nodes.
    return parse(tokens, count, Str_clone(path), &_parse_mode);
}
Str *til_parse_mode(void) { return _parse_mode ? Str_clone(_parse_mode) : Str_new(""); }

// --- Expr field accessors ---

Expr *expr_null(void) { return NULL; }
Bool expr_is_null(Expr *e) { return e == NULL; }
Bool Expr_eq(Expr *a, Expr *b) { return a == b; }
// NULL-safe: .and() chains in compiled til evaluate all operands eagerly
// (unlike C's && which short-circuits), so these may be called on NULL exprs
// or out-of-bounds indices when a prior condition would have been false.
I32 expr_get_tag(Expr *e) { return e ? (I32)e->type.tag : (I32)-1; }
Str *expr_get_str_val(Expr *e) {
    if (!e) return Str_new("");
    // str_val shares a union with decl/func_def — only valid for these node types
    switch (e->type.tag) {
    case NODE_IDENT: case NODE_LITERAL_STR: case NODE_LITERAL_NUM:
    case NODE_LITERAL_BOOL: case NODE_ASSIGN: case NODE_FOR_IN:
    case NODE_FIELD_ACCESS: case NODE_FIELD_ASSIGN: case NODE_NAMED_ARG:
        return e->type.str_val ? Str_clone(e->type.str_val) : Str_new("");
    default:
        return Str_new("");
    }
}
Expr *expr_get_child(Expr *e, U32 i) {
    if (!e || i >= e->children.count) return NULL;
    return expr_child(e, i);
}
U32 expr_nchildren(Expr *e) { return e ? e->children.count : 0; }
void expr_set_core(Expr *e) { e->is_core = true; }
void expr_push_child(Expr *e, Expr *child) { expr_add_child(e, child); }

// Replace children: old children are freed, new_children is moved in
void expr_swap_children(Expr *e, Vec *new_children) {
    Vec_delete(&e->children, &(Bool){0});
    e->children = *new_children;
    new_children->data = NULL;
    new_children->count = 0;
    new_children->cap = 0;
}

// Create new Vec for collecting Expr* (elem_size = sizeof(Expr*))
Vec *expr_vec_new(void) {
    Vec *v = malloc(sizeof(Vec));
    { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Expr *)}); *v = *_vp; free(_vp); }
    return v;
}

// Push an Expr* into a Vec
void expr_vec_push(Vec *v, Expr *e) {
    { Expr **_p = malloc(sizeof(Expr *)); *_p = e; Vec_push(v, _p); }
}

// Get Expr* from Vec at index i
Expr *expr_vec_get(Vec *v, U32 i) {
    return *(Expr **)Vec_get(v, &(U64){(U64)(i)});
}

U32 expr_vec_count(Vec *v) { return v->count; }

void expr_vec_pop(Vec *v) { v->count--; }

// --- Builder bridge: Expr field accessors ---

// Decl fields
Str *expr_decl_name(Expr *e) { return (e && e->type.tag == NODE_DECL) ? (e->type.decl.name ? Str_clone(e->type.decl.name) : Str_new("")) : Str_new(""); }
Str *expr_decl_explicit_type(Expr *e) { return (e && e->type.tag == NODE_DECL && e->type.decl.explicit_type) ? Str_clone(e->type.decl.explicit_type) : Str_new(""); }
Bool expr_decl_is_mut(Expr *e) { return e && e->type.tag == NODE_DECL && e->type.decl.is_mut; }
Bool expr_decl_is_ref(Expr *e) { return e && e->type.tag == NODE_DECL && e->type.decl.is_ref; }
Bool expr_decl_is_own(Expr *e) { return e && e->type.tag == NODE_DECL && e->type.decl.is_own; }
Bool expr_decl_is_namespace(Expr *e) { return e && e->type.tag == NODE_DECL && e->type.decl.is_namespace; }

// FuncDef fields
I32 expr_fdef_func_type(Expr *e) { return (e && e->type.tag == NODE_FUNC_DEF) ? (I32)e->type.func_def.func_type : -1; }
U32 expr_fdef_nparam(Expr *e) { return (e && e->type.tag == NODE_FUNC_DEF) ? e->type.func_def.nparam : 0; }
I32 expr_fdef_variadic_index(Expr *e) { return (e && e->type.tag == NODE_FUNC_DEF) ? e->type.func_def.variadic_index : -1; }
Str *expr_fdef_return_type(Expr *e) { return (e && e->type.tag == NODE_FUNC_DEF && e->type.func_def.return_type) ? Str_clone(e->type.func_def.return_type) : Str_new(""); }
Bool expr_fdef_return_is_ref(Expr *e) { return e && e->type.tag == NODE_FUNC_DEF && e->type.func_def.return_is_ref; }
Bool expr_fdef_return_is_shallow(Expr *e) { return e && e->type.tag == NODE_FUNC_DEF && e->type.func_def.return_is_shallow; }
Str *expr_fdef_param_name(Expr *e, U32 i) { return (e && e->type.tag == NODE_FUNC_DEF && i < e->type.func_def.nparam) ? Str_clone(e->type.func_def.param_names[i]) : Str_new(""); }
Str *expr_fdef_param_type(Expr *e, U32 i) { return (e && e->type.tag == NODE_FUNC_DEF && i < e->type.func_def.nparam && e->type.func_def.param_types) ? Str_clone(e->type.func_def.param_types[i]) : Str_new(""); }
Bool expr_fdef_param_is_mut(Expr *e, U32 i) { return e && e->type.tag == NODE_FUNC_DEF && i < e->type.func_def.nparam && e->type.func_def.param_muts && e->type.func_def.param_muts[i]; }
Bool expr_fdef_param_is_own(Expr *e, U32 i) { return e && e->type.tag == NODE_FUNC_DEF && i < e->type.func_def.nparam && e->type.func_def.param_owns && e->type.func_def.param_owns[i]; }
Bool expr_fdef_param_is_shallow(Expr *e, U32 i) { return e && e->type.tag == NODE_FUNC_DEF && i < e->type.func_def.nparam && e->type.func_def.param_shallows && e->type.func_def.param_shallows[i]; }

// Expr direct fields
I32 expr_til_type(Expr *e) { return e ? (I32)e->til_type : 0; }
Str *expr_struct_name(Expr *e) { return (e && e->struct_name) ? Str_clone(e->struct_name) : Str_new(""); }
Bool expr_is_own_arg(Expr *e) { return e && e->is_own_arg; }
Bool expr_is_own_field(Expr *e) { return e && e->is_own_field; }
Bool expr_is_ns_field(Expr *e) { return e && e->is_ns_field; }
Bool expr_is_ext_flag(Expr *e) { return e && e->is_ext; }
Bool expr_is_core_flag(Expr *e) { return e && e->is_core; }
Bool expr_save_old_delete(Expr *e) { return e && e->save_old_delete; }
I32 expr_variadic_index(Expr *e) { return e ? e->variadic_index : -1; }
U32 expr_variadic_count(Expr *e) { return e ? e->variadic_count : 0; }

// enum_has_payloads bridge
Bool expr_enum_has_payloads(Expr *e) { return enum_has_payloads(e); }

void expr_vec_free(Vec *v) {
    Vec_delete(v, &(Bool){0});
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

Str *til_mode_name(const Mode *m) { return Str_new(m ? m->name : ""); }
Str *til_mode_auto_import(const Mode *m) {
    return Str_new(m && m->auto_import ? m->auto_import : "");
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
    // Convert empty strings to NULL (C code uses NULL checks, til passes "")
    if (user_c && user_c->count == 0) user_c = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
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

// build, build_header, build_til_binding, compile_c, compile_lib
// are now provided by builder.til (imported by til.til) instead of C bridges.
// ctil still uses builder.c directly (via ctil.c).

void til_ast_print(Expr *ast, U32 indent) { ast_print(ast, indent); }
void til_expr_free(Expr *ast) { expr_free(ast); }

// --- Utility wrappers ---

// Return owned copy of first n bytes of s (avoids CAP_VIEW + scavenger ordering issues)
Str *til_str_left(Str *s, U64 n) {
    if (!s || n == 0) return Str_new("");
    U64 len = (U64)s->count;
    if (n > len) n = len;
    char *buf = malloc(n + 1);
    memcpy(buf, s->c_str, n);
    buf[n] = '\0';
    Str *result = Str_new(buf);
    free(buf);
    return result;
}

Str *til_realpath(Str *path) {
    char *abs = realpath((const char *)path->c_str, NULL);
    if (!abs) return Str_new("");
    Str *s = Str_new(abs);
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
    { Set *_sp = Set_new(Str_new("Str"), &(U64){sizeof(Str)}); *s = *_sp; free(_sp); }
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

// --- Builder Map bridges ---

// Expr-valued map (Str key → Expr* value): struct_bodies, func_defs
Map *expr_map_new(void) {
    Map *m = malloc(sizeof(Map));
    Map *_mp = Map_new(Str_new("Str"), &(U64){sizeof(Str)}, Str_new(""), &(U64){sizeof(Expr *)});
    *m = *_mp; free(_mp);
    return m;
}

void expr_map_set(Map *m, Str *key, Expr *val) {
    Str *_k = Str_clone(key);
    void *_v = malloc(sizeof(Expr *));
    memcpy(_v, &val, sizeof(Expr *));
    Map_set(m, _k, _v);
}

Bool expr_map_has(Map *m, Str *key) {
    return *Map_has(m, key);
}

Expr *expr_map_get(Map *m, Str *key) {
    if (!*Map_has(m, key)) return NULL;
    Expr **p = Map_get(m, key);
    return *p;
}

void expr_map_free(Map *m) {
    Map_delete(m, &(Bool){0});
    free(m);
}

// Str-valued map (Str key → Str* value): shallow_local_types
Map *str_map_new(void) {
    Map *m = malloc(sizeof(Map));
    Map *_mp = Map_new(Str_new("Str"), &(U64){sizeof(Str)}, Str_new(""), &(U64){sizeof(Str *)});
    *m = *_mp; free(_mp);
    return m;
}

void str_map_set(Map *m, Str *key, Str *val) {
    Str *_k = Str_clone(key);
    Str *_vc = Str_clone(val);
    void *_v = malloc(sizeof(Str *));
    memcpy(_v, &_vc, sizeof(Str *));
    Map_set(m, _k, _v);
}

Bool str_map_has(Map *m, Str *key) {
    return *Map_has(m, key);
}

Str *str_map_get(Map *m, Str *key) {
    if (!*Map_has(m, key)) return Str_new("");
    Str **p = Map_get(m, key);
    return Str_clone(*p);
}

void str_map_free(Map *m) {
    Map_delete(m, &(Bool){0});
    free(m);
}

// Mode field accessors
Bool til_mode_needs_main(const Mode *m) { return m && m->needs_main; }
Bool til_mode_decls_only(const Mode *m) { return m && m->decls_only; }

// Derive project root by searching upward from binary location for src/core/core.til
Str *til_bin_dir(void) {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return Str_new(".");
    buf[len] = '\0';
    // Strip binary name
    char *slash = strrchr(buf, '/');
    if (slash) *slash = '\0';
    // Search upward for src/core/core.til
    for (int i = 0; i < 5; i++) {
        char test[PATH_MAX + 32];
        snprintf(test, sizeof(test), "%s/src/core/core.til", buf);
        if (access(test, F_OK) == 0) return Str_new(buf);
        slash = strrchr(buf, '/');
        if (!slash) break;
        *slash = '\0';
    }
    return Str_new(".");
}

// til_prepare: exposed for self-hosting (til.til can call the C version)
// When compiled as part of ctil, til_prepare is defined in ctil.c.
// When compiled standalone (e.g. til.til compiled binary), it may not exist.
extern Expr *til_prepare(Str *path, Str *bin_dir) __attribute__((weak));
Expr *til_prepare_s(Str *path, Str *bin_dir) {
    if (til_prepare) return til_prepare(path, bin_dir);
    return NULL;
}
