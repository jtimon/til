#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4205 = Str_lit("Str", 3ULL);
    (void)_t4205;
    U64 _t4206; { U64 *_hp = (U64 *)Str_size(); _t4206 = *_hp; free(_hp); }
    (void)_t4206;
    Vec *paths = Vec_new(_t4205, &(U64){_t4206});
    (void)paths;
    Str_delete(_t4205, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4180 = expr_nchildren(body);
        (void)_t4180;
        Bool _wcond4176; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4180}); _wcond4176 = *_hp; free(_hp); }
        (void)_wcond4176;
        ;
        if (_wcond4176) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4181 = expr_get_tag(stmt);
        (void)_t4181;
        U32 _t4182 = expr_nchildren(stmt);
        (void)_t4182;
        U32 _t4183 = 2;
        (void)_t4183;
        Bool _t4184 = I32_eq(_t4181, DEREF(NODE_FCALL));
        (void)_t4184;
        ;
        Bool _t4185 = U32_eq(_t4182, _t4183);
        (void)_t4185;
        ;
        ;
        U32 *_t4186 = malloc(sizeof(U32));
        *_t4186 = 0;
        (void)_t4186;
        Expr *_t4187 = expr_get_child(stmt, DEREF(_t4186));
        (void)_t4187;
        I32 _t4188 = expr_get_tag(_t4187);
        (void)_t4188;
        U32_delete(_t4186, &(Bool){1});
        Bool _t4189 = Bool_and(_t4184, _t4185);
        (void)_t4189;
        ;
        ;
        Bool _t4190 = I32_eq(_t4188, DEREF(NODE_IDENT));
        (void)_t4190;
        ;
        U32 *_t4191 = malloc(sizeof(U32));
        *_t4191 = 0;
        (void)_t4191;
        Expr *_t4192 = expr_get_child(stmt, DEREF(_t4191));
        (void)_t4192;
        Str *_t4193 = expr_get_str_val(_t4192);
        (void)_t4193;
        Str *_t4194 = Str_lit("import", 6ULL);
        (void)_t4194;
        Bool _t4195 = Bool_and(_t4189, _t4190);
        (void)_t4195;
        ;
        ;
        Bool _t4196; { Bool *_hp = (Bool *)Str_eq(_t4193, _t4194); _t4196 = *_hp; free(_hp); }
        (void)_t4196;
        U32_delete(_t4191, &(Bool){1});
        Str_delete(_t4194, &(Bool){1});
        U32 *_t4197 = malloc(sizeof(U32));
        *_t4197 = 1;
        (void)_t4197;
        Expr *_t4198 = expr_get_child(stmt, DEREF(_t4197));
        (void)_t4198;
        I32 _t4199 = expr_get_tag(_t4198);
        (void)_t4199;
        U32_delete(_t4197, &(Bool){1});
        Bool _t4200 = Bool_and(_t4195, _t4196);
        (void)_t4200;
        ;
        ;
        Bool _t4201 = I32_eq(_t4199, DEREF(NODE_LITERAL_STR));
        (void)_t4201;
        ;
        Bool _t4202 = Bool_and(_t4200, _t4201);
        (void)_t4202;
        ;
        ;
        if (_t4202) {
            U32 *_t4177 = malloc(sizeof(U32));
            *_t4177 = 1;
            (void)_t4177;
            Expr *_t4178 = expr_get_child(stmt, DEREF(_t4177));
            (void)_t4178;
            Str *path = expr_get_str_val(_t4178);
            (void)path;
            Str *_t4179 = Str_clone(path);
            (void)_t4179;
            U32_delete(_t4177, &(Bool){1});
            Vec_push(paths, _t4179);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4203 = 1;
        (void)_t4203;
        U32 _t4204 = U32_add(DEREF(i), _t4203);
        (void)_t4204;
        ;
        *i = _t4204;
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
        U64 _t4257 = 0;
        (void)_t4257;
        U64 _t4258; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4258 = *_hp; free(_hp); }
        (void)_t4258;
        Range *_fc4207 = Range_new(_t4257, _t4258);
        (void)_fc4207;
        ;
        ;
        U64 _fi4207 = 0;
        (void)_fi4207;
        while (1) {
            U64 _t4237; { U64 *_hp = (U64 *)Range_len(_fc4207); _t4237 = *_hp; free(_hp); }
            (void)_t4237;
            Bool _wcond4208; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4207}, &(U64){_t4237}); _wcond4208 = *_hp; free(_hp); }
            (void)_wcond4208;
            ;
            if (_wcond4208) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4207, _fi4207);
            (void)i;
            U64 _t4238 = 1;
            (void)_t4238;
            U64 _t4239 = U64_add(_fi4207, _t4238);
            (void)_t4239;
            ;
            _fi4207 = _t4239;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4240 = Str_lit("/", 1ULL);
            (void)_t4240;
            Str *_t4241 = Str_concat(base_dir, _t4240);
            (void)_t4241;
            Str_delete(_t4240, &(Bool){1});
            Str *try_path = Str_concat(_t4241, import_path);
            (void)try_path;
            Str_delete(_t4241, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4242 = Str_lit("", 0ULL);
            (void)_t4242;
            U64 _t4243; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4243 = *_hp; free(_hp); }
            (void)_t4243;
            U64 _t4244 = 0;
            (void)_t4244;
            Bool _t4245; { Bool *_hp = (Bool *)Str_eq(abs, _t4242); _t4245 = *_hp; free(_hp); }
            (void)_t4245;
            Str_delete(_t4242, &(Bool){1});
            Bool _t4246; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4243}, &(U64){_t4244}); _t4246 = *_hp; free(_hp); }
            (void)_t4246;
            ;
            ;
            Bool _t4247 = Bool_and(_t4245, _t4246);
            (void)_t4247;
            ;
            ;
            if (_t4247) {
                Str *_t4209 = Str_lit("/", 1ULL);
                (void)_t4209;
                Str *_t4210 = Str_concat(lib_dir, _t4209);
                (void)_t4210;
                Str_delete(_t4209, &(Bool){1});
                try_path = Str_concat(_t4210, import_path);
                Str_delete(_t4210, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4248 = Str_lit("", 0ULL);
            (void)_t4248;
            Bool _t4249; { Bool *_hp = (Bool *)Str_eq(abs, _t4248); _t4249 = *_hp; free(_hp); }
            (void)_t4249;
            Str_delete(_t4248, &(Bool){1});
            if (_t4249) {
                Str *_t4211 = Str_lit("Str", 3ULL);
                (void)_t4211;
                U64 _t4212; { U64 *_hp = (U64 *)Str_size(); _t4212 = *_hp; free(_hp); }
                (void)_t4212;
                U64 _t4213 = 1;
                (void)_t4213;
                Array *_va75 = Array_new(_t4211, &(U64){_t4212}, &(U64){_t4213});
                (void)_va75;
                Str_delete(_t4211, &(Bool){1});
                ;
                ;
                Str *_t4214 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4214;
                Str *_t4215 = Str_concat(_t4214, import_path);
                (void)_t4215;
                Str_delete(_t4214, &(Bool){1});
                Str *_t4216 = Str_lit("' (from ", 8ULL);
                (void)_t4216;
                Str *_t4217 = Str_concat(_t4215, _t4216);
                (void)_t4217;
                Str_delete(_t4215, &(Bool){1});
                Str_delete(_t4216, &(Bool){1});
                Str *_t4218 = Str_concat(_t4217, base_dir);
                (void)_t4218;
                Str_delete(_t4217, &(Bool){1});
                Str *_t4219 = Str_lit("/)", 2ULL);
                (void)_t4219;
                U64 _t4220 = 0;
                (void)_t4220;
                Str *_t4221 = Str_concat(_t4218, _t4219);
                (void)_t4221;
                Str_delete(_t4218, &(Bool){1});
                Str_delete(_t4219, &(Bool){1});
                Array_set(_va75, &(U64){_t4220}, _t4221);
                ;
                println(_va75);
                I64 _t4222 = 1;
                (void)_t4222;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4207, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4222; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4250; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4250 = *_hp; free(_hp); }
            (void)_t4250;
            if (_t4250) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4251 = Str_clone(abs);
            (void)_t4251;
            Set_add(resolved_set, _t4251);
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
            U64 _t4252; { U64 *_hp = (U64 *)Str_len(abs); _t4252 = *_hp; free(_hp); }
            (void)_t4252;
            U64 _t4253 = 1;
            (void)_t4253;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4252, _t4253);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4224 = 0;
                (void)_t4224;
                U8 *_t4225 = Str_get(abs, last_slash);
                (void)_t4225;
                U8 _t4226 = 47;
                (void)_t4226;
                Bool _t4227; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4224}); _t4227 = *_hp; free(_hp); }
                (void)_t4227;
                ;
                Bool _t4228; { Bool *_hp = (Bool *)U8_neq(_t4225, &(U8){_t4226}); _t4228 = *_hp; free(_hp); }
                (void)_t4228;
                ;
                Bool _wcond4223 = Bool_and(_t4227, _t4228);
                (void)_wcond4223;
                ;
                ;
                if (_wcond4223) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4229 = 1;
                (void)_t4229;
                U64 _t4230 = U64_sub(DEREF(last_slash), _t4229);
                (void)_t4230;
                ;
                *last_slash = _t4230;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4254; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4254 = *_hp; free(_hp); }
            (void)_t4254;
            U64 _t4255 = 0;
            (void)_t4255;
            Bool _t4256; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4254}, &(U64){_t4255}); _t4256 = *_hp; free(_hp); }
            (void)_t4256;
            ;
            ;
            if (_t4256) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4231 = 0;
                (void)_t4231;
                Bool _t4232; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4231}); _t4232 = *_hp; free(_hp); }
                (void)_t4232;
                ;
                if (_t4232) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4207, &(Bool){1});
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
                U32 _t4234 = expr_nchildren(sub_ast);
                (void)_t4234;
                Bool _wcond4233; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4234}); _wcond4233 = *_hp; free(_hp); }
                (void)_wcond4233;
                ;
                if (_wcond4233) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4235 = 1;
                (void)_t4235;
                U32 _t4236 = U32_add(DEREF(k), _t4235);
                (void)_t4236;
                ;
                *k = _t4236;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4207, &(Bool){1});
        ;
    }
    I64 _t4259 = 0;
    (void)_t4259;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4259; return _r; }
}

