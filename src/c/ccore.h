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
I64 I64_inc(I64 a);
I64 I64_dec(I64 a);
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);
Str *I64_to_str(I64 v);
I64 *I64_new(I64 val);
I64 *I64_clone(I64 *v);
void I64_delete(I64 *v, Bool *call_free);

// --- U8 ---

U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_and(U8 a, U8 b);
U8 U8_or(U8 a, U8 b);
U8 U8_xor(U8 a, U8 b);
U8 U8_inc(U8 a);
U8 U8_dec(U8 a);
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);
Str *U8_to_str(U8 v);
I64 U8_to_i64(U8 v);
U8 U8_from_i64(I64 v);
U8 *U8_new(U8 val);
U8 *U8_clone(U8 *v);
void U8_delete(U8 *v, Bool *call_free);

// --- I16 ---

I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);
I16 I16_inc(I16 a);
I16 I16_dec(I16 a);
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);
I64 I16_to_i64(I16 v);
I16 I16_from_i64(I64 v);
I16 *I16_new(I16 val);
I16 *I16_clone(I16 *v);
void I16_delete(I16 *v, Bool *call_free);

// --- I32 ---

I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_and(I32 a, I32 b);
I32 I32_or(I32 a, I32 b);
I32 I32_xor(I32 a, I32 b);
I32 I32_inc(I32 a);
I32 I32_dec(I32 a);
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);
I64 I32_to_i64(I32 v);
I32 I32_from_i64(I64 v);
I32 *I32_new(I32 val);
I32 *I32_clone(I32 *v);
void I32_delete(I32 *v, Bool *call_free);

// --- F32 ---

F32 F32_add(F32 a, F32 b);
F32 F32_sub(F32 a, F32 b);
F32 F32_mul(F32 a, F32 b);
F32 F32_div(F32 a, F32 b);
Bool F32_eq(F32 a, F32 b);
I64 F32_cmp(F32 a, F32 b);
I64 F32_to_i64(F32 v);
F32 F32_from_i64(I64 v);
Str *F32_to_str(F32 v);
F32 *F32_new(F32 val);
F32 *F32_clone(F32 *v);
void F32_delete(F32 *v, Bool *call_free);

// --- U32 ---

U32 U32_add(U32 a, U32 b);
U32 U32_sub(U32 a, U32 b);
U32 U32_mul(U32 a, U32 b);
U32 U32_div(U32 a, U32 b);
U32 U32_mod(U32 a, U32 b);
U32 U32_and(U32 a, U32 b);
U32 U32_or(U32 a, U32 b);
U32 U32_xor(U32 a, U32 b);
U32 U32_inc(U32 a);
U32 U32_dec(U32 a);
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);
I64 U32_to_i64(U32 v);
U32 U32_from_i64(I64 v);
U32 *U32_new(U32 val);
U32 *U32_clone(U32 *v);
void U32_delete(U32 *v, Bool *call_free);

// --- Bool ---

Bool Bool_eq(Bool a, Bool b);
Bool Bool_and(Bool a, Bool b);
Bool Bool_or(Bool a, Bool b);
Bool Bool_not(Bool a);
Bool *Bool_new(Bool val);
Bool *Bool_clone(Bool *v);
void Bool_delete(Bool *v, Bool *call_free);

#endif
