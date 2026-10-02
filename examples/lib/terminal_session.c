// Example-local PTY/ConPTY ownership. No terminal-host API in til's runtime.
#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE 1
#include "ext.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#if defined(_WIN32)
#include <windows.h>
#else
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
// link_c force-includes the generated forward header before this source,
// so libc feature selection may already have happened. These are the
// standard UNIX98 declarations, not wrappers or a compiler flag change.
extern int posix_openpt(int);
extern int grantpt(int);
extern int unlockpt(int);
extern char *ptsname(int);
extern char **environ;
#endif

#define TERMINAL_CHUNK 65536
typedef struct TerminalNative {
    char **argv;
    size_t argc;
    char *input;
    size_t input_len;
    int started, exited, eof, closed;
    I64 status;
    char error[512];
#if defined(_WIN32)
    HANDLE console, process, input_pipe, output_pipe;
    HANDLE reader, writer, waiter;
    CRITICAL_SECTION lock;
    CONDITION_VARIABLE changed;
    int stopping;
    char output[TERMINAL_CHUNK];
    size_t output_len;
    HRESULT (WINAPI *create_console)(COORD, HANDLE, HANDLE, DWORD, HANDLE *);
    HRESULT (WINAPI *resize_console)(HANDLE, COORD);
    void (WINAPI *close_console)(HANDLE);
#else
    int master;
    pid_t child;
#endif
} TerminalNative;

static void terminal_lock(TerminalNative *s) {
#if defined(_WIN32)
    EnterCriticalSection(&s->lock);
#else
    (void)s;
#endif
}
static void terminal_unlock(TerminalNative *s) {
#if defined(_WIN32)
    LeaveCriticalSection(&s->lock);
#else
    (void)s;
#endif
}
static void terminal_error(TerminalNative *s, const char *operation, unsigned long code) {
    terminal_lock(s);
    if (!s->error[0]) {
#if defined(_WIN32)
        char message[256] = {0};
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, (DWORD)code, 0, message, sizeof(message), NULL);
        snprintf(s->error, sizeof(s->error), "%s: Windows error %lu: %s", operation, code, message);
#else
        snprintf(s->error, sizeof(s->error), "%s: %s (%lu)", operation, strerror((int)code), code);
#endif
    }
    terminal_unlock(s);
}
static void *terminal_alloc(size_t size) {
    void *p = calloc(1, size);
    if (!p) { fprintf(stderr, "tilminal: allocation failed\n"); exit(1); }
    return p;
}
static Str *terminal_str(const char *data, size_t len) {
    Str *s = terminal_alloc(sizeof(*s));
    s->c_str = terminal_alloc(len + 1);
    memcpy(s->c_str, data, len);
    s->count = (USize)len;
    s->cap = (USize)len;
    return s;
}
void *terminal_session_new(void) {
    TerminalNative *s = terminal_alloc(sizeof(*s));
#if defined(_WIN32)
    InitializeCriticalSection(&s->lock);
    InitializeConditionVariable(&s->changed);
#else
    s->master = -1;
    s->child = -1;
#endif
    return s;
}
void terminal_session_arg(const void *handle, const Str *arg) {
    TerminalNative *s = (TerminalNative *)handle;
    if (s->started || s->closed || memchr(arg->c_str, 0, arg->count)) {
        terminal_error(s, "invalid terminal argv/state", EINVAL); return;
    }
    char **args = realloc(s->argv, (s->argc + 2) * sizeof(*args));
    if (!args) { terminal_error(s, "allocate argv", ENOMEM); return; }
    s->argv = args;
    char *copy = terminal_alloc((size_t)arg->count + 1);
    memcpy(copy, arg->c_str, arg->count);
    s->argv[s->argc++] = copy;
    s->argv[s->argc] = NULL;
}

