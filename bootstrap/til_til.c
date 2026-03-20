#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4182 = Str_lit("Str", 3ULL);
    (void)_t4182;
    U64 _t4183; { U64 *_hp = (U64 *)Str_size(); _t4183 = *_hp; free(_hp); }
    (void)_t4183;
    Vec *paths = Vec_new(_t4182, &(U64){_t4183});
    (void)paths;
    Str_delete(_t4182, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4157 = expr_nchildren(body);
        (void)_t4157;
        Bool _wcond4153; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4157}); _wcond4153 = *_hp; free(_hp); }
        (void)_wcond4153;
        ;
        if (_wcond4153) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4158 = expr_get_tag(stmt);
        (void)_t4158;
        U32 _t4159 = expr_nchildren(stmt);
        (void)_t4159;
        U32 _t4160 = 2;
        (void)_t4160;
        Bool _t4161 = I32_eq(_t4158, DEREF(NODE_FCALL));
        (void)_t4161;
        ;
        Bool _t4162 = U32_eq(_t4159, _t4160);
        (void)_t4162;
        ;
        ;
        U32 *_t4163 = malloc(sizeof(U32));
        *_t4163 = 0;
        (void)_t4163;
        Expr *_t4164 = expr_get_child(stmt, DEREF(_t4163));
        (void)_t4164;
        I32 _t4165 = expr_get_tag(_t4164);
        (void)_t4165;
        U32_delete(_t4163, &(Bool){1});
        Bool _t4166 = Bool_and(_t4161, _t4162);
        (void)_t4166;
        ;
        ;
        Bool _t4167 = I32_eq(_t4165, DEREF(NODE_IDENT));
        (void)_t4167;
        ;
        U32 *_t4168 = malloc(sizeof(U32));
        *_t4168 = 0;
        (void)_t4168;
        Expr *_t4169 = expr_get_child(stmt, DEREF(_t4168));
        (void)_t4169;
        Str *_t4170 = expr_get_str_val(_t4169);
        (void)_t4170;
        Str *_t4171 = Str_lit("import", 6ULL);
        (void)_t4171;
        Bool _t4172 = Bool_and(_t4166, _t4167);
        (void)_t4172;
        ;
        ;
        Bool _t4173; { Bool *_hp = (Bool *)Str_eq(_t4170, _t4171); _t4173 = *_hp; free(_hp); }
        (void)_t4173;
        U32_delete(_t4168, &(Bool){1});
        Str_delete(_t4171, &(Bool){1});
        U32 *_t4174 = malloc(sizeof(U32));
        *_t4174 = 1;
        (void)_t4174;
        Expr *_t4175 = expr_get_child(stmt, DEREF(_t4174));
        (void)_t4175;
        I32 _t4176 = expr_get_tag(_t4175);
        (void)_t4176;
        U32_delete(_t4174, &(Bool){1});
        Bool _t4177 = Bool_and(_t4172, _t4173);
        (void)_t4177;
        ;
        ;
        Bool _t4178 = I32_eq(_t4176, DEREF(NODE_LITERAL_STR));
        (void)_t4178;
        ;
        Bool _t4179 = Bool_and(_t4177, _t4178);
        (void)_t4179;
        ;
        ;
        if (_t4179) {
            U32 *_t4154 = malloc(sizeof(U32));
            *_t4154 = 1;
            (void)_t4154;
            Expr *_t4155 = expr_get_child(stmt, DEREF(_t4154));
            (void)_t4155;
            Str *path = expr_get_str_val(_t4155);
            (void)path;
            Str *_t4156 = Str_clone(path);
            (void)_t4156;
            U32_delete(_t4154, &(Bool){1});
            Vec_push(paths, _t4156);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4180 = 1;
        (void)_t4180;
        U32 _t4181 = U32_add(DEREF(i), _t4180);
        (void)_t4181;
        ;
        *i = _t4181;
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
        U64 _t4234 = 0;
        (void)_t4234;
        U64 _t4235; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4235 = *_hp; free(_hp); }
        (void)_t4235;
        Range *_fc4184 = Range_new(_t4234, _t4235);
        (void)_fc4184;
        ;
        ;
        U64 _fi4184 = 0;
        (void)_fi4184;
        while (1) {
            U64 _t4214; { U64 *_hp = (U64 *)Range_len(_fc4184); _t4214 = *_hp; free(_hp); }
            (void)_t4214;
            Bool _wcond4185; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4184}, &(U64){_t4214}); _wcond4185 = *_hp; free(_hp); }
            (void)_wcond4185;
            ;
            if (_wcond4185) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4184, _fi4184);
            (void)i;
            U64 _t4215 = 1;
            (void)_t4215;
            U64 _t4216 = U64_add(_fi4184, _t4215);
            (void)_t4216;
            ;
            _fi4184 = _t4216;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4217 = Str_lit("/", 1ULL);
            (void)_t4217;
            Str *_t4218 = Str_concat(base_dir, _t4217);
            (void)_t4218;
            Str_delete(_t4217, &(Bool){1});
            Str *try_path = Str_concat(_t4218, import_path);
            (void)try_path;
            Str_delete(_t4218, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4219 = Str_lit("", 0ULL);
            (void)_t4219;
            U64 _t4220; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4220 = *_hp; free(_hp); }
            (void)_t4220;
            U64 _t4221 = 0;
            (void)_t4221;
            Bool _t4222; { Bool *_hp = (Bool *)Str_eq(abs, _t4219); _t4222 = *_hp; free(_hp); }
            (void)_t4222;
            Str_delete(_t4219, &(Bool){1});
            Bool _t4223; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4220}, &(U64){_t4221}); _t4223 = *_hp; free(_hp); }
            (void)_t4223;
            ;
            ;
            Bool _t4224 = Bool_and(_t4222, _t4223);
            (void)_t4224;
            ;
            ;
            if (_t4224) {
                Str *_t4186 = Str_lit("/", 1ULL);
                (void)_t4186;
                Str *_t4187 = Str_concat(lib_dir, _t4186);
                (void)_t4187;
                Str_delete(_t4186, &(Bool){1});
                try_path = Str_concat(_t4187, import_path);
                Str_delete(_t4187, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4225 = Str_lit("", 0ULL);
            (void)_t4225;
            Bool _t4226; { Bool *_hp = (Bool *)Str_eq(abs, _t4225); _t4226 = *_hp; free(_hp); }
            (void)_t4226;
            Str_delete(_t4225, &(Bool){1});
            if (_t4226) {
                Str *_t4188 = Str_lit("Str", 3ULL);
                (void)_t4188;
                U64 _t4189; { U64 *_hp = (U64 *)Str_size(); _t4189 = *_hp; free(_hp); }
                (void)_t4189;
                U64 _t4190 = 1;
                (void)_t4190;
                Array *_va75 = Array_new(_t4188, &(U64){_t4189}, &(U64){_t4190});
                (void)_va75;
                Str_delete(_t4188, &(Bool){1});
                ;
                ;
                Str *_t4191 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4191;
                Str *_t4192 = Str_concat(_t4191, import_path);
                (void)_t4192;
                Str_delete(_t4191, &(Bool){1});
                Str *_t4193 = Str_lit("' (from ", 8ULL);
                (void)_t4193;
                Str *_t4194 = Str_concat(_t4192, _t4193);
                (void)_t4194;
                Str_delete(_t4192, &(Bool){1});
                Str_delete(_t4193, &(Bool){1});
                Str *_t4195 = Str_concat(_t4194, base_dir);
                (void)_t4195;
                Str_delete(_t4194, &(Bool){1});
                Str *_t4196 = Str_lit("/)", 2ULL);
                (void)_t4196;
                U64 _t4197 = 0;
                (void)_t4197;
                Str *_t4198 = Str_concat(_t4195, _t4196);
                (void)_t4198;
                Str_delete(_t4195, &(Bool){1});
                Str_delete(_t4196, &(Bool){1});
                Array_set(_va75, &(U64){_t4197}, _t4198);
                ;
                println(_va75);
                I64 _t4199 = 1;
                (void)_t4199;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4184, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4199; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4227; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4227 = *_hp; free(_hp); }
            (void)_t4227;
            if (_t4227) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4228 = Str_clone(abs);
            (void)_t4228;
            Set_add(resolved_set, _t4228);
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
            U64 _t4229; { U64 *_hp = (U64 *)Str_len(abs); _t4229 = *_hp; free(_hp); }
            (void)_t4229;
            U64 _t4230 = 1;
            (void)_t4230;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4229, _t4230);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4201 = 0;
                (void)_t4201;
                U8 *_t4202 = Str_get(abs, last_slash);
                (void)_t4202;
                U8 _t4203 = 47;
                (void)_t4203;
                Bool _t4204; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4201}); _t4204 = *_hp; free(_hp); }
                (void)_t4204;
                ;
                Bool _t4205; { Bool *_hp = (Bool *)U8_neq(_t4202, &(U8){_t4203}); _t4205 = *_hp; free(_hp); }
                (void)_t4205;
                ;
                Bool _wcond4200 = Bool_and(_t4204, _t4205);
                (void)_wcond4200;
                ;
                ;
                if (_wcond4200) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4206 = 1;
                (void)_t4206;
                U64 _t4207 = U64_sub(DEREF(last_slash), _t4206);
                (void)_t4207;
                ;
                *last_slash = _t4207;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4231; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4231 = *_hp; free(_hp); }
            (void)_t4231;
            U64 _t4232 = 0;
            (void)_t4232;
            Bool _t4233; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4231}, &(U64){_t4232}); _t4233 = *_hp; free(_hp); }
            (void)_t4233;
            ;
            ;
            if (_t4233) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4208 = 0;
                (void)_t4208;
                Bool _t4209; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4208}); _t4209 = *_hp; free(_hp); }
                (void)_t4209;
                ;
                if (_t4209) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4184, &(Bool){1});
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
                U32 _t4211 = expr_nchildren(sub_ast);
                (void)_t4211;
                Bool _wcond4210; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4211}); _wcond4210 = *_hp; free(_hp); }
                (void)_wcond4210;
                ;
                if (_wcond4210) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4212 = 1;
                (void)_t4212;
                U32 _t4213 = U32_add(DEREF(k), _t4212);
                (void)_t4213;
                ;
                *k = _t4213;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4184, &(Bool){1});
        ;
    }
    I64 _t4236 = 0;
    (void)_t4236;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4236; return _r; }
}

