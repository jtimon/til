#include "til_til.h"

Expr * Expr_clone(Expr * self) {
    (void)self;
    Expr *_t1266 = malloc(sizeof(Expr));
    (void)_t1266;
    return _t1266;
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Token * Token_clone(Token * self) {
    (void)self;
    Token *_t1268 = malloc(sizeof(Token));
    (void)_t1268;
    return _t1268;
}

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

Mode * Mode_clone(Mode * self) {
    (void)self;
    Mode *_t1270 = malloc(sizeof(Mode));
    (void)_t1270;
    return _t1270;
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t1272 = malloc(sizeof(TypeScope));
    (void)_t1272;
    return _t1272;
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t1303 = Str_lit("Str", 3ULL);
    (void)_t1303;
    U64 _t1304; { U64 *_hp = (U64 *)Str_size(); _t1304 = *_hp; free(_hp); }
    (void)_t1304;
    Vec *paths = Vec_new(_t1303, &(U64){_t1304});
    (void)paths;
    Str_delete(_t1303, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t1278 = expr_nchildren(body);
        (void)_t1278;
        Bool _wcond1274; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1278}); _wcond1274 = *_hp; free(_hp); }
        (void)_wcond1274;
        ;
        if (_wcond1274) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t1279 = expr_get_tag(stmt);
        (void)_t1279;
        U32 _t1280 = expr_nchildren(stmt);
        (void)_t1280;
        U32 _t1281 = 2;
        (void)_t1281;
        Bool _t1282 = I32_eq(_t1279, DEREF(NODE_FCALL));
        (void)_t1282;
        ;
        Bool _t1283 = U32_eq(_t1280, _t1281);
        (void)_t1283;
        ;
        ;
        U32 *_t1284 = malloc(sizeof(U32));
        *_t1284 = 0;
        (void)_t1284;
        Expr *_t1285 = expr_get_child(stmt, DEREF(_t1284));
        (void)_t1285;
        I32 _t1286 = expr_get_tag(_t1285);
        (void)_t1286;
        U32_delete(_t1284, &(Bool){1});
        Bool _t1287 = Bool_and(_t1282, _t1283);
        (void)_t1287;
        ;
        ;
        Bool _t1288 = I32_eq(_t1286, DEREF(NODE_IDENT));
        (void)_t1288;
        ;
        U32 *_t1289 = malloc(sizeof(U32));
        *_t1289 = 0;
        (void)_t1289;
        Expr *_t1290 = expr_get_child(stmt, DEREF(_t1289));
        (void)_t1290;
        Str *_t1291 = expr_get_str_val(_t1290);
        (void)_t1291;
        Str *_t1292 = Str_lit("import", 6ULL);
        (void)_t1292;
        Bool _t1293 = Bool_and(_t1287, _t1288);
        (void)_t1293;
        ;
        ;
        Bool _t1294; { Bool *_hp = (Bool *)Str_eq(_t1291, _t1292); _t1294 = *_hp; free(_hp); }
        (void)_t1294;
        U32_delete(_t1289, &(Bool){1});
        Str_delete(_t1292, &(Bool){1});
        U32 *_t1295 = malloc(sizeof(U32));
        *_t1295 = 1;
        (void)_t1295;
        Expr *_t1296 = expr_get_child(stmt, DEREF(_t1295));
        (void)_t1296;
        I32 _t1297 = expr_get_tag(_t1296);
        (void)_t1297;
        U32_delete(_t1295, &(Bool){1});
        Bool _t1298 = Bool_and(_t1293, _t1294);
        (void)_t1298;
        ;
        ;
        Bool _t1299 = I32_eq(_t1297, DEREF(NODE_LITERAL_STR));
        (void)_t1299;
        ;
        Bool _t1300 = Bool_and(_t1298, _t1299);
        (void)_t1300;
        ;
        ;
        if (_t1300) {
            U32 *_t1275 = malloc(sizeof(U32));
            *_t1275 = 1;
            (void)_t1275;
            Expr *_t1276 = expr_get_child(stmt, DEREF(_t1275));
            (void)_t1276;
            Str *path = expr_get_str_val(_t1276);
            (void)path;
            Str *_t1277 = Str_clone(path);
            (void)_t1277;
            U32_delete(_t1275, &(Bool){1});
            Vec_push(paths, _t1277);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t1301 = 1;
        (void)_t1301;
        U32 _t1302 = U32_add(DEREF(i), _t1301);
        (void)_t1302;
        ;
        *i = _t1302;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(body, kept);
    Vec_delete(kept, &(Bool){1});
    return paths;
}

I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir) {
    (void)import_paths;
    (void)base_dir;
    (void)resolved_set;
    (void)stack;
    (void)merged;
    (void)lib_dir;
    {
        U64 _fi1305 = 0;
        (void)_fi1305;
        while (1) {
            U64 _t1335 = 0;
            (void)_t1335;
            U64 _t1336; { U64 *_hp = (U64 *)Vec_len(import_paths); _t1336 = *_hp; free(_hp); }
            (void)_t1336;
            Range *_t1337 = Range_new(_t1335, _t1336);
            (void)_t1337;
            ;
            ;
            U64 _t1338; { U64 *_hp = (U64 *)Range_len(_t1337); _t1338 = *_hp; free(_hp); }
            (void)_t1338;
            Range_delete(_t1337, &(Bool){1});
            Bool _wcond1306; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi1305}, &(U64){_t1338}); _wcond1306 = *_hp; free(_hp); }
            (void)_wcond1306;
            ;
            if (_wcond1306) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1339 = 0;
            (void)_t1339;
            U64 _t1340; { U64 *_hp = (U64 *)Vec_len(import_paths); _t1340 = *_hp; free(_hp); }
            (void)_t1340;
            Range *_t1341 = Range_new(_t1339, _t1340);
            (void)_t1341;
            ;
            ;
            U64 *i = Range_get(_t1341, _fi1305);
            (void)i;
            Range_delete(_t1341, &(Bool){1});
            U64 _t1342 = 1;
            (void)_t1342;
            U64 _t1343 = U64_add(_fi1305, _t1342);
            (void)_t1343;
            ;
            _fi1305 = _t1343;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t1344 = Str_lit("/", 1ULL);
            (void)_t1344;
            Str *_t1345 = Str_concat(base_dir, _t1344);
            (void)_t1345;
            Str_delete(_t1344, &(Bool){1});
            Str *try_path = Str_concat(_t1345, import_path);
            (void)try_path;
            Str_delete(_t1345, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t1346 = Str_lit("", 0ULL);
            (void)_t1346;
            U64 _t1347; { U64 *_hp = (U64 *)Str_len(lib_dir); _t1347 = *_hp; free(_hp); }
            (void)_t1347;
            U64 _t1348 = 0;
            (void)_t1348;
            Bool _t1349; { Bool *_hp = (Bool *)Str_eq(abs, _t1346); _t1349 = *_hp; free(_hp); }
            (void)_t1349;
            Str_delete(_t1346, &(Bool){1});
            Bool _t1350; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1347}, &(U64){_t1348}); _t1350 = *_hp; free(_hp); }
            (void)_t1350;
            ;
            ;
            Bool _t1351 = Bool_and(_t1349, _t1350);
            (void)_t1351;
            ;
            ;
            if (_t1351) {
                Str *_t1307 = Str_lit("/", 1ULL);
                (void)_t1307;
                Str *_t1308 = Str_concat(lib_dir, _t1307);
                (void)_t1308;
                Str_delete(_t1307, &(Bool){1});
                try_path = Str_concat(_t1308, import_path);
                Str_delete(_t1308, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t1352 = Str_lit("", 0ULL);
            (void)_t1352;
            Bool _t1353; { Bool *_hp = (Bool *)Str_eq(abs, _t1352); _t1353 = *_hp; free(_hp); }
            (void)_t1353;
            Str_delete(_t1352, &(Bool){1});
            if (_t1353) {
                Str *_t1309 = Str_lit("Str", 3ULL);
                (void)_t1309;
                U64 _t1310; { U64 *_hp = (U64 *)Str_size(); _t1310 = *_hp; free(_hp); }
                (void)_t1310;
                U64 _t1311 = 1;
                (void)_t1311;
                Array *_va20 = Array_new(_t1309, &(U64){_t1310}, &(U64){_t1311});
                (void)_va20;
                Str_delete(_t1309, &(Bool){1});
                ;
                ;
                Str *_t1312 = Str_lit("error: could not find import '", 30ULL);
                (void)_t1312;
                Str *_t1313 = Str_concat(_t1312, import_path);
                (void)_t1313;
                Str_delete(_t1312, &(Bool){1});
                Str *_t1314 = Str_lit("' (from ", 8ULL);
                (void)_t1314;
                Str *_t1315 = Str_concat(_t1313, _t1314);
                (void)_t1315;
                Str_delete(_t1313, &(Bool){1});
                Str_delete(_t1314, &(Bool){1});
                Str *_t1316 = Str_concat(_t1315, base_dir);
                (void)_t1316;
                Str_delete(_t1315, &(Bool){1});
                Str *_t1317 = Str_lit("/)", 2ULL);
                (void)_t1317;
                U64 _t1318 = 0;
                (void)_t1318;
                Str *_t1319 = Str_concat(_t1316, _t1317);
                (void)_t1319;
                Str_delete(_t1316, &(Bool){1});
                Str_delete(_t1317, &(Bool){1});
                Array_set(_va20, &(U64){_t1318}, _t1319);
                ;
                println(_va20);
                I64 _t1320 = 1;
                (void)_t1320;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t1320; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t1354 = til_set_has(resolved_set, abs);
            (void)_t1354;
            if (_t1354) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            til_set_add(resolved_set, abs);
            Str *source = readfile(abs);
            (void)source;
            Token *tokens = til_tokenize(source, abs);
            (void)tokens;
            Str_delete(source, &(Bool){1});
            U32 count = til_tok_count();
            (void)count;
            Expr *sub_ast = til_parse(tokens, count, abs);
            (void)sub_ast;
            ;
            Token_delete(tokens, &(Bool){1});
            Str *sub_mode = til_parse_mode();
            (void)sub_mode;
            Str_delete(sub_mode, &(Bool){1});
            Vec *sub_imports = extract_imports(sub_ast);
            (void)sub_imports;
            U64 _t1355; { U64 *_hp = (U64 *)Str_len(abs); _t1355 = *_hp; free(_hp); }
            (void)_t1355;
            U64 _t1356 = 1;
            (void)_t1356;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t1355, _t1356);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t1322 = 0;
                (void)_t1322;
                U8 *_t1323 = Str_get(abs, last_slash);
                (void)_t1323;
                U8 _t1324 = 47;
                (void)_t1324;
                Bool _t1325; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t1322}); _t1325 = *_hp; free(_hp); }
                (void)_t1325;
                ;
                Bool _t1326; { Bool *_hp = (Bool *)U8_neq(_t1323, &(U8){_t1324}); _t1326 = *_hp; free(_hp); }
                (void)_t1326;
                ;
                Bool _wcond1321 = Bool_and(_t1325, _t1326);
                (void)_wcond1321;
                ;
                ;
                if (_wcond1321) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1327 = 1;
                (void)_t1327;
                U64 _t1328 = U64_sub(DEREF(last_slash), _t1327);
                (void)_t1328;
                ;
                *last_slash = _t1328;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t1357; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t1357 = *_hp; free(_hp); }
            (void)_t1357;
            U64 _t1358 = 0;
            (void)_t1358;
            Bool _t1359; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1357}, &(U64){_t1358}); _t1359 = *_hp; free(_hp); }
            (void)_t1359;
            ;
            ;
            if (_t1359) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t1329 = 0;
                (void)_t1329;
                Bool _t1330; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t1329}); _t1330 = *_hp; free(_hp); }
                (void)_t1330;
                ;
                if (_t1330) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    ;
                    { I32 *_r = malloc(sizeof(I32)); *_r = err; return _r; }
                }
                ;
                ;
            }
            ;
            Str_delete(sub_dir, &(Bool){1});
            Vec_delete(sub_imports, &(Bool){1});
            U32 *k = malloc(sizeof(U32));
            *k = 0;
            (void)k;
            while (1) {
                U32 _t1332 = expr_nchildren(sub_ast);
                (void)_t1332;
                Bool _wcond1331; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t1332}); _wcond1331 = *_hp; free(_hp); }
                (void)_wcond1331;
                ;
                if (_wcond1331) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t1333 = 1;
                (void)_t1333;
                U32 _t1334 = U32_add(DEREF(k), _t1333);
                (void)_t1334;
                ;
                *k = _t1334;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t1360 = 0;
    (void)_t1360;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t1360; return _r; }
}

