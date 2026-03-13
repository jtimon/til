#include "compat.h"
#include "ast.h"
#include "initer.h"
#include "modes.h"
#include <stdlib.h>
#include <string.h>

// --- Compiler-only Str helpers ---

Str Str_val(const char *data) {
    U64 len = (U64)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = (U8 *)copy, .count = len, .cap = len};
}

Str *Str_new(const char *data) {
    U64 len = (U64)strlen(data);
    return Str_new_len(data, len);
}

Str *Str_new_len(const char *data, U64 len) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, data, len);
    s->c_str[len] = '\0';
    s->count = len;
    s->cap = len;
    return s;
}

Bool Str_eq_c(Str *a, const char *b) {
    U64 blen = (U64)strlen(b);
    if (a->count != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

// --- Compiler-only Vec helpers ---

void *Vec_last(Vec *v) {
    return (char *)v->data + (v->count - 1) * v->elem_size;
}

void *Vec_take(Vec *v) {
    void *ptr = v->data;
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
    return ptr;
}

// --- Opaque type no-ops (for ext_struct FFI) ---
// Token_clone/Token_delete defined in bootstrap/lexer.c

Expr *Expr_clone(Expr *e) { return e; }
void Expr_delete(Expr *e, Bool *call_free) { (void)e; (void)call_free; }
TypeScope *TypeScope_clone(TypeScope *s) { return s; }
void TypeScope_delete(TypeScope *s, Bool *call_free) { (void)s; (void)call_free; }
Mode *Mode_clone(Mode *m) { return m; }
void Mode_delete(Mode *m, Bool *call_free) { (void)m; (void)call_free; }
