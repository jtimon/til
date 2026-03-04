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

Set Set_new(void) {
    return (Set){.keys = NULL, .len = 0, .cap = 0};
}

int Set_has(Set *s, Str *key) {
    int found;
    sorted_find(s->keys, s->len, key, &found);
    return found;
}

void Set_add(Set *s, Str *key) {
    int found;
    int i = sorted_find(s->keys, s->len, key, &found);
    if (found) return;
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 16;
        s->keys = realloc(s->keys, s->cap * sizeof(Str *));
    }
    memmove(&s->keys[i + 1], &s->keys[i], (s->len - i) * sizeof(Str *));
    s->keys[i] = key;
    s->len++;
}

int Set_len(Set *s) {
    return s->len;
}

void Set_delete(Set *s) {
    free(s->keys);
    s->keys = NULL;
    s->len = 0;
    s->cap = 0;
}