#if defined(_WIN32)
static DWORD WINAPI terminal_reader(void *ptr) {
    TerminalNative *s = ptr;
    char bytes[4096];
    DWORD count, err = ERROR_SUCCESS;
    for (;;) {
        if (!ReadFile(s->output_pipe, bytes, sizeof(bytes), &count, NULL)) { err = GetLastError(); break; }
        if (!count) break;
        terminal_lock(s);
        while (!s->stopping && s->output_len + count > sizeof(s->output))
            SleepConditionVariableCS(&s->changed, &s->lock, INFINITE);
        // During explicit host close the reader must keep draining ConPTY,
        // even though there is no longer a view consuming the final frame.
        if (!s->stopping) {
            memcpy(s->output + s->output_len, bytes, count);
            s->output_len += count;
        }
        terminal_unlock(s);
    }
    terminal_lock(s);
    if (err != ERROR_BROKEN_PIPE && err != ERROR_OPERATION_ABORTED && err != ERROR_SUCCESS && !s->stopping)
        terminal_error(s, "read ConPTY", err);
    s->eof = 1;
    WakeAllConditionVariable(&s->changed);
    terminal_unlock(s);
    return 0;
}
static DWORD WINAPI terminal_writer(void *ptr) {
    TerminalNative *s = ptr;
    for (;;) {
        char bytes[4096];
        terminal_lock(s);
        while (!s->stopping && !s->input_len && !s->exited)
            SleepConditionVariableCS(&s->changed, &s->lock, INFINITE);
        if (s->stopping || s->exited) { terminal_unlock(s); break; }
        size_t count = s->input_len;
        if (count > sizeof(bytes)) count = sizeof(bytes);
        memcpy(bytes, s->input, count);
        memmove(s->input, s->input + count, s->input_len - count);
        s->input_len -= count;
        terminal_unlock(s);
        size_t offset = 0;
        while (offset < count) {
            DWORD written = 0;
            if (!WriteFile(s->input_pipe, bytes + offset, (DWORD)(count - offset), &written, NULL)) {
                DWORD err = GetLastError();
                terminal_lock(s);
                if (!s->stopping && !s->exited && err != ERROR_BROKEN_PIPE)
                    terminal_error(s, "write ConPTY", err);
                terminal_unlock(s);
                return 0;
            }
            if (!written) { terminal_error(s, "zero-length ConPTY write", ERROR_WRITE_FAULT); return 0; }
            offset += written;
        }
    }
    return 0;
}
static DWORD WINAPI terminal_waiter(void *ptr) {
    TerminalNative *s = ptr;
    WaitForSingleObject(s->process, INFINITE);
    DWORD code = 0;
    if (!GetExitCodeProcess(s->process, &code)) terminal_error(s, "GetExitCodeProcess", GetLastError());
    terminal_lock(s);
    s->status = (I64)code;
    s->exited = 1;
    WakeAllConditionVariable(&s->changed);
    terminal_unlock(s);
    // ClosePseudoConsole may block while emitting its final frame. The UI
    // continues to pump the bounded reader queue while this worker closes.
    s->close_console(s->console);
    return 0;
}
static wchar_t *terminal_command(TerminalNative *s) {
    // Windows CRT argv quoting: double backslashes before quotes and the
    // closing quote. CreateProcessW receives a mutable UTF-16 command line.
    size_t cap = 32;
    for (size_t i = 0; i < s->argc; ++i) cap += strlen(s->argv[i]) * 2 + 4;
    char *line = terminal_alloc(cap);
    size_t n = 0;
    const char *program = s->argv[0];
    for (const char *p = s->argv[0]; *p; ++p) if (*p == '/' || *p == '\\') program = p + 1;
    int shell_command = s->argc == 3 && !_stricmp(program, "cmd.exe") && !_stricmp(s->argv[1], "/C");
    for (size_t i = 0; i < s->argc; ++i) {
        // cmd /C parses shell text, not CRT argv escaping. /S gives the
        // outer pair of quotes a defined meaning, preserving inner quotes.
        if (shell_command && i == 1) {
            n += (size_t)sprintf(line + n, " /S /C \"%s\"", s->argv[2]);
            break;
        }
        if (i) line[n++] = ' ';
        line[n++] = '"';
        size_t slashes = 0;
        for (const char *p = s->argv[i]; ; ++p) {
            if (*p == '\\') { ++slashes; continue; }
            size_t copies = slashes;
            if (*p == '"' || !*p) copies *= 2;
            while (copies--) line[n++] = '\\';
            slashes = 0;
            if (!*p) break;
            if (*p == '"') line[n++] = '\\';
            line[n++] = *p;
        }
        line[n++] = '"';
    }
    int count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, line, -1, NULL, 0);
    if (!count) { terminal_error(s, "UTF-8 command line", GetLastError()); free(line); return NULL; }
    wchar_t *wide = terminal_alloc((size_t)count * sizeof(*wide));
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, line, -1, wide, count);
    free(line);
    return wide;
}
#endif

