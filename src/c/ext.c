#include "../../boot/til_forward.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

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
#endif
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
        DWORD len = GetEnvironmentVariableA(name, NULL, 0);
        if (len > 0) return 0;
    }
    if (SetEnvironmentVariableA(name, value)) return 0;
    return 1;
#else
    return (I32)setenv(name, value, overwrite);
#endif
}

// I64 clone
I64 I64_clone(const I64 *v) { return *v; }

// I64 arithmetic (shallow params, shallow return)
I64 I64_add(I64 a, I64 b) { return a + b; }
I64 I64_sub(I64 a, I64 b) { return a - b; }
I64 I64_mul(I64 a, I64 b) { return a * b; }
I64 I64_div(I64 a, I64 b) { return (b == 0) ? 0 : a / b; }
I64 I64_mod(I64 a, I64 b) { return (b == 0) ? 0 : a % b; }
I64 I64_band(I64 a, I64 b) { return a & b; }
I64 I64_bor(I64 a, I64 b) { return a | b; }
I64 I64_bxor(I64 a, I64 b) { return a ^ b; }
I64 I64_bnot(I64 a) { return ~a; }
I64 I64_shl(I64 a, I64 b) { return a << b; }
I64 I64_shr(I64 a, I64 b) { return a >> b; }

// I64 comparisons
Bool I64_eq(I64 a, I64 b) { return a == b; }
I64 I64_cmp(I64 a, I64 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }


// U8 arithmetic
U8 U8_add(U8 a, U8 b) { return a + b; }
U8 U8_sub(U8 a, U8 b) { return a - b; }
U8 U8_mul(U8 a, U8 b) { return a * b; }
U8 U8_div(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a / b); }
U8 U8_mod(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a % b); }
U8 U8_band(U8 a, U8 b) { return a & b; }
U8 U8_bor(U8 a, U8 b) { return a | b; }
U8 U8_bxor(U8 a, U8 b) { return a ^ b; }
U8 U8_bnot(U8 a) { return (U8)~a; }
U8 U8_shl(U8 a, U8 b) { return (U8)(a << b); }
U8 U8_shr(U8 a, U8 b) { return (U8)(a >> b); }

// U8 comparisons
Bool U8_eq(U8 a, U8 b) { return a == b; }
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
I8 I8_add(I8 a, I8 b) { return a + b; }
I8 I8_sub(I8 a, I8 b) { return a - b; }
I8 I8_mul(I8 a, I8 b) { return a * b; }
I8 I8_div(I8 a, I8 b) { return (b == 0) ? 0 : (I8)(a / b); }
I8 I8_mod(I8 a, I8 b) { return (b == 0) ? 0 : (I8)(a % b); }
I8 I8_band(I8 a, I8 b) { return a & b; }
I8 I8_bor(I8 a, I8 b) { return a | b; }
I8 I8_bxor(I8 a, I8 b) { return a ^ b; }
I8 I8_bnot(I8 a) { return (I8)~a; }
I8 I8_shl(I8 a, I8 b) { return (I8)(a << b); }
I8 I8_shr(I8 a, I8 b) { return a >> b; }

// I8 comparisons
Bool I8_eq(I8 a, I8 b) { return a == b; }
I64 I8_cmp(I8 a, I8 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// I8 conversions
U64 I8_to_u64(I8 a) { return (U64)(I64)a; }
I8 I8_from_i64(I64 v) { return (I8)v; }
I8 I8_from_i64_ext(const I64 *a) { return (I8)*a; }

// I8 clone
I8 I8_clone(const I8 *v) { return *v; }


// I16 arithmetic
I16 I16_add(I16 a, I16 b) { return a + b; }
I16 I16_sub(I16 a, I16 b) { return a - b; }
I16 I16_mul(I16 a, I16 b) { return a * b; }
I16 I16_div(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a / b); }
I16 I16_mod(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a % b); }
I16 I16_band(I16 a, I16 b) { return a & b; }
I16 I16_bor(I16 a, I16 b) { return a | b; }
I16 I16_bxor(I16 a, I16 b) { return a ^ b; }
I16 I16_bnot(I16 a) { return (I16)~a; }
I16 I16_shl(I16 a, I16 b) { return (I16)(a << b); }
I16 I16_shr(I16 a, I16 b) { return a >> b; }

