#pragma once
#include "modes_decls.h"

#include "modes_vec.h"

typedef struct Tuple {
    U8 *data;
    U64 total_size;
    U64 cap;
    Vec type_names;
    Vec type_sizes;
} Tuple;


Tuple * Tuple_new(void);
U64 * Tuple_len(Tuple * self);
void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val);
void * Tuple_get(Tuple * self, U64 * i);
Str * Tuple_type_at(Tuple * self, U64 * i);
U64 * Tuple_size_at(Tuple * self, U64 * i);
void Tuple_delete(Tuple * self, Bool * call_free);
Tuple * Tuple_clone(Tuple * self);
U64 * Tuple_size(void);
