#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t2115 = Bool_clone(&self->needs_main);
    (void)_t2115;
    Bool _t2116 = Bool_clone(&self->decls_only);
    (void)_t2116;
    Bool _t2117 = Bool_clone(&self->is_pure);
    (void)_t2117;
    Bool _t2118 = Bool_clone(&self->debug_prints);
    (void)_t2118;
    Mode *_t2119 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t2119->name = *_ca; free(_ca); }
    _t2119->needs_main = _t2115;
    _t2119->decls_only = _t2116;
    { Str *_ca = Str_clone(&self->auto_import); _t2119->auto_import = *_ca; free(_ca); }
    _t2119->is_pure = _t2117;
    _t2119->debug_prints = _t2118;
    (void)_t2119;
    ;
    ;
    ;
    ;
    return _t2119;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2120 = 0;
    (void)_t2120;
    Str_delete(&self->name, &(Bool){_t2120});
    ;
    Bool _t2121 = 0;
    (void)_t2121;
    Bool_delete(&self->needs_main, &(Bool){_t2121});
    ;
    Bool _t2122 = 0;
    (void)_t2122;
    Bool_delete(&self->decls_only, &(Bool){_t2122});
    ;
    Bool _t2123 = 0;
    (void)_t2123;
    Str_delete(&self->auto_import, &(Bool){_t2123});
    ;
    Bool _t2124 = 0;
    (void)_t2124;
    Bool_delete(&self->is_pure, &(Bool){_t2124});
    ;
    Bool _t2125 = 0;
    (void)_t2125;
    Bool_delete(&self->debug_prints, &(Bool){_t2125});
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
    TypeScope *_t2127 = malloc(sizeof(TypeScope));
    (void)_t2127;
    return _t2127;
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
    Str *_t2158 = Str_lit("Str", 3ULL);
    (void)_t2158;
    U64 _t2159; { U64 *_hp = (U64 *)Str_size(); _t2159 = *_hp; free(_hp); }
    (void)_t2159;
    Vec *paths = Vec_new(_t2158, &(U64){_t2159});
    (void)paths;
    Str_delete(_t2158, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2133 = expr_nchildren(body);
        (void)_t2133;
        Bool _wcond2129; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2133}); _wcond2129 = *_hp; free(_hp); }
        (void)_wcond2129;
        ;
        if (_wcond2129) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t2134 = expr_get_tag(stmt);
        (void)_t2134;
        U32 _t2135 = expr_nchildren(stmt);
        (void)_t2135;
        U32 _t2136 = 2;
        (void)_t2136;
        Bool _t2137 = I32_eq(_t2134, DEREF(NODE_FCALL));
        (void)_t2137;
        ;
        Bool _t2138 = U32_eq(_t2135, _t2136);
        (void)_t2138;
        ;
        ;
        U32 *_t2139 = malloc(sizeof(U32));
        *_t2139 = 0;
        (void)_t2139;
        Expr *_t2140 = expr_get_child(stmt, DEREF(_t2139));
        (void)_t2140;
        I32 _t2141 = expr_get_tag(_t2140);
        (void)_t2141;
        U32_delete(_t2139, &(Bool){1});
        Bool _t2142 = Bool_and(_t2137, _t2138);
        (void)_t2142;
        ;
        ;
        Bool _t2143 = I32_eq(_t2141, DEREF(NODE_IDENT));
        (void)_t2143;
        ;
        U32 *_t2144 = malloc(sizeof(U32));
        *_t2144 = 0;
        (void)_t2144;
        Expr *_t2145 = expr_get_child(stmt, DEREF(_t2144));
        (void)_t2145;
        Str *_t2146 = expr_get_str_val(_t2145);
        (void)_t2146;
        Str *_t2147 = Str_lit("import", 6ULL);
        (void)_t2147;
        Bool _t2148 = Bool_and(_t2142, _t2143);
        (void)_t2148;
        ;
        ;
        Bool _t2149; { Bool *_hp = (Bool *)Str_eq(_t2146, _t2147); _t2149 = *_hp; free(_hp); }
        (void)_t2149;
        U32_delete(_t2144, &(Bool){1});
        Str_delete(_t2147, &(Bool){1});
        U32 *_t2150 = malloc(sizeof(U32));
        *_t2150 = 1;
        (void)_t2150;
        Expr *_t2151 = expr_get_child(stmt, DEREF(_t2150));
        (void)_t2151;
        I32 _t2152 = expr_get_tag(_t2151);
        (void)_t2152;
        U32_delete(_t2150, &(Bool){1});
        Bool _t2153 = Bool_and(_t2148, _t2149);
        (void)_t2153;
        ;
        ;
        Bool _t2154 = I32_eq(_t2152, DEREF(NODE_LITERAL_STR));
        (void)_t2154;
        ;
        Bool _t2155 = Bool_and(_t2153, _t2154);
        (void)_t2155;
        ;
        ;
        if (_t2155) {
            U32 *_t2130 = malloc(sizeof(U32));
            *_t2130 = 1;
            (void)_t2130;
            Expr *_t2131 = expr_get_child(stmt, DEREF(_t2130));
            (void)_t2131;
            Str *path = expr_get_str_val(_t2131);
            (void)path;
            Str *_t2132 = Str_clone(path);
            (void)_t2132;
            U32_delete(_t2130, &(Bool){1});
            Vec_push(paths, _t2132);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2156 = 1;
        (void)_t2156;
        U32 _t2157 = U32_add(DEREF(i), _t2156);
        (void)_t2157;
        ;
        *i = _t2157;
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
        U64 _fi2160 = 0;
        (void)_fi2160;
        while (1) {
            U64 _t2190 = 0;
            (void)_t2190;
            U64 _t2191; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2191 = *_hp; free(_hp); }
            (void)_t2191;
            Range *_t2192 = Range_new(_t2190, _t2191);
            (void)_t2192;
            ;
            ;
            U64 _t2193; { U64 *_hp = (U64 *)Range_len(_t2192); _t2193 = *_hp; free(_hp); }
            (void)_t2193;
            Range_delete(_t2192, &(Bool){1});
            Bool _wcond2161; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2160}, &(U64){_t2193}); _wcond2161 = *_hp; free(_hp); }
            (void)_wcond2161;
            ;
            if (_wcond2161) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2194 = 0;
            (void)_t2194;
            U64 _t2195; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2195 = *_hp; free(_hp); }
            (void)_t2195;
            Range *_t2196 = Range_new(_t2194, _t2195);
            (void)_t2196;
            ;
            ;
            U64 *i = Range_get(_t2196, _fi2160);
            (void)i;
            Range_delete(_t2196, &(Bool){1});
            U64 _t2197 = 1;
            (void)_t2197;
            U64 _t2198 = U64_add(_fi2160, _t2197);
            (void)_t2198;
            ;
            _fi2160 = _t2198;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t2199 = Str_lit("/", 1ULL);
            (void)_t2199;
            Str *_t2200 = Str_concat(base_dir, _t2199);
            (void)_t2200;
            Str_delete(_t2199, &(Bool){1});
            Str *try_path = Str_concat(_t2200, import_path);
            (void)try_path;
            Str_delete(_t2200, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t2201 = Str_lit("", 0ULL);
            (void)_t2201;
            U64 _t2202; { U64 *_hp = (U64 *)Str_len(lib_dir); _t2202 = *_hp; free(_hp); }
            (void)_t2202;
            U64 _t2203 = 0;
            (void)_t2203;
            Bool _t2204; { Bool *_hp = (Bool *)Str_eq(abs, _t2201); _t2204 = *_hp; free(_hp); }
            (void)_t2204;
            Str_delete(_t2201, &(Bool){1});
            Bool _t2205; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2202}, &(U64){_t2203}); _t2205 = *_hp; free(_hp); }
            (void)_t2205;
            ;
            ;
            Bool _t2206 = Bool_and(_t2204, _t2205);
            (void)_t2206;
            ;
            ;
            if (_t2206) {
                Str *_t2162 = Str_lit("/", 1ULL);
                (void)_t2162;
                Str *_t2163 = Str_concat(lib_dir, _t2162);
                (void)_t2163;
                Str_delete(_t2162, &(Bool){1});
                try_path = Str_concat(_t2163, import_path);
                Str_delete(_t2163, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t2207 = Str_lit("", 0ULL);
            (void)_t2207;
            Bool _t2208; { Bool *_hp = (Bool *)Str_eq(abs, _t2207); _t2208 = *_hp; free(_hp); }
            (void)_t2208;
            Str_delete(_t2207, &(Bool){1});
            if (_t2208) {
                Str *_t2164 = Str_lit("Str", 3ULL);
                (void)_t2164;
                U64 _t2165; { U64 *_hp = (U64 *)Str_size(); _t2165 = *_hp; free(_hp); }
                (void)_t2165;
                U64 _t2166 = 1;
                (void)_t2166;
                Array *_va50 = Array_new(_t2164, &(U64){_t2165}, &(U64){_t2166});
                (void)_va50;
                Str_delete(_t2164, &(Bool){1});
                ;
                ;
                Str *_t2167 = Str_lit("error: could not find import '", 30ULL);
                (void)_t2167;
                Str *_t2168 = Str_concat(_t2167, import_path);
                (void)_t2168;
                Str_delete(_t2167, &(Bool){1});
                Str *_t2169 = Str_lit("' (from ", 8ULL);
                (void)_t2169;
                Str *_t2170 = Str_concat(_t2168, _t2169);
                (void)_t2170;
                Str_delete(_t2168, &(Bool){1});
                Str_delete(_t2169, &(Bool){1});
                Str *_t2171 = Str_concat(_t2170, base_dir);
                (void)_t2171;
                Str_delete(_t2170, &(Bool){1});
                Str *_t2172 = Str_lit("/)", 2ULL);
                (void)_t2172;
                U64 _t2173 = 0;
                (void)_t2173;
                Str *_t2174 = Str_concat(_t2171, _t2172);
                (void)_t2174;
                Str_delete(_t2171, &(Bool){1});
                Str_delete(_t2172, &(Bool){1});
                Array_set(_va50, &(U64){_t2173}, _t2174);
                ;
                println(_va50);
                I64 _t2175 = 1;
                (void)_t2175;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t2175; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t2209 = til_set_has(resolved_set, abs);
            (void)_t2209;
            if (_t2209) {
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
            U64 _t2210; { U64 *_hp = (U64 *)Str_len(abs); _t2210 = *_hp; free(_hp); }
            (void)_t2210;
            U64 _t2211 = 1;
            (void)_t2211;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2210, _t2211);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t2177 = 0;
                (void)_t2177;
                U8 *_t2178 = Str_get(abs, last_slash);
                (void)_t2178;
                U8 _t2179 = 47;
                (void)_t2179;
                Bool _t2180; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2177}); _t2180 = *_hp; free(_hp); }
                (void)_t2180;
                ;
                Bool _t2181; { Bool *_hp = (Bool *)U8_neq(_t2178, &(U8){_t2179}); _t2181 = *_hp; free(_hp); }
                (void)_t2181;
                ;
                Bool _wcond2176 = Bool_and(_t2180, _t2181);
                (void)_wcond2176;
                ;
                ;
                if (_wcond2176) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2182 = 1;
                (void)_t2182;
                U64 _t2183 = U64_sub(DEREF(last_slash), _t2182);
                (void)_t2183;
                ;
                *last_slash = _t2183;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t2212; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t2212 = *_hp; free(_hp); }
            (void)_t2212;
            U64 _t2213 = 0;
            (void)_t2213;
            Bool _t2214; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2212}, &(U64){_t2213}); _t2214 = *_hp; free(_hp); }
            (void)_t2214;
            ;
            ;
            if (_t2214) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t2184 = 0;
                (void)_t2184;
                Bool _t2185; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2184}); _t2185 = *_hp; free(_hp); }
                (void)_t2185;
                ;
                if (_t2185) {
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
                U32 _t2187 = expr_nchildren(sub_ast);
                (void)_t2187;
                Bool _wcond2186; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t2187}); _wcond2186 = *_hp; free(_hp); }
                (void)_wcond2186;
                ;
                if (_wcond2186) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t2188 = 1;
                (void)_t2188;
                U32 _t2189 = U32_add(DEREF(k), _t2188);
                (void)_t2189;
                ;
                *k = _t2189;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t2215 = 0;
    (void)_t2215;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2215; return _r; }
}

