#ifndef MAP_H
#define MAP_H

#include "ccore.h"

typedef struct {
    Str **keys;
    void *vals;
    int len;
    int cap;
    int elem_size;
} Map;

Map   Map_new(int elem_size);
void *Map_get(Map *m, Str *key);
void  Map_set(Map *m, Str *key, const void *val);
int   Map_has(Map *m, Str *key);
int   Map_len(Map *m);
void  Map_free(Map *m);

#endif
