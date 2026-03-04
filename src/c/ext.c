#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(til_I64 *code) { exit((int)*code); }

c_str *til_I64_to_str(til_I64 *v) {
    char *buf = malloc(32);
    snprintf(buf, 32, "%lld", *v);
    c_str *r = malloc(sizeof(c_str));
    *r = buf;
    return r;
}

c_str *til_U8_to_str(til_U8 *v) {
    char *buf = malloc(4);
    snprintf(buf, 4, "%u", (unsigned)*v);
    c_str *r = malloc(sizeof(c_str));
    *r = buf;
    return r;
}

til_Bool *til_Str_eq(c_str *a, c_str *b) {
    til_Bool *r = malloc(sizeof(til_Bool));
    *r = (strcmp(*a, *b) == 0);
    return r;
}

// I64 arithmetic
til_I64 *til_I64_add(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a + *b; return r; }
til_I64 *til_I64_sub(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a - *b; return r; }
til_I64 *til_I64_mul(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a * *b; return r; }
til_I64 *til_I64_div(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = (*b == 0) ? 0 : *a / *b; return r; }
til_I64 *til_I64_mod(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = (*b == 0) ? 0 : *a % *b; return r; }
til_I64 *til_I64_and(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a & *b; return r; }
til_I64 *til_I64_or(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a | *b; return r; }
til_I64 *til_I64_xor(til_I64 *a, til_I64 *b) { til_I64 *r = malloc(sizeof(til_I64)); *r = *a ^ *b; return r; }

// I64 comparisons
til_Bool *til_I64_eq(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a == *b; return r; }
til_Bool *til_I64_lt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a < *b; return r; }
til_Bool *til_I64_gt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a > *b; return r; }

// U8 arithmetic
til_U8 *til_U8_add(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = (til_U8)(*a + *b); return r; }
til_U8 *til_U8_sub(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = (til_U8)(*a - *b); return r; }
til_U8 *til_U8_mul(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = (til_U8)(*a * *b); return r; }
til_U8 *til_U8_div(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = (*b == 0) ? 0 : (til_U8)(*a / *b); return r; }
til_U8 *til_U8_mod(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = (*b == 0) ? 0 : (til_U8)(*a % *b); return r; }
til_U8 *til_U8_and(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = *a & *b; return r; }
til_U8 *til_U8_or(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = *a | *b; return r; }
til_U8 *til_U8_xor(til_U8 *a, til_U8 *b) { til_U8 *r = malloc(sizeof(til_U8)); *r = *a ^ *b; return r; }

// U8 comparisons
til_Bool *til_U8_eq(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a == *b; return r; }
til_Bool *til_U8_lt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a < *b; return r; }
til_Bool *til_U8_gt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a > *b; return r; }

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a) { til_I64 *r = malloc(sizeof(til_I64)); *r = (til_I64)*a; return r; }
til_U8 *til_U8_from_i64_ext(til_I64 *a) { til_U8 *r = malloc(sizeof(til_U8)); *r = (til_U8)*a; return r; }

// Bool ops
til_Bool *til_Bool_and(til_Bool *a, til_Bool *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a && *b; return r; }
til_Bool *til_Bool_or(til_Bool *a, til_Bool *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = *a || *b; return r; }
til_Bool *til_Bool_not(til_Bool *a) { til_Bool *r = malloc(sizeof(til_Bool)); *r = !*a; return r; }