void usage(void) {
    Str *_t4237 = Str_lit("Str", 3ULL);
    (void)_t4237;
    U64 _t4238; { U64 *_hp = (U64 *)Str_size(); _t4238 = *_hp; free(_hp); }
    (void)_t4238;
    U64 _t4239 = 1;
    (void)_t4239;
    Array *_va76 = Array_new(_t4237, &(U64){_t4238}, &(U64){_t4239});
    (void)_va76;
    Str_delete(_t4237, &(Bool){1});
    ;
    ;
    U64 _t4240 = 0;
    (void)_t4240;
    Str *_t4241 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4241;
    Array_set(_va76, &(U64){_t4240}, _t4241);
    ;
    println(_va76);
    Str *_t4242 = Str_lit("Str", 3ULL);
    (void)_t4242;
    U64 _t4243; { U64 *_hp = (U64 *)Str_size(); _t4243 = *_hp; free(_hp); }
    (void)_t4243;
    U64 _t4244 = 1;
    (void)_t4244;
    Array *_va77 = Array_new(_t4242, &(U64){_t4243}, &(U64){_t4244});
    (void)_va77;
    Str_delete(_t4242, &(Bool){1});
    ;
    ;
    U64 _t4245 = 0;
    (void)_t4245;
    Str *_t4246 = Str_lit("", 0ULL);
    (void)_t4246;
    Array_set(_va77, &(U64){_t4245}, _t4246);
    ;
    println(_va77);
    Str *_t4247 = Str_lit("Str", 3ULL);
    (void)_t4247;
    U64 _t4248; { U64 *_hp = (U64 *)Str_size(); _t4248 = *_hp; free(_hp); }
    (void)_t4248;
    U64 _t4249 = 1;
    (void)_t4249;
    Array *_va78 = Array_new(_t4247, &(U64){_t4248}, &(U64){_t4249});
    (void)_va78;
    Str_delete(_t4247, &(Bool){1});
    ;
    ;
    U64 _t4250 = 0;
    (void)_t4250;
    Str *_t4251 = Str_lit("Commands:", 9ULL);
    (void)_t4251;
    Array_set(_va78, &(U64){_t4250}, _t4251);
    ;
    println(_va78);
    Str *_t4252 = Str_lit("Str", 3ULL);
    (void)_t4252;
    U64 _t4253; { U64 *_hp = (U64 *)Str_size(); _t4253 = *_hp; free(_hp); }
    (void)_t4253;
    U64 _t4254 = 1;
    (void)_t4254;
    Array *_va79 = Array_new(_t4252, &(U64){_t4253}, &(U64){_t4254});
    (void)_va79;
    Str_delete(_t4252, &(Bool){1});
    ;
    ;
    U64 _t4255 = 0;
    (void)_t4255;
    Str *_t4256 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4256;
    Array_set(_va79, &(U64){_t4255}, _t4256);
    ;
    println(_va79);
    Str *_t4257 = Str_lit("Str", 3ULL);
    (void)_t4257;
    U64 _t4258; { U64 *_hp = (U64 *)Str_size(); _t4258 = *_hp; free(_hp); }
    (void)_t4258;
    U64 _t4259 = 1;
    (void)_t4259;
    Array *_va80 = Array_new(_t4257, &(U64){_t4258}, &(U64){_t4259});
    (void)_va80;
    Str_delete(_t4257, &(Bool){1});
    ;
    ;
    U64 _t4260 = 0;
    (void)_t4260;
    Str *_t4261 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4261;
    Array_set(_va80, &(U64){_t4260}, _t4261);
    ;
    println(_va80);
    Str *_t4262 = Str_lit("Str", 3ULL);
    (void)_t4262;
    U64 _t4263; { U64 *_hp = (U64 *)Str_size(); _t4263 = *_hp; free(_hp); }
    (void)_t4263;
    U64 _t4264 = 1;
    (void)_t4264;
    Array *_va81 = Array_new(_t4262, &(U64){_t4263}, &(U64){_t4264});
    (void)_va81;
    Str_delete(_t4262, &(Bool){1});
    ;
    ;
    U64 _t4265 = 0;
    (void)_t4265;
    Str *_t4266 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4266;
    Array_set(_va81, &(U64){_t4265}, _t4266);
    ;
    println(_va81);
    Str *_t4267 = Str_lit("Str", 3ULL);
    (void)_t4267;
    U64 _t4268; { U64 *_hp = (U64 *)Str_size(); _t4268 = *_hp; free(_hp); }
    (void)_t4268;
    U64 _t4269 = 1;
    (void)_t4269;
    Array *_va82 = Array_new(_t4267, &(U64){_t4268}, &(U64){_t4269});
    (void)_va82;
    Str_delete(_t4267, &(Bool){1});
    ;
    ;
    U64 _t4270 = 0;
    (void)_t4270;
    Str *_t4271 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4271;
    Array_set(_va82, &(U64){_t4270}, _t4271);
    ;
    println(_va82);
    Str *_t4272 = Str_lit("Str", 3ULL);
    (void)_t4272;
    U64 _t4273; { U64 *_hp = (U64 *)Str_size(); _t4273 = *_hp; free(_hp); }
    (void)_t4273;
    U64 _t4274 = 1;
    (void)_t4274;
    Array *_va83 = Array_new(_t4272, &(U64){_t4273}, &(U64){_t4274});
    (void)_va83;
    Str_delete(_t4272, &(Bool){1});
    ;
    ;
    U64 _t4275 = 0;
    (void)_t4275;
    Str *_t4276 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4276;
    Array_set(_va83, &(U64){_t4275}, _t4276);
    ;
    println(_va83);
    Str *_t4277 = Str_lit("Str", 3ULL);
    (void)_t4277;
    U64 _t4278; { U64 *_hp = (U64 *)Str_size(); _t4278 = *_hp; free(_hp); }
    (void)_t4278;
    U64 _t4279 = 1;
    (void)_t4279;
    Array *_va84 = Array_new(_t4277, &(U64){_t4278}, &(U64){_t4279});
    (void)_va84;
    Str_delete(_t4277, &(Bool){1});
    ;
    ;
    U64 _t4280 = 0;
    (void)_t4280;
    Str *_t4281 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4281;
    Array_set(_va84, &(U64){_t4280}, _t4281);
    ;
    println(_va84);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4287 = 1;
    (void)_t4287;
    e->is_core = _t4287;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4283 = expr_nchildren(e);
        (void)_t4283;
        Bool _wcond4282; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4283}); _wcond4282 = *_hp; free(_hp); }
        (void)_wcond4282;
        ;
        if (_wcond4282) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4284 = expr_get_child(e, DEREF(i));
        (void)_t4284;
        mark_core(_t4284);
        U32 _t4285 = 1;
        (void)_t4285;
        U32 _t4286 = U32_add(DEREF(i), _t4285);
        (void)_t4286;
        ;
        *i = _t4286;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4747 = malloc(sizeof(I64));
    *_t4747 = 0;
    (void)_t4747;
    _t4748 = malloc(sizeof(I64));
    *_t4748 = 1;
    (void)_t4748;
    _t4749 = malloc(sizeof(I64)); *_t4749 = I64_sub(DEREF(_t4747), DEREF(_t4748));
    (void)_t4749;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4749));
    (void)CAP_LIT;
    _t4750 = malloc(sizeof(I64));
    *_t4750 = 0;
    (void)_t4750;
    _t4751 = malloc(sizeof(I64));
    *_t4751 = 2;
    (void)_t4751;
    _t4752 = malloc(sizeof(I64)); *_t4752 = I64_sub(DEREF(_t4750), DEREF(_t4751));
    (void)_t4752;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4752));
    (void)CAP_VIEW;
    _t4753 = Str_lit("Str", 3ULL);
    (void)_t4753;
    _t4754 = Str_size();
    (void)_t4754;
    _t4755 = Str_lit("Mode", 4ULL);
    (void)_t4755;
    _t4756 = Mode_size();
    (void)_t4756;
    core_modes = Map_new(_t4753, _t4754, _t4755, _t4756);
    (void)core_modes;
    _t4757 = malloc(sizeof(Bool));
    *_t4757 = 0;
    (void)_t4757;
    _t4758 = malloc(sizeof(Bool));
    *_t4758 = 0;
    (void)_t4758;
    _t4759 = malloc(sizeof(Bool));
    *_t4759 = 0;
    (void)_t4759;
    _t4760 = malloc(sizeof(Bool));
    *_t4760 = 0;
    (void)_t4760;
    _t4761 = Str_lit("script", 6ULL);
    (void)_t4761;
    _t4762 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4762->name = *_ca; free(_ca); }
    _t4762->needs_main = DEREF(_t4757);
    _t4762->decls_only = DEREF(_t4758);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4762->auto_import = *_ca; free(_ca); }
    _t4762->is_pure = DEREF(_t4759);
    _t4762->debug_prints = DEREF(_t4760);
    (void)_t4762;
    _t4763 = malloc(sizeof(Bool));
    *_t4763 = 1;
    (void)_t4763;
    _t4764 = malloc(sizeof(Bool));
    *_t4764 = 1;
    (void)_t4764;
    _t4765 = malloc(sizeof(Bool));
    *_t4765 = 0;
    (void)_t4765;
    _t4766 = malloc(sizeof(Bool));
    *_t4766 = 0;
    (void)_t4766;
    _t4767 = Str_lit("cli", 3ULL);
    (void)_t4767;
    _t4768 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4768->name = *_ca; free(_ca); }
    _t4768->needs_main = DEREF(_t4763);
    _t4768->decls_only = DEREF(_t4764);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4768->auto_import = *_ca; free(_ca); }
    _t4768->is_pure = DEREF(_t4765);
    _t4768->debug_prints = DEREF(_t4766);
    (void)_t4768;
    _t4769 = malloc(sizeof(Bool));
    *_t4769 = 1;
    (void)_t4769;
    _t4770 = malloc(sizeof(Bool));
    *_t4770 = 1;
    (void)_t4770;
    _t4771 = malloc(sizeof(Bool));
    *_t4771 = 0;
    (void)_t4771;
    _t4772 = malloc(sizeof(Bool));
    *_t4772 = 0;
    (void)_t4772;
    _t4773 = Str_lit("gui", 3ULL);
    (void)_t4773;
    _t4774 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4774->name = *_ca; free(_ca); }
    _t4774->needs_main = DEREF(_t4769);
    _t4774->decls_only = DEREF(_t4770);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4774->auto_import = *_ca; free(_ca); }
    _t4774->is_pure = DEREF(_t4771);
    _t4774->debug_prints = DEREF(_t4772);
    (void)_t4774;
    _t4775 = malloc(sizeof(Bool));
    *_t4775 = 0;
    (void)_t4775;
    _t4776 = malloc(sizeof(Bool));
    *_t4776 = 1;
    (void)_t4776;
    _t4777 = malloc(sizeof(Bool));
    *_t4777 = 0;
    (void)_t4777;
    _t4778 = malloc(sizeof(Bool));
    *_t4778 = 0;
    (void)_t4778;
    _t4779 = Str_lit("test", 4ULL);
    (void)_t4779;
    _t4780 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4780->name = *_ca; free(_ca); }
    _t4780->needs_main = DEREF(_t4775);
    _t4780->decls_only = DEREF(_t4776);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4780->auto_import = *_ca; free(_ca); }
    _t4780->is_pure = DEREF(_t4777);
    _t4780->debug_prints = DEREF(_t4778);
    (void)_t4780;
    _t4781 = malloc(sizeof(Bool));
    *_t4781 = 0;
    (void)_t4781;
    _t4782 = malloc(sizeof(Bool));
    *_t4782 = 1;
    (void)_t4782;
    _t4783 = malloc(sizeof(Bool));
    *_t4783 = 1;
    (void)_t4783;
    _t4784 = malloc(sizeof(Bool));
    *_t4784 = 0;
    (void)_t4784;
    _t4785 = Str_lit("pure", 4ULL);
    (void)_t4785;
    _t4786 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4786->name = *_ca; free(_ca); }
    _t4786->needs_main = DEREF(_t4781);
    _t4786->decls_only = DEREF(_t4782);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4786->auto_import = *_ca; free(_ca); }
    _t4786->is_pure = DEREF(_t4783);
    _t4786->debug_prints = DEREF(_t4784);
    (void)_t4786;
    _t4787 = malloc(sizeof(Bool));
    *_t4787 = 0;
    (void)_t4787;
    _t4788 = malloc(sizeof(Bool));
    *_t4788 = 1;
    (void)_t4788;
    _t4789 = malloc(sizeof(Bool));
    *_t4789 = 1;
    (void)_t4789;
    _t4790 = malloc(sizeof(Bool));
    *_t4790 = 1;
    (void)_t4790;
    _t4791 = Str_lit("pura", 4ULL);
    (void)_t4791;
    _t4792 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4792->name = *_ca; free(_ca); }
    _t4792->needs_main = DEREF(_t4787);
    _t4792->decls_only = DEREF(_t4788);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4792->auto_import = *_ca; free(_ca); }
    _t4792->is_pure = DEREF(_t4789);
    _t4792->debug_prints = DEREF(_t4790);
    (void)_t4792;
    _t4793 = malloc(sizeof(Bool));
    *_t4793 = 0;
    (void)_t4793;
    _t4794 = malloc(sizeof(Bool));
    *_t4794 = 1;
    (void)_t4794;
    _t4795 = malloc(sizeof(Bool));
    *_t4795 = 0;
    (void)_t4795;
    _t4796 = malloc(sizeof(Bool));
    *_t4796 = 0;
    (void)_t4796;
    _t4797 = Str_lit("lib", 3ULL);
    (void)_t4797;
    _t4798 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4798->name = *_ca; free(_ca); }
    _t4798->needs_main = DEREF(_t4793);
    _t4798->decls_only = DEREF(_t4794);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4798->auto_import = *_ca; free(_ca); }
    _t4798->is_pure = DEREF(_t4795);
    _t4798->debug_prints = DEREF(_t4796);
    (void)_t4798;
    _t4799 = malloc(sizeof(Bool));
    *_t4799 = 0;
    (void)_t4799;
    _t4800 = malloc(sizeof(Bool));
    *_t4800 = 1;
    (void)_t4800;
    _t4801 = malloc(sizeof(Bool));
    *_t4801 = 0;
    (void)_t4801;
    _t4802 = malloc(sizeof(Bool));
    *_t4802 = 1;
    (void)_t4802;
    _t4803 = Str_lit("liba", 4ULL);
    (void)_t4803;
    _t4804 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4804->name = *_ca; free(_ca); }
    _t4804->needs_main = DEREF(_t4799);
    _t4804->decls_only = DEREF(_t4800);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4804->auto_import = *_ca; free(_ca); }
    _t4804->is_pure = DEREF(_t4801);
    _t4804->debug_prints = DEREF(_t4802);
    (void)_t4804;
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
    U64 _t4667; { U64 *_hp = (U64 *)Array_len(args); _t4667 = *_hp; free(_hp); }
    (void)_t4667;
    U64 _t4668 = 0;
    (void)_t4668;
    Bool _t4669 = U64_eq(_t4667, _t4668);
    (void)_t4669;
    ;
    ;
    if (_t4669) {
        usage();
        Str *_t4288 = Str_lit("Str", 3ULL);
        (void)_t4288;
        U64 _t4289; { U64 *_hp = (U64 *)Str_size(); _t4289 = *_hp; free(_hp); }
        (void)_t4289;
        U64 _t4290 = 1;
        (void)_t4290;
        Array *_va85 = Array_new(_t4288, &(U64){_t4289}, &(U64){_t4290});
        (void)_va85;
        Str_delete(_t4288, &(Bool){1});
        ;
        ;
        U64 _t4291 = 0;
        (void)_t4291;
        Str *_t4292 = Str_lit("no arguments", 12ULL);
        (void)_t4292;
        Array_set(_va85, &(U64){_t4291}, _t4292);
        ;
        Str *_t4293 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4293;
        panic(_t4293, _va85);
        Str_delete(_t4293, &(Bool){1});
    }
    ;
    U64 *_t4670 = malloc(sizeof(U64));
    *_t4670 = 0;
    (void)_t4670;
    Str *cmd_ref = Array_get(args, _t4670);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4670, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4671; { U64 *_hp = (U64 *)Array_len(args); _t4671 = *_hp; free(_hp); }
    (void)_t4671;
    U64 _t4672 = 1;
    (void)_t4672;
    Bool _t4673 = U64_eq(_t4671, _t4672);
    (void)_t4673;
    ;
    ;
    if (_t4673) {
        Str *_t4294 = Str_lit("help", 4ULL);
        (void)_t4294;
        Str *_t4295 = Str_lit("--help", 6ULL);
        (void)_t4295;
        Bool _t4296; { Bool *_hp = (Bool *)Str_eq(command, _t4294); _t4296 = *_hp; free(_hp); }
        (void)_t4296;
        Str_delete(_t4294, &(Bool){1});
        Bool _t4297; { Bool *_hp = (Bool *)Str_eq(command, _t4295); _t4297 = *_hp; free(_hp); }
        (void)_t4297;
        Str_delete(_t4295, &(Bool){1});
        Bool _t4298 = Bool_or(_t4296, _t4297);
        (void)_t4298;
        ;
        ;
        if (_t4298) {
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
            U64 _t4315; { U64 *_hp = (U64 *)Array_len(args); _t4315 = *_hp; free(_hp); }
            (void)_t4315;
            Bool _wcond4299; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4315}); _wcond4299 = *_hp; free(_hp); }
            (void)_wcond4299;
            ;
            if (_wcond4299) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4316 = Str_lit("-o", 2ULL);
            (void)_t4316;
            U64 _t4317 = 1;
            (void)_t4317;
            U64 _t4318 = U64_add(DEREF(path_idx), _t4317);
            (void)_t4318;
            ;
            U64 _t4319; { U64 *_hp = (U64 *)Array_len(args); _t4319 = *_hp; free(_hp); }
            (void)_t4319;
            Bool _t4320; { Bool *_hp = (Bool *)Str_eq(flag, _t4316); _t4320 = *_hp; free(_hp); }
            (void)_t4320;
            Str_delete(_t4316, &(Bool){1});
            Bool _t4321; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4318}, &(U64){_t4319}); _t4321 = *_hp; free(_hp); }
            (void)_t4321;
            ;
            ;
            Bool _t4322 = Bool_and(_t4320, _t4321);
            (void)_t4322;
            ;
            ;
            if (_t4322) {
                U64 _t4300 = 1;
                (void)_t4300;
                U64 *_t4301 = malloc(sizeof(U64)); *_t4301 = U64_add(DEREF(path_idx), _t4300);
                (void)_t4301;
                ;
                Str *oval = Array_get(args, _t4301);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4301, &(Bool){1});
                U64 _t4302 = 2;
                (void)_t4302;
                U64 _t4303 = U64_add(DEREF(path_idx), _t4302);
                (void)_t4303;
                ;
                *path_idx = _t4303;
                ;
            } else {
                Str *_t4308 = Str_lit("-c", 2ULL);
                (void)_t4308;
                U64 _t4309 = 1;
                (void)_t4309;
                U64 _t4310 = U64_add(DEREF(path_idx), _t4309);
                (void)_t4310;
                ;
                U64 _t4311; { U64 *_hp = (U64 *)Array_len(args); _t4311 = *_hp; free(_hp); }
                (void)_t4311;
                Bool _t4312; { Bool *_hp = (Bool *)Str_eq(flag, _t4308); _t4312 = *_hp; free(_hp); }
                (void)_t4312;
                Str_delete(_t4308, &(Bool){1});
                Bool _t4313; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4310}, &(U64){_t4311}); _t4313 = *_hp; free(_hp); }
                (void)_t4313;
                ;
                ;
                Bool _t4314 = Bool_and(_t4312, _t4313);
                (void)_t4314;
                ;
                ;
                if (_t4314) {
                    U64 _t4304 = 1;
                    (void)_t4304;
                    U64 *_t4305 = malloc(sizeof(U64)); *_t4305 = U64_add(DEREF(path_idx), _t4304);
                    (void)_t4305;
                    ;
                    Str *cval = Array_get(args, _t4305);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4305, &(Bool){1});
                    U64 _t4306 = 2;
                    (void)_t4306;
                    U64 _t4307 = U64_add(DEREF(path_idx), _t4306);
                    (void)_t4307;
                    ;
                    *path_idx = _t4307;
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
    Str *_t4674 = Str_lit("help", 4ULL);
    (void)_t4674;
    Str *_t4675 = Str_lit("--help", 6ULL);
    (void)_t4675;
    Bool _t4676; { Bool *_hp = (Bool *)Str_eq(command, _t4674); _t4676 = *_hp; free(_hp); }
    (void)_t4676;
    Str_delete(_t4674, &(Bool){1});
    Bool _t4677; { Bool *_hp = (Bool *)Str_eq(command, _t4675); _t4677 = *_hp; free(_hp); }
    (void)_t4677;
    Str_delete(_t4675, &(Bool){1});
    Bool _t4678 = Bool_or(_t4676, _t4677);
    (void)_t4678;
    ;
    ;
    if (_t4678) {
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
    Str *_t4679 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4679;
    Str *core_path = Str_concat(bin_dir, _t4679);
    (void)core_path;
    Str_delete(_t4679, &(Bool){1});
    Str *_t4680 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4680;
    Str *ext_c_path = Str_concat(bin_dir, _t4680);
    (void)ext_c_path;
    Str_delete(_t4680, &(Bool){1});
    Str *_t4681 = Str_lit("Str", 3ULL);
    (void)_t4681;
    U64 _t4682; { U64 *_hp = (U64 *)Str_size(); _t4682 = *_hp; free(_hp); }
    (void)_t4682;
    Set *resolved = Set_new(_t4681, &(U64){_t4682});
    (void)resolved;
    Str_delete(_t4681, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4683; { U64 *_hp = (U64 *)Str_len(abs_path); _t4683 = *_hp; free(_hp); }
    (void)_t4683;
    U64 _t4684 = 0;
    (void)_t4684;
    Bool _t4685; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4683}, &(U64){_t4684}); _t4685 = *_hp; free(_hp); }
    (void)_t4685;
    ;
    ;
    if (_t4685) {
        U64 _t4331; { U64 *_hp = (U64 *)Str_len(abs_path); _t4331 = *_hp; free(_hp); }
        (void)_t4331;
        U64 _t4332 = 1;
        (void)_t4332;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4331, _t4332);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4324 = 0;
            (void)_t4324;
            U8 *_t4325 = Str_get(abs_path, last_slash);
            (void)_t4325;
            U8 _t4326 = 47;
            (void)_t4326;
            Bool _t4327; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4324}); _t4327 = *_hp; free(_hp); }
            (void)_t4327;
            ;
            Bool _t4328; { Bool *_hp = (Bool *)U8_neq(_t4325, &(U8){_t4326}); _t4328 = *_hp; free(_hp); }
            (void)_t4328;
            ;
            Bool _wcond4323 = Bool_and(_t4327, _t4328);
            (void)_wcond4323;
            ;
            ;
            if (_wcond4323) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4329 = 1;
            (void)_t4329;
            U64 _t4330 = U64_sub(DEREF(last_slash), _t4329);
            (void)_t4330;
            ;
            *last_slash = _t4330;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4333 = Str_clone(abs_path);
        (void)_t4333;
        Set_add(resolved, _t4333);
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
    U64 _t4686; { U64 *_hp = (U64 *)Str_len(core_abs); _t4686 = *_hp; free(_hp); }
    (void)_t4686;
    U64 _t4687 = 0;
    (void)_t4687;
    Bool _t4688; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4686}, &(U64){_t4687}); _t4688 = *_hp; free(_hp); }
    (void)_t4688;
    ;
    ;
    if (_t4688) {
        Bool _t4335; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4335 = *_hp; free(_hp); }
        (void)_t4335;
        if (_t4335) {
            Bool _t4334 = 1;
            (void)_t4334;
            skip_core = _t4334;
            ;
        }
        ;
        Str *_t4336 = Str_clone(core_abs);
        (void)_t4336;
        Set_add(resolved, _t4336);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4689; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4689 = *_hp; free(_hp); }
    (void)_t4689;
    U64 _t4690 = 0;
    (void)_t4690;
    Bool _t4691; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4689}, &(U64){_t4690}); _t4691 = *_hp; free(_hp); }
    (void)_t4691;
    ;
    ;
    Bool _t4692 = Bool_not(skip_core);
    (void)_t4692;
    Bool _t4693 = Bool_and(_t4691, _t4692);
    (void)_t4693;
    ;
    ;
    if (_t4693) {
        Str *_t4343 = Str_lit("/src/core", 9ULL);
        (void)_t4343;
        Str *core_dir = Str_concat(bin_dir, _t4343);
        (void)core_dir;
        Str_delete(_t4343, &(Bool){1});
        Str *_t4344 = Str_lit("", 0ULL);
        (void)_t4344;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4344); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4344, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4345 = 0;
        (void)_t4345;
        Bool _t4346; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4345}); _t4346 = *_hp; free(_hp); }
        (void)_t4346;
        ;
        ;
        if (_t4346) {
            Str *_t4337 = Str_lit("Str", 3ULL);
            (void)_t4337;
            U64 _t4338; { U64 *_hp = (U64 *)Str_size(); _t4338 = *_hp; free(_hp); }
            (void)_t4338;
            U64 _t4339 = 1;
            (void)_t4339;
            Array *_va86 = Array_new(_t4337, &(U64){_t4338}, &(U64){_t4339});
            (void)_va86;
            Str_delete(_t4337, &(Bool){1});
            ;
            ;
            U64 _t4340 = 0;
            (void)_t4340;
            Str *_t4341 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4341;
            Array_set(_va86, &(U64){_t4340}, _t4341);
            ;
            Str *_t4342 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4342;
            panic(_t4342, _va86);
            Str_delete(_t4342, &(Bool){1});
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
    Str *_t4694 = Str_lit("script", 6ULL);
    (void)_t4694;
    Mode *cur_mode = mode_resolve(_t4694);
    (void)cur_mode;
    Str_delete(_t4694, &(Bool){1});
    U64 _t4695; { U64 *_hp = (U64 *)Str_len(mode_str); _t4695 = *_hp; free(_hp); }
    (void)_t4695;
    U64 _t4696 = 0;
    (void)_t4696;
    Bool _t4697; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4695}, &(U64){_t4696}); _t4697 = *_hp; free(_hp); }
    (void)_t4697;
    ;
    ;
    if (_t4697) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4356; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4356 = *_hp; free(_hp); }
        (void)_t4356;
        U64 _t4357 = 0;
        (void)_t4357;
        Bool _t4358 = U64_eq(_t4356, _t4357);
        (void)_t4358;
        ;
        ;
        if (_t4358) {
            Str *_t4347 = Str_lit("Str", 3ULL);
            (void)_t4347;
            U64 _t4348; { U64 *_hp = (U64 *)Str_size(); _t4348 = *_hp; free(_hp); }
            (void)_t4348;
            U64 _t4349 = 1;
            (void)_t4349;
            Array *_va87 = Array_new(_t4347, &(U64){_t4348}, &(U64){_t4349});
            (void)_va87;
            Str_delete(_t4347, &(Bool){1});
            ;
            ;
            Str *_t4350 = Str_lit("unknown mode '", 14ULL);
            (void)_t4350;
            Str *_t4351 = Str_concat(_t4350, mode_str);
            (void)_t4351;
            Str_delete(_t4350, &(Bool){1});
            Str *_t4352 = Str_lit("'", 1ULL);
            (void)_t4352;
            U64 _t4353 = 0;
            (void)_t4353;
            Str *_t4354 = Str_concat(_t4351, _t4352);
            (void)_t4354;
            Str_delete(_t4351, &(Bool){1});
            Str_delete(_t4352, &(Bool){1});
            Array_set(_va87, &(U64){_t4353}, _t4354);
            ;
            Str *_t4355 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4355;
            panic(_t4355, _va87);
            Str_delete(_t4355, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4698; { U64 *_hp = (U64 *)Vec_len(imports); _t4698 = *_hp; free(_hp); }
    (void)_t4698;
    U64 _t4699 = 0;
    (void)_t4699;
    Bool _t4700; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4698}, &(U64){_t4699}); _t4700 = *_hp; free(_hp); }
    (void)_t4700;
    ;
    ;
    if (_t4700) {
        Str *_t4365 = Str_lit("/src/lib", 8ULL);
        (void)_t4365;
        Str *lib_dir = Str_concat(bin_dir, _t4365);
        (void)lib_dir;
        Str_delete(_t4365, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4366 = 0;
        (void)_t4366;
        Bool _t4367; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4366}); _t4367 = *_hp; free(_hp); }
        (void)_t4367;
        ;
        ;
        if (_t4367) {
            Str *_t4359 = Str_lit("Str", 3ULL);
            (void)_t4359;
            U64 _t4360; { U64 *_hp = (U64 *)Str_size(); _t4360 = *_hp; free(_hp); }
            (void)_t4360;
            U64 _t4361 = 1;
            (void)_t4361;
            Array *_va88 = Array_new(_t4359, &(U64){_t4360}, &(U64){_t4361});
            (void)_va88;
            Str_delete(_t4359, &(Bool){1});
            ;
            ;
            U64 _t4362 = 0;
            (void)_t4362;
            Str *_t4363 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4363;
            Array_set(_va88, &(U64){_t4362}, _t4363);
            ;
            Str *_t4364 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4364;
            panic(_t4364, _va88);
            Str_delete(_t4364, &(Bool){1});
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
    Bool _t4701 = Bool_not(skip_core);
    (void)_t4701;
    ;
    if (_t4701) {
        while (1) {
            U32 _t4369 = expr_nchildren(core_ast);
            (void)_t4369;
            Bool _wcond4368; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4369}); _wcond4368 = *_hp; free(_hp); }
            (void)_wcond4368;
            ;
            if (_wcond4368) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4370 = 1;
            (void)_t4370;
            U32 _t4371 = U32_add(DEREF(i), _t4370);
            (void)_t4371;
            ;
            *i = _t4371;
            ;
        }
        U32 _t4376 = 0;
        (void)_t4376;
        *i = _t4376;
        ;
        while (1) {
            U32 _t4373 = expr_vec_count(core_import_decls);
            (void)_t4373;
            Bool _wcond4372; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4373}); _wcond4372 = *_hp; free(_hp); }
            (void)_wcond4372;
            ;
            if (_wcond4372) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4374 = 1;
            (void)_t4374;
            U32 _t4375 = U32_add(DEREF(i), _t4374);
            (void)_t4375;
            ;
            *i = _t4375;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4702; { U64 *_hp = (U64 *)Str_len(auto_import); _t4702 = *_hp; free(_hp); }
    (void)_t4702;
    U64 _t4703 = 0;
    (void)_t4703;
    Bool _t4704; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4702}, &(U64){_t4703}); _t4704 = *_hp; free(_hp); }
    (void)_t4704;
    ;
    ;
    if (_t4704) {
        Str *_t4381 = Str_lit("/src/modes/", 11ULL);
        (void)_t4381;
        Str *_t4382 = Str_concat(bin_dir, _t4381);
        (void)_t4382;
        Str_delete(_t4381, &(Bool){1});
        Str *_t4383 = Str_concat(_t4382, auto_import);
        (void)_t4383;
        Str_delete(_t4382, &(Bool){1});
        Str *_t4384 = Str_lit(".til", 4ULL);
        (void)_t4384;
        Str *mode_til_path = Str_concat(_t4383, _t4384);
        (void)mode_til_path;
        Str_delete(_t4383, &(Bool){1});
        Str_delete(_t4384, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4385 = 0;
        (void)_t4385;
        *i = _t4385;
        ;
        while (1) {
            U32 _t4378 = expr_nchildren(mode_ast);
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
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4379 = 1;
            (void)_t4379;
            U32 _t4380 = U32_add(DEREF(i), _t4379);
            (void)_t4380;
            ;
            *i = _t4380;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4705 = 0;
    (void)_t4705;
    *i = _t4705;
    ;
    while (1) {
        U32 _t4387 = expr_vec_count(import_decls);
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
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
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
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4706 = 0;
    (void)_t4706;
    *i = _t4706;
    ;
    while (1) {
        U32 _t4391 = expr_nchildren(ast);
        (void)_t4391;
        Bool _wcond4390; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4391}); _wcond4390 = *_hp; free(_hp); }
        (void)_wcond4390;
        ;
        if (_wcond4390) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4392 = 1;
        (void)_t4392;
        U32 _t4393 = U32_add(DEREF(i), _t4392);
        (void)_t4393;
        ;
        *i = _t4393;
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
    U32 _t4707 = 0;
    (void)_t4707;
    *i = _t4707;
    ;
    while (1) {
        U32 _t4409 = expr_nchildren(ast);
        (void)_t4409;
        Bool _wcond4394; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4409}); _wcond4394 = *_hp; free(_hp); }
        (void)_wcond4394;
        ;
        if (_wcond4394) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4410 = expr_get_tag(stmt);
        (void)_t4410;
        U32 _t4411 = expr_nchildren(stmt);
        (void)_t4411;
        U32 _t4412 = 2;
        (void)_t4412;
        Bool _t4413 = I32_eq(_t4410, DEREF(NODE_FCALL));
        (void)_t4413;
        ;
        Bool _t4414 = U32_eq(_t4411, _t4412);
        (void)_t4414;
        ;
        ;
        U32 *_t4415 = malloc(sizeof(U32));
        *_t4415 = 0;
        (void)_t4415;
        Expr *_t4416 = expr_get_child(stmt, DEREF(_t4415));
        (void)_t4416;
        I32 _t4417 = expr_get_tag(_t4416);
        (void)_t4417;
        U32_delete(_t4415, &(Bool){1});
        Bool _t4418 = Bool_and(_t4413, _t4414);
        (void)_t4418;
        ;
        ;
        Bool _t4419 = I32_eq(_t4417, DEREF(NODE_IDENT));
        (void)_t4419;
        ;
        U32 *_t4420 = malloc(sizeof(U32));
        *_t4420 = 1;
        (void)_t4420;
        Expr *_t4421 = expr_get_child(stmt, DEREF(_t4420));
        (void)_t4421;
        I32 _t4422 = expr_get_tag(_t4421);
        (void)_t4422;
        U32_delete(_t4420, &(Bool){1});
        Bool _t4423 = Bool_and(_t4418, _t4419);
        (void)_t4423;
        ;
        ;
        Bool _t4424 = I32_eq(_t4422, DEREF(NODE_LITERAL_STR));
        (void)_t4424;
        ;
        Bool _t4425 = Bool_and(_t4423, _t4424);
        (void)_t4425;
        ;
        ;
        if (_t4425) {
            U32 *_t4403 = malloc(sizeof(U32));
            *_t4403 = 0;
            (void)_t4403;
            Expr *_t4404 = expr_get_child(stmt, DEREF(_t4403));
            (void)_t4404;
            Str *fname = expr_get_str_val(_t4404);
            (void)fname;
            U32 *_t4405 = malloc(sizeof(U32));
            *_t4405 = 1;
            (void)_t4405;
            Expr *_t4406 = expr_get_child(stmt, DEREF(_t4405));
            (void)_t4406;
            Str *arg = expr_get_str_val(_t4406);
            (void)arg;
            Str *_t4407 = Str_lit("link", 4ULL);
            (void)_t4407;
            Bool _t4408; { Bool *_hp = (Bool *)Str_eq(fname, _t4407); _t4408 = *_hp; free(_hp); }
            (void)_t4408;
            Str_delete(_t4407, &(Bool){1});
            if (_t4408) {
                Str *_t4395 = Str_lit(" -l", 3ULL);
                (void)_t4395;
                Str *_t4396 = Str_concat(link_flags, _t4395);
                (void)_t4396;
                Str_delete(_t4395, &(Bool){1});
                link_flags = Str_concat(_t4396, arg);
                Str_delete(_t4396, &(Bool){1});
            } else {
                Str *_t4401 = Str_lit("link_c", 6ULL);
                (void)_t4401;
                Bool _t4402; { Bool *_hp = (Bool *)Str_eq(fname, _t4401); _t4402 = *_hp; free(_hp); }
                (void)_t4402;
                Str_delete(_t4401, &(Bool){1});
                if (_t4402) {
                    U64 _t4398; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4398 = *_hp; free(_hp); }
                    (void)_t4398;
                    U64 _t4399 = 0;
                    (void)_t4399;
                    Bool _t4400; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4398}, &(U64){_t4399}); _t4400 = *_hp; free(_hp); }
                    (void)_t4400;
                    ;
                    ;
                    if (_t4400) {
                        Str *_t4397 = Str_lit(" ", 1ULL);
                        (void)_t4397;
                        link_c_paths = Str_concat(link_c_paths, _t4397);
                        Str_delete(_t4397, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4403, &(Bool){1});
            U32_delete(_t4405, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4426 = 1;
        (void)_t4426;
        U32 _t4427 = U32_add(DEREF(i), _t4426);
        (void)_t4427;
        ;
        *i = _t4427;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4708 = init_declarations(ast, scope);
    (void)_t4708;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4709 = 0;
    (void)_t4709;
    Bool _t4710; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4709}); _t4710 = *_hp; free(_hp); }
    (void)_t4710;
    ;
    if (_t4710) {
        Str *_t4428 = Str_lit("Str", 3ULL);
        (void)_t4428;
        U64 _t4429; { U64 *_hp = (U64 *)Str_size(); _t4429 = *_hp; free(_hp); }
        (void)_t4429;
        U64 _t4430 = 1;
        (void)_t4430;
        Array *_va89 = Array_new(_t4428, &(U64){_t4429}, &(U64){_t4430});
        (void)_va89;
        Str_delete(_t4428, &(Bool){1});
        ;
        ;
        Str *_t4431 = I32_to_str(&(I32){type_errors});
        (void)_t4431;
        Str *_t4432 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4432;
        U64 _t4433 = 0;
        (void)_t4433;
        Str *_t4434 = Str_concat(_t4431, _t4432);
        (void)_t4434;
        Str_delete(_t4431, &(Bool){1});
        Str_delete(_t4432, &(Bool){1});
        Array_set(_va89, &(U64){_t4433}, _t4434);
        ;
        Str *_t4435 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4435;
        panic(_t4435, _va89);
        Str_delete(_t4435, &(Bool){1});
    }
    ;
    ;
    Str *_t4711 = Str_lit("test", 4ULL);
    (void)_t4711;
    Str *_t4712 = Str_lit("test", 4ULL);
    (void)_t4712;
    Bool _t4713; { Bool *_hp = (Bool *)Str_eq(command, _t4711); _t4713 = *_hp; free(_hp); }
    (void)_t4713;
    Str_delete(_t4711, &(Bool){1});
    Bool _t4714; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4712); _t4714 = *_hp; free(_hp); }
    (void)_t4714;
    Str_delete(_t4712, &(Bool){1});
    Str *_t4715 = Str_lit("pure", 4ULL);
    (void)_t4715;
    Bool _t4716 = Bool_or(_t4713, _t4714);
    (void)_t4716;
    ;
    ;
    Bool _t4717; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4715); _t4717 = *_hp; free(_hp); }
    (void)_t4717;
    Str_delete(_t4715, &(Bool){1});
    Str *_t4718 = Str_lit("pura", 4ULL);
    (void)_t4718;
    Bool _t4719 = Bool_or(_t4716, _t4717);
    (void)_t4719;
    ;
    ;
    Bool _t4720; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4718); _t4720 = *_hp; free(_hp); }
    (void)_t4720;
    Str_delete(_t4718, &(Bool){1});
    Bool run_tests = Bool_or(_t4719, _t4720);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4721 = Str_lit("translate", 9ULL);
    (void)_t4721;
    Str *_t4722 = Str_lit("build", 5ULL);
    (void)_t4722;
    Bool _t4723; { Bool *_hp = (Bool *)Str_eq(command, _t4721); _t4723 = *_hp; free(_hp); }
    (void)_t4723;
    Str_delete(_t4721, &(Bool){1});
    Bool _t4724; { Bool *_hp = (Bool *)Str_eq(command, _t4722); _t4724 = *_hp; free(_hp); }
    (void)_t4724;
    Str_delete(_t4722, &(Bool){1});
    Bool _t4725; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4725 = *_hp; free(_hp); }
    (void)_t4725;
    Bool _t4726 = Bool_or(_t4723, _t4724);
    (void)_t4726;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4725, _t4726);
    (void)is_lib_target;
    ;
    ;
    U64 _t4727; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4727 = *_hp; free(_hp); }
    (void)_t4727;
    U64 _t4728 = 0;
    (void)_t4728;
    Bool _t4729 = Bool_not(is_lib_target);
    (void)_t4729;
    ;
    Bool _t4730 = U64_eq(_t4727, _t4728);
    (void)_t4730;
    ;
    ;
    Bool _t4731 = Bool_and(_t4729, _t4730);
    (void)_t4731;
    ;
    ;
    if (_t4731) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4732; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4732 = *_hp; free(_hp); }
    (void)_t4732;
    U64 _t4733 = 0;
    (void)_t4733;
    Bool _t4734; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4732}, &(U64){_t4733}); _t4734 = *_hp; free(_hp); }
    (void)_t4734;
    ;
    ;
    if (_t4734) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4735 = Str_lit("Str", 3ULL);
    (void)_t4735;
    U64 _t4736; { U64 *_hp = (U64 *)Str_size(); _t4736 = *_hp; free(_hp); }
    (void)_t4736;
    Vec *user_argv = Vec_new(_t4735, &(U64){_t4736});
    (void)user_argv;
    Str_delete(_t4735, &(Bool){1});
    ;
    U64 _t4737 = 1;
    (void)_t4737;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4737);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4452; { U64 *_hp = (U64 *)Array_len(args); _t4452 = *_hp; free(_hp); }
        (void)_t4452;
        Bool _wcond4436; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4452}); _wcond4436 = *_hp; free(_hp); }
        (void)_wcond4436;
        ;
        if (_wcond4436) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4453 = Str_lit("-l", 2ULL);
        (void)_t4453;
        Bool _t4454; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4453); _t4454 = *_hp; free(_hp); }
        (void)_t4454;
        Str_delete(_t4453, &(Bool){1});
        if (_t4454) {
            U64 _t4439 = 2;
            (void)_t4439;
            U64 _t4440; { U64 *_hp = (U64 *)Str_len(arg); _t4440 = *_hp; free(_hp); }
            (void)_t4440;
            Str *lib = Str_substr(arg, &(U64){_t4439}, &(U64){_t4440});
            (void)lib;
            ;
            ;
            U64 _t4441; { U64 *_hp = (U64 *)Str_len(lib); _t4441 = *_hp; free(_hp); }
            (void)_t4441;
            U64 _t4442 = 0;
            (void)_t4442;
            U64 _t4443 = 1;
            (void)_t4443;
            U64 _t4444 = U64_add(DEREF(ai), _t4443);
            (void)_t4444;
            ;
            U64 _t4445; { U64 *_hp = (U64 *)Array_len(args); _t4445 = *_hp; free(_hp); }
            (void)_t4445;
            Bool _t4446 = U64_eq(_t4441, _t4442);
            (void)_t4446;
            ;
            ;
            Bool _t4447; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4444}, &(U64){_t4445}); _t4447 = *_hp; free(_hp); }
            (void)_t4447;
            ;
            ;
            Bool _t4448 = Bool_and(_t4446, _t4447);
            (void)_t4448;
            ;
            ;
            if (_t4448) {
                U64 _t4437 = 1;
                (void)_t4437;
                U64 _t4438 = U64_add(DEREF(ai), _t4437);
                (void)_t4438;
                ;
                *ai = _t4438;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4449 = Str_lit(" -l", 3ULL);
            (void)_t4449;
            Str *_t4450 = Str_concat(link_flags, _t4449);
            (void)_t4450;
            Str_delete(_t4449, &(Bool){1});
            link_flags = Str_concat(_t4450, lib);
            Str_delete(_t4450, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4451 = Str_clone(arg);
            (void)_t4451;
            Vec_push(user_argv, _t4451);
        }
        ;
        U64 _t4455 = 1;
        (void)_t4455;
        U64 _t4456 = U64_add(DEREF(ai), _t4455);
        (void)_t4456;
        ;
        *ai = _t4456;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4738; { U64 *_hp = (U64 *)Str_len(link_flags); _t4738 = *_hp; free(_hp); }
    (void)_t4738;
    U64 _t4739 = 0;
    (void)_t4739;
    Bool _t4740; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4738}, &(U64){_t4739}); _t4740 = *_hp; free(_hp); }
    (void)_t4740;
    ;
    ;
    if (_t4740) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4741 = Str_lit("interpret", 9ULL);
    (void)_t4741;
    Str *_t4742 = Str_lit("test", 4ULL);
    (void)_t4742;
    Bool _t4743; { Bool *_hp = (Bool *)Str_eq(command, _t4741); _t4743 = *_hp; free(_hp); }
    (void)_t4743;
    Str_delete(_t4741, &(Bool){1});
    Bool _t4744; { Bool *_hp = (Bool *)Str_eq(command, _t4742); _t4744 = *_hp; free(_hp); }
    (void)_t4744;
    Str_delete(_t4742, &(Bool){1});
    Bool _t4745 = Bool_or(_t4743, _t4744);
    (void)_t4745;
    ;
    ;
    if (_t4745) {
        Str *_t4463 = Str_lit("interpret", 9ULL);
        (void)_t4463;
        Bool _t4464; { Bool *_hp = (Bool *)Str_eq(command, _t4463); _t4464 = *_hp; free(_hp); }
        (void)_t4464;
        Str_delete(_t4463, &(Bool){1});
        Bool _t4465 = Bool_and(is_lib_mode, _t4464);
        (void)_t4465;
        ;
        if (_t4465) {
            Str *_t4457 = Str_lit("Str", 3ULL);
            (void)_t4457;
            U64 _t4458; { U64 *_hp = (U64 *)Str_size(); _t4458 = *_hp; free(_hp); }
            (void)_t4458;
            U64 _t4459 = 1;
            (void)_t4459;
            Array *_va90 = Array_new(_t4457, &(U64){_t4458}, &(U64){_t4459});
            (void)_va90;
            Str_delete(_t4457, &(Bool){1});
            ;
            ;
            U64 _t4460 = 0;
            (void)_t4460;
            Str *_t4461 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4461;
            Array_set(_va90, &(U64){_t4460}, _t4461);
            ;
            Str *_t4462 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4462;
            panic(_t4462, _va90);
            Str_delete(_t4462, &(Bool){1});
        }
        ;
        I32 _t4466 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4466;
        result = _t4466;
        ;
    } else {
        Str *_t4659 = Str_lit("translate", 9ULL);
        (void)_t4659;
        Str *_t4660 = Str_lit("build", 5ULL);
        (void)_t4660;
        Bool _t4661; { Bool *_hp = (Bool *)Str_eq(command, _t4659); _t4661 = *_hp; free(_hp); }
        (void)_t4661;
        Str_delete(_t4659, &(Bool){1});
        Bool _t4662; { Bool *_hp = (Bool *)Str_eq(command, _t4660); _t4662 = *_hp; free(_hp); }
        (void)_t4662;
        Str_delete(_t4660, &(Bool){1});
        Str *_t4663 = Str_lit("run", 3ULL);
        (void)_t4663;
        Bool _t4664 = Bool_or(_t4661, _t4662);
        (void)_t4664;
        ;
        ;
        Bool _t4665; { Bool *_hp = (Bool *)Str_eq(command, _t4663); _t4665 = *_hp; free(_hp); }
        (void)_t4665;
        Str_delete(_t4663, &(Bool){1});
        Bool _t4666 = Bool_or(_t4664, _t4665);
        (void)_t4666;
        ;
        ;
        if (_t4666) {
            Str *_t4592 = Str_lit("run", 3ULL);
            (void)_t4592;
            Bool _t4593; { Bool *_hp = (Bool *)Str_eq(command, _t4592); _t4593 = *_hp; free(_hp); }
            (void)_t4593;
            Str_delete(_t4592, &(Bool){1});
            Bool _t4594 = Bool_and(is_lib_mode, _t4593);
            (void)_t4594;
            ;
            if (_t4594) {
                Str *_t4467 = Str_lit("Str", 3ULL);
                (void)_t4467;
                U64 _t4468; { U64 *_hp = (U64 *)Str_size(); _t4468 = *_hp; free(_hp); }
                (void)_t4468;
                U64 _t4469 = 1;
                (void)_t4469;
                Array *_va91 = Array_new(_t4467, &(U64){_t4468}, &(U64){_t4469});
                (void)_va91;
                Str_delete(_t4467, &(Bool){1});
                ;
                ;
                U64 _t4470 = 0;
                (void)_t4470;
                Str *_t4471 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4471;
                Array_set(_va91, &(U64){_t4470}, _t4471);
                ;
                Str *_t4472 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4472;
                panic(_t4472, _va91);
                Str_delete(_t4472, &(Bool){1});
            }
            ;
            Str *_t4595 = Str_lit("/", 1ULL);
            (void)_t4595;
            I64 *last_slash = Str_rfind(path, _t4595);
            (void)last_slash;
            Str_delete(_t4595, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4596 = 0;
            (void)_t4596;
            Bool _t4597; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4596}); _t4597 = *_hp; free(_hp); }
            (void)_t4597;
            ;
            if (_t4597) {
                I64 _t4473 = 1;
                (void)_t4473;
                I64 _t4474 = I64_add(DEREF(last_slash), _t4473);
                (void)_t4474;
                ;
                U64 _t4475; { U64 *_hp = (U64 *)Str_len(path); _t4475 = *_hp; free(_hp); }
                (void)_t4475;
                U64 _t4476 = I64_to_u64(DEREF(last_slash));
                (void)_t4476;
                U64 _t4477 = U64_sub(_t4475, _t4476);
                (void)_t4477;
                ;
                ;
                U64 _t4478 = 1;
                (void)_t4478;
                U64 _t4479 = I64_to_u64(_t4474);
                (void)_t4479;
                ;
                U64 _t4480 = U64_sub(_t4477, _t4478);
                (void)_t4480;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4479}, &(U64){_t4480});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4598 = Str_lit(".til", 4ULL);
            (void)_t4598;
            Bool _t4599; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4598); _t4599 = *_hp; free(_hp); }
            (void)_t4599;
            Str_delete(_t4598, &(Bool){1});
            if (_t4599) {
                U64 _t4481 = 4;
                (void)_t4481;
                U64 _t4482 = U64_sub(name_len, _t4481);
                (void)_t4482;
                ;
                name_len = _t4482;
                ;
            }
            ;
            U64 _t4600 = 0;
            (void)_t4600;
            Str *name = Str_substr(basename, &(U64){_t4600}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4601 = Str_lit("gen/til/", 8ULL);
            (void)_t4601;
            Str *_t4602 = Str_concat(_t4601, name);
            (void)_t4602;
            Str_delete(_t4601, &(Bool){1});
            Str *_t4603 = Str_lit(".c", 2ULL);
            (void)_t4603;
            Str *c_path = Str_concat(_t4602, _t4603);
            (void)c_path;
            Str_delete(_t4602, &(Bool){1});
            Str_delete(_t4603, &(Bool){1});
            U64 _t4604; { U64 *_hp = (U64 *)Str_len(custom_c); _t4604 = *_hp; free(_hp); }
            (void)_t4604;
            U64 _t4605 = 0;
            (void)_t4605;
            Bool _t4606; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4604}, &(U64){_t4605}); _t4606 = *_hp; free(_hp); }
            (void)_t4606;
            ;
            ;
            if (_t4606) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4607 = Str_lit("bin/til/", 8ULL);
            (void)_t4607;
            Str *bin_path = Str_concat(_t4607, name);
            (void)bin_path;
            Str_delete(_t4607, &(Bool){1});
            U64 _t4608; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4608 = *_hp; free(_hp); }
            (void)_t4608;
            U64 _t4609 = 0;
            (void)_t4609;
            Bool _t4610; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4608}, &(U64){_t4609}); _t4610 = *_hp; free(_hp); }
            (void)_t4610;
            ;
            ;
            if (_t4610) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4611 = Str_lit("run", 3ULL);
            (void)_t4611;
            Bool _t4612; { Bool *_hp = (Bool *)Str_eq(command, _t4611); _t4612 = *_hp; free(_hp); }
            (void)_t4612;
            Str_delete(_t4611, &(Bool){1});
            Bool _t4613; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4613 = *_hp; free(_hp); }
            (void)_t4613;
            Bool _t4614 = Bool_not(_t4612);
            (void)_t4614;
            ;
            Bool do_lib = Bool_and(_t4613, _t4614);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4483 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4483;
                I32 _t4484 = til_system(_t4483);
                (void)_t4484;
                Str_delete(_t4483, &(Bool){1});
                ;
            } else {
                Str *_t4489 = Str_lit("/", 1ULL);
                (void)_t4489;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4489); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4489, &(Bool){1});
                Str *_t4490 = Str_lit("/", 1ULL);
                (void)_t4490;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4490); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4490, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4491 = 0;
                (void)_t4491;
                Bool _t4492; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4491}); _t4492 = *_hp; free(_hp); }
                (void)_t4492;
                ;
                if (_t4492) {
                    U64 _t4485 = 0;
                    (void)_t4485;
                    U64 _t4486 = I64_to_u64(cp_slash);
                    (void)_t4486;
                    cp_dir = Str_substr(c_path, &(U64){_t4485}, &(U64){_t4486});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4493 = 0;
                (void)_t4493;
                Bool _t4494; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4493}); _t4494 = *_hp; free(_hp); }
                (void)_t4494;
                ;
                if (_t4494) {
                    U64 _t4487 = 0;
                    (void)_t4487;
                    U64 _t4488 = I64_to_u64(bp_slash);
                    (void)_t4488;
                    bp_dir = Str_substr(bin_path, &(U64){_t4487}, &(U64){_t4488});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4495 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4495;
                Str *_t4496 = Str_concat(_t4495, cp_dir);
                (void)_t4496;
                Str_delete(_t4495, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4497 = Str_lit(" ", 1ULL);
                (void)_t4497;
                Str *_t4498 = Str_concat(_t4496, _t4497);
                (void)_t4498;
                Str_delete(_t4496, &(Bool){1});
                Str_delete(_t4497, &(Bool){1});
                Str *_t4499 = Str_concat(_t4498, bp_dir);
                (void)_t4499;
                Str_delete(_t4498, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4500 = til_system(_t4499);
                (void)_t4500;
                Str_delete(_t4499, &(Bool){1});
                ;
            }
            I32 _t4615 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4615;
            result = _t4615;
            ;
            I32 _t4616 = 0;
            (void)_t4616;
            Bool _t4617 = I32_eq(result, _t4616);
            (void)_t4617;
            ;
            Bool _t4618 = Bool_and(_t4617, do_lib);
            (void)_t4618;
            ;
            if (_t4618) {
                Str *_t4557 = Str_lit("gen/til/", 8ULL);
                (void)_t4557;
                Str *_t4558 = Str_concat(_t4557, name);
                (void)_t4558;
                Str_delete(_t4557, &(Bool){1});
                Str *_t4559 = Str_lit(".h", 2ULL);
                (void)_t4559;
                Str *h_path = Str_concat(_t4558, _t4559);
                (void)h_path;
                Str_delete(_t4558, &(Bool){1});
                Str_delete(_t4559, &(Bool){1});
                Str *_t4560 = Str_lit("gen/til/", 8ULL);
                (void)_t4560;
                Str *_t4561 = Str_concat(_t4560, name);
                (void)_t4561;
                Str_delete(_t4560, &(Bool){1});
                Str *_t4562 = Str_lit(".til", 4ULL);
                (void)_t4562;
                Str *til_path = Str_concat(_t4561, _t4562);
                (void)til_path;
                Str_delete(_t4561, &(Bool){1});
                Str_delete(_t4562, &(Bool){1});
                I32 _t4563 = build_header(ast, h_path);
                (void)_t4563;
                result = _t4563;
                ;
                I32 _t4564 = 0;
                (void)_t4564;
                Bool _t4565 = I32_eq(result, _t4564);
                (void)_t4565;
                ;
                if (_t4565) {
                    I32 _t4501 = build_til_binding(ast, til_path, name);
                    (void)_t4501;
                    result = _t4501;
                    ;
                }
                ;
                I32 _t4566 = 0;
                (void)_t4566;
                Str *_t4567 = Str_lit("translate", 9ULL);
                (void)_t4567;
                Bool _t4568 = I32_eq(result, _t4566);
                (void)_t4568;
                ;
                Bool _t4569; { Bool *_hp = (Bool *)Str_eq(command, _t4567); _t4569 = *_hp; free(_hp); }
                (void)_t4569;
                Str_delete(_t4567, &(Bool){1});
                Bool _t4570 = Bool_and(_t4568, _t4569);
                (void)_t4570;
                ;
                ;
                if (_t4570) {
                    Str *_t4502 = Str_lit("Str", 3ULL);
                    (void)_t4502;
                    U64 _t4503; { U64 *_hp = (U64 *)Str_size(); _t4503 = *_hp; free(_hp); }
                    (void)_t4503;
                    U64 _t4504 = 1;
                    (void)_t4504;
                    Array *_va92 = Array_new(_t4502, &(U64){_t4503}, &(U64){_t4504});
                    (void)_va92;
                    Str_delete(_t4502, &(Bool){1});
                    ;
                    ;
                    Str *_t4505 = Str_lit("Generated: ", 11ULL);
                    (void)_t4505;
                    U64 _t4506 = 0;
                    (void)_t4506;
                    Str *_t4507 = Str_concat(_t4505, c_path);
                    (void)_t4507;
                    Str_delete(_t4505, &(Bool){1});
                    Array_set(_va92, &(U64){_t4506}, _t4507);
                    ;
                    println(_va92);
                    Str *_t4508 = Str_lit("Str", 3ULL);
                    (void)_t4508;
                    U64 _t4509; { U64 *_hp = (U64 *)Str_size(); _t4509 = *_hp; free(_hp); }
                    (void)_t4509;
                    U64 _t4510 = 1;
                    (void)_t4510;
                    Array *_va93 = Array_new(_t4508, &(U64){_t4509}, &(U64){_t4510});
                    (void)_va93;
                    Str_delete(_t4508, &(Bool){1});
                    ;
                    ;
                    Str *_t4511 = Str_lit("Generated: ", 11ULL);
                    (void)_t4511;
                    U64 _t4512 = 0;
                    (void)_t4512;
                    Str *_t4513 = Str_concat(_t4511, h_path);
                    (void)_t4513;
                    Str_delete(_t4511, &(Bool){1});
                    Array_set(_va93, &(U64){_t4512}, _t4513);
                    ;
                    println(_va93);
                    Str *_t4514 = Str_lit("Str", 3ULL);
                    (void)_t4514;
                    U64 _t4515; { U64 *_hp = (U64 *)Str_size(); _t4515 = *_hp; free(_hp); }
                    (void)_t4515;
                    U64 _t4516 = 1;
                    (void)_t4516;
                    Array *_va94 = Array_new(_t4514, &(U64){_t4515}, &(U64){_t4516});
                    (void)_va94;
                    Str_delete(_t4514, &(Bool){1});
                    ;
                    ;
                    Str *_t4517 = Str_lit("Generated: ", 11ULL);
                    (void)_t4517;
                    U64 _t4518 = 0;
                    (void)_t4518;
                    Str *_t4519 = Str_concat(_t4517, til_path);
                    (void)_t4519;
                    Str_delete(_t4517, &(Bool){1});
                    Array_set(_va94, &(U64){_t4518}, _t4519);
                    ;
                    println(_va94);
                }
                ;
                I32 _t4571 = 0;
                (void)_t4571;
                Str *_t4572 = Str_lit("build", 5ULL);
                (void)_t4572;
                Bool _t4573 = I32_eq(result, _t4571);
                (void)_t4573;
                ;
                Bool _t4574; { Bool *_hp = (Bool *)Str_eq(command, _t4572); _t4574 = *_hp; free(_hp); }
                (void)_t4574;
                Str_delete(_t4572, &(Bool){1});
                Bool _t4575 = Bool_and(_t4573, _t4574);
                (void)_t4575;
                ;
                ;
                if (_t4575) {
                    I32 _t4554 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4554;
                    result = _t4554;
                    ;
                    I32 _t4555 = 0;
                    (void)_t4555;
                    Bool _t4556 = I32_eq(result, _t4555);
                    (void)_t4556;
                    ;
                    if (_t4556) {
                        Str *_t4520 = Str_lit("Str", 3ULL);
                        (void)_t4520;
                        U64 _t4521; { U64 *_hp = (U64 *)Str_size(); _t4521 = *_hp; free(_hp); }
                        (void)_t4521;
                        U64 _t4522 = 1;
                        (void)_t4522;
                        Array *_va95 = Array_new(_t4520, &(U64){_t4521}, &(U64){_t4522});
                        (void)_va95;
                        Str_delete(_t4520, &(Bool){1});
                        ;
                        ;
                        Str *_t4523 = Str_lit("Generated: ", 11ULL);
                        (void)_t4523;
                        U64 _t4524 = 0;
                        (void)_t4524;
                        Str *_t4525 = Str_concat(_t4523, c_path);
                        (void)_t4525;
                        Str_delete(_t4523, &(Bool){1});
                        Array_set(_va95, &(U64){_t4524}, _t4525);
                        ;
                        println(_va95);
                        Str *_t4526 = Str_lit("Str", 3ULL);
                        (void)_t4526;
                        U64 _t4527; { U64 *_hp = (U64 *)Str_size(); _t4527 = *_hp; free(_hp); }
                        (void)_t4527;
                        U64 _t4528 = 1;
                        (void)_t4528;
                        Array *_va96 = Array_new(_t4526, &(U64){_t4527}, &(U64){_t4528});
                        (void)_va96;
                        Str_delete(_t4526, &(Bool){1});
                        ;
                        ;
                        Str *_t4529 = Str_lit("Generated: ", 11ULL);
                        (void)_t4529;
                        U64 _t4530 = 0;
                        (void)_t4530;
                        Str *_t4531 = Str_concat(_t4529, h_path);
                        (void)_t4531;
                        Str_delete(_t4529, &(Bool){1});
                        Array_set(_va96, &(U64){_t4530}, _t4531);
                        ;
                        println(_va96);
                        Str *_t4532 = Str_lit("Str", 3ULL);
                        (void)_t4532;
                        U64 _t4533; { U64 *_hp = (U64 *)Str_size(); _t4533 = *_hp; free(_hp); }
                        (void)_t4533;
                        U64 _t4534 = 1;
                        (void)_t4534;
                        Array *_va97 = Array_new(_t4532, &(U64){_t4533}, &(U64){_t4534});
                        (void)_va97;
                        Str_delete(_t4532, &(Bool){1});
                        ;
                        ;
                        Str *_t4535 = Str_lit("Generated: ", 11ULL);
                        (void)_t4535;
                        U64 _t4536 = 0;
                        (void)_t4536;
                        Str *_t4537 = Str_concat(_t4535, til_path);
                        (void)_t4537;
                        Str_delete(_t4535, &(Bool){1});
                        Array_set(_va97, &(U64){_t4536}, _t4537);
                        ;
                        println(_va97);
                        Str *_t4538 = Str_lit("Str", 3ULL);
                        (void)_t4538;
                        U64 _t4539; { U64 *_hp = (U64 *)Str_size(); _t4539 = *_hp; free(_hp); }
                        (void)_t4539;
                        U64 _t4540 = 1;
                        (void)_t4540;
                        Array *_va98 = Array_new(_t4538, &(U64){_t4539}, &(U64){_t4540});
                        (void)_va98;
                        Str_delete(_t4538, &(Bool){1});
                        ;
                        ;
                        Str *_t4541 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4541;
                        Str *_t4542 = Str_concat(_t4541, name);
                        (void)_t4542;
                        Str_delete(_t4541, &(Bool){1});
                        Str *_t4543 = Str_lit(".so", 3ULL);
                        (void)_t4543;
                        U64 _t4544 = 0;
                        (void)_t4544;
                        Str *_t4545 = Str_concat(_t4542, _t4543);
                        (void)_t4545;
                        Str_delete(_t4542, &(Bool){1});
                        Str_delete(_t4543, &(Bool){1});
                        Array_set(_va98, &(U64){_t4544}, _t4545);
                        ;
                        println(_va98);
                        Str *_t4546 = Str_lit("Str", 3ULL);
                        (void)_t4546;
                        U64 _t4547; { U64 *_hp = (U64 *)Str_size(); _t4547 = *_hp; free(_hp); }
                        (void)_t4547;
                        U64 _t4548 = 1;
                        (void)_t4548;
                        Array *_va99 = Array_new(_t4546, &(U64){_t4547}, &(U64){_t4548});
                        (void)_va99;
                        Str_delete(_t4546, &(Bool){1});
                        ;
                        ;
                        Str *_t4549 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4549;
                        Str *_t4550 = Str_concat(_t4549, name);
                        (void)_t4550;
                        Str_delete(_t4549, &(Bool){1});
                        Str *_t4551 = Str_lit(".a", 2ULL);
                        (void)_t4551;
                        U64 _t4552 = 0;
                        (void)_t4552;
                        Str *_t4553 = Str_concat(_t4550, _t4551);
                        (void)_t4553;
                        Str_delete(_t4550, &(Bool){1});
                        Str_delete(_t4551, &(Bool){1});
                        Array_set(_va99, &(U64){_t4552}, _t4553);
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
            I32 _t4619 = 0;
            (void)_t4619;
            Bool _t4620 = I32_eq(result, _t4619);
            (void)_t4620;
            ;
            Bool _t4621 = Bool_not(do_lib);
            (void)_t4621;
            Str *_t4622 = Str_lit("translate", 9ULL);
            (void)_t4622;
            Bool _t4623 = Bool_and(_t4620, _t4621);
            (void)_t4623;
            ;
            ;
            Bool _t4624; { Bool *_hp = (Bool *)Str_eq(command, _t4622); _t4624 = *_hp; free(_hp); }
            (void)_t4624;
            Str_delete(_t4622, &(Bool){1});
            Bool _t4625 = Bool_and(_t4623, _t4624);
            (void)_t4625;
            ;
            ;
            if (_t4625) {
                Str *_t4576 = Str_lit("Str", 3ULL);
                (void)_t4576;
                U64 _t4577; { U64 *_hp = (U64 *)Str_size(); _t4577 = *_hp; free(_hp); }
                (void)_t4577;
                U64 _t4578 = 1;
                (void)_t4578;
                Array *_va100 = Array_new(_t4576, &(U64){_t4577}, &(U64){_t4578});
                (void)_va100;
                Str_delete(_t4576, &(Bool){1});
                ;
                ;
                Str *_t4579 = Str_lit("Generated: ", 11ULL);
                (void)_t4579;
                U64 _t4580 = 0;
                (void)_t4580;
                Str *_t4581 = Str_concat(_t4579, c_path);
                (void)_t4581;
                Str_delete(_t4579, &(Bool){1});
                Array_set(_va100, &(U64){_t4580}, _t4581);
                ;
                println(_va100);
            }
            ;
            I32 _t4626 = 0;
            (void)_t4626;
            Bool _t4627 = I32_eq(result, _t4626);
            (void)_t4627;
            ;
            Bool _t4628 = Bool_not(do_lib);
            (void)_t4628;
            Str *_t4629 = Str_lit("translate", 9ULL);
            (void)_t4629;
            Bool _t4630; { Bool *_hp = (Bool *)Str_eq(command, _t4629); _t4630 = *_hp; free(_hp); }
            (void)_t4630;
            Str_delete(_t4629, &(Bool){1});
            Bool _t4631 = Bool_and(_t4627, _t4628);
            (void)_t4631;
            ;
            ;
            Bool _t4632 = Bool_not(_t4630);
            (void)_t4632;
            ;
            Bool _t4633 = Bool_and(_t4631, _t4632);
            (void)_t4633;
            ;
            ;
            if (_t4633) {
                I32 _t4582 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4582;
                result = _t4582;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4634 = 0;
            (void)_t4634;
            Bool _t4635 = I32_eq(result, _t4634);
            (void)_t4635;
            ;
            Bool _t4636 = Bool_not(do_lib);
            (void)_t4636;
            ;
            Str *_t4637 = Str_lit("run", 3ULL);
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
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4584; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4584 = *_hp; free(_hp); }
                    (void)_t4584;
                    Bool _wcond4583; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4584}); _wcond4583 = *_hp; free(_hp); }
                    (void)_wcond4583;
                    ;
                    if (_wcond4583) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4585 = Str_lit(" '", 2ULL);
                    (void)_t4585;
                    Str *_t4586 = Str_concat(cmd, _t4585);
                    (void)_t4586;
                    Str_delete(_t4585, &(Bool){1});
                    Str *_t4587 = Str_concat(_t4586, uarg);
                    (void)_t4587;
                    Str_delete(_t4586, &(Bool){1});
                    Str *_t4588 = Str_lit("'", 1ULL);
                    (void)_t4588;
                    cmd = Str_concat(_t4587, _t4588);
                    Str_delete(_t4587, &(Bool){1});
                    Str_delete(_t4588, &(Bool){1});
                    U64 _t4589 = 1;
                    (void)_t4589;
                    U64 _t4590 = U64_add(DEREF(ui), _t4589);
                    (void)_t4590;
                    ;
                    *ui = _t4590;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4591 = til_system(cmd);
                (void)_t4591;
                Str_delete(cmd, &(Bool){1});
                result = _t4591;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4657 = Str_lit("ast", 3ULL);
            (void)_t4657;
            Bool _t4658; { Bool *_hp = (Bool *)Str_eq(command, _t4657); _t4658 = *_hp; free(_hp); }
            (void)_t4658;
            Str_delete(_t4657, &(Bool){1});
            if (_t4658) {
                Str *_t4641 = Str_lit("Str", 3ULL);
                (void)_t4641;
                U64 _t4642; { U64 *_hp = (U64 *)Str_size(); _t4642 = *_hp; free(_hp); }
                (void)_t4642;
                U64 _t4643 = 1;
                (void)_t4643;
                Array *_va101 = Array_new(_t4641, &(U64){_t4642}, &(U64){_t4643});
                (void)_va101;
                Str_delete(_t4641, &(Bool){1});
                ;
                ;
                Str *_t4644 = Str_lit("mode: ", 6ULL);
                (void)_t4644;
                U64 _t4645 = 0;
                (void)_t4645;
                Str *_t4646 = Str_concat(_t4644, &cur_mode->name);
                (void)_t4646;
                Str_delete(_t4644, &(Bool){1});
                Array_set(_va101, &(U64){_t4645}, _t4646);
                ;
                println(_va101);
                U32 _t4647 = 0;
                (void)_t4647;
                ast_print(ast, _t4647);
                ;
            } else {
                Str *_t4648 = Str_lit("Str", 3ULL);
                (void)_t4648;
                U64 _t4649; { U64 *_hp = (U64 *)Str_size(); _t4649 = *_hp; free(_hp); }
                (void)_t4649;
                U64 _t4650 = 1;
                (void)_t4650;
                Array *_va102 = Array_new(_t4648, &(U64){_t4649}, &(U64){_t4650});
                (void)_va102;
                Str_delete(_t4648, &(Bool){1});
                ;
                ;
                Str *_t4651 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4651;
                Str *_t4652 = Str_concat(_t4651, command);
                (void)_t4652;
                Str_delete(_t4651, &(Bool){1});
                Str *_t4653 = Str_lit("'", 1ULL);
                (void)_t4653;
                U64 _t4654 = 0;
                (void)_t4654;
                Str *_t4655 = Str_concat(_t4652, _t4653);
                (void)_t4655;
                Str_delete(_t4652, &(Bool){1});
                Str_delete(_t4653, &(Bool){1});
                Array_set(_va102, &(U64){_t4654}, _t4655);
                ;
                println(_va102);
                usage();
                I32 _t4656 = 1;
                (void)_t4656;
                result = _t4656;
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
    I64 _t4746 = I32_to_i64(result);
    (void)_t4746;
    ;
    exit(_t4746);
    ;
    return 0;
}

