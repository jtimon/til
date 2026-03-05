#include "ext.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(til_I64 *code) { exit((int)*code); }

Str *til_I64_to_str(til_I64 *v) { return I64_to_str(*v); }

Str *til_U8_to_str(til_U8 *v) { return U8_to_str(*v); }

til_Bool *til_Str_eq(Str *a, Str *b) {
    til_Bool *r = malloc(sizeof(til_Bool));
    *r = Str_eq(a, b);
    return r;
}
Str *til_Str_concat(Str *a, Str *b) { return Str_concat(a, b); }
Str *til_Str_clone(Str *s) { return Str_clone(s); }
void til_Str_delete(Str *s, til_Bool *call_free) {
    if (*call_free) Str_delete(s);
    else free(s->c_str); // field context: free string data but not the struct
}
Str *til_Str_to_str(Str *s) { return Str_clone(s); }
til_I64 *til_Str_len(Str *s) { til_I64 *r = malloc(sizeof(til_I64)); *r = Str_len(s); return r; }
Str *til_Str_substr(Str *s, til_I64 *start, til_I64 *n) { return Str_substr(s, (int)*start, (int)*n); }
til_Bool *til_Str_contains(Str *a, Str *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = Str_contains(a, b); return r; }
til_Bool *til_Str_starts_with(Str *a, Str *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = Str_starts_with(a, b); return r; }
til_Bool *til_Str_ends_with(Str *a, Str *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = Str_ends_with(a, b); return r; }

// I64 clone/delete
til_I64 *til_I64_clone(til_I64 *v) { return I64_clone(v); }
void til_I64_delete(til_I64 *v, til_Bool *call_free) { if (*call_free) I64_delete(v); }

// I64 arithmetic
til_I64 *til_I64_add(til_I64 *a, til_I64 *b) { return I64_new(I64_add(*a, *b)); }
til_I64 *til_I64_sub(til_I64 *a, til_I64 *b) { return I64_new(I64_sub(*a, *b)); }
til_I64 *til_I64_mul(til_I64 *a, til_I64 *b) { return I64_new(I64_mul(*a, *b)); }
til_I64 *til_I64_div(til_I64 *a, til_I64 *b) { return I64_new(I64_div(*a, *b)); }
til_I64 *til_I64_mod(til_I64 *a, til_I64 *b) { return I64_new(I64_mod(*a, *b)); }
til_I64 *til_I64_and(til_I64 *a, til_I64 *b) { return I64_new(I64_and(*a, *b)); }
til_I64 *til_I64_or(til_I64 *a, til_I64 *b) { return I64_new(I64_or(*a, *b)); }
til_I64 *til_I64_xor(til_I64 *a, til_I64 *b) { return I64_new(I64_xor(*a, *b)); }

// I64 comparisons
til_Bool *til_I64_eq(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_eq(*a, *b); return r; }
til_Bool *til_I64_lt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_lt(*a, *b); return r; }
til_Bool *til_I64_gt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_gt(*a, *b); return r; }

// U8 arithmetic
til_U8 *til_U8_add(til_U8 *a, til_U8 *b) { return U8_new(U8_add(*a, *b)); }
til_U8 *til_U8_sub(til_U8 *a, til_U8 *b) { return U8_new(U8_sub(*a, *b)); }
til_U8 *til_U8_mul(til_U8 *a, til_U8 *b) { return U8_new(U8_mul(*a, *b)); }
til_U8 *til_U8_div(til_U8 *a, til_U8 *b) { return U8_new(U8_div(*a, *b)); }
til_U8 *til_U8_mod(til_U8 *a, til_U8 *b) { return U8_new(U8_mod(*a, *b)); }
til_U8 *til_U8_and(til_U8 *a, til_U8 *b) { return U8_new(U8_and(*a, *b)); }
til_U8 *til_U8_or(til_U8 *a, til_U8 *b) { return U8_new(U8_or(*a, *b)); }
til_U8 *til_U8_xor(til_U8 *a, til_U8 *b) { return U8_new(U8_xor(*a, *b)); }

// U8 comparisons
til_Bool *til_U8_eq(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_eq(*a, *b); return r; }
til_Bool *til_U8_lt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_lt(*a, *b); return r; }
til_Bool *til_U8_gt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_gt(*a, *b); return r; }

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a) { return I64_new(U8_to_i64(*a)); }
til_U8 *til_U8_from_i64_ext(til_I64 *a) { return U8_new(U8_from_i64(*a)); }

// U8 clone/delete
til_U8 *til_U8_clone(til_U8 *v) { return U8_clone(v); }
void til_U8_delete(til_U8 *v, til_Bool *call_free) { if (*call_free) U8_delete(v); }

// Bool ops
til_Bool *til_Bool_and(til_Bool *a, til_Bool *b) { return Bool_new(Bool_and(*a, *b)); }
til_Bool *til_Bool_or(til_Bool *a, til_Bool *b) { return Bool_new(Bool_or(*a, *b)); }
til_Bool *til_Bool_not(til_Bool *a) { return Bool_new(Bool_not(*a)); }

// Bool clone/delete
til_Bool *til_Bool_clone(til_Bool *v) { return Bool_clone(v); }
void til_Bool_delete(til_Bool *v, til_Bool *call_free) { if (*call_free) Bool_delete(v); }

// ext_struct: Pair (test)
til_I64 *til_Pair_sum(til_Pair *self) {
    til_I64 *r = malloc(sizeof(til_I64));
    *r = self->a + self->b;
    return r;
}
til_Pair *til_Pair_swap(til_Pair *self) {
    til_Pair *r = malloc(sizeof(til_Pair));
    r->a = self->b;
    r->b = self->a;
    return r;
}
til_Pair *til_Pair_clone(til_Pair *self) {
    til_Pair *r = malloc(sizeof(til_Pair));
    *r = *self;
    return r;
}
void til_Pair_delete(til_Pair *self, til_Bool *call_free) {
    if (*call_free) free(self);
}

// Pointer primitives
void *til_malloc(til_I64 *count) { return calloc(1, (size_t)*count); }
void *til_realloc(void *buf, til_I64 *count) { return realloc(buf, (size_t)*count); }
void *til_ptr_at(void *buf, til_I64 *offset) {
    return *(void **)((char *)buf + *offset);
}
void til_ptr_set(void *buf, til_I64 *offset, void *val) {
    void **slot = (void **)((char *)buf + *offset);
    *slot = val;
}

// Variadic builtins
Str *til_format(int n, ...) {
    va_list ap; va_start(ap, n);
    Str *strs[64];
    int total = 0;
    for (int i = 0; i < n; i++) { strs[i] = va_arg(ap, Str *); total += strs[i]->cap; }
    va_end(ap);
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(total + 1);
    s->cap = total;
    int off = 0;
    for (int i = 0; i < n; i++) { memcpy(s->c_str + off, strs[i]->c_str, strs[i]->cap); off += strs[i]->cap; }
    s->c_str[off] = '\0';
    return s;
}

void til_println(int n, ...) {
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n; i++) { Str *s = va_arg(ap, Str *); printf("%s", s->c_str); }
    va_end(ap);
    printf("\n");
}

void til_print(int n, ...) {
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n; i++) { Str *s = va_arg(ap, Str *); printf("%s", s->c_str); }
    va_end(ap);
}
