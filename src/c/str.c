#include "str.h"
#include <stdlib.h>
#include <string.h>

Str Str_val(const char *data) {
    int len = (int)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = copy, .len = len};
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
    s->len = len;
    return s;
}

Str *Str_clone(Str *s) {
    return Str_new_len(s->c_str, s->len);
}

void Str_delete(Str *s) {
    free(s->c_str);
    free(s);
}

int Str_eq(Str *a, Str *b) {
    if (a->len != b->len) return 0;
    return memcmp(a->c_str, b->c_str, a->len) == 0;
}

int Str_eq_c(Str *a, const char *b) {
    int blen = (int)strlen(b);
    if (a->len != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

Str *Str_concat(Str *a, Str *b) {
    int len = a->len + b->len;
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, a->c_str, a->len);
    memcpy(s->c_str + a->len, b->c_str, b->len);
    s->c_str[len] = '\0';
    s->len = len;
    return s;
}

Str *Str_to_str(Str *s) {
    return Str_clone(s);
}

int Str_len(Str *s) {
    return s->len;
}

Str *Str_substr(Str *s, int start, int len) {
    if (start < 0) start = 0;
    if (start > s->len) start = s->len;
    if (len < 0) len = 0;
    if (start + len > s->len) len = s->len - start;
    return Str_new_len(s->c_str + start, len);
}

int Str_contains(Str *a, Str *b) {
    if (b->len == 0) return 1;
    if (b->len > a->len) return 0;
    return memmem(a->c_str, a->len, b->c_str, b->len) != NULL;
}

int Str_starts_with(Str *a, Str *b) {
    if (b->len > a->len) return 0;
    return memcmp(a->c_str, b->c_str, b->len) == 0;
}

int Str_ends_with(Str *a, Str *b) {
    if (b->len > a->len) return 0;
    return memcmp(a->c_str + a->len - b->len, b->c_str, b->len) == 0;
}
