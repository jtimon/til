#include "lexer_vec.h"

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1150 = Str_lit("Str", 3ULL);
    (void)_t1150;
    U64 _t1151; { U64 *_hp = (U64 *)Str_size(); _t1151 = *_hp; free(_hp); }
    (void)_t1151;
    Vec *parts = Vec_new(_t1150, &(U64){_t1151});
    (void)parts;
    Str_delete(_t1150, &(Bool){1});
    ;
    U64 _t1152; { U64 *_hp = (U64 *)Str_len(delim); _t1152 = *_hp; free(_hp); }
    (void)_t1152;
    U64 _t1153 = 0;
    (void)_t1153;
    Bool _t1154 = U64_eq(_t1152, _t1153);
    (void)_t1154;
    ;
    ;
    if (_t1154) {
        Str *_t1134 = Str_clone(s);
        (void)_t1134;
        Vec_push(parts, _t1134);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1144; { U64 *_hp = (U64 *)Str_len(s); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        U64 _t1145; { U64 *_hp = (U64 *)Str_len(delim); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        U64 _t1146 = U64_sub(_t1144, _t1145);
        (void)_t1146;
        ;
        ;
        Bool _wcond1135; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1146}); _wcond1135 = *_hp; free(_hp); }
        (void)_wcond1135;
        ;
        if (_wcond1135) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1147; { U64 *_hp = (U64 *)Str_len(delim); _t1147 = *_hp; free(_hp); }
        (void)_t1147;
        Str *_t1148 = Str_substr(s, &(U64){pos}, &(U64){_t1147});
        (void)_t1148;
        ;
        Bool _t1149; { Bool *_hp = (Bool *)Str_eq(_t1148, delim); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        Str_delete(_t1148, &(Bool){1});
        if (_t1149) {
            U64 _t1136 = U64_sub(pos, start);
            (void)_t1136;
            Str *_t1137 = Str_substr(s, &(U64){start}, &(U64){_t1136});
            (void)_t1137;
            ;
            Str *_t1138 = Str_clone(_t1137);
            (void)_t1138;
            Str_delete(_t1137, &(Bool){1});
            Vec_push(parts, _t1138);
            U64 _t1139; { U64 *_hp = (U64 *)Str_len(delim); _t1139 = *_hp; free(_hp); }
            (void)_t1139;
            U64 _t1140 = U64_add(pos, _t1139);
            (void)_t1140;
            ;
            start = _t1140;
            ;
            U64 _t1141 = U64_clone(&(U64){start});
            (void)_t1141;
            pos = _t1141;
            ;
        } else {
            U64 _t1142 = 1;
            (void)_t1142;
            U64 _t1143 = U64_add(pos, _t1142);
            (void)_t1143;
            ;
            pos = _t1143;
            ;
        }
        ;
    }
    ;
    U64 _t1155; { U64 *_hp = (U64 *)Str_len(s); _t1155 = *_hp; free(_hp); }
    (void)_t1155;
    U64 _t1156 = U64_sub(_t1155, start);
    (void)_t1156;
    ;
    Str *_t1157 = Str_substr(s, &(U64){start}, &(U64){_t1156});
    (void)_t1157;
    ;
    ;
    Str *_t1158 = Str_clone(_t1157);
    (void)_t1158;
    Str_delete(_t1157, &(Bool){1});
    Vec_push(parts, _t1158);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1173; { U64 *_hp = (U64 *)Vec_len(parts); _t1173 = *_hp; free(_hp); }
    (void)_t1173;
    U64 _t1174 = 0;
    (void)_t1174;
    Bool _t1175 = U64_eq(_t1173, _t1174);
    (void)_t1175;
    ;
    ;
    if (_t1175) {
        Str *_t1159 = Str_lit("", 0ULL);
        (void)_t1159;
        ;
        return _t1159;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    {
        U64 _fi1160 = 0;
        (void)_fi1160;
        while (1) {
            U64 _t1162 = 0;
            (void)_t1162;
            U64 _t1163; { U64 *_hp = (U64 *)Vec_len(parts); _t1163 = *_hp; free(_hp); }
            (void)_t1163;
            Range *_t1164 = Range_new(_t1162, _t1163);
            (void)_t1164;
            ;
            ;
            U64 _t1165; { U64 *_hp = (U64 *)Range_len(_t1164); _t1165 = *_hp; free(_hp); }
            (void)_t1165;
            Range_delete(_t1164, &(Bool){1});
            Bool _wcond1161; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1160}, &(U64){_t1165}); _wcond1161 = *_hp; free(_hp); }
            (void)_wcond1161;
            ;
            if (_wcond1161) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1166 = 0;
            (void)_t1166;
            U64 _t1167; { U64 *_hp = (U64 *)Vec_len(parts); _t1167 = *_hp; free(_hp); }
            (void)_t1167;
            Range *_t1168 = Range_new(_t1166, _t1167);
            (void)_t1168;
            ;
            ;
            U64 *i = Range_get(_t1168, _fi1160);
            (void)i;
            Range_delete(_t1168, &(Bool){1});
            U64 _t1169 = 1;
            (void)_t1169;
            U64 _t1170 = U64_add(_fi1160, _t1169);
            (void)_t1170;
            ;
            _fi1160 = _t1170;
            ;
            U64 _t1171 = 0;
            (void)_t1171;
            Bool _t1172; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1171}); _t1172 = *_hp; free(_hp); }
            (void)_t1172;
            ;
            if (_t1172) {
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

