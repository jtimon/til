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
int Str_cmp(Str *a, Str *b);
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

U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_and(U8 a, U8 b);
U8 U8_or(U8 a, U8 b);
U8 U8_xor(U8 a, U8 b);
int U8_eq(U8 a, U8 b);
int U8_lt(U8 a, U8 b);
int U8_gt(U8 a, U8 b);
Str *U8_to_str(U8 v);
I64 U8_to_i64(U8 v);
U8 U8_from_i64(I64 v);
U8 *U8_new(U8 val);
U8 *U8_clone(U8 *v);
void U8_delete(U8 *v);

// --- Bool ---

typedef int Bool;

Bool Bool_and(Bool a, Bool b);
Bool Bool_or(Bool a, Bool b);
Bool Bool_not(Bool a);
Bool *Bool_new(Bool val);
Bool *Bool_clone(Bool *v);
void Bool_delete(Bool *v);

#endif
