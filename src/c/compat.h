#ifndef COMPAT_H
#define COMPAT_H

#include "ext.h"
#include "../bootstrap/core.h"
#include <limits.h>

#define CAP_LIT  ULLONG_MAX
#define CAP_VIEW (ULLONG_MAX - 1)

// Compiler-only Str helpers (not in core.til)
Str Str_val(const char *data);
Str *Str_new(const char *data);
Str *Str_new_len(const char *data, U64 len);
Bool Str_eq_c(Str *a, const char *b);

// Compiler-only Vec helpers (not in core.til)
void *Vec_last(Vec *v);
void *Vec_take(Vec *v);

// Compat wrappers: allocate before calling core.c functions
// (core.c frees the val pointer after memcpy)
Vec cvec_new(U64 elem_size);
void cvec_push(Vec *v, const void *elem);
Map cmap_new(U64 key_size, U64 val_size);
void cmap_set(Map *m, Str *key, const void *val);
Set cset_new(U64 elem_size);
void cset_add(Set *s, Str *elem);

#endif
