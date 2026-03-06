#include "map.h"
#include <stdlib.h>
#include <string.h>

// Generic binary search over sorted void* array with comparator.
static I32 sorted_find_generic(void *data, I32 len, I32 elem_size,
                               CmpFn cmp, const void *elem, Bool *found) {
    I32 lo = 0, hi = len;
    while (lo < hi) {
        I32 mid = lo + (hi - lo) / 2;
        I32 c = cmp((char *)data + mid * elem_size, elem);
        if (c < 0) lo = mid + 1;
        else if (c > 0) hi = mid;
        else { *found = 1; return mid; }
    }
    *found = 0;
    return lo;
}

Map Map_new(I32 key_size, I32 val_size, CmpFn cmp) {
    return (Map){.keys = Vec_new(key_size), .vals = Vec_new(val_size), .cmp = cmp};
}

void *Map_get(Map *m, const void *key) {
    Bool found;
    I32 i = sorted_find_generic(m->keys.data, m->keys.count, m->keys.elem_size,
                                m->cmp, key, &found);
    if (!found) return NULL;
    return (char *)m->vals.data + i * m->vals.elem_size;
}

void Map_set(Map *m, const void *key, const void *val) {
    Bool found;
    I32 ks = m->keys.elem_size;
    I32 vs = m->vals.elem_size;
    I32 i = sorted_find_generic(m->keys.data, m->keys.count, ks,
                                m->cmp, key, &found);
    if (found) {
        memcpy((char *)m->vals.data + i * vs, val, vs);
        return;
    }
    // Grow if needed
    if (m->keys.count >= m->keys.cap) {
        I32 newcap = m->keys.cap ? m->keys.cap * 2 : 16;
        m->keys.cap = newcap;
        m->keys.data = realloc(m->keys.data, newcap * ks);
        m->vals.cap = newcap;
        m->vals.data = realloc(m->vals.data, newcap * vs);
    }
    I32 n = m->keys.count;
    // Shift right and insert at sorted position
    memmove((char *)m->keys.data + (i + 1) * ks,
            (char *)m->keys.data + i * ks, (n - i) * ks);
    memmove((char *)m->vals.data + (i + 1) * vs,
            (char *)m->vals.data + i * vs, (n - i) * vs);
    memcpy((char *)m->keys.data + i * ks, key, ks);
    memcpy((char *)m->vals.data + i * vs, val, vs);
    m->keys.count++;
    m->vals.count++;
}

Bool Map_has(Map *m, const void *key) {
    Bool found;
    sorted_find_generic(m->keys.data, m->keys.count, m->keys.elem_size,
                        m->cmp, key, &found);
    return found;
}

I32 Map_len(Map *m) {
    return m->keys.count;
}

void Map_delete(Map *m) {
    Vec_delete(&m->keys);
    Vec_delete(&m->vals);
}

Set Set_new(I32 elem_size, CmpFn cmp) {
    return (Set){.data = Vec_new(elem_size), .cmp = cmp};
}

Bool Set_has(Set *s, const void *elem) {
    Bool found;
    sorted_find_generic(s->data.data, s->data.count, s->data.elem_size,
                        s->cmp, elem, &found);
    return found;
}

void Set_add(Set *s, const void *elem) {
    Bool found;
    I32 es = s->data.elem_size;
    I32 i = sorted_find_generic(s->data.data, s->data.count, es,
                                s->cmp, elem, &found);
    if (found) return;
    // Grow if needed
    if (s->data.count >= s->data.cap) {
        s->data.cap = s->data.cap ? s->data.cap * 2 : 16;
        s->data.data = realloc(s->data.data, s->data.cap * es);
    }
    // Shift right and insert at sorted position
    memmove((char *)s->data.data + (i + 1) * es,
            (char *)s->data.data + i * es,
            (s->data.count - i) * es);
    memcpy((char *)s->data.data + i * es, elem, es);
    s->data.count++;
}

I32 Set_len(Set *s) {
    return s->data.count;
}

void Set_delete(Set *s) {
    Vec_delete(&s->data);
}

I32 str_ptr_cmp(const void *a, const void *b) {
    Str *sa = *(Str *const *)a;
    Str *sb = *(Str *const *)b;
    return Str_cmp(sa, sb);
}
