/*
 * ext.c - TIL External C Interface
 *
 * Has to be included in the right place of the output file, after the forward declarations and struct declarations.
 */

#ifndef TIL_EXT_C
#define TIL_EXT_C

// Str helper: create Str from C string literal
static inline til_Str til_Str_from_literal(const char* lit)
{
    til_Str s;
    s.c_string = (til_I64)lit;
    s.cap = strlen(lit);
    return s;
}

// single_print: print a string without newline
static inline void til_single_print(til_Str s)
{
    printf("%s", (char*)s.c_string);
}

// print_flush: flush stdout
static inline void til_print_flush(void)
{
    fflush(stdout);
}

// to_ptr: get pointer address as integer
static inline til_I64 til_to_ptr(til_I64* p)
{
    return (til_I64)p;
}

// Type conversion helpers
static inline til_I64 til_u8_to_i64(til_U8 v)
{
    return (til_I64)v;
}

static inline til_U8 til_i64_to_u8(til_I64 v)
{
    return (til_U8)v;
}

// Arithmetic functions
static inline til_Bool til_lt(til_I64 a, til_I64 b)
{
    return (til_Bool){a < b};
}

static inline til_Bool til_gt(til_I64 a, til_I64 b)
{
    return (til_Bool){a > b};
}

static inline til_I64 til_add(til_I64 a, til_I64 b)
{
    return a + b;
}

static inline til_I64 til_sub(til_I64 a, til_I64 b)
{
    return a - b;
}

static inline til_I64 til_mul(til_I64 a, til_I64 b)
{
    return a * b;
}

static inline til_I64 til_div(til_I64 a, til_I64 b)
{
    return b == 0 ? 0 : a / b;
}

static inline til_I64 til_mod(til_I64 a, til_I64 b)
{
    return b == 0 ? 0 : a % b;
}

// Memory functions
static inline int til_malloc(til_I64* _ret, til_AllocError* _err, til_I64 size)
{
    *_ret = (til_I64)malloc((size_t)size);
    return 0;
}

static inline void til_free(til_I64 ptr)
{
    free((void*)ptr);
}

static inline void til_memcpy(til_I64 dest, til_I64 src, til_I64 n)
{
    memcpy((void*)dest, (void*)src, (size_t)n);
}

static inline til_I64 til_memcmp(til_I64 a, til_I64 b, til_I64 n)
{
    return (til_I64)memcmp((void*)a, (void*)b, (size_t)n);
}

static inline void til_memset(til_I64 ptr, til_U8 value, til_I64 n)
{
    memset((void*)ptr, (int)value, (size_t)n);
}

// Process control
static inline void til_exit(til_I64 code)
{
    exit((int)code);
}

// String conversion functions
static inline til_Str til_i64_to_str(til_I64 v)
{
    static char buf[32];
    snprintf(buf, sizeof(buf), "%lld", (long long)v);
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = strlen(buf);
    return s;
}

static inline til_I64 til_str_to_i64(til_Str s)
{
    return (til_I64)strtoll((const char*)s.c_string, NULL, 10);
}

// I/O functions

// input_read_line: read a line from stdin
static inline til_Str til_input_read_line(void)
{
    static char buf[4096];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        buf[0] = '\0';
    }
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = strlen(buf);
    return s;
}

// readfile: read entire file contents
static inline til_Str til_readfile(til_Str path)
{
    FILE* f = fopen((const char*)path.c_string, "rb");
    if (!f) {
        til_Str s = {0, 0};
        return s;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        fclose(f);
        til_Str s = {0, 0};
        return s;
    }
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = len;
    return s;
}

// writefile: write string to file
static inline til_I64 til_writefile(til_Str path, til_Str contents)
{
    FILE* f = fopen((const char*)path.c_string, "wb");
    if (!f) {
        return -1;
    }
    size_t written = fwrite((const char*)contents.c_string, 1, contents.cap, f);
    fclose(f);
    return (til_I64)written;
}

// run_cmd: run shell command and return stdout
static inline til_Str til_run_cmd(til_Str cmd)
{
    static char buf[65536];
    FILE* f = popen((const char*)cmd.c_string, "r");
    if (!f) {
        buf[0] = '\0';
        til_Str s;
        s.c_string = (til_I64)buf;
        s.cap = 0;
        return s;
    }
    size_t total = 0;
    while (total < sizeof(buf) - 1) {
        size_t n = fread(buf + total, 1, sizeof(buf) - 1 - total, f);
        if (n == 0) break;
        total += n;
    }
    buf[total] = '\0';
    pclose(f);
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = total;
    return s;
}

#endif /* TIL_EXT_C */
