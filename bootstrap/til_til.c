#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4191 = Str_lit("Str", 3ULL);
    (void)_t4191;
    U64 _t4192; { U64 *_hp = (U64 *)Str_size(); _t4192 = *_hp; free(_hp); }
    (void)_t4192;
    Vec *paths = Vec_new(_t4191, &(U64){_t4192});
    (void)paths;
    Str_delete(_t4191, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4166 = expr_nchildren(body);
        (void)_t4166;
        Bool _wcond4162; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4166}); _wcond4162 = *_hp; free(_hp); }
        (void)_wcond4162;
        ;
        if (_wcond4162) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4167 = expr_get_tag(stmt);
        (void)_t4167;
        U32 _t4168 = expr_nchildren(stmt);
        (void)_t4168;
        U32 _t4169 = 2;
        (void)_t4169;
        Bool _t4170 = I32_eq(_t4167, DEREF(NODE_FCALL));
        (void)_t4170;
        ;
        Bool _t4171 = U32_eq(_t4168, _t4169);
        (void)_t4171;
        ;
        ;
        U32 *_t4172 = malloc(sizeof(U32));
        *_t4172 = 0;
        (void)_t4172;
        Expr *_t4173 = expr_get_child(stmt, DEREF(_t4172));
        (void)_t4173;
        I32 _t4174 = expr_get_tag(_t4173);
        (void)_t4174;
        U32_delete(_t4172, &(Bool){1});
        Bool _t4175 = Bool_and(_t4170, _t4171);
        (void)_t4175;
        ;
        ;
        Bool _t4176 = I32_eq(_t4174, DEREF(NODE_IDENT));
        (void)_t4176;
        ;
        U32 *_t4177 = malloc(sizeof(U32));
        *_t4177 = 0;
        (void)_t4177;
        Expr *_t4178 = expr_get_child(stmt, DEREF(_t4177));
        (void)_t4178;
        Str *_t4179 = expr_get_str_val(_t4178);
        (void)_t4179;
        Str *_t4180 = Str_lit("import", 6ULL);
        (void)_t4180;
        Bool _t4181 = Bool_and(_t4175, _t4176);
        (void)_t4181;
        ;
        ;
        Bool _t4182; { Bool *_hp = (Bool *)Str_eq(_t4179, _t4180); _t4182 = *_hp; free(_hp); }
        (void)_t4182;
        U32_delete(_t4177, &(Bool){1});
        Str_delete(_t4180, &(Bool){1});
        U32 *_t4183 = malloc(sizeof(U32));
        *_t4183 = 1;
        (void)_t4183;
        Expr *_t4184 = expr_get_child(stmt, DEREF(_t4183));
        (void)_t4184;
        I32 _t4185 = expr_get_tag(_t4184);
        (void)_t4185;
        U32_delete(_t4183, &(Bool){1});
        Bool _t4186 = Bool_and(_t4181, _t4182);
        (void)_t4186;
        ;
        ;
        Bool _t4187 = I32_eq(_t4185, DEREF(NODE_LITERAL_STR));
        (void)_t4187;
        ;
        Bool _t4188 = Bool_and(_t4186, _t4187);
        (void)_t4188;
        ;
        ;
        if (_t4188) {
            U32 *_t4163 = malloc(sizeof(U32));
            *_t4163 = 1;
            (void)_t4163;
            Expr *_t4164 = expr_get_child(stmt, DEREF(_t4163));
            (void)_t4164;
            Str *path = expr_get_str_val(_t4164);
            (void)path;
            Str *_t4165 = Str_clone(path);
            (void)_t4165;
            U32_delete(_t4163, &(Bool){1});
            Vec_push(paths, _t4165);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4189 = 1;
        (void)_t4189;
        U32 _t4190 = U32_add(DEREF(i), _t4189);
        (void)_t4190;
        ;
        *i = _t4190;
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
        U64 _t4243 = 0;
        (void)_t4243;
        U64 _t4244; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4244 = *_hp; free(_hp); }
        (void)_t4244;
        Range *_fc4193 = Range_new(_t4243, _t4244);
        (void)_fc4193;
        ;
        ;
        U64 _fi4193 = 0;
        (void)_fi4193;
        while (1) {
            U64 _t4223; { U64 *_hp = (U64 *)Range_len(_fc4193); _t4223 = *_hp; free(_hp); }
            (void)_t4223;
            Bool _wcond4194; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4193}, &(U64){_t4223}); _wcond4194 = *_hp; free(_hp); }
            (void)_wcond4194;
            ;
            if (_wcond4194) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4193, _fi4193);
            (void)i;
            U64 _t4224 = 1;
            (void)_t4224;
            U64 _t4225 = U64_add(_fi4193, _t4224);
            (void)_t4225;
            ;
            _fi4193 = _t4225;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4226 = Str_lit("/", 1ULL);
            (void)_t4226;
            Str *_t4227 = Str_concat(base_dir, _t4226);
            (void)_t4227;
            Str_delete(_t4226, &(Bool){1});
            Str *try_path = Str_concat(_t4227, import_path);
            (void)try_path;
            Str_delete(_t4227, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4228 = Str_lit("", 0ULL);
            (void)_t4228;
            U64 _t4229; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4229 = *_hp; free(_hp); }
            (void)_t4229;
            U64 _t4230 = 0;
            (void)_t4230;
            Bool _t4231; { Bool *_hp = (Bool *)Str_eq(abs, _t4228); _t4231 = *_hp; free(_hp); }
            (void)_t4231;
            Str_delete(_t4228, &(Bool){1});
            Bool _t4232; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4229}, &(U64){_t4230}); _t4232 = *_hp; free(_hp); }
            (void)_t4232;
            ;
            ;
            Bool _t4233 = Bool_and(_t4231, _t4232);
            (void)_t4233;
            ;
            ;
            if (_t4233) {
                Str *_t4195 = Str_lit("/", 1ULL);
                (void)_t4195;
                Str *_t4196 = Str_concat(lib_dir, _t4195);
                (void)_t4196;
                Str_delete(_t4195, &(Bool){1});
                try_path = Str_concat(_t4196, import_path);
                Str_delete(_t4196, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4234 = Str_lit("", 0ULL);
            (void)_t4234;
            Bool _t4235; { Bool *_hp = (Bool *)Str_eq(abs, _t4234); _t4235 = *_hp; free(_hp); }
            (void)_t4235;
            Str_delete(_t4234, &(Bool){1});
            if (_t4235) {
                Str *_t4197 = Str_lit("Str", 3ULL);
                (void)_t4197;
                U64 _t4198; { U64 *_hp = (U64 *)Str_size(); _t4198 = *_hp; free(_hp); }
                (void)_t4198;
                U64 _t4199 = 1;
                (void)_t4199;
                Array *_va75 = Array_new(_t4197, &(U64){_t4198}, &(U64){_t4199});
                (void)_va75;
                Str_delete(_t4197, &(Bool){1});
                ;
                ;
                Str *_t4200 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4200;
                Str *_t4201 = Str_concat(_t4200, import_path);
                (void)_t4201;
                Str_delete(_t4200, &(Bool){1});
                Str *_t4202 = Str_lit("' (from ", 8ULL);
                (void)_t4202;
                Str *_t4203 = Str_concat(_t4201, _t4202);
                (void)_t4203;
                Str_delete(_t4201, &(Bool){1});
                Str_delete(_t4202, &(Bool){1});
                Str *_t4204 = Str_concat(_t4203, base_dir);
                (void)_t4204;
                Str_delete(_t4203, &(Bool){1});
                Str *_t4205 = Str_lit("/)", 2ULL);
                (void)_t4205;
                U64 _t4206 = 0;
                (void)_t4206;
                Str *_t4207 = Str_concat(_t4204, _t4205);
                (void)_t4207;
                Str_delete(_t4204, &(Bool){1});
                Str_delete(_t4205, &(Bool){1});
                Array_set(_va75, &(U64){_t4206}, _t4207);
                ;
                println(_va75);
                I64 _t4208 = 1;
                (void)_t4208;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4193, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4208; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4236; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4236 = *_hp; free(_hp); }
            (void)_t4236;
            if (_t4236) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4237 = Str_clone(abs);
            (void)_t4237;
            Set_add(resolved_set, _t4237);
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
            U64 _t4238; { U64 *_hp = (U64 *)Str_len(abs); _t4238 = *_hp; free(_hp); }
            (void)_t4238;
            U64 _t4239 = 1;
            (void)_t4239;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4238, _t4239);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4210 = 0;
                (void)_t4210;
                U8 *_t4211 = Str_get(abs, last_slash);
                (void)_t4211;
                U8 _t4212 = 47;
                (void)_t4212;
                Bool _t4213; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4210}); _t4213 = *_hp; free(_hp); }
                (void)_t4213;
                ;
                Bool _t4214; { Bool *_hp = (Bool *)U8_neq(_t4211, &(U8){_t4212}); _t4214 = *_hp; free(_hp); }
                (void)_t4214;
                ;
                Bool _wcond4209 = Bool_and(_t4213, _t4214);
                (void)_wcond4209;
                ;
                ;
                if (_wcond4209) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4215 = 1;
                (void)_t4215;
                U64 _t4216 = U64_sub(DEREF(last_slash), _t4215);
                (void)_t4216;
                ;
                *last_slash = _t4216;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4240; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4240 = *_hp; free(_hp); }
            (void)_t4240;
            U64 _t4241 = 0;
            (void)_t4241;
            Bool _t4242; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4240}, &(U64){_t4241}); _t4242 = *_hp; free(_hp); }
            (void)_t4242;
            ;
            ;
            if (_t4242) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4217 = 0;
                (void)_t4217;
                Bool _t4218; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4217}); _t4218 = *_hp; free(_hp); }
                (void)_t4218;
                ;
                if (_t4218) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4193, &(Bool){1});
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
                U32 _t4220 = expr_nchildren(sub_ast);
                (void)_t4220;
                Bool _wcond4219; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4220}); _wcond4219 = *_hp; free(_hp); }
                (void)_wcond4219;
                ;
                if (_wcond4219) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4221 = 1;
                (void)_t4221;
                U32 _t4222 = U32_add(DEREF(k), _t4221);
                (void)_t4222;
                ;
                *k = _t4222;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4193, &(Bool){1});
        ;
    }
    I64 _t4245 = 0;
    (void)_t4245;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4245; return _r; }
}

