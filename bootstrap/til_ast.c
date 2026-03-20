#include "til_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw1334 = TilType_clone(t);
        (void)_sw1334;
        Bool _t1369; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_Unknown()); _t1369 = *_hp; free(_hp); }
        (void)_t1369;
        if (_t1369) {
            Str *_t1335 = Str_lit("unknown", 7ULL);
            (void)_t1335;
            TilType_delete(_sw1334, &(Bool){1});
            ;
            return _t1335;
        } else {
            Bool _t1368; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_None()); _t1368 = *_hp; free(_hp); }
            (void)_t1368;
            if (_t1368) {
                Str *_t1336 = Str_lit("None", 4ULL);
                (void)_t1336;
                ;
                TilType_delete(_sw1334, &(Bool){1});
                ;
                return _t1336;
            } else {
                Bool _t1367; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_I64()); _t1367 = *_hp; free(_hp); }
                (void)_t1367;
                if (_t1367) {
                    Str *_t1337 = Str_lit("I64", 3ULL);
                    (void)_t1337;
                    ;
                    ;
                    TilType_delete(_sw1334, &(Bool){1});
                    ;
                    return _t1337;
                } else {
                    Bool _t1366; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_U8()); _t1366 = *_hp; free(_hp); }
                    (void)_t1366;
                    if (_t1366) {
                        Str *_t1338 = Str_lit("U8", 2ULL);
                        (void)_t1338;
                        ;
                        ;
                        ;
                        TilType_delete(_sw1334, &(Bool){1});
                        ;
                        return _t1338;
                    } else {
                        Bool _t1365; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_I16()); _t1365 = *_hp; free(_hp); }
                        (void)_t1365;
                        if (_t1365) {
                            Str *_t1339 = Str_lit("I16", 3ULL);
                            (void)_t1339;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw1334, &(Bool){1});
                            ;
                            return _t1339;
                        } else {
                            Bool _t1364; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_I32()); _t1364 = *_hp; free(_hp); }
                            (void)_t1364;
                            if (_t1364) {
                                Str *_t1340 = Str_lit("I32", 3ULL);
                                (void)_t1340;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw1334, &(Bool){1});
                                ;
                                return _t1340;
                            } else {
                                Bool _t1363; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_U32()); _t1363 = *_hp; free(_hp); }
                                (void)_t1363;
                                if (_t1363) {
                                    Str *_t1341 = Str_lit("U32", 3ULL);
                                    (void)_t1341;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw1334, &(Bool){1});
                                    ;
                                    return _t1341;
                                } else {
                                    Bool _t1362; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_U64()); _t1362 = *_hp; free(_hp); }
                                    (void)_t1362;
                                    if (_t1362) {
                                        Str *_t1342 = Str_lit("U64", 3ULL);
                                        (void)_t1342;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw1334, &(Bool){1});
                                        ;
                                        return _t1342;
                                    } else {
                                        Bool _t1361; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_F32()); _t1361 = *_hp; free(_hp); }
                                        (void)_t1361;
                                        if (_t1361) {
                                            Str *_t1343 = Str_lit("F32", 3ULL);
                                            (void)_t1343;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw1334, &(Bool){1});
                                            ;
                                            return _t1343;
                                        } else {
                                            Bool _t1360; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_Bool()); _t1360 = *_hp; free(_hp); }
                                            (void)_t1360;
                                            if (_t1360) {
                                                Str *_t1344 = Str_lit("Bool", 4ULL);
                                                (void)_t1344;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw1334, &(Bool){1});
                                                ;
                                                return _t1344;
                                            } else {
                                                Bool _t1359; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_Struct()); _t1359 = *_hp; free(_hp); }
                                                (void)_t1359;
                                                if (_t1359) {
                                                    Str *_t1345 = Str_lit("Struct", 6ULL);
                                                    (void)_t1345;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw1334, &(Bool){1});
                                                    ;
                                                    return _t1345;
                                                } else {
                                                    Bool _t1358; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_StructDef()); _t1358 = *_hp; free(_hp); }
                                                    (void)_t1358;
                                                    if (_t1358) {
                                                        Str *_t1346 = Str_lit("StructDef", 9ULL);
                                                        (void)_t1346;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw1334, &(Bool){1});
                                                        ;
                                                        return _t1346;
                                                    } else {
                                                        Bool _t1357; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_Enum()); _t1357 = *_hp; free(_hp); }
                                                        (void)_t1357;
                                                        if (_t1357) {
                                                            Str *_t1347 = Str_lit("Enum", 4ULL);
                                                            (void)_t1347;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw1334, &(Bool){1});
                                                            ;
                                                            return _t1347;
                                                        } else {
                                                            Bool _t1356; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_EnumDef()); _t1356 = *_hp; free(_hp); }
                                                            (void)_t1356;
                                                            if (_t1356) {
                                                                Str *_t1348 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t1348;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw1334, &(Bool){1});
                                                                ;
                                                                return _t1348;
                                                            } else {
                                                                Bool _t1355; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_FuncDef()); _t1355 = *_hp; free(_hp); }
                                                                (void)_t1355;
                                                                if (_t1355) {
                                                                    Str *_t1349 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t1349;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw1334, &(Bool){1});
                                                                    ;
                                                                    return _t1349;
                                                                } else {
                                                                    Bool _t1354; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_FuncPtr()); _t1354 = *_hp; free(_hp); }
                                                                    (void)_t1354;
                                                                    if (_t1354) {
                                                                        Str *_t1350 = Str_lit("Fn", 2ULL);
                                                                        (void)_t1350;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw1334, &(Bool){1});
                                                                        ;
                                                                        return _t1350;
                                                                    } else {
                                                                        Bool _t1353; { Bool *_hp = (Bool *)TilType_eq(_sw1334, TilType_Dynamic()); _t1353 = *_hp; free(_hp); }
                                                                        (void)_t1353;
                                                                        if (_t1353) {
                                                                            Str *_t1351 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t1351;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1334, &(Bool){1});
                                                                            ;
                                                                            return _t1351;
                                                                        } else {
                                                                            Str *_t1352 = Str_lit("?", 1ULL);
                                                                            (void)_t1352;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1334, &(Bool){1});
                                                                            ;
                                                                            return _t1352;
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
        TilType_delete(_sw1334, &(Bool){1});
        ;
    }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t1371 = Bool_clone(&self->is_mut);
    (void)_t1371;
    Bool _t1372 = Bool_clone(&self->is_namespace);
    (void)_t1372;
    Bool _t1373 = Bool_clone(&self->is_ref);
    (void)_t1373;
    Bool _t1374 = Bool_clone(&self->is_own);
    (void)_t1374;
    I32 _t1375 = I32_clone(&self->field_offset);
    (void)_t1375;
    I32 _t1376 = I32_clone(&self->field_size);
    (void)_t1376;
    Declaration *_t1377 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t1377->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t1377->explicit_type = *_ca; free(_ca); }
    _t1377->is_mut = _t1371;
    _t1377->is_namespace = _t1372;
    _t1377->is_ref = _t1373;
    _t1377->is_own = _t1374;
    _t1377->field_offset = _t1375;
    _t1377->field_size = _t1376;
    _t1377->field_struct_def = self->field_struct_def;
    _t1377->fn_sig = self->fn_sig;
    (void)_t1377;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t1377;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1378 = 0;
    (void)_t1378;
    Str_delete(&self->name, &(Bool){_t1378});
    ;
    Bool _t1379 = 0;
    (void)_t1379;
    Str_delete(&self->explicit_type, &(Bool){_t1379});
    ;
    Bool _t1380 = 0;
    (void)_t1380;
    Bool_delete(&self->is_mut, &(Bool){_t1380});
    ;
    Bool _t1381 = 0;
    (void)_t1381;
    Bool_delete(&self->is_namespace, &(Bool){_t1381});
    ;
    Bool _t1382 = 0;
    (void)_t1382;
    Bool_delete(&self->is_ref, &(Bool){_t1382});
    ;
    Bool _t1383 = 0;
    (void)_t1383;
    Bool_delete(&self->is_own, &(Bool){_t1383});
    ;
    Bool _t1384 = 0;
    (void)_t1384;
    I32_delete(&self->field_offset, &(Bool){_t1384});
    ;
    Bool _t1385 = 0;
    (void)_t1385;
    I32_delete(&self->field_size, &(Bool){_t1385});
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
    Bool _t1419 = Bool_clone(&self->is_mut);
    (void)_t1419;
    Bool _t1420 = Bool_clone(&self->is_own);
    (void)_t1420;
    Bool _t1421 = Bool_clone(&self->is_shallow);
    (void)_t1421;
    Param *_t1422 = malloc(sizeof(Param));
    { Str *_ca = Str_clone(&self->name); _t1422->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->ptype); _t1422->ptype = *_ca; free(_ca); }
    _t1422->is_mut = _t1419;
    _t1422->is_own = _t1420;
    _t1422->is_shallow = _t1421;
    (void)_t1422;
    ;
    ;
    ;
    return _t1422;
}