// I16 comparisons
Bool I16_eq(I16 a, I16 b) { return a == b; }
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
U16 U16_add(U16 a, U16 b) { return (U16)(a + b); }
U16 U16_sub(U16 a, U16 b) { return (U16)(a - b); }
U16 U16_mul(U16 a, U16 b) { return (U16)(a * b); }
U16 U16_div(U16 a, U16 b) { return (b == 0) ? 0 : (U16)(a / b); }
U16 U16_mod(U16 a, U16 b) { return (b == 0) ? 0 : (U16)(a % b); }
U16 U16_band(U16 a, U16 b) { return (U16)(a & b); }
U16 U16_bor(U16 a, U16 b) { return (U16)(a | b); }
U16 U16_bxor(U16 a, U16 b) { return (U16)(a ^ b); }
U16 U16_bnot(U16 a) { return (U16)~a; }
U16 U16_shl(U16 a, U16 b) { return (U16)(a << b); }
U16 U16_shr(U16 a, U16 b) { return (U16)(a >> b); }

// U16 comparisons
Bool U16_eq(U16 a, U16 b) { return a == b; }
I64 U16_cmp(U16 a, U16 b) { return (a > b) ? 1 : (a < b) ? -1 : 0; }

// U16 conversions
I64 U16_to_i64(U16 a) { return (I64)a; }
F32 U16_to_f32(U16 a) { return (F32)a; }
U16 U16_from_i64(I64 v) { return (U16)v; }
U16 U16_from_i64_ext(const I64 *a) { return (U16)*a; }

// U16 clone
U16 U16_clone(const U16 *v) { return *v; }

// I32 arithmetic
I32 I32_add(I32 a, I32 b) { return a + b; }
I32 I32_sub(I32 a, I32 b) { return a - b; }
I32 I32_mul(I32 a, I32 b) { return a * b; }
I32 I32_div(I32 a, I32 b) { return (b == 0) ? 0 : a / b; }
I32 I32_mod(I32 a, I32 b) { return (b == 0) ? 0 : a % b; }
I32 I32_band(I32 a, I32 b) { return a & b; }
I32 I32_bor(I32 a, I32 b) { return a | b; }
I32 I32_bxor(I32 a, I32 b) { return a ^ b; }
I32 I32_bnot(I32 a) { return ~a; }
I32 I32_shl(I32 a, I32 b) { return a << b; }
I32 I32_shr(I32 a, I32 b) { return a >> b; }

// I32 comparisons
Bool I32_eq(I32 a, I32 b) { return a == b; }
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
F32 F32_add(F32 a, F32 b) { return a + b; }
F32 F32_sub(F32 a, F32 b) { return a - b; }
F32 F32_mul(F32 a, F32 b) { return a * b; }
F32 F32_div(F32 a, F32 b) { return (b == 0) ? 0 : a / b; }

// F32 comparisons
Bool F32_eq(F32 a, F32 b) { return a == b; }
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
    char *p = dup_n(s->c_str, s->count);
    float v = strtof(p, NULL);
    free(p);
    return (F32)v;
}



// F32 clone
F32 F32_clone(const F32 *v) { return *v; }

// U32 arithmetic
U32 U32_add(U32 a, U32 b) { return a + b; }
U32 U32_sub(U32 a, U32 b) { return a - b; }
U32 U32_mul(U32 a, U32 b) { return a * b; }
U32 U32_div(U32 a, U32 b) { return (b == 0) ? 0 : a / b; }
U32 U32_mod(U32 a, U32 b) { return (b == 0) ? 0 : a % b; }
U32 U32_band(U32 a, U32 b) { return a & b; }
U32 U32_bor(U32 a, U32 b) { return a | b; }
U32 U32_bxor(U32 a, U32 b) { return a ^ b; }
U32 U32_bnot(U32 a) { return ~a; }
U32 U32_shl(U32 a, U32 b) { return a << b; }
U32 U32_shr(U32 a, U32 b) { return a >> b; }