void usage(void) {
    Str *_t1361 = Str_lit("Str", 3ULL);
    (void)_t1361;
    U64 _t1362; { U64 *_hp = (U64 *)Str_size(); _t1362 = *_hp; free(_hp); }
    (void)_t1362;
    U64 _t1363 = 1;
    (void)_t1363;
    Array *_va21 = Array_new(_t1361, &(U64){_t1362}, &(U64){_t1363});
    (void)_va21;
    Str_delete(_t1361, &(Bool){1});
    ;
    ;
    U64 _t1364 = 0;
    (void)_t1364;
    Str *_t1365 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t1365;
    Array_set(_va21, &(U64){_t1364}, _t1365);
    ;
    println(_va21);
    Str *_t1366 = Str_lit("Str", 3ULL);
    (void)_t1366;
    U64 _t1367; { U64 *_hp = (U64 *)Str_size(); _t1367 = *_hp; free(_hp); }
    (void)_t1367;
    U64 _t1368 = 1;
    (void)_t1368;
    Array *_va22 = Array_new(_t1366, &(U64){_t1367}, &(U64){_t1368});
    (void)_va22;
    Str_delete(_t1366, &(Bool){1});
    ;
    ;
    U64 _t1369 = 0;
    (void)_t1369;
    Str *_t1370 = Str_lit("", 0ULL);
    (void)_t1370;
    Array_set(_va22, &(U64){_t1369}, _t1370);
    ;
    println(_va22);
    Str *_t1371 = Str_lit("Str", 3ULL);
    (void)_t1371;
    U64 _t1372; { U64 *_hp = (U64 *)Str_size(); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    U64 _t1373 = 1;
    (void)_t1373;
    Array *_va23 = Array_new(_t1371, &(U64){_t1372}, &(U64){_t1373});
    (void)_va23;
    Str_delete(_t1371, &(Bool){1});
    ;
    ;
    U64 _t1374 = 0;
    (void)_t1374;
    Str *_t1375 = Str_lit("Commands:", 9ULL);
    (void)_t1375;
    Array_set(_va23, &(U64){_t1374}, _t1375);
    ;
    println(_va23);
    Str *_t1376 = Str_lit("Str", 3ULL);
    (void)_t1376;
    U64 _t1377; { U64 *_hp = (U64 *)Str_size(); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    U64 _t1378 = 1;
    (void)_t1378;
    Array *_va24 = Array_new(_t1376, &(U64){_t1377}, &(U64){_t1378});
    (void)_va24;
    Str_delete(_t1376, &(Bool){1});
    ;
    ;
    U64 _t1379 = 0;
    (void)_t1379;
    Str *_t1380 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t1380;
    Array_set(_va24, &(U64){_t1379}, _t1380);
    ;
    println(_va24);
    Str *_t1381 = Str_lit("Str", 3ULL);
    (void)_t1381;
    U64 _t1382; { U64 *_hp = (U64 *)Str_size(); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    U64 _t1383 = 1;
    (void)_t1383;
    Array *_va25 = Array_new(_t1381, &(U64){_t1382}, &(U64){_t1383});
    (void)_va25;
    Str_delete(_t1381, &(Bool){1});
    ;
    ;
    U64 _t1384 = 0;
    (void)_t1384;
    Str *_t1385 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t1385;
    Array_set(_va25, &(U64){_t1384}, _t1385);
    ;
    println(_va25);
    Str *_t1386 = Str_lit("Str", 3ULL);
    (void)_t1386;
    U64 _t1387; { U64 *_hp = (U64 *)Str_size(); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    U64 _t1388 = 1;
    (void)_t1388;
    Array *_va26 = Array_new(_t1386, &(U64){_t1387}, &(U64){_t1388});
    (void)_va26;
    Str_delete(_t1386, &(Bool){1});
    ;
    ;
    U64 _t1389 = 0;
    (void)_t1389;
    Str *_t1390 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t1390;
    Array_set(_va26, &(U64){_t1389}, _t1390);
    ;
    println(_va26);
    Str *_t1391 = Str_lit("Str", 3ULL);
    (void)_t1391;
    U64 _t1392; { U64 *_hp = (U64 *)Str_size(); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    U64 _t1393 = 1;
    (void)_t1393;
    Array *_va27 = Array_new(_t1391, &(U64){_t1392}, &(U64){_t1393});
    (void)_va27;
    Str_delete(_t1391, &(Bool){1});
    ;
    ;
    U64 _t1394 = 0;
    (void)_t1394;
    Str *_t1395 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t1395;
    Array_set(_va27, &(U64){_t1394}, _t1395);
    ;
    println(_va27);
    Str *_t1396 = Str_lit("Str", 3ULL);
    (void)_t1396;
    U64 _t1397; { U64 *_hp = (U64 *)Str_size(); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    U64 _t1398 = 1;
    (void)_t1398;
    Array *_va28 = Array_new(_t1396, &(U64){_t1397}, &(U64){_t1398});
    (void)_va28;
    Str_delete(_t1396, &(Bool){1});
    ;
    ;
    U64 _t1399 = 0;
    (void)_t1399;
    Str *_t1400 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t1400;
    Array_set(_va28, &(U64){_t1399}, _t1400);
    ;
    println(_va28);
    Str *_t1401 = Str_lit("Str", 3ULL);
    (void)_t1401;
    U64 _t1402; { U64 *_hp = (U64 *)Str_size(); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    U64 _t1403 = 1;
    (void)_t1403;
    Array *_va29 = Array_new(_t1401, &(U64){_t1402}, &(U64){_t1403});
    (void)_va29;
    Str_delete(_t1401, &(Bool){1});
    ;
    ;
    U64 _t1404 = 0;
    (void)_t1404;
    Str *_t1405 = Str_lit("  help       Print this message", 31ULL);
    (void)_t1405;
    Array_set(_va29, &(U64){_t1404}, _t1405);
    ;
    println(_va29);
}

void mark_core(void * e) {
    (void)e;
    expr_set_core(e);
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t1407 = expr_nchildren(e);
        (void)_t1407;
        Bool _wcond1406; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1407}); _wcond1406 = *_hp; free(_hp); }
        (void)_wcond1406;
        ;
        if (_wcond1406) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t1408 = expr_get_child(e, DEREF(i));
        (void)_t1408;
        mark_core(_t1408);
        U32 _t1409 = 1;
        (void)_t1409;
        U32 _t1410 = U32_add(DEREF(i), _t1409);
        (void)_t1410;
        ;
        *i = _t1410;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t1871 = malloc(sizeof(I64));
    *_t1871 = 0;
    (void)_t1871;
    _t1872 = malloc(sizeof(I64));
    *_t1872 = 1;
    (void)_t1872;
    _t1873 = malloc(sizeof(I64)); *_t1873 = I64_sub(DEREF(_t1871), DEREF(_t1872));
    (void)_t1873;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t1873));
    (void)CAP_LIT;
    _t1874 = malloc(sizeof(I64));
    *_t1874 = 0;
    (void)_t1874;
    _t1875 = malloc(sizeof(I64));
    *_t1875 = 2;
    (void)_t1875;
    _t1876 = malloc(sizeof(I64)); *_t1876 = I64_sub(DEREF(_t1874), DEREF(_t1875));
    (void)_t1876;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t1876));
    (void)CAP_VIEW;
    NODE_BODY = malloc(sizeof(I32));
    *NODE_BODY = 0;
    (void)NODE_BODY;
    NODE_LITERAL_STR = malloc(sizeof(I32));
    *NODE_LITERAL_STR = 1;
    (void)NODE_LITERAL_STR;
    NODE_LITERAL_NUM = malloc(sizeof(I32));
    *NODE_LITERAL_NUM = 2;
    (void)NODE_LITERAL_NUM;
    NODE_LITERAL_BOOL = malloc(sizeof(I32));
    *NODE_LITERAL_BOOL = 3;
    (void)NODE_LITERAL_BOOL;
    NODE_LITERAL_NULL = malloc(sizeof(I32));
    *NODE_LITERAL_NULL = 4;
    (void)NODE_LITERAL_NULL;
    NODE_IDENT = malloc(sizeof(I32));
    *NODE_IDENT = 5;
    (void)NODE_IDENT;
    NODE_DECL = malloc(sizeof(I32));
    *NODE_DECL = 6;
    (void)NODE_DECL;
    NODE_ASSIGN = malloc(sizeof(I32));
    *NODE_ASSIGN = 7;
    (void)NODE_ASSIGN;
    NODE_FCALL = malloc(sizeof(I32));
    *NODE_FCALL = 8;
    (void)NODE_FCALL;
    NODE_FUNC_DEF = malloc(sizeof(I32));
    *NODE_FUNC_DEF = 9;
    (void)NODE_FUNC_DEF;
    NODE_STRUCT_DEF = malloc(sizeof(I32));
    *NODE_STRUCT_DEF = 10;
    (void)NODE_STRUCT_DEF;
    NODE_ENUM_DEF = malloc(sizeof(I32));
    *NODE_ENUM_DEF = 11;
    (void)NODE_ENUM_DEF;
    NODE_FIELD_ACCESS = malloc(sizeof(I32));
    *NODE_FIELD_ACCESS = 12;
    (void)NODE_FIELD_ACCESS;
    NODE_FIELD_ASSIGN = malloc(sizeof(I32));
    *NODE_FIELD_ASSIGN = 13;
    (void)NODE_FIELD_ASSIGN;
    NODE_RETURN = malloc(sizeof(I32));
    *NODE_RETURN = 14;
    (void)NODE_RETURN;
    NODE_IF = malloc(sizeof(I32));
    *NODE_IF = 15;
    (void)NODE_IF;
    NODE_WHILE = malloc(sizeof(I32));
    *NODE_WHILE = 16;
    (void)NODE_WHILE;
    NODE_FOR_IN = malloc(sizeof(I32));
    *NODE_FOR_IN = 17;
    (void)NODE_FOR_IN;
    NODE_NAMED_ARG = malloc(sizeof(I32));
    *NODE_NAMED_ARG = 18;
    (void)NODE_NAMED_ARG;
    NODE_BREAK = malloc(sizeof(I32));
    *NODE_BREAK = 19;
    (void)NODE_BREAK;
    NODE_CONTINUE = malloc(sizeof(I32));
    *NODE_CONTINUE = 20;
    (void)NODE_CONTINUE;
    NODE_MAP_LIT = malloc(sizeof(I32));
    *NODE_MAP_LIT = 21;
    (void)NODE_MAP_LIT;
    NODE_SET_LIT = malloc(sizeof(I32));
    *NODE_SET_LIT = 22;
    (void)NODE_SET_LIT;
    NODE_SWITCH = malloc(sizeof(I32));
    *NODE_SWITCH = 23;
    (void)NODE_SWITCH;
    NODE_CASE = malloc(sizeof(I32));
    *NODE_CASE = 24;
    (void)NODE_CASE;
    int _va_argc = argc - 1;
    U64 _va_esz = sizeof(Str);
    U64 _va_cap = _va_argc;
    Array *args = Array_new(&(Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}, &(U64){_va_esz}, &(U64){_va_cap});
    for (int _i = 0; _i < _va_argc; _i++) {
        U64 _idx = _i;
        Str *_val = Str_clone(&(Str){.c_str = (U8 *)argv[1 + _i], .count = strlen(argv[1 + _i]), .cap = TIL_CAP_LIT});
        Array_set(args, &(U64){_idx}, _val);
    }
    U64 _t1796; { U64 *_hp = (U64 *)Array_len(args); _t1796 = *_hp; free(_hp); }
    (void)_t1796;
    U64 _t1797 = 0;
    (void)_t1797;
    Bool _t1798 = U64_eq(_t1796, _t1797);
    (void)_t1798;
    ;
    ;
    if (_t1798) {
        usage();
        Str *_t1411 = Str_lit("Str", 3ULL);
        (void)_t1411;
        U64 _t1412; { U64 *_hp = (U64 *)Str_size(); _t1412 = *_hp; free(_hp); }
        (void)_t1412;
        U64 _t1413 = 1;
        (void)_t1413;
        Array *_va30 = Array_new(_t1411, &(U64){_t1412}, &(U64){_t1413});
        (void)_va30;
        Str_delete(_t1411, &(Bool){1});
        ;
        ;
        U64 _t1414 = 0;
        (void)_t1414;
        Str *_t1415 = Str_lit("no arguments", 12ULL);
        (void)_t1415;
        Array_set(_va30, &(U64){_t1414}, _t1415);
        ;
        Str *_t1416 = Str_lit("src/til.til:233:15", 18ULL);
        (void)_t1416;
        panic(_t1416, _va30);
        Str_delete(_t1416, &(Bool){1});
    }
    ;
    U64 *_t1799 = malloc(sizeof(U64));
    *_t1799 = 0;
    (void)_t1799;
    Str *cmd_ref = Array_get(args, _t1799);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t1799, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t1800; { U64 *_hp = (U64 *)Array_len(args); _t1800 = *_hp; free(_hp); }
    (void)_t1800;
    U64 _t1801 = 1;
    (void)_t1801;
    Bool _t1802 = U64_eq(_t1800, _t1801);
    (void)_t1802;
    ;
    ;
    if (_t1802) {
        Str *_t1417 = Str_lit("help", 4ULL);
        (void)_t1417;
        Str *_t1418 = Str_lit("--help", 6ULL);
        (void)_t1418;
        Bool _t1419; { Bool *_hp = (Bool *)Str_eq(command, _t1417); _t1419 = *_hp; free(_hp); }
        (void)_t1419;
        Str_delete(_t1417, &(Bool){1});
        Bool _t1420; { Bool *_hp = (Bool *)Str_eq(command, _t1418); _t1420 = *_hp; free(_hp); }
        (void)_t1420;
        Str_delete(_t1418, &(Bool){1});
        Bool _t1421 = Bool_or(_t1419, _t1420);
        (void)_t1421;
        ;
        ;
        if (_t1421) {
            usage();
            ;
            ;
            Array_delete(args, &(Bool){1});
            Str_delete(command, &(Bool){1});
            Str_delete(custom_bin, &(Bool){1});
            Str_delete(custom_c, &(Bool){1});
            Str_delete(path, &(Bool){1});
            U64_delete(path_idx, &(Bool){1});
            return 0;
        }
        ;
        path = Str_clone(command);
        command = Str_lit("interpret", 9ULL);
    } else {
        while (1) {
            U64 _t1438; { U64 *_hp = (U64 *)Array_len(args); _t1438 = *_hp; free(_hp); }
            (void)_t1438;
            Bool _wcond1422; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t1438}); _wcond1422 = *_hp; free(_hp); }
            (void)_wcond1422;
            ;
            if (_wcond1422) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t1439 = Str_lit("-o", 2ULL);
            (void)_t1439;
            U64 _t1440 = 1;
            (void)_t1440;
            U64 _t1441 = U64_add(DEREF(path_idx), _t1440);
            (void)_t1441;
            ;
            U64 _t1442; { U64 *_hp = (U64 *)Array_len(args); _t1442 = *_hp; free(_hp); }
            (void)_t1442;
            Bool _t1443; { Bool *_hp = (Bool *)Str_eq(flag, _t1439); _t1443 = *_hp; free(_hp); }
            (void)_t1443;
            Str_delete(_t1439, &(Bool){1});
            Bool _t1444; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1441}, &(U64){_t1442}); _t1444 = *_hp; free(_hp); }
            (void)_t1444;
            ;
            ;
            Bool _t1445 = Bool_and(_t1443, _t1444);
            (void)_t1445;
            ;
            ;
            if (_t1445) {
                U64 _t1423 = 1;
                (void)_t1423;
                U64 *_t1424 = malloc(sizeof(U64)); *_t1424 = U64_add(DEREF(path_idx), _t1423);
                (void)_t1424;
                ;
                Str *oval = Array_get(args, _t1424);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t1424, &(Bool){1});
                U64 _t1425 = 2;
                (void)_t1425;
                U64 _t1426 = U64_add(DEREF(path_idx), _t1425);
                (void)_t1426;
                ;
                *path_idx = _t1426;
                ;
            } else {
                Str *_t1431 = Str_lit("-c", 2ULL);
                (void)_t1431;
                U64 _t1432 = 1;
                (void)_t1432;
                U64 _t1433 = U64_add(DEREF(path_idx), _t1432);
                (void)_t1433;
                ;
                U64 _t1434; { U64 *_hp = (U64 *)Array_len(args); _t1434 = *_hp; free(_hp); }
                (void)_t1434;
                Bool _t1435; { Bool *_hp = (Bool *)Str_eq(flag, _t1431); _t1435 = *_hp; free(_hp); }
                (void)_t1435;
                Str_delete(_t1431, &(Bool){1});
                Bool _t1436; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1433}, &(U64){_t1434}); _t1436 = *_hp; free(_hp); }
                (void)_t1436;
                ;
                ;
                Bool _t1437 = Bool_and(_t1435, _t1436);
                (void)_t1437;
                ;
                ;
                if (_t1437) {
                    U64 _t1427 = 1;
                    (void)_t1427;
                    U64 *_t1428 = malloc(sizeof(U64)); *_t1428 = U64_add(DEREF(path_idx), _t1427);
                    (void)_t1428;
                    ;
                    Str *cval = Array_get(args, _t1428);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t1428, &(Bool){1});
                    U64 _t1429 = 2;
                    (void)_t1429;
                    U64 _t1430 = U64_add(DEREF(path_idx), _t1429);
                    (void)_t1430;
                    ;
                    *path_idx = _t1430;
                    ;
                } else {
                    ;
                    ;
                    break;
                }
                ;
            }
            ;
        }
        Str *p = Array_get(args, path_idx);
        (void)p;
        path = Str_clone(p);
    }
    ;
    Str *_t1803 = Str_lit("help", 4ULL);
    (void)_t1803;
    Str *_t1804 = Str_lit("--help", 6ULL);
    (void)_t1804;
    Bool _t1805; { Bool *_hp = (Bool *)Str_eq(command, _t1803); _t1805 = *_hp; free(_hp); }
    (void)_t1805;
    Str_delete(_t1803, &(Bool){1});
    Bool _t1806; { Bool *_hp = (Bool *)Str_eq(command, _t1804); _t1806 = *_hp; free(_hp); }
    (void)_t1806;
    Str_delete(_t1804, &(Bool){1});
    Bool _t1807 = Bool_or(_t1805, _t1806);
    (void)_t1807;
    ;
    ;
    if (_t1807) {
        usage();
        ;
        Array_delete(args, &(Bool){1});
        Str_delete(command, &(Bool){1});
        Str_delete(custom_bin, &(Bool){1});
        Str_delete(custom_c, &(Bool){1});
        Str_delete(path, &(Bool){1});
        U64_delete(path_idx, &(Bool){1});
        return 0;
    }
    ;
    Str *bin_dir = til_bin_dir();
    (void)bin_dir;
    Str *_t1808 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t1808;
    Str *core_path = Str_concat(bin_dir, _t1808);
    (void)core_path;
    Str_delete(_t1808, &(Bool){1});
    Str *_t1809 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t1809;
    Str *ext_c_path = Str_concat(bin_dir, _t1809);
    (void)ext_c_path;
    Str_delete(_t1809, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t1810; { U64 *_hp = (U64 *)Str_len(abs_path); _t1810 = *_hp; free(_hp); }
    (void)_t1810;
    U64 _t1811 = 0;
    (void)_t1811;
    Bool _t1812; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1810}, &(U64){_t1811}); _t1812 = *_hp; free(_hp); }
    (void)_t1812;
    ;
    ;
    if (_t1812) {
        U64 _t1454; { U64 *_hp = (U64 *)Str_len(abs_path); _t1454 = *_hp; free(_hp); }
        (void)_t1454;
        U64 _t1455 = 1;
        (void)_t1455;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t1454, _t1455);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t1447 = 0;
            (void)_t1447;
            U8 *_t1448 = Str_get(abs_path, last_slash);
            (void)_t1448;
            U8 _t1449 = 47;
            (void)_t1449;
            Bool _t1450; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t1447}); _t1450 = *_hp; free(_hp); }
            (void)_t1450;
            ;
            Bool _t1451; { Bool *_hp = (Bool *)U8_neq(_t1448, &(U8){_t1449}); _t1451 = *_hp; free(_hp); }
            (void)_t1451;
            ;
            Bool _wcond1446 = Bool_and(_t1450, _t1451);
            (void)_wcond1446;
            ;
            ;
            if (_wcond1446) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1452 = 1;
            (void)_t1452;
            U64 _t1453 = U64_sub(DEREF(last_slash), _t1452);
            (void)_t1453;
            ;
            *last_slash = _t1453;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        til_set_add(resolved, abs_path);
    }
    ;
    Str_delete(abs_path, &(Bool){1});
    Str *core_source = readfile(core_path);
    (void)core_source;
    Token *core_tokens = til_tokenize(core_source, core_path);
    (void)core_tokens;
    Str_delete(core_source, &(Bool){1});
    U32 core_count = til_tok_count();
    (void)core_count;
    Expr *core_ast = til_parse(core_tokens, core_count, core_path);
    (void)core_ast;
    ;
    Token_delete(core_tokens, &(Bool){1});
    Bool skip_core = 0;
    (void)skip_core;
    Str *core_abs = til_realpath(core_path);
    (void)core_abs;
    Str_delete(core_path, &(Bool){1});
    U64 _t1813; { U64 *_hp = (U64 *)Str_len(core_abs); _t1813 = *_hp; free(_hp); }
    (void)_t1813;
    U64 _t1814 = 0;
    (void)_t1814;
    Bool _t1815; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1813}, &(U64){_t1814}); _t1815 = *_hp; free(_hp); }
    (void)_t1815;
    ;
    ;
    if (_t1815) {
        Bool _t1457 = til_set_has(resolved, core_abs);
        (void)_t1457;
        if (_t1457) {
            Bool _t1456 = 1;
            (void)_t1456;
            skip_core = _t1456;
            ;
        }
        ;
        til_set_add(resolved, core_abs);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t1816; { U64 *_hp = (U64 *)Vec_len(core_imports); _t1816 = *_hp; free(_hp); }
    (void)_t1816;
    U64 _t1817 = 0;
    (void)_t1817;
    Bool _t1818; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1816}, &(U64){_t1817}); _t1818 = *_hp; free(_hp); }
    (void)_t1818;
    ;
    ;
    Bool _t1819 = Bool_not(skip_core);
    (void)_t1819;
    Bool _t1820 = Bool_and(_t1818, _t1819);
    (void)_t1820;
    ;
    ;
    if (_t1820) {
        Str *_t1464 = Str_lit("/src/core", 9ULL);
        (void)_t1464;
        Str *core_dir = Str_concat(bin_dir, _t1464);
        (void)core_dir;
        Str_delete(_t1464, &(Bool){1});
        Str *_t1465 = Str_lit("", 0ULL);
        (void)_t1465;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t1465); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t1465, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t1466 = 0;
        (void)_t1466;
        Bool _t1467; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t1466}); _t1467 = *_hp; free(_hp); }
        (void)_t1467;
        ;
        ;
        if (_t1467) {
            Str *_t1458 = Str_lit("Str", 3ULL);
            (void)_t1458;
            U64 _t1459; { U64 *_hp = (U64 *)Str_size(); _t1459 = *_hp; free(_hp); }
            (void)_t1459;
            U64 _t1460 = 1;
            (void)_t1460;
            Array *_va31 = Array_new(_t1458, &(U64){_t1459}, &(U64){_t1460});
            (void)_va31;
            Str_delete(_t1458, &(Bool){1});
            ;
            ;
            U64 _t1461 = 0;
            (void)_t1461;
            Str *_t1462 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t1462;
            Array_set(_va31, &(U64){_t1461}, _t1462);
            ;
            Str *_t1463 = Str_lit("src/til.til:320:19", 18ULL);
            (void)_t1463;
            panic(_t1463, _va31);
            Str_delete(_t1463, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(core_imports, &(Bool){1});
    Str *source = readfile(path);
    (void)source;
    Token *tokens = til_tokenize(source, path);
    (void)tokens;
    Str_delete(source, &(Bool){1});
    U32 count = til_tok_count();
    (void)count;
    Expr *ast = til_parse(tokens, count, path);
    (void)ast;
    ;
    Token_delete(tokens, &(Bool){1});
    Vec *imports = extract_imports(ast);
    (void)imports;
    Str *mode_str = til_parse_mode();
    (void)mode_str;
    Mode *cur_mode = til_mode_none();
    (void)cur_mode;
    U64 _t1821; { U64 *_hp = (U64 *)Str_len(mode_str); _t1821 = *_hp; free(_hp); }
    (void)_t1821;
    U64 _t1822 = 0;
    (void)_t1822;
    Bool _t1823; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1821}, &(U64){_t1822}); _t1823 = *_hp; free(_hp); }
    (void)_t1823;
    ;
    ;
    if (_t1823) {
        cur_mode = til_mode_resolve(mode_str);
        Mode *_t1477 = til_mode_none();
        (void)_t1477;
        Bool _t1478 = til_mode_eq(cur_mode, _t1477);
        (void)_t1478;
        Mode_delete(_t1477, &(Bool){1});
        if (_t1478) {
            Str *_t1468 = Str_lit("Str", 3ULL);
            (void)_t1468;
            U64 _t1469; { U64 *_hp = (U64 *)Str_size(); _t1469 = *_hp; free(_hp); }
            (void)_t1469;
            U64 _t1470 = 1;
            (void)_t1470;
            Array *_va32 = Array_new(_t1468, &(U64){_t1469}, &(U64){_t1470});
            (void)_va32;
            Str_delete(_t1468, &(Bool){1});
            ;
            ;
            Str *_t1471 = Str_lit("unknown mode '", 14ULL);
            (void)_t1471;
            Str *_t1472 = Str_concat(_t1471, mode_str);
            (void)_t1472;
            Str_delete(_t1471, &(Bool){1});
            Str *_t1473 = Str_lit("'", 1ULL);
            (void)_t1473;
            U64 _t1474 = 0;
            (void)_t1474;
            Str *_t1475 = Str_concat(_t1472, _t1473);
            (void)_t1475;
            Str_delete(_t1472, &(Bool){1});
            Str_delete(_t1473, &(Bool){1});
            Array_set(_va32, &(U64){_t1474}, _t1475);
            ;
            Str *_t1476 = Str_lit("src/til.til:337:19", 18ULL);
            (void)_t1476;
            panic(_t1476, _va32);
            Str_delete(_t1476, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Expr *mode_ast = expr_null();
    (void)mode_ast;
    Str *auto_import = til_mode_auto_import(cur_mode);
    (void)auto_import;
    U64 _t1824; { U64 *_hp = (U64 *)Str_len(auto_import); _t1824 = *_hp; free(_hp); }
    (void)_t1824;
    U64 _t1825 = 0;
    (void)_t1825;
    Bool _t1826; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1824}, &(U64){_t1825}); _t1826 = *_hp; free(_hp); }
    (void)_t1826;
    ;
    ;
    if (_t1826) {
        Str *_t1479 = Str_lit("/src/modes/", 11ULL);
        (void)_t1479;
        Str *_t1480 = Str_concat(bin_dir, _t1479);
        (void)_t1480;
        Str_delete(_t1479, &(Bool){1});
        Str *_t1481 = Str_concat(_t1480, auto_import);
        (void)_t1481;
        Str_delete(_t1480, &(Bool){1});
        Str *_t1482 = Str_lit(".til", 4ULL);
        (void)_t1482;
        Str *mode_til_path = Str_concat(_t1481, _t1482);
        (void)mode_til_path;
        Str_delete(_t1481, &(Bool){1});
        Str_delete(_t1482, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Token *mode_tokens = til_tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        U32 mode_count = til_tok_count();
        (void)mode_count;
        mode_ast = til_parse(mode_tokens, mode_count, mode_til_path);
        ;
        Str_delete(mode_til_path, &(Bool){1});
        Token_delete(mode_tokens, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t1827; { U64 *_hp = (U64 *)Vec_len(imports); _t1827 = *_hp; free(_hp); }
    (void)_t1827;
    U64 _t1828 = 0;
    (void)_t1828;
    Bool _t1829; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1827}, &(U64){_t1828}); _t1829 = *_hp; free(_hp); }
    (void)_t1829;
    ;
    ;
    if (_t1829) {
        Str *_t1489 = Str_lit("/src/lib", 8ULL);
        (void)_t1489;
        Str *lib_dir = Str_concat(bin_dir, _t1489);
        (void)lib_dir;
        Str_delete(_t1489, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t1490 = 0;
        (void)_t1490;
        Bool _t1491; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t1490}); _t1491 = *_hp; free(_hp); }
        (void)_t1491;
        ;
        ;
        if (_t1491) {
            Str *_t1483 = Str_lit("Str", 3ULL);
            (void)_t1483;
            U64 _t1484; { U64 *_hp = (U64 *)Str_size(); _t1484 = *_hp; free(_hp); }
            (void)_t1484;
            U64 _t1485 = 1;
            (void)_t1485;
            Array *_va33 = Array_new(_t1483, &(U64){_t1484}, &(U64){_t1485});
            (void)_va33;
            Str_delete(_t1483, &(Bool){1});
            ;
            ;
            U64 _t1486 = 0;
            (void)_t1486;
            Str *_t1487 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t1487;
            Array_set(_va33, &(U64){_t1486}, _t1487);
            ;
            Str *_t1488 = Str_lit("src/til.til:359:19", 18ULL);
            (void)_t1488;
            panic(_t1488, _va33);
            Str_delete(_t1488, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(bin_dir, &(Bool){1});
    Vec_delete(imports, &(Bool){1});
    Vec_delete(resolve_stack, &(Bool){1});
    Set_delete(resolved, &(Bool){1});
    Str_delete(user_dir, &(Bool){1});
    Vec *merged = expr_vec_new();
    (void)merged;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    Bool _t1830 = Bool_not(skip_core);
    (void)_t1830;
    ;
    if (_t1830) {
        while (1) {
            U32 _t1493 = expr_nchildren(core_ast);
            (void)_t1493;
            Bool _wcond1492; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1493}); _wcond1492 = *_hp; free(_hp); }
            (void)_wcond1492;
            ;
            if (_wcond1492) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t1494 = 1;
            (void)_t1494;
            U32 _t1495 = U32_add(DEREF(i), _t1494);
            (void)_t1495;
            ;
            *i = _t1495;
            ;
        }
        U32 _t1500 = 0;
        (void)_t1500;
        *i = _t1500;
        ;
        while (1) {
            U32 _t1497 = expr_vec_count(core_import_decls);
            (void)_t1497;
            Bool _wcond1496; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1497}); _wcond1496 = *_hp; free(_hp); }
            (void)_wcond1496;
            ;
            if (_wcond1496) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t1498 = 1;
            (void)_t1498;
            U32 _t1499 = U32_add(DEREF(i), _t1498);
            (void)_t1499;
            ;
            *i = _t1499;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    Bool _t1831 = expr_is_null(mode_ast);
    (void)_t1831;
    Bool _t1832 = Bool_not(_t1831);
    (void)_t1832;
    ;
    if (_t1832) {
        U32 _t1505 = 0;
        (void)_t1505;
        *i = _t1505;
        ;
        while (1) {
            U32 _t1502 = expr_nchildren(mode_ast);
            (void)_t1502;
            Bool _wcond1501; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1502}); _wcond1501 = *_hp; free(_hp); }
            (void)_wcond1501;
            ;
            if (_wcond1501) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t1503 = 1;
            (void)_t1503;
            U32 _t1504 = U32_add(DEREF(i), _t1503);
            (void)_t1504;
            ;
            *i = _t1504;
            ;
        }
    }
    ;
    Expr_delete(mode_ast, &(Bool){1});
    U32 _t1833 = 0;
    (void)_t1833;
    *i = _t1833;
    ;
    while (1) {
        U32 _t1507 = expr_vec_count(import_decls);
        (void)_t1507;
        Bool _wcond1506; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1507}); _wcond1506 = *_hp; free(_hp); }
        (void)_wcond1506;
        ;
        if (_wcond1506) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t1508 = 1;
        (void)_t1508;
        U32 _t1509 = U32_add(DEREF(i), _t1508);
        (void)_t1509;
        ;
        *i = _t1509;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t1834 = 0;
    (void)_t1834;
    *i = _t1834;
    ;
    while (1) {
        U32 _t1511 = expr_nchildren(ast);
        (void)_t1511;
        Bool _wcond1510; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1511}); _wcond1510 = *_hp; free(_hp); }
        (void)_wcond1510;
        ;
        if (_wcond1510) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t1512 = 1;
        (void)_t1512;
        U32 _t1513 = U32_add(DEREF(i), _t1512);
        (void)_t1513;
        ;
        *i = _t1513;
        ;
    }
    expr_swap_children(ast, merged);
    Vec_delete(merged, &(Bool){1});
    Str *link_flags = Str_lit("", 0ULL);
    (void)link_flags;
    Str *link_c_paths = Str_lit("", 0ULL);
    (void)link_c_paths;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 _t1835 = 0;
    (void)_t1835;
    *i = _t1835;
    ;
    while (1) {
        U32 _t1529 = expr_nchildren(ast);
        (void)_t1529;
        Bool _wcond1514; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t1529}); _wcond1514 = *_hp; free(_hp); }
        (void)_wcond1514;
        ;
        if (_wcond1514) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t1530 = expr_get_tag(stmt);
        (void)_t1530;
        U32 _t1531 = expr_nchildren(stmt);
        (void)_t1531;
        U32 _t1532 = 2;
        (void)_t1532;
        Bool _t1533 = I32_eq(_t1530, DEREF(NODE_FCALL));
        (void)_t1533;
        ;
        Bool _t1534 = U32_eq(_t1531, _t1532);
        (void)_t1534;
        ;
        ;
        U32 *_t1535 = malloc(sizeof(U32));
        *_t1535 = 0;
        (void)_t1535;
        Expr *_t1536 = expr_get_child(stmt, DEREF(_t1535));
        (void)_t1536;
        I32 _t1537 = expr_get_tag(_t1536);
        (void)_t1537;
        U32_delete(_t1535, &(Bool){1});
        Bool _t1538 = Bool_and(_t1533, _t1534);
        (void)_t1538;
        ;
        ;
        Bool _t1539 = I32_eq(_t1537, DEREF(NODE_IDENT));
        (void)_t1539;
        ;
        U32 *_t1540 = malloc(sizeof(U32));
        *_t1540 = 1;
        (void)_t1540;
        Expr *_t1541 = expr_get_child(stmt, DEREF(_t1540));
        (void)_t1541;
        I32 _t1542 = expr_get_tag(_t1541);
        (void)_t1542;
        U32_delete(_t1540, &(Bool){1});
        Bool _t1543 = Bool_and(_t1538, _t1539);
        (void)_t1543;
        ;
        ;
        Bool _t1544 = I32_eq(_t1542, DEREF(NODE_LITERAL_STR));
        (void)_t1544;
        ;
        Bool _t1545 = Bool_and(_t1543, _t1544);
        (void)_t1545;
        ;
        ;
        if (_t1545) {
            U32 *_t1523 = malloc(sizeof(U32));
            *_t1523 = 0;
            (void)_t1523;
            Expr *_t1524 = expr_get_child(stmt, DEREF(_t1523));
            (void)_t1524;
            Str *fname = expr_get_str_val(_t1524);
            (void)fname;
            U32 *_t1525 = malloc(sizeof(U32));
            *_t1525 = 1;
            (void)_t1525;
            Expr *_t1526 = expr_get_child(stmt, DEREF(_t1525));
            (void)_t1526;
            Str *arg = expr_get_str_val(_t1526);
            (void)arg;
            Str *_t1527 = Str_lit("link", 4ULL);
            (void)_t1527;
            Bool _t1528; { Bool *_hp = (Bool *)Str_eq(fname, _t1527); _t1528 = *_hp; free(_hp); }
            (void)_t1528;
            Str_delete(_t1527, &(Bool){1});
            if (_t1528) {
                Str *_t1515 = Str_lit(" -l", 3ULL);
                (void)_t1515;
                Str *_t1516 = Str_concat(link_flags, _t1515);
                (void)_t1516;
                Str_delete(_t1515, &(Bool){1});
                link_flags = Str_concat(_t1516, arg);
                Str_delete(_t1516, &(Bool){1});
            } else {
                Str *_t1521 = Str_lit("link_c", 6ULL);
                (void)_t1521;
                Bool _t1522; { Bool *_hp = (Bool *)Str_eq(fname, _t1521); _t1522 = *_hp; free(_hp); }
                (void)_t1522;
                Str_delete(_t1521, &(Bool){1});
                if (_t1522) {
                    U64 _t1518; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t1518 = *_hp; free(_hp); }
                    (void)_t1518;
                    U64 _t1519 = 0;
                    (void)_t1519;
                    Bool _t1520; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1518}, &(U64){_t1519}); _t1520 = *_hp; free(_hp); }
                    (void)_t1520;
                    ;
                    ;
                    if (_t1520) {
                        Str *_t1517 = Str_lit(" ", 1ULL);
                        (void)_t1517;
                        link_c_paths = Str_concat(link_c_paths, _t1517);
                        Str_delete(_t1517, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t1523, &(Bool){1});
            U32_delete(_t1525, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t1546 = 1;
        (void)_t1546;
        U32 _t1547 = U32_add(DEREF(i), _t1546);
        (void)_t1547;
        ;
        *i = _t1547;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t1836 = til_init_declarations(ast, scope);
    (void)_t1836;
    ;
    I32 type_errors = til_type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t1837 = 0;
    (void)_t1837;
    Bool _t1838; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t1837}); _t1838 = *_hp; free(_hp); }
    (void)_t1838;
    ;
    if (_t1838) {
        Str *_t1548 = Str_lit("Str", 3ULL);
        (void)_t1548;
        U64 _t1549; { U64 *_hp = (U64 *)Str_size(); _t1549 = *_hp; free(_hp); }
        (void)_t1549;
        U64 _t1550 = 1;
        (void)_t1550;
        Array *_va34 = Array_new(_t1548, &(U64){_t1549}, &(U64){_t1550});
        (void)_va34;
        Str_delete(_t1548, &(Bool){1});
        ;
        ;
        Str *_t1551 = I32_to_str(&(I32){type_errors});
        (void)_t1551;
        Str *_t1552 = Str_lit(" type error(s) found", 20ULL);
        (void)_t1552;
        U64 _t1553 = 0;
        (void)_t1553;
        Str *_t1554 = Str_concat(_t1551, _t1552);
        (void)_t1554;
        Str_delete(_t1551, &(Bool){1});
        Str_delete(_t1552, &(Bool){1});
        Array_set(_va34, &(U64){_t1553}, _t1554);
        ;
        Str *_t1555 = Str_lit("src/til.til:450:15", 18ULL);
        (void)_t1555;
        panic(_t1555, _va34);
        Str_delete(_t1555, &(Bool){1});
    }
    ;
    ;
    Str *_t1839 = Str_lit("test", 4ULL);
    (void)_t1839;
    Mode *_t1840 = til_mode_test();
    (void)_t1840;
    Bool _t1841; { Bool *_hp = (Bool *)Str_eq(command, _t1839); _t1841 = *_hp; free(_hp); }
    (void)_t1841;
    Str_delete(_t1839, &(Bool){1});
    Bool _t1842 = til_mode_eq(cur_mode, _t1840);
    (void)_t1842;
    Mode_delete(_t1840, &(Bool){1});
    Mode *_t1843 = til_mode_pure();
    (void)_t1843;
    Bool _t1844 = Bool_or(_t1841, _t1842);
    (void)_t1844;
    ;
    ;
    Bool _t1845 = til_mode_eq(cur_mode, _t1843);
    (void)_t1845;
    Mode_delete(_t1843, &(Bool){1});
    Mode *_t1846 = til_mode_pura();
    (void)_t1846;
    Bool _t1847 = Bool_or(_t1844, _t1845);
    (void)_t1847;
    ;
    ;
    Bool _t1848 = til_mode_eq(cur_mode, _t1846);
    (void)_t1848;
    Mode_delete(_t1846, &(Bool){1});
    Bool run_tests = Bool_or(_t1847, _t1848);
    (void)run_tests;
    ;
    ;
    til_precomp(ast);
    Str *_t1849 = Str_lit("translate", 9ULL);
    (void)_t1849;
    Str *_t1850 = Str_lit("build", 5ULL);
    (void)_t1850;
    Bool _t1851; { Bool *_hp = (Bool *)Str_eq(command, _t1849); _t1851 = *_hp; free(_hp); }
    (void)_t1851;
    Str_delete(_t1849, &(Bool){1});
    Bool _t1852; { Bool *_hp = (Bool *)Str_eq(command, _t1850); _t1852 = *_hp; free(_hp); }
    (void)_t1852;
    Str_delete(_t1850, &(Bool){1});
    Bool _t1853 = til_mode_is_lib_output(cur_mode);
    (void)_t1853;
    Bool _t1854 = Bool_or(_t1851, _t1852);
    (void)_t1854;
    ;
    ;
    Bool is_lib_target = Bool_and(_t1853, _t1854);
    (void)is_lib_target;
    ;
    ;
    Bool _t1855 = Bool_not(is_lib_target);
    (void)_t1855;
    ;
    if (_t1855) {
        til_scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t1856; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t1856 = *_hp; free(_hp); }
    (void)_t1856;
    U64 _t1857 = 0;
    (void)_t1857;
    Bool _t1858; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1856}, &(U64){_t1857}); _t1858 = *_hp; free(_hp); }
    (void)_t1858;
    ;
    ;
    if (_t1858) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t1859 = Str_lit("Str", 3ULL);
    (void)_t1859;
    U64 _t1860; { U64 *_hp = (U64 *)Str_size(); _t1860 = *_hp; free(_hp); }
    (void)_t1860;
    Vec *user_argv = Vec_new(_t1859, &(U64){_t1860});
    (void)user_argv;
    Str_delete(_t1859, &(Bool){1});
    ;
    U64 _t1861 = 1;
    (void)_t1861;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t1861);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t1572; { U64 *_hp = (U64 *)Array_len(args); _t1572 = *_hp; free(_hp); }
        (void)_t1572;
        Bool _wcond1556; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t1572}); _wcond1556 = *_hp; free(_hp); }
        (void)_wcond1556;
        ;
        if (_wcond1556) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t1573 = Str_lit("-l", 2ULL);
        (void)_t1573;
        Bool _t1574; { Bool *_hp = (Bool *)Str_starts_with(arg, _t1573); _t1574 = *_hp; free(_hp); }
        (void)_t1574;
        Str_delete(_t1573, &(Bool){1});
        if (_t1574) {
            U64 _t1559 = 2;
            (void)_t1559;
            U64 _t1560; { U64 *_hp = (U64 *)Str_len(arg); _t1560 = *_hp; free(_hp); }
            (void)_t1560;
            Str *lib = Str_substr(arg, &(U64){_t1559}, &(U64){_t1560});
            (void)lib;
            ;
            ;
            U64 _t1561; { U64 *_hp = (U64 *)Str_len(lib); _t1561 = *_hp; free(_hp); }
            (void)_t1561;
            U64 _t1562 = 0;
            (void)_t1562;
            U64 _t1563 = 1;
            (void)_t1563;
            U64 _t1564 = U64_add(DEREF(ai), _t1563);
            (void)_t1564;
            ;
            U64 _t1565; { U64 *_hp = (U64 *)Array_len(args); _t1565 = *_hp; free(_hp); }
            (void)_t1565;
            Bool _t1566 = U64_eq(_t1561, _t1562);
            (void)_t1566;
            ;
            ;
            Bool _t1567; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1564}, &(U64){_t1565}); _t1567 = *_hp; free(_hp); }
            (void)_t1567;
            ;
            ;
            Bool _t1568 = Bool_and(_t1566, _t1567);
            (void)_t1568;
            ;
            ;
            if (_t1568) {
                U64 _t1557 = 1;
                (void)_t1557;
                U64 _t1558 = U64_add(DEREF(ai), _t1557);
                (void)_t1558;
                ;
                *ai = _t1558;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t1569 = Str_lit(" -l", 3ULL);
            (void)_t1569;
            Str *_t1570 = Str_concat(link_flags, _t1569);
            (void)_t1570;
            Str_delete(_t1569, &(Bool){1});
            link_flags = Str_concat(_t1570, lib);
            Str_delete(_t1570, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t1571 = Str_clone(arg);
            (void)_t1571;
            Vec_push(user_argv, _t1571);
        }
        ;
        U64 _t1575 = 1;
        (void)_t1575;
        U64 _t1576 = U64_add(DEREF(ai), _t1575);
        (void)_t1576;
        ;
        *ai = _t1576;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t1862; { U64 *_hp = (U64 *)Str_len(link_flags); _t1862 = *_hp; free(_hp); }
    (void)_t1862;
    U64 _t1863 = 0;
    (void)_t1863;
    Bool _t1864; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1862}, &(U64){_t1863}); _t1864 = *_hp; free(_hp); }
    (void)_t1864;
    ;
    ;
    if (_t1864) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode = til_mode_is_lib(cur_mode);
    (void)is_lib_mode;
    Str *_t1865 = Str_lit("interpret", 9ULL);
    (void)_t1865;
    Str *_t1866 = Str_lit("test", 4ULL);
    (void)_t1866;
    Bool _t1867; { Bool *_hp = (Bool *)Str_eq(command, _t1865); _t1867 = *_hp; free(_hp); }
    (void)_t1867;
    Str_delete(_t1865, &(Bool){1});
    Bool _t1868; { Bool *_hp = (Bool *)Str_eq(command, _t1866); _t1868 = *_hp; free(_hp); }
    (void)_t1868;
    Str_delete(_t1866, &(Bool){1});
    Bool _t1869 = Bool_or(_t1867, _t1868);
    (void)_t1869;
    ;
    ;
    if (_t1869) {
        Str *_t1583 = Str_lit("interpret", 9ULL);
        (void)_t1583;
        Bool _t1584; { Bool *_hp = (Bool *)Str_eq(command, _t1583); _t1584 = *_hp; free(_hp); }
        (void)_t1584;
        Str_delete(_t1583, &(Bool){1});
        Bool _t1585 = Bool_and(is_lib_mode, _t1584);
        (void)_t1585;
        ;
        if (_t1585) {
            Str *_t1577 = Str_lit("Str", 3ULL);
            (void)_t1577;
            U64 _t1578; { U64 *_hp = (U64 *)Str_size(); _t1578 = *_hp; free(_hp); }
            (void)_t1578;
            U64 _t1579 = 1;
            (void)_t1579;
            Array *_va35 = Array_new(_t1577, &(U64){_t1578}, &(U64){_t1579});
            (void)_va35;
            Str_delete(_t1577, &(Bool){1});
            ;
            ;
            U64 _t1580 = 0;
            (void)_t1580;
            Str *_t1581 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t1581;
            Array_set(_va35, &(U64){_t1580}, _t1581);
            ;
            Str *_t1582 = Str_lit("src/til.til:503:19", 18ULL);
            (void)_t1582;
            panic(_t1582, _va35);
            Str_delete(_t1582, &(Bool){1});
        }
        ;
        I32 _t1586 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t1586;
        result = _t1586;
        ;
    } else {
        Str *_t1788 = Str_lit("translate", 9ULL);
        (void)_t1788;
        Str *_t1789 = Str_lit("build", 5ULL);
        (void)_t1789;
        Bool _t1790; { Bool *_hp = (Bool *)Str_eq(command, _t1788); _t1790 = *_hp; free(_hp); }
        (void)_t1790;
        Str_delete(_t1788, &(Bool){1});
        Bool _t1791; { Bool *_hp = (Bool *)Str_eq(command, _t1789); _t1791 = *_hp; free(_hp); }
        (void)_t1791;
        Str_delete(_t1789, &(Bool){1});
        Str *_t1792 = Str_lit("run", 3ULL);
        (void)_t1792;
        Bool _t1793 = Bool_or(_t1790, _t1791);
        (void)_t1793;
        ;
        ;
        Bool _t1794; { Bool *_hp = (Bool *)Str_eq(command, _t1792); _t1794 = *_hp; free(_hp); }
        (void)_t1794;
        Str_delete(_t1792, &(Bool){1});
        Bool _t1795 = Bool_or(_t1793, _t1794);
        (void)_t1795;
        ;
        ;
        if (_t1795) {
            Str *_t1712 = Str_lit("run", 3ULL);
            (void)_t1712;
            Bool _t1713; { Bool *_hp = (Bool *)Str_eq(command, _t1712); _t1713 = *_hp; free(_hp); }
            (void)_t1713;
            Str_delete(_t1712, &(Bool){1});
            Bool _t1714 = Bool_and(is_lib_mode, _t1713);
            (void)_t1714;
            ;
            if (_t1714) {
                Str *_t1587 = Str_lit("Str", 3ULL);
                (void)_t1587;
                U64 _t1588; { U64 *_hp = (U64 *)Str_size(); _t1588 = *_hp; free(_hp); }
                (void)_t1588;
                U64 _t1589 = 1;
                (void)_t1589;
                Array *_va36 = Array_new(_t1587, &(U64){_t1588}, &(U64){_t1589});
                (void)_va36;
                Str_delete(_t1587, &(Bool){1});
                ;
                ;
                U64 _t1590 = 0;
                (void)_t1590;
                Str *_t1591 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t1591;
                Array_set(_va36, &(U64){_t1590}, _t1591);
                ;
                Str *_t1592 = Str_lit("src/til.til:509:19", 18ULL);
                (void)_t1592;
                panic(_t1592, _va36);
                Str_delete(_t1592, &(Bool){1});
            }
            ;
            Str *_t1715 = Str_lit("/", 1ULL);
            (void)_t1715;
            I64 *last_slash = Str_rfind(path, _t1715);
            (void)last_slash;
            Str_delete(_t1715, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t1716 = 0;
            (void)_t1716;
            Bool _t1717; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t1716}); _t1717 = *_hp; free(_hp); }
            (void)_t1717;
            ;
            if (_t1717) {
                I64 _t1593 = 1;
                (void)_t1593;
                I64 _t1594 = I64_add(DEREF(last_slash), _t1593);
                (void)_t1594;
                ;
                U64 _t1595; { U64 *_hp = (U64 *)Str_len(path); _t1595 = *_hp; free(_hp); }
                (void)_t1595;
                U64 _t1596 = I64_to_u64(DEREF(last_slash));
                (void)_t1596;
                U64 _t1597 = U64_sub(_t1595, _t1596);
                (void)_t1597;
                ;
                ;
                U64 _t1598 = 1;
                (void)_t1598;
                U64 _t1599 = I64_to_u64(_t1594);
                (void)_t1599;
                ;
                U64 _t1600 = U64_sub(_t1597, _t1598);
                (void)_t1600;
                ;
                ;
                basename = Str_substr(path, &(U64){_t1599}, &(U64){_t1600});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t1718 = Str_lit(".til", 4ULL);
            (void)_t1718;
            Bool _t1719; { Bool *_hp = (Bool *)Str_ends_with(basename, _t1718); _t1719 = *_hp; free(_hp); }
            (void)_t1719;
            Str_delete(_t1718, &(Bool){1});
            if (_t1719) {
                U64 _t1601 = 4;
                (void)_t1601;
                U64 _t1602 = U64_sub(name_len, _t1601);
                (void)_t1602;
                ;
                name_len = _t1602;
                ;
            }
            ;
            U64 _t1720 = 0;
            (void)_t1720;
            Str *name = Str_substr(basename, &(U64){_t1720}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t1721 = Str_lit("gen/til/", 8ULL);
            (void)_t1721;
            Str *_t1722 = Str_concat(_t1721, name);
            (void)_t1722;
            Str_delete(_t1721, &(Bool){1});
            Str *_t1723 = Str_lit(".c", 2ULL);
            (void)_t1723;
            Str *c_path = Str_concat(_t1722, _t1723);
            (void)c_path;
            Str_delete(_t1722, &(Bool){1});
            Str_delete(_t1723, &(Bool){1});
            U64 _t1724; { U64 *_hp = (U64 *)Str_len(custom_c); _t1724 = *_hp; free(_hp); }
            (void)_t1724;
            U64 _t1725 = 0;
            (void)_t1725;
            Bool _t1726; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1724}, &(U64){_t1725}); _t1726 = *_hp; free(_hp); }
            (void)_t1726;
            ;
            ;
            if (_t1726) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t1727 = Str_lit("bin/til/", 8ULL);
            (void)_t1727;
            Str *bin_path = Str_concat(_t1727, name);
            (void)bin_path;
            Str_delete(_t1727, &(Bool){1});
            U64 _t1728; { U64 *_hp = (U64 *)Str_len(custom_bin); _t1728 = *_hp; free(_hp); }
            (void)_t1728;
            U64 _t1729 = 0;
            (void)_t1729;
            Bool _t1730; { Bool *_hp = (Bool *)U64_gt(&(U64){_t1728}, &(U64){_t1729}); _t1730 = *_hp; free(_hp); }
            (void)_t1730;
            ;
            ;
            if (_t1730) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t1731 = Str_lit("run", 3ULL);
            (void)_t1731;
            Bool _t1732; { Bool *_hp = (Bool *)Str_eq(command, _t1731); _t1732 = *_hp; free(_hp); }
            (void)_t1732;
            Str_delete(_t1731, &(Bool){1});
            Bool _t1733 = til_mode_is_lib_output(cur_mode);
            (void)_t1733;
            Bool _t1734 = Bool_not(_t1732);
            (void)_t1734;
            ;
            Bool do_lib = Bool_and(_t1733, _t1734);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t1603 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t1603;
                I32 _t1604 = til_system(_t1603);
                (void)_t1604;
                Str_delete(_t1603, &(Bool){1});
                ;
            } else {
                Str *_t1609 = Str_lit("/", 1ULL);
                (void)_t1609;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t1609); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t1609, &(Bool){1});
                Str *_t1610 = Str_lit("/", 1ULL);
                (void)_t1610;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t1610); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t1610, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t1611 = 0;
                (void)_t1611;
                Bool _t1612; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t1611}); _t1612 = *_hp; free(_hp); }
                (void)_t1612;
                ;
                if (_t1612) {
                    U64 _t1605 = 0;
                    (void)_t1605;
                    U64 _t1606 = I64_to_u64(cp_slash);
                    (void)_t1606;
                    cp_dir = Str_substr(c_path, &(U64){_t1605}, &(U64){_t1606});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t1613 = 0;
                (void)_t1613;
                Bool _t1614; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t1613}); _t1614 = *_hp; free(_hp); }
                (void)_t1614;
                ;
                if (_t1614) {
                    U64 _t1607 = 0;
                    (void)_t1607;
                    U64 _t1608 = I64_to_u64(bp_slash);
                    (void)_t1608;
                    bp_dir = Str_substr(bin_path, &(U64){_t1607}, &(U64){_t1608});
                    ;
                    ;
                }
                ;
                ;
                Str *_t1615 = Str_lit("mkdir -p ", 9ULL);
                (void)_t1615;
                Str *_t1616 = Str_concat(_t1615, cp_dir);
                (void)_t1616;
                Str_delete(_t1615, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t1617 = Str_lit(" ", 1ULL);
                (void)_t1617;
                Str *_t1618 = Str_concat(_t1616, _t1617);
                (void)_t1618;
                Str_delete(_t1616, &(Bool){1});
                Str_delete(_t1617, &(Bool){1});
                Str *_t1619 = Str_concat(_t1618, bp_dir);
                (void)_t1619;
                Str_delete(_t1618, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t1620 = til_system(_t1619);
                (void)_t1620;
                Str_delete(_t1619, &(Bool){1});
                ;
            }
            I32 _t1735 = til_build(ast, cur_mode, run_tests, path, c_path);
            (void)_t1735;
            result = _t1735;
            ;
            I32 _t1736 = 0;
            (void)_t1736;
            Bool _t1737 = I32_eq(result, _t1736);
            (void)_t1737;
            ;
            Bool _t1738 = Bool_and(_t1737, do_lib);
            (void)_t1738;
            ;
            if (_t1738) {
                Str *_t1677 = Str_lit("gen/til/", 8ULL);
                (void)_t1677;
                Str *_t1678 = Str_concat(_t1677, name);
                (void)_t1678;
                Str_delete(_t1677, &(Bool){1});
                Str *_t1679 = Str_lit(".h", 2ULL);
                (void)_t1679;
                Str *h_path = Str_concat(_t1678, _t1679);
                (void)h_path;
                Str_delete(_t1678, &(Bool){1});
                Str_delete(_t1679, &(Bool){1});
                Str *_t1680 = Str_lit("gen/til/", 8ULL);
                (void)_t1680;
                Str *_t1681 = Str_concat(_t1680, name);
                (void)_t1681;
                Str_delete(_t1680, &(Bool){1});
                Str *_t1682 = Str_lit(".til", 4ULL);
                (void)_t1682;
                Str *til_path = Str_concat(_t1681, _t1682);
                (void)til_path;
                Str_delete(_t1681, &(Bool){1});
                Str_delete(_t1682, &(Bool){1});
                I32 _t1683 = til_build_header(ast, h_path);
                (void)_t1683;
                result = _t1683;
                ;
                I32 _t1684 = 0;
                (void)_t1684;
                Bool _t1685 = I32_eq(result, _t1684);
                (void)_t1685;
                ;
                if (_t1685) {
                    I32 _t1621 = til_build_til_binding(ast, til_path, name);
                    (void)_t1621;
                    result = _t1621;
                    ;
                }
                ;
                I32 _t1686 = 0;
                (void)_t1686;
                Str *_t1687 = Str_lit("translate", 9ULL);
                (void)_t1687;
                Bool _t1688 = I32_eq(result, _t1686);
                (void)_t1688;
                ;
                Bool _t1689; { Bool *_hp = (Bool *)Str_eq(command, _t1687); _t1689 = *_hp; free(_hp); }
                (void)_t1689;
                Str_delete(_t1687, &(Bool){1});
                Bool _t1690 = Bool_and(_t1688, _t1689);
                (void)_t1690;
                ;
                ;
                if (_t1690) {
                    Str *_t1622 = Str_lit("Str", 3ULL);
                    (void)_t1622;
                    U64 _t1623; { U64 *_hp = (U64 *)Str_size(); _t1623 = *_hp; free(_hp); }
                    (void)_t1623;
                    U64 _t1624 = 1;
                    (void)_t1624;
                    Array *_va37 = Array_new(_t1622, &(U64){_t1623}, &(U64){_t1624});
                    (void)_va37;
                    Str_delete(_t1622, &(Bool){1});
                    ;
                    ;
                    Str *_t1625 = Str_lit("Generated: ", 11ULL);
                    (void)_t1625;
                    U64 _t1626 = 0;
                    (void)_t1626;
                    Str *_t1627 = Str_concat(_t1625, c_path);
                    (void)_t1627;
                    Str_delete(_t1625, &(Bool){1});
                    Array_set(_va37, &(U64){_t1626}, _t1627);
                    ;
                    println(_va37);
                    Str *_t1628 = Str_lit("Str", 3ULL);
                    (void)_t1628;
                    U64 _t1629; { U64 *_hp = (U64 *)Str_size(); _t1629 = *_hp; free(_hp); }
                    (void)_t1629;
                    U64 _t1630 = 1;
                    (void)_t1630;
                    Array *_va38 = Array_new(_t1628, &(U64){_t1629}, &(U64){_t1630});
                    (void)_va38;
                    Str_delete(_t1628, &(Bool){1});
                    ;
                    ;
                    Str *_t1631 = Str_lit("Generated: ", 11ULL);
                    (void)_t1631;
                    U64 _t1632 = 0;
                    (void)_t1632;
                    Str *_t1633 = Str_concat(_t1631, h_path);
                    (void)_t1633;
                    Str_delete(_t1631, &(Bool){1});
                    Array_set(_va38, &(U64){_t1632}, _t1633);
                    ;
                    println(_va38);
                    Str *_t1634 = Str_lit("Str", 3ULL);
                    (void)_t1634;
                    U64 _t1635; { U64 *_hp = (U64 *)Str_size(); _t1635 = *_hp; free(_hp); }
                    (void)_t1635;
                    U64 _t1636 = 1;
                    (void)_t1636;
                    Array *_va39 = Array_new(_t1634, &(U64){_t1635}, &(U64){_t1636});
                    (void)_va39;
                    Str_delete(_t1634, &(Bool){1});
                    ;
                    ;
                    Str *_t1637 = Str_lit("Generated: ", 11ULL);
                    (void)_t1637;
                    U64 _t1638 = 0;
                    (void)_t1638;
                    Str *_t1639 = Str_concat(_t1637, til_path);
                    (void)_t1639;
                    Str_delete(_t1637, &(Bool){1});
                    Array_set(_va39, &(U64){_t1638}, _t1639);
                    ;
                    println(_va39);
                }
                ;
                I32 _t1691 = 0;
                (void)_t1691;
                Str *_t1692 = Str_lit("build", 5ULL);
                (void)_t1692;
                Bool _t1693 = I32_eq(result, _t1691);
                (void)_t1693;
                ;
                Bool _t1694; { Bool *_hp = (Bool *)Str_eq(command, _t1692); _t1694 = *_hp; free(_hp); }
                (void)_t1694;
                Str_delete(_t1692, &(Bool){1});
                Bool _t1695 = Bool_and(_t1693, _t1694);
                (void)_t1695;
                ;
                ;
                if (_t1695) {
                    I32 _t1674 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t1674;
                    result = _t1674;
                    ;
                    I32 _t1675 = 0;
                    (void)_t1675;
                    Bool _t1676 = I32_eq(result, _t1675);
                    (void)_t1676;
                    ;
                    if (_t1676) {
                        Str *_t1640 = Str_lit("Str", 3ULL);
                        (void)_t1640;
                        U64 _t1641; { U64 *_hp = (U64 *)Str_size(); _t1641 = *_hp; free(_hp); }
                        (void)_t1641;
                        U64 _t1642 = 1;
                        (void)_t1642;
                        Array *_va40 = Array_new(_t1640, &(U64){_t1641}, &(U64){_t1642});
                        (void)_va40;
                        Str_delete(_t1640, &(Bool){1});
                        ;
                        ;
                        Str *_t1643 = Str_lit("Generated: ", 11ULL);
                        (void)_t1643;
                        U64 _t1644 = 0;
                        (void)_t1644;
                        Str *_t1645 = Str_concat(_t1643, c_path);
                        (void)_t1645;
                        Str_delete(_t1643, &(Bool){1});
                        Array_set(_va40, &(U64){_t1644}, _t1645);
                        ;
                        println(_va40);
                        Str *_t1646 = Str_lit("Str", 3ULL);
                        (void)_t1646;
                        U64 _t1647; { U64 *_hp = (U64 *)Str_size(); _t1647 = *_hp; free(_hp); }
                        (void)_t1647;
                        U64 _t1648 = 1;
                        (void)_t1648;
                        Array *_va41 = Array_new(_t1646, &(U64){_t1647}, &(U64){_t1648});
                        (void)_va41;
                        Str_delete(_t1646, &(Bool){1});
                        ;
                        ;
                        Str *_t1649 = Str_lit("Generated: ", 11ULL);
                        (void)_t1649;
                        U64 _t1650 = 0;
                        (void)_t1650;
                        Str *_t1651 = Str_concat(_t1649, h_path);
                        (void)_t1651;
                        Str_delete(_t1649, &(Bool){1});
                        Array_set(_va41, &(U64){_t1650}, _t1651);
                        ;
                        println(_va41);
                        Str *_t1652 = Str_lit("Str", 3ULL);
                        (void)_t1652;
                        U64 _t1653; { U64 *_hp = (U64 *)Str_size(); _t1653 = *_hp; free(_hp); }
                        (void)_t1653;
                        U64 _t1654 = 1;
                        (void)_t1654;
                        Array *_va42 = Array_new(_t1652, &(U64){_t1653}, &(U64){_t1654});
                        (void)_va42;
                        Str_delete(_t1652, &(Bool){1});
                        ;
                        ;
                        Str *_t1655 = Str_lit("Generated: ", 11ULL);
                        (void)_t1655;
                        U64 _t1656 = 0;
                        (void)_t1656;
                        Str *_t1657 = Str_concat(_t1655, til_path);
                        (void)_t1657;
                        Str_delete(_t1655, &(Bool){1});
                        Array_set(_va42, &(U64){_t1656}, _t1657);
                        ;
                        println(_va42);
                        Str *_t1658 = Str_lit("Str", 3ULL);
                        (void)_t1658;
                        U64 _t1659; { U64 *_hp = (U64 *)Str_size(); _t1659 = *_hp; free(_hp); }
                        (void)_t1659;
                        U64 _t1660 = 1;
                        (void)_t1660;
                        Array *_va43 = Array_new(_t1658, &(U64){_t1659}, &(U64){_t1660});
                        (void)_va43;
                        Str_delete(_t1658, &(Bool){1});
                        ;
                        ;
                        Str *_t1661 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t1661;
                        Str *_t1662 = Str_concat(_t1661, name);
                        (void)_t1662;
                        Str_delete(_t1661, &(Bool){1});
                        Str *_t1663 = Str_lit(".so", 3ULL);
                        (void)_t1663;
                        U64 _t1664 = 0;
                        (void)_t1664;
                        Str *_t1665 = Str_concat(_t1662, _t1663);
                        (void)_t1665;
                        Str_delete(_t1662, &(Bool){1});
                        Str_delete(_t1663, &(Bool){1});
                        Array_set(_va43, &(U64){_t1664}, _t1665);
                        ;
                        println(_va43);
                        Str *_t1666 = Str_lit("Str", 3ULL);
                        (void)_t1666;
                        U64 _t1667; { U64 *_hp = (U64 *)Str_size(); _t1667 = *_hp; free(_hp); }
                        (void)_t1667;
                        U64 _t1668 = 1;
                        (void)_t1668;
                        Array *_va44 = Array_new(_t1666, &(U64){_t1667}, &(U64){_t1668});
                        (void)_va44;
                        Str_delete(_t1666, &(Bool){1});
                        ;
                        ;
                        Str *_t1669 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t1669;
                        Str *_t1670 = Str_concat(_t1669, name);
                        (void)_t1670;
                        Str_delete(_t1669, &(Bool){1});
                        Str *_t1671 = Str_lit(".a", 2ULL);
                        (void)_t1671;
                        U64 _t1672 = 0;
                        (void)_t1672;
                        Str *_t1673 = Str_concat(_t1670, _t1671);
                        (void)_t1673;
                        Str_delete(_t1670, &(Bool){1});
                        Str_delete(_t1671, &(Bool){1});
                        Array_set(_va44, &(U64){_t1672}, _t1673);
                        ;
                        println(_va44);
                    }
                    ;
                }
                ;
                Str_delete(h_path, &(Bool){1});
                Str_delete(til_path, &(Bool){1});
            }
            ;
            Str_delete(name, &(Bool){1});
            I32 _t1739 = 0;
            (void)_t1739;
            Bool _t1740 = I32_eq(result, _t1739);
            (void)_t1740;
            ;
            Bool _t1741 = Bool_not(do_lib);
            (void)_t1741;
            Str *_t1742 = Str_lit("translate", 9ULL);
            (void)_t1742;
            Bool _t1743 = Bool_and(_t1740, _t1741);
            (void)_t1743;
            ;
            ;
            Bool _t1744; { Bool *_hp = (Bool *)Str_eq(command, _t1742); _t1744 = *_hp; free(_hp); }
            (void)_t1744;
            Str_delete(_t1742, &(Bool){1});
            Bool _t1745 = Bool_and(_t1743, _t1744);
            (void)_t1745;
            ;
            ;
            if (_t1745) {
                Str *_t1696 = Str_lit("Str", 3ULL);
                (void)_t1696;
                U64 _t1697; { U64 *_hp = (U64 *)Str_size(); _t1697 = *_hp; free(_hp); }
                (void)_t1697;
                U64 _t1698 = 1;
                (void)_t1698;
                Array *_va45 = Array_new(_t1696, &(U64){_t1697}, &(U64){_t1698});
                (void)_va45;
                Str_delete(_t1696, &(Bool){1});
                ;
                ;
                Str *_t1699 = Str_lit("Generated: ", 11ULL);
                (void)_t1699;
                U64 _t1700 = 0;
                (void)_t1700;
                Str *_t1701 = Str_concat(_t1699, c_path);
                (void)_t1701;
                Str_delete(_t1699, &(Bool){1});
                Array_set(_va45, &(U64){_t1700}, _t1701);
                ;
                println(_va45);
            }
            ;
            I32 _t1746 = 0;
            (void)_t1746;
            Bool _t1747 = I32_eq(result, _t1746);
            (void)_t1747;
            ;
            Bool _t1748 = Bool_not(do_lib);
            (void)_t1748;
            Str *_t1749 = Str_lit("translate", 9ULL);
            (void)_t1749;
            Bool _t1750; { Bool *_hp = (Bool *)Str_eq(command, _t1749); _t1750 = *_hp; free(_hp); }
            (void)_t1750;
            Str_delete(_t1749, &(Bool){1});
            Bool _t1751 = Bool_and(_t1747, _t1748);
            (void)_t1751;
            ;
            ;
            Bool _t1752 = Bool_not(_t1750);
            (void)_t1752;
            ;
            Bool _t1753 = Bool_and(_t1751, _t1752);
            (void)_t1753;
            ;
            ;
            if (_t1753) {
                I32 _t1702 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t1702;
                result = _t1702;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t1754 = 0;
            (void)_t1754;
            Bool _t1755 = I32_eq(result, _t1754);
            (void)_t1755;
            ;
            Bool _t1756 = Bool_not(do_lib);
            (void)_t1756;
            ;
            Str *_t1757 = Str_lit("run", 3ULL);
            (void)_t1757;
            Bool _t1758 = Bool_and(_t1755, _t1756);
            (void)_t1758;
            ;
            ;
            Bool _t1759; { Bool *_hp = (Bool *)Str_eq(command, _t1757); _t1759 = *_hp; free(_hp); }
            (void)_t1759;
            Str_delete(_t1757, &(Bool){1});
            Bool _t1760 = Bool_and(_t1758, _t1759);
            (void)_t1760;
            ;
            ;
            if (_t1760) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t1704; { U64 *_hp = (U64 *)Vec_len(user_argv); _t1704 = *_hp; free(_hp); }
                    (void)_t1704;
                    Bool _wcond1703; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t1704}); _wcond1703 = *_hp; free(_hp); }
                    (void)_wcond1703;
                    ;
                    if (_wcond1703) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t1705 = Str_lit(" '", 2ULL);
                    (void)_t1705;
                    Str *_t1706 = Str_concat(cmd, _t1705);
                    (void)_t1706;
                    Str_delete(_t1705, &(Bool){1});
                    Str *_t1707 = Str_concat(_t1706, uarg);
                    (void)_t1707;
                    Str_delete(_t1706, &(Bool){1});
                    Str *_t1708 = Str_lit("'", 1ULL);
                    (void)_t1708;
                    cmd = Str_concat(_t1707, _t1708);
                    Str_delete(_t1707, &(Bool){1});
                    Str_delete(_t1708, &(Bool){1});
                    U64 _t1709 = 1;
                    (void)_t1709;
                    U64 _t1710 = U64_add(DEREF(ui), _t1709);
                    (void)_t1710;
                    ;
                    *ui = _t1710;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t1711 = til_system(cmd);
                (void)_t1711;
                Str_delete(cmd, &(Bool){1});
                result = _t1711;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t1786 = Str_lit("ast", 3ULL);
            (void)_t1786;
            Bool _t1787; { Bool *_hp = (Bool *)Str_eq(command, _t1786); _t1787 = *_hp; free(_hp); }
            (void)_t1787;
            Str_delete(_t1786, &(Bool){1});
            if (_t1787) {
                Mode *_t1773 = til_mode_none();
                (void)_t1773;
                Bool _t1774 = til_mode_eq(cur_mode, _t1773);
                (void)_t1774;
                Mode_delete(_t1773, &(Bool){1});
                Bool _t1775 = Bool_not(_t1774);
                (void)_t1775;
                ;
                if (_t1775) {
                    Str *_t1761 = Str_lit("Str", 3ULL);
                    (void)_t1761;
                    U64 _t1762; { U64 *_hp = (U64 *)Str_size(); _t1762 = *_hp; free(_hp); }
                    (void)_t1762;
                    U64 _t1763 = 1;
                    (void)_t1763;
                    Array *_va46 = Array_new(_t1761, &(U64){_t1762}, &(U64){_t1763});
                    (void)_va46;
                    Str_delete(_t1761, &(Bool){1});
                    ;
                    ;
                    Str *_t1764 = Str_lit("mode: ", 6ULL);
                    (void)_t1764;
                    Str *_t1765 = til_mode_name(cur_mode);
                    (void)_t1765;
                    U64 _t1766 = 0;
                    (void)_t1766;
                    Str *_t1767 = Str_concat(_t1764, _t1765);
                    (void)_t1767;
                    Str_delete(_t1764, &(Bool){1});
                    Str_delete(_t1765, &(Bool){1});
                    Array_set(_va46, &(U64){_t1766}, _t1767);
                    ;
                    println(_va46);
                } else {
                    Str *_t1768 = Str_lit("Str", 3ULL);
                    (void)_t1768;
                    U64 _t1769; { U64 *_hp = (U64 *)Str_size(); _t1769 = *_hp; free(_hp); }
                    (void)_t1769;
                    U64 _t1770 = 1;
                    (void)_t1770;
                    Array *_va47 = Array_new(_t1768, &(U64){_t1769}, &(U64){_t1770});
                    (void)_va47;
                    Str_delete(_t1768, &(Bool){1});
                    ;
                    ;
                    U64 _t1771 = 0;
                    (void)_t1771;
                    Str *_t1772 = Str_lit("mode: (none)", 12ULL);
                    (void)_t1772;
                    Array_set(_va47, &(U64){_t1771}, _t1772);
                    ;
                    println(_va47);
                }
                ;
                U32 _t1776 = 0;
                (void)_t1776;
                til_ast_print(ast, _t1776);
                ;
            } else {
                Str *_t1777 = Str_lit("Str", 3ULL);
                (void)_t1777;
                U64 _t1778; { U64 *_hp = (U64 *)Str_size(); _t1778 = *_hp; free(_hp); }
                (void)_t1778;
                U64 _t1779 = 1;
                (void)_t1779;
                Array *_va48 = Array_new(_t1777, &(U64){_t1778}, &(U64){_t1779});
                (void)_va48;
                Str_delete(_t1777, &(Bool){1});
                ;
                ;
                Str *_t1780 = Str_lit("error: unknown command '", 24ULL);
                (void)_t1780;
                Str *_t1781 = Str_concat(_t1780, command);
                (void)_t1781;
                Str_delete(_t1780, &(Bool){1});
                Str *_t1782 = Str_lit("'", 1ULL);
                (void)_t1782;
                U64 _t1783 = 0;
                (void)_t1783;
                Str *_t1784 = Str_concat(_t1781, _t1782);
                (void)_t1784;
                Str_delete(_t1781, &(Bool){1});
                Str_delete(_t1782, &(Bool){1});
                Array_set(_va48, &(U64){_t1783}, _t1784);
                ;
                println(_va48);
                usage();
                I32 _t1785 = 1;
                (void)_t1785;
                result = _t1785;
                ;
            }
            ;
        }
        ;
    }
    ;
    Expr_delete(ast, &(Bool){1});
    Str_delete(command, &(Bool){1});
    Mode_delete(cur_mode, &(Bool){1});
    Str_delete(custom_bin, &(Bool){1});
    Str_delete(custom_c, &(Bool){1});
    Str_delete(ext_c_path, &(Bool){1});
    ;
    Str_delete(lflags, &(Bool){1});
    Str_delete(path, &(Bool){1});
    ;
    Vec_delete(user_argv, &(Bool){1});
    Str_delete(user_c, &(Bool){1});
    I64 _t1870 = I32_to_i64(result);
    (void)_t1870;
    ;
    exit(_t1870);
    ;
    return 0;
}

