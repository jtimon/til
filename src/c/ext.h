#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

typedef long long I64;
typedef unsigned long long U64;
typedef int I32;
typedef unsigned int U32;
typedef short I16;
typedef unsigned short U16;
// I8 must stay plain char: ext_func bindings of libc functions
// (setenv, getenv, ...) re-declare them with til types, and any other
// char spelling conflicts with the libc headers' own prototypes. Plain
// char is unsigned on aarch64/arm Linux ABIs though, which silently
// flipped I8 unsigned there (found by the first native arm64 suite
// run, issue #25) -- so every til compile passes -fsigned-char
// (toolchain_extra_args, the Makefile cc lines, and the FFI user-.so
// compile), pinning plain char signed on every platform. The guard
// below turns any compile that misses the flag (e.g. building the
// generated C by hand on an ARM box) into a loud error at the first
// include instead of silently flipping I8's semantics.
#if CHAR_MIN == 0
#error "til requires plain char to be signed (I8 == char must match libc prototypes yet behave signed). Add -fsigned-char to this compile; every til-driven build passes it already."
#endif
typedef char I8;
typedef unsigned char U8;
typedef float F32;
// til's 64-bit float (C double). Introduced for #333: C `double`
// signatures were unbindable. The compiler's own .til source cannot
// mention F64 until a compiler that knows it is the bootstrap (the
// preparation/use split in doc/self.org), so the interpreter handles
// F64 values as U64 bit words through the f64_bits_* helpers below --
// the same shape as f32_word/word_f32.
typedef double F64;
typedef bool Bool;
// container sizes (count, cap, elem_size) and raw pointer/byte widths.
// UPtr always follows the C pointer width (real pointer arithmetic needs
// it). USize defaults to U32 (issue #309): container index/count/cap/size
// fields stay 32-bit even on a 64-bit host, so containers are smaller while
// UPtr keeps pointer width. `til --usize=64` passes -DTIL_USIZE64 to cc for
// the opt-out (U64 container fields, matching the source alias the compiler
// used at typecheck/constfold).
#if defined(TIL_USIZE64)
typedef U64 USize;
#else
typedef U32 USize;
#endif
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

// I64 comparisons
I64 I64_cmp(I64 a, I64 b);

// U8 comparisons
I64 U8_cmp(U8 a, U8 b);

// U8 conversions
I64 U8_to_i64(U8 a);
I32 U8_to_i32(U8 a);
USize U8_to_usize(U8 a);
F32 U8_to_f32(U8 a);
U8 I64_to_u8(I64 a);
U8 U8_from_i64_ext(const I64 *a);

// U8 clone
U8 U8_clone(const U8 *v);

// I8 comparisons
I64 I8_cmp(I8 a, I8 b);

// I8 conversions
U64 I8_to_u64(I8 a);
I8 I64_to_i8(I64 a);
I8 I8_from_i64_ext(const I64 *a);

// I8 clone
I8 I8_clone(const I8 *v);

// I16 comparisons
I64 I16_cmp(I16 a, I16 b);

// I16 conversions
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

// U16 comparisons
I64 U16_cmp(U16 a, U16 b);

// U16 conversions
I64 U16_to_i64(U16 a);
F32 U16_to_f32(U16 a);
U16 I64_to_u16(I64 a);
U16 U16_from_i64_ext(const I64 *a);

// U16 clone
U16 U16_clone(const U16 *v);

// I32 comparisons
I64 I32_cmp(I32 a, I32 b);

// I32 conversions
U64 I32_to_u64(I32 a);
USize I32_to_usize(I32 a);
F32 I32_to_f32(I32 a);
I32 I32_from_i64_ext(const I64 *a);

// I32 clone
I32 I32_clone(const I32 *v);

// F32 comparisons
I64 F32_cmp(F32 a, F32 b);

// F32 conversions
I64 F32_to_i64(F32 a);
F32 F32_from_i64_ext(const I64 *a);
Str *F32_to_str(F32 v);
Str *F32_to_repr(F32 v);
F32 str_parse_f32(const Str *s);

// F32 clone
F32 F32_clone(const F32 *v);

// F64 comparisons
I64 F64_cmp(F64 a, F64 b);

