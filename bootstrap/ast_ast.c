TilType *TilType_Unknown() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Unknown };
    return r;
}
TilType *TilType_None() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_None };
    return r;
}
TilType *TilType_I64() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I64 };
    return r;
}
TilType *TilType_U8() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U8 };
    return r;
}
TilType *TilType_I16() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I16 };
    return r;
}
TilType *TilType_I32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_I32 };
    return r;
}
TilType *TilType_U32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U32 };
    return r;
}
TilType *TilType_U64() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_U64 };
    return r;
}
TilType *TilType_F32() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_F32 };
    return r;
}
TilType *TilType_Bool() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Bool };
    return r;
}
TilType *TilType_Struct() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Struct };
    return r;
}
TilType *TilType_StructDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_StructDef };
    return r;
}
TilType *TilType_Enum() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Enum };
    return r;
}
TilType *TilType_EnumDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_EnumDef };
    return r;
}
TilType *TilType_FuncDef() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_FuncDef };
    return r;
}
TilType *TilType_FuncPtr() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_FuncPtr };
    return r;
}
TilType *TilType_Dynamic() {
    TilType *r = malloc(sizeof(TilType));
    *r = (TilType){ .tag = TilType_TAG_Dynamic };
    return r;
}
Bool *TilType_is_Unknown(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Unknown);
    return r;
}
Bool *TilType_is_None(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_None);
    return r;
}
Bool *TilType_is_I64(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I64);
    return r;
}
Bool *TilType_is_U8(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U8);
    return r;
}
Bool *TilType_is_I16(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I16);
    return r;
}
Bool *TilType_is_I32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_I32);
    return r;
}
Bool *TilType_is_U32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U32);
    return r;
}
Bool *TilType_is_U64(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_U64);
    return r;
}
Bool *TilType_is_F32(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_F32);
    return r;
}
Bool *TilType_is_Bool(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Bool);
    return r;
}
Bool *TilType_is_Struct(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Struct);
    return r;
}
Bool *TilType_is_StructDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_StructDef);
    return r;
}
Bool *TilType_is_Enum(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Enum);
    return r;
}
Bool *TilType_is_EnumDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_EnumDef);
    return r;
}
Bool *TilType_is_FuncDef(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_FuncDef);
    return r;
}
Bool *TilType_is_FuncPtr(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_FuncPtr);
    return r;
}
Bool *TilType_is_Dynamic(TilType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TilType_TAG_Dynamic);
    return r;
}
Bool * TilType_eq(TilType * self, TilType * other) {
    (void)self;
    (void)other;
    Bool _t2202; { Bool *_hp = (Bool *)TilType_is_Unknown(self); _t2202 = *_hp; free(_hp); }
    (void)_t2202;
    if (_t2202) {
        Bool _t2185; { Bool *_hp = (Bool *)TilType_is_Unknown(other); _t2185 = *_hp; free(_hp); }
        (void)_t2185;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2185; return _r; }
    }
    ;
    Bool _t2203; { Bool *_hp = (Bool *)TilType_is_None(self); _t2203 = *_hp; free(_hp); }
    (void)_t2203;
    if (_t2203) {
        Bool _t2186; { Bool *_hp = (Bool *)TilType_is_None(other); _t2186 = *_hp; free(_hp); }
        (void)_t2186;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2186; return _r; }
    }
    ;
    Bool _t2204; { Bool *_hp = (Bool *)TilType_is_I64(self); _t2204 = *_hp; free(_hp); }
    (void)_t2204;
    if (_t2204) {
        Bool _t2187; { Bool *_hp = (Bool *)TilType_is_I64(other); _t2187 = *_hp; free(_hp); }
        (void)_t2187;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2187; return _r; }
    }
    ;
    Bool _t2205; { Bool *_hp = (Bool *)TilType_is_U8(self); _t2205 = *_hp; free(_hp); }
    (void)_t2205;
    if (_t2205) {
        Bool _t2188; { Bool *_hp = (Bool *)TilType_is_U8(other); _t2188 = *_hp; free(_hp); }
        (void)_t2188;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2188; return _r; }
    }
    ;
    Bool _t2206; { Bool *_hp = (Bool *)TilType_is_I16(self); _t2206 = *_hp; free(_hp); }
    (void)_t2206;
    if (_t2206) {
        Bool _t2189; { Bool *_hp = (Bool *)TilType_is_I16(other); _t2189 = *_hp; free(_hp); }
        (void)_t2189;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2189; return _r; }
    }
    ;
    Bool _t2207; { Bool *_hp = (Bool *)TilType_is_I32(self); _t2207 = *_hp; free(_hp); }
    (void)_t2207;
    if (_t2207) {
        Bool _t2190; { Bool *_hp = (Bool *)TilType_is_I32(other); _t2190 = *_hp; free(_hp); }
        (void)_t2190;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2190; return _r; }
    }
    ;
    Bool _t2208; { Bool *_hp = (Bool *)TilType_is_U32(self); _t2208 = *_hp; free(_hp); }
    (void)_t2208;
    if (_t2208) {
        Bool _t2191; { Bool *_hp = (Bool *)TilType_is_U32(other); _t2191 = *_hp; free(_hp); }
        (void)_t2191;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2191; return _r; }
    }
    ;
    Bool _t2209; { Bool *_hp = (Bool *)TilType_is_U64(self); _t2209 = *_hp; free(_hp); }
    (void)_t2209;
    if (_t2209) {
        Bool _t2192; { Bool *_hp = (Bool *)TilType_is_U64(other); _t2192 = *_hp; free(_hp); }
        (void)_t2192;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2192; return _r; }
    }
    ;
    Bool _t2210; { Bool *_hp = (Bool *)TilType_is_F32(self); _t2210 = *_hp; free(_hp); }
    (void)_t2210;
    if (_t2210) {
        Bool _t2193; { Bool *_hp = (Bool *)TilType_is_F32(other); _t2193 = *_hp; free(_hp); }
        (void)_t2193;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2193; return _r; }
    }
    ;
    Bool _t2211; { Bool *_hp = (Bool *)TilType_is_Bool(self); _t2211 = *_hp; free(_hp); }
    (void)_t2211;
    if (_t2211) {
        Bool _t2194; { Bool *_hp = (Bool *)TilType_is_Bool(other); _t2194 = *_hp; free(_hp); }
        (void)_t2194;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2194; return _r; }
    }
    ;
    Bool _t2212; { Bool *_hp = (Bool *)TilType_is_Struct(self); _t2212 = *_hp; free(_hp); }
    (void)_t2212;
    if (_t2212) {
        Bool _t2195; { Bool *_hp = (Bool *)TilType_is_Struct(other); _t2195 = *_hp; free(_hp); }
        (void)_t2195;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2195; return _r; }
    }
    ;
    Bool _t2213; { Bool *_hp = (Bool *)TilType_is_StructDef(self); _t2213 = *_hp; free(_hp); }
    (void)_t2213;
    if (_t2213) {
        Bool _t2196; { Bool *_hp = (Bool *)TilType_is_StructDef(other); _t2196 = *_hp; free(_hp); }
        (void)_t2196;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2196; return _r; }
    }
    ;
    Bool _t2214; { Bool *_hp = (Bool *)TilType_is_Enum(self); _t2214 = *_hp; free(_hp); }
    (void)_t2214;
    if (_t2214) {
        Bool _t2197; { Bool *_hp = (Bool *)TilType_is_Enum(other); _t2197 = *_hp; free(_hp); }
        (void)_t2197;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2197; return _r; }
    }
    ;
    Bool _t2215; { Bool *_hp = (Bool *)TilType_is_EnumDef(self); _t2215 = *_hp; free(_hp); }
    (void)_t2215;
    if (_t2215) {
        Bool _t2198; { Bool *_hp = (Bool *)TilType_is_EnumDef(other); _t2198 = *_hp; free(_hp); }
        (void)_t2198;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2198; return _r; }
    }
    ;
    Bool _t2216; { Bool *_hp = (Bool *)TilType_is_FuncDef(self); _t2216 = *_hp; free(_hp); }
    (void)_t2216;
    if (_t2216) {
        Bool _t2199; { Bool *_hp = (Bool *)TilType_is_FuncDef(other); _t2199 = *_hp; free(_hp); }
        (void)_t2199;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2199; return _r; }
    }
    ;
    Bool _t2217; { Bool *_hp = (Bool *)TilType_is_FuncPtr(self); _t2217 = *_hp; free(_hp); }
    (void)_t2217;
    if (_t2217) {
        Bool _t2200; { Bool *_hp = (Bool *)TilType_is_FuncPtr(other); _t2200 = *_hp; free(_hp); }
        (void)_t2200;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2200; return _r; }
    }
    ;
    Bool _t2218; { Bool *_hp = (Bool *)TilType_is_Dynamic(self); _t2218 = *_hp; free(_hp); }
    (void)_t2218;
    if (_t2218) {
        Bool _t2201; { Bool *_hp = (Bool *)TilType_is_Dynamic(other); _t2201 = *_hp; free(_hp); }
        (void)_t2201;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2201; return _r; }
    }
    ;
    Bool _t2219 = 0;
    (void)_t2219;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2219; return _r; }
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t2220; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t2220 = *_hp; free(_hp); }
    (void)_t2220;
    if (_t2220) {
        ;
        return TilType_Unknown();
    }
    ;
    Bool _t2221; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t2221 = *_hp; free(_hp); }
    (void)_t2221;
    if (_t2221) {
        ;
        return TilType_None();
    }
    ;
    Bool _t2222; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t2222 = *_hp; free(_hp); }
    (void)_t2222;
    if (_t2222) {
        ;
        return TilType_I64();
    }
    ;
    Bool _t2223; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t2223 = *_hp; free(_hp); }
    (void)_t2223;
    if (_t2223) {
        ;
        return TilType_U8();
    }
    ;
    Bool _t2224; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t2224 = *_hp; free(_hp); }
    (void)_t2224;
    if (_t2224) {
        ;
        return TilType_I16();
    }
    ;
    Bool _t2225; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t2225 = *_hp; free(_hp); }
    (void)_t2225;
    if (_t2225) {
        ;
        return TilType_I32();
    }
    ;
    Bool _t2226; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t2226 = *_hp; free(_hp); }
    (void)_t2226;
    if (_t2226) {
        ;
        return TilType_U32();
    }
    ;
    Bool _t2227; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t2227 = *_hp; free(_hp); }
    (void)_t2227;
    if (_t2227) {
        ;
        return TilType_U64();
    }
    ;
    Bool _t2228; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t2228 = *_hp; free(_hp); }
    (void)_t2228;
    if (_t2228) {
        ;
        return TilType_F32();
    }
    ;
    Bool _t2229; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t2229 = *_hp; free(_hp); }
    (void)_t2229;
    if (_t2229) {
        ;
        return TilType_Bool();
    }
    ;
    Bool _t2230; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t2230 = *_hp; free(_hp); }
    (void)_t2230;
    if (_t2230) {
        ;
        return TilType_Struct();
    }
    ;
    Bool _t2231; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t2231 = *_hp; free(_hp); }
    (void)_t2231;
    if (_t2231) {
        ;
        return TilType_StructDef();
    }
    ;
    Bool _t2232; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t2232 = *_hp; free(_hp); }
    (void)_t2232;
    if (_t2232) {
        ;
        return TilType_Enum();
    }
    ;
    Bool _t2233; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t2233 = *_hp; free(_hp); }
    (void)_t2233;
    if (_t2233) {
        ;
        return TilType_EnumDef();
    }
    ;
    Bool _t2234; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t2234 = *_hp; free(_hp); }
    (void)_t2234;
    if (_t2234) {
        ;
        return TilType_FuncDef();
    }
    ;
    Bool _t2235; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t2235 = *_hp; free(_hp); }
    (void)_t2235;
    if (_t2235) {
        ;
        return TilType_FuncPtr();
    }
    ;
    return TilType_Dynamic();
}

void TilType_delete(TilType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TilType_to_str(TilType * self) {
    (void)self;
    Bool _t2253; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Unknown()); _t2253 = *_hp; free(_hp); }
    (void)_t2253;
    if (_t2253) {
        Str *_t2236 = Str_lit("Unknown", 7ULL);
        (void)_t2236;
        ;
        return _t2236;
    }
    ;
    Bool _t2254; { Bool *_hp = (Bool *)TilType_eq(self, TilType_None()); _t2254 = *_hp; free(_hp); }
    (void)_t2254;
    if (_t2254) {
        Str *_t2237 = Str_lit("None", 4ULL);
        (void)_t2237;
        ;
        return _t2237;
    }
    ;
    Bool _t2255; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I64()); _t2255 = *_hp; free(_hp); }
    (void)_t2255;
    if (_t2255) {
        Str *_t2238 = Str_lit("I64", 3ULL);
        (void)_t2238;
        ;
        return _t2238;
    }
    ;
    Bool _t2256; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U8()); _t2256 = *_hp; free(_hp); }
    (void)_t2256;
    if (_t2256) {
        Str *_t2239 = Str_lit("U8", 2ULL);
        (void)_t2239;
        ;
        return _t2239;
    }
    ;
    Bool _t2257; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I16()); _t2257 = *_hp; free(_hp); }
    (void)_t2257;
    if (_t2257) {
        Str *_t2240 = Str_lit("I16", 3ULL);
        (void)_t2240;
        ;
        return _t2240;
    }
    ;
    Bool _t2258; { Bool *_hp = (Bool *)TilType_eq(self, TilType_I32()); _t2258 = *_hp; free(_hp); }
    (void)_t2258;
    if (_t2258) {
        Str *_t2241 = Str_lit("I32", 3ULL);
        (void)_t2241;
        ;
        return _t2241;
    }
    ;
    Bool _t2259; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U32()); _t2259 = *_hp; free(_hp); }
    (void)_t2259;
    if (_t2259) {
        Str *_t2242 = Str_lit("U32", 3ULL);
        (void)_t2242;
        ;
        return _t2242;
    }
    ;
    Bool _t2260; { Bool *_hp = (Bool *)TilType_eq(self, TilType_U64()); _t2260 = *_hp; free(_hp); }
    (void)_t2260;
    if (_t2260) {
        Str *_t2243 = Str_lit("U64", 3ULL);
        (void)_t2243;
        ;
        return _t2243;
    }
    ;
    Bool _t2261; { Bool *_hp = (Bool *)TilType_eq(self, TilType_F32()); _t2261 = *_hp; free(_hp); }
    (void)_t2261;
    if (_t2261) {
        Str *_t2244 = Str_lit("F32", 3ULL);
        (void)_t2244;
        ;
        return _t2244;
    }
    ;
    Bool _t2262; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Bool()); _t2262 = *_hp; free(_hp); }
    (void)_t2262;
    if (_t2262) {
        Str *_t2245 = Str_lit("Bool", 4ULL);
        (void)_t2245;
        ;
        return _t2245;
    }
    ;
    Bool _t2263; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Struct()); _t2263 = *_hp; free(_hp); }
    (void)_t2263;
    if (_t2263) {
        Str *_t2246 = Str_lit("Struct", 6ULL);
        (void)_t2246;
        ;
        return _t2246;
    }
    ;
    Bool _t2264; { Bool *_hp = (Bool *)TilType_eq(self, TilType_StructDef()); _t2264 = *_hp; free(_hp); }
    (void)_t2264;
    if (_t2264) {
        Str *_t2247 = Str_lit("StructDef", 9ULL);
        (void)_t2247;
        ;
        return _t2247;
    }
    ;
    Bool _t2265; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Enum()); _t2265 = *_hp; free(_hp); }
    (void)_t2265;
    if (_t2265) {
        Str *_t2248 = Str_lit("Enum", 4ULL);
        (void)_t2248;
        ;
        return _t2248;
    }
    ;
    Bool _t2266; { Bool *_hp = (Bool *)TilType_eq(self, TilType_EnumDef()); _t2266 = *_hp; free(_hp); }
    (void)_t2266;
    if (_t2266) {
        Str *_t2249 = Str_lit("EnumDef", 7ULL);
        (void)_t2249;
        ;
        return _t2249;
    }
    ;
    Bool _t2267; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncDef()); _t2267 = *_hp; free(_hp); }
    (void)_t2267;
    if (_t2267) {
        Str *_t2250 = Str_lit("FuncDef", 7ULL);
        (void)_t2250;
        ;
        return _t2250;
    }
    ;
    Bool _t2268; { Bool *_hp = (Bool *)TilType_eq(self, TilType_FuncPtr()); _t2268 = *_hp; free(_hp); }
    (void)_t2268;
    if (_t2268) {
        Str *_t2251 = Str_lit("FuncPtr", 7ULL);
        (void)_t2251;
        ;
        return _t2251;
    }
    ;
    Bool _t2269; { Bool *_hp = (Bool *)TilType_eq(self, TilType_Dynamic()); _t2269 = *_hp; free(_hp); }
    (void)_t2269;
    if (_t2269) {
        Str *_t2252 = Str_lit("Dynamic", 7ULL);
        (void)_t2252;
        ;
        return _t2252;
    }
    ;
    Str *_t2270 = Str_lit("unknown", 7ULL);
    (void)_t2270;
    return _t2270;
}

