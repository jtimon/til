Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t1067 = malloc(DEREF(elem_size));
    (void)_t1067;
    U64 _t1068 = 0;
    (void)_t1068;
    I64 _t1069 = 1;
    (void)_t1069;
    U64 _t1070 = U64_clone(elem_size);
    (void)_t1070;
    Vec *_t1071 = malloc(sizeof(Vec));
    _t1071->data = _t1067;
    _t1071->count = _t1068;
    _t1071->cap = _t1069;
    _t1071->elem_size = _t1070;
    { Str *_ca = Str_clone(elem_type); _t1071->elem_type = *_ca; free(_ca); }
    (void)_t1071;
    ;
    ;
    ;
    return _t1071;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t1076 = U64_eq(self->count, self->cap);
    (void)_t1076;
    if (_t1076) {
        U64 _t1072 = 2;
        (void)_t1072;
        U64 new_cap = U64_mul(self->cap, _t1072);
        (void)new_cap;
        ;
        U64 _t1073 = U64_mul(new_cap, self->elem_size);
        (void)_t1073;
        void *_t1074 = realloc(self->data, _t1073);
        (void)_t1074;
        ;
        self->data = _t1074;
        U64 _t1075 = U64_clone(&(U64){new_cap});
        (void)_t1075;
        ;
        self->cap = _t1075;
        ;
    }
    ;
    U64 *_t1077 = malloc(sizeof(U64)); *_t1077 = U64_mul(self->count, self->elem_size);
    (void)_t1077;
    void *_t1078 = ptr_add(self->data, DEREF(_t1077));
    (void)_t1078;
    memcpy(_t1078, val, self->elem_size);
    U64_delete(_t1077, &(Bool){1});
    free(val);
    U64 _t1079 = 1;
    (void)_t1079;
    U64 _t1080 = U64_add(self->count, _t1079);
    (void)_t1080;
    ;
    self->count = _t1080;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t1095; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t1095 = *_hp; free(_hp); }
    (void)_t1095;
    if (_t1095) {
        Str *_t1081 = Str_lit("Str", 3ULL);
        (void)_t1081;
        U64 _t1082; { U64 *_hp = (U64 *)Str_size(); _t1082 = *_hp; free(_hp); }
        (void)_t1082;
        U64 _t1083 = 5;
        (void)_t1083;
        Array *_va18 = Array_new(_t1081, &(U64){_t1082}, &(U64){_t1083});
        (void)_va18;
        Str_delete(_t1081, &(Bool){1});
        ;
        ;
        U64 _t1084 = 0;
        (void)_t1084;
        Str *_t1085 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t1085;
        Array_set(_va18, &(U64){_t1084}, _t1085);
        ;
        U64 _t1086 = 1;
        (void)_t1086;
        Str *_t1087 = U64_to_str(DEREF(i));
        (void)_t1087;
        Array_set(_va18, &(U64){_t1086}, _t1087);
        ;
        U64 _t1088 = 2;
        (void)_t1088;
        Str *_t1089 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1089;
        Array_set(_va18, &(U64){_t1088}, _t1089);
        ;
        U64 _t1090 = 3;
        (void)_t1090;
        Str *_t1091 = U64_to_str(self->count);
        (void)_t1091;
        Array_set(_va18, &(U64){_t1090}, _t1091);
        ;
        U64 _t1092 = 4;
        (void)_t1092;
        Str *_t1093 = Str_lit(")", 1ULL);
        (void)_t1093;
        Array_set(_va18, &(U64){_t1092}, _t1093);
        ;
        Str *_t1094 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t1094;
        panic(_t1094, _va18);
        Str_delete(_t1094, &(Bool){1});
    }
    ;
    U64 *_t1096 = malloc(sizeof(U64)); *_t1096 = U64_mul(DEREF(i), self->elem_size);
    (void)_t1096;
    void *_t1097 = ptr_add(self->data, DEREF(_t1096));
    (void)_t1097;
    U64_delete(_t1096, &(Bool){1});
    return _t1097;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1111; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1111 = *_hp; free(_hp); }
    (void)_t1111;
    Bool _t1112 = Bool_not(_t1111);
    (void)_t1112;
    ;
    if (_t1112) {
        {
            U64 _fi1098 = 0;
            (void)_fi1098;
            while (1) {
                U64 _t1100 = 0;
                (void)_t1100;
                Range *_t1101 = Range_new(_t1100, self->count);
                (void)_t1101;
                ;
                U64 _t1102; { U64 *_hp = (U64 *)Range_len(_t1101); _t1102 = *_hp; free(_hp); }
                (void)_t1102;
                Range_delete(_t1101, &(Bool){1});
                Bool _wcond1099; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1098}, &(U64){_t1102}); _wcond1099 = *_hp; free(_hp); }
                (void)_wcond1099;
                ;
                if (_wcond1099) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1103 = 0;
                (void)_t1103;
                Range *_t1104 = Range_new(_t1103, self->count);
                (void)_t1104;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1104, _fi1098); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1104, &(Bool){1});
                U64 _t1105 = 1;
                (void)_t1105;
                U64 _t1106 = U64_add(_fi1098, _t1105);
                (void)_t1106;
                ;
                _fi1098 = _t1106;
                ;
                U64 *_t1107 = malloc(sizeof(U64)); *_t1107 = U64_mul(i, self->elem_size);
                (void)_t1107;
                ;
                void *_t1108 = ptr_add(self->data, DEREF(_t1107));
                (void)_t1108;
                Bool _t1109 = 0;
                (void)_t1109;
                dyn_call_delete(&self->elem_type, _t1108, &(Bool){_t1109});
                U64_delete(_t1107, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1113; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t1113 = *_hp; free(_hp); }
    (void)_t1113;
    Bool _t1114 = Bool_not(_t1113);
    (void)_t1114;
    ;
    if (_t1114) {
        Bool _t1110 = 0;
        (void)_t1110;
        Str_delete(&self->elem_type, &(Bool){_t1110});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1128 = U64_mul(self->cap, self->elem_size);
    (void)_t1128;
    U8 *new_data = malloc(_t1128);
    (void)new_data;
    ;
    {
        U64 _fi1115 = 0;
        (void)_fi1115;
        while (1) {
            U64 _t1117 = 0;
            (void)_t1117;
            Range *_t1118 = Range_new(_t1117, self->count);
            (void)_t1118;
            ;
            U64 _t1119; { U64 *_hp = (U64 *)Range_len(_t1118); _t1119 = *_hp; free(_hp); }
            (void)_t1119;
            Range_delete(_t1118, &(Bool){1});
            Bool _wcond1116; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1115}, &(U64){_t1119}); _wcond1116 = *_hp; free(_hp); }
            (void)_wcond1116;
            ;
            if (_wcond1116) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1120 = 0;
            (void)_t1120;
            Range *_t1121 = Range_new(_t1120, self->count);
            (void)_t1121;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1121, _fi1115); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1121, &(Bool){1});
            U64 _t1122 = 1;
            (void)_t1122;
            U64 _t1123 = U64_add(_fi1115, _t1122);
            (void)_t1123;
            ;
            _fi1115 = _t1123;
            ;
            U64 *_t1124 = malloc(sizeof(U64)); *_t1124 = U64_mul(i, self->elem_size);
            (void)_t1124;
            void *_t1125 = ptr_add(self->data, DEREF(_t1124));
            (void)_t1125;
            void *cloned = dyn_call_clone(&self->elem_type, _t1125);
            (void)cloned;
            U64_delete(_t1124, &(Bool){1});
            U64 *_t1126 = malloc(sizeof(U64)); *_t1126 = U64_mul(i, self->elem_size);
            (void)_t1126;
            ;
            void *_t1127 = ptr_add(new_data, DEREF(_t1126));
            (void)_t1127;
            memcpy(_t1127, cloned, self->elem_size);
            U64_delete(_t1126, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1129 = malloc(sizeof(Vec));
    _t1129->data = new_data;
    _t1129->count = self->count;
    _t1129->cap = self->cap;
    _t1129->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1129->elem_type = *_ca; free(_ca); }
    (void)_t1129;
    return _t1129;
}

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