// F64 conversions
I64 F64_to_i64(F64 a);
F32 F64_to_f32(F64 a);
F64 F32_to_f64(F32 a);
F64 I64_to_f64(I64 a);
F64 U64_to_f64(U64 a);
F64 F64_from_i64_ext(const I64 *a);
Str *F64_to_str(F64 v);
Str *F64_to_repr(F64 v);
F64 str_parse_f64(const Str *s);

// F64 clone
F64 F64_clone(const F64 *v);

// U32 comparisons
I64 U32_cmp(U32 a, U32 b);

// U32 conversions
I64 U32_to_i64(U32 a);
I32 U32_to_i32(U32 a);
U32 U32_to_u32(U32 a);
U64 U32_to_u64(U32 a);
F32 U32_to_f32(U32 a);
U32 U32_from_i64_ext(const I64 *a);

// U32 clone
U32 U32_clone(const U32 *v);

// U64 comparisons
I64 U64_cmp(U64 a, U64 b);

// U64 conversions
U32 U64_to_u32(U64 a);
I32 U64_to_i32(U64 a);
I64 U64_to_i64(U64 a);
U64 U64_to_u64(U64 a);
USize U64_to_usize(U64 a);
F32 U64_to_f32(U64 a);
Str *U64_to_str_ext(U64 v);

// U64 clone
U64 U64_clone(const U64 *v);

// Bool clone
Bool Bool_clone(const Bool *v);

// Pointer primitives (custom, not in libc). Inputs stay non-const for
// the pointer-returning ones (to_ptr, deref),
// which hand back interior pointers the caller is expected to write
// through, and for write_ptr which mutates dest. is_null and ptr_eq
// only read the pointer values, but adding `const` there makes gcc's
// "may be used uninitialized" analysis stricter on til-emitted call
// sites that follow a buf := alloc-or-NULL ; if (is_null(buf)) {} ;
// use(buf) pattern; the analysis is correct in the abstract but
// chases a real-world non-bug, so keep these non-const for now.
void *to_ptr(void *a);
void *deref(void *slot);
void write_ptr(void *dest, void *val);
void til_closure_slot_take(void *slot, void *closure);
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
void write_f64(void *dest, F64 val);
void write_bool(void *dest, Bool val);

// System primitives
void stdio_capture_begin(const Str *path);
void stdio_capture_end(void);
Str *doc_org_load_core_info(const Str *index_path);
Str *doc_org_load_core_docs(const Str *index_path);
Str *doc_blob_lookup(const Str *blob, const Str *name);
I64 *spawn_cmd(const Str *cmd);
I64 check_cmd_status(I64 pid);
void sleep_ms(I64 ms);
// Empty proc -- callers stick `noop_proc()` inside a func body to force
// constfolder to treat the surrounding function as impure (procs are never
// folded). The call has no runtime effect; only purpose is the tag.
void noop_proc(void);
I64 file_mtime(const Str *path);
I64 clock_ms(void);
I64 get_thread_count(void);
U64 peak_rss_bytes(void);
U64 current_rss_bytes(I64 pid);
Str *host_os(void);
Str *host_arch(void);
I32 mkdir_p(const Str *path);
I32 copy_file(const Str *src, const Str *dst);
I32 copy_tree(const Str *src, const Str *dst);
Bool ptr_eq(void *a, void *b);
U64 word_bits(const void *w);
void *bits_word(U64 b);
U64 f32_word(F32 f);
F32 word_f32(U64 b);
/* F64 <-> U64 bit words, plus operate-on-bits helpers. The til-side
 * interpreter binds THESE (U64-only signatures) rather than F64-typed
 * functions: its own source is compiled by the previous bootstrap
 * compiler, which does not know the F64 type yet. */
U64 f64_word(F64 f);
F64 word_f64(U64 b);
U64 f64_bits_add(U64 a, U64 b);
U64 f64_bits_sub(U64 a, U64 b);
U64 f64_bits_mul(U64 a, U64 b);
U64 f64_bits_div(U64 a, U64 b);
I64 f64_bits_cmp(U64 a, U64 b);
U64 str_parse_f64_bits(const Str *s);
Str *f64_bits_to_str(U64 b);
Str *f64_bits_to_repr(U64 b);
U64 f64_bits_from_i64(I64 v);
void word_drop(void *w);
void *dispatch_scratch_base(void);
void *word_ring_base(void);
void eprint_single(const Str *s);

