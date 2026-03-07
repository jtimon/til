#ifndef VEC_H
#define VEC_H

#include "aliases.h"
#include <stdlib.h>

typedef struct {
    void *data;
    U32 count;
    U32 cap;
    I32 elem_size;
} Vec;

Vec   Vec_new(I32 elem_size);
void  Vec_push(Vec *v, const void *elem);
void *Vec_get(Vec *v, U32 i);
void *Vec_last(Vec *v);
U32   Vec_len(Vec *v);
void  Vec_delete(Vec *v);
void *Vec_take(Vec *v);

#endif
