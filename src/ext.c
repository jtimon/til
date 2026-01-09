/*
 * ext.c - TIL External C Interface
 *
 * Has to be included in the right place of the output file, after the forward declarations and struct declarations.
 */

#ifndef TIL_EXT_C
#define TIL_EXT_C

// Bool constants
#define true ((til_Bool){1})
#define false ((til_Bool){0})

// single_print: print a string without newline
static inline void til_single_print(const til_Str* s)
{
    printf("%s", (char*)s->c_string);
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
static inline til_I64 til_u8_to_i64(const til_U8* v)
{
    return (til_I64)*v;
}

static inline til_U8 til_i64_to_u8(const til_I64* v)
{
    return (til_U8)*v;
}

// Arithmetic functions
static inline til_Bool til_lt(const til_I64* a, const til_I64* b)
{
    return (til_Bool){*a < *b};
}

static inline til_Bool til_gt(const til_I64* a, const til_I64* b)
{
    return (til_Bool){*a > *b};
}

static inline til_I64 til_add(const til_I64* a, const til_I64* b)
{
    return *a + *b;
}

static inline til_I64 til_sub(const til_I64* a, const til_I64* b)
{
    return *a - *b;
}

static inline til_I64 til_mul(const til_I64* a, const til_I64* b)
{
    return *a * *b;
}

static inline til_I64 til_div(const til_I64* a, const til_I64* b)
{
    return *b == 0 ? 0 : *a / *b;
}

static inline til_I64 til_mod(const til_I64* a, const til_I64* b)
{
    return *b == 0 ? 0 : *a % *b;
}

// Memory functions
static inline int til_malloc(til_I64* _ret, til_AllocError* _err, const til_I64* size)
{
    *_ret = (til_I64)malloc((size_t)*size);
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

static inline til_I64 til_memcmp(const til_I64* a, const til_I64* b, const til_I64* n)
{
    return (til_I64)memcmp((void*)*a, (void*)*b, (size_t)*n);
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
        til_Str s = {0, 0};
        return s;
    }
    snprintf(buf, 32, "%lld", (long long)*v);
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = strlen(buf);
    return s;
}

static inline til_I64 til_str_to_i64(const til_Str* s)
{
    return (til_I64)strtoll((const char*)s->c_string, NULL, 10);
}

// I/O functions

// input_read_line: read a line from stdin, displaying prompt first
static inline til_Str til_input_read_line(const til_Str* prompt)
{
    // Print the prompt if non-empty
    if (prompt->cap > 0) {
        printf("%.*s", (int)prompt->cap, (const char*)prompt->c_string);
        fflush(stdout);
    }
    char* buf = (char*)malloc(4096);
    if (!buf) {
        til_Str s = {0, 0};
        return s;
    }
    if (fgets(buf, 4096, stdin) == NULL) {
        buf[0] = '\0';
    }
    til_Str s;
    s.c_string = (til_I64)buf;
    s.cap = strlen(buf);
    return s;
}

// readfile: read entire file contents
static inline til_Str til_readfile(const til_Str* path)
{
    FILE* f = fopen((const char*)path->c_string, "rb");
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
static inline til_I64 til_writefile(const til_Str* path, const til_Str* contents)
{
    FILE* f = fopen((const char*)path->c_string, "wb");
    if (!f) {
        return -1;
    }
    size_t written = fwrite((const char*)contents->c_string, 1, contents->cap, f);
    fclose(f);
    return (til_I64)written;
}

// run_cmd: run command with arguments, capture output and return exit code
// Signature: run_cmd(mut output_str: Str, args: ..Str) returns I64
// First element of args array is the command, rest are arguments
static inline til_I64 til_run_cmd(til_Str* output_str, til_Array* args)
{
    #define RUN_CMD_BUF_SIZE 65536
    char* buf = (char*)malloc(RUN_CMD_BUF_SIZE);
    if (!buf) {
        output_str->c_string = 0;
        output_str->cap = 0;
        return -1;
    }
    buf[0] = '\0';

    if (args->_len == 0) {
        output_str->c_string = (til_I64)buf;
        output_str->cap = 0;
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
        const char* arg_str = (const char*)arg->c_string;
        size_t arg_len = arg->cap;
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
        output_str->c_string = (til_I64)buf;
        output_str->cap = 0;
        return -1;
    }

    size_t total = 0;
    while (total < RUN_CMD_BUF_SIZE - 1) {
        size_t n = fread(buf + total, 1, RUN_CMD_BUF_SIZE - 1 - total, f);
        if (n == 0) break;
        total += n;
    }
    buf[total] = '\0';
    int status = pclose(f);
    int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    output_str->c_string = (til_I64)buf;
    output_str->cap = total;
    return (til_I64)exit_code;
    #undef RUN_CMD_BUF_SIZE
}

// eval_file: stub for compiled mode (repl functionality not available when compiled)
// TODO: Implement actual eval_file functionality for compiled mode if needed
// This would require reading, parsing, and evaluating TIL files at runtime,
// which would essentially embed the full interpreter into the compiled binary.
static inline void til_eval_file(const til_Str* path) {
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

// spawn_cmd: Spawn a command in the background, returns process handle
static inline int til_spawn_cmd(til_I64* _ret, void* _err_v, const til_Str* cmd) {
    struct { til_Str msg; }* _err = _err_v;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmdline[8192];
    snprintf(cmdline, sizeof(cmdline), "cmd.exe /c %s", (char*)cmd->c_string);

    if (!CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        _err->msg.c_string = (til_I64)"Failed to create process";
        _err->msg.cap = 24;
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
    HANDLE h = CreateFileA((char*)path->c_string, GENERIC_READ,
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

// list_dir_raw: List files in a directory, returns newline-separated Str
static inline til_Str til_list_dir_raw(const til_Str* path) {
    char pattern[1024];
    snprintf(pattern, sizeof(pattern), "%s/*", (char*)path->c_string);

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) return (til_Str){0, 0};

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
    return (til_Str){(til_I64)result, pos};
}

// fs_parent_dir: Get parent directory of a path (Windows version)
static inline til_Str til_fs_parent_dir(const til_Str* path) {
    const char* p = (const char*)path->c_string;
    size_t len = path->cap;

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
        return (til_Str){0, 0};  // No parent or root
    }

    // Allocate and copy parent path
    char* result = (char*)malloc(last_slash + 1);
    memcpy(result, p, last_slash);
    result[last_slash] = '\0';
    return (til_Str){(til_I64)result, last_slash};
}

#else  // Unix

#include <unistd.h>
#include <sys/wait.h>

// spawn_cmd: Spawn a command in the background, returns PID
static inline int til_spawn_cmd(til_I64* _ret, void* _err_v, const til_Str* cmd) {
    struct { til_Str msg; }* _err = _err_v;
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execl("/bin/sh", "sh", "-c", (char*)cmd->c_string, NULL);
        _exit(127);  // execl failed
    }
    if (pid < 0) {
        _err->msg.c_string = (til_I64)"Fork failed";
        _err->msg.cap = 11;
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
    if (stat((char*)path->c_string, &st) != 0) return -1;
    return (til_I64)st.st_mtime;
}

// list_dir_raw: List files in a directory, returns newline-separated Str
#include <dirent.h>
static inline til_Str til_list_dir_raw(const til_Str* path) {
    DIR* d = opendir((char*)path->c_string);
    if (!d) return (til_Str){0, 0};

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
    return (til_Str){(til_I64)result, pos};
}

// fs_parent_dir: Get parent directory of a path
static inline til_Str til_fs_parent_dir(const til_Str* path) {
    const char* p = (const char*)path->c_string;
    size_t len = path->cap;

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
        return (til_Str){0, 0};  // No parent or root
    }

    // Allocate and copy parent path
    char* result = (char*)malloc(last_slash + 1);
    memcpy(result, p, last_slash);
    result[last_slash] = '\0';
    return (til_Str){(til_I64)result, last_slash};
}

#endif  // _WIN32

#endif /* TIL_EXT_C */
