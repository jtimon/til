#include "str.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Str Str_val(const char *data) {
    I64 len = (I64)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = copy, .cap = len};
}

Str *Str_new(const char *data) {
    I64 len = (I64)strlen(data);
    return Str_new_len(data, len);
}

Str *Str_new_len(const char *data, I64 len) {
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

Bool Str_eq(Str *a, Str *b) {
    if (a->cap != b->cap) return 0;
    return memcmp(a->c_str, b->c_str, a->cap) == 0;
}

I64 Str_cmp(Str *a, Str *b) {
    I64 min = a->cap < b->cap ? a->cap : b->cap;
    I64 c = memcmp(a->c_str, b->c_str, min);
    if (c != 0) return c;
    return (a->cap > b->cap) - (a->cap < b->cap);
}

Bool Str_eq_c(Str *a, const char *b) {
    I64 blen = (I64)strlen(b);
    if (a->cap != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

Str *Str_concat(Str *a, Str *b) {
    I64 len = a->cap + b->cap;
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

I64 Str_len(Str *s) {
    return s->cap;
}

Str *Str_substr(Str *s, I64 start, I64 len) {
    if (start < 0) start = 0;
    if (start > s->cap) start = s->cap;
    if (len < 0) len = 0;
    if (start + len > s->cap) len = s->cap - start;
    return Str_new_len(s->c_str + start, len);
}

Bool Str_contains(Str *a, Str *b) {
    if (b->cap == 0) return 1;
    if (b->cap > a->cap) return 0;
    return memmem(a->c_str, a->cap, b->c_str, b->cap) != NULL;
}

Bool Str_starts_with(Str *a, Str *b) {
    if (b->cap > a->cap) return 0;
    return memcmp(a->c_str, b->c_str, b->cap) == 0;
}

Bool Str_ends_with(Str *a, Str *b) {
    if (b->cap > a->cap) return 0;
    return memcmp(a->c_str + a->cap - b->cap, b->c_str, b->cap) == 0;
}

Bool Str_neq(Str *a, Str *b) {
    return !Str_eq(a, b);
}

Bool Str_is_empty(Str *s) {
    return s->cap == 0;
}

I64 Str_find(Str *s, Str *needle) {
    if (needle->cap == 0) return -1;
    if (needle->cap > s->cap) return -1;
    char *p = memmem(s->c_str, s->cap, needle->c_str, needle->cap);
    if (!p) return -1;
    return (I64)(p - s->c_str);
}

I64 Str_rfind(Str *s, Str *needle) {
    if (needle->cap == 0) return -1;
    if (needle->cap > s->cap) return -1;
    I64 last = -1;
    for (I64 i = 0; i <= s->cap - needle->cap; i++) {
        if (memcmp(s->c_str + i, needle->c_str, needle->cap) == 0) {
            last = i;
        }
    }
    return last;
}

Str *Str_replace(Str *s, Str *from, Str *to) {
    if (from->cap == 0) return Str_clone(s);
    I64 count = 0;
    for (I64 i = 0; i <= s->cap - from->cap; ) {
        if (memcmp(s->c_str + i, from->c_str, from->cap) == 0) {
            count++;
            i += from->cap;
        } else {
            i++;
        }
    }
    if (count == 0) return Str_clone(s);
    I64 new_len = s->cap - count * from->cap + count * to->cap;
    Str *r = malloc(sizeof(Str));
    r->c_str = malloc(new_len + 1);
    r->cap = new_len;
    I64 di = 0;
    for (I64 si = 0; si < s->cap; ) {
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

Str *Str_get_char(Str *s, I64 i) {
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

Str *Str_from_byte(U8 byte) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(2);
    s->c_str[0] = (char)byte;
    s->c_str[1] = '\0';
    s->cap = 1;
    return s;
}

I64 Str_to_i64(Str *s) {
    if (s->cap == 0) {
        fprintf(stderr, "Str.to_i64: empty string\n");
        exit(1);
    }
    char *end;
    I64 v = strtoll(s->c_str, &end, 10);
    if (end != s->c_str + s->cap) {
        fprintf(stderr, "Str.to_i64: invalid char in '%.*s'\n", (int)s->cap, s->c_str);
        exit(1);
    }
    return v;
}
