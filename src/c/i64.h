#ifndef I64_H
#define I64_H

#include "str.h"

typedef long long I64;

// Arithmetic
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);

// Comparisons
int I64_eq(I64 a, I64 b);
int I64_lt(I64 a, I64 b);
int I64_gt(I64 a, I64 b);

// Conversion
Str *I64_to_str(I64 v);

// Allocation
I64 *I64_new(I64 val);
I64 *I64_clone(I64 *v);
void I64_delete(I64 *v);

#endif