U64 *TilType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TilType);
    return r;
}


Str * til_type_name_c(TilType * t) {
    (void)t;
    {
        TilType *_sw2272 = TilType_clone(t);
        (void)_sw2272;
        Bool _t2307; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Unknown()); _t2307 = *_hp; free(_hp); }
        (void)_t2307;
        if (_t2307) {
            Str *_t2273 = Str_lit("unknown", 7ULL);
            (void)_t2273;
            TilType_delete(_sw2272, &(Bool){1});
            ;
            return _t2273;
        } else {
            Bool _t2306; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_None()); _t2306 = *_hp; free(_hp); }
            (void)_t2306;
            if (_t2306) {
                Str *_t2274 = Str_lit("None", 4ULL);
                (void)_t2274;
                ;
                TilType_delete(_sw2272, &(Bool){1});
                ;
                return _t2274;
            } else {
                Bool _t2305; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I64()); _t2305 = *_hp; free(_hp); }
                (void)_t2305;
                if (_t2305) {
                    Str *_t2275 = Str_lit("I64", 3ULL);
                    (void)_t2275;
                    ;
                    ;
                    TilType_delete(_sw2272, &(Bool){1});
                    ;
                    return _t2275;
                } else {
                    Bool _t2304; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U8()); _t2304 = *_hp; free(_hp); }
                    (void)_t2304;
                    if (_t2304) {
                        Str *_t2276 = Str_lit("U8", 2ULL);
                        (void)_t2276;
                        ;
                        ;
                        ;
                        TilType_delete(_sw2272, &(Bool){1});
                        ;
                        return _t2276;
                    } else {
                        Bool _t2303; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I16()); _t2303 = *_hp; free(_hp); }
                        (void)_t2303;
                        if (_t2303) {
                            Str *_t2277 = Str_lit("I16", 3ULL);
                            (void)_t2277;
                            ;
                            ;
                            ;
                            ;
                            TilType_delete(_sw2272, &(Bool){1});
                            ;
                            return _t2277;
                        } else {
                            Bool _t2302; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_I32()); _t2302 = *_hp; free(_hp); }
                            (void)_t2302;
                            if (_t2302) {
                                Str *_t2278 = Str_lit("I32", 3ULL);
                                (void)_t2278;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TilType_delete(_sw2272, &(Bool){1});
                                ;
                                return _t2278;
                            } else {
                                Bool _t2301; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U32()); _t2301 = *_hp; free(_hp); }
                                (void)_t2301;
                                if (_t2301) {
                                    Str *_t2279 = Str_lit("U32", 3ULL);
                                    (void)_t2279;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TilType_delete(_sw2272, &(Bool){1});
                                    ;
                                    return _t2279;
                                } else {
                                    Bool _t2300; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_U64()); _t2300 = *_hp; free(_hp); }
                                    (void)_t2300;
                                    if (_t2300) {
                                        Str *_t2280 = Str_lit("U64", 3ULL);
                                        (void)_t2280;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TilType_delete(_sw2272, &(Bool){1});
                                        ;
                                        return _t2280;
                                    } else {
                                        Bool _t2299; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_F32()); _t2299 = *_hp; free(_hp); }
                                        (void)_t2299;
                                        if (_t2299) {
                                            Str *_t2281 = Str_lit("F32", 3ULL);
                                            (void)_t2281;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TilType_delete(_sw2272, &(Bool){1});
                                            ;
                                            return _t2281;
                                        } else {
                                            Bool _t2298; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Bool()); _t2298 = *_hp; free(_hp); }
                                            (void)_t2298;
                                            if (_t2298) {
                                                Str *_t2282 = Str_lit("Bool", 4ULL);
                                                (void)_t2282;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TilType_delete(_sw2272, &(Bool){1});
                                                ;
                                                return _t2282;
                                            } else {
                                                Bool _t2297; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Struct()); _t2297 = *_hp; free(_hp); }
                                                (void)_t2297;
                                                if (_t2297) {
                                                    Str *_t2283 = Str_lit("Struct", 6ULL);
                                                    (void)_t2283;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TilType_delete(_sw2272, &(Bool){1});
                                                    ;
                                                    return _t2283;
                                                } else {
                                                    Bool _t2296; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_StructDef()); _t2296 = *_hp; free(_hp); }
                                                    (void)_t2296;
                                                    if (_t2296) {
                                                        Str *_t2284 = Str_lit("StructDef", 9ULL);
                                                        (void)_t2284;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TilType_delete(_sw2272, &(Bool){1});
                                                        ;
                                                        return _t2284;
                                                    } else {
                                                        Bool _t2295; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Enum()); _t2295 = *_hp; free(_hp); }
                                                        (void)_t2295;
                                                        if (_t2295) {
                                                            Str *_t2285 = Str_lit("Enum", 4ULL);
                                                            (void)_t2285;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TilType_delete(_sw2272, &(Bool){1});
                                                            ;
                                                            return _t2285;
                                                        } else {
                                                            Bool _t2294; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_EnumDef()); _t2294 = *_hp; free(_hp); }
                                                            (void)_t2294;
                                                            if (_t2294) {
                                                                Str *_t2286 = Str_lit("EnumDef", 7ULL);
                                                                (void)_t2286;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TilType_delete(_sw2272, &(Bool){1});
                                                                ;
                                                                return _t2286;
                                                            } else {
                                                                Bool _t2293; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_FuncDef()); _t2293 = *_hp; free(_hp); }
                                                                (void)_t2293;
                                                                if (_t2293) {
                                                                    Str *_t2287 = Str_lit("FunctionDef", 11ULL);
                                                                    (void)_t2287;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TilType_delete(_sw2272, &(Bool){1});
                                                                    ;
                                                                    return _t2287;
                                                                } else {
                                                                    Bool _t2292; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_FuncPtr()); _t2292 = *_hp; free(_hp); }
                                                                    (void)_t2292;
                                                                    if (_t2292) {
                                                                        Str *_t2288 = Str_lit("Fn", 2ULL);
                                                                        (void)_t2288;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TilType_delete(_sw2272, &(Bool){1});
                                                                        ;
                                                                        return _t2288;
                                                                    } else {
                                                                        Bool _t2291; { Bool *_hp = (Bool *)TilType_eq(_sw2272, TilType_Dynamic()); _t2291 = *_hp; free(_hp); }
                                                                        (void)_t2291;
                                                                        if (_t2291) {
                                                                            Str *_t2289 = Str_lit("Dynamic", 7ULL);
                                                                            (void)_t2289;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2272, &(Bool){1});
                                                                            ;
                                                                            return _t2289;
                                                                        } else {
                                                                            Str *_t2290 = Str_lit("?", 1ULL);
                                                                            (void)_t2290;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TilType_delete(_sw2272, &(Bool){1});
                                                                            ;
                                                                            return _t2290;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TilType_delete(_sw2272, &(Bool){1});
        ;
    }
}

Bool * Declaration_eq(Declaration * a, Declaration * b) {
    (void)a;
    (void)b;
    Bool _t2308; { Bool *_hp = (Bool *)Str_eq(&a->name, &b->name); _t2308 = *_hp; free(_hp); }
    (void)_t2308;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2308; return _r; }
}

Str * Declaration_to_str(Declaration * self) {
    (void)self;
    { Str *_r = malloc(sizeof(Str)); *_r = self->name; return _r; }
}

Declaration * Declaration_clone(Declaration * self) {
    (void)self;
    Bool _t2309 = Bool_clone(&self->is_mut);
    (void)_t2309;
    Bool _t2310 = Bool_clone(&self->is_namespace);
    (void)_t2310;
    Bool _t2311 = Bool_clone(&self->is_ref);
    (void)_t2311;
    Bool _t2312 = Bool_clone(&self->is_own);
    (void)_t2312;
    I32 _t2313 = I32_clone(&self->field_offset);
    (void)_t2313;
    I32 _t2314 = I32_clone(&self->field_size);
    (void)_t2314;
    Declaration *_t2315 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); _t2315->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); _t2315->explicit_type = *_ca; free(_ca); }
    _t2315->is_mut = _t2309;
    _t2315->is_namespace = _t2310;
    _t2315->is_ref = _t2311;
    _t2315->is_own = _t2312;
    _t2315->field_offset = _t2313;
    _t2315->field_size = _t2314;
    _t2315->field_struct_def = self->field_struct_def;
    _t2315->fn_sig = self->fn_sig;
    (void)_t2315;
    ;
    ;
    ;
    ;
    ;
    ;
    return _t2315;
}

void Declaration_delete(Declaration * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t2316 = 0;
    (void)_t2316;
    Str_delete(&self->name, &(Bool){_t2316});
    ;
    Bool _t2317 = 0;
    (void)_t2317;
    Str_delete(&self->explicit_type, &(Bool){_t2317});
    ;
    Bool _t2318 = 0;
    (void)_t2318;
    Bool_delete(&self->is_mut, &(Bool){_t2318});
    ;
    Bool _t2319 = 0;
    (void)_t2319;
    Bool_delete(&self->is_namespace, &(Bool){_t2319});
    ;
    Bool _t2320 = 0;
    (void)_t2320;
    Bool_delete(&self->is_ref, &(Bool){_t2320});
    ;
    Bool _t2321 = 0;
    (void)_t2321;
    Bool_delete(&self->is_own, &(Bool){_t2321});
    ;
    Bool _t2322 = 0;
    (void)_t2322;
    I32_delete(&self->field_offset, &(Bool){_t2322});
    ;
    Bool _t2323 = 0;
    (void)_t2323;
    I32_delete(&self->field_size, &(Bool){_t2323});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Declaration_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Declaration);
    return r;
}

