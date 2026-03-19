#include "modes_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw1299 = TilType_clone(t);
        (void)_sw1299;
        Bool _t1334; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_Unknown()); _t1334 = *_hp; free(_hp); }
        (void)_t1334;
        if (_t1334) {
            Str *_t1300 = Str_lit("unknown", 7ULL);
            (void)_t1300;
            TilType_delete(_sw1299, &(Bool){1});
            ;
            return _t1300;
        } else {
            Bool _t1333; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_None()); _t1333 = *_hp; free(_hp); }
            (void)_t1333;
            if (_t1333) {
                Str *_t1301 = Str_lit("None", 4ULL);
                (void)_t1301;
                ;
                TilType_delete(_sw1299, &(Bool){1});
                ;
                return _t1301;
            } else {
                Bool _t1332; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_I64()); _t1332 = *_hp; free(_hp); }
                (void)_t1332;
                if (_t1332) {
                    Str *_t1302 = Str_lit("I64", 3ULL);
                    (void)_t1302;
                    ;
                    ;
                    TilType_delete(_sw1299, &(Bool){1});
                    ;
                    return _t1302;
                } else {
                    Bool _t1331; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_U8()); _t1331 = *_hp; free(_hp); }
                    (void)_t1331;
                    if (_t1331) {
                        Str *_t1303 = Str_lit("U8", 2ULL);
                        (void)_t1303;
                        ;
                        ;
                        ;
                        TilType_delete(_sw1299, &(Bool){1});
                        ;
                        return _t1303;
                    } else {
                        Bool _t1330; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_I16()); _t1330 = *_hp; free(_hp); }
                        (void)_t1330;
                        if (_t1330) {
                            Str *_t1304 = Str_lit("I16", 3ULL);
                            (void)_t1304;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw1299, &(Bool){1});
                            ;
                            return _t1304;
                        } else {
                            Bool _t1329; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_I32()); _t1329 = *_hp; free(_hp); }
                            (void)_t1329;
                            if (_t1329) {
                                Str *_t1305 = Str_lit("I32", 3ULL);
                                (void)_t1305;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw1299, &(Bool){1});
                                ;
                                return _t1305;
                            } else {
                                Bool _t1328; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_U32()); _t1328 = *_hp; free(_hp); }
                                (void)_t1328;
                                if (_t1328) {
                                    Str *_t1306 = Str_lit("U32", 3ULL);
                                    (void)_t1306;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw1299, &(Bool){1});
                                    ;
                                    return _t1306;
                                } else {
                                    Bool _t1327; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_U64()); _t1327 = *_hp; free(_hp); }
                                    (void)_t1327;
                                    if (_t1327) {
                                        Str *_t1307 = Str_lit("U64", 3ULL);
                                        (void)_t1307;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw1299, &(Bool){1});
                                        ;
                                        return _t1307;
                                    } else {
                                        Bool _t1326; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_F32()); _t1326 = *_hp; free(_hp); }
                                        (void)_t1326;
                                        if (_t1326) {
                                            Str *_t1308 = Str_lit("F32", 3ULL);
                                            (void)_t1308;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw1299, &(Bool){1});
                                            ;
                                            return _t1308;
                                        } else {
                                            Bool _t1325; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_Bool()); _t1325 = *_hp; free(_hp); }
                                            (void)_t1325;
                                            if (_t1325) {
                                                Str *_t1309 = Str_lit("Bool", 4ULL);
                                                (void)_t1309;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw1299, &(Bool){1});
                                                ;
                                                return _t1309;
                                            } else {
                                                Bool _t1324; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_Struct()); _t1324 = *_hp; free(_hp); }
                                                (void)_t1324;
                                                if (_t1324) {
                                                    Str *_t1310 = Str_lit("Struct", 6ULL);
                                                    (void)_t1310;
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
                                                    TilType_delete(_sw1299, &(Bool){1});
                                                    ;
                                                    return _t1310;
                                                } else {
                                                    Bool _t1323; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_StructDef()); _t1323 = *_hp; free(_hp); }
                                                    (void)_t1323;
                                                    if (_t1323) {
                                                        Str *_t1311 = Str_lit("StructDef", 9ULL);
                                                        (void)_t1311;
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
                                                        TilType_delete(_sw1299, &(Bool){1});
                                                        ;
                                                        return _t1311;
                                                    } else {
                                                        Bool _t1322; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_Enum()); _t1322 = *_hp; free(_hp); }
                                                        (void)_t1322;
                                                        if (_t1322) {
                                                            Str *_t1312 = Str_lit("Enum", 4ULL);
                                                            (void)_t1312;
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
                                                            TilType_delete(_sw1299, &(Bool){1});
                                                            ;
                                                            return _t1312;
                                                        } else {
                                                            Bool _t1321; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_EnumDef()); _t1321 = *_hp; free(_hp); }
                                                            (void)_t1321;
                                                            if (_t1321) {
                                                                Str *_t1313 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t1313;
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
                                                                TilType_delete(_sw1299, &(Bool){1});
                                                                ;
                                                                return _t1313;
                                                            } else {
                                                                Bool _t1320; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_FuncDef()); _t1320 = *_hp; free(_hp); }
                                                                (void)_t1320;
                                                                if (_t1320) {
                                                                    Str *_t1314 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t1314;
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
                                                                    TilType_delete(_sw1299, &(Bool){1});
                                                                    ;
                                                                    return _t1314;
                                                                } else {
                                                                    Bool _t1319; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_FuncPtr()); _t1319 = *_hp; free(_hp); }
                                                                    (void)_t1319;
                                                                    if (_t1319) {
                                                                        Str *_t1315 = Str_lit("Fn", 2ULL);
                                                                        (void)_t1315;
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
                                                                        TilType_delete(_sw1299, &(Bool){1});
                                                                        ;
                                                                        return _t1315;
                                                                    } else {
                                                                        Bool _t1318; { Bool *_hp = (Bool *)TilType_eq(_sw1299, TilType_Dynamic()); _t1318 = *_hp; free(_hp); }
                                                                        (void)_t1318;
                                                                        if (_t1318) {
                                                                            Str *_t1316 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t1316;
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
                                                                            TilType_delete(_sw1299, &(Bool){1});
                                                                            ;
                                                                            return _t1316;
                                                                        } else {
                                                                            Str *_t1317 = Str_lit("?", 1ULL);
                                                                            (void)_t1317;
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
                                                                            TilType_delete(_sw1299, &(Bool){1});
                                                                            ;
                                                                            return _t1317;
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
        TilType_delete(_sw1299, &(Bool){1});
        ;
    }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t1336 = Bool_clone(&self->is_mut);
    (void)_t1336;
    Bool _t1337 = Bool_clone(&self->is_namespace);
    (void)_t1337;
    Bool _t1338 = Bool_clone(&self->is_ref);
    (void)_t1338;
    Bool _t1339 = Bool_clone(&self->is_own);
    (void)_t1339;
    I32 _t1340 = I32_clone(&self->field_offset);
    (void)_t1340;
    I32 _t1341 = I32_clone(&self->field_size);
    (void)_t1341;
    Declaration *_t1342 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t1342->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t1342->explicit_type = *_ca; free(_ca); }
    _t1342->is_mut = _t1336;
    _t1342->is_namespace = _t1337;
    _t1342->is_ref = _t1338;
    _t1342->is_own = _t1339;
    _t1342->field_offset = _t1340;
    _t1342->field_size = _t1341;
    _t1342->field_struct_def = self->field_struct_def;
    _t1342->fn_sig = self->fn_sig;
    (void)_t1342;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t1342;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1343 = 0;
    (void)_t1343;
    Str_delete(&self->name, &(Bool){_t1343});
    ;
    Bool _t1344 = 0;
    (void)_t1344;
    Str_delete(&self->explicit_type, &(Bool){_t1344});
    ;
    Bool _t1345 = 0;
    (void)_t1345;
    Bool_delete(&self->is_mut, &(Bool){_t1345});
    ;
    Bool _t1346 = 0;
    (void)_t1346;
    Bool_delete(&self->is_namespace, &(Bool){_t1346});
    ;
    Bool _t1347 = 0;
    (void)_t1347;
    Bool_delete(&self->is_ref, &(Bool){_t1347});
    ;
    Bool _t1348 = 0;
    (void)_t1348;
    Bool_delete(&self->is_own, &(Bool){_t1348});
    ;
    Bool _t1349 = 0;
    (void)_t1349;
    I32_delete(&self->field_offset, &(Bool){_t1349});
    ;
    Bool _t1350 = 0;
    (void)_t1350;
    I32_delete(&self->field_size, &(Bool){_t1350});
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
    Bool _t1384 = Bool_clone(&self->is_mut);
    (void)_t1384;
    Bool _t1385 = Bool_clone(&self->is_own);
    (void)_t1385;
    Bool _t1386 = Bool_clone(&self->is_shallow);
    (void)_t1386;
    Param *_t1387 = malloc(sizeof(Param));
    { Str *_ca = Str_clone(&self->name); _t1387->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->ptype); _t1387->ptype = *_ca; free(_ca); }
    _t1387->is_mut = _t1384;
    _t1387->is_own = _t1385;
    _t1387->is_shallow = _t1386;
    (void)_t1387;
    ;
    ;
    ;
    return _t1387;
}

