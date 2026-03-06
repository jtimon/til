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
til_Bool *til_I64_lt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_lt(*a, *b); return r; }
til_Bool *til_I64_gt(til_I64 *a, til_I64 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = I64_gt(*a, *b); return r; }

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
til_Bool *til_U8_lt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_lt(*a, *b); return r; }
til_Bool *til_U8_gt(til_U8 *a, til_U8 *b) { til_Bool *r = malloc(sizeof(til_Bool)); *r = U8_gt(*a, *b); return r; }

// U8 conversions
til_I64 *til_U8_to_i64(til_U8 *a) { return I64_new(U8_to_i64(*a)); }
til_U8 *til_U8_from_i64_ext(til_I64 *a) { return U8_new(U8_from_i64(*a)); }

// U8 clone/delete
til_U8 *til_U8_clone(til_U8 *v) { return U8_clone(v); }
void til_U8_delete(til_U8 *v, til_Bool *call_free) { if (*call_free) U8_delete(v); }

// Bool ops
til_Bool *til_Bool_eq(til_Bool *a, til_Bool *b) { return Bool_new(Bool_eq(*a, *b)); }
til_Bool *til_Bool_and(til_Bool *a, til_Bool *b) { return Bool_new(Bool_and(*a, *b)); }
til_Bool *til_Bool_or(til_Bool *a, til_Bool *b) { return Bool_new(Bool_or(*a, *b)); }
til_Bool *til_Bool_not(til_Bool *a) { return Bool_new(Bool_not(*a)); }

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
    long long v = strtoll(s, &end, 10);
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
til_Bool *til_cli_parse_bool(const char *s) {
    if (strcmp(s, "true") == 0) return Bool_new(1);
    if (strcmp(s, "false") == 0) return Bool_new(0);
    fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
    exit(1);
}

// --- System primitives ---
// These use til_Str (codegen layout: { U8 *data, I64 cap }) rather than
// Str (interpreter layout: { char *c_str, int cap }).
// For the interpreter, dispatch.c has its own handlers using Str directly.

til_Str *til_readfile(til_Str *path) {
    FILE *f = fopen((char *)path->data, "rb");
    if (!f) {
        fprintf(stderr, "readfile: could not open '%.*s'\n", (int)path->cap, (char *)path->data);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len);
    fread(buf, 1, len, f);
    fclose(f);
    til_Str *s = malloc(sizeof(til_Str));
    s->data = (til_U8 *)buf;
    s->cap = len;
    return s;
}

void til_writefile(til_Str *path, til_Str *content) {
    FILE *f = fopen((char *)path->data, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%.*s'\n", (int)path->cap, (char *)path->data);
        exit(1);
    }
    fwrite(content->data, 1, content->cap, f);
    fclose(f);
}

til_I64 *til_spawn_cmd(til_Str *cmd) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", (char *)cmd->data, NULL);
        _exit(127);
    }
    if (pid < 0) {
        fprintf(stderr, "spawn_cmd: fork failed\n");
        exit(1);
    }
    return I64_new((I64)pid);
}

til_I64 *til_check_cmd_status(til_I64 *pid) {
    int status;
    pid_t result = waitpid((pid_t)*pid, &status, WNOHANG);
    if (result == 0) return I64_new(-1);
    if (WIFEXITED(status)) return I64_new(WEXITSTATUS(status));
    return I64_new(-1);
}

void til_sleep(til_I64 *ms) {
    usleep((useconds_t)(*ms * 1000));
}

til_I64 *til_file_mtime(til_Str *path) {
    struct stat st;
    if (stat((char *)path->data, &st) != 0) return I64_new(-1);
    return I64_new((I64)st.st_mtime);
}

til_I64 *til_clock_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return I64_new((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
}


