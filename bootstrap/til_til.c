#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4278 = Str_lit("Str", 3ULL);
    (void)_t4278;
    U64 _t4279; { U64 *_hp = (U64 *)Str_size(); _t4279 = *_hp; free(_hp); }
    (void)_t4279;
    Vec *paths = Vec_new(_t4278, &(U64){_t4279});
    (void)paths;
    Str_delete(_t4278, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4253 = expr_nchildren(body);
        (void)_t4253;
        Bool _wcond4249; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4253}); _wcond4249 = *_hp; free(_hp); }
        (void)_wcond4249;
        ;
        if (_wcond4249) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4254 = expr_get_tag(stmt);
        (void)_t4254;
        U32 _t4255 = expr_nchildren(stmt);
        (void)_t4255;
        U32 _t4256 = 2;
        (void)_t4256;
        Bool _t4257 = I32_eq(_t4254, DEREF(NODE_FCALL));
        (void)_t4257;
        ;
        Bool _t4258 = U32_eq(_t4255, _t4256);
        (void)_t4258;
        ;
        ;
        U32 *_t4259 = malloc(sizeof(U32));
        *_t4259 = 0;
        (void)_t4259;
        Expr *_t4260 = expr_get_child(stmt, DEREF(_t4259));
        (void)_t4260;
        I32 _t4261 = expr_get_tag(_t4260);
        (void)_t4261;
        U32_delete(_t4259, &(Bool){1});
        Bool _t4262 = Bool_and(_t4257, _t4258);
        (void)_t4262;
        ;
        ;
        Bool _t4263 = I32_eq(_t4261, DEREF(NODE_IDENT));
        (void)_t4263;
        ;
        U32 *_t4264 = malloc(sizeof(U32));
        *_t4264 = 0;
        (void)_t4264;
        Expr *_t4265 = expr_get_child(stmt, DEREF(_t4264));
        (void)_t4265;
        Str *_t4266 = expr_get_str_val(_t4265);
        (void)_t4266;
        Str *_t4267 = Str_lit("import", 6ULL);
        (void)_t4267;
        Bool _t4268 = Bool_and(_t4262, _t4263);
        (void)_t4268;
        ;
        ;
        Bool _t4269; { Bool *_hp = (Bool *)Str_eq(_t4266, _t4267); _t4269 = *_hp; free(_hp); }
        (void)_t4269;
        U32_delete(_t4264, &(Bool){1});
        Str_delete(_t4267, &(Bool){1});
        U32 *_t4270 = malloc(sizeof(U32));
        *_t4270 = 1;
        (void)_t4270;
        Expr *_t4271 = expr_get_child(stmt, DEREF(_t4270));
        (void)_t4271;
        I32 _t4272 = expr_get_tag(_t4271);
        (void)_t4272;
        U32_delete(_t4270, &(Bool){1});
        Bool _t4273 = Bool_and(_t4268, _t4269);
        (void)_t4273;
        ;
        ;
        Bool _t4274 = I32_eq(_t4272, DEREF(NODE_LITERAL_STR));
        (void)_t4274;
        ;
        Bool _t4275 = Bool_and(_t4273, _t4274);
        (void)_t4275;
        ;
        ;
        if (_t4275) {
            U32 *_t4250 = malloc(sizeof(U32));
            *_t4250 = 1;
            (void)_t4250;
            Expr *_t4251 = expr_get_child(stmt, DEREF(_t4250));
            (void)_t4251;
            Str *path = expr_get_str_val(_t4251);
            (void)path;
            Str *_t4252 = Str_clone(path);
            (void)_t4252;
            U32_delete(_t4250, &(Bool){1});
            Vec_push(paths, _t4252);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4276 = 1;
        (void)_t4276;
        U32 _t4277 = U32_add(DEREF(i), _t4276);
        (void)_t4277;
        ;
        *i = _t4277;
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
        U64 _fi4280 = 0;
        (void)_fi4280;
        while (1) {
            U64 _t4310 = 0;
            (void)_t4310;
            U64 _t4311; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4311 = *_hp; free(_hp); }
            (void)_t4311;
            Range *_t4312 = Range_new(_t4310, _t4311);
            (void)_t4312;
            ;
            ;
            U64 _t4313; { U64 *_hp = (U64 *)Range_len(_t4312); _t4313 = *_hp; free(_hp); }
            (void)_t4313;
            Range_delete(_t4312, &(Bool){1});
            Bool _wcond4281; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4280}, &(U64){_t4313}); _wcond4281 = *_hp; free(_hp); }
            (void)_wcond4281;
            ;
            if (_wcond4281) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4314 = 0;
            (void)_t4314;
            U64 _t4315; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4315 = *_hp; free(_hp); }
            (void)_t4315;
            Range *_t4316 = Range_new(_t4314, _t4315);
            (void)_t4316;
            ;
            ;
            U64 *i = Range_get(_t4316, _fi4280);
            (void)i;
            Range_delete(_t4316, &(Bool){1});
            U64 _t4317 = 1;
            (void)_t4317;
            U64 _t4318 = U64_add(_fi4280, _t4317);
            (void)_t4318;
            ;
            _fi4280 = _t4318;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4319 = Str_lit("/", 1ULL);
            (void)_t4319;
            Str *_t4320 = Str_concat(base_dir, _t4319);
            (void)_t4320;
            Str_delete(_t4319, &(Bool){1});
            Str *try_path = Str_concat(_t4320, import_path);
            (void)try_path;
            Str_delete(_t4320, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4321 = Str_lit("", 0ULL);
            (void)_t4321;
            U64 _t4322; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4322 = *_hp; free(_hp); }
            (void)_t4322;
            U64 _t4323 = 0;
            (void)_t4323;
            Bool _t4324; { Bool *_hp = (Bool *)Str_eq(abs, _t4321); _t4324 = *_hp; free(_hp); }
            (void)_t4324;
            Str_delete(_t4321, &(Bool){1});
            Bool _t4325; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4322}, &(U64){_t4323}); _t4325 = *_hp; free(_hp); }
            (void)_t4325;
            ;
            ;
            Bool _t4326 = Bool_and(_t4324, _t4325);
            (void)_t4326;
            ;
            ;
            if (_t4326) {
                Str *_t4282 = Str_lit("/", 1ULL);
                (void)_t4282;
                Str *_t4283 = Str_concat(lib_dir, _t4282);
                (void)_t4283;
                Str_delete(_t4282, &(Bool){1});
                try_path = Str_concat(_t4283, import_path);
                Str_delete(_t4283, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4327 = Str_lit("", 0ULL);
            (void)_t4327;
            Bool _t4328; { Bool *_hp = (Bool *)Str_eq(abs, _t4327); _t4328 = *_hp; free(_hp); }
            (void)_t4328;
            Str_delete(_t4327, &(Bool){1});
            if (_t4328) {
                Str *_t4284 = Str_lit("Str", 3ULL);
                (void)_t4284;
                U64 _t4285; { U64 *_hp = (U64 *)Str_size(); _t4285 = *_hp; free(_hp); }
                (void)_t4285;
                U64 _t4286 = 1;
                (void)_t4286;
                Array *_va72 = Array_new(_t4284, &(U64){_t4285}, &(U64){_t4286});
                (void)_va72;
                Str_delete(_t4284, &(Bool){1});
                ;
                ;
                Str *_t4287 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4287;
                Str *_t4288 = Str_concat(_t4287, import_path);
                (void)_t4288;
                Str_delete(_t4287, &(Bool){1});
                Str *_t4289 = Str_lit("' (from ", 8ULL);
                (void)_t4289;
                Str *_t4290 = Str_concat(_t4288, _t4289);
                (void)_t4290;
                Str_delete(_t4288, &(Bool){1});
                Str_delete(_t4289, &(Bool){1});
                Str *_t4291 = Str_concat(_t4290, base_dir);
                (void)_t4291;
                Str_delete(_t4290, &(Bool){1});
                Str *_t4292 = Str_lit("/)", 2ULL);
                (void)_t4292;
                U64 _t4293 = 0;
                (void)_t4293;
                Str *_t4294 = Str_concat(_t4291, _t4292);
                (void)_t4294;
                Str_delete(_t4291, &(Bool){1});
                Str_delete(_t4292, &(Bool){1});
                Array_set(_va72, &(U64){_t4293}, _t4294);
                ;
                println(_va72);
                I64 _t4295 = 1;
                (void)_t4295;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4295; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4329; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4329 = *_hp; free(_hp); }
            (void)_t4329;
            if (_t4329) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4330 = Str_clone(abs);
            (void)_t4330;
            Set_add(resolved_set, _t4330);
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
            U64 _t4331; { U64 *_hp = (U64 *)Str_len(abs); _t4331 = *_hp; free(_hp); }
            (void)_t4331;
            U64 _t4332 = 1;
            (void)_t4332;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4331, _t4332);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4297 = 0;
                (void)_t4297;
                U8 *_t4298 = Str_get(abs, last_slash);
                (void)_t4298;
                U8 _t4299 = 47;
                (void)_t4299;
                Bool _t4300; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4297}); _t4300 = *_hp; free(_hp); }
                (void)_t4300;
                ;
                Bool _t4301; { Bool *_hp = (Bool *)U8_neq(_t4298, &(U8){_t4299}); _t4301 = *_hp; free(_hp); }
                (void)_t4301;
                ;
                Bool _wcond4296 = Bool_and(_t4300, _t4301);
                (void)_wcond4296;
                ;
                ;
                if (_wcond4296) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4302 = 1;
                (void)_t4302;
                U64 _t4303 = U64_sub(DEREF(last_slash), _t4302);
                (void)_t4303;
                ;
                *last_slash = _t4303;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4333; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4333 = *_hp; free(_hp); }
            (void)_t4333;
            U64 _t4334 = 0;
            (void)_t4334;
            Bool _t4335; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4333}, &(U64){_t4334}); _t4335 = *_hp; free(_hp); }
            (void)_t4335;
            ;
            ;
            if (_t4335) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4304 = 0;
                (void)_t4304;
                Bool _t4305; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4304}); _t4305 = *_hp; free(_hp); }
                (void)_t4305;
                ;
                if (_t4305) {
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
                U32 _t4307 = expr_nchildren(sub_ast);
                (void)_t4307;
                Bool _wcond4306; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4307}); _wcond4306 = *_hp; free(_hp); }
                (void)_wcond4306;
                ;
                if (_wcond4306) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4308 = 1;
                (void)_t4308;
                U32 _t4309 = U32_add(DEREF(k), _t4308);
                (void)_t4309;
                ;
                *k = _t4309;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t4336 = 0;
    (void)_t4336;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4336; return _r; }
}

