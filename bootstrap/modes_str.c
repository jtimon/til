#include "modes_str.h"

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1075; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1075 = *_hp; free(_hp); }
    (void)_t1075;
    I64 _t1076 = 0;
    (void)_t1076;
    Bool _t1077 = I64_eq(_t1075, _t1076);
    (void)_t1077;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1077; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1078 = 0;
    (void)_t1078;
    I64 _t1079 = 1;
    (void)_t1079;
    I64 _t1080; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1080 = *_hp; free(_hp); }
    (void)_t1080;
    I64 _t1081 = I64_sub(_t1078, _t1079);
    (void)_t1081;
    ;
    ;
    Bool _t1082 = I64_eq(_t1080, _t1081);
    (void)_t1082;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1082; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t1083; { I64 *_hp = (I64 *)Str_cmp(a, b); _t1083 = *_hp; free(_hp); }
    (void)_t1083;
    I64 _t1084 = 1;
    (void)_t1084;
    Bool _t1085 = I64_eq(_t1083, _t1084);
    (void)_t1085;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1085; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1086; { Bool *_hp = (Bool *)Str_eq(a, b); _t1086 = *_hp; free(_hp); }
    (void)_t1086;
    Bool _t1087 = Bool_not(_t1086);
    (void)_t1087;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1087; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1088; { Bool *_hp = (Bool *)Str_gt(a, b); _t1088 = *_hp; free(_hp); }
    (void)_t1088;
    Bool _t1089 = Bool_not(_t1088);
    (void)_t1089;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1089; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t1090; { Bool *_hp = (Bool *)Str_lt(a, b); _t1090 = *_hp; free(_hp); }
    (void)_t1090;
    Bool _t1091 = Bool_not(_t1090);
    (void)_t1091;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1091; return _r; }
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1106; { U64 *_hp = (U64 *)Vec_len(parts); _t1106 = *_hp; free(_hp); }
    (void)_t1106;
    U64 _t1107 = 0;
    (void)_t1107;
    Bool _t1108 = U64_eq(_t1106, _t1107);
    (void)_t1108;
    ;
    ;
    if (_t1108) {
        Str *_t1092 = Str_lit("", 0ULL);
        (void)_t1092;
        ;
        return _t1092;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1093 = 0;
        (void)_fi1093;
        while (1) {
            U64 _t1095 = 0;
            (void)_t1095;
            U64 _t1096; { U64 *_hp = (U64 *)Vec_len(parts); _t1096 = *_hp; free(_hp); }
            (void)_t1096;
            Range *_t1097 = Range_new(_t1095, _t1096);
            (void)_t1097;
            ;
            ;
            U64 _t1098; { U64 *_hp = (U64 *)Range_len(_t1097); _t1098 = *_hp; free(_hp); }
            (void)_t1098;
            Range_delete(_t1097, &(Bool){1});
            Bool _wcond1094; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1093}, &(U64){_t1098}); _wcond1094 = *_hp; free(_hp); }
            (void)_wcond1094;
            ;
            if (_wcond1094) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1099 = 0;
            (void)_t1099;
            U64 _t1100; { U64 *_hp = (U64 *)Vec_len(parts); _t1100 = *_hp; free(_hp); }
            (void)_t1100;
            Range *_t1101 = Range_new(_t1099, _t1100);
            (void)_t1101;
            ;
            ;
            U64 *i = Range_get(_t1101, _fi1093);
            (void)i;
            Range_delete(_t1101, &(Bool){1});
            U64 _t1102 = 1;
            (void)_t1102;
            U64 _t1103 = U64_add(_fi1093, _t1102);
            (void)_t1103;
            ;
            _fi1093 = _t1103;
            ;
            U64 _t1104 = 0;
            (void)_t1104;
            Bool _t1105; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1104}); _t1105 = *_hp; free(_hp); }
            (void)_t1105;
            ;
            if (_t1105) {
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

