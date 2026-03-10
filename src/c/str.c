#include "str.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Str Str_val(const char *data) {
    U64 len = (U64)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = copy, .count = len, .cap = len};
}

Str *Str_new(const char *data) {
    U64 len = (U64)strlen(data);
    return Str_new_len(data, len);
}

Str *Str_new_len(const char *data, U64 len) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, data, len);
    s->c_str[len] = '\0';
    s->count = len;
    s->cap = len;
    return s;
}

Str *Str_clone(Str *s) {
    return Str_new_len(s->c_str, s->count);
}

void Str_delete(Str *s) {
    if (s->cap < CAP_VIEW) free(s->c_str);
    free(s);
}

Bool Str_eq(Str *a, Str *b) {
    if (a->count != b->count) return 0;
    return memcmp(a->c_str, b->c_str, a->count) == 0;
}

I64 Str_cmp(Str *a, Str *b) {
    U64 min = a->count < b->count ? a->count : b->count;
    I64 c = memcmp(a->c_str, b->c_str, min);
    if (c != 0) return c;
    return (a->count > b->count) - (a->count < b->count);
}

Bool Str_eq_c(Str *a, const char *b) {
    U64 blen = (U64)strlen(b);
    if (a->count != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

Str *Str_concat(Str *a, Str *b) {
    U64 len = a->count + b->count;
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, a->c_str, a->count);
    memcpy(s->c_str + a->count, b->c_str, b->count);
    s->c_str[len] = '\0';
    s->count = len;
    s->cap = len;
    return s;
}

Str *Str_to_str(Str *s) {
    return Str_clone(s);
}

U64 Str_len(Str *s) {
    return s->count;
}

Str *Str_substr(Str *s, U64 start, U64 len) {
    if (start > s->count) start = s->count;
    if (start + len > s->count) len = s->count - start;
    Str *v = malloc(sizeof(Str));
    v->c_str = s->c_str + start;
    v->count = len;
    v->cap = CAP_VIEW;
    return v;
}

Bool Str_contains(Str *a, Str *b) {
    if (b->count == 0) return 1;
    if (b->count > a->count) return 0;
    return memmem(a->c_str, a->count, b->c_str, b->count) != NULL;
}

Bool Str_starts_with(Str *a, Str *b) {
    if (b->count > a->count) return 0;
    return memcmp(a->c_str, b->c_str, b->count) == 0;
}

Bool Str_ends_with(Str *a, Str *b) {
    if (b->count > a->count) return 0;
    return memcmp(a->c_str + a->count - b->count, b->c_str, b->count) == 0;
}

Bool Str_neq(Str *a, Str *b) {
    return !Str_eq(a, b);
}

Bool Str_is_empty(Str *s) {
    return s->count == 0;
}

I64 Str_find(Str *s, Str *needle) {
    if (needle->count == 0) return -1;
    if (needle->count > s->count) return -1;
    char *p = memmem(s->c_str, s->count, needle->c_str, needle->count);
    if (!p) return -1;
    return (I64)(p - s->c_str);
}

I64 Str_rfind(Str *s, Str *needle) {
    if (needle->count == 0) return -1;
    if (needle->count > s->count) return -1;
    I64 last = -1;
    for (U64 i = 0; i <= s->count - needle->count; i++) {
        if (memcmp(s->c_str + i, needle->c_str, needle->count) == 0) {
            last = (I64)i;
        }
    }
    return last;
}

Str *Str_replace(Str *s, Str *from, Str *to) {
    if (from->count == 0) return Str_clone(s);
    U64 n = 0;
    for (U64 i = 0; i <= s->count - from->count; ) {
        if (memcmp(s->c_str + i, from->c_str, from->count) == 0) {
            n++;
            i += from->count;
        } else {
            i++;
        }
    }
    if (n == 0) return Str_clone(s);
    U64 new_len = s->count - n * from->count + n * to->count;
    Str *r = malloc(sizeof(Str));
    r->c_str = malloc(new_len + 1);
    r->count = new_len;
    r->cap = new_len;
    U64 di = 0;
    for (U64 si = 0; si < s->count; ) {
        if (si <= s->count - from->count && memcmp(s->c_str + si, from->c_str, from->count) == 0) {
            memcpy(r->c_str + di, to->c_str, to->count);
            di += to->count;
            si += from->count;
        } else {
            r->c_str[di++] = s->c_str[si++];
        }
    }
    r->c_str[new_len] = '\0';
    return r;
}

Str *Str_get_char(Str *s, U64 i) {
    return Str_substr(s, i, 1);
}

Str *Str_strip_prefix(Str *s, Str *prefix) {
    if (Str_starts_with(s, prefix)) {
        return Str_substr(s, prefix->count, s->count - prefix->count);
    }
    return Str_clone(s);
}

Str *Str_strip_suffix(Str *s, Str *suffix) {
    if (Str_ends_with(s, suffix)) {
        return Str_substr(s, 0, s->count - suffix->count);
    }
    return Str_clone(s);
}

Str *Str_from_byte(U8 byte) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(2);
    s->c_str[0] = (char)byte;
    s->c_str[1] = '\0';
    s->count = 1;
    s->cap = 1;
    return s;
}

I64 Str_to_i64(Str *s) {
    if (s->count == 0) {
        fprintf(stderr, "Str.to_i64: empty string\n");
        exit(1);
    }
    char buf[32];
    U64 n = s->count < 31 ? s->count : 31;
    memcpy(buf, s->c_str, n);
    buf[n] = '\0';
    char *end;
    I64 v = strtoll(buf, &end, 10);
    if (end != buf + s->count) {
        fprintf(stderr, "Str.to_i64: invalid char in '%.*s'\n", (int)s->count, s->c_str);
        exit(1);
    }
    return v;
}

Str *Str_with_capacity(U64 n) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(n + 1);
    s->c_str[0] = '\0';
    s->count = 0;
    s->cap = n;
    return s;
}

void Str_push_str(Str *s, Str *other) {
    if (s->cap >= CAP_VIEW) {
        fprintf(stderr, "Str.push_str: cannot mutate a string view or literal\n");
        exit(1);
    }
    U64 new_len = s->count + other->count;
    if (new_len > s->cap) {
        fprintf(stderr, "Str.push_str: capacity exceeded\n");
        exit(1);
    }
    memcpy(s->c_str + s->count, other->c_str, other->count);
    s->count = new_len;
    s->c_str[new_len] = '\0';
}