ExprData *ExprData_Body() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Body;
    return r;
}
ExprData *ExprData_LiteralStr(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralStr;
    { Str * _tmp = Str_clone(val); r->data.LiteralStr = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralNum(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralNum;
    { Str * _tmp = Str_clone(val); r->data.LiteralNum = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralBool(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralBool;
    { Str * _tmp = Str_clone(val); r->data.LiteralBool = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_LiteralNull() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_LiteralNull;
    return r;
}
ExprData *ExprData_Ident(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Ident;
    { Str * _tmp = Str_clone(val); r->data.Ident = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Decl(Declaration * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Decl;
    { Declaration * _tmp = Declaration_clone(val); r->data.Decl = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Assign(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Assign;
    { Str * _tmp = Str_clone(val); r->data.Assign = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_FCall() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FCall;
    return r;
}
ExprData *ExprData_FuncDef(FunctionDef * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FuncDef;
    { FunctionDef * _tmp = FunctionDef_clone(val); r->data.FuncDef = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_StructDef() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_StructDef;
    return r;
}
ExprData *ExprData_EnumDef() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_EnumDef;
    return r;
}
ExprData *ExprData_FieldAccess(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FieldAccess;
    { Str * _tmp = Str_clone(val); r->data.FieldAccess = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_FieldAssign(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_FieldAssign;
    { Str * _tmp = Str_clone(val); r->data.FieldAssign = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Return() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Return;
    return r;
}
ExprData *ExprData_If() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_If;
    return r;
}
ExprData *ExprData_While() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_While;
    return r;
}
ExprData *ExprData_ForIn(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_ForIn;
    { Str * _tmp = Str_clone(val); r->data.ForIn = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_NamedArg(Str * val) {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_NamedArg;
    { Str * _tmp = Str_clone(val); r->data.NamedArg = *_tmp; free(_tmp); }
    return r;
}
ExprData *ExprData_Break() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Break;
    return r;
}
ExprData *ExprData_Continue() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Continue;
    return r;
}
ExprData *ExprData_MapLit() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_MapLit;
    return r;
}
ExprData *ExprData_SetLit() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_SetLit;
    return r;
}
ExprData *ExprData_Switch() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Switch;
    return r;
}
ExprData *ExprData_Case() {
    ExprData *r = malloc(sizeof(ExprData));
    r->tag = ExprData_TAG_Case;
    return r;
}
Bool *ExprData_is_Body(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Body);
    return r;
}
Bool *ExprData_is_LiteralStr(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralStr);
    return r;
}
Bool *ExprData_is_LiteralNum(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralNum);
    return r;
}
Bool *ExprData_is_LiteralBool(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralBool);
    return r;
}
Bool *ExprData_is_LiteralNull(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_LiteralNull);
    return r;
}
Bool *ExprData_is_Ident(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Ident);
    return r;
}
Bool *ExprData_is_Decl(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Decl);
    return r;
}
Bool *ExprData_is_Assign(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Assign);
    return r;
}
Bool *ExprData_is_FCall(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FCall);
    return r;
}
Bool *ExprData_is_FuncDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FuncDef);
    return r;
}
Bool *ExprData_is_StructDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_StructDef);
    return r;
}
Bool *ExprData_is_EnumDef(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_EnumDef);
    return r;
}
Bool *ExprData_is_FieldAccess(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FieldAccess);
    return r;
}
Bool *ExprData_is_FieldAssign(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_FieldAssign);
    return r;
}
Bool *ExprData_is_Return(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Return);
    return r;
}
Bool *ExprData_is_If(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_If);
    return r;
}
Bool *ExprData_is_While(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_While);
    return r;
}
Bool *ExprData_is_ForIn(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_ForIn);
    return r;
}
Bool *ExprData_is_NamedArg(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_NamedArg);
    return r;
}
Bool *ExprData_is_Break(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Break);
    return r;
}
Bool *ExprData_is_Continue(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Continue);
    return r;
}
Bool *ExprData_is_MapLit(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_MapLit);
    return r;
}
Bool *ExprData_is_SetLit(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_SetLit);
    return r;
}
Bool *ExprData_is_Switch(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Switch);
    return r;
}
Bool *ExprData_is_Case(ExprData *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == ExprData_TAG_Case);
    return r;
}
Str * ExprData_get_LiteralStr(ExprData *self) {
    return Str_clone(&self->data.LiteralStr);
}
Str * ExprData_get_LiteralNum(ExprData *self) {
    return Str_clone(&self->data.LiteralNum);
}
Str * ExprData_get_LiteralBool(ExprData *self) {
    return Str_clone(&self->data.LiteralBool);
}
Str * ExprData_get_Ident(ExprData *self) {
    return Str_clone(&self->data.Ident);
}
Declaration * ExprData_get_Decl(ExprData *self) {
    return Declaration_clone(&self->data.Decl);
}
Str * ExprData_get_Assign(ExprData *self) {
    return Str_clone(&self->data.Assign);
}
FunctionDef * ExprData_get_FuncDef(ExprData *self) {
    return FunctionDef_clone(&self->data.FuncDef);
}
Str * ExprData_get_FieldAccess(ExprData *self) {
    return Str_clone(&self->data.FieldAccess);
}
Str * ExprData_get_FieldAssign(ExprData *self) {
    return Str_clone(&self->data.FieldAssign);
}
Str * ExprData_get_ForIn(ExprData *self) {
    return Str_clone(&self->data.ForIn);
}
Str * ExprData_get_NamedArg(ExprData *self) {
    return Str_clone(&self->data.NamedArg);
}
Bool * ExprData_eq(ExprData * self, ExprData * other) {
    (void)self;
    (void)other;
    Bool _t2405; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2405 = *_hp; free(_hp); }
    (void)_t2405;
    if (_t2405) {
        Bool _t2325; { Bool *_hp = (Bool *)ExprData_is_Body(other); _t2325 = *_hp; free(_hp); }
        (void)_t2325;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2325; return _r; }
    }
    ;
    Bool _t2406; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2406 = *_hp; free(_hp); }
    (void)_t2406;
    if (_t2406) {
        Bool _t2327; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(other); _t2327 = *_hp; free(_hp); }
        (void)_t2327;
        Bool _t2328 = Bool_not(_t2327);
        (void)_t2328;
        ;
        if (_t2328) {
            Bool _t2326 = 0;
            (void)_t2326;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2326; return _r; }
        }
        ;
        Str *_t2329 = ExprData_get_LiteralStr(self);
        (void)_t2329;
        Str *_t2330 = ExprData_get_LiteralStr(other);
        (void)_t2330;
        Bool _t2331; { Bool *_hp = (Bool *)Str_eq(_t2329, _t2330); _t2331 = *_hp; free(_hp); }
        (void)_t2331;
        Str_delete(_t2329, &(Bool){1});
        Str_delete(_t2330, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2331; return _r; }
    }
    ;
    Bool _t2407; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2407 = *_hp; free(_hp); }
    (void)_t2407;
    if (_t2407) {
        Bool _t2333; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(other); _t2333 = *_hp; free(_hp); }
        (void)_t2333;
        Bool _t2334 = Bool_not(_t2333);
        (void)_t2334;
        ;
        if (_t2334) {
            Bool _t2332 = 0;
            (void)_t2332;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2332; return _r; }
        }
        ;
        Str *_t2335 = ExprData_get_LiteralNum(self);
        (void)_t2335;
        Str *_t2336 = ExprData_get_LiteralNum(other);
        (void)_t2336;
        Bool _t2337; { Bool *_hp = (Bool *)Str_eq(_t2335, _t2336); _t2337 = *_hp; free(_hp); }
        (void)_t2337;
        Str_delete(_t2335, &(Bool){1});
        Str_delete(_t2336, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2337; return _r; }
    }
    ;
    Bool _t2408; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2408 = *_hp; free(_hp); }
    (void)_t2408;
    if (_t2408) {
        Bool _t2339; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(other); _t2339 = *_hp; free(_hp); }
        (void)_t2339;
        Bool _t2340 = Bool_not(_t2339);
        (void)_t2340;
        ;
        if (_t2340) {
            Bool _t2338 = 0;
            (void)_t2338;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2338; return _r; }
        }
        ;
        Str *_t2341 = ExprData_get_LiteralBool(self);
        (void)_t2341;
        Str *_t2342 = ExprData_get_LiteralBool(other);
        (void)_t2342;
        Bool _t2343; { Bool *_hp = (Bool *)Str_eq(_t2341, _t2342); _t2343 = *_hp; free(_hp); }
        (void)_t2343;
        Str_delete(_t2341, &(Bool){1});
        Str_delete(_t2342, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2343; return _r; }
    }
    ;
    Bool _t2409; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2409 = *_hp; free(_hp); }
    (void)_t2409;
    if (_t2409) {
        Bool _t2344; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(other); _t2344 = *_hp; free(_hp); }
        (void)_t2344;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2344; return _r; }
    }
    ;
    Bool _t2410; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2410 = *_hp; free(_hp); }
    (void)_t2410;
    if (_t2410) {
        Bool _t2346; { Bool *_hp = (Bool *)ExprData_is_Ident(other); _t2346 = *_hp; free(_hp); }
        (void)_t2346;
        Bool _t2347 = Bool_not(_t2346);
        (void)_t2347;
        ;
        if (_t2347) {
            Bool _t2345 = 0;
            (void)_t2345;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2345; return _r; }
        }
        ;
        Str *_t2348 = ExprData_get_Ident(self);
        (void)_t2348;
        Str *_t2349 = ExprData_get_Ident(other);
        (void)_t2349;
        Bool _t2350; { Bool *_hp = (Bool *)Str_eq(_t2348, _t2349); _t2350 = *_hp; free(_hp); }
        (void)_t2350;
        Str_delete(_t2348, &(Bool){1});
        Str_delete(_t2349, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2350; return _r; }
    }
    ;
    Bool _t2411; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2411 = *_hp; free(_hp); }
    (void)_t2411;
    if (_t2411) {
        Bool _t2352; { Bool *_hp = (Bool *)ExprData_is_Decl(other); _t2352 = *_hp; free(_hp); }
        (void)_t2352;
        Bool _t2353 = Bool_not(_t2352);
        (void)_t2353;
        ;
        if (_t2353) {
            Bool _t2351 = 0;
            (void)_t2351;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2351; return _r; }
        }
        ;
        Declaration *_t2354 = ExprData_get_Decl(self);
        (void)_t2354;
        Declaration *_t2355 = ExprData_get_Decl(other);
        (void)_t2355;
        Bool _t2356; { Bool *_hp = (Bool *)Declaration_eq(_t2354, _t2355); _t2356 = *_hp; free(_hp); }
        (void)_t2356;
        Declaration_delete(_t2354, &(Bool){1});
        Declaration_delete(_t2355, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2356; return _r; }
    }
    ;
    Bool _t2412; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2412 = *_hp; free(_hp); }
    (void)_t2412;
    if (_t2412) {
        Bool _t2358; { Bool *_hp = (Bool *)ExprData_is_Assign(other); _t2358 = *_hp; free(_hp); }
        (void)_t2358;
        Bool _t2359 = Bool_not(_t2358);
        (void)_t2359;
        ;
        if (_t2359) {
            Bool _t2357 = 0;
            (void)_t2357;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2357; return _r; }
        }
        ;
        Str *_t2360 = ExprData_get_Assign(self);
        (void)_t2360;
        Str *_t2361 = ExprData_get_Assign(other);
        (void)_t2361;
        Bool _t2362; { Bool *_hp = (Bool *)Str_eq(_t2360, _t2361); _t2362 = *_hp; free(_hp); }
        (void)_t2362;
        Str_delete(_t2360, &(Bool){1});
        Str_delete(_t2361, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2362; return _r; }
    }
    ;
    Bool _t2413; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2413 = *_hp; free(_hp); }
    (void)_t2413;
    if (_t2413) {
        Bool _t2363; { Bool *_hp = (Bool *)ExprData_is_FCall(other); _t2363 = *_hp; free(_hp); }
        (void)_t2363;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2363; return _r; }
    }
    ;
    Bool _t2414; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2414 = *_hp; free(_hp); }
    (void)_t2414;
    if (_t2414) {
        Bool _t2365; { Bool *_hp = (Bool *)ExprData_is_FuncDef(other); _t2365 = *_hp; free(_hp); }
        (void)_t2365;
        Bool _t2366 = Bool_not(_t2365);
        (void)_t2366;
        ;
        if (_t2366) {
            Bool _t2364 = 0;
            (void)_t2364;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2364; return _r; }
        }
        ;
        FunctionDef *_t2367 = ExprData_get_FuncDef(self);
        (void)_t2367;
        FunctionDef *_t2368 = ExprData_get_FuncDef(other);
        (void)_t2368;
        Bool _t2369; { Bool *_hp = (Bool *)FunctionDef_eq(_t2367, _t2368); _t2369 = *_hp; free(_hp); }
        (void)_t2369;
        FunctionDef_delete(_t2367, &(Bool){1});
        FunctionDef_delete(_t2368, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2369; return _r; }
    }
    ;
    Bool _t2415; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2415 = *_hp; free(_hp); }
    (void)_t2415;
    if (_t2415) {
        Bool _t2370; { Bool *_hp = (Bool *)ExprData_is_StructDef(other); _t2370 = *_hp; free(_hp); }
        (void)_t2370;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2370; return _r; }
    }
    ;
    Bool _t2416; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2416 = *_hp; free(_hp); }
    (void)_t2416;
    if (_t2416) {
        Bool _t2371; { Bool *_hp = (Bool *)ExprData_is_EnumDef(other); _t2371 = *_hp; free(_hp); }
        (void)_t2371;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2371; return _r; }
    }
    ;
    Bool _t2417; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2417 = *_hp; free(_hp); }
    (void)_t2417;
    if (_t2417) {
        Bool _t2373; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(other); _t2373 = *_hp; free(_hp); }
        (void)_t2373;
        Bool _t2374 = Bool_not(_t2373);
        (void)_t2374;
        ;
        if (_t2374) {
            Bool _t2372 = 0;
            (void)_t2372;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2372; return _r; }
        }
        ;
        Str *_t2375 = ExprData_get_FieldAccess(self);
        (void)_t2375;
        Str *_t2376 = ExprData_get_FieldAccess(other);
        (void)_t2376;
        Bool _t2377; { Bool *_hp = (Bool *)Str_eq(_t2375, _t2376); _t2377 = *_hp; free(_hp); }
        (void)_t2377;
        Str_delete(_t2375, &(Bool){1});
        Str_delete(_t2376, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2377; return _r; }
    }
    ;
    Bool _t2418; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2418 = *_hp; free(_hp); }
    (void)_t2418;
    if (_t2418) {
        Bool _t2379; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(other); _t2379 = *_hp; free(_hp); }
        (void)_t2379;
        Bool _t2380 = Bool_not(_t2379);
        (void)_t2380;
        ;
        if (_t2380) {
            Bool _t2378 = 0;
            (void)_t2378;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2378; return _r; }
        }
        ;
        Str *_t2381 = ExprData_get_FieldAssign(self);
        (void)_t2381;
        Str *_t2382 = ExprData_get_FieldAssign(other);
        (void)_t2382;
        Bool _t2383; { Bool *_hp = (Bool *)Str_eq(_t2381, _t2382); _t2383 = *_hp; free(_hp); }
        (void)_t2383;
        Str_delete(_t2381, &(Bool){1});
        Str_delete(_t2382, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2383; return _r; }
    }
    ;
    Bool _t2419; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2419 = *_hp; free(_hp); }
    (void)_t2419;
    if (_t2419) {
        Bool _t2384; { Bool *_hp = (Bool *)ExprData_is_Return(other); _t2384 = *_hp; free(_hp); }
        (void)_t2384;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2384; return _r; }
    }
    ;
    Bool _t2420; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2420 = *_hp; free(_hp); }
    (void)_t2420;
    if (_t2420) {
        Bool _t2385; { Bool *_hp = (Bool *)ExprData_is_If(other); _t2385 = *_hp; free(_hp); }
        (void)_t2385;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2385; return _r; }
    }
    ;
    Bool _t2421; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2421 = *_hp; free(_hp); }
    (void)_t2421;
    if (_t2421) {
        Bool _t2386; { Bool *_hp = (Bool *)ExprData_is_While(other); _t2386 = *_hp; free(_hp); }
        (void)_t2386;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2386; return _r; }
    }
    ;
    Bool _t2422; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2422 = *_hp; free(_hp); }
    (void)_t2422;
    if (_t2422) {
        Bool _t2388; { Bool *_hp = (Bool *)ExprData_is_ForIn(other); _t2388 = *_hp; free(_hp); }
        (void)_t2388;
        Bool _t2389 = Bool_not(_t2388);
        (void)_t2389;
        ;
        if (_t2389) {
            Bool _t2387 = 0;
            (void)_t2387;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2387; return _r; }
        }
        ;
        Str *_t2390 = ExprData_get_ForIn(self);
        (void)_t2390;
        Str *_t2391 = ExprData_get_ForIn(other);
        (void)_t2391;
        Bool _t2392; { Bool *_hp = (Bool *)Str_eq(_t2390, _t2391); _t2392 = *_hp; free(_hp); }
        (void)_t2392;
        Str_delete(_t2390, &(Bool){1});
        Str_delete(_t2391, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2392; return _r; }
    }
    ;
    Bool _t2423; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2423 = *_hp; free(_hp); }
    (void)_t2423;
    if (_t2423) {
        Bool _t2394; { Bool *_hp = (Bool *)ExprData_is_NamedArg(other); _t2394 = *_hp; free(_hp); }
        (void)_t2394;
        Bool _t2395 = Bool_not(_t2394);
        (void)_t2395;
        ;
        if (_t2395) {
            Bool _t2393 = 0;
            (void)_t2393;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t2393; return _r; }
        }
        ;
        Str *_t2396 = ExprData_get_NamedArg(self);
        (void)_t2396;
        Str *_t2397 = ExprData_get_NamedArg(other);
        (void)_t2397;
        Bool _t2398; { Bool *_hp = (Bool *)Str_eq(_t2396, _t2397); _t2398 = *_hp; free(_hp); }
        (void)_t2398;
        Str_delete(_t2396, &(Bool){1});
        Str_delete(_t2397, &(Bool){1});
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2398; return _r; }
    }
    ;
    Bool _t2424; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2424 = *_hp; free(_hp); }
    (void)_t2424;
    if (_t2424) {
        Bool _t2399; { Bool *_hp = (Bool *)ExprData_is_Break(other); _t2399 = *_hp; free(_hp); }
        (void)_t2399;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2399; return _r; }
    }
    ;
    Bool _t2425; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2425 = *_hp; free(_hp); }
    (void)_t2425;
    if (_t2425) {
        Bool _t2400; { Bool *_hp = (Bool *)ExprData_is_Continue(other); _t2400 = *_hp; free(_hp); }
        (void)_t2400;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2400; return _r; }
    }
    ;
    Bool _t2426; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2426 = *_hp; free(_hp); }
    (void)_t2426;
    if (_t2426) {
        Bool _t2401; { Bool *_hp = (Bool *)ExprData_is_MapLit(other); _t2401 = *_hp; free(_hp); }
        (void)_t2401;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2401; return _r; }
    }
    ;
    Bool _t2427; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2427 = *_hp; free(_hp); }
    (void)_t2427;
    if (_t2427) {
        Bool _t2402; { Bool *_hp = (Bool *)ExprData_is_SetLit(other); _t2402 = *_hp; free(_hp); }
        (void)_t2402;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2402; return _r; }
    }
    ;
    Bool _t2428; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2428 = *_hp; free(_hp); }
    (void)_t2428;
    if (_t2428) {
        Bool _t2403; { Bool *_hp = (Bool *)ExprData_is_Switch(other); _t2403 = *_hp; free(_hp); }
        (void)_t2403;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2403; return _r; }
    }
    ;
    Bool _t2429; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t2429 = *_hp; free(_hp); }
    (void)_t2429;
    if (_t2429) {
        Bool _t2404; { Bool *_hp = (Bool *)ExprData_is_Case(other); _t2404 = *_hp; free(_hp); }
        (void)_t2404;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t2404; return _r; }
    }
    ;
    Bool _t2430 = 0;
    (void)_t2430;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2430; return _r; }
}

ExprData * ExprData_clone(ExprData * self) {
    (void)self;
    Bool _t2453; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2453 = *_hp; free(_hp); }
    (void)_t2453;
    if (_t2453) {
        ;
        return ExprData_Body();
    }
    ;
    Bool _t2454; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2454 = *_hp; free(_hp); }
    (void)_t2454;
    if (_t2454) {
        Str *_t2431 = ExprData_get_LiteralStr(self);
        (void)_t2431;
        ExprData *_t2432 = ExprData_LiteralStr(_t2431);
        (void)_t2432;
        Str_delete(_t2431, &(Bool){1});
        ;
        return _t2432;
    }
    ;
    Bool _t2455; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2455 = *_hp; free(_hp); }
    (void)_t2455;
    if (_t2455) {
        Str *_t2433 = ExprData_get_LiteralNum(self);
        (void)_t2433;
        ExprData *_t2434 = ExprData_LiteralNum(_t2433);
        (void)_t2434;
        Str_delete(_t2433, &(Bool){1});
        ;
        return _t2434;
    }
    ;
    Bool _t2456; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2456 = *_hp; free(_hp); }
    (void)_t2456;
    if (_t2456) {
        Str *_t2435 = ExprData_get_LiteralBool(self);
        (void)_t2435;
        ExprData *_t2436 = ExprData_LiteralBool(_t2435);
        (void)_t2436;
        Str_delete(_t2435, &(Bool){1});
        ;
        return _t2436;
    }
    ;
    Bool _t2457; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2457 = *_hp; free(_hp); }
    (void)_t2457;
    if (_t2457) {
        ;
        return ExprData_LiteralNull();
    }
    ;
    Bool _t2458; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2458 = *_hp; free(_hp); }
    (void)_t2458;
    if (_t2458) {
        Str *_t2437 = ExprData_get_Ident(self);
        (void)_t2437;
        ExprData *_t2438 = ExprData_Ident(_t2437);
        (void)_t2438;
        Str_delete(_t2437, &(Bool){1});
        ;
        return _t2438;
    }
    ;
    Bool _t2459; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2459 = *_hp; free(_hp); }
    (void)_t2459;
    if (_t2459) {
        Declaration *_t2439 = ExprData_get_Decl(self);
        (void)_t2439;
        ExprData *_t2440 = ExprData_Decl(_t2439);
        (void)_t2440;
        Declaration_delete(_t2439, &(Bool){1});
        ;
        return _t2440;
    }
    ;
    Bool _t2460; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2460 = *_hp; free(_hp); }
    (void)_t2460;
    if (_t2460) {
        Str *_t2441 = ExprData_get_Assign(self);
        (void)_t2441;
        ExprData *_t2442 = ExprData_Assign(_t2441);
        (void)_t2442;
        Str_delete(_t2441, &(Bool){1});
        ;
        return _t2442;
    }
    ;
    Bool _t2461; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2461 = *_hp; free(_hp); }
    (void)_t2461;
    if (_t2461) {
        ;
        return ExprData_FCall();
    }
    ;
    Bool _t2462; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2462 = *_hp; free(_hp); }
    (void)_t2462;
    if (_t2462) {
        FunctionDef *_t2443 = ExprData_get_FuncDef(self);
        (void)_t2443;
        ExprData *_t2444 = ExprData_FuncDef(_t2443);
        (void)_t2444;
        FunctionDef_delete(_t2443, &(Bool){1});
        ;
        return _t2444;
    }
    ;
    Bool _t2463; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2463 = *_hp; free(_hp); }
    (void)_t2463;
    if (_t2463) {
        ;
        return ExprData_StructDef();
    }
    ;
    Bool _t2464; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2464 = *_hp; free(_hp); }
    (void)_t2464;
    if (_t2464) {
        ;
        return ExprData_EnumDef();
    }
    ;
    Bool _t2465; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2465 = *_hp; free(_hp); }
    (void)_t2465;
    if (_t2465) {
        Str *_t2445 = ExprData_get_FieldAccess(self);
        (void)_t2445;
        ExprData *_t2446 = ExprData_FieldAccess(_t2445);
        (void)_t2446;
        Str_delete(_t2445, &(Bool){1});
        ;
        return _t2446;
    }
    ;
    Bool _t2466; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2466 = *_hp; free(_hp); }
    (void)_t2466;
    if (_t2466) {
        Str *_t2447 = ExprData_get_FieldAssign(self);
        (void)_t2447;
        ExprData *_t2448 = ExprData_FieldAssign(_t2447);
        (void)_t2448;
        Str_delete(_t2447, &(Bool){1});
        ;
        return _t2448;
    }
    ;
    Bool _t2467; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2467 = *_hp; free(_hp); }
    (void)_t2467;
    if (_t2467) {
        ;
        return ExprData_Return();
    }
    ;
    Bool _t2468; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2468 = *_hp; free(_hp); }
    (void)_t2468;
    if (_t2468) {
        ;
        return ExprData_If();
    }
    ;
    Bool _t2469; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2469 = *_hp; free(_hp); }
    (void)_t2469;
    if (_t2469) {
        ;
        return ExprData_While();
    }
    ;
    Bool _t2470; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2470 = *_hp; free(_hp); }
    (void)_t2470;
    if (_t2470) {
        Str *_t2449 = ExprData_get_ForIn(self);
        (void)_t2449;
        ExprData *_t2450 = ExprData_ForIn(_t2449);
        (void)_t2450;
        Str_delete(_t2449, &(Bool){1});
        ;
        return _t2450;
    }
    ;
    Bool _t2471; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2471 = *_hp; free(_hp); }
    (void)_t2471;
    if (_t2471) {
        Str *_t2451 = ExprData_get_NamedArg(self);
        (void)_t2451;
        ExprData *_t2452 = ExprData_NamedArg(_t2451);
        (void)_t2452;
        Str_delete(_t2451, &(Bool){1});
        ;
        return _t2452;
    }
    ;
    Bool _t2472; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2472 = *_hp; free(_hp); }
    (void)_t2472;
    if (_t2472) {
        ;
        return ExprData_Break();
    }
    ;
    Bool _t2473; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2473 = *_hp; free(_hp); }
    (void)_t2473;
    if (_t2473) {
        ;
        return ExprData_Continue();
    }
    ;
    Bool _t2474; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2474 = *_hp; free(_hp); }
    (void)_t2474;
    if (_t2474) {
        ;
        return ExprData_MapLit();
    }
    ;
    Bool _t2475; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2475 = *_hp; free(_hp); }
    (void)_t2475;
    if (_t2475) {
        ;
        return ExprData_SetLit();
    }
    ;
    Bool _t2476; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2476 = *_hp; free(_hp); }
    (void)_t2476;
    if (_t2476) {
        ;
        return ExprData_Switch();
    }
    ;
    return ExprData_Case();
}

