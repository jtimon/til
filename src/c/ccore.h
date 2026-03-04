#ifndef CCORE_H
#define CCORE_H

// --- Str ---

typedef struct {
    char *c_str;
    int len;
} Str;

Str Str_val(const char *data);
Str *Str_new(const char *data);
Str *Str_new_len(const char *data, int len);
Str *Str_clone(Str *s);
void Str_delete(Str *s);
int Str_eq(Str *a, Str *b);
int Str_eq_c(Str *a, const char *b);
Str *Str_concat(Str *a, Str *b);
Str *Str_to_str(Str *s);
int Str_len(Str *s);
Str *Str_substr(Str *s, int start, int len);
int Str_contains(Str *a, Str *b);
int Str_starts_with(Str *a, Str *b);
int Str_ends_with(Str *a, Str *b);

// --- I64 ---

typedef long long I64;

I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);
int I64_eq(I64 a, I64 b);
int I64_lt(I64 a, I64 b);
int I64_gt(I64 a, I64 b);
Str *I64_to_str(I64 v);
I64 *I64_new(I64 val);
I64 *I64_clone(I64 *v);
void I64_delete(I64 *v);

// --- U8 ---

typedef unsigned char U8;

// --- Bool ---

typedef int Bool;

#endif
