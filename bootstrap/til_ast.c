#include "til_ast.h"

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

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    (void)self;
    U32 _t1385 = U32_clone(&self->nparam);
    (void)_t1385;
    I32 _t1386 = I32_clone(&self->variadic_index);
    (void)_t1386;
    I32 _t1387 = I32_clone(&self->kwargs_index);
    (void)_t1387;
    Bool _t1388 = Bool_clone(&self->return_is_ref);
    (void)_t1388;
    Bool _t1389 = Bool_clone(&self->return_is_shallow);
    (void)_t1389;
    FunctionDef *_t1390 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1390->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_names); _t1390->param_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_types); _t1390->param_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_muts); _t1390->param_muts = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_owns); _t1390->param_owns = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_shallows); _t1390->param_shallows = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->param_fn_sigs); _t1390->param_fn_sigs = *_ca; free(_ca); }
    _t1390->nparam = _t1385;
    { Map *_ca = Map_clone(&self->param_defaults); _t1390->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1390->return_type = *_ca; free(_ca); }
    _t1390->variadic_index = _t1386;
    _t1390->kwargs_index = _t1387;
    _t1390->return_is_ref = _t1388;
    _t1390->return_is_shallow = _t1389;
    (void)_t1390;
    ;
    ;
    ;
    ;
    ;
    return _t1390;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1391 = 0;
    (void)_t1391;
    FuncType_delete(&self->func_type, &(Bool){_t1391});
    ;
    Bool _t1392 = 0;
    (void)_t1392;
    Vec_delete(&self->param_names, &(Bool){_t1392});
    ;
    Bool _t1393 = 0;
    (void)_t1393;
    Vec_delete(&self->param_types, &(Bool){_t1393});
    ;
    Bool _t1394 = 0;
    (void)_t1394;
    Vec_delete(&self->param_muts, &(Bool){_t1394});
    ;
    Bool _t1395 = 0;
    (void)_t1395;
    Vec_delete(&self->param_owns, &(Bool){_t1395});
    ;
    Bool _t1396 = 0;
    (void)_t1396;
    Vec_delete(&self->param_shallows, &(Bool){_t1396});
    ;
    Bool _t1397 = 0;
    (void)_t1397;
    Vec_delete(&self->param_fn_sigs, &(Bool){_t1397});
    ;
    Bool _t1398 = 0;
    (void)_t1398;
    U32_delete(&self->nparam, &(Bool){_t1398});
    ;
    Bool _t1399 = 0;
    (void)_t1399;
    Map_delete(&self->param_defaults, &(Bool){_t1399});
    ;
    Bool _t1400 = 0;
    (void)_t1400;
    Str_delete(&self->return_type, &(Bool){_t1400});
    ;
    Bool _t1401 = 0;
    (void)_t1401;
    I32_delete(&self->variadic_index, &(Bool){_t1401});
    ;
    Bool _t1402 = 0;
    (void)_t1402;
    I32_delete(&self->kwargs_index, &(Bool){_t1402});
    ;
    Bool _t1403 = 0;
    (void)_t1403;
    Bool_delete(&self->return_is_ref, &(Bool){_t1403});
    ;
    Bool _t1404 = 0;
    (void)_t1404;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1404});
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
    Bool _t1787 = 0;
    (void)_t1787;
    ExprData_delete(&self->data, &(Bool){_t1787});
    ;
    Bool _t1788 = 0;
    (void)_t1788;
    TilType_delete(&self->til_type, &(Bool){_t1788});
    ;
    Bool _t1789 = 0;
    (void)_t1789;
    Str_delete(&self->struct_name, &(Bool){_t1789});
    ;
    Bool _t1790 = 0;
    (void)_t1790;
    Bool_delete(&self->is_own_arg, &(Bool){_t1790});
    ;
    Bool _t1791 = 0;
    (void)_t1791;
    Bool_delete(&self->is_splat, &(Bool){_t1791});
    ;
    Bool _t1792 = 0;
    (void)_t1792;
    Bool_delete(&self->is_own_field, &(Bool){_t1792});
    ;
    Bool _t1793 = 0;
    (void)_t1793;
    Bool_delete(&self->is_ref_field, &(Bool){_t1793});
    ;
    Bool _t1794 = 0;
    (void)_t1794;
    Bool_delete(&self->is_ns_field, &(Bool){_t1794});
    ;
    Bool _t1795 = 0;
    (void)_t1795;
    Bool_delete(&self->is_ext, &(Bool){_t1795});
    ;
    Bool _t1796 = 0;
    (void)_t1796;
    Bool_delete(&self->is_core, &(Bool){_t1796});
    ;
    Bool _t1797 = 0;
    (void)_t1797;
    Bool_delete(&self->save_old_delete, &(Bool){_t1797});
    ;
    Bool _t1798 = 0;
    (void)_t1798;
    I32_delete(&self->total_struct_size, &(Bool){_t1798});
    ;
    Bool _t1799 = 0;
    (void)_t1799;
    I32_delete(&self->variadic_index, &(Bool){_t1799});
    ;
    Bool _t1800 = 0;
    (void)_t1800;
    U32_delete(&self->variadic_count, &(Bool){_t1800});
    ;
    Bool _t1801 = 0;
    (void)_t1801;
    I32_delete(&self->kwargs_index, &(Bool){_t1801});
    ;
    Bool _t1802 = 0;
    (void)_t1802;
    U32_delete(&self->kwargs_count, &(Bool){_t1802});
    ;
    Bool _t1803 = 0;
    (void)_t1803;
    Vec_delete(&self->children, &(Bool){_t1803});
    ;
    Bool _t1804 = 0;
    (void)_t1804;
    U32_delete(&self->line, &(Bool){_t1804});
    ;
    Bool _t1805 = 0;
    (void)_t1805;
    U32_delete(&self->col, &(Bool){_t1805});
    ;
    Bool _t1806 = 0;
    (void)_t1806;
    Str_delete(&self->path, &(Bool){_t1806});
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
        ExprData *_sw1808 = ExprData_clone(data);
        (void)_sw1808;
        Bool _t1859; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Body()); _t1859 = *_hp; free(_hp); }
        (void)_t1859;
        if (_t1859) {
            Str *_t1809 = Str_lit("body", 4ULL);
            (void)_t1809;
            ExprData_delete(_sw1808, &(Bool){1});
            ;
            return _t1809;
        } else {
            Bool _t1858; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1808); _t1858 = *_hp; free(_hp); }
            (void)_t1858;
            if (_t1858) {
                Str *_t1810 = Str_lit("str", 3ULL);
                (void)_t1810;
                ;
                ExprData_delete(_sw1808, &(Bool){1});
                ;
                return _t1810;
            } else {
                Bool _t1857; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1808); _t1857 = *_hp; free(_hp); }
                (void)_t1857;
                if (_t1857) {
                    Str *_t1811 = Str_lit("num", 3ULL);
                    (void)_t1811;
                    ;
                    ;
                    ExprData_delete(_sw1808, &(Bool){1});
                    ;
                    return _t1811;
                } else {
                    Bool _t1856; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1808); _t1856 = *_hp; free(_hp); }
                    (void)_t1856;
                    if (_t1856) {
                        Str *_t1812 = Str_lit("bool", 4ULL);
                        (void)_t1812;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1808, &(Bool){1});
                        ;
                        return _t1812;
                    } else {
                        Bool _t1855; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_LiteralNull()); _t1855 = *_hp; free(_hp); }
                        (void)_t1855;
                        if (_t1855) {
                            Str *_t1813 = Str_lit("null", 4ULL);
                            (void)_t1813;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1808, &(Bool){1});
                            ;
                            return _t1813;
                        } else {
                            Bool _t1854; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1808); _t1854 = *_hp; free(_hp); }
                            (void)_t1854;
                            if (_t1854) {
                                Str *_t1814 = Str_lit("ident", 5ULL);
                                (void)_t1814;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1808, &(Bool){1});
                                ;
                                return _t1814;
                            } else {
                                Bool _t1853; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1808); _t1853 = *_hp; free(_hp); }
                                (void)_t1853;
                                if (_t1853) {
                                    Str *_t1815 = Str_lit("decl", 4ULL);
                                    (void)_t1815;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1808, &(Bool){1});
                                    ;
                                    return _t1815;
                                } else {
                                    Bool _t1852; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1808); _t1852 = *_hp; free(_hp); }
                                    (void)_t1852;
                                    if (_t1852) {
                                        Str *_t1816 = Str_lit("assign", 6ULL);
                                        (void)_t1816;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1808, &(Bool){1});
                                        ;
                                        return _t1816;
                                    } else {
                                        Bool _t1851; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_FCall()); _t1851 = *_hp; free(_hp); }
                                        (void)_t1851;
                                        if (_t1851) {
                                            Str *_t1817 = Str_lit("fcall", 5ULL);
                                            (void)_t1817;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1808, &(Bool){1});
                                            ;
                                            return _t1817;
                                        } else {
                                            Bool _t1850; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1808); _t1850 = *_hp; free(_hp); }
                                            (void)_t1850;
                                            if (_t1850) {
                                                Str *_t1818 = Str_lit("func_def", 8ULL);
                                                (void)_t1818;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1808, &(Bool){1});
                                                ;
                                                return _t1818;
                                            } else {
                                                Bool _t1849; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_StructDef()); _t1849 = *_hp; free(_hp); }
                                                (void)_t1849;
                                                if (_t1849) {
                                                    Str *_t1819 = Str_lit("struct_def", 10ULL);
                                                    (void)_t1819;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw1808, &(Bool){1});
                                                    ;
                                                    return _t1819;
                                                } else {
                                                    Bool _t1848; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_EnumDef()); _t1848 = *_hp; free(_hp); }
                                                    (void)_t1848;
                                                    if (_t1848) {
                                                        Str *_t1820 = Str_lit("enum_def", 8ULL);
                                                        (void)_t1820;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw1808, &(Bool){1});
                                                        ;
                                                        return _t1820;
                                                    } else {
                                                        Bool _t1847; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1808); _t1847 = *_hp; free(_hp); }
                                                        (void)_t1847;
                                                        if (_t1847) {
                                                            Str *_t1821 = Str_lit("field_access", 12ULL);
                                                            (void)_t1821;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw1808, &(Bool){1});
                                                            ;
                                                            return _t1821;
                                                        } else {
                                                            Bool _t1846; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1808); _t1846 = *_hp; free(_hp); }
                                                            (void)_t1846;
                                                            if (_t1846) {
                                                                Str *_t1822 = Str_lit("field_assign", 12ULL);
                                                                (void)_t1822;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw1808, &(Bool){1});
                                                                ;
                                                                return _t1822;
                                                            } else {
                                                                Bool _t1845; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Return()); _t1845 = *_hp; free(_hp); }
                                                                (void)_t1845;
                                                                if (_t1845) {
                                                                    Str *_t1823 = Str_lit("return", 6ULL);
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
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw1808, &(Bool){1});
                                                                    ;
                                                                    return _t1823;
                                                                } else {
                                                                    Bool _t1844; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_If()); _t1844 = *_hp; free(_hp); }
                                                                    (void)_t1844;
                                                                    if (_t1844) {
                                                                        Str *_t1824 = Str_lit("if", 2ULL);
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
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw1808, &(Bool){1});
                                                                        ;
                                                                        return _t1824;
                                                                    } else {
                                                                        Bool _t1843; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_While()); _t1843 = *_hp; free(_hp); }
                                                                        (void)_t1843;
                                                                        if (_t1843) {
                                                                            Str *_t1825 = Str_lit("while", 5ULL);
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
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw1808, &(Bool){1});
                                                                            ;
                                                                            return _t1825;
                                                                        } else {
                                                                            Bool _t1842; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1808); _t1842 = *_hp; free(_hp); }
                                                                            (void)_t1842;
                                                                            if (_t1842) {
                                                                                Str *_t1826 = Str_lit("for_in", 6ULL);
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
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw1808, &(Bool){1});
                                                                                ;
                                                                                return _t1826;
                                                                            } else {
                                                                                Bool _t1841; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1808); _t1841 = *_hp; free(_hp); }
                                                                                (void)_t1841;
                                                                                if (_t1841) {
                                                                                    Str *_t1827 = Str_lit("named_arg", 9ULL);
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
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw1808, &(Bool){1});
                                                                                    ;
                                                                                    return _t1827;
                                                                                } else {
                                                                                    Bool _t1840; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Break()); _t1840 = *_hp; free(_hp); }
                                                                                    (void)_t1840;
                                                                                    if (_t1840) {
                                                                                        Str *_t1828 = Str_lit("break", 5ULL);
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
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw1808, &(Bool){1});
                                                                                        ;
                                                                                        return _t1828;
                                                                                    } else {
                                                                                        Bool _t1839; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Continue()); _t1839 = *_hp; free(_hp); }
                                                                                        (void)_t1839;
                                                                                        if (_t1839) {
                                                                                            Str *_t1829 = Str_lit("continue", 8ULL);
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
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw1808, &(Bool){1});
                                                                                            ;
                                                                                            return _t1829;
                                                                                        } else {
                                                                                            Bool _t1838; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_MapLit()); _t1838 = *_hp; free(_hp); }
                                                                                            (void)_t1838;
                                                                                            if (_t1838) {
                                                                                                Str *_t1830 = Str_lit("map_lit", 7ULL);
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw1808, &(Bool){1});
                                                                                                ;
                                                                                                return _t1830;
                                                                                            } else {
                                                                                                Bool _t1837; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_SetLit()); _t1837 = *_hp; free(_hp); }
                                                                                                (void)_t1837;
                                                                                                if (_t1837) {
                                                                                                    Str *_t1831 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw1808, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1831;
                                                                                                } else {
                                                                                                    Bool _t1836; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Switch()); _t1836 = *_hp; free(_hp); }
                                                                                                    (void)_t1836;
                                                                                                    if (_t1836) {
                                                                                                        Str *_t1832 = Str_lit("switch", 6ULL);
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw1808, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1832;
                                                                                                    } else {
                                                                                                        Bool _t1835; { Bool *_hp = (Bool *)ExprData_eq(_sw1808, ExprData_Case()); _t1835 = *_hp; free(_hp); }
                                                                                                        (void)_t1835;
                                                                                                        if (_t1835) {
                                                                                                            Str *_t1833 = Str_lit("case", 4ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1808, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1833;
                                                                                                        } else {
                                                                                                            Str *_t1834 = Str_lit("?", 1ULL);
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1808, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1834;
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
        ExprData_delete(_sw1808, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1860 = FuncType_clone(ft);
        (void)_sw1860;
        Bool _t1873; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_Func()); _t1873 = *_hp; free(_hp); }
        (void)_t1873;
        if (_t1873) {
            Str *_t1861 = Str_lit("func", 4ULL);
            (void)_t1861;
            FuncType_delete(_sw1860, &(Bool){1});
            ;
            return _t1861;
        } else {
            Bool _t1872; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_Proc()); _t1872 = *_hp; free(_hp); }
            (void)_t1872;
            if (_t1872) {
                Str *_t1862 = Str_lit("proc", 4ULL);
                (void)_t1862;
                ;
                FuncType_delete(_sw1860, &(Bool){1});
                ;
                return _t1862;
            } else {
                Bool _t1871; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_Test()); _t1871 = *_hp; free(_hp); }
                (void)_t1871;
                if (_t1871) {
                    Str *_t1863 = Str_lit("test", 4ULL);
                    (void)_t1863;
                    ;
                    ;
                    FuncType_delete(_sw1860, &(Bool){1});
                    ;
                    return _t1863;
                } else {
                    Bool _t1870; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_Macro()); _t1870 = *_hp; free(_hp); }
                    (void)_t1870;
                    if (_t1870) {
                        Str *_t1864 = Str_lit("macro", 5ULL);
                        (void)_t1864;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1860, &(Bool){1});
                        ;
                        return _t1864;
                    } else {
                        Bool _t1869; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_ExtFunc()); _t1869 = *_hp; free(_hp); }
                        (void)_t1869;
                        if (_t1869) {
                            Str *_t1865 = Str_lit("ext_func", 8ULL);
                            (void)_t1865;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1860, &(Bool){1});
                            ;
                            return _t1865;
                        } else {
                            Bool _t1868; { Bool *_hp = (Bool *)FuncType_eq(_sw1860, FuncType_ExtProc()); _t1868 = *_hp; free(_hp); }
                            (void)_t1868;
                            if (_t1868) {
                                Str *_t1866 = Str_lit("ext_proc", 8ULL);
                                (void)_t1866;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1860, &(Bool){1});
                                ;
                                return _t1866;
                            } else {
                                Str *_t1867 = Str_lit("?", 1ULL);
                                (void)_t1867;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1860, &(Bool){1});
                                ;
                                return _t1867;
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
        FuncType_delete(_sw1860, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi1874 = 0;
        (void)_fi1874;
        while (1) {
            I64 _t1876 = U32_to_i64(indent);
            (void)_t1876;
            U64 _t1877 = 0;
            (void)_t1877;
            U64 _t1878 = I64_to_u64(_t1876);
            (void)_t1878;
            ;
            Range *_t1879 = Range_new(_t1877, _t1878);
            (void)_t1879;
            ;
            ;
            U64 _t1880; { U64 *_hp = (U64 *)Range_len(_t1879); _t1880 = *_hp; free(_hp); }
            (void)_t1880;
            Range_delete(_t1879, &(Bool){1});
            Bool _wcond1875; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1874}, &(U64){_t1880}); _wcond1875 = *_hp; free(_hp); }
            (void)_wcond1875;
            ;
            if (_wcond1875) {
            } else {
                ;
                break;
            }
            ;
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
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1884, _fi1874); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1884, &(Bool){1});
            ;
            U64 _t1885 = 1;
            (void)_t1885;
            U64 _t1886 = U64_add(_fi1874, _t1885);
            (void)_t1886;
            ;
            _fi1874 = _t1886;
            ;
            Str *_t1887 = Str_lit("Str", 3ULL);
            (void)_t1887;
            U64 _t1888; { U64 *_hp = (U64 *)Str_size(); _t1888 = *_hp; free(_hp); }
            (void)_t1888;
            U64 _t1889 = 1;
            (void)_t1889;
            Array *_va34 = Array_new(_t1887, &(U64){_t1888}, &(U64){_t1889});
            (void)_va34;
            Str_delete(_t1887, &(Bool){1});
            ;
            ;
            U64 _t1890 = 0;
            (void)_t1890;
            Str *_t1891 = Str_lit("  ", 2ULL);
            (void)_t1891;
            Array_set(_va34, &(U64){_t1890}, _t1891);
            ;
            print(_va34);
        }
        ;
    }
    Str *_t2025 = Str_lit("Str", 3ULL);
    (void)_t2025;
    U64 _t2026; { U64 *_hp = (U64 *)Str_size(); _t2026 = *_hp; free(_hp); }
    (void)_t2026;
    U64 _t2027 = 2;
    (void)_t2027;
    Array *_va48 = Array_new(_t2025, &(U64){_t2026}, &(U64){_t2027});
    (void)_va48;
    Str_delete(_t2025, &(Bool){1});
    ;
    ;
    U64 _t2028 = 0;
    (void)_t2028;
    Str *_t2029 = Str_lit("(", 1ULL);
    (void)_t2029;
    Array_set(_va48, &(U64){_t2028}, _t2029);
    ;
    U64 _t2030 = 1;
    (void)_t2030;
    Str *_t2031 = node_name(&e->data);
    (void)_t2031;
    Array_set(_va48, &(U64){_t2030}, _t2031);
    ;
    print(_va48);
    Bool _t2032; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2032 = *_hp; free(_hp); }
    (void)_t2032;
    Bool _t2033 = Bool_not(_t2032);
    (void)_t2033;
    ;
    if (_t2033) {
        Str *_t1892 = Str_lit("Str", 3ULL);
        (void)_t1892;
        U64 _t1893; { U64 *_hp = (U64 *)Str_size(); _t1893 = *_hp; free(_hp); }
        (void)_t1893;
        U64 _t1894 = 2;
        (void)_t1894;
        Array *_va35 = Array_new(_t1892, &(U64){_t1893}, &(U64){_t1894});
        (void)_va35;
        Str_delete(_t1892, &(Bool){1});
        ;
        ;
        U64 _t1895 = 0;
        (void)_t1895;
        Str *_t1896 = Str_lit(":", 1ULL);
        (void)_t1896;
        Array_set(_va35, &(U64){_t1895}, _t1896);
        ;
        U64 _t1897 = 1;
        (void)_t1897;
        Str *_t1898 = til_type_name_c(&e->til_type);
        (void)_t1898;
        Array_set(_va35, &(U64){_t1897}, _t1898);
        ;
        print(_va35);
    }
    ;
    {
        ExprData *_sw1899 = ExprData_clone(&e->data);
        (void)_sw1899;
        Bool _t1986; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1899); _t1986 = *_hp; free(_hp); }
        (void)_t1986;
        if (_t1986) {
            Str *s = ExprData_get_Ident(_sw1899);
            (void)s;
            Str *_t1900 = Str_lit("Str", 3ULL);
            (void)_t1900;
            U64 _t1901; { U64 *_hp = (U64 *)Str_size(); _t1901 = *_hp; free(_hp); }
            (void)_t1901;
            U64 _t1902 = 3;
            (void)_t1902;
            Array *_va36 = Array_new(_t1900, &(U64){_t1901}, &(U64){_t1902});
            (void)_va36;
            Str_delete(_t1900, &(Bool){1});
            ;
            ;
            U64 _t1903 = 0;
            (void)_t1903;
            Str *_t1904 = Str_lit(" \"", 3ULL);
            (void)_t1904;
            Array_set(_va36, &(U64){_t1903}, _t1904);
            ;
            U64 _t1905 = 1;
            (void)_t1905;
            Str *_t1906 = Str_clone(s);
            (void)_t1906;
            Str_delete(s, &(Bool){1});
            Array_set(_va36, &(U64){_t1905}, _t1906);
            ;
            U64 _t1907 = 2;
            (void)_t1907;
            Str *_t1908 = Str_lit("\"", 2ULL);
            (void)_t1908;
            Array_set(_va36, &(U64){_t1907}, _t1908);
            ;
            print(_va36);
        } else {
            Bool _t1985; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1899); _t1985 = *_hp; free(_hp); }
            (void)_t1985;
            if (_t1985) {
                Str *s = ExprData_get_LiteralStr(_sw1899);
                (void)s;
                Str *_t1909 = Str_lit("Str", 3ULL);
                (void)_t1909;
                U64 _t1910; { U64 *_hp = (U64 *)Str_size(); _t1910 = *_hp; free(_hp); }
                (void)_t1910;
                U64 _t1911 = 3;
                (void)_t1911;
                Array *_va37 = Array_new(_t1909, &(U64){_t1910}, &(U64){_t1911});
                (void)_va37;
                Str_delete(_t1909, &(Bool){1});
                ;
                ;
                U64 _t1912 = 0;
                (void)_t1912;
                Str *_t1913 = Str_lit(" \"", 3ULL);
                (void)_t1913;
                Array_set(_va37, &(U64){_t1912}, _t1913);
                ;
                U64 _t1914 = 1;
                (void)_t1914;
                Str *_t1915 = Str_clone(s);
                (void)_t1915;
                Str_delete(s, &(Bool){1});
                Array_set(_va37, &(U64){_t1914}, _t1915);
                ;
                U64 _t1916 = 2;
                (void)_t1916;
                Str *_t1917 = Str_lit("\"", 2ULL);
                (void)_t1917;
                Array_set(_va37, &(U64){_t1916}, _t1917);
                ;
                print(_va37);
            } else {
                Bool _t1984; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1899); _t1984 = *_hp; free(_hp); }
                (void)_t1984;
                if (_t1984) {
                    Str *s = ExprData_get_LiteralNum(_sw1899);
                    (void)s;
                    Str *_t1918 = Str_lit("Str", 3ULL);
                    (void)_t1918;
                    U64 _t1919; { U64 *_hp = (U64 *)Str_size(); _t1919 = *_hp; free(_hp); }
                    (void)_t1919;
                    U64 _t1920 = 3;
                    (void)_t1920;
                    Array *_va38 = Array_new(_t1918, &(U64){_t1919}, &(U64){_t1920});
                    (void)_va38;
                    Str_delete(_t1918, &(Bool){1});
                    ;
                    ;
                    U64 _t1921 = 0;
                    (void)_t1921;
                    Str *_t1922 = Str_lit(" \"", 3ULL);
                    (void)_t1922;
                    Array_set(_va38, &(U64){_t1921}, _t1922);
                    ;
                    U64 _t1923 = 1;
                    (void)_t1923;
                    Str *_t1924 = Str_clone(s);
                    (void)_t1924;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va38, &(U64){_t1923}, _t1924);
                    ;
                    U64 _t1925 = 2;
                    (void)_t1925;
                    Str *_t1926 = Str_lit("\"", 2ULL);
                    (void)_t1926;
                    Array_set(_va38, &(U64){_t1925}, _t1926);
                    ;
                    print(_va38);
                } else {
                    Bool _t1983; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1899); _t1983 = *_hp; free(_hp); }
                    (void)_t1983;
                    if (_t1983) {
                        Str *s = ExprData_get_LiteralBool(_sw1899);
                        (void)s;
                        Str *_t1927 = Str_lit("Str", 3ULL);
                        (void)_t1927;
                        U64 _t1928; { U64 *_hp = (U64 *)Str_size(); _t1928 = *_hp; free(_hp); }
                        (void)_t1928;
                        U64 _t1929 = 3;
                        (void)_t1929;
                        Array *_va39 = Array_new(_t1927, &(U64){_t1928}, &(U64){_t1929});
                        (void)_va39;
                        Str_delete(_t1927, &(Bool){1});
                        ;
                        ;
                        U64 _t1930 = 0;
                        (void)_t1930;
                        Str *_t1931 = Str_lit(" \"", 3ULL);
                        (void)_t1931;
                        Array_set(_va39, &(U64){_t1930}, _t1931);
                        ;
                        U64 _t1932 = 1;
                        (void)_t1932;
                        Str *_t1933 = Str_clone(s);
                        (void)_t1933;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va39, &(U64){_t1932}, _t1933);
                        ;
                        U64 _t1934 = 2;
                        (void)_t1934;
                        Str *_t1935 = Str_lit("\"", 2ULL);
                        (void)_t1935;
                        Array_set(_va39, &(U64){_t1934}, _t1935);
                        ;
                        print(_va39);
                    } else {
                        Bool _t1982; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1899); _t1982 = *_hp; free(_hp); }
                        (void)_t1982;
                        if (_t1982) {
                            Str *s = ExprData_get_ForIn(_sw1899);
                            (void)s;
                            Str *_t1936 = Str_lit("Str", 3ULL);
                            (void)_t1936;
                            U64 _t1937; { U64 *_hp = (U64 *)Str_size(); _t1937 = *_hp; free(_hp); }
                            (void)_t1937;
                            U64 _t1938 = 3;
                            (void)_t1938;
                            Array *_va40 = Array_new(_t1936, &(U64){_t1937}, &(U64){_t1938});
                            (void)_va40;
                            Str_delete(_t1936, &(Bool){1});
                            ;
                            ;
                            U64 _t1939 = 0;
                            (void)_t1939;
                            Str *_t1940 = Str_lit(" \"", 3ULL);
                            (void)_t1940;
                            Array_set(_va40, &(U64){_t1939}, _t1940);
                            ;
                            U64 _t1941 = 1;
                            (void)_t1941;
                            Str *_t1942 = Str_clone(s);
                            (void)_t1942;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va40, &(U64){_t1941}, _t1942);
                            ;
                            U64 _t1943 = 2;
                            (void)_t1943;
                            Str *_t1944 = Str_lit("\"", 2ULL);
                            (void)_t1944;
                            Array_set(_va40, &(U64){_t1943}, _t1944);
                            ;
                            print(_va40);
                        } else {
                            Bool _t1981; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1899); _t1981 = *_hp; free(_hp); }
                            (void)_t1981;
                            if (_t1981) {
                                Declaration *decl = ExprData_get_Decl(_sw1899);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1945 = Str_lit("Str", 3ULL);
                                    (void)_t1945;
                                    U64 _t1946; { U64 *_hp = (U64 *)Str_size(); _t1946 = *_hp; free(_hp); }
                                    (void)_t1946;
                                    U64 _t1947 = 1;
                                    (void)_t1947;
                                    Array *_va41 = Array_new(_t1945, &(U64){_t1946}, &(U64){_t1947});
                                    (void)_va41;
                                    Str_delete(_t1945, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1948 = 0;
                                    (void)_t1948;
                                    Str *_t1949 = Str_lit(" mut", 4ULL);
                                    (void)_t1949;
                                    Array_set(_va41, &(U64){_t1948}, _t1949);
                                    ;
                                    print(_va41);
                                }
                                Str *_t1950 = Str_lit("Str", 3ULL);
                                (void)_t1950;
                                U64 _t1951; { U64 *_hp = (U64 *)Str_size(); _t1951 = *_hp; free(_hp); }
                                (void)_t1951;
                                U64 _t1952 = 2;
                                (void)_t1952;
                                Array *_va42 = Array_new(_t1950, &(U64){_t1951}, &(U64){_t1952});
                                (void)_va42;
                                Str_delete(_t1950, &(Bool){1});
                                ;
                                ;
                                U64 _t1953 = 0;
                                (void)_t1953;
                                Str *_t1954 = Str_lit(" ", 1ULL);
                                (void)_t1954;
                                Array_set(_va42, &(U64){_t1953}, _t1954);
                                ;
                                U64 _t1955 = 1;
                                (void)_t1955;
                                Str *_t1956 = Str_clone(&decl->name);
                                (void)_t1956;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va42, &(U64){_t1955}, _t1956);
                                ;
                                print(_va42);
                            } else {
                                Bool _t1980; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1899); _t1980 = *_hp; free(_hp); }
                                (void)_t1980;
                                if (_t1980) {
                                    Str *s = ExprData_get_Assign(_sw1899);
                                    (void)s;
                                    Str *_t1957 = Str_lit("Str", 3ULL);
                                    (void)_t1957;
                                    U64 _t1958; { U64 *_hp = (U64 *)Str_size(); _t1958 = *_hp; free(_hp); }
                                    (void)_t1958;
                                    U64 _t1959 = 2;
                                    (void)_t1959;
                                    Array *_va43 = Array_new(_t1957, &(U64){_t1958}, &(U64){_t1959});
                                    (void)_va43;
                                    Str_delete(_t1957, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1960 = 0;
                                    (void)_t1960;
                                    Str *_t1961 = Str_lit(" ", 1ULL);
                                    (void)_t1961;
                                    Array_set(_va43, &(U64){_t1960}, _t1961);
                                    ;
                                    U64 _t1962 = 1;
                                    (void)_t1962;
                                    Str *_t1963 = Str_clone(s);
                                    (void)_t1963;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va43, &(U64){_t1962}, _t1963);
                                    ;
                                    print(_va43);
                                } else {
                                    Bool _t1979; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1899); _t1979 = *_hp; free(_hp); }
                                    (void)_t1979;
                                    if (_t1979) {
                                        Str *s = ExprData_get_NamedArg(_sw1899);
                                        (void)s;
                                        Str *_t1964 = Str_lit("Str", 3ULL);
                                        (void)_t1964;
                                        U64 _t1965; { U64 *_hp = (U64 *)Str_size(); _t1965 = *_hp; free(_hp); }
                                        (void)_t1965;
                                        U64 _t1966 = 2;
                                        (void)_t1966;
                                        Array *_va44 = Array_new(_t1964, &(U64){_t1965}, &(U64){_t1966});
                                        (void)_va44;
                                        Str_delete(_t1964, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1967 = 0;
                                        (void)_t1967;
                                        Str *_t1968 = Str_lit(" ", 1ULL);
                                        (void)_t1968;
                                        Array_set(_va44, &(U64){_t1967}, _t1968);
                                        ;
                                        U64 _t1969 = 1;
                                        (void)_t1969;
                                        Str *_t1970 = Str_clone(s);
                                        (void)_t1970;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va44, &(U64){_t1969}, _t1970);
                                        ;
                                        print(_va44);
                                    } else {
                                        Bool _t1978; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1899); _t1978 = *_hp; free(_hp); }
                                        (void)_t1978;
                                        if (_t1978) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1899);
                                            (void)fdef;
                                            Str *_t1971 = Str_lit("Str", 3ULL);
                                            (void)_t1971;
                                            U64 _t1972; { U64 *_hp = (U64 *)Str_size(); _t1972 = *_hp; free(_hp); }
                                            (void)_t1972;
                                            U64 _t1973 = 2;
                                            (void)_t1973;
                                            Array *_va45 = Array_new(_t1971, &(U64){_t1972}, &(U64){_t1973});
                                            (void)_va45;
                                            Str_delete(_t1971, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1974 = 0;
                                            (void)_t1974;
                                            Str *_t1975 = Str_lit(" ", 1ULL);
                                            (void)_t1975;
                                            Array_set(_va45, &(U64){_t1974}, _t1975);
                                            ;
                                            U64 _t1976 = 1;
                                            (void)_t1976;
                                            Str *_t1977 = func_type_name(&fdef->func_type);
                                            (void)_t1977;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va45, &(U64){_t1976}, _t1977);
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
        ExprData_delete(_sw1899, &(Bool){1});
        ;
    }
    U64 _t2034; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2034 = *_hp; free(_hp); }
    (void)_t2034;
    U64 _t2035 = 0;
    (void)_t2035;
    Bool _t2036; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2034}, &(U64){_t2035}); _t2036 = *_hp; free(_hp); }
    (void)_t2036;
    ;
    ;
    if (_t2036) {
        Str *_t2020 = Str_lit("Str", 3ULL);
        (void)_t2020;
        U64 _t2021; { U64 *_hp = (U64 *)Str_size(); _t2021 = *_hp; free(_hp); }
        (void)_t2021;
        U64 _t2022 = 1;
        (void)_t2022;
        Array *_va47 = Array_new(_t2020, &(U64){_t2021}, &(U64){_t2022});
        (void)_va47;
        Str_delete(_t2020, &(Bool){1});
        ;
        ;
        U64 _t2023 = 0;
        (void)_t2023;
        Str *_t2024 = Str_lit("", 0ULL);
        (void)_t2024;
        Array_set(_va47, &(U64){_t2023}, _t2024);
        ;
        println(_va47);
        {
            U64 _fi1987 = 0;
            (void)_fi1987;
            while (1) {
                U64 _t1989 = 0;
                (void)_t1989;
                U64 _t1990; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1990 = *_hp; free(_hp); }
                (void)_t1990;
                Range *_t1991 = Range_new(_t1989, _t1990);
                (void)_t1991;
                ;
                ;
                U64 _t1992; { U64 *_hp = (U64 *)Range_len(_t1991); _t1992 = *_hp; free(_hp); }
                (void)_t1992;
                Range_delete(_t1991, &(Bool){1});
                Bool _wcond1988; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1987}, &(U64){_t1992}); _wcond1988 = *_hp; free(_hp); }
                (void)_wcond1988;
                ;
                if (_wcond1988) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1993 = 0;
                (void)_t1993;
                U64 _t1994; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1994 = *_hp; free(_hp); }
                (void)_t1994;
                Range *_t1995 = Range_new(_t1993, _t1994);
                (void)_t1995;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1995, _fi1987); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1995, &(Bool){1});
                U64 _t1996 = 1;
                (void)_t1996;
                U64 _t1997 = U64_add(_fi1987, _t1996);
                (void)_t1997;
                ;
                _fi1987 = _t1997;
                ;
                I64 *_t1998 = malloc(sizeof(I64)); *_t1998 = U64_to_i64(i);
                (void)_t1998;
                ;
                U32 _t1999 = 1;
                (void)_t1999;
                Expr *_t2000 = Expr_child(e, _t1998);
                (void)_t2000;
                U32 _t2001 = U32_add(indent, _t1999);
                (void)_t2001;
                ;
                ast_print(_t2000, _t2001);
                I64_delete(_t1998, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2002 = 0;
            (void)_fi2002;
            while (1) {
                I64 _t2004 = U32_to_i64(indent);
                (void)_t2004;
                U64 _t2005 = 0;
                (void)_t2005;
                U64 _t2006 = I64_to_u64(_t2004);
                (void)_t2006;
                ;
                Range *_t2007 = Range_new(_t2005, _t2006);
                (void)_t2007;
                ;
                ;
                U64 _t2008; { U64 *_hp = (U64 *)Range_len(_t2007); _t2008 = *_hp; free(_hp); }
                (void)_t2008;
                Range_delete(_t2007, &(Bool){1});
                Bool _wcond2003; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2002}, &(U64){_t2008}); _wcond2003 = *_hp; free(_hp); }
                (void)_wcond2003;
                ;
                if (_wcond2003) {
                } else {
                    ;
                    break;
                }
                ;
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
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2012, _fi2002); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2012, &(Bool){1});
                ;
                U64 _t2013 = 1;
                (void)_t2013;
                U64 _t2014 = U64_add(_fi2002, _t2013);
                (void)_t2014;
                ;
                _fi2002 = _t2014;
                ;
                Str *_t2015 = Str_lit("Str", 3ULL);
                (void)_t2015;
                U64 _t2016; { U64 *_hp = (U64 *)Str_size(); _t2016 = *_hp; free(_hp); }
                (void)_t2016;
                U64 _t2017 = 1;
                (void)_t2017;
                Array *_va46 = Array_new(_t2015, &(U64){_t2016}, &(U64){_t2017});
                (void)_va46;
                Str_delete(_t2015, &(Bool){1});
                ;
                ;
                U64 _t2018 = 0;
                (void)_t2018;
                Str *_t2019 = Str_lit("  ", 2ULL);
                (void)_t2019;
                Array_set(_va46, &(U64){_t2018}, _t2019);
                ;
                print(_va46);
            }
            ;
        }
    }
    ;
    Str *_t2037 = Str_lit("Str", 3ULL);
    (void)_t2037;
    U64 _t2038; { U64 *_hp = (U64 *)Str_size(); _t2038 = *_hp; free(_hp); }
    (void)_t2038;
    U64 _t2039 = 1;
    (void)_t2039;
    Array *_va49 = Array_new(_t2037, &(U64){_t2038}, &(U64){_t2039});
    (void)_va49;
    Str_delete(_t2037, &(Bool){1});
    ;
    ;
    U64 _t2040 = 0;
    (void)_t2040;
    Str *_t2041 = Str_lit(")", 1ULL);
    (void)_t2041;
    Array_set(_va49, &(U64){_t2040}, _t2041);
    ;
    println(_va49);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2063 = malloc(sizeof(I64));
    *_t2063 = 0;
    (void)_t2063;
    Expr *body = Expr_child(enum_def, _t2063);
    (void)body;
    {
        U64 _fi2042 = 0;
        (void)_fi2042;
        while (1) {
            I64 _t2050; { I64 *_hp = (I64 *)Expr_child_count(body); _t2050 = *_hp; free(_hp); }
            (void)_t2050;
            U64 _t2051 = 0;
            (void)_t2051;
            U64 _t2052 = I64_to_u64(_t2050);
            (void)_t2052;
            ;
            Range *_t2053 = Range_new(_t2051, _t2052);
            (void)_t2053;
            ;
            ;
            U64 _t2054; { U64 *_hp = (U64 *)Range_len(_t2053); _t2054 = *_hp; free(_hp); }
            (void)_t2054;
            Range_delete(_t2053, &(Bool){1});
            Bool _wcond2043; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2042}, &(U64){_t2054}); _wcond2043 = *_hp; free(_hp); }
            (void)_wcond2043;
            ;
            if (_wcond2043) {
            } else {
                ;
                break;
            }
            ;
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
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2058, _fi2042); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2058, &(Bool){1});
            U64 _t2059 = 1;
            (void)_t2059;
            U64 _t2060 = U64_add(_fi2042, _t2059);
            (void)_t2060;
            ;
            _fi2042 = _t2060;
            ;
            I64 *_t2061 = malloc(sizeof(I64)); *_t2061 = U64_to_i64(i);
            (void)_t2061;
            ;
            Expr *f = Expr_child(body, _t2061);
            (void)f;
            Bool _t2062; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2062 = *_hp; free(_hp); }
            (void)_t2062;
            if (_t2062) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2045; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2045 = *_hp; free(_hp); }
                (void)_t2045;
                U64 _t2046 = 0;
                (void)_t2046;
                Bool _t2047 = Bool_not(decl->is_namespace);
                (void)_t2047;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2048; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2045}, &(U64){_t2046}); _t2048 = *_hp; free(_hp); }
                (void)_t2048;
                ;
                ;
                Bool _t2049 = Bool_and(_t2047, _t2048);
                (void)_t2049;
                ;
                ;
                if (_t2049) {
                    Bool _t2044 = 1;
                    (void)_t2044;
                    ;
                    I64_delete(_t2061, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2044; return _r; }
                }
                ;
            }
            I64_delete(_t2061, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2063, &(Bool){1});
    Bool _t2064 = 0;
    (void)_t2064;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2064; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2084 = malloc(sizeof(I64));
    *_t2084 = 0;
    (void)_t2084;
    Expr *body = Expr_child(enum_def, _t2084);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2065 = 0;
        (void)_fi2065;
        while (1) {
            I64 _t2071; { I64 *_hp = (I64 *)Expr_child_count(body); _t2071 = *_hp; free(_hp); }
            (void)_t2071;
            U64 _t2072 = 0;
            (void)_t2072;
            U64 _t2073 = I64_to_u64(_t2071);
            (void)_t2073;
            ;
            Range *_t2074 = Range_new(_t2072, _t2073);
            (void)_t2074;
            ;
            ;
            U64 _t2075; { U64 *_hp = (U64 *)Range_len(_t2074); _t2075 = *_hp; free(_hp); }
            (void)_t2075;
            Range_delete(_t2074, &(Bool){1});
            Bool _wcond2066; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2065}, &(U64){_t2075}); _wcond2066 = *_hp; free(_hp); }
            (void)_wcond2066;
            ;
            if (_wcond2066) {
            } else {
                ;
                break;
            }
            ;
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
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2079, _fi2065); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2079, &(Bool){1});
            U64 _t2080 = 1;
            (void)_t2080;
            U64 _t2081 = U64_add(_fi2065, _t2080);
            (void)_t2081;
            ;
            _fi2065 = _t2081;
            ;
            I64 *_t2082 = malloc(sizeof(I64)); *_t2082 = U64_to_i64(i);
            (void)_t2082;
            ;
            Expr *f = Expr_child(body, _t2082);
            (void)f;
            Bool _t2083; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2083 = *_hp; free(_hp); }
            (void)_t2083;
            if (_t2083) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2070 = Bool_not(decl->is_namespace);
                (void)_t2070;
                if (_t2070) {
                    Bool _t2067; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2067 = *_hp; free(_hp); }
                    (void)_t2067;
                    if (_t2067) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2082, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2068 = 1;
                    (void)_t2068;
                    I32 _t2069 = I32_add(tag, _t2068);
                    (void)_t2069;
                    ;
                    tag = _t2069;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2082, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2084, &(Bool){1});
    ;
    I64 _t2085 = 0;
    (void)_t2085;
    I64 _t2086 = 1;
    (void)_t2086;
    I64 _t2087 = I64_sub(_t2085, _t2086);
    (void)_t2087;
    ;
    ;
    I32 _t2088 = I64_to_i32(_t2087);
    (void)_t2088;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2088; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2108 = malloc(sizeof(I64));
    *_t2108 = 0;
    (void)_t2108;
    Expr *body = Expr_child(enum_def, _t2108);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi2089 = 0;
        (void)_fi2089;
        while (1) {
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
            U64 _t2099; { U64 *_hp = (U64 *)Range_len(_t2098); _t2099 = *_hp; free(_hp); }
            (void)_t2099;
            Range_delete(_t2098, &(Bool){1});
            Bool _wcond2090; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2089}, &(U64){_t2099}); _wcond2090 = *_hp; free(_hp); }
            (void)_wcond2090;
            ;
            if (_wcond2090) {
            } else {
                ;
                break;
            }
            ;
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
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2103, _fi2089); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2103, &(Bool){1});
            U64 _t2104 = 1;
            (void)_t2104;
            U64 _t2105 = U64_add(_fi2089, _t2104);
            (void)_t2105;
            ;
            _fi2089 = _t2105;
            ;
            I64 *_t2106 = malloc(sizeof(I64)); *_t2106 = U64_to_i64(i);
            (void)_t2106;
            ;
            Expr *f = Expr_child(body, _t2106);
            (void)f;
            Bool _t2107; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2107 = *_hp; free(_hp); }
            (void)_t2107;
            if (_t2107) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2094 = Bool_not(decl->is_namespace);
                (void)_t2094;
                if (_t2094) {
                    Bool _t2091 = I32_eq(idx, tag);
                    (void)_t2091;
                    if (_t2091) {
                        ;
                        ;
                        I64_delete(_t2106, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2092 = 1;
                    (void)_t2092;
                    I32 _t2093 = I32_add(idx, _t2092);
                    (void)_t2093;
                    ;
                    idx = _t2093;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2106, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2108, &(Bool){1});
    ;
    Str *_t2109 = Str_lit("", 0ULL);
    (void)_t2109;
    return _t2109;
}

