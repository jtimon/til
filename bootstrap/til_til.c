#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4280 = Str_lit("Str", 3ULL);
    (void)_t4280;
    U64 _t4281; { U64 *_hp = (U64 *)Str_size(); _t4281 = *_hp; free(_hp); }
    (void)_t4281;
    Vec *paths = Vec_new(_t4280, &(U64){_t4281});
    (void)paths;
    Str_delete(_t4280, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4255 = expr_nchildren(body);
        (void)_t4255;
        Bool _wcond4251; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4255}); _wcond4251 = *_hp; free(_hp); }
        (void)_wcond4251;
        ;
        if (_wcond4251) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4256 = expr_get_tag(stmt);
        (void)_t4256;
        U32 _t4257 = expr_nchildren(stmt);
        (void)_t4257;
        U32 _t4258 = 2;
        (void)_t4258;
        Bool _t4259 = I32_eq(_t4256, DEREF(NODE_FCALL));
        (void)_t4259;
        ;
        Bool _t4260 = U32_eq(_t4257, _t4258);
        (void)_t4260;
        ;
        ;
        U32 *_t4261 = malloc(sizeof(U32));
        *_t4261 = 0;
        (void)_t4261;
        Expr *_t4262 = expr_get_child(stmt, DEREF(_t4261));
        (void)_t4262;
        I32 _t4263 = expr_get_tag(_t4262);
        (void)_t4263;
        U32_delete(_t4261, &(Bool){1});
        Bool _t4264 = Bool_and(_t4259, _t4260);
        (void)_t4264;
        ;
        ;
        Bool _t4265 = I32_eq(_t4263, DEREF(NODE_IDENT));
        (void)_t4265;
        ;
        U32 *_t4266 = malloc(sizeof(U32));
        *_t4266 = 0;
        (void)_t4266;
        Expr *_t4267 = expr_get_child(stmt, DEREF(_t4266));
        (void)_t4267;
        Str *_t4268 = expr_get_str_val(_t4267);
        (void)_t4268;
        Str *_t4269 = Str_lit("import", 6ULL);
        (void)_t4269;
        Bool _t4270 = Bool_and(_t4264, _t4265);
        (void)_t4270;
        ;
        ;
        Bool _t4271; { Bool *_hp = (Bool *)Str_eq(_t4268, _t4269); _t4271 = *_hp; free(_hp); }
        (void)_t4271;
        U32_delete(_t4266, &(Bool){1});
        Str_delete(_t4269, &(Bool){1});
        U32 *_t4272 = malloc(sizeof(U32));
        *_t4272 = 1;
        (void)_t4272;
        Expr *_t4273 = expr_get_child(stmt, DEREF(_t4272));
        (void)_t4273;
        I32 _t4274 = expr_get_tag(_t4273);
        (void)_t4274;
        U32_delete(_t4272, &(Bool){1});
        Bool _t4275 = Bool_and(_t4270, _t4271);
        (void)_t4275;
        ;
        ;
        Bool _t4276 = I32_eq(_t4274, DEREF(NODE_LITERAL_STR));
        (void)_t4276;
        ;
        Bool _t4277 = Bool_and(_t4275, _t4276);
        (void)_t4277;
        ;
        ;
        if (_t4277) {
            U32 *_t4252 = malloc(sizeof(U32));
            *_t4252 = 1;
            (void)_t4252;
            Expr *_t4253 = expr_get_child(stmt, DEREF(_t4252));
            (void)_t4253;
            Str *path = expr_get_str_val(_t4253);
            (void)path;
            Str *_t4254 = Str_clone(path);
            (void)_t4254;
            U32_delete(_t4252, &(Bool){1});
            Vec_push(paths, _t4254);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4278 = 1;
        (void)_t4278;
        U32 _t4279 = U32_add(DEREF(i), _t4278);
        (void)_t4279;
        ;
        *i = _t4279;
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
        U64 _fi4282 = 0;
        (void)_fi4282;
        while (1) {
            U64 _t4312 = 0;
            (void)_t4312;
            U64 _t4313; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4313 = *_hp; free(_hp); }
            (void)_t4313;
            Range *_t4314 = Range_new(_t4312, _t4313);
            (void)_t4314;
            ;
            ;
            U64 _t4315; { U64 *_hp = (U64 *)Range_len(_t4314); _t4315 = *_hp; free(_hp); }
            (void)_t4315;
            Range_delete(_t4314, &(Bool){1});
            Bool _wcond4283; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4282}, &(U64){_t4315}); _wcond4283 = *_hp; free(_hp); }
            (void)_wcond4283;
            ;
            if (_wcond4283) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4316 = 0;
            (void)_t4316;
            U64 _t4317; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4317 = *_hp; free(_hp); }
            (void)_t4317;
            Range *_t4318 = Range_new(_t4316, _t4317);
            (void)_t4318;
            ;
            ;
            U64 *i = Range_get(_t4318, _fi4282);
            (void)i;
            Range_delete(_t4318, &(Bool){1});
            U64 _t4319 = 1;
            (void)_t4319;
            U64 _t4320 = U64_add(_fi4282, _t4319);
            (void)_t4320;
            ;
            _fi4282 = _t4320;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4321 = Str_lit("/", 1ULL);
            (void)_t4321;
            Str *_t4322 = Str_concat(base_dir, _t4321);
            (void)_t4322;
            Str_delete(_t4321, &(Bool){1});
            Str *try_path = Str_concat(_t4322, import_path);
            (void)try_path;
            Str_delete(_t4322, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4323 = Str_lit("", 0ULL);
            (void)_t4323;
            U64 _t4324; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4324 = *_hp; free(_hp); }
            (void)_t4324;
            U64 _t4325 = 0;
            (void)_t4325;
            Bool _t4326; { Bool *_hp = (Bool *)Str_eq(abs, _t4323); _t4326 = *_hp; free(_hp); }
            (void)_t4326;
            Str_delete(_t4323, &(Bool){1});
            Bool _t4327; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4324}, &(U64){_t4325}); _t4327 = *_hp; free(_hp); }
            (void)_t4327;
            ;
            ;
            Bool _t4328 = Bool_and(_t4326, _t4327);
            (void)_t4328;
            ;
            ;
            if (_t4328) {
                Str *_t4284 = Str_lit("/", 1ULL);
                (void)_t4284;
                Str *_t4285 = Str_concat(lib_dir, _t4284);
                (void)_t4285;
                Str_delete(_t4284, &(Bool){1});
                try_path = Str_concat(_t4285, import_path);
                Str_delete(_t4285, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4329 = Str_lit("", 0ULL);
            (void)_t4329;
            Bool _t4330; { Bool *_hp = (Bool *)Str_eq(abs, _t4329); _t4330 = *_hp; free(_hp); }
            (void)_t4330;
            Str_delete(_t4329, &(Bool){1});
            if (_t4330) {
                Str *_t4286 = Str_lit("Str", 3ULL);
                (void)_t4286;
                U64 _t4287; { U64 *_hp = (U64 *)Str_size(); _t4287 = *_hp; free(_hp); }
                (void)_t4287;
                U64 _t4288 = 1;
                (void)_t4288;
                Array *_va72 = Array_new(_t4286, &(U64){_t4287}, &(U64){_t4288});
                (void)_va72;
                Str_delete(_t4286, &(Bool){1});
                ;
                ;
                Str *_t4289 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4289;
                Str *_t4290 = Str_concat(_t4289, import_path);
                (void)_t4290;
                Str_delete(_t4289, &(Bool){1});
                Str *_t4291 = Str_lit("' (from ", 8ULL);
                (void)_t4291;
                Str *_t4292 = Str_concat(_t4290, _t4291);
                (void)_t4292;
                Str_delete(_t4290, &(Bool){1});
                Str_delete(_t4291, &(Bool){1});
                Str *_t4293 = Str_concat(_t4292, base_dir);
                (void)_t4293;
                Str_delete(_t4292, &(Bool){1});
                Str *_t4294 = Str_lit("/)", 2ULL);
                (void)_t4294;
                U64 _t4295 = 0;
                (void)_t4295;
                Str *_t4296 = Str_concat(_t4293, _t4294);
                (void)_t4296;
                Str_delete(_t4293, &(Bool){1});
                Str_delete(_t4294, &(Bool){1});
                Array_set(_va72, &(U64){_t4295}, _t4296);
                ;
                println(_va72);
                I64 _t4297 = 1;
                (void)_t4297;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4297; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4331; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4331 = *_hp; free(_hp); }
            (void)_t4331;
            if (_t4331) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4332 = Str_clone(abs);
            (void)_t4332;
            Set_add(resolved_set, _t4332);
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
            U64 _t4333; { U64 *_hp = (U64 *)Str_len(abs); _t4333 = *_hp; free(_hp); }
            (void)_t4333;
            U64 _t4334 = 1;
            (void)_t4334;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4333, _t4334);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4299 = 0;
                (void)_t4299;
                U8 *_t4300 = Str_get(abs, last_slash);
                (void)_t4300;
                U8 _t4301 = 47;
                (void)_t4301;
                Bool _t4302; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4299}); _t4302 = *_hp; free(_hp); }
                (void)_t4302;
                ;
                Bool _t4303; { Bool *_hp = (Bool *)U8_neq(_t4300, &(U8){_t4301}); _t4303 = *_hp; free(_hp); }
                (void)_t4303;
                ;
                Bool _wcond4298 = Bool_and(_t4302, _t4303);
                (void)_wcond4298;
                ;
                ;
                if (_wcond4298) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4304 = 1;
                (void)_t4304;
                U64 _t4305 = U64_sub(DEREF(last_slash), _t4304);
                (void)_t4305;
                ;
                *last_slash = _t4305;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4335; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4335 = *_hp; free(_hp); }
            (void)_t4335;
            U64 _t4336 = 0;
            (void)_t4336;
            Bool _t4337; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4335}, &(U64){_t4336}); _t4337 = *_hp; free(_hp); }
            (void)_t4337;
            ;
            ;
            if (_t4337) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4306 = 0;
                (void)_t4306;
                Bool _t4307; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4306}); _t4307 = *_hp; free(_hp); }
                (void)_t4307;
                ;
                if (_t4307) {
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
                U32 _t4309 = expr_nchildren(sub_ast);
                (void)_t4309;
                Bool _wcond4308; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4309}); _wcond4308 = *_hp; free(_hp); }
                (void)_wcond4308;
                ;
                if (_wcond4308) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4310 = 1;
                (void)_t4310;
                U32 _t4311 = U32_add(DEREF(k), _t4310);
                (void)_t4311;
                ;
                *k = _t4311;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t4338 = 0;
    (void)_t4338;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4338; return _r; }
}

