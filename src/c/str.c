#include "str.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Str Str_val(const char *data) {
    int len = (int)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = copy, .cap = len};
}

Str *Str_new(const char *data) {
    int len = (int)strlen(data);
    return Str_new_len(data, len);
}

Str *Str_new_len(const char *data, int len) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, data, len);
    s->c_str[len] = '\0';
    s->cap = len;
    return s;
}

Str *Str_clone(Str *s) {
    return Str_new_len(s->c_str, s->cap);
}

void Str_delete(Str *s) {
    free(s->c_str);
    free(s);
}

int Str_eq(Str *a, Str *b) {
    if (a->cap != b->cap) return 0;
    return memcmp(a->c_str, b->c_str, a->cap) == 0;
}

int Str_cmp(Str *a, Str *b) {
    return strcmp(a->c_str, b->c_str);
}

int Str_eq_c(Str *a, const char *b) {
    int blen = (int)strlen(b);
    if (a->cap != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

Str *Str_concat(Str *a, Str *b) {
    int len = a->cap + b->cap;
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, a->c_str, a->cap);
    memcpy(s->c_str + a->cap, b->c_str, b->cap);
    s->c_str[len] = '\0';
    s->cap = len;
    return s;
}

Str *Str_to_str(Str *s) {
    return Str_clone(s);
}

int Str_len(Str *s) {
    return s->cap;
}

Str *Str_substr(Str *s, int start, int len) {
    if (start < 0) start = 0;
    if (start > s->cap) start = s->cap;
    if (len < 0) len = 0;
    if (start + len > s->cap) len = s->cap - start;
    return Str_new_len(s->c_str + start, len);
}

int Str_contains(Str *a, Str *b) {
    if (b->cap == 0) return 1;
    if (b->cap > a->cap) return 0;
    return memmem(a->c_str, a->cap, b->c_str, b->cap) != NULL;
}

int Str_starts_with(Str *a, Str *b) {
    if (b->cap > a->cap) return 0;
    return memcmp(a->c_str, b->c_str, b->cap) == 0;
}

int Str_ends_with(Str *a, Str *b) {
    if (b->cap > a->cap) return 0;
    return memcmp(a->c_str + a->cap - b->cap, b->c_str, b->cap) == 0;
}

int Str_neq(Str *a, Str *b) {
    return !Str_eq(a, b);
}

int Str_is_empty(Str *s) {
    return s->cap == 0;
}

int Str_find(Str *s, Str *needle) {
    if (needle->cap == 0) return -1;
    if (needle->cap > s->cap) return -1;
    char *p = memmem(s->c_str, s->cap, needle->c_str, needle->cap);
    if (!p) return -1;
    return (int)(p - s->c_str);
}

int Str_rfind(Str *s, Str *needle) {
    if (needle->cap == 0) return -1;
    if (needle->cap > s->cap) return -1;
    int last = -1;
    for (int i = 0; i <= s->cap - needle->cap; i++) {
        if (memcmp(s->c_str + i, needle->c_str, needle->cap) == 0) {
            last = i;
        }
    }
    return last;
}

Str *Str_replace(Str *s, Str *from, Str *to) {
    if (from->cap == 0) return Str_clone(s);
    // Count occurrences
    int count = 0;
    for (int i = 0; i <= s->cap - from->cap; ) {
        if (memcmp(s->c_str + i, from->c_str, from->cap) == 0) {
            count++;
            i += from->cap;
        } else {
            i++;
        }
    }
    if (count == 0) return Str_clone(s);
    int new_len = s->cap - count * from->cap + count * to->cap;
    Str *r = malloc(sizeof(Str));
    r->c_str = malloc(new_len + 1);
    r->cap = new_len;
    int di = 0;
    for (int si = 0; si < s->cap; ) {
        if (si <= s->cap - from->cap && memcmp(s->c_str + si, from->c_str, from->cap) == 0) {
            memcpy(r->c_str + di, to->c_str, to->cap);
            di += to->cap;
            si += from->cap;
        } else {
            r->c_str[di++] = s->c_str[si++];
        }
    }
    r->c_str[new_len] = '\0';
    return r;
}

Str *Str_get_char(Str *s, int i) {
    return Str_substr(s, i, 1);
}

Str *Str_strip_prefix(Str *s, Str *prefix) {
    if (Str_starts_with(s, prefix)) {
        return Str_substr(s, prefix->cap, s->cap - prefix->cap);
    }
    return Str_clone(s);
}

Str *Str_strip_suffix(Str *s, Str *suffix) {
    if (Str_ends_with(s, suffix)) {
        return Str_substr(s, 0, s->cap - suffix->cap);
    }
    return Str_clone(s);
}

Str *Str_from_byte(unsigned char byte) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(2);
    s->c_str[0] = (char)byte;
    s->c_str[1] = '\0';
    s->cap = 1;
    return s;
}

long long Str_to_i64(Str *s) {
    if (s->cap == 0) {
        fprintf(stderr, "Str.to_i64: empty string\n");
        exit(1);
    }
    char *end;
    long long v = strtoll(s->c_str, &end, 10);
    if (end != s->c_str + s->cap) {
        fprintf(stderr, "Str.to_i64: invalid char in '%.*s'\n", s->cap, s->c_str);
        exit(1);
    }
    return v;
}
