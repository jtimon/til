#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

// Internal helpers for heap-allocating scalar values (pointer ABI)
static I64 *new_i64(I64 v) { I64 *r = malloc(sizeof(I64)); *r = v; return r; }
static U8 *new_u8(U8 v) { U8 *r = malloc(sizeof(U8)); *r = v; return r; }
static I16 *new_i16(I16 v) { I16 *r = malloc(sizeof(I16)); *r = v; return r; }
static I32 *new_i32(I32 v) { I32 *r = malloc(sizeof(I32)); *r = v; return r; }
static U32 *new_u32(U32 v) { U32 *r = malloc(sizeof(U32)); *r = v; return r; }
static Bool *new_bool(Bool v) { Bool *r = malloc(sizeof(Bool)); *r = v; return r; }

void exit_program(I64 *code) { exit((int)*code); }

// I64 clone/delete
I64 *I64_clone(I64 *v) { return new_i64(*v); }
void I64_delete(I64 *v, Bool *call_free) { if (*call_free) free(v); }

// I64 arithmetic
I64 *I64_add(I64 *a, I64 *b) { return new_i64(*a + *b); }
I64 *I64_sub(I64 *a, I64 *b) { return new_i64(*a - *b); }
I64 *I64_mul(I64 *a, I64 *b) { return new_i64(*a * *b); }
I64 *I64_div(I64 *a, I64 *b) { return new_i64(*a / *b); }
I64 *I64_mod(I64 *a, I64 *b) { return new_i64(*a % *b); }
I64 *I64_and(I64 *a, I64 *b) { return new_i64(*a & *b); }
I64 *I64_or(I64 *a, I64 *b) { return new_i64(*a | *b); }
I64 *I64_xor(I64 *a, I64 *b) { return new_i64(*a ^ *b); }

// I64 inc/dec
I64 *I64_inc(I64 *a) { return new_i64(*a + 1); }
I64 *I64_dec(I64 *a) { return new_i64(*a - 1); }

// I64 comparisons
Bool *I64_eq(I64 *a, I64 *b) { return new_bool(*a == *b); }
I64 *I64_cmp(I64 *a, I64 *b) { return new_i64((*a > *b) ? 1 : (*a < *b) ? -1 : 0); }

// U8 arithmetic
U8 *U8_add(U8 *a, U8 *b) { return new_u8(*a + *b); }
U8 *U8_sub(U8 *a, U8 *b) { return new_u8(*a - *b); }
U8 *U8_mul(U8 *a, U8 *b) { return new_u8(*a * *b); }
U8 *U8_div(U8 *a, U8 *b) { return new_u8(*a / *b); }
U8 *U8_mod(U8 *a, U8 *b) { return new_u8(*a % *b); }
U8 *U8_and(U8 *a, U8 *b) { return new_u8(*a & *b); }
U8 *U8_or(U8 *a, U8 *b) { return new_u8(*a | *b); }
U8 *U8_xor(U8 *a, U8 *b) { return new_u8(*a ^ *b); }

// U8 inc/dec
U8 *U8_inc(U8 *a) { return new_u8(*a + 1); }
U8 *U8_dec(U8 *a) { return new_u8(*a - 1); }

// U8 comparisons
Bool *U8_eq(U8 *a, U8 *b) { return new_bool(*a == *b); }
I64 *U8_cmp(U8 *a, U8 *b) { return new_i64((*a > *b) ? 1 : (*a < *b) ? -1 : 0); }

// U8 conversions
I64 *U8_to_i64(U8 *a) { return new_i64((I64)*a); }
U8 *U8_from_i64_ext(I64 *a) { return new_u8((U8)*a); }

// U8 clone/delete
U8 *U8_clone(U8 *v) { return new_u8(*v); }
void U8_delete(U8 *v, Bool *call_free) { if (*call_free) free(v); }

// I16 arithmetic
I16 *I16_add(I16 *a, I16 *b) { return new_i16(*a + *b); }
I16 *I16_sub(I16 *a, I16 *b) { return new_i16(*a - *b); }
I16 *I16_mul(I16 *a, I16 *b) { return new_i16(*a * *b); }
I16 *I16_div(I16 *a, I16 *b) { return new_i16(*a / *b); }
I16 *I16_mod(I16 *a, I16 *b) { return new_i16(*a % *b); }
I16 *I16_and(I16 *a, I16 *b) { return new_i16(*a & *b); }
I16 *I16_or(I16 *a, I16 *b) { return new_i16(*a | *b); }
I16 *I16_xor(I16 *a, I16 *b) { return new_i16(*a ^ *b); }