void usage(void) {
    Str *_t4339 = Str_lit("Str", 3ULL);
    (void)_t4339;
    U64 _t4340; { U64 *_hp = (U64 *)Str_size(); _t4340 = *_hp; free(_hp); }
    (void)_t4340;
    U64 _t4341 = 1;
    (void)_t4341;
    Array *_va73 = Array_new(_t4339, &(U64){_t4340}, &(U64){_t4341});
    (void)_va73;
    Str_delete(_t4339, &(Bool){1});
    ;
    ;
    U64 _t4342 = 0;
    (void)_t4342;
    Str *_t4343 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4343;
    Array_set(_va73, &(U64){_t4342}, _t4343);
    ;
    println(_va73);
    Str *_t4344 = Str_lit("Str", 3ULL);
    (void)_t4344;
    U64 _t4345; { U64 *_hp = (U64 *)Str_size(); _t4345 = *_hp; free(_hp); }
    (void)_t4345;
    U64 _t4346 = 1;
    (void)_t4346;
    Array *_va74 = Array_new(_t4344, &(U64){_t4345}, &(U64){_t4346});
    (void)_va74;
    Str_delete(_t4344, &(Bool){1});
    ;
    ;
    U64 _t4347 = 0;
    (void)_t4347;
    Str *_t4348 = Str_lit("", 0ULL);
    (void)_t4348;
    Array_set(_va74, &(U64){_t4347}, _t4348);
    ;
    println(_va74);
    Str *_t4349 = Str_lit("Str", 3ULL);
    (void)_t4349;
    U64 _t4350; { U64 *_hp = (U64 *)Str_size(); _t4350 = *_hp; free(_hp); }
    (void)_t4350;
    U64 _t4351 = 1;
    (void)_t4351;
    Array *_va75 = Array_new(_t4349, &(U64){_t4350}, &(U64){_t4351});
    (void)_va75;
    Str_delete(_t4349, &(Bool){1});
    ;
    ;
    U64 _t4352 = 0;
    (void)_t4352;
    Str *_t4353 = Str_lit("Commands:", 9ULL);
    (void)_t4353;
    Array_set(_va75, &(U64){_t4352}, _t4353);
    ;
    println(_va75);
    Str *_t4354 = Str_lit("Str", 3ULL);
    (void)_t4354;
    U64 _t4355; { U64 *_hp = (U64 *)Str_size(); _t4355 = *_hp; free(_hp); }
    (void)_t4355;
    U64 _t4356 = 1;
    (void)_t4356;
    Array *_va76 = Array_new(_t4354, &(U64){_t4355}, &(U64){_t4356});
    (void)_va76;
    Str_delete(_t4354, &(Bool){1});
    ;
    ;
    U64 _t4357 = 0;
    (void)_t4357;
    Str *_t4358 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4358;
    Array_set(_va76, &(U64){_t4357}, _t4358);
    ;
    println(_va76);
    Str *_t4359 = Str_lit("Str", 3ULL);
    (void)_t4359;
    U64 _t4360; { U64 *_hp = (U64 *)Str_size(); _t4360 = *_hp; free(_hp); }
    (void)_t4360;
    U64 _t4361 = 1;
    (void)_t4361;
    Array *_va77 = Array_new(_t4359, &(U64){_t4360}, &(U64){_t4361});
    (void)_va77;
    Str_delete(_t4359, &(Bool){1});
    ;
    ;
    U64 _t4362 = 0;
    (void)_t4362;
    Str *_t4363 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4363;
    Array_set(_va77, &(U64){_t4362}, _t4363);
    ;
    println(_va77);
    Str *_t4364 = Str_lit("Str", 3ULL);
    (void)_t4364;
    U64 _t4365; { U64 *_hp = (U64 *)Str_size(); _t4365 = *_hp; free(_hp); }
    (void)_t4365;
    U64 _t4366 = 1;
    (void)_t4366;
    Array *_va78 = Array_new(_t4364, &(U64){_t4365}, &(U64){_t4366});
    (void)_va78;
    Str_delete(_t4364, &(Bool){1});
    ;
    ;
    U64 _t4367 = 0;
    (void)_t4367;
    Str *_t4368 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4368;
    Array_set(_va78, &(U64){_t4367}, _t4368);
    ;
    println(_va78);
    Str *_t4369 = Str_lit("Str", 3ULL);
    (void)_t4369;
    U64 _t4370; { U64 *_hp = (U64 *)Str_size(); _t4370 = *_hp; free(_hp); }
    (void)_t4370;
    U64 _t4371 = 1;
    (void)_t4371;
    Array *_va79 = Array_new(_t4369, &(U64){_t4370}, &(U64){_t4371});
    (void)_va79;
    Str_delete(_t4369, &(Bool){1});
    ;
    ;
    U64 _t4372 = 0;
    (void)_t4372;
    Str *_t4373 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4373;
    Array_set(_va79, &(U64){_t4372}, _t4373);
    ;
    println(_va79);
    Str *_t4374 = Str_lit("Str", 3ULL);
    (void)_t4374;
    U64 _t4375; { U64 *_hp = (U64 *)Str_size(); _t4375 = *_hp; free(_hp); }
    (void)_t4375;
    U64 _t4376 = 1;
    (void)_t4376;
    Array *_va80 = Array_new(_t4374, &(U64){_t4375}, &(U64){_t4376});
    (void)_va80;
    Str_delete(_t4374, &(Bool){1});
    ;
    ;
    U64 _t4377 = 0;
    (void)_t4377;
    Str *_t4378 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4378;
    Array_set(_va80, &(U64){_t4377}, _t4378);
    ;
    println(_va80);
    Str *_t4379 = Str_lit("Str", 3ULL);
    (void)_t4379;
    U64 _t4380; { U64 *_hp = (U64 *)Str_size(); _t4380 = *_hp; free(_hp); }
    (void)_t4380;
    U64 _t4381 = 1;
    (void)_t4381;
    Array *_va81 = Array_new(_t4379, &(U64){_t4380}, &(U64){_t4381});
    (void)_va81;
    Str_delete(_t4379, &(Bool){1});
    ;
    ;
    U64 _t4382 = 0;
    (void)_t4382;
    Str *_t4383 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4383;
    Array_set(_va81, &(U64){_t4382}, _t4383);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4389 = 1;
    (void)_t4389;
    e->is_core = _t4389;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4385 = expr_nchildren(e);
        (void)_t4385;
        Bool _wcond4384; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4385}); _wcond4384 = *_hp; free(_hp); }
        (void)_wcond4384;
        ;
        if (_wcond4384) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4386 = expr_get_child(e, DEREF(i));
        (void)_t4386;
        mark_core(_t4386);
        U32 _t4387 = 1;
        (void)_t4387;
        U32 _t4388 = U32_add(DEREF(i), _t4387);
        (void)_t4388;
        ;
        *i = _t4388;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4849 = malloc(sizeof(I64));
    *_t4849 = 0;
    (void)_t4849;
    _t4850 = malloc(sizeof(I64));
    *_t4850 = 1;
    (void)_t4850;
    _t4851 = malloc(sizeof(I64)); *_t4851 = I64_sub(DEREF(_t4849), DEREF(_t4850));
    (void)_t4851;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4851));
    (void)CAP_LIT;
    _t4852 = malloc(sizeof(I64));
    *_t4852 = 0;
    (void)_t4852;
    _t4853 = malloc(sizeof(I64));
    *_t4853 = 2;
    (void)_t4853;
    _t4854 = malloc(sizeof(I64)); *_t4854 = I64_sub(DEREF(_t4852), DEREF(_t4853));
    (void)_t4854;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4854));
    (void)CAP_VIEW;
    _t4855 = Str_lit("Str", 3ULL);
    (void)_t4855;
    _t4856 = Str_size();
    (void)_t4856;
    _t4857 = Str_lit("Mode", 4ULL);
    (void)_t4857;
    _t4858 = Mode_size();
    (void)_t4858;
    core_modes = Map_new(_t4855, _t4856, _t4857, _t4858);
    (void)core_modes;
    _t4859 = malloc(sizeof(Bool));
    *_t4859 = 0;
    (void)_t4859;
    _t4860 = malloc(sizeof(Bool));
    *_t4860 = 0;
    (void)_t4860;
    _t4861 = malloc(sizeof(Bool));
    *_t4861 = 0;
    (void)_t4861;
    _t4862 = malloc(sizeof(Bool));
    *_t4862 = 0;
    (void)_t4862;
    _t4863 = Str_lit("script", 6ULL);
    (void)_t4863;
    _t4864 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4864->name = *_ca; free(_ca); }
    _t4864->needs_main = DEREF(_t4859);
    _t4864->decls_only = DEREF(_t4860);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4864->auto_import = *_ca; free(_ca); }
    _t4864->is_pure = DEREF(_t4861);
    _t4864->debug_prints = DEREF(_t4862);
    (void)_t4864;
    _t4865 = malloc(sizeof(Bool));
    *_t4865 = 1;
    (void)_t4865;
    _t4866 = malloc(sizeof(Bool));
    *_t4866 = 1;
    (void)_t4866;
    _t4867 = malloc(sizeof(Bool));
    *_t4867 = 0;
    (void)_t4867;
    _t4868 = malloc(sizeof(Bool));
    *_t4868 = 0;
    (void)_t4868;
    _t4869 = Str_lit("cli", 3ULL);
    (void)_t4869;
    _t4870 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4870->name = *_ca; free(_ca); }
    _t4870->needs_main = DEREF(_t4865);
    _t4870->decls_only = DEREF(_t4866);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4870->auto_import = *_ca; free(_ca); }
    _t4870->is_pure = DEREF(_t4867);
    _t4870->debug_prints = DEREF(_t4868);
    (void)_t4870;
    _t4871 = malloc(sizeof(Bool));
    *_t4871 = 1;
    (void)_t4871;
    _t4872 = malloc(sizeof(Bool));
    *_t4872 = 1;
    (void)_t4872;
    _t4873 = malloc(sizeof(Bool));
    *_t4873 = 0;
    (void)_t4873;
    _t4874 = malloc(sizeof(Bool));
    *_t4874 = 0;
    (void)_t4874;
    _t4875 = Str_lit("gui", 3ULL);
    (void)_t4875;
    _t4876 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4876->name = *_ca; free(_ca); }
    _t4876->needs_main = DEREF(_t4871);
    _t4876->decls_only = DEREF(_t4872);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4876->auto_import = *_ca; free(_ca); }
    _t4876->is_pure = DEREF(_t4873);
    _t4876->debug_prints = DEREF(_t4874);
    (void)_t4876;
    _t4877 = malloc(sizeof(Bool));
    *_t4877 = 0;
    (void)_t4877;
    _t4878 = malloc(sizeof(Bool));
    *_t4878 = 1;
    (void)_t4878;
    _t4879 = malloc(sizeof(Bool));
    *_t4879 = 0;
    (void)_t4879;
    _t4880 = malloc(sizeof(Bool));
    *_t4880 = 0;
    (void)_t4880;
    _t4881 = Str_lit("test", 4ULL);
    (void)_t4881;
    _t4882 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4882->name = *_ca; free(_ca); }
    _t4882->needs_main = DEREF(_t4877);
    _t4882->decls_only = DEREF(_t4878);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4882->auto_import = *_ca; free(_ca); }
    _t4882->is_pure = DEREF(_t4879);
    _t4882->debug_prints = DEREF(_t4880);
    (void)_t4882;
    _t4883 = malloc(sizeof(Bool));
    *_t4883 = 0;
    (void)_t4883;
    _t4884 = malloc(sizeof(Bool));
    *_t4884 = 1;
    (void)_t4884;
    _t4885 = malloc(sizeof(Bool));
    *_t4885 = 1;
    (void)_t4885;
    _t4886 = malloc(sizeof(Bool));
    *_t4886 = 0;
    (void)_t4886;
    _t4887 = Str_lit("pure", 4ULL);
    (void)_t4887;
    _t4888 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4888->name = *_ca; free(_ca); }
    _t4888->needs_main = DEREF(_t4883);
    _t4888->decls_only = DEREF(_t4884);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4888->auto_import = *_ca; free(_ca); }
    _t4888->is_pure = DEREF(_t4885);
    _t4888->debug_prints = DEREF(_t4886);
    (void)_t4888;
    _t4889 = malloc(sizeof(Bool));
    *_t4889 = 0;
    (void)_t4889;
    _t4890 = malloc(sizeof(Bool));
    *_t4890 = 1;
    (void)_t4890;
    _t4891 = malloc(sizeof(Bool));
    *_t4891 = 1;
    (void)_t4891;
    _t4892 = malloc(sizeof(Bool));
    *_t4892 = 1;
    (void)_t4892;
    _t4893 = Str_lit("pura", 4ULL);
    (void)_t4893;
    _t4894 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4894->name = *_ca; free(_ca); }
    _t4894->needs_main = DEREF(_t4889);
    _t4894->decls_only = DEREF(_t4890);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4894->auto_import = *_ca; free(_ca); }
    _t4894->is_pure = DEREF(_t4891);
    _t4894->debug_prints = DEREF(_t4892);
    (void)_t4894;
    _t4895 = malloc(sizeof(Bool));
    *_t4895 = 0;
    (void)_t4895;
    _t4896 = malloc(sizeof(Bool));
    *_t4896 = 1;
    (void)_t4896;
    _t4897 = malloc(sizeof(Bool));
    *_t4897 = 0;
    (void)_t4897;
    _t4898 = malloc(sizeof(Bool));
    *_t4898 = 0;
    (void)_t4898;
    _t4899 = Str_lit("lib", 3ULL);
    (void)_t4899;
    _t4900 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4900->name = *_ca; free(_ca); }
    _t4900->needs_main = DEREF(_t4895);
    _t4900->decls_only = DEREF(_t4896);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4900->auto_import = *_ca; free(_ca); }
    _t4900->is_pure = DEREF(_t4897);
    _t4900->debug_prints = DEREF(_t4898);
    (void)_t4900;
    _t4901 = malloc(sizeof(Bool));
    *_t4901 = 0;
    (void)_t4901;
    _t4902 = malloc(sizeof(Bool));
    *_t4902 = 1;
    (void)_t4902;
    _t4903 = malloc(sizeof(Bool));
    *_t4903 = 0;
    (void)_t4903;
    _t4904 = malloc(sizeof(Bool));
    *_t4904 = 1;
    (void)_t4904;
    _t4905 = Str_lit("liba", 4ULL);
    (void)_t4905;
    _t4906 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4906->name = *_ca; free(_ca); }
    _t4906->needs_main = DEREF(_t4901);
    _t4906->decls_only = DEREF(_t4902);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4906->auto_import = *_ca; free(_ca); }
    _t4906->is_pure = DEREF(_t4903);
    _t4906->debug_prints = DEREF(_t4904);
    (void)_t4906;
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
    U64 _t4769; { U64 *_hp = (U64 *)Array_len(args); _t4769 = *_hp; free(_hp); }
    (void)_t4769;
    U64 _t4770 = 0;
    (void)_t4770;
    Bool _t4771 = U64_eq(_t4769, _t4770);
    (void)_t4771;
    ;
    ;
    if (_t4771) {
        usage();
        Str *_t4390 = Str_lit("Str", 3ULL);
        (void)_t4390;
        U64 _t4391; { U64 *_hp = (U64 *)Str_size(); _t4391 = *_hp; free(_hp); }
        (void)_t4391;
        U64 _t4392 = 1;
        (void)_t4392;
        Array *_va82 = Array_new(_t4390, &(U64){_t4391}, &(U64){_t4392});
        (void)_va82;
        Str_delete(_t4390, &(Bool){1});
        ;
        ;
        U64 _t4393 = 0;
        (void)_t4393;
        Str *_t4394 = Str_lit("no arguments", 12ULL);
        (void)_t4394;
        Array_set(_va82, &(U64){_t4393}, _t4394);
        ;
        Str *_t4395 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4395;
        panic(_t4395, _va82);
        Str_delete(_t4395, &(Bool){1});
    }
    ;
    U64 *_t4772 = malloc(sizeof(U64));
    *_t4772 = 0;
    (void)_t4772;
    Str *cmd_ref = Array_get(args, _t4772);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4772, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4773; { U64 *_hp = (U64 *)Array_len(args); _t4773 = *_hp; free(_hp); }
    (void)_t4773;
    U64 _t4774 = 1;
    (void)_t4774;
    Bool _t4775 = U64_eq(_t4773, _t4774);
    (void)_t4775;
    ;
    ;
    if (_t4775) {
        Str *_t4396 = Str_lit("help", 4ULL);
        (void)_t4396;
        Str *_t4397 = Str_lit("--help", 6ULL);
        (void)_t4397;
        Bool _t4398; { Bool *_hp = (Bool *)Str_eq(command, _t4396); _t4398 = *_hp; free(_hp); }
        (void)_t4398;
        Str_delete(_t4396, &(Bool){1});
        Bool _t4399; { Bool *_hp = (Bool *)Str_eq(command, _t4397); _t4399 = *_hp; free(_hp); }
        (void)_t4399;
        Str_delete(_t4397, &(Bool){1});
        Bool _t4400 = Bool_or(_t4398, _t4399);
        (void)_t4400;
        ;
        ;
        if (_t4400) {
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
            U64 _t4417; { U64 *_hp = (U64 *)Array_len(args); _t4417 = *_hp; free(_hp); }
            (void)_t4417;
            Bool _wcond4401; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4417}); _wcond4401 = *_hp; free(_hp); }
            (void)_wcond4401;
            ;
            if (_wcond4401) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4418 = Str_lit("-o", 2ULL);
            (void)_t4418;
            U64 _t4419 = 1;
            (void)_t4419;
            U64 _t4420 = U64_add(DEREF(path_idx), _t4419);
            (void)_t4420;
            ;
            U64 _t4421; { U64 *_hp = (U64 *)Array_len(args); _t4421 = *_hp; free(_hp); }
            (void)_t4421;
            Bool _t4422; { Bool *_hp = (Bool *)Str_eq(flag, _t4418); _t4422 = *_hp; free(_hp); }
            (void)_t4422;
            Str_delete(_t4418, &(Bool){1});
            Bool _t4423; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4420}, &(U64){_t4421}); _t4423 = *_hp; free(_hp); }
            (void)_t4423;
            ;
            ;
            Bool _t4424 = Bool_and(_t4422, _t4423);
            (void)_t4424;
            ;
            ;
            if (_t4424) {
                U64 _t4402 = 1;
                (void)_t4402;
                U64 *_t4403 = malloc(sizeof(U64)); *_t4403 = U64_add(DEREF(path_idx), _t4402);
                (void)_t4403;
                ;
                Str *oval = Array_get(args, _t4403);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4403, &(Bool){1});
                U64 _t4404 = 2;
                (void)_t4404;
                U64 _t4405 = U64_add(DEREF(path_idx), _t4404);
                (void)_t4405;
                ;
                *path_idx = _t4405;
                ;
            } else {
                Str *_t4410 = Str_lit("-c", 2ULL);
                (void)_t4410;
                U64 _t4411 = 1;
                (void)_t4411;
                U64 _t4412 = U64_add(DEREF(path_idx), _t4411);
                (void)_t4412;
                ;
                U64 _t4413; { U64 *_hp = (U64 *)Array_len(args); _t4413 = *_hp; free(_hp); }
                (void)_t4413;
                Bool _t4414; { Bool *_hp = (Bool *)Str_eq(flag, _t4410); _t4414 = *_hp; free(_hp); }
                (void)_t4414;
                Str_delete(_t4410, &(Bool){1});
                Bool _t4415; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4412}, &(U64){_t4413}); _t4415 = *_hp; free(_hp); }
                (void)_t4415;
                ;
                ;
                Bool _t4416 = Bool_and(_t4414, _t4415);
                (void)_t4416;
                ;
                ;
                if (_t4416) {
                    U64 _t4406 = 1;
                    (void)_t4406;
                    U64 *_t4407 = malloc(sizeof(U64)); *_t4407 = U64_add(DEREF(path_idx), _t4406);
                    (void)_t4407;
                    ;
                    Str *cval = Array_get(args, _t4407);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4407, &(Bool){1});
                    U64 _t4408 = 2;
                    (void)_t4408;
                    U64 _t4409 = U64_add(DEREF(path_idx), _t4408);
                    (void)_t4409;
                    ;
                    *path_idx = _t4409;
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
    Str *_t4776 = Str_lit("help", 4ULL);
    (void)_t4776;
    Str *_t4777 = Str_lit("--help", 6ULL);
    (void)_t4777;
    Bool _t4778; { Bool *_hp = (Bool *)Str_eq(command, _t4776); _t4778 = *_hp; free(_hp); }
    (void)_t4778;
    Str_delete(_t4776, &(Bool){1});
    Bool _t4779; { Bool *_hp = (Bool *)Str_eq(command, _t4777); _t4779 = *_hp; free(_hp); }
    (void)_t4779;
    Str_delete(_t4777, &(Bool){1});
    Bool _t4780 = Bool_or(_t4778, _t4779);
    (void)_t4780;
    ;
    ;
    if (_t4780) {
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
    Str *_t4781 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4781;
    Str *core_path = Str_concat(bin_dir, _t4781);
    (void)core_path;
    Str_delete(_t4781, &(Bool){1});
    Str *_t4782 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4782;
    Str *ext_c_path = Str_concat(bin_dir, _t4782);
    (void)ext_c_path;
    Str_delete(_t4782, &(Bool){1});
    Str *_t4783 = Str_lit("Str", 3ULL);
    (void)_t4783;
    U64 _t4784; { U64 *_hp = (U64 *)Str_size(); _t4784 = *_hp; free(_hp); }
    (void)_t4784;
    Set *resolved = Set_new(_t4783, &(U64){_t4784});
    (void)resolved;
    Str_delete(_t4783, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4785; { U64 *_hp = (U64 *)Str_len(abs_path); _t4785 = *_hp; free(_hp); }
    (void)_t4785;
    U64 _t4786 = 0;
    (void)_t4786;
    Bool _t4787; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4785}, &(U64){_t4786}); _t4787 = *_hp; free(_hp); }
    (void)_t4787;
    ;
    ;
    if (_t4787) {
        U64 _t4433; { U64 *_hp = (U64 *)Str_len(abs_path); _t4433 = *_hp; free(_hp); }
        (void)_t4433;
        U64 _t4434 = 1;
        (void)_t4434;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4433, _t4434);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4426 = 0;
            (void)_t4426;
            U8 *_t4427 = Str_get(abs_path, last_slash);
            (void)_t4427;
            U8 _t4428 = 47;
            (void)_t4428;
            Bool _t4429; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4426}); _t4429 = *_hp; free(_hp); }
            (void)_t4429;
            ;
            Bool _t4430; { Bool *_hp = (Bool *)U8_neq(_t4427, &(U8){_t4428}); _t4430 = *_hp; free(_hp); }
            (void)_t4430;
            ;
            Bool _wcond4425 = Bool_and(_t4429, _t4430);
            (void)_wcond4425;
            ;
            ;
            if (_wcond4425) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4431 = 1;
            (void)_t4431;
            U64 _t4432 = U64_sub(DEREF(last_slash), _t4431);
            (void)_t4432;
            ;
            *last_slash = _t4432;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4435 = Str_clone(abs_path);
        (void)_t4435;
        Set_add(resolved, _t4435);
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
    U64 _t4788; { U64 *_hp = (U64 *)Str_len(core_abs); _t4788 = *_hp; free(_hp); }
    (void)_t4788;
    U64 _t4789 = 0;
    (void)_t4789;
    Bool _t4790; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4788}, &(U64){_t4789}); _t4790 = *_hp; free(_hp); }
    (void)_t4790;
    ;
    ;
    if (_t4790) {
        Bool _t4437; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4437 = *_hp; free(_hp); }
        (void)_t4437;
        if (_t4437) {
            Bool _t4436 = 1;
            (void)_t4436;
            skip_core = _t4436;
            ;
        }
        ;
        Str *_t4438 = Str_clone(core_abs);
        (void)_t4438;
        Set_add(resolved, _t4438);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4791; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4791 = *_hp; free(_hp); }
    (void)_t4791;
    U64 _t4792 = 0;
    (void)_t4792;
    Bool _t4793; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4791}, &(U64){_t4792}); _t4793 = *_hp; free(_hp); }
    (void)_t4793;
    ;
    ;
    Bool _t4794 = Bool_not(skip_core);
    (void)_t4794;
    Bool _t4795 = Bool_and(_t4793, _t4794);
    (void)_t4795;
    ;
    ;
    if (_t4795) {
        Str *_t4445 = Str_lit("/src/core", 9ULL);
        (void)_t4445;
        Str *core_dir = Str_concat(bin_dir, _t4445);
        (void)core_dir;
        Str_delete(_t4445, &(Bool){1});
        Str *_t4446 = Str_lit("", 0ULL);
        (void)_t4446;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4446); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4446, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4447 = 0;
        (void)_t4447;
        Bool _t4448; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4447}); _t4448 = *_hp; free(_hp); }
        (void)_t4448;
        ;
        ;
        if (_t4448) {
            Str *_t4439 = Str_lit("Str", 3ULL);
            (void)_t4439;
            U64 _t4440; { U64 *_hp = (U64 *)Str_size(); _t4440 = *_hp; free(_hp); }
            (void)_t4440;
            U64 _t4441 = 1;
            (void)_t4441;
            Array *_va83 = Array_new(_t4439, &(U64){_t4440}, &(U64){_t4441});
            (void)_va83;
            Str_delete(_t4439, &(Bool){1});
            ;
            ;
            U64 _t4442 = 0;
            (void)_t4442;
            Str *_t4443 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4443;
            Array_set(_va83, &(U64){_t4442}, _t4443);
            ;
            Str *_t4444 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4444;
            panic(_t4444, _va83);
            Str_delete(_t4444, &(Bool){1});
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
    Str *_t4796 = Str_lit("script", 6ULL);
    (void)_t4796;
    Mode *cur_mode = mode_resolve(_t4796);
    (void)cur_mode;
    Str_delete(_t4796, &(Bool){1});
    U64 _t4797; { U64 *_hp = (U64 *)Str_len(mode_str); _t4797 = *_hp; free(_hp); }
    (void)_t4797;
    U64 _t4798 = 0;
    (void)_t4798;
    Bool _t4799; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4797}, &(U64){_t4798}); _t4799 = *_hp; free(_hp); }
    (void)_t4799;
    ;
    ;
    if (_t4799) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4458; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4458 = *_hp; free(_hp); }
        (void)_t4458;
        U64 _t4459 = 0;
        (void)_t4459;
        Bool _t4460 = U64_eq(_t4458, _t4459);
        (void)_t4460;
        ;
        ;
        if (_t4460) {
            Str *_t4449 = Str_lit("Str", 3ULL);
            (void)_t4449;
            U64 _t4450; { U64 *_hp = (U64 *)Str_size(); _t4450 = *_hp; free(_hp); }
            (void)_t4450;
            U64 _t4451 = 1;
            (void)_t4451;
            Array *_va84 = Array_new(_t4449, &(U64){_t4450}, &(U64){_t4451});
            (void)_va84;
            Str_delete(_t4449, &(Bool){1});
            ;
            ;
            Str *_t4452 = Str_lit("unknown mode '", 14ULL);
            (void)_t4452;
            Str *_t4453 = Str_concat(_t4452, mode_str);
            (void)_t4453;
            Str_delete(_t4452, &(Bool){1});
            Str *_t4454 = Str_lit("'", 1ULL);
            (void)_t4454;
            U64 _t4455 = 0;
            (void)_t4455;
            Str *_t4456 = Str_concat(_t4453, _t4454);
            (void)_t4456;
            Str_delete(_t4453, &(Bool){1});
            Str_delete(_t4454, &(Bool){1});
            Array_set(_va84, &(U64){_t4455}, _t4456);
            ;
            Str *_t4457 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4457;
            panic(_t4457, _va84);
            Str_delete(_t4457, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4800; { U64 *_hp = (U64 *)Vec_len(imports); _t4800 = *_hp; free(_hp); }
    (void)_t4800;
    U64 _t4801 = 0;
    (void)_t4801;
    Bool _t4802; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4800}, &(U64){_t4801}); _t4802 = *_hp; free(_hp); }
    (void)_t4802;
    ;
    ;
    if (_t4802) {
        Str *_t4467 = Str_lit("/src/lib", 8ULL);
        (void)_t4467;
        Str *lib_dir = Str_concat(bin_dir, _t4467);
        (void)lib_dir;
        Str_delete(_t4467, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4468 = 0;
        (void)_t4468;
        Bool _t4469; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4468}); _t4469 = *_hp; free(_hp); }
        (void)_t4469;
        ;
        ;
        if (_t4469) {
            Str *_t4461 = Str_lit("Str", 3ULL);
            (void)_t4461;
            U64 _t4462; { U64 *_hp = (U64 *)Str_size(); _t4462 = *_hp; free(_hp); }
            (void)_t4462;
            U64 _t4463 = 1;
            (void)_t4463;
            Array *_va85 = Array_new(_t4461, &(U64){_t4462}, &(U64){_t4463});
            (void)_va85;
            Str_delete(_t4461, &(Bool){1});
            ;
            ;
            U64 _t4464 = 0;
            (void)_t4464;
            Str *_t4465 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4465;
            Array_set(_va85, &(U64){_t4464}, _t4465);
            ;
            Str *_t4466 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4466;
            panic(_t4466, _va85);
            Str_delete(_t4466, &(Bool){1});
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
    Bool _t4803 = Bool_not(skip_core);
    (void)_t4803;
    ;
    if (_t4803) {
        while (1) {
            U32 _t4471 = expr_nchildren(core_ast);
            (void)_t4471;
            Bool _wcond4470; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4471}); _wcond4470 = *_hp; free(_hp); }
            (void)_wcond4470;
            ;
            if (_wcond4470) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4472 = 1;
            (void)_t4472;
            U32 _t4473 = U32_add(DEREF(i), _t4472);
            (void)_t4473;
            ;
            *i = _t4473;
            ;
        }
        U32 _t4478 = 0;
        (void)_t4478;
        *i = _t4478;
        ;
        while (1) {
            U32 _t4475 = expr_vec_count(core_import_decls);
            (void)_t4475;
            Bool _wcond4474; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4475}); _wcond4474 = *_hp; free(_hp); }
            (void)_wcond4474;
            ;
            if (_wcond4474) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4476 = 1;
            (void)_t4476;
            U32 _t4477 = U32_add(DEREF(i), _t4476);
            (void)_t4477;
            ;
            *i = _t4477;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4804; { U64 *_hp = (U64 *)Str_len(auto_import); _t4804 = *_hp; free(_hp); }
    (void)_t4804;
    U64 _t4805 = 0;
    (void)_t4805;
    Bool _t4806; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4804}, &(U64){_t4805}); _t4806 = *_hp; free(_hp); }
    (void)_t4806;
    ;
    ;
    if (_t4806) {
        Str *_t4483 = Str_lit("/src/modes/", 11ULL);
        (void)_t4483;
        Str *_t4484 = Str_concat(bin_dir, _t4483);
        (void)_t4484;
        Str_delete(_t4483, &(Bool){1});
        Str *_t4485 = Str_concat(_t4484, auto_import);
        (void)_t4485;
        Str_delete(_t4484, &(Bool){1});
        Str *_t4486 = Str_lit(".til", 4ULL);
        (void)_t4486;
        Str *mode_til_path = Str_concat(_t4485, _t4486);
        (void)mode_til_path;
        Str_delete(_t4485, &(Bool){1});
        Str_delete(_t4486, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4487 = 0;
        (void)_t4487;
        *i = _t4487;
        ;
        while (1) {
            U32 _t4480 = expr_nchildren(mode_ast);
            (void)_t4480;
            Bool _wcond4479; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4480}); _wcond4479 = *_hp; free(_hp); }
            (void)_wcond4479;
            ;
            if (_wcond4479) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4481 = 1;
            (void)_t4481;
            U32 _t4482 = U32_add(DEREF(i), _t4481);
            (void)_t4482;
            ;
            *i = _t4482;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4807 = 0;
    (void)_t4807;
    *i = _t4807;
    ;
    while (1) {
        U32 _t4489 = expr_vec_count(import_decls);
        (void)_t4489;
        Bool _wcond4488; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4489}); _wcond4488 = *_hp; free(_hp); }
        (void)_wcond4488;
        ;
        if (_wcond4488) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4490 = 1;
        (void)_t4490;
        U32 _t4491 = U32_add(DEREF(i), _t4490);
        (void)_t4491;
        ;
        *i = _t4491;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4808 = 0;
    (void)_t4808;
    *i = _t4808;
    ;
    while (1) {
        U32 _t4493 = expr_nchildren(ast);
        (void)_t4493;
        Bool _wcond4492; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4493}); _wcond4492 = *_hp; free(_hp); }
        (void)_wcond4492;
        ;
        if (_wcond4492) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4494 = 1;
        (void)_t4494;
        U32 _t4495 = U32_add(DEREF(i), _t4494);
        (void)_t4495;
        ;
        *i = _t4495;
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
    U32 _t4809 = 0;
    (void)_t4809;
    *i = _t4809;
    ;
    while (1) {
        U32 _t4511 = expr_nchildren(ast);
        (void)_t4511;
        Bool _wcond4496; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4511}); _wcond4496 = *_hp; free(_hp); }
        (void)_wcond4496;
        ;
        if (_wcond4496) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4512 = expr_get_tag(stmt);
        (void)_t4512;
        U32 _t4513 = expr_nchildren(stmt);
        (void)_t4513;
        U32 _t4514 = 2;
        (void)_t4514;
        Bool _t4515 = I32_eq(_t4512, DEREF(NODE_FCALL));
        (void)_t4515;
        ;
        Bool _t4516 = U32_eq(_t4513, _t4514);
        (void)_t4516;
        ;
        ;
        U32 *_t4517 = malloc(sizeof(U32));
        *_t4517 = 0;
        (void)_t4517;
        Expr *_t4518 = expr_get_child(stmt, DEREF(_t4517));
        (void)_t4518;
        I32 _t4519 = expr_get_tag(_t4518);
        (void)_t4519;
        U32_delete(_t4517, &(Bool){1});
        Bool _t4520 = Bool_and(_t4515, _t4516);
        (void)_t4520;
        ;
        ;
        Bool _t4521 = I32_eq(_t4519, DEREF(NODE_IDENT));
        (void)_t4521;
        ;
        U32 *_t4522 = malloc(sizeof(U32));
        *_t4522 = 1;
        (void)_t4522;
        Expr *_t4523 = expr_get_child(stmt, DEREF(_t4522));
        (void)_t4523;
        I32 _t4524 = expr_get_tag(_t4523);
        (void)_t4524;
        U32_delete(_t4522, &(Bool){1});
        Bool _t4525 = Bool_and(_t4520, _t4521);
        (void)_t4525;
        ;
        ;
        Bool _t4526 = I32_eq(_t4524, DEREF(NODE_LITERAL_STR));
        (void)_t4526;
        ;
        Bool _t4527 = Bool_and(_t4525, _t4526);
        (void)_t4527;
        ;
        ;
        if (_t4527) {
            U32 *_t4505 = malloc(sizeof(U32));
            *_t4505 = 0;
            (void)_t4505;
            Expr *_t4506 = expr_get_child(stmt, DEREF(_t4505));
            (void)_t4506;
            Str *fname = expr_get_str_val(_t4506);
            (void)fname;
            U32 *_t4507 = malloc(sizeof(U32));
            *_t4507 = 1;
            (void)_t4507;
            Expr *_t4508 = expr_get_child(stmt, DEREF(_t4507));
            (void)_t4508;
            Str *arg = expr_get_str_val(_t4508);
            (void)arg;
            Str *_t4509 = Str_lit("link", 4ULL);
            (void)_t4509;
            Bool _t4510; { Bool *_hp = (Bool *)Str_eq(fname, _t4509); _t4510 = *_hp; free(_hp); }
            (void)_t4510;
            Str_delete(_t4509, &(Bool){1});
            if (_t4510) {
                Str *_t4497 = Str_lit(" -l", 3ULL);
                (void)_t4497;
                Str *_t4498 = Str_concat(link_flags, _t4497);
                (void)_t4498;
                Str_delete(_t4497, &(Bool){1});
                link_flags = Str_concat(_t4498, arg);
                Str_delete(_t4498, &(Bool){1});
            } else {
                Str *_t4503 = Str_lit("link_c", 6ULL);
                (void)_t4503;
                Bool _t4504; { Bool *_hp = (Bool *)Str_eq(fname, _t4503); _t4504 = *_hp; free(_hp); }
                (void)_t4504;
                Str_delete(_t4503, &(Bool){1});
                if (_t4504) {
                    U64 _t4500; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4500 = *_hp; free(_hp); }
                    (void)_t4500;
                    U64 _t4501 = 0;
                    (void)_t4501;
                    Bool _t4502; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4500}, &(U64){_t4501}); _t4502 = *_hp; free(_hp); }
                    (void)_t4502;
                    ;
                    ;
                    if (_t4502) {
                        Str *_t4499 = Str_lit(" ", 1ULL);
                        (void)_t4499;
                        link_c_paths = Str_concat(link_c_paths, _t4499);
                        Str_delete(_t4499, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4505, &(Bool){1});
            U32_delete(_t4507, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4528 = 1;
        (void)_t4528;
        U32 _t4529 = U32_add(DEREF(i), _t4528);
        (void)_t4529;
        ;
        *i = _t4529;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4810 = init_declarations(ast, scope);
    (void)_t4810;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4811 = 0;
    (void)_t4811;
    Bool _t4812; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4811}); _t4812 = *_hp; free(_hp); }
    (void)_t4812;
    ;
    if (_t4812) {
        Str *_t4530 = Str_lit("Str", 3ULL);
        (void)_t4530;
        U64 _t4531; { U64 *_hp = (U64 *)Str_size(); _t4531 = *_hp; free(_hp); }
        (void)_t4531;
        U64 _t4532 = 1;
        (void)_t4532;
        Array *_va86 = Array_new(_t4530, &(U64){_t4531}, &(U64){_t4532});
        (void)_va86;
        Str_delete(_t4530, &(Bool){1});
        ;
        ;
        Str *_t4533 = I32_to_str(&(I32){type_errors});
        (void)_t4533;
        Str *_t4534 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4534;
        U64 _t4535 = 0;
        (void)_t4535;
        Str *_t4536 = Str_concat(_t4533, _t4534);
        (void)_t4536;
        Str_delete(_t4533, &(Bool){1});
        Str_delete(_t4534, &(Bool){1});
        Array_set(_va86, &(U64){_t4535}, _t4536);
        ;
        Str *_t4537 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4537;
        panic(_t4537, _va86);
        Str_delete(_t4537, &(Bool){1});
    }
    ;
    ;
    Str *_t4813 = Str_lit("test", 4ULL);
    (void)_t4813;
    Str *_t4814 = Str_lit("test", 4ULL);
    (void)_t4814;
    Bool _t4815; { Bool *_hp = (Bool *)Str_eq(command, _t4813); _t4815 = *_hp; free(_hp); }
    (void)_t4815;
    Str_delete(_t4813, &(Bool){1});
    Bool _t4816; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4814); _t4816 = *_hp; free(_hp); }
    (void)_t4816;
    Str_delete(_t4814, &(Bool){1});
    Str *_t4817 = Str_lit("pure", 4ULL);
    (void)_t4817;
    Bool _t4818 = Bool_or(_t4815, _t4816);
    (void)_t4818;
    ;
    ;
    Bool _t4819; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4817); _t4819 = *_hp; free(_hp); }
    (void)_t4819;
    Str_delete(_t4817, &(Bool){1});
    Str *_t4820 = Str_lit("pura", 4ULL);
    (void)_t4820;
    Bool _t4821 = Bool_or(_t4818, _t4819);
    (void)_t4821;
    ;
    ;
    Bool _t4822; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4820); _t4822 = *_hp; free(_hp); }
    (void)_t4822;
    Str_delete(_t4820, &(Bool){1});
    Bool run_tests = Bool_or(_t4821, _t4822);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4823 = Str_lit("translate", 9ULL);
    (void)_t4823;
    Str *_t4824 = Str_lit("build", 5ULL);
    (void)_t4824;
    Bool _t4825; { Bool *_hp = (Bool *)Str_eq(command, _t4823); _t4825 = *_hp; free(_hp); }
    (void)_t4825;
    Str_delete(_t4823, &(Bool){1});
    Bool _t4826; { Bool *_hp = (Bool *)Str_eq(command, _t4824); _t4826 = *_hp; free(_hp); }
    (void)_t4826;
    Str_delete(_t4824, &(Bool){1});
    Bool _t4827; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4827 = *_hp; free(_hp); }
    (void)_t4827;
    Bool _t4828 = Bool_or(_t4825, _t4826);
    (void)_t4828;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4827, _t4828);
    (void)is_lib_target;
    ;
    ;
    U64 _t4829; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4829 = *_hp; free(_hp); }
    (void)_t4829;
    U64 _t4830 = 0;
    (void)_t4830;
    Bool _t4831 = Bool_not(is_lib_target);
    (void)_t4831;
    ;
    Bool _t4832 = U64_eq(_t4829, _t4830);
    (void)_t4832;
    ;
    ;
    Bool _t4833 = Bool_and(_t4831, _t4832);
    (void)_t4833;
    ;
    ;
    if (_t4833) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4834; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4834 = *_hp; free(_hp); }
    (void)_t4834;
    U64 _t4835 = 0;
    (void)_t4835;
    Bool _t4836; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4834}, &(U64){_t4835}); _t4836 = *_hp; free(_hp); }
    (void)_t4836;
    ;
    ;
    if (_t4836) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4837 = Str_lit("Str", 3ULL);
    (void)_t4837;
    U64 _t4838; { U64 *_hp = (U64 *)Str_size(); _t4838 = *_hp; free(_hp); }
    (void)_t4838;
    Vec *user_argv = Vec_new(_t4837, &(U64){_t4838});
    (void)user_argv;
    Str_delete(_t4837, &(Bool){1});
    ;
    U64 _t4839 = 1;
    (void)_t4839;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4839);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4554; { U64 *_hp = (U64 *)Array_len(args); _t4554 = *_hp; free(_hp); }
        (void)_t4554;
        Bool _wcond4538; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4554}); _wcond4538 = *_hp; free(_hp); }
        (void)_wcond4538;
        ;
        if (_wcond4538) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4555 = Str_lit("-l", 2ULL);
        (void)_t4555;
        Bool _t4556; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4555); _t4556 = *_hp; free(_hp); }
        (void)_t4556;
        Str_delete(_t4555, &(Bool){1});
        if (_t4556) {
            U64 _t4541 = 2;
            (void)_t4541;
            U64 _t4542; { U64 *_hp = (U64 *)Str_len(arg); _t4542 = *_hp; free(_hp); }
            (void)_t4542;
            Str *lib = Str_substr(arg, &(U64){_t4541}, &(U64){_t4542});
            (void)lib;
            ;
            ;
            U64 _t4543; { U64 *_hp = (U64 *)Str_len(lib); _t4543 = *_hp; free(_hp); }
            (void)_t4543;
            U64 _t4544 = 0;
            (void)_t4544;
            U64 _t4545 = 1;
            (void)_t4545;
            U64 _t4546 = U64_add(DEREF(ai), _t4545);
            (void)_t4546;
            ;
            U64 _t4547; { U64 *_hp = (U64 *)Array_len(args); _t4547 = *_hp; free(_hp); }
            (void)_t4547;
            Bool _t4548 = U64_eq(_t4543, _t4544);
            (void)_t4548;
            ;
            ;
            Bool _t4549; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4546}, &(U64){_t4547}); _t4549 = *_hp; free(_hp); }
            (void)_t4549;
            ;
            ;
            Bool _t4550 = Bool_and(_t4548, _t4549);
            (void)_t4550;
            ;
            ;
            if (_t4550) {
                U64 _t4539 = 1;
                (void)_t4539;
                U64 _t4540 = U64_add(DEREF(ai), _t4539);
                (void)_t4540;
                ;
                *ai = _t4540;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4551 = Str_lit(" -l", 3ULL);
            (void)_t4551;
            Str *_t4552 = Str_concat(link_flags, _t4551);
            (void)_t4552;
            Str_delete(_t4551, &(Bool){1});
            link_flags = Str_concat(_t4552, lib);
            Str_delete(_t4552, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4553 = Str_clone(arg);
            (void)_t4553;
            Vec_push(user_argv, _t4553);
        }
        ;
        U64 _t4557 = 1;
        (void)_t4557;
        U64 _t4558 = U64_add(DEREF(ai), _t4557);
        (void)_t4558;
        ;
        *ai = _t4558;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4840; { U64 *_hp = (U64 *)Str_len(link_flags); _t4840 = *_hp; free(_hp); }
    (void)_t4840;
    U64 _t4841 = 0;
    (void)_t4841;
    Bool _t4842; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4840}, &(U64){_t4841}); _t4842 = *_hp; free(_hp); }
    (void)_t4842;
    ;
    ;
    if (_t4842) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4843 = Str_lit("interpret", 9ULL);
    (void)_t4843;
    Str *_t4844 = Str_lit("test", 4ULL);
    (void)_t4844;
    Bool _t4845; { Bool *_hp = (Bool *)Str_eq(command, _t4843); _t4845 = *_hp; free(_hp); }
    (void)_t4845;
    Str_delete(_t4843, &(Bool){1});
    Bool _t4846; { Bool *_hp = (Bool *)Str_eq(command, _t4844); _t4846 = *_hp; free(_hp); }
    (void)_t4846;
    Str_delete(_t4844, &(Bool){1});
    Bool _t4847 = Bool_or(_t4845, _t4846);
    (void)_t4847;
    ;
    ;
    if (_t4847) {
        Str *_t4565 = Str_lit("interpret", 9ULL);
        (void)_t4565;
        Bool _t4566; { Bool *_hp = (Bool *)Str_eq(command, _t4565); _t4566 = *_hp; free(_hp); }
        (void)_t4566;
        Str_delete(_t4565, &(Bool){1});
        Bool _t4567 = Bool_and(is_lib_mode, _t4566);
        (void)_t4567;
        ;
        if (_t4567) {
            Str *_t4559 = Str_lit("Str", 3ULL);
            (void)_t4559;
            U64 _t4560; { U64 *_hp = (U64 *)Str_size(); _t4560 = *_hp; free(_hp); }
            (void)_t4560;
            U64 _t4561 = 1;
            (void)_t4561;
            Array *_va87 = Array_new(_t4559, &(U64){_t4560}, &(U64){_t4561});
            (void)_va87;
            Str_delete(_t4559, &(Bool){1});
            ;
            ;
            U64 _t4562 = 0;
            (void)_t4562;
            Str *_t4563 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4563;
            Array_set(_va87, &(U64){_t4562}, _t4563);
            ;
            Str *_t4564 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4564;
            panic(_t4564, _va87);
            Str_delete(_t4564, &(Bool){1});
        }
        ;
        I32 _t4568 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4568;
        result = _t4568;
        ;
    } else {
        Str *_t4761 = Str_lit("translate", 9ULL);
        (void)_t4761;
        Str *_t4762 = Str_lit("build", 5ULL);
        (void)_t4762;
        Bool _t4763; { Bool *_hp = (Bool *)Str_eq(command, _t4761); _t4763 = *_hp; free(_hp); }
        (void)_t4763;
        Str_delete(_t4761, &(Bool){1});
        Bool _t4764; { Bool *_hp = (Bool *)Str_eq(command, _t4762); _t4764 = *_hp; free(_hp); }
        (void)_t4764;
        Str_delete(_t4762, &(Bool){1});
        Str *_t4765 = Str_lit("run", 3ULL);
        (void)_t4765;
        Bool _t4766 = Bool_or(_t4763, _t4764);
        (void)_t4766;
        ;
        ;
        Bool _t4767; { Bool *_hp = (Bool *)Str_eq(command, _t4765); _t4767 = *_hp; free(_hp); }
        (void)_t4767;
        Str_delete(_t4765, &(Bool){1});
        Bool _t4768 = Bool_or(_t4766, _t4767);
        (void)_t4768;
        ;
        ;
        if (_t4768) {
            Str *_t4694 = Str_lit("run", 3ULL);
            (void)_t4694;
            Bool _t4695; { Bool *_hp = (Bool *)Str_eq(command, _t4694); _t4695 = *_hp; free(_hp); }
            (void)_t4695;
            Str_delete(_t4694, &(Bool){1});
            Bool _t4696 = Bool_and(is_lib_mode, _t4695);
            (void)_t4696;
            ;
            if (_t4696) {
                Str *_t4569 = Str_lit("Str", 3ULL);
                (void)_t4569;
                U64 _t4570; { U64 *_hp = (U64 *)Str_size(); _t4570 = *_hp; free(_hp); }
                (void)_t4570;
                U64 _t4571 = 1;
                (void)_t4571;
                Array *_va88 = Array_new(_t4569, &(U64){_t4570}, &(U64){_t4571});
                (void)_va88;
                Str_delete(_t4569, &(Bool){1});
                ;
                ;
                U64 _t4572 = 0;
                (void)_t4572;
                Str *_t4573 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4573;
                Array_set(_va88, &(U64){_t4572}, _t4573);
                ;
                Str *_t4574 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4574;
                panic(_t4574, _va88);
                Str_delete(_t4574, &(Bool){1});
            }
            ;
            Str *_t4697 = Str_lit("/", 1ULL);
            (void)_t4697;
            I64 *last_slash = Str_rfind(path, _t4697);
            (void)last_slash;
            Str_delete(_t4697, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4698 = 0;
            (void)_t4698;
            Bool _t4699; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4698}); _t4699 = *_hp; free(_hp); }
            (void)_t4699;
            ;
            if (_t4699) {
                I64 _t4575 = 1;
                (void)_t4575;
                I64 _t4576 = I64_add(DEREF(last_slash), _t4575);
                (void)_t4576;
                ;
                U64 _t4577; { U64 *_hp = (U64 *)Str_len(path); _t4577 = *_hp; free(_hp); }
                (void)_t4577;
                U64 _t4578 = I64_to_u64(DEREF(last_slash));
                (void)_t4578;
                U64 _t4579 = U64_sub(_t4577, _t4578);
                (void)_t4579;
                ;
                ;
                U64 _t4580 = 1;
                (void)_t4580;
                U64 _t4581 = I64_to_u64(_t4576);
                (void)_t4581;
                ;
                U64 _t4582 = U64_sub(_t4579, _t4580);
                (void)_t4582;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4581}, &(U64){_t4582});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4700 = Str_lit(".til", 4ULL);
            (void)_t4700;
            Bool _t4701; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4700); _t4701 = *_hp; free(_hp); }
            (void)_t4701;
            Str_delete(_t4700, &(Bool){1});
            if (_t4701) {
                U64 _t4583 = 4;
                (void)_t4583;
                U64 _t4584 = U64_sub(name_len, _t4583);
                (void)_t4584;
                ;
                name_len = _t4584;
                ;
            }
            ;
            U64 _t4702 = 0;
            (void)_t4702;
            Str *name = Str_substr(basename, &(U64){_t4702}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4703 = Str_lit("gen/til/", 8ULL);
            (void)_t4703;
            Str *_t4704 = Str_concat(_t4703, name);
            (void)_t4704;
            Str_delete(_t4703, &(Bool){1});
            Str *_t4705 = Str_lit(".c", 2ULL);
            (void)_t4705;
            Str *c_path = Str_concat(_t4704, _t4705);
            (void)c_path;
            Str_delete(_t4704, &(Bool){1});
            Str_delete(_t4705, &(Bool){1});
            U64 _t4706; { U64 *_hp = (U64 *)Str_len(custom_c); _t4706 = *_hp; free(_hp); }
            (void)_t4706;
            U64 _t4707 = 0;
            (void)_t4707;
            Bool _t4708; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4706}, &(U64){_t4707}); _t4708 = *_hp; free(_hp); }
            (void)_t4708;
            ;
            ;
            if (_t4708) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4709 = Str_lit("bin/til/", 8ULL);
            (void)_t4709;
            Str *bin_path = Str_concat(_t4709, name);
            (void)bin_path;
            Str_delete(_t4709, &(Bool){1});
            U64 _t4710; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4710 = *_hp; free(_hp); }
            (void)_t4710;
            U64 _t4711 = 0;
            (void)_t4711;
            Bool _t4712; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4710}, &(U64){_t4711}); _t4712 = *_hp; free(_hp); }
            (void)_t4712;
            ;
            ;
            if (_t4712) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4713 = Str_lit("run", 3ULL);
            (void)_t4713;
            Bool _t4714; { Bool *_hp = (Bool *)Str_eq(command, _t4713); _t4714 = *_hp; free(_hp); }
            (void)_t4714;
            Str_delete(_t4713, &(Bool){1});
            Bool _t4715; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4715 = *_hp; free(_hp); }
            (void)_t4715;
            Bool _t4716 = Bool_not(_t4714);
            (void)_t4716;
            ;
            Bool do_lib = Bool_and(_t4715, _t4716);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4585 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4585;
                I32 _t4586 = til_system(_t4585);
                (void)_t4586;
                Str_delete(_t4585, &(Bool){1});
                ;
            } else {
                Str *_t4591 = Str_lit("/", 1ULL);
                (void)_t4591;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4591); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4591, &(Bool){1});
                Str *_t4592 = Str_lit("/", 1ULL);
                (void)_t4592;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4592); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4592, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4593 = 0;
                (void)_t4593;
                Bool _t4594; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4593}); _t4594 = *_hp; free(_hp); }
                (void)_t4594;
                ;
                if (_t4594) {
                    U64 _t4587 = 0;
                    (void)_t4587;
                    U64 _t4588 = I64_to_u64(cp_slash);
                    (void)_t4588;
                    cp_dir = Str_substr(c_path, &(U64){_t4587}, &(U64){_t4588});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4595 = 0;
                (void)_t4595;
                Bool _t4596; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4595}); _t4596 = *_hp; free(_hp); }
                (void)_t4596;
                ;
                if (_t4596) {
                    U64 _t4589 = 0;
                    (void)_t4589;
                    U64 _t4590 = I64_to_u64(bp_slash);
                    (void)_t4590;
                    bp_dir = Str_substr(bin_path, &(U64){_t4589}, &(U64){_t4590});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4597 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4597;
                Str *_t4598 = Str_concat(_t4597, cp_dir);
                (void)_t4598;
                Str_delete(_t4597, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4599 = Str_lit(" ", 1ULL);
                (void)_t4599;
                Str *_t4600 = Str_concat(_t4598, _t4599);
                (void)_t4600;
                Str_delete(_t4598, &(Bool){1});
                Str_delete(_t4599, &(Bool){1});
                Str *_t4601 = Str_concat(_t4600, bp_dir);
                (void)_t4601;
                Str_delete(_t4600, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4602 = til_system(_t4601);
                (void)_t4602;
                Str_delete(_t4601, &(Bool){1});
                ;
            }
            I32 _t4717 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4717;
            result = _t4717;
            ;
            I32 _t4718 = 0;
            (void)_t4718;
            Bool _t4719 = I32_eq(result, _t4718);
            (void)_t4719;
            ;
            Bool _t4720 = Bool_and(_t4719, do_lib);
            (void)_t4720;
            ;
            if (_t4720) {
                Str *_t4659 = Str_lit("gen/til/", 8ULL);
                (void)_t4659;
                Str *_t4660 = Str_concat(_t4659, name);
                (void)_t4660;
                Str_delete(_t4659, &(Bool){1});
                Str *_t4661 = Str_lit(".h", 2ULL);
                (void)_t4661;
                Str *h_path = Str_concat(_t4660, _t4661);
                (void)h_path;
                Str_delete(_t4660, &(Bool){1});
                Str_delete(_t4661, &(Bool){1});
                Str *_t4662 = Str_lit("gen/til/", 8ULL);
                (void)_t4662;
                Str *_t4663 = Str_concat(_t4662, name);
                (void)_t4663;
                Str_delete(_t4662, &(Bool){1});
                Str *_t4664 = Str_lit(".til", 4ULL);
                (void)_t4664;
                Str *til_path = Str_concat(_t4663, _t4664);
                (void)til_path;
                Str_delete(_t4663, &(Bool){1});
                Str_delete(_t4664, &(Bool){1});
                I32 _t4665 = build_header(ast, h_path);
                (void)_t4665;
                result = _t4665;
                ;
                I32 _t4666 = 0;
                (void)_t4666;
                Bool _t4667 = I32_eq(result, _t4666);
                (void)_t4667;
                ;
                if (_t4667) {
                    I32 _t4603 = build_til_binding(ast, til_path, name);
                    (void)_t4603;
                    result = _t4603;
                    ;
                }
                ;
                I32 _t4668 = 0;
                (void)_t4668;
                Str *_t4669 = Str_lit("translate", 9ULL);
                (void)_t4669;
                Bool _t4670 = I32_eq(result, _t4668);
                (void)_t4670;
                ;
                Bool _t4671; { Bool *_hp = (Bool *)Str_eq(command, _t4669); _t4671 = *_hp; free(_hp); }
                (void)_t4671;
                Str_delete(_t4669, &(Bool){1});
                Bool _t4672 = Bool_and(_t4670, _t4671);
                (void)_t4672;
                ;
                ;
                if (_t4672) {
                    Str *_t4604 = Str_lit("Str", 3ULL);
                    (void)_t4604;
                    U64 _t4605; { U64 *_hp = (U64 *)Str_size(); _t4605 = *_hp; free(_hp); }
                    (void)_t4605;
                    U64 _t4606 = 1;
                    (void)_t4606;
                    Array *_va89 = Array_new(_t4604, &(U64){_t4605}, &(U64){_t4606});
                    (void)_va89;
                    Str_delete(_t4604, &(Bool){1});
                    ;
                    ;
                    Str *_t4607 = Str_lit("Generated: ", 11ULL);
                    (void)_t4607;
                    U64 _t4608 = 0;
                    (void)_t4608;
                    Str *_t4609 = Str_concat(_t4607, c_path);
                    (void)_t4609;
                    Str_delete(_t4607, &(Bool){1});
                    Array_set(_va89, &(U64){_t4608}, _t4609);
                    ;
                    println(_va89);
                    Str *_t4610 = Str_lit("Str", 3ULL);
                    (void)_t4610;
                    U64 _t4611; { U64 *_hp = (U64 *)Str_size(); _t4611 = *_hp; free(_hp); }
                    (void)_t4611;
                    U64 _t4612 = 1;
                    (void)_t4612;
                    Array *_va90 = Array_new(_t4610, &(U64){_t4611}, &(U64){_t4612});
                    (void)_va90;
                    Str_delete(_t4610, &(Bool){1});
                    ;
                    ;
                    Str *_t4613 = Str_lit("Generated: ", 11ULL);
                    (void)_t4613;
                    U64 _t4614 = 0;
                    (void)_t4614;
                    Str *_t4615 = Str_concat(_t4613, h_path);
                    (void)_t4615;
                    Str_delete(_t4613, &(Bool){1});
                    Array_set(_va90, &(U64){_t4614}, _t4615);
                    ;
                    println(_va90);
                    Str *_t4616 = Str_lit("Str", 3ULL);
                    (void)_t4616;
                    U64 _t4617; { U64 *_hp = (U64 *)Str_size(); _t4617 = *_hp; free(_hp); }
                    (void)_t4617;
                    U64 _t4618 = 1;
                    (void)_t4618;
                    Array *_va91 = Array_new(_t4616, &(U64){_t4617}, &(U64){_t4618});
                    (void)_va91;
                    Str_delete(_t4616, &(Bool){1});
                    ;
                    ;
                    Str *_t4619 = Str_lit("Generated: ", 11ULL);
                    (void)_t4619;
                    U64 _t4620 = 0;
                    (void)_t4620;
                    Str *_t4621 = Str_concat(_t4619, til_path);
                    (void)_t4621;
                    Str_delete(_t4619, &(Bool){1});
                    Array_set(_va91, &(U64){_t4620}, _t4621);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4673 = 0;
                (void)_t4673;
                Str *_t4674 = Str_lit("build", 5ULL);
                (void)_t4674;
                Bool _t4675 = I32_eq(result, _t4673);
                (void)_t4675;
                ;
                Bool _t4676; { Bool *_hp = (Bool *)Str_eq(command, _t4674); _t4676 = *_hp; free(_hp); }
                (void)_t4676;
                Str_delete(_t4674, &(Bool){1});
                Bool _t4677 = Bool_and(_t4675, _t4676);
                (void)_t4677;
                ;
                ;
                if (_t4677) {
                    I32 _t4656 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4656;
                    result = _t4656;
                    ;
                    I32 _t4657 = 0;
                    (void)_t4657;
                    Bool _t4658 = I32_eq(result, _t4657);
                    (void)_t4658;
                    ;
                    if (_t4658) {
                        Str *_t4622 = Str_lit("Str", 3ULL);
                        (void)_t4622;
                        U64 _t4623; { U64 *_hp = (U64 *)Str_size(); _t4623 = *_hp; free(_hp); }
                        (void)_t4623;
                        U64 _t4624 = 1;
                        (void)_t4624;
                        Array *_va92 = Array_new(_t4622, &(U64){_t4623}, &(U64){_t4624});
                        (void)_va92;
                        Str_delete(_t4622, &(Bool){1});
                        ;
                        ;
                        Str *_t4625 = Str_lit("Generated: ", 11ULL);
                        (void)_t4625;
                        U64 _t4626 = 0;
                        (void)_t4626;
                        Str *_t4627 = Str_concat(_t4625, c_path);
                        (void)_t4627;
                        Str_delete(_t4625, &(Bool){1});
                        Array_set(_va92, &(U64){_t4626}, _t4627);
                        ;
                        println(_va92);
                        Str *_t4628 = Str_lit("Str", 3ULL);
                        (void)_t4628;
                        U64 _t4629; { U64 *_hp = (U64 *)Str_size(); _t4629 = *_hp; free(_hp); }
                        (void)_t4629;
                        U64 _t4630 = 1;
                        (void)_t4630;
                        Array *_va93 = Array_new(_t4628, &(U64){_t4629}, &(U64){_t4630});
                        (void)_va93;
                        Str_delete(_t4628, &(Bool){1});
                        ;
                        ;
                        Str *_t4631 = Str_lit("Generated: ", 11ULL);
                        (void)_t4631;
                        U64 _t4632 = 0;
                        (void)_t4632;
                        Str *_t4633 = Str_concat(_t4631, h_path);
                        (void)_t4633;
                        Str_delete(_t4631, &(Bool){1});
                        Array_set(_va93, &(U64){_t4632}, _t4633);
                        ;
                        println(_va93);
                        Str *_t4634 = Str_lit("Str", 3ULL);
                        (void)_t4634;
                        U64 _t4635; { U64 *_hp = (U64 *)Str_size(); _t4635 = *_hp; free(_hp); }
                        (void)_t4635;
                        U64 _t4636 = 1;
                        (void)_t4636;
                        Array *_va94 = Array_new(_t4634, &(U64){_t4635}, &(U64){_t4636});
                        (void)_va94;
                        Str_delete(_t4634, &(Bool){1});
                        ;
                        ;
                        Str *_t4637 = Str_lit("Generated: ", 11ULL);
                        (void)_t4637;
                        U64 _t4638 = 0;
                        (void)_t4638;
                        Str *_t4639 = Str_concat(_t4637, til_path);
                        (void)_t4639;
                        Str_delete(_t4637, &(Bool){1});
                        Array_set(_va94, &(U64){_t4638}, _t4639);
                        ;
                        println(_va94);
                        Str *_t4640 = Str_lit("Str", 3ULL);
                        (void)_t4640;
                        U64 _t4641; { U64 *_hp = (U64 *)Str_size(); _t4641 = *_hp; free(_hp); }
                        (void)_t4641;
                        U64 _t4642 = 1;
                        (void)_t4642;
                        Array *_va95 = Array_new(_t4640, &(U64){_t4641}, &(U64){_t4642});
                        (void)_va95;
                        Str_delete(_t4640, &(Bool){1});
                        ;
                        ;
                        Str *_t4643 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4643;
                        Str *_t4644 = Str_concat(_t4643, name);
                        (void)_t4644;
                        Str_delete(_t4643, &(Bool){1});
                        Str *_t4645 = Str_lit(".so", 3ULL);
                        (void)_t4645;
                        U64 _t4646 = 0;
                        (void)_t4646;
                        Str *_t4647 = Str_concat(_t4644, _t4645);
                        (void)_t4647;
                        Str_delete(_t4644, &(Bool){1});
                        Str_delete(_t4645, &(Bool){1});
                        Array_set(_va95, &(U64){_t4646}, _t4647);
                        ;
                        println(_va95);
                        Str *_t4648 = Str_lit("Str", 3ULL);
                        (void)_t4648;
                        U64 _t4649; { U64 *_hp = (U64 *)Str_size(); _t4649 = *_hp; free(_hp); }
                        (void)_t4649;
                        U64 _t4650 = 1;
                        (void)_t4650;
                        Array *_va96 = Array_new(_t4648, &(U64){_t4649}, &(U64){_t4650});
                        (void)_va96;
                        Str_delete(_t4648, &(Bool){1});
                        ;
                        ;
                        Str *_t4651 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4651;
                        Str *_t4652 = Str_concat(_t4651, name);
                        (void)_t4652;
                        Str_delete(_t4651, &(Bool){1});
                        Str *_t4653 = Str_lit(".a", 2ULL);
                        (void)_t4653;
                        U64 _t4654 = 0;
                        (void)_t4654;
                        Str *_t4655 = Str_concat(_t4652, _t4653);
                        (void)_t4655;
                        Str_delete(_t4652, &(Bool){1});
                        Str_delete(_t4653, &(Bool){1});
                        Array_set(_va96, &(U64){_t4654}, _t4655);
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
            I32 _t4721 = 0;
            (void)_t4721;
            Bool _t4722 = I32_eq(result, _t4721);
            (void)_t4722;
            ;
            Bool _t4723 = Bool_not(do_lib);
            (void)_t4723;
            Str *_t4724 = Str_lit("translate", 9ULL);
            (void)_t4724;
            Bool _t4725 = Bool_and(_t4722, _t4723);
            (void)_t4725;
            ;
            ;
            Bool _t4726; { Bool *_hp = (Bool *)Str_eq(command, _t4724); _t4726 = *_hp; free(_hp); }
            (void)_t4726;
            Str_delete(_t4724, &(Bool){1});
            Bool _t4727 = Bool_and(_t4725, _t4726);
            (void)_t4727;
            ;
            ;
            if (_t4727) {
                Str *_t4678 = Str_lit("Str", 3ULL);
                (void)_t4678;
                U64 _t4679; { U64 *_hp = (U64 *)Str_size(); _t4679 = *_hp; free(_hp); }
                (void)_t4679;
                U64 _t4680 = 1;
                (void)_t4680;
                Array *_va97 = Array_new(_t4678, &(U64){_t4679}, &(U64){_t4680});
                (void)_va97;
                Str_delete(_t4678, &(Bool){1});
                ;
                ;
                Str *_t4681 = Str_lit("Generated: ", 11ULL);
                (void)_t4681;
                U64 _t4682 = 0;
                (void)_t4682;
                Str *_t4683 = Str_concat(_t4681, c_path);
                (void)_t4683;
                Str_delete(_t4681, &(Bool){1});
                Array_set(_va97, &(U64){_t4682}, _t4683);
                ;
                println(_va97);
            }
            ;
            I32 _t4728 = 0;
            (void)_t4728;
            Bool _t4729 = I32_eq(result, _t4728);
            (void)_t4729;
            ;
            Bool _t4730 = Bool_not(do_lib);
            (void)_t4730;
            Str *_t4731 = Str_lit("translate", 9ULL);
            (void)_t4731;
            Bool _t4732; { Bool *_hp = (Bool *)Str_eq(command, _t4731); _t4732 = *_hp; free(_hp); }
            (void)_t4732;
            Str_delete(_t4731, &(Bool){1});
            Bool _t4733 = Bool_and(_t4729, _t4730);
            (void)_t4733;
            ;
            ;
            Bool _t4734 = Bool_not(_t4732);
            (void)_t4734;
            ;
            Bool _t4735 = Bool_and(_t4733, _t4734);
            (void)_t4735;
            ;
            ;
            if (_t4735) {
                I32 _t4684 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4684;
                result = _t4684;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4736 = 0;
            (void)_t4736;
            Bool _t4737 = I32_eq(result, _t4736);
            (void)_t4737;
            ;
            Bool _t4738 = Bool_not(do_lib);
            (void)_t4738;
            ;
            Str *_t4739 = Str_lit("run", 3ULL);
            (void)_t4739;
            Bool _t4740 = Bool_and(_t4737, _t4738);
            (void)_t4740;
            ;
            ;
            Bool _t4741; { Bool *_hp = (Bool *)Str_eq(command, _t4739); _t4741 = *_hp; free(_hp); }
            (void)_t4741;
            Str_delete(_t4739, &(Bool){1});
            Bool _t4742 = Bool_and(_t4740, _t4741);
            (void)_t4742;
            ;
            ;
            if (_t4742) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4686; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4686 = *_hp; free(_hp); }
                    (void)_t4686;
                    Bool _wcond4685; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4686}); _wcond4685 = *_hp; free(_hp); }
                    (void)_wcond4685;
                    ;
                    if (_wcond4685) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4687 = Str_lit(" '", 2ULL);
                    (void)_t4687;
                    Str *_t4688 = Str_concat(cmd, _t4687);
                    (void)_t4688;
                    Str_delete(_t4687, &(Bool){1});
                    Str *_t4689 = Str_concat(_t4688, uarg);
                    (void)_t4689;
                    Str_delete(_t4688, &(Bool){1});
                    Str *_t4690 = Str_lit("'", 1ULL);
                    (void)_t4690;
                    cmd = Str_concat(_t4689, _t4690);
                    Str_delete(_t4689, &(Bool){1});
                    Str_delete(_t4690, &(Bool){1});
                    U64 _t4691 = 1;
                    (void)_t4691;
                    U64 _t4692 = U64_add(DEREF(ui), _t4691);
                    (void)_t4692;
                    ;
                    *ui = _t4692;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4693 = til_system(cmd);
                (void)_t4693;
                Str_delete(cmd, &(Bool){1});
                result = _t4693;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4759 = Str_lit("ast", 3ULL);
            (void)_t4759;
            Bool _t4760; { Bool *_hp = (Bool *)Str_eq(command, _t4759); _t4760 = *_hp; free(_hp); }
            (void)_t4760;
            Str_delete(_t4759, &(Bool){1});
            if (_t4760) {
                Str *_t4743 = Str_lit("Str", 3ULL);
                (void)_t4743;
                U64 _t4744; { U64 *_hp = (U64 *)Str_size(); _t4744 = *_hp; free(_hp); }
                (void)_t4744;
                U64 _t4745 = 1;
                (void)_t4745;
                Array *_va98 = Array_new(_t4743, &(U64){_t4744}, &(U64){_t4745});
                (void)_va98;
                Str_delete(_t4743, &(Bool){1});
                ;
                ;
                Str *_t4746 = Str_lit("mode: ", 6ULL);
                (void)_t4746;
                U64 _t4747 = 0;
                (void)_t4747;
                Str *_t4748 = Str_concat(_t4746, &cur_mode->name);
                (void)_t4748;
                Str_delete(_t4746, &(Bool){1});
                Array_set(_va98, &(U64){_t4747}, _t4748);
                ;
                println(_va98);
                U32 _t4749 = 0;
                (void)_t4749;
                ast_print(ast, _t4749);
                ;
            } else {
                Str *_t4750 = Str_lit("Str", 3ULL);
                (void)_t4750;
                U64 _t4751; { U64 *_hp = (U64 *)Str_size(); _t4751 = *_hp; free(_hp); }
                (void)_t4751;
                U64 _t4752 = 1;
                (void)_t4752;
                Array *_va99 = Array_new(_t4750, &(U64){_t4751}, &(U64){_t4752});
                (void)_va99;
                Str_delete(_t4750, &(Bool){1});
                ;
                ;
                Str *_t4753 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4753;
                Str *_t4754 = Str_concat(_t4753, command);
                (void)_t4754;
                Str_delete(_t4753, &(Bool){1});
                Str *_t4755 = Str_lit("'", 1ULL);
                (void)_t4755;
                U64 _t4756 = 0;
                (void)_t4756;
                Str *_t4757 = Str_concat(_t4754, _t4755);
                (void)_t4757;
                Str_delete(_t4754, &(Bool){1});
                Str_delete(_t4755, &(Bool){1});
                Array_set(_va99, &(U64){_t4756}, _t4757);
                ;
                println(_va99);
                usage();
                I32 _t4758 = 1;
                (void)_t4758;
                result = _t4758;
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
    I64 _t4848 = I32_to_i64(result);
    (void)_t4848;
    ;
    exit(_t4848);
    ;
    return 0;
}

