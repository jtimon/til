#include "parser_ast.h"

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
    U32_delete(&self->nparam, &(Bool){_t1397});
    ;
    Bool _t1398 = 0;
    (void)_t1398;
    Map_delete(&self->param_defaults, &(Bool){_t1398});
    ;
    Bool _t1399 = 0;
    (void)_t1399;
    Str_delete(&self->return_type, &(Bool){_t1399});
    ;
    Bool _t1400 = 0;
    (void)_t1400;
    I32_delete(&self->variadic_index, &(Bool){_t1400});
    ;
    Bool _t1401 = 0;
    (void)_t1401;
    I32_delete(&self->kwargs_index, &(Bool){_t1401});
    ;
    Bool _t1402 = 0;
    (void)_t1402;
    Bool_delete(&self->return_is_ref, &(Bool){_t1402});
    ;
    Bool _t1403 = 0;
    (void)_t1403;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1403});
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
    Bool _t1786 = 0;
    (void)_t1786;
    ExprData_delete(&self->data, &(Bool){_t1786});
    ;
    Bool _t1787 = 0;
    (void)_t1787;
    TilType_delete(&self->til_type, &(Bool){_t1787});
    ;
    Bool _t1788 = 0;
    (void)_t1788;
    Str_delete(&self->struct_name, &(Bool){_t1788});
    ;
    Bool _t1789 = 0;
    (void)_t1789;
    Bool_delete(&self->is_own_arg, &(Bool){_t1789});
    ;
    Bool _t1790 = 0;
    (void)_t1790;
    Bool_delete(&self->is_splat, &(Bool){_t1790});
    ;
    Bool _t1791 = 0;
    (void)_t1791;
    Bool_delete(&self->is_own_field, &(Bool){_t1791});
    ;
    Bool _t1792 = 0;
    (void)_t1792;
    Bool_delete(&self->is_ref_field, &(Bool){_t1792});
    ;
    Bool _t1793 = 0;
    (void)_t1793;
    Bool_delete(&self->is_ns_field, &(Bool){_t1793});
    ;
    Bool _t1794 = 0;
    (void)_t1794;
    Bool_delete(&self->is_ext, &(Bool){_t1794});
    ;
    Bool _t1795 = 0;
    (void)_t1795;
    Bool_delete(&self->is_core, &(Bool){_t1795});
    ;
    Bool _t1796 = 0;
    (void)_t1796;
    Bool_delete(&self->save_old_delete, &(Bool){_t1796});
    ;
    Bool _t1797 = 0;
    (void)_t1797;
    I32_delete(&self->total_struct_size, &(Bool){_t1797});
    ;
    Bool _t1798 = 0;
    (void)_t1798;
    I32_delete(&self->variadic_index, &(Bool){_t1798});
    ;
    Bool _t1799 = 0;
    (void)_t1799;
    U32_delete(&self->variadic_count, &(Bool){_t1799});
    ;
    Bool _t1800 = 0;
    (void)_t1800;
    I32_delete(&self->kwargs_index, &(Bool){_t1800});
    ;
    Bool _t1801 = 0;
    (void)_t1801;
    U32_delete(&self->kwargs_count, &(Bool){_t1801});
    ;
    Bool _t1802 = 0;
    (void)_t1802;
    Vec_delete(&self->children, &(Bool){_t1802});
    ;
    Bool _t1803 = 0;
    (void)_t1803;
    U32_delete(&self->line, &(Bool){_t1803});
    ;
    Bool _t1804 = 0;
    (void)_t1804;
    U32_delete(&self->col, &(Bool){_t1804});
    ;
    Bool _t1805 = 0;
    (void)_t1805;
    Str_delete(&self->path, &(Bool){_t1805});
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
        ExprData *_sw1807 = ExprData_clone(data);
        (void)_sw1807;
        Bool _t1858; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Body()); _t1858 = *_hp; free(_hp); }
        (void)_t1858;
        if (_t1858) {
            Str *_t1808 = Str_lit("body", 4ULL);
            (void)_t1808;
            ExprData_delete(_sw1807, &(Bool){1});
            ;
            return _t1808;
        } else {
            Bool _t1857; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1807); _t1857 = *_hp; free(_hp); }
            (void)_t1857;
            if (_t1857) {
                Str *_t1809 = Str_lit("str", 3ULL);
                (void)_t1809;
                ;
                ExprData_delete(_sw1807, &(Bool){1});
                ;
                return _t1809;
            } else {
                Bool _t1856; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1807); _t1856 = *_hp; free(_hp); }
                (void)_t1856;
                if (_t1856) {
                    Str *_t1810 = Str_lit("num", 3ULL);
                    (void)_t1810;
                    ;
                    ;
                    ExprData_delete(_sw1807, &(Bool){1});
                    ;
                    return _t1810;
                } else {
                    Bool _t1855; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1807); _t1855 = *_hp; free(_hp); }
                    (void)_t1855;
                    if (_t1855) {
                        Str *_t1811 = Str_lit("bool", 4ULL);
                        (void)_t1811;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1807, &(Bool){1});
                        ;
                        return _t1811;
                    } else {
                        Bool _t1854; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_LiteralNull()); _t1854 = *_hp; free(_hp); }
                        (void)_t1854;
                        if (_t1854) {
                            Str *_t1812 = Str_lit("null", 4ULL);
                            (void)_t1812;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1807, &(Bool){1});
                            ;
                            return _t1812;
                        } else {
                            Bool _t1853; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1807); _t1853 = *_hp; free(_hp); }
                            (void)_t1853;
                            if (_t1853) {
                                Str *_t1813 = Str_lit("ident", 5ULL);
                                (void)_t1813;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1807, &(Bool){1});
                                ;
                                return _t1813;
                            } else {
                                Bool _t1852; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1807); _t1852 = *_hp; free(_hp); }
                                (void)_t1852;
                                if (_t1852) {
                                    Str *_t1814 = Str_lit("decl", 4ULL);
                                    (void)_t1814;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1807, &(Bool){1});
                                    ;
                                    return _t1814;
                                } else {
                                    Bool _t1851; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1807); _t1851 = *_hp; free(_hp); }
                                    (void)_t1851;
                                    if (_t1851) {
                                        Str *_t1815 = Str_lit("assign", 6ULL);
                                        (void)_t1815;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1807, &(Bool){1});
                                        ;
                                        return _t1815;
                                    } else {
                                        Bool _t1850; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_FCall()); _t1850 = *_hp; free(_hp); }
                                        (void)_t1850;
                                        if (_t1850) {
                                            Str *_t1816 = Str_lit("fcall", 5ULL);
                                            (void)_t1816;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1807, &(Bool){1});
                                            ;
                                            return _t1816;
                                        } else {
                                            Bool _t1849; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1807); _t1849 = *_hp; free(_hp); }
                                            (void)_t1849;
                                            if (_t1849) {
                                                Str *_t1817 = Str_lit("func_def", 8ULL);
                                                (void)_t1817;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1807, &(Bool){1});
                                                ;
                                                return _t1817;
                                            } else {
                                                Bool _t1848; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_StructDef()); _t1848 = *_hp; free(_hp); }
                                                (void)_t1848;
                                                if (_t1848) {
                                                    Str *_t1818 = Str_lit("struct_def", 10ULL);
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
                                                    ;
                                                    ExprData_delete(_sw1807, &(Bool){1});
                                                    ;
                                                    return _t1818;
                                                } else {
                                                    Bool _t1847; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_EnumDef()); _t1847 = *_hp; free(_hp); }
                                                    (void)_t1847;
                                                    if (_t1847) {
                                                        Str *_t1819 = Str_lit("enum_def", 8ULL);
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
                                                        ;
                                                        ExprData_delete(_sw1807, &(Bool){1});
                                                        ;
                                                        return _t1819;
                                                    } else {
                                                        Bool _t1846; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1807); _t1846 = *_hp; free(_hp); }
                                                        (void)_t1846;
                                                        if (_t1846) {
                                                            Str *_t1820 = Str_lit("field_access", 12ULL);
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
                                                            ;
                                                            ExprData_delete(_sw1807, &(Bool){1});
                                                            ;
                                                            return _t1820;
                                                        } else {
                                                            Bool _t1845; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1807); _t1845 = *_hp; free(_hp); }
                                                            (void)_t1845;
                                                            if (_t1845) {
                                                                Str *_t1821 = Str_lit("field_assign", 12ULL);
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
                                                                ;
                                                                ExprData_delete(_sw1807, &(Bool){1});
                                                                ;
                                                                return _t1821;
                                                            } else {
                                                                Bool _t1844; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Return()); _t1844 = *_hp; free(_hp); }
                                                                (void)_t1844;
                                                                if (_t1844) {
                                                                    Str *_t1822 = Str_lit("return", 6ULL);
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
                                                                    ;
                                                                    ExprData_delete(_sw1807, &(Bool){1});
                                                                    ;
                                                                    return _t1822;
                                                                } else {
                                                                    Bool _t1843; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_If()); _t1843 = *_hp; free(_hp); }
                                                                    (void)_t1843;
                                                                    if (_t1843) {
                                                                        Str *_t1823 = Str_lit("if", 2ULL);
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
                                                                        ;
                                                                        ExprData_delete(_sw1807, &(Bool){1});
                                                                        ;
                                                                        return _t1823;
                                                                    } else {
                                                                        Bool _t1842; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_While()); _t1842 = *_hp; free(_hp); }
                                                                        (void)_t1842;
                                                                        if (_t1842) {
                                                                            Str *_t1824 = Str_lit("while", 5ULL);
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
                                                                            ;
                                                                            ExprData_delete(_sw1807, &(Bool){1});
                                                                            ;
                                                                            return _t1824;
                                                                        } else {
                                                                            Bool _t1841; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1807); _t1841 = *_hp; free(_hp); }
                                                                            (void)_t1841;
                                                                            if (_t1841) {
                                                                                Str *_t1825 = Str_lit("for_in", 6ULL);
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
                                                                                ;
                                                                                ExprData_delete(_sw1807, &(Bool){1});
                                                                                ;
                                                                                return _t1825;
                                                                            } else {
                                                                                Bool _t1840; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1807); _t1840 = *_hp; free(_hp); }
                                                                                (void)_t1840;
                                                                                if (_t1840) {
                                                                                    Str *_t1826 = Str_lit("named_arg", 9ULL);
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
                                                                                    ;
                                                                                    ExprData_delete(_sw1807, &(Bool){1});
                                                                                    ;
                                                                                    return _t1826;
                                                                                } else {
                                                                                    Bool _t1839; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Break()); _t1839 = *_hp; free(_hp); }
                                                                                    (void)_t1839;
                                                                                    if (_t1839) {
                                                                                        Str *_t1827 = Str_lit("break", 5ULL);
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
                                                                                        ;
                                                                                        ExprData_delete(_sw1807, &(Bool){1});
                                                                                        ;
                                                                                        return _t1827;
                                                                                    } else {
                                                                                        Bool _t1838; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Continue()); _t1838 = *_hp; free(_hp); }
                                                                                        (void)_t1838;
                                                                                        if (_t1838) {
                                                                                            Str *_t1828 = Str_lit("continue", 8ULL);
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
                                                                                            ;
                                                                                            ExprData_delete(_sw1807, &(Bool){1});
                                                                                            ;
                                                                                            return _t1828;
                                                                                        } else {
                                                                                            Bool _t1837; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_MapLit()); _t1837 = *_hp; free(_hp); }
                                                                                            (void)_t1837;
                                                                                            if (_t1837) {
                                                                                                Str *_t1829 = Str_lit("map_lit", 7ULL);
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
                                                                                                ;
                                                                                                ExprData_delete(_sw1807, &(Bool){1});
                                                                                                ;
                                                                                                return _t1829;
                                                                                            } else {
                                                                                                Bool _t1836; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_SetLit()); _t1836 = *_hp; free(_hp); }
                                                                                                (void)_t1836;
                                                                                                if (_t1836) {
                                                                                                    Str *_t1830 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ;
                                                                                                    ExprData_delete(_sw1807, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1830;
                                                                                                } else {
                                                                                                    Bool _t1835; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Switch()); _t1835 = *_hp; free(_hp); }
                                                                                                    (void)_t1835;
                                                                                                    if (_t1835) {
                                                                                                        Str *_t1831 = Str_lit("switch", 6ULL);
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
                                                                                                        ;
                                                                                                        ExprData_delete(_sw1807, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1831;
                                                                                                    } else {
                                                                                                        Bool _t1834; { Bool *_hp = (Bool *)ExprData_eq(_sw1807, ExprData_Case()); _t1834 = *_hp; free(_hp); }
                                                                                                        (void)_t1834;
                                                                                                        if (_t1834) {
                                                                                                            Str *_t1832 = Str_lit("case", 4ULL);
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
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1807, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1832;
                                                                                                        } else {
                                                                                                            Str *_t1833 = Str_lit("?", 1ULL);
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
                                                                                                            ExprData_delete(_sw1807, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1833;
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
        ExprData_delete(_sw1807, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1859 = FuncType_clone(ft);
        (void)_sw1859;
        Bool _t1872; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_Func()); _t1872 = *_hp; free(_hp); }
        (void)_t1872;
        if (_t1872) {
            Str *_t1860 = Str_lit("func", 4ULL);
            (void)_t1860;
            FuncType_delete(_sw1859, &(Bool){1});
            ;
            return _t1860;
        } else {
            Bool _t1871; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_Proc()); _t1871 = *_hp; free(_hp); }
            (void)_t1871;
            if (_t1871) {
                Str *_t1861 = Str_lit("proc", 4ULL);
                (void)_t1861;
                ;
                FuncType_delete(_sw1859, &(Bool){1});
                ;
                return _t1861;
            } else {
                Bool _t1870; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_Test()); _t1870 = *_hp; free(_hp); }
                (void)_t1870;
                if (_t1870) {
                    Str *_t1862 = Str_lit("test", 4ULL);
                    (void)_t1862;
                    ;
                    ;
                    FuncType_delete(_sw1859, &(Bool){1});
                    ;
                    return _t1862;
                } else {
                    Bool _t1869; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_Macro()); _t1869 = *_hp; free(_hp); }
                    (void)_t1869;
                    if (_t1869) {
                        Str *_t1863 = Str_lit("macro", 5ULL);
                        (void)_t1863;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1859, &(Bool){1});
                        ;
                        return _t1863;
                    } else {
                        Bool _t1868; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_ExtFunc()); _t1868 = *_hp; free(_hp); }
                        (void)_t1868;
                        if (_t1868) {
                            Str *_t1864 = Str_lit("ext_func", 8ULL);
                            (void)_t1864;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1859, &(Bool){1});
                            ;
                            return _t1864;
                        } else {
                            Bool _t1867; { Bool *_hp = (Bool *)FuncType_eq(_sw1859, FuncType_ExtProc()); _t1867 = *_hp; free(_hp); }
                            (void)_t1867;
                            if (_t1867) {
                                Str *_t1865 = Str_lit("ext_proc", 8ULL);
                                (void)_t1865;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1859, &(Bool){1});
                                ;
                                return _t1865;
                            } else {
                                Str *_t1866 = Str_lit("?", 1ULL);
                                (void)_t1866;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1859, &(Bool){1});
                                ;
                                return _t1866;
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
        FuncType_delete(_sw1859, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi1873 = 0;
        (void)_fi1873;
        while (1) {
            I64 _t1875 = U32_to_i64(indent);
            (void)_t1875;
            U64 _t1876 = 0;
            (void)_t1876;
            U64 _t1877 = I64_to_u64(_t1875);
            (void)_t1877;
            ;
            Range *_t1878 = Range_new(_t1876, _t1877);
            (void)_t1878;
            ;
            ;
            U64 _t1879; { U64 *_hp = (U64 *)Range_len(_t1878); _t1879 = *_hp; free(_hp); }
            (void)_t1879;
            Range_delete(_t1878, &(Bool){1});
            Bool _wcond1874; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1873}, &(U64){_t1879}); _wcond1874 = *_hp; free(_hp); }
            (void)_wcond1874;
            ;
            if (_wcond1874) {
            } else {
                ;
                break;
            }
            ;
            I64 _t1880 = U32_to_i64(indent);
            (void)_t1880;
            U64 _t1881 = 0;
            (void)_t1881;
            U64 _t1882 = I64_to_u64(_t1880);
            (void)_t1882;
            ;
            Range *_t1883 = Range_new(_t1881, _t1882);
            (void)_t1883;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t1883, _fi1873); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t1883, &(Bool){1});
            ;
            U64 _t1884 = 1;
            (void)_t1884;
            U64 _t1885 = U64_add(_fi1873, _t1884);
            (void)_t1885;
            ;
            _fi1873 = _t1885;
            ;
            Str *_t1886 = Str_lit("Str", 3ULL);
            (void)_t1886;
            U64 _t1887; { U64 *_hp = (U64 *)Str_size(); _t1887 = *_hp; free(_hp); }
            (void)_t1887;
            U64 _t1888 = 1;
            (void)_t1888;
            Array *_va34 = Array_new(_t1886, &(U64){_t1887}, &(U64){_t1888});
            (void)_va34;
            Str_delete(_t1886, &(Bool){1});
            ;
            ;
            U64 _t1889 = 0;
            (void)_t1889;
            Str *_t1890 = Str_lit("  ", 2ULL);
            (void)_t1890;
            Array_set(_va34, &(U64){_t1889}, _t1890);
            ;
            print(_va34);
        }
        ;
    }
    Str *_t2024 = Str_lit("Str", 3ULL);
    (void)_t2024;
    U64 _t2025; { U64 *_hp = (U64 *)Str_size(); _t2025 = *_hp; free(_hp); }
    (void)_t2025;
    U64 _t2026 = 2;
    (void)_t2026;
    Array *_va48 = Array_new(_t2024, &(U64){_t2025}, &(U64){_t2026});
    (void)_va48;
    Str_delete(_t2024, &(Bool){1});
    ;
    ;
    U64 _t2027 = 0;
    (void)_t2027;
    Str *_t2028 = Str_lit("(", 1ULL);
    (void)_t2028;
    Array_set(_va48, &(U64){_t2027}, _t2028);
    ;
    U64 _t2029 = 1;
    (void)_t2029;
    Str *_t2030 = node_name(&e->data);
    (void)_t2030;
    Array_set(_va48, &(U64){_t2029}, _t2030);
    ;
    print(_va48);
    Bool _t2031; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2031 = *_hp; free(_hp); }
    (void)_t2031;
    Bool _t2032 = Bool_not(_t2031);
    (void)_t2032;
    ;
    if (_t2032) {
        Str *_t1891 = Str_lit("Str", 3ULL);
        (void)_t1891;
        U64 _t1892; { U64 *_hp = (U64 *)Str_size(); _t1892 = *_hp; free(_hp); }
        (void)_t1892;
        U64 _t1893 = 2;
        (void)_t1893;
        Array *_va35 = Array_new(_t1891, &(U64){_t1892}, &(U64){_t1893});
        (void)_va35;
        Str_delete(_t1891, &(Bool){1});
        ;
        ;
        U64 _t1894 = 0;
        (void)_t1894;
        Str *_t1895 = Str_lit(":", 1ULL);
        (void)_t1895;
        Array_set(_va35, &(U64){_t1894}, _t1895);
        ;
        U64 _t1896 = 1;
        (void)_t1896;
        Str *_t1897 = til_type_name_c(&e->til_type);
        (void)_t1897;
        Array_set(_va35, &(U64){_t1896}, _t1897);
        ;
        print(_va35);
    }
    ;
    {
        ExprData *_sw1898 = ExprData_clone(&e->data);
        (void)_sw1898;
        Bool _t1985; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1898); _t1985 = *_hp; free(_hp); }
        (void)_t1985;
        if (_t1985) {
            Str *s = ExprData_get_Ident(_sw1898);
            (void)s;
            Str *_t1899 = Str_lit("Str", 3ULL);
            (void)_t1899;
            U64 _t1900; { U64 *_hp = (U64 *)Str_size(); _t1900 = *_hp; free(_hp); }
            (void)_t1900;
            U64 _t1901 = 3;
            (void)_t1901;
            Array *_va36 = Array_new(_t1899, &(U64){_t1900}, &(U64){_t1901});
            (void)_va36;
            Str_delete(_t1899, &(Bool){1});
            ;
            ;
            U64 _t1902 = 0;
            (void)_t1902;
            Str *_t1903 = Str_lit(" \"", 3ULL);
            (void)_t1903;
            Array_set(_va36, &(U64){_t1902}, _t1903);
            ;
            U64 _t1904 = 1;
            (void)_t1904;
            Str *_t1905 = Str_clone(s);
            (void)_t1905;
            Str_delete(s, &(Bool){1});
            Array_set(_va36, &(U64){_t1904}, _t1905);
            ;
            U64 _t1906 = 2;
            (void)_t1906;
            Str *_t1907 = Str_lit("\"", 2ULL);
            (void)_t1907;
            Array_set(_va36, &(U64){_t1906}, _t1907);
            ;
            print(_va36);
        } else {
            Bool _t1984; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1898); _t1984 = *_hp; free(_hp); }
            (void)_t1984;
            if (_t1984) {
                Str *s = ExprData_get_LiteralStr(_sw1898);
                (void)s;
                Str *_t1908 = Str_lit("Str", 3ULL);
                (void)_t1908;
                U64 _t1909; { U64 *_hp = (U64 *)Str_size(); _t1909 = *_hp; free(_hp); }
                (void)_t1909;
                U64 _t1910 = 3;
                (void)_t1910;
                Array *_va37 = Array_new(_t1908, &(U64){_t1909}, &(U64){_t1910});
                (void)_va37;
                Str_delete(_t1908, &(Bool){1});
                ;
                ;
                U64 _t1911 = 0;
                (void)_t1911;
                Str *_t1912 = Str_lit(" \"", 3ULL);
                (void)_t1912;
                Array_set(_va37, &(U64){_t1911}, _t1912);
                ;
                U64 _t1913 = 1;
                (void)_t1913;
                Str *_t1914 = Str_clone(s);
                (void)_t1914;
                Str_delete(s, &(Bool){1});
                Array_set(_va37, &(U64){_t1913}, _t1914);
                ;
                U64 _t1915 = 2;
                (void)_t1915;
                Str *_t1916 = Str_lit("\"", 2ULL);
                (void)_t1916;
                Array_set(_va37, &(U64){_t1915}, _t1916);
                ;
                print(_va37);
            } else {
                Bool _t1983; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1898); _t1983 = *_hp; free(_hp); }
                (void)_t1983;
                if (_t1983) {
                    Str *s = ExprData_get_LiteralNum(_sw1898);
                    (void)s;
                    Str *_t1917 = Str_lit("Str", 3ULL);
                    (void)_t1917;
                    U64 _t1918; { U64 *_hp = (U64 *)Str_size(); _t1918 = *_hp; free(_hp); }
                    (void)_t1918;
                    U64 _t1919 = 3;
                    (void)_t1919;
                    Array *_va38 = Array_new(_t1917, &(U64){_t1918}, &(U64){_t1919});
                    (void)_va38;
                    Str_delete(_t1917, &(Bool){1});
                    ;
                    ;
                    U64 _t1920 = 0;
                    (void)_t1920;
                    Str *_t1921 = Str_lit(" \"", 3ULL);
                    (void)_t1921;
                    Array_set(_va38, &(U64){_t1920}, _t1921);
                    ;
                    U64 _t1922 = 1;
                    (void)_t1922;
                    Str *_t1923 = Str_clone(s);
                    (void)_t1923;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va38, &(U64){_t1922}, _t1923);
                    ;
                    U64 _t1924 = 2;
                    (void)_t1924;
                    Str *_t1925 = Str_lit("\"", 2ULL);
                    (void)_t1925;
                    Array_set(_va38, &(U64){_t1924}, _t1925);
                    ;
                    print(_va38);
                } else {
                    Bool _t1982; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1898); _t1982 = *_hp; free(_hp); }
                    (void)_t1982;
                    if (_t1982) {
                        Str *s = ExprData_get_LiteralBool(_sw1898);
                        (void)s;
                        Str *_t1926 = Str_lit("Str", 3ULL);
                        (void)_t1926;
                        U64 _t1927; { U64 *_hp = (U64 *)Str_size(); _t1927 = *_hp; free(_hp); }
                        (void)_t1927;
                        U64 _t1928 = 3;
                        (void)_t1928;
                        Array *_va39 = Array_new(_t1926, &(U64){_t1927}, &(U64){_t1928});
                        (void)_va39;
                        Str_delete(_t1926, &(Bool){1});
                        ;
                        ;
                        U64 _t1929 = 0;
                        (void)_t1929;
                        Str *_t1930 = Str_lit(" \"", 3ULL);
                        (void)_t1930;
                        Array_set(_va39, &(U64){_t1929}, _t1930);
                        ;
                        U64 _t1931 = 1;
                        (void)_t1931;
                        Str *_t1932 = Str_clone(s);
                        (void)_t1932;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va39, &(U64){_t1931}, _t1932);
                        ;
                        U64 _t1933 = 2;
                        (void)_t1933;
                        Str *_t1934 = Str_lit("\"", 2ULL);
                        (void)_t1934;
                        Array_set(_va39, &(U64){_t1933}, _t1934);
                        ;
                        print(_va39);
                    } else {
                        Bool _t1981; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1898); _t1981 = *_hp; free(_hp); }
                        (void)_t1981;
                        if (_t1981) {
                            Str *s = ExprData_get_ForIn(_sw1898);
                            (void)s;
                            Str *_t1935 = Str_lit("Str", 3ULL);
                            (void)_t1935;
                            U64 _t1936; { U64 *_hp = (U64 *)Str_size(); _t1936 = *_hp; free(_hp); }
                            (void)_t1936;
                            U64 _t1937 = 3;
                            (void)_t1937;
                            Array *_va40 = Array_new(_t1935, &(U64){_t1936}, &(U64){_t1937});
                            (void)_va40;
                            Str_delete(_t1935, &(Bool){1});
                            ;
                            ;
                            U64 _t1938 = 0;
                            (void)_t1938;
                            Str *_t1939 = Str_lit(" \"", 3ULL);
                            (void)_t1939;
                            Array_set(_va40, &(U64){_t1938}, _t1939);
                            ;
                            U64 _t1940 = 1;
                            (void)_t1940;
                            Str *_t1941 = Str_clone(s);
                            (void)_t1941;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va40, &(U64){_t1940}, _t1941);
                            ;
                            U64 _t1942 = 2;
                            (void)_t1942;
                            Str *_t1943 = Str_lit("\"", 2ULL);
                            (void)_t1943;
                            Array_set(_va40, &(U64){_t1942}, _t1943);
                            ;
                            print(_va40);
                        } else {
                            Bool _t1980; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1898); _t1980 = *_hp; free(_hp); }
                            (void)_t1980;
                            if (_t1980) {
                                Declaration *decl = ExprData_get_Decl(_sw1898);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1944 = Str_lit("Str", 3ULL);
                                    (void)_t1944;
                                    U64 _t1945; { U64 *_hp = (U64 *)Str_size(); _t1945 = *_hp; free(_hp); }
                                    (void)_t1945;
                                    U64 _t1946 = 1;
                                    (void)_t1946;
                                    Array *_va41 = Array_new(_t1944, &(U64){_t1945}, &(U64){_t1946});
                                    (void)_va41;
                                    Str_delete(_t1944, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1947 = 0;
                                    (void)_t1947;
                                    Str *_t1948 = Str_lit(" mut", 4ULL);
                                    (void)_t1948;
                                    Array_set(_va41, &(U64){_t1947}, _t1948);
                                    ;
                                    print(_va41);
                                }
                                Str *_t1949 = Str_lit("Str", 3ULL);
                                (void)_t1949;
                                U64 _t1950; { U64 *_hp = (U64 *)Str_size(); _t1950 = *_hp; free(_hp); }
                                (void)_t1950;
                                U64 _t1951 = 2;
                                (void)_t1951;
                                Array *_va42 = Array_new(_t1949, &(U64){_t1950}, &(U64){_t1951});
                                (void)_va42;
                                Str_delete(_t1949, &(Bool){1});
                                ;
                                ;
                                U64 _t1952 = 0;
                                (void)_t1952;
                                Str *_t1953 = Str_lit(" ", 1ULL);
                                (void)_t1953;
                                Array_set(_va42, &(U64){_t1952}, _t1953);
                                ;
                                U64 _t1954 = 1;
                                (void)_t1954;
                                Str *_t1955 = Str_clone(&decl->name);
                                (void)_t1955;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va42, &(U64){_t1954}, _t1955);
                                ;
                                print(_va42);
                            } else {
                                Bool _t1979; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1898); _t1979 = *_hp; free(_hp); }
                                (void)_t1979;
                                if (_t1979) {
                                    Str *s = ExprData_get_Assign(_sw1898);
                                    (void)s;
                                    Str *_t1956 = Str_lit("Str", 3ULL);
                                    (void)_t1956;
                                    U64 _t1957; { U64 *_hp = (U64 *)Str_size(); _t1957 = *_hp; free(_hp); }
                                    (void)_t1957;
                                    U64 _t1958 = 2;
                                    (void)_t1958;
                                    Array *_va43 = Array_new(_t1956, &(U64){_t1957}, &(U64){_t1958});
                                    (void)_va43;
                                    Str_delete(_t1956, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1959 = 0;
                                    (void)_t1959;
                                    Str *_t1960 = Str_lit(" ", 1ULL);
                                    (void)_t1960;
                                    Array_set(_va43, &(U64){_t1959}, _t1960);
                                    ;
                                    U64 _t1961 = 1;
                                    (void)_t1961;
                                    Str *_t1962 = Str_clone(s);
                                    (void)_t1962;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va43, &(U64){_t1961}, _t1962);
                                    ;
                                    print(_va43);
                                } else {
                                    Bool _t1978; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1898); _t1978 = *_hp; free(_hp); }
                                    (void)_t1978;
                                    if (_t1978) {
                                        Str *s = ExprData_get_NamedArg(_sw1898);
                                        (void)s;
                                        Str *_t1963 = Str_lit("Str", 3ULL);
                                        (void)_t1963;
                                        U64 _t1964; { U64 *_hp = (U64 *)Str_size(); _t1964 = *_hp; free(_hp); }
                                        (void)_t1964;
                                        U64 _t1965 = 2;
                                        (void)_t1965;
                                        Array *_va44 = Array_new(_t1963, &(U64){_t1964}, &(U64){_t1965});
                                        (void)_va44;
                                        Str_delete(_t1963, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1966 = 0;
                                        (void)_t1966;
                                        Str *_t1967 = Str_lit(" ", 1ULL);
                                        (void)_t1967;
                                        Array_set(_va44, &(U64){_t1966}, _t1967);
                                        ;
                                        U64 _t1968 = 1;
                                        (void)_t1968;
                                        Str *_t1969 = Str_clone(s);
                                        (void)_t1969;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va44, &(U64){_t1968}, _t1969);
                                        ;
                                        print(_va44);
                                    } else {
                                        Bool _t1977; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1898); _t1977 = *_hp; free(_hp); }
                                        (void)_t1977;
                                        if (_t1977) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1898);
                                            (void)fdef;
                                            Str *_t1970 = Str_lit("Str", 3ULL);
                                            (void)_t1970;
                                            U64 _t1971; { U64 *_hp = (U64 *)Str_size(); _t1971 = *_hp; free(_hp); }
                                            (void)_t1971;
                                            U64 _t1972 = 2;
                                            (void)_t1972;
                                            Array *_va45 = Array_new(_t1970, &(U64){_t1971}, &(U64){_t1972});
                                            (void)_va45;
                                            Str_delete(_t1970, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1973 = 0;
                                            (void)_t1973;
                                            Str *_t1974 = Str_lit(" ", 1ULL);
                                            (void)_t1974;
                                            Array_set(_va45, &(U64){_t1973}, _t1974);
                                            ;
                                            U64 _t1975 = 1;
                                            (void)_t1975;
                                            Str *_t1976 = func_type_name(&fdef->func_type);
                                            (void)_t1976;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va45, &(U64){_t1975}, _t1976);
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
        ExprData_delete(_sw1898, &(Bool){1});
        ;
    }
    U64 _t2033; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2033 = *_hp; free(_hp); }
    (void)_t2033;
    U64 _t2034 = 0;
    (void)_t2034;
    Bool _t2035; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2033}, &(U64){_t2034}); _t2035 = *_hp; free(_hp); }
    (void)_t2035;
    ;
    ;
    if (_t2035) {
        Str *_t2019 = Str_lit("Str", 3ULL);
        (void)_t2019;
        U64 _t2020; { U64 *_hp = (U64 *)Str_size(); _t2020 = *_hp; free(_hp); }
        (void)_t2020;
        U64 _t2021 = 1;
        (void)_t2021;
        Array *_va47 = Array_new(_t2019, &(U64){_t2020}, &(U64){_t2021});
        (void)_va47;
        Str_delete(_t2019, &(Bool){1});
        ;
        ;
        U64 _t2022 = 0;
        (void)_t2022;
        Str *_t2023 = Str_lit("", 0ULL);
        (void)_t2023;
        Array_set(_va47, &(U64){_t2022}, _t2023);
        ;
        println(_va47);
        {
            U64 _fi1986 = 0;
            (void)_fi1986;
            while (1) {
                U64 _t1988 = 0;
                (void)_t1988;
                U64 _t1989; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1989 = *_hp; free(_hp); }
                (void)_t1989;
                Range *_t1990 = Range_new(_t1988, _t1989);
                (void)_t1990;
                ;
                ;
                U64 _t1991; { U64 *_hp = (U64 *)Range_len(_t1990); _t1991 = *_hp; free(_hp); }
                (void)_t1991;
                Range_delete(_t1990, &(Bool){1});
                Bool _wcond1987; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1986}, &(U64){_t1991}); _wcond1987 = *_hp; free(_hp); }
                (void)_wcond1987;
                ;
                if (_wcond1987) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1992 = 0;
                (void)_t1992;
                U64 _t1993; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1993 = *_hp; free(_hp); }
                (void)_t1993;
                Range *_t1994 = Range_new(_t1992, _t1993);
                (void)_t1994;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t1994, _fi1986); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t1994, &(Bool){1});
                U64 _t1995 = 1;
                (void)_t1995;
                U64 _t1996 = U64_add(_fi1986, _t1995);
                (void)_t1996;
                ;
                _fi1986 = _t1996;
                ;
                I64 *_t1997 = malloc(sizeof(I64)); *_t1997 = U64_to_i64(i);
                (void)_t1997;
                ;
                U32 _t1998 = 1;
                (void)_t1998;
                Expr *_t1999 = Expr_child(e, _t1997);
                (void)_t1999;
                U32 _t2000 = U32_add(indent, _t1998);
                (void)_t2000;
                ;
                ast_print(_t1999, _t2000);
                I64_delete(_t1997, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2001 = 0;
            (void)_fi2001;
            while (1) {
                I64 _t2003 = U32_to_i64(indent);
                (void)_t2003;
                U64 _t2004 = 0;
                (void)_t2004;
                U64 _t2005 = I64_to_u64(_t2003);
                (void)_t2005;
                ;
                Range *_t2006 = Range_new(_t2004, _t2005);
                (void)_t2006;
                ;
                ;
                U64 _t2007; { U64 *_hp = (U64 *)Range_len(_t2006); _t2007 = *_hp; free(_hp); }
                (void)_t2007;
                Range_delete(_t2006, &(Bool){1});
                Bool _wcond2002; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2001}, &(U64){_t2007}); _wcond2002 = *_hp; free(_hp); }
                (void)_wcond2002;
                ;
                if (_wcond2002) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2008 = U32_to_i64(indent);
                (void)_t2008;
                U64 _t2009 = 0;
                (void)_t2009;
                U64 _t2010 = I64_to_u64(_t2008);
                (void)_t2010;
                ;
                Range *_t2011 = Range_new(_t2009, _t2010);
                (void)_t2011;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2011, _fi2001); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2011, &(Bool){1});
                ;
                U64 _t2012 = 1;
                (void)_t2012;
                U64 _t2013 = U64_add(_fi2001, _t2012);
                (void)_t2013;
                ;
                _fi2001 = _t2013;
                ;
                Str *_t2014 = Str_lit("Str", 3ULL);
                (void)_t2014;
                U64 _t2015; { U64 *_hp = (U64 *)Str_size(); _t2015 = *_hp; free(_hp); }
                (void)_t2015;
                U64 _t2016 = 1;
                (void)_t2016;
                Array *_va46 = Array_new(_t2014, &(U64){_t2015}, &(U64){_t2016});
                (void)_va46;
                Str_delete(_t2014, &(Bool){1});
                ;
                ;
                U64 _t2017 = 0;
                (void)_t2017;
                Str *_t2018 = Str_lit("  ", 2ULL);
                (void)_t2018;
                Array_set(_va46, &(U64){_t2017}, _t2018);
                ;
                print(_va46);
            }
            ;
        }
    }
    ;
    Str *_t2036 = Str_lit("Str", 3ULL);
    (void)_t2036;
    U64 _t2037; { U64 *_hp = (U64 *)Str_size(); _t2037 = *_hp; free(_hp); }
    (void)_t2037;
    U64 _t2038 = 1;
    (void)_t2038;
    Array *_va49 = Array_new(_t2036, &(U64){_t2037}, &(U64){_t2038});
    (void)_va49;
    Str_delete(_t2036, &(Bool){1});
    ;
    ;
    U64 _t2039 = 0;
    (void)_t2039;
    Str *_t2040 = Str_lit(")", 1ULL);
    (void)_t2040;
    Array_set(_va49, &(U64){_t2039}, _t2040);
    ;
    println(_va49);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2062 = malloc(sizeof(I64));
    *_t2062 = 0;
    (void)_t2062;
    Expr *body = Expr_child(enum_def, _t2062);
    (void)body;
    {
        U64 _fi2041 = 0;
        (void)_fi2041;
        while (1) {
            I64 _t2049; { I64 *_hp = (I64 *)Expr_child_count(body); _t2049 = *_hp; free(_hp); }
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
            U64 _t2053; { U64 *_hp = (U64 *)Range_len(_t2052); _t2053 = *_hp; free(_hp); }
            (void)_t2053;
            Range_delete(_t2052, &(Bool){1});
            Bool _wcond2042; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2041}, &(U64){_t2053}); _wcond2042 = *_hp; free(_hp); }
            (void)_wcond2042;
            ;
            if (_wcond2042) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2054; { I64 *_hp = (I64 *)Expr_child_count(body); _t2054 = *_hp; free(_hp); }
            (void)_t2054;
            U64 _t2055 = 0;
            (void)_t2055;
            U64 _t2056 = I64_to_u64(_t2054);
            (void)_t2056;
            ;
            Range *_t2057 = Range_new(_t2055, _t2056);
            (void)_t2057;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2057, _fi2041); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2057, &(Bool){1});
            U64 _t2058 = 1;
            (void)_t2058;
            U64 _t2059 = U64_add(_fi2041, _t2058);
            (void)_t2059;
            ;
            _fi2041 = _t2059;
            ;
            I64 *_t2060 = malloc(sizeof(I64)); *_t2060 = U64_to_i64(i);
            (void)_t2060;
            ;
            Expr *f = Expr_child(body, _t2060);
            (void)f;
            Bool _t2061; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2061 = *_hp; free(_hp); }
            (void)_t2061;
            if (_t2061) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2044; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2044 = *_hp; free(_hp); }
                (void)_t2044;
                U64 _t2045 = 0;
                (void)_t2045;
                Bool _t2046 = Bool_not(decl->is_namespace);
                (void)_t2046;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2047; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2044}, &(U64){_t2045}); _t2047 = *_hp; free(_hp); }
                (void)_t2047;
                ;
                ;
                Bool _t2048 = Bool_and(_t2046, _t2047);
                (void)_t2048;
                ;
                ;
                if (_t2048) {
                    Bool _t2043 = 1;
                    (void)_t2043;
                    ;
                    I64_delete(_t2060, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2043; return _r; }
                }
                ;
            }
            I64_delete(_t2060, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2062, &(Bool){1});
    Bool _t2063 = 0;
    (void)_t2063;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2063; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2083 = malloc(sizeof(I64));
    *_t2083 = 0;
    (void)_t2083;
    Expr *body = Expr_child(enum_def, _t2083);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2064 = 0;
        (void)_fi2064;
        while (1) {
            I64 _t2070; { I64 *_hp = (I64 *)Expr_child_count(body); _t2070 = *_hp; free(_hp); }
            (void)_t2070;
            U64 _t2071 = 0;
            (void)_t2071;
            U64 _t2072 = I64_to_u64(_t2070);
            (void)_t2072;
            ;
            Range *_t2073 = Range_new(_t2071, _t2072);
            (void)_t2073;
            ;
            ;
            U64 _t2074; { U64 *_hp = (U64 *)Range_len(_t2073); _t2074 = *_hp; free(_hp); }
            (void)_t2074;
            Range_delete(_t2073, &(Bool){1});
            Bool _wcond2065; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2064}, &(U64){_t2074}); _wcond2065 = *_hp; free(_hp); }
            (void)_wcond2065;
            ;
            if (_wcond2065) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2075; { I64 *_hp = (I64 *)Expr_child_count(body); _t2075 = *_hp; free(_hp); }
            (void)_t2075;
            U64 _t2076 = 0;
            (void)_t2076;
            U64 _t2077 = I64_to_u64(_t2075);
            (void)_t2077;
            ;
            Range *_t2078 = Range_new(_t2076, _t2077);
            (void)_t2078;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2078, _fi2064); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2078, &(Bool){1});
            U64 _t2079 = 1;
            (void)_t2079;
            U64 _t2080 = U64_add(_fi2064, _t2079);
            (void)_t2080;
            ;
            _fi2064 = _t2080;
            ;
            I64 *_t2081 = malloc(sizeof(I64)); *_t2081 = U64_to_i64(i);
            (void)_t2081;
            ;
            Expr *f = Expr_child(body, _t2081);
            (void)f;
            Bool _t2082; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2082 = *_hp; free(_hp); }
            (void)_t2082;
            if (_t2082) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2069 = Bool_not(decl->is_namespace);
                (void)_t2069;
                if (_t2069) {
                    Bool _t2066; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2066 = *_hp; free(_hp); }
                    (void)_t2066;
                    if (_t2066) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2081, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2067 = 1;
                    (void)_t2067;
                    I32 _t2068 = I32_add(tag, _t2067);
                    (void)_t2068;
                    ;
                    tag = _t2068;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2081, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2083, &(Bool){1});
    ;
    I64 _t2084 = 0;
    (void)_t2084;
    I64 _t2085 = 1;
    (void)_t2085;
    I64 _t2086 = I64_sub(_t2084, _t2085);
    (void)_t2086;
    ;
    ;
    I32 _t2087 = I64_to_i32(_t2086);
    (void)_t2087;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2087; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2107 = malloc(sizeof(I64));
    *_t2107 = 0;
    (void)_t2107;
    Expr *body = Expr_child(enum_def, _t2107);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi2088 = 0;
        (void)_fi2088;
        while (1) {
            I64 _t2094; { I64 *_hp = (I64 *)Expr_child_count(body); _t2094 = *_hp; free(_hp); }
            (void)_t2094;
            U64 _t2095 = 0;
            (void)_t2095;
            U64 _t2096 = I64_to_u64(_t2094);
            (void)_t2096;
            ;
            Range *_t2097 = Range_new(_t2095, _t2096);
            (void)_t2097;
            ;
            ;
            U64 _t2098; { U64 *_hp = (U64 *)Range_len(_t2097); _t2098 = *_hp; free(_hp); }
            (void)_t2098;
            Range_delete(_t2097, &(Bool){1});
            Bool _wcond2089; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2088}, &(U64){_t2098}); _wcond2089 = *_hp; free(_hp); }
            (void)_wcond2089;
            ;
            if (_wcond2089) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2099; { I64 *_hp = (I64 *)Expr_child_count(body); _t2099 = *_hp; free(_hp); }
            (void)_t2099;
            U64 _t2100 = 0;
            (void)_t2100;
            U64 _t2101 = I64_to_u64(_t2099);
            (void)_t2101;
            ;
            Range *_t2102 = Range_new(_t2100, _t2101);
            (void)_t2102;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2102, _fi2088); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2102, &(Bool){1});
            U64 _t2103 = 1;
            (void)_t2103;
            U64 _t2104 = U64_add(_fi2088, _t2103);
            (void)_t2104;
            ;
            _fi2088 = _t2104;
            ;
            I64 *_t2105 = malloc(sizeof(I64)); *_t2105 = U64_to_i64(i);
            (void)_t2105;
            ;
            Expr *f = Expr_child(body, _t2105);
            (void)f;
            Bool _t2106; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2106 = *_hp; free(_hp); }
            (void)_t2106;
            if (_t2106) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2093 = Bool_not(decl->is_namespace);
                (void)_t2093;
                if (_t2093) {
                    Bool _t2090 = I32_eq(idx, tag);
                    (void)_t2090;
                    if (_t2090) {
                        ;
                        ;
                        I64_delete(_t2105, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2091 = 1;
                    (void)_t2091;
                    I32 _t2092 = I32_add(idx, _t2091);
                    (void)_t2092;
                    ;
                    idx = _t2092;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2105, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2107, &(Bool){1});
    ;
    Str *_t2108 = Str_lit("", 0ULL);
    (void)_t2108;
    return _t2108;
}

