#include "til_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw1271 = TilType_clone(t);
        (void)_sw1271;
        Bool _t1306; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_Unknown()); _t1306 = *_hp; free(_hp); }
        (void)_t1306;
        if (_t1306) {
            Str *_t1272 = Str_lit("unknown", 7ULL);
            (void)_t1272;
            TilType_delete(_sw1271, &(Bool){1});
            ;
            return _t1272;
        } else {
            Bool _t1305; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_None()); _t1305 = *_hp; free(_hp); }
            (void)_t1305;
            if (_t1305) {
                Str *_t1273 = Str_lit("None", 4ULL);
                (void)_t1273;
                ;
                TilType_delete(_sw1271, &(Bool){1});
                ;
                return _t1273;
            } else {
                Bool _t1304; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_I64()); _t1304 = *_hp; free(_hp); }
                (void)_t1304;
                if (_t1304) {
                    Str *_t1274 = Str_lit("I64", 3ULL);
                    (void)_t1274;
                    ;
                    ;
                    TilType_delete(_sw1271, &(Bool){1});
                    ;
                    return _t1274;
                } else {
                    Bool _t1303; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_U8()); _t1303 = *_hp; free(_hp); }
                    (void)_t1303;
                    if (_t1303) {
                        Str *_t1275 = Str_lit("U8", 2ULL);
                        (void)_t1275;
                        ;
                        ;
                        ;
                        TilType_delete(_sw1271, &(Bool){1});
                        ;
                        return _t1275;
                    } else {
                        Bool _t1302; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_I16()); _t1302 = *_hp; free(_hp); }
                        (void)_t1302;
                        if (_t1302) {
                            Str *_t1276 = Str_lit("I16", 3ULL);
                            (void)_t1276;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw1271, &(Bool){1});
                            ;
                            return _t1276;
                        } else {
                            Bool _t1301; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_I32()); _t1301 = *_hp; free(_hp); }
                            (void)_t1301;
                            if (_t1301) {
                                Str *_t1277 = Str_lit("I32", 3ULL);
                                (void)_t1277;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw1271, &(Bool){1});
                                ;
                                return _t1277;
                            } else {
                                Bool _t1300; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_U32()); _t1300 = *_hp; free(_hp); }
                                (void)_t1300;
                                if (_t1300) {
                                    Str *_t1278 = Str_lit("U32", 3ULL);
                                    (void)_t1278;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw1271, &(Bool){1});
                                    ;
                                    return _t1278;
                                } else {
                                    Bool _t1299; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_U64()); _t1299 = *_hp; free(_hp); }
                                    (void)_t1299;
                                    if (_t1299) {
                                        Str *_t1279 = Str_lit("U64", 3ULL);
                                        (void)_t1279;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw1271, &(Bool){1});
                                        ;
                                        return _t1279;
                                    } else {
                                        Bool _t1298; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_F32()); _t1298 = *_hp; free(_hp); }
                                        (void)_t1298;
                                        if (_t1298) {
                                            Str *_t1280 = Str_lit("F32", 3ULL);
                                            (void)_t1280;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw1271, &(Bool){1});
                                            ;
                                            return _t1280;
                                        } else {
                                            Bool _t1297; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_Bool()); _t1297 = *_hp; free(_hp); }
                                            (void)_t1297;
                                            if (_t1297) {
                                                Str *_t1281 = Str_lit("Bool", 4ULL);
                                                (void)_t1281;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw1271, &(Bool){1});
                                                ;
                                                return _t1281;
                                            } else {
                                                Bool _t1296; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_Struct()); _t1296 = *_hp; free(_hp); }
                                                (void)_t1296;
                                                if (_t1296) {
                                                    Str *_t1282 = Str_lit("Struct", 6ULL);
                                                    (void)_t1282;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw1271, &(Bool){1});
                                                    ;
                                                    return _t1282;
                                                } else {
                                                    Bool _t1295; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_StructDef()); _t1295 = *_hp; free(_hp); }
                                                    (void)_t1295;
                                                    if (_t1295) {
                                                        Str *_t1283 = Str_lit("StructDef", 9ULL);
                                                        (void)_t1283;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw1271, &(Bool){1});
                                                        ;
                                                        return _t1283;
                                                    } else {
                                                        Bool _t1294; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_Enum()); _t1294 = *_hp; free(_hp); }
                                                        (void)_t1294;
                                                        if (_t1294) {
                                                            Str *_t1284 = Str_lit("Enum", 4ULL);
                                                            (void)_t1284;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw1271, &(Bool){1});
                                                            ;
                                                            return _t1284;
                                                        } else {
                                                            Bool _t1293; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_EnumDef()); _t1293 = *_hp; free(_hp); }
                                                            (void)_t1293;
                                                            if (_t1293) {
                                                                Str *_t1285 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t1285;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw1271, &(Bool){1});
                                                                ;
                                                                return _t1285;
                                                            } else {
                                                                Bool _t1292; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_FuncDef()); _t1292 = *_hp; free(_hp); }
                                                                (void)_t1292;
                                                                if (_t1292) {
                                                                    Str *_t1286 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t1286;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw1271, &(Bool){1});
                                                                    ;
                                                                    return _t1286;
                                                                } else {
                                                                    Bool _t1291; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_FuncPtr()); _t1291 = *_hp; free(_hp); }
                                                                    (void)_t1291;
                                                                    if (_t1291) {
                                                                        Str *_t1287 = Str_lit("Fn", 2ULL);
                                                                        (void)_t1287;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw1271, &(Bool){1});
                                                                        ;
                                                                        return _t1287;
                                                                    } else {
                                                                        Bool _t1290; { Bool *_hp = (Bool *)TilType_eq(_sw1271, TilType_Dynamic()); _t1290 = *_hp; free(_hp); }
                                                                        (void)_t1290;
                                                                        if (_t1290) {
                                                                            Str *_t1288 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t1288;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1271, &(Bool){1});
                                                                            ;
                                                                            return _t1288;
                                                                        } else {
                                                                            Str *_t1289 = Str_lit("?", 1ULL);
                                                                            (void)_t1289;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1271, &(Bool){1});
                                                                            ;
                                                                            return _t1289;
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
        TilType_delete(_sw1271, &(Bool){1});
        ;
    }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t1308 = Bool_clone(&self->is_mut);
    (void)_t1308;
    Bool _t1309 = Bool_clone(&self->is_namespace);
    (void)_t1309;
    Bool _t1310 = Bool_clone(&self->is_ref);
    (void)_t1310;
    Bool _t1311 = Bool_clone(&self->is_own);
    (void)_t1311;
    I32 _t1312 = I32_clone(&self->field_offset);
    (void)_t1312;
    I32 _t1313 = I32_clone(&self->field_size);
    (void)_t1313;
    Declaration *_t1314 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t1314->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t1314->explicit_type = *_ca; free(_ca); }
    _t1314->is_mut = _t1308;
    _t1314->is_namespace = _t1309;
    _t1314->is_ref = _t1310;
    _t1314->is_own = _t1311;
    _t1314->field_offset = _t1312;
    _t1314->field_size = _t1313;
    _t1314->field_struct_def = self->field_struct_def;
    _t1314->fn_sig = self->fn_sig;
    (void)_t1314;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t1314;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1315 = 0;
    (void)_t1315;
    Str_delete(&self->name, &(Bool){_t1315});
    ;
    Bool _t1316 = 0;
    (void)_t1316;
    Str_delete(&self->explicit_type, &(Bool){_t1316});
    ;
    Bool _t1317 = 0;
    (void)_t1317;
    Bool_delete(&self->is_mut, &(Bool){_t1317});
    ;
    Bool _t1318 = 0;
    (void)_t1318;
    Bool_delete(&self->is_namespace, &(Bool){_t1318});
    ;
    Bool _t1319 = 0;
    (void)_t1319;
    Bool_delete(&self->is_ref, &(Bool){_t1319});
    ;
    Bool _t1320 = 0;
    (void)_t1320;
    Bool_delete(&self->is_own, &(Bool){_t1320});
    ;
    Bool _t1321 = 0;
    (void)_t1321;
    I32_delete(&self->field_offset, &(Bool){_t1321});
    ;
    Bool _t1322 = 0;
    (void)_t1322;
    I32_delete(&self->field_size, &(Bool){_t1322});
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
    Bool _t1356 = Bool_clone(&self->is_mut);
    (void)_t1356;
    Bool _t1357 = Bool_clone(&self->is_own);
    (void)_t1357;
    Bool _t1358 = Bool_clone(&self->is_shallow);
    (void)_t1358;
    Param *_t1359 = malloc(sizeof(Param));
    { Str *_ca = Str_clone(&self->name); _t1359->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->ptype); _t1359->ptype = *_ca; free(_ca); }
    _t1359->is_mut = _t1356;
    _t1359->is_own = _t1357;
    _t1359->is_shallow = _t1358;
    (void)_t1359;
    ;
    ;
    ;
    return _t1359;
}

