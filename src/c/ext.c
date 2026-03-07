#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

void til_free(void *ptr) { free(ptr); }
void til_exit(til_I64 *code) { exit((int)*code); }

// I64 clone/delete
til_I64 *til_I64_clone(til_I64 *v) { return I64_clone(v); }
void til_I64_delete(til_I64 *v, til_Bool *call_free) { if (*call_free) I64_delete(v); }

// I64 arithmetic
til_I64 *til_I64_add(til_I64 *a, til_I64 *b) { return I64_new(I64_add(*a, *b)); }
til_I64 *til_I64_sub(til_I64 *a, til_I64 *b) { return I64_new(I64_sub(*a, *b)); }
til_I64 *til_I64_mul(til_I64 *a, til_I64 *b) { return I64_new(I64_mul(*a, *b)); }
til_I64 *til_I64_div(til_I64 *a, til_I64 *b) { return I64_new(I64_div(*a, *b)); }
til_I64 *til_I64_mod(til_I64 *a, til_I64 *b) { return I64_new(I64_mod(*a, *b)); }
til_I64 *til_I64_and(til_I64 *a, til_I64 *b) { return I64_new(I64_and(*a, *b)); }
til_I64 *til_I64_or(til_I64 *a, til_I64 *b) { return I64_new(I64_or(*a, *b)); }
til_I64 *til_I64_xor(til_I64 *a, til_I64 *b) { return I64_new(I64_xor(*a, *b)); }

// I64 comparisons
til_Bool *til_I64_eq(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_eq(*a, *b); return r; }
til_I64 *til_I64_cmp(til_I64 *a, til_I64 *b) { return I64_new(I64_cmp(*a, *b)); }

// U8 arithmetic
til_U8 *til_U8_add(til_U8 *a, til_U8 *b) { return U8_new(U8_add(*a, *b)); }
til_U8 *til_U8_sub(til_U8 *a, til_U8 *b) { return U8_new(U8_sub(*a, *b)); }
til_U8 *til_U8_mul(til_U8 *a, til_U8 *b) { return U8_new(U8_mul(*a, *b)); }
til_U8 *til_U8_div(til_U8 *a, til_U8 *b) { return U8_new(U8_div(*a, *b)); }
til_U8 *til_U8_mod(til_U8 *a, til_U8 *b) { return U8_new(U8_mod(*a, *b)); }
til_U8 *til_U8_and(til_U8 *a, til_U8 *b) { return U8_new(U8_and(*a, *b)); }
til_U8 *til_U8_or(til_U8 *a, til_U8 *b) { return U8_new(U8_or(*a, *b)); }
til_U8 *til_U8_xor(til_U8 *a, til_U8 *b) { return U8_new(U8_xor(*a, *b)); }

// U8 comparisons
til_Bool *til_U8_eq(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_eq(*a, *b); return r; }
til_I64 *til_U8_cmp(til_U8 *a, til_U8 *b) { return I64_new(U8_cmp(*a, *b)); }

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a) { return I64_new(U8_to_i64(*a)); }
til_U8 *til_U8_from_i64_ext(til_I64 *a) { return U8_new(U8_from_i64(*a)); }

// U8 clone/delete
til_U8 *til_U8_clone(til_U8 *v) { return U8_clone(v); }
void til_U8_delete(til_U8 *v, til_Bool *call_free) { if (*call_free) U8_delete(v); }

// I16 arithmetic
til_I16 *til_I16_add(til_I16 *a, til_I16 *b) { return I16_new(I16_add(*a, *b)); }
til_I16 *til_I16_sub(til_I16 *a, til_I16 *b) { return I16_new(I16_sub(*a, *b)); }
til_I16 *til_I16_mul(til_I16 *a, til_I16 *b) { return I16_new(I16_mul(*a, *b)); }
til_I16 *til_I16_div(til_I16 *a, til_I16 *b) { return I16_new(I16_div(*a, *b)); }
til_I16 *til_I16_mod(til_I16 *a, til_I16 *b) { return I16_new(I16_mod(*a, *b)); }
til_I16 *til_I16_and(til_I16 *a, til_I16 *b) { return I16_new(I16_and(*a, *b)); }
til_I16 *til_I16_or(til_I16 *a, til_I16 *b) { return I16_new(I16_or(*a, *b)); }
til_I16 *til_I16_xor(til_I16 *a, til_I16 *b) { return I16_new(I16_xor(*a, *b)); }

