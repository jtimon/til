#pragma once
#include "ast_decls.h"

#include "ast_str.h"

typedef struct Vec {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Vec;


Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