void usage(void) {
    Str *_t2216 = Str_lit("Str", 3ULL);
    (void)_t2216;
    U64 _t2217; { U64 *_hp = (U64 *)Str_size(); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    U64 _t2218 = 1;
    (void)_t2218;
    Array *_va51 = Array_new(_t2216, &(U64){_t2217}, &(U64){_t2218});
    (void)_va51;
    Str_delete(_t2216, &(Bool){1});
    ;
    ;
    U64 _t2219 = 0;
    (void)_t2219;
    Str *_t2220 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t2220;
    Array_set(_va51, &(U64){_t2219}, _t2220);
    ;
    println(_va51);
    Str *_t2221 = Str_lit("Str", 3ULL);
    (void)_t2221;
    U64 _t2222; { U64 *_hp = (U64 *)Str_size(); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    U64 _t2223 = 1;
    (void)_t2223;
    Array *_va52 = Array_new(_t2221, &(U64){_t2222}, &(U64){_t2223});
    (void)_va52;
    Str_delete(_t2221, &(Bool){1});
    ;
    ;
    U64 _t2224 = 0;
    (void)_t2224;
    Str *_t2225 = Str_lit("", 0ULL);
    (void)_t2225;
    Array_set(_va52, &(U64){_t2224}, _t2225);
    ;
    println(_va52);
    Str *_t2226 = Str_lit("Str", 3ULL);
    (void)_t2226;
    U64 _t2227; { U64 *_hp = (U64 *)Str_size(); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    U64 _t2228 = 1;
    (void)_t2228;
    Array *_va53 = Array_new(_t2226, &(U64){_t2227}, &(U64){_t2228});
    (void)_va53;
    Str_delete(_t2226, &(Bool){1});
    ;
    ;
    U64 _t2229 = 0;
    (void)_t2229;
    Str *_t2230 = Str_lit("Commands:", 9ULL);
    (void)_t2230;
    Array_set(_va53, &(U64){_t2229}, _t2230);
    ;
    println(_va53);
    Str *_t2231 = Str_lit("Str", 3ULL);
    (void)_t2231;
    U64 _t2232; { U64 *_hp = (U64 *)Str_size(); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    U64 _t2233 = 1;
    (void)_t2233;
    Array *_va54 = Array_new(_t2231, &(U64){_t2232}, &(U64){_t2233});
    (void)_va54;
    Str_delete(_t2231, &(Bool){1});
    ;
    ;
    U64 _t2234 = 0;
    (void)_t2234;
    Str *_t2235 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t2235;
    Array_set(_va54, &(U64){_t2234}, _t2235);
    ;
    println(_va54);
    Str *_t2236 = Str_lit("Str", 3ULL);
    (void)_t2236;
    U64 _t2237; { U64 *_hp = (U64 *)Str_size(); _t2237 = *_hp; free(_hp); }
    (void)_t2237;
    U64 _t2238 = 1;
    (void)_t2238;
    Array *_va55 = Array_new(_t2236, &(U64){_t2237}, &(U64){_t2238});
    (void)_va55;
    Str_delete(_t2236, &(Bool){1});
    ;
    ;
    U64 _t2239 = 0;
    (void)_t2239;
    Str *_t2240 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t2240;
    Array_set(_va55, &(U64){_t2239}, _t2240);
    ;
    println(_va55);
    Str *_t2241 = Str_lit("Str", 3ULL);
    (void)_t2241;
    U64 _t2242; { U64 *_hp = (U64 *)Str_size(); _t2242 = *_hp; free(_hp); }
    (void)_t2242;
    U64 _t2243 = 1;
    (void)_t2243;
    Array *_va56 = Array_new(_t2241, &(U64){_t2242}, &(U64){_t2243});
    (void)_va56;
    Str_delete(_t2241, &(Bool){1});
    ;
    ;
    U64 _t2244 = 0;
    (void)_t2244;
    Str *_t2245 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t2245;
    Array_set(_va56, &(U64){_t2244}, _t2245);
    ;
    println(_va56);
    Str *_t2246 = Str_lit("Str", 3ULL);
    (void)_t2246;
    U64 _t2247; { U64 *_hp = (U64 *)Str_size(); _t2247 = *_hp; free(_hp); }
    (void)_t2247;
    U64 _t2248 = 1;
    (void)_t2248;
    Array *_va57 = Array_new(_t2246, &(U64){_t2247}, &(U64){_t2248});
    (void)_va57;
    Str_delete(_t2246, &(Bool){1});
    ;
    ;
    U64 _t2249 = 0;
    (void)_t2249;
    Str *_t2250 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t2250;
    Array_set(_va57, &(U64){_t2249}, _t2250);
    ;
    println(_va57);
    Str *_t2251 = Str_lit("Str", 3ULL);
    (void)_t2251;
    U64 _t2252; { U64 *_hp = (U64 *)Str_size(); _t2252 = *_hp; free(_hp); }
    (void)_t2252;
    U64 _t2253 = 1;
    (void)_t2253;
    Array *_va58 = Array_new(_t2251, &(U64){_t2252}, &(U64){_t2253});
    (void)_va58;
    Str_delete(_t2251, &(Bool){1});
    ;
    ;
    U64 _t2254 = 0;
    (void)_t2254;
    Str *_t2255 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t2255;
    Array_set(_va58, &(U64){_t2254}, _t2255);
    ;
    println(_va58);
    Str *_t2256 = Str_lit("Str", 3ULL);
    (void)_t2256;
    U64 _t2257; { U64 *_hp = (U64 *)Str_size(); _t2257 = *_hp; free(_hp); }
    (void)_t2257;
    U64 _t2258 = 1;
    (void)_t2258;
    Array *_va59 = Array_new(_t2256, &(U64){_t2257}, &(U64){_t2258});
    (void)_va59;
    Str_delete(_t2256, &(Bool){1});
    ;
    ;
    U64 _t2259 = 0;
    (void)_t2259;
    Str *_t2260 = Str_lit("  help       Print this message", 31ULL);
    (void)_t2260;
    Array_set(_va59, &(U64){_t2259}, _t2260);
    ;
    println(_va59);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t2266 = 1;
    (void)_t2266;
    e->is_core = _t2266;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2262 = expr_nchildren(e);
        (void)_t2262;
        Bool _wcond2261; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2262}); _wcond2261 = *_hp; free(_hp); }
        (void)_wcond2261;
        ;
        if (_wcond2261) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t2263 = expr_get_child(e, DEREF(i));
        (void)_t2263;
        mark_core(_t2263);
        U32 _t2264 = 1;
        (void)_t2264;
        U32 _t2265 = U32_add(DEREF(i), _t2264);
        (void)_t2265;
        ;
        *i = _t2265;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t2722 = malloc(sizeof(I64));
    *_t2722 = 0;
    (void)_t2722;
    _t2723 = malloc(sizeof(I64));
    *_t2723 = 1;
    (void)_t2723;
    _t2724 = malloc(sizeof(I64)); *_t2724 = I64_sub(DEREF(_t2722), DEREF(_t2723));
    (void)_t2724;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2724));
    (void)CAP_LIT;
    _t2725 = malloc(sizeof(I64));
    *_t2725 = 0;
    (void)_t2725;
    _t2726 = malloc(sizeof(I64));
    *_t2726 = 2;
    (void)_t2726;
    _t2727 = malloc(sizeof(I64)); *_t2727 = I64_sub(DEREF(_t2725), DEREF(_t2726));
    (void)_t2727;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2727));
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
    U64 _t2644; { U64 *_hp = (U64 *)Array_len(args); _t2644 = *_hp; free(_hp); }
    (void)_t2644;
    U64 _t2645 = 0;
    (void)_t2645;
    Bool _t2646 = U64_eq(_t2644, _t2645);
    (void)_t2646;
    ;
    ;
    if (_t2646) {
        usage();
        Str *_t2267 = Str_lit("Str", 3ULL);
        (void)_t2267;
        U64 _t2268; { U64 *_hp = (U64 *)Str_size(); _t2268 = *_hp; free(_hp); }
        (void)_t2268;
        U64 _t2269 = 1;
        (void)_t2269;
        Array *_va60 = Array_new(_t2267, &(U64){_t2268}, &(U64){_t2269});
        (void)_va60;
        Str_delete(_t2267, &(Bool){1});
        ;
        ;
        U64 _t2270 = 0;
        (void)_t2270;
        Str *_t2271 = Str_lit("no arguments", 12ULL);
        (void)_t2271;
        Array_set(_va60, &(U64){_t2270}, _t2271);
        ;
        Str *_t2272 = Str_lit("src/til.til:217:15", 18ULL);
        (void)_t2272;
        panic(_t2272, _va60);
        Str_delete(_t2272, &(Bool){1});
    }
    ;
    U64 *_t2647 = malloc(sizeof(U64));
    *_t2647 = 0;
    (void)_t2647;
    Str *cmd_ref = Array_get(args, _t2647);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t2647, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t2648; { U64 *_hp = (U64 *)Array_len(args); _t2648 = *_hp; free(_hp); }
    (void)_t2648;
    U64 _t2649 = 1;
    (void)_t2649;
    Bool _t2650 = U64_eq(_t2648, _t2649);
    (void)_t2650;
    ;
    ;
    if (_t2650) {
        Str *_t2273 = Str_lit("help", 4ULL);
        (void)_t2273;
        Str *_t2274 = Str_lit("--help", 6ULL);
        (void)_t2274;
        Bool _t2275; { Bool *_hp = (Bool *)Str_eq(command, _t2273); _t2275 = *_hp; free(_hp); }
        (void)_t2275;
        Str_delete(_t2273, &(Bool){1});
        Bool _t2276; { Bool *_hp = (Bool *)Str_eq(command, _t2274); _t2276 = *_hp; free(_hp); }
        (void)_t2276;
        Str_delete(_t2274, &(Bool){1});
        Bool _t2277 = Bool_or(_t2275, _t2276);
        (void)_t2277;
        ;
        ;
        if (_t2277) {
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
            U64 _t2294; { U64 *_hp = (U64 *)Array_len(args); _t2294 = *_hp; free(_hp); }
            (void)_t2294;
            Bool _wcond2278; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t2294}); _wcond2278 = *_hp; free(_hp); }
            (void)_wcond2278;
            ;
            if (_wcond2278) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t2295 = Str_lit("-o", 2ULL);
            (void)_t2295;
            U64 _t2296 = 1;
            (void)_t2296;
            U64 _t2297 = U64_add(DEREF(path_idx), _t2296);
            (void)_t2297;
            ;
            U64 _t2298; { U64 *_hp = (U64 *)Array_len(args); _t2298 = *_hp; free(_hp); }
            (void)_t2298;
            Bool _t2299; { Bool *_hp = (Bool *)Str_eq(flag, _t2295); _t2299 = *_hp; free(_hp); }
            (void)_t2299;
            Str_delete(_t2295, &(Bool){1});
            Bool _t2300; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2297}, &(U64){_t2298}); _t2300 = *_hp; free(_hp); }
            (void)_t2300;
            ;
            ;
            Bool _t2301 = Bool_and(_t2299, _t2300);
            (void)_t2301;
            ;
            ;
            if (_t2301) {
                U64 _t2279 = 1;
                (void)_t2279;
                U64 *_t2280 = malloc(sizeof(U64)); *_t2280 = U64_add(DEREF(path_idx), _t2279);
                (void)_t2280;
                ;
                Str *oval = Array_get(args, _t2280);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t2280, &(Bool){1});
                U64 _t2281 = 2;
                (void)_t2281;
                U64 _t2282 = U64_add(DEREF(path_idx), _t2281);
                (void)_t2282;
                ;
                *path_idx = _t2282;
                ;
            } else {
                Str *_t2287 = Str_lit("-c", 2ULL);
                (void)_t2287;
                U64 _t2288 = 1;
                (void)_t2288;
                U64 _t2289 = U64_add(DEREF(path_idx), _t2288);
                (void)_t2289;
                ;
                U64 _t2290; { U64 *_hp = (U64 *)Array_len(args); _t2290 = *_hp; free(_hp); }
                (void)_t2290;
                Bool _t2291; { Bool *_hp = (Bool *)Str_eq(flag, _t2287); _t2291 = *_hp; free(_hp); }
                (void)_t2291;
                Str_delete(_t2287, &(Bool){1});
                Bool _t2292; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2289}, &(U64){_t2290}); _t2292 = *_hp; free(_hp); }
                (void)_t2292;
                ;
                ;
                Bool _t2293 = Bool_and(_t2291, _t2292);
                (void)_t2293;
                ;
                ;
                if (_t2293) {
                    U64 _t2283 = 1;
                    (void)_t2283;
                    U64 *_t2284 = malloc(sizeof(U64)); *_t2284 = U64_add(DEREF(path_idx), _t2283);
                    (void)_t2284;
                    ;
                    Str *cval = Array_get(args, _t2284);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t2284, &(Bool){1});
                    U64 _t2285 = 2;
                    (void)_t2285;
                    U64 _t2286 = U64_add(DEREF(path_idx), _t2285);
                    (void)_t2286;
                    ;
                    *path_idx = _t2286;
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
    Str *_t2651 = Str_lit("help", 4ULL);
    (void)_t2651;
    Str *_t2652 = Str_lit("--help", 6ULL);
    (void)_t2652;
    Bool _t2653; { Bool *_hp = (Bool *)Str_eq(command, _t2651); _t2653 = *_hp; free(_hp); }
    (void)_t2653;
    Str_delete(_t2651, &(Bool){1});
    Bool _t2654; { Bool *_hp = (Bool *)Str_eq(command, _t2652); _t2654 = *_hp; free(_hp); }
    (void)_t2654;
    Str_delete(_t2652, &(Bool){1});
    Bool _t2655 = Bool_or(_t2653, _t2654);
    (void)_t2655;
    ;
    ;
    if (_t2655) {
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
    Str *_t2656 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t2656;
    Str *core_path = Str_concat(bin_dir, _t2656);
    (void)core_path;
    Str_delete(_t2656, &(Bool){1});
    Str *_t2657 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t2657;
    Str *ext_c_path = Str_concat(bin_dir, _t2657);
    (void)ext_c_path;
    Str_delete(_t2657, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t2658; { U64 *_hp = (U64 *)Str_len(abs_path); _t2658 = *_hp; free(_hp); }
    (void)_t2658;
    U64 _t2659 = 0;
    (void)_t2659;
    Bool _t2660; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2658}, &(U64){_t2659}); _t2660 = *_hp; free(_hp); }
    (void)_t2660;
    ;
    ;
    if (_t2660) {
        U64 _t2310; { U64 *_hp = (U64 *)Str_len(abs_path); _t2310 = *_hp; free(_hp); }
        (void)_t2310;
        U64 _t2311 = 1;
        (void)_t2311;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2310, _t2311);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t2303 = 0;
            (void)_t2303;
            U8 *_t2304 = Str_get(abs_path, last_slash);
            (void)_t2304;
            U8 _t2305 = 47;
            (void)_t2305;
            Bool _t2306; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2303}); _t2306 = *_hp; free(_hp); }
            (void)_t2306;
            ;
            Bool _t2307; { Bool *_hp = (Bool *)U8_neq(_t2304, &(U8){_t2305}); _t2307 = *_hp; free(_hp); }
            (void)_t2307;
            ;
            Bool _wcond2302 = Bool_and(_t2306, _t2307);
            (void)_wcond2302;
            ;
            ;
            if (_wcond2302) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2308 = 1;
            (void)_t2308;
            U64 _t2309 = U64_sub(DEREF(last_slash), _t2308);
            (void)_t2309;
            ;
            *last_slash = _t2309;
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
    U64 _t2661; { U64 *_hp = (U64 *)Str_len(core_abs); _t2661 = *_hp; free(_hp); }
    (void)_t2661;
    U64 _t2662 = 0;
    (void)_t2662;
    Bool _t2663; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2661}, &(U64){_t2662}); _t2663 = *_hp; free(_hp); }
    (void)_t2663;
    ;
    ;
    if (_t2663) {
        Bool _t2313 = til_set_has(resolved, core_abs);
        (void)_t2313;
        if (_t2313) {
            Bool _t2312 = 1;
            (void)_t2312;
            skip_core = _t2312;
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
    U64 _t2664; { U64 *_hp = (U64 *)Vec_len(core_imports); _t2664 = *_hp; free(_hp); }
    (void)_t2664;
    U64 _t2665 = 0;
    (void)_t2665;
    Bool _t2666; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2664}, &(U64){_t2665}); _t2666 = *_hp; free(_hp); }
    (void)_t2666;
    ;
    ;
    Bool _t2667 = Bool_not(skip_core);
    (void)_t2667;
    Bool _t2668 = Bool_and(_t2666, _t2667);
    (void)_t2668;
    ;
    ;
    if (_t2668) {
        Str *_t2320 = Str_lit("/src/core", 9ULL);
        (void)_t2320;
        Str *core_dir = Str_concat(bin_dir, _t2320);
        (void)core_dir;
        Str_delete(_t2320, &(Bool){1});
        Str *_t2321 = Str_lit("", 0ULL);
        (void)_t2321;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t2321); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t2321, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t2322 = 0;
        (void)_t2322;
        Bool _t2323; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2322}); _t2323 = *_hp; free(_hp); }
        (void)_t2323;
        ;
        ;
        if (_t2323) {
            Str *_t2314 = Str_lit("Str", 3ULL);
            (void)_t2314;
            U64 _t2315; { U64 *_hp = (U64 *)Str_size(); _t2315 = *_hp; free(_hp); }
            (void)_t2315;
            U64 _t2316 = 1;
            (void)_t2316;
            Array *_va61 = Array_new(_t2314, &(U64){_t2315}, &(U64){_t2316});
            (void)_va61;
            Str_delete(_t2314, &(Bool){1});
            ;
            ;
            U64 _t2317 = 0;
            (void)_t2317;
            Str *_t2318 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t2318;
            Array_set(_va61, &(U64){_t2317}, _t2318);
            ;
            Str *_t2319 = Str_lit("src/til.til:303:19", 18ULL);
            (void)_t2319;
            panic(_t2319, _va61);
            Str_delete(_t2319, &(Bool){1});
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
    Str *_t2669 = Str_lit("script", 6ULL);
    (void)_t2669;
    Mode *cur_mode = mode_resolve(_t2669);
    (void)cur_mode;
    Str_delete(_t2669, &(Bool){1});
    U64 _t2670; { U64 *_hp = (U64 *)Str_len(mode_str); _t2670 = *_hp; free(_hp); }
    (void)_t2670;
    U64 _t2671 = 0;
    (void)_t2671;
    Bool _t2672; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2670}, &(U64){_t2671}); _t2672 = *_hp; free(_hp); }
    (void)_t2672;
    ;
    ;
    if (_t2672) {
        cur_mode = mode_resolve(mode_str);
        U64 _t2333; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t2333 = *_hp; free(_hp); }
        (void)_t2333;
        U64 _t2334 = 0;
        (void)_t2334;
        Bool _t2335 = U64_eq(_t2333, _t2334);
        (void)_t2335;
        ;
        ;
        if (_t2335) {
            Str *_t2324 = Str_lit("Str", 3ULL);
            (void)_t2324;
            U64 _t2325; { U64 *_hp = (U64 *)Str_size(); _t2325 = *_hp; free(_hp); }
            (void)_t2325;
            U64 _t2326 = 1;
            (void)_t2326;
            Array *_va62 = Array_new(_t2324, &(U64){_t2325}, &(U64){_t2326});
            (void)_va62;
            Str_delete(_t2324, &(Bool){1});
            ;
            ;
            Str *_t2327 = Str_lit("unknown mode '", 14ULL);
            (void)_t2327;
            Str *_t2328 = Str_concat(_t2327, mode_str);
            (void)_t2328;
            Str_delete(_t2327, &(Bool){1});
            Str *_t2329 = Str_lit("'", 1ULL);
            (void)_t2329;
            U64 _t2330 = 0;
            (void)_t2330;
            Str *_t2331 = Str_concat(_t2328, _t2329);
            (void)_t2331;
            Str_delete(_t2328, &(Bool){1});
            Str_delete(_t2329, &(Bool){1});
            Array_set(_va62, &(U64){_t2330}, _t2331);
            ;
            Str *_t2332 = Str_lit("src/til.til:319:19", 18ULL);
            (void)_t2332;
            panic(_t2332, _va62);
            Str_delete(_t2332, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t2673; { U64 *_hp = (U64 *)Vec_len(imports); _t2673 = *_hp; free(_hp); }
    (void)_t2673;
    U64 _t2674 = 0;
    (void)_t2674;
    Bool _t2675; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2673}, &(U64){_t2674}); _t2675 = *_hp; free(_hp); }
    (void)_t2675;
    ;
    ;
    if (_t2675) {
        Str *_t2342 = Str_lit("/src/lib", 8ULL);
        (void)_t2342;
        Str *lib_dir = Str_concat(bin_dir, _t2342);
        (void)lib_dir;
        Str_delete(_t2342, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t2343 = 0;
        (void)_t2343;
        Bool _t2344; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2343}); _t2344 = *_hp; free(_hp); }
        (void)_t2344;
        ;
        ;
        if (_t2344) {
            Str *_t2336 = Str_lit("Str", 3ULL);
            (void)_t2336;
            U64 _t2337; { U64 *_hp = (U64 *)Str_size(); _t2337 = *_hp; free(_hp); }
            (void)_t2337;
            U64 _t2338 = 1;
            (void)_t2338;
            Array *_va63 = Array_new(_t2336, &(U64){_t2337}, &(U64){_t2338});
            (void)_va63;
            Str_delete(_t2336, &(Bool){1});
            ;
            ;
            U64 _t2339 = 0;
            (void)_t2339;
            Str *_t2340 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t2340;
            Array_set(_va63, &(U64){_t2339}, _t2340);
            ;
            Str *_t2341 = Str_lit("src/til.til:333:19", 18ULL);
            (void)_t2341;
            panic(_t2341, _va63);
            Str_delete(_t2341, &(Bool){1});
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
    Bool _t2676 = Bool_not(skip_core);
    (void)_t2676;
    ;
    if (_t2676) {
        while (1) {
            U32 _t2346 = expr_nchildren(core_ast);
            (void)_t2346;
            Bool _wcond2345; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2346}); _wcond2345 = *_hp; free(_hp); }
            (void)_wcond2345;
            ;
            if (_wcond2345) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2347 = 1;
            (void)_t2347;
            U32 _t2348 = U32_add(DEREF(i), _t2347);
            (void)_t2348;
            ;
            *i = _t2348;
            ;
        }
        U32 _t2353 = 0;
        (void)_t2353;
        *i = _t2353;
        ;
        while (1) {
            U32 _t2350 = expr_vec_count(core_import_decls);
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
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2351 = 1;
            (void)_t2351;
            U32 _t2352 = U32_add(DEREF(i), _t2351);
            (void)_t2352;
            ;
            *i = _t2352;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t2677; { U64 *_hp = (U64 *)Str_len(auto_import); _t2677 = *_hp; free(_hp); }
    (void)_t2677;
    U64 _t2678 = 0;
    (void)_t2678;
    Bool _t2679; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2677}, &(U64){_t2678}); _t2679 = *_hp; free(_hp); }
    (void)_t2679;
    ;
    ;
    if (_t2679) {
        Str *_t2358 = Str_lit("/src/modes/", 11ULL);
        (void)_t2358;
        Str *_t2359 = Str_concat(bin_dir, _t2358);
        (void)_t2359;
        Str_delete(_t2358, &(Bool){1});
        Str *_t2360 = Str_concat(_t2359, auto_import);
        (void)_t2360;
        Str_delete(_t2359, &(Bool){1});
        Str *_t2361 = Str_lit(".til", 4ULL);
        (void)_t2361;
        Str *mode_til_path = Str_concat(_t2360, _t2361);
        (void)mode_til_path;
        Str_delete(_t2360, &(Bool){1});
        Str_delete(_t2361, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t2362 = 0;
        (void)_t2362;
        *i = _t2362;
        ;
        while (1) {
            U32 _t2355 = expr_nchildren(mode_ast);
            (void)_t2355;
            Bool _wcond2354; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2355}); _wcond2354 = *_hp; free(_hp); }
            (void)_wcond2354;
            ;
            if (_wcond2354) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t2356 = 1;
            (void)_t2356;
            U32 _t2357 = U32_add(DEREF(i), _t2356);
            (void)_t2357;
            ;
            *i = _t2357;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t2680 = 0;
    (void)_t2680;
    *i = _t2680;
    ;
    while (1) {
        U32 _t2364 = expr_vec_count(import_decls);
        (void)_t2364;
        Bool _wcond2363; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2364}); _wcond2363 = *_hp; free(_hp); }
        (void)_wcond2363;
        ;
        if (_wcond2363) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2365 = 1;
        (void)_t2365;
        U32 _t2366 = U32_add(DEREF(i), _t2365);
        (void)_t2366;
        ;
        *i = _t2366;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t2681 = 0;
    (void)_t2681;
    *i = _t2681;
    ;
    while (1) {
        U32 _t2368 = expr_nchildren(ast);
        (void)_t2368;
        Bool _wcond2367; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2368}); _wcond2367 = *_hp; free(_hp); }
        (void)_wcond2367;
        ;
        if (_wcond2367) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2369 = 1;
        (void)_t2369;
        U32 _t2370 = U32_add(DEREF(i), _t2369);
        (void)_t2370;
        ;
        *i = _t2370;
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
    U32 _t2682 = 0;
    (void)_t2682;
    *i = _t2682;
    ;
    while (1) {
        U32 _t2386 = expr_nchildren(ast);
        (void)_t2386;
        Bool _wcond2371; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2386}); _wcond2371 = *_hp; free(_hp); }
        (void)_wcond2371;
        ;
        if (_wcond2371) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t2387 = expr_get_tag(stmt);
        (void)_t2387;
        U32 _t2388 = expr_nchildren(stmt);
        (void)_t2388;
        U32 _t2389 = 2;
        (void)_t2389;
        Bool _t2390 = I32_eq(_t2387, DEREF(NODE_FCALL));
        (void)_t2390;
        ;
        Bool _t2391 = U32_eq(_t2388, _t2389);
        (void)_t2391;
        ;
        ;
        U32 *_t2392 = malloc(sizeof(U32));
        *_t2392 = 0;
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
        Bool _t2396 = I32_eq(_t2394, DEREF(NODE_IDENT));
        (void)_t2396;
        ;
        U32 *_t2397 = malloc(sizeof(U32));
        *_t2397 = 1;
        (void)_t2397;
        Expr *_t2398 = expr_get_child(stmt, DEREF(_t2397));
        (void)_t2398;
        I32 _t2399 = expr_get_tag(_t2398);
        (void)_t2399;
        U32_delete(_t2397, &(Bool){1});
        Bool _t2400 = Bool_and(_t2395, _t2396);
        (void)_t2400;
        ;
        ;
        Bool _t2401 = I32_eq(_t2399, DEREF(NODE_LITERAL_STR));
        (void)_t2401;
        ;
        Bool _t2402 = Bool_and(_t2400, _t2401);
        (void)_t2402;
        ;
        ;
        if (_t2402) {
            U32 *_t2380 = malloc(sizeof(U32));
            *_t2380 = 0;
            (void)_t2380;
            Expr *_t2381 = expr_get_child(stmt, DEREF(_t2380));
            (void)_t2381;
            Str *fname = expr_get_str_val(_t2381);
            (void)fname;
            U32 *_t2382 = malloc(sizeof(U32));
            *_t2382 = 1;
            (void)_t2382;
            Expr *_t2383 = expr_get_child(stmt, DEREF(_t2382));
            (void)_t2383;
            Str *arg = expr_get_str_val(_t2383);
            (void)arg;
            Str *_t2384 = Str_lit("link", 4ULL);
            (void)_t2384;
            Bool _t2385; { Bool *_hp = (Bool *)Str_eq(fname, _t2384); _t2385 = *_hp; free(_hp); }
            (void)_t2385;
            Str_delete(_t2384, &(Bool){1});
            if (_t2385) {
                Str *_t2372 = Str_lit(" -l", 3ULL);
                (void)_t2372;
                Str *_t2373 = Str_concat(link_flags, _t2372);
                (void)_t2373;
                Str_delete(_t2372, &(Bool){1});
                link_flags = Str_concat(_t2373, arg);
                Str_delete(_t2373, &(Bool){1});
            } else {
                Str *_t2378 = Str_lit("link_c", 6ULL);
                (void)_t2378;
                Bool _t2379; { Bool *_hp = (Bool *)Str_eq(fname, _t2378); _t2379 = *_hp; free(_hp); }
                (void)_t2379;
                Str_delete(_t2378, &(Bool){1});
                if (_t2379) {
                    U64 _t2375; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2375 = *_hp; free(_hp); }
                    (void)_t2375;
                    U64 _t2376 = 0;
                    (void)_t2376;
                    Bool _t2377; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2375}, &(U64){_t2376}); _t2377 = *_hp; free(_hp); }
                    (void)_t2377;
                    ;
                    ;
                    if (_t2377) {
                        Str *_t2374 = Str_lit(" ", 1ULL);
                        (void)_t2374;
                        link_c_paths = Str_concat(link_c_paths, _t2374);
                        Str_delete(_t2374, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t2380, &(Bool){1});
            U32_delete(_t2382, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2403 = 1;
        (void)_t2403;
        U32 _t2404 = U32_add(DEREF(i), _t2403);
        (void)_t2404;
        ;
        *i = _t2404;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t2683 = init_declarations(ast, scope);
    (void)_t2683;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t2684 = 0;
    (void)_t2684;
    Bool _t2685; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t2684}); _t2685 = *_hp; free(_hp); }
    (void)_t2685;
    ;
    if (_t2685) {
        Str *_t2405 = Str_lit("Str", 3ULL);
        (void)_t2405;
        U64 _t2406; { U64 *_hp = (U64 *)Str_size(); _t2406 = *_hp; free(_hp); }
        (void)_t2406;
        U64 _t2407 = 1;
        (void)_t2407;
        Array *_va64 = Array_new(_t2405, &(U64){_t2406}, &(U64){_t2407});
        (void)_va64;
        Str_delete(_t2405, &(Bool){1});
        ;
        ;
        Str *_t2408 = I32_to_str(&(I32){type_errors});
        (void)_t2408;
        Str *_t2409 = Str_lit(" type error(s) found", 20ULL);
        (void)_t2409;
        U64 _t2410 = 0;
        (void)_t2410;
        Str *_t2411 = Str_concat(_t2408, _t2409);
        (void)_t2411;
        Str_delete(_t2408, &(Bool){1});
        Str_delete(_t2409, &(Bool){1});
        Array_set(_va64, &(U64){_t2410}, _t2411);
        ;
        Str *_t2412 = Str_lit("src/til.til:428:15", 18ULL);
        (void)_t2412;
        panic(_t2412, _va64);
        Str_delete(_t2412, &(Bool){1});
    }
    ;
    ;
    Str *_t2686 = Str_lit("test", 4ULL);
    (void)_t2686;
    Str *_t2687 = Str_lit("test", 4ULL);
    (void)_t2687;
    Bool _t2688; { Bool *_hp = (Bool *)Str_eq(command, _t2686); _t2688 = *_hp; free(_hp); }
    (void)_t2688;
    Str_delete(_t2686, &(Bool){1});
    Bool _t2689; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2687); _t2689 = *_hp; free(_hp); }
    (void)_t2689;
    Str_delete(_t2687, &(Bool){1});
    Str *_t2690 = Str_lit("pure", 4ULL);
    (void)_t2690;
    Bool _t2691 = Bool_or(_t2688, _t2689);
    (void)_t2691;
    ;
    ;
    Bool _t2692; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2690); _t2692 = *_hp; free(_hp); }
    (void)_t2692;
    Str_delete(_t2690, &(Bool){1});
    Str *_t2693 = Str_lit("pura", 4ULL);
    (void)_t2693;
    Bool _t2694 = Bool_or(_t2691, _t2692);
    (void)_t2694;
    ;
    ;
    Bool _t2695; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2693); _t2695 = *_hp; free(_hp); }
    (void)_t2695;
    Str_delete(_t2693, &(Bool){1});
    Bool run_tests = Bool_or(_t2694, _t2695);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t2696 = Str_lit("translate", 9ULL);
    (void)_t2696;
    Str *_t2697 = Str_lit("build", 5ULL);
    (void)_t2697;
    Bool _t2698; { Bool *_hp = (Bool *)Str_eq(command, _t2696); _t2698 = *_hp; free(_hp); }
    (void)_t2698;
    Str_delete(_t2696, &(Bool){1});
    Bool _t2699; { Bool *_hp = (Bool *)Str_eq(command, _t2697); _t2699 = *_hp; free(_hp); }
    (void)_t2699;
    Str_delete(_t2697, &(Bool){1});
    Bool _t2700; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2700 = *_hp; free(_hp); }
    (void)_t2700;
    Bool _t2701 = Bool_or(_t2698, _t2699);
    (void)_t2701;
    ;
    ;
    Bool is_lib_target = Bool_and(_t2700, _t2701);
    (void)is_lib_target;
    ;
    ;
    U64 _t2702; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2702 = *_hp; free(_hp); }
    (void)_t2702;
    U64 _t2703 = 0;
    (void)_t2703;
    Bool _t2704 = Bool_not(is_lib_target);
    (void)_t2704;
    ;
    Bool _t2705 = U64_eq(_t2702, _t2703);
    (void)_t2705;
    ;
    ;
    Bool _t2706 = Bool_and(_t2704, _t2705);
    (void)_t2706;
    ;
    ;
    if (_t2706) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t2707; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2707 = *_hp; free(_hp); }
    (void)_t2707;
    U64 _t2708 = 0;
    (void)_t2708;
    Bool _t2709; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2707}, &(U64){_t2708}); _t2709 = *_hp; free(_hp); }
    (void)_t2709;
    ;
    ;
    if (_t2709) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t2710 = Str_lit("Str", 3ULL);
    (void)_t2710;
    U64 _t2711; { U64 *_hp = (U64 *)Str_size(); _t2711 = *_hp; free(_hp); }
    (void)_t2711;
    Vec *user_argv = Vec_new(_t2710, &(U64){_t2711});
    (void)user_argv;
    Str_delete(_t2710, &(Bool){1});
    ;
    U64 _t2712 = 1;
    (void)_t2712;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t2712);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t2429; { U64 *_hp = (U64 *)Array_len(args); _t2429 = *_hp; free(_hp); }
        (void)_t2429;
        Bool _wcond2413; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t2429}); _wcond2413 = *_hp; free(_hp); }
        (void)_wcond2413;
        ;
        if (_wcond2413) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t2430 = Str_lit("-l", 2ULL);
        (void)_t2430;
        Bool _t2431; { Bool *_hp = (Bool *)Str_starts_with(arg, _t2430); _t2431 = *_hp; free(_hp); }
        (void)_t2431;
        Str_delete(_t2430, &(Bool){1});
        if (_t2431) {
            U64 _t2416 = 2;
            (void)_t2416;
            U64 _t2417; { U64 *_hp = (U64 *)Str_len(arg); _t2417 = *_hp; free(_hp); }
            (void)_t2417;
            Str *lib = Str_substr(arg, &(U64){_t2416}, &(U64){_t2417});
            (void)lib;
            ;
            ;
            U64 _t2418; { U64 *_hp = (U64 *)Str_len(lib); _t2418 = *_hp; free(_hp); }
            (void)_t2418;
            U64 _t2419 = 0;
            (void)_t2419;
            U64 _t2420 = 1;
            (void)_t2420;
            U64 _t2421 = U64_add(DEREF(ai), _t2420);
            (void)_t2421;
            ;
            U64 _t2422; { U64 *_hp = (U64 *)Array_len(args); _t2422 = *_hp; free(_hp); }
            (void)_t2422;
            Bool _t2423 = U64_eq(_t2418, _t2419);
            (void)_t2423;
            ;
            ;
            Bool _t2424; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2421}, &(U64){_t2422}); _t2424 = *_hp; free(_hp); }
            (void)_t2424;
            ;
            ;
            Bool _t2425 = Bool_and(_t2423, _t2424);
            (void)_t2425;
            ;
            ;
            if (_t2425) {
                U64 _t2414 = 1;
                (void)_t2414;
                U64 _t2415 = U64_add(DEREF(ai), _t2414);
                (void)_t2415;
                ;
                *ai = _t2415;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t2426 = Str_lit(" -l", 3ULL);
            (void)_t2426;
            Str *_t2427 = Str_concat(link_flags, _t2426);
            (void)_t2427;
            Str_delete(_t2426, &(Bool){1});
            link_flags = Str_concat(_t2427, lib);
            Str_delete(_t2427, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t2428 = Str_clone(arg);
            (void)_t2428;
            Vec_push(user_argv, _t2428);
        }
        ;
        U64 _t2432 = 1;
        (void)_t2432;
        U64 _t2433 = U64_add(DEREF(ai), _t2432);
        (void)_t2433;
        ;
        *ai = _t2433;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t2713; { U64 *_hp = (U64 *)Str_len(link_flags); _t2713 = *_hp; free(_hp); }
    (void)_t2713;
    U64 _t2714 = 0;
    (void)_t2714;
    Bool _t2715; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2713}, &(U64){_t2714}); _t2715 = *_hp; free(_hp); }
    (void)_t2715;
    ;
    ;
    if (_t2715) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t2716 = Str_lit("interpret", 9ULL);
    (void)_t2716;
    Str *_t2717 = Str_lit("test", 4ULL);
    (void)_t2717;
    Bool _t2718; { Bool *_hp = (Bool *)Str_eq(command, _t2716); _t2718 = *_hp; free(_hp); }
    (void)_t2718;
    Str_delete(_t2716, &(Bool){1});
    Bool _t2719; { Bool *_hp = (Bool *)Str_eq(command, _t2717); _t2719 = *_hp; free(_hp); }
    (void)_t2719;
    Str_delete(_t2717, &(Bool){1});
    Bool _t2720 = Bool_or(_t2718, _t2719);
    (void)_t2720;
    ;
    ;
    if (_t2720) {
        Str *_t2440 = Str_lit("interpret", 9ULL);
        (void)_t2440;
        Bool _t2441; { Bool *_hp = (Bool *)Str_eq(command, _t2440); _t2441 = *_hp; free(_hp); }
        (void)_t2441;
        Str_delete(_t2440, &(Bool){1});
        Bool _t2442 = Bool_and(is_lib_mode, _t2441);
        (void)_t2442;
        ;
        if (_t2442) {
            Str *_t2434 = Str_lit("Str", 3ULL);
            (void)_t2434;
            U64 _t2435; { U64 *_hp = (U64 *)Str_size(); _t2435 = *_hp; free(_hp); }
            (void)_t2435;
            U64 _t2436 = 1;
            (void)_t2436;
            Array *_va65 = Array_new(_t2434, &(U64){_t2435}, &(U64){_t2436});
            (void)_va65;
            Str_delete(_t2434, &(Bool){1});
            ;
            ;
            U64 _t2437 = 0;
            (void)_t2437;
            Str *_t2438 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t2438;
            Array_set(_va65, &(U64){_t2437}, _t2438);
            ;
            Str *_t2439 = Str_lit("src/til.til:482:19", 18ULL);
            (void)_t2439;
            panic(_t2439, _va65);
            Str_delete(_t2439, &(Bool){1});
        }
        ;
        I32 _t2443 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t2443;
        result = _t2443;
        ;
    } else {
        Str *_t2636 = Str_lit("translate", 9ULL);
        (void)_t2636;
        Str *_t2637 = Str_lit("build", 5ULL);
        (void)_t2637;
        Bool _t2638; { Bool *_hp = (Bool *)Str_eq(command, _t2636); _t2638 = *_hp; free(_hp); }
        (void)_t2638;
        Str_delete(_t2636, &(Bool){1});
        Bool _t2639; { Bool *_hp = (Bool *)Str_eq(command, _t2637); _t2639 = *_hp; free(_hp); }
        (void)_t2639;
        Str_delete(_t2637, &(Bool){1});
        Str *_t2640 = Str_lit("run", 3ULL);
        (void)_t2640;
        Bool _t2641 = Bool_or(_t2638, _t2639);
        (void)_t2641;
        ;
        ;
        Bool _t2642; { Bool *_hp = (Bool *)Str_eq(command, _t2640); _t2642 = *_hp; free(_hp); }
        (void)_t2642;
        Str_delete(_t2640, &(Bool){1});
        Bool _t2643 = Bool_or(_t2641, _t2642);
        (void)_t2643;
        ;
        ;
        if (_t2643) {
            Str *_t2569 = Str_lit("run", 3ULL);
            (void)_t2569;
            Bool _t2570; { Bool *_hp = (Bool *)Str_eq(command, _t2569); _t2570 = *_hp; free(_hp); }
            (void)_t2570;
            Str_delete(_t2569, &(Bool){1});
            Bool _t2571 = Bool_and(is_lib_mode, _t2570);
            (void)_t2571;
            ;
            if (_t2571) {
                Str *_t2444 = Str_lit("Str", 3ULL);
                (void)_t2444;
                U64 _t2445; { U64 *_hp = (U64 *)Str_size(); _t2445 = *_hp; free(_hp); }
                (void)_t2445;
                U64 _t2446 = 1;
                (void)_t2446;
                Array *_va66 = Array_new(_t2444, &(U64){_t2445}, &(U64){_t2446});
                (void)_va66;
                Str_delete(_t2444, &(Bool){1});
                ;
                ;
                U64 _t2447 = 0;
                (void)_t2447;
                Str *_t2448 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t2448;
                Array_set(_va66, &(U64){_t2447}, _t2448);
                ;
                Str *_t2449 = Str_lit("src/til.til:488:19", 18ULL);
                (void)_t2449;
                panic(_t2449, _va66);
                Str_delete(_t2449, &(Bool){1});
            }
            ;
            Str *_t2572 = Str_lit("/", 1ULL);
            (void)_t2572;
            I64 *last_slash = Str_rfind(path, _t2572);
            (void)last_slash;
            Str_delete(_t2572, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t2573 = 0;
            (void)_t2573;
            Bool _t2574; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t2573}); _t2574 = *_hp; free(_hp); }
            (void)_t2574;
            ;
            if (_t2574) {
                I64 _t2450 = 1;
                (void)_t2450;
                I64 _t2451 = I64_add(DEREF(last_slash), _t2450);
                (void)_t2451;
                ;
                U64 _t2452; { U64 *_hp = (U64 *)Str_len(path); _t2452 = *_hp; free(_hp); }
                (void)_t2452;
                U64 _t2453 = I64_to_u64(DEREF(last_slash));
                (void)_t2453;
                U64 _t2454 = U64_sub(_t2452, _t2453);
                (void)_t2454;
                ;
                ;
                U64 _t2455 = 1;
                (void)_t2455;
                U64 _t2456 = I64_to_u64(_t2451);
                (void)_t2456;
                ;
                U64 _t2457 = U64_sub(_t2454, _t2455);
                (void)_t2457;
                ;
                ;
                basename = Str_substr(path, &(U64){_t2456}, &(U64){_t2457});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t2575 = Str_lit(".til", 4ULL);
            (void)_t2575;
            Bool _t2576; { Bool *_hp = (Bool *)Str_ends_with(basename, _t2575); _t2576 = *_hp; free(_hp); }
            (void)_t2576;
            Str_delete(_t2575, &(Bool){1});
            if (_t2576) {
                U64 _t2458 = 4;
                (void)_t2458;
                U64 _t2459 = U64_sub(name_len, _t2458);
                (void)_t2459;
                ;
                name_len = _t2459;
                ;
            }
            ;
            U64 _t2577 = 0;
            (void)_t2577;
            Str *name = Str_substr(basename, &(U64){_t2577}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t2578 = Str_lit("gen/til/", 8ULL);
            (void)_t2578;
            Str *_t2579 = Str_concat(_t2578, name);
            (void)_t2579;
            Str_delete(_t2578, &(Bool){1});
            Str *_t2580 = Str_lit(".c", 2ULL);
            (void)_t2580;
            Str *c_path = Str_concat(_t2579, _t2580);
            (void)c_path;
            Str_delete(_t2579, &(Bool){1});
            Str_delete(_t2580, &(Bool){1});
            U64 _t2581; { U64 *_hp = (U64 *)Str_len(custom_c); _t2581 = *_hp; free(_hp); }
            (void)_t2581;
            U64 _t2582 = 0;
            (void)_t2582;
            Bool _t2583; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2581}, &(U64){_t2582}); _t2583 = *_hp; free(_hp); }
            (void)_t2583;
            ;
            ;
            if (_t2583) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t2584 = Str_lit("bin/til/", 8ULL);
            (void)_t2584;
            Str *bin_path = Str_concat(_t2584, name);
            (void)bin_path;
            Str_delete(_t2584, &(Bool){1});
            U64 _t2585; { U64 *_hp = (U64 *)Str_len(custom_bin); _t2585 = *_hp; free(_hp); }
            (void)_t2585;
            U64 _t2586 = 0;
            (void)_t2586;
            Bool _t2587; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2585}, &(U64){_t2586}); _t2587 = *_hp; free(_hp); }
            (void)_t2587;
            ;
            ;
            if (_t2587) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t2588 = Str_lit("run", 3ULL);
            (void)_t2588;
            Bool _t2589; { Bool *_hp = (Bool *)Str_eq(command, _t2588); _t2589 = *_hp; free(_hp); }
            (void)_t2589;
            Str_delete(_t2588, &(Bool){1});
            Bool _t2590; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2590 = *_hp; free(_hp); }
            (void)_t2590;
            Bool _t2591 = Bool_not(_t2589);
            (void)_t2591;
            ;
            Bool do_lib = Bool_and(_t2590, _t2591);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t2460 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t2460;
                I32 _t2461 = til_system(_t2460);
                (void)_t2461;
                Str_delete(_t2460, &(Bool){1});
                ;
            } else {
                Str *_t2466 = Str_lit("/", 1ULL);
                (void)_t2466;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t2466); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t2466, &(Bool){1});
                Str *_t2467 = Str_lit("/", 1ULL);
                (void)_t2467;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t2467); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t2467, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t2468 = 0;
                (void)_t2468;
                Bool _t2469; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t2468}); _t2469 = *_hp; free(_hp); }
                (void)_t2469;
                ;
                if (_t2469) {
                    U64 _t2462 = 0;
                    (void)_t2462;
                    U64 _t2463 = I64_to_u64(cp_slash);
                    (void)_t2463;
                    cp_dir = Str_substr(c_path, &(U64){_t2462}, &(U64){_t2463});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t2470 = 0;
                (void)_t2470;
                Bool _t2471; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t2470}); _t2471 = *_hp; free(_hp); }
                (void)_t2471;
                ;
                if (_t2471) {
                    U64 _t2464 = 0;
                    (void)_t2464;
                    U64 _t2465 = I64_to_u64(bp_slash);
                    (void)_t2465;
                    bp_dir = Str_substr(bin_path, &(U64){_t2464}, &(U64){_t2465});
                    ;
                    ;
                }
                ;
                ;
                Str *_t2472 = Str_lit("mkdir -p ", 9ULL);
                (void)_t2472;
                Str *_t2473 = Str_concat(_t2472, cp_dir);
                (void)_t2473;
                Str_delete(_t2472, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t2474 = Str_lit(" ", 1ULL);
                (void)_t2474;
                Str *_t2475 = Str_concat(_t2473, _t2474);
                (void)_t2475;
                Str_delete(_t2473, &(Bool){1});
                Str_delete(_t2474, &(Bool){1});
                Str *_t2476 = Str_concat(_t2475, bp_dir);
                (void)_t2476;
                Str_delete(_t2475, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t2477 = til_system(_t2476);
                (void)_t2477;
                Str_delete(_t2476, &(Bool){1});
                ;
            }
            I32 _t2592 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t2592;
            result = _t2592;
            ;
            I32 _t2593 = 0;
            (void)_t2593;
            Bool _t2594 = I32_eq(result, _t2593);
            (void)_t2594;
            ;
            Bool _t2595 = Bool_and(_t2594, do_lib);
            (void)_t2595;
            ;
            if (_t2595) {
                Str *_t2534 = Str_lit("gen/til/", 8ULL);
                (void)_t2534;
                Str *_t2535 = Str_concat(_t2534, name);
                (void)_t2535;
                Str_delete(_t2534, &(Bool){1});
                Str *_t2536 = Str_lit(".h", 2ULL);
                (void)_t2536;
                Str *h_path = Str_concat(_t2535, _t2536);
                (void)h_path;
                Str_delete(_t2535, &(Bool){1});
                Str_delete(_t2536, &(Bool){1});
                Str *_t2537 = Str_lit("gen/til/", 8ULL);
                (void)_t2537;
                Str *_t2538 = Str_concat(_t2537, name);
                (void)_t2538;
                Str_delete(_t2537, &(Bool){1});
                Str *_t2539 = Str_lit(".til", 4ULL);
                (void)_t2539;
                Str *til_path = Str_concat(_t2538, _t2539);
                (void)til_path;
                Str_delete(_t2538, &(Bool){1});
                Str_delete(_t2539, &(Bool){1});
                I32 _t2540 = build_header(ast, h_path);
                (void)_t2540;
                result = _t2540;
                ;
                I32 _t2541 = 0;
                (void)_t2541;
                Bool _t2542 = I32_eq(result, _t2541);
                (void)_t2542;
                ;
                if (_t2542) {
                    I32 _t2478 = build_til_binding(ast, til_path, name);
                    (void)_t2478;
                    result = _t2478;
                    ;
                }
                ;
                I32 _t2543 = 0;
                (void)_t2543;
                Str *_t2544 = Str_lit("translate", 9ULL);
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
                    Str *_t2479 = Str_lit("Str", 3ULL);
                    (void)_t2479;
                    U64 _t2480; { U64 *_hp = (U64 *)Str_size(); _t2480 = *_hp; free(_hp); }
                    (void)_t2480;
                    U64 _t2481 = 1;
                    (void)_t2481;
                    Array *_va67 = Array_new(_t2479, &(U64){_t2480}, &(U64){_t2481});
                    (void)_va67;
                    Str_delete(_t2479, &(Bool){1});
                    ;
                    ;
                    Str *_t2482 = Str_lit("Generated: ", 11ULL);
                    (void)_t2482;
                    U64 _t2483 = 0;
                    (void)_t2483;
                    Str *_t2484 = Str_concat(_t2482, c_path);
                    (void)_t2484;
                    Str_delete(_t2482, &(Bool){1});
                    Array_set(_va67, &(U64){_t2483}, _t2484);
                    ;
                    println(_va67);
                    Str *_t2485 = Str_lit("Str", 3ULL);
                    (void)_t2485;
                    U64 _t2486; { U64 *_hp = (U64 *)Str_size(); _t2486 = *_hp; free(_hp); }
                    (void)_t2486;
                    U64 _t2487 = 1;
                    (void)_t2487;
                    Array *_va68 = Array_new(_t2485, &(U64){_t2486}, &(U64){_t2487});
                    (void)_va68;
                    Str_delete(_t2485, &(Bool){1});
                    ;
                    ;
                    Str *_t2488 = Str_lit("Generated: ", 11ULL);
                    (void)_t2488;
                    U64 _t2489 = 0;
                    (void)_t2489;
                    Str *_t2490 = Str_concat(_t2488, h_path);
                    (void)_t2490;
                    Str_delete(_t2488, &(Bool){1});
                    Array_set(_va68, &(U64){_t2489}, _t2490);
                    ;
                    println(_va68);
                    Str *_t2491 = Str_lit("Str", 3ULL);
                    (void)_t2491;
                    U64 _t2492; { U64 *_hp = (U64 *)Str_size(); _t2492 = *_hp; free(_hp); }
                    (void)_t2492;
                    U64 _t2493 = 1;
                    (void)_t2493;
                    Array *_va69 = Array_new(_t2491, &(U64){_t2492}, &(U64){_t2493});
                    (void)_va69;
                    Str_delete(_t2491, &(Bool){1});
                    ;
                    ;
                    Str *_t2494 = Str_lit("Generated: ", 11ULL);
                    (void)_t2494;
                    U64 _t2495 = 0;
                    (void)_t2495;
                    Str *_t2496 = Str_concat(_t2494, til_path);
                    (void)_t2496;
                    Str_delete(_t2494, &(Bool){1});
                    Array_set(_va69, &(U64){_t2495}, _t2496);
                    ;
                    println(_va69);
                }
                ;
                I32 _t2548 = 0;
                (void)_t2548;
                Str *_t2549 = Str_lit("build", 5ULL);
                (void)_t2549;
                Bool _t2550 = I32_eq(result, _t2548);
                (void)_t2550;
                ;
                Bool _t2551; { Bool *_hp = (Bool *)Str_eq(command, _t2549); _t2551 = *_hp; free(_hp); }
                (void)_t2551;
                Str_delete(_t2549, &(Bool){1});
                Bool _t2552 = Bool_and(_t2550, _t2551);
                (void)_t2552;
                ;
                ;
                if (_t2552) {
                    I32 _t2531 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t2531;
                    result = _t2531;
                    ;
                    I32 _t2532 = 0;
                    (void)_t2532;
                    Bool _t2533 = I32_eq(result, _t2532);
                    (void)_t2533;
                    ;
                    if (_t2533) {
                        Str *_t2497 = Str_lit("Str", 3ULL);
                        (void)_t2497;
                        U64 _t2498; { U64 *_hp = (U64 *)Str_size(); _t2498 = *_hp; free(_hp); }
                        (void)_t2498;
                        U64 _t2499 = 1;
                        (void)_t2499;
                        Array *_va70 = Array_new(_t2497, &(U64){_t2498}, &(U64){_t2499});
                        (void)_va70;
                        Str_delete(_t2497, &(Bool){1});
                        ;
                        ;
                        Str *_t2500 = Str_lit("Generated: ", 11ULL);
                        (void)_t2500;
                        U64 _t2501 = 0;
                        (void)_t2501;
                        Str *_t2502 = Str_concat(_t2500, c_path);
                        (void)_t2502;
                        Str_delete(_t2500, &(Bool){1});
                        Array_set(_va70, &(U64){_t2501}, _t2502);
                        ;
                        println(_va70);
                        Str *_t2503 = Str_lit("Str", 3ULL);
                        (void)_t2503;
                        U64 _t2504; { U64 *_hp = (U64 *)Str_size(); _t2504 = *_hp; free(_hp); }
                        (void)_t2504;
                        U64 _t2505 = 1;
                        (void)_t2505;
                        Array *_va71 = Array_new(_t2503, &(U64){_t2504}, &(U64){_t2505});
                        (void)_va71;
                        Str_delete(_t2503, &(Bool){1});
                        ;
                        ;
                        Str *_t2506 = Str_lit("Generated: ", 11ULL);
                        (void)_t2506;
                        U64 _t2507 = 0;
                        (void)_t2507;
                        Str *_t2508 = Str_concat(_t2506, h_path);
                        (void)_t2508;
                        Str_delete(_t2506, &(Bool){1});
                        Array_set(_va71, &(U64){_t2507}, _t2508);
                        ;
                        println(_va71);
                        Str *_t2509 = Str_lit("Str", 3ULL);
                        (void)_t2509;
                        U64 _t2510; { U64 *_hp = (U64 *)Str_size(); _t2510 = *_hp; free(_hp); }
                        (void)_t2510;
                        U64 _t2511 = 1;
                        (void)_t2511;
                        Array *_va72 = Array_new(_t2509, &(U64){_t2510}, &(U64){_t2511});
                        (void)_va72;
                        Str_delete(_t2509, &(Bool){1});
                        ;
                        ;
                        Str *_t2512 = Str_lit("Generated: ", 11ULL);
                        (void)_t2512;
                        U64 _t2513 = 0;
                        (void)_t2513;
                        Str *_t2514 = Str_concat(_t2512, til_path);
                        (void)_t2514;
                        Str_delete(_t2512, &(Bool){1});
                        Array_set(_va72, &(U64){_t2513}, _t2514);
                        ;
                        println(_va72);
                        Str *_t2515 = Str_lit("Str", 3ULL);
                        (void)_t2515;
                        U64 _t2516; { U64 *_hp = (U64 *)Str_size(); _t2516 = *_hp; free(_hp); }
                        (void)_t2516;
                        U64 _t2517 = 1;
                        (void)_t2517;
                        Array *_va73 = Array_new(_t2515, &(U64){_t2516}, &(U64){_t2517});
                        (void)_va73;
                        Str_delete(_t2515, &(Bool){1});
                        ;
                        ;
                        Str *_t2518 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2518;
                        Str *_t2519 = Str_concat(_t2518, name);
                        (void)_t2519;
                        Str_delete(_t2518, &(Bool){1});
                        Str *_t2520 = Str_lit(".so", 3ULL);
                        (void)_t2520;
                        U64 _t2521 = 0;
                        (void)_t2521;
                        Str *_t2522 = Str_concat(_t2519, _t2520);
                        (void)_t2522;
                        Str_delete(_t2519, &(Bool){1});
                        Str_delete(_t2520, &(Bool){1});
                        Array_set(_va73, &(U64){_t2521}, _t2522);
                        ;
                        println(_va73);
                        Str *_t2523 = Str_lit("Str", 3ULL);
                        (void)_t2523;
                        U64 _t2524; { U64 *_hp = (U64 *)Str_size(); _t2524 = *_hp; free(_hp); }
                        (void)_t2524;
                        U64 _t2525 = 1;
                        (void)_t2525;
                        Array *_va74 = Array_new(_t2523, &(U64){_t2524}, &(U64){_t2525});
                        (void)_va74;
                        Str_delete(_t2523, &(Bool){1});
                        ;
                        ;
                        Str *_t2526 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2526;
                        Str *_t2527 = Str_concat(_t2526, name);
                        (void)_t2527;
                        Str_delete(_t2526, &(Bool){1});
                        Str *_t2528 = Str_lit(".a", 2ULL);
                        (void)_t2528;
                        U64 _t2529 = 0;
                        (void)_t2529;
                        Str *_t2530 = Str_concat(_t2527, _t2528);
                        (void)_t2530;
                        Str_delete(_t2527, &(Bool){1});
                        Str_delete(_t2528, &(Bool){1});
                        Array_set(_va74, &(U64){_t2529}, _t2530);
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
            I32 _t2596 = 0;
            (void)_t2596;
            Bool _t2597 = I32_eq(result, _t2596);
            (void)_t2597;
            ;
            Bool _t2598 = Bool_not(do_lib);
            (void)_t2598;
            Str *_t2599 = Str_lit("translate", 9ULL);
            (void)_t2599;
            Bool _t2600 = Bool_and(_t2597, _t2598);
            (void)_t2600;
            ;
            ;
            Bool _t2601; { Bool *_hp = (Bool *)Str_eq(command, _t2599); _t2601 = *_hp; free(_hp); }
            (void)_t2601;
            Str_delete(_t2599, &(Bool){1});
            Bool _t2602 = Bool_and(_t2600, _t2601);
            (void)_t2602;
            ;
            ;
            if (_t2602) {
                Str *_t2553 = Str_lit("Str", 3ULL);
                (void)_t2553;
                U64 _t2554; { U64 *_hp = (U64 *)Str_size(); _t2554 = *_hp; free(_hp); }
                (void)_t2554;
                U64 _t2555 = 1;
                (void)_t2555;
                Array *_va75 = Array_new(_t2553, &(U64){_t2554}, &(U64){_t2555});
                (void)_va75;
                Str_delete(_t2553, &(Bool){1});
                ;
                ;
                Str *_t2556 = Str_lit("Generated: ", 11ULL);
                (void)_t2556;
                U64 _t2557 = 0;
                (void)_t2557;
                Str *_t2558 = Str_concat(_t2556, c_path);
                (void)_t2558;
                Str_delete(_t2556, &(Bool){1});
                Array_set(_va75, &(U64){_t2557}, _t2558);
                ;
                println(_va75);
            }
            ;
            I32 _t2603 = 0;
            (void)_t2603;
            Bool _t2604 = I32_eq(result, _t2603);
            (void)_t2604;
            ;
            Bool _t2605 = Bool_not(do_lib);
            (void)_t2605;
            Str *_t2606 = Str_lit("translate", 9ULL);
            (void)_t2606;
            Bool _t2607; { Bool *_hp = (Bool *)Str_eq(command, _t2606); _t2607 = *_hp; free(_hp); }
            (void)_t2607;
            Str_delete(_t2606, &(Bool){1});
            Bool _t2608 = Bool_and(_t2604, _t2605);
            (void)_t2608;
            ;
            ;
            Bool _t2609 = Bool_not(_t2607);
            (void)_t2609;
            ;
            Bool _t2610 = Bool_and(_t2608, _t2609);
            (void)_t2610;
            ;
            ;
            if (_t2610) {
                I32 _t2559 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t2559;
                result = _t2559;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t2611 = 0;
            (void)_t2611;
            Bool _t2612 = I32_eq(result, _t2611);
            (void)_t2612;
            ;
            Bool _t2613 = Bool_not(do_lib);
            (void)_t2613;
            ;
            Str *_t2614 = Str_lit("run", 3ULL);
            (void)_t2614;
            Bool _t2615 = Bool_and(_t2612, _t2613);
            (void)_t2615;
            ;
            ;
            Bool _t2616; { Bool *_hp = (Bool *)Str_eq(command, _t2614); _t2616 = *_hp; free(_hp); }
            (void)_t2616;
            Str_delete(_t2614, &(Bool){1});
            Bool _t2617 = Bool_and(_t2615, _t2616);
            (void)_t2617;
            ;
            ;
            if (_t2617) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t2561; { U64 *_hp = (U64 *)Vec_len(user_argv); _t2561 = *_hp; free(_hp); }
                    (void)_t2561;
                    Bool _wcond2560; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t2561}); _wcond2560 = *_hp; free(_hp); }
                    (void)_wcond2560;
                    ;
                    if (_wcond2560) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t2562 = Str_lit(" '", 2ULL);
                    (void)_t2562;
                    Str *_t2563 = Str_concat(cmd, _t2562);
                    (void)_t2563;
                    Str_delete(_t2562, &(Bool){1});
                    Str *_t2564 = Str_concat(_t2563, uarg);
                    (void)_t2564;
                    Str_delete(_t2563, &(Bool){1});
                    Str *_t2565 = Str_lit("'", 1ULL);
                    (void)_t2565;
                    cmd = Str_concat(_t2564, _t2565);
                    Str_delete(_t2564, &(Bool){1});
                    Str_delete(_t2565, &(Bool){1});
                    U64 _t2566 = 1;
                    (void)_t2566;
                    U64 _t2567 = U64_add(DEREF(ui), _t2566);
                    (void)_t2567;
                    ;
                    *ui = _t2567;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t2568 = til_system(cmd);
                (void)_t2568;
                Str_delete(cmd, &(Bool){1});
                result = _t2568;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t2634 = Str_lit("ast", 3ULL);
            (void)_t2634;
            Bool _t2635; { Bool *_hp = (Bool *)Str_eq(command, _t2634); _t2635 = *_hp; free(_hp); }
            (void)_t2635;
            Str_delete(_t2634, &(Bool){1});
            if (_t2635) {
                Str *_t2618 = Str_lit("Str", 3ULL);
                (void)_t2618;
                U64 _t2619; { U64 *_hp = (U64 *)Str_size(); _t2619 = *_hp; free(_hp); }
                (void)_t2619;
                U64 _t2620 = 1;
                (void)_t2620;
                Array *_va76 = Array_new(_t2618, &(U64){_t2619}, &(U64){_t2620});
                (void)_va76;
                Str_delete(_t2618, &(Bool){1});
                ;
                ;
                Str *_t2621 = Str_lit("mode: ", 6ULL);
                (void)_t2621;
                U64 _t2622 = 0;
                (void)_t2622;
                Str *_t2623 = Str_concat(_t2621, &cur_mode->name);
                (void)_t2623;
                Str_delete(_t2621, &(Bool){1});
                Array_set(_va76, &(U64){_t2622}, _t2623);
                ;
                println(_va76);
                U32 _t2624 = 0;
                (void)_t2624;
                ast_print(ast, _t2624);
                ;
            } else {
                Str *_t2625 = Str_lit("Str", 3ULL);
                (void)_t2625;
                U64 _t2626; { U64 *_hp = (U64 *)Str_size(); _t2626 = *_hp; free(_hp); }
                (void)_t2626;
                U64 _t2627 = 1;
                (void)_t2627;
                Array *_va77 = Array_new(_t2625, &(U64){_t2626}, &(U64){_t2627});
                (void)_va77;
                Str_delete(_t2625, &(Bool){1});
                ;
                ;
                Str *_t2628 = Str_lit("error: unknown command '", 24ULL);
                (void)_t2628;
                Str *_t2629 = Str_concat(_t2628, command);
                (void)_t2629;
                Str_delete(_t2628, &(Bool){1});
                Str *_t2630 = Str_lit("'", 1ULL);
                (void)_t2630;
                U64 _t2631 = 0;
                (void)_t2631;
                Str *_t2632 = Str_concat(_t2629, _t2630);
                (void)_t2632;
                Str_delete(_t2629, &(Bool){1});
                Str_delete(_t2630, &(Bool){1});
                Array_set(_va77, &(U64){_t2631}, _t2632);
                ;
                println(_va77);
                usage();
                I32 _t2633 = 1;
                (void)_t2633;
                result = _t2633;
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
    I64 _t2721 = I32_to_i64(result);
    (void)_t2721;
    ;
    exit(_t2721);
    ;
    return 0;
}