// U32 comparisons
Bool U32_eq(U32 a, U32 b) { return a == b; }
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
U64 U64_add(U64 a, U64 b) { return a + b; }
U64 U64_sub(U64 a, U64 b) { return a - b; }
U64 U64_mul(U64 a, U64 b) { return a * b; }
U64 U64_div(U64 a, U64 b) { return (b == 0) ? 0 : a / b; }
U64 U64_mod(U64 a, U64 b) { return (b == 0) ? 0 : a % b; }
U64 U64_band(U64 a, U64 b) { return a & b; }
U64 U64_bor(U64 a, U64 b) { return a | b; }
U64 U64_bxor(U64 a, U64 b) { return a ^ b; }
U64 U64_bnot(U64 a) { return ~a; }
U64 U64_shl(U64 a, U64 b) { return a << b; }
U64 U64_shr(U64 a, U64 b) { return a >> b; }

// U64 comparisons
Bool U64_eq(U64 a, U64 b) { return a == b; }
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

// Bool ops (shallow params, shallow return)
Bool Bool_eq(Bool a, Bool b) { return a == b; }
Bool not(Bool a) { return !a; }
Bool band(Bool a, Bool b) { return a && b; }
Bool bor(Bool a, Bool b) { return a || b; }
Bool bxor(Bool a, Bool b) { return a != b; }


// Bool clone
Bool Bool_clone(const Bool *v) { return *v; }

// Pointer primitives (custom, not in libc). See ext.h for why these
// keep non-const inputs.
void *ptr_add(void *buf, UPtr offset) {
    return (char *)buf + offset;
}
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
Bool is(void *self, void *other) { return *(I32*)self == *(I32*)other; }
/* #264: compare enum tags of a chosen width without over-reading a struct
 * narrower than 4 bytes (enum(U8)/enum(U16)) or under-reading a wider one
 * (enum(U64)). */
Bool is_n(void *self, void *other, USize size) {
    switch (size) {
    case 1: return *(U8*)self == *(U8*)other;
    case 2: return *(U16*)self == *(U16*)other;
    case 8: return *(U64*)self == *(U64*)other;
    default: return *(U32*)self == *(U32*)other;
    }
}
void *get_payload(void *self) { return (U8*)self + sizeof(void *); }

// CLI arg parsing

// --- System primitives ---
// These use the codegen Str layout: { U8 *c_str, U64 count, U64 cap }.

