#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t2110 = Bool_clone(&self->needs_main);
    (void)_t2110;
    Bool _t2111 = Bool_clone(&self->decls_only);
    (void)_t2111;
    Bool _t2112 = Bool_clone(&self->is_pure);
    (void)_t2112;
    Bool _t2113 = Bool_clone(&self->debug_prints);
    (void)_t2113;
    Mode *_t2114 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t2114->name = *_ca; free(_ca); }
    _t2114->needs_main = _t2110;
    _t2114->decls_only = _t2111;
    { Str *_ca = Str_clone(&self->auto_import); _t2114->auto_import = *_ca; free(_ca); }
    _t2114->is_pure = _t2112;
    _t2114->debug_prints = _t2113;
    (void)_t2114;
    ;
    ;
    ;
    ;
    return _t2114;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2115 = 0;
    (void)_t2115;
    Str_delete(&self->name, &(Bool){_t2115});
    ;
    Bool _t2116 = 0;
    (void)_t2116;
    Bool_delete(&self->needs_main, &(Bool){_t2116});
    ;
    Bool _t2117 = 0;
    (void)_t2117;
    Bool_delete(&self->decls_only, &(Bool){_t2117});
    ;
    Bool _t2118 = 0;
    (void)_t2118;
    Str_delete(&self->auto_import, &(Bool){_t2118});
    ;
    Bool _t2119 = 0;
    (void)_t2119;
    Bool_delete(&self->is_pure, &(Bool){_t2119});
    ;
    Bool _t2120 = 0;
    (void)_t2120;
    Bool_delete(&self->debug_prints, &(Bool){_t2120});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Mode_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Mode);
    return r;
}

TypeScope * TypeScope_clone(TypeScope * self) {
    (void)self;
    TypeScope *_t2122 = malloc(sizeof(TypeScope));
    (void)_t2122;
    return _t2122;
}

void TypeScope_delete(TypeScope * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *TypeScope_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TypeScope);
    return r;
}

Vec * extract_imports(void * body) {
    (void)body;
    Str *_t2153 = Str_lit("Str", 3ULL);
    (void)_t2153;
    U64 _t2154; { U64 *_hp = (U64 *)Str_size(); _t2154 = *_hp; free(_hp); }
    (void)_t2154;
    Vec *paths = Vec_new(_t2153, &(U64){_t2154});
    (void)paths;
    Str_delete(_t2153, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2128 = expr_nchildren(body);
        (void)_t2128;
        Bool _wcond2124; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2128}); _wcond2124 = *_hp; free(_hp); }
        (void)_wcond2124;
        ;
        if (_wcond2124) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t2129 = expr_get_tag(stmt);
        (void)_t2129;
        U32 _t2130 = expr_nchildren(stmt);
        (void)_t2130;
        U32 _t2131 = 2;
        (void)_t2131;
        Bool _t2132 = I32_eq(_t2129, DEREF(NODE_FCALL));
        (void)_t2132;
        ;
        Bool _t2133 = U32_eq(_t2130, _t2131);
        (void)_t2133;
        ;
        ;
        U32 *_t2134 = malloc(sizeof(U32));
        *_t2134 = 0;
        (void)_t2134;
        Expr *_t2135 = expr_get_child(stmt, DEREF(_t2134));
        (void)_t2135;
        I32 _t2136 = expr_get_tag(_t2135);
        (void)_t2136;
        U32_delete(_t2134, &(Bool){1});
        Bool _t2137 = Bool_and(_t2132, _t2133);
        (void)_t2137;
        ;
        ;
        Bool _t2138 = I32_eq(_t2136, DEREF(NODE_IDENT));
        (void)_t2138;
        ;
        U32 *_t2139 = malloc(sizeof(U32));
        *_t2139 = 0;
        (void)_t2139;
        Expr *_t2140 = expr_get_child(stmt, DEREF(_t2139));
        (void)_t2140;
        Str *_t2141 = expr_get_str_val(_t2140);
        (void)_t2141;
        Str *_t2142 = Str_lit("import", 6ULL);
        (void)_t2142;
        Bool _t2143 = Bool_and(_t2137, _t2138);
        (void)_t2143;
        ;
        ;
        Bool _t2144; { Bool *_hp = (Bool *)Str_eq(_t2141, _t2142); _t2144 = *_hp; free(_hp); }
        (void)_t2144;
        U32_delete(_t2139, &(Bool){1});
        Str_delete(_t2142, &(Bool){1});
        U32 *_t2145 = malloc(sizeof(U32));
        *_t2145 = 1;
        (void)_t2145;
        Expr *_t2146 = expr_get_child(stmt, DEREF(_t2145));
        (void)_t2146;
        I32 _t2147 = expr_get_tag(_t2146);
        (void)_t2147;
        U32_delete(_t2145, &(Bool){1});
        Bool _t2148 = Bool_and(_t2143, _t2144);
        (void)_t2148;
        ;
        ;
        Bool _t2149 = I32_eq(_t2147, DEREF(NODE_LITERAL_STR));
        (void)_t2149;
        ;
        Bool _t2150 = Bool_and(_t2148, _t2149);
        (void)_t2150;
        ;
        ;
        if (_t2150) {
            U32 *_t2125 = malloc(sizeof(U32));
            *_t2125 = 1;
            (void)_t2125;
            Expr *_t2126 = expr_get_child(stmt, DEREF(_t2125));
            (void)_t2126;
            Str *path = expr_get_str_val(_t2126);
            (void)path;
            Str *_t2127 = Str_clone(path);
            (void)_t2127;
            U32_delete(_t2125, &(Bool){1});
            Vec_push(paths, _t2127);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2151 = 1;
        (void)_t2151;
        U32 _t2152 = U32_add(DEREF(i), _t2151);
        (void)_t2152;
        ;
        *i = _t2152;
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
        U64 _fi2155 = 0;
        (void)_fi2155;
        while (1) {
            U64 _t2185 = 0;
            (void)_t2185;
            U64 _t2186; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2186 = *_hp; free(_hp); }
            (void)_t2186;
            Range *_t2187 = Range_new(_t2185, _t2186);
            (void)_t2187;
            ;
            ;
            U64 _t2188; { U64 *_hp = (U64 *)Range_len(_t2187); _t2188 = *_hp; free(_hp); }
            (void)_t2188;
            Range_delete(_t2187, &(Bool){1});
            Bool _wcond2156; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2155}, &(U64){_t2188}); _wcond2156 = *_hp; free(_hp); }
            (void)_wcond2156;
            ;
            if (_wcond2156) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2189 = 0;
            (void)_t2189;
            U64 _t2190; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2190 = *_hp; free(_hp); }
            (void)_t2190;
            Range *_t2191 = Range_new(_t2189, _t2190);
            (void)_t2191;
            ;
            ;
            U64 *i = Range_get(_t2191, _fi2155);
            (void)i;
            Range_delete(_t2191, &(Bool){1});
            U64 _t2192 = 1;
            (void)_t2192;
            U64 _t2193 = U64_add(_fi2155, _t2192);
            (void)_t2193;
            ;
            _fi2155 = _t2193;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t2194 = Str_lit("/", 1ULL);
            (void)_t2194;
            Str *_t2195 = Str_concat(base_dir, _t2194);
            (void)_t2195;
            Str_delete(_t2194, &(Bool){1});
            Str *try_path = Str_concat(_t2195, import_path);
            (void)try_path;
            Str_delete(_t2195, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t2196 = Str_lit("", 0ULL);
            (void)_t2196;
            U64 _t2197; { U64 *_hp = (U64 *)Str_len(lib_dir); _t2197 = *_hp; free(_hp); }
            (void)_t2197;
            U64 _t2198 = 0;
            (void)_t2198;
            Bool _t2199; { Bool *_hp = (Bool *)Str_eq(abs, _t2196); _t2199 = *_hp; free(_hp); }
            (void)_t2199;
            Str_delete(_t2196, &(Bool){1});
            Bool _t2200; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2197}, &(U64){_t2198}); _t2200 = *_hp; free(_hp); }
            (void)_t2200;
            ;
            ;
            Bool _t2201 = Bool_and(_t2199, _t2200);
            (void)_t2201;
            ;
            ;
            if (_t2201) {
                Str *_t2157 = Str_lit("/", 1ULL);
                (void)_t2157;
                Str *_t2158 = Str_concat(lib_dir, _t2157);
                (void)_t2158;
                Str_delete(_t2157, &(Bool){1});
                try_path = Str_concat(_t2158, import_path);
                Str_delete(_t2158, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t2202 = Str_lit("", 0ULL);
            (void)_t2202;
            Bool _t2203; { Bool *_hp = (Bool *)Str_eq(abs, _t2202); _t2203 = *_hp; free(_hp); }
            (void)_t2203;
            Str_delete(_t2202, &(Bool){1});
            if (_t2203) {
                Str *_t2159 = Str_lit("Str", 3ULL);
                (void)_t2159;
                U64 _t2160; { U64 *_hp = (U64 *)Str_size(); _t2160 = *_hp; free(_hp); }
                (void)_t2160;
                U64 _t2161 = 1;
                (void)_t2161;
                Array *_va50 = Array_new(_t2159, &(U64){_t2160}, &(U64){_t2161});
                (void)_va50;
                Str_delete(_t2159, &(Bool){1});
                ;
                ;
                Str *_t2162 = Str_lit("error: could not find import '", 30ULL);
                (void)_t2162;
                Str *_t2163 = Str_concat(_t2162, import_path);
                (void)_t2163;
                Str_delete(_t2162, &(Bool){1});
                Str *_t2164 = Str_lit("' (from ", 8ULL);
                (void)_t2164;
                Str *_t2165 = Str_concat(_t2163, _t2164);
                (void)_t2165;
                Str_delete(_t2163, &(Bool){1});
                Str_delete(_t2164, &(Bool){1});
                Str *_t2166 = Str_concat(_t2165, base_dir);
                (void)_t2166;
                Str_delete(_t2165, &(Bool){1});
                Str *_t2167 = Str_lit("/)", 2ULL);
                (void)_t2167;
                U64 _t2168 = 0;
                (void)_t2168;
                Str *_t2169 = Str_concat(_t2166, _t2167);
                (void)_t2169;
                Str_delete(_t2166, &(Bool){1});
                Str_delete(_t2167, &(Bool){1});
                Array_set(_va50, &(U64){_t2168}, _t2169);
                ;
                println(_va50);
                I64 _t2170 = 1;
                (void)_t2170;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t2170; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t2204 = til_set_has(resolved_set, abs);
            (void)_t2204;
            if (_t2204) {
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
            U64 _t2205; { U64 *_hp = (U64 *)Str_len(abs); _t2205 = *_hp; free(_hp); }
            (void)_t2205;
            U64 _t2206 = 1;
            (void)_t2206;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2205, _t2206);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t2172 = 0;
                (void)_t2172;
                U8 *_t2173 = Str_get(abs, last_slash);
                (void)_t2173;
                U8 _t2174 = 47;
                (void)_t2174;
                Bool _t2175; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2172}); _t2175 = *_hp; free(_hp); }
                (void)_t2175;
                ;
                Bool _t2176; { Bool *_hp = (Bool *)U8_neq(_t2173, &(U8){_t2174}); _t2176 = *_hp; free(_hp); }
                (void)_t2176;
                ;
                Bool _wcond2171 = Bool_and(_t2175, _t2176);
                (void)_wcond2171;
                ;
                ;
                if (_wcond2171) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2177 = 1;
                (void)_t2177;
                U64 _t2178 = U64_sub(DEREF(last_slash), _t2177);
                (void)_t2178;
                ;
                *last_slash = _t2178;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t2207; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t2207 = *_hp; free(_hp); }
            (void)_t2207;
            U64 _t2208 = 0;
            (void)_t2208;
            Bool _t2209; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2207}, &(U64){_t2208}); _t2209 = *_hp; free(_hp); }
            (void)_t2209;
            ;
            ;
            if (_t2209) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t2179 = 0;
                (void)_t2179;
                Bool _t2180; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2179}); _t2180 = *_hp; free(_hp); }
                (void)_t2180;
                ;
                if (_t2180) {
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
                U32 _t2182 = expr_nchildren(sub_ast);
                (void)_t2182;
                Bool _wcond2181; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t2182}); _wcond2181 = *_hp; free(_hp); }
                (void)_wcond2181;
                ;
                if (_wcond2181) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t2183 = 1;
                (void)_t2183;
                U32 _t2184 = U32_add(DEREF(k), _t2183);
                (void)_t2184;
                ;
                *k = _t2184;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t2210 = 0;
    (void)_t2210;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2210; return _r; }
}