void ExprData_delete(ExprData * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * ExprData_to_str(ExprData * self) {
    (void)self;
    Bool _t2612; { Bool *_hp = (Bool *)ExprData_is_Body(self); _t2612 = *_hp; free(_hp); }
    (void)_t2612;
    if (_t2612) {
        Str *_t2477 = Str_lit("Body", 4ULL);
        (void)_t2477;
        ;
        return _t2477;
    }
    ;
    Bool _t2613; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(self); _t2613 = *_hp; free(_hp); }
    (void)_t2613;
    if (_t2613) {
        Str *_t2478 = Str_lit("Str", 3ULL);
        (void)_t2478;
        U64 _t2479; { U64 *_hp = (U64 *)Str_size(); _t2479 = *_hp; free(_hp); }
        (void)_t2479;
        U64 _t2480 = 3;
        (void)_t2480;
        Array *_va24 = Array_new(_t2478, &(U64){_t2479}, &(U64){_t2480});
        (void)_va24;
        Str_delete(_t2478, &(Bool){1});
        ;
        ;
        U64 _t2481 = 0;
        (void)_t2481;
        Str *_t2482 = Str_lit("LiteralStr(", 11ULL);
        (void)_t2482;
        Array_set(_va24, &(U64){_t2481}, _t2482);
        ;
        Str *_t2483 = ExprData_get_LiteralStr(self);
        (void)_t2483;
        U64 _t2484 = 1;
        (void)_t2484;
        Str *_t2485 = Str_to_str(_t2483);
        (void)_t2485;
        Str_delete(_t2483, &(Bool){1});
        Array_set(_va24, &(U64){_t2484}, _t2485);
        ;
        U64 _t2486 = 2;
        (void)_t2486;
        Str *_t2487 = Str_lit(")", 1ULL);
        (void)_t2487;
        Array_set(_va24, &(U64){_t2486}, _t2487);
        ;
        Str *_t2488 = format(_va24);
        (void)_t2488;
        ;
        return _t2488;
    }
    ;
    Bool _t2614; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(self); _t2614 = *_hp; free(_hp); }
    (void)_t2614;
    if (_t2614) {
        Str *_t2489 = Str_lit("Str", 3ULL);
        (void)_t2489;
        U64 _t2490; { U64 *_hp = (U64 *)Str_size(); _t2490 = *_hp; free(_hp); }
        (void)_t2490;
        U64 _t2491 = 3;
        (void)_t2491;
        Array *_va25 = Array_new(_t2489, &(U64){_t2490}, &(U64){_t2491});
        (void)_va25;
        Str_delete(_t2489, &(Bool){1});
        ;
        ;
        U64 _t2492 = 0;
        (void)_t2492;
        Str *_t2493 = Str_lit("LiteralNum(", 11ULL);
        (void)_t2493;
        Array_set(_va25, &(U64){_t2492}, _t2493);
        ;
        Str *_t2494 = ExprData_get_LiteralNum(self);
        (void)_t2494;
        U64 _t2495 = 1;
        (void)_t2495;
        Str *_t2496 = Str_to_str(_t2494);
        (void)_t2496;
        Str_delete(_t2494, &(Bool){1});
        Array_set(_va25, &(U64){_t2495}, _t2496);
        ;
        U64 _t2497 = 2;
        (void)_t2497;
        Str *_t2498 = Str_lit(")", 1ULL);
        (void)_t2498;
        Array_set(_va25, &(U64){_t2497}, _t2498);
        ;
        Str *_t2499 = format(_va25);
        (void)_t2499;
        ;
        return _t2499;
    }
    ;
    Bool _t2615; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(self); _t2615 = *_hp; free(_hp); }
    (void)_t2615;
    if (_t2615) {
        Str *_t2500 = Str_lit("Str", 3ULL);
        (void)_t2500;
        U64 _t2501; { U64 *_hp = (U64 *)Str_size(); _t2501 = *_hp; free(_hp); }
        (void)_t2501;
        U64 _t2502 = 3;
        (void)_t2502;
        Array *_va26 = Array_new(_t2500, &(U64){_t2501}, &(U64){_t2502});
        (void)_va26;
        Str_delete(_t2500, &(Bool){1});
        ;
        ;
        U64 _t2503 = 0;
        (void)_t2503;
        Str *_t2504 = Str_lit("LiteralBool(", 12ULL);
        (void)_t2504;
        Array_set(_va26, &(U64){_t2503}, _t2504);
        ;
        Str *_t2505 = ExprData_get_LiteralBool(self);
        (void)_t2505;
        U64 _t2506 = 1;
        (void)_t2506;
        Str *_t2507 = Str_to_str(_t2505);
        (void)_t2507;
        Str_delete(_t2505, &(Bool){1});
        Array_set(_va26, &(U64){_t2506}, _t2507);
        ;
        U64 _t2508 = 2;
        (void)_t2508;
        Str *_t2509 = Str_lit(")", 1ULL);
        (void)_t2509;
        Array_set(_va26, &(U64){_t2508}, _t2509);
        ;
        Str *_t2510 = format(_va26);
        (void)_t2510;
        ;
        return _t2510;
    }
    ;
    Bool _t2616; { Bool *_hp = (Bool *)ExprData_is_LiteralNull(self); _t2616 = *_hp; free(_hp); }
    (void)_t2616;
    if (_t2616) {
        Str *_t2511 = Str_lit("LiteralNull", 11ULL);
        (void)_t2511;
        ;
        return _t2511;
    }
    ;
    Bool _t2617; { Bool *_hp = (Bool *)ExprData_is_Ident(self); _t2617 = *_hp; free(_hp); }
    (void)_t2617;
    if (_t2617) {
        Str *_t2512 = Str_lit("Str", 3ULL);
        (void)_t2512;
        U64 _t2513; { U64 *_hp = (U64 *)Str_size(); _t2513 = *_hp; free(_hp); }
        (void)_t2513;
        U64 _t2514 = 3;
        (void)_t2514;
        Array *_va27 = Array_new(_t2512, &(U64){_t2513}, &(U64){_t2514});
        (void)_va27;
        Str_delete(_t2512, &(Bool){1});
        ;
        ;
        U64 _t2515 = 0;
        (void)_t2515;
        Str *_t2516 = Str_lit("Ident(", 6ULL);
        (void)_t2516;
        Array_set(_va27, &(U64){_t2515}, _t2516);
        ;
        Str *_t2517 = ExprData_get_Ident(self);
        (void)_t2517;
        U64 _t2518 = 1;
        (void)_t2518;
        Str *_t2519 = Str_to_str(_t2517);
        (void)_t2519;
        Str_delete(_t2517, &(Bool){1});
        Array_set(_va27, &(U64){_t2518}, _t2519);
        ;
        U64 _t2520 = 2;
        (void)_t2520;
        Str *_t2521 = Str_lit(")", 1ULL);
        (void)_t2521;
        Array_set(_va27, &(U64){_t2520}, _t2521);
        ;
        Str *_t2522 = format(_va27);
        (void)_t2522;
        ;
        return _t2522;
    }
    ;
    Bool _t2618; { Bool *_hp = (Bool *)ExprData_is_Decl(self); _t2618 = *_hp; free(_hp); }
    (void)_t2618;
    if (_t2618) {
        Str *_t2523 = Str_lit("Str", 3ULL);
        (void)_t2523;
        U64 _t2524; { U64 *_hp = (U64 *)Str_size(); _t2524 = *_hp; free(_hp); }
        (void)_t2524;
        U64 _t2525 = 3;
        (void)_t2525;
        Array *_va28 = Array_new(_t2523, &(U64){_t2524}, &(U64){_t2525});
        (void)_va28;
        Str_delete(_t2523, &(Bool){1});
        ;
        ;
        U64 _t2526 = 0;
        (void)_t2526;
        Str *_t2527 = Str_lit("Decl(", 5ULL);
        (void)_t2527;
        Array_set(_va28, &(U64){_t2526}, _t2527);
        ;
        Declaration *_t2528 = ExprData_get_Decl(self);
        (void)_t2528;
        U64 _t2529 = 1;
        (void)_t2529;
        Str *_t2530 = Declaration_to_str(_t2528);
        (void)_t2530;
        Declaration_delete(_t2528, &(Bool){1});
        Array_set(_va28, &(U64){_t2529}, _t2530);
        ;
        U64 _t2531 = 2;
        (void)_t2531;
        Str *_t2532 = Str_lit(")", 1ULL);
        (void)_t2532;
        Array_set(_va28, &(U64){_t2531}, _t2532);
        ;
        Str *_t2533 = format(_va28);
        (void)_t2533;
        ;
        return _t2533;
    }
    ;
    Bool _t2619; { Bool *_hp = (Bool *)ExprData_is_Assign(self); _t2619 = *_hp; free(_hp); }
    (void)_t2619;
    if (_t2619) {
        Str *_t2534 = Str_lit("Str", 3ULL);
        (void)_t2534;
        U64 _t2535; { U64 *_hp = (U64 *)Str_size(); _t2535 = *_hp; free(_hp); }
        (void)_t2535;
        U64 _t2536 = 3;
        (void)_t2536;
        Array *_va29 = Array_new(_t2534, &(U64){_t2535}, &(U64){_t2536});
        (void)_va29;
        Str_delete(_t2534, &(Bool){1});
        ;
        ;
        U64 _t2537 = 0;
        (void)_t2537;
        Str *_t2538 = Str_lit("Assign(", 7ULL);
        (void)_t2538;
        Array_set(_va29, &(U64){_t2537}, _t2538);
        ;
        Str *_t2539 = ExprData_get_Assign(self);
        (void)_t2539;
        U64 _t2540 = 1;
        (void)_t2540;
        Str *_t2541 = Str_to_str(_t2539);
        (void)_t2541;
        Str_delete(_t2539, &(Bool){1});
        Array_set(_va29, &(U64){_t2540}, _t2541);
        ;
        U64 _t2542 = 2;
        (void)_t2542;
        Str *_t2543 = Str_lit(")", 1ULL);
        (void)_t2543;
        Array_set(_va29, &(U64){_t2542}, _t2543);
        ;
        Str *_t2544 = format(_va29);
        (void)_t2544;
        ;
        return _t2544;
    }
    ;
    Bool _t2620; { Bool *_hp = (Bool *)ExprData_is_FCall(self); _t2620 = *_hp; free(_hp); }
    (void)_t2620;
    if (_t2620) {
        Str *_t2545 = Str_lit("FCall", 5ULL);
        (void)_t2545;
        ;
        return _t2545;
    }
    ;
    Bool _t2621; { Bool *_hp = (Bool *)ExprData_is_FuncDef(self); _t2621 = *_hp; free(_hp); }
    (void)_t2621;
    if (_t2621) {
        Str *_t2546 = Str_lit("Str", 3ULL);
        (void)_t2546;
        U64 _t2547; { U64 *_hp = (U64 *)Str_size(); _t2547 = *_hp; free(_hp); }
        (void)_t2547;
        U64 _t2548 = 3;
        (void)_t2548;
        Array *_va30 = Array_new(_t2546, &(U64){_t2547}, &(U64){_t2548});
        (void)_va30;
        Str_delete(_t2546, &(Bool){1});
        ;
        ;
        U64 _t2549 = 0;
        (void)_t2549;
        Str *_t2550 = Str_lit("FuncDef(", 8ULL);
        (void)_t2550;
        Array_set(_va30, &(U64){_t2549}, _t2550);
        ;
        FunctionDef *_t2551 = ExprData_get_FuncDef(self);
        (void)_t2551;
        U64 _t2552 = 1;
        (void)_t2552;
        Str *_t2553 = FunctionDef_to_str(_t2551);
        (void)_t2553;
        FunctionDef_delete(_t2551, &(Bool){1});
        Array_set(_va30, &(U64){_t2552}, _t2553);
        ;
        U64 _t2554 = 2;
        (void)_t2554;
        Str *_t2555 = Str_lit(")", 1ULL);
        (void)_t2555;
        Array_set(_va30, &(U64){_t2554}, _t2555);
        ;
        Str *_t2556 = format(_va30);
        (void)_t2556;
        ;
        return _t2556;
    }
    ;
    Bool _t2622; { Bool *_hp = (Bool *)ExprData_is_StructDef(self); _t2622 = *_hp; free(_hp); }
    (void)_t2622;
    if (_t2622) {
        Str *_t2557 = Str_lit("StructDef", 9ULL);
        (void)_t2557;
        ;
        return _t2557;
    }
    ;
    Bool _t2623; { Bool *_hp = (Bool *)ExprData_is_EnumDef(self); _t2623 = *_hp; free(_hp); }
    (void)_t2623;
    if (_t2623) {
        Str *_t2558 = Str_lit("EnumDef", 7ULL);
        (void)_t2558;
        ;
        return _t2558;
    }
    ;
    Bool _t2624; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(self); _t2624 = *_hp; free(_hp); }
    (void)_t2624;
    if (_t2624) {
        Str *_t2559 = Str_lit("Str", 3ULL);
        (void)_t2559;
        U64 _t2560; { U64 *_hp = (U64 *)Str_size(); _t2560 = *_hp; free(_hp); }
        (void)_t2560;
        U64 _t2561 = 3;
        (void)_t2561;
        Array *_va31 = Array_new(_t2559, &(U64){_t2560}, &(U64){_t2561});
        (void)_va31;
        Str_delete(_t2559, &(Bool){1});
        ;
        ;
        U64 _t2562 = 0;
        (void)_t2562;
        Str *_t2563 = Str_lit("FieldAccess(", 12ULL);
        (void)_t2563;
        Array_set(_va31, &(U64){_t2562}, _t2563);
        ;
        Str *_t2564 = ExprData_get_FieldAccess(self);
        (void)_t2564;
        U64 _t2565 = 1;
        (void)_t2565;
        Str *_t2566 = Str_to_str(_t2564);
        (void)_t2566;
        Str_delete(_t2564, &(Bool){1});
        Array_set(_va31, &(U64){_t2565}, _t2566);
        ;
        U64 _t2567 = 2;
        (void)_t2567;
        Str *_t2568 = Str_lit(")", 1ULL);
        (void)_t2568;
        Array_set(_va31, &(U64){_t2567}, _t2568);
        ;
        Str *_t2569 = format(_va31);
        (void)_t2569;
        ;
        return _t2569;
    }
    ;
    Bool _t2625; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(self); _t2625 = *_hp; free(_hp); }
    (void)_t2625;
    if (_t2625) {
        Str *_t2570 = Str_lit("Str", 3ULL);
        (void)_t2570;
        U64 _t2571; { U64 *_hp = (U64 *)Str_size(); _t2571 = *_hp; free(_hp); }
        (void)_t2571;
        U64 _t2572 = 3;
        (void)_t2572;
        Array *_va32 = Array_new(_t2570, &(U64){_t2571}, &(U64){_t2572});
        (void)_va32;
        Str_delete(_t2570, &(Bool){1});
        ;
        ;
        U64 _t2573 = 0;
        (void)_t2573;
        Str *_t2574 = Str_lit("FieldAssign(", 12ULL);
        (void)_t2574;
        Array_set(_va32, &(U64){_t2573}, _t2574);
        ;
        Str *_t2575 = ExprData_get_FieldAssign(self);
        (void)_t2575;
        U64 _t2576 = 1;
        (void)_t2576;
        Str *_t2577 = Str_to_str(_t2575);
        (void)_t2577;
        Str_delete(_t2575, &(Bool){1});
        Array_set(_va32, &(U64){_t2576}, _t2577);
        ;
        U64 _t2578 = 2;
        (void)_t2578;
        Str *_t2579 = Str_lit(")", 1ULL);
        (void)_t2579;
        Array_set(_va32, &(U64){_t2578}, _t2579);
        ;
        Str *_t2580 = format(_va32);
        (void)_t2580;
        ;
        return _t2580;
    }
    ;
    Bool _t2626; { Bool *_hp = (Bool *)ExprData_is_Return(self); _t2626 = *_hp; free(_hp); }
    (void)_t2626;
    if (_t2626) {
        Str *_t2581 = Str_lit("Return", 6ULL);
        (void)_t2581;
        ;
        return _t2581;
    }
    ;
    Bool _t2627; { Bool *_hp = (Bool *)ExprData_is_If(self); _t2627 = *_hp; free(_hp); }
    (void)_t2627;
    if (_t2627) {
        Str *_t2582 = Str_lit("If", 2ULL);
        (void)_t2582;
        ;
        return _t2582;
    }
    ;
    Bool _t2628; { Bool *_hp = (Bool *)ExprData_is_While(self); _t2628 = *_hp; free(_hp); }
    (void)_t2628;
    if (_t2628) {
        Str *_t2583 = Str_lit("While", 5ULL);
        (void)_t2583;
        ;
        return _t2583;
    }
    ;
    Bool _t2629; { Bool *_hp = (Bool *)ExprData_is_ForIn(self); _t2629 = *_hp; free(_hp); }
    (void)_t2629;
    if (_t2629) {
        Str *_t2584 = Str_lit("Str", 3ULL);
        (void)_t2584;
        U64 _t2585; { U64 *_hp = (U64 *)Str_size(); _t2585 = *_hp; free(_hp); }
        (void)_t2585;
        U64 _t2586 = 3;
        (void)_t2586;
        Array *_va33 = Array_new(_t2584, &(U64){_t2585}, &(U64){_t2586});
        (void)_va33;
        Str_delete(_t2584, &(Bool){1});
        ;
        ;
        U64 _t2587 = 0;
        (void)_t2587;
        Str *_t2588 = Str_lit("ForIn(", 6ULL);
        (void)_t2588;
        Array_set(_va33, &(U64){_t2587}, _t2588);
        ;
        Str *_t2589 = ExprData_get_ForIn(self);
        (void)_t2589;
        U64 _t2590 = 1;
        (void)_t2590;
        Str *_t2591 = Str_to_str(_t2589);
        (void)_t2591;
        Str_delete(_t2589, &(Bool){1});
        Array_set(_va33, &(U64){_t2590}, _t2591);
        ;
        U64 _t2592 = 2;
        (void)_t2592;
        Str *_t2593 = Str_lit(")", 1ULL);
        (void)_t2593;
        Array_set(_va33, &(U64){_t2592}, _t2593);
        ;
        Str *_t2594 = format(_va33);
        (void)_t2594;
        ;
        return _t2594;
    }
    ;
    Bool _t2630; { Bool *_hp = (Bool *)ExprData_is_NamedArg(self); _t2630 = *_hp; free(_hp); }
    (void)_t2630;
    if (_t2630) {
        Str *_t2595 = Str_lit("Str", 3ULL);
        (void)_t2595;
        U64 _t2596; { U64 *_hp = (U64 *)Str_size(); _t2596 = *_hp; free(_hp); }
        (void)_t2596;
        U64 _t2597 = 3;
        (void)_t2597;
        Array *_va34 = Array_new(_t2595, &(U64){_t2596}, &(U64){_t2597});
        (void)_va34;
        Str_delete(_t2595, &(Bool){1});
        ;
        ;
        U64 _t2598 = 0;
        (void)_t2598;
        Str *_t2599 = Str_lit("NamedArg(", 9ULL);
        (void)_t2599;
        Array_set(_va34, &(U64){_t2598}, _t2599);
        ;
        Str *_t2600 = ExprData_get_NamedArg(self);
        (void)_t2600;
        U64 _t2601 = 1;
        (void)_t2601;
        Str *_t2602 = Str_to_str(_t2600);
        (void)_t2602;
        Str_delete(_t2600, &(Bool){1});
        Array_set(_va34, &(U64){_t2601}, _t2602);
        ;
        U64 _t2603 = 2;
        (void)_t2603;
        Str *_t2604 = Str_lit(")", 1ULL);
        (void)_t2604;
        Array_set(_va34, &(U64){_t2603}, _t2604);
        ;
        Str *_t2605 = format(_va34);
        (void)_t2605;
        ;
        return _t2605;
    }
    ;
    Bool _t2631; { Bool *_hp = (Bool *)ExprData_is_Break(self); _t2631 = *_hp; free(_hp); }
    (void)_t2631;
    if (_t2631) {
        Str *_t2606 = Str_lit("Break", 5ULL);
        (void)_t2606;
        ;
        return _t2606;
    }
    ;
    Bool _t2632; { Bool *_hp = (Bool *)ExprData_is_Continue(self); _t2632 = *_hp; free(_hp); }
    (void)_t2632;
    if (_t2632) {
        Str *_t2607 = Str_lit("Continue", 8ULL);
        (void)_t2607;
        ;
        return _t2607;
    }
    ;
    Bool _t2633; { Bool *_hp = (Bool *)ExprData_is_MapLit(self); _t2633 = *_hp; free(_hp); }
    (void)_t2633;
    if (_t2633) {
        Str *_t2608 = Str_lit("MapLit", 6ULL);
        (void)_t2608;
        ;
        return _t2608;
    }
    ;
    Bool _t2634; { Bool *_hp = (Bool *)ExprData_is_SetLit(self); _t2634 = *_hp; free(_hp); }
    (void)_t2634;
    if (_t2634) {
        Str *_t2609 = Str_lit("SetLit", 6ULL);
        (void)_t2609;
        ;
        return _t2609;
    }
    ;
    Bool _t2635; { Bool *_hp = (Bool *)ExprData_is_Switch(self); _t2635 = *_hp; free(_hp); }
    (void)_t2635;
    if (_t2635) {
        Str *_t2610 = Str_lit("Switch", 6ULL);
        (void)_t2610;
        ;
        return _t2610;
    }
    ;
    Bool _t2636; { Bool *_hp = (Bool *)ExprData_is_Case(self); _t2636 = *_hp; free(_hp); }
    (void)_t2636;
    if (_t2636) {
        Str *_t2611 = Str_lit("Case", 4ULL);
        (void)_t2611;
        ;
        return _t2611;
    }
    ;
    Str *_t2637 = Str_lit("unknown", 7ULL);
    (void)_t2637;
    return _t2637;
}

