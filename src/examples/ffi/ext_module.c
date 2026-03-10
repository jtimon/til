#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Top-level ext functions

Str *greet(Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    Str *result = malloc(sizeof(Str));
    result->count = hello_len + name->count;
    result->cap = result->count;
    result->c_str = malloc(result->count);
    memcpy(result->c_str, hello, hello_len);
    memcpy(result->c_str + hello_len, name->c_str, name->count);
    return result;
}

void greet_print(Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    fwrite(hello, 1, hello_len, stdout);
    fwrite(name->c_str, 1, name->count, stdout);
    putchar('\n');
}

// Regular struct used as ext_func arg/return
typedef struct { I64 x; I64 y; } Point;

Point *add_points(Point *a, Point *b) {
    Point *r = malloc(sizeof(Point));
    r->x = a->x + b->x;
    r->y = a->y + b->y;
    return r;
}

// Variadic ext_func: sum all I64 args
I64 *sum_all(Array *args) {
    I64 *r = malloc(sizeof(I64));
    *r = 0;
    for (U64 i = 0; i < args->cap; i++) {
        I64 *elem = (I64 *)Array_elem(args, i);
        *r += *elem;
    }
    return r;
}

// ext_struct: Pair

typedef struct { I64 a; I64 b; } Pair;

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
