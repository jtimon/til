#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef long long I64;
typedef unsigned long long U64;
typedef int I32;
typedef unsigned int U32;
typedef short I16;
typedef unsigned short U16;
typedef char I8;
typedef unsigned char U8;
typedef float F32;
typedef bool Bool;
typedef U32 USize;  // container sizes (count, cap, elem_size)
#if UINTPTR_MAX == 0xffffffff
typedef U32 UPtr;
#else
typedef U64 UPtr;
#endif
typedef struct Str Str;

// During the USize migration, generated code should box size arguments using
// the alias-facing ABI rather than the source expression's numeric type.
// USIZE_REF spells the box with the USize typedef name (rather than a hardwired
// U32) so it widens with the typedef once it goes target-driven.
#define USIZE_REF(x) ((void *)&(USize){(USize)(x)})
#define UPTR_REF(x) ((void *)&(UPtr){(UPtr)(x)})

// I64 clone
I64 I64_clone(const I64 *v);

// I64 arithmetic (shallow params)
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_band(I64 a, I64 b);
I64 I64_bor(I64 a, I64 b);
I64 I64_bxor(I64 a, I64 b);
I64 I64_bnot(I64 a);
I64 I64_shl(I64 a, I64 b);
I64 I64_shr(I64 a, I64 b);

// I64 comparisons
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);

// U8 arithmetic
U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_band(U8 a, U8 b);
U8 U8_bor(U8 a, U8 b);
U8 U8_bxor(U8 a, U8 b);
U8 U8_bnot(U8 a);
U8 U8_shl(U8 a, U8 b);
U8 U8_shr(U8 a, U8 b);

// U8 comparisons
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);

// U8 conversions
I64 U8_to_i64(U8 a);
U64 U8_to_u64(U8 a);
I32 U8_to_i32(U8 a);
U32 U8_to_u32(U8 a);
USize U8_to_usize(U8 a);
F32 U8_to_f32(U8 a);
U8 I64_to_u8(I64 a);
U8 U8_from_i64_ext(const I64 *a);

// U8 clone
U8 U8_clone(const U8 *v);

// I8 arithmetic
I8 I8_add(I8 a, I8 b);
I8 I8_sub(I8 a, I8 b);
I8 I8_mul(I8 a, I8 b);
I8 I8_div(I8 a, I8 b);
I8 I8_mod(I8 a, I8 b);
I8 I8_band(I8 a, I8 b);
I8 I8_bor(I8 a, I8 b);
I8 I8_bxor(I8 a, I8 b);
I8 I8_bnot(I8 a);
I8 I8_shl(I8 a, I8 b);
I8 I8_shr(I8 a, I8 b);

// I8 comparisons
Bool I8_eq(I8 a, I8 b);
I64 I8_cmp(I8 a, I8 b);

// I8 conversions
I64 I8_to_i64(I8 a);
U64 I8_to_u64(I8 a);
I8 I64_to_i8(I64 a);
I8 I8_from_i64_ext(const I64 *a);

// I8 clone
I8 I8_clone(const I8 *v);

// I16 arithmetic
I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_band(I16 a, I16 b);
I16 I16_bor(I16 a, I16 b);
I16 I16_bxor(I16 a, I16 b);
I16 I16_bnot(I16 a);
I16 I16_shl(I16 a, I16 b);
I16 I16_shr(I16 a, I16 b);

// I16 comparisons
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);

// I16 conversions
I64 I16_to_i64(I16 a);
U64 I16_to_u64(I16 a);
U32 I16_to_u32(I16 a);
F32 I16_to_f32(I16 a);
I16 I64_to_i16(I64 a);
I32 I64_to_i32(I64 a);
U32 I64_to_u32(I64 a);
USize I64_to_usize(I64 a);
F32 I64_to_f32(I64 a);
I16 I16_from_i64_ext(const I64 *a);

// I16 clone
I16 I16_clone(const I16 *v);

// U16 arithmetic
U16 U16_add(U16 a, U16 b);
U16 U16_sub(U16 a, U16 b);
U16 U16_mul(U16 a, U16 b);
U16 U16_div(U16 a, U16 b);
U16 U16_mod(U16 a, U16 b);
U16 U16_band(U16 a, U16 b);
U16 U16_bor(U16 a, U16 b);
U16 U16_bxor(U16 a, U16 b);
U16 U16_bnot(U16 a);
U16 U16_shl(U16 a, U16 b);
U16 U16_shr(U16 a, U16 b);

// U16 comparisons
Bool U16_eq(U16 a, U16 b);
I64 U16_cmp(U16 a, U16 b);

// U16 conversions
I64 U16_to_i64(U16 a);
U64 U16_to_u64(U16 a);
U32 U16_to_u32(U16 a);
F32 U16_to_f32(U16 a);
U16 I64_to_u16(I64 a);
U16 U16_from_i64_ext(const I64 *a);

// U16 clone
U16 U16_clone(const U16 *v);

// I32 arithmetic
I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_band(I32 a, I32 b);
I32 I32_bor(I32 a, I32 b);
I32 I32_bxor(I32 a, I32 b);
I32 I32_bnot(I32 a);
I32 I32_shl(I32 a, I32 b);
I32 I32_shr(I32 a, I32 b);

// I32 comparisons
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);

// I32 conversions
I64 I32_to_i64(I32 a);
U64 I32_to_u64(I32 a);
USize I32_to_usize(I32 a);
F32 I32_to_f32(I32 a);
I32 I32_from_i64_ext(const I64 *a);