// I16 inc/dec
I16 *I16_inc(I16 *a) { return new_i16(*a + 1); }
I16 *I16_dec(I16 *a) { return new_i16(*a - 1); }

// I16 comparisons
Bool *I16_eq(I16 *a, I16 *b) { return new_bool(*a == *b); }
I64 *I16_cmp(I16 *a, I16 *b) { return new_i64((*a > *b) ? 1 : (*a < *b) ? -1 : 0); }

// I16 conversions
I64 *I16_to_i64(I16 *a) { return new_i64((I64)*a); }
I16 *I16_from_i64_ext(I64 *a) { return new_i16((I16)*a); }

// I16 clone/delete
I16 *I16_clone(I16 *v) { return new_i16(*v); }
void I16_delete(I16 *v, Bool *call_free) { if (*call_free) free(v); }

// I16 CLI
I16 *cli_parse_i16(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < -32768 || v > 32767) {
        fprintf(stderr, "error: cannot parse '%s' as I16\n", s);
        exit(1);
    }
    return new_i16((I16)v);
}

// I32 arithmetic
I32 *I32_add(I32 *a, I32 *b) { return new_i32(*a + *b); }
I32 *I32_sub(I32 *a, I32 *b) { return new_i32(*a - *b); }
I32 *I32_mul(I32 *a, I32 *b) { return new_i32(*a * *b); }
I32 *I32_div(I32 *a, I32 *b) { return new_i32(*a / *b); }
I32 *I32_mod(I32 *a, I32 *b) { return new_i32(*a % *b); }
I32 *I32_and(I32 *a, I32 *b) { return new_i32(*a & *b); }
I32 *I32_or(I32 *a, I32 *b) { return new_i32(*a | *b); }
I32 *I32_xor(I32 *a, I32 *b) { return new_i32(*a ^ *b); }

// I32 inc/dec
I32 *I32_inc(I32 *a) { return new_i32(*a + 1); }
I32 *I32_dec(I32 *a) { return new_i32(*a - 1); }

// I32 comparisons
Bool *I32_eq(I32 *a, I32 *b) { return new_bool(*a == *b); }
I64 *I32_cmp(I32 *a, I32 *b) { return new_i64((*a > *b) ? 1 : (*a < *b) ? -1 : 0); }

// I32 conversions
I64 *I32_to_i64(I32 *a) { return new_i64((I64)*a); }
I32 *I32_from_i64_ext(I64 *a) { return new_i32((I32)*a); }

// I32 clone/delete
I32 *I32_clone(I32 *v) { return new_i32(*v); }
void I32_delete(I32 *v, Bool *call_free) { if (*call_free) free(v); }

// I32 CLI
I32 *cli_parse_i32(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < -2147483648L || v > 2147483647L) {
        fprintf(stderr, "error: cannot parse '%s' as I32\n", s);
        exit(1);
    }
    return new_i32((I32)v);
}

// U32 arithmetic
U32 *U32_add(U32 *a, U32 *b) { return new_u32(*a + *b); }
U32 *U32_sub(U32 *a, U32 *b) { return new_u32(*a - *b); }
U32 *U32_mul(U32 *a, U32 *b) { return new_u32(*a * *b); }
U32 *U32_div(U32 *a, U32 *b) { return new_u32(*a / *b); }
U32 *U32_mod(U32 *a, U32 *b) { return new_u32(*a % *b); }
U32 *U32_and(U32 *a, U32 *b) { return new_u32(*a & *b); }
U32 *U32_or(U32 *a, U32 *b) { return new_u32(*a | *b); }
U32 *U32_xor(U32 *a, U32 *b) { return new_u32(*a ^ *b); }

// U32 inc/dec
U32 *U32_inc(U32 *a) { return new_u32(*a + 1); }
U32 *U32_dec(U32 *a) { return new_u32(*a - 1); }

// U32 comparisons
Bool *U32_eq(U32 *a, U32 *b) { return new_bool(*a == *b); }
I64 *U32_cmp(U32 *a, U32 *b) { return new_i64((*a > *b) ? 1 : (*a < *b) ? -1 : 0); }

