#ifndef MAP_H
#define MAP_H

#include "str.h"
#include "vec.h"

typedef int (*CmpFn)(const void *a, const void *b);

typedef struct {
    Vec keys;
    Vec vals;
    CmpFn cmp;
} Map;

Map   Map_new(int key_size, int val_size, CmpFn cmp);
void *Map_get(Map *m, const void *key);
void  Map_set(Map *m, const void *key, const void *val);
int   Map_has(Map *m, const void *key);
int   Map_len(Map *m);
void  Map_delete(Map *m);

typedef struct {
    Vec data;
    CmpFn cmp;
} Set;

Set  Set_new(int elem_size, CmpFn cmp);
int  Set_has(Set *s, const void *elem);
void Set_add(Set *s, const void *elem);
int  Set_len(Set *s);
void Set_delete(Set *s);

int str_ptr_cmp(const void *a, const void *b);

#endif