void usage(void) {
    Str *_t2211 = Str_lit("Str", 3ULL);
    (void)_t2211;
    U64 _t2212; { U64 *_hp = (U64 *)Str_size(); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    U64 _t2213 = 1;
    (void)_t2213;
    Array *_va51 = Array_new(_t2211, &(U64){_t2212}, &(U64){_t2213});
    (void)_va51;
    Str_delete(_t2211, &(Bool){1});
    ;
    ;
    U64 _t2214 = 0;
    (void)_t2214;
    Str *_t2215 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t2215;
    Array_set(_va51, &(U64){_t2214}, _t2215);
    ;
    println(_va51);
    Str *_t2216 = Str_lit("Str", 3ULL);
    (void)_t2216;
    U64 _t2217; { U64 *_hp = (U64 *)Str_size(); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    U64 _t2218 = 1;
    (void)_t2218;
    Array *_va52 = Array_new(_t2216, &(U64){_t2217}, &(U64){_t2218});
    (void)_va52;
    Str_delete(_t2216, &(Bool){1});
    ;
    ;
    U64 _t2219 = 0;
    (void)_t2219;
    Str *_t2220 = Str_lit("", 0ULL);
    (void)_t2220;
    Array_set(_va52, &(U64){_t2219}, _t2220);
    ;
    println(_va52);
    Str *_t2221 = Str_lit("Str", 3ULL);
    (void)_t2221;
    U64 _t2222; { U64 *_hp = (U64 *)Str_size(); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    U64 _t2223 = 1;
    (void)_t2223;
    Array *_va53 = Array_new(_t2221, &(U64){_t2222}, &(U64){_t2223});
    (void)_va53;
    Str_delete(_t2221, &(Bool){1});
    ;
    ;
    U64 _t2224 = 0;
    (void)_t2224;
    Str *_t2225 = Str_lit("Commands:", 9ULL);
    (void)_t2225;
    Array_set(_va53, &(U64){_t2224}, _t2225);
    ;
    println(_va53);
    Str *_t2226 = Str_lit("Str", 3ULL);
    (void)_t2226;
    U64 _t2227; { U64 *_hp = (U64 *)Str_size(); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    U64 _t2228 = 1;
    (void)_t2228;
    Array *_va54 = Array_new(_t2226, &(U64){_t2227}, &(U64){_t2228});
    (void)_va54;
    Str_delete(_t2226, &(Bool){1});
    ;
    ;
    U64 _t2229 = 0;
    (void)_t2229;
    Str *_t2230 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t2230;
    Array_set(_va54, &(U64){_t2229}, _t2230);
    ;
    println(_va54);
    Str *_t2231 = Str_lit("Str", 3ULL);
    (void)_t2231;
    U64 _t2232; { U64 *_hp = (U64 *)Str_size(); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    U64 _t2233 = 1;
    (void)_t2233;
    Array *_va55 = Array_new(_t2231, &(U64){_t2232}, &(U64){_t2233});
    (void)_va55;
    Str_delete(_t2231, &(Bool){1});
    ;
    ;
    U64 _t2234 = 0;
    (void)_t2234;
    Str *_t2235 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t2235;
    Array_set(_va55, &(U64){_t2234}, _t2235);
    ;
    println(_va55);
    Str *_t2236 = Str_lit("Str", 3ULL);
    (void)_t2236;
    U64 _t2237; { U64 *_hp = (U64 *)Str_size(); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    U64 _t2238 = 1;
    (void)_t2238;
    Array *_va56 = Array_new(_t2236, &(U64){_t2237}, &(U64){_t2238});
    (void)_va56;
    Str_delete(_t2236, &(Bool){1});
    ;
    ;
    U64 _t2239 = 0;
    (void)_t2239;
    Str *_t2240 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t2240;
    Array_set(_va56, &(U64){_t2239}, _t2240);
    ;
    println(_va56);
    Str *_t2241 = Str_lit("Str", 3ULL);
    (void)_t2241;
    U64 _t2242; { U64 *_hp = (U64 *)Str_size(); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    U64 _t2243 = 1;
    (void)_t2243;
    Array *_va57 = Array_new(_t2241, &(U64){_t2242}, &(U64){_t2243});
    (void)_va57;
    Str_delete(_t2241, &(Bool){1});
    ;
    ;
    U64 _t2244 = 0;
    (void)_t2244;
    Str *_t2245 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t2245;
    Array_set(_va57, &(U64){_t2244}, _t2245);
    ;
    println(_va57);
    Str *_t2246 = Str_lit("Str", 3ULL);
    (void)_t2246;
    U64 _t2247; { U64 *_hp = (U64 *)Str_size(); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    U64 _t2248 = 1;
    (void)_t2248;
    Array *_va58 = Array_new(_t2246, &(U64){_t2247}, &(U64){_t2248});
    (void)_va58;
    Str_delete(_t2246, &(Bool){1});
    ;
    ;
    U64 _t2249 = 0;
    (void)_t2249;
    Str *_t2250 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t2250;
    Array_set(_va58, &(U64){_t2249}, _t2250);
    ;
    println(_va58);
    Str *_t2251 = Str_lit("Str", 3ULL);
    (void)_t2251;
    U64 _t2252; { U64 *_hp = (U64 *)Str_size(); _t2252 = *_hp; free(_hp); }
    (void)_t2252;
    U64 _t2253 = 1;
    (void)_t2253;
    Array *_va59 = Array_new(_t2251, &(U64){_t2252}, &(U64){_t2253});
    (void)_va59;
    Str_delete(_t2251, &(Bool){1});
    ;
    ;
    U64 _t2254 = 0;
    (void)_t2254;
    Str *_t2255 = Str_lit("  help       Print this message", 31ULL);
    (void)_t2255;
    Array_set(_va59, &(U64){_t2254}, _t2255);
    ;
    println(_va59);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t2261 = 1;
    (void)_t2261;
    e->is_core = _t2261;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2257 = expr_nchildren(e);
        (void)_t2257;
        Bool _wcond2256; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2257}); _wcond2256 = *_hp; free(_hp); }
        (void)_wcond2256;
        ;
        if (_wcond2256) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t2258 = expr_get_child(e, DEREF(i));
        (void)_t2258;
        mark_core(_t2258);
        U32 _t2259 = 1;
        (void)_t2259;
        U32 _t2260 = U32_add(DEREF(i), _t2259);
        (void)_t2260;
        ;
        *i = _t2260;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t2717 = malloc(sizeof(I64));
    *_t2717 = 0;
    (void)_t2717;
    _t2718 = malloc(sizeof(I64));
    *_t2718 = 1;
    (void)_t2718;
    _t2719 = malloc(sizeof(I64)); *_t2719 = I64_sub(DEREF(_t2717), DEREF(_t2718));
    (void)_t2719;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2719));
    (void)CAP_LIT;
    _t2720 = malloc(sizeof(I64));
    *_t2720 = 0;
    (void)_t2720;
    _t2721 = malloc(sizeof(I64));
    *_t2721 = 2;
    (void)_t2721;
    _t2722 = malloc(sizeof(I64)); *_t2722 = I64_sub(DEREF(_t2720), DEREF(_t2721));
    (void)_t2722;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2722));
    (void)CAP_VIEW;
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
    U64 _t2639; { U64 *_hp = (U64 *)Array_len(args); _t2639 = *_hp; free(_hp); }
    (void)_t2639;
    U64 _t2640 = 0;
    (void)_t2640;
    Bool _t2641 = U64_eq(_t2639, _t2640);
    (void)_t2641;
    ;
    ;
    if (_t2641) {
        usage();
        Str *_t2262 = Str_lit("Str", 3ULL);
        (void)_t2262;
        U64 _t2263; { U64 *_hp = (U64 *)Str_size(); _t2263 = *_hp; free(_hp); }
        (void)_t2263;
        U64 _t2264 = 1;
        (void)_t2264;
        Array *_va60 = Array_new(_t2262, &(U64){_t2263}, &(U64){_t2264});
        (void)_va60;
        Str_delete(_t2262, &(Bool){1});
        ;
        ;
        U64 _t2265 = 0;
        (void)_t2265;
        Str *_t2266 = Str_lit("no arguments", 12ULL);
        (void)_t2266;
        Array_set(_va60, &(U64){_t2265}, _t2266);
        ;
        Str *_t2267 = Str_lit("src/til.til:218:15", 18ULL);
        (void)_t2267;
        panic(_t2267, _va60);
        Str_delete(_t2267, &(Bool){1});
    }
    ;
    U64 *_t2642 = malloc(sizeof(U64));
    *_t2642 = 0;
    (void)_t2642;
    Str *cmd_ref = Array_get(args, _t2642);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t2642, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t2643; { U64 *_hp = (U64 *)Array_len(args); _t2643 = *_hp; free(_hp); }
    (void)_t2643;
    U64 _t2644 = 1;
    (void)_t2644;
    Bool _t2645 = U64_eq(_t2643, _t2644);
    (void)_t2645;
    ;
    ;
    if (_t2645) {
        Str *_t2268 = Str_lit("help", 4ULL);
        (void)_t2268;
        Str *_t2269 = Str_lit("--help", 6ULL);
        (void)_t2269;
        Bool _t2270; { Bool *_hp = (Bool *)Str_eq(command, _t2268); _t2270 = *_hp; free(_hp); }
        (void)_t2270;
        Str_delete(_t2268, &(Bool){1});
        Bool _t2271; { Bool *_hp = (Bool *)Str_eq(command, _t2269); _t2271 = *_hp; free(_hp); }
        (void)_t2271;
        Str_delete(_t2269, &(Bool){1});
        Bool _t2272 = Bool_or(_t2270, _t2271);
        (void)_t2272;
        ;
        ;
        if (_t2272) {
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
            U64 _t2289; { U64 *_hp = (U64 *)Array_len(args); _t2289 = *_hp; free(_hp); }
            (void)_t2289;
            Bool _wcond2273; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t2289}); _wcond2273 = *_hp; free(_hp); }
            (void)_wcond2273;
            ;
            if (_wcond2273) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t2290 = Str_lit("-o", 2ULL);
            (void)_t2290;
            U64 _t2291 = 1;
            (void)_t2291;
            U64 _t2292 = U64_add(DEREF(path_idx), _t2291);
            (void)_t2292;
            ;
            U64 _t2293; { U64 *_hp = (U64 *)Array_len(args); _t2293 = *_hp; free(_hp); }
            (void)_t2293;
            Bool _t2294; { Bool *_hp = (Bool *)Str_eq(flag, _t2290); _t2294 = *_hp; free(_hp); }
            (void)_t2294;
            Str_delete(_t2290, &(Bool){1});
            Bool _t2295; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2292}, &(U64){_t2293}); _t2295 = *_hp; free(_hp); }
            (void)_t2295;
            ;
            ;
            Bool _t2296 = Bool_and(_t2294, _t2295);
            (void)_t2296;
            ;
            ;
            if (_t2296) {
                U64 _t2274 = 1;
                (void)_t2274;
                U64 *_t2275 = malloc(sizeof(U64)); *_t2275 = U64_add(DEREF(path_idx), _t2274);
                (void)_t2275;
                ;
                Str *oval = Array_get(args, _t2275);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t2275, &(Bool){1});
                U64 _t2276 = 2;
                (void)_t2276;
                U64 _t2277 = U64_add(DEREF(path_idx), _t2276);
                (void)_t2277;
                ;
                *path_idx = _t2277;
                ;
            } else {
                Str *_t2282 = Str_lit("-c", 2ULL);
                (void)_t2282;
                U64 _t2283 = 1;
                (void)_t2283;
                U64 _t2284 = U64_add(DEREF(path_idx), _t2283);
                (void)_t2284;
                ;
                U64 _t2285; { U64 *_hp = (U64 *)Array_len(args); _t2285 = *_hp; free(_hp); }
                (void)_t2285;
                Bool _t2286; { Bool *_hp = (Bool *)Str_eq(flag, _t2282); _t2286 = *_hp; free(_hp); }
                (void)_t2286;
                Str_delete(_t2282, &(Bool){1});
                Bool _t2287; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2284}, &(U64){_t2285}); _t2287 = *_hp; free(_hp); }
                (void)_t2287;
                ;
                ;
                Bool _t2288 = Bool_and(_t2286, _t2287);
                (void)_t2288;
                ;
                ;
                if (_t2288) {
                    U64 _t2278 = 1;
                    (void)_t2278;
                    U64 *_t2279 = malloc(sizeof(U64)); *_t2279 = U64_add(DEREF(path_idx), _t2278);
                    (void)_t2279;
                    ;
                    Str *cval = Array_get(args, _t2279);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t2279, &(Bool){1});
                    U64 _t2280 = 2;
                    (void)_t2280;
                    U64 _t2281 = U64_add(DEREF(path_idx), _t2280);
                    (void)_t2281;
                    ;
                    *path_idx = _t2281;
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
    Str *_t2646 = Str_lit("help", 4ULL);
    (void)_t2646;
    Str *_t2647 = Str_lit("--help", 6ULL);
    (void)_t2647;
    Bool _t2648; { Bool *_hp = (Bool *)Str_eq(command, _t2646); _t2648 = *_hp; free(_hp); }
    (void)_t2648;
    Str_delete(_t2646, &(Bool){1});
    Bool _t2649; { Bool *_hp = (Bool *)Str_eq(command, _t2647); _t2649 = *_hp; free(_hp); }
    (void)_t2649;
    Str_delete(_t2647, &(Bool){1});
    Bool _t2650 = Bool_or(_t2648, _t2649);
    (void)_t2650;
    ;
    ;
    if (_t2650) {
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
    Str *_t2651 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t2651;
    Str *core_path = Str_concat(bin_dir, _t2651);
    (void)core_path;
    Str_delete(_t2651, &(Bool){1});
    Str *_t2652 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t2652;
    Str *ext_c_path = Str_concat(bin_dir, _t2652);
    (void)ext_c_path;
    Str_delete(_t2652, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t2653; { U64 *_hp = (U64 *)Str_len(abs_path); _t2653 = *_hp; free(_hp); }
    (void)_t2653;
    U64 _t2654 = 0;
    (void)_t2654;
    Bool _t2655; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2653}, &(U64){_t2654}); _t2655 = *_hp; free(_hp); }
    (void)_t2655;
    ;
    ;
    if (_t2655) {
        U64 _t2305; { U64 *_hp = (U64 *)Str_len(abs_path); _t2305 = *_hp; free(_hp); }
        (void)_t2305;
        U64 _t2306 = 1;
        (void)_t2306;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2305, _t2306);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t2298 = 0;
            (void)_t2298;
            U8 *_t2299 = Str_get(abs_path, last_slash);
            (void)_t2299;
            U8 _t2300 = 47;
            (void)_t2300;
            Bool _t2301; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2298}); _t2301 = *_hp; free(_hp); }
            (void)_t2301;
            ;
            Bool _t2302; { Bool *_hp = (Bool *)U8_neq(_t2299, &(U8){_t2300}); _t2302 = *_hp; free(_hp); }
            (void)_t2302;
            ;
            Bool _wcond2297 = Bool_and(_t2301, _t2302);
            (void)_wcond2297;
            ;
            ;
            if (_wcond2297) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2303 = 1;
            (void)_t2303;
            U64 _t2304 = U64_sub(DEREF(last_slash), _t2303);
            (void)_t2304;
            ;
            *last_slash = _t2304;
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
    U64 _t2656; { U64 *_hp = (U64 *)Str_len(core_abs); _t2656 = *_hp; free(_hp); }
    (void)_t2656;
    U64 _t2657 = 0;
    (void)_t2657;
    Bool _t2658; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2656}, &(U64){_t2657}); _t2658 = *_hp; free(_hp); }
    (void)_t2658;
    ;
    ;
    if (_t2658) {
        Bool _t2308 = til_set_has(resolved, core_abs);
        (void)_t2308;
        if (_t2308) {
            Bool _t2307 = 1;
            (void)_t2307;
            skip_core = _t2307;
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
    U64 _t2659; { U64 *_hp = (U64 *)Vec_len(core_imports); _t2659 = *_hp; free(_hp); }
    (void)_t2659;
    U64 _t2660 = 0;
    (void)_t2660;
    Bool _t2661; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2659}, &(U64){_t2660}); _t2661 = *_hp; free(_hp); }
    (void)_t2661;
    ;
    ;
    Bool _t2662 = Bool_not(skip_core);
    (void)_t2662;
    Bool _t2663 = Bool_and(_t2661, _t2662);
    (void)_t2663;
    ;
    ;
    if (_t2663) {
        Str *_t2315 = Str_lit("/src/core", 9ULL);
        (void)_t2315;
        Str *core_dir = Str_concat(bin_dir, _t2315);
        (void)core_dir;
        Str_delete(_t2315, &(Bool){1});
        Str *_t2316 = Str_lit("", 0ULL);
        (void)_t2316;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t2316); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t2316, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t2317 = 0;
        (void)_t2317;
        Bool _t2318; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2317}); _t2318 = *_hp; free(_hp); }
        (void)_t2318;
        ;
        ;
        if (_t2318) {
            Str *_t2309 = Str_lit("Str", 3ULL);
            (void)_t2309;
            U64 _t2310; { U64 *_hp = (U64 *)Str_size(); _t2310 = *_hp; free(_hp); }
            (void)_t2310;
            U64 _t2311 = 1;
            (void)_t2311;
            Array *_va61 = Array_new(_t2309, &(U64){_t2310}, &(U64){_t2311});
            (void)_va61;
            Str_delete(_t2309, &(Bool){1});
            ;
            ;
            U64 _t2312 = 0;
            (void)_t2312;
            Str *_t2313 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t2313;
            Array_set(_va61, &(U64){_t2312}, _t2313);
            ;
            Str *_t2314 = Str_lit("src/til.til:304:19", 18ULL);
            (void)_t2314;
            panic(_t2314, _va61);
            Str_delete(_t2314, &(Bool){1});
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
    Str *_t2664 = Str_lit("script", 6ULL);
    (void)_t2664;
    Mode *cur_mode = mode_resolve(_t2664);
    (void)cur_mode;
    Str_delete(_t2664, &(Bool){1});
    U64 _t2665; { U64 *_hp = (U64 *)Str_len(mode_str); _t2665 = *_hp; free(_hp); }
    (void)_t2665;
    U64 _t2666 = 0;
    (void)_t2666;
    Bool _t2667; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2665}, &(U64){_t2666}); _t2667 = *_hp; free(_hp); }
    (void)_t2667;
    ;
    ;
    if (_t2667) {
        cur_mode = mode_resolve(mode_str);
        U64 _t2328; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t2328 = *_hp; free(_hp); }
        (void)_t2328;
        U64 _t2329 = 0;
        (void)_t2329;
        Bool _t2330 = U64_eq(_t2328, _t2329);
        (void)_t2330;
        ;
        ;
        if (_t2330) {
            Str *_t2319 = Str_lit("Str", 3ULL);
            (void)_t2319;
            U64 _t2320; { U64 *_hp = (U64 *)Str_size(); _t2320 = *_hp; free(_hp); }
            (void)_t2320;
            U64 _t2321 = 1;
            (void)_t2321;
            Array *_va62 = Array_new(_t2319, &(U64){_t2320}, &(U64){_t2321});
            (void)_va62;
            Str_delete(_t2319, &(Bool){1});
            ;
            ;
            Str *_t2322 = Str_lit("unknown mode '", 14ULL);
            (void)_t2322;
            Str *_t2323 = Str_concat(_t2322, mode_str);
            (void)_t2323;
            Str_delete(_t2322, &(Bool){1});
            Str *_t2324 = Str_lit("'", 1ULL);
            (void)_t2324;
            U64 _t2325 = 0;
            (void)_t2325;
            Str *_t2326 = Str_concat(_t2323, _t2324);
            (void)_t2326;
            Str_delete(_t2323, &(Bool){1});
            Str_delete(_t2324, &(Bool){1});
            Array_set(_va62, &(U64){_t2325}, _t2326);
            ;
            Str *_t2327 = Str_lit("src/til.til:320:19", 18ULL);
            (void)_t2327;
            panic(_t2327, _va62);
            Str_delete(_t2327, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t2668; { U64 *_hp = (U64 *)Vec_len(imports); _t2668 = *_hp; free(_hp); }
    (void)_t2668;
    U64 _t2669 = 0;
    (void)_t2669;
    Bool _t2670; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2668}, &(U64){_t2669}); _t2670 = *_hp; free(_hp); }
    (void)_t2670;
    ;
    ;
    if (_t2670) {
        Str *_t2337 = Str_lit("/src/lib", 8ULL);
        (void)_t2337;
        Str *lib_dir = Str_concat(bin_dir, _t2337);
        (void)lib_dir;
        Str_delete(_t2337, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t2338 = 0;
        (void)_t2338;
        Bool _t2339; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2338}); _t2339 = *_hp; free(_hp); }
        (void)_t2339;
        ;
        ;
        if (_t2339) {
            Str *_t2331 = Str_lit("Str", 3ULL);
            (void)_t2331;
            U64 _t2332; { U64 *_hp = (U64 *)Str_size(); _t2332 = *_hp; free(_hp); }
            (void)_t2332;
            U64 _t2333 = 1;
            (void)_t2333;
            Array *_va63 = Array_new(_t2331, &(U64){_t2332}, &(U64){_t2333});
            (void)_va63;
            Str_delete(_t2331, &(Bool){1});
            ;
            ;
            U64 _t2334 = 0;
            (void)_t2334;
            Str *_t2335 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t2335;
            Array_set(_va63, &(U64){_t2334}, _t2335);
            ;
            Str *_t2336 = Str_lit("src/til.til:334:19", 18ULL);
            (void)_t2336;
            panic(_t2336, _va63);
            Str_delete(_t2336, &(Bool){1});
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
    Bool _t2671 = Bool_not(skip_core);
    (void)_t2671;
    ;
    if (_t2671) {
        while (1) {
            U32 _t2341 = expr_nchildren(core_ast);
            (void)_t2341;
            Bool _wcond2340; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2341}); _wcond2340 = *_hp; free(_hp); }
            (void)_wcond2340;
            ;
            if (_wcond2340) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2342 = 1;
            (void)_t2342;
            U32 _t2343 = U32_add(DEREF(i), _t2342);
            (void)_t2343;
            ;
            *i = _t2343;
            ;
        }
        U32 _t2348 = 0;
        (void)_t2348;
        *i = _t2348;
        ;
        while (1) {
            U32 _t2345 = expr_vec_count(core_import_decls);
            (void)_t2345;
            Bool _wcond2344; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2345}); _wcond2344 = *_hp; free(_hp); }
            (void)_wcond2344;
            ;
            if (_wcond2344) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2346 = 1;
            (void)_t2346;
            U32 _t2347 = U32_add(DEREF(i), _t2346);
            (void)_t2347;
            ;
            *i = _t2347;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t2672; { U64 *_hp = (U64 *)Str_len(auto_import); _t2672 = *_hp; free(_hp); }
    (void)_t2672;
    U64 _t2673 = 0;
    (void)_t2673;
    Bool _t2674; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2672}, &(U64){_t2673}); _t2674 = *_hp; free(_hp); }
    (void)_t2674;
    ;
    ;
    if (_t2674) {
        Str *_t2353 = Str_lit("/src/modes/", 11ULL);
        (void)_t2353;
        Str *_t2354 = Str_concat(bin_dir, _t2353);
        (void)_t2354;
        Str_delete(_t2353, &(Bool){1});
        Str *_t2355 = Str_concat(_t2354, auto_import);
        (void)_t2355;
        Str_delete(_t2354, &(Bool){1});
        Str *_t2356 = Str_lit(".til", 4ULL);
        (void)_t2356;
        Str *mode_til_path = Str_concat(_t2355, _t2356);
        (void)mode_til_path;
        Str_delete(_t2355, &(Bool){1});
        Str_delete(_t2356, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t2357 = 0;
        (void)_t2357;
        *i = _t2357;
        ;
        while (1) {
            U32 _t2350 = expr_nchildren(mode_ast);
            (void)_t2350;
            Bool _wcond2349; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2350}); _wcond2349 = *_hp; free(_hp); }
            (void)_wcond2349;
            ;
            if (_wcond2349) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t2351 = 1;
            (void)_t2351;
            U32 _t2352 = U32_add(DEREF(i), _t2351);
            (void)_t2352;
            ;
            *i = _t2352;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t2675 = 0;
    (void)_t2675;
    *i = _t2675;
    ;
    while (1) {
        U32 _t2359 = expr_vec_count(import_decls);
        (void)_t2359;
        Bool _wcond2358; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2359}); _wcond2358 = *_hp; free(_hp); }
        (void)_wcond2358;
        ;
        if (_wcond2358) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2360 = 1;
        (void)_t2360;
        U32 _t2361 = U32_add(DEREF(i), _t2360);
        (void)_t2361;
        ;
        *i = _t2361;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t2676 = 0;
    (void)_t2676;
    *i = _t2676;
    ;
    while (1) {
        U32 _t2363 = expr_nchildren(ast);
        (void)_t2363;
        Bool _wcond2362; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2363}); _wcond2362 = *_hp; free(_hp); }
        (void)_wcond2362;
        ;
        if (_wcond2362) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2364 = 1;
        (void)_t2364;
        U32 _t2365 = U32_add(DEREF(i), _t2364);
        (void)_t2365;
        ;
        *i = _t2365;
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
    U32 _t2677 = 0;
    (void)_t2677;
    *i = _t2677;
    ;
    while (1) {
        U32 _t2381 = expr_nchildren(ast);
        (void)_t2381;
        Bool _wcond2366; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2381}); _wcond2366 = *_hp; free(_hp); }
        (void)_wcond2366;
        ;
        if (_wcond2366) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t2382 = expr_get_tag(stmt);
        (void)_t2382;
        U32 _t2383 = expr_nchildren(stmt);
        (void)_t2383;
        U32 _t2384 = 2;
        (void)_t2384;
        Bool _t2385 = I32_eq(_t2382, DEREF(NODE_FCALL));
        (void)_t2385;
        ;
        Bool _t2386 = U32_eq(_t2383, _t2384);
        (void)_t2386;
        ;
        ;
        U32 *_t2387 = malloc(sizeof(U32));
        *_t2387 = 0;
        (void)_t2387;
        Expr *_t2388 = expr_get_child(stmt, DEREF(_t2387));
        (void)_t2388;
        I32 _t2389 = expr_get_tag(_t2388);
        (void)_t2389;
        U32_delete(_t2387, &(Bool){1});
        Bool _t2390 = Bool_and(_t2385, _t2386);
        (void)_t2390;
        ;
        ;
        Bool _t2391 = I32_eq(_t2389, DEREF(NODE_IDENT));
        (void)_t2391;
        ;
        U32 *_t2392 = malloc(sizeof(U32));
        *_t2392 = 1;
        (void)_t2392;
        Expr *_t2393 = expr_get_child(stmt, DEREF(_t2392));
        (void)_t2393;
        I32 _t2394 = expr_get_tag(_t2393);
        (void)_t2394;
        U32_delete(_t2392, &(Bool){1});
        Bool _t2395 = Bool_and(_t2390, _t2391);
        (void)_t2395;
        ;
        ;
        Bool _t2396 = I32_eq(_t2394, DEREF(NODE_LITERAL_STR));
        (void)_t2396;
        ;
        Bool _t2397 = Bool_and(_t2395, _t2396);
        (void)_t2397;
        ;
        ;
        if (_t2397) {
            U32 *_t2375 = malloc(sizeof(U32));
            *_t2375 = 0;
            (void)_t2375;
            Expr *_t2376 = expr_get_child(stmt, DEREF(_t2375));
            (void)_t2376;
            Str *fname = expr_get_str_val(_t2376);
            (void)fname;
            U32 *_t2377 = malloc(sizeof(U32));
            *_t2377 = 1;
            (void)_t2377;
            Expr *_t2378 = expr_get_child(stmt, DEREF(_t2377));
            (void)_t2378;
            Str *arg = expr_get_str_val(_t2378);
            (void)arg;
            Str *_t2379 = Str_lit("link", 4ULL);
            (void)_t2379;
            Bool _t2380; { Bool *_hp = (Bool *)Str_eq(fname, _t2379); _t2380 = *_hp; free(_hp); }
            (void)_t2380;
            Str_delete(_t2379, &(Bool){1});
            if (_t2380) {
                Str *_t2367 = Str_lit(" -l", 3ULL);
                (void)_t2367;
                Str *_t2368 = Str_concat(link_flags, _t2367);
                (void)_t2368;
                Str_delete(_t2367, &(Bool){1});
                link_flags = Str_concat(_t2368, arg);
                Str_delete(_t2368, &(Bool){1});
            } else {
                Str *_t2373 = Str_lit("link_c", 6ULL);
                (void)_t2373;
                Bool _t2374; { Bool *_hp = (Bool *)Str_eq(fname, _t2373); _t2374 = *_hp; free(_hp); }
                (void)_t2374;
                Str_delete(_t2373, &(Bool){1});
                if (_t2374) {
                    U64 _t2370; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2370 = *_hp; free(_hp); }
                    (void)_t2370;
                    U64 _t2371 = 0;
                    (void)_t2371;
                    Bool _t2372; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2370}, &(U64){_t2371}); _t2372 = *_hp; free(_hp); }
                    (void)_t2372;
                    ;
                    ;
                    if (_t2372) {
                        Str *_t2369 = Str_lit(" ", 1ULL);
                        (void)_t2369;
                        link_c_paths = Str_concat(link_c_paths, _t2369);
                        Str_delete(_t2369, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t2375, &(Bool){1});
            U32_delete(_t2377, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2398 = 1;
        (void)_t2398;
        U32 _t2399 = U32_add(DEREF(i), _t2398);
        (void)_t2399;
        ;
        *i = _t2399;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t2678 = init_declarations(ast, scope);
    (void)_t2678;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t2679 = 0;
    (void)_t2679;
    Bool _t2680; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t2679}); _t2680 = *_hp; free(_hp); }
    (void)_t2680;
    ;
    if (_t2680) {
        Str *_t2400 = Str_lit("Str", 3ULL);
        (void)_t2400;
        U64 _t2401; { U64 *_hp = (U64 *)Str_size(); _t2401 = *_hp; free(_hp); }
        (void)_t2401;
        U64 _t2402 = 1;
        (void)_t2402;
        Array *_va64 = Array_new(_t2400, &(U64){_t2401}, &(U64){_t2402});
        (void)_va64;
        Str_delete(_t2400, &(Bool){1});
        ;
        ;
        Str *_t2403 = I32_to_str(&(I32){type_errors});
        (void)_t2403;
        Str *_t2404 = Str_lit(" type error(s) found", 20ULL);
        (void)_t2404;
        U64 _t2405 = 0;
        (void)_t2405;
        Str *_t2406 = Str_concat(_t2403, _t2404);
        (void)_t2406;
        Str_delete(_t2403, &(Bool){1});
        Str_delete(_t2404, &(Bool){1});
        Array_set(_va64, &(U64){_t2405}, _t2406);
        ;
        Str *_t2407 = Str_lit("src/til.til:429:15", 18ULL);
        (void)_t2407;
        panic(_t2407, _va64);
        Str_delete(_t2407, &(Bool){1});
    }
    ;
    ;
    Str *_t2681 = Str_lit("test", 4ULL);
    (void)_t2681;
    Str *_t2682 = Str_lit("test", 4ULL);
    (void)_t2682;
    Bool _t2683; { Bool *_hp = (Bool *)Str_eq(command, _t2681); _t2683 = *_hp; free(_hp); }
    (void)_t2683;
    Str_delete(_t2681, &(Bool){1});
    Bool _t2684; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2682); _t2684 = *_hp; free(_hp); }
    (void)_t2684;
    Str_delete(_t2682, &(Bool){1});
    Str *_t2685 = Str_lit("pure", 4ULL);
    (void)_t2685;
    Bool _t2686 = Bool_or(_t2683, _t2684);
    (void)_t2686;
    ;
    ;
    Bool _t2687; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2685); _t2687 = *_hp; free(_hp); }
    (void)_t2687;
    Str_delete(_t2685, &(Bool){1});
    Str *_t2688 = Str_lit("pura", 4ULL);
    (void)_t2688;
    Bool _t2689 = Bool_or(_t2686, _t2687);
    (void)_t2689;
    ;
    ;
    Bool _t2690; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2688); _t2690 = *_hp; free(_hp); }
    (void)_t2690;
    Str_delete(_t2688, &(Bool){1});
    Bool run_tests = Bool_or(_t2689, _t2690);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t2691 = Str_lit("translate", 9ULL);
    (void)_t2691;
    Str *_t2692 = Str_lit("build", 5ULL);
    (void)_t2692;
    Bool _t2693; { Bool *_hp = (Bool *)Str_eq(command, _t2691); _t2693 = *_hp; free(_hp); }
    (void)_t2693;
    Str_delete(_t2691, &(Bool){1});
    Bool _t2694; { Bool *_hp = (Bool *)Str_eq(command, _t2692); _t2694 = *_hp; free(_hp); }
    (void)_t2694;
    Str_delete(_t2692, &(Bool){1});
    Bool _t2695; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2695 = *_hp; free(_hp); }
    (void)_t2695;
    Bool _t2696 = Bool_or(_t2693, _t2694);
    (void)_t2696;
    ;
    ;
    Bool is_lib_target = Bool_and(_t2695, _t2696);
    (void)is_lib_target;
    ;
    ;
    U64 _t2697; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2697 = *_hp; free(_hp); }
    (void)_t2697;
    U64 _t2698 = 0;
    (void)_t2698;
    Bool _t2699 = Bool_not(is_lib_target);
    (void)_t2699;
    ;
    Bool _t2700 = U64_eq(_t2697, _t2698);
    (void)_t2700;
    ;
    ;
    Bool _t2701 = Bool_and(_t2699, _t2700);
    (void)_t2701;
    ;
    ;
    if (_t2701) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t2702; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2702 = *_hp; free(_hp); }
    (void)_t2702;
    U64 _t2703 = 0;
    (void)_t2703;
    Bool _t2704; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2702}, &(U64){_t2703}); _t2704 = *_hp; free(_hp); }
    (void)_t2704;
    ;
    ;
    if (_t2704) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t2705 = Str_lit("Str", 3ULL);
    (void)_t2705;
    U64 _t2706; { U64 *_hp = (U64 *)Str_size(); _t2706 = *_hp; free(_hp); }
    (void)_t2706;
    Vec *user_argv = Vec_new(_t2705, &(U64){_t2706});
    (void)user_argv;
    Str_delete(_t2705, &(Bool){1});
    ;
    U64 _t2707 = 1;
    (void)_t2707;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t2707);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t2424; { U64 *_hp = (U64 *)Array_len(args); _t2424 = *_hp; free(_hp); }
        (void)_t2424;
        Bool _wcond2408; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t2424}); _wcond2408 = *_hp; free(_hp); }
        (void)_wcond2408;
        ;
        if (_wcond2408) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t2425 = Str_lit("-l", 2ULL);
        (void)_t2425;
        Bool _t2426; { Bool *_hp = (Bool *)Str_starts_with(arg, _t2425); _t2426 = *_hp; free(_hp); }
        (void)_t2426;
        Str_delete(_t2425, &(Bool){1});
        if (_t2426) {
            U64 _t2411 = 2;
            (void)_t2411;
            U64 _t2412; { U64 *_hp = (U64 *)Str_len(arg); _t2412 = *_hp; free(_hp); }
            (void)_t2412;
            Str *lib = Str_substr(arg, &(U64){_t2411}, &(U64){_t2412});
            (void)lib;
            ;
            ;
            U64 _t2413; { U64 *_hp = (U64 *)Str_len(lib); _t2413 = *_hp; free(_hp); }
            (void)_t2413;
            U64 _t2414 = 0;
            (void)_t2414;
            U64 _t2415 = 1;
            (void)_t2415;
            U64 _t2416 = U64_add(DEREF(ai), _t2415);
            (void)_t2416;
            ;
            U64 _t2417; { U64 *_hp = (U64 *)Array_len(args); _t2417 = *_hp; free(_hp); }
            (void)_t2417;
            Bool _t2418 = U64_eq(_t2413, _t2414);
            (void)_t2418;
            ;
            ;
            Bool _t2419; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2416}, &(U64){_t2417}); _t2419 = *_hp; free(_hp); }
            (void)_t2419;
            ;
            ;
            Bool _t2420 = Bool_and(_t2418, _t2419);
            (void)_t2420;
            ;
            ;
            if (_t2420) {
                U64 _t2409 = 1;
                (void)_t2409;
                U64 _t2410 = U64_add(DEREF(ai), _t2409);
                (void)_t2410;
                ;
                *ai = _t2410;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t2421 = Str_lit(" -l", 3ULL);
            (void)_t2421;
            Str *_t2422 = Str_concat(link_flags, _t2421);
            (void)_t2422;
            Str_delete(_t2421, &(Bool){1});
            link_flags = Str_concat(_t2422, lib);
            Str_delete(_t2422, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t2423 = Str_clone(arg);
            (void)_t2423;
            Vec_push(user_argv, _t2423);
        }
        ;
        U64 _t2427 = 1;
        (void)_t2427;
        U64 _t2428 = U64_add(DEREF(ai), _t2427);
        (void)_t2428;
        ;
        *ai = _t2428;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t2708; { U64 *_hp = (U64 *)Str_len(link_flags); _t2708 = *_hp; free(_hp); }
    (void)_t2708;
    U64 _t2709 = 0;
    (void)_t2709;
    Bool _t2710; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2708}, &(U64){_t2709}); _t2710 = *_hp; free(_hp); }
    (void)_t2710;
    ;
    ;
    if (_t2710) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t2711 = Str_lit("interpret", 9ULL);
    (void)_t2711;
    Str *_t2712 = Str_lit("test", 4ULL);
    (void)_t2712;
    Bool _t2713; { Bool *_hp = (Bool *)Str_eq(command, _t2711); _t2713 = *_hp; free(_hp); }
    (void)_t2713;
    Str_delete(_t2711, &(Bool){1});
    Bool _t2714; { Bool *_hp = (Bool *)Str_eq(command, _t2712); _t2714 = *_hp; free(_hp); }
    (void)_t2714;
    Str_delete(_t2712, &(Bool){1});
    Bool _t2715 = Bool_or(_t2713, _t2714);
    (void)_t2715;
    ;
    ;
    if (_t2715) {
        Str *_t2435 = Str_lit("interpret", 9ULL);
        (void)_t2435;
        Bool _t2436; { Bool *_hp = (Bool *)Str_eq(command, _t2435); _t2436 = *_hp; free(_hp); }
        (void)_t2436;
        Str_delete(_t2435, &(Bool){1});
        Bool _t2437 = Bool_and(is_lib_mode, _t2436);
        (void)_t2437;
        ;
        if (_t2437) {
            Str *_t2429 = Str_lit("Str", 3ULL);
            (void)_t2429;
            U64 _t2430; { U64 *_hp = (U64 *)Str_size(); _t2430 = *_hp; free(_hp); }
            (void)_t2430;
            U64 _t2431 = 1;
            (void)_t2431;
            Array *_va65 = Array_new(_t2429, &(U64){_t2430}, &(U64){_t2431});
            (void)_va65;
            Str_delete(_t2429, &(Bool){1});
            ;
            ;
            U64 _t2432 = 0;
            (void)_t2432;
            Str *_t2433 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t2433;
            Array_set(_va65, &(U64){_t2432}, _t2433);
            ;
            Str *_t2434 = Str_lit("src/til.til:483:19", 18ULL);
            (void)_t2434;
            panic(_t2434, _va65);
            Str_delete(_t2434, &(Bool){1});
        }
        ;
        I32 _t2438 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t2438;
        result = _t2438;
        ;
    } else {
        Str *_t2631 = Str_lit("translate", 9ULL);
        (void)_t2631;
        Str *_t2632 = Str_lit("build", 5ULL);
        (void)_t2632;
        Bool _t2633; { Bool *_hp = (Bool *)Str_eq(command, _t2631); _t2633 = *_hp; free(_hp); }
        (void)_t2633;
        Str_delete(_t2631, &(Bool){1});
        Bool _t2634; { Bool *_hp = (Bool *)Str_eq(command, _t2632); _t2634 = *_hp; free(_hp); }
        (void)_t2634;
        Str_delete(_t2632, &(Bool){1});
        Str *_t2635 = Str_lit("run", 3ULL);
        (void)_t2635;
        Bool _t2636 = Bool_or(_t2633, _t2634);
        (void)_t2636;
        ;
        ;
        Bool _t2637; { Bool *_hp = (Bool *)Str_eq(command, _t2635); _t2637 = *_hp; free(_hp); }
        (void)_t2637;
        Str_delete(_t2635, &(Bool){1});
        Bool _t2638 = Bool_or(_t2636, _t2637);
        (void)_t2638;
        ;
        ;
        if (_t2638) {
            Str *_t2564 = Str_lit("run", 3ULL);
            (void)_t2564;
            Bool _t2565; { Bool *_hp = (Bool *)Str_eq(command, _t2564); _t2565 = *_hp; free(_hp); }
            (void)_t2565;
            Str_delete(_t2564, &(Bool){1});
            Bool _t2566 = Bool_and(is_lib_mode, _t2565);
            (void)_t2566;
            ;
            if (_t2566) {
                Str *_t2439 = Str_lit("Str", 3ULL);
                (void)_t2439;
                U64 _t2440; { U64 *_hp = (U64 *)Str_size(); _t2440 = *_hp; free(_hp); }
                (void)_t2440;
                U64 _t2441 = 1;
                (void)_t2441;
                Array *_va66 = Array_new(_t2439, &(U64){_t2440}, &(U64){_t2441});
                (void)_va66;
                Str_delete(_t2439, &(Bool){1});
                ;
                ;
                U64 _t2442 = 0;
                (void)_t2442;
                Str *_t2443 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t2443;
                Array_set(_va66, &(U64){_t2442}, _t2443);
                ;
                Str *_t2444 = Str_lit("src/til.til:489:19", 18ULL);
                (void)_t2444;
                panic(_t2444, _va66);
                Str_delete(_t2444, &(Bool){1});
            }
            ;
            Str *_t2567 = Str_lit("/", 1ULL);
            (void)_t2567;
            I64 *last_slash = Str_rfind(path, _t2567);
            (void)last_slash;
            Str_delete(_t2567, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t2568 = 0;
            (void)_t2568;
            Bool _t2569; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t2568}); _t2569 = *_hp; free(_hp); }
            (void)_t2569;
            ;
            if (_t2569) {
                I64 _t2445 = 1;
                (void)_t2445;
                I64 _t2446 = I64_add(DEREF(last_slash), _t2445);
                (void)_t2446;
                ;
                U64 _t2447; { U64 *_hp = (U64 *)Str_len(path); _t2447 = *_hp; free(_hp); }
                (void)_t2447;
                U64 _t2448 = I64_to_u64(DEREF(last_slash));
                (void)_t2448;
                U64 _t2449 = U64_sub(_t2447, _t2448);
                (void)_t2449;
                ;
                ;
                U64 _t2450 = 1;
                (void)_t2450;
                U64 _t2451 = I64_to_u64(_t2446);
                (void)_t2451;
                ;
                U64 _t2452 = U64_sub(_t2449, _t2450);
                (void)_t2452;
                ;
                ;
                basename = Str_substr(path, &(U64){_t2451}, &(U64){_t2452});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t2570 = Str_lit(".til", 4ULL);
            (void)_t2570;
            Bool _t2571; { Bool *_hp = (Bool *)Str_ends_with(basename, _t2570); _t2571 = *_hp; free(_hp); }
            (void)_t2571;
            Str_delete(_t2570, &(Bool){1});
            if (_t2571) {
                U64 _t2453 = 4;
                (void)_t2453;
                U64 _t2454 = U64_sub(name_len, _t2453);
                (void)_t2454;
                ;
                name_len = _t2454;
                ;
            }
            ;
            U64 _t2572 = 0;
            (void)_t2572;
            Str *name = Str_substr(basename, &(U64){_t2572}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t2573 = Str_lit("gen/til/", 8ULL);
            (void)_t2573;
            Str *_t2574 = Str_concat(_t2573, name);
            (void)_t2574;
            Str_delete(_t2573, &(Bool){1});
            Str *_t2575 = Str_lit(".c", 2ULL);
            (void)_t2575;
            Str *c_path = Str_concat(_t2574, _t2575);
            (void)c_path;
            Str_delete(_t2574, &(Bool){1});
            Str_delete(_t2575, &(Bool){1});
            U64 _t2576; { U64 *_hp = (U64 *)Str_len(custom_c); _t2576 = *_hp; free(_hp); }
            (void)_t2576;
            U64 _t2577 = 0;
            (void)_t2577;
            Bool _t2578; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2576}, &(U64){_t2577}); _t2578 = *_hp; free(_hp); }
            (void)_t2578;
            ;
            ;
            if (_t2578) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t2579 = Str_lit("bin/til/", 8ULL);
            (void)_t2579;
            Str *bin_path = Str_concat(_t2579, name);
            (void)bin_path;
            Str_delete(_t2579, &(Bool){1});
            U64 _t2580; { U64 *_hp = (U64 *)Str_len(custom_bin); _t2580 = *_hp; free(_hp); }
            (void)_t2580;
            U64 _t2581 = 0;
            (void)_t2581;
            Bool _t2582; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2580}, &(U64){_t2581}); _t2582 = *_hp; free(_hp); }
            (void)_t2582;
            ;
            ;
            if (_t2582) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t2583 = Str_lit("run", 3ULL);
            (void)_t2583;
            Bool _t2584; { Bool *_hp = (Bool *)Str_eq(command, _t2583); _t2584 = *_hp; free(_hp); }
            (void)_t2584;
            Str_delete(_t2583, &(Bool){1});
            Bool _t2585; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2585 = *_hp; free(_hp); }
            (void)_t2585;
            Bool _t2586 = Bool_not(_t2584);
            (void)_t2586;
            ;
            Bool do_lib = Bool_and(_t2585, _t2586);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t2455 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t2455;
                I32 _t2456 = til_system(_t2455);
                (void)_t2456;
                Str_delete(_t2455, &(Bool){1});
                ;
            } else {
                Str *_t2461 = Str_lit("/", 1ULL);
                (void)_t2461;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t2461); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t2461, &(Bool){1});
                Str *_t2462 = Str_lit("/", 1ULL);
                (void)_t2462;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t2462); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t2462, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t2463 = 0;
                (void)_t2463;
                Bool _t2464; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t2463}); _t2464 = *_hp; free(_hp); }
                (void)_t2464;
                ;
                if (_t2464) {
                    U64 _t2457 = 0;
                    (void)_t2457;
                    U64 _t2458 = I64_to_u64(cp_slash);
                    (void)_t2458;
                    cp_dir = Str_substr(c_path, &(U64){_t2457}, &(U64){_t2458});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t2465 = 0;
                (void)_t2465;
                Bool _t2466; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t2465}); _t2466 = *_hp; free(_hp); }
                (void)_t2466;
                ;
                if (_t2466) {
                    U64 _t2459 = 0;
                    (void)_t2459;
                    U64 _t2460 = I64_to_u64(bp_slash);
                    (void)_t2460;
                    bp_dir = Str_substr(bin_path, &(U64){_t2459}, &(U64){_t2460});
                    ;
                    ;
                }
                ;
                ;
                Str *_t2467 = Str_lit("mkdir -p ", 9ULL);
                (void)_t2467;
                Str *_t2468 = Str_concat(_t2467, cp_dir);
                (void)_t2468;
                Str_delete(_t2467, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t2469 = Str_lit(" ", 1ULL);
                (void)_t2469;
                Str *_t2470 = Str_concat(_t2468, _t2469);
                (void)_t2470;
                Str_delete(_t2468, &(Bool){1});
                Str_delete(_t2469, &(Bool){1});
                Str *_t2471 = Str_concat(_t2470, bp_dir);
                (void)_t2471;
                Str_delete(_t2470, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t2472 = til_system(_t2471);
                (void)_t2472;
                Str_delete(_t2471, &(Bool){1});
                ;
            }
            I32 _t2587 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t2587;
            result = _t2587;
            ;
            I32 _t2588 = 0;
            (void)_t2588;
            Bool _t2589 = I32_eq(result, _t2588);
            (void)_t2589;
            ;
            Bool _t2590 = Bool_and(_t2589, do_lib);
            (void)_t2590;
            ;
            if (_t2590) {
                Str *_t2529 = Str_lit("gen/til/", 8ULL);
                (void)_t2529;
                Str *_t2530 = Str_concat(_t2529, name);
                (void)_t2530;
                Str_delete(_t2529, &(Bool){1});
                Str *_t2531 = Str_lit(".h", 2ULL);
                (void)_t2531;
                Str *h_path = Str_concat(_t2530, _t2531);
                (void)h_path;
                Str_delete(_t2530, &(Bool){1});
                Str_delete(_t2531, &(Bool){1});
                Str *_t2532 = Str_lit("gen/til/", 8ULL);
                (void)_t2532;
                Str *_t2533 = Str_concat(_t2532, name);
                (void)_t2533;
                Str_delete(_t2532, &(Bool){1});
                Str *_t2534 = Str_lit(".til", 4ULL);
                (void)_t2534;
                Str *til_path = Str_concat(_t2533, _t2534);
                (void)til_path;
                Str_delete(_t2533, &(Bool){1});
                Str_delete(_t2534, &(Bool){1});
                I32 _t2535 = build_header(ast, h_path);
                (void)_t2535;
                result = _t2535;
                ;
                I32 _t2536 = 0;
                (void)_t2536;
                Bool _t2537 = I32_eq(result, _t2536);
                (void)_t2537;
                ;
                if (_t2537) {
                    I32 _t2473 = build_til_binding(ast, til_path, name);
                    (void)_t2473;
                    result = _t2473;
                    ;
                }
                ;
                I32 _t2538 = 0;
                (void)_t2538;
                Str *_t2539 = Str_lit("translate", 9ULL);
                (void)_t2539;
                Bool _t2540 = I32_eq(result, _t2538);
                (void)_t2540;
                ;
                Bool _t2541; { Bool *_hp = (Bool *)Str_eq(command, _t2539); _t2541 = *_hp; free(_hp); }
                (void)_t2541;
                Str_delete(_t2539, &(Bool){1});
                Bool _t2542 = Bool_and(_t2540, _t2541);
                (void)_t2542;
                ;
                ;
                if (_t2542) {
                    Str *_t2474 = Str_lit("Str", 3ULL);
                    (void)_t2474;
                    U64 _t2475; { U64 *_hp = (U64 *)Str_size(); _t2475 = *_hp; free(_hp); }
                    (void)_t2475;
                    U64 _t2476 = 1;
                    (void)_t2476;
                    Array *_va67 = Array_new(_t2474, &(U64){_t2475}, &(U64){_t2476});
                    (void)_va67;
                    Str_delete(_t2474, &(Bool){1});
                    ;
                    ;
                    Str *_t2477 = Str_lit("Generated: ", 11ULL);
                    (void)_t2477;
                    U64 _t2478 = 0;
                    (void)_t2478;
                    Str *_t2479 = Str_concat(_t2477, c_path);
                    (void)_t2479;
                    Str_delete(_t2477, &(Bool){1});
                    Array_set(_va67, &(U64){_t2478}, _t2479);
                    ;
                    println(_va67);
                    Str *_t2480 = Str_lit("Str", 3ULL);
                    (void)_t2480;
                    U64 _t2481; { U64 *_hp = (U64 *)Str_size(); _t2481 = *_hp; free(_hp); }
                    (void)_t2481;
                    U64 _t2482 = 1;
                    (void)_t2482;
                    Array *_va68 = Array_new(_t2480, &(U64){_t2481}, &(U64){_t2482});
                    (void)_va68;
                    Str_delete(_t2480, &(Bool){1});
                    ;
                    ;
                    Str *_t2483 = Str_lit("Generated: ", 11ULL);
                    (void)_t2483;
                    U64 _t2484 = 0;
                    (void)_t2484;
                    Str *_t2485 = Str_concat(_t2483, h_path);
                    (void)_t2485;
                    Str_delete(_t2483, &(Bool){1});
                    Array_set(_va68, &(U64){_t2484}, _t2485);
                    ;
                    println(_va68);
                    Str *_t2486 = Str_lit("Str", 3ULL);
                    (void)_t2486;
                    U64 _t2487; { U64 *_hp = (U64 *)Str_size(); _t2487 = *_hp; free(_hp); }
                    (void)_t2487;
                    U64 _t2488 = 1;
                    (void)_t2488;
                    Array *_va69 = Array_new(_t2486, &(U64){_t2487}, &(U64){_t2488});
                    (void)_va69;
                    Str_delete(_t2486, &(Bool){1});
                    ;
                    ;
                    Str *_t2489 = Str_lit("Generated: ", 11ULL);
                    (void)_t2489;
                    U64 _t2490 = 0;
                    (void)_t2490;
                    Str *_t2491 = Str_concat(_t2489, til_path);
                    (void)_t2491;
                    Str_delete(_t2489, &(Bool){1});
                    Array_set(_va69, &(U64){_t2490}, _t2491);
                    ;
                    println(_va69);
                }
                ;
                I32 _t2543 = 0;
                (void)_t2543;
                Str *_t2544 = Str_lit("build", 5ULL);
                (void)_t2544;
                Bool _t2545 = I32_eq(result, _t2543);
                (void)_t2545;
                ;
                Bool _t2546; { Bool *_hp = (Bool *)Str_eq(command, _t2544); _t2546 = *_hp; free(_hp); }
                (void)_t2546;
                Str_delete(_t2544, &(Bool){1});
                Bool _t2547 = Bool_and(_t2545, _t2546);
                (void)_t2547;
                ;
                ;
                if (_t2547) {
                    I32 _t2526 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t2526;
                    result = _t2526;
                    ;
                    I32 _t2527 = 0;
                    (void)_t2527;
                    Bool _t2528 = I32_eq(result, _t2527);
                    (void)_t2528;
                    ;
                    if (_t2528) {
                        Str *_t2492 = Str_lit("Str", 3ULL);
                        (void)_t2492;
                        U64 _t2493; { U64 *_hp = (U64 *)Str_size(); _t2493 = *_hp; free(_hp); }
                        (void)_t2493;
                        U64 _t2494 = 1;
                        (void)_t2494;
                        Array *_va70 = Array_new(_t2492, &(U64){_t2493}, &(U64){_t2494});
                        (void)_va70;
                        Str_delete(_t2492, &(Bool){1});
                        ;
                        ;
                        Str *_t2495 = Str_lit("Generated: ", 11ULL);
                        (void)_t2495;
                        U64 _t2496 = 0;
                        (void)_t2496;
                        Str *_t2497 = Str_concat(_t2495, c_path);
                        (void)_t2497;
                        Str_delete(_t2495, &(Bool){1});
                        Array_set(_va70, &(U64){_t2496}, _t2497);
                        ;
                        println(_va70);
                        Str *_t2498 = Str_lit("Str", 3ULL);
                        (void)_t2498;
                        U64 _t2499; { U64 *_hp = (U64 *)Str_size(); _t2499 = *_hp; free(_hp); }
                        (void)_t2499;
                        U64 _t2500 = 1;
                        (void)_t2500;
                        Array *_va71 = Array_new(_t2498, &(U64){_t2499}, &(U64){_t2500});
                        (void)_va71;
                        Str_delete(_t2498, &(Bool){1});
                        ;
                        ;
                        Str *_t2501 = Str_lit("Generated: ", 11ULL);
                        (void)_t2501;
                        U64 _t2502 = 0;
                        (void)_t2502;
                        Str *_t2503 = Str_concat(_t2501, h_path);
                        (void)_t2503;
                        Str_delete(_t2501, &(Bool){1});
                        Array_set(_va71, &(U64){_t2502}, _t2503);
                        ;
                        println(_va71);
                        Str *_t2504 = Str_lit("Str", 3ULL);
                        (void)_t2504;
                        U64 _t2505; { U64 *_hp = (U64 *)Str_size(); _t2505 = *_hp; free(_hp); }
                        (void)_t2505;
                        U64 _t2506 = 1;
                        (void)_t2506;
                        Array *_va72 = Array_new(_t2504, &(U64){_t2505}, &(U64){_t2506});
                        (void)_va72;
                        Str_delete(_t2504, &(Bool){1});
                        ;
                        ;
                        Str *_t2507 = Str_lit("Generated: ", 11ULL);
                        (void)_t2507;
                        U64 _t2508 = 0;
                        (void)_t2508;
                        Str *_t2509 = Str_concat(_t2507, til_path);
                        (void)_t2509;
                        Str_delete(_t2507, &(Bool){1});
                        Array_set(_va72, &(U64){_t2508}, _t2509);
                        ;
                        println(_va72);
                        Str *_t2510 = Str_lit("Str", 3ULL);
                        (void)_t2510;
                        U64 _t2511; { U64 *_hp = (U64 *)Str_size(); _t2511 = *_hp; free(_hp); }
                        (void)_t2511;
                        U64 _t2512 = 1;
                        (void)_t2512;
                        Array *_va73 = Array_new(_t2510, &(U64){_t2511}, &(U64){_t2512});
                        (void)_va73;
                        Str_delete(_t2510, &(Bool){1});
                        ;
                        ;
                        Str *_t2513 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2513;
                        Str *_t2514 = Str_concat(_t2513, name);
                        (void)_t2514;
                        Str_delete(_t2513, &(Bool){1});
                        Str *_t2515 = Str_lit(".so", 3ULL);
                        (void)_t2515;
                        U64 _t2516 = 0;
                        (void)_t2516;
                        Str *_t2517 = Str_concat(_t2514, _t2515);
                        (void)_t2517;
                        Str_delete(_t2514, &(Bool){1});
                        Str_delete(_t2515, &(Bool){1});
                        Array_set(_va73, &(U64){_t2516}, _t2517);
                        ;
                        println(_va73);
                        Str *_t2518 = Str_lit("Str", 3ULL);
                        (void)_t2518;
                        U64 _t2519; { U64 *_hp = (U64 *)Str_size(); _t2519 = *_hp; free(_hp); }
                        (void)_t2519;
                        U64 _t2520 = 1;
                        (void)_t2520;
                        Array *_va74 = Array_new(_t2518, &(U64){_t2519}, &(U64){_t2520});
                        (void)_va74;
                        Str_delete(_t2518, &(Bool){1});
                        ;
                        ;
                        Str *_t2521 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2521;
                        Str *_t2522 = Str_concat(_t2521, name);
                        (void)_t2522;
                        Str_delete(_t2521, &(Bool){1});
                        Str *_t2523 = Str_lit(".a", 2ULL);
                        (void)_t2523;
                        U64 _t2524 = 0;
                        (void)_t2524;
                        Str *_t2525 = Str_concat(_t2522, _t2523);
                        (void)_t2525;
                        Str_delete(_t2522, &(Bool){1});
                        Str_delete(_t2523, &(Bool){1});
                        Array_set(_va74, &(U64){_t2524}, _t2525);
                        ;
                        println(_va74);
                    }
                    ;
                }
                ;
                Str_delete(h_path, &(Bool){1});
                Str_delete(til_path, &(Bool){1});
            }
            ;
            Str_delete(name, &(Bool){1});
            I32 _t2591 = 0;
            (void)_t2591;
            Bool _t2592 = I32_eq(result, _t2591);
            (void)_t2592;
            ;
            Bool _t2593 = Bool_not(do_lib);
            (void)_t2593;
            Str *_t2594 = Str_lit("translate", 9ULL);
            (void)_t2594;
            Bool _t2595 = Bool_and(_t2592, _t2593);
            (void)_t2595;
            ;
            ;
            Bool _t2596; { Bool *_hp = (Bool *)Str_eq(command, _t2594); _t2596 = *_hp; free(_hp); }
            (void)_t2596;
            Str_delete(_t2594, &(Bool){1});
            Bool _t2597 = Bool_and(_t2595, _t2596);
            (void)_t2597;
            ;
            ;
            if (_t2597) {
                Str *_t2548 = Str_lit("Str", 3ULL);
                (void)_t2548;
                U64 _t2549; { U64 *_hp = (U64 *)Str_size(); _t2549 = *_hp; free(_hp); }
                (void)_t2549;
                U64 _t2550 = 1;
                (void)_t2550;
                Array *_va75 = Array_new(_t2548, &(U64){_t2549}, &(U64){_t2550});
                (void)_va75;
                Str_delete(_t2548, &(Bool){1});
                ;
                ;
                Str *_t2551 = Str_lit("Generated: ", 11ULL);
                (void)_t2551;
                U64 _t2552 = 0;
                (void)_t2552;
                Str *_t2553 = Str_concat(_t2551, c_path);
                (void)_t2553;
                Str_delete(_t2551, &(Bool){1});
                Array_set(_va75, &(U64){_t2552}, _t2553);
                ;
                println(_va75);
            }
            ;
            I32 _t2598 = 0;
            (void)_t2598;
            Bool _t2599 = I32_eq(result, _t2598);
            (void)_t2599;
            ;
            Bool _t2600 = Bool_not(do_lib);
            (void)_t2600;
            Str *_t2601 = Str_lit("translate", 9ULL);
            (void)_t2601;
            Bool _t2602; { Bool *_hp = (Bool *)Str_eq(command, _t2601); _t2602 = *_hp; free(_hp); }
            (void)_t2602;
            Str_delete(_t2601, &(Bool){1});
            Bool _t2603 = Bool_and(_t2599, _t2600);
            (void)_t2603;
            ;
            ;
            Bool _t2604 = Bool_not(_t2602);
            (void)_t2604;
            ;
            Bool _t2605 = Bool_and(_t2603, _t2604);
            (void)_t2605;
            ;
            ;
            if (_t2605) {
                I32 _t2554 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t2554;
                result = _t2554;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t2606 = 0;
            (void)_t2606;
            Bool _t2607 = I32_eq(result, _t2606);
            (void)_t2607;
            ;
            Bool _t2608 = Bool_not(do_lib);
            (void)_t2608;
            ;
            Str *_t2609 = Str_lit("run", 3ULL);
            (void)_t2609;
            Bool _t2610 = Bool_and(_t2607, _t2608);
            (void)_t2610;
            ;
            ;
            Bool _t2611; { Bool *_hp = (Bool *)Str_eq(command, _t2609); _t2611 = *_hp; free(_hp); }
            (void)_t2611;
            Str_delete(_t2609, &(Bool){1});
            Bool _t2612 = Bool_and(_t2610, _t2611);
            (void)_t2612;
            ;
            ;
            if (_t2612) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t2556; { U64 *_hp = (U64 *)Vec_len(user_argv); _t2556 = *_hp; free(_hp); }
                    (void)_t2556;
                    Bool _wcond2555; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t2556}); _wcond2555 = *_hp; free(_hp); }
                    (void)_wcond2555;
                    ;
                    if (_wcond2555) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t2557 = Str_lit(" '", 2ULL);
                    (void)_t2557;
                    Str *_t2558 = Str_concat(cmd, _t2557);
                    (void)_t2558;
                    Str_delete(_t2557, &(Bool){1});
                    Str *_t2559 = Str_concat(_t2558, uarg);
                    (void)_t2559;
                    Str_delete(_t2558, &(Bool){1});
                    Str *_t2560 = Str_lit("'", 1ULL);
                    (void)_t2560;
                    cmd = Str_concat(_t2559, _t2560);
                    Str_delete(_t2559, &(Bool){1});
                    Str_delete(_t2560, &(Bool){1});
                    U64 _t2561 = 1;
                    (void)_t2561;
                    U64 _t2562 = U64_add(DEREF(ui), _t2561);
                    (void)_t2562;
                    ;
                    *ui = _t2562;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t2563 = til_system(cmd);
                (void)_t2563;
                Str_delete(cmd, &(Bool){1});
                result = _t2563;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t2629 = Str_lit("ast", 3ULL);
            (void)_t2629;
            Bool _t2630; { Bool *_hp = (Bool *)Str_eq(command, _t2629); _t2630 = *_hp; free(_hp); }
            (void)_t2630;
            Str_delete(_t2629, &(Bool){1});
            if (_t2630) {
                Str *_t2613 = Str_lit("Str", 3ULL);
                (void)_t2613;
                U64 _t2614; { U64 *_hp = (U64 *)Str_size(); _t2614 = *_hp; free(_hp); }
                (void)_t2614;
                U64 _t2615 = 1;
                (void)_t2615;
                Array *_va76 = Array_new(_t2613, &(U64){_t2614}, &(U64){_t2615});
                (void)_va76;
                Str_delete(_t2613, &(Bool){1});
                ;
                ;
                Str *_t2616 = Str_lit("mode: ", 6ULL);
                (void)_t2616;
                U64 _t2617 = 0;
                (void)_t2617;
                Str *_t2618 = Str_concat(_t2616, &cur_mode->name);
                (void)_t2618;
                Str_delete(_t2616, &(Bool){1});
                Array_set(_va76, &(U64){_t2617}, _t2618);
                ;
                println(_va76);
                U32 _t2619 = 0;
                (void)_t2619;
                ast_print(ast, _t2619);
                ;
            } else {
                Str *_t2620 = Str_lit("Str", 3ULL);
                (void)_t2620;
                U64 _t2621; { U64 *_hp = (U64 *)Str_size(); _t2621 = *_hp; free(_hp); }
                (void)_t2621;
                U64 _t2622 = 1;
                (void)_t2622;
                Array *_va77 = Array_new(_t2620, &(U64){_t2621}, &(U64){_t2622});
                (void)_va77;
                Str_delete(_t2620, &(Bool){1});
                ;
                ;
                Str *_t2623 = Str_lit("error: unknown command '", 24ULL);
                (void)_t2623;
                Str *_t2624 = Str_concat(_t2623, command);
                (void)_t2624;
                Str_delete(_t2623, &(Bool){1});
                Str *_t2625 = Str_lit("'", 1ULL);
                (void)_t2625;
                U64 _t2626 = 0;
                (void)_t2626;
                Str *_t2627 = Str_concat(_t2624, _t2625);
                (void)_t2627;
                Str_delete(_t2624, &(Bool){1});
                Str_delete(_t2625, &(Bool){1});
                Array_set(_va77, &(U64){_t2626}, _t2627);
                ;
                println(_va77);
                usage();
                I32 _t2628 = 1;
                (void)_t2628;
                result = _t2628;
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
    I64 _t2716 = I32_to_i64(result);
    (void)_t2716;
    ;
    exit(_t2716);
    ;
    return 0;
}

