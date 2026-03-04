#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(long long *code) { exit((int)*code); }

const char **til_i64_to_str(long long *v) {
    char *buf = malloc(32);
    snprintf(buf, 32, "%lld", *v);
    const char **r = malloc(sizeof(const char *));
    *r = buf;
    return r;
}

const char **til_u8_to_str(unsigned char *v) {
    char *buf = malloc(4);
    snprintf(buf, 4, "%u", (unsigned)*v);
    const char **r = malloc(sizeof(const char *));
    *r = buf;
    return r;
}

int *til_str_eq(const char **a, const char **b) {
    int *r = malloc(sizeof(int));
    *r = (strcmp(*a, *b) == 0);
    return r;
}

// I64 arithmetic
long long *til_i64_add(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a + *b; return r; }
long long *til_i64_sub(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a - *b; return r; }
long long *til_i64_mul(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a * *b; return r; }
long long *til_i64_div(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = (*b == 0) ? 0 : *a / *b; return r; }
long long *til_i64_mod(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = (*b == 0) ? 0 : *a % *b; return r; }
long long *til_i64_and(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a & *b; return r; }
long long *til_i64_or(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a | *b; return r; }
long long *til_i64_xor(long long *a, long long *b) { long long *r = malloc(sizeof(long long)); *r = *a ^ *b; return r; }

// I64 comparisons (return Bool/int *)
int *til_i64_eq(long long *a, long long *b) { int *r = malloc(sizeof(int)); *r = *a == *b; return r; }
int *til_i64_lt(long long *a, long long *b) { int *r = malloc(sizeof(int)); *r = *a < *b; return r; }
int *til_i64_gt(long long *a, long long *b) { int *r = malloc(sizeof(int)); *r = *a > *b; return r; }

// U8 arithmetic
unsigned char *til_u8_add(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = (unsigned char)(*a + *b); return r; }
unsigned char *til_u8_sub(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = (unsigned char)(*a - *b); return r; }
unsigned char *til_u8_mul(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = (unsigned char)(*a * *b); return r; }
unsigned char *til_u8_div(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = (*b == 0) ? 0 : (unsigned char)(*a / *b); return r; }
unsigned char *til_u8_mod(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = (*b == 0) ? 0 : (unsigned char)(*a % *b); return r; }
unsigned char *til_u8_and(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = *a & *b; return r; }
unsigned char *til_u8_or(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = *a | *b; return r; }
unsigned char *til_u8_xor(unsigned char *a, unsigned char *b) { unsigned char *r = malloc(1); *r = *a ^ *b; return r; }

// U8 comparisons
int *til_u8_eq(unsigned char *a, unsigned char *b) { int *r = malloc(sizeof(int)); *r = *a == *b; return r; }
int *til_u8_lt(unsigned char *a, unsigned char *b) { int *r = malloc(sizeof(int)); *r = *a < *b; return r; }
int *til_u8_gt(unsigned char *a, unsigned char *b) { int *r = malloc(sizeof(int)); *r = *a > *b; return r; }

// U8 conversions
long long *til_u8_to_i64(unsigned char *a) { long long *r = malloc(sizeof(long long)); *r = (long long)*a; return r; }
unsigned char *til_u8_from_i64(long long *a) { unsigned char *r = malloc(1); *r = (unsigned char)*a; return r; }

// Bool ops
int *til_bool_and(int *a, int *b) { int *r = malloc(sizeof(int)); *r = *a && *b; return r; }
int *til_bool_or(int *a, int *b) { int *r = malloc(sizeof(int)); *r = *a || *b; return r; }
int *til_bool_not(int *a) { int *r = malloc(sizeof(int)); *r = !*a; return r; }
