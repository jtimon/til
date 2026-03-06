#ifndef MAP_H
#define MAP_H

#include "str.h"
#include "vec.h"

typedef I32 (*CmpFn)(const void *a, const void *b);

typedef struct {
    Vec keys;
    Vec vals;
    CmpFn cmp;
} Map;

Map   Map_new(I32 key_size, I32 val_size, CmpFn cmp);
void *Map_get(Map *m, const void *key);
void  Map_set(Map *m, const void *key, const void *val);
Bool  Map_has(Map *m, const void *key);
I32   Map_len(Map *m);
void  Map_delete(Map *m);

typedef struct {
    Vec data;
    CmpFn cmp;
} Set;

Set  Set_new(I32 elem_size, CmpFn cmp);
Bool Set_has(Set *s, const void *elem);
void Set_add(Set *s, const void *elem);
I32  Set_len(Set *s);
void Set_delete(Set *s);

I32 str_ptr_cmp(const void *a, const void *b);

#endif
