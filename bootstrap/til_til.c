#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4197 = Str_lit("Str", 3ULL);
    (void)_t4197;
    U64 _t4198; { U64 *_hp = (U64 *)Str_size(); _t4198 = *_hp; free(_hp); }
    (void)_t4198;
    Vec *paths = Vec_new(_t4197, &(U64){_t4198});
    (void)paths;
    Str_delete(_t4197, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4172 = expr_nchildren(body);
        (void)_t4172;
        Bool _wcond4168; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4172}); _wcond4168 = *_hp; free(_hp); }
        (void)_wcond4168;
        ;
        if (_wcond4168) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4173 = expr_get_tag(stmt);
        (void)_t4173;
        U32 _t4174 = expr_nchildren(stmt);
        (void)_t4174;
        U32 _t4175 = 2;
        (void)_t4175;
        Bool _t4176 = I32_eq(_t4173, DEREF(NODE_FCALL));
        (void)_t4176;
        ;
        Bool _t4177 = U32_eq(_t4174, _t4175);
        (void)_t4177;
        ;
        ;
        U32 *_t4178 = malloc(sizeof(U32));
        *_t4178 = 0;
        (void)_t4178;
        Expr *_t4179 = expr_get_child(stmt, DEREF(_t4178));
        (void)_t4179;
        I32 _t4180 = expr_get_tag(_t4179);
        (void)_t4180;
        U32_delete(_t4178, &(Bool){1});
        Bool _t4181 = Bool_and(_t4176, _t4177);
        (void)_t4181;
        ;
        ;
        Bool _t4182 = I32_eq(_t4180, DEREF(NODE_IDENT));
        (void)_t4182;
        ;
        U32 *_t4183 = malloc(sizeof(U32));
        *_t4183 = 0;
        (void)_t4183;
        Expr *_t4184 = expr_get_child(stmt, DEREF(_t4183));
        (void)_t4184;
        Str *_t4185 = expr_get_str_val(_t4184);
        (void)_t4185;
        Str *_t4186 = Str_lit("import", 6ULL);
        (void)_t4186;
        Bool _t4187 = Bool_and(_t4181, _t4182);
        (void)_t4187;
        ;
        ;
        Bool _t4188; { Bool *_hp = (Bool *)Str_eq(_t4185, _t4186); _t4188 = *_hp; free(_hp); }
        (void)_t4188;
        U32_delete(_t4183, &(Bool){1});
        Str_delete(_t4186, &(Bool){1});
        U32 *_t4189 = malloc(sizeof(U32));
        *_t4189 = 1;
        (void)_t4189;
        Expr *_t4190 = expr_get_child(stmt, DEREF(_t4189));
        (void)_t4190;
        I32 _t4191 = expr_get_tag(_t4190);
        (void)_t4191;
        U32_delete(_t4189, &(Bool){1});
        Bool _t4192 = Bool_and(_t4187, _t4188);
        (void)_t4192;
        ;
        ;
        Bool _t4193 = I32_eq(_t4191, DEREF(NODE_LITERAL_STR));
        (void)_t4193;
        ;
        Bool _t4194 = Bool_and(_t4192, _t4193);
        (void)_t4194;
        ;
        ;
        if (_t4194) {
            U32 *_t4169 = malloc(sizeof(U32));
            *_t4169 = 1;
            (void)_t4169;
            Expr *_t4170 = expr_get_child(stmt, DEREF(_t4169));
            (void)_t4170;
            Str *path = expr_get_str_val(_t4170);
            (void)path;
            Str *_t4171 = Str_clone(path);
            (void)_t4171;
            U32_delete(_t4169, &(Bool){1});
            Vec_push(paths, _t4171);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4195 = 1;
        (void)_t4195;
        U32 _t4196 = U32_add(DEREF(i), _t4195);
        (void)_t4196;
        ;
        *i = _t4196;
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
        U64 _t4249 = 0;
        (void)_t4249;
        U64 _t4250; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4250 = *_hp; free(_hp); }
        (void)_t4250;
        Range *_fc4199 = Range_new(_t4249, _t4250);
        (void)_fc4199;
        ;
        ;
        U64 _fi4199 = 0;
        (void)_fi4199;
        while (1) {
            U64 _t4229; { U64 *_hp = (U64 *)Range_len(_fc4199); _t4229 = *_hp; free(_hp); }
            (void)_t4229;
            Bool _wcond4200; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4199}, &(U64){_t4229}); _wcond4200 = *_hp; free(_hp); }
            (void)_wcond4200;
            ;
            if (_wcond4200) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4199, _fi4199);
            (void)i;
            U64 _t4230 = 1;
            (void)_t4230;
            U64 _t4231 = U64_add(_fi4199, _t4230);
            (void)_t4231;
            ;
            _fi4199 = _t4231;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4232 = Str_lit("/", 1ULL);
            (void)_t4232;
            Str *_t4233 = Str_concat(base_dir, _t4232);
            (void)_t4233;
            Str_delete(_t4232, &(Bool){1});
            Str *try_path = Str_concat(_t4233, import_path);
            (void)try_path;
            Str_delete(_t4233, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4234 = Str_lit("", 0ULL);
            (void)_t4234;
            U64 _t4235; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4235 = *_hp; free(_hp); }
            (void)_t4235;
            U64 _t4236 = 0;
            (void)_t4236;
            Bool _t4237; { Bool *_hp = (Bool *)Str_eq(abs, _t4234); _t4237 = *_hp; free(_hp); }
            (void)_t4237;
            Str_delete(_t4234, &(Bool){1});
            Bool _t4238; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4235}, &(U64){_t4236}); _t4238 = *_hp; free(_hp); }
            (void)_t4238;
            ;
            ;
            Bool _t4239 = Bool_and(_t4237, _t4238);
            (void)_t4239;
            ;
            ;
            if (_t4239) {
                Str *_t4201 = Str_lit("/", 1ULL);
                (void)_t4201;
                Str *_t4202 = Str_concat(lib_dir, _t4201);
                (void)_t4202;
                Str_delete(_t4201, &(Bool){1});
                try_path = Str_concat(_t4202, import_path);
                Str_delete(_t4202, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4240 = Str_lit("", 0ULL);
            (void)_t4240;
            Bool _t4241; { Bool *_hp = (Bool *)Str_eq(abs, _t4240); _t4241 = *_hp; free(_hp); }
            (void)_t4241;
            Str_delete(_t4240, &(Bool){1});
            if (_t4241) {
                Str *_t4203 = Str_lit("Str", 3ULL);
                (void)_t4203;
                U64 _t4204; { U64 *_hp = (U64 *)Str_size(); _t4204 = *_hp; free(_hp); }
                (void)_t4204;
                U64 _t4205 = 1;
                (void)_t4205;
                Array *_va75 = Array_new(_t4203, &(U64){_t4204}, &(U64){_t4205});
                (void)_va75;
                Str_delete(_t4203, &(Bool){1});
                ;
                ;
                Str *_t4206 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4206;
                Str *_t4207 = Str_concat(_t4206, import_path);
                (void)_t4207;
                Str_delete(_t4206, &(Bool){1});
                Str *_t4208 = Str_lit("' (from ", 8ULL);
                (void)_t4208;
                Str *_t4209 = Str_concat(_t4207, _t4208);
                (void)_t4209;
                Str_delete(_t4207, &(Bool){1});
                Str_delete(_t4208, &(Bool){1});
                Str *_t4210 = Str_concat(_t4209, base_dir);
                (void)_t4210;
                Str_delete(_t4209, &(Bool){1});
                Str *_t4211 = Str_lit("/)", 2ULL);
                (void)_t4211;
                U64 _t4212 = 0;
                (void)_t4212;
                Str *_t4213 = Str_concat(_t4210, _t4211);
                (void)_t4213;
                Str_delete(_t4210, &(Bool){1});
                Str_delete(_t4211, &(Bool){1});
                Array_set(_va75, &(U64){_t4212}, _t4213);
                ;
                println(_va75);
                I64 _t4214 = 1;
                (void)_t4214;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4199, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4214; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4242; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4242 = *_hp; free(_hp); }
            (void)_t4242;
            if (_t4242) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4243 = Str_clone(abs);
            (void)_t4243;
            Set_add(resolved_set, _t4243);
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
            U64 _t4244; { U64 *_hp = (U64 *)Str_len(abs); _t4244 = *_hp; free(_hp); }
            (void)_t4244;
            U64 _t4245 = 1;
            (void)_t4245;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4244, _t4245);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4216 = 0;
                (void)_t4216;
                U8 *_t4217 = Str_get(abs, last_slash);
                (void)_t4217;
                U8 _t4218 = 47;
                (void)_t4218;
                Bool _t4219; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4216}); _t4219 = *_hp; free(_hp); }
                (void)_t4219;
                ;
                Bool _t4220; { Bool *_hp = (Bool *)U8_neq(_t4217, &(U8){_t4218}); _t4220 = *_hp; free(_hp); }
                (void)_t4220;
                ;
                Bool _wcond4215 = Bool_and(_t4219, _t4220);
                (void)_wcond4215;
                ;
                ;
                if (_wcond4215) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4221 = 1;
                (void)_t4221;
                U64 _t4222 = U64_sub(DEREF(last_slash), _t4221);
                (void)_t4222;
                ;
                *last_slash = _t4222;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4246; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4246 = *_hp; free(_hp); }
            (void)_t4246;
            U64 _t4247 = 0;
            (void)_t4247;
            Bool _t4248; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4246}, &(U64){_t4247}); _t4248 = *_hp; free(_hp); }
            (void)_t4248;
            ;
            ;
            if (_t4248) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4223 = 0;
                (void)_t4223;
                Bool _t4224; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4223}); _t4224 = *_hp; free(_hp); }
                (void)_t4224;
                ;
                if (_t4224) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4199, &(Bool){1});
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
                U32 _t4226 = expr_nchildren(sub_ast);
                (void)_t4226;
                Bool _wcond4225; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4226}); _wcond4225 = *_hp; free(_hp); }
                (void)_wcond4225;
                ;
                if (_wcond4225) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4227 = 1;
                (void)_t4227;
                U32 _t4228 = U32_add(DEREF(k), _t4227);
                (void)_t4228;
                ;
                *k = _t4228;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4199, &(Bool){1});
        ;
    }
    I64 _t4251 = 0;
    (void)_t4251;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4251; return _r; }
}

