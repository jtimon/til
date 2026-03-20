#include "modes_ast.h"

Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw1272 = TilType_clone(t);
        (void)_sw1272;
        Bool _t1307; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_Unknown()); _t1307 = *_hp; free(_hp); }
        (void)_t1307;
        if (_t1307) {
            Str *_t1273 = Str_lit("unknown", 7ULL);
            (void)_t1273;
            TilType_delete(_sw1272, &(Bool){1});
            ;
            return _t1273;
        } else {
            Bool _t1306; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_None()); _t1306 = *_hp; free(_hp); }
            (void)_t1306;
            if (_t1306) {
                Str *_t1274 = Str_lit("None", 4ULL);
                (void)_t1274;
                ;
                TilType_delete(_sw1272, &(Bool){1});
                ;
                return _t1274;
            } else {
                Bool _t1305; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_I64()); _t1305 = *_hp; free(_hp); }
                (void)_t1305;
                if (_t1305) {
                    Str *_t1275 = Str_lit("I64", 3ULL);
                    (void)_t1275;
                    ;
                    ;
                    TilType_delete(_sw1272, &(Bool){1});
                    ;
                    return _t1275;
                } else {
                    Bool _t1304; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_U8()); _t1304 = *_hp; free(_hp); }
                    (void)_t1304;
                    if (_t1304) {
                        Str *_t1276 = Str_lit("U8", 2ULL);
                        (void)_t1276;
                        ;
                        ;
                        ;
                        TilType_delete(_sw1272, &(Bool){1});
                        ;
                        return _t1276;
                    } else {
                        Bool _t1303; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_I16()); _t1303 = *_hp; free(_hp); }
                        (void)_t1303;
                        if (_t1303) {
                            Str *_t1277 = Str_lit("I16", 3ULL);
                            (void)_t1277;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw1272, &(Bool){1});
                            ;
                            return _t1277;
                        } else {
                            Bool _t1302; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_I32()); _t1302 = *_hp; free(_hp); }
                            (void)_t1302;
                            if (_t1302) {
                                Str *_t1278 = Str_lit("I32", 3ULL);
                                (void)_t1278;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw1272, &(Bool){1});
                                ;
                                return _t1278;
                            } else {
                                Bool _t1301; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_U32()); _t1301 = *_hp; free(_hp); }
                                (void)_t1301;
                                if (_t1301) {
                                    Str *_t1279 = Str_lit("U32", 3ULL);
                                    (void)_t1279;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw1272, &(Bool){1});
                                    ;
                                    return _t1279;
                                } else {
                                    Bool _t1300; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_U64()); _t1300 = *_hp; free(_hp); }
                                    (void)_t1300;
                                    if (_t1300) {
                                        Str *_t1280 = Str_lit("U64", 3ULL);
                                        (void)_t1280;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw1272, &(Bool){1});
                                        ;
                                        return _t1280;
                                    } else {
                                        Bool _t1299; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_F32()); _t1299 = *_hp; free(_hp); }
                                        (void)_t1299;
                                        if (_t1299) {
                                            Str *_t1281 = Str_lit("F32", 3ULL);
                                            (void)_t1281;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw1272, &(Bool){1});
                                            ;
                                            return _t1281;
                                        } else {
                                            Bool _t1298; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_Bool()); _t1298 = *_hp; free(_hp); }
                                            (void)_t1298;
                                            if (_t1298) {
                                                Str *_t1282 = Str_lit("Bool", 4ULL);
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
                                                TilType_delete(_sw1272, &(Bool){1});
                                                ;
                                                return _t1282;
                                            } else {
                                                Bool _t1297; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_Struct()); _t1297 = *_hp; free(_hp); }
                                                (void)_t1297;
                                                if (_t1297) {
                                                    Str *_t1283 = Str_lit("Struct", 6ULL);
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
                                                    TilType_delete(_sw1272, &(Bool){1});
                                                    ;
                                                    return _t1283;
                                                } else {
                                                    Bool _t1296; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_StructDef()); _t1296 = *_hp; free(_hp); }
                                                    (void)_t1296;
                                                    if (_t1296) {
                                                        Str *_t1284 = Str_lit("StructDef", 9ULL);
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
                                                        TilType_delete(_sw1272, &(Bool){1});
                                                        ;
                                                        return _t1284;
                                                    } else {
                                                        Bool _t1295; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_Enum()); _t1295 = *_hp; free(_hp); }
                                                        (void)_t1295;
                                                        if (_t1295) {
                                                            Str *_t1285 = Str_lit("Enum", 4ULL);
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
                                                            TilType_delete(_sw1272, &(Bool){1});
                                                            ;
                                                            return _t1285;
                                                        } else {
                                                            Bool _t1294; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_EnumDef()); _t1294 = *_hp; free(_hp); }
                                                            (void)_t1294;
                                                            if (_t1294) {
                                                                Str *_t1286 = Str_lit("EnumDef", 7ULL);
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
                                                                TilType_delete(_sw1272, &(Bool){1});
                                                                ;
                                                                return _t1286;
                                                            } else {
                                                                Bool _t1293; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_FuncDef()); _t1293 = *_hp; free(_hp); }
                                                                (void)_t1293;
                                                                if (_t1293) {
                                                                    Str *_t1287 = Str_lit("FunctionDef", 11ULL);
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
                                                                    TilType_delete(_sw1272, &(Bool){1});
                                                                    ;
                                                                    return _t1287;
                                                                } else {
                                                                    Bool _t1292; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_FuncPtr()); _t1292 = *_hp; free(_hp); }
                                                                    (void)_t1292;
                                                                    if (_t1292) {
                                                                        Str *_t1288 = Str_lit("Fn", 2ULL);
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
                                                                        TilType_delete(_sw1272, &(Bool){1});
                                                                        ;
                                                                        return _t1288;
                                                                    } else {
                                                                        Bool _t1291; { Bool *_hp = (Bool *)TilType_eq(_sw1272, TilType_Dynamic()); _t1291 = *_hp; free(_hp); }
                                                                        (void)_t1291;
                                                                        if (_t1291) {
                                                                            Str *_t1289 = Str_lit("Dynamic", 7ULL);
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
                                                                            TilType_delete(_sw1272, &(Bool){1});
                                                                            ;
                                                                            return _t1289;
                                                                        } else {
                                                                            Str *_t1290 = Str_lit("?", 1ULL);
                                                                            (void)_t1290;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw1272, &(Bool){1});
                                                                            ;
                                                                            return _t1290;
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
        TilType_delete(_sw1272, &(Bool){1});
        ;
    }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t1309 = Bool_clone(&self->is_mut);
    (void)_t1309;
    Bool _t1310 = Bool_clone(&self->is_namespace);
    (void)_t1310;
    Bool _t1311 = Bool_clone(&self->is_ref);
    (void)_t1311;
    Bool _t1312 = Bool_clone(&self->is_own);
    (void)_t1312;
    I32 _t1313 = I32_clone(&self->field_offset);
    (void)_t1313;
    I32 _t1314 = I32_clone(&self->field_size);
    (void)_t1314;
    Declaration *_t1315 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t1315->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t1315->explicit_type = *_ca; free(_ca); }
    _t1315->is_mut = _t1309;
    _t1315->is_namespace = _t1310;
    _t1315->is_ref = _t1311;
    _t1315->is_own = _t1312;
    _t1315->field_offset = _t1313;
    _t1315->field_size = _t1314;
    _t1315->field_struct_def = self->field_struct_def;
    _t1315->fn_sig = self->fn_sig;
    (void)_t1315;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t1315;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1316 = 0;
    (void)_t1316;
    Str_delete(&self->name, &(Bool){_t1316});
    ;
    Bool _t1317 = 0;
    (void)_t1317;
    Str_delete(&self->explicit_type, &(Bool){_t1317});
    ;
    Bool _t1318 = 0;
    (void)_t1318;
    Bool_delete(&self->is_mut, &(Bool){_t1318});
    ;
    Bool _t1319 = 0;
    (void)_t1319;
    Bool_delete(&self->is_namespace, &(Bool){_t1319});
    ;
    Bool _t1320 = 0;
    (void)_t1320;
    Bool_delete(&self->is_ref, &(Bool){_t1320});
    ;
    Bool _t1321 = 0;
    (void)_t1321;
    Bool_delete(&self->is_own, &(Bool){_t1321});
    ;
    Bool _t1322 = 0;
    (void)_t1322;
    I32_delete(&self->field_offset, &(Bool){_t1322});
    ;
    Bool _t1323 = 0;
    (void)_t1323;
    I32_delete(&self->field_size, &(Bool){_t1323});
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
    Bool _t1357 = Bool_clone(&self->is_mut);
    (void)_t1357;
    Bool _t1358 = Bool_clone(&self->is_own);
    (void)_t1358;
    Bool _t1359 = Bool_clone(&self->is_shallow);
    (void)_t1359;
    Param *_t1360 = malloc(sizeof(Param));
    { Str *_ca = Str_clone(&self->name); _t1360->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->ptype); _t1360->ptype = *_ca; free(_ca); }
    _t1360->is_mut = _t1357;
    _t1360->is_own = _t1358;
    _t1360->is_shallow = _t1359;
    (void)_t1360;
    ;
    ;
    ;
    return _t1360;
}

