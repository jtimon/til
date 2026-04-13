#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <time.h>
#include <limits.h>
#include <dlfcn.h>

// Internal helpers for heap-allocating scalar values
static I64 *new_i64(I64 v) { I64 *r = malloc(sizeof(I64)); *r = v; return r; }
static U8 *new_u8(U8 v) { U8 *r = malloc(sizeof(U8)); *r = v; return r; }
static I8 *new_i8(I8 v) { I8 *r = malloc(sizeof(I8)); *r = v; return r; }
static I16 *new_i16(I16 v) { I16 *r = malloc(sizeof(I16)); *r = v; return r; }
static I32 *new_i32(I32 v) { I32 *r = malloc(sizeof(I32)); *r = v; return r; }
static U32 *new_u32(U32 v) { U32 *r = malloc(sizeof(U32)); *r = v; return r; }

__attribute__((unused)) static F32 *new_f32(F32 v) { F32 *r = malloc(sizeof(F32)); *r = v; return r; }
static U64 *new_u64(U64 v) { U64 *r = malloc(sizeof(U64)); *r = v; return r; }
static Bool *new_bool(Bool v) { Bool *r = malloc(sizeof(Bool)); *r = v; return r; }

static void *ffi_handle;

// I64 clone
I64 I64_clone(I64 *v) { return *v; }

// I64 arithmetic (shallow params, shallow return)
I64 I64_add(I64 a, I64 b) { return a + b; }
I64 I64_sub(I64 a, I64 b) { return a - b; }
I64 I64_mul(I64 a, I64 b) { return a * b; }
I64 I64_div(I64 a, I64 b) { return (b == 0) ? 0 : a / b; }
I64 I64_mod(I64 a, I64 b) { return (b == 0) ? 0 : a % b; }
I64 I64_and(I64 a, I64 b) { return a & b; }
I64 I64_or(I64 a, I64 b) { return a | b; }
I64 I64_xor(I64 a, I64 b) { return a ^ b; }

// I64 comparisons
Bool I64_eq(I64 a, I64 b) { return a == b; }
I64 I64_cmp(I64 a, I64 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }


// U8 arithmetic
U8 U8_add(U8 a, U8 b) { return a + b; }
U8 U8_sub(U8 a, U8 b) { return a - b; }
U8 U8_mul(U8 a, U8 b) { return a * b; }
U8 U8_div(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a / b); }
U8 U8_mod(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a % b); }
U8 U8_and(U8 a, U8 b) { return a & b; }
U8 U8_or(U8 a, U8 b) { return a | b; }
U8 U8_xor(U8 a, U8 b) { return a ^ b; }

// U8 comparisons
Bool U8_eq(U8 a, U8 b) { return a == b; }
I64 U8_cmp(U8 a, U8 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U8 conversions
I64 U8_to_i64(U8 a) { return (I64)a; }
U64 U8_to_u64(U8 a) { return (U64)a; }
U8 I64_to_u8(I64 a) { return (U8)a; }
I8 I64_to_i8(I64 a) { return (I8)a; }
I16 I64_to_i16(I64 a) { return (I16)a; }
I32 I64_to_i32(I64 a) { return (I32)a; }
U32 I64_to_u32(I64 a) { return (U32)a; }
U32 I32_to_u32(I32 a) { return (U32)a; }
U64 I64_to_u64(I64 a) { return (U64)a; }
F32 I64_to_f32(I64 a) { return (F32)a; }
U8 U8_from_i64(I64 v) { return (U8)v; }
U8 U8_from_i64_ext(I64 *a) { return (U8)*a; }

// U8 clone
U8 U8_clone(U8 *v) { return *v; }

// I8 arithmetic
I8 I8_add(I8 a, I8 b) { return a + b; }
I8 I8_sub(I8 a, I8 b) { return a - b; }
I8 I8_mul(I8 a, I8 b) { return a * b; }
I8 I8_div(I8 a, I8 b) { return (b == 0) ? 0 : (I8)(a / b); }
I8 I8_mod(I8 a, I8 b) { return (b == 0) ? 0 : (I8)(a % b); }
I8 I8_and(I8 a, I8 b) { return a & b; }
I8 I8_or(I8 a, I8 b) { return a | b; }
I8 I8_xor(I8 a, I8 b) { return a ^ b; }

// I8 comparisons
Bool I8_eq(I8 a, I8 b) { return a == b; }
I64 I8_cmp(I8 a, I8 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I8 conversions
I64 I8_to_i64(I8 a) { return (I64)a; }
I8 I8_from_i64(I64 v) { return (I8)v; }
I8 I8_from_i64_ext(I64 *a) { return (I8)*a; }

// I8 clone
I8 I8_clone(I8 *v) { return *v; }


// I16 arithmetic
I16 I16_add(I16 a, I16 b) { return a + b; }
I16 I16_sub(I16 a, I16 b) { return a - b; }
I16 I16_mul(I16 a, I16 b) { return a * b; }
I16 I16_div(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a / b); }
I16 I16_mod(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a % b); }
I16 I16_and(I16 a, I16 b) { return a & b; }
I16 I16_or(I16 a, I16 b) { return a | b; }
I16 I16_xor(I16 a, I16 b) { return a ^ b; }

