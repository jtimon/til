#ifndef TIL_EXT_H
#define TIL_EXT_H

void til_free(void *ptr);
void til_exit(long long *code);
const char **til_i64_to_str(long long *v);
const char **til_u8_to_str(unsigned char *v);
int *til_str_eq(const char **a, const char **b);

// I64 arithmetic
long long *til_i64_add(long long *a, long long *b);
long long *til_i64_sub(long long *a, long long *b);
long long *til_i64_mul(long long *a, long long *b);
long long *til_i64_div(long long *a, long long *b);
long long *til_i64_mod(long long *a, long long *b);
long long *til_i64_and(long long *a, long long *b);
long long *til_i64_or(long long *a, long long *b);
long long *til_i64_xor(long long *a, long long *b);

// I64 comparisons
int *til_i64_eq(long long *a, long long *b);
int *til_i64_lt(long long *a, long long *b);
int *til_i64_gt(long long *a, long long *b);

// U8 arithmetic
unsigned char *til_u8_add(unsigned char *a, unsigned char *b);
unsigned char *til_u8_sub(unsigned char *a, unsigned char *b);
unsigned char *til_u8_mul(unsigned char *a, unsigned char *b);
unsigned char *til_u8_div(unsigned char *a, unsigned char *b);
unsigned char *til_u8_mod(unsigned char *a, unsigned char *b);
unsigned char *til_u8_and(unsigned char *a, unsigned char *b);
unsigned char *til_u8_or(unsigned char *a, unsigned char *b);
unsigned char *til_u8_xor(unsigned char *a, unsigned char *b);

// U8 comparisons
int *til_u8_eq(unsigned char *a, unsigned char *b);
int *til_u8_lt(unsigned char *a, unsigned char *b);
int *til_u8_gt(unsigned char *a, unsigned char *b);

// U8 conversions
long long *til_u8_to_i64(unsigned char *a);
unsigned char *til_u8_from_i64(long long *a);

// Bool ops
int *til_bool_and(int *a, int *b);
int *til_bool_or(int *a, int *b);
int *til_bool_not(int *a);

#endif
