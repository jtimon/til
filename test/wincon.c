// Issue #347: the console driver behind test/repl_wincon.til.
//
// The Windows half of the REPL line editor (src/c/ext.c's `#if
// defined(_WIN32)` repl_term_* block) had never been executed. CI's
// windows-host job runs til.exe's interpret / translate / build on a real
// runner, but none of those opens a console, and piping into
// `til.exe repl` proves nothing: repl_term_is_interactive asks
// GetConsoleMode, a pipe fails it, and the REPL takes the non-editing
// path that already worked.
//
// This is the console analogue of the pseudo-terminal test/repl_pty.til
// drives on POSIX. It allocates a REAL console, and the til driver spawns
// the REPL into it through Cmd -- Cmd's CreateProcessA passes this
// process's std handles through, and a child started without
// CREATE_NEW_CONSOLE attaches to the same console -- then posts key
// records with WriteConsoleInput and reads the drawn rows back with
// ReadConsoleOutputCharacter.
//
// It is linked with link_c() into that one test rather than added to
// src/c/ext.c: nothing but the test needs it, and the compiler runtime
// should not grow a console-injection surface.
//
// Reporting deliberately keeps using the CRT's stdout. AllocConsole
// rebinds the WIN32 std handles (which is what the child inherits) but
// not the CRT's file descriptors, so the driver's own println still
// reaches the CI log while the REPL draws into the console.

#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Str *wincon_str(const char *data, size_t len) {
    char *buf = malloc(len + 1);
    Str *s = malloc(sizeof(Str));
    if (!buf || !s) {
        fprintf(stderr, "wincon: allocation failed\n");
        exit(1);
    }
    if (len > 0) memcpy(buf, data, len);
    buf[len] = '\0';
    s->c_str = (I8 *)buf;
    s->count = (USize)len;
    s->cap = (USize)len;
    return s;
}

#if defined(_WIN32)

#include <windows.h>

static HANDLE wincon_in_h = INVALID_HANDLE_VALUE;
static HANDLE wincon_out_h = INVALID_HANDLE_VALUE;

Bool wincon_begin(void) {
    // Whatever console the job process has (usually none -- the runner
    // redirects to pipes) is not one we can drive, so start a fresh one.
    FreeConsole();
    if (!AllocConsole()) return 0;
    SECURITY_ATTRIBUTES sa;
    memset(&sa, 0, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    wincon_in_h = CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                              OPEN_EXISTING, 0, NULL);
    wincon_out_h = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                               OPEN_EXISTING, 0, NULL);
    if (wincon_in_h == INVALID_HANDLE_VALUE || wincon_out_h == INVALID_HANDLE_VALUE) return 0;
    // Opening CONIN$/CONOUT$ can SUCCEED without there being a console
    // behind them -- that is what wine does on a headless host, where
    // every later GetConsoleScreenBufferInfo then fails and the driver
    // would sit watching an empty screen until its poll budget ran out.
    // Ask the two handles whether they are really a console, so a host
    // that cannot host this test says so immediately.
    {
        DWORD probe = 0;
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleMode(wincon_in_h, &probe)) return 0;
        if (!GetConsoleScreenBufferInfo(wincon_out_h, &info)) return 0;
    }
    // The child reads these through STARTUPINFO, which Cmd fills from
    // GetStdHandle. The CRT's own fds are untouched, so this process keeps
    // reporting to the job log.
    SetStdHandle(STD_INPUT_HANDLE, wincon_in_h);
    SetStdHandle(STD_OUTPUT_HANDLE, wincon_out_h);
    SetStdHandle(STD_ERROR_HANDLE, wincon_out_h);
    return 1;
}

void wincon_end(void) {
    if (wincon_in_h != INVALID_HANDLE_VALUE) {
        CloseHandle(wincon_in_h);
        wincon_in_h = INVALID_HANDLE_VALUE;
    }
    if (wincon_out_h != INVALID_HANDLE_VALUE) {
        CloseHandle(wincon_out_h);
        wincon_out_h = INVALID_HANDLE_VALUE;
    }
    FreeConsole();
}

// One keystroke as a real keyboard delivers it: the down record the
// editor reads, then the up record it must skip. `vk` is 0 for an
// ordinary character (the editor decides by uChar) and a VK_* code for
// the arrows / Home / End / Delete it maps by key code.
void wincon_key(I64 vk, I64 ch) {
    INPUT_RECORD rec[2];
    DWORD written = 0;
    int i;
    for (i = 0; i < 2; i++) {
        memset(&rec[i], 0, sizeof(rec[i]));
        rec[i].EventType = KEY_EVENT;
        rec[i].Event.KeyEvent.bKeyDown = (BOOL)(i == 0);
        rec[i].Event.KeyEvent.wRepeatCount = 1;
        rec[i].Event.KeyEvent.wVirtualKeyCode = (WORD)vk;
        rec[i].Event.KeyEvent.wVirtualScanCode =
            (WORD)MapVirtualKeyA((UINT)vk, MAPVK_VK_TO_VSC);
        rec[i].Event.KeyEvent.uChar.AsciiChar = (CHAR)ch;
        rec[i].Event.KeyEvent.dwControlKeyState = 0;
    }
    WriteConsoleInput(wincon_in_h, rec, 2, &written);
}

