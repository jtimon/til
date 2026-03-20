#include "modes_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1014; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1014 = *_hp; free(_hp); }
    (void)_t1014;
    I64 _t1015 = 0;
    (void)_t1015;
    Bool _t1016 = I64_eq(_t1014, _t1015);
    (void)_t1016;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1016; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1017 = 0;
    (void)_t1017;
    I64 _t1018 = 1;
    (void)_t1018;
    I64 _t1019; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1019 = *_hp; free(_hp); }
    (void)_t1019;
    I64 _t1020 = I64_sub(_t1017, _t1018);
    (void)_t1020;
    ;
    ;
    Bool _t1021 = I64_eq(_t1019, _t1020);
    (void)_t1021;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1021; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1022; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1022 = *_hp; free(_hp); }
    (void)_t1022;
    I64 _t1023 = 1;
    (void)_t1023;
    Bool _t1024 = I64_eq(_t1022, _t1023);
    (void)_t1024;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1024; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1025; { Bool *_hp = (Bool *)Str_eq(a, b); _t1025 = *_hp; free(_hp); }
    (void)_t1025;
    Bool _t1026 = Bool_not(_t1025);
    (void)_t1026;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1026; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1027; { Bool *_hp = (Bool *)Str_gt(a, b); _t1027 = *_hp; free(_hp); }
    (void)_t1027;
    Bool _t1028 = Bool_not(_t1027);
    (void)_t1028;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1028; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1029; { Bool *_hp = (Bool *)Str_lt(a, b); _t1029 = *_hp; free(_hp); }
    (void)_t1029;
    Bool _t1030 = Bool_not(_t1029);
    (void)_t1030;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1030; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1041; { U64 *_hp = (U64 *)Vec_len(parts); _t1041 = *_hp; free(_hp); }
    (void)_t1041;
    U64 _t1042 = 0;
    (void)_t1042;
    Bool _t1043 = U64_eq(_t1041, _t1042);
    (void)_t1043;
    ;
    ;
    if (_t1043) {
        Str *_t1031 = Str_lit("", 0ULL);
        (void)_t1031;
        ;
        return _t1031;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _t1039 = 0;
        (void)_t1039;
        U64 _t1040; { U64 *_hp = (U64 *)Vec_len(parts); _t1040 = *_hp; free(_hp); }
        (void)_t1040;
        Range *_fc1032 = Range_new(_t1039, _t1040);
        (void)_fc1032;
        ;
        ;
        U64 _fi1032 = 0;
        (void)_fi1032;
        while (1) {
            U64 _t1034; { U64 *_hp = (U64 *)Range_len(_fc1032); _t1034 = *_hp; free(_hp); }
            (void)_t1034;
            Bool _wcond1033; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1032}, &(U64){_t1034}); _wcond1033 = *_hp; free(_hp); }
            (void)_wcond1033;
            ;
            if (_wcond1033) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1032, _fi1032);
            (void)i;
            U64 _t1035 = 1;
            (void)_t1035;
            U64 _t1036 = U64_add(_fi1032, _t1035);
            (void)_t1036;
            ;
            _fi1032 = _t1036;
            ;
            U64 _t1037 = 0;
            (void)_t1037;
            Bool _t1038; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1037}); _t1038 = *_hp; free(_hp); }
            (void)_t1038;
            ;
            if (_t1038) {
                result = Str_concat(result, sep);
            }
            ;
            Str *p = Vec_get(parts, i);
            (void)p;
            result = Str_concat(result, p);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc1032, &(Bool){1});
        ;
    }
    return result;
}

