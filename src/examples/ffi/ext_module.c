#include "ccore.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Top-level ext functions

til_Str *til_greet(til_Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    til_Str *result = malloc(sizeof(til_Str));
    result->cap = hello_len + name->cap;
    result->data = malloc(result->cap);
    memcpy(result->data, hello, hello_len);
    memcpy(result->data + hello_len, name->data, name->cap);
    return result;
}

void til_greet_print(til_Str *name) {
    const char *hello = "hello ";
    int hello_len = 6;
    fwrite(hello, 1, hello_len, stdout);
    fwrite(name->data, 1, name->cap, stdout);
    putchar('\n');
}

// Regular struct used as ext_func arg/return
typedef struct { til_I64 x; til_I64 y; } til_Point;

til_Point *til_add_points(til_Point *a, til_Point *b) {
    til_Point *r = malloc(sizeof(til_Point));
    r->x = a->x + b->x;
    r->y = a->y + b->y;
    return r;
}

// ext_struct: Pair

typedef struct { til_I64 a; til_I64 b; } til_Pair;

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
