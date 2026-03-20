#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4181 = Str_lit("Str", 3ULL);
    (void)_t4181;
    U64 _t4182; { U64 *_hp = (U64 *)Str_size(); _t4182 = *_hp; free(_hp); }
    (void)_t4182;
    Vec *paths = Vec_new(_t4181, &(U64){_t4182});
    (void)paths;
    Str_delete(_t4181, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4156 = expr_nchildren(body);
        (void)_t4156;
        Bool _wcond4152; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4156}); _wcond4152 = *_hp; free(_hp); }
        (void)_wcond4152;
        ;
        if (_wcond4152) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4157 = expr_get_tag(stmt);
        (void)_t4157;
        U32 _t4158 = expr_nchildren(stmt);
        (void)_t4158;
        U32 _t4159 = 2;
        (void)_t4159;
        Bool _t4160 = I32_eq(_t4157, DEREF(NODE_FCALL));
        (void)_t4160;
        ;
        Bool _t4161 = U32_eq(_t4158, _t4159);
        (void)_t4161;
        ;
        ;
        U32 *_t4162 = malloc(sizeof(U32));
        *_t4162 = 0;
        (void)_t4162;
        Expr *_t4163 = expr_get_child(stmt, DEREF(_t4162));
        (void)_t4163;
        I32 _t4164 = expr_get_tag(_t4163);
        (void)_t4164;
        U32_delete(_t4162, &(Bool){1});
        Bool _t4165 = Bool_and(_t4160, _t4161);
        (void)_t4165;
        ;
        ;
        Bool _t4166 = I32_eq(_t4164, DEREF(NODE_IDENT));
        (void)_t4166;
        ;
        U32 *_t4167 = malloc(sizeof(U32));
        *_t4167 = 0;
        (void)_t4167;
        Expr *_t4168 = expr_get_child(stmt, DEREF(_t4167));
        (void)_t4168;
        Str *_t4169 = expr_get_str_val(_t4168);
        (void)_t4169;
        Str *_t4170 = Str_lit("import", 6ULL);
        (void)_t4170;
        Bool _t4171 = Bool_and(_t4165, _t4166);
        (void)_t4171;
        ;
        ;
        Bool _t4172; { Bool *_hp = (Bool *)Str_eq(_t4169, _t4170); _t4172 = *_hp; free(_hp); }
        (void)_t4172;
        U32_delete(_t4167, &(Bool){1});
        Str_delete(_t4170, &(Bool){1});
        U32 *_t4173 = malloc(sizeof(U32));
        *_t4173 = 1;
        (void)_t4173;
        Expr *_t4174 = expr_get_child(stmt, DEREF(_t4173));
        (void)_t4174;
        I32 _t4175 = expr_get_tag(_t4174);
        (void)_t4175;
        U32_delete(_t4173, &(Bool){1});
        Bool _t4176 = Bool_and(_t4171, _t4172);
        (void)_t4176;
        ;
        ;
        Bool _t4177 = I32_eq(_t4175, DEREF(NODE_LITERAL_STR));
        (void)_t4177;
        ;
        Bool _t4178 = Bool_and(_t4176, _t4177);
        (void)_t4178;
        ;
        ;
        if (_t4178) {
            U32 *_t4153 = malloc(sizeof(U32));
            *_t4153 = 1;
            (void)_t4153;
            Expr *_t4154 = expr_get_child(stmt, DEREF(_t4153));
            (void)_t4154;
            Str *path = expr_get_str_val(_t4154);
            (void)path;
            Str *_t4155 = Str_clone(path);
            (void)_t4155;
            U32_delete(_t4153, &(Bool){1});
            Vec_push(paths, _t4155);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4179 = 1;
        (void)_t4179;
        U32 _t4180 = U32_add(DEREF(i), _t4179);
        (void)_t4180;
        ;
        *i = _t4180;
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
        U64 _t4233 = 0;
        (void)_t4233;
        U64 _t4234; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4234 = *_hp; free(_hp); }
        (void)_t4234;
        Range *_fc4183 = Range_new(_t4233, _t4234);
        (void)_fc4183;
        ;
        ;
        U64 _fi4183 = 0;
        (void)_fi4183;
        while (1) {
            U64 _t4213; { U64 *_hp = (U64 *)Range_len(_fc4183); _t4213 = *_hp; free(_hp); }
            (void)_t4213;
            Bool _wcond4184; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4183}, &(U64){_t4213}); _wcond4184 = *_hp; free(_hp); }
            (void)_wcond4184;
            ;
            if (_wcond4184) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4183, _fi4183);
            (void)i;
            U64 _t4214 = 1;
            (void)_t4214;
            U64 _t4215 = U64_add(_fi4183, _t4214);
            (void)_t4215;
            ;
            _fi4183 = _t4215;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4216 = Str_lit("/", 1ULL);
            (void)_t4216;
            Str *_t4217 = Str_concat(base_dir, _t4216);
            (void)_t4217;
            Str_delete(_t4216, &(Bool){1});
            Str *try_path = Str_concat(_t4217, import_path);
            (void)try_path;
            Str_delete(_t4217, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4218 = Str_lit("", 0ULL);
            (void)_t4218;
            U64 _t4219; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4219 = *_hp; free(_hp); }
            (void)_t4219;
            U64 _t4220 = 0;
            (void)_t4220;
            Bool _t4221; { Bool *_hp = (Bool *)Str_eq(abs, _t4218); _t4221 = *_hp; free(_hp); }
            (void)_t4221;
            Str_delete(_t4218, &(Bool){1});
            Bool _t4222; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4219}, &(U64){_t4220}); _t4222 = *_hp; free(_hp); }
            (void)_t4222;
            ;
            ;
            Bool _t4223 = Bool_and(_t4221, _t4222);
            (void)_t4223;
            ;
            ;
            if (_t4223) {
                Str *_t4185 = Str_lit("/", 1ULL);
                (void)_t4185;
                Str *_t4186 = Str_concat(lib_dir, _t4185);
                (void)_t4186;
                Str_delete(_t4185, &(Bool){1});
                try_path = Str_concat(_t4186, import_path);
                Str_delete(_t4186, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4224 = Str_lit("", 0ULL);
            (void)_t4224;
            Bool _t4225; { Bool *_hp = (Bool *)Str_eq(abs, _t4224); _t4225 = *_hp; free(_hp); }
            (void)_t4225;
            Str_delete(_t4224, &(Bool){1});
            if (_t4225) {
                Str *_t4187 = Str_lit("Str", 3ULL);
                (void)_t4187;
                U64 _t4188; { U64 *_hp = (U64 *)Str_size(); _t4188 = *_hp; free(_hp); }
                (void)_t4188;
                U64 _t4189 = 1;
                (void)_t4189;
                Array *_va75 = Array_new(_t4187, &(U64){_t4188}, &(U64){_t4189});
                (void)_va75;
                Str_delete(_t4187, &(Bool){1});
                ;
                ;
                Str *_t4190 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4190;
                Str *_t4191 = Str_concat(_t4190, import_path);
                (void)_t4191;
                Str_delete(_t4190, &(Bool){1});
                Str *_t4192 = Str_lit("' (from ", 8ULL);
                (void)_t4192;
                Str *_t4193 = Str_concat(_t4191, _t4192);
                (void)_t4193;
                Str_delete(_t4191, &(Bool){1});
                Str_delete(_t4192, &(Bool){1});
                Str *_t4194 = Str_concat(_t4193, base_dir);
                (void)_t4194;
                Str_delete(_t4193, &(Bool){1});
                Str *_t4195 = Str_lit("/)", 2ULL);
                (void)_t4195;
                U64 _t4196 = 0;
                (void)_t4196;
                Str *_t4197 = Str_concat(_t4194, _t4195);
                (void)_t4197;
                Str_delete(_t4194, &(Bool){1});
                Str_delete(_t4195, &(Bool){1});
                Array_set(_va75, &(U64){_t4196}, _t4197);
                ;
                println(_va75);
                I64 _t4198 = 1;
                (void)_t4198;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4183, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4198; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4226; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4226 = *_hp; free(_hp); }
            (void)_t4226;
            if (_t4226) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4227 = Str_clone(abs);
            (void)_t4227;
            Set_add(resolved_set, _t4227);
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
            U64 _t4228; { U64 *_hp = (U64 *)Str_len(abs); _t4228 = *_hp; free(_hp); }
            (void)_t4228;
            U64 _t4229 = 1;
            (void)_t4229;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4228, _t4229);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4200 = 0;
                (void)_t4200;
                U8 *_t4201 = Str_get(abs, last_slash);
                (void)_t4201;
                U8 _t4202 = 47;
                (void)_t4202;
                Bool _t4203; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4200}); _t4203 = *_hp; free(_hp); }
                (void)_t4203;
                ;
                Bool _t4204; { Bool *_hp = (Bool *)U8_neq(_t4201, &(U8){_t4202}); _t4204 = *_hp; free(_hp); }
                (void)_t4204;
                ;
                Bool _wcond4199 = Bool_and(_t4203, _t4204);
                (void)_wcond4199;
                ;
                ;
                if (_wcond4199) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4205 = 1;
                (void)_t4205;
                U64 _t4206 = U64_sub(DEREF(last_slash), _t4205);
                (void)_t4206;
                ;
                *last_slash = _t4206;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4230; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4230 = *_hp; free(_hp); }
            (void)_t4230;
            U64 _t4231 = 0;
            (void)_t4231;
            Bool _t4232; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4230}, &(U64){_t4231}); _t4232 = *_hp; free(_hp); }
            (void)_t4232;
            ;
            ;
            if (_t4232) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4207 = 0;
                (void)_t4207;
                Bool _t4208; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4207}); _t4208 = *_hp; free(_hp); }
                (void)_t4208;
                ;
                if (_t4208) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4183, &(Bool){1});
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
                U32 _t4210 = expr_nchildren(sub_ast);
                (void)_t4210;
                Bool _wcond4209; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4210}); _wcond4209 = *_hp; free(_hp); }
                (void)_wcond4209;
                ;
                if (_wcond4209) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4211 = 1;
                (void)_t4211;
                U32 _t4212 = U32_add(DEREF(k), _t4211);
                (void)_t4212;
                ;
                *k = _t4212;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4183, &(Bool){1});
        ;
    }
    I64 _t4235 = 0;
    (void)_t4235;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4235; return _r; }
}

