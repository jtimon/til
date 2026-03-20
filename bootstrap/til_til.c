#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4296 = Str_lit("Str", 3ULL);
    (void)_t4296;
    U64 _t4297; { U64 *_hp = (U64 *)Str_size(); _t4297 = *_hp; free(_hp); }
    (void)_t4297;
    Vec *paths = Vec_new(_t4296, &(U64){_t4297});
    (void)paths;
    Str_delete(_t4296, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4271 = expr_nchildren(body);
        (void)_t4271;
        Bool _wcond4267; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4271}); _wcond4267 = *_hp; free(_hp); }
        (void)_wcond4267;
        ;
        if (_wcond4267) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4272 = expr_get_tag(stmt);
        (void)_t4272;
        U32 _t4273 = expr_nchildren(stmt);
        (void)_t4273;
        U32 _t4274 = 2;
        (void)_t4274;
        Bool _t4275 = I32_eq(_t4272, DEREF(NODE_FCALL));
        (void)_t4275;
        ;
        Bool _t4276 = U32_eq(_t4273, _t4274);
        (void)_t4276;
        ;
        ;
        U32 *_t4277 = malloc(sizeof(U32));
        *_t4277 = 0;
        (void)_t4277;
        Expr *_t4278 = expr_get_child(stmt, DEREF(_t4277));
        (void)_t4278;
        I32 _t4279 = expr_get_tag(_t4278);
        (void)_t4279;
        U32_delete(_t4277, &(Bool){1});
        Bool _t4280 = Bool_and(_t4275, _t4276);
        (void)_t4280;
        ;
        ;
        Bool _t4281 = I32_eq(_t4279, DEREF(NODE_IDENT));
        (void)_t4281;
        ;
        U32 *_t4282 = malloc(sizeof(U32));
        *_t4282 = 0;
        (void)_t4282;
        Expr *_t4283 = expr_get_child(stmt, DEREF(_t4282));
        (void)_t4283;
        Str *_t4284 = expr_get_str_val(_t4283);
        (void)_t4284;
        Str *_t4285 = Str_lit("import", 6ULL);
        (void)_t4285;
        Bool _t4286 = Bool_and(_t4280, _t4281);
        (void)_t4286;
        ;
        ;
        Bool _t4287; { Bool *_hp = (Bool *)Str_eq(_t4284, _t4285); _t4287 = *_hp; free(_hp); }
        (void)_t4287;
        U32_delete(_t4282, &(Bool){1});
        Str_delete(_t4285, &(Bool){1});
        U32 *_t4288 = malloc(sizeof(U32));
        *_t4288 = 1;
        (void)_t4288;
        Expr *_t4289 = expr_get_child(stmt, DEREF(_t4288));
        (void)_t4289;
        I32 _t4290 = expr_get_tag(_t4289);
        (void)_t4290;
        U32_delete(_t4288, &(Bool){1});
        Bool _t4291 = Bool_and(_t4286, _t4287);
        (void)_t4291;
        ;
        ;
        Bool _t4292 = I32_eq(_t4290, DEREF(NODE_LITERAL_STR));
        (void)_t4292;
        ;
        Bool _t4293 = Bool_and(_t4291, _t4292);
        (void)_t4293;
        ;
        ;
        if (_t4293) {
            U32 *_t4268 = malloc(sizeof(U32));
            *_t4268 = 1;
            (void)_t4268;
            Expr *_t4269 = expr_get_child(stmt, DEREF(_t4268));
            (void)_t4269;
            Str *path = expr_get_str_val(_t4269);
            (void)path;
            Str *_t4270 = Str_clone(path);
            (void)_t4270;
            U32_delete(_t4268, &(Bool){1});
            Vec_push(paths, _t4270);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4294 = 1;
        (void)_t4294;
        U32 _t4295 = U32_add(DEREF(i), _t4294);
        (void)_t4295;
        ;
        *i = _t4295;
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
        U64 _fi4298 = 0;
        (void)_fi4298;
        while (1) {
            U64 _t4328 = 0;
            (void)_t4328;
            U64 _t4329; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4329 = *_hp; free(_hp); }
            (void)_t4329;
            Range *_t4330 = Range_new(_t4328, _t4329);
            (void)_t4330;
            ;
            ;
            U64 _t4331; { U64 *_hp = (U64 *)Range_len(_t4330); _t4331 = *_hp; free(_hp); }
            (void)_t4331;
            Range_delete(_t4330, &(Bool){1});
            Bool _wcond4299; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4298}, &(U64){_t4331}); _wcond4299 = *_hp; free(_hp); }
            (void)_wcond4299;
            ;
            if (_wcond4299) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4332 = 0;
            (void)_t4332;
            U64 _t4333; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4333 = *_hp; free(_hp); }
            (void)_t4333;
            Range *_t4334 = Range_new(_t4332, _t4333);
            (void)_t4334;
            ;
            ;
            U64 *i = Range_get(_t4334, _fi4298);
            (void)i;
            Range_delete(_t4334, &(Bool){1});
            U64 _t4335 = 1;
            (void)_t4335;
            U64 _t4336 = U64_add(_fi4298, _t4335);
            (void)_t4336;
            ;
            _fi4298 = _t4336;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4337 = Str_lit("/", 1ULL);
            (void)_t4337;
            Str *_t4338 = Str_concat(base_dir, _t4337);
            (void)_t4338;
            Str_delete(_t4337, &(Bool){1});
            Str *try_path = Str_concat(_t4338, import_path);
            (void)try_path;
            Str_delete(_t4338, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4339 = Str_lit("", 0ULL);
            (void)_t4339;
            U64 _t4340; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4340 = *_hp; free(_hp); }
            (void)_t4340;
            U64 _t4341 = 0;
            (void)_t4341;
            Bool _t4342; { Bool *_hp = (Bool *)Str_eq(abs, _t4339); _t4342 = *_hp; free(_hp); }
            (void)_t4342;
            Str_delete(_t4339, &(Bool){1});
            Bool _t4343; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4340}, &(U64){_t4341}); _t4343 = *_hp; free(_hp); }
            (void)_t4343;
            ;
            ;
            Bool _t4344 = Bool_and(_t4342, _t4343);
            (void)_t4344;
            ;
            ;
            if (_t4344) {
                Str *_t4300 = Str_lit("/", 1ULL);
                (void)_t4300;
                Str *_t4301 = Str_concat(lib_dir, _t4300);
                (void)_t4301;
                Str_delete(_t4300, &(Bool){1});
                try_path = Str_concat(_t4301, import_path);
                Str_delete(_t4301, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4345 = Str_lit("", 0ULL);
            (void)_t4345;
            Bool _t4346; { Bool *_hp = (Bool *)Str_eq(abs, _t4345); _t4346 = *_hp; free(_hp); }
            (void)_t4346;
            Str_delete(_t4345, &(Bool){1});
            if (_t4346) {
                Str *_t4302 = Str_lit("Str", 3ULL);
                (void)_t4302;
                U64 _t4303; { U64 *_hp = (U64 *)Str_size(); _t4303 = *_hp; free(_hp); }
                (void)_t4303;
                U64 _t4304 = 1;
                (void)_t4304;
                Array *_va72 = Array_new(_t4302, &(U64){_t4303}, &(U64){_t4304});
                (void)_va72;
                Str_delete(_t4302, &(Bool){1});
                ;
                ;
                Str *_t4305 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4305;
                Str *_t4306 = Str_concat(_t4305, import_path);
                (void)_t4306;
                Str_delete(_t4305, &(Bool){1});
                Str *_t4307 = Str_lit("' (from ", 8ULL);
                (void)_t4307;
                Str *_t4308 = Str_concat(_t4306, _t4307);
                (void)_t4308;
                Str_delete(_t4306, &(Bool){1});
                Str_delete(_t4307, &(Bool){1});
                Str *_t4309 = Str_concat(_t4308, base_dir);
                (void)_t4309;
                Str_delete(_t4308, &(Bool){1});
                Str *_t4310 = Str_lit("/)", 2ULL);
                (void)_t4310;
                U64 _t4311 = 0;
                (void)_t4311;
                Str *_t4312 = Str_concat(_t4309, _t4310);
                (void)_t4312;
                Str_delete(_t4309, &(Bool){1});
                Str_delete(_t4310, &(Bool){1});
                Array_set(_va72, &(U64){_t4311}, _t4312);
                ;
                println(_va72);
                I64 _t4313 = 1;
                (void)_t4313;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4313; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4347; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4347 = *_hp; free(_hp); }
            (void)_t4347;
            if (_t4347) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4348 = Str_clone(abs);
            (void)_t4348;
            Set_add(resolved_set, _t4348);
            Str *source = readfile(abs);
            (void)source;
            Vec *tokens = tokenize(source, abs);
            (void)tokens;
            Str_delete(source, &(Bool){1});
            Expr *sub_ast = til_parse(tokens, abs);
            (void)sub_ast;
            Vec_delete(tokens, &(Bool){1});
            Str *sub_mode = til_parse_mode();
            (void)sub_mode;
            Str_delete(sub_mode, &(Bool){1});
            Vec *sub_imports = extract_imports(sub_ast);
            (void)sub_imports;
            U64 _t4349; { U64 *_hp = (U64 *)Str_len(abs); _t4349 = *_hp; free(_hp); }
            (void)_t4349;
            U64 _t4350 = 1;
            (void)_t4350;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4349, _t4350);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4315 = 0;
                (void)_t4315;
                U8 *_t4316 = Str_get(abs, last_slash);
                (void)_t4316;
                U8 _t4317 = 47;
                (void)_t4317;
                Bool _t4318; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4315}); _t4318 = *_hp; free(_hp); }
                (void)_t4318;
                ;
                Bool _t4319; { Bool *_hp = (Bool *)U8_neq(_t4316, &(U8){_t4317}); _t4319 = *_hp; free(_hp); }
                (void)_t4319;
                ;
                Bool _wcond4314 = Bool_and(_t4318, _t4319);
                (void)_wcond4314;
                ;
                ;
                if (_wcond4314) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4320 = 1;
                (void)_t4320;
                U64 _t4321 = U64_sub(DEREF(last_slash), _t4320);
                (void)_t4321;
                ;
                *last_slash = _t4321;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4351; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4351 = *_hp; free(_hp); }
            (void)_t4351;
            U64 _t4352 = 0;
            (void)_t4352;
            Bool _t4353; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4351}, &(U64){_t4352}); _t4353 = *_hp; free(_hp); }
            (void)_t4353;
            ;
            ;
            if (_t4353) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4322 = 0;
                (void)_t4322;
                Bool _t4323; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4322}); _t4323 = *_hp; free(_hp); }
                (void)_t4323;
                ;
                if (_t4323) {
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
                U32 _t4325 = expr_nchildren(sub_ast);
                (void)_t4325;
                Bool _wcond4324; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4325}); _wcond4324 = *_hp; free(_hp); }
                (void)_wcond4324;
                ;
                if (_wcond4324) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4326 = 1;
                (void)_t4326;
                U32 _t4327 = U32_add(DEREF(k), _t4326);
                (void)_t4327;
                ;
                *k = _t4327;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t4354 = 0;
    (void)_t4354;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4354; return _r; }
}

