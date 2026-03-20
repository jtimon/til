#include "til_til.h"

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t4164 = Str_lit("Str", 3ULL);
    (void)_t4164;
    U64 _t4165; { U64 *_hp = (U64 *)Str_size(); _t4165 = *_hp; free(_hp); }
    (void)_t4165;
    Vec *paths = Vec_new(_t4164, &(U64){_t4165});
    (void)paths;
    Str_delete(_t4164, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4139 = expr_nchildren(body);
        (void)_t4139;
        Bool _wcond4135; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4139}); _wcond4135 = *_hp; free(_hp); }
        (void)_wcond4135;
        ;
        if (_wcond4135) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t4140 = expr_get_tag(stmt);
        (void)_t4140;
        U32 _t4141 = expr_nchildren(stmt);
        (void)_t4141;
        U32 _t4142 = 2;
        (void)_t4142;
        Bool _t4143 = I32_eq(_t4140, DEREF(NODE_FCALL));
        (void)_t4143;
        ;
        Bool _t4144 = U32_eq(_t4141, _t4142);
        (void)_t4144;
        ;
        ;
        U32 *_t4145 = malloc(sizeof(U32));
        *_t4145 = 0;
        (void)_t4145;
        Expr *_t4146 = expr_get_child(stmt, DEREF(_t4145));
        (void)_t4146;
        I32 _t4147 = expr_get_tag(_t4146);
        (void)_t4147;
        U32_delete(_t4145, &(Bool){1});
        Bool _t4148 = Bool_and(_t4143, _t4144);
        (void)_t4148;
        ;
        ;
        Bool _t4149 = I32_eq(_t4147, DEREF(NODE_IDENT));
        (void)_t4149;
        ;
        U32 *_t4150 = malloc(sizeof(U32));
        *_t4150 = 0;
        (void)_t4150;
        Expr *_t4151 = expr_get_child(stmt, DEREF(_t4150));
        (void)_t4151;
        Str *_t4152 = expr_get_str_val(_t4151);
        (void)_t4152;
        Str *_t4153 = Str_lit("import", 6ULL);
        (void)_t4153;
        Bool _t4154 = Bool_and(_t4148, _t4149);
        (void)_t4154;
        ;
        ;
        Bool _t4155; { Bool *_hp = (Bool *)Str_eq(_t4152, _t4153); _t4155 = *_hp; free(_hp); }
        (void)_t4155;
        U32_delete(_t4150, &(Bool){1});
        Str_delete(_t4153, &(Bool){1});
        U32 *_t4156 = malloc(sizeof(U32));
        *_t4156 = 1;
        (void)_t4156;
        Expr *_t4157 = expr_get_child(stmt, DEREF(_t4156));
        (void)_t4157;
        I32 _t4158 = expr_get_tag(_t4157);
        (void)_t4158;
        U32_delete(_t4156, &(Bool){1});
        Bool _t4159 = Bool_and(_t4154, _t4155);
        (void)_t4159;
        ;
        ;
        Bool _t4160 = I32_eq(_t4158, DEREF(NODE_LITERAL_STR));
        (void)_t4160;
        ;
        Bool _t4161 = Bool_and(_t4159, _t4160);
        (void)_t4161;
        ;
        ;
        if (_t4161) {
            U32 *_t4136 = malloc(sizeof(U32));
            *_t4136 = 1;
            (void)_t4136;
            Expr *_t4137 = expr_get_child(stmt, DEREF(_t4136));
            (void)_t4137;
            Str *path = expr_get_str_val(_t4137);
            (void)path;
            Str *_t4138 = Str_clone(path);
            (void)_t4138;
            U32_delete(_t4136, &(Bool){1});
            Vec_push(paths, _t4138);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4162 = 1;
        (void)_t4162;
        U32 _t4163 = U32_add(DEREF(i), _t4162);
        (void)_t4163;
        ;
        *i = _t4163;
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
        U64 _t4216 = 0;
        (void)_t4216;
        U64 _t4217; { U64 *_hp = (U64 *)Vec_len(import_paths); _t4217 = *_hp; free(_hp); }
        (void)_t4217;
        Range *_fc4166 = Range_new(_t4216, _t4217);
        (void)_fc4166;
        ;
        ;
        U64 _fi4166 = 0;
        (void)_fi4166;
        while (1) {
            U64 _t4196; { U64 *_hp = (U64 *)Range_len(_fc4166); _t4196 = *_hp; free(_hp); }
            (void)_t4196;
            Bool _wcond4167; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi4166}, &(U64){_t4196}); _wcond4167 = *_hp; free(_hp); }
            (void)_wcond4167;
            ;
            if (_wcond4167) {
            } else {
                ;
                break;
            }
            ;
            U64 *i = Range_get(_fc4166, _fi4166);
            (void)i;
            U64 _t4197 = 1;
            (void)_t4197;
            U64 _t4198 = U64_add(_fi4166, _t4197);
            (void)_t4198;
            ;
            _fi4166 = _t4198;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t4199 = Str_lit("/", 1ULL);
            (void)_t4199;
            Str *_t4200 = Str_concat(base_dir, _t4199);
            (void)_t4200;
            Str_delete(_t4199, &(Bool){1});
            Str *try_path = Str_concat(_t4200, import_path);
            (void)try_path;
            Str_delete(_t4200, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t4201 = Str_lit("", 0ULL);
            (void)_t4201;
            U64 _t4202; { U64 *_hp = (U64 *)Str_len(lib_dir); _t4202 = *_hp; free(_hp); }
            (void)_t4202;
            U64 _t4203 = 0;
            (void)_t4203;
            Bool _t4204; { Bool *_hp = (Bool *)Str_eq(abs, _t4201); _t4204 = *_hp; free(_hp); }
            (void)_t4204;
            Str_delete(_t4201, &(Bool){1});
            Bool _t4205; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4202}, &(U64){_t4203}); _t4205 = *_hp; free(_hp); }
            (void)_t4205;
            ;
            ;
            Bool _t4206 = Bool_and(_t4204, _t4205);
            (void)_t4206;
            ;
            ;
            if (_t4206) {
                Str *_t4168 = Str_lit("/", 1ULL);
                (void)_t4168;
                Str *_t4169 = Str_concat(lib_dir, _t4168);
                (void)_t4169;
                Str_delete(_t4168, &(Bool){1});
                try_path = Str_concat(_t4169, import_path);
                Str_delete(_t4169, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t4207 = Str_lit("", 0ULL);
            (void)_t4207;
            Bool _t4208; { Bool *_hp = (Bool *)Str_eq(abs, _t4207); _t4208 = *_hp; free(_hp); }
            (void)_t4208;
            Str_delete(_t4207, &(Bool){1});
            if (_t4208) {
                Str *_t4170 = Str_lit("Str", 3ULL);
                (void)_t4170;
                U64 _t4171; { U64 *_hp = (U64 *)Str_size(); _t4171 = *_hp; free(_hp); }
                (void)_t4171;
                U64 _t4172 = 1;
                (void)_t4172;
                Array *_va72 = Array_new(_t4170, &(U64){_t4171}, &(U64){_t4172});
                (void)_va72;
                Str_delete(_t4170, &(Bool){1});
                ;
                ;
                Str *_t4173 = Str_lit("error: could not find import '", 30ULL);
                (void)_t4173;
                Str *_t4174 = Str_concat(_t4173, import_path);
                (void)_t4174;
                Str_delete(_t4173, &(Bool){1});
                Str *_t4175 = Str_lit("' (from ", 8ULL);
                (void)_t4175;
                Str *_t4176 = Str_concat(_t4174, _t4175);
                (void)_t4176;
                Str_delete(_t4174, &(Bool){1});
                Str_delete(_t4175, &(Bool){1});
                Str *_t4177 = Str_concat(_t4176, base_dir);
                (void)_t4177;
                Str_delete(_t4176, &(Bool){1});
                Str *_t4178 = Str_lit("/)", 2ULL);
                (void)_t4178;
                U64 _t4179 = 0;
                (void)_t4179;
                Str *_t4180 = Str_concat(_t4177, _t4178);
                (void)_t4180;
                Str_delete(_t4177, &(Bool){1});
                Str_delete(_t4178, &(Bool){1});
                Array_set(_va72, &(U64){_t4179}, _t4180);
                ;
                println(_va72);
                I64 _t4181 = 1;
                (void)_t4181;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                Range_delete(_fc4166, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t4181; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t4209; { Bool *_hp = (Bool *)Set_has(resolved_set, abs); _t4209 = *_hp; free(_hp); }
            (void)_t4209;
            if (_t4209) {
                ;
                Str_delete(abs, &(Bool){1});
                continue;
            }
            ;
            Str *_t4210 = Str_clone(abs);
            (void)_t4210;
            Set_add(resolved_set, _t4210);
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
            U64 _t4211; { U64 *_hp = (U64 *)Str_len(abs); _t4211 = *_hp; free(_hp); }
            (void)_t4211;
            U64 _t4212 = 1;
            (void)_t4212;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4211, _t4212);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t4183 = 0;
                (void)_t4183;
                U8 *_t4184 = Str_get(abs, last_slash);
                (void)_t4184;
                U8 _t4185 = 47;
                (void)_t4185;
                Bool _t4186; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4183}); _t4186 = *_hp; free(_hp); }
                (void)_t4186;
                ;
                Bool _t4187; { Bool *_hp = (Bool *)U8_neq(_t4184, &(U8){_t4185}); _t4187 = *_hp; free(_hp); }
                (void)_t4187;
                ;
                Bool _wcond4182 = Bool_and(_t4186, _t4187);
                (void)_wcond4182;
                ;
                ;
                if (_wcond4182) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t4188 = 1;
                (void)_t4188;
                U64 _t4189 = U64_sub(DEREF(last_slash), _t4188);
                (void)_t4189;
                ;
                *last_slash = _t4189;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t4213; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t4213 = *_hp; free(_hp); }
            (void)_t4213;
            U64 _t4214 = 0;
            (void)_t4214;
            Bool _t4215; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4213}, &(U64){_t4214}); _t4215 = *_hp; free(_hp); }
            (void)_t4215;
            ;
            ;
            if (_t4215) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t4190 = 0;
                (void)_t4190;
                Bool _t4191; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4190}); _t4191 = *_hp; free(_hp); }
                (void)_t4191;
                ;
                if (_t4191) {
                    ;
                    ;
                    Expr_delete(sub_ast, &(Bool){1});
                    Str_delete(sub_dir, &(Bool){1});
                    Vec_delete(sub_imports, &(Bool){1});
                    Str_delete(sub_mode, &(Bool){1});
                    Range_delete(_fc4166, &(Bool){1});
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
                U32 _t4193 = expr_nchildren(sub_ast);
                (void)_t4193;
                Bool _wcond4192; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t4193}); _wcond4192 = *_hp; free(_hp); }
                (void)_wcond4192;
                ;
                if (_wcond4192) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t4194 = 1;
                (void)_t4194;
                U32 _t4195 = U32_add(DEREF(k), _t4194);
                (void)_t4195;
                ;
                *k = _t4195;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        Range_delete(_fc4166, &(Bool){1});
        ;
    }
    I64 _t4218 = 0;
    (void)_t4218;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t4218; return _r; }
}