void usage(void) {
    Str *_t4252 = Str_lit("Str", 3ULL);
    (void)_t4252;
    U64 _t4253; { U64 *_hp = (U64 *)Str_size(); _t4253 = *_hp; free(_hp); }
    (void)_t4253;
    U64 _t4254 = 1;
    (void)_t4254;
    Array *_va76 = Array_new(_t4252, &(U64){_t4253}, &(U64){_t4254});
    (void)_va76;
    Str_delete(_t4252, &(Bool){1});
    ;
    ;
    U64 _t4255 = 0;
    (void)_t4255;
    Str *_t4256 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4256;
    Array_set(_va76, &(U64){_t4255}, _t4256);
    ;
    println(_va76);
    Str *_t4257 = Str_lit("Str", 3ULL);
    (void)_t4257;
    U64 _t4258; { U64 *_hp = (U64 *)Str_size(); _t4258 = *_hp; free(_hp); }
    (void)_t4258;
    U64 _t4259 = 1;
    (void)_t4259;
    Array *_va77 = Array_new(_t4257, &(U64){_t4258}, &(U64){_t4259});
    (void)_va77;
    Str_delete(_t4257, &(Bool){1});
    ;
    ;
    U64 _t4260 = 0;
    (void)_t4260;
    Str *_t4261 = Str_lit("", 0ULL);
    (void)_t4261;
    Array_set(_va77, &(U64){_t4260}, _t4261);
    ;
    println(_va77);
    Str *_t4262 = Str_lit("Str", 3ULL);
    (void)_t4262;
    U64 _t4263; { U64 *_hp = (U64 *)Str_size(); _t4263 = *_hp; free(_hp); }
    (void)_t4263;
    U64 _t4264 = 1;
    (void)_t4264;
    Array *_va78 = Array_new(_t4262, &(U64){_t4263}, &(U64){_t4264});
    (void)_va78;
    Str_delete(_t4262, &(Bool){1});
    ;
    ;
    U64 _t4265 = 0;
    (void)_t4265;
    Str *_t4266 = Str_lit("Commands:", 9ULL);
    (void)_t4266;
    Array_set(_va78, &(U64){_t4265}, _t4266);
    ;
    println(_va78);
    Str *_t4267 = Str_lit("Str", 3ULL);
    (void)_t4267;
    U64 _t4268; { U64 *_hp = (U64 *)Str_size(); _t4268 = *_hp; free(_hp); }
    (void)_t4268;
    U64 _t4269 = 1;
    (void)_t4269;
    Array *_va79 = Array_new(_t4267, &(U64){_t4268}, &(U64){_t4269});
    (void)_va79;
    Str_delete(_t4267, &(Bool){1});
    ;
    ;
    U64 _t4270 = 0;
    (void)_t4270;
    Str *_t4271 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4271;
    Array_set(_va79, &(U64){_t4270}, _t4271);
    ;
    println(_va79);
    Str *_t4272 = Str_lit("Str", 3ULL);
    (void)_t4272;
    U64 _t4273; { U64 *_hp = (U64 *)Str_size(); _t4273 = *_hp; free(_hp); }
    (void)_t4273;
    U64 _t4274 = 1;
    (void)_t4274;
    Array *_va80 = Array_new(_t4272, &(U64){_t4273}, &(U64){_t4274});
    (void)_va80;
    Str_delete(_t4272, &(Bool){1});
    ;
    ;
    U64 _t4275 = 0;
    (void)_t4275;
    Str *_t4276 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4276;
    Array_set(_va80, &(U64){_t4275}, _t4276);
    ;
    println(_va80);
    Str *_t4277 = Str_lit("Str", 3ULL);
    (void)_t4277;
    U64 _t4278; { U64 *_hp = (U64 *)Str_size(); _t4278 = *_hp; free(_hp); }
    (void)_t4278;
    U64 _t4279 = 1;
    (void)_t4279;
    Array *_va81 = Array_new(_t4277, &(U64){_t4278}, &(U64){_t4279});
    (void)_va81;
    Str_delete(_t4277, &(Bool){1});
    ;
    ;
    U64 _t4280 = 0;
    (void)_t4280;
    Str *_t4281 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4281;
    Array_set(_va81, &(U64){_t4280}, _t4281);
    ;
    println(_va81);
    Str *_t4282 = Str_lit("Str", 3ULL);
    (void)_t4282;
    U64 _t4283; { U64 *_hp = (U64 *)Str_size(); _t4283 = *_hp; free(_hp); }
    (void)_t4283;
    U64 _t4284 = 1;
    (void)_t4284;
    Array *_va82 = Array_new(_t4282, &(U64){_t4283}, &(U64){_t4284});
    (void)_va82;
    Str_delete(_t4282, &(Bool){1});
    ;
    ;
    U64 _t4285 = 0;
    (void)_t4285;
    Str *_t4286 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4286;
    Array_set(_va82, &(U64){_t4285}, _t4286);
    ;
    println(_va82);
    Str *_t4287 = Str_lit("Str", 3ULL);
    (void)_t4287;
    U64 _t4288; { U64 *_hp = (U64 *)Str_size(); _t4288 = *_hp; free(_hp); }
    (void)_t4288;
    U64 _t4289 = 1;
    (void)_t4289;
    Array *_va83 = Array_new(_t4287, &(U64){_t4288}, &(U64){_t4289});
    (void)_va83;
    Str_delete(_t4287, &(Bool){1});
    ;
    ;
    U64 _t4290 = 0;
    (void)_t4290;
    Str *_t4291 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4291;
    Array_set(_va83, &(U64){_t4290}, _t4291);
    ;
    println(_va83);
    Str *_t4292 = Str_lit("Str", 3ULL);
    (void)_t4292;
    U64 _t4293; { U64 *_hp = (U64 *)Str_size(); _t4293 = *_hp; free(_hp); }
    (void)_t4293;
    U64 _t4294 = 1;
    (void)_t4294;
    Array *_va84 = Array_new(_t4292, &(U64){_t4293}, &(U64){_t4294});
    (void)_va84;
    Str_delete(_t4292, &(Bool){1});
    ;
    ;
    U64 _t4295 = 0;
    (void)_t4295;
    Str *_t4296 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4296;
    Array_set(_va84, &(U64){_t4295}, _t4296);
    ;
    println(_va84);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4302 = 1;
    (void)_t4302;
    e->is_core = _t4302;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4298 = expr_nchildren(e);
        (void)_t4298;
        Bool _wcond4297; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4298}); _wcond4297 = *_hp; free(_hp); }
        (void)_wcond4297;
        ;
        if (_wcond4297) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4299 = expr_get_child(e, DEREF(i));
        (void)_t4299;
        mark_core(_t4299);
        U32 _t4300 = 1;
        (void)_t4300;
        U32 _t4301 = U32_add(DEREF(i), _t4300);
        (void)_t4301;
        ;
        *i = _t4301;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4762 = malloc(sizeof(I64));
    *_t4762 = 0;
    (void)_t4762;
    _t4763 = malloc(sizeof(I64));
    *_t4763 = 1;
    (void)_t4763;
    _t4764 = malloc(sizeof(I64)); *_t4764 = I64_sub(DEREF(_t4762), DEREF(_t4763));
    (void)_t4764;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4764));
    (void)CAP_LIT;
    _t4765 = malloc(sizeof(I64));
    *_t4765 = 0;
    (void)_t4765;
    _t4766 = malloc(sizeof(I64));
    *_t4766 = 2;
    (void)_t4766;
    _t4767 = malloc(sizeof(I64)); *_t4767 = I64_sub(DEREF(_t4765), DEREF(_t4766));
    (void)_t4767;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4767));
    (void)CAP_VIEW;
    _t4768 = Str_lit("Str", 3ULL);
    (void)_t4768;
    _t4769 = Str_size();
    (void)_t4769;
    _t4770 = Str_lit("Mode", 4ULL);
    (void)_t4770;
    _t4771 = Mode_size();
    (void)_t4771;
    core_modes = Map_new(_t4768, _t4769, _t4770, _t4771);
    (void)core_modes;
    _t4772 = malloc(sizeof(Bool));
    *_t4772 = 0;
    (void)_t4772;
    _t4773 = malloc(sizeof(Bool));
    *_t4773 = 0;
    (void)_t4773;
    _t4774 = malloc(sizeof(Bool));
    *_t4774 = 0;
    (void)_t4774;
    _t4775 = malloc(sizeof(Bool));
    *_t4775 = 0;
    (void)_t4775;
    _t4776 = Str_lit("script", 6ULL);
    (void)_t4776;
    _t4777 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4777->name = *_ca; free(_ca); }
    _t4777->needs_main = DEREF(_t4772);
    _t4777->decls_only = DEREF(_t4773);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4777->auto_import = *_ca; free(_ca); }
    _t4777->is_pure = DEREF(_t4774);
    _t4777->debug_prints = DEREF(_t4775);
    (void)_t4777;
    _t4778 = malloc(sizeof(Bool));
    *_t4778 = 1;
    (void)_t4778;
    _t4779 = malloc(sizeof(Bool));
    *_t4779 = 1;
    (void)_t4779;
    _t4780 = malloc(sizeof(Bool));
    *_t4780 = 0;
    (void)_t4780;
    _t4781 = malloc(sizeof(Bool));
    *_t4781 = 0;
    (void)_t4781;
    _t4782 = Str_lit("cli", 3ULL);
    (void)_t4782;
    _t4783 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4783->name = *_ca; free(_ca); }
    _t4783->needs_main = DEREF(_t4778);
    _t4783->decls_only = DEREF(_t4779);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4783->auto_import = *_ca; free(_ca); }
    _t4783->is_pure = DEREF(_t4780);
    _t4783->debug_prints = DEREF(_t4781);
    (void)_t4783;
    _t4784 = malloc(sizeof(Bool));
    *_t4784 = 1;
    (void)_t4784;
    _t4785 = malloc(sizeof(Bool));
    *_t4785 = 1;
    (void)_t4785;
    _t4786 = malloc(sizeof(Bool));
    *_t4786 = 0;
    (void)_t4786;
    _t4787 = malloc(sizeof(Bool));
    *_t4787 = 0;
    (void)_t4787;
    _t4788 = Str_lit("gui", 3ULL);
    (void)_t4788;
    _t4789 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4789->name = *_ca; free(_ca); }
    _t4789->needs_main = DEREF(_t4784);
    _t4789->decls_only = DEREF(_t4785);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4789->auto_import = *_ca; free(_ca); }
    _t4789->is_pure = DEREF(_t4786);
    _t4789->debug_prints = DEREF(_t4787);
    (void)_t4789;
    _t4790 = malloc(sizeof(Bool));
    *_t4790 = 0;
    (void)_t4790;
    _t4791 = malloc(sizeof(Bool));
    *_t4791 = 1;
    (void)_t4791;
    _t4792 = malloc(sizeof(Bool));
    *_t4792 = 0;
    (void)_t4792;
    _t4793 = malloc(sizeof(Bool));
    *_t4793 = 0;
    (void)_t4793;
    _t4794 = Str_lit("test", 4ULL);
    (void)_t4794;
    _t4795 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4795->name = *_ca; free(_ca); }
    _t4795->needs_main = DEREF(_t4790);
    _t4795->decls_only = DEREF(_t4791);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4795->auto_import = *_ca; free(_ca); }
    _t4795->is_pure = DEREF(_t4792);
    _t4795->debug_prints = DEREF(_t4793);
    (void)_t4795;
    _t4796 = malloc(sizeof(Bool));
    *_t4796 = 0;
    (void)_t4796;
    _t4797 = malloc(sizeof(Bool));
    *_t4797 = 1;
    (void)_t4797;
    _t4798 = malloc(sizeof(Bool));
    *_t4798 = 1;
    (void)_t4798;
    _t4799 = malloc(sizeof(Bool));
    *_t4799 = 0;
    (void)_t4799;
    _t4800 = Str_lit("pure", 4ULL);
    (void)_t4800;
    _t4801 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4801->name = *_ca; free(_ca); }
    _t4801->needs_main = DEREF(_t4796);
    _t4801->decls_only = DEREF(_t4797);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4801->auto_import = *_ca; free(_ca); }
    _t4801->is_pure = DEREF(_t4798);
    _t4801->debug_prints = DEREF(_t4799);
    (void)_t4801;
    _t4802 = malloc(sizeof(Bool));
    *_t4802 = 0;
    (void)_t4802;
    _t4803 = malloc(sizeof(Bool));
    *_t4803 = 1;
    (void)_t4803;
    _t4804 = malloc(sizeof(Bool));
    *_t4804 = 1;
    (void)_t4804;
    _t4805 = malloc(sizeof(Bool));
    *_t4805 = 1;
    (void)_t4805;
    _t4806 = Str_lit("pura", 4ULL);
    (void)_t4806;
    _t4807 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4807->name = *_ca; free(_ca); }
    _t4807->needs_main = DEREF(_t4802);
    _t4807->decls_only = DEREF(_t4803);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4807->auto_import = *_ca; free(_ca); }
    _t4807->is_pure = DEREF(_t4804);
    _t4807->debug_prints = DEREF(_t4805);
    (void)_t4807;
    _t4808 = malloc(sizeof(Bool));
    *_t4808 = 0;
    (void)_t4808;
    _t4809 = malloc(sizeof(Bool));
    *_t4809 = 1;
    (void)_t4809;
    _t4810 = malloc(sizeof(Bool));
    *_t4810 = 0;
    (void)_t4810;
    _t4811 = malloc(sizeof(Bool));
    *_t4811 = 0;
    (void)_t4811;
    _t4812 = Str_lit("lib", 3ULL);
    (void)_t4812;
    _t4813 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4813->name = *_ca; free(_ca); }
    _t4813->needs_main = DEREF(_t4808);
    _t4813->decls_only = DEREF(_t4809);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4813->auto_import = *_ca; free(_ca); }
    _t4813->is_pure = DEREF(_t4810);
    _t4813->debug_prints = DEREF(_t4811);
    (void)_t4813;
    _t4814 = malloc(sizeof(Bool));
    *_t4814 = 0;
    (void)_t4814;
    _t4815 = malloc(sizeof(Bool));
    *_t4815 = 1;
    (void)_t4815;
    _t4816 = malloc(sizeof(Bool));
    *_t4816 = 0;
    (void)_t4816;
    _t4817 = malloc(sizeof(Bool));
    *_t4817 = 1;
    (void)_t4817;
    _t4818 = Str_lit("liba", 4ULL);
    (void)_t4818;
    _t4819 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4819->name = *_ca; free(_ca); }
    _t4819->needs_main = DEREF(_t4814);
    _t4819->decls_only = DEREF(_t4815);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4819->auto_import = *_ca; free(_ca); }
    _t4819->is_pure = DEREF(_t4816);
    _t4819->debug_prints = DEREF(_t4817);
    (void)_t4819;
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
    U64 _t4682; { U64 *_hp = (U64 *)Array_len(args); _t4682 = *_hp; free(_hp); }
    (void)_t4682;
    U64 _t4683 = 0;
    (void)_t4683;
    Bool _t4684 = U64_eq(_t4682, _t4683);
    (void)_t4684;
    ;
    ;
    if (_t4684) {
        usage();
        Str *_t4303 = Str_lit("Str", 3ULL);
        (void)_t4303;
        U64 _t4304; { U64 *_hp = (U64 *)Str_size(); _t4304 = *_hp; free(_hp); }
        (void)_t4304;
        U64 _t4305 = 1;
        (void)_t4305;
        Array *_va85 = Array_new(_t4303, &(U64){_t4304}, &(U64){_t4305});
        (void)_va85;
        Str_delete(_t4303, &(Bool){1});
        ;
        ;
        U64 _t4306 = 0;
        (void)_t4306;
        Str *_t4307 = Str_lit("no arguments", 12ULL);
        (void)_t4307;
        Array_set(_va85, &(U64){_t4306}, _t4307);
        ;
        Str *_t4308 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4308;
        panic(_t4308, _va85);
        Str_delete(_t4308, &(Bool){1});
    }
    ;
    U64 *_t4685 = malloc(sizeof(U64));
    *_t4685 = 0;
    (void)_t4685;
    Str *cmd_ref = Array_get(args, _t4685);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4685, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4686; { U64 *_hp = (U64 *)Array_len(args); _t4686 = *_hp; free(_hp); }
    (void)_t4686;
    U64 _t4687 = 1;
    (void)_t4687;
    Bool _t4688 = U64_eq(_t4686, _t4687);
    (void)_t4688;
    ;
    ;
    if (_t4688) {
        Str *_t4309 = Str_lit("help", 4ULL);
        (void)_t4309;
        Str *_t4310 = Str_lit("--help", 6ULL);
        (void)_t4310;
        Bool _t4311; { Bool *_hp = (Bool *)Str_eq(command, _t4309); _t4311 = *_hp; free(_hp); }
        (void)_t4311;
        Str_delete(_t4309, &(Bool){1});
        Bool _t4312; { Bool *_hp = (Bool *)Str_eq(command, _t4310); _t4312 = *_hp; free(_hp); }
        (void)_t4312;
        Str_delete(_t4310, &(Bool){1});
        Bool _t4313 = Bool_or(_t4311, _t4312);
        (void)_t4313;
        ;
        ;
        if (_t4313) {
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
            U64 _t4330; { U64 *_hp = (U64 *)Array_len(args); _t4330 = *_hp; free(_hp); }
            (void)_t4330;
            Bool _wcond4314; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4330}); _wcond4314 = *_hp; free(_hp); }
            (void)_wcond4314;
            ;
            if (_wcond4314) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4331 = Str_lit("-o", 2ULL);
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
                U64 _t4315 = 1;
                (void)_t4315;
                U64 *_t4316 = malloc(sizeof(U64)); *_t4316 = U64_add(DEREF(path_idx), _t4315);
                (void)_t4316;
                ;
                Str *oval = Array_get(args, _t4316);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4316, &(Bool){1});
                U64 _t4317 = 2;
                (void)_t4317;
                U64 _t4318 = U64_add(DEREF(path_idx), _t4317);
                (void)_t4318;
                ;
                *path_idx = _t4318;
                ;
            } else {
                Str *_t4323 = Str_lit("-c", 2ULL);
                (void)_t4323;
                U64 _t4324 = 1;
                (void)_t4324;
                U64 _t4325 = U64_add(DEREF(path_idx), _t4324);
                (void)_t4325;
                ;
                U64 _t4326; { U64 *_hp = (U64 *)Array_len(args); _t4326 = *_hp; free(_hp); }
                (void)_t4326;
                Bool _t4327; { Bool *_hp = (Bool *)Str_eq(flag, _t4323); _t4327 = *_hp; free(_hp); }
                (void)_t4327;
                Str_delete(_t4323, &(Bool){1});
                Bool _t4328; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4325}, &(U64){_t4326}); _t4328 = *_hp; free(_hp); }
                (void)_t4328;
                ;
                ;
                Bool _t4329 = Bool_and(_t4327, _t4328);
                (void)_t4329;
                ;
                ;
                if (_t4329) {
                    U64 _t4319 = 1;
                    (void)_t4319;
                    U64 *_t4320 = malloc(sizeof(U64)); *_t4320 = U64_add(DEREF(path_idx), _t4319);
                    (void)_t4320;
                    ;
                    Str *cval = Array_get(args, _t4320);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4320, &(Bool){1});
                    U64 _t4321 = 2;
                    (void)_t4321;
                    U64 _t4322 = U64_add(DEREF(path_idx), _t4321);
                    (void)_t4322;
                    ;
                    *path_idx = _t4322;
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
    Str *_t4689 = Str_lit("help", 4ULL);
    (void)_t4689;
    Str *_t4690 = Str_lit("--help", 6ULL);
    (void)_t4690;
    Bool _t4691; { Bool *_hp = (Bool *)Str_eq(command, _t4689); _t4691 = *_hp; free(_hp); }
    (void)_t4691;
    Str_delete(_t4689, &(Bool){1});
    Bool _t4692; { Bool *_hp = (Bool *)Str_eq(command, _t4690); _t4692 = *_hp; free(_hp); }
    (void)_t4692;
    Str_delete(_t4690, &(Bool){1});
    Bool _t4693 = Bool_or(_t4691, _t4692);
    (void)_t4693;
    ;
    ;
    if (_t4693) {
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
    Str *_t4694 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4694;
    Str *core_path = Str_concat(bin_dir, _t4694);
    (void)core_path;
    Str_delete(_t4694, &(Bool){1});
    Str *_t4695 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4695;
    Str *ext_c_path = Str_concat(bin_dir, _t4695);
    (void)ext_c_path;
    Str_delete(_t4695, &(Bool){1});
    Str *_t4696 = Str_lit("Str", 3ULL);
    (void)_t4696;
    U64 _t4697; { U64 *_hp = (U64 *)Str_size(); _t4697 = *_hp; free(_hp); }
    (void)_t4697;
    Set *resolved = Set_new(_t4696, &(U64){_t4697});
    (void)resolved;
    Str_delete(_t4696, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4698; { U64 *_hp = (U64 *)Str_len(abs_path); _t4698 = *_hp; free(_hp); }
    (void)_t4698;
    U64 _t4699 = 0;
    (void)_t4699;
    Bool _t4700; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4698}, &(U64){_t4699}); _t4700 = *_hp; free(_hp); }
    (void)_t4700;
    ;
    ;
    if (_t4700) {
        U64 _t4346; { U64 *_hp = (U64 *)Str_len(abs_path); _t4346 = *_hp; free(_hp); }
        (void)_t4346;
        U64 _t4347 = 1;
        (void)_t4347;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4346, _t4347);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4339 = 0;
            (void)_t4339;
            U8 *_t4340 = Str_get(abs_path, last_slash);
            (void)_t4340;
            U8 _t4341 = 47;
            (void)_t4341;
            Bool _t4342; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4339}); _t4342 = *_hp; free(_hp); }
            (void)_t4342;
            ;
            Bool _t4343; { Bool *_hp = (Bool *)U8_neq(_t4340, &(U8){_t4341}); _t4343 = *_hp; free(_hp); }
            (void)_t4343;
            ;
            Bool _wcond4338 = Bool_and(_t4342, _t4343);
            (void)_wcond4338;
            ;
            ;
            if (_wcond4338) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4344 = 1;
            (void)_t4344;
            U64 _t4345 = U64_sub(DEREF(last_slash), _t4344);
            (void)_t4345;
            ;
            *last_slash = _t4345;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4348 = Str_clone(abs_path);
        (void)_t4348;
        Set_add(resolved, _t4348);
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
    U64 _t4701; { U64 *_hp = (U64 *)Str_len(core_abs); _t4701 = *_hp; free(_hp); }
    (void)_t4701;
    U64 _t4702 = 0;
    (void)_t4702;
    Bool _t4703; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4701}, &(U64){_t4702}); _t4703 = *_hp; free(_hp); }
    (void)_t4703;
    ;
    ;
    if (_t4703) {
        Bool _t4350; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4350 = *_hp; free(_hp); }
        (void)_t4350;
        if (_t4350) {
            Bool _t4349 = 1;
            (void)_t4349;
            skip_core = _t4349;
            ;
        }
        ;
        Str *_t4351 = Str_clone(core_abs);
        (void)_t4351;
        Set_add(resolved, _t4351);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4704; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4704 = *_hp; free(_hp); }
    (void)_t4704;
    U64 _t4705 = 0;
    (void)_t4705;
    Bool _t4706; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4704}, &(U64){_t4705}); _t4706 = *_hp; free(_hp); }
    (void)_t4706;
    ;
    ;
    Bool _t4707 = Bool_not(skip_core);
    (void)_t4707;
    Bool _t4708 = Bool_and(_t4706, _t4707);
    (void)_t4708;
    ;
    ;
    if (_t4708) {
        Str *_t4358 = Str_lit("/src/core", 9ULL);
        (void)_t4358;
        Str *core_dir = Str_concat(bin_dir, _t4358);
        (void)core_dir;
        Str_delete(_t4358, &(Bool){1});
        Str *_t4359 = Str_lit("", 0ULL);
        (void)_t4359;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4359); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4359, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4360 = 0;
        (void)_t4360;
        Bool _t4361; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4360}); _t4361 = *_hp; free(_hp); }
        (void)_t4361;
        ;
        ;
        if (_t4361) {
            Str *_t4352 = Str_lit("Str", 3ULL);
            (void)_t4352;
            U64 _t4353; { U64 *_hp = (U64 *)Str_size(); _t4353 = *_hp; free(_hp); }
            (void)_t4353;
            U64 _t4354 = 1;
            (void)_t4354;
            Array *_va86 = Array_new(_t4352, &(U64){_t4353}, &(U64){_t4354});
            (void)_va86;
            Str_delete(_t4352, &(Bool){1});
            ;
            ;
            U64 _t4355 = 0;
            (void)_t4355;
            Str *_t4356 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4356;
            Array_set(_va86, &(U64){_t4355}, _t4356);
            ;
            Str *_t4357 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4357;
            panic(_t4357, _va86);
            Str_delete(_t4357, &(Bool){1});
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
    Str *_t4709 = Str_lit("script", 6ULL);
    (void)_t4709;
    Mode *cur_mode = mode_resolve(_t4709);
    (void)cur_mode;
    Str_delete(_t4709, &(Bool){1});
    U64 _t4710; { U64 *_hp = (U64 *)Str_len(mode_str); _t4710 = *_hp; free(_hp); }
    (void)_t4710;
    U64 _t4711 = 0;
    (void)_t4711;
    Bool _t4712; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4710}, &(U64){_t4711}); _t4712 = *_hp; free(_hp); }
    (void)_t4712;
    ;
    ;
    if (_t4712) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4371; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4371 = *_hp; free(_hp); }
        (void)_t4371;
        U64 _t4372 = 0;
        (void)_t4372;
        Bool _t4373 = U64_eq(_t4371, _t4372);
        (void)_t4373;
        ;
        ;
        if (_t4373) {
            Str *_t4362 = Str_lit("Str", 3ULL);
            (void)_t4362;
            U64 _t4363; { U64 *_hp = (U64 *)Str_size(); _t4363 = *_hp; free(_hp); }
            (void)_t4363;
            U64 _t4364 = 1;
            (void)_t4364;
            Array *_va87 = Array_new(_t4362, &(U64){_t4363}, &(U64){_t4364});
            (void)_va87;
            Str_delete(_t4362, &(Bool){1});
            ;
            ;
            Str *_t4365 = Str_lit("unknown mode '", 14ULL);
            (void)_t4365;
            Str *_t4366 = Str_concat(_t4365, mode_str);
            (void)_t4366;
            Str_delete(_t4365, &(Bool){1});
            Str *_t4367 = Str_lit("'", 1ULL);
            (void)_t4367;
            U64 _t4368 = 0;
            (void)_t4368;
            Str *_t4369 = Str_concat(_t4366, _t4367);
            (void)_t4369;
            Str_delete(_t4366, &(Bool){1});
            Str_delete(_t4367, &(Bool){1});
            Array_set(_va87, &(U64){_t4368}, _t4369);
            ;
            Str *_t4370 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4370;
            panic(_t4370, _va87);
            Str_delete(_t4370, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4713; { U64 *_hp = (U64 *)Vec_len(imports); _t4713 = *_hp; free(_hp); }
    (void)_t4713;
    U64 _t4714 = 0;
    (void)_t4714;
    Bool _t4715; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4713}, &(U64){_t4714}); _t4715 = *_hp; free(_hp); }
    (void)_t4715;
    ;
    ;
    if (_t4715) {
        Str *_t4380 = Str_lit("/src/lib", 8ULL);
        (void)_t4380;
        Str *lib_dir = Str_concat(bin_dir, _t4380);
        (void)lib_dir;
        Str_delete(_t4380, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4381 = 0;
        (void)_t4381;
        Bool _t4382; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4381}); _t4382 = *_hp; free(_hp); }
        (void)_t4382;
        ;
        ;
        if (_t4382) {
            Str *_t4374 = Str_lit("Str", 3ULL);
            (void)_t4374;
            U64 _t4375; { U64 *_hp = (U64 *)Str_size(); _t4375 = *_hp; free(_hp); }
            (void)_t4375;
            U64 _t4376 = 1;
            (void)_t4376;
            Array *_va88 = Array_new(_t4374, &(U64){_t4375}, &(U64){_t4376});
            (void)_va88;
            Str_delete(_t4374, &(Bool){1});
            ;
            ;
            U64 _t4377 = 0;
            (void)_t4377;
            Str *_t4378 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4378;
            Array_set(_va88, &(U64){_t4377}, _t4378);
            ;
            Str *_t4379 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4379;
            panic(_t4379, _va88);
            Str_delete(_t4379, &(Bool){1});
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
    Bool _t4716 = Bool_not(skip_core);
    (void)_t4716;
    ;
    if (_t4716) {
        while (1) {
            U32 _t4384 = expr_nchildren(core_ast);
            (void)_t4384;
            Bool _wcond4383; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4384}); _wcond4383 = *_hp; free(_hp); }
            (void)_wcond4383;
            ;
            if (_wcond4383) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4385 = 1;
            (void)_t4385;
            U32 _t4386 = U32_add(DEREF(i), _t4385);
            (void)_t4386;
            ;
            *i = _t4386;
            ;
        }
        U32 _t4391 = 0;
        (void)_t4391;
        *i = _t4391;
        ;
        while (1) {
            U32 _t4388 = expr_vec_count(core_import_decls);
            (void)_t4388;
            Bool _wcond4387; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4388}); _wcond4387 = *_hp; free(_hp); }
            (void)_wcond4387;
            ;
            if (_wcond4387) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4389 = 1;
            (void)_t4389;
            U32 _t4390 = U32_add(DEREF(i), _t4389);
            (void)_t4390;
            ;
            *i = _t4390;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4717; { U64 *_hp = (U64 *)Str_len(auto_import); _t4717 = *_hp; free(_hp); }
    (void)_t4717;
    U64 _t4718 = 0;
    (void)_t4718;
    Bool _t4719; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4717}, &(U64){_t4718}); _t4719 = *_hp; free(_hp); }
    (void)_t4719;
    ;
    ;
    if (_t4719) {
        Str *_t4396 = Str_lit("/src/modes/", 11ULL);
        (void)_t4396;
        Str *_t4397 = Str_concat(bin_dir, _t4396);
        (void)_t4397;
        Str_delete(_t4396, &(Bool){1});
        Str *_t4398 = Str_concat(_t4397, auto_import);
        (void)_t4398;
        Str_delete(_t4397, &(Bool){1});
        Str *_t4399 = Str_lit(".til", 4ULL);
        (void)_t4399;
        Str *mode_til_path = Str_concat(_t4398, _t4399);
        (void)mode_til_path;
        Str_delete(_t4398, &(Bool){1});
        Str_delete(_t4399, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4400 = 0;
        (void)_t4400;
        *i = _t4400;
        ;
        while (1) {
            U32 _t4393 = expr_nchildren(mode_ast);
            (void)_t4393;
            Bool _wcond4392; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4393}); _wcond4392 = *_hp; free(_hp); }
            (void)_wcond4392;
            ;
            if (_wcond4392) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4394 = 1;
            (void)_t4394;
            U32 _t4395 = U32_add(DEREF(i), _t4394);
            (void)_t4395;
            ;
            *i = _t4395;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4720 = 0;
    (void)_t4720;
    *i = _t4720;
    ;
    while (1) {
        U32 _t4402 = expr_vec_count(import_decls);
        (void)_t4402;
        Bool _wcond4401; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4402}); _wcond4401 = *_hp; free(_hp); }
        (void)_wcond4401;
        ;
        if (_wcond4401) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4403 = 1;
        (void)_t4403;
        U32 _t4404 = U32_add(DEREF(i), _t4403);
        (void)_t4404;
        ;
        *i = _t4404;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4721 = 0;
    (void)_t4721;
    *i = _t4721;
    ;
    while (1) {
        U32 _t4406 = expr_nchildren(ast);
        (void)_t4406;
        Bool _wcond4405; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4406}); _wcond4405 = *_hp; free(_hp); }
        (void)_wcond4405;
        ;
        if (_wcond4405) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4407 = 1;
        (void)_t4407;
        U32 _t4408 = U32_add(DEREF(i), _t4407);
        (void)_t4408;
        ;
        *i = _t4408;
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
    U32 _t4722 = 0;
    (void)_t4722;
    *i = _t4722;
    ;
    while (1) {
        U32 _t4424 = expr_nchildren(ast);
        (void)_t4424;
        Bool _wcond4409; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4424}); _wcond4409 = *_hp; free(_hp); }
        (void)_wcond4409;
        ;
        if (_wcond4409) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4425 = expr_get_tag(stmt);
        (void)_t4425;
        U32 _t4426 = expr_nchildren(stmt);
        (void)_t4426;
        U32 _t4427 = 2;
        (void)_t4427;
        Bool _t4428 = I32_eq(_t4425, DEREF(NODE_FCALL));
        (void)_t4428;
        ;
        Bool _t4429 = U32_eq(_t4426, _t4427);
        (void)_t4429;
        ;
        ;
        U32 *_t4430 = malloc(sizeof(U32));
        *_t4430 = 0;
        (void)_t4430;
        Expr *_t4431 = expr_get_child(stmt, DEREF(_t4430));
        (void)_t4431;
        I32 _t4432 = expr_get_tag(_t4431);
        (void)_t4432;
        U32_delete(_t4430, &(Bool){1});
        Bool _t4433 = Bool_and(_t4428, _t4429);
        (void)_t4433;
        ;
        ;
        Bool _t4434 = I32_eq(_t4432, DEREF(NODE_IDENT));
        (void)_t4434;
        ;
        U32 *_t4435 = malloc(sizeof(U32));
        *_t4435 = 1;
        (void)_t4435;
        Expr *_t4436 = expr_get_child(stmt, DEREF(_t4435));
        (void)_t4436;
        I32 _t4437 = expr_get_tag(_t4436);
        (void)_t4437;
        U32_delete(_t4435, &(Bool){1});
        Bool _t4438 = Bool_and(_t4433, _t4434);
        (void)_t4438;
        ;
        ;
        Bool _t4439 = I32_eq(_t4437, DEREF(NODE_LITERAL_STR));
        (void)_t4439;
        ;
        Bool _t4440 = Bool_and(_t4438, _t4439);
        (void)_t4440;
        ;
        ;
        if (_t4440) {
            U32 *_t4418 = malloc(sizeof(U32));
            *_t4418 = 0;
            (void)_t4418;
            Expr *_t4419 = expr_get_child(stmt, DEREF(_t4418));
            (void)_t4419;
            Str *fname = expr_get_str_val(_t4419);
            (void)fname;
            U32 *_t4420 = malloc(sizeof(U32));
            *_t4420 = 1;
            (void)_t4420;
            Expr *_t4421 = expr_get_child(stmt, DEREF(_t4420));
            (void)_t4421;
            Str *arg = expr_get_str_val(_t4421);
            (void)arg;
            Str *_t4422 = Str_lit("link", 4ULL);
            (void)_t4422;
            Bool _t4423; { Bool *_hp = (Bool *)Str_eq(fname, _t4422); _t4423 = *_hp; free(_hp); }
            (void)_t4423;
            Str_delete(_t4422, &(Bool){1});
            if (_t4423) {
                Str *_t4410 = Str_lit(" -l", 3ULL);
                (void)_t4410;
                Str *_t4411 = Str_concat(link_flags, _t4410);
                (void)_t4411;
                Str_delete(_t4410, &(Bool){1});
                link_flags = Str_concat(_t4411, arg);
                Str_delete(_t4411, &(Bool){1});
            } else {
                Str *_t4416 = Str_lit("link_c", 6ULL);
                (void)_t4416;
                Bool _t4417; { Bool *_hp = (Bool *)Str_eq(fname, _t4416); _t4417 = *_hp; free(_hp); }
                (void)_t4417;
                Str_delete(_t4416, &(Bool){1});
                if (_t4417) {
                    U64 _t4413; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4413 = *_hp; free(_hp); }
                    (void)_t4413;
                    U64 _t4414 = 0;
                    (void)_t4414;
                    Bool _t4415; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4413}, &(U64){_t4414}); _t4415 = *_hp; free(_hp); }
                    (void)_t4415;
                    ;
                    ;
                    if (_t4415) {
                        Str *_t4412 = Str_lit(" ", 1ULL);
                        (void)_t4412;
                        link_c_paths = Str_concat(link_c_paths, _t4412);
                        Str_delete(_t4412, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4418, &(Bool){1});
            U32_delete(_t4420, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4441 = 1;
        (void)_t4441;
        U32 _t4442 = U32_add(DEREF(i), _t4441);
        (void)_t4442;
        ;
        *i = _t4442;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4723 = init_declarations(ast, scope);
    (void)_t4723;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4724 = 0;
    (void)_t4724;
    Bool _t4725; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4724}); _t4725 = *_hp; free(_hp); }
    (void)_t4725;
    ;
    if (_t4725) {
        Str *_t4443 = Str_lit("Str", 3ULL);
        (void)_t4443;
        U64 _t4444; { U64 *_hp = (U64 *)Str_size(); _t4444 = *_hp; free(_hp); }
        (void)_t4444;
        U64 _t4445 = 1;
        (void)_t4445;
        Array *_va89 = Array_new(_t4443, &(U64){_t4444}, &(U64){_t4445});
        (void)_va89;
        Str_delete(_t4443, &(Bool){1});
        ;
        ;
        Str *_t4446 = I32_to_str(&(I32){type_errors});
        (void)_t4446;
        Str *_t4447 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4447;
        U64 _t4448 = 0;
        (void)_t4448;
        Str *_t4449 = Str_concat(_t4446, _t4447);
        (void)_t4449;
        Str_delete(_t4446, &(Bool){1});
        Str_delete(_t4447, &(Bool){1});
        Array_set(_va89, &(U64){_t4448}, _t4449);
        ;
        Str *_t4450 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4450;
        panic(_t4450, _va89);
        Str_delete(_t4450, &(Bool){1});
    }
    ;
    ;
    Str *_t4726 = Str_lit("test", 4ULL);
    (void)_t4726;
    Str *_t4727 = Str_lit("test", 4ULL);
    (void)_t4727;
    Bool _t4728; { Bool *_hp = (Bool *)Str_eq(command, _t4726); _t4728 = *_hp; free(_hp); }
    (void)_t4728;
    Str_delete(_t4726, &(Bool){1});
    Bool _t4729; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4727); _t4729 = *_hp; free(_hp); }
    (void)_t4729;
    Str_delete(_t4727, &(Bool){1});
    Str *_t4730 = Str_lit("pure", 4ULL);
    (void)_t4730;
    Bool _t4731 = Bool_or(_t4728, _t4729);
    (void)_t4731;
    ;
    ;
    Bool _t4732; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4730); _t4732 = *_hp; free(_hp); }
    (void)_t4732;
    Str_delete(_t4730, &(Bool){1});
    Str *_t4733 = Str_lit("pura", 4ULL);
    (void)_t4733;
    Bool _t4734 = Bool_or(_t4731, _t4732);
    (void)_t4734;
    ;
    ;
    Bool _t4735; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4733); _t4735 = *_hp; free(_hp); }
    (void)_t4735;
    Str_delete(_t4733, &(Bool){1});
    Bool run_tests = Bool_or(_t4734, _t4735);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4736 = Str_lit("translate", 9ULL);
    (void)_t4736;
    Str *_t4737 = Str_lit("build", 5ULL);
    (void)_t4737;
    Bool _t4738; { Bool *_hp = (Bool *)Str_eq(command, _t4736); _t4738 = *_hp; free(_hp); }
    (void)_t4738;
    Str_delete(_t4736, &(Bool){1});
    Bool _t4739; { Bool *_hp = (Bool *)Str_eq(command, _t4737); _t4739 = *_hp; free(_hp); }
    (void)_t4739;
    Str_delete(_t4737, &(Bool){1});
    Bool _t4740; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4740 = *_hp; free(_hp); }
    (void)_t4740;
    Bool _t4741 = Bool_or(_t4738, _t4739);
    (void)_t4741;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4740, _t4741);
    (void)is_lib_target;
    ;
    ;
    U64 _t4742; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4742 = *_hp; free(_hp); }
    (void)_t4742;
    U64 _t4743 = 0;
    (void)_t4743;
    Bool _t4744 = Bool_not(is_lib_target);
    (void)_t4744;
    ;
    Bool _t4745 = U64_eq(_t4742, _t4743);
    (void)_t4745;
    ;
    ;
    Bool _t4746 = Bool_and(_t4744, _t4745);
    (void)_t4746;
    ;
    ;
    if (_t4746) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4747; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4747 = *_hp; free(_hp); }
    (void)_t4747;
    U64 _t4748 = 0;
    (void)_t4748;
    Bool _t4749; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4747}, &(U64){_t4748}); _t4749 = *_hp; free(_hp); }
    (void)_t4749;
    ;
    ;
    if (_t4749) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4750 = Str_lit("Str", 3ULL);
    (void)_t4750;
    U64 _t4751; { U64 *_hp = (U64 *)Str_size(); _t4751 = *_hp; free(_hp); }
    (void)_t4751;
    Vec *user_argv = Vec_new(_t4750, &(U64){_t4751});
    (void)user_argv;
    Str_delete(_t4750, &(Bool){1});
    ;
    U64 _t4752 = 1;
    (void)_t4752;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4752);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4467; { U64 *_hp = (U64 *)Array_len(args); _t4467 = *_hp; free(_hp); }
        (void)_t4467;
        Bool _wcond4451; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4467}); _wcond4451 = *_hp; free(_hp); }
        (void)_wcond4451;
        ;
        if (_wcond4451) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4468 = Str_lit("-l", 2ULL);
        (void)_t4468;
        Bool _t4469; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4468); _t4469 = *_hp; free(_hp); }
        (void)_t4469;
        Str_delete(_t4468, &(Bool){1});
        if (_t4469) {
            U64 _t4454 = 2;
            (void)_t4454;
            U64 _t4455; { U64 *_hp = (U64 *)Str_len(arg); _t4455 = *_hp; free(_hp); }
            (void)_t4455;
            Str *lib = Str_substr(arg, &(U64){_t4454}, &(U64){_t4455});
            (void)lib;
            ;
            ;
            U64 _t4456; { U64 *_hp = (U64 *)Str_len(lib); _t4456 = *_hp; free(_hp); }
            (void)_t4456;
            U64 _t4457 = 0;
            (void)_t4457;
            U64 _t4458 = 1;
            (void)_t4458;
            U64 _t4459 = U64_add(DEREF(ai), _t4458);
            (void)_t4459;
            ;
            U64 _t4460; { U64 *_hp = (U64 *)Array_len(args); _t4460 = *_hp; free(_hp); }
            (void)_t4460;
            Bool _t4461 = U64_eq(_t4456, _t4457);
            (void)_t4461;
            ;
            ;
            Bool _t4462; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4459}, &(U64){_t4460}); _t4462 = *_hp; free(_hp); }
            (void)_t4462;
            ;
            ;
            Bool _t4463 = Bool_and(_t4461, _t4462);
            (void)_t4463;
            ;
            ;
            if (_t4463) {
                U64 _t4452 = 1;
                (void)_t4452;
                U64 _t4453 = U64_add(DEREF(ai), _t4452);
                (void)_t4453;
                ;
                *ai = _t4453;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4464 = Str_lit(" -l", 3ULL);
            (void)_t4464;
            Str *_t4465 = Str_concat(link_flags, _t4464);
            (void)_t4465;
            Str_delete(_t4464, &(Bool){1});
            link_flags = Str_concat(_t4465, lib);
            Str_delete(_t4465, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4466 = Str_clone(arg);
            (void)_t4466;
            Vec_push(user_argv, _t4466);
        }
        ;
        U64 _t4470 = 1;
        (void)_t4470;
        U64 _t4471 = U64_add(DEREF(ai), _t4470);
        (void)_t4471;
        ;
        *ai = _t4471;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4753; { U64 *_hp = (U64 *)Str_len(link_flags); _t4753 = *_hp; free(_hp); }
    (void)_t4753;
    U64 _t4754 = 0;
    (void)_t4754;
    Bool _t4755; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4753}, &(U64){_t4754}); _t4755 = *_hp; free(_hp); }
    (void)_t4755;
    ;
    ;
    if (_t4755) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4756 = Str_lit("interpret", 9ULL);
    (void)_t4756;
    Str *_t4757 = Str_lit("test", 4ULL);
    (void)_t4757;
    Bool _t4758; { Bool *_hp = (Bool *)Str_eq(command, _t4756); _t4758 = *_hp; free(_hp); }
    (void)_t4758;
    Str_delete(_t4756, &(Bool){1});
    Bool _t4759; { Bool *_hp = (Bool *)Str_eq(command, _t4757); _t4759 = *_hp; free(_hp); }
    (void)_t4759;
    Str_delete(_t4757, &(Bool){1});
    Bool _t4760 = Bool_or(_t4758, _t4759);
    (void)_t4760;
    ;
    ;
    if (_t4760) {
        Str *_t4478 = Str_lit("interpret", 9ULL);
        (void)_t4478;
        Bool _t4479; { Bool *_hp = (Bool *)Str_eq(command, _t4478); _t4479 = *_hp; free(_hp); }
        (void)_t4479;
        Str_delete(_t4478, &(Bool){1});
        Bool _t4480 = Bool_and(is_lib_mode, _t4479);
        (void)_t4480;
        ;
        if (_t4480) {
            Str *_t4472 = Str_lit("Str", 3ULL);
            (void)_t4472;
            U64 _t4473; { U64 *_hp = (U64 *)Str_size(); _t4473 = *_hp; free(_hp); }
            (void)_t4473;
            U64 _t4474 = 1;
            (void)_t4474;
            Array *_va90 = Array_new(_t4472, &(U64){_t4473}, &(U64){_t4474});
            (void)_va90;
            Str_delete(_t4472, &(Bool){1});
            ;
            ;
            U64 _t4475 = 0;
            (void)_t4475;
            Str *_t4476 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4476;
            Array_set(_va90, &(U64){_t4475}, _t4476);
            ;
            Str *_t4477 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4477;
            panic(_t4477, _va90);
            Str_delete(_t4477, &(Bool){1});
        }
        ;
        I32 _t4481 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4481;
        result = _t4481;
        ;
    } else {
        Str *_t4674 = Str_lit("translate", 9ULL);
        (void)_t4674;
        Str *_t4675 = Str_lit("build", 5ULL);
        (void)_t4675;
        Bool _t4676; { Bool *_hp = (Bool *)Str_eq(command, _t4674); _t4676 = *_hp; free(_hp); }
        (void)_t4676;
        Str_delete(_t4674, &(Bool){1});
        Bool _t4677; { Bool *_hp = (Bool *)Str_eq(command, _t4675); _t4677 = *_hp; free(_hp); }
        (void)_t4677;
        Str_delete(_t4675, &(Bool){1});
        Str *_t4678 = Str_lit("run", 3ULL);
        (void)_t4678;
        Bool _t4679 = Bool_or(_t4676, _t4677);
        (void)_t4679;
        ;
        ;
        Bool _t4680; { Bool *_hp = (Bool *)Str_eq(command, _t4678); _t4680 = *_hp; free(_hp); }
        (void)_t4680;
        Str_delete(_t4678, &(Bool){1});
        Bool _t4681 = Bool_or(_t4679, _t4680);
        (void)_t4681;
        ;
        ;
        if (_t4681) {
            Str *_t4607 = Str_lit("run", 3ULL);
            (void)_t4607;
            Bool _t4608; { Bool *_hp = (Bool *)Str_eq(command, _t4607); _t4608 = *_hp; free(_hp); }
            (void)_t4608;
            Str_delete(_t4607, &(Bool){1});
            Bool _t4609 = Bool_and(is_lib_mode, _t4608);
            (void)_t4609;
            ;
            if (_t4609) {
                Str *_t4482 = Str_lit("Str", 3ULL);
                (void)_t4482;
                U64 _t4483; { U64 *_hp = (U64 *)Str_size(); _t4483 = *_hp; free(_hp); }
                (void)_t4483;
                U64 _t4484 = 1;
                (void)_t4484;
                Array *_va91 = Array_new(_t4482, &(U64){_t4483}, &(U64){_t4484});
                (void)_va91;
                Str_delete(_t4482, &(Bool){1});
                ;
                ;
                U64 _t4485 = 0;
                (void)_t4485;
                Str *_t4486 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4486;
                Array_set(_va91, &(U64){_t4485}, _t4486);
                ;
                Str *_t4487 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4487;
                panic(_t4487, _va91);
                Str_delete(_t4487, &(Bool){1});
            }
            ;
            Str *_t4610 = Str_lit("/", 1ULL);
            (void)_t4610;
            I64 *last_slash = Str_rfind(path, _t4610);
            (void)last_slash;
            Str_delete(_t4610, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4611 = 0;
            (void)_t4611;
            Bool _t4612; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4611}); _t4612 = *_hp; free(_hp); }
            (void)_t4612;
            ;
            if (_t4612) {
                I64 _t4488 = 1;
                (void)_t4488;
                I64 _t4489 = I64_add(DEREF(last_slash), _t4488);
                (void)_t4489;
                ;
                U64 _t4490; { U64 *_hp = (U64 *)Str_len(path); _t4490 = *_hp; free(_hp); }
                (void)_t4490;
                U64 _t4491 = I64_to_u64(DEREF(last_slash));
                (void)_t4491;
                U64 _t4492 = U64_sub(_t4490, _t4491);
                (void)_t4492;
                ;
                ;
                U64 _t4493 = 1;
                (void)_t4493;
                U64 _t4494 = I64_to_u64(_t4489);
                (void)_t4494;
                ;
                U64 _t4495 = U64_sub(_t4492, _t4493);
                (void)_t4495;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4494}, &(U64){_t4495});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4613 = Str_lit(".til", 4ULL);
            (void)_t4613;
            Bool _t4614; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4613); _t4614 = *_hp; free(_hp); }
            (void)_t4614;
            Str_delete(_t4613, &(Bool){1});
            if (_t4614) {
                U64 _t4496 = 4;
                (void)_t4496;
                U64 _t4497 = U64_sub(name_len, _t4496);
                (void)_t4497;
                ;
                name_len = _t4497;
                ;
            }
            ;
            U64 _t4615 = 0;
            (void)_t4615;
            Str *name = Str_substr(basename, &(U64){_t4615}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4616 = Str_lit("gen/til/", 8ULL);
            (void)_t4616;
            Str *_t4617 = Str_concat(_t4616, name);
            (void)_t4617;
            Str_delete(_t4616, &(Bool){1});
            Str *_t4618 = Str_lit(".c", 2ULL);
            (void)_t4618;
            Str *c_path = Str_concat(_t4617, _t4618);
            (void)c_path;
            Str_delete(_t4617, &(Bool){1});
            Str_delete(_t4618, &(Bool){1});
            U64 _t4619; { U64 *_hp = (U64 *)Str_len(custom_c); _t4619 = *_hp; free(_hp); }
            (void)_t4619;
            U64 _t4620 = 0;
            (void)_t4620;
            Bool _t4621; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4619}, &(U64){_t4620}); _t4621 = *_hp; free(_hp); }
            (void)_t4621;
            ;
            ;
            if (_t4621) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4622 = Str_lit("bin/til/", 8ULL);
            (void)_t4622;
            Str *bin_path = Str_concat(_t4622, name);
            (void)bin_path;
            Str_delete(_t4622, &(Bool){1});
            U64 _t4623; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4623 = *_hp; free(_hp); }
            (void)_t4623;
            U64 _t4624 = 0;
            (void)_t4624;
            Bool _t4625; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4623}, &(U64){_t4624}); _t4625 = *_hp; free(_hp); }
            (void)_t4625;
            ;
            ;
            if (_t4625) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4626 = Str_lit("run", 3ULL);
            (void)_t4626;
            Bool _t4627; { Bool *_hp = (Bool *)Str_eq(command, _t4626); _t4627 = *_hp; free(_hp); }
            (void)_t4627;
            Str_delete(_t4626, &(Bool){1});
            Bool _t4628; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4628 = *_hp; free(_hp); }
            (void)_t4628;
            Bool _t4629 = Bool_not(_t4627);
            (void)_t4629;
            ;
            Bool do_lib = Bool_and(_t4628, _t4629);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4498 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4498;
                I32 _t4499 = til_system(_t4498);
                (void)_t4499;
                Str_delete(_t4498, &(Bool){1});
                ;
            } else {
                Str *_t4504 = Str_lit("/", 1ULL);
                (void)_t4504;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4504); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4504, &(Bool){1});
                Str *_t4505 = Str_lit("/", 1ULL);
                (void)_t4505;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4505); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4505, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4506 = 0;
                (void)_t4506;
                Bool _t4507; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4506}); _t4507 = *_hp; free(_hp); }
                (void)_t4507;
                ;
                if (_t4507) {
                    U64 _t4500 = 0;
                    (void)_t4500;
                    U64 _t4501 = I64_to_u64(cp_slash);
                    (void)_t4501;
                    cp_dir = Str_substr(c_path, &(U64){_t4500}, &(U64){_t4501});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4508 = 0;
                (void)_t4508;
                Bool _t4509; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4508}); _t4509 = *_hp; free(_hp); }
                (void)_t4509;
                ;
                if (_t4509) {
                    U64 _t4502 = 0;
                    (void)_t4502;
                    U64 _t4503 = I64_to_u64(bp_slash);
                    (void)_t4503;
                    bp_dir = Str_substr(bin_path, &(U64){_t4502}, &(U64){_t4503});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4510 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4510;
                Str *_t4511 = Str_concat(_t4510, cp_dir);
                (void)_t4511;
                Str_delete(_t4510, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4512 = Str_lit(" ", 1ULL);
                (void)_t4512;
                Str *_t4513 = Str_concat(_t4511, _t4512);
                (void)_t4513;
                Str_delete(_t4511, &(Bool){1});
                Str_delete(_t4512, &(Bool){1});
                Str *_t4514 = Str_concat(_t4513, bp_dir);
                (void)_t4514;
                Str_delete(_t4513, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4515 = til_system(_t4514);
                (void)_t4515;
                Str_delete(_t4514, &(Bool){1});
                ;
            }
            I32 _t4630 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4630;
            result = _t4630;
            ;
            I32 _t4631 = 0;
            (void)_t4631;
            Bool _t4632 = I32_eq(result, _t4631);
            (void)_t4632;
            ;
            Bool _t4633 = Bool_and(_t4632, do_lib);
            (void)_t4633;
            ;
            if (_t4633) {
                Str *_t4572 = Str_lit("gen/til/", 8ULL);
                (void)_t4572;
                Str *_t4573 = Str_concat(_t4572, name);
                (void)_t4573;
                Str_delete(_t4572, &(Bool){1});
                Str *_t4574 = Str_lit(".h", 2ULL);
                (void)_t4574;
                Str *h_path = Str_concat(_t4573, _t4574);
                (void)h_path;
                Str_delete(_t4573, &(Bool){1});
                Str_delete(_t4574, &(Bool){1});
                Str *_t4575 = Str_lit("gen/til/", 8ULL);
                (void)_t4575;
                Str *_t4576 = Str_concat(_t4575, name);
                (void)_t4576;
                Str_delete(_t4575, &(Bool){1});
                Str *_t4577 = Str_lit(".til", 4ULL);
                (void)_t4577;
                Str *til_path = Str_concat(_t4576, _t4577);
                (void)til_path;
                Str_delete(_t4576, &(Bool){1});
                Str_delete(_t4577, &(Bool){1});
                I32 _t4578 = build_header(ast, h_path);
                (void)_t4578;
                result = _t4578;
                ;
                I32 _t4579 = 0;
                (void)_t4579;
                Bool _t4580 = I32_eq(result, _t4579);
                (void)_t4580;
                ;
                if (_t4580) {
                    I32 _t4516 = build_til_binding(ast, til_path, name);
                    (void)_t4516;
                    result = _t4516;
                    ;
                }
                ;
                I32 _t4581 = 0;
                (void)_t4581;
                Str *_t4582 = Str_lit("translate", 9ULL);
                (void)_t4582;
                Bool _t4583 = I32_eq(result, _t4581);
                (void)_t4583;
                ;
                Bool _t4584; { Bool *_hp = (Bool *)Str_eq(command, _t4582); _t4584 = *_hp; free(_hp); }
                (void)_t4584;
                Str_delete(_t4582, &(Bool){1});
                Bool _t4585 = Bool_and(_t4583, _t4584);
                (void)_t4585;
                ;
                ;
                if (_t4585) {
                    Str *_t4517 = Str_lit("Str", 3ULL);
                    (void)_t4517;
                    U64 _t4518; { U64 *_hp = (U64 *)Str_size(); _t4518 = *_hp; free(_hp); }
                    (void)_t4518;
                    U64 _t4519 = 1;
                    (void)_t4519;
                    Array *_va92 = Array_new(_t4517, &(U64){_t4518}, &(U64){_t4519});
                    (void)_va92;
                    Str_delete(_t4517, &(Bool){1});
                    ;
                    ;
                    Str *_t4520 = Str_lit("Generated: ", 11ULL);
                    (void)_t4520;
                    U64 _t4521 = 0;
                    (void)_t4521;
                    Str *_t4522 = Str_concat(_t4520, c_path);
                    (void)_t4522;
                    Str_delete(_t4520, &(Bool){1});
                    Array_set(_va92, &(U64){_t4521}, _t4522);
                    ;
                    println(_va92);
                    Str *_t4523 = Str_lit("Str", 3ULL);
                    (void)_t4523;
                    U64 _t4524; { U64 *_hp = (U64 *)Str_size(); _t4524 = *_hp; free(_hp); }
                    (void)_t4524;
                    U64 _t4525 = 1;
                    (void)_t4525;
                    Array *_va93 = Array_new(_t4523, &(U64){_t4524}, &(U64){_t4525});
                    (void)_va93;
                    Str_delete(_t4523, &(Bool){1});
                    ;
                    ;
                    Str *_t4526 = Str_lit("Generated: ", 11ULL);
                    (void)_t4526;
                    U64 _t4527 = 0;
                    (void)_t4527;
                    Str *_t4528 = Str_concat(_t4526, h_path);
                    (void)_t4528;
                    Str_delete(_t4526, &(Bool){1});
                    Array_set(_va93, &(U64){_t4527}, _t4528);
                    ;
                    println(_va93);
                    Str *_t4529 = Str_lit("Str", 3ULL);
                    (void)_t4529;
                    U64 _t4530; { U64 *_hp = (U64 *)Str_size(); _t4530 = *_hp; free(_hp); }
                    (void)_t4530;
                    U64 _t4531 = 1;
                    (void)_t4531;
                    Array *_va94 = Array_new(_t4529, &(U64){_t4530}, &(U64){_t4531});
                    (void)_va94;
                    Str_delete(_t4529, &(Bool){1});
                    ;
                    ;
                    Str *_t4532 = Str_lit("Generated: ", 11ULL);
                    (void)_t4532;
                    U64 _t4533 = 0;
                    (void)_t4533;
                    Str *_t4534 = Str_concat(_t4532, til_path);
                    (void)_t4534;
                    Str_delete(_t4532, &(Bool){1});
                    Array_set(_va94, &(U64){_t4533}, _t4534);
                    ;
                    println(_va94);
                }
                ;
                I32 _t4586 = 0;
                (void)_t4586;
                Str *_t4587 = Str_lit("build", 5ULL);
                (void)_t4587;
                Bool _t4588 = I32_eq(result, _t4586);
                (void)_t4588;
                ;
                Bool _t4589; { Bool *_hp = (Bool *)Str_eq(command, _t4587); _t4589 = *_hp; free(_hp); }
                (void)_t4589;
                Str_delete(_t4587, &(Bool){1});
                Bool _t4590 = Bool_and(_t4588, _t4589);
                (void)_t4590;
                ;
                ;
                if (_t4590) {
                    I32 _t4569 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4569;
                    result = _t4569;
                    ;
                    I32 _t4570 = 0;
                    (void)_t4570;
                    Bool _t4571 = I32_eq(result, _t4570);
                    (void)_t4571;
                    ;
                    if (_t4571) {
                        Str *_t4535 = Str_lit("Str", 3ULL);
                        (void)_t4535;
                        U64 _t4536; { U64 *_hp = (U64 *)Str_size(); _t4536 = *_hp; free(_hp); }
                        (void)_t4536;
                        U64 _t4537 = 1;
                        (void)_t4537;
                        Array *_va95 = Array_new(_t4535, &(U64){_t4536}, &(U64){_t4537});
                        (void)_va95;
                        Str_delete(_t4535, &(Bool){1});
                        ;
                        ;
                        Str *_t4538 = Str_lit("Generated: ", 11ULL);
                        (void)_t4538;
                        U64 _t4539 = 0;
                        (void)_t4539;
                        Str *_t4540 = Str_concat(_t4538, c_path);
                        (void)_t4540;
                        Str_delete(_t4538, &(Bool){1});
                        Array_set(_va95, &(U64){_t4539}, _t4540);
                        ;
                        println(_va95);
                        Str *_t4541 = Str_lit("Str", 3ULL);
                        (void)_t4541;
                        U64 _t4542; { U64 *_hp = (U64 *)Str_size(); _t4542 = *_hp; free(_hp); }
                        (void)_t4542;
                        U64 _t4543 = 1;
                        (void)_t4543;
                        Array *_va96 = Array_new(_t4541, &(U64){_t4542}, &(U64){_t4543});
                        (void)_va96;
                        Str_delete(_t4541, &(Bool){1});
                        ;
                        ;
                        Str *_t4544 = Str_lit("Generated: ", 11ULL);
                        (void)_t4544;
                        U64 _t4545 = 0;
                        (void)_t4545;
                        Str *_t4546 = Str_concat(_t4544, h_path);
                        (void)_t4546;
                        Str_delete(_t4544, &(Bool){1});
                        Array_set(_va96, &(U64){_t4545}, _t4546);
                        ;
                        println(_va96);
                        Str *_t4547 = Str_lit("Str", 3ULL);
                        (void)_t4547;
                        U64 _t4548; { U64 *_hp = (U64 *)Str_size(); _t4548 = *_hp; free(_hp); }
                        (void)_t4548;
                        U64 _t4549 = 1;
                        (void)_t4549;
                        Array *_va97 = Array_new(_t4547, &(U64){_t4548}, &(U64){_t4549});
                        (void)_va97;
                        Str_delete(_t4547, &(Bool){1});
                        ;
                        ;
                        Str *_t4550 = Str_lit("Generated: ", 11ULL);
                        (void)_t4550;
                        U64 _t4551 = 0;
                        (void)_t4551;
                        Str *_t4552 = Str_concat(_t4550, til_path);
                        (void)_t4552;
                        Str_delete(_t4550, &(Bool){1});
                        Array_set(_va97, &(U64){_t4551}, _t4552);
                        ;
                        println(_va97);
                        Str *_t4553 = Str_lit("Str", 3ULL);
                        (void)_t4553;
                        U64 _t4554; { U64 *_hp = (U64 *)Str_size(); _t4554 = *_hp; free(_hp); }
                        (void)_t4554;
                        U64 _t4555 = 1;
                        (void)_t4555;
                        Array *_va98 = Array_new(_t4553, &(U64){_t4554}, &(U64){_t4555});
                        (void)_va98;
                        Str_delete(_t4553, &(Bool){1});
                        ;
                        ;
                        Str *_t4556 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4556;
                        Str *_t4557 = Str_concat(_t4556, name);
                        (void)_t4557;
                        Str_delete(_t4556, &(Bool){1});
                        Str *_t4558 = Str_lit(".so", 3ULL);
                        (void)_t4558;
                        U64 _t4559 = 0;
                        (void)_t4559;
                        Str *_t4560 = Str_concat(_t4557, _t4558);
                        (void)_t4560;
                        Str_delete(_t4557, &(Bool){1});
                        Str_delete(_t4558, &(Bool){1});
                        Array_set(_va98, &(U64){_t4559}, _t4560);
                        ;
                        println(_va98);
                        Str *_t4561 = Str_lit("Str", 3ULL);
                        (void)_t4561;
                        U64 _t4562; { U64 *_hp = (U64 *)Str_size(); _t4562 = *_hp; free(_hp); }
                        (void)_t4562;
                        U64 _t4563 = 1;
                        (void)_t4563;
                        Array *_va99 = Array_new(_t4561, &(U64){_t4562}, &(U64){_t4563});
                        (void)_va99;
                        Str_delete(_t4561, &(Bool){1});
                        ;
                        ;
                        Str *_t4564 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4564;
                        Str *_t4565 = Str_concat(_t4564, name);
                        (void)_t4565;
                        Str_delete(_t4564, &(Bool){1});
                        Str *_t4566 = Str_lit(".a", 2ULL);
                        (void)_t4566;
                        U64 _t4567 = 0;
                        (void)_t4567;
                        Str *_t4568 = Str_concat(_t4565, _t4566);
                        (void)_t4568;
                        Str_delete(_t4565, &(Bool){1});
                        Str_delete(_t4566, &(Bool){1});
                        Array_set(_va99, &(U64){_t4567}, _t4568);
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
            I32 _t4634 = 0;
            (void)_t4634;
            Bool _t4635 = I32_eq(result, _t4634);
            (void)_t4635;
            ;
            Bool _t4636 = Bool_not(do_lib);
            (void)_t4636;
            Str *_t4637 = Str_lit("translate", 9ULL);
            (void)_t4637;
            Bool _t4638 = Bool_and(_t4635, _t4636);
            (void)_t4638;
            ;
            ;
            Bool _t4639; { Bool *_hp = (Bool *)Str_eq(command, _t4637); _t4639 = *_hp; free(_hp); }
            (void)_t4639;
            Str_delete(_t4637, &(Bool){1});
            Bool _t4640 = Bool_and(_t4638, _t4639);
            (void)_t4640;
            ;
            ;
            if (_t4640) {
                Str *_t4591 = Str_lit("Str", 3ULL);
                (void)_t4591;
                U64 _t4592; { U64 *_hp = (U64 *)Str_size(); _t4592 = *_hp; free(_hp); }
                (void)_t4592;
                U64 _t4593 = 1;
                (void)_t4593;
                Array *_va100 = Array_new(_t4591, &(U64){_t4592}, &(U64){_t4593});
                (void)_va100;
                Str_delete(_t4591, &(Bool){1});
                ;
                ;
                Str *_t4594 = Str_lit("Generated: ", 11ULL);
                (void)_t4594;
                U64 _t4595 = 0;
                (void)_t4595;
                Str *_t4596 = Str_concat(_t4594, c_path);
                (void)_t4596;
                Str_delete(_t4594, &(Bool){1});
                Array_set(_va100, &(U64){_t4595}, _t4596);
                ;
                println(_va100);
            }
            ;
            I32 _t4641 = 0;
            (void)_t4641;
            Bool _t4642 = I32_eq(result, _t4641);
            (void)_t4642;
            ;
            Bool _t4643 = Bool_not(do_lib);
            (void)_t4643;
            Str *_t4644 = Str_lit("translate", 9ULL);
            (void)_t4644;
            Bool _t4645; { Bool *_hp = (Bool *)Str_eq(command, _t4644); _t4645 = *_hp; free(_hp); }
            (void)_t4645;
            Str_delete(_t4644, &(Bool){1});
            Bool _t4646 = Bool_and(_t4642, _t4643);
            (void)_t4646;
            ;
            ;
            Bool _t4647 = Bool_not(_t4645);
            (void)_t4647;
            ;
            Bool _t4648 = Bool_and(_t4646, _t4647);
            (void)_t4648;
            ;
            ;
            if (_t4648) {
                I32 _t4597 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4597;
                result = _t4597;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4649 = 0;
            (void)_t4649;
            Bool _t4650 = I32_eq(result, _t4649);
            (void)_t4650;
            ;
            Bool _t4651 = Bool_not(do_lib);
            (void)_t4651;
            ;
            Str *_t4652 = Str_lit("run", 3ULL);
            (void)_t4652;
            Bool _t4653 = Bool_and(_t4650, _t4651);
            (void)_t4653;
            ;
            ;
            Bool _t4654; { Bool *_hp = (Bool *)Str_eq(command, _t4652); _t4654 = *_hp; free(_hp); }
            (void)_t4654;
            Str_delete(_t4652, &(Bool){1});
            Bool _t4655 = Bool_and(_t4653, _t4654);
            (void)_t4655;
            ;
            ;
            if (_t4655) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4599; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4599 = *_hp; free(_hp); }
                    (void)_t4599;
                    Bool _wcond4598; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4599}); _wcond4598 = *_hp; free(_hp); }
                    (void)_wcond4598;
                    ;
                    if (_wcond4598) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4600 = Str_lit(" '", 2ULL);
                    (void)_t4600;
                    Str *_t4601 = Str_concat(cmd, _t4600);
                    (void)_t4601;
                    Str_delete(_t4600, &(Bool){1});
                    Str *_t4602 = Str_concat(_t4601, uarg);
                    (void)_t4602;
                    Str_delete(_t4601, &(Bool){1});
                    Str *_t4603 = Str_lit("'", 1ULL);
                    (void)_t4603;
                    cmd = Str_concat(_t4602, _t4603);
                    Str_delete(_t4602, &(Bool){1});
                    Str_delete(_t4603, &(Bool){1});
                    U64 _t4604 = 1;
                    (void)_t4604;
                    U64 _t4605 = U64_add(DEREF(ui), _t4604);
                    (void)_t4605;
                    ;
                    *ui = _t4605;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4606 = til_system(cmd);
                (void)_t4606;
                Str_delete(cmd, &(Bool){1});
                result = _t4606;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4672 = Str_lit("ast", 3ULL);
            (void)_t4672;
            Bool _t4673; { Bool *_hp = (Bool *)Str_eq(command, _t4672); _t4673 = *_hp; free(_hp); }
            (void)_t4673;
            Str_delete(_t4672, &(Bool){1});
            if (_t4673) {
                Str *_t4656 = Str_lit("Str", 3ULL);
                (void)_t4656;
                U64 _t4657; { U64 *_hp = (U64 *)Str_size(); _t4657 = *_hp; free(_hp); }
                (void)_t4657;
                U64 _t4658 = 1;
                (void)_t4658;
                Array *_va101 = Array_new(_t4656, &(U64){_t4657}, &(U64){_t4658});
                (void)_va101;
                Str_delete(_t4656, &(Bool){1});
                ;
                ;
                Str *_t4659 = Str_lit("mode: ", 6ULL);
                (void)_t4659;
                U64 _t4660 = 0;
                (void)_t4660;
                Str *_t4661 = Str_concat(_t4659, &cur_mode->name);
                (void)_t4661;
                Str_delete(_t4659, &(Bool){1});
                Array_set(_va101, &(U64){_t4660}, _t4661);
                ;
                println(_va101);
                U32 _t4662 = 0;
                (void)_t4662;
                ast_print(ast, _t4662);
                ;
            } else {
                Str *_t4663 = Str_lit("Str", 3ULL);
                (void)_t4663;
                U64 _t4664; { U64 *_hp = (U64 *)Str_size(); _t4664 = *_hp; free(_hp); }
                (void)_t4664;
                U64 _t4665 = 1;
                (void)_t4665;
                Array *_va102 = Array_new(_t4663, &(U64){_t4664}, &(U64){_t4665});
                (void)_va102;
                Str_delete(_t4663, &(Bool){1});
                ;
                ;
                Str *_t4666 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4666;
                Str *_t4667 = Str_concat(_t4666, command);
                (void)_t4667;
                Str_delete(_t4666, &(Bool){1});
                Str *_t4668 = Str_lit("'", 1ULL);
                (void)_t4668;
                U64 _t4669 = 0;
                (void)_t4669;
                Str *_t4670 = Str_concat(_t4667, _t4668);
                (void)_t4670;
                Str_delete(_t4667, &(Bool){1});
                Str_delete(_t4668, &(Bool){1});
                Array_set(_va102, &(U64){_t4669}, _t4670);
                ;
                println(_va102);
                usage();
                I32 _t4671 = 1;
                (void)_t4671;
                result = _t4671;
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
    I64 _t4761 = I32_to_i64(result);
    (void)_t4761;
    ;
    exit(_t4761);
    ;
    return 0;
}