void usage(void) {
    Str *_t4355 = Str_lit("Str", 3ULL);
    (void)_t4355;
    U64 _t4356; { U64 *_hp = (U64 *)Str_size(); _t4356 = *_hp; free(_hp); }
    (void)_t4356;
    U64 _t4357 = 1;
    (void)_t4357;
    Array *_va73 = Array_new(_t4355, &(U64){_t4356}, &(U64){_t4357});
    (void)_va73;
    Str_delete(_t4355, &(Bool){1});
    ;
    ;
    U64 _t4358 = 0;
    (void)_t4358;
    Str *_t4359 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4359;
    Array_set(_va73, &(U64){_t4358}, _t4359);
    ;
    println(_va73);
    Str *_t4360 = Str_lit("Str", 3ULL);
    (void)_t4360;
    U64 _t4361; { U64 *_hp = (U64 *)Str_size(); _t4361 = *_hp; free(_hp); }
    (void)_t4361;
    U64 _t4362 = 1;
    (void)_t4362;
    Array *_va74 = Array_new(_t4360, &(U64){_t4361}, &(U64){_t4362});
    (void)_va74;
    Str_delete(_t4360, &(Bool){1});
    ;
    ;
    U64 _t4363 = 0;
    (void)_t4363;
    Str *_t4364 = Str_lit("", 0ULL);
    (void)_t4364;
    Array_set(_va74, &(U64){_t4363}, _t4364);
    ;
    println(_va74);
    Str *_t4365 = Str_lit("Str", 3ULL);
    (void)_t4365;
    U64 _t4366; { U64 *_hp = (U64 *)Str_size(); _t4366 = *_hp; free(_hp); }
    (void)_t4366;
    U64 _t4367 = 1;
    (void)_t4367;
    Array *_va75 = Array_new(_t4365, &(U64){_t4366}, &(U64){_t4367});
    (void)_va75;
    Str_delete(_t4365, &(Bool){1});
    ;
    ;
    U64 _t4368 = 0;
    (void)_t4368;
    Str *_t4369 = Str_lit("Commands:", 9ULL);
    (void)_t4369;
    Array_set(_va75, &(U64){_t4368}, _t4369);
    ;
    println(_va75);
    Str *_t4370 = Str_lit("Str", 3ULL);
    (void)_t4370;
    U64 _t4371; { U64 *_hp = (U64 *)Str_size(); _t4371 = *_hp; free(_hp); }
    (void)_t4371;
    U64 _t4372 = 1;
    (void)_t4372;
    Array *_va76 = Array_new(_t4370, &(U64){_t4371}, &(U64){_t4372});
    (void)_va76;
    Str_delete(_t4370, &(Bool){1});
    ;
    ;
    U64 _t4373 = 0;
    (void)_t4373;
    Str *_t4374 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4374;
    Array_set(_va76, &(U64){_t4373}, _t4374);
    ;
    println(_va76);
    Str *_t4375 = Str_lit("Str", 3ULL);
    (void)_t4375;
    U64 _t4376; { U64 *_hp = (U64 *)Str_size(); _t4376 = *_hp; free(_hp); }
    (void)_t4376;
    U64 _t4377 = 1;
    (void)_t4377;
    Array *_va77 = Array_new(_t4375, &(U64){_t4376}, &(U64){_t4377});
    (void)_va77;
    Str_delete(_t4375, &(Bool){1});
    ;
    ;
    U64 _t4378 = 0;
    (void)_t4378;
    Str *_t4379 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4379;
    Array_set(_va77, &(U64){_t4378}, _t4379);
    ;
    println(_va77);
    Str *_t4380 = Str_lit("Str", 3ULL);
    (void)_t4380;
    U64 _t4381; { U64 *_hp = (U64 *)Str_size(); _t4381 = *_hp; free(_hp); }
    (void)_t4381;
    U64 _t4382 = 1;
    (void)_t4382;
    Array *_va78 = Array_new(_t4380, &(U64){_t4381}, &(U64){_t4382});
    (void)_va78;
    Str_delete(_t4380, &(Bool){1});
    ;
    ;
    U64 _t4383 = 0;
    (void)_t4383;
    Str *_t4384 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4384;
    Array_set(_va78, &(U64){_t4383}, _t4384);
    ;
    println(_va78);
    Str *_t4385 = Str_lit("Str", 3ULL);
    (void)_t4385;
    U64 _t4386; { U64 *_hp = (U64 *)Str_size(); _t4386 = *_hp; free(_hp); }
    (void)_t4386;
    U64 _t4387 = 1;
    (void)_t4387;
    Array *_va79 = Array_new(_t4385, &(U64){_t4386}, &(U64){_t4387});
    (void)_va79;
    Str_delete(_t4385, &(Bool){1});
    ;
    ;
    U64 _t4388 = 0;
    (void)_t4388;
    Str *_t4389 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4389;
    Array_set(_va79, &(U64){_t4388}, _t4389);
    ;
    println(_va79);
    Str *_t4390 = Str_lit("Str", 3ULL);
    (void)_t4390;
    U64 _t4391; { U64 *_hp = (U64 *)Str_size(); _t4391 = *_hp; free(_hp); }
    (void)_t4391;
    U64 _t4392 = 1;
    (void)_t4392;
    Array *_va80 = Array_new(_t4390, &(U64){_t4391}, &(U64){_t4392});
    (void)_va80;
    Str_delete(_t4390, &(Bool){1});
    ;
    ;
    U64 _t4393 = 0;
    (void)_t4393;
    Str *_t4394 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4394;
    Array_set(_va80, &(U64){_t4393}, _t4394);
    ;
    println(_va80);
    Str *_t4395 = Str_lit("Str", 3ULL);
    (void)_t4395;
    U64 _t4396; { U64 *_hp = (U64 *)Str_size(); _t4396 = *_hp; free(_hp); }
    (void)_t4396;
    U64 _t4397 = 1;
    (void)_t4397;
    Array *_va81 = Array_new(_t4395, &(U64){_t4396}, &(U64){_t4397});
    (void)_va81;
    Str_delete(_t4395, &(Bool){1});
    ;
    ;
    U64 _t4398 = 0;
    (void)_t4398;
    Str *_t4399 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4399;
    Array_set(_va81, &(U64){_t4398}, _t4399);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4405 = 1;
    (void)_t4405;
    e->is_core = _t4405;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4401 = expr_nchildren(e);
        (void)_t4401;
        Bool _wcond4400; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4401}); _wcond4400 = *_hp; free(_hp); }
        (void)_wcond4400;
        ;
        if (_wcond4400) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4402 = expr_get_child(e, DEREF(i));
        (void)_t4402;
        mark_core(_t4402);
        U32 _t4403 = 1;
        (void)_t4403;
        U32 _t4404 = U32_add(DEREF(i), _t4403);
        (void)_t4404;
        ;
        *i = _t4404;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4865 = malloc(sizeof(I64));
    *_t4865 = 0;
    (void)_t4865;
    _t4866 = malloc(sizeof(I64));
    *_t4866 = 1;
    (void)_t4866;
    _t4867 = malloc(sizeof(I64)); *_t4867 = I64_sub(DEREF(_t4865), DEREF(_t4866));
    (void)_t4867;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4867));
    (void)CAP_LIT;
    _t4868 = malloc(sizeof(I64));
    *_t4868 = 0;
    (void)_t4868;
    _t4869 = malloc(sizeof(I64));
    *_t4869 = 2;
    (void)_t4869;
    _t4870 = malloc(sizeof(I64)); *_t4870 = I64_sub(DEREF(_t4868), DEREF(_t4869));
    (void)_t4870;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4870));
    (void)CAP_VIEW;
    _t4871 = Str_lit("Str", 3ULL);
    (void)_t4871;
    _t4872 = Str_size();
    (void)_t4872;
    _t4873 = Str_lit("Mode", 4ULL);
    (void)_t4873;
    _t4874 = Mode_size();
    (void)_t4874;
    core_modes = Map_new(_t4871, _t4872, _t4873, _t4874);
    (void)core_modes;
    _t4875 = malloc(sizeof(Bool));
    *_t4875 = 0;
    (void)_t4875;
    _t4876 = malloc(sizeof(Bool));
    *_t4876 = 0;
    (void)_t4876;
    _t4877 = malloc(sizeof(Bool));
    *_t4877 = 0;
    (void)_t4877;
    _t4878 = malloc(sizeof(Bool));
    *_t4878 = 0;
    (void)_t4878;
    _t4879 = Str_lit("script", 6ULL);
    (void)_t4879;
    _t4880 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4880->name = *_ca; free(_ca); }
    _t4880->needs_main = DEREF(_t4875);
    _t4880->decls_only = DEREF(_t4876);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4880->auto_import = *_ca; free(_ca); }
    _t4880->is_pure = DEREF(_t4877);
    _t4880->debug_prints = DEREF(_t4878);
    (void)_t4880;
    _t4881 = malloc(sizeof(Bool));
    *_t4881 = 1;
    (void)_t4881;
    _t4882 = malloc(sizeof(Bool));
    *_t4882 = 1;
    (void)_t4882;
    _t4883 = malloc(sizeof(Bool));
    *_t4883 = 0;
    (void)_t4883;
    _t4884 = malloc(sizeof(Bool));
    *_t4884 = 0;
    (void)_t4884;
    _t4885 = Str_lit("cli", 3ULL);
    (void)_t4885;
    _t4886 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4886->name = *_ca; free(_ca); }
    _t4886->needs_main = DEREF(_t4881);
    _t4886->decls_only = DEREF(_t4882);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4886->auto_import = *_ca; free(_ca); }
    _t4886->is_pure = DEREF(_t4883);
    _t4886->debug_prints = DEREF(_t4884);
    (void)_t4886;
    _t4887 = malloc(sizeof(Bool));
    *_t4887 = 1;
    (void)_t4887;
    _t4888 = malloc(sizeof(Bool));
    *_t4888 = 1;
    (void)_t4888;
    _t4889 = malloc(sizeof(Bool));
    *_t4889 = 0;
    (void)_t4889;
    _t4890 = malloc(sizeof(Bool));
    *_t4890 = 0;
    (void)_t4890;
    _t4891 = Str_lit("gui", 3ULL);
    (void)_t4891;
    _t4892 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4892->name = *_ca; free(_ca); }
    _t4892->needs_main = DEREF(_t4887);
    _t4892->decls_only = DEREF(_t4888);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4892->auto_import = *_ca; free(_ca); }
    _t4892->is_pure = DEREF(_t4889);
    _t4892->debug_prints = DEREF(_t4890);
    (void)_t4892;
    _t4893 = malloc(sizeof(Bool));
    *_t4893 = 0;
    (void)_t4893;
    _t4894 = malloc(sizeof(Bool));
    *_t4894 = 1;
    (void)_t4894;
    _t4895 = malloc(sizeof(Bool));
    *_t4895 = 0;
    (void)_t4895;
    _t4896 = malloc(sizeof(Bool));
    *_t4896 = 0;
    (void)_t4896;
    _t4897 = Str_lit("test", 4ULL);
    (void)_t4897;
    _t4898 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4898->name = *_ca; free(_ca); }
    _t4898->needs_main = DEREF(_t4893);
    _t4898->decls_only = DEREF(_t4894);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4898->auto_import = *_ca; free(_ca); }
    _t4898->is_pure = DEREF(_t4895);
    _t4898->debug_prints = DEREF(_t4896);
    (void)_t4898;
    _t4899 = malloc(sizeof(Bool));
    *_t4899 = 0;
    (void)_t4899;
    _t4900 = malloc(sizeof(Bool));
    *_t4900 = 1;
    (void)_t4900;
    _t4901 = malloc(sizeof(Bool));
    *_t4901 = 1;
    (void)_t4901;
    _t4902 = malloc(sizeof(Bool));
    *_t4902 = 0;
    (void)_t4902;
    _t4903 = Str_lit("pure", 4ULL);
    (void)_t4903;
    _t4904 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4904->name = *_ca; free(_ca); }
    _t4904->needs_main = DEREF(_t4899);
    _t4904->decls_only = DEREF(_t4900);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4904->auto_import = *_ca; free(_ca); }
    _t4904->is_pure = DEREF(_t4901);
    _t4904->debug_prints = DEREF(_t4902);
    (void)_t4904;
    _t4905 = malloc(sizeof(Bool));
    *_t4905 = 0;
    (void)_t4905;
    _t4906 = malloc(sizeof(Bool));
    *_t4906 = 1;
    (void)_t4906;
    _t4907 = malloc(sizeof(Bool));
    *_t4907 = 1;
    (void)_t4907;
    _t4908 = malloc(sizeof(Bool));
    *_t4908 = 1;
    (void)_t4908;
    _t4909 = Str_lit("pura", 4ULL);
    (void)_t4909;
    _t4910 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4910->name = *_ca; free(_ca); }
    _t4910->needs_main = DEREF(_t4905);
    _t4910->decls_only = DEREF(_t4906);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4910->auto_import = *_ca; free(_ca); }
    _t4910->is_pure = DEREF(_t4907);
    _t4910->debug_prints = DEREF(_t4908);
    (void)_t4910;
    _t4911 = malloc(sizeof(Bool));
    *_t4911 = 0;
    (void)_t4911;
    _t4912 = malloc(sizeof(Bool));
    *_t4912 = 1;
    (void)_t4912;
    _t4913 = malloc(sizeof(Bool));
    *_t4913 = 0;
    (void)_t4913;
    _t4914 = malloc(sizeof(Bool));
    *_t4914 = 0;
    (void)_t4914;
    _t4915 = Str_lit("lib", 3ULL);
    (void)_t4915;
    _t4916 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4916->name = *_ca; free(_ca); }
    _t4916->needs_main = DEREF(_t4911);
    _t4916->decls_only = DEREF(_t4912);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4916->auto_import = *_ca; free(_ca); }
    _t4916->is_pure = DEREF(_t4913);
    _t4916->debug_prints = DEREF(_t4914);
    (void)_t4916;
    _t4917 = malloc(sizeof(Bool));
    *_t4917 = 0;
    (void)_t4917;
    _t4918 = malloc(sizeof(Bool));
    *_t4918 = 1;
    (void)_t4918;
    _t4919 = malloc(sizeof(Bool));
    *_t4919 = 0;
    (void)_t4919;
    _t4920 = malloc(sizeof(Bool));
    *_t4920 = 1;
    (void)_t4920;
    _t4921 = Str_lit("liba", 4ULL);
    (void)_t4921;
    _t4922 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4922->name = *_ca; free(_ca); }
    _t4922->needs_main = DEREF(_t4917);
    _t4922->decls_only = DEREF(_t4918);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4922->auto_import = *_ca; free(_ca); }
    _t4922->is_pure = DEREF(_t4919);
    _t4922->debug_prints = DEREF(_t4920);
    (void)_t4922;
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
    U64 _t4785; { U64 *_hp = (U64 *)Array_len(args); _t4785 = *_hp; free(_hp); }
    (void)_t4785;
    U64 _t4786 = 0;
    (void)_t4786;
    Bool _t4787 = U64_eq(_t4785, _t4786);
    (void)_t4787;
    ;
    ;
    if (_t4787) {
        usage();
        Str *_t4406 = Str_lit("Str", 3ULL);
        (void)_t4406;
        U64 _t4407; { U64 *_hp = (U64 *)Str_size(); _t4407 = *_hp; free(_hp); }
        (void)_t4407;
        U64 _t4408 = 1;
        (void)_t4408;
        Array *_va82 = Array_new(_t4406, &(U64){_t4407}, &(U64){_t4408});
        (void)_va82;
        Str_delete(_t4406, &(Bool){1});
        ;
        ;
        U64 _t4409 = 0;
        (void)_t4409;
        Str *_t4410 = Str_lit("no arguments", 12ULL);
        (void)_t4410;
        Array_set(_va82, &(U64){_t4409}, _t4410);
        ;
        Str *_t4411 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4411;
        panic(_t4411, _va82);
        Str_delete(_t4411, &(Bool){1});
    }
    ;
    U64 *_t4788 = malloc(sizeof(U64));
    *_t4788 = 0;
    (void)_t4788;
    Str *cmd_ref = Array_get(args, _t4788);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4788, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4789; { U64 *_hp = (U64 *)Array_len(args); _t4789 = *_hp; free(_hp); }
    (void)_t4789;
    U64 _t4790 = 1;
    (void)_t4790;
    Bool _t4791 = U64_eq(_t4789, _t4790);
    (void)_t4791;
    ;
    ;
    if (_t4791) {
        Str *_t4412 = Str_lit("help", 4ULL);
        (void)_t4412;
        Str *_t4413 = Str_lit("--help", 6ULL);
        (void)_t4413;
        Bool _t4414; { Bool *_hp = (Bool *)Str_eq(command, _t4412); _t4414 = *_hp; free(_hp); }
        (void)_t4414;
        Str_delete(_t4412, &(Bool){1});
        Bool _t4415; { Bool *_hp = (Bool *)Str_eq(command, _t4413); _t4415 = *_hp; free(_hp); }
        (void)_t4415;
        Str_delete(_t4413, &(Bool){1});
        Bool _t4416 = Bool_or(_t4414, _t4415);
        (void)_t4416;
        ;
        ;
        if (_t4416) {
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
            U64 _t4433; { U64 *_hp = (U64 *)Array_len(args); _t4433 = *_hp; free(_hp); }
            (void)_t4433;
            Bool _wcond4417; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4433}); _wcond4417 = *_hp; free(_hp); }
            (void)_wcond4417;
            ;
            if (_wcond4417) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4434 = Str_lit("-o", 2ULL);
            (void)_t4434;
            U64 _t4435 = 1;
            (void)_t4435;
            U64 _t4436 = U64_add(DEREF(path_idx), _t4435);
            (void)_t4436;
            ;
            U64 _t4437; { U64 *_hp = (U64 *)Array_len(args); _t4437 = *_hp; free(_hp); }
            (void)_t4437;
            Bool _t4438; { Bool *_hp = (Bool *)Str_eq(flag, _t4434); _t4438 = *_hp; free(_hp); }
            (void)_t4438;
            Str_delete(_t4434, &(Bool){1});
            Bool _t4439; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4436}, &(U64){_t4437}); _t4439 = *_hp; free(_hp); }
            (void)_t4439;
            ;
            ;
            Bool _t4440 = Bool_and(_t4438, _t4439);
            (void)_t4440;
            ;
            ;
            if (_t4440) {
                U64 _t4418 = 1;
                (void)_t4418;
                U64 *_t4419 = malloc(sizeof(U64)); *_t4419 = U64_add(DEREF(path_idx), _t4418);
                (void)_t4419;
                ;
                Str *oval = Array_get(args, _t4419);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4419, &(Bool){1});
                U64 _t4420 = 2;
                (void)_t4420;
                U64 _t4421 = U64_add(DEREF(path_idx), _t4420);
                (void)_t4421;
                ;
                *path_idx = _t4421;
                ;
            } else {
                Str *_t4426 = Str_lit("-c", 2ULL);
                (void)_t4426;
                U64 _t4427 = 1;
                (void)_t4427;
                U64 _t4428 = U64_add(DEREF(path_idx), _t4427);
                (void)_t4428;
                ;
                U64 _t4429; { U64 *_hp = (U64 *)Array_len(args); _t4429 = *_hp; free(_hp); }
                (void)_t4429;
                Bool _t4430; { Bool *_hp = (Bool *)Str_eq(flag, _t4426); _t4430 = *_hp; free(_hp); }
                (void)_t4430;
                Str_delete(_t4426, &(Bool){1});
                Bool _t4431; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4428}, &(U64){_t4429}); _t4431 = *_hp; free(_hp); }
                (void)_t4431;
                ;
                ;
                Bool _t4432 = Bool_and(_t4430, _t4431);
                (void)_t4432;
                ;
                ;
                if (_t4432) {
                    U64 _t4422 = 1;
                    (void)_t4422;
                    U64 *_t4423 = malloc(sizeof(U64)); *_t4423 = U64_add(DEREF(path_idx), _t4422);
                    (void)_t4423;
                    ;
                    Str *cval = Array_get(args, _t4423);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4423, &(Bool){1});
                    U64 _t4424 = 2;
                    (void)_t4424;
                    U64 _t4425 = U64_add(DEREF(path_idx), _t4424);
                    (void)_t4425;
                    ;
                    *path_idx = _t4425;
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
    Str *_t4792 = Str_lit("help", 4ULL);
    (void)_t4792;
    Str *_t4793 = Str_lit("--help", 6ULL);
    (void)_t4793;
    Bool _t4794; { Bool *_hp = (Bool *)Str_eq(command, _t4792); _t4794 = *_hp; free(_hp); }
    (void)_t4794;
    Str_delete(_t4792, &(Bool){1});
    Bool _t4795; { Bool *_hp = (Bool *)Str_eq(command, _t4793); _t4795 = *_hp; free(_hp); }
    (void)_t4795;
    Str_delete(_t4793, &(Bool){1});
    Bool _t4796 = Bool_or(_t4794, _t4795);
    (void)_t4796;
    ;
    ;
    if (_t4796) {
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
    Str *_t4797 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4797;
    Str *core_path = Str_concat(bin_dir, _t4797);
    (void)core_path;
    Str_delete(_t4797, &(Bool){1});
    Str *_t4798 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4798;
    Str *ext_c_path = Str_concat(bin_dir, _t4798);
    (void)ext_c_path;
    Str_delete(_t4798, &(Bool){1});
    Str *_t4799 = Str_lit("Str", 3ULL);
    (void)_t4799;
    U64 _t4800; { U64 *_hp = (U64 *)Str_size(); _t4800 = *_hp; free(_hp); }
    (void)_t4800;
    Set *resolved = Set_new(_t4799, &(U64){_t4800});
    (void)resolved;
    Str_delete(_t4799, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4801; { U64 *_hp = (U64 *)Str_len(abs_path); _t4801 = *_hp; free(_hp); }
    (void)_t4801;
    U64 _t4802 = 0;
    (void)_t4802;
    Bool _t4803; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4801}, &(U64){_t4802}); _t4803 = *_hp; free(_hp); }
    (void)_t4803;
    ;
    ;
    if (_t4803) {
        U64 _t4449; { U64 *_hp = (U64 *)Str_len(abs_path); _t4449 = *_hp; free(_hp); }
        (void)_t4449;
        U64 _t4450 = 1;
        (void)_t4450;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4449, _t4450);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4442 = 0;
            (void)_t4442;
            U8 *_t4443 = Str_get(abs_path, last_slash);
            (void)_t4443;
            U8 _t4444 = 47;
            (void)_t4444;
            Bool _t4445; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4442}); _t4445 = *_hp; free(_hp); }
            (void)_t4445;
            ;
            Bool _t4446; { Bool *_hp = (Bool *)U8_neq(_t4443, &(U8){_t4444}); _t4446 = *_hp; free(_hp); }
            (void)_t4446;
            ;
            Bool _wcond4441 = Bool_and(_t4445, _t4446);
            (void)_wcond4441;
            ;
            ;
            if (_wcond4441) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4447 = 1;
            (void)_t4447;
            U64 _t4448 = U64_sub(DEREF(last_slash), _t4447);
            (void)_t4448;
            ;
            *last_slash = _t4448;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4451 = Str_clone(abs_path);
        (void)_t4451;
        Set_add(resolved, _t4451);
    }
    ;
    Str_delete(abs_path, &(Bool){1});
    Str *core_source = readfile(core_path);
    (void)core_source;
    Vec *core_tokens = tokenize(core_source, core_path);
    (void)core_tokens;
    Str_delete(core_source, &(Bool){1});
    Expr *core_ast = til_parse(core_tokens, core_path);
    (void)core_ast;
    Vec_delete(core_tokens, &(Bool){1});
    Bool skip_core = 0;
    (void)skip_core;
    Str *core_abs = til_realpath(core_path);
    (void)core_abs;
    Str_delete(core_path, &(Bool){1});
    U64 _t4804; { U64 *_hp = (U64 *)Str_len(core_abs); _t4804 = *_hp; free(_hp); }
    (void)_t4804;
    U64 _t4805 = 0;
    (void)_t4805;
    Bool _t4806; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4804}, &(U64){_t4805}); _t4806 = *_hp; free(_hp); }
    (void)_t4806;
    ;
    ;
    if (_t4806) {
        Bool _t4453; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4453 = *_hp; free(_hp); }
        (void)_t4453;
        if (_t4453) {
            Bool _t4452 = 1;
            (void)_t4452;
            skip_core = _t4452;
            ;
        }
        ;
        Str *_t4454 = Str_clone(core_abs);
        (void)_t4454;
        Set_add(resolved, _t4454);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4807; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4807 = *_hp; free(_hp); }
    (void)_t4807;
    U64 _t4808 = 0;
    (void)_t4808;
    Bool _t4809; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4807}, &(U64){_t4808}); _t4809 = *_hp; free(_hp); }
    (void)_t4809;
    ;
    ;
    Bool _t4810 = Bool_not(skip_core);
    (void)_t4810;
    Bool _t4811 = Bool_and(_t4809, _t4810);
    (void)_t4811;
    ;
    ;
    if (_t4811) {
        Str *_t4461 = Str_lit("/src/core", 9ULL);
        (void)_t4461;
        Str *core_dir = Str_concat(bin_dir, _t4461);
        (void)core_dir;
        Str_delete(_t4461, &(Bool){1});
        Str *_t4462 = Str_lit("", 0ULL);
        (void)_t4462;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4462); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4462, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4463 = 0;
        (void)_t4463;
        Bool _t4464; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4463}); _t4464 = *_hp; free(_hp); }
        (void)_t4464;
        ;
        ;
        if (_t4464) {
            Str *_t4455 = Str_lit("Str", 3ULL);
            (void)_t4455;
            U64 _t4456; { U64 *_hp = (U64 *)Str_size(); _t4456 = *_hp; free(_hp); }
            (void)_t4456;
            U64 _t4457 = 1;
            (void)_t4457;
            Array *_va83 = Array_new(_t4455, &(U64){_t4456}, &(U64){_t4457});
            (void)_va83;
            Str_delete(_t4455, &(Bool){1});
            ;
            ;
            U64 _t4458 = 0;
            (void)_t4458;
            Str *_t4459 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4459;
            Array_set(_va83, &(U64){_t4458}, _t4459);
            ;
            Str *_t4460 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4460;
            panic(_t4460, _va83);
            Str_delete(_t4460, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(core_imports, &(Bool){1});
    Str *source = readfile(path);
    (void)source;
    Vec *tokens = tokenize(source, path);
    (void)tokens;
    Str_delete(source, &(Bool){1});
    Expr *ast = til_parse(tokens, path);
    (void)ast;
    Vec_delete(tokens, &(Bool){1});
    Vec *imports = extract_imports(ast);
    (void)imports;
    Str *mode_str = til_parse_mode();
    (void)mode_str;
    Str *_t4812 = Str_lit("script", 6ULL);
    (void)_t4812;
    Mode *cur_mode = mode_resolve(_t4812);
    (void)cur_mode;
    Str_delete(_t4812, &(Bool){1});
    U64 _t4813; { U64 *_hp = (U64 *)Str_len(mode_str); _t4813 = *_hp; free(_hp); }
    (void)_t4813;
    U64 _t4814 = 0;
    (void)_t4814;
    Bool _t4815; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4813}, &(U64){_t4814}); _t4815 = *_hp; free(_hp); }
    (void)_t4815;
    ;
    ;
    if (_t4815) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4474; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4474 = *_hp; free(_hp); }
        (void)_t4474;
        U64 _t4475 = 0;
        (void)_t4475;
        Bool _t4476 = U64_eq(_t4474, _t4475);
        (void)_t4476;
        ;
        ;
        if (_t4476) {
            Str *_t4465 = Str_lit("Str", 3ULL);
            (void)_t4465;
            U64 _t4466; { U64 *_hp = (U64 *)Str_size(); _t4466 = *_hp; free(_hp); }
            (void)_t4466;
            U64 _t4467 = 1;
            (void)_t4467;
            Array *_va84 = Array_new(_t4465, &(U64){_t4466}, &(U64){_t4467});
            (void)_va84;
            Str_delete(_t4465, &(Bool){1});
            ;
            ;
            Str *_t4468 = Str_lit("unknown mode '", 14ULL);
            (void)_t4468;
            Str *_t4469 = Str_concat(_t4468, mode_str);
            (void)_t4469;
            Str_delete(_t4468, &(Bool){1});
            Str *_t4470 = Str_lit("'", 1ULL);
            (void)_t4470;
            U64 _t4471 = 0;
            (void)_t4471;
            Str *_t4472 = Str_concat(_t4469, _t4470);
            (void)_t4472;
            Str_delete(_t4469, &(Bool){1});
            Str_delete(_t4470, &(Bool){1});
            Array_set(_va84, &(U64){_t4471}, _t4472);
            ;
            Str *_t4473 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4473;
            panic(_t4473, _va84);
            Str_delete(_t4473, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4816; { U64 *_hp = (U64 *)Vec_len(imports); _t4816 = *_hp; free(_hp); }
    (void)_t4816;
    U64 _t4817 = 0;
    (void)_t4817;
    Bool _t4818; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4816}, &(U64){_t4817}); _t4818 = *_hp; free(_hp); }
    (void)_t4818;
    ;
    ;
    if (_t4818) {
        Str *_t4483 = Str_lit("/src/lib", 8ULL);
        (void)_t4483;
        Str *lib_dir = Str_concat(bin_dir, _t4483);
        (void)lib_dir;
        Str_delete(_t4483, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4484 = 0;
        (void)_t4484;
        Bool _t4485; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4484}); _t4485 = *_hp; free(_hp); }
        (void)_t4485;
        ;
        ;
        if (_t4485) {
            Str *_t4477 = Str_lit("Str", 3ULL);
            (void)_t4477;
            U64 _t4478; { U64 *_hp = (U64 *)Str_size(); _t4478 = *_hp; free(_hp); }
            (void)_t4478;
            U64 _t4479 = 1;
            (void)_t4479;
            Array *_va85 = Array_new(_t4477, &(U64){_t4478}, &(U64){_t4479});
            (void)_va85;
            Str_delete(_t4477, &(Bool){1});
            ;
            ;
            U64 _t4480 = 0;
            (void)_t4480;
            Str *_t4481 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4481;
            Array_set(_va85, &(U64){_t4480}, _t4481);
            ;
            Str *_t4482 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4482;
            panic(_t4482, _va85);
            Str_delete(_t4482, &(Bool){1});
        }
        ;
    }
    ;
    Vec_delete(imports, &(Bool){1});
    Vec_delete(resolve_stack, &(Bool){1});
    Set_delete(resolved, &(Bool){1});
    Str_delete(user_dir, &(Bool){1});
    Vec *merged = expr_vec_new();
    (void)merged;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    Bool _t4819 = Bool_not(skip_core);
    (void)_t4819;
    ;
    if (_t4819) {
        while (1) {
            U32 _t4487 = expr_nchildren(core_ast);
            (void)_t4487;
            Bool _wcond4486; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4487}); _wcond4486 = *_hp; free(_hp); }
            (void)_wcond4486;
            ;
            if (_wcond4486) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4488 = 1;
            (void)_t4488;
            U32 _t4489 = U32_add(DEREF(i), _t4488);
            (void)_t4489;
            ;
            *i = _t4489;
            ;
        }
        U32 _t4494 = 0;
        (void)_t4494;
        *i = _t4494;
        ;
        while (1) {
            U32 _t4491 = expr_vec_count(core_import_decls);
            (void)_t4491;
            Bool _wcond4490; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4491}); _wcond4490 = *_hp; free(_hp); }
            (void)_wcond4490;
            ;
            if (_wcond4490) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4492 = 1;
            (void)_t4492;
            U32 _t4493 = U32_add(DEREF(i), _t4492);
            (void)_t4493;
            ;
            *i = _t4493;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4820; { U64 *_hp = (U64 *)Str_len(auto_import); _t4820 = *_hp; free(_hp); }
    (void)_t4820;
    U64 _t4821 = 0;
    (void)_t4821;
    Bool _t4822; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4820}, &(U64){_t4821}); _t4822 = *_hp; free(_hp); }
    (void)_t4822;
    ;
    ;
    if (_t4822) {
        Str *_t4499 = Str_lit("/src/modes/", 11ULL);
        (void)_t4499;
        Str *_t4500 = Str_concat(bin_dir, _t4499);
        (void)_t4500;
        Str_delete(_t4499, &(Bool){1});
        Str *_t4501 = Str_concat(_t4500, auto_import);
        (void)_t4501;
        Str_delete(_t4500, &(Bool){1});
        Str *_t4502 = Str_lit(".til", 4ULL);
        (void)_t4502;
        Str *mode_til_path = Str_concat(_t4501, _t4502);
        (void)mode_til_path;
        Str_delete(_t4501, &(Bool){1});
        Str_delete(_t4502, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4503 = 0;
        (void)_t4503;
        *i = _t4503;
        ;
        while (1) {
            U32 _t4496 = expr_nchildren(mode_ast);
            (void)_t4496;
            Bool _wcond4495; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4496}); _wcond4495 = *_hp; free(_hp); }
            (void)_wcond4495;
            ;
            if (_wcond4495) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4497 = 1;
            (void)_t4497;
            U32 _t4498 = U32_add(DEREF(i), _t4497);
            (void)_t4498;
            ;
            *i = _t4498;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4823 = 0;
    (void)_t4823;
    *i = _t4823;
    ;
    while (1) {
        U32 _t4505 = expr_vec_count(import_decls);
        (void)_t4505;
        Bool _wcond4504; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4505}); _wcond4504 = *_hp; free(_hp); }
        (void)_wcond4504;
        ;
        if (_wcond4504) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4506 = 1;
        (void)_t4506;
        U32 _t4507 = U32_add(DEREF(i), _t4506);
        (void)_t4507;
        ;
        *i = _t4507;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4824 = 0;
    (void)_t4824;
    *i = _t4824;
    ;
    while (1) {
        U32 _t4509 = expr_nchildren(ast);
        (void)_t4509;
        Bool _wcond4508; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4509}); _wcond4508 = *_hp; free(_hp); }
        (void)_wcond4508;
        ;
        if (_wcond4508) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4510 = 1;
        (void)_t4510;
        U32 _t4511 = U32_add(DEREF(i), _t4510);
        (void)_t4511;
        ;
        *i = _t4511;
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
    U32 _t4825 = 0;
    (void)_t4825;
    *i = _t4825;
    ;
    while (1) {
        U32 _t4527 = expr_nchildren(ast);
        (void)_t4527;
        Bool _wcond4512; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4527}); _wcond4512 = *_hp; free(_hp); }
        (void)_wcond4512;
        ;
        if (_wcond4512) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4528 = expr_get_tag(stmt);
        (void)_t4528;
        U32 _t4529 = expr_nchildren(stmt);
        (void)_t4529;
        U32 _t4530 = 2;
        (void)_t4530;
        Bool _t4531 = I32_eq(_t4528, DEREF(NODE_FCALL));
        (void)_t4531;
        ;
        Bool _t4532 = U32_eq(_t4529, _t4530);
        (void)_t4532;
        ;
        ;
        U32 *_t4533 = malloc(sizeof(U32));
        *_t4533 = 0;
        (void)_t4533;
        Expr *_t4534 = expr_get_child(stmt, DEREF(_t4533));
        (void)_t4534;
        I32 _t4535 = expr_get_tag(_t4534);
        (void)_t4535;
        U32_delete(_t4533, &(Bool){1});
        Bool _t4536 = Bool_and(_t4531, _t4532);
        (void)_t4536;
        ;
        ;
        Bool _t4537 = I32_eq(_t4535, DEREF(NODE_IDENT));
        (void)_t4537;
        ;
        U32 *_t4538 = malloc(sizeof(U32));
        *_t4538 = 1;
        (void)_t4538;
        Expr *_t4539 = expr_get_child(stmt, DEREF(_t4538));
        (void)_t4539;
        I32 _t4540 = expr_get_tag(_t4539);
        (void)_t4540;
        U32_delete(_t4538, &(Bool){1});
        Bool _t4541 = Bool_and(_t4536, _t4537);
        (void)_t4541;
        ;
        ;
        Bool _t4542 = I32_eq(_t4540, DEREF(NODE_LITERAL_STR));
        (void)_t4542;
        ;
        Bool _t4543 = Bool_and(_t4541, _t4542);
        (void)_t4543;
        ;
        ;
        if (_t4543) {
            U32 *_t4521 = malloc(sizeof(U32));
            *_t4521 = 0;
            (void)_t4521;
            Expr *_t4522 = expr_get_child(stmt, DEREF(_t4521));
            (void)_t4522;
            Str *fname = expr_get_str_val(_t4522);
            (void)fname;
            U32 *_t4523 = malloc(sizeof(U32));
            *_t4523 = 1;
            (void)_t4523;
            Expr *_t4524 = expr_get_child(stmt, DEREF(_t4523));
            (void)_t4524;
            Str *arg = expr_get_str_val(_t4524);
            (void)arg;
            Str *_t4525 = Str_lit("link", 4ULL);
            (void)_t4525;
            Bool _t4526; { Bool *_hp = (Bool *)Str_eq(fname, _t4525); _t4526 = *_hp; free(_hp); }
            (void)_t4526;
            Str_delete(_t4525, &(Bool){1});
            if (_t4526) {
                Str *_t4513 = Str_lit(" -l", 3ULL);
                (void)_t4513;
                Str *_t4514 = Str_concat(link_flags, _t4513);
                (void)_t4514;
                Str_delete(_t4513, &(Bool){1});
                link_flags = Str_concat(_t4514, arg);
                Str_delete(_t4514, &(Bool){1});
            } else {
                Str *_t4519 = Str_lit("link_c", 6ULL);
                (void)_t4519;
                Bool _t4520; { Bool *_hp = (Bool *)Str_eq(fname, _t4519); _t4520 = *_hp; free(_hp); }
                (void)_t4520;
                Str_delete(_t4519, &(Bool){1});
                if (_t4520) {
                    U64 _t4516; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4516 = *_hp; free(_hp); }
                    (void)_t4516;
                    U64 _t4517 = 0;
                    (void)_t4517;
                    Bool _t4518; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4516}, &(U64){_t4517}); _t4518 = *_hp; free(_hp); }
                    (void)_t4518;
                    ;
                    ;
                    if (_t4518) {
                        Str *_t4515 = Str_lit(" ", 1ULL);
                        (void)_t4515;
                        link_c_paths = Str_concat(link_c_paths, _t4515);
                        Str_delete(_t4515, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4521, &(Bool){1});
            U32_delete(_t4523, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4544 = 1;
        (void)_t4544;
        U32 _t4545 = U32_add(DEREF(i), _t4544);
        (void)_t4545;
        ;
        *i = _t4545;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4826 = init_declarations(ast, scope);
    (void)_t4826;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4827 = 0;
    (void)_t4827;
    Bool _t4828; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4827}); _t4828 = *_hp; free(_hp); }
    (void)_t4828;
    ;
    if (_t4828) {
        Str *_t4546 = Str_lit("Str", 3ULL);
        (void)_t4546;
        U64 _t4547; { U64 *_hp = (U64 *)Str_size(); _t4547 = *_hp; free(_hp); }
        (void)_t4547;
        U64 _t4548 = 1;
        (void)_t4548;
        Array *_va86 = Array_new(_t4546, &(U64){_t4547}, &(U64){_t4548});
        (void)_va86;
        Str_delete(_t4546, &(Bool){1});
        ;
        ;
        Str *_t4549 = I32_to_str(&(I32){type_errors});
        (void)_t4549;
        Str *_t4550 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4550;
        U64 _t4551 = 0;
        (void)_t4551;
        Str *_t4552 = Str_concat(_t4549, _t4550);
        (void)_t4552;
        Str_delete(_t4549, &(Bool){1});
        Str_delete(_t4550, &(Bool){1});
        Array_set(_va86, &(U64){_t4551}, _t4552);
        ;
        Str *_t4553 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4553;
        panic(_t4553, _va86);
        Str_delete(_t4553, &(Bool){1});
    }
    ;
    ;
    Str *_t4829 = Str_lit("test", 4ULL);
    (void)_t4829;
    Str *_t4830 = Str_lit("test", 4ULL);
    (void)_t4830;
    Bool _t4831; { Bool *_hp = (Bool *)Str_eq(command, _t4829); _t4831 = *_hp; free(_hp); }
    (void)_t4831;
    Str_delete(_t4829, &(Bool){1});
    Bool _t4832; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4830); _t4832 = *_hp; free(_hp); }
    (void)_t4832;
    Str_delete(_t4830, &(Bool){1});
    Str *_t4833 = Str_lit("pure", 4ULL);
    (void)_t4833;
    Bool _t4834 = Bool_or(_t4831, _t4832);
    (void)_t4834;
    ;
    ;
    Bool _t4835; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4833); _t4835 = *_hp; free(_hp); }
    (void)_t4835;
    Str_delete(_t4833, &(Bool){1});
    Str *_t4836 = Str_lit("pura", 4ULL);
    (void)_t4836;
    Bool _t4837 = Bool_or(_t4834, _t4835);
    (void)_t4837;
    ;
    ;
    Bool _t4838; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4836); _t4838 = *_hp; free(_hp); }
    (void)_t4838;
    Str_delete(_t4836, &(Bool){1});
    Bool run_tests = Bool_or(_t4837, _t4838);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4839 = Str_lit("translate", 9ULL);
    (void)_t4839;
    Str *_t4840 = Str_lit("build", 5ULL);
    (void)_t4840;
    Bool _t4841; { Bool *_hp = (Bool *)Str_eq(command, _t4839); _t4841 = *_hp; free(_hp); }
    (void)_t4841;
    Str_delete(_t4839, &(Bool){1});
    Bool _t4842; { Bool *_hp = (Bool *)Str_eq(command, _t4840); _t4842 = *_hp; free(_hp); }
    (void)_t4842;
    Str_delete(_t4840, &(Bool){1});
    Bool _t4843; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4843 = *_hp; free(_hp); }
    (void)_t4843;
    Bool _t4844 = Bool_or(_t4841, _t4842);
    (void)_t4844;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4843, _t4844);
    (void)is_lib_target;
    ;
    ;
    U64 _t4845; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4845 = *_hp; free(_hp); }
    (void)_t4845;
    U64 _t4846 = 0;
    (void)_t4846;
    Bool _t4847 = Bool_not(is_lib_target);
    (void)_t4847;
    ;
    Bool _t4848 = U64_eq(_t4845, _t4846);
    (void)_t4848;
    ;
    ;
    Bool _t4849 = Bool_and(_t4847, _t4848);
    (void)_t4849;
    ;
    ;
    if (_t4849) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4850; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4850 = *_hp; free(_hp); }
    (void)_t4850;
    U64 _t4851 = 0;
    (void)_t4851;
    Bool _t4852; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4850}, &(U64){_t4851}); _t4852 = *_hp; free(_hp); }
    (void)_t4852;
    ;
    ;
    if (_t4852) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4853 = Str_lit("Str", 3ULL);
    (void)_t4853;
    U64 _t4854; { U64 *_hp = (U64 *)Str_size(); _t4854 = *_hp; free(_hp); }
    (void)_t4854;
    Vec *user_argv = Vec_new(_t4853, &(U64){_t4854});
    (void)user_argv;
    Str_delete(_t4853, &(Bool){1});
    ;
    U64 _t4855 = 1;
    (void)_t4855;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4855);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4570; { U64 *_hp = (U64 *)Array_len(args); _t4570 = *_hp; free(_hp); }
        (void)_t4570;
        Bool _wcond4554; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4570}); _wcond4554 = *_hp; free(_hp); }
        (void)_wcond4554;
        ;
        if (_wcond4554) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4571 = Str_lit("-l", 2ULL);
        (void)_t4571;
        Bool _t4572; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4571); _t4572 = *_hp; free(_hp); }
        (void)_t4572;
        Str_delete(_t4571, &(Bool){1});
        if (_t4572) {
            U64 _t4557 = 2;
            (void)_t4557;
            U64 _t4558; { U64 *_hp = (U64 *)Str_len(arg); _t4558 = *_hp; free(_hp); }
            (void)_t4558;
            Str *lib = Str_substr(arg, &(U64){_t4557}, &(U64){_t4558});
            (void)lib;
            ;
            ;
            U64 _t4559; { U64 *_hp = (U64 *)Str_len(lib); _t4559 = *_hp; free(_hp); }
            (void)_t4559;
            U64 _t4560 = 0;
            (void)_t4560;
            U64 _t4561 = 1;
            (void)_t4561;
            U64 _t4562 = U64_add(DEREF(ai), _t4561);
            (void)_t4562;
            ;
            U64 _t4563; { U64 *_hp = (U64 *)Array_len(args); _t4563 = *_hp; free(_hp); }
            (void)_t4563;
            Bool _t4564 = U64_eq(_t4559, _t4560);
            (void)_t4564;
            ;
            ;
            Bool _t4565; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4562}, &(U64){_t4563}); _t4565 = *_hp; free(_hp); }
            (void)_t4565;
            ;
            ;
            Bool _t4566 = Bool_and(_t4564, _t4565);
            (void)_t4566;
            ;
            ;
            if (_t4566) {
                U64 _t4555 = 1;
                (void)_t4555;
                U64 _t4556 = U64_add(DEREF(ai), _t4555);
                (void)_t4556;
                ;
                *ai = _t4556;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4567 = Str_lit(" -l", 3ULL);
            (void)_t4567;
            Str *_t4568 = Str_concat(link_flags, _t4567);
            (void)_t4568;
            Str_delete(_t4567, &(Bool){1});
            link_flags = Str_concat(_t4568, lib);
            Str_delete(_t4568, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4569 = Str_clone(arg);
            (void)_t4569;
            Vec_push(user_argv, _t4569);
        }
        ;
        U64 _t4573 = 1;
        (void)_t4573;
        U64 _t4574 = U64_add(DEREF(ai), _t4573);
        (void)_t4574;
        ;
        *ai = _t4574;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4856; { U64 *_hp = (U64 *)Str_len(link_flags); _t4856 = *_hp; free(_hp); }
    (void)_t4856;
    U64 _t4857 = 0;
    (void)_t4857;
    Bool _t4858; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4856}, &(U64){_t4857}); _t4858 = *_hp; free(_hp); }
    (void)_t4858;
    ;
    ;
    if (_t4858) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4859 = Str_lit("interpret", 9ULL);
    (void)_t4859;
    Str *_t4860 = Str_lit("test", 4ULL);
    (void)_t4860;
    Bool _t4861; { Bool *_hp = (Bool *)Str_eq(command, _t4859); _t4861 = *_hp; free(_hp); }
    (void)_t4861;
    Str_delete(_t4859, &(Bool){1});
    Bool _t4862; { Bool *_hp = (Bool *)Str_eq(command, _t4860); _t4862 = *_hp; free(_hp); }
    (void)_t4862;
    Str_delete(_t4860, &(Bool){1});
    Bool _t4863 = Bool_or(_t4861, _t4862);
    (void)_t4863;
    ;
    ;
    if (_t4863) {
        Str *_t4581 = Str_lit("interpret", 9ULL);
        (void)_t4581;
        Bool _t4582; { Bool *_hp = (Bool *)Str_eq(command, _t4581); _t4582 = *_hp; free(_hp); }
        (void)_t4582;
        Str_delete(_t4581, &(Bool){1});
        Bool _t4583 = Bool_and(is_lib_mode, _t4582);
        (void)_t4583;
        ;
        if (_t4583) {
            Str *_t4575 = Str_lit("Str", 3ULL);
            (void)_t4575;
            U64 _t4576; { U64 *_hp = (U64 *)Str_size(); _t4576 = *_hp; free(_hp); }
            (void)_t4576;
            U64 _t4577 = 1;
            (void)_t4577;
            Array *_va87 = Array_new(_t4575, &(U64){_t4576}, &(U64){_t4577});
            (void)_va87;
            Str_delete(_t4575, &(Bool){1});
            ;
            ;
            U64 _t4578 = 0;
            (void)_t4578;
            Str *_t4579 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4579;
            Array_set(_va87, &(U64){_t4578}, _t4579);
            ;
            Str *_t4580 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4580;
            panic(_t4580, _va87);
            Str_delete(_t4580, &(Bool){1});
        }
        ;
        I32 _t4584 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4584;
        result = _t4584;
        ;
    } else {
        Str *_t4777 = Str_lit("translate", 9ULL);
        (void)_t4777;
        Str *_t4778 = Str_lit("build", 5ULL);
        (void)_t4778;
        Bool _t4779; { Bool *_hp = (Bool *)Str_eq(command, _t4777); _t4779 = *_hp; free(_hp); }
        (void)_t4779;
        Str_delete(_t4777, &(Bool){1});
        Bool _t4780; { Bool *_hp = (Bool *)Str_eq(command, _t4778); _t4780 = *_hp; free(_hp); }
        (void)_t4780;
        Str_delete(_t4778, &(Bool){1});
        Str *_t4781 = Str_lit("run", 3ULL);
        (void)_t4781;
        Bool _t4782 = Bool_or(_t4779, _t4780);
        (void)_t4782;
        ;
        ;
        Bool _t4783; { Bool *_hp = (Bool *)Str_eq(command, _t4781); _t4783 = *_hp; free(_hp); }
        (void)_t4783;
        Str_delete(_t4781, &(Bool){1});
        Bool _t4784 = Bool_or(_t4782, _t4783);
        (void)_t4784;
        ;
        ;
        if (_t4784) {
            Str *_t4710 = Str_lit("run", 3ULL);
            (void)_t4710;
            Bool _t4711; { Bool *_hp = (Bool *)Str_eq(command, _t4710); _t4711 = *_hp; free(_hp); }
            (void)_t4711;
            Str_delete(_t4710, &(Bool){1});
            Bool _t4712 = Bool_and(is_lib_mode, _t4711);
            (void)_t4712;
            ;
            if (_t4712) {
                Str *_t4585 = Str_lit("Str", 3ULL);
                (void)_t4585;
                U64 _t4586; { U64 *_hp = (U64 *)Str_size(); _t4586 = *_hp; free(_hp); }
                (void)_t4586;
                U64 _t4587 = 1;
                (void)_t4587;
                Array *_va88 = Array_new(_t4585, &(U64){_t4586}, &(U64){_t4587});
                (void)_va88;
                Str_delete(_t4585, &(Bool){1});
                ;
                ;
                U64 _t4588 = 0;
                (void)_t4588;
                Str *_t4589 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4589;
                Array_set(_va88, &(U64){_t4588}, _t4589);
                ;
                Str *_t4590 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4590;
                panic(_t4590, _va88);
                Str_delete(_t4590, &(Bool){1});
            }
            ;
            Str *_t4713 = Str_lit("/", 1ULL);
            (void)_t4713;
            I64 *last_slash = Str_rfind(path, _t4713);
            (void)last_slash;
            Str_delete(_t4713, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4714 = 0;
            (void)_t4714;
            Bool _t4715; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4714}); _t4715 = *_hp; free(_hp); }
            (void)_t4715;
            ;
            if (_t4715) {
                I64 _t4591 = 1;
                (void)_t4591;
                I64 _t4592 = I64_add(DEREF(last_slash), _t4591);
                (void)_t4592;
                ;
                U64 _t4593; { U64 *_hp = (U64 *)Str_len(path); _t4593 = *_hp; free(_hp); }
                (void)_t4593;
                U64 _t4594 = I64_to_u64(DEREF(last_slash));
                (void)_t4594;
                U64 _t4595 = U64_sub(_t4593, _t4594);
                (void)_t4595;
                ;
                ;
                U64 _t4596 = 1;
                (void)_t4596;
                U64 _t4597 = I64_to_u64(_t4592);
                (void)_t4597;
                ;
                U64 _t4598 = U64_sub(_t4595, _t4596);
                (void)_t4598;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4597}, &(U64){_t4598});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4716 = Str_lit(".til", 4ULL);
            (void)_t4716;
            Bool _t4717; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4716); _t4717 = *_hp; free(_hp); }
            (void)_t4717;
            Str_delete(_t4716, &(Bool){1});
            if (_t4717) {
                U64 _t4599 = 4;
                (void)_t4599;
                U64 _t4600 = U64_sub(name_len, _t4599);
                (void)_t4600;
                ;
                name_len = _t4600;
                ;
            }
            ;
            U64 _t4718 = 0;
            (void)_t4718;
            Str *name = Str_substr(basename, &(U64){_t4718}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4719 = Str_lit("gen/til/", 8ULL);
            (void)_t4719;
            Str *_t4720 = Str_concat(_t4719, name);
            (void)_t4720;
            Str_delete(_t4719, &(Bool){1});
            Str *_t4721 = Str_lit(".c", 2ULL);
            (void)_t4721;
            Str *c_path = Str_concat(_t4720, _t4721);
            (void)c_path;
            Str_delete(_t4720, &(Bool){1});
            Str_delete(_t4721, &(Bool){1});
            U64 _t4722; { U64 *_hp = (U64 *)Str_len(custom_c); _t4722 = *_hp; free(_hp); }
            (void)_t4722;
            U64 _t4723 = 0;
            (void)_t4723;
            Bool _t4724; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4722}, &(U64){_t4723}); _t4724 = *_hp; free(_hp); }
            (void)_t4724;
            ;
            ;
            if (_t4724) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4725 = Str_lit("bin/til/", 8ULL);
            (void)_t4725;
            Str *bin_path = Str_concat(_t4725, name);
            (void)bin_path;
            Str_delete(_t4725, &(Bool){1});
            U64 _t4726; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4726 = *_hp; free(_hp); }
            (void)_t4726;
            U64 _t4727 = 0;
            (void)_t4727;
            Bool _t4728; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4726}, &(U64){_t4727}); _t4728 = *_hp; free(_hp); }
            (void)_t4728;
            ;
            ;
            if (_t4728) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4729 = Str_lit("run", 3ULL);
            (void)_t4729;
            Bool _t4730; { Bool *_hp = (Bool *)Str_eq(command, _t4729); _t4730 = *_hp; free(_hp); }
            (void)_t4730;
            Str_delete(_t4729, &(Bool){1});
            Bool _t4731; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4731 = *_hp; free(_hp); }
            (void)_t4731;
            Bool _t4732 = Bool_not(_t4730);
            (void)_t4732;
            ;
            Bool do_lib = Bool_and(_t4731, _t4732);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4601 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4601;
                I32 _t4602 = til_system(_t4601);
                (void)_t4602;
                Str_delete(_t4601, &(Bool){1});
                ;
            } else {
                Str *_t4607 = Str_lit("/", 1ULL);
                (void)_t4607;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4607); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4607, &(Bool){1});
                Str *_t4608 = Str_lit("/", 1ULL);
                (void)_t4608;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4608); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4608, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4609 = 0;
                (void)_t4609;
                Bool _t4610; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4609}); _t4610 = *_hp; free(_hp); }
                (void)_t4610;
                ;
                if (_t4610) {
                    U64 _t4603 = 0;
                    (void)_t4603;
                    U64 _t4604 = I64_to_u64(cp_slash);
                    (void)_t4604;
                    cp_dir = Str_substr(c_path, &(U64){_t4603}, &(U64){_t4604});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4611 = 0;
                (void)_t4611;
                Bool _t4612; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4611}); _t4612 = *_hp; free(_hp); }
                (void)_t4612;
                ;
                if (_t4612) {
                    U64 _t4605 = 0;
                    (void)_t4605;
                    U64 _t4606 = I64_to_u64(bp_slash);
                    (void)_t4606;
                    bp_dir = Str_substr(bin_path, &(U64){_t4605}, &(U64){_t4606});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4613 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4613;
                Str *_t4614 = Str_concat(_t4613, cp_dir);
                (void)_t4614;
                Str_delete(_t4613, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4615 = Str_lit(" ", 1ULL);
                (void)_t4615;
                Str *_t4616 = Str_concat(_t4614, _t4615);
                (void)_t4616;
                Str_delete(_t4614, &(Bool){1});
                Str_delete(_t4615, &(Bool){1});
                Str *_t4617 = Str_concat(_t4616, bp_dir);
                (void)_t4617;
                Str_delete(_t4616, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4618 = til_system(_t4617);
                (void)_t4618;
                Str_delete(_t4617, &(Bool){1});
                ;
            }
            I32 _t4733 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4733;
            result = _t4733;
            ;
            I32 _t4734 = 0;
            (void)_t4734;
            Bool _t4735 = I32_eq(result, _t4734);
            (void)_t4735;
            ;
            Bool _t4736 = Bool_and(_t4735, do_lib);
            (void)_t4736;
            ;
            if (_t4736) {
                Str *_t4675 = Str_lit("gen/til/", 8ULL);
                (void)_t4675;
                Str *_t4676 = Str_concat(_t4675, name);
                (void)_t4676;
                Str_delete(_t4675, &(Bool){1});
                Str *_t4677 = Str_lit(".h", 2ULL);
                (void)_t4677;
                Str *h_path = Str_concat(_t4676, _t4677);
                (void)h_path;
                Str_delete(_t4676, &(Bool){1});
                Str_delete(_t4677, &(Bool){1});
                Str *_t4678 = Str_lit("gen/til/", 8ULL);
                (void)_t4678;
                Str *_t4679 = Str_concat(_t4678, name);
                (void)_t4679;
                Str_delete(_t4678, &(Bool){1});
                Str *_t4680 = Str_lit(".til", 4ULL);
                (void)_t4680;
                Str *til_path = Str_concat(_t4679, _t4680);
                (void)til_path;
                Str_delete(_t4679, &(Bool){1});
                Str_delete(_t4680, &(Bool){1});
                I32 _t4681 = build_header(ast, h_path);
                (void)_t4681;
                result = _t4681;
                ;
                I32 _t4682 = 0;
                (void)_t4682;
                Bool _t4683 = I32_eq(result, _t4682);
                (void)_t4683;
                ;
                if (_t4683) {
                    I32 _t4619 = build_til_binding(ast, til_path, name);
                    (void)_t4619;
                    result = _t4619;
                    ;
                }
                ;
                I32 _t4684 = 0;
                (void)_t4684;
                Str *_t4685 = Str_lit("translate", 9ULL);
                (void)_t4685;
                Bool _t4686 = I32_eq(result, _t4684);
                (void)_t4686;
                ;
                Bool _t4687; { Bool *_hp = (Bool *)Str_eq(command, _t4685); _t4687 = *_hp; free(_hp); }
                (void)_t4687;
                Str_delete(_t4685, &(Bool){1});
                Bool _t4688 = Bool_and(_t4686, _t4687);
                (void)_t4688;
                ;
                ;
                if (_t4688) {
                    Str *_t4620 = Str_lit("Str", 3ULL);
                    (void)_t4620;
                    U64 _t4621; { U64 *_hp = (U64 *)Str_size(); _t4621 = *_hp; free(_hp); }
                    (void)_t4621;
                    U64 _t4622 = 1;
                    (void)_t4622;
                    Array *_va89 = Array_new(_t4620, &(U64){_t4621}, &(U64){_t4622});
                    (void)_va89;
                    Str_delete(_t4620, &(Bool){1});
                    ;
                    ;
                    Str *_t4623 = Str_lit("Generated: ", 11ULL);
                    (void)_t4623;
                    U64 _t4624 = 0;
                    (void)_t4624;
                    Str *_t4625 = Str_concat(_t4623, c_path);
                    (void)_t4625;
                    Str_delete(_t4623, &(Bool){1});
                    Array_set(_va89, &(U64){_t4624}, _t4625);
                    ;
                    println(_va89);
                    Str *_t4626 = Str_lit("Str", 3ULL);
                    (void)_t4626;
                    U64 _t4627; { U64 *_hp = (U64 *)Str_size(); _t4627 = *_hp; free(_hp); }
                    (void)_t4627;
                    U64 _t4628 = 1;
                    (void)_t4628;
                    Array *_va90 = Array_new(_t4626, &(U64){_t4627}, &(U64){_t4628});
                    (void)_va90;
                    Str_delete(_t4626, &(Bool){1});
                    ;
                    ;
                    Str *_t4629 = Str_lit("Generated: ", 11ULL);
                    (void)_t4629;
                    U64 _t4630 = 0;
                    (void)_t4630;
                    Str *_t4631 = Str_concat(_t4629, h_path);
                    (void)_t4631;
                    Str_delete(_t4629, &(Bool){1});
                    Array_set(_va90, &(U64){_t4630}, _t4631);
                    ;
                    println(_va90);
                    Str *_t4632 = Str_lit("Str", 3ULL);
                    (void)_t4632;
                    U64 _t4633; { U64 *_hp = (U64 *)Str_size(); _t4633 = *_hp; free(_hp); }
                    (void)_t4633;
                    U64 _t4634 = 1;
                    (void)_t4634;
                    Array *_va91 = Array_new(_t4632, &(U64){_t4633}, &(U64){_t4634});
                    (void)_va91;
                    Str_delete(_t4632, &(Bool){1});
                    ;
                    ;
                    Str *_t4635 = Str_lit("Generated: ", 11ULL);
                    (void)_t4635;
                    U64 _t4636 = 0;
                    (void)_t4636;
                    Str *_t4637 = Str_concat(_t4635, til_path);
                    (void)_t4637;
                    Str_delete(_t4635, &(Bool){1});
                    Array_set(_va91, &(U64){_t4636}, _t4637);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4689 = 0;
                (void)_t4689;
                Str *_t4690 = Str_lit("build", 5ULL);
                (void)_t4690;
                Bool _t4691 = I32_eq(result, _t4689);
                (void)_t4691;
                ;
                Bool _t4692; { Bool *_hp = (Bool *)Str_eq(command, _t4690); _t4692 = *_hp; free(_hp); }
                (void)_t4692;
                Str_delete(_t4690, &(Bool){1});
                Bool _t4693 = Bool_and(_t4691, _t4692);
                (void)_t4693;
                ;
                ;
                if (_t4693) {
                    I32 _t4672 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4672;
                    result = _t4672;
                    ;
                    I32 _t4673 = 0;
                    (void)_t4673;
                    Bool _t4674 = I32_eq(result, _t4673);
                    (void)_t4674;
                    ;
                    if (_t4674) {
                        Str *_t4638 = Str_lit("Str", 3ULL);
                        (void)_t4638;
                        U64 _t4639; { U64 *_hp = (U64 *)Str_size(); _t4639 = *_hp; free(_hp); }
                        (void)_t4639;
                        U64 _t4640 = 1;
                        (void)_t4640;
                        Array *_va92 = Array_new(_t4638, &(U64){_t4639}, &(U64){_t4640});
                        (void)_va92;
                        Str_delete(_t4638, &(Bool){1});
                        ;
                        ;
                        Str *_t4641 = Str_lit("Generated: ", 11ULL);
                        (void)_t4641;
                        U64 _t4642 = 0;
                        (void)_t4642;
                        Str *_t4643 = Str_concat(_t4641, c_path);
                        (void)_t4643;
                        Str_delete(_t4641, &(Bool){1});
                        Array_set(_va92, &(U64){_t4642}, _t4643);
                        ;
                        println(_va92);
                        Str *_t4644 = Str_lit("Str", 3ULL);
                        (void)_t4644;
                        U64 _t4645; { U64 *_hp = (U64 *)Str_size(); _t4645 = *_hp; free(_hp); }
                        (void)_t4645;
                        U64 _t4646 = 1;
                        (void)_t4646;
                        Array *_va93 = Array_new(_t4644, &(U64){_t4645}, &(U64){_t4646});
                        (void)_va93;
                        Str_delete(_t4644, &(Bool){1});
                        ;
                        ;
                        Str *_t4647 = Str_lit("Generated: ", 11ULL);
                        (void)_t4647;
                        U64 _t4648 = 0;
                        (void)_t4648;
                        Str *_t4649 = Str_concat(_t4647, h_path);
                        (void)_t4649;
                        Str_delete(_t4647, &(Bool){1});
                        Array_set(_va93, &(U64){_t4648}, _t4649);
                        ;
                        println(_va93);
                        Str *_t4650 = Str_lit("Str", 3ULL);
                        (void)_t4650;
                        U64 _t4651; { U64 *_hp = (U64 *)Str_size(); _t4651 = *_hp; free(_hp); }
                        (void)_t4651;
                        U64 _t4652 = 1;
                        (void)_t4652;
                        Array *_va94 = Array_new(_t4650, &(U64){_t4651}, &(U64){_t4652});
                        (void)_va94;
                        Str_delete(_t4650, &(Bool){1});
                        ;
                        ;
                        Str *_t4653 = Str_lit("Generated: ", 11ULL);
                        (void)_t4653;
                        U64 _t4654 = 0;
                        (void)_t4654;
                        Str *_t4655 = Str_concat(_t4653, til_path);
                        (void)_t4655;
                        Str_delete(_t4653, &(Bool){1});
                        Array_set(_va94, &(U64){_t4654}, _t4655);
                        ;
                        println(_va94);
                        Str *_t4656 = Str_lit("Str", 3ULL);
                        (void)_t4656;
                        U64 _t4657; { U64 *_hp = (U64 *)Str_size(); _t4657 = *_hp; free(_hp); }
                        (void)_t4657;
                        U64 _t4658 = 1;
                        (void)_t4658;
                        Array *_va95 = Array_new(_t4656, &(U64){_t4657}, &(U64){_t4658});
                        (void)_va95;
                        Str_delete(_t4656, &(Bool){1});
                        ;
                        ;
                        Str *_t4659 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4659;
                        Str *_t4660 = Str_concat(_t4659, name);
                        (void)_t4660;
                        Str_delete(_t4659, &(Bool){1});
                        Str *_t4661 = Str_lit(".so", 3ULL);
                        (void)_t4661;
                        U64 _t4662 = 0;
                        (void)_t4662;
                        Str *_t4663 = Str_concat(_t4660, _t4661);
                        (void)_t4663;
                        Str_delete(_t4660, &(Bool){1});
                        Str_delete(_t4661, &(Bool){1});
                        Array_set(_va95, &(U64){_t4662}, _t4663);
                        ;
                        println(_va95);
                        Str *_t4664 = Str_lit("Str", 3ULL);
                        (void)_t4664;
                        U64 _t4665; { U64 *_hp = (U64 *)Str_size(); _t4665 = *_hp; free(_hp); }
                        (void)_t4665;
                        U64 _t4666 = 1;
                        (void)_t4666;
                        Array *_va96 = Array_new(_t4664, &(U64){_t4665}, &(U64){_t4666});
                        (void)_va96;
                        Str_delete(_t4664, &(Bool){1});
                        ;
                        ;
                        Str *_t4667 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4667;
                        Str *_t4668 = Str_concat(_t4667, name);
                        (void)_t4668;
                        Str_delete(_t4667, &(Bool){1});
                        Str *_t4669 = Str_lit(".a", 2ULL);
                        (void)_t4669;
                        U64 _t4670 = 0;
                        (void)_t4670;
                        Str *_t4671 = Str_concat(_t4668, _t4669);
                        (void)_t4671;
                        Str_delete(_t4668, &(Bool){1});
                        Str_delete(_t4669, &(Bool){1});
                        Array_set(_va96, &(U64){_t4670}, _t4671);
                        ;
                        println(_va96);
                    }
                    ;
                }
                ;
                Str_delete(h_path, &(Bool){1});
                Str_delete(til_path, &(Bool){1});
            }
            ;
            Str_delete(name, &(Bool){1});
            I32 _t4737 = 0;
            (void)_t4737;
            Bool _t4738 = I32_eq(result, _t4737);
            (void)_t4738;
            ;
            Bool _t4739 = Bool_not(do_lib);
            (void)_t4739;
            Str *_t4740 = Str_lit("translate", 9ULL);
            (void)_t4740;
            Bool _t4741 = Bool_and(_t4738, _t4739);
            (void)_t4741;
            ;
            ;
            Bool _t4742; { Bool *_hp = (Bool *)Str_eq(command, _t4740); _t4742 = *_hp; free(_hp); }
            (void)_t4742;
            Str_delete(_t4740, &(Bool){1});
            Bool _t4743 = Bool_and(_t4741, _t4742);
            (void)_t4743;
            ;
            ;
            if (_t4743) {
                Str *_t4694 = Str_lit("Str", 3ULL);
                (void)_t4694;
                U64 _t4695; { U64 *_hp = (U64 *)Str_size(); _t4695 = *_hp; free(_hp); }
                (void)_t4695;
                U64 _t4696 = 1;
                (void)_t4696;
                Array *_va97 = Array_new(_t4694, &(U64){_t4695}, &(U64){_t4696});
                (void)_va97;
                Str_delete(_t4694, &(Bool){1});
                ;
                ;
                Str *_t4697 = Str_lit("Generated: ", 11ULL);
                (void)_t4697;
                U64 _t4698 = 0;
                (void)_t4698;
                Str *_t4699 = Str_concat(_t4697, c_path);
                (void)_t4699;
                Str_delete(_t4697, &(Bool){1});
                Array_set(_va97, &(U64){_t4698}, _t4699);
                ;
                println(_va97);
            }
            ;
            I32 _t4744 = 0;
            (void)_t4744;
            Bool _t4745 = I32_eq(result, _t4744);
            (void)_t4745;
            ;
            Bool _t4746 = Bool_not(do_lib);
            (void)_t4746;
            Str *_t4747 = Str_lit("translate", 9ULL);
            (void)_t4747;
            Bool _t4748; { Bool *_hp = (Bool *)Str_eq(command, _t4747); _t4748 = *_hp; free(_hp); }
            (void)_t4748;
            Str_delete(_t4747, &(Bool){1});
            Bool _t4749 = Bool_and(_t4745, _t4746);
            (void)_t4749;
            ;
            ;
            Bool _t4750 = Bool_not(_t4748);
            (void)_t4750;
            ;
            Bool _t4751 = Bool_and(_t4749, _t4750);
            (void)_t4751;
            ;
            ;
            if (_t4751) {
                I32 _t4700 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4700;
                result = _t4700;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4752 = 0;
            (void)_t4752;
            Bool _t4753 = I32_eq(result, _t4752);
            (void)_t4753;
            ;
            Bool _t4754 = Bool_not(do_lib);
            (void)_t4754;
            ;
            Str *_t4755 = Str_lit("run", 3ULL);
            (void)_t4755;
            Bool _t4756 = Bool_and(_t4753, _t4754);
            (void)_t4756;
            ;
            ;
            Bool _t4757; { Bool *_hp = (Bool *)Str_eq(command, _t4755); _t4757 = *_hp; free(_hp); }
            (void)_t4757;
            Str_delete(_t4755, &(Bool){1});
            Bool _t4758 = Bool_and(_t4756, _t4757);
            (void)_t4758;
            ;
            ;
            if (_t4758) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4702; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4702 = *_hp; free(_hp); }
                    (void)_t4702;
                    Bool _wcond4701; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4702}); _wcond4701 = *_hp; free(_hp); }
                    (void)_wcond4701;
                    ;
                    if (_wcond4701) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4703 = Str_lit(" '", 2ULL);
                    (void)_t4703;
                    Str *_t4704 = Str_concat(cmd, _t4703);
                    (void)_t4704;
                    Str_delete(_t4703, &(Bool){1});
                    Str *_t4705 = Str_concat(_t4704, uarg);
                    (void)_t4705;
                    Str_delete(_t4704, &(Bool){1});
                    Str *_t4706 = Str_lit("'", 1ULL);
                    (void)_t4706;
                    cmd = Str_concat(_t4705, _t4706);
                    Str_delete(_t4705, &(Bool){1});
                    Str_delete(_t4706, &(Bool){1});
                    U64 _t4707 = 1;
                    (void)_t4707;
                    U64 _t4708 = U64_add(DEREF(ui), _t4707);
                    (void)_t4708;
                    ;
                    *ui = _t4708;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4709 = til_system(cmd);
                (void)_t4709;
                Str_delete(cmd, &(Bool){1});
                result = _t4709;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4775 = Str_lit("ast", 3ULL);
            (void)_t4775;
            Bool _t4776; { Bool *_hp = (Bool *)Str_eq(command, _t4775); _t4776 = *_hp; free(_hp); }
            (void)_t4776;
            Str_delete(_t4775, &(Bool){1});
            if (_t4776) {
                Str *_t4759 = Str_lit("Str", 3ULL);
                (void)_t4759;
                U64 _t4760; { U64 *_hp = (U64 *)Str_size(); _t4760 = *_hp; free(_hp); }
                (void)_t4760;
                U64 _t4761 = 1;
                (void)_t4761;
                Array *_va98 = Array_new(_t4759, &(U64){_t4760}, &(U64){_t4761});
                (void)_va98;
                Str_delete(_t4759, &(Bool){1});
                ;
                ;
                Str *_t4762 = Str_lit("mode: ", 6ULL);
                (void)_t4762;
                U64 _t4763 = 0;
                (void)_t4763;
                Str *_t4764 = Str_concat(_t4762, &cur_mode->name);
                (void)_t4764;
                Str_delete(_t4762, &(Bool){1});
                Array_set(_va98, &(U64){_t4763}, _t4764);
                ;
                println(_va98);
                U32 _t4765 = 0;
                (void)_t4765;
                ast_print(ast, _t4765);
                ;
            } else {
                Str *_t4766 = Str_lit("Str", 3ULL);
                (void)_t4766;
                U64 _t4767; { U64 *_hp = (U64 *)Str_size(); _t4767 = *_hp; free(_hp); }
                (void)_t4767;
                U64 _t4768 = 1;
                (void)_t4768;
                Array *_va99 = Array_new(_t4766, &(U64){_t4767}, &(U64){_t4768});
                (void)_va99;
                Str_delete(_t4766, &(Bool){1});
                ;
                ;
                Str *_t4769 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4769;
                Str *_t4770 = Str_concat(_t4769, command);
                (void)_t4770;
                Str_delete(_t4769, &(Bool){1});
                Str *_t4771 = Str_lit("'", 1ULL);
                (void)_t4771;
                U64 _t4772 = 0;
                (void)_t4772;
                Str *_t4773 = Str_concat(_t4770, _t4771);
                (void)_t4773;
                Str_delete(_t4770, &(Bool){1});
                Str_delete(_t4771, &(Bool){1});
                Array_set(_va99, &(U64){_t4772}, _t4773);
                ;
                println(_va99);
                usage();
                I32 _t4774 = 1;
                (void)_t4774;
                result = _t4774;
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
    I64 _t4864 = I32_to_i64(result);
    (void)_t4864;
    ;
    exit(_t4864);
    ;
    return 0;
}

