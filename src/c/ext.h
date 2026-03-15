#ifndef TIL_EXT_H
#define TIL_EXT_H

#include "aliases.h"

// I64 clone/delete
I64 I64_clone(I64 *v);
void I64_delete(I64 *v, Bool *call_free);

// I64 arithmetic (shallow params)
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
U8 U8_inc(U8 a);
U8 U8_dec(U8 a);

// U8 comparisons
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);

// U8 conversions
I64 U8_to_i64(U8 a);
U8 I64_to_u8(I64 a);
U8 U8_from_i64_ext(I64 *a);

// U8 clone/delete
U8 U8_clone(U8 *v);
void U8_delete(U8 *v, Bool *call_free);

// I16 arithmetic
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

// I16 clone/delete
I16 I16_clone(I16 *v);
void I16_delete(I16 *v, Bool *call_free);

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
I32 I32_inc(I32 a);
I32 I32_dec(I32 a);

// I32 comparisons
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);

// I32 conversions
I64 I32_to_i64(I32 a);
I32 I32_from_i64_ext(I64 *a);

// I32 clone/delete
I32 I32_clone(I32 *v);
void I32_delete(I32 *v, Bool *call_free);

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

// F32 clone/delete
F32 F32_clone(F32 *v);
void F32_delete(F32 *v, Bool *call_free);

// U32 arithmetic
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

// U32 comparisons
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);

// U32 conversions
I64 U32_to_i64(U32 a);
U32 U32_from_i64_ext(I64 *a);

// U32 clone/delete
U32 U32_clone(U32 *v);
void U32_delete(U32 *v, Bool *call_free);

// U64 arithmetic
U64 U64_add(U64 a, U64 b);
U64 U64_sub(U64 a, U64 b);
U64 U64_mul(U64 a, U64 b);
U64 U64_div(U64 a, U64 b);
U64 U64_mod(U64 a, U64 b);
U64 U64_and(U64 a, U64 b);
U64 U64_or(U64 a, U64 b);
U64 U64_xor(U64 a, U64 b);
U64 U64_inc(U64 a);
U64 U64_dec(U64 a);

// U64 comparisons
Bool U64_eq(U64 a, U64 b);
I64 U64_cmp(U64 a, U64 b);

// U64 conversions
I64 U64_to_i64(U64 a);
U64 U64_from_i64_ext(I64 *a);
Str *U64_to_str(U64 v);
Str *U64_to_str_ext(U64 v);

// U64 clone/delete
U64 U64_clone(U64 *v);
void U64_delete(U64 *v, Bool *call_free);

// Bool ops (shallow params)
Bool Bool_eq(Bool a, Bool b);
Bool Bool_and(Bool a, Bool b);
Bool Bool_or(Bool a, Bool b);
Bool Bool_not(Bool a);

// Bool clone/delete
Bool Bool_clone(Bool *v);
void Bool_delete(Bool *v, Bool *call_free);

// Pointer primitives (custom, not in libc)
void *ptr_add(void *buf, U64 offset);
Bool is_null(void *p);

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

#endif
