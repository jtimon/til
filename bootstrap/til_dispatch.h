#pragma once
#include "til_decls.h"


typedef struct ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} ExtStr;


ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U64 * ExtStr_size(void);