void terminal_session_start(const void *handle, I64 columns, I64 rows) {
    TerminalNative *s = (TerminalNative *)handle;
    if (s->started || s->closed || !s->argc || columns < 1 || rows < 1 || columns > 32767 || rows > 32767) {
        terminal_error(s, "invalid terminal start", EINVAL); return;
    }
#if defined(_WIN32)
    HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
    s->create_console = (HRESULT (WINAPI *)(COORD,HANDLE,HANDLE,DWORD,HANDLE *))(void *)GetProcAddress(kernel, "CreatePseudoConsole");
    s->resize_console = (HRESULT (WINAPI *)(HANDLE,COORD))(void *)GetProcAddress(kernel, "ResizePseudoConsole");
    s->close_console = (void (WINAPI *)(HANDLE))(void *)GetProcAddress(kernel, "ClosePseudoConsole");
    if (!s->create_console || !s->resize_console || !s->close_console) {
        terminal_error(s, "ConPTY requires Windows 10 1809 or later", ERROR_NOT_SUPPORTED); return;
    }
    HANDLE input_read = NULL, output_write = NULL;
    if (!CreatePipe(&input_read, &s->input_pipe, NULL, 0) || !CreatePipe(&s->output_pipe, &output_write, NULL, 0)) {
        terminal_error(s, "CreatePipe", GetLastError());
        if (input_read) CloseHandle(input_read);
        if (output_write) CloseHandle(output_write);
        return;
    }
    COORD size = {(SHORT)columns, (SHORT)rows};
    HRESULT hr = s->create_console(size, input_read, output_write, 0, &s->console);
    if (FAILED(hr)) { terminal_error(s, "CreatePseudoConsole", (DWORD)hr); CloseHandle(input_read); CloseHandle(output_write); return; }
    SIZE_T bytes = 0;
    InitializeProcThreadAttributeList(NULL, 1, 0, &bytes);
    STARTUPINFOEXW si;
    memset(&si, 0, sizeof(si));
    si.StartupInfo.cb = sizeof(si);
    si.lpAttributeList = terminal_alloc(bytes);
    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));
    wchar_t *command = terminal_command(s);
    int initialized = InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &bytes);
    if (!initialized || !UpdateProcThreadAttribute(si.lpAttributeList, 0, 0x00020016,
            s->console, sizeof(s->console), NULL, NULL) || !command ||
        !CreateProcessW(NULL, command, NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT,
                        NULL, NULL, &si.StartupInfo, &pi)) {
        terminal_error(s, "CreateProcessW/ConPTY attributes", GetLastError());
    } else {
        s->process = pi.hProcess;
        CloseHandle(pi.hThread);
        s->started = 1;
    }
    free(command);
    if (initialized) DeleteProcThreadAttributeList(si.lpAttributeList);
    free(si.lpAttributeList);
    CloseHandle(input_read);
    CloseHandle(output_write);
    if (!s->started) return;
    s->reader = CreateThread(NULL, 0, terminal_reader, s, 0, NULL);
    s->writer = CreateThread(NULL, 0, terminal_writer, s, 0, NULL);
    s->waiter = CreateThread(NULL, 0, terminal_waiter, s, 0, NULL);
    if (!s->reader || !s->writer || !s->waiter) terminal_error(s, "CreateThread", GetLastError());
#else
    s->master = posix_openpt(O_RDWR | O_NOCTTY | O_CLOEXEC);
    if (s->master < 0) { terminal_error(s, "posix_openpt", errno); return; }
    if (grantpt(s->master) || unlockpt(s->master)) { terminal_error(s, "grantpt/unlockpt", errno); return; }
    const char *slave = ptsname(s->master);
    if (!slave) { terminal_error(s, "ptsname", errno); return; }
    char *slave_name = strdup(slave);
    if (!slave_name) { terminal_error(s, "allocate slave name", ENOMEM); return; }
    struct winsize size = {0};
    size.ws_col = (unsigned short)columns; size.ws_row = (unsigned short)rows;
    if (ioctl(s->master, TIOCSWINSZ, &size)) { terminal_error(s, "TIOCSWINSZ", errno); free(slave_name); return; }
    int errors[2];
    if (pipe(errors)) { terminal_error(s, "exec error pipe", errno); free(slave_name); return; }
    if (fcntl(errors[0], F_SETFD, FD_CLOEXEC) || fcntl(errors[1], F_SETFD, FD_CLOEXEC)) {
        terminal_error(s, "exec pipe CLOEXEC", errno); close(errors[0]); close(errors[1]); free(slave_name); return;
    }
    size_t env_count = 0;
    while (environ[env_count]) ++env_count;
    char **child_env = terminal_alloc((env_count + 2) * sizeof(*child_env));
    size_t env_used = 0;
    for (size_t i = 0; i < env_count; ++i)
        if (strncmp(environ[i], "TERM=", 5)) child_env[env_used++] = environ[i];
    child_env[env_used] = "TERM=vt100";
    s->child = fork();
    if (s->child == 0) {
        close(errors[0]);
        int err = 0;
        if (setsid() < 0) goto child_error;
        int fd = open(slave_name, O_RDWR);
        if (fd < 0) goto child_error;
        if (ioctl(fd, TIOCSCTTY, 0) < 0) goto child_error;
        struct termios settings;
        if (tcgetattr(fd, &settings)) goto child_error;
        settings.c_cc[VERASE] = 8; // vt100's kbs is ^H, also on the wire.
        if (tcsetattr(fd, TCSANOW, &settings)) goto child_error;
        for (int i = 0; i < 3; ++i) if (dup2(fd, i) < 0) goto child_error;
        if (fd > 2) close(fd);
        close(s->master);
        signal(SIGINT, SIG_DFL); signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL); signal(SIGTTIN, SIG_DFL); signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL); signal(SIGPIPE, SIG_DFL); signal(SIGHUP, SIG_DFL);
        sigset_t empty_mask;
        sigemptyset(&empty_mask);
        if (sigprocmask(SIG_SETMASK, &empty_mask, NULL)) goto child_error;
        // Prepared before fork: no setenv allocation in the child of a
        // potentially multi-threaded OpenGL host.
        environ = child_env;
        execvp(s->argv[0], s->argv);