void usage(void) {
    Str *_t4260 = Str_lit("Str", 3ULL);
    (void)_t4260;
    U64 _t4261; { U64 *_hp = (U64 *)Str_size(); _t4261 = *_hp; free(_hp); }
    (void)_t4261;
    U64 _t4262 = 1;
    (void)_t4262;
    Array *_va76 = Array_new(_t4260, &(U64){_t4261}, &(U64){_t4262});
    (void)_va76;
    Str_delete(_t4260, &(Bool){1});
    ;
    ;
    U64 _t4263 = 0;
    (void)_t4263;
    Str *_t4264 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4264;
    Array_set(_va76, &(U64){_t4263}, _t4264);
    ;
    println(_va76);
    Str *_t4265 = Str_lit("Str", 3ULL);
    (void)_t4265;
    U64 _t4266; { U64 *_hp = (U64 *)Str_size(); _t4266 = *_hp; free(_hp); }
    (void)_t4266;
    U64 _t4267 = 1;
    (void)_t4267;
    Array *_va77 = Array_new(_t4265, &(U64){_t4266}, &(U64){_t4267});
    (void)_va77;
    Str_delete(_t4265, &(Bool){1});
    ;
    ;
    U64 _t4268 = 0;
    (void)_t4268;
    Str *_t4269 = Str_lit("", 0ULL);
    (void)_t4269;
    Array_set(_va77, &(U64){_t4268}, _t4269);
    ;
    println(_va77);
    Str *_t4270 = Str_lit("Str", 3ULL);
    (void)_t4270;
    U64 _t4271; { U64 *_hp = (U64 *)Str_size(); _t4271 = *_hp; free(_hp); }
    (void)_t4271;
    U64 _t4272 = 1;
    (void)_t4272;
    Array *_va78 = Array_new(_t4270, &(U64){_t4271}, &(U64){_t4272});
    (void)_va78;
    Str_delete(_t4270, &(Bool){1});
    ;
    ;
    U64 _t4273 = 0;
    (void)_t4273;
    Str *_t4274 = Str_lit("Commands:", 9ULL);
    (void)_t4274;
    Array_set(_va78, &(U64){_t4273}, _t4274);
    ;
    println(_va78);
    Str *_t4275 = Str_lit("Str", 3ULL);
    (void)_t4275;
    U64 _t4276; { U64 *_hp = (U64 *)Str_size(); _t4276 = *_hp; free(_hp); }
    (void)_t4276;
    U64 _t4277 = 1;
    (void)_t4277;
    Array *_va79 = Array_new(_t4275, &(U64){_t4276}, &(U64){_t4277});
    (void)_va79;
    Str_delete(_t4275, &(Bool){1});
    ;
    ;
    U64 _t4278 = 0;
    (void)_t4278;
    Str *_t4279 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4279;
    Array_set(_va79, &(U64){_t4278}, _t4279);
    ;
    println(_va79);
    Str *_t4280 = Str_lit("Str", 3ULL);
    (void)_t4280;
    U64 _t4281; { U64 *_hp = (U64 *)Str_size(); _t4281 = *_hp; free(_hp); }
    (void)_t4281;
    U64 _t4282 = 1;
    (void)_t4282;
    Array *_va80 = Array_new(_t4280, &(U64){_t4281}, &(U64){_t4282});
    (void)_va80;
    Str_delete(_t4280, &(Bool){1});
    ;
    ;
    U64 _t4283 = 0;
    (void)_t4283;
    Str *_t4284 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4284;
    Array_set(_va80, &(U64){_t4283}, _t4284);
    ;
    println(_va80);
    Str *_t4285 = Str_lit("Str", 3ULL);
    (void)_t4285;
    U64 _t4286; { U64 *_hp = (U64 *)Str_size(); _t4286 = *_hp; free(_hp); }
    (void)_t4286;
    U64 _t4287 = 1;
    (void)_t4287;
    Array *_va81 = Array_new(_t4285, &(U64){_t4286}, &(U64){_t4287});
    (void)_va81;
    Str_delete(_t4285, &(Bool){1});
    ;
    ;
    U64 _t4288 = 0;
    (void)_t4288;
    Str *_t4289 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4289;
    Array_set(_va81, &(U64){_t4288}, _t4289);
    ;
    println(_va81);
    Str *_t4290 = Str_lit("Str", 3ULL);
    (void)_t4290;
    U64 _t4291; { U64 *_hp = (U64 *)Str_size(); _t4291 = *_hp; free(_hp); }
    (void)_t4291;
    U64 _t4292 = 1;
    (void)_t4292;
    Array *_va82 = Array_new(_t4290, &(U64){_t4291}, &(U64){_t4292});
    (void)_va82;
    Str_delete(_t4290, &(Bool){1});
    ;
    ;
    U64 _t4293 = 0;
    (void)_t4293;
    Str *_t4294 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4294;
    Array_set(_va82, &(U64){_t4293}, _t4294);
    ;
    println(_va82);
    Str *_t4295 = Str_lit("Str", 3ULL);
    (void)_t4295;
    U64 _t4296; { U64 *_hp = (U64 *)Str_size(); _t4296 = *_hp; free(_hp); }
    (void)_t4296;
    U64 _t4297 = 1;
    (void)_t4297;
    Array *_va83 = Array_new(_t4295, &(U64){_t4296}, &(U64){_t4297});
    (void)_va83;
    Str_delete(_t4295, &(Bool){1});
    ;
    ;
    U64 _t4298 = 0;
    (void)_t4298;
    Str *_t4299 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4299;
    Array_set(_va83, &(U64){_t4298}, _t4299);
    ;
    println(_va83);
    Str *_t4300 = Str_lit("Str", 3ULL);
    (void)_t4300;
    U64 _t4301; { U64 *_hp = (U64 *)Str_size(); _t4301 = *_hp; free(_hp); }
    (void)_t4301;
    U64 _t4302 = 1;
    (void)_t4302;
    Array *_va84 = Array_new(_t4300, &(U64){_t4301}, &(U64){_t4302});
    (void)_va84;
    Str_delete(_t4300, &(Bool){1});
    ;
    ;
    U64 _t4303 = 0;
    (void)_t4303;
    Str *_t4304 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4304;
    Array_set(_va84, &(U64){_t4303}, _t4304);
    ;
    println(_va84);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4310 = 1;
    (void)_t4310;
    e->is_core = _t4310;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4306 = expr_nchildren(e);
        (void)_t4306;
        Bool _wcond4305; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4306}); _wcond4305 = *_hp; free(_hp); }
        (void)_wcond4305;
        ;
        if (_wcond4305) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4307 = expr_get_child(e, DEREF(i));
        (void)_t4307;
        mark_core(_t4307);
        U32 _t4308 = 1;
        (void)_t4308;
        U32 _t4309 = U32_add(DEREF(i), _t4308);
        (void)_t4309;
        ;
        *i = _t4309;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4770 = malloc(sizeof(I64));
    *_t4770 = 0;
    (void)_t4770;
    _t4771 = malloc(sizeof(I64));
    *_t4771 = 1;
    (void)_t4771;
    _t4772 = malloc(sizeof(I64)); *_t4772 = I64_sub(DEREF(_t4770), DEREF(_t4771));
    (void)_t4772;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4772));
    (void)CAP_LIT;
    _t4773 = malloc(sizeof(I64));
    *_t4773 = 0;
    (void)_t4773;
    _t4774 = malloc(sizeof(I64));
    *_t4774 = 2;
    (void)_t4774;
    _t4775 = malloc(sizeof(I64)); *_t4775 = I64_sub(DEREF(_t4773), DEREF(_t4774));
    (void)_t4775;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4775));
    (void)CAP_VIEW;
    _t4776 = Str_lit("Str", 3ULL);
    (void)_t4776;
    _t4777 = Str_size();
    (void)_t4777;
    _t4778 = Str_lit("Mode", 4ULL);
    (void)_t4778;
    _t4779 = Mode_size();
    (void)_t4779;
    core_modes = Map_new(_t4776, _t4777, _t4778, _t4779);
    (void)core_modes;
    _t4780 = malloc(sizeof(Bool));
    *_t4780 = 0;
    (void)_t4780;
    _t4781 = malloc(sizeof(Bool));
    *_t4781 = 0;
    (void)_t4781;
    _t4782 = malloc(sizeof(Bool));
    *_t4782 = 0;
    (void)_t4782;
    _t4783 = malloc(sizeof(Bool));
    *_t4783 = 0;
    (void)_t4783;
    _t4784 = Str_lit("script", 6ULL);
    (void)_t4784;
    _t4785 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4785->name = *_ca; free(_ca); }
    _t4785->needs_main = DEREF(_t4780);
    _t4785->decls_only = DEREF(_t4781);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4785->auto_import = *_ca; free(_ca); }
    _t4785->is_pure = DEREF(_t4782);
    _t4785->debug_prints = DEREF(_t4783);
    (void)_t4785;
    _t4786 = malloc(sizeof(Bool));
    *_t4786 = 1;
    (void)_t4786;
    _t4787 = malloc(sizeof(Bool));
    *_t4787 = 1;
    (void)_t4787;
    _t4788 = malloc(sizeof(Bool));
    *_t4788 = 0;
    (void)_t4788;
    _t4789 = malloc(sizeof(Bool));
    *_t4789 = 0;
    (void)_t4789;
    _t4790 = Str_lit("cli", 3ULL);
    (void)_t4790;
    _t4791 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4791->name = *_ca; free(_ca); }
    _t4791->needs_main = DEREF(_t4786);
    _t4791->decls_only = DEREF(_t4787);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4791->auto_import = *_ca; free(_ca); }
    _t4791->is_pure = DEREF(_t4788);
    _t4791->debug_prints = DEREF(_t4789);
    (void)_t4791;
    _t4792 = malloc(sizeof(Bool));
    *_t4792 = 1;
    (void)_t4792;
    _t4793 = malloc(sizeof(Bool));
    *_t4793 = 1;
    (void)_t4793;
    _t4794 = malloc(sizeof(Bool));
    *_t4794 = 0;
    (void)_t4794;
    _t4795 = malloc(sizeof(Bool));
    *_t4795 = 0;
    (void)_t4795;
    _t4796 = Str_lit("gui", 3ULL);
    (void)_t4796;
    _t4797 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4797->name = *_ca; free(_ca); }
    _t4797->needs_main = DEREF(_t4792);
    _t4797->decls_only = DEREF(_t4793);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4797->auto_import = *_ca; free(_ca); }
    _t4797->is_pure = DEREF(_t4794);
    _t4797->debug_prints = DEREF(_t4795);
    (void)_t4797;
    _t4798 = malloc(sizeof(Bool));
    *_t4798 = 0;
    (void)_t4798;
    _t4799 = malloc(sizeof(Bool));
    *_t4799 = 1;
    (void)_t4799;
    _t4800 = malloc(sizeof(Bool));
    *_t4800 = 0;
    (void)_t4800;
    _t4801 = malloc(sizeof(Bool));
    *_t4801 = 0;
    (void)_t4801;
    _t4802 = Str_lit("test", 4ULL);
    (void)_t4802;
    _t4803 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4803->name = *_ca; free(_ca); }
    _t4803->needs_main = DEREF(_t4798);
    _t4803->decls_only = DEREF(_t4799);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4803->auto_import = *_ca; free(_ca); }
    _t4803->is_pure = DEREF(_t4800);
    _t4803->debug_prints = DEREF(_t4801);
    (void)_t4803;
    _t4804 = malloc(sizeof(Bool));
    *_t4804 = 0;
    (void)_t4804;
    _t4805 = malloc(sizeof(Bool));
    *_t4805 = 1;
    (void)_t4805;
    _t4806 = malloc(sizeof(Bool));
    *_t4806 = 1;
    (void)_t4806;
    _t4807 = malloc(sizeof(Bool));
    *_t4807 = 0;
    (void)_t4807;
    _t4808 = Str_lit("pure", 4ULL);
    (void)_t4808;
    _t4809 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4809->name = *_ca; free(_ca); }
    _t4809->needs_main = DEREF(_t4804);
    _t4809->decls_only = DEREF(_t4805);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4809->auto_import = *_ca; free(_ca); }
    _t4809->is_pure = DEREF(_t4806);
    _t4809->debug_prints = DEREF(_t4807);
    (void)_t4809;
    _t4810 = malloc(sizeof(Bool));
    *_t4810 = 0;
    (void)_t4810;
    _t4811 = malloc(sizeof(Bool));
    *_t4811 = 1;
    (void)_t4811;
    _t4812 = malloc(sizeof(Bool));
    *_t4812 = 1;
    (void)_t4812;
    _t4813 = malloc(sizeof(Bool));
    *_t4813 = 1;
    (void)_t4813;
    _t4814 = Str_lit("pura", 4ULL);
    (void)_t4814;
    _t4815 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4815->name = *_ca; free(_ca); }
    _t4815->needs_main = DEREF(_t4810);
    _t4815->decls_only = DEREF(_t4811);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4815->auto_import = *_ca; free(_ca); }
    _t4815->is_pure = DEREF(_t4812);
    _t4815->debug_prints = DEREF(_t4813);
    (void)_t4815;
    _t4816 = malloc(sizeof(Bool));
    *_t4816 = 0;
    (void)_t4816;
    _t4817 = malloc(sizeof(Bool));
    *_t4817 = 1;
    (void)_t4817;
    _t4818 = malloc(sizeof(Bool));
    *_t4818 = 0;
    (void)_t4818;
    _t4819 = malloc(sizeof(Bool));
    *_t4819 = 0;
    (void)_t4819;
    _t4820 = Str_lit("lib", 3ULL);
    (void)_t4820;
    _t4821 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4821->name = *_ca; free(_ca); }
    _t4821->needs_main = DEREF(_t4816);
    _t4821->decls_only = DEREF(_t4817);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4821->auto_import = *_ca; free(_ca); }
    _t4821->is_pure = DEREF(_t4818);
    _t4821->debug_prints = DEREF(_t4819);
    (void)_t4821;
    _t4822 = malloc(sizeof(Bool));
    *_t4822 = 0;
    (void)_t4822;
    _t4823 = malloc(sizeof(Bool));
    *_t4823 = 1;
    (void)_t4823;
    _t4824 = malloc(sizeof(Bool));
    *_t4824 = 0;
    (void)_t4824;
    _t4825 = malloc(sizeof(Bool));
    *_t4825 = 1;
    (void)_t4825;
    _t4826 = Str_lit("liba", 4ULL);
    (void)_t4826;
    _t4827 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4827->name = *_ca; free(_ca); }
    _t4827->needs_main = DEREF(_t4822);
    _t4827->decls_only = DEREF(_t4823);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4827->auto_import = *_ca; free(_ca); }
    _t4827->is_pure = DEREF(_t4824);
    _t4827->debug_prints = DEREF(_t4825);
    (void)_t4827;
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
    U64 _t4690; { U64 *_hp = (U64 *)Array_len(args); _t4690 = *_hp; free(_hp); }
    (void)_t4690;
    U64 _t4691 = 0;
    (void)_t4691;
    Bool _t4692 = U64_eq(_t4690, _t4691);
    (void)_t4692;
    ;
    ;
    if (_t4692) {
        usage();
        Str *_t4311 = Str_lit("Str", 3ULL);
        (void)_t4311;
        U64 _t4312; { U64 *_hp = (U64 *)Str_size(); _t4312 = *_hp; free(_hp); }
        (void)_t4312;
        U64 _t4313 = 1;
        (void)_t4313;
        Array *_va85 = Array_new(_t4311, &(U64){_t4312}, &(U64){_t4313});
        (void)_va85;
        Str_delete(_t4311, &(Bool){1});
        ;
        ;
        U64 _t4314 = 0;
        (void)_t4314;
        Str *_t4315 = Str_lit("no arguments", 12ULL);
        (void)_t4315;
        Array_set(_va85, &(U64){_t4314}, _t4315);
        ;
        Str *_t4316 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4316;
        panic(_t4316, _va85);
        Str_delete(_t4316, &(Bool){1});
    }
    ;
    U64 *_t4693 = malloc(sizeof(U64));
    *_t4693 = 0;
    (void)_t4693;
    Str *cmd_ref = Array_get(args, _t4693);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4693, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4694; { U64 *_hp = (U64 *)Array_len(args); _t4694 = *_hp; free(_hp); }
    (void)_t4694;
    U64 _t4695 = 1;
    (void)_t4695;
    Bool _t4696 = U64_eq(_t4694, _t4695);
    (void)_t4696;
    ;
    ;
    if (_t4696) {
        Str *_t4317 = Str_lit("help", 4ULL);
        (void)_t4317;
        Str *_t4318 = Str_lit("--help", 6ULL);
        (void)_t4318;
        Bool _t4319; { Bool *_hp = (Bool *)Str_eq(command, _t4317); _t4319 = *_hp; free(_hp); }
        (void)_t4319;
        Str_delete(_t4317, &(Bool){1});
        Bool _t4320; { Bool *_hp = (Bool *)Str_eq(command, _t4318); _t4320 = *_hp; free(_hp); }
        (void)_t4320;
        Str_delete(_t4318, &(Bool){1});
        Bool _t4321 = Bool_or(_t4319, _t4320);
        (void)_t4321;
        ;
        ;
        if (_t4321) {
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
            U64 _t4338; { U64 *_hp = (U64 *)Array_len(args); _t4338 = *_hp; free(_hp); }
            (void)_t4338;
            Bool _wcond4322; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4338}); _wcond4322 = *_hp; free(_hp); }
            (void)_wcond4322;
            ;
            if (_wcond4322) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4339 = Str_lit("-o", 2ULL);
            (void)_t4339;
            U64 _t4340 = 1;
            (void)_t4340;
            U64 _t4341 = U64_add(DEREF(path_idx), _t4340);
            (void)_t4341;
            ;
            U64 _t4342; { U64 *_hp = (U64 *)Array_len(args); _t4342 = *_hp; free(_hp); }
            (void)_t4342;
            Bool _t4343; { Bool *_hp = (Bool *)Str_eq(flag, _t4339); _t4343 = *_hp; free(_hp); }
            (void)_t4343;
            Str_delete(_t4339, &(Bool){1});
            Bool _t4344; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4341}, &(U64){_t4342}); _t4344 = *_hp; free(_hp); }
            (void)_t4344;
            ;
            ;
            Bool _t4345 = Bool_and(_t4343, _t4344);
            (void)_t4345;
            ;
            ;
            if (_t4345) {
                U64 _t4323 = 1;
                (void)_t4323;
                U64 *_t4324 = malloc(sizeof(U64)); *_t4324 = U64_add(DEREF(path_idx), _t4323);
                (void)_t4324;
                ;
                Str *oval = Array_get(args, _t4324);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4324, &(Bool){1});
                U64 _t4325 = 2;
                (void)_t4325;
                U64 _t4326 = U64_add(DEREF(path_idx), _t4325);
                (void)_t4326;
                ;
                *path_idx = _t4326;
                ;
            } else {
                Str *_t4331 = Str_lit("-c", 2ULL);
                (void)_t4331;
                U64 _t4332 = 1;
                (void)_t4332;
                U64 _t4333 = U64_add(DEREF(path_idx), _t4332);
                (void)_t4333;
                ;
                U64 _t4334; { U64 *_hp = (U64 *)Array_len(args); _t4334 = *_hp; free(_hp); }
                (void)_t4334;
                Bool _t4335; { Bool *_hp = (Bool *)Str_eq(flag, _t4331); _t4335 = *_hp; free(_hp); }
                (void)_t4335;
                Str_delete(_t4331, &(Bool){1});
                Bool _t4336; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4333}, &(U64){_t4334}); _t4336 = *_hp; free(_hp); }
                (void)_t4336;
                ;
                ;
                Bool _t4337 = Bool_and(_t4335, _t4336);
                (void)_t4337;
                ;
                ;
                if (_t4337) {
                    U64 _t4327 = 1;
                    (void)_t4327;
                    U64 *_t4328 = malloc(sizeof(U64)); *_t4328 = U64_add(DEREF(path_idx), _t4327);
                    (void)_t4328;
                    ;
                    Str *cval = Array_get(args, _t4328);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4328, &(Bool){1});
                    U64 _t4329 = 2;
                    (void)_t4329;
                    U64 _t4330 = U64_add(DEREF(path_idx), _t4329);
                    (void)_t4330;
                    ;
                    *path_idx = _t4330;
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
    Str *_t4697 = Str_lit("help", 4ULL);
    (void)_t4697;
    Str *_t4698 = Str_lit("--help", 6ULL);
    (void)_t4698;
    Bool _t4699; { Bool *_hp = (Bool *)Str_eq(command, _t4697); _t4699 = *_hp; free(_hp); }
    (void)_t4699;
    Str_delete(_t4697, &(Bool){1});
    Bool _t4700; { Bool *_hp = (Bool *)Str_eq(command, _t4698); _t4700 = *_hp; free(_hp); }
    (void)_t4700;
    Str_delete(_t4698, &(Bool){1});
    Bool _t4701 = Bool_or(_t4699, _t4700);
    (void)_t4701;
    ;
    ;
    if (_t4701) {
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
    Str *_t4702 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4702;
    Str *core_path = Str_concat(bin_dir, _t4702);
    (void)core_path;
    Str_delete(_t4702, &(Bool){1});
    Str *_t4703 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4703;
    Str *ext_c_path = Str_concat(bin_dir, _t4703);
    (void)ext_c_path;
    Str_delete(_t4703, &(Bool){1});
    Str *_t4704 = Str_lit("Str", 3ULL);
    (void)_t4704;
    U64 _t4705; { U64 *_hp = (U64 *)Str_size(); _t4705 = *_hp; free(_hp); }
    (void)_t4705;
    Set *resolved = Set_new(_t4704, &(U64){_t4705});
    (void)resolved;
    Str_delete(_t4704, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4706; { U64 *_hp = (U64 *)Str_len(abs_path); _t4706 = *_hp; free(_hp); }
    (void)_t4706;
    U64 _t4707 = 0;
    (void)_t4707;
    Bool _t4708; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4706}, &(U64){_t4707}); _t4708 = *_hp; free(_hp); }
    (void)_t4708;
    ;
    ;
    if (_t4708) {
        U64 _t4354; { U64 *_hp = (U64 *)Str_len(abs_path); _t4354 = *_hp; free(_hp); }
        (void)_t4354;
        U64 _t4355 = 1;
        (void)_t4355;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4354, _t4355);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4347 = 0;
            (void)_t4347;
            U8 *_t4348 = Str_get(abs_path, last_slash);
            (void)_t4348;
            U8 _t4349 = 47;
            (void)_t4349;
            Bool _t4350; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4347}); _t4350 = *_hp; free(_hp); }
            (void)_t4350;
            ;
            Bool _t4351; { Bool *_hp = (Bool *)U8_neq(_t4348, &(U8){_t4349}); _t4351 = *_hp; free(_hp); }
            (void)_t4351;
            ;
            Bool _wcond4346 = Bool_and(_t4350, _t4351);
            (void)_wcond4346;
            ;
            ;
            if (_wcond4346) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4352 = 1;
            (void)_t4352;
            U64 _t4353 = U64_sub(DEREF(last_slash), _t4352);
            (void)_t4353;
            ;
            *last_slash = _t4353;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4356 = Str_clone(abs_path);
        (void)_t4356;
        Set_add(resolved, _t4356);
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
    U64 _t4709; { U64 *_hp = (U64 *)Str_len(core_abs); _t4709 = *_hp; free(_hp); }
    (void)_t4709;
    U64 _t4710 = 0;
    (void)_t4710;
    Bool _t4711; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4709}, &(U64){_t4710}); _t4711 = *_hp; free(_hp); }
    (void)_t4711;
    ;
    ;
    if (_t4711) {
        Bool _t4358; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4358 = *_hp; free(_hp); }
        (void)_t4358;
        if (_t4358) {
            Bool _t4357 = 1;
            (void)_t4357;
            skip_core = _t4357;
            ;
        }
        ;
        Str *_t4359 = Str_clone(core_abs);
        (void)_t4359;
        Set_add(resolved, _t4359);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4712; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4712 = *_hp; free(_hp); }
    (void)_t4712;
    U64 _t4713 = 0;
    (void)_t4713;
    Bool _t4714; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4712}, &(U64){_t4713}); _t4714 = *_hp; free(_hp); }
    (void)_t4714;
    ;
    ;
    Bool _t4715 = Bool_not(skip_core);
    (void)_t4715;
    Bool _t4716 = Bool_and(_t4714, _t4715);
    (void)_t4716;
    ;
    ;
    if (_t4716) {
        Str *_t4366 = Str_lit("/src/core", 9ULL);
        (void)_t4366;
        Str *core_dir = Str_concat(bin_dir, _t4366);
        (void)core_dir;
        Str_delete(_t4366, &(Bool){1});
        Str *_t4367 = Str_lit("", 0ULL);
        (void)_t4367;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4367); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4367, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4368 = 0;
        (void)_t4368;
        Bool _t4369; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4368}); _t4369 = *_hp; free(_hp); }
        (void)_t4369;
        ;
        ;
        if (_t4369) {
            Str *_t4360 = Str_lit("Str", 3ULL);
            (void)_t4360;
            U64 _t4361; { U64 *_hp = (U64 *)Str_size(); _t4361 = *_hp; free(_hp); }
            (void)_t4361;
            U64 _t4362 = 1;
            (void)_t4362;
            Array *_va86 = Array_new(_t4360, &(U64){_t4361}, &(U64){_t4362});
            (void)_va86;
            Str_delete(_t4360, &(Bool){1});
            ;
            ;
            U64 _t4363 = 0;
            (void)_t4363;
            Str *_t4364 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4364;
            Array_set(_va86, &(U64){_t4363}, _t4364);
            ;
            Str *_t4365 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4365;
            panic(_t4365, _va86);
            Str_delete(_t4365, &(Bool){1});
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
    Str *_t4717 = Str_lit("script", 6ULL);
    (void)_t4717;
    Mode *cur_mode = mode_resolve(_t4717);
    (void)cur_mode;
    Str_delete(_t4717, &(Bool){1});
    U64 _t4718; { U64 *_hp = (U64 *)Str_len(mode_str); _t4718 = *_hp; free(_hp); }
    (void)_t4718;
    U64 _t4719 = 0;
    (void)_t4719;
    Bool _t4720; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4718}, &(U64){_t4719}); _t4720 = *_hp; free(_hp); }
    (void)_t4720;
    ;
    ;
    if (_t4720) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4379; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4379 = *_hp; free(_hp); }
        (void)_t4379;
        U64 _t4380 = 0;
        (void)_t4380;
        Bool _t4381 = U64_eq(_t4379, _t4380);
        (void)_t4381;
        ;
        ;
        if (_t4381) {
            Str *_t4370 = Str_lit("Str", 3ULL);
            (void)_t4370;
            U64 _t4371; { U64 *_hp = (U64 *)Str_size(); _t4371 = *_hp; free(_hp); }
            (void)_t4371;
            U64 _t4372 = 1;
            (void)_t4372;
            Array *_va87 = Array_new(_t4370, &(U64){_t4371}, &(U64){_t4372});
            (void)_va87;
            Str_delete(_t4370, &(Bool){1});
            ;
            ;
            Str *_t4373 = Str_lit("unknown mode '", 14ULL);
            (void)_t4373;
            Str *_t4374 = Str_concat(_t4373, mode_str);
            (void)_t4374;
            Str_delete(_t4373, &(Bool){1});
            Str *_t4375 = Str_lit("'", 1ULL);
            (void)_t4375;
            U64 _t4376 = 0;
            (void)_t4376;
            Str *_t4377 = Str_concat(_t4374, _t4375);
            (void)_t4377;
            Str_delete(_t4374, &(Bool){1});
            Str_delete(_t4375, &(Bool){1});
            Array_set(_va87, &(U64){_t4376}, _t4377);
            ;
            Str *_t4378 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4378;
            panic(_t4378, _va87);
            Str_delete(_t4378, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4721; { U64 *_hp = (U64 *)Vec_len(imports); _t4721 = *_hp; free(_hp); }
    (void)_t4721;
    U64 _t4722 = 0;
    (void)_t4722;
    Bool _t4723; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4721}, &(U64){_t4722}); _t4723 = *_hp; free(_hp); }
    (void)_t4723;
    ;
    ;
    if (_t4723) {
        Str *_t4388 = Str_lit("/src/lib", 8ULL);
        (void)_t4388;
        Str *lib_dir = Str_concat(bin_dir, _t4388);
        (void)lib_dir;
        Str_delete(_t4388, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4389 = 0;
        (void)_t4389;
        Bool _t4390; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4389}); _t4390 = *_hp; free(_hp); }
        (void)_t4390;
        ;
        ;
        if (_t4390) {
            Str *_t4382 = Str_lit("Str", 3ULL);
            (void)_t4382;
            U64 _t4383; { U64 *_hp = (U64 *)Str_size(); _t4383 = *_hp; free(_hp); }
            (void)_t4383;
            U64 _t4384 = 1;
            (void)_t4384;
            Array *_va88 = Array_new(_t4382, &(U64){_t4383}, &(U64){_t4384});
            (void)_va88;
            Str_delete(_t4382, &(Bool){1});
            ;
            ;
            U64 _t4385 = 0;
            (void)_t4385;
            Str *_t4386 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4386;
            Array_set(_va88, &(U64){_t4385}, _t4386);
            ;
            Str *_t4387 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4387;
            panic(_t4387, _va88);
            Str_delete(_t4387, &(Bool){1});
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
    Bool _t4724 = Bool_not(skip_core);
    (void)_t4724;
    ;
    if (_t4724) {
        while (1) {
            U32 _t4392 = expr_nchildren(core_ast);
            (void)_t4392;
            Bool _wcond4391; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4392}); _wcond4391 = *_hp; free(_hp); }
            (void)_wcond4391;
            ;
            if (_wcond4391) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4393 = 1;
            (void)_t4393;
            U32 _t4394 = U32_add(DEREF(i), _t4393);
            (void)_t4394;
            ;
            *i = _t4394;
            ;
        }
        U32 _t4399 = 0;
        (void)_t4399;
        *i = _t4399;
        ;
        while (1) {
            U32 _t4396 = expr_vec_count(core_import_decls);
            (void)_t4396;
            Bool _wcond4395; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4396}); _wcond4395 = *_hp; free(_hp); }
            (void)_wcond4395;
            ;
            if (_wcond4395) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4397 = 1;
            (void)_t4397;
            U32 _t4398 = U32_add(DEREF(i), _t4397);
            (void)_t4398;
            ;
            *i = _t4398;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4725; { U64 *_hp = (U64 *)Str_len(auto_import); _t4725 = *_hp; free(_hp); }
    (void)_t4725;
    U64 _t4726 = 0;
    (void)_t4726;
    Bool _t4727; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4725}, &(U64){_t4726}); _t4727 = *_hp; free(_hp); }
    (void)_t4727;
    ;
    ;
    if (_t4727) {
        Str *_t4404 = Str_lit("/src/modes/", 11ULL);
        (void)_t4404;
        Str *_t4405 = Str_concat(bin_dir, _t4404);
        (void)_t4405;
        Str_delete(_t4404, &(Bool){1});
        Str *_t4406 = Str_concat(_t4405, auto_import);
        (void)_t4406;
        Str_delete(_t4405, &(Bool){1});
        Str *_t4407 = Str_lit(".til", 4ULL);
        (void)_t4407;
        Str *mode_til_path = Str_concat(_t4406, _t4407);
        (void)mode_til_path;
        Str_delete(_t4406, &(Bool){1});
        Str_delete(_t4407, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4408 = 0;
        (void)_t4408;
        *i = _t4408;
        ;
        while (1) {
            U32 _t4401 = expr_nchildren(mode_ast);
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
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4402 = 1;
            (void)_t4402;
            U32 _t4403 = U32_add(DEREF(i), _t4402);
            (void)_t4403;
            ;
            *i = _t4403;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4728 = 0;
    (void)_t4728;
    *i = _t4728;
    ;
    while (1) {
        U32 _t4410 = expr_vec_count(import_decls);
        (void)_t4410;
        Bool _wcond4409; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4410}); _wcond4409 = *_hp; free(_hp); }
        (void)_wcond4409;
        ;
        if (_wcond4409) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4411 = 1;
        (void)_t4411;
        U32 _t4412 = U32_add(DEREF(i), _t4411);
        (void)_t4412;
        ;
        *i = _t4412;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4729 = 0;
    (void)_t4729;
    *i = _t4729;
    ;
    while (1) {
        U32 _t4414 = expr_nchildren(ast);
        (void)_t4414;
        Bool _wcond4413; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4414}); _wcond4413 = *_hp; free(_hp); }
        (void)_wcond4413;
        ;
        if (_wcond4413) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4415 = 1;
        (void)_t4415;
        U32 _t4416 = U32_add(DEREF(i), _t4415);
        (void)_t4416;
        ;
        *i = _t4416;
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
    U32 _t4730 = 0;
    (void)_t4730;
    *i = _t4730;
    ;
    while (1) {
        U32 _t4432 = expr_nchildren(ast);
        (void)_t4432;
        Bool _wcond4417; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4432}); _wcond4417 = *_hp; free(_hp); }
        (void)_wcond4417;
        ;
        if (_wcond4417) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4433 = expr_get_tag(stmt);
        (void)_t4433;
        U32 _t4434 = expr_nchildren(stmt);
        (void)_t4434;
        U32 _t4435 = 2;
        (void)_t4435;
        Bool _t4436 = I32_eq(_t4433, DEREF(NODE_FCALL));
        (void)_t4436;
        ;
        Bool _t4437 = U32_eq(_t4434, _t4435);
        (void)_t4437;
        ;
        ;
        U32 *_t4438 = malloc(sizeof(U32));
        *_t4438 = 0;
        (void)_t4438;
        Expr *_t4439 = expr_get_child(stmt, DEREF(_t4438));
        (void)_t4439;
        I32 _t4440 = expr_get_tag(_t4439);
        (void)_t4440;
        U32_delete(_t4438, &(Bool){1});
        Bool _t4441 = Bool_and(_t4436, _t4437);
        (void)_t4441;
        ;
        ;
        Bool _t4442 = I32_eq(_t4440, DEREF(NODE_IDENT));
        (void)_t4442;
        ;
        U32 *_t4443 = malloc(sizeof(U32));
        *_t4443 = 1;
        (void)_t4443;
        Expr *_t4444 = expr_get_child(stmt, DEREF(_t4443));
        (void)_t4444;
        I32 _t4445 = expr_get_tag(_t4444);
        (void)_t4445;
        U32_delete(_t4443, &(Bool){1});
        Bool _t4446 = Bool_and(_t4441, _t4442);
        (void)_t4446;
        ;
        ;
        Bool _t4447 = I32_eq(_t4445, DEREF(NODE_LITERAL_STR));
        (void)_t4447;
        ;
        Bool _t4448 = Bool_and(_t4446, _t4447);
        (void)_t4448;
        ;
        ;
        if (_t4448) {
            U32 *_t4426 = malloc(sizeof(U32));
            *_t4426 = 0;
            (void)_t4426;
            Expr *_t4427 = expr_get_child(stmt, DEREF(_t4426));
            (void)_t4427;
            Str *fname = expr_get_str_val(_t4427);
            (void)fname;
            U32 *_t4428 = malloc(sizeof(U32));
            *_t4428 = 1;
            (void)_t4428;
            Expr *_t4429 = expr_get_child(stmt, DEREF(_t4428));
            (void)_t4429;
            Str *arg = expr_get_str_val(_t4429);
            (void)arg;
            Str *_t4430 = Str_lit("link", 4ULL);
            (void)_t4430;
            Bool _t4431; { Bool *_hp = (Bool *)Str_eq(fname, _t4430); _t4431 = *_hp; free(_hp); }
            (void)_t4431;
            Str_delete(_t4430, &(Bool){1});
            if (_t4431) {
                Str *_t4418 = Str_lit(" -l", 3ULL);
                (void)_t4418;
                Str *_t4419 = Str_concat(link_flags, _t4418);
                (void)_t4419;
                Str_delete(_t4418, &(Bool){1});
                link_flags = Str_concat(_t4419, arg);
                Str_delete(_t4419, &(Bool){1});
            } else {
                Str *_t4424 = Str_lit("link_c", 6ULL);
                (void)_t4424;
                Bool _t4425; { Bool *_hp = (Bool *)Str_eq(fname, _t4424); _t4425 = *_hp; free(_hp); }
                (void)_t4425;
                Str_delete(_t4424, &(Bool){1});
                if (_t4425) {
                    U64 _t4421; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4421 = *_hp; free(_hp); }
                    (void)_t4421;
                    U64 _t4422 = 0;
                    (void)_t4422;
                    Bool _t4423; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4421}, &(U64){_t4422}); _t4423 = *_hp; free(_hp); }
                    (void)_t4423;
                    ;
                    ;
                    if (_t4423) {
                        Str *_t4420 = Str_lit(" ", 1ULL);
                        (void)_t4420;
                        link_c_paths = Str_concat(link_c_paths, _t4420);
                        Str_delete(_t4420, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4426, &(Bool){1});
            U32_delete(_t4428, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4449 = 1;
        (void)_t4449;
        U32 _t4450 = U32_add(DEREF(i), _t4449);
        (void)_t4450;
        ;
        *i = _t4450;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4731 = init_declarations(ast, scope);
    (void)_t4731;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4732 = 0;
    (void)_t4732;
    Bool _t4733; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4732}); _t4733 = *_hp; free(_hp); }
    (void)_t4733;
    ;
    if (_t4733) {
        Str *_t4451 = Str_lit("Str", 3ULL);
        (void)_t4451;
        U64 _t4452; { U64 *_hp = (U64 *)Str_size(); _t4452 = *_hp; free(_hp); }
        (void)_t4452;
        U64 _t4453 = 1;
        (void)_t4453;
        Array *_va89 = Array_new(_t4451, &(U64){_t4452}, &(U64){_t4453});
        (void)_va89;
        Str_delete(_t4451, &(Bool){1});
        ;
        ;
        Str *_t4454 = I32_to_str(&(I32){type_errors});
        (void)_t4454;
        Str *_t4455 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4455;
        U64 _t4456 = 0;
        (void)_t4456;
        Str *_t4457 = Str_concat(_t4454, _t4455);
        (void)_t4457;
        Str_delete(_t4454, &(Bool){1});
        Str_delete(_t4455, &(Bool){1});
        Array_set(_va89, &(U64){_t4456}, _t4457);
        ;
        Str *_t4458 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4458;
        panic(_t4458, _va89);
        Str_delete(_t4458, &(Bool){1});
    }
    ;
    ;
    Str *_t4734 = Str_lit("test", 4ULL);
    (void)_t4734;
    Str *_t4735 = Str_lit("test", 4ULL);
    (void)_t4735;
    Bool _t4736; { Bool *_hp = (Bool *)Str_eq(command, _t4734); _t4736 = *_hp; free(_hp); }
    (void)_t4736;
    Str_delete(_t4734, &(Bool){1});
    Bool _t4737; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4735); _t4737 = *_hp; free(_hp); }
    (void)_t4737;
    Str_delete(_t4735, &(Bool){1});
    Str *_t4738 = Str_lit("pure", 4ULL);
    (void)_t4738;
    Bool _t4739 = Bool_or(_t4736, _t4737);
    (void)_t4739;
    ;
    ;
    Bool _t4740; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4738); _t4740 = *_hp; free(_hp); }
    (void)_t4740;
    Str_delete(_t4738, &(Bool){1});
    Str *_t4741 = Str_lit("pura", 4ULL);
    (void)_t4741;
    Bool _t4742 = Bool_or(_t4739, _t4740);
    (void)_t4742;
    ;
    ;
    Bool _t4743; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4741); _t4743 = *_hp; free(_hp); }
    (void)_t4743;
    Str_delete(_t4741, &(Bool){1});
    Bool run_tests = Bool_or(_t4742, _t4743);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4744 = Str_lit("translate", 9ULL);
    (void)_t4744;
    Str *_t4745 = Str_lit("build", 5ULL);
    (void)_t4745;
    Bool _t4746; { Bool *_hp = (Bool *)Str_eq(command, _t4744); _t4746 = *_hp; free(_hp); }
    (void)_t4746;
    Str_delete(_t4744, &(Bool){1});
    Bool _t4747; { Bool *_hp = (Bool *)Str_eq(command, _t4745); _t4747 = *_hp; free(_hp); }
    (void)_t4747;
    Str_delete(_t4745, &(Bool){1});
    Bool _t4748; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4748 = *_hp; free(_hp); }
    (void)_t4748;
    Bool _t4749 = Bool_or(_t4746, _t4747);
    (void)_t4749;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4748, _t4749);
    (void)is_lib_target;
    ;
    ;
    U64 _t4750; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4750 = *_hp; free(_hp); }
    (void)_t4750;
    U64 _t4751 = 0;
    (void)_t4751;
    Bool _t4752 = Bool_not(is_lib_target);
    (void)_t4752;
    ;
    Bool _t4753 = U64_eq(_t4750, _t4751);
    (void)_t4753;
    ;
    ;
    Bool _t4754 = Bool_and(_t4752, _t4753);
    (void)_t4754;
    ;
    ;
    if (_t4754) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4755; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4755 = *_hp; free(_hp); }
    (void)_t4755;
    U64 _t4756 = 0;
    (void)_t4756;
    Bool _t4757; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4755}, &(U64){_t4756}); _t4757 = *_hp; free(_hp); }
    (void)_t4757;
    ;
    ;
    if (_t4757) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4758 = Str_lit("Str", 3ULL);
    (void)_t4758;
    U64 _t4759; { U64 *_hp = (U64 *)Str_size(); _t4759 = *_hp; free(_hp); }
    (void)_t4759;
    Vec *user_argv = Vec_new(_t4758, &(U64){_t4759});
    (void)user_argv;
    Str_delete(_t4758, &(Bool){1});
    ;
    U64 _t4760 = 1;
    (void)_t4760;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4760);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4475; { U64 *_hp = (U64 *)Array_len(args); _t4475 = *_hp; free(_hp); }
        (void)_t4475;
        Bool _wcond4459; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4475}); _wcond4459 = *_hp; free(_hp); }
        (void)_wcond4459;
        ;
        if (_wcond4459) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4476 = Str_lit("-l", 2ULL);
        (void)_t4476;
        Bool _t4477; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4476); _t4477 = *_hp; free(_hp); }
        (void)_t4477;
        Str_delete(_t4476, &(Bool){1});
        if (_t4477) {
            U64 _t4462 = 2;
            (void)_t4462;
            U64 _t4463; { U64 *_hp = (U64 *)Str_len(arg); _t4463 = *_hp; free(_hp); }
            (void)_t4463;
            Str *lib = Str_substr(arg, &(U64){_t4462}, &(U64){_t4463});
            (void)lib;
            ;
            ;
            U64 _t4464; { U64 *_hp = (U64 *)Str_len(lib); _t4464 = *_hp; free(_hp); }
            (void)_t4464;
            U64 _t4465 = 0;
            (void)_t4465;
            U64 _t4466 = 1;
            (void)_t4466;
            U64 _t4467 = U64_add(DEREF(ai), _t4466);
            (void)_t4467;
            ;
            U64 _t4468; { U64 *_hp = (U64 *)Array_len(args); _t4468 = *_hp; free(_hp); }
            (void)_t4468;
            Bool _t4469 = U64_eq(_t4464, _t4465);
            (void)_t4469;
            ;
            ;
            Bool _t4470; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4467}, &(U64){_t4468}); _t4470 = *_hp; free(_hp); }
            (void)_t4470;
            ;
            ;
            Bool _t4471 = Bool_and(_t4469, _t4470);
            (void)_t4471;
            ;
            ;
            if (_t4471) {
                U64 _t4460 = 1;
                (void)_t4460;
                U64 _t4461 = U64_add(DEREF(ai), _t4460);
                (void)_t4461;
                ;
                *ai = _t4461;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4472 = Str_lit(" -l", 3ULL);
            (void)_t4472;
            Str *_t4473 = Str_concat(link_flags, _t4472);
            (void)_t4473;
            Str_delete(_t4472, &(Bool){1});
            link_flags = Str_concat(_t4473, lib);
            Str_delete(_t4473, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4474 = Str_clone(arg);
            (void)_t4474;
            Vec_push(user_argv, _t4474);
        }
        ;
        U64 _t4478 = 1;
        (void)_t4478;
        U64 _t4479 = U64_add(DEREF(ai), _t4478);
        (void)_t4479;
        ;
        *ai = _t4479;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4761; { U64 *_hp = (U64 *)Str_len(link_flags); _t4761 = *_hp; free(_hp); }
    (void)_t4761;
    U64 _t4762 = 0;
    (void)_t4762;
    Bool _t4763; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4761}, &(U64){_t4762}); _t4763 = *_hp; free(_hp); }
    (void)_t4763;
    ;
    ;
    if (_t4763) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4764 = Str_lit("interpret", 9ULL);
    (void)_t4764;
    Str *_t4765 = Str_lit("test", 4ULL);
    (void)_t4765;
    Bool _t4766; { Bool *_hp = (Bool *)Str_eq(command, _t4764); _t4766 = *_hp; free(_hp); }
    (void)_t4766;
    Str_delete(_t4764, &(Bool){1});
    Bool _t4767; { Bool *_hp = (Bool *)Str_eq(command, _t4765); _t4767 = *_hp; free(_hp); }
    (void)_t4767;
    Str_delete(_t4765, &(Bool){1});
    Bool _t4768 = Bool_or(_t4766, _t4767);
    (void)_t4768;
    ;
    ;
    if (_t4768) {
        Str *_t4486 = Str_lit("interpret", 9ULL);
        (void)_t4486;
        Bool _t4487; { Bool *_hp = (Bool *)Str_eq(command, _t4486); _t4487 = *_hp; free(_hp); }
        (void)_t4487;
        Str_delete(_t4486, &(Bool){1});
        Bool _t4488 = Bool_and(is_lib_mode, _t4487);
        (void)_t4488;
        ;
        if (_t4488) {
            Str *_t4480 = Str_lit("Str", 3ULL);
            (void)_t4480;
            U64 _t4481; { U64 *_hp = (U64 *)Str_size(); _t4481 = *_hp; free(_hp); }
            (void)_t4481;
            U64 _t4482 = 1;
            (void)_t4482;
            Array *_va90 = Array_new(_t4480, &(U64){_t4481}, &(U64){_t4482});
            (void)_va90;
            Str_delete(_t4480, &(Bool){1});
            ;
            ;
            U64 _t4483 = 0;
            (void)_t4483;
            Str *_t4484 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4484;
            Array_set(_va90, &(U64){_t4483}, _t4484);
            ;
            Str *_t4485 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4485;
            panic(_t4485, _va90);
            Str_delete(_t4485, &(Bool){1});
        }
        ;
        I32 _t4489 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4489;
        result = _t4489;
        ;
    } else {
        Str *_t4682 = Str_lit("translate", 9ULL);
        (void)_t4682;
        Str *_t4683 = Str_lit("build", 5ULL);
        (void)_t4683;
        Bool _t4684; { Bool *_hp = (Bool *)Str_eq(command, _t4682); _t4684 = *_hp; free(_hp); }
        (void)_t4684;
        Str_delete(_t4682, &(Bool){1});
        Bool _t4685; { Bool *_hp = (Bool *)Str_eq(command, _t4683); _t4685 = *_hp; free(_hp); }
        (void)_t4685;
        Str_delete(_t4683, &(Bool){1});
        Str *_t4686 = Str_lit("run", 3ULL);
        (void)_t4686;
        Bool _t4687 = Bool_or(_t4684, _t4685);
        (void)_t4687;
        ;
        ;
        Bool _t4688; { Bool *_hp = (Bool *)Str_eq(command, _t4686); _t4688 = *_hp; free(_hp); }
        (void)_t4688;
        Str_delete(_t4686, &(Bool){1});
        Bool _t4689 = Bool_or(_t4687, _t4688);
        (void)_t4689;
        ;
        ;
        if (_t4689) {
            Str *_t4615 = Str_lit("run", 3ULL);
            (void)_t4615;
            Bool _t4616; { Bool *_hp = (Bool *)Str_eq(command, _t4615); _t4616 = *_hp; free(_hp); }
            (void)_t4616;
            Str_delete(_t4615, &(Bool){1});
            Bool _t4617 = Bool_and(is_lib_mode, _t4616);
            (void)_t4617;
            ;
            if (_t4617) {
                Str *_t4490 = Str_lit("Str", 3ULL);
                (void)_t4490;
                U64 _t4491; { U64 *_hp = (U64 *)Str_size(); _t4491 = *_hp; free(_hp); }
                (void)_t4491;
                U64 _t4492 = 1;
                (void)_t4492;
                Array *_va91 = Array_new(_t4490, &(U64){_t4491}, &(U64){_t4492});
                (void)_va91;
                Str_delete(_t4490, &(Bool){1});
                ;
                ;
                U64 _t4493 = 0;
                (void)_t4493;
                Str *_t4494 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4494;
                Array_set(_va91, &(U64){_t4493}, _t4494);
                ;
                Str *_t4495 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4495;
                panic(_t4495, _va91);
                Str_delete(_t4495, &(Bool){1});
            }
            ;
            Str *_t4618 = Str_lit("/", 1ULL);
            (void)_t4618;
            I64 *last_slash = Str_rfind(path, _t4618);
            (void)last_slash;
            Str_delete(_t4618, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4619 = 0;
            (void)_t4619;
            Bool _t4620; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4619}); _t4620 = *_hp; free(_hp); }
            (void)_t4620;
            ;
            if (_t4620) {
                I64 _t4496 = 1;
                (void)_t4496;
                I64 _t4497 = I64_add(DEREF(last_slash), _t4496);
                (void)_t4497;
                ;
                U64 _t4498; { U64 *_hp = (U64 *)Str_len(path); _t4498 = *_hp; free(_hp); }
                (void)_t4498;
                U64 _t4499 = I64_to_u64(DEREF(last_slash));
                (void)_t4499;
                U64 _t4500 = U64_sub(_t4498, _t4499);
                (void)_t4500;
                ;
                ;
                U64 _t4501 = 1;
                (void)_t4501;
                U64 _t4502 = I64_to_u64(_t4497);
                (void)_t4502;
                ;
                U64 _t4503 = U64_sub(_t4500, _t4501);
                (void)_t4503;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4502}, &(U64){_t4503});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4621 = Str_lit(".til", 4ULL);
            (void)_t4621;
            Bool _t4622; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4621); _t4622 = *_hp; free(_hp); }
            (void)_t4622;
            Str_delete(_t4621, &(Bool){1});
            if (_t4622) {
                U64 _t4504 = 4;
                (void)_t4504;
                U64 _t4505 = U64_sub(name_len, _t4504);
                (void)_t4505;
                ;
                name_len = _t4505;
                ;
            }
            ;
            U64 _t4623 = 0;
            (void)_t4623;
            Str *name = Str_substr(basename, &(U64){_t4623}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4624 = Str_lit("gen/til/", 8ULL);
            (void)_t4624;
            Str *_t4625 = Str_concat(_t4624, name);
            (void)_t4625;
            Str_delete(_t4624, &(Bool){1});
            Str *_t4626 = Str_lit(".c", 2ULL);
            (void)_t4626;
            Str *c_path = Str_concat(_t4625, _t4626);
            (void)c_path;
            Str_delete(_t4625, &(Bool){1});
            Str_delete(_t4626, &(Bool){1});
            U64 _t4627; { U64 *_hp = (U64 *)Str_len(custom_c); _t4627 = *_hp; free(_hp); }
            (void)_t4627;
            U64 _t4628 = 0;
            (void)_t4628;
            Bool _t4629; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4627}, &(U64){_t4628}); _t4629 = *_hp; free(_hp); }
            (void)_t4629;
            ;
            ;
            if (_t4629) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4630 = Str_lit("bin/til/", 8ULL);
            (void)_t4630;
            Str *bin_path = Str_concat(_t4630, name);
            (void)bin_path;
            Str_delete(_t4630, &(Bool){1});
            U64 _t4631; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4631 = *_hp; free(_hp); }
            (void)_t4631;
            U64 _t4632 = 0;
            (void)_t4632;
            Bool _t4633; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4631}, &(U64){_t4632}); _t4633 = *_hp; free(_hp); }
            (void)_t4633;
            ;
            ;
            if (_t4633) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4634 = Str_lit("run", 3ULL);
            (void)_t4634;
            Bool _t4635; { Bool *_hp = (Bool *)Str_eq(command, _t4634); _t4635 = *_hp; free(_hp); }
            (void)_t4635;
            Str_delete(_t4634, &(Bool){1});
            Bool _t4636; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4636 = *_hp; free(_hp); }
            (void)_t4636;
            Bool _t4637 = Bool_not(_t4635);
            (void)_t4637;
            ;
            Bool do_lib = Bool_and(_t4636, _t4637);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4506 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4506;
                I32 _t4507 = til_system(_t4506);
                (void)_t4507;
                Str_delete(_t4506, &(Bool){1});
                ;
            } else {
                Str *_t4512 = Str_lit("/", 1ULL);
                (void)_t4512;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4512); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4512, &(Bool){1});
                Str *_t4513 = Str_lit("/", 1ULL);
                (void)_t4513;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4513); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4513, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4514 = 0;
                (void)_t4514;
                Bool _t4515; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4514}); _t4515 = *_hp; free(_hp); }
                (void)_t4515;
                ;
                if (_t4515) {
                    U64 _t4508 = 0;
                    (void)_t4508;
                    U64 _t4509 = I64_to_u64(cp_slash);
                    (void)_t4509;
                    cp_dir = Str_substr(c_path, &(U64){_t4508}, &(U64){_t4509});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4516 = 0;
                (void)_t4516;
                Bool _t4517; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4516}); _t4517 = *_hp; free(_hp); }
                (void)_t4517;
                ;
                if (_t4517) {
                    U64 _t4510 = 0;
                    (void)_t4510;
                    U64 _t4511 = I64_to_u64(bp_slash);
                    (void)_t4511;
                    bp_dir = Str_substr(bin_path, &(U64){_t4510}, &(U64){_t4511});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4518 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4518;
                Str *_t4519 = Str_concat(_t4518, cp_dir);
                (void)_t4519;
                Str_delete(_t4518, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4520 = Str_lit(" ", 1ULL);
                (void)_t4520;
                Str *_t4521 = Str_concat(_t4519, _t4520);
                (void)_t4521;
                Str_delete(_t4519, &(Bool){1});
                Str_delete(_t4520, &(Bool){1});
                Str *_t4522 = Str_concat(_t4521, bp_dir);
                (void)_t4522;
                Str_delete(_t4521, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4523 = til_system(_t4522);
                (void)_t4523;
                Str_delete(_t4522, &(Bool){1});
                ;
            }
            I32 _t4638 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4638;
            result = _t4638;
            ;
            I32 _t4639 = 0;
            (void)_t4639;
            Bool _t4640 = I32_eq(result, _t4639);
            (void)_t4640;
            ;
            Bool _t4641 = Bool_and(_t4640, do_lib);
            (void)_t4641;
            ;
            if (_t4641) {
                Str *_t4580 = Str_lit("gen/til/", 8ULL);
                (void)_t4580;
                Str *_t4581 = Str_concat(_t4580, name);
                (void)_t4581;
                Str_delete(_t4580, &(Bool){1});
                Str *_t4582 = Str_lit(".h", 2ULL);
                (void)_t4582;
                Str *h_path = Str_concat(_t4581, _t4582);
                (void)h_path;
                Str_delete(_t4581, &(Bool){1});
                Str_delete(_t4582, &(Bool){1});
                Str *_t4583 = Str_lit("gen/til/", 8ULL);
                (void)_t4583;
                Str *_t4584 = Str_concat(_t4583, name);
                (void)_t4584;
                Str_delete(_t4583, &(Bool){1});
                Str *_t4585 = Str_lit(".til", 4ULL);
                (void)_t4585;
                Str *til_path = Str_concat(_t4584, _t4585);
                (void)til_path;
                Str_delete(_t4584, &(Bool){1});
                Str_delete(_t4585, &(Bool){1});
                I32 _t4586 = build_header(ast, h_path);
                (void)_t4586;
                result = _t4586;
                ;
                I32 _t4587 = 0;
                (void)_t4587;
                Bool _t4588 = I32_eq(result, _t4587);
                (void)_t4588;
                ;
                if (_t4588) {
                    I32 _t4524 = build_til_binding(ast, til_path, name);
                    (void)_t4524;
                    result = _t4524;
                    ;
                }
                ;
                I32 _t4589 = 0;
                (void)_t4589;
                Str *_t4590 = Str_lit("translate", 9ULL);
                (void)_t4590;
                Bool _t4591 = I32_eq(result, _t4589);
                (void)_t4591;
                ;
                Bool _t4592; { Bool *_hp = (Bool *)Str_eq(command, _t4590); _t4592 = *_hp; free(_hp); }
                (void)_t4592;
                Str_delete(_t4590, &(Bool){1});
                Bool _t4593 = Bool_and(_t4591, _t4592);
                (void)_t4593;
                ;
                ;
                if (_t4593) {
                    Str *_t4525 = Str_lit("Str", 3ULL);
                    (void)_t4525;
                    U64 _t4526; { U64 *_hp = (U64 *)Str_size(); _t4526 = *_hp; free(_hp); }
                    (void)_t4526;
                    U64 _t4527 = 1;
                    (void)_t4527;
                    Array *_va92 = Array_new(_t4525, &(U64){_t4526}, &(U64){_t4527});
                    (void)_va92;
                    Str_delete(_t4525, &(Bool){1});
                    ;
                    ;
                    Str *_t4528 = Str_lit("Generated: ", 11ULL);
                    (void)_t4528;
                    U64 _t4529 = 0;
                    (void)_t4529;
                    Str *_t4530 = Str_concat(_t4528, c_path);
                    (void)_t4530;
                    Str_delete(_t4528, &(Bool){1});
                    Array_set(_va92, &(U64){_t4529}, _t4530);
                    ;
                    println(_va92);
                    Str *_t4531 = Str_lit("Str", 3ULL);
                    (void)_t4531;
                    U64 _t4532; { U64 *_hp = (U64 *)Str_size(); _t4532 = *_hp; free(_hp); }
                    (void)_t4532;
                    U64 _t4533 = 1;
                    (void)_t4533;
                    Array *_va93 = Array_new(_t4531, &(U64){_t4532}, &(U64){_t4533});
                    (void)_va93;
                    Str_delete(_t4531, &(Bool){1});
                    ;
                    ;
                    Str *_t4534 = Str_lit("Generated: ", 11ULL);
                    (void)_t4534;
                    U64 _t4535 = 0;
                    (void)_t4535;
                    Str *_t4536 = Str_concat(_t4534, h_path);
                    (void)_t4536;
                    Str_delete(_t4534, &(Bool){1});
                    Array_set(_va93, &(U64){_t4535}, _t4536);
                    ;
                    println(_va93);
                    Str *_t4537 = Str_lit("Str", 3ULL);
                    (void)_t4537;
                    U64 _t4538; { U64 *_hp = (U64 *)Str_size(); _t4538 = *_hp; free(_hp); }
                    (void)_t4538;
                    U64 _t4539 = 1;
                    (void)_t4539;
                    Array *_va94 = Array_new(_t4537, &(U64){_t4538}, &(U64){_t4539});
                    (void)_va94;
                    Str_delete(_t4537, &(Bool){1});
                    ;
                    ;
                    Str *_t4540 = Str_lit("Generated: ", 11ULL);
                    (void)_t4540;
                    U64 _t4541 = 0;
                    (void)_t4541;
                    Str *_t4542 = Str_concat(_t4540, til_path);
                    (void)_t4542;
                    Str_delete(_t4540, &(Bool){1});
                    Array_set(_va94, &(U64){_t4541}, _t4542);
                    ;
                    println(_va94);
                }
                ;
                I32 _t4594 = 0;
                (void)_t4594;
                Str *_t4595 = Str_lit("build", 5ULL);
                (void)_t4595;
                Bool _t4596 = I32_eq(result, _t4594);
                (void)_t4596;
                ;
                Bool _t4597; { Bool *_hp = (Bool *)Str_eq(command, _t4595); _t4597 = *_hp; free(_hp); }
                (void)_t4597;
                Str_delete(_t4595, &(Bool){1});
                Bool _t4598 = Bool_and(_t4596, _t4597);
                (void)_t4598;
                ;
                ;
                if (_t4598) {
                    I32 _t4577 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4577;
                    result = _t4577;
                    ;
                    I32 _t4578 = 0;
                    (void)_t4578;
                    Bool _t4579 = I32_eq(result, _t4578);
                    (void)_t4579;
                    ;
                    if (_t4579) {
                        Str *_t4543 = Str_lit("Str", 3ULL);
                        (void)_t4543;
                        U64 _t4544; { U64 *_hp = (U64 *)Str_size(); _t4544 = *_hp; free(_hp); }
                        (void)_t4544;
                        U64 _t4545 = 1;
                        (void)_t4545;
                        Array *_va95 = Array_new(_t4543, &(U64){_t4544}, &(U64){_t4545});
                        (void)_va95;
                        Str_delete(_t4543, &(Bool){1});
                        ;
                        ;
                        Str *_t4546 = Str_lit("Generated: ", 11ULL);
                        (void)_t4546;
                        U64 _t4547 = 0;
                        (void)_t4547;
                        Str *_t4548 = Str_concat(_t4546, c_path);
                        (void)_t4548;
                        Str_delete(_t4546, &(Bool){1});
                        Array_set(_va95, &(U64){_t4547}, _t4548);
                        ;
                        println(_va95);
                        Str *_t4549 = Str_lit("Str", 3ULL);
                        (void)_t4549;
                        U64 _t4550; { U64 *_hp = (U64 *)Str_size(); _t4550 = *_hp; free(_hp); }
                        (void)_t4550;
                        U64 _t4551 = 1;
                        (void)_t4551;
                        Array *_va96 = Array_new(_t4549, &(U64){_t4550}, &(U64){_t4551});
                        (void)_va96;
                        Str_delete(_t4549, &(Bool){1});
                        ;
                        ;
                        Str *_t4552 = Str_lit("Generated: ", 11ULL);
                        (void)_t4552;
                        U64 _t4553 = 0;
                        (void)_t4553;
                        Str *_t4554 = Str_concat(_t4552, h_path);
                        (void)_t4554;
                        Str_delete(_t4552, &(Bool){1});
                        Array_set(_va96, &(U64){_t4553}, _t4554);
                        ;
                        println(_va96);
                        Str *_t4555 = Str_lit("Str", 3ULL);
                        (void)_t4555;
                        U64 _t4556; { U64 *_hp = (U64 *)Str_size(); _t4556 = *_hp; free(_hp); }
                        (void)_t4556;
                        U64 _t4557 = 1;
                        (void)_t4557;
                        Array *_va97 = Array_new(_t4555, &(U64){_t4556}, &(U64){_t4557});
                        (void)_va97;
                        Str_delete(_t4555, &(Bool){1});
                        ;
                        ;
                        Str *_t4558 = Str_lit("Generated: ", 11ULL);
                        (void)_t4558;
                        U64 _t4559 = 0;
                        (void)_t4559;
                        Str *_t4560 = Str_concat(_t4558, til_path);
                        (void)_t4560;
                        Str_delete(_t4558, &(Bool){1});
                        Array_set(_va97, &(U64){_t4559}, _t4560);
                        ;
                        println(_va97);
                        Str *_t4561 = Str_lit("Str", 3ULL);
                        (void)_t4561;
                        U64 _t4562; { U64 *_hp = (U64 *)Str_size(); _t4562 = *_hp; free(_hp); }
                        (void)_t4562;
                        U64 _t4563 = 1;
                        (void)_t4563;
                        Array *_va98 = Array_new(_t4561, &(U64){_t4562}, &(U64){_t4563});
                        (void)_va98;
                        Str_delete(_t4561, &(Bool){1});
                        ;
                        ;
                        Str *_t4564 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4564;
                        Str *_t4565 = Str_concat(_t4564, name);
                        (void)_t4565;
                        Str_delete(_t4564, &(Bool){1});
                        Str *_t4566 = Str_lit(".so", 3ULL);
                        (void)_t4566;
                        U64 _t4567 = 0;
                        (void)_t4567;
                        Str *_t4568 = Str_concat(_t4565, _t4566);
                        (void)_t4568;
                        Str_delete(_t4565, &(Bool){1});
                        Str_delete(_t4566, &(Bool){1});
                        Array_set(_va98, &(U64){_t4567}, _t4568);
                        ;
                        println(_va98);
                        Str *_t4569 = Str_lit("Str", 3ULL);
                        (void)_t4569;
                        U64 _t4570; { U64 *_hp = (U64 *)Str_size(); _t4570 = *_hp; free(_hp); }
                        (void)_t4570;
                        U64 _t4571 = 1;
                        (void)_t4571;
                        Array *_va99 = Array_new(_t4569, &(U64){_t4570}, &(U64){_t4571});
                        (void)_va99;
                        Str_delete(_t4569, &(Bool){1});
                        ;
                        ;
                        Str *_t4572 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4572;
                        Str *_t4573 = Str_concat(_t4572, name);
                        (void)_t4573;
                        Str_delete(_t4572, &(Bool){1});
                        Str *_t4574 = Str_lit(".a", 2ULL);
                        (void)_t4574;
                        U64 _t4575 = 0;
                        (void)_t4575;
                        Str *_t4576 = Str_concat(_t4573, _t4574);
                        (void)_t4576;
                        Str_delete(_t4573, &(Bool){1});
                        Str_delete(_t4574, &(Bool){1});
                        Array_set(_va99, &(U64){_t4575}, _t4576);
                        ;
                        println(_va99);
                    }
                    ;
                }
                ;
                Str_delete(h_path, &(Bool){1});
                Str_delete(til_path, &(Bool){1});
            }
            ;
            Str_delete(name, &(Bool){1});
            I32 _t4642 = 0;
            (void)_t4642;
            Bool _t4643 = I32_eq(result, _t4642);
            (void)_t4643;
            ;
            Bool _t4644 = Bool_not(do_lib);
            (void)_t4644;
            Str *_t4645 = Str_lit("translate", 9ULL);
            (void)_t4645;
            Bool _t4646 = Bool_and(_t4643, _t4644);
            (void)_t4646;
            ;
            ;
            Bool _t4647; { Bool *_hp = (Bool *)Str_eq(command, _t4645); _t4647 = *_hp; free(_hp); }
            (void)_t4647;
            Str_delete(_t4645, &(Bool){1});
            Bool _t4648 = Bool_and(_t4646, _t4647);
            (void)_t4648;
            ;
            ;
            if (_t4648) {
                Str *_t4599 = Str_lit("Str", 3ULL);
                (void)_t4599;
                U64 _t4600; { U64 *_hp = (U64 *)Str_size(); _t4600 = *_hp; free(_hp); }
                (void)_t4600;
                U64 _t4601 = 1;
                (void)_t4601;
                Array *_va100 = Array_new(_t4599, &(U64){_t4600}, &(U64){_t4601});
                (void)_va100;
                Str_delete(_t4599, &(Bool){1});
                ;
                ;
                Str *_t4602 = Str_lit("Generated: ", 11ULL);
                (void)_t4602;
                U64 _t4603 = 0;
                (void)_t4603;
                Str *_t4604 = Str_concat(_t4602, c_path);
                (void)_t4604;
                Str_delete(_t4602, &(Bool){1});
                Array_set(_va100, &(U64){_t4603}, _t4604);
                ;
                println(_va100);
            }
            ;
            I32 _t4649 = 0;
            (void)_t4649;
            Bool _t4650 = I32_eq(result, _t4649);
            (void)_t4650;
            ;
            Bool _t4651 = Bool_not(do_lib);
            (void)_t4651;
            Str *_t4652 = Str_lit("translate", 9ULL);
            (void)_t4652;
            Bool _t4653; { Bool *_hp = (Bool *)Str_eq(command, _t4652); _t4653 = *_hp; free(_hp); }
            (void)_t4653;
            Str_delete(_t4652, &(Bool){1});
            Bool _t4654 = Bool_and(_t4650, _t4651);
            (void)_t4654;
            ;
            ;
            Bool _t4655 = Bool_not(_t4653);
            (void)_t4655;
            ;
            Bool _t4656 = Bool_and(_t4654, _t4655);
            (void)_t4656;
            ;
            ;
            if (_t4656) {
                I32 _t4605 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4605;
                result = _t4605;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4657 = 0;
            (void)_t4657;
            Bool _t4658 = I32_eq(result, _t4657);
            (void)_t4658;
            ;
            Bool _t4659 = Bool_not(do_lib);
            (void)_t4659;
            ;
            Str *_t4660 = Str_lit("run", 3ULL);
            (void)_t4660;
            Bool _t4661 = Bool_and(_t4658, _t4659);
            (void)_t4661;
            ;
            ;
            Bool _t4662; { Bool *_hp = (Bool *)Str_eq(command, _t4660); _t4662 = *_hp; free(_hp); }
            (void)_t4662;
            Str_delete(_t4660, &(Bool){1});
            Bool _t4663 = Bool_and(_t4661, _t4662);
            (void)_t4663;
            ;
            ;
            if (_t4663) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4607; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4607 = *_hp; free(_hp); }
                    (void)_t4607;
                    Bool _wcond4606; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4607}); _wcond4606 = *_hp; free(_hp); }
                    (void)_wcond4606;
                    ;
                    if (_wcond4606) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4608 = Str_lit(" '", 2ULL);
                    (void)_t4608;
                    Str *_t4609 = Str_concat(cmd, _t4608);
                    (void)_t4609;
                    Str_delete(_t4608, &(Bool){1});
                    Str *_t4610 = Str_concat(_t4609, uarg);
                    (void)_t4610;
                    Str_delete(_t4609, &(Bool){1});
                    Str *_t4611 = Str_lit("'", 1ULL);
                    (void)_t4611;
                    cmd = Str_concat(_t4610, _t4611);
                    Str_delete(_t4610, &(Bool){1});
                    Str_delete(_t4611, &(Bool){1});
                    U64 _t4612 = 1;
                    (void)_t4612;
                    U64 _t4613 = U64_add(DEREF(ui), _t4612);
                    (void)_t4613;
                    ;
                    *ui = _t4613;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4614 = til_system(cmd);
                (void)_t4614;
                Str_delete(cmd, &(Bool){1});
                result = _t4614;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4680 = Str_lit("ast", 3ULL);
            (void)_t4680;
            Bool _t4681; { Bool *_hp = (Bool *)Str_eq(command, _t4680); _t4681 = *_hp; free(_hp); }
            (void)_t4681;
            Str_delete(_t4680, &(Bool){1});
            if (_t4681) {
                Str *_t4664 = Str_lit("Str", 3ULL);
                (void)_t4664;
                U64 _t4665; { U64 *_hp = (U64 *)Str_size(); _t4665 = *_hp; free(_hp); }
                (void)_t4665;
                U64 _t4666 = 1;
                (void)_t4666;
                Array *_va101 = Array_new(_t4664, &(U64){_t4665}, &(U64){_t4666});
                (void)_va101;
                Str_delete(_t4664, &(Bool){1});
                ;
                ;
                Str *_t4667 = Str_lit("mode: ", 6ULL);
                (void)_t4667;
                U64 _t4668 = 0;
                (void)_t4668;
                Str *_t4669 = Str_concat(_t4667, &cur_mode->name);
                (void)_t4669;
                Str_delete(_t4667, &(Bool){1});
                Array_set(_va101, &(U64){_t4668}, _t4669);
                ;
                println(_va101);
                U32 _t4670 = 0;
                (void)_t4670;
                ast_print(ast, _t4670);
                ;
            } else {
                Str *_t4671 = Str_lit("Str", 3ULL);
                (void)_t4671;
                U64 _t4672; { U64 *_hp = (U64 *)Str_size(); _t4672 = *_hp; free(_hp); }
                (void)_t4672;
                U64 _t4673 = 1;
                (void)_t4673;
                Array *_va102 = Array_new(_t4671, &(U64){_t4672}, &(U64){_t4673});
                (void)_va102;
                Str_delete(_t4671, &(Bool){1});
                ;
                ;
                Str *_t4674 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4674;
                Str *_t4675 = Str_concat(_t4674, command);
                (void)_t4675;
                Str_delete(_t4674, &(Bool){1});
                Str *_t4676 = Str_lit("'", 1ULL);
                (void)_t4676;
                U64 _t4677 = 0;
                (void)_t4677;
                Str *_t4678 = Str_concat(_t4675, _t4676);
                (void)_t4678;
                Str_delete(_t4675, &(Bool){1});
                Str_delete(_t4676, &(Bool){1});
                Array_set(_va102, &(U64){_t4677}, _t4678);
                ;
                println(_va102);
                usage();
                I32 _t4679 = 1;
                (void)_t4679;
                result = _t4679;
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
    I64 _t4769 = I32_to_i64(result);
    (void)_t4769;
    ;
    exit(_t4769);
    ;
    return 0;
}