void usage(void) {
    Str *_t4337 = Str_lit("Str", 3ULL);
    (void)_t4337;
    U64 _t4338; { U64 *_hp = (U64 *)Str_size(); _t4338 = *_hp; free(_hp); }
    (void)_t4338;
    U64 _t4339 = 1;
    (void)_t4339;
    Array *_va73 = Array_new(_t4337, &(U64){_t4338}, &(U64){_t4339});
    (void)_va73;
    Str_delete(_t4337, &(Bool){1});
    ;
    ;
    U64 _t4340 = 0;
    (void)_t4340;
    Str *_t4341 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4341;
    Array_set(_va73, &(U64){_t4340}, _t4341);
    ;
    println(_va73);
    Str *_t4342 = Str_lit("Str", 3ULL);
    (void)_t4342;
    U64 _t4343; { U64 *_hp = (U64 *)Str_size(); _t4343 = *_hp; free(_hp); }
    (void)_t4343;
    U64 _t4344 = 1;
    (void)_t4344;
    Array *_va74 = Array_new(_t4342, &(U64){_t4343}, &(U64){_t4344});
    (void)_va74;
    Str_delete(_t4342, &(Bool){1});
    ;
    ;
    U64 _t4345 = 0;
    (void)_t4345;
    Str *_t4346 = Str_lit("", 0ULL);
    (void)_t4346;
    Array_set(_va74, &(U64){_t4345}, _t4346);
    ;
    println(_va74);
    Str *_t4347 = Str_lit("Str", 3ULL);
    (void)_t4347;
    U64 _t4348; { U64 *_hp = (U64 *)Str_size(); _t4348 = *_hp; free(_hp); }
    (void)_t4348;
    U64 _t4349 = 1;
    (void)_t4349;
    Array *_va75 = Array_new(_t4347, &(U64){_t4348}, &(U64){_t4349});
    (void)_va75;
    Str_delete(_t4347, &(Bool){1});
    ;
    ;
    U64 _t4350 = 0;
    (void)_t4350;
    Str *_t4351 = Str_lit("Commands:", 9ULL);
    (void)_t4351;
    Array_set(_va75, &(U64){_t4350}, _t4351);
    ;
    println(_va75);
    Str *_t4352 = Str_lit("Str", 3ULL);
    (void)_t4352;
    U64 _t4353; { U64 *_hp = (U64 *)Str_size(); _t4353 = *_hp; free(_hp); }
    (void)_t4353;
    U64 _t4354 = 1;
    (void)_t4354;
    Array *_va76 = Array_new(_t4352, &(U64){_t4353}, &(U64){_t4354});
    (void)_va76;
    Str_delete(_t4352, &(Bool){1});
    ;
    ;
    U64 _t4355 = 0;
    (void)_t4355;
    Str *_t4356 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4356;
    Array_set(_va76, &(U64){_t4355}, _t4356);
    ;
    println(_va76);
    Str *_t4357 = Str_lit("Str", 3ULL);
    (void)_t4357;
    U64 _t4358; { U64 *_hp = (U64 *)Str_size(); _t4358 = *_hp; free(_hp); }
    (void)_t4358;
    U64 _t4359 = 1;
    (void)_t4359;
    Array *_va77 = Array_new(_t4357, &(U64){_t4358}, &(U64){_t4359});
    (void)_va77;
    Str_delete(_t4357, &(Bool){1});
    ;
    ;
    U64 _t4360 = 0;
    (void)_t4360;
    Str *_t4361 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4361;
    Array_set(_va77, &(U64){_t4360}, _t4361);
    ;
    println(_va77);
    Str *_t4362 = Str_lit("Str", 3ULL);
    (void)_t4362;
    U64 _t4363; { U64 *_hp = (U64 *)Str_size(); _t4363 = *_hp; free(_hp); }
    (void)_t4363;
    U64 _t4364 = 1;
    (void)_t4364;
    Array *_va78 = Array_new(_t4362, &(U64){_t4363}, &(U64){_t4364});
    (void)_va78;
    Str_delete(_t4362, &(Bool){1});
    ;
    ;
    U64 _t4365 = 0;
    (void)_t4365;
    Str *_t4366 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4366;
    Array_set(_va78, &(U64){_t4365}, _t4366);
    ;
    println(_va78);
    Str *_t4367 = Str_lit("Str", 3ULL);
    (void)_t4367;
    U64 _t4368; { U64 *_hp = (U64 *)Str_size(); _t4368 = *_hp; free(_hp); }
    (void)_t4368;
    U64 _t4369 = 1;
    (void)_t4369;
    Array *_va79 = Array_new(_t4367, &(U64){_t4368}, &(U64){_t4369});
    (void)_va79;
    Str_delete(_t4367, &(Bool){1});
    ;
    ;
    U64 _t4370 = 0;
    (void)_t4370;
    Str *_t4371 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4371;
    Array_set(_va79, &(U64){_t4370}, _t4371);
    ;
    println(_va79);
    Str *_t4372 = Str_lit("Str", 3ULL);
    (void)_t4372;
    U64 _t4373; { U64 *_hp = (U64 *)Str_size(); _t4373 = *_hp; free(_hp); }
    (void)_t4373;
    U64 _t4374 = 1;
    (void)_t4374;
    Array *_va80 = Array_new(_t4372, &(U64){_t4373}, &(U64){_t4374});
    (void)_va80;
    Str_delete(_t4372, &(Bool){1});
    ;
    ;
    U64 _t4375 = 0;
    (void)_t4375;
    Str *_t4376 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4376;
    Array_set(_va80, &(U64){_t4375}, _t4376);
    ;
    println(_va80);
    Str *_t4377 = Str_lit("Str", 3ULL);
    (void)_t4377;
    U64 _t4378; { U64 *_hp = (U64 *)Str_size(); _t4378 = *_hp; free(_hp); }
    (void)_t4378;
    U64 _t4379 = 1;
    (void)_t4379;
    Array *_va81 = Array_new(_t4377, &(U64){_t4378}, &(U64){_t4379});
    (void)_va81;
    Str_delete(_t4377, &(Bool){1});
    ;
    ;
    U64 _t4380 = 0;
    (void)_t4380;
    Str *_t4381 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4381;
    Array_set(_va81, &(U64){_t4380}, _t4381);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4387 = 1;
    (void)_t4387;
    e->is_core = _t4387;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4383 = expr_nchildren(e);
        (void)_t4383;
        Bool _wcond4382; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4383}); _wcond4382 = *_hp; free(_hp); }
        (void)_wcond4382;
        ;
        if (_wcond4382) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4384 = expr_get_child(e, DEREF(i));
        (void)_t4384;
        mark_core(_t4384);
        U32 _t4385 = 1;
        (void)_t4385;
        U32 _t4386 = U32_add(DEREF(i), _t4385);
        (void)_t4386;
        ;
        *i = _t4386;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4847 = malloc(sizeof(I64));
    *_t4847 = 0;
    (void)_t4847;
    _t4848 = malloc(sizeof(I64));
    *_t4848 = 1;
    (void)_t4848;
    _t4849 = malloc(sizeof(I64)); *_t4849 = I64_sub(DEREF(_t4847), DEREF(_t4848));
    (void)_t4849;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4849));
    (void)CAP_LIT;
    _t4850 = malloc(sizeof(I64));
    *_t4850 = 0;
    (void)_t4850;
    _t4851 = malloc(sizeof(I64));
    *_t4851 = 2;
    (void)_t4851;
    _t4852 = malloc(sizeof(I64)); *_t4852 = I64_sub(DEREF(_t4850), DEREF(_t4851));
    (void)_t4852;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4852));
    (void)CAP_VIEW;
    _t4853 = Str_lit("Str", 3ULL);
    (void)_t4853;
    _t4854 = Str_size();
    (void)_t4854;
    _t4855 = Str_lit("Mode", 4ULL);
    (void)_t4855;
    _t4856 = Mode_size();
    (void)_t4856;
    core_modes = Map_new(_t4853, _t4854, _t4855, _t4856);
    (void)core_modes;
    _t4857 = malloc(sizeof(Bool));
    *_t4857 = 0;
    (void)_t4857;
    _t4858 = malloc(sizeof(Bool));
    *_t4858 = 0;
    (void)_t4858;
    _t4859 = malloc(sizeof(Bool));
    *_t4859 = 0;
    (void)_t4859;
    _t4860 = malloc(sizeof(Bool));
    *_t4860 = 0;
    (void)_t4860;
    _t4861 = Str_lit("script", 6ULL);
    (void)_t4861;
    _t4862 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4862->name = *_ca; free(_ca); }
    _t4862->needs_main = DEREF(_t4857);
    _t4862->decls_only = DEREF(_t4858);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4862->auto_import = *_ca; free(_ca); }
    _t4862->is_pure = DEREF(_t4859);
    _t4862->debug_prints = DEREF(_t4860);
    (void)_t4862;
    _t4863 = malloc(sizeof(Bool));
    *_t4863 = 1;
    (void)_t4863;
    _t4864 = malloc(sizeof(Bool));
    *_t4864 = 1;
    (void)_t4864;
    _t4865 = malloc(sizeof(Bool));
    *_t4865 = 0;
    (void)_t4865;
    _t4866 = malloc(sizeof(Bool));
    *_t4866 = 0;
    (void)_t4866;
    _t4867 = Str_lit("cli", 3ULL);
    (void)_t4867;
    _t4868 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4868->name = *_ca; free(_ca); }
    _t4868->needs_main = DEREF(_t4863);
    _t4868->decls_only = DEREF(_t4864);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4868->auto_import = *_ca; free(_ca); }
    _t4868->is_pure = DEREF(_t4865);
    _t4868->debug_prints = DEREF(_t4866);
    (void)_t4868;
    _t4869 = malloc(sizeof(Bool));
    *_t4869 = 1;
    (void)_t4869;
    _t4870 = malloc(sizeof(Bool));
    *_t4870 = 1;
    (void)_t4870;
    _t4871 = malloc(sizeof(Bool));
    *_t4871 = 0;
    (void)_t4871;
    _t4872 = malloc(sizeof(Bool));
    *_t4872 = 0;
    (void)_t4872;
    _t4873 = Str_lit("gui", 3ULL);
    (void)_t4873;
    _t4874 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4874->name = *_ca; free(_ca); }
    _t4874->needs_main = DEREF(_t4869);
    _t4874->decls_only = DEREF(_t4870);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4874->auto_import = *_ca; free(_ca); }
    _t4874->is_pure = DEREF(_t4871);
    _t4874->debug_prints = DEREF(_t4872);
    (void)_t4874;
    _t4875 = malloc(sizeof(Bool));
    *_t4875 = 0;
    (void)_t4875;
    _t4876 = malloc(sizeof(Bool));
    *_t4876 = 1;
    (void)_t4876;
    _t4877 = malloc(sizeof(Bool));
    *_t4877 = 0;
    (void)_t4877;
    _t4878 = malloc(sizeof(Bool));
    *_t4878 = 0;
    (void)_t4878;
    _t4879 = Str_lit("test", 4ULL);
    (void)_t4879;
    _t4880 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4880->name = *_ca; free(_ca); }
    _t4880->needs_main = DEREF(_t4875);
    _t4880->decls_only = DEREF(_t4876);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4880->auto_import = *_ca; free(_ca); }
    _t4880->is_pure = DEREF(_t4877);
    _t4880->debug_prints = DEREF(_t4878);
    (void)_t4880;
    _t4881 = malloc(sizeof(Bool));
    *_t4881 = 0;
    (void)_t4881;
    _t4882 = malloc(sizeof(Bool));
    *_t4882 = 1;
    (void)_t4882;
    _t4883 = malloc(sizeof(Bool));
    *_t4883 = 1;
    (void)_t4883;
    _t4884 = malloc(sizeof(Bool));
    *_t4884 = 0;
    (void)_t4884;
    _t4885 = Str_lit("pure", 4ULL);
    (void)_t4885;
    _t4886 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4886->name = *_ca; free(_ca); }
    _t4886->needs_main = DEREF(_t4881);
    _t4886->decls_only = DEREF(_t4882);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4886->auto_import = *_ca; free(_ca); }
    _t4886->is_pure = DEREF(_t4883);
    _t4886->debug_prints = DEREF(_t4884);
    (void)_t4886;
    _t4887 = malloc(sizeof(Bool));
    *_t4887 = 0;
    (void)_t4887;
    _t4888 = malloc(sizeof(Bool));
    *_t4888 = 1;
    (void)_t4888;
    _t4889 = malloc(sizeof(Bool));
    *_t4889 = 1;
    (void)_t4889;
    _t4890 = malloc(sizeof(Bool));
    *_t4890 = 1;
    (void)_t4890;
    _t4891 = Str_lit("pura", 4ULL);
    (void)_t4891;
    _t4892 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4892->name = *_ca; free(_ca); }
    _t4892->needs_main = DEREF(_t4887);
    _t4892->decls_only = DEREF(_t4888);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4892->auto_import = *_ca; free(_ca); }
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
    _t4897 = Str_lit("lib", 3ULL);
    (void)_t4897;
    _t4898 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4898->name = *_ca; free(_ca); }
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
    *_t4901 = 0;
    (void)_t4901;
    _t4902 = malloc(sizeof(Bool));
    *_t4902 = 1;
    (void)_t4902;
    _t4903 = Str_lit("liba", 4ULL);
    (void)_t4903;
    _t4904 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4904->name = *_ca; free(_ca); }
    _t4904->needs_main = DEREF(_t4899);
    _t4904->decls_only = DEREF(_t4900);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4904->auto_import = *_ca; free(_ca); }
    _t4904->is_pure = DEREF(_t4901);
    _t4904->debug_prints = DEREF(_t4902);
    (void)_t4904;
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
    U64 _t4767; { U64 *_hp = (U64 *)Array_len(args); _t4767 = *_hp; free(_hp); }
    (void)_t4767;
    U64 _t4768 = 0;
    (void)_t4768;
    Bool _t4769 = U64_eq(_t4767, _t4768);
    (void)_t4769;
    ;
    ;
    if (_t4769) {
        usage();
        Str *_t4388 = Str_lit("Str", 3ULL);
        (void)_t4388;
        U64 _t4389; { U64 *_hp = (U64 *)Str_size(); _t4389 = *_hp; free(_hp); }
        (void)_t4389;
        U64 _t4390 = 1;
        (void)_t4390;
        Array *_va82 = Array_new(_t4388, &(U64){_t4389}, &(U64){_t4390});
        (void)_va82;
        Str_delete(_t4388, &(Bool){1});
        ;
        ;
        U64 _t4391 = 0;
        (void)_t4391;
        Str *_t4392 = Str_lit("no arguments", 12ULL);
        (void)_t4392;
        Array_set(_va82, &(U64){_t4391}, _t4392);
        ;
        Str *_t4393 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4393;
        panic(_t4393, _va82);
        Str_delete(_t4393, &(Bool){1});
    }
    ;
    U64 *_t4770 = malloc(sizeof(U64));
    *_t4770 = 0;
    (void)_t4770;
    Str *cmd_ref = Array_get(args, _t4770);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4770, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4771; { U64 *_hp = (U64 *)Array_len(args); _t4771 = *_hp; free(_hp); }
    (void)_t4771;
    U64 _t4772 = 1;
    (void)_t4772;
    Bool _t4773 = U64_eq(_t4771, _t4772);
    (void)_t4773;
    ;
    ;
    if (_t4773) {
        Str *_t4394 = Str_lit("help", 4ULL);
        (void)_t4394;
        Str *_t4395 = Str_lit("--help", 6ULL);
        (void)_t4395;
        Bool _t4396; { Bool *_hp = (Bool *)Str_eq(command, _t4394); _t4396 = *_hp; free(_hp); }
        (void)_t4396;
        Str_delete(_t4394, &(Bool){1});
        Bool _t4397; { Bool *_hp = (Bool *)Str_eq(command, _t4395); _t4397 = *_hp; free(_hp); }
        (void)_t4397;
        Str_delete(_t4395, &(Bool){1});
        Bool _t4398 = Bool_or(_t4396, _t4397);
        (void)_t4398;
        ;
        ;
        if (_t4398) {
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
            U64 _t4415; { U64 *_hp = (U64 *)Array_len(args); _t4415 = *_hp; free(_hp); }
            (void)_t4415;
            Bool _wcond4399; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4415}); _wcond4399 = *_hp; free(_hp); }
            (void)_wcond4399;
            ;
            if (_wcond4399) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4416 = Str_lit("-o", 2ULL);
            (void)_t4416;
            U64 _t4417 = 1;
            (void)_t4417;
            U64 _t4418 = U64_add(DEREF(path_idx), _t4417);
            (void)_t4418;
            ;
            U64 _t4419; { U64 *_hp = (U64 *)Array_len(args); _t4419 = *_hp; free(_hp); }
            (void)_t4419;
            Bool _t4420; { Bool *_hp = (Bool *)Str_eq(flag, _t4416); _t4420 = *_hp; free(_hp); }
            (void)_t4420;
            Str_delete(_t4416, &(Bool){1});
            Bool _t4421; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4418}, &(U64){_t4419}); _t4421 = *_hp; free(_hp); }
            (void)_t4421;
            ;
            ;
            Bool _t4422 = Bool_and(_t4420, _t4421);
            (void)_t4422;
            ;
            ;
            if (_t4422) {
                U64 _t4400 = 1;
                (void)_t4400;
                U64 *_t4401 = malloc(sizeof(U64)); *_t4401 = U64_add(DEREF(path_idx), _t4400);
                (void)_t4401;
                ;
                Str *oval = Array_get(args, _t4401);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4401, &(Bool){1});
                U64 _t4402 = 2;
                (void)_t4402;
                U64 _t4403 = U64_add(DEREF(path_idx), _t4402);
                (void)_t4403;
                ;
                *path_idx = _t4403;
                ;
            } else {
                Str *_t4408 = Str_lit("-c", 2ULL);
                (void)_t4408;
                U64 _t4409 = 1;
                (void)_t4409;
                U64 _t4410 = U64_add(DEREF(path_idx), _t4409);
                (void)_t4410;
                ;
                U64 _t4411; { U64 *_hp = (U64 *)Array_len(args); _t4411 = *_hp; free(_hp); }
                (void)_t4411;
                Bool _t4412; { Bool *_hp = (Bool *)Str_eq(flag, _t4408); _t4412 = *_hp; free(_hp); }
                (void)_t4412;
                Str_delete(_t4408, &(Bool){1});
                Bool _t4413; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4410}, &(U64){_t4411}); _t4413 = *_hp; free(_hp); }
                (void)_t4413;
                ;
                ;
                Bool _t4414 = Bool_and(_t4412, _t4413);
                (void)_t4414;
                ;
                ;
                if (_t4414) {
                    U64 _t4404 = 1;
                    (void)_t4404;
                    U64 *_t4405 = malloc(sizeof(U64)); *_t4405 = U64_add(DEREF(path_idx), _t4404);
                    (void)_t4405;
                    ;
                    Str *cval = Array_get(args, _t4405);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4405, &(Bool){1});
                    U64 _t4406 = 2;
                    (void)_t4406;
                    U64 _t4407 = U64_add(DEREF(path_idx), _t4406);
                    (void)_t4407;
                    ;
                    *path_idx = _t4407;
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
    Str *_t4774 = Str_lit("help", 4ULL);
    (void)_t4774;
    Str *_t4775 = Str_lit("--help", 6ULL);
    (void)_t4775;
    Bool _t4776; { Bool *_hp = (Bool *)Str_eq(command, _t4774); _t4776 = *_hp; free(_hp); }
    (void)_t4776;
    Str_delete(_t4774, &(Bool){1});
    Bool _t4777; { Bool *_hp = (Bool *)Str_eq(command, _t4775); _t4777 = *_hp; free(_hp); }
    (void)_t4777;
    Str_delete(_t4775, &(Bool){1});
    Bool _t4778 = Bool_or(_t4776, _t4777);
    (void)_t4778;
    ;
    ;
    if (_t4778) {
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
    Str *_t4779 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4779;
    Str *core_path = Str_concat(bin_dir, _t4779);
    (void)core_path;
    Str_delete(_t4779, &(Bool){1});
    Str *_t4780 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4780;
    Str *ext_c_path = Str_concat(bin_dir, _t4780);
    (void)ext_c_path;
    Str_delete(_t4780, &(Bool){1});
    Str *_t4781 = Str_lit("Str", 3ULL);
    (void)_t4781;
    U64 _t4782; { U64 *_hp = (U64 *)Str_size(); _t4782 = *_hp; free(_hp); }
    (void)_t4782;
    Set *resolved = Set_new(_t4781, &(U64){_t4782});
    (void)resolved;
    Str_delete(_t4781, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4783; { U64 *_hp = (U64 *)Str_len(abs_path); _t4783 = *_hp; free(_hp); }
    (void)_t4783;
    U64 _t4784 = 0;
    (void)_t4784;
    Bool _t4785; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4783}, &(U64){_t4784}); _t4785 = *_hp; free(_hp); }
    (void)_t4785;
    ;
    ;
    if (_t4785) {
        U64 _t4431; { U64 *_hp = (U64 *)Str_len(abs_path); _t4431 = *_hp; free(_hp); }
        (void)_t4431;
        U64 _t4432 = 1;
        (void)_t4432;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4431, _t4432);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4424 = 0;
            (void)_t4424;
            U8 *_t4425 = Str_get(abs_path, last_slash);
            (void)_t4425;
            U8 _t4426 = 47;
            (void)_t4426;
            Bool _t4427; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4424}); _t4427 = *_hp; free(_hp); }
            (void)_t4427;
            ;
            Bool _t4428; { Bool *_hp = (Bool *)U8_neq(_t4425, &(U8){_t4426}); _t4428 = *_hp; free(_hp); }
            (void)_t4428;
            ;
            Bool _wcond4423 = Bool_and(_t4427, _t4428);
            (void)_wcond4423;
            ;
            ;
            if (_wcond4423) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4429 = 1;
            (void)_t4429;
            U64 _t4430 = U64_sub(DEREF(last_slash), _t4429);
            (void)_t4430;
            ;
            *last_slash = _t4430;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4433 = Str_clone(abs_path);
        (void)_t4433;
        Set_add(resolved, _t4433);
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
    U64 _t4786; { U64 *_hp = (U64 *)Str_len(core_abs); _t4786 = *_hp; free(_hp); }
    (void)_t4786;
    U64 _t4787 = 0;
    (void)_t4787;
    Bool _t4788; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4786}, &(U64){_t4787}); _t4788 = *_hp; free(_hp); }
    (void)_t4788;
    ;
    ;
    if (_t4788) {
        Bool _t4435; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4435 = *_hp; free(_hp); }
        (void)_t4435;
        if (_t4435) {
            Bool _t4434 = 1;
            (void)_t4434;
            skip_core = _t4434;
            ;
        }
        ;
        Str *_t4436 = Str_clone(core_abs);
        (void)_t4436;
        Set_add(resolved, _t4436);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4789; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4789 = *_hp; free(_hp); }
    (void)_t4789;
    U64 _t4790 = 0;
    (void)_t4790;
    Bool _t4791; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4789}, &(U64){_t4790}); _t4791 = *_hp; free(_hp); }
    (void)_t4791;
    ;
    ;
    Bool _t4792 = Bool_not(skip_core);
    (void)_t4792;
    Bool _t4793 = Bool_and(_t4791, _t4792);
    (void)_t4793;
    ;
    ;
    if (_t4793) {
        Str *_t4443 = Str_lit("/src/core", 9ULL);
        (void)_t4443;
        Str *core_dir = Str_concat(bin_dir, _t4443);
        (void)core_dir;
        Str_delete(_t4443, &(Bool){1});
        Str *_t4444 = Str_lit("", 0ULL);
        (void)_t4444;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4444); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4444, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4445 = 0;
        (void)_t4445;
        Bool _t4446; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4445}); _t4446 = *_hp; free(_hp); }
        (void)_t4446;
        ;
        ;
        if (_t4446) {
            Str *_t4437 = Str_lit("Str", 3ULL);
            (void)_t4437;
            U64 _t4438; { U64 *_hp = (U64 *)Str_size(); _t4438 = *_hp; free(_hp); }
            (void)_t4438;
            U64 _t4439 = 1;
            (void)_t4439;
            Array *_va83 = Array_new(_t4437, &(U64){_t4438}, &(U64){_t4439});
            (void)_va83;
            Str_delete(_t4437, &(Bool){1});
            ;
            ;
            U64 _t4440 = 0;
            (void)_t4440;
            Str *_t4441 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4441;
            Array_set(_va83, &(U64){_t4440}, _t4441);
            ;
            Str *_t4442 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4442;
            panic(_t4442, _va83);
            Str_delete(_t4442, &(Bool){1});
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
    Str *_t4794 = Str_lit("script", 6ULL);
    (void)_t4794;
    Mode *cur_mode = mode_resolve(_t4794);
    (void)cur_mode;
    Str_delete(_t4794, &(Bool){1});
    U64 _t4795; { U64 *_hp = (U64 *)Str_len(mode_str); _t4795 = *_hp; free(_hp); }
    (void)_t4795;
    U64 _t4796 = 0;
    (void)_t4796;
    Bool _t4797; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4795}, &(U64){_t4796}); _t4797 = *_hp; free(_hp); }
    (void)_t4797;
    ;
    ;
    if (_t4797) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4456; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4456 = *_hp; free(_hp); }
        (void)_t4456;
        U64 _t4457 = 0;
        (void)_t4457;
        Bool _t4458 = U64_eq(_t4456, _t4457);
        (void)_t4458;
        ;
        ;
        if (_t4458) {
            Str *_t4447 = Str_lit("Str", 3ULL);
            (void)_t4447;
            U64 _t4448; { U64 *_hp = (U64 *)Str_size(); _t4448 = *_hp; free(_hp); }
            (void)_t4448;
            U64 _t4449 = 1;
            (void)_t4449;
            Array *_va84 = Array_new(_t4447, &(U64){_t4448}, &(U64){_t4449});
            (void)_va84;
            Str_delete(_t4447, &(Bool){1});
            ;
            ;
            Str *_t4450 = Str_lit("unknown mode '", 14ULL);
            (void)_t4450;
            Str *_t4451 = Str_concat(_t4450, mode_str);
            (void)_t4451;
            Str_delete(_t4450, &(Bool){1});
            Str *_t4452 = Str_lit("'", 1ULL);
            (void)_t4452;
            U64 _t4453 = 0;
            (void)_t4453;
            Str *_t4454 = Str_concat(_t4451, _t4452);
            (void)_t4454;
            Str_delete(_t4451, &(Bool){1});
            Str_delete(_t4452, &(Bool){1});
            Array_set(_va84, &(U64){_t4453}, _t4454);
            ;
            Str *_t4455 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4455;
            panic(_t4455, _va84);
            Str_delete(_t4455, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4798; { U64 *_hp = (U64 *)Vec_len(imports); _t4798 = *_hp; free(_hp); }
    (void)_t4798;
    U64 _t4799 = 0;
    (void)_t4799;
    Bool _t4800; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4798}, &(U64){_t4799}); _t4800 = *_hp; free(_hp); }
    (void)_t4800;
    ;
    ;
    if (_t4800) {
        Str *_t4465 = Str_lit("/src/lib", 8ULL);
        (void)_t4465;
        Str *lib_dir = Str_concat(bin_dir, _t4465);
        (void)lib_dir;
        Str_delete(_t4465, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4466 = 0;
        (void)_t4466;
        Bool _t4467; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4466}); _t4467 = *_hp; free(_hp); }
        (void)_t4467;
        ;
        ;
        if (_t4467) {
            Str *_t4459 = Str_lit("Str", 3ULL);
            (void)_t4459;
            U64 _t4460; { U64 *_hp = (U64 *)Str_size(); _t4460 = *_hp; free(_hp); }
            (void)_t4460;
            U64 _t4461 = 1;
            (void)_t4461;
            Array *_va85 = Array_new(_t4459, &(U64){_t4460}, &(U64){_t4461});
            (void)_va85;
            Str_delete(_t4459, &(Bool){1});
            ;
            ;
            U64 _t4462 = 0;
            (void)_t4462;
            Str *_t4463 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4463;
            Array_set(_va85, &(U64){_t4462}, _t4463);
            ;
            Str *_t4464 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4464;
            panic(_t4464, _va85);
            Str_delete(_t4464, &(Bool){1});
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
    Bool _t4801 = Bool_not(skip_core);
    (void)_t4801;
    ;
    if (_t4801) {
        while (1) {
            U32 _t4469 = expr_nchildren(core_ast);
            (void)_t4469;
            Bool _wcond4468; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4469}); _wcond4468 = *_hp; free(_hp); }
            (void)_wcond4468;
            ;
            if (_wcond4468) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4470 = 1;
            (void)_t4470;
            U32 _t4471 = U32_add(DEREF(i), _t4470);
            (void)_t4471;
            ;
            *i = _t4471;
            ;
        }
        U32 _t4476 = 0;
        (void)_t4476;
        *i = _t4476;
        ;
        while (1) {
            U32 _t4473 = expr_vec_count(core_import_decls);
            (void)_t4473;
            Bool _wcond4472; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4473}); _wcond4472 = *_hp; free(_hp); }
            (void)_wcond4472;
            ;
            if (_wcond4472) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4474 = 1;
            (void)_t4474;
            U32 _t4475 = U32_add(DEREF(i), _t4474);
            (void)_t4475;
            ;
            *i = _t4475;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4802; { U64 *_hp = (U64 *)Str_len(auto_import); _t4802 = *_hp; free(_hp); }
    (void)_t4802;
    U64 _t4803 = 0;
    (void)_t4803;
    Bool _t4804; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4802}, &(U64){_t4803}); _t4804 = *_hp; free(_hp); }
    (void)_t4804;
    ;
    ;
    if (_t4804) {
        Str *_t4481 = Str_lit("/src/modes/", 11ULL);
        (void)_t4481;
        Str *_t4482 = Str_concat(bin_dir, _t4481);
        (void)_t4482;
        Str_delete(_t4481, &(Bool){1});
        Str *_t4483 = Str_concat(_t4482, auto_import);
        (void)_t4483;
        Str_delete(_t4482, &(Bool){1});
        Str *_t4484 = Str_lit(".til", 4ULL);
        (void)_t4484;
        Str *mode_til_path = Str_concat(_t4483, _t4484);
        (void)mode_til_path;
        Str_delete(_t4483, &(Bool){1});
        Str_delete(_t4484, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4485 = 0;
        (void)_t4485;
        *i = _t4485;
        ;
        while (1) {
            U32 _t4478 = expr_nchildren(mode_ast);
            (void)_t4478;
            Bool _wcond4477; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4478}); _wcond4477 = *_hp; free(_hp); }
            (void)_wcond4477;
            ;
            if (_wcond4477) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4479 = 1;
            (void)_t4479;
            U32 _t4480 = U32_add(DEREF(i), _t4479);
            (void)_t4480;
            ;
            *i = _t4480;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4805 = 0;
    (void)_t4805;
    *i = _t4805;
    ;
    while (1) {
        U32 _t4487 = expr_vec_count(import_decls);
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
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4488 = 1;
        (void)_t4488;
        U32 _t4489 = U32_add(DEREF(i), _t4488);
        (void)_t4489;
        ;
        *i = _t4489;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4806 = 0;
    (void)_t4806;
    *i = _t4806;
    ;
    while (1) {
        U32 _t4491 = expr_nchildren(ast);
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
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4492 = 1;
        (void)_t4492;
        U32 _t4493 = U32_add(DEREF(i), _t4492);
        (void)_t4493;
        ;
        *i = _t4493;
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
    U32 _t4807 = 0;
    (void)_t4807;
    *i = _t4807;
    ;
    while (1) {
        U32 _t4509 = expr_nchildren(ast);
        (void)_t4509;
        Bool _wcond4494; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4509}); _wcond4494 = *_hp; free(_hp); }
        (void)_wcond4494;
        ;
        if (_wcond4494) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4510 = expr_get_tag(stmt);
        (void)_t4510;
        U32 _t4511 = expr_nchildren(stmt);
        (void)_t4511;
        U32 _t4512 = 2;
        (void)_t4512;
        Bool _t4513 = I32_eq(_t4510, DEREF(NODE_FCALL));
        (void)_t4513;
        ;
        Bool _t4514 = U32_eq(_t4511, _t4512);
        (void)_t4514;
        ;
        ;
        U32 *_t4515 = malloc(sizeof(U32));
        *_t4515 = 0;
        (void)_t4515;
        Expr *_t4516 = expr_get_child(stmt, DEREF(_t4515));
        (void)_t4516;
        I32 _t4517 = expr_get_tag(_t4516);
        (void)_t4517;
        U32_delete(_t4515, &(Bool){1});
        Bool _t4518 = Bool_and(_t4513, _t4514);
        (void)_t4518;
        ;
        ;
        Bool _t4519 = I32_eq(_t4517, DEREF(NODE_IDENT));
        (void)_t4519;
        ;
        U32 *_t4520 = malloc(sizeof(U32));
        *_t4520 = 1;
        (void)_t4520;
        Expr *_t4521 = expr_get_child(stmt, DEREF(_t4520));
        (void)_t4521;
        I32 _t4522 = expr_get_tag(_t4521);
        (void)_t4522;
        U32_delete(_t4520, &(Bool){1});
        Bool _t4523 = Bool_and(_t4518, _t4519);
        (void)_t4523;
        ;
        ;
        Bool _t4524 = I32_eq(_t4522, DEREF(NODE_LITERAL_STR));
        (void)_t4524;
        ;
        Bool _t4525 = Bool_and(_t4523, _t4524);
        (void)_t4525;
        ;
        ;
        if (_t4525) {
            U32 *_t4503 = malloc(sizeof(U32));
            *_t4503 = 0;
            (void)_t4503;
            Expr *_t4504 = expr_get_child(stmt, DEREF(_t4503));
            (void)_t4504;
            Str *fname = expr_get_str_val(_t4504);
            (void)fname;
            U32 *_t4505 = malloc(sizeof(U32));
            *_t4505 = 1;
            (void)_t4505;
            Expr *_t4506 = expr_get_child(stmt, DEREF(_t4505));
            (void)_t4506;
            Str *arg = expr_get_str_val(_t4506);
            (void)arg;
            Str *_t4507 = Str_lit("link", 4ULL);
            (void)_t4507;
            Bool _t4508; { Bool *_hp = (Bool *)Str_eq(fname, _t4507); _t4508 = *_hp; free(_hp); }
            (void)_t4508;
            Str_delete(_t4507, &(Bool){1});
            if (_t4508) {
                Str *_t4495 = Str_lit(" -l", 3ULL);
                (void)_t4495;
                Str *_t4496 = Str_concat(link_flags, _t4495);
                (void)_t4496;
                Str_delete(_t4495, &(Bool){1});
                link_flags = Str_concat(_t4496, arg);
                Str_delete(_t4496, &(Bool){1});
            } else {
                Str *_t4501 = Str_lit("link_c", 6ULL);
                (void)_t4501;
                Bool _t4502; { Bool *_hp = (Bool *)Str_eq(fname, _t4501); _t4502 = *_hp; free(_hp); }
                (void)_t4502;
                Str_delete(_t4501, &(Bool){1});
                if (_t4502) {
                    U64 _t4498; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4498 = *_hp; free(_hp); }
                    (void)_t4498;
                    U64 _t4499 = 0;
                    (void)_t4499;
                    Bool _t4500; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4498}, &(U64){_t4499}); _t4500 = *_hp; free(_hp); }
                    (void)_t4500;
                    ;
                    ;
                    if (_t4500) {
                        Str *_t4497 = Str_lit(" ", 1ULL);
                        (void)_t4497;
                        link_c_paths = Str_concat(link_c_paths, _t4497);
                        Str_delete(_t4497, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4503, &(Bool){1});
            U32_delete(_t4505, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4526 = 1;
        (void)_t4526;
        U32 _t4527 = U32_add(DEREF(i), _t4526);
        (void)_t4527;
        ;
        *i = _t4527;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4808 = init_declarations(ast, scope);
    (void)_t4808;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4809 = 0;
    (void)_t4809;
    Bool _t4810; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4809}); _t4810 = *_hp; free(_hp); }
    (void)_t4810;
    ;
    if (_t4810) {
        Str *_t4528 = Str_lit("Str", 3ULL);
        (void)_t4528;
        U64 _t4529; { U64 *_hp = (U64 *)Str_size(); _t4529 = *_hp; free(_hp); }
        (void)_t4529;
        U64 _t4530 = 1;
        (void)_t4530;
        Array *_va86 = Array_new(_t4528, &(U64){_t4529}, &(U64){_t4530});
        (void)_va86;
        Str_delete(_t4528, &(Bool){1});
        ;
        ;
        Str *_t4531 = I32_to_str(&(I32){type_errors});
        (void)_t4531;
        Str *_t4532 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4532;
        U64 _t4533 = 0;
        (void)_t4533;
        Str *_t4534 = Str_concat(_t4531, _t4532);
        (void)_t4534;
        Str_delete(_t4531, &(Bool){1});
        Str_delete(_t4532, &(Bool){1});
        Array_set(_va86, &(U64){_t4533}, _t4534);
        ;
        Str *_t4535 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4535;
        panic(_t4535, _va86);
        Str_delete(_t4535, &(Bool){1});
    }
    ;
    ;
    Str *_t4811 = Str_lit("test", 4ULL);
    (void)_t4811;
    Str *_t4812 = Str_lit("test", 4ULL);
    (void)_t4812;
    Bool _t4813; { Bool *_hp = (Bool *)Str_eq(command, _t4811); _t4813 = *_hp; free(_hp); }
    (void)_t4813;
    Str_delete(_t4811, &(Bool){1});
    Bool _t4814; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4812); _t4814 = *_hp; free(_hp); }
    (void)_t4814;
    Str_delete(_t4812, &(Bool){1});
    Str *_t4815 = Str_lit("pure", 4ULL);
    (void)_t4815;
    Bool _t4816 = Bool_or(_t4813, _t4814);
    (void)_t4816;
    ;
    ;
    Bool _t4817; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4815); _t4817 = *_hp; free(_hp); }
    (void)_t4817;
    Str_delete(_t4815, &(Bool){1});
    Str *_t4818 = Str_lit("pura", 4ULL);
    (void)_t4818;
    Bool _t4819 = Bool_or(_t4816, _t4817);
    (void)_t4819;
    ;
    ;
    Bool _t4820; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4818); _t4820 = *_hp; free(_hp); }
    (void)_t4820;
    Str_delete(_t4818, &(Bool){1});
    Bool run_tests = Bool_or(_t4819, _t4820);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4821 = Str_lit("translate", 9ULL);
    (void)_t4821;
    Str *_t4822 = Str_lit("build", 5ULL);
    (void)_t4822;
    Bool _t4823; { Bool *_hp = (Bool *)Str_eq(command, _t4821); _t4823 = *_hp; free(_hp); }
    (void)_t4823;
    Str_delete(_t4821, &(Bool){1});
    Bool _t4824; { Bool *_hp = (Bool *)Str_eq(command, _t4822); _t4824 = *_hp; free(_hp); }
    (void)_t4824;
    Str_delete(_t4822, &(Bool){1});
    Bool _t4825; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4825 = *_hp; free(_hp); }
    (void)_t4825;
    Bool _t4826 = Bool_or(_t4823, _t4824);
    (void)_t4826;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4825, _t4826);
    (void)is_lib_target;
    ;
    ;
    U64 _t4827; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4827 = *_hp; free(_hp); }
    (void)_t4827;
    U64 _t4828 = 0;
    (void)_t4828;
    Bool _t4829 = Bool_not(is_lib_target);
    (void)_t4829;
    ;
    Bool _t4830 = U64_eq(_t4827, _t4828);
    (void)_t4830;
    ;
    ;
    Bool _t4831 = Bool_and(_t4829, _t4830);
    (void)_t4831;
    ;
    ;
    if (_t4831) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4832; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4832 = *_hp; free(_hp); }
    (void)_t4832;
    U64 _t4833 = 0;
    (void)_t4833;
    Bool _t4834; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4832}, &(U64){_t4833}); _t4834 = *_hp; free(_hp); }
    (void)_t4834;
    ;
    ;
    if (_t4834) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4835 = Str_lit("Str", 3ULL);
    (void)_t4835;
    U64 _t4836; { U64 *_hp = (U64 *)Str_size(); _t4836 = *_hp; free(_hp); }
    (void)_t4836;
    Vec *user_argv = Vec_new(_t4835, &(U64){_t4836});
    (void)user_argv;
    Str_delete(_t4835, &(Bool){1});
    ;
    U64 _t4837 = 1;
    (void)_t4837;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4837);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4552; { U64 *_hp = (U64 *)Array_len(args); _t4552 = *_hp; free(_hp); }
        (void)_t4552;
        Bool _wcond4536; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4552}); _wcond4536 = *_hp; free(_hp); }
        (void)_wcond4536;
        ;
        if (_wcond4536) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4553 = Str_lit("-l", 2ULL);
        (void)_t4553;
        Bool _t4554; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4553); _t4554 = *_hp; free(_hp); }
        (void)_t4554;
        Str_delete(_t4553, &(Bool){1});
        if (_t4554) {
            U64 _t4539 = 2;
            (void)_t4539;
            U64 _t4540; { U64 *_hp = (U64 *)Str_len(arg); _t4540 = *_hp; free(_hp); }
            (void)_t4540;
            Str *lib = Str_substr(arg, &(U64){_t4539}, &(U64){_t4540});
            (void)lib;
            ;
            ;
            U64 _t4541; { U64 *_hp = (U64 *)Str_len(lib); _t4541 = *_hp; free(_hp); }
            (void)_t4541;
            U64 _t4542 = 0;
            (void)_t4542;
            U64 _t4543 = 1;
            (void)_t4543;
            U64 _t4544 = U64_add(DEREF(ai), _t4543);
            (void)_t4544;
            ;
            U64 _t4545; { U64 *_hp = (U64 *)Array_len(args); _t4545 = *_hp; free(_hp); }
            (void)_t4545;
            Bool _t4546 = U64_eq(_t4541, _t4542);
            (void)_t4546;
            ;
            ;
            Bool _t4547; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4544}, &(U64){_t4545}); _t4547 = *_hp; free(_hp); }
            (void)_t4547;
            ;
            ;
            Bool _t4548 = Bool_and(_t4546, _t4547);
            (void)_t4548;
            ;
            ;
            if (_t4548) {
                U64 _t4537 = 1;
                (void)_t4537;
                U64 _t4538 = U64_add(DEREF(ai), _t4537);
                (void)_t4538;
                ;
                *ai = _t4538;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4549 = Str_lit(" -l", 3ULL);
            (void)_t4549;
            Str *_t4550 = Str_concat(link_flags, _t4549);
            (void)_t4550;
            Str_delete(_t4549, &(Bool){1});
            link_flags = Str_concat(_t4550, lib);
            Str_delete(_t4550, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4551 = Str_clone(arg);
            (void)_t4551;
            Vec_push(user_argv, _t4551);
        }
        ;
        U64 _t4555 = 1;
        (void)_t4555;
        U64 _t4556 = U64_add(DEREF(ai), _t4555);
        (void)_t4556;
        ;
        *ai = _t4556;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4838; { U64 *_hp = (U64 *)Str_len(link_flags); _t4838 = *_hp; free(_hp); }
    (void)_t4838;
    U64 _t4839 = 0;
    (void)_t4839;
    Bool _t4840; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4838}, &(U64){_t4839}); _t4840 = *_hp; free(_hp); }
    (void)_t4840;
    ;
    ;
    if (_t4840) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4841 = Str_lit("interpret", 9ULL);
    (void)_t4841;
    Str *_t4842 = Str_lit("test", 4ULL);
    (void)_t4842;
    Bool _t4843; { Bool *_hp = (Bool *)Str_eq(command, _t4841); _t4843 = *_hp; free(_hp); }
    (void)_t4843;
    Str_delete(_t4841, &(Bool){1});
    Bool _t4844; { Bool *_hp = (Bool *)Str_eq(command, _t4842); _t4844 = *_hp; free(_hp); }
    (void)_t4844;
    Str_delete(_t4842, &(Bool){1});
    Bool _t4845 = Bool_or(_t4843, _t4844);
    (void)_t4845;
    ;
    ;
    if (_t4845) {
        Str *_t4563 = Str_lit("interpret", 9ULL);
        (void)_t4563;
        Bool _t4564; { Bool *_hp = (Bool *)Str_eq(command, _t4563); _t4564 = *_hp; free(_hp); }
        (void)_t4564;
        Str_delete(_t4563, &(Bool){1});
        Bool _t4565 = Bool_and(is_lib_mode, _t4564);
        (void)_t4565;
        ;
        if (_t4565) {
            Str *_t4557 = Str_lit("Str", 3ULL);
            (void)_t4557;
            U64 _t4558; { U64 *_hp = (U64 *)Str_size(); _t4558 = *_hp; free(_hp); }
            (void)_t4558;
            U64 _t4559 = 1;
            (void)_t4559;
            Array *_va87 = Array_new(_t4557, &(U64){_t4558}, &(U64){_t4559});
            (void)_va87;
            Str_delete(_t4557, &(Bool){1});
            ;
            ;
            U64 _t4560 = 0;
            (void)_t4560;
            Str *_t4561 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4561;
            Array_set(_va87, &(U64){_t4560}, _t4561);
            ;
            Str *_t4562 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4562;
            panic(_t4562, _va87);
            Str_delete(_t4562, &(Bool){1});
        }
        ;
        I32 _t4566 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4566;
        result = _t4566;
        ;
    } else {
        Str *_t4759 = Str_lit("translate", 9ULL);
        (void)_t4759;
        Str *_t4760 = Str_lit("build", 5ULL);
        (void)_t4760;
        Bool _t4761; { Bool *_hp = (Bool *)Str_eq(command, _t4759); _t4761 = *_hp; free(_hp); }
        (void)_t4761;
        Str_delete(_t4759, &(Bool){1});
        Bool _t4762; { Bool *_hp = (Bool *)Str_eq(command, _t4760); _t4762 = *_hp; free(_hp); }
        (void)_t4762;
        Str_delete(_t4760, &(Bool){1});
        Str *_t4763 = Str_lit("run", 3ULL);
        (void)_t4763;
        Bool _t4764 = Bool_or(_t4761, _t4762);
        (void)_t4764;
        ;
        ;
        Bool _t4765; { Bool *_hp = (Bool *)Str_eq(command, _t4763); _t4765 = *_hp; free(_hp); }
        (void)_t4765;
        Str_delete(_t4763, &(Bool){1});
        Bool _t4766 = Bool_or(_t4764, _t4765);
        (void)_t4766;
        ;
        ;
        if (_t4766) {
            Str *_t4692 = Str_lit("run", 3ULL);
            (void)_t4692;
            Bool _t4693; { Bool *_hp = (Bool *)Str_eq(command, _t4692); _t4693 = *_hp; free(_hp); }
            (void)_t4693;
            Str_delete(_t4692, &(Bool){1});
            Bool _t4694 = Bool_and(is_lib_mode, _t4693);
            (void)_t4694;
            ;
            if (_t4694) {
                Str *_t4567 = Str_lit("Str", 3ULL);
                (void)_t4567;
                U64 _t4568; { U64 *_hp = (U64 *)Str_size(); _t4568 = *_hp; free(_hp); }
                (void)_t4568;
                U64 _t4569 = 1;
                (void)_t4569;
                Array *_va88 = Array_new(_t4567, &(U64){_t4568}, &(U64){_t4569});
                (void)_va88;
                Str_delete(_t4567, &(Bool){1});
                ;
                ;
                U64 _t4570 = 0;
                (void)_t4570;
                Str *_t4571 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4571;
                Array_set(_va88, &(U64){_t4570}, _t4571);
                ;
                Str *_t4572 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4572;
                panic(_t4572, _va88);
                Str_delete(_t4572, &(Bool){1});
            }
            ;
            Str *_t4695 = Str_lit("/", 1ULL);
            (void)_t4695;
            I64 *last_slash = Str_rfind(path, _t4695);
            (void)last_slash;
            Str_delete(_t4695, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4696 = 0;
            (void)_t4696;
            Bool _t4697; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4696}); _t4697 = *_hp; free(_hp); }
            (void)_t4697;
            ;
            if (_t4697) {
                I64 _t4573 = 1;
                (void)_t4573;
                I64 _t4574 = I64_add(DEREF(last_slash), _t4573);
                (void)_t4574;
                ;
                U64 _t4575; { U64 *_hp = (U64 *)Str_len(path); _t4575 = *_hp; free(_hp); }
                (void)_t4575;
                U64 _t4576 = I64_to_u64(DEREF(last_slash));
                (void)_t4576;
                U64 _t4577 = U64_sub(_t4575, _t4576);
                (void)_t4577;
                ;
                ;
                U64 _t4578 = 1;
                (void)_t4578;
                U64 _t4579 = I64_to_u64(_t4574);
                (void)_t4579;
                ;
                U64 _t4580 = U64_sub(_t4577, _t4578);
                (void)_t4580;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4579}, &(U64){_t4580});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4698 = Str_lit(".til", 4ULL);
            (void)_t4698;
            Bool _t4699; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4698); _t4699 = *_hp; free(_hp); }
            (void)_t4699;
            Str_delete(_t4698, &(Bool){1});
            if (_t4699) {
                U64 _t4581 = 4;
                (void)_t4581;
                U64 _t4582 = U64_sub(name_len, _t4581);
                (void)_t4582;
                ;
                name_len = _t4582;
                ;
            }
            ;
            U64 _t4700 = 0;
            (void)_t4700;
            Str *name = Str_substr(basename, &(U64){_t4700}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4701 = Str_lit("gen/til/", 8ULL);
            (void)_t4701;
            Str *_t4702 = Str_concat(_t4701, name);
            (void)_t4702;
            Str_delete(_t4701, &(Bool){1});
            Str *_t4703 = Str_lit(".c", 2ULL);
            (void)_t4703;
            Str *c_path = Str_concat(_t4702, _t4703);
            (void)c_path;
            Str_delete(_t4702, &(Bool){1});
            Str_delete(_t4703, &(Bool){1});
            U64 _t4704; { U64 *_hp = (U64 *)Str_len(custom_c); _t4704 = *_hp; free(_hp); }
            (void)_t4704;
            U64 _t4705 = 0;
            (void)_t4705;
            Bool _t4706; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4704}, &(U64){_t4705}); _t4706 = *_hp; free(_hp); }
            (void)_t4706;
            ;
            ;
            if (_t4706) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4707 = Str_lit("bin/til/", 8ULL);
            (void)_t4707;
            Str *bin_path = Str_concat(_t4707, name);
            (void)bin_path;
            Str_delete(_t4707, &(Bool){1});
            U64 _t4708; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4708 = *_hp; free(_hp); }
            (void)_t4708;
            U64 _t4709 = 0;
            (void)_t4709;
            Bool _t4710; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4708}, &(U64){_t4709}); _t4710 = *_hp; free(_hp); }
            (void)_t4710;
            ;
            ;
            if (_t4710) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4711 = Str_lit("run", 3ULL);
            (void)_t4711;
            Bool _t4712; { Bool *_hp = (Bool *)Str_eq(command, _t4711); _t4712 = *_hp; free(_hp); }
            (void)_t4712;
            Str_delete(_t4711, &(Bool){1});
            Bool _t4713; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4713 = *_hp; free(_hp); }
            (void)_t4713;
            Bool _t4714 = Bool_not(_t4712);
            (void)_t4714;
            ;
            Bool do_lib = Bool_and(_t4713, _t4714);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4583 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4583;
                I32 _t4584 = til_system(_t4583);
                (void)_t4584;
                Str_delete(_t4583, &(Bool){1});
                ;
            } else {
                Str *_t4589 = Str_lit("/", 1ULL);
                (void)_t4589;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4589); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4589, &(Bool){1});
                Str *_t4590 = Str_lit("/", 1ULL);
                (void)_t4590;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4590); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4590, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4591 = 0;
                (void)_t4591;
                Bool _t4592; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4591}); _t4592 = *_hp; free(_hp); }
                (void)_t4592;
                ;
                if (_t4592) {
                    U64 _t4585 = 0;
                    (void)_t4585;
                    U64 _t4586 = I64_to_u64(cp_slash);
                    (void)_t4586;
                    cp_dir = Str_substr(c_path, &(U64){_t4585}, &(U64){_t4586});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4593 = 0;
                (void)_t4593;
                Bool _t4594; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4593}); _t4594 = *_hp; free(_hp); }
                (void)_t4594;
                ;
                if (_t4594) {
                    U64 _t4587 = 0;
                    (void)_t4587;
                    U64 _t4588 = I64_to_u64(bp_slash);
                    (void)_t4588;
                    bp_dir = Str_substr(bin_path, &(U64){_t4587}, &(U64){_t4588});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4595 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4595;
                Str *_t4596 = Str_concat(_t4595, cp_dir);
                (void)_t4596;
                Str_delete(_t4595, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4597 = Str_lit(" ", 1ULL);
                (void)_t4597;
                Str *_t4598 = Str_concat(_t4596, _t4597);
                (void)_t4598;
                Str_delete(_t4596, &(Bool){1});
                Str_delete(_t4597, &(Bool){1});
                Str *_t4599 = Str_concat(_t4598, bp_dir);
                (void)_t4599;
                Str_delete(_t4598, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4600 = til_system(_t4599);
                (void)_t4600;
                Str_delete(_t4599, &(Bool){1});
                ;
            }
            I32 _t4715 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4715;
            result = _t4715;
            ;
            I32 _t4716 = 0;
            (void)_t4716;
            Bool _t4717 = I32_eq(result, _t4716);
            (void)_t4717;
            ;
            Bool _t4718 = Bool_and(_t4717, do_lib);
            (void)_t4718;
            ;
            if (_t4718) {
                Str *_t4657 = Str_lit("gen/til/", 8ULL);
                (void)_t4657;
                Str *_t4658 = Str_concat(_t4657, name);
                (void)_t4658;
                Str_delete(_t4657, &(Bool){1});
                Str *_t4659 = Str_lit(".h", 2ULL);
                (void)_t4659;
                Str *h_path = Str_concat(_t4658, _t4659);
                (void)h_path;
                Str_delete(_t4658, &(Bool){1});
                Str_delete(_t4659, &(Bool){1});
                Str *_t4660 = Str_lit("gen/til/", 8ULL);
                (void)_t4660;
                Str *_t4661 = Str_concat(_t4660, name);
                (void)_t4661;
                Str_delete(_t4660, &(Bool){1});
                Str *_t4662 = Str_lit(".til", 4ULL);
                (void)_t4662;
                Str *til_path = Str_concat(_t4661, _t4662);
                (void)til_path;
                Str_delete(_t4661, &(Bool){1});
                Str_delete(_t4662, &(Bool){1});
                I32 _t4663 = build_header(ast, h_path);
                (void)_t4663;
                result = _t4663;
                ;
                I32 _t4664 = 0;
                (void)_t4664;
                Bool _t4665 = I32_eq(result, _t4664);
                (void)_t4665;
                ;
                if (_t4665) {
                    I32 _t4601 = build_til_binding(ast, til_path, name);
                    (void)_t4601;
                    result = _t4601;
                    ;
                }
                ;
                I32 _t4666 = 0;
                (void)_t4666;
                Str *_t4667 = Str_lit("translate", 9ULL);
                (void)_t4667;
                Bool _t4668 = I32_eq(result, _t4666);
                (void)_t4668;
                ;
                Bool _t4669; { Bool *_hp = (Bool *)Str_eq(command, _t4667); _t4669 = *_hp; free(_hp); }
                (void)_t4669;
                Str_delete(_t4667, &(Bool){1});
                Bool _t4670 = Bool_and(_t4668, _t4669);
                (void)_t4670;
                ;
                ;
                if (_t4670) {
                    Str *_t4602 = Str_lit("Str", 3ULL);
                    (void)_t4602;
                    U64 _t4603; { U64 *_hp = (U64 *)Str_size(); _t4603 = *_hp; free(_hp); }
                    (void)_t4603;
                    U64 _t4604 = 1;
                    (void)_t4604;
                    Array *_va89 = Array_new(_t4602, &(U64){_t4603}, &(U64){_t4604});
                    (void)_va89;
                    Str_delete(_t4602, &(Bool){1});
                    ;
                    ;
                    Str *_t4605 = Str_lit("Generated: ", 11ULL);
                    (void)_t4605;
                    U64 _t4606 = 0;
                    (void)_t4606;
                    Str *_t4607 = Str_concat(_t4605, c_path);
                    (void)_t4607;
                    Str_delete(_t4605, &(Bool){1});
                    Array_set(_va89, &(U64){_t4606}, _t4607);
                    ;
                    println(_va89);
                    Str *_t4608 = Str_lit("Str", 3ULL);
                    (void)_t4608;
                    U64 _t4609; { U64 *_hp = (U64 *)Str_size(); _t4609 = *_hp; free(_hp); }
                    (void)_t4609;
                    U64 _t4610 = 1;
                    (void)_t4610;
                    Array *_va90 = Array_new(_t4608, &(U64){_t4609}, &(U64){_t4610});
                    (void)_va90;
                    Str_delete(_t4608, &(Bool){1});
                    ;
                    ;
                    Str *_t4611 = Str_lit("Generated: ", 11ULL);
                    (void)_t4611;
                    U64 _t4612 = 0;
                    (void)_t4612;
                    Str *_t4613 = Str_concat(_t4611, h_path);
                    (void)_t4613;
                    Str_delete(_t4611, &(Bool){1});
                    Array_set(_va90, &(U64){_t4612}, _t4613);
                    ;
                    println(_va90);
                    Str *_t4614 = Str_lit("Str", 3ULL);
                    (void)_t4614;
                    U64 _t4615; { U64 *_hp = (U64 *)Str_size(); _t4615 = *_hp; free(_hp); }
                    (void)_t4615;
                    U64 _t4616 = 1;
                    (void)_t4616;
                    Array *_va91 = Array_new(_t4614, &(U64){_t4615}, &(U64){_t4616});
                    (void)_va91;
                    Str_delete(_t4614, &(Bool){1});
                    ;
                    ;
                    Str *_t4617 = Str_lit("Generated: ", 11ULL);
                    (void)_t4617;
                    U64 _t4618 = 0;
                    (void)_t4618;
                    Str *_t4619 = Str_concat(_t4617, til_path);
                    (void)_t4619;
                    Str_delete(_t4617, &(Bool){1});
                    Array_set(_va91, &(U64){_t4618}, _t4619);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4671 = 0;
                (void)_t4671;
                Str *_t4672 = Str_lit("build", 5ULL);
                (void)_t4672;
                Bool _t4673 = I32_eq(result, _t4671);
                (void)_t4673;
                ;
                Bool _t4674; { Bool *_hp = (Bool *)Str_eq(command, _t4672); _t4674 = *_hp; free(_hp); }
                (void)_t4674;
                Str_delete(_t4672, &(Bool){1});
                Bool _t4675 = Bool_and(_t4673, _t4674);
                (void)_t4675;
                ;
                ;
                if (_t4675) {
                    I32 _t4654 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4654;
                    result = _t4654;
                    ;
                    I32 _t4655 = 0;
                    (void)_t4655;
                    Bool _t4656 = I32_eq(result, _t4655);
                    (void)_t4656;
                    ;
                    if (_t4656) {
                        Str *_t4620 = Str_lit("Str", 3ULL);
                        (void)_t4620;
                        U64 _t4621; { U64 *_hp = (U64 *)Str_size(); _t4621 = *_hp; free(_hp); }
                        (void)_t4621;
                        U64 _t4622 = 1;
                        (void)_t4622;
                        Array *_va92 = Array_new(_t4620, &(U64){_t4621}, &(U64){_t4622});
                        (void)_va92;
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
                        Array_set(_va92, &(U64){_t4624}, _t4625);
                        ;
                        println(_va92);
                        Str *_t4626 = Str_lit("Str", 3ULL);
                        (void)_t4626;
                        U64 _t4627; { U64 *_hp = (U64 *)Str_size(); _t4627 = *_hp; free(_hp); }
                        (void)_t4627;
                        U64 _t4628 = 1;
                        (void)_t4628;
                        Array *_va93 = Array_new(_t4626, &(U64){_t4627}, &(U64){_t4628});
                        (void)_va93;
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
                        Array_set(_va93, &(U64){_t4630}, _t4631);
                        ;
                        println(_va93);
                        Str *_t4632 = Str_lit("Str", 3ULL);
                        (void)_t4632;
                        U64 _t4633; { U64 *_hp = (U64 *)Str_size(); _t4633 = *_hp; free(_hp); }
                        (void)_t4633;
                        U64 _t4634 = 1;
                        (void)_t4634;
                        Array *_va94 = Array_new(_t4632, &(U64){_t4633}, &(U64){_t4634});
                        (void)_va94;
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
                        Array_set(_va94, &(U64){_t4636}, _t4637);
                        ;
                        println(_va94);
                        Str *_t4638 = Str_lit("Str", 3ULL);
                        (void)_t4638;
                        U64 _t4639; { U64 *_hp = (U64 *)Str_size(); _t4639 = *_hp; free(_hp); }
                        (void)_t4639;
                        U64 _t4640 = 1;
                        (void)_t4640;
                        Array *_va95 = Array_new(_t4638, &(U64){_t4639}, &(U64){_t4640});
                        (void)_va95;
                        Str_delete(_t4638, &(Bool){1});
                        ;
                        ;
                        Str *_t4641 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4641;
                        Str *_t4642 = Str_concat(_t4641, name);
                        (void)_t4642;
                        Str_delete(_t4641, &(Bool){1});
                        Str *_t4643 = Str_lit(".so", 3ULL);
                        (void)_t4643;
                        U64 _t4644 = 0;
                        (void)_t4644;
                        Str *_t4645 = Str_concat(_t4642, _t4643);
                        (void)_t4645;
                        Str_delete(_t4642, &(Bool){1});
                        Str_delete(_t4643, &(Bool){1});
                        Array_set(_va95, &(U64){_t4644}, _t4645);
                        ;
                        println(_va95);
                        Str *_t4646 = Str_lit("Str", 3ULL);
                        (void)_t4646;
                        U64 _t4647; { U64 *_hp = (U64 *)Str_size(); _t4647 = *_hp; free(_hp); }
                        (void)_t4647;
                        U64 _t4648 = 1;
                        (void)_t4648;
                        Array *_va96 = Array_new(_t4646, &(U64){_t4647}, &(U64){_t4648});
                        (void)_va96;
                        Str_delete(_t4646, &(Bool){1});
                        ;
                        ;
                        Str *_t4649 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4649;
                        Str *_t4650 = Str_concat(_t4649, name);
                        (void)_t4650;
                        Str_delete(_t4649, &(Bool){1});
                        Str *_t4651 = Str_lit(".a", 2ULL);
                        (void)_t4651;
                        U64 _t4652 = 0;
                        (void)_t4652;
                        Str *_t4653 = Str_concat(_t4650, _t4651);
                        (void)_t4653;
                        Str_delete(_t4650, &(Bool){1});
                        Str_delete(_t4651, &(Bool){1});
                        Array_set(_va96, &(U64){_t4652}, _t4653);
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
            I32 _t4719 = 0;
            (void)_t4719;
            Bool _t4720 = I32_eq(result, _t4719);
            (void)_t4720;
            ;
            Bool _t4721 = Bool_not(do_lib);
            (void)_t4721;
            Str *_t4722 = Str_lit("translate", 9ULL);
            (void)_t4722;
            Bool _t4723 = Bool_and(_t4720, _t4721);
            (void)_t4723;
            ;
            ;
            Bool _t4724; { Bool *_hp = (Bool *)Str_eq(command, _t4722); _t4724 = *_hp; free(_hp); }
            (void)_t4724;
            Str_delete(_t4722, &(Bool){1});
            Bool _t4725 = Bool_and(_t4723, _t4724);
            (void)_t4725;
            ;
            ;
            if (_t4725) {
                Str *_t4676 = Str_lit("Str", 3ULL);
                (void)_t4676;
                U64 _t4677; { U64 *_hp = (U64 *)Str_size(); _t4677 = *_hp; free(_hp); }
                (void)_t4677;
                U64 _t4678 = 1;
                (void)_t4678;
                Array *_va97 = Array_new(_t4676, &(U64){_t4677}, &(U64){_t4678});
                (void)_va97;
                Str_delete(_t4676, &(Bool){1});
                ;
                ;
                Str *_t4679 = Str_lit("Generated: ", 11ULL);
                (void)_t4679;
                U64 _t4680 = 0;
                (void)_t4680;
                Str *_t4681 = Str_concat(_t4679, c_path);
                (void)_t4681;
                Str_delete(_t4679, &(Bool){1});
                Array_set(_va97, &(U64){_t4680}, _t4681);
                ;
                println(_va97);
            }
            ;
            I32 _t4726 = 0;
            (void)_t4726;
            Bool _t4727 = I32_eq(result, _t4726);
            (void)_t4727;
            ;
            Bool _t4728 = Bool_not(do_lib);
            (void)_t4728;
            Str *_t4729 = Str_lit("translate", 9ULL);
            (void)_t4729;
            Bool _t4730; { Bool *_hp = (Bool *)Str_eq(command, _t4729); _t4730 = *_hp; free(_hp); }
            (void)_t4730;
            Str_delete(_t4729, &(Bool){1});
            Bool _t4731 = Bool_and(_t4727, _t4728);
            (void)_t4731;
            ;
            ;
            Bool _t4732 = Bool_not(_t4730);
            (void)_t4732;
            ;
            Bool _t4733 = Bool_and(_t4731, _t4732);
            (void)_t4733;
            ;
            ;
            if (_t4733) {
                I32 _t4682 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4682;
                result = _t4682;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4734 = 0;
            (void)_t4734;
            Bool _t4735 = I32_eq(result, _t4734);
            (void)_t4735;
            ;
            Bool _t4736 = Bool_not(do_lib);
            (void)_t4736;
            ;
            Str *_t4737 = Str_lit("run", 3ULL);
            (void)_t4737;
            Bool _t4738 = Bool_and(_t4735, _t4736);
            (void)_t4738;
            ;
            ;
            Bool _t4739; { Bool *_hp = (Bool *)Str_eq(command, _t4737); _t4739 = *_hp; free(_hp); }
            (void)_t4739;
            Str_delete(_t4737, &(Bool){1});
            Bool _t4740 = Bool_and(_t4738, _t4739);
            (void)_t4740;
            ;
            ;
            if (_t4740) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4684; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4684 = *_hp; free(_hp); }
                    (void)_t4684;
                    Bool _wcond4683; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4684}); _wcond4683 = *_hp; free(_hp); }
                    (void)_wcond4683;
                    ;
                    if (_wcond4683) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4685 = Str_lit(" '", 2ULL);
                    (void)_t4685;
                    Str *_t4686 = Str_concat(cmd, _t4685);
                    (void)_t4686;
                    Str_delete(_t4685, &(Bool){1});
                    Str *_t4687 = Str_concat(_t4686, uarg);
                    (void)_t4687;
                    Str_delete(_t4686, &(Bool){1});
                    Str *_t4688 = Str_lit("'", 1ULL);
                    (void)_t4688;
                    cmd = Str_concat(_t4687, _t4688);
                    Str_delete(_t4687, &(Bool){1});
                    Str_delete(_t4688, &(Bool){1});
                    U64 _t4689 = 1;
                    (void)_t4689;
                    U64 _t4690 = U64_add(DEREF(ui), _t4689);
                    (void)_t4690;
                    ;
                    *ui = _t4690;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4691 = til_system(cmd);
                (void)_t4691;
                Str_delete(cmd, &(Bool){1});
                result = _t4691;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4757 = Str_lit("ast", 3ULL);
            (void)_t4757;
            Bool _t4758; { Bool *_hp = (Bool *)Str_eq(command, _t4757); _t4758 = *_hp; free(_hp); }
            (void)_t4758;
            Str_delete(_t4757, &(Bool){1});
            if (_t4758) {
                Str *_t4741 = Str_lit("Str", 3ULL);
                (void)_t4741;
                U64 _t4742; { U64 *_hp = (U64 *)Str_size(); _t4742 = *_hp; free(_hp); }
                (void)_t4742;
                U64 _t4743 = 1;
                (void)_t4743;
                Array *_va98 = Array_new(_t4741, &(U64){_t4742}, &(U64){_t4743});
                (void)_va98;
                Str_delete(_t4741, &(Bool){1});
                ;
                ;
                Str *_t4744 = Str_lit("mode: ", 6ULL);
                (void)_t4744;
                U64 _t4745 = 0;
                (void)_t4745;
                Str *_t4746 = Str_concat(_t4744, &cur_mode->name);
                (void)_t4746;
                Str_delete(_t4744, &(Bool){1});
                Array_set(_va98, &(U64){_t4745}, _t4746);
                ;
                println(_va98);
                U32 _t4747 = 0;
                (void)_t4747;
                ast_print(ast, _t4747);
                ;
            } else {
                Str *_t4748 = Str_lit("Str", 3ULL);
                (void)_t4748;
                U64 _t4749; { U64 *_hp = (U64 *)Str_size(); _t4749 = *_hp; free(_hp); }
                (void)_t4749;
                U64 _t4750 = 1;
                (void)_t4750;
                Array *_va99 = Array_new(_t4748, &(U64){_t4749}, &(U64){_t4750});
                (void)_va99;
                Str_delete(_t4748, &(Bool){1});
                ;
                ;
                Str *_t4751 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4751;
                Str *_t4752 = Str_concat(_t4751, command);
                (void)_t4752;
                Str_delete(_t4751, &(Bool){1});
                Str *_t4753 = Str_lit("'", 1ULL);
                (void)_t4753;
                U64 _t4754 = 0;
                (void)_t4754;
                Str *_t4755 = Str_concat(_t4752, _t4753);
                (void)_t4755;
                Str_delete(_t4752, &(Bool){1});
                Str_delete(_t4753, &(Bool){1});
                Array_set(_va99, &(U64){_t4754}, _t4755);
                ;
                println(_va99);
                usage();
                I32 _t4756 = 1;
                (void)_t4756;
                result = _t4756;
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
    I64 _t4846 = I32_to_i64(result);
    (void)_t4846;
    ;
    exit(_t4846);
    ;
    return 0;
}