// I32 clone
I32 I32_clone(const I32 *v);

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
F32 F32_from_i64_ext(const I64 *a);
Str *F32_to_str(F32 v);
Str *F32_to_repr(F32 v);
F32 str_parse_f32(const Str *s);

// F32 clone
F32 F32_clone(const F32 *v);

// U32 arithmetic
U32 U32_add(U32 a, U32 b);
U32 U32_sub(U32 a, U32 b);
U32 U32_mul(U32 a, U32 b);
U32 U32_div(U32 a, U32 b);
U32 U32_mod(U32 a, U32 b);
U32 U32_band(U32 a, U32 b);
U32 U32_bor(U32 a, U32 b);
U32 U32_bxor(U32 a, U32 b);
U32 U32_bnot(U32 a);
U32 U32_shl(U32 a, U32 b);
U32 U32_shr(U32 a, U32 b);

// U32 comparisons
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);

// U32 conversions
I64 U32_to_i64(U32 a);
U64 U32_to_u64(U32 a);
F32 U32_to_f32(U32 a);
U32 U32_from_i64_ext(const I64 *a);

// U32 clone
U32 U32_clone(const U32 *v);

// U64 arithmetic
U64 U64_add(U64 a, U64 b);
U64 U64_sub(U64 a, U64 b);
U64 U64_mul(U64 a, U64 b);
U64 U64_div(U64 a, U64 b);
U64 U64_mod(U64 a, U64 b);
U64 U64_band(U64 a, U64 b);
U64 U64_bor(U64 a, U64 b);
U64 U64_bxor(U64 a, U64 b);
U64 U64_bnot(U64 a);
U64 U64_shl(U64 a, U64 b);
U64 U64_shr(U64 a, U64 b);

// U64 comparisons
Bool U64_eq(U64 a, U64 b);
I64 U64_cmp(U64 a, U64 b);

// U64 conversions
U32 U64_to_u32(U64 a);
I32 U64_to_i32(U64 a);
USize U64_to_usize(U64 a);
F32 U64_to_f32(U64 a);
Str *U64_to_str_ext(U64 v);

// U64 clone
U64 U64_clone(const U64 *v);

// Bool ops (shallow params)
Bool Bool_eq(Bool a, Bool b);
Bool and(Bool a, Bool b);
Bool or(Bool a, Bool b);
Bool not(Bool a);
Bool band(Bool a, Bool b);
Bool bor(Bool a, Bool b);
Bool bxor(Bool a, Bool b);

// Bool clone
Bool Bool_clone(const Bool *v);

// Pointer primitives (custom, not in libc). Inputs stay non-const for
// the pointer-returning ones (ptr_add, to_ptr, deref, get_payload),
// which hand back interior pointers the caller is expected to write
// through, and for write_ptr which mutates dest. is_null and ptr_eq
// only read the pointer values, but adding `const` there makes gcc's
// "may be used uninitialized" analysis stricter on til-emitted call
// sites that follow a buf := alloc-or-NULL ; if (is_null(buf)) {} ;
// use(buf) pattern; the analysis is correct in the abstract but
// chases a real-world non-bug, so keep these non-const for now.
void *ptr_add(void *buf, UPtr offset);
void *to_ptr(void *a);
void *deref(void *slot);
void write_ptr(void *dest, void *val);
/* #211 follow-up: typed primitive writers used by the AST interpreter
 * to mirror writes through payload-aliased bindings. */
void write_i64(void *dest, I64 val);
void write_u8(void *dest, U8 val);
void write_i8(void *dest, I8 val);
void write_i16(void *dest, I16 val);
void write_u16(void *dest, U16 val);
void write_i32(void *dest, I32 val);
void write_u32(void *dest, U32 val);
void write_u64(void *dest, U64 val);
void write_f32(void *dest, F32 val);
void write_bool(void *dest, Bool val);
Bool is(void *self, void *other);
void *get_payload(void *self);

// System primitives
Str *File_readfile(const Str *path);
void File_writefile(const Str *path, const Str *content);
I64 *spawn_cmd(const Str *cmd);
I64 check_cmd_status(I64 pid);
void sleep_ms(I64 ms);
// Empty proc -- callers stick `noop_proc()` inside a func body to force
// precomp to treat the surrounding function as impure (procs are never
// folded). The call has no runtime effect; only purpose is the tag.
void noop_proc(void);
I64 file_mtime(const Str *path);
I64 clock_ms(void);
I64 get_thread_count(void);
U64 peak_rss_bytes(void);
U64 current_rss_bytes(I64 pid);
Str *host_os(void);
I32 mkdir_p(const Str *path);
I32 copy_file(const Str *src, const Str *dst);
I32 copy_tree(const Str *src, const Str *dst);
Bool ptr_eq(void *a, void *b);
void eprint_single(const Str *s);

// File handle I/O. The void * handle is opaque; til-side bindings take
// it non-mut, but the underlying FILE * state is mutated by the call,
// so handle stays non-const.
void *cfile_open(const Str *path, Bool is_write);
void *cfile_open_update(const Str *path);
void cfile_close(void *handle);
void cfile_write_str(void *handle, const Str *s);
Str *cfile_read_all(void *handle);
I64 cfile_tell(void *handle);
void cfile_seek(void *handle, I64 pos);
void cfile_seek_cur(void *handle, I64 delta);
void cfile_seek_end(void *handle, I64 delta);
Str *cfile_read_n(void *handle, I64 count);

// Line input. The til-side binding declares `mut line: Str`, so line
// is mutated by this call -- keep it non-const.
Bool in_read_line(Str *line);
