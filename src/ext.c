/*
 * ext.c - TIL External C Interface
 *
 * Has to be included in the right place of the output file, after the forward declarations and struct declarations.
 */

#ifndef TIL_EXT_C
#define TIL_EXT_C

// Forward declarations
static inline til_I64 til_size_of(const til_Str* type_name);

// Bool constants
#define true ((til_Bool){1})
#define false ((til_Bool){0})

// single_print: print a string without newline
static inline void til_single_print(const til_Str* s)
{
    printf("%s", (char*)s->c_string.data);
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

// enum_get_payload: extract enum payload into out parameter
// Takes enum as Dynamic*, payload type name as Str*, out as Dynamic*
static inline void til_enum_get_payload(til_Dynamic* enum_ptr, const til_Str* payload_type, til_Dynamic* out_ptr)
{
    // Get payload size from type name
    til_I64 payload_size = til_size_of(payload_type);
    // Copy payload bytes from enum to out
    // Enum layout: tag (til_I64) + payload union
    // Bug #137: enum tags are til_I64 to ensure consistent offset
    memcpy(out_ptr, (char*)enum_ptr + sizeof(til_I64), (size_t)payload_size);
}

// Type conversion helpers
static inline til_I64 til_u8_to_i64(const til_U8* v)
{
    return (til_I64)*v;
}

static inline til_U8 til_i64_to_u8(const til_I64* v)
{
    return (til_U8)*v;
}

// U8 wrapping addition (mod 256)
til_U8 til_u8_add(const til_U8* a, const til_U8* b)
{
    return (til_U8)((*a + *b) & 0xFF);
}

// U8 wrapping subtraction (mod 256)
til_U8 til_u8_sub(const til_U8* a, const til_U8* b)
{
    return (til_U8)((*a - *b) & 0xFF);
}

// U8 wrapping multiplication (mod 256)
til_U8 til_u8_mul(const til_U8* a, const til_U8* b)
{
    return (til_U8)((*a * *b) & 0xFF);
}

// U8 division (returns 0 on divide by zero)
til_U8 til_u8_div(const til_U8* a, const til_U8* b)
{
    return *b == 0 ? 0 : (til_U8)(*a / *b);
}

// U8 modulo (returns 0 on divide by zero)
til_U8 til_u8_mod(const til_U8* a, const til_U8* b)
{
    return *b == 0 ? 0 : (til_U8)(*a % *b);
}

// U8 bitwise xor
til_U8 til_u8_xor(const til_U8* a, const til_U8* b)
{
    return (til_U8)(*a ^ *b);
}

// U8 bitwise and
til_U8 til_u8_and(const til_U8* a, const til_U8* b)
{
    return (til_U8)(*a & *b);
}

// U8 bitwise or
til_U8 til_u8_or(const til_U8* a, const til_U8* b)
{
    return (til_U8)(*a | *b);
}

// Arithmetic functions
static inline til_Bool til_i64_lt(const til_I64* a, const til_I64* b)
{
    return (til_Bool){*a < *b};
}

static inline til_Bool til_i64_gt(const til_I64* a, const til_I64* b)
{
    return (til_Bool){*a > *b};
}

static inline til_Bool til_u8_lt(const til_U8* a, const til_U8* b)
{
    return (til_Bool){*a < *b};
}

static inline til_Bool til_u8_gt(const til_U8* a, const til_U8* b)
{
    return (til_Bool){*a > *b};
}

static inline til_I64 til_i64_add(const til_I64* a, const til_I64* b)
{
    return *a + *b;
}

static inline til_I64 til_i64_sub(const til_I64* a, const til_I64* b)
{
    return *a - *b;
}

static inline til_I64 til_i64_mul(const til_I64* a, const til_I64* b)
{
    return *a * *b;
}

static inline til_I64 til_i64_div(const til_I64* a, const til_I64* b)
{
    return *b == 0 ? 0 : *a / *b;
}

static inline til_I64 til_i64_mod(const til_I64* a, const til_I64* b)
{
    return *b == 0 ? 0 : *a % *b;
}

// Bitwise operations
static inline til_I64 til_i64_xor(const til_I64* a, const til_I64* b)
{
    return *a ^ *b;
}

static inline til_I64 til_i64_and(const til_I64* a, const til_I64* b)
{
    return *a & *b;
}

static inline til_I64 til_i64_or(const til_I64* a, const til_I64* b)
{
    return *a | *b;
}

// Memory functions
// Issue #119: BadAlloc is an empty struct, so no error parameter needed - just return status
static inline int til_malloc(til_I64* _ret, const til_I64* size)
{
    void* ptr = malloc((size_t)*size);
    if (ptr == NULL && *size > 0) {
        return 1;  // throw BadAlloc
    }
    *_ret = (til_I64)ptr;
    return 0;
}

static inline void til_free(const til_I64* ptr)
{
    free((void*)*ptr);
}

static inline void til_memcpy(const til_I64* dest, const til_I64* src, const til_I64* n)
{
    memcpy((void*)*dest, (void*)*src, (size_t)*n);
}

static inline void til_memset(const til_I64* ptr, const til_U8* value, const til_I64* n)
{
    memset((void*)*ptr, (int)*value, (size_t)*n);
}

// Process control
static inline void til_exit(const til_I64* code)
{
    exit((int)*code);
}

// String conversion functions
static inline til_Str til_i64_to_str(const til_I64* v)
{
    char* buf = (char*)malloc(32);
    if (!buf) {
        til_Str s = {{0, 0, 0, 0, 0}, 0, 0};  // Ptr{data, is_borrowed, alloc_size, elem_type, elem_size}
        return s;
    }
    snprintf(buf, 32, "%lld", (long long)*v);
    til_Str s;
    s.c_string.data = (til_I64)buf;
    s.c_string.is_borrowed = 0;
    s.c_string.alloc_size = 32;
    s.c_string.elem_type = 0;
    s.c_string.elem_size = 0;
    s._len = strlen(buf);
    s.cap = 32;
    return s;
}

static inline til_I64 til_str_to_i64(const til_Str* s)
{
    return (til_I64)strtoll((const char*)s->c_string.data, NULL, 10);
}

// I/O functions

// input_read_line: read a line from stdin, displaying prompt first
// Bug #98: Now throws ReadError instead of silently failing
static inline int til_input_read_line(til_Str* _ret, void* _err_v, const til_Str* prompt)
{
    struct { til_Str msg; }* _err = _err_v;
    // Print the prompt if non-empty
    if (prompt->_len > 0) {
        printf("%.*s", (int)prompt->_len, (const char*)prompt->c_string.data);
        fflush(stdout);
    }
    char* buf = (char*)malloc(4096);
    if (!buf) {
        _err->msg.c_string.data = (til_I64)"Failed to allocate input buffer";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 31;
        _err->msg.cap = 0;
        return 1;  // throw ReadError
    }
    if (fgets(buf, 4096, stdin) == NULL) {
        free(buf);
        _err->msg.c_string.data = (til_I64)"Failed to read from stdin";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 25;
        _err->msg.cap = 0;
        return 1;  // throw ReadError
    }
    _ret->c_string.data = (til_I64)buf;
    _ret->c_string.is_borrowed = 0;
    _ret->_len = strlen(buf);
    _ret->cap = 4096;
    return 0;
}

// Bug #98: Now throws ReadError instead of returning empty string
static inline int til_readfile(til_Str* _ret, void* _err_v, const til_Str* path)
{
    struct { til_Str msg; }* _err = _err_v;
    FILE* f = fopen((const char*)path->c_string.data, "rb");
    if (!f) {
        _err->msg.c_string.data = (til_I64)"Could not open file for reading";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 31;
        _err->msg.cap = 0;
        return 1;  // throw ReadError
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        fclose(f);
        _err->msg.c_string.data = (til_I64)"Failed to allocate buffer for file";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 34;
        _err->msg.cap = 0;
        return 1;  // throw ReadError
    }
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    _ret->c_string.data = (til_I64)buf;
    _ret->c_string.is_borrowed = 0;
    _ret->_len = len;
    _ret->cap = len + 1;
    return 0;
}

// Bug #98: Now throws WriteError instead of panicking
static inline int til_writefile(void* _err_v, const til_Str* path, const til_Str* contents)
{
    struct { til_Str msg; }* _err = _err_v;
    FILE* f = fopen((const char*)path->c_string.data, "wb");
    if (!f) {
        _err->msg.c_string.data = (til_I64)"Could not open file for writing";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 31;
        _err->msg.cap = 0;
        return 1;  // throw WriteError
    }
    size_t written = fwrite((const char*)contents->c_string.data, 1, contents->_len, f);
    fclose(f);
    if (written != (size_t)contents->_len) {
        _err->msg.c_string.data = (til_I64)"Failed to write all data to file";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 32;
        _err->msg.cap = 0;
        return 1;  // throw WriteError
    }
    return 0;
}

// run_cmd: run command with arguments, capture output and return exit code
// Signature: run_cmd(mut output_str: Str, args: ..Str) returns I64
// First element of args array is the command, rest are arguments
static inline til_I64 til_run_cmd(til_Str* output_str, til_Array* args)
{
    #define RUN_CMD_BUF_SIZE 65536
    char* buf = (char*)malloc(RUN_CMD_BUF_SIZE);
    if (!buf) {
        output_str->c_string.data = 0;
        output_str->c_string.is_borrowed = 0;
        output_str->_len = 0;
        output_str->cap = 0;
        return -1;
    }
    buf[0] = '\0';

    if (args->_len == 0) {
        output_str->c_string.data = (til_I64)buf;
        output_str->c_string.is_borrowed = 0;
        output_str->_len = 0;
        output_str->cap = RUN_CMD_BUF_SIZE;
        return -1;
    }

    // Build command string: "cmd 'arg1' 'arg2' ..."
    // Arguments (except command) are single-quoted for shell safety
    // Single quotes within args are escaped as '\''
    char cmd_buf[8192];
    cmd_buf[0] = '\0';
    size_t cmd_len = 0;

    for (til_I64 i = 0; i < args->_len; i++) {
        til_Str* arg = (til_Str*)((char*)args->ptr + i * sizeof(til_Str));
        if (i > 0) {
            if (cmd_len < sizeof(cmd_buf) - 1) {
                cmd_buf[cmd_len++] = ' ';
            }
            // Quote arguments (not the command itself)
            if (cmd_len < sizeof(cmd_buf) - 1) {
                cmd_buf[cmd_len++] = '\'';
            }
        }
        const char* arg_str = (const char*)arg->c_string.data;
        size_t arg_len = arg->_len;
        if (i == 0) {
            // Command: no quoting needed
            if (cmd_len + arg_len < sizeof(cmd_buf) - 1) {
                memcpy(cmd_buf + cmd_len, arg_str, arg_len);
                cmd_len += arg_len;
            }
        } else {
            // Argument: escape single quotes as '\''
            for (size_t j = 0; j < arg_len && cmd_len < sizeof(cmd_buf) - 5; j++) {
                if (arg_str[j] == '\'') {
                    // End quote, escaped quote, start quote: '\''
                    cmd_buf[cmd_len++] = '\'';
                    cmd_buf[cmd_len++] = '\\';
                    cmd_buf[cmd_len++] = '\'';
                    cmd_buf[cmd_len++] = '\'';
                } else {
                    cmd_buf[cmd_len++] = arg_str[j];
                }
            }
            // Close quote
            if (cmd_len < sizeof(cmd_buf) - 1) {
                cmd_buf[cmd_len++] = '\'';
            }
        }
    }
    cmd_buf[cmd_len] = '\0';

    FILE* f = popen(cmd_buf, "r");
    if (!f) {
        output_str->c_string.data = (til_I64)buf;
        output_str->c_string.is_borrowed = 0;
        output_str->_len = 0;
        output_str->cap = RUN_CMD_BUF_SIZE;
        return -1;
    }

    size_t total = 0;
    while (total < RUN_CMD_BUF_SIZE - 1) {
        size_t n = fread(buf + total, 1, RUN_CMD_BUF_SIZE - 1 - total, f);
        if (n == 0) break;
        total += n;
    }
    buf[total] = '\0';
    // Drain any remaining output to prevent SIGPIPE killing the child process
    // This ensures we get the correct exit code even if output exceeds buffer
    char drain_buf[4096];
    while (fread(drain_buf, 1, sizeof(drain_buf), f) > 0) {}
    int status = pclose(f);
#ifdef _WIN32
    // On Windows, pclose returns the exit code directly
    int exit_code = status;
#else
    // On Unix, pclose returns a wait status that needs WIFEXITED/WEXITSTATUS
    int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif

    output_str->c_string.data = (til_I64)buf;
    output_str->c_string.is_borrowed = 0;
    output_str->_len = total;
    output_str->cap = RUN_CMD_BUF_SIZE;
    return (til_I64)exit_code;
    #undef RUN_CMD_BUF_SIZE
}

// eval_file: stub for compiled mode (repl functionality not available when compiled)
// TODO: Implement actual eval_file functionality for compiled mode if needed
// This would require reading, parsing, and evaluating TIL files at runtime,
// which would essentially embed the full interpreter into the compiled binary.
static inline void til_eval_file(const til_Str* _unused) {
    (void)_unused;  // Suppress unused parameter warning
    printf("Error: eval_file is not available in compiled mode.\n");
    printf("Use 'til repl' with the interpreted version instead.\n");
    exit(1);
}

// ---------- Process spawning functions
// Note: These functions use void* for error parameters to avoid type conflicts
// when the TIL program doesn't import std.sys. The actual error struct has the
// same layout (just a til_Str msg field), so casting is safe.

#ifdef _WIN32
#include <windows.h>
#include <direct.h>  // for _mkdir

// spawn_cmd: Spawn a command in the background, returns process handle
static inline int til_spawn_cmd(til_I64* _ret, void* _err_v, const til_Str* cmd) {
    struct { til_Str msg; }* _err = _err_v;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmdline[8192];
    snprintf(cmdline, sizeof(cmdline), "cmd.exe /c %s", (char*)cmd->c_string.data);

    if (!CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        _err->msg.c_string.data = (til_I64)"Failed to create process";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 24;
        _err->msg.cap = 0;
        return 1;  // throw
    }
    CloseHandle(pi.hThread);
    *_ret = (til_I64)pi.hProcess;  // Return handle
    return 0;
}

// check_cmd_status: Check if process has finished (non-blocking)
// Returns -1 if still running, exit code if finished
static inline til_I64 til_check_cmd_status(const til_I64* handle) {
    DWORD result = WaitForSingleObject((HANDLE)*handle, 0);
    if (result == WAIT_TIMEOUT) {
        return -1;  // still running
    }
    DWORD exitCode;
    GetExitCodeProcess((HANDLE)*handle, &exitCode);
    CloseHandle((HANDLE)*handle);
    return (til_I64)exitCode;
}

// sleep: Sleep for specified milliseconds
static inline int til_sleep(void* _err_v, const til_I64* ms) {
    (void)_err_v;  // unused - sleep doesn't throw on Windows
    Sleep((DWORD)*ms);
    return 0;
}

// get_thread_count: Returns number of logical processors (threads)
static inline til_I64 til_get_thread_count(void) {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return (til_I64)sysinfo.dwNumberOfProcessors;
}

// file_mtime: Returns file modification time as Unix timestamp, -1 if not exists
static inline til_I64 til_file_mtime(const til_Str* path) {
    HANDLE h = CreateFileA((char*)path->c_string.data, GENERIC_READ,
        FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return -1;
    FILETIME ft;
    if (!GetFileTime(h, NULL, NULL, &ft)) { CloseHandle(h); return -1; }
    CloseHandle(h);
    // Convert FILETIME to Unix timestamp
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return (til_I64)((ull.QuadPart - 116444736000000000ULL) / 10000000ULL);
}

// Bug #98: Now throws IOError instead of returning empty string
static inline int til_list_dir_raw(til_Str* _ret, void* _err_v, const til_Str* path) {
    struct { til_Str msg; }* _err = _err_v;
    char pattern[1024];
    snprintf(pattern, sizeof(pattern), "%s/*", (char*)path->c_string.data);

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        _err->msg.c_string.data = (til_I64)"Could not open directory";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 24;
        _err->msg.cap = 0;
        return 1;  // throw IOError
    }

    char buf[65536];
    size_t pos = 0;
    int first = 1;
    do {
        if (fd.cFileName[0] == '.') continue;  // skip . and ..
        size_t len = strlen(fd.cFileName);
        if (pos + len + 2 >= sizeof(buf)) break;  // buffer full
        if (!first) buf[pos++] = '\n';
        memcpy(buf + pos, fd.cFileName, len);
        pos += len;
        first = 0;
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    buf[pos] = '\0';

    // Allocate and copy result
    char* result = (char*)malloc(pos + 1);
    memcpy(result, buf, pos + 1);
    _ret->c_string.data = (til_I64)result;
    _ret->c_string.is_borrowed = 0;
    _ret->_len = pos;
    _ret->cap = pos + 1;
    return 0;
}

// fs_parent_dir: Get parent directory of a path (Windows version)
static inline til_Str til_fs_parent_dir(const til_Str* path) {
    const char* p = (const char*)path->c_string.data;
    size_t len = path->_len;

    // Find last slash or backslash
    size_t last_slash = 0;
    int found = 0;
    for (size_t i = 0; i < len; i++) {
        if (p[i] == '/' || p[i] == '\\') {
            last_slash = i;
            found = 1;
        }
    }

    if (!found || last_slash == 0) {
        return (til_Str){{0, 0, 0, 0, 0}, 0, 0};  // No parent or root
    }

    // Allocate and copy parent path
    char* result = (char*)malloc(last_slash + 1);
    memcpy(result, p, last_slash);
    result[last_slash] = '\0';
    return (til_Str){{(til_I64)result, 0, last_slash + 1, 0, 0}, last_slash, last_slash + 1};
}

// fs_mkdir_p: Create directory and all parent directories (Windows)
static inline til_I64 til_fs_mkdir_p(const til_Str* path) {
    const char* p = (const char*)path->c_string.data;
    size_t len = path->_len;
    if (len == 0) return 0;

    char* tmp = (char*)malloc(len + 1);
    memcpy(tmp, p, len);
    tmp[len] = '\0';

    for (size_t i = 1; i < len; i++) {
        if (tmp[i] == '/' || tmp[i] == '\\') {
            tmp[i] = '\0';
            _mkdir(tmp);
            tmp[i] = '/';
        }
    }
    int result = _mkdir(tmp);
    free(tmp);
    return (result == 0 || errno == EEXIST) ? 0 : -1;
}

#else  // Unix

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

// spawn_cmd: Spawn a command in the background, returns PID
static inline int til_spawn_cmd(til_I64* _ret, void* _err_v, const til_Str* cmd) {
    struct { til_Str msg; }* _err = _err_v;
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execl("/bin/sh", "sh", "-c", (char*)cmd->c_string.data, NULL);
        _exit(127);  // execl failed
    }
    if (pid < 0) {
        _err->msg.c_string.data = (til_I64)"Fork failed";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 11;
        _err->msg.cap = 0;
        return 1;  // throw
    }
    *_ret = (til_I64)pid;
    return 0;
}

// check_cmd_status: Check if process has finished (non-blocking)
// Returns -1 if still running, exit code if finished
static inline til_I64 til_check_cmd_status(const til_I64* pid) {
    int status;
    pid_t result = waitpid((pid_t)*pid, &status, WNOHANG);
    if (result == 0) {
        return -1;  // still running
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;  // abnormal termination
}

// sleep: Sleep for specified milliseconds
static inline int til_sleep(void* _err_v, const til_I64* ms) {
    (void)_err_v;  // unused - sleep doesn't throw on success
    usleep((useconds_t)(*ms * 1000));
    return 0;
}

// get_thread_count: Returns number of logical processors (threads)
static inline til_I64 til_get_thread_count(void) {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return count > 0 ? (til_I64)count : 1;
}

// file_mtime: Returns file modification time as Unix timestamp, -1 if not exists
#include <sys/stat.h>
static inline til_I64 til_file_mtime(const til_Str* path) {
    struct stat st;
    if (stat((char*)path->c_string.data, &st) != 0) return -1;
    return (til_I64)st.st_mtime;
}

// Bug #98: Now throws IOError instead of returning empty string
#include <dirent.h>
static inline int til_list_dir_raw(til_Str* _ret, void* _err_v, const til_Str* path) {
    struct { til_Str msg; }* _err = _err_v;
    DIR* d = opendir((char*)path->c_string.data);
    if (!d) {
        _err->msg.c_string.data = (til_I64)"Could not open directory";
        _err->msg.c_string.is_borrowed = 1;
        _err->msg._len = 24;
        _err->msg.cap = 0;
        return 1;  // throw IOError
    }

    char buf[65536];
    size_t pos = 0;
    int first = 1;
    struct dirent* entry;
    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] == '.') continue;  // skip . and ..
        size_t len = strlen(entry->d_name);
        if (pos + len + 2 >= sizeof(buf)) break;  // buffer full
        if (!first) buf[pos++] = '\n';
        memcpy(buf + pos, entry->d_name, len);
        pos += len;
        first = 0;
    }
    closedir(d);
    buf[pos] = '\0';

    // Allocate and copy result
    char* result = (char*)malloc(pos + 1);
    memcpy(result, buf, pos + 1);
    _ret->c_string.data = (til_I64)result;
    _ret->c_string.is_borrowed = 0;
    _ret->_len = pos;
    _ret->cap = pos + 1;
    return 0;
}

