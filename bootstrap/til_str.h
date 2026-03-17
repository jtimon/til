#pragma once
#include "til_decls.h"


typedef struct Str {
    U8 *c_str;
    U64 count;
    U64 cap;
} Str;


U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_rfind(Str * self, Str * needle);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
