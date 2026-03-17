#pragma once
#include "til_decls.h"


typedef struct Dynamic {
    char _;
} Dynamic;







typedef struct Range {
    U64 start;
    U64 end;
} Range;



Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
void println(Array * parts);
Str * format(Array * parts);
void panic(Str * loc_str, Array * parts);
