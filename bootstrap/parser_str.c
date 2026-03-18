#include "parser_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1021; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1021 = *_hp; free(_hp); }
    (void)_t1021;
    I64 _t1022 = 0;
    (void)_t1022;
    Bool _t1023 = I64_eq(_t1021, _t1022);
    (void)_t1023;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1023; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1024 = 0;
    (void)_t1024;
    I64 _t1025 = 1;
    (void)_t1025;
    I64 _t1026; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1026 = *_hp; free(_hp); }
    (void)_t1026;
    I64 _t1027 = I64_sub(_t1024, _t1025);
    (void)_t1027;
    ;
    ;
    Bool _t1028 = I64_eq(_t1026, _t1027);
    (void)_t1028;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1028; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1029; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1029 = *_hp; free(_hp); }
    (void)_t1029;
    I64 _t1030 = 1;
    (void)_t1030;
    Bool _t1031 = I64_eq(_t1029, _t1030);
    (void)_t1031;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1031; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1032; { Bool *_hp = (Bool *)Str_eq(a, b); _t1032 = *_hp; free(_hp); }
    (void)_t1032;
    Bool _t1033 = Bool_not(_t1032);
    (void)_t1033;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1033; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1034; { Bool *_hp = (Bool *)Str_gt(a, b); _t1034 = *_hp; free(_hp); }
    (void)_t1034;
    Bool _t1035 = Bool_not(_t1034);
    (void)_t1035;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1035; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1036; { Bool *_hp = (Bool *)Str_lt(a, b); _t1036 = *_hp; free(_hp); }
    (void)_t1036;
    Bool _t1037 = Bool_not(_t1036);
    (void)_t1037;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1037; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1052; { U64 *_hp = (U64 *)Vec_len(parts); _t1052 = *_hp; free(_hp); }
    (void)_t1052;
    U64 _t1053 = 0;
    (void)_t1053;
    Bool _t1054 = U64_eq(_t1052, _t1053);
    (void)_t1054;
    ;
    ;
    if (_t1054) {
        Str *_t1038 = Str_lit("", 0ULL);
        (void)_t1038;
        ;
        return _t1038;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1039 = 0;
        (void)_fi1039;
        while (1) {
            U64 _t1041 = 0;
            (void)_t1041;
            U64 _t1042; { U64 *_hp = (U64 *)Vec_len(parts); _t1042 = *_hp; free(_hp); }
            (void)_t1042;
            Range *_t1043 = Range_new(_t1041, _t1042);
            (void)_t1043;
            ;
            ;
            U64 _t1044; { U64 *_hp = (U64 *)Range_len(_t1043); _t1044 = *_hp; free(_hp); }
            (void)_t1044;
            Range_delete(_t1043, &(Bool){1});
            Bool _wcond1040; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1039}, &(U64){_t1044}); _wcond1040 = *_hp; free(_hp); }
            (void)_wcond1040;
            ;
            if (_wcond1040) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1045 = 0;
            (void)_t1045;
            U64 _t1046; { U64 *_hp = (U64 *)Vec_len(parts); _t1046 = *_hp; free(_hp); }
            (void)_t1046;
            Range *_t1047 = Range_new(_t1045, _t1046);
            (void)_t1047;
            ;
            ;
            U64 *i = Range_get(_t1047, _fi1039);
            (void)i;
            Range_delete(_t1047, &(Bool){1});
            U64 _t1048 = 1;
            (void)_t1048;
            U64 _t1049 = U64_add(_fi1039, _t1048);
            (void)_t1049;
            ;
            _fi1039 = _t1049;
            ;
            U64 _t1050 = 0;
            (void)_t1050;
            Bool _t1051; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1050}); _t1051 = *_hp; free(_hp); }
            (void)_t1051;
            ;
            if (_t1051) {
                result = Str_concat(result, sep);
            }
            ;
            Str *p = Vec_get(parts, i);
            (void)p;
            result = Str_concat(result, p);
            U64_delete(i, &(Bool){1});
        }
        ;
    }
    return result;
}

