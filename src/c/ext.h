#ifndef TIL_EXT_H
#define TIL_EXT_H

typedef long long til_I64;
typedef unsigned char til_U8;
typedef int til_Bool;
typedef const char *c_str;

void til_free(void *ptr);
void til_exit(til_I64 *code);
c_str *til_I64_to_str(til_I64 *v);
c_str *til_U8_to_str(til_U8 *v);
til_Bool *til_Str_eq(c_str *a, c_str *b);

// I64 arithmetic
til_I64 *til_I64_add(til_I64 *a, til_I64 *b);
til_I64 *til_I64_sub(til_I64 *a, til_I64 *b);
til_I64 *til_I64_mul(til_I64 *a, til_I64 *b);
til_I64 *til_I64_div(til_I64 *a, til_I64 *b);
til_I64 *til_I64_mod(til_I64 *a, til_I64 *b);
til_I64 *til_I64_and(til_I64 *a, til_I64 *b);
til_I64 *til_I64_or(til_I64 *a, til_I64 *b);
til_I64 *til_I64_xor(til_I64 *a, til_I64 *b);

// I64 comparisons
til_Bool *til_I64_eq(til_I64 *a, til_I64 *b);
til_Bool *til_I64_lt(til_I64 *a, til_I64 *b);
til_Bool *til_I64_gt(til_I64 *a, til_I64 *b);

// U8 arithmetic
til_U8 *til_U8_add(til_U8 *a, til_U8 *b);
til_U8 *til_U8_sub(til_U8 *a, til_U8 *b);
til_U8 *til_U8_mul(til_U8 *a, til_U8 *b);
til_U8 *til_U8_div(til_U8 *a, til_U8 *b);
til_U8 *til_U8_mod(til_U8 *a, til_U8 *b);
til_U8 *til_U8_and(til_U8 *a, til_U8 *b);
til_U8 *til_U8_or(til_U8 *a, til_U8 *b);
til_U8 *til_U8_xor(til_U8 *a, til_U8 *b);

// U8 comparisons
til_Bool *til_U8_eq(til_U8 *a, til_U8 *b);
til_Bool *til_U8_lt(til_U8 *a, til_U8 *b);
til_Bool *til_U8_gt(til_U8 *a, til_U8 *b);

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a);
til_U8 *til_U8_from_i64_ext(til_I64 *a);

// Bool ops
til_Bool *til_Bool_and(til_Bool *a, til_Bool *b);
til_Bool *til_Bool_or(til_Bool *a, til_Bool *b);
til_Bool *til_Bool_not(til_Bool *a);

#endif
