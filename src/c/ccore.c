#include "ccore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Str (str.h) ---

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

// --- I64 (i64.h) ---

I64 I64_add(I64 a, I64 b) { return a + b; }
I64 I64_sub(I64 a, I64 b) { return a - b; }
I64 I64_mul(I64 a, I64 b) { return a * b; }
I64 I64_div(I64 a, I64 b) { return (b == 0) ? 0 : a / b; }
I64 I64_mod(I64 a, I64 b) { return (b == 0) ? 0 : a % b; }
I64 I64_and(I64 a, I64 b) { return a & b; }
I64 I64_or(I64 a, I64 b) { return a | b; }
I64 I64_xor(I64 a, I64 b) { return a ^ b; }

int I64_eq(I64 a, I64 b) { return a == b; }
int I64_lt(I64 a, I64 b) { return a < b; }
int I64_gt(I64 a, I64 b) { return a > b; }

Str *I64_to_str(I64 v) {
    char buf[32];
    snprintf(buf, 32, "%lld", v);
    return Str_new(buf);
}

I64 *I64_new(I64 val) {
    I64 *p = malloc(sizeof(I64));
    *p = val;
    return p;
}

I64 *I64_clone(I64 *v) { return I64_new(*v); }
void I64_delete(I64 *v) { free(v); }

// --- U8 (ccore.h) ---

U8 U8_add(U8 a, U8 b) { return (U8)(a + b); }
U8 U8_sub(U8 a, U8 b) { return (U8)(a - b); }
U8 U8_mul(U8 a, U8 b) { return (U8)(a * b); }
U8 U8_div(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a / b); }
U8 U8_mod(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a % b); }
U8 U8_and(U8 a, U8 b) { return a & b; }
U8 U8_or(U8 a, U8 b) { return a | b; }
U8 U8_xor(U8 a, U8 b) { return a ^ b; }

int U8_eq(U8 a, U8 b) { return a == b; }
int U8_lt(U8 a, U8 b) { return a < b; }
int U8_gt(U8 a, U8 b) { return a > b; }

Str *U8_to_str(U8 v) {
    char buf[4];
    snprintf(buf, 4, "%u", (unsigned)v);
    return Str_new(buf);
}

I64 U8_to_i64(U8 v) { return (I64)v; }
U8 U8_from_i64(I64 v) { return (U8)v; }

U8 *U8_new(U8 val) {
    U8 *p = malloc(sizeof(U8));
    *p = val;
    return p;
}

U8 *U8_clone(U8 *v) { return U8_new(*v); }
void U8_delete(U8 *v) { free(v); }