child_error:
        err = errno;
        (void)write(errors[1], &err, sizeof(err));
        _exit(127);
    }
    free(slave_name);
    free(child_env);
    close(errors[1]);
    if (s->child < 0) { terminal_error(s, "fork", errno); close(errors[0]); return; }
    s->started = 1;
    int child_errno = 0;
    ssize_t got;
    do { got = read(errors[0], &child_errno, sizeof(child_errno)); } while (got < 0 && errno == EINTR);
    close(errors[0]);
    if (got > 0) { terminal_error(s, "child terminal setup/execvp", (unsigned long)child_errno); return; }
    if (got < 0) { terminal_error(s, "read exec status", errno); return; }
    int flags = fcntl(s->master, F_GETFL);
    if (flags < 0 || fcntl(s->master, F_SETFL, flags | O_NONBLOCK)) terminal_error(s, "nonblocking PTY", errno);
#endif
}

Bool terminal_session_send(const void *handle, const Str *bytes) {
    TerminalNative *s = (TerminalNative *)handle;
    terminal_lock(s);
    if (!s->started || s->closed) {
        terminal_error(s, "send to inactive terminal", EINVAL); terminal_unlock(s); return false;
    }
    // Child exit can race a GUI key event; report that the session no
    // longer accepts input instead of turning a normal exit into an error.
    if (s->exited || s->eof) { terminal_unlock(s); return false; }
    size_t size = s->input_len + bytes->count;
    if (size < s->input_len) { terminal_error(s, "terminal input overflow", EOVERFLOW); terminal_unlock(s); return false; }
    if (bytes->count) {
        char *buf = realloc(s->input, size);
        if (!buf) { terminal_error(s, "allocate terminal input", ENOMEM); terminal_unlock(s); return false; }
        s->input = buf;
        memcpy(buf + s->input_len, bytes->c_str, bytes->count);
        s->input_len = size;
    }
#if defined(_WIN32)
    WakeAllConditionVariable(&s->changed);
#endif
    terminal_unlock(s);
    return true;
}

