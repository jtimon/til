#include "lexer_str.h"

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

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1053 = 0;
    (void)_t1053;
    I64 _t1054 = 1;
    (void)_t1054;
    I64 _t1055; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1055 = *_hp; free(_hp); }
    (void)_t1055;
    I64 _t1056 = I64_sub(_t1053, _t1054);
    (void)_t1056;
    ;
    ;
    Bool _t1057 = I64_eq(_t1055, _t1056);
    (void)_t1057;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1057; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1058; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1058 = *_hp; free(_hp); }
    (void)_t1058;
    I64 _t1059 = 1;
    (void)_t1059;
    Bool _t1060 = I64_eq(_t1058, _t1059);
    (void)_t1060;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1060; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1061; { Bool *_hp = (Bool *)Str_eq(a, b); _t1061 = *_hp; free(_hp); }
    (void)_t1061;
    Bool _t1062 = Bool_not(_t1061);
    (void)_t1062;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1063; { Bool *_hp = (Bool *)Str_gt(a, b); _t1063 = *_hp; free(_hp); }
    (void)_t1063;
    Bool _t1064 = Bool_not(_t1063);
    (void)_t1064;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1065; { Bool *_hp = (Bool *)Str_lt(a, b); _t1065 = *_hp; free(_hp); }
    (void)_t1065;
    Bool _t1066 = Bool_not(_t1065);
    (void)_t1066;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
}

