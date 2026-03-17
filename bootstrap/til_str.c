#include "til_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1050; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1050 = *_hp; free(_hp); }
    (void)_t1050;
    I64 _t1051 = 0;
    (void)_t1051;
    Bool _t1052 = I64_eq(_t1050, _t1051);
    (void)_t1052;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1052; return _r; }
}

