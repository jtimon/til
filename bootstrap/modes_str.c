#include "modes_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t997; { I64 *_hp = (I64 *)Str_cmp(a, b); _t997 = *_hp; free(_hp); }
    (void)_t997;
    I64 _t998 = 0;
    (void)_t998;
    Bool _t999 = I64_eq(_t997, _t998);
    (void)_t999;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t999; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1000 = 0;
    (void)_t1000;
    I64 _t1001 = 1;
    (void)_t1001;
    I64 _t1002; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1002 = *_hp; free(_hp); }
    (void)_t1002;
    I64 _t1003 = I64_sub(_t1000, _t1001);
    (void)_t1003;
    ;
    ;
    Bool _t1004 = I64_eq(_t1002, _t1003);
    (void)_t1004;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1004; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1005; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1005 = *_hp; free(_hp); }
    (void)_t1005;
    I64 _t1006 = 1;
    (void)_t1006;
    Bool _t1007 = I64_eq(_t1005, _t1006);
    (void)_t1007;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1007; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1008; { Bool *_hp = (Bool *)Str_eq(a, b); _t1008 = *_hp; free(_hp); }
    (void)_t1008;
    Bool _t1009 = Bool_not(_t1008);
    (void)_t1009;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1009; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1010; { Bool *_hp = (Bool *)Str_gt(a, b); _t1010 = *_hp; free(_hp); }
    (void)_t1010;
    Bool _t1011 = Bool_not(_t1010);
    (void)_t1011;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1011; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1012; { Bool *_hp = (Bool *)Str_lt(a, b); _t1012 = *_hp; free(_hp); }
    (void)_t1012;
    Bool _t1013 = Bool_not(_t1012);
    (void)_t1013;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1013; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1024; { U64 *_hp = (U64 *)Vec_len(parts); _t1024 = *_hp; free(_hp); }
    (void)_t1024;
    U64 _t1025 = 0;
    (void)_t1025;
    Bool _t1026 = U64_eq(_t1024, _t1025);
    (void)_t1026;
    ;
    ;
    if (_t1026) {
        Str *_t1014 = Str_lit("", 0ULL);
        (void)_t1014;
        ;
        return _t1014;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _t1022 = 0;
        (void)_t1022;
        U64 _t1023; { U64 *_hp = (U64 *)Vec_len(parts); _t1023 = *_hp; free(_hp); }
        (void)_t1023;
        Range *_fc1015 = Range_new(_t1022, _t1023);
        (void)_fc1015;
        ;
        ;
        U64 _fi1015 = 0;
        (void)_fi1015;
        while (1) {
            U64 _t1017; { U64 *_hp = (U64 *)Range_len(_fc1015); _t1017 = *_hp; free(_hp); }
            (void)_t1017;
            Bool _wcond1016; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1015}, &(U64){_t1017}); _wcond1016 = *_hp; free(_hp); }
            (void)_wcond1016;
            ;
            if (_wcond1016) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1015, _fi1015);
            (void)i;
            U64 _t1018 = 1;
            (void)_t1018;
            U64 _t1019 = U64_add(_fi1015, _t1018);
            (void)_t1019;
            ;
            _fi1015 = _t1019;
            ;
            U64 _t1020 = 0;
            (void)_t1020;
            Bool _t1021; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1020}); _t1021 = *_hp; free(_hp); }
            (void)_t1021;
            ;
            if (_t1021) {
                result = Str_concat(result, sep);
            }
            ;
            Str *p = Vec_get(parts, i);
            (void)p;
            result = Str_concat(result, p);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc1015, &(Bool){1});
        ;
    }
    return result;
}