void usage(void) {
    Str *_t4236 = Str_lit("Str", 3ULL);
    (void)_t4236;
    U64 _t4237; { U64 *_hp = (U64 *)Str_size(); _t4237 = *_hp; free(_hp); }
    (void)_t4237;
    U64 _t4238 = 1;
    (void)_t4238;
    Array *_va76 = Array_new(_t4236, &(U64){_t4237}, &(U64){_t4238});
    (void)_va76;
    Str_delete(_t4236, &(Bool){1});
    ;
    ;
    U64 _t4239 = 0;
    (void)_t4239;
    Str *_t4240 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4240;
    Array_set(_va76, &(U64){_t4239}, _t4240);
    ;
    println(_va76);
    Str *_t4241 = Str_lit("Str", 3ULL);
    (void)_t4241;
    U64 _t4242; { U64 *_hp = (U64 *)Str_size(); _t4242 = *_hp; free(_hp); }
    (void)_t4242;
    U64 _t4243 = 1;
    (void)_t4243;
    Array *_va77 = Array_new(_t4241, &(U64){_t4242}, &(U64){_t4243});
    (void)_va77;
    Str_delete(_t4241, &(Bool){1});
    ;
    ;
    U64 _t4244 = 0;
    (void)_t4244;
    Str *_t4245 = Str_lit("", 0ULL);
    (void)_t4245;
    Array_set(_va77, &(U64){_t4244}, _t4245);
    ;
    println(_va77);
    Str *_t4246 = Str_lit("Str", 3ULL);
    (void)_t4246;
    U64 _t4247; { U64 *_hp = (U64 *)Str_size(); _t4247 = *_hp; free(_hp); }
    (void)_t4247;
    U64 _t4248 = 1;
    (void)_t4248;
    Array *_va78 = Array_new(_t4246, &(U64){_t4247}, &(U64){_t4248});
    (void)_va78;
    Str_delete(_t4246, &(Bool){1});
    ;
    ;
    U64 _t4249 = 0;
    (void)_t4249;
    Str *_t4250 = Str_lit("Commands:", 9ULL);
    (void)_t4250;
    Array_set(_va78, &(U64){_t4249}, _t4250);
    ;
    println(_va78);
    Str *_t4251 = Str_lit("Str", 3ULL);
    (void)_t4251;
    U64 _t4252; { U64 *_hp = (U64 *)Str_size(); _t4252 = *_hp; free(_hp); }
    (void)_t4252;
    U64 _t4253 = 1;
    (void)_t4253;
    Array *_va79 = Array_new(_t4251, &(U64){_t4252}, &(U64){_t4253});
    (void)_va79;
    Str_delete(_t4251, &(Bool){1});
    ;
    ;
    U64 _t4254 = 0;
    (void)_t4254;
    Str *_t4255 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4255;
    Array_set(_va79, &(U64){_t4254}, _t4255);
    ;
    println(_va79);
    Str *_t4256 = Str_lit("Str", 3ULL);
    (void)_t4256;
    U64 _t4257; { U64 *_hp = (U64 *)Str_size(); _t4257 = *_hp; free(_hp); }
    (void)_t4257;
    U64 _t4258 = 1;
    (void)_t4258;
    Array *_va80 = Array_new(_t4256, &(U64){_t4257}, &(U64){_t4258});
    (void)_va80;
    Str_delete(_t4256, &(Bool){1});
    ;
    ;
    U64 _t4259 = 0;
    (void)_t4259;
    Str *_t4260 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4260;
    Array_set(_va80, &(U64){_t4259}, _t4260);
    ;
    println(_va80);
    Str *_t4261 = Str_lit("Str", 3ULL);
    (void)_t4261;
    U64 _t4262; { U64 *_hp = (U64 *)Str_size(); _t4262 = *_hp; free(_hp); }
    (void)_t4262;
    U64 _t4263 = 1;
    (void)_t4263;
    Array *_va81 = Array_new(_t4261, &(U64){_t4262}, &(U64){_t4263});
    (void)_va81;
    Str_delete(_t4261, &(Bool){1});
    ;
    ;
    U64 _t4264 = 0;
    (void)_t4264;
    Str *_t4265 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4265;
    Array_set(_va81, &(U64){_t4264}, _t4265);
    ;
    println(_va81);
    Str *_t4266 = Str_lit("Str", 3ULL);
    (void)_t4266;
    U64 _t4267; { U64 *_hp = (U64 *)Str_size(); _t4267 = *_hp; free(_hp); }
    (void)_t4267;
    U64 _t4268 = 1;
    (void)_t4268;
    Array *_va82 = Array_new(_t4266, &(U64){_t4267}, &(U64){_t4268});
    (void)_va82;
    Str_delete(_t4266, &(Bool){1});
    ;
    ;
    U64 _t4269 = 0;
    (void)_t4269;
    Str *_t4270 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4270;
    Array_set(_va82, &(U64){_t4269}, _t4270);
    ;
    println(_va82);
    Str *_t4271 = Str_lit("Str", 3ULL);
    (void)_t4271;
    U64 _t4272; { U64 *_hp = (U64 *)Str_size(); _t4272 = *_hp; free(_hp); }
    (void)_t4272;
    U64 _t4273 = 1;
    (void)_t4273;
    Array *_va83 = Array_new(_t4271, &(U64){_t4272}, &(U64){_t4273});
    (void)_va83;
    Str_delete(_t4271, &(Bool){1});
    ;
    ;
    U64 _t4274 = 0;
    (void)_t4274;
    Str *_t4275 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4275;
    Array_set(_va83, &(U64){_t4274}, _t4275);
    ;
    println(_va83);
    Str *_t4276 = Str_lit("Str", 3ULL);
    (void)_t4276;
    U64 _t4277; { U64 *_hp = (U64 *)Str_size(); _t4277 = *_hp; free(_hp); }
    (void)_t4277;
    U64 _t4278 = 1;
    (void)_t4278;
    Array *_va84 = Array_new(_t4276, &(U64){_t4277}, &(U64){_t4278});
    (void)_va84;
    Str_delete(_t4276, &(Bool){1});
    ;
    ;
    U64 _t4279 = 0;
    (void)_t4279;
    Str *_t4280 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4280;
    Array_set(_va84, &(U64){_t4279}, _t4280);
    ;
    println(_va84);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4286 = 1;
    (void)_t4286;
    e->is_core = _t4286;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4282 = expr_nchildren(e);
        (void)_t4282;
        Bool _wcond4281; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4282}); _wcond4281 = *_hp; free(_hp); }
        (void)_wcond4281;
        ;
        if (_wcond4281) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4283 = expr_get_child(e, DEREF(i));
        (void)_t4283;
        mark_core(_t4283);
        U32 _t4284 = 1;
        (void)_t4284;
        U32 _t4285 = U32_add(DEREF(i), _t4284);
        (void)_t4285;
        ;
        *i = _t4285;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4746 = malloc(sizeof(I64));
    *_t4746 = 0;
    (void)_t4746;
    _t4747 = malloc(sizeof(I64));
    *_t4747 = 1;
    (void)_t4747;
    _t4748 = malloc(sizeof(I64)); *_t4748 = I64_sub(DEREF(_t4746), DEREF(_t4747));
    (void)_t4748;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4748));
    (void)CAP_LIT;
    _t4749 = malloc(sizeof(I64));
    *_t4749 = 0;
    (void)_t4749;
    _t4750 = malloc(sizeof(I64));
    *_t4750 = 2;
    (void)_t4750;
    _t4751 = malloc(sizeof(I64)); *_t4751 = I64_sub(DEREF(_t4749), DEREF(_t4750));
    (void)_t4751;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4751));
    (void)CAP_VIEW;
    _t4752 = Str_lit("Str", 3ULL);
    (void)_t4752;
    _t4753 = Str_size();
    (void)_t4753;
    _t4754 = Str_lit("Mode", 4ULL);
    (void)_t4754;
    _t4755 = Mode_size();
    (void)_t4755;
    core_modes = Map_new(_t4752, _t4753, _t4754, _t4755);
    (void)core_modes;
    _t4756 = malloc(sizeof(Bool));
    *_t4756 = 0;
    (void)_t4756;
    _t4757 = malloc(sizeof(Bool));
    *_t4757 = 0;
    (void)_t4757;
    _t4758 = malloc(sizeof(Bool));
    *_t4758 = 0;
    (void)_t4758;
    _t4759 = malloc(sizeof(Bool));
    *_t4759 = 0;
    (void)_t4759;
    _t4760 = Str_lit("script", 6ULL);
    (void)_t4760;
    _t4761 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4761->name = *_ca; free(_ca); }
    _t4761->needs_main = DEREF(_t4756);
    _t4761->decls_only = DEREF(_t4757);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4761->auto_import = *_ca; free(_ca); }
    _t4761->is_pure = DEREF(_t4758);
    _t4761->debug_prints = DEREF(_t4759);
    (void)_t4761;
    _t4762 = malloc(sizeof(Bool));
    *_t4762 = 1;
    (void)_t4762;
    _t4763 = malloc(sizeof(Bool));
    *_t4763 = 1;
    (void)_t4763;
    _t4764 = malloc(sizeof(Bool));
    *_t4764 = 0;
    (void)_t4764;
    _t4765 = malloc(sizeof(Bool));
    *_t4765 = 0;
    (void)_t4765;
    _t4766 = Str_lit("cli", 3ULL);
    (void)_t4766;
    _t4767 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4767->name = *_ca; free(_ca); }
    _t4767->needs_main = DEREF(_t4762);
    _t4767->decls_only = DEREF(_t4763);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4767->auto_import = *_ca; free(_ca); }
    _t4767->is_pure = DEREF(_t4764);
    _t4767->debug_prints = DEREF(_t4765);
    (void)_t4767;
    _t4768 = malloc(sizeof(Bool));
    *_t4768 = 1;
    (void)_t4768;
    _t4769 = malloc(sizeof(Bool));
    *_t4769 = 1;
    (void)_t4769;
    _t4770 = malloc(sizeof(Bool));
    *_t4770 = 0;
    (void)_t4770;
    _t4771 = malloc(sizeof(Bool));
    *_t4771 = 0;
    (void)_t4771;
    _t4772 = Str_lit("gui", 3ULL);
    (void)_t4772;
    _t4773 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4773->name = *_ca; free(_ca); }
    _t4773->needs_main = DEREF(_t4768);
    _t4773->decls_only = DEREF(_t4769);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4773->auto_import = *_ca; free(_ca); }
    _t4773->is_pure = DEREF(_t4770);
    _t4773->debug_prints = DEREF(_t4771);
    (void)_t4773;
    _t4774 = malloc(sizeof(Bool));
    *_t4774 = 0;
    (void)_t4774;
    _t4775 = malloc(sizeof(Bool));
    *_t4775 = 1;
    (void)_t4775;
    _t4776 = malloc(sizeof(Bool));
    *_t4776 = 0;
    (void)_t4776;
    _t4777 = malloc(sizeof(Bool));
    *_t4777 = 0;
    (void)_t4777;
    _t4778 = Str_lit("test", 4ULL);
    (void)_t4778;
    _t4779 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4779->name = *_ca; free(_ca); }
    _t4779->needs_main = DEREF(_t4774);
    _t4779->decls_only = DEREF(_t4775);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4779->auto_import = *_ca; free(_ca); }
    _t4779->is_pure = DEREF(_t4776);
    _t4779->debug_prints = DEREF(_t4777);
    (void)_t4779;
    _t4780 = malloc(sizeof(Bool));
    *_t4780 = 0;
    (void)_t4780;
    _t4781 = malloc(sizeof(Bool));
    *_t4781 = 1;
    (void)_t4781;
    _t4782 = malloc(sizeof(Bool));
    *_t4782 = 1;
    (void)_t4782;
    _t4783 = malloc(sizeof(Bool));
    *_t4783 = 0;
    (void)_t4783;
    _t4784 = Str_lit("pure", 4ULL);
    (void)_t4784;
    _t4785 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4785->name = *_ca; free(_ca); }
    _t4785->needs_main = DEREF(_t4780);
    _t4785->decls_only = DEREF(_t4781);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4785->auto_import = *_ca; free(_ca); }
    _t4785->is_pure = DEREF(_t4782);
    _t4785->debug_prints = DEREF(_t4783);
    (void)_t4785;
    _t4786 = malloc(sizeof(Bool));
    *_t4786 = 0;
    (void)_t4786;
    _t4787 = malloc(sizeof(Bool));
    *_t4787 = 1;
    (void)_t4787;
    _t4788 = malloc(sizeof(Bool));
    *_t4788 = 1;
    (void)_t4788;
    _t4789 = malloc(sizeof(Bool));
    *_t4789 = 1;
    (void)_t4789;
    _t4790 = Str_lit("pura", 4ULL);
    (void)_t4790;
    _t4791 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4791->name = *_ca; free(_ca); }
    _t4791->needs_main = DEREF(_t4786);
    _t4791->decls_only = DEREF(_t4787);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4791->auto_import = *_ca; free(_ca); }
    _t4791->is_pure = DEREF(_t4788);
    _t4791->debug_prints = DEREF(_t4789);
    (void)_t4791;
    _t4792 = malloc(sizeof(Bool));
    *_t4792 = 0;
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
    _t4796 = Str_lit("lib", 3ULL);
    (void)_t4796;
    _t4797 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4797->name = *_ca; free(_ca); }
    _t4797->needs_main = DEREF(_t4792);
    _t4797->decls_only = DEREF(_t4793);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4797->auto_import = *_ca; free(_ca); }
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
    *_t4801 = 1;
    (void)_t4801;
    _t4802 = Str_lit("liba", 4ULL);
    (void)_t4802;
    _t4803 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4803->name = *_ca; free(_ca); }
    _t4803->needs_main = DEREF(_t4798);
    _t4803->decls_only = DEREF(_t4799);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4803->auto_import = *_ca; free(_ca); }
    _t4803->is_pure = DEREF(_t4800);
    _t4803->debug_prints = DEREF(_t4801);
    (void)_t4803;
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
    U64 _t4666; { U64 *_hp = (U64 *)Array_len(args); _t4666 = *_hp; free(_hp); }
    (void)_t4666;
    U64 _t4667 = 0;
    (void)_t4667;
    Bool _t4668 = U64_eq(_t4666, _t4667);
    (void)_t4668;
    ;
    ;
    if (_t4668) {
        usage();
        Str *_t4287 = Str_lit("Str", 3ULL);
        (void)_t4287;
        U64 _t4288; { U64 *_hp = (U64 *)Str_size(); _t4288 = *_hp; free(_hp); }
        (void)_t4288;
        U64 _t4289 = 1;
        (void)_t4289;
        Array *_va85 = Array_new(_t4287, &(U64){_t4288}, &(U64){_t4289});
        (void)_va85;
        Str_delete(_t4287, &(Bool){1});
        ;
        ;
        U64 _t4290 = 0;
        (void)_t4290;
        Str *_t4291 = Str_lit("no arguments", 12ULL);
        (void)_t4291;
        Array_set(_va85, &(U64){_t4290}, _t4291);
        ;
        Str *_t4292 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4292;
        panic(_t4292, _va85);
        Str_delete(_t4292, &(Bool){1});
    }
    ;
    U64 *_t4669 = malloc(sizeof(U64));
    *_t4669 = 0;
    (void)_t4669;
    Str *cmd_ref = Array_get(args, _t4669);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4669, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4670; { U64 *_hp = (U64 *)Array_len(args); _t4670 = *_hp; free(_hp); }
    (void)_t4670;
    U64 _t4671 = 1;
    (void)_t4671;
    Bool _t4672 = U64_eq(_t4670, _t4671);
    (void)_t4672;
    ;
    ;
    if (_t4672) {
        Str *_t4293 = Str_lit("help", 4ULL);
        (void)_t4293;
        Str *_t4294 = Str_lit("--help", 6ULL);
        (void)_t4294;
        Bool _t4295; { Bool *_hp = (Bool *)Str_eq(command, _t4293); _t4295 = *_hp; free(_hp); }
        (void)_t4295;
        Str_delete(_t4293, &(Bool){1});
        Bool _t4296; { Bool *_hp = (Bool *)Str_eq(command, _t4294); _t4296 = *_hp; free(_hp); }
        (void)_t4296;
        Str_delete(_t4294, &(Bool){1});
        Bool _t4297 = Bool_or(_t4295, _t4296);
        (void)_t4297;
        ;
        ;
        if (_t4297) {
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
            U64 _t4314; { U64 *_hp = (U64 *)Array_len(args); _t4314 = *_hp; free(_hp); }
            (void)_t4314;
            Bool _wcond4298; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4314}); _wcond4298 = *_hp; free(_hp); }
            (void)_wcond4298;
            ;
            if (_wcond4298) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4315 = Str_lit("-o", 2ULL);
            (void)_t4315;
            U64 _t4316 = 1;
            (void)_t4316;
            U64 _t4317 = U64_add(DEREF(path_idx), _t4316);
            (void)_t4317;
            ;
            U64 _t4318; { U64 *_hp = (U64 *)Array_len(args); _t4318 = *_hp; free(_hp); }
            (void)_t4318;
            Bool _t4319; { Bool *_hp = (Bool *)Str_eq(flag, _t4315); _t4319 = *_hp; free(_hp); }
            (void)_t4319;
            Str_delete(_t4315, &(Bool){1});
            Bool _t4320; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4317}, &(U64){_t4318}); _t4320 = *_hp; free(_hp); }
            (void)_t4320;
            ;
            ;
            Bool _t4321 = Bool_and(_t4319, _t4320);
            (void)_t4321;
            ;
            ;
            if (_t4321) {
                U64 _t4299 = 1;
                (void)_t4299;
                U64 *_t4300 = malloc(sizeof(U64)); *_t4300 = U64_add(DEREF(path_idx), _t4299);
                (void)_t4300;
                ;
                Str *oval = Array_get(args, _t4300);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4300, &(Bool){1});
                U64 _t4301 = 2;
                (void)_t4301;
                U64 _t4302 = U64_add(DEREF(path_idx), _t4301);
                (void)_t4302;
                ;
                *path_idx = _t4302;
                ;
            } else {
                Str *_t4307 = Str_lit("-c", 2ULL);
                (void)_t4307;
                U64 _t4308 = 1;
                (void)_t4308;
                U64 _t4309 = U64_add(DEREF(path_idx), _t4308);
                (void)_t4309;
                ;
                U64 _t4310; { U64 *_hp = (U64 *)Array_len(args); _t4310 = *_hp; free(_hp); }
                (void)_t4310;
                Bool _t4311; { Bool *_hp = (Bool *)Str_eq(flag, _t4307); _t4311 = *_hp; free(_hp); }
                (void)_t4311;
                Str_delete(_t4307, &(Bool){1});
                Bool _t4312; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4309}, &(U64){_t4310}); _t4312 = *_hp; free(_hp); }
                (void)_t4312;
                ;
                ;
                Bool _t4313 = Bool_and(_t4311, _t4312);
                (void)_t4313;
                ;
                ;
                if (_t4313) {
                    U64 _t4303 = 1;
                    (void)_t4303;
                    U64 *_t4304 = malloc(sizeof(U64)); *_t4304 = U64_add(DEREF(path_idx), _t4303);
                    (void)_t4304;
                    ;
                    Str *cval = Array_get(args, _t4304);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4304, &(Bool){1});
                    U64 _t4305 = 2;
                    (void)_t4305;
                    U64 _t4306 = U64_add(DEREF(path_idx), _t4305);
                    (void)_t4306;
                    ;
                    *path_idx = _t4306;
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
    Str *_t4673 = Str_lit("help", 4ULL);
    (void)_t4673;
    Str *_t4674 = Str_lit("--help", 6ULL);
    (void)_t4674;
    Bool _t4675; { Bool *_hp = (Bool *)Str_eq(command, _t4673); _t4675 = *_hp; free(_hp); }
    (void)_t4675;
    Str_delete(_t4673, &(Bool){1});
    Bool _t4676; { Bool *_hp = (Bool *)Str_eq(command, _t4674); _t4676 = *_hp; free(_hp); }
    (void)_t4676;
    Str_delete(_t4674, &(Bool){1});
    Bool _t4677 = Bool_or(_t4675, _t4676);
    (void)_t4677;
    ;
    ;
    if (_t4677) {
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
    Str *_t4678 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4678;
    Str *core_path = Str_concat(bin_dir, _t4678);
    (void)core_path;
    Str_delete(_t4678, &(Bool){1});
    Str *_t4679 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4679;
    Str *ext_c_path = Str_concat(bin_dir, _t4679);
    (void)ext_c_path;
    Str_delete(_t4679, &(Bool){1});
    Str *_t4680 = Str_lit("Str", 3ULL);
    (void)_t4680;
    U64 _t4681; { U64 *_hp = (U64 *)Str_size(); _t4681 = *_hp; free(_hp); }
    (void)_t4681;
    Set *resolved = Set_new(_t4680, &(U64){_t4681});
    (void)resolved;
    Str_delete(_t4680, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4682; { U64 *_hp = (U64 *)Str_len(abs_path); _t4682 = *_hp; free(_hp); }
    (void)_t4682;
    U64 _t4683 = 0;
    (void)_t4683;
    Bool _t4684; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4682}, &(U64){_t4683}); _t4684 = *_hp; free(_hp); }
    (void)_t4684;
    ;
    ;
    if (_t4684) {
        U64 _t4330; { U64 *_hp = (U64 *)Str_len(abs_path); _t4330 = *_hp; free(_hp); }
        (void)_t4330;
        U64 _t4331 = 1;
        (void)_t4331;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4330, _t4331);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4323 = 0;
            (void)_t4323;
            U8 *_t4324 = Str_get(abs_path, last_slash);
            (void)_t4324;
            U8 _t4325 = 47;
            (void)_t4325;
            Bool _t4326; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4323}); _t4326 = *_hp; free(_hp); }
            (void)_t4326;
            ;
            Bool _t4327; { Bool *_hp = (Bool *)U8_neq(_t4324, &(U8){_t4325}); _t4327 = *_hp; free(_hp); }
            (void)_t4327;
            ;
            Bool _wcond4322 = Bool_and(_t4326, _t4327);
            (void)_wcond4322;
            ;
            ;
            if (_wcond4322) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4328 = 1;
            (void)_t4328;
            U64 _t4329 = U64_sub(DEREF(last_slash), _t4328);
            (void)_t4329;
            ;
            *last_slash = _t4329;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4332 = Str_clone(abs_path);
        (void)_t4332;
        Set_add(resolved, _t4332);
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
    U64 _t4685; { U64 *_hp = (U64 *)Str_len(core_abs); _t4685 = *_hp; free(_hp); }
    (void)_t4685;
    U64 _t4686 = 0;
    (void)_t4686;
    Bool _t4687; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4685}, &(U64){_t4686}); _t4687 = *_hp; free(_hp); }
    (void)_t4687;
    ;
    ;
    if (_t4687) {
        Bool _t4334; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4334 = *_hp; free(_hp); }
        (void)_t4334;
        if (_t4334) {
            Bool _t4333 = 1;
            (void)_t4333;
            skip_core = _t4333;
            ;
        }
        ;
        Str *_t4335 = Str_clone(core_abs);
        (void)_t4335;
        Set_add(resolved, _t4335);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4688; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4688 = *_hp; free(_hp); }
    (void)_t4688;
    U64 _t4689 = 0;
    (void)_t4689;
    Bool _t4690; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4688}, &(U64){_t4689}); _t4690 = *_hp; free(_hp); }
    (void)_t4690;
    ;
    ;
    Bool _t4691 = Bool_not(skip_core);
    (void)_t4691;
    Bool _t4692 = Bool_and(_t4690, _t4691);
    (void)_t4692;
    ;
    ;
    if (_t4692) {
        Str *_t4342 = Str_lit("/src/core", 9ULL);
        (void)_t4342;
        Str *core_dir = Str_concat(bin_dir, _t4342);
        (void)core_dir;
        Str_delete(_t4342, &(Bool){1});
        Str *_t4343 = Str_lit("", 0ULL);
        (void)_t4343;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4343); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4343, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4344 = 0;
        (void)_t4344;
        Bool _t4345; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4344}); _t4345 = *_hp; free(_hp); }
        (void)_t4345;
        ;
        ;
        if (_t4345) {
            Str *_t4336 = Str_lit("Str", 3ULL);
            (void)_t4336;
            U64 _t4337; { U64 *_hp = (U64 *)Str_size(); _t4337 = *_hp; free(_hp); }
            (void)_t4337;
            U64 _t4338 = 1;
            (void)_t4338;
            Array *_va86 = Array_new(_t4336, &(U64){_t4337}, &(U64){_t4338});
            (void)_va86;
            Str_delete(_t4336, &(Bool){1});
            ;
            ;
            U64 _t4339 = 0;
            (void)_t4339;
            Str *_t4340 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4340;
            Array_set(_va86, &(U64){_t4339}, _t4340);
            ;
            Str *_t4341 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4341;
            panic(_t4341, _va86);
            Str_delete(_t4341, &(Bool){1});
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
    Str *_t4693 = Str_lit("script", 6ULL);
    (void)_t4693;
    Mode *cur_mode = mode_resolve(_t4693);
    (void)cur_mode;
    Str_delete(_t4693, &(Bool){1});
    U64 _t4694; { U64 *_hp = (U64 *)Str_len(mode_str); _t4694 = *_hp; free(_hp); }
    (void)_t4694;
    U64 _t4695 = 0;
    (void)_t4695;
    Bool _t4696; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4694}, &(U64){_t4695}); _t4696 = *_hp; free(_hp); }
    (void)_t4696;
    ;
    ;
    if (_t4696) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4355; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4355 = *_hp; free(_hp); }
        (void)_t4355;
        U64 _t4356 = 0;
        (void)_t4356;
        Bool _t4357 = U64_eq(_t4355, _t4356);
        (void)_t4357;
        ;
        ;
        if (_t4357) {
            Str *_t4346 = Str_lit("Str", 3ULL);
            (void)_t4346;
            U64 _t4347; { U64 *_hp = (U64 *)Str_size(); _t4347 = *_hp; free(_hp); }
            (void)_t4347;
            U64 _t4348 = 1;
            (void)_t4348;
            Array *_va87 = Array_new(_t4346, &(U64){_t4347}, &(U64){_t4348});
            (void)_va87;
            Str_delete(_t4346, &(Bool){1});
            ;
            ;
            Str *_t4349 = Str_lit("unknown mode '", 14ULL);
            (void)_t4349;
            Str *_t4350 = Str_concat(_t4349, mode_str);
            (void)_t4350;
            Str_delete(_t4349, &(Bool){1});
            Str *_t4351 = Str_lit("'", 1ULL);
            (void)_t4351;
            U64 _t4352 = 0;
            (void)_t4352;
            Str *_t4353 = Str_concat(_t4350, _t4351);
            (void)_t4353;
            Str_delete(_t4350, &(Bool){1});
            Str_delete(_t4351, &(Bool){1});
            Array_set(_va87, &(U64){_t4352}, _t4353);
            ;
            Str *_t4354 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4354;
            panic(_t4354, _va87);
            Str_delete(_t4354, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4697; { U64 *_hp = (U64 *)Vec_len(imports); _t4697 = *_hp; free(_hp); }
    (void)_t4697;
    U64 _t4698 = 0;
    (void)_t4698;
    Bool _t4699; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4697}, &(U64){_t4698}); _t4699 = *_hp; free(_hp); }
    (void)_t4699;
    ;
    ;
    if (_t4699) {
        Str *_t4364 = Str_lit("/src/lib", 8ULL);
        (void)_t4364;
        Str *lib_dir = Str_concat(bin_dir, _t4364);
        (void)lib_dir;
        Str_delete(_t4364, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4365 = 0;
        (void)_t4365;
        Bool _t4366; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4365}); _t4366 = *_hp; free(_hp); }
        (void)_t4366;
        ;
        ;
        if (_t4366) {
            Str *_t4358 = Str_lit("Str", 3ULL);
            (void)_t4358;
            U64 _t4359; { U64 *_hp = (U64 *)Str_size(); _t4359 = *_hp; free(_hp); }
            (void)_t4359;
            U64 _t4360 = 1;
            (void)_t4360;
            Array *_va88 = Array_new(_t4358, &(U64){_t4359}, &(U64){_t4360});
            (void)_va88;
            Str_delete(_t4358, &(Bool){1});
            ;
            ;
            U64 _t4361 = 0;
            (void)_t4361;
            Str *_t4362 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4362;
            Array_set(_va88, &(U64){_t4361}, _t4362);
            ;
            Str *_t4363 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4363;
            panic(_t4363, _va88);
            Str_delete(_t4363, &(Bool){1});
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
    Bool _t4700 = Bool_not(skip_core);
    (void)_t4700;
    ;
    if (_t4700) {
        while (1) {
            U32 _t4368 = expr_nchildren(core_ast);
            (void)_t4368;
            Bool _wcond4367; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4368}); _wcond4367 = *_hp; free(_hp); }
            (void)_wcond4367;
            ;
            if (_wcond4367) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4369 = 1;
            (void)_t4369;
            U32 _t4370 = U32_add(DEREF(i), _t4369);
            (void)_t4370;
            ;
            *i = _t4370;
            ;
        }
        U32 _t4375 = 0;
        (void)_t4375;
        *i = _t4375;
        ;
        while (1) {
            U32 _t4372 = expr_vec_count(core_import_decls);
            (void)_t4372;
            Bool _wcond4371; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4372}); _wcond4371 = *_hp; free(_hp); }
            (void)_wcond4371;
            ;
            if (_wcond4371) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4373 = 1;
            (void)_t4373;
            U32 _t4374 = U32_add(DEREF(i), _t4373);
            (void)_t4374;
            ;
            *i = _t4374;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4701; { U64 *_hp = (U64 *)Str_len(auto_import); _t4701 = *_hp; free(_hp); }
    (void)_t4701;
    U64 _t4702 = 0;
    (void)_t4702;
    Bool _t4703; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4701}, &(U64){_t4702}); _t4703 = *_hp; free(_hp); }
    (void)_t4703;
    ;
    ;
    if (_t4703) {
        Str *_t4380 = Str_lit("/src/modes/", 11ULL);
        (void)_t4380;
        Str *_t4381 = Str_concat(bin_dir, _t4380);
        (void)_t4381;
        Str_delete(_t4380, &(Bool){1});
        Str *_t4382 = Str_concat(_t4381, auto_import);
        (void)_t4382;
        Str_delete(_t4381, &(Bool){1});
        Str *_t4383 = Str_lit(".til", 4ULL);
        (void)_t4383;
        Str *mode_til_path = Str_concat(_t4382, _t4383);
        (void)mode_til_path;
        Str_delete(_t4382, &(Bool){1});
        Str_delete(_t4383, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4384 = 0;
        (void)_t4384;
        *i = _t4384;
        ;
        while (1) {
            U32 _t4377 = expr_nchildren(mode_ast);
            (void)_t4377;
            Bool _wcond4376; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4377}); _wcond4376 = *_hp; free(_hp); }
            (void)_wcond4376;
            ;
            if (_wcond4376) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4378 = 1;
            (void)_t4378;
            U32 _t4379 = U32_add(DEREF(i), _t4378);
            (void)_t4379;
            ;
            *i = _t4379;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4704 = 0;
    (void)_t4704;
    *i = _t4704;
    ;
    while (1) {
        U32 _t4386 = expr_vec_count(import_decls);
        (void)_t4386;
        Bool _wcond4385; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4386}); _wcond4385 = *_hp; free(_hp); }
        (void)_wcond4385;
        ;
        if (_wcond4385) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4387 = 1;
        (void)_t4387;
        U32 _t4388 = U32_add(DEREF(i), _t4387);
        (void)_t4388;
        ;
        *i = _t4388;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4705 = 0;
    (void)_t4705;
    *i = _t4705;
    ;
    while (1) {
        U32 _t4390 = expr_nchildren(ast);
        (void)_t4390;
        Bool _wcond4389; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4390}); _wcond4389 = *_hp; free(_hp); }
        (void)_wcond4389;
        ;
        if (_wcond4389) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4391 = 1;
        (void)_t4391;
        U32 _t4392 = U32_add(DEREF(i), _t4391);
        (void)_t4392;
        ;
        *i = _t4392;
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
    U32 _t4706 = 0;
    (void)_t4706;
    *i = _t4706;
    ;
    while (1) {
        U32 _t4408 = expr_nchildren(ast);
        (void)_t4408;
        Bool _wcond4393; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4408}); _wcond4393 = *_hp; free(_hp); }
        (void)_wcond4393;
        ;
        if (_wcond4393) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4409 = expr_get_tag(stmt);
        (void)_t4409;
        U32 _t4410 = expr_nchildren(stmt);
        (void)_t4410;
        U32 _t4411 = 2;
        (void)_t4411;
        Bool _t4412 = I32_eq(_t4409, DEREF(NODE_FCALL));
        (void)_t4412;
        ;
        Bool _t4413 = U32_eq(_t4410, _t4411);
        (void)_t4413;
        ;
        ;
        U32 *_t4414 = malloc(sizeof(U32));
        *_t4414 = 0;
        (void)_t4414;
        Expr *_t4415 = expr_get_child(stmt, DEREF(_t4414));
        (void)_t4415;
        I32 _t4416 = expr_get_tag(_t4415);
        (void)_t4416;
        U32_delete(_t4414, &(Bool){1});
        Bool _t4417 = Bool_and(_t4412, _t4413);
        (void)_t4417;
        ;
        ;
        Bool _t4418 = I32_eq(_t4416, DEREF(NODE_IDENT));
        (void)_t4418;
        ;
        U32 *_t4419 = malloc(sizeof(U32));
        *_t4419 = 1;
        (void)_t4419;
        Expr *_t4420 = expr_get_child(stmt, DEREF(_t4419));
        (void)_t4420;
        I32 _t4421 = expr_get_tag(_t4420);
        (void)_t4421;
        U32_delete(_t4419, &(Bool){1});
        Bool _t4422 = Bool_and(_t4417, _t4418);
        (void)_t4422;
        ;
        ;
        Bool _t4423 = I32_eq(_t4421, DEREF(NODE_LITERAL_STR));
        (void)_t4423;
        ;
        Bool _t4424 = Bool_and(_t4422, _t4423);
        (void)_t4424;
        ;
        ;
        if (_t4424) {
            U32 *_t4402 = malloc(sizeof(U32));
            *_t4402 = 0;
            (void)_t4402;
            Expr *_t4403 = expr_get_child(stmt, DEREF(_t4402));
            (void)_t4403;
            Str *fname = expr_get_str_val(_t4403);
            (void)fname;
            U32 *_t4404 = malloc(sizeof(U32));
            *_t4404 = 1;
            (void)_t4404;
            Expr *_t4405 = expr_get_child(stmt, DEREF(_t4404));
            (void)_t4405;
            Str *arg = expr_get_str_val(_t4405);
            (void)arg;
            Str *_t4406 = Str_lit("link", 4ULL);
            (void)_t4406;
            Bool _t4407; { Bool *_hp = (Bool *)Str_eq(fname, _t4406); _t4407 = *_hp; free(_hp); }
            (void)_t4407;
            Str_delete(_t4406, &(Bool){1});
            if (_t4407) {
                Str *_t4394 = Str_lit(" -l", 3ULL);
                (void)_t4394;
                Str *_t4395 = Str_concat(link_flags, _t4394);
                (void)_t4395;
                Str_delete(_t4394, &(Bool){1});
                link_flags = Str_concat(_t4395, arg);
                Str_delete(_t4395, &(Bool){1});
            } else {
                Str *_t4400 = Str_lit("link_c", 6ULL);
                (void)_t4400;
                Bool _t4401; { Bool *_hp = (Bool *)Str_eq(fname, _t4400); _t4401 = *_hp; free(_hp); }
                (void)_t4401;
                Str_delete(_t4400, &(Bool){1});
                if (_t4401) {
                    U64 _t4397; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4397 = *_hp; free(_hp); }
                    (void)_t4397;
                    U64 _t4398 = 0;
                    (void)_t4398;
                    Bool _t4399; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4397}, &(U64){_t4398}); _t4399 = *_hp; free(_hp); }
                    (void)_t4399;
                    ;
                    ;
                    if (_t4399) {
                        Str *_t4396 = Str_lit(" ", 1ULL);
                        (void)_t4396;
                        link_c_paths = Str_concat(link_c_paths, _t4396);
                        Str_delete(_t4396, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4402, &(Bool){1});
            U32_delete(_t4404, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4425 = 1;
        (void)_t4425;
        U32 _t4426 = U32_add(DEREF(i), _t4425);
        (void)_t4426;
        ;
        *i = _t4426;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4707 = init_declarations(ast, scope);
    (void)_t4707;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4708 = 0;
    (void)_t4708;
    Bool _t4709; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4708}); _t4709 = *_hp; free(_hp); }
    (void)_t4709;
    ;
    if (_t4709) {
        Str *_t4427 = Str_lit("Str", 3ULL);
        (void)_t4427;
        U64 _t4428; { U64 *_hp = (U64 *)Str_size(); _t4428 = *_hp; free(_hp); }
        (void)_t4428;
        U64 _t4429 = 1;
        (void)_t4429;
        Array *_va89 = Array_new(_t4427, &(U64){_t4428}, &(U64){_t4429});
        (void)_va89;
        Str_delete(_t4427, &(Bool){1});
        ;
        ;
        Str *_t4430 = I32_to_str(&(I32){type_errors});
        (void)_t4430;
        Str *_t4431 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4431;
        U64 _t4432 = 0;
        (void)_t4432;
        Str *_t4433 = Str_concat(_t4430, _t4431);
        (void)_t4433;
        Str_delete(_t4430, &(Bool){1});
        Str_delete(_t4431, &(Bool){1});
        Array_set(_va89, &(U64){_t4432}, _t4433);
        ;
        Str *_t4434 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4434;
        panic(_t4434, _va89);
        Str_delete(_t4434, &(Bool){1});
    }
    ;
    ;
    Str *_t4710 = Str_lit("test", 4ULL);
    (void)_t4710;
    Str *_t4711 = Str_lit("test", 4ULL);
    (void)_t4711;
    Bool _t4712; { Bool *_hp = (Bool *)Str_eq(command, _t4710); _t4712 = *_hp; free(_hp); }
    (void)_t4712;
    Str_delete(_t4710, &(Bool){1});
    Bool _t4713; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4711); _t4713 = *_hp; free(_hp); }
    (void)_t4713;
    Str_delete(_t4711, &(Bool){1});
    Str *_t4714 = Str_lit("pure", 4ULL);
    (void)_t4714;
    Bool _t4715 = Bool_or(_t4712, _t4713);
    (void)_t4715;
    ;
    ;
    Bool _t4716; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4714); _t4716 = *_hp; free(_hp); }
    (void)_t4716;
    Str_delete(_t4714, &(Bool){1});
    Str *_t4717 = Str_lit("pura", 4ULL);
    (void)_t4717;
    Bool _t4718 = Bool_or(_t4715, _t4716);
    (void)_t4718;
    ;
    ;
    Bool _t4719; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4717); _t4719 = *_hp; free(_hp); }
    (void)_t4719;
    Str_delete(_t4717, &(Bool){1});
    Bool run_tests = Bool_or(_t4718, _t4719);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4720 = Str_lit("translate", 9ULL);
    (void)_t4720;
    Str *_t4721 = Str_lit("build", 5ULL);
    (void)_t4721;
    Bool _t4722; { Bool *_hp = (Bool *)Str_eq(command, _t4720); _t4722 = *_hp; free(_hp); }
    (void)_t4722;
    Str_delete(_t4720, &(Bool){1});
    Bool _t4723; { Bool *_hp = (Bool *)Str_eq(command, _t4721); _t4723 = *_hp; free(_hp); }
    (void)_t4723;
    Str_delete(_t4721, &(Bool){1});
    Bool _t4724; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4724 = *_hp; free(_hp); }
    (void)_t4724;
    Bool _t4725 = Bool_or(_t4722, _t4723);
    (void)_t4725;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4724, _t4725);
    (void)is_lib_target;
    ;
    ;
    U64 _t4726; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4726 = *_hp; free(_hp); }
    (void)_t4726;
    U64 _t4727 = 0;
    (void)_t4727;
    Bool _t4728 = Bool_not(is_lib_target);
    (void)_t4728;
    ;
    Bool _t4729 = U64_eq(_t4726, _t4727);
    (void)_t4729;
    ;
    ;
    Bool _t4730 = Bool_and(_t4728, _t4729);
    (void)_t4730;
    ;
    ;
    if (_t4730) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4731; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4731 = *_hp; free(_hp); }
    (void)_t4731;
    U64 _t4732 = 0;
    (void)_t4732;
    Bool _t4733; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4731}, &(U64){_t4732}); _t4733 = *_hp; free(_hp); }
    (void)_t4733;
    ;
    ;
    if (_t4733) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4734 = Str_lit("Str", 3ULL);
    (void)_t4734;
    U64 _t4735; { U64 *_hp = (U64 *)Str_size(); _t4735 = *_hp; free(_hp); }
    (void)_t4735;
    Vec *user_argv = Vec_new(_t4734, &(U64){_t4735});
    (void)user_argv;
    Str_delete(_t4734, &(Bool){1});
    ;
    U64 _t4736 = 1;
    (void)_t4736;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4736);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4451; { U64 *_hp = (U64 *)Array_len(args); _t4451 = *_hp; free(_hp); }
        (void)_t4451;
        Bool _wcond4435; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4451}); _wcond4435 = *_hp; free(_hp); }
        (void)_wcond4435;
        ;
        if (_wcond4435) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4452 = Str_lit("-l", 2ULL);
        (void)_t4452;
        Bool _t4453; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4452); _t4453 = *_hp; free(_hp); }
        (void)_t4453;
        Str_delete(_t4452, &(Bool){1});
        if (_t4453) {
            U64 _t4438 = 2;
            (void)_t4438;
            U64 _t4439; { U64 *_hp = (U64 *)Str_len(arg); _t4439 = *_hp; free(_hp); }
            (void)_t4439;
            Str *lib = Str_substr(arg, &(U64){_t4438}, &(U64){_t4439});
            (void)lib;
            ;
            ;
            U64 _t4440; { U64 *_hp = (U64 *)Str_len(lib); _t4440 = *_hp; free(_hp); }
            (void)_t4440;
            U64 _t4441 = 0;
            (void)_t4441;
            U64 _t4442 = 1;
            (void)_t4442;
            U64 _t4443 = U64_add(DEREF(ai), _t4442);
            (void)_t4443;
            ;
            U64 _t4444; { U64 *_hp = (U64 *)Array_len(args); _t4444 = *_hp; free(_hp); }
            (void)_t4444;
            Bool _t4445 = U64_eq(_t4440, _t4441);
            (void)_t4445;
            ;
            ;
            Bool _t4446; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4443}, &(U64){_t4444}); _t4446 = *_hp; free(_hp); }
            (void)_t4446;
            ;
            ;
            Bool _t4447 = Bool_and(_t4445, _t4446);
            (void)_t4447;
            ;
            ;
            if (_t4447) {
                U64 _t4436 = 1;
                (void)_t4436;
                U64 _t4437 = U64_add(DEREF(ai), _t4436);
                (void)_t4437;
                ;
                *ai = _t4437;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4448 = Str_lit(" -l", 3ULL);
            (void)_t4448;
            Str *_t4449 = Str_concat(link_flags, _t4448);
            (void)_t4449;
            Str_delete(_t4448, &(Bool){1});
            link_flags = Str_concat(_t4449, lib);
            Str_delete(_t4449, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4450 = Str_clone(arg);
            (void)_t4450;
            Vec_push(user_argv, _t4450);
        }
        ;
        U64 _t4454 = 1;
        (void)_t4454;
        U64 _t4455 = U64_add(DEREF(ai), _t4454);
        (void)_t4455;
        ;
        *ai = _t4455;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4737; { U64 *_hp = (U64 *)Str_len(link_flags); _t4737 = *_hp; free(_hp); }
    (void)_t4737;
    U64 _t4738 = 0;
    (void)_t4738;
    Bool _t4739; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4737}, &(U64){_t4738}); _t4739 = *_hp; free(_hp); }
    (void)_t4739;
    ;
    ;
    if (_t4739) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4740 = Str_lit("interpret", 9ULL);
    (void)_t4740;
    Str *_t4741 = Str_lit("test", 4ULL);
    (void)_t4741;
    Bool _t4742; { Bool *_hp = (Bool *)Str_eq(command, _t4740); _t4742 = *_hp; free(_hp); }
    (void)_t4742;
    Str_delete(_t4740, &(Bool){1});
    Bool _t4743; { Bool *_hp = (Bool *)Str_eq(command, _t4741); _t4743 = *_hp; free(_hp); }
    (void)_t4743;
    Str_delete(_t4741, &(Bool){1});
    Bool _t4744 = Bool_or(_t4742, _t4743);
    (void)_t4744;
    ;
    ;
    if (_t4744) {
        Str *_t4462 = Str_lit("interpret", 9ULL);
        (void)_t4462;
        Bool _t4463; { Bool *_hp = (Bool *)Str_eq(command, _t4462); _t4463 = *_hp; free(_hp); }
        (void)_t4463;
        Str_delete(_t4462, &(Bool){1});
        Bool _t4464 = Bool_and(is_lib_mode, _t4463);
        (void)_t4464;
        ;
        if (_t4464) {
            Str *_t4456 = Str_lit("Str", 3ULL);
            (void)_t4456;
            U64 _t4457; { U64 *_hp = (U64 *)Str_size(); _t4457 = *_hp; free(_hp); }
            (void)_t4457;
            U64 _t4458 = 1;
            (void)_t4458;
            Array *_va90 = Array_new(_t4456, &(U64){_t4457}, &(U64){_t4458});
            (void)_va90;
            Str_delete(_t4456, &(Bool){1});
            ;
            ;
            U64 _t4459 = 0;
            (void)_t4459;
            Str *_t4460 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4460;
            Array_set(_va90, &(U64){_t4459}, _t4460);
            ;
            Str *_t4461 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4461;
            panic(_t4461, _va90);
            Str_delete(_t4461, &(Bool){1});
        }
        ;
        I32 _t4465 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4465;
        result = _t4465;
        ;
    } else {
        Str *_t4658 = Str_lit("translate", 9ULL);
        (void)_t4658;
        Str *_t4659 = Str_lit("build", 5ULL);
        (void)_t4659;
        Bool _t4660; { Bool *_hp = (Bool *)Str_eq(command, _t4658); _t4660 = *_hp; free(_hp); }
        (void)_t4660;
        Str_delete(_t4658, &(Bool){1});
        Bool _t4661; { Bool *_hp = (Bool *)Str_eq(command, _t4659); _t4661 = *_hp; free(_hp); }
        (void)_t4661;
        Str_delete(_t4659, &(Bool){1});
        Str *_t4662 = Str_lit("run", 3ULL);
        (void)_t4662;
        Bool _t4663 = Bool_or(_t4660, _t4661);
        (void)_t4663;
        ;
        ;
        Bool _t4664; { Bool *_hp = (Bool *)Str_eq(command, _t4662); _t4664 = *_hp; free(_hp); }
        (void)_t4664;
        Str_delete(_t4662, &(Bool){1});
        Bool _t4665 = Bool_or(_t4663, _t4664);
        (void)_t4665;
        ;
        ;
        if (_t4665) {
            Str *_t4591 = Str_lit("run", 3ULL);
            (void)_t4591;
            Bool _t4592; { Bool *_hp = (Bool *)Str_eq(command, _t4591); _t4592 = *_hp; free(_hp); }
            (void)_t4592;
            Str_delete(_t4591, &(Bool){1});
            Bool _t4593 = Bool_and(is_lib_mode, _t4592);
            (void)_t4593;
            ;
            if (_t4593) {
                Str *_t4466 = Str_lit("Str", 3ULL);
                (void)_t4466;
                U64 _t4467; { U64 *_hp = (U64 *)Str_size(); _t4467 = *_hp; free(_hp); }
                (void)_t4467;
                U64 _t4468 = 1;
                (void)_t4468;
                Array *_va91 = Array_new(_t4466, &(U64){_t4467}, &(U64){_t4468});
                (void)_va91;
                Str_delete(_t4466, &(Bool){1});
                ;
                ;
                U64 _t4469 = 0;
                (void)_t4469;
                Str *_t4470 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4470;
                Array_set(_va91, &(U64){_t4469}, _t4470);
                ;
                Str *_t4471 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4471;
                panic(_t4471, _va91);
                Str_delete(_t4471, &(Bool){1});
            }
            ;
            Str *_t4594 = Str_lit("/", 1ULL);
            (void)_t4594;
            I64 *last_slash = Str_rfind(path, _t4594);
            (void)last_slash;
            Str_delete(_t4594, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4595 = 0;
            (void)_t4595;
            Bool _t4596; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4595}); _t4596 = *_hp; free(_hp); }
            (void)_t4596;
            ;
            if (_t4596) {
                I64 _t4472 = 1;
                (void)_t4472;
                I64 _t4473 = I64_add(DEREF(last_slash), _t4472);
                (void)_t4473;
                ;
                U64 _t4474; { U64 *_hp = (U64 *)Str_len(path); _t4474 = *_hp; free(_hp); }
                (void)_t4474;
                U64 _t4475 = I64_to_u64(DEREF(last_slash));
                (void)_t4475;
                U64 _t4476 = U64_sub(_t4474, _t4475);
                (void)_t4476;
                ;
                ;
                U64 _t4477 = 1;
                (void)_t4477;
                U64 _t4478 = I64_to_u64(_t4473);
                (void)_t4478;
                ;
                U64 _t4479 = U64_sub(_t4476, _t4477);
                (void)_t4479;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4478}, &(U64){_t4479});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4597 = Str_lit(".til", 4ULL);
            (void)_t4597;
            Bool _t4598; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4597); _t4598 = *_hp; free(_hp); }
            (void)_t4598;
            Str_delete(_t4597, &(Bool){1});
            if (_t4598) {
                U64 _t4480 = 4;
                (void)_t4480;
                U64 _t4481 = U64_sub(name_len, _t4480);
                (void)_t4481;
                ;
                name_len = _t4481;
                ;
            }
            ;
            U64 _t4599 = 0;
            (void)_t4599;
            Str *name = Str_substr(basename, &(U64){_t4599}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4600 = Str_lit("gen/til/", 8ULL);
            (void)_t4600;
            Str *_t4601 = Str_concat(_t4600, name);
            (void)_t4601;
            Str_delete(_t4600, &(Bool){1});
            Str *_t4602 = Str_lit(".c", 2ULL);
            (void)_t4602;
            Str *c_path = Str_concat(_t4601, _t4602);
            (void)c_path;
            Str_delete(_t4601, &(Bool){1});
            Str_delete(_t4602, &(Bool){1});
            U64 _t4603; { U64 *_hp = (U64 *)Str_len(custom_c); _t4603 = *_hp; free(_hp); }
            (void)_t4603;
            U64 _t4604 = 0;
            (void)_t4604;
            Bool _t4605; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4603}, &(U64){_t4604}); _t4605 = *_hp; free(_hp); }
            (void)_t4605;
            ;
            ;
            if (_t4605) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4606 = Str_lit("bin/til/", 8ULL);
            (void)_t4606;
            Str *bin_path = Str_concat(_t4606, name);
            (void)bin_path;
            Str_delete(_t4606, &(Bool){1});
            U64 _t4607; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4607 = *_hp; free(_hp); }
            (void)_t4607;
            U64 _t4608 = 0;
            (void)_t4608;
            Bool _t4609; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4607}, &(U64){_t4608}); _t4609 = *_hp; free(_hp); }
            (void)_t4609;
            ;
            ;
            if (_t4609) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4610 = Str_lit("run", 3ULL);
            (void)_t4610;
            Bool _t4611; { Bool *_hp = (Bool *)Str_eq(command, _t4610); _t4611 = *_hp; free(_hp); }
            (void)_t4611;
            Str_delete(_t4610, &(Bool){1});
            Bool _t4612; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4612 = *_hp; free(_hp); }
            (void)_t4612;
            Bool _t4613 = Bool_not(_t4611);
            (void)_t4613;
            ;
            Bool do_lib = Bool_and(_t4612, _t4613);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4482 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4482;
                I32 _t4483 = til_system(_t4482);
                (void)_t4483;
                Str_delete(_t4482, &(Bool){1});
                ;
            } else {
                Str *_t4488 = Str_lit("/", 1ULL);
                (void)_t4488;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4488); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4488, &(Bool){1});
                Str *_t4489 = Str_lit("/", 1ULL);
                (void)_t4489;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4489); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4489, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4490 = 0;
                (void)_t4490;
                Bool _t4491; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4490}); _t4491 = *_hp; free(_hp); }
                (void)_t4491;
                ;
                if (_t4491) {
                    U64 _t4484 = 0;
                    (void)_t4484;
                    U64 _t4485 = I64_to_u64(cp_slash);
                    (void)_t4485;
                    cp_dir = Str_substr(c_path, &(U64){_t4484}, &(U64){_t4485});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4492 = 0;
                (void)_t4492;
                Bool _t4493; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4492}); _t4493 = *_hp; free(_hp); }
                (void)_t4493;
                ;
                if (_t4493) {
                    U64 _t4486 = 0;
                    (void)_t4486;
                    U64 _t4487 = I64_to_u64(bp_slash);
                    (void)_t4487;
                    bp_dir = Str_substr(bin_path, &(U64){_t4486}, &(U64){_t4487});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4494 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4494;
                Str *_t4495 = Str_concat(_t4494, cp_dir);
                (void)_t4495;
                Str_delete(_t4494, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4496 = Str_lit(" ", 1ULL);
                (void)_t4496;
                Str *_t4497 = Str_concat(_t4495, _t4496);
                (void)_t4497;
                Str_delete(_t4495, &(Bool){1});
                Str_delete(_t4496, &(Bool){1});
                Str *_t4498 = Str_concat(_t4497, bp_dir);
                (void)_t4498;
                Str_delete(_t4497, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4499 = til_system(_t4498);
                (void)_t4499;
                Str_delete(_t4498, &(Bool){1});
                ;
            }
            I32 _t4614 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4614;
            result = _t4614;
            ;
            I32 _t4615 = 0;
            (void)_t4615;
            Bool _t4616 = I32_eq(result, _t4615);
            (void)_t4616;
            ;
            Bool _t4617 = Bool_and(_t4616, do_lib);
            (void)_t4617;
            ;
            if (_t4617) {
                Str *_t4556 = Str_lit("gen/til/", 8ULL);
                (void)_t4556;
                Str *_t4557 = Str_concat(_t4556, name);
                (void)_t4557;
                Str_delete(_t4556, &(Bool){1});
                Str *_t4558 = Str_lit(".h", 2ULL);
                (void)_t4558;
                Str *h_path = Str_concat(_t4557, _t4558);
                (void)h_path;
                Str_delete(_t4557, &(Bool){1});
                Str_delete(_t4558, &(Bool){1});
                Str *_t4559 = Str_lit("gen/til/", 8ULL);
                (void)_t4559;
                Str *_t4560 = Str_concat(_t4559, name);
                (void)_t4560;
                Str_delete(_t4559, &(Bool){1});
                Str *_t4561 = Str_lit(".til", 4ULL);
                (void)_t4561;
                Str *til_path = Str_concat(_t4560, _t4561);
                (void)til_path;
                Str_delete(_t4560, &(Bool){1});
                Str_delete(_t4561, &(Bool){1});
                I32 _t4562 = build_header(ast, h_path);
                (void)_t4562;
                result = _t4562;
                ;
                I32 _t4563 = 0;
                (void)_t4563;
                Bool _t4564 = I32_eq(result, _t4563);
                (void)_t4564;
                ;
                if (_t4564) {
                    I32 _t4500 = build_til_binding(ast, til_path, name);
                    (void)_t4500;
                    result = _t4500;
                    ;
                }
                ;
                I32 _t4565 = 0;
                (void)_t4565;
                Str *_t4566 = Str_lit("translate", 9ULL);
                (void)_t4566;
                Bool _t4567 = I32_eq(result, _t4565);
                (void)_t4567;
                ;
                Bool _t4568; { Bool *_hp = (Bool *)Str_eq(command, _t4566); _t4568 = *_hp; free(_hp); }
                (void)_t4568;
                Str_delete(_t4566, &(Bool){1});
                Bool _t4569 = Bool_and(_t4567, _t4568);
                (void)_t4569;
                ;
                ;
                if (_t4569) {
                    Str *_t4501 = Str_lit("Str", 3ULL);
                    (void)_t4501;
                    U64 _t4502; { U64 *_hp = (U64 *)Str_size(); _t4502 = *_hp; free(_hp); }
                    (void)_t4502;
                    U64 _t4503 = 1;
                    (void)_t4503;
                    Array *_va92 = Array_new(_t4501, &(U64){_t4502}, &(U64){_t4503});
                    (void)_va92;
                    Str_delete(_t4501, &(Bool){1});
                    ;
                    ;
                    Str *_t4504 = Str_lit("Generated: ", 11ULL);
                    (void)_t4504;
                    U64 _t4505 = 0;
                    (void)_t4505;
                    Str *_t4506 = Str_concat(_t4504, c_path);
                    (void)_t4506;
                    Str_delete(_t4504, &(Bool){1});
                    Array_set(_va92, &(U64){_t4505}, _t4506);
                    ;
                    println(_va92);
                    Str *_t4507 = Str_lit("Str", 3ULL);
                    (void)_t4507;
                    U64 _t4508; { U64 *_hp = (U64 *)Str_size(); _t4508 = *_hp; free(_hp); }
                    (void)_t4508;
                    U64 _t4509 = 1;
                    (void)_t4509;
                    Array *_va93 = Array_new(_t4507, &(U64){_t4508}, &(U64){_t4509});
                    (void)_va93;
                    Str_delete(_t4507, &(Bool){1});
                    ;
                    ;
                    Str *_t4510 = Str_lit("Generated: ", 11ULL);
                    (void)_t4510;
                    U64 _t4511 = 0;
                    (void)_t4511;
                    Str *_t4512 = Str_concat(_t4510, h_path);
                    (void)_t4512;
                    Str_delete(_t4510, &(Bool){1});
                    Array_set(_va93, &(U64){_t4511}, _t4512);
                    ;
                    println(_va93);
                    Str *_t4513 = Str_lit("Str", 3ULL);
                    (void)_t4513;
                    U64 _t4514; { U64 *_hp = (U64 *)Str_size(); _t4514 = *_hp; free(_hp); }
                    (void)_t4514;
                    U64 _t4515 = 1;
                    (void)_t4515;
                    Array *_va94 = Array_new(_t4513, &(U64){_t4514}, &(U64){_t4515});
                    (void)_va94;
                    Str_delete(_t4513, &(Bool){1});
                    ;
                    ;
                    Str *_t4516 = Str_lit("Generated: ", 11ULL);
                    (void)_t4516;
                    U64 _t4517 = 0;
                    (void)_t4517;
                    Str *_t4518 = Str_concat(_t4516, til_path);
                    (void)_t4518;
                    Str_delete(_t4516, &(Bool){1});
                    Array_set(_va94, &(U64){_t4517}, _t4518);
                    ;
                    println(_va94);
                }
                ;
                I32 _t4570 = 0;
                (void)_t4570;
                Str *_t4571 = Str_lit("build", 5ULL);
                (void)_t4571;
                Bool _t4572 = I32_eq(result, _t4570);
                (void)_t4572;
                ;
                Bool _t4573; { Bool *_hp = (Bool *)Str_eq(command, _t4571); _t4573 = *_hp; free(_hp); }
                (void)_t4573;
                Str_delete(_t4571, &(Bool){1});
                Bool _t4574 = Bool_and(_t4572, _t4573);
                (void)_t4574;
                ;
                ;
                if (_t4574) {
                    I32 _t4553 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4553;
                    result = _t4553;
                    ;
                    I32 _t4554 = 0;
                    (void)_t4554;
                    Bool _t4555 = I32_eq(result, _t4554);
                    (void)_t4555;
                    ;
                    if (_t4555) {
                        Str *_t4519 = Str_lit("Str", 3ULL);
                        (void)_t4519;
                        U64 _t4520; { U64 *_hp = (U64 *)Str_size(); _t4520 = *_hp; free(_hp); }
                        (void)_t4520;
                        U64 _t4521 = 1;
                        (void)_t4521;
                        Array *_va95 = Array_new(_t4519, &(U64){_t4520}, &(U64){_t4521});
                        (void)_va95;
                        Str_delete(_t4519, &(Bool){1});
                        ;
                        ;
                        Str *_t4522 = Str_lit("Generated: ", 11ULL);
                        (void)_t4522;
                        U64 _t4523 = 0;
                        (void)_t4523;
                        Str *_t4524 = Str_concat(_t4522, c_path);
                        (void)_t4524;
                        Str_delete(_t4522, &(Bool){1});
                        Array_set(_va95, &(U64){_t4523}, _t4524);
                        ;
                        println(_va95);
                        Str *_t4525 = Str_lit("Str", 3ULL);
                        (void)_t4525;
                        U64 _t4526; { U64 *_hp = (U64 *)Str_size(); _t4526 = *_hp; free(_hp); }
                        (void)_t4526;
                        U64 _t4527 = 1;
                        (void)_t4527;
                        Array *_va96 = Array_new(_t4525, &(U64){_t4526}, &(U64){_t4527});
                        (void)_va96;
                        Str_delete(_t4525, &(Bool){1});
                        ;
                        ;
                        Str *_t4528 = Str_lit("Generated: ", 11ULL);
                        (void)_t4528;
                        U64 _t4529 = 0;
                        (void)_t4529;
                        Str *_t4530 = Str_concat(_t4528, h_path);
                        (void)_t4530;
                        Str_delete(_t4528, &(Bool){1});
                        Array_set(_va96, &(U64){_t4529}, _t4530);
                        ;
                        println(_va96);
                        Str *_t4531 = Str_lit("Str", 3ULL);
                        (void)_t4531;
                        U64 _t4532; { U64 *_hp = (U64 *)Str_size(); _t4532 = *_hp; free(_hp); }
                        (void)_t4532;
                        U64 _t4533 = 1;
                        (void)_t4533;
                        Array *_va97 = Array_new(_t4531, &(U64){_t4532}, &(U64){_t4533});
                        (void)_va97;
                        Str_delete(_t4531, &(Bool){1});
                        ;
                        ;
                        Str *_t4534 = Str_lit("Generated: ", 11ULL);
                        (void)_t4534;
                        U64 _t4535 = 0;
                        (void)_t4535;
                        Str *_t4536 = Str_concat(_t4534, til_path);
                        (void)_t4536;
                        Str_delete(_t4534, &(Bool){1});
                        Array_set(_va97, &(U64){_t4535}, _t4536);
                        ;
                        println(_va97);
                        Str *_t4537 = Str_lit("Str", 3ULL);
                        (void)_t4537;
                        U64 _t4538; { U64 *_hp = (U64 *)Str_size(); _t4538 = *_hp; free(_hp); }
                        (void)_t4538;
                        U64 _t4539 = 1;
                        (void)_t4539;
                        Array *_va98 = Array_new(_t4537, &(U64){_t4538}, &(U64){_t4539});
                        (void)_va98;
                        Str_delete(_t4537, &(Bool){1});
                        ;
                        ;
                        Str *_t4540 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4540;
                        Str *_t4541 = Str_concat(_t4540, name);
                        (void)_t4541;
                        Str_delete(_t4540, &(Bool){1});
                        Str *_t4542 = Str_lit(".so", 3ULL);
                        (void)_t4542;
                        U64 _t4543 = 0;
                        (void)_t4543;
                        Str *_t4544 = Str_concat(_t4541, _t4542);
                        (void)_t4544;
                        Str_delete(_t4541, &(Bool){1});
                        Str_delete(_t4542, &(Bool){1});
                        Array_set(_va98, &(U64){_t4543}, _t4544);
                        ;
                        println(_va98);
                        Str *_t4545 = Str_lit("Str", 3ULL);
                        (void)_t4545;
                        U64 _t4546; { U64 *_hp = (U64 *)Str_size(); _t4546 = *_hp; free(_hp); }
                        (void)_t4546;
                        U64 _t4547 = 1;
                        (void)_t4547;
                        Array *_va99 = Array_new(_t4545, &(U64){_t4546}, &(U64){_t4547});
                        (void)_va99;
                        Str_delete(_t4545, &(Bool){1});
                        ;
                        ;
                        Str *_t4548 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4548;
                        Str *_t4549 = Str_concat(_t4548, name);
                        (void)_t4549;
                        Str_delete(_t4548, &(Bool){1});
                        Str *_t4550 = Str_lit(".a", 2ULL);
                        (void)_t4550;
                        U64 _t4551 = 0;
                        (void)_t4551;
                        Str *_t4552 = Str_concat(_t4549, _t4550);
                        (void)_t4552;
                        Str_delete(_t4549, &(Bool){1});
                        Str_delete(_t4550, &(Bool){1});
                        Array_set(_va99, &(U64){_t4551}, _t4552);
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
            I32 _t4618 = 0;
            (void)_t4618;
            Bool _t4619 = I32_eq(result, _t4618);
            (void)_t4619;
            ;
            Bool _t4620 = Bool_not(do_lib);
            (void)_t4620;
            Str *_t4621 = Str_lit("translate", 9ULL);
            (void)_t4621;
            Bool _t4622 = Bool_and(_t4619, _t4620);
            (void)_t4622;
            ;
            ;
            Bool _t4623; { Bool *_hp = (Bool *)Str_eq(command, _t4621); _t4623 = *_hp; free(_hp); }
            (void)_t4623;
            Str_delete(_t4621, &(Bool){1});
            Bool _t4624 = Bool_and(_t4622, _t4623);
            (void)_t4624;
            ;
            ;
            if (_t4624) {
                Str *_t4575 = Str_lit("Str", 3ULL);
                (void)_t4575;
                U64 _t4576; { U64 *_hp = (U64 *)Str_size(); _t4576 = *_hp; free(_hp); }
                (void)_t4576;
                U64 _t4577 = 1;
                (void)_t4577;
                Array *_va100 = Array_new(_t4575, &(U64){_t4576}, &(U64){_t4577});
                (void)_va100;
                Str_delete(_t4575, &(Bool){1});
                ;
                ;
                Str *_t4578 = Str_lit("Generated: ", 11ULL);
                (void)_t4578;
                U64 _t4579 = 0;
                (void)_t4579;
                Str *_t4580 = Str_concat(_t4578, c_path);
                (void)_t4580;
                Str_delete(_t4578, &(Bool){1});
                Array_set(_va100, &(U64){_t4579}, _t4580);
                ;
                println(_va100);
            }
            ;
            I32 _t4625 = 0;
            (void)_t4625;
            Bool _t4626 = I32_eq(result, _t4625);
            (void)_t4626;
            ;
            Bool _t4627 = Bool_not(do_lib);
            (void)_t4627;
            Str *_t4628 = Str_lit("translate", 9ULL);
            (void)_t4628;
            Bool _t4629; { Bool *_hp = (Bool *)Str_eq(command, _t4628); _t4629 = *_hp; free(_hp); }
            (void)_t4629;
            Str_delete(_t4628, &(Bool){1});
            Bool _t4630 = Bool_and(_t4626, _t4627);
            (void)_t4630;
            ;
            ;
            Bool _t4631 = Bool_not(_t4629);
            (void)_t4631;
            ;
            Bool _t4632 = Bool_and(_t4630, _t4631);
            (void)_t4632;
            ;
            ;
            if (_t4632) {
                I32 _t4581 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4581;
                result = _t4581;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4633 = 0;
            (void)_t4633;
            Bool _t4634 = I32_eq(result, _t4633);
            (void)_t4634;
            ;
            Bool _t4635 = Bool_not(do_lib);
            (void)_t4635;
            ;
            Str *_t4636 = Str_lit("run", 3ULL);
            (void)_t4636;
            Bool _t4637 = Bool_and(_t4634, _t4635);
            (void)_t4637;
            ;
            ;
            Bool _t4638; { Bool *_hp = (Bool *)Str_eq(command, _t4636); _t4638 = *_hp; free(_hp); }
            (void)_t4638;
            Str_delete(_t4636, &(Bool){1});
            Bool _t4639 = Bool_and(_t4637, _t4638);
            (void)_t4639;
            ;
            ;
            if (_t4639) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4583; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4583 = *_hp; free(_hp); }
                    (void)_t4583;
                    Bool _wcond4582; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4583}); _wcond4582 = *_hp; free(_hp); }
                    (void)_wcond4582;
                    ;
                    if (_wcond4582) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4584 = Str_lit(" '", 2ULL);
                    (void)_t4584;
                    Str *_t4585 = Str_concat(cmd, _t4584);
                    (void)_t4585;
                    Str_delete(_t4584, &(Bool){1});
                    Str *_t4586 = Str_concat(_t4585, uarg);
                    (void)_t4586;
                    Str_delete(_t4585, &(Bool){1});
                    Str *_t4587 = Str_lit("'", 1ULL);
                    (void)_t4587;
                    cmd = Str_concat(_t4586, _t4587);
                    Str_delete(_t4586, &(Bool){1});
                    Str_delete(_t4587, &(Bool){1});
                    U64 _t4588 = 1;
                    (void)_t4588;
                    U64 _t4589 = U64_add(DEREF(ui), _t4588);
                    (void)_t4589;
                    ;
                    *ui = _t4589;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4590 = til_system(cmd);
                (void)_t4590;
                Str_delete(cmd, &(Bool){1});
                result = _t4590;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4656 = Str_lit("ast", 3ULL);
            (void)_t4656;
            Bool _t4657; { Bool *_hp = (Bool *)Str_eq(command, _t4656); _t4657 = *_hp; free(_hp); }
            (void)_t4657;
            Str_delete(_t4656, &(Bool){1});
            if (_t4657) {
                Str *_t4640 = Str_lit("Str", 3ULL);
                (void)_t4640;
                U64 _t4641; { U64 *_hp = (U64 *)Str_size(); _t4641 = *_hp; free(_hp); }
                (void)_t4641;
                U64 _t4642 = 1;
                (void)_t4642;
                Array *_va101 = Array_new(_t4640, &(U64){_t4641}, &(U64){_t4642});
                (void)_va101;
                Str_delete(_t4640, &(Bool){1});
                ;
                ;
                Str *_t4643 = Str_lit("mode: ", 6ULL);
                (void)_t4643;
                U64 _t4644 = 0;
                (void)_t4644;
                Str *_t4645 = Str_concat(_t4643, &cur_mode->name);
                (void)_t4645;
                Str_delete(_t4643, &(Bool){1});
                Array_set(_va101, &(U64){_t4644}, _t4645);
                ;
                println(_va101);
                U32 _t4646 = 0;
                (void)_t4646;
                ast_print(ast, _t4646);
                ;
            } else {
                Str *_t4647 = Str_lit("Str", 3ULL);
                (void)_t4647;
                U64 _t4648; { U64 *_hp = (U64 *)Str_size(); _t4648 = *_hp; free(_hp); }
                (void)_t4648;
                U64 _t4649 = 1;
                (void)_t4649;
                Array *_va102 = Array_new(_t4647, &(U64){_t4648}, &(U64){_t4649});
                (void)_va102;
                Str_delete(_t4647, &(Bool){1});
                ;
                ;
                Str *_t4650 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4650;
                Str *_t4651 = Str_concat(_t4650, command);
                (void)_t4651;
                Str_delete(_t4650, &(Bool){1});
                Str *_t4652 = Str_lit("'", 1ULL);
                (void)_t4652;
                U64 _t4653 = 0;
                (void)_t4653;
                Str *_t4654 = Str_concat(_t4651, _t4652);
                (void)_t4654;
                Str_delete(_t4651, &(Bool){1});
                Str_delete(_t4652, &(Bool){1});
                Array_set(_va102, &(U64){_t4653}, _t4654);
                ;
                println(_va102);
                usage();
                I32 _t4655 = 1;
                (void)_t4655;
                result = _t4655;
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
    I64 _t4745 = I32_to_i64(result);
    (void)_t4745;
    ;
    exit(_t4745);
    ;
    return 0;
}

