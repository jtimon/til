#include "map.h"
#include <stdlib.h>
#include <string.h>

Map Map_new(int elem_size) {
    return (Map){.keys = NULL, .vals = NULL, .len = 0, .cap = 0, .elem_size = elem_size};
}

// Binary search over sorted Str* array: returns index where key is or
// should be inserted. Sets *found to 1 if key exists, 0 if not.
static int sorted_find(Str **keys, int len, Str *key, int *found) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = strcmp(keys[mid]->c_str, key->c_str);
        if (cmp < 0) lo = mid + 1;
        else if (cmp > 0) hi = mid;
        else { *found = 1; return mid; }
    }
    *found = 0;
    return lo;
}

void *Map_get(Map *m, Str *key) {
    int found;
    int i = sorted_find(m->keys, m->len, key, &found);
    if (!found) return NULL;
    return (char *)m->vals + i * m->elem_size;
}

void Map_set(Map *m, Str *key, const void *val) {
    int found;
    int i = sorted_find(m->keys, m->len, key, &found);
    if (found) {
        memcpy((char *)m->vals + i * m->elem_size, val, m->elem_size);
        return;
    }
    if (m->len >= m->cap) {
        m->cap = m->cap ? m->cap * 2 : 16;
        m->keys = realloc(m->keys, m->cap * sizeof(Str *));
        m->vals = realloc(m->vals, m->cap * m->elem_size);
    }
    // Shift elements right to make room at index i
    memmove(&m->keys[i + 1], &m->keys[i], (m->len - i) * sizeof(Str *));
    memmove((char *)m->vals + (i + 1) * m->elem_size,
            (char *)m->vals + i * m->elem_size,
            (m->len - i) * m->elem_size);
    m->keys[i] = key;
    memcpy((char *)m->vals + i * m->elem_size, val, m->elem_size);
    m->len++;
}

int Map_has(Map *m, Str *key) {
    int found;
    sorted_find(m->keys, m->len, key, &found);
    return found;
}

int Map_len(Map *m) {
    return m->len;
}

void Map_delete(Map *m) {
    free(m->keys);
    free(m->vals);
    m->keys = NULL;
    m->vals = NULL;
    m->len = 0;
    m->cap = 0;
}

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

Set Set_new(int elem_size, CmpFn cmp) {
    return (Set){.data = Vec_new(elem_size), .cmp = cmp};
}

int Set_has(Set *s, const void *elem) {
    int found;
    sorted_find_generic(s->data.data, s->data.len, s->data.elem_size,
                        s->cmp, elem, &found);
    return found;
}

void Set_add(Set *s, const void *elem) {
    int found;
    int es = s->data.elem_size;
    int i = sorted_find_generic(s->data.data, s->data.len, es,
                                s->cmp, elem, &found);
    if (found) return;
    // Grow if needed
    if (s->data.len >= s->data.cap) {
        s->data.cap = s->data.cap ? s->data.cap * 2 : 16;
        s->data.data = realloc(s->data.data, s->data.cap * es);
    }
    // Shift right and insert at sorted position
    memmove((char *)s->data.data + (i + 1) * es,
            (char *)s->data.data + i * es,
            (s->data.len - i) * es);
    memcpy((char *)s->data.data + i * es, elem, es);
    s->data.len++;
}

int Set_len(Set *s) {
    return s->data.len;
}

void Set_delete(Set *s) {
    Vec_delete(&s->data);
}

int str_ptr_cmp(const void *a, const void *b) {
    Str *sa = *(Str *const *)a;
    Str *sb = *(Str *const *)b;
    return Str_cmp(sa, sb);
}