// I16 comparisons
til_Bool *til_I16_eq(til_I16 *a, til_I16 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I16_eq(*a, *b); return r; }
til_I64 *til_I16_cmp(til_I16 *a, til_I16 *b) { return I64_new(I16_cmp(*a, *b)); }

// I16 conversions
til_I64 *til_I16_to_i64(til_I16 *a) { return I64_new(I16_to_i64(*a)); }
til_I16 *til_I16_from_i64_ext(til_I64 *a) { return I16_new(I16_from_i64(*a)); }

// I16 clone/delete
til_I16 *til_I16_clone(til_I16 *v) { return I16_clone(v); }
void til_I16_delete(til_I16 *v, til_Bool *call_free) { if (*call_free) I16_delete(v); }

// I16 CLI
til_I16 *til_cli_parse_i16(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < -32768 || v > 32767) {
        fprintf(stderr, "error: cannot parse '%s' as I16\n", s);
        exit(1);
    }
    return I16_new((I16)v);
}

// I32 arithmetic
til_I32 *til_I32_add(til_I32 *a, til_I32 *b) { return I32_new(I32_add(*a, *b)); }
til_I32 *til_I32_sub(til_I32 *a, til_I32 *b) { return I32_new(I32_sub(*a, *b)); }
til_I32 *til_I32_mul(til_I32 *a, til_I32 *b) { return I32_new(I32_mul(*a, *b)); }
til_I32 *til_I32_div(til_I32 *a, til_I32 *b) { return I32_new(I32_div(*a, *b)); }
til_I32 *til_I32_mod(til_I32 *a, til_I32 *b) { return I32_new(I32_mod(*a, *b)); }
til_I32 *til_I32_and(til_I32 *a, til_I32 *b) { return I32_new(I32_and(*a, *b)); }
til_I32 *til_I32_or(til_I32 *a, til_I32 *b) { return I32_new(I32_or(*a, *b)); }
til_I32 *til_I32_xor(til_I32 *a, til_I32 *b) { return I32_new(I32_xor(*a, *b)); }

// I32 comparisons
til_Bool *til_I32_eq(til_I32 *a, til_I32 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I32_eq(*a, *b); return r; }
til_I64 *til_I32_cmp(til_I32 *a, til_I32 *b) { return I64_new(I32_cmp(*a, *b)); }

// I32 conversions
til_I64 *til_I32_to_i64(til_I32 *a) { return I64_new(I32_to_i64(*a)); }
til_I32 *til_I32_from_i64_ext(til_I64 *a) { return I32_new(I32_from_i64(*a)); }

// I32 clone/delete
til_I32 *til_I32_clone(til_I32 *v) { return I32_clone(v); }
void til_I32_delete(til_I32 *v, til_Bool *call_free) { if (*call_free) I32_delete(v); }

// I32 CLI
til_I32 *til_cli_parse_i32(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < -2147483648L || v > 2147483647L) {
        fprintf(stderr, "error: cannot parse '%s' as I32\n", s);
        exit(1);
    }
    return I32_new((I32)v);
}

// U32 arithmetic
til_U32 *til_U32_add(til_U32 *a, til_U32 *b) { return U32_new(U32_add(*a, *b)); }
til_U32 *til_U32_sub(til_U32 *a, til_U32 *b) { return U32_new(U32_sub(*a, *b)); }
til_U32 *til_U32_mul(til_U32 *a, til_U32 *b) { return U32_new(U32_mul(*a, *b)); }
til_U32 *til_U32_div(til_U32 *a, til_U32 *b) { return U32_new(U32_div(*a, *b)); }
til_U32 *til_U32_mod(til_U32 *a, til_U32 *b) { return U32_new(U32_mod(*a, *b)); }
til_U32 *til_U32_and(til_U32 *a, til_U32 *b) { return U32_new(U32_and(*a, *b)); }
til_U32 *til_U32_or(til_U32 *a, til_U32 *b) { return U32_new(U32_or(*a, *b)); }
til_U32 *til_U32_xor(til_U32 *a, til_U32 *b) { return U32_new(U32_xor(*a, *b)); }

// U32 comparisons
til_Bool *til_U32_eq(til_U32 *a, til_U32 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U32_eq(*a, *b); return r; }
til_I64 *til_U32_cmp(til_U32 *a, til_U32 *b) { return I64_new(U32_cmp(*a, *b)); }