U64 *ExprData_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(ExprData);
    return r;
}


void Expr_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Str *_t2639 = Str_lit("Str", 3ULL);
    (void)_t2639;
    U64 _t2640; { U64 *_hp = (U64 *)Str_size(); _t2640 = *_hp; free(_hp); }
    (void)_t2640;
    U64 _t2641 = 7;
    (void)_t2641;
    Array *_va35 = Array_new(_t2639, &(U64){_t2640}, &(U64){_t2641});
    (void)_va35;
    Str_delete(_t2639, &(Bool){1});
    ;
    ;
    U64 _t2642 = 0;
    (void)_t2642;
    Str *_t2643 = Str_clone(&self->path);
    (void)_t2643;
    Array_set(_va35, &(U64){_t2642}, _t2643);
    ;
    U64 _t2644 = 1;
    (void)_t2644;
    Str *_t2645 = Str_lit(":", 1ULL);
    (void)_t2645;
    Array_set(_va35, &(U64){_t2644}, _t2645);
    ;
    U64 _t2646 = 2;
    (void)_t2646;
    Str *_t2647 = U32_to_str(&self->line);
    (void)_t2647;
    Array_set(_va35, &(U64){_t2646}, _t2647);
    ;
    U64 _t2648 = 3;
    (void)_t2648;
    Str *_t2649 = Str_lit(":", 1ULL);
    (void)_t2649;
    Array_set(_va35, &(U64){_t2648}, _t2649);
    ;
    U64 _t2650 = 4;
    (void)_t2650;
    Str *_t2651 = U32_to_str(&self->col);
    (void)_t2651;
    Array_set(_va35, &(U64){_t2650}, _t2651);
    ;
    U64 _t2652 = 5;
    (void)_t2652;
    Str *_t2653 = Str_lit(": error: ", 9ULL);
    (void)_t2653;
    Array_set(_va35, &(U64){_t2652}, _t2653);
    ;
    U64 _t2654 = 6;
    (void)_t2654;
    Str *_t2655 = Str_clone(msg);
    (void)_t2655;
    Array_set(_va35, &(U64){_t2654}, _t2655);
    ;
    println(_va35);
}

void Expr_todo_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2656 = Str_lit("Str", 3ULL);
    (void)_t2656;
    U64 _t2657; { U64 *_hp = (U64 *)Str_size(); _t2657 = *_hp; free(_hp); }
    (void)_t2657;
    U64 _t2658 = 1;
    (void)_t2658;
    Array *_va36 = Array_new(_t2656, &(U64){_t2657}, &(U64){_t2658});
    (void)_va36;
    Str_delete(_t2656, &(Bool){1});
    ;
    ;
    U64 _t2659 = 0;
    (void)_t2659;
    Str *_t2660 = Str_lit("  note: this language feature is not implemented yet", 52ULL);
    (void)_t2660;
    Array_set(_va36, &(U64){_t2659}, _t2660);
    ;
    println(_va36);
}

void Expr_lang_error(Expr * self, Str * msg) {
    (void)self;
    (void)msg;
    Expr_error(self, msg);
    Str *_t2661 = Str_lit("Str", 3ULL);
    (void)_t2661;
    U64 _t2662; { U64 *_hp = (U64 *)Str_size(); _t2662 = *_hp; free(_hp); }
    (void)_t2662;
    U64 _t2663 = 1;
    (void)_t2663;
    Array *_va37 = Array_new(_t2661, &(U64){_t2662}, &(U64){_t2663});
    (void)_va37;
    Str_delete(_t2661, &(Bool){1});
    ;
    ;
    U64 _t2664 = 0;
    (void)_t2664;
    Str *_t2665 = Str_lit("  note: this is a bug in the language, please report it", 55ULL);
    (void)_t2665;
    Array_set(_va37, &(U64){_t2664}, _t2665);
    ;
    println(_va37);
}

void Expr_add_child(Expr * self, Expr * child) {
    (void)self;
    (void)child;
    Vec_push(&self->children, child);
}

Expr * Expr_child(Expr * parent, I64 * i) {
    (void)parent;
    (void)i;
    U64 *_t2666 = malloc(sizeof(U64)); *_t2666 = I64_to_u64(DEREF(i));
    (void)_t2666;
    Expr *c = Vec_get(&parent->children, _t2666);
    (void)c;
    U64_delete(_t2666, &(Bool){1});
    return c;
}

I64 * Expr_child_count(Expr * parent) {
    (void)parent;
    U64 _t2667; { U64 *_hp = (U64 *)Vec_len(&parent->children); _t2667 = *_hp; free(_hp); }
    (void)_t2667;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t2667; return _r; }
}

Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path) {
    (void)data;
    (void)line;
    (void)col;
    (void)path;
    I64 _t2668 = 0;
    (void)_t2668;
    I64 _t2669 = 1;
    (void)_t2669;
    I64 _t2670 = I64_sub(_t2668, _t2669);
    (void)_t2670;
    ;
    ;
    I64 _t2671 = 0;
    (void)_t2671;
    I64 _t2672 = 1;
    (void)_t2672;
    I64 _t2673 = I64_sub(_t2671, _t2672);
    (void)_t2673;
    ;
    ;
    Str *_t2674 = Str_lit("Expr", 4ULL);
    (void)_t2674;
    U64 _t2675; { U64 *_hp = (U64 *)Expr_size(); _t2675 = *_hp; free(_hp); }
    (void)_t2675;
    Bool _t2676 = 0;
    (void)_t2676;
    Bool _t2677 = 0;
    (void)_t2677;
    Bool _t2678 = 0;
    (void)_t2678;
    Bool _t2679 = 0;
    (void)_t2679;
    Bool _t2680 = 0;
    (void)_t2680;
    Bool _t2681 = 0;
    (void)_t2681;
    Bool _t2682 = 0;
    (void)_t2682;
    Bool _t2683 = 0;
    (void)_t2683;
    I32 _t2684 = 0;
    (void)_t2684;
    I32 _t2685 = I64_to_i32(_t2670);
    (void)_t2685;
    ;
    U32 _t2686 = 0;
    (void)_t2686;
    I32 _t2687 = I64_to_i32(_t2673);
    (void)_t2687;
    ;
    U32 _t2688 = 0;
    (void)_t2688;
    U32 _t2689 = U32_clone(&(U32){col});
    (void)_t2689;
    Str *_t2690 = Str_clone(path);
    (void)_t2690;
    Expr *_t2691 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(data); _t2691->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(TilType_Unknown()); _t2691->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2691->struct_name = *_ca; free(_ca); }
    _t2691->is_own_arg = _t2676;
    _t2691->is_splat = _t2677;
    _t2691->is_own_field = _t2678;
    _t2691->is_ref_field = _t2679;
    _t2691->is_ns_field = _t2680;
    _t2691->is_ext = _t2681;
    _t2691->is_core = _t2682;
    _t2691->save_old_delete = _t2683;
    _t2691->total_struct_size = _t2684;
    _t2691->variadic_index = _t2685;
    _t2691->variadic_count = _t2686;
    _t2691->kwargs_index = _t2687;
    _t2691->kwargs_count = _t2688;
    _t2691->fn_sig = NULL;
    { Vec *_ca = Vec_new(_t2674, &(U64){_t2675}); _t2691->children = *_ca; free(_ca); }
    _t2691->line = U32_clone(&(U32){line});
    _t2691->col = _t2689;
    { Str *_ca = Str_clone(_t2690); _t2691->path = *_ca; free(_ca); }
    (void)_t2691;
    Str_delete(_t2674, &(Bool){1});
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2690, &(Bool){1});
    return _t2691;
}