void usage(void) {
    Str *_t4219 = Str_lit("Str", 3ULL);
    (void)_t4219;
    U64 _t4220; { U64 *_hp = (U64 *)Str_size(); _t4220 = *_hp; free(_hp); }
    (void)_t4220;
    U64 _t4221 = 1;
    (void)_t4221;
    Array *_va73 = Array_new(_t4219, &(U64){_t4220}, &(U64){_t4221});
    (void)_va73;
    Str_delete(_t4219, &(Bool){1});
    ;
    ;
    U64 _t4222 = 0;
    (void)_t4222;
    Str *_t4223 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t4223;
    Array_set(_va73, &(U64){_t4222}, _t4223);
    ;
    println(_va73);
    Str *_t4224 = Str_lit("Str", 3ULL);
    (void)_t4224;
    U64 _t4225; { U64 *_hp = (U64 *)Str_size(); _t4225 = *_hp; free(_hp); }
    (void)_t4225;
    U64 _t4226 = 1;
    (void)_t4226;
    Array *_va74 = Array_new(_t4224, &(U64){_t4225}, &(U64){_t4226});
    (void)_va74;
    Str_delete(_t4224, &(Bool){1});
    ;
    ;
    U64 _t4227 = 0;
    (void)_t4227;
    Str *_t4228 = Str_lit("", 0ULL);
    (void)_t4228;
    Array_set(_va74, &(U64){_t4227}, _t4228);
    ;
    println(_va74);
    Str *_t4229 = Str_lit("Str", 3ULL);
    (void)_t4229;
    U64 _t4230; { U64 *_hp = (U64 *)Str_size(); _t4230 = *_hp; free(_hp); }
    (void)_t4230;
    U64 _t4231 = 1;
    (void)_t4231;
    Array *_va75 = Array_new(_t4229, &(U64){_t4230}, &(U64){_t4231});
    (void)_va75;
    Str_delete(_t4229, &(Bool){1});
    ;
    ;
    U64 _t4232 = 0;
    (void)_t4232;
    Str *_t4233 = Str_lit("Commands:", 9ULL);
    (void)_t4233;
    Array_set(_va75, &(U64){_t4232}, _t4233);
    ;
    println(_va75);
    Str *_t4234 = Str_lit("Str", 3ULL);
    (void)_t4234;
    U64 _t4235; { U64 *_hp = (U64 *)Str_size(); _t4235 = *_hp; free(_hp); }
    (void)_t4235;
    U64 _t4236 = 1;
    (void)_t4236;
    Array *_va76 = Array_new(_t4234, &(U64){_t4235}, &(U64){_t4236});
    (void)_va76;
    Str_delete(_t4234, &(Bool){1});
    ;
    ;
    U64 _t4237 = 0;
    (void)_t4237;
    Str *_t4238 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t4238;
    Array_set(_va76, &(U64){_t4237}, _t4238);
    ;
    println(_va76);
    Str *_t4239 = Str_lit("Str", 3ULL);
    (void)_t4239;
    U64 _t4240; { U64 *_hp = (U64 *)Str_size(); _t4240 = *_hp; free(_hp); }
    (void)_t4240;
    U64 _t4241 = 1;
    (void)_t4241;
    Array *_va77 = Array_new(_t4239, &(U64){_t4240}, &(U64){_t4241});
    (void)_va77;
    Str_delete(_t4239, &(Bool){1});
    ;
    ;
    U64 _t4242 = 0;
    (void)_t4242;
    Str *_t4243 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t4243;
    Array_set(_va77, &(U64){_t4242}, _t4243);
    ;
    println(_va77);
    Str *_t4244 = Str_lit("Str", 3ULL);
    (void)_t4244;
    U64 _t4245; { U64 *_hp = (U64 *)Str_size(); _t4245 = *_hp; free(_hp); }
    (void)_t4245;
    U64 _t4246 = 1;
    (void)_t4246;
    Array *_va78 = Array_new(_t4244, &(U64){_t4245}, &(U64){_t4246});
    (void)_va78;
    Str_delete(_t4244, &(Bool){1});
    ;
    ;
    U64 _t4247 = 0;
    (void)_t4247;
    Str *_t4248 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t4248;
    Array_set(_va78, &(U64){_t4247}, _t4248);
    ;
    println(_va78);
    Str *_t4249 = Str_lit("Str", 3ULL);
    (void)_t4249;
    U64 _t4250; { U64 *_hp = (U64 *)Str_size(); _t4250 = *_hp; free(_hp); }
    (void)_t4250;
    U64 _t4251 = 1;
    (void)_t4251;
    Array *_va79 = Array_new(_t4249, &(U64){_t4250}, &(U64){_t4251});
    (void)_va79;
    Str_delete(_t4249, &(Bool){1});
    ;
    ;
    U64 _t4252 = 0;
    (void)_t4252;
    Str *_t4253 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t4253;
    Array_set(_va79, &(U64){_t4252}, _t4253);
    ;
    println(_va79);
    Str *_t4254 = Str_lit("Str", 3ULL);
    (void)_t4254;
    U64 _t4255; { U64 *_hp = (U64 *)Str_size(); _t4255 = *_hp; free(_hp); }
    (void)_t4255;
    U64 _t4256 = 1;
    (void)_t4256;
    Array *_va80 = Array_new(_t4254, &(U64){_t4255}, &(U64){_t4256});
    (void)_va80;
    Str_delete(_t4254, &(Bool){1});
    ;
    ;
    U64 _t4257 = 0;
    (void)_t4257;
    Str *_t4258 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t4258;
    Array_set(_va80, &(U64){_t4257}, _t4258);
    ;
    println(_va80);
    Str *_t4259 = Str_lit("Str", 3ULL);
    (void)_t4259;
    U64 _t4260; { U64 *_hp = (U64 *)Str_size(); _t4260 = *_hp; free(_hp); }
    (void)_t4260;
    U64 _t4261 = 1;
    (void)_t4261;
    Array *_va81 = Array_new(_t4259, &(U64){_t4260}, &(U64){_t4261});
    (void)_va81;
    Str_delete(_t4259, &(Bool){1});
    ;
    ;
    U64 _t4262 = 0;
    (void)_t4262;
    Str *_t4263 = Str_lit("  help       Print this message", 31ULL);
    (void)_t4263;
    Array_set(_va81, &(U64){_t4262}, _t4263);
    ;
    println(_va81);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t4269 = 1;
    (void)_t4269;
    e->is_core = _t4269;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t4265 = expr_nchildren(e);
        (void)_t4265;
        Bool _wcond4264; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4265}); _wcond4264 = *_hp; free(_hp); }
        (void)_wcond4264;
        ;
        if (_wcond4264) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t4266 = expr_get_child(e, DEREF(i));
        (void)_t4266;
        mark_core(_t4266);
        U32 _t4267 = 1;
        (void)_t4267;
        U32 _t4268 = U32_add(DEREF(i), _t4267);
        (void)_t4268;
        ;
        *i = _t4268;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t4729 = malloc(sizeof(I64));
    *_t4729 = 0;
    (void)_t4729;
    _t4730 = malloc(sizeof(I64));
    *_t4730 = 1;
    (void)_t4730;
    _t4731 = malloc(sizeof(I64)); *_t4731 = I64_sub(DEREF(_t4729), DEREF(_t4730));
    (void)_t4731;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t4731));
    (void)CAP_LIT;
    _t4732 = malloc(sizeof(I64));
    *_t4732 = 0;
    (void)_t4732;
    _t4733 = malloc(sizeof(I64));
    *_t4733 = 2;
    (void)_t4733;
    _t4734 = malloc(sizeof(I64)); *_t4734 = I64_sub(DEREF(_t4732), DEREF(_t4733));
    (void)_t4734;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t4734));
    (void)CAP_VIEW;
    _t4735 = Str_lit("Str", 3ULL);
    (void)_t4735;
    _t4736 = Str_size();
    (void)_t4736;
    _t4737 = Str_lit("Mode", 4ULL);
    (void)_t4737;
    _t4738 = Mode_size();
    (void)_t4738;
    core_modes = Map_new(_t4735, _t4736, _t4737, _t4738);
    (void)core_modes;
    _t4739 = malloc(sizeof(Bool));
    *_t4739 = 0;
    (void)_t4739;
    _t4740 = malloc(sizeof(Bool));
    *_t4740 = 0;
    (void)_t4740;
    _t4741 = malloc(sizeof(Bool));
    *_t4741 = 0;
    (void)_t4741;
    _t4742 = malloc(sizeof(Bool));
    *_t4742 = 0;
    (void)_t4742;
    _t4743 = Str_lit("script", 6ULL);
    (void)_t4743;
    _t4744 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("script", 6ULL)); _t4744->name = *_ca; free(_ca); }
    _t4744->needs_main = DEREF(_t4739);
    _t4744->decls_only = DEREF(_t4740);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4744->auto_import = *_ca; free(_ca); }
    _t4744->is_pure = DEREF(_t4741);
    _t4744->debug_prints = DEREF(_t4742);
    (void)_t4744;
    _t4745 = malloc(sizeof(Bool));
    *_t4745 = 1;
    (void)_t4745;
    _t4746 = malloc(sizeof(Bool));
    *_t4746 = 1;
    (void)_t4746;
    _t4747 = malloc(sizeof(Bool));
    *_t4747 = 0;
    (void)_t4747;
    _t4748 = malloc(sizeof(Bool));
    *_t4748 = 0;
    (void)_t4748;
    _t4749 = Str_lit("cli", 3ULL);
    (void)_t4749;
    _t4750 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("cli", 3ULL)); _t4750->name = *_ca; free(_ca); }
    _t4750->needs_main = DEREF(_t4745);
    _t4750->decls_only = DEREF(_t4746);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4750->auto_import = *_ca; free(_ca); }
    _t4750->is_pure = DEREF(_t4747);
    _t4750->debug_prints = DEREF(_t4748);
    (void)_t4750;
    _t4751 = malloc(sizeof(Bool));
    *_t4751 = 1;
    (void)_t4751;
    _t4752 = malloc(sizeof(Bool));
    *_t4752 = 1;
    (void)_t4752;
    _t4753 = malloc(sizeof(Bool));
    *_t4753 = 0;
    (void)_t4753;
    _t4754 = malloc(sizeof(Bool));
    *_t4754 = 0;
    (void)_t4754;
    _t4755 = Str_lit("gui", 3ULL);
    (void)_t4755;
    _t4756 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4756->name = *_ca; free(_ca); }
    _t4756->needs_main = DEREF(_t4751);
    _t4756->decls_only = DEREF(_t4752);
    { Str *_ca = Str_clone(Str_lit("gui", 3ULL)); _t4756->auto_import = *_ca; free(_ca); }
    _t4756->is_pure = DEREF(_t4753);
    _t4756->debug_prints = DEREF(_t4754);
    (void)_t4756;
    _t4757 = malloc(sizeof(Bool));
    *_t4757 = 0;
    (void)_t4757;
    _t4758 = malloc(sizeof(Bool));
    *_t4758 = 1;
    (void)_t4758;
    _t4759 = malloc(sizeof(Bool));
    *_t4759 = 0;
    (void)_t4759;
    _t4760 = malloc(sizeof(Bool));
    *_t4760 = 0;
    (void)_t4760;
    _t4761 = Str_lit("test", 4ULL);
    (void)_t4761;
    _t4762 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("test", 4ULL)); _t4762->name = *_ca; free(_ca); }
    _t4762->needs_main = DEREF(_t4757);
    _t4762->decls_only = DEREF(_t4758);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4762->auto_import = *_ca; free(_ca); }
    _t4762->is_pure = DEREF(_t4759);
    _t4762->debug_prints = DEREF(_t4760);
    (void)_t4762;
    _t4763 = malloc(sizeof(Bool));
    *_t4763 = 0;
    (void)_t4763;
    _t4764 = malloc(sizeof(Bool));
    *_t4764 = 1;
    (void)_t4764;
    _t4765 = malloc(sizeof(Bool));
    *_t4765 = 1;
    (void)_t4765;
    _t4766 = malloc(sizeof(Bool));
    *_t4766 = 0;
    (void)_t4766;
    _t4767 = Str_lit("pure", 4ULL);
    (void)_t4767;
    _t4768 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pure", 4ULL)); _t4768->name = *_ca; free(_ca); }
    _t4768->needs_main = DEREF(_t4763);
    _t4768->decls_only = DEREF(_t4764);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4768->auto_import = *_ca; free(_ca); }
    _t4768->is_pure = DEREF(_t4765);
    _t4768->debug_prints = DEREF(_t4766);
    (void)_t4768;
    _t4769 = malloc(sizeof(Bool));
    *_t4769 = 0;
    (void)_t4769;
    _t4770 = malloc(sizeof(Bool));
    *_t4770 = 1;
    (void)_t4770;
    _t4771 = malloc(sizeof(Bool));
    *_t4771 = 1;
    (void)_t4771;
    _t4772 = malloc(sizeof(Bool));
    *_t4772 = 1;
    (void)_t4772;
    _t4773 = Str_lit("pura", 4ULL);
    (void)_t4773;
    _t4774 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("pura", 4ULL)); _t4774->name = *_ca; free(_ca); }
    _t4774->needs_main = DEREF(_t4769);
    _t4774->decls_only = DEREF(_t4770);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4774->auto_import = *_ca; free(_ca); }
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
    _t4779 = Str_lit("lib", 3ULL);
    (void)_t4779;
    _t4780 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("lib", 3ULL)); _t4780->name = *_ca; free(_ca); }
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
    *_t4783 = 0;
    (void)_t4783;
    _t4784 = malloc(sizeof(Bool));
    *_t4784 = 1;
    (void)_t4784;
    _t4785 = Str_lit("liba", 4ULL);
    (void)_t4785;
    _t4786 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(Str_lit("liba", 4ULL)); _t4786->name = *_ca; free(_ca); }
    _t4786->needs_main = DEREF(_t4781);
    _t4786->decls_only = DEREF(_t4782);
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t4786->auto_import = *_ca; free(_ca); }
    _t4786->is_pure = DEREF(_t4783);
    _t4786->debug_prints = DEREF(_t4784);
    (void)_t4786;
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
    U64 _t4649; { U64 *_hp = (U64 *)Array_len(args); _t4649 = *_hp; free(_hp); }
    (void)_t4649;
    U64 _t4650 = 0;
    (void)_t4650;
    Bool _t4651 = U64_eq(_t4649, _t4650);
    (void)_t4651;
    ;
    ;
    if (_t4651) {
        usage();
        Str *_t4270 = Str_lit("Str", 3ULL);
        (void)_t4270;
        U64 _t4271; { U64 *_hp = (U64 *)Str_size(); _t4271 = *_hp; free(_hp); }
        (void)_t4271;
        U64 _t4272 = 1;
        (void)_t4272;
        Array *_va82 = Array_new(_t4270, &(U64){_t4271}, &(U64){_t4272});
        (void)_va82;
        Str_delete(_t4270, &(Bool){1});
        ;
        ;
        U64 _t4273 = 0;
        (void)_t4273;
        Str *_t4274 = Str_lit("no arguments", 12ULL);
        (void)_t4274;
        Array_set(_va82, &(U64){_t4273}, _t4274);
        ;
        Str *_t4275 = Str_lit("src/til.til:205:15", 18ULL);
        (void)_t4275;
        panic(_t4275, _va82);
        Str_delete(_t4275, &(Bool){1});
    }
    ;
    U64 *_t4652 = malloc(sizeof(U64));
    *_t4652 = 0;
    (void)_t4652;
    Str *cmd_ref = Array_get(args, _t4652);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t4652, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t4653; { U64 *_hp = (U64 *)Array_len(args); _t4653 = *_hp; free(_hp); }
    (void)_t4653;
    U64 _t4654 = 1;
    (void)_t4654;
    Bool _t4655 = U64_eq(_t4653, _t4654);
    (void)_t4655;
    ;
    ;
    if (_t4655) {
        Str *_t4276 = Str_lit("help", 4ULL);
        (void)_t4276;
        Str *_t4277 = Str_lit("--help", 6ULL);
        (void)_t4277;
        Bool _t4278; { Bool *_hp = (Bool *)Str_eq(command, _t4276); _t4278 = *_hp; free(_hp); }
        (void)_t4278;
        Str_delete(_t4276, &(Bool){1});
        Bool _t4279; { Bool *_hp = (Bool *)Str_eq(command, _t4277); _t4279 = *_hp; free(_hp); }
        (void)_t4279;
        Str_delete(_t4277, &(Bool){1});
        Bool _t4280 = Bool_or(_t4278, _t4279);
        (void)_t4280;
        ;
        ;
        if (_t4280) {
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
            U64 _t4297; { U64 *_hp = (U64 *)Array_len(args); _t4297 = *_hp; free(_hp); }
            (void)_t4297;
            Bool _wcond4281; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t4297}); _wcond4281 = *_hp; free(_hp); }
            (void)_wcond4281;
            ;
            if (_wcond4281) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t4298 = Str_lit("-o", 2ULL);
            (void)_t4298;
            U64 _t4299 = 1;
            (void)_t4299;
            U64 _t4300 = U64_add(DEREF(path_idx), _t4299);
            (void)_t4300;
            ;
            U64 _t4301; { U64 *_hp = (U64 *)Array_len(args); _t4301 = *_hp; free(_hp); }
            (void)_t4301;
            Bool _t4302; { Bool *_hp = (Bool *)Str_eq(flag, _t4298); _t4302 = *_hp; free(_hp); }
            (void)_t4302;
            Str_delete(_t4298, &(Bool){1});
            Bool _t4303; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4300}, &(U64){_t4301}); _t4303 = *_hp; free(_hp); }
            (void)_t4303;
            ;
            ;
            Bool _t4304 = Bool_and(_t4302, _t4303);
            (void)_t4304;
            ;
            ;
            if (_t4304) {
                U64 _t4282 = 1;
                (void)_t4282;
                U64 *_t4283 = malloc(sizeof(U64)); *_t4283 = U64_add(DEREF(path_idx), _t4282);
                (void)_t4283;
                ;
                Str *oval = Array_get(args, _t4283);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t4283, &(Bool){1});
                U64 _t4284 = 2;
                (void)_t4284;
                U64 _t4285 = U64_add(DEREF(path_idx), _t4284);
                (void)_t4285;
                ;
                *path_idx = _t4285;
                ;
            } else {
                Str *_t4290 = Str_lit("-c", 2ULL);
                (void)_t4290;
                U64 _t4291 = 1;
                (void)_t4291;
                U64 _t4292 = U64_add(DEREF(path_idx), _t4291);
                (void)_t4292;
                ;
                U64 _t4293; { U64 *_hp = (U64 *)Array_len(args); _t4293 = *_hp; free(_hp); }
                (void)_t4293;
                Bool _t4294; { Bool *_hp = (Bool *)Str_eq(flag, _t4290); _t4294 = *_hp; free(_hp); }
                (void)_t4294;
                Str_delete(_t4290, &(Bool){1});
                Bool _t4295; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4292}, &(U64){_t4293}); _t4295 = *_hp; free(_hp); }
                (void)_t4295;
                ;
                ;
                Bool _t4296 = Bool_and(_t4294, _t4295);
                (void)_t4296;
                ;
                ;
                if (_t4296) {
                    U64 _t4286 = 1;
                    (void)_t4286;
                    U64 *_t4287 = malloc(sizeof(U64)); *_t4287 = U64_add(DEREF(path_idx), _t4286);
                    (void)_t4287;
                    ;
                    Str *cval = Array_get(args, _t4287);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t4287, &(Bool){1});
                    U64 _t4288 = 2;
                    (void)_t4288;
                    U64 _t4289 = U64_add(DEREF(path_idx), _t4288);
                    (void)_t4289;
                    ;
                    *path_idx = _t4289;
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
    Str *_t4656 = Str_lit("help", 4ULL);
    (void)_t4656;
    Str *_t4657 = Str_lit("--help", 6ULL);
    (void)_t4657;
    Bool _t4658; { Bool *_hp = (Bool *)Str_eq(command, _t4656); _t4658 = *_hp; free(_hp); }
    (void)_t4658;
    Str_delete(_t4656, &(Bool){1});
    Bool _t4659; { Bool *_hp = (Bool *)Str_eq(command, _t4657); _t4659 = *_hp; free(_hp); }
    (void)_t4659;
    Str_delete(_t4657, &(Bool){1});
    Bool _t4660 = Bool_or(_t4658, _t4659);
    (void)_t4660;
    ;
    ;
    if (_t4660) {
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
    Str *_t4661 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t4661;
    Str *core_path = Str_concat(bin_dir, _t4661);
    (void)core_path;
    Str_delete(_t4661, &(Bool){1});
    Str *_t4662 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t4662;
    Str *ext_c_path = Str_concat(bin_dir, _t4662);
    (void)ext_c_path;
    Str_delete(_t4662, &(Bool){1});
    Str *_t4663 = Str_lit("Str", 3ULL);
    (void)_t4663;
    U64 _t4664; { U64 *_hp = (U64 *)Str_size(); _t4664 = *_hp; free(_hp); }
    (void)_t4664;
    Set *resolved = Set_new(_t4663, &(U64){_t4664});
    (void)resolved;
    Str_delete(_t4663, &(Bool){1});
    ;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t4665; { U64 *_hp = (U64 *)Str_len(abs_path); _t4665 = *_hp; free(_hp); }
    (void)_t4665;
    U64 _t4666 = 0;
    (void)_t4666;
    Bool _t4667; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4665}, &(U64){_t4666}); _t4667 = *_hp; free(_hp); }
    (void)_t4667;
    ;
    ;
    if (_t4667) {
        U64 _t4313; { U64 *_hp = (U64 *)Str_len(abs_path); _t4313 = *_hp; free(_hp); }
        (void)_t4313;
        U64 _t4314 = 1;
        (void)_t4314;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t4313, _t4314);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t4306 = 0;
            (void)_t4306;
            U8 *_t4307 = Str_get(abs_path, last_slash);
            (void)_t4307;
            U8 _t4308 = 47;
            (void)_t4308;
            Bool _t4309; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t4306}); _t4309 = *_hp; free(_hp); }
            (void)_t4309;
            ;
            Bool _t4310; { Bool *_hp = (Bool *)U8_neq(_t4307, &(U8){_t4308}); _t4310 = *_hp; free(_hp); }
            (void)_t4310;
            ;
            Bool _wcond4305 = Bool_and(_t4309, _t4310);
            (void)_wcond4305;
            ;
            ;
            if (_wcond4305) {
            } else {
                ;
                break;
            }
            ;
            U64 _t4311 = 1;
            (void)_t4311;
            U64 _t4312 = U64_sub(DEREF(last_slash), _t4311);
            (void)_t4312;
            ;
            *last_slash = _t4312;
            ;
        }
        user_dir = til_str_left(abs_path, DEREF(last_slash));
        U64_delete(last_slash, &(Bool){1});
        Str *_t4315 = Str_clone(abs_path);
        (void)_t4315;
        Set_add(resolved, _t4315);
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
    U64 _t4668; { U64 *_hp = (U64 *)Str_len(core_abs); _t4668 = *_hp; free(_hp); }
    (void)_t4668;
    U64 _t4669 = 0;
    (void)_t4669;
    Bool _t4670; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4668}, &(U64){_t4669}); _t4670 = *_hp; free(_hp); }
    (void)_t4670;
    ;
    ;
    if (_t4670) {
        Bool _t4317; { Bool *_hp = (Bool *)Set_has(resolved, core_abs); _t4317 = *_hp; free(_hp); }
        (void)_t4317;
        if (_t4317) {
            Bool _t4316 = 1;
            (void)_t4316;
            skip_core = _t4316;
            ;
        }
        ;
        Str *_t4318 = Str_clone(core_abs);
        (void)_t4318;
        Set_add(resolved, _t4318);
    }
    ;
    Str_delete(core_abs, &(Bool){1});
    Vec *core_import_decls = expr_vec_new();
    (void)core_import_decls;
    Vec *core_imports = extract_imports(core_ast);
    (void)core_imports;
    U64 _t4671; { U64 *_hp = (U64 *)Vec_len(core_imports); _t4671 = *_hp; free(_hp); }
    (void)_t4671;
    U64 _t4672 = 0;
    (void)_t4672;
    Bool _t4673; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4671}, &(U64){_t4672}); _t4673 = *_hp; free(_hp); }
    (void)_t4673;
    ;
    ;
    Bool _t4674 = Bool_not(skip_core);
    (void)_t4674;
    Bool _t4675 = Bool_and(_t4673, _t4674);
    (void)_t4675;
    ;
    ;
    if (_t4675) {
        Str *_t4325 = Str_lit("/src/core", 9ULL);
        (void)_t4325;
        Str *core_dir = Str_concat(bin_dir, _t4325);
        (void)core_dir;
        Str_delete(_t4325, &(Bool){1});
        Str *_t4326 = Str_lit("", 0ULL);
        (void)_t4326;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t4326); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t4326, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t4327 = 0;
        (void)_t4327;
        Bool _t4328; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4327}); _t4328 = *_hp; free(_hp); }
        (void)_t4328;
        ;
        ;
        if (_t4328) {
            Str *_t4319 = Str_lit("Str", 3ULL);
            (void)_t4319;
            U64 _t4320; { U64 *_hp = (U64 *)Str_size(); _t4320 = *_hp; free(_hp); }
            (void)_t4320;
            U64 _t4321 = 1;
            (void)_t4321;
            Array *_va83 = Array_new(_t4319, &(U64){_t4320}, &(U64){_t4321});
            (void)_va83;
            Str_delete(_t4319, &(Bool){1});
            ;
            ;
            U64 _t4322 = 0;
            (void)_t4322;
            Str *_t4323 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t4323;
            Array_set(_va83, &(U64){_t4322}, _t4323);
            ;
            Str *_t4324 = Str_lit("src/til.til:291:19", 18ULL);
            (void)_t4324;
            panic(_t4324, _va83);
            Str_delete(_t4324, &(Bool){1});
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
    Str *_t4676 = Str_lit("script", 6ULL);
    (void)_t4676;
    Mode *cur_mode = mode_resolve(_t4676);
    (void)cur_mode;
    Str_delete(_t4676, &(Bool){1});
    U64 _t4677; { U64 *_hp = (U64 *)Str_len(mode_str); _t4677 = *_hp; free(_hp); }
    (void)_t4677;
    U64 _t4678 = 0;
    (void)_t4678;
    Bool _t4679; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4677}, &(U64){_t4678}); _t4679 = *_hp; free(_hp); }
    (void)_t4679;
    ;
    ;
    if (_t4679) {
        cur_mode = mode_resolve(mode_str);
        U64 _t4338; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t4338 = *_hp; free(_hp); }
        (void)_t4338;
        U64 _t4339 = 0;
        (void)_t4339;
        Bool _t4340 = U64_eq(_t4338, _t4339);
        (void)_t4340;
        ;
        ;
        if (_t4340) {
            Str *_t4329 = Str_lit("Str", 3ULL);
            (void)_t4329;
            U64 _t4330; { U64 *_hp = (U64 *)Str_size(); _t4330 = *_hp; free(_hp); }
            (void)_t4330;
            U64 _t4331 = 1;
            (void)_t4331;
            Array *_va84 = Array_new(_t4329, &(U64){_t4330}, &(U64){_t4331});
            (void)_va84;
            Str_delete(_t4329, &(Bool){1});
            ;
            ;
            Str *_t4332 = Str_lit("unknown mode '", 14ULL);
            (void)_t4332;
            Str *_t4333 = Str_concat(_t4332, mode_str);
            (void)_t4333;
            Str_delete(_t4332, &(Bool){1});
            Str *_t4334 = Str_lit("'", 1ULL);
            (void)_t4334;
            U64 _t4335 = 0;
            (void)_t4335;
            Str *_t4336 = Str_concat(_t4333, _t4334);
            (void)_t4336;
            Str_delete(_t4333, &(Bool){1});
            Str_delete(_t4334, &(Bool){1});
            Array_set(_va84, &(U64){_t4335}, _t4336);
            ;
            Str *_t4337 = Str_lit("src/til.til:307:19", 18ULL);
            (void)_t4337;
            panic(_t4337, _va84);
            Str_delete(_t4337, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t4680; { U64 *_hp = (U64 *)Vec_len(imports); _t4680 = *_hp; free(_hp); }
    (void)_t4680;
    U64 _t4681 = 0;
    (void)_t4681;
    Bool _t4682; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4680}, &(U64){_t4681}); _t4682 = *_hp; free(_hp); }
    (void)_t4682;
    ;
    ;
    if (_t4682) {
        Str *_t4347 = Str_lit("/src/lib", 8ULL);
        (void)_t4347;
        Str *lib_dir = Str_concat(bin_dir, _t4347);
        (void)lib_dir;
        Str_delete(_t4347, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t4348 = 0;
        (void)_t4348;
        Bool _t4349; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t4348}); _t4349 = *_hp; free(_hp); }
        (void)_t4349;
        ;
        ;
        if (_t4349) {
            Str *_t4341 = Str_lit("Str", 3ULL);
            (void)_t4341;
            U64 _t4342; { U64 *_hp = (U64 *)Str_size(); _t4342 = *_hp; free(_hp); }
            (void)_t4342;
            U64 _t4343 = 1;
            (void)_t4343;
            Array *_va85 = Array_new(_t4341, &(U64){_t4342}, &(U64){_t4343});
            (void)_va85;
            Str_delete(_t4341, &(Bool){1});
            ;
            ;
            U64 _t4344 = 0;
            (void)_t4344;
            Str *_t4345 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t4345;
            Array_set(_va85, &(U64){_t4344}, _t4345);
            ;
            Str *_t4346 = Str_lit("src/til.til:321:19", 18ULL);
            (void)_t4346;
            panic(_t4346, _va85);
            Str_delete(_t4346, &(Bool){1});
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
    Bool _t4683 = Bool_not(skip_core);
    (void)_t4683;
    ;
    if (_t4683) {
        while (1) {
            U32 _t4351 = expr_nchildren(core_ast);
            (void)_t4351;
            Bool _wcond4350; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4351}); _wcond4350 = *_hp; free(_hp); }
            (void)_wcond4350;
            ;
            if (_wcond4350) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4352 = 1;
            (void)_t4352;
            U32 _t4353 = U32_add(DEREF(i), _t4352);
            (void)_t4353;
            ;
            *i = _t4353;
            ;
        }
        U32 _t4358 = 0;
        (void)_t4358;
        *i = _t4358;
        ;
        while (1) {
            U32 _t4355 = expr_vec_count(core_import_decls);
            (void)_t4355;
            Bool _wcond4354; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4355}); _wcond4354 = *_hp; free(_hp); }
            (void)_wcond4354;
            ;
            if (_wcond4354) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t4356 = 1;
            (void)_t4356;
            U32 _t4357 = U32_add(DEREF(i), _t4356);
            (void)_t4357;
            ;
            *i = _t4357;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t4684; { U64 *_hp = (U64 *)Str_len(auto_import); _t4684 = *_hp; free(_hp); }
    (void)_t4684;
    U64 _t4685 = 0;
    (void)_t4685;
    Bool _t4686; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4684}, &(U64){_t4685}); _t4686 = *_hp; free(_hp); }
    (void)_t4686;
    ;
    ;
    if (_t4686) {
        Str *_t4363 = Str_lit("/src/modes/", 11ULL);
        (void)_t4363;
        Str *_t4364 = Str_concat(bin_dir, _t4363);
        (void)_t4364;
        Str_delete(_t4363, &(Bool){1});
        Str *_t4365 = Str_concat(_t4364, auto_import);
        (void)_t4365;
        Str_delete(_t4364, &(Bool){1});
        Str *_t4366 = Str_lit(".til", 4ULL);
        (void)_t4366;
        Str *mode_til_path = Str_concat(_t4365, _t4366);
        (void)mode_til_path;
        Str_delete(_t4365, &(Bool){1});
        Str_delete(_t4366, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t4367 = 0;
        (void)_t4367;
        *i = _t4367;
        ;
        while (1) {
            U32 _t4360 = expr_nchildren(mode_ast);
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
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t4361 = 1;
            (void)_t4361;
            U32 _t4362 = U32_add(DEREF(i), _t4361);
            (void)_t4362;
            ;
            *i = _t4362;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t4687 = 0;
    (void)_t4687;
    *i = _t4687;
    ;
    while (1) {
        U32 _t4369 = expr_vec_count(import_decls);
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
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4370 = 1;
        (void)_t4370;
        U32 _t4371 = U32_add(DEREF(i), _t4370);
        (void)_t4371;
        ;
        *i = _t4371;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t4688 = 0;
    (void)_t4688;
    *i = _t4688;
    ;
    while (1) {
        U32 _t4373 = expr_nchildren(ast);
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
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t4374 = 1;
        (void)_t4374;
        U32 _t4375 = U32_add(DEREF(i), _t4374);
        (void)_t4375;
        ;
        *i = _t4375;
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
    U32 _t4689 = 0;
    (void)_t4689;
    *i = _t4689;
    ;
    while (1) {
        U32 _t4391 = expr_nchildren(ast);
        (void)_t4391;
        Bool _wcond4376; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t4391}); _wcond4376 = *_hp; free(_hp); }
        (void)_wcond4376;
        ;
        if (_wcond4376) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t4392 = expr_get_tag(stmt);
        (void)_t4392;
        U32 _t4393 = expr_nchildren(stmt);
        (void)_t4393;
        U32 _t4394 = 2;
        (void)_t4394;
        Bool _t4395 = I32_eq(_t4392, DEREF(NODE_FCALL));
        (void)_t4395;
        ;
        Bool _t4396 = U32_eq(_t4393, _t4394);
        (void)_t4396;
        ;
        ;
        U32 *_t4397 = malloc(sizeof(U32));
        *_t4397 = 0;
        (void)_t4397;
        Expr *_t4398 = expr_get_child(stmt, DEREF(_t4397));
        (void)_t4398;
        I32 _t4399 = expr_get_tag(_t4398);
        (void)_t4399;
        U32_delete(_t4397, &(Bool){1});
        Bool _t4400 = Bool_and(_t4395, _t4396);
        (void)_t4400;
        ;
        ;
        Bool _t4401 = I32_eq(_t4399, DEREF(NODE_IDENT));
        (void)_t4401;
        ;
        U32 *_t4402 = malloc(sizeof(U32));
        *_t4402 = 1;
        (void)_t4402;
        Expr *_t4403 = expr_get_child(stmt, DEREF(_t4402));
        (void)_t4403;
        I32 _t4404 = expr_get_tag(_t4403);
        (void)_t4404;
        U32_delete(_t4402, &(Bool){1});
        Bool _t4405 = Bool_and(_t4400, _t4401);
        (void)_t4405;
        ;
        ;
        Bool _t4406 = I32_eq(_t4404, DEREF(NODE_LITERAL_STR));
        (void)_t4406;
        ;
        Bool _t4407 = Bool_and(_t4405, _t4406);
        (void)_t4407;
        ;
        ;
        if (_t4407) {
            U32 *_t4385 = malloc(sizeof(U32));
            *_t4385 = 0;
            (void)_t4385;
            Expr *_t4386 = expr_get_child(stmt, DEREF(_t4385));
            (void)_t4386;
            Str *fname = expr_get_str_val(_t4386);
            (void)fname;
            U32 *_t4387 = malloc(sizeof(U32));
            *_t4387 = 1;
            (void)_t4387;
            Expr *_t4388 = expr_get_child(stmt, DEREF(_t4387));
            (void)_t4388;
            Str *arg = expr_get_str_val(_t4388);
            (void)arg;
            Str *_t4389 = Str_lit("link", 4ULL);
            (void)_t4389;
            Bool _t4390; { Bool *_hp = (Bool *)Str_eq(fname, _t4389); _t4390 = *_hp; free(_hp); }
            (void)_t4390;
            Str_delete(_t4389, &(Bool){1});
            if (_t4390) {
                Str *_t4377 = Str_lit(" -l", 3ULL);
                (void)_t4377;
                Str *_t4378 = Str_concat(link_flags, _t4377);
                (void)_t4378;
                Str_delete(_t4377, &(Bool){1});
                link_flags = Str_concat(_t4378, arg);
                Str_delete(_t4378, &(Bool){1});
            } else {
                Str *_t4383 = Str_lit("link_c", 6ULL);
                (void)_t4383;
                Bool _t4384; { Bool *_hp = (Bool *)Str_eq(fname, _t4383); _t4384 = *_hp; free(_hp); }
                (void)_t4384;
                Str_delete(_t4383, &(Bool){1});
                if (_t4384) {
                    U64 _t4380; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4380 = *_hp; free(_hp); }
                    (void)_t4380;
                    U64 _t4381 = 0;
                    (void)_t4381;
                    Bool _t4382; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4380}, &(U64){_t4381}); _t4382 = *_hp; free(_hp); }
                    (void)_t4382;
                    ;
                    ;
                    if (_t4382) {
                        Str *_t4379 = Str_lit(" ", 1ULL);
                        (void)_t4379;
                        link_c_paths = Str_concat(link_c_paths, _t4379);
                        Str_delete(_t4379, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t4385, &(Bool){1});
            U32_delete(_t4387, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t4408 = 1;
        (void)_t4408;
        U32 _t4409 = U32_add(DEREF(i), _t4408);
        (void)_t4409;
        ;
        *i = _t4409;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t4690 = init_declarations(ast, scope);
    (void)_t4690;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t4691 = 0;
    (void)_t4691;
    Bool _t4692; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t4691}); _t4692 = *_hp; free(_hp); }
    (void)_t4692;
    ;
    if (_t4692) {
        Str *_t4410 = Str_lit("Str", 3ULL);
        (void)_t4410;
        U64 _t4411; { U64 *_hp = (U64 *)Str_size(); _t4411 = *_hp; free(_hp); }
        (void)_t4411;
        U64 _t4412 = 1;
        (void)_t4412;
        Array *_va86 = Array_new(_t4410, &(U64){_t4411}, &(U64){_t4412});
        (void)_va86;
        Str_delete(_t4410, &(Bool){1});
        ;
        ;
        Str *_t4413 = I32_to_str(&(I32){type_errors});
        (void)_t4413;
        Str *_t4414 = Str_lit(" type error(s) found", 20ULL);
        (void)_t4414;
        U64 _t4415 = 0;
        (void)_t4415;
        Str *_t4416 = Str_concat(_t4413, _t4414);
        (void)_t4416;
        Str_delete(_t4413, &(Bool){1});
        Str_delete(_t4414, &(Bool){1});
        Array_set(_va86, &(U64){_t4415}, _t4416);
        ;
        Str *_t4417 = Str_lit("src/til.til:416:15", 18ULL);
        (void)_t4417;
        panic(_t4417, _va86);
        Str_delete(_t4417, &(Bool){1});
    }
    ;
    ;
    Str *_t4693 = Str_lit("test", 4ULL);
    (void)_t4693;
    Str *_t4694 = Str_lit("test", 4ULL);
    (void)_t4694;
    Bool _t4695; { Bool *_hp = (Bool *)Str_eq(command, _t4693); _t4695 = *_hp; free(_hp); }
    (void)_t4695;
    Str_delete(_t4693, &(Bool){1});
    Bool _t4696; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4694); _t4696 = *_hp; free(_hp); }
    (void)_t4696;
    Str_delete(_t4694, &(Bool){1});
    Str *_t4697 = Str_lit("pure", 4ULL);
    (void)_t4697;
    Bool _t4698 = Bool_or(_t4695, _t4696);
    (void)_t4698;
    ;
    ;
    Bool _t4699; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4697); _t4699 = *_hp; free(_hp); }
    (void)_t4699;
    Str_delete(_t4697, &(Bool){1});
    Str *_t4700 = Str_lit("pura", 4ULL);
    (void)_t4700;
    Bool _t4701 = Bool_or(_t4698, _t4699);
    (void)_t4701;
    ;
    ;
    Bool _t4702; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t4700); _t4702 = *_hp; free(_hp); }
    (void)_t4702;
    Str_delete(_t4700, &(Bool){1});
    Bool run_tests = Bool_or(_t4701, _t4702);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t4703 = Str_lit("translate", 9ULL);
    (void)_t4703;
    Str *_t4704 = Str_lit("build", 5ULL);
    (void)_t4704;
    Bool _t4705; { Bool *_hp = (Bool *)Str_eq(command, _t4703); _t4705 = *_hp; free(_hp); }
    (void)_t4705;
    Str_delete(_t4703, &(Bool){1});
    Bool _t4706; { Bool *_hp = (Bool *)Str_eq(command, _t4704); _t4706 = *_hp; free(_hp); }
    (void)_t4706;
    Str_delete(_t4704, &(Bool){1});
    Bool _t4707; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4707 = *_hp; free(_hp); }
    (void)_t4707;
    Bool _t4708 = Bool_or(_t4705, _t4706);
    (void)_t4708;
    ;
    ;
    Bool is_lib_target = Bool_and(_t4707, _t4708);
    (void)is_lib_target;
    ;
    ;
    U64 _t4709; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4709 = *_hp; free(_hp); }
    (void)_t4709;
    U64 _t4710 = 0;
    (void)_t4710;
    Bool _t4711 = Bool_not(is_lib_target);
    (void)_t4711;
    ;
    Bool _t4712 = U64_eq(_t4709, _t4710);
    (void)_t4712;
    ;
    ;
    Bool _t4713 = Bool_and(_t4711, _t4712);
    (void)_t4713;
    ;
    ;
    if (_t4713) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t4714; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t4714 = *_hp; free(_hp); }
    (void)_t4714;
    U64 _t4715 = 0;
    (void)_t4715;
    Bool _t4716; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4714}, &(U64){_t4715}); _t4716 = *_hp; free(_hp); }
    (void)_t4716;
    ;
    ;
    if (_t4716) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t4717 = Str_lit("Str", 3ULL);
    (void)_t4717;
    U64 _t4718; { U64 *_hp = (U64 *)Str_size(); _t4718 = *_hp; free(_hp); }
    (void)_t4718;
    Vec *user_argv = Vec_new(_t4717, &(U64){_t4718});
    (void)user_argv;
    Str_delete(_t4717, &(Bool){1});
    ;
    U64 _t4719 = 1;
    (void)_t4719;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t4719);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t4434; { U64 *_hp = (U64 *)Array_len(args); _t4434 = *_hp; free(_hp); }
        (void)_t4434;
        Bool _wcond4418; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t4434}); _wcond4418 = *_hp; free(_hp); }
        (void)_wcond4418;
        ;
        if (_wcond4418) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t4435 = Str_lit("-l", 2ULL);
        (void)_t4435;
        Bool _t4436; { Bool *_hp = (Bool *)Str_starts_with(arg, _t4435); _t4436 = *_hp; free(_hp); }
        (void)_t4436;
        Str_delete(_t4435, &(Bool){1});
        if (_t4436) {
            U64 _t4421 = 2;
            (void)_t4421;
            U64 _t4422; { U64 *_hp = (U64 *)Str_len(arg); _t4422 = *_hp; free(_hp); }
            (void)_t4422;
            Str *lib = Str_substr(arg, &(U64){_t4421}, &(U64){_t4422});
            (void)lib;
            ;
            ;
            U64 _t4423; { U64 *_hp = (U64 *)Str_len(lib); _t4423 = *_hp; free(_hp); }
            (void)_t4423;
            U64 _t4424 = 0;
            (void)_t4424;
            U64 _t4425 = 1;
            (void)_t4425;
            U64 _t4426 = U64_add(DEREF(ai), _t4425);
            (void)_t4426;
            ;
            U64 _t4427; { U64 *_hp = (U64 *)Array_len(args); _t4427 = *_hp; free(_hp); }
            (void)_t4427;
            Bool _t4428 = U64_eq(_t4423, _t4424);
            (void)_t4428;
            ;
            ;
            Bool _t4429; { Bool *_hp = (Bool *)U64_lt(&(U64){_t4426}, &(U64){_t4427}); _t4429 = *_hp; free(_hp); }
            (void)_t4429;
            ;
            ;
            Bool _t4430 = Bool_and(_t4428, _t4429);
            (void)_t4430;
            ;
            ;
            if (_t4430) {
                U64 _t4419 = 1;
                (void)_t4419;
                U64 _t4420 = U64_add(DEREF(ai), _t4419);
                (void)_t4420;
                ;
                *ai = _t4420;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t4431 = Str_lit(" -l", 3ULL);
            (void)_t4431;
            Str *_t4432 = Str_concat(link_flags, _t4431);
            (void)_t4432;
            Str_delete(_t4431, &(Bool){1});
            link_flags = Str_concat(_t4432, lib);
            Str_delete(_t4432, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t4433 = Str_clone(arg);
            (void)_t4433;
            Vec_push(user_argv, _t4433);
        }
        ;
        U64 _t4437 = 1;
        (void)_t4437;
        U64 _t4438 = U64_add(DEREF(ai), _t4437);
        (void)_t4438;
        ;
        *ai = _t4438;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t4720; { U64 *_hp = (U64 *)Str_len(link_flags); _t4720 = *_hp; free(_hp); }
    (void)_t4720;
    U64 _t4721 = 0;
    (void)_t4721;
    Bool _t4722; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4720}, &(U64){_t4721}); _t4722 = *_hp; free(_hp); }
    (void)_t4722;
    ;
    ;
    if (_t4722) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t4723 = Str_lit("interpret", 9ULL);
    (void)_t4723;
    Str *_t4724 = Str_lit("test", 4ULL);
    (void)_t4724;
    Bool _t4725; { Bool *_hp = (Bool *)Str_eq(command, _t4723); _t4725 = *_hp; free(_hp); }
    (void)_t4725;
    Str_delete(_t4723, &(Bool){1});
    Bool _t4726; { Bool *_hp = (Bool *)Str_eq(command, _t4724); _t4726 = *_hp; free(_hp); }
    (void)_t4726;
    Str_delete(_t4724, &(Bool){1});
    Bool _t4727 = Bool_or(_t4725, _t4726);
    (void)_t4727;
    ;
    ;
    if (_t4727) {
        Str *_t4445 = Str_lit("interpret", 9ULL);
        (void)_t4445;
        Bool _t4446; { Bool *_hp = (Bool *)Str_eq(command, _t4445); _t4446 = *_hp; free(_hp); }
        (void)_t4446;
        Str_delete(_t4445, &(Bool){1});
        Bool _t4447 = Bool_and(is_lib_mode, _t4446);
        (void)_t4447;
        ;
        if (_t4447) {
            Str *_t4439 = Str_lit("Str", 3ULL);
            (void)_t4439;
            U64 _t4440; { U64 *_hp = (U64 *)Str_size(); _t4440 = *_hp; free(_hp); }
            (void)_t4440;
            U64 _t4441 = 1;
            (void)_t4441;
            Array *_va87 = Array_new(_t4439, &(U64){_t4440}, &(U64){_t4441});
            (void)_va87;
            Str_delete(_t4439, &(Bool){1});
            ;
            ;
            U64 _t4442 = 0;
            (void)_t4442;
            Str *_t4443 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t4443;
            Array_set(_va87, &(U64){_t4442}, _t4443);
            ;
            Str *_t4444 = Str_lit("src/til.til:470:19", 18ULL);
            (void)_t4444;
            panic(_t4444, _va87);
            Str_delete(_t4444, &(Bool){1});
        }
        ;
        I32 _t4448 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t4448;
        result = _t4448;
        ;
    } else {
        Str *_t4641 = Str_lit("translate", 9ULL);
        (void)_t4641;
        Str *_t4642 = Str_lit("build", 5ULL);
        (void)_t4642;
        Bool _t4643; { Bool *_hp = (Bool *)Str_eq(command, _t4641); _t4643 = *_hp; free(_hp); }
        (void)_t4643;
        Str_delete(_t4641, &(Bool){1});
        Bool _t4644; { Bool *_hp = (Bool *)Str_eq(command, _t4642); _t4644 = *_hp; free(_hp); }
        (void)_t4644;
        Str_delete(_t4642, &(Bool){1});
        Str *_t4645 = Str_lit("run", 3ULL);
        (void)_t4645;
        Bool _t4646 = Bool_or(_t4643, _t4644);
        (void)_t4646;
        ;
        ;
        Bool _t4647; { Bool *_hp = (Bool *)Str_eq(command, _t4645); _t4647 = *_hp; free(_hp); }
        (void)_t4647;
        Str_delete(_t4645, &(Bool){1});
        Bool _t4648 = Bool_or(_t4646, _t4647);
        (void)_t4648;
        ;
        ;
        if (_t4648) {
            Str *_t4574 = Str_lit("run", 3ULL);
            (void)_t4574;
            Bool _t4575; { Bool *_hp = (Bool *)Str_eq(command, _t4574); _t4575 = *_hp; free(_hp); }
            (void)_t4575;
            Str_delete(_t4574, &(Bool){1});
            Bool _t4576 = Bool_and(is_lib_mode, _t4575);
            (void)_t4576;
            ;
            if (_t4576) {
                Str *_t4449 = Str_lit("Str", 3ULL);
                (void)_t4449;
                U64 _t4450; { U64 *_hp = (U64 *)Str_size(); _t4450 = *_hp; free(_hp); }
                (void)_t4450;
                U64 _t4451 = 1;
                (void)_t4451;
                Array *_va88 = Array_new(_t4449, &(U64){_t4450}, &(U64){_t4451});
                (void)_va88;
                Str_delete(_t4449, &(Bool){1});
                ;
                ;
                U64 _t4452 = 0;
                (void)_t4452;
                Str *_t4453 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t4453;
                Array_set(_va88, &(U64){_t4452}, _t4453);
                ;
                Str *_t4454 = Str_lit("src/til.til:476:19", 18ULL);
                (void)_t4454;
                panic(_t4454, _va88);
                Str_delete(_t4454, &(Bool){1});
            }
            ;
            Str *_t4577 = Str_lit("/", 1ULL);
            (void)_t4577;
            I64 *last_slash = Str_rfind(path, _t4577);
            (void)last_slash;
            Str_delete(_t4577, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t4578 = 0;
            (void)_t4578;
            Bool _t4579; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t4578}); _t4579 = *_hp; free(_hp); }
            (void)_t4579;
            ;
            if (_t4579) {
                I64 _t4455 = 1;
                (void)_t4455;
                I64 _t4456 = I64_add(DEREF(last_slash), _t4455);
                (void)_t4456;
                ;
                U64 _t4457; { U64 *_hp = (U64 *)Str_len(path); _t4457 = *_hp; free(_hp); }
                (void)_t4457;
                U64 _t4458 = I64_to_u64(DEREF(last_slash));
                (void)_t4458;
                U64 _t4459 = U64_sub(_t4457, _t4458);
                (void)_t4459;
                ;
                ;
                U64 _t4460 = 1;
                (void)_t4460;
                U64 _t4461 = I64_to_u64(_t4456);
                (void)_t4461;
                ;
                U64 _t4462 = U64_sub(_t4459, _t4460);
                (void)_t4462;
                ;
                ;
                basename = Str_substr(path, &(U64){_t4461}, &(U64){_t4462});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t4580 = Str_lit(".til", 4ULL);
            (void)_t4580;
            Bool _t4581; { Bool *_hp = (Bool *)Str_ends_with(basename, _t4580); _t4581 = *_hp; free(_hp); }
            (void)_t4581;
            Str_delete(_t4580, &(Bool){1});
            if (_t4581) {
                U64 _t4463 = 4;
                (void)_t4463;
                U64 _t4464 = U64_sub(name_len, _t4463);
                (void)_t4464;
                ;
                name_len = _t4464;
                ;
            }
            ;
            U64 _t4582 = 0;
            (void)_t4582;
            Str *name = Str_substr(basename, &(U64){_t4582}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t4583 = Str_lit("gen/til/", 8ULL);
            (void)_t4583;
            Str *_t4584 = Str_concat(_t4583, name);
            (void)_t4584;
            Str_delete(_t4583, &(Bool){1});
            Str *_t4585 = Str_lit(".c", 2ULL);
            (void)_t4585;
            Str *c_path = Str_concat(_t4584, _t4585);
            (void)c_path;
            Str_delete(_t4584, &(Bool){1});
            Str_delete(_t4585, &(Bool){1});
            U64 _t4586; { U64 *_hp = (U64 *)Str_len(custom_c); _t4586 = *_hp; free(_hp); }
            (void)_t4586;
            U64 _t4587 = 0;
            (void)_t4587;
            Bool _t4588; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4586}, &(U64){_t4587}); _t4588 = *_hp; free(_hp); }
            (void)_t4588;
            ;
            ;
            if (_t4588) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t4589 = Str_lit("bin/til/", 8ULL);
            (void)_t4589;
            Str *bin_path = Str_concat(_t4589, name);
            (void)bin_path;
            Str_delete(_t4589, &(Bool){1});
            U64 _t4590; { U64 *_hp = (U64 *)Str_len(custom_bin); _t4590 = *_hp; free(_hp); }
            (void)_t4590;
            U64 _t4591 = 0;
            (void)_t4591;
            Bool _t4592; { Bool *_hp = (Bool *)U64_gt(&(U64){_t4590}, &(U64){_t4591}); _t4592 = *_hp; free(_hp); }
            (void)_t4592;
            ;
            ;
            if (_t4592) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t4593 = Str_lit("run", 3ULL);
            (void)_t4593;
            Bool _t4594; { Bool *_hp = (Bool *)Str_eq(command, _t4593); _t4594 = *_hp; free(_hp); }
            (void)_t4594;
            Str_delete(_t4593, &(Bool){1});
            Bool _t4595; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t4595 = *_hp; free(_hp); }
            (void)_t4595;
            Bool _t4596 = Bool_not(_t4594);
            (void)_t4596;
            ;
            Bool do_lib = Bool_and(_t4595, _t4596);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t4465 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t4465;
                I32 _t4466 = til_system(_t4465);
                (void)_t4466;
                Str_delete(_t4465, &(Bool){1});
                ;
            } else {
                Str *_t4471 = Str_lit("/", 1ULL);
                (void)_t4471;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t4471); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t4471, &(Bool){1});
                Str *_t4472 = Str_lit("/", 1ULL);
                (void)_t4472;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t4472); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t4472, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t4473 = 0;
                (void)_t4473;
                Bool _t4474; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t4473}); _t4474 = *_hp; free(_hp); }
                (void)_t4474;
                ;
                if (_t4474) {
                    U64 _t4467 = 0;
                    (void)_t4467;
                    U64 _t4468 = I64_to_u64(cp_slash);
                    (void)_t4468;
                    cp_dir = Str_substr(c_path, &(U64){_t4467}, &(U64){_t4468});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t4475 = 0;
                (void)_t4475;
                Bool _t4476; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t4475}); _t4476 = *_hp; free(_hp); }
                (void)_t4476;
                ;
                if (_t4476) {
                    U64 _t4469 = 0;
                    (void)_t4469;
                    U64 _t4470 = I64_to_u64(bp_slash);
                    (void)_t4470;
                    bp_dir = Str_substr(bin_path, &(U64){_t4469}, &(U64){_t4470});
                    ;
                    ;
                }
                ;
                ;
                Str *_t4477 = Str_lit("mkdir -p ", 9ULL);
                (void)_t4477;
                Str *_t4478 = Str_concat(_t4477, cp_dir);
                (void)_t4478;
                Str_delete(_t4477, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t4479 = Str_lit(" ", 1ULL);
                (void)_t4479;
                Str *_t4480 = Str_concat(_t4478, _t4479);
                (void)_t4480;
                Str_delete(_t4478, &(Bool){1});
                Str_delete(_t4479, &(Bool){1});
                Str *_t4481 = Str_concat(_t4480, bp_dir);
                (void)_t4481;
                Str_delete(_t4480, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t4482 = til_system(_t4481);
                (void)_t4482;
                Str_delete(_t4481, &(Bool){1});
                ;
            }
            I32 _t4597 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t4597;
            result = _t4597;
            ;
            I32 _t4598 = 0;
            (void)_t4598;
            Bool _t4599 = I32_eq(result, _t4598);
            (void)_t4599;
            ;
            Bool _t4600 = Bool_and(_t4599, do_lib);
            (void)_t4600;
            ;
            if (_t4600) {
                Str *_t4539 = Str_lit("gen/til/", 8ULL);
                (void)_t4539;
                Str *_t4540 = Str_concat(_t4539, name);
                (void)_t4540;
                Str_delete(_t4539, &(Bool){1});
                Str *_t4541 = Str_lit(".h", 2ULL);
                (void)_t4541;
                Str *h_path = Str_concat(_t4540, _t4541);
                (void)h_path;
                Str_delete(_t4540, &(Bool){1});
                Str_delete(_t4541, &(Bool){1});
                Str *_t4542 = Str_lit("gen/til/", 8ULL);
                (void)_t4542;
                Str *_t4543 = Str_concat(_t4542, name);
                (void)_t4543;
                Str_delete(_t4542, &(Bool){1});
                Str *_t4544 = Str_lit(".til", 4ULL);
                (void)_t4544;
                Str *til_path = Str_concat(_t4543, _t4544);
                (void)til_path;
                Str_delete(_t4543, &(Bool){1});
                Str_delete(_t4544, &(Bool){1});
                I32 _t4545 = build_header(ast, h_path);
                (void)_t4545;
                result = _t4545;
                ;
                I32 _t4546 = 0;
                (void)_t4546;
                Bool _t4547 = I32_eq(result, _t4546);
                (void)_t4547;
                ;
                if (_t4547) {
                    I32 _t4483 = build_til_binding(ast, til_path, name);
                    (void)_t4483;
                    result = _t4483;
                    ;
                }
                ;
                I32 _t4548 = 0;
                (void)_t4548;
                Str *_t4549 = Str_lit("translate", 9ULL);
                (void)_t4549;
                Bool _t4550 = I32_eq(result, _t4548);
                (void)_t4550;
                ;
                Bool _t4551; { Bool *_hp = (Bool *)Str_eq(command, _t4549); _t4551 = *_hp; free(_hp); }
                (void)_t4551;
                Str_delete(_t4549, &(Bool){1});
                Bool _t4552 = Bool_and(_t4550, _t4551);
                (void)_t4552;
                ;
                ;
                if (_t4552) {
                    Str *_t4484 = Str_lit("Str", 3ULL);
                    (void)_t4484;
                    U64 _t4485; { U64 *_hp = (U64 *)Str_size(); _t4485 = *_hp; free(_hp); }
                    (void)_t4485;
                    U64 _t4486 = 1;
                    (void)_t4486;
                    Array *_va89 = Array_new(_t4484, &(U64){_t4485}, &(U64){_t4486});
                    (void)_va89;
                    Str_delete(_t4484, &(Bool){1});
                    ;
                    ;
                    Str *_t4487 = Str_lit("Generated: ", 11ULL);
                    (void)_t4487;
                    U64 _t4488 = 0;
                    (void)_t4488;
                    Str *_t4489 = Str_concat(_t4487, c_path);
                    (void)_t4489;
                    Str_delete(_t4487, &(Bool){1});
                    Array_set(_va89, &(U64){_t4488}, _t4489);
                    ;
                    println(_va89);
                    Str *_t4490 = Str_lit("Str", 3ULL);
                    (void)_t4490;
                    U64 _t4491; { U64 *_hp = (U64 *)Str_size(); _t4491 = *_hp; free(_hp); }
                    (void)_t4491;
                    U64 _t4492 = 1;
                    (void)_t4492;
                    Array *_va90 = Array_new(_t4490, &(U64){_t4491}, &(U64){_t4492});
                    (void)_va90;
                    Str_delete(_t4490, &(Bool){1});
                    ;
                    ;
                    Str *_t4493 = Str_lit("Generated: ", 11ULL);
                    (void)_t4493;
                    U64 _t4494 = 0;
                    (void)_t4494;
                    Str *_t4495 = Str_concat(_t4493, h_path);
                    (void)_t4495;
                    Str_delete(_t4493, &(Bool){1});
                    Array_set(_va90, &(U64){_t4494}, _t4495);
                    ;
                    println(_va90);
                    Str *_t4496 = Str_lit("Str", 3ULL);
                    (void)_t4496;
                    U64 _t4497; { U64 *_hp = (U64 *)Str_size(); _t4497 = *_hp; free(_hp); }
                    (void)_t4497;
                    U64 _t4498 = 1;
                    (void)_t4498;
                    Array *_va91 = Array_new(_t4496, &(U64){_t4497}, &(U64){_t4498});
                    (void)_va91;
                    Str_delete(_t4496, &(Bool){1});
                    ;
                    ;
                    Str *_t4499 = Str_lit("Generated: ", 11ULL);
                    (void)_t4499;
                    U64 _t4500 = 0;
                    (void)_t4500;
                    Str *_t4501 = Str_concat(_t4499, til_path);
                    (void)_t4501;
                    Str_delete(_t4499, &(Bool){1});
                    Array_set(_va91, &(U64){_t4500}, _t4501);
                    ;
                    println(_va91);
                }
                ;
                I32 _t4553 = 0;
                (void)_t4553;
                Str *_t4554 = Str_lit("build", 5ULL);
                (void)_t4554;
                Bool _t4555 = I32_eq(result, _t4553);
                (void)_t4555;
                ;
                Bool _t4556; { Bool *_hp = (Bool *)Str_eq(command, _t4554); _t4556 = *_hp; free(_hp); }
                (void)_t4556;
                Str_delete(_t4554, &(Bool){1});
                Bool _t4557 = Bool_and(_t4555, _t4556);
                (void)_t4557;
                ;
                ;
                if (_t4557) {
                    I32 _t4536 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t4536;
                    result = _t4536;
                    ;
                    I32 _t4537 = 0;
                    (void)_t4537;
                    Bool _t4538 = I32_eq(result, _t4537);
                    (void)_t4538;
                    ;
                    if (_t4538) {
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
                        Str *_t4523 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4523;
                        Str *_t4524 = Str_concat(_t4523, name);
                        (void)_t4524;
                        Str_delete(_t4523, &(Bool){1});
                        Str *_t4525 = Str_lit(".so", 3ULL);
                        (void)_t4525;
                        U64 _t4526 = 0;
                        (void)_t4526;
                        Str *_t4527 = Str_concat(_t4524, _t4525);
                        (void)_t4527;
                        Str_delete(_t4524, &(Bool){1});
                        Str_delete(_t4525, &(Bool){1});
                        Array_set(_va95, &(U64){_t4526}, _t4527);
                        ;
                        println(_va95);
                        Str *_t4528 = Str_lit("Str", 3ULL);
                        (void)_t4528;
                        U64 _t4529; { U64 *_hp = (U64 *)Str_size(); _t4529 = *_hp; free(_hp); }
                        (void)_t4529;
                        U64 _t4530 = 1;
                        (void)_t4530;
                        Array *_va96 = Array_new(_t4528, &(U64){_t4529}, &(U64){_t4530});
                        (void)_va96;
                        Str_delete(_t4528, &(Bool){1});
                        ;
                        ;
                        Str *_t4531 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t4531;
                        Str *_t4532 = Str_concat(_t4531, name);
                        (void)_t4532;
                        Str_delete(_t4531, &(Bool){1});
                        Str *_t4533 = Str_lit(".a", 2ULL);
                        (void)_t4533;
                        U64 _t4534 = 0;
                        (void)_t4534;
                        Str *_t4535 = Str_concat(_t4532, _t4533);
                        (void)_t4535;
                        Str_delete(_t4532, &(Bool){1});
                        Str_delete(_t4533, &(Bool){1});
                        Array_set(_va96, &(U64){_t4534}, _t4535);
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
            I32 _t4601 = 0;
            (void)_t4601;
            Bool _t4602 = I32_eq(result, _t4601);
            (void)_t4602;
            ;
            Bool _t4603 = Bool_not(do_lib);
            (void)_t4603;
            Str *_t4604 = Str_lit("translate", 9ULL);
            (void)_t4604;
            Bool _t4605 = Bool_and(_t4602, _t4603);
            (void)_t4605;
            ;
            ;
            Bool _t4606; { Bool *_hp = (Bool *)Str_eq(command, _t4604); _t4606 = *_hp; free(_hp); }
            (void)_t4606;
            Str_delete(_t4604, &(Bool){1});
            Bool _t4607 = Bool_and(_t4605, _t4606);
            (void)_t4607;
            ;
            ;
            if (_t4607) {
                Str *_t4558 = Str_lit("Str", 3ULL);
                (void)_t4558;
                U64 _t4559; { U64 *_hp = (U64 *)Str_size(); _t4559 = *_hp; free(_hp); }
                (void)_t4559;
                U64 _t4560 = 1;
                (void)_t4560;
                Array *_va97 = Array_new(_t4558, &(U64){_t4559}, &(U64){_t4560});
                (void)_va97;
                Str_delete(_t4558, &(Bool){1});
                ;
                ;
                Str *_t4561 = Str_lit("Generated: ", 11ULL);
                (void)_t4561;
                U64 _t4562 = 0;
                (void)_t4562;
                Str *_t4563 = Str_concat(_t4561, c_path);
                (void)_t4563;
                Str_delete(_t4561, &(Bool){1});
                Array_set(_va97, &(U64){_t4562}, _t4563);
                ;
                println(_va97);
            }
            ;
            I32 _t4608 = 0;
            (void)_t4608;
            Bool _t4609 = I32_eq(result, _t4608);
            (void)_t4609;
            ;
            Bool _t4610 = Bool_not(do_lib);
            (void)_t4610;
            Str *_t4611 = Str_lit("translate", 9ULL);
            (void)_t4611;
            Bool _t4612; { Bool *_hp = (Bool *)Str_eq(command, _t4611); _t4612 = *_hp; free(_hp); }
            (void)_t4612;
            Str_delete(_t4611, &(Bool){1});
            Bool _t4613 = Bool_and(_t4609, _t4610);
            (void)_t4613;
            ;
            ;
            Bool _t4614 = Bool_not(_t4612);
            (void)_t4614;
            ;
            Bool _t4615 = Bool_and(_t4613, _t4614);
            (void)_t4615;
            ;
            ;
            if (_t4615) {
                I32 _t4564 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t4564;
                result = _t4564;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t4616 = 0;
            (void)_t4616;
            Bool _t4617 = I32_eq(result, _t4616);
            (void)_t4617;
            ;
            Bool _t4618 = Bool_not(do_lib);
            (void)_t4618;
            ;
            Str *_t4619 = Str_lit("run", 3ULL);
            (void)_t4619;
            Bool _t4620 = Bool_and(_t4617, _t4618);
            (void)_t4620;
            ;
            ;
            Bool _t4621; { Bool *_hp = (Bool *)Str_eq(command, _t4619); _t4621 = *_hp; free(_hp); }
            (void)_t4621;
            Str_delete(_t4619, &(Bool){1});
            Bool _t4622 = Bool_and(_t4620, _t4621);
            (void)_t4622;
            ;
            ;
            if (_t4622) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t4566; { U64 *_hp = (U64 *)Vec_len(user_argv); _t4566 = *_hp; free(_hp); }
                    (void)_t4566;
                    Bool _wcond4565; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t4566}); _wcond4565 = *_hp; free(_hp); }
                    (void)_wcond4565;
                    ;
                    if (_wcond4565) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t4567 = Str_lit(" '", 2ULL);
                    (void)_t4567;
                    Str *_t4568 = Str_concat(cmd, _t4567);
                    (void)_t4568;
                    Str_delete(_t4567, &(Bool){1});
                    Str *_t4569 = Str_concat(_t4568, uarg);
                    (void)_t4569;
                    Str_delete(_t4568, &(Bool){1});
                    Str *_t4570 = Str_lit("'", 1ULL);
                    (void)_t4570;
                    cmd = Str_concat(_t4569, _t4570);
                    Str_delete(_t4569, &(Bool){1});
                    Str_delete(_t4570, &(Bool){1});
                    U64 _t4571 = 1;
                    (void)_t4571;
                    U64 _t4572 = U64_add(DEREF(ui), _t4571);
                    (void)_t4572;
                    ;
                    *ui = _t4572;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t4573 = til_system(cmd);
                (void)_t4573;
                Str_delete(cmd, &(Bool){1});
                result = _t4573;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t4639 = Str_lit("ast", 3ULL);
            (void)_t4639;
            Bool _t4640; { Bool *_hp = (Bool *)Str_eq(command, _t4639); _t4640 = *_hp; free(_hp); }
            (void)_t4640;
            Str_delete(_t4639, &(Bool){1});
            if (_t4640) {
                Str *_t4623 = Str_lit("Str", 3ULL);
                (void)_t4623;
                U64 _t4624; { U64 *_hp = (U64 *)Str_size(); _t4624 = *_hp; free(_hp); }
                (void)_t4624;
                U64 _t4625 = 1;
                (void)_t4625;
                Array *_va98 = Array_new(_t4623, &(U64){_t4624}, &(U64){_t4625});
                (void)_va98;
                Str_delete(_t4623, &(Bool){1});
                ;
                ;
                Str *_t4626 = Str_lit("mode: ", 6ULL);
                (void)_t4626;
                U64 _t4627 = 0;
                (void)_t4627;
                Str *_t4628 = Str_concat(_t4626, &cur_mode->name);
                (void)_t4628;
                Str_delete(_t4626, &(Bool){1});
                Array_set(_va98, &(U64){_t4627}, _t4628);
                ;
                println(_va98);
                U32 _t4629 = 0;
                (void)_t4629;
                ast_print(ast, _t4629);
                ;
            } else {
                Str *_t4630 = Str_lit("Str", 3ULL);
                (void)_t4630;
                U64 _t4631; { U64 *_hp = (U64 *)Str_size(); _t4631 = *_hp; free(_hp); }
                (void)_t4631;
                U64 _t4632 = 1;
                (void)_t4632;
                Array *_va99 = Array_new(_t4630, &(U64){_t4631}, &(U64){_t4632});
                (void)_va99;
                Str_delete(_t4630, &(Bool){1});
                ;
                ;
                Str *_t4633 = Str_lit("error: unknown command '", 24ULL);
                (void)_t4633;
                Str *_t4634 = Str_concat(_t4633, command);
                (void)_t4634;
                Str_delete(_t4633, &(Bool){1});
                Str *_t4635 = Str_lit("'", 1ULL);
                (void)_t4635;
                U64 _t4636 = 0;
                (void)_t4636;
                Str *_t4637 = Str_concat(_t4634, _t4635);
                (void)_t4637;
                Str_delete(_t4634, &(Bool){1});
                Str_delete(_t4635, &(Bool){1});
                Array_set(_va99, &(U64){_t4636}, _t4637);
                ;
                println(_va99);
                usage();
                I32 _t4638 = 1;
                (void)_t4638;
                result = _t4638;
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
    I64 _t4728 = I32_to_i64(result);
    (void)_t4728;
    ;
    exit(_t4728);
    ;
    return 0;
}

