#include "til_til.h"

Mode * Mode_clone(Mode * self) {
    (void)self;
    Bool _t2109 = Bool_clone(&self->needs_main);
    (void)_t2109;
    Bool _t2110 = Bool_clone(&self->decls_only);
    (void)_t2110;
    Bool _t2111 = Bool_clone(&self->is_pure);
    (void)_t2111;
    Bool _t2112 = Bool_clone(&self->debug_prints);
    (void)_t2112;
    Mode *_t2113 = malloc(sizeof(Mode));
    { Str *_ca = Str_clone(&self->name); _t2113->name = *_ca; free(_ca); }
    _t2113->needs_main = _t2109;
    _t2113->decls_only = _t2110;
    { Str *_ca = Str_clone(&self->auto_import); _t2113->auto_import = *_ca; free(_ca); }
    _t2113->is_pure = _t2111;
    _t2113->debug_prints = _t2112;
    (void)_t2113;
    ;
    ;
    ;
    ;
    return _t2113;
}

void Mode_delete(Mode * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (!self) return;
    Bool _t2114 = 0;
    (void)_t2114;
    Str_delete(&self->name, &(Bool){_t2114});
    ;
    Bool _t2115 = 0;
    (void)_t2115;
    Bool_delete(&self->needs_main, &(Bool){_t2115});
    ;
    Bool _t2116 = 0;
    (void)_t2116;
    Bool_delete(&self->decls_only, &(Bool){_t2116});
    ;
    Bool _t2117 = 0;
    (void)_t2117;
    Str_delete(&self->auto_import, &(Bool){_t2117});
    ;
    Bool _t2118 = 0;
    (void)_t2118;
    Bool_delete(&self->is_pure, &(Bool){_t2118});
    ;
    Bool _t2119 = 0;
    (void)_t2119;
    Bool_delete(&self->debug_prints, &(Bool){_t2119});
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
    TypeScope *_t2121 = malloc(sizeof(TypeScope));
    (void)_t2121;
    return _t2121;
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
    Str *_t2152 = Str_lit("Str", 3ULL);
    (void)_t2152;
    U64 _t2153; { U64 *_hp = (U64 *)Str_size(); _t2153 = *_hp; free(_hp); }
    (void)_t2153;
    Vec *paths = Vec_new(_t2152, &(U64){_t2153});
    (void)paths;
    Str_delete(_t2152, &(Bool){1});
    ;
    Vec *kept = expr_vec_new();
    (void)kept;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2127 = expr_nchildren(body);
        (void)_t2127;
        Bool _wcond2123; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2127}); _wcond2123 = *_hp; free(_hp); }
        (void)_wcond2123;
        ;
        if (_wcond2123) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(body, DEREF(i));
        (void)stmt;
        I32 _t2128 = expr_get_tag(stmt);
        (void)_t2128;
        U32 _t2129 = expr_nchildren(stmt);
        (void)_t2129;
        U32 _t2130 = 2;
        (void)_t2130;
        Bool _t2131 = I32_eq(_t2128, DEREF(NODE_FCALL));
        (void)_t2131;
        ;
        Bool _t2132 = U32_eq(_t2129, _t2130);
        (void)_t2132;
        ;
        ;
        U32 *_t2133 = malloc(sizeof(U32));
        *_t2133 = 0;
        (void)_t2133;
        Expr *_t2134 = expr_get_child(stmt, DEREF(_t2133));
        (void)_t2134;
        I32 _t2135 = expr_get_tag(_t2134);
        (void)_t2135;
        U32_delete(_t2133, &(Bool){1});
        Bool _t2136 = Bool_and(_t2131, _t2132);
        (void)_t2136;
        ;
        ;
        Bool _t2137 = I32_eq(_t2135, DEREF(NODE_IDENT));
        (void)_t2137;
        ;
        U32 *_t2138 = malloc(sizeof(U32));
        *_t2138 = 0;
        (void)_t2138;
        Expr *_t2139 = expr_get_child(stmt, DEREF(_t2138));
        (void)_t2139;
        Str *_t2140 = expr_get_str_val(_t2139);
        (void)_t2140;
        Str *_t2141 = Str_lit("import", 6ULL);
        (void)_t2141;
        Bool _t2142 = Bool_and(_t2136, _t2137);
        (void)_t2142;
        ;
        ;
        Bool _t2143; { Bool *_hp = (Bool *)Str_eq(_t2140, _t2141); _t2143 = *_hp; free(_hp); }
        (void)_t2143;
        U32_delete(_t2138, &(Bool){1});
        Str_delete(_t2141, &(Bool){1});
        U32 *_t2144 = malloc(sizeof(U32));
        *_t2144 = 1;
        (void)_t2144;
        Expr *_t2145 = expr_get_child(stmt, DEREF(_t2144));
        (void)_t2145;
        I32 _t2146 = expr_get_tag(_t2145);
        (void)_t2146;
        U32_delete(_t2144, &(Bool){1});
        Bool _t2147 = Bool_and(_t2142, _t2143);
        (void)_t2147;
        ;
        ;
        Bool _t2148 = I32_eq(_t2146, DEREF(NODE_LITERAL_STR));
        (void)_t2148;
        ;
        Bool _t2149 = Bool_and(_t2147, _t2148);
        (void)_t2149;
        ;
        ;
        if (_t2149) {
            U32 *_t2124 = malloc(sizeof(U32));
            *_t2124 = 1;
            (void)_t2124;
            Expr *_t2125 = expr_get_child(stmt, DEREF(_t2124));
            (void)_t2125;
            Str *path = expr_get_str_val(_t2125);
            (void)path;
            Str *_t2126 = Str_clone(path);
            (void)_t2126;
            U32_delete(_t2124, &(Bool){1});
            Vec_push(paths, _t2126);
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2150 = 1;
        (void)_t2150;
        U32 _t2151 = U32_add(DEREF(i), _t2150);
        (void)_t2151;
        ;
        *i = _t2151;
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
        U64 _fi2154 = 0;
        (void)_fi2154;
        while (1) {
            U64 _t2184 = 0;
            (void)_t2184;
            U64 _t2185; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2185 = *_hp; free(_hp); }
            (void)_t2185;
            Range *_t2186 = Range_new(_t2184, _t2185);
            (void)_t2186;
            ;
            ;
            U64 _t2187; { U64 *_hp = (U64 *)Range_len(_t2186); _t2187 = *_hp; free(_hp); }
            (void)_t2187;
            Range_delete(_t2186, &(Bool){1});
            Bool _wcond2155; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2154}, &(U64){_t2187}); _wcond2155 = *_hp; free(_hp); }
            (void)_wcond2155;
            ;
            if (_wcond2155) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2188 = 0;
            (void)_t2188;
            U64 _t2189; { U64 *_hp = (U64 *)Vec_len(import_paths); _t2189 = *_hp; free(_hp); }
            (void)_t2189;
            Range *_t2190 = Range_new(_t2188, _t2189);
            (void)_t2190;
            ;
            ;
            U64 *i = Range_get(_t2190, _fi2154);
            (void)i;
            Range_delete(_t2190, &(Bool){1});
            U64 _t2191 = 1;
            (void)_t2191;
            U64 _t2192 = U64_add(_fi2154, _t2191);
            (void)_t2192;
            ;
            _fi2154 = _t2192;
            ;
            Str *import_path = Vec_get(import_paths, i);
            (void)import_path;
            Str *_t2193 = Str_lit("/", 1ULL);
            (void)_t2193;
            Str *_t2194 = Str_concat(base_dir, _t2193);
            (void)_t2194;
            Str_delete(_t2193, &(Bool){1});
            Str *try_path = Str_concat(_t2194, import_path);
            (void)try_path;
            Str_delete(_t2194, &(Bool){1});
            Str *abs = til_realpath(try_path);
            (void)abs;
            Str *_t2195 = Str_lit("", 0ULL);
            (void)_t2195;
            U64 _t2196; { U64 *_hp = (U64 *)Str_len(lib_dir); _t2196 = *_hp; free(_hp); }
            (void)_t2196;
            U64 _t2197 = 0;
            (void)_t2197;
            Bool _t2198; { Bool *_hp = (Bool *)Str_eq(abs, _t2195); _t2198 = *_hp; free(_hp); }
            (void)_t2198;
            Str_delete(_t2195, &(Bool){1});
            Bool _t2199; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2196}, &(U64){_t2197}); _t2199 = *_hp; free(_hp); }
            (void)_t2199;
            ;
            ;
            Bool _t2200 = Bool_and(_t2198, _t2199);
            (void)_t2200;
            ;
            ;
            if (_t2200) {
                Str *_t2156 = Str_lit("/", 1ULL);
                (void)_t2156;
                Str *_t2157 = Str_concat(lib_dir, _t2156);
                (void)_t2157;
                Str_delete(_t2156, &(Bool){1});
                try_path = Str_concat(_t2157, import_path);
                Str_delete(_t2157, &(Bool){1});
                abs = til_realpath(try_path);
            }
            ;
            Str_delete(try_path, &(Bool){1});
            Str *_t2201 = Str_lit("", 0ULL);
            (void)_t2201;
            Bool _t2202; { Bool *_hp = (Bool *)Str_eq(abs, _t2201); _t2202 = *_hp; free(_hp); }
            (void)_t2202;
            Str_delete(_t2201, &(Bool){1});
            if (_t2202) {
                Str *_t2158 = Str_lit("Str", 3ULL);
                (void)_t2158;
                U64 _t2159; { U64 *_hp = (U64 *)Str_size(); _t2159 = *_hp; free(_hp); }
                (void)_t2159;
                U64 _t2160 = 1;
                (void)_t2160;
                Array *_va50 = Array_new(_t2158, &(U64){_t2159}, &(U64){_t2160});
                (void)_va50;
                Str_delete(_t2158, &(Bool){1});
                ;
                ;
                Str *_t2161 = Str_lit("error: could not find import '", 30ULL);
                (void)_t2161;
                Str *_t2162 = Str_concat(_t2161, import_path);
                (void)_t2162;
                Str_delete(_t2161, &(Bool){1});
                Str *_t2163 = Str_lit("' (from ", 8ULL);
                (void)_t2163;
                Str *_t2164 = Str_concat(_t2162, _t2163);
                (void)_t2164;
                Str_delete(_t2162, &(Bool){1});
                Str_delete(_t2163, &(Bool){1});
                Str *_t2165 = Str_concat(_t2164, base_dir);
                (void)_t2165;
                Str_delete(_t2164, &(Bool){1});
                Str *_t2166 = Str_lit("/)", 2ULL);
                (void)_t2166;
                U64 _t2167 = 0;
                (void)_t2167;
                Str *_t2168 = Str_concat(_t2165, _t2166);
                (void)_t2168;
                Str_delete(_t2165, &(Bool){1});
                Str_delete(_t2166, &(Bool){1});
                Array_set(_va50, &(U64){_t2167}, _t2168);
                ;
                println(_va50);
                I64 _t2169 = 1;
                (void)_t2169;
                ;
                Str_delete(abs, &(Bool){1});
                U64_delete(i, &(Bool){1});
                ;
                { I32 *_r = malloc(sizeof(I32)); *_r = _t2169; return _r; }
            }
            ;
            U64_delete(i, &(Bool){1});
            Bool _t2203 = til_set_has(resolved_set, abs);
            (void)_t2203;
            if (_t2203) {
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
            U64 _t2204; { U64 *_hp = (U64 *)Str_len(abs); _t2204 = *_hp; free(_hp); }
            (void)_t2204;
            U64 _t2205 = 1;
            (void)_t2205;
            U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2204, _t2205);
            (void)last_slash;
            ;
            ;
            while (1) {
                U64 _t2171 = 0;
                (void)_t2171;
                U8 *_t2172 = Str_get(abs, last_slash);
                (void)_t2172;
                U8 _t2173 = 47;
                (void)_t2173;
                Bool _t2174; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2171}); _t2174 = *_hp; free(_hp); }
                (void)_t2174;
                ;
                Bool _t2175; { Bool *_hp = (Bool *)U8_neq(_t2172, &(U8){_t2173}); _t2175 = *_hp; free(_hp); }
                (void)_t2175;
                ;
                Bool _wcond2170 = Bool_and(_t2174, _t2175);
                (void)_wcond2170;
                ;
                ;
                if (_wcond2170) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2176 = 1;
                (void)_t2176;
                U64 _t2177 = U64_sub(DEREF(last_slash), _t2176);
                (void)_t2177;
                ;
                *last_slash = _t2177;
                ;
            }
            Str *sub_dir = til_str_left(abs, DEREF(last_slash));
            (void)sub_dir;
            Str_delete(abs, &(Bool){1});
            U64_delete(last_slash, &(Bool){1});
            U64 _t2206; { U64 *_hp = (U64 *)Vec_len(sub_imports); _t2206 = *_hp; free(_hp); }
            (void)_t2206;
            U64 _t2207 = 0;
            (void)_t2207;
            Bool _t2208; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2206}, &(U64){_t2207}); _t2208 = *_hp; free(_hp); }
            (void)_t2208;
            ;
            ;
            if (_t2208) {
                I32 err; { I32 *_hp = (I32 *)resolve_imports(sub_imports, sub_dir, resolved_set, stack, merged, lib_dir); err = *_hp; free(_hp); }
                (void)err;
                I32 _t2178 = 0;
                (void)_t2178;
                Bool _t2179; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2178}); _t2179 = *_hp; free(_hp); }
                (void)_t2179;
                ;
                if (_t2179) {
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
                U32 _t2181 = expr_nchildren(sub_ast);
                (void)_t2181;
                Bool _wcond2180; { Bool *_hp = (Bool *)U32_lt(k, &(U32){_t2181}); _wcond2180 = *_hp; free(_hp); }
                (void)_wcond2180;
                ;
                if (_wcond2180) {
                } else {
                    ;
                    break;
                }
                ;
                Expr *ch = expr_get_child(sub_ast, DEREF(k));
                (void)ch;
                expr_vec_push(merged, ch);
                U32 _t2182 = 1;
                (void)_t2182;
                U32 _t2183 = U32_add(DEREF(k), _t2182);
                (void)_t2183;
                ;
                *k = _t2183;
                ;
            }
            U32_delete(k, &(Bool){1});
            Expr_delete(sub_ast, &(Bool){1});
        }
        ;
    }
    I64 _t2209 = 0;
    (void)_t2209;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t2209; return _r; }
}