Expr * Expr_clone(Expr * self) {
    (void)self;
    Bool _t2692 = Bool_clone(&self->is_own_arg);
    (void)_t2692;
    Bool _t2693 = Bool_clone(&self->is_splat);
    (void)_t2693;
    Bool _t2694 = Bool_clone(&self->is_own_field);
    (void)_t2694;
    Bool _t2695 = Bool_clone(&self->is_ref_field);
    (void)_t2695;
    Bool _t2696 = Bool_clone(&self->is_ns_field);
    (void)_t2696;
    Bool _t2697 = Bool_clone(&self->is_ext);
    (void)_t2697;
    Bool _t2698 = Bool_clone(&self->is_core);
    (void)_t2698;
    Bool _t2699 = Bool_clone(&self->save_old_delete);
    (void)_t2699;
    I32 _t2700 = I32_clone(&self->total_struct_size);
    (void)_t2700;
    I32 _t2701 = I32_clone(&self->variadic_index);
    (void)_t2701;
    U32 _t2702 = U32_clone(&self->variadic_count);
    (void)_t2702;
    I32 _t2703 = I32_clone(&self->kwargs_index);
    (void)_t2703;
    U32 _t2704 = U32_clone(&self->kwargs_count);
    (void)_t2704;
    U32 _t2705 = U32_clone(&self->col);
    (void)_t2705;
    Str *_t2706 = Str_clone(&self->path);
    (void)_t2706;
    Expr *_t2707 = malloc(sizeof(Expr));
    { ExprData *_ca = ExprData_clone(&self->data); _t2707->data = *_ca; free(_ca); }
    { TilType *_ca = TilType_clone(&self->til_type); _t2707->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->struct_name); _t2707->struct_name = *_ca; free(_ca); }
    _t2707->is_own_arg = _t2692;
    _t2707->is_splat = _t2693;
    _t2707->is_own_field = _t2694;
    _t2707->is_ref_field = _t2695;
    _t2707->is_ns_field = _t2696;
    _t2707->is_ext = _t2697;
    _t2707->is_core = _t2698;
    _t2707->save_old_delete = _t2699;
    _t2707->total_struct_size = _t2700;
    _t2707->variadic_index = _t2701;
    _t2707->variadic_count = _t2702;
    _t2707->kwargs_index = _t2703;
    _t2707->kwargs_count = _t2704;
    _t2707->fn_sig = self->fn_sig;
    { Vec *_ca = Vec_clone(&self->children); _t2707->children = *_ca; free(_ca); }
    _t2707->line = U32_clone(&self->line);
    _t2707->col = _t2705;
    { Str *_ca = Str_clone(_t2706); _t2707->path = *_ca; free(_ca); }
    (void)_t2707;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    Str_delete(_t2706, &(Bool){1});
    return _t2707;
}

void Expr_delete(Expr * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t2708 = 0;
    (void)_t2708;
    ExprData_delete(&self->data, &(Bool){_t2708});
    ;
    Bool _t2709 = 0;
    (void)_t2709;
    TilType_delete(&self->til_type, &(Bool){_t2709});
    ;
    Bool _t2710 = 0;
    (void)_t2710;
    Str_delete(&self->struct_name, &(Bool){_t2710});
    ;
    Bool _t2711 = 0;
    (void)_t2711;
    Bool_delete(&self->is_own_arg, &(Bool){_t2711});
    ;
    Bool _t2712 = 0;
    (void)_t2712;
    Bool_delete(&self->is_splat, &(Bool){_t2712});
    ;
    Bool _t2713 = 0;
    (void)_t2713;
    Bool_delete(&self->is_own_field, &(Bool){_t2713});
    ;
    Bool _t2714 = 0;
    (void)_t2714;
    Bool_delete(&self->is_ref_field, &(Bool){_t2714});
    ;
    Bool _t2715 = 0;
    (void)_t2715;
    Bool_delete(&self->is_ns_field, &(Bool){_t2715});
    ;
    Bool _t2716 = 0;
    (void)_t2716;
    Bool_delete(&self->is_ext, &(Bool){_t2716});
    ;
    Bool _t2717 = 0;
    (void)_t2717;
    Bool_delete(&self->is_core, &(Bool){_t2717});
    ;
    Bool _t2718 = 0;
    (void)_t2718;
    Bool_delete(&self->save_old_delete, &(Bool){_t2718});
    ;
    Bool _t2719 = 0;
    (void)_t2719;
    I32_delete(&self->total_struct_size, &(Bool){_t2719});
    ;
    Bool _t2720 = 0;
    (void)_t2720;
    I32_delete(&self->variadic_index, &(Bool){_t2720});
    ;
    Bool _t2721 = 0;
    (void)_t2721;
    U32_delete(&self->variadic_count, &(Bool){_t2721});
    ;
    Bool _t2722 = 0;
    (void)_t2722;
    I32_delete(&self->kwargs_index, &(Bool){_t2722});
    ;
    Bool _t2723 = 0;
    (void)_t2723;
    U32_delete(&self->kwargs_count, &(Bool){_t2723});
    ;
    Bool _t2724 = 0;
    (void)_t2724;
    Vec_delete(&self->children, &(Bool){_t2724});
    ;
    Bool _t2725 = 0;
    (void)_t2725;
    U32_delete(&self->line, &(Bool){_t2725});
    ;
    Bool _t2726 = 0;
    (void)_t2726;
    U32_delete(&self->col, &(Bool){_t2726});
    ;
    Bool _t2727 = 0;
    (void)_t2727;
    Str_delete(&self->path, &(Bool){_t2727});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Expr_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Expr);
    return r;
}

Str * node_name(ExprData * data) {
    (void)data;
    {
        ExprData *_sw2729 = ExprData_clone(data);
        (void)_sw2729;
        Bool _t2780; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Body()); _t2780 = *_hp; free(_hp); }
        (void)_t2780;
        if (_t2780) {
            Str *_t2730 = Str_lit("body", 4ULL);
            (void)_t2730;
            ExprData_delete(_sw2729, &(Bool){1});
            ;
            return _t2730;
        } else {
            Bool _t2779; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2729); _t2779 = *_hp; free(_hp); }
            (void)_t2779;
            if (_t2779) {
                Str *_t2731 = Str_lit("str", 3ULL);
                (void)_t2731;
                ;
                ExprData_delete(_sw2729, &(Bool){1});
                ;
                return _t2731;
            } else {
                Bool _t2778; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2729); _t2778 = *_hp; free(_hp); }
                (void)_t2778;
                if (_t2778) {
                    Str *_t2732 = Str_lit("num", 3ULL);
                    (void)_t2732;
                    ;
                    ;
                    ExprData_delete(_sw2729, &(Bool){1});
                    ;
                    return _t2732;
                } else {
                    Bool _t2777; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2729); _t2777 = *_hp; free(_hp); }
                    (void)_t2777;
                    if (_t2777) {
                        Str *_t2733 = Str_lit("bool", 4ULL);
                        (void)_t2733;
                        ;
                        ;
                        ;
                        ExprData_delete(_sw2729, &(Bool){1});
                        ;
                        return _t2733;
                    } else {
                        Bool _t2776; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_LiteralNull()); _t2776 = *_hp; free(_hp); }
                        (void)_t2776;
                        if (_t2776) {
                            Str *_t2734 = Str_lit("null", 4ULL);
                            (void)_t2734;
                            ;
                            ;
                            ;
                            ;
                            ExprData_delete(_sw2729, &(Bool){1});
                            ;
                            return _t2734;
                        } else {
                            Bool _t2775; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2729); _t2775 = *_hp; free(_hp); }
                            (void)_t2775;
                            if (_t2775) {
                                Str *_t2735 = Str_lit("ident", 5ULL);
                                (void)_t2735;
                                ;
                                ;
                                ;
                                ;
                                ;
                                ExprData_delete(_sw2729, &(Bool){1});
                                ;
                                return _t2735;
                            } else {
                                Bool _t2774; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2729); _t2774 = *_hp; free(_hp); }
                                (void)_t2774;
                                if (_t2774) {
                                    Str *_t2736 = Str_lit("decl", 4ULL);
                                    (void)_t2736;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ExprData_delete(_sw2729, &(Bool){1});
                                    ;
                                    return _t2736;
                                } else {
                                    Bool _t2773; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2729); _t2773 = *_hp; free(_hp); }
                                    (void)_t2773;
                                    if (_t2773) {
                                        Str *_t2737 = Str_lit("assign", 6ULL);
                                        (void)_t2737;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ExprData_delete(_sw2729, &(Bool){1});
                                        ;
                                        return _t2737;
                                    } else {
                                        Bool _t2772; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_FCall()); _t2772 = *_hp; free(_hp); }
                                        (void)_t2772;
                                        if (_t2772) {
                                            Str *_t2738 = Str_lit("fcall", 5ULL);
                                            (void)_t2738;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ExprData_delete(_sw2729, &(Bool){1});
                                            ;
                                            return _t2738;
                                        } else {
                                            Bool _t2771; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2729); _t2771 = *_hp; free(_hp); }
                                            (void)_t2771;
                                            if (_t2771) {
                                                Str *_t2739 = Str_lit("func_def", 8ULL);
                                                (void)_t2739;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ExprData_delete(_sw2729, &(Bool){1});
                                                ;
                                                return _t2739;
                                            } else {
                                                Bool _t2770; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_StructDef()); _t2770 = *_hp; free(_hp); }
                                                (void)_t2770;
                                                if (_t2770) {
                                                    Str *_t2740 = Str_lit("struct_def", 10ULL);
                                                    (void)_t2740;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                    ;
                                                    return _t2740;
                                                } else {
                                                    Bool _t2769; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_EnumDef()); _t2769 = *_hp; free(_hp); }
                                                    (void)_t2769;
                                                    if (_t2769) {
                                                        Str *_t2741 = Str_lit("enum_def", 8ULL);
                                                        (void)_t2741;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                        ;
                                                        return _t2741;
                                                    } else {
                                                        Bool _t2768; { Bool *_hp = (Bool *)ExprData_is_FieldAccess(_sw2729); _t2768 = *_hp; free(_hp); }
                                                        (void)_t2768;
                                                        if (_t2768) {
                                                            Str *_t2742 = Str_lit("field_access", 12ULL);
                                                            (void)_t2742;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                            ;
                                                            return _t2742;
                                                        } else {
                                                            Bool _t2767; { Bool *_hp = (Bool *)ExprData_is_FieldAssign(_sw2729); _t2767 = *_hp; free(_hp); }
                                                            (void)_t2767;
                                                            if (_t2767) {
                                                                Str *_t2743 = Str_lit("field_assign", 12ULL);
                                                                (void)_t2743;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                ;
                                                                return _t2743;
                                                            } else {
                                                                Bool _t2766; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Return()); _t2766 = *_hp; free(_hp); }
                                                                (void)_t2766;
                                                                if (_t2766) {
                                                                    Str *_t2744 = Str_lit("return", 6ULL);
                                                                    (void)_t2744;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                    ;
                                                                    return _t2744;
                                                                } else {
                                                                    Bool _t2765; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_If()); _t2765 = *_hp; free(_hp); }
                                                                    (void)_t2765;
                                                                    if (_t2765) {
                                                                        Str *_t2745 = Str_lit("if", 2ULL);
                                                                        (void)_t2745;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                        ;
                                                                        return _t2745;
                                                                    } else {
                                                                        Bool _t2764; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_While()); _t2764 = *_hp; free(_hp); }
                                                                        (void)_t2764;
                                                                        if (_t2764) {
                                                                            Str *_t2746 = Str_lit("while", 5ULL);
                                                                            (void)_t2746;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                            ;
                                                                            return _t2746;
                                                                        } else {
                                                                            Bool _t2763; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2729); _t2763 = *_hp; free(_hp); }
                                                                            (void)_t2763;
                                                                            if (_t2763) {
                                                                                Str *_t2747 = Str_lit("for_in", 6ULL);
                                                                                (void)_t2747;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                                ;
                                                                                return _t2747;
                                                                            } else {
                                                                                Bool _t2762; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2729); _t2762 = *_hp; free(_hp); }
                                                                                (void)_t2762;
                                                                                if (_t2762) {
                                                                                    Str *_t2748 = Str_lit("named_arg", 9ULL);
                                                                                    (void)_t2748;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                                    ;
                                                                                    return _t2748;
                                                                                } else {
                                                                                    Bool _t2761; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Break()); _t2761 = *_hp; free(_hp); }
                                                                                    (void)_t2761;
                                                                                    if (_t2761) {
                                                                                        Str *_t2749 = Str_lit("break", 5ULL);
                                                                                        (void)_t2749;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                                        ;
                                                                                        return _t2749;
                                                                                    } else {
                                                                                        Bool _t2760; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Continue()); _t2760 = *_hp; free(_hp); }
                                                                                        (void)_t2760;
                                                                                        if (_t2760) {
                                                                                            Str *_t2750 = Str_lit("continue", 8ULL);
                                                                                            (void)_t2750;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                            ;
                                                                                            return _t2750;
                                                                                        } else {
                                                                                            Bool _t2759; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_MapLit()); _t2759 = *_hp; free(_hp); }
                                                                                            (void)_t2759;
                                                                                            if (_t2759) {
                                                                                                Str *_t2751 = Str_lit("map_lit", 7ULL);
                                                                                                (void)_t2751;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ExprData_delete(_sw2729, &(Bool){1});
                                                                                                ;
                                                                                                return _t2751;
                                                                                            } else {
                                                                                                Bool _t2758; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_SetLit()); _t2758 = *_hp; free(_hp); }
                                                                                                (void)_t2758;
                                                                                                if (_t2758) {
                                                                                                    Str *_t2752 = Str_lit("set_lit", 7ULL);
                                                                                                    (void)_t2752;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ExprData_delete(_sw2729, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t2752;
                                                                                                } else {
                                                                                                    Bool _t2757; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Switch()); _t2757 = *_hp; free(_hp); }
                                                                                                    (void)_t2757;
                                                                                                    if (_t2757) {
                                                                                                        Str *_t2753 = Str_lit("switch", 6ULL);
                                                                                                        (void)_t2753;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ExprData_delete(_sw2729, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t2753;
                                                                                                    } else {
                                                                                                        Bool _t2756; { Bool *_hp = (Bool *)ExprData_eq(_sw2729, ExprData_Case()); _t2756 = *_hp; free(_hp); }
                                                                                                        (void)_t2756;
                                                                                                        if (_t2756) {
                                                                                                            Str *_t2754 = Str_lit("case", 4ULL);
                                                                                                            (void)_t2754;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2754;
                                                                                                        } else {
                                                                                                            Str *_t2755 = Str_lit("?", 1ULL);
                                                                                                            (void)_t2755;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ExprData_delete(_sw2729, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t2755;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw2729, &(Bool){1});
        ;
    }
}

Str * func_type_name(FuncType * ft) {
    (void)ft;
    {
        FuncType *_sw2781 = FuncType_clone(ft);
        (void)_sw2781;
        Bool _t2794; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Func()); _t2794 = *_hp; free(_hp); }
        (void)_t2794;
        if (_t2794) {
            Str *_t2782 = Str_lit("func", 4ULL);
            (void)_t2782;
            FuncType_delete(_sw2781, &(Bool){1});
            ;
            return _t2782;
        } else {
            Bool _t2793; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Proc()); _t2793 = *_hp; free(_hp); }
            (void)_t2793;
            if (_t2793) {
                Str *_t2783 = Str_lit("proc", 4ULL);
                (void)_t2783;
                ;
                FuncType_delete(_sw2781, &(Bool){1});
                ;
                return _t2783;
            } else {
                Bool _t2792; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Test()); _t2792 = *_hp; free(_hp); }
                (void)_t2792;
                if (_t2792) {
                    Str *_t2784 = Str_lit("test", 4ULL);
                    (void)_t2784;
                    ;
                    ;
                    FuncType_delete(_sw2781, &(Bool){1});
                    ;
                    return _t2784;
                } else {
                    Bool _t2791; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_Macro()); _t2791 = *_hp; free(_hp); }
                    (void)_t2791;
                    if (_t2791) {
                        Str *_t2785 = Str_lit("macro", 5ULL);
                        (void)_t2785;
                        ;
                        ;
                        ;
                        FuncType_delete(_sw2781, &(Bool){1});
                        ;
                        return _t2785;
                    } else {
                        Bool _t2790; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_ExtFunc()); _t2790 = *_hp; free(_hp); }
                        (void)_t2790;
                        if (_t2790) {
                            Str *_t2786 = Str_lit("ext_func", 8ULL);
                            (void)_t2786;
                            ;
                            ;
                            ;
                            ;
                            FuncType_delete(_sw2781, &(Bool){1});
                            ;
                            return _t2786;
                        } else {
                            Bool _t2789; { Bool *_hp = (Bool *)FuncType_eq(_sw2781, FuncType_ExtProc()); _t2789 = *_hp; free(_hp); }
                            (void)_t2789;
                            if (_t2789) {
                                Str *_t2787 = Str_lit("ext_proc", 8ULL);
                                (void)_t2787;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2781, &(Bool){1});
                                ;
                                return _t2787;
                            } else {
                                Str *_t2788 = Str_lit("?", 1ULL);
                                (void)_t2788;
                                ;
                                ;
                                ;
                                ;
                                ;
                                FuncType_delete(_sw2781, &(Bool){1});
                                ;
                                return _t2788;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        FuncType_delete(_sw2781, &(Bool){1});
        ;
    }
}

