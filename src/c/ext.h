#ifndef TIL_EXT_H
#define TIL_EXT_H

#include "ccore.h"

typedef I64 til_I64;
typedef U8 til_U8;
typedef I16 til_I16;
typedef I32 til_I32;
typedef U32 til_U32;
typedef Bool til_Bool;

typedef struct til_Str {
    til_U8 *data;
    til_I64 count;
    til_I64 cap;
} til_Str;

typedef struct til_Array {
    til_U8 *data;       // raw element buffer
    til_I64 cap;        // number of elements
    til_I64 elem_size;  // bytes per element
    til_Str elem_type;  // element type name
} til_Array;

// Get pointer to element i in a til_Array (C-side helper, not the til function)
static inline void *til_Array_elem(til_Array *a, til_I64 i) {
    return a->data + i * a->elem_size;
}

void til_free(void *ptr);
void til_exit(til_I64 *code);

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
til_I64 *til_I64_cmp(til_I64 *a, til_I64 *b);

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
til_I64 *til_U8_cmp(til_U8 *a, til_U8 *b);

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a);
til_U8 *til_U8_from_i64_ext(til_I64 *a);

// U8 clone/delete
til_U8 *til_U8_clone(til_U8 *v);
void til_U8_delete(til_U8 *v, til_Bool *call_free);

// I16 arithmetic
til_I16 *til_I16_add(til_I16 *a, til_I16 *b);
til_I16 *til_I16_sub(til_I16 *a, til_I16 *b);
til_I16 *til_I16_mul(til_I16 *a, til_I16 *b);
til_I16 *til_I16_div(til_I16 *a, til_I16 *b);
til_I16 *til_I16_mod(til_I16 *a, til_I16 *b);
til_I16 *til_I16_and(til_I16 *a, til_I16 *b);
til_I16 *til_I16_or(til_I16 *a, til_I16 *b);
til_I16 *til_I16_xor(til_I16 *a, til_I16 *b);

// I16 comparisons
til_Bool *til_I16_eq(til_I16 *a, til_I16 *b);
til_I64 *til_I16_cmp(til_I16 *a, til_I16 *b);

// I16 conversions
til_I64 *til_I16_to_i64(til_I16 *a);
til_I16 *til_I16_from_i64_ext(til_I64 *a);

// I16 clone/delete
til_I16 *til_I16_clone(til_I16 *v);
void til_I16_delete(til_I16 *v, til_Bool *call_free);

// I16 CLI
til_I16 *til_cli_parse_i16(const char *s);

// I32 arithmetic
til_I32 *til_I32_add(til_I32 *a, til_I32 *b);
til_I32 *til_I32_sub(til_I32 *a, til_I32 *b);
til_I32 *til_I32_mul(til_I32 *a, til_I32 *b);
til_I32 *til_I32_div(til_I32 *a, til_I32 *b);
til_I32 *til_I32_mod(til_I32 *a, til_I32 *b);
til_I32 *til_I32_and(til_I32 *a, til_I32 *b);
til_I32 *til_I32_or(til_I32 *a, til_I32 *b);
til_I32 *til_I32_xor(til_I32 *a, til_I32 *b);

// I32 comparisons
til_Bool *til_I32_eq(til_I32 *a, til_I32 *b);
til_I64 *til_I32_cmp(til_I32 *a, til_I32 *b);

// I32 conversions
til_I64 *til_I32_to_i64(til_I32 *a);
til_I32 *til_I32_from_i64_ext(til_I64 *a);

// I32 clone/delete
til_I32 *til_I32_clone(til_I32 *v);
void til_I32_delete(til_I32 *v, til_Bool *call_free);

// I32 CLI
til_I32 *til_cli_parse_i32(const char *s);

// U32 arithmetic
til_U32 *til_U32_add(til_U32 *a, til_U32 *b);
til_U32 *til_U32_sub(til_U32 *a, til_U32 *b);
til_U32 *til_U32_mul(til_U32 *a, til_U32 *b);
til_U32 *til_U32_div(til_U32 *a, til_U32 *b);
til_U32 *til_U32_mod(til_U32 *a, til_U32 *b);
til_U32 *til_U32_and(til_U32 *a, til_U32 *b);
til_U32 *til_U32_or(til_U32 *a, til_U32 *b);
til_U32 *til_U32_xor(til_U32 *a, til_U32 *b);

// U32 comparisons
til_Bool *til_U32_eq(til_U32 *a, til_U32 *b);
til_I64 *til_U32_cmp(til_U32 *a, til_U32 *b);

// U32 conversions
til_I64 *til_U32_to_i64(til_U32 *a);
til_U32 *til_U32_from_i64_ext(til_I64 *a);

// U32 clone/delete
til_U32 *til_U32_clone(til_U32 *v);
void til_U32_delete(til_U32 *v, til_Bool *call_free);

// Bool ops
til_Bool *til_Bool_eq(til_Bool *a, til_Bool *b);
til_Bool *til_and(til_Bool *a, til_Bool *b);
til_Bool *til_or(til_Bool *a, til_Bool *b);
til_Bool *til_not(til_Bool *a);

void til_memmove(void *dest, void *src, til_I64 *len);

// Bool clone/delete
til_Bool *til_Bool_clone(til_Bool *v);
void til_Bool_delete(til_Bool *v, til_Bool *call_free);

// Pointer primitives
void *til_malloc(til_I64 *count);
void *til_realloc(void *buf, til_I64 *count);
void *til_ptr_add(void *buf, til_I64 *offset);
void til_memcpy(void *dest, void *src, til_I64 *len);

// CLI arg parsing
til_I64 *til_cli_parse_i64(const char *s);
til_U8 *til_cli_parse_u8(const char *s);
til_U32 *til_cli_parse_u32(const char *s);
til_Bool *til_cli_parse_bool(const char *s);

// System primitives
til_Str *til_readfile(til_Str *path);
void til_writefile(til_Str *path, til_Str *content);
til_I64 *til_spawn_cmd(til_Str *cmd);
til_I64 *til_check_cmd_status(til_I64 *pid);
void til_sleep(til_I64 *ms);
til_I64 *til_file_mtime(til_Str *path);
til_I64 *til_clock_ms(void);
til_I64 *til_get_thread_count(void);

#endif