// U32 conversions
til_I64 *til_U32_to_i64(til_U32 *a) { return I64_new(U32_to_i64(*a)); }
til_U32 *til_U32_from_i64_ext(til_I64 *a) { return U32_new(U32_from_i64(*a)); }

// U32 clone/delete
til_U32 *til_U32_clone(til_U32 *v) { return U32_clone(v); }
void til_U32_delete(til_U32 *v, til_Bool *call_free) { if (*call_free) U32_delete(v); }

// Bool ops
til_Bool *til_Bool_eq(til_Bool *a, til_Bool *b) { return Bool_new(Bool_eq(*a, *b)); }
til_Bool *til_and(til_Bool *a, til_Bool *b) { return Bool_new(Bool_and(*a, *b)); }
til_Bool *til_or(til_Bool *a, til_Bool *b) { return Bool_new(Bool_or(*a, *b)); }
til_Bool *til_not(til_Bool *a) { return Bool_new(Bool_not(*a)); }

// Bool clone/delete
til_Bool *til_Bool_clone(til_Bool *v) { return Bool_clone(v); }
void til_Bool_delete(til_Bool *v, til_Bool *call_free) { if (*call_free) Bool_delete(v); }

// Pointer primitives
void *til_malloc(til_I64 *count) { return calloc(1, (size_t)*count); }
void *til_realloc(void *buf, til_I64 *count) { return realloc(buf, (size_t)*count); }
void *til_ptr_add(void *buf, til_I64 *offset) {
    return (char *)buf + *offset;
}
void til_memcpy(void *dest, void *src, til_I64 *len) {
    memcpy(dest, src, (size_t)*len);
}
void til_memmove(void *dest, void *src, til_I64 *len) {
    memmove(dest, src, (size_t)*len);
}

// CLI arg parsing
til_I64 *til_cli_parse_i64(const char *s) {
    char *end;
    I64 v = strtoll(s, &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "error: cannot parse '%s' as I64\n", s);
        exit(1);
    }
    return I64_new(v);
}
til_U8 *til_cli_parse_u8(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < 0 || v > 255) {
        fprintf(stderr, "error: cannot parse '%s' as U8\n", s);
        exit(1);
    }
    return U8_new((U8)v);
}
til_U32 *til_cli_parse_u32(const char *s) {
    char *end;
    unsigned long v = strtoul(s, &end, 10);
    if (*end != '\0' || v > 0xFFFFFFFF) {
        fprintf(stderr, "error: cannot parse '%s' as U32\n", s);
        exit(1);
    }
    return U32_new((U32)v);
}
til_Bool *til_cli_parse_bool(const char *s) {
    if (strcmp(s, "true") == 0) return Bool_new(1);
    if (strcmp(s, "false") == 0) return Bool_new(0);
    fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
    exit(1);
}

// --- System primitives ---
// These use til_Str (codegen layout: { U8 *data, I64 len, I64 cap }) rather than
// Str (interpreter layout: { char *c_str, I64 cap }).
// For the interpreter, dispatch.c has its own handlers using Str directly.

til_Str *til_readfile(til_Str *path) {
    char *p = strndup((char *)path->data, path->len);
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
    til_Str *s = malloc(sizeof(til_Str));
    s->data = (til_U8 *)buf;
    s->len = len;
    s->cap = len;
    return s;
}

void til_writefile(til_Str *path, til_Str *content) {
    char *p = strndup((char *)path->data, path->len);
    FILE *f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fwrite(content->data, 1, content->len, f);
    fclose(f);
}

til_I64 *til_spawn_cmd(til_Str *cmd) {
    char *c = strndup((char *)cmd->data, cmd->len);
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
    return I64_new((I64)pid);
}

til_I64 *til_check_cmd_status(til_I64 *pid) {
    I32 status;
    pid_t result = waitpid((pid_t)*pid, &status, WNOHANG);
    if (result == 0) return I64_new(-1);
    if (WIFEXITED(status)) return I64_new(WEXITSTATUS(status));
    return I64_new(-1);
}

void til_sleep(til_I64 *ms) {
    usleep((useconds_t)(*ms * 1000));
}

til_I64 *til_file_mtime(til_Str *path) {
    char *p = strndup((char *)path->data, path->len);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return I64_new(-1);
    return I64_new((I64)st.st_mtime);
}

til_I64 *til_clock_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return I64_new((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
}

til_I64 *til_get_thread_count(void) {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return I64_new(count > 0 ? (I64)count : 1);
}


