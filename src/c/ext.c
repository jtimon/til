#include "../../boot/til_forward.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#ifdef _WIN32
#define TIL_DUP _dup
#define TIL_DUP2 _dup2
#define TIL_CLOSE _close
#define TIL_OPEN _open
#define TIL_FILENO _fileno
#define TIL_O_WRONLY _O_WRONLY
#define TIL_O_CREAT _O_CREAT
#define TIL_O_TRUNC _O_TRUNC
#define TIL_O_BINARY _O_BINARY
#else
#define TIL_DUP dup
#define TIL_DUP2 dup2
#define TIL_CLOSE close
#define TIL_OPEN open
#define TIL_FILENO fileno
#define TIL_O_WRONLY O_WRONLY
#define TIL_O_CREAT O_CREAT
#define TIL_O_TRUNC O_TRUNC
#define TIL_O_BINARY 0
#endif

static int stdio_capture_stdout_fd = -1;
static int stdio_capture_stderr_fd = -1;

static void stdio_capture_fail(const char *op) {
    perror(op);
    exit(1);
}

#ifdef _WIN32
// winnt.h declares 'TokenType' as an enum constant inside
// TOKEN_INFORMATION_CLASS, which collides with our 'TokenType' typedef from
// boot/til_forward.h. ext.c never references the Windows token enum, so rename it
// via the preprocessor for the duration of the Windows headers.
// wingdi.h declares a 'Rectangle' GDI function, which collides with our
// 'Rectangle' struct (from the raylib bindings) in boot/til_forward.h.
// ext.c never calls the GDI function, so rename it the same way.
#define TokenType _WinTokenType_Conflict
#define Rectangle _WinRectangle_Conflict
#include <windows.h>
#undef TokenType
#undef Rectangle
#include <direct.h>
#include <io.h>
#include <psapi.h>
#include <sys/stat.h>
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#else
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#ifndef __EMSCRIPTEN__
#include <sys/wait.h>
#include <sys/resource.h>
#include <dlfcn.h>
// RTLD_DEFAULT is a GNU/Darwin extension the header only exposes at the right
// feature level: glibc hides it without _GNU_SOURCE and some cross toolchains
// targeting linux do not expose it, while macOS gates it behind __DARWIN_C_FULL.
// ext.c deliberately avoids _GNU_SOURCE (see the dladdr lookup below), so supply
// the platform-correct value when the header did not (glibc/musl: 0, macOS: -2).
#ifndef RTLD_DEFAULT
#  ifdef __APPLE__
#    define RTLD_DEFAULT ((void *)-2)
#  else
#    define RTLD_DEFAULT ((void *)0)
#  endif
#endif
#endif
#endif

// nng's win_clock.c calls the C11 timespec_get(&ts, TIME_UTC), which mingw only
// declares under the universal CRT (_UCRT). We deliberately build nng against
// the default msvcrt instead (see the Makefile NNG_WIN_LIB rule): a UCRT nng
// pulls ucrtbase.dll in alongside mingw's msvcrt.dll startup, and Windows
// refuses to load the resulting dual-CRT binary (issue #25 -- the exit-127 the
// windows-host runner hit; wine tolerated it). So supply timespec_get here for
// nng to link against. Guarded off under _UCRT, where the real one exists.
#if defined(_WIN32) && !defined(_UCRT)
#include <time.h>
int timespec_get(struct timespec *ts, int base) {
    FILETIME ft;
    ULARGE_INTEGER u;
    GetSystemTimeAsFileTime(&ft);
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    // FILETIME counts 100ns ticks from 1601-01-01; shift to the Unix epoch.
    unsigned long long t = u.QuadPart - 116444736000000000ULL;
    ts->tv_sec = (time_t)(t / 10000000ULL);
    ts->tv_nsec = (long)((t % 10000000ULL) * 100);
    return base;
}
#endif

#ifdef _WIN32
static HMODULE ffi_handle;
#elif defined(__EMSCRIPTEN__)
#else
static void *ffi_handle;
#endif

// Portable strndup replacement -- MSVC toolchains don't ship one and mingw's
// availability varies by _GNU_SOURCE. This is tiny, so inline it.
static char *dup_n(const char *s, size_t n) {
    char *r = malloc(n + 1);
    if (!r) return NULL;
    memcpy(r, s, n);
    r[n] = '\0';
    return r;
}

static char *path_join(const char *a, const char *b) {
    size_t na = strlen(a);
    size_t nb = strlen(b);
    int need_sep = na > 0 && a[na - 1] != '/' && a[na - 1] != '\\';
    char *out = malloc(na + nb + (need_sep ? 2 : 1));
    if (!out) return NULL;
    memcpy(out, a, na);
    if (need_sep) out[na++] = '/';
    memcpy(out + na, b, nb + 1);
    return out;
}

static char *path_dirname(const char *path) {
    const char *slash = strrchr(path, '/');
#ifdef _WIN32
    const char *backslash = strrchr(path, '\\');
    if (backslash && (!slash || backslash > slash)) slash = backslash;
#endif
    if (!slash) return NULL;
    return dup_n(path, (size_t)(slash - path));
}

#ifdef _WIN32
static void normalize_windows_path(char *path) {
    for (char *p = path; *p; p++) {
        if (*p == '/') *p = '\\';
    }
}
#endif

static int mkdir_one(const char *path) {
#ifdef _WIN32
    if (_mkdir(path) == 0 || errno == EEXIST) return 0;
#else
    if (mkdir(path, 0777) == 0 || errno == EEXIST) return 0;
#endif
    return 1;
}

static int mkdir_p_cstr(const char *path) {
    if (!path || !*path) return 0;
    char *tmp = dup_n(path, strlen(path));
    if (!tmp) return 1;
#ifdef _WIN32
    normalize_windows_path(tmp);
#endif
    size_t start = 0;
    if (tmp[0] == '/' || tmp[0] == '\\') start = 1;
#ifdef _WIN32
    if (strlen(tmp) >= 2 && tmp[1] == ':') {
        start = 2;
        if (tmp[2] == '\\' || tmp[2] == '/') start = 3;
    }
#endif
    for (size_t i = start; tmp[i]; i++) {
        if (tmp[i] != '/' && tmp[i] != '\\') continue;
        char saved = tmp[i];
        tmp[i] = '\0';
        if (tmp[0] && mkdir_one(tmp) != 0) {
            tmp[i] = saved;
            free(tmp);
            return 1;
        }
        tmp[i] = saved;
    }
    if (mkdir_one(tmp) != 0) {
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}

static int copy_file_cstr(const char *src, const char *dst) {
    char *parent = path_dirname(dst);
    if (parent) {
        if (mkdir_p_cstr(parent) != 0) {
            free(parent);
            return 1;
        }
        free(parent);
    }

    FILE *in = fopen(src, "rb");
    if (!in) return 1;
    FILE *out = fopen(dst, "wb");
    if (!out) {
        fclose(in);
        return 1;
    }

    char buf[65536];
    size_t n = 0;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            return 1;
        }
    }
    fclose(in);
    fclose(out);
#if !defined(_WIN32) && !defined(__EMSCRIPTEN__)
    struct stat st;
    if (stat(src, &st) == 0) {
        chmod(dst, st.st_mode & 0777);
    }
#endif
    return 0;
}

static int copy_tree_cstr(const char *src, const char *dst) {
    if (mkdir_p_cstr(dst) != 0) return 1;
#ifdef _WIN32
    char *src_norm = dup_n(src, strlen(src));
    if (!src_norm) return 1;
    normalize_windows_path(src_norm);
    char *pattern = path_join(src_norm, "*");
    free(src_norm);
    if (!pattern) return 1;
    normalize_windows_path(pattern);

    WIN32_FIND_DATAA data;
    HANDLE h = FindFirstFileA(pattern, &data);
    free(pattern);
    if (h == INVALID_HANDLE_VALUE) return 1;
    int rc = 0;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        char *child_src = path_join(src, data.cFileName);
        char *child_dst = path_join(dst, data.cFileName);
        if (!child_src || !child_dst) {
            free(child_src);
            free(child_dst);
            rc = 1;
            break;
        }
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) rc = copy_tree_cstr(child_src, child_dst);
        else rc = copy_file_cstr(child_src, child_dst);
        free(child_src);
        free(child_dst);
        if (rc != 0) break;
    } while (FindNextFileA(h, &data));
    FindClose(h);
    return rc;
#else
    DIR *dir = opendir(src);
    if (!dir) return 1;
    struct dirent *ent = NULL;
    int rc = 0;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
        char *child_src = path_join(src, ent->d_name);
        char *child_dst = path_join(dst, ent->d_name);
        if (!child_src || !child_dst) {
            free(child_src);
            free(child_dst);
            rc = 1;
            break;
        }
        struct stat st;
        if (stat(child_src, &st) != 0) {
            free(child_src);
            free(child_dst);
            rc = 1;
            break;
        }
        if (S_ISDIR(st.st_mode)) rc = copy_tree_cstr(child_src, child_dst);
        else rc = copy_file_cstr(child_src, child_dst);
        free(child_src);
        free(child_dst);
        if (rc != 0) break;
    }
    closedir(dir);
    return rc;
#endif
}

// Internal helper for heap-allocating scalar values. The per-type
// new_u8/new_i8/.../new_bool helpers were dropped when CLI argument
// parsing moved into til and got inlined by the builder. new_i64 survives
// because the process-spawn helpers below still box a pid/handle into I64*.
static I64 *new_i64(I64 v) { I64 *r = malloc(sizeof(I64)); *r = v; return r; }

// --- Small libc wrappers ---

// Avoid declaring libc symbols directly in generated C (signature mismatches
// vs stdlib.h can cause compile errors). Provide stable wrappers instead.
I32 til_setenv(const I8 *name, const I8 *value, I32 overwrite)
{
#ifdef _WIN32
    // setenv is not portable to Windows; use Win32 environment APIs.
    if (!overwrite) {
        // If the variable exists, do nothing.
        DWORD len = GetEnvironmentVariableA((const char *)name, NULL, 0);
        if (len > 0) return 0;
    }
    if (SetEnvironmentVariableA((const char *)name, (const char *)value)) return 0;
    return 1;
#else
    return (I32)setenv((const char *)name, (const char *)value, overwrite);
#endif
}