void Param_delete(Param * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1360 = 0;
    (void)_t1360;
    Str_delete(&self->name, &(Bool){_t1360});
    ;
    Bool _t1361 = 0;
    (void)_t1361;
    Str_delete(&self->ptype, &(Bool){_t1361});
    ;
    Bool _t1362 = 0;
    (void)_t1362;
    Bool_delete(&self->is_mut, &(Bool){_t1362});
    ;
    Bool _t1363 = 0;
    (void)_t1363;
    Bool_delete(&self->is_own, &(Bool){_t1363});
    ;
    Bool _t1364 = 0;
    (void)_t1364;
    Bool_delete(&self->is_shallow, &(Bool){_t1364});
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
    U32 _t1367 = U32_clone(&self->nparam);
    (void)_t1367;
    I32 _t1368 = I32_clone(&self->variadic_index);
    (void)_t1368;
    I32 _t1369 = I32_clone(&self->kwargs_index);
    (void)_t1369;
    Bool _t1370 = Bool_clone(&self->return_is_ref);
    (void)_t1370;
    Bool _t1371 = Bool_clone(&self->return_is_shallow);
    (void)_t1371;
    FunctionDef *_t1372 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1372->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); _t1372->params = *_ca; free(_ca); }
    _t1372->nparam = _t1367;
    { Map *_ca = Map_clone(&self->param_defaults); _t1372->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1372->return_type = *_ca; free(_ca); }
    _t1372->variadic_index = _t1368;
    _t1372->kwargs_index = _t1369;
    _t1372->return_is_ref = _t1370;
    _t1372->return_is_shallow = _t1371;
    (void)_t1372;
    ;
    ;
    ;
    ;
    ;
    return _t1372;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1373 = 0;
    (void)_t1373;
    FuncType_delete(&self->func_type, &(Bool){_t1373});
    ;
    Bool _t1374 = 0;
    (void)_t1374;
    Vec_delete(&self->params, &(Bool){_t1374});
    ;
    Bool _t1375 = 0;
    (void)_t1375;
    U32_delete(&self->nparam, &(Bool){_t1375});
    ;
    Bool _t1376 = 0;
    (void)_t1376;
    Map_delete(&self->param_defaults, &(Bool){_t1376});
    ;
    Bool _t1377 = 0;
    (void)_t1377;
    Str_delete(&self->return_type, &(Bool){_t1377});
    ;
    Bool _t1378 = 0;
    (void)_t1378;
    I32_delete(&self->variadic_index, &(Bool){_t1378});
    ;
    Bool _t1379 = 0;
    (void)_t1379;
    I32_delete(&self->kwargs_index, &(Bool){_t1379});
    ;
    Bool _t1380 = 0;
    (void)_t1380;
    Bool_delete(&self->return_is_ref, &(Bool){_t1380});
    ;
    Bool _t1381 = 0;
    (void)_t1381;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1381});
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
    Bool _t1760 = 0;
    (void)_t1760;
    ExprData_delete(&self->data, &(Bool){_t1760});
    ;
    Bool _t1761 = 0;
    (void)_t1761;
    TilType_delete(&self->til_type, &(Bool){_t1761});
    ;
    Bool _t1762 = 0;
    (void)_t1762;
    Str_delete(&self->struct_name, &(Bool){_t1762});
    ;
    Bool _t1763 = 0;
    (void)_t1763;
    Bool_delete(&self->is_own_arg, &(Bool){_t1763});
    ;
    Bool _t1764 = 0;
    (void)_t1764;
    Bool_delete(&self->is_splat, &(Bool){_t1764});
    ;
    Bool _t1765 = 0;
    (void)_t1765;
    Bool_delete(&self->is_own_field, &(Bool){_t1765});
    ;
    Bool _t1766 = 0;
    (void)_t1766;
    Bool_delete(&self->is_ref_field, &(Bool){_t1766});
    ;
    Bool _t1767 = 0;
    (void)_t1767;
    Bool_delete(&self->is_ns_field, &(Bool){_t1767});
    ;
    Bool _t1768 = 0;
    (void)_t1768;
    Bool_delete(&self->is_ext, &(Bool){_t1768});
    ;
    Bool _t1769 = 0;
    (void)_t1769;
    Bool_delete(&self->is_core, &(Bool){_t1769});
    ;
    Bool _t1770 = 0;
    (void)_t1770;
    Bool_delete(&self->save_old_delete, &(Bool){_t1770});
    ;
    Bool _t1771 = 0;
    (void)_t1771;
    I32_delete(&self->total_struct_size, &(Bool){_t1771});
    ;
    Bool _t1772 = 0;
    (void)_t1772;
    I32_delete(&self->variadic_index, &(Bool){_t1772});
    ;
    Bool _t1773 = 0;
    (void)_t1773;
    U32_delete(&self->variadic_count, &(Bool){_t1773});
    ;
    Bool _t1774 = 0;
    (void)_t1774;
    I32_delete(&self->kwargs_index, &(Bool){_t1774});
    ;
    Bool _t1775 = 0;
    (void)_t1775;
    U32_delete(&self->kwargs_count, &(Bool){_t1775});
    ;
    Bool _t1776 = 0;
    (void)_t1776;
    Vec_delete(&self->children, &(Bool){_t1776});
    ;
    Bool _t1777 = 0;
    (void)_t1777;
    U32_delete(&self->line, &(Bool){_t1777});
    ;
    Bool _t1778 = 0;
    (void)_t1778;
    U32_delete(&self->col, &(Bool){_t1778});
    ;
    Bool _t1779 = 0;
    (void)_t1779;
    Str_delete(&self->path, &(Bool){_t1779});
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
        ExprData *_sw1781 = ExprData_clone(data);
        (void)_sw1781;
        Bool _t1832; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Body()); _t1832 = *_hp; free(_hp); }
        (void)_t1832;
        if (_t1832) {
            Str *_t1782 = Str_lit("body", 4ULL);
            (void)_t1782;
            ExprData_delete(_sw1781, &(Bool){1});
            ;
            return _t1782;
        } else {
            Bool _t1831; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1781); _t1831 = *_hp; free(_hp); }
            (void)_t1831;
            if (_t1831) {
                Str *_t1783 = Str_lit("str", 3ULL);
                (void)_t1783;
                ;
                ExprData_delete(_sw1781, &(Bool){1});
                ;
                return _t1783;
            } else {
                Bool _t1830; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1781); _t1830 = *_hp; free(_hp); }
                (void)_t1830;
                if (_t1830) {
                    Str *_t1784 = Str_lit("num", 3ULL);
                    (void)_t1784;
                    ;
                    ;
                    ExprData_delete(_sw1781, &(Bool){1});
                    ;
                    return _t1784;
                } else {
                    Bool _t1829; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1781); _t1829 = *_hp; free(_hp); }
                    (void)_t1829;
                    if (_t1829) {
                        Str *_t1785 = Str_lit("bool", 4ULL);
                        (void)_t1785;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1781, &(Bool){1});
                        ;
                        return _t1785;
                    } else {
                        Bool _t1828; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_LiteralNull()); _t1828 = *_hp; free(_hp); }
                        (void)_t1828;
                        if (_t1828) {
                            Str *_t1786 = Str_lit("null", 4ULL);
                            (void)_t1786;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1781, &(Bool){1});
                            ;
                            return _t1786;
                        } else {
                            Bool _t1827; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1781); _t1827 = *_hp; free(_hp); }
                            (void)_t1827;
                            if (_t1827) {
                                Str *_t1787 = Str_lit("ident", 5ULL);
                                (void)_t1787;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1781, &(Bool){1});
                                ;
                                return _t1787;
                            } else {
                                Bool _t1826; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1781); _t1826 = *_hp; free(_hp); }
                                (void)_t1826;
                                if (_t1826) {
                                    Str *_t1788 = Str_lit("decl", 4ULL);
                                    (void)_t1788;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1781, &(Bool){1});
                                    ;
                                    return _t1788;
                                } else {
                                    Bool _t1825; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1781); _t1825 = *_hp; free(_hp); }
                                    (void)_t1825;
                                    if (_t1825) {
                                        Str *_t1789 = Str_lit("assign", 6ULL);
                                        (void)_t1789;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1781, &(Bool){1});
                                        ;
                                        return _t1789;
                                    } else {
                                        Bool _t1824; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_FCall()); _t1824 = *_hp; free(_hp); }
                                        (void)_t1824;
                                        if (_t1824) {
                                            Str *_t1790 = Str_lit("fcall", 5ULL);
                                            (void)_t1790;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1781, &(Bool){1});
                                            ;
                                            return _t1790;
                                        } else {
                                            Bool _t1823; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1781); _t1823 = *_hp; free(_hp); }
                                            (void)_t1823;
                                            if (_t1823) {
                                                Str *_t1791 = Str_lit("func_def", 8ULL);
                                                (void)_t1791;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw1781, &(Bool){1});
                                                ;
                                                return _t1791;
                                            } else {
                                                Bool _t1822; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_StructDef()); _t1822 = *_hp; free(_hp); }
                                                (void)_t1822;
                                                if (_t1822) {
                                                    Str *_t1792 = Str_lit("struct_def", 10ULL);
                                                    (void)_t1792;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw1781, &(Bool){1});
                                                    ;
                                                    return _t1792;
                                                } else {
                                                    Bool _t1821; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_EnumDef()); _t1821 = *_hp; free(_hp); }
                                                    (void)_t1821;
                                                    if (_t1821) {
                                                        Str *_t1793 = Str_lit("enum_def", 8ULL);
                                                        (void)_t1793;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw1781, &(Bool){1});
                                                        ;
                                                        return _t1793;
                                                    } else {
                                                        Bool _t1820; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1781); _t1820 = *_hp; free(_hp); }
                                                        (void)_t1820;
                                                        if (_t1820) {
                                                            Str *_t1794 = Str_lit("field_access", 12ULL);
                                                            (void)_t1794;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw1781, &(Bool){1});
                                                            ;
                                                            return _t1794;
                                                        } else {
                                                            Bool _t1819; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1781); _t1819 = *_hp; free(_hp); }
                                                            (void)_t1819;
                                                            if (_t1819) {
                                                                Str *_t1795 = Str_lit("field_assign", 12ULL);
                                                                (void)_t1795;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw1781, &(Bool){1});
                                                                ;
                                                                return _t1795;
                                                            } else {
                                                                Bool _t1818; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Return()); _t1818 = *_hp; free(_hp); }
                                                                (void)_t1818;
                                                                if (_t1818) {
                                                                    Str *_t1796 = Str_lit("return", 6ULL);
                                                                    (void)_t1796;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw1781, &(Bool){1});
                                                                    ;
                                                                    return _t1796;
                                                                } else {
                                                                    Bool _t1817; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_If()); _t1817 = *_hp; free(_hp); }
                                                                    (void)_t1817;
                                                                    if (_t1817) {
                                                                        Str *_t1797 = Str_lit("if", 2ULL);
                                                                        (void)_t1797;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw1781, &(Bool){1});
                                                                        ;
                                                                        return _t1797;
                                                                    } else {
                                                                        Bool _t1816; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_While()); _t1816 = *_hp; free(_hp); }
                                                                        (void)_t1816;
                                                                        if (_t1816) {
                                                                            Str *_t1798 = Str_lit("while", 5ULL);
                                                                            (void)_t1798;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw1781, &(Bool){1});
                                                                            ;
                                                                            return _t1798;
                                                                        } else {
                                                                            Bool _t1815; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1781); _t1815 = *_hp; free(_hp); }
                                                                            (void)_t1815;
                                                                            if (_t1815) {
                                                                                Str *_t1799 = Str_lit("for_in", 6ULL);
                                                                                (void)_t1799;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw1781, &(Bool){1});
                                                                                ;
                                                                                return _t1799;
                                                                            } else {
                                                                                Bool _t1814; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1781); _t1814 = *_hp; free(_hp); }
                                                                                (void)_t1814;
                                                                                if (_t1814) {
                                                                                    Str *_t1800 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t1800;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw1781, &(Bool){1});
                                                                                    ;
                                                                                    return _t1800;
                                                                                } else {
                                                                                    Bool _t1813; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Break()); _t1813 = *_hp; free(_hp); }
                                                                                    (void)_t1813;
                                                                                    if (_t1813) {
                                                                                        Str *_t1801 = Str_lit("break", 5ULL);
                                                                                        (void)_t1801;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw1781, &(Bool){1});
                                                                                        ;
                                                                                        return _t1801;
                                                                                    } else {
                                                                                        Bool _t1812; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Continue()); _t1812 = *_hp; free(_hp); }
                                                                                        (void)_t1812;
                                                                                        if (_t1812) {
                                                                                            Str *_t1802 = Str_lit("continue", 8ULL);
                                                                                            (void)_t1802;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw1781, &(Bool){1});
                                                                                            ;
                                                                                            return _t1802;
                                                                                        } else {
                                                                                            Bool _t1811; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_MapLit()); _t1811 = *_hp; free(_hp); }
                                                                                            (void)_t1811;
                                                                                            if (_t1811) {
                                                                                                Str *_t1803 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t1803;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw1781, &(Bool){1});
                                                                                                ;
                                                                                                return _t1803;
                                                                                            } else {
                                                                                                Bool _t1810; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_SetLit()); _t1810 = *_hp; free(_hp); }
                                                                                                (void)_t1810;
                                                                                                if (_t1810) {
                                                                                                    Str *_t1804 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t1804;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw1781, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1804;
                                                                                                } else {
                                                                                                    Bool _t1809; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Switch()); _t1809 = *_hp; free(_hp); }
                                                                                                    (void)_t1809;
                                                                                                    if (_t1809) {
                                                                                                        Str *_t1805 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t1805;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw1781, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1805;
                                                                                                    } else {
                                                                                                        Bool _t1808; { Bool *_hp = (Bool *)ExprData_eq(_sw1781, ExprData_Case()); _t1808 = *_hp; free(_hp); }
                                                                                                        (void)_t1808;
                                                                                                        if (_t1808) {
                                                                                                            Str *_t1806 = Str_lit("case", 4ULL);
                                                                                                            (void)_t1806;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1781, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1806;
                                                                                                        } else {
                                                                                                            Str *_t1807 = Str_lit("?", 1ULL);
                                                                                                            (void)_t1807;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1781, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1807;
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
        ExprData_delete(_sw1781, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1833 = FuncType_clone(ft);
        (void)_sw1833;
        Bool _t1846; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_Func()); _t1846 = *_hp; free(_hp); }
        (void)_t1846;
        if (_t1846) {
            Str *_t1834 = Str_lit("func", 4ULL);
            (void)_t1834;
            FuncType_delete(_sw1833, &(Bool){1});
            ;
            return _t1834;
        } else {
            Bool _t1845; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_Proc()); _t1845 = *_hp; free(_hp); }
            (void)_t1845;
            if (_t1845) {
                Str *_t1835 = Str_lit("proc", 4ULL);
                (void)_t1835;
                ;
                FuncType_delete(_sw1833, &(Bool){1});
                ;
                return _t1835;
            } else {
                Bool _t1844; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_Test()); _t1844 = *_hp; free(_hp); }
                (void)_t1844;
                if (_t1844) {
                    Str *_t1836 = Str_lit("test", 4ULL);
                    (void)_t1836;
                    ;
                    ;
                    FuncType_delete(_sw1833, &(Bool){1});
                    ;
                    return _t1836;
                } else {
                    Bool _t1843; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_Macro()); _t1843 = *_hp; free(_hp); }
                    (void)_t1843;
                    if (_t1843) {
                        Str *_t1837 = Str_lit("macro", 5ULL);
                        (void)_t1837;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1833, &(Bool){1});
                        ;
                        return _t1837;
                    } else {
                        Bool _t1842; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_ExtFunc()); _t1842 = *_hp; free(_hp); }
                        (void)_t1842;
                        if (_t1842) {
                            Str *_t1838 = Str_lit("ext_func", 8ULL);
                            (void)_t1838;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1833, &(Bool){1});
                            ;
                            return _t1838;
                        } else {
                            Bool _t1841; { Bool *_hp = (Bool *)FuncType_eq(_sw1833, FuncType_ExtProc()); _t1841 = *_hp; free(_hp); }
                            (void)_t1841;
                            if (_t1841) {
                                Str *_t1839 = Str_lit("ext_proc", 8ULL);
                                (void)_t1839;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1833, &(Bool){1});
                                ;
                                return _t1839;
                            } else {
                                Str *_t1840 = Str_lit("?", 1ULL);
                                (void)_t1840;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1833, &(Bool){1});
                                ;
                                return _t1840;
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
        FuncType_delete(_sw1833, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        I64 _t1857 = U32_to_i64(indent);
        (void)_t1857;
        U64 _t1858 = 0;
        (void)_t1858;
        U64 _t1859 = I64_to_u64(_t1857);
        (void)_t1859;
        ;
        Range *_fc1847 = Range_new(_t1858, _t1859);
        (void)_fc1847;
        ;
        ;
        U64 _fi1847 = 0;
        (void)_fi1847;
        while (1) {
            U64 _t1849; { U64 *_hp = (U64 *)Range_len(_fc1847); _t1849 = *_hp; free(_hp); }
            (void)_t1849;
            Bool _wcond1848; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1847}, &(U64){_t1849}); _wcond1848 = *_hp; free(_hp); }
            (void)_wcond1848;
            ;
            if (_wcond1848) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc1847, _fi1847); i = *_hp; free(_hp); }
            (void)i;
            ;
            U64 _t1850 = 1;
            (void)_t1850;
            U64 _t1851 = U64_add(_fi1847, _t1850);
            (void)_t1851;
            ;
            _fi1847 = _t1851;
            ;
            Str *_t1852 = Str_lit("Str", 3ULL);
            (void)_t1852;
            U64 _t1853; { U64 *_hp = (U64 *)Str_size(); _t1853 = *_hp; free(_hp); }
            (void)_t1853;
            U64 _t1854 = 1;
            (void)_t1854;
            Array *_va37 = Array_new(_t1852, &(U64){_t1853}, &(U64){_t1854});
            (void)_va37;
            Str_delete(_t1852, &(Bool){1});
            ;
            ;
            U64 _t1855 = 0;
            (void)_t1855;
            Str *_t1856 = Str_lit("  ", 2ULL);
            (void)_t1856;
            Array_set(_va37, &(U64){_t1855}, _t1856);
            ;
            print(_va37);
        }
        Range_delete(_fc1847, &(Bool){1});
        ;
    }
    Str *_t1984 = Str_lit("Str", 3ULL);
    (void)_t1984;
    U64 _t1985; { U64 *_hp = (U64 *)Str_size(); _t1985 = *_hp; free(_hp); }
    (void)_t1985;
    U64 _t1986 = 2;
    (void)_t1986;
    Array *_va51 = Array_new(_t1984, &(U64){_t1985}, &(U64){_t1986});
    (void)_va51;
    Str_delete(_t1984, &(Bool){1});
    ;
    ;
    U64 _t1987 = 0;
    (void)_t1987;
    Str *_t1988 = Str_lit("(", 1ULL);
    (void)_t1988;
    Array_set(_va51, &(U64){_t1987}, _t1988);
    ;
    U64 _t1989 = 1;
    (void)_t1989;
    Str *_t1990 = node_name(&e->data);
    (void)_t1990;
    Array_set(_va51, &(U64){_t1989}, _t1990);
    ;
    print(_va51);
    Bool _t1991; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t1991 = *_hp; free(_hp); }
    (void)_t1991;
    Bool _t1992 = Bool_not(_t1991);
    (void)_t1992;
    ;
    if (_t1992) {
        Str *_t1860 = Str_lit("Str", 3ULL);
        (void)_t1860;
        U64 _t1861; { U64 *_hp = (U64 *)Str_size(); _t1861 = *_hp; free(_hp); }
        (void)_t1861;
        U64 _t1862 = 2;
        (void)_t1862;
        Array *_va38 = Array_new(_t1860, &(U64){_t1861}, &(U64){_t1862});
        (void)_va38;
        Str_delete(_t1860, &(Bool){1});
        ;
        ;
        U64 _t1863 = 0;
        (void)_t1863;
        Str *_t1864 = Str_lit(":", 1ULL);
        (void)_t1864;
        Array_set(_va38, &(U64){_t1863}, _t1864);
        ;
        U64 _t1865 = 1;
        (void)_t1865;
        Str *_t1866 = til_type_name_c(&e->til_type);
        (void)_t1866;
        Array_set(_va38, &(U64){_t1865}, _t1866);
        ;
        print(_va38);
    }
    ;
    {
        ExprData *_sw1867 = ExprData_clone(&e->data);
        (void)_sw1867;
        Bool _t1954; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1867); _t1954 = *_hp; free(_hp); }
        (void)_t1954;
        if (_t1954) {
            Str *s = ExprData_get_Ident(_sw1867);
            (void)s;
            Str *_t1868 = Str_lit("Str", 3ULL);
            (void)_t1868;
            U64 _t1869; { U64 *_hp = (U64 *)Str_size(); _t1869 = *_hp; free(_hp); }
            (void)_t1869;
            U64 _t1870 = 3;
            (void)_t1870;
            Array *_va39 = Array_new(_t1868, &(U64){_t1869}, &(U64){_t1870});
            (void)_va39;
            Str_delete(_t1868, &(Bool){1});
            ;
            ;
            U64 _t1871 = 0;
            (void)_t1871;
            Str *_t1872 = Str_lit(" \"", 3ULL);
            (void)_t1872;
            Array_set(_va39, &(U64){_t1871}, _t1872);
            ;
            U64 _t1873 = 1;
            (void)_t1873;
            Str *_t1874 = Str_clone(s);
            (void)_t1874;
            Str_delete(s, &(Bool){1});
            Array_set(_va39, &(U64){_t1873}, _t1874);
            ;
            U64 _t1875 = 2;
            (void)_t1875;
            Str *_t1876 = Str_lit("\"", 2ULL);
            (void)_t1876;
            Array_set(_va39, &(U64){_t1875}, _t1876);
            ;
            print(_va39);
        } else {
            Bool _t1953; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1867); _t1953 = *_hp; free(_hp); }
            (void)_t1953;
            if (_t1953) {
                Str *s = ExprData_get_LiteralStr(_sw1867);
                (void)s;
                Str *_t1877 = Str_lit("Str", 3ULL);
                (void)_t1877;
                U64 _t1878; { U64 *_hp = (U64 *)Str_size(); _t1878 = *_hp; free(_hp); }
                (void)_t1878;
                U64 _t1879 = 3;
                (void)_t1879;
                Array *_va40 = Array_new(_t1877, &(U64){_t1878}, &(U64){_t1879});
                (void)_va40;
                Str_delete(_t1877, &(Bool){1});
                ;
                ;
                U64 _t1880 = 0;
                (void)_t1880;
                Str *_t1881 = Str_lit(" \"", 3ULL);
                (void)_t1881;
                Array_set(_va40, &(U64){_t1880}, _t1881);
                ;
                U64 _t1882 = 1;
                (void)_t1882;
                Str *_t1883 = Str_clone(s);
                (void)_t1883;
                Str_delete(s, &(Bool){1});
                Array_set(_va40, &(U64){_t1882}, _t1883);
                ;
                U64 _t1884 = 2;
                (void)_t1884;
                Str *_t1885 = Str_lit("\"", 2ULL);
                (void)_t1885;
                Array_set(_va40, &(U64){_t1884}, _t1885);
                ;
                print(_va40);
            } else {
                Bool _t1952; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1867); _t1952 = *_hp; free(_hp); }
                (void)_t1952;
                if (_t1952) {
                    Str *s = ExprData_get_LiteralNum(_sw1867);
                    (void)s;
                    Str *_t1886 = Str_lit("Str", 3ULL);
                    (void)_t1886;
                    U64 _t1887; { U64 *_hp = (U64 *)Str_size(); _t1887 = *_hp; free(_hp); }
                    (void)_t1887;
                    U64 _t1888 = 3;
                    (void)_t1888;
                    Array *_va41 = Array_new(_t1886, &(U64){_t1887}, &(U64){_t1888});
                    (void)_va41;
                    Str_delete(_t1886, &(Bool){1});
                    ;
                    ;
                    U64 _t1889 = 0;
                    (void)_t1889;
                    Str *_t1890 = Str_lit(" \"", 3ULL);
                    (void)_t1890;
                    Array_set(_va41, &(U64){_t1889}, _t1890);
                    ;
                    U64 _t1891 = 1;
                    (void)_t1891;
                    Str *_t1892 = Str_clone(s);
                    (void)_t1892;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va41, &(U64){_t1891}, _t1892);
                    ;
                    U64 _t1893 = 2;
                    (void)_t1893;
                    Str *_t1894 = Str_lit("\"", 2ULL);
                    (void)_t1894;
                    Array_set(_va41, &(U64){_t1893}, _t1894);
                    ;
                    print(_va41);
                } else {
                    Bool _t1951; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1867); _t1951 = *_hp; free(_hp); }
                    (void)_t1951;
                    if (_t1951) {
                        Str *s = ExprData_get_LiteralBool(_sw1867);
                        (void)s;
                        Str *_t1895 = Str_lit("Str", 3ULL);
                        (void)_t1895;
                        U64 _t1896; { U64 *_hp = (U64 *)Str_size(); _t1896 = *_hp; free(_hp); }
                        (void)_t1896;
                        U64 _t1897 = 3;
                        (void)_t1897;
                        Array *_va42 = Array_new(_t1895, &(U64){_t1896}, &(U64){_t1897});
                        (void)_va42;
                        Str_delete(_t1895, &(Bool){1});
                        ;
                        ;
                        U64 _t1898 = 0;
                        (void)_t1898;
                        Str *_t1899 = Str_lit(" \"", 3ULL);
                        (void)_t1899;
                        Array_set(_va42, &(U64){_t1898}, _t1899);
                        ;
                        U64 _t1900 = 1;
                        (void)_t1900;
                        Str *_t1901 = Str_clone(s);
                        (void)_t1901;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va42, &(U64){_t1900}, _t1901);
                        ;
                        U64 _t1902 = 2;
                        (void)_t1902;
                        Str *_t1903 = Str_lit("\"", 2ULL);
                        (void)_t1903;
                        Array_set(_va42, &(U64){_t1902}, _t1903);
                        ;
                        print(_va42);
                    } else {
                        Bool _t1950; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1867); _t1950 = *_hp; free(_hp); }
                        (void)_t1950;
                        if (_t1950) {
                            Str *s = ExprData_get_ForIn(_sw1867);
                            (void)s;
                            Str *_t1904 = Str_lit("Str", 3ULL);
                            (void)_t1904;
                            U64 _t1905; { U64 *_hp = (U64 *)Str_size(); _t1905 = *_hp; free(_hp); }
                            (void)_t1905;
                            U64 _t1906 = 3;
                            (void)_t1906;
                            Array *_va43 = Array_new(_t1904, &(U64){_t1905}, &(U64){_t1906});
                            (void)_va43;
                            Str_delete(_t1904, &(Bool){1});
                            ;
                            ;
                            U64 _t1907 = 0;
                            (void)_t1907;
                            Str *_t1908 = Str_lit(" \"", 3ULL);
                            (void)_t1908;
                            Array_set(_va43, &(U64){_t1907}, _t1908);
                            ;
                            U64 _t1909 = 1;
                            (void)_t1909;
                            Str *_t1910 = Str_clone(s);
                            (void)_t1910;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va43, &(U64){_t1909}, _t1910);
                            ;
                            U64 _t1911 = 2;
                            (void)_t1911;
                            Str *_t1912 = Str_lit("\"", 2ULL);
                            (void)_t1912;
                            Array_set(_va43, &(U64){_t1911}, _t1912);
                            ;
                            print(_va43);
                        } else {
                            Bool _t1949; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1867); _t1949 = *_hp; free(_hp); }
                            (void)_t1949;
                            if (_t1949) {
                                Declaration *decl = ExprData_get_Decl(_sw1867);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1913 = Str_lit("Str", 3ULL);
                                    (void)_t1913;
                                    U64 _t1914; { U64 *_hp = (U64 *)Str_size(); _t1914 = *_hp; free(_hp); }
                                    (void)_t1914;
                                    U64 _t1915 = 1;
                                    (void)_t1915;
                                    Array *_va44 = Array_new(_t1913, &(U64){_t1914}, &(U64){_t1915});
                                    (void)_va44;
                                    Str_delete(_t1913, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1916 = 0;
                                    (void)_t1916;
                                    Str *_t1917 = Str_lit(" mut", 4ULL);
                                    (void)_t1917;
                                    Array_set(_va44, &(U64){_t1916}, _t1917);
                                    ;
                                    print(_va44);
                                }
                                Str *_t1918 = Str_lit("Str", 3ULL);
                                (void)_t1918;
                                U64 _t1919; { U64 *_hp = (U64 *)Str_size(); _t1919 = *_hp; free(_hp); }
                                (void)_t1919;
                                U64 _t1920 = 2;
                                (void)_t1920;
                                Array *_va45 = Array_new(_t1918, &(U64){_t1919}, &(U64){_t1920});
                                (void)_va45;
                                Str_delete(_t1918, &(Bool){1});
                                ;
                                ;
                                U64 _t1921 = 0;
                                (void)_t1921;
                                Str *_t1922 = Str_lit(" ", 1ULL);
                                (void)_t1922;
                                Array_set(_va45, &(U64){_t1921}, _t1922);
                                ;
                                U64 _t1923 = 1;
                                (void)_t1923;
                                Str *_t1924 = Str_clone(&decl->name);
                                (void)_t1924;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va45, &(U64){_t1923}, _t1924);
                                ;
                                print(_va45);
                            } else {
                                Bool _t1948; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1867); _t1948 = *_hp; free(_hp); }
                                (void)_t1948;
                                if (_t1948) {
                                    Str *s = ExprData_get_Assign(_sw1867);
                                    (void)s;
                                    Str *_t1925 = Str_lit("Str", 3ULL);
                                    (void)_t1925;
                                    U64 _t1926; { U64 *_hp = (U64 *)Str_size(); _t1926 = *_hp; free(_hp); }
                                    (void)_t1926;
                                    U64 _t1927 = 2;
                                    (void)_t1927;
                                    Array *_va46 = Array_new(_t1925, &(U64){_t1926}, &(U64){_t1927});
                                    (void)_va46;
                                    Str_delete(_t1925, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1928 = 0;
                                    (void)_t1928;
                                    Str *_t1929 = Str_lit(" ", 1ULL);
                                    (void)_t1929;
                                    Array_set(_va46, &(U64){_t1928}, _t1929);
                                    ;
                                    U64 _t1930 = 1;
                                    (void)_t1930;
                                    Str *_t1931 = Str_clone(s);
                                    (void)_t1931;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va46, &(U64){_t1930}, _t1931);
                                    ;
                                    print(_va46);
                                } else {
                                    Bool _t1947; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1867); _t1947 = *_hp; free(_hp); }
                                    (void)_t1947;
                                    if (_t1947) {
                                        Str *s = ExprData_get_NamedArg(_sw1867);
                                        (void)s;
                                        Str *_t1932 = Str_lit("Str", 3ULL);
                                        (void)_t1932;
                                        U64 _t1933; { U64 *_hp = (U64 *)Str_size(); _t1933 = *_hp; free(_hp); }
                                        (void)_t1933;
                                        U64 _t1934 = 2;
                                        (void)_t1934;
                                        Array *_va47 = Array_new(_t1932, &(U64){_t1933}, &(U64){_t1934});
                                        (void)_va47;
                                        Str_delete(_t1932, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1935 = 0;
                                        (void)_t1935;
                                        Str *_t1936 = Str_lit(" ", 1ULL);
                                        (void)_t1936;
                                        Array_set(_va47, &(U64){_t1935}, _t1936);
                                        ;
                                        U64 _t1937 = 1;
                                        (void)_t1937;
                                        Str *_t1938 = Str_clone(s);
                                        (void)_t1938;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va47, &(U64){_t1937}, _t1938);
                                        ;
                                        print(_va47);
                                    } else {
                                        Bool _t1946; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1867); _t1946 = *_hp; free(_hp); }
                                        (void)_t1946;
                                        if (_t1946) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1867);
                                            (void)fdef;
                                            Str *_t1939 = Str_lit("Str", 3ULL);
                                            (void)_t1939;
                                            U64 _t1940; { U64 *_hp = (U64 *)Str_size(); _t1940 = *_hp; free(_hp); }
                                            (void)_t1940;
                                            U64 _t1941 = 2;
                                            (void)_t1941;
                                            Array *_va48 = Array_new(_t1939, &(U64){_t1940}, &(U64){_t1941});
                                            (void)_va48;
                                            Str_delete(_t1939, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1942 = 0;
                                            (void)_t1942;
                                            Str *_t1943 = Str_lit(" ", 1ULL);
                                            (void)_t1943;
                                            Array_set(_va48, &(U64){_t1942}, _t1943);
                                            ;
                                            U64 _t1944 = 1;
                                            (void)_t1944;
                                            Str *_t1945 = func_type_name(&fdef->func_type);
                                            (void)_t1945;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va48, &(U64){_t1944}, _t1945);
                                            ;
                                            print(_va48);
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
        ExprData_delete(_sw1867, &(Bool){1});
        ;
    }
    U64 _t1993; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1993 = *_hp; free(_hp); }
    (void)_t1993;
    U64 _t1994 = 0;
    (void)_t1994;
    Bool _t1995; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1993}, &(U64){_t1994}); _t1995 = *_hp; free(_hp); }
    (void)_t1995;
    ;
    ;
    if (_t1995) {
        Str *_t1979 = Str_lit("Str", 3ULL);
        (void)_t1979;
        U64 _t1980; { U64 *_hp = (U64 *)Str_size(); _t1980 = *_hp; free(_hp); }
        (void)_t1980;
        U64 _t1981 = 1;
        (void)_t1981;
        Array *_va50 = Array_new(_t1979, &(U64){_t1980}, &(U64){_t1981});
        (void)_va50;
        Str_delete(_t1979, &(Bool){1});
        ;
        ;
        U64 _t1982 = 0;
        (void)_t1982;
        Str *_t1983 = Str_lit("", 0ULL);
        (void)_t1983;
        Array_set(_va50, &(U64){_t1982}, _t1983);
        ;
        println(_va50);
        {
            U64 _t1964 = 0;
            (void)_t1964;
            U64 _t1965; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1965 = *_hp; free(_hp); }
            (void)_t1965;
            Range *_fc1955 = Range_new(_t1964, _t1965);
            (void)_fc1955;
            ;
            ;
            U64 _fi1955 = 0;
            (void)_fi1955;
            while (1) {
                U64 _t1957; { U64 *_hp = (U64 *)Range_len(_fc1955); _t1957 = *_hp; free(_hp); }
                (void)_t1957;
                Bool _wcond1956; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1955}, &(U64){_t1957}); _wcond1956 = *_hp; free(_hp); }
                (void)_wcond1956;
                ;
                if (_wcond1956) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1955, _fi1955); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1958 = 1;
                (void)_t1958;
                U64 _t1959 = U64_add(_fi1955, _t1958);
                (void)_t1959;
                ;
                _fi1955 = _t1959;
                ;
                I64 *_t1960 = malloc(sizeof(I64)); *_t1960 = U64_to_i64(i);
                (void)_t1960;
                ;
                U32 _t1961 = 1;
                (void)_t1961;
                Expr *_t1962 = Expr_child(e, _t1960);
                (void)_t1962;
                U32 _t1963 = U32_add(indent, _t1961);
                (void)_t1963;
                ;
                ast_print(_t1962, _t1963);
                I64_delete(_t1960, &(Bool){1});
                ;
            }
            Range_delete(_fc1955, &(Bool){1});
            ;
        }
        {
            I64 _t1976 = U32_to_i64(indent);
            (void)_t1976;
            U64 _t1977 = 0;
            (void)_t1977;
            U64 _t1978 = I64_to_u64(_t1976);
            (void)_t1978;
            ;
            Range *_fc1966 = Range_new(_t1977, _t1978);
            (void)_fc1966;
            ;
            ;
            U64 _fi1966 = 0;
            (void)_fi1966;
            while (1) {
                U64 _t1968; { U64 *_hp = (U64 *)Range_len(_fc1966); _t1968 = *_hp; free(_hp); }
                (void)_t1968;
                Bool _wcond1967; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1966}, &(U64){_t1968}); _wcond1967 = *_hp; free(_hp); }
                (void)_wcond1967;
                ;
                if (_wcond1967) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1966, _fi1966); i = *_hp; free(_hp); }
                (void)i;
                ;
                U64 _t1969 = 1;
                (void)_t1969;
                U64 _t1970 = U64_add(_fi1966, _t1969);
                (void)_t1970;
                ;
                _fi1966 = _t1970;
                ;
                Str *_t1971 = Str_lit("Str", 3ULL);
                (void)_t1971;
                U64 _t1972; { U64 *_hp = (U64 *)Str_size(); _t1972 = *_hp; free(_hp); }
                (void)_t1972;
                U64 _t1973 = 1;
                (void)_t1973;
                Array *_va49 = Array_new(_t1971, &(U64){_t1972}, &(U64){_t1973});
                (void)_va49;
                Str_delete(_t1971, &(Bool){1});
                ;
                ;
                U64 _t1974 = 0;
                (void)_t1974;
                Str *_t1975 = Str_lit("  ", 2ULL);
                (void)_t1975;
                Array_set(_va49, &(U64){_t1974}, _t1975);
                ;
                print(_va49);
            }
            Range_delete(_fc1966, &(Bool){1});
            ;
        }
    }
    ;
    Str *_t1996 = Str_lit("Str", 3ULL);
    (void)_t1996;
    U64 _t1997; { U64 *_hp = (U64 *)Str_size(); _t1997 = *_hp; free(_hp); }
    (void)_t1997;
    U64 _t1998 = 1;
    (void)_t1998;
    Array *_va52 = Array_new(_t1996, &(U64){_t1997}, &(U64){_t1998});
    (void)_va52;
    Str_delete(_t1996, &(Bool){1});
    ;
    ;
    U64 _t1999 = 0;
    (void)_t1999;
    Str *_t2000 = Str_lit(")", 1ULL);
    (void)_t2000;
    Array_set(_va52, &(U64){_t1999}, _t2000);
    ;
    println(_va52);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2017 = malloc(sizeof(I64));
    *_t2017 = 0;
    (void)_t2017;
    Expr *body = Expr_child(enum_def, _t2017);
    (void)body;
    {
        I64 _t2014; { I64 *_hp = (I64 *)Expr_child_count(body); _t2014 = *_hp; free(_hp); }
        (void)_t2014;
        U64 _t2015 = 0;
        (void)_t2015;
        U64 _t2016 = I64_to_u64(_t2014);
        (void)_t2016;
        ;
        Range *_fc2001 = Range_new(_t2015, _t2016);
        (void)_fc2001;
        ;
        ;
        U64 _fi2001 = 0;
        (void)_fi2001;
        while (1) {
            U64 _t2009; { U64 *_hp = (U64 *)Range_len(_fc2001); _t2009 = *_hp; free(_hp); }
            (void)_t2009;
            Bool _wcond2002; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2001}, &(U64){_t2009}); _wcond2002 = *_hp; free(_hp); }
            (void)_wcond2002;
            ;
            if (_wcond2002) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2001, _fi2001); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2010 = 1;
            (void)_t2010;
            U64 _t2011 = U64_add(_fi2001, _t2010);
            (void)_t2011;
            ;
            _fi2001 = _t2011;
            ;
            I64 *_t2012 = malloc(sizeof(I64)); *_t2012 = U64_to_i64(i);
            (void)_t2012;
            ;
            Expr *f = Expr_child(body, _t2012);
            (void)f;
            Bool _t2013; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2013 = *_hp; free(_hp); }
            (void)_t2013;
            if (_t2013) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2004; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2004 = *_hp; free(_hp); }
                (void)_t2004;
                U64 _t2005 = 0;
                (void)_t2005;
                Bool _t2006 = Bool_not(decl->is_namespace);
                (void)_t2006;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2007; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2004}, &(U64){_t2005}); _t2007 = *_hp; free(_hp); }
                (void)_t2007;
                ;
                ;
                Bool _t2008 = Bool_and(_t2006, _t2007);
                (void)_t2008;
                ;
                ;
                if (_t2008) {
                    Bool _t2003 = 1;
                    (void)_t2003;
                    ;
                    I64_delete(_t2012, &(Bool){1});
                    ;
                    Range_delete(_fc2001, &(Bool){1});
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2003; return _r; }
                }
                ;
            }
            I64_delete(_t2012, &(Bool){1});
            ;
        }
        Range_delete(_fc2001, &(Bool){1});
        ;
    }
    I64_delete(_t2017, &(Bool){1});
    Bool _t2018 = 0;
    (void)_t2018;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2018; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2033 = malloc(sizeof(I64));
    *_t2033 = 0;
    (void)_t2033;
    Expr *body = Expr_child(enum_def, _t2033);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        I64 _t2030; { I64 *_hp = (I64 *)Expr_child_count(body); _t2030 = *_hp; free(_hp); }
        (void)_t2030;
        U64 _t2031 = 0;
        (void)_t2031;
        U64 _t2032 = I64_to_u64(_t2030);
        (void)_t2032;
        ;
        Range *_fc2019 = Range_new(_t2031, _t2032);
        (void)_fc2019;
        ;
        ;
        U64 _fi2019 = 0;
        (void)_fi2019;
        while (1) {
            U64 _t2025; { U64 *_hp = (U64 *)Range_len(_fc2019); _t2025 = *_hp; free(_hp); }
            (void)_t2025;
            Bool _wcond2020; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2019}, &(U64){_t2025}); _wcond2020 = *_hp; free(_hp); }
            (void)_wcond2020;
            ;
            if (_wcond2020) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2019, _fi2019); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2026 = 1;
            (void)_t2026;
            U64 _t2027 = U64_add(_fi2019, _t2026);
            (void)_t2027;
            ;
            _fi2019 = _t2027;
            ;
            I64 *_t2028 = malloc(sizeof(I64)); *_t2028 = U64_to_i64(i);
            (void)_t2028;
            ;
            Expr *f = Expr_child(body, _t2028);
            (void)f;
            Bool _t2029; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2029 = *_hp; free(_hp); }
            (void)_t2029;
            if (_t2029) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2024 = Bool_not(decl->is_namespace);
                (void)_t2024;
                if (_t2024) {
                    Bool _t2021; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2021 = *_hp; free(_hp); }
                    (void)_t2021;
                    if (_t2021) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2028, &(Bool){1});
                        ;
                        Range_delete(_fc2019, &(Bool){1});
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2022 = 1;
                    (void)_t2022;
                    I32 _t2023 = I32_add(tag, _t2022);
                    (void)_t2023;
                    ;
                    tag = _t2023;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2028, &(Bool){1});
            ;
        }
        Range_delete(_fc2019, &(Bool){1});
        ;
    }
    I64_delete(_t2033, &(Bool){1});
    ;
    I64 _t2034 = 0;
    (void)_t2034;
    I64 _t2035 = 1;
    (void)_t2035;
    I64 _t2036 = I64_sub(_t2034, _t2035);
    (void)_t2036;
    ;
    ;
    I32 _t2037 = I64_to_i32(_t2036);
    (void)_t2037;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2037; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2052 = malloc(sizeof(I64));
    *_t2052 = 0;
    (void)_t2052;
    Expr *body = Expr_child(enum_def, _t2052);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        I64 _t2049; { I64 *_hp = (I64 *)Expr_child_count(body); _t2049 = *_hp; free(_hp); }
        (void)_t2049;
        U64 _t2050 = 0;
        (void)_t2050;
        U64 _t2051 = I64_to_u64(_t2049);
        (void)_t2051;
        ;
        Range *_fc2038 = Range_new(_t2050, _t2051);
        (void)_fc2038;
        ;
        ;
        U64 _fi2038 = 0;
        (void)_fi2038;
        while (1) {
            U64 _t2044; { U64 *_hp = (U64 *)Range_len(_fc2038); _t2044 = *_hp; free(_hp); }
            (void)_t2044;
            Bool _wcond2039; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2038}, &(U64){_t2044}); _wcond2039 = *_hp; free(_hp); }
            (void)_wcond2039;
            ;
            if (_wcond2039) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2038, _fi2038); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2045 = 1;
            (void)_t2045;
            U64 _t2046 = U64_add(_fi2038, _t2045);
            (void)_t2046;
            ;
            _fi2038 = _t2046;
            ;
            I64 *_t2047 = malloc(sizeof(I64)); *_t2047 = U64_to_i64(i);
            (void)_t2047;
            ;
            Expr *f = Expr_child(body, _t2047);
            (void)f;
            Bool _t2048; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2048 = *_hp; free(_hp); }
            (void)_t2048;
            if (_t2048) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2043 = Bool_not(decl->is_namespace);
                (void)_t2043;
                if (_t2043) {
                    Bool _t2040 = I32_eq(idx, tag);
                    (void)_t2040;
                    if (_t2040) {
                        ;
                        ;
                        I64_delete(_t2047, &(Bool){1});
                        ;
                        Range_delete(_fc2038, &(Bool){1});
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2041 = 1;
                    (void)_t2041;
                    I32 _t2042 = I32_add(idx, _t2041);
                    (void)_t2042;
                    ;
                    idx = _t2042;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2047, &(Bool){1});
            ;
        }
        Range_delete(_fc2038, &(Bool){1});
        ;
    }
    I64_delete(_t2052, &(Bool){1});
    ;
    Str *_t2053 = Str_lit("", 0ULL);
    (void)_t2053;
    return _t2053;
}