// Input records that are not keys. A console delivers these whenever the
// user moves the mouse across the window, and repl_term_read_event
// filters them with `continue` -- after which it waits AGAIN with the
// full timeout, which is what the ESC follow-up window depends on.
void wincon_noise(I64 count) {
    INPUT_RECORD rec;
    DWORD written = 0;
    I64 i;
    for (i = 0; i < count; i++) {
        memset(&rec, 0, sizeof(rec));
        rec.EventType = MOUSE_EVENT;
        rec.Event.MouseEvent.dwMousePosition.X = (SHORT)(i % 8);
        rec.Event.MouseEvent.dwMousePosition.Y = 0;
        rec.Event.MouseEvent.dwEventFlags = MOUSE_MOVED;
        WriteConsoleInput(wincon_in_h, &rec, 1, &written);
    }
}

// Blank the whole buffer without moving the cursor, so a row that comes
// back afterwards was REDRAWN rather than left over.
void wincon_clear(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    COORD origin;
    DWORD filled = 0;
    if (!GetConsoleScreenBufferInfo(wincon_out_h, &info)) return;
    origin.X = 0;
    origin.Y = 0;
    FillConsoleOutputCharacterA(wincon_out_h, ' ',
                                (DWORD)info.dwSize.X * (DWORD)info.dwSize.Y,
                                origin, &filled);
}

// A buffer-size change is what raises WINDOW_BUFFER_SIZE_EVENT, the
// console's answer to SIGWINCH. Only the height changes: shrinking the
// width below the window is rejected, and the row assertions want a
// stable width anyway.
void wincon_resize(I64 rows) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    COORD size;
    if (!GetConsoleScreenBufferInfo(wincon_out_h, &info)) return;
    size.X = info.dwSize.X;
    size.Y = (SHORT)rows;
    SetConsoleScreenBufferSize(wincon_out_h, size);
}

// Ctrl-C as the console raises it, which is the only way to reach
// repl_term_ctrl_handler: an injected key record is not processed into a
// control event. The ignore flag is set HERE and not in wincon_begin
// because CreateProcess passes it to children -- the REPL was spawned
// before this runs, so it still takes the event.
void wincon_ctrl_c(void) {
    SetConsoleCtrlHandler(NULL, TRUE);
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
}

// The visible screen: every row up to the cursor's, right-trimmed and
// joined with newlines. Nothing below the cursor has been written.
Str *wincon_screen(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    char *row;
    char *out;
    size_t len = 0;
    int cols, last, y;
    if (wincon_out_h == INVALID_HANDLE_VALUE ||
        !GetConsoleScreenBufferInfo(wincon_out_h, &info)) {
        return wincon_str("", 0);
    }
    cols = info.dwSize.X;
    last = info.dwCursorPosition.Y;
    if (cols <= 0 || last < 0) return wincon_str("", 0);
    row = malloc((size_t)cols + 1);
    out = malloc(((size_t)cols + 1) * ((size_t)last + 1) + 1);
    if (!row || !out) {
        fprintf(stderr, "wincon: allocation failed\n");
        exit(1);
    }
    for (y = 0; y <= last; y++) {
        COORD at;
        DWORD got = 0;
        int end;
        at.X = 0;
        at.Y = (SHORT)y;
        if (!ReadConsoleOutputCharacterA(wincon_out_h, row, (DWORD)cols, at, &got)) got = 0;
        end = (int)got;
        while (end > 0 && (row[end - 1] == ' ' || row[end - 1] == '\0')) end--;
        if (y > 0) out[len++] = '\n';
        if (end > 0) {
            memcpy(out + len, row, (size_t)end);
            len += (size_t)end;
        }
    }
    {
        Str *s = wincon_str(out, len);
        free(row);
        free(out);
        return s;
    }
}

// The console input mode, for the before/after comparison that `stty -g`
// makes on POSIX: the REPL must hand the console back exactly as found,
// on a clean exit and on Ctrl-C alike.
I64 wincon_in_mode(void) {
    DWORD mode = 0;
    if (!GetConsoleMode(wincon_in_h, &mode)) return -1;
    return (I64)mode;
}

// Column 0 means the row the editor was drawing has been ended -- what
// repl_term_ctrl_handler's "\r\n" exists to guarantee, so whatever prints
// next does not land on top of the prompt.
I64 wincon_cursor_col(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(wincon_out_h, &info)) return -1;
    return (I64)info.dwCursorPosition.X;
}

#else

// Every other host: the driver reports SKIP before calling any of these,
// and they exist so the file still compiles and links into the suite's
// ordinary build on linux and macOS.

Bool wincon_begin(void) { return 0; }
void wincon_end(void) {}
void wincon_key(I64 vk, I64 ch) { (void)vk; (void)ch; }
void wincon_noise(I64 count) { (void)count; }
void wincon_clear(void) {}
void wincon_resize(I64 rows) { (void)rows; }
void wincon_ctrl_c(void) {}
Str *wincon_screen(void) { return wincon_str("", 0); }
I64 wincon_in_mode(void) { return -1; }
I64 wincon_cursor_col(void) { return -1; }

#endif