void Param_delete(Param * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1361 = 0;
    (void)_t1361;
    Str_delete(&self->name, &(Bool){_t1361});
    ;
    Bool _t1362 = 0;
    (void)_t1362;
    Str_delete(&self->ptype, &(Bool){_t1362});
    ;
    Bool _t1363 = 0;
    (void)_t1363;
    Bool_delete(&self->is_mut, &(Bool){_t1363});
    ;
    Bool _t1364 = 0;
    (void)_t1364;
    Bool_delete(&self->is_own, &(Bool){_t1364});
    ;
    Bool _t1365 = 0;
    (void)_t1365;
    Bool_delete(&self->is_shallow, &(Bool){_t1365});
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
    U32 _t1368 = U32_clone(&self->nparam);
    (void)_t1368;
    I32 _t1369 = I32_clone(&self->variadic_index);
    (void)_t1369;
    I32 _t1370 = I32_clone(&self->kwargs_index);
    (void)_t1370;
    Bool _t1371 = Bool_clone(&self->return_is_ref);
    (void)_t1371;
    Bool _t1372 = Bool_clone(&self->return_is_shallow);
    (void)_t1372;
    FunctionDef *_t1373 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); _t1373->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); _t1373->params = *_ca; free(_ca); }
    _t1373->nparam = _t1368;
    { Map *_ca = Map_clone(&self->param_defaults); _t1373->param_defaults = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); _t1373->return_type = *_ca; free(_ca); }
    _t1373->variadic_index = _t1369;
    _t1373->kwargs_index = _t1370;
    _t1373->return_is_ref = _t1371;
    _t1373->return_is_shallow = _t1372;
    (void)_t1373;
    ;
    ;
    ;
    ;
    ;
    return _t1373;
}