void ast_print(Expr * e, U32 indent) {
    (void)e;
    (void)indent;
    {
        U64 _fi2795 = 0;
        (void)_fi2795;
        while (1) {
            I64 _t2797 = U32_to_i64(indent);
            (void)_t2797;
            U64 _t2798 = 0;
            (void)_t2798;
            U64 _t2799 = I64_to_u64(_t2797);
            (void)_t2799;
            ;
            Range *_t2800 = Range_new(_t2798, _t2799);
            (void)_t2800;
            ;
            ;
            U64 _t2801; { U64 *_hp = (U64 *)Range_len(_t2800); _t2801 = *_hp; free(_hp); }
            (void)_t2801;
            Range_delete(_t2800, &(Bool){1});
            Bool _wcond2796; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2795}, &(U64){_t2801}); _wcond2796 = *_hp; free(_hp); }
            (void)_wcond2796;
            ;
            if (_wcond2796) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2802 = U32_to_i64(indent);
            (void)_t2802;
            U64 _t2803 = 0;
            (void)_t2803;
            U64 _t2804 = I64_to_u64(_t2802);
            (void)_t2804;
            ;
            Range *_t2805 = Range_new(_t2803, _t2804);
            (void)_t2805;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2805, _fi2795); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2805, &(Bool){1});
            ;
            U64 _t2806 = 1;
            (void)_t2806;
            U64 _t2807 = U64_add(_fi2795, _t2806);
            (void)_t2807;
            ;
            _fi2795 = _t2807;
            ;
            Str *_t2808 = Str_lit("Str", 3ULL);
            (void)_t2808;
            U64 _t2809; { U64 *_hp = (U64 *)Str_size(); _t2809 = *_hp; free(_hp); }
            (void)_t2809;
            U64 _t2810 = 1;
            (void)_t2810;
            Array *_va38 = Array_new(_t2808, &(U64){_t2809}, &(U64){_t2810});
            (void)_va38;
            Str_delete(_t2808, &(Bool){1});
            ;
            ;
            U64 _t2811 = 0;
            (void)_t2811;
            Str *_t2812 = Str_lit("  ", 2ULL);
            (void)_t2812;
            Array_set(_va38, &(U64){_t2811}, _t2812);
            ;
            print(_va38);
        }
        ;
    }
    Str *_t2946 = Str_lit("Str", 3ULL);
    (void)_t2946;
    U64 _t2947; { U64 *_hp = (U64 *)Str_size(); _t2947 = *_hp; free(_hp); }
    (void)_t2947;
    U64 _t2948 = 2;
    (void)_t2948;
    Array *_va52 = Array_new(_t2946, &(U64){_t2947}, &(U64){_t2948});
    (void)_va52;
    Str_delete(_t2946, &(Bool){1});
    ;
    ;
    U64 _t2949 = 0;
    (void)_t2949;
    Str *_t2950 = Str_lit("(", 1ULL);
    (void)_t2950;
    Array_set(_va52, &(U64){_t2949}, _t2950);
    ;
    U64 _t2951 = 1;
    (void)_t2951;
    Str *_t2952 = node_name(&e->data);
    (void)_t2952;
    Array_set(_va52, &(U64){_t2951}, _t2952);
    ;
    print(_va52);
    Bool _t2953; { Bool *_hp = (Bool *)TilType_eq(&e->til_type, TilType_Unknown()); _t2953 = *_hp; free(_hp); }
    (void)_t2953;
    Bool _t2954 = Bool_not(_t2953);
    (void)_t2954;
    ;
    if (_t2954) {
        Str *_t2813 = Str_lit("Str", 3ULL);
        (void)_t2813;
        U64 _t2814; { U64 *_hp = (U64 *)Str_size(); _t2814 = *_hp; free(_hp); }
        (void)_t2814;
        U64 _t2815 = 2;
        (void)_t2815;
        Array *_va39 = Array_new(_t2813, &(U64){_t2814}, &(U64){_t2815});
        (void)_va39;
        Str_delete(_t2813, &(Bool){1});
        ;
        ;
        U64 _t2816 = 0;
        (void)_t2816;
        Str *_t2817 = Str_lit(":", 1ULL);
        (void)_t2817;
        Array_set(_va39, &(U64){_t2816}, _t2817);
        ;
        U64 _t2818 = 1;
        (void)_t2818;
        Str *_t2819 = til_type_name_c(&e->til_type);
        (void)_t2819;
        Array_set(_va39, &(U64){_t2818}, _t2819);
        ;
        print(_va39);
    }
    ;
    {
        ExprData *_sw2820 = ExprData_clone(&e->data);
        (void)_sw2820;
        Bool _t2907; { Bool *_hp = (Bool *)ExprData_is_Ident(_sw2820); _t2907 = *_hp; free(_hp); }
        (void)_t2907;
        if (_t2907) {
            Str *s = ExprData_get_Ident(_sw2820);
            (void)s;
            Str *_t2821 = Str_lit("Str", 3ULL);
            (void)_t2821;
            U64 _t2822; { U64 *_hp = (U64 *)Str_size(); _t2822 = *_hp; free(_hp); }
            (void)_t2822;
            U64 _t2823 = 3;
            (void)_t2823;
            Array *_va40 = Array_new(_t2821, &(U64){_t2822}, &(U64){_t2823});
            (void)_va40;
            Str_delete(_t2821, &(Bool){1});
            ;
            ;
            U64 _t2824 = 0;
            (void)_t2824;
            Str *_t2825 = Str_lit(" \"", 3ULL);
            (void)_t2825;
            Array_set(_va40, &(U64){_t2824}, _t2825);
            ;
            U64 _t2826 = 1;
            (void)_t2826;
            Str *_t2827 = Str_clone(s);
            (void)_t2827;
            Str_delete(s, &(Bool){1});
            Array_set(_va40, &(U64){_t2826}, _t2827);
            ;
            U64 _t2828 = 2;
            (void)_t2828;
            Str *_t2829 = Str_lit("\"", 2ULL);
            (void)_t2829;
            Array_set(_va40, &(U64){_t2828}, _t2829);
            ;
            print(_va40);
        } else {
            Bool _t2906; { Bool *_hp = (Bool *)ExprData_is_LiteralStr(_sw2820); _t2906 = *_hp; free(_hp); }
            (void)_t2906;
            if (_t2906) {
                Str *s = ExprData_get_LiteralStr(_sw2820);
                (void)s;
                Str *_t2830 = Str_lit("Str", 3ULL);
                (void)_t2830;
                U64 _t2831; { U64 *_hp = (U64 *)Str_size(); _t2831 = *_hp; free(_hp); }
                (void)_t2831;
                U64 _t2832 = 3;
                (void)_t2832;
                Array *_va41 = Array_new(_t2830, &(U64){_t2831}, &(U64){_t2832});
                (void)_va41;
                Str_delete(_t2830, &(Bool){1});
                ;
                ;
                U64 _t2833 = 0;
                (void)_t2833;
                Str *_t2834 = Str_lit(" \"", 3ULL);
                (void)_t2834;
                Array_set(_va41, &(U64){_t2833}, _t2834);
                ;
                U64 _t2835 = 1;
                (void)_t2835;
                Str *_t2836 = Str_clone(s);
                (void)_t2836;
                Str_delete(s, &(Bool){1});
                Array_set(_va41, &(U64){_t2835}, _t2836);
                ;
                U64 _t2837 = 2;
                (void)_t2837;
                Str *_t2838 = Str_lit("\"", 2ULL);
                (void)_t2838;
                Array_set(_va41, &(U64){_t2837}, _t2838);
                ;
                print(_va41);
            } else {
                Bool _t2905; { Bool *_hp = (Bool *)ExprData_is_LiteralNum(_sw2820); _t2905 = *_hp; free(_hp); }
                (void)_t2905;
                if (_t2905) {
                    Str *s = ExprData_get_LiteralNum(_sw2820);
                    (void)s;
                    Str *_t2839 = Str_lit("Str", 3ULL);
                    (void)_t2839;
                    U64 _t2840; { U64 *_hp = (U64 *)Str_size(); _t2840 = *_hp; free(_hp); }
                    (void)_t2840;
                    U64 _t2841 = 3;
                    (void)_t2841;
                    Array *_va42 = Array_new(_t2839, &(U64){_t2840}, &(U64){_t2841});
                    (void)_va42;
                    Str_delete(_t2839, &(Bool){1});
                    ;
                    ;
                    U64 _t2842 = 0;
                    (void)_t2842;
                    Str *_t2843 = Str_lit(" \"", 3ULL);
                    (void)_t2843;
                    Array_set(_va42, &(U64){_t2842}, _t2843);
                    ;
                    U64 _t2844 = 1;
                    (void)_t2844;
                    Str *_t2845 = Str_clone(s);
                    (void)_t2845;
                    Str_delete(s, &(Bool){1});
                    Array_set(_va42, &(U64){_t2844}, _t2845);
                    ;
                    U64 _t2846 = 2;
                    (void)_t2846;
                    Str *_t2847 = Str_lit("\"", 2ULL);
                    (void)_t2847;
                    Array_set(_va42, &(U64){_t2846}, _t2847);
                    ;
                    print(_va42);
                } else {
                    Bool _t2904; { Bool *_hp = (Bool *)ExprData_is_LiteralBool(_sw2820); _t2904 = *_hp; free(_hp); }
                    (void)_t2904;
                    if (_t2904) {
                        Str *s = ExprData_get_LiteralBool(_sw2820);
                        (void)s;
                        Str *_t2848 = Str_lit("Str", 3ULL);
                        (void)_t2848;
                        U64 _t2849; { U64 *_hp = (U64 *)Str_size(); _t2849 = *_hp; free(_hp); }
                        (void)_t2849;
                        U64 _t2850 = 3;
                        (void)_t2850;
                        Array *_va43 = Array_new(_t2848, &(U64){_t2849}, &(U64){_t2850});
                        (void)_va43;
                        Str_delete(_t2848, &(Bool){1});
                        ;
                        ;
                        U64 _t2851 = 0;
                        (void)_t2851;
                        Str *_t2852 = Str_lit(" \"", 3ULL);
                        (void)_t2852;
                        Array_set(_va43, &(U64){_t2851}, _t2852);
                        ;
                        U64 _t2853 = 1;
                        (void)_t2853;
                        Str *_t2854 = Str_clone(s);
                        (void)_t2854;
                        Str_delete(s, &(Bool){1});
                        Array_set(_va43, &(U64){_t2853}, _t2854);
                        ;
                        U64 _t2855 = 2;
                        (void)_t2855;
                        Str *_t2856 = Str_lit("\"", 2ULL);
                        (void)_t2856;
                        Array_set(_va43, &(U64){_t2855}, _t2856);
                        ;
                        print(_va43);
                    } else {
                        Bool _t2903; { Bool *_hp = (Bool *)ExprData_is_ForIn(_sw2820); _t2903 = *_hp; free(_hp); }
                        (void)_t2903;
                        if (_t2903) {
                            Str *s = ExprData_get_ForIn(_sw2820);
                            (void)s;
                            Str *_t2857 = Str_lit("Str", 3ULL);
                            (void)_t2857;
                            U64 _t2858; { U64 *_hp = (U64 *)Str_size(); _t2858 = *_hp; free(_hp); }
                            (void)_t2858;
                            U64 _t2859 = 3;
                            (void)_t2859;
                            Array *_va44 = Array_new(_t2857, &(U64){_t2858}, &(U64){_t2859});
                            (void)_va44;
                            Str_delete(_t2857, &(Bool){1});
                            ;
                            ;
                            U64 _t2860 = 0;
                            (void)_t2860;
                            Str *_t2861 = Str_lit(" \"", 3ULL);
                            (void)_t2861;
                            Array_set(_va44, &(U64){_t2860}, _t2861);
                            ;
                            U64 _t2862 = 1;
                            (void)_t2862;
                            Str *_t2863 = Str_clone(s);
                            (void)_t2863;
                            Str_delete(s, &(Bool){1});
                            Array_set(_va44, &(U64){_t2862}, _t2863);
                            ;
                            U64 _t2864 = 2;
                            (void)_t2864;
                            Str *_t2865 = Str_lit("\"", 2ULL);
                            (void)_t2865;
                            Array_set(_va44, &(U64){_t2864}, _t2865);
                            ;
                            print(_va44);
                        } else {
                            Bool _t2902; { Bool *_hp = (Bool *)ExprData_is_Decl(_sw2820); _t2902 = *_hp; free(_hp); }
                            (void)_t2902;
                            if (_t2902) {
                                Declaration *decl = ExprData_get_Decl(_sw2820);
                                (void)decl;
                                if (decl->is_mut) {
                                    Str *_t2866 = Str_lit("Str", 3ULL);
                                    (void)_t2866;
                                    U64 _t2867; { U64 *_hp = (U64 *)Str_size(); _t2867 = *_hp; free(_hp); }
                                    (void)_t2867;
                                    U64 _t2868 = 1;
                                    (void)_t2868;
                                    Array *_va45 = Array_new(_t2866, &(U64){_t2867}, &(U64){_t2868});
                                    (void)_va45;
                                    Str_delete(_t2866, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2869 = 0;
                                    (void)_t2869;
                                    Str *_t2870 = Str_lit(" mut", 4ULL);
                                    (void)_t2870;
                                    Array_set(_va45, &(U64){_t2869}, _t2870);
                                    ;
                                    print(_va45);
                                }
                                Str *_t2871 = Str_lit("Str", 3ULL);
                                (void)_t2871;
                                U64 _t2872; { U64 *_hp = (U64 *)Str_size(); _t2872 = *_hp; free(_hp); }
                                (void)_t2872;
                                U64 _t2873 = 2;
                                (void)_t2873;
                                Array *_va46 = Array_new(_t2871, &(U64){_t2872}, &(U64){_t2873});
                                (void)_va46;
                                Str_delete(_t2871, &(Bool){1});
                                ;
                                ;
                                U64 _t2874 = 0;
                                (void)_t2874;
                                Str *_t2875 = Str_lit(" ", 1ULL);
                                (void)_t2875;
                                Array_set(_va46, &(U64){_t2874}, _t2875);
                                ;
                                U64 _t2876 = 1;
                                (void)_t2876;
                                Str *_t2877 = Str_clone(&decl->name);
                                (void)_t2877;
                                Declaration_delete(decl, &(Bool){1});
                                Array_set(_va46, &(U64){_t2876}, _t2877);
                                ;
                                print(_va46);
                            } else {
                                Bool _t2901; { Bool *_hp = (Bool *)ExprData_is_Assign(_sw2820); _t2901 = *_hp; free(_hp); }
                                (void)_t2901;
                                if (_t2901) {
                                    Str *s = ExprData_get_Assign(_sw2820);
                                    (void)s;
                                    Str *_t2878 = Str_lit("Str", 3ULL);
                                    (void)_t2878;
                                    U64 _t2879; { U64 *_hp = (U64 *)Str_size(); _t2879 = *_hp; free(_hp); }
                                    (void)_t2879;
                                    U64 _t2880 = 2;
                                    (void)_t2880;
                                    Array *_va47 = Array_new(_t2878, &(U64){_t2879}, &(U64){_t2880});
                                    (void)_va47;
                                    Str_delete(_t2878, &(Bool){1});
                                    ;
                                    ;
                                    U64 _t2881 = 0;
                                    (void)_t2881;
                                    Str *_t2882 = Str_lit(" ", 1ULL);
                                    (void)_t2882;
                                    Array_set(_va47, &(U64){_t2881}, _t2882);
                                    ;
                                    U64 _t2883 = 1;
                                    (void)_t2883;
                                    Str *_t2884 = Str_clone(s);
                                    (void)_t2884;
                                    Str_delete(s, &(Bool){1});
                                    Array_set(_va47, &(U64){_t2883}, _t2884);
                                    ;
                                    print(_va47);
                                } else {
                                    Bool _t2900; { Bool *_hp = (Bool *)ExprData_is_NamedArg(_sw2820); _t2900 = *_hp; free(_hp); }
                                    (void)_t2900;
                                    if (_t2900) {
                                        Str *s = ExprData_get_NamedArg(_sw2820);
                                        (void)s;
                                        Str *_t2885 = Str_lit("Str", 3ULL);
                                        (void)_t2885;
                                        U64 _t2886; { U64 *_hp = (U64 *)Str_size(); _t2886 = *_hp; free(_hp); }
                                        (void)_t2886;
                                        U64 _t2887 = 2;
                                        (void)_t2887;
                                        Array *_va48 = Array_new(_t2885, &(U64){_t2886}, &(U64){_t2887});
                                        (void)_va48;
                                        Str_delete(_t2885, &(Bool){1});
                                        ;
                                        ;
                                        U64 _t2888 = 0;
                                        (void)_t2888;
                                        Str *_t2889 = Str_lit(" ", 1ULL);
                                        (void)_t2889;
                                        Array_set(_va48, &(U64){_t2888}, _t2889);
                                        ;
                                        U64 _t2890 = 1;
                                        (void)_t2890;
                                        Str *_t2891 = Str_clone(s);
                                        (void)_t2891;
                                        Str_delete(s, &(Bool){1});
                                        Array_set(_va48, &(U64){_t2890}, _t2891);
                                        ;
                                        print(_va48);
                                    } else {
                                        Bool _t2899; { Bool *_hp = (Bool *)ExprData_is_FuncDef(_sw2820); _t2899 = *_hp; free(_hp); }
                                        (void)_t2899;
                                        if (_t2899) {
                                            FunctionDef *fdef = ExprData_get_FuncDef(_sw2820);
                                            (void)fdef;
                                            Str *_t2892 = Str_lit("Str", 3ULL);
                                            (void)_t2892;
                                            U64 _t2893; { U64 *_hp = (U64 *)Str_size(); _t2893 = *_hp; free(_hp); }
                                            (void)_t2893;
                                            U64 _t2894 = 2;
                                            (void)_t2894;
                                            Array *_va49 = Array_new(_t2892, &(U64){_t2893}, &(U64){_t2894});
                                            (void)_va49;
                                            Str_delete(_t2892, &(Bool){1});
                                            ;
                                            ;
                                            U64 _t2895 = 0;
                                            (void)_t2895;
                                            Str *_t2896 = Str_lit(" ", 1ULL);
                                            (void)_t2896;
                                            Array_set(_va49, &(U64){_t2895}, _t2896);
                                            ;
                                            U64 _t2897 = 1;
                                            (void)_t2897;
                                            Str *_t2898 = func_type_name(&fdef->func_type);
                                            (void)_t2898;
                                            FunctionDef_delete(fdef, &(Bool){1});
                                            Array_set(_va49, &(U64){_t2897}, _t2898);
                                            ;
                                            print(_va49);
                                        } else {
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ExprData_delete(_sw2820, &(Bool){1});
        ;
    }
    U64 _t2955; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2955 = *_hp; free(_hp); }
    (void)_t2955;
    U64 _t2956 = 0;
    (void)_t2956;
    Bool _t2957; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2955}, &(U64){_t2956}); _t2957 = *_hp; free(_hp); }
    (void)_t2957;
    ;
    ;
    if (_t2957) {
        Str *_t2941 = Str_lit("Str", 3ULL);
        (void)_t2941;
        U64 _t2942; { U64 *_hp = (U64 *)Str_size(); _t2942 = *_hp; free(_hp); }
        (void)_t2942;
        U64 _t2943 = 1;
        (void)_t2943;
        Array *_va51 = Array_new(_t2941, &(U64){_t2942}, &(U64){_t2943});
        (void)_va51;
        Str_delete(_t2941, &(Bool){1});
        ;
        ;
        U64 _t2944 = 0;
        (void)_t2944;
        Str *_t2945 = Str_lit("", 0ULL);
        (void)_t2945;
        Array_set(_va51, &(U64){_t2944}, _t2945);
        ;
        println(_va51);
        {
            U64 _fi2908 = 0;
            (void)_fi2908;
            while (1) {
                U64 _t2910 = 0;
                (void)_t2910;
                U64 _t2911; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2911 = *_hp; free(_hp); }
                (void)_t2911;
                Range *_t2912 = Range_new(_t2910, _t2911);
                (void)_t2912;
                ;
                ;
                U64 _t2913; { U64 *_hp = (U64 *)Range_len(_t2912); _t2913 = *_hp; free(_hp); }
                (void)_t2913;
                Range_delete(_t2912, &(Bool){1});
                Bool _wcond2909; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2908}, &(U64){_t2913}); _wcond2909 = *_hp; free(_hp); }
                (void)_wcond2909;
                ;
                if (_wcond2909) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t2914 = 0;
                (void)_t2914;
                U64 _t2915; { U64 *_hp = (U64 *)Vec_len(&e->children); _t2915 = *_hp; free(_hp); }
                (void)_t2915;
                Range *_t2916 = Range_new(_t2914, _t2915);
                (void)_t2916;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2916, _fi2908); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2916, &(Bool){1});
                U64 _t2917 = 1;
                (void)_t2917;
                U64 _t2918 = U64_add(_fi2908, _t2917);
                (void)_t2918;
                ;
                _fi2908 = _t2918;
                ;
                I64 *_t2919 = malloc(sizeof(I64)); *_t2919 = U64_to_i64(i);
                (void)_t2919;
                ;
                U32 _t2920 = 1;
                (void)_t2920;
                Expr *_t2921 = Expr_child(e, _t2919);
                (void)_t2921;
                U32 _t2922 = U32_add(indent, _t2920);
                (void)_t2922;
                ;
                ast_print(_t2921, _t2922);
                I64_delete(_t2919, &(Bool){1});
                ;
            }
            ;
        }
        {
            U64 _fi2923 = 0;
            (void)_fi2923;
            while (1) {
                I64 _t2925 = U32_to_i64(indent);
                (void)_t2925;
                U64 _t2926 = 0;
                (void)_t2926;
                U64 _t2927 = I64_to_u64(_t2925);
                (void)_t2927;
                ;
                Range *_t2928 = Range_new(_t2926, _t2927);
                (void)_t2928;
                ;
                ;
                U64 _t2929; { U64 *_hp = (U64 *)Range_len(_t2928); _t2929 = *_hp; free(_hp); }
                (void)_t2929;
                Range_delete(_t2928, &(Bool){1});
                Bool _wcond2924; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2923}, &(U64){_t2929}); _wcond2924 = *_hp; free(_hp); }
                (void)_wcond2924;
                ;
                if (_wcond2924) {
                } else {
                    ;
                    break;
                }
                ;
                I64 _t2930 = U32_to_i64(indent);
                (void)_t2930;
                U64 _t2931 = 0;
                (void)_t2931;
                U64 _t2932 = I64_to_u64(_t2930);
                (void)_t2932;
                ;
                Range *_t2933 = Range_new(_t2931, _t2932);
                (void)_t2933;
                ;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t2933, _fi2923); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t2933, &(Bool){1});
                ;
                U64 _t2934 = 1;
                (void)_t2934;
                U64 _t2935 = U64_add(_fi2923, _t2934);
                (void)_t2935;
                ;
                _fi2923 = _t2935;
                ;
                Str *_t2936 = Str_lit("Str", 3ULL);
                (void)_t2936;
                U64 _t2937; { U64 *_hp = (U64 *)Str_size(); _t2937 = *_hp; free(_hp); }
                (void)_t2937;
                U64 _t2938 = 1;
                (void)_t2938;
                Array *_va50 = Array_new(_t2936, &(U64){_t2937}, &(U64){_t2938});
                (void)_va50;
                Str_delete(_t2936, &(Bool){1});
                ;
                ;
                U64 _t2939 = 0;
                (void)_t2939;
                Str *_t2940 = Str_lit("  ", 2ULL);
                (void)_t2940;
                Array_set(_va50, &(U64){_t2939}, _t2940);
                ;
                print(_va50);
            }
            ;
        }
    }
    ;
    Str *_t2958 = Str_lit("Str", 3ULL);
    (void)_t2958;
    U64 _t2959; { U64 *_hp = (U64 *)Str_size(); _t2959 = *_hp; free(_hp); }
    (void)_t2959;
    U64 _t2960 = 1;
    (void)_t2960;
    Array *_va53 = Array_new(_t2958, &(U64){_t2959}, &(U64){_t2960});
    (void)_va53;
    Str_delete(_t2958, &(Bool){1});
    ;
    ;
    U64 _t2961 = 0;
    (void)_t2961;
    Str *_t2962 = Str_lit(")", 1ULL);
    (void)_t2962;
    Array_set(_va53, &(U64){_t2961}, _t2962);
    ;
    println(_va53);
}

