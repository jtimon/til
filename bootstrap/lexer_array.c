#include "lexer_array.h"

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

