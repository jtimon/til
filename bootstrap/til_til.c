#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4256 = Str_lit("Str", 3ULL);
    (void)_t4256;
    U64 _t4257; { U64 *_hp = (U64 *)Str_size(); _t4257 = *_hp; free(_hp); }
    (void)_t4257;
    Vec *paths = Vec_new(_t4256, &(U64){_t4257});
    (void)paths;
    Str_delete(_t4256, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4231 = expr_nchildren(body);
        (void)_t4231;
        Bool _wcond4227; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4231}); _wcond4227 = *_hp; free(_hp); }
        (void)_wcond4227;
        ;
        if (_wcond4227) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4232 = expr_get_tag(stmt);
        (void)_t4232;
        U32 _t4233 = expr_nchildren(stmt);
        (void)_t4233;
        U32 _t4234 = 2;
        (void)_t4234;
        Bool _t4235 = I32_eq(_t4232, DEREF(NODE_FCALL));
        (void)_t4235;
        ;
        Bool _t4236 = U32_eq(_t4233, _t4234);
        (void)_t4236;
        ;
        ;
        U32 *_t4237 = malloc(sizeof(U32));
        *_t4237 = 0;
        (void)_t4237;
        Expr *_t4238 = expr_get_child(stmt, DEREF(_t4237));
        (void)_t4238;
        I32 _t4239 = expr_get_tag(_t4238);
        (void)_t4239;
        U32_delete(_t4237, &(Bool){1});
        Bool _t4240 = Bool_and(_t4235, _t4236);
        (void)_t4240;
        ;
        ;
        Bool _t4241 = I32_eq(_t4239, DEREF(NODE_IDENT));
        (void)_t4241;
        ;
        U32 *_t4242 = malloc(sizeof(U32));
        *_t4242 = 0;
        (void)_t4242;
        Expr *_t4243 = expr_get_child(stmt, DEREF(_t4242));
        (void)_t4243;
        Str *_t4244 = expr_get_str_val(_t4243);
        (void)_t4244;
        Str *_t4245 = Str_lit("import", 6ULL);
        (void)_t4245;
        Bool _t4246 = Bool_and(_t4240, _t4241);
        (void)_t4246;
        ;
        ;
        Bool _t4247; { Bool *_hp = (Bool *)Str_eq(_t4244, _t4245); _t4247 = *_hp; free(_hp); }
        (void)_t4247;
        U32_delete(_t4242, &(Bool){1});
        Str_delete(_t4245, &(Bool){1});
        U32 *_t4248 = malloc(sizeof(U32));
        *_t4248 = 1;
        (void)_t4248;
        Expr *_t4249 = expr_get_child(stmt, DEREF(_t4248));
        (void)_t4249;
        I32 _t4250 = expr_get_tag(_t4249);
        (void)_t4250;
        U32_delete(_t4248, &(Bool){1});
        Bool _t4251 = Bool_and(_t4246, _t4247);
        (void)_t4251;
        ;
        ;
        Bool _t4252 = I32_eq(_t4250, DEREF(NODE_LITERAL_STR));
        (void)_t4252;
        ;
        Bool _t4253 = Bool_and(_t4251, _t4252);
        (void)_t4253;
        ;
        ;
        if (_t4253) {
            U32 *_t4228 = malloc(sizeof(U32));
            *_t4228 = 1;
            (void)_t4228;
            Expr *_t4229 = expr_get_child(stmt, DEREF(_t4228));
            (void)_t4229;
            Str *path = expr_get_str_val(_t4229);
            (void)path;
            Str *_t4230 = Str_clone(path);
            (void)_t4230;
            U32_delete(_t4228, &(Bool){1});
            Vec_push(paths, _t4230);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4254 = 1;
        (void)_t4254;
        U32 _t4255 = U32_add(DEREF(i), _t4254);
        (void)_t4255;
        ;
        *i = _t4255;
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
        U64 _fi4258 = 0;
        (void)_fi4258;
        while (1) {
            U64 _t4288 = 0;
            (void)_t4288;
            U64 _t4289; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4289 = *_hp; free(_hp); }
            (void)_t4289;
            Range *_t4290 = Range_new(_t4288, _t4289);
            (void)_t4290;
            ;
            ;
            U64 _t4291; { U64 *_hp = (U64 *)Range_len(_t4290); _t4291 = *_hp; free(_hp); }
            (void)_t4291;
            Range_delete(_t4290, &(Bool){1});
            Bool _wcond4259; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4258}, &(U64){_t4291}); _wcond4259 = *_hp; free(_hp); }
            (void)_wcond4259;
            ;
            if (_wcond4259) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4292 = 0;
            (void)_t4292;
            U64 _t4293; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4293 = *_hp; free(_hp); }
            (void)_t4293;
            Range *_t4294 = Range_new(_t4292, _t4293);
            (void)_t4294;
            ;
            ;
            U64 *i = Range_get(_t4294, _fi4258);
            (void)i;
            Range_delete(_t4294, &(Bool){1});
            U64 _t4295 = 1;
            (void)_t4295;
            U64 _t4296 = U64_add(_fi4258, _t4295);
            (void)_t4296;
            ;
            _fi4258 = _t4296;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4297 = Str_lit("/", 1ULL);
            (void)_t4297;
            Str *_t4298 = Str_concat(base_dir, _t4297);
            (void)_t4298;
            Str_delete(_t4297, &(Bool){1});
            Str *try_path = Str_concat(_t4298, import_path);
            (void)try_path;
            Str_delete(_t4298, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4299 = Str_lit("", 0ULL);
            (void)_t4299;
            U64 _t4300; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4300 = *_hp; free(_hp); }
            (void)_t4300;
            U64 _t4301 = 0;
            (void)_t4301;
            Bool _t4302; { Bool *_hp = (Bool *)Str_eq(abs, _t4299); _t4302 = *_hp; free(_hp); }
            (void)_t4302;
            Str_delete(_t4299, &(Bool){1});
            Bool _t4303; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4300}, &(U64){_t4301}); _t4303 = *_hp; free(_hp); }
            (void)_t4303;
            ;
            ;
            Bool _t4304 = Bool_and(_t4302, _t4303);
            (void)_t4304;
            ;
            ;
            if (_t4304) {
                Str *_t4260 = Str_lit("/", 1ULL);
                (void)_t4260;
                Str *_t4261 = Str_concat(lib_dir, _t4260);
                (void)_t4261;
                Str_delete(_t4260, &(Bool){1});
                try_path = Str_concat(_t4261, import_path);
                Str_delete(_t4261, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4305 = Str_lit("", 0ULL);
            (void)_t4305;
            Bool _t4306; { Bool *_hp = (Bool *)Str_eq(abs, _t4305); _t4306 = *_hp; free(_hp); }
            (void)_t4306;
            Str_delete(_t4305, &(Bool){1});
            if (_t4306) {
                Str *_t4262 = Str_lit("Str", 3ULL);
                (void)_t4262;
                U64 _t4263; { U64 *_hp = (U64 *)Str_size(); _t4263 = *_hp; free(_hp); }
                (void)_t4263;
                U64 _t4264 = 1;
                (void)_t4264;
                Array *_va72 = Array_new(_t4262, &(U64){_t4263}, &(U64){_t4264});
                (void)_va72;
                Str_delete(_t4262, &(Bool){1});
                ;
                ;
                Str *_t4265 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4265;
                Str *_t4266 = Str_concat(_t4265, import_path);
                (void)_t4266;
                Str_delete(_t4265, &(Bool){1});
                Str *_t4267 = Str_lit("' (from ", 8ULL);
                (void)_t4267;
                Str *_t4268 = Str_concat(_t4266, _t4267);
                (void)_t4268;
                Str_delete(_t4266, &(Bool){1});
                Str_delete(_t4267, &(Bool){1});
                Str *_t4269 = Str_concat(_t4268, base_dir);
                (void)_t4269;
                Str_delete(_t4268, &(Bool){1});
                Str *_t4270 = Str_lit("/)", 2ULL);
                (void)_t4270;
                U64 _t4271 = 0;
                (void)_t4271;
                Str *_t4272 = Str_concat(_t4269, _t4270);
                (void)_t4272;
                Str_delete(_t4269, &(Bool){1});
                Str_delete(_t4270, &(Bool){1});
                Array_set(_va72, &(U64){_t4271}, _t4272);
                ;
                println(_va72);
                I64 _t4273 = 1;
                (void)_t4273;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4273; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4307 = til_set_has(resolved_set, abs);
            (void)_t4307;
            if (_t4307) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            til_set_add(resolved_set, abs);
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
            U64 _t4308; { U64 *_hp = (U64 *)Str_len(abs); _t4308 = *_hp; free(_hp); }
            (void)_t4308;
            U64 _t4309 = 1;
            (void)_t4309;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4308, _t4309);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4275 = 0;
                (void)_t4275;
                U8 *_t4276 = Str_get(abs, last_slash);
                (void)_t4276;
                U8 _t4277 = 47;
                (void)_t4277;
                Bool _t4278; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4275}); _t4278 = *_hp; free(_hp); }
                (void)_t4278;
                ;
                Bool _t4279; { Bool *_hp = (Bool *)U8_neq(_t4276, &(U8){_t4277}); _t4279 = *_hp; free(_hp); }
                (void)_t4279;
                ;
                Bool _wcond4274 = Bool_and(_t4278, _t4279);
                (void)_wcond4274;
                ;
                ;
                if (_wcond4274) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4280 = 1;
                (void)_t4280;
                U64 _t4281 = U64_sub(DEREF(last_slash), _t4280);
                (void)_t4281;
                ;
                *last_slash = _t4281;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4310; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4310 = *_hp; free(_hp); }
            (void)_t4310;
            U64 _t4311 = 0;
            (void)_t4311;
            Bool _t4312; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4310}, &(U64){_t4311}); _t4312 = *_hp; free(_hp); }
            (void)_t4312;
            ;
            ;
            if (_t4312) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4282 = 0;
                (void)_t4282;
                Bool _t4283; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4282}); _t4283 = *_hp; free(_hp); }
                (void)_t4283;
                ;
                if (_t4283) {
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
                U32 _t4285 = expr_nchildren(sub_ast);
                (void)_t4285;
                Bool _wcond4284; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4285}); _wcond4284 = *_hp; free(_hp); }
                (void)_wcond4284;
                ;
                if (_wcond4284) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4286 = 1;
                (void)_t4286;
                U32 _t4287 = U32_add(DEREF(k), _t4286);
                (void)_t4287;
                ;
                *k = _t4287;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t4313 = 0;
    (void)_t4313;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4313; return _r; }
}

