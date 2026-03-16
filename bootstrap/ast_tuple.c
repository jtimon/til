Tuple * Tuple_new(void) {
    U64 _t1173 = 8;
    (void)_t1173;
    Str *_t1174 = Str_lit("Str", 3ULL);
    (void)_t1174;
    U64 _t1175; { U64 *_hp = (U64 *)Str_size(); _t1175 = *_hp; free(_hp); }
    (void)_t1175;
    Str *_t1176 = Str_lit("U64", 3ULL);
    (void)_t1176;
    U64 _t1177; { U64 *_hp = (U64 *)U64_size(); _t1177 = *_hp; free(_hp); }
    (void)_t1177;
    void *_t1178 = malloc(_t1173);
    (void)_t1178;
    ;
    U64 _t1179 = 0;
    (void)_t1179;
    I64 _t1180 = 8;
    (void)_t1180;
    Tuple *_t1181 = malloc(sizeof(Tuple));
    _t1181->data = _t1178;
    _t1181->total_size = _t1179;
    _t1181->cap = _t1180;
    { Vec *_ca = Vec_new(_t1174, &(U64){_t1175}); _t1181->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1176, &(U64){_t1177}); _t1181->type_sizes = *_ca; free(_ca); }
    (void)_t1181;
    Str_delete(_t1174, &(Bool){1});
    ;
    Str_delete(_t1176, &(Bool){1});
    ;
    ;
    ;
    return _t1181;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1182; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1182; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1189; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        U64 _t1186 = 2;
        (void)_t1186;
        U64 new_cap = U64_mul(self->cap, _t1186);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1183; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1183 = *_hp; free(_hp); }
            (void)_wcond1183;
            if (_wcond1183) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1184 = 2;
            (void)_t1184;
            U64 _t1185 = U64_mul(new_cap, _t1184);
            (void)_t1185;
            ;
            new_cap = _t1185;
            ;
        }
        void *_t1187 = realloc(self->data, new_cap);
        (void)_t1187;
        self->data = _t1187;
        U64 _t1188 = U64_clone(&(U64){new_cap});
        (void)_t1188;
        ;
        self->cap = _t1188;
        ;
    }
    ;
    void *_t1190 = ptr_add(self->data, self->total_size);
    (void)_t1190;
    memcpy(_t1190, val, DEREF(elem_size));
    free(val);
    Str *_t1191 = Str_clone(elem_type);
    (void)_t1191;
    Vec_push(&self->type_names, _t1191);
    U64 _t1192 = U64_clone(elem_size);
    (void)_t1192;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1192; _oa; }));
    U64 _t1193 = U64_clone(&(U64){new_total});
    (void)_t1193;
    ;
    self->total_size = _t1193;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1219; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    Bool _t1220; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1219}); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    ;
    if (_t1220) {
        Str *_t1194 = Str_lit("Str", 3ULL);
        (void)_t1194;
        U64 _t1195; { U64 *_hp = (U64 *)Str_size(); _t1195 = *_hp; free(_hp); }
        (void)_t1195;
        U64 _t1196 = 5;
        (void)_t1196;
        Array *_va19 = Array_new(_t1194, &(U64){_t1195}, &(U64){_t1196});
        (void)_va19;
        Str_delete(_t1194, &(Bool){1});
        ;
        ;
        U64 _t1197 = 0;
        (void)_t1197;
        Str *_t1198 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1198;
        Array_set(_va19, &(U64){_t1197}, _t1198);
        ;
        U64 _t1199 = 1;
        (void)_t1199;
        Str *_t1200 = U64_to_str(DEREF(i));
        (void)_t1200;
        Array_set(_va19, &(U64){_t1199}, _t1200);
        ;
        U64 _t1201 = 2;
        (void)_t1201;
        Str *_t1202 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1202;
        Array_set(_va19, &(U64){_t1201}, _t1202);
        ;
        U64 _t1203; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1203 = *_hp; free(_hp); }
        (void)_t1203;
        U64 _t1204 = 3;
        (void)_t1204;
        Str *_t1205 = U64_to_str(_t1203);
        (void)_t1205;
        ;
        Array_set(_va19, &(U64){_t1204}, _t1205);
        ;
        U64 _t1206 = 4;
        (void)_t1206;
        Str *_t1207 = Str_lit(")", 1ULL);
        (void)_t1207;
        Array_set(_va19, &(U64){_t1206}, _t1207);
        ;
        Str *_t1208 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1208;
        panic(_t1208, _va19);
        Str_delete(_t1208, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1209 = 0;
        (void)_fi1209;
        while (1) {
            U64 _t1211 = 0;
            (void)_t1211;
            Range *_t1212 = Range_new(_t1211, DEREF(i));
            (void)_t1212;
            ;
            U64 _t1213; { U64 *_hp = (U64 *)Range_len(_t1212); _t1213 = *_hp; free(_hp); }
            (void)_t1213;
            Range_delete(_t1212, &(Bool){1});
            Bool _wcond1210; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1209}, &(U64){_t1213}); _wcond1210 = *_hp; free(_hp); }
            (void)_wcond1210;
            ;
            if (_wcond1210) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1214 = 0;
            (void)_t1214;
            Range *_t1215 = Range_new(_t1214, DEREF(i));
            (void)_t1215;
            ;
            U64 *j = Range_get(_t1215, _fi1209);
            (void)j;
            Range_delete(_t1215, &(Bool){1});
            U64 _t1216 = 1;
            (void)_t1216;
            U64 _t1217 = U64_add(_fi1209, _t1216);
            (void)_t1217;
            ;
            _fi1209 = _t1217;
            ;
            U64 *sz = Vec_get(&self->type_sizes, j);
            (void)sz;
            U64 _t1218 = U64_add(DEREF(offset), DEREF(sz));
            (void)_t1218;
            U64_delete(j, &(Bool){1});
            *offset = _t1218;
            ;
        }
        ;
    }
    void *_t1221 = ptr_add(self->data, DEREF(offset));
    (void)_t1221;
    U64_delete(offset, &(Bool){1});
    return _t1221;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1222 = Vec_get(&self->type_names, i);
    (void)_t1222;
    return _t1222;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1223 = Vec_get(&self->type_sizes, i);
    (void)_t1223;
    return _t1223;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1224 = 0;
        (void)_fi1224;
        while (1) {
            U64 _t1226 = 0;
            (void)_t1226;
            U64 _t1227; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1227 = *_hp; free(_hp); }
            (void)_t1227;
            Range *_t1228 = Range_new(_t1226, _t1227);
            (void)_t1228;
            ;
            ;
            U64 _t1229; { U64 *_hp = (U64 *)Range_len(_t1228); _t1229 = *_hp; free(_hp); }
            (void)_t1229;
            Range_delete(_t1228, &(Bool){1});
            Bool _wcond1225; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1224}, &(U64){_t1229}); _wcond1225 = *_hp; free(_hp); }
            (void)_wcond1225;
            ;
            if (_wcond1225) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1230 = 0;
            (void)_t1230;
            U64 _t1231; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1231 = *_hp; free(_hp); }
            (void)_t1231;
            Range *_t1232 = Range_new(_t1230, _t1231);
            (void)_t1232;
            ;
            ;
            U64 *i = Range_get(_t1232, _fi1224);
            (void)i;
            Range_delete(_t1232, &(Bool){1});
            U64 _t1233 = 1;
            (void)_t1233;
            U64 _t1234 = U64_add(_fi1224, _t1233);
            (void)_t1234;
            ;
            _fi1224 = _t1234;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1235 = ptr_add(self->data, DEREF(offset));
            (void)_t1235;
            Bool _t1236 = 0;
            (void)_t1236;
            dyn_call_delete(tn, _t1235, &(Bool){_t1236});
            ;
            U64 _t1237 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1237;
            U64_delete(i, &(Bool){1});
            *offset = _t1237;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1238 = 0;
    (void)_t1238;
    Vec_delete(&self->type_names, &(Bool){_t1238});
    ;
    Bool _t1239 = 0;
    (void)_t1239;
    Vec_delete(&self->type_sizes, &(Bool){_t1239});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1256 = 0;
    (void)_t1256;
    Bool _t1257 = U64_eq(new_cap, _t1256);
    (void)_t1257;
    ;
    if (_t1257) {
        I64 _t1240 = 8;
        (void)_t1240;
        U64 _t1241; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1240}); _t1241 = *_hp; free(_hp); }
        (void)_t1241;
        ;
        new_cap = _t1241;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 _fi1242 = 0;
        (void)_fi1242;
        while (1) {
            U64 _t1244 = 0;
            (void)_t1244;
            U64 _t1245; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1245 = *_hp; free(_hp); }
            (void)_t1245;
            Range *_t1246 = Range_new(_t1244, _t1245);
            (void)_t1246;
            ;
            ;
            U64 _t1247; { U64 *_hp = (U64 *)Range_len(_t1246); _t1247 = *_hp; free(_hp); }
            (void)_t1247;
            Range_delete(_t1246, &(Bool){1});
            Bool _wcond1243; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1242}, &(U64){_t1247}); _wcond1243 = *_hp; free(_hp); }
            (void)_wcond1243;
            ;
            if (_wcond1243) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1248 = 0;
            (void)_t1248;
            U64 _t1249; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1249 = *_hp; free(_hp); }
            (void)_t1249;
            Range *_t1250 = Range_new(_t1248, _t1249);
            (void)_t1250;
            ;
            ;
            U64 *i = Range_get(_t1250, _fi1242);
            (void)i;
            Range_delete(_t1250, &(Bool){1});
            U64 _t1251 = 1;
            (void)_t1251;
            U64 _t1252 = U64_add(_fi1242, _t1251);
            (void)_t1252;
            ;
            _fi1242 = _t1252;
            ;
            Str *tn = Vec_get(&self->type_names, i);
            (void)tn;
            U64 *ts = Vec_get(&self->type_sizes, i);
            (void)ts;
            void *_t1253 = ptr_add(self->data, DEREF(offset));
            (void)_t1253;
            void *cloned = dyn_call_clone(tn, _t1253);
            (void)cloned;
            void *_t1254 = ptr_add(new_data, DEREF(offset));
            (void)_t1254;
            memcpy(_t1254, cloned, DEREF(ts));
            free(cloned);
            U64 _t1255 = U64_add(DEREF(offset), DEREF(ts));
            (void)_t1255;
            U64_delete(i, &(Bool){1});
            *offset = _t1255;
            ;
        }
        ;
    }
    U64_delete(offset, &(Bool){1});
    U64 _t1258 = U64_clone(&(U64){new_cap});
    (void)_t1258;
    ;
    Vec *_t1259 = Vec_clone(&self->type_names);
    (void)_t1259;
    Vec *_t1260 = Vec_clone(&self->type_sizes);
    (void)_t1260;
    Tuple *_t1261 = malloc(sizeof(Tuple));
    _t1261->data = new_data;
    _t1261->total_size = self->total_size;
    _t1261->cap = _t1258;
    { Vec *_ca = Vec_clone(_t1259); _t1261->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1260); _t1261->type_sizes = *_ca; free(_ca); }
    (void)_t1261;
    ;
    Vec_delete(_t1259, &(Bool){1});
    Vec_delete(_t1260, &(Bool){1});
    return _t1261;
}

U64 *Tuple_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Tuple);
    return r;
}