Str *terminal_session_pump(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
#if defined(_WIN32)
    terminal_lock(s);
    Str *out = terminal_str(s->output, s->output_len);
    s->output_len = 0;
    WakeAllConditionVariable(&s->changed);
    terminal_unlock(s);
    return out;
#else
    if (!s->started || s->closed) { terminal_error(s, "pump inactive terminal", EINVAL); return terminal_str("", 0); }
    if (s->input_len && !s->eof && !s->exited) {
        size_t count = s->input_len < TERMINAL_CHUNK ? s->input_len : TERMINAL_CHUNK;
        ssize_t n = write(s->master, s->input, count);
        if (n > 0) { memmove(s->input, s->input + n, s->input_len - (size_t)n); s->input_len -= (size_t)n; }
        else if (n < 0 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK && errno != EIO)
            terminal_error(s, "write PTY", errno);
    }
    char buffer[TERMINAL_CHUNK];
    size_t count = 0;
    while (!s->eof && count < sizeof(buffer)) {
        ssize_t n = read(s->master, buffer + count, sizeof(buffer) - count);
        if (n > 0) count += (size_t)n;
        else if (!n || (n < 0 && errno == EIO)) s->eof = 1; // Linux PTY hangup.
        else if (errno == EAGAIN || errno == EWOULDBLOCK) break;
        else if (errno != EINTR) { terminal_error(s, "read PTY", errno); break; }
    }
    if (!s->exited) {
        int status;
        pid_t p = waitpid(s->child, &status, WNOHANG);
        if (p == s->child) {
            s->exited = 1;
            s->status = WIFEXITED(status) ? WEXITSTATUS(status) : -WTERMSIG(status);
        } else if (p < 0 && errno != EINTR) terminal_error(s, "waitpid", errno);
    }
    return terminal_str(buffer, count);
#endif
}
I64 terminal_session_state(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
    terminal_lock(s);
    I64 state = 0;
    if (s->closed) state = 4;
    else if (s->started) {
        state = s->exited ? 2 : 1;
        if (s->exited && s->eof) state = 3;
#if defined(_WIN32)
        if (s->output_len && state == 3) state = 2;
#endif
    }
    terminal_unlock(s);
    return state;
}
I64 terminal_session_status(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
    terminal_lock(s);
    if (!s->exited) terminal_error(s, "status before child exit", EINVAL);
    I64 result = s->status;
    terminal_unlock(s);
    return result;
}
Str *terminal_session_error(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
    terminal_lock(s);
    Str *result = terminal_str(s->error, strlen(s->error));
    terminal_unlock(s);
    return result;
}
void terminal_session_resize(const void *handle, I64 columns, I64 rows) {
    TerminalNative *s = (TerminalNative *)handle;
    if (!s->started || s->closed || columns < 1 || rows < 1 || columns > 32767 || rows > 32767) {
        terminal_error(s, "invalid terminal resize", EINVAL); return;
    }
#if defined(_WIN32)
    terminal_lock(s);
    // The waiter closes the pseudoconsole only after setting exited.
    if (!s->exited) {
        COORD size = {(SHORT)columns, (SHORT)rows};
        HRESULT hr = s->resize_console(s->console, size);
        if (FAILED(hr)) terminal_error(s, "ResizePseudoConsole", (DWORD)hr);
    }
    terminal_unlock(s);
#else
    struct winsize size = {0};
    size.ws_col = (unsigned short)columns; size.ws_row = (unsigned short)rows;
    if (ioctl(s->master, TIOCSWINSZ, &size)) terminal_error(s, "TIOCSWINSZ", errno);
#endif
}
void terminal_session_close(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
    if (s->closed) return; // Explicit close followed by destructor is expected.
#if defined(_WIN32)
    terminal_lock(s);
    s->stopping = 1;
    WakeAllConditionVariable(&s->changed);
    terminal_unlock(s);
    if (s->process && WaitForSingleObject(s->process, 0) == WAIT_TIMEOUT)
        TerminateProcess(s->process, 1);
    if (s->writer) CancelSynchronousIo(s->writer);
    if (s->waiter) WaitForSingleObject(s->waiter, INFINITE);
    else if (s->console) s->close_console(s->console);
    if (s->reader) WaitForSingleObject(s->reader, INFINITE);
    if (s->writer) WaitForSingleObject(s->writer, INFINITE);
    if (s->reader) CloseHandle(s->reader);
    if (s->writer) CloseHandle(s->writer);
    if (s->waiter) CloseHandle(s->waiter);
    if (s->process) CloseHandle(s->process);
    if (s->input_pipe) CloseHandle(s->input_pipe);
    if (s->output_pipe) CloseHandle(s->output_pipe);
#else
    if (s->master >= 0) { close(s->master); s->master = -1; }
    if (s->started && !s->exited) {
        kill(-s->child, SIGHUP);
        int status = 0;
        pid_t result = 0;
        for (int i = 0; i < 100 && !result; ++i) {
            result = waitpid(s->child, &status, WNOHANG);
            if (result < 0 && errno == EINTR) result = 0;
            if (!result) { struct timespec delay = {0, 5000000}; nanosleep(&delay, NULL); }
        }
        if (!result) {
            kill(-s->child, SIGKILL);
            do { result = waitpid(s->child, &status, 0); } while (result < 0 && errno == EINTR);
        }
        if (result < 0) terminal_error(s, "reap terminal child", errno);
        else { s->exited = 1; s->status = WIFEXITED(status) ? WEXITSTATUS(status) : -WTERMSIG(status); }
    }
#endif
    s->closed = 1;
}
void terminal_session_free(const void *handle) {
    TerminalNative *s = (TerminalNative *)handle;
    terminal_session_close(s);
    for (size_t i = 0; i < s->argc; ++i) free(s->argv[i]);
    free(s->argv);
    free(s->input);
#if defined(_WIN32)
    DeleteCriticalSection(&s->lock);
#endif
    free(s);
}