void usage(void) {
    Str *_t2210 = Str_lit("Str", 3ULL);
    (void)_t2210;
    U64 _t2211; { U64 *_hp = (U64 *)Str_size(); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    U64 _t2212 = 1;
    (void)_t2212;
    Array *_va51 = Array_new(_t2210, &(U64){_t2211}, &(U64){_t2212});
    (void)_va51;
    Str_delete(_t2210, &(Bool){1});
    ;
    ;
    U64 _t2213 = 0;
    (void)_t2213;
    Str *_t2214 = Str_lit("Usage: til <command> <path>", 27ULL);
    (void)_t2214;
    Array_set(_va51, &(U64){_t2213}, _t2214);
    ;
    println(_va51);
    Str *_t2215 = Str_lit("Str", 3ULL);
    (void)_t2215;
    U64 _t2216; { U64 *_hp = (U64 *)Str_size(); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    U64 _t2217 = 1;
    (void)_t2217;
    Array *_va52 = Array_new(_t2215, &(U64){_t2216}, &(U64){_t2217});
    (void)_va52;
    Str_delete(_t2215, &(Bool){1});
    ;
    ;
    U64 _t2218 = 0;
    (void)_t2218;
    Str *_t2219 = Str_lit("", 0ULL);
    (void)_t2219;
    Array_set(_va52, &(U64){_t2218}, _t2219);
    ;
    println(_va52);
    Str *_t2220 = Str_lit("Str", 3ULL);
    (void)_t2220;
    U64 _t2221; { U64 *_hp = (U64 *)Str_size(); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    U64 _t2222 = 1;
    (void)_t2222;
    Array *_va53 = Array_new(_t2220, &(U64){_t2221}, &(U64){_t2222});
    (void)_va53;
    Str_delete(_t2220, &(Bool){1});
    ;
    ;
    U64 _t2223 = 0;
    (void)_t2223;
    Str *_t2224 = Str_lit("Commands:", 9ULL);
    (void)_t2224;
    Array_set(_va53, &(U64){_t2223}, _t2224);
    ;
    println(_va53);
    Str *_t2225 = Str_lit("Str", 3ULL);
    (void)_t2225;
    U64 _t2226; { U64 *_hp = (U64 *)Str_size(); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    U64 _t2227 = 1;
    (void)_t2227;
    Array *_va54 = Array_new(_t2225, &(U64){_t2226}, &(U64){_t2227});
    (void)_va54;
    Str_delete(_t2225, &(Bool){1});
    ;
    ;
    U64 _t2228 = 0;
    (void)_t2228;
    Str *_t2229 = Str_lit("  interpret  Read and interpret a .til file", 43ULL);
    (void)_t2229;
    Array_set(_va54, &(U64){_t2228}, _t2229);
    ;
    println(_va54);
    Str *_t2230 = Str_lit("Str", 3ULL);
    (void)_t2230;
    U64 _t2231; { U64 *_hp = (U64 *)Str_size(); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    U64 _t2232 = 1;
    (void)_t2232;
    Array *_va55 = Array_new(_t2230, &(U64){_t2231}, &(U64){_t2232});
    (void)_va55;
    Str_delete(_t2230, &(Bool){1});
    ;
    ;
    U64 _t2233 = 0;
    (void)_t2233;
    Str *_t2234 = Str_lit("  translate  Generate C source (no compilation)", 47ULL);
    (void)_t2234;
    Array_set(_va55, &(U64){_t2233}, _t2234);
    ;
    println(_va55);
    Str *_t2235 = Str_lit("Str", 3ULL);
    (void)_t2235;
    U64 _t2236; { U64 *_hp = (U64 *)Str_size(); _t2236 = *_hp; free(_hp); }
    (void)_t2236;
    U64 _t2237 = 1;
    (void)_t2237;
    Array *_va56 = Array_new(_t2235, &(U64){_t2236}, &(U64){_t2237});
    (void)_va56;
    Str_delete(_t2235, &(Bool){1});
    ;
    ;
    U64 _t2238 = 0;
    (void)_t2238;
    Str *_t2239 = Str_lit("  build      Compile a .til file to a binary", 44ULL);
    (void)_t2239;
    Array_set(_va56, &(U64){_t2238}, _t2239);
    ;
    println(_va56);
    Str *_t2240 = Str_lit("Str", 3ULL);
    (void)_t2240;
    U64 _t2241; { U64 *_hp = (U64 *)Str_size(); _t2241 = *_hp; free(_hp); }
    (void)_t2241;
    U64 _t2242 = 1;
    (void)_t2242;
    Array *_va57 = Array_new(_t2240, &(U64){_t2241}, &(U64){_t2242});
    (void)_va57;
    Str_delete(_t2240, &(Bool){1});
    ;
    ;
    U64 _t2243 = 0;
    (void)_t2243;
    Str *_t2244 = Str_lit("  run        Compile and run a .til file", 40ULL);
    (void)_t2244;
    Array_set(_va57, &(U64){_t2243}, _t2244);
    ;
    println(_va57);
    Str *_t2245 = Str_lit("Str", 3ULL);
    (void)_t2245;
    U64 _t2246; { U64 *_hp = (U64 *)Str_size(); _t2246 = *_hp; free(_hp); }
    (void)_t2246;
    U64 _t2247 = 1;
    (void)_t2247;
    Array *_va58 = Array_new(_t2245, &(U64){_t2246}, &(U64){_t2247});
    (void)_va58;
    Str_delete(_t2245, &(Bool){1});
    ;
    ;
    U64 _t2248 = 0;
    (void)_t2248;
    Str *_t2249 = Str_lit("  test       Run test functions in a .til file", 46ULL);
    (void)_t2249;
    Array_set(_va58, &(U64){_t2248}, _t2249);
    ;
    println(_va58);
    Str *_t2250 = Str_lit("Str", 3ULL);
    (void)_t2250;
    U64 _t2251; { U64 *_hp = (U64 *)Str_size(); _t2251 = *_hp; free(_hp); }
    (void)_t2251;
    U64 _t2252 = 1;
    (void)_t2252;
    Array *_va59 = Array_new(_t2250, &(U64){_t2251}, &(U64){_t2252});
    (void)_va59;
    Str_delete(_t2250, &(Bool){1});
    ;
    ;
    U64 _t2253 = 0;
    (void)_t2253;
    Str *_t2254 = Str_lit("  help       Print this message", 31ULL);
    (void)_t2254;
    Array_set(_va59, &(U64){_t2253}, _t2254);
    ;
    println(_va59);
}

void mark_core(Expr * e) {
    (void)e;
    Bool _t2260 = 1;
    (void)_t2260;
    e->is_core = _t2260;
    ;
    U32 *i = malloc(sizeof(U32));
    *i = 0;
    (void)i;
    while (1) {
        U32 _t2256 = expr_nchildren(e);
        (void)_t2256;
        Bool _wcond2255; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2256}); _wcond2255 = *_hp; free(_hp); }
        (void)_wcond2255;
        ;
        if (_wcond2255) {
        } else {
            ;
            break;
        }
        ;
        Expr *_t2257 = expr_get_child(e, DEREF(i));
        (void)_t2257;
        mark_core(_t2257);
        U32 _t2258 = 1;
        (void)_t2258;
        U32 _t2259 = U32_add(DEREF(i), _t2258);
        (void)_t2259;
        ;
        *i = _t2259;
        ;
    }
    U32_delete(i, &(Bool){1});
}

int main(int argc, char **argv) {
    if (argc - 1 < 0) { fprintf(stderr, "error: main expects at least 0 argument(s), got %d\n", argc - 1); return 1; }
    _t2716 = malloc(sizeof(I64));
    *_t2716 = 0;
    (void)_t2716;
    _t2717 = malloc(sizeof(I64));
    *_t2717 = 1;
    (void)_t2717;
    _t2718 = malloc(sizeof(I64)); *_t2718 = I64_sub(DEREF(_t2716), DEREF(_t2717));
    (void)_t2718;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2718));
    (void)CAP_LIT;
    _t2719 = malloc(sizeof(I64));
    *_t2719 = 0;
    (void)_t2719;
    _t2720 = malloc(sizeof(I64));
    *_t2720 = 2;
    (void)_t2720;
    _t2721 = malloc(sizeof(I64)); *_t2721 = I64_sub(DEREF(_t2719), DEREF(_t2720));
    (void)_t2721;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2721));
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
    U64 _t2638; { U64 *_hp = (U64 *)Array_len(args); _t2638 = *_hp; free(_hp); }
    (void)_t2638;
    U64 _t2639 = 0;
    (void)_t2639;
    Bool _t2640 = U64_eq(_t2638, _t2639);
    (void)_t2640;
    ;
    ;
    if (_t2640) {
        usage();
        Str *_t2261 = Str_lit("Str", 3ULL);
        (void)_t2261;
        U64 _t2262; { U64 *_hp = (U64 *)Str_size(); _t2262 = *_hp; free(_hp); }
        (void)_t2262;
        U64 _t2263 = 1;
        (void)_t2263;
        Array *_va60 = Array_new(_t2261, &(U64){_t2262}, &(U64){_t2263});
        (void)_va60;
        Str_delete(_t2261, &(Bool){1});
        ;
        ;
        U64 _t2264 = 0;
        (void)_t2264;
        Str *_t2265 = Str_lit("no arguments", 12ULL);
        (void)_t2265;
        Array_set(_va60, &(U64){_t2264}, _t2265);
        ;
        Str *_t2266 = Str_lit("src/til.til:218:15", 18ULL);
        (void)_t2266;
        panic(_t2266, _va60);
        Str_delete(_t2266, &(Bool){1});
    }
    ;
    U64 *_t2641 = malloc(sizeof(U64));
    *_t2641 = 0;
    (void)_t2641;
    Str *cmd_ref = Array_get(args, _t2641);
    (void)cmd_ref;
    Str *command = Str_clone(cmd_ref);
    (void)command;
    U64_delete(_t2641, &(Bool){1});
    Str *path = Str_lit("", 0ULL);
    (void)path;
    Str *custom_bin = Str_lit("", 0ULL);
    (void)custom_bin;
    Str *custom_c = Str_lit("", 0ULL);
    (void)custom_c;
    U64 *path_idx = malloc(sizeof(U64));
    *path_idx = 1;
    (void)path_idx;
    U64 _t2642; { U64 *_hp = (U64 *)Array_len(args); _t2642 = *_hp; free(_hp); }
    (void)_t2642;
    U64 _t2643 = 1;
    (void)_t2643;
    Bool _t2644 = U64_eq(_t2642, _t2643);
    (void)_t2644;
    ;
    ;
    if (_t2644) {
        Str *_t2267 = Str_lit("help", 4ULL);
        (void)_t2267;
        Str *_t2268 = Str_lit("--help", 6ULL);
        (void)_t2268;
        Bool _t2269; { Bool *_hp = (Bool *)Str_eq(command, _t2267); _t2269 = *_hp; free(_hp); }
        (void)_t2269;
        Str_delete(_t2267, &(Bool){1});
        Bool _t2270; { Bool *_hp = (Bool *)Str_eq(command, _t2268); _t2270 = *_hp; free(_hp); }
        (void)_t2270;
        Str_delete(_t2268, &(Bool){1});
        Bool _t2271 = Bool_or(_t2269, _t2270);
        (void)_t2271;
        ;
        ;
        if (_t2271) {
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
            U64 _t2288; { U64 *_hp = (U64 *)Array_len(args); _t2288 = *_hp; free(_hp); }
            (void)_t2288;
            Bool _wcond2272; { Bool *_hp = (Bool *)U64_lt(path_idx, &(U64){_t2288}); _wcond2272 = *_hp; free(_hp); }
            (void)_wcond2272;
            ;
            if (_wcond2272) {
            } else {
                ;
                break;
            }
            ;
            Str *flag = Array_get(args, path_idx);
            (void)flag;
            Str *_t2289 = Str_lit("-o", 2ULL);
            (void)_t2289;
            U64 _t2290 = 1;
            (void)_t2290;
            U64 _t2291 = U64_add(DEREF(path_idx), _t2290);
            (void)_t2291;
            ;
            U64 _t2292; { U64 *_hp = (U64 *)Array_len(args); _t2292 = *_hp; free(_hp); }
            (void)_t2292;
            Bool _t2293; { Bool *_hp = (Bool *)Str_eq(flag, _t2289); _t2293 = *_hp; free(_hp); }
            (void)_t2293;
            Str_delete(_t2289, &(Bool){1});
            Bool _t2294; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2291}, &(U64){_t2292}); _t2294 = *_hp; free(_hp); }
            (void)_t2294;
            ;
            ;
            Bool _t2295 = Bool_and(_t2293, _t2294);
            (void)_t2295;
            ;
            ;
            if (_t2295) {
                U64 _t2273 = 1;
                (void)_t2273;
                U64 *_t2274 = malloc(sizeof(U64)); *_t2274 = U64_add(DEREF(path_idx), _t2273);
                (void)_t2274;
                ;
                Str *oval = Array_get(args, _t2274);
                (void)oval;
                custom_bin = Str_clone(oval);
                U64_delete(_t2274, &(Bool){1});
                U64 _t2275 = 2;
                (void)_t2275;
                U64 _t2276 = U64_add(DEREF(path_idx), _t2275);
                (void)_t2276;
                ;
                *path_idx = _t2276;
                ;
            } else {
                Str *_t2281 = Str_lit("-c", 2ULL);
                (void)_t2281;
                U64 _t2282 = 1;
                (void)_t2282;
                U64 _t2283 = U64_add(DEREF(path_idx), _t2282);
                (void)_t2283;
                ;
                U64 _t2284; { U64 *_hp = (U64 *)Array_len(args); _t2284 = *_hp; free(_hp); }
                (void)_t2284;
                Bool _t2285; { Bool *_hp = (Bool *)Str_eq(flag, _t2281); _t2285 = *_hp; free(_hp); }
                (void)_t2285;
                Str_delete(_t2281, &(Bool){1});
                Bool _t2286; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2283}, &(U64){_t2284}); _t2286 = *_hp; free(_hp); }
                (void)_t2286;
                ;
                ;
                Bool _t2287 = Bool_and(_t2285, _t2286);
                (void)_t2287;
                ;
                ;
                if (_t2287) {
                    U64 _t2277 = 1;
                    (void)_t2277;
                    U64 *_t2278 = malloc(sizeof(U64)); *_t2278 = U64_add(DEREF(path_idx), _t2277);
                    (void)_t2278;
                    ;
                    Str *cval = Array_get(args, _t2278);
                    (void)cval;
                    custom_c = Str_clone(cval);
                    U64_delete(_t2278, &(Bool){1});
                    U64 _t2279 = 2;
                    (void)_t2279;
                    U64 _t2280 = U64_add(DEREF(path_idx), _t2279);
                    (void)_t2280;
                    ;
                    *path_idx = _t2280;
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
    Str *_t2645 = Str_lit("help", 4ULL);
    (void)_t2645;
    Str *_t2646 = Str_lit("--help", 6ULL);
    (void)_t2646;
    Bool _t2647; { Bool *_hp = (Bool *)Str_eq(command, _t2645); _t2647 = *_hp; free(_hp); }
    (void)_t2647;
    Str_delete(_t2645, &(Bool){1});
    Bool _t2648; { Bool *_hp = (Bool *)Str_eq(command, _t2646); _t2648 = *_hp; free(_hp); }
    (void)_t2648;
    Str_delete(_t2646, &(Bool){1});
    Bool _t2649 = Bool_or(_t2647, _t2648);
    (void)_t2649;
    ;
    ;
    if (_t2649) {
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
    Str *_t2650 = Str_lit("/src/core/core.til", 18ULL);
    (void)_t2650;
    Str *core_path = Str_concat(bin_dir, _t2650);
    (void)core_path;
    Str_delete(_t2650, &(Bool){1});
    Str *_t2651 = Str_lit("/src/c/ext.c", 12ULL);
    (void)_t2651;
    Str *ext_c_path = Str_concat(bin_dir, _t2651);
    (void)ext_c_path;
    Str_delete(_t2651, &(Bool){1});
    Set *resolved = til_set_new();
    (void)resolved;
    Vec *resolve_stack = expr_vec_new();
    (void)resolve_stack;
    Str *abs_path = til_realpath(path);
    (void)abs_path;
    Str *user_dir = Str_lit(".", 1ULL);
    (void)user_dir;
    U64 _t2652; { U64 *_hp = (U64 *)Str_len(abs_path); _t2652 = *_hp; free(_hp); }
    (void)_t2652;
    U64 _t2653 = 0;
    (void)_t2653;
    Bool _t2654; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2652}, &(U64){_t2653}); _t2654 = *_hp; free(_hp); }
    (void)_t2654;
    ;
    ;
    if (_t2654) {
        U64 _t2304; { U64 *_hp = (U64 *)Str_len(abs_path); _t2304 = *_hp; free(_hp); }
        (void)_t2304;
        U64 _t2305 = 1;
        (void)_t2305;
        U64 *last_slash = malloc(sizeof(U64)); *last_slash = U64_sub(_t2304, _t2305);
        (void)last_slash;
        ;
        ;
        while (1) {
            U64 _t2297 = 0;
            (void)_t2297;
            U8 *_t2298 = Str_get(abs_path, last_slash);
            (void)_t2298;
            U8 _t2299 = 47;
            (void)_t2299;
            Bool _t2300; { Bool *_hp = (Bool *)U64_gt(last_slash, &(U64){_t2297}); _t2300 = *_hp; free(_hp); }
            (void)_t2300;
            ;
            Bool _t2301; { Bool *_hp = (Bool *)U8_neq(_t2298, &(U8){_t2299}); _t2301 = *_hp; free(_hp); }
            (void)_t2301;
            ;
            Bool _wcond2296 = Bool_and(_t2300, _t2301);
            (void)_wcond2296;
            ;
            ;
            if (_wcond2296) {
            } else {
                ;
                break;
            }
            ;
            U64 _t2302 = 1;
            (void)_t2302;
            U64 _t2303 = U64_sub(DEREF(last_slash), _t2302);
            (void)_t2303;
            ;
            *last_slash = _t2303;
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
    U64 _t2655; { U64 *_hp = (U64 *)Str_len(core_abs); _t2655 = *_hp; free(_hp); }
    (void)_t2655;
    U64 _t2656 = 0;
    (void)_t2656;
    Bool _t2657; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2655}, &(U64){_t2656}); _t2657 = *_hp; free(_hp); }
    (void)_t2657;
    ;
    ;
    if (_t2657) {
        Bool _t2307 = til_set_has(resolved, core_abs);
        (void)_t2307;
        if (_t2307) {
            Bool _t2306 = 1;
            (void)_t2306;
            skip_core = _t2306;
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
    U64 _t2658; { U64 *_hp = (U64 *)Vec_len(core_imports); _t2658 = *_hp; free(_hp); }
    (void)_t2658;
    U64 _t2659 = 0;
    (void)_t2659;
    Bool _t2660; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2658}, &(U64){_t2659}); _t2660 = *_hp; free(_hp); }
    (void)_t2660;
    ;
    ;
    Bool _t2661 = Bool_not(skip_core);
    (void)_t2661;
    Bool _t2662 = Bool_and(_t2660, _t2661);
    (void)_t2662;
    ;
    ;
    if (_t2662) {
        Str *_t2314 = Str_lit("/src/core", 9ULL);
        (void)_t2314;
        Str *core_dir = Str_concat(bin_dir, _t2314);
        (void)core_dir;
        Str_delete(_t2314, &(Bool){1});
        Str *_t2315 = Str_lit("", 0ULL);
        (void)_t2315;
        I32 err; { I32 *_hp = (I32 *)resolve_imports(core_imports, core_dir, resolved, resolve_stack, core_import_decls, _t2315); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(_t2315, &(Bool){1});
        Str_delete(core_dir, &(Bool){1});
        I32 _t2316 = 0;
        (void)_t2316;
        Bool _t2317; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2316}); _t2317 = *_hp; free(_hp); }
        (void)_t2317;
        ;
        ;
        if (_t2317) {
            Str *_t2308 = Str_lit("Str", 3ULL);
            (void)_t2308;
            U64 _t2309; { U64 *_hp = (U64 *)Str_size(); _t2309 = *_hp; free(_hp); }
            (void)_t2309;
            U64 _t2310 = 1;
            (void)_t2310;
            Array *_va61 = Array_new(_t2308, &(U64){_t2309}, &(U64){_t2310});
            (void)_va61;
            Str_delete(_t2308, &(Bool){1});
            ;
            ;
            U64 _t2311 = 0;
            (void)_t2311;
            Str *_t2312 = Str_lit("failed to resolve core imports", 30ULL);
            (void)_t2312;
            Array_set(_va61, &(U64){_t2311}, _t2312);
            ;
            Str *_t2313 = Str_lit("src/til.til:304:19", 18ULL);
            (void)_t2313;
            panic(_t2313, _va61);
            Str_delete(_t2313, &(Bool){1});
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
    Str *_t2663 = Str_lit("script", 6ULL);
    (void)_t2663;
    Mode *cur_mode = mode_resolve(_t2663);
    (void)cur_mode;
    Str_delete(_t2663, &(Bool){1});
    U64 _t2664; { U64 *_hp = (U64 *)Str_len(mode_str); _t2664 = *_hp; free(_hp); }
    (void)_t2664;
    U64 _t2665 = 0;
    (void)_t2665;
    Bool _t2666; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2664}, &(U64){_t2665}); _t2666 = *_hp; free(_hp); }
    (void)_t2666;
    ;
    ;
    if (_t2666) {
        cur_mode = mode_resolve(mode_str);
        U64 _t2327; { U64 *_hp = (U64 *)Str_len(&cur_mode->name); _t2327 = *_hp; free(_hp); }
        (void)_t2327;
        U64 _t2328 = 0;
        (void)_t2328;
        Bool _t2329 = U64_eq(_t2327, _t2328);
        (void)_t2329;
        ;
        ;
        if (_t2329) {
            Str *_t2318 = Str_lit("Str", 3ULL);
            (void)_t2318;
            U64 _t2319; { U64 *_hp = (U64 *)Str_size(); _t2319 = *_hp; free(_hp); }
            (void)_t2319;
            U64 _t2320 = 1;
            (void)_t2320;
            Array *_va62 = Array_new(_t2318, &(U64){_t2319}, &(U64){_t2320});
            (void)_va62;
            Str_delete(_t2318, &(Bool){1});
            ;
            ;
            Str *_t2321 = Str_lit("unknown mode '", 14ULL);
            (void)_t2321;
            Str *_t2322 = Str_concat(_t2321, mode_str);
            (void)_t2322;
            Str_delete(_t2321, &(Bool){1});
            Str *_t2323 = Str_lit("'", 1ULL);
            (void)_t2323;
            U64 _t2324 = 0;
            (void)_t2324;
            Str *_t2325 = Str_concat(_t2322, _t2323);
            (void)_t2325;
            Str_delete(_t2322, &(Bool){1});
            Str_delete(_t2323, &(Bool){1});
            Array_set(_va62, &(U64){_t2324}, _t2325);
            ;
            Str *_t2326 = Str_lit("src/til.til:320:19", 18ULL);
            (void)_t2326;
            panic(_t2326, _va62);
            Str_delete(_t2326, &(Bool){1});
        }
        ;
    }
    ;
    Str_delete(mode_str, &(Bool){1});
    Str *auto_import = Str_clone(&cur_mode->auto_import);
    (void)auto_import;
    Vec *import_decls = expr_vec_new();
    (void)import_decls;
    U64 _t2667; { U64 *_hp = (U64 *)Vec_len(imports); _t2667 = *_hp; free(_hp); }
    (void)_t2667;
    U64 _t2668 = 0;
    (void)_t2668;
    Bool _t2669; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2667}, &(U64){_t2668}); _t2669 = *_hp; free(_hp); }
    (void)_t2669;
    ;
    ;
    if (_t2669) {
        Str *_t2336 = Str_lit("/src/lib", 8ULL);
        (void)_t2336;
        Str *lib_dir = Str_concat(bin_dir, _t2336);
        (void)lib_dir;
        Str_delete(_t2336, &(Bool){1});
        I32 err; { I32 *_hp = (I32 *)resolve_imports(imports, user_dir, resolved, resolve_stack, import_decls, lib_dir); err = *_hp; free(_hp); }
        (void)err;
        Str_delete(lib_dir, &(Bool){1});
        I32 _t2337 = 0;
        (void)_t2337;
        Bool _t2338; { Bool *_hp = (Bool *)I32_gt(&(I32){err}, &(I32){_t2337}); _t2338 = *_hp; free(_hp); }
        (void)_t2338;
        ;
        ;
        if (_t2338) {
            Str *_t2330 = Str_lit("Str", 3ULL);
            (void)_t2330;
            U64 _t2331; { U64 *_hp = (U64 *)Str_size(); _t2331 = *_hp; free(_hp); }
            (void)_t2331;
            U64 _t2332 = 1;
            (void)_t2332;
            Array *_va63 = Array_new(_t2330, &(U64){_t2331}, &(U64){_t2332});
            (void)_va63;
            Str_delete(_t2330, &(Bool){1});
            ;
            ;
            U64 _t2333 = 0;
            (void)_t2333;
            Str *_t2334 = Str_lit("failed to resolve imports", 25ULL);
            (void)_t2334;
            Array_set(_va63, &(U64){_t2333}, _t2334);
            ;
            Str *_t2335 = Str_lit("src/til.til:334:19", 18ULL);
            (void)_t2335;
            panic(_t2335, _va63);
            Str_delete(_t2335, &(Bool){1});
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
    Bool _t2670 = Bool_not(skip_core);
    (void)_t2670;
    ;
    if (_t2670) {
        while (1) {
            U32 _t2340 = expr_nchildren(core_ast);
            (void)_t2340;
            Bool _wcond2339; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2340}); _wcond2339 = *_hp; free(_hp); }
            (void)_wcond2339;
            ;
            if (_wcond2339) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(core_ast, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2341 = 1;
            (void)_t2341;
            U32 _t2342 = U32_add(DEREF(i), _t2341);
            (void)_t2342;
            ;
            *i = _t2342;
            ;
        }
        U32 _t2347 = 0;
        (void)_t2347;
        *i = _t2347;
        ;
        while (1) {
            U32 _t2344 = expr_vec_count(core_import_decls);
            (void)_t2344;
            Bool _wcond2343; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2344}); _wcond2343 = *_hp; free(_hp); }
            (void)_wcond2343;
            ;
            if (_wcond2343) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_vec_get(core_import_decls, DEREF(i));
            (void)ch;
            mark_core(ch);
            expr_vec_push(merged, ch);
            U32 _t2345 = 1;
            (void)_t2345;
            U32 _t2346 = U32_add(DEREF(i), _t2345);
            (void)_t2346;
            ;
            *i = _t2346;
            ;
        }
    }
    ;
    Expr_delete(core_ast, &(Bool){1});
    Vec_delete(core_import_decls, &(Bool){1});
    U64 _t2671; { U64 *_hp = (U64 *)Str_len(auto_import); _t2671 = *_hp; free(_hp); }
    (void)_t2671;
    U64 _t2672 = 0;
    (void)_t2672;
    Bool _t2673; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2671}, &(U64){_t2672}); _t2673 = *_hp; free(_hp); }
    (void)_t2673;
    ;
    ;
    if (_t2673) {
        Str *_t2352 = Str_lit("/src/modes/", 11ULL);
        (void)_t2352;
        Str *_t2353 = Str_concat(bin_dir, _t2352);
        (void)_t2353;
        Str_delete(_t2352, &(Bool){1});
        Str *_t2354 = Str_concat(_t2353, auto_import);
        (void)_t2354;
        Str_delete(_t2353, &(Bool){1});
        Str *_t2355 = Str_lit(".til", 4ULL);
        (void)_t2355;
        Str *mode_til_path = Str_concat(_t2354, _t2355);
        (void)mode_til_path;
        Str_delete(_t2354, &(Bool){1});
        Str_delete(_t2355, &(Bool){1});
        Str *mode_source = readfile(mode_til_path);
        (void)mode_source;
        Vec *mode_tokens = tokenize(mode_source, mode_til_path);
        (void)mode_tokens;
        Str_delete(mode_source, &(Bool){1});
        Expr *mode_ast = til_parse(mode_tokens, mode_til_path);
        (void)mode_ast;
        Str_delete(mode_til_path, &(Bool){1});
        Vec_delete(mode_tokens, &(Bool){1});
        U32 _t2356 = 0;
        (void)_t2356;
        *i = _t2356;
        ;
        while (1) {
            U32 _t2349 = expr_nchildren(mode_ast);
            (void)_t2349;
            Bool _wcond2348; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2349}); _wcond2348 = *_hp; free(_hp); }
            (void)_wcond2348;
            ;
            if (_wcond2348) {
            } else {
                ;
                break;
            }
            ;
            Expr *ch = expr_get_child(mode_ast, DEREF(i));
            (void)ch;
            expr_vec_push(merged, ch);
            U32 _t2350 = 1;
            (void)_t2350;
            U32 _t2351 = U32_add(DEREF(i), _t2350);
            (void)_t2351;
            ;
            *i = _t2351;
            ;
        }
        Expr_delete(mode_ast, &(Bool){1});
    }
    ;
    Str_delete(auto_import, &(Bool){1});
    Str_delete(bin_dir, &(Bool){1});
    U32 _t2674 = 0;
    (void)_t2674;
    *i = _t2674;
    ;
    while (1) {
        U32 _t2358 = expr_vec_count(import_decls);
        (void)_t2358;
        Bool _wcond2357; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2358}); _wcond2357 = *_hp; free(_hp); }
        (void)_wcond2357;
        ;
        if (_wcond2357) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_vec_get(import_decls, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2359 = 1;
        (void)_t2359;
        U32 _t2360 = U32_add(DEREF(i), _t2359);
        (void)_t2360;
        ;
        *i = _t2360;
        ;
    }
    Vec_delete(import_decls, &(Bool){1});
    U32 _t2675 = 0;
    (void)_t2675;
    *i = _t2675;
    ;
    while (1) {
        U32 _t2362 = expr_nchildren(ast);
        (void)_t2362;
        Bool _wcond2361; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2362}); _wcond2361 = *_hp; free(_hp); }
        (void)_wcond2361;
        ;
        if (_wcond2361) {
        } else {
            ;
            break;
        }
        ;
        Expr *ch = expr_get_child(ast, DEREF(i));
        (void)ch;
        expr_vec_push(merged, ch);
        U32 _t2363 = 1;
        (void)_t2363;
        U32 _t2364 = U32_add(DEREF(i), _t2363);
        (void)_t2364;
        ;
        *i = _t2364;
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
    U32 _t2676 = 0;
    (void)_t2676;
    *i = _t2676;
    ;
    while (1) {
        U32 _t2380 = expr_nchildren(ast);
        (void)_t2380;
        Bool _wcond2365; { Bool *_hp = (Bool *)U32_lt(i, &(U32){_t2380}); _wcond2365 = *_hp; free(_hp); }
        (void)_wcond2365;
        ;
        if (_wcond2365) {
        } else {
            ;
            break;
        }
        ;
        Expr *stmt = expr_get_child(ast, DEREF(i));
        (void)stmt;
        I32 _t2381 = expr_get_tag(stmt);
        (void)_t2381;
        U32 _t2382 = expr_nchildren(stmt);
        (void)_t2382;
        U32 _t2383 = 2;
        (void)_t2383;
        Bool _t2384 = I32_eq(_t2381, DEREF(NODE_FCALL));
        (void)_t2384;
        ;
        Bool _t2385 = U32_eq(_t2382, _t2383);
        (void)_t2385;
        ;
        ;
        U32 *_t2386 = malloc(sizeof(U32));
        *_t2386 = 0;
        (void)_t2386;
        Expr *_t2387 = expr_get_child(stmt, DEREF(_t2386));
        (void)_t2387;
        I32 _t2388 = expr_get_tag(_t2387);
        (void)_t2388;
        U32_delete(_t2386, &(Bool){1});
        Bool _t2389 = Bool_and(_t2384, _t2385);
        (void)_t2389;
        ;
        ;
        Bool _t2390 = I32_eq(_t2388, DEREF(NODE_IDENT));
        (void)_t2390;
        ;
        U32 *_t2391 = malloc(sizeof(U32));
        *_t2391 = 1;
        (void)_t2391;
        Expr *_t2392 = expr_get_child(stmt, DEREF(_t2391));
        (void)_t2392;
        I32 _t2393 = expr_get_tag(_t2392);
        (void)_t2393;
        U32_delete(_t2391, &(Bool){1});
        Bool _t2394 = Bool_and(_t2389, _t2390);
        (void)_t2394;
        ;
        ;
        Bool _t2395 = I32_eq(_t2393, DEREF(NODE_LITERAL_STR));
        (void)_t2395;
        ;
        Bool _t2396 = Bool_and(_t2394, _t2395);
        (void)_t2396;
        ;
        ;
        if (_t2396) {
            U32 *_t2374 = malloc(sizeof(U32));
            *_t2374 = 0;
            (void)_t2374;
            Expr *_t2375 = expr_get_child(stmt, DEREF(_t2374));
            (void)_t2375;
            Str *fname = expr_get_str_val(_t2375);
            (void)fname;
            U32 *_t2376 = malloc(sizeof(U32));
            *_t2376 = 1;
            (void)_t2376;
            Expr *_t2377 = expr_get_child(stmt, DEREF(_t2376));
            (void)_t2377;
            Str *arg = expr_get_str_val(_t2377);
            (void)arg;
            Str *_t2378 = Str_lit("link", 4ULL);
            (void)_t2378;
            Bool _t2379; { Bool *_hp = (Bool *)Str_eq(fname, _t2378); _t2379 = *_hp; free(_hp); }
            (void)_t2379;
            Str_delete(_t2378, &(Bool){1});
            if (_t2379) {
                Str *_t2366 = Str_lit(" -l", 3ULL);
                (void)_t2366;
                Str *_t2367 = Str_concat(link_flags, _t2366);
                (void)_t2367;
                Str_delete(_t2366, &(Bool){1});
                link_flags = Str_concat(_t2367, arg);
                Str_delete(_t2367, &(Bool){1});
            } else {
                Str *_t2372 = Str_lit("link_c", 6ULL);
                (void)_t2372;
                Bool _t2373; { Bool *_hp = (Bool *)Str_eq(fname, _t2372); _t2373 = *_hp; free(_hp); }
                (void)_t2373;
                Str_delete(_t2372, &(Bool){1});
                if (_t2373) {
                    U64 _t2369; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2369 = *_hp; free(_hp); }
                    (void)_t2369;
                    U64 _t2370 = 0;
                    (void)_t2370;
                    Bool _t2371; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2369}, &(U64){_t2370}); _t2371 = *_hp; free(_hp); }
                    (void)_t2371;
                    ;
                    ;
                    if (_t2371) {
                        Str *_t2368 = Str_lit(" ", 1ULL);
                        (void)_t2368;
                        link_c_paths = Str_concat(link_c_paths, _t2368);
                        Str_delete(_t2368, &(Bool){1});
                    }
                    ;
                    link_c_paths = Str_concat(link_c_paths, arg);
                } else {
                    expr_vec_push(kept, stmt);
                }
                ;
            }
            U32_delete(_t2374, &(Bool){1});
            U32_delete(_t2376, &(Bool){1});
            ;
        } else {
            expr_vec_push(kept, stmt);
        }
        ;
        U32 _t2397 = 1;
        (void)_t2397;
        U32 _t2398 = U32_add(DEREF(i), _t2397);
        (void)_t2398;
        ;
        *i = _t2398;
        ;
    }
    U32_delete(i, &(Bool){1});
    expr_swap_children(ast, kept);
    Vec_delete(kept, &(Bool){1});
    TypeScope *scope = tscope_new(NULL);
    (void)scope;
    I32 _t2677 = init_declarations(ast, scope);
    (void)_t2677;
    ;
    I32 type_errors = type_check(ast, scope, cur_mode);
    (void)type_errors;
    TypeScope_delete(scope, &(Bool){1});
    I32 _t2678 = 0;
    (void)_t2678;
    Bool _t2679; { Bool *_hp = (Bool *)I32_gt(&(I32){type_errors}, &(I32){_t2678}); _t2679 = *_hp; free(_hp); }
    (void)_t2679;
    ;
    if (_t2679) {
        Str *_t2399 = Str_lit("Str", 3ULL);
        (void)_t2399;
        U64 _t2400; { U64 *_hp = (U64 *)Str_size(); _t2400 = *_hp; free(_hp); }
        (void)_t2400;
        U64 _t2401 = 1;
        (void)_t2401;
        Array *_va64 = Array_new(_t2399, &(U64){_t2400}, &(U64){_t2401});
        (void)_va64;
        Str_delete(_t2399, &(Bool){1});
        ;
        ;
        Str *_t2402 = I32_to_str(&(I32){type_errors});
        (void)_t2402;
        Str *_t2403 = Str_lit(" type error(s) found", 20ULL);
        (void)_t2403;
        U64 _t2404 = 0;
        (void)_t2404;
        Str *_t2405 = Str_concat(_t2402, _t2403);
        (void)_t2405;
        Str_delete(_t2402, &(Bool){1});
        Str_delete(_t2403, &(Bool){1});
        Array_set(_va64, &(U64){_t2404}, _t2405);
        ;
        Str *_t2406 = Str_lit("src/til.til:429:15", 18ULL);
        (void)_t2406;
        panic(_t2406, _va64);
        Str_delete(_t2406, &(Bool){1});
    }
    ;
    ;
    Str *_t2680 = Str_lit("test", 4ULL);
    (void)_t2680;
    Str *_t2681 = Str_lit("test", 4ULL);
    (void)_t2681;
    Bool _t2682; { Bool *_hp = (Bool *)Str_eq(command, _t2680); _t2682 = *_hp; free(_hp); }
    (void)_t2682;
    Str_delete(_t2680, &(Bool){1});
    Bool _t2683; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2681); _t2683 = *_hp; free(_hp); }
    (void)_t2683;
    Str_delete(_t2681, &(Bool){1});
    Str *_t2684 = Str_lit("pure", 4ULL);
    (void)_t2684;
    Bool _t2685 = Bool_or(_t2682, _t2683);
    (void)_t2685;
    ;
    ;
    Bool _t2686; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2684); _t2686 = *_hp; free(_hp); }
    (void)_t2686;
    Str_delete(_t2684, &(Bool){1});
    Str *_t2687 = Str_lit("pura", 4ULL);
    (void)_t2687;
    Bool _t2688 = Bool_or(_t2685, _t2686);
    (void)_t2688;
    ;
    ;
    Bool _t2689; { Bool *_hp = (Bool *)Str_eq(&cur_mode->name, _t2687); _t2689 = *_hp; free(_hp); }
    (void)_t2689;
    Str_delete(_t2687, &(Bool){1});
    Bool run_tests = Bool_or(_t2688, _t2689);
    (void)run_tests;
    ;
    ;
    precomp(ast);
    Str *_t2690 = Str_lit("translate", 9ULL);
    (void)_t2690;
    Str *_t2691 = Str_lit("build", 5ULL);
    (void)_t2691;
    Bool _t2692; { Bool *_hp = (Bool *)Str_eq(command, _t2690); _t2692 = *_hp; free(_hp); }
    (void)_t2692;
    Str_delete(_t2690, &(Bool){1});
    Bool _t2693; { Bool *_hp = (Bool *)Str_eq(command, _t2691); _t2693 = *_hp; free(_hp); }
    (void)_t2693;
    Str_delete(_t2691, &(Bool){1});
    Bool _t2694; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2694 = *_hp; free(_hp); }
    (void)_t2694;
    Bool _t2695 = Bool_or(_t2692, _t2693);
    (void)_t2695;
    ;
    ;
    Bool is_lib_target = Bool_and(_t2694, _t2695);
    (void)is_lib_target;
    ;
    ;
    U64 _t2696; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2696 = *_hp; free(_hp); }
    (void)_t2696;
    U64 _t2697 = 0;
    (void)_t2697;
    Bool _t2698 = Bool_not(is_lib_target);
    (void)_t2698;
    ;
    Bool _t2699 = U64_eq(_t2696, _t2697);
    (void)_t2699;
    ;
    ;
    Bool _t2700 = Bool_and(_t2698, _t2699);
    (void)_t2700;
    ;
    ;
    if (_t2700) {
        scavenge(ast, cur_mode, run_tests);
    }
    ;
    I32 result = 0;
    (void)result;
    Str *user_c = Str_lit("", 0ULL);
    (void)user_c;
    U64 _t2701; { U64 *_hp = (U64 *)Str_len(link_c_paths); _t2701 = *_hp; free(_hp); }
    (void)_t2701;
    U64 _t2702 = 0;
    (void)_t2702;
    Bool _t2703; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2701}, &(U64){_t2702}); _t2703 = *_hp; free(_hp); }
    (void)_t2703;
    ;
    ;
    if (_t2703) {
        user_c = Str_clone(link_c_paths);
    }
    ;
    Str_delete(link_c_paths, &(Bool){1});
    Str *_t2704 = Str_lit("Str", 3ULL);
    (void)_t2704;
    U64 _t2705; { U64 *_hp = (U64 *)Str_size(); _t2705 = *_hp; free(_hp); }
    (void)_t2705;
    Vec *user_argv = Vec_new(_t2704, &(U64){_t2705});
    (void)user_argv;
    Str_delete(_t2704, &(Bool){1});
    ;
    U64 _t2706 = 1;
    (void)_t2706;
    U64 *ai = malloc(sizeof(U64)); *ai = U64_add(DEREF(path_idx), _t2706);
    (void)ai;
    ;
    U64_delete(path_idx, &(Bool){1});
    while (1) {
        U64 _t2423; { U64 *_hp = (U64 *)Array_len(args); _t2423 = *_hp; free(_hp); }
        (void)_t2423;
        Bool _wcond2407; { Bool *_hp = (Bool *)U64_lt(ai, &(U64){_t2423}); _wcond2407 = *_hp; free(_hp); }
        (void)_wcond2407;
        ;
        if (_wcond2407) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, ai);
        (void)arg;
        Str *_t2424 = Str_lit("-l", 2ULL);
        (void)_t2424;
        Bool _t2425; { Bool *_hp = (Bool *)Str_starts_with(arg, _t2424); _t2425 = *_hp; free(_hp); }
        (void)_t2425;
        Str_delete(_t2424, &(Bool){1});
        if (_t2425) {
            U64 _t2410 = 2;
            (void)_t2410;
            U64 _t2411; { U64 *_hp = (U64 *)Str_len(arg); _t2411 = *_hp; free(_hp); }
            (void)_t2411;
            Str *lib = Str_substr(arg, &(U64){_t2410}, &(U64){_t2411});
            (void)lib;
            ;
            ;
            U64 _t2412; { U64 *_hp = (U64 *)Str_len(lib); _t2412 = *_hp; free(_hp); }
            (void)_t2412;
            U64 _t2413 = 0;
            (void)_t2413;
            U64 _t2414 = 1;
            (void)_t2414;
            U64 _t2415 = U64_add(DEREF(ai), _t2414);
            (void)_t2415;
            ;
            U64 _t2416; { U64 *_hp = (U64 *)Array_len(args); _t2416 = *_hp; free(_hp); }
            (void)_t2416;
            Bool _t2417 = U64_eq(_t2412, _t2413);
            (void)_t2417;
            ;
            ;
            Bool _t2418; { Bool *_hp = (Bool *)U64_lt(&(U64){_t2415}, &(U64){_t2416}); _t2418 = *_hp; free(_hp); }
            (void)_t2418;
            ;
            ;
            Bool _t2419 = Bool_and(_t2417, _t2418);
            (void)_t2419;
            ;
            ;
            if (_t2419) {
                U64 _t2408 = 1;
                (void)_t2408;
                U64 _t2409 = U64_add(DEREF(ai), _t2408);
                (void)_t2409;
                ;
                *ai = _t2409;
                ;
                Str *next_arg = Array_get(args, ai);
                (void)next_arg;
                lib = Str_clone(next_arg);
            }
            ;
            Str *_t2420 = Str_lit(" -l", 3ULL);
            (void)_t2420;
            Str *_t2421 = Str_concat(link_flags, _t2420);
            (void)_t2421;
            Str_delete(_t2420, &(Bool){1});
            link_flags = Str_concat(_t2421, lib);
            Str_delete(_t2421, &(Bool){1});
            Str_delete(lib, &(Bool){1});
        } else {
            Str *_t2422 = Str_clone(arg);
            (void)_t2422;
            Vec_push(user_argv, _t2422);
        }
        ;
        U64 _t2426 = 1;
        (void)_t2426;
        U64 _t2427 = U64_add(DEREF(ai), _t2426);
        (void)_t2427;
        ;
        *ai = _t2427;
        ;
    }
    U64_delete(ai, &(Bool){1});
    Array_delete(args, &(Bool){1});
    Str *lflags = Str_lit("", 0ULL);
    (void)lflags;
    U64 _t2707; { U64 *_hp = (U64 *)Str_len(link_flags); _t2707 = *_hp; free(_hp); }
    (void)_t2707;
    U64 _t2708 = 0;
    (void)_t2708;
    Bool _t2709; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2707}, &(U64){_t2708}); _t2709 = *_hp; free(_hp); }
    (void)_t2709;
    ;
    ;
    if (_t2709) {
        lflags = Str_clone(link_flags);
    }
    ;
    Str_delete(link_flags, &(Bool){1});
    Bool is_lib_mode; { Bool *_hp = (Bool *)mode_is_lib(cur_mode); is_lib_mode = *_hp; free(_hp); }
    (void)is_lib_mode;
    Str *_t2710 = Str_lit("interpret", 9ULL);
    (void)_t2710;
    Str *_t2711 = Str_lit("test", 4ULL);
    (void)_t2711;
    Bool _t2712; { Bool *_hp = (Bool *)Str_eq(command, _t2710); _t2712 = *_hp; free(_hp); }
    (void)_t2712;
    Str_delete(_t2710, &(Bool){1});
    Bool _t2713; { Bool *_hp = (Bool *)Str_eq(command, _t2711); _t2713 = *_hp; free(_hp); }
    (void)_t2713;
    Str_delete(_t2711, &(Bool){1});
    Bool _t2714 = Bool_or(_t2712, _t2713);
    (void)_t2714;
    ;
    ;
    if (_t2714) {
        Str *_t2434 = Str_lit("interpret", 9ULL);
        (void)_t2434;
        Bool _t2435; { Bool *_hp = (Bool *)Str_eq(command, _t2434); _t2435 = *_hp; free(_hp); }
        (void)_t2435;
        Str_delete(_t2434, &(Bool){1});
        Bool _t2436 = Bool_and(is_lib_mode, _t2435);
        (void)_t2436;
        ;
        if (_t2436) {
            Str *_t2428 = Str_lit("Str", 3ULL);
            (void)_t2428;
            U64 _t2429; { U64 *_hp = (U64 *)Str_size(); _t2429 = *_hp; free(_hp); }
            (void)_t2429;
            U64 _t2430 = 1;
            (void)_t2430;
            Array *_va65 = Array_new(_t2428, &(U64){_t2429}, &(U64){_t2430});
            (void)_va65;
            Str_delete(_t2428, &(Bool){1});
            ;
            ;
            U64 _t2431 = 0;
            (void)_t2431;
            Str *_t2432 = Str_lit("cannot interpret a library — use translate or build", 53ULL);
            (void)_t2432;
            Array_set(_va65, &(U64){_t2431}, _t2432);
            ;
            Str *_t2433 = Str_lit("src/til.til:483:19", 18ULL);
            (void)_t2433;
            panic(_t2433, _va65);
            Str_delete(_t2433, &(Bool){1});
        }
        ;
        I32 _t2437 = til_interpret_v(ast, cur_mode, run_tests, path, user_c, ext_c_path, lflags, user_argv);
        (void)_t2437;
        result = _t2437;
        ;
    } else {
        Str *_t2630 = Str_lit("translate", 9ULL);
        (void)_t2630;
        Str *_t2631 = Str_lit("build", 5ULL);
        (void)_t2631;
        Bool _t2632; { Bool *_hp = (Bool *)Str_eq(command, _t2630); _t2632 = *_hp; free(_hp); }
        (void)_t2632;
        Str_delete(_t2630, &(Bool){1});
        Bool _t2633; { Bool *_hp = (Bool *)Str_eq(command, _t2631); _t2633 = *_hp; free(_hp); }
        (void)_t2633;
        Str_delete(_t2631, &(Bool){1});
        Str *_t2634 = Str_lit("run", 3ULL);
        (void)_t2634;
        Bool _t2635 = Bool_or(_t2632, _t2633);
        (void)_t2635;
        ;
        ;
        Bool _t2636; { Bool *_hp = (Bool *)Str_eq(command, _t2634); _t2636 = *_hp; free(_hp); }
        (void)_t2636;
        Str_delete(_t2634, &(Bool){1});
        Bool _t2637 = Bool_or(_t2635, _t2636);
        (void)_t2637;
        ;
        ;
        if (_t2637) {
            Str *_t2563 = Str_lit("run", 3ULL);
            (void)_t2563;
            Bool _t2564; { Bool *_hp = (Bool *)Str_eq(command, _t2563); _t2564 = *_hp; free(_hp); }
            (void)_t2564;
            Str_delete(_t2563, &(Bool){1});
            Bool _t2565 = Bool_and(is_lib_mode, _t2564);
            (void)_t2565;
            ;
            if (_t2565) {
                Str *_t2438 = Str_lit("Str", 3ULL);
                (void)_t2438;
                U64 _t2439; { U64 *_hp = (U64 *)Str_size(); _t2439 = *_hp; free(_hp); }
                (void)_t2439;
                U64 _t2440 = 1;
                (void)_t2440;
                Array *_va66 = Array_new(_t2438, &(U64){_t2439}, &(U64){_t2440});
                (void)_va66;
                Str_delete(_t2438, &(Bool){1});
                ;
                ;
                U64 _t2441 = 0;
                (void)_t2441;
                Str *_t2442 = Str_lit("cannot run a library — use translate or build", 47ULL);
                (void)_t2442;
                Array_set(_va66, &(U64){_t2441}, _t2442);
                ;
                Str *_t2443 = Str_lit("src/til.til:489:19", 18ULL);
                (void)_t2443;
                panic(_t2443, _va66);
                Str_delete(_t2443, &(Bool){1});
            }
            ;
            Str *_t2566 = Str_lit("/", 1ULL);
            (void)_t2566;
            I64 *last_slash = Str_rfind(path, _t2566);
            (void)last_slash;
            Str_delete(_t2566, &(Bool){1});
            Str *basename = Str_clone(path);
            (void)basename;
            I64 _t2567 = 0;
            (void)_t2567;
            Bool _t2568; { Bool *_hp = (Bool *)I64_gte(last_slash, &(I64){_t2567}); _t2568 = *_hp; free(_hp); }
            (void)_t2568;
            ;
            if (_t2568) {
                I64 _t2444 = 1;
                (void)_t2444;
                I64 _t2445 = I64_add(DEREF(last_slash), _t2444);
                (void)_t2445;
                ;
                U64 _t2446; { U64 *_hp = (U64 *)Str_len(path); _t2446 = *_hp; free(_hp); }
                (void)_t2446;
                U64 _t2447 = I64_to_u64(DEREF(last_slash));
                (void)_t2447;
                U64 _t2448 = U64_sub(_t2446, _t2447);
                (void)_t2448;
                ;
                ;
                U64 _t2449 = 1;
                (void)_t2449;
                U64 _t2450 = I64_to_u64(_t2445);
                (void)_t2450;
                ;
                U64 _t2451 = U64_sub(_t2448, _t2449);
                (void)_t2451;
                ;
                ;
                basename = Str_substr(path, &(U64){_t2450}, &(U64){_t2451});
                ;
                ;
            }
            ;
            I64_delete(last_slash, &(Bool){1});
            U64 name_len; { U64 *_hp = (U64 *)Str_len(basename); name_len = *_hp; free(_hp); }
            (void)name_len;
            Str *_t2569 = Str_lit(".til", 4ULL);
            (void)_t2569;
            Bool _t2570; { Bool *_hp = (Bool *)Str_ends_with(basename, _t2569); _t2570 = *_hp; free(_hp); }
            (void)_t2570;
            Str_delete(_t2569, &(Bool){1});
            if (_t2570) {
                U64 _t2452 = 4;
                (void)_t2452;
                U64 _t2453 = U64_sub(name_len, _t2452);
                (void)_t2453;
                ;
                name_len = _t2453;
                ;
            }
            ;
            U64 _t2571 = 0;
            (void)_t2571;
            Str *name = Str_substr(basename, &(U64){_t2571}, &(U64){name_len});
            (void)name;
            ;
            Str_delete(basename, &(Bool){1});
            ;
            Str *_t2572 = Str_lit("gen/til/", 8ULL);
            (void)_t2572;
            Str *_t2573 = Str_concat(_t2572, name);
            (void)_t2573;
            Str_delete(_t2572, &(Bool){1});
            Str *_t2574 = Str_lit(".c", 2ULL);
            (void)_t2574;
            Str *c_path = Str_concat(_t2573, _t2574);
            (void)c_path;
            Str_delete(_t2573, &(Bool){1});
            Str_delete(_t2574, &(Bool){1});
            U64 _t2575; { U64 *_hp = (U64 *)Str_len(custom_c); _t2575 = *_hp; free(_hp); }
            (void)_t2575;
            U64 _t2576 = 0;
            (void)_t2576;
            Bool _t2577; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2575}, &(U64){_t2576}); _t2577 = *_hp; free(_hp); }
            (void)_t2577;
            ;
            ;
            if (_t2577) {
                c_path = Str_clone(custom_c);
            }
            ;
            Str *_t2578 = Str_lit("bin/til/", 8ULL);
            (void)_t2578;
            Str *bin_path = Str_concat(_t2578, name);
            (void)bin_path;
            Str_delete(_t2578, &(Bool){1});
            U64 _t2579; { U64 *_hp = (U64 *)Str_len(custom_bin); _t2579 = *_hp; free(_hp); }
            (void)_t2579;
            U64 _t2580 = 0;
            (void)_t2580;
            Bool _t2581; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2579}, &(U64){_t2580}); _t2581 = *_hp; free(_hp); }
            (void)_t2581;
            ;
            ;
            if (_t2581) {
                bin_path = Str_clone(custom_bin);
            }
            ;
            Str *_t2582 = Str_lit("run", 3ULL);
            (void)_t2582;
            Bool _t2583; { Bool *_hp = (Bool *)Str_eq(command, _t2582); _t2583 = *_hp; free(_hp); }
            (void)_t2583;
            Str_delete(_t2582, &(Bool){1});
            Bool _t2584; { Bool *_hp = (Bool *)mode_is_lib_output(cur_mode); _t2584 = *_hp; free(_hp); }
            (void)_t2584;
            Bool _t2585 = Bool_not(_t2583);
            (void)_t2585;
            ;
            Bool do_lib = Bool_and(_t2584, _t2585);
            (void)do_lib;
            ;
            ;
            if (do_lib) {
                Str *_t2454 = Str_lit("mkdir -p gen/til gen/lib", 24ULL);
                (void)_t2454;
                I32 _t2455 = til_system(_t2454);
                (void)_t2455;
                Str_delete(_t2454, &(Bool){1});
                ;
            } else {
                Str *_t2460 = Str_lit("/", 1ULL);
                (void)_t2460;
                I64 cp_slash; { I64 *_hp = (I64 *)Str_rfind(c_path, _t2460); cp_slash = *_hp; free(_hp); }
                (void)cp_slash;
                Str_delete(_t2460, &(Bool){1});
                Str *_t2461 = Str_lit("/", 1ULL);
                (void)_t2461;
                I64 bp_slash; { I64 *_hp = (I64 *)Str_rfind(bin_path, _t2461); bp_slash = *_hp; free(_hp); }
                (void)bp_slash;
                Str_delete(_t2461, &(Bool){1});
                Str *cp_dir = Str_lit("gen/til", 7ULL);
                (void)cp_dir;
                I64 _t2462 = 0;
                (void)_t2462;
                Bool _t2463; { Bool *_hp = (Bool *)I64_gt(&(I64){cp_slash}, &(I64){_t2462}); _t2463 = *_hp; free(_hp); }
                (void)_t2463;
                ;
                if (_t2463) {
                    U64 _t2456 = 0;
                    (void)_t2456;
                    U64 _t2457 = I64_to_u64(cp_slash);
                    (void)_t2457;
                    cp_dir = Str_substr(c_path, &(U64){_t2456}, &(U64){_t2457});
                    ;
                    ;
                }
                ;
                ;
                Str *bp_dir = Str_lit("bin/til", 7ULL);
                (void)bp_dir;
                I64 _t2464 = 0;
                (void)_t2464;
                Bool _t2465; { Bool *_hp = (Bool *)I64_gt(&(I64){bp_slash}, &(I64){_t2464}); _t2465 = *_hp; free(_hp); }
                (void)_t2465;
                ;
                if (_t2465) {
                    U64 _t2458 = 0;
                    (void)_t2458;
                    U64 _t2459 = I64_to_u64(bp_slash);
                    (void)_t2459;
                    bp_dir = Str_substr(bin_path, &(U64){_t2458}, &(U64){_t2459});
                    ;
                    ;
                }
                ;
                ;
                Str *_t2466 = Str_lit("mkdir -p ", 9ULL);
                (void)_t2466;
                Str *_t2467 = Str_concat(_t2466, cp_dir);
                (void)_t2467;
                Str_delete(_t2466, &(Bool){1});
                Str_delete(cp_dir, &(Bool){1});
                Str *_t2468 = Str_lit(" ", 1ULL);
                (void)_t2468;
                Str *_t2469 = Str_concat(_t2467, _t2468);
                (void)_t2469;
                Str_delete(_t2467, &(Bool){1});
                Str_delete(_t2468, &(Bool){1});
                Str *_t2470 = Str_concat(_t2469, bp_dir);
                (void)_t2470;
                Str_delete(_t2469, &(Bool){1});
                Str_delete(bp_dir, &(Bool){1});
                I32 _t2471 = til_system(_t2470);
                (void)_t2471;
                Str_delete(_t2470, &(Bool){1});
                ;
            }
            I32 _t2586 = build(ast, cur_mode, run_tests, path, c_path);
            (void)_t2586;
            result = _t2586;
            ;
            I32 _t2587 = 0;
            (void)_t2587;
            Bool _t2588 = I32_eq(result, _t2587);
            (void)_t2588;
            ;
            Bool _t2589 = Bool_and(_t2588, do_lib);
            (void)_t2589;
            ;
            if (_t2589) {
                Str *_t2528 = Str_lit("gen/til/", 8ULL);
                (void)_t2528;
                Str *_t2529 = Str_concat(_t2528, name);
                (void)_t2529;
                Str_delete(_t2528, &(Bool){1});
                Str *_t2530 = Str_lit(".h", 2ULL);
                (void)_t2530;
                Str *h_path = Str_concat(_t2529, _t2530);
                (void)h_path;
                Str_delete(_t2529, &(Bool){1});
                Str_delete(_t2530, &(Bool){1});
                Str *_t2531 = Str_lit("gen/til/", 8ULL);
                (void)_t2531;
                Str *_t2532 = Str_concat(_t2531, name);
                (void)_t2532;
                Str_delete(_t2531, &(Bool){1});
                Str *_t2533 = Str_lit(".til", 4ULL);
                (void)_t2533;
                Str *til_path = Str_concat(_t2532, _t2533);
                (void)til_path;
                Str_delete(_t2532, &(Bool){1});
                Str_delete(_t2533, &(Bool){1});
                I32 _t2534 = build_header(ast, h_path);
                (void)_t2534;
                result = _t2534;
                ;
                I32 _t2535 = 0;
                (void)_t2535;
                Bool _t2536 = I32_eq(result, _t2535);
                (void)_t2536;
                ;
                if (_t2536) {
                    I32 _t2472 = build_til_binding(ast, til_path, name);
                    (void)_t2472;
                    result = _t2472;
                    ;
                }
                ;
                I32 _t2537 = 0;
                (void)_t2537;
                Str *_t2538 = Str_lit("translate", 9ULL);
                (void)_t2538;
                Bool _t2539 = I32_eq(result, _t2537);
                (void)_t2539;
                ;
                Bool _t2540; { Bool *_hp = (Bool *)Str_eq(command, _t2538); _t2540 = *_hp; free(_hp); }
                (void)_t2540;
                Str_delete(_t2538, &(Bool){1});
                Bool _t2541 = Bool_and(_t2539, _t2540);
                (void)_t2541;
                ;
                ;
                if (_t2541) {
                    Str *_t2473 = Str_lit("Str", 3ULL);
                    (void)_t2473;
                    U64 _t2474; { U64 *_hp = (U64 *)Str_size(); _t2474 = *_hp; free(_hp); }
                    (void)_t2474;
                    U64 _t2475 = 1;
                    (void)_t2475;
                    Array *_va67 = Array_new(_t2473, &(U64){_t2474}, &(U64){_t2475});
                    (void)_va67;
                    Str_delete(_t2473, &(Bool){1});
                    ;
                    ;
                    Str *_t2476 = Str_lit("Generated: ", 11ULL);
                    (void)_t2476;
                    U64 _t2477 = 0;
                    (void)_t2477;
                    Str *_t2478 = Str_concat(_t2476, c_path);
                    (void)_t2478;
                    Str_delete(_t2476, &(Bool){1});
                    Array_set(_va67, &(U64){_t2477}, _t2478);
                    ;
                    println(_va67);
                    Str *_t2479 = Str_lit("Str", 3ULL);
                    (void)_t2479;
                    U64 _t2480; { U64 *_hp = (U64 *)Str_size(); _t2480 = *_hp; free(_hp); }
                    (void)_t2480;
                    U64 _t2481 = 1;
                    (void)_t2481;
                    Array *_va68 = Array_new(_t2479, &(U64){_t2480}, &(U64){_t2481});
                    (void)_va68;
                    Str_delete(_t2479, &(Bool){1});
                    ;
                    ;
                    Str *_t2482 = Str_lit("Generated: ", 11ULL);
                    (void)_t2482;
                    U64 _t2483 = 0;
                    (void)_t2483;
                    Str *_t2484 = Str_concat(_t2482, h_path);
                    (void)_t2484;
                    Str_delete(_t2482, &(Bool){1});
                    Array_set(_va68, &(U64){_t2483}, _t2484);
                    ;
                    println(_va68);
                    Str *_t2485 = Str_lit("Str", 3ULL);
                    (void)_t2485;
                    U64 _t2486; { U64 *_hp = (U64 *)Str_size(); _t2486 = *_hp; free(_hp); }
                    (void)_t2486;
                    U64 _t2487 = 1;
                    (void)_t2487;
                    Array *_va69 = Array_new(_t2485, &(U64){_t2486}, &(U64){_t2487});
                    (void)_va69;
                    Str_delete(_t2485, &(Bool){1});
                    ;
                    ;
                    Str *_t2488 = Str_lit("Generated: ", 11ULL);
                    (void)_t2488;
                    U64 _t2489 = 0;
                    (void)_t2489;
                    Str *_t2490 = Str_concat(_t2488, til_path);
                    (void)_t2490;
                    Str_delete(_t2488, &(Bool){1});
                    Array_set(_va69, &(U64){_t2489}, _t2490);
                    ;
                    println(_va69);
                }
                ;
                I32 _t2542 = 0;
                (void)_t2542;
                Str *_t2543 = Str_lit("build", 5ULL);
                (void)_t2543;
                Bool _t2544 = I32_eq(result, _t2542);
                (void)_t2544;
                ;
                Bool _t2545; { Bool *_hp = (Bool *)Str_eq(command, _t2543); _t2545 = *_hp; free(_hp); }
                (void)_t2545;
                Str_delete(_t2543, &(Bool){1});
                Bool _t2546 = Bool_and(_t2544, _t2545);
                (void)_t2546;
                ;
                ;
                if (_t2546) {
                    I32 _t2525 = til_compile_lib(c_path, name, ext_c_path, user_c, lflags);
                    (void)_t2525;
                    result = _t2525;
                    ;
                    I32 _t2526 = 0;
                    (void)_t2526;
                    Bool _t2527 = I32_eq(result, _t2526);
                    (void)_t2527;
                    ;
                    if (_t2527) {
                        Str *_t2491 = Str_lit("Str", 3ULL);
                        (void)_t2491;
                        U64 _t2492; { U64 *_hp = (U64 *)Str_size(); _t2492 = *_hp; free(_hp); }
                        (void)_t2492;
                        U64 _t2493 = 1;
                        (void)_t2493;
                        Array *_va70 = Array_new(_t2491, &(U64){_t2492}, &(U64){_t2493});
                        (void)_va70;
                        Str_delete(_t2491, &(Bool){1});
                        ;
                        ;
                        Str *_t2494 = Str_lit("Generated: ", 11ULL);
                        (void)_t2494;
                        U64 _t2495 = 0;
                        (void)_t2495;
                        Str *_t2496 = Str_concat(_t2494, c_path);
                        (void)_t2496;
                        Str_delete(_t2494, &(Bool){1});
                        Array_set(_va70, &(U64){_t2495}, _t2496);
                        ;
                        println(_va70);
                        Str *_t2497 = Str_lit("Str", 3ULL);
                        (void)_t2497;
                        U64 _t2498; { U64 *_hp = (U64 *)Str_size(); _t2498 = *_hp; free(_hp); }
                        (void)_t2498;
                        U64 _t2499 = 1;
                        (void)_t2499;
                        Array *_va71 = Array_new(_t2497, &(U64){_t2498}, &(U64){_t2499});
                        (void)_va71;
                        Str_delete(_t2497, &(Bool){1});
                        ;
                        ;
                        Str *_t2500 = Str_lit("Generated: ", 11ULL);
                        (void)_t2500;
                        U64 _t2501 = 0;
                        (void)_t2501;
                        Str *_t2502 = Str_concat(_t2500, h_path);
                        (void)_t2502;
                        Str_delete(_t2500, &(Bool){1});
                        Array_set(_va71, &(U64){_t2501}, _t2502);
                        ;
                        println(_va71);
                        Str *_t2503 = Str_lit("Str", 3ULL);
                        (void)_t2503;
                        U64 _t2504; { U64 *_hp = (U64 *)Str_size(); _t2504 = *_hp; free(_hp); }
                        (void)_t2504;
                        U64 _t2505 = 1;
                        (void)_t2505;
                        Array *_va72 = Array_new(_t2503, &(U64){_t2504}, &(U64){_t2505});
                        (void)_va72;
                        Str_delete(_t2503, &(Bool){1});
                        ;
                        ;
                        Str *_t2506 = Str_lit("Generated: ", 11ULL);
                        (void)_t2506;
                        U64 _t2507 = 0;
                        (void)_t2507;
                        Str *_t2508 = Str_concat(_t2506, til_path);
                        (void)_t2508;
                        Str_delete(_t2506, &(Bool){1});
                        Array_set(_va72, &(U64){_t2507}, _t2508);
                        ;
                        println(_va72);
                        Str *_t2509 = Str_lit("Str", 3ULL);
                        (void)_t2509;
                        U64 _t2510; { U64 *_hp = (U64 *)Str_size(); _t2510 = *_hp; free(_hp); }
                        (void)_t2510;
                        U64 _t2511 = 1;
                        (void)_t2511;
                        Array *_va73 = Array_new(_t2509, &(U64){_t2510}, &(U64){_t2511});
                        (void)_va73;
                        Str_delete(_t2509, &(Bool){1});
                        ;
                        ;
                        Str *_t2512 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2512;
                        Str *_t2513 = Str_concat(_t2512, name);
                        (void)_t2513;
                        Str_delete(_t2512, &(Bool){1});
                        Str *_t2514 = Str_lit(".so", 3ULL);
                        (void)_t2514;
                        U64 _t2515 = 0;
                        (void)_t2515;
                        Str *_t2516 = Str_concat(_t2513, _t2514);
                        (void)_t2516;
                        Str_delete(_t2513, &(Bool){1});
                        Str_delete(_t2514, &(Bool){1});
                        Array_set(_va73, &(U64){_t2515}, _t2516);
                        ;
                        println(_va73);
                        Str *_t2517 = Str_lit("Str", 3ULL);
                        (void)_t2517;
                        U64 _t2518; { U64 *_hp = (U64 *)Str_size(); _t2518 = *_hp; free(_hp); }
                        (void)_t2518;
                        U64 _t2519 = 1;
                        (void)_t2519;
                        Array *_va74 = Array_new(_t2517, &(U64){_t2518}, &(U64){_t2519});
                        (void)_va74;
                        Str_delete(_t2517, &(Bool){1});
                        ;
                        ;
                        Str *_t2520 = Str_lit("Generated: gen/lib/lib", 22ULL);
                        (void)_t2520;
                        Str *_t2521 = Str_concat(_t2520, name);
                        (void)_t2521;
                        Str_delete(_t2520, &(Bool){1});
                        Str *_t2522 = Str_lit(".a", 2ULL);
                        (void)_t2522;
                        U64 _t2523 = 0;
                        (void)_t2523;
                        Str *_t2524 = Str_concat(_t2521, _t2522);
                        (void)_t2524;
                        Str_delete(_t2521, &(Bool){1});
                        Str_delete(_t2522, &(Bool){1});
                        Array_set(_va74, &(U64){_t2523}, _t2524);
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
            I32 _t2590 = 0;
            (void)_t2590;
            Bool _t2591 = I32_eq(result, _t2590);
            (void)_t2591;
            ;
            Bool _t2592 = Bool_not(do_lib);
            (void)_t2592;
            Str *_t2593 = Str_lit("translate", 9ULL);
            (void)_t2593;
            Bool _t2594 = Bool_and(_t2591, _t2592);
            (void)_t2594;
            ;
            ;
            Bool _t2595; { Bool *_hp = (Bool *)Str_eq(command, _t2593); _t2595 = *_hp; free(_hp); }
            (void)_t2595;
            Str_delete(_t2593, &(Bool){1});
            Bool _t2596 = Bool_and(_t2594, _t2595);
            (void)_t2596;
            ;
            ;
            if (_t2596) {
                Str *_t2547 = Str_lit("Str", 3ULL);
                (void)_t2547;
                U64 _t2548; { U64 *_hp = (U64 *)Str_size(); _t2548 = *_hp; free(_hp); }
                (void)_t2548;
                U64 _t2549 = 1;
                (void)_t2549;
                Array *_va75 = Array_new(_t2547, &(U64){_t2548}, &(U64){_t2549});
                (void)_va75;
                Str_delete(_t2547, &(Bool){1});
                ;
                ;
                Str *_t2550 = Str_lit("Generated: ", 11ULL);
                (void)_t2550;
                U64 _t2551 = 0;
                (void)_t2551;
                Str *_t2552 = Str_concat(_t2550, c_path);
                (void)_t2552;
                Str_delete(_t2550, &(Bool){1});
                Array_set(_va75, &(U64){_t2551}, _t2552);
                ;
                println(_va75);
            }
            ;
            I32 _t2597 = 0;
            (void)_t2597;
            Bool _t2598 = I32_eq(result, _t2597);
            (void)_t2598;
            ;
            Bool _t2599 = Bool_not(do_lib);
            (void)_t2599;
            Str *_t2600 = Str_lit("translate", 9ULL);
            (void)_t2600;
            Bool _t2601; { Bool *_hp = (Bool *)Str_eq(command, _t2600); _t2601 = *_hp; free(_hp); }
            (void)_t2601;
            Str_delete(_t2600, &(Bool){1});
            Bool _t2602 = Bool_and(_t2598, _t2599);
            (void)_t2602;
            ;
            ;
            Bool _t2603 = Bool_not(_t2601);
            (void)_t2603;
            ;
            Bool _t2604 = Bool_and(_t2602, _t2603);
            (void)_t2604;
            ;
            ;
            if (_t2604) {
                I32 _t2553 = til_compile_c(c_path, bin_path, ext_c_path, user_c, lflags);
                (void)_t2553;
                result = _t2553;
                ;
            }
            ;
            Str_delete(c_path, &(Bool){1});
            I32 _t2605 = 0;
            (void)_t2605;
            Bool _t2606 = I32_eq(result, _t2605);
            (void)_t2606;
            ;
            Bool _t2607 = Bool_not(do_lib);
            (void)_t2607;
            ;
            Str *_t2608 = Str_lit("run", 3ULL);
            (void)_t2608;
            Bool _t2609 = Bool_and(_t2606, _t2607);
            (void)_t2609;
            ;
            ;
            Bool _t2610; { Bool *_hp = (Bool *)Str_eq(command, _t2608); _t2610 = *_hp; free(_hp); }
            (void)_t2610;
            Str_delete(_t2608, &(Bool){1});
            Bool _t2611 = Bool_and(_t2609, _t2610);
            (void)_t2611;
            ;
            ;
            if (_t2611) {
                Str *cmd = Str_clone(bin_path);
                (void)cmd;
                U64 *ui = malloc(sizeof(U64));
                *ui = 0;
                (void)ui;
                while (1) {
                    U64 _t2555; { U64 *_hp = (U64 *)Vec_len(user_argv); _t2555 = *_hp; free(_hp); }
                    (void)_t2555;
                    Bool _wcond2554; { Bool *_hp = (Bool *)U64_lt(ui, &(U64){_t2555}); _wcond2554 = *_hp; free(_hp); }
                    (void)_wcond2554;
                    ;
                    if (_wcond2554) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    Str *uarg = Vec_get(user_argv, ui);
                    (void)uarg;
                    Str *_t2556 = Str_lit(" '", 2ULL);
                    (void)_t2556;
                    Str *_t2557 = Str_concat(cmd, _t2556);
                    (void)_t2557;
                    Str_delete(_t2556, &(Bool){1});
                    Str *_t2558 = Str_concat(_t2557, uarg);
                    (void)_t2558;
                    Str_delete(_t2557, &(Bool){1});
                    Str *_t2559 = Str_lit("'", 1ULL);
                    (void)_t2559;
                    cmd = Str_concat(_t2558, _t2559);
                    Str_delete(_t2558, &(Bool){1});
                    Str_delete(_t2559, &(Bool){1});
                    U64 _t2560 = 1;
                    (void)_t2560;
                    U64 _t2561 = U64_add(DEREF(ui), _t2560);
                    (void)_t2561;
                    ;
                    *ui = _t2561;
                    ;
                }
                U64_delete(ui, &(Bool){1});
                I32 _t2562 = til_system(cmd);
                (void)_t2562;
                Str_delete(cmd, &(Bool){1});
                result = _t2562;
                ;
            }
            ;
            Str_delete(bin_path, &(Bool){1});
        } else {
            Str *_t2628 = Str_lit("ast", 3ULL);
            (void)_t2628;
            Bool _t2629; { Bool *_hp = (Bool *)Str_eq(command, _t2628); _t2629 = *_hp; free(_hp); }
            (void)_t2629;
            Str_delete(_t2628, &(Bool){1});
            if (_t2629) {
                Str *_t2612 = Str_lit("Str", 3ULL);
                (void)_t2612;
                U64 _t2613; { U64 *_hp = (U64 *)Str_size(); _t2613 = *_hp; free(_hp); }
                (void)_t2613;
                U64 _t2614 = 1;
                (void)_t2614;
                Array *_va76 = Array_new(_t2612, &(U64){_t2613}, &(U64){_t2614});
                (void)_va76;
                Str_delete(_t2612, &(Bool){1});
                ;
                ;
                Str *_t2615 = Str_lit("mode: ", 6ULL);
                (void)_t2615;
                U64 _t2616 = 0;
                (void)_t2616;
                Str *_t2617 = Str_concat(_t2615, &cur_mode->name);
                (void)_t2617;
                Str_delete(_t2615, &(Bool){1});
                Array_set(_va76, &(U64){_t2616}, _t2617);
                ;
                println(_va76);
                U32 _t2618 = 0;
                (void)_t2618;
                ast_print(ast, _t2618);
                ;
            } else {
                Str *_t2619 = Str_lit("Str", 3ULL);
                (void)_t2619;
                U64 _t2620; { U64 *_hp = (U64 *)Str_size(); _t2620 = *_hp; free(_hp); }
                (void)_t2620;
                U64 _t2621 = 1;
                (void)_t2621;
                Array *_va77 = Array_new(_t2619, &(U64){_t2620}, &(U64){_t2621});
                (void)_va77;
                Str_delete(_t2619, &(Bool){1});
                ;
                ;
                Str *_t2622 = Str_lit("error: unknown command '", 24ULL);
                (void)_t2622;
                Str *_t2623 = Str_concat(_t2622, command);
                (void)_t2623;
                Str_delete(_t2622, &(Bool){1});
                Str *_t2624 = Str_lit("'", 1ULL);
                (void)_t2624;
                U64 _t2625 = 0;
                (void)_t2625;
                Str *_t2626 = Str_concat(_t2623, _t2624);
                (void)_t2626;
                Str_delete(_t2623, &(Bool){1});
                Str_delete(_t2624, &(Bool){1});
                Array_set(_va77, &(U64){_t2625}, _t2626);
                ;
                println(_va77);
                usage();
                I32 _t2627 = 1;
                (void)_t2627;
                result = _t2627;
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
    I64 _t2715 = I32_to_i64(result);
    (void)_t2715;
    ;
    exit(_t2715);
    ;
    return 0;
}

