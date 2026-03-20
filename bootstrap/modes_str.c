#include "modes_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1056; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1056 = *_hp; free(_hp); }
    (void)_t1056;
    I64 _t1057 = 0;
    (void)_t1057;
    Bool _t1058 = I64_eq(_t1056, _t1057);
    (void)_t1058;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1058; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1059 = 0;
    (void)_t1059;
    I64 _t1060 = 1;
    (void)_t1060;
    I64 _t1061; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1061 = *_hp; free(_hp); }
    (void)_t1061;
    I64 _t1062 = I64_sub(_t1059, _t1060);
    (void)_t1062;
    ;
    ;
    Bool _t1063 = I64_eq(_t1061, _t1062);
    (void)_t1063;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1063; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1064; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1064 = *_hp; free(_hp); }
    (void)_t1064;
    I64 _t1065 = 1;
    (void)_t1065;
    Bool _t1066 = I64_eq(_t1064, _t1065);
    (void)_t1066;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1067; { Bool *_hp = (Bool *)Str_eq(a, b); _t1067 = *_hp; free(_hp); }
    (void)_t1067;
    Bool _t1068 = Bool_not(_t1067);
    (void)_t1068;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1068; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1069; { Bool *_hp = (Bool *)Str_gt(a, b); _t1069 = *_hp; free(_hp); }
    (void)_t1069;
    Bool _t1070 = Bool_not(_t1069);
    (void)_t1070;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1070; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1071; { Bool *_hp = (Bool *)Str_lt(a, b); _t1071 = *_hp; free(_hp); }
    (void)_t1071;
    Bool _t1072 = Bool_not(_t1071);
    (void)_t1072;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1072; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1087; { U64 *_hp = (U64 *)Vec_len(parts); _t1087 = *_hp; free(_hp); }
    (void)_t1087;
    U64 _t1088 = 0;
    (void)_t1088;
    Bool _t1089 = U64_eq(_t1087, _t1088);
    (void)_t1089;
    ;
    ;
    if (_t1089) {
        Str *_t1073 = Str_lit("", 0ULL);
        (void)_t1073;
        ;
        return _t1073;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1074 = 0;
        (void)_fi1074;
        while (1) {
            U64 _t1076 = 0;
            (void)_t1076;
            U64 _t1077; { U64 *_hp = (U64 *)Vec_len(parts); _t1077 = *_hp; free(_hp); }
            (void)_t1077;
            Range *_t1078 = Range_new(_t1076, _t1077);
            (void)_t1078;
            ;
            ;
            U64 _t1079; { U64 *_hp = (U64 *)Range_len(_t1078); _t1079 = *_hp; free(_hp); }
            (void)_t1079;
            Range_delete(_t1078, &(Bool){1});
            Bool _wcond1075; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1074}, &(U64){_t1079}); _wcond1075 = *_hp; free(_hp); }
            (void)_wcond1075;
            ;
            if (_wcond1075) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1080 = 0;
            (void)_t1080;
            U64 _t1081; { U64 *_hp = (U64 *)Vec_len(parts); _t1081 = *_hp; free(_hp); }
            (void)_t1081;
            Range *_t1082 = Range_new(_t1080, _t1081);
            (void)_t1082;
            ;
            ;
            U64 *i = Range_get(_t1082, _fi1074);
            (void)i;
            Range_delete(_t1082, &(Bool){1});
            U64 _t1083 = 1;
            (void)_t1083;
            U64 _t1084 = U64_add(_fi1074, _t1083);
            (void)_t1084;
            ;
            _fi1074 = _t1084;
            ;
            U64 _t1085 = 0;
            (void)_t1085;
            Bool _t1086; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1085}); _t1086 = *_hp; free(_hp); }
            (void)_t1086;
            ;
            if (_t1086) {
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

