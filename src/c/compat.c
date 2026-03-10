#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

// --- Compiler-only Str helpers ---

Str Str_val(const char *data) {
    U64 len = (U64)strlen(data);
    char *copy = malloc(len + 1);
    memcpy(copy, data, len + 1);
    return (Str){.c_str = (U8 *)copy, .count = len, .cap = len};
}

Str *Str_new(const char *data) {
    U64 len = (U64)strlen(data);
    return Str_new_len(data, len);
}

Str *Str_new_len(const char *data, U64 len) {
    Str *s = malloc(sizeof(Str));
    s->c_str = malloc(len + 1);
    memcpy(s->c_str, data, len);
    s->c_str[len] = '\0';
    s->count = len;
    s->cap = len;
    return s;
}

Bool Str_eq_c(Str *a, const char *b) {
    U64 blen = (U64)strlen(b);
    if (a->count != blen) return 0;
    return memcmp(a->c_str, b, blen) == 0;
}

// --- Compiler-only Vec helpers ---

void *Vec_last(Vec *v) {
    return (char *)v->data + (v->count - 1) * v->elem_size;
}

void *Vec_take(Vec *v) {
    void *ptr = v->data;
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
    return ptr;
}

// --- Compat wrappers ---

Vec cvec_new(U64 elem_size) {
    Str empty = {.c_str = (U8 *)"", .count = 0, .cap = CAP_LIT};
    Vec *vp = Vec_new(&empty, &elem_size);
    Vec v = *vp;
    free(vp);
    return v;
}

void cvec_push(Vec *v, const void *elem) {
    void *copy = malloc(v->elem_size);
    memcpy(copy, elem, v->elem_size);
    Vec_push(v, copy);
}

Map cmap_new(U64 key_size, U64 val_size) {
    Str str_type = {.c_str = (U8 *)"Str", .count = 3, .cap = CAP_LIT};
    Str empty = {.c_str = (U8 *)"", .count = 0, .cap = CAP_LIT};
    Map *mp = Map_new(&str_type, &key_size, &empty, &val_size);
    Map m = *mp;
    free(mp);
    return m;
}

void cmap_set(Map *m, Str *key, const void *val) {
    // Store key as a CAP_VIEW Str (borrowed, won't free c_str on delete)
    Str *kcopy = malloc(sizeof(Str));
    kcopy->c_str = key->c_str;
    kcopy->count = key->count;
    kcopy->cap = CAP_VIEW;
    void *vcopy = malloc(m->val_size);
    memcpy(vcopy, val, m->val_size);
    Map_set(m, kcopy, vcopy);
}

Set cset_new(U64 elem_size) {
    Str str_type = {.c_str = (U8 *)"Str", .count = 3, .cap = CAP_LIT};
    Set *sp = Set_new(&str_type, &elem_size);
    Set s = *sp;
    free(sp);
    return s;
}

void cset_add(Set *s, Str *elem) {
    // Store elem as a CAP_VIEW Str (borrowed)
    Str *copy = malloc(sizeof(Str));
    copy->c_str = elem->c_str;
    copy->count = elem->count;
    copy->cap = CAP_VIEW;
    Set_add(s, copy);
}

// --- Externs needed by core.c ---

void *ptr_add(void *buf, U64 offset) {
    return (char *)buf + offset;
}

// System primitives

static I64 *new_i64(I64 v) { I64 *r = malloc(sizeof(I64)); *r = v; return r; }

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

I64 *check_cmd_status(I64 pid) {
    I32 status;
    pid_t result = waitpid((pid_t)pid, &status, WNOHANG);
    if (result == 0) return new_i64(-1);
    if (WIFEXITED(status)) return new_i64(WEXITSTATUS(status));
    return new_i64(-1);
}

void sleep_ms(I64 ms) {
    usleep((useconds_t)(ms * 1000));
}

I64 *file_mtime(Str *path) {
    char *p = strndup((char *)path->c_str, path->count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) return new_i64(-1);
    return new_i64((I64)st.st_mtime);
}

I64 *clock_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return new_i64((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
}

I64 *get_thread_count(void) {
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    return new_i64(count > 0 ? (I64)count : 1);
}