Bool * enum_has_payloads(Expr * enum_def) {
    (void)enum_def;
    I64 *_t2984 = malloc(sizeof(I64));
    *_t2984 = 0;
    (void)_t2984;
    Expr *body = Expr_child(enum_def, _t2984);
    (void)body;
    {
        U64 _fi2963 = 0;
        (void)_fi2963;
        while (1) {
            I64 _t2971; { I64 *_hp = (I64 *)Expr_child_count(body); _t2971 = *_hp; free(_hp); }
            (void)_t2971;
            U64 _t2972 = 0;
            (void)_t2972;
            U64 _t2973 = I64_to_u64(_t2971);
            (void)_t2973;
            ;
            Range *_t2974 = Range_new(_t2972, _t2973);
            (void)_t2974;
            ;
            ;
            U64 _t2975; { U64 *_hp = (U64 *)Range_len(_t2974); _t2975 = *_hp; free(_hp); }
            (void)_t2975;
            Range_delete(_t2974, &(Bool){1});
            Bool _wcond2964; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2963}, &(U64){_t2975}); _wcond2964 = *_hp; free(_hp); }
            (void)_wcond2964;
            ;
            if (_wcond2964) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2976; { I64 *_hp = (I64 *)Expr_child_count(body); _t2976 = *_hp; free(_hp); }
            (void)_t2976;
            U64 _t2977 = 0;
            (void)_t2977;
            U64 _t2978 = I64_to_u64(_t2976);
            (void)_t2978;
            ;
            Range *_t2979 = Range_new(_t2977, _t2978);
            (void)_t2979;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t2979, _fi2963); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t2979, &(Bool){1});
            U64 _t2980 = 1;
            (void)_t2980;
            U64 _t2981 = U64_add(_fi2963, _t2980);
            (void)_t2981;
            ;
            _fi2963 = _t2981;
            ;
            I64 *_t2982 = malloc(sizeof(I64)); *_t2982 = U64_to_i64(i);
            (void)_t2982;
            ;
            Expr *f = Expr_child(body, _t2982);
            (void)f;
            Bool _t2983; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t2983 = *_hp; free(_hp); }
            (void)_t2983;
            if (_t2983) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                U64 _t2966; { U64 *_hp = (U64 *)Str_len(&decl->explicit_type); _t2966 = *_hp; free(_hp); }
                (void)_t2966;
                U64 _t2967 = 0;
                (void)_t2967;
                Bool _t2968 = Bool_not(decl->is_namespace);
                (void)_t2968;
                Declaration_delete(decl, &(Bool){1});
                Bool _t2969; { Bool *_hp = (Bool *)U64_gt(&(U64){_t2966}, &(U64){_t2967}); _t2969 = *_hp; free(_hp); }
                (void)_t2969;
                ;
                ;
                Bool _t2970 = Bool_and(_t2968, _t2969);
                (void)_t2970;
                ;
                ;
                if (_t2970) {
                    Bool _t2965 = 1;
                    (void)_t2965;
                    ;
                    I64_delete(_t2982, &(Bool){1});
                    ;
                    ;
                    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2965; return _r; }
                }
                ;
            }
            I64_delete(_t2982, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t2984, &(Bool){1});
    Bool _t2985 = 0;
    (void)_t2985;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t2985; return _r; }
}

I32 * enum_variant_tag(Expr * enum_def, Str * variant_name) {
    (void)enum_def;
    (void)variant_name;
    I64 *_t3005 = malloc(sizeof(I64));
    *_t3005 = 0;
    (void)_t3005;
    Expr *body = Expr_child(enum_def, _t3005);
    (void)body;
    I32 tag = 0;
    (void)tag;
    {
        U64 _fi2986 = 0;
        (void)_fi2986;
        while (1) {
            I64 _t2992; { I64 *_hp = (I64 *)Expr_child_count(body); _t2992 = *_hp; free(_hp); }
            (void)_t2992;
            U64 _t2993 = 0;
            (void)_t2993;
            U64 _t2994 = I64_to_u64(_t2992);
            (void)_t2994;
            ;
            Range *_t2995 = Range_new(_t2993, _t2994);
            (void)_t2995;
            ;
            ;
            U64 _t2996; { U64 *_hp = (U64 *)Range_len(_t2995); _t2996 = *_hp; free(_hp); }
            (void)_t2996;
            Range_delete(_t2995, &(Bool){1});
            Bool _wcond2987; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi2986}, &(U64){_t2996}); _wcond2987 = *_hp; free(_hp); }
            (void)_wcond2987;
            ;
            if (_wcond2987) {
            } else {
                ;
                break;
            }
            ;
            I64 _t2997; { I64 *_hp = (I64 *)Expr_child_count(body); _t2997 = *_hp; free(_hp); }
            (void)_t2997;
            U64 _t2998 = 0;
            (void)_t2998;
            U64 _t2999 = I64_to_u64(_t2997);
            (void)_t2999;
            ;
            Range *_t3000 = Range_new(_t2998, _t2999);
            (void)_t3000;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3000, _fi2986); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3000, &(Bool){1});
            U64 _t3001 = 1;
            (void)_t3001;
            U64 _t3002 = U64_add(_fi2986, _t3001);
            (void)_t3002;
            ;
            _fi2986 = _t3002;
            ;
            I64 *_t3003 = malloc(sizeof(I64)); *_t3003 = U64_to_i64(i);
            (void)_t3003;
            ;
            Expr *f = Expr_child(body, _t3003);
            (void)f;
            Bool _t3004; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3004 = *_hp; free(_hp); }
            (void)_t3004;
            if (_t3004) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t2991 = Bool_not(decl->is_namespace);
                (void)_t2991;
                if (_t2991) {
                    Bool _t2988; { Bool *_hp = (Bool *)Str_eq(&decl->name, variant_name); _t2988 = *_hp; free(_hp); }
                    (void)_t2988;
                    if (_t2988) {
                        ;
                        ;
                        Declaration_delete(decl, &(Bool){1});
                        I64_delete(_t3003, &(Bool){1});
                        ;
                        ;
                        { I32 *_r = malloc(sizeof(I32)); *_r = tag; return _r; }
                    }
                    ;
                    I32 _t2989 = 1;
                    (void)_t2989;
                    I32 _t2990 = I32_add(tag, _t2989);
                    (void)_t2990;
                    ;
                    tag = _t2990;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3003, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3005, &(Bool){1});
    ;
    I64 _t3006 = 0;
    (void)_t3006;
    I64 _t3007 = 1;
    (void)_t3007;
    I64 _t3008 = I64_sub(_t3006, _t3007);
    (void)_t3008;
    ;
    ;
    I32 _t3009 = I64_to_i32(_t3008);
    (void)_t3009;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t3009; return _r; }
}

Str * enum_variant_type(Expr * enum_def, I32 tag) {
    (void)enum_def;
    (void)tag;
    I64 *_t3029 = malloc(sizeof(I64));
    *_t3029 = 0;
    (void)_t3029;
    Expr *body = Expr_child(enum_def, _t3029);
    (void)body;
    I32 idx = 0;
    (void)idx;
    {
        U64 _fi3010 = 0;
        (void)_fi3010;
        while (1) {
            I64 _t3016; { I64 *_hp = (I64 *)Expr_child_count(body); _t3016 = *_hp; free(_hp); }
            (void)_t3016;
            U64 _t3017 = 0;
            (void)_t3017;
            U64 _t3018 = I64_to_u64(_t3016);
            (void)_t3018;
            ;
            Range *_t3019 = Range_new(_t3017, _t3018);
            (void)_t3019;
            ;
            ;
            U64 _t3020; { U64 *_hp = (U64 *)Range_len(_t3019); _t3020 = *_hp; free(_hp); }
            (void)_t3020;
            Range_delete(_t3019, &(Bool){1});
            Bool _wcond3011; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi3010}, &(U64){_t3020}); _wcond3011 = *_hp; free(_hp); }
            (void)_wcond3011;
            ;
            if (_wcond3011) {
            } else {
                ;
                break;
            }
            ;
            I64 _t3021; { I64 *_hp = (I64 *)Expr_child_count(body); _t3021 = *_hp; free(_hp); }
            (void)_t3021;
            U64 _t3022 = 0;
            (void)_t3022;
            U64 _t3023 = I64_to_u64(_t3021);
            (void)_t3023;
            ;
            Range *_t3024 = Range_new(_t3022, _t3023);
            (void)_t3024;
            ;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t3024, _fi3010); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t3024, &(Bool){1});
            U64 _t3025 = 1;
            (void)_t3025;
            U64 _t3026 = U64_add(_fi3010, _t3025);
            (void)_t3026;
            ;
            _fi3010 = _t3026;
            ;
            I64 *_t3027 = malloc(sizeof(I64)); *_t3027 = U64_to_i64(i);
            (void)_t3027;
            ;
            Expr *f = Expr_child(body, _t3027);
            (void)f;
            Bool _t3028; { Bool *_hp = (Bool *)ExprData_is_Decl(&f->data); _t3028 = *_hp; free(_hp); }
            (void)_t3028;
            if (_t3028) {
                Declaration *decl = ExprData_get_Decl(&f->data);
                (void)decl;
                Bool _t3015 = Bool_not(decl->is_namespace);
                (void)_t3015;
                if (_t3015) {
                    Bool _t3012 = I32_eq(idx, tag);
                    (void)_t3012;
                    if (_t3012) {
                        ;
                        ;
                        I64_delete(_t3027, &(Bool){1});
                        ;
                        ;
                        { Str *_r = malloc(sizeof(Str)); *_r = decl->explicit_type; return _r; }
                    }
                    ;
                    I32 _t3013 = 1;
                    (void)_t3013;
                    I32 _t3014 = I32_add(idx, _t3013);
                    (void)_t3014;
                    ;
                    idx = _t3014;
                    ;
                }
                ;
                Declaration_delete(decl, &(Bool){1});
            }
            I64_delete(_t3027, &(Bool){1});
            ;
        }
        ;
    }
    I64_delete(_t3029, &(Bool){1});
    ;
    Str *_t3030 = Str_lit("", 0ULL);
    (void)_t3030;
    return _t3030;
}