// I64 clone
I64 I64_clone(const I64 *v) { return *v; }

// I64 arithmetic (shallow params, shallow return)

// I64 comparisons
I64 I64_cmp(I64 a, I64 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }


// U8 arithmetic

// U8 comparisons
I64 U8_cmp(U8 a, U8 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U8 conversions
I64 U8_to_i64(U8 a) { return (I64)a; }
I32 U8_to_i32(U8 a) { return (I32)a; }
USize U8_to_usize(U8 a) { return (USize)a; }
F32 U8_to_f32(U8 a) { return (F32)a; }
U8 I64_to_u8(I64 a) { return (U8)a; }
I8 I64_to_i8(I64 a) { return (I8)a; }
I16 I64_to_i16(I64 a) { return (I16)a; }
U16 I64_to_u16(I64 a) { return (U16)a; }
I32 I64_to_i32(I64 a) { return (I32)a; }
U32 I64_to_u32(I64 a) { return (U32)a; }
USize I64_to_usize(I64 a) { return (USize)a; }
F32 I64_to_f32(I64 a) { return (F32)a; }
U8 U8_from_i64(I64 v) { return (U8)v; }
U8 U8_from_i64_ext(const I64 *a) { return (U8)*a; }

// U8 clone
U8 U8_clone(const U8 *v) { return *v; }

// I8 arithmetic

// I8 comparisons
I64 I8_cmp(I8 a, I8 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I8 conversions
U64 I8_to_u64(I8 a) { return (U64)(I64)a; }
I8 I8_from_i64(I64 v) { return (I8)v; }
I8 I8_from_i64_ext(const I64 *a) { return (I8)*a; }

// I8 clone
I8 I8_clone(const I8 *v) { return *v; }


// I16 arithmetic

// I16 comparisons
I64 I16_cmp(I16 a, I16 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I16 conversions
U64 I16_to_u64(I16 a) { return (U64)(I64)a; }
U32 I16_to_u32(I16 a) { return (U32)(I32)a; }
F32 I16_to_f32(I16 a) { return (F32)a; }
I16 I16_from_i64(I64 v) { return (I16)v; }
I16 I16_from_i64_ext(const I64 *a) { return (I16)*a; }


// I16 clone
I16 I16_clone(const I16 *v) { return *v; }

// U16 arithmetic

// U16 comparisons
I64 U16_cmp(U16 a, U16 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U16 conversions
I64 U16_to_i64(U16 a) { return (I64)a; }
F32 U16_to_f32(U16 a) { return (F32)a; }
U16 U16_from_i64(I64 v) { return (U16)v; }
U16 U16_from_i64_ext(const I64 *a) { return (U16)*a; }

// U16 clone
U16 U16_clone(const U16 *v) { return *v; }

// I32 arithmetic

// I32 comparisons
I64 I32_cmp(I32 a, I32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I32 conversions
U64 I32_to_u64(I32 a) { return (U64)(I64)a; }
USize I32_to_usize(I32 a) { return (USize)a; }
F32 I32_to_f32(I32 a) { return (F32)a; }
I32 I32_from_i64(I64 v) { return (I32)v; }
I32 I32_from_i64_ext(const I64 *a) { return (I32)*a; }


// I32 clone
I32 I32_clone(const I32 *v) { return *v; }

// F32 arithmetic

// F32 comparisons
I64 F32_cmp(F32 a, F32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// F32 conversions
I64 F32_to_i64(F32 a) { return (I64)a; }
F32 F32_from_i64_ext(const I64 *a) { return (F32)*a; }

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

// Round-trippable F32 repr: 9 significant digits uniquely identify any
// IEEE-754 single, so strtof(F32_to_repr(x)) == x. Used by constfolder to bake
// folded F32 results as source literals (F32_to_str's %g loses precision).
Str *F32_to_repr(F32 v) {
    char buf[32];
    snprintf(buf, 32, "%.9g", (double)v);
    USize len = (USize)strlen(buf);
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, buf, len + 1);
    s->count = len;
    s->cap = len;
    return s;
}

// Faithful decimal/scientific float parse (strtof) -- handles exponents
// and full precision, unlike the old hand-rolled Str.to_f32. Backs
// Str.to_f32 so folded F32 literals round-trip in interp and codegen.
F32 str_parse_f32(const Str *s) {
    char *p = dup_n((const char *)s->c_str, s->count);
    float v = strtof(p, NULL);
    free(p);
    return (F32)v;
}



// F32 clone
F32 F32_clone(const F32 *v) { return *v; }

// U32 arithmetic

// U32 comparisons
I64 U32_cmp(U32 a, U32 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U32 conversions
I64 U32_to_i64(U32 a) { return (I64)a; }
I32 U32_to_i32(U32 a) { return (I32)a; }
U32 U32_to_u32(U32 a) { return a; }
U64 U32_to_u64(U32 a) { return (U64)a; }
F32 U32_to_f32(U32 a) { return (F32)a; }
U32 U32_from_i64(I64 v) { return (U32)v; }
U32 U32_from_i64_ext(const I64 *a) { return (U32)*a; }


// U32 clone
U32 U32_clone(const U32 *v) { return *v; }

// U64 arithmetic

// U64 comparisons
I64 U64_cmp(U64 a, U64 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U64 conversions
U32 U64_to_u32(U64 a) { return (U32)a; }
I32 U64_to_i32(U64 a) { return (I32)a; }
I64 U64_to_i64(U64 a) { return (I64)a; }
U64 U64_to_u64(U64 a) { return a; }
USize U64_to_usize(U64 a) { return (USize)a; }
F32 U64_to_f32(U64 a) { return (F32)a; }

// U64 to_str
Str *U64_to_str_ext(U64 v) {
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


// U64 clone
U64 U64_clone(const U64 *v) { return *v; }

// The Bool ops that used to live here (Bool_eq, not, band, bor, bxor) are
// gone: eq and not are core_funcs (the backend inlines every call), and
// band/bor/bxor had no til declaration left. and/or never lived here --
// they are lazy_funcs whose bodies compile into the generated C itself.

// Bool clone
Bool Bool_clone(const Bool *v) { return *v; }

// Pointer primitives (custom, not in libc). See ext.h for why these
// keep non-const inputs. ptr_add used to live here; it is a core_func
// now (every call site, including the variadic-args template, emits the
// pointer arithmetic inline).
void *to_ptr(void *a) { return a; }
void *deref(void *slot) { return *(void **)slot; }
void write_ptr(void *dest, void *val) { *(void **)dest = val; }
/* #211 follow-up: write a typed primitive into raw bytes. Used by the
 * AST interpreter to mirror writes through a payload-aliased binding
 * into the underlying enum's payload memory. */
void write_i64(void *dest, I64 val) { *(I64 *)dest = val; }
void write_u8(void *dest, U8 val)   { *(U8 *)dest  = val; }
void write_i8(void *dest, I8 val)   { *(I8 *)dest  = val; }
void write_i16(void *dest, I16 val) { *(I16 *)dest = val; }
void write_u16(void *dest, U16 val) { *(U16 *)dest = val; }
void write_i32(void *dest, I32 val) { *(I32 *)dest = val; }
void write_u32(void *dest, U32 val) { *(U32 *)dest = val; }
void write_u64(void *dest, U64 val) { *(U64 *)dest = val; }
void write_f32(void *dest, F32 val) { *(F32 *)dest = val; }
void write_bool(void *dest, Bool val) { *(Bool *)dest = val; }
Bool ptr_eq(void *a, void *b) { return a == b; }
void eprint_single(const Str *s) { fwrite(s->c_str, 1, (size_t)s->count, stderr); }

// CLI arg parsing

// --- System primitives ---
// These use the codegen Str layout: { U8 *c_str, U64 count, U64 cap }.

Str *File_readfile(Str *path) {
    char *p = dup_n((const char *)path->c_str, path->count);
    FILE *f = fopen(p, "rb");
    if (!f) {
        fprintf(stderr, "File.readfile: could not open '%s'\n", p);
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
    s->c_str = (I8 *)buf;
    s->count = len;
    s->cap = len;
    return s;
}

void File_writefile(Str *path, Str *content) {
    char *p = dup_n((const char *)path->c_str, path->count);
    FILE *f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "File.writefile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fwrite(content->c_str, 1, content->count, f);
    fclose(f);
}

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} DocBuf;

typedef struct {
    char **items;
    size_t len;
    size_t cap;
} DocPageList;

typedef struct {
    const char *since;
    size_t since_len;
    const char *deprecated;
    size_t deprecated_len;
    int hidden;
} DocProps;

static char *doc_org_cached_path = NULL;
static DocBuf doc_org_cached_info = {0};
static DocBuf doc_org_cached_docs = {0};

static void doc_die_alloc(const char *what) {
    fprintf(stderr, "%s: allocation failed\n", what);
    exit(1);
}

static Str *str_from_bytes(const char *data, size_t len, const char *what) {
    char *buf = malloc(len + 1);
    if (!buf) doc_die_alloc(what);
    memcpy(buf, data, len);
    buf[len] = '\0';
    Str *s = malloc(sizeof(Str));
    if (!s) doc_die_alloc(what);
    s->c_str = (I8 *)buf;
    s->count = (USize)len;
    s->cap = (USize)len;
    return s;
}

static void doc_buf_free(DocBuf *buf) {
    free(buf->data);
    buf->data = NULL;
    buf->len = 0;
    buf->cap = 0;
}

static void doc_buf_reserve(DocBuf *buf, size_t add) {
    if (add > SIZE_MAX - buf->len) doc_die_alloc("doc_buf_reserve");
    size_t need = buf->len + add;
    if (need <= buf->cap) return;
    size_t cap = buf->cap ? buf->cap : 4096;
    while (cap < need) {
        if (cap > SIZE_MAX / 2) {
            cap = need;
            break;
        }
        cap *= 2;
    }
    char *data = realloc(buf->data, cap);
    if (!data) doc_die_alloc("doc_buf_reserve");
    buf->data = data;
    buf->cap = cap;
}

static void doc_buf_append(DocBuf *buf, const char *data, size_t len) {
    if (len == 0) return;
    doc_buf_reserve(buf, len);
    memcpy(buf->data + buf->len, data, len);
    buf->len += len;
}

static void doc_buf_append_cstr(DocBuf *buf, const char *s) {
    doc_buf_append(buf, s, strlen(s));
}

static void doc_buf_append_ch(DocBuf *buf, char ch) {
    doc_buf_reserve(buf, 1);
    buf->data[buf->len++] = ch;
}

static void doc_pack_entry(DocBuf *packed, const char *name, size_t name_len, const char *value, size_t value_len) {
    if (name_len == 0 || value_len == 0) return;
    doc_buf_append(packed, name, name_len);
    doc_buf_append_ch(packed, 1);
    doc_buf_append(packed, value, value_len);
    doc_buf_append_ch(packed, 2);
}

static void trim_range(const char **start, const char **end) {
    while (*start < *end && ((*start)[0] == '\n' || (*start)[0] == '\r')) (*start)++;
    while (*end > *start && ((*end)[-1] == '\n' || (*end)[-1] == '\r')) (*end)--;
}

static void trim_spaces(const char **start, const char **end) {
    while (*start < *end && ((*start)[0] == ' ' || (*start)[0] == '\t')) (*start)++;
    while (*end > *start && ((*end)[-1] == ' ' || (*end)[-1] == '\t')) (*end)--;
}

static int range_starts_with(const char *start, const char *end, const char *prefix) {
    size_t n = strlen(prefix);
    return (size_t)(end - start) >= n && memcmp(start, prefix, n) == 0;
}

static int range_eq_cstr(const char *start, const char *end, const char *s) {
    size_t n = strlen(s);
    return (size_t)(end - start) == n && memcmp(start, s, n) == 0;
}

static const char *find_bytes_range(const char *start, const char *end, const char *needle) {
    size_t n = strlen(needle);
    if (n == 0) return start;
    for (const char *p = start; p + n <= end; p++) {
        if (memcmp(p, needle, n) == 0) return p;
    }
    return NULL;
}

static const char *find_line_prefix(const char *start, const char *end, const char *prefix) {
    size_t n = strlen(prefix);
    for (const char *p = start; p + n <= end; p++) {
        if ((p == start || p[-1] == '\n') && memcmp(p, prefix, n) == 0) return p;
    }
    return NULL;
}

static char *read_file_cstr_or_die(const char *path, size_t *len_out) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "doc_org_load: could not open '%s'\n", path);
        exit(1);
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "doc_org_load: could not seek '%s'\n", path);
        exit(1);
    }
    long len = ftell(f);
    if (len < 0) {
        fprintf(stderr, "doc_org_load: could not tell '%s'\n", path);
        exit(1);
    }
    if (fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "doc_org_load: could not rewind '%s'\n", path);
        exit(1);
    }
    char *buf = malloc((size_t)len + 1);
    if (!buf) doc_die_alloc("doc_org_load");
    if (fread(buf, 1, (size_t)len, f) != (size_t)len) {
        fprintf(stderr, "doc_org_load: could not read '%s'\n", path);
        exit(1);
    }
    fclose(f);
    buf[len] = '\0';
    *len_out = (size_t)len;
    return buf;
}

static char *dirname_dup_cstr(const char *path) {
    const char *slash = strrchr(path, '/');
#ifdef _WIN32
    const char *backslash = strrchr(path, '\\');
    if (backslash && (!slash || backslash > slash)) slash = backslash;
#endif
    if (!slash) return dup_n(".", 1);
    return dup_n(path, (size_t)(slash - path));
}

static int page_is_core_org(const char *page, size_t len) {
    const char *prefix = "src/core/";
    const char *suffix = ".org";
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    return len > prefix_len + suffix_len
        && memcmp(page, prefix, prefix_len) == 0
        && memcmp(page + len - suffix_len, suffix, suffix_len) == 0;
}

static int page_list_has(DocPageList *pages, const char *page, size_t len) {
    for (size_t i = 0; i < pages->len; i++) {
        if (strlen(pages->items[i]) == len && memcmp(pages->items[i], page, len) == 0) return 1;
    }
    return 0;
}

static void page_list_add(DocPageList *pages, const char *page, size_t len) {
    if (page_list_has(pages, page, len)) return;
    if (pages->len == pages->cap) {
        size_t cap = pages->cap ? pages->cap * 2 : 32;
        char **items = realloc(pages->items, cap * sizeof(char *));
        if (!items) doc_die_alloc("page_list_add");
        pages->items = items;
        pages->cap = cap;
    }
    pages->items[pages->len++] = dup_n(page, len);
    if (!pages->items[pages->len - 1]) doc_die_alloc("page_list_add");
}

static void page_list_free(DocPageList *pages) {
    for (size_t i = 0; i < pages->len; i++) free(pages->items[i]);
    free(pages->items);
    pages->items = NULL;
    pages->len = 0;
    pages->cap = 0;
}

static void parse_index_pages(const char *index, size_t len, DocPageList *pages) {
    const char *end = index + len;
    const char *p = index;
    while ((p = find_bytes_range(p, end, "[[file:")) != NULL) {
        const char *page_start = p + 7;
        const char *page_end = find_bytes_range(page_start, end, "::#");
        if (!page_end) {
            fprintf(stderr, "doc_org_load: malformed file link in index\n");
            exit(1);
        }
        size_t page_len = (size_t)(page_end - page_start);
        if (page_is_core_org(page_start, page_len)) page_list_add(pages, page_start, page_len);
        p = page_end + 3;
    }
    if (pages->len == 0) {
        fprintf(stderr, "doc_org_load: no src/core org pages found in index\n");
        exit(1);
    }
}

static void parse_property_line(const char *line_start, const char *line_end, DocProps *props) {
    const char *start = line_start;
    const char *end = line_end;
    trim_spaces(&start, &end);
    if (range_starts_with(start, end, ":since:")) {
        start += 7;
        trim_spaces(&start, &end);
        props->since = start;
        props->since_len = (size_t)(end - start);
    } else if (range_starts_with(start, end, ":deprecated:")) {
        start += 12;
        trim_spaces(&start, &end);
        props->deprecated = start;
        props->deprecated_len = (size_t)(end - start);
    }
}

static void parse_properties(const char *start, const char *end, DocProps *props) {
    const char *p = start;
    while (p < end) {
        const char *line_end = memchr(p, '\n', (size_t)(end - p));
        if (!line_end) line_end = end;
        parse_property_line(p, line_end, props);
        p = line_end < end ? line_end + 1 : end;
    }
}

static int line_false_value(const char *start, const char *end) {
    trim_spaces(&start, &end);
    return range_eq_cstr(start, end, "false") || range_eq_cstr(start, end, "nil") || range_eq_cstr(start, end, "no");
}

static void parse_raw_doc_meta_line(const char *line_start, const char *line_end, DocProps *props, DocBuf *body) {
    const char *start = line_start;
    const char *end = line_end;
    trim_spaces(&start, &end);
    if (range_starts_with(start, end, "#+doc:")) {
        start += 6;
        if (line_false_value(start, end)) props->hidden = 1;
        return;
    }
    if (range_starts_with(start, end, "#+since:")) {
        start += 8;
        trim_spaces(&start, &end);
        props->since = start;
        props->since_len = (size_t)(end - start);
        return;
    }
    if (range_starts_with(start, end, "#+deprecated:")) {
        start += 13;
        trim_spaces(&start, &end);
        props->deprecated = start;
        props->deprecated_len = (size_t)(end - start);
        return;
    }
    if (range_starts_with(start, end, "#+group:")) return;
    if (body->len > 0) doc_buf_append_ch(body, '\n');
    doc_buf_append(body, line_start, (size_t)(line_end - line_start));
}

static void append_doc_value(DocBuf *value, DocProps props, const char *body_start, const char *body_end) {
    trim_range(&body_start, &body_end);
    if (props.since_len > 0) {
        doc_buf_append_cstr(value, "Since: ");
        doc_buf_append(value, props.since, props.since_len);
        doc_buf_append_ch(value, '\n');
    }
    if (props.deprecated_len > 0) {
        doc_buf_append_cstr(value, "Deprecated: ");
        doc_buf_append(value, props.deprecated, props.deprecated_len);
        doc_buf_append_ch(value, '\n');
    }
    if (value->len > 0 && body_start < body_end) doc_buf_append_ch(value, '\n');
    doc_buf_append(value, body_start, (size_t)(body_end - body_start));
}

static void pack_doc_from_body(DocBuf *docs, const char *name, size_t name_len, DocProps props, const char *body_start, const char *body_end) {
    if (props.hidden) return;
    DocBuf value = {0};
    append_doc_value(&value, props, body_start, body_end);
    doc_pack_entry(docs, name, name_len, value.data, value.len);
    doc_buf_free(&value);
}

static void pack_doc_from_raw(DocBuf *docs, const char *name, size_t name_len, const char *raw, size_t raw_len) {
    DocProps props = {0};
    DocBuf body = {0};
    const char *p = raw;
    const char *end = raw + raw_len;
    while (p < end) {
        const char *line_end = memchr(p, '\n', (size_t)(end - p));
        if (!line_end) line_end = end;
        parse_raw_doc_meta_line(p, line_end, &props, &body);
        p = line_end < end ? line_end + 1 : end;
    }
    if (!props.hidden) {
        DocBuf value = {0};
        const char *body_start = body.data ? body.data : "";
        const char *body_end = body_start + body.len;
        append_doc_value(&value, props, body_start, body_end);
        doc_pack_entry(docs, name, name_len, value.data, value.len);
        doc_buf_free(&value);
    }
    doc_buf_free(&body);
}

static int method_kind_len(const char *line, const char *end) {
    const char *kinds[] = {"func", "proc", "test", "macro", "ext_func", "ext_proc", "core_func", "core_proc"};
    for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); i++) {
        size_t n = strlen(kinds[i]);
        if ((size_t)(end - line) > n && memcmp(line, kinds[i], n) == 0 && line[n] == ' ') return (int)n;
    }
    return 0;
}

static void pack_pending_member_doc(DocBuf *docs, const char *member_name, size_t member_name_len, DocBuf *pending_doc) {
    if (pending_doc->len > 0) {
        pack_doc_from_raw(docs, member_name, member_name_len, pending_doc->data, pending_doc->len);
        pending_doc->len = 0;
    }
}

static void append_qualified_info(DocBuf *out, const char *prefix, const char *type_name, size_t type_len, const char *member, size_t member_len, const char *suffix, size_t suffix_len) {
    doc_buf_append_cstr(out, prefix);
    doc_buf_append(out, type_name, type_len);
    doc_buf_append_ch(out, '.');
    doc_buf_append(out, member, member_len);
    doc_buf_append(out, suffix, suffix_len);
}

static void parse_struct_field_line(DocBuf *info, DocBuf *docs, const char *type_name, size_t type_len, const char *line, const char *line_end, DocBuf *pending_doc) {
    const char *name = line;
    while (name < line_end) {
        const char *word_end = name;
        while (word_end < line_end && *word_end != ' ' && *word_end != '\t' && *word_end != ':') word_end++;
        if ((range_eq_cstr(name, word_end, "own") || range_eq_cstr(name, word_end, "ref") || range_eq_cstr(name, word_end, "shallow") || range_eq_cstr(name, word_end, "mut")) && word_end < line_end) {
            name = word_end;
            while (name < line_end && (*name == ' ' || *name == '\t')) name++;
        } else {
            break;
        }
    }
    const char *name_end = name;
    while (name_end < line_end && *name_end != ' ' && *name_end != '\t' && *name_end != ':') name_end++;
    if (name == name_end) return;
    DocBuf qual = {0};
    append_qualified_info(&qual, "", type_name, type_len, name, (size_t)(name_end - name), "", 0);
    DocBuf value = {0};
    doc_buf_append_cstr(&value, "field ");
    doc_buf_append(&value, line, (size_t)(name - line));
    doc_buf_append(&value, qual.data, qual.len);
    doc_buf_append(&value, name_end, (size_t)(line_end - name_end));
    doc_pack_entry(info, qual.data, qual.len, value.data, value.len);
    pack_pending_member_doc(docs, qual.data, qual.len, pending_doc);
    doc_buf_free(&qual);
    doc_buf_free(&value);
}

static void parse_enum_variant_line(DocBuf *info, DocBuf *docs, const char *type_name, size_t type_len, const char *line, const char *line_end, DocBuf *pending_doc) {
    const char *name = line;
    const char *name_end = name;
    while (name_end < line_end && *name_end != ' ' && *name_end != '\t' && *name_end != ':') name_end++;
    if (name == name_end) return;
    DocBuf qual = {0};
    append_qualified_info(&qual, "", type_name, type_len, name, (size_t)(name_end - name), "", 0);
    DocBuf value = {0};
    append_qualified_info(&value, "variant ", type_name, type_len, name, (size_t)(name_end - name), name_end, (size_t)(line_end - name_end));
    doc_pack_entry(info, qual.data, qual.len, value.data, value.len);
    pack_pending_member_doc(docs, qual.data, qual.len, pending_doc);
    doc_buf_free(&qual);
    doc_buf_free(&value);
}

static void parse_namespace_member_line(DocBuf *info, DocBuf *docs, const char *type_name, size_t type_len, const char *line, const char *line_end, DocBuf *pending_doc) {
    int kind_len = method_kind_len(line, line_end);
    const char *name = line;
    const char *prefix = "member ";
    size_t prefix_len = strlen(prefix);
    if (kind_len > 0) {
        name = line + kind_len + 1;
        prefix = line;
        prefix_len = (size_t)kind_len + 1;
    }
    const char *name_end = name;
    while (name_end < line_end && *name_end != ' ' && *name_end != '\t' && *name_end != '(' && *name_end != ':') name_end++;
    if (name == name_end) return;
    DocBuf qual = {0};
    append_qualified_info(&qual, "", type_name, type_len, name, (size_t)(name_end - name), "", 0);
    DocBuf value = {0};
    doc_buf_append(&value, prefix, prefix_len);
    doc_buf_append(&value, type_name, type_len);
    doc_buf_append_ch(&value, '.');
    doc_buf_append(&value, name, (size_t)(name_end - name));
    doc_buf_append(&value, name_end, (size_t)(line_end - name_end));
    doc_pack_entry(info, qual.data, qual.len, value.data, value.len);
    pack_pending_member_doc(docs, qual.data, qual.len, pending_doc);
    doc_buf_free(&qual);
    doc_buf_free(&value);
}

static void append_members_from_info(DocBuf *info_blob, DocBuf *docs_blob, const char *entry_name, size_t entry_name_len, const char *info, size_t info_len) {
    const char *end = info + info_len;
    int is_struct = range_starts_with(info, end, "struct ");
    int is_enum = range_starts_with(info, end, "enum ");
    if (!is_struct && !is_enum) return;
    const char *p = memchr(info, '\n', info_len);
    if (!p) return;
    p++;
    int in_namespace = 0;
    DocBuf pending_doc = {0};
    while (p < end) {
        const char *line_end = memchr(p, '\n', (size_t)(end - p));
        if (!line_end) line_end = end;
        const char *line = p;
        trim_spaces(&line, &line_end);
        if (line < line_end) {
            if (range_eq_cstr(line, line_end, "}")) break;
            if (range_eq_cstr(line, line_end, "namespace:")) {
                in_namespace = 1;
            } else if (range_starts_with(line, line_end, "///")) {
                const char *doc_start = line + 3;
                if (doc_start < line_end && *doc_start == ' ') doc_start++;
                if (pending_doc.len > 0) doc_buf_append_ch(&pending_doc, '\n');
                doc_buf_append(&pending_doc, doc_start, (size_t)(line_end - doc_start));
            } else if (in_namespace) {
                parse_namespace_member_line(info_blob, docs_blob, entry_name, entry_name_len, line, line_end, &pending_doc);
            } else if (is_struct) {
                parse_struct_field_line(info_blob, docs_blob, entry_name, entry_name_len, line, line_end, &pending_doc);
            } else {
                parse_enum_variant_line(info_blob, docs_blob, entry_name, entry_name_len, line, line_end, &pending_doc);
            }
        }
        p = line_end < end ? line_end + 1 : end;
    }
    doc_buf_free(&pending_doc);
}

static const char *next_org_heading(const char *start, const char *end) {
    for (const char *p = start; p + 3 <= end; p++) {
        if (p[0] == '\n' && p[1] == '*' && p[2] == ' ') return p + 1;
    }
    return end;
}

static void parse_org_entry(DocBuf *info_blob, DocBuf *docs_blob, const char *name, size_t name_len, const char *section_start, const char *section_end) {
    DocProps props = {0};
    const char *body_start = section_start;
    if (range_starts_with(body_start, section_end, ":PROPERTIES:\n")) {
        const char *props_start = body_start + strlen(":PROPERTIES:\n");
        const char *props_end = find_line_prefix(props_start, section_end, ":END:");
        if (!props_end) {
            fprintf(stderr, "doc_org_load: unterminated property drawer for '%.*s'\n", (int)name_len, name);
            exit(1);
        }
        parse_properties(props_start, props_end, &props);
        const char *props_line_end = memchr(props_end, '\n', (size_t)(section_end - props_end));
        body_start = props_line_end ? props_line_end + 1 : section_end;
        if (body_start < section_end && *body_start == '\n') body_start++;
    }

    const char *last_begin = NULL;
    const char *last_end = NULL;
    const char *search = body_start;
    while (search < section_end) {
        const char *begin = find_line_prefix(search, section_end, "#+begin_src");
        if (!begin) break;
        const char *end_marker = find_line_prefix(begin, section_end, "#+end_src");
        if (!end_marker) {
            fprintf(stderr, "doc_org_load: unterminated source block for '%.*s'\n", (int)name_len, name);
            exit(1);
        }
        last_begin = begin;
        last_end = end_marker;
        const char *end_line = memchr(end_marker, '\n', (size_t)(section_end - end_marker));
        search = end_line ? end_line + 1 : section_end;
    }

    const char *body_end = last_begin ? last_begin : section_end;
    pack_doc_from_body(docs_blob, name, name_len, props, body_start, body_end);

    if (last_begin) {
        const char *begin_line_end = memchr(last_begin, '\n', (size_t)(section_end - last_begin));
        if (!begin_line_end) {
            fprintf(stderr, "doc_org_load: malformed source block for '%.*s'\n", (int)name_len, name);
            exit(1);
        }
        const char *info_start = begin_line_end + 1;
        const char *info_end = last_end;
        trim_range(&info_start, &info_end);
        doc_pack_entry(info_blob, name, name_len, info_start, (size_t)(info_end - info_start));
        append_members_from_info(info_blob, docs_blob, name, name_len, info_start, (size_t)(info_end - info_start));
    }
}

static void parse_org_page(const char *path, DocBuf *info_blob, DocBuf *docs_blob) {
    size_t len = 0;
    char *content = read_file_cstr_or_die(path, &len);
    const char *end = content + len;
    const char *p = content;
    while (p < end) {
        if ((p == content || p[-1] == '\n') && p + 2 <= end && p[0] == '*' && p[1] == ' ') {
            const char *line_end = memchr(p, '\n', (size_t)(end - p));
            if (!line_end) line_end = end;
            const char *name_start = p + 2;
            const char *name_end = line_end;
            trim_spaces(&name_start, &name_end);
            const char *section_start = line_end < end ? line_end + 1 : end;
            const char *section_end = next_org_heading(section_start, end);
            parse_org_entry(info_blob, docs_blob, name_start, (size_t)(name_end - name_start), section_start, section_end);
            p = section_end;
        } else {
            const char *line_end = memchr(p, '\n', (size_t)(end - p));
            p = line_end ? line_end + 1 : end;
        }
    }
    free(content);
}

static void doc_org_rebuild_cache(const char *index_path) {
    size_t index_len = 0;
    char *index = read_file_cstr_or_die(index_path, &index_len);
    DocPageList pages = {0};
    parse_index_pages(index, index_len, &pages);

    char *base_dir = dirname_dup_cstr(index_path);
    doc_buf_free(&doc_org_cached_info);
    doc_buf_free(&doc_org_cached_docs);
    for (size_t i = 0; i < pages.len; i++) {
        char *full = path_join(base_dir, pages.items[i]);
        if (!full) doc_die_alloc("doc_org_load");
        parse_org_page(full, &doc_org_cached_info, &doc_org_cached_docs);
        free(full);
    }
    free(base_dir);
    free(index);
    page_list_free(&pages);
}

static void doc_org_ensure_cache(const Str *index_path) {
    char *path = dup_n(index_path->c_str, index_path->count);
    if (!path) doc_die_alloc("doc_org_load");
    if (doc_org_cached_path && strcmp(doc_org_cached_path, path) == 0) {
        free(path);
        return;
    }
    free(doc_org_cached_path);
    doc_org_cached_path = path;
    doc_org_rebuild_cache(doc_org_cached_path);
}

Str *doc_org_load_core_info(const Str *index_path) {
    doc_org_ensure_cache(index_path);
    return str_from_bytes(doc_org_cached_info.data ? doc_org_cached_info.data : "", doc_org_cached_info.len, "doc_org_load_core_info");
}

Str *doc_org_load_core_docs(const Str *index_path) {
    doc_org_ensure_cache(index_path);
    return str_from_bytes(doc_org_cached_docs.data ? doc_org_cached_docs.data : "", doc_org_cached_docs.len, "doc_org_load_core_docs");
}

Str *doc_blob_lookup(const Str *blob, const Str *name) {
    USize i = 0;
    while (i < blob->count) {
        USize sep1 = i;
        while (sep1 < blob->count && (U8)blob->c_str[sep1] != 1) sep1++;
        if (sep1 >= blob->count) return Str_clone(&(Str){.c_str = (I8 *)"", .count = 0, .cap = CAP_LIT});

        USize sep2 = sep1 + 1;
        while (sep2 < blob->count && (U8)blob->c_str[sep2] != 2) sep2++;

        if (sep1 - i == name->count && memcmp(blob->c_str + i, name->c_str, (size_t)name->count) == 0) {
            USize len = sep2 - sep1 - 1;
            char *buf = malloc((size_t)len + 1);
            if (!buf) {
                fprintf(stderr, "doc_blob_lookup: allocation failed\n");
                exit(1);
            }
            memcpy(buf, blob->c_str + sep1 + 1, (size_t)len);
            buf[len] = '\0';

            Str *s = malloc(sizeof(Str));
            if (!s) {
                fprintf(stderr, "doc_blob_lookup: Str allocation failed\n");
                exit(1);
            }
            s->c_str = (I8 *)buf;
            s->count = len;
            s->cap = len;
            return s;
        }

        i = sep2 + 1;
    }
    return Str_clone(&(Str){.c_str = (I8 *)"", .count = 0, .cap = CAP_LIT});
}

void stdio_capture_begin(const Str *path) {
    if (stdio_capture_stdout_fd != -1 || stdio_capture_stderr_fd != -1) {
        fprintf(stderr, "stdio_capture_begin: capture already active\n");
        exit(1);
    }
    fflush(stdout);
    fflush(stderr);

    char *p = dup_n((const char *)path->c_str, path->count);
    int fd = TIL_OPEN(p, TIL_O_WRONLY | TIL_O_CREAT | TIL_O_TRUNC | TIL_O_BINARY, 0666);
    free(p);
    if (fd < 0) stdio_capture_fail("stdio_capture_begin: open");

    stdio_capture_stdout_fd = TIL_DUP(TIL_FILENO(stdout));
    if (stdio_capture_stdout_fd < 0) stdio_capture_fail("stdio_capture_begin: dup stdout");
    stdio_capture_stderr_fd = TIL_DUP(TIL_FILENO(stderr));
    if (stdio_capture_stderr_fd < 0) stdio_capture_fail("stdio_capture_begin: dup stderr");

    if (TIL_DUP2(fd, TIL_FILENO(stdout)) < 0) stdio_capture_fail("stdio_capture_begin: dup2 stdout");
    if (TIL_DUP2(fd, TIL_FILENO(stderr)) < 0) stdio_capture_fail("stdio_capture_begin: dup2 stderr");
    if (TIL_CLOSE(fd) != 0) stdio_capture_fail("stdio_capture_begin: close");
}

void stdio_capture_end(void) {
    if (stdio_capture_stdout_fd == -1 || stdio_capture_stderr_fd == -1) {
        fprintf(stderr, "stdio_capture_end: capture not active\n");
        exit(1);
    }
    fflush(stdout);
    fflush(stderr);
    if (TIL_DUP2(stdio_capture_stdout_fd, TIL_FILENO(stdout)) < 0) stdio_capture_fail("stdio_capture_end: restore stdout");
    if (TIL_DUP2(stdio_capture_stderr_fd, TIL_FILENO(stderr)) < 0) stdio_capture_fail("stdio_capture_end: restore stderr");
    if (TIL_CLOSE(stdio_capture_stdout_fd) != 0) stdio_capture_fail("stdio_capture_end: close stdout");
    if (TIL_CLOSE(stdio_capture_stderr_fd) != 0) stdio_capture_fail("stdio_capture_end: close stderr");
    stdio_capture_stdout_fd = -1;
    stdio_capture_stderr_fd = -1;
}

// --- File handle I/O ---

void *cfile_open(const Str *path, Bool is_write) {
    char *p = dup_n((const char *)path->c_str, path->count);
    FILE *f = fopen(p, is_write ? "wb" : "rb");
    if (!f) {
        fprintf(stderr, "cfile_open: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    return (void *)f;
}

void cfile_close(const void *handle) {
    if (handle) fclose((FILE *)handle);
}

void cfile_write_str(const void *handle, const Str *s) {
    if (!handle) {
        fprintf(stderr, "cfile_write_str: file not open\n");
        exit(1);
    }
    fwrite(s->c_str, 1, s->count, (FILE *)handle);
}

// Open a file for in-place update ("r+b"): reads and writes are both
// allowed and the cursor can move freely with cfile_seek, so small
// regions can be patched without rewriting the whole file.
void *cfile_open_update(const Str *path) {
    char *p = dup_n((const char *)path->c_str, path->count);
    FILE *f = fopen(p, "r+b");
    if (!f) {
        fprintf(stderr, "cfile_open_update: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    return (void *)f;
}

// Current cursor position as a byte offset from the start of the file.
I64 cfile_tell(const void *handle) {
    if (!handle) {
        fprintf(stderr, "cfile_tell: file not open\n");
        exit(1);
    }
    return (I64)ftell((FILE *)handle);
}

// Move the cursor to an absolute byte offset from the start of the file.
void cfile_seek(const void *handle, I64 pos) {
    if (!handle) {
        fprintf(stderr, "cfile_seek: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)pos, SEEK_SET);
}

// Move the cursor by `delta` bytes relative to its current position
// (delta may be negative).
void cfile_seek_cur(const void *handle, I64 delta) {
    if (!handle) {
        fprintf(stderr, "cfile_seek_cur: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)delta, SEEK_CUR);
}

// Move the cursor to `delta` bytes relative to the end of the file
// (delta is typically <= 0; seek_end(0) puts the cursor at EOF, so a
// following tell() yields the file size).
void cfile_seek_end(const void *handle, I64 delta) {
    if (!handle) {
        fprintf(stderr, "cfile_seek_end: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)delta, SEEK_END);
}

// Read up to `count` bytes starting at the current cursor position. The
// returned Str's count reflects how many bytes were actually read (fewer
// than `count` near end-of-file).
Str *cfile_read_n(const void *handle, I64 count) {
    if (!handle) {
        fprintf(stderr, "cfile_read_n: file not open\n");
        exit(1);
    }
    FILE *f = (FILE *)handle;
    if (count < 0) count = 0;
    char *buf = malloc((size_t)count + 1);
    size_t got = fread(buf, 1, (size_t)count, f);
    buf[got] = '\0';
    Str *s = malloc(sizeof(Str));
    s->c_str = (I8 *)buf;
    s->count = (U32)got;
    s->cap = (U32)count;
    return s;
}

// Read a single line from stdin into *line (without trailing newline).
// Returns true on success, false on EOF. Flushes stdout first so prompts appear.
Bool in_read_line(Str *line) {
    fflush(stdout);
    size_t cap = 256;
    size_t len = 0;
    char *buf = malloc(cap);
    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (len + 1 >= cap) {
            cap *= 2;
            buf = realloc(buf, cap);
        }
        buf[len++] = (char)c;
    }
    if (c == EOF && len == 0) {
        free(buf);
        line->c_str = NULL;
        line->count = 0;
        line->cap = 0;
        return 0;
    }
    buf[len] = '\0';
    if (line->c_str && line->cap != CAP_LIT && line->cap != CAP_VIEW) {
        free(line->c_str);
    }
    line->c_str = (I8 *)buf;
    line->count = (U32)len;
    line->cap = (U32)len;
    return 1;
}

Str *cfile_read_all(const void *handle) {
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
    s->c_str = (I8 *)buf;
    s->count = len;
    s->cap = len;
    return s;
}

Str *get_cwd_str(void) {
    char buf[PATH_MAX];
#ifdef _WIN32
    if (!_getcwd(buf, sizeof(buf))) return Str_clone(&(Str){.c_str = (I8*)"", .count = 0, .cap = CAP_LIT});
    for (char *q = buf; *q; q++) if (*q == '\\') *q = '/';
#else
    if (!getcwd(buf, sizeof(buf))) return Str_clone(&(Str){.c_str = (I8*)"", .count = 0, .cap = CAP_LIT});
#endif
    return Str_clone(&(Str){.c_str = (I8*)(buf), .count = (USize)strlen(buf), .cap = CAP_VIEW});
}

Str *realpath_str(const Str *path) {
    char *p = malloc(path->count + 1);
    memcpy(p, path->c_str, path->count);
    p[path->count] = '\0';
#ifdef _WIN32
    char *abs = _fullpath(NULL, p, 0);
    free(p);
    // _fullpath is a pure string normalizer: unlike POSIX realpath it
    // succeeds for paths that do NOT exist. Callers rely on "" meaning
    // "no such file" (e.g. the builder's libffi absence gate, which
    // otherwise links a nonexistent archive on a windows host), so
    // enforce the POSIX contract with an explicit existence check.
    if (abs && _access(abs, 0) != 0) { free(abs); abs = NULL; }
    if (!abs) return Str_clone(&(Str){.c_str = (I8*)"", .count = 0, .cap = CAP_LIT});
    // Normalize backslashes to forward slashes so path comparisons stay
    // consistent across Unix and Windows codepaths.
    for (char *q = abs; *q; q++) if (*q == '\\') *q = '/';
#else
    char *abs = realpath(p, NULL);
    free(p);
    if (!abs) return Str_clone(&(Str){.c_str = (I8*)"", .count = 0, .cap = CAP_LIT});
#endif
    Str *s = Str_clone(&(Str){.c_str = (I8*)(abs), .count = (USize)strlen((const char*)(abs)), .cap = CAP_VIEW});
    free(abs);
    return s;
}

I32 system_cmd(const Str *cmd) {
#ifdef __EMSCRIPTEN__
    (void)cmd;
    return 1;
#else
    char *c = malloc(cmd->count + 1);
    memcpy(c, cmd->c_str, cmd->count);
    c[cmd->count] = '\0';
    int status = system(c);
    free(c);
#ifdef _WIN32
    return (I32)status;
#else
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return 1;
#endif
#endif
}

Str *get_bin_dir(void) {
    char buf[PATH_MAX];
#ifdef _WIN32
    DWORD len = GetModuleFileNameA(NULL, buf, (DWORD)sizeof(buf));
    if (len == 0 || len >= sizeof(buf)) {
        return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
    }
    for (DWORD i = 0; i < len; i++) if (buf[i] == '\\') buf[i] = '/';
#elif defined(__EMSCRIPTEN__)
    return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
#elif defined(__APPLE__)
    // No /proc on macOS; _NSGetExecutablePath may return a path with
    // symlinks or relative components, so resolve it before use.
    uint32_t bufsize = sizeof(buf);
    if (_NSGetExecutablePath(buf, &bufsize) != 0) {
        return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
    }
    char resolved[PATH_MAX];
    if (realpath(buf, resolved) == NULL) {
        return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
    }
    snprintf(buf, sizeof(buf), "%s", resolved);
#else
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0) return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
    buf[len] = '\0';
#endif
    char *slash = strrchr(buf, '/');
    if (slash) *slash = '\0';
    for (int i = 0; i < 5; i++) {
        char test[PATH_MAX * 2];
        snprintf(test, sizeof(test), "%s/src/core/core.til", buf);
#ifdef _WIN32
        if (_access(test, 0) == 0) return Str_clone(&(Str){.c_str = (I8*)(buf), .count = (USize)strlen((const char*)(buf)), .cap = CAP_VIEW});
#else
        if (access(test, F_OK) == 0) return Str_clone(&(Str){.c_str = (I8*)(buf), .count = (USize)strlen((const char*)(buf)), .cap = CAP_VIEW});
#endif
        char *parent = strrchr(buf, '/');
        if (parent) {
            char install_root[PATH_MAX * 2];
            size_t parent_len = (size_t)(parent - buf);
            memcpy(install_root, buf, parent_len);
            install_root[parent_len] = '\0';
            const char *core_suffix = "/lib/til/src/core/core.til";
            size_t core_suffix_len = strlen(core_suffix);
            if (parent_len + core_suffix_len >= sizeof(test)) {
                break;
            }
            memcpy(test, install_root, parent_len);
            memcpy(test + parent_len, core_suffix, core_suffix_len + 1);
#ifdef _WIN32
            if (_access(test, 0) == 0) {
#else
            if (access(test, F_OK) == 0) {
#endif
                const char *root_suffix = "/lib/til";
                size_t root_suffix_len = strlen(root_suffix);
                if (parent_len + root_suffix_len >= sizeof(install_root)) {
                    break;
                }
                memcpy(install_root, buf, parent_len);
                memcpy(install_root + parent_len, root_suffix, root_suffix_len + 1);
                return Str_clone(&(Str){.c_str = (I8*)(install_root), .count = (USize)strlen((const char*)(install_root)), .cap = CAP_VIEW});
            }
        }
        slash = strrchr(buf, '/');
        if (!slash) break;
        *slash = '\0';
    }
    return Str_clone(&(Str){.c_str = (I8*)".", .count = 1, .cap = CAP_LIT});
}

// Returns the OS family the running .exe is on. Mirrors target_to_str() OS
// segments so til source can compare against "linux" / "windows" / "macos" /
// "wasm" / "templeos". This is the host, not the build target.
Str *host_os(void) {
#if defined(__EMSCRIPTEN__)
    return Str_clone(&(Str){.c_str = (I8*)"wasm", .count = 4, .cap = CAP_LIT});
#elif defined(_WIN32)
    return Str_clone(&(Str){.c_str = (I8*)"windows", .count = 7, .cap = CAP_LIT});
#elif defined(__APPLE__)
    return Str_clone(&(Str){.c_str = (I8*)"macos", .count = 5, .cap = CAP_LIT});
#elif defined(__linux__)
    return Str_clone(&(Str){.c_str = (I8*)"linux", .count = 5, .cap = CAP_LIT});
#elif defined(__wasm__) || defined(__wasm32__)
    return Str_clone(&(Str){.c_str = (I8*)"wasm", .count = 4, .cap = CAP_LIT});
#else
    return Str_clone(&(Str){.c_str = (I8*)"unknown", .count = 7, .cap = CAP_LIT});
#endif
}

// Architecture this binary was COMPILED for, from predefined macros --
// deliberately NOT uname: under emulation (Rosetta, qemu-user) uname
// reports the kernel's arch while this binary, and the libffi linked
// into it, are the compiled arch, which is what FFI ABI selection
// needs. It also runs in hot paths (once per ext_func registration),
// so it must not spawn processes the way detect_current_target does.
// Names mirror target_to_str() arch segments.
Str *host_arch(void) {
#if defined(__x86_64__) || defined(_M_X64)
    return Str_clone(&(Str){.c_str = (I8*)"x64", .count = 3, .cap = CAP_LIT});
#elif defined(__aarch64__) || defined(_M_ARM64)
    return Str_clone(&(Str){.c_str = (I8*)"arm64", .count = 5, .cap = CAP_LIT});
#elif defined(__riscv) && defined(__riscv_xlen) && (__riscv_xlen == 64)
    return Str_clone(&(Str){.c_str = (I8*)"riscv64", .count = 7, .cap = CAP_LIT});
#elif defined(__riscv)
    return Str_clone(&(Str){.c_str = (I8*)"riscv32", .count = 7, .cap = CAP_LIT});
#elif defined(__arm__)
    return Str_clone(&(Str){.c_str = (I8*)"arm32", .count = 5, .cap = CAP_LIT});
#elif defined(__i386__) || defined(_M_IX86)
    return Str_clone(&(Str){.c_str = (I8*)"x86", .count = 3, .cap = CAP_LIT});
#else
    return Str_clone(&(Str){.c_str = (I8*)"unknown", .count = 7, .cap = CAP_LIT});
#endif
}

// Issue #302 stage 0: filter for the garbager's decision-audit dump.
// TIL_GC_AUDIT=<path-substring> makes the asap pass print its per-body
// decisions (the LocalInfo table and the destructor sites present after
// insertion) for bodies whose unit path contains the substring; unset or
// empty disables the dump (the normal case). See doc/garbager.org. Owned
// Str return, "" when unset -- same convention as host_os above.
Str *gc_audit_filter(void) {
    const char *env = getenv("TIL_GC_AUDIT");
    if (!env) env = "";
    return Str_clone(&(Str){.c_str = (I8*)env, .count = strlen(env), .cap = CAP_LIT});
}

#ifdef _WIN32
I64 *spawn_cmd(const Str *cmd) {
    char *c = malloc(cmd->count + 1);
    memcpy(c, cmd->c_str, cmd->count);
    c[cmd->count] = '\0';

    char cmdline[8192];
    snprintf(cmdline, sizeof(cmdline), "cmd.exe /c %s", c);
    free(c);

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "spawn_cmd: CreateProcess failed\n");
        exit(1);
    }
    CloseHandle(pi.hThread);
    return new_i64((I64)(intptr_t)pi.hProcess);
}

I64 check_cmd_status(I64 pid) {
    HANDLE h = (HANDLE)(intptr_t)pid;
    DWORD wait = WaitForSingleObject(h, 0);
    if (wait == WAIT_TIMEOUT) return -1;
    DWORD code = 0;
    GetExitCodeProcess(h, &code);
    CloseHandle(h);
    return (I64)code;
}

void sleep_ms(I64 ms) {
    Sleep((DWORD)ms);
}
#elif defined(__EMSCRIPTEN__)
I64 *spawn_cmd(const Str *cmd) {
    (void)cmd;
    return NULL;
}

I64 check_cmd_status(I64 pid) {
    (void)pid;
    return -1;
}

void sleep_ms(I64 ms) {
    (void)ms;
}
#else
I64 *spawn_cmd(const Str *cmd) {
    char *c = dup_n((const char *)cmd->c_str, cmd->count);
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
    if (result == 0) return -1;  // still running
    if (result < 0) {
        // Treat waitpid errors as a hard failure so the runner doesn't spin.
        return 127;
    }
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return 127;
}

void sleep_ms(I64 ms) {
    usleep((useconds_t)(ms * 1000));
}
#endif

void noop_proc(void) {}

I64 file_mtime(const Str *path) {
    char *p = dup_n((const char *)path->c_str, path->count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return -1;
    return (I64)st.st_mtime;
}

I32 mkdir_p(const Str *path) {
    char *p = dup_n((const char *)path->c_str, path->count);
    int rc = mkdir_p_cstr(p);
    if (rc != 0) fprintf(stderr, "mkdir_p: failed for '%s'\n", p);
    free(p);
    return (I32)rc;
}

I32 copy_file(const Str *src, const Str *dst) {
    char *s = dup_n((const char *)src->c_str, src->count);
    char *d = dup_n((const char *)dst->c_str, dst->count);
    int rc = copy_file_cstr(s, d);
    if (rc != 0) fprintf(stderr, "copy_file: failed from '%s' to '%s'\n", s, d);
    free(s);
    free(d);
    return (I32)rc;
}

I32 copy_tree(const Str *src, const Str *dst) {
    char *s = dup_n((const char *)src->c_str, src->count);
    char *d = dup_n((const char *)dst->c_str, dst->count);
    int rc = copy_tree_cstr(s, d);
    if (rc != 0) fprintf(stderr, "copy_tree: failed from '%s' to '%s'\n", s, d);
    free(s);
    free(d);
    return (I32)rc;
}

I64 clock_ms(void) {
#ifdef _WIN32
    return (I64)GetTickCount64();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000;
#endif
}

I64 get_thread_count(void) {
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (I64)si.dwNumberOfProcessors;
#else
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return count > 0 ? (I64)count : 1;
#endif
}

U64 peak_rss_bytes(void) {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) return 0;
    return (U64)pmc.PeakWorkingSetSize;
#elif defined(__EMSCRIPTEN__)
    return 0;
#else
    struct rusage ru;
    if (getrusage(RUSAGE_SELF, &ru) != 0) return 0;
#if defined(__APPLE__)
    return (U64)ru.ru_maxrss;
#else
    return (U64)ru.ru_maxrss * 1024ULL;
#endif
#endif
}

// __linux__, not just POSIX: these walk /proc, which macOS does not have.
// On macOS they would compile as unused static functions and trip
// -Werror=unused-function (current_rss_bytes only calls them on __linux__).
#if defined(__linux__)
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

// A "child" in /proc/<pid>/task/<pid>/children can be either a real child
// process or (on some kernels, e.g. 4.4) a thread of another process. Threads
// share memory with their process leader, so summing their RSS double-counts.
// Return 1 iff tid is the thread-group leader of its own process.
static int is_process_leader(pid_t tid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%lld/status", (long long)tid);
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    char line[128];
    int leader = 0;
    while (fgets(line, sizeof(line), f)) {
        long long tgid;
        if (sscanf(line, "Tgid: %lld", &tgid) == 1) {
            leader = (tgid == (long long)tid);
            break;
        }
    }
    fclose(f);
    return leader;
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
        if (child > 0 && is_process_leader((pid_t)child)) {
            total += proc_tree_rss_bytes((pid_t)child);
        }
        p = end;
    }
    return total;
}
#endif  // __linux__

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
    return get_bin_dir();
}

Str *til_realpath(const Str *path) {
    return realpath_str(path);
}

I32 til_system(const Str *cmd) {
#ifdef __EMSCRIPTEN__
    (void)cmd;
    return 1;
#else
    int status = system((const char *)cmd->c_str);
#ifdef _WIN32
    return (I32)status;
#else
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return 1;
#endif
#endif
}

#ifdef _WIN32
Bool ffi_load_global_lib(const Str *soname) {
    return LoadLibraryA((const char *)soname->c_str) != NULL;
}

Bool ffi_open_user_so(const Str *path) {
    ffi_handle = LoadLibraryA((const char *)path->c_str);
    return ffi_handle != NULL;
}

void ffi_close_user_so(void) {
    if (ffi_handle) {
        FreeLibrary(ffi_handle);
        ffi_handle = NULL;
    }
}

U8 *ffi_user_symbol(const Str *name) {
    if (!ffi_handle) return NULL;
    return (U8 *)GetProcAddress(ffi_handle, (const char *)name->c_str);
}

U8 *ffi_global_symbol(const Str *name) {
    // Walk loaded modules looking for the symbol. Mirrors RTLD_DEFAULT
    // semantics well enough for the built-in libs til links against.
    HMODULE mods[256];
    DWORD needed = 0;
    if (!EnumProcessModules(GetCurrentProcess(), mods, sizeof(mods), &needed)) return NULL;
    DWORD count = needed / sizeof(HMODULE);
    if (count > 256) count = 256;
    for (DWORD i = 0; i < count; i++) {
        FARPROC p = GetProcAddress(mods[i], name->c_str);
        if (p) return (U8 *)p;
    }
    return NULL;
}

Str *ffi_last_error(void) {
    DWORD err = GetLastError();
    if (!err) {
        return Str_clone(&(Str){.c_str = (I8 *)"", .count = 0, .cap = CAP_LIT});
    }
    char buf[512];
    DWORD n = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, err, 0, buf, sizeof(buf), NULL);
    if (n == 0) {
        snprintf(buf, sizeof(buf), "Windows error %lu", (unsigned long)err);
        n = (DWORD)strlen(buf);
    }
    return Str_clone(&(Str){.c_str = (I8 *)buf, .count = (USize)n, .cap = CAP_VIEW});
}
#elif defined(__EMSCRIPTEN__)
Bool ffi_load_global_lib(const Str *soname) {
    (void)soname;
    return 0;
}

Bool ffi_open_user_so(const Str *path) {
    (void)path;
    return 0;
}

void ffi_close_user_so(void) {
}

U8 *ffi_user_symbol(const Str *name) {
    (void)name;
    return NULL;
}

U8 *ffi_global_symbol(const Str *name) {
    (void)name;
    return NULL;
}

Str *ffi_last_error(void) {
    return Str_clone(&(Str){.c_str = (I8 *)"", .count = 0, .cap = CAP_LIT});
}
#else
Bool ffi_load_global_lib(const Str *soname) {
    return dlopen((const char *)soname->c_str, RTLD_NOW | RTLD_GLOBAL) != NULL;
}

Bool ffi_open_user_so(const Str *path) {
    ffi_handle = dlopen((const char *)path->c_str, RTLD_NOW);
    return ffi_handle != NULL;
}

void ffi_close_user_so(void) {
    if (ffi_handle) {
        dlclose(ffi_handle);
        ffi_handle = NULL;
    }
}

U8 *ffi_user_symbol(const Str *name) {
    if (!ffi_handle) return NULL;
    return dlsym(ffi_handle, (const char *)name->c_str);
}

U8 *ffi_global_symbol(const Str *name) {
    return dlsym(RTLD_DEFAULT, (const char *)name->c_str);
}

Str *ffi_last_error(void) {
    char *msg = dlerror();
    if (!msg) {
        return Str_clone(&(Str){.c_str = (I8 *)"", .count = 0, .cap = CAP_LIT});
    }
    return Str_clone(&(Str){.c_str = (I8 *)msg, .count = (USize)strlen(msg), .cap = CAP_VIEW});
}
#endif

#ifdef __EMSCRIPTEN__
static TilClosure *til_browser_frame;

static void til_browser_frame_tick(void) {
    if (!til_browser_frame) return;
    ((void (*)(void *))til_browser_frame->call)(til_browser_frame->env);
}
#endif

void til_emscripten_set_main_loop(TilClosure *frame, I32 fps, Bool simulate_infinite_loop) {
#ifdef __EMSCRIPTEN__
    til_browser_frame = frame;
    emscripten_set_main_loop(til_browser_frame_tick, fps, simulate_infinite_loop);
#else
    (void)frame;
    (void)fps;
    (void)simulate_infinite_loop;
#endif
}

I32 stderr_print(const Str *msg) {
    fprintf(stderr, "%.*s", (int)msg->count, msg->c_str ? (char *)msg->c_str : "");
    return 0;
}

void unlink_path(const Str *path) {
#ifdef _WIN32
    _unlink((const char *)path->c_str);
#else
    unlink((const char *)path->c_str);
#endif
}

I32 process_id(void) {
#ifdef _WIN32
    return (I32)GetCurrentProcessId();
#else
    return (I32)getpid();
#endif
}

/* #299: true iff this binary was compiled with AddressSanitizer. The
 * interpreter uses it to compile a link_c() FFI library with the SAME
 * sanitizer flags as itself: under bin/til_asan the user .so must share the
 * ASAN allocator, otherwise an interpreter-side malloc/calloc that libffi
 * routes to the (non-ASAN) user .so's libc allocator gets freed by the
 * interpreter's ASAN free() -- a spurious bad-free. */
Bool til_built_with_asan(void) {
#if defined(__SANITIZE_ADDRESS__)
    return 1;
#elif defined(__has_feature)
# if __has_feature(address_sanitizer)
    return 1;
# else
    return 0;
# endif
#else
    return 0;
#endif
}

Str *til_str_left(const Str *s, U64 n) {
    if (!s || n == 0) return Str_clone(&(Str){.c_str = (I8*)"", .count = 0, .cap = CAP_LIT});
    USize len = (USize)s->count;
    if (n > len) n = len;
    char *buf = malloc(n + 1);
    memcpy(buf, s->c_str, n);
    buf[n] = '\0';
    Str *result = Str_clone(&(Str){.c_str = (I8*)buf, .count = n, .cap = CAP_VIEW});
    free(buf);
    return result;
}

// --- `til build --prof`: per-function CPU + allocation profiler ---
//
// Active only in binaries compiled with -finstrument-functions, which
// `til build --prof` adds (mirroring how --asan adds -fsanitize=address).
// gcc then inserts __cyg_profile_func_enter/exit at every function
// boundary; we accumulate per-function call counts and inclusive/self
// time, and dump a top-N table to stderr at exit (atexit). Function names
// are resolved with dladdr -- looked up via dlsym(RTLD_DEFAULT) so we do
// not depend on _GNU_SOURCE -- and the build links -rdynamic, so the til
// function names show through as the C symbol names (Map_set, Vec_push,
// the typer_* helpers, ...). Set TIL_PROF_TOP=N to change the row count
// (0 = all).
//
// With -DTIL_PROF_ALLOC (added by --prof unless --asan, since asan owns
// malloc) the build also wraps malloc/calloc/realloc via -Wl,--wrap; the
// wrappers charge the bytes to whichever instrumented function is on top of
// the call stack, and a second "top by bytes allocated" table is printed.
// That answers "which callsite mallocs the most / which Vec reallocs worst".
//
// Not built on Windows; intended for the single-threaded self-host build,
// so the stats counters are not lock-protected (the call stack is
// per-thread, so multithreaded programs will not crash but their counters
// may race).
#if !defined(_WIN32) && !defined(__EMSCRIPTEN__)

typedef struct {
    const char *dli_fname;
    void       *dli_fbase;
    const char *dli_sname;
    void       *dli_saddr;
} TilDlInfo;

#define TIL_PROF_SLOTS (1u << 17)   // open-addressed by function pointer
#define TIL_PROF_STACK (1u << 14)   // max instrumented call depth

typedef struct {
    void *fn;                       // NULL = empty slot
    unsigned long long calls;
    unsigned long long total_ns;    // inclusive (self + callees)
    unsigned long long self_ns;     // exclusive
    unsigned long long allocs;      // malloc/calloc/realloc calls (TIL_PROF_ALLOC)
    unsigned long long alloc_bytes; // bytes requested through them
} TilProfSlot;

typedef struct {
    unsigned idx;
    unsigned long long start;
    unsigned long long child_ns;
} TilProfFrame;

static TilProfSlot til_prof_slots[TIL_PROF_SLOTS];
static __thread TilProfFrame til_prof_stack[TIL_PROF_STACK];
static __thread unsigned til_prof_depth;
static int til_prof_registered;

static unsigned long long til_prof_now(void) __attribute__((no_instrument_function));
static unsigned long long til_prof_now(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long long)ts.tv_sec * 1000000000ULL + (unsigned long long)ts.tv_nsec;
}

static unsigned til_prof_slot(void *fn) __attribute__((no_instrument_function));
static unsigned til_prof_slot(void *fn) {
    unsigned h = (unsigned)(((uintptr_t)fn >> 4) * 2654435761u) & (TIL_PROF_SLOTS - 1u);
    for (unsigned i = 0; i < TIL_PROF_SLOTS; i++) {
        unsigned j = (h + i) & (TIL_PROF_SLOTS - 1u);
        if (til_prof_slots[j].fn == fn) return j;
        if (til_prof_slots[j].fn == NULL) { til_prof_slots[j].fn = fn; return j; }
    }
    return 0;   // table full: should not happen with the headroom above
}

static int til_prof_cmp_self(const void *a, const void *b) __attribute__((no_instrument_function));
static int til_prof_cmp_self(const void *a, const void *b) {
    const TilProfSlot *x = *(const TilProfSlot *const *)a;
    const TilProfSlot *y = *(const TilProfSlot *const *)b;
    if (y->self_ns > x->self_ns) return 1;
    if (y->self_ns < x->self_ns) return -1;
    return 0;
}

static int til_prof_cmp_bytes(const void *a, const void *b) __attribute__((no_instrument_function));
static int til_prof_cmp_bytes(const void *a, const void *b) {
    const TilProfSlot *x = *(const TilProfSlot *const *)a;
    const TilProfSlot *y = *(const TilProfSlot *const *)b;
    if (y->alloc_bytes > x->alloc_bytes) return 1;
    if (y->alloc_bytes < x->alloc_bytes) return -1;
    return 0;
}

static const char *til_prof_name(const TilProfSlot *s, void *pd) __attribute__((no_instrument_function));
static const char *til_prof_name(const TilProfSlot *s, void *pd) {
    typedef int (*til_dladdr_fn)(const void *, TilDlInfo *);
    til_dladdr_fn pdladdr = (til_dladdr_fn)pd;
    TilDlInfo info;
    if (pdladdr && pdladdr(s->fn, &info) && info.dli_sname) return info.dli_sname;
    return "(unknown)";
}

static void til_prof_report(void) __attribute__((no_instrument_function));
static void til_prof_report(void) {
    static const TilProfSlot *order[TIL_PROF_SLOTS];
    unsigned n = 0;
    unsigned long long total_allocs = 0;
    for (unsigned i = 0; i < TIL_PROF_SLOTS; i++) {
        if (til_prof_slots[i].fn && til_prof_slots[i].calls) {
            order[n++] = &til_prof_slots[i];
            total_allocs += til_prof_slots[i].allocs;
        }
    }

    unsigned want = 20;
    const char *env = getenv("TIL_PROF_TOP");
    if (env) want = (unsigned)strtoul(env, NULL, 10);
    if (want == 0 || want > n) want = n;

    void *pd = dlsym(RTLD_DEFAULT, "dladdr");

    qsort(order, n, sizeof(order[0]), til_prof_cmp_self);
    fprintf(stderr, "\n=== til --prof: %u functions instrumented, top %u by self time ===\n", n, want);
    fprintf(stderr, "%-48s %14s %12s %12s\n", "function", "calls", "self_ms", "total_ms");
    for (unsigned i = 0; i < want; i++) {
        const TilProfSlot *s = order[i];
        fprintf(stderr, "%-48s %14llu %12.3f %12.3f\n",
                til_prof_name(s, pd), s->calls, (double)s->self_ns / 1e6, (double)s->total_ns / 1e6);
    }

    if (total_allocs > 0) {
        qsort(order, n, sizeof(order[0]), til_prof_cmp_bytes);
        fprintf(stderr, "\n=== til --prof: top %u by bytes allocated ===\n", want);
        fprintf(stderr, "%-48s %14s %14s %14s\n", "function", "allocs", "alloc_kb", "calls");
        for (unsigned i = 0; i < want; i++) {
            const TilProfSlot *s = order[i];
            fprintf(stderr, "%-48s %14llu %14.1f %14llu\n",
                    til_prof_name(s, pd), s->allocs, (double)s->alloc_bytes / 1024.0, s->calls);
        }
    }
}

void __cyg_profile_func_enter(void *this_fn, void *call_site) __attribute__((no_instrument_function));
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
    (void)call_site;
    if (!til_prof_registered) { til_prof_registered = 1; atexit(til_prof_report); }
    if (til_prof_depth >= TIL_PROF_STACK) return;
    unsigned idx = til_prof_slot(this_fn);
    til_prof_slots[idx].calls++;
    TilProfFrame *f = &til_prof_stack[til_prof_depth++];
    f->idx = idx;
    f->start = til_prof_now();
    f->child_ns = 0;
}

void __cyg_profile_func_exit(void *this_fn, void *call_site) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
    (void)this_fn;
    (void)call_site;
    if (til_prof_depth == 0) return;
    TilProfFrame *f = &til_prof_stack[--til_prof_depth];
    unsigned long long incl = til_prof_now() - f->start;
    til_prof_slots[f->idx].total_ns += incl;
    til_prof_slots[f->idx].self_ns  += incl - f->child_ns;
    if (til_prof_depth > 0) til_prof_stack[til_prof_depth - 1].child_ns += incl;
}

#ifdef TIL_PROF_ALLOC
// --prof (unless --asan) links -Wl,--wrap=malloc/calloc/realloc, so these
// wrappers see every heap allocation. They charge the bytes to whichever
// instrumented function is on top of the call stack (allocations before the
// first instrumented call, e.g. C runtime startup, are not attributed). free
// is left unwrapped: __real_malloc'd pointers are released by the real free.
extern void *__real_malloc(size_t size);
extern void *__real_calloc(size_t nmemb, size_t size);
extern void *__real_realloc(void *ptr, size_t size);

static void til_prof_charge(unsigned long long bytes) __attribute__((no_instrument_function));
static void til_prof_charge(unsigned long long bytes) {
    if (til_prof_depth == 0) return;
    unsigned idx = til_prof_stack[til_prof_depth - 1].idx;
    til_prof_slots[idx].allocs++;
    til_prof_slots[idx].alloc_bytes += bytes;
}

void *__wrap_malloc(size_t size) __attribute__((no_instrument_function));
void *__wrap_malloc(size_t size) {
    til_prof_charge((unsigned long long)size);
    return __real_malloc(size);
}

void *__wrap_calloc(size_t nmemb, size_t size) __attribute__((no_instrument_function));
void *__wrap_calloc(size_t nmemb, size_t size) {
    til_prof_charge((unsigned long long)nmemb * (unsigned long long)size);
    return __real_calloc(nmemb, size);
}

void *__wrap_realloc(void *ptr, size_t size) __attribute__((no_instrument_function));
void *__wrap_realloc(void *ptr, size_t size) {
    til_prof_charge((unsigned long long)size);
    return __real_realloc(ptr, size);
}
#endif // TIL_PROF_ALLOC

#endif // !_WIN32 && !__EMSCRIPTEN__

// Leak measurement. Runs as a destructor -- after main() returns, i.e. after
// the program has finished tearing its data structures down -- and prints the
// sanitizer's live-allocated byte count. That is the true never-freed total.
// Unlike LeakSanitizer's "N byte(s) leaked", it is independent of ASAN config
// and immune to inter-leak false-reachability (leaked blocks pointing at each
// other), which makes the LSAN number under-report by orders of magnitude and
// swing several-fold with trivial option changes. Gated on TIL_LEAK_PROBE so
// normal runs are unaffected; examples/merge_commit.til sets it to record the
// ASAN baseline. The weak decl lets non-sanitizer builds link (symbol is NULL
// there, and the address check skips the call).
// glibc-only block: the undefined-weak + address-check idiom is an ELF
// linker feature -- Mach-O rejects the undefined symbols outright (issue
// #25), and the probe measures glibc internals anyway, so gate the whole
// probe on __GLIBC__ rather than declaring it weak everywhere.
#if defined(__GLIBC__)
__attribute__((weak)) unsigned long __sanitizer_get_current_allocated_bytes(void);
// glibc's "release every internal allocation" entry point (what mtrace and
// valgrind drive). Weak so non-glibc builds link with it NULL.
__attribute__((weak)) void __libc_freeres(void);
static void til_leak_probe(void) __attribute__((destructor));
static void til_leak_probe(void) {
    if (!getenv("TIL_LEAK_PROBE")) return;
    // Flush and release libc's own stdio write buffer before measuring: the
    // stdout st_blksize buffer (~4096B) is libc-owned and reclaimed at exit,
    // and is only live here because this destructor runs before libc's stdio
    // teardown -- it is not a til leak. (translate prints its success line to
    // stdout via println, so only the translate channel showed this 4096-byte
    // floor; interpret writes to stderr.)
    fflush(NULL);
    fclose(stdout);
    // Same reasoning, one layer deeper: glibc keeps process-lifetime internal
    // allocations live until ITS exit teardown, which runs AFTER this
    // destructor. The dominant one is the dynamic loader's _dl_find_object
    // mapping segment (~2.3KB), allocated by dlopen the first time any FFI .so
    // is loaded and kept for the whole process by glibc's lock-free design --
    // so dlclose (ffi_cleanup already does it) does not reclaim it, and it is
    // reachable via ld.so globals (LSAN never flags it) yet inflates the raw
    // allocated-bytes count below. __libc_freeres releases it (and the rest of
    // glibc's internal state) so TIL_TRUE_LEAK reflects only til-owned memory.
    // It frees ONLY glibc-internal allocations, never til's, so real til leaks
    // still count. stderr is unbuffered, so the print below survives it.
    if (&__libc_freeres) __libc_freeres();
    if (&__sanitizer_get_current_allocated_bytes)
        fprintf(stderr, "TIL_TRUE_LEAK=%lu\n", __sanitizer_get_current_allocated_bytes());
}
#endif  // __GLIBC__