Str *File_readfile(const Str *path) {
    char *p = dup_n(path->c_str, path->count);
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

void File_writefile(const Str *path, const Str *content) {
    char *p = dup_n(path->c_str, path->count);
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

// --- File handle I/O ---

void *cfile_open(const Str *path, Bool is_write) {
    char *p = dup_n(path->c_str, path->count);
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

void cfile_write_str(void *handle, const Str *s) {
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
    char *p = dup_n(path->c_str, path->count);
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
I64 cfile_tell(void *handle) {
    if (!handle) {
        fprintf(stderr, "cfile_tell: file not open\n");
        exit(1);
    }
    return (I64)ftell((FILE *)handle);
}

// Move the cursor to an absolute byte offset from the start of the file.
void cfile_seek(void *handle, I64 pos) {
    if (!handle) {
        fprintf(stderr, "cfile_seek: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)pos, SEEK_SET);
}

// Move the cursor by `delta` bytes relative to its current position
// (delta may be negative).
void cfile_seek_cur(void *handle, I64 delta) {
    if (!handle) {
        fprintf(stderr, "cfile_seek_cur: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)delta, SEEK_CUR);
}

// Move the cursor to `delta` bytes relative to the end of the file
// (delta is typically <= 0; seek_end(0) puts the cursor at EOF, so a
// following tell() yields the file size).
void cfile_seek_end(void *handle, I64 delta) {
    if (!handle) {
        fprintf(stderr, "cfile_seek_end: file not open\n");
        exit(1);
    }
    fseek((FILE *)handle, (long)delta, SEEK_END);
}

// Read up to `count` bytes starting at the current cursor position. The
// returned Str's count reflects how many bytes were actually read (fewer
// than `count` near end-of-file).
Str *cfile_read_n(void *handle, I64 count) {
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
    char *c = dup_n(cmd->c_str, cmd->count);
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
    char *p = dup_n(path->c_str, path->count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return -1;
    return (I64)st.st_mtime;
}

I32 mkdir_p(const Str *path) {
    char *p = dup_n(path->c_str, path->count);
    int rc = mkdir_p_cstr(p);
    if (rc != 0) fprintf(stderr, "mkdir_p: failed for '%s'\n", p);
    free(p);
    return (I32)rc;
}

I32 copy_file(const Str *src, const Str *dst) {
    char *s = dup_n(src->c_str, src->count);
    char *d = dup_n(dst->c_str, dst->count);
    int rc = copy_file_cstr(s, d);
    if (rc != 0) fprintf(stderr, "copy_file: failed from '%s' to '%s'\n", s, d);
    free(s);
    free(d);
    return (I32)rc;
}

I32 copy_tree(const Str *src, const Str *dst) {
    char *s = dup_n(src->c_str, src->count);
    char *d = dup_n(dst->c_str, dst->count);
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

#if !defined(_WIN32) && !defined(__EMSCRIPTEN__)
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
#endif  // !_WIN32

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
    int status = system(cmd->c_str);
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
    return LoadLibraryA(soname->c_str) != NULL;
}

Bool ffi_open_user_so(const Str *path) {
    ffi_handle = LoadLibraryA(path->c_str);
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
    return (U8 *)GetProcAddress(ffi_handle, name->c_str);
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
    return dlopen(soname->c_str, RTLD_NOW | RTLD_GLOBAL) != NULL;
}

Bool ffi_open_user_so(const Str *path) {
    ffi_handle = dlopen(path->c_str, RTLD_NOW);
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
    return dlsym(ffi_handle, name->c_str);
}

U8 *ffi_global_symbol(const Str *name) {
    return dlsym(RTLD_DEFAULT, name->c_str);
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
    _unlink(path->c_str);
#else
    unlink(path->c_str);
#endif
}

I32 process_id(void) {
#ifdef _WIN32
    return (I32)GetCurrentProcessId();
#else
    return (I32)getpid();
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

// --- `til build --prof`: per-function CPU + call profiler ---
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
// (0 = all). Not built on Windows; intended for the single-threaded
// self-host build, so the stats counters are not lock-protected (the call
// stack is per-thread, so multithreaded programs will not crash but their
// counters may race).
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

static int til_prof_cmp(const void *a, const void *b) __attribute__((no_instrument_function));
static int til_prof_cmp(const void *a, const void *b) {
    const TilProfSlot *x = *(const TilProfSlot *const *)a;
    const TilProfSlot *y = *(const TilProfSlot *const *)b;
    if (y->self_ns > x->self_ns) return 1;
    if (y->self_ns < x->self_ns) return -1;
    return 0;
}

static void til_prof_report(void) __attribute__((no_instrument_function));
static void til_prof_report(void) {
    static const TilProfSlot *order[TIL_PROF_SLOTS];
    unsigned n = 0;
    for (unsigned i = 0; i < TIL_PROF_SLOTS; i++) {
        if (til_prof_slots[i].fn && til_prof_slots[i].calls) order[n++] = &til_prof_slots[i];
    }
    qsort(order, n, sizeof(order[0]), til_prof_cmp);

    unsigned want = 20;
    const char *env = getenv("TIL_PROF_TOP");
    if (env) want = (unsigned)strtoul(env, NULL, 10);
    if (want == 0 || want > n) want = n;

    typedef int (*til_dladdr_fn)(const void *, TilDlInfo *);
    til_dladdr_fn pdladdr = (til_dladdr_fn)dlsym(RTLD_DEFAULT, "dladdr");

    fprintf(stderr, "\n=== til --prof: %u functions instrumented, top %u by self time ===\n", n, want);
    fprintf(stderr, "%-48s %14s %12s %12s\n", "function", "calls", "self_ms", "total_ms");
    for (unsigned i = 0; i < want; i++) {
        const TilProfSlot *s = order[i];
        const char *name = "(unknown)";
        TilDlInfo info;
        if (pdladdr && pdladdr(s->fn, &info) && info.dli_sname) name = info.dli_sname;
        fprintf(stderr, "%-48s %14llu %12.3f %12.3f\n",
                name, s->calls, (double)s->self_ns / 1e6, (double)s->total_ns / 1e6);
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
__attribute__((weak)) unsigned long __sanitizer_get_current_allocated_bytes(void);
static void til_leak_probe(void) __attribute__((destructor));
static void til_leak_probe(void) {
    if (!getenv("TIL_LEAK_PROBE")) return;
    if (&__sanitizer_get_current_allocated_bytes)
        fprintf(stderr, "TIL_TRUE_LEAK=%lu\n", __sanitizer_get_current_allocated_bytes());
}
