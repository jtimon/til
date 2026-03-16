#include "ast_vec.h"

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1147 = Str_lit("Str", 3ULL);
    (void)_t1147;
    U64 _t1148; { U64 *_hp = (U64 *)Str_size(); _t1148 = *_hp; free(_hp); }
    (void)_t1148;
    Vec *parts = Vec_new(_t1147, &(U64){_t1148});
    (void)parts;
    Str_delete(_t1147, &(Bool){1});
    ;
    U64 _t1149; { U64 *_hp = (U64 *)Str_len(delim); _t1149 = *_hp; free(_hp); }
    (void)_t1149;
    U64 _t1150 = 0;
    (void)_t1150;
    Bool _t1151 = U64_eq(_t1149, _t1150);
    (void)_t1151;
    ;
    ;
    if (_t1151) {
        Str *_t1131 = Str_clone(s);
        (void)_t1131;
        Vec_push(parts, _t1131);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1141; { U64 *_hp = (U64 *)Str_len(s); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        U64 _t1142; { U64 *_hp = (U64 *)Str_len(delim); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        U64 _t1143 = U64_sub(_t1141, _t1142);
        (void)_t1143;
        ;
        ;
        Bool _wcond1132; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1143}); _wcond1132 = *_hp; free(_hp); }
        (void)_wcond1132;
        ;
        if (_wcond1132) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1144; { U64 *_hp = (U64 *)Str_len(delim); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        Str *_t1145 = Str_substr(s, &(U64){pos}, &(U64){_t1144});
        (void)_t1145;
        ;
        Bool _t1146; { Bool *_hp = (Bool *)Str_eq(_t1145, delim); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        Str_delete(_t1145, &(Bool){1});
        if (_t1146) {
            U64 _t1133 = U64_sub(pos, start);
            (void)_t1133;
            Str *_t1134 = Str_substr(s, &(U64){start}, &(U64){_t1133});
            (void)_t1134;
            ;
            Str *_t1135 = Str_clone(_t1134);
            (void)_t1135;
            Str_delete(_t1134, &(Bool){1});
            Vec_push(parts, _t1135);
            U64 _t1136; { U64 *_hp = (U64 *)Str_len(delim); _t1136 = *_hp; free(_hp); }
            (void)_t1136;
            U64 _t1137 = U64_add(pos, _t1136);
            (void)_t1137;
            ;
            start = _t1137;
            ;
            U64 _t1138 = U64_clone(&(U64){start});
            (void)_t1138;
            pos = _t1138;
            ;
        } else {
            U64 _t1139 = 1;
            (void)_t1139;
            U64 _t1140 = U64_add(pos, _t1139);
            (void)_t1140;
            ;
            pos = _t1140;
            ;
        }
        ;
    }
    ;
    U64 _t1152; { U64 *_hp = (U64 *)Str_len(s); _t1152 = *_hp; free(_hp); }
    (void)_t1152;
    U64 _t1153 = U64_sub(_t1152, start);
    (void)_t1153;
    ;
    Str *_t1154 = Str_substr(s, &(U64){start}, &(U64){_t1153});
    (void)_t1154;
    ;
    ;
    Str *_t1155 = Str_clone(_t1154);
    (void)_t1155;
    Str_delete(_t1154, &(Bool){1});
    Vec_push(parts, _t1155);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1170; { U64 *_hp = (U64 *)Vec_len(parts); _t1170 = *_hp; free(_hp); }
    (void)_t1170;
    U64 _t1171 = 0;
    (void)_t1171;
    Bool _t1172 = U64_eq(_t1170, _t1171);
    (void)_t1172;
    ;
    ;
    if (_t1172) {
        Str *_t1156 = Str_lit("", 0ULL);
        (void)_t1156;
        ;
        return _t1156;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1157 = 0;
        (void)_fi1157;
        while (1) {
            U64 _t1159 = 0;
            (void)_t1159;
            U64 _t1160; { U64 *_hp = (U64 *)Vec_len(parts); _t1160 = *_hp; free(_hp); }
            (void)_t1160;
            Range *_t1161 = Range_new(_t1159, _t1160);
            (void)_t1161;
            ;
            ;
            U64 _t1162; { U64 *_hp = (U64 *)Range_len(_t1161); _t1162 = *_hp; free(_hp); }
            (void)_t1162;
            Range_delete(_t1161, &(Bool){1});
            Bool _wcond1158; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1157}, &(U64){_t1162}); _wcond1158 = *_hp; free(_hp); }
            (void)_wcond1158;
            ;
            if (_wcond1158) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1163 = 0;
            (void)_t1163;
            U64 _t1164; { U64 *_hp = (U64 *)Vec_len(parts); _t1164 = *_hp; free(_hp); }
            (void)_t1164;
            Range *_t1165 = Range_new(_t1163, _t1164);
            (void)_t1165;
            ;
            ;
            U64 *i = Range_get(_t1165, _fi1157);
            (void)i;
            Range_delete(_t1165, &(Bool){1});
            U64 _t1166 = 1;
            (void)_t1166;
            U64 _t1167 = U64_add(_fi1157, _t1166);
            (void)_t1167;
            ;
            _fi1157 = _t1167;
            ;
            U64 _t1168 = 0;
            (void)_t1168;
            Bool _t1169; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1168}); _t1169 = *_hp; free(_hp); }
            (void)_t1169;
            ;
            if (_t1169) {
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