void FunctionDef_delete(FunctionDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t1374 = 0;
    (void)_t1374;
    FuncType_delete(&self->func_type, &(Bool){_t1374});
    ;
    Bool _t1375 = 0;
    (void)_t1375;
    Vec_delete(&self->params, &(Bool){_t1375});
    ;
    Bool _t1376 = 0;
    (void)_t1376;
    U32_delete(&self->nparam, &(Bool){_t1376});
    ;
    Bool _t1377 = 0;
    (void)_t1377;
    Map_delete(&self->param_defaults, &(Bool){_t1377});
    ;
    Bool _t1378 = 0;
    (void)_t1378;
    Str_delete(&self->return_type, &(Bool){_t1378});
    ;
    Bool _t1379 = 0;
    (void)_t1379;
    I32_delete(&self->variadic_index, &(Bool){_t1379});
    ;
    Bool _t1380 = 0;
    (void)_t1380;
    I32_delete(&self->kwargs_index, &(Bool){_t1380});
    ;
    Bool _t1381 = 0;
    (void)_t1381;
    Bool_delete(&self->return_is_ref, &(Bool){_t1381});
    ;
    Bool _t1382 = 0;
    (void)_t1382;
    Bool_delete(&self->return_is_shallow, &(Bool){_t1382});
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
    Bool _t1761 = 0;
    (void)_t1761;
    ExprData_delete(&self->data, &(Bool){_t1761});
    ;
    Bool _t1762 = 0;
    (void)_t1762;
    TilType_delete(&self->til_type, &(Bool){_t1762});
    ;
    Bool _t1763 = 0;
    (void)_t1763;
    Str_delete(&self->struct_name, &(Bool){_t1763});
    ;
    Bool _t1764 = 0;
    (void)_t1764;
    Bool_delete(&self->is_own_arg, &(Bool){_t1764});
    ;
    Bool _t1765 = 0;
    (void)_t1765;
    Bool_delete(&self->is_splat, &(Bool){_t1765});
    ;
    Bool _t1766 = 0;
    (void)_t1766;
    Bool_delete(&self->is_own_field, &(Bool){_t1766});
    ;
    Bool _t1767 = 0;
    (void)_t1767;
    Bool_delete(&self->is_ref_field, &(Bool){_t1767});
    ;
    Bool _t1768 = 0;
    (void)_t1768;
    Bool_delete(&self->is_ns_field, &(Bool){_t1768});
    ;
    Bool _t1769 = 0;
    (void)_t1769;
    Bool_delete(&self->is_ext, &(Bool){_t1769});
    ;
    Bool _t1770 = 0;
    (void)_t1770;
    Bool_delete(&self->is_core, &(Bool){_t1770});
    ;
    Bool _t1771 = 0;
    (void)_t1771;
    Bool_delete(&self->save_old_delete, &(Bool){_t1771});
    ;
    Bool _t1772 = 0;
    (void)_t1772;
    I32_delete(&self->total_struct_size, &(Bool){_t1772});
    ;
    Bool _t1773 = 0;
    (void)_t1773;
    I32_delete(&self->variadic_index, &(Bool){_t1773});
    ;
    Bool _t1774 = 0;
    (void)_t1774;
    U32_delete(&self->variadic_count, &(Bool){_t1774});
    ;
    Bool _t1775 = 0;
    (void)_t1775;
    I32_delete(&self->kwargs_index, &(Bool){_t1775});
    ;
    Bool _t1776 = 0;
    (void)_t1776;
    U32_delete(&self->kwargs_count, &(Bool){_t1776});
    ;
    Bool _t1777 = 0;
    (void)_t1777;
    Vec_delete(&self->children, &(Bool){_t1777});
    ;
    Bool _t1778 = 0;
    (void)_t1778;
    U32_delete(&self->line, &(Bool){_t1778});
    ;
    Bool _t1779 = 0;
    (void)_t1779;
    U32_delete(&self->col, &(Bool){_t1779});
    ;
    Bool _t1780 = 0;
    (void)_t1780;
    Str_delete(&self->path, &(Bool){_t1780});
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
        ExprData *_sw1782 = ExprData_clone(data);
        (void)_sw1782;
        Bool _t1833; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Body()); _t1833 = *_hp; free(_hp); }
        (void)_t1833;
        if (_t1833) {
            Str *_t1783 = Str_lit("body", 4ULL);
            (void)_t1783;
            ExprData_delete(_sw1782, &(Bool){1});
            ;
            return _t1783;
        } else {
            Bool _t1832; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1782); _t1832 = *_hp; free(_hp); }
            (void)_t1832;
            if (_t1832) {
                Str *_t1784 = Str_lit("str", 3ULL);
                (void)_t1784;
                ;
                ExprData_delete(_sw1782, &(Bool){1});
                ;
                return _t1784;
            } else {
                Bool _t1831; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1782); _t1831 = *_hp; free(_hp); }
                (void)_t1831;
                if (_t1831) {
                    Str *_t1785 = Str_lit("num", 3ULL);
                    (void)_t1785;
                    ;
                    ;
                    ExprData_delete(_sw1782, &(Bool){1});
                    ;
                    return _t1785;
                } else {
                    Bool _t1830; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1782); _t1830 = *_hp; free(_hp); }
                    (void)_t1830;
                    if (_t1830) {
                        Str *_t1786 = Str_lit("bool", 4ULL);
                        (void)_t1786;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw1782, &(Bool){1});
                        ;
                        return _t1786;
                    } else {
                        Bool _t1829; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_LiteralNull()); _t1829 = *_hp; free(_hp); }
                        (void)_t1829;
                        if (_t1829) {
                            Str *_t1787 = Str_lit("null", 4ULL);
                            (void)_t1787;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw1782, &(Bool){1});
                            ;
                            return _t1787;
                        } else {
                            Bool _t1828; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1782); _t1828 = *_hp; free(_hp); }
                            (void)_t1828;
                            if (_t1828) {
                                Str *_t1788 = Str_lit("ident", 5ULL);
                                (void)_t1788;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw1782, &(Bool){1});
                                ;
                                return _t1788;
                            } else {
                                Bool _t1827; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1782); _t1827 = *_hp; free(_hp); }
                                (void)_t1827;
                                if (_t1827) {
                                    Str *_t1789 = Str_lit("decl", 4ULL);
                                    (void)_t1789;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw1782, &(Bool){1});
                                    ;
                                    return _t1789;
                                } else {
                                    Bool _t1826; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1782); _t1826 = *_hp; free(_hp); }
                                    (void)_t1826;
                                    if (_t1826) {
                                        Str *_t1790 = Str_lit("assign", 6ULL);
                                        (void)_t1790;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw1782, &(Bool){1});
                                        ;
                                        return _t1790;
                                    } else {
                                        Bool _t1825; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_FCall()); _t1825 = *_hp; free(_hp); }
                                        (void)_t1825;
                                        if (_t1825) {
                                            Str *_t1791 = Str_lit("fcall", 5ULL);
                                            (void)_t1791;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw1782, &(Bool){1});
                                            ;
                                            return _t1791;
                                        } else {
                                            Bool _t1824; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1782); _t1824 = *_hp; free(_hp); }
                                            (void)_t1824;
                                            if (_t1824) {
                                                Str *_t1792 = Str_lit("func_def", 8ULL);
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
                                                ExprData_delete(_sw1782, &(Bool){1});
                                                ;
                                                return _t1792;
                                            } else {
                                                Bool _t1823; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_StructDef()); _t1823 = *_hp; free(_hp); }
                                                (void)_t1823;
                                                if (_t1823) {
                                                    Str *_t1793 = Str_lit("struct_def", 10ULL);
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
                                                    ExprData_delete(_sw1782, &(Bool){1});
                                                    ;
                                                    return _t1793;
                                                } else {
                                                    Bool _t1822; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_EnumDef()); _t1822 = *_hp; free(_hp); }
                                                    (void)_t1822;
                                                    if (_t1822) {
                                                        Str *_t1794 = Str_lit("enum_def", 8ULL);
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
                                                        ExprData_delete(_sw1782, &(Bool){1});
                                                        ;
                                                        return _t1794;
                                                    } else {
                                                        Bool _t1821; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw1782); _t1821 = *_hp; free(_hp); }
                                                        (void)_t1821;
                                                        if (_t1821) {
                                                            Str *_t1795 = Str_lit("field_access", 12ULL);
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
                                                            ExprData_delete(_sw1782, &(Bool){1});
                                                            ;
                                                            return _t1795;
                                                        } else {
                                                            Bool _t1820; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw1782); _t1820 = *_hp; free(_hp); }
                                                            (void)_t1820;
                                                            if (_t1820) {
                                                                Str *_t1796 = Str_lit("field_assign", 12ULL);
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
                                                                ExprData_delete(_sw1782, &(Bool){1});
                                                                ;
                                                                return _t1796;
                                                            } else {
                                                                Bool _t1819; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Return()); _t1819 = *_hp; free(_hp); }
                                                                (void)_t1819;
                                                                if (_t1819) {
                                                                    Str *_t1797 = Str_lit("return", 6ULL);
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
                                                                    ExprData_delete(_sw1782, &(Bool){1});
                                                                    ;
                                                                    return _t1797;
                                                                } else {
                                                                    Bool _t1818; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_If()); _t1818 = *_hp; free(_hp); }
                                                                    (void)_t1818;
                                                                    if (_t1818) {
                                                                        Str *_t1798 = Str_lit("if", 2ULL);
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
                                                                        ExprData_delete(_sw1782, &(Bool){1});
                                                                        ;
                                                                        return _t1798;
                                                                    } else {
                                                                        Bool _t1817; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_While()); _t1817 = *_hp; free(_hp); }
                                                                        (void)_t1817;
                                                                        if (_t1817) {
                                                                            Str *_t1799 = Str_lit("while", 5ULL);
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
                                                                            ExprData_delete(_sw1782, &(Bool){1});
                                                                            ;
                                                                            return _t1799;
                                                                        } else {
                                                                            Bool _t1816; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1782); _t1816 = *_hp; free(_hp); }
                                                                            (void)_t1816;
                                                                            if (_t1816) {
                                                                                Str *_t1800 = Str_lit("for_in", 6ULL);
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
                                                                                ExprData_delete(_sw1782, &(Bool){1});
                                                                                ;
                                                                                return _t1800;
                                                                            } else {
                                                                                Bool _t1815; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1782); _t1815 = *_hp; free(_hp); }
                                                                                (void)_t1815;
                                                                                if (_t1815) {
                                                                                    Str *_t1801 = Str_lit("named_arg", 9ULL);
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
                                                                                    ExprData_delete(_sw1782, &(Bool){1});
                                                                                    ;
                                                                                    return _t1801;
                                                                                } else {
                                                                                    Bool _t1814; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Break()); _t1814 = *_hp; free(_hp); }
                                                                                    (void)_t1814;
                                                                                    if (_t1814) {
                                                                                        Str *_t1802 = Str_lit("break", 5ULL);
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
                                                                                        ExprData_delete(_sw1782, &(Bool){1});
                                                                                        ;
                                                                                        return _t1802;
                                                                                    } else {
                                                                                        Bool _t1813; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Continue()); _t1813 = *_hp; free(_hp); }
                                                                                        (void)_t1813;
                                                                                        if (_t1813) {
                                                                                            Str *_t1803 = Str_lit("continue", 8ULL);
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
                                                                                            ExprData_delete(_sw1782, &(Bool){1});
                                                                                            ;
                                                                                            return _t1803;
                                                                                        } else {
                                                                                            Bool _t1812; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_MapLit()); _t1812 = *_hp; free(_hp); }
                                                                                            (void)_t1812;
                                                                                            if (_t1812) {
                                                                                                Str *_t1804 = Str_lit("map_lit", 7ULL);
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
                                                                                                ExprData_delete(_sw1782, &(Bool){1});
                                                                                                ;
                                                                                                return _t1804;
                                                                                            } else {
                                                                                                Bool _t1811; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_SetLit()); _t1811 = *_hp; free(_hp); }
                                                                                                (void)_t1811;
                                                                                                if (_t1811) {
                                                                                                    Str *_t1805 = Str_lit("set_lit", 7ULL);
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
                                                                                                    ExprData_delete(_sw1782, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1805;
                                                                                                } else {
                                                                                                    Bool _t1810; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Switch()); _t1810 = *_hp; free(_hp); }
                                                                                                    (void)_t1810;
                                                                                                    if (_t1810) {
                                                                                                        Str *_t1806 = Str_lit("switch", 6ULL);
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
                                                                                                        ExprData_delete(_sw1782, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1806;
                                                                                                    } else {
                                                                                                        Bool _t1809; { Bool *_hp = (Bool *)ExprData_eq(_sw1782, ExprData_Case()); _t1809 = *_hp; free(_hp); }
                                                                                                        (void)_t1809;
                                                                                                        if (_t1809) {
                                                                                                            Str *_t1807 = Str_lit("case", 4ULL);
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
                                                                                                            ExprData_delete(_sw1782, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1807;
                                                                                                        } else {
                                                                                                            Str *_t1808 = Str_lit("?", 1ULL);
                                                                                                            (void)_t1808;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw1782, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1808;
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
        ExprData_delete(_sw1782, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw1834 = FuncType_clone(ft);
        (void)_sw1834;
        Bool _t1847; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_Func()); _t1847 = *_hp; free(_hp); }
        (void)_t1847;
        if (_t1847) {
            Str *_t1835 = Str_lit("func", 4ULL);
            (void)_t1835;
            FuncType_delete(_sw1834, &(Bool){1});
            ;
            return _t1835;
        } else {
            Bool _t1846; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_Proc()); _t1846 = *_hp; free(_hp); }
            (void)_t1846;
            if (_t1846) {
                Str *_t1836 = Str_lit("proc", 4ULL);
                (void)_t1836;
                ;
                FuncType_delete(_sw1834, &(Bool){1});
                ;
                return _t1836;
            } else {
                Bool _t1845; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_Test()); _t1845 = *_hp; free(_hp); }
                (void)_t1845;
                if (_t1845) {
                    Str *_t1837 = Str_lit("test", 4ULL);
                    (void)_t1837;
                    ;
                    ;
                    FuncType_delete(_sw1834, &(Bool){1});
                    ;
                    return _t1837;
                } else {
                    Bool _t1844; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_Macro()); _t1844 = *_hp; free(_hp); }
                    (void)_t1844;
                    if (_t1844) {
                        Str *_t1838 = Str_lit("macro", 5ULL);
                        (void)_t1838;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw1834, &(Bool){1});
                        ;
                        return _t1838;
                    } else {
                        Bool _t1843; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_ExtFunc()); _t1843 = *_hp; free(_hp); }
                        (void)_t1843;
                        if (_t1843) {
                            Str *_t1839 = Str_lit("ext_func", 8ULL);
                            (void)_t1839;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw1834, &(Bool){1});
                            ;
                            return _t1839;
                        } else {
                            Bool _t1842; { Bool *_hp = (Bool *)FuncType_eq(_sw1834, FuncType_ExtProc()); _t1842 = *_hp; free(_hp); }
                            (void)_t1842;
                            if (_t1842) {
                                Str *_t1840 = Str_lit("ext_proc", 8ULL);
                                (void)_t1840;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1834, &(Bool){1});
                                ;
                                return _t1840;
                            } else {
                                Str *_t1841 = Str_lit("?", 1ULL);
                                (void)_t1841;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw1834, &(Bool){1});
                                ;
                                return _t1841;
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
        FuncType_delete(_sw1834, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        I64 _t1858 = U32_to_i64(indent);
        (void)_t1858;
        U64 _t1859 = 0;
        (void)_t1859;
        U64 _t1860 = I64_to_u64(_t1858);
        (void)_t1860;
        ;
        Range *_fc1848 = Range_new(_t1859, _t1860);
        (void)_fc1848;
        ;
        ;
        U64 _fi1848 = 0;
        (void)_fi1848;
        while (1) {
            U64 _t1850; { U64 *_hp = (U64 *)Range_len(_fc1848); _t1850 = *_hp; free(_hp); }
            (void)_t1850;
            Bool _wcond1849; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1848}, &(U64){_t1850}); _wcond1849 = *_hp; free(_hp); }
            (void)_wcond1849;
            ;
            if (_wcond1849) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc1848, _fi1848); i = *_hp; free(_hp); }
            (void)i;
            ;
            U64 _t1851 = 1;
            (void)_t1851;
            U64 _t1852 = U64_add(_fi1848, _t1851);
            (void)_t1852;
            ;
            _fi1848 = _t1852;
            ;
            Str *_t1853 = Str_lit("Str", 3ULL);
            (void)_t1853;
            U64 _t1854; { U64 *_hp = (U64 *)Str_size(); _t1854 = *_hp; free(_hp); }
            (void)_t1854;
            U64 _t1855 = 1;
            (void)_t1855;
            Array *_va37 = Array_new(_t1853, &(U64){_t1854}, &(U64){_t1855});
            (void)_va37;
            Str_delete(_t1853, &(Bool){1});
            ;
            ;
            U64 _t1856 = 0;
            (void)_t1856;
            Str *_t1857 = Str_lit("  ", 2ULL);
            (void)_t1857;
            Array_set(_va37, &(U64){_t1856}, _t1857);
            ;
            print(_va37);
        }
        Range_delete(_fc1848, &(Bool){1});
        ;
    }
    Str *_t1985 = Str_lit("Str", 3ULL);
    (void)_t1985;
    U64 _t1986; { U64 *_hp = (U64 *)Str_size(); _t1986 = *_hp; free(_hp); }
    (void)_t1986;
    U64 _t1987 = 2;
    (void)_t1987;
    Array *_va51 = Array_new(_t1985, &(U64){_t1986}, &(U64){_t1987});
    (void)_va51;
    Str_delete(_t1985, &(Bool){1});
    ;
    ;
    U64 _t1988 = 0;
    (void)_t1988;
    Str *_t1989 = Str_lit("(", 1ULL);
    (void)_t1989;
    Array_set(_va51, &(U64){_t1988}, _t1989);
    ;
    U64 _t1990 = 1;
    (void)_t1990;
    Str *_t1991 = node_name(&e->data);
    (void)_t1991;
    Array_set(_va51, &(U64){_t1990}, _t1991);
    ;
    print(_va51);
    Bool _t1992; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t1992 = *_hp; free(_hp); }
    (void)_t1992;
    Bool _t1993 = Bool_not(_t1992);
    (void)_t1993;
    ;
    if (_t1993) {
        Str *_t1861 = Str_lit("Str", 3ULL);
        (void)_t1861;
        U64 _t1862; { U64 *_hp = (U64 *)Str_size(); _t1862 = *_hp; free(_hp); }
        (void)_t1862;
        U64 _t1863 = 2;
        (void)_t1863;
        Array *_va38 = Array_new(_t1861, &(U64){_t1862}, &(U64){_t1863});
        (void)_va38;
        Str_delete(_t1861, &(Bool){1});
        ;
        ;
        U64 _t1864 = 0;
        (void)_t1864;
        Str *_t1865 = Str_lit(":", 1ULL);
        (void)_t1865;
        Array_set(_va38, &(U64){_t1864}, _t1865);
        ;
        U64 _t1866 = 1;
        (void)_t1866;
        Str *_t1867 = til_type_name_c(&e->til_type);
        (void)_t1867;
        Array_set(_va38, &(U64){_t1866}, _t1867);
        ;
        print(_va38);
    }
    ;
    {
        ExprData *_sw1868 = ExprData_clone(&e->data);
        (void)_sw1868;
        Bool _t1955; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw1868); _t1955 = *_hp; free(_hp); }
        (void)_t1955;
        if (_t1955) {
            Str *s = ExprData_get_Ident(_sw1868);
            (void)s;
            Str *_t1869 = Str_lit("Str", 3ULL);
            (void)_t1869;
            U64 _t1870; { U64 *_hp = (U64 *)Str_size(); _t1870 = *_hp; free(_hp); }
            (void)_t1870;
            U64 _t1871 = 3;
            (void)_t1871;
            Array *_va39 = Array_new(_t1869, &(U64){_t1870}, &(U64){_t1871});
            (void)_va39;
            Str_delete(_t1869, &(Bool){1});
            ;
            ;
            U64 _t1872 = 0;
            (void)_t1872;
            Str *_t1873 = Str_lit(" \"", 3ULL);
            (void)_t1873;
            Array_set(_va39, &(U64){_t1872}, _t1873);
            ;
            U64 _t1874 = 1;
            (void)_t1874;
            Str *_t1875 = Str_clone(s);
            (void)_t1875;
            Str_delete(s, &(Bool){1});
            Array_set(_va39, &(U64){_t1874}, _t1875);
            ;
            U64 _t1876 = 2;
            (void)_t1876;
            Str *_t1877 = Str_lit("\"", 2ULL);
            (void)_t1877;
            Array_set(_va39, &(U64){_t1876}, _t1877);
            ;
            print(_va39);
        } else {
            Bool _t1954; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw1868); _t1954 = *_hp; free(_hp); }
            (void)_t1954;
            if (_t1954) {
                Str *s = ExprData_get_LiteralStr(_sw1868);
                (void)s;
                Str *_t1878 = Str_lit("Str", 3ULL);
                (void)_t1878;
                U64 _t1879; { U64 *_hp = (U64 *)Str_size(); _t1879 = *_hp; free(_hp); }
                (void)_t1879;
                U64 _t1880 = 3;
                (void)_t1880;
                Array *_va40 = Array_new(_t1878, &(U64){_t1879}, &(U64){_t1880});
                (void)_va40;
                Str_delete(_t1878, &(Bool){1});
                ;
                ;
                U64 _t1881 = 0;
                (void)_t1881;
                Str *_t1882 = Str_lit(" \"", 3ULL);
                (void)_t1882;
                Array_set(_va40, &(U64){_t1881}, _t1882);
                ;
                U64 _t1883 = 1;
                (void)_t1883;
                Str *_t1884 = Str_clone(s);
                (void)_t1884;
                Str_delete(s, &(Bool){1});
                Array_set(_va40, &(U64){_t1883}, _t1884);
                ;
                U64 _t1885 = 2;
                (void)_t1885;
                Str *_t1886 = Str_lit("\"", 2ULL);
                (void)_t1886;
                Array_set(_va40, &(U64){_t1885}, _t1886);
                ;
                print(_va40);
            } else {
                Bool _t1953; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw1868); _t1953 = *_hp; free(_hp); }
                (void)_t1953;
                if (_t1953) {
                    Str *s = ExprData_get_LiteralNum(_sw1868);
                    (void)s;
                    Str *_t1887 = Str_lit("Str", 3ULL);
                    (void)_t1887;
                    U64 _t1888; { U64 *_hp = (U64 *)Str_size(); _t1888 = *_hp; free(_hp); }
                    (void)_t1888;
                    U64 _t1889 = 3;
                    (void)_t1889;
                    Array *_va41 = Array_new(_t1887, &(U64){_t1888}, &(U64){_t1889});
                    (void)_va41;
                    Str_delete(_t1887, &(Bool){1});
                    ;
                    ;
                    U64 _t1890 = 0;
                    (void)_t1890;
                    Str *_t1891 = Str_lit(" \"", 3ULL);
                    (void)_t1891;
                    Array_set(_va41, &(U64){_t1890}, _t1891);
                    ;
                    U64 _t1892 = 1;
                    (void)_t1892;
                    Str *_t1893 = Str_clone(s);
                    (void)_t1893;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va41, &(U64){_t1892}, _t1893);
                    ;
                    U64 _t1894 = 2;
                    (void)_t1894;
                    Str *_t1895 = Str_lit("\"", 2ULL);
                    (void)_t1895;
                    Array_set(_va41, &(U64){_t1894}, _t1895);
                    ;
                    print(_va41);
                } else {
                    Bool _t1952; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw1868); _t1952 = *_hp; free(_hp); }
                    (void)_t1952;
                    if (_t1952) {
                        Str *s = ExprData_get_LiteralBool(_sw1868);
                        (void)s;
                        Str *_t1896 = Str_lit("Str", 3ULL);
                        (void)_t1896;
                        U64 _t1897; { U64 *_hp = (U64 *)Str_size(); _t1897 = *_hp; free(_hp); }
                        (void)_t1897;
                        U64 _t1898 = 3;
                        (void)_t1898;
                        Array *_va42 = Array_new(_t1896, &(U64){_t1897}, &(U64){_t1898});
                        (void)_va42;
                        Str_delete(_t1896, &(Bool){1});
                        ;
                        ;
                        U64 _t1899 = 0;
                        (void)_t1899;
                        Str *_t1900 = Str_lit(" \"", 3ULL);
                        (void)_t1900;
                        Array_set(_va42, &(U64){_t1899}, _t1900);
                        ;
                        U64 _t1901 = 1;
                        (void)_t1901;
                        Str *_t1902 = Str_clone(s);
                        (void)_t1902;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va42, &(U64){_t1901}, _t1902);
                        ;
                        U64 _t1903 = 2;
                        (void)_t1903;
                        Str *_t1904 = Str_lit("\"", 2ULL);
                        (void)_t1904;
                        Array_set(_va42, &(U64){_t1903}, _t1904);
                        ;
                        print(_va42);
                    } else {
                        Bool _t1951; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw1868); _t1951 = *_hp; free(_hp); }
                        (void)_t1951;
                        if (_t1951) {
                            Str *s = ExprData_get_ForIn(_sw1868);
                            (void)s;
                            Str *_t1905 = Str_lit("Str", 3ULL);
                            (void)_t1905;
                            U64 _t1906; { U64 *_hp = (U64 *)Str_size(); _t1906 = *_hp; free(_hp); }
                            (void)_t1906;
                            U64 _t1907 = 3;
                            (void)_t1907;
                            Array *_va43 = Array_new(_t1905, &(U64){_t1906}, &(U64){_t1907});
                            (void)_va43;
                            Str_delete(_t1905, &(Bool){1});
                            ;
                            ;
                            U64 _t1908 = 0;
                            (void)_t1908;
                            Str *_t1909 = Str_lit(" \"", 3ULL);
                            (void)_t1909;
                            Array_set(_va43, &(U64){_t1908}, _t1909);
                            ;
                            U64 _t1910 = 1;
                            (void)_t1910;
                            Str *_t1911 = Str_clone(s);
                            (void)_t1911;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va43, &(U64){_t1910}, _t1911);
                            ;
                            U64 _t1912 = 2;
                            (void)_t1912;
                            Str *_t1913 = Str_lit("\"", 2ULL);
                            (void)_t1913;
                            Array_set(_va43, &(U64){_t1912}, _t1913);
                            ;
                            print(_va43);
                        } else {
                            Bool _t1950; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw1868); _t1950 = *_hp; free(_hp); }
                            (void)_t1950;
                            if (_t1950) {
                                Declaration *decl = ExprData_get_Decl(_sw1868);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t1914 = Str_lit("Str", 3ULL);
                                    (void)_t1914;
                                    U64 _t1915; { U64 *_hp = (U64 *)Str_size(); _t1915 = *_hp; free(_hp); }
                                    (void)_t1915;
                                    U64 _t1916 = 1;
                                    (void)_t1916;
                                    Array *_va44 = Array_new(_t1914, &(U64){_t1915}, &(U64){_t1916});
                                    (void)_va44;
                                    Str_delete(_t1914, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1917 = 0;
                                    (void)_t1917;
                                    Str *_t1918 = Str_lit(" mut", 4ULL);
                                    (void)_t1918;
                                    Array_set(_va44, &(U64){_t1917}, _t1918);
                                    ;
                                    print(_va44);
                                }
                                Str *_t1919 = Str_lit("Str", 3ULL);
                                (void)_t1919;
                                U64 _t1920; { U64 *_hp = (U64 *)Str_size(); _t1920 = *_hp; free(_hp); }
                                (void)_t1920;
                                U64 _t1921 = 2;
                                (void)_t1921;
                                Array *_va45 = Array_new(_t1919, &(U64){_t1920}, &(U64){_t1921});
                                (void)_va45;
                                Str_delete(_t1919, &(Bool){1});
                                ;
                                ;
                                U64 _t1922 = 0;
                                (void)_t1922;
                                Str *_t1923 = Str_lit(" ", 1ULL);
                                (void)_t1923;
                                Array_set(_va45, &(U64){_t1922}, _t1923);
                                ;
                                U64 _t1924 = 1;
                                (void)_t1924;
                                Str *_t1925 = Str_clone(&decl->name);
                                (void)_t1925;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va45, &(U64){_t1924}, _t1925);
                                ;
                                print(_va45);
                            } else {
                                Bool _t1949; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw1868); _t1949 = *_hp; free(_hp); }
                                (void)_t1949;
                                if (_t1949) {
                                    Str *s = ExprData_get_Assign(_sw1868);
                                    (void)s;
                                    Str *_t1926 = Str_lit("Str", 3ULL);
                                    (void)_t1926;
                                    U64 _t1927; { U64 *_hp = (U64 *)Str_size(); _t1927 = *_hp; free(_hp); }
                                    (void)_t1927;
                                    U64 _t1928 = 2;
                                    (void)_t1928;
                                    Array *_va46 = Array_new(_t1926, &(U64){_t1927}, &(U64){_t1928});
                                    (void)_va46;
                                    Str_delete(_t1926, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t1929 = 0;
                                    (void)_t1929;
                                    Str *_t1930 = Str_lit(" ", 1ULL);
                                    (void)_t1930;
                                    Array_set(_va46, &(U64){_t1929}, _t1930);
                                    ;
                                    U64 _t1931 = 1;
                                    (void)_t1931;
                                    Str *_t1932 = Str_clone(s);
                                    (void)_t1932;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va46, &(U64){_t1931}, _t1932);
                                    ;
                                    print(_va46);
                                } else {
                                    Bool _t1948; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw1868); _t1948 = *_hp; free(_hp); }
                                    (void)_t1948;
                                    if (_t1948) {
                                        Str *s = ExprData_get_NamedArg(_sw1868);
                                        (void)s;
                                        Str *_t1933 = Str_lit("Str", 3ULL);
                                        (void)_t1933;
                                        U64 _t1934; { U64 *_hp = (U64 *)Str_size(); _t1934 = *_hp; free(_hp); }
                                        (void)_t1934;
                                        U64 _t1935 = 2;
                                        (void)_t1935;
                                        Array *_va47 = Array_new(_t1933, &(U64){_t1934}, &(U64){_t1935});
                                        (void)_va47;
                                        Str_delete(_t1933, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t1936 = 0;
                                        (void)_t1936;
                                        Str *_t1937 = Str_lit(" ", 1ULL);
                                        (void)_t1937;
                                        Array_set(_va47, &(U64){_t1936}, _t1937);
                                        ;
                                        U64 _t1938 = 1;
                                        (void)_t1938;
                                        Str *_t1939 = Str_clone(s);
                                        (void)_t1939;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va47, &(U64){_t1938}, _t1939);
                                        ;
                                        print(_va47);
                                    } else {
                                        Bool _t1947; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw1868); _t1947 = *_hp; free(_hp); }
                                        (void)_t1947;
                                        if (_t1947) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw1868);
                                            (void)fdef;
                                            Str *_t1940 = Str_lit("Str", 3ULL);
                                            (void)_t1940;
                                            U64 _t1941; { U64 *_hp = (U64 *)Str_size(); _t1941 = *_hp; free(_hp); }
                                            (void)_t1941;
                                            U64 _t1942 = 2;
                                            (void)_t1942;
                                            Array *_va48 = Array_new(_t1940, &(U64){_t1941}, &(U64){_t1942});
                                            (void)_va48;
                                            Str_delete(_t1940, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t1943 = 0;
                                            (void)_t1943;
                                            Str *_t1944 = Str_lit(" ", 1ULL);
                                            (void)_t1944;
                                            Array_set(_va48, &(U64){_t1943}, _t1944);
                                            ;
                                            U64 _t1945 = 1;
                                            (void)_t1945;
                                            Str *_t1946 = func_type_name(&fdef->func_type);
                                            (void)_t1946;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va48, &(U64){_t1945}, _t1946);
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
        ExprData_delete(_sw1868, &(Bool){1});
        ;
    }
    U64 _t1994; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1994 = *_hp; free(_hp); }
    (void)_t1994;
    U64 _t1995 = 0;
    (void)_t1995;
    Bool _t1996; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1994}, &(U64){_t1995}); _t1996 = *_hp; free(_hp); }
    (void)_t1996;
    ;
    ;
    if (_t1996) {
        Str *_t1980 = Str_lit("Str", 3ULL);
        (void)_t1980;
        U64 _t1981; { U64 *_hp = (U64 *)Str_size(); _t1981 = *_hp; free(_hp); }
        (void)_t1981;
        U64 _t1982 = 1;
        (void)_t1982;
        Array *_va50 = Array_new(_t1980, &(U64){_t1981}, &(U64){_t1982});
        (void)_va50;
        Str_delete(_t1980, &(Bool){1});
        ;
        ;
        U64 _t1983 = 0;
        (void)_t1983;
        Str *_t1984 = Str_lit("", 0ULL);
        (void)_t1984;
        Array_set(_va50, &(U64){_t1983}, _t1984);
        ;
        println(_va50);
        {
            U64 _t1965 = 0;
            (void)_t1965;
            U64 _t1966; { U64 *_hp = (U64 *)Vec_len(&e->children); _t1966 = *_hp; free(_hp); }
            (void)_t1966;
            Range *_fc1956 = Range_new(_t1965, _t1966);
            (void)_fc1956;
            ;
            ;
            U64 _fi1956 = 0;
            (void)_fi1956;
            while (1) {
                U64 _t1958; { U64 *_hp = (U64 *)Range_len(_fc1956); _t1958 = *_hp; free(_hp); }
                (void)_t1958;
                Bool _wcond1957; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1956}, &(U64){_t1958}); _wcond1957 = *_hp; free(_hp); }
                (void)_wcond1957;
                ;
                if (_wcond1957) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1956, _fi1956); i = *_hp; free(_hp); }
                (void)i;
                U64 _t1959 = 1;
                (void)_t1959;
                U64 _t1960 = U64_add(_fi1956, _t1959);
                (void)_t1960;
                ;
                _fi1956 = _t1960;
                ;
                I64 *_t1961 = malloc(sizeof(I64)); *_t1961 = U64_to_i64(i);
                (void)_t1961;
                ;
                U32 _t1962 = 1;
                (void)_t1962;
                Expr *_t1963 = Expr_child(e, _t1961);
                (void)_t1963;
                U32 _t1964 = U32_add(indent, _t1962);
                (void)_t1964;
                ;
                ast_print(_t1963, _t1964);
                I64_delete(_t1961, &(Bool){1});
                ;
            }
            Range_delete(_fc1956, &(Bool){1});
            ;
        }
        {
            I64 _t1977 = U32_to_i64(indent);
            (void)_t1977;
            U64 _t1978 = 0;
            (void)_t1978;
            U64 _t1979 = I64_to_u64(_t1977);
            (void)_t1979;
            ;
            Range *_fc1967 = Range_new(_t1978, _t1979);
            (void)_fc1967;
            ;
            ;
            U64 _fi1967 = 0;
            (void)_fi1967;
            while (1) {
                U64 _t1969; { U64 *_hp = (U64 *)Range_len(_fc1967); _t1969 = *_hp; free(_hp); }
                (void)_t1969;
                Bool _wcond1968; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1967}, &(U64){_t1969}); _wcond1968 = *_hp; free(_hp); }
                (void)_wcond1968;
                ;
                if (_wcond1968) {
                } else {
                    ;
                    break;
                }
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_fc1967, _fi1967); i = *_hp; free(_hp); }
                (void)i;
                ;
                U64 _t1970 = 1;
                (void)_t1970;
                U64 _t1971 = U64_add(_fi1967, _t1970);
                (void)_t1971;
                ;
                _fi1967 = _t1971;
                ;
                Str *_t1972 = Str_lit("Str", 3ULL);
                (void)_t1972;
                U64 _t1973; { U64 *_hp = (U64 *)Str_size(); _t1973 = *_hp; free(_hp); }
                (void)_t1973;
                U64 _t1974 = 1;
                (void)_t1974;
                Array *_va49 = Array_new(_t1972, &(U64){_t1973}, &(U64){_t1974});
                (void)_va49;
                Str_delete(_t1972, &(Bool){1});
                ;
                ;
                U64 _t1975 = 0;
                (void)_t1975;
                Str *_t1976 = Str_lit("  ", 2ULL);
                (void)_t1976;
                Array_set(_va49, &(U64){_t1975}, _t1976);
                ;
                print(_va49);
            }
            Range_delete(_fc1967, &(Bool){1});
            ;
        }
    }
    ;
    Str *_t1997 = Str_lit("Str", 3ULL);
    (void)_t1997;
    U64 _t1998; { U64 *_hp = (U64 *)Str_size(); _t1998 = *_hp; free(_hp); }
    (void)_t1998;
    U64 _t1999 = 1;
    (void)_t1999;
    Array *_va52 = Array_new(_t1997, &(U64){_t1998}, &(U64){_t1999});
    (void)_va52;
    Str_delete(_t1997, &(Bool){1});
    ;
    ;
    U64 _t2000 = 0;
    (void)_t2000;
    Str *_t2001 = Str_lit(")", 1ULL);
    (void)_t2001;
    Array_set(_va52, &(U64){_t2000}, _t2001);
    ;
    println(_va52);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2018 = malloc(sizeof(I64));
    *_t2018 = 0;
    (void)_t2018;
    Expr *body = Expr_child(enum_def, _t2018);
    (void)body;
    {
        I64 _t2015; { I64 *_hp = (I64 *)Expr_child_count(body); _t2015 = *_hp; free(_hp); }
        (void)_t2015;
        U64 _t2016 = 0;
        (void)_t2016;
        U64 _t2017 = I64_to_u64(_t2015);
        (void)_t2017;
        ;
        Range *_fc2002 = Range_new(_t2016, _t2017);
        (void)_fc2002;
        ;
        ;
        U64 _fi2002 = 0;
        (void)_fi2002;
        while (1) {
            U64 _t2010; { U64 *_hp = (U64 *)Range_len(_fc2002); _t2010 = *_hp; free(_hp); }
            (void)_t2010;
            Bool _wcond2003; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2002}, &(U64){_t2010}); _wcond2003 = *_hp; free(_hp); }
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
            U64 _t2011 = 1;
            (void)_t2011;
            U64 _t2012 = U64_add(_fi2002, _t2011);
            (void)_t2012;
            ;
            _fi2002 = _t2012;
            ;
            I64 *_t2013 = malloc(sizeof(I64)); *_t2013 = U64_to_i64(i);
            (void)_t2013;
            ;
            Expr *f = Expr_child(body, _t2013);
            (void)f;
            Bool _t2014; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2014 = *_hp; free(_hp); }
            (void)_t2014;
            if (_t2014) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2005; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2005 = *_hp; free(_hp); }
                (void)_t2005;
                U64 _t2006 = 0;
                (void)_t2006;
                Bool _t2007 = Bool_not(decl->is_namespace);
                (void)_t2007;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2008; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2005}, &(U64){_t2006}); _t2008 = *_hp; free(_hp); }
                (void)_t2008;
                ;
                ;
                Bool _t2009 = Bool_and(_t2007, _t2008);
                (void)_t2009;
                ;
                ;
                if (_t2009) {
                    Bool _t2004 = 1;
                    (void)_t2004;
                    ;
                    I64_delete(_t2013, &(Bool){1});
                    ;
                    Range_delete(_fc2002, &(Bool){1});
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2004; return _r; }
                }
                ;
            }
            I64_delete(_t2013, &(Bool){1});
            ;
        }
        Range_delete(_fc2002, &(Bool){1});
        ;
    }
    I64_delete(_t2018, &(Bool){1});
    Bool _t2019 = 0;
    (void)_t2019;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2019; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t2034 = malloc(sizeof(I64));
    *_t2034 = 0;
    (void)_t2034;
    Expr *body = Expr_child(enum_def, _t2034);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        I64 _t2031; { I64 *_hp = (I64 *)Expr_child_count(body); _t2031 = *_hp; free(_hp); }
        (void)_t2031;
        U64 _t2032 = 0;
        (void)_t2032;
        U64 _t2033 = I64_to_u64(_t2031);
        (void)_t2033;
        ;
        Range *_fc2020 = Range_new(_t2032, _t2033);
        (void)_fc2020;
        ;
        ;
        U64 _fi2020 = 0;
        (void)_fi2020;
        while (1) {
            U64 _t2026; { U64 *_hp = (U64 *)Range_len(_fc2020); _t2026 = *_hp; free(_hp); }
            (void)_t2026;
            Bool _wcond2021; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2020}, &(U64){_t2026}); _wcond2021 = *_hp; free(_hp); }
            (void)_wcond2021;
            ;
            if (_wcond2021) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2020, _fi2020); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2027 = 1;
            (void)_t2027;
            U64 _t2028 = U64_add(_fi2020, _t2027);
            (void)_t2028;
            ;
            _fi2020 = _t2028;
            ;
            I64 *_t2029 = malloc(sizeof(I64)); *_t2029 = U64_to_i64(i);
            (void)_t2029;
            ;
            Expr *f = Expr_child(body, _t2029);
            (void)f;
            Bool _t2030; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2030 = *_hp; free(_hp); }
            (void)_t2030;
            if (_t2030) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2025 = Bool_not(decl->is_namespace);
                (void)_t2025;
                if (_t2025) {
                    Bool _t2022; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2022 = *_hp; free(_hp); }
                    (void)_t2022;
                    if (_t2022) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t2029, &(Bool){1});
                        ;
                        Range_delete(_fc2020, &(Bool){1});
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2023 = 1;
                    (void)_t2023;
                    I32 _t2024 = I32_add(tag, _t2023);
                    (void)_t2024;
                    ;
                    tag = _t2024;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2029, &(Bool){1});
            ;
        }
        Range_delete(_fc2020, &(Bool){1});
        ;
    }
    I64_delete(_t2034, &(Bool){1});
    ;
    I64 _t2035 = 0;
    (void)_t2035;
    I64 _t2036 = 1;
    (void)_t2036;
    I64 _t2037 = I64_sub(_t2035, _t2036);
    (void)_t2037;
    ;
    ;
    I32 _t2038 = I64_to_i32(_t2037);
    (void)_t2038;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2038; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t2053 = malloc(sizeof(I64));
    *_t2053 = 0;
    (void)_t2053;
    Expr *body = Expr_child(enum_def, _t2053);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        I64 _t2050; { I64 *_hp = (I64 *)Expr_child_count(body); _t2050 = *_hp; free(_hp); }
        (void)_t2050;
        U64 _t2051 = 0;
        (void)_t2051;
        U64 _t2052 = I64_to_u64(_t2050);
        (void)_t2052;
        ;
        Range *_fc2039 = Range_new(_t2051, _t2052);
        (void)_fc2039;
        ;
        ;
        U64 _fi2039 = 0;
        (void)_fi2039;
        while (1) {
            U64 _t2045; { U64 *_hp = (U64 *)Range_len(_fc2039); _t2045 = *_hp; free(_hp); }
            (void)_t2045;
            Bool _wcond2040; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2039}, &(U64){_t2045}); _wcond2040 = *_hp; free(_hp); }
            (void)_wcond2040;
            ;
            if (_wcond2040) {
            } else {
                ;
                break;
            }
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_fc2039, _fi2039); i = *_hp; free(_hp); }
            (void)i;
            U64 _t2046 = 1;
            (void)_t2046;
            U64 _t2047 = U64_add(_fi2039, _t2046);
            (void)_t2047;
            ;
            _fi2039 = _t2047;
            ;
            I64 *_t2048 = malloc(sizeof(I64)); *_t2048 = U64_to_i64(i);
            (void)_t2048;
            ;
            Expr *f = Expr_child(body, _t2048);
            (void)f;
            Bool _t2049; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2049 = *_hp; free(_hp); }
            (void)_t2049;
            if (_t2049) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2044 = Bool_not(decl->is_namespace);
                (void)_t2044;
                if (_t2044) {
                    Bool _t2041 = I32_eq(idx, tag);
                    (void)_t2041;
                    if (_t2041) {
                        ;
                        ;
                        I64_delete(_t2048, &(Bool){1});
                        ;
                        Range_delete(_fc2039, &(Bool){1});
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t2042 = 1;
                    (void)_t2042;
                    I32 _t2043 = I32_add(idx, _t2042);
                    (void)_t2043;
                    ;
                    idx = _t2043;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t2048, &(Bool){1});
            ;
        }
        Range_delete(_fc2039, &(Bool){1});
        ;
    }
    I64_delete(_t2053, &(Bool){1});
    ;
    Str *_t2054 = Str_lit("", 0ULL);
    (void)_t2054;
    return _t2054;
}

