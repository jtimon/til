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
            Bool _t4307; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4307 = *_hp; free(_hp); }
            (void)_t4307;
            if (_t4307) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4308 = Str_clone(abs);
            (void)_t4308;
            Set_add(resolved_set, _t4308);
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
            U64 _t4309; { U64 *_hp = (U64 *)Str_len(abs); _t4309 = *_hp; free(_hp); }
            (void)_t4309;
            U64 _t4310 = 1;
            (void)_t4310;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4309, _t4310);
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
            U64 _t4311; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4311 = *_hp; free(_hp); }
            (void)_t4311;
            U64 _t4312 = 0;
            (void)_t4312;
            Bool _t4313; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4311}, &(U64){_t4312}); _t4313 = *_hp; free(_hp); }
            (void)_t4313;
            ;
            ;
            if (_t4313) {
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
    I64 _t4314 = 0;
    (void)_t4314;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4314; return _r; }
}

void usage(void) {
    Str *_t4315 = Str_lit("Str", 3ULL);
    (void)_t4315;
    U64 _t4316; { U64 *_hp = (U64 *)Str_size(); _t4316 = *_hp; free(_hp); }
    (void)_t4316;
    U64 _t4317 = 1;
    (void)_t4317;
    Array *_va73 = Array_new(_t4315, &(U64){_t4316}, &(U64){_t4317});
    (void)_va73;
    Str_delete(_t4315, &(Bool){1});
    ;
    ;
    U64 _t4318 = 0;
    (void)_t4318;
    Str *_t4319 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4319;
    Array_set(_va73, &(U64){_t4318}, _t4319);
    ;
    println(_va73);
    Str *_t4320 = Str_lit("Str", 3ULL);
    (void)_t4320;
    U64 _t4321; { U64 *_hp = (U64 *)Str_size(); _t4321 = *_hp; free(_hp); }
    (void)_t4321;
    U64 _t4322 = 1;
    (void)_t4322;
    Array *_va74 = Array_new(_t4320, &(U64){_t4321}, &(U64){_t4322});
    (void)_va74;
    Str_delete(_t4320, &(Bool){1});
    ;
    ;
    U64 _t4323 = 0;
    (void)_t4323;
    Str *_t4324 = Str_lit("", 0ULL);
    (void)_t4324;
    Array_set(_va74, &(U64){_t4323}, _t4324);
    ;
    println(_va74);
    Str *_t4325 = Str_lit("Str", 3ULL);
    (void)_t4325;
    U64 _t4326; { U64 *_hp = (U64 *)Str_size(); _t4326 = *_hp; free(_hp); }
    (void)_t4326;
    U64 _t4327 = 1;
    (void)_t4327;
    Array *_va75 = Array_new(_t4325, &(U64){_t4326}, &(U64){_t4327});
    (void)_va75;
    Str_delete(_t4325, &(Bool){1});
    ;
    ;
    U64 _t4328 = 0;
    (void)_t4328;
    Str *_t4329 = Str_lit("Commands:", 9ULL);
    (void)_t4329;
    Array_set(_va75, &(U64){_t4328}, _t4329);
    ;
    println(_va75);
    Str *_t4330 = Str_lit("Str", 3ULL);
    (void)_t4330;
    U64 _t4331; { U64 *_hp = (U64 *)Str_size(); _t4331 = *_hp; free(_hp); }
    (void)_t4331;
    U64 _t4332 = 1;
    (void)_t4332;
    Array *_va76 = Array_new(_t4330, &(U64){_t4331}, &(U64){_t4332});
    (void)_va76;
    Str_delete(_t4330, &(Bool){1});
    ;
    ;
    U64 _t4333 = 0;
    (void)_t4333;
    Str *_t4334 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4334;
    Array_set(_va76, &(U64){_t4333}, _t4334);
    ;
    println(_va76);
    Str *_t4335 = Str_lit("Str", 3ULL);
    (void)_t4335;
    U64 _t4336; { U64 *_hp = (U64 *)Str_size(); _t4336 = *_hp; free(_hp); }
    (void)_t4336;
    U64 _t4337 = 1;
    (void)_t4337;
    Array *_va77 = Array_new(_t4335, &(U64){_t4336}, &(U64){_t4337});
    (void)_va77;
    Str_delete(_t4335, &(Bool){1});
    ;
    ;
    U64 _t4338 = 0;
    (void)_t4338;
    Str *_t4339 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4339;
    Array_set(_va77, &(U64){_t4338}, _t4339);
    ;
    println(_va77);
    Str *_t4340 = Str_lit("Str", 3ULL);
    (void)_t4340;
    U64 _t4341; { U64 *_hp = (U64 *)Str_size(); _t4341 = *_hp; free(_hp); }
    (void)_t4341;
    U64 _t4342 = 1;
    (void)_t4342;
    Array *_va78 = Array_new(_t4340, &(U64){_t4341}, &(U64){_t4342});
    (void)_va78;
    Str_delete(_t4340, &(Bool){1});
    ;
    ;
    U64 _t4343 = 0;
    (void)_t4343;
    Str *_t4344 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4344;
    Array_set(_va78, &(U64){_t4343}, _t4344);
    ;
    println(_va78);
    Str *_t4345 = Str_lit("Str", 3ULL);
    (void)_t4345;
    U64 _t4346; { U64 *_hp = (U64 *)Str_size(); _t4346 = *_hp; free(_hp); }
    (void)_t4346;
    U64 _t4347 = 1;
    (void)_t4347;
    Array *_va79 = Array_new(_t4345, &(U64){_t4346}, &(U64){_t4347});
    (void)_va79;
    Str_delete(_t4345, &(Bool){1});
    ;
    ;
    U64 _t4348 = 0;
    (void)_t4348;
    Str *_t4349 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4349;
    Array_set(_va79, &(U64){_t4348}, _t4349);
    ;
    println(_va79);
    Str *_t4350 = Str_lit("Str", 3ULL);
    (void)_t4350;
    U64 _t4351; { U64 *_hp = (U64 *)Str_size(); _t4351 = *_hp; free(_hp); }
    (void)_t4351;
    U64 _t4352 = 1;
    (void)_t4352;
    Array *_va80 = Array_new(_t4350, &(U64){_t4351}, &(U64){_t4352});
    (void)_va80;
    Str_delete(_t4350, &(Bool){1});
    ;
    ;
    U64 _t4353 = 0;
    (void)_t4353;
    Str *_t4354 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4354;
    Array_set(_va80, &(U64){_t4353}, _t4354);
    ;
    println(_va80);
    Str *_t4355 = Str_lit("Str", 3ULL);
    (void)_t4355;
    U64 _t4356; { U64 *_hp = (U64 *)Str_size(); _t4356 = *_hp; free(_hp); }
    (void)_t4356;
    U64 _t4357 = 1;
    (void)_t4357;
    Array *_va81 = Array_new(_t4355, &(U64){_t4356}, &(U64){_t4357});
    (void)_va81;
    Str_delete(_t4355, &(Bool){1});
    ;
    ;
    U64 _t4358 = 0;
    (void)_t4358;
    Str *_t4359 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4359;
    Array_set(_va81, &(U64){_t4358}, _t4359);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4365 = 1;
    (void)_t4365;
    e->is_core = _t4365;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4361 = expr_nchildren(e);
        (void)_t4361;
        Bool _wcond4360; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4361}); _wcond4360 = *_hp; free(_hp); }
        (void)_wcond4360;
        ;
        if (_wcond4360) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4362 = expr_get_child(e, DEREF(i));
        (void)_t4362;
        mark_core(_t4362);
        U32 _t4363 = 1;
        (void)_t4363;
        U32 _t4364 = U32_add(DEREF(i), _t4363);
        (void)_t4364;
        ;
        *i = _t4364;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4825 = malloc(sizeof(I64));
    *_t4825 = 0;
    (void)_t4825;
    _t4826 = malloc(sizeof(I64));
    *_t4826 = 1;
    (void)_t4826;
    _t4827 = malloc(sizeof(I64)); *_t4827 = I64_sub(DEREF(_t4825), DEREF(_t4826));
    (void)_t4827;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4827));
    (void)CAP_LIT;
    _t4828 = malloc(sizeof(I64));
    *_t4828 = 0;
    (void)_t4828;
    _t4829 = malloc(sizeof(I64));
    *_t4829 = 2;
    (void)_t4829;
    _t4830 = malloc(sizeof(I64)); *_t4830 = I64_sub(DEREF(_t4828), DEREF(_t4829));
    (void)_t4830;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4830));
    (void)CAP_VIEW;
    _t4831 = Str_lit("Str", 3ULL);
    (void)_t4831;
    _t4832 = Str_size();
    (void)_t4832;
    _t4833 = Str_lit("Mode", 4ULL);
    (void)_t4833;
    _t4834 = Mode_size();
    (void)_t4834;
    core_modes = Map_new(_t4831, _t4832, _t4833, _t4834);
    (void)core_modes;
    _t4835 = malloc(sizeof(Bool));
    *_t4835 = 0;
    (void)_t4835;
    _t4836 = malloc(sizeof(Bool));
    *_t4836 = 0;
    (void)_t4836;
    _t4837 = malloc(sizeof(Bool));
    *_t4837 = 0;
    (void)_t4837;
    _t4838 = malloc(sizeof(Bool));
    *_t4838 = 0;
    (void)_t4838;
    _t4839 = Str_lit("script", 6ULL);
    (void)_t4839;
    _t4840 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4840->name = *_ca; free(_ca); }
    _t4840->needs_main = DEREF(_t4835);
    _t4840->decls_only = DEREF(_t4836);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4840->auto_import = *_ca; free(_ca); }
    _t4840->is_pure = DEREF(_t4837);
    _t4840->debug_prints = DEREF(_t4838);
    (void)_t4840;
    _t4841 = malloc(sizeof(Bool));
    *_t4841 = 1;
    (void)_t4841;
    _t4842 = malloc(sizeof(Bool));
    *_t4842 = 1;
    (void)_t4842;
    _t4843 = malloc(sizeof(Bool));
    *_t4843 = 0;
    (void)_t4843;
    _t4844 = malloc(sizeof(Bool));
    *_t4844 = 0;
    (void)_t4844;
    _t4845 = Str_lit("cli", 3ULL);
    (void)_t4845;
    _t4846 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4846->name = *_ca; free(_ca); }
    _t4846->needs_main = DEREF(_t4841);
    _t4846->decls_only = DEREF(_t4842);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4846->auto_import = *_ca; free(_ca); }
    _t4846->is_pure = DEREF(_t4843);
    _t4846->debug_prints = DEREF(_t4844);
    (void)_t4846;
    _t4847 = malloc(sizeof(Bool));
    *_t4847 = 1;
    (void)_t4847;
    _t4848 = malloc(sizeof(Bool));
    *_t4848 = 1;
    (void)_t4848;
    _t4849 = malloc(sizeof(Bool));
    *_t4849 = 0;
    (void)_t4849;
    _t4850 = malloc(sizeof(Bool));
    *_t4850 = 0;
    (void)_t4850;
    _t4851 = Str_lit("gui", 3ULL);
    (void)_t4851;
    _t4852 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4852->name = *_ca; free(_ca); }
    _t4852->needs_main = DEREF(_t4847);
    _t4852->decls_only = DEREF(_t4848);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4852->auto_import = *_ca; free(_ca); }
    _t4852->is_pure = DEREF(_t4849);
    _t4852->debug_prints = DEREF(_t4850);
    (void)_t4852;
    _t4853 = malloc(sizeof(Bool));
    *_t4853 = 0;
    (void)_t4853;
    _t4854 = malloc(sizeof(Bool));
    *_t4854 = 1;
    (void)_t4854;
    _t4855 = malloc(sizeof(Bool));
    *_t4855 = 0;
    (void)_t4855;
    _t4856 = malloc(sizeof(Bool));
    *_t4856 = 0;
    (void)_t4856;
    _t4857 = Str_lit("test", 4ULL);
    (void)_t4857;
    _t4858 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4858->name = *_ca; free(_ca); }
    _t4858->needs_main = DEREF(_t4853);
    _t4858->decls_only = DEREF(_t4854);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4858->auto_import = *_ca; free(_ca); }
    _t4858->is_pure = DEREF(_t4855);
    _t4858->debug_prints = DEREF(_t4856);
    (void)_t4858;
    _t4859 = malloc(sizeof(Bool));
    *_t4859 = 0;
    (void)_t4859;
    _t4860 = malloc(sizeof(Bool));
    *_t4860 = 1;
    (void)_t4860;
    _t4861 = malloc(sizeof(Bool));
    *_t4861 = 1;
    (void)_t4861;
    _t4862 = malloc(sizeof(Bool));
    *_t4862 = 0;
    (void)_t4862;
    _t4863 = Str_lit("pure", 4ULL);
    (void)_t4863;
    _t4864 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4864->name = *_ca; free(_ca); }
    _t4864->needs_main = DEREF(_t4859);
    _t4864->decls_only = DEREF(_t4860);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4864->auto_import = *_ca; free(_ca); }
    _t4864->is_pure = DEREF(_t4861);
    _t4864->debug_prints = DEREF(_t4862);
    (void)_t4864;
    _t4865 = malloc(sizeof(Bool));
    *_t4865 = 0;
    (void)_t4865;
    _t4866 = malloc(sizeof(Bool));
    *_t4866 = 1;
    (void)_t4866;
    _t4867 = malloc(sizeof(Bool));
    *_t4867 = 1;
    (void)_t4867;
    _t4868 = malloc(sizeof(Bool));
    *_t4868 = 1;
    (void)_t4868;
    _t4869 = Str_lit("pura", 4ULL);
    (void)_t4869;
    _t4870 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4870->name = *_ca; free(_ca); }
    _t4870->needs_main = DEREF(_t4865);
    _t4870->decls_only = DEREF(_t4866);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4870->auto_import = *_ca; free(_ca); }
    _t4870->is_pure = DEREF(_t4867);
    _t4870->debug_prints = DEREF(_t4868);
    (void)_t4870;
    _t4871 = malloc(sizeof(Bool));
    *_t4871 = 0;
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
    _t4875 = Str_lit("lib", 3ULL);
    (void)_t4875;
    _t4876 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4876->name = *_ca; free(_ca); }
    _t4876->needs_main = DEREF(_t4871);
    _t4876->decls_only = DEREF(_t4872);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4876->auto_import = *_ca; free(_ca); }
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
    *_t4880 = 1;
    (void)_t4880;
    _t4881 = Str_lit("liba", 4ULL);
    (void)_t4881;
    _t4882 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4882->name = *_ca; free(_ca); }
    _t4882->needs_main = DEREF(_t4877);
    _t4882->decls_only = DEREF(_t4878);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4882->auto_import = *_ca; free(_ca); }
    _t4882->is_pure = DEREF(_t4879);
    _t4882->debug_prints = DEREF(_t4880);
    (void)_t4882;
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
    U64 _t4745; { U64 *_hp = (U64 *)Array_len(args); _t4745 = *_hp; free(_hp); }
    (void)_t4745;
    U64 _t4746 = 0;
    (void)_t4746;
    Bool _t4747 = U64_eq(_t4745, _t4746);
    (void)_t4747;
    ;
    ;
    if (_t4747) {
        usage();
        Str *_t4366 = Str_lit("Str", 3ULL);
        (void)_t4366;
        U64 _t4367; { U64 *_hp = (U64 *)Str_size(); _t4367 = *_hp; free(_hp); }
        (void)_t4367;
        U64 _t4368 = 1;
        (void)_t4368;
        Array *_va82 = Array_new(_t4366, &(U64){_t4367}, &(U64){_t4368});
        (void)_va82;
        Str_delete(_t4366, &(Bool){1});
        ;
        ;
        U64 _t4369 = 0;
        (void)_t4369;
        Str *_t4370 = Str_lit("no arguments", 12ULL);
        (void)_t4370;
        Array_set(_va82, &(U64){_t4369}, _t4370);
        ;
        Str *_t4371 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4371;
        panic(_t4371, _va82);
        Str_delete(_t4371, &(Bool){1});
    }
    ;
    U64 *_t4748 = malloc(sizeof(U64));
    *_t4748 = 0;
    (void)_t4748;
    Str *cmd_ref = Array_get(args, _t4748);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4748, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4749; { U64 *_hp = (U64 *)Array_len(args); _t4749 = *_hp; free(_hp); }
    (void)_t4749;
    U64 _t4750 = 1;
    (void)_t4750;
    Bool _t4751 = U64_eq(_t4749, _t4750);
    (void)_t4751;
    ;
    ;
    if (_t4751) {
        Str *_t4372 = Str_lit("help", 4ULL);
        (void)_t4372;
        Str *_t4373 = Str_lit("--help", 6ULL);
        (void)_t4373;
        Bool _t4374; { Bool *_hp = (Bool *)Str_eq(command, _t4372); _t4374 = *_hp; free(_hp); }
        (void)_t4374;
        Str_delete(_t4372, &(Bool){1});
        Bool _t4375; { Bool *_hp = (Bool *)Str_eq(command, _t4373); _t4375 = *_hp; free(_hp); }
        (void)_t4375;
        Str_delete(_t4373, &(Bool){1});
        Bool _t4376 = Bool_or(_t4374, _t4375);
        (void)_t4376;
        ;
        ;
        if (_t4376) {
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
            U64 _t4393; { U64 *_hp = (U64 *)Array_len(args); _t4393 = *_hp; free(_hp); }
            (void)_t4393;
            Bool _wcond4377; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4393}); _wcond4377 = *_hp; free(_hp); }
            (void)_wcond4377;
            ;
            if (_wcond4377) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4394 = Str_lit("-o", 2ULL);
            (void)_t4394;
            U64 _t4395 = 1;
            (void)_t4395;
            U64 _t4396 = U64_add(DEREF(path_idx), _t4395);
            (void)_t4396;
            ;
            U64 _t4397; { U64 *_hp = (U64 *)Array_len(args); _t4397 = *_hp; free(_hp); }
            (void)_t4397;
            Bool _t4398; { Bool *_hp = (Bool *)Str_eq(flag, _t4394); _t4398 = *_hp; free(_hp); }
            (void)_t4398;
            Str_delete(_t4394, &(Bool){1});
            Bool _t4399; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4396}, &(U64){_t4397}); _t4399 = *_hp; free(_hp); }
            (void)_t4399;
            ;
            ;
            Bool _t4400 = Bool_and(_t4398, _t4399);
            (void)_t4400;
            ;
            ;
            if (_t4400) {
                U64 _t4378 = 1;
                (void)_t4378;
                U64 *_t4379 = malloc(sizeof(U64)); *_t4379 = U64_add(DEREF(path_idx), _t4378);
                (void)_t4379;
                ;
                Str *oval = Array_get(args, _t4379);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4379, &(Bool){1});
                U64 _t4380 = 2;
                (void)_t4380;
                U64 _t4381 = U64_add(DEREF(path_idx), _t4380);
                (void)_t4381;
                ;
                *path_idx = _t4381;
                ;
            } else {
                Str *_t4386 = Str_lit("-c", 2ULL);
                (void)_t4386;
                U64 _t4387 = 1;
                (void)_t4387;
                U64 _t4388 = U64_add(DEREF(path_idx), _t4387);
                (void)_t4388;
                ;
                U64 _t4389; { U64 *_hp = (U64 *)Array_len(args); _t4389 = *_hp; free(_hp); }
                (void)_t4389;
                Bool _t4390; { Bool *_hp = (Bool *)Str_eq(flag, _t4386); _t4390 = *_hp; free(_hp); }
                (void)_t4390;
                Str_delete(_t4386, &(Bool){1});
                Bool _t4391; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4388}, &(U64){_t4389}); _t4391 = *_hp; free(_hp); }
                (void)_t4391;
                ;
                ;
                Bool _t4392 = Bool_and(_t4390, _t4391);
                (void)_t4392;
                ;
                ;
                if (_t4392) {
                    U64 _t4382 = 1;
                    (void)_t4382;
                    U64 *_t4383 = malloc(sizeof(U64)); *_t4383 = U64_add(DEREF(path_idx), _t4382);
                    (void)_t4383;
                    ;
                    Str *cval = Array_get(args, _t4383);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4383, &(Bool){1});
                    U64 _t4384 = 2;
                    (void)_t4384;
                    U64 _t4385 = U64_add(DEREF(path_idx), _t4384);
                    (void)_t4385;
                    ;
                    *path_idx = _t4385;
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
    Str *_t4752 = Str_lit("help", 4ULL);
    (void)_t4752;
    Str *_t4753 = Str_lit("--help", 6ULL);
    (void)_t4753;
    Bool _t4754; { Bool *_hp = (Bool *)Str_eq(command, _t4752); _t4754 = *_hp; free(_hp); }
    (void)_t4754;
    Str_delete(_t4752, &(Bool){1});
    Bool _t4755; { Bool *_hp = (Bool *)Str_eq(command, _t4753); _t4755 = *_hp; free(_hp); }
    (void)_t4755;
    Str_delete(_t4753, &(Bool){1});
    Bool _t4756 = Bool_or(_t4754, _t4755);
    (void)_t4756;
    ;
    ;
    if (_t4756) {
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
    Str *_t4757 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4757;
    Str *core_path = Str_concat(bin_dir, _t4757);
    (void)core_path;
    Str_delete(_t4757, &(Bool){1});
    Str *_t4758 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4758;
    Str *ext_c_path = Str_concat(bin_dir, _t4758);
    (void)ext_c_path;
    Str_delete(_t4758, &(Bool){1});
    Str *_t4759 = Str_lit("Str", 3ULL);
    (void)_t4759;
    U64 _t4760; { U64 *_hp = (U64 *)Str_size(); _t4760 = *_hp; free(_hp); }
    (void)_t4760;
    Set *resolved = Set_new(_t4759, &(U64){_t4760});
    (void)resolved;
    Str_delete(_t4759, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4761; { U64 *_hp = (U64 *)Str_len(abs_path); _t4761 = *_hp; free(_hp); }
    (void)_t4761;
    U64 _t4762 = 0;
    (void)_t4762;
    Bool _t4763; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4761}, &(U64){_t4762}); _t4763 = *_hp; free(_hp); }
    (void)_t4763;
    ;
    ;
    if (_t4763) {
        U64 _t4409; { U64 *_hp = (U64 *)Str_len(abs_path); _t4409 = *_hp; free(_hp); }
        (void)_t4409;
        U64 _t4410 = 1;
        (void)_t4410;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4409, _t4410);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4402 = 0;
            (void)_t4402;
            U8 *_t4403 = Str_get(abs_path, last_slash);
            (void)_t4403;
            U8 _t4404 = 47;
            (void)_t4404;
            Bool _t4405; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4402}); _t4405 = *_hp; free(_hp); }
            (void)_t4405;
            ;
            Bool _t4406; { Bool *_hp = (Bool *)U8_neq(_t4403, &(U8){_t4404}); _t4406 = *_hp; free(_hp); }
            (void)_t4406;
            ;
            Bool _wcond4401 = Bool_and(_t4405, _t4406);
            (void)_wcond4401;
            ;
            ;
            if (_wcond4401) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4407 = 1;
            (void)_t4407;
            U64 _t4408 = U64_sub(DEREF(last_slash), _t4407);
            (void)_t4408;
            ;
            *last_slash = _t4408;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4411 = Str_clone(abs_path);
        (void)_t4411;
        Set_add(resolved, _t4411);
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
    U64 _t4764; { U64 *_hp = (U64 *)Str_len(core_abs); _t4764 = *_hp; free(_hp); }
    (void)_t4764;
    U64 _t4765 = 0;
    (void)_t4765;
    Bool _t4766; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4764}, &(U64){_t4765}); _t4766 = *_hp; free(_hp); }
    (void)_t4766;
    ;
    ;
    if (_t4766) {
        Bool _t4413; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4413 = *_hp; free(_hp); }
        (void)_t4413;
        if (_t4413) {
            Bool _t4412 = 1;
            (void)_t4412;
            skip_core = _t4412;
            ;
        }
        ;
        Str *_t4414 = Str_clone(core_abs);
        (void)_t4414;
        Set_add(resolved, _t4414);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4767; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4767 = *_hp; free(_hp); }
    (void)_t4767;
    U64 _t4768 = 0;
    (void)_t4768;
    Bool _t4769; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4767}, &(U64){_t4768}); _t4769 = *_hp; free(_hp); }
    (void)_t4769;
    ;
    ;
    Bool _t4770 = Bool_not(skip_core);
    (void)_t4770;
    Bool _t4771 = Bool_and(_t4769, _t4770);
    (void)_t4771;
    ;
    ;
    if (_t4771) {
        Str *_t4421 = Str_lit("/src/core", 9ULL);
        (void)_t4421;
        Str *core_dir = Str_concat(bin_dir, _t4421);
        (void)core_dir;
        Str_delete(_t4421, &(Bool){1});
        Str *_t4422 = Str_lit("", 0ULL);
        (void)_t4422;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4422); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4422, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4423 = 0;
        (void)_t4423;
        Bool _t4424; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4423}); _t4424 = *_hp; free(_hp); }
        (void)_t4424;
        ;
        ;
        if (_t4424) {
            Str *_t4415 = Str_lit("Str", 3ULL);
            (void)_t4415;
            U64 _t4416; { U64 *_hp = (U64 *)Str_size(); _t4416 = *_hp; free(_hp); }
            (void)_t4416;
            U64 _t4417 = 1;
            (void)_t4417;
            Array *_va83 = Array_new(_t4415, &(U64){_t4416}, &(U64){_t4417});
            (void)_va83;
            Str_delete(_t4415, &(Bool){1});
            ;
            ;
            U64 _t4418 = 0;
            (void)_t4418;
            Str *_t4419 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4419;
            Array_set(_va83, &(U64){_t4418}, _t4419);
            ;
            Str *_t4420 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4420;
            panic(_t4420, _va83);
            Str_delete(_t4420, &(Bool){1});
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
    Str *_t4772 = Str_lit("script", 6ULL);
    (void)_t4772;
    Mode *cur_mode = mode_resolve(_t4772);
    (void)cur_mode;
    Str_delete(_t4772, &(Bool){1});
    U64 _t4773; { U64 *_hp = (U64 *)Str_len(mode_str); _t4773 = *_hp; free(_hp); }
    (void)_t4773;
    U64 _t4774 = 0;
    (void)_t4774;
    Bool _t4775; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4773}, &(U64){_t4774}); _t4775 = *_hp; free(_hp); }
    (void)_t4775;
    ;
    ;
    if (_t4775) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4434; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4434 = *_hp; free(_hp); }
        (void)_t4434;
        U64 _t4435 = 0;
        (void)_t4435;
        Bool _t4436 = U64_eq(_t4434, _t4435);
        (void)_t4436;
        ;
        ;
        if (_t4436) {
            Str *_t4425 = Str_lit("Str", 3ULL);
            (void)_t4425;
            U64 _t4426; { U64 *_hp = (U64 *)Str_size(); _t4426 = *_hp; free(_hp); }
            (void)_t4426;
            U64 _t4427 = 1;
            (void)_t4427;
            Array *_va84 = Array_new(_t4425, &(U64){_t4426}, &(U64){_t4427});
            (void)_va84;
            Str_delete(_t4425, &(Bool){1});
            ;
            ;
            Str *_t4428 = Str_lit("unknown mode '", 14ULL);
            (void)_t4428;
            Str *_t4429 = Str_concat(_t4428, mode_str);
            (void)_t4429;
            Str_delete(_t4428, &(Bool){1});
            Str *_t4430 = Str_lit("'", 1ULL);
            (void)_t4430;
            U64 _t4431 = 0;
            (void)_t4431;
            Str *_t4432 = Str_concat(_t4429, _t4430);
            (void)_t4432;
            Str_delete(_t4429, &(Bool){1});
            Str_delete(_t4430, &(Bool){1});
            Array_set(_va84, &(U64){_t4431}, _t4432);
            ;
            Str *_t4433 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4433;
            panic(_t4433, _va84);
            Str_delete(_t4433, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4776; { U64 *_hp = (U64 *)Vec_len(imports); _t4776 = *_hp; free(_hp); }
    (void)_t4776;
    U64 _t4777 = 0;
    (void)_t4777;
    Bool _t4778; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4776}, &(U64){_t4777}); _t4778 = *_hp; free(_hp); }
    (void)_t4778;
    ;
    ;
    if (_t4778) {
        Str *_t4443 = Str_lit("/src/lib", 8ULL);
        (void)_t4443;
        Str *lib_dir = Str_concat(bin_dir, _t4443);
        (void)lib_dir;
        Str_delete(_t4443, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4444 = 0;
        (void)_t4444;
        Bool _t4445; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4444}); _t4445 = *_hp; free(_hp); }
        (void)_t4445;
        ;
        ;
        if (_t4445) {
            Str *_t4437 = Str_lit("Str", 3ULL);
            (void)_t4437;
            U64 _t4438; { U64 *_hp = (U64 *)Str_size(); _t4438 = *_hp; free(_hp); }
            (void)_t4438;
            U64 _t4439 = 1;
            (void)_t4439;
            Array *_va85 = Array_new(_t4437, &(U64){_t4438}, &(U64){_t4439});
            (void)_va85;
            Str_delete(_t4437, &(Bool){1});
            ;
            ;
            U64 _t4440 = 0;
            (void)_t4440;
            Str *_t4441 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4441;
            Array_set(_va85, &(U64){_t4440}, _t4441);
            ;
            Str *_t4442 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4442;
            panic(_t4442, _va85);
            Str_delete(_t4442, &(Bool){1});
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
    Bool _t4779 = Bool_not(skip_core);
    (void)_t4779;
    ;
    if (_t4779) {
        while (1) {
            U32 _t4447 = expr_nchildren(core_ast);
            (void)_t4447;
            Bool _wcond4446; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4447}); _wcond4446 = *_hp; free(_hp); }
            (void)_wcond4446;
            ;
            if (_wcond4446) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4448 = 1;
            (void)_t4448;
            U32 _t4449 = U32_add(DEREF(i), _t4448);
            (void)_t4449;
            ;
            *i = _t4449;
            ;
        }
        U32 _t4454 = 0;
        (void)_t4454;
        *i = _t4454;
        ;
        while (1) {
            U32 _t4451 = expr_vec_count(core_import_decls);
            (void)_t4451;
            Bool _wcond4450; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4451}); _wcond4450 = *_hp; free(_hp); }
            (void)_wcond4450;
            ;
            if (_wcond4450) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4452 = 1;
            (void)_t4452;
            U32 _t4453 = U32_add(DEREF(i), _t4452);
            (void)_t4453;
            ;
            *i = _t4453;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4780; { U64 *_hp = (U64 *)Str_len(auto_import); _t4780 = *_hp; free(_hp); }
    (void)_t4780;
    U64 _t4781 = 0;
    (void)_t4781;
    Bool _t4782; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4780}, &(U64){_t4781}); _t4782 = *_hp; free(_hp); }
    (void)_t4782;
    ;
    ;
    if (_t4782) {
        Str *_t4459 = Str_lit("/src/modes/", 11ULL);
        (void)_t4459;
        Str *_t4460 = Str_concat(bin_dir, _t4459);
        (void)_t4460;
        Str_delete(_t4459, &(Bool){1});
        Str *_t4461 = Str_concat(_t4460, auto_import);
        (void)_t4461;
        Str_delete(_t4460, &(Bool){1});
        Str *_t4462 = Str_lit(".til", 4ULL);
        (void)_t4462;
        Str *mode_til_path = Str_concat(_t4461, _t4462);
        (void)mode_til_path;
        Str_delete(_t4461, &(Bool){1});
        Str_delete(_t4462, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4463 = 0;
        (void)_t4463;
        *i = _t4463;
        ;
        while (1) {
            U32 _t4456 = expr_nchildren(mode_ast);
            (void)_t4456;
            Bool _wcond4455; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4456}); _wcond4455 = *_hp; free(_hp); }
            (void)_wcond4455;
            ;
            if (_wcond4455) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4457 = 1;
            (void)_t4457;
            U32 _t4458 = U32_add(DEREF(i), _t4457);
            (void)_t4458;
            ;
            *i = _t4458;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4783 = 0;
    (void)_t4783;
    *i = _t4783;
    ;
    while (1) {
        U32 _t4465 = expr_vec_count(import_decls);
        (void)_t4465;
        Bool _wcond4464; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4465}); _wcond4464 = *_hp; free(_hp); }
        (void)_wcond4464;
        ;
        if (_wcond4464) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4466 = 1;
        (void)_t4466;
        U32 _t4467 = U32_add(DEREF(i), _t4466);
        (void)_t4467;
        ;
        *i = _t4467;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4784 = 0;
    (void)_t4784;
    *i = _t4784;
    ;
    while (1) {
        U32 _t4469 = expr_nchildren(ast);
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
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4470 = 1;
        (void)_t4470;
        U32 _t4471 = U32_add(DEREF(i), _t4470);
        (void)_t4471;
        ;
        *i = _t4471;
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
    U32 _t4785 = 0;
    (void)_t4785;
    *i = _t4785;
    ;
    while (1) {
        U32 _t4487 = expr_nchildren(ast);
        (void)_t4487;
        Bool _wcond4472; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4487}); _wcond4472 = *_hp; free(_hp); }
        (void)_wcond4472;
        ;
        if (_wcond4472) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4488 = expr_get_tag(stmt);
        (void)_t4488;
        U32 _t4489 = expr_nchildren(stmt);
        (void)_t4489;
        U32 _t4490 = 2;
        (void)_t4490;
        Bool _t4491 = I32_eq(_t4488, DEREF(NODE_FCALL));
        (void)_t4491;
        ;
        Bool _t4492 = U32_eq(_t4489, _t4490);
        (void)_t4492;
        ;
        ;
        U32 *_t4493 = malloc(sizeof(U32));
        *_t4493 = 0;
        (void)_t4493;
        Expr *_t4494 = expr_get_child(stmt, DEREF(_t4493));
        (void)_t4494;
        I32 _t4495 = expr_get_tag(_t4494);
        (void)_t4495;
        U32_delete(_t4493, &(Bool){1});
        Bool _t4496 = Bool_and(_t4491, _t4492);
        (void)_t4496;
        ;
        ;
        Bool _t4497 = I32_eq(_t4495, DEREF(NODE_IDENT));
        (void)_t4497;
        ;
        U32 *_t4498 = malloc(sizeof(U32));
        *_t4498 = 1;
        (void)_t4498;
        Expr *_t4499 = expr_get_child(stmt, DEREF(_t4498));
        (void)_t4499;
        I32 _t4500 = expr_get_tag(_t4499);
        (void)_t4500;
        U32_delete(_t4498, &(Bool){1});
        Bool _t4501 = Bool_and(_t4496, _t4497);
        (void)_t4501;
        ;
        ;
        Bool _t4502 = I32_eq(_t4500, DEREF(NODE_LITERAL_STR));
        (void)_t4502;
        ;
        Bool _t4503 = Bool_and(_t4501, _t4502);
        (void)_t4503;
        ;
        ;
        if (_t4503) {
            U32 *_t4481 = malloc(sizeof(U32));
            *_t4481 = 0;
            (void)_t4481;
            Expr *_t4482 = expr_get_child(stmt, DEREF(_t4481));
            (void)_t4482;
            Str *fname = expr_get_str_val(_t4482);
            (void)fname;
            U32 *_t4483 = malloc(sizeof(U32));
            *_t4483 = 1;
            (void)_t4483;
            Expr *_t4484 = expr_get_child(stmt, DEREF(_t4483));
            (void)_t4484;
            Str *arg = expr_get_str_val(_t4484);
            (void)arg;
            Str *_t4485 = Str_lit("link", 4ULL);
            (void)_t4485;
            Bool _t4486; { Bool *_hp = (Bool *)Str_eq(fname, _t4485); _t4486 = *_hp; free(_hp); }
            (void)_t4486;
            Str_delete(_t4485, &(Bool){1});
            if (_t4486) {
                Str *_t4473 = Str_lit(" -l", 3ULL);
                (void)_t4473;
                Str *_t4474 = Str_concat(link_flags, _t4473);
                (void)_t4474;
                Str_delete(_t4473, &(Bool){1});
                link_flags = Str_concat(_t4474, arg);
                Str_delete(_t4474, &(Bool){1});
            } else {
                Str *_t4479 = Str_lit("link_c", 6ULL);
                (void)_t4479;
                Bool _t4480; { Bool *_hp = (Bool *)Str_eq(fname, _t4479); _t4480 = *_hp; free(_hp); }
                (void)_t4480;
                Str_delete(_t4479, &(Bool){1});
                if (_t4480) {
                    U64 _t4476; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4476 = *_hp; free(_hp); }
                    (void)_t4476;
                    U64 _t4477 = 0;
                    (void)_t4477;
                    Bool _t4478; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4476}, &(U64){_t4477}); _t4478 = *_hp; free(_hp); }
                    (void)_t4478;
                    ;
                    ;
                    if (_t4478) {
                        Str *_t4475 = Str_lit(" ", 1ULL);
                        (void)_t4475;
                        link_c_paths = Str_concat(link_c_paths, _t4475);
                        Str_delete(_t4475, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4481, &(Bool){1});
            U32_delete(_t4483, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4504 = 1;
        (void)_t4504;
        U32 _t4505 = U32_add(DEREF(i), _t4504);
        (void)_t4505;
        ;
        *i = _t4505;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4786 = init_declarations(ast, scope);
    (void)_t4786;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4787 = 0;
    (void)_t4787;
    Bool _t4788; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4787}); _t4788 = *_hp; free(_hp); }
    (void)_t4788;
    ;
    if (_t4788) {
        Str *_t4506 = Str_lit("Str", 3ULL);
        (void)_t4506;
        U64 _t4507; { U64 *_hp = (U64 *)Str_size(); _t4507 = *_hp; free(_hp); }
        (void)_t4507;
        U64 _t4508 = 1;
        (void)_t4508;
        Array *_va86 = Array_new(_t4506, &(U64){_t4507}, &(U64){_t4508});
        (void)_va86;
        Str_delete(_t4506, &(Bool){1});
        ;
        ;
        Str *_t4509 = I32_to_str(&(I32){type_errors});
        (void)_t4509;
        Str *_t4510 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4510;
        U64 _t4511 = 0;
        (void)_t4511;
        Str *_t4512 = Str_concat(_t4509, _t4510);
        (void)_t4512;
        Str_delete(_t4509, &(Bool){1});
        Str_delete(_t4510, &(Bool){1});
        Array_set(_va86, &(U64){_t4511}, _t4512);
        ;
        Str *_t4513 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4513;
        panic(_t4513, _va86);
        Str_delete(_t4513, &(Bool){1});
    }
    ;
    ;
    Str *_t4789 = Str_lit("test", 4ULL);
    (void)_t4789;
    Str *_t4790 = Str_lit("test", 4ULL);
    (void)_t4790;
    Bool _t4791; { Bool *_hp = (Bool *)Str_eq(command, _t4789); _t4791 = *_hp; free(_hp); }
    (void)_t4791;
    Str_delete(_t4789, &(Bool){1});
    Bool _t4792; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4790); _t4792 = *_hp; free(_hp); }
    (void)_t4792;
    Str_delete(_t4790, &(Bool){1});
    Str *_t4793 = Str_lit("pure", 4ULL);
    (void)_t4793;
    Bool _t4794 = Bool_or(_t4791, _t4792);
    (void)_t4794;
    ;
    ;
    Bool _t4795; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4793); _t4795 = *_hp; free(_hp); }
    (void)_t4795;
    Str_delete(_t4793, &(Bool){1});
    Str *_t4796 = Str_lit("pura", 4ULL);
    (void)_t4796;
    Bool _t4797 = Bool_or(_t4794, _t4795);
    (void)_t4797;
    ;
    ;
    Bool _t4798; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4796); _t4798 = *_hp; free(_hp); }
    (void)_t4798;
    Str_delete(_t4796, &(Bool){1});
    Bool run_tests = Bool_or(_t4797, _t4798);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4799 = Str_lit("translate", 9ULL);
    (void)_t4799;
    Str *_t4800 = Str_lit("build", 5ULL);
    (void)_t4800;
    Bool _t4801; { Bool *_hp = (Bool *)Str_eq(command, _t4799); _t4801 = *_hp; free(_hp); }
    (void)_t4801;
    Str_delete(_t4799, &(Bool){1});
    Bool _t4802; { Bool *_hp = (Bool *)Str_eq(command, _t4800); _t4802 = *_hp; free(_hp); }
    (void)_t4802;
    Str_delete(_t4800, &(Bool){1});
    Bool _t4803; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4803 = *_hp; free(_hp); }
    (void)_t4803;
    Bool _t4804 = Bool_or(_t4801, _t4802);
    (void)_t4804;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4803, _t4804);
    (void)is_lib_target;
    ;
    ;
    U64 _t4805; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4805 = *_hp; free(_hp); }
    (void)_t4805;
    U64 _t4806 = 0;
    (void)_t4806;
    Bool _t4807 = Bool_not(is_lib_target);
    (void)_t4807;
    ;
    Bool _t4808 = U64_eq(_t4805, _t4806);
    (void)_t4808;
    ;
    ;
    Bool _t4809 = Bool_and(_t4807, _t4808);
    (void)_t4809;
    ;
    ;
    if (_t4809) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4810; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4810 = *_hp; free(_hp); }
    (void)_t4810;
    U64 _t4811 = 0;
    (void)_t4811;
    Bool _t4812; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4810}, &(U64){_t4811}); _t4812 = *_hp; free(_hp); }
    (void)_t4812;
    ;
    ;
    if (_t4812) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4813 = Str_lit("Str", 3ULL);
    (void)_t4813;
    U64 _t4814; { U64 *_hp = (U64 *)Str_size(); _t4814 = *_hp; free(_hp); }
    (void)_t4814;
    Vec *user_argv = Vec_new(_t4813, &(U64){_t4814});
    (void)user_argv;
    Str_delete(_t4813, &(Bool){1});
    ;
    U64 _t4815 = 1;
    (void)_t4815;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4815);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4530; { U64 *_hp = (U64 *)Array_len(args); _t4530 = *_hp; free(_hp); }
        (void)_t4530;
        Bool _wcond4514; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4530}); _wcond4514 = *_hp; free(_hp); }
        (void)_wcond4514;
        ;
        if (_wcond4514) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4531 = Str_lit("-l", 2ULL);
        (void)_t4531;
        Bool _t4532; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4531); _t4532 = *_hp; free(_hp); }
        (void)_t4532;
        Str_delete(_t4531, &(Bool){1});
        if (_t4532) {
            U64 _t4517 = 2;
            (void)_t4517;
            U64 _t4518; { U64 *_hp = (U64 *)Str_len(arg); _t4518 = *_hp; free(_hp); }
            (void)_t4518;
            Str *lib = Str_substr(arg, &(U64){_t4517}, &(U64){_t4518});
            (void)lib;
            ;
            ;
            U64 _t4519; { U64 *_hp = (U64 *)Str_len(lib); _t4519 = *_hp; free(_hp); }
            (void)_t4519;
            U64 _t4520 = 0;
            (void)_t4520;
            U64 _t4521 = 1;
            (void)_t4521;
            U64 _t4522 = U64_add(DEREF(ai), _t4521);
            (void)_t4522;
            ;
            U64 _t4523; { U64 *_hp = (U64 *)Array_len(args); _t4523 = *_hp; free(_hp); }
            (void)_t4523;
            Bool _t4524 = U64_eq(_t4519, _t4520);
            (void)_t4524;
            ;
            ;
            Bool _t4525; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4522}, &(U64){_t4523}); _t4525 = *_hp; free(_hp); }
            (void)_t4525;
            ;
            ;
            Bool _t4526 = Bool_and(_t4524, _t4525);
            (void)_t4526;
            ;
            ;
            if (_t4526) {
                U64 _t4515 = 1;
                (void)_t4515;
                U64 _t4516 = U64_add(DEREF(ai), _t4515);
                (void)_t4516;
                ;
                *ai = _t4516;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4527 = Str_lit(" -l", 3ULL);
            (void)_t4527;
            Str *_t4528 = Str_concat(link_flags, _t4527);
            (void)_t4528;
            Str_delete(_t4527, &(Bool){1});
            link_flags = Str_concat(_t4528, lib);
            Str_delete(_t4528, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4529 = Str_clone(arg);
            (void)_t4529;
            Vec_push(user_argv, _t4529);
        }
        ;
        U64 _t4533 = 1;
        (void)_t4533;
        U64 _t4534 = U64_add(DEREF(ai), _t4533);
        (void)_t4534;
        ;
        *ai = _t4534;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4816; { U64 *_hp = (U64 *)Str_len(link_flags); _t4816 = *_hp; free(_hp); }
    (void)_t4816;
    U64 _t4817 = 0;
    (void)_t4817;
    Bool _t4818; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4816}, &(U64){_t4817}); _t4818 = *_hp; free(_hp); }
    (void)_t4818;
    ;
    ;
    if (_t4818) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4819 = Str_lit("interpret", 9ULL);
    (void)_t4819;
    Str *_t4820 = Str_lit("test", 4ULL);
    (void)_t4820;
    Bool _t4821; { Bool *_hp = (Bool *)Str_eq(command, _t4819); _t4821 = *_hp; free(_hp); }
    (void)_t4821;
    Str_delete(_t4819, &(Bool){1});
    Bool _t4822; { Bool *_hp = (Bool *)Str_eq(command, _t4820); _t4822 = *_hp; free(_hp); }
    (void)_t4822;
    Str_delete(_t4820, &(Bool){1});
    Bool _t4823 = Bool_or(_t4821, _t4822);
    (void)_t4823;
    ;
    ;
    if (_t4823) {
        Str *_t4541 = Str_lit("interpret", 9ULL);
        (void)_t4541;
        Bool _t4542; { Bool *_hp = (Bool *)Str_eq(command, _t4541); _t4542 = *_hp; free(_hp); }
        (void)_t4542;
        Str_delete(_t4541, &(Bool){1});
        Bool _t4543 = Bool_and(is_lib_mode, _t4542);
        (void)_t4543;
        ;
        if (_t4543) {
            Str *_t4535 = Str_lit("Str", 3ULL);
            (void)_t4535;
            U64 _t4536; { U64 *_hp = (U64 *)Str_size(); _t4536 = *_hp; free(_hp); }
            (void)_t4536;
            U64 _t4537 = 1;
            (void)_t4537;
            Array *_va87 = Array_new(_t4535, &(U64){_t4536}, &(U64){_t4537});
            (void)_va87;
            Str_delete(_t4535, &(Bool){1});
            ;
            ;
            U64 _t4538 = 0;
            (void)_t4538;
            Str *_t4539 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4539;
            Array_set(_va87, &(U64){_t4538}, _t4539);
            ;
            Str *_t4540 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4540;
            panic(_t4540, _va87);
            Str_delete(_t4540, &(Bool){1});
        }
        ;
        I32 _t4544 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4544;
        result = _t4544;
        ;
    } else {
        Str *_t4737 = Str_lit("translate", 9ULL);
        (void)_t4737;
        Str *_t4738 = Str_lit("build", 5ULL);
        (void)_t4738;
        Bool _t4739; { Bool *_hp = (Bool *)Str_eq(command, _t4737); _t4739 = *_hp; free(_hp); }
        (void)_t4739;
        Str_delete(_t4737, &(Bool){1});
        Bool _t4740; { Bool *_hp = (Bool *)Str_eq(command, _t4738); _t4740 = *_hp; free(_hp); }
        (void)_t4740;
        Str_delete(_t4738, &(Bool){1});
        Str *_t4741 = Str_lit("run", 3ULL);
        (void)_t4741;
        Bool _t4742 = Bool_or(_t4739, _t4740);
        (void)_t4742;
        ;
        ;
        Bool _t4743; { Bool *_hp = (Bool *)Str_eq(command, _t4741); _t4743 = *_hp; free(_hp); }
        (void)_t4743;
        Str_delete(_t4741, &(Bool){1});
        Bool _t4744 = Bool_or(_t4742, _t4743);
        (void)_t4744;
        ;
        ;
        if (_t4744) {
            Str *_t4670 = Str_lit("run", 3ULL);
            (void)_t4670;
            Bool _t4671; { Bool *_hp = (Bool *)Str_eq(command, _t4670); _t4671 = *_hp; free(_hp); }
            (void)_t4671;
            Str_delete(_t4670, &(Bool){1});
            Bool _t4672 = Bool_and(is_lib_mode, _t4671);
            (void)_t4672;
            ;
            if (_t4672) {
                Str *_t4545 = Str_lit("Str", 3ULL);
                (void)_t4545;
                U64 _t4546; { U64 *_hp = (U64 *)Str_size(); _t4546 = *_hp; free(_hp); }
                (void)_t4546;
                U64 _t4547 = 1;
                (void)_t4547;
                Array *_va88 = Array_new(_t4545, &(U64){_t4546}, &(U64){_t4547});
                (void)_va88;
                Str_delete(_t4545, &(Bool){1});
                ;
                ;
                U64 _t4548 = 0;
                (void)_t4548;
                Str *_t4549 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4549;
                Array_set(_va88, &(U64){_t4548}, _t4549);
                ;
                Str *_t4550 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4550;
                panic(_t4550, _va88);
                Str_delete(_t4550, &(Bool){1});
            }
            ;
            Str *_t4673 = Str_lit("/", 1ULL);
            (void)_t4673;
            I64 *last_slash = Str_rfind(path, _t4673);
            (void)last_slash;
            Str_delete(_t4673, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4674 = 0;
            (void)_t4674;
            Bool _t4675; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4674}); _t4675 = *_hp; free(_hp); }
            (void)_t4675;
            ;
            if (_t4675) {
                I64 _t4551 = 1;
                (void)_t4551;
                I64 _t4552 = I64_add(DEREF(last_slash), _t4551);
                (void)_t4552;
                ;
                U64 _t4553; { U64 *_hp = (U64 *)Str_len(path); _t4553 = *_hp; free(_hp); }
                (void)_t4553;
                U64 _t4554 = I64_to_u64(DEREF(last_slash));
                (void)_t4554;
                U64 _t4555 = U64_sub(_t4553, _t4554);
                (void)_t4555;
                ;
                ;
                U64 _t4556 = 1;
                (void)_t4556;
                U64 _t4557 = I64_to_u64(_t4552);
                (void)_t4557;
                ;
                U64 _t4558 = U64_sub(_t4555, _t4556);
                (void)_t4558;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4557}, &(U64){_t4558});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4676 = Str_lit(".til", 4ULL);
            (void)_t4676;
            Bool _t4677; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4676); _t4677 = *_hp; free(_hp); }
            (void)_t4677;
            Str_delete(_t4676, &(Bool){1});
            if (_t4677) {
                U64 _t4559 = 4;
                (void)_t4559;
                U64 _t4560 = U64_sub(name_len, _t4559);
                (void)_t4560;
                ;
                name_len = _t4560;
                ;
            }
            ;
            U64 _t4678 = 0;
            (void)_t4678;
            Str *name = Str_substr(basename, &(U64){_t4678}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4679 = Str_lit("gen/til/", 8ULL);
            (void)_t4679;
            Str *_t4680 = Str_concat(_t4679, name);
            (void)_t4680;
            Str_delete(_t4679, &(Bool){1});
            Str *_t4681 = Str_lit(".c", 2ULL);
            (void)_t4681;
            Str *c_path = Str_concat(_t4680, _t4681);
            (void)c_path;
            Str_delete(_t4680, &(Bool){1});
            Str_delete(_t4681, &(Bool){1});
            U64 _t4682; { U64 *_hp = (U64 *)Str_len(custom_c); _t4682 = *_hp; free(_hp); }
            (void)_t4682;
            U64 _t4683 = 0;
            (void)_t4683;
            Bool _t4684; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4682}, &(U64){_t4683}); _t4684 = *_hp; free(_hp); }
            (void)_t4684;
            ;
            ;
            if (_t4684) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4685 = Str_lit("bin/til/", 8ULL);
            (void)_t4685;
            Str *bin_path = Str_concat(_t4685, name);
            (void)bin_path;
            Str_delete(_t4685, &(Bool){1});
            U64 _t4686; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4686 = *_hp; free(_hp); }
            (void)_t4686;
            U64 _t4687 = 0;
            (void)_t4687;
            Bool _t4688; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4686}, &(U64){_t4687}); _t4688 = *_hp; free(_hp); }
            (void)_t4688;
            ;
            ;
            if (_t4688) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4689 = Str_lit("run", 3ULL);
            (void)_t4689;
            Bool _t4690; { Bool *_hp = (Bool *)Str_eq(command, _t4689); _t4690 = *_hp; free(_hp); }
            (void)_t4690;
            Str_delete(_t4689, &(Bool){1});
            Bool _t4691; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4691 = *_hp; free(_hp); }
            (void)_t4691;
            Bool _t4692 = Bool_not(_t4690);
            (void)_t4692;
            ;
            Bool do_lib = Bool_and(_t4691, _t4692);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4561 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4561;
                I32 _t4562 = til_system(_t4561);
                (void)_t4562;
                Str_delete(_t4561, &(Bool){1});
                ;
            } else {
                Str *_t4567 = Str_lit("/", 1ULL);
                (void)_t4567;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4567); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4567, &(Bool){1});
                Str *_t4568 = Str_lit("/", 1ULL);
                (void)_t4568;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4568); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4568, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4569 = 0;
                (void)_t4569;
                Bool _t4570; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4569}); _t4570 = *_hp; free(_hp); }
                (void)_t4570;
                ;
                if (_t4570) {
                    U64 _t4563 = 0;
                    (void)_t4563;
                    U64 _t4564 = I64_to_u64(cp_slash);
                    (void)_t4564;
                    cp_dir = Str_substr(c_path, &(U64){_t4563}, &(U64){_t4564});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4571 = 0;
                (void)_t4571;
                Bool _t4572; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4571}); _t4572 = *_hp; free(_hp); }
                (void)_t4572;
                ;
                if (_t4572) {
                    U64 _t4565 = 0;
                    (void)_t4565;
                    U64 _t4566 = I64_to_u64(bp_slash);
                    (void)_t4566;
                    bp_dir = Str_substr(bin_path, &(U64){_t4565}, &(U64){_t4566});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4573 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4573;
                Str *_t4574 = Str_concat(_t4573, cp_dir);
                (void)_t4574;
                Str_delete(_t4573, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4575 = Str_lit(" ", 1ULL);
                (void)_t4575;
                Str *_t4576 = Str_concat(_t4574, _t4575);
                (void)_t4576;
                Str_delete(_t4574, &(Bool){1});
                Str_delete(_t4575, &(Bool){1});
                Str *_t4577 = Str_concat(_t4576, bp_dir);
                (void)_t4577;
                Str_delete(_t4576, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4578 = til_system(_t4577);
                (void)_t4578;
                Str_delete(_t4577, &(Bool){1});
                ;
            }
            I32 _t4693 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4693;
            result = _t4693;
            ;
            I32 _t4694 = 0;
            (void)_t4694;
            Bool _t4695 = I32_eq(result, _t4694);
            (void)_t4695;
            ;
            Bool _t4696 = Bool_and(_t4695, do_lib);
            (void)_t4696;
            ;
            if (_t4696) {
                Str *_t4635 = Str_lit("gen/til/", 8ULL);
                (void)_t4635;
                Str *_t4636 = Str_concat(_t4635, name);
                (void)_t4636;
                Str_delete(_t4635, &(Bool){1});
                Str *_t4637 = Str_lit(".h", 2ULL);
                (void)_t4637;
                Str *h_path = Str_concat(_t4636, _t4637);
                (void)h_path;
                Str_delete(_t4636, &(Bool){1});
                Str_delete(_t4637, &(Bool){1});
                Str *_t4638 = Str_lit("gen/til/", 8ULL);
                (void)_t4638;
                Str *_t4639 = Str_concat(_t4638, name);
                (void)_t4639;
                Str_delete(_t4638, &(Bool){1});
                Str *_t4640 = Str_lit(".til", 4ULL);
                (void)_t4640;
                Str *til_path = Str_concat(_t4639, _t4640);
                (void)til_path;
                Str_delete(_t4639, &(Bool){1});
                Str_delete(_t4640, &(Bool){1});
                I32 _t4641 = build_header(ast, h_path);
                (void)_t4641;
                result = _t4641;
                ;
                I32 _t4642 = 0;
                (void)_t4642;
                Bool _t4643 = I32_eq(result, _t4642);
                (void)_t4643;
                ;
                if (_t4643) {
                    I32 _t4579 = build_til_binding(ast, til_path, name);
                    (void)_t4579;
                    result = _t4579;
                    ;
                }
                ;
                I32 _t4644 = 0;
                (void)_t4644;
                Str *_t4645 = Str_lit("translate", 9ULL);
                (void)_t4645;
                Bool _t4646 = I32_eq(result, _t4644);
                (void)_t4646;
                ;
                Bool _t4647; { Bool *_hp = (Bool *)Str_eq(command, _t4645); _t4647 = *_hp; free(_hp); }
                (void)_t4647;
                Str_delete(_t4645, &(Bool){1});
                Bool _t4648 = Bool_and(_t4646, _t4647);
                (void)_t4648;
                ;
                ;
                if (_t4648) {
                    Str *_t4580 = Str_lit("Str", 3ULL);
                    (void)_t4580;
                    U64 _t4581; { U64 *_hp = (U64 *)Str_size(); _t4581 = *_hp; free(_hp); }
                    (void)_t4581;
                    U64 _t4582 = 1;
                    (void)_t4582;
                    Array *_va89 = Array_new(_t4580, &(U64){_t4581}, &(U64){_t4582});
                    (void)_va89;
                    Str_delete(_t4580, &(Bool){1});
                    ;
                    ;
                    Str *_t4583 = Str_lit("Generated: ", 11ULL);
                    (void)_t4583;
                    U64 _t4584 = 0;
                    (void)_t4584;
                    Str *_t4585 = Str_concat(_t4583, c_path);
                    (void)_t4585;
                    Str_delete(_t4583, &(Bool){1});
                    Array_set(_va89, &(U64){_t4584}, _t4585);
                    ;
                    println(_va89);
                    Str *_t4586 = Str_lit("Str", 3ULL);
                    (void)_t4586;
                    U64 _t4587; { U64 *_hp = (U64 *)Str_size(); _t4587 = *_hp; free(_hp); }
                    (void)_t4587;
                    U64 _t4588 = 1;
                    (void)_t4588;
                    Array *_va90 = Array_new(_t4586, &(U64){_t4587}, &(U64){_t4588});
                    (void)_va90;
                    Str_delete(_t4586, &(Bool){1});
                    ;
                    ;
                    Str *_t4589 = Str_lit("Generated: ", 11ULL);
                    (void)_t4589;
                    U64 _t4590 = 0;
                    (void)_t4590;
                    Str *_t4591 = Str_concat(_t4589, h_path);
                    (void)_t4591;
                    Str_delete(_t4589, &(Bool){1});
                    Array_set(_va90, &(U64){_t4590}, _t4591);
                    ;
                    println(_va90);
                    Str *_t4592 = Str_lit("Str", 3ULL);
                    (void)_t4592;
                    U64 _t4593; { U64 *_hp = (U64 *)Str_size(); _t4593 = *_hp; free(_hp); }
                    (void)_t4593;
                    U64 _t4594 = 1;
                    (void)_t4594;
                    Array *_va91 = Array_new(_t4592, &(U64){_t4593}, &(U64){_t4594});
                    (void)_va91;
                    Str_delete(_t4592, &(Bool){1});
                    ;
                    ;
                    Str *_t4595 = Str_lit("Generated: ", 11ULL);
                    (void)_t4595;
                    U64 _t4596 = 0;
                    (void)_t4596;
                    Str *_t4597 = Str_concat(_t4595, til_path);
                    (void)_t4597;
                    Str_delete(_t4595, &(Bool){1});
                    Array_set(_va91, &(U64){_t4596}, _t4597);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4649 = 0;
                (void)_t4649;
                Str *_t4650 = Str_lit("build", 5ULL);
                (void)_t4650;
                Bool _t4651 = I32_eq(result, _t4649);
                (void)_t4651;
                ;
                Bool _t4652; { Bool *_hp = (Bool *)Str_eq(command, _t4650); _t4652 = *_hp; free(_hp); }
                (void)_t4652;
                Str_delete(_t4650, &(Bool){1});
                Bool _t4653 = Bool_and(_t4651, _t4652);
                (void)_t4653;
                ;
                ;
                if (_t4653) {
                    I32 _t4632 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4632;
                    result = _t4632;
                    ;
                    I32 _t4633 = 0;
                    (void)_t4633;
                    Bool _t4634 = I32_eq(result, _t4633);
                    (void)_t4634;
                    ;
                    if (_t4634) {
                        Str *_t4598 = Str_lit("Str", 3ULL);
                        (void)_t4598;
                        U64 _t4599; { U64 *_hp = (U64 *)Str_size(); _t4599 = *_hp; free(_hp); }
                        (void)_t4599;
                        U64 _t4600 = 1;
                        (void)_t4600;
                        Array *_va92 = Array_new(_t4598, &(U64){_t4599}, &(U64){_t4600});
                        (void)_va92;
                        Str_delete(_t4598, &(Bool){1});
                        ;
                        ;
                        Str *_t4601 = Str_lit("Generated: ", 11ULL);
                        (void)_t4601;
                        U64 _t4602 = 0;
                        (void)_t4602;
                        Str *_t4603 = Str_concat(_t4601, c_path);
                        (void)_t4603;
                        Str_delete(_t4601, &(Bool){1});
                        Array_set(_va92, &(U64){_t4602}, _t4603);
                        ;
                        println(_va92);
                        Str *_t4604 = Str_lit("Str", 3ULL);
                        (void)_t4604;
                        U64 _t4605; { U64 *_hp = (U64 *)Str_size(); _t4605 = *_hp; free(_hp); }
                        (void)_t4605;
                        U64 _t4606 = 1;
                        (void)_t4606;
                        Array *_va93 = Array_new(_t4604, &(U64){_t4605}, &(U64){_t4606});
                        (void)_va93;
                        Str_delete(_t4604, &(Bool){1});
                        ;
                        ;
                        Str *_t4607 = Str_lit("Generated: ", 11ULL);
                        (void)_t4607;
                        U64 _t4608 = 0;
                        (void)_t4608;
                        Str *_t4609 = Str_concat(_t4607, h_path);
                        (void)_t4609;
                        Str_delete(_t4607, &(Bool){1});
                        Array_set(_va93, &(U64){_t4608}, _t4609);
                        ;
                        println(_va93);
                        Str *_t4610 = Str_lit("Str", 3ULL);
                        (void)_t4610;
                        U64 _t4611; { U64 *_hp = (U64 *)Str_size(); _t4611 = *_hp; free(_hp); }
                        (void)_t4611;
                        U64 _t4612 = 1;
                        (void)_t4612;
                        Array *_va94 = Array_new(_t4610, &(U64){_t4611}, &(U64){_t4612});
                        (void)_va94;
                        Str_delete(_t4610, &(Bool){1});
                        ;
                        ;
                        Str *_t4613 = Str_lit("Generated: ", 11ULL);
                        (void)_t4613;
                        U64 _t4614 = 0;
                        (void)_t4614;
                        Str *_t4615 = Str_concat(_t4613, til_path);
                        (void)_t4615;
                        Str_delete(_t4613, &(Bool){1});
                        Array_set(_va94, &(U64){_t4614}, _t4615);
                        ;
                        println(_va94);
                        Str *_t4616 = Str_lit("Str", 3ULL);
                        (void)_t4616;
                        U64 _t4617; { U64 *_hp = (U64 *)Str_size(); _t4617 = *_hp; free(_hp); }
                        (void)_t4617;
                        U64 _t4618 = 1;
                        (void)_t4618;
                        Array *_va95 = Array_new(_t4616, &(U64){_t4617}, &(U64){_t4618});
                        (void)_va95;
                        Str_delete(_t4616, &(Bool){1});
                        ;
                        ;
                        Str *_t4619 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4619;
                        Str *_t4620 = Str_concat(_t4619, name);
                        (void)_t4620;
                        Str_delete(_t4619, &(Bool){1});
                        Str *_t4621 = Str_lit(".so", 3ULL);
                        (void)_t4621;
                        U64 _t4622 = 0;
                        (void)_t4622;
                        Str *_t4623 = Str_concat(_t4620, _t4621);
                        (void)_t4623;
                        Str_delete(_t4620, &(Bool){1});
                        Str_delete(_t4621, &(Bool){1});
                        Array_set(_va95, &(U64){_t4622}, _t4623);
                        ;
                        println(_va95);
                        Str *_t4624 = Str_lit("Str", 3ULL);
                        (void)_t4624;
                        U64 _t4625; { U64 *_hp = (U64 *)Str_size(); _t4625 = *_hp; free(_hp); }
                        (void)_t4625;
                        U64 _t4626 = 1;
                        (void)_t4626;
                        Array *_va96 = Array_new(_t4624, &(U64){_t4625}, &(U64){_t4626});
                        (void)_va96;
                        Str_delete(_t4624, &(Bool){1});
                        ;
                        ;
                        Str *_t4627 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4627;
                        Str *_t4628 = Str_concat(_t4627, name);
                        (void)_t4628;
                        Str_delete(_t4627, &(Bool){1});
                        Str *_t4629 = Str_lit(".a", 2ULL);
                        (void)_t4629;
                        U64 _t4630 = 0;
                        (void)_t4630;
                        Str *_t4631 = Str_concat(_t4628, _t4629);
                        (void)_t4631;
                        Str_delete(_t4628, &(Bool){1});
                        Str_delete(_t4629, &(Bool){1});
                        Array_set(_va96, &(U64){_t4630}, _t4631);
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
            I32 _t4697 = 0;
            (void)_t4697;
            Bool _t4698 = I32_eq(result, _t4697);
            (void)_t4698;
            ;
            Bool _t4699 = Bool_not(do_lib);
            (void)_t4699;
            Str *_t4700 = Str_lit("translate", 9ULL);
            (void)_t4700;
            Bool _t4701 = Bool_and(_t4698, _t4699);
            (void)_t4701;
            ;
            ;
            Bool _t4702; { Bool *_hp = (Bool *)Str_eq(command, _t4700); _t4702 = *_hp; free(_hp); }
            (void)_t4702;
            Str_delete(_t4700, &(Bool){1});
            Bool _t4703 = Bool_and(_t4701, _t4702);
            (void)_t4703;
            ;
            ;
            if (_t4703) {
                Str *_t4654 = Str_lit("Str", 3ULL);
                (void)_t4654;
                U64 _t4655; { U64 *_hp = (U64 *)Str_size(); _t4655 = *_hp; free(_hp); }
                (void)_t4655;
                U64 _t4656 = 1;
                (void)_t4656;
                Array *_va97 = Array_new(_t4654, &(U64){_t4655}, &(U64){_t4656});
                (void)_va97;
                Str_delete(_t4654, &(Bool){1});
                ;
                ;
                Str *_t4657 = Str_lit("Generated: ", 11ULL);
                (void)_t4657;
                U64 _t4658 = 0;
                (void)_t4658;
                Str *_t4659 = Str_concat(_t4657, c_path);
                (void)_t4659;
                Str_delete(_t4657, &(Bool){1});
                Array_set(_va97, &(U64){_t4658}, _t4659);
                ;
                println(_va97);
            }
            ;
            I32 _t4704 = 0;
            (void)_t4704;
            Bool _t4705 = I32_eq(result, _t4704);
            (void)_t4705;
            ;
            Bool _t4706 = Bool_not(do_lib);
            (void)_t4706;
            Str *_t4707 = Str_lit("translate", 9ULL);
            (void)_t4707;
            Bool _t4708; { Bool *_hp = (Bool *)Str_eq(command, _t4707); _t4708 = *_hp; free(_hp); }
            (void)_t4708;
            Str_delete(_t4707, &(Bool){1});
            Bool _t4709 = Bool_and(_t4705, _t4706);
            (void)_t4709;
            ;
            ;
            Bool _t4710 = Bool_not(_t4708);
            (void)_t4710;
            ;
            Bool _t4711 = Bool_and(_t4709, _t4710);
            (void)_t4711;
            ;
            ;
            if (_t4711) {
                I32 _t4660 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4660;
                result = _t4660;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4712 = 0;
            (void)_t4712;
            Bool _t4713 = I32_eq(result, _t4712);
            (void)_t4713;
            ;
            Bool _t4714 = Bool_not(do_lib);
            (void)_t4714;
            ;
            Str *_t4715 = Str_lit("run", 3ULL);
            (void)_t4715;
            Bool _t4716 = Bool_and(_t4713, _t4714);
            (void)_t4716;
            ;
            ;
            Bool _t4717; { Bool *_hp = (Bool *)Str_eq(command, _t4715); _t4717 = *_hp; free(_hp); }
            (void)_t4717;
            Str_delete(_t4715, &(Bool){1});
            Bool _t4718 = Bool_and(_t4716, _t4717);
            (void)_t4718;
            ;
            ;
            if (_t4718) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4662; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4662 = *_hp; free(_hp); }
                    (void)_t4662;
                    Bool _wcond4661; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4662}); _wcond4661 = *_hp; free(_hp); }
                    (void)_wcond4661;
                    ;
                    if (_wcond4661) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4663 = Str_lit(" '", 2ULL);
                    (void)_t4663;
                    Str *_t4664 = Str_concat(cmd, _t4663);
                    (void)_t4664;
                    Str_delete(_t4663, &(Bool){1});
                    Str *_t4665 = Str_concat(_t4664, uarg);
                    (void)_t4665;
                    Str_delete(_t4664, &(Bool){1});
                    Str *_t4666 = Str_lit("'", 1ULL);
                    (void)_t4666;
                    cmd = Str_concat(_t4665, _t4666);
                    Str_delete(_t4665, &(Bool){1});
                    Str_delete(_t4666, &(Bool){1});
                    U64 _t4667 = 1;
                    (void)_t4667;
                    U64 _t4668 = U64_add(DEREF(ui), _t4667);
                    (void)_t4668;
                    ;
                    *ui = _t4668;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4669 = til_system(cmd);
                (void)_t4669;
                Str_delete(cmd, &(Bool){1});
                result = _t4669;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4735 = Str_lit("ast", 3ULL);
            (void)_t4735;
            Bool _t4736; { Bool *_hp = (Bool *)Str_eq(command, _t4735); _t4736 = *_hp; free(_hp); }
            (void)_t4736;
            Str_delete(_t4735, &(Bool){1});
            if (_t4736) {
                Str *_t4719 = Str_lit("Str", 3ULL);
                (void)_t4719;
                U64 _t4720; { U64 *_hp = (U64 *)Str_size(); _t4720 = *_hp; free(_hp); }
                (void)_t4720;
                U64 _t4721 = 1;
                (void)_t4721;
                Array *_va98 = Array_new(_t4719, &(U64){_t4720}, &(U64){_t4721});
                (void)_va98;
                Str_delete(_t4719, &(Bool){1});
                ;
                ;
                Str *_t4722 = Str_lit("mode: ", 6ULL);
                (void)_t4722;
                U64 _t4723 = 0;
                (void)_t4723;
                Str *_t4724 = Str_concat(_t4722, &cur_mode->name);
                (void)_t4724;
                Str_delete(_t4722, &(Bool){1});
                Array_set(_va98, &(U64){_t4723}, _t4724);
                ;
                println(_va98);
                U32 _t4725 = 0;
                (void)_t4725;
                ast_print(ast, _t4725);
                ;
            } else {
                Str *_t4726 = Str_lit("Str", 3ULL);
                (void)_t4726;
                U64 _t4727; { U64 *_hp = (U64 *)Str_size(); _t4727 = *_hp; free(_hp); }
                (void)_t4727;
                U64 _t4728 = 1;
                (void)_t4728;
                Array *_va99 = Array_new(_t4726, &(U64){_t4727}, &(U64){_t4728});
                (void)_va99;
                Str_delete(_t4726, &(Bool){1});
                ;
                ;
                Str *_t4729 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4729;
                Str *_t4730 = Str_concat(_t4729, command);
                (void)_t4730;
                Str_delete(_t4729, &(Bool){1});
                Str *_t4731 = Str_lit("'", 1ULL);
                (void)_t4731;
                U64 _t4732 = 0;
                (void)_t4732;
                Str *_t4733 = Str_concat(_t4730, _t4731);
                (void)_t4733;
                Str_delete(_t4730, &(Bool){1});
                Str_delete(_t4731, &(Bool){1});
                Array_set(_va99, &(U64){_t4732}, _t4733);
                ;
                println(_va99);
                usage();
                I32 _t4734 = 1;
                (void)_t4734;
                result = _t4734;
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
    I64 _t4824 = I32_to_i64(result);
    (void)_t4824;
    ;
    exit(_t4824);
    ;
    return 0;
}