// File handle I/O. The void * handle is opaque; the til-side bindings
// (src/std/file.til) take it as a non-mut Dynamic, and the builder's FFI
// const convention emits those params as `const void *`, so the handle
// is const here and each body casts it back to FILE * (the FILE state
// itself is of course mutated by the call).
void *cfile_open(const Str *path, Bool is_write);
void *cfile_open_update(const Str *path);
void *cfile_open_append(const Str *path);
Bool cfile_exists(const Str *path);
void cfile_close(const void *handle);
void cfile_write_str(const void *handle, const Str *s);
Str *cfile_read_all(const void *handle);
I64 cfile_tell(const void *handle);
void cfile_seek(const void *handle, I64 pos);
void cfile_seek_cur(const void *handle, I64 delta);
void cfile_seek_end(const void *handle, I64 delta);
Str *cfile_read_n(const void *handle, I64 count);

// Directory reading, path types, tree removal and rename (issue #345).
// cdir_* follows the cfile_* handle convention above; cdir_next answers
// "" when the directory is exhausted, never reporting "." or "..".
void *cdir_open(const Str *path);
Str *cdir_next(const void *handle);
void cdir_close(const void *handle);
Bool cpath_is_dir(const Str *path);
Bool cpath_is_file(const Str *path);
I32 cremove_tree(const Str *path);
I32 crename_path(const Str *src, const Str *dst);

// Argv-based process execution (issue #345). A command is accumulated
// element by element and then run, so no argument is ever re-parsed by
// a shell -- see the header comment in ext.c. Same opaque-handle
// convention as cfile_*.
void *ccmd_new(void);
void ccmd_arg(const void *handle, const Str *arg);
void ccmd_cwd(const void *handle, const Str *dir);
void ccmd_env(const void *handle, const Str *name, const Str *value);
void ccmd_stdout_file(const void *handle, const Str *path);
void ccmd_stderr_file(const void *handle, const Str *path);
void ccmd_stderr_to_stdout(const void *handle);
void ccmd_capture(const void *handle, Bool out, Bool err);
Str *ccmd_render(const void *handle);
I64 ccmd_start(const void *handle);
I64 ccmd_wait(const void *handle);
Bool ccmd_poll(const void *handle);
I64 ccmd_status(const void *handle);
Str *ccmd_out(const void *handle);
Str *ccmd_err(const void *handle);
void ccmd_free(const void *handle);

// Line input. The til-side binding declares `mut line: Str`, so line
// is mutated by this call -- keep it non-const.
Bool in_read_line(Str *line);

// --- REPL line editor bridge (issue #332) ---
//
// The editor itself (key handling, history policy, rendering, ANSI
// decoding) lives in src/self/repl_editor.til. Only the operations that
// cannot be expressed portably in til are here: terminal detection, the
// raw-mode interval, one input event, the column count, and the atomic
// history replacement.
//
// repl_term_read_event returns one EVENT. Ordinary input bytes come back
// as 0..255; everything else is one of the disjoint negative codes below.
// POSIX hands back raw bytes and lets til decode the ANSI sequences;
// native Windows maps console key events onto the same TIL_KEY_* codes
// before returning, so both sides feed the editor the same alphabet.
// src/self/repl_editor.til mirrors these values as REPL_KEY_* constants.
#define TIL_KEY_EOF     (-1)
#define TIL_KEY_TIMEOUT (-2)
#define TIL_KEY_REDRAW  (-3)
#define TIL_KEY_ERROR   (-4)
#define TIL_KEY_UP      (-10)
#define TIL_KEY_DOWN    (-11)
#define TIL_KEY_RIGHT   (-12)
#define TIL_KEY_LEFT    (-13)
#define TIL_KEY_HOME    (-14)
#define TIL_KEY_END     (-15)
#define TIL_KEY_DELETE  (-16)

Bool repl_term_is_interactive(void);
Bool repl_term_begin(void);
void repl_term_end(void);
void repl_term_flush(void);
I64 repl_term_read_event(I64 timeout_ms);
I64 repl_term_columns(void);
// History file I/O. Both report failure through their return value
// (0 = done, 1 = no such file, 2 = error described in *err) instead of
// exiting the way cfile_open does: a REPL whose history file is
// unreadable must keep running with in-memory history, and it must say
// so rather than pretend the write happened.
I64 repl_history_read(const Str *path, Str *out, Str *err);
I64 repl_history_write(const Str *path, const Str *contents, Str *err);
