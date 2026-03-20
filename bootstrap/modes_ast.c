#include "modes_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw1254 = TilType_clone(t);
        (void)_sw1254;
        Bool _t1289; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_Unknown()); _t1289 = *_hp; free(_hp); }
        (void)_t1289;
        if (_t1289) {
            Str *_t1255 = Str_lit("unknown", 7ULL);
            (void)_t1255;
            TilType_delete(_sw1254, &(Bool){1});
            ;
            return _t1255;
        } else {
            Bool _t1288; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_None()); _t1288 = *_hp; free(_hp); }
            (void)_t1288;
            if (_t1288) {
                Str *_t1256 = Str_lit("None", 4ULL);
                (void)_t1256;
                ;
                TilType_delete(_sw1254, &(Bool){1});
                ;
                return _t1256;
            } else {
                Bool _t1287; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_I64()); _t1287 = *_hp; free(_hp); }
                (void)_t1287;
                if (_t1287) {
                    Str *_t1257 = Str_lit("I64", 3ULL);
                    (void)_t1257;
                    ;
                    ;
                    TilType_delete(_sw1254, &(Bool){1});
                    ;
                    return _t1257;
                } else {
                    Bool _t1286; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_U8()); _t1286 = *_hp; free(_hp); }
                    (void)_t1286;
                    if (_t1286) {
                        Str *_t1258 = Str_lit("U8", 2ULL);
                        (void)_t1258;
                        ;
                        ;
                        ;
                        TilType_delete(_sw1254, &(Bool){1});
                        ;
                        return _t1258;
                    } else {
                        Bool _t1285; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_I16()); _t1285 = *_hp; free(_hp); }
                        (void)_t1285;
                        if (_t1285) {
                            Str *_t1259 = Str_lit("I16", 3ULL);
                            (void)_t1259;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw1254, &(Bool){1});
                            ;
                            return _t1259;
                        } else {
                            Bool _t1284; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_I32()); _t1284 = *_hp; free(_hp); }
                            (void)_t1284;
                            if (_t1284) {
                                Str *_t1260 = Str_lit("I32", 3ULL);
                                (void)_t1260;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw1254, &(Bool){1});
                                ;
                                return _t1260;
                            } else {
                                Bool _t1283; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_U32()); _t1283 = *_hp; free(_hp); }
                                (void)_t1283;
                                if (_t1283) {
                                    Str *_t1261 = Str_lit("U32", 3ULL);
                                    (void)_t1261;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw1254, &(Bool){1});
                                    ;
                                    return _t1261;
                                } else {
                                    Bool _t1282; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_U64()); _t1282 = *_hp; free(_hp); }
                                    (void)_t1282;
                                    if (_t1282) {
                                        Str *_t1262 = Str_lit("U64", 3ULL);
                                        (void)_t1262;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw1254, &(Bool){1});
                                        ;
                                        return _t1262;
                                    } else {
                                        Bool _t1281; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_F32()); _t1281 = *_hp; free(_hp); }
                                        (void)_t1281;
                                        if (_t1281) {
                                            Str *_t1263 = Str_lit("F32", 3ULL);
                                            (void)_t1263;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw1254, &(Bool){1});
                                            ;
                                            return _t1263;
                                        } else {
                                            Bool _t1280; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_Bool()); _t1280 = *_hp; free(_hp); }
                                            (void)_t1280;
                                            if (_t1280) {
                                                Str *_t1264 = Str_lit("Bool", 4ULL);
                                                (void)_t1264;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw1254, &(Bool){1});
                                                ;
                                                return _t1264;
                                            } else {
                                                Bool _t1279; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_Struct()); _t1279 = *_hp; free(_hp); }
                                                (void)_t1279;
                                                if (_t1279) {
                                                    Str *_t1265 = Str_lit("Struct", 6ULL);
                                                    (void)_t1265;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw1254, &(Bool){1});
                                                    ;
                                                    return _t1265;
                                                } else {
                                                    Bool _t1278; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_StructDef()); _t1278 = *_hp; free(_hp); }
                                                    (void)_t1278;
                                                    if (_t1278) {
                                                        Str *_t1266 = Str_lit("StructDef", 9ULL);
                                                        (void)_t1266;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw1254, &(Bool){1});
                                                        ;
                                                        return _t1266;
                                                    } else {
                                                        Bool _t1277; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_Enum()); _t1277 = *_hp; free(_hp); }
                                                        (void)_t1277;
                                                        if (_t1277) {
                                                            Str *_t1267 = Str_lit("Enum", 4ULL);
                                                            (void)_t1267;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw1254, &(Bool){1});
                                                            ;
                                                            return _t1267;
                                                        } else {
                                                            Bool _t1276; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_EnumDef()); _t1276 = *_hp; free(_hp); }
                                                            (void)_t1276;
                                                            if (_t1276) {
                                                                Str *_t1268 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t1268;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw1254, &(Bool){1});
                                                                ;
                                                                return _t1268;
                                                            } else {
                                                                Bool _t1275; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_FuncDef()); _t1275 = *_hp; free(_hp); }
                                                                (void)_t1275;
                                                                if (_t1275) {
                                                                    Str *_t1269 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t1269;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw1254, &(Bool){1});
                                                                    ;
                                                                    return _t1269;
                                                                } else {
                                                                    Bool _t1274; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_FuncPtr()); _t1274 = *_hp; free(_hp); }
                                                                    (void)_t1274;
                                                                    if (_t1274) {
                                                                        Str *_t1270 = Str_lit("Fn", 2ULL);
                                                                        (void)_t1270;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw1254, &(Bool){1});
                                                                        ;
                                                                        return _t1270;
                                                                    } else {
                                                                        Bool _t1273; { Bool *_hp = (Bool *)TilType_eq(_sw1254, TilType_Dynamic()); _t1273 = *_hp; free(_hp); }
                                                                        (void)_t1273;
                                                                        if (_t1273) {
                                                                            Str *_t1271 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t1271;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1254, &(Bool){1});
                                                                            ;
                                                                            return _t1271;
                                                                        } else {
                                                                            Str *_t1272 = Str_lit("?", 1ULL);
                                                                            (void)_t1272;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1254, &(Bool){1});
                                                                            ;
                                                                            return _t1272;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TilType_delete(_sw1254, &(Bool){1});
        ;
    }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t1291 = Bool_clone(&self->is_mut);
    (void)_t1291;
    Bool _t1292 = Bool_clone(&self->is_namespace);
    (void)_t1292;
    Bool _t1293 = Bool_clone(&self->is_ref);
    (void)_t1293;
    Bool _t1294 = Bool_clone(&self->is_own);
    (void)_t1294;
    I32 _t1295 = I32_clone(&self->field_offset);
    (void)_t1295;
    I32 _t1296 = I32_clone(&self->field_size);
    (void)_t1296;
    Declaration *_t1297 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t1297->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t1297->explicit_type = *_ca; free(_ca); }
    _t1297->is_mut = _t1291;
    _t1297->is_namespace = _t1292;
    _t1297->is_ref = _t1293;
    _t1297->is_own = _t1294;
    _t1297->field_offset = _t1295;
    _t1297->field_size = _t1296;
    _t1297->field_struct_def = self->field_struct_def;
    _t1297->fn_sig = self->fn_sig;
    (void)_t1297;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t1297;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1298 = 0;
    (void)_t1298;
    Str_delete(&self->name, &(Bool){_t1298});
    ;
    Bool _t1299 = 0;
    (void)_t1299;
    Str_delete(&self->explicit_type, &(Bool){_t1299});
    ;
    Bool _t1300 = 0;
    (void)_t1300;
    Bool_delete(&self->is_mut, &(Bool){_t1300});
    ;
    Bool _t1301 = 0;
    (void)_t1301;
    Bool_delete(&self->is_namespace, &(Bool){_t1301});
    ;
    Bool _t1302 = 0;
    (void)_t1302;
    Bool_delete(&self->is_ref, &(Bool){_t1302});
    ;
    Bool _t1303 = 0;
    (void)_t1303;
    Bool_delete(&self->is_own, &(Bool){_t1303});
    ;
    Bool _t1304 = 0;
    (void)_t1304;
    I32_delete(&self->field_offset, &(Bool){_t1304});
    ;
    Bool _t1305 = 0;
    (void)_t1305;
    I32_delete(&self->field_size, &(Bool){_t1305});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

