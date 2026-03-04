#ifndef VEC_H
#define VEC_H

#include <stdlib.h>

typedef struct {
    void *data;
    int len;
    int cap;
    int elem_size;
} Vec;

Vec   Vec_new(int elem_size);
void  Vec_push(Vec *v, const void *elem);
void *Vec_get(Vec *v, int i);
void *Vec_last(Vec *v);
int   Vec_len(Vec *v);
void  Vec_delete(Vec *v);
void *Vec_take(Vec *v);

#endif