// U32 conversions
I64 *U32_to_i64(U32 *a) { return new_i64((I64)*a); }
U32 *U32_from_i64_ext(I64 *a) { return new_u32((U32)*a); }

// U32 clone/delete
U32 *U32_clone(U32 *v) { return new_u32(*v); }
void U32_delete(U32 *v, Bool *call_free) { if (*call_free) free(v); }

// Bool ops
Bool *Bool_eq(Bool *a, Bool *b) { return new_bool(*a == *b); }
Bool *Bool_and(Bool *a, Bool *b) { return new_bool(*a && *b); }
Bool *Bool_or(Bool *a, Bool *b) { return new_bool(*a || *b); }
Bool *Bool_not(Bool *a) { return new_bool(!*a); }

// Bool clone/delete
Bool *Bool_clone(Bool *v) { return new_bool(*v); }
void Bool_delete(Bool *v, Bool *call_free) { if (*call_free) free(v); }

// Pointer primitives
void *til_malloc(I64 *count) { return calloc(1, (size_t)*count); }
void *til_realloc(void *buf, I64 *count) { return realloc(buf, (size_t)*count); }
void *ptr_add(void *buf, I64 *offset) {
    return (char *)buf + *offset;
}
void til_memcpy(void *dest, void *src, I64 *len) {
    memcpy(dest, src, (size_t)*len);
}
void til_memmove(void *dest, void *src, I64 *len) {
    memmove(dest, src, (size_t)*len);
}

// CLI arg parsing
I64 *cli_parse_i64(const char *s) {
    char *end;
    I64 v = strtoll(s, &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "error: cannot parse '%s' as I64\n", s);
        exit(1);
    }
    return new_i64(v);
}
U8 *cli_parse_u8(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < 0 || v > 255) {
        fprintf(stderr, "error: cannot parse '%s' as U8\n", s);
        exit(1);
    }
    return new_u8((U8)v);
}
U32 *cli_parse_u32(const char *s) {
    char *end;
    unsigned long v = strtoul(s, &end, 10);
    if (*end != '\0' || v > 0xFFFFFFFF) {
        fprintf(stderr, "error: cannot parse '%s' as U32\n", s);
        exit(1);
    }
    return new_u32((U32)v);
}
Bool *cli_parse_bool(const char *s) {
    if (strcmp(s, "true") == 0) return new_bool(1);
    if (strcmp(s, "false") == 0) return new_bool(0);
    fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
    exit(1);
}

// --- System primitives ---
// These use Str (codegen layout: { U8 *data, I64 count, I64 cap }) rather than
// the compiler-internal Str ({ char *c_str, I64 count, I64 cap }).
// For the interpreter, dispatch.c has its own handlers using the compiler Str directly.

Str *readfile(Str *path) {
    char *p = strndup((char *)path->data, path->count);
    FILE *f = fopen(p, "rb");
    if (!f) {
        fprintf(stderr, "readfile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len);
    fread(buf, 1, len, f);
    fclose(f);
    Str *s = malloc(sizeof(Str));
    s->data = (U8 *)buf;
    s->count = len;
    s->cap = len;
    return s;
}

void writefile(Str *path, Str *content) {
    char *p = strndup((char *)path->data, path->count);
    FILE *f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fwrite(content->data, 1, content->count, f);
    fclose(f);
}

I64 *spawn_cmd(Str *cmd) {
    char *c = strndup((char *)cmd->data, cmd->count);
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", c, NULL);
        _exit(127);
    }
    free(c);
    if (pid < 0) {
        fprintf(stderr, "spawn_cmd: fork failed\n");
        exit(1);
    }
    return new_i64((I64)pid);
}

I64 *check_cmd_status(I64 *pid) {
    I32 status;
    pid_t result = waitpid((pid_t)*pid, &status, WNOHANG);
    if (result == 0) return new_i64(-1);
    if (WIFEXITED(status)) return new_i64(WEXITSTATUS(status));
    return new_i64(-1);
}

void sleep_ms(I64 *ms) {
    usleep((useconds_t)(*ms * 1000));
}

I64 *file_mtime(Str *path) {
    char *p = strndup((char *)path->data, path->count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return new_i64(-1);
    return new_i64((I64)st.st_mtime);
}

I64 *clock_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return new_i64((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
}

I64 *get_thread_count(void) {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return new_i64(count > 0 ? (I64)count : 1);
}
