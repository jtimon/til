#include "vec.h"
#include <string.h>

Vec Vec_new(int elem_size) {
    return (Vec){.data = NULL, .count = 0, .cap = 0, .elem_size = elem_size};
}

void Vec_push(Vec *v, const void *elem) {
    if (v->count >= v->cap) {
        v->cap = v->cap ? v->cap * 2 : 64;
        v->data = realloc(v->data, v->cap * v->elem_size);
    }
    memcpy((char *)v->data + v->count * v->elem_size, elem, v->elem_size);
    v->count++;
}

void *Vec_get(Vec *v, int i) {
    return (char *)v->data + i * v->elem_size;
}

void *Vec_last(Vec *v) {
    return (char *)v->data + (v->count - 1) * v->elem_size;
}

int Vec_len(Vec *v) {
    return v->count;
}

void Vec_delete(Vec *v) {
    free(v->data);
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
}

void *Vec_take(Vec *v) {
    void *ptr = v->data;
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
    return ptr;
}