void usage(void) {
    Str *_t4246 = Str_lit("Str", 3ULL);
    (void)_t4246;
    U64 _t4247; { U64 *_hp = (U64 *)Str_size(); _t4247 = *_hp; free(_hp); }
    (void)_t4247;
    U64 _t4248 = 1;
    (void)_t4248;
    Array *_va76 = Array_new(_t4246, &(U64){_t4247}, &(U64){_t4248});
    (void)_va76;
    Str_delete(_t4246, &(Bool){1});
    ;
    ;
    U64 _t4249 = 0;
    (void)_t4249;
    Str *_t4250 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4250;
    Array_set(_va76, &(U64){_t4249}, _t4250);
    ;
    println(_va76);
    Str *_t4251 = Str_lit("Str", 3ULL);
    (void)_t4251;
    U64 _t4252; { U64 *_hp = (U64 *)Str_size(); _t4252 = *_hp; free(_hp); }
    (void)_t4252;
    U64 _t4253 = 1;
    (void)_t4253;
    Array *_va77 = Array_new(_t4251, &(U64){_t4252}, &(U64){_t4253});
    (void)_va77;
    Str_delete(_t4251, &(Bool){1});
    ;
    ;
    U64 _t4254 = 0;
    (void)_t4254;
    Str *_t4255 = Str_lit("", 0ULL);
    (void)_t4255;
    Array_set(_va77, &(U64){_t4254}, _t4255);
    ;
    println(_va77);
    Str *_t4256 = Str_lit("Str", 3ULL);
    (void)_t4256;
    U64 _t4257; { U64 *_hp = (U64 *)Str_size(); _t4257 = *_hp; free(_hp); }
    (void)_t4257;
    U64 _t4258 = 1;
    (void)_t4258;
    Array *_va78 = Array_new(_t4256, &(U64){_t4257}, &(U64){_t4258});
    (void)_va78;
    Str_delete(_t4256, &(Bool){1});
    ;
    ;
    U64 _t4259 = 0;
    (void)_t4259;
    Str *_t4260 = Str_lit("Commands:", 9ULL);
    (void)_t4260;
    Array_set(_va78, &(U64){_t4259}, _t4260);
    ;
    println(_va78);
    Str *_t4261 = Str_lit("Str", 3ULL);
    (void)_t4261;
    U64 _t4262; { U64 *_hp = (U64 *)Str_size(); _t4262 = *_hp; free(_hp); }
    (void)_t4262;
    U64 _t4263 = 1;
    (void)_t4263;
    Array *_va79 = Array_new(_t4261, &(U64){_t4262}, &(U64){_t4263});
    (void)_va79;
    Str_delete(_t4261, &(Bool){1});
    ;
    ;
    U64 _t4264 = 0;
    (void)_t4264;
    Str *_t4265 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4265;
    Array_set(_va79, &(U64){_t4264}, _t4265);
    ;
    println(_va79);
    Str *_t4266 = Str_lit("Str", 3ULL);
    (void)_t4266;
    U64 _t4267; { U64 *_hp = (U64 *)Str_size(); _t4267 = *_hp; free(_hp); }
    (void)_t4267;
    U64 _t4268 = 1;
    (void)_t4268;
    Array *_va80 = Array_new(_t4266, &(U64){_t4267}, &(U64){_t4268});
    (void)_va80;
    Str_delete(_t4266, &(Bool){1});
    ;
    ;
    U64 _t4269 = 0;
    (void)_t4269;
    Str *_t4270 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4270;
    Array_set(_va80, &(U64){_t4269}, _t4270);
    ;
    println(_va80);
    Str *_t4271 = Str_lit("Str", 3ULL);
    (void)_t4271;
    U64 _t4272; { U64 *_hp = (U64 *)Str_size(); _t4272 = *_hp; free(_hp); }
    (void)_t4272;
    U64 _t4273 = 1;
    (void)_t4273;
    Array *_va81 = Array_new(_t4271, &(U64){_t4272}, &(U64){_t4273});
    (void)_va81;
    Str_delete(_t4271, &(Bool){1});
    ;
    ;
    U64 _t4274 = 0;
    (void)_t4274;
    Str *_t4275 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4275;
    Array_set(_va81, &(U64){_t4274}, _t4275);
    ;
    println(_va81);
    Str *_t4276 = Str_lit("Str", 3ULL);
    (void)_t4276;
    U64 _t4277; { U64 *_hp = (U64 *)Str_size(); _t4277 = *_hp; free(_hp); }
    (void)_t4277;
    U64 _t4278 = 1;
    (void)_t4278;
    Array *_va82 = Array_new(_t4276, &(U64){_t4277}, &(U64){_t4278});
    (void)_va82;
    Str_delete(_t4276, &(Bool){1});
    ;
    ;
    U64 _t4279 = 0;
    (void)_t4279;
    Str *_t4280 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4280;
    Array_set(_va82, &(U64){_t4279}, _t4280);
    ;
    println(_va82);
    Str *_t4281 = Str_lit("Str", 3ULL);
    (void)_t4281;
    U64 _t4282; { U64 *_hp = (U64 *)Str_size(); _t4282 = *_hp; free(_hp); }
    (void)_t4282;
    U64 _t4283 = 1;
    (void)_t4283;
    Array *_va83 = Array_new(_t4281, &(U64){_t4282}, &(U64){_t4283});
    (void)_va83;
    Str_delete(_t4281, &(Bool){1});
    ;
    ;
    U64 _t4284 = 0;
    (void)_t4284;
    Str *_t4285 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4285;
    Array_set(_va83, &(U64){_t4284}, _t4285);
    ;
    println(_va83);
    Str *_t4286 = Str_lit("Str", 3ULL);
    (void)_t4286;
    U64 _t4287; { U64 *_hp = (U64 *)Str_size(); _t4287 = *_hp; free(_hp); }
    (void)_t4287;
    U64 _t4288 = 1;
    (void)_t4288;
    Array *_va84 = Array_new(_t4286, &(U64){_t4287}, &(U64){_t4288});
    (void)_va84;
    Str_delete(_t4286, &(Bool){1});
    ;
    ;
    U64 _t4289 = 0;
    (void)_t4289;
    Str *_t4290 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4290;
    Array_set(_va84, &(U64){_t4289}, _t4290);
    ;
    println(_va84);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4296 = 1;
    (void)_t4296;
    e->is_core = _t4296;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4292 = expr_nchildren(e);
        (void)_t4292;
        Bool _wcond4291; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4292}); _wcond4291 = *_hp; free(_hp); }
        (void)_wcond4291;
        ;
        if (_wcond4291) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4293 = expr_get_child(e, DEREF(i));
        (void)_t4293;
        mark_core(_t4293);
        U32 _t4294 = 1;
        (void)_t4294;
        U32 _t4295 = U32_add(DEREF(i), _t4294);
        (void)_t4295;
        ;
        *i = _t4295;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4756 = malloc(sizeof(I64));
    *_t4756 = 0;
    (void)_t4756;
    _t4757 = malloc(sizeof(I64));
    *_t4757 = 1;
    (void)_t4757;
    _t4758 = malloc(sizeof(I64)); *_t4758 = I64_sub(DEREF(_t4756), DEREF(_t4757));
    (void)_t4758;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4758));
    (void)CAP_LIT;
    _t4759 = malloc(sizeof(I64));
    *_t4759 = 0;
    (void)_t4759;
    _t4760 = malloc(sizeof(I64));
    *_t4760 = 2;
    (void)_t4760;
    _t4761 = malloc(sizeof(I64)); *_t4761 = I64_sub(DEREF(_t4759), DEREF(_t4760));
    (void)_t4761;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4761));
    (void)CAP_VIEW;
    _t4762 = Str_lit("Str", 3ULL);
    (void)_t4762;
    _t4763 = Str_size();
    (void)_t4763;
    _t4764 = Str_lit("Mode", 4ULL);
    (void)_t4764;
    _t4765 = Mode_size();
    (void)_t4765;
    core_modes = Map_new(_t4762, _t4763, _t4764, _t4765);
    (void)core_modes;
    _t4766 = malloc(sizeof(Bool));
    *_t4766 = 0;
    (void)_t4766;
    _t4767 = malloc(sizeof(Bool));
    *_t4767 = 0;
    (void)_t4767;
    _t4768 = malloc(sizeof(Bool));
    *_t4768 = 0;
    (void)_t4768;
    _t4769 = malloc(sizeof(Bool));
    *_t4769 = 0;
    (void)_t4769;
    _t4770 = Str_lit("script", 6ULL);
    (void)_t4770;
    _t4771 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4771->name = *_ca; free(_ca); }
    _t4771->needs_main = DEREF(_t4766);
    _t4771->decls_only = DEREF(_t4767);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4771->auto_import = *_ca; free(_ca); }
    _t4771->is_pure = DEREF(_t4768);
    _t4771->debug_prints = DEREF(_t4769);
    (void)_t4771;
    _t4772 = malloc(sizeof(Bool));
    *_t4772 = 1;
    (void)_t4772;
    _t4773 = malloc(sizeof(Bool));
    *_t4773 = 1;
    (void)_t4773;
    _t4774 = malloc(sizeof(Bool));
    *_t4774 = 0;
    (void)_t4774;
    _t4775 = malloc(sizeof(Bool));
    *_t4775 = 0;
    (void)_t4775;
    _t4776 = Str_lit("cli", 3ULL);
    (void)_t4776;
    _t4777 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4777->name = *_ca; free(_ca); }
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
    _t4782 = Str_lit("gui", 3ULL);
    (void)_t4782;
    _t4783 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4783->name = *_ca; free(_ca); }
    _t4783->needs_main = DEREF(_t4778);
    _t4783->decls_only = DEREF(_t4779);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4783->auto_import = *_ca; free(_ca); }
    _t4783->is_pure = DEREF(_t4780);
    _t4783->debug_prints = DEREF(_t4781);
    (void)_t4783;
    _t4784 = malloc(sizeof(Bool));
    *_t4784 = 0;
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
    _t4788 = Str_lit("test", 4ULL);
    (void)_t4788;
    _t4789 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4789->name = *_ca; free(_ca); }
    _t4789->needs_main = DEREF(_t4784);
    _t4789->decls_only = DEREF(_t4785);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4789->auto_import = *_ca; free(_ca); }
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
    *_t4792 = 1;
    (void)_t4792;
    _t4793 = malloc(sizeof(Bool));
    *_t4793 = 0;
    (void)_t4793;
    _t4794 = Str_lit("pure", 4ULL);
    (void)_t4794;
    _t4795 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4795->name = *_ca; free(_ca); }
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
    *_t4799 = 1;
    (void)_t4799;
    _t4800 = Str_lit("pura", 4ULL);
    (void)_t4800;
    _t4801 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4801->name = *_ca; free(_ca); }
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
    *_t4804 = 0;
    (void)_t4804;
    _t4805 = malloc(sizeof(Bool));
    *_t4805 = 0;
    (void)_t4805;
    _t4806 = Str_lit("lib", 3ULL);
    (void)_t4806;
    _t4807 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4807->name = *_ca; free(_ca); }
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
    *_t4811 = 1;
    (void)_t4811;
    _t4812 = Str_lit("liba", 4ULL);
    (void)_t4812;
    _t4813 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4813->name = *_ca; free(_ca); }
    _t4813->needs_main = DEREF(_t4808);
    _t4813->decls_only = DEREF(_t4809);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4813->auto_import = *_ca; free(_ca); }
    _t4813->is_pure = DEREF(_t4810);
    _t4813->debug_prints = DEREF(_t4811);
    (void)_t4813;
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
    U64 _t4676; { U64 *_hp = (U64 *)Array_len(args); _t4676 = *_hp; free(_hp); }
    (void)_t4676;
    U64 _t4677 = 0;
    (void)_t4677;
    Bool _t4678 = U64_eq(_t4676, _t4677);
    (void)_t4678;
    ;
    ;
    if (_t4678) {
        usage();
        Str *_t4297 = Str_lit("Str", 3ULL);
        (void)_t4297;
        U64 _t4298; { U64 *_hp = (U64 *)Str_size(); _t4298 = *_hp; free(_hp); }
        (void)_t4298;
        U64 _t4299 = 1;
        (void)_t4299;
        Array *_va85 = Array_new(_t4297, &(U64){_t4298}, &(U64){_t4299});
        (void)_va85;
        Str_delete(_t4297, &(Bool){1});
        ;
        ;
        U64 _t4300 = 0;
        (void)_t4300;
        Str *_t4301 = Str_lit("no arguments", 12ULL);
        (void)_t4301;
        Array_set(_va85, &(U64){_t4300}, _t4301);
        ;
        Str *_t4302 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4302;
        panic(_t4302, _va85);
        Str_delete(_t4302, &(Bool){1});
    }
    ;
    U64 *_t4679 = malloc(sizeof(U64));
    *_t4679 = 0;
    (void)_t4679;
    Str *cmd_ref = Array_get(args, _t4679);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4679, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4680; { U64 *_hp = (U64 *)Array_len(args); _t4680 = *_hp; free(_hp); }
    (void)_t4680;
    U64 _t4681 = 1;
    (void)_t4681;
    Bool _t4682 = U64_eq(_t4680, _t4681);
    (void)_t4682;
    ;
    ;
    if (_t4682) {
        Str *_t4303 = Str_lit("help", 4ULL);
        (void)_t4303;
        Str *_t4304 = Str_lit("--help", 6ULL);
        (void)_t4304;
        Bool _t4305; { Bool *_hp = (Bool *)Str_eq(command, _t4303); _t4305 = *_hp; free(_hp); }
        (void)_t4305;
        Str_delete(_t4303, &(Bool){1});
        Bool _t4306; { Bool *_hp = (Bool *)Str_eq(command, _t4304); _t4306 = *_hp; free(_hp); }
        (void)_t4306;
        Str_delete(_t4304, &(Bool){1});
        Bool _t4307 = Bool_or(_t4305, _t4306);
        (void)_t4307;
        ;
        ;
        if (_t4307) {
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
            U64 _t4324; { U64 *_hp = (U64 *)Array_len(args); _t4324 = *_hp; free(_hp); }
            (void)_t4324;
            Bool _wcond4308; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4324}); _wcond4308 = *_hp; free(_hp); }
            (void)_wcond4308;
            ;
            if (_wcond4308) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4325 = Str_lit("-o", 2ULL);
            (void)_t4325;
            U64 _t4326 = 1;
            (void)_t4326;
            U64 _t4327 = U64_add(DEREF(path_idx), _t4326);
            (void)_t4327;
            ;
            U64 _t4328; { U64 *_hp = (U64 *)Array_len(args); _t4328 = *_hp; free(_hp); }
            (void)_t4328;
            Bool _t4329; { Bool *_hp = (Bool *)Str_eq(flag, _t4325); _t4329 = *_hp; free(_hp); }
            (void)_t4329;
            Str_delete(_t4325, &(Bool){1});
            Bool _t4330; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4327}, &(U64){_t4328}); _t4330 = *_hp; free(_hp); }
            (void)_t4330;
            ;
            ;
            Bool _t4331 = Bool_and(_t4329, _t4330);
            (void)_t4331;
            ;
            ;
            if (_t4331) {
                U64 _t4309 = 1;
                (void)_t4309;
                U64 *_t4310 = malloc(sizeof(U64)); *_t4310 = U64_add(DEREF(path_idx), _t4309);
                (void)_t4310;
                ;
                Str *oval = Array_get(args, _t4310);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4310, &(Bool){1});
                U64 _t4311 = 2;
                (void)_t4311;
                U64 _t4312 = U64_add(DEREF(path_idx), _t4311);
                (void)_t4312;
                ;
                *path_idx = _t4312;
                ;
            } else {
                Str *_t4317 = Str_lit("-c", 2ULL);
                (void)_t4317;
                U64 _t4318 = 1;
                (void)_t4318;
                U64 _t4319 = U64_add(DEREF(path_idx), _t4318);
                (void)_t4319;
                ;
                U64 _t4320; { U64 *_hp = (U64 *)Array_len(args); _t4320 = *_hp; free(_hp); }
                (void)_t4320;
                Bool _t4321; { Bool *_hp = (Bool *)Str_eq(flag, _t4317); _t4321 = *_hp; free(_hp); }
                (void)_t4321;
                Str_delete(_t4317, &(Bool){1});
                Bool _t4322; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4319}, &(U64){_t4320}); _t4322 = *_hp; free(_hp); }
                (void)_t4322;
                ;
                ;
                Bool _t4323 = Bool_and(_t4321, _t4322);
                (void)_t4323;
                ;
                ;
                if (_t4323) {
                    U64 _t4313 = 1;
                    (void)_t4313;
                    U64 *_t4314 = malloc(sizeof(U64)); *_t4314 = U64_add(DEREF(path_idx), _t4313);
                    (void)_t4314;
                    ;
                    Str *cval = Array_get(args, _t4314);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4314, &(Bool){1});
                    U64 _t4315 = 2;
                    (void)_t4315;
                    U64 _t4316 = U64_add(DEREF(path_idx), _t4315);
                    (void)_t4316;
                    ;
                    *path_idx = _t4316;
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
    Str *_t4683 = Str_lit("help", 4ULL);
    (void)_t4683;
    Str *_t4684 = Str_lit("--help", 6ULL);
    (void)_t4684;
    Bool _t4685; { Bool *_hp = (Bool *)Str_eq(command, _t4683); _t4685 = *_hp; free(_hp); }
    (void)_t4685;
    Str_delete(_t4683, &(Bool){1});
    Bool _t4686; { Bool *_hp = (Bool *)Str_eq(command, _t4684); _t4686 = *_hp; free(_hp); }
    (void)_t4686;
    Str_delete(_t4684, &(Bool){1});
    Bool _t4687 = Bool_or(_t4685, _t4686);
    (void)_t4687;
    ;
    ;
    if (_t4687) {
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
    Str *_t4688 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4688;
    Str *core_path = Str_concat(bin_dir, _t4688);
    (void)core_path;
    Str_delete(_t4688, &(Bool){1});
    Str *_t4689 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4689;
    Str *ext_c_path = Str_concat(bin_dir, _t4689);
    (void)ext_c_path;
    Str_delete(_t4689, &(Bool){1});
    Str *_t4690 = Str_lit("Str", 3ULL);
    (void)_t4690;
    U64 _t4691; { U64 *_hp = (U64 *)Str_size(); _t4691 = *_hp; free(_hp); }
    (void)_t4691;
    Set *resolved = Set_new(_t4690, &(U64){_t4691});
    (void)resolved;
    Str_delete(_t4690, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4692; { U64 *_hp = (U64 *)Str_len(abs_path); _t4692 = *_hp; free(_hp); }
    (void)_t4692;
    U64 _t4693 = 0;
    (void)_t4693;
    Bool _t4694; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4692}, &(U64){_t4693}); _t4694 = *_hp; free(_hp); }
    (void)_t4694;
    ;
    ;
    if (_t4694) {
        U64 _t4340; { U64 *_hp = (U64 *)Str_len(abs_path); _t4340 = *_hp; free(_hp); }
        (void)_t4340;
        U64 _t4341 = 1;
        (void)_t4341;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4340, _t4341);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4333 = 0;
            (void)_t4333;
            U8 *_t4334 = Str_get(abs_path, last_slash);
            (void)_t4334;
            U8 _t4335 = 47;
            (void)_t4335;
            Bool _t4336; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4333}); _t4336 = *_hp; free(_hp); }
            (void)_t4336;
            ;
            Bool _t4337; { Bool *_hp = (Bool *)U8_neq(_t4334, &(U8){_t4335}); _t4337 = *_hp; free(_hp); }
            (void)_t4337;
            ;
            Bool _wcond4332 = Bool_and(_t4336, _t4337);
            (void)_wcond4332;
            ;
            ;
            if (_wcond4332) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4338 = 1;
            (void)_t4338;
            U64 _t4339 = U64_sub(DEREF(last_slash), _t4338);
            (void)_t4339;
            ;
            *last_slash = _t4339;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4342 = Str_clone(abs_path);
        (void)_t4342;
        Set_add(resolved, _t4342);
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
    U64 _t4695; { U64 *_hp = (U64 *)Str_len(core_abs); _t4695 = *_hp; free(_hp); }
    (void)_t4695;
    U64 _t4696 = 0;
    (void)_t4696;
    Bool _t4697; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4695}, &(U64){_t4696}); _t4697 = *_hp; free(_hp); }
    (void)_t4697;
    ;
    ;
    if (_t4697) {
        Bool _t4344; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4344 = *_hp; free(_hp); }
        (void)_t4344;
        if (_t4344) {
            Bool _t4343 = 1;
            (void)_t4343;
            skip_core = _t4343;
            ;
        }
        ;
        Str *_t4345 = Str_clone(core_abs);
        (void)_t4345;
        Set_add(resolved, _t4345);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4698; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4698 = *_hp; free(_hp); }
    (void)_t4698;
    U64 _t4699 = 0;
    (void)_t4699;
    Bool _t4700; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4698}, &(U64){_t4699}); _t4700 = *_hp; free(_hp); }
    (void)_t4700;
    ;
    ;
    Bool _t4701 = Bool_not(skip_core);
    (void)_t4701;
    Bool _t4702 = Bool_and(_t4700, _t4701);
    (void)_t4702;
    ;
    ;
    if (_t4702) {
        Str *_t4352 = Str_lit("/src/core", 9ULL);
        (void)_t4352;
        Str *core_dir = Str_concat(bin_dir, _t4352);
        (void)core_dir;
        Str_delete(_t4352, &(Bool){1});
        Str *_t4353 = Str_lit("", 0ULL);
        (void)_t4353;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4353); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4353, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4354 = 0;
        (void)_t4354;
        Bool _t4355; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4354}); _t4355 = *_hp; free(_hp); }
        (void)_t4355;
        ;
        ;
        if (_t4355) {
            Str *_t4346 = Str_lit("Str", 3ULL);
            (void)_t4346;
            U64 _t4347; { U64 *_hp = (U64 *)Str_size(); _t4347 = *_hp; free(_hp); }
            (void)_t4347;
            U64 _t4348 = 1;
            (void)_t4348;
            Array *_va86 = Array_new(_t4346, &(U64){_t4347}, &(U64){_t4348});
            (void)_va86;
            Str_delete(_t4346, &(Bool){1});
            ;
            ;
            U64 _t4349 = 0;
            (void)_t4349;
            Str *_t4350 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4350;
            Array_set(_va86, &(U64){_t4349}, _t4350);
            ;
            Str *_t4351 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4351;
            panic(_t4351, _va86);
            Str_delete(_t4351, &(Bool){1});
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
    Str *_t4703 = Str_lit("script", 6ULL);
    (void)_t4703;
    Mode *cur_mode = mode_resolve(_t4703);
    (void)cur_mode;
    Str_delete(_t4703, &(Bool){1});
    U64 _t4704; { U64 *_hp = (U64 *)Str_len(mode_str); _t4704 = *_hp; free(_hp); }
    (void)_t4704;
    U64 _t4705 = 0;
    (void)_t4705;
    Bool _t4706; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4704}, &(U64){_t4705}); _t4706 = *_hp; free(_hp); }
    (void)_t4706;
    ;
    ;
    if (_t4706) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4365; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4365 = *_hp; free(_hp); }
        (void)_t4365;
        U64 _t4366 = 0;
        (void)_t4366;
        Bool _t4367 = U64_eq(_t4365, _t4366);
        (void)_t4367;
        ;
        ;
        if (_t4367) {
            Str *_t4356 = Str_lit("Str", 3ULL);
            (void)_t4356;
            U64 _t4357; { U64 *_hp = (U64 *)Str_size(); _t4357 = *_hp; free(_hp); }
            (void)_t4357;
            U64 _t4358 = 1;
            (void)_t4358;
            Array *_va87 = Array_new(_t4356, &(U64){_t4357}, &(U64){_t4358});
            (void)_va87;
            Str_delete(_t4356, &(Bool){1});
            ;
            ;
            Str *_t4359 = Str_lit("unknown mode '", 14ULL);
            (void)_t4359;
            Str *_t4360 = Str_concat(_t4359, mode_str);
            (void)_t4360;
            Str_delete(_t4359, &(Bool){1});
            Str *_t4361 = Str_lit("'", 1ULL);
            (void)_t4361;
            U64 _t4362 = 0;
            (void)_t4362;
            Str *_t4363 = Str_concat(_t4360, _t4361);
            (void)_t4363;
            Str_delete(_t4360, &(Bool){1});
            Str_delete(_t4361, &(Bool){1});
            Array_set(_va87, &(U64){_t4362}, _t4363);
            ;
            Str *_t4364 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4364;
            panic(_t4364, _va87);
            Str_delete(_t4364, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4707; { U64 *_hp = (U64 *)Vec_len(imports); _t4707 = *_hp; free(_hp); }
    (void)_t4707;
    U64 _t4708 = 0;
    (void)_t4708;
    Bool _t4709; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4707}, &(U64){_t4708}); _t4709 = *_hp; free(_hp); }
    (void)_t4709;
    ;
    ;
    if (_t4709) {
        Str *_t4374 = Str_lit("/src/lib", 8ULL);
        (void)_t4374;
        Str *lib_dir = Str_concat(bin_dir, _t4374);
        (void)lib_dir;
        Str_delete(_t4374, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4375 = 0;
        (void)_t4375;
        Bool _t4376; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4375}); _t4376 = *_hp; free(_hp); }
        (void)_t4376;
        ;
        ;
        if (_t4376) {
            Str *_t4368 = Str_lit("Str", 3ULL);
            (void)_t4368;
            U64 _t4369; { U64 *_hp = (U64 *)Str_size(); _t4369 = *_hp; free(_hp); }
            (void)_t4369;
            U64 _t4370 = 1;
            (void)_t4370;
            Array *_va88 = Array_new(_t4368, &(U64){_t4369}, &(U64){_t4370});
            (void)_va88;
            Str_delete(_t4368, &(Bool){1});
            ;
            ;
            U64 _t4371 = 0;
            (void)_t4371;
            Str *_t4372 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4372;
            Array_set(_va88, &(U64){_t4371}, _t4372);
            ;
            Str *_t4373 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4373;
            panic(_t4373, _va88);
            Str_delete(_t4373, &(Bool){1});
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
    Bool _t4710 = Bool_not(skip_core);
    (void)_t4710;
    ;
    if (_t4710) {
        while (1) {
            U32 _t4378 = expr_nchildren(core_ast);
            (void)_t4378;
            Bool _wcond4377; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4378}); _wcond4377 = *_hp; free(_hp); }
            (void)_wcond4377;
            ;
            if (_wcond4377) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4379 = 1;
            (void)_t4379;
            U32 _t4380 = U32_add(DEREF(i), _t4379);
            (void)_t4380;
            ;
            *i = _t4380;
            ;
        }
        U32 _t4385 = 0;
        (void)_t4385;
        *i = _t4385;
        ;
        while (1) {
            U32 _t4382 = expr_vec_count(core_import_decls);
            (void)_t4382;
            Bool _wcond4381; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4382}); _wcond4381 = *_hp; free(_hp); }
            (void)_wcond4381;
            ;
            if (_wcond4381) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4383 = 1;
            (void)_t4383;
            U32 _t4384 = U32_add(DEREF(i), _t4383);
            (void)_t4384;
            ;
            *i = _t4384;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4711; { U64 *_hp = (U64 *)Str_len(auto_import); _t4711 = *_hp; free(_hp); }
    (void)_t4711;
    U64 _t4712 = 0;
    (void)_t4712;
    Bool _t4713; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4711}, &(U64){_t4712}); _t4713 = *_hp; free(_hp); }
    (void)_t4713;
    ;
    ;
    if (_t4713) {
        Str *_t4390 = Str_lit("/src/modes/", 11ULL);
        (void)_t4390;
        Str *_t4391 = Str_concat(bin_dir, _t4390);
        (void)_t4391;
        Str_delete(_t4390, &(Bool){1});
        Str *_t4392 = Str_concat(_t4391, auto_import);
        (void)_t4392;
        Str_delete(_t4391, &(Bool){1});
        Str *_t4393 = Str_lit(".til", 4ULL);
        (void)_t4393;
        Str *mode_til_path = Str_concat(_t4392, _t4393);
        (void)mode_til_path;
        Str_delete(_t4392, &(Bool){1});
        Str_delete(_t4393, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4394 = 0;
        (void)_t4394;
        *i = _t4394;
        ;
        while (1) {
            U32 _t4387 = expr_nchildren(mode_ast);
            (void)_t4387;
            Bool _wcond4386; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4387}); _wcond4386 = *_hp; free(_hp); }
            (void)_wcond4386;
            ;
            if (_wcond4386) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4388 = 1;
            (void)_t4388;
            U32 _t4389 = U32_add(DEREF(i), _t4388);
            (void)_t4389;
            ;
            *i = _t4389;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4714 = 0;
    (void)_t4714;
    *i = _t4714;
    ;
    while (1) {
        U32 _t4396 = expr_vec_count(import_decls);
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
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4397 = 1;
        (void)_t4397;
        U32 _t4398 = U32_add(DEREF(i), _t4397);
        (void)_t4398;
        ;
        *i = _t4398;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4715 = 0;
    (void)_t4715;
    *i = _t4715;
    ;
    while (1) {
        U32 _t4400 = expr_nchildren(ast);
        (void)_t4400;
        Bool _wcond4399; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4400}); _wcond4399 = *_hp; free(_hp); }
        (void)_wcond4399;
        ;
        if (_wcond4399) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4401 = 1;
        (void)_t4401;
        U32 _t4402 = U32_add(DEREF(i), _t4401);
        (void)_t4402;
        ;
        *i = _t4402;
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
    U32 _t4716 = 0;
    (void)_t4716;
    *i = _t4716;
    ;
    while (1) {
        U32 _t4418 = expr_nchildren(ast);
        (void)_t4418;
        Bool _wcond4403; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4418}); _wcond4403 = *_hp; free(_hp); }
        (void)_wcond4403;
        ;
        if (_wcond4403) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4419 = expr_get_tag(stmt);
        (void)_t4419;
        U32 _t4420 = expr_nchildren(stmt);
        (void)_t4420;
        U32 _t4421 = 2;
        (void)_t4421;
        Bool _t4422 = I32_eq(_t4419, DEREF(NODE_FCALL));
        (void)_t4422;
        ;
        Bool _t4423 = U32_eq(_t4420, _t4421);
        (void)_t4423;
        ;
        ;
        U32 *_t4424 = malloc(sizeof(U32));
        *_t4424 = 0;
        (void)_t4424;
        Expr *_t4425 = expr_get_child(stmt, DEREF(_t4424));
        (void)_t4425;
        I32 _t4426 = expr_get_tag(_t4425);
        (void)_t4426;
        U32_delete(_t4424, &(Bool){1});
        Bool _t4427 = Bool_and(_t4422, _t4423);
        (void)_t4427;
        ;
        ;
        Bool _t4428 = I32_eq(_t4426, DEREF(NODE_IDENT));
        (void)_t4428;
        ;
        U32 *_t4429 = malloc(sizeof(U32));
        *_t4429 = 1;
        (void)_t4429;
        Expr *_t4430 = expr_get_child(stmt, DEREF(_t4429));
        (void)_t4430;
        I32 _t4431 = expr_get_tag(_t4430);
        (void)_t4431;
        U32_delete(_t4429, &(Bool){1});
        Bool _t4432 = Bool_and(_t4427, _t4428);
        (void)_t4432;
        ;
        ;
        Bool _t4433 = I32_eq(_t4431, DEREF(NODE_LITERAL_STR));
        (void)_t4433;
        ;
        Bool _t4434 = Bool_and(_t4432, _t4433);
        (void)_t4434;
        ;
        ;
        if (_t4434) {
            U32 *_t4412 = malloc(sizeof(U32));
            *_t4412 = 0;
            (void)_t4412;
            Expr *_t4413 = expr_get_child(stmt, DEREF(_t4412));
            (void)_t4413;
            Str *fname = expr_get_str_val(_t4413);
            (void)fname;
            U32 *_t4414 = malloc(sizeof(U32));
            *_t4414 = 1;
            (void)_t4414;
            Expr *_t4415 = expr_get_child(stmt, DEREF(_t4414));
            (void)_t4415;
            Str *arg = expr_get_str_val(_t4415);
            (void)arg;
            Str *_t4416 = Str_lit("link", 4ULL);
            (void)_t4416;
            Bool _t4417; { Bool *_hp = (Bool *)Str_eq(fname, _t4416); _t4417 = *_hp; free(_hp); }
            (void)_t4417;
            Str_delete(_t4416, &(Bool){1});
            if (_t4417) {
                Str *_t4404 = Str_lit(" -l", 3ULL);
                (void)_t4404;
                Str *_t4405 = Str_concat(link_flags, _t4404);
                (void)_t4405;
                Str_delete(_t4404, &(Bool){1});
                link_flags = Str_concat(_t4405, arg);
                Str_delete(_t4405, &(Bool){1});
            } else {
                Str *_t4410 = Str_lit("link_c", 6ULL);
                (void)_t4410;
                Bool _t4411; { Bool *_hp = (Bool *)Str_eq(fname, _t4410); _t4411 = *_hp; free(_hp); }
                (void)_t4411;
                Str_delete(_t4410, &(Bool){1});
                if (_t4411) {
                    U64 _t4407; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4407 = *_hp; free(_hp); }
                    (void)_t4407;
                    U64 _t4408 = 0;
                    (void)_t4408;
                    Bool _t4409; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4407}, &(U64){_t4408}); _t4409 = *_hp; free(_hp); }
                    (void)_t4409;
                    ;
                    ;
                    if (_t4409) {
                        Str *_t4406 = Str_lit(" ", 1ULL);
                        (void)_t4406;
                        link_c_paths = Str_concat(link_c_paths, _t4406);
                        Str_delete(_t4406, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4412, &(Bool){1});
            U32_delete(_t4414, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4435 = 1;
        (void)_t4435;
        U32 _t4436 = U32_add(DEREF(i), _t4435);
        (void)_t4436;
        ;
        *i = _t4436;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4717 = init_declarations(ast, scope);
    (void)_t4717;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4718 = 0;
    (void)_t4718;
    Bool _t4719; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4718}); _t4719 = *_hp; free(_hp); }
    (void)_t4719;
    ;
    if (_t4719) {
        Str *_t4437 = Str_lit("Str", 3ULL);
        (void)_t4437;
        U64 _t4438; { U64 *_hp = (U64 *)Str_size(); _t4438 = *_hp; free(_hp); }
        (void)_t4438;
        U64 _t4439 = 1;
        (void)_t4439;
        Array *_va89 = Array_new(_t4437, &(U64){_t4438}, &(U64){_t4439});
        (void)_va89;
        Str_delete(_t4437, &(Bool){1});
        ;
        ;
        Str *_t4440 = I32_to_str(&(I32){type_errors});
        (void)_t4440;
        Str *_t4441 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4441;
        U64 _t4442 = 0;
        (void)_t4442;
        Str *_t4443 = Str_concat(_t4440, _t4441);
        (void)_t4443;
        Str_delete(_t4440, &(Bool){1});
        Str_delete(_t4441, &(Bool){1});
        Array_set(_va89, &(U64){_t4442}, _t4443);
        ;
        Str *_t4444 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4444;
        panic(_t4444, _va89);
        Str_delete(_t4444, &(Bool){1});
    }
    ;
    ;
    Str *_t4720 = Str_lit("test", 4ULL);
    (void)_t4720;
    Str *_t4721 = Str_lit("test", 4ULL);
    (void)_t4721;
    Bool _t4722; { Bool *_hp = (Bool *)Str_eq(command, _t4720); _t4722 = *_hp; free(_hp); }
    (void)_t4722;
    Str_delete(_t4720, &(Bool){1});
    Bool _t4723; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4721); _t4723 = *_hp; free(_hp); }
    (void)_t4723;
    Str_delete(_t4721, &(Bool){1});
    Str *_t4724 = Str_lit("pure", 4ULL);
    (void)_t4724;
    Bool _t4725 = Bool_or(_t4722, _t4723);
    (void)_t4725;
    ;
    ;
    Bool _t4726; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4724); _t4726 = *_hp; free(_hp); }
    (void)_t4726;
    Str_delete(_t4724, &(Bool){1});
    Str *_t4727 = Str_lit("pura", 4ULL);
    (void)_t4727;
    Bool _t4728 = Bool_or(_t4725, _t4726);
    (void)_t4728;
    ;
    ;
    Bool _t4729; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4727); _t4729 = *_hp; free(_hp); }
    (void)_t4729;
    Str_delete(_t4727, &(Bool){1});
    Bool run_tests = Bool_or(_t4728, _t4729);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4730 = Str_lit("translate", 9ULL);
    (void)_t4730;
    Str *_t4731 = Str_lit("build", 5ULL);
    (void)_t4731;
    Bool _t4732; { Bool *_hp = (Bool *)Str_eq(command, _t4730); _t4732 = *_hp; free(_hp); }
    (void)_t4732;
    Str_delete(_t4730, &(Bool){1});
    Bool _t4733; { Bool *_hp = (Bool *)Str_eq(command, _t4731); _t4733 = *_hp; free(_hp); }
    (void)_t4733;
    Str_delete(_t4731, &(Bool){1});
    Bool _t4734; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4734 = *_hp; free(_hp); }
    (void)_t4734;
    Bool _t4735 = Bool_or(_t4732, _t4733);
    (void)_t4735;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4734, _t4735);
    (void)is_lib_target;
    ;
    ;
    U64 _t4736; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4736 = *_hp; free(_hp); }
    (void)_t4736;
    U64 _t4737 = 0;
    (void)_t4737;
    Bool _t4738 = Bool_not(is_lib_target);
    (void)_t4738;
    ;
    Bool _t4739 = U64_eq(_t4736, _t4737);
    (void)_t4739;
    ;
    ;
    Bool _t4740 = Bool_and(_t4738, _t4739);
    (void)_t4740;
    ;
    ;
    if (_t4740) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4741; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4741 = *_hp; free(_hp); }
    (void)_t4741;
    U64 _t4742 = 0;
    (void)_t4742;
    Bool _t4743; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4741}, &(U64){_t4742}); _t4743 = *_hp; free(_hp); }
    (void)_t4743;
    ;
    ;
    if (_t4743) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4744 = Str_lit("Str", 3ULL);
    (void)_t4744;
    U64 _t4745; { U64 *_hp = (U64 *)Str_size(); _t4745 = *_hp; free(_hp); }
    (void)_t4745;
    Vec *user_argv = Vec_new(_t4744, &(U64){_t4745});
    (void)user_argv;
    Str_delete(_t4744, &(Bool){1});
    ;
    U64 _t4746 = 1;
    (void)_t4746;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4746);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4461; { U64 *_hp = (U64 *)Array_len(args); _t4461 = *_hp; free(_hp); }
        (void)_t4461;
        Bool _wcond4445; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4461}); _wcond4445 = *_hp; free(_hp); }
        (void)_wcond4445;
        ;
        if (_wcond4445) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4462 = Str_lit("-l", 2ULL);
        (void)_t4462;
        Bool _t4463; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4462); _t4463 = *_hp; free(_hp); }
        (void)_t4463;
        Str_delete(_t4462, &(Bool){1});
        if (_t4463) {
            U64 _t4448 = 2;
            (void)_t4448;
            U64 _t4449; { U64 *_hp = (U64 *)Str_len(arg); _t4449 = *_hp; free(_hp); }
            (void)_t4449;
            Str *lib = Str_substr(arg, &(U64){_t4448}, &(U64){_t4449});
            (void)lib;
            ;
            ;
            U64 _t4450; { U64 *_hp = (U64 *)Str_len(lib); _t4450 = *_hp; free(_hp); }
            (void)_t4450;
            U64 _t4451 = 0;
            (void)_t4451;
            U64 _t4452 = 1;
            (void)_t4452;
            U64 _t4453 = U64_add(DEREF(ai), _t4452);
            (void)_t4453;
            ;
            U64 _t4454; { U64 *_hp = (U64 *)Array_len(args); _t4454 = *_hp; free(_hp); }
            (void)_t4454;
            Bool _t4455 = U64_eq(_t4450, _t4451);
            (void)_t4455;
            ;
            ;
            Bool _t4456; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4453}, &(U64){_t4454}); _t4456 = *_hp; free(_hp); }
            (void)_t4456;
            ;
            ;
            Bool _t4457 = Bool_and(_t4455, _t4456);
            (void)_t4457;
            ;
            ;
            if (_t4457) {
                U64 _t4446 = 1;
                (void)_t4446;
                U64 _t4447 = U64_add(DEREF(ai), _t4446);
                (void)_t4447;
                ;
                *ai = _t4447;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4458 = Str_lit(" -l", 3ULL);
            (void)_t4458;
            Str *_t4459 = Str_concat(link_flags, _t4458);
            (void)_t4459;
            Str_delete(_t4458, &(Bool){1});
            link_flags = Str_concat(_t4459, lib);
            Str_delete(_t4459, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4460 = Str_clone(arg);
            (void)_t4460;
            Vec_push(user_argv, _t4460);
        }
        ;
        U64 _t4464 = 1;
        (void)_t4464;
        U64 _t4465 = U64_add(DEREF(ai), _t4464);
        (void)_t4465;
        ;
        *ai = _t4465;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4747; { U64 *_hp = (U64 *)Str_len(link_flags); _t4747 = *_hp; free(_hp); }
    (void)_t4747;
    U64 _t4748 = 0;
    (void)_t4748;
    Bool _t4749; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4747}, &(U64){_t4748}); _t4749 = *_hp; free(_hp); }
    (void)_t4749;
    ;
    ;
    if (_t4749) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4750 = Str_lit("interpret", 9ULL);
    (void)_t4750;
    Str *_t4751 = Str_lit("test", 4ULL);
    (void)_t4751;
    Bool _t4752; { Bool *_hp = (Bool *)Str_eq(command, _t4750); _t4752 = *_hp; free(_hp); }
    (void)_t4752;
    Str_delete(_t4750, &(Bool){1});
    Bool _t4753; { Bool *_hp = (Bool *)Str_eq(command, _t4751); _t4753 = *_hp; free(_hp); }
    (void)_t4753;
    Str_delete(_t4751, &(Bool){1});
    Bool _t4754 = Bool_or(_t4752, _t4753);
    (void)_t4754;
    ;
    ;
    if (_t4754) {
        Str *_t4472 = Str_lit("interpret", 9ULL);
        (void)_t4472;
        Bool _t4473; { Bool *_hp = (Bool *)Str_eq(command, _t4472); _t4473 = *_hp; free(_hp); }
        (void)_t4473;
        Str_delete(_t4472, &(Bool){1});
        Bool _t4474 = Bool_and(is_lib_mode, _t4473);
        (void)_t4474;
        ;
        if (_t4474) {
            Str *_t4466 = Str_lit("Str", 3ULL);
            (void)_t4466;
            U64 _t4467; { U64 *_hp = (U64 *)Str_size(); _t4467 = *_hp; free(_hp); }
            (void)_t4467;
            U64 _t4468 = 1;
            (void)_t4468;
            Array *_va90 = Array_new(_t4466, &(U64){_t4467}, &(U64){_t4468});
            (void)_va90;
            Str_delete(_t4466, &(Bool){1});
            ;
            ;
            U64 _t4469 = 0;
            (void)_t4469;
            Str *_t4470 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4470;
            Array_set(_va90, &(U64){_t4469}, _t4470);
            ;
            Str *_t4471 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4471;
            panic(_t4471, _va90);
            Str_delete(_t4471, &(Bool){1});
        }
        ;
        I32 _t4475 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4475;
        result = _t4475;
        ;
    } else {
        Str *_t4668 = Str_lit("translate", 9ULL);
        (void)_t4668;
        Str *_t4669 = Str_lit("build", 5ULL);
        (void)_t4669;
        Bool _t4670; { Bool *_hp = (Bool *)Str_eq(command, _t4668); _t4670 = *_hp; free(_hp); }
        (void)_t4670;
        Str_delete(_t4668, &(Bool){1});
        Bool _t4671; { Bool *_hp = (Bool *)Str_eq(command, _t4669); _t4671 = *_hp; free(_hp); }
        (void)_t4671;
        Str_delete(_t4669, &(Bool){1});
        Str *_t4672 = Str_lit("run", 3ULL);
        (void)_t4672;
        Bool _t4673 = Bool_or(_t4670, _t4671);
        (void)_t4673;
        ;
        ;
        Bool _t4674; { Bool *_hp = (Bool *)Str_eq(command, _t4672); _t4674 = *_hp; free(_hp); }
        (void)_t4674;
        Str_delete(_t4672, &(Bool){1});
        Bool _t4675 = Bool_or(_t4673, _t4674);
        (void)_t4675;
        ;
        ;
        if (_t4675) {
            Str *_t4601 = Str_lit("run", 3ULL);
            (void)_t4601;
            Bool _t4602; { Bool *_hp = (Bool *)Str_eq(command, _t4601); _t4602 = *_hp; free(_hp); }
            (void)_t4602;
            Str_delete(_t4601, &(Bool){1});
            Bool _t4603 = Bool_and(is_lib_mode, _t4602);
            (void)_t4603;
            ;
            if (_t4603) {
                Str *_t4476 = Str_lit("Str", 3ULL);
                (void)_t4476;
                U64 _t4477; { U64 *_hp = (U64 *)Str_size(); _t4477 = *_hp; free(_hp); }
                (void)_t4477;
                U64 _t4478 = 1;
                (void)_t4478;
                Array *_va91 = Array_new(_t4476, &(U64){_t4477}, &(U64){_t4478});
                (void)_va91;
                Str_delete(_t4476, &(Bool){1});
                ;
                ;
                U64 _t4479 = 0;
                (void)_t4479;
                Str *_t4480 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4480;
                Array_set(_va91, &(U64){_t4479}, _t4480);
                ;
                Str *_t4481 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4481;
                panic(_t4481, _va91);
                Str_delete(_t4481, &(Bool){1});
            }
            ;
            Str *_t4604 = Str_lit("/", 1ULL);
            (void)_t4604;
            I64 *last_slash = Str_rfind(path, _t4604);
            (void)last_slash;
            Str_delete(_t4604, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4605 = 0;
            (void)_t4605;
            Bool _t4606; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4605}); _t4606 = *_hp; free(_hp); }
            (void)_t4606;
            ;
            if (_t4606) {
                I64 _t4482 = 1;
                (void)_t4482;
                I64 _t4483 = I64_add(DEREF(last_slash), _t4482);
                (void)_t4483;
                ;
                U64 _t4484; { U64 *_hp = (U64 *)Str_len(path); _t4484 = *_hp; free(_hp); }
                (void)_t4484;
                U64 _t4485 = I64_to_u64(DEREF(last_slash));
                (void)_t4485;
                U64 _t4486 = U64_sub(_t4484, _t4485);
                (void)_t4486;
                ;
                ;
                U64 _t4487 = 1;
                (void)_t4487;
                U64 _t4488 = I64_to_u64(_t4483);
                (void)_t4488;
                ;
                U64 _t4489 = U64_sub(_t4486, _t4487);
                (void)_t4489;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4488}, &(U64){_t4489});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4607 = Str_lit(".til", 4ULL);
            (void)_t4607;
            Bool _t4608; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4607); _t4608 = *_hp; free(_hp); }
            (void)_t4608;
            Str_delete(_t4607, &(Bool){1});
            if (_t4608) {
                U64 _t4490 = 4;
                (void)_t4490;
                U64 _t4491 = U64_sub(name_len, _t4490);
                (void)_t4491;
                ;
                name_len = _t4491;
                ;
            }
            ;
            U64 _t4609 = 0;
            (void)_t4609;
            Str *name = Str_substr(basename, &(U64){_t4609}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4610 = Str_lit("gen/til/", 8ULL);
            (void)_t4610;
            Str *_t4611 = Str_concat(_t4610, name);
            (void)_t4611;
            Str_delete(_t4610, &(Bool){1});
            Str *_t4612 = Str_lit(".c", 2ULL);
            (void)_t4612;
            Str *c_path = Str_concat(_t4611, _t4612);
            (void)c_path;
            Str_delete(_t4611, &(Bool){1});
            Str_delete(_t4612, &(Bool){1});
            U64 _t4613; { U64 *_hp = (U64 *)Str_len(custom_c); _t4613 = *_hp; free(_hp); }
            (void)_t4613;
            U64 _t4614 = 0;
            (void)_t4614;
            Bool _t4615; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4613}, &(U64){_t4614}); _t4615 = *_hp; free(_hp); }
            (void)_t4615;
            ;
            ;
            if (_t4615) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4616 = Str_lit("bin/til/", 8ULL);
            (void)_t4616;
            Str *bin_path = Str_concat(_t4616, name);
            (void)bin_path;
            Str_delete(_t4616, &(Bool){1});
            U64 _t4617; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4617 = *_hp; free(_hp); }
            (void)_t4617;
            U64 _t4618 = 0;
            (void)_t4618;
            Bool _t4619; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4617}, &(U64){_t4618}); _t4619 = *_hp; free(_hp); }
            (void)_t4619;
            ;
            ;
            if (_t4619) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4620 = Str_lit("run", 3ULL);
            (void)_t4620;
            Bool _t4621; { Bool *_hp = (Bool *)Str_eq(command, _t4620); _t4621 = *_hp; free(_hp); }
            (void)_t4621;
            Str_delete(_t4620, &(Bool){1});
            Bool _t4622; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4622 = *_hp; free(_hp); }
            (void)_t4622;
            Bool _t4623 = Bool_not(_t4621);
            (void)_t4623;
            ;
            Bool do_lib = Bool_and(_t4622, _t4623);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4492 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4492;
                I32 _t4493 = til_system(_t4492);
                (void)_t4493;
                Str_delete(_t4492, &(Bool){1});
                ;
            } else {
                Str *_t4498 = Str_lit("/", 1ULL);
                (void)_t4498;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4498); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4498, &(Bool){1});
                Str *_t4499 = Str_lit("/", 1ULL);
                (void)_t4499;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4499); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4499, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4500 = 0;
                (void)_t4500;
                Bool _t4501; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4500}); _t4501 = *_hp; free(_hp); }
                (void)_t4501;
                ;
                if (_t4501) {
                    U64 _t4494 = 0;
                    (void)_t4494;
                    U64 _t4495 = I64_to_u64(cp_slash);
                    (void)_t4495;
                    cp_dir = Str_substr(c_path, &(U64){_t4494}, &(U64){_t4495});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4502 = 0;
                (void)_t4502;
                Bool _t4503; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4502}); _t4503 = *_hp; free(_hp); }
                (void)_t4503;
                ;
                if (_t4503) {
                    U64 _t4496 = 0;
                    (void)_t4496;
                    U64 _t4497 = I64_to_u64(bp_slash);
                    (void)_t4497;
                    bp_dir = Str_substr(bin_path, &(U64){_t4496}, &(U64){_t4497});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4504 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4504;
                Str *_t4505 = Str_concat(_t4504, cp_dir);
                (void)_t4505;
                Str_delete(_t4504, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4506 = Str_lit(" ", 1ULL);
                (void)_t4506;
                Str *_t4507 = Str_concat(_t4505, _t4506);
                (void)_t4507;
                Str_delete(_t4505, &(Bool){1});
                Str_delete(_t4506, &(Bool){1});
                Str *_t4508 = Str_concat(_t4507, bp_dir);
                (void)_t4508;
                Str_delete(_t4507, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4509 = til_system(_t4508);
                (void)_t4509;
                Str_delete(_t4508, &(Bool){1});
                ;
            }
            I32 _t4624 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4624;
            result = _t4624;
            ;
            I32 _t4625 = 0;
            (void)_t4625;
            Bool _t4626 = I32_eq(result, _t4625);
            (void)_t4626;
            ;
            Bool _t4627 = Bool_and(_t4626, do_lib);
            (void)_t4627;
            ;
            if (_t4627) {
                Str *_t4566 = Str_lit("gen/til/", 8ULL);
                (void)_t4566;
                Str *_t4567 = Str_concat(_t4566, name);
                (void)_t4567;
                Str_delete(_t4566, &(Bool){1});
                Str *_t4568 = Str_lit(".h", 2ULL);
                (void)_t4568;
                Str *h_path = Str_concat(_t4567, _t4568);
                (void)h_path;
                Str_delete(_t4567, &(Bool){1});
                Str_delete(_t4568, &(Bool){1});
                Str *_t4569 = Str_lit("gen/til/", 8ULL);
                (void)_t4569;
                Str *_t4570 = Str_concat(_t4569, name);
                (void)_t4570;
                Str_delete(_t4569, &(Bool){1});
                Str *_t4571 = Str_lit(".til", 4ULL);
                (void)_t4571;
                Str *til_path = Str_concat(_t4570, _t4571);
                (void)til_path;
                Str_delete(_t4570, &(Bool){1});
                Str_delete(_t4571, &(Bool){1});
                I32 _t4572 = build_header(ast, h_path);
                (void)_t4572;
                result = _t4572;
                ;
                I32 _t4573 = 0;
                (void)_t4573;
                Bool _t4574 = I32_eq(result, _t4573);
                (void)_t4574;
                ;
                if (_t4574) {
                    I32 _t4510 = build_til_binding(ast, til_path, name);
                    (void)_t4510;
                    result = _t4510;
                    ;
                }
                ;
                I32 _t4575 = 0;
                (void)_t4575;
                Str *_t4576 = Str_lit("translate", 9ULL);
                (void)_t4576;
                Bool _t4577 = I32_eq(result, _t4575);
                (void)_t4577;
                ;
                Bool _t4578; { Bool *_hp = (Bool *)Str_eq(command, _t4576); _t4578 = *_hp; free(_hp); }
                (void)_t4578;
                Str_delete(_t4576, &(Bool){1});
                Bool _t4579 = Bool_and(_t4577, _t4578);
                (void)_t4579;
                ;
                ;
                if (_t4579) {
                    Str *_t4511 = Str_lit("Str", 3ULL);
                    (void)_t4511;
                    U64 _t4512; { U64 *_hp = (U64 *)Str_size(); _t4512 = *_hp; free(_hp); }
                    (void)_t4512;
                    U64 _t4513 = 1;
                    (void)_t4513;
                    Array *_va92 = Array_new(_t4511, &(U64){_t4512}, &(U64){_t4513});
                    (void)_va92;
                    Str_delete(_t4511, &(Bool){1});
                    ;
                    ;
                    Str *_t4514 = Str_lit("Generated: ", 11ULL);
                    (void)_t4514;
                    U64 _t4515 = 0;
                    (void)_t4515;
                    Str *_t4516 = Str_concat(_t4514, c_path);
                    (void)_t4516;
                    Str_delete(_t4514, &(Bool){1});
                    Array_set(_va92, &(U64){_t4515}, _t4516);
                    ;
                    println(_va92);
                    Str *_t4517 = Str_lit("Str", 3ULL);
                    (void)_t4517;
                    U64 _t4518; { U64 *_hp = (U64 *)Str_size(); _t4518 = *_hp; free(_hp); }
                    (void)_t4518;
                    U64 _t4519 = 1;
                    (void)_t4519;
                    Array *_va93 = Array_new(_t4517, &(U64){_t4518}, &(U64){_t4519});
                    (void)_va93;
                    Str_delete(_t4517, &(Bool){1});
                    ;
                    ;
                    Str *_t4520 = Str_lit("Generated: ", 11ULL);
                    (void)_t4520;
                    U64 _t4521 = 0;
                    (void)_t4521;
                    Str *_t4522 = Str_concat(_t4520, h_path);
                    (void)_t4522;
                    Str_delete(_t4520, &(Bool){1});
                    Array_set(_va93, &(U64){_t4521}, _t4522);
                    ;
                    println(_va93);
                    Str *_t4523 = Str_lit("Str", 3ULL);
                    (void)_t4523;
                    U64 _t4524; { U64 *_hp = (U64 *)Str_size(); _t4524 = *_hp; free(_hp); }
                    (void)_t4524;
                    U64 _t4525 = 1;
                    (void)_t4525;
                    Array *_va94 = Array_new(_t4523, &(U64){_t4524}, &(U64){_t4525});
                    (void)_va94;
                    Str_delete(_t4523, &(Bool){1});
                    ;
                    ;
                    Str *_t4526 = Str_lit("Generated: ", 11ULL);
                    (void)_t4526;
                    U64 _t4527 = 0;
                    (void)_t4527;
                    Str *_t4528 = Str_concat(_t4526, til_path);
                    (void)_t4528;
                    Str_delete(_t4526, &(Bool){1});
                    Array_set(_va94, &(U64){_t4527}, _t4528);
                    ;
                    println(_va94);
                }
                ;
                I32 _t4580 = 0;
                (void)_t4580;
                Str *_t4581 = Str_lit("build", 5ULL);
                (void)_t4581;
                Bool _t4582 = I32_eq(result, _t4580);
                (void)_t4582;
                ;
                Bool _t4583; { Bool *_hp = (Bool *)Str_eq(command, _t4581); _t4583 = *_hp; free(_hp); }
                (void)_t4583;
                Str_delete(_t4581, &(Bool){1});
                Bool _t4584 = Bool_and(_t4582, _t4583);
                (void)_t4584;
                ;
                ;
                if (_t4584) {
                    I32 _t4563 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4563;
                    result = _t4563;
                    ;
                    I32 _t4564 = 0;
                    (void)_t4564;
                    Bool _t4565 = I32_eq(result, _t4564);
                    (void)_t4565;
                    ;
                    if (_t4565) {
                        Str *_t4529 = Str_lit("Str", 3ULL);
                        (void)_t4529;
                        U64 _t4530; { U64 *_hp = (U64 *)Str_size(); _t4530 = *_hp; free(_hp); }
                        (void)_t4530;
                        U64 _t4531 = 1;
                        (void)_t4531;
                        Array *_va95 = Array_new(_t4529, &(U64){_t4530}, &(U64){_t4531});
                        (void)_va95;
                        Str_delete(_t4529, &(Bool){1});
                        ;
                        ;
                        Str *_t4532 = Str_lit("Generated: ", 11ULL);
                        (void)_t4532;
                        U64 _t4533 = 0;
                        (void)_t4533;
                        Str *_t4534 = Str_concat(_t4532, c_path);
                        (void)_t4534;
                        Str_delete(_t4532, &(Bool){1});
                        Array_set(_va95, &(U64){_t4533}, _t4534);
                        ;
                        println(_va95);
                        Str *_t4535 = Str_lit("Str", 3ULL);
                        (void)_t4535;
                        U64 _t4536; { U64 *_hp = (U64 *)Str_size(); _t4536 = *_hp; free(_hp); }
                        (void)_t4536;
                        U64 _t4537 = 1;
                        (void)_t4537;
                        Array *_va96 = Array_new(_t4535, &(U64){_t4536}, &(U64){_t4537});
                        (void)_va96;
                        Str_delete(_t4535, &(Bool){1});
                        ;
                        ;
                        Str *_t4538 = Str_lit("Generated: ", 11ULL);
                        (void)_t4538;
                        U64 _t4539 = 0;
                        (void)_t4539;
                        Str *_t4540 = Str_concat(_t4538, h_path);
                        (void)_t4540;
                        Str_delete(_t4538, &(Bool){1});
                        Array_set(_va96, &(U64){_t4539}, _t4540);
                        ;
                        println(_va96);
                        Str *_t4541 = Str_lit("Str", 3ULL);
                        (void)_t4541;
                        U64 _t4542; { U64 *_hp = (U64 *)Str_size(); _t4542 = *_hp; free(_hp); }
                        (void)_t4542;
                        U64 _t4543 = 1;
                        (void)_t4543;
                        Array *_va97 = Array_new(_t4541, &(U64){_t4542}, &(U64){_t4543});
                        (void)_va97;
                        Str_delete(_t4541, &(Bool){1});
                        ;
                        ;
                        Str *_t4544 = Str_lit("Generated: ", 11ULL);
                        (void)_t4544;
                        U64 _t4545 = 0;
                        (void)_t4545;
                        Str *_t4546 = Str_concat(_t4544, til_path);
                        (void)_t4546;
                        Str_delete(_t4544, &(Bool){1});
                        Array_set(_va97, &(U64){_t4545}, _t4546);
                        ;
                        println(_va97);
                        Str *_t4547 = Str_lit("Str", 3ULL);
                        (void)_t4547;
                        U64 _t4548; { U64 *_hp = (U64 *)Str_size(); _t4548 = *_hp; free(_hp); }
                        (void)_t4548;
                        U64 _t4549 = 1;
                        (void)_t4549;
                        Array *_va98 = Array_new(_t4547, &(U64){_t4548}, &(U64){_t4549});
                        (void)_va98;
                        Str_delete(_t4547, &(Bool){1});
                        ;
                        ;
                        Str *_t4550 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4550;
                        Str *_t4551 = Str_concat(_t4550, name);
                        (void)_t4551;
                        Str_delete(_t4550, &(Bool){1});
                        Str *_t4552 = Str_lit(".so", 3ULL);
                        (void)_t4552;
                        U64 _t4553 = 0;
                        (void)_t4553;
                        Str *_t4554 = Str_concat(_t4551, _t4552);
                        (void)_t4554;
                        Str_delete(_t4551, &(Bool){1});
                        Str_delete(_t4552, &(Bool){1});
                        Array_set(_va98, &(U64){_t4553}, _t4554);
                        ;
                        println(_va98);
                        Str *_t4555 = Str_lit("Str", 3ULL);
                        (void)_t4555;
                        U64 _t4556; { U64 *_hp = (U64 *)Str_size(); _t4556 = *_hp; free(_hp); }
                        (void)_t4556;
                        U64 _t4557 = 1;
                        (void)_t4557;
                        Array *_va99 = Array_new(_t4555, &(U64){_t4556}, &(U64){_t4557});
                        (void)_va99;
                        Str_delete(_t4555, &(Bool){1});
                        ;
                        ;
                        Str *_t4558 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4558;
                        Str *_t4559 = Str_concat(_t4558, name);
                        (void)_t4559;
                        Str_delete(_t4558, &(Bool){1});
                        Str *_t4560 = Str_lit(".a", 2ULL);
                        (void)_t4560;
                        U64 _t4561 = 0;
                        (void)_t4561;
                        Str *_t4562 = Str_concat(_t4559, _t4560);
                        (void)_t4562;
                        Str_delete(_t4559, &(Bool){1});
                        Str_delete(_t4560, &(Bool){1});
                        Array_set(_va99, &(U64){_t4561}, _t4562);
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
            I32 _t4628 = 0;
            (void)_t4628;
            Bool _t4629 = I32_eq(result, _t4628);
            (void)_t4629;
            ;
            Bool _t4630 = Bool_not(do_lib);
            (void)_t4630;
            Str *_t4631 = Str_lit("translate", 9ULL);
            (void)_t4631;
            Bool _t4632 = Bool_and(_t4629, _t4630);
            (void)_t4632;
            ;
            ;
            Bool _t4633; { Bool *_hp = (Bool *)Str_eq(command, _t4631); _t4633 = *_hp; free(_hp); }
            (void)_t4633;
            Str_delete(_t4631, &(Bool){1});
            Bool _t4634 = Bool_and(_t4632, _t4633);
            (void)_t4634;
            ;
            ;
            if (_t4634) {
                Str *_t4585 = Str_lit("Str", 3ULL);
                (void)_t4585;
                U64 _t4586; { U64 *_hp = (U64 *)Str_size(); _t4586 = *_hp; free(_hp); }
                (void)_t4586;
                U64 _t4587 = 1;
                (void)_t4587;
                Array *_va100 = Array_new(_t4585, &(U64){_t4586}, &(U64){_t4587});
                (void)_va100;
                Str_delete(_t4585, &(Bool){1});
                ;
                ;
                Str *_t4588 = Str_lit("Generated: ", 11ULL);
                (void)_t4588;
                U64 _t4589 = 0;
                (void)_t4589;
                Str *_t4590 = Str_concat(_t4588, c_path);
                (void)_t4590;
                Str_delete(_t4588, &(Bool){1});
                Array_set(_va100, &(U64){_t4589}, _t4590);
                ;
                println(_va100);
            }
            ;
            I32 _t4635 = 0;
            (void)_t4635;
            Bool _t4636 = I32_eq(result, _t4635);
            (void)_t4636;
            ;
            Bool _t4637 = Bool_not(do_lib);
            (void)_t4637;
            Str *_t4638 = Str_lit("translate", 9ULL);
            (void)_t4638;
            Bool _t4639; { Bool *_hp = (Bool *)Str_eq(command, _t4638); _t4639 = *_hp; free(_hp); }
            (void)_t4639;
            Str_delete(_t4638, &(Bool){1});
            Bool _t4640 = Bool_and(_t4636, _t4637);
            (void)_t4640;
            ;
            ;
            Bool _t4641 = Bool_not(_t4639);
            (void)_t4641;
            ;
            Bool _t4642 = Bool_and(_t4640, _t4641);
            (void)_t4642;
            ;
            ;
            if (_t4642) {
                I32 _t4591 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4591;
                result = _t4591;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4643 = 0;
            (void)_t4643;
            Bool _t4644 = I32_eq(result, _t4643);
            (void)_t4644;
            ;
            Bool _t4645 = Bool_not(do_lib);
            (void)_t4645;
            ;
            Str *_t4646 = Str_lit("run", 3ULL);
            (void)_t4646;
            Bool _t4647 = Bool_and(_t4644, _t4645);
            (void)_t4647;
            ;
            ;
            Bool _t4648; { Bool *_hp = (Bool *)Str_eq(command, _t4646); _t4648 = *_hp; free(_hp); }
            (void)_t4648;
            Str_delete(_t4646, &(Bool){1});
            Bool _t4649 = Bool_and(_t4647, _t4648);
            (void)_t4649;
            ;
            ;
            if (_t4649) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4593; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4593 = *_hp; free(_hp); }
                    (void)_t4593;
                    Bool _wcond4592; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4593}); _wcond4592 = *_hp; free(_hp); }
                    (void)_wcond4592;
                    ;
                    if (_wcond4592) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4594 = Str_lit(" '", 2ULL);
                    (void)_t4594;
                    Str *_t4595 = Str_concat(cmd, _t4594);
                    (void)_t4595;
                    Str_delete(_t4594, &(Bool){1});
                    Str *_t4596 = Str_concat(_t4595, uarg);
                    (void)_t4596;
                    Str_delete(_t4595, &(Bool){1});
                    Str *_t4597 = Str_lit("'", 1ULL);
                    (void)_t4597;
                    cmd = Str_concat(_t4596, _t4597);
                    Str_delete(_t4596, &(Bool){1});
                    Str_delete(_t4597, &(Bool){1});
                    U64 _t4598 = 1;
                    (void)_t4598;
                    U64 _t4599 = U64_add(DEREF(ui), _t4598);
                    (void)_t4599;
                    ;
                    *ui = _t4599;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4600 = til_system(cmd);
                (void)_t4600;
                Str_delete(cmd, &(Bool){1});
                result = _t4600;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4666 = Str_lit("ast", 3ULL);
            (void)_t4666;
            Bool _t4667; { Bool *_hp = (Bool *)Str_eq(command, _t4666); _t4667 = *_hp; free(_hp); }
            (void)_t4667;
            Str_delete(_t4666, &(Bool){1});
            if (_t4667) {
                Str *_t4650 = Str_lit("Str", 3ULL);
                (void)_t4650;
                U64 _t4651; { U64 *_hp = (U64 *)Str_size(); _t4651 = *_hp; free(_hp); }
                (void)_t4651;
                U64 _t4652 = 1;
                (void)_t4652;
                Array *_va101 = Array_new(_t4650, &(U64){_t4651}, &(U64){_t4652});
                (void)_va101;
                Str_delete(_t4650, &(Bool){1});
                ;
                ;
                Str *_t4653 = Str_lit("mode: ", 6ULL);
                (void)_t4653;
                U64 _t4654 = 0;
                (void)_t4654;
                Str *_t4655 = Str_concat(_t4653, &cur_mode->name);
                (void)_t4655;
                Str_delete(_t4653, &(Bool){1});
                Array_set(_va101, &(U64){_t4654}, _t4655);
                ;
                println(_va101);
                U32 _t4656 = 0;
                (void)_t4656;
                ast_print(ast, _t4656);
                ;
            } else {
                Str *_t4657 = Str_lit("Str", 3ULL);
                (void)_t4657;
                U64 _t4658; { U64 *_hp = (U64 *)Str_size(); _t4658 = *_hp; free(_hp); }
                (void)_t4658;
                U64 _t4659 = 1;
                (void)_t4659;
                Array *_va102 = Array_new(_t4657, &(U64){_t4658}, &(U64){_t4659});
                (void)_va102;
                Str_delete(_t4657, &(Bool){1});
                ;
                ;
                Str *_t4660 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4660;
                Str *_t4661 = Str_concat(_t4660, command);
                (void)_t4661;
                Str_delete(_t4660, &(Bool){1});
                Str *_t4662 = Str_lit("'", 1ULL);
                (void)_t4662;
                U64 _t4663 = 0;
                (void)_t4663;
                Str *_t4664 = Str_concat(_t4661, _t4662);
                (void)_t4664;
                Str_delete(_t4661, &(Bool){1});
                Str_delete(_t4662, &(Bool){1});
                Array_set(_va102, &(U64){_t4663}, _t4664);
                ;
                println(_va102);
                usage();
                I32 _t4665 = 1;
                (void)_t4665;
                result = _t4665;
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
    I64 _t4755 = I32_to_i64(result);
    (void)_t4755;
    ;
    exit(_t4755);
    ;
    return 0;
}

