#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ext_module_forward.h is force-included by the builder. Namespace data must
// be declared there with its flattened C name and source type.
_Static_assert(sizeof(Pair_answer) == sizeof(I64), "Pair.answer declaration missing or mistyped");
_Static_assert(sizeof(Pair_forward) == sizeof(I64), "Pair.forward declaration missing or mistyped");

// Top-level ext functions

Str *greet(Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    Str *result = malloc(sizeof(Str));
    result->count = hello_len + name->count;
    result->cap = result->count;
    // Own pointer fields go through ext.h's accessors: under --cptr=32 they
    // hold 32-bit cage offsets, not pointers (issue #313).
    I8 *bytes = malloc(result->count);
    memcpy(bytes, hello, hello_len);
    memcpy(bytes + hello_len, TIL_OWN_GET(I8, name->c_str), name->count);
    TIL_OWN_SET(result->c_str, bytes);
    return result;
}

void greet_print(Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    fwrite(hello, 1, hello_len, stdout);
    fwrite(TIL_OWN_GET(I8, name->c_str), 1, name->count, stdout);
    putchar('\n');
}

// Point struct defined by til (available via forward.h -include)
Point *add_points(Point *a, Point *b) {
    Point *r = malloc(sizeof(Point));
    r->x = a->x + b->x;
    r->y = a->y + b->y;
    return r;
}

// Variadic ext_func: sum all I64 args
I64 *sum_all(Array__I64 *args) {
    I64 *r = malloc(sizeof(I64));
    *r = 0;
    for (U64 i = 0; i < args->cap; i++) {
        I64 *elem = (I64 *)(TIL_OWN_GET(U8, args->data) + i * sizeof(I64));
        *r += *elem;
    }
    return r;
}

// ext_struct: Pair

// Pair struct defined by til (available via forward.h -include)
I64 *Pair_sum(Pair *self) {
    I64 *r = malloc(sizeof(I64));
    *r = self->a + self->b;
    return r;
}

Pair *Pair_swap(Pair *self) {
    Pair *r = malloc(sizeof(Pair));
    r->a = self->b;
    r->b = self->a;
    return r;
}

Pair *Pair_clone(Pair *self) {
    Pair *r = malloc(sizeof(Pair));
    *r = *self;
    return r;
}

void Pair_delete(Pair *self, Bool *call_free) {
    if (*call_free) free(self);
}