// I16 comparisons
Bool I16_eq(I16 a, I16 b) { return a == b; }
I64 I16_cmp(I16 a, I16 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I16 conversions
I64 I16_to_i64(I16 a) { return (I64)a; }
I16 I16_from_i64(I64 v) { return (I16)v; }
I16 I16_from_i64_ext(I64 *a) { return (I16)*a; }


// I16 clone
I16 I16_clone(I16 *v) { return *v; }

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
I32 I32_add(I32 a, I32 b) { return a + b; }
I32 I32_sub(I32 a, I32 b) { return a - b; }
I32 I32_mul(I32 a, I32 b) { return a * b; }
I32 I32_div(I32 a, I32 b) { return (b == 0) ? 0 : a / b; }
I32 I32_mod(I32 a, I32 b) { return (b == 0) ? 0 : a % b; }
I32 I32_and(I32 a, I32 b) { return a & b; }
I32 I32_or(I32 a, I32 b) { return a | b; }
I32 I32_xor(I32 a, I32 b) { return a ^ b; }
I32 I32_not(I32 a) { return ~a; }

// I32 comparisons
Bool I32_eq(I32 a, I32 b) { return a == b; }
I64 I32_cmp(I32 a, I32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I32 conversions
I64 I32_to_i64(I32 a) { return (I64)a; }
I32 I32_from_i64(I64 v) { return (I32)v; }
I32 I32_from_i64_ext(I64 *a) { return (I32)*a; }


// I32 clone
I32 I32_clone(I32 *v) { return *v; }

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

// F32 arithmetic
F32 F32_add(F32 a, F32 b) { return a + b; }
F32 F32_sub(F32 a, F32 b) { return a - b; }
F32 F32_mul(F32 a, F32 b) { return a * b; }
F32 F32_div(F32 a, F32 b) { return (b == 0) ? 0 : a / b; }

// F32 comparisons
Bool F32_eq(F32 a, F32 b) { return a == b; }
I64 F32_cmp(F32 a, F32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// F32 conversions
I64 F32_to_i64(F32 a) { return (I64)a; }
F32 F32_from_i64(I64 v) { return (F32)v; }
F32 F32_from_i64_ext(I64 *a) { return (F32)*a; }

// F32 to_str
Str *F32_to_str(F32 v) {
    char buf[32];
    snprintf(buf, 32, "%g", (double)v);
    USize len = (USize)strlen(buf);
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, buf, len + 1);
    s->count = len;
    s->cap = len;
    return s;
}


// F32 clone
F32 F32_clone(F32 *v) { return *v; }

// U32 arithmetic
U32 U32_add(U32 a, U32 b) { return a + b; }
U32 U32_sub(U32 a, U32 b) { return a - b; }
U32 U32_mul(U32 a, U32 b) { return a * b; }
U32 U32_div(U32 a, U32 b) { return (b == 0) ? 0 : a / b; }
U32 U32_mod(U32 a, U32 b) { return (b == 0) ? 0 : a % b; }
U32 U32_and(U32 a, U32 b) { return a & b; }
U32 U32_or(U32 a, U32 b) { return a | b; }
U32 U32_xor(U32 a, U32 b) { return a ^ b; }

// U32 comparisons
Bool U32_eq(U32 a, U32 b) { return a == b; }
I64 U32_cmp(U32 a, U32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U32 conversions
I64 U32_to_i64(U32 a) { return (I64)a; }
U64 U32_to_u64(U32 a) { return (U64)a; }
U32 U32_from_i64(I64 v) { return (U32)v; }
U32 U32_from_i64_ext(I64 *a) { return (U32)*a; }


// U32 clone
U32 U32_clone(U32 *v) { return *v; }

// U64 arithmetic
U64 U64_add(U64 a, U64 b) { return a + b; }
U64 U64_sub(U64 a, U64 b) { return a - b; }
U64 U64_mul(U64 a, U64 b) { return a * b; }
U64 U64_div(U64 a, U64 b) { return (b == 0) ? 0 : a / b; }
U64 U64_mod(U64 a, U64 b) { return (b == 0) ? 0 : a % b; }
U64 U64_and(U64 a, U64 b) { return a & b; }
U64 U64_or(U64 a, U64 b) { return a | b; }
U64 U64_xor(U64 a, U64 b) { return a ^ b; }

// U64 comparisons
Bool U64_eq(U64 a, U64 b) { return a == b; }
I64 U64_cmp(U64 a, U64 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U64 conversions
I64 U64_to_i64(U64 a) { return (I64)a; }
U64 U64_from_i64(I64 v) { return (U64)v; }
U64 U64_from_i64_ext(I64 *a) { return (U64)*a; }

// U64 to_str
Str *U64_to_str(U64 v) {
    char buf[32];
    snprintf(buf, 32, "%llu", v);
    USize len = (USize)strlen(buf);
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, buf, len + 1);
    s->count = len;
    s->cap = len;
    return s;
}

Str *U64_to_str_ext(U64 v) { return U64_to_str(v); }


// U64 clone
U64 U64_clone(U64 *v) { return *v; }

// Bool ops (shallow params, shallow return)
Bool Bool_eq(Bool a, Bool b) { return a == b; }
Bool and(Bool a, Bool b) { return a && b; }
Bool or(Bool a, Bool b) { return a || b; }
Bool not(Bool a) { return !a; }


// Bool clone
Bool Bool_clone(Bool *v) { return *v; }

// Pointer primitives (custom, not in libc)
void *ptr_add(void *buf, U64 offset) {
    return (char *)buf + offset;
}
void *read_ptr(void *slot) { return *(void **)slot; }
void write_ptr(void *dest, void *val) { *(void **)dest = val; }
Bool is_null(void *p) { return p == NULL; }
Bool is(void *self, void *other) { return *(I32*)self == *(I32*)other; }
Bool is_variant(void *self, void *other) { return *(I32*)self == *(I32*)other; }
void *get_payload(void *self) { return (U8*)self + sizeof(I64); }

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
I8 *cli_parse_i8(const char *s) {
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < -128 || v > 127) {
        fprintf(stderr, "error: cannot parse '%s' as I8\n", s);
        exit(1);
    }
    return new_i8((I8)v);
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
U64 *cli_parse_u64(const char *s) {
    char *end;
    unsigned long long v = strtoull(s, &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "error: cannot parse '%s' as U64\n", s);
        exit(1);
    }
    return new_u64((U64)v);
}
Bool *cli_parse_bool(const char *s) {
    if (strcmp(s, "true") == 0) return new_bool(1);
    if (strcmp(s, "false") == 0) return new_bool(0);
    fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
    exit(1);
}

// --- System primitives ---
// These use the codegen Str layout: { U8 *c_str, U64 count, U64 cap }.
// For the interpreter, dispatch.c has its own handlers using the compiler Str directly.

Str *readfile(Str *path) {
    char *p = strndup((char *)path->c_str, path->count);
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
    s->c_str = (U8 *)buf;
    s->count = len;
    s->cap = len;
    return s;
}

void writefile(Str *path, Str *content) {
    char *p = strndup((char *)path->c_str, path->count);
    FILE *f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fwrite(content->c_str, 1, content->count, f);
    fclose(f);
}

// --- File handle I/O ---

void *cfile_open(Str *path, Bool is_write) {
    char *p = strndup((char *)path->c_str, path->count);
    FILE *f = fopen(p, is_write ? "wb" : "rb");
    if (!f) {
        fprintf(stderr, "cfile_open: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    return (void *)f;
}

void cfile_close(void *handle) {
    if (handle) fclose((FILE *)handle);
}

void cfile_write_str(void *handle, Str *s) {
    if (!handle) {
        fprintf(stderr, "cfile_write_str: file not open\n");
        exit(1);
    }
    fwrite(s->c_str, 1, s->count, (FILE *)handle);
}

Str *cfile_read_all(void *handle) {
    if (!handle) {
        fprintf(stderr, "cfile_read_all: file not open\n");
        exit(1);
    }
    FILE *f = (FILE *)handle;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len);
    fread(buf, 1, len, f);
    Str *s = malloc(sizeof(Str));
    s->c_str = (U8 *)buf;
    s->count = len;
    s->cap = len;
    return s;
}

Str *realpath_str(Str *path) {
    char *p = strndup((char *)path->c_str, path->count);
    char *abs = realpath(p, NULL);
    free(p);
    if (!abs) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    Str *s = Str_clone(&(Str){.c_str = (U8*)(abs), .count = (USize)strlen((const char*)(abs)), .cap = CAP_VIEW});
    free(abs);
    return s;
}

I32 system_cmd(Str *cmd) {
    char *c = strndup((char *)cmd->c_str, cmd->count);
    int status = system(c);
    free(c);
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return 1;
}

Str *get_bin_dir(void) {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
    buf[len] = '\0';
    char *slash = strrchr(buf, '/');
    if (slash) *slash = '\0';
    for (int i = 0; i < 5; i++) {
        char test[PATH_MAX + 32];
        snprintf(test, sizeof(test), "%s/src/core/core.til", buf);
        if (access(test, F_OK) == 0) return Str_clone(&(Str){.c_str = (U8*)(buf), .count = (USize)strlen((const char*)(buf)), .cap = CAP_VIEW});
        slash = strrchr(buf, '/');
        if (!slash) break;
        *slash = '\0';
    }
    return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
}

I64 *spawn_cmd(Str *cmd) {
    char *c = strndup((char *)cmd->c_str, cmd->count);
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

I64 check_cmd_status(I64 pid) {
    I32 status;
    pid_t result = waitpid((pid_t)pid, &status, WNOHANG);
    if (result == 0) return -1;
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return -1;
}

void sleep_ms(I64 ms) {
    usleep((useconds_t)(ms * 1000));
}

I64 file_mtime(Str *path) {
    char *p = strndup((char *)path->c_str, path->count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return -1;
    return (I64)st.st_mtime;
}

I64 clock_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000;
}

I64 get_thread_count(void) {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return count > 0 ? (I64)count : 1;
}

U64 peak_rss_bytes(void) {
    struct rusage ru;
    if (getrusage(RUSAGE_SELF, &ru) != 0) return 0;
#if defined(__APPLE__)
    return (U64)ru.ru_maxrss;
#else
    return (U64)ru.ru_maxrss * 1024ULL;
#endif
}

static U64 proc_rss_bytes(pid_t pid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%lld/statm", (long long)pid);
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    unsigned long long total_pages = 0;
    unsigned long long resident_pages = 0;
    int scanned = fscanf(f, "%llu %llu", &total_pages, &resident_pages);
    fclose(f);
    if (scanned != 2) return 0;
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;
    return (U64)resident_pages * (U64)page_size;
}

static U64 proc_tree_rss_bytes(pid_t pid) {
    U64 total = proc_rss_bytes(pid);
    char path[96];
    snprintf(path, sizeof(path), "/proc/%lld/task/%lld/children",
             (long long)pid, (long long)pid);
    FILE *f = fopen(path, "rb");
    if (!f) return total;
    char buf[4096];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = '\0';
    char *p = buf;
    while (*p) {
        while (*p == ' ' || *p == '\n' || *p == '\t') p++;
        if (!*p) break;
        char *end = p;
        long long child = strtoll(p, &end, 10);
        if (end == p) break;
        if (child > 0) total += proc_tree_rss_bytes((pid_t)child);
        p = end;
    }
    return total;
}

U64 current_rss_bytes(I64 pid) {
#if defined(__linux__)
    return proc_tree_rss_bytes((pid_t)pid);
#else
    (void)pid;
    return 0;
#endif
}

// --- Utility functions (for til.til ext_func calls) ---

Str *til_bin_dir(void) {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
    buf[len] = '\0';
    char *slash = strrchr(buf, '/');
    if (slash) *slash = '\0';
    for (int i = 0; i < 5; i++) {
        char test[PATH_MAX + 32];
        snprintf(test, sizeof(test), "%s/src/core/core.til", buf);
        if (access(test, F_OK) == 0) return Str_clone(&(Str){.c_str = (U8*)buf, .count = (USize)strlen(buf), .cap = CAP_VIEW});
        slash = strrchr(buf, '/');
        if (!slash) break;
        *slash = '\0';
    }
    return Str_clone(&(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
}

Str *til_realpath(Str *path) {
    char *abs = realpath((const char *)path->c_str, NULL);
    if (!abs) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    Str *s = Str_clone(&(Str){.c_str = (U8*)abs, .count = (USize)strlen(abs), .cap = CAP_VIEW});
    free(abs);
    return s;
}

I32 til_system(Str *cmd) {
    int status = system((const char *)cmd->c_str);
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return 1;
}

Bool ffi_load_global_lib(Str *soname) {
    return dlopen((const char *)soname->c_str, RTLD_NOW | RTLD_GLOBAL) != NULL;
}

Bool ffi_open_user_so(Str *path) {
    ffi_handle = dlopen((const char *)path->c_str, RTLD_NOW);
    return ffi_handle != NULL;
}

void ffi_close_user_so(void) {
    if (ffi_handle) {
        dlclose(ffi_handle);
        ffi_handle = NULL;
    }
}

U8 *ffi_user_symbol(Str *name) {
    if (!ffi_handle) return NULL;
    return dlsym(ffi_handle, (const char *)name->c_str);
}

U8 *ffi_global_symbol(Str *name) {
    return dlsym(RTLD_DEFAULT, (const char *)name->c_str);
}

Str *ffi_last_error(void) {
    char *msg = dlerror();
    if (!msg) {
        return Str_clone(&(Str){.c_str = (U8 *)"", .count = 0, .cap = CAP_LIT});
    }
    return Str_clone(&(Str){.c_str = (U8 *)msg, .count = (USize)strlen(msg), .cap = CAP_VIEW});
}

I32 stderr_print(Str *msg) {
    fprintf(stderr, "%.*s", (int)msg->count, msg->c_str ? (char *)msg->c_str : "");
    return 0;
}

void unlink_path(Str *path) {
    unlink((const char *)path->c_str);
}

I32 process_id(void) {
    return (I32)getpid();
}

Str *til_str_left(Str *s, U64 n) {
    if (!s || n == 0) return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
    USize len = (USize)s->count;
    if (n > len) n = len;
    char *buf = malloc(n + 1);
    memcpy(buf, s->c_str, n);
    buf[n] = '\0';
    Str *result = Str_clone(&(Str){.c_str = (U8*)buf, .count = n, .cap = CAP_VIEW});
    free(buf);
    return result;
}

void *Vec_take(Vec *v) {
    void *ptr = v->data;
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
    return ptr;
}

USize c_str_len(U8 *s) { return (USize)strlen((const char *)s); }
