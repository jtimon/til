#pragma once
#include "ast_decls.h"

#include "ast_str.h"

typedef struct Array {
    U8 *data;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Array;


Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
