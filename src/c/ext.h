#ifndef TIL_EXT_H
#define TIL_EXT_H

#include "str.h"

typedef long long til_I64;
typedef unsigned char til_U8;
typedef int til_Bool;

void til_free(void *ptr);
void til_exit(til_I64 *code);
Str *til_I64_to_str(til_I64 *v);
Str *til_U8_to_str(til_U8 *v);
til_Bool *til_Str_eq(Str *a, Str *b);
Str *til_Str_concat(Str *a, Str *b);
Str *til_Str_clone(Str *s);
void til_Str_delete(Str *s, til_Bool *call_free);
Str *til_Str_to_str(Str *s);
til_I64 *til_Str_len(Str *s);
Str *til_Str_substr(Str *s, til_I64 *start, til_I64 *n);
til_Bool *til_Str_contains(Str *a, Str *b);
til_Bool *til_Str_starts_with(Str *a, Str *b);
til_Bool *til_Str_ends_with(Str *a, Str *b);

// I64 clone/delete
til_I64 *til_I64_clone(til_I64 *v);
void til_I64_delete(til_I64 *v, til_Bool *call_free);

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

// U8 clone/delete
til_U8 *til_U8_clone(til_U8 *v);
void til_U8_delete(til_U8 *v, til_Bool *call_free);

// Bool ops
til_Bool *til_Bool_and(til_Bool *a, til_Bool *b);
til_Bool *til_Bool_or(til_Bool *a, til_Bool *b);
til_Bool *til_Bool_not(til_Bool *a);

// ext_struct: Pair (test)
typedef struct til_Pair { til_I64 a; til_I64 b; } til_Pair;
til_I64 *til_Pair_sum(til_Pair *self);
til_Pair *til_Pair_swap(til_Pair *self);
til_Pair *til_Pair_clone(til_Pair *self);
void til_Pair_delete(til_Pair *self, til_Bool *call_free);

// Variadic builtins
Str *til_format(int n, ...);
void til_println(int n, ...);
void til_print(int n, ...);

#endif