Param * Param_clone(Param * self) {
    (void)self;
    Bool _t1339 = Bool_clone(&self->is_mut);
    (void)_t1339;
    Bool _t1340 = Bool_clone(&self->is_own);
    (void)_t1340;
    Bool _t1341 = Bool_clone(&self->is_shallow);
    (void)_t1341;
    Param *_t1342 = malloc(sizeof(Param));
    { Str *_ca = Str_clone(&self->name); _t1342->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->ptype); _t1342->ptype = *_ca; free(_ca); }
    _t1342->is_mut = _t1339;
    _t1342->is_own = _t1340;
    _t1342->is_shallow = _t1341;
    (void)_t1342;
    ;
    ;
    ;
    return _t1342;
}

void Param_delete(Param * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1343 = 0;
    (void)_t1343;
    Str_delete(&self->name, &(Bool){_t1343});
    ;
    Bool _t1344 = 0;
    (void)_t1344;
    Str_delete(&self->ptype, &(Bool){_t1344});
    ;
    Bool _t1345 = 0;
    (void)_t1345;
    Bool_delete(&self->is_mut, &(Bool){_t1345});
    ;
    Bool _t1346 = 0;
    (void)_t1346;
    Bool_delete(&self->is_own, &(Bool){_t1346});
    ;
    Bool _t1347 = 0;
    (void)_t1347;
    Bool_delete(&self->is_shallow, &(Bool){_t1347});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Param_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Param);
    return r;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    (void)self;
    U32 _t1350 = U32_clone(&self->nparam);
    (void)_t1350;
    I32 _t1351 = I32_clone(&self->variadic_index);
    (void)_t1351;
    I32 _t1352 = I32_clone(&self->kwargs_index);
    (void)_t1352;
    Bool _t1353 = Bool_clone(&self->return_is_ref);
    (void)_t1353;
    Bool _t1354 = Bool_clone(&self->return_is_shallow);
    (void)_t1354;
    FunctionDef *_t1355 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1355->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); _t1355->params = *_ca; free(_ca); }
    _t1355->nparam = _t1350;
    { Map *_ca = Map_clone(&self->param_defaults); _t1355->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1355->return_type = *_ca; free(_ca); }
    _t1355->variadic_index = _t1351;
    _t1355->kwargs_index = _t1352;
    _t1355->return_is_ref = _t1353;
    _t1355->return_is_shallow = _t1354;
    (void)_t1355;
    ;
    ;
    ;
    ;
    ;
    return _t1355;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1356 = 0;
    (void)_t1356;
    FuncType_delete(&self->func_type, &(Bool){_t1356});
    ;
    Bool _t1357 = 0;
    (void)_t1357;
    Vec_delete(&self->params, &(Bool){_t1357});
    ;
    Bool _t1358 = 0;
    (void)_t1358;
    U32_delete(&self->nparam, &(Bool){_t1358});
    ;
    Bool _t1359 = 0;
    (void)_t1359;
    Map_delete(&self->param_defaults, &(Bool){_t1359});
    ;
    Bool _t1360 = 0;
    (void)_t1360;
    Str_delete(&self->return_type, &(Bool){_t1360});
    ;
    Bool _t1361 = 0;
    (void)_t1361;
    I32_delete(&self->variadic_index, &(Bool){_t1361});
    ;
    Bool _t1362 = 0;
    (void)_t1362;
    I32_delete(&self->kwargs_index, &(Bool){_t1362});
    ;
    Bool _t1363 = 0;
    (void)_t1363;
    Bool_delete(&self->return_is_ref, &(Bool){_t1363});
    ;
    Bool _t1364 = 0;
    (void)_t1364;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1364});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *FunctionDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(FunctionDef);
    return r;
}

