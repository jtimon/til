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

#define Vec_push_val(v, val) do { __typeof__(val) _tmp = (val); Vec_push((v), &_tmp); } while(0)
#define Vec_get_T(T, v, i)  (*(T *)Vec_get((v), (i)))
#define Vec_last_T(T, v)    (*(T *)Vec_last((v)))

#endif