void usage(void) {
    Str *_t4314 = Str_lit("Str", 3ULL);
    (void)_t4314;
    U64 _t4315; { U64 *_hp = (U64 *)Str_size(); _t4315 = *_hp; free(_hp); }
    (void)_t4315;
    U64 _t4316 = 1;
    (void)_t4316;
    Array *_va73 = Array_new(_t4314, &(U64){_t4315}, &(U64){_t4316});
    (void)_va73;
    Str_delete(_t4314, &(Bool){1});
    ;
    ;
    U64 _t4317 = 0;
    (void)_t4317;
    Str *_t4318 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4318;
    Array_set(_va73, &(U64){_t4317}, _t4318);
    ;
    println(_va73);
    Str *_t4319 = Str_lit("Str", 3ULL);
    (void)_t4319;
    U64 _t4320; { U64 *_hp = (U64 *)Str_size(); _t4320 = *_hp; free(_hp); }
    (void)_t4320;
    U64 _t4321 = 1;
    (void)_t4321;
    Array *_va74 = Array_new(_t4319, &(U64){_t4320}, &(U64){_t4321});
    (void)_va74;
    Str_delete(_t4319, &(Bool){1});
    ;
    ;
    U64 _t4322 = 0;
    (void)_t4322;
    Str *_t4323 = Str_lit("", 0ULL);
    (void)_t4323;
    Array_set(_va74, &(U64){_t4322}, _t4323);
    ;
    println(_va74);
    Str *_t4324 = Str_lit("Str", 3ULL);
    (void)_t4324;
    U64 _t4325; { U64 *_hp = (U64 *)Str_size(); _t4325 = *_hp; free(_hp); }
    (void)_t4325;
    U64 _t4326 = 1;
    (void)_t4326;
    Array *_va75 = Array_new(_t4324, &(U64){_t4325}, &(U64){_t4326});
    (void)_va75;
    Str_delete(_t4324, &(Bool){1});
    ;
    ;
    U64 _t4327 = 0;
    (void)_t4327;
    Str *_t4328 = Str_lit("Commands:", 9ULL);
    (void)_t4328;
    Array_set(_va75, &(U64){_t4327}, _t4328);
    ;
    println(_va75);
    Str *_t4329 = Str_lit("Str", 3ULL);
    (void)_t4329;
    U64 _t4330; { U64 *_hp = (U64 *)Str_size(); _t4330 = *_hp; free(_hp); }
    (void)_t4330;
    U64 _t4331 = 1;
    (void)_t4331;
    Array *_va76 = Array_new(_t4329, &(U64){_t4330}, &(U64){_t4331});
    (void)_va76;
    Str_delete(_t4329, &(Bool){1});
    ;
    ;
    U64 _t4332 = 0;
    (void)_t4332;
    Str *_t4333 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4333;
    Array_set(_va76, &(U64){_t4332}, _t4333);
    ;
    println(_va76);
    Str *_t4334 = Str_lit("Str", 3ULL);
    (void)_t4334;
    U64 _t4335; { U64 *_hp = (U64 *)Str_size(); _t4335 = *_hp; free(_hp); }
    (void)_t4335;
    U64 _t4336 = 1;
    (void)_t4336;
    Array *_va77 = Array_new(_t4334, &(U64){_t4335}, &(U64){_t4336});
    (void)_va77;
    Str_delete(_t4334, &(Bool){1});
    ;
    ;
    U64 _t4337 = 0;
    (void)_t4337;
    Str *_t4338 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4338;
    Array_set(_va77, &(U64){_t4337}, _t4338);
    ;
    println(_va77);
    Str *_t4339 = Str_lit("Str", 3ULL);
    (void)_t4339;
    U64 _t4340; { U64 *_hp = (U64 *)Str_size(); _t4340 = *_hp; free(_hp); }
    (void)_t4340;
    U64 _t4341 = 1;
    (void)_t4341;
    Array *_va78 = Array_new(_t4339, &(U64){_t4340}, &(U64){_t4341});
    (void)_va78;
    Str_delete(_t4339, &(Bool){1});
    ;
    ;
    U64 _t4342 = 0;
    (void)_t4342;
    Str *_t4343 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4343;
    Array_set(_va78, &(U64){_t4342}, _t4343);
    ;
    println(_va78);
    Str *_t4344 = Str_lit("Str", 3ULL);
    (void)_t4344;
    U64 _t4345; { U64 *_hp = (U64 *)Str_size(); _t4345 = *_hp; free(_hp); }
    (void)_t4345;
    U64 _t4346 = 1;
    (void)_t4346;
    Array *_va79 = Array_new(_t4344, &(U64){_t4345}, &(U64){_t4346});
    (void)_va79;
    Str_delete(_t4344, &(Bool){1});
    ;
    ;
    U64 _t4347 = 0;
    (void)_t4347;
    Str *_t4348 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4348;
    Array_set(_va79, &(U64){_t4347}, _t4348);
    ;
    println(_va79);
    Str *_t4349 = Str_lit("Str", 3ULL);
    (void)_t4349;
    U64 _t4350; { U64 *_hp = (U64 *)Str_size(); _t4350 = *_hp; free(_hp); }
    (void)_t4350;
    U64 _t4351 = 1;
    (void)_t4351;
    Array *_va80 = Array_new(_t4349, &(U64){_t4350}, &(U64){_t4351});
    (void)_va80;
    Str_delete(_t4349, &(Bool){1});
    ;
    ;
    U64 _t4352 = 0;
    (void)_t4352;
    Str *_t4353 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4353;
    Array_set(_va80, &(U64){_t4352}, _t4353);
    ;
    println(_va80);
    Str *_t4354 = Str_lit("Str", 3ULL);
    (void)_t4354;
    U64 _t4355; { U64 *_hp = (U64 *)Str_size(); _t4355 = *_hp; free(_hp); }
    (void)_t4355;
    U64 _t4356 = 1;
    (void)_t4356;
    Array *_va81 = Array_new(_t4354, &(U64){_t4355}, &(U64){_t4356});
    (void)_va81;
    Str_delete(_t4354, &(Bool){1});
    ;
    ;
    U64 _t4357 = 0;
    (void)_t4357;
    Str *_t4358 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4358;
    Array_set(_va81, &(U64){_t4357}, _t4358);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4364 = 1;
    (void)_t4364;
    e->is_core = _t4364;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4360 = expr_nchildren(e);
        (void)_t4360;
        Bool _wcond4359; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4360}); _wcond4359 = *_hp; free(_hp); }
        (void)_wcond4359;
        ;
        if (_wcond4359) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4361 = expr_get_child(e, DEREF(i));
        (void)_t4361;
        mark_core(_t4361);
        U32 _t4362 = 1;
        (void)_t4362;
        U32 _t4363 = U32_add(DEREF(i), _t4362);
        (void)_t4363;
        ;
        *i = _t4363;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4820 = malloc(sizeof(I64));
    *_t4820 = 0;
    (void)_t4820;
    _t4821 = malloc(sizeof(I64));
    *_t4821 = 1;
    (void)_t4821;
    _t4822 = malloc(sizeof(I64)); *_t4822 = I64_sub(DEREF(_t4820), DEREF(_t4821));
    (void)_t4822;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4822));
    (void)CAP_LIT;
    _t4823 = malloc(sizeof(I64));
    *_t4823 = 0;
    (void)_t4823;
    _t4824 = malloc(sizeof(I64));
    *_t4824 = 2;
    (void)_t4824;
    _t4825 = malloc(sizeof(I64)); *_t4825 = I64_sub(DEREF(_t4823), DEREF(_t4824));
    (void)_t4825;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4825));
    (void)CAP_VIEW;
    _t4826 = Str_lit("Str", 3ULL);
    (void)_t4826;
    _t4827 = Str_size();
    (void)_t4827;
    _t4828 = Str_lit("Mode", 4ULL);
    (void)_t4828;
    _t4829 = Mode_size();
    (void)_t4829;
    core_modes = Map_new(_t4826, _t4827, _t4828, _t4829);
    (void)core_modes;
    _t4830 = malloc(sizeof(Bool));
    *_t4830 = 0;
    (void)_t4830;
    _t4831 = malloc(sizeof(Bool));
    *_t4831 = 0;
    (void)_t4831;
    _t4832 = malloc(sizeof(Bool));
    *_t4832 = 0;
    (void)_t4832;
    _t4833 = malloc(sizeof(Bool));
    *_t4833 = 0;
    (void)_t4833;
    _t4834 = Str_lit("script", 6ULL);
    (void)_t4834;
    _t4835 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4835->name = *_ca; free(_ca); }
    _t4835->needs_main = DEREF(_t4830);
    _t4835->decls_only = DEREF(_t4831);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4835->auto_import = *_ca; free(_ca); }
    _t4835->is_pure = DEREF(_t4832);
    _t4835->debug_prints = DEREF(_t4833);
    (void)_t4835;
    _t4836 = malloc(sizeof(Bool));
    *_t4836 = 1;
    (void)_t4836;
    _t4837 = malloc(sizeof(Bool));
    *_t4837 = 1;
    (void)_t4837;
    _t4838 = malloc(sizeof(Bool));
    *_t4838 = 0;
    (void)_t4838;
    _t4839 = malloc(sizeof(Bool));
    *_t4839 = 0;
    (void)_t4839;
    _t4840 = Str_lit("cli", 3ULL);
    (void)_t4840;
    _t4841 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4841->name = *_ca; free(_ca); }
    _t4841->needs_main = DEREF(_t4836);
    _t4841->decls_only = DEREF(_t4837);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4841->auto_import = *_ca; free(_ca); }
    _t4841->is_pure = DEREF(_t4838);
    _t4841->debug_prints = DEREF(_t4839);
    (void)_t4841;
    _t4842 = malloc(sizeof(Bool));
    *_t4842 = 1;
    (void)_t4842;
    _t4843 = malloc(sizeof(Bool));
    *_t4843 = 1;
    (void)_t4843;
    _t4844 = malloc(sizeof(Bool));
    *_t4844 = 0;
    (void)_t4844;
    _t4845 = malloc(sizeof(Bool));
    *_t4845 = 0;
    (void)_t4845;
    _t4846 = Str_lit("gui", 3ULL);
    (void)_t4846;
    _t4847 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4847->name = *_ca; free(_ca); }
    _t4847->needs_main = DEREF(_t4842);
    _t4847->decls_only = DEREF(_t4843);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4847->auto_import = *_ca; free(_ca); }
    _t4847->is_pure = DEREF(_t4844);
    _t4847->debug_prints = DEREF(_t4845);
    (void)_t4847;
    _t4848 = malloc(sizeof(Bool));
    *_t4848 = 0;
    (void)_t4848;
    _t4849 = malloc(sizeof(Bool));
    *_t4849 = 1;
    (void)_t4849;
    _t4850 = malloc(sizeof(Bool));
    *_t4850 = 0;
    (void)_t4850;
    _t4851 = malloc(sizeof(Bool));
    *_t4851 = 0;
    (void)_t4851;
    _t4852 = Str_lit("test", 4ULL);
    (void)_t4852;
    _t4853 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4853->name = *_ca; free(_ca); }
    _t4853->needs_main = DEREF(_t4848);
    _t4853->decls_only = DEREF(_t4849);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4853->auto_import = *_ca; free(_ca); }
    _t4853->is_pure = DEREF(_t4850);
    _t4853->debug_prints = DEREF(_t4851);
    (void)_t4853;
    _t4854 = malloc(sizeof(Bool));
    *_t4854 = 0;
    (void)_t4854;
    _t4855 = malloc(sizeof(Bool));
    *_t4855 = 1;
    (void)_t4855;
    _t4856 = malloc(sizeof(Bool));
    *_t4856 = 1;
    (void)_t4856;
    _t4857 = malloc(sizeof(Bool));
    *_t4857 = 0;
    (void)_t4857;
    _t4858 = Str_lit("pure", 4ULL);
    (void)_t4858;
    _t4859 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4859->name = *_ca; free(_ca); }
    _t4859->needs_main = DEREF(_t4854);
    _t4859->decls_only = DEREF(_t4855);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4859->auto_import = *_ca; free(_ca); }
    _t4859->is_pure = DEREF(_t4856);
    _t4859->debug_prints = DEREF(_t4857);
    (void)_t4859;
    _t4860 = malloc(sizeof(Bool));
    *_t4860 = 0;
    (void)_t4860;
    _t4861 = malloc(sizeof(Bool));
    *_t4861 = 1;
    (void)_t4861;
    _t4862 = malloc(sizeof(Bool));
    *_t4862 = 1;
    (void)_t4862;
    _t4863 = malloc(sizeof(Bool));
    *_t4863 = 1;
    (void)_t4863;
    _t4864 = Str_lit("pura", 4ULL);
    (void)_t4864;
    _t4865 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4865->name = *_ca; free(_ca); }
    _t4865->needs_main = DEREF(_t4860);
    _t4865->decls_only = DEREF(_t4861);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4865->auto_import = *_ca; free(_ca); }
    _t4865->is_pure = DEREF(_t4862);
    _t4865->debug_prints = DEREF(_t4863);
    (void)_t4865;
    _t4866 = malloc(sizeof(Bool));
    *_t4866 = 0;
    (void)_t4866;
    _t4867 = malloc(sizeof(Bool));
    *_t4867 = 1;
    (void)_t4867;
    _t4868 = malloc(sizeof(Bool));
    *_t4868 = 0;
    (void)_t4868;
    _t4869 = malloc(sizeof(Bool));
    *_t4869 = 0;
    (void)_t4869;
    _t4870 = Str_lit("lib", 3ULL);
    (void)_t4870;
    _t4871 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4871->name = *_ca; free(_ca); }
    _t4871->needs_main = DEREF(_t4866);
    _t4871->decls_only = DEREF(_t4867);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4871->auto_import = *_ca; free(_ca); }
    _t4871->is_pure = DEREF(_t4868);
    _t4871->debug_prints = DEREF(_t4869);
    (void)_t4871;
    _t4872 = malloc(sizeof(Bool));
    *_t4872 = 0;
    (void)_t4872;
    _t4873 = malloc(sizeof(Bool));
    *_t4873 = 1;
    (void)_t4873;
    _t4874 = malloc(sizeof(Bool));
    *_t4874 = 0;
    (void)_t4874;
    _t4875 = malloc(sizeof(Bool));
    *_t4875 = 1;
    (void)_t4875;
    _t4876 = Str_lit("liba", 4ULL);
    (void)_t4876;
    _t4877 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4877->name = *_ca; free(_ca); }
    _t4877->needs_main = DEREF(_t4872);
    _t4877->decls_only = DEREF(_t4873);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4877->auto_import = *_ca; free(_ca); }
    _t4877->is_pure = DEREF(_t4874);
    _t4877->debug_prints = DEREF(_t4875);
    (void)_t4877;
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
    U64 _t4742; { U64 *_hp = (U64 *)Array_len(args); _t4742 = *_hp; free(_hp); }
    (void)_t4742;
    U64 _t4743 = 0;
    (void)_t4743;
    Bool _t4744 = U64_eq(_t4742, _t4743);
    (void)_t4744;
    ;
    ;
    if (_t4744) {
        usage();
        Str *_t4365 = Str_lit("Str", 3ULL);
        (void)_t4365;
        U64 _t4366; { U64 *_hp = (U64 *)Str_size(); _t4366 = *_hp; free(_hp); }
        (void)_t4366;
        U64 _t4367 = 1;
        (void)_t4367;
        Array *_va82 = Array_new(_t4365, &(U64){_t4366}, &(U64){_t4367});
        (void)_va82;
        Str_delete(_t4365, &(Bool){1});
        ;
        ;
        U64 _t4368 = 0;
        (void)_t4368;
        Str *_t4369 = Str_lit("no arguments", 12ULL);
        (void)_t4369;
        Array_set(_va82, &(U64){_t4368}, _t4369);
        ;
        Str *_t4370 = Str_lit("src/til.til:209:15", 18ULL);
        (void)_t4370;
        panic(_t4370, _va82);
        Str_delete(_t4370, &(Bool){1});
    }
    ;
    U64 *_t4745 = malloc(sizeof(U64));
    *_t4745 = 0;
    (void)_t4745;
    Str *cmd_ref = Array_get(args, _t4745);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4745, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4746; { U64 *_hp = (U64 *)Array_len(args); _t4746 = *_hp; free(_hp); }
    (void)_t4746;
    U64 _t4747 = 1;
    (void)_t4747;
    Bool _t4748 = U64_eq(_t4746, _t4747);
    (void)_t4748;
    ;
    ;
    if (_t4748) {
        Str *_t4371 = Str_lit("help", 4ULL);
        (void)_t4371;
        Str *_t4372 = Str_lit("--help", 6ULL);
        (void)_t4372;
        Bool _t4373; { Bool *_hp = (Bool *)Str_eq(command, _t4371); _t4373 = *_hp; free(_hp); }
        (void)_t4373;
        Str_delete(_t4371, &(Bool){1});
        Bool _t4374; { Bool *_hp = (Bool *)Str_eq(command, _t4372); _t4374 = *_hp; free(_hp); }
        (void)_t4374;
        Str_delete(_t4372, &(Bool){1});
        Bool _t4375 = Bool_or(_t4373, _t4374);
        (void)_t4375;
        ;
        ;
        if (_t4375) {
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
            U64 _t4392; { U64 *_hp = (U64 *)Array_len(args); _t4392 = *_hp; free(_hp); }
            (void)_t4392;
            Bool _wcond4376; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4392}); _wcond4376 = *_hp; free(_hp); }
            (void)_wcond4376;
            ;
            if (_wcond4376) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4393 = Str_lit("-o", 2ULL);
            (void)_t4393;
            U64 _t4394 = 1;
            (void)_t4394;
            U64 _t4395 = U64_add(DEREF(path_idx), _t4394);
            (void)_t4395;
            ;
            U64 _t4396; { U64 *_hp = (U64 *)Array_len(args); _t4396 = *_hp; free(_hp); }
            (void)_t4396;
            Bool _t4397; { Bool *_hp = (Bool *)Str_eq(flag, _t4393); _t4397 = *_hp; free(_hp); }
            (void)_t4397;
            Str_delete(_t4393, &(Bool){1});
            Bool _t4398; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4395}, &(U64){_t4396}); _t4398 = *_hp; free(_hp); }
            (void)_t4398;
            ;
            ;
            Bool _t4399 = Bool_and(_t4397, _t4398);
            (void)_t4399;
            ;
            ;
            if (_t4399) {
                U64 _t4377 = 1;
                (void)_t4377;
                U64 *_t4378 = malloc(sizeof(U64)); *_t4378 = U64_add(DEREF(path_idx), _t4377);
                (void)_t4378;
                ;
                Str *oval = Array_get(args, _t4378);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4378, &(Bool){1});
                U64 _t4379 = 2;
                (void)_t4379;
                U64 _t4380 = U64_add(DEREF(path_idx), _t4379);
                (void)_t4380;
                ;
                *path_idx = _t4380;
                ;
            } else {
                Str *_t4385 = Str_lit("-c", 2ULL);
                (void)_t4385;
                U64 _t4386 = 1;
                (void)_t4386;
                U64 _t4387 = U64_add(DEREF(path_idx), _t4386);
                (void)_t4387;
                ;
                U64 _t4388; { U64 *_hp = (U64 *)Array_len(args); _t4388 = *_hp; free(_hp); }
                (void)_t4388;
                Bool _t4389; { Bool *_hp = (Bool *)Str_eq(flag, _t4385); _t4389 = *_hp; free(_hp); }
                (void)_t4389;
                Str_delete(_t4385, &(Bool){1});
                Bool _t4390; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4387}, &(U64){_t4388}); _t4390 = *_hp; free(_hp); }
                (void)_t4390;
                ;
                ;
                Bool _t4391 = Bool_and(_t4389, _t4390);
                (void)_t4391;
                ;
                ;
                if (_t4391) {
                    U64 _t4381 = 1;
                    (void)_t4381;
                    U64 *_t4382 = malloc(sizeof(U64)); *_t4382 = U64_add(DEREF(path_idx), _t4381);
                    (void)_t4382;
                    ;
                    Str *cval = Array_get(args, _t4382);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4382, &(Bool){1});
                    U64 _t4383 = 2;
                    (void)_t4383;
                    U64 _t4384 = U64_add(DEREF(path_idx), _t4383);
                    (void)_t4384;
                    ;
                    *path_idx = _t4384;
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
    Str *_t4749 = Str_lit("help", 4ULL);
    (void)_t4749;
    Str *_t4750 = Str_lit("--help", 6ULL);
    (void)_t4750;
    Bool _t4751; { Bool *_hp = (Bool *)Str_eq(command, _t4749); _t4751 = *_hp; free(_hp); }
    (void)_t4751;
    Str_delete(_t4749, &(Bool){1});
    Bool _t4752; { Bool *_hp = (Bool *)Str_eq(command, _t4750); _t4752 = *_hp; free(_hp); }
    (void)_t4752;
    Str_delete(_t4750, &(Bool){1});
    Bool _t4753 = Bool_or(_t4751, _t4752);
    (void)_t4753;
    ;
    ;
    if (_t4753) {
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
    Str *_t4754 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4754;
    Str *core_path = Str_concat(bin_dir, _t4754);
    (void)core_path;
    Str_delete(_t4754, &(Bool){1});
    Str *_t4755 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4755;
    Str *ext_c_path = Str_concat(bin_dir, _t4755);
    (void)ext_c_path;
    Str_delete(_t4755, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4756; { U64 *_hp = (U64 *)Str_len(abs_path); _t4756 = *_hp; free(_hp); }
    (void)_t4756;
    U64 _t4757 = 0;
    (void)_t4757;
    Bool _t4758; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4756}, &(U64){_t4757}); _t4758 = *_hp; free(_hp); }
    (void)_t4758;
    ;
    ;
    if (_t4758) {
        U64 _t4408; { U64 *_hp = (U64 *)Str_len(abs_path); _t4408 = *_hp; free(_hp); }
        (void)_t4408;
        U64 _t4409 = 1;
        (void)_t4409;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4408, _t4409);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4401 = 0;
            (void)_t4401;
            U8 *_t4402 = Str_get(abs_path, last_slash);
            (void)_t4402;
            U8 _t4403 = 47;
            (void)_t4403;
            Bool _t4404; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4401}); _t4404 = *_hp; free(_hp); }
            (void)_t4404;
            ;
            Bool _t4405; { Bool *_hp = (Bool *)U8_neq(_t4402, &(U8){_t4403}); _t4405 = *_hp; free(_hp); }
            (void)_t4405;
            ;
            Bool _wcond4400 = Bool_and(_t4404, _t4405);
            (void)_wcond4400;
            ;
            ;
            if (_wcond4400) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4406 = 1;
            (void)_t4406;
            U64 _t4407 = U64_sub(DEREF(last_slash), _t4406);
            (void)_t4407;
            ;
            *last_slash = _t4407;
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
    U64 _t4759; { U64 *_hp = (U64 *)Str_len(core_abs); _t4759 = *_hp; free(_hp); }
    (void)_t4759;
    U64 _t4760 = 0;
    (void)_t4760;
    Bool _t4761; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4759}, &(U64){_t4760}); _t4761 = *_hp; free(_hp); }
    (void)_t4761;
    ;
    ;
    if (_t4761) {
        Bool _t4411 = til_set_has(resolved, core_abs);
        (void)_t4411;
        if (_t4411) {
            Bool _t4410 = 1;
            (void)_t4410;
            skip_core = _t4410;
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
    U64 _t4762; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4762 = *_hp; free(_hp); }
    (void)_t4762;
    U64 _t4763 = 0;
    (void)_t4763;
    Bool _t4764; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4762}, &(U64){_t4763}); _t4764 = *_hp; free(_hp); }
    (void)_t4764;
    ;
    ;
    Bool _t4765 = Bool_not(skip_core);
    (void)_t4765;
    Bool _t4766 = Bool_and(_t4764, _t4765);
    (void)_t4766;
    ;
    ;
    if (_t4766) {
        Str *_t4418 = Str_lit("/src/core", 9ULL);
        (void)_t4418;
        Str *core_dir = Str_concat(bin_dir, _t4418);
        (void)core_dir;
        Str_delete(_t4418, &(Bool){1});
        Str *_t4419 = Str_lit("", 0ULL);
        (void)_t4419;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4419); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4419, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4420 = 0;
        (void)_t4420;
        Bool _t4421; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4420}); _t4421 = *_hp; free(_hp); }
        (void)_t4421;
        ;
        ;
        if (_t4421) {
            Str *_t4412 = Str_lit("Str", 3ULL);
            (void)_t4412;
            U64 _t4413; { U64 *_hp = (U64 *)Str_size(); _t4413 = *_hp; free(_hp); }
            (void)_t4413;
            U64 _t4414 = 1;
            (void)_t4414;
            Array *_va83 = Array_new(_t4412, &(U64){_t4413}, &(U64){_t4414});
            (void)_va83;
            Str_delete(_t4412, &(Bool){1});
            ;
            ;
            U64 _t4415 = 0;
            (void)_t4415;
            Str *_t4416 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4416;
            Array_set(_va83, &(U64){_t4415}, _t4416);
            ;
            Str *_t4417 = Str_lit("src/til.til:295:19", 18ULL);
            (void)_t4417;
            panic(_t4417, _va83);
            Str_delete(_t4417, &(Bool){1});
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
    Str *_t4767 = Str_lit("script", 6ULL);
    (void)_t4767;
    Mode *cur_mode = mode_resolve(_t4767);
    (void)cur_mode;
    Str_delete(_t4767, &(Bool){1});
    U64 _t4768; { U64 *_hp = (U64 *)Str_len(mode_str); _t4768 = *_hp; free(_hp); }
    (void)_t4768;
    U64 _t4769 = 0;
    (void)_t4769;
    Bool _t4770; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4768}, &(U64){_t4769}); _t4770 = *_hp; free(_hp); }
    (void)_t4770;
    ;
    ;
    if (_t4770) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4431; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4431 = *_hp; free(_hp); }
        (void)_t4431;
        U64 _t4432 = 0;
        (void)_t4432;
        Bool _t4433 = U64_eq(_t4431, _t4432);
        (void)_t4433;
        ;
        ;
        if (_t4433) {
            Str *_t4422 = Str_lit("Str", 3ULL);
            (void)_t4422;
            U64 _t4423; { U64 *_hp = (U64 *)Str_size(); _t4423 = *_hp; free(_hp); }
            (void)_t4423;
            U64 _t4424 = 1;
            (void)_t4424;
            Array *_va84 = Array_new(_t4422, &(U64){_t4423}, &(U64){_t4424});
            (void)_va84;
            Str_delete(_t4422, &(Bool){1});
            ;
            ;
            Str *_t4425 = Str_lit("unknown mode '", 14ULL);
            (void)_t4425;
            Str *_t4426 = Str_concat(_t4425, mode_str);
            (void)_t4426;
            Str_delete(_t4425, &(Bool){1});
            Str *_t4427 = Str_lit("'", 1ULL);
            (void)_t4427;
            U64 _t4428 = 0;
            (void)_t4428;
            Str *_t4429 = Str_concat(_t4426, _t4427);
            (void)_t4429;
            Str_delete(_t4426, &(Bool){1});
            Str_delete(_t4427, &(Bool){1});
            Array_set(_va84, &(U64){_t4428}, _t4429);
            ;
            Str *_t4430 = Str_lit("src/til.til:311:19", 18ULL);
            (void)_t4430;
            panic(_t4430, _va84);
            Str_delete(_t4430, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4771; { U64 *_hp = (U64 *)Vec_len(imports); _t4771 = *_hp; free(_hp); }
    (void)_t4771;
    U64 _t4772 = 0;
    (void)_t4772;
    Bool _t4773; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4771}, &(U64){_t4772}); _t4773 = *_hp; free(_hp); }
    (void)_t4773;
    ;
    ;
    if (_t4773) {
        Str *_t4440 = Str_lit("/src/lib", 8ULL);
        (void)_t4440;
        Str *lib_dir = Str_concat(bin_dir, _t4440);
        (void)lib_dir;
        Str_delete(_t4440, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4441 = 0;
        (void)_t4441;
        Bool _t4442; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4441}); _t4442 = *_hp; free(_hp); }
        (void)_t4442;
        ;
        ;
        if (_t4442) {
            Str *_t4434 = Str_lit("Str", 3ULL);
            (void)_t4434;
            U64 _t4435; { U64 *_hp = (U64 *)Str_size(); _t4435 = *_hp; free(_hp); }
            (void)_t4435;
            U64 _t4436 = 1;
            (void)_t4436;
            Array *_va85 = Array_new(_t4434, &(U64){_t4435}, &(U64){_t4436});
            (void)_va85;
            Str_delete(_t4434, &(Bool){1});
            ;
            ;
            U64 _t4437 = 0;
            (void)_t4437;
            Str *_t4438 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4438;
            Array_set(_va85, &(U64){_t4437}, _t4438);
            ;
            Str *_t4439 = Str_lit("src/til.til:325:19", 18ULL);
            (void)_t4439;
            panic(_t4439, _va85);
            Str_delete(_t4439, &(Bool){1});
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
    Bool _t4774 = Bool_not(skip_core);
    (void)_t4774;
    ;
    if (_t4774) {
        while (1) {
            U32 _t4444 = expr_nchildren(core_ast);
            (void)_t4444;
            Bool _wcond4443; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4444}); _wcond4443 = *_hp; free(_hp); }
            (void)_wcond4443;
            ;
            if (_wcond4443) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4445 = 1;
            (void)_t4445;
            U32 _t4446 = U32_add(DEREF(i), _t4445);
            (void)_t4446;
            ;
            *i = _t4446;
            ;
        }
        U32 _t4451 = 0;
        (void)_t4451;
        *i = _t4451;
        ;
        while (1) {
            U32 _t4448 = expr_vec_count(core_import_decls);
            (void)_t4448;
            Bool _wcond4447; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4448}); _wcond4447 = *_hp; free(_hp); }
            (void)_wcond4447;
            ;
            if (_wcond4447) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4449 = 1;
            (void)_t4449;
            U32 _t4450 = U32_add(DEREF(i), _t4449);
            (void)_t4450;
            ;
            *i = _t4450;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4775; { U64 *_hp = (U64 *)Str_len(auto_import); _t4775 = *_hp; free(_hp); }
    (void)_t4775;
    U64 _t4776 = 0;
    (void)_t4776;
    Bool _t4777; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4775}, &(U64){_t4776}); _t4777 = *_hp; free(_hp); }
    (void)_t4777;
    ;
    ;
    if (_t4777) {
        Str *_t4456 = Str_lit("/src/modes/", 11ULL);
        (void)_t4456;
        Str *_t4457 = Str_concat(bin_dir, _t4456);
        (void)_t4457;
        Str_delete(_t4456, &(Bool){1});
        Str *_t4458 = Str_concat(_t4457, auto_import);
        (void)_t4458;
        Str_delete(_t4457, &(Bool){1});
        Str *_t4459 = Str_lit(".til", 4ULL);
        (void)_t4459;
        Str *mode_til_path = Str_concat(_t4458, _t4459);
        (void)mode_til_path;
        Str_delete(_t4458, &(Bool){1});
        Str_delete(_t4459, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4460 = 0;
        (void)_t4460;
        *i = _t4460;
        ;
        while (1) {
            U32 _t4453 = expr_nchildren(mode_ast);
            (void)_t4453;
            Bool _wcond4452; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4453}); _wcond4452 = *_hp; free(_hp); }
            (void)_wcond4452;
            ;
            if (_wcond4452) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4454 = 1;
            (void)_t4454;
            U32 _t4455 = U32_add(DEREF(i), _t4454);
            (void)_t4455;
            ;
            *i = _t4455;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4778 = 0;
    (void)_t4778;
    *i = _t4778;
    ;
    while (1) {
        U32 _t4462 = expr_vec_count(import_decls);
        (void)_t4462;
        Bool _wcond4461; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4462}); _wcond4461 = *_hp; free(_hp); }
        (void)_wcond4461;
        ;
        if (_wcond4461) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4463 = 1;
        (void)_t4463;
        U32 _t4464 = U32_add(DEREF(i), _t4463);
        (void)_t4464;
        ;
        *i = _t4464;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4779 = 0;
    (void)_t4779;
    *i = _t4779;
    ;
    while (1) {
        U32 _t4466 = expr_nchildren(ast);
        (void)_t4466;
        Bool _wcond4465; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4466}); _wcond4465 = *_hp; free(_hp); }
        (void)_wcond4465;
        ;
        if (_wcond4465) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4467 = 1;
        (void)_t4467;
        U32 _t4468 = U32_add(DEREF(i), _t4467);
        (void)_t4468;
        ;
        *i = _t4468;
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
    U32 _t4780 = 0;
    (void)_t4780;
    *i = _t4780;
    ;
    while (1) {
        U32 _t4484 = expr_nchildren(ast);
        (void)_t4484;
        Bool _wcond4469; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4484}); _wcond4469 = *_hp; free(_hp); }
        (void)_wcond4469;
        ;
        if (_wcond4469) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4485 = expr_get_tag(stmt);
        (void)_t4485;
        U32 _t4486 = expr_nchildren(stmt);
        (void)_t4486;
        U32 _t4487 = 2;
        (void)_t4487;
        Bool _t4488 = I32_eq(_t4485, DEREF(NODE_FCALL));
        (void)_t4488;
        ;
        Bool _t4489 = U32_eq(_t4486, _t4487);
        (void)_t4489;
        ;
        ;
        U32 *_t4490 = malloc(sizeof(U32));
        *_t4490 = 0;
        (void)_t4490;
        Expr *_t4491 = expr_get_child(stmt, DEREF(_t4490));
        (void)_t4491;
        I32 _t4492 = expr_get_tag(_t4491);
        (void)_t4492;
        U32_delete(_t4490, &(Bool){1});
        Bool _t4493 = Bool_and(_t4488, _t4489);
        (void)_t4493;
        ;
        ;
        Bool _t4494 = I32_eq(_t4492, DEREF(NODE_IDENT));
        (void)_t4494;
        ;
        U32 *_t4495 = malloc(sizeof(U32));
        *_t4495 = 1;
        (void)_t4495;
        Expr *_t4496 = expr_get_child(stmt, DEREF(_t4495));
        (void)_t4496;
        I32 _t4497 = expr_get_tag(_t4496);
        (void)_t4497;
        U32_delete(_t4495, &(Bool){1});
        Bool _t4498 = Bool_and(_t4493, _t4494);
        (void)_t4498;
        ;
        ;
        Bool _t4499 = I32_eq(_t4497, DEREF(NODE_LITERAL_STR));
        (void)_t4499;
        ;
        Bool _t4500 = Bool_and(_t4498, _t4499);
        (void)_t4500;
        ;
        ;
        if (_t4500) {
            U32 *_t4478 = malloc(sizeof(U32));
            *_t4478 = 0;
            (void)_t4478;
            Expr *_t4479 = expr_get_child(stmt, DEREF(_t4478));
            (void)_t4479;
            Str *fname = expr_get_str_val(_t4479);
            (void)fname;
            U32 *_t4480 = malloc(sizeof(U32));
            *_t4480 = 1;
            (void)_t4480;
            Expr *_t4481 = expr_get_child(stmt, DEREF(_t4480));
            (void)_t4481;
            Str *arg = expr_get_str_val(_t4481);
            (void)arg;
            Str *_t4482 = Str_lit("link", 4ULL);
            (void)_t4482;
            Bool _t4483; { Bool *_hp = (Bool *)Str_eq(fname, _t4482); _t4483 = *_hp; free(_hp); }
            (void)_t4483;
            Str_delete(_t4482, &(Bool){1});
            if (_t4483) {
                Str *_t4470 = Str_lit(" -l", 3ULL);
                (void)_t4470;
                Str *_t4471 = Str_concat(link_flags, _t4470);
                (void)_t4471;
                Str_delete(_t4470, &(Bool){1});
                link_flags = Str_concat(_t4471, arg);
                Str_delete(_t4471, &(Bool){1});
            } else {
                Str *_t4476 = Str_lit("link_c", 6ULL);
                (void)_t4476;
                Bool _t4477; { Bool *_hp = (Bool *)Str_eq(fname, _t4476); _t4477 = *_hp; free(_hp); }
                (void)_t4477;
                Str_delete(_t4476, &(Bool){1});
                if (_t4477) {
                    U64 _t4473; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4473 = *_hp; free(_hp); }
                    (void)_t4473;
                    U64 _t4474 = 0;
                    (void)_t4474;
                    Bool _t4475; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4473}, &(U64){_t4474}); _t4475 = *_hp; free(_hp); }
                    (void)_t4475;
                    ;
                    ;
                    if (_t4475) {
                        Str *_t4472 = Str_lit(" ", 1ULL);
                        (void)_t4472;
                        link_c_paths = Str_concat(link_c_paths, _t4472);
                        Str_delete(_t4472, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4478, &(Bool){1});
            U32_delete(_t4480, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4501 = 1;
        (void)_t4501;
        U32 _t4502 = U32_add(DEREF(i), _t4501);
        (void)_t4502;
        ;
        *i = _t4502;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4781 = init_declarations(ast, scope);
    (void)_t4781;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4782 = 0;
    (void)_t4782;
    Bool _t4783; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4782}); _t4783 = *_hp; free(_hp); }
    (void)_t4783;
    ;
    if (_t4783) {
        Str *_t4503 = Str_lit("Str", 3ULL);
        (void)_t4503;
        U64 _t4504; { U64 *_hp = (U64 *)Str_size(); _t4504 = *_hp; free(_hp); }
        (void)_t4504;
        U64 _t4505 = 1;
        (void)_t4505;
        Array *_va86 = Array_new(_t4503, &(U64){_t4504}, &(U64){_t4505});
        (void)_va86;
        Str_delete(_t4503, &(Bool){1});
        ;
        ;
        Str *_t4506 = I32_to_str(&(I32){type_errors});
        (void)_t4506;
        Str *_t4507 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4507;
        U64 _t4508 = 0;
        (void)_t4508;
        Str *_t4509 = Str_concat(_t4506, _t4507);
        (void)_t4509;
        Str_delete(_t4506, &(Bool){1});
        Str_delete(_t4507, &(Bool){1});
        Array_set(_va86, &(U64){_t4508}, _t4509);
        ;
        Str *_t4510 = Str_lit("src/til.til:420:15", 18ULL);
        (void)_t4510;
        panic(_t4510, _va86);
        Str_delete(_t4510, &(Bool){1});
    }
    ;
    ;
    Str *_t4784 = Str_lit("test", 4ULL);
    (void)_t4784;
    Str *_t4785 = Str_lit("test", 4ULL);
    (void)_t4785;
    Bool _t4786; { Bool *_hp = (Bool *)Str_eq(command, _t4784); _t4786 = *_hp; free(_hp); }
    (void)_t4786;
    Str_delete(_t4784, &(Bool){1});
    Bool _t4787; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4785); _t4787 = *_hp; free(_hp); }
    (void)_t4787;
    Str_delete(_t4785, &(Bool){1});
    Str *_t4788 = Str_lit("pure", 4ULL);
    (void)_t4788;
    Bool _t4789 = Bool_or(_t4786, _t4787);
    (void)_t4789;
    ;
    ;
    Bool _t4790; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4788); _t4790 = *_hp; free(_hp); }
    (void)_t4790;
    Str_delete(_t4788, &(Bool){1});
    Str *_t4791 = Str_lit("pura", 4ULL);
    (void)_t4791;
    Bool _t4792 = Bool_or(_t4789, _t4790);
    (void)_t4792;
    ;
    ;
    Bool _t4793; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4791); _t4793 = *_hp; free(_hp); }
    (void)_t4793;
    Str_delete(_t4791, &(Bool){1});
    Bool run_tests = Bool_or(_t4792, _t4793);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4794 = Str_lit("translate", 9ULL);
    (void)_t4794;
    Str *_t4795 = Str_lit("build", 5ULL);
    (void)_t4795;
    Bool _t4796; { Bool *_hp = (Bool *)Str_eq(command, _t4794); _t4796 = *_hp; free(_hp); }
    (void)_t4796;
    Str_delete(_t4794, &(Bool){1});
    Bool _t4797; { Bool *_hp = (Bool *)Str_eq(command, _t4795); _t4797 = *_hp; free(_hp); }
    (void)_t4797;
    Str_delete(_t4795, &(Bool){1});
    Bool _t4798; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4798 = *_hp; free(_hp); }
    (void)_t4798;
    Bool _t4799 = Bool_or(_t4796, _t4797);
    (void)_t4799;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4798, _t4799);
    (void)is_lib_target;
    ;
    ;
    U64 _t4800; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4800 = *_hp; free(_hp); }
    (void)_t4800;
    U64 _t4801 = 0;
    (void)_t4801;
    Bool _t4802 = Bool_not(is_lib_target);
    (void)_t4802;
    ;
    Bool _t4803 = U64_eq(_t4800, _t4801);
    (void)_t4803;
    ;
    ;
    Bool _t4804 = Bool_and(_t4802, _t4803);
    (void)_t4804;
    ;
    ;
    if (_t4804) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4805; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4805 = *_hp; free(_hp); }
    (void)_t4805;
    U64 _t4806 = 0;
    (void)_t4806;
    Bool _t4807; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4805}, &(U64){_t4806}); _t4807 = *_hp; free(_hp); }
    (void)_t4807;
    ;
    ;
    if (_t4807) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4808 = Str_lit("Str", 3ULL);
    (void)_t4808;
    U64 _t4809; { U64 *_hp = (U64 *)Str_size(); _t4809 = *_hp; free(_hp); }
    (void)_t4809;
    Vec *user_argv = Vec_new(_t4808, &(U64){_t4809});
    (void)user_argv;
    Str_delete(_t4808, &(Bool){1});
    ;
    U64 _t4810 = 1;
    (void)_t4810;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4810);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4527; { U64 *_hp = (U64 *)Array_len(args); _t4527 = *_hp; free(_hp); }
        (void)_t4527;
        Bool _wcond4511; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4527}); _wcond4511 = *_hp; free(_hp); }
        (void)_wcond4511;
        ;
        if (_wcond4511) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4528 = Str_lit("-l", 2ULL);
        (void)_t4528;
        Bool _t4529; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4528); _t4529 = *_hp; free(_hp); }
        (void)_t4529;
        Str_delete(_t4528, &(Bool){1});
        if (_t4529) {
            U64 _t4514 = 2;
            (void)_t4514;
            U64 _t4515; { U64 *_hp = (U64 *)Str_len(arg); _t4515 = *_hp; free(_hp); }
            (void)_t4515;
            Str *lib = Str_substr(arg, &(U64){_t4514}, &(U64){_t4515});
            (void)lib;
            ;
            ;
            U64 _t4516; { U64 *_hp = (U64 *)Str_len(lib); _t4516 = *_hp; free(_hp); }
            (void)_t4516;
            U64 _t4517 = 0;
            (void)_t4517;
            U64 _t4518 = 1;
            (void)_t4518;
            U64 _t4519 = U64_add(DEREF(ai), _t4518);
            (void)_t4519;
            ;
            U64 _t4520; { U64 *_hp = (U64 *)Array_len(args); _t4520 = *_hp; free(_hp); }
            (void)_t4520;
            Bool _t4521 = U64_eq(_t4516, _t4517);
            (void)_t4521;
            ;
            ;
            Bool _t4522; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4519}, &(U64){_t4520}); _t4522 = *_hp; free(_hp); }
            (void)_t4522;
            ;
            ;
            Bool _t4523 = Bool_and(_t4521, _t4522);
            (void)_t4523;
            ;
            ;
            if (_t4523) {
                U64 _t4512 = 1;
                (void)_t4512;
                U64 _t4513 = U64_add(DEREF(ai), _t4512);
                (void)_t4513;
                ;
                *ai = _t4513;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4524 = Str_lit(" -l", 3ULL);
            (void)_t4524;
            Str *_t4525 = Str_concat(link_flags, _t4524);
            (void)_t4525;
            Str_delete(_t4524, &(Bool){1});
            link_flags = Str_concat(_t4525, lib);
            Str_delete(_t4525, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4526 = Str_clone(arg);
            (void)_t4526;
            Vec_push(user_argv, _t4526);
        }
        ;
        U64 _t4530 = 1;
        (void)_t4530;
        U64 _t4531 = U64_add(DEREF(ai), _t4530);
        (void)_t4531;
        ;
        *ai = _t4531;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4811; { U64 *_hp = (U64 *)Str_len(link_flags); _t4811 = *_hp; free(_hp); }
    (void)_t4811;
    U64 _t4812 = 0;
    (void)_t4812;
    Bool _t4813; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4811}, &(U64){_t4812}); _t4813 = *_hp; free(_hp); }
    (void)_t4813;
    ;
    ;
    if (_t4813) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4814 = Str_lit("interpret", 9ULL);
    (void)_t4814;
    Str *_t4815 = Str_lit("test", 4ULL);
    (void)_t4815;
    Bool _t4816; { Bool *_hp = (Bool *)Str_eq(command, _t4814); _t4816 = *_hp; free(_hp); }
    (void)_t4816;
    Str_delete(_t4814, &(Bool){1});
    Bool _t4817; { Bool *_hp = (Bool *)Str_eq(command, _t4815); _t4817 = *_hp; free(_hp); }
    (void)_t4817;
    Str_delete(_t4815, &(Bool){1});
    Bool _t4818 = Bool_or(_t4816, _t4817);
    (void)_t4818;
    ;
    ;
    if (_t4818) {
        Str *_t4538 = Str_lit("interpret", 9ULL);
        (void)_t4538;
        Bool _t4539; { Bool *_hp = (Bool *)Str_eq(command, _t4538); _t4539 = *_hp; free(_hp); }
        (void)_t4539;
        Str_delete(_t4538, &(Bool){1});
        Bool _t4540 = Bool_and(is_lib_mode, _t4539);
        (void)_t4540;
        ;
        if (_t4540) {
            Str *_t4532 = Str_lit("Str", 3ULL);
            (void)_t4532;
            U64 _t4533; { U64 *_hp = (U64 *)Str_size(); _t4533 = *_hp; free(_hp); }
            (void)_t4533;
            U64 _t4534 = 1;
            (void)_t4534;
            Array *_va87 = Array_new(_t4532, &(U64){_t4533}, &(U64){_t4534});
            (void)_va87;
            Str_delete(_t4532, &(Bool){1});
            ;
            ;
            U64 _t4535 = 0;
            (void)_t4535;
            Str *_t4536 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4536;
            Array_set(_va87, &(U64){_t4535}, _t4536);
            ;
            Str *_t4537 = Str_lit("src/til.til:474:19", 18ULL);
            (void)_t4537;
            panic(_t4537, _va87);
            Str_delete(_t4537, &(Bool){1});
        }
        ;
        I32 _t4541 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4541;
        result = _t4541;
        ;
    } else {
        Str *_t4734 = Str_lit("translate", 9ULL);
        (void)_t4734;
        Str *_t4735 = Str_lit("build", 5ULL);
        (void)_t4735;
        Bool _t4736; { Bool *_hp = (Bool *)Str_eq(command, _t4734); _t4736 = *_hp; free(_hp); }
        (void)_t4736;
        Str_delete(_t4734, &(Bool){1});
        Bool _t4737; { Bool *_hp = (Bool *)Str_eq(command, _t4735); _t4737 = *_hp; free(_hp); }
        (void)_t4737;
        Str_delete(_t4735, &(Bool){1});
        Str *_t4738 = Str_lit("run", 3ULL);
        (void)_t4738;
        Bool _t4739 = Bool_or(_t4736, _t4737);
        (void)_t4739;
        ;
        ;
        Bool _t4740; { Bool *_hp = (Bool *)Str_eq(command, _t4738); _t4740 = *_hp; free(_hp); }
        (void)_t4740;
        Str_delete(_t4738, &(Bool){1});
        Bool _t4741 = Bool_or(_t4739, _t4740);
        (void)_t4741;
        ;
        ;
        if (_t4741) {
            Str *_t4667 = Str_lit("run", 3ULL);
            (void)_t4667;
            Bool _t4668; { Bool *_hp = (Bool *)Str_eq(command, _t4667); _t4668 = *_hp; free(_hp); }
            (void)_t4668;
            Str_delete(_t4667, &(Bool){1});
            Bool _t4669 = Bool_and(is_lib_mode, _t4668);
            (void)_t4669;
            ;
            if (_t4669) {
                Str *_t4542 = Str_lit("Str", 3ULL);
                (void)_t4542;
                U64 _t4543; { U64 *_hp = (U64 *)Str_size(); _t4543 = *_hp; free(_hp); }
                (void)_t4543;
                U64 _t4544 = 1;
                (void)_t4544;
                Array *_va88 = Array_new(_t4542, &(U64){_t4543}, &(U64){_t4544});
                (void)_va88;
                Str_delete(_t4542, &(Bool){1});
                ;
                ;
                U64 _t4545 = 0;
                (void)_t4545;
                Str *_t4546 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4546;
                Array_set(_va88, &(U64){_t4545}, _t4546);
                ;
                Str *_t4547 = Str_lit("src/til.til:480:19", 18ULL);
                (void)_t4547;
                panic(_t4547, _va88);
                Str_delete(_t4547, &(Bool){1});
            }
            ;
            Str *_t4670 = Str_lit("/", 1ULL);
            (void)_t4670;
            I64 *last_slash = Str_rfind(path, _t4670);
            (void)last_slash;
            Str_delete(_t4670, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4671 = 0;
            (void)_t4671;
            Bool _t4672; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4671}); _t4672 = *_hp; free(_hp); }
            (void)_t4672;
            ;
            if (_t4672) {
                I64 _t4548 = 1;
                (void)_t4548;
                I64 _t4549 = I64_add(DEREF(last_slash), _t4548);
                (void)_t4549;
                ;
                U64 _t4550; { U64 *_hp = (U64 *)Str_len(path); _t4550 = *_hp; free(_hp); }
                (void)_t4550;
                U64 _t4551 = I64_to_u64(DEREF(last_slash));
                (void)_t4551;
                U64 _t4552 = U64_sub(_t4550, _t4551);
                (void)_t4552;
                ;
                ;
                U64 _t4553 = 1;
                (void)_t4553;
                U64 _t4554 = I64_to_u64(_t4549);
                (void)_t4554;
                ;
                U64 _t4555 = U64_sub(_t4552, _t4553);
                (void)_t4555;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4554}, &(U64){_t4555});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4673 = Str_lit(".til", 4ULL);
            (void)_t4673;
            Bool _t4674; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4673); _t4674 = *_hp; free(_hp); }
            (void)_t4674;
            Str_delete(_t4673, &(Bool){1});
            if (_t4674) {
                U64 _t4556 = 4;
                (void)_t4556;
                U64 _t4557 = U64_sub(name_len, _t4556);
                (void)_t4557;
                ;
                name_len = _t4557;
                ;
            }
            ;
            U64 _t4675 = 0;
            (void)_t4675;
            Str *name = Str_substr(basename, &(U64){_t4675}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4676 = Str_lit("gen/til/", 8ULL);
            (void)_t4676;
            Str *_t4677 = Str_concat(_t4676, name);
            (void)_t4677;
            Str_delete(_t4676, &(Bool){1});
            Str *_t4678 = Str_lit(".c", 2ULL);
            (void)_t4678;
            Str *c_path = Str_concat(_t4677, _t4678);
            (void)c_path;
            Str_delete(_t4677, &(Bool){1});
            Str_delete(_t4678, &(Bool){1});
            U64 _t4679; { U64 *_hp = (U64 *)Str_len(custom_c); _t4679 = *_hp; free(_hp); }
            (void)_t4679;
            U64 _t4680 = 0;
            (void)_t4680;
            Bool _t4681; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4679}, &(U64){_t4680}); _t4681 = *_hp; free(_hp); }
            (void)_t4681;
            ;
            ;
            if (_t4681) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4682 = Str_lit("bin/til/", 8ULL);
            (void)_t4682;
            Str *bin_path = Str_concat(_t4682, name);
            (void)bin_path;
            Str_delete(_t4682, &(Bool){1});
            U64 _t4683; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4683 = *_hp; free(_hp); }
            (void)_t4683;
            U64 _t4684 = 0;
            (void)_t4684;
            Bool _t4685; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4683}, &(U64){_t4684}); _t4685 = *_hp; free(_hp); }
            (void)_t4685;
            ;
            ;
            if (_t4685) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4686 = Str_lit("run", 3ULL);
            (void)_t4686;
            Bool _t4687; { Bool *_hp = (Bool *)Str_eq(command, _t4686); _t4687 = *_hp; free(_hp); }
            (void)_t4687;
            Str_delete(_t4686, &(Bool){1});
            Bool _t4688; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4688 = *_hp; free(_hp); }
            (void)_t4688;
            Bool _t4689 = Bool_not(_t4687);
            (void)_t4689;
            ;
            Bool do_lib = Bool_and(_t4688, _t4689);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4558 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4558;
                I32 _t4559 = til_system(_t4558);
                (void)_t4559;
                Str_delete(_t4558, &(Bool){1});
                ;
            } else {
                Str *_t4564 = Str_lit("/", 1ULL);
                (void)_t4564;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4564); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4564, &(Bool){1});
                Str *_t4565 = Str_lit("/", 1ULL);
                (void)_t4565;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4565); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4565, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4566 = 0;
                (void)_t4566;
                Bool _t4567; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4566}); _t4567 = *_hp; free(_hp); }
                (void)_t4567;
                ;
                if (_t4567) {
                    U64 _t4560 = 0;
                    (void)_t4560;
                    U64 _t4561 = I64_to_u64(cp_slash);
                    (void)_t4561;
                    cp_dir = Str_substr(c_path, &(U64){_t4560}, &(U64){_t4561});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4568 = 0;
                (void)_t4568;
                Bool _t4569; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4568}); _t4569 = *_hp; free(_hp); }
                (void)_t4569;
                ;
                if (_t4569) {
                    U64 _t4562 = 0;
                    (void)_t4562;
                    U64 _t4563 = I64_to_u64(bp_slash);
                    (void)_t4563;
                    bp_dir = Str_substr(bin_path, &(U64){_t4562}, &(U64){_t4563});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4570 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4570;
                Str *_t4571 = Str_concat(_t4570, cp_dir);
                (void)_t4571;
                Str_delete(_t4570, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4572 = Str_lit(" ", 1ULL);
                (void)_t4572;
                Str *_t4573 = Str_concat(_t4571, _t4572);
                (void)_t4573;
                Str_delete(_t4571, &(Bool){1});
                Str_delete(_t4572, &(Bool){1});
                Str *_t4574 = Str_concat(_t4573, bp_dir);
                (void)_t4574;
                Str_delete(_t4573, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4575 = til_system(_t4574);
                (void)_t4575;
                Str_delete(_t4574, &(Bool){1});
                ;
            }
            I32 _t4690 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4690;
            result = _t4690;
            ;
            I32 _t4691 = 0;
            (void)_t4691;
            Bool _t4692 = I32_eq(result, _t4691);
            (void)_t4692;
            ;
            Bool _t4693 = Bool_and(_t4692, do_lib);
            (void)_t4693;
            ;
            if (_t4693) {
                Str *_t4632 = Str_lit("gen/til/", 8ULL);
                (void)_t4632;
                Str *_t4633 = Str_concat(_t4632, name);
                (void)_t4633;
                Str_delete(_t4632, &(Bool){1});
                Str *_t4634 = Str_lit(".h", 2ULL);
                (void)_t4634;
                Str *h_path = Str_concat(_t4633, _t4634);
                (void)h_path;
                Str_delete(_t4633, &(Bool){1});
                Str_delete(_t4634, &(Bool){1});
                Str *_t4635 = Str_lit("gen/til/", 8ULL);
                (void)_t4635;
                Str *_t4636 = Str_concat(_t4635, name);
                (void)_t4636;
                Str_delete(_t4635, &(Bool){1});
                Str *_t4637 = Str_lit(".til", 4ULL);
                (void)_t4637;
                Str *til_path = Str_concat(_t4636, _t4637);
                (void)til_path;
                Str_delete(_t4636, &(Bool){1});
                Str_delete(_t4637, &(Bool){1});
                I32 _t4638 = build_header(ast, h_path);
                (void)_t4638;
                result = _t4638;
                ;
                I32 _t4639 = 0;
                (void)_t4639;
                Bool _t4640 = I32_eq(result, _t4639);
                (void)_t4640;
                ;
                if (_t4640) {
                    I32 _t4576 = build_til_binding(ast, til_path, name);
                    (void)_t4576;
                    result = _t4576;
                    ;
                }
                ;
                I32 _t4641 = 0;
                (void)_t4641;
                Str *_t4642 = Str_lit("translate", 9ULL);
                (void)_t4642;
                Bool _t4643 = I32_eq(result, _t4641);
                (void)_t4643;
                ;
                Bool _t4644; { Bool *_hp = (Bool *)Str_eq(command, _t4642); _t4644 = *_hp; free(_hp); }
                (void)_t4644;
                Str_delete(_t4642, &(Bool){1});
                Bool _t4645 = Bool_and(_t4643, _t4644);
                (void)_t4645;
                ;
                ;
                if (_t4645) {
                    Str *_t4577 = Str_lit("Str", 3ULL);
                    (void)_t4577;
                    U64 _t4578; { U64 *_hp = (U64 *)Str_size(); _t4578 = *_hp; free(_hp); }
                    (void)_t4578;
                    U64 _t4579 = 1;
                    (void)_t4579;
                    Array *_va89 = Array_new(_t4577, &(U64){_t4578}, &(U64){_t4579});
                    (void)_va89;
                    Str_delete(_t4577, &(Bool){1});
                    ;
                    ;
                    Str *_t4580 = Str_lit("Generated: ", 11ULL);
                    (void)_t4580;
                    U64 _t4581 = 0;
                    (void)_t4581;
                    Str *_t4582 = Str_concat(_t4580, c_path);
                    (void)_t4582;
                    Str_delete(_t4580, &(Bool){1});
                    Array_set(_va89, &(U64){_t4581}, _t4582);
                    ;
                    println(_va89);
                    Str *_t4583 = Str_lit("Str", 3ULL);
                    (void)_t4583;
                    U64 _t4584; { U64 *_hp = (U64 *)Str_size(); _t4584 = *_hp; free(_hp); }
                    (void)_t4584;
                    U64 _t4585 = 1;
                    (void)_t4585;
                    Array *_va90 = Array_new(_t4583, &(U64){_t4584}, &(U64){_t4585});
                    (void)_va90;
                    Str_delete(_t4583, &(Bool){1});
                    ;
                    ;
                    Str *_t4586 = Str_lit("Generated: ", 11ULL);
                    (void)_t4586;
                    U64 _t4587 = 0;
                    (void)_t4587;
                    Str *_t4588 = Str_concat(_t4586, h_path);
                    (void)_t4588;
                    Str_delete(_t4586, &(Bool){1});
                    Array_set(_va90, &(U64){_t4587}, _t4588);
                    ;
                    println(_va90);
                    Str *_t4589 = Str_lit("Str", 3ULL);
                    (void)_t4589;
                    U64 _t4590; { U64 *_hp = (U64 *)Str_size(); _t4590 = *_hp; free(_hp); }
                    (void)_t4590;
                    U64 _t4591 = 1;
                    (void)_t4591;
                    Array *_va91 = Array_new(_t4589, &(U64){_t4590}, &(U64){_t4591});
                    (void)_va91;
                    Str_delete(_t4589, &(Bool){1});
                    ;
                    ;
                    Str *_t4592 = Str_lit("Generated: ", 11ULL);
                    (void)_t4592;
                    U64 _t4593 = 0;
                    (void)_t4593;
                    Str *_t4594 = Str_concat(_t4592, til_path);
                    (void)_t4594;
                    Str_delete(_t4592, &(Bool){1});
                    Array_set(_va91, &(U64){_t4593}, _t4594);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4646 = 0;
                (void)_t4646;
                Str *_t4647 = Str_lit("build", 5ULL);
                (void)_t4647;
                Bool _t4648 = I32_eq(result, _t4646);
                (void)_t4648;
                ;
                Bool _t4649; { Bool *_hp = (Bool *)Str_eq(command, _t4647); _t4649 = *_hp; free(_hp); }
                (void)_t4649;
                Str_delete(_t4647, &(Bool){1});
                Bool _t4650 = Bool_and(_t4648, _t4649);
                (void)_t4650;
                ;
                ;
                if (_t4650) {
                    I32 _t4629 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4629;
                    result = _t4629;
                    ;
                    I32 _t4630 = 0;
                    (void)_t4630;
                    Bool _t4631 = I32_eq(result, _t4630);
                    (void)_t4631;
                    ;
                    if (_t4631) {
                        Str *_t4595 = Str_lit("Str", 3ULL);
                        (void)_t4595;
                        U64 _t4596; { U64 *_hp = (U64 *)Str_size(); _t4596 = *_hp; free(_hp); }
                        (void)_t4596;
                        U64 _t4597 = 1;
                        (void)_t4597;
                        Array *_va92 = Array_new(_t4595, &(U64){_t4596}, &(U64){_t4597});
                        (void)_va92;
                        Str_delete(_t4595, &(Bool){1});
                        ;
                        ;
                        Str *_t4598 = Str_lit("Generated: ", 11ULL);
                        (void)_t4598;
                        U64 _t4599 = 0;
                        (void)_t4599;
                        Str *_t4600 = Str_concat(_t4598, c_path);
                        (void)_t4600;
                        Str_delete(_t4598, &(Bool){1});
                        Array_set(_va92, &(U64){_t4599}, _t4600);
                        ;
                        println(_va92);
                        Str *_t4601 = Str_lit("Str", 3ULL);
                        (void)_t4601;
                        U64 _t4602; { U64 *_hp = (U64 *)Str_size(); _t4602 = *_hp; free(_hp); }
                        (void)_t4602;
                        U64 _t4603 = 1;
                        (void)_t4603;
                        Array *_va93 = Array_new(_t4601, &(U64){_t4602}, &(U64){_t4603});
                        (void)_va93;
                        Str_delete(_t4601, &(Bool){1});
                        ;
                        ;
                        Str *_t4604 = Str_lit("Generated: ", 11ULL);
                        (void)_t4604;
                        U64 _t4605 = 0;
                        (void)_t4605;
                        Str *_t4606 = Str_concat(_t4604, h_path);
                        (void)_t4606;
                        Str_delete(_t4604, &(Bool){1});
                        Array_set(_va93, &(U64){_t4605}, _t4606);
                        ;
                        println(_va93);
                        Str *_t4607 = Str_lit("Str", 3ULL);
                        (void)_t4607;
                        U64 _t4608; { U64 *_hp = (U64 *)Str_size(); _t4608 = *_hp; free(_hp); }
                        (void)_t4608;
                        U64 _t4609 = 1;
                        (void)_t4609;
                        Array *_va94 = Array_new(_t4607, &(U64){_t4608}, &(U64){_t4609});
                        (void)_va94;
                        Str_delete(_t4607, &(Bool){1});
                        ;
                        ;
                        Str *_t4610 = Str_lit("Generated: ", 11ULL);
                        (void)_t4610;
                        U64 _t4611 = 0;
                        (void)_t4611;
                        Str *_t4612 = Str_concat(_t4610, til_path);
                        (void)_t4612;
                        Str_delete(_t4610, &(Bool){1});
                        Array_set(_va94, &(U64){_t4611}, _t4612);
                        ;
                        println(_va94);
                        Str *_t4613 = Str_lit("Str", 3ULL);
                        (void)_t4613;
                        U64 _t4614; { U64 *_hp = (U64 *)Str_size(); _t4614 = *_hp; free(_hp); }
                        (void)_t4614;
                        U64 _t4615 = 1;
                        (void)_t4615;
                        Array *_va95 = Array_new(_t4613, &(U64){_t4614}, &(U64){_t4615});
                        (void)_va95;
                        Str_delete(_t4613, &(Bool){1});
                        ;
                        ;
                        Str *_t4616 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4616;
                        Str *_t4617 = Str_concat(_t4616, name);
                        (void)_t4617;
                        Str_delete(_t4616, &(Bool){1});
                        Str *_t4618 = Str_lit(".so", 3ULL);
                        (void)_t4618;
                        U64 _t4619 = 0;
                        (void)_t4619;
                        Str *_t4620 = Str_concat(_t4617, _t4618);
                        (void)_t4620;
                        Str_delete(_t4617, &(Bool){1});
                        Str_delete(_t4618, &(Bool){1});
                        Array_set(_va95, &(U64){_t4619}, _t4620);
                        ;
                        println(_va95);
                        Str *_t4621 = Str_lit("Str", 3ULL);
                        (void)_t4621;
                        U64 _t4622; { U64 *_hp = (U64 *)Str_size(); _t4622 = *_hp; free(_hp); }
                        (void)_t4622;
                        U64 _t4623 = 1;
                        (void)_t4623;
                        Array *_va96 = Array_new(_t4621, &(U64){_t4622}, &(U64){_t4623});
                        (void)_va96;
                        Str_delete(_t4621, &(Bool){1});
                        ;
                        ;
                        Str *_t4624 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4624;
                        Str *_t4625 = Str_concat(_t4624, name);
                        (void)_t4625;
                        Str_delete(_t4624, &(Bool){1});
                        Str *_t4626 = Str_lit(".a", 2ULL);
                        (void)_t4626;
                        U64 _t4627 = 0;
                        (void)_t4627;
                        Str *_t4628 = Str_concat(_t4625, _t4626);
                        (void)_t4628;
                        Str_delete(_t4625, &(Bool){1});
                        Str_delete(_t4626, &(Bool){1});
                        Array_set(_va96, &(U64){_t4627}, _t4628);
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
            I32 _t4694 = 0;
            (void)_t4694;
            Bool _t4695 = I32_eq(result, _t4694);
            (void)_t4695;
            ;
            Bool _t4696 = Bool_not(do_lib);
            (void)_t4696;
            Str *_t4697 = Str_lit("translate", 9ULL);
            (void)_t4697;
            Bool _t4698 = Bool_and(_t4695, _t4696);
            (void)_t4698;
            ;
            ;
            Bool _t4699; { Bool *_hp = (Bool *)Str_eq(command, _t4697); _t4699 = *_hp; free(_hp); }
            (void)_t4699;
            Str_delete(_t4697, &(Bool){1});
            Bool _t4700 = Bool_and(_t4698, _t4699);
            (void)_t4700;
            ;
            ;
            if (_t4700) {
                Str *_t4651 = Str_lit("Str", 3ULL);
                (void)_t4651;
                U64 _t4652; { U64 *_hp = (U64 *)Str_size(); _t4652 = *_hp; free(_hp); }
                (void)_t4652;
                U64 _t4653 = 1;
                (void)_t4653;
                Array *_va97 = Array_new(_t4651, &(U64){_t4652}, &(U64){_t4653});
                (void)_va97;
                Str_delete(_t4651, &(Bool){1});
                ;
                ;
                Str *_t4654 = Str_lit("Generated: ", 11ULL);
                (void)_t4654;
                U64 _t4655 = 0;
                (void)_t4655;
                Str *_t4656 = Str_concat(_t4654, c_path);
                (void)_t4656;
                Str_delete(_t4654, &(Bool){1});
                Array_set(_va97, &(U64){_t4655}, _t4656);
                ;
                println(_va97);
            }
            ;
            I32 _t4701 = 0;
            (void)_t4701;
            Bool _t4702 = I32_eq(result, _t4701);
            (void)_t4702;
            ;
            Bool _t4703 = Bool_not(do_lib);
            (void)_t4703;
            Str *_t4704 = Str_lit("translate", 9ULL);
            (void)_t4704;
            Bool _t4705; { Bool *_hp = (Bool *)Str_eq(command, _t4704); _t4705 = *_hp; free(_hp); }
            (void)_t4705;
            Str_delete(_t4704, &(Bool){1});
            Bool _t4706 = Bool_and(_t4702, _t4703);
            (void)_t4706;
            ;
            ;
            Bool _t4707 = Bool_not(_t4705);
            (void)_t4707;
            ;
            Bool _t4708 = Bool_and(_t4706, _t4707);
            (void)_t4708;
            ;
            ;
            if (_t4708) {
                I32 _t4657 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4657;
                result = _t4657;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4709 = 0;
            (void)_t4709;
            Bool _t4710 = I32_eq(result, _t4709);
            (void)_t4710;
            ;
            Bool _t4711 = Bool_not(do_lib);
            (void)_t4711;
            ;
            Str *_t4712 = Str_lit("run", 3ULL);
            (void)_t4712;
            Bool _t4713 = Bool_and(_t4710, _t4711);
            (void)_t4713;
            ;
            ;
            Bool _t4714; { Bool *_hp = (Bool *)Str_eq(command, _t4712); _t4714 = *_hp; free(_hp); }
            (void)_t4714;
            Str_delete(_t4712, &(Bool){1});
            Bool _t4715 = Bool_and(_t4713, _t4714);
            (void)_t4715;
            ;
            ;
            if (_t4715) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4659; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4659 = *_hp; free(_hp); }
                    (void)_t4659;
                    Bool _wcond4658; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4659}); _wcond4658 = *_hp; free(_hp); }
                    (void)_wcond4658;
                    ;
                    if (_wcond4658) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4660 = Str_lit(" '", 2ULL);
                    (void)_t4660;
                    Str *_t4661 = Str_concat(cmd, _t4660);
                    (void)_t4661;
                    Str_delete(_t4660, &(Bool){1});
                    Str *_t4662 = Str_concat(_t4661, uarg);
                    (void)_t4662;
                    Str_delete(_t4661, &(Bool){1});
                    Str *_t4663 = Str_lit("'", 1ULL);
                    (void)_t4663;
                    cmd = Str_concat(_t4662, _t4663);
                    Str_delete(_t4662, &(Bool){1});
                    Str_delete(_t4663, &(Bool){1});
                    U64 _t4664 = 1;
                    (void)_t4664;
                    U64 _t4665 = U64_add(DEREF(ui), _t4664);
                    (void)_t4665;
                    ;
                    *ui = _t4665;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4666 = til_system(cmd);
                (void)_t4666;
                Str_delete(cmd, &(Bool){1});
                result = _t4666;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4732 = Str_lit("ast", 3ULL);
            (void)_t4732;
            Bool _t4733; { Bool *_hp = (Bool *)Str_eq(command, _t4732); _t4733 = *_hp; free(_hp); }
            (void)_t4733;
            Str_delete(_t4732, &(Bool){1});
            if (_t4733) {
                Str *_t4716 = Str_lit("Str", 3ULL);
                (void)_t4716;
                U64 _t4717; { U64 *_hp = (U64 *)Str_size(); _t4717 = *_hp; free(_hp); }
                (void)_t4717;
                U64 _t4718 = 1;
                (void)_t4718;
                Array *_va98 = Array_new(_t4716, &(U64){_t4717}, &(U64){_t4718});
                (void)_va98;
                Str_delete(_t4716, &(Bool){1});
                ;
                ;
                Str *_t4719 = Str_lit("mode: ", 6ULL);
                (void)_t4719;
                U64 _t4720 = 0;
                (void)_t4720;
                Str *_t4721 = Str_concat(_t4719, &cur_mode->name);
                (void)_t4721;
                Str_delete(_t4719, &(Bool){1});
                Array_set(_va98, &(U64){_t4720}, _t4721);
                ;
                println(_va98);
                U32 _t4722 = 0;
                (void)_t4722;
                ast_print(ast, _t4722);
                ;
            } else {
                Str *_t4723 = Str_lit("Str", 3ULL);
                (void)_t4723;
                U64 _t4724; { U64 *_hp = (U64 *)Str_size(); _t4724 = *_hp; free(_hp); }
                (void)_t4724;
                U64 _t4725 = 1;
                (void)_t4725;
                Array *_va99 = Array_new(_t4723, &(U64){_t4724}, &(U64){_t4725});
                (void)_va99;
                Str_delete(_t4723, &(Bool){1});
                ;
                ;
                Str *_t4726 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4726;
                Str *_t4727 = Str_concat(_t4726, command);
                (void)_t4727;
                Str_delete(_t4726, &(Bool){1});
                Str *_t4728 = Str_lit("'", 1ULL);
                (void)_t4728;
                U64 _t4729 = 0;
                (void)_t4729;
                Str *_t4730 = Str_concat(_t4727, _t4728);
                (void)_t4730;
                Str_delete(_t4727, &(Bool){1});
                Str_delete(_t4728, &(Bool){1});
                Array_set(_va99, &(U64){_t4729}, _t4730);
                ;
                println(_va99);
                usage();
                I32 _t4731 = 1;
                (void)_t4731;
                result = _t4731;
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
    I64 _t4819 = I32_to_i64(result);
    (void)_t4819;
    ;
    exit(_t4819);
    ;
    return 0;
}

