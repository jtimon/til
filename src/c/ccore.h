#ifndef CCORE_H
#define CCORE_H

#include "aliases.h"
#include "str.h"

// --- I64 ---

I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);
Str *I64_to_str(I64 v);
I64 *I64_new(I64 val);
I64 *I64_clone(I64 *v);
void I64_delete(I64 *v);

// --- U8 ---

U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_and(U8 a, U8 b);
U8 U8_or(U8 a, U8 b);
U8 U8_xor(U8 a, U8 b);
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);
Str *U8_to_str(U8 v);
I64 U8_to_i64(U8 v);
U8 U8_from_i64(I64 v);
U8 *U8_new(U8 val);
U8 *U8_clone(U8 *v);
void U8_delete(U8 *v);

// --- I16 ---

I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);
I64 I16_to_i64(I16 v);
I16 I16_from_i64(I64 v);
I16 *I16_new(I16 val);
I16 *I16_clone(I16 *v);
void I16_delete(I16 *v);

// --- U32 ---

U32 U32_add(U32 a, U32 b);
U32 U32_sub(U32 a, U32 b);
U32 U32_mul(U32 a, U32 b);
U32 U32_div(U32 a, U32 b);
U32 U32_mod(U32 a, U32 b);
U32 U32_and(U32 a, U32 b);
U32 U32_or(U32 a, U32 b);
U32 U32_xor(U32 a, U32 b);
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);
I64 U32_to_i64(U32 v);
U32 U32_from_i64(I64 v);
U32 *U32_new(U32 val);
U32 *U32_clone(U32 *v);
void U32_delete(U32 *v);

// --- Bool ---

Bool Bool_eq(Bool a, Bool b);
Bool Bool_and(Bool a, Bool b);
Bool Bool_or(Bool a, Bool b);
Bool Bool_not(Bool a);
Bool *Bool_new(Bool val);
Bool *Bool_clone(Bool *v);
void Bool_delete(Bool *v);

#endif