void Expr_delete(Expr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1743 = 0;
    (void)_t1743;
    ExprData_delete(&self->data, &(Bool){_t1743});
    ;
    Bool _t1744 = 0;
    (void)_t1744;
    TilType_delete(&self->til_type, &(Bool){_t1744});
    ;
    Bool _t1745 = 0;
    (void)_t1745;
    Str_delete(&self->struct_name, &(Bool){_t1745});
    ;
    Bool _t1746 = 0;
    (void)_t1746;
    Bool_delete(&self->is_own_arg, &(Bool){_t1746});
    ;
    Bool _t1747 = 0;
    (void)_t1747;
    Bool_delete(&self->is_splat, &(Bool){_t1747});
    ;
    Bool _t1748 = 0;
    (void)_t1748;
    Bool_delete(&self->is_own_field, &(Bool){_t1748});
    ;
    Bool _t1749 = 0;
    (void)_t1749;
    Bool_delete(&self->is_ref_field, &(Bool){_t1749});
    ;
    Bool _t1750 = 0;
    (void)_t1750;
    Bool_delete(&self->is_ns_field, &(Bool){_t1750});
    ;
    Bool _t1751 = 0;
    (void)_t1751;
    Bool_delete(&self->is_ext, &(Bool){_t1751});
    ;
    Bool _t1752 = 0;
    (void)_t1752;
    Bool_delete(&self->is_core, &(Bool){_t1752});
    ;
    Bool _t1753 = 0;
    (void)_t1753;
    Bool_delete(&self->save_old_delete, &(Bool){_t1753});
    ;
    Bool _t1754 = 0;
    (void)_t1754;
    I32_delete(&self->total_struct_size, &(Bool){_t1754});
    ;
    Bool _t1755 = 0;
    (void)_t1755;
    I32_delete(&self->variadic_index, &(Bool){_t1755});
    ;
    Bool _t1756 = 0;
    (void)_t1756;
    U32_delete(&self->variadic_count, &(Bool){_t1756});
    ;
    Bool _t1757 = 0;
    (void)_t1757;
    I32_delete(&self->kwargs_index, &(Bool){_t1757});
    ;
    Bool _t1758 = 0;
    (void)_t1758;
    U32_delete(&self->kwargs_count, &(Bool){_t1758});
    ;
    Bool _t1759 = 0;
    (void)_t1759;
    Vec_delete(&self->children, &(Bool){_t1759});
    ;
    Bool _t1760 = 0;
    (void)_t1760;
    U32_delete(&self->line, &(Bool){_t1760});
    ;
    Bool _t1761 = 0;
    (void)_t1761;
    U32_delete(&self->col, &(Bool){_t1761});
    ;
    Bool _t1762 = 0;
    (void)_t1762;
    Str_delete(&self->path, &(Bool){_t1762});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw1764 = ExprData_clone(data);
        (void)_sw1764;
        Bool _t1815; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Body()); _t1815 = *_hp; free(_hp); }
        (void)_t1815;
        if (_t1815) {
            Str *_t1765 = Str_lit("body", 4ULL);
            (void)_t1765;
            ExprData_delete(_sw1764, &(Bool){1});
            ;
            return _t1765;
        } else {
            Bool _t1814; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1764); _t1814 = *_hp; free(_hp); }
            (void)_t1814;
            if (_t1814) {
                Str *_t1766 = Str_lit("str", 3ULL);
                (void)_t1766;
                ;
                ExprData_delete(_sw1764, &(Bool){1});
                ;
                return _t1766;
            } else {
                Bool _t1813; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1764); _t1813 = *_hp; free(_hp); }
                (void)_t1813;
                if (_t1813) {
                    Str *_t1767 = Str_lit("num", 3ULL);
                    (void)_t1767;
                    ;
                    ;
                    ExprData_delete(_sw1764, &(Bool){1});
                    ;
                    return _t1767;
                } else {
                    Bool _t1812; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1764); _t1812 = *_hp; free(_hp); }
                    (void)_t1812;
                    if (_t1812) {
                        Str *_t1768 = Str_lit("bool", 4ULL);
                        (void)_t1768;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1764, &(Bool){1});
                        ;
                        return _t1768;
                    } else {
                        Bool _t1811; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_LiteralNull()); _t1811 = *_hp; free(_hp); }
                        (void)_t1811;
                        if (_t1811) {
                            Str *_t1769 = Str_lit("null", 4ULL);
                            (void)_t1769;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1764, &(Bool){1});
                            ;
                            return _t1769;
                        } else {
                            Bool _t1810; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1764); _t1810 = *_hp; free(_hp); }
                            (void)_t1810;
                            if (_t1810) {
                                Str *_t1770 = Str_lit("ident", 5ULL);
                                (void)_t1770;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1764, &(Bool){1});
                                ;
                                return _t1770;
                            } else {
                                Bool _t1809; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1764); _t1809 = *_hp; free(_hp); }
                                (void)_t1809;
                                if (_t1809) {
                                    Str *_t1771 = Str_lit("decl", 4ULL);
                                    (void)_t1771;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1764, &(Bool){1});
                                    ;
                                    return _t1771;
                                } else {
                                    Bool _t1808; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1764); _t1808 = *_hp; free(_hp); }
                                    (void)_t1808;
                                    if (_t1808) {
                                        Str *_t1772 = Str_lit("assign", 6ULL);
                                        (void)_t1772;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1764, &(Bool){1});
                                        ;
                                        return _t1772;
                                    } else {
                                        Bool _t1807; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_FCall()); _t1807 = *_hp; free(_hp); }
                                        (void)_t1807;
                                        if (_t1807) {
                                            Str *_t1773 = Str_lit("fcall", 5ULL);
                                            (void)_t1773;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1764, &(Bool){1});
                                            ;
                                            return _t1773;
                                        } else {
                                            Bool _t1806; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1764); _t1806 = *_hp; free(_hp); }
                                            (void)_t1806;
                                            if (_t1806) {
                                                Str *_t1774 = Str_lit("func_def", 8ULL);
                                                (void)_t1774;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1764, &(Bool){1});
                                                ;
                                                return _t1774;
                                            } else {
                                                Bool _t1805; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_StructDef()); _t1805 = *_hp; free(_hp); }
                                                (void)_t1805;
                                                if (_t1805) {
                                                    Str *_t1775 = Str_lit("struct_def", 10ULL);
                                                    (void)_t1775;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw1764, &(Bool){1});
                                                    ;
                                                    return _t1775;
                                                } else {
                                                    Bool _t1804; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_EnumDef()); _t1804 = *_hp; free(_hp); }
                                                    (void)_t1804;
                                                    if (_t1804) {
                                                        Str *_t1776 = Str_lit("enum_def", 8ULL);
                                                        (void)_t1776;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw1764, &(Bool){1});
                                                        ;
                                                        return _t1776;
                                                    } else {
                                                        Bool _t1803; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1764); _t1803 = *_hp; free(_hp); }
                                                        (void)_t1803;
                                                        if (_t1803) {
                                                            Str *_t1777 = Str_lit("field_access", 12ULL);
                                                            (void)_t1777;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw1764, &(Bool){1});
                                                            ;
                                                            return _t1777;
                                                        } else {
                                                            Bool _t1802; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1764); _t1802 = *_hp; free(_hp); }
                                                            (void)_t1802;
                                                            if (_t1802) {
                                                                Str *_t1778 = Str_lit("field_assign", 12ULL);
                                                                (void)_t1778;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw1764, &(Bool){1});
                                                                ;
                                                                return _t1778;
                                                            } else {
                                                                Bool _t1801; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Return()); _t1801 = *_hp; free(_hp); }
                                                                (void)_t1801;
                                                                if (_t1801) {
                                                                    Str *_t1779 = Str_lit("return", 6ULL);
                                                                    (void)_t1779;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw1764, &(Bool){1});
                                                                    ;
                                                                    return _t1779;
                                                                } else {
                                                                    Bool _t1800; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_If()); _t1800 = *_hp; free(_hp); }
                                                                    (void)_t1800;
                                                                    if (_t1800) {
                                                                        Str *_t1780 = Str_lit("if", 2ULL);
                                                                        (void)_t1780;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw1764, &(Bool){1});
                                                                        ;
                                                                        return _t1780;
                                                                    } else {
                                                                        Bool _t1799; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_While()); _t1799 = *_hp; free(_hp); }
                                                                        (void)_t1799;
                                                                        if (_t1799) {
                                                                            Str *_t1781 = Str_lit("while", 5ULL);
                                                                            (void)_t1781;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw1764, &(Bool){1});
                                                                            ;
                                                                            return _t1781;
                                                                        } else {
                                                                            Bool _t1798; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1764); _t1798 = *_hp; free(_hp); }
                                                                            (void)_t1798;
                                                                            if (_t1798) {
                                                                                Str *_t1782 = Str_lit("for_in", 6ULL);
                                                                                (void)_t1782;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw1764, &(Bool){1});
                                                                                ;
                                                                                return _t1782;
                                                                            } else {
                                                                                Bool _t1797; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1764); _t1797 = *_hp; free(_hp); }
                                                                                (void)_t1797;
                                                                                if (_t1797) {
                                                                                    Str *_t1783 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t1783;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw1764, &(Bool){1});
                                                                                    ;
                                                                                    return _t1783;
                                                                                } else {
                                                                                    Bool _t1796; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Break()); _t1796 = *_hp; free(_hp); }
                                                                                    (void)_t1796;
                                                                                    if (_t1796) {
                                                                                        Str *_t1784 = Str_lit("break", 5ULL);
                                                                                        (void)_t1784;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw1764, &(Bool){1});
                                                                                        ;
                                                                                        return _t1784;
                                                                                    } else {
                                                                                        Bool _t1795; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Continue()); _t1795 = *_hp; free(_hp); }
                                                                                        (void)_t1795;
                                                                                        if (_t1795) {
                                                                                            Str *_t1785 = Str_lit("continue", 8ULL);
                                                                                            (void)_t1785;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw1764, &(Bool){1});
                                                                                            ;
                                                                                            return _t1785;
                                                                                        } else {
                                                                                            Bool _t1794; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_MapLit()); _t1794 = *_hp; free(_hp); }
                                                                                            (void)_t1794;
                                                                                            if (_t1794) {
                                                                                                Str *_t1786 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t1786;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw1764, &(Bool){1});
                                                                                                ;
                                                                                                return _t1786;
                                                                                            } else {
                                                                                                Bool _t1793; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_SetLit()); _t1793 = *_hp; free(_hp); }
                                                                                                (void)_t1793;
                                                                                                if (_t1793) {
                                                                                                    Str *_t1787 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t1787;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw1764, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1787;
                                                                                                } else {
                                                                                                    Bool _t1792; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Switch()); _t1792 = *_hp; free(_hp); }
                                                                                                    (void)_t1792;
                                                                                                    if (_t1792) {
                                                                                                        Str *_t1788 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t1788;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw1764, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1788;
                                                                                                    } else {
                                                                                                        Bool _t1791; { Bool *_hp = (Bool *)ExprData_eq(_sw1764, ExprData_Case()); _t1791 = *_hp; free(_hp); }
                                                                                                        (void)_t1791;
                                                                                                        if (_t1791) {
                                                                                                            Str *_t1789 = Str_lit("case", 4ULL);
                                                                                                            (void)_t1789;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1764, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1789;
                                                                                                        } else {
                                                                                                            Str *_t1790 = Str_lit("?", 1ULL);
                                                                                                            (void)_t1790;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1764, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1790;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw1764, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1816 = FuncType_clone(ft);
        (void)_sw1816;
        Bool _t1829; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_Func()); _t1829 = *_hp; free(_hp); }
        (void)_t1829;
        if (_t1829) {
            Str *_t1817 = Str_lit("func", 4ULL);
            (void)_t1817;
            FuncType_delete(_sw1816, &(Bool){1});
            ;
            return _t1817;
        } else {
            Bool _t1828; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_Proc()); _t1828 = *_hp; free(_hp); }
            (void)_t1828;
            if (_t1828) {
                Str *_t1818 = Str_lit("proc", 4ULL);
                (void)_t1818;
                ;
                FuncType_delete(_sw1816, &(Bool){1});
                ;
                return _t1818;
            } else {
                Bool _t1827; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_Test()); _t1827 = *_hp; free(_hp); }
                (void)_t1827;
                if (_t1827) {
                    Str *_t1819 = Str_lit("test", 4ULL);
                    (void)_t1819;
                    ;
                    ;
                    FuncType_delete(_sw1816, &(Bool){1});
                    ;
                    return _t1819;
                } else {
                    Bool _t1826; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_Macro()); _t1826 = *_hp; free(_hp); }
                    (void)_t1826;
                    if (_t1826) {
                        Str *_t1820 = Str_lit("macro", 5ULL);
                        (void)_t1820;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1816, &(Bool){1});
                        ;
                        return _t1820;
                    } else {
                        Bool _t1825; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_ExtFunc()); _t1825 = *_hp; free(_hp); }
                        (void)_t1825;
                        if (_t1825) {
                            Str *_t1821 = Str_lit("ext_func", 8ULL);
                            (void)_t1821;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1816, &(Bool){1});
                            ;
                            return _t1821;
                        } else {
                            Bool _t1824; { Bool *_hp = (Bool *)FuncType_eq(_sw1816, FuncType_ExtProc()); _t1824 = *_hp; free(_hp); }
                            (void)_t1824;
                            if (_t1824) {
                                Str *_t1822 = Str_lit("ext_proc", 8ULL);
                                (void)_t1822;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1816, &(Bool){1});
                                ;
                                return _t1822;
                            } else {
                                Str *_t1823 = Str_lit("?", 1ULL);
                                (void)_t1823;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1816, &(Bool){1});
                                ;
                                return _t1823;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        FuncType_delete(_sw1816, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        I64 _t1840 = U32_to_i64(indent);
        (void)_t1840;
        U64 _t1841 = 0;
        (void)_t1841;
        U64 _t1842 = I64_to_u64(_t1840);
        (void)_t1842;
        ;
        Range *_fc1830 = Range_new(_t1841, _t1842);
        (void)_fc1830;
        ;
        ;
        U64 _fi1830 = 0;
        (void)_fi1830;
        while (1) {
            U64 _t1832; { U64 *_hp = (U64 *)Range_len(_fc1830); _t1832 = *_hp; free(_hp); }
            (void)_t1832;
            Bool _wcond1831; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1830}, &(U64){_t1832}); _wcond1831 = *_hp; free(_hp); }
            (void)_wcond1831;
            ;
            if (_wcond1831) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc1830, _fi1830); i = *_hp; free(_hp); }
            (void)i;
            ;
            U64 _t1833 = 1;
            (void)_t1833;
            U64 _t1834 = U64_add(_fi1830, _t1833);
            (void)_t1834;
            ;
            _fi1830 = _t1834;
            ;
            Str *_t1835 = Str_lit("Str", 3ULL);
            (void)_t1835;
            U64 _t1836; { U64 *_hp = (U64 *)Str_size(); _t1836 = *_hp; free(_hp); }
            (void)_t1836;
            U64 _t1837 = 1;
            (void)_t1837;
            Array *_va34 = Array_new(_t1835, &(U64){_t1836}, &(U64){_t1837});
            (void)_va34;
            Str_delete(_t1835, &(Bool){1});
            ;
            ;
            U64 _t1838 = 0;
            (void)_t1838;
            Str *_t1839 = Str_lit("  ", 2ULL);
            (void)_t1839;
            Array_set(_va34, &(U64){_t1838}, _t1839);
            ;
            print(_va34);
        }
        Range_delete(_fc1830, &(Bool){1});
        ;
    }
    Str *_t1967 = Str_lit("Str", 3ULL);
    (void)_t1967;
    U64 _t1968; { U64 *_hp = (U64 *)Str_size(); _t1968 = *_hp; free(_hp); }
    (void)_t1968;
    U64 _t1969 = 2;
    (void)_t1969;
    Array *_va48 = Array_new(_t1967, &(U64){_t1968}, &(U64){_t1969});
    (void)_va48;
    Str_delete(_t1967, &(Bool){1});
    ;
    ;
    U64 _t1970 = 0;
    (void)_t1970;
    Str *_t1971 = Str_lit("(", 1ULL);
    (void)_t1971;
    Array_set(_va48, &(U64){_t1970}, _t1971);
    ;
    U64 _t1972 = 1;
    (void)_t1972;
    Str *_t1973 = node_name(&e->data);
    (void)_t1973;
    Array_set(_va48, &(U64){_t1972}, _t1973);
    ;
    print(_va48);
    Bool _t1974; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t1974 = *_hp; free(_hp); }
    (void)_t1974;
    Bool _t1975 = Bool_not(_t1974);
    (void)_t1975;
    ;
    if (_t1975) {
        Str *_t1843 = Str_lit("Str", 3ULL);
        (void)_t1843;
        U64 _t1844; { U64 *_hp = (U64 *)Str_size(); _t1844 = *_hp; free(_hp); }
        (void)_t1844;
        U64 _t1845 = 2;
        (void)_t1845;
        Array *_va35 = Array_new(_t1843, &(U64){_t1844}, &(U64){_t1845});
        (void)_va35;
        Str_delete(_t1843, &(Bool){1});
        ;
        ;
        U64 _t1846 = 0;
        (void)_t1846;
        Str *_t1847 = Str_lit(":", 1ULL);
        (void)_t1847;
        Array_set(_va35, &(U64){_t1846}, _t1847);
        ;
        U64 _t1848 = 1;
        (void)_t1848;
        Str *_t1849 = til_type_name_c(&e->til_type);
        (void)_t1849;
        Array_set(_va35, &(U64){_t1848}, _t1849);
        ;
        print(_va35);
    }
    ;
    {
        ExprData *_sw1850 = ExprData_clone(&e->data);
        (void)_sw1850;
        Bool _t1937; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1850); _t1937 = *_hp; free(_hp); }
        (void)_t1937;
        if (_t1937) {
            Str *s = ExprData_get_Ident(_sw1850);
            (void)s;
            Str *_t1851 = Str_lit("Str", 3ULL);
            (void)_t1851;
            U64 _t1852; { U64 *_hp = (U64 *)Str_size(); _t1852 = *_hp; free(_hp); }
            (void)_t1852;
            U64 _t1853 = 3;
            (void)_t1853;
            Array *_va36 = Array_new(_t1851, &(U64){_t1852}, &(U64){_t1853});
            (void)_va36;
            Str_delete(_t1851, &(Bool){1});
            ;
            ;
            U64 _t1854 = 0;
            (void)_t1854;
            Str *_t1855 = Str_lit(" \"", 3ULL);
            (void)_t1855;
            Array_set(_va36, &(U64){_t1854}, _t1855);
            ;
            U64 _t1856 = 1;
            (void)_t1856;
            Str *_t1857 = Str_clone(s);
            (void)_t1857;
            Str_delete(s, &(Bool){1});
            Array_set(_va36, &(U64){_t1856}, _t1857);
            ;
            U64 _t1858 = 2;
            (void)_t1858;
            Str *_t1859 = Str_lit("\"", 2ULL);
            (void)_t1859;
            Array_set(_va36, &(U64){_t1858}, _t1859);
            ;
            print(_va36);
        } else {
            Bool _t1936; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1850); _t1936 = *_hp; free(_hp); }
            (void)_t1936;
            if (_t1936) {
                Str *s = ExprData_get_LiteralStr(_sw1850);
                (void)s;
                Str *_t1860 = Str_lit("Str", 3ULL);
                (void)_t1860;
                U64 _t1861; { U64 *_hp = (U64 *)Str_size(); _t1861 = *_hp; free(_hp); }
                (void)_t1861;
                U64 _t1862 = 3;
                (void)_t1862;
                Array *_va37 = Array_new(_t1860, &(U64){_t1861}, &(U64){_t1862});
                (void)_va37;
                Str_delete(_t1860, &(Bool){1});
                ;
                ;
                U64 _t1863 = 0;
                (void)_t1863;
                Str *_t1864 = Str_lit(" \"", 3ULL);
                (void)_t1864;
                Array_set(_va37, &(U64){_t1863}, _t1864);
                ;
                U64 _t1865 = 1;
                (void)_t1865;
                Str *_t1866 = Str_clone(s);
                (void)_t1866;
                Str_delete(s, &(Bool){1});
                Array_set(_va37, &(U64){_t1865}, _t1866);
                ;
                U64 _t1867 = 2;
                (void)_t1867;
                Str *_t1868 = Str_lit("\"", 2ULL);
                (void)_t1868;
                Array_set(_va37, &(U64){_t1867}, _t1868);
                ;
                print(_va37);
            } else {
                Bool _t1935; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1850); _t1935 = *_hp; free(_hp); }
                (void)_t1935;
                if (_t1935) {
                    Str *s = ExprData_get_LiteralNum(_sw1850);
                    (void)s;
                    Str *_t1869 = Str_lit("Str", 3ULL);
                    (void)_t1869;
                    U64 _t1870; { U64 *_hp = (U64 *)Str_size(); _t1870 = *_hp; free(_hp); }
                    (void)_t1870;
                    U64 _t1871 = 3;
                    (void)_t1871;
                    Array *_va38 = Array_new(_t1869, &(U64){_t1870}, &(U64){_t1871});
                    (void)_va38;
                    Str_delete(_t1869, &(Bool){1});
                    ;
                    ;
                    U64 _t1872 = 0;
                    (void)_t1872;
                    Str *_t1873 = Str_lit(" \"", 3ULL);
                    (void)_t1873;
                    Array_set(_va38, &(U64){_t1872}, _t1873);
                    ;
                    U64 _t1874 = 1;
                    (void)_t1874;
                    Str *_t1875 = Str_clone(s);
                    (void)_t1875;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va38, &(U64){_t1874}, _t1875);
                    ;
                    U64 _t1876 = 2;
                    (void)_t1876;
                    Str *_t1877 = Str_lit("\"", 2ULL);
                    (void)_t1877;
                    Array_set(_va38, &(U64){_t1876}, _t1877);
                    ;
                    print(_va38);
                } else {
                    Bool _t1934; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1850); _t1934 = *_hp; free(_hp); }
                    (void)_t1934;
                    if (_t1934) {
                        Str *s = ExprData_get_LiteralBool(_sw1850);
                        (void)s;
                        Str *_t1878 = Str_lit("Str", 3ULL);
                        (void)_t1878;
                        U64 _t1879; { U64 *_hp = (U64 *)Str_size(); _t1879 = *_hp; free(_hp); }
                        (void)_t1879;
                        U64 _t1880 = 3;
                        (void)_t1880;
                        Array *_va39 = Array_new(_t1878, &(U64){_t1879}, &(U64){_t1880});
                        (void)_va39;
                        Str_delete(_t1878, &(Bool){1});
                        ;
                        ;
                        U64 _t1881 = 0;
                        (void)_t1881;
                        Str *_t1882 = Str_lit(" \"", 3ULL);
                        (void)_t1882;
                        Array_set(_va39, &(U64){_t1881}, _t1882);
                        ;
                        U64 _t1883 = 1;
                        (void)_t1883;
                        Str *_t1884 = Str_clone(s);
                        (void)_t1884;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va39, &(U64){_t1883}, _t1884);
                        ;
                        U64 _t1885 = 2;
                        (void)_t1885;
                        Str *_t1886 = Str_lit("\"", 2ULL);
                        (void)_t1886;
                        Array_set(_va39, &(U64){_t1885}, _t1886);
                        ;
                        print(_va39);
                    } else {
                        Bool _t1933; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1850); _t1933 = *_hp; free(_hp); }
                        (void)_t1933;
                        if (_t1933) {
                            Str *s = ExprData_get_ForIn(_sw1850);
                            (void)s;
                            Str *_t1887 = Str_lit("Str", 3ULL);
                            (void)_t1887;
                            U64 _t1888; { U64 *_hp = (U64 *)Str_size(); _t1888 = *_hp; free(_hp); }
                            (void)_t1888;
                            U64 _t1889 = 3;
                            (void)_t1889;
                            Array *_va40 = Array_new(_t1887, &(U64){_t1888}, &(U64){_t1889});
                            (void)_va40;
                            Str_delete(_t1887, &(Bool){1});
                            ;
                            ;
                            U64 _t1890 = 0;
                            (void)_t1890;
                            Str *_t1891 = Str_lit(" \"", 3ULL);
                            (void)_t1891;
                            Array_set(_va40, &(U64){_t1890}, _t1891);
                            ;
                            U64 _t1892 = 1;
                            (void)_t1892;
                            Str *_t1893 = Str_clone(s);
                            (void)_t1893;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va40, &(U64){_t1892}, _t1893);
                            ;
                            U64 _t1894 = 2;
                            (void)_t1894;
                            Str *_t1895 = Str_lit("\"", 2ULL);
                            (void)_t1895;
                            Array_set(_va40, &(U64){_t1894}, _t1895);
                            ;
                            print(_va40);
                        } else {
                            Bool _t1932; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1850); _t1932 = *_hp; free(_hp); }
                            (void)_t1932;
                            if (_t1932) {
                                Declaration *decl = ExprData_get_Decl(_sw1850);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1896 = Str_lit("Str", 3ULL);
                                    (void)_t1896;
                                    U64 _t1897; { U64 *_hp = (U64 *)Str_size(); _t1897 = *_hp; free(_hp); }
                                    (void)_t1897;
                                    U64 _t1898 = 1;
                                    (void)_t1898;
                                    Array *_va41 = Array_new(_t1896, &(U64){_t1897}, &(U64){_t1898});
                                    (void)_va41;
                                    Str_delete(_t1896, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1899 = 0;
                                    (void)_t1899;
                                    Str *_t1900 = Str_lit(" mut", 4ULL);
                                    (void)_t1900;
                                    Array_set(_va41, &(U64){_t1899}, _t1900);
                                    ;
                                    print(_va41);
                                }
                                Str *_t1901 = Str_lit("Str", 3ULL);
                                (void)_t1901;
                                U64 _t1902; { U64 *_hp = (U64 *)Str_size(); _t1902 = *_hp; free(_hp); }
                                (void)_t1902;
                                U64 _t1903 = 2;
                                (void)_t1903;
                                Array *_va42 = Array_new(_t1901, &(U64){_t1902}, &(U64){_t1903});
                                (void)_va42;
                                Str_delete(_t1901, &(Bool){1});
                                ;
                                ;
                                U64 _t1904 = 0;
                                (void)_t1904;
                                Str *_t1905 = Str_lit(" ", 1ULL);
                                (void)_t1905;
                                Array_set(_va42, &(U64){_t1904}, _t1905);
                                ;
                                U64 _t1906 = 1;
                                (void)_t1906;
                                Str *_t1907 = Str_clone(&decl->name);
                                (void)_t1907;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va42, &(U64){_t1906}, _t1907);
                                ;
                                print(_va42);
                            } else {
                                Bool _t1931; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1850); _t1931 = *_hp; free(_hp); }
                                (void)_t1931;
                                if (_t1931) {
                                    Str *s = ExprData_get_Assign(_sw1850);
                                    (void)s;
                                    Str *_t1908 = Str_lit("Str", 3ULL);
                                    (void)_t1908;
                                    U64 _t1909; { U64 *_hp = (U64 *)Str_size(); _t1909 = *_hp; free(_hp); }
                                    (void)_t1909;
                                    U64 _t1910 = 2;
                                    (void)_t1910;
                                    Array *_va43 = Array_new(_t1908, &(U64){_t1909}, &(U64){_t1910});
                                    (void)_va43;
                                    Str_delete(_t1908, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1911 = 0;
                                    (void)_t1911;
                                    Str *_t1912 = Str_lit(" ", 1ULL);
                                    (void)_t1912;
                                    Array_set(_va43, &(U64){_t1911}, _t1912);
                                    ;
                                    U64 _t1913 = 1;
                                    (void)_t1913;
                                    Str *_t1914 = Str_clone(s);
                                    (void)_t1914;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va43, &(U64){_t1913}, _t1914);
                                    ;
                                    print(_va43);
                                } else {
                                    Bool _t1930; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1850); _t1930 = *_hp; free(_hp); }
                                    (void)_t1930;
                                    if (_t1930) {
                                        Str *s = ExprData_get_NamedArg(_sw1850);
                                        (void)s;
                                        Str *_t1915 = Str_lit("Str", 3ULL);
                                        (void)_t1915;
                                        U64 _t1916; { U64 *_hp = (U64 *)Str_size(); _t1916 = *_hp; free(_hp); }
                                        (void)_t1916;
                                        U64 _t1917 = 2;
                                        (void)_t1917;
                                        Array *_va44 = Array_new(_t1915, &(U64){_t1916}, &(U64){_t1917});
                                        (void)_va44;
                                        Str_delete(_t1915, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1918 = 0;
                                        (void)_t1918;
                                        Str *_t1919 = Str_lit(" ", 1ULL);
                                        (void)_t1919;
                                        Array_set(_va44, &(U64){_t1918}, _t1919);
                                        ;
                                        U64 _t1920 = 1;
                                        (void)_t1920;
                                        Str *_t1921 = Str_clone(s);
                                        (void)_t1921;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va44, &(U64){_t1920}, _t1921);
                                        ;
                                        print(_va44);
                                    } else {
                                        Bool _t1929; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1850); _t1929 = *_hp; free(_hp); }
                                        (void)_t1929;
                                        if (_t1929) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1850);
                                            (void)fdef;
                                            Str *_t1922 = Str_lit("Str", 3ULL);
                                            (void)_t1922;
                                            U64 _t1923; { U64 *_hp = (U64 *)Str_size(); _t1923 = *_hp; free(_hp); }
                                            (void)_t1923;
                                            U64 _t1924 = 2;
                                            (void)_t1924;
                                            Array *_va45 = Array_new(_t1922, &(U64){_t1923}, &(U64){_t1924});
                                            (void)_va45;
                                            Str_delete(_t1922, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1925 = 0;
                                            (void)_t1925;
                                            Str *_t1926 = Str_lit(" ", 1ULL);
                                            (void)_t1926;
                                            Array_set(_va45, &(U64){_t1925}, _t1926);
                                            ;
                                            U64 _t1927 = 1;
                                            (void)_t1927;
                                            Str *_t1928 = func_type_name(&fdef->func_type);
                                            (void)_t1928;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va45, &(U64){_t1927}, _t1928);
                                            ;
                                            print(_va45);
                                        } else {
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw1850, &(Bool){1});
        ;
    }
    U64 _t1976; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1976 = *_hp; free(_hp); }
    (void)_t1976;
    U64 _t1977 = 0;
    (void)_t1977;
    Bool _t1978; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1976}, &(U64){_t1977}); _t1978 = *_hp; free(_hp); }
    (void)_t1978;
    ;
    ;
    if (_t1978) {
        Str *_t1962 = Str_lit("Str", 3ULL);
        (void)_t1962;
        U64 _t1963; { U64 *_hp = (U64 *)Str_size(); _t1963 = *_hp; free(_hp); }
        (void)_t1963;
        U64 _t1964 = 1;
        (void)_t1964;
        Array *_va47 = Array_new(_t1962, &(U64){_t1963}, &(U64){_t1964});
        (void)_va47;
        Str_delete(_t1962, &(Bool){1});
        ;
        ;
        U64 _t1965 = 0;
        (void)_t1965;
        Str *_t1966 = Str_lit("", 0ULL);
        (void)_t1966;
        Array_set(_va47, &(U64){_t1965}, _t1966);
        ;
        println(_va47);
        {
            U64 _t1947 = 0;
            (void)_t1947;
            U64 _t1948; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1948 = *_hp; free(_hp); }
            (void)_t1948;
            Range *_fc1938 = Range_new(_t1947, _t1948);
            (void)_fc1938;
            ;
            ;
            U64 _fi1938 = 0;
            (void)_fi1938;
            while (1) {
                U64 _t1940; { U64 *_hp = (U64 *)Range_len(_fc1938); _t1940 = *_hp; free(_hp); }
                (void)_t1940;
                Bool _wcond1939; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1938}, &(U64){_t1940}); _wcond1939 = *_hp; free(_hp); }
                (void)_wcond1939;
                ;
                if (_wcond1939) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1938, _fi1938); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1941 = 1;
                (void)_t1941;
                U64 _t1942 = U64_add(_fi1938, _t1941);
                (void)_t1942;
                ;
                _fi1938 = _t1942;
                ;
                I64 *_t1943 = malloc(sizeof(I64)); *_t1943 = U64_to_i64(i);
                (void)_t1943;
                ;
                U32 _t1944 = 1;
                (void)_t1944;
                Expr *_t1945 = Expr_child(e, _t1943);
                (void)_t1945;
                U32 _t1946 = U32_add(indent, _t1944);
                (void)_t1946;
                ;
                ast_print(_t1945, _t1946);
                I64_delete(_t1943, &(Bool){1});
                ;
            }
            Range_delete(_fc1938, &(Bool){1});
            ;
        }
        {
            I64 _t1959 = U32_to_i64(indent);
            (void)_t1959;
            U64 _t1960 = 0;
            (void)_t1960;
            U64 _t1961 = I64_to_u64(_t1959);
            (void)_t1961;
            ;
            Range *_fc1949 = Range_new(_t1960, _t1961);
            (void)_fc1949;
            ;
            ;
            U64 _fi1949 = 0;
            (void)_fi1949;
            while (1) {
                U64 _t1951; { U64 *_hp = (U64 *)Range_len(_fc1949); _t1951 = *_hp; free(_hp); }
                (void)_t1951;
                Bool _wcond1950; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1949}, &(U64){_t1951}); _wcond1950 = *_hp; free(_hp); }
                (void)_wcond1950;
                ;
                if (_wcond1950) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1949, _fi1949); i = *_hp; free(_hp); }
                (void)i;
                ;
                U64 _t1952 = 1;
                (void)_t1952;
                U64 _t1953 = U64_add(_fi1949, _t1952);
                (void)_t1953;
                ;
                _fi1949 = _t1953;
                ;
                Str *_t1954 = Str_lit("Str", 3ULL);
                (void)_t1954;
                U64 _t1955; { U64 *_hp = (U64 *)Str_size(); _t1955 = *_hp; free(_hp); }
                (void)_t1955;
                U64 _t1956 = 1;
                (void)_t1956;
                Array *_va46 = Array_new(_t1954, &(U64){_t1955}, &(U64){_t1956});
                (void)_va46;
                Str_delete(_t1954, &(Bool){1});
                ;
                ;
                U64 _t1957 = 0;
                (void)_t1957;
                Str *_t1958 = Str_lit("  ", 2ULL);
                (void)_t1958;
                Array_set(_va46, &(U64){_t1957}, _t1958);
                ;
                print(_va46);
            }
            Range_delete(_fc1949, &(Bool){1});
            ;
        }
    }
    ;
    Str *_t1979 = Str_lit("Str", 3ULL);
    (void)_t1979;
    U64 _t1980; { U64 *_hp = (U64 *)Str_size(); _t1980 = *_hp; free(_hp); }
    (void)_t1980;
    U64 _t1981 = 1;
    (void)_t1981;
    Array *_va49 = Array_new(_t1979, &(U64){_t1980}, &(U64){_t1981});
    (void)_va49;
    Str_delete(_t1979, &(Bool){1});
    ;
    ;
    U64 _t1982 = 0;
    (void)_t1982;
    Str *_t1983 = Str_lit(")", 1ULL);
    (void)_t1983;
    Array_set(_va49, &(U64){_t1982}, _t1983);
    ;
    println(_va49);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2000 = malloc(sizeof(I64));
    *_t2000 = 0;
    (void)_t2000;
    Expr *body = Expr_child(enum_def, _t2000);
    (void)body;
    {
        I64 _t1997; { I64 *_hp = (I64 *)Expr_child_count(body); _t1997 = *_hp; free(_hp); }
        (void)_t1997;
        U64 _t1998 = 0;
        (void)_t1998;
        U64 _t1999 = I64_to_u64(_t1997);
        (void)_t1999;
        ;
        Range *_fc1984 = Range_new(_t1998, _t1999);
        (void)_fc1984;
        ;
        ;
        U64 _fi1984 = 0;
        (void)_fi1984;
        while (1) {
            U64 _t1992; { U64 *_hp = (U64 *)Range_len(_fc1984); _t1992 = *_hp; free(_hp); }
            (void)_t1992;
            Bool _wcond1985; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1984}, &(U64){_t1992}); _wcond1985 = *_hp; free(_hp); }
            (void)_wcond1985;
            ;
            if (_wcond1985) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc1984, _fi1984); i = *_hp; free(_hp); }
            (void)i;
            U64 _t1993 = 1;
            (void)_t1993;
            U64 _t1994 = U64_add(_fi1984, _t1993);
            (void)_t1994;
            ;
            _fi1984 = _t1994;
            ;
            I64 *_t1995 = malloc(sizeof(I64)); *_t1995 = U64_to_i64(i);
            (void)_t1995;
            ;
            Expr *f = Expr_child(body, _t1995);
            (void)f;
            Bool _t1996; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t1996 = *_hp; free(_hp); }
            (void)_t1996;
            if (_t1996) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t1987; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t1987 = *_hp; free(_hp); }
                (void)_t1987;
                U64 _t1988 = 0;
                (void)_t1988;
                Bool _t1989 = Bool_not(decl->is_namespace);
                (void)_t1989;
                Declaration_delete(decl, &(Bool){1});
                Bool _t1990; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1987}, &(U64){_t1988}); _t1990 = *_hp; free(_hp); }
                (void)_t1990;
                ;
                ;
                Bool _t1991 = Bool_and(_t1989, _t1990);
                (void)_t1991;
                ;
                ;
                if (_t1991) {
                    Bool _t1986 = 1;
                    (void)_t1986;
                    ;
                    I64_delete(_t1995, &(Bool){1});
                    ;
                    Range_delete(_fc1984, &(Bool){1});
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1986; return _r; }
                }
                ;
            }
            I64_delete(_t1995, &(Bool){1});
            ;
        }
        Range_delete(_fc1984, &(Bool){1});
        ;
    }
    I64_delete(_t2000, &(Bool){1});
    Bool _t2001 = 0;
    (void)_t2001;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2001; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2016 = malloc(sizeof(I64));
    *_t2016 = 0;
    (void)_t2016;
    Expr *body = Expr_child(enum_def, _t2016);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        I64 _t2013; { I64 *_hp = (I64 *)Expr_child_count(body); _t2013 = *_hp; free(_hp); }
        (void)_t2013;
        U64 _t2014 = 0;
        (void)_t2014;
        U64 _t2015 = I64_to_u64(_t2013);
        (void)_t2015;
        ;
        Range *_fc2002 = Range_new(_t2014, _t2015);
        (void)_fc2002;
        ;
        ;
        U64 _fi2002 = 0;
        (void)_fi2002;
        while (1) {
            U64 _t2008; { U64 *_hp = (U64 *)Range_len(_fc2002); _t2008 = *_hp; free(_hp); }
            (void)_t2008;
            Bool _wcond2003; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2002}, &(U64){_t2008}); _wcond2003 = *_hp; free(_hp); }
            (void)_wcond2003;
            ;
            if (_wcond2003) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2002, _fi2002); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2009 = 1;
            (void)_t2009;
            U64 _t2010 = U64_add(_fi2002, _t2009);
            (void)_t2010;
            ;
            _fi2002 = _t2010;
            ;
            I64 *_t2011 = malloc(sizeof(I64)); *_t2011 = U64_to_i64(i);
            (void)_t2011;
            ;
            Expr *f = Expr_child(body, _t2011);
            (void)f;
            Bool _t2012; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2012 = *_hp; free(_hp); }
            (void)_t2012;
            if (_t2012) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2007 = Bool_not(decl->is_namespace);
                (void)_t2007;
                if (_t2007) {
                    Bool _t2004; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2004 = *_hp; free(_hp); }
                    (void)_t2004;
                    if (_t2004) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2011, &(Bool){1});
                        ;
                        Range_delete(_fc2002, &(Bool){1});
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2005 = 1;
                    (void)_t2005;
                    I32 _t2006 = I32_add(tag, _t2005);
                    (void)_t2006;
                    ;
                    tag = _t2006;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2011, &(Bool){1});
            ;
        }
        Range_delete(_fc2002, &(Bool){1});
        ;
    }
    I64_delete(_t2016, &(Bool){1});
    ;
    I64 _t2017 = 0;
    (void)_t2017;
    I64 _t2018 = 1;
    (void)_t2018;
    I64 _t2019 = I64_sub(_t2017, _t2018);
    (void)_t2019;
    ;
    ;
    I32 _t2020 = I64_to_i32(_t2019);
    (void)_t2020;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2020; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2035 = malloc(sizeof(I64));
    *_t2035 = 0;
    (void)_t2035;
    Expr *body = Expr_child(enum_def, _t2035);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        I64 _t2032; { I64 *_hp = (I64 *)Expr_child_count(body); _t2032 = *_hp; free(_hp); }
        (void)_t2032;
        U64 _t2033 = 0;
        (void)_t2033;
        U64 _t2034 = I64_to_u64(_t2032);
        (void)_t2034;
        ;
        Range *_fc2021 = Range_new(_t2033, _t2034);
        (void)_fc2021;
        ;
        ;
        U64 _fi2021 = 0;
        (void)_fi2021;
        while (1) {
            U64 _t2027; { U64 *_hp = (U64 *)Range_len(_fc2021); _t2027 = *_hp; free(_hp); }
            (void)_t2027;
            Bool _wcond2022; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2021}, &(U64){_t2027}); _wcond2022 = *_hp; free(_hp); }
            (void)_wcond2022;
            ;
            if (_wcond2022) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2021, _fi2021); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2028 = 1;
            (void)_t2028;
            U64 _t2029 = U64_add(_fi2021, _t2028);
            (void)_t2029;
            ;
            _fi2021 = _t2029;
            ;
            I64 *_t2030 = malloc(sizeof(I64)); *_t2030 = U64_to_i64(i);
            (void)_t2030;
            ;
            Expr *f = Expr_child(body, _t2030);
            (void)f;
            Bool _t2031; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2031 = *_hp; free(_hp); }
            (void)_t2031;
            if (_t2031) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2026 = Bool_not(decl->is_namespace);
                (void)_t2026;
                if (_t2026) {
                    Bool _t2023 = I32_eq(idx, tag);
                    (void)_t2023;
                    if (_t2023) {
                        ;
                        ;
                        I64_delete(_t2030, &(Bool){1});
                        ;
                        Range_delete(_fc2021, &(Bool){1});
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2024 = 1;
                    (void)_t2024;
                    I32 _t2025 = I32_add(idx, _t2024);
                    (void)_t2025;
                    ;
                    idx = _t2025;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2030, &(Bool){1});
            ;
        }
        Range_delete(_fc2021, &(Bool){1});
        ;
    }
    I64_delete(_t2035, &(Bool){1});
    ;
    Str *_t2036 = Str_lit("", 0ULL);
    (void)_t2036;
    return _t2036;
}

