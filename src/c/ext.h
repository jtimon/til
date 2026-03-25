#pragma once

#include "aliases.h"

// I64 clone
I64 I64_clone(I64 *v);

// I64 arithmetic (shallow params)
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);

// I64 comparisons
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);

// U8 arithmetic
U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_and(U8 a, U8 b);
U8 U8_or(U8 a, U8 b);
U8 U8_xor(U8 a, U8 b);

// U8 comparisons
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);

// U8 conversions
I64 U8_to_i64(U8 a);
U8 I64_to_u8(I64 a);
U8 U8_from_i64_ext(I64 *a);

// U8 clone
U8 U8_clone(U8 *v);

// I16 arithmetic
I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);

// I16 comparisons
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);

// I16 conversions
I64 I16_to_i64(I16 a);
I16 I64_to_i16(I64 a);
I32 I64_to_i32(I64 a);
U32 I64_to_u32(I64 a);
U64 I64_to_u64(I64 a);
F32 I64_to_f32(I64 a);
I16 I16_from_i64_ext(I64 *a);

// I16 clone
I16 I16_clone(I16 *v);

// I16 CLI
I16 *cli_parse_i16(const char *s);

// I32 arithmetic
I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_and(I32 a, I32 b);
I32 I32_or(I32 a, I32 b);
I32 I32_xor(I32 a, I32 b);
I32 I32_not(I32 a);

// I32 comparisons
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);

// I32 conversions
I64 I32_to_i64(I32 a);
I32 I32_from_i64_ext(I64 *a);

// I32 clone
I32 I32_clone(I32 *v);

// I32 CLI
I32 *cli_parse_i32(const char *s);

// F32 arithmetic
F32 F32_add(F32 a, F32 b);
F32 F32_sub(F32 a, F32 b);
F32 F32_mul(F32 a, F32 b);
F32 F32_div(F32 a, F32 b);

// F32 comparisons
Bool F32_eq(F32 a, F32 b);
I64 F32_cmp(F32 a, F32 b);

// F32 conversions
I64 F32_to_i64(F32 a);
F32 F32_from_i64_ext(I64 *a);
Str *F32_to_str(F32 v);

// F32 clone
F32 F32_clone(F32 *v);

// U32 arithmetic
U32 U32_add(U32 a, U32 b);
U32 U32_sub(U32 a, U32 b);
U32 U32_mul(U32 a, U32 b);
U32 U32_div(U32 a, U32 b);
U32 U32_mod(U32 a, U32 b);
U32 U32_and(U32 a, U32 b);
U32 U32_or(U32 a, U32 b);
U32 U32_xor(U32 a, U32 b);

// U32 comparisons
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);

// U32 conversions
I64 U32_to_i64(U32 a);
U32 U32_from_i64_ext(I64 *a);

// U32 clone
U32 U32_clone(U32 *v);

// U64 arithmetic
U64 U64_add(U64 a, U64 b);
U64 U64_sub(U64 a, U64 b);
U64 U64_mul(U64 a, U64 b);
U64 U64_div(U64 a, U64 b);
U64 U64_mod(U64 a, U64 b);
U64 U64_and(U64 a, U64 b);
U64 U64_or(U64 a, U64 b);
U64 U64_xor(U64 a, U64 b);

// U64 comparisons
Bool U64_eq(U64 a, U64 b);
I64 U64_cmp(U64 a, U64 b);

// U64 conversions
I64 U64_to_i64(U64 a);
U64 U64_from_i64_ext(I64 *a);
Str *U64_to_str(U64 v);
Str *U64_to_str_ext(U64 v);

// U64 clone
U64 U64_clone(U64 *v);

// Bool ops (shallow params)
Bool Bool_eq(Bool a, Bool b);
Bool Bool_and(Bool a, Bool b);
Bool Bool_or(Bool a, Bool b);
Bool Bool_not(Bool a);

// Bool clone
Bool Bool_clone(Bool *v);

// Pointer primitives (custom, not in libc)
void *ptr_add(void *buf, U64 offset);
Bool is_null(void *p);
Bool is_variant(void *self, void *other);
void *get_payload(void *self);

// CLI arg parsing
I64 *cli_parse_i64(const char *s);
U8 *cli_parse_u8(const char *s);
U32 *cli_parse_u32(const char *s);
U64 *cli_parse_u64(const char *s);
Bool *cli_parse_bool(const char *s);

// System primitives
Str *readfile(Str *path);
void writefile(Str *path, Str *content);
I64 *spawn_cmd(Str *cmd);
I64 check_cmd_status(I64 pid);
void sleep_ms(I64 ms);
I64 file_mtime(Str *path);
I64 clock_ms(void);
I64 get_thread_count(void);
USize c_str_len(U8 *s);