void Param_delete(Param * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1388 = 0;
    (void)_t1388;
    Str_delete(&self->name, &(Bool){_t1388});
    ;
    Bool _t1389 = 0;
    (void)_t1389;
    Str_delete(&self->ptype, &(Bool){_t1389});
    ;
    Bool _t1390 = 0;
    (void)_t1390;
    Bool_delete(&self->is_mut, &(Bool){_t1390});
    ;
    Bool _t1391 = 0;
    (void)_t1391;
    Bool_delete(&self->is_own, &(Bool){_t1391});
    ;
    Bool _t1392 = 0;
    (void)_t1392;
    Bool_delete(&self->is_shallow, &(Bool){_t1392});
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
    U32 _t1395 = U32_clone(&self->nparam);
    (void)_t1395;
    I32 _t1396 = I32_clone(&self->variadic_index);
    (void)_t1396;
    I32 _t1397 = I32_clone(&self->kwargs_index);
    (void)_t1397;
    Bool _t1398 = Bool_clone(&self->return_is_ref);
    (void)_t1398;
    Bool _t1399 = Bool_clone(&self->return_is_shallow);
    (void)_t1399;
    FunctionDef *_t1400 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1400->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); _t1400->params = *_ca; free(_ca); }
    _t1400->nparam = _t1395;
    { Map *_ca = Map_clone(&self->param_defaults); _t1400->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1400->return_type = *_ca; free(_ca); }
    _t1400->variadic_index = _t1396;
    _t1400->kwargs_index = _t1397;
    _t1400->return_is_ref = _t1398;
    _t1400->return_is_shallow = _t1399;
    (void)_t1400;
    ;
    ;
    ;
    ;
    ;
    return _t1400;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1401 = 0;
    (void)_t1401;
    FuncType_delete(&self->func_type, &(Bool){_t1401});
    ;
    Bool _t1402 = 0;
    (void)_t1402;
    Vec_delete(&self->params, &(Bool){_t1402});
    ;
    Bool _t1403 = 0;
    (void)_t1403;
    U32_delete(&self->nparam, &(Bool){_t1403});
    ;
    Bool _t1404 = 0;
    (void)_t1404;
    Map_delete(&self->param_defaults, &(Bool){_t1404});
    ;
    Bool _t1405 = 0;
    (void)_t1405;
    Str_delete(&self->return_type, &(Bool){_t1405});
    ;
    Bool _t1406 = 0;
    (void)_t1406;
    I32_delete(&self->variadic_index, &(Bool){_t1406});
    ;
    Bool _t1407 = 0;
    (void)_t1407;
    I32_delete(&self->kwargs_index, &(Bool){_t1407});
    ;
    Bool _t1408 = 0;
    (void)_t1408;
    Bool_delete(&self->return_is_ref, &(Bool){_t1408});
    ;
    Bool _t1409 = 0;
    (void)_t1409;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1409});
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
    Bool _t1792 = 0;
    (void)_t1792;
    ExprData_delete(&self->data, &(Bool){_t1792});
    ;
    Bool _t1793 = 0;
    (void)_t1793;
    TilType_delete(&self->til_type, &(Bool){_t1793});
    ;
    Bool _t1794 = 0;
    (void)_t1794;
    Str_delete(&self->struct_name, &(Bool){_t1794});
    ;
    Bool _t1795 = 0;
    (void)_t1795;
    Bool_delete(&self->is_own_arg, &(Bool){_t1795});
    ;
    Bool _t1796 = 0;
    (void)_t1796;
    Bool_delete(&self->is_splat, &(Bool){_t1796});
    ;
    Bool _t1797 = 0;
    (void)_t1797;
    Bool_delete(&self->is_own_field, &(Bool){_t1797});
    ;
    Bool _t1798 = 0;
    (void)_t1798;
    Bool_delete(&self->is_ref_field, &(Bool){_t1798});
    ;
    Bool _t1799 = 0;
    (void)_t1799;
    Bool_delete(&self->is_ns_field, &(Bool){_t1799});
    ;
    Bool _t1800 = 0;
    (void)_t1800;
    Bool_delete(&self->is_ext, &(Bool){_t1800});
    ;
    Bool _t1801 = 0;
    (void)_t1801;
    Bool_delete(&self->is_core, &(Bool){_t1801});
    ;
    Bool _t1802 = 0;
    (void)_t1802;
    Bool_delete(&self->save_old_delete, &(Bool){_t1802});
    ;
    Bool _t1803 = 0;
    (void)_t1803;
    I32_delete(&self->total_struct_size, &(Bool){_t1803});
    ;
    Bool _t1804 = 0;
    (void)_t1804;
    I32_delete(&self->variadic_index, &(Bool){_t1804});
    ;
    Bool _t1805 = 0;
    (void)_t1805;
    U32_delete(&self->variadic_count, &(Bool){_t1805});
    ;
    Bool _t1806 = 0;
    (void)_t1806;
    I32_delete(&self->kwargs_index, &(Bool){_t1806});
    ;
    Bool _t1807 = 0;
    (void)_t1807;
    U32_delete(&self->kwargs_count, &(Bool){_t1807});
    ;
    Bool _t1808 = 0;
    (void)_t1808;
    Vec_delete(&self->children, &(Bool){_t1808});
    ;
    Bool _t1809 = 0;
    (void)_t1809;
    U32_delete(&self->line, &(Bool){_t1809});
    ;
    Bool _t1810 = 0;
    (void)_t1810;
    U32_delete(&self->col, &(Bool){_t1810});
    ;
    Bool _t1811 = 0;
    (void)_t1811;
    Str_delete(&self->path, &(Bool){_t1811});
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
        ExprData *_sw1813 = ExprData_clone(data);
        (void)_sw1813;
        Bool _t1864; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Body()); _t1864 = *_hp; free(_hp); }
        (void)_t1864;
        if (_t1864) {
            Str *_t1814 = Str_lit("body", 4ULL);
            (void)_t1814;
            ExprData_delete(_sw1813, &(Bool){1});
            ;
            return _t1814;
        } else {
            Bool _t1863; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1813); _t1863 = *_hp; free(_hp); }
            (void)_t1863;
            if (_t1863) {
                Str *_t1815 = Str_lit("str", 3ULL);
                (void)_t1815;
                ;
                ExprData_delete(_sw1813, &(Bool){1});
                ;
                return _t1815;
            } else {
                Bool _t1862; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1813); _t1862 = *_hp; free(_hp); }
                (void)_t1862;
                if (_t1862) {
                    Str *_t1816 = Str_lit("num", 3ULL);
                    (void)_t1816;
                    ;
                    ;
                    ExprData_delete(_sw1813, &(Bool){1});
                    ;
                    return _t1816;
                } else {
                    Bool _t1861; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1813); _t1861 = *_hp; free(_hp); }
                    (void)_t1861;
                    if (_t1861) {
                        Str *_t1817 = Str_lit("bool", 4ULL);
                        (void)_t1817;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1813, &(Bool){1});
                        ;
                        return _t1817;
                    } else {
                        Bool _t1860; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_LiteralNull()); _t1860 = *_hp; free(_hp); }
                        (void)_t1860;
                        if (_t1860) {
                            Str *_t1818 = Str_lit("null", 4ULL);
                            (void)_t1818;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1813, &(Bool){1});
                            ;
                            return _t1818;
                        } else {
                            Bool _t1859; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1813); _t1859 = *_hp; free(_hp); }
                            (void)_t1859;
                            if (_t1859) {
                                Str *_t1819 = Str_lit("ident", 5ULL);
                                (void)_t1819;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1813, &(Bool){1});
                                ;
                                return _t1819;
                            } else {
                                Bool _t1858; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1813); _t1858 = *_hp; free(_hp); }
                                (void)_t1858;
                                if (_t1858) {
                                    Str *_t1820 = Str_lit("decl", 4ULL);
                                    (void)_t1820;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1813, &(Bool){1});
                                    ;
                                    return _t1820;
                                } else {
                                    Bool _t1857; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1813); _t1857 = *_hp; free(_hp); }
                                    (void)_t1857;
                                    if (_t1857) {
                                        Str *_t1821 = Str_lit("assign", 6ULL);
                                        (void)_t1821;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1813, &(Bool){1});
                                        ;
                                        return _t1821;
                                    } else {
                                        Bool _t1856; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_FCall()); _t1856 = *_hp; free(_hp); }
                                        (void)_t1856;
                                        if (_t1856) {
                                            Str *_t1822 = Str_lit("fcall", 5ULL);
                                            (void)_t1822;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1813, &(Bool){1});
                                            ;
                                            return _t1822;
                                        } else {
                                            Bool _t1855; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1813); _t1855 = *_hp; free(_hp); }
                                            (void)_t1855;
                                            if (_t1855) {
                                                Str *_t1823 = Str_lit("func_def", 8ULL);
                                                (void)_t1823;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1813, &(Bool){1});
                                                ;
                                                return _t1823;
                                            } else {
                                                Bool _t1854; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_StructDef()); _t1854 = *_hp; free(_hp); }
                                                (void)_t1854;
                                                if (_t1854) {
                                                    Str *_t1824 = Str_lit("struct_def", 10ULL);
                                                    (void)_t1824;
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
                                                    ExprData_delete(_sw1813, &(Bool){1});
                                                    ;
                                                    return _t1824;
                                                } else {
                                                    Bool _t1853; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_EnumDef()); _t1853 = *_hp; free(_hp); }
                                                    (void)_t1853;
                                                    if (_t1853) {
                                                        Str *_t1825 = Str_lit("enum_def", 8ULL);
                                                        (void)_t1825;
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
                                                        ExprData_delete(_sw1813, &(Bool){1});
                                                        ;
                                                        return _t1825;
                                                    } else {
                                                        Bool _t1852; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1813); _t1852 = *_hp; free(_hp); }
                                                        (void)_t1852;
                                                        if (_t1852) {
                                                            Str *_t1826 = Str_lit("field_access", 12ULL);
                                                            (void)_t1826;
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
                                                            ExprData_delete(_sw1813, &(Bool){1});
                                                            ;
                                                            return _t1826;
                                                        } else {
                                                            Bool _t1851; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1813); _t1851 = *_hp; free(_hp); }
                                                            (void)_t1851;
                                                            if (_t1851) {
                                                                Str *_t1827 = Str_lit("field_assign", 12ULL);
                                                                (void)_t1827;
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
                                                                ExprData_delete(_sw1813, &(Bool){1});
                                                                ;
                                                                return _t1827;
                                                            } else {
                                                                Bool _t1850; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Return()); _t1850 = *_hp; free(_hp); }
                                                                (void)_t1850;
                                                                if (_t1850) {
                                                                    Str *_t1828 = Str_lit("return", 6ULL);
                                                                    (void)_t1828;
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
                                                                    ExprData_delete(_sw1813, &(Bool){1});
                                                                    ;
                                                                    return _t1828;
                                                                } else {
                                                                    Bool _t1849; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_If()); _t1849 = *_hp; free(_hp); }
                                                                    (void)_t1849;
                                                                    if (_t1849) {
                                                                        Str *_t1829 = Str_lit("if", 2ULL);
                                                                        (void)_t1829;
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
                                                                        ExprData_delete(_sw1813, &(Bool){1});
                                                                        ;
                                                                        return _t1829;
                                                                    } else {
                                                                        Bool _t1848; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_While()); _t1848 = *_hp; free(_hp); }
                                                                        (void)_t1848;
                                                                        if (_t1848) {
                                                                            Str *_t1830 = Str_lit("while", 5ULL);
                                                                            (void)_t1830;
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
                                                                            ExprData_delete(_sw1813, &(Bool){1});
                                                                            ;
                                                                            return _t1830;
                                                                        } else {
                                                                            Bool _t1847; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1813); _t1847 = *_hp; free(_hp); }
                                                                            (void)_t1847;
                                                                            if (_t1847) {
                                                                                Str *_t1831 = Str_lit("for_in", 6ULL);
                                                                                (void)_t1831;
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
                                                                                ExprData_delete(_sw1813, &(Bool){1});
                                                                                ;
                                                                                return _t1831;
                                                                            } else {
                                                                                Bool _t1846; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1813); _t1846 = *_hp; free(_hp); }
                                                                                (void)_t1846;
                                                                                if (_t1846) {
                                                                                    Str *_t1832 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t1832;
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
                                                                                    ExprData_delete(_sw1813, &(Bool){1});
                                                                                    ;
                                                                                    return _t1832;
                                                                                } else {
                                                                                    Bool _t1845; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Break()); _t1845 = *_hp; free(_hp); }
                                                                                    (void)_t1845;
                                                                                    if (_t1845) {
                                                                                        Str *_t1833 = Str_lit("break", 5ULL);
                                                                                        (void)_t1833;
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
                                                                                        ExprData_delete(_sw1813, &(Bool){1});
                                                                                        ;
                                                                                        return _t1833;
                                                                                    } else {
                                                                                        Bool _t1844; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Continue()); _t1844 = *_hp; free(_hp); }
                                                                                        (void)_t1844;
                                                                                        if (_t1844) {
                                                                                            Str *_t1834 = Str_lit("continue", 8ULL);
                                                                                            (void)_t1834;
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
                                                                                            ExprData_delete(_sw1813, &(Bool){1});
                                                                                            ;
                                                                                            return _t1834;
                                                                                        } else {
                                                                                            Bool _t1843; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_MapLit()); _t1843 = *_hp; free(_hp); }
                                                                                            (void)_t1843;
                                                                                            if (_t1843) {
                                                                                                Str *_t1835 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t1835;
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
                                                                                                ExprData_delete(_sw1813, &(Bool){1});
                                                                                                ;
                                                                                                return _t1835;
                                                                                            } else {
                                                                                                Bool _t1842; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_SetLit()); _t1842 = *_hp; free(_hp); }
                                                                                                (void)_t1842;
                                                                                                if (_t1842) {
                                                                                                    Str *_t1836 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t1836;
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
                                                                                                    ExprData_delete(_sw1813, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1836;
                                                                                                } else {
                                                                                                    Bool _t1841; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Switch()); _t1841 = *_hp; free(_hp); }
                                                                                                    (void)_t1841;
                                                                                                    if (_t1841) {
                                                                                                        Str *_t1837 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t1837;
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
                                                                                                        ExprData_delete(_sw1813, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1837;
                                                                                                    } else {
                                                                                                        Bool _t1840; { Bool *_hp = (Bool *)ExprData_eq(_sw1813, ExprData_Case()); _t1840 = *_hp; free(_hp); }
                                                                                                        (void)_t1840;
                                                                                                        if (_t1840) {
                                                                                                            Str *_t1838 = Str_lit("case", 4ULL);
                                                                                                            (void)_t1838;
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
                                                                                                            ExprData_delete(_sw1813, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1838;
                                                                                                        } else {
                                                                                                            Str *_t1839 = Str_lit("?", 1ULL);
                                                                                                            (void)_t1839;
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
                                                                                                            ExprData_delete(_sw1813, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1839;
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
        ExprData_delete(_sw1813, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1865 = FuncType_clone(ft);
        (void)_sw1865;
        Bool _t1878; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_Func()); _t1878 = *_hp; free(_hp); }
        (void)_t1878;
        if (_t1878) {
            Str *_t1866 = Str_lit("func", 4ULL);
            (void)_t1866;
            FuncType_delete(_sw1865, &(Bool){1});
            ;
            return _t1866;
        } else {
            Bool _t1877; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_Proc()); _t1877 = *_hp; free(_hp); }
            (void)_t1877;
            if (_t1877) {
                Str *_t1867 = Str_lit("proc", 4ULL);
                (void)_t1867;
                ;
                FuncType_delete(_sw1865, &(Bool){1});
                ;
                return _t1867;
            } else {
                Bool _t1876; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_Test()); _t1876 = *_hp; free(_hp); }
                (void)_t1876;
                if (_t1876) {
                    Str *_t1868 = Str_lit("test", 4ULL);
                    (void)_t1868;
                    ;
                    ;
                    FuncType_delete(_sw1865, &(Bool){1});
                    ;
                    return _t1868;
                } else {
                    Bool _t1875; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_Macro()); _t1875 = *_hp; free(_hp); }
                    (void)_t1875;
                    if (_t1875) {
                        Str *_t1869 = Str_lit("macro", 5ULL);
                        (void)_t1869;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1865, &(Bool){1});
                        ;
                        return _t1869;
                    } else {
                        Bool _t1874; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_ExtFunc()); _t1874 = *_hp; free(_hp); }
                        (void)_t1874;
                        if (_t1874) {
                            Str *_t1870 = Str_lit("ext_func", 8ULL);
                            (void)_t1870;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1865, &(Bool){1});
                            ;
                            return _t1870;
                        } else {
                            Bool _t1873; { Bool *_hp = (Bool *)FuncType_eq(_sw1865, FuncType_ExtProc()); _t1873 = *_hp; free(_hp); }
                            (void)_t1873;
                            if (_t1873) {
                                Str *_t1871 = Str_lit("ext_proc", 8ULL);
                                (void)_t1871;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1865, &(Bool){1});
                                ;
                                return _t1871;
                            } else {
                                Str *_t1872 = Str_lit("?", 1ULL);
                                (void)_t1872;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1865, &(Bool){1});
                                ;
                                return _t1872;
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
        FuncType_delete(_sw1865, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi1879 = 0;
        (void)_fi1879;
        while (1) {
            I64 _t1881 = U32_to_i64(indent);
            (void)_t1881;
            U64 _t1882 = 0;
            (void)_t1882;
            U64 _t1883 = I64_to_u64(_t1881);
            (void)_t1883;
            ;
            Range *_t1884 = Range_new(_t1882, _t1883);
            (void)_t1884;
            ;
            ;
            U64 _t1885; { U64 *_hp = (U64 *)Range_len(_t1884); _t1885 = *_hp; free(_hp); }
            (void)_t1885;
            Range_delete(_t1884, &(Bool){1});
            Bool _wcond1880; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1879}, &(U64){_t1885}); _wcond1880 = *_hp; free(_hp); }
            (void)_wcond1880;
            ;
            if (_wcond1880) {
            } else {
                ;
                break;
            }
            ;
            I64 _t1886 = U32_to_i64(indent);
            (void)_t1886;
            U64 _t1887 = 0;
            (void)_t1887;
            U64 _t1888 = I64_to_u64(_t1886);
            (void)_t1888;
            ;
            Range *_t1889 = Range_new(_t1887, _t1888);
            (void)_t1889;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1889, _fi1879); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1889, &(Bool){1});
            ;
            U64 _t1890 = 1;
            (void)_t1890;
            U64 _t1891 = U64_add(_fi1879, _t1890);
            (void)_t1891;
            ;
            _fi1879 = _t1891;
            ;
            Str *_t1892 = Str_lit("Str", 3ULL);
            (void)_t1892;
            U64 _t1893; { U64 *_hp = (U64 *)Str_size(); _t1893 = *_hp; free(_hp); }
            (void)_t1893;
            U64 _t1894 = 1;
            (void)_t1894;
            Array *_va34 = Array_new(_t1892, &(U64){_t1893}, &(U64){_t1894});
            (void)_va34;
            Str_delete(_t1892, &(Bool){1});
            ;
            ;
            U64 _t1895 = 0;
            (void)_t1895;
            Str *_t1896 = Str_lit("  ", 2ULL);
            (void)_t1896;
            Array_set(_va34, &(U64){_t1895}, _t1896);
            ;
            print(_va34);
        }
        ;
    }
    Str *_t2030 = Str_lit("Str", 3ULL);
    (void)_t2030;
    U64 _t2031; { U64 *_hp = (U64 *)Str_size(); _t2031 = *_hp; free(_hp); }
    (void)_t2031;
    U64 _t2032 = 2;
    (void)_t2032;
    Array *_va48 = Array_new(_t2030, &(U64){_t2031}, &(U64){_t2032});
    (void)_va48;
    Str_delete(_t2030, &(Bool){1});
    ;
    ;
    U64 _t2033 = 0;
    (void)_t2033;
    Str *_t2034 = Str_lit("(", 1ULL);
    (void)_t2034;
    Array_set(_va48, &(U64){_t2033}, _t2034);
    ;
    U64 _t2035 = 1;
    (void)_t2035;
    Str *_t2036 = node_name(&e->data);
    (void)_t2036;
    Array_set(_va48, &(U64){_t2035}, _t2036);
    ;
    print(_va48);
    Bool _t2037; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2037 = *_hp; free(_hp); }
    (void)_t2037;
    Bool _t2038 = Bool_not(_t2037);
    (void)_t2038;
    ;
    if (_t2038) {
        Str *_t1897 = Str_lit("Str", 3ULL);
        (void)_t1897;
        U64 _t1898; { U64 *_hp = (U64 *)Str_size(); _t1898 = *_hp; free(_hp); }
        (void)_t1898;
        U64 _t1899 = 2;
        (void)_t1899;
        Array *_va35 = Array_new(_t1897, &(U64){_t1898}, &(U64){_t1899});
        (void)_va35;
        Str_delete(_t1897, &(Bool){1});
        ;
        ;
        U64 _t1900 = 0;
        (void)_t1900;
        Str *_t1901 = Str_lit(":", 1ULL);
        (void)_t1901;
        Array_set(_va35, &(U64){_t1900}, _t1901);
        ;
        U64 _t1902 = 1;
        (void)_t1902;
        Str *_t1903 = til_type_name_c(&e->til_type);
        (void)_t1903;
        Array_set(_va35, &(U64){_t1902}, _t1903);
        ;
        print(_va35);
    }
    ;
    {
        ExprData *_sw1904 = ExprData_clone(&e->data);
        (void)_sw1904;
        Bool _t1991; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1904); _t1991 = *_hp; free(_hp); }
        (void)_t1991;
        if (_t1991) {
            Str *s = ExprData_get_Ident(_sw1904);
            (void)s;
            Str *_t1905 = Str_lit("Str", 3ULL);
            (void)_t1905;
            U64 _t1906; { U64 *_hp = (U64 *)Str_size(); _t1906 = *_hp; free(_hp); }
            (void)_t1906;
            U64 _t1907 = 3;
            (void)_t1907;
            Array *_va36 = Array_new(_t1905, &(U64){_t1906}, &(U64){_t1907});
            (void)_va36;
            Str_delete(_t1905, &(Bool){1});
            ;
            ;
            U64 _t1908 = 0;
            (void)_t1908;
            Str *_t1909 = Str_lit(" \"", 3ULL);
            (void)_t1909;
            Array_set(_va36, &(U64){_t1908}, _t1909);
            ;
            U64 _t1910 = 1;
            (void)_t1910;
            Str *_t1911 = Str_clone(s);
            (void)_t1911;
            Str_delete(s, &(Bool){1});
            Array_set(_va36, &(U64){_t1910}, _t1911);
            ;
            U64 _t1912 = 2;
            (void)_t1912;
            Str *_t1913 = Str_lit("\"", 2ULL);
            (void)_t1913;
            Array_set(_va36, &(U64){_t1912}, _t1913);
            ;
            print(_va36);
        } else {
            Bool _t1990; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1904); _t1990 = *_hp; free(_hp); }
            (void)_t1990;
            if (_t1990) {
                Str *s = ExprData_get_LiteralStr(_sw1904);
                (void)s;
                Str *_t1914 = Str_lit("Str", 3ULL);
                (void)_t1914;
                U64 _t1915; { U64 *_hp = (U64 *)Str_size(); _t1915 = *_hp; free(_hp); }
                (void)_t1915;
                U64 _t1916 = 3;
                (void)_t1916;
                Array *_va37 = Array_new(_t1914, &(U64){_t1915}, &(U64){_t1916});
                (void)_va37;
                Str_delete(_t1914, &(Bool){1});
                ;
                ;
                U64 _t1917 = 0;
                (void)_t1917;
                Str *_t1918 = Str_lit(" \"", 3ULL);
                (void)_t1918;
                Array_set(_va37, &(U64){_t1917}, _t1918);
                ;
                U64 _t1919 = 1;
                (void)_t1919;
                Str *_t1920 = Str_clone(s);
                (void)_t1920;
                Str_delete(s, &(Bool){1});
                Array_set(_va37, &(U64){_t1919}, _t1920);
                ;
                U64 _t1921 = 2;
                (void)_t1921;
                Str *_t1922 = Str_lit("\"", 2ULL);
                (void)_t1922;
                Array_set(_va37, &(U64){_t1921}, _t1922);
                ;
                print(_va37);
            } else {
                Bool _t1989; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1904); _t1989 = *_hp; free(_hp); }
                (void)_t1989;
                if (_t1989) {
                    Str *s = ExprData_get_LiteralNum(_sw1904);
                    (void)s;
                    Str *_t1923 = Str_lit("Str", 3ULL);
                    (void)_t1923;
                    U64 _t1924; { U64 *_hp = (U64 *)Str_size(); _t1924 = *_hp; free(_hp); }
                    (void)_t1924;
                    U64 _t1925 = 3;
                    (void)_t1925;
                    Array *_va38 = Array_new(_t1923, &(U64){_t1924}, &(U64){_t1925});
                    (void)_va38;
                    Str_delete(_t1923, &(Bool){1});
                    ;
                    ;
                    U64 _t1926 = 0;
                    (void)_t1926;
                    Str *_t1927 = Str_lit(" \"", 3ULL);
                    (void)_t1927;
                    Array_set(_va38, &(U64){_t1926}, _t1927);
                    ;
                    U64 _t1928 = 1;
                    (void)_t1928;
                    Str *_t1929 = Str_clone(s);
                    (void)_t1929;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va38, &(U64){_t1928}, _t1929);
                    ;
                    U64 _t1930 = 2;
                    (void)_t1930;
                    Str *_t1931 = Str_lit("\"", 2ULL);
                    (void)_t1931;
                    Array_set(_va38, &(U64){_t1930}, _t1931);
                    ;
                    print(_va38);
                } else {
                    Bool _t1988; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1904); _t1988 = *_hp; free(_hp); }
                    (void)_t1988;
                    if (_t1988) {
                        Str *s = ExprData_get_LiteralBool(_sw1904);
                        (void)s;
                        Str *_t1932 = Str_lit("Str", 3ULL);
                        (void)_t1932;
                        U64 _t1933; { U64 *_hp = (U64 *)Str_size(); _t1933 = *_hp; free(_hp); }
                        (void)_t1933;
                        U64 _t1934 = 3;
                        (void)_t1934;
                        Array *_va39 = Array_new(_t1932, &(U64){_t1933}, &(U64){_t1934});
                        (void)_va39;
                        Str_delete(_t1932, &(Bool){1});
                        ;
                        ;
                        U64 _t1935 = 0;
                        (void)_t1935;
                        Str *_t1936 = Str_lit(" \"", 3ULL);
                        (void)_t1936;
                        Array_set(_va39, &(U64){_t1935}, _t1936);
                        ;
                        U64 _t1937 = 1;
                        (void)_t1937;
                        Str *_t1938 = Str_clone(s);
                        (void)_t1938;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va39, &(U64){_t1937}, _t1938);
                        ;
                        U64 _t1939 = 2;
                        (void)_t1939;
                        Str *_t1940 = Str_lit("\"", 2ULL);
                        (void)_t1940;
                        Array_set(_va39, &(U64){_t1939}, _t1940);
                        ;
                        print(_va39);
                    } else {
                        Bool _t1987; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1904); _t1987 = *_hp; free(_hp); }
                        (void)_t1987;
                        if (_t1987) {
                            Str *s = ExprData_get_ForIn(_sw1904);
                            (void)s;
                            Str *_t1941 = Str_lit("Str", 3ULL);
                            (void)_t1941;
                            U64 _t1942; { U64 *_hp = (U64 *)Str_size(); _t1942 = *_hp; free(_hp); }
                            (void)_t1942;
                            U64 _t1943 = 3;
                            (void)_t1943;
                            Array *_va40 = Array_new(_t1941, &(U64){_t1942}, &(U64){_t1943});
                            (void)_va40;
                            Str_delete(_t1941, &(Bool){1});
                            ;
                            ;
                            U64 _t1944 = 0;
                            (void)_t1944;
                            Str *_t1945 = Str_lit(" \"", 3ULL);
                            (void)_t1945;
                            Array_set(_va40, &(U64){_t1944}, _t1945);
                            ;
                            U64 _t1946 = 1;
                            (void)_t1946;
                            Str *_t1947 = Str_clone(s);
                            (void)_t1947;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va40, &(U64){_t1946}, _t1947);
                            ;
                            U64 _t1948 = 2;
                            (void)_t1948;
                            Str *_t1949 = Str_lit("\"", 2ULL);
                            (void)_t1949;
                            Array_set(_va40, &(U64){_t1948}, _t1949);
                            ;
                            print(_va40);
                        } else {
                            Bool _t1986; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1904); _t1986 = *_hp; free(_hp); }
                            (void)_t1986;
                            if (_t1986) {
                                Declaration *decl = ExprData_get_Decl(_sw1904);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1950 = Str_lit("Str", 3ULL);
                                    (void)_t1950;
                                    U64 _t1951; { U64 *_hp = (U64 *)Str_size(); _t1951 = *_hp; free(_hp); }
                                    (void)_t1951;
                                    U64 _t1952 = 1;
                                    (void)_t1952;
                                    Array *_va41 = Array_new(_t1950, &(U64){_t1951}, &(U64){_t1952});
                                    (void)_va41;
                                    Str_delete(_t1950, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1953 = 0;
                                    (void)_t1953;
                                    Str *_t1954 = Str_lit(" mut", 4ULL);
                                    (void)_t1954;
                                    Array_set(_va41, &(U64){_t1953}, _t1954);
                                    ;
                                    print(_va41);
                                }
                                Str *_t1955 = Str_lit("Str", 3ULL);
                                (void)_t1955;
                                U64 _t1956; { U64 *_hp = (U64 *)Str_size(); _t1956 = *_hp; free(_hp); }
                                (void)_t1956;
                                U64 _t1957 = 2;
                                (void)_t1957;
                                Array *_va42 = Array_new(_t1955, &(U64){_t1956}, &(U64){_t1957});
                                (void)_va42;
                                Str_delete(_t1955, &(Bool){1});
                                ;
                                ;
                                U64 _t1958 = 0;
                                (void)_t1958;
                                Str *_t1959 = Str_lit(" ", 1ULL);
                                (void)_t1959;
                                Array_set(_va42, &(U64){_t1958}, _t1959);
                                ;
                                U64 _t1960 = 1;
                                (void)_t1960;
                                Str *_t1961 = Str_clone(&decl->name);
                                (void)_t1961;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va42, &(U64){_t1960}, _t1961);
                                ;
                                print(_va42);
                            } else {
                                Bool _t1985; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1904); _t1985 = *_hp; free(_hp); }
                                (void)_t1985;
                                if (_t1985) {
                                    Str *s = ExprData_get_Assign(_sw1904);
                                    (void)s;
                                    Str *_t1962 = Str_lit("Str", 3ULL);
                                    (void)_t1962;
                                    U64 _t1963; { U64 *_hp = (U64 *)Str_size(); _t1963 = *_hp; free(_hp); }
                                    (void)_t1963;
                                    U64 _t1964 = 2;
                                    (void)_t1964;
                                    Array *_va43 = Array_new(_t1962, &(U64){_t1963}, &(U64){_t1964});
                                    (void)_va43;
                                    Str_delete(_t1962, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1965 = 0;
                                    (void)_t1965;
                                    Str *_t1966 = Str_lit(" ", 1ULL);
                                    (void)_t1966;
                                    Array_set(_va43, &(U64){_t1965}, _t1966);
                                    ;
                                    U64 _t1967 = 1;
                                    (void)_t1967;
                                    Str *_t1968 = Str_clone(s);
                                    (void)_t1968;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va43, &(U64){_t1967}, _t1968);
                                    ;
                                    print(_va43);
                                } else {
                                    Bool _t1984; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1904); _t1984 = *_hp; free(_hp); }
                                    (void)_t1984;
                                    if (_t1984) {
                                        Str *s = ExprData_get_NamedArg(_sw1904);
                                        (void)s;
                                        Str *_t1969 = Str_lit("Str", 3ULL);
                                        (void)_t1969;
                                        U64 _t1970; { U64 *_hp = (U64 *)Str_size(); _t1970 = *_hp; free(_hp); }
                                        (void)_t1970;
                                        U64 _t1971 = 2;
                                        (void)_t1971;
                                        Array *_va44 = Array_new(_t1969, &(U64){_t1970}, &(U64){_t1971});
                                        (void)_va44;
                                        Str_delete(_t1969, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1972 = 0;
                                        (void)_t1972;
                                        Str *_t1973 = Str_lit(" ", 1ULL);
                                        (void)_t1973;
                                        Array_set(_va44, &(U64){_t1972}, _t1973);
                                        ;
                                        U64 _t1974 = 1;
                                        (void)_t1974;
                                        Str *_t1975 = Str_clone(s);
                                        (void)_t1975;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va44, &(U64){_t1974}, _t1975);
                                        ;
                                        print(_va44);
                                    } else {
                                        Bool _t1983; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1904); _t1983 = *_hp; free(_hp); }
                                        (void)_t1983;
                                        if (_t1983) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1904);
                                            (void)fdef;
                                            Str *_t1976 = Str_lit("Str", 3ULL);
                                            (void)_t1976;
                                            U64 _t1977; { U64 *_hp = (U64 *)Str_size(); _t1977 = *_hp; free(_hp); }
                                            (void)_t1977;
                                            U64 _t1978 = 2;
                                            (void)_t1978;
                                            Array *_va45 = Array_new(_t1976, &(U64){_t1977}, &(U64){_t1978});
                                            (void)_va45;
                                            Str_delete(_t1976, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1979 = 0;
                                            (void)_t1979;
                                            Str *_t1980 = Str_lit(" ", 1ULL);
                                            (void)_t1980;
                                            Array_set(_va45, &(U64){_t1979}, _t1980);
                                            ;
                                            U64 _t1981 = 1;
                                            (void)_t1981;
                                            Str *_t1982 = func_type_name(&fdef->func_type);
                                            (void)_t1982;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va45, &(U64){_t1981}, _t1982);
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
        ExprData_delete(_sw1904, &(Bool){1});
        ;
    }
    U64 _t2039; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2039 = *_hp; free(_hp); }
    (void)_t2039;
    U64 _t2040 = 0;
    (void)_t2040;
    Bool _t2041; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2039}, &(U64){_t2040}); _t2041 = *_hp; free(_hp); }
    (void)_t2041;
    ;
    ;
    if (_t2041) {
        Str *_t2025 = Str_lit("Str", 3ULL);
        (void)_t2025;
        U64 _t2026; { U64 *_hp = (U64 *)Str_size(); _t2026 = *_hp; free(_hp); }
        (void)_t2026;
        U64 _t2027 = 1;
        (void)_t2027;
        Array *_va47 = Array_new(_t2025, &(U64){_t2026}, &(U64){_t2027});
        (void)_va47;
        Str_delete(_t2025, &(Bool){1});
        ;
        ;
        U64 _t2028 = 0;
        (void)_t2028;
        Str *_t2029 = Str_lit("", 0ULL);
        (void)_t2029;
        Array_set(_va47, &(U64){_t2028}, _t2029);
        ;
        println(_va47);
        {
            U64 _fi1992 = 0;
            (void)_fi1992;
            while (1) {
                U64 _t1994 = 0;
                (void)_t1994;
                U64 _t1995; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1995 = *_hp; free(_hp); }
                (void)_t1995;
                Range *_t1996 = Range_new(_t1994, _t1995);
                (void)_t1996;
                ;
                ;
                U64 _t1997; { U64 *_hp = (U64 *)Range_len(_t1996); _t1997 = *_hp; free(_hp); }
                (void)_t1997;
                Range_delete(_t1996, &(Bool){1});
                Bool _wcond1993; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1992}, &(U64){_t1997}); _wcond1993 = *_hp; free(_hp); }
                (void)_wcond1993;
                ;
                if (_wcond1993) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1998 = 0;
                (void)_t1998;
                U64 _t1999; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1999 = *_hp; free(_hp); }
                (void)_t1999;
                Range *_t2000 = Range_new(_t1998, _t1999);
                (void)_t2000;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2000, _fi1992); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2000, &(Bool){1});
                U64 _t2001 = 1;
                (void)_t2001;
                U64 _t2002 = U64_add(_fi1992, _t2001);
                (void)_t2002;
                ;
                _fi1992 = _t2002;
                ;
                I64 *_t2003 = malloc(sizeof(I64)); *_t2003 = U64_to_i64(i);
                (void)_t2003;
                ;
                U32 _t2004 = 1;
                (void)_t2004;
                Expr *_t2005 = Expr_child(e, _t2003);
                (void)_t2005;
                U32 _t2006 = U32_add(indent, _t2004);
                (void)_t2006;
                ;
                ast_print(_t2005, _t2006);
                I64_delete(_t2003, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2007 = 0;
            (void)_fi2007;
            while (1) {
                I64 _t2009 = U32_to_i64(indent);
                (void)_t2009;
                U64 _t2010 = 0;
                (void)_t2010;
                U64 _t2011 = I64_to_u64(_t2009);
                (void)_t2011;
                ;
                Range *_t2012 = Range_new(_t2010, _t2011);
                (void)_t2012;
                ;
                ;
                U64 _t2013; { U64 *_hp = (U64 *)Range_len(_t2012); _t2013 = *_hp; free(_hp); }
                (void)_t2013;
                Range_delete(_t2012, &(Bool){1});
                Bool _wcond2008; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2007}, &(U64){_t2013}); _wcond2008 = *_hp; free(_hp); }
                (void)_wcond2008;
                ;
                if (_wcond2008) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2014 = U32_to_i64(indent);
                (void)_t2014;
                U64 _t2015 = 0;
                (void)_t2015;
                U64 _t2016 = I64_to_u64(_t2014);
                (void)_t2016;
                ;
                Range *_t2017 = Range_new(_t2015, _t2016);
                (void)_t2017;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2017, _fi2007); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2017, &(Bool){1});
                ;
                U64 _t2018 = 1;
                (void)_t2018;
                U64 _t2019 = U64_add(_fi2007, _t2018);
                (void)_t2019;
                ;
                _fi2007 = _t2019;
                ;
                Str *_t2020 = Str_lit("Str", 3ULL);
                (void)_t2020;
                U64 _t2021; { U64 *_hp = (U64 *)Str_size(); _t2021 = *_hp; free(_hp); }
                (void)_t2021;
                U64 _t2022 = 1;
                (void)_t2022;
                Array *_va46 = Array_new(_t2020, &(U64){_t2021}, &(U64){_t2022});
                (void)_va46;
                Str_delete(_t2020, &(Bool){1});
                ;
                ;
                U64 _t2023 = 0;
                (void)_t2023;
                Str *_t2024 = Str_lit("  ", 2ULL);
                (void)_t2024;
                Array_set(_va46, &(U64){_t2023}, _t2024);
                ;
                print(_va46);
            }
            ;
        }
    }
    ;
    Str *_t2042 = Str_lit("Str", 3ULL);
    (void)_t2042;
    U64 _t2043; { U64 *_hp = (U64 *)Str_size(); _t2043 = *_hp; free(_hp); }
    (void)_t2043;
    U64 _t2044 = 1;
    (void)_t2044;
    Array *_va49 = Array_new(_t2042, &(U64){_t2043}, &(U64){_t2044});
    (void)_va49;
    Str_delete(_t2042, &(Bool){1});
    ;
    ;
    U64 _t2045 = 0;
    (void)_t2045;
    Str *_t2046 = Str_lit(")", 1ULL);
    (void)_t2046;
    Array_set(_va49, &(U64){_t2045}, _t2046);
    ;
    println(_va49);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2068 = malloc(sizeof(I64));
    *_t2068 = 0;
    (void)_t2068;
    Expr *body = Expr_child(enum_def, _t2068);
    (void)body;
    {
        U64 _fi2047 = 0;
        (void)_fi2047;
        while (1) {
            I64 _t2055; { I64 *_hp = (I64 *)Expr_child_count(body); _t2055 = *_hp; free(_hp); }
            (void)_t2055;
            U64 _t2056 = 0;
            (void)_t2056;
            U64 _t2057 = I64_to_u64(_t2055);
            (void)_t2057;
            ;
            Range *_t2058 = Range_new(_t2056, _t2057);
            (void)_t2058;
            ;
            ;
            U64 _t2059; { U64 *_hp = (U64 *)Range_len(_t2058); _t2059 = *_hp; free(_hp); }
            (void)_t2059;
            Range_delete(_t2058, &(Bool){1});
            Bool _wcond2048; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2047}, &(U64){_t2059}); _wcond2048 = *_hp; free(_hp); }
            (void)_wcond2048;
            ;
            if (_wcond2048) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2060; { I64 *_hp = (I64 *)Expr_child_count(body); _t2060 = *_hp; free(_hp); }
            (void)_t2060;
            U64 _t2061 = 0;
            (void)_t2061;
            U64 _t2062 = I64_to_u64(_t2060);
            (void)_t2062;
            ;
            Range *_t2063 = Range_new(_t2061, _t2062);
            (void)_t2063;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2063, _fi2047); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2063, &(Bool){1});
            U64 _t2064 = 1;
            (void)_t2064;
            U64 _t2065 = U64_add(_fi2047, _t2064);
            (void)_t2065;
            ;
            _fi2047 = _t2065;
            ;
            I64 *_t2066 = malloc(sizeof(I64)); *_t2066 = U64_to_i64(i);
            (void)_t2066;
            ;
            Expr *f = Expr_child(body, _t2066);
            (void)f;
            Bool _t2067; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2067 = *_hp; free(_hp); }
            (void)_t2067;
            if (_t2067) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2050; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2050 = *_hp; free(_hp); }
                (void)_t2050;
                U64 _t2051 = 0;
                (void)_t2051;
                Bool _t2052 = Bool_not(decl->is_namespace);
                (void)_t2052;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2053; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2050}, &(U64){_t2051}); _t2053 = *_hp; free(_hp); }
                (void)_t2053;
                ;
                ;
                Bool _t2054 = Bool_and(_t2052, _t2053);
                (void)_t2054;
                ;
                ;
                if (_t2054) {
                    Bool _t2049 = 1;
                    (void)_t2049;
                    ;
                    I64_delete(_t2066, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2049; return _r; }
                }
                ;
            }
            I64_delete(_t2066, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2068, &(Bool){1});
    Bool _t2069 = 0;
    (void)_t2069;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2069; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2089 = malloc(sizeof(I64));
    *_t2089 = 0;
    (void)_t2089;
    Expr *body = Expr_child(enum_def, _t2089);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2070 = 0;
        (void)_fi2070;
        while (1) {
            I64 _t2076; { I64 *_hp = (I64 *)Expr_child_count(body); _t2076 = *_hp; free(_hp); }
            (void)_t2076;
            U64 _t2077 = 0;
            (void)_t2077;
            U64 _t2078 = I64_to_u64(_t2076);
            (void)_t2078;
            ;
            Range *_t2079 = Range_new(_t2077, _t2078);
            (void)_t2079;
            ;
            ;
            U64 _t2080; { U64 *_hp = (U64 *)Range_len(_t2079); _t2080 = *_hp; free(_hp); }
            (void)_t2080;
            Range_delete(_t2079, &(Bool){1});
            Bool _wcond2071; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2070}, &(U64){_t2080}); _wcond2071 = *_hp; free(_hp); }
            (void)_wcond2071;
            ;
            if (_wcond2071) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2081; { I64 *_hp = (I64 *)Expr_child_count(body); _t2081 = *_hp; free(_hp); }
            (void)_t2081;
            U64 _t2082 = 0;
            (void)_t2082;
            U64 _t2083 = I64_to_u64(_t2081);
            (void)_t2083;
            ;
            Range *_t2084 = Range_new(_t2082, _t2083);
            (void)_t2084;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2084, _fi2070); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2084, &(Bool){1});
            U64 _t2085 = 1;
            (void)_t2085;
            U64 _t2086 = U64_add(_fi2070, _t2085);
            (void)_t2086;
            ;
            _fi2070 = _t2086;
            ;
            I64 *_t2087 = malloc(sizeof(I64)); *_t2087 = U64_to_i64(i);
            (void)_t2087;
            ;
            Expr *f = Expr_child(body, _t2087);
            (void)f;
            Bool _t2088; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2088 = *_hp; free(_hp); }
            (void)_t2088;
            if (_t2088) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2075 = Bool_not(decl->is_namespace);
                (void)_t2075;
                if (_t2075) {
                    Bool _t2072; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2072 = *_hp; free(_hp); }
                    (void)_t2072;
                    if (_t2072) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2087, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2073 = 1;
                    (void)_t2073;
                    I32 _t2074 = I32_add(tag, _t2073);
                    (void)_t2074;
                    ;
                    tag = _t2074;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2087, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2089, &(Bool){1});
    ;
    I64 _t2090 = 0;
    (void)_t2090;
    I64 _t2091 = 1;
    (void)_t2091;
    I64 _t2092 = I64_sub(_t2090, _t2091);
    (void)_t2092;
    ;
    ;
    I32 _t2093 = I64_to_i32(_t2092);
    (void)_t2093;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2093; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2113 = malloc(sizeof(I64));
    *_t2113 = 0;
    (void)_t2113;
    Expr *body = Expr_child(enum_def, _t2113);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi2094 = 0;
        (void)_fi2094;
        while (1) {
            I64 _t2100; { I64 *_hp = (I64 *)Expr_child_count(body); _t2100 = *_hp; free(_hp); }
            (void)_t2100;
            U64 _t2101 = 0;
            (void)_t2101;
            U64 _t2102 = I64_to_u64(_t2100);
            (void)_t2102;
            ;
            Range *_t2103 = Range_new(_t2101, _t2102);
            (void)_t2103;
            ;
            ;
            U64 _t2104; { U64 *_hp = (U64 *)Range_len(_t2103); _t2104 = *_hp; free(_hp); }
            (void)_t2104;
            Range_delete(_t2103, &(Bool){1});
            Bool _wcond2095; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2094}, &(U64){_t2104}); _wcond2095 = *_hp; free(_hp); }
            (void)_wcond2095;
            ;
            if (_wcond2095) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2105; { I64 *_hp = (I64 *)Expr_child_count(body); _t2105 = *_hp; free(_hp); }
            (void)_t2105;
            U64 _t2106 = 0;
            (void)_t2106;
            U64 _t2107 = I64_to_u64(_t2105);
            (void)_t2107;
            ;
            Range *_t2108 = Range_new(_t2106, _t2107);
            (void)_t2108;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2108, _fi2094); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2108, &(Bool){1});
            U64 _t2109 = 1;
            (void)_t2109;
            U64 _t2110 = U64_add(_fi2094, _t2109);
            (void)_t2110;
            ;
            _fi2094 = _t2110;
            ;
            I64 *_t2111 = malloc(sizeof(I64)); *_t2111 = U64_to_i64(i);
            (void)_t2111;
            ;
            Expr *f = Expr_child(body, _t2111);
            (void)f;
            Bool _t2112; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2112 = *_hp; free(_hp); }
            (void)_t2112;
            if (_t2112) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2099 = Bool_not(decl->is_namespace);
                (void)_t2099;
                if (_t2099) {
                    Bool _t2096 = I32_eq(idx, tag);
                    (void)_t2096;
                    if (_t2096) {
                        ;
                        ;
                        I64_delete(_t2111, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2097 = 1;
                    (void)_t2097;
                    I32 _t2098 = I32_add(idx, _t2097);
                    (void)_t2098;
                    ;
                    idx = _t2098;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2111, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2113, &(Bool){1});
    ;
    Str *_t2114 = Str_lit("", 0ULL);
    (void)_t2114;
    return _t2114;
}