// fs_parent_dir: Get parent directory of a path
static inline til_Str til_fs_parent_dir(const til_Str* path) {
    const char* p = (const char*)path->c_string.data;
    size_t len = path->_len;

    // Find last slash
    size_t last_slash = 0;
    int found = 0;
    for (size_t i = 0; i < len; i++) {
        if (p[i] == '/') {
            last_slash = i;
            found = 1;
        }
    }

    if (!found || last_slash == 0) {
        return (til_Str){{0, 0, 0, 0, 0}, 0, 0};  // No parent or root
    }

    // Allocate and copy parent path
    char* result = (char*)malloc(last_slash + 1);
    memcpy(result, p, last_slash);
    result[last_slash] = '\0';
    return (til_Str){{(til_I64)result, 0, last_slash + 1, 0, 0}, last_slash, last_slash + 1};
}

// fs_mkdir_p: Create directory and all parent directories (Unix)
static inline til_I64 til_fs_mkdir_p(const til_Str* path) {
    const char* p = (const char*)path->c_string.data;
    size_t len = path->_len;
    if (len == 0) return 0;

    char* tmp = (char*)malloc(len + 1);
    memcpy(tmp, p, len);
    tmp[len] = '\0';

    for (size_t i = 1; i < len; i++) {
        if (tmp[i] == '/') {
            tmp[i] = '\0';
            mkdir(tmp, 0755);
            tmp[i] = '/';
        }
    }
    int result = mkdir(tmp, 0755);
    free(tmp);
    return (result == 0 || errno == EEXIST) ? 0 : -1;
}

#endif  // _WIN32

#endif /* TIL_EXT_C */
