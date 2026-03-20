#include "til_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1015; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1015 = *_hp; free(_hp); }
    (void)_t1015;
    I64 _t1016 = 0;
    (void)_t1016;
    Bool _t1017 = I64_eq(_t1015, _t1016);
    (void)_t1017;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1017; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1018 = 0;
    (void)_t1018;
    I64 _t1019 = 1;
    (void)_t1019;
    I64 _t1020; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1020 = *_hp; free(_hp); }
    (void)_t1020;
    I64 _t1021 = I64_sub(_t1018, _t1019);
    (void)_t1021;
    ;
    ;
    Bool _t1022 = I64_eq(_t1020, _t1021);
    (void)_t1022;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1022; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1023; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1023 = *_hp; free(_hp); }
    (void)_t1023;
    I64 _t1024 = 1;
    (void)_t1024;
    Bool _t1025 = I64_eq(_t1023, _t1024);
    (void)_t1025;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1025; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1026; { Bool *_hp = (Bool *)Str_eq(a, b); _t1026 = *_hp; free(_hp); }
    (void)_t1026;
    Bool _t1027 = Bool_not(_t1026);
    (void)_t1027;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1027; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1028; { Bool *_hp = (Bool *)Str_gt(a, b); _t1028 = *_hp; free(_hp); }
    (void)_t1028;
    Bool _t1029 = Bool_not(_t1028);
    (void)_t1029;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1029; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1030; { Bool *_hp = (Bool *)Str_lt(a, b); _t1030 = *_hp; free(_hp); }
    (void)_t1030;
    Bool _t1031 = Bool_not(_t1030);
    (void)_t1031;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1031; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1042; { U64 *_hp = (U64 *)Vec_len(parts); _t1042 = *_hp; free(_hp); }
    (void)_t1042;
    U64 _t1043 = 0;
    (void)_t1043;
    Bool _t1044 = U64_eq(_t1042, _t1043);
    (void)_t1044;
    ;
    ;
    if (_t1044) {
        Str *_t1032 = Str_lit("", 0ULL);
        (void)_t1032;
        ;
        return _t1032;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _t1040 = 0;
        (void)_t1040;
        U64 _t1041; { U64 *_hp = (U64 *)Vec_len(parts); _t1041 = *_hp; free(_hp); }
        (void)_t1041;
        Range *_fc1033 = Range_new(_t1040, _t1041);
        (void)_fc1033;
        ;
        ;
        U64 _fi1033 = 0;
        (void)_fi1033;
        while (1) {
            U64 _t1035; { U64 *_hp = (U64 *)Range_len(_fc1033); _t1035 = *_hp; free(_hp); }
            (void)_t1035;
            Bool _wcond1034; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1033}, &(U64){_t1035}); _wcond1034 = *_hp; free(_hp); }
            (void)_wcond1034;
            ;
            if (_wcond1034) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc1033, _fi1033);
            (void)i;
            U64 _t1036 = 1;
            (void)_t1036;
            U64 _t1037 = U64_add(_fi1033, _t1036);
            (void)_t1037;
            ;
            _fi1033 = _t1037;
            ;
            U64 _t1038 = 0;
            (void)_t1038;
            Bool _t1039; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1038}); _t1039 = *_hp; free(_hp); }
            (void)_t1039;
            ;
            if (_t1039) {
                result = Str_concat(result, sep);
            }
            ;
            Str *p = Vec_get(parts, i);
            (void)p;
            result = Str_concat(result, p);
            U64_delete(i, &(Bool){1});
        }
        Range_delete(_fc1033, &(Bool){1});
        ;
    }
    return result;
}

