#include "map.h"
#include <stdlib.h>
#include <string.h>

// Generic binary search over sorted void* array with comparator.
static int sorted_find_generic(void *data, int len, int elem_size,
                               CmpFn cmp, const void *elem, int *found) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int c = cmp((char *)data + mid * elem_size, elem);
        if (c < 0) lo = mid + 1;
        else if (c > 0) hi = mid;
        else { *found = 1; return mid; }
    }
    *found = 0;
    return lo;
}

Map Map_new(int key_size, int val_size, CmpFn cmp) {
    return (Map){.keys = Vec_new(key_size), .vals = Vec_new(val_size), .cmp = cmp};
}

void *Map_get(Map *m, const void *key) {
    int found;
    int i = sorted_find_generic(m->keys.data, m->keys.count, m->keys.elem_size,
                                m->cmp, key, &found);
    if (!found) return NULL;
    return (char *)m->vals.data + i * m->vals.elem_size;
}

void Map_set(Map *m, const void *key, const void *val) {
    int found;
    int ks = m->keys.elem_size;
    int vs = m->vals.elem_size;
    int i = sorted_find_generic(m->keys.data, m->keys.count, ks,
                                m->cmp, key, &found);
    if (found) {
        memcpy((char *)m->vals.data + i * vs, val, vs);
        return;
    }
    // Grow if needed
    if (m->keys.count >= m->keys.cap) {
        int newcap = m->keys.cap ? m->keys.cap * 2 : 16;
        m->keys.cap = newcap;
        m->keys.data = realloc(m->keys.data, newcap * ks);
        m->vals.cap = newcap;
        m->vals.data = realloc(m->vals.data, newcap * vs);
    }
    int n = m->keys.count;
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

int Map_has(Map *m, const void *key) {
    int found;
    sorted_find_generic(m->keys.data, m->keys.count, m->keys.elem_size,
                        m->cmp, key, &found);
    return found;
}

int Map_len(Map *m) {
    return m->keys.count;
}

void Map_delete(Map *m) {
    Vec_delete(&m->keys);
    Vec_delete(&m->vals);
}

Set Set_new(int elem_size, CmpFn cmp) {
    return (Set){.data = Vec_new(elem_size), .cmp = cmp};
}

int Set_has(Set *s, const void *elem) {
    int found;
    sorted_find_generic(s->data.data, s->data.count, s->data.elem_size,
                        s->cmp, elem, &found);
    return found;
}

void Set_add(Set *s, const void *elem) {
    int found;
    int es = s->data.elem_size;
    int i = sorted_find_generic(s->data.data, s->data.count, es,
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

int Set_len(Set *s) {
    return s->data.count;
}

void Set_delete(Set *s) {
    Vec_delete(&s->data);
}

int str_ptr_cmp(const void *a, const void *b) {
    Str *sa = *(Str *const *)a;
    Str *sb = *(Str *const *)b;
    return Str_cmp(sa, sb);
}