void Param_delete(Param * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1423 = 0;
    (void)_t1423;
    Str_delete(&self->name, &(Bool){_t1423});
    ;
    Bool _t1424 = 0;
    (void)_t1424;
    Str_delete(&self->ptype, &(Bool){_t1424});
    ;
    Bool _t1425 = 0;
    (void)_t1425;
    Bool_delete(&self->is_mut, &(Bool){_t1425});
    ;
    Bool _t1426 = 0;
    (void)_t1426;
    Bool_delete(&self->is_own, &(Bool){_t1426});
    ;
    Bool _t1427 = 0;
    (void)_t1427;
    Bool_delete(&self->is_shallow, &(Bool){_t1427});
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
    U32 _t1430 = U32_clone(&self->nparam);
    (void)_t1430;
    I32 _t1431 = I32_clone(&self->variadic_index);
    (void)_t1431;
    I32 _t1432 = I32_clone(&self->kwargs_index);
    (void)_t1432;
    Bool _t1433 = Bool_clone(&self->return_is_ref);
    (void)_t1433;
    Bool _t1434 = Bool_clone(&self->return_is_shallow);
    (void)_t1434;
    FunctionDef *_t1435 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1435->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); _t1435->params = *_ca; free(_ca); }
    _t1435->nparam = _t1430;
    { Map *_ca = Map_clone(&self->param_defaults); _t1435->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1435->return_type = *_ca; free(_ca); }
    _t1435->variadic_index = _t1431;
    _t1435->kwargs_index = _t1432;
    _t1435->return_is_ref = _t1433;
    _t1435->return_is_shallow = _t1434;
    (void)_t1435;
    ;
    ;
    ;
    ;
    ;
    return _t1435;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1436 = 0;
    (void)_t1436;
    FuncType_delete(&self->func_type, &(Bool){_t1436});
    ;
    Bool _t1437 = 0;
    (void)_t1437;
    Vec_delete(&self->params, &(Bool){_t1437});
    ;
    Bool _t1438 = 0;
    (void)_t1438;
    U32_delete(&self->nparam, &(Bool){_t1438});
    ;
    Bool _t1439 = 0;
    (void)_t1439;
    Map_delete(&self->param_defaults, &(Bool){_t1439});
    ;
    Bool _t1440 = 0;
    (void)_t1440;
    Str_delete(&self->return_type, &(Bool){_t1440});
    ;
    Bool _t1441 = 0;
    (void)_t1441;
    I32_delete(&self->variadic_index, &(Bool){_t1441});
    ;
    Bool _t1442 = 0;
    (void)_t1442;
    I32_delete(&self->kwargs_index, &(Bool){_t1442});
    ;
    Bool _t1443 = 0;
    (void)_t1443;
    Bool_delete(&self->return_is_ref, &(Bool){_t1443});
    ;
    Bool _t1444 = 0;
    (void)_t1444;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1444});
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
    Bool _t1827 = 0;
    (void)_t1827;
    ExprData_delete(&self->data, &(Bool){_t1827});
    ;
    Bool _t1828 = 0;
    (void)_t1828;
    TilType_delete(&self->til_type, &(Bool){_t1828});
    ;
    Bool _t1829 = 0;
    (void)_t1829;
    Str_delete(&self->struct_name, &(Bool){_t1829});
    ;
    Bool _t1830 = 0;
    (void)_t1830;
    Bool_delete(&self->is_own_arg, &(Bool){_t1830});
    ;
    Bool _t1831 = 0;
    (void)_t1831;
    Bool_delete(&self->is_splat, &(Bool){_t1831});
    ;
    Bool _t1832 = 0;
    (void)_t1832;
    Bool_delete(&self->is_own_field, &(Bool){_t1832});
    ;
    Bool _t1833 = 0;
    (void)_t1833;
    Bool_delete(&self->is_ref_field, &(Bool){_t1833});
    ;
    Bool _t1834 = 0;
    (void)_t1834;
    Bool_delete(&self->is_ns_field, &(Bool){_t1834});
    ;
    Bool _t1835 = 0;
    (void)_t1835;
    Bool_delete(&self->is_ext, &(Bool){_t1835});
    ;
    Bool _t1836 = 0;
    (void)_t1836;
    Bool_delete(&self->is_core, &(Bool){_t1836});
    ;
    Bool _t1837 = 0;
    (void)_t1837;
    Bool_delete(&self->save_old_delete, &(Bool){_t1837});
    ;
    Bool _t1838 = 0;
    (void)_t1838;
    I32_delete(&self->total_struct_size, &(Bool){_t1838});
    ;
    Bool _t1839 = 0;
    (void)_t1839;
    I32_delete(&self->variadic_index, &(Bool){_t1839});
    ;
    Bool _t1840 = 0;
    (void)_t1840;
    U32_delete(&self->variadic_count, &(Bool){_t1840});
    ;
    Bool _t1841 = 0;
    (void)_t1841;
    I32_delete(&self->kwargs_index, &(Bool){_t1841});
    ;
    Bool _t1842 = 0;
    (void)_t1842;
    U32_delete(&self->kwargs_count, &(Bool){_t1842});
    ;
    Bool _t1843 = 0;
    (void)_t1843;
    Vec_delete(&self->children, &(Bool){_t1843});
    ;
    Bool _t1844 = 0;
    (void)_t1844;
    U32_delete(&self->line, &(Bool){_t1844});
    ;
    Bool _t1845 = 0;
    (void)_t1845;
    U32_delete(&self->col, &(Bool){_t1845});
    ;
    Bool _t1846 = 0;
    (void)_t1846;
    Str_delete(&self->path, &(Bool){_t1846});
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
        ExprData *_sw1848 = ExprData_clone(data);
        (void)_sw1848;
        Bool _t1899; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Body()); _t1899 = *_hp; free(_hp); }
        (void)_t1899;
        if (_t1899) {
            Str *_t1849 = Str_lit("body", 4ULL);
            (void)_t1849;
            ExprData_delete(_sw1848, &(Bool){1});
            ;
            return _t1849;
        } else {
            Bool _t1898; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1848); _t1898 = *_hp; free(_hp); }
            (void)_t1898;
            if (_t1898) {
                Str *_t1850 = Str_lit("str", 3ULL);
                (void)_t1850;
                ;
                ExprData_delete(_sw1848, &(Bool){1});
                ;
                return _t1850;
            } else {
                Bool _t1897; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1848); _t1897 = *_hp; free(_hp); }
                (void)_t1897;
                if (_t1897) {
                    Str *_t1851 = Str_lit("num", 3ULL);
                    (void)_t1851;
                    ;
                    ;
                    ExprData_delete(_sw1848, &(Bool){1});
                    ;
                    return _t1851;
                } else {
                    Bool _t1896; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1848); _t1896 = *_hp; free(_hp); }
                    (void)_t1896;
                    if (_t1896) {
                        Str *_t1852 = Str_lit("bool", 4ULL);
                        (void)_t1852;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1848, &(Bool){1});
                        ;
                        return _t1852;
                    } else {
                        Bool _t1895; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_LiteralNull()); _t1895 = *_hp; free(_hp); }
                        (void)_t1895;
                        if (_t1895) {
                            Str *_t1853 = Str_lit("null", 4ULL);
                            (void)_t1853;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1848, &(Bool){1});
                            ;
                            return _t1853;
                        } else {
                            Bool _t1894; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1848); _t1894 = *_hp; free(_hp); }
                            (void)_t1894;
                            if (_t1894) {
                                Str *_t1854 = Str_lit("ident", 5ULL);
                                (void)_t1854;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1848, &(Bool){1});
                                ;
                                return _t1854;
                            } else {
                                Bool _t1893; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1848); _t1893 = *_hp; free(_hp); }
                                (void)_t1893;
                                if (_t1893) {
                                    Str *_t1855 = Str_lit("decl", 4ULL);
                                    (void)_t1855;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1848, &(Bool){1});
                                    ;
                                    return _t1855;
                                } else {
                                    Bool _t1892; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1848); _t1892 = *_hp; free(_hp); }
                                    (void)_t1892;
                                    if (_t1892) {
                                        Str *_t1856 = Str_lit("assign", 6ULL);
                                        (void)_t1856;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1848, &(Bool){1});
                                        ;
                                        return _t1856;
                                    } else {
                                        Bool _t1891; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_FCall()); _t1891 = *_hp; free(_hp); }
                                        (void)_t1891;
                                        if (_t1891) {
                                            Str *_t1857 = Str_lit("fcall", 5ULL);
                                            (void)_t1857;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1848, &(Bool){1});
                                            ;
                                            return _t1857;
                                        } else {
                                            Bool _t1890; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1848); _t1890 = *_hp; free(_hp); }
                                            (void)_t1890;
                                            if (_t1890) {
                                                Str *_t1858 = Str_lit("func_def", 8ULL);
                                                (void)_t1858;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1848, &(Bool){1});
                                                ;
                                                return _t1858;
                                            } else {
                                                Bool _t1889; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_StructDef()); _t1889 = *_hp; free(_hp); }
                                                (void)_t1889;
                                                if (_t1889) {
                                                    Str *_t1859 = Str_lit("struct_def", 10ULL);
                                                    (void)_t1859;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw1848, &(Bool){1});
                                                    ;
                                                    return _t1859;
                                                } else {
                                                    Bool _t1888; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_EnumDef()); _t1888 = *_hp; free(_hp); }
                                                    (void)_t1888;
                                                    if (_t1888) {
                                                        Str *_t1860 = Str_lit("enum_def", 8ULL);
                                                        (void)_t1860;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw1848, &(Bool){1});
                                                        ;
                                                        return _t1860;
                                                    } else {
                                                        Bool _t1887; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1848); _t1887 = *_hp; free(_hp); }
                                                        (void)_t1887;
                                                        if (_t1887) {
                                                            Str *_t1861 = Str_lit("field_access", 12ULL);
                                                            (void)_t1861;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw1848, &(Bool){1});
                                                            ;
                                                            return _t1861;
                                                        } else {
                                                            Bool _t1886; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1848); _t1886 = *_hp; free(_hp); }
                                                            (void)_t1886;
                                                            if (_t1886) {
                                                                Str *_t1862 = Str_lit("field_assign", 12ULL);
                                                                (void)_t1862;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw1848, &(Bool){1});
                                                                ;
                                                                return _t1862;
                                                            } else {
                                                                Bool _t1885; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Return()); _t1885 = *_hp; free(_hp); }
                                                                (void)_t1885;
                                                                if (_t1885) {
                                                                    Str *_t1863 = Str_lit("return", 6ULL);
                                                                    (void)_t1863;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw1848, &(Bool){1});
                                                                    ;
                                                                    return _t1863;
                                                                } else {
                                                                    Bool _t1884; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_If()); _t1884 = *_hp; free(_hp); }
                                                                    (void)_t1884;
                                                                    if (_t1884) {
                                                                        Str *_t1864 = Str_lit("if", 2ULL);
                                                                        (void)_t1864;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw1848, &(Bool){1});
                                                                        ;
                                                                        return _t1864;
                                                                    } else {
                                                                        Bool _t1883; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_While()); _t1883 = *_hp; free(_hp); }
                                                                        (void)_t1883;
                                                                        if (_t1883) {
                                                                            Str *_t1865 = Str_lit("while", 5ULL);
                                                                            (void)_t1865;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw1848, &(Bool){1});
                                                                            ;
                                                                            return _t1865;
                                                                        } else {
                                                                            Bool _t1882; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1848); _t1882 = *_hp; free(_hp); }
                                                                            (void)_t1882;
                                                                            if (_t1882) {
                                                                                Str *_t1866 = Str_lit("for_in", 6ULL);
                                                                                (void)_t1866;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw1848, &(Bool){1});
                                                                                ;
                                                                                return _t1866;
                                                                            } else {
                                                                                Bool _t1881; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1848); _t1881 = *_hp; free(_hp); }
                                                                                (void)_t1881;
                                                                                if (_t1881) {
                                                                                    Str *_t1867 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t1867;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw1848, &(Bool){1});
                                                                                    ;
                                                                                    return _t1867;
                                                                                } else {
                                                                                    Bool _t1880; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Break()); _t1880 = *_hp; free(_hp); }
                                                                                    (void)_t1880;
                                                                                    if (_t1880) {
                                                                                        Str *_t1868 = Str_lit("break", 5ULL);
                                                                                        (void)_t1868;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw1848, &(Bool){1});
                                                                                        ;
                                                                                        return _t1868;
                                                                                    } else {
                                                                                        Bool _t1879; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Continue()); _t1879 = *_hp; free(_hp); }
                                                                                        (void)_t1879;
                                                                                        if (_t1879) {
                                                                                            Str *_t1869 = Str_lit("continue", 8ULL);
                                                                                            (void)_t1869;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw1848, &(Bool){1});
                                                                                            ;
                                                                                            return _t1869;
                                                                                        } else {
                                                                                            Bool _t1878; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_MapLit()); _t1878 = *_hp; free(_hp); }
                                                                                            (void)_t1878;
                                                                                            if (_t1878) {
                                                                                                Str *_t1870 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t1870;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw1848, &(Bool){1});
                                                                                                ;
                                                                                                return _t1870;
                                                                                            } else {
                                                                                                Bool _t1877; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_SetLit()); _t1877 = *_hp; free(_hp); }
                                                                                                (void)_t1877;
                                                                                                if (_t1877) {
                                                                                                    Str *_t1871 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t1871;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw1848, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1871;
                                                                                                } else {
                                                                                                    Bool _t1876; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Switch()); _t1876 = *_hp; free(_hp); }
                                                                                                    (void)_t1876;
                                                                                                    if (_t1876) {
                                                                                                        Str *_t1872 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t1872;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw1848, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1872;
                                                                                                    } else {
                                                                                                        Bool _t1875; { Bool *_hp = (Bool *)ExprData_eq(_sw1848, ExprData_Case()); _t1875 = *_hp; free(_hp); }
                                                                                                        (void)_t1875;
                                                                                                        if (_t1875) {
                                                                                                            Str *_t1873 = Str_lit("case", 4ULL);
                                                                                                            (void)_t1873;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1848, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1873;
                                                                                                        } else {
                                                                                                            Str *_t1874 = Str_lit("?", 1ULL);
                                                                                                            (void)_t1874;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1848, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1874;
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
        ExprData_delete(_sw1848, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1900 = FuncType_clone(ft);
        (void)_sw1900;
        Bool _t1913; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_Func()); _t1913 = *_hp; free(_hp); }
        (void)_t1913;
        if (_t1913) {
            Str *_t1901 = Str_lit("func", 4ULL);
            (void)_t1901;
            FuncType_delete(_sw1900, &(Bool){1});
            ;
            return _t1901;
        } else {
            Bool _t1912; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_Proc()); _t1912 = *_hp; free(_hp); }
            (void)_t1912;
            if (_t1912) {
                Str *_t1902 = Str_lit("proc", 4ULL);
                (void)_t1902;
                ;
                FuncType_delete(_sw1900, &(Bool){1});
                ;
                return _t1902;
            } else {
                Bool _t1911; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_Test()); _t1911 = *_hp; free(_hp); }
                (void)_t1911;
                if (_t1911) {
                    Str *_t1903 = Str_lit("test", 4ULL);
                    (void)_t1903;
                    ;
                    ;
                    FuncType_delete(_sw1900, &(Bool){1});
                    ;
                    return _t1903;
                } else {
                    Bool _t1910; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_Macro()); _t1910 = *_hp; free(_hp); }
                    (void)_t1910;
                    if (_t1910) {
                        Str *_t1904 = Str_lit("macro", 5ULL);
                        (void)_t1904;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1900, &(Bool){1});
                        ;
                        return _t1904;
                    } else {
                        Bool _t1909; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_ExtFunc()); _t1909 = *_hp; free(_hp); }
                        (void)_t1909;
                        if (_t1909) {
                            Str *_t1905 = Str_lit("ext_func", 8ULL);
                            (void)_t1905;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1900, &(Bool){1});
                            ;
                            return _t1905;
                        } else {
                            Bool _t1908; { Bool *_hp = (Bool *)FuncType_eq(_sw1900, FuncType_ExtProc()); _t1908 = *_hp; free(_hp); }
                            (void)_t1908;
                            if (_t1908) {
                                Str *_t1906 = Str_lit("ext_proc", 8ULL);
                                (void)_t1906;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1900, &(Bool){1});
                                ;
                                return _t1906;
                            } else {
                                Str *_t1907 = Str_lit("?", 1ULL);
                                (void)_t1907;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1900, &(Bool){1});
                                ;
                                return _t1907;
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
        FuncType_delete(_sw1900, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi1914 = 0;
        (void)_fi1914;
        while (1) {
            I64 _t1916 = U32_to_i64(indent);
            (void)_t1916;
            U64 _t1917 = 0;
            (void)_t1917;
            U64 _t1918 = I64_to_u64(_t1916);
            (void)_t1918;
            ;
            Range *_t1919 = Range_new(_t1917, _t1918);
            (void)_t1919;
            ;
            ;
            U64 _t1920; { U64 *_hp = (U64 *)Range_len(_t1919); _t1920 = *_hp; free(_hp); }
            (void)_t1920;
            Range_delete(_t1919, &(Bool){1});
            Bool _wcond1915; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1914}, &(U64){_t1920}); _wcond1915 = *_hp; free(_hp); }
            (void)_wcond1915;
            ;
            if (_wcond1915) {
            } else {
                ;
                break;
            }
            ;
            I64 _t1921 = U32_to_i64(indent);
            (void)_t1921;
            U64 _t1922 = 0;
            (void)_t1922;
            U64 _t1923 = I64_to_u64(_t1921);
            (void)_t1923;
            ;
            Range *_t1924 = Range_new(_t1922, _t1923);
            (void)_t1924;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1924, _fi1914); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1924, &(Bool){1});
            ;
            U64 _t1925 = 1;
            (void)_t1925;
            U64 _t1926 = U64_add(_fi1914, _t1925);
            (void)_t1926;
            ;
            _fi1914 = _t1926;
            ;
            Str *_t1927 = Str_lit("Str", 3ULL);
            (void)_t1927;
            U64 _t1928; { U64 *_hp = (U64 *)Str_size(); _t1928 = *_hp; free(_hp); }
            (void)_t1928;
            U64 _t1929 = 1;
            (void)_t1929;
            Array *_va34 = Array_new(_t1927, &(U64){_t1928}, &(U64){_t1929});
            (void)_va34;
            Str_delete(_t1927, &(Bool){1});
            ;
            ;
            U64 _t1930 = 0;
            (void)_t1930;
            Str *_t1931 = Str_lit("  ", 2ULL);
            (void)_t1931;
            Array_set(_va34, &(U64){_t1930}, _t1931);
            ;
            print(_va34);
        }
        ;
    }
    Str *_t2065 = Str_lit("Str", 3ULL);
    (void)_t2065;
    U64 _t2066; { U64 *_hp = (U64 *)Str_size(); _t2066 = *_hp; free(_hp); }
    (void)_t2066;
    U64 _t2067 = 2;
    (void)_t2067;
    Array *_va48 = Array_new(_t2065, &(U64){_t2066}, &(U64){_t2067});
    (void)_va48;
    Str_delete(_t2065, &(Bool){1});
    ;
    ;
    U64 _t2068 = 0;
    (void)_t2068;
    Str *_t2069 = Str_lit("(", 1ULL);
    (void)_t2069;
    Array_set(_va48, &(U64){_t2068}, _t2069);
    ;
    U64 _t2070 = 1;
    (void)_t2070;
    Str *_t2071 = node_name(&e->data);
    (void)_t2071;
    Array_set(_va48, &(U64){_t2070}, _t2071);
    ;
    print(_va48);
    Bool _t2072; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2072 = *_hp; free(_hp); }
    (void)_t2072;
    Bool _t2073 = Bool_not(_t2072);
    (void)_t2073;
    ;
    if (_t2073) {
        Str *_t1932 = Str_lit("Str", 3ULL);
        (void)_t1932;
        U64 _t1933; { U64 *_hp = (U64 *)Str_size(); _t1933 = *_hp; free(_hp); }
        (void)_t1933;
        U64 _t1934 = 2;
        (void)_t1934;
        Array *_va35 = Array_new(_t1932, &(U64){_t1933}, &(U64){_t1934});
        (void)_va35;
        Str_delete(_t1932, &(Bool){1});
        ;
        ;
        U64 _t1935 = 0;
        (void)_t1935;
        Str *_t1936 = Str_lit(":", 1ULL);
        (void)_t1936;
        Array_set(_va35, &(U64){_t1935}, _t1936);
        ;
        U64 _t1937 = 1;
        (void)_t1937;
        Str *_t1938 = til_type_name_c(&e->til_type);
        (void)_t1938;
        Array_set(_va35, &(U64){_t1937}, _t1938);
        ;
        print(_va35);
    }
    ;
    {
        ExprData *_sw1939 = ExprData_clone(&e->data);
        (void)_sw1939;
        Bool _t2026; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1939); _t2026 = *_hp; free(_hp); }
        (void)_t2026;
        if (_t2026) {
            Str *s = ExprData_get_Ident(_sw1939);
            (void)s;
            Str *_t1940 = Str_lit("Str", 3ULL);
            (void)_t1940;
            U64 _t1941; { U64 *_hp = (U64 *)Str_size(); _t1941 = *_hp; free(_hp); }
            (void)_t1941;
            U64 _t1942 = 3;
            (void)_t1942;
            Array *_va36 = Array_new(_t1940, &(U64){_t1941}, &(U64){_t1942});
            (void)_va36;
            Str_delete(_t1940, &(Bool){1});
            ;
            ;
            U64 _t1943 = 0;
            (void)_t1943;
            Str *_t1944 = Str_lit(" \"", 3ULL);
            (void)_t1944;
            Array_set(_va36, &(U64){_t1943}, _t1944);
            ;
            U64 _t1945 = 1;
            (void)_t1945;
            Str *_t1946 = Str_clone(s);
            (void)_t1946;
            Str_delete(s, &(Bool){1});
            Array_set(_va36, &(U64){_t1945}, _t1946);
            ;
            U64 _t1947 = 2;
            (void)_t1947;
            Str *_t1948 = Str_lit("\"", 2ULL);
            (void)_t1948;
            Array_set(_va36, &(U64){_t1947}, _t1948);
            ;
            print(_va36);
        } else {
            Bool _t2025; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1939); _t2025 = *_hp; free(_hp); }
            (void)_t2025;
            if (_t2025) {
                Str *s = ExprData_get_LiteralStr(_sw1939);
                (void)s;
                Str *_t1949 = Str_lit("Str", 3ULL);
                (void)_t1949;
                U64 _t1950; { U64 *_hp = (U64 *)Str_size(); _t1950 = *_hp; free(_hp); }
                (void)_t1950;
                U64 _t1951 = 3;
                (void)_t1951;
                Array *_va37 = Array_new(_t1949, &(U64){_t1950}, &(U64){_t1951});
                (void)_va37;
                Str_delete(_t1949, &(Bool){1});
                ;
                ;
                U64 _t1952 = 0;
                (void)_t1952;
                Str *_t1953 = Str_lit(" \"", 3ULL);
                (void)_t1953;
                Array_set(_va37, &(U64){_t1952}, _t1953);
                ;
                U64 _t1954 = 1;
                (void)_t1954;
                Str *_t1955 = Str_clone(s);
                (void)_t1955;
                Str_delete(s, &(Bool){1});
                Array_set(_va37, &(U64){_t1954}, _t1955);
                ;
                U64 _t1956 = 2;
                (void)_t1956;
                Str *_t1957 = Str_lit("\"", 2ULL);
                (void)_t1957;
                Array_set(_va37, &(U64){_t1956}, _t1957);
                ;
                print(_va37);
            } else {
                Bool _t2024; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1939); _t2024 = *_hp; free(_hp); }
                (void)_t2024;
                if (_t2024) {
                    Str *s = ExprData_get_LiteralNum(_sw1939);
                    (void)s;
                    Str *_t1958 = Str_lit("Str", 3ULL);
                    (void)_t1958;
                    U64 _t1959; { U64 *_hp = (U64 *)Str_size(); _t1959 = *_hp; free(_hp); }
                    (void)_t1959;
                    U64 _t1960 = 3;
                    (void)_t1960;
                    Array *_va38 = Array_new(_t1958, &(U64){_t1959}, &(U64){_t1960});
                    (void)_va38;
                    Str_delete(_t1958, &(Bool){1});
                    ;
                    ;
                    U64 _t1961 = 0;
                    (void)_t1961;
                    Str *_t1962 = Str_lit(" \"", 3ULL);
                    (void)_t1962;
                    Array_set(_va38, &(U64){_t1961}, _t1962);
                    ;
                    U64 _t1963 = 1;
                    (void)_t1963;
                    Str *_t1964 = Str_clone(s);
                    (void)_t1964;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va38, &(U64){_t1963}, _t1964);
                    ;
                    U64 _t1965 = 2;
                    (void)_t1965;
                    Str *_t1966 = Str_lit("\"", 2ULL);
                    (void)_t1966;
                    Array_set(_va38, &(U64){_t1965}, _t1966);
                    ;
                    print(_va38);
                } else {
                    Bool _t2023; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1939); _t2023 = *_hp; free(_hp); }
                    (void)_t2023;
                    if (_t2023) {
                        Str *s = ExprData_get_LiteralBool(_sw1939);
                        (void)s;
                        Str *_t1967 = Str_lit("Str", 3ULL);
                        (void)_t1967;
                        U64 _t1968; { U64 *_hp = (U64 *)Str_size(); _t1968 = *_hp; free(_hp); }
                        (void)_t1968;
                        U64 _t1969 = 3;
                        (void)_t1969;
                        Array *_va39 = Array_new(_t1967, &(U64){_t1968}, &(U64){_t1969});
                        (void)_va39;
                        Str_delete(_t1967, &(Bool){1});
                        ;
                        ;
                        U64 _t1970 = 0;
                        (void)_t1970;
                        Str *_t1971 = Str_lit(" \"", 3ULL);
                        (void)_t1971;
                        Array_set(_va39, &(U64){_t1970}, _t1971);
                        ;
                        U64 _t1972 = 1;
                        (void)_t1972;
                        Str *_t1973 = Str_clone(s);
                        (void)_t1973;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va39, &(U64){_t1972}, _t1973);
                        ;
                        U64 _t1974 = 2;
                        (void)_t1974;
                        Str *_t1975 = Str_lit("\"", 2ULL);
                        (void)_t1975;
                        Array_set(_va39, &(U64){_t1974}, _t1975);
                        ;
                        print(_va39);
                    } else {
                        Bool _t2022; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1939); _t2022 = *_hp; free(_hp); }
                        (void)_t2022;
                        if (_t2022) {
                            Str *s = ExprData_get_ForIn(_sw1939);
                            (void)s;
                            Str *_t1976 = Str_lit("Str", 3ULL);
                            (void)_t1976;
                            U64 _t1977; { U64 *_hp = (U64 *)Str_size(); _t1977 = *_hp; free(_hp); }
                            (void)_t1977;
                            U64 _t1978 = 3;
                            (void)_t1978;
                            Array *_va40 = Array_new(_t1976, &(U64){_t1977}, &(U64){_t1978});
                            (void)_va40;
                            Str_delete(_t1976, &(Bool){1});
                            ;
                            ;
                            U64 _t1979 = 0;
                            (void)_t1979;
                            Str *_t1980 = Str_lit(" \"", 3ULL);
                            (void)_t1980;
                            Array_set(_va40, &(U64){_t1979}, _t1980);
                            ;
                            U64 _t1981 = 1;
                            (void)_t1981;
                            Str *_t1982 = Str_clone(s);
                            (void)_t1982;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va40, &(U64){_t1981}, _t1982);
                            ;
                            U64 _t1983 = 2;
                            (void)_t1983;
                            Str *_t1984 = Str_lit("\"", 2ULL);
                            (void)_t1984;
                            Array_set(_va40, &(U64){_t1983}, _t1984);
                            ;
                            print(_va40);
                        } else {
                            Bool _t2021; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1939); _t2021 = *_hp; free(_hp); }
                            (void)_t2021;
                            if (_t2021) {
                                Declaration *decl = ExprData_get_Decl(_sw1939);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1985 = Str_lit("Str", 3ULL);
                                    (void)_t1985;
                                    U64 _t1986; { U64 *_hp = (U64 *)Str_size(); _t1986 = *_hp; free(_hp); }
                                    (void)_t1986;
                                    U64 _t1987 = 1;
                                    (void)_t1987;
                                    Array *_va41 = Array_new(_t1985, &(U64){_t1986}, &(U64){_t1987});
                                    (void)_va41;
                                    Str_delete(_t1985, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1988 = 0;
                                    (void)_t1988;
                                    Str *_t1989 = Str_lit(" mut", 4ULL);
                                    (void)_t1989;
                                    Array_set(_va41, &(U64){_t1988}, _t1989);
                                    ;
                                    print(_va41);
                                }
                                Str *_t1990 = Str_lit("Str", 3ULL);
                                (void)_t1990;
                                U64 _t1991; { U64 *_hp = (U64 *)Str_size(); _t1991 = *_hp; free(_hp); }
                                (void)_t1991;
                                U64 _t1992 = 2;
                                (void)_t1992;
                                Array *_va42 = Array_new(_t1990, &(U64){_t1991}, &(U64){_t1992});
                                (void)_va42;
                                Str_delete(_t1990, &(Bool){1});
                                ;
                                ;
                                U64 _t1993 = 0;
                                (void)_t1993;
                                Str *_t1994 = Str_lit(" ", 1ULL);
                                (void)_t1994;
                                Array_set(_va42, &(U64){_t1993}, _t1994);
                                ;
                                U64 _t1995 = 1;
                                (void)_t1995;
                                Str *_t1996 = Str_clone(&decl->name);
                                (void)_t1996;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va42, &(U64){_t1995}, _t1996);
                                ;
                                print(_va42);
                            } else {
                                Bool _t2020; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1939); _t2020 = *_hp; free(_hp); }
                                (void)_t2020;
                                if (_t2020) {
                                    Str *s = ExprData_get_Assign(_sw1939);
                                    (void)s;
                                    Str *_t1997 = Str_lit("Str", 3ULL);
                                    (void)_t1997;
                                    U64 _t1998; { U64 *_hp = (U64 *)Str_size(); _t1998 = *_hp; free(_hp); }
                                    (void)_t1998;
                                    U64 _t1999 = 2;
                                    (void)_t1999;
                                    Array *_va43 = Array_new(_t1997, &(U64){_t1998}, &(U64){_t1999});
                                    (void)_va43;
                                    Str_delete(_t1997, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2000 = 0;
                                    (void)_t2000;
                                    Str *_t2001 = Str_lit(" ", 1ULL);
                                    (void)_t2001;
                                    Array_set(_va43, &(U64){_t2000}, _t2001);
                                    ;
                                    U64 _t2002 = 1;
                                    (void)_t2002;
                                    Str *_t2003 = Str_clone(s);
                                    (void)_t2003;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va43, &(U64){_t2002}, _t2003);
                                    ;
                                    print(_va43);
                                } else {
                                    Bool _t2019; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1939); _t2019 = *_hp; free(_hp); }
                                    (void)_t2019;
                                    if (_t2019) {
                                        Str *s = ExprData_get_NamedArg(_sw1939);
                                        (void)s;
                                        Str *_t2004 = Str_lit("Str", 3ULL);
                                        (void)_t2004;
                                        U64 _t2005; { U64 *_hp = (U64 *)Str_size(); _t2005 = *_hp; free(_hp); }
                                        (void)_t2005;
                                        U64 _t2006 = 2;
                                        (void)_t2006;
                                        Array *_va44 = Array_new(_t2004, &(U64){_t2005}, &(U64){_t2006});
                                        (void)_va44;
                                        Str_delete(_t2004, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2007 = 0;
                                        (void)_t2007;
                                        Str *_t2008 = Str_lit(" ", 1ULL);
                                        (void)_t2008;
                                        Array_set(_va44, &(U64){_t2007}, _t2008);
                                        ;
                                        U64 _t2009 = 1;
                                        (void)_t2009;
                                        Str *_t2010 = Str_clone(s);
                                        (void)_t2010;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va44, &(U64){_t2009}, _t2010);
                                        ;
                                        print(_va44);
                                    } else {
                                        Bool _t2018; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1939); _t2018 = *_hp; free(_hp); }
                                        (void)_t2018;
                                        if (_t2018) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1939);
                                            (void)fdef;
                                            Str *_t2011 = Str_lit("Str", 3ULL);
                                            (void)_t2011;
                                            U64 _t2012; { U64 *_hp = (U64 *)Str_size(); _t2012 = *_hp; free(_hp); }
                                            (void)_t2012;
                                            U64 _t2013 = 2;
                                            (void)_t2013;
                                            Array *_va45 = Array_new(_t2011, &(U64){_t2012}, &(U64){_t2013});
                                            (void)_va45;
                                            Str_delete(_t2011, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2014 = 0;
                                            (void)_t2014;
                                            Str *_t2015 = Str_lit(" ", 1ULL);
                                            (void)_t2015;
                                            Array_set(_va45, &(U64){_t2014}, _t2015);
                                            ;
                                            U64 _t2016 = 1;
                                            (void)_t2016;
                                            Str *_t2017 = func_type_name(&fdef->func_type);
                                            (void)_t2017;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va45, &(U64){_t2016}, _t2017);
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
        ExprData_delete(_sw1939, &(Bool){1});
        ;
    }
    U64 _t2074; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2074 = *_hp; free(_hp); }
    (void)_t2074;
    U64 _t2075 = 0;
    (void)_t2075;
    Bool _t2076; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2074}, &(U64){_t2075}); _t2076 = *_hp; free(_hp); }
    (void)_t2076;
    ;
    ;
    if (_t2076) {
        Str *_t2060 = Str_lit("Str", 3ULL);
        (void)_t2060;
        U64 _t2061; { U64 *_hp = (U64 *)Str_size(); _t2061 = *_hp; free(_hp); }
        (void)_t2061;
        U64 _t2062 = 1;
        (void)_t2062;
        Array *_va47 = Array_new(_t2060, &(U64){_t2061}, &(U64){_t2062});
        (void)_va47;
        Str_delete(_t2060, &(Bool){1});
        ;
        ;
        U64 _t2063 = 0;
        (void)_t2063;
        Str *_t2064 = Str_lit("", 0ULL);
        (void)_t2064;
        Array_set(_va47, &(U64){_t2063}, _t2064);
        ;
        println(_va47);
        {
            U64 _fi2027 = 0;
            (void)_fi2027;
            while (1) {
                U64 _t2029 = 0;
                (void)_t2029;
                U64 _t2030; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2030 = *_hp; free(_hp); }
                (void)_t2030;
                Range *_t2031 = Range_new(_t2029, _t2030);
                (void)_t2031;
                ;
                ;
                U64 _t2032; { U64 *_hp = (U64 *)Range_len(_t2031); _t2032 = *_hp; free(_hp); }
                (void)_t2032;
                Range_delete(_t2031, &(Bool){1});
                Bool _wcond2028; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2027}, &(U64){_t2032}); _wcond2028 = *_hp; free(_hp); }
                (void)_wcond2028;
                ;
                if (_wcond2028) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2033 = 0;
                (void)_t2033;
                U64 _t2034; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2034 = *_hp; free(_hp); }
                (void)_t2034;
                Range *_t2035 = Range_new(_t2033, _t2034);
                (void)_t2035;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2035, _fi2027); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2035, &(Bool){1});
                U64 _t2036 = 1;
                (void)_t2036;
                U64 _t2037 = U64_add(_fi2027, _t2036);
                (void)_t2037;
                ;
                _fi2027 = _t2037;
                ;
                I64 *_t2038 = malloc(sizeof(I64)); *_t2038 = U64_to_i64(i);
                (void)_t2038;
                ;
                U32 _t2039 = 1;
                (void)_t2039;
                Expr *_t2040 = Expr_child(e, _t2038);
                (void)_t2040;
                U32 _t2041 = U32_add(indent, _t2039);
                (void)_t2041;
                ;
                ast_print(_t2040, _t2041);
                I64_delete(_t2038, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2042 = 0;
            (void)_fi2042;
            while (1) {
                I64 _t2044 = U32_to_i64(indent);
                (void)_t2044;
                U64 _t2045 = 0;
                (void)_t2045;
                U64 _t2046 = I64_to_u64(_t2044);
                (void)_t2046;
                ;
                Range *_t2047 = Range_new(_t2045, _t2046);
                (void)_t2047;
                ;
                ;
                U64 _t2048; { U64 *_hp = (U64 *)Range_len(_t2047); _t2048 = *_hp; free(_hp); }
                (void)_t2048;
                Range_delete(_t2047, &(Bool){1});
                Bool _wcond2043; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2042}, &(U64){_t2048}); _wcond2043 = *_hp; free(_hp); }
                (void)_wcond2043;
                ;
                if (_wcond2043) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2049 = U32_to_i64(indent);
                (void)_t2049;
                U64 _t2050 = 0;
                (void)_t2050;
                U64 _t2051 = I64_to_u64(_t2049);
                (void)_t2051;
                ;
                Range *_t2052 = Range_new(_t2050, _t2051);
                (void)_t2052;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2052, _fi2042); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2052, &(Bool){1});
                ;
                U64 _t2053 = 1;
                (void)_t2053;
                U64 _t2054 = U64_add(_fi2042, _t2053);
                (void)_t2054;
                ;
                _fi2042 = _t2054;
                ;
                Str *_t2055 = Str_lit("Str", 3ULL);
                (void)_t2055;
                U64 _t2056; { U64 *_hp = (U64 *)Str_size(); _t2056 = *_hp; free(_hp); }
                (void)_t2056;
                U64 _t2057 = 1;
                (void)_t2057;
                Array *_va46 = Array_new(_t2055, &(U64){_t2056}, &(U64){_t2057});
                (void)_va46;
                Str_delete(_t2055, &(Bool){1});
                ;
                ;
                U64 _t2058 = 0;
                (void)_t2058;
                Str *_t2059 = Str_lit("  ", 2ULL);
                (void)_t2059;
                Array_set(_va46, &(U64){_t2058}, _t2059);
                ;
                print(_va46);
            }
            ;
        }
    }
    ;
    Str *_t2077 = Str_lit("Str", 3ULL);
    (void)_t2077;
    U64 _t2078; { U64 *_hp = (U64 *)Str_size(); _t2078 = *_hp; free(_hp); }
    (void)_t2078;
    U64 _t2079 = 1;
    (void)_t2079;
    Array *_va49 = Array_new(_t2077, &(U64){_t2078}, &(U64){_t2079});
    (void)_va49;
    Str_delete(_t2077, &(Bool){1});
    ;
    ;
    U64 _t2080 = 0;
    (void)_t2080;
    Str *_t2081 = Str_lit(")", 1ULL);
    (void)_t2081;
    Array_set(_va49, &(U64){_t2080}, _t2081);
    ;
    println(_va49);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2103 = malloc(sizeof(I64));
    *_t2103 = 0;
    (void)_t2103;
    Expr *body = Expr_child(enum_def, _t2103);
    (void)body;
    {
        U64 _fi2082 = 0;
        (void)_fi2082;
        while (1) {
            I64 _t2090; { I64 *_hp = (I64 *)Expr_child_count(body); _t2090 = *_hp; free(_hp); }
            (void)_t2090;
            U64 _t2091 = 0;
            (void)_t2091;
            U64 _t2092 = I64_to_u64(_t2090);
            (void)_t2092;
            ;
            Range *_t2093 = Range_new(_t2091, _t2092);
            (void)_t2093;
            ;
            ;
            U64 _t2094; { U64 *_hp = (U64 *)Range_len(_t2093); _t2094 = *_hp; free(_hp); }
            (void)_t2094;
            Range_delete(_t2093, &(Bool){1});
            Bool _wcond2083; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2082}, &(U64){_t2094}); _wcond2083 = *_hp; free(_hp); }
            (void)_wcond2083;
            ;
            if (_wcond2083) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2095; { I64 *_hp = (I64 *)Expr_child_count(body); _t2095 = *_hp; free(_hp); }
            (void)_t2095;
            U64 _t2096 = 0;
            (void)_t2096;
            U64 _t2097 = I64_to_u64(_t2095);
            (void)_t2097;
            ;
            Range *_t2098 = Range_new(_t2096, _t2097);
            (void)_t2098;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2098, _fi2082); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2098, &(Bool){1});
            U64 _t2099 = 1;
            (void)_t2099;
            U64 _t2100 = U64_add(_fi2082, _t2099);
            (void)_t2100;
            ;
            _fi2082 = _t2100;
            ;
            I64 *_t2101 = malloc(sizeof(I64)); *_t2101 = U64_to_i64(i);
            (void)_t2101;
            ;
            Expr *f = Expr_child(body, _t2101);
            (void)f;
            Bool _t2102; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2102 = *_hp; free(_hp); }
            (void)_t2102;
            if (_t2102) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2085; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2085 = *_hp; free(_hp); }
                (void)_t2085;
                U64 _t2086 = 0;
                (void)_t2086;
                Bool _t2087 = Bool_not(decl->is_namespace);
                (void)_t2087;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2088; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2085}, &(U64){_t2086}); _t2088 = *_hp; free(_hp); }
                (void)_t2088;
                ;
                ;
                Bool _t2089 = Bool_and(_t2087, _t2088);
                (void)_t2089;
                ;
                ;
                if (_t2089) {
                    Bool _t2084 = 1;
                    (void)_t2084;
                    ;
                    I64_delete(_t2101, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2084; return _r; }
                }
                ;
            }
            I64_delete(_t2101, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2103, &(Bool){1});
    Bool _t2104 = 0;
    (void)_t2104;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2104; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2124 = malloc(sizeof(I64));
    *_t2124 = 0;
    (void)_t2124;
    Expr *body = Expr_child(enum_def, _t2124);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2105 = 0;
        (void)_fi2105;
        while (1) {
            I64 _t2111; { I64 *_hp = (I64 *)Expr_child_count(body); _t2111 = *_hp; free(_hp); }
            (void)_t2111;
            U64 _t2112 = 0;
            (void)_t2112;
            U64 _t2113 = I64_to_u64(_t2111);
            (void)_t2113;
            ;
            Range *_t2114 = Range_new(_t2112, _t2113);
            (void)_t2114;
            ;
            ;
            U64 _t2115; { U64 *_hp = (U64 *)Range_len(_t2114); _t2115 = *_hp; free(_hp); }
            (void)_t2115;
            Range_delete(_t2114, &(Bool){1});
            Bool _wcond2106; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2105}, &(U64){_t2115}); _wcond2106 = *_hp; free(_hp); }
            (void)_wcond2106;
            ;
            if (_wcond2106) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2116; { I64 *_hp = (I64 *)Expr_child_count(body); _t2116 = *_hp; free(_hp); }
            (void)_t2116;
            U64 _t2117 = 0;
            (void)_t2117;
            U64 _t2118 = I64_to_u64(_t2116);
            (void)_t2118;
            ;
            Range *_t2119 = Range_new(_t2117, _t2118);
            (void)_t2119;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2119, _fi2105); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2119, &(Bool){1});
            U64 _t2120 = 1;
            (void)_t2120;
            U64 _t2121 = U64_add(_fi2105, _t2120);
            (void)_t2121;
            ;
            _fi2105 = _t2121;
            ;
            I64 *_t2122 = malloc(sizeof(I64)); *_t2122 = U64_to_i64(i);
            (void)_t2122;
            ;
            Expr *f = Expr_child(body, _t2122);
            (void)f;
            Bool _t2123; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2123 = *_hp; free(_hp); }
            (void)_t2123;
            if (_t2123) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2110 = Bool_not(decl->is_namespace);
                (void)_t2110;
                if (_t2110) {
                    Bool _t2107; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2107 = *_hp; free(_hp); }
                    (void)_t2107;
                    if (_t2107) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2122, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2108 = 1;
                    (void)_t2108;
                    I32 _t2109 = I32_add(tag, _t2108);
                    (void)_t2109;
                    ;
                    tag = _t2109;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2122, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2124, &(Bool){1});
    ;
    I64 _t2125 = 0;
    (void)_t2125;
    I64 _t2126 = 1;
    (void)_t2126;
    I64 _t2127 = I64_sub(_t2125, _t2126);
    (void)_t2127;
    ;
    ;
    I32 _t2128 = I64_to_i32(_t2127);
    (void)_t2128;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2128; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2148 = malloc(sizeof(I64));
    *_t2148 = 0;
    (void)_t2148;
    Expr *body = Expr_child(enum_def, _t2148);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi2129 = 0;
        (void)_fi2129;
        while (1) {
            I64 _t2135; { I64 *_hp = (I64 *)Expr_child_count(body); _t2135 = *_hp; free(_hp); }
            (void)_t2135;
            U64 _t2136 = 0;
            (void)_t2136;
            U64 _t2137 = I64_to_u64(_t2135);
            (void)_t2137;
            ;
            Range *_t2138 = Range_new(_t2136, _t2137);
            (void)_t2138;
            ;
            ;
            U64 _t2139; { U64 *_hp = (U64 *)Range_len(_t2138); _t2139 = *_hp; free(_hp); }
            (void)_t2139;
            Range_delete(_t2138, &(Bool){1});
            Bool _wcond2130; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2129}, &(U64){_t2139}); _wcond2130 = *_hp; free(_hp); }
            (void)_wcond2130;
            ;
            if (_wcond2130) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2140; { I64 *_hp = (I64 *)Expr_child_count(body); _t2140 = *_hp; free(_hp); }
            (void)_t2140;
            U64 _t2141 = 0;
            (void)_t2141;
            U64 _t2142 = I64_to_u64(_t2140);
            (void)_t2142;
            ;
            Range *_t2143 = Range_new(_t2141, _t2142);
            (void)_t2143;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2143, _fi2129); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2143, &(Bool){1});
            U64 _t2144 = 1;
            (void)_t2144;
            U64 _t2145 = U64_add(_fi2129, _t2144);
            (void)_t2145;
            ;
            _fi2129 = _t2145;
            ;
            I64 *_t2146 = malloc(sizeof(I64)); *_t2146 = U64_to_i64(i);
            (void)_t2146;
            ;
            Expr *f = Expr_child(body, _t2146);
            (void)f;
            Bool _t2147; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2147 = *_hp; free(_hp); }
            (void)_t2147;
            if (_t2147) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2134 = Bool_not(decl->is_namespace);
                (void)_t2134;
                if (_t2134) {
                    Bool _t2131 = I32_eq(idx, tag);
                    (void)_t2131;
                    if (_t2131) {
                        ;
                        ;
                        I64_delete(_t2146, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2132 = 1;
                    (void)_t2132;
                    I32 _t2133 = I32_add(idx, _t2132);
                    (void)_t2133;
                    ;
                    idx = _t2133;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2146, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2148, &(Bool){1});
    ;
    Str *_t2149 = Str_lit("", 0ULL);
    (void)_t2149;
    return _t2149;
}

